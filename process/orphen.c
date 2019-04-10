//
// Created by jason on 4/9/19.
//

#include <stdio.h>
#include <unistd.h>

int main(int argc, const char *argv[]) {
    pid_t pid = fork();

    //子进程一直存活
    if (pid == 0) {
        while (1) {
            printf("child process pid = %d, parent process pid = %d\n", getpid(), getppid());
            sleep(10);
        }
    }else{
        printf("parent process pid = %d, parent process ppid = %d\n", getpid(), getppid());
    }

    return 0;
}