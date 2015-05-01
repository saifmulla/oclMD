#include <stdio.h>
#include <iostream>

#include "mocks/Mock_Platform.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "oclmd/BaseImpl.h"
//#include "oclmd/Platform.h"

using ::testing::AtLeast; 
using namespace OclMD;


TEST(TestPlatform, construct){
    MockPlatform* platform;
    std::string name = "CPU";
    /// using reinterpret_case to simply cast the MockPlatform
    /// pointer to base class platform
    BaseImpl impl(reinterpret_cast<OclMD::Platform&>(platform),
                  name);
}

int main(int argc, char *argv[]){
    ::testing::InitGoogleMock(&argc,argv);
    return RUN_ALL_TESTS();
}