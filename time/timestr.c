//
// Created by jason on 4/9/19.
//

#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <assert.h>

int main()
{
    char *str = NULL;

    time_t t = time(NULL);
    struct tm *ptm = localtime(&t);
    if (ptm == NULL) {
        perror("gmtime");
    } else{
        printf("now is %d-%d-%d %d:%d:%d\n", ptm->tm_year + 1900, ptm->tm_mon + 1, ptm->tm_mday, ptm->tm_hour,
               ptm->tm_min, ptm->tm_sec);
    }

    str = asctime(ptm);
    if (str == NULL) {
        perror("asctime");
    } else{
        printf("now is %s\n", str);
    }

    time_t s = mktime(ptm);
    printf("t = %ld, s = %ld\n", t, s);

    return 0;
}