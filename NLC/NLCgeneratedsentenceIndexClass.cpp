#include "NLCgeneratedsentenceIndexClass.hpp"
#include "NLClibrary.hpp"

sentenceIndexClass::sentenceIndexClass(void)
{
	name = "sentenceIndex";
	numericalValue = numeric_limits<double>::quiet_NaN();
	inverseConditionTwoWay = false;
	thirdpartyAPIobject = NULL;
	propertyLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("int", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&intClassPropertyList)));
}

