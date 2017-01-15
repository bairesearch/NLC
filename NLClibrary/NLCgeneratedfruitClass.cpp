#include "NLCgeneratedfruitClass.hpp"
#include "NLClibrary.hpp"

fruitClass::fruitClass(void)
{
	name = "fruit";
	propertyLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("yellow", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&yellowClassPropertyList)));
	propertyLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("tasty", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&tastyClassPropertyList)));
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

