cmake_minimum_required(VERSION 3.10)

project(ImageProcessing)

set(CMAKE_CXX_STANDARD 17)

add_executable(ImageProcessing main.cpp image.cpp)

target_compile_options(ImageProcessing PRIVATE -Wall -Wextra -pedantic -O2)
