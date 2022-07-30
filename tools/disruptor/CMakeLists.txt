cmake_minimum_required(VERSION 3.22)
project(multi_shm_queue)
set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_STANDARD 23)

include_directories(deps/spdlog-1.x/include)
add_subdirectory(deps/spdlog-1.x)

add_executable(multi_shm_queue main.cpp)
target_link_libraries(multi_shm_queue PUBLIC spdlog::spdlog_header_only)
