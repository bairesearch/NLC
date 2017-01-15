#include "NLCgeneratedfirstRelationInListClass.hpp"
#include "NLClibrary.hpp"

firstRelationInListClass::firstRelationInListClass(void)
{
	name = "firstRelationInList";
	numericalValue = numeric_limits<double>::quiet_NaN();
	inverseConditionTwoWay = false;
	thirdpartyAPIobject = NULL;
	propertyLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("GIArelation", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&GIArelationClassPropertyList)));
}
