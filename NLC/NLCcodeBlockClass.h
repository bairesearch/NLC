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
 * Project Version: 1k7b 14-October-2014
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
#define NLC_CODEBLOCK_TYPE_ADD_NEW_ENTITY_TO_LOCAL_LIST (9)
//#define NLC_CODEBLOCK_TYPE_CREATE_NEW_LOCAL_LIST_VARIABLE (9)
#define NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_LOCAL_LIST (10)		//param1instancePropertyList.push_back(param2);
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
	#define NLC_CODEBLOCK_TYPE_REMOVE_ENTITIES_FROM_LOCAL_LIST (23)
	#define NLC_CODEBLOCK_TYPE_REMOVE_CONDITIONS (24)
#endif
#ifdef NLC_PREPROCESSOR_MATH
	#define NLC_CODEBLOCK_TYPE_MATHTEXT_LINE (25)
#endif
#define NLC_CODEBLOCK_TYPE_DECLARE_NEW_INT_VARIABLE (26)
#define NLC_CODEBLOCK_TYPE_INCREMENT_INT_VARIABLE (27)
#define NLC_CODEBLOCK_TYPE_COMMENT_SINGLE_LINE (28)
#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN
	#define NLC_CODEBLOCK_TYPE_REASSIGN_ITER (29)
#endif
#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN
	#define NLC_CODEBLOCK_TYPE_DECLARE_NEW_GENERIC_LIST_VARIABLE (30)
	#define NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST (31)
	#ifdef NLC_CATEGORIES_TEST_PLURALITY
		#define NLC_CODEBLOCK_TYPE_PRINT_WARNING (32)
		#define NLC_CODEBLOCK_TYPE_GET_BACK_GENERIC_ENTITY_LIST (33)
	#endif
	#ifdef NLC_USE_ADVANCED_REFERENCING
		#define NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST_CHECK_LAST_SENTENCE_REFERENCED_SINGULAR_EXECUTE_FUNCTION (34)
		#define NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST_CHECK_LAST_SENTENCE_REFERENCED_SINGULAR_NEW_FUNCTION (35)		
		#define NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST_CHECK_LAST_SENTENCE_REFERENCED_PLURAL_EXECUTE_FUNCTION (36)
		#define NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST_CHECK_LAST_SENTENCE_REFERENCED_PLURAL_NEW_FUNCTION (37)	
		#define NLC_CODEBLOCK_TYPE_UPDATE_LAST_SENTENCE_REFERENCED (38)	//execute for all new/undeclared/indefinite entities and accessed category items
	#endif
#endif
#ifdef NLC_GENERATE_TYPE_LISTS
	#define NLC_CODEBLOCK_TYPE_DECLARE_NEW_GENERIC_LIST_VARIABLE2 (39)
	#define NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST2 (40)
#endif
#ifdef NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT
	#define NLC_CODEBLOCK_TYPE_DECLARE_CONTEXT_LIST (41)
	#define NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_CONTEXT_LIST_NEW_FUNCTION (42)
	#define NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_CONTEXT_LIST_EXECUTE_FUNCTION (43)
	#define NLC_CODEBLOCK_TYPE_CLEAR_CONTEXT_LIST_NEW_FUNCTION (44)
	#define NLC_CODEBLOCK_TYPE_CLEAR_CONTEXT_LIST_EXECUTE_FUNCTION (45)
#endif

