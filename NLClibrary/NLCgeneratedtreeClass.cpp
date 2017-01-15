#include "NLCgeneratedtreeClass.hpp"
#include "NLClibrary.hpp"

treeClass::treeClass(void)
{
	name = "tree";
	propertyLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("green", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&greenClassPropertyList)));
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

