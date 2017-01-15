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
 * File Name: NLCcodeBlockClass.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2015 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 1q14f 02-September-2015
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/


#include "NLCcodeBlockClass.h"
#include "NLCprintDefs.h"	//required for progLangArrayOpen/progLangArrayClose/NLC_ITEM_TYPE_PROPERTYCOUNT_VAR_APPENDITION/NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION
#include "GIAtranslatorOperations.h"
#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS_SUPPORT_LOCAL_LISTS_USE_CLASS_NAMES_ADVANCED
#include "GIAtranslatorDefineReferencing.h"
#endif

//#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED || NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT
static int currentLogicalConditionLevel;
int getCurrentLogicalConditionLevel()
{
	return currentLogicalConditionLevel;
}
void setCurrentLogicalConditionLevel(int value)
{
	currentLogicalConditionLevel = value;
}

NLCcodeblock::NLCcodeblock(void)
{
	codeBlockType = NLC_CODEBLOCK_TYPE_UNDEFINED;

	/*
	//used by language specific code generator (eg C++, java);
	codeBlockName = ""; 	//eg "for"
	openingText = "";	//eg "for(...){"
	closingText = ""; 	//eg "}";
	*/

	lowerLevel = NULL;
	next = NULL;
	
	#ifdef NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT
	isLogicalCondition = false;
	contextLevel = 0;
	#endif
}
NLCcodeblock::~NLCcodeblock(void)
{
}

NLCgenerateContextBlocksVariables::NLCgenerateContextBlocksVariables(void)
{
	logicalOperation = NLC_LOGICAL_CONDITION_OPERATIONS_FOR;
	//#ifndef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS_ADVANCED
	negative = BOOL_IRRELEVANT;
	//#endif
	#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS_ADVANCED
	logicalConditionConjunctionIndex = INT_DEFAULT_VALUE;
	primaryEntityInLogicalConditionConjunctionSubset = NULL;
	foundLogicalConditionConjunction = NULL;
	#endif
	#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
	onlyGenerateContextBlocksIfConnectionsParsedForNLCorSameReferenceSet = false;
	#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_BASIC_GENERATE_CONTEXT_BLOCKS_IF_SAME_REFERENCE_SET
	generateContextBlocksIfSameReferenceSet = true;
	#endif
	#endif
	#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
	negativeDetectedInContextBlocks = false;
	#ifndef NLC_GENERATE_UNIQUE_CONTEXT_BLOCK_FOR_EACH_SENTENCE_LOGICAL_CONDITIONS_FOR_LOOPS
	setCodeBlockInTreeAtBaseLevel = false;
	currentCodeBlockInTreeAtBaseLevel = NULL;
	#endif
	#endif
	#ifdef NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY
	testNumerosity = false;
	childQuantity = 1;
	#endif
	#ifdef NLC_FUNCTIONS_SUPPORT_PLURAL_SUBJECTS_AND_OBJECTS
	enterGeneratedCategoryList = true;
	#endif
	#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN
	searchSubstanceConceptsForChildren = true;
	#endif
	#ifdef NLC_PARSE_CONDITION_PARENTS
	parseConditionParents = true;
	#endif
	#ifdef NLC_TRANSLATOR_GENERATE_CONTEXT_BLOCKS_PARSE_PARENT_EFFICIENT
	parseParentEfficient = false;
	childEntityNotToParse = NULL;
	#endif
	getParentCheckLastParent = false;
	lastParent = NULL;
}
NLCgenerateContextBlocksVariables::~NLCgenerateContextBlocksVariables(void)
{
}

#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS_ADVANCED
NLClogicalConditionConjunction::NLClogicalConditionConjunction(void)
{
	conjunctionType = INT_DEFAULT_VALUE;
	negative = false;
}
NLClogicalConditionConjunction::~NLClogicalConditionConjunction(void)
{
}
#endif


//Resultant code: functionItem[context].functionItem[name](objectItem[context].objectItem[name]);	//NB functionItem[context] = action subject
NLCcodeblock* createCodeBlockExecuteSubjectObject(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* actionEntity, GIAentityNode* subjectEntity, GIAentityNode* objectEntity, int sentenceIndex)
{
	NLCitem* functionItem = new NLCitem(actionEntity, NLC_ITEM_TYPE_FUNCTION_EXECUTION_ARGUMENT_FUNCTION, sentenceIndex);
	NLCitem* functionSubjectItem = new NLCitem(subjectEntity, NLC_ITEM_TYPE_FUNCTION_EXECUTION_ARGUMENT_FUNCTION_OWNER, sentenceIndex);
	NLCitem* functionObjectItem = new NLCitem(objectEntity, NLC_ITEM_TYPE_FUNCTION_EXECUTION_ARGUMENT_FUNCTION_OBJECT, sentenceIndex);

	currentCodeBlockInTree->parameters.push_back(functionSubjectItem);
	currentCodeBlockInTree->parameters.push_back(functionItem);
	currentCodeBlockInTree->parameters.push_back(functionObjectItem);

	return createCodeBlock(currentCodeBlockInTree, NLC_CODEBLOCK_TYPE_EXECUTE_FUNCTION);
}

NLCcodeblock* createCodeBlockExecuteSubject(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* actionEntity, GIAentityNode* subjectEntity, int sentenceIndex)
{
	NLCitem* functionItem = new NLCitem(actionEntity, NLC_ITEM_TYPE_FUNCTION_EXECUTION_ARGUMENT_FUNCTION, sentenceIndex);
	NLCitem* functionSubjectItem = new NLCitem(subjectEntity, NLC_ITEM_TYPE_FUNCTION_EXECUTION_ARGUMENT_FUNCTION_OWNER, sentenceIndex);
	
	currentCodeBlockInTree->parameters.push_back(functionSubjectItem);
	currentCodeBlockInTree->parameters.push_back(functionItem);

	return createCodeBlock(currentCodeBlockInTree, NLC_CODEBLOCK_TYPE_EXECUTE_FUNCTION);
}

NLCcodeblock* createCodeBlockExecuteObject(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* actionEntity, GIAentityNode* objectEntity, int sentenceIndex)
{
	NLCitem* functionItem = new NLCitem(actionEntity, NLC_ITEM_TYPE_FUNCTION_EXECUTION_ARGUMENT_FUNCTION, sentenceIndex);
	NLCitem* functionObjectItem = new NLCitem(objectEntity, NLC_ITEM_TYPE_FUNCTION_EXECUTION_ARGUMENT_FUNCTION_OBJECT, sentenceIndex);
	
	currentCodeBlockInTree->parameters.push_back(functionItem);
	currentCodeBlockInTree->parameters.push_back(functionObjectItem);

	return createCodeBlock(currentCodeBlockInTree, NLC_CODEBLOCK_TYPE_EXECUTE_FUNCTION);
}

NLCcodeblock* createCodeBlockExecute(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* actionEntity, int sentenceIndex)
{
	NLCitem* functionItem = new NLCitem(actionEntity, NLC_ITEM_TYPE_FUNCTION_EXECUTION_ARGUMENT_FUNCTION, sentenceIndex);

	currentCodeBlockInTree->parameters.push_back(functionItem);

	return createCodeBlock(currentCodeBlockInTree, NLC_CODEBLOCK_TYPE_EXECUTE_FUNCTION);
}

#ifdef NLC_RECORD_ACTION_HISTORY
NLCcodeblock* createCodeBlockRecordHistoryActionSubject(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* actionEntity, GIAentityNode* subjectEntity)
{
	NLCitem* functionItem = new NLCitem(actionEntity, NLC_ITEM_TYPE_FUNCTION_EXECUTION_ARGUMENT_FUNCTION);
	NLCitem* functionSubjectItem = new NLCitem(subjectEntity, NLC_ITEM_TYPE_FUNCTION_EXECUTION_ARGUMENT_FUNCTION_OWNER);

	currentCodeBlockInTree->parameters.push_back(functionSubjectItem);
	currentCodeBlockInTree->parameters.push_back(functionItem);

	return createCodeBlock(currentCodeBlockInTree, NLC_CODEBLOCK_TYPE_RECORD_HISTORY_ACTION_SUBJECT);
}

NLCcodeblock* createCodeBlockRecordHistoryActionObject(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* actionEntity, GIAentityNode* objectEntity)
{
	NLCitem* functionItem = new NLCitem(actionEntity, NLC_ITEM_TYPE_FUNCTION_EXECUTION_ARGUMENT_FUNCTION);
	NLCitem* functionObjectItem = new NLCitem(objectEntity, NLC_ITEM_TYPE_FUNCTION_EXECUTION_ARGUMENT_FUNCTION_OBJECT);

	currentCodeBlockInTree->parameters.push_back(functionItem);
	currentCodeBlockInTree->parameters.push_back(functionObjectItem);

	return createCodeBlock(currentCodeBlockInTree, NLC_CODEBLOCK_TYPE_RECORD_HISTORY_ACTION_OBJECT);
}
#endif


//add property

NLCcodeblock* createCodeBlockCreateNewProperty(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* propertyEntity, int sentenceIndex, bool copyNewItemsToLocalList)
{	
	#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_BLOCKS_FOR_PARENT_INITIALISATION_SPECIAL
	currentCodeBlockInTree = createCodeBlocksDeclareNewCategoryListVariable(currentCodeBlockInTree, propertyEntity, NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION, sentenceIndex);	//create new category list
	#endif
	currentCodeBlockInTree = createCodeBlockAddNewProperty(currentCodeBlockInTree, entity, propertyEntity, sentenceIndex, copyNewItemsToLocalList);
	return currentCodeBlockInTree;
}

NLCcodeblock* createCodeBlockAddNewProperty(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* propertyEntity, int sentenceIndex, bool copyNewItemsToLocalList)
{
	#ifdef NLC_SUPPORT_QUANTITIES
	NLCcodeblock* origCurrentCodeBlockInTree = currentCodeBlockInTree;
	if(propertyEntity->quantityNumber > 1)
	{
		string numberIterationsOrVariable = convertIntToString(propertyEntity->quantityNumber);
		#ifdef NLC_PREPROCESSOR_MATH_REPLACE_NUMERICAL_VARIABLES_NAMES_FOR_NLP
		if(propertyEntity->NLCoriginalNumericalVariableName != "")
		{
			numberIterationsOrVariable = propertyEntity->NLCoriginalNumericalVariableName;
		}
		#endif
		currentCodeBlockInTree = createCodeBlockForInteger(currentCodeBlockInTree, numberIterationsOrVariable);
	}
	//for(int i=0; i<propertyEntity->quantityNumber; i++)
	//{
	#endif

	NLCitem* entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	NLCitem* propertyItem = new NLCitem(propertyEntity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(propertyItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_ADD_NEW_PROPERTY;
	currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);

	#ifdef NLC_DEFINE_LOCAL_VARIABLES_FOR_ALL_INDEFINATE_ENTITIES
	if(copyNewItemsToLocalList)
	{
		//cout << "copyNewItemsToLocalList: entity->entityName = " << entity->entityName << endl;	
		if(propertyEntity->NLClocalListVariableHasBeenDeclared)
		{//added 1g8a 11-July-2014
			currentCodeBlockInTree = createCodeBlockAddEntityToLocalList(currentCodeBlockInTree, propertyEntity, propertyEntity);
			propertyEntity->NLClocalListVariableHasBeenInitialised = true;

			#ifdef NLC_DEBUG
			//string debugString = string("10createCodeBlockAddNewProperty") + entity->entityName + string(" ") + convertIntToString(entity->NLClocalListVariableHasBeenInitialised) + string(" ") + propertyEntity->entityName + string(" ") + convertIntToString(propertyEntity->NLClocalListVariableHasBeenInitialised);
			//currentCodeBlockInTree = createCodeBlockDebug(currentCodeBlockInTree, debugString);
			//cout << debugString << endl;
			#endif
			//cout << "(propertyEntity->NLClocalListVariableHasBeenDeclared): entity->entityName = " << entity->entityName << endl;	
		}
		else
		{
			//cout << "!(propertyEntity->NLClocalListVariableHasBeenDeclared): entity->entityName = " << entity->entityName << endl;	
		}
	}
	else
	{
		//cout << "!copyNewItemsToLocalList: entity->entityName = " << entity->entityName << endl;	
	}
	#endif

	#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_BLOCKS_FOR_PARENT_INITIALISATION_SPECIAL
	currentCodeBlockInTree = createCodeBlockAddEntityToCategoryList(currentCodeBlockInTree, propertyEntity, propertyEntity, NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION, sentenceIndex);	//add new object to category list
	#endif
	#ifdef NLC_USE_ADVANCED_REFERENCING
	#ifdef NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT
	currentCodeBlockInTree =  createCodeBlocksAddEntityToContextLevelListExecuteFunction(currentCodeBlockInTree, getCurrentLogicalConditionLevel(), propertyEntity, sentenceIndex);
	#else
	currentCodeBlockInTree = createCodeBlockUpdateLastSentenceReferenced(currentCodeBlockInTree, propertyEntity, sentenceIndex);
	#endif
	#endif

	#ifdef NLC_SUPPORT_QUANTITIES
	if(propertyEntity->quantityNumber > 1)
	{
		currentCodeBlockInTree = origCurrentCodeBlockInTree->next;
	}
	//}
	#endif

	return currentCodeBlockInTree;
}

NLCcodeblock* createCodeBlockAddNewEntityToLocalList(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, int sentenceIndex, bool addReferencingContext)
{
	#ifdef NLC_SUPPORT_QUANTITIES
	NLCcodeblock* origCurrentCodeBlockInTree = currentCodeBlockInTree;
	if(entity->quantityNumber > 1)
	{
		string numberIterationsOrVariable = convertIntToString(entity->quantityNumber);
		#ifdef NLC_PREPROCESSOR_MATH_REPLACE_NUMERICAL_VARIABLES_NAMES_FOR_NLP
		if(entity->NLCoriginalNumericalVariableName != "")
		{
			numberIterationsOrVariable = entity->NLCoriginalNumericalVariableName;
		}
		#endif
		currentCodeBlockInTree = createCodeBlockForInteger(currentCodeBlockInTree, numberIterationsOrVariable);
	}
	//for(int i=0; i<entity->quantityNumber; i++)
	//{
	#endif

	int codeBlockType;
	#ifdef NLC_DO_NOT_CREATE_LOCAL_LISTS_FOR_QUALITIES
	if(entity->isSubstanceQuality)
	{
		codeBlockType = NLC_CODEBLOCK_TYPE_DECLARE_NEW_VARIABLE;
	}
	else
	{
	#endif
		codeBlockType = NLC_CODEBLOCK_TYPE_ADD_NEW_ENTITY_TO_LOCAL_LIST;
	#ifdef NLC_DO_NOT_CREATE_LOCAL_LISTS_FOR_QUALITIES	
	}
	#endif
	NLCitem* entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(entityItem);
	currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);
		
	if(addReferencingContext)
	{
		#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_BLOCKS_FOR_PARENT_INITIALISATION_SPECIAL
		currentCodeBlockInTree = createCodeBlockAddEntityToCategoryList(currentCodeBlockInTree, entity, entity, NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION, sentenceIndex);	//add new object to category list
		#endif
		#ifdef NLC_USE_ADVANCED_REFERENCING
		#ifdef NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT
		currentCodeBlockInTree =  createCodeBlocksAddEntityToContextLevelListExecuteFunction(currentCodeBlockInTree, getCurrentLogicalConditionLevel(), entity, sentenceIndex);
		#else
		currentCodeBlockInTree = createCodeBlockUpdateLastSentenceReferenced(currentCodeBlockInTree, entity, sentenceIndex);
		#endif
		#endif
	}

	#ifdef NLC_SUPPORT_QUANTITIES
	if(entity->quantityNumber > 1)
	{
		currentCodeBlockInTree = origCurrentCodeBlockInTree->next;
	}
	//}
	#endif

	return currentCodeBlockInTree;
}

