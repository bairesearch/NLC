#include "NLCgeneratedfruitClass.hpp"
#include "NLClibrary.hpp"

fruitClass::fruitClass(void)
{
	name = "fruit";
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

