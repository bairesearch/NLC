#include "NLCgeneratedthatClass.hpp"
#include "NLClibrary.hpp"

thatClass::thatClass(void)
{
	name = "that";
	actionLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("do", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&doClassActionList)));
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

