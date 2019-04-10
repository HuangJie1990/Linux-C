//
// Created by jason on 4/8/19.
// 该demo展示了
// 1.如何正确的循环创建子进程
// 2.fork产生的进程之间不共享全局变量
//

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int counter = 200;

int main(int argc, const char *argv[]) {
    int i;
    pid_t pid;

    for (i = 0; i < 3; i++) {
        pid = fork();
        if (pid == 0) {
            printf("child process %d, pid = %d, ppid = %d\n", i, getpid(), getppid());
            break;
        } else if (pid == -1) {
            perror("fork");
        }
    }

//根据i值可以区分父进程和子进程

    if (i == 0) {
        counter += 200;
        printf("pid of first child process is %d\n", getpid());
        printf("--counter = %d\n", counter);
    }

    if (i == 1) {
        counter += 200;
        printf("pid of second child process is %d\n", getpid());
        printf("--counter = %d\n", counter);
    }

    if (i == 2) {
        counter += 200;
        printf("pid of third child process is %d\n", getpid());
        printf("--counter = %d\n", counter);
    }

    if (i == 3) {
        counter += 400;
        printf("pid of parent process is %d\n", getpid());
        printf("--counter = %d\n", counter);
    }
}