//
//  TestContextImplement.cpp
//  OclMD
//
//  Created by Saif Mulla on 27/04/2015.
//
//

#include <stdio.h>
#include <iostream>
//#include "mocks/Mock_Platform.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "oclmd/Vec3.h"
#include "oclmd/impl/ContextImpl.h"
//#include "CpuPlatform.h"
#include "oclmd/System.h"
#include "oclmd/NonBondedForce.h"

using namespace OclMD;

TEST(TestContextImpl, construct){
    System s;
    NonBondedForce nbf(1);
    nbf.addLJPair(0.12,0.0034,0.0,0.0,0.1,1,1);
    s.addParticle(2.0);
    s.addForce(&nbf);
//    MockPlatform* cpu = new CpuPlatform();
//    OclMD::ContextImpl context(s,cpu);
    SUCCEED();
}

int main(int argc, char *argv[]){
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}