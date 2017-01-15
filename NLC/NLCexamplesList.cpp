NLC execution time: 10:56:16 08/11/2014 (start)
parse error; lower level sectionTagName expected = coreference. section tag name found currentTag->name = 
code = 
#include <string>
#include <vector>
#include <stack>
#include <unordered_map>
#include <utility>
#include <algorithm>
#include <iostream>
using namespace std;



class NLCgenericEntityClass
{
public:
	NLCgenericEntityClass(void);
	string name;
	stack<int> lastSentenceReferenced;
	vector<string> aliasList;
};

NLCgenericEntityClass::NLCgenericEntityClass(void)
{
	name = "NLCgenericEntity";
};

class objectClass : public NLCgenericEntityClass
{
public:
	objectClass(void);
	vector<eatClass*> eatClassActionIncomingList;
};

objectClass::objectClass(void)
{
	name = "object";
};

class eatClass : public NLCgenericEntityClass
{
public:
	eatClass(void);
	vector<animalClass*> animalClassActionSubjectList;
	vector<dogClass*> dogClassActionSubjectList;
	vector<objectClass*> objectClassActionObjectList;
	vector<ballClass*> ballClassActionObjectList;
};

eatClass::eatClass(void)
{
	name = "eat";
};

class happyClass : public NLCgenericEntityClass
{
public:
	happyClass(void);
};

happyClass::happyClass(void)
{
	name = "happy";
};

class ballClass : public objectClass
{
public:
	ballClass(void);
	vector<happyClass*> happyClassPropertyList;
	vector<eatClass*> eatClassActionIncomingList;
};

ballClass::ballClass(void)
{
	name = "ball";
};

class animalClass : public NLCgenericEntityClass
{
public:
	animalClass(void);
	void eatFunction(vector<eatClass*> &eatClassList, vector<objectClass*> &objectClassList);
	void eatFunction(vector<eatClass*> &eatClassList, vector<ballClass*> &ballClassList);
	vector<eatClass*> eatClassActionList;
};

animalClass::animalClass(void)
{
	name = "animal";
};

class dogClass : public animalClass
{
public:
	dogClass(void);
	void rideFunction(vector<rideClass*> &rideClassList, vector<bikeClass*> &bikeClassList, vector<ballClass*> &ballClassList);
	void eatFunction(vector<eatClass*> &eatClassList, vector<objectClass*> &objectClassList);
	void eatFunction(vector<eatClass*> &eatClassList, vector<ballClass*> &ballClassList);
	vector<eatClass*> eatClassActionList;
};

dogClass::dogClass(void)
{
	name = "dog";
};

class functionsWithNoSubjectArtificialClass : public NLCgenericEntityClass
{
public:
	functionsWithNoSubjectArtificialClass(void);
	void mainFunction(vector<mainClass*> &mainClassList, vector<animalClass*> &animalClassList, vector<objectClass*> &objectClassList, vector<dogClass*> &dogClassList, vector<ballClass*> &ballClassList);
};

functionsWithNoSubjectArtificialClass::functionsWithNoSubjectArtificialClass(void)
{
	name = "functionsWithNoSubjectArtificial";
};

