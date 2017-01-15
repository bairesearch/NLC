#include "NLCgenerated.hpp"

NLCgenericEntityClass* generateObjectByName(string name)
{
	NLCgenericEntityClass* newGenericObject = NULL;
	if(name == "functionsWithNoSubjectArtificial")
	{
		functionsWithNoSubjectArtificialClass* newfunctionsWithNoSubjectArtificialClass = new functionsWithNoSubjectArtificialClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newfunctionsWithNoSubjectArtificialClass);
	}
	if(name == "ball")
	{
		ballClass* newballClass = new ballClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newballClass);
	}
	if(name == "goal_line")
	{
		goal_lineClass* newgoal_lineClass = new goal_lineClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newgoal_lineClass);
	}
	if(name == "near")
	{
		nearClass* newnearClass = new nearClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newnearClass);
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
	if(name == "ball")
	{
		ballClass* newballClass = new ballClass(*(static_cast<ballClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newballClass);
	}
	if(name == "goal_line")
	{
		goal_lineClass* newgoal_lineClass = new goal_lineClass(*(static_cast<goal_lineClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newgoal_lineClass);
	}
	if(name == "near")
	{
		nearClass* newnearClass = new nearClass(*(static_cast<nearClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newnearClass);
	}
	return newGenericObject;
}

