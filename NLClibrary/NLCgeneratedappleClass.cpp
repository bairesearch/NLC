#include "NLCgeneratedappleClass.hpp"
#include "NLClibrary.hpp"

appleClass::appleClass(void)
{
	name = "apple";
	conditionLists.insert(pair<pair<string, string>*, unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>*>(new pair<string, string>("on", "tree"), reinterpret_cast<unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>*>(&onClasstreeClassConditionList)));
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new fruitClass));
}

