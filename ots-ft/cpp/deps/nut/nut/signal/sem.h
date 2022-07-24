// https://github.com/jingqi/nut/blob/580bbfce2621d631c9eb7a8b059d14579c97ca90/src/nut/threading/sync/sem.h


#ifndef ___HEADFILE_49083D01_04DA_4385_A1BD_6D1F2902FA7A_
#define ___HEADFILE_49083D01_04DA_4385_A1BD_6D1F2902FA7A_

#include "platform.h"

#if NUT_PLATFORM_OS_WINDOWS
#include <windows.h>
#elif NUT_PLATFORM_OS_MACOS
#include <condition_variable>
#include <mutex>
#else
#include <semaphore.h>
#endif
#include <assert.h>
#include <time.h>

#if NUT_PLATFORM_OS_MACOS
#include <chrono>
#endif


namespace nut {
    class Semaphore {
    public:
        explicit Semaphore(unsigned init_value) noexcept;
        ~Semaphore() noexcept;

        void post() noexcept;

        void wait() noexcept;
        bool trywait() noexcept;
        bool timedwait(unsigned s, unsigned ms) noexcept;

    private:
        Semaphore(const Semaphore &) = delete;
        Semaphore &operator=(const Semaphore &) = delete;

    private:
#if NUT_PLATFORM_OS_WINDOWS
        HANDLE _sem = nullptr;
#elif NUT_PLATFORM_OS_MACOS
        // XXX macOS 上匿名 posix sem 被废弃了
        std::mutex _lock;
        std::condition_variable _cond;
        unsigned _count;
#else
        sem_t _sem;
#endif
    };


    inline Semaphore::Semaphore(unsigned init_value) noexcept {
#if NUT_PLATFORM_OS_WINDOWS
        _sem = ::CreateSemaphoreA(
                nullptr,   // security attributes
                init_value,// initial count
                0x7fffffff,// maximum value
                nullptr);  // name
        assert(nullptr != _sem);
#elif NUT_PLATFORM_OS_MACOS
        _count = init_value;
#else
        const int rs = ::sem_init(&_sem, 0, init_value);
        assert(0 == rs);
        UNUSED(rs);
#endif
    }

    inline Semaphore::~Semaphore() noexcept {
#if NUT_PLATFORM_OS_WINDOWS
        const BOOL rs = ::CloseHandle(_sem);
        assert(FALSE != rs);
        UNUSED(rs);
#elif NUT_PLATFORM_OS_MACOS
        // Nothing to do
#else
        int rs = ::sem_destroy(&_sem);
        assert(0 == rs);
        UNUSED(rs);
#endif
    }

    inline void Semaphore::post() noexcept {
#if NUT_PLATFORM_OS_WINDOWS
        const BOOL rs = ::ReleaseSemaphore(_sem, 1, nullptr);
        assert(FALSE != rs);
        UNUSED(rs);
#elif NUT_PLATFORM_OS_MACOS
        std::unique_lock<std::mutex> guard(_lock);
        ++_count;
        _cond.notify_one();
#else
        const int rs = ::sem_post(&_sem);
        assert(0 == rs);
        UNUSED(rs);
#endif
    }

    inline void Semaphore::wait() noexcept {
#if NUT_PLATFORM_OS_WINDOWS
        const DWORD rs = ::WaitForSingleObject(_sem, INFINITE);
        assert(WAIT_OBJECT_0 == rs);
        UNUSED(rs);
#elif NUT_PLATFORM_OS_MACOS
        std::unique_lock<std::mutex> unique_guard(_lock);
        _cond.wait(unique_guard, [=] { return _count > 0; });
        --_count;
#else
        const int rs = ::sem_wait(&_sem);
        assert(0 == rs);
        UNUSED(rs);
#endif
    }

    inline bool Semaphore::trywait() noexcept {
#if NUT_PLATFORM_OS_WINDOWS
        return WAIT_OBJECT_0 == ::WaitForSingleObject(_sem, 0);
#elif NUT_PLATFORM_OS_MACOS
        std::unique_lock<std::mutex> unique_guard(_lock);
        const bool ret = _cond.wait_for(
                unique_guard, std::chrono::milliseconds(0), [=] { return _count > 0; });
        if (ret)
            --_count;
        return ret;
#else
        return 0 == ::sem_trywait(&_sem);
#endif
    }

    inline bool Semaphore::timedwait(unsigned s, unsigned ms) noexcept {
#if NUT_PLATFORM_OS_WINDOWS
        const DWORD dw_milliseconds = s * 1000 + ms;
        return WAIT_OBJECT_0 == ::WaitForSingleObject(_sem, dw_milliseconds);
#elif NUT_PLATFORM_OS_MACOS
        std::unique_lock<std::mutex> unique_guard(_lock);
        const bool ret = _cond.wait_for(
                unique_guard, std::chrono::seconds(s) + std::chrono::milliseconds(ms),
                [=] { return _count > 0; });
        if (ret)
            --_count;
        return ret;
#else
        struct timespec abstime;
        ::clock_gettime(CLOCK_REALTIME, &abstime);
        abstime.tv_sec += s;
        abstime.tv_nsec += ((long) ms) * 1000 * 1000;
        return 0 == ::sem_timedwait(&_sem, &abstime);
#endif
    }


}// namespace nut

#endif
