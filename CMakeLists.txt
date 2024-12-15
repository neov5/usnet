cmake_minimum_required(VERSION 3.14)
project(virtio-console-driver 
    VERSION 0.1
    LANGUAGES C CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE) # for clangd
set(CMAKE_CXX_STANDARD 23)

set(CMAKE_C_FLAGS_DEBUG "-Wall -Wextra -fsanitize=address -static-libasan -g")
set(CMAKE_C_FLAGS_RELEASE "-O2")


file(GLOB_RECURSE SOURCES src/*.hpp src/*.cpp)
add_executable(driver ${SOURCES})
target_include_directories(driver PRIVATE include)
