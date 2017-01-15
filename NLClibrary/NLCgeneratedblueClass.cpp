#include "NLCgeneratedblueClass.hpp"
#include "NLClibrary.hpp"

blueClass::blueClass(void)
{
	name = "blue";
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

