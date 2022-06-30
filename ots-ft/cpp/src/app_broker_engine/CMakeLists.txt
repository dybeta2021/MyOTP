#pybind11_add_module(app_broker_engine app_broker_engine.cpp)
aux_source_directory(. BROKER_ENGINE)
#add_executable(app_broker_engine ${BROKER_ENGINE})
add_executable(app_broker_engine  gateway.cpp broker_ctp.cpp app_broker_engine.cpp)

target_link_directories(app_broker_engine PUBLIC "${PROJECT_SOURCE_DIR}/deps/ctp_future")
target_link_libraries(app_broker_engine PUBLIC pthread)
target_link_libraries(app_broker_engine PUBLIC libthosttraderapi_se.so)
target_link_libraries(app_broker_engine PUBLIC fmt::fmt)