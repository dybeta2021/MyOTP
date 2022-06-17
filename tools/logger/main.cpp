#include "logger.h"
#include <iostream>

void test_start(){
    const std::string log_file = "clogs/test.log";
    const std::string level = "info";
    const bool use_async = true;
    const bool show_use_level = true;
    const bool use_format = true;
    const int flush_policy = 1;
    const int thread_count = 1;

    create_logger(log_file, level, use_async, show_use_level, use_format, flush_policy, thread_count);
    SPDLOG_TRACE("Trace from SpdLog!");
    SPDLOG_DEBUG("Debug from SpdLog!");
    SPDLOG_INFO("Info from SpdLog!");
    SPDLOG_WARN("Warn from SpdLog!");
    SPDLOG_ERROR("Error from SpdLog!");
    SPDLOG_CRITICAL("Critical from SpdLog!");
}

// 定时推送
void test_flush_policy(){
    const std::string log_file = "clogs/test.log";
    const std::string level = "info";
    const bool use_async = true;
    const bool show_use_level = true;
    const bool use_format = true;
    const int flush_policy = 5;
    const int thread_count = 1;

    create_logger(log_file, level, use_async, show_use_level, use_format, flush_policy, thread_count);
    SPDLOG_TRACE("Trace from SpdLog!");
    SPDLOG_DEBUG("Debug from SpdLog!");
    SPDLOG_INFO("Info from SpdLog!");
    SPDLOG_WARN("Warn from SpdLog!");
    SPDLOG_ERROR("Error from SpdLog!");
    SPDLOG_CRITICAL("Critical from SpdLog!");
}

// 多线程，乱序
void test_thread_count(){
    const std::string log_file = "clogs/test.log";
    const std::string level = "info";
    const bool use_async = true;
    const bool show_use_level = true;
    const bool use_format = true;
    const int flush_policy = 5;
    const int thread_count = 5;

    create_logger(log_file, level, use_async, show_use_level, use_format, flush_policy, thread_count);
    SPDLOG_TRACE("Trace from SpdLog!");
    SPDLOG_DEBUG("Debug from SpdLog!");
    SPDLOG_INFO("Info from SpdLog!");
    SPDLOG_WARN("Warn from SpdLog!");
    SPDLOG_ERROR("Error from SpdLog!");
    SPDLOG_CRITICAL("Critical from SpdLog!");
}

int main() {
//    std::cout << "test_start" << std::endl;
//    test_start();

    std::cout << "test_thread_count" << std::endl;
    test_thread_count();
    return 0;
}
