//
// Created by 稻草人 on 2022/6/28.
//

#ifndef OTS_FT_NAN_TO_NUM_H
#define OTS_FT_NAN_TO_NUM_H
#include <chrono>

namespace ots::utils{
    void inline timing_ms(int ms) {
        auto us = ms * 1000;
        auto start = std::chrono::system_clock::now();
        while (true) {
            auto end = std::chrono::system_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            if (duration.count() > us) break;
        }
    }

}

#endif//OTS_FT_NAN_TO_NUM_H
