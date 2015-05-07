//
//  TestCpuPlatform.cpp
//  OclMD
//
//  Created by Saif Mulla on 02/04/2015.
//
//

#include <stdio.h>
#include <iostream>
#include "oclmd/RealType.h"
#include "oclmd/Vec3.h"
#include "oclmd/System.h"
#include "oclmd/NonBondedForce.h"
#include "CpuPlatform.h"
#include "oclmd/impl/ContextImpl.h"
#include "gtest/gtest.h"
//#include "gmock/gmock.h"
#include <vector>


using namespace OclMD;
using namespace std;

TEST(TestNonBondedIxn,oneatomljpair){
    System system;
    system.addParticle(1.0);
    system.addParticle(1.0);
    NonBondedForce* nb = new NonBondedForce();
    nb->addParticle(1.0,0);
    nb->addLJPair(1.2,1.0,2.0,1.0,1.0,0,0);
//    nb->addLJPair(1.4,2.0,2.0,1.0,1.0,0,0);
    system.addForce(nb);
    CpuPlatform* platform = new CpuPlatform();
    ContextImpl context(system,platform);
    vector<Vec3> positions(2);
    positions[0] = Vec3(0,0,0);
    positions[1] = Vec3(2,0,0);
    context.setPositions(positions);
    context.CalculateForcesandEnergy();
    
    vector<Vec3> forces(2);
    context.getForces(forces);
    vector<double> pe(2);
    context.getPotentialEnergy(pe);
    vector<Tensor<double> > virial(2);
    context.getVirial(virial);
    
    /// calculate force equation
    Vec3 diff = positions[1] - positions[0];
    Real MagSqr = 0.0;
    MagSqr += diff[0] * diff[0];
    MagSqr += diff[1] * diff[1];
    MagSqr += diff[2] * diff[2];
    
    Real mag = SQRT(MagSqr);
    Real num1 = -48 * 1.0 * POW(1.2,12);
    num1 /= POW(mag,13);
    Real num2 = 24 * 1.0 * POW(1.2,6);
    num2 /= POW(mag,7);
    Real force = num1 + num2;
    force *= mag;
    Vec3 expectForce = diff/force;
    
    /// test force equation with resultant forces
    EXPECT_DOUBLE_EQ(-expectForce[0],forces[0][0]);
    EXPECT_DOUBLE_EQ(expectForce[1],forces[0][1]);
    EXPECT_DOUBLE_EQ(expectForce[2],forces[0][2]);
    EXPECT_DOUBLE_EQ(expectForce[0],forces[1][0]);
    EXPECT_DOUBLE_EQ(expectForce[1],forces[1][1]);
    EXPECT_DOUBLE_EQ(expectForce[2],forces[1][2]);
    
    ///calculate energy equation to test calculated values
    
    Real e1 = POW(1.2,12)/POW(mag,12);
    e1 -= (POW(1.2,6) / POW(mag,6));
    Real expectpe = e1 * (4.0 * 1.0 * 0.5);
    /// compare result
    EXPECT_DOUBLE_EQ(expectpe,pe[0]);
    EXPECT_DOUBLE_EQ(expectpe,pe[1]);
    
    std::cout << "V0 => " << virial[0] << std::endl;
    std::cout << "V1 => " << virial[1] << std::endl;
    
    
    
    
}

int main(int argc, char *argv[]){
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}