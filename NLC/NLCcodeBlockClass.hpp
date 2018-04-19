/*******************************************************************************
 *
 * No License
 * 
 * This work is under exclusive copyright (c) Baxter AI (baxterai.com). 
 * Nobody else can use, copy, distribute, or modify this work without being 
 * at risk of take-downs, shake-downs, or litigation. 
 * 
 * By publishing this source code in a public repository on GitHub, Terms of 
 * Service have been accepted by which Baxter AI have allowed others to view 
 * and fork their repository.
 * 
 * If you find software that doesn't have a license, that generally means you 
 * have no permission from the creators of the software to use, modify, or 
 * share the software. Although a code host such as GitHub may allow you to 
 * view and fork the code, this does not imply that you are permitted to use, 
 * modify, or share the software for any purpose.
 *
 * This notice has been derived from https://choosealicense.com/no-permission 
 * (https://web.archive.org/web/20180312144938/https://choosealicense.com/no-permission)
 *
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: NLCcodeBlockClass.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2018 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler
 * Project Version: 2f3a 10-April-2018
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 * /
 *******************************************************************************/


#ifndef HEADER_NLC_CODEBLOCK_CLASS
#define HEADER_NLC_CODEBLOCK_CLASS

#include "NLCglobalDefs.hpp"
#include "NLCitemClass.hpp"
#include "GIAentityNodeClass.hpp"
#include "GIAentityConnectionClass.hpp"
//#ifdef NLC_PREPROCESSOR
#include "NLCpreprocessorSentenceClass.hpp"	//required for findIndefiniteEntityCorrespondingToDefiniteEntityInSameContext()
#include "NLCprintDefs.hpp"	//required for progLangArrayOpen/progLangArrayClose/NLC_ITEM_TYPE_PROPERTYCOUNT_VAR_APPENDITION/NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION
#include "GIAtranslatorOperations.hpp"
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
	#ifdef NLC_ADVANCED_REFERENCING
		#define NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST_CHECK_LAST_SENTENCE_REFERENCED_SINGULAR_EXECUTE_FUNCTION (34)
		#define NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST_CHECK_LAST_SENTENCE_REFERENCED_SINGULAR_WITH_CAST_EXECUTE_FUNCTION (35)
		#define NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST_CHECK_LAST_SENTENCE_REFERENCED_SINGULAR_NEW_FUNCTION (36)
		#define NLC_CODEBLOCK_TYPE_UPDATE_LAST_SENTENCE_REFERENCED (37)	//execute for all new/undeclared/indefinite entities and accessed category items
	#endif
#endif
#ifdef NLC_PERFORM_PLURAL_DEFINITE_REFERENCING_TESTS
	#define NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST_CHECK_LAST_SENTENCE_REFERENCED_PLURAL_EXECUTE_FUNCTION (38)
	#define NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST_CHECK_LAST_SENTENCE_REFERENCED_PLURAL_WITH_CAST_EXECUTE_FUNCTION (39)
	#define NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST_CHECK_LAST_SENTENCE_REFERENCED_PLURAL_NEW_FUNCTION (40)
#endif
#ifdef NLC_GENERATE_TYPE_LISTS
	#define NLC_CODEBLOCK_TYPE_DECLARE_NEW_GENERIC_LIST_VARIABLE2 (41)
	#define NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST2 (42)
#endif
#ifdef NLC_ADVANCED_REFERENCING_MONITOR_CONTEXT
	#define NLC_CODEBLOCK_TYPE_DECLARE_CONTEXT_LIST (43)
	#define NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_CONTEXT_LIST_NEW_FUNCTION (44)
	#define NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_CONTEXT_LIST_EXECUTE_FUNCTION (45)
	#define NLC_CODEBLOCK_TYPE_CLEAR_CONTEXT_LIST_NEW_FUNCTION (46)
	#define NLC_CODEBLOCK_TYPE_CLEAR_CONTEXT_LIST_EXECUTE_FUNCTION (47)
#endif
#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS
	#define NLC_CODEBLOCK_TYPE_CAST_VECTOR_NEW_FUNCTION (48)
	#define NLC_CODEBLOCK_TYPE_CAST_VECTOR_EXECUTE_FUNCTION (49)
#endif
#ifdef NLC_ADVANCED_REFERENCING_SUPPORT_ALIASES
	#define NLC_CODEBLOCK_TYPE_ADD_ALIAS_TO_ENTITY_ALIAS_LIST (50)
	#define NLC_CODEBLOCK_TYPE_FIND_ALIAS_AND_ADD_TO_CATEGORY_LIST_NEW_FUNCTION (51)
	#define NLC_CODEBLOCK_TYPE_FIND_ALIAS_AND_ADD_TO_CATEGORY_LIST_EXECUTE_FUNCTION (52)
	#define NLC_CODEBLOCK_TYPE_FIND_ALIAS_NEW_FUNCTION (53)
#endif
#ifdef NLC_RECORD_ACTION_HISTORY
	#define NLC_CODEBLOCK_TYPE_RECORD_HISTORY_ACTION_SUBJECT (54)
	#define NLC_CODEBLOCK_TYPE_RECORD_HISTORY_ACTION_OBJECT (55)
#endif
#ifdef NLC_REDEFINITIONS
	#define NLC_CODEBLOCK_TYPE_CONVERT_PARENT_TO_CHILD_CLASS (56)
