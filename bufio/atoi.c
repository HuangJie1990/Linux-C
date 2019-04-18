//
// Created by huangjie on 19-4-19.
//

#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[]) {
    char buf[2];
    int ascii;

    while (fgets(buf, 2, stdin)) {
        ascii = atoi(buf);
        printf("The ascii code of character %s is %d\n", buf, ascii);
    }

    if (feof(stdin)) {
        printf("End of file\n");
    }
    exit(EXIT_SUCCESS);
}
