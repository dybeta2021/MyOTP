#include "nanotime.h"
#include <iostream>

int main() {
    std::cout << "Hello, World!" << std::endl;

    auto current_time = now_in_nano();
    std::cout<<"current_time: " << current_time<<std::endl;

    auto str_time = num2time(current_time);
    std::cout<<"str_time: " << str_time<<std::endl;

    auto num_time = time2num(str_time);
    std::cout<<"num_time: " << num_time<<std::endl;
    return 0;
}
