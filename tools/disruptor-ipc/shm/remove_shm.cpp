//
// Created by 杨东 on 2022/6/19.
//
#include "disruptor/ipc.h"
#include "disruptor/ringbuffer.h"
#include "disruptor/shm.h"
#include "disruptor/wait_strategy.h"
#include "logger.h"
#include <iostream>


int main() {
    std::cout << "Hello, World!" << std::endl;
    disruptor::shm::SharedMemoryManager client;
    bool is_first = true;
    constexpr int shm_size = 8192;
    client.CreateShm(10086, shm_size, is_first);
    client.DetachShm();
    client.RemoveShm();
    return 0;
}
