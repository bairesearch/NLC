#include "NLCgeneratedmoveClass.hpp"
#include "NLClibrary.hpp"

moveClass::moveClass(void)
{
	name = "move";
	actionObjectLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("NLCgenericEntity", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&NLCgenericEntityClassActionObjectList)));
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

