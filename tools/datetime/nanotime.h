//
// Created by 稻草人 on 2022/6/16.
//

#ifndef NANOTIME_NANOTIME_H
#define NANOTIME_NANOTIME_H

#include "kftime.h"

inline int64_t now_in_nano() {
    return kungfu::yijinjing::time::now_in_nano();
}

inline int64_t time2num(const std::string &time) {
    return kungfu::yijinjing::time::strptime(time);
}

inline std::string num2time(const int64_t &time) {
    return kungfu::yijinjing::time::strftime(time);
}

#endif//NANOTIME_NANOTIME_H
