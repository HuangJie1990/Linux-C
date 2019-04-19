//
// Created by jason on 4/15/19.
//

#include <stdio.h>
#include <fcntl.h>
#include <assert.h>
#include <unistd.h>

int main(int argc,const char *argv[])
{
    char buf[512];
    int fd;
    int len;

    if (argc < 2) {
        printf("usage: %s <filepath>\n", argv[0]);
        return -1;
    }

    //以只读方式打开
    fd = open(argv[1], O_RDONLY);
    assert(fd != -1);

    while ((len = read(fd, buf, sizeof(buf))) != 0) {
        if (len == -1) {
            perror("read");
            return -1;
        }
        write(STDOUT_FILENO, buf, (size_t )len);
    }
    return 0;
}