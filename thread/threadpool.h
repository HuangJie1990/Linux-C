//
// Created by huangjie on 19-4-14.
//

#ifndef LINUXSP_THREADPOOL_H
#define LINUXSP_THREADPOOL_H

#include <zconf.h>

typedef struct task {
    void *(*task_routine)(void *);

    void *arg;
    struct task *next;
} task_t;

typedef struct threadpool {
    pthread_mutex_t mutex;
    pthread_cond_t cond;

    task_t *head;
    task_t *tail;

    pthread_t *tids;        //线程号集合
    int thread_capacity;    //线程池线程容量
    int thread_count;       //线程池当前线程数量
    int task_count;         //任务队列数量

    int destroy;            //是否销毁线程池
} threadpool_t;

/**
 * 初始化线程池
 * @param capacity [IN]线程池线程容量
 * @return 成功返回0并初始化pool所指向的线程池对象，失败返回-1
 */
int threadpool_init(int capacity);

/**
 * 添加任务项
 * @param arg  [IN]任务项回调函数的参数
 * @return 成功返回0，失败返回-1
 */
int threadpool_add_task(void *(*func)(void *),void *arg);

/**
 * 销毁线程池
 * @return 成功返回0，失败返回-1
 */
int threadpool_destroy();

#endif //LINUXSP_THREADPOOL_H
