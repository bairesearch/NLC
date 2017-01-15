#include "NLCgeneratedbikeClass.hpp"
#include "NLClibrary.hpp"

bikeClass::bikeClass(void)
{
	name = "bike";
	actionIncomingLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("ride", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&rideClassActionIncomingList)));
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new somethingClass));
}

