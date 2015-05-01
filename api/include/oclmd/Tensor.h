/**
 * @file
 * @author Saif Mulla <s.mulla@ed.ac.uk>
 * @version 1.0
 *
 * @section LICENSE
 *
 *
 * @section DESCRIPTION
 *
 * classname Tensor
 * This class represents a nine component tensor, to represent datastructure
 * primarily for pressure calculation and rotation of each molecule for
 * polyAtomic simulations
 */

#include <cassert>
#include "oclmd/RealType.h"
#include "oclmd/Vec3.h"
#include "oclmd/OclMDException.h"

#ifndef OclMD_Tensor_h
#define OclMD_Tensor_h

namespace OclMD {
    
template <class Type>
class Tensor {
private:
    Type data_[9];
public:
    /// default constructor with no values
    Tensor(){
        data_[0] = data_[1] = data_[2] = data_[3] = data_[4] = data_[5] = data_[6] = data_[7] = data_[8] = REALVAL;
    }
    // parameterised constructor
    Tensor(Type xx,Type xy,Type xz,Type yx,Type yy,Type yz,Type zx,Type zy,Type zz){
        data_[0] = xx;
        data_[1] = xy;
        data_[2] = xz;
        data_[3] = yx;
        data_[4] = yy;
        data_[5] = yz;
        data_[6] = zx;
        data_[7] = zy;
        data_[8] = zz;
    }
    
    // user defined copy constructor
    Tensor(const Tensor<Type>& rhs){
        this->data_[0] = rhs.data_[0];
        this->data_[1] = rhs.data_[1];
        this->data_[2] = rhs.data_[2];
        this->data_[3] = rhs.data_[3];
        this->data_[4] = rhs.data_[4];
        this->data_[5] = rhs.data_[5];
        this->data_[6] = rhs.data_[6];
        this->data_[7] = rhs.data_[7];
        this->data_[8] = rhs.data_[8];
    }
    
    /// assignment operator overloaded
    Tensor operator=(const Tensor<Type>& rhs){
        this->data_[0] = rhs.data_[0];
        this->data_[1] = rhs.data_[1];
        this->data_[2] = rhs.data_[2];
        this->data_[3] = rhs.data_[3];
        this->data_[4] = rhs.data_[4];
        this->data_[5] = rhs.data_[5];
        this->data_[6] = rhs.data_[6];
        this->data_[7] = rhs.data_[7];
        this->data_[8] = rhs.data_[8];
    }
    
    // index operator overloading
    Type operator[](const int index) const {
        if(index>=0 && index<9)
            return data_[index];
        else
            throw OclMDException("Tensor: Array Index out of bound operator[]");
    }
    
    Type& operator[](const int index) {
        //        assert(index>=0 && index<9);
        if(index>=0 && index<9)
            return data_[index];
        else
            throw OclMDException("Tensor: Array Index out of bound operator[]");
    }
    
    Tensor operator+=(const Tensor& rhs){
        data_[0] += rhs[0];
        data_[1] += rhs[1];
        data_[2] += rhs[2];
        data_[3] += rhs[3];
        data_[4] += rhs[4];
        data_[5] += rhs[5];
        data_[6] += rhs[6];
        data_[7] += rhs[7];
        data_[8] += rhs[8];
    }
    
    /// accessor functions
    
    Type xx(){
        return data_[0];
    }
    
    friend Tensor<Type> operator*(Vec3& v1,Vec3& v2){
        return Tensor<Type>(
                            v1[0]*v2[0],v1[0]*v2[1],v1[0]*v2[2],
                            v1[1]*v2[0],v1[1]*v2[1],v1[1]*v2[2],
                            v1[2]*v2[0],v1[2]*v2[1],v1[2]*v2[2]
                            );
    }
};
    
// outer-product between two vectors
template <class T>
Tensor<T> outerProduct(const Vec3& v1,const Vec3& v2){
    return Tensor<T>(
                     v1[0]*v2[0],v1[0]*v2[1],v1[0]*v2[2],
                     v1[1]*v2[0],v1[1]*v2[1],v1[1]*v2[2],
                     v1[2]*v2[0],v1[2]*v2[1],v1[2]*v2[2]
                     );
}
    
}//end namespace OclMD
#endif
