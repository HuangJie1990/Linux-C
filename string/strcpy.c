//
// Created by jason on 4/21/19.
//

#include <string.h>
#include <stdio.h>
#include <malloc.h>

int main(int argc, const char *argv[])
{
    size_t len;
    char *src = "hello, world!";
    char *dest = malloc(20);
    memset(dest, 'a', 19);

    len = strlen(src);

    /* 拷贝时包括\0 */
    dest = strcpy(dest, src);
    printf("%s\n",dest);

    dest[len] = 'a';
    printf("%s\n",dest);

    dest = strncpy(dest, src, strlen(src));
    printf("%s\n",dest);

    dest = strncpy(dest, src, strlen(src) + 1);
    printf("%s\n",dest);

    free(dest);
    return 0;
}