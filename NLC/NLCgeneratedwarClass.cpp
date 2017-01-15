#include "NLCgeneratedwarClass.hpp"
#include "NLClibrary.hpp"

warClass::warClass(void)
{
	name = "war";
	propertyLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("terrible", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&terribleClassPropertyList)));
	actionIncomingLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("declare", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&declareClassActionIncomingList)));
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

