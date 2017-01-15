#include "NLCgeneratedredClass.hpp"
#include "NLClibrary.hpp"

redClass::redClass(void)
{
	name = "red";
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

