#cmake_minimum_required(VERSION 3.10)

cmake_minimum_required(VERSION 3.50)
project(my_epoll_server)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)  # 可执行文件输出到 build/bin
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)  # 动态库输出到 build/lib
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)  # 静态库输出到 build/lib

include_directories(${PROJECT_SOURCE_DIR}/include)

set(SRC main.cpp Socket/socket.cpp Socket/logger.cpp)
add_executable(my_epoll_server ${SRC})

if(WIN32)
    target_link_libraries(my_epoll_server PRIVATE ws2_32)
endif()