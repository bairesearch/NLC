#include "NLCgeneratedconditionEntityArtificialIndexCurrentClass.hpp"
#include "NLClibrary.hpp"

conditionEntityArtificialIndexCurrentClass::conditionEntityArtificialIndexCurrentClass(void)
{
	name = "conditionEntityArtificialIndexCurrent";
	numericalValue = numeric_limits<double>::quiet_NaN();
	propertyLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("int", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&intClassPropertyList)));
}