#endif
#define NLC_CODEBLOCK_TYPE_DECLARE_TEMP_VARIABLE (57)			//param1class* param1 = NULL;
#define NLC_CODEBLOCK_TYPE_SET_TEMP_VARIABLE (58)			//param1 = param2;
#define NLC_CODEBLOCK_TYPE_DECLARE_TEMP_VARIABLE_AND_SET_TO_ENTITY (59)			//param1class* param1 = param2;
#ifdef NLC_REDEFINITIONS
	#define NLC_CODEBLOCK_TYPE_CHECK_PARENT_CLASS_NAME_NEW_FUNCTION (60)
#endif
#ifdef NLC_NON_LIBRARY_FUNCTIONS_EXTENDED
	#define NLC_CODEBLOCK_TYPE_ADD_PROPERTY_NEW_FUNCTION (61)
	#define NLC_CODEBLOCK_TYPE_ADD_CONDITION_NEW_FUNCTION (62)
#endif
#ifdef NLC_LIBRARY_BASE_EXTENDED
	#define NLC_CODEBLOCK_TYPE_ADD_PROPERTY_EXECUTE_FUNCTION (63)
	#define NLC_CODEBLOCK_TYPE_ADD_CONDITION_EXECUTE_FUNCTION (64)
#endif
#ifdef NLC_TRANSLATE_NEGATIVE_PROPERTIES_AND_CONDITIONS
	//should be merged with moved in line with other cases above
	#define NLC_CODEBLOCK_TYPE_REMOVE_PROPERTY (65)
	#define NLC_CODEBLOCK_TYPE_REMOVE_CONDITION (66)
#endif
#ifdef NLC_MATH_OBJECTS
	#define NLC_CODEBLOCK_TYPE_SET_MATH_OBJECT_NUMERICAL_VALUE (67)
	#define NLC_CODEBLOCK_TYPE_DECLARE_NEW_DECIMAL_POINTER_VARIABLE (68)
	#define NLC_CODEBLOCK_TYPE_SET_DECIMAL_POINTER_TO_ENTITY_MATH_OBJECT_NUMERICAL_VALUE (69)
	#define NLC_CODEBLOCK_TYPE_SET_MATH_OBJECT_TYPE_AS_NUMERICAL (70)
	#ifdef NLC_MATH_OBJECTS_ADVANCED
		#define NLC_CODEBLOCK_TYPE_DECLARE_NEW_GENERIC_ENTITY_POINTER_VARIABLE (71)
		#define NLC_CODEBLOCK_TYPE_SET_GENERIC_ENTITY_POINTER_TO_ENTITY (72)
		#ifdef NLC_MATH_OBJECTS_STRING
		#define NLC_CODEBLOCK_TYPE_SET_MATH_OBJECT_STRING_VALUE (73)
		#define NLC_CODEBLOCK_TYPE_DECLARE_NEW_STRING_POINTER_VARIABLE (74)
		#define NLC_CODEBLOCK_TYPE_SET_STRING_POINTER_TO_ENTITY_MATH_OBJECT_STRING_VALUE (75)
		#define NLC_CODEBLOCK_TYPE_SET_MATH_OBJECT_TYPE_AS_STRING (76)
		#endif
		#ifdef NLC_MATH_OBJECTS_BOOLEAN
		#define NLC_CODEBLOCK_TYPE_SET_MATH_OBJECT_BOOLEAN_VALUE (77)
		#define NLC_CODEBLOCK_TYPE_DECLARE_NEW_BOOLEAN_POINTER_VARIABLE (78)
		#define NLC_CODEBLOCK_TYPE_SET_BOOLEAN_POINTER_TO_ENTITY_MATH_OBJECT_BOOLEAN_VALUE (79)
		#define NLC_CODEBLOCK_TYPE_SET_MATH_OBJECT_TYPE_AS_BOOLEAN (80)
		#endif
	#endif
	#ifdef NLC_MATH_OBJECTS_TEST_NULL_POINTER_MAINTAIN_CONTEXT
		#define NLC_CODEBLOCK_TYPE_TEST_POINTER_VALUE (81)
	#endif
#endif
#ifdef NLC_NORMALISE_TWOWAY_PREPOSITIONS_MARK_INVERSE_CONDITIONS
	#define NLC_CODEBLOCK_TYPE_ADD_CONDITION_INVERSE (82)
	#ifdef NLC_NON_LIBRARY_FUNCTIONS_EXTENDED
		#define NLC_CODEBLOCK_TYPE_ADD_CONDITION_INVERSE_NEW_FUNCTION (83)
	#endif
#endif
#ifdef NLC_TRANSLATOR_TEST_DEFINITE_ENTITY_EXISTENCE
	#define NLC_CODEBLOCK_TYPE_VERIFY_DEFINITE_ENTITY_EXISTENCE_NEW_FUNCTION (84)
	#define NLC_CODEBLOCK_TYPE_VERIFY_DEFINITE_ENTITY_EXISTENCE_EXECUTE_FUNCTION (85)
#endif
#ifdef NLC_ADVANCED_REFERENCING_SUPPORT_ALIASES_MERGERS
	#define NLC_CODEBLOCK_TYPE_REMOVE_ENTITY_FROM_LOCAL_LIST_EXECUTE_FUNCTION (86)
	#define NLC_CODEBLOCK_TYPE_REPLACE_ENTITY_IN_LOCAL_LIST_EXECUTE_FUNCTION (87)
	#define NLC_CODEBLOCK_TYPE_MERGE_ENTITY1_ATTRIBUTES_INTO_ENTITY2_EXECUTE_FUNCTION (88)
#endif

//containers:
#define NLC_CODEBLOCK_TYPE_FOR_PROPERTY_LIST (100)		//forall(context1.param1PropertyList){
#define NLC_CODEBLOCK_TYPE_FOR_LOCAL_LIST (101)	//forall(param1instance){
#define NLC_CODEBLOCK_TYPE_FOR_CONDITION_LIST (102)		//forall(context1.param1param2ConditionList){
#define NLC_CODEBLOCK_TYPE_FOR_INTEGER (103)
#define NLC_CODEBLOCK_TYPE_NEW_FUNCTION (104)			//main(){

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
	#define NLC_CODEBLOCK_TYPE_IF_HAS_GENERIC_ENTITY (117)
