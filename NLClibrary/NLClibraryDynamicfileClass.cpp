#include "NLClibraryDynamicfileClass.hpp"

fileClass::fileClass(void)
{
	name = "file";
	actionIncomingLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("move", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&moveClassActionIncomingList)));
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

