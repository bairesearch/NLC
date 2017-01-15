#include "NLCgeneratedtastyClass.hpp"
#include "NLClibrary.hpp"

tastyClass::tastyClass(void)
{
	name = "tasty";
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

