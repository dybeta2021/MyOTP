//
// Created by 稻草人 on 2022/6/19.
//
#include "logger.h"
#include "disruptor/disruptor.h"
#include "disruptor/shm.h"
#include "disruptor/wait_strategy.h"
#include <iostream>


typedef struct {
    std::string data;
    size_t th;
} TestBufferData;


int main() {
    create_logger("clogs/consumer.log", "trace", false, false, false, 1, 1);
    auto shm = disruptor::Disruptor<TestBufferData>(disruptor::wait::BLOCKING_WAIT);
    shm.Init("test.store", 1024*1024*16);

    // 获取当前最新的数据
    const int user_id = 0;
    int64_t user_last_cursor = -1;
    if (!shm.RegisterConsumer(user_id, user_last_cursor)) {
        return 1;
    }
    SPDLOG_DEBUG("user:{}, user_cursor:{}", user_id, user_last_cursor);

    auto ret_idx = shm.WaitFor(user_last_cursor);
    SPDLOG_DEBUG("user:{}, user_cursor:{}，ret_idx:{}", user_id, user_last_cursor, ret_idx);
    do {
        shm.GetData(user_last_cursor);
        shm.CommitRead(user_id, user_last_cursor);
        ret_idx = shm.WaitFor(++user_last_cursor);
        SPDLOG_DEBUG("user:{}, user_cursor:{}，ret_idx:{}", user_id, user_last_cursor, ret_idx);
    } while (user_last_cursor <= ret_idx);
}