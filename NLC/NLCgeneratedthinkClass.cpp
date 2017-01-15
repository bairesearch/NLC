#include "NLCgeneratedthinkClass.hpp"
#include "NLClibrary.hpp"

thinkClass::thinkClass(void)
{
	name = "think";
	conditionLists.insert(pair<pair<string, string>*, unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>*>(new pair<string, string>("about", "bike"), reinterpret_cast<unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>*>(&aboutClassbikeClassConditionList)));
	conditionLists.insert(pair<pair<string, string>*, unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>*>(new pair<string, string>("about", "something"), reinterpret_cast<unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>*>(&aboutClasssomethingClassConditionList)));
	actionSubjectLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("module", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&moduleClassActionSubjectList)));
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

