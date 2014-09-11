cmake_minimum_required(VERSION 2.8)
project(polaris_shared)

include(GetGitRevisionDescription)
get_git_head_revision(GIT_REFSPEC GIT_SHA1)

file(GLOB_RECURSE LIBPOLARIS_SOURCES *.cpp)

add_library(polaris_shared ${LIBPOLARIS_SOURCES})
target_link_libraries(polaris_shared ${LIBS})

set(LIBS ${LIBS} polaris_shared PARENT_SCOPE)