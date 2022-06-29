# app_static_data_ctp_future

pybind11_add_module(app_static_data app_static_data.cpp)
target_link_directories(app_static_data PUBLIC "${PROJECT_SOURCE_DIR}/deps/ctp_future")
target_link_libraries(app_static_data PUBLIC pthread)
target_link_libraries(app_static_data PUBLIC libthosttraderapi_se.so)

