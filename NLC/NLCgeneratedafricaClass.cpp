#include "NLCgeneratedafricaClass.hpp"
#include "NLClibrary.hpp"

africaClass::africaClass(void)
{
	name = "africa";
	propertyLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("castle", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&castleClassPropertyList)));
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new countryClass));
}

