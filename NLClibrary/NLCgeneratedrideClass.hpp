#ifndef HEADER_NLC_GENERATED_rideClass
#define HEADER_NLC_GENERATED_rideClass

#include "NLClibraryGenericEntityClass.hpp"

class tomClass;
class bikeClass;
class rideClass : public NLCgenericEntityClass
{
public:
	rideClass(void);
	vector<tomClass*> tomClassActionSubjectList;
	vector<bikeClass*> bikeClassActionObjectList;
};

#endif
