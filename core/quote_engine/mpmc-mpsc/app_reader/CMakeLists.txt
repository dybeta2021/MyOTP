cmake_minimum_required(VERSION 3.22)
project(app_reader)

set(CMAKE_CXX_STANDARD 23)

find_package(spdlog)
find_package(fmt)
find_package(pybind11)

include_directories(ctp/include)

#add_executable(app_reader app_reader.cpp)
pybind11_add_module(${PROJECT_NAME} app_reader.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC ${Boost_LIBRARIES} fmt::fmt)
