#include "NLCgeneratedmoduleClass.hpp"
#include "NLClibrary.hpp"

moduleClass::moduleClass(void)
{
	name = "module";
	propertyLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("tall", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&tallClassPropertyList)));
	actionLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("think", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&thinkClassActionList)));
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

