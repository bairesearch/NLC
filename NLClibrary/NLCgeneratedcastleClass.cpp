#include "NLCgeneratedcastleClass.hpp"
#include "NLClibrary.hpp"

castleClass::castleClass(void)
{
	name = "castle";
	propertyLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("knight", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&knightClassPropertyList)));
	actionLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("declare", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&declareClassActionList)));
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

