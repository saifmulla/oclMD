#ifndef OclMD_CpuInteractionCells_h
#define OclMD_CpuInteractionCells_h

#include <vector>
#include "oclmd/Vec3.h"
#include "oclmd/RealType.h"

namespace OclMD {
    
class CpuInteractionCells {
public:
    CpuInteractionCells(std::vector<std::vector<int> > dil,
                        std::vector<std::vector<int> > neighbouringcells,
                        const int ncells,
                        const int nreferredcells);

    void updateCellOccupancy(std::vector<std::vector<int> >& celloccupancy,
                             std::vector<std::vector<int> >& refcellparticles);
    void setCellOccupancy(const std::vector<std::vector<int> >& celloccupancy);
    
    void setRefCellParticles(const std::vector<std::vector<int> >& refcellparticles);
    
    const std::vector<int>* getCellOccupancy(int cellId);
    
    const std::vector<int>* getRefCellParticles(int cellId);
    
    const std::vector<int>* getDil(int cellId);
    
    const std::vector<int>* getNeighbouringCells(int cellId);
    
    int nCells() const {
        return nCells_;
    }
    
    int nRefCells() const {
        return nReferredCells_;
    }
    
    
private:
    std::vector<std::vector<int> > dil_; // this is a list of integer list
    std::vector<std::vector<int> > neighbouringCells_; // this is a list of integer list
    /// cellOccupancy is a list of positions which is dynamic vec3 list
    /// outer list is a list of real cells on the mesh
    /// inner list is a list of real molecules inside the real cell
//    std::vector<std::vector<Vec3*> cellOccupancy_;
    std::vector<std::vector<int> > cellOccupancy_;
    
    /// forces
//    std::vector<std::vector<Vec3*> forces_;
    
    /// referred particles
    /// outer list is a list of referred cells around mesh
    /// inner list is a list of referred molecules inside the referred cell
//    std::vector<std::vector<Vec3*> refCellParticles_;
    std::vector<std::vector<int> > refCellParticles_;
    /// size of total cells
    int nCells_;
    int nReferredCells_;
    
    
    
};
    
}//end namespace


#endif