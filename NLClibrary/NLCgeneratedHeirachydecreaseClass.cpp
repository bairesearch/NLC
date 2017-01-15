#include "NLCgeneratedHeirachydecreaseClass.hpp"

decreaseClass::decreaseClass(void)
{
	name = "decrease";
	actionSubjectLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("energy", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&energyClassActionSubjectList)));
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

