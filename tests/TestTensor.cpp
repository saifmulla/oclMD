//
//  TestTensor.cpp
//  OclMD
//
//  Created by Saif Mulla on 04/04/2015.
//
//

#include <stdio.h>
#include "oclmd/Vec3.h"
#include "oclmd/Tensor.h"
#include "gtest/gtest.h"

using namespace OclMD;

TEST(TestTensor,constructor){
    Tensor<double> t;
    SUCCEED();
}

TEST(TestTensor,paramconstructor){
    Tensor<double> t(0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0);
    ASSERT_EQ(0.0,t[0]);
}

TEST(TestTensor,copyconstruct){
    Tensor<double> t(1.0,0.0,0.0,0.0,0.0,5.0,0.0,0.0,0.0);
    Tensor<double> copy(t);
    ASSERT_EQ(t[5],copy[5]);
}

TEST(TestTensor,assignment){
    Tensor<double> t(0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.000465);
    Tensor<double> assin = t;
    ASSERT_EQ(t[8],assin[8]);
}

TEST(TestTensor,assignment2){
    Tensor<double> t(0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.000465);
    t[6] = 0.002987;
    ASSERT_EQ(0.002987,t[6]);
}

TEST(TestTensor,vectors){
    std::vector<Tensor<double> > t(10);
}

TEST(TestTensor,outerproduct){
    Vec3 x(2.0,3.0,4.0);
    Vec3 y(2.0,3.0,4.0);
    Tensor<double> t = outerProduct<double>(x,y);
    ASSERT_EQ(6.0,t[1]);
}

TEST(TestTensor, plusadd){
    Tensor<double> t1(0.245,0.986,0.2,0.0,0.0,0.0,0.0,0.0,0.000465);
    Tensor<double> t2(0.245,0.986,0.2,0.0,0.0,0.0,0.0,0.0,0.000465);
    t1 += t2;
    ASSERT_EQ(0.4,t1[2]);
    ASSERT_EQ(1.972,t1[1]);
    
}

int main(int argc, char *argv[]){
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}
