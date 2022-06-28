#if (APPLE)
#    set(PYTHON_EXECUTABLE /usr/local/Caskroom/miniconda/base/bin/python)
#endif ()

cmake_minimum_required(VERSION 3.20)
project(ots-dr)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE "Release")
find_package(pybind11)
find_package(spdlog)

# app_static_data_ctp_future
link_directories(deps/ctp_future)

pybind11_add_module(app_static_data_ctp_future "${PROJECT_SOURCE_DIR}/app/app_static_data_ctp_future/app_static_data_ctp_future.cpp")

target_link_directories(app_static_data_ctp_future PUBLIC "${PROJECT_SOURCE_DIR}/deps/ctp_future")
target_link_libraries(app_static_data_ctp_future PUBLIC pthread)
target_link_libraries(app_static_data_ctp_future PUBLIC libthosttraderapi_se.so)
FILE(COPY deps/ctp_future/libthosttraderapi_se.so DESTINATION ${CMAKE_BINARY_DIR})

# app_data_recorder_ctp_future
include_directories(deps/readerwriterqueue)
include_directories(deps/clickhouse/contrib)
include_directories(deps/clickhouse)
include_directories(deps/kungfu)

link_directories(deps/ctp_future)
link_directories(deps/clickhouse)

pybind11_add_module(app_data_recorder_ctp_future "${PROJECT_SOURCE_DIR}/app/app_data_recorder_ctp_future/app_data_recorder_ctp_future.cpp" "${PROJECT_SOURCE_DIR}/deps/kungfu/kftime.cpp")

target_link_directories(app_data_recorder_ctp_future PUBLIC "${PROJECT_SOURCE_DIR}/deps/ctp_future")
target_link_libraries(app_data_recorder_ctp_future PUBLIC pthread)
target_link_libraries(app_data_recorder_ctp_future PUBLIC clickhouse-cpp-lib)
target_link_libraries(app_data_recorder_ctp_future PUBLIC libthostmduserapi_se.so)
FILE(COPY deps/ctp_future/libthostmduserapi_se.so DESTINATION ${CMAKE_BINARY_DIR})

IF (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --rtlib=compiler-rt")
ENDIF ()