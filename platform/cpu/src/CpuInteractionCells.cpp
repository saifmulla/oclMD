#include "CpuInteractionCells.h"

OclMD::CpuInteractionCells::CpuInteractionCells(int** dil,
                                int** neighbouringcells,
                                const int ncells,
                                const int nreferredcells)
:dil_(dil),neighbouringCells_(neighbouringcells),cellOccupancy_(0),refCellParticles_(0),nCells_(ncells),nReferredCells_(nreferredcells){
    cellOccupancy_ = (OclMD::Vec3**) malloc(sizeof(OclMD::Vec3*)*nCells_);
    refCellParticles_ = (OclMD::Vec3**) malloc(sizeof(OclMD::Vec3*)*nReferredCells_);

//    cellInteractionList_ = (int**) malloc(sizeof(int*) * totalCells_);
//    cellOccupancy_ = new std::vector<std::vector<OclMD::Vec3*> >(nCells_);
//    refCellParticles_ = new std::vector<OclMD::Vec3*>(nReferredCells_);
}

void OclMD::CpuInteractionCells::updateCellOccupancy(){
    
}