#include "NLCgeneratedboneClass.hpp"
#include "NLClibrary.hpp"

boneClass::boneClass(void)
{
	name = "bone";
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

