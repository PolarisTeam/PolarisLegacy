cmake_minimum_required(VERSION 2.8.4)
project(PolarisServer)

set(SOURCE_FILES src/polaris_query/main.cpp)
add_executable(PolarisServer ${SOURCE_FILES})