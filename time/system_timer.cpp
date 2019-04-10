//
// Created by jason on 4/10/19.
//

#include <sys/time.h>
#include <cstdio>
#include <iostream>
#include <unistd.h>
#include <csignal>

using namespace std;

void alarm_handler (int signo)
{
    printf("Timer hit!\n");
}
int main () {
    struct itimerval delay = {{1,0},{5,0}};
    int ret;
    signal (SIGALRM, alarm_handler);
    ret = setitimer (ITIMER_REAL, &delay, nullptr);

    while (true) {
        ;
    }
}