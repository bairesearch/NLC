#include "NLCgeneratedcabbageClass.hpp"
#include "NLClibrary.hpp"

cabbageClass::cabbageClass(void)
{
	name = "cabbage";
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

