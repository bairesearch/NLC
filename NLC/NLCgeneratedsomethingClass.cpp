#include "NLCgeneratedsomethingClass.hpp"
#include "NLClibrary.hpp"

somethingClass::somethingClass(void)
{
	name = "something";
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

