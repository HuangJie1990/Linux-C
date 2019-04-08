//
// Created by jason on 4/8/19.
// 该demo展示了
// 1.如何正确的循环创建子进程
//

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[]) {
    int i;
    pid_t pid;

    for (i = 0; i < 5; i++) {
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
        printf("pid of first child process is %d\n", getpid());
    }

    if (i == 5) {
        printf("pid of parent process id is %d\n", getpid());
    }
}