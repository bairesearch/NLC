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
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2015 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 1q8b 20-August-2015
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/


#ifndef HEADER_NLC_CODEBLOCK_CLASS
#define HEADER_NLC_CODEBLOCK_CLASS

#include "NLCglobalDefs.h"
#include "NLCitemClass.h"
#include "GIAentityNodeClass.h"
#include "GIAentityConnectionClass.h"
//#ifdef NLC_USE_PREPROCESSOR
#include "NLCpreprocessorSentenceClass.h"	//required for findIndefiniteEntityCorrespondingToDefiniteEntityInSameContext()
//#endif

#define NLC_CODEBLOCK_TYPE_UNDEFINED (-1)

//statements:
#define NLC_CODEBLOCK_TYPE_EXECUTE_FUNCTION (1)				//context1.param1(context.param2); 	[param1 = function, context1 = subject, param2 = object]
#define NLC_CODEBLOCK_TYPE_ADD_NEW_PROPERTY (3)				//context1->param1->param2PropertyList.push_back(param2);		//OLD2: context1.param1.param2PropertyList.addProperty(context2.param2);
#define NLC_CODEBLOCK_TYPE_ADD_NEW_CONDITION (4)			//context1->param1->param2param3ConditionList.insert(param2, param3);	//OLD2: context1.param1.param3ConditionList.addCondition(context3.param3, param2);
#define NLC_CODEBLOCK_TYPE_DECLARE_AND_INITIALISE_VARIABLE (5)
#define NLC_CODEBLOCK_TYPE_DECLARE_NEW_VARIABLE (6)
#define NLC_CODEBLOCK_TYPE_ADD_PROPERTY (7)				//context1->param1->param2PropertyList.push_back(param2);
#define NLC_CODEBLOCK_TYPE_ADD_CONDITION (8)				//context1->param1->param2param3ConditionList.insert(param2, param3);	//aka NLC_CODEBLOCK_TYPE_ADD_NEW_CONDITION_EXISTING_OBJECT
#define NLC_CODEBLOCK_TYPE_ADD_NEW_ENTITY_TO_LOCAL_LIST (9)
//#define NLC_CODEBLOCK_TYPE_CREATE_NEW_LOCAL_LIST_VARIABLE (9)
#define NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_LOCAL_LIST (10)		//param1instancePropertyList.push_back(param2);
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
		#define NLC_CODEBLOCK_TYPE_UPDATE_LAST_SENTENCE_REFERENCED (36)	//execute for all new/undeclared/indefinite entities and accessed category items
	#endif
#endif
#ifdef NLC_PERFORM_PLURAL_DEFINITE_REFERENCING_TESTS
	#define NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST_CHECK_LAST_SENTENCE_REFERENCED_PLURAL_EXECUTE_FUNCTION (37)
	#define NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST_CHECK_LAST_SENTENCE_REFERENCED_PLURAL_NEW_FUNCTION (38)	
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
#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS	
	#define NLC_CODEBLOCK_TYPE_CAST_VECTOR_NEW_FUNCTION (46)
	#define NLC_CODEBLOCK_TYPE_CAST_VECTOR_EXECUTE_FUNCTION (47)
#endif
#ifdef NLC_USE_ADVANCED_REFERENCING_SUPPORT_ALIASES
	#define NLC_CODEBLOCK_TYPE_ADD_ALIAS_TO_ENTITY_ALIAS_LIST (48)
	#define NLC_CODEBLOCK_TYPE_FIND_ALIAS_AND_ADD_TO_CATEGORY_LIST_NEW_FUNCTION (49)
	#define NLC_CODEBLOCK_TYPE_FIND_ALIAS_AND_ADD_TO_CATEGORY_LIST_EXECUTE_FUNCTION (50)
	#define NLC_CODEBLOCK_TYPE_FIND_ALIAS_NEW_FUNCTION (51)
#endif
#ifdef NLC_RECORD_ACTION_HISTORY
	#define NLC_CODEBLOCK_TYPE_RECORD_HISTORY_ACTION_SUBJECT (52)
	#define NLC_CODEBLOCK_TYPE_RECORD_HISTORY_ACTION_OBJECT (53)
#endif
#ifdef NLC_SUPPORT_REDEFINITIONS
	#define NLC_CODEBLOCK_TYPE_CONVERT_PARENT_TO_CHILD_CLASS (54)
#endif
#define NLC_CODEBLOCK_TYPE_DECLARE_TEMP_VARIABLE (55)			//param1class* param1 = NULL;
#define NLC_CODEBLOCK_TYPE_SET_TEMP_VARIABLE (56)			//param1 = param2;
#define NLC_CODEBLOCK_TYPE_DECLARE_TEMP_VARIABLE_AND_SET_TO_ENTITY (57)			//param1class* param1 = param2;
#ifdef NLC_SUPPORT_REDEFINITIONS
	#define NLC_CODEBLOCK_TYPE_CHECK_PARENT_CLASS_NAME_NEW_FUNCTION (58)
