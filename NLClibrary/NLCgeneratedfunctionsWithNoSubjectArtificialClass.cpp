#include "NLCgeneratedfunctionsWithNoSubjectArtificialClass.hpp"
#include "NLClibrary.hpp"

functionsWithNoSubjectArtificialClass::functionsWithNoSubjectArtificialClass(void)
{
	name = "functionsWithNoSubjectArtificial";
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

void functionsWithNoSubjectArtificialClass::NLCimplicitlyDeclaredFunctionArtificialFunction(vector<NLCimplicitlyDeclaredFunctionArtificialClass*>& NLCimplicitlyDeclaredFunctionArtificialClassList, vector<bananaClass*>& bananaClassList, vector<treeClass*>& treeClassList)
{
	vector<NLCgenericEntityClass*> referenceContextList0;
	vector<appleClass*> appleClassList;
	//The yellow banana is a fruit.
	vector<bananaClass*> banana1SubjectCategoryList;
	vector<bananaClass*> banana1CategoryList;
	for(vector<bananaClass*>::iterator iter1 = bananaClassList.begin(); iter1 < bananaClassList.end(); iter1++) 
	{
		bananaClass* banana1 = *iter1;
		for(vector<yellowClass*>::iterator iter2 = banana1->yellowClassPropertyList.begin(); iter2 < banana1->yellowClassPropertyList.end(); iter2++) 
		{
			yellowClass* yellow1 = *iter2;
			//Singular definite referencing tests
			addToCategoryIfPassSingularDefiniteReferencingTests<bananaClass, bananaClass> (banana1CategoryList, banana1);
		}
	}
	if(!(banana1CategoryList.empty()))
	{
		bananaClass* banana1 = banana1CategoryList.back();
		banana1->lastSentenceReferenced.top() = 1;
		addToCategoryIfPassPluralDefiniteReferencingTests<bananaClass, bananaClass> (banana1SubjectCategoryList, banana1);
	}
	for(vector<bananaClass*>::iterator iter1 = banana1SubjectCategoryList.begin(); iter1 < banana1SubjectCategoryList.end(); iter1++) 
	{
		bananaClass* banana1 = *iter1;
		if(checkParentClassName(static_cast<NLCgenericEntityClass*>(new fruitClass), "banana"))
		{
			fruitClass* fruit1 = static_cast<fruitClass*>(banana1);
			fruit1->name = "fruit";
			addEntityToLocalList<fruitClass>(&(fruitClassList), fruit1);
		}
	}
	//Apples are fruit.
	//An apple is on the green tree.
	vector<appleClass*> apple2SubjectCategoryList;
	vector<appleClass*> apple2CategoryList;
	appleClass* apple2 = addNewEntityToLocalList<appleClass>(&(appleClassList));
	apple2CategoryList.push_back(apple2);
	addEntityToReferenceContextList(referenceContextList0, apple2, 3);
	for(vector<appleClass*>::iterator iter1 = apple2CategoryList.begin(); iter1 < apple2CategoryList.end(); iter1++) 
	{
		appleClass* apple2 = *iter1;
		addToCategoryIfPassPluralDefiniteReferencingTests<appleClass, appleClass> (apple2SubjectCategoryList, apple2);
	}
	vector<treeClass*> tree1ObjectCategoryList;
	vector<treeClass*> tree1CategoryList;
	for(vector<treeClass*>::iterator iter1 = treeClassList.begin(); iter1 < treeClassList.end(); iter1++) 
	{
		treeClass* tree1 = *iter1;
		for(vector<greenClass*>::iterator iter2 = tree1->greenClassPropertyList.begin(); iter2 < tree1->greenClassPropertyList.end(); iter2++) 
		{
			greenClass* green1 = *iter2;
			//Singular definite referencing tests
			addToCategoryIfPassSingularDefiniteReferencingTests<treeClass, treeClass> (tree1CategoryList, tree1);
		}
	}
	if(!(tree1CategoryList.empty()))
	{
		treeClass* tree1 = tree1CategoryList.back();
		tree1->lastSentenceReferenced.top() = 3;
		addToCategoryIfPassPluralDefiniteReferencingTests<treeClass, treeClass> (tree1ObjectCategoryList, tree1);
	}
	for(vector<appleClass*>::iterator iter1 = apple2SubjectCategoryList.begin(); iter1 < apple2SubjectCategoryList.end(); iter1++) 
	{
		appleClass* apple2 = *iter1;
		for(vector<treeClass*>::iterator iter2 = tree1ObjectCategoryList.begin(); iter2 < tree1ObjectCategoryList.end(); iter2++) 
		{
			treeClass* tree1 = *iter2;
			addCondition<appleClass, onClass, treeClass>(apple2, &(apple2->onClasstreeClassConditionList), "on", tree1);
		}
	}
	clearReferenceContextList(referenceContextList0);
}
