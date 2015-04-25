CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

#set the appropriate environment for OSX if platform is macOSX
IF (APPLE AND NOT CMAKE_OSX_DEPLOYMENT_TARGET)
    SET(CMAKE_OSX_ARCHITECTURES "x86_64")
    SET(CMAKE_OSX_DEPLOYMENT_TARGET "")
ENDIF(APPLE AND NOT CMAKE_OSX_DEPLOYMENT_TARGET)

PROJECT(OclMD) #name of project
SET(OCLMD_LIBRARY_NAME OclMD) #project library name
SET(SHARED_TARGET ${OCLMD_LIBRARY_NAME}) #shared
SET(STATIC_TARGET ${OCLMD_LIBRARY_NAME}_static) #static

#determine version of cmake, this project is build with version 2.8 in mind
SET(cmv "${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}")
MESSAGE("Using CMAKE version ${cmv}, anything below 2.8 is not guarenteed to work")

# create a list of of directories to be compiled at first
SET(OCLMD_SRCSUB_DIR src base/src platform/cpu)

#set c++11 flag if compiler supports
#TODO: make appropriate checks for compiler
ADD_DEFINITIONS(-std=c++11 -g -O1)
#set preprocessor definations for internal realType
IF(${REALTYPE})
    ADD_DEFINITIONS(-DREALTYPE=${REALTYPE})
ENDIF(${REALTYPE})

IF(NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE Debug)
    #later add further compiler definition information add_definitions
ENDIF(NOT CMAKE_BUILD_TYPE)

SET(SRC_SUBDIRS "src")

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/include/internal ${CMAKE_CURRENT_SOURCE_DIR}/base/include ${CMAKE_CURRENT_SOURCE_DIR}/platform/cpu/include)
# start compiling each source file
# this list is for the API source files
SET(FILENAME_LIST "") #an empty list of cpp file names

FILE(GLOB SRC_PROGS "${CMAKE_CURRENT_SOURCE_DIR}/${SRC_SUBDIRS}/*.cpp") #read into list of *.cpp filenames
FOREACH(SRC_PROG ${SRC_PROGS})
    GET_FILENAME_COMPONENT(FILENAME ${SRC_PROG} NAME)
    SET(FILENAME_LIST ${FILENAME_LIST}  ${SRC_SUBDIRS}/${FILENAME})
ENDFOREACH(SRC_PROG ${SRC_PROGS})

#this list is for the internal files
SET(FILENAME_LIST ${FILENAME_LIST} ${CMAKE_CURRENT_SOURCE_DIR}/base/${SRC_SUBDIRS}/Platform.cpp)

#inlude cpu platform src files
FILE(GLOB CPUSRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/platform/cpu/src/*.cpp")
FOREACH(CPUSRC ${CPUSRC_FILES})
    GET_FILENAME_COMPONENT(FILENAME ${CPUSRC} NAME)
    SET(FILENAME_LIST ${FILENAME_LIST} platform/cpu/src/${FILENAME})
ENDFOREACH(CPUSRC ${CPUSRC_FILES})

ADD_LIBRARY(${SHARED_TARGET} SHARED ${FILENAME_LIST}) #use all the *.cpp codes to create a library

#enable testing and add subdir 'tests'
ADD_SUBDIRECTORY(tests)
#add test directory for platforms
ADD_SUBDIRECTORY(platform/tests)

#testing is enabled
ENABLE_TESTING()