#endif
#ifdef NLC_USE_NON_LIBRARY_FUNCTIONS_EXTENDED
	#define NLC_CODEBLOCK_TYPE_ADD_PROPERTY_NEW_FUNCTION (59)
	#define NLC_CODEBLOCK_TYPE_ADD_CONDITION_NEW_FUNCTION (60)
#endif
#ifdef NLC_USE_LIBRARY_BASE_EXTENDED
	#define NLC_CODEBLOCK_TYPE_ADD_PROPERTY_EXECUTE_FUNCTION (61)
	#define NLC_CODEBLOCK_TYPE_ADD_CONDITION_EXECUTE_FUNCTION (62)
#endif
#ifdef NLC_TRANSLATE_NEGATIVE_PROPERTIES_AND_CONDITIONS
	//should be merged with moved in line with other cases above
	#define NLC_CODEBLOCK_TYPE_REMOVE_PROPERTY (63)
	#define NLC_CODEBLOCK_TYPE_REMOVE_CONDITION (64)
#endif
#ifdef NLC_USE_MATH_OBJECTS
	#define NLC_CODEBLOCK_TYPE_SET_MATH_VALUE (65)
	#define NLC_CODEBLOCK_TYPE_DECLARE_NEW_DECIMAL_POINTER_VARIABLE (66)
	#define NLC_CODEBLOCK_TYPE_SET_DECIMAL_POINTER_TO_ENTITY_MATH_VALUE (67)
	#ifdef NLC_MATH_OBJECTS_TEST_NULL_POINTER_MAINTAIN_CONTEXT
		#define NLC_CODEBLOCK_TYPE_TEST_DECIMAL_POINTER_VALUE (68)
	#endif
#endif

//containers:
#define NLC_CODEBLOCK_TYPE_FOR_PROPERTY_LIST (100)		//forall(context1.param1PropertyList){
#define NLC_CODEBLOCK_TYPE_FOR_LOCAL_LIST (101)	//forall(param1instance){
#define NLC_CODEBLOCK_TYPE_FOR_CONDITION_LIST (102)		//forall(context1.param1param2ConditionList){
#define NLC_CODEBLOCK_TYPE_FOR_INTEGER (103)
#define NLC_CODEBLOCK_TYPE_NEW_FUNCTION (104)			//main(){
#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
#ifndef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS_ADVANCED
	#define NLC_CODEBLOCK_TYPE_IF_HAS_PROPERTY (105)			//if(!(context1->param1PropertyList.empty())){			//OLD2:	if(context1.param1.param2PropertyList.findProperty(context2.param2)){		//OLD: if(context.param1->has(param2)){
	#define NLC_CODEBLOCK_TYPE_IF_HAS_CONDITION (106)		//if(!(context1->param1param2ConditionList.empty())){		//OLD2: if(context1.param1.param3ConditionList.findCondition(context3.param3, param2)){	//OLD: if(param2(context.param1, context.param3)){
	#define NLC_CODEBLOCK_TYPE_WHILE_HAS_PROPERTY (107)		//while(!(context1->param1PropertyList.empty())){
	#define NLC_CODEBLOCK_TYPE_WHILE_HAS_CONDITION (108)		//while(!(context1->param1param2ConditionList.empty())){
#endif
#endif
#define NLC_CODEBLOCK_TYPE_WHILE_LOGICAL_CONJUNCTION_OF_BOOLS (109)
#define NLC_CODEBLOCK_TYPE_ELSE (110)
#define NLC_CODEBLOCK_TYPE_IF_LOGICAL_CONJUNCTION_OF_BOOLS (111)
#define NLC_CODEBLOCK_TYPE_ELSE_IF_LOGICAL_CONJUNCTION_OF_BOOLS (112)
#ifdef NLC_PREPROCESSOR_MATH
	#define NLC_CODEBLOCK_TYPE_MATHTEXT_WITH_LOGICAL_OPERATOR (113)
#endif
#define NLC_CODEBLOCK_TYPE_WHILE (114)
#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN
	#define NLC_CODEBLOCK_TYPE_FOR_GENERIC_LIST (115)
	#ifdef NLC_CATEGORIES_TEST_PLURALITY
		#define NLC_CODEBLOCK_TYPE_IF_HAS_GREATER_THAN_NUM_GENERIC_ENTITY (116)
	#endif
	#ifdef NLC_USE_ADVANCED_REFERENCING
		#define NLC_CODEBLOCK_TYPE_IF_HAS_GENERIC_ENTITY (117)
	#endif
#endif
#ifdef NLC_GENERATE_TYPE_LISTS
	#define NLC_CODEBLOCK_TYPE_FOR_GENERIC_LIST2 (118)