#endif
#ifdef NLC_GENERATE_TYPE_LISTS
	#define NLC_CODEBLOCK_TYPE_FOR_GENERIC_LIST2 (118)
#endif
#ifdef NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY
	#define NLC_CODEBLOCK_TYPE_IF_HAS_GREATER_THAN_OR_EQUAL_TO_NUM_GENERIC_ENTITY (119)
	#define NLC_CODEBLOCK_TYPE_TEST_INT_VARIABLE_GREATER_THAN_OR_EQUAL_TO_NUM (120)
	#define NLC_CODEBLOCK_TYPE_TEST_INT_VARIABLE_EQUALS_LIST_SIZE (121)
	//#define NLC_CODEBLOCK_TYPE_IF_HAS_MORE_THAN_NUM_PROPERTY (12x)
	//#define NLC_CODEBLOCK_TYPE_IF_HAS_MORE_THAN_NUM_CONDITION (12x)
#endif
#define NLC_CODEBLOCK_TYPE_CONTEXT_BLOCK (123)
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
#ifdef NLC_REFERENCING_OBJECTS_IN_PLURAL_LIST_BY_NUMBER
	#define NLC_CODEBLOCK_TYPE_IN_PROPERTY_LIST (131)
	#define NLC_CODEBLOCK_TYPE_IN_LOCAL_LIST (132)
#endif
#ifdef NLC_REDEFINITIONS
	#define NLC_CODEBLOCK_TYPE_CHECK_PARENT_CLASS_NAME_EXECUTE_FUNCTION1 (133)
	#define NLC_CODEBLOCK_TYPE_CHECK_PARENT_CLASS_NAME_EXECUTE_FUNCTION2 (134)
#endif
#define NLC_CODEBLOCK_TYPE_IF_TEMP_VARIABLE_EQUALS_ENTITY (135)			//if(param1 == param2){
#ifdef NLC_ADVANCED_REFERENCING_SUPPORT_ALIASES
	#define NLC_CODEBLOCK_TYPE_FIND_ALIAS_EXECUTE_FUNCTION (136)
#endif
#ifdef NLC_MATH_OBJECTS
	#ifndef NLC_MATH_OBJECTS_TEST_NULL_POINTER_MAINTAIN_CONTEXT
		#define NLC_CODEBLOCK_TYPE_CHECK_POINTER_VALUE (137)
	#endif
	#define NLC_CODEBLOCK_TYPE_TEST_MATH_OBJECT_NUMERICAL_VALUE (138)
#endif
#define NLC_CODEBLOCK_TYPE_IF_TEMP_VARIABLE_NAME_EQUALS_CLASS_NAME (139)
#define NLC_CODEBLOCK_TYPE_CHECK_BOOL_VARIABLE_TRUE (140)
#define NLC_CODEBLOCK_TYPE_CHECK_BOOL_VARIABLE_FALSE (141)

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

	#ifdef NLC_ADVANCED_REFERENCING_MONITOR_CONTEXT
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
	bool negative;
	#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
	bool onlyGenerateContextBlocksIfConnectionsParsedForNLCorSameReferenceSet;
	bool generateContextBlocksIfSameReferenceSet;	//added 1i3d
	#endif
	#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
	bool negativeDetectedInContextBlocks;
	#ifdef NLC_TRANSLATOR_LOGICAL_CONDITIONS_SINGLE_SENTENCE_MULTIPLE_LEVEL_FOR_LOOPS_OLD
	#ifndef NLC_GENERATE_UNIQUE_CONTEXT_BLOCK_FOR_EACH_SENTENCE_LOGICAL_CONDITIONS_FOR_LOOPS
	bool setCodeBlockInTreeAtBaseLevel;	//added 1k16c - for loop support
	NLCcodeblock* currentCodeBlockInTreeAtBaseLevel;	//added 1k16c - for loop support
	#endif
	#endif
	#endif
	
	#ifdef NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY
	bool testNumerosity;
	#ifdef NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY_BASIC
	int childQuantity;
	#endif
	#endif
	#ifdef NLC_FUNCTIONS_SUPPORT_PLURAL_SUBJECTS_AND_OBJECTS
	bool enterGeneratedCategoryList;
	#endif
	#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN
	bool searchConceptsForChildren;
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
	#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN_SUBCLASSES
	bool searchSubclassesForChildren;
	#endif
	#ifdef NLC_TRANSLATOR_LOGICAL_CONDITIONS_BOOLEAN_STATEMENTS_INTERPRET_SUBJECT_AND_OBJECT_INDEPENDENTLY
	bool logicalConditionStatement;
	bool secondaryComparison;
	#endif
};


class NLCcodeBlockClassClass
{
	private: SHAREDvarsClass SHAREDvars;
	private: GIAtranslatorOperationsClass GIAtranslatorOperations;
	private: NLCitemClassClass NLCitemClass;
	
	public: int getCurrentLogicalConditionLevel();
	public: void setCurrentLogicalConditionLevel(const int value);

