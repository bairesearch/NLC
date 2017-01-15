#include "NLCgeneratedfunctionsWithNoSubjectArtificialClass.hpp"
#include "NLClibrary.hpp"

functionsWithNoSubjectArtificialClass::functionsWithNoSubjectArtificialClass(void)
{
	name = "functionsWithNoSubjectArtificial";
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

void functionsWithNoSubjectArtificialClass::NLCimplicitlyDeclaredFunctionArtificialFunction(vector<NLCimplicitlyDeclaredFunctionArtificialClass*>& NLCimplicitlyDeclaredFunctionArtificialClassList)
{
	vector<NLCgenericEntityClass*> referenceContextList0;
	vector<appleClass*> appleClassList;
	vector<pieClass*> pieClassList;
	//An apple is near a pie.
	vector<appleClass*> apple1SubjectCategoryList;
	vector<appleClass*> apple1CategoryList;
	appleClass* apple1 = addNewEntityToLocalList<appleClass>(&(appleClassList));
	apple1CategoryList.push_back(apple1);
	addEntityToReferenceContextList(referenceContextList0, apple1, 1);
	for(vector<appleClass*>::iterator iter1 = apple1CategoryList.begin(); iter1 < apple1CategoryList.end(); iter1++) 
	{
		appleClass* apple1 = *iter1;
		addToCategoryIfPassPluralDefiniteReferencingTests<appleClass, appleClass> (apple1SubjectCategoryList, apple1);
	}
	vector<pieClass*> pie1ObjectCategoryList;
	vector<pieClass*> pie1CategoryList;
	pieClass* pie1 = addNewEntityToLocalList<pieClass>(&(pieClassList));
	pie1CategoryList.push_back(pie1);
	addEntityToReferenceContextList(referenceContextList0, pie1, 1);
	for(vector<pieClass*>::iterator iter1 = pie1CategoryList.begin(); iter1 < pie1CategoryList.end(); iter1++) 
	{
		pieClass* pie1 = *iter1;
		addToCategoryIfPassPluralDefiniteReferencingTests<pieClass, pieClass> (pie1ObjectCategoryList, pie1);
	}
	for(vector<appleClass*>::iterator iter1 = apple1SubjectCategoryList.begin(); iter1 < apple1SubjectCategoryList.end(); iter1++) 
	{
		appleClass* apple1 = *iter1;
		for(vector<pieClass*>::iterator iter2 = pie1ObjectCategoryList.begin(); iter2 < pie1ObjectCategoryList.end(); iter2++) 
		{
			pieClass* pie1 = *iter2;
			addCondition<appleClass, nearClass, pieClass>(apple1, &(apple1->nearClasspieClassConditionList), "near", pie1);
			addCondition<pieClass, nearClass, appleClass>(pie1, &(pie1->nearClassappleClassConditionList), "near", apple1);
		}
	}
	//If the apple is near the pie
	bool theappleisnearthepie2 = false;
	vector<appleClass*> apple2CategoryList;
	int apple2CategoryListPropertyCount = 0;
	for(vector<appleClass*>::iterator iter1 = appleClassList.begin(); iter1 < appleClassList.end(); iter1++) 
	{
		appleClass* apple2 = *iter1;
		for(unordered_map<nearClass*, pieClass*>::iterator iter2 = apple2->nearClasspieClassConditionList.begin(); iter2 != apple2->nearClasspieClassConditionList.end(); iter2++) 
		{
			pieClass* pie2 = iter2->second;
			pieClass* pieCandidate = pie2;
			vector<pieClass*> pie2CategoryList;
			int pie2CategoryListPropertyCount = 0;
			for(vector<pieClass*>::iterator iter3 = pieClassList.begin(); iter3 < pieClassList.end(); iter3++) 
			{
				pieClass* pie2 = *iter3;
				//Singular definite referencing tests
				addToCategoryIfPassSingularDefiniteReferencingTests<pieClass, pieClass> (pie2CategoryList, pie2);
				pie2CategoryListPropertyCount = pie2CategoryListPropertyCount + 1;
			}
			if(!(pie2CategoryList.empty()))
			{
				pieClass* pie2 = pie2CategoryList.back();
				pie2->lastSentenceReferenced.top() = 2;
				if(pieCandidate == pie2)
				{
					//Singular definite referencing tests
					addToCategoryIfPassSingularDefiniteReferencingTests<appleClass, appleClass> (apple2CategoryList, apple2);
					apple2CategoryListPropertyCount = apple2CategoryListPropertyCount + 1;
				}
			}
		}
	}
	if(!(apple2CategoryList.empty()))
	{
		appleClass* apple2 = apple2CategoryList.back();
		apple2->lastSentenceReferenced.top() = 2;
		theappleisnearthepie2 = true;
	}
	if(theappleisnearthepie2)
	{
		vector<NLCgenericEntityClass*> referenceContextList1;
		//The apple is happy.
		vector<appleClass*> apple3SubjectCategoryList;
		vector<appleClass*> apple3CategoryList;
		for(vector<appleClass*>::iterator iter2 = appleClassList.begin(); iter2 < appleClassList.end(); iter2++) 
		{
			appleClass* apple3 = *iter2;
			//Singular definite referencing tests
			addToCategoryIfPassSingularDefiniteReferencingTests<appleClass, appleClass> (apple3CategoryList, apple3);
		}
		if(!(apple3CategoryList.empty()))
		{
			appleClass* apple3 = apple3CategoryList.back();
			apple3->lastSentenceReferenced.top() = 3;
			addToCategoryIfPassPluralDefiniteReferencingTests<appleClass, appleClass> (apple3SubjectCategoryList, apple3);
		}
		vector<happyClass*> happy1ObjectCategoryList;
		vector<happyClass*> happyClassList;
		vector<happyClass*> happy1CategoryList;
		happyClass* happy1 = addNewEntityToLocalList<happyClass>(&(happyClassList));
		happy1CategoryList.push_back(happy1);
		addEntityToReferenceContextList(referenceContextList1, happy1, 3);
		for(vector<happyClass*>::iterator iter2 = happy1CategoryList.begin(); iter2 < happy1CategoryList.end(); iter2++) 
		{
			happyClass* happy1 = *iter2;
			addToCategoryIfPassPluralDefiniteReferencingTests<happyClass, happyClass> (happy1ObjectCategoryList, happy1);
		}
		for(vector<appleClass*>::iterator iter2 = apple3SubjectCategoryList.begin(); iter2 < apple3SubjectCategoryList.end(); iter2++) 
		{
			appleClass* apple3 = *iter2;
			for(vector<happyClass*>::iterator iter3 = happy1ObjectCategoryList.begin(); iter3 < happy1ObjectCategoryList.end(); iter3++) 
			{
				happyClass* happy1 = *iter3;
				addProperty<appleClass, happyClass>(apple3, &(apple3->happyClassPropertyList), happy1);
			}
		}
		clearReferenceContextList(referenceContextList1);
	}
	//Print the apple.
	vector<printClass*> printClassList;
	vector<printClass*> print1CategoryList;
	printClass* print1 = addNewEntityToLocalList<printClass>(&(printClassList));
	print1CategoryList.push_back(print1);
	addEntityToReferenceContextList(referenceContextList0, print1, 4);
	vector<appleClass*> apple4ObjectCategoryList;
	vector<appleClass*> apple4CategoryList;
	for(vector<appleClass*>::iterator iter1 = appleClassList.begin(); iter1 < appleClassList.end(); iter1++) 
	{
		appleClass* apple4 = *iter1;
		//Singular definite referencing tests
		addToCategoryIfPassSingularDefiniteReferencingTests<appleClass, appleClass> (apple4CategoryList, apple4);
	}
	if(!(apple4CategoryList.empty()))
	{
		appleClass* apple4 = apple4CategoryList.back();
		apple4->lastSentenceReferenced.top() = 4;
		addToCategoryIfPassPluralDefiniteReferencingTests<appleClass, appleClass> (apple4ObjectCategoryList, apple4);
	}
	for(vector<appleClass*>::iterator iter1 = apple4ObjectCategoryList.begin(); iter1 < apple4ObjectCategoryList.end(); iter1++) 
	{
		appleClass* apple4 = *iter1;
		addActionObject<printClass, appleClass>(print1, apple4, &(apple4->printClassActionIncomingList), &(print1->appleClassActionObjectList));
	}
	printFunction(castVector<printClass, NLCgenericEntityClass>(printClassList), castVector<appleClass, NLCgenericEntityClass>(apple4ObjectCategoryList));
	clearReferenceContextList(referenceContextList0);
}

int main()
{
	vector<NLCimplicitlyDeclaredFunctionArtificialClass*> NLCimplicitlyDeclaredFunctionArtificialClassList;
	(new functionsWithNoSubjectArtificialClass)->NLCimplicitlyDeclaredFunctionArtificialFunction(NLCimplicitlyDeclaredFunctionArtificialClassList);
}
