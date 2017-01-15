#include "NLCgeneratedfatClass.hpp"

fatClass::fatClass(void)
{
	name = "fat";
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

