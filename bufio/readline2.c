//
// Created by huangjie on 19-4-19.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, const char *argv[])
{
    FILE *stream;
    char *line = NULL;
    size_t len = 0;
    ssize_t n_read;

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

    while ((n_read = getline(&line, &len, stream)) != -1) {
        fwrite(line, sizeof(char), n_read, stdout);
        usleep(500 * 1000);
    }

    free(line);
    fclose(stream);
    exit(EXIT_SUCCESS);
}