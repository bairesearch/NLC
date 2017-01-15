#include "NLCgeneratedClass.hpp"
#include "NLClibrary.hpp"

Class::Class(void)
{
	name = "";
	numericalValue = numeric_limits<double>::quiet_NaN();
	propertyLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("void", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&voidClassPropertyList)));
}

