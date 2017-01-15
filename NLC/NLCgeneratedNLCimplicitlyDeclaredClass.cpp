#include "NLCgeneratedNLCimplicitlyDeclaredClass.hpp"
#include "NLClibrary.hpp"

NLCimplicitlyDeclaredClass::NLCimplicitlyDeclaredClass(void)
{
	name = "NLCimplicitlyDeclared";
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

