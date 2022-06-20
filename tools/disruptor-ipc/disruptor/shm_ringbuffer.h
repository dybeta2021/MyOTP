//
// Created by 稻草人 on 2022/6/19.
//

#ifndef DISRUPTOR_IPC_SHM_RINGBUFFER_H
#define DISRUPTOR_IPC_SHM_RINGBUFFER_H
#include "status.h"
#include <atomic>
#include <cinttypes>
#include <iostream>
#include <thread>
#include <vector>

#include "ringbuffer.h"
#include "shm_manager.h"
#include "wait_strategy.h"

namespace disruptor {
    template<typename T>
    class SharedMemoryRingBuffer {
    private:
        size_t buffer_size_{};
        size_t total_mem_size_{};
        wait::WaitStrategy *wait_strategy_;
        wait::ENUM_WAIT_STRATEGY wait_strategy_type_;
        RingBufferStatusOnSharedMemory *status_;
        shm::SharedMemoryManager shm_manager_;
        RingBuffer<T *> ring_buffer_;
        int item_size;

    public:
        explicit SharedMemoryRingBuffer(wait::ENUM_WAIT_STRATEGY wait_strategy);
        ~SharedMemoryRingBuffer();

        bool InitRingBuffer(const key_t &shm_key, int size);
        void ResetRingBufferState();
        bool TerminateRingBuffer();
        bool SetData(const int64_t &index, T *data);
        T *GetData(const int64_t &index);

        bool RegisterConsumer(const int &id, int64_t &index_of_customer);

        int64_t GetTranslatedIndex(int64_t sequence) {
            return ring_buffer_.GetTranslatedIndex(sequence);
        }

        void NotifyAll();

        //producer
        int64_t ClaimIndex();
        bool Commit(const int64_t &index);

        //consumer
        int64_t WaitFor(const int64_t &index);

        bool CommitRead(const int &user_id, const int64_t &index) {
            status_->array_of_consumer_indexes[user_id] = index;
            return true;
        }

    public:
        bool set_data(T *data) {
            SPDLOG_DEBUG("next:{}, writer_cursor:{}, min_reader_cursor:{}", status_->next, status_->cursor, GetMinIndexOfConsumers());

            const auto idx = ClaimIndex();
            const bool ret = SetData(idx, data);
            if (ret) {
                return Commit(idx);
            }

            return ret;
        }

    private:
        int64_t GetMinIndexOfConsumers();

        int64_t GetNextSequenceForClaim() {
            // fetch_add, Adds val to the contained value and returns the value it had immediately before the operation.
            return status_->next.fetch_add(1) + 1;
        }
    };

    template<typename T>
    inline SharedMemoryRingBuffer<T>::SharedMemoryRingBuffer(wait::ENUM_WAIT_STRATEGY wait_strategy) {
        status_ = nullptr;
        wait_strategy_type_ = wait_strategy;
        wait_strategy_ = nullptr;
        item_size = sizeof(T);
    }

    template<typename T>
    inline SharedMemoryRingBuffer<T>::~SharedMemoryRingBuffer() {
        if (wait_strategy_) {
            delete wait_strategy_;
            wait_strategy_ = nullptr;
        }
    }

    template<typename T>
    inline bool SharedMemoryRingBuffer<T>::InitRingBuffer(const key_t &shm_key, int size) {
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

        //shared memory consists of : RingBufferStatusOnSharedMemory + actual data
        total_mem_size_ = (int64_t) sizeof(RingBufferStatusOnSharedMemory) + (int64_t) (sizeof(T) * size);

        bool isShmFirstCreated = false;
        if (!shm_manager_.CreateShm(shm_key, total_mem_size_, isShmFirstCreated)) {
            SPDLOG_ERROR("CreateShm failed :{}", shm_manager_.GetLastErrMsg());
            return false;
        }
        if (!shm_manager_.AttachShm()) {
            SPDLOG_ERROR("AttachShm failed :{}", shm_manager_.GetLastErrMsg());
            return false;
        }
        status_ = (RingBufferStatusOnSharedMemory *) shm_manager_.GetShmStartAddress();
        if (isShmFirstCreated) {
            ResetRingBufferState();
        }
        char *pBufferStart = (char *) shm_manager_.GetShmStartAddress() + sizeof(RingBufferStatusOnSharedMemory);

        SPDLOG_DEBUG("Shared memory initialization.");
        for (int i = 0; i < size; i++) {
            ring_buffer_[i] = (T *) ((char *) pBufferStart + (sizeof(T) * i));
        }
        status_->buffer_size = size;
        status_->total_mem_size = total_mem_size_;

        //wait strategy
        if (wait_strategy_type_ == wait::BLOCKING_WAIT) {
            SPDLOG_INFO("Wait Strategy :BLOCKING_WAIT");
            wait_strategy_ = new wait::BlockingWaitStrategy(status_);
        } else if (wait_strategy_type_ == wait::YIELDING_WAIT) {
            SPDLOG_INFO("Wait Strategy :YIELDING_WAIT");
            wait_strategy_ = new wait::YieldingWaitStrategy(status_);
        } else if (wait_strategy_type_ == wait::SLEEPING_WAIT) {
            SPDLOG_INFO("Wait Strategy :SLEEPING_WAIT");
            wait_strategy_ = new wait::SleepingWaitStrategy(status_);
        } else {
            SPDLOG_ERROR("Error: Invalid Wait Strategy: {}", wait_strategy_type_);
            return false;
        }
        return true;
    }