#endif
#ifdef NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY
	#define NLC_CODEBLOCK_TYPE_IF_HAS_GREATER_THAN_OR_EQUAL_TO_NUM_GENERIC_ENTITY (119)
	#ifdef NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY_CHILDREN
		#define NLC_CODEBLOCK_TYPE_TEST_INT_VARIABLE_GREATER_THAN_OR_EQUAL_TO_NUM (120)
		//#define NLC_CODEBLOCK_TYPE_IF_HAS_MORE_THAN_NUM_PROPERTY (121)
		//#define NLC_CODEBLOCK_TYPE_IF_HAS_MORE_THAN_NUM_CONDITION (122)
	#endif
#endif
#ifdef NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT
	#define NLC_CODEBLOCK_TYPE_CONTEXT_BLOCK (123)
#endif
#ifdef NLC_RECORD_ACTION_HISTORY
	#define NLC_CODEBLOCK_TYPE_FOR_ACTION_LIST (124)
	#define NLC_CODEBLOCK_TYPE_FOR_ACTION_INCOMING_LIST (125)
	#define NLC_CODEBLOCK_TYPE_FOR_ACTION_OBJECT_LIST (126)
	#define NLC_CODEBLOCK_TYPE_FOR_ACTION_SUBJECT_LIST (127)
#endif
#ifdef NLC_NONOO
	#define NLC_CODEBLOCK_TYPE_IF_PROPERTY_NAME (128)
	#define NLC_CODEBLOCK_TYPE_IF_CONDITION_NAME (129)
	#ifdef NLC_RECORD_ACTION_HISTORY
	#define NLC_CODEBLOCK_TYPE_IF_ACTION_NAME (130)
	#endif
#endif
#ifdef NLC_USE_SUPPORT_REFERENCING_OBJECTS_IN_PLURAL_LIST_BY_NUMBER
	#define NLC_CODEBLOCK_TYPE_IN_PROPERTY_LIST (131)
	#define NLC_CODEBLOCK_TYPE_IN_LOCAL_LIST (132)
#endif
#ifdef NLC_SUPPORT_REDEFINITIONS
	#define NLC_CODEBLOCK_TYPE_CHECK_PARENT_CLASS_NAME_EXECUTE_FUNCTION1 (133)
	#define NLC_CODEBLOCK_TYPE_CHECK_PARENT_CLASS_NAME_EXECUTE_FUNCTION2 (134)
#endif
#define NLC_CODEBLOCK_TYPE_IF_TEMP_VARIABLE_EQUALS_ENTITY (135)			//if(param1 == param2){
#ifdef NLC_USE_ADVANCED_REFERENCING_SUPPORT_ALIASES
	#define NLC_CODEBLOCK_TYPE_FIND_ALIAS_EXECUTE_FUNCTION (136)
#endif
#ifdef NLC_USE_MATH_OBJECTS
	#ifndef NLC_MATH_OBJECTS_TEST_NULL_POINTER_MAINTAIN_CONTEXT
		#define NLC_CODEBLOCK_TYPE_CHECK_DECIMAL_POINTER_VALUE (137)
	#endif
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

	NLCcodeblock* lowerLevel;
	NLCcodeblock* next;
	
	#ifdef NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT
	bool isLogicalCondition;
	int contextLevel;
	#endif
};


class NLCgenerateContextBlocksVariables
{
public:

	NLCgenerateContextBlocksVariables(void);
	~NLCgenerateContextBlocksVariables(void);

	int logicalOperation;
	//#ifndef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS_ADVANCED
	bool negative;
	//#endif
	#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS_ADVANCED
	int logicalConditionConjunctionIndex;
	GIAentityNode* primaryEntityInLogicalConditionConjunctionSubset;
	GIAentityNode* foundLogicalConditionConjunction;
	#endif
	#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
	bool onlyGenerateContextBlocksIfConnectionsParsedForNLCorSameReferenceSet;
	bool generateContextBlocksIfSameReferenceSet;	//added 1i3d
	#endif
	#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
	bool negativeDetectedInContextBlocks;
	bool setCodeBlockInTreeAtBaseLevel;	//added 1k16c - for loop support
	NLCcodeblock* currentCodeBlockInTreeAtBaseLevel;	//added 1k16c - for loop support
	#endif
	#ifdef NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY
	bool testNumerosity;
	int childQuantity;
	#endif
	#ifdef NLC_FUNCTIONS_SUPPORT_PLURAL_SUBJECTS_AND_OBJECTS
	bool enterGeneratedCategoryList;
	#endif
	#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN
	bool searchSubstanceConceptsForChildren;
	#endif
	#ifdef NLC_PARSE_CONDITION_PARENTS
	bool parseConditionParents;
	#endif
	#ifdef NLC_TRANSLATOR_GENERATE_CONTEXT_BLOCKS_PARSE_PARENT_EFFICIENT
	bool parseParentEfficient;
	GIAentityNode* childEntityNotToParse;
	#endif
	bool getParentCheckLastParent;
	GIAentityNode* lastParent;
};

