#include "NLClibraryStandard.h"


//New NLC library Functions (generic property and condition lists) >= NLC1nXy

vector<NLCgenericEntityClass*> * getPropertyListByName(NLCgenericEntityClass* entity, string propertyName)
{
	vector<NLCgenericEntityClass*> * propertyList = getVectorListByName(entity->propertyListAll, string vectorName);
	return propertyList;
}

vector<NLCgenericEntityClass*> * getVectorListByName(unordered_map<string, vector<NLCgenericEntityClass*>* >* vectorListAll, string vectorName)
{
	vector<NLCgenericEntityClass*> * vectorList = NULL;
	for(unordered_map<string, vector<NLCgenericEntityClass*> *> ::iterator iter1 = vectorListAll.begin(); iter1 != vectorListAll.end(); iter1++) 
	{
		string key = iter1->first;
		if(key->first == vectorName)
		{
			vectorList = iter1->second;
		}
	}
	return vectorList;
}

vector<NLCgenericEntityClass*> * getActionListByName(NLCgenericEntityClass* entity, string propertyName)
{
	vector<NLCgenericEntityClass*> * actionList = getVectorListByName(entity->actionListAll, string vectorName);
	return actionList;
}
vector<NLCgenericEntityClass*> * getActionIncomingListByName(NLCgenericEntityClass* entity, string actionName)
{
	vector<NLCgenericEntityClass*> * actionIncomingList = getVectorListByName(entity->actionIncomingListAll, string vectorName);
	return actionIncomingList;
}
vector<NLCgenericEntityClass*> * getActionSubjectListByName(NLCgenericEntityClass* entity, string actionName)
{
	vector<NLCgenericEntityClass*> * actionSubjectList = getVectorListByName(entity->actionSubjectListAll, string vectorName);
	return actionSubjectList;
}
vector<NLCgenericEntityClass*> * getActionObjectListByName(NLCgenericEntityClass* entity, string actionName)
{
	vector<NLCgenericEntityClass*> * actionObjectList = getVectorListByName(entity->actionObjectListAll, string vectorName);
	return actionObjectList;
}

unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*> * getConditionListByConditionName(NLCgenericEntityClass* entity, string conditionName, string conditionObjectName) 
{
	unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*> * conditionList = NULL;
	for(unordered_map<pair<string, string>, unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*> *> ::iterator iter1 = entity->conditionListAll.begin(); iter1 != entity->conditionListAll.end(); iter1++) 
	{
		pair<string, string> key = iter1->first;
		if((key->first == conditionName) && (key->second == conditionObjectName))
		{
			conditionList = iter1->second;
		}
	}
	return conditionList;
}

unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*> * getConditionListByConditionName(NLCgenericEntityClass* entity, string conditionName) 
{
	unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*> * conditionList = NULL;
	for(unordered_map<pair<string, string>, unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*> *> ::iterator iter1 = entity->conditionListAll.begin(); iter1 != entity->conditionListAll.end(); iter1++) 
	{
		pair<string, string> key = iter1->first;
		if(key->first == conditionName)
		{
			conditionList = iter1->second;
		}
	}
	return conditionList;
}

bool addPropertyListByName(NLCgenericEntityClass* entity, NLCgenericEntityClass * propertyEntity)
{
	bool result = false;
	vector<NLCgenericEntityClass*> * propertyList = getPropertyListByName(entity, propertyEntity->name);
	if(propertyList != NULL)
	{
		result = true;
		propertyList->push_back(propertyEntity);
	}
	return result;
}

bool addConditionListByConditionName(NLCgenericEntityClass* entity, NLCgenericEntityClass * condition, NLCgenericEntityClass * conditionObject) 
{
	bool result = false;
	unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*> * conditionList = getConditionListByName(entity, condition->name, conditionObject->name);
	if(conditionList != NULL)
	{
		result = true;
		conditionList->insert(pair<NLCgenericEntityClass*, NLCgenericEntityClass*>(condition, conditionObject));
	}
	return result;
}

template <class E1>
bool removeItemFromVectorList(vector<E1*> * vectorList, E1* itemToRemove)
{
	bool result = false;
	for(vector<E1*> ::iterator iter1 = vectorList.begin(); iter1 < vectorList.end();) 
	{
		itemTemp = *iter1;
		if(itemToRemove == itemTemp)
		{
			iter1 = vectorList->erase(iter1);
			result = true;
		}
		else
		{
			iter1++;
		}
	}
}

template <class E1, class E2>
bool removeItemFromUnorderedMap(unordered_map<E1*, E2*> * unorderedMap, pair<E1*, E2*> *itemToRemove)
{
	bool result = false;
	for(unordered_map<E1*, E2*> ::iterator iter1 = unorderedMap.begin(); iter1 != unorderedMap.end();) 
	{
		NLCgenericEntityClass* first = iter1->first;
		NLCgenericEntityClass* second = iter1->second;
		if((itemToRemove->first == first) && (itemToRemove->second == second))
		{
			iter1 = unorderedMap->erase(iter1);
			result = true;
		}
		else
		{
			iter1++;
		}
	}
}

/*
template <class E1, class E2>
void removeObjectFromUnorderedMap(unordered_map<E1*, E2*> * unorderedMap, E2 *objectToRemove)
{
	for(unordered_map<E1*, E2*> ::iterator iter1 = unorderedMap.begin(); iter1 != unorderedMap.end();) 
	{
		NLCgenericEntityClass* second = iter1->second;
		if((itemToRemove->second == objectToRemove))
		{
			iter1 = unorderedMap->erase(iter1);
		}
		else
		{
			iter1++;
		}
	}
}
*/

