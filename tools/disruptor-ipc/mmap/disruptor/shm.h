//
// Created by 杨东 on 2022/6/20.
//
//http://c.biancheng.net/cpp/html/238.html
//https://blog.csdn.net/takashi77/article/details/108245717

#ifndef DISRUPTOR_IPC_SHM_H
#define DISRUPTOR_IPC_SHM_H
#include "spdlog/spdlog.h"
#include <cerrno>
#include <cstdio>
#include <cstring>
#include <fcntl.h>
#include <string>
#include <sys/ipc.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

namespace disruptor {
#define CHANNEL_LINE_SIZE 64
#define MAX_CONSUMER 32
    typedef struct
    {
        size_t buffer_size;
        size_t total_mem_size;
        std::atomic<size_t> registered_consumer_count;
        std::atomic<int64_t> cursor alignas(CHANNEL_LINE_SIZE);
        std::atomic<int64_t> next alignas(CHANNEL_LINE_SIZE);
        std::atomic<int64_t> array_of_consumer_indexes[MAX_CONSUMER] __attribute__((aligned(CHANNEL_LINE_SIZE)));
        pthread_cond_t cond_var;
        pthread_mutex_t mtx_lock;
    } ShmStoreHeader;

    class SharedMemoryManager {
    private:
        std::string path_;
        size_t size_{};
        void *shm_data_{};

    public:
        SharedMemoryManager() = default;

        ~SharedMemoryManager() = default;

        bool CreateShm(const std::string &path, const size_t &size);

        bool GetShm(const std::string &path, const size_t &size, const bool &read_write);

        bool DetachShm();

        bool RemoveFile();
        static bool RemoveFile(const std::string &path);

        void *GetShmStartAddress() { return shm_data_; }

        auto GetFilePath() { return path_; }
    };

    inline bool SharedMemoryManager::CreateShm(const std::string &path, const size_t &size) {
        constexpr size_t GB = 1024 * 1024 * 1024;
        if (size > GB) {
            size_ = GB;
            SPDLOG_WARN("Mmap max memory size 1GB, size:{} replaced by 1GB.", size);
        } else {
            size_ = size;
        }
        path_ = path;


        // 打开文件
        auto fd = open(path_.c_str(), O_RDWR | O_CREAT, 0666);
        if (fd == -1) {
            SPDLOG_ERROR("Open error: {}", strerror(errno));
            return false;
        } else {
            SPDLOG_DEBUG("Open, fd: {}", fd);
        }

        // 获取文件大小
        struct stat st {};
        if (fstat(fd, &st) == -1) {
            SPDLOG_ERROR("Fstat error: {}", strerror(errno));
            close(fd);
            return false;
        }

        // 改变文件大小
        bool is_init = (st.st_size == 0);
        if (is_init) {
            SPDLOG_INFO("First created, path:{}, size:{}.", path_, size_);
            if (ftruncate(fd, (int64_t) size_) == 0) {
                SPDLOG_DEBUG("Ftruncate, file size:{}", size_);
            } else {
                SPDLOG_ERROR("Failed to ftruncate {}, size:{}, error:{}", path_, size_, strerror(errno));
                return false;
            }
        } else {
            SPDLOG_INFO("File exit,  path:{}, size:{}.", path_, st.st_size);
            size_ = st.st_size;
        }

        shm_data_ = mmap(nullptr, size_, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
        if (shm_data_ == MAP_FAILED) {
            SPDLOG_ERROR("Failed to mmap: {}, size: {}, errno: {}", path_, size_, strerror(errno));
            close(fd);
            return false;
        }
        close(fd);
        return true;
    }

    inline bool SharedMemoryManager::GetShm(const std::string &path, const size_t &size, const bool &read_write) {
        path_ = path;
        size_ = size;

        int fd;
        if (read_write) {
            fd = open(path_.c_str(), O_RDWR, 0666);
        } else {
            fd = open(path_.c_str(), O_RDONLY);
        }

        if (fd == -1) {
            SPDLOG_ERROR("Failed to open: {}, errno: {}", path_, strerror(errno));
            return false;
        }

        // 获取文件大小
        struct stat st {};
        if (fstat(fd, &st) == -1) {
            SPDLOG_ERROR("Failed to fstat: {}, errno: {}", path_, strerror(errno));
            close(fd);
            return false;
        }

        // 检查是否存在文件
        if (st.st_size == 0) {
            SPDLOG_ERROR("File: {} is empty.", path_);
            close(fd);
            return false;
        }

        size_ = st.st_size;
        SPDLOG_INFO("File exit, path:{}, size:{}.", path_, st.st_size);

        if (read_write) {
            shm_data_ = mmap(nullptr, size_, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
        } else {
            shm_data_ = mmap(nullptr, size_, PROT_READ, MAP_PRIVATE, fd, 0);
        }

        if (shm_data_ == MAP_FAILED) {
            SPDLOG_ERROR("Failed to mmap: {}, size: {}, errno: {}", path_, size_, strerror(errno));
            close(fd);
            return false;
        }
        close(fd);
        return true;
    }

    inline bool SharedMemoryManager::DetachShm() {
        if (msync(shm_data_, size_, MS_SYNC) != 0) {
            SPDLOG_ERROR("Failed to msync: {}, size: {}, errno: {}", path_, size_, strerror(errno));
            return false;
        }

        if (munmap(shm_data_, size_) == -1) {
            SPDLOG_ERROR("Failed to munmap: {}, size: {}, errno: {}", path_, size_, strerror(errno));
            return false;
        }
        shm_data_ = {};
        size_ = {};
        return true;
    }

    inline bool SharedMemoryManager::RemoveFile() {
        return RemoveFile(path_);
    }

    inline bool SharedMemoryManager::RemoveFile(const std::string &path) {
        if (remove(path.c_str()) == -1) {
            SPDLOG_ERROR("Failed to remove: {}, errno: {}", path, strerror(errno));
            return false;
        }
        SPDLOG_DEBUG("Remove: {}.", path);
        return true;
    }
}// namespace disruptor

#endif//DISRUPTOR_IPC_SHM_H