#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS_ADVANCED
class NLClogicalConditionConjunction
{
public:

	NLClogicalConditionConjunction(void);
	~NLClogicalConditionConjunction(void);

	int conjunctionType;
	bool negative;
};
#endif


int getCurrentLogicalConditionLevel();
void setCurrentLogicalConditionLevel(int value);

NLCcodeblock* createCodeBlockExecuteSubjectObject(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* actionEntity, GIAentityNode* subjectEntity, GIAentityNode* objectEntity);
NLCcodeblock* createCodeBlockExecuteSubject(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* actionEntity, GIAentityNode* subjectEntity);
NLCcodeblock* createCodeBlockExecuteObject(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* actionEntity, GIAentityNode* objectEntity);
NLCcodeblock* createCodeBlockExecute(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* actionEntity);
#ifdef NLC_RECORD_ACTION_HISTORY
NLCcodeblock* createCodeBlockRecordHistoryActionSubject(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* actionEntity, GIAentityNode* subjectEntity);
NLCcodeblock* createCodeBlockRecordHistoryActionObject(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* actionEntity, GIAentityNode* objectEntity);
#endif

NLCcodeblock* createCodeBlockCreateNewProperty(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* propertyEntity, int sentenceIndex, bool copyNewItemsToLocalList);
	NLCcodeblock* createCodeBlockAddNewProperty(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* propertyEntity, int sentenceIndex, bool copyNewItemsToLocalList);
		NLCcodeblock* createCodeBlockAddEntityToLocalList(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* propertyEntity);
		NLCcodeblock* createCodeBlockAddProperty(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* propertyEntity, int sentenceIndex);

NLCcodeblock* createCodeBlockCreateNewCondition(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* conditionEntity, int sentenceIndex, bool copyNewItemsToLocalList);
	NLCcodeblock* createCodeBlockAddNewCondition(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* conditionEntity, int sentenceIndex, bool copyNewItemsToLocalList);
		NLCcodeblock* createCodeBlockAddNewConditionSimple(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* conditionEntity, GIAentityNode* conditionObject);
NLCcodeblock* createCodeBlockAddCondition(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* conditionEntity, int sentenceIndex);
	NLCcodeblock* createCodeBlockAddConditionSimple(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* conditionEntity, GIAentityNode* conditionObject);

NLCcodeblock* createCodeBlocksCreateNewLocalListVariable(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, int sentenceIndex);
	NLCcodeblock* createCodeBlocksDeclareNewLocalListVariableIfNecessary(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity);
		NLCcodeblock* createCodeBlocksDeclareNewLocalListVariable(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity);
	NLCcodeblock* createCodeBlockAddNewEntityToLocalList(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, int sentenceIndex, bool addReferencingContext);

NLCcodeblock* createCodeBlockForOrInPropertyList(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, string context);
NLCcodeblock* createCodeBlockForOrInPropertyList(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity);
	NLCcodeblock* createCodeBlockForPropertyList(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, string context);
		NLCcodeblock* createCodeBlockForPropertyList(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity);
			NLCcodeblock* createCodeBlockForPropertyList(NLCcodeblock* currentCodeBlockInTree, NLCitem* item);
	#ifdef NLC_USE_SUPPORT_REFERENCING_OBJECTS_IN_PLURAL_LIST_BY_NUMBER
	NLCcodeblock* createCodeBlockInPropertyList(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, int index);
	NLCcodeblock* createCodeBlockInPropertyList(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, string context, int index);
	#endif
NLCcodeblock* createCodeBlockForOrInLocalList(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity);
	NLCcodeblock* createCodeBlockForLocalList(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity);
	#ifdef NLC_USE_SUPPORT_REFERENCING_OBJECTS_IN_PLURAL_LIST_BY_NUMBER
	NLCcodeblock* createCodeBlockInLocalList(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, int index);
	#endif
NLCcodeblock* createCodeBlockForConditionList(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* condition, GIAentityNode* conditionObject, string context);
	NLCcodeblock* createCodeBlockForConditionList(NLCcodeblock* currentCodeBlockInTree, NLCitem* item, NLCitem* objectItem);

