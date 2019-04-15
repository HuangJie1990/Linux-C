//
// Created by jason on 4/11/19.
//

#include <cstdlib>
#include <iostream>
#include <malloc.h>

using namespace std;

int main() {
    int *p;
    p = (int *) malloc(sizeof(int));
    *p = 100;
    printf("p = %ld, p = %p, *p = %d\n", p, p, *p);

    free(p);
    //free只标记ptr指向的内存可重用，ptr指向的内存区域不变，存储的内容也不一定变化
    //仍然可以访问，但不安全
    //最好加上ptr=NULL，防止误访问

//    p = nullptr;
//    printf("p = %p, *p = %d\n", p, *p);
    malloc_stats();
}