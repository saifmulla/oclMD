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
 * classname AbstractBases
 * This file contains pure abstract classes which form a framework for classes
 * inheriting from them. Ideally any kind of class will implement certains
 * rules of implementation.
 *
 */

#ifndef OclMD_AbstractBases_h
#define OclMD_AbstractBases_h

#include <string>
#include <vector>
#include "oclmd/BaseImpl.h"
#include "oclmd/RealType.h"
#include "oclmd/Vec3.h"
#include "oclmd/System.h"
#include "oclmd/impl/ContextImpl.h"
#include "oclmd/impl/NonBondedForceImpl.h"


namespace OclMD {

/**
 * classname CaculateForcesAndEnergy
 *
 * This abstract class defines the rules for force 
 * calculation functionality, it starts from initialising
 * all the required datastructure and then two more 
 * pure abstract functions prepare and calculate.
 * prepare - generally will include functionality to make all
 * necessary adjustments such as zeroing forces, creating neighbourhood
 * list etc.
 *
 * calculate - will contain the actual force calculating functionality
 * with all pairwise interactions and collecting updated forces information
 * energy, total energy, virial etc.
 */

class BaseCalculateForcesAndEnergy : public BaseImpl{
public:
    /// function returning the name of the class as string
    static std::string className(){
        return "BaseCaluateForcesAndEnergy";
    }
    
    /// constructor initialising BaseImpl
    BaseCalculateForcesAndEnergy(const Platform& platform, std::string classname)
    : BaseImpl(platform,classname){
        
    }
    
    /**
     *
     * function initialise
     * initialise all the required datastructure this is a pure abstract funtion 
     * and must be implemented in derived class.
     * this functiona is called only once, so should be used to initialise
     * or setup the simulation to enable force calculating functionality
     *
     *
     */
    virtual void initialise(const System& system) = 0;
    
    /**
     *
     * function prepare
     * this is a pure virtual function therefore must be implemented in derived class
     * this function is called just before calculate function, therefore all necessary 
     * adjustments such as zeroing data, creating neighbourhood list should be done in here
     *
     * @param context   Type of contectImplement
     */
    virtual void prepare(ContextImpl& context) = 0;
    
    /**
     * 
     * function calculate
     * This is a pure virtual function theremore must be implemented in derived class
     * it is called for every time step. this is the core kernel where all the pair-wise
     * interaction are implemented and all the force update, energy, virial and potential energy
     * is accumulated
     */
    virtual Real calculate(ContextImpl& context) = 0;
    
};
    
/**
 * classname BaseData
 *
 * This class is an abstract implementation for all the datastructure
 * used to set and get for each platform. This abstract class treats
 * like kindoff a bridge between the API layer and base platforms so
 * that all the datastructure from API should be replicated underneath each 
 * treating platform in its own matter appropriate for that platform. Moreover
 * it also allows each platform having its own independent datastructure. There
 * are pure virtual functions which must be implemented in derived classes.
 */
    
class BaseData : public BaseImpl {
public:
    static std::string className(){
        return "BaseData";
    }
    
    BaseData(const Platform& platform, std::string classname) : BaseImpl(platform,classname){
        
    }
    
    virtual void initialise(const System& system) = 0;
    
    virtual void setPositions(ContextImpl& context, std::vector<Vec3>& positions) = 0;
    
    virtual void getForces(ContextImpl& context, std::vector<Vec3>& forces) = 0;
    
    virtual void setPeriodicBox(ContextImpl& context, const Vec3& x, const Vec3& y, const Vec3& z) const = 0;
    
    virtual void getPeriodicBox(ContextImpl& context, Vec3& x, Vec3& y, Vec3& z) const = 0;
};
 

class BaseCalculateNonBondedForce : public BaseImpl {
public:
    static std::string className(){
        return "BaseCalculateNonBondedForce";
    }
    
    BaseCalculateNonBondedForce(const Platform& platform, std::string name) : BaseImpl(platform,name){
        
    }
    
    virtual void initialise(const System& system, const NonBondedForceImpl& forceImpl) = 0;
    
    virtual Real calculate(ContextImpl& context) = 0;
};
    
}
#endif
