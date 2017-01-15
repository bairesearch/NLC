#include "NLCgeneratedknightClass.hpp"
#include "NLClibrary.hpp"

knightClass::knightClass(void)
{
	name = "knight";
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

