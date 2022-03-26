#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>

#include <stdio.h>

// gcc -g -o t1 t1.c -lavformat -lavcodec -lswscale -lz -lavtuil

#if LIBAVCODEC_VERSION_INT < AV_VERSION_INT(55, 28, 1)
#define av_frame_alloc avcodec_alloc_frame
#define av_frame_free avcodec_free_frame
// #define av_malloc       avcodec_malloc
// #define av_get_picture_type_char  avcodec_get_picture_type_char
#endif

static void SaveFrame(AVFrame *pFrame, int width, int height, int iFrame)
{
    FILE *pFile;
    char szFilename[32];
    int y;

    // Open file
    sprintf(szFilename, "frame_%d.ppm", iFrame);
    pFile = fopen(szFilename, "wb");
    if (pFile == NULL)
        return;

    // Write header
    fprintf(pFile, "P6\n%d %d\n255\n", width, height);

    // Write pixel data
    for (y = 0; y < height; y++)
        fwrite(pFrame->data[0] + y * pFrame->linesize[0], 1, width * 3, pFile);

    // Close file
    fclose(pFile);
}

//gcc -o t1 t1.c -lavformat -lavcodec -lswscale -lz
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        return -1;
    }

    printf("version:%d", LIBAVCODEC_VERSION_INT);

    char *file = argv[1];
    printf("open file: %s\n", file);

    av_register_all();

    int ret;
    AVFormatContext *pFormatCtx = NULL;

    // Open video file
    if (avformat_open_input(&pFormatCtx, file, NULL, NULL) != 0)
    {
        printf("failed to open file.\n");
        return -1; // Couldn't open file
    }

    // Retrieve stream information
    ret = avformat_find_stream_info(pFormatCtx, NULL);
    if (ret < 0)
    {
        printf("not find stream info. ret=%d\n", ret);
        return -1; // Couldn't find stream information
    }

    // Dump information about file onto standard error
    // av_dump_format(pFormatCtx, 0, file, 0);

    //find the first video stream.
    int video_stream = -1;
    for (int i = 0; i < pFormatCtx->nb_streams; i++)
    {
        printf("stream [%d], codec_type:%d\n", i, pFormatCtx->streams[i]->codec->codec_type);
        if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
        {
            video_stream = i;
        }
    }

    // Get a pointer to the codec context for the video stream
    AVCodecContext *pCodecCtx = pFormatCtx->streams[video_stream]->codec;

    // Find the decoder for the video stream
    AVCodec *pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
    if (pCodec == NULL)
    {
        printf("Unsupported codec!\n");
        return -1; // Codec not found
    }

    printf("codec_id:%d\n", pCodecCtx->codec_id);

    // Open codec
    if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0)
    {
        printf("failed to open codec\n");
        return -1; // Could not open codec
    }

    // Allocate video frame
    AVFrame *pFrame = av_frame_alloc();

    // Allocate an AVFrame structure
    AVFrame *pFrameRGB = av_frame_alloc();
    if (pFrameRGB == NULL)
        return -1;

    // Determine required buffer size and allocate buffer
    int numBytes = avpicture_get_size(AV_PIX_FMT_RGB24, pCodecCtx->width,
                                      pCodecCtx->height);
    uint8_t *buffer = (uint8_t *)av_malloc(numBytes * sizeof(uint8_t));

    //pix_fmt: example: AV_PIX_FMT_YUV420P
    printf("width:%d height:%d pix_fmt:%d numBytes=%d",
           pCodecCtx->width, pCodecCtx->height, pCodecCtx->pix_fmt, numBytes);

    // Assign appropriate parts of buffer to image planes in pFrameRGB
    // Note that pFrameRGB is an AVFrame, but AVFrame is a superset
    // of AVPicture
    avpicture_fill((AVPicture *)pFrameRGB, buffer, AV_PIX_FMT_RGB24,
                   pCodecCtx->width, pCodecCtx->height);

    // initialize SWS context for software scaling
    struct SwsContext *sws_ctx = sws_getContext(pCodecCtx->width,
                                                pCodecCtx->height,
                                                pCodecCtx->pix_fmt,
                                                pCodecCtx->width,
                                                pCodecCtx->height,
                                                AV_PIX_FMT_RGB24,
                                                SWS_BILINEAR,
                                                NULL,
                                                NULL,
                                                NULL);

    //read stream packet
    int frameFinished, i = 0;
    AVPacket packet;
    while (av_read_frame(pFormatCtx, &packet) >= 0)
    {
        //It is video stream packet.
        if (packet.stream_index == video_stream)
        {
            // Decode video frame, decode packet to avFrame
            avcodec_decode_video2(pCodecCtx, pFrame, &frameFinished, &packet);

            //show frame type.
            printf("#%d key_frame:%u  pict_type:%c line_size:%d",
                   i, pFrame->key_frame, av_get_picture_type_char(pFrame->pict_type),
                   pFrame->linesize[0]);

            //pict_type None, I, P, B
            if (pFrame->key_frame && pFrame->pict_type == 0)
            {
                //SPS or PPS
                printf(" <---- SPS or PPS");
            }
            printf("\n");

            if (frameFinished)
            {
                // Convert the image from its native format to RGB
                sws_scale(sws_ctx, (uint8_t const *const *)pFrame->data,
                          pFrame->linesize, 0, pCodecCtx->height,
                          pFrameRGB->data, pFrameRGB->linesize);

                // Save the frame to disk
                if (++i <= 5)
                {
                    SaveFrame(pFrameRGB, pCodecCtx->width, pCodecCtx->height,
                              i);
                }
            }
        }
        else
        {
            //not a video frame.
        }

        // Free the packet that was allocated by av_read_frame
        av_free_packet(&packet);
    }

    av_free(buffer);
    av_frame_free(&pFrameRGB);

    // Free the YUV frame
    av_frame_free(&pFrame);

    // Close the codecs
    avcodec_close(pCodecCtx);

    // Close the video file
    avformat_close_input(&pFormatCtx);

    return 0;
}
