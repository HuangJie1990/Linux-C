//
// Created by jason on 4/21/19.
//

#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
/* 缺点:父子进程最后都有init进程回收，无法获取进程退出信息。
 * 更好的方法是创建2个子进程，一个执行ps aux，另一个执行grep，父进程回收子进程资源*/
int main(int argc, const char *argv[]) {

    int ret;
    int fd[2];
    pid_t pid;

    ret = pipe(fd);
    if (ret == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid > 0) {
        /* 父进程关闭读段，重定向标准输出，执行ps aux */
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        execlp("ps", "ps", "aux", NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        /* 子进程关闭写端，重定向标准输入，执行grep bash --color=auto */
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        sleep(100);
        execlp("grep", "grep", "bash", "--color=auto", NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    }
}