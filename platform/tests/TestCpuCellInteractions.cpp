#include <stdio.h>
#include <iostream>
#include "oclmd/RealType.h"
#include "oclmd/Vec3.h"
#include "gtest/gtest.h"
#include "CpuCellInteractions.h"
#include <vector>

using namespace OclMD;
using namespace std;

TEST(TestCellInteractions,constructor){
    Vec3 boxDim[3];
    boxDim[0] = Vec3(2.33,0.0,0.0);
    boxDim[1] = Vec3(0.0,2.33,0.0);
    boxDim[2] = Vec3(0.0,0.0,2.33);
    
    CpuCellInteractions* pbc = new CpuCellInteractions(boxDim,2.0);
    ASSERT_EQ(0,pbc->getNumReferredPositions());
    pbc->initialise();
    ASSERT_EQ(1, pbc->nCells());
    ASSERT_EQ(1, pbc->nCellXDim());
    ASSERT_EQ(1, pbc->nCellYDim());
    ASSERT_EQ(1, pbc->nCellZDim());
}

TEST(TestCellInteractions,bitBiggerBox){
    Vec3 boxDim[3];
    boxDim[0] = Vec3(4,0.0,0.0);
    boxDim[1] = Vec3(0.0,4.0,0.0);
    boxDim[2] = Vec3(0.0,0.0,4.0);
    
    CpuCellInteractions* pbc = new CpuCellInteractions(boxDim,2.0);
    ASSERT_EQ(0,pbc->getNumReferredPositions());
    pbc->initialise();
    ASSERT_EQ(8, pbc->nCells());
    ASSERT_EQ(2, pbc->nCellXDim());
    ASSERT_EQ(2, pbc->nCellYDim());
    ASSERT_EQ(2, pbc->nCellZDim());
}

TEST(TestCellInteractions,unevenBiggerBox){
    Vec3 boxDim[3];
    boxDim[0] = Vec3(10.0,0.0,0.0);
    boxDim[1] = Vec3(0.0,20.0,0.0);
    boxDim[2] = Vec3(0.0,0.0,30.0);
    
    CpuCellInteractions* pbc = new CpuCellInteractions(boxDim,3.33);
    ASSERT_EQ(0,pbc->getNumReferredPositions());
    pbc->initialise();
    ASSERT_EQ(3, pbc->nCellXDim());
    ASSERT_EQ(6, pbc->nCellYDim());
    ASSERT_EQ(9, pbc->nCellZDim());
    ASSERT_EQ(162, pbc->nCells());
    
}

TEST(TestCellInteractions, corneringcells){
    Vec3 boxDim[3];
    boxDim[0] = Vec3(8.0,0.0,0.0);
    boxDim[1] = Vec3(0.0,8.0,0.0);
    boxDim[2] = Vec3(0.0,0.0,8.0);
    
    CpuCellInteractions* pbc = new CpuCellInteractions(boxDim,2.0);
    pbc->initialise();
    ASSERT_EQ(40, pbc->getTotalCornerCells());
    const int* rightcells = pbc->getRightSideCellIndexes();
//    const int ncellsleft = pbc->getnCellsRight();
//    ASSERT_EQ(12, ncellsleft);
    for (int i = 0; i<pbc->getnCellsRight(); i++) {
        cout << i << " => " << rightcells[i] << endl;
    }
    const int* cornercells = pbc->getCorneringCellIndexes();
    for (int j = 0; j < pbc->getTotalCornerCells(); j++) {
        cout << j << " => " << cornercells[j] << endl;
    }
}


int main(int argc, char *argv[]){
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}