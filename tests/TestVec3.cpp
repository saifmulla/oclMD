//
//  TestVec3.cpp
//  OclMD
//
//  Created by Saif Mulla on 06/03/2015.
//
//

#include <stdio.h>
#include <iostream>
#include <valarray>
#include <list>
#include "oclmd/Vec3.h"
#include "gtest/gtest.h"

using namespace OclMD;

TEST(TestVec3,declare){
    Vec3 xcomponent;
    SUCCEED();
}

TEST(TestVec3,setVals){
    Vec3 xcomponent(0.0098,2.1,1.0);
    ASSERT_EQ(0.0098,xcomponent[0]);
}

TEST(TestVec3,checkdefault){
    Vec3 xcomponent;
    ASSERT_EQ(0.0,xcomponent[0]);
}

TEST(TestVec3,assignment){
    Vec3 xcomponent;
    Vec3 ycomponent(2.0,0.0,0.0);
    xcomponent = ycomponent;
    ASSERT_EQ(ycomponent[0],xcomponent[0]);
}

TEST(TestVec3, checkValArray){
    std::valarray<Vec3> vec3array(10);
    for(int i = 0;i < 10;++i)
    {
        vec3array[i] = Vec3(0.00864,0.653,0.2345);
    }
    SUCCEED();
}

TEST(TestVec3, checkLists){
    std::list<Vec3> vec3array;
    for(int i = 0;i<10;i++)
        vec3array.push_back(Vec3(0.00864,0.653,0.2345));
    SUCCEED();
}

TEST(TestVec3, scalarMultiply){
    Vec3 dim(2.0,0.03,0.023);
    Vec3 scalar = dim * 2.0;
    ASSERT_EQ(4.0,scalar[0]);
}

TEST(TestVec3, multiplication){
    Vec3 x(0.22,0.33,0.44);
    Vec3 y(0.22,0.33,0.44);
    Vec3 z = y * x;
    ASSERT_EQ(0.0484,z[0]);
    ASSERT_EQ(0.22,y[0]);
}

TEST(TestVec3, addition){
    Vec3 x(0.22,0.33,0.44);
    Vec3 y(0.22,0.33,0.44);
    
    Vec3 z = y + x;
    ASSERT_EQ(0.44,z[0]);
    ASSERT_EQ(0.22,y[0]);
}

TEST(TestVec3, addequal){
    Vec3 x(0.22,0.33,0.44);
    Vec3 y(0.22,0.33,0.44);
    
    y += x;
    ASSERT_EQ(0.44,y[0]);
    ASSERT_EQ(0.66,y[1]);
    ASSERT_EQ(0.88,y[2]);
}

TEST(TestVec3, substract){
    Vec3 x(0.22,0.33,0.44);
    Vec3 y(0.22,0.33,0.44);
    
    Vec3 z = y - x;
    ASSERT_EQ(0,z[0]);
    ASSERT_EQ(0.22,y[0]);
}

TEST(TestVec3,negation){
    Vec3 x(0.22,0.33,0.44);
    Vec3 y(0.22,0.33,0.44);
    x += -y;
    ASSERT_EQ(0.0,x[0]);
}

TEST(TestVec3,division){
    Vec3 x(4.0,2,8);
    Vec3 y = x/2;
    ASSERT_EQ(2.0,y[0]);
    ASSERT_EQ(1.0,y[1]);
    ASSERT_EQ(4.0,y[2]);
    
    ASSERT_EQ(4.0,x[0]);
    ASSERT_EQ(2.0,x[1]);
    ASSERT_EQ(8.0,x[2]);
    
}

TEST(TestVec3, magsqr){
    Vec3 x(0.22,0.33,0.44);
    Real expect = 0.0;
    expect += x[0] * x[0];
    expect += x[1] * x[1];
    expect += x[2] * x[2];
    Real magsqr = MagSqr(x);
    ASSERT_EQ(expect,magsqr);
}


TEST(TestVec3, mag){
    Vec3 x(0.22,0.33,0.44);
    Real magsqr = MagSqr(x);
    Real expect = SQRT(magsqr);
    Real mag = Mag(magsqr);
    ASSERT_EQ(expect,mag);
}

/**
 * some tests are commented to enable compilation
 * even if clang compiler is used
 * once openmp clang compiler is installed
 * uncomment these tests
 */
//TEST(TestVec3, omptest){
//    int tid = omp_get_thread_num();
//    int numthreads = omp_get_num_threads();
//    ASSERT_EQ(0,tid);
//    ASSERT_NE(0,numthreads);
//}

TEST(TestVec3, compare){
    Vec3 first(0.22,0.33,0.44);
    Vec3 second(0.22,0.33,0.44);
    if(first == second)
        SUCCEED();
    else
        FAIL();
}

TEST(TestVec3, copy){
    Vec3 copyfrom(0.986,0.53,0.23);
    Vec3 copyTo(copyfrom);
    if(copyfrom == copyTo)
        SUCCEED();
    else
        FAIL();
}

TEST(TestVec3, assign){
    Vec3 copyfrom(0.986,0.53,0.23);
    Vec3 copyTo = copyfrom;
    if(copyfrom == copyTo)
        SUCCEED();
    else
        FAIL();
}

//TEST(TestVec3, ompArray){
//    std::valarray<Vec3> vec3array(100000);
//    for(int i = 0;i < 100000;++i)
//    {
//        vec3array[i] = Vec3(0.00864,0.653,0.2345);
//    }
//    
//#pragma omp parallel default(none) private(vec3array)
//    {
//        for (int j = omp_get_thread_num(); j<100000; j+=omp_get_num_threads()) {
//            vec3array[j] = vec3array[j] * 0.0987;
//        }
//    }
//}

//TEST(TestVec3, ompmalloc){
//    Vec3* mallarray;
//    mallarray = (Vec3*) malloc(sizeof(Vec3)*100000);
//    
//    for(int i = 0;i < 100000;++i)
//        mallarray[i] = Vec3(0.00864,0.653,0.2345);
//    
//#pragma omp parallel default(none) private(mallarray)
//    {
//        for (int j = omp_get_thread_num(); j<100000; j+=omp_get_num_threads()) {
//            mallarray[j] = mallarray[j] * 0.0987;
//        }
//    }
//    
//    delete mallarray;
//    
//}


int main(int argc, char *argv[]){
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}