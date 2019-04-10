//
// Created by jason on 4/10/19.
//
#include <csignal>
#include <pthread.h>
#include <iostream>
#include <unistd.h>

using namespace std;

void alarm_handle(int signum)
{
    cout << "tid = " << pthread_self() << endl;
}

int main()
{
    cout << "tid = " << pthread_self() << endl;
    signal(SIGALRM, alarm_handle);
    alarm(5);

    pause();
}