//containers:
#define NLC_CODEBLOCK_TYPE_FOR_PROPERTY_LIST (50)		//forall(context1.param1PropertyList){
#define NLC_CODEBLOCK_TYPE_FOR_LOCAL_LIST (51)	//forall(param1instance){
#define NLC_CODEBLOCK_TYPE_FOR_CONDITION_LIST (52)		//forall(context1.param1param2ConditionList){
#define NLC_CODEBLOCK_TYPE_FOR_INTEGER (53)
#define NLC_CODEBLOCK_TYPE_NEW_FUNCTION (54)			//main(){
#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
#ifndef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS
	#define NLC_CODEBLOCK_TYPE_IF_HAS_PROPERTY (55)			//if(!(context1->param1PropertyList.empty())){			//OLD2:	if(context1.param1.param2PropertyList.findProperty(context2.param2)){		//OLD: if(context.param1->has(param2)){
	#define NLC_CODEBLOCK_TYPE_IF_HAS_CONDITION (56)		//if(!(context1->param1param2ConditionList.empty())){		//OLD2: if(context1.param1.param3ConditionList.findCondition(context3.param3, param2)){	//OLD: if(param2(context.param1, context.param3)){
	#define NLC_CODEBLOCK_TYPE_WHILE_HAS_PROPERTY (57)		//while(!(context1->param1PropertyList.empty())){
	#define NLC_CODEBLOCK_TYPE_WHILE_HAS_CONDITION (58)		//while(!(context1->param1param2ConditionList.empty())){
#endif
#endif
#define NLC_CODEBLOCK_TYPE_WHILE_LOGICAL_CONJUNCTION_OF_BOOLS (59)
#define NLC_CODEBLOCK_TYPE_ELSE (60)
#define NLC_CODEBLOCK_TYPE_IF_LOGICAL_CONJUNCTION_OF_BOOLS (61)
#define NLC_CODEBLOCK_TYPE_ELSE_IF_LOGICAL_CONJUNCTION_OF_BOOLS (62)
#ifdef NLC_PREPROCESSOR_MATH
	#define NLC_CODEBLOCK_TYPE_MATHTEXT_WITH_LOGICAL_OPERATOR (63)
#endif
#define NLC_CODEBLOCK_TYPE_WHILE (64)
#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN
	#define NLC_CODEBLOCK_TYPE_FOR_GENERIC_LIST (65)
	#ifdef NLC_CATEGORIES_TEST_PLURALITY
		#define NLC_CODEBLOCK_TYPE_IF_HAS_GREATER_THAN_NUM_GENERIC_ENTITY (66)
	#endif
	#ifdef NLC_USE_ADVANCED_REFERENCING
		#define NLC_CODEBLOCK_TYPE_IF_HAS_GENERIC_ENTITY (67)
	#endif
#endif
#ifdef NLC_GENERATE_TYPE_LISTS
	#define NLC_CODEBLOCK_TYPE_FOR_GENERIC_LIST2 (68)
#endif
#ifdef NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY
	#define NLC_CODEBLOCK_TYPE_IF_HAS_GREATER_THAN_OR_EQUAL_TO_NUM_GENERIC_ENTITY (69)
	#ifdef NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY_CHILDREN
		#define NLC_CODEBLOCK_TYPE_TEST_INT_VARIABLE_GREATER_THAN_OR_EQUAL_TO_NUM (70)
		//#define NLC_CODEBLOCK_TYPE_IF_HAS_MORE_THAN_NUM_PROPERTY (71)
		//#define NLC_CODEBLOCK_TYPE_IF_HAS_MORE_THAN_NUM_CONDITION (72)
	#endif
#endif
#ifdef NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT
	#define NLC_CODEBLOCK_TYPE_CONTEXT_BLOCK (73)
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

class NLCgenerateContextBlocksVariables
{
public:

	NLCgenerateContextBlocksVariables(void);
	~NLCgenerateContextBlocksVariables(void);

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
	bool generateContextBlocksIfSameReferenceSet;	//added 1i3d
	#endif
	#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
	bool negativeDetectedInContextBlocks;
	#endif
	#ifdef NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY
	bool testNumerosity;
	int childQuantity;
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
	
	#ifdef NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT
	bool isLogicalCondition;
	int contextLevel;
	#endif
};

int getCurrentLogicalConditionLevel();
void setCurrentLogicalConditionLevel(int value);

