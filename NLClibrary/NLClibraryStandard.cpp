#include "NLClibraryStandard.h"

void print(vector<printClass*> printClassList, vector<NLCgenericEntityClass*> &printObjectClassList)
{
	for(vector<NLCgenericEntityClass*> ::iterator iter1 = moveObjectClassList.begin(); iter1 < moveObjectClassList.end(); iter1++) 
	{
		printObject = *iter1;
		cout << printObject->name << endl;	//print the entity name
		vector<vector<NLCgenericEntityClass*>> NLCgenericEntityPropertyListList;
		NLCgenericEntityClass:getProperties(printObject, NLCgenericEntityPropertyListList);
		for(vector<vector<NLCgenericEntityClass*>> ::iterator iter1 = NLCgenericEntityPropertyListList.begin(); iter1 < NLCgenericEntityPropertyListList.end(); iter1++) 
		{
			vector<NLCgenericEntityClass*> * NLCgenericEntityPropertyList = *iter1;
			print(printClassList, NLCgenericEntityPropertyList);
		}
	}
}

void move(vector<moveClass*> moveClassList, vector<NLCgenericEntityClass*> &moveObjectClassList)
{
	unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*> * NLCgenericEntityFromConditionList = getConditionsByName(moveClassList->back(), "from");	//there only exists 1 action per actionList and so "->back()" can be used
	unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*> * NLCgenericEntityToConditionList = getConditionsByName(moveClassList->back(), "to");	//there only exists 1 action per actionList and so "->back()" can be used
	if(NLCgenericEntityToConditionList.empty())		//Stanford Parser/GIA usually connects "to" condition to the from condition object if there is a preceeding "from" condition
	{
		for(unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*> ::iterator iter1 = NLCgenericEntityFromConditionList.begin(); iter1 != NLCgenericEntityFromConditionList.end(); iter1++) 
		{
			NLCgenericEntityClass* fromConditionObject = iter1->second;
			NLCgenericEntityToConditionList = getConditionsByName(fromConditionObject, "to");
		}
	}

	for(unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*> ::iterator iter1 = NLCgenericEntityFromConditionList.begin(); iter1 != NLCgenericEntityFromConditionList.end(); iter1++)
	{
		NLCgenericEntityClass* fromConditionObject = iter1->second;
		//string actionObjectName = moveObjectClassList.back()->name;
  		//vector<NLCgenericEntityClass*> NLCgenericEntityActionObjectPropertyList = removePropertiesByName(fromConditionObject, actionObjectName);
  		vector<NLCgenericEntityClass*> NLCgenericEntityActionObjectPropertyList = removePropertiesByPointer(fromConditionObject, moveObjectClassList); 
		//vector<NLCgenericEntityClass*> NLCgenericEntityActionObjectPropertyList = removeConditionsByPointer(fromConditionObject, moveObjectClassList, "in"/"at");	//in case the moveObject was defined as "in"/"at" (condition) and not a property of the parent //no not required because "in" conditions will be attaced to the the moveObject and not the move action
		for(vector<NLCgenericEntityClass*> ::iterator iter2 = moveObjectClassList.begin(); iter2 < moveObjectClassList.end(); iter2++) 
		{
			moveObject = *iter2;
			for(unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*> ::iterator iter3 = NLCgenericEntityToConditionList.begin(); iter3 != NLCgenericEntityToConditionList.end(); iter3++)
			{
				NLCgenericEntityClass* toConditionObject = iter3->second;
  				toConditionObject->propertyListX.push_back(moveObject);
			}
		}
	}
}
