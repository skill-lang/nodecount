cmake_minimum_required(VERSION 3.9)
project(nodecount)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -std=c++11 -Wall -pedantic -DNDEBUG")

################################
# skill c++ common
################################
ADD_SUBDIRECTORY(lib/skill.cpp.common)
include_directories(lib/skill.cpp.common)

################################
# OpenMP
################################
find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()


################################
# Unit Tests
################################

#implementation
file(GLOB_RECURSE SOURCE_FILES LIST_DIRECTORIES false src/*.cpp)
#actual tests
file(GLOB_RECURSE TEST_FILES LIST_DIRECTORIES false test/*.cpp)

add_executable(nodecount ${SOURCE_FILES} ${TEST_FILES})

# Link test executable against gtest & gtest_main
target_link_libraries(nodecount skill.cpp.common)

set_property(TARGET nodecount PROPERTY INTERPROCEDURAL_OPTIMIZATION True)
