//
// Created by jason on 4/9/19.
// 该demo展示了
// 1.如何使用wait函数等待子进程结束
// 2.如何使用wait函数获取子进程退出状态
// 3.判断子进程退出方式，通过exit或return退出，还是通过信号退出
// 4.获取子进程退出值或被哪个信号打断退出
//

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, const char *argv[])
{
    pid_t pid = fork();
    printf("pid = %d\n", pid);
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        sleep(2);
        printf("child process pid = %d, ppid = %d\n", getpid(), getppid());
        sleep(20);
    } else{
        printf("parent process pid = %d\n", getpid());
        int status;
        pid = wait(&status);
        printf("child process %d exit\n",pid);

        if (WIFEXITED(status)) {
            printf("child process exit value = %d\n", WEXITSTATUS(status));
        }
        if (WIFSIGNALED(status)) {
            printf("child process exit by signal: %d\n", WTERMSIG(status));
        }
    }

    return 9;
}
