#include "NLCgeneratednameClass.hpp"
#include "NLClibrary.hpp"

nameClass::nameClass(void)
{
	name = "name";
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

