#ifndef HEADER_NLC_GENERATED_bikeClass
#define HEADER_NLC_GENERATED_bikeClass

#include "NLClibraryGenericEntityClass.hpp"

class rideClass;
class bikeClass : public NLCgenericEntityClass
{
public:
	bikeClass(void);
	vector<rideClass*> rideClassActionIncomingList;
};

#endif
