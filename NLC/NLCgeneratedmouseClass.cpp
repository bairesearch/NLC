#include "NLCgeneratedmouseClass.hpp"
#include "NLClibrary.hpp"

mouseClass::mouseClass(void)
{
	name = "mouse";
	propertyLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("happy", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&happyClassPropertyList)));
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

