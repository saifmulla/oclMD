//
//  TestTensor.cpp
//  OclMD
//
//  Created by Saif Mulla on 04/04/2015.
//
//

#include <stdio.h>
#include "Tensor.h"
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


int main(int argc, char *argv[]){
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}
