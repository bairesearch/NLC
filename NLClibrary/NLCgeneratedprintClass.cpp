#include "NLCgeneratedprintClass.hpp"
#include "NLClibrary.hpp"

printClass::printClass(void)
{
	name = "print";
	actionObjectLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("cabbage", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&cabbageClassActionObjectList)));
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

