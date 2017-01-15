#include "NLCgeneratedfunctionsWithNoSubjectArtificialClass.hpp"
#include "NLClibrary.hpp"

functionsWithNoSubjectArtificialClass::functionsWithNoSubjectArtificialClass(void)
{
	name = "functionsWithNoSubjectArtificial";
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

void functionsWithNoSubjectArtificialClass::mainFunction(vector<mainClass*>& mainClassList, vector<bikeClass*>& bikeClassList)
{
	vector<NLCgenericEntityClass*> referenceContextList0;
	vector<dogClass*> dogClassList;
	//Blue dogs are fat.
	//A blue dog rides the bike.
	vector<rideClass*> rideClassList;
	vector<rideClass*> ride1CategoryList;
	rideClass* ride1 = addNewEntityToLocalList<rideClass>(&(rideClassList));
	ride1CategoryList.push_back(ride1);
	addEntityToReferenceContextList(referenceContextList0, ride1, 2);
	vector<dogClass*> dog2SubjectCategoryList;
	vector<dogClass*> dog2CategoryList;
	dogClass* dog2 = addNewEntityToLocalList<dogClass>(&(dogClassList));
	dog2CategoryList.push_back(dog2);
	addEntityToReferenceContextList(referenceContextList0, dog2, 2);
	for(vector<dogClass*>::iterator iter1 = dog2CategoryList.begin(); iter1 < dog2CategoryList.end(); iter1++) 
	{
		dogClass* dog2 = *iter1;
		vector<fatClass*> fat1CategoryList;
		fatClass* fat1 = new fatClass();
		addProperty<dogClass, fatClass>(dog2, &(dog2->fatClassPropertyList), fat1);
		fat1CategoryList.push_back(fat1);
		addEntityToReferenceContextList(referenceContextList0, fat1, 2);
	}
	for(vector<dogClass*>::iterator iter1 = dog2CategoryList.begin(); iter1 < dog2CategoryList.end(); iter1++) 
	{
		dogClass* dog2 = *iter1;
		vector<blueClass*> blueClassList;
		vector<blueClass*> blue2CategoryList;
		blueClass* blue2 = addNewEntityToLocalList<blueClass>(&(blueClassList));
		blue2CategoryList.push_back(blue2);
		addEntityToReferenceContextList(referenceContextList0, blue2, 2);
		for(vector<blueClass*>::iterator iter2 = blue2CategoryList.begin(); iter2 < blue2CategoryList.end(); iter2++) 
		{
			blueClass* blue2 = *iter2;
			addProperty<dogClass, blueClass>(dog2, &(dog2->blueClassPropertyList), blue2);
		}
	}
	for(vector<dogClass*>::iterator iter1 = dog2CategoryList.begin(); iter1 < dog2CategoryList.end(); iter1++) 
	{
		dogClass* dog2 = *iter1;
		addToCategoryIfPassPluralDefiniteReferencingTests<dogClass, dogClass> (dog2SubjectCategoryList, dog2);
	}
	vector<bikeClass*> bike1ObjectCategoryList;
	vector<bikeClass*> bike1CategoryList;
	for(vector<bikeClass*>::iterator iter1 = bikeClassList.begin(); iter1 < bikeClassList.end(); iter1++) 
	{
		bikeClass* bike1 = *iter1;
		//Singular definite referencing tests
		addToCategoryIfPassSingularDefiniteReferencingTests<bikeClass, bikeClass> (bike1CategoryList, bike1);
	}
	if(!(bike1CategoryList.empty()))
	{
		bikeClass* bike1 = bike1CategoryList.back();
		bike1->lastSentenceReferenced.top() = 2;
		addToCategoryIfPassPluralDefiniteReferencingTests<bikeClass, bikeClass> (bike1ObjectCategoryList, bike1);
	}
	for(vector<dogClass*>::iterator iter1 = dog2SubjectCategoryList.begin(); iter1 < dog2SubjectCategoryList.end(); iter1++) 
	{
		dogClass* dog2 = *iter1;
		addActionSubject<rideClass, dogClass>(ride1, dog2, &(dog2->rideClassActionList), &(ride1->dogClassActionSubjectList));
	}
	for(vector<bikeClass*>::iterator iter1 = bike1ObjectCategoryList.begin(); iter1 < bike1ObjectCategoryList.end(); iter1++) 
	{
		bikeClass* bike1 = *iter1;
		addActionObject<rideClass, bikeClass>(ride1, bike1, &(bike1->rideClassActionIncomingList), &(ride1->bikeClassActionObjectList));
	}
	(new dogClass)->rideFunction(dog2SubjectCategoryList, rideClassList, bike1ObjectCategoryList);
	clearReferenceContextList(referenceContextList0);
}
