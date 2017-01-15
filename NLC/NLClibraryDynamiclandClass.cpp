#include "NLClibraryDynamiclandClass.hpp"

landClass::landClass(void)
{
	name = "land";
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

