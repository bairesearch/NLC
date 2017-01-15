#include "NLCgenerated.hpp"

NLCgenericEntityClass* generateObjectByName(string name)
{
	NLCgenericEntityClass* newGenericObject = NULL;
	if(name == "functionsWithNoSubjectArtificial")
	{
		functionsWithNoSubjectArtificialClass* newfunctionsWithNoSubjectArtificialClass = new functionsWithNoSubjectArtificialClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newfunctionsWithNoSubjectArtificialClass);
	}
	if(name == "module")
	{
		moduleClass* newmoduleClass = new moduleClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newmoduleClass);
	}
	if(name == "tall")
	{
		tallClass* newtallClass = new tallClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newtallClass);
	}
	if(name == "something")
	{
		somethingClass* newsomethingClass = new somethingClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newsomethingClass);
	}
	if(name == "do")
	{
		doClass* newdoClass = new doClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newdoClass);
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
	if(name == "module")
	{
		moduleClass* newmoduleClass = new moduleClass(*(static_cast<moduleClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newmoduleClass);
	}
	if(name == "tall")
	{
		tallClass* newtallClass = new tallClass(*(static_cast<tallClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newtallClass);
	}
	if(name == "something")
	{
		somethingClass* newsomethingClass = new somethingClass(*(static_cast<somethingClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newsomethingClass);
	}
	if(name == "do")
	{
		doClass* newdoClass = new doClass(*(static_cast<doClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newdoClass);
	}
	return newGenericObject;
}

