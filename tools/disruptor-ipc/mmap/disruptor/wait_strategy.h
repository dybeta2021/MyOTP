//
// Created by 稻草人 on 2022/6/19.
//
// 等待读取数据的工具类，主要负责等待可读取游标是否到达要读取的位置，可中断等待。
// BusySpinStrategy：不放弃cpu死循环等待
// YieldingStrategy：死循环一定次数后调用yield放弃cpu时间片。
// SleepingStrategy：死循环一定次数后重复调用yield放弃cpu时间片。调用yield一定次数后重复调用sleep睡眠指定时间。
// BlockingStrategy：阻塞等待，内部使用了条件变量，需要写入的时候唤醒。

#ifndef DISRUPTOR_IPC_WAIT_STRATEGY_H
#define DISRUPTOR_IPC_WAIT_STRATEGY_H
#include "shm.h"
#include <atomic>
#include <condition_variable>
#include <fcntl.h>
#include <iostream>
#include <pthread.h>//blocking strategy : mutex, condition_var on shared memory
#include <sys/ipc.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <thread>

namespace disruptor::wait {
    typedef enum {
        BLOCKING_WAIT,
        YIELDING_WAIT,
        SLEEPING_WAIT
    } ENUM_WAIT_STRATEGY;

    class WaitStrategy {
    public:
        WaitStrategy() = default;
        ;
        virtual ~WaitStrategy() = default;
        ;
        virtual int64_t Wait(int64_t nIndex) = 0;
        virtual void NotifyAllWhenBlocking() = 0;//blocking strategy only
    protected:
        ShmStoreHeader *shm_hdr{};
    };

    class YieldingWaitStrategy : public WaitStrategy {
    public:
        explicit YieldingWaitStrategy(ShmStoreHeader *ptr) {
            shm_hdr = ptr;
        };
        ~YieldingWaitStrategy() override = default;
        ;

        int64_t Wait(int64_t nIndex) override {
            int nCounter = 100;
            while (true) {
                int64_t nCurrentCursor = shm_hdr->cursor.load();
                if (nIndex > nCurrentCursor) {
                    //spins --> yield
                    if (nCounter == 0) {
                        std::this_thread::yield();
                    } else {
                        nCounter--;
                    }
                    continue;
                } else {
                    return nCurrentCursor;
                }
            }//while
        }
        void NotifyAllWhenBlocking() override {//blocking strategy only
        }
    };

    class SleepingWaitStrategy : public WaitStrategy {
    public:
        explicit SleepingWaitStrategy(ShmStoreHeader *ptr) {
            shm_hdr = ptr;
        };
        ~SleepingWaitStrategy() override = default;
        ;

        int64_t Wait(int64_t nIndex) override {
            int nCounter = 200;

            while (true) {
                int64_t nCurrentCursor = shm_hdr->cursor.load();
                if (nIndex > nCurrentCursor) {
                    //spins --> yield --> sleep
                    if (nCounter > 100) {
                        nCounter--;
                    } else if (nCounter > 0) {
                        std::this_thread::yield();
                        nCounter--;
                    } else {
                        std::this_thread::sleep_for(std::chrono::nanoseconds(1));
                    }
                    continue;
                } else {
                    return nCurrentCursor;
                }
            }//while
        }
        void NotifyAllWhenBlocking() override {//blocking strategy only
        }
    };

    class BlockingWaitStrategy : public WaitStrategy {
    public:
        explicit BlockingWaitStrategy(ShmStoreHeader *ptr) {
            shm_hdr = ptr;
        };
        ~BlockingWaitStrategy() override = default;
        ;

        int64_t Wait(int64_t nIndex) override {
            while (true) {
                int64_t nCurrentCursor = shm_hdr->cursor.load();
                if (nIndex > nCurrentCursor) {
                    struct timespec timeToWait {};
                    struct timeval now {};
                    gettimeofday(&now, nullptr);
                    timeToWait.tv_sec = now.tv_sec;
                    timeToWait.tv_nsec = now.tv_usec * 1000;
                    timeToWait.tv_sec += 1;
                    //timeToWait.tv_nsec += 100;
                    pthread_mutex_lock(&(shm_hdr->mtx_lock));

                    pthread_cond_timedwait(&(shm_hdr->cond_var),
                                           &(shm_hdr->mtx_lock),
                                           &timeToWait);
                    pthread_mutex_unlock(&(shm_hdr->mtx_lock));
                } else {
                    return nCurrentCursor;
                }
            }//while
        }
        void NotifyAllWhenBlocking() override {//blocking strategy only
            pthread_mutex_lock(&(shm_hdr->mtx_lock));
            pthread_cond_broadcast(&(shm_hdr->cond_var));
            pthread_mutex_unlock(&(shm_hdr->mtx_lock));
        }
    };


}// namespace disruptor::wait


#endif//DISRUPTOR_IPC_WAIT_STRATEGY_H
