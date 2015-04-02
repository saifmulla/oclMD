CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(OclMD) #name of project
SET(OCLMD_LIBRARY_NAME OclMD) #project library name
SET(SHARED_TARGET ${OCLMD_LIBRARY_NAME}) #shared
SET(STATIC_TARGET ${OCLMD_LIBRARY_NAME}_static) #static

#set preprocessor definations for internal realType
IF(${REALTYPE})
    ADD_DEFINITIONS(-DREALTYPE=${REALTYPE})
ENDIF(${REALTYPE})
SET(CMAKE_BUILD_TYPE Debug) #TODO: later make this generic
SET(OCLMD_SRC_SUBDIRS "src")

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/include)
# start compiling each source file

SET(FILENAME_LIST "") #an empty list of cpp file names
FILE(GLOB SRC_PROGS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp") #read into list of *.cpp filenames

FOREACH(SRC_PROG ${SRC_PROGS})
    GET_FILENAME_COMPONENT(FILENAME ${SRC_PROG} NAME)
    SET(FILENAME_LIST ${FILENAME_LIST}  src/${FILENAME})
ENDFOREACH(SRC_PROG ${SRC_PROGS})

ADD_LIBRARY(${SHARED_TARGET} SHARED ${FILENAME_LIST}) #use all the *.cpp codes to create a library

#enable testing and add subdir 'tests'
SUBDIRS(tests)
ENABLE_TESTING()

