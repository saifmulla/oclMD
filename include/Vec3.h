//
//  Vec3.h
//  OclMD
//
//  Created by Saif Mulla on 06/03/2015.
//
//

#ifndef OclMD_Vec3_h
#define OclMD_Vec3_h

namespace OclMD {

class Vec3{
private:
    double data_[3];
    
public:
    Vec3(){
        data_[0] = data_[1] = data_[2] = 0.0;
    }
    
    Vec3(double x, double y, double z){
        data_[0] = x;
        data_[1] = y;
        data_[2] = z;
    }
    
    //copy constructor to disable default copy
    Vec3(const Vec3& copyme){
        data_[0] = copyme[0];
	data_[1] = copyme[1];
	data_[2] = copyme[2];
    }
    
    Vec3 operator=(const Vec3& lhs){
        data_[0] = lhs[0];
	data_[1] = lhs[1];
	data_[2] = lhs[2];
    }
    
    double operator[](int index) const{
        if(index>=0 && index<3)
            return data_[index];
        else
            return data_[0];
    }
    
    //scalar product
    Vec3 operator*(double scalar) const {
        const Vec3& lhs = *this;
        return Vec3(lhs[0]*scalar,lhs[1]*scalar,lhs[2]*scalar);
    }
    
    Vec3 operator*=(Vec3& rhs) {
        data_[0] *= rhs[0];
        data_[1] *= rhs[1];
        data_[2] *= rhs[2];
        return *this;
    }
    //equal operator
    bool operator==(Vec3& rhs){
        return (data_[0] == rhs[0] && data_[1] == rhs[1] && data_[2] == rhs[2]);
    }
    
    ~Vec3(){}
    
};//end class
    
}//end namespace
#endif
