CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

#set the appropriate environment for OSX if platform is macOSX
IF (APPLE AND NOT CMAKE_OSX_DEPLOYMENT_TARGET)
SET(CMAKE_OSX_ARCHITECTURES "x86_64")
SET(CMAKE_OSX_DEPLOYMENT_TARGET "")
ENDIF(APPLE AND NOT CMAKE_OSX_DEPLOYMENT_TARGET)

PROJECT(OclMD CXX) #name of project
SET(OCLMD_LIBRARY_NAME OclMD) #project library name
SET(SHARED_TARGET ${OCLMD_LIBRARY_NAME}) #shared
SET(STATIC_TARGET ${OCLMD_LIBRARY_NAME}_static) #static

#determine version of cmake, this project is build with version 2.8 in mind
SET(cmv "${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}")
MESSAGE("Using CMAKE version ${cmv}, anything below 2.8 is not guarenteed to work")

# create a list of of directories to be compiled at first
SET(OCLMD_SRC_SUB_DIR base/src)

#check if CMAKE_BUILD_TYPE is specified or else directly put to
# debug version, however in production make this to Release as default
IF(NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE Debug)
#later add further compiler definition information add_definitions
ENDIF(NOT CMAKE_BUILD_TYPE)

SET(ADDITIONAL_COMP_FLAGS "")

#set c++11 flag if compiler supports
#TODO: make appropriate checks for compiler
IF(CMAKE_BUILD_TYPE MATCHES Debug)
    SET(ADDITIONAL_COMP_FLAGS ${ADDITIONAL_COMP_FLAGS} "-g -O1 -DFULLDEBUG")
    MESSAGE("Building in DEBUG mode")
ELSEIF(CMAKE_BUILD_TYPE MATCHES Release)
    SET(ADDITIONAL_COMP_FLAGS ${ADDITIONAL_COMP_FLAGS} "-std=c++11 -O3 -ftree-vectorize -march=native")
    MESSAGE("Building in RELEASE mode")
ENDIF(CMAKE_BUILD_TYPE MATCHES Debug)

# now append the conditional compiler flags to
# CMAKE_CXX_FLAGS
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} ${ADDITIONAL_COMP_FLAGS})

#set preprocessor definations for internal realType
IF(${REALTYPE})
ADD_DEFINITIONS(-DREALTYPE=${REALTYPE})
ENDIF(${REALTYPE})

#check if GTEST_DIR and GMOCK_DIR paths are specified
# if not specified then compile the supplied frameworks
# which comes along source distribution
#
#
# later supply make provisions for enabling and disabling
# testing this will decide upon framework compilation
#
#
IF(NOT GTEST_DIR)
    MESSAGE("Using source supplied GTest framework...")
    SET(GTEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/frameworks/gtest)
    MESSAGE("GTEST directory root " ${GTEST_DIR})
    ADD_SUBDIRECTORY(frameworks/gtest)
ENDIF(NOT GTEST_DIR)

IF(NOT GMOCK_DIR)
    MESSAGE("Using source supplied gmock framework...")
    SET(GMOCK_DIR ${CMAKE_CURRENT_SOURCE_DIR}/frameworks/gmock)
    MESSAGE("GMOCK directory root " ${GTEST_MOCK})
    ADD_SUBDIRECTORY(frameworks/gmock)
ENDIF(NOT GMOCK_DIR)


# just added a variable with src directory name embedded
SET(SRC_SUBDIRS "src")
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/base/include ${CMAKE_CURRENT_SOURCE_DIR}/api/include ${CMAKE_CURRENT_SOURCE_DIR}/platform/cpu/include ${CMAKE_CURRENT_SOURCE_DIR}/platform/omp/include)

# start compiling each source file
# this list is for the API source files
SET(FILENAME_LIST "") #an empty list of cpp file names

#this list is for the internal files
SET(FILENAME_LIST ${FILENAME_LIST} ${CMAKE_CURRENT_SOURCE_DIR}/base/${SRC_SUBDIRS}/Platform.cpp)
SET(FILENAME_LIST ${FILENAME_LIST} ${CMAKE_CURRENT_SOURCE_DIR}/base/${SRC_SUBDIRS}/BaseImpl.cpp)
SET(FILENAME_LIST ${FILENAME_LIST} ${CMAKE_CURRENT_SOURCE_DIR}/base/${SRC_SUBDIRS}/Base.cpp)

FILE(GLOB SRC_PROGS "${CMAKE_CURRENT_SOURCE_DIR}/api/src/*.cpp") #read into list of *.cpp filenames
FOREACH(SRC_PROG ${SRC_PROGS})
GET_FILENAME_COMPONENT(FILENAME ${SRC_PROG} NAME)
SET(FILENAME_LIST ${FILENAME_LIST}  api/src/${FILENAME})
ENDFOREACH(SRC_PROG ${SRC_PROGS})

#include cpu platform src files
# as this is default platform therefore must be compiled irrespectively

FILE(GLOB CPUSRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/platform/cpu/src/*.cpp")
FOREACH(CPUSRC ${CPUSRC_FILES})
GET_FILENAME_COMPONENT(FILENAME ${CPUSRC} NAME)
SET(FILENAME_LIST ${FILENAME_LIST} platform/cpu/src/${FILENAME})
ENDFOREACH(CPUSRC ${CPUSRC_FILES})

#find library does not works with any compiler
# therefore find_package is a convinient option
FIND_PACKAGE(OpenMP QUIET)
IF(OPENMP_FOUND)
    MESSAGE("Compiler supports OpenMP! installing OMP platform")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    SET(FILENAME_LIST ${FILENAME_LIST} platform/omp/src/OmpBaseFactory.cpp)
    SET(FILENAME_LIST ${FILENAME_LIST} platform/omp/src/OmpPlatform.cpp)
ENDIF(OPENMP_FOUND)

ADD_LIBRARY(${SHARED_TARGET} SHARED ${FILENAME_LIST}) #use all the *.cpp codes to create a library

#enable testing and add subdir 'tests'
ADD_SUBDIRECTORY(tests)
#add test directory for platforms
ADD_SUBDIRECTORY(platform/tests)

#add test directory of OMP tests
IF(OPENMP_FOUND)
    ADD_SUBDIRECTORY(platform/omp/tests)
ENDIF(OPENMP_FOUND)

#testing is enabled
ENABLE_TESTING()

#instal API
#TODO - later make provisions for user supplied path
SET(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/${CMAKE_BUILD_TYPE})

MESSAGE("Installing " ${PROJECT_NAME} " at " ${CMAKE_INSTALL_PREFIX})

INSTALL (TARGETS ${SHARED_TARGET} DESTINATION lib)
FILE(GLOB MAIN_HEADER ${CMAKE_SOURCE_DIR}/api/include/*.h)
FILE(GLOB API_HEADERS ${CMAKE_SOURCE_DIR}/api/include/oclmd/*.h)
FILE(GLOB IMPL_HEADERS ${CMAKE_SOURCE_DIR}/api/include/oclmd/impl/*.h)
FILE(GLOB CPU_PLATFORM_HEADERS ${CMAKE_SOURCE_DIR}/platform/cpu/include/*.h)

INSTALL (FILES ${MAIN_HEADER} DESTINATION include)
INSTALL (FILES ${API_HEADERS} DESTINATION include/oclmd)
INSTALL (FILES ${IMPL_HEADERS} DESTINATION include/oclmd/impl)
INSTALL (FILES ${CPU_PLATFORM_HEADERS} DESTINATION include/oclmd/cpu)







