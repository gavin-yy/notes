#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>

#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libswresample/swresample.h>

int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "Usage: test input_file\n");
        exit(1);
    }

    AVFormatContext *fmt_ctx = NULL;

    AVCodec *codec = NULL;
    int ret = 0;
    AVPacket packet;

    // Register all formats and codecs
    av_register_all();

    fmt_ctx = avformat_alloc_context();
    if( !fmt_ctx ) {
        printf("avformat_alloc_context failed\n");
        goto ERR;
    }

    if( avformat_open_input(&fmt_ctx, argv[1], NULL, NULL)) {
        printf("avformat_open_input failed, filename:%s\n", argv[1]);
        goto ERR;
    }

    if( avformat_find_stream_info(fmt_ctx, NULL) < 0) {
        printf("avformat_find_stream_info return error");
        goto ERR;
    }

    //debug output.
    av_dump_format(fmt_ctx, 0, argv[1], 0);

    int stream_index = av_find_best_stream(fmt_ctx, AVMEDIA_TYPE_AUDIO, -1, -1, &codec, 0);
    if( stream_index >= 0  && codec ) {
        printf("Find audio stream index : %d, codec_id:%s \n", stream_index, avcodec_get_name(codec->id) );
    } else {
        printf("avformat_find_stream_info return error, ret=%d", stream_index);
        goto ERR;
    }

    AVCodecParameters *codec_param = fmt_ctx->streams[stream_index]->codecpar;
    if( !codec_param ) {
        printf("codec param in stream is null.\n");
        goto ERR;
    }

    //allocate decoder ctx
    AVCodecContext *ctx2 = avcodec_alloc_context3(codec);
    if( !ctx2 ) {
        printf("avcodec_alloc_context3 failed.\n");
        goto ERR;
    }

    ret = avcodec_parameters_to_context(ctx2, codec_param);
    if( ret < 0 ) {
        printf("avcodec_parameters_to_context failed. ret=%d\n", ret);
        goto ERR;
    }

    ret = avcodec_open2(ctx2, codec, NULL);
    if( ret ) {
         printf("avcodec_open2 failed. ret=%d\n", ret);
        goto ERR;
    }

    //output file.
    char out_filename[128];
    snprintf(out_filename, 128, "%s.pcm", argv[1]);

    FILE *out_fp = fopen(out_filename, "wb");
    if( !out_fp ) {
        printf("Failed to open file to write: %s\n", out_filename);
        goto ERR;
    }

    av_init_packet(&packet);

    uint64_t out_channel_layout = codec_param->channel_layout;
    int out_nb_samples = codec_param->frame_size;
    enum AVSampleFormat out_sample_fmt = AV_SAMPLE_FMT_S16;
    int out_sample_rate = codec_param->sample_rate;
    int out_channels = codec_param->channels;

    //prepare frame.
    AVFrame *frame = av_frame_alloc();
    frame->channels = codec_param->channels;
    frame->format = AV_SAMPLE_FMT_S16;
    frame->nb_samples = codec_param->frame_size;
    av_frame_get_buffer(frame, 0);

    printf("audio frame format: channels=%d nb_samples=%d sample_rate=%d\n", frame->channels, frame->nb_samples, out_sample_rate);

    //
    struct SwrContext *convert_ctx = swr_alloc();
    convert_ctx = swr_alloc_set_opts(convert_ctx, out_channel_layout,
        out_sample_fmt, out_sample_rate,
        codec_param->channel_layout,
        codec_param->format,
        codec_param->sample_rate,
        0,
        NULL );

    swr_init(convert_ctx);

    int buffer_size = av_samples_get_buffer_size(NULL, out_channels, out_nb_samples, out_sample_fmt, 0);

    printf("buffer store out data , size=%d\n", buffer_size);

    uint8_t **data = (uint8_t **)av_calloc(1, sizeof(*data));

    int alloc_size = av_samples_alloc(data, NULL, out_channels, out_nb_samples, out_sample_fmt, 0);

    uint32_t cnt=0;
    while( av_read_frame(fmt_ctx, &packet) >= 0 ) {
        if( packet.stream_index != stream_index ) {
            continue;
        }
        ++cnt;
        printf("read frame #%d , size=%d, ", cnt, packet.size);

        ret = avcodec_send_packet(ctx2, &packet);
        if( ret != 0 ) {
            printf("decode send packet error, ret=%d\n", ret);
            goto ERR;
        }

        while( 1 ) {
            ret = avcodec_receive_frame(ctx2, frame) ;
            if( ret == 0 ) {
                ret = swr_convert(convert_ctx, data, alloc_size, (const uint8_t **)frame->data, frame->nb_samples);
                if( ret < 0 ) {
                    printf("swr_convert err:%d\n", ret);
                } else {
                    printf("write output to file. buffer_size=%d \n", buffer_size);
                    fwrite( data[0], 1, buffer_size, out_fp);
                }
            } else {
                switch(ret) {
                    case AVERROR(EAGAIN):
                        printf("avcodec_receive_frame EAGAIN , ret=%d \n", ret );
                        break;
                    case AVERROR_EOF:
                        printf("avcodec_receive_frame AVERROR_EOF \n");
                        break;
                    case AVERROR_INPUT_CHANGED:
                        printf("avcodec_receive_frame AVERROR_INPUT_CHANGED \n");
                        break;
                    case AVERROR(EINVAL):
                        printf("avcodec_receive_frame EINVAL \n");
                        break;
                    default:
                        printf("avcodec_receive_frame legitimate error, ret=%d, [%s]\n", ret, strerror(AVERROR(ret)) );
                        break;
                }

                break;
            }
        }

        av_packet_unref(&packet);
    }



ERR:
    if( fmt_ctx ) {
        avformat_close_input(&fmt_ctx);
        avformat_free_context(fmt_ctx);
    }

    if( ctx2 ) {
        avcodec_close(ctx2);
        avcodec_free_context(&ctx2);
    }

    if( out_fp ) {
        fclose(out_fp);
    }

    if( frame ) {
        av_frame_free(&frame);
    }

    if( convert_ctx ) {
        swr_free(&convert_ctx);
    }
}

