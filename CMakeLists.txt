project(rtsp_client)
cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_PREFIX_PATH ${PROJECT_SOURCE_DIR}/3rdparty/)

find_package(Boost REQUIRED COMPONENTS system)

add_executable(rtsp_client
    src/main.cpp
)

target_link_libraries(rtsp_client
    Boost::system
)