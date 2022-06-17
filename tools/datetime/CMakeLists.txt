cmake_minimum_required(VERSION 3.22)
project(nanotime)

set(CMAKE_CXX_STANDARD 20)

include_directories(deps/fmt-master/include)
add_subdirectory(deps/fmt-master EXCLUDE_FROM_ALL)

aux_source_directory(. SOURCE)
add_executable(${PROJECT_NAME} ${SOURCE})
target_link_libraries(${PROJECT_NAME} fmt-header-only)

#其中EXCLUDE_FROM_ALL 是我第一次知道有这种写法，表示将这个项目移除出 make 列表。
#接着是链接 fmt-header-only 这个库，其实也可以用 fmt 这个，从名字上就能区别它们的不同了
#https://moevis.github.io/cheatsheet/2018/10/11/fmt-%E6%9B%B4%E6%96%B9%E4%BE%BF%E7%9A%84-c++-format-%E5%BA%93.html