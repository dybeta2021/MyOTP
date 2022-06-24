if (WIN32)
    set(CMAKE_TOOLCHAIN_FILE C:/Software/vcpkg/scripts/buildsystems/vcpkg.cmake CACHE STRING "Vcpkg toolchain file")
endif ()
if (APPLE)
    set(PYTHON_EXECUTABLE /usr/local/Caskroom/miniconda/base/bin/python)
endif ()

cmake_minimum_required(VERSION 3.20)
project(app_yijinjing_service)

set(CMAKE_CXX_STANDARD 20)

set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost COMPONENTS filesystem system thread regex REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})

find_package(spdlog)
find_package(fmt)
find_package(pybind11)

include_directories(yjj/include)
aux_source_directory(yjj/paged PAGED)
aux_source_directory(yjj/journal JOURNAL)
set(SERVER yjj/provider/ClientPageProvider.cpp)

#add_executable(service ${PAGED} ${JOURNAL} ${SERVER} server.cpp)
pybind11_add_module(${PROJECT_NAME} ${PAGED} ${JOURNAL} ${SERVER} app_yijinjing_service.cpp)

if (WIN32)
    target_link_libraries(service ${Boost_LIBRARIES})
endif ()
if (UNIX AND NOT APPLE)
    target_link_libraries(${PROJECT_NAME} PUBLIC ${Boost_LIBRARIES} fmt::fmt)
endif ()
if (APPLE)
#    target_link_libraries(service ${Boost_LIBRARIES} fmt::fmt iconv)
    target_link_libraries(${PROJECT_NAME} PUBLIC ${Boost_LIBRARIES} fmt::fmt iconv)
endif ()

FILE(COPY python/test.py  DESTINATION ${CMAKE_BINARY_DIR})