void mainFunction(vector<mainClass*> &mainClassList, vector<animalClass*> &animalClassList, vector<objectClass*> &objectClassList, vector<dogClass*> &dogClassList, vector<ballClass*> &ballClassList)
{
	vector<eatClass*> eatClassList;
	vector<eatClass*> eat1CategoryList;
	eatClass* eat1 = new eatClass();
	eatClassList.push_back(eat1);
	eat1CategoryList.push_back(eat1);
	addEntityToReferenceContextList(referenceContextList0, eat1, 3);
	vector<objectClass*> object2CategoryList;
	for(vector<objectClass*> ::iterator iter1 = objectClassList.begin(); iter1 < objectClassList.end(); iter1++) 
	{
		objectClass* object2 = *iter1;
		//Singular definite referencing tests
		addToCategoryIfPassSingularDefiniteReferencingTests<objectClass, objectClass> (object2CategoryList, object2);
	}
	for(vector<ballClass*> ::iterator iter1 = ballClassList.begin(); iter1 < ballClassList.end(); iter1++) 
	{
		ballClass* ball2 = *iter1;
		//Singular definite referencing tests
		addToCategoryIfPassSingularDefiniteReferencingTests<objectClass, ballClass> (object2CategoryList, ball2);
	}
	for(vector<ballClass*> ::iterator iter1 = ballClassList.begin(); iter1 < ballClassList.end(); iter1++) 
	{
		ballClass* ball3 = *iter1;
		//Singular definite referencing tests
		addToCategoryIfPassSingularDefiniteReferencingTests<objectClass, ballClass> (object2CategoryList, ball3);
	}
	for(vector<objectClass*> ::iterator iter1 = objectClassList.begin(); iter1 < objectClassList.end(); iter1++) 
	{
		objectClass* object3 = *iter1;
		//Singular definite referencing tests
		addToCategoryIfPassSingularDefiniteReferencingTests<objectClass, objectClass> (object2CategoryList, object3);
	}
	if(!(object2CategoryList.empty()))
	{
		objectClass* object2 = object2CategoryList.back();
		object2->lastSentenceReferenced.top() = 3;
		object2->eatClassActionIncomingList.push_back(eat1);
		eat1->objectClassActionObjectList.push_back(object2);
		vector<animalClass*> animal2CategoryList;
		for(vector<animalClass*> ::iterator iter2 = animalClassList.begin(); iter2 < animalClassList.end(); iter2++) 
		{
			animalClass* animal2 = *iter2;
			//Singular definite referencing tests
			addToCategoryIfPassSingularDefiniteReferencingTests<animalClass, animalClass> (animal2CategoryList, animal2);
		}
		for(vector<dogClass*> ::iterator iter2 = dogClassList.begin(); iter2 < dogClassList.end(); iter2++) 
		{
			dogClass* dog2 = *iter2;
			//Singular definite referencing tests
			addToCategoryIfPassSingularDefiniteReferencingTests<animalClass, dogClass> (animal2CategoryList, dog2);
		}
		for(vector<dogClass*> ::iterator iter2 = dogClassList.begin(); iter2 < dogClassList.end(); iter2++) 
		{
			dogClass* dog3 = *iter2;
			//Singular definite referencing tests
			addToCategoryIfPassSingularDefiniteReferencingTests<animalClass, dogClass> (animal2CategoryList, dog3);
		}
		for(vector<animalClass*> ::iterator iter2 = animalClassList.begin(); iter2 < animalClassList.end(); iter2++) 
		{
			animalClass* animal3 = *iter2;
			//Singular definite referencing tests
			addToCategoryIfPassSingularDefiniteReferencingTests<animalClass, animalClass> (animal2CategoryList, animal3);
		}
		if(!(animal2CategoryList.empty()))
		{
			animalClass* animal2 = animal2CategoryList.back();
			animal2->lastSentenceReferenced.top() = 3;
			animal2->eatClassActionList.push_back(eat1);
			eat1->animalClassActionSubjectList.push_back(animal2);
			animal2->eatFunction(eatClassList, objectClassList);
		}
	}
	vector<eatClass*> eat2CategoryList;
	eatClass* eat2 = new eatClass();
	eatClassList.push_back(eat2);
	eat2CategoryList.push_back(eat2);
	addEntityToReferenceContextList(referenceContextList0, eat2, 4);
	vector<objectClass*> object3CategoryList;
	for(vector<objectClass*> ::iterator iter1 = objectClassList.begin(); iter1 < objectClassList.end(); iter1++) 
	{
		objectClass* object3 = *iter1;
		//Singular definite referencing tests
		addToCategoryIfPassSingularDefiniteReferencingTests<objectClass, objectClass> (object3CategoryList, object3);
	}
	for(vector<ballClass*> ::iterator iter1 = ballClassList.begin(); iter1 < ballClassList.end(); iter1++) 
	{
		ballClass* ball2 = *iter1;
		//Singular definite referencing tests
		addToCategoryIfPassSingularDefiniteReferencingTests<objectClass, ballClass> (object3CategoryList, ball2);
	}
	for(vector<ballClass*> ::iterator iter1 = ballClassList.begin(); iter1 < ballClassList.end(); iter1++) 
	{
		ballClass* ball3 = *iter1;
		//Singular definite referencing tests
		addToCategoryIfPassSingularDefiniteReferencingTests<objectClass, ballClass> (object3CategoryList, ball3);
	}
	for(vector<objectClass*> ::iterator iter1 = objectClassList.begin(); iter1 < objectClassList.end(); iter1++) 
	{
		objectClass* object2 = *iter1;
		//Singular definite referencing tests
		addToCategoryIfPassSingularDefiniteReferencingTests<objectClass, objectClass> (object3CategoryList, object2);
	}
	if(!(object3CategoryList.empty()))
	{
		objectClass* object3 = object3CategoryList.back();
		object3->lastSentenceReferenced.top() = 4;
		object3->eatClassActionIncomingList.push_back(eat2);
		eat2->objectClassActionObjectList.push_back(object3);
		vector<dogClass*> dog2CategoryList;
		for(vector<dogClass*> ::iterator iter2 = dogClassList.begin(); iter2 < dogClassList.end(); iter2++) 
		{
			dogClass* dog2 = *iter2;
			//Singular definite referencing tests
			addToCategoryIfPassSingularDefiniteReferencingTests<dogClass, dogClass> (dog2CategoryList, dog2);
		}
		for(vector<dogClass*> ::iterator iter2 = dogClassList.begin(); iter2 < dogClassList.end(); iter2++) 
		{
			dogClass* dog3 = *iter2;
			//Singular definite referencing tests
			addToCategoryIfPassSingularDefiniteReferencingTests<dogClass, dogClass> (dog2CategoryList, dog3);
		}
		if(!(dog2CategoryList.empty()))
		{
			dogClass* dog2 = dog2CategoryList.back();
			dog2->lastSentenceReferenced.top() = 4;
			dog2->eatClassActionList.push_back(eat2);
			eat2->dogClassActionSubjectList.push_back(dog2);
			dog2->eatFunction(eatClassList, objectClassList);
		}
	}
	vector<eatClass*> eat3CategoryList;
	eatClass* eat3 = new eatClass();
	eatClassList.push_back(eat3);
	eat3CategoryList.push_back(eat3);
	addEntityToReferenceContextList(referenceContextList0, eat3, 5);
	vector<ballClass*> ball2CategoryList;
	for(vector<ballClass*> ::iterator iter1 = ballClassList.begin(); iter1 < ballClassList.end(); iter1++) 
	{
		ballClass* ball2 = *iter1;
		//Singular definite referencing tests
		addToCategoryIfPassSingularDefiniteReferencingTests<ballClass, ballClass> (ball2CategoryList, ball2);
	}
	for(vector<ballClass*> ::iterator iter1 = ballClassList.begin(); iter1 < ballClassList.end(); iter1++) 
	{
		ballClass* ball3 = *iter1;
		//Singular definite referencing tests
		addToCategoryIfPassSingularDefiniteReferencingTests<ballClass, ballClass> (ball2CategoryList, ball3);
	}
	if(!(ball2CategoryList.empty()))
	{
		ballClass* ball2 = ball2CategoryList.back();
		ball2->lastSentenceReferenced.top() = 5;
		ball2->eatClassActionIncomingList.push_back(eat3);
		eat3->ballClassActionObjectList.push_back(ball2);
		vector<animalClass*> animal3CategoryList;
		for(vector<animalClass*> ::iterator iter2 = animalClassList.begin(); iter2 < animalClassList.end(); iter2++) 
		{
			animalClass* animal3 = *iter2;
			//Singular definite referencing tests
			addToCategoryIfPassSingularDefiniteReferencingTests<animalClass, animalClass> (animal3CategoryList, animal3);
		}
		for(vector<dogClass*> ::iterator iter2 = dogClassList.begin(); iter2 < dogClassList.end(); iter2++) 
		{
			dogClass* dog2 = *iter2;
			//Singular definite referencing tests
			addToCategoryIfPassSingularDefiniteReferencingTests<animalClass, dogClass> (animal3CategoryList, dog2);
		}
		for(vector<dogClass*> ::iterator iter2 = dogClassList.begin(); iter2 < dogClassList.end(); iter2++) 
		{
			dogClass* dog3 = *iter2;
			//Singular definite referencing tests
			addToCategoryIfPassSingularDefiniteReferencingTests<animalClass, dogClass> (animal3CategoryList, dog3);
		}
		for(vector<animalClass*> ::iterator iter2 = animalClassList.begin(); iter2 < animalClassList.end(); iter2++) 
		{
			animalClass* animal2 = *iter2;
			//Singular definite referencing tests
			addToCategoryIfPassSingularDefiniteReferencingTests<animalClass, animalClass> (animal3CategoryList, animal2);
		}
		if(!(animal3CategoryList.empty()))
		{
			animalClass* animal3 = animal3CategoryList.back();
			animal3->lastSentenceReferenced.top() = 5;
			animal3->eatClassActionList.push_back(eat3);
			eat3->animalClassActionSubjectList.push_back(animal3);
			animal3->eatFunction(eatClassList, ballClassList);
		}
	}
	vector<eatClass*> eat4CategoryList;
	eatClass* eat4 = new eatClass();
	eatClassList.push_back(eat4);
	eat4CategoryList.push_back(eat4);
	addEntityToReferenceContextList(referenceContextList0, eat4, 6);
	vector<ballClass*> ball3CategoryList;
	for(vector<ballClass*> ::iterator iter1 = ballClassList.begin(); iter1 < ballClassList.end(); iter1++) 
	{
		ballClass* ball3 = *iter1;
		//Singular definite referencing tests
		addToCategoryIfPassSingularDefiniteReferencingTests<ballClass, ballClass> (ball3CategoryList, ball3);
	}
	for(vector<ballClass*> ::iterator iter1 = ballClassList.begin(); iter1 < ballClassList.end(); iter1++) 
	{
		ballClass* ball2 = *iter1;
		//Singular definite referencing tests
		addToCategoryIfPassSingularDefiniteReferencingTests<ballClass, ballClass> (ball3CategoryList, ball2);
	}
	if(!(ball3CategoryList.empty()))
	{
		ballClass* ball3 = ball3CategoryList.back();
		ball3->lastSentenceReferenced.top() = 6;
		ball3->eatClassActionIncomingList.push_back(eat4);
		eat4->ballClassActionObjectList.push_back(ball3);
		vector<dogClass*> dog3CategoryList;
		for(vector<dogClass*> ::iterator iter2 = dogClassList.begin(); iter2 < dogClassList.end(); iter2++) 
		{
			dogClass* dog3 = *iter2;
			//Singular definite referencing tests
			addToCategoryIfPassSingularDefiniteReferencingTests<dogClass, dogClass> (dog3CategoryList, dog3);
		}
		for(vector<dogClass*> ::iterator iter2 = dogClassList.begin(); iter2 < dogClassList.end(); iter2++) 
		{
			dogClass* dog2 = *iter2;
			//Singular definite referencing tests
			addToCategoryIfPassSingularDefiniteReferencingTests<dogClass, dogClass> (dog3CategoryList, dog2);
		}
		if(!(dog3CategoryList.empty()))
		{
			dogClass* dog3 = dog3CategoryList.back();
			dog3->lastSentenceReferenced.top() = 6;
			dog3->eatClassActionList.push_back(eat4);
			eat4->dogClassActionSubjectList.push_back(dog3);
			dog3->eatFunction(eatClassList, ballClassList);
		}
	}
}
void dogClass::rideFunction(vector<rideClass*> &rideClassList, vector<bikeClass*> &bikeClassList, vector<ballClass*> &ballClassList)
{
	vector<ballClass*> ball1CategoryList;
	for(vector<ballClass*> ::iterator iter1 = ballClassList.begin(); iter1 < ballClassList.end(); iter1++) 
	{
		ballClass* ball1 = *iter1;
		//Singular definite referencing tests
		addToCategoryIfPassSingularDefiniteReferencingTests<ballClass, ballClass> (ball1CategoryList, ball1);
	}
	if(!(ball1CategoryList.empty()))
	{
		ballClass* ball1 = ball1CategoryList.back();
		ball1->lastSentenceReferenced.top() = 1;
		vector<happyClass*> happy1CategoryList;
		happyClass* happy1 = new happyClass();
		ball1->happyClassPropertyList.push_back(happy1);
		happy1CategoryList.push_back(happy1);
		addEntityToReferenceContextList(referenceContextList0, happy1, 1);
	}
}

