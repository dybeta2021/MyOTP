if (APPLE)
    set(PYTHON_EXECUTABLE /usr/local/Caskroom/miniconda/base/bin/python)
endif ()
set(CMAKE_BUILD_TYPE "Release")

cmake_minimum_required(VERSION 3.22)
project(disruptor_ipc)

set(CMAKE_CXX_STANDARD 23)

#find_package(spdlog)
include_directories(disruptor)

add_executable(test main.cpp disruptor/mman.c)
target_link_libraries(test)

add_executable(producer producer.cpp disruptor/mman.c)
target_link_libraries(producer)

add_executable(consumer consumer.cpp disruptor/mman.c)
target_link_libraries(consumer)