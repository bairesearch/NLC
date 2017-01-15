/*******************************************************************************
 *
 * This file is part of NLC.
 *
 * NLC is commercially licensed software. It may not be redistributed,
 * and may only be used by a registered licensee.
 *
 * NLC is sold in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * BAI Commercial License for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You will have received a copy of the BAI Commercial License
 * along with NLC. For more information, visit <http://www.baxterai.com>
 *
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: NLClibraryStandardPrint.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2015 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 1q11a 21-August-2015
 * Requirements: requires C++ code to be generated by NLC
 *
 *******************************************************************************/
 
#include "../NLClibrary/NLClibraryStandardPrint.hpp"
#include "../NLClibrary/NLClibraryStandardOperations.hpp"

void printFunction(vector<NLCgenericEntityClass*>& printClassList, vector<NLCgenericEntityClass*>& printObjectClassList)
{
	for(vector<NLCgenericEntityClass*>::iterator iter1 = printObjectClassList.begin(); iter1 < printObjectClassList.end(); iter1++) 
	{
		NLCgenericEntityClass* printObject = *iter1;
		cout << printObject->name << endl;	//print the entity name
		if(!std::isnan(printObject->value))
		{
			cout << printObject->value << endl;	//print the entity value
		}
				
		for(unordered_map<string, vector<NLCgenericEntityClass*>*>::iterator iter1 = printObject->propertyLists.begin(); iter1 != printObject->propertyLists.end(); iter1++) 
		{
			vector<NLCgenericEntityClass*>* propertyList = iter1->second;
			printFunction(printClassList, *propertyList);
		}
	}
}

//mathText function (macro)
void print(double value)
{
	cout << value << endl;	//print the mathText value
}

