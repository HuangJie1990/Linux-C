//
// Created by huangjie on 19-4-19.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* 测试数据： period.txt */

int main(int argc, const char *argv[])
{
    FILE *stream;
    char *line = NULL;
    size_t len = 0;
    ssize_t n_read;
    long file_size;

    //检查命令行参数
    if (argc < 2) {
        printf("Usage: %s <file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    stream = fopen(argv[1], "r");
    if (stream == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    /* getdelim and write to stdout without flush */
    printf("******getline and write to stdout without flush\n");
    while ((n_read = getdelim(&line, &len, '\.', stream)) != -1) {
        fwrite(line, sizeof(char), (size_t) n_read, stdout);
        usleep(1000 * 1000);
    }
    if (ferror(stream)) {
        printf("End with error!\n");
        exit(EXIT_FAILURE);
    } else if (feof(stream)) {
        printf("End with eof!\n");
        printf("\n");
    }
    fseek(stream, 0, SEEK_SET);

    /* getdelim and write to stdout with flush */
    printf("******getline and write to stdout without flush\n");
    while ((n_read = getdelim(&line, &len, '\.', stream)) != -1) {
        fwrite(line, sizeof(char), (size_t) n_read, stdout);
        fflush(stdout);
        fsync(fileno(stdout));
        usleep(1000 * 1000);
    }

    if (ferror(stream)) {
        printf("End with error!\n");
        exit(EXIT_FAILURE);
    } else if (feof(stream)) {
        printf("End with eof!\n");
        printf("----------\n");
    }

    fseek(stream, 0, SEEK_SET);

    /* getdelim and write to stderr with flush */
    printf("******getline and write to stderr without flush\n");
    while ((n_read = getdelim(&line, &len, '\.', stream)) != -1) {
        fwrite(line, sizeof(char), (size_t) n_read, stderr);
        usleep(1000 * 1000);
    }

    if (ferror(stream)) {
        printf("End with error!\n");
        exit(EXIT_FAILURE);
    } else if (feof(stream)) {
        printf("End with eof!\n");
        file_size = ftell(stream);
        printf("Size of file is %d\n", (int) file_size);
    }

    free(line);
    fclose(stream);
    exit(EXIT_SUCCESS);
}