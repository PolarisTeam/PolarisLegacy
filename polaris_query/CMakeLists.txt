cmake_minimum_required(VERSION 2.8.4)
project(polaris_query)

set(SOURCE_FILES src/PolarisQuery.cpp src/QueryServerFactory.cpp src/QueryServerConnection.cpp)
add_executable(polaris_query ${SOURCE_FILES})

target_link_libraries(polaris_query ${LIBS})
