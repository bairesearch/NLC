#include "NLCgeneratedbeClass.hpp"
#include "NLClibrary.hpp"

beClass::beClass(void)
{
	name = "be";
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

