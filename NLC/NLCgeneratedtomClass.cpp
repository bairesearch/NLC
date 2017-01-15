#include "NLCgeneratedtomClass.hpp"
#include "NLClibrary.hpp"

tomClass::tomClass(void)
{
	name = "tom";
	actionLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("ride", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&rideClassActionList)));
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

