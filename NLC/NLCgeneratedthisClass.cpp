#include "NLCgeneratedthisClass.hpp"
#include "NLClibrary.hpp"

thisClass::thisClass(void)
{
	name = "this";
	actionIncomingLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("do", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&doClassActionIncomingList)));
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

