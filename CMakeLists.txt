cmake_minimum_required(VERSION 3.16)
project(Project1)

set(CMAKE_CXX_STANDARD 14)

add_executable(Project1 src/main.cpp src/machine.cpp include/machine.h src/money.cpp include/money.h src/product.cpp include/product.h)