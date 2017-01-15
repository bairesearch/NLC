#include "NLCgeneratedmdClass.hpp"
#include "NLClibrary.hpp"

mdClass::mdClass(void)
{
	name = "md";
	numericalValue = numeric_limits<double>::quiet_NaN();
	inverseConditionTwoWay = false;
	thirdpartyAPIobject = NULL;
	propertyLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("MemberDef", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&MemberDefClassPropertyList)));
}

