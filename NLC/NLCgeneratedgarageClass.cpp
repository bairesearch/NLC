#include "NLCgeneratedgarageClass.hpp"
#include "NLClibrary.hpp"

garageClass::garageClass(void)
{
	name = "garage";
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