	public: NLCcodeblock* createCodeBlockExecuteSubjectObject(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* actionRelationshipEntity, const GIAentityNode* subjectEntity, const GIAentityNode* objectEntity, const int sentenceIndex);
	public: NLCcodeblock* createCodeBlockExecuteSubject(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* actionRelationshipEntity, const GIAentityNode* subjectEntity, const int sentenceIndex);
	public: NLCcodeblock* createCodeBlockExecuteObject(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* actionRelationshipEntity, const GIAentityNode* objectEntity, const int sentenceIndex);
	public: NLCcodeblock* createCodeBlockExecute(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* actionRelationshipEntity, const int sentenceIndex);
	#ifdef NLC_RECORD_ACTION_HISTORY
	public: NLCcodeblock* createCodeBlockRecordHistoryActionSubject(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* actionRelationshipEntity, const GIAentityNode* subjectEntity);
	public: NLCcodeblock* createCodeBlockRecordHistoryActionObject(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* actionRelationshipEntity, const GIAentityNode* objectEntity);
	#endif

	public: NLCcodeblock* createCodeBlockCreateNewProperty(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* propertyRelationshipObjectEntity, int sentenceIndex, bool copyNewItemsToLocalList);
		private: NLCcodeblock* createCodeBlockAddNewProperty(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, GIAentityNode* propertyRelationshipObjectEntity, int sentenceIndex, const bool copyNewItemsToLocalList);
			public: NLCcodeblock* createCodeBlockAddEntityToLocalList(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* localListEntity, const GIAentityNode* entity);
			public: NLCcodeblock* createCodeBlockAddProperty(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const GIAentityNode* propertyRelationshipObjectEntity, const int sentenceIndex);

	public: NLCcodeblock* createCodeBlockCreateNewCondition(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* conditionRelationshipEntity, int sentenceIndex, bool copyNewItemsToLocalList);
		private: NLCcodeblock* createCodeBlockAddNewCondition(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* conditionRelationshipEntity, int sentenceIndex, const bool copyNewItemsToLocalList);
			private: NLCcodeblock* createCodeBlockAddNewConditionSimple(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const GIAentityNode* conditionRelationshipEntity, const GIAentityNode* conditionRelationshipObjectEntity);
	public: NLCcodeblock* createCodeBlockAddCondition(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* conditionRelationshipEntity, const int sentenceIndex);
		public: NLCcodeblock* createCodeBlockAddConditionSimple(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const GIAentityNode* conditionRelationshipEntity, const GIAentityNode* conditionRelationshipObjectEntity);
		#ifdef NLC_NORMALISE_TWOWAY_PREPOSITIONS
		private: NLCcodeblock* createCodeBlockAddConditionSimpleInverse(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* conditionRelationshipEntity, GIAentityNode* conditionRelationshipObjectEntity);
		#endif

	public: NLCcodeblock* createCodeBlocksCreateNewLocalListVariable(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, int sentenceIndex);
		public: NLCcodeblock* createCodeBlocksDeclareNewLocalListVariableIfNecessary(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity);
			private: NLCcodeblock* createCodeBlocksDeclareNewLocalListVariable(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, const bool createTypeList);
				#ifdef NLC_GENERATE_TYPE_LISTS
				public: NLCcodeblock* createIfNecessaryAndAddToTypeList(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity);
				#endif
		private: NLCcodeblock* createCodeBlockAddNewEntityToLocalList(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, int sentenceIndex, const bool addReferencingContext);

	public: NLCcodeblock* createCodeBlockForOrInPropertyList(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, string context);
	public: NLCcodeblock* createCodeBlockForOrInPropertyList(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity);
		public: NLCcodeblock* createCodeBlockForPropertyList(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const GIAentityNode* parent);
			public: NLCcodeblock* createCodeBlockForPropertyList(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const string context);
				public: NLCcodeblock* createCodeBlockForPropertyList(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity);
					public: NLCcodeblock* createCodeBlockForPropertyList(NLCcodeblock* currentCodeBlockInTree, NLCitem* item);
		#ifdef NLC_REFERENCING_OBJECTS_IN_PLURAL_LIST_BY_NUMBER
		private: NLCcodeblock* createCodeBlockInPropertyList(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const int index);
		private: NLCcodeblock* createCodeBlockInPropertyList(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const string context, const int index);
		#endif
	public: NLCcodeblock* createCodeBlockForOrInLocalList(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity);
		public: NLCcodeblock* createCodeBlockForLocalList(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity);
		#ifdef NLC_REFERENCING_OBJECTS_IN_PLURAL_LIST_BY_NUMBER
		private: NLCcodeblock* createCodeBlockInLocalList(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const int index);
		#endif
	public: NLCcodeblock* createCodeBlockForConditionList(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* condition, const GIAentityNode* conditionRelationshipObjectEntity, const GIAentityNode* conditionRelationshipSubjectEntity);
		public: NLCcodeblock* createCodeBlockForConditionList(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* condition, const GIAentityNode* conditionRelationshipObjectEntity, const string context);
			public: NLCcodeblock* createCodeBlockForConditionList(NLCcodeblock* currentCodeBlockInTree, NLCitem* item, NLCitem* objectItem);

