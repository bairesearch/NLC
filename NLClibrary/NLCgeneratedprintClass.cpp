#include "NLCgeneratedprintClass.hpp"
#include "NLClibrary.hpp"

printClass::printClass(void)
{
	name = "print";
	actionObjectLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("apple", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&appleClassActionObjectList)));
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

