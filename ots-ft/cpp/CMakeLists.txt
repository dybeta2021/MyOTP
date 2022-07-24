if (APPLE)
    set(PYTHON_EXECUTABLE /usr/local/Caskroom/miniconda/base/bin/python)
elseif(UNIX)
    set(PYTHON_EXECUTABLE /opt/miniconda3/bin/python)
endif ()


cmake_minimum_required(VERSION 3.20)
project(ots-ft)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE "Release")

include_directories(deps/spdlog-1.x/include)
add_subdirectory(deps/spdlog-1.x)
include_directories(deps/pybind11-2.9.2/include)
add_subdirectory(deps/pybind11-2.9.2)
include_directories(deps/fmt-9.0.0/include)
add_subdirectory(deps/fmt-9.0.0)
include_directories(deps/SQLiteCpp-master/include)
add_subdirectory(deps/SQLiteCpp-master)
include_directories(deps/magic_enum-master/include)
add_subdirectory(deps/magic_enum-master)

include_directories(deps/kungfu)
include_directories(deps/nut)
include_directories(include)

# ctp
include_directories(deps/ctp_future)
link_directories(deps/ctp_future)

add_subdirectory(src/app_static_data)
add_subdirectory(src/app_last_data)
add_subdirectory(src/app_quote_engine)
add_subdirectory(src/app_broker_engine)
FILE(COPY static_data.sqlite DESTINATION ${CMAKE_BINARY_DIR}/src/app_broker_engine)

if (APPLE)
    FILE(COPY deps/ctp_future/libthosttraderapi_se.dylib DESTINATION ${CMAKE_BINARY_DIR})
    FILE(COPY deps/ctp_future/libthostmduserapi_se.dylib DESTINATION ${CMAKE_BINARY_DIR})
elseif(UNIX)
    FILE(COPY deps/ctp_future/libthosttraderapi_se.so DESTINATION ${CMAKE_BINARY_DIR})
    FILE(COPY deps/ctp_future/libthostmduserapi_se.so DESTINATION ${CMAKE_BINARY_DIR})
endif ()