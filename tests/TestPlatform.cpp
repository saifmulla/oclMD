#include <stdio.h>
#include <iostream>

//#include "mocks/Mock_Platform.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
//#include "oclmd/BaseImpl.h"
#include "oclmd/Platform.h"

using ::testing::AtLeast; 
using namespace OclMD;


TEST(TestPlatform, construct){
    Platform* platform;
}

int main(int argc, char *argv[]){
    ::testing::InitGoogleMock(&argc,argv);
    return RUN_ALL_TESTS();
}