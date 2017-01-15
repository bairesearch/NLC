#ifndef HEADER_NLC_GENERATED_bikeClass
#define HEADER_NLC_GENERATED_bikeClass

#include "NLClibraryGenericEntityClass.hpp"

class blueClass;
class nearClass;
class garageClass;
class rideClass;
class bikeClass : public NLCgenericEntityClass
{
public:
	bikeClass(void);
	vector<blueClass*> blueClassPropertyList;
	unordered_map<nearClass*, garageClass*> nearClassgarageClassConditionList;
	vector<rideClass*> rideClassActionIncomingList;
};

#endif