template <class E1, class E2>
void addToCategoryIfPassPluralDefiniteReferencingTests(vector<E1*> &entityCategoryList, E2* entity0)
{
	if(!(find(entityCategoryList.begin(), entityCategoryList.end(), entity0) != entityCategoryList.end()))
	{
		entityCategoryList.push_back(entity0);
	}
}

template <class E1, class E2>
void addToCategoryIfPassSingularDefiniteReferencingTests(vector<E1*> &entityCategoryList, E2* entity0)
{
	if(!(entity0->lastSentenceReferenced.empty()))
	{
		if(entityCategoryList.empty())
		{
			entityCategoryList.push_back(entity0);
		}
		else
		{
			if(entity0->lastSentenceReferenced.top() > (entityCategoryList.back())->lastSentenceReferenced.top())
			{
				entityCategoryList.clear();
				entityCategoryList.push_back(entity0);
			}
			else if(entity0->lastSentenceReferenced.top() == (entityCategoryList.back())->lastSentenceReferenced.top())
			{
				if(!(find(entityCategoryList.begin(), entityCategoryList.end(), entity0) != entityCategoryList.end()))
				{
					entityCategoryList.push_back(entity0);
				}
			}
			else
			{
			}
		}
	}
	//Singular definite plurality tests
	if(entityCategoryList.size() > 1)
	{
		cout << "Execution warning: multiple objects have been added to a singular definite variable (category) - should the entity have been defined as plural instead?" << endl;
	}
}

