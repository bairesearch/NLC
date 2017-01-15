#include "NLCgeneratedmoduleClass.hpp"
#include "NLClibrary.hpp"

moduleClass::moduleClass(void)
{
	name = "module";
	propertyLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("tall", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&tallClassPropertyList)));
	actionLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("do", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&doClassActionList)));
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new somethingClass));
}

