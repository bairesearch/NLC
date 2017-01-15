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
 * Project Version: 1c4d 29-October-2013
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
	className2 = "";
	instanceName2 = "";
}
NLPIitem::NLPIitem(GIAentityNode * entity, int newItemType)
{
	itemType = newItemType;
	className = generateClassName(entity);
	instanceName = generateInstanceName(entity);
	className2 = "";
	instanceName2 = "";
}
NLPIitem::NLPIitem(string newName, int newItemType)
{
	itemType = newItemType;
	className = newName;
	instanceName = "";
	className2 = "";
	instanceName2 = "";
}
NLPIitem::~NLPIitem(void)
{
}

string generateClassName(GIAentityNode * entity)
{
	string className = "";
	#ifndef NLPI_BAD_IMPLEMENTATION
	className = entity->entityName + "Class";
	#else
	if(entity->isConcept)
	{
		className = entity->entityName + "Class";
	}
	else
	{
		className = entity->entityName + convertLongToString(entity->idInstance) + "Class";
	}
	#endif
	return className;
}
string generateInstanceName(GIAentityNode * entity)
{
	string instanceName = entity->entityName + convertLongToString(entity->idInstance);
	return instanceName;
}
string generateActionName(GIAentityNode * entity)
{
	string actionName = entity->entityName;
	return actionName;
}

string convertLongToString(long number)
{
	//return to_string(number);	//C++11
	
	char tempString[100];
	sprintf(tempString, "%ld", number);
	return string(tempString);
}


