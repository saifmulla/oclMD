#include "gmock/gmock.h"
#include "oclmd/Platform.h"
#include "oclmd/impl/ContextImpl.h"


class MockOmpPlatform : public OclMD::Platform {
public:
    MOCK_CONST_METHOD0(getName,const std::string&());
    MOCK_CONST_METHOD0(supportsDoublePrecision,bool());
    MOCK_CONST_METHOD1(createData,void(OclMD::ContextImpl& context));
    MOCK_CONST_METHOD1(deleteData,void(OclMD::ContextImpl& context));
    MOCK_CONST_METHOD0(getBaseFactory,OclMD::BaseFactory*());
};
