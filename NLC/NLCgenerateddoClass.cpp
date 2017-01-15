#include "NLCgenerateddoClass.hpp"
#include "NLClibrary.hpp"

doClass::doClass(void)
{
	name = "do";
	actionObjectLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("this", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&thisClassActionObjectList)));
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

