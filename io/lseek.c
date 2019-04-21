//
// Created by jason on 4/21/19.
//

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <assert.h>
#include <string.h>

int main(int argc, const char *argv[]) {
    int ret, fd;
    off_t offset;
    ssize_t n;
    const char *buf = "hello, world!";

    if (argc < 2) {
        printf("Usage: %s <file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    ret = access(argv[1], F_OK);
    if (ret) {
        printf("%s does not exit, it will be created\n", argv[1]);
    } else {
        printf("%s exits\n", argv[1]);
    }

    fd = open(argv[1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    offset = lseek(fd, 0, SEEK_END);
    if (offset == (off_t) -1) {
        perror("lseek");
        exit(EXIT_FAILURE);
    } else {
        printf("Length of file %s is %d\n", argv[1], (int) offset);
    }

    /* 到达文件EOF之后
     * 读操作返回-1
     * 写操作扩大文件，新旧长度之间填充0
     * 没有写操作不影响文件大小 */
    offset = lseek(fd, 1, SEEK_CUR);
    if (offset == (off_t) -1) {
        perror("lseek");
        exit(EXIT_FAILURE);
    } else {
        printf("jump after the end of file, and current position is %d\n", (int) offset);
    }

    offset = lseek(fd, 0, SEEK_END);

    offset = lseek(fd, 0, SEEK_SET);
    assert(offset == (off_t) 0);
    printf("jump to head of file\n");

    /* 新位置在文件头之前都会失败 */
//    offset = lseek(fd, -2, SEEK_CUR);
//    assert(offset!=(off_t)-1);

    offset = lseek(fd, 0, SEEK_END);
    printf("jumo to end of file\n");

    offset = lseek(fd, 100, SEEK_CUR);
    printf("jump to 100 bytes after end of file\n");

    n = write(fd, buf, strlen(buf));
    printf("write %zd bytes to file\n", n);

    offset = lseek(fd, 0, SEEK_END);
    printf("jumo to end of file\n");
    printf("length of file if %zd\n", offset);

    return 0;
}