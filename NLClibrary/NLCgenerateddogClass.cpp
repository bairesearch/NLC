#include "NLCgenerateddogClass.hpp"
#include "NLClibrary.hpp"

dogClass::dogClass(void)
{
	name = "dog";
	propertyLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("red", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&redClassPropertyList)));
	propertyLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("bone", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&boneClassPropertyList)));
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

