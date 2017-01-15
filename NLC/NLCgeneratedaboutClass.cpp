#include "NLCgeneratedaboutClass.hpp"
#include "NLClibrary.hpp"

aboutClass::aboutClass(void)
{
	name = "about";
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

