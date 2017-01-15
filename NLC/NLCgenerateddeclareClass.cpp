#include "NLCgenerateddeclareClass.hpp"
#include "NLClibrary.hpp"

declareClass::declareClass(void)
{
	name = "declare";
	actionSubjectLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("castle", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&castleClassActionSubjectList)));
	actionObjectLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("war", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&warClassActionObjectList)));
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

