#include "NLCgenerateddoClass.hpp"
#include "NLClibrary.hpp"

doClass::doClass(void)
{
	name = "do";
	actionSubjectLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("module", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&moduleClassActionSubjectList)));
	actionObjectLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("something", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&somethingClassActionObjectList)));
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

