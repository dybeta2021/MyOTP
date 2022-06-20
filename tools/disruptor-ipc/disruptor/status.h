//
// Created by 稻草人 on 2022/6/19.
//

#ifndef DISRUPTOR_IPC_STATUS_H
#define DISRUPTOR_IPC_STATUS_H
#include "spdlog/spdlog.h"
#include <cerrno>
#include <cstdio>
#include <cstring>
#include <string>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

namespace disruptor {
#define CHANNEL_LINE_SIZE 64
#define MAX_CONSUMER 32
    typedef struct
    {
        size_t buffer_size;
        size_t total_mem_size;
        std::atomic<size_t> registered_producer_count;
        std::atomic<size_t> registered_consumer_count;
        std::atomic<int64_t> cursor alignas(CHANNEL_LINE_SIZE);
        std::atomic<int64_t> next alignas(CHANNEL_LINE_SIZE);
        std::atomic<int64_t> array_of_consumer_indexes[MAX_CONSUMER] __attribute__((aligned(CHANNEL_LINE_SIZE)));
        pthread_cond_t cond_var;
        pthread_mutex_t mtx_lock;
    } RingBufferStatusOnSharedMemory;
}// namespace disruptor


#endif//DISRUPTOR_IPC_STATUS_H
