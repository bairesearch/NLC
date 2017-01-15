#include "NLCgeneratedpieClass.hpp"
#include "NLClibrary.hpp"

pieClass::pieClass(void)
{
	name = "pie";
	conditionLists.insert(pair<pair<string, string>*, unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>*>(new pair<string, string>("near", "apple"), reinterpret_cast<unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>*>(&nearClassappleClassConditionList)));
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

