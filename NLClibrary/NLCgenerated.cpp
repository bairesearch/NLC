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
	if(name == "on")
	{
		onClass* newonClass = new onClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newonClass);
	}
	if(name == "table")
	{
		tableClass* newtableClass = new tableClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newtableClass);
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
	if(name == "tasty")
	{
		tastyClass* newtastyClass = new tastyClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newtastyClass);
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
	if(name == "on")
	{
		onClass* newonClass = new onClass(*(static_cast<onClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newonClass);
	}
	if(name == "table")
	{
		tableClass* newtableClass = new tableClass(*(static_cast<tableClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newtableClass);
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
	if(name == "tasty")
	{
		tastyClass* newtastyClass = new tastyClass(*(static_cast<tastyClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newtastyClass);
	}
	return newGenericObject;
}

