#include "NLCgeneratedvalueClass.hpp"
#include "NLClibrary.hpp"

valueClass::valueClass(void)
{
	name = "value";
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

