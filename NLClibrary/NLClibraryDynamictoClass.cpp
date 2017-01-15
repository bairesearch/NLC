#include "NLClibraryDynamictoClass.hpp"

toClass::toClass(void)
{
	name = "to";
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

