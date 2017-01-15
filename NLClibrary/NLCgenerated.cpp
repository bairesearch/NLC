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
	if(name == "africa")
	{
		africaClass* newafricaClass = new africaClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newafricaClass);
	}
	if(name == "country")
	{
		countryClass* newcountryClass = new countryClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newcountryClass);
	}
	if(name == "castle")
	{
		castleClass* newcastleClass = new castleClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newcastleClass);
	}
	if(name == "knight")
	{
		knightClass* newknightClass = new knightClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newknightClass);
	}
	if(name == "declare")
	{
		declareClass* newdeclareClass = new declareClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newdeclareClass);
	}
	if(name == "war")
	{
		warClass* newwarClass = new warClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newwarClass);
	}
	if(name == "terrible")
	{
		terribleClass* newterribleClass = new terribleClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newterribleClass);
	}
	if(name == "tom")
	{
		tomClass* newtomClass = new tomClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newtomClass);
	}
	if(name == "ride")
	{
		rideClass* newrideClass = new rideClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newrideClass);
	}
	if(name == "bike")
	{
		bikeClass* newbikeClass = new bikeClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newbikeClass);
	}
	if(name == "blue")
	{
		blueClass* newblueClass = new blueClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newblueClass);
	}
	if(name == "near")
	{
		nearClass* newnearClass = new nearClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newnearClass);
	}
	if(name == "garage")
	{
		garageClass* newgarageClass = new garageClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newgarageClass);
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
	if(name == "africa")
	{
		africaClass* newafricaClass = new africaClass(*(static_cast<africaClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newafricaClass);
	}
	if(name == "country")
	{
		countryClass* newcountryClass = new countryClass(*(static_cast<countryClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newcountryClass);
	}
	if(name == "castle")
	{
		castleClass* newcastleClass = new castleClass(*(static_cast<castleClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newcastleClass);
	}
	if(name == "knight")
	{
		knightClass* newknightClass = new knightClass(*(static_cast<knightClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newknightClass);
	}
	if(name == "declare")
	{
		declareClass* newdeclareClass = new declareClass(*(static_cast<declareClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newdeclareClass);
	}
	if(name == "war")
	{
		warClass* newwarClass = new warClass(*(static_cast<warClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newwarClass);
	}
	if(name == "terrible")
	{
		terribleClass* newterribleClass = new terribleClass(*(static_cast<terribleClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newterribleClass);
	}
	if(name == "tom")
	{
		tomClass* newtomClass = new tomClass(*(static_cast<tomClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newtomClass);
	}
	if(name == "ride")
	{
		rideClass* newrideClass = new rideClass(*(static_cast<rideClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newrideClass);
	}
	if(name == "bike")
	{
		bikeClass* newbikeClass = new bikeClass(*(static_cast<bikeClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newbikeClass);
	}
	if(name == "blue")
	{
		blueClass* newblueClass = new blueClass(*(static_cast<blueClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newblueClass);
	}
	if(name == "near")
	{
		nearClass* newnearClass = new nearClass(*(static_cast<nearClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newnearClass);
	}
	if(name == "garage")
	{
		garageClass* newgarageClass = new garageClass(*(static_cast<garageClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newgarageClass);
	}
	return newGenericObject;
}

