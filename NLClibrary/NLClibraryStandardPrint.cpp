#include "NLClibraryStandardPrint.h"

void printFunction(vector<printClass*> &printClassList, vector<NLCgenericEntityClass*> &printObjectClassList)
{
	for(vector<NLCgenericEntityClass*> ::iterator iter1 = printObjectClassList.begin(); iter1 < printObjectClassList.end(); iter1++) 
	{
		NLCgenericEntityClass* printObject = *iter1;
		cout << printObject->name << endl;	//print the entity name
		for(unordered_map<string, vector<NLCgenericEntityClass*> *> ::iterator iter1 = printObject->propertyListAll.begin(); iter1 != printObject->propertyListAll.end(); iter1++) 
		{
			vector<NLCgenericEntityClass*> * propertyList = iter1->second;
			printFunction(printClassList, propertyList);
		}
	}
}


