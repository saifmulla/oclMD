cmake_minimum_required(VERSION 2.8)
project(OclMDTests)

include_directories("../include")
include_directories("${GTEST_DIR}/include")

add_executable(Vec3Test TestVec3.cpp)
target_link_libraries(Vec3Test gomp pthread "-L${GTEST_DIR}" gtest)
