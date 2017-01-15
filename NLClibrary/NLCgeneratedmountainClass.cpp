#include "NLCgeneratedmountainClass.hpp"
#include "NLClibrary.hpp"

mountainClass::mountainClass(void)
{
	name = "mountain";
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

