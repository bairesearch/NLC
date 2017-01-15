#include "NLCgeneratedfirstFeatureInListClass.hpp"
#include "NLClibrary.hpp"

firstFeatureInListClass::firstFeatureInListClass(void)
{
	name = "firstFeatureInList";
	numericalValue = numeric_limits<double>::quiet_NaN();
	inverseConditionTwoWay = false;
	thirdpartyAPIobject = NULL;
	propertyLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("GIAfeature", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&GIAfeatureClassPropertyList)));
}
