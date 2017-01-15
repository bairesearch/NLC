#include "NLCgeneratedboatClass.hpp"
#include "NLClibrary.hpp"

boatClass::boatClass(void)
{
	name = "boat";
	conditionLists.insert(pair<pair<string, string>*, unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>*>(new pair<string, string>("near", "cabbage"), reinterpret_cast<unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>*>(&nearClasscabbageClassConditionList)));
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

