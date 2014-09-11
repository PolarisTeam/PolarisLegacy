cmake_minimum_required(VERSION 2.8)
project(PolarisServer)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules")

find_package(Poco REQUIRED)
include_directories(${POCO_INCLUDE_DIRS})
set(LIBS ${LIBS} ${POCO_LIBRARIES} ${POCO_Net_LIBRARY} ${POCO_Util_LIBRARY})

add_subdirectory(polaris_shared)
include_directories(polaris_shared/src)

add_subdirectory(polaris_query)
