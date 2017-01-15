#include "NLClibraryStandard.h"

void printFunction(vector<printClass*> printClassList, vector<NLCgenericEntityClass*> &printObjectClassList)
{
	for(vector<NLCgenericEntityClass*> ::iterator iter1 = printObjectClassList.begin(); iter1 < printObjectClassList.end(); iter1++) 
	{
		NLCgenericEntityClass* printObject = *iter1;
		cout << printObject->name << endl;	//print the entity name
		for(unordered_map<string, vector<NLCgenericEntityClass*> *> ::iterator iter1 = printObject->propertyListAll.begin(); iter1 != printObject->propertyListAll.end(); iter1++) 
		{
			vector<NLCgenericEntityClass*> * propertyList = iter1->second;
			print(printClassList, propertyList);
			
			/*
			for(vector<NLCgenericEntityClass*> ::iterator iter2 = propertyList.begin(); iter2 < propertyList.end(); iter2++) 
			{
				NLCgenericEntityClass * property = *iter2;
			}
			*/
		}
	}
}

void moveFunction(vector<moveClass*> moveClassList, vector<NLCgenericEntityClass*> &moveObjectClassList)
{
	for(vector<NLCgenericEntityClass*> ::iterator iter1 = moveClassList.begin(); iter1 < moveClassList.end(); iter1++) 
	{
		moveAction = *iter2;
		unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*> * NLCgenericEntityFromConditionList = getConditionListByConditionName(moveAction, "from"); 
		unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*> * NLCgenericEntityToConditionList = getConditionListByConditionName(moveAction, "to"); 

		if(NLCgenericEntityToConditionList == NULL)		//Stanford Parser/GIA usually connects "to" condition to the from condition object if there is a preceeding "from" condition
		{
			if(NLCgenericEntityFromConditionList != NULL)
			{
				for(unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*> ::iterator iter1 = NLCgenericEntityFromConditionList.begin(); iter1 != NLCgenericEntityFromConditionList.end(); iter1++) 
				{
					NLCgenericEntityClass* fromConditionObject = iter1->second;
					NLCgenericEntityToConditionList = getConditionListByConditionName(fromConditionObject, "to"); 
				}
			}
		}

		if(NLCgenericEntityFromConditionList != NULL)
		{
			if(NLCgenericEntityToConditionList != NULL)
			{
				for(unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*> ::iterator iter2 = NLCgenericEntityFromConditionList.begin(); iter2 != NLCgenericEntityFromConditionList.end(); iter2++)
				{
					NLCgenericEntityClass* fromConditionObject = iter2->second;
					for(vector<NLCgenericEntityClass*> ::iterator iter3 = moveObjectClassList.begin(); iter3 < moveObjectClassList.end(); iter3++) 
					{
						NLCgenericEntityClass* moveObject = *iter3;
						bool moveObjectFoundAttachedAsPropertyAndHasBeenRemoved = false;
						vector<NLCgenericEntityClass*> * fromObjectMoveObjectPropertyList = getPropertyListByName(fromConditionObject, moveObject->name); 
						if(fromObjectMoveObjectPropertyList != NULL)
						{
							if(removeItemFromVectorList(fromObjectMoveObjectPropertyList, moveObject))
							{	
								moveObjectFoundAttachedAsPropertyAndHasBeenRemoved = true;
							}
						}

						if(moveObjectFoundAttachedAsPropertyAndHasBeenRemoved)
						{
							for(unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*> ::iterator iter4 = NLCgenericEntityToConditionList.begin(); iter4 != NLCgenericEntityToConditionList.end(); iter4++)
							{
								NLCgenericEntityClass* toConditionObject = iter4->second;
  								addPropertyListByName(toConditionObject, moveObject);
								#ifdef NLC_DEBUG_LIBRARY
								cout << "move() pass: moveParentOld (fromConditionObject) = " << fromConditionObject->name << ", moveObject = " << moveObject->name << "moveParentNew (toConditionObject) = " << toConditionObject->name << endl;
								#endif
							}
						}
						else
						{
							/*
							//in case the moveObject was defined as "in"/"at" (condition) and not a property of the parent //no not required because "in" conditions will be attaced to the the moveObject and not the move action

							unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*> * NLCgenericEntityFromObjectAtConditionList = getConditionListByConditionName(fromConditionObject, "at"); 
							if(NLCgenericEntityFromObjectAtConditionList == NULL)
							{
								NLCgenericEntityFromObjectAtConditionList = getConditionListByConditionName(fromConditionObject, "in");
							}
							*/
							cout << "move() error: move object parent not found" << endl;
						}
					}
				}
			}
			else
			{
				cout << "move() error: move action 'from' condition not found" << endl;
			}
		}
		else
		{
			cout << "move() error: move action 'to' condition not found" << endl;
		}
	}
}


//New NLC library Functions (generic property and condition lists) >= NLC1nXy

vector<NLCgenericEntityClass*> * getPropertyListByName(NLCgenericEntityClass* entity, string propertyName)
{
	vector<NLCgenericEntityClass*> * propertyList = NULL;
	for(unordered_map<string, vector<NLCgenericEntityClass*> *> ::iterator iter1 = entity->propertyListAll.begin(); iter1 != entity->propertyListAll.end(); iter1++) 
	{
		string key = iter1->first;
		if(key->first == propertyName)
		{
			propertyList = iter1->second;
		}
	}
	return propertyList;
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

