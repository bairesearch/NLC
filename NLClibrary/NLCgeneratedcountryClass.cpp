#include "NLCgeneratedcountryClass.hpp"
#include "NLClibrary.hpp"

countryClass::countryClass(void)
{
	name = "country";
	propertyLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("happy", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&happyClassPropertyList)));
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

