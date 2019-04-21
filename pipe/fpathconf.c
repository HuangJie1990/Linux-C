//
// Created by jason on 4/21/19.
//

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
    int fd[2], ret;
    long size;
    
    ret = pipe(fd);
    if (ret) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    size = fpathconf(fd[0], _PC_PIPE_BUF);
    printf("Size of pipe is %ld\n", size);
    printf("fd[0] = %d\n", fd[0]);
    printf("fd[1] = %d\n", fd[1]);

    return 0;
}