#include "NLCgenerated.hpp"

NLCgenericEntityClass* generateObjectByName(string name)
{
	NLCgenericEntityClass* newGenericObject = NULL;
	if(name == "functionsWithNoSubjectArtificial")
	{
		functionsWithNoSubjectArtificialClass* newfunctionsWithNoSubjectArtificialClass = new functionsWithNoSubjectArtificialClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newfunctionsWithNoSubjectArtificialClass);
	}
	if(name == "city")
	{
		cityClass* newcityClass = new cityClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newcityClass);
	}
	if(name == "name")
	{
		nameClass* newnameClass = new nameClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newnameClass);
	}
	if(name == "mouse")
	{
		mouseClass* newmouseClass = new mouseClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newmouseClass);
	}
	if(name == "happy")
	{
		happyClass* newhappyClass = new happyClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newhappyClass);
	}
	if(name == "rabbit")
	{
		rabbitClass* newrabbitClass = new rabbitClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newrabbitClass);
	}
	if(name == "be")
	{
		beClass* newbeClass = new beClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newbeClass);
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
	if(name == "city")
	{
		cityClass* newcityClass = new cityClass(*(static_cast<cityClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newcityClass);
	}
	if(name == "name")
	{
		nameClass* newnameClass = new nameClass(*(static_cast<nameClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newnameClass);
	}
	if(name == "mouse")
	{
		mouseClass* newmouseClass = new mouseClass(*(static_cast<mouseClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newmouseClass);
	}
	if(name == "happy")
	{
		happyClass* newhappyClass = new happyClass(*(static_cast<happyClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newhappyClass);
	}
	if(name == "rabbit")
	{
		rabbitClass* newrabbitClass = new rabbitClass(*(static_cast<rabbitClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newrabbitClass);
	}
	if(name == "be")
	{
		beClass* newbeClass = new beClass(*(static_cast<beClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newbeClass);
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
	return newGenericObject;
}