#ifdef NLC_NONOO
NLCcodeblock* createCodeBlockIfPropertyName(NLCcodeblock* currentCodeBlockInTree, NLCitem* item);
NLCcodeblock* createCodeBlockIfConditionName(NLCcodeblock* currentCodeBlockInTree, NLCitem* item, NLCitem* objectItem);
#ifdef NLC_RECORD_ACTION_HISTORY
NLCcodeblock* createCodeBlockIfActionName(NLCcodeblock* currentCodeBlockInTree, NLCitem* item);
#endif
#endif
#ifdef NLC_RECORD_ACTION_HISTORY
NLCcodeblock* createCodeBlockForActionList(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, string context);
NLCcodeblock* createCodeBlockForActionIncomingList(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, string context);
NLCcodeblock* createCodeBlockForActionObjectList(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, string context);
NLCcodeblock* createCodeBlockForActionSubjectList(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, string context);
#endif
#ifdef NLC_SUPPORT_QUANTITIES
NLCcodeblock* createCodeBlockForInteger(NLCcodeblock* currentCodeBlockInTree, string numberIterationsOrVariable);
#endif
NLCcodeblock* createCodeBlockNewFunction(NLCcodeblock* currentCodeBlockInTree, string NLCfunctionName, vector<GIAentityNode*>* entityNodesActiveListComplete, NLCsentence* firstNLCsentenceInList);
	NLCcodeblock* createCodeBlockDeclareAndInitialiseVariableForActionSubject(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* functionOwner);
	NLCcodeblock* createCodeBlocksAddVariableToNewList(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity);
	#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS
	void generateLocalFunctionArgumentsBasedOnImplicitDeclarations(vector<GIAentityNode*>* entityNodesActiveListComplete, vector<NLCitem*>* parameters, NLCsentence* firstNLCsentenceInList);
		bool generateLocalFunctionArgumentsBasedOnImplicitDeclarationsValidClassChecks(GIAentityNode* entityNode);
		#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS_SUPPORT_LOCAL_LISTS_USE_CLASS_NAMES
		bool findIndefiniteEntityCorrespondingToDefiniteEntityInSameContext(vector<GIAentityNode*>* entityNodesActiveListComplete, GIAentityNode* definiteEntity, NLCsentence* firstNLCsentenceInList);
		#endif
	#endif
	
bool assumedToAlreadyHaveBeenDeclared(GIAentityNode* entity);
	bool isDefiniteEntity(GIAentityNode* entity);

NLCcodeblock* createCodeBlock(NLCcodeblock* currentCodeBlockInTree, int codeBlockType);
NLCcodeblock* createLowerLevel(NLCcodeblock* currentCodeBlockInTree);

bool getEntityContext(GIAentityNode* entity, vector<string>* context, bool includePresentObject, int sentenceIndex, bool markSameSentenceParentsAsParsed);

bool checkSentenceIndexParsingCodeBlocks(GIAentityNode* entity, GIAentityConnection* connection, int sentenceIndex, bool checkIfEntityHasBeenParsedForNLCcodeBlocks);
	bool checkSentenceIndexParsingCodeBlocks(GIAentityNode* entity, int sentenceIndex, bool checkIfEntityHasBeenParsedForNLCcodeBlocks);

bool checkDuplicateProperty(GIAentityNode* propertyEntity, GIAentityNode* childActionEntity);
bool checkDuplicateCondition(GIAentityNode* conditionEntity, GIAentityNode* childActionEntity);

#ifdef NLC_SUPPORT_INPUT_FUNCTION_LISTS
string parseFunctionNameFromNLCfunctionName(string NLCfunctionName);
void parseFunctionNameFromNLCfunctionName(string NLCfunctionName, string* functionName, string* functionOwnerName, bool* hasFunctionOwnerClass);
void parseFunctionNameFromNLCfunctionName(string NLCfunctionName, string* functionName, string* functionOwnerName, bool* hasFunctionOwnerClass, string* functionObjectName, bool* hasFunctionObjectClass);
#ifdef NLC_USE_LIBRARY
void parseFunctionNameFromNLClibFunctionName(string NLCfunctionName, string* functionName, string* functionOwnerName, bool* hasFunctionOwnerClass, string* functionObjectName, bool* hasFunctionObjectClass, vector<NLCitem*>* additionalArguments);
#endif
void parseFunctionNameFromNLCgeneralFunctionName(string NLCfunctionName, string* functionName, string* functionOwnerName, bool* hasFunctionOwnerClass, string* functionObjectName, bool* hasFunctionObjectClass, vector<NLCitem*>* additionalArguments);
string generateNLCfunctionHeader(string functionName, string functionOwnerName, bool hasFunctionOwnerClass, string functionObjectName, bool hasFunctionObjectClass);
#endif

