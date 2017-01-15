#include "NLCgeneratedtomClass.hpp"
#include "NLClibrary.hpp"

tomClass::tomClass(void)
{
	name = "tom";
	propertyLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("happy", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&happyClassPropertyList)));
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

