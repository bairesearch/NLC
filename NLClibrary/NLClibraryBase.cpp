#include "NLClibraryBase.h"

//Original NLC library Functions (no generic property and condition lists)

//NLC_USE_ADVANCED_REFERENCING and GIA_USE_ADVANCED_REFERENCING
template <class E1, class E2>
void addToCategoryIfPassPluralDefiniteReferencingTests(vector<E1*> &entityCategoryList, E2* entity0)
{
	if(!(find(entityCategoryList.begin(), entityCategoryList.end(), entity0) != entityCategoryList.end()))
	{
		entityCategoryList.push_back(entity0);
	}
}

//NLC_USE_ADVANCED_REFERENCING
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

//NLC_USE_ADVANCED_REFERENCING
void addEntityToReferenceContextList(vector<NLCgenericEntityClass*> &referenceContextList, NLCgenericEntityClass* NLCgenericEntity, int sentenceIndex)
{
	referenceContextList.push_back(NLCgenericEntity);
	NLCgenericEntity->lastSentenceReferenced.push(sentenceIndex);
}

//NLC_USE_ADVANCED_REFERENCING
void clearReferenceContextList(vector<NLCgenericEntityClass*> &referenceContextList)
{
	for(vector<NLCgenericEntityClass*> ::iterator iter1 = referenceContextList.begin(); iter1 < referenceContextList.end(); iter1++) 
	{
		NLCgenericEntityClass* NLCgenericEntity = *iter1;
		NLCgenericEntity->lastSentenceReferenced.pop();
	}
	referenceContextList.clear();
}

//NLC_USE_ADVANCED_REFERENCING and GIA_USE_ADVANCED_REFERENCING
template <class E1, class E2>
vector<E1*> castVector(vector<E1*> &E1List)
{
	vector<E2*> E2List;
	for(typename vector<E1*> ::iterator iter1 = E1List.begin(); iter1 < E1List.end(); iter1++) 
	{
		E1* E1entity = *iter1;
		E2List.push_back(dynamic_cast<E2*>(E1entity));
	}
	return E2List;
}

//NLC_USE_ADVANCED_REFERENCING
template <class E1, class E2, class E3, class E4>
vector<E1*> castUnorderedMap(unordered_map<E1*, E2*> &E1E2List)
{
	unordered_map<E3*, E4*> E3E4List;
	for(unordered_map<E1*, E2*> ::iterator iter1 = E1E2List.begin(); iter1 != E1E2List.end(); iter1++) 
	{
		E1* E1entity = iter1->first;
		E2* E2entity = iter1->second;
		E3E4List.insert(pair<E3*, E4*>(dynamic_cast<E3*>(E1entity), dynamic_cast<E4*>(E2entity)));
	}
	return E3E4List;
}

//NLC_USE_ADVANCED_REFERENCING
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

