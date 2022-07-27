//
// Created by 稻草人 on 2022/6/19.
//
#include "logger.h"
#include "disruptor/disruptor.h"
#include <iostream>

typedef struct {
    std::string data;
    size_t th;
} TestBufferData;

void test_mmap() {
    disruptor::SharedMemoryManager shm;
    std::string path = "tmp.store";
    shm.RemoveFile(path);
    size_t size = 1024 * 1024 * 1024 + 1;
    shm.CreateShm(path, size);
    shm.GetShm(path, size, true);
    shm.GetShm(path, size, false);
    shm.DetachShm();
    shm.RemoveFile();
    shm.GetShm(path, size, true);
    shm.GetShm(path, size, false);
}

void test_ring() {
    disruptor::RingBuffer<TestBufferData> ring;
    ring.SetCapacity(4099);
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


int main() {
    std::cout << "Hello, World!" << std::endl;
    create_logger("clogs/shm.log", "trace", false, true, false, 1, 1);

    std::cout << sizeof(TestBufferData) * 1024 + sizeof(disruptor::ShmStoreHeader) << std::endl;
    auto shm = disruptor::Disruptor<TestBufferData>(disruptor::wait::BLOCKING_WAIT);
    shm.Init("test.store", 1024);
    SPDLOG_DEBUG("Init.");

//    {
//        TestBufferData test{};
//        const auto idx = shm.ClaimIndex();
//        SPDLOG_DEBUG("ClaimIndex:{}", idx);
//
//        const bool ret = shm.SetData(idx, &test);
//        SPDLOG_DEBUG("SetData:{}", ret);
//
//        const bool commit = shm.Commit(idx);
//        SPDLOG_DEBUG("Commit:{}", commit);
//    }

    {
        const auto idx = shm.ClaimIndex();
        SPDLOG_DEBUG("ClaimIndex:{}", idx);
        auto *data = shm.CreateData(idx);
        data->data = "abcdedf";
        const bool commit = shm.Commit(idx);
        SPDLOG_DEBUG("Commit:{}", commit);
    }

    {
        // 获取当前最新的数据
        const int user_id = 0;
        int64_t user_last_cursor = -1;
        if (!shm.RegisterConsumer(user_id, user_last_cursor)) {
            return 1;
        }

        auto ret_idx = shm.WaitFor(user_last_cursor);
        SPDLOG_DEBUG("user:{}, user_cursor:{}，ret_idx:{}", user_id, user_last_cursor, ret_idx);
        do {
            auto ret = shm.GetData(user_last_cursor);
            std::cout<<ret->data<<std::endl;
            shm.CommitRead(user_id, user_last_cursor);
            ret_idx = shm.WaitFor(++user_last_cursor);
            SPDLOG_DEBUG("user:{}, user_cursor:{}，ret_idx:{}", user_id, user_last_cursor, ret_idx);
        } while (user_last_cursor <= ret_idx);


    }




    return 0;
}
