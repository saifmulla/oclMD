#include<cassert>
#include <iostream>
#include "RealType.h"
#include "OclMDException.h"

#ifndef OclMD_Vec3_h
#define OclMD_Vec3_h

namespace OclMD {
    
class Vec3{
private:
    Real data_[3];
    
public:
    Vec3(){
        data_[0] = data_[1] = data_[2] = 0.0;
    }
    
    Vec3(Real x, Real y, Real z){
        data_[0] = x;
        data_[1] = y;
        data_[2] = z;
    }
    
    //copy constructor
    Vec3(const Vec3& copyme){
        data_[0] = copyme.data_[0];
        data_[1] = copyme.data_[1];
        data_[2] = copyme.data_[2];
    }
    
    Real operator[](const int index) const {
        if(index>=0 && index<3)
            return data_[index];
        else
            throw OclMDException("Vec3:: Array out of bound operator[]");
    }
    
    Real& operator[](const int index) {
        if(index>=0 && index<3)
            return data_[index];
        else
            throw OclMDException("Vec3:: Array out of bound operator[]");
    }
    
    Vec3& operator=(const Vec3& lhs){
        /**
         * for safety of self assignment while assignment operator
         * overloading, check address of this object and parameter
         * if they are same simply return this pointer or else
         * do manual assignment for a different object
         */
        if(this == &lhs)
            return *this;
        
        data_[0] = lhs.data_[0];
        data_[1] = lhs.data_[1];
        data_[2] = lhs.data_[2];
        
        return *this;
    }
    
    Vec3 operator*(const Vec3& rhs) {
        return Vec3(data_[0] * rhs.data_[0],data_[1] * rhs.data_[1],data_[2] * rhs.data_[2]);
    }
    
    //equal operator
    bool operator==(const Vec3& rhs){
        return (data_[0] == rhs[0] && data_[1] == rhs[1] && data_[2] == rhs[2]);
    }
    
    /// addition operator
    Vec3 operator+(const Vec3& rhs){
        return Vec3(data_[0] + rhs.data_[0],data_[1] + rhs.data_[1],data_[2] + rhs.data_[2]);
    }
    
    /// substraction operator
    Vec3 operator-(const Vec3& rhs){
        return Vec3(data_[0] - rhs.data_[0],data_[1] - rhs.data_[1],data_[2] - rhs.data_[2]);
    }
    
    /// division operator
    Vec3 operator/(const Real divisor){
        return Vec3(data_[0]/divisor,data_[1]/divisor,data_[2]/divisor);
    }
    
    /// addition equal operator or plus-equal operator
    Vec3 operator+=(const Vec3& rhs){
        data_[0] += rhs.data_[0];
        data_[1] += rhs.data_[1];
        data_[2] += rhs.data_[2];
        return *this;
    }
    
    /// multiply add operator with scalar
    Vec3 operator*=(const Real val){
        data_[0] *= val;
        data_[1] *= val;
        data_[2] *= val;
        return *this;
    }
    
    // negation operator
    // to be worked on expressions such as v += -v2
    Vec3 operator-() const {
        Vec3 v;
        v.data_[0] = -data_[0];
        v.data_[1] = -data_[1];
        v.data_[2] = -data_[2];
        return v;
    }
    //scalar product
    Vec3 operator*(const Real scalar){
        const Vec3& lhs = *this;
        return Vec3(lhs[0]*scalar, lhs[1]*scalar, lhs[2]*scalar);
    }
    
    std::ostream& write(std::ostream& os) const {
        return os << "[ " << data_[0] << ", " << data_[1] << ", " << data_[2] << " ]";
    }
    
    ~Vec3(){}
    
};//end class

inline std::ostream& operator<<(std::ostream& os, const Vec3& vec) {
    return vec.write(os);
}
    
inline Real MagSqr(Vec3& data){
    Real sum = 0.0;
    sum += data[0] * data[0];
    sum += data[1] * data[1];
    sum += data[2] * data[2];
    return sum;
}

inline Real Mag(Real magsqr){
    return std::SQRT(magsqr);
}
    
}//end namespace
#endif
