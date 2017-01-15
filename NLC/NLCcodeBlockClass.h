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
 * File Name: NLCcodeBlockClass.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2014 Baxter AI (baxterai.com)
 * Project: Natural Language Programming Interface (compiler)
 * Project Version: 1h3f 28-July-2014
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/


#ifndef HEADER_NLC_CODEBLOCK_CLASS
#define HEADER_NLC_CODEBLOCK_CLASS

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
#include "NLCitemClass.h"
#include "GIAglobalDefs.h"
#include "GIAentityNodeClass.h"
#include "GIAentityConnectionClass.h"

#define NLC_CODEBLOCK_TYPE_UNDEFINED (-1)
//statements:
#define NLC_CODEBLOCK_TYPE_EXECUTE_FUNCTION (1)				//context1.param1(context.param2); 	[param1 = function, context1 = subject, param2 = object]
#define NLC_CODEBLOCK_TYPE_ADD_NEW_PROPERTY (3)				//context1->param1->param2PropertyList.push_back(param2);		//OLD2: context1.param1.param2PropertyList.addProperty(context2.param2);
#define NLC_CODEBLOCK_TYPE_ADD_NEW_CONDITION (4)			//context1->param1->param2param3ConditionList.insert(param2, param3);	//OLD2: context1.param1.param3ConditionList.addCondition(context3.param3, param2);
#define NLC_CODEBLOCK_TYPE_DECLARE_AND_INITIALISE_VARIABLE (5)
#define NLC_CODEBLOCK_TYPE_DECLARE_NEW_VARIABLE (6)
#define NLC_CODEBLOCK_TYPE_ADD_PROPERTY (7)				//context1->param1->param2PropertyList.push_back(param2);
#define NLC_CODEBLOCK_TYPE_ADD_CONDITION (8)				//context1->param1->param2param3ConditionList.insert(param2, param3);
#define NLC_CODEBLOCK_TYPE_ADD_NEW_PROPERTY_TO_LOCAL_LIST (9)
//#define NLC_CODEBLOCK_TYPE_CREATE_NEW_LOCAL_LIST_VARIABLE (9)
#define NLC_CODEBLOCK_TYPE_ADD_PROPERTY_TO_LOCAL_LIST (10)		//param1instancePropertyList.push_back(param2);
#define NLC_CODEBLOCK_TYPE_ADD_PROPERTY (11)
#define NLC_CODEBLOCK_TYPE_ADD_CONDITION (13)
#define NLC_CODEBLOCK_TYPE_DECLARE_NEW_LOCAL_LIST_VARIABLE (14)
#define NLC_CODEBLOCK_TYPE_DECLARE_NEW_BOOL_VARIABLE_INITIALISE_TRUE (15)
#define NLC_CODEBLOCK_TYPE_DECLARE_NEW_BOOL_VARIABLE_INITIALISE_FALSE (16)
#define NLC_CODEBLOCK_TYPE_SET_BOOL_VARIABLE_TRUE (17)
#define NLC_CODEBLOCK_TYPE_SET_BOOL_VARIABLE_FALSE (18)
#define NLC_CODEBLOCK_TYPE_DECLARE_NEW_BOOL_ARRAY_INITIALISE_TRUE (19)
#define NLC_CODEBLOCK_TYPE_DECLARE_NEW_BOOL_ARRAY_INITIALISE_FALSE (20)
#define NLC_CODEBLOCK_TYPE_DEBUG (21)
#ifdef NLC_TRANSLATE_NEGATIVE_PROPERTIES_AND_CONDITIONS
	#define NLC_CODEBLOCK_TYPE_REMOVE_PROPERTIES (22)
	#define NLC_CODEBLOCK_TYPE_REMOVE_PROPERTIES_FROM_LOCAL_LIST (23)
	#define NLC_CODEBLOCK_TYPE_REMOVE_CONDITIONS (24)
#endif
#ifdef NLC_PREPROCESSOR_MATH
	#define NLC_CODEBLOCK_TYPE_MATHTEXT_LINE (25)
#endif
#define NLC_CODEBLOCK_TYPE_DECLARE_NEW_INT_VARIABLE (26)
#define NLC_CODEBLOCK_TYPE_INCREMENT_INT_VARIABLE (27)

