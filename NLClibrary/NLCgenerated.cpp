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
	if(name == "NLCimplicitlyDeclaredFunctionArtificial")
	{
		NLCimplicitlyDeclaredFunctionArtificialClass* newNLCimplicitlyDeclaredFunctionArtificialClass = new NLCimplicitlyDeclaredFunctionArtificialClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newNLCimplicitlyDeclaredFunctionArtificialClass);
	}
	if(name == "red")
	{
		redClass* newredClass = new redClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newredClass);
	}
	if(name == "dog")
	{
		dogClass* newdogClass = new dogClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newdogClass);
	}
	if(name == "blue")
	{
		blueClass* newblueClass = new blueClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newblueClass);
	}
	if(name == "bird")
	{
		birdClass* newbirdClass = new birdClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newbirdClass);
	}
	if(name == "near")
	{
		nearClass* newnearClass = new nearClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newnearClass);
	}
	if(name == "mountain")
	{
		mountainClass* newmountainClass = new mountainClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newmountainClass);
	}
	if(name == "elephant")
	{
		elephantClass* newelephantClass = new elephantClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newelephantClass);
	}
	if(name == "bone")
	{
		boneClass* newboneClass = new boneClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newboneClass);
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
	if(name == "NLCimplicitlyDeclaredFunctionArtificial")
	{
		NLCimplicitlyDeclaredFunctionArtificialClass* newNLCimplicitlyDeclaredFunctionArtificialClass = new NLCimplicitlyDeclaredFunctionArtificialClass(*(static_cast<NLCimplicitlyDeclaredFunctionArtificialClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newNLCimplicitlyDeclaredFunctionArtificialClass);
	}
	if(name == "red")
	{
		redClass* newredClass = new redClass(*(static_cast<redClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newredClass);
	}
	if(name == "dog")
	{
		dogClass* newdogClass = new dogClass(*(static_cast<dogClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newdogClass);
	}
	if(name == "blue")
	{
		blueClass* newblueClass = new blueClass(*(static_cast<blueClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newblueClass);
	}
	if(name == "bird")
	{
		birdClass* newbirdClass = new birdClass(*(static_cast<birdClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newbirdClass);
	}
	if(name == "near")
	{
		nearClass* newnearClass = new nearClass(*(static_cast<nearClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newnearClass);
	}
	if(name == "mountain")
	{
		mountainClass* newmountainClass = new mountainClass(*(static_cast<mountainClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newmountainClass);
	}
	if(name == "elephant")
	{
		elephantClass* newelephantClass = new elephantClass(*(static_cast<elephantClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newelephantClass);
	}
	if(name == "bone")
	{
		boneClass* newboneClass = new boneClass(*(static_cast<boneClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newboneClass);
	}
	return newGenericObject;
}

