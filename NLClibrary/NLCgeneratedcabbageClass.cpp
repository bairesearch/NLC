#include "NLCgeneratedcabbageClass.hpp"
#include "NLClibrary.hpp"

cabbageClass::cabbageClass(void)
{
	name = "cabbage";
	propertyLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("brown", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&brownClassPropertyList)));
	propertyLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("happy", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&happyClassPropertyList)));
	conditionLists.insert(pair<pair<string, string>*, unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>*>(new pair<string, string>("near", "boat"), reinterpret_cast<unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>*>(&nearClassboatClassConditionList)));
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