//containers:
#define NLC_CODEBLOCK_TYPE_FOR_PROPERTY_LIST (30)		//forall(context1.param1PropertyList){
#define NLC_CODEBLOCK_TYPE_FOR_PROPERTY_LIST_LOCAL (31)	//forall(param1instance){
#define NLC_CODEBLOCK_TYPE_FOR_CONDITION_LIST (32)		//forall(context1.param1param2ConditionList){
#define NLC_CODEBLOCK_TYPE_FOR_INTEGER (33)
#define NLC_CODEBLOCK_TYPE_NEW_FUNCTION (34)			//main(){
#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
#ifndef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS
	#define NLC_CODEBLOCK_TYPE_IF_HAS_PROPERTY (35)			//if(!(context1->param1PropertyList.empty())){			//OLD2:	if(context1.param1.param2PropertyList.findProperty(context2.param2)){		//OLD: if(context.param1->has(param2)){
	#define NLC_CODEBLOCK_TYPE_IF_HAS_CONDITION (36)		//if(!(context1->param1param2ConditionList.empty())){		//OLD2: if(context1.param1.param3ConditionList.findCondition(context3.param3, param2)){	//OLD: if(param2(context.param1, context.param3)){
	#define NLC_CODEBLOCK_TYPE_WHILE_HAS_PROPERTY (37)		//while(!(context1->param1PropertyList.empty())){
	#define NLC_CODEBLOCK_TYPE_WHILE_HAS_CONDITION (38)		//while(!(context1->param1param2ConditionList.empty())){
#endif
#endif
#define NLC_CODEBLOCK_TYPE_WHILE_LOGICAL_CONJUNCTION_OF_BOOLS (39)
#define NLC_CODEBLOCK_TYPE_ELSE (40)
#define NLC_CODEBLOCK_TYPE_IF_LOGICAL_CONJUNCTION_OF_BOOLS (41)
#define NLC_CODEBLOCK_TYPE_ELSE_IF_LOGICAL_CONJUNCTION_OF_BOOLS (42)
#ifdef NLC_PREPROCESSOR_MATH
	#define NLC_CODEBLOCK_TYPE_MATHTEXT_WITH_LOGICAL_OPERATOR (43)
#endif
#define NLC_CODEBLOCK_TYPE_CONTAINERS (NLC_CODEBLOCK_TYPE_FOR_PROPERTY_LIST)


/*
//#define NLC_CODEBLOCK_TYPE_IF_IS_ACTION_SUBJECT (10)
//#define NLC_CODEBLOCK_TYPE_IF_IS_ACTION_OBJECT (11)
#define NLC_CODEBLOCK_TYPE_IF_HAS_CONDITION (12)
#define NLC_CODEBLOCK_TYPE_IF_HAS_PROPERTY (13)
//#define NLC_CODEBLOCK_TYPE_IF_IS_PROPERTY (14)
//#define NLC_CODEBLOCK_TYPE_IF_HAS_DEFINITION (15)
//#define NLC_CODEBLOCK_TYPE_IF_IS_DEFINITION (16)
static bool codeBlockTypeIfStatementArrayUseVectorEntityConnection[GIA_ENTITY_NUMBER_OF_VECTOR_CONNECTION_TYPES] = {true, true, true, true, true, true, true, true, true, true, true, false, false, false};
static int codeBlockTypeIfStatementArray[GIA_ENTITY_NUMBER_OF_VECTOR_CONNECTION_TYPES] = {NLC_CODEBLOCK_TYPE_IF_IS_ACTION_SUBJECT, NLC_CODEBLOCK_TYPE_IF_IS_ACTION_OBJECT, NLC_CODEBLOCK_TYPE_IF_HAS_CONDITION, NLC_CODEBLOCK_TYPE_UNDEFINED, NLC_CODEBLOCK_TYPE_IF_HAS_PROPERTY, NLC_CODEBLOCK_TYPE_IF_IS_PROPERTY, NLC_CODEBLOCK_TYPE_IF_HAS_DEFINITION, NLC_CODEBLOCK_TYPE_IF_IS_DEFINITION, NLC_CODEBLOCK_TYPE_UNDEFINED, NLC_CODEBLOCK_TYPE_UNDEFINED, NLC_CODEBLOCK_TYPE_UNDEFINED, NLC_CODEBLOCK_TYPE_UNDEFINED, NLC_CODEBLOCK_TYPE_UNDEFINED, NLC_CODEBLOCK_TYPE_UNDEFINED};
*/

