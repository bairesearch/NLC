#include "NLCgeneratedmainClass.hpp"

mainClass::mainClass(void)
{
	name = "main";
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

