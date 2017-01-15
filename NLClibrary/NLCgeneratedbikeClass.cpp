#include "NLCgeneratedbikeClass.hpp"
#include "NLClibrary.hpp"

bikeClass::bikeClass(void)
{
	name = "bike";
	propertyLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("blue", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&blueClassPropertyList)));
	conditionLists.insert(pair<pair<string, string>*, unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>*>(new pair<string, string>("near", "garage"), reinterpret_cast<unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>*>(&nearClassgarageClassConditionList)));
	actionIncomingLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("ride", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&rideClassActionIncomingList)));
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

