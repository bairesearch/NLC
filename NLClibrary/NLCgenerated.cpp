#include "NLCgenerated.hpp"

NLCgenericEntityClass* generateObjectByName(string name)
{
	NLCgenericEntityClass* newGenericObject = NULL;
	if(name == "functionsWithNoSubjectArtificial")
	{
		functionsWithNoSubjectArtificialClass* newfunctionsWithNoSubjectArtificialClass = new functionsWithNoSubjectArtificialClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newfunctionsWithNoSubjectArtificialClass);
	}
	if(name == "cabbage")
	{
		cabbageClass* newcabbageClass = new cabbageClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newcabbageClass);
	}
	if(name == "boat")
	{
		boatClass* newboatClass = new boatClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newboatClass);
	}
	if(name == "near")
	{
		nearClass* newnearClass = new nearClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newnearClass);
	}
	if(name == "brown")
	{
		brownClass* newbrownClass = new brownClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newbrownClass);
	}
	if(name == "happy")
	{
		happyClass* newhappyClass = new happyClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newhappyClass);
	}
	if(name == "sun")
	{
		sunClass* newsunClass = new sunClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newsunClass);
	}
	if(name == "fight")
	{
		fightClass* newfightClass = new fightClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newfightClass);
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
	if(name == "cabbage")
	{
		cabbageClass* newcabbageClass = new cabbageClass(*(static_cast<cabbageClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newcabbageClass);
	}
	if(name == "boat")
	{
		boatClass* newboatClass = new boatClass(*(static_cast<boatClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newboatClass);
	}
	if(name == "near")
	{
		nearClass* newnearClass = new nearClass(*(static_cast<nearClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newnearClass);
	}
	if(name == "brown")
	{
		brownClass* newbrownClass = new brownClass(*(static_cast<brownClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newbrownClass);
	}
	if(name == "happy")
	{
		happyClass* newhappyClass = new happyClass(*(static_cast<happyClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newhappyClass);
	}
	if(name == "sun")
	{
		sunClass* newsunClass = new sunClass(*(static_cast<sunClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newsunClass);
	}
	if(name == "fight")
	{
		fightClass* newfightClass = new fightClass(*(static_cast<fightClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newfightClass);
	}
	if(name == "print")
	{
		printClass* newprintClass = new printClass(*(static_cast<printClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newprintClass);
	}
	return newGenericObject;
}

