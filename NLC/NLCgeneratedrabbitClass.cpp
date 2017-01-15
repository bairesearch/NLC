#include "NLCgeneratedrabbitClass.hpp"
#include "NLClibrary.hpp"

rabbitClass::rabbitClass(void)
{
	name = "rabbit";
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