//shared with GIAtranslatorDefineReferencing.cpp

class NLClogicalConditionConjunctionVariables
{
public:

	NLClogicalConditionConjunctionVariables(void);
	~NLClogicalConditionConjunctionVariables(void);

	int logicalOperation;
	//#ifndef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS
	bool negative;
	//#endif
	#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS
	int logicalConditionConjunctionIndex;
	GIAentityNode * primaryEntityInLogicalConditionConjunctionSubset;
	GIAentityNode * foundLogicalConditionConjunction;
	#endif
	#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
	bool onlyGenerateContextBlocksIfConnectionsParsedForNLC;
	#endif
};

#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS
class NLClogicalConditionConjunction
{
public:

	NLClogicalConditionConjunction(void);
	~NLClogicalConditionConjunction(void);

	int conjunctionType;
	bool negative;
};
#endif

class NLCcodeblock
{
public:

	NLCcodeblock(void);
	~NLCcodeblock(void);

	int codeBlockType;
	vector<NLCitem*> parameters;

	/*
	//used by language specific code generator (eg C++, java);
	string codeBlockName; 	//eg "for"
	string openingText;	//eg "for(...){"
	string closingText; 	//eg "}";
	*/

	NLCcodeblock * lowerLevel;
	NLCcodeblock * next;
};

NLCcodeblock * createCodeBlockExecute(NLCcodeblock * currentCodeBlockInTree, NLCitem * functionItem, NLCitem* objectItem);
NLCcodeblock * createCodeBlockExecute(NLCcodeblock * currentCodeBlockInTree, NLCitem * functionItem);
NLCcodeblock * createCodeBlockAddNewProperty(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* propertyEntity, int sentenceIndex, bool copyNewItemsToLocalList);
	NLCcodeblock * createCodeBlockAddNewPropertyToLocalList(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* propertyEntity);
	NLCcodeblock * createCodeBlockAddPropertyToLocalList(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* propertyEntity);
	NLCcodeblock * createCodeBlockAddProperty(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* propertyEntity, int sentenceIndex);
NLCcodeblock * createCodeBlockAddNewCondition(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* conditionEntity, int sentenceIndex, bool copyNewItemsToLocalList);
	NLCcodeblock * createCodeBlockAddCondition(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* conditionEntity, int sentenceIndex);
NLCcodeblock * createCodeBlocksCreateNewLocalListVariable(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* entity);
NLCcodeblock * createCodeBlocksDeclareNewLocalListVariable(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* entity);

NLCcodeblock * createCodeBlockForPropertyList(NLCcodeblock * currentCodeBlockInTree, NLCitem * item);
NLCcodeblock * createCodeBlockForPropertyListLocal(NLCcodeblock * currentCodeBlockInTree, NLCitem * item);
NLCcodeblock * createCodeBlockForConditionList(NLCcodeblock * currentCodeBlockInTree, NLCitem * item, NLCitem * objectItem);
#ifdef NLC_SUPPORT_QUANTITIES
NLCcodeblock * createCodeBlockForInteger(NLCcodeblock * currentCodeBlockInTree, string numberIterationsOrVariable);
#endif
NLCcodeblock * createCodeBlockNewFunction(NLCcodeblock * currentCodeBlockInTree, string NLCfunctionName, vector<GIAentityNode*> * entityNodesActiveListComplete);
	NLCcodeblock * createCodeBlockDeclareAndInitialiseVariableForActionSubject(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* functionOwner);
	NLCcodeblock * createCodeBlocksAddVariableToNewList(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* entity);
	#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS
	void generateLocalFunctionArgumentsBasedOnImplicitDeclarations(vector<GIAentityNode*> * entityNodesActiveListComplete, vector<NLCitem*> * parameters);
		bool assumedToAlreadyHaveBeenDeclared(GIAentityNode* entity);
	#endif

NLCcodeblock * createCodeBlock(NLCcodeblock * currentCodeBlockInTree, int codeBlockType);
NLCcodeblock * createLowerLevel(NLCcodeblock * currentCodeBlockInTree);

bool getEntityContext(GIAentityNode * entity, vector<string> * context, bool includePresentObject, int sentenceIndex, bool markSameSentenceParentsAsParsed);

