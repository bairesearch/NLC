NLC execution time: 14:5:30 02/12/2014 (start)
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

class animalClass : public NLCgenericEntityClass
{
public:
	animalClass(void);
};

animalClass::animalClass(void)
{
	name = "animal";
};

class objectClass : public NLCgenericEntityClass
{
public:
	objectClass(void);
};

objectClass::objectClass(void)
{
	name = "object";
};

class eatClass : public NLCgenericEntityClass
{
public:
	eatClass(void);
	vector<dogClass*> dogClassActionSubjectList;
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

class dogClass : public animalClass
{
public:
	dogClass(void);
	void rideFunction(vector<dogClass*> &dogClassList, vector<rideClass*> &rideClassList, vector<bikeClass*> &bikeClassList, vector<ballClass*> &ballClassList);
	void eatFunction(vector<eatClass*> &eatClassList, vector<eatClass*> &eatClassList, vector<ballClass*> &ballClassList);
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
	void mainFunction(vector<mainClass*> &mainClassList, vector<dogClass*> &dogClassList, vector<ballClass*> &ballClassList);
};

functionsWithNoSubjectArtificialClass::functionsWithNoSubjectArtificialClass(void)
{
	name = "functionsWithNoSubjectArtificial";
};

void mainFunction(vector<mainClass*> &mainClassList, vector<dogClass*> &dogClassList, vector<ballClass*> &ballClassList)
{
	vector<eatClass*> eatClassList;
	vector<eatClass*> eat1CategoryList;
	eatClass* eat1 = new eatClass();
	eatClassList.push_back(eat1);
	eat1CategoryList.push_back(eat1);
	addEntityToReferenceContextList(referenceContextList0, eat1, 3);
	vector<ballClass*> ball2ActionCategoryList;
	vector<ballClass*> ball2CategoryList;
	for(vector<ballClass*> ::iterator iter1 = ballClassList.begin(); iter1 < ballClassList.end(); iter1++) 
	{
		ballClass* ball2 = *iter1;
		//Singular definite referencing tests
		addToCategoryIfPassSingularDefiniteReferencingTests<ballClass, ballClass> (ball2CategoryList, ball2);
	}
	if(!(ball2CategoryList.empty()))
	{
		ballClass* ball2 = ball2CategoryList.back();
		ball2->lastSentenceReferenced.top() = 3;
		addToCategoryIfPassPluralDefiniteReferencingTests<ballClass, ballClass> (ball2ActionCategoryList, ball2);
		ball2->eatClassActionIncomingList.push_back(eat1);
		eat1->ballClassActionObjectList.push_back(ball2);
	}
	vector<dogClass*> dog2ActionCategoryList;
	vector<dogClass*> dog2CategoryList;
	for(vector<dogClass*> ::iterator iter1 = dogClassList.begin(); iter1 < dogClassList.end(); iter1++) 
	{
		dogClass* dog2 = *iter1;
		//Singular definite referencing tests
		addToCategoryIfPassSingularDefiniteReferencingTests<dogClass, dogClass> (dog2CategoryList, dog2);
	}
	if(!(dog2CategoryList.empty()))
	{
		dogClass* dog2 = dog2CategoryList.back();
		dog2->lastSentenceReferenced.top() = 3;
		addToCategoryIfPassPluralDefiniteReferencingTests<dogClass, dogClass> (dog2ActionCategoryList, dog2);
		dog2->eatClassActionList.push_back(eat1);
		eat1->dogClassActionSubjectList.push_back(dog2);
	}
	(new dogClass)->eatFunction(dog2ActionCategoryList, eatClassList, ball2ActionCategoryList);
}
void dogClass::rideFunction(vector<dogClass*> &dogClassList, vector<rideClass*> &rideClassList, vector<bikeClass*> &bikeClassList, vector<ballClass*> &ballClassList)
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

NLC execution time: 14:8:14 02/12/2014 (finish)