#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS_ADVANCED
NLCcodeblock* createCodeBlockLogicalConditionConjunctionOfBools(NLCcodeblock* currentCodeBlockInTree, int logicalOperation, NLClogicalConditionConjunction* logicalConditionConjunctionArray, int logicalConditionConjunctionIndexMax, int logicalConditionLevel, int logicalConditionCase, bool elseIfDetected);
string generateLogicalConditionConjunctionBooleanName(int logicalConditionLevel, int logicalConditionCase, int logicalOperation);
string generateLogicalConditionConjunctionBooleanName(int logicalConditionLevel, int logicalConditionCase, int logicalConditionConjunctionIndex, int logicalOperation);
NLCcodeblock* createCodeBlockDeclareNewBoolArray(NLCcodeblock* currentCodeBlockInTree, string boolArrayName, bool value);
#else
NLCcodeblock* createCodeBlockIfHasProperty(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, string context, bool negative);
NLCcodeblock* createCodeBlockIfHasCondition(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* condition, GIAentityNode* conditionObject, string context, bool negative);
NLCcodeblock* createCodeBlockWhileHasProperty(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, string context, bool negative);
NLCcodeblock* createCodeBlockWhileHasCondition(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* condition, GIAentityNode* conditionObject, string context, bool negative);
#endif
#endif
NLCcodeblock* createCodeBlockElse(NLCcodeblock* currentCodeBlockInTree);
NLCcodeblock* createCodeBlockWhileHasBool(NLCcodeblock* currentCodeBlockInTree, string whileLogicalConditionConjunctionBooleanName);
string generateWhileLogicalConditionConjunctionBooleanName(int logicalConditionLevel);
NLCcodeblock* createCodeBlockDeclareNewBoolVar(NLCcodeblock* currentCodeBlockInTree, string boolVariableName, bool value);
NLCcodeblock* createCodeBlockSetBoolVar(NLCcodeblock* currentCodeBlockInTree, string boolVariableName, bool value);


#ifdef NLC_TRANSLATE_NEGATIVE_PROPERTIES_AND_CONDITIONS
NLCcodeblock* createCodeBlockRemoveProperty(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* propertyEntity);
NLCcodeblock* createCodeBlockRemoveProperties(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* propertyEntity);
NLCcodeblock* createCodeBlockRemoveEntitiesFromLocalList(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity);
NLCcodeblock* createCodeBlockRemoveCondition(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* conditionEntity);
	NLCcodeblock* createCodeBlockRemoveConditionSimple(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* conditionEntity, GIAentityNode* conditionObject);
NLCcodeblock* createCodeBlockRemoveConditions(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* conditionEntity);
	NLCcodeblock* createCodeBlockRemoveConditionsSimple(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* conditionEntity, GIAentityNode* conditionObject);
#endif

#ifdef NLC_PREPROCESSOR_MATH
NLCcodeblock* createCodeBlockMathTextLine(NLCcodeblock* currentCodeBlockInTree, string mathText);
NLCcodeblock* createCodeBlockMathTextWithLogicalOperator(NLCcodeblock* currentCodeBlockInTree, string mathText);
#endif
NLCcodeblock* createCodeBlockDeclareNewIntVar(NLCcodeblock* currentCodeBlockInTree, string intVariableName, int value);
NLCcodeblock* createCodeBlockIncrementIntVar(NLCcodeblock* currentCodeBlockInTree, string intVariableName);

NLCcodeblock* createCodeBlockCommentSingleLine(NLCcodeblock* currentCodeBlockInTree, string comment);


#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN
NLCcodeblock* createCodeBlockReassignIter(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity);
NLCcodeblock* createCodeBlocksDeclareNewCategoryListVariable(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, string genericListAppendName);
NLCcodeblock* createCodeBlockAddEntityToCategoryList(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* propertyEntity, string genericListAppendName);
NLCcodeblock* createCodeBlockForCategoryList(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, string genericListAppendName);
#ifdef NLC_CATEGORIES_TEST_PLURALITY
NLCcodeblock* createCodeBlockGetBackCategoryEntityList(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, string genericListAppendName);
NLCcodeblock* createCodeBlockIfHasGreaterThanNumCategoryItem(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, string genericListAppendName, int value);
#endif
#ifdef NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY
NLCcodeblock* createCodeBlockIfHasGreaterThanOrEqualToNumCategoryItem(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, string genericListAppendName, int value);
#endif
#ifdef NLC_USE_ADVANCED_REFERENCING
NLCcodeblock* createCodeBlockIfHasCategoryItem(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, bool negative, string genericListAppendName);
NLCcodeblock* createCodeBlockAddEntityToCategoryListCheckLastSentenceReferencedSingularExecuteFunction(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* propertyEntity, string genericListAppendName);
NLCcodeblock* createCodeBlockAddEntityToCategoryListCheckLastSentenceReferencedSingularNewFunction(NLCcodeblock* currentCodeBlockInTree);
#endif
#ifdef NLC_PERFORM_PLURAL_DEFINITE_REFERENCING_TESTS
NLCcodeblock* createCodeBlockAddEntityToCategoryListCheckLastSentenceReferencedPluralExecuteFunction(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* propertyEntity, string genericListAppendName);
NLCcodeblock* createCodeBlockAddEntityToCategoryListCheckLastSentenceReferencedPluralNewFunction(NLCcodeblock* currentCodeBlockInTree);
#endif
	NLCcodeblock* createCodeBlocksDeclareNewGenericListVariable(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, string genericObjectName, string genericListAppendName);
	NLCcodeblock* createCodeBlockAddEntityToGenericList(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, string genericObjectName, string genericListAppendName, GIAentityNode* propertyEntity);
	NLCcodeblock* createCodeBlockForGenericList(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, string genericObjectName, string genericListAppendName);
	#ifdef NLC_CATEGORIES_TEST_PLURALITY
	NLCcodeblock* createCodeBlockGetBackGenericEntityList(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, string genericObjectName, string genericListAppendName);
	NLCcodeblock* createCodeBlockIfHasGreaterThanNumGenericEntity(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, string genericObjectName, string genericListAppendName, int value);
	NLCcodeblock* createCodeBlockPrintWarning(NLCcodeblock* currentCodeBlockInTree, string warning);
	#endif
	#ifdef NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY
	NLCcodeblock* createCodeBlockIfHasGreaterThanOrEqualToNumGenericEntity(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, string genericObjectName, string genericListAppendName, int value);
	#endif
	#ifdef NLC_USE_ADVANCED_REFERENCING
	NLCcodeblock* createCodeBlockIfHasGenericEntity(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, string genericObjectName, string genericListAppendName, bool negative);
	NLCcodeblock* createCodeBlockAddEntityToGenericListCheckLastSentenceReferencedSingularExecuteFunction(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, string genericObjectName, string genericListAppendName, GIAentityNode* propertyEntity);
	NLCcodeblock* createCodeBlockAddEntityToGenericListCheckLastSentenceReferencedSingularNewFunction(NLCcodeblock* currentCodeBlockInTree);
	NLCcodeblock* createCodeBlockUpdateLastSentenceReferenced(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, int sentenceIndex);
	#endif
	#ifdef NLC_PERFORM_PLURAL_DEFINITE_REFERENCING_TESTS
	NLCcodeblock* createCodeBlockAddEntityToGenericListCheckLastSentenceReferencedPluralExecuteFunction(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, string genericObjectName, string genericListAppendName, GIAentityNode* propertyEntity);
	NLCcodeblock* createCodeBlockAddEntityToGenericListCheckLastSentenceReferencedPluralNewFunction(NLCcodeblock* currentCodeBlockInTree);
	#endif
