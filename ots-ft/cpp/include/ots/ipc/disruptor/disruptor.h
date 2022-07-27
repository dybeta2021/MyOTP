//
// Created by 稻草人 on 2022/6/19.
//
// multi-producer in one process， and multi-consumer in another process.
//

#ifndef DISRUPTOR_IPC_DISRUPTOR_H
#define DISRUPTOR_IPC_DISRUPTOR_H

//#define USE_SPSC_SPMC
#include "ring.h"
#include "shm.h"
#include "wait_strategy.h"
#include <atomic>
#include <cinttypes>
#include <iostream>
#include <sys/stat.h>
#include <thread>
#include <vector>

namespace disruptor {
    template<typename T>
    class Disruptor {
    private:
        wait::WaitStrategy *wait_strategy_;
        wait::ENUM_WAIT_STRATEGY wait_strategy_type_;
        size_t buffer_size_{};
        RingBuffer<T *> ring_buffer_;
        size_t total_memory_size_{};
        ShmStoreHeader *shm_hdr_;
        void *shm_data_hdr_{};
        SharedMemoryManager shm_;
        int item_size;

    public:
        explicit Disruptor(wait::ENUM_WAIT_STRATEGY wait_strategy);

        ~Disruptor();

        bool Terminate();

        void NotifyAll();

        bool Init(const std::string &path, const size_t &size);

        bool RegisterConsumer(const int &id, int64_t &index_of_customer);

        //producer
        int64_t ClaimIndex();

        bool SetData(const int64_t &index, T *data);

        bool Commit(const int64_t &index);

        // zero copy
        T *CreateData(const int64_t &index);

        //consumer
        int64_t WaitFor(const int64_t &index);

        T *GetData(const int64_t &index);

        bool CommitRead(const int &user_id, const int64_t &index);

    private:
        int64_t GetMinIndexOfConsumers();

    public:
        bool set_data(T *data) {
            const auto idx = ClaimIndex();
            const bool ret = SetData(idx, data);
            if (ret) {
                return Commit(idx);
            }
            return ret;
        }

        int64_t get_translated_index(int64_t sequence) {
            return ring_buffer_.GetTranslatedIndex(sequence);
        }
    };

    template<typename T>
    inline Disruptor<T>::Disruptor(wait::ENUM_WAIT_STRATEGY wait_strategy) {
        shm_hdr_ = nullptr;
        wait_strategy_type_ = wait_strategy;
        wait_strategy_ = nullptr;
        item_size = sizeof(T);
    }

    template<typename T>
    inline Disruptor<T>::~Disruptor() {
        if (wait_strategy_) {
            delete wait_strategy_;
            wait_strategy_ = nullptr;
        }

        if (!shm_.DetachShm()) {
            SPDLOG_ERROR("Error");
        }
    }

    template<typename T>
    inline bool Disruptor<T>::Terminate() {
        if (!shm_.DetachShm()) {
            SPDLOG_ERROR("Error");
            return false;
        }
        return true;
    }


