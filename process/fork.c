//
// Created by jason on 4/8/19.
// 该demo展示了
// 1.fork函数的调用方法
// 2.如何通过fork返回值区分父进程和子进程
// 3.子进程开始执行的位置
// 4.父子进程的执行顺序
//
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{
    pid_t pid;

    pid = fork();
    if (pid == 0) {
        printf("child process, pid = %ld, ppid = %ld\n", getpid(), getppid());
    }

    if (pid > 0) {
        printf("parent process, pid = %ld\n", getpid());
    }

    if (pid = -1) {
        perror("fork");
        return EXIT_FAILURE;
    }
}