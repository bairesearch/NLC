#include "NLCgeneratedbananaClass.hpp"
#include "NLClibrary.hpp"

bananaClass::bananaClass(void)
{
	name = "banana";
	propertyLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("yellow", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&yellowClassPropertyList)));
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new fruitClass));
}

