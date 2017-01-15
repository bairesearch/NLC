#include "NLClibraryGenericEntityClass.hpp"

class dogClass;
class bikeClass;
class rideClass : public NLCgenericEntityClass
{
public:
	rideClass(void);
	vector<dogClass*> dogClassActionSubjectList;
	vector<bikeClass*> bikeClassActionObjectList;
};

