//
//  TestCpuPlatform.cpp
//  OclMD
//
//  Created by Saif Mulla on 02/04/2015.
//
//

#include <stdio.h>
#include <iostream>
#include "CpuPlatform.h"
#include "gtest/gtest.h"


TEST(TestCpuPlatform,constructor){
    OclMD::CpuPlatform cpu;
}

TEST(TestCpuPlatform,support){
    OclMD::CpuPlatform cpu;
    ASSERT_TRUE(cpu.supportsDoublePrecision());
}

TEST(TestCpuPlatform,name){
    OclMD::CpuPlatform cpu;
    ASSERT_EQ("CPU",cpu.getName());
}


TEST(TestCpuPlatform,platformdata){
    OclMD::CpuPlatform::PlatformData platformdata(10);
    ASSERT_EQ(10,platformdata.numParticles_);
}
int main(int argc, char *argv[]){
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}