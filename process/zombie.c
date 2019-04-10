//
// Created by jason on 4/9/19.
//

#include <unistd.h>
#include <stdio.h>
#include <assert.h>

int main(int argc, const char *argv[])
{
    pid_t pid = fork();
    assert(pid != -1);

    //子进程打印自己pid和ppid后死亡
    if (pid == 0) {
        printf("child process pid = %d, ppid = %d\n", getpid(), getppid());
    }

    //父进程一直存活
    if (pid > 0)
    {
        while (1) {
            sleep(1);
        }
    }

    //进程退出
    return 0;
}