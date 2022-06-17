if (APPLE)
    set(PYTHON_EXECUTABLE /usr/local/Caskroom/miniconda/base/bin/python)
endif ()
set(CMAKE_BUILD_TYPE "Release")

cmake_minimum_required(VERSION 3.20)
project(logger)
set(CMAKE_CXX_STANDARD 20)

include_directories(include)
aux_source_directory(. SOURCES)
add_executable(${PROJECT_NAME} ${SOURCES})
