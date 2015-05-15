#include <stdio.h>
#include <iostream>
#include <vector>
#include "oclmd/Vec3.h"
#include "mocks/MockOmpPlatform.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::AtLeast;
using namespace OclMD;

TEST(TestOmpPlatform, constructor){
    MockOmpPlatform platform;
}

TEST(TestOmpPlatform, supportsDoublePrecision){
    MockOmpPlatform platform;
    EXPECT_CALL(platform,supportsDoublePrecision())
    .WillRepeatedly(::testing::Return(true));
    EXPECT_TRUE(platform.supportsDoublePrecision());
}

TEST(TestOmpPlatform, getName){
    MockOmpPlatform platform;
    std::string value = "omp";
    ::testing::DefaultValue<const std::string&>::Set(value);
    EXPECT_CALL(platform,getName());
    EXPECT_EQ("omp", platform.getName());
}

int main(int argc, char *argv[]){
    ::testing::InitGoogleMock(&argc,argv);
    return RUN_ALL_TESTS();
}