bool checkSentenceIndexParsingCodeBlocks(GIAentityNode * entity, GIAentityConnection * connection, int sentenceIndex, bool checkIfEntityHasBeenParsedForNLCcodeBlocks);
	bool checkSentenceIndexParsingCodeBlocks(GIAentityNode * entity, int sentenceIndex, bool checkIfEntityHasBeenParsedForNLCcodeBlocks);

bool checkDuplicateProperty(GIAentityNode * propertyEntity, GIAentityNode * childActionEntity);
bool checkDuplicateCondition(GIAentityNode * conditionEntity, GIAentityNode * childActionEntity);

#ifdef NLC_SUPPORT_INPUT_FILE_LISTS
string parseFunctionNameFromNLCfunctionName(string NLCfunctionName);
void parseFunctionNameFromNLCfunctionName(string NLCfunctionName, string * functionName, string * functionOwnerName, bool * foundFunctionOwnerClass);
void parseFunctionNameFromNLCfunctionName(string NLCfunctionName, string * functionName, string * functionOwnerName, bool * foundFunctionOwnerClass, string * functionObjectName, bool * foundFunctionObjectClass);
#endif

#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS
NLCcodeblock * createCodeBlockElse(NLCcodeblock * currentCodeBlockInTree);
NLCcodeblock * createCodeBlockLogicalConditionConjunctionOfBools(NLCcodeblock * currentCodeBlockInTree, int logicalOperation, NLClogicalConditionConjunction * logicalConditionConjunctionArray, int logicalConditionConjunctionIndexMax, int logicalConditionLevel, int logicalConditionCase, bool elseIfDetected);
string generateLogicalConditionConjunctionBooleanName(int logicalConditionLevel, int logicalConditionCase, int logicalOperation);
string generateLogicalConditionConjunctionBooleanName(int logicalConditionLevel, int logicalConditionCase, int logicalConditionConjunctionIndex, int logicalOperation);
NLCcodeblock * createCodeBlockDeclareNewBoolArray(NLCcodeblock * currentCodeBlockInTree, string boolArrayName, bool value);
#else
NLCcodeblock * createCodeBlockIfHasProperty(NLCcodeblock * currentCodeBlockInTree, NLCitem * itemProperty, bool negative);
NLCcodeblock * createCodeBlockIfHasCondition(NLCcodeblock * currentCodeBlockInTree, NLCitem * itemCondition, NLCitem * itemConditionObject, bool negative);
NLCcodeblock * createCodeBlockWhileHasProperty(NLCcodeblock * currentCodeBlockInTree, NLCitem * itemProperty, bool negative);
NLCcodeblock * createCodeBlockWhileHasCondition(NLCcodeblock * currentCodeBlockInTree, NLCitem * itemCondition, NLCitem * itemConditionObject, bool negative);
#endif
#endif
NLCcodeblock * createCodeBlockWhileHasBool(NLCcodeblock * currentCodeBlockInTree, string whileLogicalConditionConjunctionBooleanName);
string generateWhileLogicalConditionConjunctionBooleanName(int logicalConditionLevel);
NLCcodeblock * createCodeBlockDeclareNewBoolVar(NLCcodeblock * currentCodeBlockInTree, string boolVariableName, bool value);
NLCcodeblock * createCodeBlockSetBoolVar(NLCcodeblock * currentCodeBlockInTree, string boolVariableName, bool value);


NLCcodeblock * createCodeBlockDebug(NLCcodeblock * currentCodeBlockInTree, string warning);

#ifdef NLC_TRANSLATE_NEGATIVE_PROPERTIES_AND_CONDITIONS
NLCcodeblock * createCodeBlockRemoveProperties(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* propertyEntity);
NLCcodeblock * createCodeBlockRemovePropertiesFromLocalList(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* entity);
NLCcodeblock * createCodeBlockRemoveConditions(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* conditionEntity);
#endif

#ifdef NLC_PREPROCESSOR_MATH
NLCcodeblock * createCodeBlockMathTextLine(NLCcodeblock * currentCodeBlockInTree, string mathText);
NLCcodeblock * createCodeBlockMathTextWithLogicalOperator(NLCcodeblock * currentCodeBlockInTree, string mathText);
#endif
NLCcodeblock * createCodeBlockDeclareNewIntVar(NLCcodeblock * currentCodeBlockInTree, string intVariableName, int value);
NLCcodeblock * createCodeBlockIncrementIntVar(NLCcodeblock * currentCodeBlockInTree, string intVariableName);

void clearCodeBlock(NLCcodeblock * codeBlock);

#endif
