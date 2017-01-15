/*******************************************************************************
 *
 * This file is part of BAIPROJECT.
 *
 * BAIPROJECT is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License version 3
 * only, as published by the Free Software Foundation.
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
 * File Name: NLPIcodeBlock.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2013 Baxter AI (baxterai.com)
 * Project: Natural Language Programming Interface (compiler)
 * Project Version: 1e8b 24-November-2013
 * Requirements: requires text parsed by NLP Parser (eg Relex; available in .CFF format <relations>)
 *
 *******************************************************************************/




#include "NLPIitem.h"
#include "GIAtranslatorOperations.h"



NLPIitem::NLPIitem(void)
{
	itemType = NLPI_ITEM_INSTANCE_ID_UNDEFINED;
	className = "";
	instanceName = "";
	functionName = "";
	className2 = "";
	instanceName2 = "";
	#ifdef NLPI_SUPPORT_INPUT_FILE_LISTS
	functionArgumentCertified = false;
	functionArgumentPassCastRequired = false;
	functionArgumentPassCastClassName = "";
	formalFunctionArgumentCorrespondsToActionSubjectUseThisAlias = false;
	#endif
}
NLPIitem::NLPIitem(GIAentityNode * entity, int newItemType)
{
	itemType = newItemType;
	className = generateClassName(entity);
	instanceName = generateInstanceName(entity);
	functionName = generateFunctionName(entity);	//added 9 November 2013
	className2 = "";
	instanceName2 = "";
	#ifdef NLPI_SUPPORT_INPUT_FILE_LISTS
	functionArgumentCertified = false;
	functionArgumentPassCastRequired = false;
	functionArgumentPassCastClassName = "";
	formalFunctionArgumentCorrespondsToActionSubjectUseThisAlias = false;
	#endif
}
NLPIitem::NLPIitem(string newName, int newItemType)
{
	itemType = newItemType;
	className = generateClassName(newName);	//changed 9 November 2013
	#ifdef NLPI_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS
	instanceName = newName;		//added 21 November 2013
	#else
	instanceName = ""
	#endif
	functionName = generateFunctionName(newName);	//added 9 November 2013
	className2 = "";
	instanceName2 = "";
	#ifdef NLPI_SUPPORT_INPUT_FILE_LISTS
	functionArgumentCertified = false;
	functionArgumentPassCastRequired = false;
	functionArgumentPassCastClassName = "";
	formalFunctionArgumentCorrespondsToActionSubjectUseThisAlias = false;
	#endif
}
NLPIitem::NLPIitem(NLPIitem * newItem)
{
	itemType = newItem->itemType;
	className = newItem->className;
	instanceName = newItem->instanceName;
	functionName = newItem->functionName;
	className2 = newItem->className2;
	instanceName2 = newItem->instanceName2;
	#ifdef NLPI_SUPPORT_INPUT_FILE_LISTS
	functionArgumentCertified = false;
	functionArgumentPassCastRequired = false;
	functionArgumentPassCastClassName = newItem->functionArgumentPassCastClassName;
	formalFunctionArgumentCorrespondsToActionSubjectUseThisAlias = newItem->formalFunctionArgumentCorrespondsToActionSubjectUseThisAlias;;
	#endif
}
NLPIitem::~NLPIitem(void)
{
}

string generateClassName(GIAentityNode * entity)
{
	string className = generateClassName(entity->entityName);
	return className;
}
string generateClassName(string entityName)
{
	string className = entityName + NLPI_CLASS_NAME_APPEND;
	return className;
}
string generateFunctionName(GIAentityNode * entity)
{
	return generateFunctionName(entity->entityName);
}
string generateFunctionName(string entityName)
{
	string functionName = entityName + NLPI_FUNCTION_NAME_APPEND;
	return functionName;
}
string generateInstanceName(GIAentityNode * entity)
{
	string instanceName = entity->entityName + convertLongToString(entity->idInstance);
	return instanceName;
}

string convertLongToString(long number)
{
	//return to_string(number);	//C++11
	
	char tempString[100];
	sprintf(tempString, "%ld", number);
	return string(tempString);
}


