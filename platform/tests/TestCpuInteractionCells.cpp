#include <stdio.h>
#include <iostream>
#include "oclmd/RealType.h"
#include "oclmd/Vec3.h"
#include "gtest/gtest.h"
#include "CpuInteractionCells.h"
#include <vector>

using namespace OclMD;
using namespace std;


int main(int argc, char *argv[]){
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}