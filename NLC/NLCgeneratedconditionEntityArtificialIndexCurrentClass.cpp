#include "NLCgeneratedconditionEntityArtificialIndexCurrentClass.hpp"
#include "NLClibrary.hpp"

conditionEntityArtificialIndexCurrentClass::conditionEntityArtificialIndexCurrentClass(void)
{
	name = "conditionEntityArtificialIndexCurrent";
	numericalValue = numeric_limits<double>::quiet_NaN();
	inverseConditionTwoWay = false;
	thirdpartyAPIobject = NULL;
	propertyLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("int", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&intClassPropertyList)));
}
