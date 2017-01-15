#include "NLCgeneratedfunctionsWithNoSubjectArtificialClass.hpp"
#include "NLClibrary.hpp"

functionsWithNoSubjectArtificialClass::functionsWithNoSubjectArtificialClass(void)
{
	name = "functionsWithNoSubjectArtificial";
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

void functionsWithNoSubjectArtificialClass::NLCimplicitlyDeclaredFunction(vector<fileClass*>& fileClassList, vector<landClass*>& landClassList)
{
	vector<NLCgenericEntityClass*> referenceContextList0;
	//move the file to the land.
	vector<moveClass*> moveClassList;
	vector<moveClass*> move1CategoryList;
	moveClass* move1 = addNewEntityToLocalList<moveClass>(&(moveClassList));
	move1CategoryList.push_back(move1);
	addEntityToReferenceContextList(referenceContextList0, move1, 1);
	for(vector<moveClass*>::iterator iter1 = move1CategoryList.begin(); iter1 < move1CategoryList.end(); iter1++) 
	{
		moveClass* move1 = *iter1;
		vector<landClass*> land1CategoryList;
		for(vector<landClass*>::iterator iter2 = landClassList.begin(); iter2 < landClassList.end(); iter2++) 
		{
			landClass* land1 = *iter2;
			//Singular definite referencing tests
			addToCategoryIfPassSingularDefiniteReferencingTests<landClass, landClass> (land1CategoryList, land1);
		}
		if(!(land1CategoryList.empty()))
		{
			landClass* land1 = land1CategoryList.back();
			land1->lastSentenceReferenced.top() = 1;
			addCondition<moveClass, toClass, landClass>(move1, &(move1->toClasslandClassConditionList), "to", land1);
		}
	}
	vector<fileClass*> file1ObjectCategoryList;
	vector<fileClass*> file1CategoryList;
	for(vector<fileClass*>::iterator iter1 = fileClassList.begin(); iter1 < fileClassList.end(); iter1++) 
	{
		fileClass* file1 = *iter1;
		//Singular definite referencing tests
		addToCategoryIfPassSingularDefiniteReferencingTests<fileClass, fileClass> (file1CategoryList, file1);
	}
	if(!(file1CategoryList.empty()))
	{
		fileClass* file1 = file1CategoryList.back();
		file1->lastSentenceReferenced.top() = 1;
		addToCategoryIfPassPluralDefiniteReferencingTests<fileClass, fileClass> (file1ObjectCategoryList, file1);
	}
	for(vector<fileClass*>::iterator iter1 = file1ObjectCategoryList.begin(); iter1 < file1ObjectCategoryList.end(); iter1++) 
	{
		fileClass* file1 = *iter1;
		addActionObject<moveClass, fileClass>(move1, file1, &(file1->moveClassActionIncomingList), &(move1->fileClassActionObjectList));
	}
	moveFunction(castVector<moveClass, NLCgenericEntityClass>(moveClassList), castVector<fileClass, NLCgenericEntityClass>(file1ObjectCategoryList));
	clearReferenceContextList(referenceContextList0);
}
