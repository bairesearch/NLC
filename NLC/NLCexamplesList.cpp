NLC execution time: 23:47:5 02/12/2014 (start)
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

class redClass : public NLCgenericEntityClass
{
public:
	redClass(void);
};

redClass::redClass(void)
{
	name = "red";
};

class blueClass : public NLCgenericEntityClass
{
public:
	blueClass(void);
};

blueClass::blueClass(void)
{
	name = "blue";
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
	vector<objectClass*> objectClassActionObjectList;
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

class animalClass : public NLCgenericEntityClass
{
public:
	animalClass(void);
	void eatFunction(vector<eatClass*> &eatClassList, vector<eatClass*> &eatClassList, vector<objectClass*> &objectClassList);
	vector<eatClass*> eatClassActionList;
};

animalClass::animalClass(void)
{
	name = "animal";
};

class ballClass : public objectClass
{
public:
	ballClass(void);
	vector<blueClass*> blueClassPropertyList;
	vector<happyClass*> happyClassPropertyList;
};

ballClass::ballClass(void)
{
	name = "ball";
};

class functionsWithNoSubjectArtificialClass : public NLCgenericEntityClass
{
public:
	functionsWithNoSubjectArtificialClass(void);
	void mainFunction(vector<mainClass*> &mainClassList, vector<redClass*> &redClassList, vector<blueClass*> &blueClassList, vector<animalClass*> &animalClassList, vector<objectClass*> &objectClassList);
};

functionsWithNoSubjectArtificialClass::functionsWithNoSubjectArtificialClass(void)
{
	name = "functionsWithNoSubjectArtificial";
};

class dogClass : public animalClass
{
public:
	dogClass(void);
	vector<redClass*> redClassPropertyList;
	void rideFunction(vector<dogClass*> &dogClassList, vector<rideClass*> &rideClassList, vector<bikeClass*> &bikeClassList, vector<ballClass*> &ballClassList);
};

dogClass::dogClass(void)
{
	name = "dog";
};

void mainFunction(vector<mainClass*> &mainClassList, vector<redClass*> &redClassList, vector<blueClass*> &blueClassList, vector<animalClass*> &animalClassList, vector<objectClass*> &objectClassList)
{
	vector<eatClass*> eatClassList;
	vector<eatClass*> eat1CategoryList;
	eatClass* eat1 = new eatClass();
	eatClassList.push_back(eat1);
	eat1CategoryList.push_back(eat1);
	addEntityToReferenceContextList(referenceContextList0, eat1, 3);
	vector<objectClass*> object2ActionCategoryList;
	vector<objectClass*> object2CategoryList;
	for(vector<objectClass*> ::iterator iter1 = objectClassList.begin(); iter1 < objectClassList.end(); iter1++) 
	{
		objectClass* object2 =* iter1;
		//Singular definite referencing tests
		addToCategoryIfPassSingularDefiniteReferencingTests<objectClass, objectClass> (object2CategoryList, object2);
	}
	if(!(object2CategoryList.empty()))
	{
		objectClass* object2 = object2CategoryList.back();
		object2->lastSentenceReferenced.top() = 3;
		addToCategoryIfPassPluralDefiniteReferencingTests<objectClass, objectClass> (object2ActionCategoryList, object2);
		object2->eatClassActionIncomingList.push_back(eat1);
		eat1->objectClassActionObjectList.push_back(object2);
	}
	vector<animalClass*> animal2ActionCategoryList;
	vector<animalClass*> animal2CategoryList;
	for(vector<animalClass*> ::iterator iter1 = animalClassList.begin(); iter1 < animalClassList.end(); iter1++) 
	{
		animalClass* animal2 =* iter1;
		//Singular definite referencing tests
		addToCategoryIfPassSingularDefiniteReferencingTests<animalClass, animalClass> (animal2CategoryList, animal2);
	}
	if(!(animal2CategoryList.empty()))
	{
		animalClass* animal2 = animal2CategoryList.back();
		animal2->lastSentenceReferenced.top() = 3;
		addToCategoryIfPassPluralDefiniteReferencingTests<animalClass, animalClass> (animal2ActionCategoryList, animal2);
		animal2->eatClassActionList.push_back(eat1);
		eat1->animalClassActionSubjectList.push_back(animal2);
	}
	(new animalClass)->eatFunction(animal2ActionCategoryList, eatClassList, object2ActionCategoryList);
}
void dogClass::rideFunction(vector<dogClass*> &dogClassList, vector<rideClass*> &rideClassList, vector<bikeClass*> &bikeClassList, vector<ballClass*> &ballClassList)
{
	vector<ballClass*> ball1CategoryList;
	for(vector<ballClass*> ::iterator iter1 = ballClassList.begin(); iter1 < ballClassList.end(); iter1++) 
	{
		ballClass* ball1 =* iter1;
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
		NLCgenericEntityClass* NLCgenericEntity =* iter1;
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
		E1* NLCgenericEntity =* iter1;
		E2List.push_back(dynamic_cast<E2*>(NLCgenericEntity));
	}
	return E2List;
}

template <class E1>
void findAliasAndAddToCategoryList(vector<E1*> &E1List, string aliasName, vector<E1*> &E1CategoryList)
{
	for(typename vector<E1*> ::iterator iter1 = E1List.begin(); iter1 < E1List.end(); iter1++) 
	{
		E1* NLCgenericEntity =* iter1;
		if((find(NLCgenericEntity->aliasList.begin(), NLCgenericEntity->aliasList.end(), aliasName) != NLCgenericEntity->aliasList.end()))
		{
			E1CategoryList.push_back(NLCgenericEntity);
		}
	}
}

NLC execution time: 23:50:2 02/12/2014 (finish)
