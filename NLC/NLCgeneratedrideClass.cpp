#include "NLCgeneratedrideClass.hpp"
#include "NLClibrary.hpp"

rideClass::rideClass(void)
{
	name = "ride";
	actionObjectLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("bike", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&bikeClassActionObjectList)));
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

