cmake_minimum_required (VERSION 3.0)

set (CMAKE_CXX_FLAGS "-g")
set (CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_STANDARD_REQUIRE ON)

add_definitions (-DDEBUG)

project (hate CXX)

add_subdirectory("src")

