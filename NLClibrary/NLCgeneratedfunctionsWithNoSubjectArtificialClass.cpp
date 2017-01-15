#include "NLCgeneratedfunctionsWithNoSubjectArtificialClass.hpp"
#include "NLClibrary.hpp"

functionsWithNoSubjectArtificialClass::functionsWithNoSubjectArtificialClass(void)
{
	name = "functionsWithNoSubjectArtificial";
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

void functionsWithNoSubjectArtificialClass::NLCimplicitlyDeclaredFunctionArtificialFunction(vector<NLCimplicitlyDeclaredFunctionArtificialClass*>& NLCimplicitlyDeclaredFunctionArtificialClassList, vector<dogClass*>& dogClassList, vector<birdClass*>& birdClassList, vector<mountainClass*>& mountainClassList, vector<elephantClass*>& elephantClassList, vector<boneClass*>& boneClassList)
{
	vector<NLCgenericEntityClass*> referenceContextList0;
	//X = Y * (the number of red dogs) + the number of blue birds near the mountain
	int thenumberofreddogs1 = 0;
	vector<dogClass*> dog1CategoryList;
	for(vector<dogClass*>::iterator iter1 = dogClassList.begin(); iter1 < dogClassList.end(); iter1++) 
	{
		dogClass* dog1 = *iter1;
		for(vector<redClass*>::iterator iter2 = dog1->redClassPropertyList.begin(); iter2 < dog1->redClassPropertyList.end(); iter2++) 
		{
			redClass* red1 = *iter2;
			//Plural definite referencing tests
			addToCategoryIfPassPluralDefiniteReferencingTests<dogClass, dogClass> (dog1CategoryList, dog1);
		}
	}
	for(vector<dogClass*>::iterator iter1 = dog1CategoryList.begin(); iter1 < dog1CategoryList.end(); iter1++) 
	{
		dogClass* dog1 = *iter1;
		dog1->lastSentenceReferenced.top() = 1;
		thenumberofreddogs1 = thenumberofreddogs1 + 1;
	}
	int thenumberofbluebirdsnearthemountain1 = 0;
	vector<birdClass*> bird1CategoryList;
	for(vector<birdClass*>::iterator iter1 = birdClassList.begin(); iter1 < birdClassList.end(); iter1++) 
	{
		birdClass* bird1 = *iter1;
		for(vector<blueClass*>::iterator iter2 = bird1->blueClassPropertyList.begin(); iter2 < bird1->blueClassPropertyList.end(); iter2++) 
		{
			blueClass* blue1 = *iter2;
			for(unordered_map<nearClass*, mountainClass*>::iterator iter3 = bird1->nearClassmountainClassConditionList.begin(); iter3 != bird1->nearClassmountainClassConditionList.end(); iter3++) 
			{
				mountainClass* mountain1 = iter3->second;
				mountainClass* mountainCandidate = mountain1;
				vector<mountainClass*> mountain1CategoryList;
				for(vector<mountainClass*>::iterator iter4 = mountainClassList.begin(); iter4 < mountainClassList.end(); iter4++) 
				{
					mountainClass* mountain1 = *iter4;
					//Singular definite referencing tests
					addToCategoryIfPassSingularDefiniteReferencingTests<mountainClass, mountainClass> (mountain1CategoryList, mountain1);
				}
				if(!(mountain1CategoryList.empty()))
				{
					mountainClass* mountain1 = mountain1CategoryList.back();
					mountain1->lastSentenceReferenced.top() = 2;
					if(mountainCandidate == mountain1)
					{
						//Plural definite referencing tests
						addToCategoryIfPassPluralDefiniteReferencingTests<birdClass, birdClass> (bird1CategoryList, bird1);
					}
				}
			}
		}
	}
	for(vector<birdClass*>::iterator iter1 = bird1CategoryList.begin(); iter1 < bird1CategoryList.end(); iter1++) 
	{
		birdClass* bird1 = *iter1;
		bird1->lastSentenceReferenced.top() = 2;
		thenumberofbluebirdsnearthemountain1 = thenumberofbluebirdsnearthemountain1 + 1;
	}
	double X = Y * (thenumberofreddogs1) + thenumberofbluebirdsnearthemountain1;
	//Z = q234 / (the number of blue elephants)
	int thenumberofblueelephants3 = 0;
	vector<elephantClass*> elephant1CategoryList;
	for(vector<elephantClass*>::iterator iter1 = elephantClassList.begin(); iter1 < elephantClassList.end(); iter1++) 
	{
		elephantClass* elephant1 = *iter1;
		for(vector<blueClass*>::iterator iter2 = elephant1->blueClassPropertyList.begin(); iter2 < elephant1->blueClassPropertyList.end(); iter2++) 
		{
			blueClass* blue2 = *iter2;
			//Plural definite referencing tests
			addToCategoryIfPassPluralDefiniteReferencingTests<elephantClass, elephantClass> (elephant1CategoryList, elephant1);
		}
	}
	for(vector<elephantClass*>::iterator iter1 = elephant1CategoryList.begin(); iter1 < elephant1CategoryList.end(); iter1++) 
	{
		elephantClass* elephant1 = *iter1;
		elephant1->lastSentenceReferenced.top() = 3;
		thenumberofblueelephants3 = thenumberofblueelephants3 + 1;
	}
	double Z = q234 / (thenumberofblueelephants3);
	//X dogs have the bone.
	vector<dogClass*> dog2SubjectCategoryList;
	vector<dogClass*> dog2CategoryList;
	for(int index1 = 0; index1 < X; index1++) 
	{
		dogClass* dog2 = addNewEntityToLocalList<dogClass>(&(dogClassList));
		dog2CategoryList.push_back(dog2);
		addEntityToReferenceContextList(referenceContextList0, dog2, 4);
	}
	for(vector<dogClass*>::iterator iter1 = dog2CategoryList.begin(); iter1 < dog2CategoryList.end(); iter1++) 
	{
		dogClass* dog2 = *iter1;
		addToCategoryIfPassPluralDefiniteReferencingTests<dogClass, dogClass> (dog2SubjectCategoryList, dog2);
	}
	vector<boneClass*> bone1ObjectCategoryList;
	vector<boneClass*> bone1CategoryList;
	for(vector<boneClass*>::iterator iter1 = boneClassList.begin(); iter1 < boneClassList.end(); iter1++) 
	{
		boneClass* bone1 = *iter1;
		//Singular definite referencing tests
		addToCategoryIfPassSingularDefiniteReferencingTests<boneClass, boneClass> (bone1CategoryList, bone1);
	}
	if(!(bone1CategoryList.empty()))
	{
		boneClass* bone1 = bone1CategoryList.back();
		bone1->lastSentenceReferenced.top() = 4;
		addToCategoryIfPassPluralDefiniteReferencingTests<boneClass, boneClass> (bone1ObjectCategoryList, bone1);
	}
	for(vector<dogClass*>::iterator iter1 = dog2SubjectCategoryList.begin(); iter1 < dog2SubjectCategoryList.end(); iter1++) 
	{
		dogClass* dog2 = *iter1;
		for(vector<boneClass*>::iterator iter2 = bone1ObjectCategoryList.begin(); iter2 < bone1ObjectCategoryList.end(); iter2++) 
		{
			boneClass* bone1 = *iter2;
			addProperty<dogClass, boneClass>(dog2, &(dog2->boneClassPropertyList), bone1);
		}
	}
	clearReferenceContextList(referenceContextList0);
}

int main()
{
	vector<NLCimplicitlyDeclaredFunctionArtificialClass*> NLCimplicitlyDeclaredFunctionArtificialClassList;
	vector<dogClass*> dogClassList;
	vector<birdClass*> birdClassList;
	vector<mountainClass*> mountainClassList;
	vector<elephantClass*> elephantClassList;
	vector<boneClass*> boneClassList;
	(new functionsWithNoSubjectArtificialClass)->NLCimplicitlyDeclaredFunctionArtificialFunction(NLCimplicitlyDeclaredFunctionArtificialClassList, dogClassList, birdClassList, mountainClassList, elephantClassList, boneClassList);
}
