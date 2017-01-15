#include "NLCgenerated.hpp"

NLCgenericEntityClass* generateObjectByName(string name)
{
	NLCgenericEntityClass* newGenericObject = NULL;
	if(name == "functionsWithNoSubjectArtificial")
	{
		functionsWithNoSubjectArtificialClass* newfunctionsWithNoSubjectArtificialClass = new functionsWithNoSubjectArtificialClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newfunctionsWithNoSubjectArtificialClass);
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
	if(name == "cabbage")
	{
		cabbageClass* newcabbageClass = new cabbageClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newcabbageClass);
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
	if(name == "cabbage")
	{
		cabbageClass* newcabbageClass = new cabbageClass(*(static_cast<cabbageClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newcabbageClass);
	}
	return newGenericObject;
}