#endif

#ifdef NLC_GENERATE_TYPE_LISTS
NLCcodeblock* createCodeBlocksDeclareNewTypeListVariable(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity);
NLCcodeblock* createCodeBlockAddInstanceListToTypeList(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* propertyEntity);
NLCcodeblock* createCodeBlockForPropertyTypeClass(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity);
	NLCcodeblock* createCodeBlocksDeclareNewGenericListVariable2(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, string genericObjectName, string genericListAppendName);
	NLCcodeblock* createCodeBlockAddEntityToGenericList2(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, string genericObjectName, string genericListAppendName, GIAentityNode* propertyEntity, string genericListAppendName2);
	NLCcodeblock* createCodeBlockForGenericList2(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, string genericObjectName, string genericListAppendName);
#endif

#ifdef NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY_CHILDREN
NLCcodeblock* createCodeBlockIfIntVariableGreaterThanOrEqualToNum(NLCcodeblock* currentCodeBlockInTree, string intVariableName, int value);
/*
NLCcodeblock* createCodeBlockIfHasMoreThanNumProperty(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* propertyEntity, int value, string parentInstanceName);
NLCcodeblock* createCodeBlockIfHasMoreThanNumCondition(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* conditionEntity, GIAentityNode* conditionObject, int value, string parentInstanceName);
*/
#endif

#ifdef NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT
NLCcodeblock* createCodeBlocksDeclareContextList(NLCcodeblock* currentCodeBlockInTree, int contextLevel);
NLCcodeblock* createCodeBlocksAddEntityToContextLevelListNewFunction(NLCcodeblock* currentCodeBlockInTree);
NLCcodeblock* createCodeBlocksClearContextListNewFunction(NLCcodeblock* currentCodeBlockInTree);
NLCcodeblock* createCodeBlocksAddEntityToContextLevelListExecuteFunction(NLCcodeblock* currentCodeBlockInTree, int contextLevel, GIAentityNode* entity, int sentenceIndex);
NLCcodeblock* createCodeBlocksClearContextListVariableExecuteFunction(NLCcodeblock* currentCodeBlockInTree, int contextLevel);
NLCcodeblock* createCodeBlocksCreateContextBlock(NLCcodeblock* currentCodeBlockInTree);
#endif

#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS	
NLCcodeblock* createCodeBlocksCastVectorNewFunction(NLCcodeblock* currentCodeBlockInTree);
NLCcodeblock* createCodeBlocksCastVectorExecuteFunction(NLCcodeblock* currentCodeBlockInTree, NLCitem* item, NLCitem* itemPassCastClassName);
#endif

