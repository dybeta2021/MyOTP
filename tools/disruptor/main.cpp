#include "logger.h"
#include "disruptor.h"
#include "atomic_disruptor.h"
#include <iostream>

typedef struct {
    char data[128];
    size_t th;
} TestBufferData;


int main() {
    bool init_log = ots::utils::create_logger("test.log", "info", false, false, false);
    {
        auto page = disruptor::Page("test.store", true);
        page.GetShm();
        auto file_path = page.GetFilePath();
        auto address = page.GetShmDataAddress();
    }

    {
        auto notebook = disruptor::Notebook<TestBufferData>();
        notebook.Init("test", 1024 * 1024 * 1, true, true);
        SPDLOG_INFO("start.");
        for (auto i = 0; i < 1024 * 1024 * 1; i++) {
            TestBufferData t{};
            auto idx = notebook.ClaimIndex();
            auto tmp = notebook.OpenData(idx);
            tmp->th = i;
            notebook.Commit(idx);
        }
        SPDLOG_INFO("end.");
    }

    {
        auto notebook = disruptor::Notebook<TestBufferData>();
        notebook.Init("test", 1024 * 1024 * 1, false, false);
        SPDLOG_INFO("start.");
        for (auto i = 0; i < 1024 * 1024 * 1; i++) {
            notebook.WaitFor(i);
            auto ret = notebook.GetData(i);
            // std::cout << ret->th << std::endl;
        }
        SPDLOG_INFO("end.");
    }

    {
        auto notebook = disruptor::Notebook<TestBufferData>();
        notebook.Init("test", 1024 * 1024 * 2, true, true);
        SPDLOG_INFO("start.");
        for (auto i = 0; i < 1024 * 1024 * 2; i++) {
            TestBufferData t{};
            auto idx = notebook.ClaimIndex();
            auto tmp = notebook.OpenData(idx);
            tmp->th = i;
            notebook.Commit(idx);
        }
        SPDLOG_INFO("end.");
    }

    {
        auto notebook = disruptor::Notebook<TestBufferData>();
        notebook.Init("test", 1024 * 1024 * 2, false, false);
        SPDLOG_INFO("start.");
        for (auto i = 0; i < 1024 * 1024 * 2; i++) {
            notebook.WaitFor(i);
            auto ret = notebook.GetData(i);
            // std::cout << ret->th << std::endl;
        }
        SPDLOG_INFO("end.");
    }


    {
        auto notebook = disruptor::Notebook<TestBufferData>();
        notebook.Init("test", 1024 * 1024 * 20, true, true);
        SPDLOG_INFO("start.");
        for (auto i = 0; i < 1024 * 1024 * 20; i++) {
            TestBufferData t{};
            auto idx = notebook.ClaimIndex();
            auto tmp = notebook.OpenData(idx);
            tmp->th = i;
//            notebook.Commit(idx);
        }
        SPDLOG_INFO("end.");
    }


    {
        auto notebook = disruptor::Notebook<TestBufferData>();
        notebook.Init("test", 1024 * 1024 * 20, true, true);
        SPDLOG_INFO("start.");
        for (auto i = 0; i < 1024 * 1024 * 20; i++) {
            TestBufferData t{};
            t.th=1;
            notebook.SetData(notebook.ClaimIndex(), &t);
        }
        SPDLOG_INFO("end.");
    }

    {
        auto notebook = disruptor::Notebook<TestBufferData>();
        notebook.Init("test", 1024 * 1024 * 20, false, false);
        SPDLOG_INFO("start.");
        for (auto i = 0; i < 1024 * 1024 * 20; i++) {
            notebook.WaitFor(i);
            auto ret = notebook.GetData(i);
            // std::cout << ret->th << std::endl;
        }
        SPDLOG_INFO("end.");
    }

    std::cout<<1024 * 1024 * 20 / 1.129<<std::endl;
    return 0;
}
