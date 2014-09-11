cmake_minimum_required(VERSION 2.8)
project(polaris_query)

file(GLOB_RECURSE SOURCE_FILES *.cpp)

message("Hello " ${SOURCE_FILES})

add_executable(polaris_query ${SOURCE_FILES})
target_link_libraries(polaris_query ${LIBS})