    template<typename T>
    inline bool Disruptor<T>::Init(const std::string &path, const size_t &size) {
        if (size <= 0) {
            SPDLOG_ERROR("Invalid size : {}", size);
            return false;
        }

        if (!ring_buffer_.SetCapacity(size)) {
            SPDLOG_ERROR("Invalid size : {}", size);
            return false;
        } else {
            buffer_size_ = size;
        }

        //shared memory consists of : ShmStoreHeader + actual data
        total_memory_size_ = (int64_t) sizeof(ShmStoreHeader) + (int64_t) (sizeof(T) * size);

        // 判断文件是否存在
        struct stat st{};
        if (stat(path.c_str(), &st) == 0) {
            SPDLOG_INFO("File: {} exits.", path);
            if (!shm_.GetShm(path, total_memory_size_, true)) {
                return false;
            }
            shm_hdr_ = (ShmStoreHeader *) shm_.GetShmStartAddress();
            if (shm_hdr_ == nullptr) {
                SPDLOG_CRITICAL("MMAP memory header address error!");
                return false;
            }
        } else {
            SPDLOG_INFO("Create file: {}.", path);
            if (!shm_.CreateShm(path, total_memory_size_)) {
                return false;
            }
            shm_hdr_ = (ShmStoreHeader *) shm_.GetShmStartAddress();
            if (shm_hdr_ == nullptr) {
                SPDLOG_CRITICAL("MMAP memory header address error!");
                return false;
            }

            shm_hdr_->cursor.store(-1);
            shm_hdr_->next.store(-1);
            shm_hdr_->registered_consumer_count.store(0);

            for (auto &array_of_consumer_index: shm_hdr_->array_of_consumer_indexes) {
                array_of_consumer_index = -1;
            }

            //for blocking wait strategy : shared mutex, shared cond var
            pthread_mutexattr_t mutexAttr;
            pthread_mutexattr_init(&mutexAttr);
            pthread_mutexattr_setpshared(&mutexAttr, PTHREAD_PROCESS_SHARED);
            pthread_mutex_init(&shm_hdr_->mtx_lock, &mutexAttr);

            pthread_condattr_t condAttr;
            pthread_condattr_init(&condAttr);
            pthread_condattr_setpshared(&condAttr, PTHREAD_PROCESS_SHARED);
            pthread_cond_init(&shm_hdr_->cond_var, &condAttr);
        }

        SPDLOG_INFO("Shared memory initialization.");
        shm_data_hdr_ = (char *) shm_.GetShmStartAddress() + sizeof(ShmStoreHeader);
        for (int i = 0; i < size; i++) {
            ring_buffer_[i] = (T *) ((char *) shm_data_hdr_ + (sizeof(T) * i));
        }
        shm_hdr_->buffer_size = size;
        shm_hdr_->total_mem_size = total_memory_size_;

        //wait strategy
        if (wait_strategy_type_ == wait::BLOCKING_WAIT) {
            SPDLOG_INFO("Wait Strategy :BLOCKING_WAIT");
            wait_strategy_ = new wait::BlockingWaitStrategy(shm_hdr_);
        } else if (wait_strategy_type_ == wait::YIELDING_WAIT) {
            SPDLOG_INFO("Wait Strategy :YIELDING_WAIT");
            wait_strategy_ = new wait::YieldingWaitStrategy(shm_hdr_);
        } else if (wait_strategy_type_ == wait::SLEEPING_WAIT) {
            SPDLOG_INFO("Wait Strategy :SLEEPING_WAIT");
            wait_strategy_ = new wait::SleepingWaitStrategy(shm_hdr_);
        } else {
            SPDLOG_ERROR("Error: Invalid Wait Strategy: {}", wait_strategy_type_);
            return false;
        }

        return true;
    }

    template<typename T>
    inline int64_t Disruptor<T>::GetMinIndexOfConsumers() {
        int64_t min_index = INT64_MAX;
        bool is_found = false;
        for (size_t i = 0; i < shm_hdr_->registered_consumer_count; i++) {
            int64_t index = shm_hdr_->array_of_consumer_indexes[i];
            if (index < min_index) {
                min_index = index;
                is_found = true;
            }
        }
        if (!is_found) {
            return 0;
        }
        return min_index;
    }

    // 一个进程写入，单进程内多线程因为原子操作无需区分写入线程
    template<typename T>
    inline int64_t Disruptor<T>::ClaimIndex() {
        // fetch_add, Adds val to the contained value and returns the value it had immediately before the operation.
        auto nNextSeqForClaim = shm_hdr_->next.fetch_add(1) + 1;

        int64_t wrapPoint = nNextSeqForClaim - buffer_size_;
        do {
            int64_t gatingSequence = GetMinIndexOfConsumers();
            if (wrapPoint >= gatingSequence) {
                // std::this_thread::yield tells the implementation to reschedule the execution of threads,
                // that should be used in a case where you are in a busy waiting state, like in a thread pool:
                std::this_thread::yield();
                continue;
            } else {
                break;
            }
        } while (true);

        SPDLOG_DEBUG("nNextSeqForClaim:{}, wrapPoint:{}, buffer_size_:{}, gatingSequence:{}, next:{}, cursor:{}",
                     nNextSeqForClaim, wrapPoint, buffer_size_, GetMinIndexOfConsumers(), shm_hdr_->next,
                     shm_hdr_->cursor);
        return nNextSeqForClaim;
    }