#ifdef NLC_USE_ADVANCED_REFERENCING_SUPPORT_ALIASES
NLCcodeblock* createCodeBlocksAddAliasToEntityAliasList(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, string aliasName);
NLCcodeblock* createCodeBlocksFindAliasAndAddToCategoryListNewFunction(NLCcodeblock* currentCodeBlockInTree);
NLCcodeblock* createCodeBlocksFindAliasAndAddToCategoryListExecuteFunction(NLCcodeblock* currentCodeBlockInTree, string aliasName, GIAentityNode* entity, string genericListAppendName);
NLCcodeblock* createCodeBlocksFindAliasNewFunction(NLCcodeblock* currentCodeBlockInTree);
NLCcodeblock* createCodeBlocksFindAliasExecuteFunction(NLCcodeblock* currentCodeBlockInTree, string aliasName, GIAentityNode* entity);
bool findAliasInEntity(GIAentityNode* entity, string* aliasName);
#ifdef NLC_USE_ADVANCED_REFERENCING_SUPPORT_ALIASES_PREVENT_ADDING_AS_FUNCTION_ARGUMENT
unordered_map<string, string>* getFunctionAliasClassList();
void initialiseFunctionAliasClassList();
bool findEntityNameInFunctionAliasList(string aliasName, string* aliasClassName);
#endif
#endif

NLCcodeblock* clearCodeBlock(NLCcodeblock* codeBlock);

NLCcodeblock* createCodeBlockDebug(NLCcodeblock* currentCodeBlockInTree, string warning);

#ifdef NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY_CHILDREN
string generateCategoryListPropertyCountVariableName(GIAentityNode* entity);
#endif

//see NLCclassDefinitionClass.cpp for other versions of this function;
bool findFunctionArgument(vector<NLCitem*>* parameters, GIAentityNode* entity, int itemType, NLCitem** functionArgument);

NLCcodeblock* getLastCodeBlockInLevel(NLCcodeblock* currentCodeBlockInTree);

#ifdef NLC_NORMALISE_TWOWAY_PREPOSITIONS
GIAentityNode* generateInverseConditionEntity(GIAentityNode* conditionEntity);
#endif

#ifdef NLC_SUPPORT_REDEFINITIONS
NLCcodeblock* createCodeBlockCheckParentClassNameExecuteFunction1(NLCcodeblock* currentCodeBlockInTree, string objectInstanceName, string classNameToFind);
NLCcodeblock* createCodeBlockCheckParentClassNameExecuteFunction1(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* object, string classNameToFind);
NLCcodeblock* createCodeBlockCheckParentClassNameExecuteFunction2(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* object, string classNameToFind);
NLCcodeblock* createCodeBlockCheckParentClassNameNewFunction(NLCcodeblock* currentCodeBlockInTree);
NLCcodeblock* createCodeConvertParentToChildClass(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* parentEntity, GIAentityNode* childEntity);
#endif


NLCcodeblock* createCodeBlockDeclareTempVariable(NLCcodeblock* currentCodeBlockInTree, string tempVariableClassName, string tempVariableInstanceName);
NLCcodeblock* createCodeBlockSetTempVariable(NLCcodeblock* currentCodeBlockInTree, string tempVariableInstanceName, GIAentityNode* entity);
NLCcodeblock* createCodeBlockDeclareTempVariableAndSetToEntity(NLCcodeblock* currentCodeBlockInTree, string tempVariableClassName, string tempVariableInstanceName, GIAentityNode* entity);
NLCcodeblock* createCodeBlockIfTempVariableEqualsEntity(NLCcodeblock* currentCodeBlockInTree, string tempVariableClassName, string tempVariableInstanceName, GIAentityNode* entity);

#ifdef NLC_USE_NON_LIBRARY_FUNCTIONS_EXTENDED
NLCcodeblock* createCodeBlockAddPropertyNewFunction(NLCcodeblock* currentCodeBlockInTree);
NLCcodeblock* createCodeBlockAddConditionNewFunction(NLCcodeblock* currentCodeBlockInTree);
#endif

#ifdef NLC_USE_MATH_OBJECTS
NLCcodeblock* createCodeBlockSetMathValue(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* valueEntity);
NLCcodeblock* createCodeBlockDeclareNewDecimalPointerVar(NLCcodeblock* currentCodeBlockInTree, string decimalPointerVariableName);
NLCcodeblock* createCodeBlockSetDecimalPointerToEntityMathValue(NLCcodeblock* currentCodeBlockInTree, string decimalPointerVariableName, GIAentityNode* entity);
#ifdef NLC_MATH_OBJECTS_TEST_NULL_POINTER_MAINTAIN_CONTEXT
NLCcodeblock* createCodeBlockTestDecimalPointerValue(NLCcodeblock* currentCodeBlockInTree, string decimalPointerVariableName);
#else
NLCcodeblock* createCodeBlockCheckDecimalPointerValue(NLCcodeblock* currentCodeBlockInTree, string decimalPointerVariableName);
#endif
#endif


#ifdef NLC_USE_SUPPORT_REFERENCING_OBJECTS_IN_PLURAL_LIST_BY_NUMBER
bool checkNumericalReferenceToEntity(GIAentityNode* entity);
#endif

#endif
