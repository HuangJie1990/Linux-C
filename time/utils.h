//
// Created by jason on 4/9/19.
//

#ifndef LINUXSP_UTILS_H
#define LINUXSP_UTILS_H

#include <time.h>
#include <pthread.h>
#include <signal.h>

#ifdef __plusplus
extern "C" {
#endif

long get_hz();

void force_sleep(unsigned int seconds);

void force_nanosleep(struct timespec *req);

void force_nanosleep1(struct timespec *req);

typedef struct {
    timer_t timer_id;
    pthread_mutex_t lock;
} Timer_handle;

typedef void (*posix_timer_cb)(union sigval value);

int posix_timer_create(Timer_handle *handle, posix_timer_cb cbf, union sigval value);

int posix_timer_start(Timer_handle *handle, struct itimerspec period);

int posix_timer_stop(Timer_handle *handle);

int posix_timer_delete(Timer_handle *handle);

int posix_timer_info(Timer_handle *handle);

#ifdef __cpluscplus
}
#endif
#endif //LINUXSP_UTILS_H
