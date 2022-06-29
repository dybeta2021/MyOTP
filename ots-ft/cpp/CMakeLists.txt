if (APPLE)
    set(PYTHON_EXECUTABLE /usr/local/Caskroom/miniconda/base/bin/python)
endif ()

cmake_minimum_required(VERSION 3.20)
project(ots-ft)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_BUILD_TYPE "Release")
find_package(pybind11)
find_package(spdlog)

include_directories(include)
include_directories(deps/kungfu)

# ctp
include_directories(deps/ctp_future)
link_directories(deps/ctp_future)
#
#add_subdirectory(src/app_static_data)
#FILE(COPY deps/ctp_future/libthosttraderapi_se.so DESTINATION ${CMAKE_BINARY_DIR})
#
#add_subdirectory(src/app_quote_engine)
#FILE(COPY deps/ctp_future/libthostmduserapi_se.so DESTINATION ${CMAKE_BINARY_DIR})

add_subdirectory(src/app_broker_engine)
FILE(COPY deps/ctp_future/libthostmduserapi_se.so DESTINATION ${CMAKE_BINARY_DIR})