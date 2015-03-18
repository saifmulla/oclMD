cmake_minimum_required(VERSION 2.8)

project (OclMD)


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
add_library(OclMD SHARED ${CMAKE_CURRENT_SOURCE_DIR}/src/System.cpp)
