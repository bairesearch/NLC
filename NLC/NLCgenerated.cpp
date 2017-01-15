#include "NLCgenerated.hpp"

NLCgenericEntityClass* generateObjectByName(string name)
{
	NLCgenericEntityClass* newGenericObject = NULL;
	if(name == "functionsWithNoSubjectArtificial")
	{
		functionsWithNoSubjectArtificialClass* newfunctionsWithNoSubjectArtificialClass = new functionsWithNoSubjectArtificialClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newfunctionsWithNoSubjectArtificialClass);
	}
	if(name == "move")
	{
		moveClass* newmoveClass = new moveClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newmoveClass);
	}
	if(name == "NLCgenericEntity")
	{
		NLCgenericEntityClass* newNLCgenericEntityClass = new NLCgenericEntityClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newNLCgenericEntityClass);
	}
	if(name == "inputText")
	{
		inputTextClass* newinputTextClass = new inputTextClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newinputTextClass);
	}
	if(name == "file")
	{
		fileClass* newfileClass = new fileClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newfileClass);
	}
	if(name == "to")
	{
		toClass* newtoClass = new toClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newtoClass);
	}
	if(name == "land")
	{
		landClass* newlandClass = new landClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newlandClass);
	}
	return newGenericObject;
}

NLCgenericEntityClass* copyObjectByName(string name, NLCgenericEntityClass* entityToCopy)
{
	NLCgenericEntityClass* newGenericObject = NULL;
	if(name == "functionsWithNoSubjectArtificial")
	{
		functionsWithNoSubjectArtificialClass* newfunctionsWithNoSubjectArtificialClass = new functionsWithNoSubjectArtificialClass(*(static_cast<functionsWithNoSubjectArtificialClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newfunctionsWithNoSubjectArtificialClass);
	}
	if(name == "move")
	{
		moveClass* newmoveClass = new moveClass(*(static_cast<moveClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newmoveClass);
	}
	if(name == "NLCgenericEntity")
	{
		NLCgenericEntityClass* newNLCgenericEntityClass = new NLCgenericEntityClass(*(static_cast<NLCgenericEntityClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newNLCgenericEntityClass);
	}
	if(name == "inputText")
	{
		inputTextClass* newinputTextClass = new inputTextClass(*(static_cast<inputTextClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newinputTextClass);
	}
	if(name == "file")
	{
		fileClass* newfileClass = new fileClass(*(static_cast<fileClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newfileClass);
	}
	if(name == "to")
	{
		toClass* newtoClass = new toClass(*(static_cast<toClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newtoClass);
	}
	if(name == "land")
	{
		landClass* newlandClass = new landClass(*(static_cast<landClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newlandClass);
	}
	return newGenericObject;
}

