#include "NLCgeneratedsomethingClass.hpp"
#include "NLClibrary.hpp"

somethingClass::somethingClass(void)
{
	name = "something";
	actionIncomingLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("do", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&doClassActionIncomingList)));
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

