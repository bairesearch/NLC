#include "NLCgeneratedHeirachyrideClass.hpp"

rideClass::rideClass(void)
{
	name = "ride";
	actionSubjectLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("dog", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&dogClassActionSubjectList)));
	actionObjectLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("bike", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&bikeClassActionObjectList)));
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

