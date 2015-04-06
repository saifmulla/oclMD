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
 * classname OclMDException
 * This class is implemented to handle all types of 
 * exceptions thrown by OclMD
 */

#include <exception>
#include <string>

#ifndef OclMD_OclMDException_h
#define OclMD_OclMDException_h

namespace OclMD {

class OclMDException : public std::exception {
public:
    /**
     * OclMDException
     * only constructor that takes string message as user supplied 
     * message as feed back for instant clues
     * @param message type of string
     */
    explicit OclMDException(const std::string& msg) : message_(msg){
    }
    
    /// destructor
    ~OclMDException() throw() {
    }
    
    /**
     * OclMDException
     * this function return the exception message
     */
    const char* what() const throw(){
        return message_.c_str();
    }
private:
    std::string message_;
};
    
}//end namespace

#endif
