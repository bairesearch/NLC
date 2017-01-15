#include "NLCgeneratedtheClass.hpp"
#include "NLClibrary.hpp"

theClass::theClass(void)
{
	name = "the";
	actionObjectLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("value", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&valueClassActionObjectList)));
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

