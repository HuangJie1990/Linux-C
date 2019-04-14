//
// Created by huangjie on 19-4-14.
//

#include <pthread.h>
#include <cstdlib>
#include <cassert>
#include <cstdio>
#include "threadpool.h"

static threadpool_t *pool = nullptr;

void *thread_routine(void *arg) {
    assert(pool != nullptr);

    while (true) {
        pthread_mutex_lock(&pool->mutex);
        //如果任务队列中没有任务项，不销毁线程池，阻塞等待新的任务项
        if (pool->task_count == 0 && !pool->destroy) {
            printf("Thread %ld is waiting!\n", pthread_self());
            pthread_cond_wait(&pool->cond, &pool->mutex);
        }
        if (pool->destroy) {
            printf("***** Thrad pool now has %d threads *****\n", pool->thread_count);
            pthread_mutex_unlock(&pool->mutex);
            printf("Thread %ld is exiting!\n", pthread_self());
            pool->thread_count--;
            pthread_exit(nullptr);
        }
        assert(pool->task_count != 0);
        assert(pool->head != nullptr);

        //从任务队列中取出一个任务执行
        task_t *task_temp = pool->head;
        pool->head = pool->head->next;
        pool->task_count--;
        printf("***** Thread pool now has %d task *****\n", pool->task_count);

        //取出任务项后解锁,执行任务，释放资源
        pthread_mutex_unlock(&pool->mutex);

        (*(task_temp->task_routine))(task_temp->arg);
        free(task_temp);
    }
}

int threadpool_init(const int capacity) {
    int ret;

    pool = (threadpool_t *) malloc(sizeof(threadpool_t));
    assert(pool != nullptr);
    pool->tids = (pthread_t *) malloc(sizeof(pthread_t) * capacity);
    assert(pool->tids != nullptr);

    ret = pthread_mutex_init(&pool->mutex, nullptr);
    if (ret == -1) {
        perror("pthread_mutex_init");
        return -1;
    }

    ret = pthread_cond_init(&pool->cond, nullptr);
    if (ret == -1) {
        perror("pthread_cond_init");
        return -1;
    }

    pool->head = pool->tail = nullptr;
    pool->thread_capacity = capacity;
    pool->task_count = 0;
    pool->thread_count = 0;
    pool->destroy = 0;

    int i;
    for (i = 0; i < pool->thread_capacity; i++) {
        ret = pthread_create(&pool->tids[i], nullptr, thread_routine, nullptr);
        if (ret == -1) {
            perror("pthread_create");
            return -1;
        }
        pool->thread_count++;
        printf("*****Thread pool now has %d threads and tid = %ld *****\n", pool->thread_count, pool->tids[i]);
    }

    return ret;
}

int threadpool_add_task(void *(*func)(void *), void *arg) {
    int ret;
    assert(pool != nullptr);
    //使用传入的任务回调函数和参数组成任务项
    auto *new_task = (task_t *) malloc(sizeof(task_t));
    new_task->task_routine = func;
    new_task->arg = arg;
    new_task->next = nullptr;

    //把任务添加到线程池的任务队列中，首先需要先加锁
    ret = pthread_mutex_lock(&pool->mutex);
    if (ret == -1) {
        perror("pthread_mutex_lock");
        return -1;
    }
    if (pool->head == nullptr) {
        //如果任务队列头节点为空，把新的任务节点添加到头节点
        pool->head = new_task;
    } else {
        //如果任务队列头节点不为空
        pool->tail->next = new_task;
    }
    pool->tail = new_task;
    pool->task_count++;
    printf("***** Thread pool now has %d task *****\n", pool->task_count);
    ret = pthread_mutex_unlock(&pool->mutex);
    if (ret == -1) {
        perror("pthread_mutex_unlock");
        return -1;
    }

    //通知任务线程有新的任务项
    ret = pthread_cond_signal(&pool->cond);
    if (ret == -1) {
        perror("pthread_cond_signal");
        return -1;
    }
    return ret;
}

int threadpool_destroy() {
    assert(pool != nullptr);

    pool->destroy = 1;
    //通知所有线程池线程
    pthread_cond_broadcast(&pool->cond);

    int i;
    for (i = 0; i < pool->thread_capacity; i++) {
        pthread_join(pool->tids[i], nullptr);
    }
    free(pool->tids);
    task_t *temp;
    while (pool->head != nullptr) {
        temp = pool->head;
        pool->head = pool->head->next;
        free(temp);
    }

    pthread_mutex_destroy(&pool->mutex);
    pthread_cond_destroy(&pool->cond);
    free(pool);
    pool = nullptr;
    return 0;
}

void *task_routine(void *arg) {
    auto *i = (int *) arg;
    printf("Thread %ld is process task %d\n", pthread_self(), *i);
    sleep(2);
}

int main(int argc, const char *argv[]) {
    threadpool_init(3);

    auto *task_item = (int *) malloc(sizeof(int) * 10);
    int i;
    for (i = 0; i < 10; i++) {
        task_item[i] = i;
        threadpool_add_task(task_routine, (void *) &task_item[i]);
    }

    sleep(10);
    threadpool_destroy();
    free(task_item);
    return 0;
}
