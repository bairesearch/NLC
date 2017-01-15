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
 * File Name: NLCitemClass.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2014 Baxter AI (baxterai.com)
 * Project: Natural Language Programming Interface (compiler)
 * Project Version: 1g18a 21-July-2014
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/


#ifndef HEADER_NLC_ITEM_CLASS
#define HEADER_NLC_ITEM_CLASS

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

#include "NLCglobalDefs.h"
#include "GIAglobalDefs.h"
#include "GIAentityNodeClass.h"
#include "GIAentityConnectionClass.h"

#define NLC_ITEM_INSTANCE_ID_UNDEFINED (INT_DEFAULT_VALUE)

#define NLC_ITEM_TYPE_UNDEFINED (-1)
#define NLC_ITEM_TYPE_OBJECT (0)
#define NLC_ITEM_TYPE_CLASS (1)
#define NLC_ITEM_TYPE_FUNCTION (2)
#define NLC_ITEM_TYPE_TEMPVAR (3)
#ifdef NLC_INTERPRET_ACTION_PROPERTIES_AND_CONDITIONS_AS_FUNCTION_ARGUMENTS
	#define NLC_ITEM_TYPE_FUNCTION_ARGUMENT_CONDITION (4)
	#define NLC_ITEM_TYPE_FUNCTION_ARGUMENT_PROPERTY (5)
#endif
#define NLC_ITEM_TYPE_THIS_FUNCTION_ARGUMENT_INSTANCE_PLURAL (6)
#define NLC_ITEM_TYPE_CLASS_DECLARATION_CONDITION_LIST (7)
#define NLC_ITEM_TYPE_CLASS_DECLARATION_PROPERTY_LIST (8)
#define NLC_ITEM_TYPE_FUNCTION_OWNER (11)
#define NLC_ITEM_TYPE_FUNCTION_OBJECT (12)
#define NLC_ITEM_TYPE_NEGATIVE (13)
#define NLC_ITEM_TYPE_VARIABLE (14)

#define NLC_CLASS_NAME_APPEND "Class"
#define NLC_FUNCTION_NAME_APPEND "Function"

#define NLC_SUBSTANCE_CONCEPT_CLASS_PREPEND "With"
#define NLC_SUBSTANCE_CONCEPT_CLASS_CONDITION "Condition"
#define NLC_SUBSTANCE_CONCEPT_CLASS_PROPERTY "Property"

#define NLC_ITEM_TYPE_CONDITIONLISTCONDITIONPARAMETERINVERTACOMMAS CHAR_INVERTED_COMMAS

#define NLC_SUPPORT_INPUT_FILE_LISTS_ACTION_SUBJECT_INSTANCE_REPLACEMENT_NAME "this"
#define NLC_SUPPORT_INPUT_FILE_LISTS_ACTION_SUBJECT_CLASS_REPLACEMENT_NAME "thisClassYetToCodeThis"

class NLCitem
{
public:

	NLCitem(void);
	NLCitem(GIAentityNode * entity, int newItemType);
	NLCitem(string newName, int newItemType);
	NLCitem(NLCitem * newItem);
	NLCitem(int newIntValue, int newItemType);
	~NLCitem(void);

	int itemType;
	string className;	//eg dogClass
	string instanceName;	//eg dog1
	string functionName;	//eg dogFunction
	#ifdef NLC_SUPPORT_INPUT_FILE_LISTS
	bool functionArgumentCertified;
	bool functionArgumentPassCastRequired;
	string functionArgumentPassCastClassName;	//used to map function arguments of referenced functions to implicitly defined function arguments (based on function definition content)
	bool formalFunctionArgumentCorrespondsToActionSubjectUseThisAlias;
	#endif
	vector<string> context;	//item context

	string className2;	//used for NLC_ITEM_TYPE_FUNCTION_ARGUMENT_CONDITION only
	string instanceName2;	//used for NLC_ITEM_TYPE_FUNCTION_ARGUMENT_CONDITION only

	bool negative;
	#ifdef NLC_LOGICAL_CONDITIONS_SUPPORT_CONJUNCTIONS
	int conjunctionType;
	#endif
	int intValue;
};


string generateClassName(GIAentityNode * entity);
	string generateClassName(string entityName);
string generateFunctionName(GIAentityNode * entity);
	string generateFunctionName(string entityName);
string generateInstanceName(GIAentityNode * entity);

//string generateItemName(GIAentityNode * entity, int itemType);
string convertLongToString(long number);

#endif
