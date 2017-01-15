#include "NLCgeneratedenergyClass.hpp"

energyClass::energyClass(void)
{
	name = "energy";
	actionLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("decrease", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&decreaseClassActionList)));
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

