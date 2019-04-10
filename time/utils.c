//
// Created by jason on 4/9/19.
//

#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <asm/errno.h>
#include <memory.h>
#include <stdio.h>
#include "utils.h"

long get_hz() {
    return sysconf(_SC_CLK_TCK);
}

void force_sleep(unsigned int seconds) {
    while (seconds = sleep(seconds)) { ;
    }
}

void force_nanosleep(struct timespec *req) {
    struct timespec rem, *a = req, *b = &rem;
    while (nanosleep(a, b) && errno == EINTR) {
        struct timespec *tmp;
        tmp = a;
        a = b;
        b = tmp;
    }
}

void force_nanosleep1(struct timespec *const req) {
    struct timespec rem;
    int ret;

    retry:
    ret = nanosleep(req, &rem);
    if (ret) {
        if (errno == EINTR) {
            req->tv_sec = rem.tv_sec;
            req->tv_nsec = rem.tv_nsec;
            goto retry;
        }
    }
}

int posix_timer_create(Timer_handle *handle, posix_timer_cb cbf, union sigval value) {
    int ret = -1;
    struct sigevent sev;
    pthread_mutexattr_t pthread_mutexattr;

    ret = pthread_mutexattr_init(&pthread_mutexattr);
    ret += pthread_mutex_init(&handle->lock, &pthread_mutexattr);

    memset(&sev, 0, sizeof(sev));
    sev.sigev_notify = SIGEV_THREAD;
    sev.sigev_value.sival_int = value.sival_int;
    sev.sigev_value.sival_ptr = value.sival_ptr;
    sev.sigev_notify_function = cbf;
    sev.sigev_notify_attributes = NULL;

    ret += timer_create(CLOCK_REALTIME, &sev, &handle->timer_id);
    if (ret) {
        perror("timer_create");
        pthread_mutex_destroy(&handle->lock);
    }

    pthread_mutexattr_destroy(&pthread_mutexattr);

    return ret;
}

int posix_timer_start(Timer_handle *handle, const struct itimerspec period) {
    int ret = -1;

    pthread_mutex_lock(&handle->lock);
    ret = timer_settime(handle->timer_id, 0, &period, NULL);
    pthread_mutex_unlock(&handle->lock);

    return ret;
}

int posix_timer_stop(Timer_handle *handle) {
    int ret = -1;

    struct itimerspec value= {{0,0},{0,0}};
    pthread_mutex_lock(&handle->lock);
    ret = timer_settime(handle->timer_id, 0, &value, NULL);
    pthread_mutex_unlock(&handle->lock);

    return ret;
}

int posix_timer_delete(Timer_handle *handle) {
    int ret = -1;

    struct itimerspec value={{0,0},{0,0}};
    pthread_mutex_lock(&handle->lock);
    ret = timer_settime(handle->timer_id, 0, &value, NULL);
    ret += timer_delete(handle->timer_id);
    pthread_mutex_unlock(&handle->lock);

    pthread_mutex_destroy(&handle->lock);

    return ret;
}

int posix_timer_info(Timer_handle *handle) {
    int ret = -1;
    
    struct itimerspec value;
    ret = timer_gettime(handle->timer_id, &value);
    if(!ret)
    {
        printf("current sec = %ld, nsec = %ld\n", value.it_value.tv_sec, value.it_value.tv_nsec);
        printf("next sec = %ld, nsec = %ld\n", value.it_interval.tv_sec, value.it_interval.tv_nsec);
    }

    return ret;
}

Timer_handle timerHandle;