NLCcodeblock* createCodeBlockAddEntityToLocalList(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* propertyEntity)
{
	NLCitem* entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	NLCitem* propertyItem = new NLCitem(propertyEntity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(propertyItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_LOCAL_LIST;
	currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}

NLCcodeblock* createCodeBlockAddProperty(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* propertyEntity, int sentenceIndex)
{
	NLCitem* entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	NLCitem* propertyItem = new NLCitem(propertyEntity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(propertyItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_ADD_PROPERTY;
	currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}



NLCcodeblock* createCodeBlockCreateNewCondition(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* conditionEntity, int sentenceIndex, bool copyNewItemsToLocalList)
{	
	#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_BLOCKS_FOR_PARENT_INITIALISATION_SPECIAL
	if(!(conditionEntity->conditionObjectEntity->empty()))
	{
		GIAentityNode* conditionObject = (conditionEntity->conditionObjectEntity->back())->entity;
		currentCodeBlockInTree = createCodeBlocksDeclareNewCategoryListVariable(currentCodeBlockInTree, conditionObject, NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION, sentenceIndex);	//create new category list
	}
	#endif
	currentCodeBlockInTree = createCodeBlockAddNewCondition(currentCodeBlockInTree, entity, conditionEntity, sentenceIndex, copyNewItemsToLocalList);
	return currentCodeBlockInTree;
}


NLCcodeblock* createCodeBlockAddNewCondition(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* conditionEntity, int sentenceIndex, bool copyNewItemsToLocalList)
{
	if(!(conditionEntity->conditionObjectEntity->empty()))
	{
		GIAentityNode* conditionObject = (conditionEntity->conditionObjectEntity->back())->entity;

		#ifdef NLC_SUPPORT_QUANTITIES
		NLCcodeblock* origCurrentCodeBlockInTree = currentCodeBlockInTree;
		if(conditionObject->quantityNumber > 1)
		{
			string numberIterationsOrVariable = convertIntToString(conditionObject->quantityNumber);
			#ifdef NLC_PREPROCESSOR_MATH_REPLACE_NUMERICAL_VARIABLES_NAMES_FOR_NLP
			if(conditionObject->NLCoriginalNumericalVariableName != "")
			{
				numberIterationsOrVariable = conditionObject->NLCoriginalNumericalVariableName;
			}
			#endif
			currentCodeBlockInTree = createCodeBlockForInteger(currentCodeBlockInTree, numberIterationsOrVariable);
		}
		//for(int i=0; i<conditionObject->quantityNumber; i++)
		//{
		#endif

		currentCodeBlockInTree = createCodeBlockAddNewConditionSimple(currentCodeBlockInTree, entity, conditionEntity, conditionObject);
		#ifdef NLC_NORMALISE_TWOWAY_PREPOSITIONS
		if(conditionEntity->conditionTwoWay)
		{
			GIAentityNode* entityInverse = conditionObject;
			GIAentityNode* conditionEntityInverse = NULL;
			conditionEntityInverse = generateInverseConditionEntity(conditionEntity);
			#ifdef NLC_DEBUG
			cout << "conditionEntityInverse: conditionEntity = " << conditionEntity->entityName << endl;
			#endif
			currentCodeBlockInTree = createCodeBlockAddConditionSimpleInverse(currentCodeBlockInTree, conditionObject, conditionEntityInverse, entity);
		}
		#endif

		#ifdef NLC_DEFINE_LOCAL_VARIABLES_FOR_ALL_INDEFINATE_ENTITIES
		if(copyNewItemsToLocalList)
		{
			if(conditionObject->NLClocalListVariableHasBeenDeclared)
			{//added 1g8a 11-July-2014
				currentCodeBlockInTree = createCodeBlockAddEntityToLocalList(currentCodeBlockInTree, conditionObject, conditionObject);
				conditionObject->NLClocalListVariableHasBeenInitialised = true;

				#ifdef NLC_DEBUG
				//string debugString = string("11createCodeBlockAddNewCondition") + entity->entityName + string(" ") + convertIntToString(entity->NLClocalListVariableHasBeenInitialised) + string(" ") + conditionObject->entityName + string(" ") + convertIntToString(conditionObject->NLClocalListVariableHasBeenInitialised);
				//currentCodeBlockInTree = createCodeBlockDebug(currentCodeBlockInTree, debugString);
				//cout << debugString << endl;
				#endif
			}
		}
		#endif

		#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_BLOCKS_FOR_PARENT_INITIALISATION_SPECIAL
		currentCodeBlockInTree = createCodeBlockAddEntityToCategoryList(currentCodeBlockInTree, conditionObject, conditionObject, NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION, sentenceIndex);	//add new object to category list
		#endif
		#ifdef NLC_USE_ADVANCED_REFERENCING
		#ifdef NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT
		currentCodeBlockInTree =  createCodeBlocksAddEntityToContextLevelListExecuteFunction(currentCodeBlockInTree, getCurrentLogicalConditionLevel(), conditionObject, sentenceIndex);
		#else
		currentCodeBlockInTree = createCodeBlockUpdateLastSentenceReferenced(currentCodeBlockInTree, conditionObject, sentenceIndex);
		#endif
		#endif

		#ifdef NLC_SUPPORT_QUANTITIES
		if(conditionObject->quantityNumber > 1)
		{
			currentCodeBlockInTree = origCurrentCodeBlockInTree->next;
		}
		//}
		#endif
	}
	else
	{
		cout << "error: condition does not have object" << endl;
	}

	return currentCodeBlockInTree;
}

NLCcodeblock* createCodeBlockAddNewConditionSimple(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* conditionEntity, GIAentityNode* conditionObject)
{
	NLCitem* entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	NLCitem* conditionItem = new NLCitem(conditionEntity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(conditionItem);

	NLCitem* conditionObjectItem = new NLCitem(conditionObject, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(conditionObjectItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_ADD_NEW_CONDITION;
	currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);
	
	return currentCodeBlockInTree;
}

NLCcodeblock* createCodeBlockAddCondition(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* conditionEntity, int sentenceIndex)
{
	if(!(conditionEntity->conditionObjectEntity->empty()))
	{
		GIAentityNode* conditionObject = (conditionEntity->conditionObjectEntity->back())->entity;
		
		currentCodeBlockInTree = createCodeBlockAddConditionSimple(currentCodeBlockInTree, entity, conditionEntity, conditionObject);
		#ifdef NLC_NORMALISE_TWOWAY_PREPOSITIONS
		if(conditionEntity->conditionTwoWay)
		{
			GIAentityNode* entityInverse = conditionObject;
			GIAentityNode* conditionEntityInverse = NULL;
			conditionEntityInverse = generateInverseConditionEntity(conditionEntity);
			#ifdef NLC_DEBUG
			cout << "conditionEntityInverse: conditionEntity = " << conditionEntity->entityName << endl;
			#endif
			currentCodeBlockInTree = createCodeBlockAddConditionSimpleInverse(currentCodeBlockInTree, conditionObject, conditionEntityInverse, entity);
		}
		#endif
	}
	else
	{
		cout << "error: condition does not have object" << endl;
	}

	return currentCodeBlockInTree;
}

NLCcodeblock* createCodeBlockAddConditionSimple(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* conditionEntity, GIAentityNode* conditionObject)
{
	NLCitem* entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
	//removed 1e7c as it is not used: getEntityContext(entity, &(entityItem->context), false, sentenceIndex, false);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	NLCitem* conditionItem = new NLCitem(conditionEntity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(conditionItem);

	NLCitem* conditionObjectItem = new NLCitem(conditionObject, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(conditionObjectItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_ADD_CONDITION;
	currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);
	
	return currentCodeBlockInTree;
}

#ifdef NLC_NORMALISE_TWOWAY_PREPOSITIONS_MARK_INVERSE_CONDITIONS	
NLCcodeblock* createCodeBlockAddConditionSimpleInverse(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* conditionEntity, GIAentityNode* conditionObject)
{
	#ifdef NLC_NORMALISE_TWOWAY_PREPOSITIONS_MARK_INVERSE_CONDITIONS
	NLCitem* entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
	//removed 1e7c as it is not used: getEntityContext(entity, &(entityItem->context), false, sentenceIndex, false);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	NLCitem* conditionItem = new NLCitem(conditionEntity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(conditionItem);

	NLCitem* conditionObjectItem = new NLCitem(conditionObject, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(conditionObjectItem);
	
	int codeBlockType = NLC_CODEBLOCK_TYPE_ADD_CONDITION_INVERSE;
	currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);
	#else
	currentCodeBlockInTree = createCodeBlockAddConditionSimple(currentCodeBlockInTree, entity, conditionEntity, conditionObject);
	#endif
	return currentCodeBlockInTree;
}
#endif


NLCcodeblock* createCodeBlocksCreateNewLocalListVariable(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, int sentenceIndex)
{
	#ifdef NLC_DO_NOT_CREATE_LOCAL_LISTS_FOR_QUALITIES
	if(!(entity->isSubstanceQuality))
	{	
	#endif
		currentCodeBlockInTree = createCodeBlocksDeclareNewLocalListVariableIfNecessary(currentCodeBlockInTree, entity);
	#ifdef NLC_DO_NOT_CREATE_LOCAL_LISTS_FOR_QUALITIES
	}
	#endif
	#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_BLOCKS_FOR_PARENT_INITIALISATION_SPECIAL
	currentCodeBlockInTree = createCodeBlocksDeclareNewCategoryListVariable(currentCodeBlockInTree, entity, NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION, sentenceIndex);	//create new category list
	#endif
	currentCodeBlockInTree = createCodeBlockAddNewEntityToLocalList(currentCodeBlockInTree, entity, sentenceIndex, true);
	return currentCodeBlockInTree;
}

NLCcodeblock* createCodeBlocksDeclareNewLocalListVariableIfNecessary(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity)
{
	bool setNLCLocalListVariableHasBeenDeclared = true;
	#ifdef NLC_GENERATE_UNIQUE_CONTEXT_BLOCK_FOR_EACH_SENTENCE
	if(entity->isAction)
	{
		setNLCLocalListVariableHasBeenDeclared = false;
	}
	#endif
	#ifdef NLC_DO_NOT_PREDECLARE_LOCAL_LISTS_FOR_QUALITIES
	#ifndef NLC_DO_NOT_CREATE_LOCAL_LISTS_FOR_QUALITIES
	if(entity->isSubstanceQuality)
	{
		setNLCLocalListVariableHasBeenDeclared = false;
	}	
	#endif
	#endif
	
	if(setNLCLocalListVariableHasBeenDeclared)
	{	
		#ifdef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES
		if(!(entity->NLClocalListVariableHasBeenDeclared))
		{//added 1g8a 11-July-2014
			entity->NLClocalListVariableHasBeenDeclared = true;
		#else
		entity->NLClocalListVariableHasBeenDeclared = true;	//added 1n4a
		GIAentityNode* conceptEntity = getPrimaryConceptNodeDefiningInstance(entity);
		if(!(conceptEntity->NLClocalListVariableHasBeenDeclared))
		{

			conceptEntity->NLClocalListVariableHasBeenDeclared = true;
		#endif

			currentCodeBlockInTree = createCodeBlocksDeclareNewLocalListVariable(currentCodeBlockInTree, entity, setNLCLocalListVariableHasBeenDeclared);
		}
	}
	else
	{
		currentCodeBlockInTree = createCodeBlocksDeclareNewLocalListVariable(currentCodeBlockInTree, entity, setNLCLocalListVariableHasBeenDeclared);
	}
	
	return currentCodeBlockInTree;
}

NLCcodeblock* createCodeBlocksDeclareNewLocalListVariable(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, bool createTypeList)
{	
	NLCitem* entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_DECLARE_NEW_LOCAL_LIST_VARIABLE;
	currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);

	#ifdef NLC_GENERATE_TYPE_LISTS
	if(createTypeList)
	{
		#ifdef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES
		if(!(getPrimaryConceptNodeDefiningInstance(entity)->NLClocalListVariableHasBeenDeclared))	//ie typeList has not been declared (NLC_LOCAL_LISTS_USE_INSTANCE_NAMES:conceptEntity->NLClocalListVariableHasBeenDeclared)
		{	
		#endif
			//declare a generic type list (typeList) of local instance lists (instanceLists)
			currentCodeBlockInTree = createCodeBlocksDeclareNewTypeListVariable(currentCodeBlockInTree, entity);

			//add local instance list to generic type list		
			currentCodeBlockInTree = createCodeBlockAddInstanceListToTypeList(currentCodeBlockInTree, entity, entity);

		#ifdef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES
			getPrimaryConceptNodeDefiningInstance(entity)->NLClocalListVariableHasBeenDeclared = true;	//ie typeList has been declared (NLC_LOCAL_LISTS_USE_INSTANCE_NAMES:conceptEntity->NLClocalListVariableHasBeenDeclared)
		}
		#endif
	}
	#endif
	
	return currentCodeBlockInTree;
}


NLCcodeblock* createCodeBlockForOrInPropertyList(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, string context)
{
	#ifdef NLC_USE_SUPPORT_REFERENCING_OBJECTS_IN_PLURAL_LIST_BY_NUMBER
	if(checkNumericalReferenceToEntity(entity))
	{
		currentCodeBlockInTree = createCodeBlockInPropertyList(currentCodeBlockInTree, entity, context, entity->quantityNumber);
	}
	else
	{
	#endif
		currentCodeBlockInTree = createCodeBlockForPropertyList(currentCodeBlockInTree, entity, context);	
	#ifdef NLC_USE_SUPPORT_REFERENCING_OBJECTS_IN_PLURAL_LIST_BY_NUMBER
	}
	#endif
	return currentCodeBlockInTree;
}
NLCcodeblock* createCodeBlockForOrInPropertyList(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity)
{
	#ifdef NLC_USE_SUPPORT_REFERENCING_OBJECTS_IN_PLURAL_LIST_BY_NUMBER
	if(checkNumericalReferenceToEntity(entity))
	{
		currentCodeBlockInTree = createCodeBlockInPropertyList(currentCodeBlockInTree, entity, entity->quantityNumber);	
	}
	else
	{
	#endif
		currentCodeBlockInTree = createCodeBlockForPropertyList(currentCodeBlockInTree, entity);	
	#ifdef NLC_USE_SUPPORT_REFERENCING_OBJECTS_IN_PLURAL_LIST_BY_NUMBER
	}
	#endif
	return currentCodeBlockInTree;
}		

NLCcodeblock* createCodeBlockForPropertyList(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, string context)
{
	NLCitem* item = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
	item->context.push_back(context);
	return createCodeBlockForPropertyList(currentCodeBlockInTree, item);
}
NLCcodeblock* createCodeBlockForPropertyList(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity)
{
	NLCitem* item = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
	return createCodeBlockForPropertyList(currentCodeBlockInTree, item);
}
NLCcodeblock* createCodeBlockForPropertyList(NLCcodeblock* currentCodeBlockInTree, NLCitem* item)
{
	currentCodeBlockInTree->parameters.push_back(item);
	int codeBlockType = NLC_CODEBLOCK_TYPE_FOR_PROPERTY_LIST;
	currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);
	#ifdef NLC_NONOO
	currentCodeBlockInTree = createCodeBlockIfPropertyName(currentCodeBlockInTree, item);	
	#endif
	return currentCodeBlockInTree;
}
		
#ifdef NLC_USE_SUPPORT_REFERENCING_OBJECTS_IN_PLURAL_LIST_BY_NUMBER
NLCcodeblock* createCodeBlockInPropertyList(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, int index)
{
	NLCitem* item = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(item);
	
	string intValueString = convertIntToString(index);
	NLCitem* intValueItem = new NLCitem(intValueString, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(intValueItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_IN_PROPERTY_LIST;
	return createCodeBlock(currentCodeBlockInTree, codeBlockType);
}
NLCcodeblock* createCodeBlockInPropertyList(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, string context, int index)
{
	NLCitem* item = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(item);
	item->context.push_back(context);
		
	string intValueString = convertIntToString(index);
	NLCitem* intValueItem = new NLCitem(intValueString, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(intValueItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_IN_PROPERTY_LIST;
	return createCodeBlock(currentCodeBlockInTree, codeBlockType);
}
#endif


NLCcodeblock* createCodeBlockForOrInLocalList(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity)
{
	#ifdef NLC_USE_SUPPORT_REFERENCING_OBJECTS_IN_PLURAL_LIST_BY_NUMBER
	if(checkNumericalReferenceToEntity(entity))
	{
		currentCodeBlockInTree = createCodeBlockInLocalList(currentCodeBlockInTree, entity, entity->quantityNumber);	
	}
	else
	{
	#endif
		currentCodeBlockInTree = createCodeBlockForLocalList(currentCodeBlockInTree, entity);	
	#ifdef NLC_USE_SUPPORT_REFERENCING_OBJECTS_IN_PLURAL_LIST_BY_NUMBER
	}
	#endif
	return currentCodeBlockInTree;
}

NLCcodeblock* createCodeBlockForLocalList(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity)
{
	NLCitem* item = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(item);
	int codeBlockType = NLC_CODEBLOCK_TYPE_FOR_LOCAL_LIST;
	return createCodeBlock(currentCodeBlockInTree, codeBlockType);
}

#ifdef NLC_USE_SUPPORT_REFERENCING_OBJECTS_IN_PLURAL_LIST_BY_NUMBER
NLCcodeblock* createCodeBlockInLocalList(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, int index)
{
	NLCitem* item = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(item);
	
	string intValueString = convertIntToString(index);
	NLCitem* intValueItem = new NLCitem(intValueString, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(intValueItem);
	
	int codeBlockType = NLC_CODEBLOCK_TYPE_IN_LOCAL_LIST;
	return createCodeBlock(currentCodeBlockInTree, codeBlockType);
}
#endif


NLCcodeblock* createCodeBlockForConditionList(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* condition, GIAentityNode* conditionObject, string context)
{
	NLCitem* conditionItem = new NLCitem(condition, NLC_ITEM_TYPE_OBJECT);
	NLCitem* conditionObjectItem = new NLCitem(conditionObject, NLC_ITEM_TYPE_OBJECT);
	conditionItem->context.push_back(context);
	conditionObjectItem->context.push_back(context);	//redundant
	return createCodeBlockForConditionList(currentCodeBlockInTree, conditionItem, conditionObjectItem);
}
NLCcodeblock* createCodeBlockForConditionList(NLCcodeblock* currentCodeBlockInTree, NLCitem* item, NLCitem* objectItem)
{
	currentCodeBlockInTree->parameters.push_back(item);
	currentCodeBlockInTree->parameters.push_back(objectItem);
	int codeBlockType = NLC_CODEBLOCK_TYPE_FOR_CONDITION_LIST;
	currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);
	#ifdef NLC_NONOO
	currentCodeBlockInTree = createCodeBlockIfConditionName(currentCodeBlockInTree, item, objectItem);		
	#endif
	return currentCodeBlockInTree;
}


#ifdef NLC_NONOO
NLCcodeblock* createCodeBlockIfPropertyName(NLCcodeblock* currentCodeBlockInTree, NLCitem* item)
{
	currentCodeBlockInTree->parameters.push_back(item);
	int codeBlockType = NLC_CODEBLOCK_TYPE_IF_PROPERTY_NAME;
	return createCodeBlock(currentCodeBlockInTree, codeBlockType);
}
NLCcodeblock* createCodeBlockIfConditionName(NLCcodeblock* currentCodeBlockInTree, NLCitem* item, NLCitem* objectItem)
{
	currentCodeBlockInTree->parameters.push_back(item);
	currentCodeBlockInTree->parameters.push_back(objectItem);
	int codeBlockType = NLC_CODEBLOCK_TYPE_IF_CONDITION_NAME;
	return createCodeBlock(currentCodeBlockInTree, codeBlockType);
}
#ifdef NLC_RECORD_ACTION_HISTORY
NLCcodeblock* createCodeBlockIfActionName(NLCcodeblock* currentCodeBlockInTree, NLCitem* item)
{
	currentCodeBlockInTree->parameters.push_back(item);
	int codeBlockType = NLC_CODEBLOCK_TYPE_IF_ACTION_NAME;
	return createCodeBlock(currentCodeBlockInTree, codeBlockType);
}
#endif
#endif

#ifdef NLC_RECORD_ACTION_HISTORY
NLCcodeblock* createCodeBlockForActionList(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, string context)
{
	NLCitem* item = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
	item->context.push_back(context);
		
	currentCodeBlockInTree->parameters.push_back(item);
	int codeBlockType = NLC_CODEBLOCK_TYPE_FOR_ACTION_LIST;
	currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);
	#ifdef NLC_NONOO
	currentCodeBlockInTree = createCodeBlockIfActionName(currentCodeBlockInTree, item);			
	#endif
	return currentCodeBlockInTree;
}
NLCcodeblock* createCodeBlockForActionIncomingList(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, string context)
{
	NLCitem* item = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
	item->context.push_back(context);
	
	currentCodeBlockInTree->parameters.push_back(item);
	int codeBlockType = NLC_CODEBLOCK_TYPE_FOR_ACTION_INCOMING_LIST;
	currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);
	#ifdef NLC_NONOO
	currentCodeBlockInTree = createCodeBlockIfActionName(currentCodeBlockInTree, item);			
	#endif
	return currentCodeBlockInTree;
}
NLCcodeblock* createCodeBlockForActionObjectList(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, string context)
{
	NLCitem* item = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
	item->context.push_back(context);
	
	currentCodeBlockInTree->parameters.push_back(item);
	int codeBlockType = NLC_CODEBLOCK_TYPE_FOR_ACTION_OBJECT_LIST;
	return createCodeBlock(currentCodeBlockInTree, codeBlockType);
}
NLCcodeblock* createCodeBlockForActionSubjectList(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, string context)
{
	NLCitem* item = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
	item->context.push_back(context);
	
	currentCodeBlockInTree->parameters.push_back(item);
	int codeBlockType = NLC_CODEBLOCK_TYPE_FOR_ACTION_SUBJECT_LIST;
	return createCodeBlock(currentCodeBlockInTree, codeBlockType);
}
#endif

#ifdef NLC_SUPPORT_QUANTITIES
NLCcodeblock* createCodeBlockForInteger(NLCcodeblock* currentCodeBlockInTree, string numberIterationsOrVariable)
{
	NLCitem* integerItem = new NLCitem(numberIterationsOrVariable, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(integerItem);
	int codeBlockType = NLC_CODEBLOCK_TYPE_FOR_INTEGER;
	return createCodeBlock(currentCodeBlockInTree, codeBlockType);
}
#endif





NLCcodeblock* createCodeBlockNewFunction(NLCcodeblock* currentCodeBlockInTree, string NLCfunctionName, vector<GIAentityNode*>* entityNodesActiveListComplete, NLCsentence* firstNLCsentenceInList)
{
	#ifdef NLC_SUPPORT_INPUT_FUNCTION_LISTS
	//gets "fight" from "dog::fight"
	string functionName = "";
	bool hasFunctionOwnerClass = false;
	string functionOwnerName = "";
	bool hasFunctionObjectClass = false;
	string functionObjectName = "";
	parseFunctionNameFromNLCfunctionName(NLCfunctionName, &functionName, &functionOwnerName, &hasFunctionOwnerClass, &functionObjectName, &hasFunctionObjectClass);

	GIAentityNode* functionOwner = NULL;
	GIAentityNode* functionObject = NULL;
	GIAentityNode* function = NULL;
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode* entity = *entityIter;
		if(!(entity->isConcept) && !(entity->isActionConcept) && !(entity->isSubstanceConcept))
		{
			if(entity->entityName == functionOwnerName)
			{
				entity->NLCisSingularArgument = true;	//formalFunctionArgumentCorrespondsToActionSubjectUseThisAlias
				entity->NLCparsedForCodeBlocks = true;

				functionOwner = entity;
			}
			else if(entity->entityName == functionObjectName)
			{
				entity->NLCisSingularArgument = true;
				entity->NLCparsedForCodeBlocks = true;

				functionObject = entity;
			}
			else if(entity->entityName == functionName)
			{
				entity->NLCisSingularArgument = true;
				entity->NLCparsedForCodeBlocks = true;

				function = entity;
			}
		}
	}
	#else
	string functionName = NLCfunctionName;
	#endif

	#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS
	if(hasFunctionOwnerClass)
	{
		NLCitem* functionOwnerItem = new NLCitem(functionOwnerName, NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION_OWNER);
		currentCodeBlockInTree->parameters.push_back(functionOwnerItem);
	}
	#endif
	
	NLCitem* functionItem = new NLCitem(functionName, NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION);
	currentCodeBlockInTree->parameters.push_back(functionItem);

	#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS
	if(hasFunctionObjectClass)	//added 21 November 2013
	{
		if(functionObject != NULL)
		{//functionObject is used by the function definition: use functionObject instance name
			//cout << "functionObjectName2 = " << functionObjectName << endl;
			NLCitem* functionObjectItem = new NLCitem(functionObject, NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION_OBJECT);
			currentCodeBlockInTree->parameters.push_back(functionObjectItem);
		}
		else
		{//functionObject is not used by the function definition
			NLCitem* functionObjectItem = new NLCitem(functionObjectName, NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION_OBJECT);
			currentCodeBlockInTree->parameters.push_back(functionObjectItem);
		}
	}
	#endif

	#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS
	generateLocalFunctionArgumentsBasedOnImplicitDeclarations(entityNodesActiveListComplete, &(currentCodeBlockInTree->parameters), firstNLCsentenceInList);
	#endif

	currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, NLC_CODEBLOCK_TYPE_NEW_FUNCTION);

	#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS
	#ifndef NLC_FUNCTIONS_SUPPORT_PLURAL_SUBJECTS
	if(functionOwner != NULL)
	{
		currentCodeBlockInTree = createCodeBlockDeclareAndInitialiseVariableForActionSubject(currentCodeBlockInTree, functionOwner);
		currentCodeBlockInTree = createCodeBlocksAddVariableToNewList(currentCodeBlockInTree, functionOwner);
	}
	#endif
	#ifndef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS_PASS_AS_LISTS
	if(functionObject != NULL)
	{
		currentCodeBlockInTree = createCodeBlocksAddVariableToNewList(currentCodeBlockInTree, functionObject);
	}
	if(function != NULL)
	{
		currentCodeBlockInTree = createCodeBlocksAddVariableToNewList(currentCodeBlockInTree, function);
	}
	#endif
	#endif

	return currentCodeBlockInTree;
}

NLCcodeblock* createCodeBlockDeclareAndInitialiseVariableForActionSubject(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* functionOwner)
{
	//"Dog dog1 = this;"
	NLCitem* functionOwnerItem = new NLCitem(functionOwner, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(functionOwnerItem);
	NLCitem* actionSubjectInstanceReplacementItem = new NLCitem(NLC_SUPPORT_INPUT_FUNCTION_LISTS_ACTION_SUBJECT_INSTANCE_REPLACEMENT_NAME, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(actionSubjectInstanceReplacementItem);
	currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, NLC_CODEBLOCK_TYPE_DECLARE_AND_INITIALISE_VARIABLE);

	return currentCodeBlockInTree;
}

NLCcodeblock* createCodeBlocksAddVariableToNewList(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity)
{
	currentCodeBlockInTree = createCodeBlocksDeclareNewLocalListVariableIfNecessary(currentCodeBlockInTree, entity);
	currentCodeBlockInTree = createCodeBlockAddEntityToLocalList(currentCodeBlockInTree, entity, entity);

	return currentCodeBlockInTree;
}

#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS
void generateLocalFunctionArgumentsBasedOnImplicitDeclarations(vector<GIAentityNode*>* entityNodesActiveListComplete, vector<NLCitem*>* parameters, NLCsentence* firstNLCsentenceInList)
{
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode* entity = *entityIter;
		if(assumedToAlreadyHaveBeenDeclared(entity))
		{
			if(!(entity->isConcept))
			{
				#ifdef NLC_SUPPORT_INPUT_FUNCTION_LISTS
				if(!entity->NLCisSingularArgument)
				{
				#endif
					if(generateLocalFunctionArgumentsBasedOnImplicitDeclarationsValidClassChecks(entity))
					{
						#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS_SUPPORT_LOCAL_LISTS_USE_CLASS_NAMES
						if(!findIndefiniteEntityCorrespondingToDefiniteEntityInSameContext(entityNodesActiveListComplete, entity, firstNLCsentenceInList))	//NB findIndefiniteEntityCorrespondingToDefiniteEntityInSameContext() could be reimplemented to be performed during generateCodeBlocks() sentence parsing, but then generateLocalFunctionArgumentsBasedOnImplicitDeclarations() could not be decared at start of generateCodeBlocks(), ie it would have to be moved out of createCodeBlockNewFunction()
						{
						#endif
							#ifdef NLC_DEBUG
							//cout << "!findIndefiniteEntityCorrespondingToDefiniteEntityInSameContext, entity = " << entity->entityName << endl;
							#endif
							
							#ifdef NLC_USE_ADVANCED_REFERENCING_SUPPORT_ALIASES_PREVENT_ADDING_AS_FUNCTION_ARGUMENT
							bool entityIsAlias = false;
							string aliasClassName = "";
							if(findEntityNameInFunctionAliasList(entity->entityName, &aliasClassName))
							{
								entityIsAlias = true;
							}
							/*
							for(vector<GIAentityConnection*>::iterator entityNodeDefinitionListReverseIterator = entity->entityNodeDefinitionReverseList->begin(); entityNodeDefinitionListReverseIterator < entity->entityNodeDefinitionReverseList->end(); entityNodeDefinitionListReverseIterator++)
							{
								GIAentityConnection* definitionConnection = (*entityNodeDefinitionListReverseIterator);
								if(definitionConnection->isAlias)
								{
									entityIsAlias = true;
									cout << "entityIsAlias: " << entity->entityName << endl;
								}
							}
							*/
							if(!entityIsAlias)
							{
							#endif
								#ifdef NLC_USE_ADVANCED_REFERENCING
								NLCitem* functionArgumentTemp = NULL;
								if(!findFunctionArgument(parameters, entity, NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_INSTANCE_OR_CLASS_LIST, &functionArgumentTemp))
								{
								#endif
									//cout << "generateLocalFunctionArgumentsBasedOnImplicitDeclarations: entity->entityName = " << entity->entityName << endl;
									//detected "the x" without declaring x (ie implicit declaration)
									NLCitem* thisFunctionArgumentInstanceItem = new NLCitem(entity, NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_INSTANCE_OR_CLASS_LIST);
									parameters->push_back(thisFunctionArgumentInstanceItem);

									//added 1j5d
									#ifdef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES
									entity->NLClocalListVariableHasBeenDeclared = true;	//redundant
									#else
									GIAentityNode* conceptEntity = getPrimaryConceptNodeDefiningInstance(entity);
									if(!(conceptEntity->NLClocalListVariableHasBeenDeclared))	//redundant test
									{
										entity->NLClocalListVariableHasBeenDeclared = true;
										conceptEntity->NLClocalListVariableHasBeenDeclared = true;
									}
									#endif
								#ifdef NLC_USE_ADVANCED_REFERENCING
								}
								#endif
							#ifdef NLC_USE_ADVANCED_REFERENCING_SUPPORT_ALIASES
							}
							#endif
						#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS_SUPPORT_LOCAL_LISTS_USE_CLASS_NAMES
						}
						#endif
						
					}
				#ifdef NLC_SUPPORT_INPUT_FUNCTION_LISTS
				}
				#endif
			}
		}
	}
}

#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS_SUPPORT_LOCAL_LISTS_USE_CLASS_NAMES
bool findIndefiniteEntityCorrespondingToDefiniteEntityInSameContext(vector<GIAentityNode*>* entityNodesActiveListComplete, GIAentityNode* definiteEntity, NLCsentence* firstNLCsentenceInList)
{
	bool foundIndefiniteEntity = false;

	#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS_SUPPORT_LOCAL_LISTS_USE_CLASS_NAMES_ADVANCED
	int referenceSetID = 0;
	//see identifyReferenceSetsSpecificConceptsAndLinkWithSubstanceConcepts()

	int minimumEntityIndexOfReferenceSet = definiteEntity->entityIndexTemp;

	//cout << "definiteEntity->entityName  = " << definiteEntity->entityName << endl;
	if(identifyReferenceSetDetermineNextCourseOfAction(definiteEntity, true, referenceSetID, minimumEntityIndexOfReferenceSet, false))
	{
		bool traceModeIsQuery = false;

		#ifdef NLC_DEBUG
		//cout << "findIndefiniteEntityCorrespondingToDefiniteEntityInSameContext{}: identifyReferenceSetDetermineNextCourseOfAction passed" << endl;
		//cout << "definiteEntity = " << definiteEntity->entityName << endl;
		#endif
		
		GIAreferenceTraceParameters referenceTraceParameters;
		referenceTraceParameters.referenceSetID = referenceSetID;
		#ifdef GIA_SUPPORT_NLC_INTEGRATION_DEFINE_REFERENCE_CONTEXT_BY_TEXT_INDENTATION
		referenceTraceParameters.referenceSetDefiniteEntity = true;	//referenceSetDefiniteEntity
		//referenceTraceParameters.firstSentenceInList = firstNLCsentenceInList;
		#endif
		referenceTraceParameters.ensureSameReferenceSetQueryConnections = true;	//added 1n28b

		#ifdef GIA_QUERY_SIMPLIFIED_SEARCH_ENFORCE_EXACT_MATCH
		int irrelevant;
		string printEntityNodeString = "";
		int maxNumberOfMatchedNodesPossible = 0;
		bool traceInstantiations = GIA_QUERY_TRACE_CONCEPT_NODES_DEFINING_INSTANTIATIONS_VALUE;
		traceEntityNode(firstNodeConceptEntityNodesListQuery, GIA_QUERY_TRACE_ENTITY_NODES_FUNCTION_DETERMINE_MAX_NUMBER_MATCHED_NODES_SAME_SET_ONLY, &maxNumberOfMatchedNodesPossible, NULL, false, referenceSetID, traceInstantiations);
		traceEntityNode(currentQueryEntityNode, GIA_QUERY_TRACE_ENTITY_NODES_FUNCTION_RESET_TESTEDFORQUERYCOMPARISONTEMP, &irrelevant, &printEntityNodeString, false, NULL, traceInstantiations);
		#endif

		for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
		{
			GIAentityNode* indefiniteEntity = *entityIter;
			
			if(!assumedToAlreadyHaveBeenDeclared(indefiniteEntity))
			{//indefiniteEntityFound
			
				#ifdef NLC_DEBUG
				//cout << "indefiniteEntity = " << indefiniteEntity->entityName << endl;
				#endif
				
				GIAqueryTraceParameters queryTraceParameters;		//not used
				int numberOfMatchedNodesTemp = 0;
				int numberOfMatchedNodesRequiredSynonymnDetectionTemp = 0;
				//bool exactMatch = testEntityNodeForQueryOrReferenceSet2(definiteEntity, indefiniteEntity, &numberOfMatchedNodesTemp, false, &numberOfMatchedNodesRequiredSynonymnDetectionTemp, traceModeIsQuery, &queryTraceParameters, &referenceTraceParameters);
				bool exactMatch = testReferencedEntityNodeForExactNameMatch2(definiteEntity, indefiniteEntity, &numberOfMatchedNodesTemp, false, &numberOfMatchedNodesRequiredSynonymnDetectionTemp, traceModeIsQuery, &queryTraceParameters, &referenceTraceParameters);

				if(exactMatch)
				{
					if(numberOfMatchedNodesTemp > 0)
					{
						#ifdef NLC_DEBUG
						//cout << "\texactMatch: numberOfMatchedNodesTemp = " << numberOfMatchedNodesTemp << endl;
						#endif

						#ifdef GIA_QUERY_SIMPLIFIED_SEARCH_ENFORCE_EXACT_MATCH
						if(numberOfMatchedNodesTemp == maxNumberOfMatchedNodesPossible)
						{
						#endif
							foundIndefiniteEntity = true;
						#ifdef GIA_QUERY_SIMPLIFIED_SEARCH_ENFORCE_EXACT_MATCH
						}
						#endif
					}
				}
				else
				{
					#ifdef NLC_DEBUG
					//cout << "\t!exactMatch" << endl;
					#endif
				}

				//now reset the matched nodes as unpassed (required such that they are retracable using a the different path)
				int irrelevant;
				string printEntityNodeString = "";
				bool traceInstantiations = GIA_QUERY_TRACE_CONCEPT_NODES_DEFINING_INSTANTIATIONS_VALUE;
				traceEntityNode(definiteEntity, GIA_QUERY_TRACE_ENTITY_NODES_FUNCTION_RESET_TESTEDFORQUERYCOMPARISONTEMP, &irrelevant, &printEntityNodeString, false, NULL, traceInstantiations);
				traceEntityNode(indefiniteEntity, GIA_QUERY_TRACE_ENTITY_NODES_FUNCTION_RESET_TESTEDFORQUERYCOMPARISONTEMP, &irrelevant, &printEntityNodeString, false, NULL, traceInstantiations);

			}
		}
		referenceSetID	= referenceSetID + 1;
	}
	#else
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode* indefiniteEntity = *entityIter;
		if(!assumedToAlreadyHaveBeenDeclared(indefiniteEntity))
		{	
			if(((indefiniteEntity->grammaticalNumber == GRAMMATICAL_NUMBER_SINGULAR) && (definiteEntity->grammaticalNumber == GRAMMATICAL_NUMBER_SINGULAR)) || (indefiniteEntity->grammaticalNumber == GRAMMATICAL_NUMBER_PLURAL))
			{
				setFirstNLCsentenceInList(firstNLCsentenceInList);
				if(checkIndefiniteEntityCorrespondingToDefiniteEntityInSameContext(indefiniteEntity, definiteEntity))
				{
					foundIndefiniteEntity = true;
				}
			}
		}
	}
	#endif
	return foundIndefiniteEntity;
}
#endif

bool generateLocalFunctionArgumentsBasedOnImplicitDeclarationsValidClassChecks(GIAentityNode* entityNode)
{
	bool validClass = true;
	
	#ifdef NLC_PREPROCESSOR_MATH
	#ifdef NLC_PREPROCESSOR_MATH_OLD_NUMBER_OF_IMPLEMENTATION_USING_QVARS
	if(entityNode->entityName == REFERENCE_TYPE_QUESTION_COMPARISON_VARIABLE)
	{
		validClass = false;	
	}
	#endif
	#endif
	if(entityNode->isSubstanceConcept)
	{
		validClass = false;	
	}
	
	return validClass;
}

#endif

bool assumedToAlreadyHaveBeenDeclared(GIAentityNode* entity)
{
	bool isAssumedToAlreadyHaveBeenDeclared = false;
	if(isDefiniteEntity(entity) || entity->NLClocalListVariableHasBeenInitialised || entity->NLCisSingularArgument)
	{
		isAssumedToAlreadyHaveBeenDeclared = true;
		#ifdef NLC_DEBUG
		//cout << "assumedToAlreadyHaveBeenDeclared{}:" << endl;
		//cout << "entity->grammaticalDefiniteTemp = " << entity->grammaticalDefiniteTemp << endl;
		//cout << "entity->grammaticalProperNounTemp = " << entity->grammaticalProperNounTemp << endl;
		//cout << "entity->NLClocalListVariableHasBeenInitialised = " << entity->NLClocalListVariableHasBeenInitialised << endl;
		//cout << "entity->NLCisSingularArgument = " << entity->NLCisSingularArgument << endl;
		#endif
	}
	return isAssumedToAlreadyHaveBeenDeclared;
}

bool isDefiniteEntity(GIAentityNode* entity)
{
	bool isDefiniteEntity = false;
	if((entity->grammaticalDefiniteTemp) || (entity->grammaticalProperNounTemp))
	{
		isDefiniteEntity = true;
	}
	return isDefiniteEntity;
}






NLCcodeblock* createCodeBlock(NLCcodeblock* currentCodeBlockInTree, int codeBlockType)
{
	#ifdef NLC_DEBUG
	cout << "createCodeBlock [" << codeBlockType << "]" << endl;
	#endif
	currentCodeBlockInTree->codeBlockType = codeBlockType;
	currentCodeBlockInTree->next = new NLCcodeblock();

	if(codeBlockType >= NLC_CODEBLOCK_TYPE_CONTAINERS)
	{
		currentCodeBlockInTree = createLowerLevel(currentCodeBlockInTree);
	}
	else
	{
		currentCodeBlockInTree = currentCodeBlockInTree->next;
	}
	return currentCodeBlockInTree;
}

NLCcodeblock* createLowerLevel(NLCcodeblock* currentCodeBlockInTree)
{
	currentCodeBlockInTree->lowerLevel = new NLCcodeblock();
	currentCodeBlockInTree = currentCodeBlockInTree->lowerLevel;
	return currentCodeBlockInTree;
}



bool getEntityContext(GIAentityNode* entity, vector<string>* context, bool includePresentObject, int sentenceIndex, bool markSameSentenceParentsAsParsed)
{
	if(includePresentObject)
	{
		string itemName = generateInstanceName(entity);
		context->push_back(itemName);
	}
	bool entityHasParent = false;
	bool stillSearching = true;
	GIAentityNode* currentEntity = entity;

	while(stillSearching)
	{
		if(!(currentEntity->propertyNodeReverseList->empty()))
		{
			entityHasParent = true;
			GIAentityNode* parentEntity = currentEntity;
			currentEntity = (currentEntity->propertyNodeReverseList->back())->entity;
			string itemName = generateInstanceName(currentEntity);
			if(markSameSentenceParentsAsParsed)
			{
				if(currentEntity->sentenceIndexTemp == sentenceIndex)
				{
					bool foundNode = false;
					GIAentityConnection* propertyConnection = findEntityNodePointerInVector(currentEntity, parentEntity, GIA_ENTITY_VECTOR_CONNECTION_TYPE_PROPERTIES, &foundNode);
					if(foundNode)
					{
						propertyConnection->NLCparsedForCodeBlocks = true;
					}
					else
					{
						cout << "getEntityContext{} error: !foundNode" << endl;
					}
				}
			}
			//string itemName = currentEntity->entityName;	//OLD
			context->push_back(itemName);
		}
		else
		{
			stillSearching = false;
		}
	}
	return entityHasParent;
}



bool checkSentenceIndexParsingCodeBlocks(GIAentityNode* entity, GIAentityConnection* connection, int sentenceIndex, bool checkIfEntityHasBeenParsedForNLCcodeBlocks)
{
	bool result = false;
	//cout << "connection->sentenceIndexTemp = " << connection->sentenceIndexTemp << endl;
	#ifdef NLC_VERIFY_CONNECTIONS_SENTENCE_INDEX
	if(connection->sentenceIndexTemp == sentenceIndex)
	{
	#endif
		if(checkSentenceIndexParsingCodeBlocks(entity, sentenceIndex, checkIfEntityHasBeenParsedForNLCcodeBlocks))
		{
			result = true;
		}
	#ifdef NLC_VERIFY_CONNECTIONS_SENTENCE_INDEX
	}
	#endif
	return result;
}

bool checkSentenceIndexParsingCodeBlocks(GIAentityNode* entity, int sentenceIndex, bool checkIfEntityHasBeenParsedForNLCcodeBlocks)
{
	bool result = false;
	if(!checkIfEntityHasBeenParsedForNLCcodeBlocks || !(entity->NLCparsedForCodeBlocks))
	{
		#ifdef GIA_RECORD_WAS_REFERENCE_INFORMATION
		if((entity->sentenceIndexTemp == sentenceIndex) || (entity->wasReference && (sentenceIndex > entity->sentenceIndexTemp)))	//1l6c added && (sentenceIndex > entity->sentenceIndexTemp) 
		#else
		if(entity->sentenceIndexTemp == sentenceIndex)
		#endif
		{
			if(!(entity->disabled))
			{
				result = true;
			}
		}
	}
	return result;
}


bool checkDuplicateProperty(GIAentityNode* propertyEntity, GIAentityNode* childActionEntity)
{
	bool alreadyAdded = false;
	for(vector<GIAentityConnection*>::iterator propertyNodeListIterator = childActionEntity->propertyNodeList->begin(); propertyNodeListIterator < childActionEntity->propertyNodeList->end(); propertyNodeListIterator++)
	{
		GIAentityNode* propertyEntityLocal = (*propertyNodeListIterator)->entity;
		if((propertyEntity->entityName == propertyEntityLocal->entityName))
		{
			alreadyAdded = true;
		}
	}
	return alreadyAdded;
}

bool checkDuplicateCondition(GIAentityNode* conditionEntity, GIAentityNode* childActionEntity)
{
	bool alreadyAdded = false;
	for(vector<GIAentityConnection*>::iterator conditionNodeListIterator = childActionEntity->conditionNodeList->begin(); conditionNodeListIterator < childActionEntity->conditionNodeList->end(); conditionNodeListIterator++)
	{
		GIAentityNode* conditionEntityLocal = (*conditionNodeListIterator)->entity;
		string conditionObjectEntityLocalName = "";
		if(!(conditionEntityLocal->conditionObjectEntity->empty()))
		{
			conditionObjectEntityLocalName = (conditionEntityLocal->conditionObjectEntity->back())->entity->entityName;
		}
		string conditionObjectEntityName = "";
		if(!(conditionEntity->conditionObjectEntity->empty()))
		{
			conditionObjectEntityName = (conditionEntity->conditionObjectEntity->back())->entity->entityName;
		}
		if((conditionEntity->entityName == conditionEntityLocal->entityName) && (conditionObjectEntityName == conditionObjectEntityLocalName))
		{
			alreadyAdded = true;
		}
	}
	return alreadyAdded;
}

#ifdef NLC_SUPPORT_INPUT_FUNCTION_LISTS
string parseFunctionNameFromNLCfunctionName(string NLCfunctionName)
{
	//gets "fight" from "dog::fight"
	string functionName = "";
	bool hasFunctionOwnerClass = false;
	string functionOwnerName = "";
	parseFunctionNameFromNLCfunctionName(NLCfunctionName, &functionName, &functionOwnerName, &hasFunctionOwnerClass);
	return functionName;
}

void parseFunctionNameFromNLCfunctionName(string NLCfunctionName, string* functionName, string* functionOwnerName, bool* hasFunctionOwnerClass)
{
	//gets "fight" from "dog::fight"
	bool hasFunctionObjectClass = false;
	string functionObjectName = "";
	parseFunctionNameFromNLCfunctionName(NLCfunctionName, functionName, functionOwnerName, hasFunctionOwnerClass, &functionObjectName, &hasFunctionObjectClass);
}

void parseFunctionNameFromNLCfunctionName(string NLCfunctionName, string* functionName, string* functionOwnerName, bool* hasFunctionOwnerClass, string* functionObjectName, bool* hasFunctionObjectClass)
{
	vector<NLCitem*> additionalArgumentsTempNotUsed;
	parseFunctionNameFromNLCgeneralFunctionName(NLCfunctionName, functionName, functionOwnerName, hasFunctionOwnerClass, functionObjectName, hasFunctionObjectClass, &additionalArgumentsTempNotUsed);
}

#ifdef NLC_USE_LIBRARY
void parseFunctionNameFromNLClibFunctionName(string NLCfunctionName, string* functionName, string* functionOwnerName, bool* hasFunctionOwnerClass, string* functionObjectName, bool* hasFunctionObjectClass, vector<NLCitem*>* additionalArguments)
{
	parseFunctionNameFromNLCgeneralFunctionName(NLCfunctionName, functionName, functionOwnerName, hasFunctionOwnerClass, functionObjectName, hasFunctionObjectClass, additionalArguments);
}
#endif

void parseFunctionNameFromNLCgeneralFunctionName(string NLCfunctionName, string* functionName, string* functionOwnerName, bool* hasFunctionOwnerClass, string* functionObjectName, bool* hasFunctionObjectClass, vector<NLCitem*>* additionalArguments)
{
	//gets "fight" from "dog::fight"
	*hasFunctionOwnerClass = false;
	*functionOwnerName = "";
	*hasFunctionObjectClass = false;
	*functionObjectName = "";
	*functionName = NLCfunctionName;
	int indexOfActionName = NLCfunctionName.find(NLC_SUPPORT_INPUT_FUNCTION_LISTS_ACTION_DELIMITER);
	int indexOfObjectName = NLCfunctionName.find(NLC_SUPPORT_INPUT_FUNCTION_LISTS_ACTION_OBJECT_DELIMITER);
	int indexOfFirstArgumentName = NLCfunctionName.find(NLC_SUPPORT_INPUT_FUNCTION_LISTS_ACTION_ARGUMENT_DELIMITER);
	int indexOfFirstArgumentOrEnd = NLCfunctionName.length();
	#ifdef NLC_USE_LIBRARY
	if(indexOfFirstArgumentName != CPP_STRING_FIND_RESULT_FAIL_VALUE)
	{
		indexOfFirstArgumentOrEnd = indexOfFirstArgumentName;
	}
	#endif
	if(indexOfActionName != CPP_STRING_FIND_RESULT_FAIL_VALUE)
	{
		if(indexOfObjectName != CPP_STRING_FIND_RESULT_FAIL_VALUE)
		{
			*functionName = NLCfunctionName.substr(indexOfActionName+NLC_SUPPORT_INPUT_FUNCTION_LISTS_ACTION_DELIMITER_LENGTH, indexOfObjectName-indexOfActionName-NLC_SUPPORT_INPUT_FUNCTION_LISTS_ACTION_DELIMITER_LENGTH);
			*functionOwnerName = NLCfunctionName.substr(0, indexOfActionName);
			*functionObjectName = NLCfunctionName.substr(indexOfObjectName+NLC_SUPPORT_INPUT_FUNCTION_LISTS_ACTION_OBJECT_DELIMITER_LENGTH, indexOfFirstArgumentOrEnd-indexOfObjectName-(NLC_SUPPORT_INPUT_FUNCTION_LISTS_ACTION_OBJECT_DELIMITER_LENGTH));
			*hasFunctionOwnerClass = true;
			*hasFunctionObjectClass = true;
			#ifdef NLC_DEBUG
			cout << "parseFunctionNameFromNLCfunctionName{}:" << endl;
			cout << "NLCfunctionName = " << NLCfunctionName << endl;
			cout << "functionName = " <<* functionName << endl;
			cout << "functionOwnerName = " <<* functionOwnerName << endl;
			cout << "functionObjectName = " <<* functionObjectName << endl;
			#endif
		}
		else
		{
			*functionName = NLCfunctionName.substr(indexOfActionName+NLC_SUPPORT_INPUT_FUNCTION_LISTS_ACTION_DELIMITER_LENGTH, indexOfFirstArgumentOrEnd-indexOfActionName-NLC_SUPPORT_INPUT_FUNCTION_LISTS_ACTION_DELIMITER_LENGTH);
			*functionOwnerName = NLCfunctionName.substr(0, indexOfActionName);
			*hasFunctionOwnerClass = true;
			#ifdef NLC_DEBUG
			cout << "parseFunctionNameFromNLCfunctionName{}:" << endl;
			cout << "NLCfunctionName = " << NLCfunctionName << endl;
			cout << "functionName = " <<* functionName << endl;
			cout << "functionOwnerName = " <<* functionOwnerName << endl;
			#endif
		}
	}
	else if(indexOfObjectName != CPP_STRING_FIND_RESULT_FAIL_VALUE)
	{
		*functionName = NLCfunctionName.substr(0, indexOfObjectName);
		*functionObjectName = NLCfunctionName.substr(indexOfObjectName+NLC_SUPPORT_INPUT_FUNCTION_LISTS_ACTION_OBJECT_DELIMITER_LENGTH, indexOfFirstArgumentOrEnd-indexOfObjectName-(NLC_SUPPORT_INPUT_FUNCTION_LISTS_ACTION_OBJECT_DELIMITER_LENGTH));
		*hasFunctionObjectClass = true;
		#ifdef NLC_DEBUG
		cout << "parseFunctionNameFromNLCfunctionName{}:" << endl;
		cout << "NLCfunctionName = " << NLCfunctionName << endl;
		cout << "functionName = " <<* functionName << endl;
		cout << "functionObjectName = " <<* functionObjectName << endl;
		#endif
	}
	else
	{
		*functionName = NLCfunctionName.substr(0, indexOfFirstArgumentOrEnd);
	}

	#ifdef NLC_USE_LIBRARY
	if(indexOfFirstArgumentName != CPP_STRING_FIND_RESULT_FAIL_VALUE)
	{
		int indexOfArgument = indexOfFirstArgumentName+NLC_SUPPORT_INPUT_FUNCTION_LISTS_ACTION_ARGUMENT_DELIMITER_LENGTH;
		bool stillFindingArguments = true;
		while(stillFindingArguments)
		{
			string argumentName = "";
			int indexOfArgumentNew = NLCfunctionName.find(NLC_SUPPORT_INPUT_FUNCTION_LISTS_ACTION_ARGUMENT_DELIMITER, indexOfArgument);
			if(indexOfArgumentNew != CPP_STRING_FIND_RESULT_FAIL_VALUE)
			{	
				argumentName = NLCfunctionName.substr(indexOfArgument, indexOfArgumentNew-indexOfArgument);
			}
			else
			{
				argumentName = NLCfunctionName.substr(indexOfArgument, NLCfunctionName.length()-indexOfArgument);
				stillFindingArguments = false;
			}
			//cout << "argumentName = " << argumentName << endl;
			NLCitem* functionArgumentItem = new NLCitem(argumentName, NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_INSTANCE_OR_CLASS_LIST);	//NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_INSTANCE_OR_CLASS_LIST
			additionalArguments->push_back(functionArgumentItem);
			indexOfArgument = indexOfArgumentNew+NLC_SUPPORT_INPUT_FUNCTION_LISTS_ACTION_ARGUMENT_DELIMITER_LENGTH;
		}
	}	
	#endif
}

string generateNLCfunctionHeader(string functionName, string functionOwnerName, bool hasFunctionOwnerClass, string functionObjectName, bool hasFunctionObjectClass)
{
	string NLCfunctionHeader = string(NLC_PREPROCESSOR_FUNCTION_HEADER_STRING) + NLC_PREPROCESSOR_FUNCTION_HEADER_MID_CHAR;
	if(hasFunctionOwnerClass)
	{
		NLCfunctionHeader = NLCfunctionHeader + functionOwnerName + NLC_SUPPORT_INPUT_FUNCTION_LISTS_ACTION_DELIMITER;
	}
	NLCfunctionHeader = NLCfunctionHeader + functionName;
	if(hasFunctionObjectClass)
	{
		NLCfunctionHeader = NLCfunctionHeader + NLC_SUPPORT_INPUT_FUNCTION_LISTS_ACTION_OBJECT_DELIMITER + functionObjectName;
	}
	NLCfunctionHeader = NLCfunctionHeader + CHAR_NEWLINE;
	return NLCfunctionHeader;
}

#endif

#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS_ADVANCED

NLCcodeblock* createCodeBlockLogicalConditionConjunctionOfBools(NLCcodeblock* currentCodeBlockInTree, int logicalOperation, NLClogicalConditionConjunction* logicalConditionConjunctionArray, int logicalConditionConjunctionIndexMax, int logicalConditionLevel, int logicalConditionCase, bool elseIfDetected)
{
	//cout << "logicalConditionConjunctionIndexMax = " << logicalConditionConjunctionIndexMax << endl;
	for(int i=0; i<logicalConditionConjunctionIndexMax; i++)
	{
		string logicalConditionConjunctionBooleanName = generateLogicalConditionConjunctionBooleanName(logicalConditionLevel, logicalConditionCase, i, logicalOperation);
		NLCitem* conditionItem = new NLCitem(logicalConditionConjunctionBooleanName, NLC_ITEM_TYPE_VARIABLE);
		conditionItem->conjunctionType = logicalConditionConjunctionArray[i].conjunctionType;
		conditionItem->negative = logicalConditionConjunctionArray[i].negative;
		//cout << "currentCodeBlockInTree->parameters.push_back(conditionItem)" << endl;
		currentCodeBlockInTree->parameters.push_back(conditionItem);
		//cout << "done currentCodeBlockInTree->parameters.push_back(conditionItem)" << endl;
	}

	int codeBlockType;
	if(logicalOperation == NLC_LOGICAL_CONDITION_OPERATIONS_IF)
	{
		if(elseIfDetected)
		{
			codeBlockType = NLC_CODEBLOCK_TYPE_ELSE_IF_LOGICAL_CONJUNCTION_OF_BOOLS;
		}
		else
		{
			codeBlockType = NLC_CODEBLOCK_TYPE_IF_LOGICAL_CONJUNCTION_OF_BOOLS;
		}
	}
	else if(logicalOperation == NLC_LOGICAL_CONDITION_OPERATIONS_WHILE)
	{//not currently used
		codeBlockType = NLC_CODEBLOCK_TYPE_WHILE_LOGICAL_CONJUNCTION_OF_BOOLS;
	}
	else
	{
		cout << "createCodeBlockLogicalConditionHasBools{} error: invalid logicalOperation: " << logicalOperation << endl;
	}

	return createCodeBlock(currentCodeBlockInTree, codeBlockType);
}

string generateLogicalConditionConjunctionBooleanName(int logicalConditionLevel, int logicalConditionCase, int logicalOperation)
{
	string logicalConditionConjunctionBooleanName = "";
	if(logicalOperation == NLC_LOGICAL_CONDITION_OPERATIONS_IF)
	{
		logicalConditionConjunctionBooleanName = string(NLC_LOGICAL_CONDITION_CONJUNCTION_BOOLEAN_VARIABLE_NAME) + string(NLC_LOGICAL_CONDITION_CONJUNCTION_BOOLEAN_VARIABLE_NAME_LEVEL) + convertIntToString(logicalConditionLevel) + string(NLC_LOGICAL_CONDITION_CONJUNCTION_BOOLEAN_VARIABLE_NAME_CASE) + convertIntToString(logicalConditionCase);
	}
	else if(logicalOperation == NLC_LOGICAL_CONDITION_OPERATIONS_WHILE)
	{
		logicalConditionConjunctionBooleanName = string(NLC_LOGICAL_CONDITION_CONJUNCTION_BOOLEAN_VARIABLE_NAME) + string(NLC_LOGICAL_CONDITION_CONJUNCTION_BOOLEAN_VARIABLE_NAME_LEVEL) + convertIntToString(logicalConditionLevel);
	}
	else
	{
		cout << "generateLogicalConditionConjunctionBooleanName{} error: invalid logicalOperation: " << logicalOperation << endl;
	}
	
	return logicalConditionConjunctionBooleanName;
}


string generateLogicalConditionConjunctionBooleanName(int logicalConditionLevel, int logicalConditionCase, int logicalConditionConjunctionIndex, int logicalOperation)
{
	string logicalConditionConjunctionBooleanName = "";
	if(logicalOperation == NLC_LOGICAL_CONDITION_OPERATIONS_IF)
	{
		logicalConditionConjunctionBooleanName = string(NLC_LOGICAL_CONDITION_CONJUNCTION_BOOLEAN_VARIABLE_NAME) + string(NLC_LOGICAL_CONDITION_CONJUNCTION_BOOLEAN_VARIABLE_NAME_LEVEL) + convertIntToString(logicalConditionLevel) + string(NLC_LOGICAL_CONDITION_CONJUNCTION_BOOLEAN_VARIABLE_NAME_CASE) + convertIntToString(logicalConditionCase) + progLangArrayOpen[0] + convertIntToString(logicalConditionConjunctionIndex) + progLangArrayClose[0];
	}
	else if(logicalOperation == NLC_LOGICAL_CONDITION_OPERATIONS_WHILE)
	{
		logicalConditionConjunctionBooleanName = string(NLC_LOGICAL_CONDITION_CONJUNCTION_BOOLEAN_VARIABLE_NAME) + string(NLC_LOGICAL_CONDITION_CONJUNCTION_BOOLEAN_VARIABLE_NAME_LEVEL) + convertIntToString(logicalConditionLevel) + progLangArrayOpen[0] + convertIntToString(logicalConditionConjunctionIndex) + progLangArrayClose[0];	
	}
	else
	{
		cout << "generateLogicalConditionConjunctionBooleanName{} error: invalid logicalOperation: " << logicalOperation << endl;
	}
	return logicalConditionConjunctionBooleanName;
}

NLCcodeblock* createCodeBlockDeclareNewBoolArray(NLCcodeblock* currentCodeBlockInTree, string boolArrayName, bool value)
{
	NLCitem* itemDeclareNewBoolVariable = new NLCitem(boolArrayName, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(itemDeclareNewBoolVariable);
	int codeBlockType;
	if(value)
	{
		codeBlockType = NLC_CODEBLOCK_TYPE_DECLARE_NEW_BOOL_ARRAY_INITIALISE_TRUE;
	}
	else
	{
		codeBlockType = NLC_CODEBLOCK_TYPE_DECLARE_NEW_BOOL_ARRAY_INITIALISE_FALSE;
	}
	return createCodeBlock(currentCodeBlockInTree, codeBlockType);
}
#else

NLCcodeblock* createCodeBlockIfHasProperty(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, string context, bool negative)
{
	NLCitem* item = new NLCitem(propertyEntity, NLC_ITEM_TYPE_OBJECT);
	item->context.push_back(context);
	
	currentCodeBlockInTree->parameters.push_back(item);
	int codeBlockType = NLC_CODEBLOCK_TYPE_IF_HAS_PROPERTY;
	if(negative)
	{
		item->negative = true;
	}
	return createCodeBlock(currentCodeBlockInTree, codeBlockType);
}

NLCcodeblock* createCodeBlockIfHasCondition(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* condition, GIAentityNode* conditionObject, string context, bool negative)
{
	NLCitem* conditionItem = new NLCitem(conditionEntity, NLC_ITEM_TYPE_OBJECT);
	NLCitem* conditionObjectItem = new NLCitem(conditionObject, NLC_ITEM_TYPE_OBJECT);
	conditionItem->context.push_back(context);
	conditionObjectItem->context.push_back(context);	//redundant
			
	currentCodeBlockInTree->parameters.push_back(itemCondition);
	currentCodeBlockInTree->parameters.push_back(itemConditionObject);
	int codeBlockType = NLC_CODEBLOCK_TYPE_IF_HAS_CONDITION;
	if(negative)
	{
		itemCondition->negative = true;
	}
	return createCodeBlock(currentCodeBlockInTree, codeBlockType);
}

NLCcodeblock* createCodeBlockWhileHasProperty(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, string context, bool negative)
{
	NLCitem* item = new NLCitem(propertyEntity, NLC_ITEM_TYPE_OBJECT);
	item->context.push_back(context);
	
	currentCodeBlockInTree->parameters.push_back(item);
	int codeBlockType = NLC_CODEBLOCK_TYPE_WHILE_HAS_PROPERTY;
	if(negative)
	{
		item->negative = true;
	}
	return createCodeBlock(currentCodeBlockInTree, codeBlockType);
}

NLCcodeblock* createCodeBlockWhileHasCondition(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* condition, GIAentityNode* conditionObject, string context, bool negative)
{
	NLCitem* conditionItem = new NLCitem(conditionEntity, NLC_ITEM_TYPE_OBJECT);
	NLCitem* conditionObjectItem = new NLCitem(conditionObject, NLC_ITEM_TYPE_OBJECT);
	conditionItem->context.push_back(context);
	conditionObjectItem->context.push_back(context);	//redundant
			
	currentCodeBlockInTree->parameters.push_back(itemCondition);
	currentCodeBlockInTree->parameters.push_back(itemConditionObject);
	int codeBlockType = NLC_CODEBLOCK_TYPE_WHILE_HAS_CONDITION;
	if(negative)
	{
		itemCondition->negative = true;
	}
	return createCodeBlock(currentCodeBlockInTree, codeBlockType);
}
#endif
#endif

NLCcodeblock* createCodeBlockElse(NLCcodeblock* currentCodeBlockInTree)
{
	NLCitem* tempItem = new NLCitem("notUsedButNLCprintCodeBlocksRequiresAtLeastOneItem", NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(tempItem);
	int codeBlockType = NLC_CODEBLOCK_TYPE_ELSE;
	return createCodeBlock(currentCodeBlockInTree, codeBlockType);
}

NLCcodeblock* createCodeBlockWhileHasBool(NLCcodeblock* currentCodeBlockInTree, string whileLogicalConditionConjunctionBooleanName)
{
	NLCitem* conditionItem = new NLCitem(whileLogicalConditionConjunctionBooleanName, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(conditionItem);
	int codeBlockType = NLC_CODEBLOCK_TYPE_WHILE;
	return createCodeBlock(currentCodeBlockInTree, codeBlockType);
}

//logicalConditionLevel is defined based on user tab indenting of text file, as parsed by NLC preprocessor
string generateWhileLogicalConditionConjunctionBooleanName(int logicalConditionLevel)
{
	string whileLogicalConditionConjunctionBooleanName = string(NLC_WHILE_LOGICAL_CONDITION_CONJUNCTION_BOOLEAN_VARIABLE_NAME) + convertIntToString(logicalConditionLevel);
	return whileLogicalConditionConjunctionBooleanName;
}

NLCcodeblock* createCodeBlockDeclareNewBoolVar(NLCcodeblock* currentCodeBlockInTree, string boolVariableName, bool value)
{
	NLCitem* itemDeclareNewBoolVariable = new NLCitem(boolVariableName, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(itemDeclareNewBoolVariable);
	int codeBlockType;
	if(value)
	{
		codeBlockType = NLC_CODEBLOCK_TYPE_DECLARE_NEW_BOOL_VARIABLE_INITIALISE_TRUE;
	}
	else
	{
		codeBlockType = NLC_CODEBLOCK_TYPE_DECLARE_NEW_BOOL_VARIABLE_INITIALISE_FALSE;
	}
	return createCodeBlock(currentCodeBlockInTree, codeBlockType);
}

NLCcodeblock* createCodeBlockSetBoolVar(NLCcodeblock* currentCodeBlockInTree, string boolVariableName, bool value)
{
	NLCitem* itemSetBoolVariable = new NLCitem(boolVariableName, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(itemSetBoolVariable);
	int codeBlockType;
	if(value)
	{
		codeBlockType = NLC_CODEBLOCK_TYPE_SET_BOOL_VARIABLE_TRUE;
	}
	else
	{
		codeBlockType = NLC_CODEBLOCK_TYPE_SET_BOOL_VARIABLE_FALSE;
	}
	return createCodeBlock(currentCodeBlockInTree, codeBlockType);
}

#ifdef NLC_TRANSLATE_NEGATIVE_PROPERTIES_AND_CONDITIONS
NLCcodeblock* createCodeBlockRemoveProperty(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* propertyEntity)
{
	NLCitem* entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	NLCitem* propertyItem = new NLCitem(propertyEntity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(propertyItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_REMOVE_PROPERTY;
	currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}
NLCcodeblock* createCodeBlockRemoveProperties(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* propertyEntity)
{
	NLCitem* entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	NLCitem* propertyItem = new NLCitem(propertyEntity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(propertyItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_REMOVE_PROPERTIES;
	currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}

//not currently used;
NLCcodeblock* createCodeBlockRemoveEntitiesFromLocalList(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity)
{
	NLCitem* entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_REMOVE_ENTITIES_FROM_LOCAL_LIST;
	currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}

NLCcodeblock* createCodeBlockRemoveCondition(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* conditionEntity)
{
	if(!(conditionEntity->conditionObjectEntity->empty()))
	{
		GIAentityNode* conditionObject = (conditionEntity->conditionObjectEntity->back())->entity;

		currentCodeBlockInTree = createCodeBlockRemoveConditionSimple(currentCodeBlockInTree, entity, conditionEntity, conditionObject);
		#ifdef NLC_NORMALISE_TWOWAY_PREPOSITIONS
		if(conditionEntity->conditionTwoWay)
		{
			GIAentityNode* entityInverse = conditionObject;
			GIAentityNode* conditionEntityInverse = NULL;
			conditionEntityInverse = generateInverseConditionEntity(conditionEntity);
			#ifdef NLC_DEBUG
			cout << "conditionEntityInverse: conditionEntity = " << conditionEntity->entityName << endl;
			#endif
			currentCodeBlockInTree = createCodeBlockRemoveConditionSimple(currentCodeBlockInTree, conditionObject, conditionEntityInverse, entity);
		}
		#endif
	}
	else
	{
		cout << "error: condition does not have object" << endl;
	}

	return currentCodeBlockInTree;
}

NLCcodeblock* createCodeBlockRemoveConditionSimple(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* conditionEntity, GIAentityNode* conditionObject)
{
	NLCitem* entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
	//removed 1e7c as it is not used: getEntityContext(entity, &(entityItem->context), false, sentenceIndex, false);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	NLCitem* conditionItem = new NLCitem(conditionEntity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(conditionItem);

	NLCitem* conditionObjectItem = new NLCitem(conditionObject, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(conditionObjectItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_REMOVE_CONDITION;
	currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);
	
	return currentCodeBlockInTree;
}

NLCcodeblock* createCodeBlockRemoveConditions(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* conditionEntity)
{
	if(!(conditionEntity->conditionObjectEntity->empty()))
	{
		GIAentityNode* conditionObject = (conditionEntity->conditionObjectEntity->back())->entity;

		currentCodeBlockInTree = createCodeBlockRemoveConditionsSimple(currentCodeBlockInTree, entity, conditionEntity, conditionObject);
		#ifdef NLC_NORMALISE_TWOWAY_PREPOSITIONS
		if(conditionEntity->conditionTwoWay)
		{
			GIAentityNode* entityInverse = conditionObject;
			GIAentityNode* conditionEntityInverse = NULL;
			conditionEntityInverse = generateInverseConditionEntity(conditionEntity);
			#ifdef NLC_DEBUG
			cout << "conditionEntityInverse: conditionEntity = " << conditionEntity->entityName << endl;
			#endif
			currentCodeBlockInTree = createCodeBlockRemoveConditionsSimple(currentCodeBlockInTree, conditionObject, conditionEntityInverse, entity);
		}
		#endif
	}
	else
	{
		cout << "error: condition does not have object" << endl;
	}

	return currentCodeBlockInTree;
}

NLCcodeblock* createCodeBlockRemoveConditionsSimple(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* conditionEntity, GIAentityNode* conditionObject)
{
	NLCitem* entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
	//removed 1e7c as it is not used: getEntityContext(entity, &(entityItem->context), false, sentenceIndex, false);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	NLCitem* conditionItem = new NLCitem(conditionEntity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(conditionItem);

	NLCitem* conditionObjectItem = new NLCitem(conditionObject, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(conditionObjectItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_REMOVE_CONDITIONS;
	currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);
	
	return currentCodeBlockInTree;
}
		
#endif

#ifdef NLC_PREPROCESSOR_MATH
NLCcodeblock* createCodeBlockMathTextLine(NLCcodeblock* currentCodeBlockInTree, string mathText)
{
	NLCitem* mathTextItem = new NLCitem(mathText, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(mathTextItem);
	
	int codeBlockType = NLC_CODEBLOCK_TYPE_MATHTEXT_LINE;
	currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}

NLCcodeblock* createCodeBlockMathTextWithLogicalOperator(NLCcodeblock* currentCodeBlockInTree, string mathText)
{
	if(!(currentCodeBlockInTree->parameters.empty()))
	{
		cout << "error: !(currentCodeBlockInTree->parameters.empty())" << endl;
	}
	NLCitem* mathTextItem = new NLCitem(mathText, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(mathTextItem);
		
	int codeBlockType = NLC_CODEBLOCK_TYPE_MATHTEXT_WITH_LOGICAL_OPERATOR;
	currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}
#endif

NLCcodeblock* createCodeBlockDeclareNewIntVar(NLCcodeblock* currentCodeBlockInTree, string intVariableName, int value)
{
	NLCitem* intNameItem = new NLCitem(intVariableName, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(intNameItem);
	//cout << "intVariableName = " << intVariableName << endl;

	string intValueString = convertIntToString(value);
	NLCitem* intValueItem = new NLCitem(intValueString, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(intValueItem);
	//cout << "intValueString = " << intValueString << endl;
		
	int codeBlockType = NLC_CODEBLOCK_TYPE_DECLARE_NEW_INT_VARIABLE;

	return createCodeBlock(currentCodeBlockInTree, codeBlockType);
}

NLCcodeblock* createCodeBlockIncrementIntVar(NLCcodeblock* currentCodeBlockInTree, string intVariableName)
{	
	NLCitem* intNameItem = new NLCitem(intVariableName, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(intNameItem);
	
	int codeBlockType = NLC_CODEBLOCK_TYPE_INCREMENT_INT_VARIABLE;

	return createCodeBlock(currentCodeBlockInTree, codeBlockType);
}

NLCcodeblock* createCodeBlockCommentSingleLine(NLCcodeblock* currentCodeBlockInTree, string comment)
{
	NLCitem* item = new NLCitem(comment, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(item);

	int codeBlockType = NLC_CODEBLOCK_TYPE_COMMENT_SINGLE_LINE;
	currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}



#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN

NLCcodeblock* createCodeBlockReassignIter(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity)
{	
	NLCitem* entityClass = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);

	currentCodeBlockInTree->parameters.push_back(entityClass);
	
	int codeBlockType = NLC_CODEBLOCK_TYPE_REASSIGN_ITER;

	return createCodeBlock(currentCodeBlockInTree, codeBlockType);
}

NLCcodeblock* createCodeBlocksDeclareNewCategoryListVariable(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, string genericListAppendName, int sentenceIndex)
{
	return createCodeBlocksDeclareNewGenericListVariable(currentCodeBlockInTree, entity, generateCategoryListGenericObjectName(entity, sentenceIndex), genericListAppendName);
}

NLCcodeblock* createCodeBlockAddEntityToCategoryList(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* propertyEntity, string genericListAppendName, int sentenceIndex)
{
	return createCodeBlockAddEntityToGenericList(currentCodeBlockInTree, entity, generateCategoryListGenericObjectName(entity, sentenceIndex), genericListAppendName, propertyEntity);
}

NLCcodeblock* createCodeBlockForCategoryList(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, string genericListAppendName, int sentenceIndex)
{
	return createCodeBlockForGenericList(currentCodeBlockInTree, entity, generateCategoryListGenericObjectName(entity, sentenceIndex), genericListAppendName);
}

#ifdef NLC_CATEGORIES_TEST_PLURALITY
NLCcodeblock* createCodeBlockGetBackCategoryEntityList(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, string genericListAppendName, int sentenceIndex)
{
	return createCodeBlockGetBackGenericEntityList(currentCodeBlockInTree, entity, generateCategoryListGenericObjectName(entity, sentenceIndex), genericListAppendName);
}
NLCcodeblock* createCodeBlockIfHasGreaterThanNumCategoryItem(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, string genericListAppendName, int value, int sentenceIndex)
{
	return createCodeBlockIfHasGreaterThanNumGenericEntity(currentCodeBlockInTree, entity, generateCategoryListGenericObjectName(entity, sentenceIndex), genericListAppendName, value);
}
#endif
#ifdef NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY
NLCcodeblock* createCodeBlockIfHasGreaterThanOrEqualToNumCategoryItem(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, string genericListAppendName, int value, int sentenceIndex)
{
	return createCodeBlockIfHasGreaterThanOrEqualToNumGenericEntity(currentCodeBlockInTree, entity, generateCategoryListGenericObjectName(entity, sentenceIndex), genericListAppendName, value);
}
#endif
#ifdef NLC_USE_ADVANCED_REFERENCING
NLCcodeblock* createCodeBlockIfHasCategoryItem(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, bool negative, string genericListAppendName, int sentenceIndex)
{
	return createCodeBlockIfHasGenericEntity(currentCodeBlockInTree, entity, generateCategoryListGenericObjectName(entity, sentenceIndex), genericListAppendName, negative);
}
NLCcodeblock* createCodeBlockAddEntityToCategoryListCheckLastSentenceReferencedSingularExecuteFunction(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* propertyEntity, string genericListAppendName, int sentenceIndex)
{
	return createCodeBlockAddEntityToGenericListCheckLastSentenceReferencedSingularExecuteFunction(currentCodeBlockInTree, entity, generateCategoryListGenericObjectName(entity, sentenceIndex), genericListAppendName, propertyEntity);
}
NLCcodeblock* createCodeBlockAddEntityToCategoryListCheckLastSentenceReferencedSingularNewFunction(NLCcodeblock* currentCodeBlockInTree)
{
	return createCodeBlockAddEntityToGenericListCheckLastSentenceReferencedSingularNewFunction(currentCodeBlockInTree);
}
#endif
#ifdef NLC_PERFORM_PLURAL_DEFINITE_REFERENCING_TESTS
NLCcodeblock* createCodeBlockAddEntityToCategoryListCheckLastSentenceReferencedPluralExecuteFunction(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* propertyEntity, string genericListAppendName, int sentenceIndex)
{
	return createCodeBlockAddEntityToGenericListCheckLastSentenceReferencedPluralExecuteFunction(currentCodeBlockInTree, entity, generateCategoryListGenericObjectName(entity, sentenceIndex), genericListAppendName, propertyEntity);
}
NLCcodeblock* createCodeBlockAddEntityToCategoryListCheckLastSentenceReferencedPluralNewFunction(NLCcodeblock* currentCodeBlockInTree)
{
	return createCodeBlockAddEntityToGenericListCheckLastSentenceReferencedPluralNewFunction(currentCodeBlockInTree);
}
#endif


NLCcodeblock* createCodeBlocksDeclareNewGenericListVariable(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, string genericObjectName, string genericListAppendName)
{
	NLCitem* entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT, genericObjectName);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	NLCitem* genericListAppendItem = new NLCitem(genericListAppendName, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(genericListAppendItem);
	
	int codeBlockType = NLC_CODEBLOCK_TYPE_DECLARE_NEW_GENERIC_LIST_VARIABLE;
	currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}

NLCcodeblock* createCodeBlockAddEntityToGenericList(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, string genericObjectName, string genericListAppendName, GIAentityNode* propertyEntity)
{
	NLCitem* entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT, genericObjectName);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	NLCitem* propertyItem = new NLCitem(propertyEntity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(propertyItem);

	NLCitem* genericListAppendItem = new NLCitem(genericListAppendName, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(genericListAppendItem);
	
	int codeBlockType = NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST;
	currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}

NLCcodeblock* createCodeBlockForGenericList(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, string genericObjectName, string genericListAppendName)
{
	NLCitem* entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT, genericObjectName);
	currentCodeBlockInTree->parameters.push_back(entityItem);
	
	NLCitem* genericListAppendItem = new NLCitem(genericListAppendName, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(genericListAppendItem);
	
	int codeBlockType = NLC_CODEBLOCK_TYPE_FOR_GENERIC_LIST;
	return createCodeBlock(currentCodeBlockInTree, codeBlockType);
}

#ifdef NLC_CATEGORIES_TEST_PLURALITY
NLCcodeblock* createCodeBlockGetBackGenericEntityList(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, string genericObjectName, string genericListAppendName)
{
	NLCitem* entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT, genericObjectName);
	currentCodeBlockInTree->parameters.push_back(entityItem);
	
	NLCitem* genericListAppendItem = new NLCitem(genericListAppendName, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(genericListAppendItem);
	
	int codeBlockType = NLC_CODEBLOCK_TYPE_GET_BACK_GENERIC_ENTITY_LIST;
	return createCodeBlock(currentCodeBlockInTree, codeBlockType);
}
NLCcodeblock* createCodeBlockIfHasGreaterThanNumGenericEntity(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, string genericObjectName, string genericListAppendName, int value)
{
	NLCitem* entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT, genericObjectName);
	currentCodeBlockInTree->parameters.push_back(entityItem);
	
	NLCitem* genericListAppendItem = new NLCitem(genericListAppendName, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(genericListAppendItem);
	
	string intValueString = convertIntToString(value);
	NLCitem* intValueItem = new NLCitem(intValueString, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(intValueItem);
	//cout << "intValueString = " << intValueString << endl;
	
	int codeBlockType = NLC_CODEBLOCK_TYPE_IF_HAS_GREATER_THAN_NUM_GENERIC_ENTITY;
	return createCodeBlock(currentCodeBlockInTree, codeBlockType);
}

NLCcodeblock* createCodeBlockPrintWarning(NLCcodeblock* currentCodeBlockInTree, string warning)
{
	NLCitem* printWarningItem = new NLCitem(warning, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(printWarningItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_PRINT_WARNING;
	currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}
#endif
#ifdef NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY
NLCcodeblock* createCodeBlockIfHasGreaterThanOrEqualToNumGenericEntity(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, string genericObjectName, string genericListAppendName, int value)
{
	NLCitem* entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT, genericObjectName);
	currentCodeBlockInTree->parameters.push_back(entityItem);
	
	NLCitem* genericListAppendItem = new NLCitem(genericListAppendName, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(genericListAppendItem);
	
	string intValueString = convertIntToString(value);
	NLCitem* intValueItem = new NLCitem(intValueString, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(intValueItem);
	//cout << "intValueString = " << intValueString << endl;
	
	int codeBlockType = NLC_CODEBLOCK_TYPE_IF_HAS_GREATER_THAN_OR_EQUAL_TO_NUM_GENERIC_ENTITY;
	return createCodeBlock(currentCodeBlockInTree, codeBlockType);
}
#endif

#ifdef NLC_USE_ADVANCED_REFERENCING
NLCcodeblock* createCodeBlockIfHasGenericEntity(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, string genericObjectName, string genericListAppendName, bool negative)
{
	NLCitem* entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT, genericObjectName);
	currentCodeBlockInTree->parameters.push_back(entityItem);
	
	NLCitem* genericListAppendItem = new NLCitem(genericListAppendName, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(genericListAppendItem);
	
	int codeBlockType = NLC_CODEBLOCK_TYPE_IF_HAS_GENERIC_ENTITY;
	if(negative)
	{
		entityItem->negative = true;
	}
	return createCodeBlock(currentCodeBlockInTree, codeBlockType);
}
NLCcodeblock* createCodeBlockAddEntityToGenericListCheckLastSentenceReferencedSingularExecuteFunction(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, string genericObjectName, string genericListAppendName, GIAentityNode* propertyEntity)
{
	NLCitem* entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT, genericObjectName);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	NLCitem* propertyItem = new NLCitem(propertyEntity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(propertyItem);

	NLCitem* genericListAppendItem = new NLCitem(genericListAppendName, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(genericListAppendItem);
	
	int codeBlockType = NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST_CHECK_LAST_SENTENCE_REFERENCED_SINGULAR_EXECUTE_FUNCTION;
	currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}
NLCcodeblock* createCodeBlockAddEntityToGenericListCheckLastSentenceReferencedSingularNewFunction(NLCcodeblock* currentCodeBlockInTree)
{
	//required because printCodeBlocks requires at least 1 param
	NLCitem* entityItem = new NLCitem("dummyentity", NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(entityItem);
	
	int codeBlockType = NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST_CHECK_LAST_SENTENCE_REFERENCED_SINGULAR_NEW_FUNCTION;
	currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}

NLCcodeblock* createCodeBlockUpdateLastSentenceReferenced(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, int sentenceIndex)
{
	NLCitem* entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(entityItem);
	
	string sentenceIndexString = convertIntToString(sentenceIndex);
	NLCitem* sentenceIndexItem = new NLCitem(sentenceIndexString, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(sentenceIndexItem);
	
	int codeBlockType = NLC_CODEBLOCK_TYPE_UPDATE_LAST_SENTENCE_REFERENCED;
	return createCodeBlock(currentCodeBlockInTree, codeBlockType);
}
#endif
#endif

#ifdef NLC_PERFORM_PLURAL_DEFINITE_REFERENCING_TESTS
NLCcodeblock* createCodeBlockAddEntityToGenericListCheckLastSentenceReferencedPluralExecuteFunction(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, string genericObjectName, string genericListAppendName, GIAentityNode* propertyEntity)
{
	NLCitem* entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT, genericObjectName);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	NLCitem* propertyItem = new NLCitem(propertyEntity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(propertyItem);

	NLCitem* genericListAppendItem = new NLCitem(genericListAppendName, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(genericListAppendItem);
	
	int codeBlockType = NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST_CHECK_LAST_SENTENCE_REFERENCED_PLURAL_EXECUTE_FUNCTION;
	currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}
NLCcodeblock* createCodeBlockAddEntityToGenericListCheckLastSentenceReferencedPluralNewFunction(NLCcodeblock* currentCodeBlockInTree)
{
	//required because printCodeBlocks requires at least 1 param
	NLCitem* entityItem = new NLCitem("dummyentity", NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(entityItem);
		
	int codeBlockType = NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST_CHECK_LAST_SENTENCE_REFERENCED_PLURAL_NEW_FUNCTION;
	currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}
#endif


#ifdef NLC_GENERATE_TYPE_LISTS
NLCcodeblock* createCodeBlocksDeclareNewGenericListVariable2(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, string genericObjectName, string genericListAppendName)
{
	NLCitem* entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT, genericObjectName);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	NLCitem* genericListAppendItem = new NLCitem(genericListAppendName, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(genericListAppendItem);
	
	int codeBlockType = NLC_CODEBLOCK_TYPE_DECLARE_NEW_GENERIC_LIST_VARIABLE2;
	currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}

NLCcodeblock* createCodeBlockAddEntityToGenericList2(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, string genericObjectName, string genericListAppendName, GIAentityNode* propertyEntity, string genericListAppendName2)
{
	NLCitem* entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT, genericObjectName);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	NLCitem* propertyItem = new NLCitem(propertyEntity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(propertyItem);

	NLCitem* genericListAppendItem = new NLCitem(genericListAppendName, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(genericListAppendItem);

	NLCitem* genericListAppendItem2 = new NLCitem(genericListAppendName2, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(genericListAppendItem2);
		
	int codeBlockType = NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST2;
	currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}

NLCcodeblock* createCodeBlockForGenericList2(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, string genericObjectName, string genericListAppendName)
{
	NLCitem* entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT, genericObjectName);
	currentCodeBlockInTree->parameters.push_back(entityItem);
	
	NLCitem* genericListAppendItem = new NLCitem(genericListAppendName, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(genericListAppendItem);
	
	int codeBlockType = NLC_CODEBLOCK_TYPE_FOR_GENERIC_LIST2;
	return createCodeBlock(currentCodeBlockInTree, codeBlockType);
}

NLCcodeblock* createCodeBlocksDeclareNewTypeListVariable(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity)
{
	return createCodeBlocksDeclareNewGenericListVariable2(currentCodeBlockInTree, entity, entity->entityName, NLC_ITEM_TYPE_TYPE_VAR_APPENDITION2);
}
NLCcodeblock* createCodeBlockAddInstanceListToTypeList(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* propertyEntity)
{
	return createCodeBlockAddEntityToGenericList2(currentCodeBlockInTree, entity, entity->entityName, NLC_ITEM_TYPE_TYPE_VAR_APPENDITION2, propertyEntity, NLC_ITEM_TYPE_INSTANCE_VAR_APPENDITION2);
}
NLCcodeblock* createCodeBlockForPropertyTypeClass(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity)
{
	return createCodeBlockForGenericList2(currentCodeBlockInTree, entity, entity->entityName, NLC_ITEM_TYPE_TYPE_VAR_APPENDITION2);
}
#endif

#ifdef NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY_CHILDREN
NLCcodeblock* createCodeBlockIfIntVariableGreaterThanOrEqualToNum(NLCcodeblock* currentCodeBlockInTree, string intVariableName, int value)
{
	NLCitem* intNameItem = new NLCitem(intVariableName, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(intNameItem);
	//cout << "intVariableName = " << intVariableName << endl;

	string intValueString = convertIntToString(value);
	NLCitem* intValueItem = new NLCitem(intValueString, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(intValueItem);
	//cout << "intValueString = " << intValueString << endl;
	
	int codeBlockType = NLC_CODEBLOCK_TYPE_TEST_INT_VARIABLE_GREATER_THAN_OR_EQUAL_TO_NUM;
	return createCodeBlock(currentCodeBlockInTree, codeBlockType);
}
/*
NLCcodeblock* createCodeBlockIfHasMoreThanNumProperty(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* propertyEntity, int value, string parentInstanceName)
{
	NLCitem* propertyItem = new NLCitem(propertyEntity, NLC_ITEM_TYPE_OBJECT);
	propertyItem->context.push_back(parentInstanceName);
	currentCodeBlockInTree->parameters.push_back(propertyItem);
	
	string intValueString = convertIntToString(value);
	NLCitem* intValueItem = new NLCitem(intValueString, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(intValueItem);
	//cout << "intValueString = " << intValueString << endl;
	
	int codeBlockType = NLC_CODEBLOCK_TYPE_IF_HAS_MORE_THAN_NUM_PROPERTY;
	return createCodeBlock(currentCodeBlockInTree, codeBlockType);
}
NLCcodeblock* createCodeBlockIfHasMoreThanNumCondition(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* conditionEntity, GIAentityNode* conditionObject, int value, string parentInstanceName)
{
	NLCitem* conditionItem = new NLCitem(conditionEntity, NLC_ITEM_TYPE_OBJECT);
	NLCitem* conditionObjectItem = new NLCitem(conditionObject, NLC_ITEM_TYPE_OBJECT);
	//cout << "createCodeBlockForGivenCondition: " << conditionObjectItem->instanceName << endl;

	conditionItem->context.push_back(parentInstanceName);
	conditionObjectItem->context.push_back(parentInstanceName);	//redundant
	
	currentCodeBlockInTree->parameters.push_back(conditionItem);
	currentCodeBlockInTree->parameters.push_back(conditionObjectItem);
	
	string intValueString = convertIntToString(value);
	NLCitem* intValueItem = new NLCitem(intValueString, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(intValueItem);
	//cout << "intValueString = " << intValueString << endl;
	
	int codeBlockType = NLC_CODEBLOCK_TYPE_IF_HAS_MORE_THAN_NUM_CONDITION;
	return createCodeBlock(currentCodeBlockInTree, codeBlockType);
}
*/
#endif

#ifdef NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT
NLCcodeblock* createCodeBlocksDeclareContextList(NLCcodeblock* currentCodeBlockInTree, int contextLevel)
{	
	string contextLevelString = convertIntToString(contextLevel);
	NLCitem* contextLevelItem = new NLCitem(contextLevelString, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(contextLevelItem);
	
	int codeBlockType = NLC_CODEBLOCK_TYPE_DECLARE_CONTEXT_LIST;
	currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}

NLCcodeblock* createCodeBlocksAddEntityToContextLevelListNewFunction(NLCcodeblock* currentCodeBlockInTree)
{
	//required because printCodeBlocks requires at least 1 param
	NLCitem* entityItem = new NLCitem("dummyentity", NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(entityItem);
	
	int codeBlockType = NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_CONTEXT_LIST_NEW_FUNCTION;
	currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}

NLCcodeblock* createCodeBlocksClearContextListNewFunction(NLCcodeblock* currentCodeBlockInTree)
{
	//required because printCodeBlocks requires at least 1 param
	NLCitem* entityItem = new NLCitem("dummyentity", NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(entityItem);
	
	int codeBlockType = NLC_CODEBLOCK_TYPE_CLEAR_CONTEXT_LIST_NEW_FUNCTION;
	currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}

NLCcodeblock* createCodeBlocksAddEntityToContextLevelListExecuteFunction(NLCcodeblock* currentCodeBlockInTree, int contextLevel, GIAentityNode* entity, int sentenceIndex)
{
	string contextLevelString = convertIntToString(contextLevel);
	NLCitem* contextLevelItem = new NLCitem(contextLevelString, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(contextLevelItem);
	
	NLCitem* entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	string sentenceIndexString = convertIntToString(sentenceIndex);
	NLCitem* sentenceIndexItem = new NLCitem(sentenceIndexString, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(sentenceIndexItem);
	
	int codeBlockType = NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_CONTEXT_LIST_EXECUTE_FUNCTION;
	currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);
	
	return currentCodeBlockInTree;
}

//NB createCodeBlocksClearContextListVariableExecuteFunction is embedded in printCodeBlocks()
NLCcodeblock* createCodeBlocksClearContextListVariableExecuteFunction(NLCcodeblock* currentCodeBlockInTree, int contextLevel)
{
	string contextLevelString = convertIntToString(contextLevel);
	NLCitem* contextLevelItem = new NLCitem(contextLevelString, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(contextLevelItem);
	
	int codeBlockType = NLC_CODEBLOCK_TYPE_CLEAR_CONTEXT_LIST_EXECUTE_FUNCTION;
	currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);
	
	return currentCodeBlockInTree;
}
#endif

NLCcodeblock* createCodeBlocksCreateContextBlock(NLCcodeblock* currentCodeBlockInTree)
{
	//required because printCodeBlocks requires at least 1 param
	NLCitem* entityItem = new NLCitem("dummyentity", NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(entityItem);
	
	int codeBlockType = NLC_CODEBLOCK_TYPE_CONTEXT_BLOCK;
	currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}


#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS	
NLCcodeblock* createCodeBlocksCastVectorNewFunction(NLCcodeblock* currentCodeBlockInTree)
{
	//required because printCodeBlocks requires at least 1 param
	NLCitem* entityItem = new NLCitem("dummyentity", NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(entityItem);
	
	int codeBlockType = NLC_CODEBLOCK_TYPE_CAST_VECTOR_NEW_FUNCTION;
	currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);
	
	return currentCodeBlockInTree;
}

NLCcodeblock* createCodeBlocksCastVectorExecuteFunction(NLCcodeblock* currentCodeBlockInTree, NLCitem* item, NLCitem* itemPassCastClassName)
{
	currentCodeBlockInTree->parameters.push_back(item);
	currentCodeBlockInTree->parameters.push_back(itemPassCastClassName);
	
	int codeBlockType = NLC_CODEBLOCK_TYPE_CAST_VECTOR_EXECUTE_FUNCTION;
	currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);
}
#endif

#ifdef NLC_USE_ADVANCED_REFERENCING_SUPPORT_ALIASES
NLCcodeblock* createCodeBlocksAddAliasToEntityAliasList(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, string aliasName)
{
	#ifdef NLC_DEBUG_ADVANCED_REFERENCING_SUPPORT_ALIASES
	cout << "createCodeBlocksAddAliasToEntityAliasList{}:" << endl;
	#endif
	
	NLCitem* entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(entityItem);
	
	NLCitem* aliasEntityItem = new NLCitem(aliasName, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(aliasEntityItem);
	
	int codeBlockType = NLC_CODEBLOCK_TYPE_ADD_ALIAS_TO_ENTITY_ALIAS_LIST;
	currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);
	
	#ifdef NLC_DEBUG_ADVANCED_REFERENCING_SUPPORT_ALIASES
	cout << "end createCodeBlocksAddAliasToEntityAliasList{}:" << endl;
	#endif
	
	return currentCodeBlockInTree;
}	

NLCcodeblock* createCodeBlocksFindAliasAndAddToCategoryListNewFunction(NLCcodeblock* currentCodeBlockInTree)
{
	#ifdef NLC_DEBUG_ADVANCED_REFERENCING_SUPPORT_ALIASES
	cout << "createCodeBlocksFindAliasAndAddToCategoryListNewFunction{}:" << endl;
	#endif
	
	//required because printCodeBlocks requires at least 1 param
	NLCitem* entityItem = new NLCitem("dummyentity", NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(entityItem);
	
	int codeBlockType = NLC_CODEBLOCK_TYPE_FIND_ALIAS_AND_ADD_TO_CATEGORY_LIST_NEW_FUNCTION;
	currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);

	#ifdef NLC_DEBUG_ADVANCED_REFERENCING_SUPPORT_ALIASES
	cout << "end createCodeBlocksFindAliasAndAddToCategoryListNewFunction{}:" << endl;
	#endif
	
	return currentCodeBlockInTree;
}
//NB genericListAppendName is "CategoryList"
NLCcodeblock* createCodeBlocksFindAliasAndAddToCategoryListExecuteFunction(NLCcodeblock* currentCodeBlockInTree, string aliasName, GIAentityNode* entity, string genericListAppendName, int sentenceIndex)
{
	#ifdef NLC_DEBUG_ADVANCED_REFERENCING_SUPPORT_ALIASES
	cout << "createCodeBlocksFindAliasAndAddToCategoryListExecuteFunction{}:" << endl;
	#endif
	
	NLCitem* aliasEntityItem = new NLCitem(aliasName, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(aliasEntityItem);

	//NB entity is used for both instance and category list
	NLCitem* entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT, sentenceIndex);
	currentCodeBlockInTree->parameters.push_back(entityItem);	
	
	NLCitem* genericListAppendItem = new NLCitem(genericListAppendName, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(genericListAppendItem);
	
	int codeBlockType = NLC_CODEBLOCK_TYPE_FIND_ALIAS_AND_ADD_TO_CATEGORY_LIST_EXECUTE_FUNCTION;
	currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);

	#ifdef NLC_DEBUG_ADVANCED_REFERENCING_SUPPORT_ALIASES
	cout << "end createCodeBlocksFindAliasAndAddToCategoryListExecuteFunction{}:" << endl;
	#endif
	
	return currentCodeBlockInTree;
}

NLCcodeblock* createCodeBlocksFindAliasNewFunction(NLCcodeblock* currentCodeBlockInTree)
{
	#ifdef NLC_DEBUG_ADVANCED_REFERENCING_SUPPORT_ALIASES
	cout << "createCodeBlocksFindAliasNewFunction{}:" << endl;
	#endif
	
	//required because printCodeBlocks requires at least 1 param
	NLCitem* entityItem = new NLCitem("dummyentity", NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(entityItem);
	
	int codeBlockType = NLC_CODEBLOCK_TYPE_FIND_ALIAS_NEW_FUNCTION;
	currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);

	#ifdef NLC_DEBUG_ADVANCED_REFERENCING_SUPPORT_ALIASES
	cout << "end createCodeBlocksFindAliasAndAddToCategoryListNewFunction{}:" << endl;
	#endif
	
	return currentCodeBlockInTree;
}	
NLCcodeblock* createCodeBlocksFindAliasExecuteFunction(NLCcodeblock* currentCodeBlockInTree, string aliasName, GIAentityNode* entity)
{
	#ifdef NLC_DEBUG_ADVANCED_REFERENCING_SUPPORT_ALIASES
	cout << "createCodeBlocksFindAliasExecuteFunction{}:" << endl;
	#endif
	
	NLCitem* aliasEntityItem = new NLCitem(aliasName, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(aliasEntityItem);

	//NB entity is used for both instance and category list
	NLCitem* entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(entityItem);	
	
	int codeBlockType = NLC_CODEBLOCK_TYPE_FIND_ALIAS_EXECUTE_FUNCTION;
	currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);

	#ifdef NLC_DEBUG_ADVANCED_REFERENCING_SUPPORT_ALIASES
	cout << "end createCodeBlocksFindAliasAndAddToCategoryListExecuteFunction{}:" << endl;
	#endif
	
	return currentCodeBlockInTree;
}

bool findAliasInEntity(GIAentityNode* entity, string* aliasName)
{
	bool result = false;
	if(!(entity->aliasList.empty()))
	{
		*aliasName = entity->aliasList.back();
		result = true;
	}
	return result;
}

#ifdef NLC_USE_ADVANCED_REFERENCING_SUPPORT_ALIASES_PREVENT_ADDING_AS_FUNCTION_ARGUMENT
unordered_map<string, string>* functionAliasClassList;	//<aliasName, aliasClassName>

unordered_map<string, string>* getFunctionAliasClassList()
{
	return functionAliasClassList;
}

void initialiseFunctionAliasClassList()
{
	#ifdef NLC_DEBUG_ADVANCED_REFERENCING_SUPPORT_ALIASES
	cout << "initialiseFunctionAliasClassList{}:" << endl;
	#endif
	//functionAliasClassList->clear();
	functionAliasClassList = new unordered_map<string, string>;
	#ifdef NLC_DEBUG_ADVANCED_REFERENCING_SUPPORT_ALIASES
	cout << "end initialiseFunctionAliasClassList{}" << endl;
	#endif
}

bool findEntityNameInFunctionAliasList(string aliasName, string* aliasClassName)
{
	#ifdef NLC_DEBUG_ADVANCED_REFERENCING_SUPPORT_ALIASES
	cout << "start findEntityNameInFunctionAliasList{}:" << endl;
	#endif
	bool result = false;
	unordered_map<string, string>::iterator iter1 = functionAliasClassList->find(aliasName);
	if(iter1 != functionAliasClassList->end())
	{
		*aliasClassName = iter1->second;
		result = true;
	}
	return result;
	#ifdef NLC_DEBUG_ADVANCED_REFERENCING_SUPPORT_ALIASES
	cout << "end findEntityNameInFunctionAliasList{}:" << endl;
	#endif
}
#endif
#endif


NLCcodeblock* clearCodeBlock(NLCcodeblock* codeBlock)
{
	codeBlock->codeBlockType = NLC_CODEBLOCK_TYPE_UNDEFINED;
	codeBlock->next = NULL;
	codeBlock->lowerLevel = NULL;
	codeBlock->parameters.clear();
	if(!(codeBlock->parameters.empty()))
	{
		cout << "error: !(codeBlock->parameters.empty())" << endl;
	}
	return codeBlock;
}

NLCcodeblock* createCodeBlockDebug(NLCcodeblock* currentCodeBlockInTree, string warning)
{
	NLCitem* debugItem = new NLCitem(warning, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(debugItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_DEBUG;
	currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}

#ifdef NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY_CHILDREN
string generateCategoryListPropertyCountVariableName(GIAentityNode* entity)
{
	string categoryListPropertyCountVariableName = generateInstanceName(entity) + NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION + NLC_ITEM_TYPE_LIST_VAR_APPENDITION + NLC_ITEM_TYPE_PROPERTYCOUNT_VAR_APPENDITION;	
	
	return categoryListPropertyCountVariableName;
}
#endif

bool findFunctionArgument(vector<NLCitem*>* parameters, GIAentityNode* entity, int itemType, NLCitem** functionArgument)
{
	bool foundFunctionArgument = false;
	for(vector<NLCitem*>::iterator parametersIterator = parameters->begin(); parametersIterator < parameters->end(); parametersIterator++)
	{
		NLCitem* currentItem = *parametersIterator;
		//cout << "currentItem->itemType = " << currentItem->itemType << endl;
		if(currentItem->itemType == itemType)
		{
			//cout << "(currentItem->itemType == itemType)" << endl;
			#ifdef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES
			if(currentItem->instanceName == generateInstanceName(entity))
			#else
			if(currentItem->name == entity->entityName)	//or if(currentItem->className == generateClassName(entity->entityName))
			#endif
			{
				//cout << "(currentItem->name)" << endl;
				*functionArgument = currentItem;
				foundFunctionArgument = true;	
			}
		}
	}
	return foundFunctionArgument;
}

NLCcodeblock* getLastCodeBlockInLevel(NLCcodeblock* currentCodeBlockInTree)
{
	while(currentCodeBlockInTree->next != NULL)
	{
		currentCodeBlockInTree = currentCodeBlockInTree->next;
	}
	return currentCodeBlockInTree;
}

#ifdef NLC_NORMALISE_TWOWAY_PREPOSITIONS
GIAentityNode* generateInverseConditionEntity(GIAentityNode* conditionEntity)
{
	GIAentityNode* conditionEntityInverse = new GIAentityNode();
	conditionEntityInverse->isCondition = true;
	conditionEntityInverse->entityName = conditionEntity->entityName;
	conditionEntityInverse->idInstance = conditionEntity->idInstance;
	conditionEntityInverse->conditionSubjectEntity->push_back(conditionEntity->conditionObjectEntity->back());	//CHECKTHIS: reused existing connections
	conditionEntityInverse->conditionObjectEntity->push_back(conditionEntity->conditionSubjectEntity->back());	//CHECKTHIS: reused existing connections
	return conditionEntityInverse;
}
#endif


#ifdef NLC_SUPPORT_REDEFINITIONS
NLCcodeblock* createCodeBlockCheckParentClassNameExecuteFunction1(NLCcodeblock* currentCodeBlockInTree, string objectInstanceName, string classNameToFind)
{
	NLCitem* objectItem = new NLCitem("object", NLC_ITEM_TYPE_OBJECT);
	objectItem->instanceName = objectInstanceName;
	currentCodeBlockInTree->parameters.push_back(objectItem);
	
	NLCitem* classNameToFindItem = new NLCitem(classNameToFind, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(classNameToFindItem);
		
	int codeBlockType = NLC_CODEBLOCK_TYPE_CHECK_PARENT_CLASS_NAME_EXECUTE_FUNCTION1;
	currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);
	
	return currentCodeBlockInTree;
}
NLCcodeblock* createCodeBlockCheckParentClassNameExecuteFunction1(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* object, string classNameToFind)
{
	NLCitem* objectItem = new NLCitem(object, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(objectItem);

	NLCitem* classNameToFindItem = new NLCitem(classNameToFind, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(classNameToFindItem);
		
	int codeBlockType = NLC_CODEBLOCK_TYPE_CHECK_PARENT_CLASS_NAME_EXECUTE_FUNCTION1;
	currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);
	
	return currentCodeBlockInTree;
}
NLCcodeblock* createCodeBlockCheckParentClassNameExecuteFunction2(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* object, string classNameToFind)
{
	NLCitem* objectItem = new NLCitem(object, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(objectItem);

	NLCitem* classNameToFindItem = new NLCitem(classNameToFind, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(classNameToFindItem);
		
	int codeBlockType = NLC_CODEBLOCK_TYPE_CHECK_PARENT_CLASS_NAME_EXECUTE_FUNCTION2;
	currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);
	
	return currentCodeBlockInTree;
}
NLCcodeblock* createCodeBlockCheckParentClassNameNewFunction(NLCcodeblock* currentCodeBlockInTree)
{
	//required because printCodeBlocks requires at least 1 param
	NLCitem* entityItem = new NLCitem("dummyentity", NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(entityItem);
	
	int codeBlockType = NLC_CODEBLOCK_TYPE_CHECK_PARENT_CLASS_NAME_NEW_FUNCTION;
	currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}

NLCcodeblock* createCodeConvertParentToChildClass(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* parentEntity, GIAentityNode* childEntity)
{
	NLCitem* parentItem = new NLCitem(parentEntity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(parentItem);

	NLCitem* childItem = new NLCitem(childEntity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(childItem);
		
	int codeBlockType = NLC_CODEBLOCK_TYPE_CONVERT_PARENT_TO_CHILD_CLASS;
	currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);
	
	return currentCodeBlockInTree;
}
#endif

NLCcodeblock* createCodeBlockDeclareTempVariable(NLCcodeblock* currentCodeBlockInTree, string tempVariableClassName, string tempVariableInstanceName)
{
	NLCitem* tempVariableItem = new NLCitem(tempVariableInstanceName, NLC_ITEM_TYPE_OBJECT);
	tempVariableItem->className = tempVariableClassName;
	tempVariableItem->instanceName = tempVariableInstanceName;
	currentCodeBlockInTree->parameters.push_back(tempVariableItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_DECLARE_TEMP_VARIABLE;
	currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);
	
	return currentCodeBlockInTree;
}

NLCcodeblock* createCodeBlockSetTempVariable(NLCcodeblock* currentCodeBlockInTree, string tempVariableInstanceName, GIAentityNode* entity)
{
	NLCitem* tempVariableItem = new NLCitem(tempVariableInstanceName, NLC_ITEM_TYPE_OBJECT);
	tempVariableItem->instanceName = tempVariableInstanceName;
	currentCodeBlockInTree->parameters.push_back(tempVariableItem);

	NLCitem* entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(entityItem);
	
	int codeBlockType = NLC_CODEBLOCK_TYPE_SET_TEMP_VARIABLE;
	currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);
	
	return currentCodeBlockInTree;
}

NLCcodeblock* createCodeBlockDeclareTempVariableAndSetToEntity(NLCcodeblock* currentCodeBlockInTree, string tempVariableClassName, string tempVariableInstanceName, GIAentityNode* entity)
{
	NLCitem* tempVariableItem = new NLCitem(tempVariableInstanceName, NLC_ITEM_TYPE_OBJECT);
	tempVariableItem->className = tempVariableClassName;
	tempVariableItem->instanceName = tempVariableInstanceName;
	currentCodeBlockInTree->parameters.push_back(tempVariableItem);

	NLCitem* entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(entityItem);
	
	int codeBlockType = NLC_CODEBLOCK_TYPE_DECLARE_TEMP_VARIABLE_AND_SET_TO_ENTITY;
	currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);
	
	return currentCodeBlockInTree;
}

NLCcodeblock* createCodeBlockIfTempVariableEqualsEntity(NLCcodeblock* currentCodeBlockInTree, string tempVariableClassName, string tempVariableInstanceName, GIAentityNode* entity)
{
	NLCitem* tempVariableItem = new NLCitem(tempVariableInstanceName, NLC_ITEM_TYPE_OBJECT);
	tempVariableItem->className = tempVariableClassName;
	tempVariableItem->instanceName = tempVariableInstanceName;
	currentCodeBlockInTree->parameters.push_back(tempVariableItem);

	NLCitem* entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(entityItem);
	
	int codeBlockType = NLC_CODEBLOCK_TYPE_IF_TEMP_VARIABLE_EQUALS_ENTITY;
	currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);
	
	return currentCodeBlockInTree;
}

#ifdef NLC_USE_NON_LIBRARY_FUNCTIONS_EXTENDED
NLCcodeblock* createCodeBlockAddPropertyNewFunction(NLCcodeblock* currentCodeBlockInTree)
{
	//required because printCodeBlocks requires at least 1 param
	NLCitem* entityItem = new NLCitem("dummyentity", NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(entityItem);
	
	int codeBlockType = NLC_CODEBLOCK_TYPE_ADD_PROPERTY_NEW_FUNCTION;
	currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}

NLCcodeblock* createCodeBlockAddConditionNewFunction(NLCcodeblock* currentCodeBlockInTree)
{
	//required because printCodeBlocks requires at least 1 param
	NLCitem* entityItem = new NLCitem("dummyentity", NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(entityItem);
	
	int codeBlockType = NLC_CODEBLOCK_TYPE_ADD_CONDITION_NEW_FUNCTION;
	currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}
#ifdef NLC_NORMALISE_TWOWAY_PREPOSITIONS_MARK_INVERSE_CONDITIONS
NLCcodeblock* createCodeBlockAddConditionInverseNewFunction(NLCcodeblock* currentCodeBlockInTree)
{
	//required because printCodeBlocks requires at least 1 param
	NLCitem* entityItem = new NLCitem("dummyentity", NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(entityItem);
	
	int codeBlockType = NLC_CODEBLOCK_TYPE_ADD_CONDITION_INVERSE_NEW_FUNCTION;
	currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}
#endif
#endif


#ifdef NLC_USE_MATH_OBJECTS
NLCcodeblock* createCodeBlockSetMathValue(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* valueEntity)
{
	NLCitem* entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	NLCitem* valueItem = new NLCitem(valueEntity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(valueItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_SET_MATH_VALUE;
	currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);
	
	return currentCodeBlockInTree;
}

NLCcodeblock* createCodeBlockDeclareNewDecimalPointerVar(NLCcodeblock* currentCodeBlockInTree, string decimalPointerVariableName)
{
	NLCitem* decimalPointerItem = new NLCitem(decimalPointerVariableName, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(decimalPointerItem);
		
	int codeBlockType = NLC_CODEBLOCK_TYPE_DECLARE_NEW_DECIMAL_POINTER_VARIABLE;

	return createCodeBlock(currentCodeBlockInTree, codeBlockType);
}

NLCcodeblock* createCodeBlockSetDecimalPointerToEntityMathValue(NLCcodeblock* currentCodeBlockInTree, string decimalPointerVariableName, GIAentityNode* entity)
{
	NLCitem* decimalPointerItem = new NLCitem(decimalPointerVariableName, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(decimalPointerItem);
	
	NLCitem* entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_SET_DECIMAL_POINTER_TO_ENTITY_MATH_VALUE;
	currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);
	
	return currentCodeBlockInTree;
}

//check that pointer is not NULL
#ifdef NLC_MATH_OBJECTS_TEST_NULL_POINTER_MAINTAIN_CONTEXT
NLCcodeblock* createCodeBlockTestDecimalPointerValue(NLCcodeblock* currentCodeBlockInTree, string decimalPointerVariableName)
{
	NLCitem* decimalPointerItem = new NLCitem(decimalPointerVariableName, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(decimalPointerItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_TEST_DECIMAL_POINTER_VALUE;
	currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);
	
	return currentCodeBlockInTree;
}
#else
NLCcodeblock* createCodeBlockCheckDecimalPointerValue(NLCcodeblock* currentCodeBlockInTree, string decimalPointerVariableName)
{
	NLCitem* decimalPointerItem = new NLCitem(decimalPointerVariableName, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(decimalPointerItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_CHECK_DECIMAL_POINTER_VALUE;
	currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);
	
	return currentCodeBlockInTree;
}
#endif

#endif


#ifdef NLC_USE_SUPPORT_REFERENCING_OBJECTS_IN_PLURAL_LIST_BY_NUMBER
bool checkNumericalReferenceToEntity(GIAentityNode* entity)
{
	bool numericalReference = false;
	if((entity->hasQuantity) && (entity->grammaticalNumber != GRAMMATICAL_NUMBER_PLURAL))
	{
		numericalReference = true;
	}
	return numericalReference;
}
#endif

