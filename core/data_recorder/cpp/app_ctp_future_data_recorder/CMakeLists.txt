if (APPLE)
    set(PYTHON_EXECUTABLE /usr/local/Caskroom/miniconda/base/bin/python)
endif ()

cmake_minimum_required(VERSION 3.20)
project(app_ctp_future_data_recorder)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE "Release")

include_directories(ctp/include)
link_directories(ctp/lib)

find_package(pybind11)
include_directories(deps/fmt/include)
add_subdirectory(deps/fmt)
include_directories(deps/spdlog/include)
add_subdirectory(deps/spdlog)
include_directories(deps/contrib)
include_directories(deps/clickhouse)

aux_source_directory(. SOURCES)
pybind11_add_module(${PROJECT_NAME} ${SOURCES})

target_link_directories(${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/ctp/lib")
target_link_directories(${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/lib")
target_link_libraries(${PROJECT_NAME} PUBLIC pthread)
target_link_libraries(${PROJECT_NAME} PUBLIC fmt)
#target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt-header-only)
target_link_libraries(${PROJECT_NAME} PUBLIC clickhouse-cpp-lib)
target_link_libraries(${PROJECT_NAME} PUBLIC libthostmduserapi_se.so)

IF (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --rtlib=compiler-rt")
ENDIF ()

FILE(COPY ctp/lib/libthostmduserapi_se.so DESTINATION ${CMAKE_BINARY_DIR})
FILE(COPY ctp/error.dtd DESTINATION ${CMAKE_BINARY_DIR})
FILE(COPY ctp/error.xml DESTINATION ${CMAKE_BINARY_DIR})
message(${CMAKE_BINARY_DIR})