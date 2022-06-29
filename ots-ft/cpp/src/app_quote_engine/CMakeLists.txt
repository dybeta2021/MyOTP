
pybind11_add_module(app_quote_engine app_quote_engine.cpp "${PROJECT_SOURCE_DIR}/deps/kungfu/kftime.cpp")
target_link_directories(app_quote_engine PUBLIC "${PROJECT_SOURCE_DIR}/deps/ctp_future")
target_link_libraries(app_quote_engine PUBLIC pthread)
target_link_libraries(app_quote_engine PUBLIC libthostmduserapi_se.so)

IF (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --rtlib=compiler-rt")
ENDIF ()
