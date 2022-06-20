#include "logger.h"
#include "disruptor/ringbuffer.h"
#include "disruptor/shm_manager.h"
#include "disruptor/shm_ringbuffer.h"
#include "disruptor/wait_strategy.h"
#include <iostream>

void test_shm() {
    const key_t key = 10086;
    constexpr size_t size = 8192;
    bool first_created = true;
    disruptor::shm::SharedMemoryManager shm;
    shm.CreateShm(key, size, first_created);
    shm.GetShm(key, size);
    shm.AttachShm();
    shm.DetachShm();
    shm.RemoveShm();
}

typedef struct {
    std::string data;
    size_t th;
} TestBufferData;

void test_ring() {
    disruptor::RingBuffer<TestBufferData> ring;
    ring.SetCapacity(4096);
    ring.SetCapacity(4096 * 8);

    TestBufferData test{};
    test.th = 0;
    test.data = "12345";
    ring[0] = test;
    test.th = 1;
    test.data = "23456";
    ring[1] = test;
    test.th = 2;
    test.data = "34567";
    ring[2] = test;

    std::cout << ring.GetTranslatedIndex(1) << std::endl;
    std::cout << ring.GetTranslatedIndex(4096 * 8 + 5) << std::endl;

    TestBufferData tmp = ring[ring.GetTranslatedIndex(0)];
    std::cout << tmp.th << tmp.data << std::endl;
    tmp = ring[ring.GetTranslatedIndex(1)];
    std::cout << tmp.th << tmp.data << std::endl;
    tmp = ring[ring.GetTranslatedIndex(2)];
    std::cout << tmp.th << tmp.data << std::endl;
}

void test_shm_ring(){
    auto shm_ring = disruptor::SharedMemoryRingBuffer<TestBufferData>(disruptor::wait::BLOCKING_WAIT);
    shm_ring.InitRingBuffer(10086, 8192);
//    shm_ring.print();

    TestBufferData test{};
    shm_ring.set_data(&test);
//    shm_ring.print();

    shm_ring.TerminateRingBuffer();
}

void test_producer(){
    auto shm_ring = disruptor::SharedMemoryRingBuffer<TestBufferData>(disruptor::wait::BLOCKING_WAIT);
    constexpr int shm_size = 8192;
    shm_ring.InitRingBuffer(10086,  shm_size);
    for (int i=0; i<8192*1024; i++){
        TestBufferData test{};
        test.th = i+100;
        test.data = fmt::format("data:{}", i);
        shm_ring.set_data(&test);
    }
    fmt::print("end!");
//    shm_ring.TerminateRingBuffer();
}


int main() {
    create_logger("clogs/shm.log", "info", true, false, false, 1, 1);
    SPDLOG_INFO("start!");
    test_producer();
    SPDLOG_INFO("end!");
    return 0;
}