	#ifdef NLC_NONOO
	private: NLCcodeblock* createCodeBlockIfPropertyName(NLCcodeblock* currentCodeBlockInTree, NLCitem* item);
	private: NLCcodeblock* createCodeBlockIfConditionName(NLCcodeblock* currentCodeBlockInTree, NLCitem* item, NLCitem* objectItem);
	#ifdef NLC_RECORD_ACTION_HISTORY
	private: NLCcodeblock* createCodeBlockIfActionName(NLCcodeblock* currentCodeBlockInTree, NLCitem* item);
	#endif
	#endif
	#ifdef NLC_RECORD_ACTION_HISTORY
	public: NLCcodeblock* createCodeBlockForActionList(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* actionRelationshipEntity, const GIAentityNode* actionRelationshipSubjectEntity);
		public: NLCcodeblock* createCodeBlockForActionList(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const string context);
	public: NLCcodeblock* createCodeBlockForActionIncomingList(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* actionRelationshipEntity, const GIAentityNode* actionRelationshipObjectEntity);
		public: NLCcodeblock* createCodeBlockForActionIncomingList(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const string context);
	public: NLCcodeblock* createCodeBlockForActionObjectList(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* actionRelationshipObjectEntity, const GIAentityNode* actionRelationshipEntity);
		public: NLCcodeblock* createCodeBlockForActionObjectList(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const string context);
	public: NLCcodeblock* createCodeBlockForActionSubjectList(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* actionRelationshipSubjectEntity, const GIAentityNode* actionRelationshipEntity);
		public: NLCcodeblock* createCodeBlockForActionSubjectList(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const string context);
	#endif
	#ifdef NLC_QUANTITIES
	private: NLCcodeblock* createCodeBlockForInteger(NLCcodeblock* currentCodeBlockInTree, const string numberIterationsOrVariable);
	#endif
	public: NLCcodeblock* createCodeBlockDeclareAndInitialiseVariableForActionSubject(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* functionOwner);
	public: NLCcodeblock* createCodeBlocksAddVariableToNewList(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity);

	public: bool assumedToAlreadyHaveBeenDeclared(const GIAentityNode* entity);
		public: bool isDefiniteEntity(const GIAentityNode* entity);
		public: bool isDefiniteEntityStrict(const GIAentityNode* entity);
	public: bool assumedToAlreadyHaveBeenDeclaredInitialisation(const GIAentityNode* entity);

	public: NLCcodeblock* createCodeBlock(NLCcodeblock* currentCodeBlockInTree, int codeBlockType);
	private: NLCcodeblock* createLowerLevel(NLCcodeblock* currentCodeBlockInTree);

	private: bool getEntityContext(GIAentityNode* entity, vector<string>* context, const bool includePresentObject, const int sentenceIndex, const bool markSameSentenceParentsAsParsed);

	public: bool checkSentenceIndexParsingCodeBlocks(const GIAentityNode* entity, const GIAentityConnection* connection, const int sentenceIndex, const bool checkIfEntityHasBeenParsedForNLCcodeBlocks);
		public: bool checkSentenceIndexParsingCodeBlocks(const GIAentityNode* entity, const int sentenceIndex, const bool checkIfEntityHasBeenParsedForNLCcodeBlocks);

	public: bool checkDuplicateProperty(const GIAentityNode* propertyRelationshipObjectEntity, GIAentityNode* childActionEntity);
	public: bool checkDuplicateCondition(GIAentityNode* conditionRelationshipEntity, GIAentityNode* childActionEntity);

	public: NLCcodeblock* createCodeBlockElse(NLCcodeblock* currentCodeBlockInTree);
	public: NLCcodeblock* createCodeBlockWhileHasBool(NLCcodeblock* currentCodeBlockInTree, const string whileLogicalConditionConjunctionBooleanName);
	public: string generateWhileLogicalConditionConjunctionBooleanName(const int logicalConditionLevel);
	public: NLCcodeblock* createCodeBlockDeclareNewBoolVar(NLCcodeblock* currentCodeBlockInTree, const string boolVariableName, const bool value);
	public: NLCcodeblock* createCodeBlockSetBoolVar(NLCcodeblock* currentCodeBlockInTree, const string boolVariableName, const bool value);
	private: NLCcodeblock* createCodeBlockCheckBoolVar(NLCcodeblock* currentCodeBlockInTree, const string boolVariableName, const bool value);

	#ifdef NLC_TRANSLATE_NEGATIVE_PROPERTIES_AND_CONDITIONS
	public: NLCcodeblock* createCodeBlockRemoveProperty(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const GIAentityNode* propertyRelationshipObjectEntity);
	public: NLCcodeblock* createCodeBlockRemoveProperties(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const GIAentityNode* propertyRelationshipObjectEntity);
	private: NLCcodeblock* createCodeBlockRemoveEntitiesFromLocalList(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity);
	public: NLCcodeblock* createCodeBlockRemoveCondition(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* conditionRelationshipEntity);
		private: NLCcodeblock* createCodeBlockRemoveConditionSimple(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const GIAentityNode* conditionRelationshipEntity, const GIAentityNode* conditionRelationshipObjectEntity);
	public: NLCcodeblock* createCodeBlockRemoveConditions(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* conditionRelationshipEntity);
		private: NLCcodeblock* createCodeBlockRemoveConditionsSimple(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const GIAentityNode* conditionRelationshipEntity, const GIAentityNode* conditionRelationshipObjectEntity);
	#endif

	#ifdef NLC_PREPROCESSOR_MATH
	public: NLCcodeblock* createCodeBlockMathTextLine(NLCcodeblock* currentCodeBlockInTree, const string mathText);
	public: NLCcodeblock* createCodeBlockMathTextWithLogicalOperator(NLCcodeblock* currentCodeBlockInTree, const string mathText);
	#endif
	public: NLCcodeblock* createCodeBlockDeclareNewIntVar(NLCcodeblock* currentCodeBlockInTree, const string intVariableName, const int value);
	public: NLCcodeblock* createCodeBlockIncrementIntVar(NLCcodeblock* currentCodeBlockInTree, const string intVariableName);

	public: NLCcodeblock* createCodeBlockCommentSingleLine(NLCcodeblock* currentCodeBlockInTree, const string comment);


