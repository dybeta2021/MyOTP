if (APPLE)
    set(PYTHON_EXECUTABLE /usr/local/Caskroom/miniconda/base/bin/python)
endif ()

cmake_minimum_required(VERSION 3.16)
project(app_ctp_spot_static_data)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE "Release")
find_package(pybind11)
find_package(spdlog)

aux_source_directory(. SOURCES)
pybind11_add_module(${PROJECT_NAME} ${SOURCES})
target_link_directories(${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}")
target_link_libraries(${PROJECT_NAME} PUBLIC soptthosttraderapi_se.so)
target_link_libraries(${PROJECT_NAME} PUBLIC pthread)

FILE(COPY libsoptthosttraderapi_se.so DESTINATION ${CMAKE_BINARY_DIR})