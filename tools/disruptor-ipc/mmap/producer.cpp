#include "logger.h"
#include "disruptor/shm.h"
#include "disruptor/wait_strategy.h"
#include "disruptor/disruptor.h"
#include <iostream>


typedef struct {
    std::string data;
    size_t th;
} TestBufferData;


void test_producer(){
    auto shm = disruptor::Disruptor<TestBufferData>(disruptor::wait::BLOCKING_WAIT);
    shm.Init("test.store", 1024*1024*16);


    SPDLOG_INFO("insert rows: {}", 1024*1024*16);
    SPDLOG_INFO("start!");
    for (int i=0; i<1024*1024*16; i++){
        auto idx = shm.ClaimIndex();
        auto test = shm.CreateData(idx);
        test->th = i+100;
        test->data = fmt::format("data:{}", i);
        shm.Commit(idx);
    }
    SPDLOG_INFO("end!");
}


int main() {
    create_logger("clogs/shm.log", "info", false, false, false, 1, 1);    SPDLOG_INFO("start!");
    test_producer();

    return 0;
}
