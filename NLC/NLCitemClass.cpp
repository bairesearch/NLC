/*******************************************************************************
 *
 * This file is part of BAIPROJECT.
 *
 * BAIPROJECT is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License version 3
 * only, as published by the Free Software Foundation. The use of
 * intermediary programs or interfaces including file i/o is considered
 * remote network interaction. This does not imply such arrangements
 * do not constitute derivative works.
 *
 * BAIPROJECT is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU Affero General Public License
 * version 3 along with BAIPROJECT.  If not, see <http://www.gnu.org/licenses/>
 * for a copy of the AGPLv3 License.
 *
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: NLCitemClass.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2014 Baxter AI (baxterai.com)
 * Project: Natural Language Programming Interface (compiler)
 * Project Version: 1k5b 13-October-2014
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/




#include "NLCitemClass.h"
#include "GIAtranslatorOperations.h"
#include "SHAREDvars.h"	//required for convertLongToString()



NLCitem::NLCitem(void)
{
	itemType = NLC_ITEM_INSTANCE_ID_UNDEFINED;
	className = "";
	instanceName = "";
	functionName = "";
	className2 = "";
	instanceName2 = "";
	#ifdef NLC_SUPPORT_INPUT_FILE_LISTS
	functionArgumentCertified = false;
	functionArgumentPassCastRequired = false;
	functionArgumentPassCastClassName = "";
	formalFunctionArgumentCorrespondsToActionSubjectUseThisAlias = false;
	#endif
	negative = false;
	#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS
	conjunctionType = INT_DEFAULT_VALUE;
	#endif
	name = "";
}
NLCitem::NLCitem(GIAentityNode * entity, int newItemType)
{
	itemType = newItemType;
	className = generateClassName(entity);
	instanceName = generateInstanceName(entity);
	functionName = generateFunctionName(entity);	//added 9 November 2013
	className2 = "";
	instanceName2 = "";
	#ifdef NLC_SUPPORT_INPUT_FILE_LISTS
	functionArgumentCertified = false;
	functionArgumentPassCastRequired = false;
	functionArgumentPassCastClassName = "";
	formalFunctionArgumentCorrespondsToActionSubjectUseThisAlias = false;
	#endif
	negative = false;
	#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS
	conjunctionType = INT_DEFAULT_VALUE;
	#endif
	name = entity->entityName;
	genericObjectName = "";
}
NLCitem::NLCitem(string newName, int newItemType)
{
	itemType = newItemType;
	className = generateClassName(newName);	//changed 9 November 2013
	#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS
	instanceName = newName;		//added 21 November 2013
	#else
	instanceName = ""
	#endif
	functionName = generateFunctionName(newName);	//added 9 November 2013
	className2 = "";
	instanceName2 = "";
	#ifdef NLC_SUPPORT_INPUT_FILE_LISTS
	functionArgumentCertified = false;
	functionArgumentPassCastRequired = false;
	functionArgumentPassCastClassName = "";
	formalFunctionArgumentCorrespondsToActionSubjectUseThisAlias = false;
	#endif
	negative = false;
	#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS
	conjunctionType = INT_DEFAULT_VALUE;
	#endif
	//if(newItemType == NLC_ITEM_TYPE_VARIABLE)
	name = newName;
	genericObjectName = "";
}
NLCitem::NLCitem(NLCitem * newItem)
{
	itemType = newItem->itemType;
	className = newItem->className;
	instanceName = newItem->instanceName;
	functionName = newItem->functionName;
	className2 = newItem->className2;
	instanceName2 = newItem->instanceName2;
	#ifdef NLC_SUPPORT_INPUT_FILE_LISTS
	functionArgumentCertified = false;
	functionArgumentPassCastRequired = false;
	functionArgumentPassCastClassName = newItem->functionArgumentPassCastClassName;
	formalFunctionArgumentCorrespondsToActionSubjectUseThisAlias = newItem->formalFunctionArgumentCorrespondsToActionSubjectUseThisAlias;;
	#endif
	negative = false;
	#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS
	conjunctionType = INT_DEFAULT_VALUE;
	#endif
	name = newItem->name;
	genericObjectName = "";
}
NLCitem::~NLCitem(void)
{
}

string generateClassName(GIAentityNode * entity)
{
	string className = generateClassName(entity->entityName);
	return className;
}
string generateClassName(string entityName)
{
	string className = entityName + NLC_CLASS_NAME_APPEND;
	return className;
}
string generateFunctionName(GIAentityNode * entity)
{
	return generateFunctionName(entity->entityName);
}
string generateFunctionName(string entityName)
{
	string functionName = entityName + NLC_FUNCTION_NAME_APPEND;
	return functionName;
}
string generateInstanceName(GIAentityNode * entity)
{
	string instanceName = entity->entityName + convertLongToString(entity->idInstance);
	return instanceName;
}

string generateTypeName(string entityName)
{
	string typeName = entityName;
	return typeName;
}



