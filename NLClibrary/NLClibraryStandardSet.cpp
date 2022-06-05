 /*******************************************************************************
 *
 * License: GNU Affero General Public License version 3 (AGPLv3)
 *
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: NLClibraryStandardSet.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2022 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 2p1a 05-June-2022
 * Requirements: requires C++ code to be generated by NLC
 *
 *******************************************************************************/

#include "NLClibraryStandardSet.hpp"
#include "NLClibraryStandardMath.hpp"
#include "NLClibraryStandardOperations.hpp"

//e.g. Set the value to 5.
void setFunction(vector<NLCgenericEntityClass*>& setClassList, vector<NLCgenericEntityClass*>& setObjectClassList)
{
	for(vector<NLCgenericEntityClass*>::iterator iter1 = setClassList.begin(); iter1 < setClassList.end(); iter1++) 
	{
		NLCgenericEntityClass* setAction = *iter1;

		for(vector<NLCgenericEntityClass*>::iterator iter2 = setObjectClassList.begin(); iter2 < setObjectClassList.end(); iter2++) 
		{
			NLCgenericEntityClass* setObject = *iter2;
			
			unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>* NLCgenericEntityToConditionList = getConditionListByConditionName(setAction, NLC_LIBRARY_SET_FUNCTION_ACTION_CONDITION_TO_NAME); 

			if(NLCgenericEntityToConditionList != NULL)
			{	
				for(unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>::iterator iter3 = NLCgenericEntityToConditionList->begin(); iter3 != NLCgenericEntityToConditionList->end(); iter3++)
				{
					NLCgenericEntityClass* toConditionObject = iter3->second;
					
					#ifdef NLC_MATH_OBJECTS				
					//eg "Set the mathObjectNumericalValue to 5."
					if(isStringNumberOrFractional(toConditionObject->name))
					{
						setObject->mathObjectNumericalValue = atof(toConditionObject->name.c_str());
					}
					else
					{
					#endif
						addPropertyGeneric(setObject, toConditionObject);
					#ifdef NLC_MATH_OBJECTS				
					}
					#endif
				}
			}
		}
	}
}



