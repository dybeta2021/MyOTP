if (APPLE)
    set(PYTHON_EXECUTABLE /usr/local/Caskroom/miniconda/base/bin/python)
endif ()

cmake_minimum_required(VERSION 3.16)
project(app_ctp_future_last_data)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE "Release")
find_package(pybind11)
find_package(spdlog)

aux_source_directory(. SOURCES)
pybind11_add_module(${PROJECT_NAME} ${SOURCES})
target_link_directories(${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}")
target_link_libraries(${PROJECT_NAME} PUBLIC thostmduserapi_se.so)
#target_link_libraries(${PROJECT_NAME} PUBLIC pthread)

FILE(COPY libthostmduserapi_se.so DESTINATION ${CMAKE_BINARY_DIR})
#FILE(COPY test.py DESTINATION ${CMAKE_BINARY_DIR})


