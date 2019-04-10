//
// Created by jason on 4/9/19.
//

#include <unistd.h>
#include <time.h>
#include <sys/times.h>
#include <stdio.h>
#include <sys/time.h>
#include "utils.h"

int main(int argc, const char *argv[])
{
    int ret;
    time_t t = time(NULL);
    if (t == (time_t) -1) {
        perror("time");
    } else{
        printf("current time: %ld\n", t);
        printf("the same value: %ld\n", (long) t);
    }

    struct timeval tv;
    ret = gettimeofday(&tv, NULL);
    if (ret == -1) {
        perror("gettimeofday");
    }else{
        printf("current seconds: %ld, current useconds: %ld\n", tv.tv_sec, tv.tv_usec);
    }

    struct timespec tp;
    ret = clock_gettime(CLOCK_REALTIME, &tp);
    if (ret == -1) {
        perror("clock_gettime");
    }else{
        printf("clock = %d, seconds = %ld, nanoseconds = %ld\n", CLOCK_REALTIME, tp.tv_sec, tp.tv_nsec);
    }

    struct tms tms1;
    clock_t clock = times(&tms1);
    if (clock == (clock_t) -1) {
        perror("times");
    } else{
        printf("user time consumed = %ld\n", tms1.tms_utime);
        printf("system time consumed = %ld\n", tms1.tms_stime);
        printf("user time consumed by child = %ld\n", tms1.tms_cutime);
        printf("system time consumed by child = %ld\n", tms1.tms_cstime);
        printf("clock_t = %ld\n", CLOCKS_PER_SEC);
    }

    long hz = get_hz();
    if (hz == -1) {
        printf("get hz failed\n");
    }else{
        printf("hz = %ld\n", hz);
    }
}