#include "NLClibraryGenericEntityClass.hpp"

class blueClass;
class fatClass;
class energyClass;
class rideClass;
class bikeClass;
class dogClass : public NLCgenericEntityClass
{
public:
	dogClass(void);
	vector<blueClass*> blueClassPropertyList;
	vector<fatClass*> fatClassPropertyList;
	vector<energyClass*> energyClassPropertyList;
	void rideFunction(vector<dogClass*>& dogClassList, vector<rideClass*>& rideClassList, vector<bikeClass*>& bikeClassList);
	vector<rideClass*> rideClassActionList;
};

