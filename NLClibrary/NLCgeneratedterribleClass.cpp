#include "NLCgeneratedterribleClass.hpp"
#include "NLClibrary.hpp"

terribleClass::terribleClass(void)
{
	name = "terrible";
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

