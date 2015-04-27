//
//  TestContextImplement.cpp
//  OclMD
//
//  Created by Saif Mulla on 27/04/2015.
//
//

#include <stdio.h>
#include <iostream>
#include "Vec3.h"
#include "gtest/gtest.h"
#include "ContextImpl.h"
#include "CpuPlatform.h"
#include "System.h"
#include "NonBondedForce.h"

using namespace OclMD;

TEST(TestContextImpl, construct){
    System s;
    NonBondedForce nbf(1);
    nbf.addLJPair(0.12,0.0034,0.0,0.0,0.1,1,1);
    s.addParticle(2.0);
    s.addForce(&nbf);
    CpuPlatform* cpu = new CpuPlatform();
    OclMD::ContextImpl context(s,cpu);
    SUCCEED();
}

int main(int argc, char *argv[]){
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}