	#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN
	private: NLCcodeblock* createCodeBlockReassignIter(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity);
	public: NLCcodeblock* createCodeBlocksDeclareNewCategoryListVariable(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const string genericListAppendName, const int sentenceIndex);
	public: NLCcodeblock* createCodeBlockAddEntityToCategoryList(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const GIAentityNode* propertyRelationshipObjectEntity, const string genericListAppendName, const int sentenceIndex);
	public: NLCcodeblock* createCodeBlockForCategoryList(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const string genericListAppendName, const int sentenceIndex);
	#ifdef NLC_CATEGORIES_TEST_PLURALITY
	public: NLCcodeblock* createCodeBlockGetBackCategoryEntityList(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const string genericListAppendName, const int sentenceIndex);
	public: NLCcodeblock* createCodeBlockIfHasGreaterThanNumCategoryItem(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const string genericListAppendName, const int value, const int sentenceIndex);
	#endif
	#ifdef NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY
	public: NLCcodeblock* createCodeBlockIfHasGreaterThanOrEqualToNumCategoryItem(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const string genericListAppendName, const int value, const int sentenceIndex);
	#endif
	public: NLCcodeblock* createCodeBlockIfHasCategoryItem(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const bool negative, const string genericListAppendName, const int sentenceIndex);
	#ifdef NLC_ADVANCED_REFERENCING
	public: NLCcodeblock* createCodeBlockAddEntityToCategoryListCheckLastSentenceReferencedSingularExecuteFunction(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const GIAentityNode* propertyRelationshipObjectEntity, const string genericListAppendName, const int sentenceIndex, const bool castToCategoryType);
	public: NLCcodeblock* createCodeBlockAddEntityToCategoryListCheckLastSentenceReferencedSingularNewFunction(NLCcodeblock* currentCodeBlockInTree);
	#endif
	#ifdef NLC_PERFORM_PLURAL_DEFINITE_REFERENCING_TESTS
	public: NLCcodeblock* createCodeBlockAddEntityToCategoryListCheckLastSentenceReferencedPluralExecuteFunction(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const GIAentityNode* propertyRelationshipObjectEntity, const string genericListAppendName, const int sentenceIndex, const bool castToCategoryType);
	public: NLCcodeblock* createCodeBlockAddEntityToCategoryListCheckLastSentenceReferencedPluralNewFunction(NLCcodeblock* currentCodeBlockInTree);
	#endif
		private: NLCcodeblock* createCodeBlocksDeclareNewGenericListVariable(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const string genericObjectName, const string genericListAppendName);
		private: NLCcodeblock* createCodeBlockAddEntityToGenericList(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const string genericObjectName, const string genericListAppendName, const GIAentityNode* propertyRelationshipObjectEntity);
		private: NLCcodeblock* createCodeBlockForGenericList(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const string genericObjectName, const string genericListAppendName);
		#ifdef NLC_CATEGORIES_TEST_PLURALITY
		private: NLCcodeblock* createCodeBlockGetBackGenericEntityList(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const string genericObjectName, const string genericListAppendName);
		private: NLCcodeblock* createCodeBlockIfHasGreaterThanNumGenericEntity(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const string genericObjectName, const string genericListAppendName, const int value);
		public: NLCcodeblock* createCodeBlockPrintWarning(NLCcodeblock* currentCodeBlockInTree, const string warning);
		#endif
		#ifdef NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY
		private: NLCcodeblock* createCodeBlockIfHasGreaterThanOrEqualToNumGenericEntity(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const string genericObjectName, const string genericListAppendName, const int value);
		#endif
		private: NLCcodeblock* createCodeBlockIfHasGenericEntity(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const string genericObjectName, const string genericListAppendName, const bool negative);
		#ifdef NLC_ADVANCED_REFERENCING
		private: NLCcodeblock* createCodeBlockAddEntityToGenericListCheckLastSentenceReferencedSingularExecuteFunction(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const string genericObjectName, const string genericListAppendName, const GIAentityNode* propertyRelationshipObjectEntity, const bool castToCategoryType);
		private: NLCcodeblock* createCodeBlockAddEntityToGenericListCheckLastSentenceReferencedSingularNewFunction(NLCcodeblock* currentCodeBlockInTree);
		public: NLCcodeblock* createCodeBlockUpdateLastSentenceReferenced(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const int sentenceIndex);
		#endif
		#ifdef NLC_PERFORM_PLURAL_DEFINITE_REFERENCING_TESTS
		public: NLCcodeblock* createCodeBlockAddEntityToGenericListCheckLastSentenceReferencedPluralExecuteFunction(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const string genericObjectName, const string genericListAppendName, const GIAentityNode* propertyRelationshipObjectEntity, const bool castToCategoryType);
		private: NLCcodeblock* createCodeBlockAddEntityToGenericListCheckLastSentenceReferencedPluralNewFunction(NLCcodeblock* currentCodeBlockInTree);
		#endif
#endif

	#ifdef NLC_GENERATE_TYPE_LISTS
	private: NLCcodeblock* createCodeBlocksDeclareNewTypeListVariable(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity);
	private: NLCcodeblock* createCodeBlockAddInstanceListToTypeList(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const GIAentityNode* propertyRelationshipObjectEntity);
	public: NLCcodeblock* createCodeBlockForPropertyTypeClass(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity);
		private: NLCcodeblock* createCodeBlocksDeclareNewGenericListVariable2(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const string genericObjectName, const string genericListAppendName);
		private: NLCcodeblock* createCodeBlockAddEntityToGenericList2(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const string genericObjectName, const string genericListAppendName, const GIAentityNode* propertyRelationshipObjectEntity, const string genericListAppendName2);
		private: NLCcodeblock* createCodeBlockForGenericList2(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const string genericObjectName, const string genericListAppendName);
	#endif

