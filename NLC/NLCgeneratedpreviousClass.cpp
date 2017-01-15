#include "NLCgeneratedpreviousClass.hpp"
#include "NLClibrary.hpp"

previousClass::previousClass(void)
{
	name = "previous";
	numericalValue = numeric_limits<double>::quiet_NaN();
	inverseConditionTwoWay = false;
	thirdpartyAPIobject = NULL;
	propertyLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("GIAsentence", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&GIAsentenceClassPropertyList)));
}

