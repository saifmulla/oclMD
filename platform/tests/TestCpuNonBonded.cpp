//
//  TestCpuPlatform.cpp
//  OclMD
//
//  Created by Saif Mulla on 02/04/2015.
//
//

#include <stdio.h>
#include <iostream>
#include "oclmd/Vec3.h"
#include "oclmd/System.h"
#include "oclmd/NonBondedForce.h"
#include "CpuPlatform.h"
#include "oclmd/impl/ContextImpl.h"
#include "gtest/gtest.h"
//#include "gmock/gmock.h"

using namespace OclMD;
using namespace std;

TEST(TestNonBondedIxn,oneatomljpair){
    System system;
    system.addParticle(1.0);
    system.addParticle(1.0);
    NonBondedForce* nb = new NonBondedForce();
    nb->addParticle(1.0,0);
    nb->addLJPair(1.2,1.0,2.0,1.0,1.0,0,0);
    system.addForce(nb);
    CpuPlatform* platform = new CpuPlatform();
    ContextImpl context(system,platform);
    vector<Vec3> positions(2);
    positions[0] = Vec3(0,0,0);
    positions[1] = Vec3(2,0,0);
    context.setPositions(positions);
    
}

int main(int argc, char *argv[]){
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}