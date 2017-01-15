#include "NLCgeneratedgreenClass.hpp"
#include "NLClibrary.hpp"

greenClass::greenClass(void)
{
	name = "green";
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

