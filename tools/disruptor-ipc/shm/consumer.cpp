//
// Created by 稻草人 on 2022/6/19.
//
#include "disruptor/ipc.h"
#include "disruptor/shm.h"
#include "disruptor/wait_strategy.h"
#include "logger.h"
#include <iostream>

typedef struct {
    std::string data;
    size_t th;
} TestBufferData;


int main() {
    create_logger("clogs/shm.log", "trace", false, false, false, 1, 1);

    auto shm_ring = disruptor::RingIPC<TestBufferData>(disruptor::wait::BLOCKING_WAIT);
    constexpr int shm_size = 8192;
    shm_ring.InitRingBuffer(10086,  shm_size);

    // 获取当前最新的数据
    const int user_id = 0;
    int64_t user_last_cursor = -1;
    if (!shm_ring.RegisterConsumer(user_id, user_last_cursor)) {
        return 1;
    }
    auto ret_idx = shm_ring.WaitFor(user_last_cursor);
    SPDLOG_INFO("user:{}, user_cursor:{}，ret_idx:{}\n", user_id, user_last_cursor, ret_idx);

    do {
//        if(user_last_cursor%1024==0){
//            fmt::print("user:{}, user_cursor:{}，ret_idx:{}\n", user_id, user_last_cursor, ret_idx);
//        }
        shm_ring.GetData(user_last_cursor);
        shm_ring.CommitRead(user_id, user_last_cursor);
        ret_idx = shm_ring.WaitFor(++user_last_cursor);
    } while (user_last_cursor <= ret_idx);
}