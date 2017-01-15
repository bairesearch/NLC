#include "NLCgeneratedfunctionsWithNoSubjectArtificialClass.hpp"
#include "NLClibrary.hpp"

functionsWithNoSubjectArtificialClass::functionsWithNoSubjectArtificialClass(void)
{
	name = "functionsWithNoSubjectArtificial";
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

void functionsWithNoSubjectArtificialClass::NLCimplicitlyDeclaredFunctionArtificialFunction(vector<NLCimplicitlyDeclaredFunctionArtificialClass*>& NLCimplicitlyDeclaredFunctionArtificialClassList, vector<boatClass*>& boatClassList, vector<cabbageClass*>& cabbageClassList, vector<sunClass*>& sunClassList)
{
	vector<NLCgenericEntityClass*> referenceContextList0;
	//2 cabbages are near the boat.
	vector<cabbageClass*> cabbage1SubjectCategoryList;
	vector<cabbageClass*> cabbage1CategoryList;
	for(int index1 = 0; index1 < 2; index1++) 
	{
		cabbageClass* cabbage1 = addNewEntityToLocalList<cabbageClass>(&(cabbageClassList));
		cabbage1CategoryList.push_back(cabbage1);
		addEntityToReferenceContextList(referenceContextList0, cabbage1, 1);
	}
	for(vector<cabbageClass*>::iterator iter1 = cabbage1CategoryList.begin(); iter1 < cabbage1CategoryList.end(); iter1++) 
	{
		cabbageClass* cabbage1 = *iter1;
		addToCategoryIfPassPluralDefiniteReferencingTests<cabbageClass, cabbageClass> (cabbage1SubjectCategoryList, cabbage1);
	}
	vector<boatClass*> boat1ObjectCategoryList;
	vector<boatClass*> boat1CategoryList;
	for(vector<boatClass*>::iterator iter1 = boatClassList.begin(); iter1 < boatClassList.end(); iter1++) 
	{
		boatClass* boat1 = *iter1;
		//Singular definite referencing tests
		addToCategoryIfPassSingularDefiniteReferencingTests<boatClass, boatClass> (boat1CategoryList, boat1);
	}
	if(!(boat1CategoryList.empty()))
	{
		boatClass* boat1 = boat1CategoryList.back();
		boat1->lastSentenceReferenced.top() = 1;
		addToCategoryIfPassPluralDefiniteReferencingTests<boatClass, boatClass> (boat1ObjectCategoryList, boat1);
	}
	for(vector<cabbageClass*>::iterator iter1 = cabbage1SubjectCategoryList.begin(); iter1 < cabbage1SubjectCategoryList.end(); iter1++) 
	{
		cabbageClass* cabbage1 = *iter1;
		for(vector<boatClass*>::iterator iter2 = boat1ObjectCategoryList.begin(); iter2 < boat1ObjectCategoryList.end(); iter2++) 
		{
			boatClass* boat1 = *iter2;
			addCondition<cabbageClass, nearClass, boatClass>(cabbage1, &(cabbage1->nearClassboatClassConditionList), "near", boat1);
			addCondition<boatClass, nearClass, cabbageClass>(boat1, &(boat1->nearClasscabbageClassConditionList), "near", cabbage1);
		}
	}
	//Cabbage 1 is brown.
	vector<cabbageClass*> cabbage2SubjectCategoryList;
	vector<cabbageClass*> cabbage2CategoryList;
	if(1 <= cabbageClassList.size())
	{
		cabbageClass* cabbage2 = cabbageClassList.at(1-1);
		//Singular definite referencing tests
		addToCategoryIfPassSingularDefiniteReferencingTests<cabbageClass, cabbageClass> (cabbage2CategoryList, cabbage2);
	}
	if(!(cabbage2CategoryList.empty()))
	{
		cabbageClass* cabbage2 = cabbage2CategoryList.back();
		cabbage2->lastSentenceReferenced.top() = 2;
		addToCategoryIfPassPluralDefiniteReferencingTests<cabbageClass, cabbageClass> (cabbage2SubjectCategoryList, cabbage2);
	}
	vector<brownClass*> brown1ObjectCategoryList;
	vector<brownClass*> brownClassList;
	vector<brownClass*> brown1CategoryList;
	brownClass* brown1 = addNewEntityToLocalList<brownClass>(&(brownClassList));
	brown1CategoryList.push_back(brown1);
	addEntityToReferenceContextList(referenceContextList0, brown1, 2);
	for(vector<brownClass*>::iterator iter1 = brown1CategoryList.begin(); iter1 < brown1CategoryList.end(); iter1++) 
	{
		brownClass* brown1 = *iter1;
		addToCategoryIfPassPluralDefiniteReferencingTests<brownClass, brownClass> (brown1ObjectCategoryList, brown1);
	}
	for(vector<cabbageClass*>::iterator iter1 = cabbage2SubjectCategoryList.begin(); iter1 < cabbage2SubjectCategoryList.end(); iter1++) 
	{
		cabbageClass* cabbage2 = *iter1;
		for(vector<brownClass*>::iterator iter2 = brown1ObjectCategoryList.begin(); iter2 < brown1ObjectCategoryList.end(); iter2++) 
		{
			brownClass* brown1 = *iter2;
			addProperty<cabbageClass, brownClass>(cabbage2, &(cabbage2->brownClassPropertyList), brown1);
		}
	}
	//Cabbage 2 is happy.
	vector<cabbageClass*> cabbage3SubjectCategoryList;
	vector<cabbageClass*> cabbage3CategoryList;
	if(2 <= cabbageClassList.size())
	{
		cabbageClass* cabbage3 = cabbageClassList.at(2-1);
		//Singular definite referencing tests
		addToCategoryIfPassSingularDefiniteReferencingTests<cabbageClass, cabbageClass> (cabbage3CategoryList, cabbage3);
	}
	if(!(cabbage3CategoryList.empty()))
	{
		cabbageClass* cabbage3 = cabbage3CategoryList.back();
		cabbage3->lastSentenceReferenced.top() = 3;
		addToCategoryIfPassPluralDefiniteReferencingTests<cabbageClass, cabbageClass> (cabbage3SubjectCategoryList, cabbage3);
	}
	vector<happyClass*> happy1ObjectCategoryList;
	vector<happyClass*> happyClassList;
	vector<happyClass*> happy1CategoryList;
	happyClass* happy1 = addNewEntityToLocalList<happyClass>(&(happyClassList));
	happy1CategoryList.push_back(happy1);
	addEntityToReferenceContextList(referenceContextList0, happy1, 3);
	for(vector<happyClass*>::iterator iter1 = happy1CategoryList.begin(); iter1 < happy1CategoryList.end(); iter1++) 
	{
		happyClass* happy1 = *iter1;
		addToCategoryIfPassPluralDefiniteReferencingTests<happyClass, happyClass> (happy1ObjectCategoryList, happy1);
	}
	for(vector<cabbageClass*>::iterator iter1 = cabbage3SubjectCategoryList.begin(); iter1 < cabbage3SubjectCategoryList.end(); iter1++) 
	{
		cabbageClass* cabbage3 = *iter1;
		for(vector<happyClass*>::iterator iter2 = happy1ObjectCategoryList.begin(); iter2 < happy1ObjectCategoryList.end(); iter2++) 
		{
			happyClass* happy1 = *iter2;
			addProperty<cabbageClass, happyClass>(cabbage3, &(cabbage3->happyClassPropertyList), happy1);
		}
	}
	//The sun fights.
	vector<fightClass*> fightClassList;
	vector<fightClass*> fight1CategoryList;
	fightClass* fight1 = addNewEntityToLocalList<fightClass>(&(fightClassList));
	fight1CategoryList.push_back(fight1);
	addEntityToReferenceContextList(referenceContextList0, fight1, 4);
	vector<sunClass*> sun1SubjectCategoryList;
	vector<sunClass*> sun1CategoryList;
	for(vector<sunClass*>::iterator iter1 = sunClassList.begin(); iter1 < sunClassList.end(); iter1++) 
	{
		sunClass* sun1 = *iter1;
		//Singular definite referencing tests
		addToCategoryIfPassSingularDefiniteReferencingTests<sunClass, sunClass> (sun1CategoryList, sun1);
	}
	if(!(sun1CategoryList.empty()))
	{
		sunClass* sun1 = sun1CategoryList.back();
		sun1->lastSentenceReferenced.top() = 4;
		addToCategoryIfPassPluralDefiniteReferencingTests<sunClass, sunClass> (sun1SubjectCategoryList, sun1);
	}
	for(vector<sunClass*>::iterator iter1 = sun1SubjectCategoryList.begin(); iter1 < sun1SubjectCategoryList.end(); iter1++) 
	{
		sunClass* sun1 = *iter1;
		addActionSubject<fightClass, sunClass>(fight1, sun1, &(sun1->fightClassActionList), &(fight1->sunClassActionSubjectList));
	}
	(new sunClass)->fightFunction(sun1SubjectCategoryList, fightClassList);
	//If the sun fights, print the cabbage.
	bool thesunfights5 = false;
	vector<sunClass*> sun2CategoryList;
	int sun2CategoryListPropertyCount = 0;
	for(vector<sunClass*>::iterator iter1 = sunClassList.begin(); iter1 < sunClassList.end(); iter1++) 
	{
		sunClass* sun2 = *iter1;
		for(vector<fightClass*>::iterator iter2 = sun2->fightClassActionList.begin(); iter2 < sun2->fightClassActionList.end(); iter2++) 
		{
			fightClass* fight2 = *iter2;
			//Singular definite referencing tests
			addToCategoryIfPassSingularDefiniteReferencingTests<sunClass, sunClass> (sun2CategoryList, sun2);
			sun2CategoryListPropertyCount = sun2CategoryListPropertyCount + 1;
		}
	}
	if(!(sun2CategoryList.empty()))
	{
		sunClass* sun2 = sun2CategoryList.back();
		sun2->lastSentenceReferenced.top() = 5;
		thesunfights5 = true;
	}
	if(thesunfights5print )
	{
		vector<NLCgenericEntityClass*> referenceContextList1;
		//
		clearReferenceContextList(referenceContextList1);
	}
	clearReferenceContextList(referenceContextList0);
}

int main()
{
	vector<NLCimplicitlyDeclaredFunctionArtificialClass*> NLCimplicitlyDeclaredFunctionArtificialClassList;
	vector<boatClass*> boatClassList;
	vector<cabbageClass*> cabbageClassList;
	vector<sunClass*> sunClassList;
	(new functionsWithNoSubjectArtificialClass)->NLCimplicitlyDeclaredFunctionArtificialFunction(NLCimplicitlyDeclaredFunctionArtificialClassList, boatClassList, cabbageClassList, sunClassList);
}
