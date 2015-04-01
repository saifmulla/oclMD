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
    NonBondedForce nbf;
//    nbf.getCutOffDistance();
    ASSERT_EQ(0.0,nbf.getCutOffDistance());
    NonBondedForce::NonBondedMethods method = nbf.getNonBondedMethod();
}


int main(int argc, char *argv[]){
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}

