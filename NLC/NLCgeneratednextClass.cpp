#include "NLCgeneratednextClass.hpp"
#include "NLClibrary.hpp"

nextClass::nextClass(void)
{
	name = "next";
	numericalValue = numeric_limits<double>::quiet_NaN();
	inverseConditionTwoWay = false;
	thirdpartyAPIobject = NULL;
	propertyLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("GIAsentence", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&GIAsentenceClassPropertyList)));
}

