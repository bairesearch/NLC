#include "NLCgeneratedchickenClass.hpp"
#include "NLClibrary.hpp"

chickenClass::chickenClass(void)
{
	name = "chicken";
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

