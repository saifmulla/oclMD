#include <stdio.h>
#include <iostream>
#include <vector>
#include "oclmd/Vec3.h"
#include "OmpPlatform.h"
#include "OmpBaseFactory.h"
#include "gtest/gtest.h"

using namespace OclMD;

TEST(TestOmpPlatform, constructor){
    OmpPlatform* platform = new OmpPlatform();
    OmpBaseFactory* factory = new OmpBaseFactory();
}


TEST(TestOmpPlatform, supportsDoublePrecision){
    OmpPlatform* platform = new OmpPlatform();
    EXPECT_TRUE(platform->supportsDoublePrecision());
}

TEST(TestOmpPlatform, getName){
    OmpPlatform* platform = new OmpPlatform();
    ASSERT_EQ("OMP", platform->getName());
}

TEST(TestOmpPlatform, platformData){
    OmpPlatform::PlatformData* data = new OmpPlatform::PlatformData(1);
    ASSERT_EQ(1,data->numParticles_);
}

TEST(TestOmpPlatform, deletePlatformData){
    OmpPlatform::PlatformData* data = new OmpPlatform::PlatformData(1);
    delete data;
}

TEST(TestOmpPlatform, openmpthreads){
    OmpPlatform::PlatformData* data = new OmpPlatform::PlatformData(1);
    ASSERT_EQ(omp_get_num_threads(),data->numThreads_);
}


int main(int argc, char *argv[]){
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}


