cmake_minimum_required(VERSION 3.17.2)

project(main)

set(SOURCES
    src/main.cpp
)

add_executable(main src/main.cpp)

target_include_directories(main 
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/include
)

find_package(dpp CONFIG REQUIRED)
target_link_libraries(main PRIVATE dpp::dpp)

