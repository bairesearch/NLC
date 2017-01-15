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
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2015 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 1q9b 20-August-2015
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/


#ifndef HEADER_NLC_ITEM_CLASS
#define HEADER_NLC_ITEM_CLASS

#include "NLCglobalDefs.h"
#include "GIAentityNodeClass.h"
#include "GIAentityConnectionClass.h"

#define NLC_ITEM_INSTANCE_ID_UNDEFINED (INT_DEFAULT_VALUE)

#define NLC_ITEM_TYPE_UNDEFINED (-1)
#define NLC_ITEM_TYPE_OBJECT (0)	//primary item type
#define NLC_ITEM_TYPE_CLASS (1)		//not used
#define NLC_ITEM_TYPE_TEMPVAR (3)
#define NLC_ITEM_TYPE_CLASS_DECLARATION_CONDITION_LIST (7)
#define NLC_ITEM_TYPE_CLASS_DECLARATION_PROPERTY_LIST (8)
#define NLC_ITEM_TYPE_FUNCTION_EXECUTION_ARGUMENT_FUNCTION (9)
#define NLC_ITEM_TYPE_FUNCTION_EXECUTION_ARGUMENT_FUNCTION_OWNER (10)
#define NLC_ITEM_TYPE_FUNCTION_EXECUTION_ARGUMENT_FUNCTION_OBJECT (11)
#define NLC_ITEM_TYPE_FUNCTION_EXECUTION_ARGUMENT_INSTANCE_OR_CLASS_LIST (12)	//not used
#define NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION (13)
#define NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION_OWNER (14)
#define NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION_OBJECT (15)
#define NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_INSTANCE_OR_CLASS_LIST (16)	//this has not yet been implemented but needs to be
#ifdef NLC_INTERPRET_ACTION_PROPERTIES_AND_CONDITIONS_AS_FUNCTION_ARGUMENTS
	#define NLC_ITEM_TYPE_FUNCTION_DECLARATION_ARGUMENT_CONDITION (4)
	#define NLC_ITEM_TYPE_FUNCTION_DECLARATION_ARGUMENT_PROPERTY (5)
#endif
#define NLC_ITEM_TYPE_NEGATIVE (21)
#define NLC_ITEM_TYPE_VARIABLE (22)

#define NLC_CLASS_NAME_APPEND "Class"
#define NLC_FUNCTION_NAME_APPEND "Function"

#define NLC_SUBSTANCE_CONCEPT_CLASS_PREPEND "With"
#define NLC_SUBSTANCE_CONCEPT_CLASS_CONDITION "Condition"
#define NLC_SUBSTANCE_CONCEPT_CLASS_PROPERTY "Property"

#define NLC_ITEM_TYPE_CONDITIONLISTCONDITIONPARAMETERINVERTACOMMAS CHAR_INVERTED_COMMAS

#define NLC_SUPPORT_INPUT_FUNCTION_LISTS_ACTION_SUBJECT_INSTANCE_REPLACEMENT_NAME "this"
#define NLC_SUPPORT_INPUT_FUNCTION_LISTS_ACTION_SUBJECT_CLASS_REPLACEMENT_NAME "thisClassYetToCodeThis"

class NLCitem
{
public:

	NLCitem(void);
	NLCitem(GIAentityNode* entity, int newItemType);
	NLCitem(string newName, int newItemType);
	NLCitem(NLCitem* newItem);
	~NLCitem(void);

	int itemType;
	string className;	//eg dogClass
	string instanceName;	//eg dog1
	string functionName;	//eg dogFunction
	#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS
	bool functionArgumentCertified;
	bool functionArgumentPassCastRequired;
	string functionArgumentPassCastClassName;	//used to map function arguments of referenced functions to implicitly defined function arguments (based on function definition content)
	#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
	string functionArgumentExecutionEntityName;
	#endif
	//bool formalFunctionArgumentCorrespondsToActionSubjectUseThisAlias;
	#endif
	vector<string> context;	//item context

	string className2;	//used for NLC_ITEM_TYPE_FUNCTION_ARGUMENT_CONDITION/NLC_ITEM_TYPE_CLASS_DECLARATION_CONDITION_LIST only
	string instanceName2;	//used for NLC_ITEM_TYPE_FUNCTION_ARGUMENT_CONDITION/NLC_ITEM_TYPE_CLASS_DECLARATION_CONDITION_LIST only

	bool negative;
	#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS_ADVANCED
	int conjunctionType;
	#endif
	
	string name;	//added 1h1d 24-July-2014 for NLC_ITEM_TYPE_VARIABLE
	string genericObjectName;	//added 1i7a	//NB name could be co-opted for this purpose (ie instead of using genericObjectName)
};


string generateClassName(GIAentityNode* entity);
	string generateClassName(string entityName);
string generateFunctionName(GIAentityNode* entity);
	string generateFunctionName(string entityName);
string generateInstanceName(GIAentityNode* entity);

string generateTypeName(string entityName);

//string generateItemName(GIAentityNode* entity, int itemType);

string removeClassTextFromClassDefinitionName(string className);

#endif
