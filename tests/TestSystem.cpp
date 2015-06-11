//
//  TestSystem.cpp
//  OclMD
//
//  Created by Saif Mulla on 11/03/2015.
//
//

#include <stdio.h>
#include <iostream>
#include "oclmd/System.h"
//#include "NonBondedForce.h"
#include "oclmd/Vec3.h"
#include "gtest/gtest.h"

using namespace OclMD;

TEST(TestSystem,initialise){
    System s;
    ASSERT_EQ(1,s.getMoleculeSize());
}

TEST(TestSystem, paramConstructor){
    Vec3 dimensions[3];
    dimensions[0][0] = 0.098;
    dimensions[1][0] = 0.098;
    dimensions[2][0] = 0.098;
    System s(dimensions,1);
    //    ASSERT_EQ(10,s.getNumParticles());
    Vec3 dimensions2[3];
    s.getDimensions(dimensions2[0],dimensions2[1],dimensions2[2]);
    ASSERT_EQ(dimensions[0][0],dimensions2[0][0]);
}

TEST(TestSystem, paramConstructor2){
    std::vector<std::vector<int> > dil(2);
    System s(dil,dil,2,4);
}

TEST(TestSystem, getterFunctions){
    std::vector<std::vector<int> > dil(2);
    dil[0].push_back(0);
    dil[0].push_back(1);
    dil[1].push_back(2);
    dil[1].push_back(3);
    
    System s(dil,dil,2,2);
    
    ASSERT_EQ(2, s.getnCells());
    ASSERT_EQ(2, s.getnRefCells());
    
    const std::vector<std::vector<int> >& tempdil = s.getDil();
    ASSERT_EQ(0, dil[0][0]);
    ASSERT_EQ(3, dil[1][1]);
    const std::vector<std::vector<int> >& tempneighbours = s.getNeighbouringCells();
    ASSERT_EQ(1, dil[0][1]);
    ASSERT_EQ(2, dil[1][0]);
    
}

TEST(TestSystem, addForce){
    System s;
    //NonBondedForce *nb;
    //s.addForce(nb);
//    ASSERT_EQ(1,s.getNumForces());
}


int main(int argc, char *argv[]){
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}
