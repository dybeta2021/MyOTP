//
// Created by 杨东 on 2022/6/19.
//

#ifndef DISRUPTOR_IPC_RING_H
#define DISRUPTOR_IPC_RING_H

#include "spdlog/spdlog.h"
#include <iostream>
#include <memory>
#include <vector>

namespace disruptor {
    template<typename T>
    class RingBuffer {
    private:
        int64_t capacity_{};
        std::vector<T> buffer_;

    public:
        RingBuffer() = default;
        ~RingBuffer() = default;

        explicit RingBuffer(const std::vector<T> &buffer) : buffer_(buffer) {}

        T &operator[](const int64_t &sequence) {
            return buffer_[sequence & (capacity_ - 1)];//only when multiple of 2
        }

        int64_t GetTranslatedIndex(const int64_t &sequence) {
            int64_t translated_index = (sequence & (capacity_ - 1));
            return translated_index;
        }

        bool SetCapacity(const int64_t &capacity) {
            bool is_power2 = capacity && !((capacity - 1) & capacity);
            if (is_power2 == 0) {
                SPDLOG_ERROR("Buffer capacity error: power of 2 required!");
                return false;
            }

            try {
                buffer_.reserve(capacity);
            } catch (const std::length_error &e) {
                SPDLOG_ERROR("Length error: {}", e.what());
                return false;
            }
            capacity_ = capacity;
            return true;
        }
    };
}// namespace disruptor

#endif//DISRUPTOR_IPC_RING_H