	#ifdef NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY
	public: NLCcodeblock* createCodeBlockIfIntVariableGreaterThanOrEqualToNum(NLCcodeblock* currentCodeBlockInTree, const string intVariableName, const int value);
	public: NLCcodeblock* createCodeBlockIfIntVariableEqualsListSize(NLCcodeblock* currentCodeBlockInTree, const string intVariableName, const GIAentityNode* entityList, const string genericListAppendName, const int sentenceIndex);
	/*
	NLCcodeblock* createCodeBlockIfHasMoreThanNumProperty(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* propertyRelationshipObjectEntity, int value, string parentInstanceName);
	NLCcodeblock* createCodeBlockIfHasMoreThanNumCondition(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* conditionRelationshipEntity, GIAentityNode* conditionRelationshipObjectEntity, int value, string parentInstanceName);
	*/
	#endif

	#ifdef NLC_ADVANCED_REFERENCING_MONITOR_CONTEXT
	public: NLCcodeblock* createCodeBlocksDeclareContextList(NLCcodeblock* currentCodeBlockInTree, const int contextLevel);
	public: NLCcodeblock* createCodeBlocksAddEntityToContextLevelListNewFunction(NLCcodeblock* currentCodeBlockInTree);
	public: NLCcodeblock* createCodeBlocksClearContextListNewFunction(NLCcodeblock* currentCodeBlockInTree);
	public: NLCcodeblock* createCodeBlocksAddEntityToContextLevelListExecuteFunction(NLCcodeblock* currentCodeBlockInTree, const int contextLevel, const GIAentityNode* entity, const int sentenceIndex);
	public: NLCcodeblock* createCodeBlocksClearContextListVariableExecuteFunction(NLCcodeblock* currentCodeBlockInTree, const int contextLevel);
	#endif
	public: NLCcodeblock* createCodeBlocksCreateContextBlock(NLCcodeblock* currentCodeBlockInTree);

	#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS
	public: NLCcodeblock* createCodeBlocksCastVectorNewFunction(NLCcodeblock* currentCodeBlockInTree);
	private: NLCcodeblock* createCodeBlocksCastVectorExecuteFunction(NLCcodeblock* currentCodeBlockInTree, NLCitem* item, NLCitem* itemPassCastClassName);
	#endif

	#ifdef NLC_ADVANCED_REFERENCING_SUPPORT_ALIASES
	public: NLCcodeblock* createCodeBlocksAddAliasToEntityAliasList(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const string aliasName);
	public: NLCcodeblock* createCodeBlocksFindAliasAndAddToCategoryListNewFunction(NLCcodeblock* currentCodeBlockInTree);
	public: NLCcodeblock* createCodeBlocksFindAliasAndAddToCategoryListExecuteFunction(NLCcodeblock* currentCodeBlockInTree, const string aliasName, const GIAentityNode* entity, const string genericListAppendName, const int sentenceIndex);
	public: NLCcodeblock* createCodeBlocksFindAliasNewFunction(NLCcodeblock* currentCodeBlockInTree);
	public: NLCcodeblock* createCodeBlocksFindAliasExecuteFunction(NLCcodeblock* currentCodeBlockInTree, const string aliasName, const GIAentityNode* entity);
	public: bool findAliasInEntity(GIAentityNode* entity, string* aliasName);
	#ifdef NLC_ADVANCED_REFERENCING_SUPPORT_ALIASES_PREVENT_ADDING_AS_FUNCTION_ARGUMENT
	public: unordered_map<string, string>* getFunctionAliasClassList();
	public: void initialiseFunctionAliasClassList();
	public: bool findEntityNameInFunctionAliasList(const string aliasName, string* aliasClassName);
	#endif
	#endif

	public: NLCcodeblock* createCodeBlockDebug(NLCcodeblock* currentCodeBlockInTree, const string warning);

	#ifdef NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY
	public: string generateCategoryListPropertyCountVariableName(const GIAentityNode* entity);
	#endif

	public: NLCcodeblock* clearCodeBlock(NLCcodeblock* codeBlock);
	public: NLCcodeblock* getLastCodeBlockInLevel(NLCcodeblock* currentCodeBlockInTree);
	public: NLCcodeblock* getLastSetCodeBlockInLevel(NLCcodeblock* currentCodeBlockInTree);

	#ifdef NLC_NORMALISE_TWOWAY_PREPOSITIONS
	public: GIAentityNode* generateInverseConditionEntity(const GIAentityNode* conditionRelationshipEntity);
	#endif

	#ifdef NLC_REDEFINITIONS
	public: NLCcodeblock* createCodeBlockCheckParentClassNameExecuteFunction1(NLCcodeblock* currentCodeBlockInTree, const string objectInstanceName, const string classNameToFind);
	public: NLCcodeblock* createCodeBlockCheckParentClassNameExecuteFunction1(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* object, const string classNameToFind);
	public: NLCcodeblock* createCodeBlockCheckParentClassNameExecuteFunction2(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* object, const string classNameToFind);
	public: NLCcodeblock* createCodeBlockCheckParentClassNameNewFunction(NLCcodeblock* currentCodeBlockInTree);
	public: NLCcodeblock* createCodeConvertParentToChildClass(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* parentEntity, const GIAentityNode* childEntity);
	#endif


	private: NLCcodeblock* createCodeBlockDeclareTempVariable(NLCcodeblock* currentCodeBlockInTree, const string tempVariableClassName, const string tempVariableInstanceName);
	private: NLCcodeblock* createCodeBlockSetTempVariable(NLCcodeblock* currentCodeBlockInTree, const string tempVariableInstanceName, const GIAentityNode* entity);
	public: NLCcodeblock* createCodeBlockDeclareTempVariableAndSetToEntity(NLCcodeblock* currentCodeBlockInTree, const string tempVariableClassName, const string tempVariableInstanceName, const GIAentityNode* entity);
	public: NLCcodeblock* createCodeBlockIfTempVariableEqualsEntity(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity1, const GIAentityNode* entity2);
	public: NLCcodeblock* createCodeBlockIfTempVariableEqualsEntity(NLCcodeblock* currentCodeBlockInTree, const string tempVariableClassName, const string tempVariableInstanceName, const GIAentityNode* entity);

