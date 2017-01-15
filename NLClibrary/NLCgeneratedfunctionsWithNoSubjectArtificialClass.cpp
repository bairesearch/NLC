#include "NLCgeneratedfunctionsWithNoSubjectArtificialClass.hpp"
#include "NLClibrary.hpp"

functionsWithNoSubjectArtificialClass::functionsWithNoSubjectArtificialClass(void)
{
	name = "functionsWithNoSubjectArtificial";
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

void functionsWithNoSubjectArtificialClass::NLCimplicitlyDeclaredFunctionArtificialFunction(vector<NLCimplicitlyDeclaredFunctionArtificialClass*>& NLCimplicitlyDeclaredFunctionArtificialClassList, vector<tableClass*>& tableClassList, vector<treeClass*>& treeClassList, vector<fruitClass*>& fruitClassList)
{
	vector<NLCgenericEntityClass*> referenceContextList0;
	vector<bananaClass*> bananaClassList;
	vector<appleClass*> appleClassList;
	//A yellow banana is on the table.
	vector<bananaClass*> banana1SubjectCategoryList;
	vector<bananaClass*> banana1CategoryList;
	bananaClass* banana1 = addNewEntityToLocalList<bananaClass>(&(bananaClassList));
	banana1CategoryList.push_back(banana1);
	addEntityToReferenceContextList(referenceContextList0, banana1, 1);
	for(vector<bananaClass*>::iterator iter1 = banana1CategoryList.begin(); iter1 < banana1CategoryList.end(); iter1++) 
	{
		bananaClass* banana1 = *iter1;
		vector<yellowClass*> yellowClassList;
		vector<yellowClass*> yellow1CategoryList;
		yellowClass* yellow1 = addNewEntityToLocalList<yellowClass>(&(yellowClassList));
		yellow1CategoryList.push_back(yellow1);
		addEntityToReferenceContextList(referenceContextList0, yellow1, 1);
		for(vector<yellowClass*>::iterator iter2 = yellow1CategoryList.begin(); iter2 < yellow1CategoryList.end(); iter2++) 
		{
			yellowClass* yellow1 = *iter2;
			addProperty<bananaClass, yellowClass>(banana1, &(banana1->yellowClassPropertyList), yellow1);
		}
	}
	for(vector<bananaClass*>::iterator iter1 = banana1CategoryList.begin(); iter1 < banana1CategoryList.end(); iter1++) 
	{
		bananaClass* banana1 = *iter1;
		addToCategoryIfPassPluralDefiniteReferencingTests<bananaClass, bananaClass> (banana1SubjectCategoryList, banana1);
	}
	vector<tableClass*> table1ObjectCategoryList;
	vector<tableClass*> table1CategoryList;
	for(vector<tableClass*>::iterator iter1 = tableClassList.begin(); iter1 < tableClassList.end(); iter1++) 
	{
		tableClass* table1 = *iter1;
		//Singular definite referencing tests
		addToCategoryIfPassSingularDefiniteReferencingTests<tableClass, tableClass> (table1CategoryList, table1);
	}
	if(!(table1CategoryList.empty()))
	{
		tableClass* table1 = table1CategoryList.back();
		table1->lastSentenceReferenced.top() = 1;
		addToCategoryIfPassPluralDefiniteReferencingTests<tableClass, tableClass> (table1ObjectCategoryList, table1);
	}
	for(vector<bananaClass*>::iterator iter1 = banana1SubjectCategoryList.begin(); iter1 < banana1SubjectCategoryList.end(); iter1++) 
	{
		bananaClass* banana1 = *iter1;
		for(vector<tableClass*>::iterator iter2 = table1ObjectCategoryList.begin(); iter2 < table1ObjectCategoryList.end(); iter2++) 
		{
			tableClass* table1 = *iter2;
			addCondition<bananaClass, onClass, tableClass>(banana1, &(banana1->onClasstableClassConditionList), "on", table1);
		}
	}
	//The yellow banana is a fruit.
	vector<bananaClass*> banana2SubjectCategoryList;
	vector<bananaClass*> banana2CategoryList;
	for(vector<bananaClass*>::iterator iter1 = bananaClassList.begin(); iter1 < bananaClassList.end(); iter1++) 
	{
		bananaClass* banana2 = *iter1;
		for(vector<yellowClass*>::iterator iter2 = banana2->yellowClassPropertyList.begin(); iter2 < banana2->yellowClassPropertyList.end(); iter2++) 
		{
			yellowClass* yellow2 = *iter2;
			//Singular definite referencing tests
			addToCategoryIfPassSingularDefiniteReferencingTests<bananaClass, bananaClass> (banana2CategoryList, banana2);
		}
	}
	if(!(banana2CategoryList.empty()))
	{
		bananaClass* banana2 = banana2CategoryList.back();
		banana2->lastSentenceReferenced.top() = 2;
		addToCategoryIfPassPluralDefiniteReferencingTests<bananaClass, bananaClass> (banana2SubjectCategoryList, banana2);
	}
	for(vector<bananaClass*>::iterator iter1 = banana2SubjectCategoryList.begin(); iter1 < banana2SubjectCategoryList.end(); iter1++) 
	{
		bananaClass* banana2 = *iter1;
		if(checkParentClassName(static_cast<NLCgenericEntityClass*>(new fruitClass), "banana"))
		{
			fruitClass* fruit1 = dynamic_cast<fruitClass*>(banana2);
			fruit1->name = "fruit";
		}
	}
	//Apples are fruit.
	//An apple is on the green tree.
	vector<appleClass*> apple2SubjectCategoryList;
	vector<appleClass*> apple2CategoryList;
	appleClass* apple2 = addNewEntityToLocalList<appleClass>(&(appleClassList));
	apple2CategoryList.push_back(apple2);
	addEntityToReferenceContextList(referenceContextList0, apple2, 4);
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
		tree1->lastSentenceReferenced.top() = 4;
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
	//The yellow fruit is tasty.
	vector<fruitClass*> fruit2SubjectCategoryList;
	vector<fruitClass*> fruit2CategoryList;
	for(vector<fruitClass*>::iterator iter1 = fruitClassList.begin(); iter1 < fruitClassList.end(); iter1++) 
	{
		fruitClass* fruit2 = *iter1;
		for(vector<yellowClass*>::iterator iter2 = fruit2->yellowClassPropertyList.begin(); iter2 < fruit2->yellowClassPropertyList.end(); iter2++) 
		{
			yellowClass* yellow3 = *iter2;
			//Singular definite referencing tests
			addToCategoryIfPassSingularDefiniteReferencingTests<fruitClass, fruitClass> (fruit2CategoryList, fruit2);
		}
	}
	for(vector<bananaClass*>::iterator iter1 = bananaClassList.begin(); iter1 < bananaClassList.end(); iter1++) 
	{
		bananaClass* banana2 = *iter1;
		for(vector<yellowClass*>::iterator iter2 = banana2->yellowClassPropertyList.begin(); iter2 < banana2->yellowClassPropertyList.end(); iter2++) 
		{
			yellowClass* yellow3 = *iter2;
			//Singular definite referencing tests
			addToCategoryIfPassSingularDefiniteReferencingTests<fruitClass, bananaClass> (fruit2CategoryList, banana2);
		}
	}
	for(vector<appleClass*>::iterator iter1 = appleClassList.begin(); iter1 < appleClassList.end(); iter1++) 
	{
		appleClass* apple2 = *iter1;
		for(vector<yellowClass*>::iterator iter2 = apple2->yellowClassPropertyList.begin(); iter2 < apple2->yellowClassPropertyList.end(); iter2++) 
		{
			yellowClass* yellow3 = *iter2;
			//Singular definite referencing tests
			addToCategoryIfPassSingularDefiniteReferencingTests<fruitClass, appleClass> (fruit2CategoryList, apple2);
		}
	}
	if(!(fruit2CategoryList.empty()))
	{
		fruitClass* fruit2 = fruit2CategoryList.back();
		fruit2->lastSentenceReferenced.top() = 5;
		addToCategoryIfPassPluralDefiniteReferencingTests<fruitClass, fruitClass> (fruit2SubjectCategoryList, fruit2);
	}
	vector<tastyClass*> tasty1ObjectCategoryList;
	vector<tastyClass*> tastyClassList;
	vector<tastyClass*> tasty1CategoryList;
	tastyClass* tasty1 = addNewEntityToLocalList<tastyClass>(&(tastyClassList));
	tasty1CategoryList.push_back(tasty1);
	addEntityToReferenceContextList(referenceContextList0, tasty1, 5);
	for(vector<tastyClass*>::iterator iter1 = tasty1CategoryList.begin(); iter1 < tasty1CategoryList.end(); iter1++) 
	{
		tastyClass* tasty1 = *iter1;
		addToCategoryIfPassPluralDefiniteReferencingTests<tastyClass, tastyClass> (tasty1ObjectCategoryList, tasty1);
	}
	for(vector<fruitClass*>::iterator iter1 = fruit2SubjectCategoryList.begin(); iter1 < fruit2SubjectCategoryList.end(); iter1++) 
	{
		fruitClass* fruit2 = *iter1;
		for(vector<tastyClass*>::iterator iter2 = tasty1ObjectCategoryList.begin(); iter2 < tasty1ObjectCategoryList.end(); iter2++) 
		{
			tastyClass* tasty1 = *iter2;
			addProperty<fruitClass, tastyClass>(fruit2, &(fruit2->tastyClassPropertyList), tasty1);
		}
	}
	clearReferenceContextList(referenceContextList0);
}

int main()
{
	vector<NLCimplicitlyDeclaredFunctionArtificialClass*> NLCimplicitlyDeclaredFunctionArtificialClassList;
	vector<tableClass*> tableClassList;
	vector<treeClass*> treeClassList;
	vector<fruitClass*> fruitClassList;
	(new functionsWithNoSubjectArtificialClass)->NLCimplicitlyDeclaredFunctionArtificialFunction(NLCimplicitlyDeclaredFunctionArtificialClassList, tableClassList, treeClassList, fruitClassList);
}
