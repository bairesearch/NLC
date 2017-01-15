#include "NLCgeneratednearClass.hpp"
#include "NLClibrary.hpp"

nearClass::nearClass(void)
{
	name = "near";
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

