//
// Created by yungu on 2022/4/12.
//
#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char **argv)
{
    cpu_set_t cpuset;

    CPU_ZERO(&cpuset);    // 初始化CPU集合，将 cpuset 置为空
    CPU_SET(2, &cpuset);  // 将本进程绑定到 CPU2 上

    // 设置进程的 CPU 亲和性
    if (sched_setaffinity(0, sizeof(cpuset), &cpuset) == -1) {
        printf("Set CPU affinity failed, error: %s\n", strerror(errno));
        return -1;
    }

    return 0;
}

