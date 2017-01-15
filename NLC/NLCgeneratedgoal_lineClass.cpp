#include "NLCgeneratedgoal_lineClass.hpp"
#include "NLClibrary.hpp"

goal_lineClass::goal_lineClass(void)
{
	name = "goal_line";
	conditionLists.insert(pair<pair<string, string>*, unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>*>(new pair<string, string>("near", "ball"), reinterpret_cast<unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>*>(&nearClassballClassConditionList)));
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

