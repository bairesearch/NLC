#include "NLCgeneratedelephantClass.hpp"
#include "NLClibrary.hpp"

elephantClass::elephantClass(void)
{
	name = "elephant";
	propertyLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("blue", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&blueClassPropertyList)));
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

