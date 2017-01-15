#include "NLCgeneratedHeirachydogClass.hpp"

dogClass::dogClass(void)
{
	name = "dog";
	propertyLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("blue", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&blueClassPropertyList)));
	propertyLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("fat", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&fatClassPropertyList)));
	propertyLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("energy", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&energyClassPropertyList)));
	actionLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("ride", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&rideClassActionList)));
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

