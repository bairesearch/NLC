#include "NLCgenerated.hpp"

NLCgenericEntityClass* generateObjectByName(string name)
{
	NLCgenericEntityClass* newGenericObject = NULL;
	if(name == "GIAsentence")
	{
		GIAsentenceClass* newGIAsentenceClass = new GIAsentenceClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newGIAsentenceClass);
	}
	if(name == "sentenceIndex")
	{
		sentenceIndexClass* newsentenceIndexClass = new sentenceIndexClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newsentenceIndexClass);
	}
	if(name == "int")
	{
		intClass* newintClass = new intClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newintClass);
	}
	if(name == "maxNumberOfWordsInSentence")
	{
		maxNumberOfWordsInSentenceClass* newmaxNumberOfWordsInSentenceClass = new maxNumberOfWordsInSentenceClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newmaxNumberOfWordsInSentenceClass);
	}
	if(name == "firstRelationInList")
	{
		firstRelationInListClass* newfirstRelationInListClass = new firstRelationInListClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newfirstRelationInListClass);
	}
	if(name == "GIArelation")
	{
		GIArelationClass* newGIArelationClass = new GIArelationClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newGIArelationClass);
	}
	if(name == "firstFeatureInList")
	{
		firstFeatureInListClass* newfirstFeatureInListClass = new firstFeatureInListClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newfirstFeatureInListClass);
	}
	if(name == "GIAfeature")
	{
		GIAfeatureClass* newGIAfeatureClass = new GIAfeatureClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newGIAfeatureClass);
	}
	if(name == "next")
	{
		nextClass* newnextClass = new nextClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newnextClass);
	}
	if(name == "previous")
	{
		previousClass* newpreviousClass = new previousClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newpreviousClass);
	}
	if(name == "isQuestion")
	{
		isQuestionClass* newisQuestionClass = new isQuestionClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newisQuestionClass);
	}
	if(name == "semanticParserSuccessful")
	{
		semanticParserSuccessfulClass* newsemanticParserSuccessfulClass = new semanticParserSuccessfulClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newsemanticParserSuccessfulClass);
	}
	if(name == "conditionEntityArtificialIndexCurrent")
	{
		conditionEntityArtificialIndexCurrentClass* newconditionEntityArtificialIndexCurrentClass = new conditionEntityArtificialIndexCurrentClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newconditionEntityArtificialIndexCurrentClass);
	}
	if(name == "")
	{
		Class* newClass = new Class();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newClass);
	}
	if(name == "void")
	{
		voidClass* newvoidClass = new voidClass();
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newvoidClass);
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
	if(name == "GIAsentence")
	{
		GIAsentenceClass* newGIAsentenceClass = new GIAsentenceClass(*(static_cast<GIAsentenceClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newGIAsentenceClass);
	}
	if(name == "sentenceIndex")
	{
		sentenceIndexClass* newsentenceIndexClass = new sentenceIndexClass(*(static_cast<sentenceIndexClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newsentenceIndexClass);
	}
	if(name == "int")
	{
		intClass* newintClass = new intClass(*(static_cast<intClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newintClass);
	}
	if(name == "maxNumberOfWordsInSentence")
	{
		maxNumberOfWordsInSentenceClass* newmaxNumberOfWordsInSentenceClass = new maxNumberOfWordsInSentenceClass(*(static_cast<maxNumberOfWordsInSentenceClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newmaxNumberOfWordsInSentenceClass);
	}
	if(name == "firstRelationInList")
	{
		firstRelationInListClass* newfirstRelationInListClass = new firstRelationInListClass(*(static_cast<firstRelationInListClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newfirstRelationInListClass);
	}
	if(name == "GIArelation")
	{
		GIArelationClass* newGIArelationClass = new GIArelationClass(*(static_cast<GIArelationClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newGIArelationClass);
	}
	if(name == "firstFeatureInList")
	{
		firstFeatureInListClass* newfirstFeatureInListClass = new firstFeatureInListClass(*(static_cast<firstFeatureInListClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newfirstFeatureInListClass);
	}
	if(name == "GIAfeature")
	{
		GIAfeatureClass* newGIAfeatureClass = new GIAfeatureClass(*(static_cast<GIAfeatureClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newGIAfeatureClass);
	}
	if(name == "next")
	{
		nextClass* newnextClass = new nextClass(*(static_cast<nextClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newnextClass);
	}
	if(name == "previous")
	{
		previousClass* newpreviousClass = new previousClass(*(static_cast<previousClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newpreviousClass);
	}
	if(name == "isQuestion")
	{
		isQuestionClass* newisQuestionClass = new isQuestionClass(*(static_cast<isQuestionClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newisQuestionClass);
	}
	if(name == "semanticParserSuccessful")
	{
		semanticParserSuccessfulClass* newsemanticParserSuccessfulClass = new semanticParserSuccessfulClass(*(static_cast<semanticParserSuccessfulClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newsemanticParserSuccessfulClass);
	}
	if(name == "conditionEntityArtificialIndexCurrent")
	{
		conditionEntityArtificialIndexCurrentClass* newconditionEntityArtificialIndexCurrentClass = new conditionEntityArtificialIndexCurrentClass(*(static_cast<conditionEntityArtificialIndexCurrentClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newconditionEntityArtificialIndexCurrentClass);
	}
	if(name == "")
	{
		Class* newClass = new Class(*(static_cast<Class*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newClass);
	}
	if(name == "void")
	{
		voidClass* newvoidClass = new voidClass(*(static_cast<voidClass*>(entityToCopy)));
		newGenericObject = reinterpret_cast<NLCgenericEntityClass*>(newvoidClass);
	}
	return newGenericObject;
}