NLCcodeblock * createCodeBlockExecute(NLCcodeblock * currentCodeBlockInTree, NLCitem * functionItem, NLCitem* objectItem);
NLCcodeblock * createCodeBlockExecute(NLCcodeblock * currentCodeBlockInTree, NLCitem * functionItem);
NLCcodeblock * createCodeBlockCreateNewProperty(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* propertyEntity, int sentenceIndex, bool copyNewItemsToLocalList);
	NLCcodeblock * createCodeBlockAddNewProperty(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* propertyEntity, int sentenceIndex, bool copyNewItemsToLocalList);
		NLCcodeblock * createCodeBlockAddEntityToLocalList(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* propertyEntity);
		NLCcodeblock * createCodeBlockAddProperty(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* propertyEntity, int sentenceIndex);

NLCcodeblock * createCodeBlockCreateNewCondition(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* conditionEntity, int sentenceIndex, bool copyNewItemsToLocalList);
	NLCcodeblock * createCodeBlockAddNewCondition(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* conditionEntity, int sentenceIndex, bool copyNewItemsToLocalList);
		NLCcodeblock * createCodeBlockAddCondition(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* conditionEntity, int sentenceIndex);

NLCcodeblock * createCodeBlocksCreateNewLocalListVariable(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* entity, int sentenceIndex);
	NLCcodeblock * createCodeBlocksDeclareNewLocalListVariableIfNecessary(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* entity);
		NLCcodeblock * createCodeBlocksDeclareNewLocalListVariable(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* entity);
	NLCcodeblock * createCodeBlockAddNewEntityToLocalList(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* entity, int sentenceIndex);

NLCcodeblock * createCodeBlockForPropertyList(NLCcodeblock * currentCodeBlockInTree, NLCitem * item);
NLCcodeblock * createCodeBlockForLocalList(NLCcodeblock * currentCodeBlockInTree, NLCitem * item);
NLCcodeblock * createCodeBlockForConditionList(NLCcodeblock * currentCodeBlockInTree, NLCitem * item, NLCitem * objectItem);
#ifdef NLC_SUPPORT_QUANTITIES
NLCcodeblock * createCodeBlockForInteger(NLCcodeblock * currentCodeBlockInTree, string numberIterationsOrVariable);
#endif
NLCcodeblock * createCodeBlockNewFunction(NLCcodeblock * currentCodeBlockInTree, string NLCfunctionName, vector<GIAentityNode*> * entityNodesActiveListComplete);
	NLCcodeblock * createCodeBlockDeclareAndInitialiseVariableForActionSubject(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* functionOwner);
	NLCcodeblock * createCodeBlocksAddVariableToNewList(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* entity);
	#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS
	void generateLocalFunctionArgumentsBasedOnImplicitDeclarations(vector<GIAentityNode*> * entityNodesActiveListComplete, vector<NLCitem*> * parameters);
		bool generateLocalFunctionArgumentsBasedOnImplicitDeclarationsValidClassChecks(GIAentityNode* entityNode);
	#endif
	
bool assumedToAlreadyHaveBeenDeclared(GIAentityNode* entity);

NLCcodeblock * createCodeBlock(NLCcodeblock * currentCodeBlockInTree, int codeBlockType);
NLCcodeblock * createLowerLevel(NLCcodeblock * currentCodeBlockInTree);

bool getEntityContext(GIAentityNode * entity, vector<string> * context, bool includePresentObject, int sentenceIndex, bool markSameSentenceParentsAsParsed);

/*
#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN
bool checkSentenceIndexParsingCodeBlocks(GIAentityNode * entity, GIAentityConnection * connection, int sentenceIndex, bool checkIfEntityHasBeenParsedForNLCcodeBlocks, bool checkSameSentenceConnection);
#endif
*/	
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
NLCcodeblock * createCodeBlockElse(NLCcodeblock * currentCodeBlockInTree);
NLCcodeblock * createCodeBlockWhileHasBool(NLCcodeblock * currentCodeBlockInTree, string whileLogicalConditionConjunctionBooleanName);
string generateWhileLogicalConditionConjunctionBooleanName(int logicalConditionLevel);
NLCcodeblock * createCodeBlockDeclareNewBoolVar(NLCcodeblock * currentCodeBlockInTree, string boolVariableName, bool value);
NLCcodeblock * createCodeBlockSetBoolVar(NLCcodeblock * currentCodeBlockInTree, string boolVariableName, bool value);


