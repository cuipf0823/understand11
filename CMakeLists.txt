cmake_minimum_required(VERSION 2.8)
project(understand11_test)
set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES
    understand11.cc
)

#代码存在大量的未使用变量 忽略
add_definitions("-g -DDEBUG -Wno-unused-variable -Wno-return-type -MMD -funroll-loops -std=c++11")
add_executable(understand11_test ${SOURCE_FILES})
