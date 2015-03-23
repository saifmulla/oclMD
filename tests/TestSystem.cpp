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
    System s;
    ASSERT_EQ(1,s.getMoleculeSize());
}

TEST(TestSystem, paramConstructor){
    Vec3 dimensions[3];
    dimensions[0][0] = 0.098;
    dimensions[1][0] = 0.098;
    dimensions[2][0] = 0.098;
    System s(dimensions,10,1);
    ASSERT_EQ(10,s.getNumParticles());
    Vec3 dimensions2[3];
    s.getDimensions(dimensions2[0],dimensions2[1],dimensions2[3]);
    ASSERT_EQ(dimensions[0][0],dimensions2[0][0]);
}

TEST(TestSystem, moleculemass){
    System s;
    s.setMoleculeMass(0,0.7653);
    ASSERT_EQ(0.7653,s.getMoleculeMass(0));
}

int main(int argc, char *argv[]){
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}