void addEntityToReferenceContextList(vector<NLCgenericEntityClass*> &referenceContextList, NLCgenericEntityClass* NLCgenericEntity, int sentenceIndex)
{
	referenceContextList.push_back(NLCgenericEntity);
	NLCgenericEntity->lastSentenceReferenced.push(sentenceIndex);
}

void clearReferenceContextList(vector<NLCgenericEntityClass*> &referenceContextList)
{
	for(vector<NLCgenericEntityClass*> ::iterator iter1 = referenceContextList.begin(); iter1 < referenceContextList.end(); iter1++) 
	{
		NLCgenericEntityClass* NLCgenericEntity = *iter1;
		NLCgenericEntity->lastSentenceReferenced.pop();
	}
	referenceContextList.clear();
}

template <class E1, class E2>
vector<E1*> castVector(vector<E1*> &E1List)
{
	vector<E2*> E2List;
	for(typename vector<E1*> ::iterator iter1 = E1List.begin(); iter1 < E1List.end(); iter1++) 
	{
		E1* NLCgenericEntity = *iter1;
		E2List.push_back(dynamic_cast<E2*>(NLCgenericEntity));
	}
	return E2List;
}

template <class E1>
void findAliasAndAddToCategoryList(vector<E1*> &E1List, string aliasName, vector<E1*> &E1CategoryList)
{
	for(typename vector<E1*> ::iterator iter1 = E1List.begin(); iter1 < E1List.end(); iter1++) 
	{
		E1* NLCgenericEntity = *iter1;
		if((find(NLCgenericEntity->aliasList.begin(), NLCgenericEntity->aliasList.end(), aliasName) != NLCgenericEntity->aliasList.end()))
		{
			E1CategoryList.push_back(NLCgenericEntity);
		}
	}
}

NLC execution time: 10:59:7 08/11/2014 (finish)
