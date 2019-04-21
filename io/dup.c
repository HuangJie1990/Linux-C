//
// Created by jason on 4/21/19.
//

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>

int main(int argc, const char *argv[]){
    int fd;
    ssize_t n;
    char buf[LINE_MAX];

    if (argc < 2) {
        printf("Usage: %s <file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    /* 如果文件不存在，创建文件，文件所有者和组成员可读写，其他用户可读。
     * 以只读方式打开文件 */
    fd = open(argv[1], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
    printf("The fd of \"%s\" is %d\n", argv[1], fd);

    /* 将标准输入写入文件argv[0] */
    close(STDOUT_FILENO);
    dup(fd);
    printf("The fd of \"%s\" is %d after dup\n", argv[1], fd);

    while ((n = read(STDIN_FILENO, buf, LINE_MAX)) > 0) {
        write(STDOUT_FILENO, buf, (size_t) n);
    }

    if (n == 0) {
        printf("EOF\n");
    } else if (n == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}