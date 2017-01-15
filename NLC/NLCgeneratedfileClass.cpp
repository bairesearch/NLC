#include "NLCgeneratedfileClass.hpp"
#include "NLClibrary.hpp"

fileClass::fileClass(void)
{
	name = "file";
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

