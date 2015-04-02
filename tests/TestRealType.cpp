//
//  TestRealType.cpp
//  OclMD
//
//  Created by Saif Mulla on 02/04/2015.
//
//

#include <stdio.h>
#include <iostream>
#include "RealType.h"
#include "gtest/gtest.h"


TEST(TestRealType,checksize){
    ASSERT_EQ(REALSIZE,sizeof(Real));
}
int main(int argc, char *argv[]){
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}