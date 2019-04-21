//
// Created by jason on 4/21/19.
//

#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>

int main(int argc, const char *argv[])
{
    int ret,fd;
    off_t length;
    void *ptr;

    if (argc < 2) {
        printf("Usage: %s <file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    ret = access(argv[1], F_OK);
    if (ret == -1) {
        perror("access");
        exit(EXIT_FAILURE);
    }

    fd = open(argv[1], O_RDWR);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    length = lseek(fd, 0, SEEK_END);

    ptr = mmap(NULL, (size_t) length, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }
    ptr++;

    printf((char *) ptr);

    ret = munmap(ptr, (size_t) length);
    if (ret == -1) {
        perror("munmap");
        exit(EXIT_FAILURE);
    }
    close(fd);
    return 0;
}