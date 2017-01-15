#include "NLCgeneratedbikeClass.hpp"
#include "NLClibrary.hpp"

bikeClass::bikeClass(void)
{
	name = "bike";
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

