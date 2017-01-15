#include "NLCgeneratedyellowClass.hpp"
#include "NLClibrary.hpp"

yellowClass::yellowClass(void)
{
	name = "yellow";
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

