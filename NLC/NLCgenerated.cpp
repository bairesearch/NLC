#include "NLCgenerated.hpp"

NLCgenericEntityClass* generateObjectByName(string name)
{
	NLCgenericEntityClass* newGenericObject = NULL;
	if(name == "functionsWithNoSubjectArtificial")
	{
		functionsWithNoSubjectArtificialClass* newfunctionsWithNoSubjectArtificialClass = new functionsWithNoSubjectArtificialClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newfunctionsWithNoSubjectArtificialClass);
	}
	if(name == "value")
	{
		valueClass* newvalueClass = new valueClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newvalueClass);
	}
	if(name == "chicken")
	{
		chickenClass* newchickenClass = new chickenClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newchickenClass);
	}
	if(newGenericObject != NULL)
	{
		newGenericObject->lastSentenceReferenced.push(0);
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
	if(name == "value")
	{
		valueClass* newvalueClass = new valueClass(*(static_cast<valueClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newvalueClass);
	}
	if(name == "chicken")
	{
		chickenClass* newchickenClass = new chickenClass(*(static_cast<chickenClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newchickenClass);
	}
	return newGenericObject;
}