	#ifdef NLC_NON_LIBRARY_FUNCTIONS_EXTENDED
	public: NLCcodeblock* createCodeBlockAddPropertyNewFunction(NLCcodeblock* currentCodeBlockInTree);
	public: NLCcodeblock* createCodeBlockAddConditionNewFunction(NLCcodeblock* currentCodeBlockInTree);
	#ifdef NLC_NORMALISE_TWOWAY_PREPOSITIONS_MARK_INVERSE_CONDITIONS
	private: NLCcodeblock* createCodeBlockAddConditionInverseNewFunction(NLCcodeblock* currentCodeBlockInTree);
	#endif
	#endif

	#ifdef NLC_MATH_OBJECTS
	public: NLCcodeblock* createCodeBlockTestMathObjectNumericalValue(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const GIAentityNode* valueEntity);
	public: NLCcodeblock* createCodeBlockSetMathObjectNumericalValue(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const GIAentityNode* valueEntity);
	public: NLCcodeblock* createCodeBlockDeclareNewDecimalPointerVar(NLCcodeblock* currentCodeBlockInTree, const string decimalPointerVariableName);
	public: NLCcodeblock* createCodeBlockSetDecimalPointerToEntityMathObjectNumericalValue(NLCcodeblock* currentCodeBlockInTree, const string decimalPointerVariableName, const GIAentityNode* entity);
	public: NLCcodeblock* createCodeBlockSetMathObjectTypeAsNumerical(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity);
	#ifdef NLC_MATH_OBJECTS_ADVANCED
	public: NLCcodeblock* createCodeBlockDeclareNewGenericEntityPointerVar(NLCcodeblock* currentCodeBlockInTree, const string genericEntityPointerVariableName);
	public: NLCcodeblock* createCodeBlockSetGenericEntityPointerToEntity(NLCcodeblock* currentCodeBlockInTree, const string genericEntityPointerVariableName, const GIAentityNode* entity);
	#ifdef NLC_MATH_OBJECTS_STRING
	private: NLCcodeblock* createCodeBlockSetMathObjectStringValue(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const GIAentityNode* valueEntity);
	public: NLCcodeblock* createCodeBlockDeclareNewStringPointerVar(NLCcodeblock* currentCodeBlockInTree, const string stringPointerVariableName);
	public: NLCcodeblock* createCodeBlockSetStringPointerToEntityMathObjectStringValue(NLCcodeblock* currentCodeBlockInTree, const string stringPointerVariableName, const GIAentityNode* entity);
	public: NLCcodeblock* createCodeBlockSetMathObjectTypeAsString(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity);
	#endif
	#ifdef NLC_MATH_OBJECTS_BOOLEAN
	private: NLCcodeblock* createCodeBlockSetMathObjectBooleanValue(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const GIAentityNode* valueEntity);
	public: NLCcodeblock* createCodeBlockDeclareNewBooleanPointerVar(NLCcodeblock* currentCodeBlockInTree, const string booleanPointerVariableName);
	public: NLCcodeblock* createCodeBlockSetBooleanPointerToEntityMathObjectBooleanValue(NLCcodeblock* currentCodeBlockInTree, const string booleanPointerVariableName, const GIAentityNode* entity);
	public: NLCcodeblock* createCodeBlockSetMathObjectTypeAsBoolean(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity);
	#endif
	#endif
	#ifdef NLC_MATH_OBJECTS_TEST_NULL_POINTER_MAINTAIN_CONTEXT
	public: NLCcodeblock* createCodeBlockTestDecimalPointerValue(NLCcodeblock* currentCodeBlockInTree, const string decimalPointerVariableName);
	#else
	public: NLCcodeblock* createCodeBlockCheckDecimalPointerValue(NLCcodeblock* currentCodeBlockInTree, const string decimalPointerVariableName);
	#endif
	#endif

	public: NLCcodeblock* createCodeBlockIfTempVariableNameEqualsClassName(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const string className);


	#ifdef NLC_REFERENCING_OBJECTS_IN_PLURAL_LIST_BY_NUMBER
	private: bool checkNumericalReferenceToEntity(const GIAentityNode* entity);
	#endif

	#ifdef NLC_TRANSLATOR_TEST_DEFINITE_ENTITY_EXISTENCE
	public: NLCcodeblock* createCodeVerifyDefiniteReferenceExistenceNewFunction(NLCcodeblock* currentCodeBlockInTree);
	public: NLCcodeblock* createCodeVerifyDefiniteReferenceExistenceExecuteFunction(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const string genericListAppendName, const int sentenceIndex);
	#endif

	public: GIAentityNode* getSameReferenceSetSubstanceNonQualityChild(GIAentityNode* parentEntity, int sentenceIndex, bool *foundChildEntity);
	
	#ifdef NLC_ADVANCED_REFERENCING_SUPPORT_ALIASES_MERGERS
	public: NLCcodeblock* createCodeBlockRemoveEntityFromLocalListExecuteFunction(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity);
	public: NLCcodeblock* createCodeBlockReplaceEntityInLocalListExecuteFunction(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity1, const GIAentityNode* entity2);	//replace entity1 with entity2
	public: NLCcodeblock* createCodeBlocksMergeEntity1AttributesIntoEntity2ExecuteFunction(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity1, const GIAentityNode* entity2);
	#endif
};

#endif