    template<typename T>
    inline bool Disruptor<T>::SetData(const int64_t &index, T *data) {
        memcpy(ring_buffer_[index], data, item_size);
        return true;
    }

    template<typename T>
    inline bool Disruptor<T>::Commit(const int64_t &index) {
#ifdef USE_SPSC_SPMC
        const int64_t expected = index - 1;
        shm_hdr_->cursor = index;
        return true;
#else
        const int64_t expected = index - 1;
        while (true) {
            if (shm_hdr_->cursor == expected) {
                shm_hdr_->cursor = index;
                break;
            }
            std::this_thread::yield();
        }
        wait_strategy_->NotifyAllWhenBlocking();//blocking wait strategy only.
        return true;
#endif
    }

    template<typename T>
    inline bool Disruptor<T>::RegisterConsumer(const int &id, int64_t &index_of_customer) {
        SPDLOG_DEBUG("id:{}, index_of_customer:{}", id, index_of_customer);
        if (id >= MAX_CONSUMER) {
            SPDLOG_ERROR("Customer id 0~{}.", MAX_CONSUMER - 1);
            return false;
        }

        SPDLOG_DEBUG("id:{}, array_of_consumer_indexes:{}", id, shm_hdr_->array_of_consumer_indexes[id]);
        if (shm_hdr_->array_of_consumer_indexes[id] == -1) {
            shm_hdr_->registered_consumer_count++;
            if (shm_hdr_->registered_consumer_count >= MAX_CONSUMER) {
                SPDLOG_ERROR("Exceeds MAX_CONSUMER : {}", MAX_CONSUMER);
                return false;
            }
            if (shm_hdr_->cursor >= 0) {
                SPDLOG_INFO("cursor:{} >=0", shm_hdr_->cursor);
                shm_hdr_->array_of_consumer_indexes[id] = shm_hdr_->cursor.load();
                SPDLOG_INFO("user cursor set {}.", shm_hdr_->array_of_consumer_indexes[id]);
            } else {
                SPDLOG_INFO("user cursor set 0.");
                shm_hdr_->array_of_consumer_indexes[id] = 0;
            }
            index_of_customer = shm_hdr_->array_of_consumer_indexes[id];
        } else {
            // note: blocking made ring-buffer start_idx <= consumer cursor
            // user client no need keep user_cursor
            index_of_customer = shm_hdr_->array_of_consumer_indexes[id] + 1;
        }
        SPDLOG_INFO("USAGE_CONSUMER ID: {}, index: {}", id, index_of_customer);
        return true;
    }

    template<typename T>
    inline int64_t Disruptor<T>::WaitFor(const int64_t &index) {
        int64_t nCurrentCursor = shm_hdr_->cursor.load();
        if (index > nCurrentCursor) {
            return wait_strategy_->Wait(index);
        } else {
            return nCurrentCursor;
        }
    }

    template<typename T>
    inline T *Disruptor<T>::GetData(const int64_t &index) {
        return ring_buffer_[index];
    }

    template<typename T>
    inline bool Disruptor<T>::CommitRead(const int &user_id, const int64_t &index) {
        shm_hdr_->array_of_consumer_indexes[user_id] = index;
        return true;
    }

    template<typename T>
    inline void Disruptor<T>::NotifyAll() {
        wait_strategy_->NotifyAllWhenBlocking();//blocking wait strategy only.
    }

    // zero copy
    template<typename T>
    inline T *Disruptor<T>::CreateData(const int64_t &index) {
        return &(*ring_buffer_[index]);
    }


}// namespace disruptor

#endif//DISRUPTOR_IPC_DISRUPTOR_H
