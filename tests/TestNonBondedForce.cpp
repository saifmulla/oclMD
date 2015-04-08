//
//  TestNonBondedForce.cpp
//  OclMD
//
//  Created by Saif Mulla on 01/04/2015.
//
//

#include <stdio.h>
#include <iostream>
#include "NonBondedForce.h"
#include "gtest/gtest.h"

using namespace OclMD;

TEST(TestNBF,initialise){
    NonBondedForce nbf(1);
//    nbf.getCutOffDistance();
    ASSERT_EQ(2.0,nbf.getCutOffDistance());
    NonBondedForce::NonBondedMethods method = nbf.getNonBondedMethod();
}

TEST(TestNBF,LJPairs){
    NonBondedForce::LJPairs lpairs(0.12,0.0034,0.0,0.0,0.1,1,1);
    ASSERT_EQ(0.12,lpairs.sigma_);
}
int main(int argc, char *argv[]){
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}

