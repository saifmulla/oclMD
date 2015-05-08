//
//  TestSolver.cpp
//  OclMD
//
//  Created by Saif Mulla on 08/05/2015.
//
//

#include <stdio.h>
#include <iostream>
#include "gtest/gtest.h"
#include "oclmd/Vec3.h"
#include "oclmd/System.h"
#include "oclmd/Solver.h"
#include "oclmd/NonBondedForce.h"

using namespace OclMD;

TEST(TestSolver, construct){
    System s;
    s.addParticle(1.0);
    s.addCharge(1.0);
    NonBondedForce nbf(1);
    nbf.addLJPair(0.12,0.0034,0.0,0.0,0.1,1,1);
    s.addParticle(2.0);
    s.addForce(&nbf);
    Solver solve(s);
    SUCCEED();
}

int main(int argc, char *argv[]){
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}
