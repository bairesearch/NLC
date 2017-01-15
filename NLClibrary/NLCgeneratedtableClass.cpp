#include "NLCgeneratedtableClass.hpp"
#include "NLClibrary.hpp"

tableClass::tableClass(void)
{
	name = "table";
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

