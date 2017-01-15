#include "NLCgeneratedcountryClass.hpp"
#include "NLClibrary.hpp"

countryClass::countryClass(void)
{
	name = "country";
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

