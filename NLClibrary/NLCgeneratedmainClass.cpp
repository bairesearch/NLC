#include "NLCgeneratedmainClass.hpp"
#include "NLClibrary.hpp"

mainClass::mainClass(void)
{
	name = "main";
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

