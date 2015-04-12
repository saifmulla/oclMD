//
//  TestCpuPlatform.cpp
//  OclMD
//
//  Created by Saif Mulla on 02/04/2015.
//
//

#include <stdio.h>
#include <iostream>
#include "CpuNonBondedIxn.h"
#include "gtest/gtest.h"

using namespace OclMD;
using namespace std;

TEST(TestNonBondedIxn,constructor){
    OclMD::CpuNonBondedIxn cpunonbonded;
    std::vector<Vec3> positions(2);
    std::vector<Vec3> forces(2);
    std::vector<Real> pe(2);
    std::vector<Tensor<double> > virial(2);
    cpunonbonded.calculateForces(2,positions,forces,pe,virial);
}

int main(int argc, char *argv[]){
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}