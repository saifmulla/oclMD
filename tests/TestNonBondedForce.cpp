//
//  TestNonBondedForce.cpp
//  OclMD
//
//  Created by Saif Mulla on 01/04/2015.
//
//

#include <stdio.h>
#include <iostream>
#include <vector>
#include "oclmd/Vec3.h"
#include "oclmd/NonBondedForce.h"
#include "gtest/gtest.h"

using namespace OclMD;

TEST(TestNBF,initialise){
    NonBondedForce nbf(1);
//    nbf.getCutOffDistance();
    ASSERT_EQ(2.0,nbf.getCutOffDistance());
    NonBondedForce::NonBondedMethods method = nbf.getNonBondedMethod();
    if(method)
        SUCCEED();
    else
        FAIL();
}


TEST(TestNBF,LJPairs){
    NonBondedForce::LJPairs lpairs(0.12,0.0034,0.0,0.0,0.1,1,1);
    ASSERT_EQ(0.12,lpairs.sigma_);
}

TEST(TestNBF,ParticleInfo){
    Vec3 vector(0.12,0.6,0.3);
    NonBondedForce::ParticleInfo minfo(vector,6.39,3.12,1.0,1,0);
    ASSERT_EQ(6.39,minfo.siteMass_);
    ASSERT_FALSE(minfo.frozen_);
}

TEST(TestNBF, addLJPair){
    NonBondedForce nbf(1);
    int size = nbf.addLJPair(0.12,0.0034,0.0,0.0,0.1,1,1);
    ASSERT_EQ(1,size);
    size = nbf.addLJPair(0.12,0.0034,2.0,2.0,0.1,1,1);
    ASSERT_EQ(2,size);
    
    std::vector<NonBondedForce::LJPairs> info = nbf.getListLJPairs();
    NonBondedForce::LJPairs& temp = info[1];
    Real rcutsqr = temp.rCutSqr_;
    ASSERT_EQ(4.0,rcutsqr);
}

TEST(TestNBF, checkImpl){
    NonBondedForce nbf(1);
    int size = nbf.addLJPair(0.12,0.0034,0.0,0.0,0.1,1,1);
    ASSERT_EQ(1,size);
    size = nbf.addLJPair(0.12,0.0034,2.0,2.0,0.1,1,1);
    ASSERT_EQ(2,size);
//    ForceImpl* tempforce = static_cast<ForceImpl*>(nbf.createImpl());
//    tempforce->initialise();
}

TEST(TestNBF,addParticle){
    NonBondedForce nbf(1);
    nbf.addParticle(6.39,1);
//    nbf.addParticle(6.39,Vec3(0.0,0.0,0.0),3.12,1,1);
}


int main(int argc, char *argv[]){
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}

