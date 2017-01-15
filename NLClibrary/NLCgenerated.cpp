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
	if(name == "main")
	{
		mainClass* newmainClass = new mainClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newmainClass);
	}
	if(name == "blue")
	{
		blueClass* newblueClass = new blueClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newblueClass);
	}
	if(name == "dog")
	{
		dogClass* newdogClass = new dogClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newdogClass);
	}
	if(name == "fat")
	{
		fatClass* newfatClass = new fatClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newfatClass);
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
	if(name == "energy")
	{
		energyClass* newenergyClass = new energyClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newenergyClass);
	}
	if(name == "decrease")
	{
		decreaseClass* newdecreaseClass = new decreaseClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newdecreaseClass);
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
	if(name == "main")
	{
		mainClass* newmainClass = new mainClass(*(static_cast<mainClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newmainClass);
	}
	if(name == "blue")
	{
		blueClass* newblueClass = new blueClass(*(static_cast<blueClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newblueClass);
	}
	if(name == "dog")
	{
		dogClass* newdogClass = new dogClass(*(static_cast<dogClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newdogClass);
	}
	if(name == "fat")
	{
		fatClass* newfatClass = new fatClass(*(static_cast<fatClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newfatClass);
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
	if(name == "energy")
	{
		energyClass* newenergyClass = new energyClass(*(static_cast<energyClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newenergyClass);
	}
	if(name == "decrease")
	{
		decreaseClass* newdecreaseClass = new decreaseClass(*(static_cast<decreaseClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newdecreaseClass);
	}
	return newGenericObject;
}

