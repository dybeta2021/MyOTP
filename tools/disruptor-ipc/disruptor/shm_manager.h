//
// Created by 稻草人 on 2022/6/19.
//

#ifndef DISRUPTOR_IPC_SHM_MANAGER_H
#define DISRUPTOR_IPC_SHM_MANAGER_H

#include "spdlog/spdlog.h"
#include <cerrno>
#include <cstdio>
#include <cstring>
#include <string>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>


namespace disruptor::shm {
    class SharedMemoryManager {
    private:
        key_t shm_key_{};
        int shm_id_;
        int64_t shm_size_;
        void *shm_start_address_;
        int total_attached_;
        std::string err_msg_;

    public:
        SharedMemoryManager() {
            shm_id_ = -1;
            shm_size_ = 0;
            shm_start_address_ = nullptr;
            total_attached_ = 0;
            err_msg_ = "null";
        }
        bool CreateShm(const key_t &key, const int64_t &size, bool &first_created);
        bool GetShm(const key_t &key, const int64_t &size);
        bool AttachShm();
        bool DetachShm();
        bool RemoveShm();

        void *GetShmStartAddress() { return shm_start_address_; }
        const char *GetLastErrMsg() { return err_msg_.c_str(); }
        [[nodiscard]] int GetAttachedCount() const { return total_attached_; }
    };

    inline bool SharedMemoryManager::CreateShm(const key_t &key, const int64_t &size, bool &first_created) {
        first_created = false;
        shm_key_ = key;
        shm_size_ = size;

        // IPC_CREAT|IPC_EXCL：如果内核中不存在键值与key相等的共享内存，则新建一个消息队列；如果存在这样的共享内存则报错
        shm_id_ = shmget(key, size, IPC_CREAT | IPC_EXCL | 0666);
        if (shm_id_ < 0) {
            if (errno == EINVAL) {
                err_msg_ = std::string("EINVAL：参数size小于SHMMIN或大于SHMMAX.");
                SPDLOG_ERROR(err_msg_);
                return false;
            } else if (errno == EIDRM) {
                err_msg_ = std::string("EIDRM：参数key所指的共享内存已经删除.");
                SPDLOG_ERROR(err_msg_);
                return false;
            } else if (errno == EEXIST) {
                SPDLOG_INFO("EEXIST：预建立key所指的共享内存，但已经存在.");
                return GetShm(key, size);
            } else if (errno == ENOSPC) {
                err_msg_ = std::string("ENOSPC：超过了系统允许建立的共享内存的最大值(SHMALL).");
                SPDLOG_ERROR(err_msg_);
                return false;
            } else if (errno == EACCES) {
                SPDLOG_INFO("EACCES:没有权限.");
                return GetShm(key, size);
            } else if (errno == ENOMEM) {
                err_msg_ = std::string("ENOMEM：核心内存不足");
                SPDLOG_ERROR(err_msg_);
                return false;
            } else {
                err_msg_ = std::string("未定义错误.");
                SPDLOG_CRITICAL("未定义错误");
                return false;
            }
        }
        first_created = true;
        SPDLOG_DEBUG("CreateShm, shmget key:{}, size:{}, first_created:{}.", key, size, first_created);
        return true;
    }

    inline bool SharedMemoryManager::GetShm(const key_t &key, const int64_t &size) {
        SPDLOG_DEBUG("GetShm, shmget key:{}, size:{}.", key, size);
        shm_key_ = key;
        shm_size_ = size;
        shm_id_ = shmget(key, size, 0666);
        if (shm_id_ < 0) {
            if (errno == EINVAL) {
                err_msg_ = std::string("EINVAL：参数size小于SHMMIN或大于SHMMAX.");
                SPDLOG_ERROR(err_msg_);
                return false;
            } else if (errno == EIDRM) {
                err_msg_ = std::string("EIDRM：参数key所指的共享内存已经删除.");
                SPDLOG_ERROR(err_msg_);
                return false;
            } else if (errno == ENOSPC) {
                err_msg_ = std::string("ENOSPC：超过了系统允许建立的共享内存的最大值(SHMALL).");
                SPDLOG_ERROR(err_msg_);
                return false;
            } else if (errno == EACCES) {
                err_msg_ = std::string("EACCES:没有权限.");
                SPDLOG_ERROR(err_msg_);
                return false;
            } else if (errno == ENOMEM) {
                err_msg_ = std::string("ENOMEM：核心内存不足");
                SPDLOG_ERROR(err_msg_);
                return false;
            } else {
                err_msg_ = std::string("未定义错误.");
                SPDLOG_CRITICAL("未定义错误");
                return false;
            }
        }
        return true;
    }

    inline bool SharedMemoryManager::AttachShm() {
        SPDLOG_DEBUG("AttachShm, shmat shmid:{}, shmaddr:NULL, shmflg:0.", shm_id_, shm_size_);
        //shmid：共享内存ID，通常是由shmget()函数返回的。
        //shmaddr：如果不为NULL，则系统会根据shmaddr来选择一个合适的内存区域， 如果为NULL，则系统会自动选择一个合适的虚拟内存空间地址去映射共享内存。
        //shmflg：操作共享内存的方式：
        //SHM_RDONLY：以只读方式映射共享内存。
        //SHM_REMAP：重新映射，此时shmaddr不能为NULL。
        //NULLSHM：自动选择比shmaddr小的最大页对齐地址。
        shm_start_address_ = shmat(shm_id_, nullptr, 0);
        if (shm_start_address_ == (void *) -1) {
            SPDLOG_ERROR("shmat error: {}, sh_mem_id_={}", strerror(errno), shm_id_);
            return false;
        }
        total_attached_++;
        return true;
    }

    inline bool SharedMemoryManager::DetachShm() {
        SPDLOG_DEBUG("DetachShm, shmdt shmaddr:{}.", shm_start_address_);
        if (shm_start_address_ == nullptr) {
            SPDLOG_ERROR("Error: shared mem start address is NULL");
            return false;
        }
        if (shmdt(shm_start_address_) == -1) {
            SPDLOG_ERROR("shmdt error: {}", strerror(errno));
            return false;
        }
        total_attached_--;
        return true;
    }

    inline bool SharedMemoryManager::RemoveShm() {
        SPDLOG_DEBUG("RemoveShm, shmctl shmid:{}, cmd: IPC_RMID.", shm_id_);

        if (total_attached_ > 0) {
            SPDLOG_ERROR("Error : attached exists :{}", total_attached_);
            return false;
        }
        if (shmctl(shm_id_, IPC_RMID, (struct shmid_ds *) nullptr) == -1) {
            SPDLOG_ERROR("Remove shared memory error: {}", strerror(errno));
            return false;
        }
        return true;
    }
}// namespace disruptor::shm


#endif//DISRUPTOR_IPC_SHM_MANAGER_H
