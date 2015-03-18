//
//  TestSystem.cpp
//  OclMD
//
//  Created by Saif Mulla on 11/03/2015.
//
//

#include <stdio.h>
#include <iostream>
#include "System.h"
#include "Vec3.h"
#include "gtest/gtest.h"

using namespace OclMD;

TEST(TestSystem,initialise){
//    Vec3 vec(0.0,0.0,0.0);
    System s;
    SUCCEED();
}

int main(int argc, char *argv[]){
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}
