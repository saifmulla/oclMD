#include <stdio.h>
#include <iostream>
#include <vector>
#include "oclmd/Vec3.h"
//#include "oclmd/System.h"
//#include "oclmd/NonBondedForce.h"
#include "CpuPlatform.h"
//#include "oclmd/impl/ContextImpl.h"
#include "gtest/gtest.h"


using namespace OclMD;

TEST(TestCpuPlatform, constructor){
    CpuPlatform* platform = new CpuPlatform();
    ASSERT_TRUE(platform->supportsDoublePrecision());
}

TEST(TestCpuPlatform, platformData){
    CpuPlatform::PlatformData* data = new CpuPlatform::PlatformData(1);
    CpuPlatform::PlatformData* staticdata(new CpuPlatform::PlatformData(10));
    delete data;
    delete staticdata;
}

TEST(TestCpuPlatform, platformdata_stepcount){
    CpuPlatform::PlatformData* data = new CpuPlatform::PlatformData(2);
    ASSERT_EQ(0,data->stepCount_);
    std::vector<Vec3>* pos = static_cast<std::vector<Vec3>*>(data->positions_);
    ASSERT_EQ(2,pos->size());
    delete data;
}



int main(int argc, char *argv[]){
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}