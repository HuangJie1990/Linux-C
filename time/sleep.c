//
// Created by jason on 4/10/19.
//

#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>

int main()
{
    int ret;
    struct timespec start,end;

    /* 秒级精度睡眠 */
    clock_gettime(CLOCK_REALTIME, &start);
    sleep(5);
    clock_gettime(CLOCK_REALTIME, &end);

    printf("sleep %ld seconds and %ld nano seconds\n", end.tv_sec - start.tv_sec, end.tv_nsec - start.tv_nsec);

    /* 微秒级精度睡眠 */
    clock_gettime(CLOCK_REALTIME, &start);
    usleep(5000 * 1000);
    clock_gettime(CLOCK_REALTIME, &end);

    printf("sleep %ld seconds and %ld nano seconds\n", end.tv_sec - start.tv_sec, end.tv_nsec - start.tv_nsec);

    /* 纳秒级精度睡眠 */
    struct timespec req = {
            .tv_sec = 0,
            .tv_nsec = 1000
    };
    clock_gettime(CLOCK_REALTIME, &start);
    nanosleep(&req, NULL);
    clock_gettime(CLOCK_REALTIME, &end);

    printf("sleep %ld seconds and %ld nano seconds\n", end.tv_sec - start.tv_sec, end.tv_nsec - start.tv_nsec);

    /* 纳秒级精度睡眠 */
    clock_gettime(CLOCK_REALTIME, &start);
    clock_nanosleep(CLOCK_REALTIME, 0, &req, NULL);
    clock_gettime(CLOCK_REALTIME, &end);

    printf("sleep %ld seconds and %ld nano seconds\n", end.tv_sec - start.tv_sec, end.tv_nsec - start.tv_nsec);
}