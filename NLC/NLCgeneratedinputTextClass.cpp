#include "NLCgeneratedinputTextClass.hpp"
#include "NLClibrary.hpp"

inputTextClass::inputTextClass(void)
{
	name = "inputText";
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

