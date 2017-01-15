#include "NLCgeneratedhappyClass.hpp"
#include "NLClibrary.hpp"

happyClass::happyClass(void)
{
	name = "happy";
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

