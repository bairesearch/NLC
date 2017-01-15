#include "NLCgenerated.hpp"

NLCgenericEntityClass* generateObjectByName(string name)
{
	NLCgenericEntityClass* newGenericObject = NULL;
	if(name == "functionsWithNoSubjectArtificial")
	{
		functionsWithNoSubjectArtificialClass* newfunctionsWithNoSubjectArtificialClass = new functionsWithNoSubjectArtificialClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newfunctionsWithNoSubjectArtificialClass);
	}
	if(name == "apple")
	{
		appleClass* newappleClass = new appleClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newappleClass);
	}
	if(name == "pie")
	{
		pieClass* newpieClass = new pieClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newpieClass);
	}
	if(name == "near")
	{
		nearClass* newnearClass = new nearClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newnearClass);
	}
	if(name == "happy")
	{
		happyClass* newhappyClass = new happyClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newhappyClass);
	}
	if(name == "print")
	{
		printClass* newprintClass = new printClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newprintClass);
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
	if(name == "apple")
	{
		appleClass* newappleClass = new appleClass(*(static_cast<appleClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newappleClass);
	}
	if(name == "pie")
	{
		pieClass* newpieClass = new pieClass(*(static_cast<pieClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newpieClass);
	}
	if(name == "near")
	{
		nearClass* newnearClass = new nearClass(*(static_cast<nearClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newnearClass);
	}
	if(name == "happy")
	{
		happyClass* newhappyClass = new happyClass(*(static_cast<happyClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newhappyClass);
	}
	if(name == "print")
	{
		printClass* newprintClass = new printClass(*(static_cast<printClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newprintClass);
	}
	return newGenericObject;
}

