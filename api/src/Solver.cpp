#include "oclmd/Solver.h"
#include "oclmd/impl/ContextImpl.h"
#include "oclmd/RealType.h"
#include "oclmd/Vec3.h"


OclMD::Solver::Solver(System& system){
    impl = new OclMD::ContextImpl(*this,system,0);
}

OclMD::Solver::Solver(System& system, Platform* platform){
    impl = new OclMD::ContextImpl(*this,system,platform);
}
OclMD::Solver::~Solver(){
    delete impl;
}
OclMD::System& OclMD::Solver::getSystem() const{
    return impl->getSystem();
}

const OclMD::Platform& OclMD::Solver::getPlatform() const {
    return impl->getPlatform();
}

OclMD::Platform& OclMD::Solver::getPlatform() {
    return impl->getPlatform();
}

void OclMD::Solver::setPositions(const std::vector<Vec3>& positions){
    impl->setPositions(positions);
}

void OclMD::Solver::getForces(std::vector<Vec3>& forces){
    impl->getForces(forces);
}

void OclMD::Solver::getVirial(std::vector<Tensor<double> >& virial){
    impl->getVirial(virial);
}

void OclMD::Solver::getPotentialEnergy(std::vector<Real>& pe){
    impl->getPotentialEnergy(pe);
}

Real OclMD::Solver::calculateForcesandEnergy(){
    impl->CalculateForcesandEnergy();
    return 0.0;
}

OclMD::ContextImpl& OclMD::Solver::getImpl(){
    return *impl;
}