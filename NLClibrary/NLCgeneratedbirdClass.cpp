#include "NLCgeneratedbirdClass.hpp"
#include "NLClibrary.hpp"

birdClass::birdClass(void)
{
	name = "bird";
	propertyLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("blue", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&blueClassPropertyList)));
	conditionLists.insert(pair<pair<string, string>*, unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>*>(new pair<string, string>("near", "mountain"), reinterpret_cast<unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>*>(&nearClassmountainClassConditionList)));
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

