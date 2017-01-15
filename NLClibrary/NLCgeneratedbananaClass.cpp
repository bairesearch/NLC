#include "NLCgeneratedbananaClass.hpp"
#include "NLClibrary.hpp"

bananaClass::bananaClass(void)
{
	name = "banana";
	conditionLists.insert(pair<pair<string, string>*, unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>*>(new pair<string, string>("on", "table"), reinterpret_cast<unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>*>(&onClasstableClassConditionList)));
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new fruitClass));
}

