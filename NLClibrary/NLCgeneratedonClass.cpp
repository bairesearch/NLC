#include "NLCgeneratedonClass.hpp"
#include "NLClibrary.hpp"

onClass::onClass(void)
{
	name = "on";
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

