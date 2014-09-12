cmake_minimum_required(VERSION 2.8)
project(polaris_block)

file(GLOB_RECURSE SOURCE_FILES *.cpp)

add_executable(polaris_block ${SOURCE_FILES})
target_link_libraries(polaris_block ${LIBS})