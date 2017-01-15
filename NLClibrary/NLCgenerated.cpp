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
	if(name == "NLCimplicitlyDeclared")
	{
		NLCimplicitlyDeclaredClass* newNLCimplicitlyDeclaredClass = new NLCimplicitlyDeclaredClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newNLCimplicitlyDeclaredClass);
	}
	if(name == "yellow")
	{
		yellowClass* newyellowClass = new yellowClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newyellowClass);
	}
	if(name == "banana")
	{
		bananaClass* newbananaClass = new bananaClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newbananaClass);
	}
	if(name == "fruit")
	{
		fruitClass* newfruitClass = new fruitClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newfruitClass);
	}
	if(name == "apple")
	{
		appleClass* newappleClass = new appleClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newappleClass);
	}
	if(name == "on")
	{
		onClass* newonClass = new onClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newonClass);
	}
	if(name == "tree")
	{
		treeClass* newtreeClass = new treeClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newtreeClass);
	}
	if(name == "green")
	{
		greenClass* newgreenClass = new greenClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newgreenClass);
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
	if(name == "NLCimplicitlyDeclared")
	{
		NLCimplicitlyDeclaredClass* newNLCimplicitlyDeclaredClass = new NLCimplicitlyDeclaredClass(*(static_cast<NLCimplicitlyDeclaredClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newNLCimplicitlyDeclaredClass);
	}
	if(name == "yellow")
	{
		yellowClass* newyellowClass = new yellowClass(*(static_cast<yellowClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newyellowClass);
	}
	if(name == "banana")
	{
		bananaClass* newbananaClass = new bananaClass(*(static_cast<bananaClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newbananaClass);
	}
	if(name == "fruit")
	{
		fruitClass* newfruitClass = new fruitClass(*(static_cast<fruitClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newfruitClass);
	}
	if(name == "apple")
	{
		appleClass* newappleClass = new appleClass(*(static_cast<appleClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newappleClass);
	}
	if(name == "on")
	{
		onClass* newonClass = new onClass(*(static_cast<onClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newonClass);
	}
	if(name == "tree")
	{
		treeClass* newtreeClass = new treeClass(*(static_cast<treeClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newtreeClass);
	}
	if(name == "green")
	{
		greenClass* newgreenClass = new greenClass(*(static_cast<greenClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newgreenClass);
	}
	return newGenericObject;
}

