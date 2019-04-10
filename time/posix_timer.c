//
// Created by jason on 4/10/19.
//

#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <signal.h>
#include <ctype.h>
#include "utils.h"

void cbf(union sigval value) {
    printf("tid = %ld\n", pthread_self());
    printf("value = %d\n", value.sival_int);
}

extern Timer_handle timerHandle;

int main() {
    int ret;
    char ch;
    struct itimerspec period = {{1, 0},
                                {1, 0}};
    union sigval value = {.sival_int=10};

    printf("tid = %ld\n", pthread_self());

    while (1) {
        ch = getchar();
        switch (toupper(ch)) {
            case 'C':
                ret = +posix_timer_create(&timerHandle, cbf, value);
                if (ret) {
                    return ret;
                }
                break;
            case 'B':
                ret += posix_timer_start(&timerHandle, period);
                if (ret) {
                    return ret;
                }
                break;
            case 'S':
                ret = +posix_timer_stop(&timerHandle);
                if (ret) {
                    return ret;
                }
                break;
            case 'E':
                ret = +posix_timer_delete(&timerHandle);
                return ret;
        }
    }
}