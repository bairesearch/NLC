#include "NLCgeneratedfightClass.hpp"
#include "NLClibrary.hpp"

fightClass::fightClass(void)
{
	name = "fight";
	actionSubjectLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("sun", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&sunClassActionSubjectList)));
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

