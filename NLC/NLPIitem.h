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
 * File Name: NLPIcodeBlock.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2013 Baxter AI (baxterai.com)
 * Project: Natural Language Programming Interface (compiler)
 * Project Version: 1d1b 02-November-2013
 * Requirements: requires text parsed by NLP Parser (eg Relex; available in .CFF format <relations>)
 *
 *******************************************************************************/


#ifndef HEADER_NLPI_ITEM
#define HEADER_NLPI_ITEM

#include <iostream>
#include <fstream>
#include <ctime>
#include <cstring>
#include <cstdlib>	//for random number generation
#include <cmath>
#include <string>
#include <vector>
#include <vector>
#include <unordered_map>
using namespace std;

#include "NLPIglobalDefs.h"
#include "GIAglobalDefs.h"
#include "GIAentityNodeClass.h"
#include "GIAentityConnectionClass.h"

#define NLPI_ITEM_INSTANCE_ID_UNDEFINED (-1)

#define NLPI_ITEM_TYPE_UNDEFINED (-1)
#define NLPI_ITEM_TYPE_OBJECT (0)
#define NLPI_ITEM_TYPE_CLASS (1)
#define NLPI_ITEM_TYPE_FUNCTION (2)
#define NLPI_ITEM_TYPE_TEMPVAR (3)
#define NLPI_ITEM_TYPE_TEMPVAR_APPENDITION "Temp"
#define NLPI_ITEM_TYPE_PROPERTYLISTVAR_APPENDITION "PropertyList"
#define NLPI_ITEM_TYPE_CONDITIONLISTVAR_APPENDITION "ConditionList"
#define NLPI_ITEM_TYPE_DEFINITIONLISTVAR_APPENDITION "DefinitionList"
#define NLPI_ITEM_TYPE_CONDITIONPAIRVAR_APPENDITION "ConditionPair"
#define NLPI_ITEM_TYPE_FUNCTION_ARGUMENT_CONDITION (4)
#define NLPI_ITEM_TYPE_FUNCTION_ARGUMENT_PROPERTY (5)
#define NLPI_ITEM_TYPE_THIS_FUNCTION_ARGUMENT_INSTANCE (6)
#define NLPI_ITEM_TYPE_THIS_FUNCTION_ARGUMENT_INSTANCE_PLURAL (6)
#define NLPI_ITEM_TYPE_CLASS_DECLARATION_CONDITION_LIST (7)
#define NLPI_ITEM_TYPE_CLASS_DECLARATION_PROPERTY_LIST (8)
#define NLPI_ITEM_TYPE_CLASS_DECLARATION_FUNCTION_OBJECT (9)
#define NLPI_ITEM_TYPE_CLASS_DECLARATION_FUNCTION (10)

#define NLPI_ITEM_TYPE_CONDITIONLISTCONDITIONPARAMETERINVERTACOMMAS CHAR_INVERTED_COMMAS

class NLPIitem
{
public:

	NLPIitem(void);
	NLPIitem(GIAentityNode * entity, int newItemType);
	NLPIitem(string newName, int newItemType);
	NLPIitem(NLPIitem * newItem);
	~NLPIitem(void);
	
	int itemType;
	string className;	//eg dog
	string instanceName;	//eg dog1
	#ifdef NLPI_SUPPORT_INPUT_FILE_LISTS
	bool functionArgumentCertified;
	string functionArgumentPassCastClassName;	//used to map function arguments of referenced functions to implicitly defined function arguments (based on function definition content)
	#endif
	vector<string> context;	//item context
	
	string className2;	//used for NLPI_ITEM_TYPE_FUNCTION_ARGUMENT_CONDITION only
	string instanceName2;	//used for NLPI_ITEM_TYPE_FUNCTION_ARGUMENT_CONDITION only
};


string generateClassName(GIAentityNode * entity);
string generateInstanceName(GIAentityNode * entity);
string generateActionName(GIAentityNode * entity);

//string generateItemName(GIAentityNode * entity, int itemType);
string convertLongToString(long number);

#endif
