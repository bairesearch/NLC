#include "NLCgeneratedrideClass.hpp"
#include "NLClibrary.hpp"

rideClass::rideClass(void)
{
	name = "ride";
	actionSubjectLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("module", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&moduleClassActionSubjectList)));
	actionObjectLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("bike", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&bikeClassActionObjectList)));
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new somethingClass));
}

