#include "NLCgeneratedcityClass.hpp"
#include "NLClibrary.hpp"

cityClass::cityClass(void)
{
	name = "city";
	propertyLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("name", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&nameClassPropertyList)));
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

