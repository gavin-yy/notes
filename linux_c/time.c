#include<time.h>
#include <sys/time.h>
#include<stdio.h>
#include <stdlib.h>

void print_tm(struct tm *ptm)
{
    printf("time      :%d-%d-%d %d:%d:%d\n",
        ptm->tm_year+1900,
        ptm->tm_mon + 1,
        ptm->tm_mday,
        ptm->tm_hour,
        ptm->tm_min,
        ptm->tm_sec
    );
}

int main()
{
    time_t current;
    current = time(NULL);
    printf("UTC:%lu\n", current);

    char *TZ = getenv("TZ");
    if( TZ) {
        printf("TZ=%s\n", TZ);
    } else {
        printf("TZ is empty\n");
    }

    struct tm tmr = {0};
    localtime_r(&current, &tmr);
    print_tm(&tmr);

    //https://linux.die.net/man/3/localtime
    //The function acts as if it called tzset(3)
    //and sets the external variables tzname with information about the current timezone
    struct tm *ptm = localtime(&current);
    print_tm(ptm);

    struct tm gmt;
    gmtime_r(&current, &gmt);
    print_tm(&gmt);

    struct timeval tv;
    gettimeofday(&tv, NULL);
    printf("gettimeofday UTC:%lu\n", tv.tv_sec);

    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    printf("clock_gettime UTC:%lu\n", ts.tv_sec);

    return 0;
}

/*result:
yzg@yzg-VirtualBox:~/test$ date "+%F %T"
2021-11-16 22:12:29
yzg@yzg-VirtualBox:~/test$ ./time
UTC:1637071949
time      :2021-11-16 22:12:29
time      :2021-11-16 22:12:29
time      :2021-11-16 14:12:29


$cat /etc/timezone
Asia/Shanghai

$echo $TZ

未设置
*/


delete /etc/timezone

yzg@yzg-VirtualBox:~/test$ ./time
UTC:1637072781
time      :2021-11-16 22:26:21
time      :2021-11-16 22:26:21
time      :2021-11-16 14:26:21    --gmtime_r
gettimeofday UTC:1637072781
clock_gettime UTC:1637072781
yzg@yzg-VirtualBox:~/test$
yzg@yzg-VirtualBox:~/test$ date
Tue 16 Nov 2021 10:26:32 PM CST
yzg@yzg-VirtualBox:~/test$ date -u
Tue 16 Nov 2021 02:26:34 PM UTC

yzg@yzg-VirtualBox:~/test$ timedatectl
               Local time: Tue 2021-11-16 22:28:27 CST
           Universal time: Tue 2021-11-16 14:28:27 UTC
                 RTC time: Wed 2021-11-03 16:49:28
                Time zone: Asia/Shanghai (CST, +0800)
System clock synchronized: no
              NTP service: inactive
          RTC in local TZ: no

source:
https://github.com/systemd/systemd/blob/main/src/timedate/timedatectl.c

```
tz = getenv("TZ");
tzset();
sec = time(NULL);
n = have_time ? strftime(a, sizeof a, "%a %Y-%m-%d %H:%M:%S %Z", localtime_r(&sec, &tm)) : 0;
r = table_add_many(table,
                    TABLE_STRING, "Local time:",
                    TABLE_STRING, n > 0 ? a : "n/a");

n = have_time ? strftime(a, sizeof a, "%a %Y-%m-%d %H:%M:%S UTC", gmtime_r(&sec, &tm)) : 0;
r = table_add_many(table,
                    TABLE_STRING, "Universal time:",
                    TABLE_STRING, n > 0 ? a : "n/a");
```

1.
time()
gettimeofday()
clock_gettime(CLOCK_REALTIME, &ts);
获取的都是UTC时间戳

2. localtime , localtime_r() 转换时都考虑了本地timezone
优先使用TZ环境变量

3. gmtime,gmtime_r() 转换时不考虑时区，标准格林威治时间.