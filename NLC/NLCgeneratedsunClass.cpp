#include "NLCgeneratedsunClass.hpp"
#include "NLClibrary.hpp"

sunClass::sunClass(void)
{
	name = "sun";
	actionLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("fight", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&fightClassActionList)));
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

