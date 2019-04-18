//
// Created by huangjie on 19-4-18.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

int main(int argc, const char *argv[])
{
    FILE *stream;
    char buf[LINE_MAX];
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

    while (fgets(buf, LINE_MAX, stream)) {
        fputs(buf, stdout);
        usleep(200 * 1000);
    }

    if(feof(stream))
    {
        clearerr(stream);
        fclose(stream);
        exit(EXIT_SUCCESS);
    } else{
        printf("Read failed with error num: %d\n", ferror(stream));
        clearerr(stream);
        fclose(stream);
        exit(EXIT_FAILURE);
    }
}