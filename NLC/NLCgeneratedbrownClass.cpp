#include "NLCgeneratedbrownClass.hpp"
#include "NLClibrary.hpp"

brownClass::brownClass(void)
{
	name = "brown";
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

