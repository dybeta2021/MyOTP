if (WIN32)
    set(CMAKE_TOOLCHAIN_FILE C:/Software/vcpkg/scripts/buildsystems/vcpkg.cmake CACHE STRING "Vcpkg toolchain file")
endif ()
if (APPLE)
    set(PYTHON_EXECUTABLE /usr/local/Caskroom/miniconda/base/bin/python)
endif ()

cmake_minimum_required(VERSION 3.20)
project(app_ctp_future_quote_engine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE "Release")

set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost COMPONENTS filesystem system thread regex REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})

find_package(spdlog)
find_package(fmt)
find_package(pybind11)

#ctp
include_directories(ctp/include)
link_directories(ctp/lib)

pybind11_add_module(${PROJECT_NAME} app_ctp_future_quote_engine.cpp deps/kungfu/kftime.cpp)
target_link_directories(${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/ctp/lib")

if (WIN32)
    target_link_libraries(service ${Boost_LIBRARIES})
endif ()
if (UNIX AND NOT APPLE)
    target_link_libraries(${PROJECT_NAME} PUBLIC ${Boost_LIBRARIES} fmt::fmt)
    target_link_libraries(${PROJECT_NAME} PUBLIC libthostmduserapi_se.so)
    FILE(COPY ctp/lib/libthostmduserapi_se.so DESTINATION ${CMAKE_BINARY_DIR})
endif ()
if (APPLE)
    target_link_libraries(${PROJECT_NAME} PUBLIC ${Boost_LIBRARIES} fmt::fmt iconv)
    target_link_libraries(${PROJECT_NAME} PUBLIC libthostmduserapi_se.dylib)
    FILE(COPY ctp/lib/libthostmduserapi_se.dylib DESTINATION ${CMAKE_BINARY_DIR})
endif ()

FILE(COPY ctp/error.dtd DESTINATION ${CMAKE_BINARY_DIR})
FILE(COPY ctp/error.xml DESTINATION ${CMAKE_BINARY_DIR})