    template<typename T>
    inline void SharedMemoryRingBuffer<T>::ResetRingBufferState() {
        if (status_ == nullptr) {
            SPDLOG_ERROR("call InitRingBuffer first !");
            return;
        }
        SPDLOG_DEBUG("ResetRingBufferState");
        status_->cursor.store(-1);
        status_->next.store(-1);
        status_->registered_producer_count.store(0);
        status_->registered_consumer_count.store(0);
        total_mem_size_ = 0;
        for (auto &array_of_consumer_index: status_->array_of_consumer_indexes) {
            array_of_consumer_index = -1;
        }
        //for blocking wait strategy : shared mutex, shared cond var
        pthread_mutexattr_t mutexAttr;
        pthread_mutexattr_init(&mutexAttr);
        pthread_mutexattr_setpshared(&mutexAttr, PTHREAD_PROCESS_SHARED);
        pthread_mutex_init(&status_->mtx_lock, &mutexAttr);

        pthread_condattr_t condAttr;
        pthread_condattr_init(&condAttr);
        pthread_condattr_setpshared(&condAttr, PTHREAD_PROCESS_SHARED);
        pthread_cond_init(&status_->cond_var, &condAttr);
    }

    template<typename T>
    inline bool SharedMemoryRingBuffer<T>::TerminateRingBuffer() {
        if (!shm_manager_.DetachShm()) {
            SPDLOG_ERROR("Error");
            return false;
        }
        if (!shm_manager_.RemoveShm()) {
            SPDLOG_ERROR("Error");
            return false;
        }
        return true;
    }

    template<typename T>
    inline bool SharedMemoryRingBuffer<T>::SetData(const int64_t &index, T *data) {
        memcpy(ring_buffer_[index], data, item_size);
        return true;
    }

    template<typename T>
    inline T *SharedMemoryRingBuffer<T>::GetData(const int64_t &index) {
        return ring_buffer_[index];
    }

    template<typename T>
    inline void SharedMemoryRingBuffer<T>::NotifyAll() {
        wait_strategy_->NotifyAllWhenBlocking();//blocking wait strategy only.
    }

    // 一个进程写入，单进程内多线程因为原子操作无需区分写入线程
    template<typename T>
    inline int64_t SharedMemoryRingBuffer<T>::ClaimIndex() {
        int64_t nNextSeqForClaim = GetNextSequenceForClaim();
        int64_t wrapPoint = nNextSeqForClaim - buffer_size_;
        do {
            int64_t gatingSequence = GetMinIndexOfConsumers();
            if (wrapPoint >= gatingSequence) {
                std::this_thread::yield();
                continue;
            } else {
                break;
            }
        } while (true);
        return nNextSeqForClaim;
    }

    template<typename T>
    inline int64_t SharedMemoryRingBuffer<T>::GetMinIndexOfConsumers() {
        int64_t min_index = INT64_MAX;
        bool is_found = false;
        for (size_t i = 0; i < status_->registered_consumer_count; i++) {
            int64_t index = status_->array_of_consumer_indexes[i];
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

    template<typename T>
    inline bool SharedMemoryRingBuffer<T>::Commit(const int64_t &index) {
        const int64_t expected = index - 1;
        while (true) {
            if (status_->cursor == expected) {
                status_->cursor = index;
                break;
            }
            std::this_thread::yield();
        }
        wait_strategy_->NotifyAllWhenBlocking();//blocking wait strategy only.
        return true;
    }

    ///
    /// \tparam T
    /// \param id consumer identify
    /// \param index_of_customer ==-1，from first
    /// \return
    template<typename T>
    inline bool SharedMemoryRingBuffer<T>::RegisterConsumer(const int &id, int64_t &index_of_customer) {
        if (id >= MAX_CONSUMER) {
            SPDLOG_ERROR("Customer more than {}", MAX_CONSUMER);
            return false;
        }

        if (status_->array_of_consumer_indexes[id] == -1) {
            status_->registered_consumer_count++;
            if (status_->registered_consumer_count >= MAX_CONSUMER) {
                SPDLOG_ERROR("Exceeds MAX_CONSUMER : {}", MAX_CONSUMER);
                return false;
            }
            if (status_->cursor >= 0) {
                SPDLOG_INFO("cursor >= 0.");
                if (index_of_customer == -1) {
                    status_->array_of_consumer_indexes[id] = status_->cursor.load() - status_->buffer_size + 1;
                } else if (index_of_customer == 0) {
                    status_->array_of_consumer_indexes[id] = status_->cursor.load();
                } else {
                    SPDLOG_ERROR("error params!");
                    return false;
                }

            } else {
                SPDLOG_INFO("user cursor set 0.");
                status_->array_of_consumer_indexes[id] = 0;
            }
            index_of_customer = status_->array_of_consumer_indexes[id];
        } else {
            // note: blocking made ring-buffer start_idx <= consumer cursor
            index_of_customer = status_->array_of_consumer_indexes[id] + 1;
        }
        SPDLOG_INFO("USAGE_CONSUMER ID: {}, index: {}", id, index_of_customer);
        return true;
    }

    template<typename T>
    inline int64_t SharedMemoryRingBuffer<T>::WaitFor(const int64_t &index) {
        int64_t nCurrentCursor = status_->cursor.load();
        if (index > nCurrentCursor) {
            return wait_strategy_->Wait(index);
        } else {
            return nCurrentCursor;
        }
    }

}// namespace disruptor

#endif//DISRUPTOR_IPC_SHM_RINGBUFFER_H
