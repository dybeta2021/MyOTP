if (APPLE)
    set(PYTHON_EXECUTABLE /usr/local/Caskroom/miniconda/base/bin/python)
endif ()
set(CMAKE_BUILD_TYPE "Release")

cmake_minimum_required(VERSION 3.22)
project(disruptor_ipc)

set(CMAKE_CXX_STANDARD 23)

find_package(spdlog)

add_executable(producer producer.cpp)
target_link_libraries(producer fmt::fmt)

add_executable(consumer consumer.cpp)
target_link_libraries(consumer fmt::fmt)

add_executable(remove_shm remove_shm.cpp)
target_link_libraries(remove_shm fmt::fmt)