NLCcodeblock * createCodeBlockDebug(NLCcodeblock * currentCodeBlockInTree, string warning);

#ifdef NLC_TRANSLATE_NEGATIVE_PROPERTIES_AND_CONDITIONS
NLCcodeblock * createCodeBlockRemoveProperties(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* propertyEntity);
NLCcodeblock * createCodeBlockRemoveEntitiesFromLocalList(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* entity);
NLCcodeblock * createCodeBlockRemoveConditions(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* conditionEntity);
#endif

#ifdef NLC_PREPROCESSOR_MATH
NLCcodeblock * createCodeBlockMathTextLine(NLCcodeblock * currentCodeBlockInTree, string mathText);
NLCcodeblock * createCodeBlockMathTextWithLogicalOperator(NLCcodeblock * currentCodeBlockInTree, string mathText);
#endif
NLCcodeblock * createCodeBlockDeclareNewIntVar(NLCcodeblock * currentCodeBlockInTree, string intVariableName, int value);
NLCcodeblock * createCodeBlockIncrementIntVar(NLCcodeblock * currentCodeBlockInTree, string intVariableName);

NLCcodeblock * createCodeBlockCommentSingleLine(NLCcodeblock * currentCodeBlockInTree, string comment);


#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN
NLCcodeblock * createCodeBlockReassignIter(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* entity, string genericListAppendName);
NLCcodeblock * createCodeBlocksDeclareNewCategoryListVariable(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* entity, string genericListAppendName);
NLCcodeblock * createCodeBlockAddEntityToCategoryList(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* propertyEntity, string genericListAppendName);
NLCcodeblock * createCodeBlockForCategoryList(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* entity, string genericListAppendName);
#ifdef NLC_CATEGORIES_TEST_PLURALITY
NLCcodeblock * createCodeBlockGetBackCategoryEntityList(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* entity, string genericListAppendName);
NLCcodeblock * createCodeBlockIfHasGreaterThanNumCategoryItem(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* entity, string genericListAppendName, int value);
#endif
#ifdef NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY
NLCcodeblock * createCodeBlockIfHasGreaterThanOrEqualToNumCategoryItem(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* entity, string genericListAppendName, int value);
#endif
#ifdef NLC_USE_ADVANCED_REFERENCING
NLCcodeblock * createCodeBlockIfHasCategoryItem(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* entity, bool negative, string genericListAppendName);
NLCcodeblock * createCodeBlockAddEntityToCategoryListCheckLastSentenceReferencedSingularExecuteFunction(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* propertyEntity, string genericListAppendName);
NLCcodeblock * createCodeBlockAddEntityToCategoryListCheckLastSentenceReferencedSingularNewFunction(NLCcodeblock * currentCodeBlockInTree, string genericListAppendName);
NLCcodeblock * createCodeBlockAddEntityToCategoryListCheckLastSentenceReferencedPluralExecuteFunction(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* propertyEntity, string genericListAppendName);
NLCcodeblock * createCodeBlockAddEntityToCategoryListCheckLastSentenceReferencedPluralNewFunction(NLCcodeblock * currentCodeBlockInTree, string genericListAppendName);
#endif
	NLCcodeblock * createCodeBlocksDeclareNewGenericListVariable(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* entity, string genericObjectName, string genericListAppendName);
	NLCcodeblock * createCodeBlockAddEntityToGenericList(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* entity, string genericObjectName, string genericListAppendName, GIAentityNode* propertyEntity);
	NLCcodeblock * createCodeBlockForGenericList(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* entity, string genericObjectName, string genericListAppendName);
	#ifdef NLC_CATEGORIES_TEST_PLURALITY
	NLCcodeblock * createCodeBlockGetBackGenericEntityList(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* entity, string genericObjectName, string genericListAppendName);
	NLCcodeblock * createCodeBlockIfHasGreaterThanNumGenericEntity(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* entity, string genericObjectName, string genericListAppendName, int value);
	NLCcodeblock * createCodeBlockPrintWarning(NLCcodeblock * currentCodeBlockInTree, string warning);
	#endif
	#ifdef NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY
	NLCcodeblock * createCodeBlockIfHasGreaterThanOrEqualToNumGenericEntity(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* entity, string genericObjectName, string genericListAppendName, int value);
	#endif
	#ifdef NLC_USE_ADVANCED_REFERENCING
	NLCcodeblock * createCodeBlockIfHasGenericEntity(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* entity, string genericObjectName, string genericListAppendName, bool negative);
	NLCcodeblock * createCodeBlockAddEntityToGenericListCheckLastSentenceReferencedSingularExecuteFunction(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* entity, string genericObjectName, string genericListAppendName, GIAentityNode* propertyEntity);
	NLCcodeblock * createCodeBlockAddEntityToGenericListCheckLastSentenceReferencedSingularNewFunction(NLCcodeblock * currentCodeBlockInTree, string genericListAppendName);
	NLCcodeblock * createCodeBlockAddEntityToGenericListCheckLastSentenceReferencedPluralExecuteFunction(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* entity, string genericObjectName, string genericListAppendName, GIAentityNode* propertyEntity);
	NLCcodeblock * createCodeBlockAddEntityToGenericListCheckLastSentenceReferencedPluralNewFunction(NLCcodeblock * currentCodeBlockInTree, string genericListAppendName);
	NLCcodeblock * createCodeBlockUpdateLastSentenceReferenced(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* entity, int sentenceIndex);
	#endif
