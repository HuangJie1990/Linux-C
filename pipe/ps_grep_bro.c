//
// Created by jason on 4/21/19.
//

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <wait.h>

int main(int argc, const char *argv[]) {
    int ret, i, fd[2], status;
    pid_t pid;

    ret = pipe(fd);
    if (ret == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < 2; i++) {
        pid = fork();
        if (pid == 0) {
            break;
        }
    }

    /* 子进程1关闭读端，重定向标准输出，执行ps aux */
    if (i == 0) {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        execlp("ps", "ps", "aux", NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    /* 子进程2关闭写端，重定向标准输入，执行grep bash */
    if (i == 1) {
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        execlp("grep", "grep", "bash", NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    /* 父进程回收子进程资源 */
    if (i == 2) {
        close(fd[0]);
        close(fd[1]);
        while ((pid = waitpid(-1, &status, 0)) != -1) {
            if (WIFEXITED(status)) {
                printf("Process %d exit with value: %d\n", pid, WEXITSTATUS(status));
            } else if (WIFSIGNALED(status)) {
                printf("Process %d exit by signal: %d\n", pid, WTERMSIG(status));
            }
        }
    }

    return 0;
}