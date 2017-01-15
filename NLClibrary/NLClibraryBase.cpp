#include "NLClibraryBase.h"

//New NLC library Functions (generic property and condition lists) >= NLC1nXy

template <class E1>
vector<NLCgenericEntityClass*> getPropertiesByName(E1* entity, string name) 
{
	vector<NLCgenericEntityClass*> * NLCgenericEntityPropertyList;
	vector<vector<NLCgenericEntityClass*>> NLCgenericEntityPropertyListList;
	E1:getProperties<NLCgenericEntityClass*>(entity, NLCgenericEntityPropertyListList);
	for(vector<vector<NLCgenericEntityClass*>> ::iterator iter1 = NLCgenericEntityPropertyListList.begin(); iter1 < NLCgenericEntityPropertyListList.end(); iter1++) 
	{
		vector<NLCgenericEntityClass*> * NLCgenericEntityPropertyListTemp = *iter1;
		if(!(NLCgenericEntityPropertyListTemp->empty())) 
		{
			if(NLCgenericEntityPropertyListTemp->back()->name == name)	//gets any entity within the list (all entities are assumed to have the same name)
			{
				NLCgenericEntityPropertyList = NLCgenericEntityPropertyListTemp;
			}
		}
	}
	return NLCgenericEntityPropertyList;
}

template <class E1>
unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*> getConditionsByName(E1* entity, string name) 	//NB the name refers to the condition not the conditionObject
{
	unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*> * NLCgenericEntityConditionsList;
	vector<unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>> NLCgenericEntityConditionListList;
	E1:getConditions<NLCgenericEntityClass*>(entity, NLCgenericEntityConditionListList);
	for(vector<unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>> ::iterator iter1 = NLCgenericEntityConditionListList.begin(); iter1 < NLCgenericEntityConditionListList.end(); iter1++) 
	{
		unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*> * NLCgenericEntityConditionsListTemp = *iter1;
		if(!(NLCgenericEntityConditionsListTemp->empty())) 
		{
			if(NLCgenericEntityConditionsListTemp->begin()->first->name == name)	//gets any entity within the list (all entities are assumed to have the same name)
			{
				NLCgenericEntityConditionsList = NLCgenericEntityConditionsListTemp;
			}
		}
	}
	return NLCgenericEntityConditionsList;
}

template <class E1>
void removePropertiesByPointer(E1* E1entity, vector<NLCgenericEntityClass*> &propertiesToRemoveList) 
{
	for(vector<NLCgenericEntityClass*> ::iterator iter1 = propertiesToRemoveList.begin(); iter1 < propertiesToRemoveList.end(); iter1++) 
	{
		NLCgenericEntityClass* propertyToRemove = *iter1;
		E1:removeProperties(E1entity, propertyToRemove);
	}
}

template <class E1>
void removeItemFromVectorList(vector<E1*> * vectorList, E1* itemToRemove)
{
	for(vector<E1*> ::iterator iter1 = vectorList.begin(); iter1 < vectorList.end();) 
	{
		itemTemp = *iter1;
		if(itemToRemove == itemTemp)
		{
			iter1 = vectorList->erase(iter1);
		}
		else
		{
			iter1++;
		}
	}
}

template <class E1, class E2>
void removeItemFromUnorderedMap(unordered_map<E1*, E2*> * unorderedMap, pair<E1*, E2*> *itemToRemove)
{
	for(unordered_map<E1*, E2*> ::iterator iter1 = unorderedMap.begin(); iter1 != unorderedMap.end();) 
	{
		NLCgenericEntityClass* first = iter1->first;
		NLCgenericEntityClass* second = iter1->second;
		if((itemToRemove->first == first) && (itemToRemove->second == second))
		{
			iter1 = unorderedMap->erase(iter1);
		}
		else
		{
			iter1++;
		}
	}
}

/*
//must replicate (generate) for each NLC class;
template <class E1>	//TEMPLATE SHOULD BE MANUALLY REPLACED WITH CLASS NAME
void getProperties(E1* E1entity, vector<vector<NLCgenericEntityClass*>> &NLCgenericEntityPropertyListList) 
{
	NLCgenericEntityPropertyList.push_back(castVector<propertyList1Class*, NLCgenericEntityClass*>(E1entity->propertyList1));
	NLCgenericEntityPropertyList.push_back(castVector<propertyList2Class*, NLCgenericEntityClass*>(E1entity->propertyList2));		
	ParentClassName::getProperties(dynamic_cast<ParentClassName*>(E1entity), NLCgenericEntityPropertyListList); // calls base class' function
}
template <class E1>	//TEMPLATE SHOULD BE MANUALLY REPLACED WITH CLASS NAME
void getConditions(E1* E1entity, vector<unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>> &NLCgenericEntityConditionListList) 
{
	NLCgenericEntityPropertyList.push_back(castUnorderedMap<conditionList1Class*, NLCgenericEntityClass*>(E1entity->conditionList1));
	NLCgenericEntityPropertyList.push_back(castUnorderedMap<conditionList2ClassA*, conditionList2ClassB*, NLCgenericEntityClass*, NLCgenericEntityClass*>(E1entity->conditionList2));
	ParentClassName::getConditions(dynamic_cast<ParentClassName*>(E1entity), NLCgenericEntityConditionListList); // calls base class' function
}

template <class E1>	//TEMPLATE SHOULD BE MANUALLY REPLACED WITH CLASS NAME
void removeProperties(E1* E1entity, NLCgenericEntityClass *propertyToRemove) 
{
	removeItemFromVectorList<NLCgenericEntityClass>(E1entity->propertyList1, propertyToRemove)
	removeItemFromVectorList<NLCgenericEntityClass>(E1entity->propertyList2, propertyToRemove)
	ParentClassName::removeProperties(dynamic_cast<ParentClassName*>(E1entity), propertyToRemove); // calls base class' function
}

template <class E1>	//TEMPLATE SHOULD BE MANUALLY REPLACED WITH CLASS NAME
void removeConditions(E1* E1entity, pair<NLCgenericEntityClass*, NLCgenericEntityClass*> *conditionToRemove) 
{
	removeItemFromUnorderedMap<NLCgenericEntityClass, NLCgenericEntityClass>(E1entity->propertyList1, conditionToRemove)
	removeItemFromUnorderedMap<NLCgenericEntityClass, NLCgenericEntityClass>(E1entity->propertyList2, conditionToRemove)
	ParentClassName::removeProperties(dynamic_cast<ParentClassName*>(E1entity), conditionToRemove); // calls base class' function
}
*/
	




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

