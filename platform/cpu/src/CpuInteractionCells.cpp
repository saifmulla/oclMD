#include "CpuInteractionCells.h"

OclMD::CpuInteractionCells::CpuInteractionCells(std::vector<std::vector<int> > dil,
                                std::vector<std::vector<int> > neighbouringcells,
                                const int ncells,
                                const int nreferredcells)
:dil_(dil),neighbouringCells_(neighbouringcells),cellOccupancy_(0),refCellParticles_(0),nCells_(ncells),nReferredCells_(nreferredcells){
//    std::vector<int> *cellOccupancy_ = new std::vector<int>(nCells_);
//    refCellParticles_ = (int**) malloc(sizeof(int*)*nReferredCells_);

//    cellInteractionList_ = (int**) malloc(sizeof(int*) * totalCells_);
//    cellOccupancy_ = new std::vector<std::vector<OclMD::Vec3*> >(nCells_);
//    refCellParticles_ = new std::vector<OclMD::Vec3*>(nReferredCells_);
    cellOccupancy_.resize(nCells_);
    refCellParticles_.resize(nReferredCells_);
}

const std::vector<int>* OclMD::CpuInteractionCells::getCellOccupancy(int cellId) {
    return &cellOccupancy_[cellId];
}

const std::vector<int>* OclMD::CpuInteractionCells::getRefCellParticles(int cellId){
    return &refCellParticles_[cellId];
}


const std::vector<int>* OclMD::CpuInteractionCells::getDil(int cellId){
    return &dil_[cellId];
}

const std::vector<int>* OclMD::CpuInteractionCells::getNeighbouringCells(int cellId){
    return &neighbouringCells_[cellId];
}

void OclMD::CpuInteractionCells::setCellOccupancy(const std::vector<std::vector<int> >& celloccupancy){
    /// clear all existing position indexes from celloccupancy list
    for (int c = 0; c < nCells_; c++) {
        cellOccupancy_[c].clear();
    }
    
    for (int c = 0; c < nCells_; c++) {
        int size = celloccupancy[c].size();
        cellOccupancy_[c].resize(size);
        for (int j = 0; j < celloccupancy[c].size(); j++) {
            cellOccupancy_[c][j] = celloccupancy[c][j];
        }
    }
}


void OclMD::CpuInteractionCells::setRefCellParticles(const std::vector<std::vector<int> > &refcellparticles){
    /// clear all existing position indexes from refcelllist
    for (int c = 0; c < nReferredCells_; c++) {
        refCellParticles_[c].clear();
    }
    
    for (int c = 0; c < nReferredCells_; c++) {
        int size = refcellparticles[c].size();
        refCellParticles_[c].resize(size);
        for (int j = 0; j < refcellparticles[c].size(); j++) {
            refCellParticles_[c][j] = refcellparticles[c][j];
        }
    }
}

void OclMD::CpuInteractionCells::updateCellOccupancy(
                                std::vector<std::vector<int> >& celloccupancy,
                                std::vector<std::vector<int> >& refcellparticles)
{
    cellOccupancy_ = celloccupancy;
    refCellParticles_ = refcellparticles;
}
