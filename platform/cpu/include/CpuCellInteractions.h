/**
 *
 * @file
 * @author Saif Mulla <s.mulla@ed.ac.uk>
 * @version 1.0
 *
 * @section LICENSE
 *
 * @section DESCRIPTION
 *
 * className CellInteractions
 *
 * This class handles the molecular interactions and pair-wise 
 * calculation by providing periodic boundary force calculations.
 * In this class the whole system is divided into cells, the cells 
 * are later taged based on numbers and cornering cells and edge cells.
 * Furthermore each positions assigned are tagged based on cells, based
 * on these information create list of molecules withing rcut of periodic 
 * boundary and also called as referred molecules.
 *
 *
 */

#ifndef OclMD_CellInteractions_h
#define OclMD_CellInteractions_h

#include <vector>
#include "oclmd/Vec3.h"
#include "oclmd/RealType.h"

namespace OclMD {

class CpuCellInteractions {
public:
    /**
     * @section DESCRIPTION
     * functionname
     *
     /// constructor
     * @param boxDimension pointer to box size
     * @param rCut size of rcut 
     *
     */
    CpuCellInteractions(Vec3* boxDimension,Real rCut);
    
    /// Destructor
    ~CpuCellInteractions();
    
    /// get referredPosition size
    int getNumReferredPositions();
    
    /// get the pointer to list of reffered particles
    Vec3* getReferredPositions(){
        return referredPositions_;
    }
    
    /**
     * this function does all the initialisation tasks this could be done inside
     * the constructor however it is not a good idea to apply complex and lenghty
     * login inside a constructor
     */
    
    void initialise();
    
    void generateReferredPositions(std::vector<Vec3>& realPositions);
    
    /// get number of total cell
    int nCells(){
        return totalCells_;
    }
    
    /// get total cells in x,y,z dimension
    int nCellXDim() const {
        return nCellsX_;
    }
    
    int nCellYDim() const {
        return nCellsY_;
    }
    
    int nCellZDim() const {
        return nCellsZ_;
    }
    
    const int* getCellIndexes() const;
    
    const int* getCorneringCellIndexes() const;
    
    const int* getLeftSideCellIndexes() const;
    
    const int* getRightSideCellIndexes() const;
    
    int getTotalCornerCells() const {
        return totalCornerCells_;
    }
    
    int getnCellsLeft() const {
        return nCellsLeft_;
    }
    
    int getnCellsRight() const {
        return nCellsRight_;
    }
    
    
private:
    Vec3* referredPositions_;
    Vec3* boxDimensions_;
    Real rCut_;
    unsigned int totalCells_;
    unsigned int nCellsX_;
    unsigned int nCellsY_;
    unsigned int nCellsZ_;
    int roundedBoxDims_[3];
    int* cellIndexes_;
    int* corneringCells_;
    int* referredCells_;
    int* leftSideCells_;
    int* rightSideCells_;
    int roundedRcut_;
    int totalCornerCells_;
    int nCellsLeft_;
    int nCellsRight_;
    
};

}//end namespace

#endif /* OclMD_CellInteractions_h */