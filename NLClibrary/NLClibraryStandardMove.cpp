#include "NLClibraryStandardMove.h"

void moveFunction(vector<moveClass*> &moveClassList, vector<NLCgenericEntityClass*> &moveObjectClassList)
{
	for(vector<NLCgenericEntityClass*> ::iterator iter1 = moveClassList.begin(); iter1 < moveClassList.end(); iter1++) 
	{
		moveAction = *iter2;
		unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*> * NLCgenericEntityFromConditionList = getConditionListByConditionName(moveAction, NLC_USE_LIBRARY_MOVE_FUNCTION_ACTION_CONDITION_FROM_NAME); 
		unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*> * NLCgenericEntityToConditionList = getConditionListByConditionName(moveAction, NLC_USE_LIBRARY_MOVE_FUNCTION_ACTION_CONDITION_TO_NAME); 

		if(NLCgenericEntityToConditionList == NULL)		//Stanford Parser/GIA usually connects "to" condition to the from condition object if there is a preceeding "from" condition
		{
			if(NLCgenericEntityFromConditionList != NULL)
			{
				for(unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*> ::iterator iter1 = NLCgenericEntityFromConditionList.begin(); iter1 != NLCgenericEntityFromConditionList.end(); iter1++) 
				{
					NLCgenericEntityClass* fromConditionObject = iter1->second;
					NLCgenericEntityToConditionList = getConditionListByConditionName(fromConditionObject, NLC_USE_LIBRARY_MOVE_FUNCTION_ACTION_CONDITION_TO_NAME); 
				}
			}
		}
		if(NLCgenericEntityFromConditionList == NULL)
		{
			//in case the moveObject was defined as "in"/"at" (condition) and not a property of the parent, eg The ball is near the park. Move the ball to the mountain.
			unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*> * NLCgenericEntityFromConditionList = getConditionListByConditionName(fromConditionObject, NLC_USE_LIBRARY_MOVE_FUNCTION_ACTIONOBJECT_CONDITION_AT_NAME); 
			if(NLCgenericEntityFromConditionList == NULL)
			{
				NLCgenericEntityFromConditionList = getConditionListByConditionName(fromConditionObject, NLC_USE_LIBRARY_MOVE_FUNCTION_ACTIONOBJECT_CONDITION_IN_NAME);
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

