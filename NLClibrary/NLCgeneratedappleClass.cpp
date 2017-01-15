#include "NLCgeneratedappleClass.hpp"
#include "NLClibrary.hpp"

appleClass::appleClass(void)
{
	name = "apple";
	propertyLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("happy", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&happyClassPropertyList)));
	conditionLists.insert(pair<pair<string, string>*, unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>*>(new pair<string, string>("near", "pie"), reinterpret_cast<unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>*>(&nearClasspieClassConditionList)));
	actionIncomingLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("print", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&printClassActionIncomingList)));
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

