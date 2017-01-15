#include "NLCgeneratedfunctionsWithNoSubjectArtificialClass.hpp"
#include "NLClibrary.hpp"

functionsWithNoSubjectArtificialClass::functionsWithNoSubjectArtificialClass(void)
{
	name = "functionsWithNoSubjectArtificial";
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

void functionsWithNoSubjectArtificialClass::NLCimplicitlyDeclaredFunctionArtificialFunction(vector<NLCimplicitlyDeclaredFunctionArtificialClass*>& NLCimplicitlyDeclaredFunctionArtificialClassList, vector<africaClass*>& africaClassList, vector<tomClass*>& tomClassList, vector<bikeClass*>& bikeClassList, vector<garageClass*>& garageClassList)
{
	vector<NLCgenericEntityClass*> referenceContextList0;
	vector<castleClass*> castleClassList;
	vector<knightClass*> knightClassList;
	vector<warClass*> warClassList;
	vector<countryClass*> countryClassList;
	//Africa is a country.
	vector<africaClass*> africa1SubjectCategoryList;
	vector<africaClass*> africa1CategoryList;
	for(vector<africaClass*>::iterator iter1 = africaClassList.begin(); iter1 < africaClassList.end(); iter1++) 
	{
		africaClass* africa1 = *iter1;
		//Singular definite referencing tests
		addToCategoryIfPassSingularDefiniteReferencingTests<africaClass, africaClass> (africa1CategoryList, africa1);
	}
	if(!(africa1CategoryList.empty()))
	{
		africaClass* africa1 = africa1CategoryList.back();
		africa1->lastSentenceReferenced.top() = 1;
		addToCategoryIfPassPluralDefiniteReferencingTests<africaClass, africaClass> (africa1SubjectCategoryList, africa1);
	}
	for(vector<africaClass*>::iterator iter1 = africa1SubjectCategoryList.begin(); iter1 < africa1SubjectCategoryList.end(); iter1++) 
	{
		africaClass* africa1 = *iter1;
		if(checkParentClassName(static_cast<NLCgenericEntityClass*>(new countryClass), "africa"))
		{
			countryClass* country1 = static_cast<countryClass*>(africa1);
			country1->name = "country";
			addEntityToLocalList<countryClass>(&(countryClassList), country1);
		}
	}
	//Africa has a castle with knights.
	vector<africaClass*> africa2SubjectCategoryList;
	vector<africaClass*> africa2CategoryList;
	for(vector<africaClass*>::iterator iter1 = africaClassList.begin(); iter1 < africaClassList.end(); iter1++) 
	{
		africaClass* africa2 = *iter1;
		//Singular definite referencing tests
		addToCategoryIfPassSingularDefiniteReferencingTests<africaClass, africaClass> (africa2CategoryList, africa2);
	}
	if(!(africa2CategoryList.empty()))
	{
		africaClass* africa2 = africa2CategoryList.back();
		africa2->lastSentenceReferenced.top() = 2;
		addToCategoryIfPassPluralDefiniteReferencingTests<africaClass, africaClass> (africa2SubjectCategoryList, africa2);
	}
	vector<castleClass*> castle1ObjectCategoryList;
	vector<castleClass*> castle1CategoryList;
	castleClass* castle1 = addNewEntityToLocalList<castleClass>(&(castleClassList));
	castle1CategoryList.push_back(castle1);
	addEntityToReferenceContextList(referenceContextList0, castle1, 2);
	for(vector<castleClass*>::iterator iter1 = castle1CategoryList.begin(); iter1 < castle1CategoryList.end(); iter1++) 
	{
		castleClass* castle1 = *iter1;
		vector<knightClass*> knight1CategoryList;
		knightClass* knight1 = addNewEntityToLocalList<knightClass>(&(knightClassList));
		knight1CategoryList.push_back(knight1);
		addEntityToReferenceContextList(referenceContextList0, knight1, 2);
		for(vector<knightClass*>::iterator iter2 = knight1CategoryList.begin(); iter2 < knight1CategoryList.end(); iter2++) 
		{
			knightClass* knight1 = *iter2;
			addProperty<castleClass, knightClass>(castle1, &(castle1->knightClassPropertyList), knight1);
		}
	}
	for(vector<castleClass*>::iterator iter1 = castle1CategoryList.begin(); iter1 < castle1CategoryList.end(); iter1++) 
	{
		castleClass* castle1 = *iter1;
		addToCategoryIfPassPluralDefiniteReferencingTests<castleClass, castleClass> (castle1ObjectCategoryList, castle1);
	}
	for(vector<africaClass*>::iterator iter1 = africa2SubjectCategoryList.begin(); iter1 < africa2SubjectCategoryList.end(); iter1++) 
	{
		africaClass* africa2 = *iter1;
		for(vector<castleClass*>::iterator iter2 = castle1ObjectCategoryList.begin(); iter2 < castle1ObjectCategoryList.end(); iter2++) 
		{
			castleClass* castle1 = *iter2;
			addProperty<africaClass, castleClass>(africa2, &(africa2->castleClassPropertyList), castle1);
		}
	}
	//The castle with knights declares a terrible war.
	vector<declareClass*> declareClassList;
	vector<declareClass*> declare1CategoryList;
	declareClass* declare1 = addNewEntityToLocalList<declareClass>(&(declareClassList));
	declare1CategoryList.push_back(declare1);
	addEntityToReferenceContextList(referenceContextList0, declare1, 3);
	vector<castleClass*> castle2SubjectCategoryList;
	vector<castleClass*> castle2CategoryList;
	for(vector<castleClass*>::iterator iter1 = castleClassList.begin(); iter1 < castleClassList.end(); iter1++) 
	{
		castleClass* castle2 = *iter1;
		for(vector<knightClass*>::iterator iter2 = castle2->knightClassPropertyList.begin(); iter2 < castle2->knightClassPropertyList.end(); iter2++) 
		{
			knightClass* knight2 = *iter2;
			//Singular definite referencing tests
			addToCategoryIfPassSingularDefiniteReferencingTests<castleClass, castleClass> (castle2CategoryList, castle2);
		}
	}
	if(!(castle2CategoryList.empty()))
	{
		castleClass* castle2 = castle2CategoryList.back();
		castle2->lastSentenceReferenced.top() = 3;
		addToCategoryIfPassPluralDefiniteReferencingTests<castleClass, castleClass> (castle2SubjectCategoryList, castle2);
	}
	vector<warClass*> war1ObjectCategoryList;
	vector<warClass*> war1CategoryList;
	warClass* war1 = addNewEntityToLocalList<warClass>(&(warClassList));
	war1CategoryList.push_back(war1);
	addEntityToReferenceContextList(referenceContextList0, war1, 3);
	for(vector<warClass*>::iterator iter1 = war1CategoryList.begin(); iter1 < war1CategoryList.end(); iter1++) 
	{
		warClass* war1 = *iter1;
		vector<terribleClass*> terribleClassList;
		vector<terribleClass*> terrible1CategoryList;
		terribleClass* terrible1 = addNewEntityToLocalList<terribleClass>(&(terribleClassList));
		terrible1CategoryList.push_back(terrible1);
		addEntityToReferenceContextList(referenceContextList0, terrible1, 3);
		for(vector<terribleClass*>::iterator iter2 = terrible1CategoryList.begin(); iter2 < terrible1CategoryList.end(); iter2++) 
		{
			terribleClass* terrible1 = *iter2;
			addProperty<warClass, terribleClass>(war1, &(war1->terribleClassPropertyList), terrible1);
		}
	}
	for(vector<warClass*>::iterator iter1 = war1CategoryList.begin(); iter1 < war1CategoryList.end(); iter1++) 
	{
		warClass* war1 = *iter1;
		addToCategoryIfPassPluralDefiniteReferencingTests<warClass, warClass> (war1ObjectCategoryList, war1);
	}
	for(vector<castleClass*>::iterator iter1 = castle2SubjectCategoryList.begin(); iter1 < castle2SubjectCategoryList.end(); iter1++) 
	{
		castleClass* castle2 = *iter1;
		addActionSubject<declareClass, castleClass>(declare1, castle2, &(castle2->declareClassActionList), &(declare1->castleClassActionSubjectList));
	}
	for(vector<warClass*>::iterator iter1 = war1ObjectCategoryList.begin(); iter1 < war1ObjectCategoryList.end(); iter1++) 
	{
		warClass* war1 = *iter1;
		addActionObject<declareClass, warClass>(declare1, war1, &(war1->declareClassActionIncomingList), &(declare1->warClassActionObjectList));
	}
	(new castleClass)->declareFunction(castle2SubjectCategoryList, declareClassList, war1ObjectCategoryList);
	//Tom rides the blue bike that is near the garage.
	vector<rideClass*> rideClassList;
	vector<rideClass*> ride1CategoryList;
	rideClass* ride1 = addNewEntityToLocalList<rideClass>(&(rideClassList));
	ride1CategoryList.push_back(ride1);
	addEntityToReferenceContextList(referenceContextList0, ride1, 4);
	vector<tomClass*> tom1SubjectCategoryList;
	vector<tomClass*> tom1CategoryList;
	for(vector<tomClass*>::iterator iter1 = tomClassList.begin(); iter1 < tomClassList.end(); iter1++) 
	{
		tomClass* tom1 = *iter1;
		//Singular definite referencing tests
		addToCategoryIfPassSingularDefiniteReferencingTests<tomClass, tomClass> (tom1CategoryList, tom1);
	}
	if(!(tom1CategoryList.empty()))
	{
		tomClass* tom1 = tom1CategoryList.back();
		tom1->lastSentenceReferenced.top() = 4;
		addToCategoryIfPassPluralDefiniteReferencingTests<tomClass, tomClass> (tom1SubjectCategoryList, tom1);
	}
	vector<bikeClass*> bike1ObjectCategoryList;
	vector<bikeClass*> bike1CategoryList;
	for(vector<bikeClass*>::iterator iter1 = bikeClassList.begin(); iter1 < bikeClassList.end(); iter1++) 
	{
		bikeClass* bike1 = *iter1;
		for(vector<blueClass*>::iterator iter2 = bike1->blueClassPropertyList.begin(); iter2 < bike1->blueClassPropertyList.end(); iter2++) 
		{
			blueClass* blue1 = *iter2;
			for(unordered_map<nearClass*, garageClass*>::iterator iter3 = bike1->nearClassgarageClassConditionList.begin(); iter3 != bike1->nearClassgarageClassConditionList.end(); iter3++) 
			{
				garageClass* garage1 = iter3->second;
				garageClass* garageCandidate = garage1;
				vector<garageClass*> garage1CategoryList;
				for(vector<garageClass*>::iterator iter4 = garageClassList.begin(); iter4 < garageClassList.end(); iter4++) 
				{
					garageClass* garage1 = *iter4;
					//Singular definite referencing tests
					addToCategoryIfPassSingularDefiniteReferencingTests<garageClass, garageClass> (garage1CategoryList, garage1);
				}
				if(!(garage1CategoryList.empty()))
				{
					garageClass* garage1 = garage1CategoryList.back();
					garage1->lastSentenceReferenced.top() = 4;
					if(garageCandidate == garage1)
					{
						//Singular definite referencing tests
						addToCategoryIfPassSingularDefiniteReferencingTests<bikeClass, bikeClass> (bike1CategoryList, bike1);
					}
				}
			}
		}
	}
	if(!(bike1CategoryList.empty()))
	{
		bikeClass* bike1 = bike1CategoryList.back();
		bike1->lastSentenceReferenced.top() = 4;
		addToCategoryIfPassPluralDefiniteReferencingTests<bikeClass, bikeClass> (bike1ObjectCategoryList, bike1);
	}
	for(vector<tomClass*>::iterator iter1 = tom1SubjectCategoryList.begin(); iter1 < tom1SubjectCategoryList.end(); iter1++) 
	{
		tomClass* tom1 = *iter1;
		addActionSubject<rideClass, tomClass>(ride1, tom1, &(tom1->rideClassActionList), &(ride1->tomClassActionSubjectList));
	}
	for(vector<bikeClass*>::iterator iter1 = bike1ObjectCategoryList.begin(); iter1 < bike1ObjectCategoryList.end(); iter1++) 
	{
		bikeClass* bike1 = *iter1;
		addActionObject<rideClass, bikeClass>(ride1, bike1, &(bike1->rideClassActionIncomingList), &(ride1->bikeClassActionObjectList));
	}
	(new tomClass)->rideFunction(tom1SubjectCategoryList, rideClassList, bike1ObjectCategoryList);
	//A country is happy.
	vector<countryClass*> country2SubjectCategoryList;
	vector<countryClass*> country2CategoryList;
	countryClass* country2 = addNewEntityToLocalList<countryClass>(&(countryClassList));
	country2CategoryList.push_back(country2);
	addEntityToReferenceContextList(referenceContextList0, country2, 5);
	for(vector<countryClass*>::iterator iter1 = country2CategoryList.begin(); iter1 < country2CategoryList.end(); iter1++) 
	{
		countryClass* country2 = *iter1;
		addToCategoryIfPassPluralDefiniteReferencingTests<countryClass, countryClass> (country2SubjectCategoryList, country2);
	}
	vector<happyClass*> happy1ObjectCategoryList;
	vector<happyClass*> happyClassList;
	vector<happyClass*> happy1CategoryList;
	happyClass* happy1 = addNewEntityToLocalList<happyClass>(&(happyClassList));
	happy1CategoryList.push_back(happy1);
	addEntityToReferenceContextList(referenceContextList0, happy1, 5);
	for(vector<happyClass*>::iterator iter1 = happy1CategoryList.begin(); iter1 < happy1CategoryList.end(); iter1++) 
	{
		happyClass* happy1 = *iter1;
		addToCategoryIfPassPluralDefiniteReferencingTests<happyClass, happyClass> (happy1ObjectCategoryList, happy1);
	}
	for(vector<countryClass*>::iterator iter1 = country2SubjectCategoryList.begin(); iter1 < country2SubjectCategoryList.end(); iter1++) 
	{
		countryClass* country2 = *iter1;
		for(vector<happyClass*>::iterator iter2 = happy1ObjectCategoryList.begin(); iter2 < happy1ObjectCategoryList.end(); iter2++) 
		{
			happyClass* happy1 = *iter2;
			addProperty<countryClass, happyClass>(country2, &(country2->happyClassPropertyList), happy1);
		}
	}
	clearReferenceContextList(referenceContextList0);
}

int main()
{
	vector<NLCimplicitlyDeclaredFunctionArtificialClass*> NLCimplicitlyDeclaredFunctionArtificialClassList;
	vector<africaClass*> africaClassList;
	vector<tomClass*> tomClassList;
	vector<bikeClass*> bikeClassList;
	vector<garageClass*> garageClassList;
	(new functionsWithNoSubjectArtificialClass)->NLCimplicitlyDeclaredFunctionArtificialFunction(NLCimplicitlyDeclaredFunctionArtificialClassList, africaClassList, tomClassList, bikeClassList, garageClassList);
}
