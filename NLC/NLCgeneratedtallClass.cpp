#include "NLCgeneratedtallClass.hpp"
#include "NLClibrary.hpp"

tallClass::tallClass(void)
{
	name = "tall";
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new somethingClass));
}