#endif

#ifdef NLC_GENERATE_TYPE_LISTS
NLCcodeblock * createCodeBlocksDeclareNewTypeListVariable(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* entity);
NLCcodeblock * createCodeBlockAddInstanceListToTypeList(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* propertyEntity);
NLCcodeblock * createCodeBlockForPropertyTypeClass(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* entity);
	NLCcodeblock * createCodeBlocksDeclareNewGenericListVariable2(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* entity, string genericObjectName, string genericListAppendName);
	NLCcodeblock * createCodeBlockAddEntityToGenericList2(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* entity, string genericObjectName, string genericListAppendName, GIAentityNode* propertyEntity, string genericListAppendName2);
	NLCcodeblock * createCodeBlockForGenericList2(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* entity, string genericObjectName, string genericListAppendName);
#endif

#ifdef NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY_CHILDREN
NLCcodeblock * createCodeBlockIfIntVariableGreaterThanOrEqualToNum(NLCcodeblock * currentCodeBlockInTree, string intVariableName, int value);
/*
NLCcodeblock * createCodeBlockIfHasMoreThanNumProperty(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* propertyEntity, int value, string parentInstanceName);
NLCcodeblock * createCodeBlockIfHasMoreThanNumCondition(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* conditionEntity, GIAentityNode* conditionObject, int value, string parentInstanceName);
*/
#endif

#ifdef NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT
NLCcodeblock * createCodeBlocksDeclareContextList(NLCcodeblock * currentCodeBlockInTree, int contextLevel);
NLCcodeblock * addEntityToContextLevelListNewFunction(NLCcodeblock * currentCodeBlockInTree);
NLCcodeblock * createCodeBlocksClearContextListNewFunction(NLCcodeblock * currentCodeBlockInTree);
NLCcodeblock * addEntityToContextLevelListExecuteFunction(NLCcodeblock * currentCodeBlockInTree, int contextLevel, GIAentityNode* entity, int sentenceIndex);
NLCcodeblock * createCodeBlocksClearContextListVariableExecuteFunction(NLCcodeblock * currentCodeBlockInTree, int contextLevel);
NLCcodeblock * createCodeBlocksCreateContextBlock(NLCcodeblock * currentCodeBlockInTree);
#endif

void clearCodeBlock(NLCcodeblock * codeBlock);

#ifdef NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY_CHILDREN
string generateCategoryListPropertyCountVariableName(GIAentityNode * entity);
#endif

#endif
