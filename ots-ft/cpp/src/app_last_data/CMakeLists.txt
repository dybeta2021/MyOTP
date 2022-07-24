# app_static_data_ctp_future

pybind11_add_module(app_last_data app_last_data.cpp)
target_link_directories(app_last_data PUBLIC "${PROJECT_SOURCE_DIR}/deps/ctp_future")
target_link_libraries(app_last_data PUBLIC pthread)

if (APPLE)
    target_link_libraries(app_last_data PUBLIC libthostmduserapi_se.dylib)
    target_link_libraries(app_last_data PUBLIC fmt::fmt)
elseif(UNIX)
    target_link_libraries(app_last_data PUBLIC libthostmduserapi_se.so)
endif ()

IF (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --rtlib=compiler-rt")
ENDIF ()
