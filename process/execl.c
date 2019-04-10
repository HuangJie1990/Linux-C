//
// Created by jason on 4/9/19.
//

#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{
    //父进程
    int i;
    int ret;
    for (i = 0; i < 10; i++) {
        printf("parent i = %d\n", i);
    }

    //创建子进程
    pid_t pid = fork();
    assert(pid != -1);

    if (pid == 0) {
        //使用程序ls替换子进程的地址空间
        execl("/bin/ls", "ls", "-lh", NULL);
        perror("execl");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < 10; i++) {
        printf("parent i = %d\n", i);
        usleep(500);
    }
}