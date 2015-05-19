#include "OmpBases.h"


static std::vector<OclMD::Vec3>& extractPositions(OclMD::ContextImpl& context){
    OclMD::OmpPlatform::PlatformData* data = reinterpret_cast<OclMD::OmpPlatform::PlatformData*>(context.getPlatformData());
    return *((std::vector<OclMD::Vec3>*) data->positions_);
}

static std::vector<OclMD::Vec3>& extractForces(OclMD::ContextImpl& context){
    OclMD::OmpPlatform::PlatformData* data = reinterpret_cast<OclMD::OmpPlatform::PlatformData*>(context.getPlatformData());
    return *((std::vector<OclMD::Vec3>*) data->forces_);
}

static std::vector<OclMD::Tensor<double> >& extractVirial(OclMD::ContextImpl& context){
    OclMD::OmpPlatform::PlatformData* data = reinterpret_cast<OclMD::OmpPlatform::PlatformData*>(context.getPlatformData());
    return *((std::vector<OclMD::Tensor<double> >*) data->virial_);
}

static std::vector<double>& extractPE(OclMD::ContextImpl& context){
    OclMD::OmpPlatform::PlatformData* data = reinterpret_cast<OclMD::OmpPlatform::PlatformData*>(context.getPlatformData());
    return *((std::vector<double>*) data->pE_);
}

static OclMD::Vec3& extractBoxDimensions(OclMD::ContextImpl& context){
    OclMD::OmpPlatform::PlatformData* data = reinterpret_cast<OclMD::OmpPlatform::PlatformData*>(context.getPlatformData());
    return *(OclMD::Vec3*) data->periodicBoxSize_;
}

void OclMD::OmpBaseCalculateForcesAndEnergy::initialise(const System& system){
#ifdef FULLDEBUG
    std::cout << "Initialising OmpBaseCalculateForcesAndEnergy" << std::endl;
#endif
}

void OclMD::OmpBaseCalculateForcesAndEnergy::prepare(ContextImpl& context){
#ifdef FULLDEBUG
    std::cout << "prepare on OmpBaseCalculateForcesAndEnergy" << std::endl;
#endif
    /// zero all data structure
    std::vector<OclMD::Vec3>& forces = extractForces(context);
    std::vector<OclMD::Tensor<double> >& virial = extractVirial(context);
    std::vector<double>& pe = extractPE(context);
    
    for (int i = 0; i <context.getSystem().getNumParticles(); i++) {
        forces[i] = OclMD::Vec3(0.0,0.0,0.0);
        virial[i] = OclMD::Tensor<double>(0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0);
        pe[i] = 0.0;
    }
}

Real OclMD::OmpBaseCalculateForcesAndEnergy::calculate(ContextImpl& context){
#ifdef FULLDEBUG
    std::cout << "calculating OmpBaseCalculateForcesAndEnergy" << std::endl;
#endif
    return 0.0;
}

/// definition of class OmpBaseData

void OclMD::OmpBaseData::initialise(const System& system){
    
}

void OclMD::OmpBaseData::setPositions(ContextImpl& context,
                                      const std::vector<Vec3>& positions){
#ifdef FULLDEBUG
    std::cout << "setting positions on OmpBaseData" << std::endl;
#endif
    
    int numparticles = context.getSystem().getNumParticles();
    std::vector<OclMD::Vec3>& dataPositions = extractPositions(context);
    for(int i = 0; i < numparticles; i++){
        dataPositions[i] = positions[i];
    }
    
}

void OclMD::OmpBaseData::getForces(ContextImpl& context,
                                   std::vector<Vec3>& forces){
    int numparticles = context.getSystem().getNumParticles();
    std::vector<OclMD::Vec3>& dataForces = extractForces(context);
    for (int i = 0; i < numparticles; i++) {
        forces[i] = dataForces[i];
    }
    
}

void OclMD::OmpBaseData::getVirial(OclMD::ContextImpl& context, std::vector<OclMD::Tensor<double> >& virial){
    int numparticles = context.getSystem().getNumParticles();
    std::vector<OclMD::Tensor<double> >& dataVirial = extractVirial(context);
    for (int i = 0; i < numparticles; i++) {
        virial[i] = dataVirial[i];
    }
}

void OclMD::OmpBaseData::getPotentialEnergy(OclMD::ContextImpl& context, std::vector<double>& pe){
    int numparticles = context.getSystem().getNumParticles();
    std::vector<double>& dataPE = extractPE(context);
    for (int i = 0; i < numparticles; i++) {
        pe[i] = dataPE[i];
    }
}


void OclMD::OmpBaseData::setPeriodicBox(ContextImpl& context,
                                        const Vec3& x, const Vec3& y, const Vec3& z) const {
    OclMD::Vec3& boxdim = extractBoxDimensions(context);
    boxdim[0] = x[0]; //x axis;
    boxdim[1] = y[1]; //y axis;
    boxdim[2] = z[2]; //z axis;
}

void OclMD::OmpBaseData::getPeriodicBox(ContextImpl& context,
                                        Vec3& x, Vec3& y, Vec3& z) const {
    
};


/// definition for class OmpCalculateNonBondedForceBase
void OclMD::OmpBaseCalculateNonBondedForce::initialise(const System& system,
                                                       const NonBondedForceImpl& force)
{
#ifdef FULLDEBUG
    std::cout << "Initialising on OmpBaseCalculateNonBondedForce" << std::endl;
#endif
    nonbondedixn = new OclMD::OmpNonBondedIxn((const OclMD::NonBondedForceImpl::LJInfo**) force.getLJInfo());
}

Real OclMD::OmpBaseCalculateNonBondedForce::calculate(ContextImpl& context)
{
#ifdef FULLDEBUG
    std::cout << "calculate on OmpBaseCalculateNonBondedForce" << std::endl;
#endif
    
    nonbondedixn->calculateForces(context.getSystem().getNumParticles(),
                                  extractPositions(context),
                                  extractForces(context),
                                  extractPE(context),
                                  extractVirial(context));
    
    return 0.0;
}