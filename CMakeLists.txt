cmake_minimum_required(VERSION 2.8.4)
project(PolarisServer)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules")

find_package(POCO REQUIRED)
include_directories(${POCO_INCLUDE_DIRS})
set(LIBS ${LIBS} ${POCO_LIBRARIES})

add_subdirectory(polaris_query)