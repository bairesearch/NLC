#ifndef HEADER_NLC_GENERATED_tomClass
#define HEADER_NLC_GENERATED_tomClass

#include "NLClibraryGenericEntityClass.hpp"

class rideClass;
class bikeClass;
class tomClass : public NLCgenericEntityClass
{
public:
	tomClass(void);
	void rideFunction(vector<tomClass*>& tomClassList, vector<rideClass*>& rideClassList, vector<bikeClass*>& bikeClassList);
	vector<rideClass*> rideClassActionList;
};

#endif
