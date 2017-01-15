#include "NLClibraryGenericEntityClass.hpp"

class rideClass;
class bikeClass : public NLCgenericEntityClass
{
public:
	bikeClass(void);
	vector<rideClass*> rideClassActionIncomingList;
};

