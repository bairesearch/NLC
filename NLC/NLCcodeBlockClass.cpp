/*******************************************************************************
 *
 * This file is part of BAIPROJECT.
 *
 * BAIPROJECT is licensed under the GNU Affero General Public License
 * version 3, as published by the Free Software Foundation. The use of
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
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2017 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 2a2b 21-March-2017
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/


#include "NLCcodeBlockClass.hpp"

static int currentLogicalConditionLevel;
int NLCcodeBlockClassClass::getCurrentLogicalConditionLevel()
{
	return currentLogicalConditionLevel;
}
void NLCcodeBlockClassClass::setCurrentLogicalConditionLevel(const int value)
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

	#ifdef NLC_ADVANCED_REFERENCING_MONITOR_CONTEXT
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
	negative = BOOL_IRRELEVANT;
	#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
	onlyGenerateContextBlocksIfConnectionsParsedForNLCorSameReferenceSet = true;
	#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_BASIC_GENERATE_CONTEXT_BLOCKS_IF_SAME_REFERENCE_SET
	generateContextBlocksIfSameReferenceSet = true;
	#endif
	#endif
	#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
	negativeDetectedInContextBlocks = false;
	#ifdef NLC_TRANSLATOR_LOGICAL_CONDITIONS_SINGLE_SENTENCE_MULTIPLE_LEVEL_FOR_LOOPS_OLD
	#ifndef NLC_GENERATE_UNIQUE_CONTEXT_BLOCK_FOR_EACH_SENTENCE_LOGICAL_CONDITIONS_FOR_LOOPS
	setCodeBlockInTreeAtBaseLevel = false;
	currentCodeBlockInTreeAtBaseLevel = NULL;
	#endif
	#endif
	#endif
	#ifdef NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY
	testNumerosity = false;
	#ifdef NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY_BASIC
	childQuantity = 1;
	#endif
	#endif
	#ifdef NLC_FUNCTIONS_SUPPORT_PLURAL_SUBJECTS_AND_OBJECTS
	enterGeneratedCategoryList = true;
	#endif
	#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN
	searchConceptsForChildren = true;
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
	#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN_SUBCLASSES
	searchSubclassesForChildren = true;
	#endif
	#ifdef NLC_TRANSLATOR_LOGICAL_CONDITIONS_BOOLEAN_STATEMENTS_INTERPRET_SUBJECT_AND_OBJECT_INDEPENDENTLY
	logicalConditionStatement = false;
	secondaryComparison = false;
	#endif
}
NLCgenerateContextBlocksVariables::~NLCgenerateContextBlocksVariables(void)
{
}



//Resultant code: functionItem[context].functionItem[name](objectItem[context].objectItem[name]);	//NB functionItem[context] = action subject
NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockExecuteSubjectObject(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* actionRelationshipEntity, const GIAentityNode* subjectEntity, const GIAentityNode* objectEntity, const int sentenceIndex)
{
	NLCitem* functionItem = new NLCitem(actionRelationshipEntity, NLC_ITEM_TYPE_FUNCTION_EXECUTION_ARGUMENT_FUNCTION, sentenceIndex);
	NLCitem* functionSubjectItem = new NLCitem(subjectEntity, NLC_ITEM_TYPE_FUNCTION_EXECUTION_ARGUMENT_FUNCTION_OWNER, sentenceIndex);
	NLCitem* functionObjectItem = new NLCitem(objectEntity, NLC_ITEM_TYPE_FUNCTION_EXECUTION_ARGUMENT_FUNCTION_OBJECT, sentenceIndex);

	currentCodeBlockInTree->parameters.push_back(functionSubjectItem);
	currentCodeBlockInTree->parameters.push_back(functionItem);
	currentCodeBlockInTree->parameters.push_back(functionObjectItem);

	return this->createCodeBlock(currentCodeBlockInTree, NLC_CODEBLOCK_TYPE_EXECUTE_FUNCTION);
}

NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockExecuteSubject(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* actionRelationshipEntity, const GIAentityNode* subjectEntity, const int sentenceIndex)
{
	NLCitem* functionItem = new NLCitem(actionRelationshipEntity, NLC_ITEM_TYPE_FUNCTION_EXECUTION_ARGUMENT_FUNCTION, sentenceIndex);
	NLCitem* functionSubjectItem = new NLCitem(subjectEntity, NLC_ITEM_TYPE_FUNCTION_EXECUTION_ARGUMENT_FUNCTION_OWNER, sentenceIndex);

	currentCodeBlockInTree->parameters.push_back(functionSubjectItem);
	currentCodeBlockInTree->parameters.push_back(functionItem);

	return this->createCodeBlock(currentCodeBlockInTree, NLC_CODEBLOCK_TYPE_EXECUTE_FUNCTION);
}

NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockExecuteObject(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* actionRelationshipEntity, const GIAentityNode* objectEntity, const int sentenceIndex)
{
	NLCitem* functionItem = new NLCitem(actionRelationshipEntity, NLC_ITEM_TYPE_FUNCTION_EXECUTION_ARGUMENT_FUNCTION, sentenceIndex);
	NLCitem* functionObjectItem = new NLCitem(objectEntity, NLC_ITEM_TYPE_FUNCTION_EXECUTION_ARGUMENT_FUNCTION_OBJECT, sentenceIndex);

	currentCodeBlockInTree->parameters.push_back(functionItem);
	currentCodeBlockInTree->parameters.push_back(functionObjectItem);

	return this->createCodeBlock(currentCodeBlockInTree, NLC_CODEBLOCK_TYPE_EXECUTE_FUNCTION);
}

NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockExecute(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* actionRelationshipEntity, const int sentenceIndex)
{
	NLCitem* functionItem = new NLCitem(actionRelationshipEntity, NLC_ITEM_TYPE_FUNCTION_EXECUTION_ARGUMENT_FUNCTION, sentenceIndex);

	currentCodeBlockInTree->parameters.push_back(functionItem);

	return this->createCodeBlock(currentCodeBlockInTree, NLC_CODEBLOCK_TYPE_EXECUTE_FUNCTION);
}

#ifdef NLC_RECORD_ACTION_HISTORY
NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockRecordHistoryActionSubject(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* actionRelationshipEntity, const GIAentityNode* subjectEntity)
{
	NLCitem* functionItem = new NLCitem(actionRelationshipEntity, NLC_ITEM_TYPE_FUNCTION_EXECUTION_ARGUMENT_FUNCTION);
	NLCitem* functionSubjectItem = new NLCitem(subjectEntity, NLC_ITEM_TYPE_FUNCTION_EXECUTION_ARGUMENT_FUNCTION_OWNER);

	currentCodeBlockInTree->parameters.push_back(functionSubjectItem);
	currentCodeBlockInTree->parameters.push_back(functionItem);

	return this->createCodeBlock(currentCodeBlockInTree, NLC_CODEBLOCK_TYPE_RECORD_HISTORY_ACTION_SUBJECT);
}

NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockRecordHistoryActionObject(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* actionRelationshipEntity, const GIAentityNode* objectEntity)
{
	NLCitem* functionItem = new NLCitem(actionRelationshipEntity, NLC_ITEM_TYPE_FUNCTION_EXECUTION_ARGUMENT_FUNCTION);
	NLCitem* functionObjectItem = new NLCitem(objectEntity, NLC_ITEM_TYPE_FUNCTION_EXECUTION_ARGUMENT_FUNCTION_OBJECT);

	currentCodeBlockInTree->parameters.push_back(functionItem);
	currentCodeBlockInTree->parameters.push_back(functionObjectItem);

	return this->createCodeBlock(currentCodeBlockInTree, NLC_CODEBLOCK_TYPE_RECORD_HISTORY_ACTION_OBJECT);
}
#endif


//add property

NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockCreateNewProperty(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* propertyRelationshipObjectEntity, int sentenceIndex, bool copyNewItemsToLocalList)
{
	#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_BLOCKS_FOR_PARENT_INITIALISATION_SPECIAL
	currentCodeBlockInTree = this->createCodeBlocksDeclareNewCategoryListVariable(currentCodeBlockInTree, propertyRelationshipObjectEntity, NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION, sentenceIndex);	//create new category list
	#endif
	currentCodeBlockInTree = this->createCodeBlockAddNewProperty(currentCodeBlockInTree, entity, propertyRelationshipObjectEntity, sentenceIndex, copyNewItemsToLocalList);
	return currentCodeBlockInTree;
}

NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockAddNewProperty(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, GIAentityNode* propertyRelationshipObjectEntity, int sentenceIndex, const bool copyNewItemsToLocalList)
{
	#ifdef NLC_QUANTITIES
	NLCcodeblock* origCurrentCodeBlockInTree = currentCodeBlockInTree;
	if(propertyRelationshipObjectEntity->quantityNumber > 1)
	{
		string numberIterationsOrVariable = SHAREDvars.convertIntToString(propertyRelationshipObjectEntity->quantityNumber);
		#ifdef NLC_PREPROCESSOR_MATH_REPLACE_NUMERICAL_VARIABLES_NAMES_FOR_NLP
		if(propertyRelationshipObjectEntity->NLCoriginalNumericalVariableName != "")
		{
			numberIterationsOrVariable = propertyRelationshipObjectEntity->NLCoriginalNumericalVariableName;
		}
		#endif
		currentCodeBlockInTree = this->createCodeBlockForInteger(currentCodeBlockInTree, numberIterationsOrVariable);
	}
	//for(int i=0; i<propertyRelationshipObjectEntity->quantityNumber; i++)
	//{
	#endif

	NLCitem* entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	NLCitem* propertyItem = new NLCitem(propertyRelationshipObjectEntity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(propertyItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_ADD_NEW_PROPERTY;
	currentCodeBlockInTree = this->createCodeBlock(currentCodeBlockInTree, codeBlockType);

	#ifdef NLC_DEFINE_LOCAL_VARIABLES_FOR_ALL_INDEFINATE_ENTITIES
	if(copyNewItemsToLocalList)
	{
		if(propertyRelationshipObjectEntity->NLClocalListVariableHasBeenDeclared)
		{//added 1g8a 11-July-2014
			currentCodeBlockInTree = this->createCodeBlockAddEntityToLocalList(currentCodeBlockInTree, propertyRelationshipObjectEntity, propertyRelationshipObjectEntity);
			propertyRelationshipObjectEntity->NLClocalListVariableHasBeenInitialised = true;

		}
		else
		{
		}
	}
	else
	{
	}
	#endif

	#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_BLOCKS_FOR_PARENT_INITIALISATION_SPECIAL
	currentCodeBlockInTree = this->createCodeBlockAddEntityToCategoryList(currentCodeBlockInTree, propertyRelationshipObjectEntity, propertyRelationshipObjectEntity, NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION, sentenceIndex);	//add new object to category list
	#endif
	#ifdef NLC_ADVANCED_REFERENCING
	#ifdef NLC_ADVANCED_REFERENCING_MONITOR_CONTEXT
	currentCodeBlockInTree =  this->createCodeBlocksAddEntityToContextLevelListExecuteFunction(currentCodeBlockInTree, this->getCurrentLogicalConditionLevel(), propertyRelationshipObjectEntity, sentenceIndex);
	#else
	currentCodeBlockInTree = this->createCodeBlockUpdateLastSentenceReferenced(currentCodeBlockInTree, propertyRelationshipObjectEntity, sentenceIndex);
	#endif
	#endif

	#ifdef NLC_QUANTITIES
	if(propertyRelationshipObjectEntity->quantityNumber > 1)
	{
		currentCodeBlockInTree = origCurrentCodeBlockInTree->next;
	}
	//}
	#endif

	return currentCodeBlockInTree;
}

NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockAddNewEntityToLocalList(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, int sentenceIndex, const bool addReferencingContext)
{
	#ifdef NLC_QUANTITIES
	NLCcodeblock* origCurrentCodeBlockInTree = currentCodeBlockInTree;
	if(entity->quantityNumber > 1)
	{
		string numberIterationsOrVariable = SHAREDvars.convertIntToString(entity->quantityNumber);
		#ifdef NLC_PREPROCESSOR_MATH_REPLACE_NUMERICAL_VARIABLES_NAMES_FOR_NLP
		if(entity->NLCoriginalNumericalVariableName != "")
		{
			numberIterationsOrVariable = entity->NLCoriginalNumericalVariableName;
		}
		#endif
		currentCodeBlockInTree = this->createCodeBlockForInteger(currentCodeBlockInTree, numberIterationsOrVariable);
	}
	//for(int i=0; i<entity->quantityNumber; i++)
	//{
	#endif

	int codeBlockType;
	#ifdef NLC_DO_NOT_CREATE_LOCAL_LISTS_FOR_QUALITIES
	if(entity->entityType == GIA_ENTITY_TYPE_QUALITY)
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
	currentCodeBlockInTree = this->createCodeBlock(currentCodeBlockInTree, codeBlockType);
	
	if(addReferencingContext)
	{
		#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_BLOCKS_FOR_PARENT_INITIALISATION_SPECIAL
		currentCodeBlockInTree = this->createCodeBlockAddEntityToCategoryList(currentCodeBlockInTree, entity, entity, NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION, sentenceIndex);	//add new object to category list
		#endif
		#ifdef NLC_ADVANCED_REFERENCING
		#ifdef NLC_ADVANCED_REFERENCING_MONITOR_CONTEXT
		currentCodeBlockInTree = this->createCodeBlocksAddEntityToContextLevelListExecuteFunction(currentCodeBlockInTree, this->getCurrentLogicalConditionLevel(), entity, sentenceIndex);
		#else
		currentCodeBlockInTree = this->createCodeBlockUpdateLastSentenceReferenced(currentCodeBlockInTree, entity, sentenceIndex);
		#endif
		#endif
	}

	#ifdef NLC_QUANTITIES
	if(entity->quantityNumber > 1)
	{
		currentCodeBlockInTree = origCurrentCodeBlockInTree->next;
	}
	//}
	#endif

	return currentCodeBlockInTree;
}

NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockAddEntityToLocalList(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* localListEntity, const GIAentityNode* entity)
{
	NLCitem* entityItem = new NLCitem(localListEntity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	NLCitem* propertyItem = new NLCitem( entity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(propertyItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_LOCAL_LIST;
	currentCodeBlockInTree = this->createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}

NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockAddProperty(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const GIAentityNode* propertyRelationshipObjectEntity, const int sentenceIndex)
{
	NLCitem* entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	NLCitem* propertyItem = new NLCitem(propertyRelationshipObjectEntity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(propertyItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_ADD_PROPERTY;
	currentCodeBlockInTree = this->createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}



NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockCreateNewCondition(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* conditionRelationshipEntity, int sentenceIndex, bool copyNewItemsToLocalList)
{
	#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_BLOCKS_FOR_PARENT_INITIALISATION_SPECIAL
	if(!(conditionRelationshipEntity->relationshipObjectEntity->empty()))
	{
		GIAentityNode* conditionRelationshipObjectEntity = (conditionRelationshipEntity->relationshipObjectEntity->back())->entity;
		currentCodeBlockInTree = this->createCodeBlocksDeclareNewCategoryListVariable(currentCodeBlockInTree, conditionRelationshipObjectEntity, NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION, sentenceIndex);	//create new category list
	}
	#endif
	currentCodeBlockInTree = this->createCodeBlockAddNewCondition(currentCodeBlockInTree, entity, conditionRelationshipEntity, sentenceIndex, copyNewItemsToLocalList);
	return currentCodeBlockInTree;
}


NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockAddNewCondition(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* conditionRelationshipEntity, int sentenceIndex, const bool copyNewItemsToLocalList)
{
	if(!(conditionRelationshipEntity->relationshipObjectEntity->empty()))
	{
		GIAentityNode* conditionRelationshipObjectEntity = (conditionRelationshipEntity->relationshipObjectEntity->back())->entity;

		#ifdef NLC_QUANTITIES
		NLCcodeblock* origCurrentCodeBlockInTree = currentCodeBlockInTree;
		if(conditionRelationshipObjectEntity->quantityNumber > 1)
		{
			string numberIterationsOrVariable = SHAREDvars.convertIntToString(conditionRelationshipObjectEntity->quantityNumber);
			#ifdef NLC_PREPROCESSOR_MATH_REPLACE_NUMERICAL_VARIABLES_NAMES_FOR_NLP
			if(conditionRelationshipObjectEntity->NLCoriginalNumericalVariableName != "")
			{
				numberIterationsOrVariable = conditionRelationshipObjectEntity->NLCoriginalNumericalVariableName;
			}
			#endif
			currentCodeBlockInTree = this->createCodeBlockForInteger(currentCodeBlockInTree, numberIterationsOrVariable);
		}
		//for(int i=0; i<conditionRelationshipObjectEntity->quantityNumber; i++)
		//{
		#endif

		currentCodeBlockInTree = this->createCodeBlockAddNewConditionSimple(currentCodeBlockInTree, entity, conditionRelationshipEntity, conditionRelationshipObjectEntity);
		#ifdef NLC_NORMALISE_TWOWAY_PREPOSITIONS
		if(conditionRelationshipEntity->conditionTwoWay)
		{
			GIAentityNode* entityInverse = conditionRelationshipObjectEntity;
			GIAentityNode* conditionEntityInverse = NULL;
			conditionEntityInverse = this->generateInverseConditionEntity(conditionRelationshipEntity);
			currentCodeBlockInTree = this->createCodeBlockAddConditionSimpleInverse(currentCodeBlockInTree, conditionRelationshipObjectEntity, conditionEntityInverse, entity);
		}
		#endif

		#ifdef NLC_DEFINE_LOCAL_VARIABLES_FOR_ALL_INDEFINATE_ENTITIES
		if(copyNewItemsToLocalList)
		{
			if(conditionRelationshipObjectEntity->NLClocalListVariableHasBeenDeclared)
			{//added 1g8a 11-July-2014
				currentCodeBlockInTree = this->createCodeBlockAddEntityToLocalList(currentCodeBlockInTree, conditionRelationshipObjectEntity, conditionRelationshipObjectEntity);
				conditionRelationshipObjectEntity->NLClocalListVariableHasBeenInitialised = true;

			}
		}
		#endif

		#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_BLOCKS_FOR_PARENT_INITIALISATION_SPECIAL
		currentCodeBlockInTree = this->createCodeBlockAddEntityToCategoryList(currentCodeBlockInTree, conditionRelationshipObjectEntity, conditionRelationshipObjectEntity, NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION, sentenceIndex);	//add new object to category list
		#endif
		#ifdef NLC_ADVANCED_REFERENCING
		#ifdef NLC_ADVANCED_REFERENCING_MONITOR_CONTEXT
		currentCodeBlockInTree =  this->createCodeBlocksAddEntityToContextLevelListExecuteFunction(currentCodeBlockInTree, this->getCurrentLogicalConditionLevel(), conditionRelationshipObjectEntity, sentenceIndex);
		#else
		currentCodeBlockInTree = this->createCodeBlockUpdateLastSentenceReferenced(currentCodeBlockInTree, conditionRelationshipObjectEntity, sentenceIndex);
		#endif
		#endif

		#ifdef NLC_QUANTITIES
		if(conditionRelationshipObjectEntity->quantityNumber > 1)
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

NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockAddNewConditionSimple(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const GIAentityNode* conditionRelationshipEntity, const GIAentityNode* conditionRelationshipObjectEntity)
{
	NLCitem* entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	NLCitem* conditionItem = new NLCitem(conditionRelationshipEntity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(conditionItem);

	NLCitem* conditionObjectItem = new NLCitem(conditionRelationshipObjectEntity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(conditionObjectItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_ADD_NEW_CONDITION;
	currentCodeBlockInTree = this->createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}

NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockAddCondition(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* conditionRelationshipEntity, const int sentenceIndex)
{
	if(!(conditionRelationshipEntity->relationshipObjectEntity->empty()))
	{
		GIAentityNode* conditionRelationshipObjectEntity = (conditionRelationshipEntity->relationshipObjectEntity->back())->entity;

		currentCodeBlockInTree = this->createCodeBlockAddConditionSimple(currentCodeBlockInTree, entity, conditionRelationshipEntity, conditionRelationshipObjectEntity);
		#ifdef NLC_NORMALISE_TWOWAY_PREPOSITIONS
		if(conditionRelationshipEntity->conditionTwoWay)
		{
			GIAentityNode* entityInverse = conditionRelationshipObjectEntity;
			GIAentityNode* conditionEntityInverse = NULL;
			conditionEntityInverse = this->generateInverseConditionEntity(conditionRelationshipEntity);
			currentCodeBlockInTree = this->createCodeBlockAddConditionSimpleInverse(currentCodeBlockInTree, conditionRelationshipObjectEntity, conditionEntityInverse, entity);
		}
		#endif
	}
	else
	{
		cout << "error: condition does not have object" << endl;
	}

	return currentCodeBlockInTree;
}

NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockAddConditionSimple(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const GIAentityNode* conditionRelationshipEntity, const GIAentityNode* conditionRelationshipObjectEntity)
{
	NLCitem* entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
	//removed 1e7c as it is not used: getEntityContext(entity, &(entityItem->context), false, sentenceIndex, false);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	NLCitem* conditionItem = new NLCitem(conditionRelationshipEntity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(conditionItem);

	NLCitem* conditionObjectItem = new NLCitem(conditionRelationshipObjectEntity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(conditionObjectItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_ADD_CONDITION;
	currentCodeBlockInTree = this->createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}

#ifdef NLC_NORMALISE_TWOWAY_PREPOSITIONS
NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockAddConditionSimpleInverse(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* conditionRelationshipEntity, GIAentityNode* conditionRelationshipObjectEntity)
{
	#ifdef NLC_NORMALISE_TWOWAY_PREPOSITIONS_MARK_INVERSE_CONDITIONS
	NLCitem* entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
	//removed 1e7c as it is not used: getEntityContext(entity, &(entityItem->context), false, sentenceIndex, false);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	NLCitem* conditionItem = new NLCitem(conditionRelationshipEntity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(conditionItem);

	NLCitem* conditionObjectItem = new NLCitem(conditionRelationshipObjectEntity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(conditionObjectItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_ADD_CONDITION_INVERSE;
	currentCodeBlockInTree = this->createCodeBlock(currentCodeBlockInTree, codeBlockType);
	#else
	currentCodeBlockInTree = this->createCodeBlockAddConditionSimple(currentCodeBlockInTree, entity, conditionRelationshipEntity, conditionRelationshipObjectEntity);
	#endif
	return currentCodeBlockInTree;
}
#endif


NLCcodeblock* NLCcodeBlockClassClass::createCodeBlocksCreateNewLocalListVariable(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, int sentenceIndex)
{
	#ifdef NLC_DO_NOT_CREATE_LOCAL_LISTS_FOR_QUALITIES
	if(!(entity->entityType == GIA_ENTITY_TYPE_QUALITY))
	{
	#endif
		currentCodeBlockInTree = this->createCodeBlocksDeclareNewLocalListVariableIfNecessary(currentCodeBlockInTree, entity);
	#ifdef NLC_DO_NOT_CREATE_LOCAL_LISTS_FOR_QUALITIES
	}
	#endif
	#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_BLOCKS_FOR_PARENT_INITIALISATION_SPECIAL
	currentCodeBlockInTree = this->createCodeBlocksDeclareNewCategoryListVariable(currentCodeBlockInTree, entity, NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION, sentenceIndex);	//create new category list
	#endif
	currentCodeBlockInTree = this->createCodeBlockAddNewEntityToLocalList(currentCodeBlockInTree, entity, sentenceIndex, true);
	return currentCodeBlockInTree;
}

NLCcodeblock* NLCcodeBlockClassClass::createCodeBlocksDeclareNewLocalListVariableIfNecessary(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity)
{
	bool setNLCLocalListVariableHasBeenDeclared = true;
	#ifdef NLC_GENERATE_UNIQUE_CONTEXT_BLOCK_FOR_EACH_SENTENCE
	if(entity->entityType == GIA_ENTITY_TYPE_ACTION)
	{
		setNLCLocalListVariableHasBeenDeclared = false;
	}
	#endif
	#ifdef NLC_DO_NOT_PREDECLARE_LOCAL_LISTS_FOR_QUALITIES
	#ifndef NLC_DO_NOT_CREATE_LOCAL_LISTS_FOR_QUALITIES
	if(entity->entityType == GIA_ENTITY_TYPE_QUALITY)
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
		GIAentityNode* networkIndexEntity = GIAtranslatorOperations.getPrimaryNetworkIndexNodeDefiningInstance(entity);
		if(!(networkIndexEntity->NLClocalListVariableHasBeenDeclared))
		{
			networkIndexEntity->NLClocalListVariableHasBeenDeclared = true;
		#endif

			currentCodeBlockInTree = this->createCodeBlocksDeclareNewLocalListVariable(currentCodeBlockInTree, entity, setNLCLocalListVariableHasBeenDeclared);
		}
	}
	else
	{
		currentCodeBlockInTree = this->createCodeBlocksDeclareNewLocalListVariable(currentCodeBlockInTree, entity, setNLCLocalListVariableHasBeenDeclared);
	}

	return currentCodeBlockInTree;
}

NLCcodeblock* NLCcodeBlockClassClass::createCodeBlocksDeclareNewLocalListVariable(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, const bool createTypeList)
{
	NLCitem* entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_DECLARE_NEW_LOCAL_LIST_VARIABLE;
	currentCodeBlockInTree = this->createCodeBlock(currentCodeBlockInTree, codeBlockType);

	#ifdef NLC_GENERATE_TYPE_LISTS
	if(createTypeList)
	{
		currentCodeBlockInTree = this->createIfNecessaryAndAddToTypeList(currentCodeBlockInTree, entity);
	}
	#endif

	return currentCodeBlockInTree;
}

#ifdef NLC_GENERATE_TYPE_LISTS
NLCcodeblock* NLCcodeBlockClassClass::createIfNecessaryAndAddToTypeList(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity)
{
	#ifdef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES
	if(!(GIAtranslatorOperations.getPrimaryNetworkIndexNodeDefiningInstance(entity)->NLClocalListVariableHasBeenDeclared))	//ie typeList has not been declared (NLC_LOCAL_LISTS_USE_INSTANCE_NAMES:networkIndexEntity->NLClocalListVariableHasBeenDeclared)
	{
	#endif
		//declare a generic type list (typeList) of local instance lists (instanceLists)
		currentCodeBlockInTree = this->createCodeBlocksDeclareNewTypeListVariable(currentCodeBlockInTree, entity);

	#ifdef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES
		GIAtranslatorOperations.getPrimaryNetworkIndexNodeDefiningInstance(entity)->NLClocalListVariableHasBeenDeclared = true;	//ie typeList has been declared (NLC_LOCAL_LISTS_USE_INSTANCE_NAMES:networkIndexEntity->NLClocalListVariableHasBeenDeclared)
	}
	#endif

	//add local instance list to generic type list
	currentCodeBlockInTree = this->createCodeBlockAddInstanceListToTypeList(currentCodeBlockInTree, entity, entity);	
	
	return currentCodeBlockInTree;
}
#endif



NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockForOrInPropertyList(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, string context)
{
	#ifdef NLC_REFERENCING_OBJECTS_IN_PLURAL_LIST_BY_NUMBER
	if(this->checkNumericalReferenceToEntity(entity))
	{
		currentCodeBlockInTree = this->createCodeBlockInPropertyList(currentCodeBlockInTree, entity, context, entity->quantityNumber);
	}
	else
	{
	#endif
		currentCodeBlockInTree = this->createCodeBlockForPropertyList(currentCodeBlockInTree, entity, context);
	#ifdef NLC_REFERENCING_OBJECTS_IN_PLURAL_LIST_BY_NUMBER
	}
	#endif
	return currentCodeBlockInTree;
}
NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockForOrInPropertyList(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity)
{
	#ifdef NLC_REFERENCING_OBJECTS_IN_PLURAL_LIST_BY_NUMBER
	if(this->checkNumericalReferenceToEntity(entity))
	{
		currentCodeBlockInTree = this->createCodeBlockInPropertyList(currentCodeBlockInTree, entity, entity->quantityNumber);
	}
	else
	{
	#endif
		currentCodeBlockInTree = this->createCodeBlockForPropertyList(currentCodeBlockInTree, entity);
	#ifdef NLC_REFERENCING_OBJECTS_IN_PLURAL_LIST_BY_NUMBER
	}
	#endif
	return currentCodeBlockInTree;
}

NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockForPropertyList(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const GIAentityNode* parent)	//this function should probably be used more often
{
	string context = NLCitemClass.generateInstanceName(parent);
	return this->createCodeBlockForPropertyList(currentCodeBlockInTree, entity, context);
}
NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockForPropertyList(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const string context)
{
	NLCitem* item = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
	item->context.push_back(context);
	return this->createCodeBlockForPropertyList(currentCodeBlockInTree, item);
}
NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockForPropertyList(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity)
{
	NLCitem* item = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
	return this->createCodeBlockForPropertyList(currentCodeBlockInTree, item);
}
NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockForPropertyList(NLCcodeblock* currentCodeBlockInTree, NLCitem* item)
{
	currentCodeBlockInTree->parameters.push_back(item);
	int codeBlockType = NLC_CODEBLOCK_TYPE_FOR_PROPERTY_LIST;
	currentCodeBlockInTree = this->createCodeBlock(currentCodeBlockInTree, codeBlockType);
	#ifdef NLC_NONOO
	currentCodeBlockInTree = this->createCodeBlockIfPropertyName(currentCodeBlockInTree, item);
	#endif
	return currentCodeBlockInTree;
}

#ifdef NLC_REFERENCING_OBJECTS_IN_PLURAL_LIST_BY_NUMBER
NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockInPropertyList(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const int index)
{
	NLCitem* item = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(item);

	string intValueString = SHAREDvars.convertIntToString(index);
	NLCitem* intValueItem = new NLCitem(intValueString, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(intValueItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_IN_PROPERTY_LIST;
	return this->createCodeBlock(currentCodeBlockInTree, codeBlockType);
}
NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockInPropertyList(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const string context, const int index)
{
	NLCitem* item = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(item);
	item->context.push_back(context);

	string intValueString = SHAREDvars.convertIntToString(index);
	NLCitem* intValueItem = new NLCitem(intValueString, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(intValueItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_IN_PROPERTY_LIST;
	return this->createCodeBlock(currentCodeBlockInTree, codeBlockType);
}
#endif


NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockForOrInLocalList(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity)
{
	#ifdef NLC_REFERENCING_OBJECTS_IN_PLURAL_LIST_BY_NUMBER
	if(this->checkNumericalReferenceToEntity(entity))
	{
		currentCodeBlockInTree = this->createCodeBlockInLocalList(currentCodeBlockInTree, entity, entity->quantityNumber);
	}
	else
	{
	#endif
		currentCodeBlockInTree = this->createCodeBlockForLocalList(currentCodeBlockInTree, entity);
	#ifdef NLC_REFERENCING_OBJECTS_IN_PLURAL_LIST_BY_NUMBER
	}
	#endif
	return currentCodeBlockInTree;
}

NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockForLocalList(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity)
{
	NLCitem* item = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(item);
	int codeBlockType = NLC_CODEBLOCK_TYPE_FOR_LOCAL_LIST;
	return this->createCodeBlock(currentCodeBlockInTree, codeBlockType);
}

#ifdef NLC_REFERENCING_OBJECTS_IN_PLURAL_LIST_BY_NUMBER
NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockInLocalList(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const int index)
{
	NLCitem* item = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(item);

	string intValueString = SHAREDvars.convertIntToString(index);
	NLCitem* intValueItem = new NLCitem(intValueString, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(intValueItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_IN_LOCAL_LIST;
	return this->createCodeBlock(currentCodeBlockInTree, codeBlockType);
}
#endif


NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockForConditionList(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* condition, const GIAentityNode* conditionRelationshipObjectEntity, const GIAentityNode* conditionRelationshipSubjectEntity)	//this function should probably be used more often
{
	string context = NLCitemClass.generateInstanceName(conditionRelationshipSubjectEntity);
	return this->createCodeBlockForConditionList(currentCodeBlockInTree, condition, conditionRelationshipObjectEntity, conditionRelationshipSubjectEntity);
}
NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockForConditionList(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* condition, const GIAentityNode* conditionRelationshipObjectEntity, const string context)
{
	NLCitem* conditionItem = new NLCitem(condition, NLC_ITEM_TYPE_OBJECT);
	NLCitem* conditionObjectItem = new NLCitem(conditionRelationshipObjectEntity, NLC_ITEM_TYPE_OBJECT);
	conditionItem->context.push_back(context);
	conditionObjectItem->context.push_back(context);	//redundant
	return this->createCodeBlockForConditionList(currentCodeBlockInTree, conditionItem, conditionObjectItem);
}
NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockForConditionList(NLCcodeblock* currentCodeBlockInTree, NLCitem* item, NLCitem* objectItem)
{
	currentCodeBlockInTree->parameters.push_back(item);
	currentCodeBlockInTree->parameters.push_back(objectItem);
	int codeBlockType = NLC_CODEBLOCK_TYPE_FOR_CONDITION_LIST;
	currentCodeBlockInTree = this->createCodeBlock(currentCodeBlockInTree, codeBlockType);
	#ifdef NLC_NONOO
	currentCodeBlockInTree = this->createCodeBlockIfConditionName(currentCodeBlockInTree, item, objectItem);
	#endif
	return currentCodeBlockInTree;
}


#ifdef NLC_NONOO
NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockIfPropertyName(NLCcodeblock* currentCodeBlockInTree, NLCitem* item)
{
	currentCodeBlockInTree->parameters.push_back(item);
	int codeBlockType = NLC_CODEBLOCK_TYPE_IF_PROPERTY_NAME;
	return this->createCodeBlock(currentCodeBlockInTree, codeBlockType);
}
NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockIfConditionName(NLCcodeblock* currentCodeBlockInTree, NLCitem* item, NLCitem* objectItem)
{
	currentCodeBlockInTree->parameters.push_back(item);
	currentCodeBlockInTree->parameters.push_back(objectItem);
	int codeBlockType = NLC_CODEBLOCK_TYPE_IF_CONDITION_NAME;
	return this->createCodeBlock(currentCodeBlockInTree, codeBlockType);
}
#ifdef NLC_RECORD_ACTION_HISTORY
NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockIfActionName(NLCcodeblock* currentCodeBlockInTree, NLCitem* item)
{
	currentCodeBlockInTree->parameters.push_back(item);
	int codeBlockType = NLC_CODEBLOCK_TYPE_IF_ACTION_NAME;
	return this->createCodeBlock(currentCodeBlockInTree, codeBlockType);
}
#endif
#endif

#ifdef NLC_RECORD_ACTION_HISTORY

NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockForActionList(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* actionRelationshipEntity, const GIAentityNode* actionRelationshipSubjectEntity)
{
	return this->createCodeBlockForActionList(currentCodeBlockInTree, actionRelationshipEntity, NLCitemClass.generateInstanceName(actionRelationshipSubjectEntity));
}
NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockForActionList(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const string context)
{
	NLCitem* item = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
	item->context.push_back(context);

	currentCodeBlockInTree->parameters.push_back(item);
	int codeBlockType = NLC_CODEBLOCK_TYPE_FOR_ACTION_LIST;
	currentCodeBlockInTree = this->createCodeBlock(currentCodeBlockInTree, codeBlockType);
	#ifdef NLC_NONOO
	currentCodeBlockInTree = this->createCodeBlockIfActionName(currentCodeBlockInTree, item);
	#endif
	return currentCodeBlockInTree;
}
NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockForActionIncomingList(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* actionRelationshipEntity, const GIAentityNode* actionRelationshipObjectEntity)
{
	return this->createCodeBlockForActionIncomingList(currentCodeBlockInTree, actionRelationshipEntity, NLCitemClass.generateInstanceName(actionRelationshipObjectEntity));
}
NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockForActionIncomingList(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const string context)
{
	NLCitem* item = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
	item->context.push_back(context);

	currentCodeBlockInTree->parameters.push_back(item);
	int codeBlockType = NLC_CODEBLOCK_TYPE_FOR_ACTION_INCOMING_LIST;
	currentCodeBlockInTree = this->createCodeBlock(currentCodeBlockInTree, codeBlockType);
	#ifdef NLC_NONOO
	currentCodeBlockInTree = this->createCodeBlockIfActionName(currentCodeBlockInTree, item);
	#endif
	return currentCodeBlockInTree;
}
NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockForActionObjectList(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* actionRelationshipObjectEntity, const GIAentityNode* actionRelationshipEntity)
{
	return this->createCodeBlockForActionObjectList(currentCodeBlockInTree, actionRelationshipObjectEntity, NLCitemClass.generateInstanceName(actionRelationshipEntity));
}
NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockForActionObjectList(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const string context)
{
	NLCitem* item = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
	item->context.push_back(context);

	currentCodeBlockInTree->parameters.push_back(item);
	int codeBlockType = NLC_CODEBLOCK_TYPE_FOR_ACTION_OBJECT_LIST;
	return this->createCodeBlock(currentCodeBlockInTree, codeBlockType);
}
NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockForActionSubjectList(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* actionRelationshipSubjectEntity, const GIAentityNode* actionRelationshipEntity)
{
	return this->createCodeBlockForActionSubjectList(currentCodeBlockInTree, actionRelationshipSubjectEntity, NLCitemClass.generateInstanceName(actionRelationshipEntity));
}
NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockForActionSubjectList(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const string context)
{
	NLCitem* item = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
	item->context.push_back(context);

	currentCodeBlockInTree->parameters.push_back(item);
	int codeBlockType = NLC_CODEBLOCK_TYPE_FOR_ACTION_SUBJECT_LIST;
	return this->createCodeBlock(currentCodeBlockInTree, codeBlockType);
}
#endif

#ifdef NLC_QUANTITIES
NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockForInteger(NLCcodeblock* currentCodeBlockInTree, const string numberIterationsOrVariable)
{
	NLCitem* integerItem = new NLCitem(numberIterationsOrVariable, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(integerItem);
	int codeBlockType = NLC_CODEBLOCK_TYPE_FOR_INTEGER;
	return this->createCodeBlock(currentCodeBlockInTree, codeBlockType);
}
#endif






NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockDeclareAndInitialiseVariableForActionSubject(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* functionOwner)
{
	//"Dog dog1 = this;"
	NLCitem* functionOwnerItem = new NLCitem(functionOwner, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(functionOwnerItem);
	NLCitem* actionSubjectInstanceReplacementItem = new NLCitem(NLC_INPUT_FUNCTION_LISTS_ACTION_SUBJECT_INSTANCE_REPLACEMENT_NAME, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(actionSubjectInstanceReplacementItem);
	currentCodeBlockInTree = this->createCodeBlock(currentCodeBlockInTree, NLC_CODEBLOCK_TYPE_DECLARE_AND_INITIALISE_VARIABLE);

	return currentCodeBlockInTree;
}

NLCcodeblock* NLCcodeBlockClassClass::createCodeBlocksAddVariableToNewList(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity)
{
	currentCodeBlockInTree = this->createCodeBlocksDeclareNewLocalListVariableIfNecessary(currentCodeBlockInTree, entity);
	currentCodeBlockInTree = this->createCodeBlockAddEntityToLocalList(currentCodeBlockInTree, entity, entity);

	return currentCodeBlockInTree;
}



bool NLCcodeBlockClassClass::assumedToAlreadyHaveBeenDeclared(const GIAentityNode* entity)
{
	bool isAssumedToAlreadyHaveBeenDeclared = false;
	if(this->assumedToAlreadyHaveBeenDeclaredInitialisation(entity) || entity->NLClocalListVariableHasBeenInitialised)
	{
		isAssumedToAlreadyHaveBeenDeclared = true;
	}
	return isAssumedToAlreadyHaveBeenDeclared;
}

bool NLCcodeBlockClassClass::isDefiniteEntity(const GIAentityNode* entity)
{
	bool isDefiniteEntity = false;
	#ifdef NLC_TRANSLATOR_INTERPRET_PROPERNOUNS_WITH_DEFINITION_LINK_AS_NEWLY_DECLARED
	if((entity->grammaticalDefiniteTemp) || ((entity->grammaticalProperNounTemp) && !(entity->NLCfirstInstanceOfProperNounInContext)))	
	#else
	if((entity->grammaticalDefiniteTemp) || (entity->grammaticalProperNounTemp))
	#endif
	{
		isDefiniteEntity = true;
	}
	return isDefiniteEntity;
}

bool NLCcodeBlockClassClass::isDefiniteEntityStrict(const GIAentityNode* entity)
{
	bool isDefiniteEntity = false;
	if((entity->grammaticalDefiniteTemp) || (entity->grammaticalProperNounTemp))
	{
		isDefiniteEntity = true;
	}
	return isDefiniteEntity;
}

bool NLCcodeBlockClassClass::assumedToAlreadyHaveBeenDeclaredInitialisation(const GIAentityNode* entity)
{
	bool isAssumedToAlreadyHaveBeenDeclared = false;
	if(this->isDefiniteEntity(entity) || entity->NLCisSingularArgument)
	{
		isAssumedToAlreadyHaveBeenDeclared = true;
	}
	return isAssumedToAlreadyHaveBeenDeclared;
}






NLCcodeblock* NLCcodeBlockClassClass::createCodeBlock(NLCcodeblock* currentCodeBlockInTree, int codeBlockType)
{
	currentCodeBlockInTree->codeBlockType = codeBlockType;
	currentCodeBlockInTree->next = new NLCcodeblock();

	if(codeBlockType >= NLC_CODEBLOCK_TYPE_CONTAINERS)
	{
		currentCodeBlockInTree = this->createLowerLevel(currentCodeBlockInTree);
	}
	else
	{
		currentCodeBlockInTree = currentCodeBlockInTree->next;
	}
	return currentCodeBlockInTree;
}

NLCcodeblock* NLCcodeBlockClassClass::createLowerLevel(NLCcodeblock* currentCodeBlockInTree)
{
	currentCodeBlockInTree->lowerLevel = new NLCcodeblock();
	currentCodeBlockInTree = currentCodeBlockInTree->lowerLevel;
	return currentCodeBlockInTree;
}



bool NLCcodeBlockClassClass::getEntityContext(GIAentityNode* entity, vector<string>* context, const bool includePresentObject, const int sentenceIndex, const bool markSameSentenceParentsAsParsed)
{
	if(includePresentObject)
	{
		string itemName = NLCitemClass.generateInstanceName(entity);
		context->push_back(itemName);
	}
	bool entityHasParent = false;
	bool stillSearching = true;
	GIAentityNode* currentEntity = entity;

	while(stillSearching)
	{
		if(!(currentEntity->propertyReverseNodeList->empty()))
		{
			entityHasParent = true;
			GIAentityNode* parentEntity = currentEntity;
			currentEntity = GIAtranslatorOperations.getPropertyRelationshipSubjectEntity(currentEntity->propertyReverseNodeList->back());
			string itemName = NLCitemClass.generateInstanceName(currentEntity);
			if(markSameSentenceParentsAsParsed)
			{
				if(currentEntity->sentenceIndexTemp == sentenceIndex)
				{
					GIAentityConnection* propertyConnection = NULL;
					if(GIAtranslatorOperations.findEntityNodePointerInVector(currentEntity, parentEntity, GIA_ENTITY_VECTOR_CONNECTION_TYPE_PROPERTY, &propertyConnection))
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



bool NLCcodeBlockClassClass::checkSentenceIndexParsingCodeBlocks(const GIAentityNode* entity, const GIAentityConnection* connection, const int sentenceIndex, const bool checkIfEntityHasBeenParsedForNLCcodeBlocks)
{
	bool result = false;
	#ifdef NLC_VERIFY_CONNECTIONS_SENTENCE_INDEX
	if(connection->sentenceIndexTemp == sentenceIndex)
	{
	#endif
		if(this->checkSentenceIndexParsingCodeBlocks(entity, sentenceIndex, checkIfEntityHasBeenParsedForNLCcodeBlocks))
		{
			result = true;
		}
	#ifdef NLC_VERIFY_CONNECTIONS_SENTENCE_INDEX
	}
	#endif
	return result;
}

bool NLCcodeBlockClassClass::checkSentenceIndexParsingCodeBlocks(const GIAentityNode* entity, const int sentenceIndex, const bool checkIfEntityHasBeenParsedForNLCcodeBlocks)
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


bool NLCcodeBlockClassClass::checkDuplicateProperty(const GIAentityNode* propertyRelationshipObjectEntity, GIAentityNode* childActionEntity)
{
	bool alreadyAdded = false;
	for(vector<GIAentityConnection*>::iterator propertyNodeListIterator = childActionEntity->propertyNodeList->begin(); propertyNodeListIterator < childActionEntity->propertyNodeList->end(); propertyNodeListIterator++)
	{
		GIAentityNode* propertyEntityLocal = GIAtranslatorOperations.getPropertyRelationshipObjectEntity(*propertyNodeListIterator);
		if((propertyRelationshipObjectEntity->entityName == propertyEntityLocal->entityName))
		{
			alreadyAdded = true;
		}
	}
	return alreadyAdded;
}

bool NLCcodeBlockClassClass::checkDuplicateCondition(GIAentityNode* conditionRelationshipEntity, GIAentityNode* childActionEntity)
{
	bool alreadyAdded = false;
	for(vector<GIAentityConnection*>::iterator conditionNodeListIterator = childActionEntity->conditionNodeList->begin(); conditionNodeListIterator < childActionEntity->conditionNodeList->end(); conditionNodeListIterator++)
	{
		GIAentityNode* conditionEntityLocal = (*conditionNodeListIterator)->entity;
		string conditionObjectEntityLocalName = "";
		if(!(conditionEntityLocal->relationshipObjectEntity->empty()))
		{
			conditionObjectEntityLocalName = (conditionEntityLocal->relationshipObjectEntity->back())->entity->entityName;
		}
		string conditionObjectEntityName = "";
		if(!(conditionRelationshipEntity->relationshipObjectEntity->empty()))
		{
			conditionObjectEntityName = (conditionRelationshipEntity->relationshipObjectEntity->back())->entity->entityName;
		}
		if((conditionRelationshipEntity->entityName == conditionEntityLocal->entityName) && (conditionObjectEntityName == conditionObjectEntityLocalName))
		{
			alreadyAdded = true;
		}
	}
	return alreadyAdded;
}



NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockElse(NLCcodeblock* currentCodeBlockInTree)
{
	NLCitem* tempItem = new NLCitem("notUsedButNLCprintCodeBlocksRequiresAtLeastOneItem", NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(tempItem);
	int codeBlockType = NLC_CODEBLOCK_TYPE_ELSE;
	return this->createCodeBlock(currentCodeBlockInTree, codeBlockType);
}

NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockWhileHasBool(NLCcodeblock* currentCodeBlockInTree, const string whileLogicalConditionConjunctionBooleanName)
{
	NLCitem* conditionItem = new NLCitem(whileLogicalConditionConjunctionBooleanName, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(conditionItem);
	int codeBlockType = NLC_CODEBLOCK_TYPE_WHILE;
	return this->createCodeBlock(currentCodeBlockInTree, codeBlockType);
}

//logicalConditionLevel is defined based on user tab indenting of text file, as parsed by NLC preprocessor
string NLCcodeBlockClassClass::generateWhileLogicalConditionConjunctionBooleanName(const int logicalConditionLevel)
{
	string whileLogicalConditionConjunctionBooleanName = string(NLC_WHILE_LOGICAL_CONDITION_CONJUNCTION_BOOLEAN_VARIABLE_NAME) + SHAREDvars.convertIntToString(logicalConditionLevel);
	return whileLogicalConditionConjunctionBooleanName;
}

NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockDeclareNewBoolVar(NLCcodeblock* currentCodeBlockInTree, const string boolVariableName, const bool value)
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
	return this->createCodeBlock(currentCodeBlockInTree, codeBlockType);
}

NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockSetBoolVar(NLCcodeblock* currentCodeBlockInTree, const string boolVariableName, const bool value)
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
	return this->createCodeBlock(currentCodeBlockInTree, codeBlockType);
}

NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockCheckBoolVar(NLCcodeblock* currentCodeBlockInTree, const string boolVariableName, const bool value)
{
	NLCitem* itemCheckBoolVariable = new NLCitem(boolVariableName, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(itemCheckBoolVariable);
	int codeBlockType;
	if(value)
	{
		codeBlockType = NLC_CODEBLOCK_TYPE_CHECK_BOOL_VARIABLE_TRUE;
	}
	else
	{
		codeBlockType = NLC_CODEBLOCK_TYPE_CHECK_BOOL_VARIABLE_FALSE;
	}
	return this->createCodeBlock(currentCodeBlockInTree, codeBlockType);
}



#ifdef NLC_TRANSLATE_NEGATIVE_PROPERTIES_AND_CONDITIONS
NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockRemoveProperty(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const GIAentityNode* propertyRelationshipObjectEntity)
{
	NLCitem* entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	NLCitem* propertyItem = new NLCitem(propertyRelationshipObjectEntity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(propertyItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_REMOVE_PROPERTY;
	currentCodeBlockInTree = this->createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}
NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockRemoveProperties(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const GIAentityNode* propertyRelationshipObjectEntity)
{
	NLCitem* entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	NLCitem* propertyItem = new NLCitem(propertyRelationshipObjectEntity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(propertyItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_REMOVE_PROPERTIES;
	currentCodeBlockInTree = this->createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}

//not currently used;
NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockRemoveEntitiesFromLocalList(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity)
{
	NLCitem* entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_REMOVE_ENTITIES_FROM_LOCAL_LIST;
	currentCodeBlockInTree = this->createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}

NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockRemoveCondition(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* conditionRelationshipEntity)
{
	if(!(conditionRelationshipEntity->relationshipObjectEntity->empty()))
	{
		GIAentityNode* conditionRelationshipObjectEntity = (conditionRelationshipEntity->relationshipObjectEntity->back())->entity;

		currentCodeBlockInTree = this->createCodeBlockRemoveConditionSimple(currentCodeBlockInTree, entity, conditionRelationshipEntity, conditionRelationshipObjectEntity);
		#ifdef NLC_NORMALISE_TWOWAY_PREPOSITIONS
		if(conditionRelationshipEntity->conditionTwoWay)
		{
			GIAentityNode* entityInverse = conditionRelationshipObjectEntity;
			GIAentityNode* conditionEntityInverse = NULL;
			conditionEntityInverse = this->generateInverseConditionEntity(conditionRelationshipEntity);
			currentCodeBlockInTree = this->createCodeBlockRemoveConditionSimple(currentCodeBlockInTree, conditionRelationshipObjectEntity, conditionEntityInverse, entity);
		}
		#endif
	}
	else
	{
		cout << "error: condition does not have object" << endl;
	}

	return currentCodeBlockInTree;
}

NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockRemoveConditionSimple(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const GIAentityNode* conditionRelationshipEntity, const GIAentityNode* conditionRelationshipObjectEntity)
{
	NLCitem* entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
	//removed 1e7c as it is not used: getEntityContext(entity, &(entityItem->context), false, sentenceIndex, false);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	NLCitem* conditionItem = new NLCitem(conditionRelationshipEntity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(conditionItem);

	NLCitem* conditionObjectItem = new NLCitem(conditionRelationshipObjectEntity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(conditionObjectItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_REMOVE_CONDITION;
	currentCodeBlockInTree = this->createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}

NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockRemoveConditions(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* conditionRelationshipEntity)
{
	if(!(conditionRelationshipEntity->relationshipObjectEntity->empty()))
	{
		GIAentityNode* conditionRelationshipObjectEntity = (conditionRelationshipEntity->relationshipObjectEntity->back())->entity;

		currentCodeBlockInTree = this->createCodeBlockRemoveConditionsSimple(currentCodeBlockInTree, entity, conditionRelationshipEntity, conditionRelationshipObjectEntity);
		#ifdef NLC_NORMALISE_TWOWAY_PREPOSITIONS
		if(conditionRelationshipEntity->conditionTwoWay)
		{
			GIAentityNode* entityInverse = conditionRelationshipObjectEntity;
			GIAentityNode* conditionEntityInverse = NULL;
			conditionEntityInverse = this->generateInverseConditionEntity(conditionRelationshipEntity);
			currentCodeBlockInTree = this->createCodeBlockRemoveConditionsSimple(currentCodeBlockInTree, conditionRelationshipObjectEntity, conditionEntityInverse, entity);
		}
		#endif
	}
	else
	{
		cout << "error: condition does not have object" << endl;
	}

	return currentCodeBlockInTree;
}

NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockRemoveConditionsSimple(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const GIAentityNode* conditionRelationshipEntity, const GIAentityNode* conditionRelationshipObjectEntity)
{
	NLCitem* entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
	//removed 1e7c as it is not used: getEntityContext(entity, &(entityItem->context), false, sentenceIndex, false);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	NLCitem* conditionItem = new NLCitem(conditionRelationshipEntity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(conditionItem);

	NLCitem* conditionObjectItem = new NLCitem(conditionRelationshipObjectEntity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(conditionObjectItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_REMOVE_CONDITIONS;
	currentCodeBlockInTree = this->createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}

#endif

#ifdef NLC_PREPROCESSOR_MATH
NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockMathTextLine(NLCcodeblock* currentCodeBlockInTree, const string mathText)
{
	NLCitem* mathTextItem = new NLCitem(mathText, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(mathTextItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_MATHTEXT_LINE;
	currentCodeBlockInTree = this->createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}

NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockMathTextWithLogicalOperator(NLCcodeblock* currentCodeBlockInTree, const string mathText)
{
	if(!(currentCodeBlockInTree->parameters.empty()))
	{
		cout << "error: !(currentCodeBlockInTree->parameters.empty())" << endl;
	}
	NLCitem* mathTextItem = new NLCitem(mathText, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(mathTextItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_MATHTEXT_WITH_LOGICAL_OPERATOR;
	currentCodeBlockInTree = this->createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}
#endif

NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockDeclareNewIntVar(NLCcodeblock* currentCodeBlockInTree, const string intVariableName, const int value)
{
	NLCitem* intNameItem = new NLCitem(intVariableName, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(intNameItem);

	string intValueString = SHAREDvars.convertIntToString(value);
	NLCitem* intValueItem = new NLCitem(intValueString, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(intValueItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_DECLARE_NEW_INT_VARIABLE;

	return this->createCodeBlock(currentCodeBlockInTree, codeBlockType);
}

NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockIncrementIntVar(NLCcodeblock* currentCodeBlockInTree, const string intVariableName)
{
	NLCitem* intNameItem = new NLCitem(intVariableName, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(intNameItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_INCREMENT_INT_VARIABLE;

	return this->createCodeBlock(currentCodeBlockInTree, codeBlockType);
}

NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockCommentSingleLine(NLCcodeblock* currentCodeBlockInTree, const string comment)
{
	NLCitem* item = new NLCitem(comment, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(item);

	int codeBlockType = NLC_CODEBLOCK_TYPE_COMMENT_SINGLE_LINE;
	currentCodeBlockInTree = this->createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}



#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN

NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockReassignIter(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity)
{
	NLCitem* entityClass = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);

	currentCodeBlockInTree->parameters.push_back(entityClass);

	int codeBlockType = NLC_CODEBLOCK_TYPE_REASSIGN_ITER;

	return this->createCodeBlock(currentCodeBlockInTree, codeBlockType);
}

NLCcodeblock* NLCcodeBlockClassClass::createCodeBlocksDeclareNewCategoryListVariable(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const string genericListAppendName, const int sentenceIndex)
{
	return this->createCodeBlocksDeclareNewGenericListVariable(currentCodeBlockInTree, entity, NLCitemClass.generateCategoryListGenericObjectName(entity, sentenceIndex), genericListAppendName);
}

NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockAddEntityToCategoryList(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const GIAentityNode* propertyRelationshipObjectEntity, const string genericListAppendName, const int sentenceIndex)
{
	return this->createCodeBlockAddEntityToGenericList(currentCodeBlockInTree, entity, NLCitemClass.generateCategoryListGenericObjectName(entity, sentenceIndex), genericListAppendName, propertyRelationshipObjectEntity);
}

NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockForCategoryList(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const string genericListAppendName, const int sentenceIndex)
{
	return this->createCodeBlockForGenericList(currentCodeBlockInTree, entity, NLCitemClass.generateCategoryListGenericObjectName(entity, sentenceIndex), genericListAppendName);
}

#ifdef NLC_CATEGORIES_TEST_PLURALITY
NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockGetBackCategoryEntityList(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const string genericListAppendName, const int sentenceIndex)
{
	return this->createCodeBlockGetBackGenericEntityList(currentCodeBlockInTree, entity, NLCitemClass.generateCategoryListGenericObjectName(entity, sentenceIndex), genericListAppendName);
}
NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockIfHasGreaterThanNumCategoryItem(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const string genericListAppendName, const int value, const int sentenceIndex)
{
	return this->createCodeBlockIfHasGreaterThanNumGenericEntity(currentCodeBlockInTree, entity, NLCitemClass.generateCategoryListGenericObjectName(entity, sentenceIndex), genericListAppendName, value);
}
#endif
#ifdef NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY
NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockIfHasGreaterThanOrEqualToNumCategoryItem(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const string genericListAppendName, const int value, const int sentenceIndex)
{
	return this->createCodeBlockIfHasGreaterThanOrEqualToNumGenericEntity(currentCodeBlockInTree, entity, NLCitemClass.generateCategoryListGenericObjectName(entity, sentenceIndex), genericListAppendName, value);
}
#endif
NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockIfHasCategoryItem(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const bool negative, const string genericListAppendName, const int sentenceIndex)
{
	return this->createCodeBlockIfHasGenericEntity(currentCodeBlockInTree, entity, NLCitemClass.generateCategoryListGenericObjectName(entity, sentenceIndex), genericListAppendName, negative);
}
#ifdef NLC_ADVANCED_REFERENCING
NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockAddEntityToCategoryListCheckLastSentenceReferencedSingularExecuteFunction(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const GIAentityNode* propertyRelationshipObjectEntity, const string genericListAppendName, const int sentenceIndex, const bool castToCategoryType)
{
	return this->createCodeBlockAddEntityToGenericListCheckLastSentenceReferencedSingularExecuteFunction(currentCodeBlockInTree, entity, NLCitemClass.generateCategoryListGenericObjectName(entity, sentenceIndex), genericListAppendName, propertyRelationshipObjectEntity, castToCategoryType);
}
NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockAddEntityToCategoryListCheckLastSentenceReferencedSingularNewFunction(NLCcodeblock* currentCodeBlockInTree)
{
	return this->createCodeBlockAddEntityToGenericListCheckLastSentenceReferencedSingularNewFunction(currentCodeBlockInTree);
}
#endif
#ifdef NLC_PERFORM_PLURAL_DEFINITE_REFERENCING_TESTS
NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockAddEntityToCategoryListCheckLastSentenceReferencedPluralExecuteFunction(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const GIAentityNode* propertyRelationshipObjectEntity, const string genericListAppendName, const int sentenceIndex, const bool castToCategoryType)
{
	return this->createCodeBlockAddEntityToGenericListCheckLastSentenceReferencedPluralExecuteFunction(currentCodeBlockInTree, entity, NLCitemClass.generateCategoryListGenericObjectName(entity, sentenceIndex), genericListAppendName, propertyRelationshipObjectEntity, castToCategoryType);
}
NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockAddEntityToCategoryListCheckLastSentenceReferencedPluralNewFunction(NLCcodeblock* currentCodeBlockInTree)
{
	return this->createCodeBlockAddEntityToGenericListCheckLastSentenceReferencedPluralNewFunction(currentCodeBlockInTree);
}
#endif


NLCcodeblock* NLCcodeBlockClassClass::createCodeBlocksDeclareNewGenericListVariable(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const string genericObjectName, const string genericListAppendName)
{
	NLCitem* entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT, genericObjectName);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	NLCitem* genericListAppendItem = new NLCitem(genericListAppendName, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(genericListAppendItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_DECLARE_NEW_GENERIC_LIST_VARIABLE;
	currentCodeBlockInTree = this->createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}

NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockAddEntityToGenericList(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const string genericObjectName, const string genericListAppendName, const GIAentityNode* propertyRelationshipObjectEntity)
{
	NLCitem* entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT, genericObjectName);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	NLCitem* propertyItem = new NLCitem(propertyRelationshipObjectEntity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(propertyItem);

	NLCitem* genericListAppendItem = new NLCitem(genericListAppendName, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(genericListAppendItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST;
	currentCodeBlockInTree = this->createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}

NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockForGenericList(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const string genericObjectName, const string genericListAppendName)
{
	NLCitem* entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT, genericObjectName);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	NLCitem* genericListAppendItem = new NLCitem(genericListAppendName, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(genericListAppendItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_FOR_GENERIC_LIST;
	return this->createCodeBlock(currentCodeBlockInTree, codeBlockType);
}

#ifdef NLC_CATEGORIES_TEST_PLURALITY
NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockGetBackGenericEntityList(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const string genericObjectName, const string genericListAppendName)
{
	NLCitem* entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT, genericObjectName);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	NLCitem* genericListAppendItem = new NLCitem(genericListAppendName, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(genericListAppendItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_GET_BACK_GENERIC_ENTITY_LIST;
	return this->createCodeBlock(currentCodeBlockInTree, codeBlockType);
}
NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockIfHasGreaterThanNumGenericEntity(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const string genericObjectName, const string genericListAppendName, const int value)
{
	NLCitem* entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT, genericObjectName);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	NLCitem* genericListAppendItem = new NLCitem(genericListAppendName, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(genericListAppendItem);

	string intValueString = SHAREDvars.convertIntToString(value);
	NLCitem* intValueItem = new NLCitem(intValueString, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(intValueItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_IF_HAS_GREATER_THAN_NUM_GENERIC_ENTITY;
	return this->createCodeBlock(currentCodeBlockInTree, codeBlockType);
}

NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockPrintWarning(NLCcodeblock* currentCodeBlockInTree, const string warning)
{
	NLCitem* printWarningItem = new NLCitem(warning, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(printWarningItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_PRINT_WARNING;
	currentCodeBlockInTree = this->createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}
#endif
#ifdef NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY
NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockIfHasGreaterThanOrEqualToNumGenericEntity(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const string genericObjectName, const string genericListAppendName, const int value)
{
	NLCitem* entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT, genericObjectName);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	NLCitem* genericListAppendItem = new NLCitem(genericListAppendName, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(genericListAppendItem);

	string intValueString = SHAREDvars.convertIntToString(value);
	NLCitem* intValueItem = new NLCitem(intValueString, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(intValueItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_IF_HAS_GREATER_THAN_OR_EQUAL_TO_NUM_GENERIC_ENTITY;
	return this->createCodeBlock(currentCodeBlockInTree, codeBlockType);
}
#endif

NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockIfHasGenericEntity(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const string genericObjectName, const string genericListAppendName, const bool negative)
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
	return this->createCodeBlock(currentCodeBlockInTree, codeBlockType);
}
#ifdef NLC_ADVANCED_REFERENCING
NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockAddEntityToGenericListCheckLastSentenceReferencedSingularExecuteFunction(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const string genericObjectName, const string genericListAppendName, const GIAentityNode* propertyRelationshipObjectEntity, const bool castToCategoryType)
{
	NLCitem* entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT, genericObjectName);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	NLCitem* propertyItem = new NLCitem(propertyRelationshipObjectEntity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(propertyItem);

	NLCitem* genericListAppendItem = new NLCitem(genericListAppendName, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(genericListAppendItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST_CHECK_LAST_SENTENCE_REFERENCED_SINGULAR_EXECUTE_FUNCTION;
	if(castToCategoryType)
	{
		codeBlockType = NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST_CHECK_LAST_SENTENCE_REFERENCED_SINGULAR_WITH_CAST_EXECUTE_FUNCTION;
	}
	else
	{
		codeBlockType = NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST_CHECK_LAST_SENTENCE_REFERENCED_SINGULAR_EXECUTE_FUNCTION;
	}
	currentCodeBlockInTree = this->createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}
NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockAddEntityToGenericListCheckLastSentenceReferencedSingularNewFunction(NLCcodeblock* currentCodeBlockInTree)
{
	//required because printCodeBlocks requires at least 1 param
	NLCitem* entityItem = new NLCitem("dummyentity", NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST_CHECK_LAST_SENTENCE_REFERENCED_SINGULAR_NEW_FUNCTION;
	currentCodeBlockInTree = this->createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}

NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockUpdateLastSentenceReferenced(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const int sentenceIndex)
{
	NLCitem* entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	string sentenceIndexString = SHAREDvars.convertIntToString(sentenceIndex);
	NLCitem* sentenceIndexItem = new NLCitem(sentenceIndexString, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(sentenceIndexItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_UPDATE_LAST_SENTENCE_REFERENCED;
	return this->createCodeBlock(currentCodeBlockInTree, codeBlockType);
}
#endif
#endif

#ifdef NLC_PERFORM_PLURAL_DEFINITE_REFERENCING_TESTS
NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockAddEntityToGenericListCheckLastSentenceReferencedPluralExecuteFunction(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const string genericObjectName, const string genericListAppendName, const GIAentityNode* propertyRelationshipObjectEntity, const bool castToCategoryType)
{
	NLCitem* entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT, genericObjectName);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	NLCitem* propertyItem = new NLCitem(propertyRelationshipObjectEntity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(propertyItem);

	NLCitem* genericListAppendItem = new NLCitem(genericListAppendName, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(genericListAppendItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST_CHECK_LAST_SENTENCE_REFERENCED_PLURAL_EXECUTE_FUNCTION;
	if(castToCategoryType)
	{
		codeBlockType = NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST_CHECK_LAST_SENTENCE_REFERENCED_PLURAL_WITH_CAST_EXECUTE_FUNCTION;
	}
	else
	{
		codeBlockType = NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST_CHECK_LAST_SENTENCE_REFERENCED_PLURAL_EXECUTE_FUNCTION;
	}
	currentCodeBlockInTree = this->createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}
NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockAddEntityToGenericListCheckLastSentenceReferencedPluralNewFunction(NLCcodeblock* currentCodeBlockInTree)
{
	//required because printCodeBlocks requires at least 1 param
	NLCitem* entityItem = new NLCitem("dummyentity", NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST_CHECK_LAST_SENTENCE_REFERENCED_PLURAL_NEW_FUNCTION;
	currentCodeBlockInTree = this->createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}
#endif


#ifdef NLC_GENERATE_TYPE_LISTS
NLCcodeblock* NLCcodeBlockClassClass::createCodeBlocksDeclareNewGenericListVariable2(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const string genericObjectName, const string genericListAppendName)
{
	NLCitem* entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT, genericObjectName);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	NLCitem* genericListAppendItem = new NLCitem(genericListAppendName, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(genericListAppendItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_DECLARE_NEW_GENERIC_LIST_VARIABLE2;
	currentCodeBlockInTree = this->createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}

NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockAddEntityToGenericList2(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const string genericObjectName, const string genericListAppendName, const GIAentityNode* propertyRelationshipObjectEntity, const string genericListAppendName2)
{
	NLCitem* entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT, genericObjectName);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	NLCitem* propertyItem = new NLCitem(propertyRelationshipObjectEntity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(propertyItem);

	NLCitem* genericListAppendItem = new NLCitem(genericListAppendName, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(genericListAppendItem);

	NLCitem* genericListAppendItem2 = new NLCitem(genericListAppendName2, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(genericListAppendItem2);

	int codeBlockType = NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST2;
	currentCodeBlockInTree = this->createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}

NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockForGenericList2(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const string genericObjectName, const string genericListAppendName)
{
	NLCitem* entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT, genericObjectName);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	NLCitem* genericListAppendItem = new NLCitem(genericListAppendName, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(genericListAppendItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_FOR_GENERIC_LIST2;
	return this->createCodeBlock(currentCodeBlockInTree, codeBlockType);
}

NLCcodeblock* NLCcodeBlockClassClass::createCodeBlocksDeclareNewTypeListVariable(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity)
{
	return this->createCodeBlocksDeclareNewGenericListVariable2(currentCodeBlockInTree, entity, entity->entityName, NLC_ITEM_TYPE_TYPE_VAR_APPENDITION2);
}
NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockAddInstanceListToTypeList(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const GIAentityNode* propertyRelationshipObjectEntity)
{
	return this->createCodeBlockAddEntityToGenericList2(currentCodeBlockInTree, entity, entity->entityName, NLC_ITEM_TYPE_TYPE_VAR_APPENDITION2, propertyRelationshipObjectEntity, NLC_ITEM_TYPE_INSTANCE_VAR_APPENDITION2);
}
NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockForPropertyTypeClass(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity)
{
	return this->createCodeBlockForGenericList2(currentCodeBlockInTree, entity, entity->entityName, NLC_ITEM_TYPE_TYPE_VAR_APPENDITION2);
}
#endif

#ifdef NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY
NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockIfIntVariableGreaterThanOrEqualToNum(NLCcodeblock* currentCodeBlockInTree, const string intVariableName, const int value)
{
	NLCitem* intNameItem = new NLCitem(intVariableName, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(intNameItem);
	
	string intValueString = SHAREDvars.convertIntToString(value);
	NLCitem* intValueItem = new NLCitem(intValueString, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(intValueItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_TEST_INT_VARIABLE_GREATER_THAN_OR_EQUAL_TO_NUM;
	return this->createCodeBlock(currentCodeBlockInTree, codeBlockType);
}
NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockIfIntVariableEqualsListSize(NLCcodeblock* currentCodeBlockInTree, const string intVariableName, const GIAentityNode* entityList, const string genericListAppendName, const int sentenceIndex)
{
	NLCitem* intNameItem = new NLCitem(intVariableName, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(intNameItem);
	
	string genericObjectName = NLCitemClass.generateCategoryListGenericObjectName(entityList, sentenceIndex);
	NLCitem* entityItem = new NLCitem(entityList, NLC_ITEM_TYPE_OBJECT, genericObjectName);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	NLCitem* genericListAppendItem = new NLCitem(genericListAppendName, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(genericListAppendItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_TEST_INT_VARIABLE_EQUALS_LIST_SIZE;
	return this->createCodeBlock(currentCodeBlockInTree, codeBlockType);
}
/*
NLCcodeblock* createCodeBlockIfHasMoreThanNumProperty(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* propertyRelationshipObjectEntity, int value, string parentInstanceName)
{
	NLCitem* propertyItem = new NLCitem(propertyRelationshipObjectEntity, NLC_ITEM_TYPE_OBJECT);
	propertyItem->context.push_back(parentInstanceName);
	currentCodeBlockInTree->parameters.push_back(propertyItem);

	string intValueString = convertIntToString(value);
	NLCitem* intValueItem = new NLCitem(intValueString, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(intValueItem);
	#ifdef NLC_DEBUG
	//cout << "intValueString = " << intValueString << endl;
	#endif

	int codeBlockType = NLC_CODEBLOCK_TYPE_IF_HAS_MORE_THAN_NUM_PROPERTY;
	return createCodeBlock(currentCodeBlockInTree, codeBlockType);
}
NLCcodeblock* createCodeBlockIfHasMoreThanNumCondition(NLCcodeblock* currentCodeBlockInTree, GIAentityNode* conditionRelationshipEntity, GIAentityNode* conditionRelationshipObjectEntity, int value, string parentInstanceName)
{
	NLCitem* conditionItem = new NLCitem(conditionRelationshipEntity, NLC_ITEM_TYPE_OBJECT);
	NLCitem* conditionObjectItem = new NLCitem(conditionRelationshipObjectEntity, NLC_ITEM_TYPE_OBJECT);
	#ifdef NLC_DEBUG
	//cout << "createCodeBlockForGivenCondition: " << conditionObjectItem->instanceName << endl;
	#endif

	conditionItem->context.push_back(parentInstanceName);
	conditionObjectItem->context.push_back(parentInstanceName);	//redundant

	currentCodeBlockInTree->parameters.push_back(conditionItem);
	currentCodeBlockInTree->parameters.push_back(conditionObjectItem);

	string intValueString = convertIntToString(value);
	NLCitem* intValueItem = new NLCitem(intValueString, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(intValueItem);
	#ifdef NLC_DEBUG
	//cout << "intValueString = " << intValueString << endl;
	#endif

	int codeBlockType = NLC_CODEBLOCK_TYPE_IF_HAS_MORE_THAN_NUM_CONDITION;
	return createCodeBlock(currentCodeBlockInTree, codeBlockType);
}
*/
#endif

#ifdef NLC_ADVANCED_REFERENCING_MONITOR_CONTEXT
NLCcodeblock* NLCcodeBlockClassClass::createCodeBlocksDeclareContextList(NLCcodeblock* currentCodeBlockInTree, const int contextLevel)
{
	string contextLevelString = SHAREDvars.convertIntToString(contextLevel);
	NLCitem* contextLevelItem = new NLCitem(contextLevelString, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(contextLevelItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_DECLARE_CONTEXT_LIST;
	currentCodeBlockInTree = this->createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}

NLCcodeblock* NLCcodeBlockClassClass::createCodeBlocksAddEntityToContextLevelListNewFunction(NLCcodeblock* currentCodeBlockInTree)
{
	//required because printCodeBlocks requires at least 1 param
	NLCitem* entityItem = new NLCitem("dummyentity", NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_CONTEXT_LIST_NEW_FUNCTION;
	currentCodeBlockInTree = this->createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}

NLCcodeblock* NLCcodeBlockClassClass::createCodeBlocksClearContextListNewFunction(NLCcodeblock* currentCodeBlockInTree)
{
	//required because printCodeBlocks requires at least 1 param
	NLCitem* entityItem = new NLCitem("dummyentity", NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_CLEAR_CONTEXT_LIST_NEW_FUNCTION;
	currentCodeBlockInTree = this->createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}

NLCcodeblock* NLCcodeBlockClassClass::createCodeBlocksAddEntityToContextLevelListExecuteFunction(NLCcodeblock* currentCodeBlockInTree, const int contextLevel, const GIAentityNode* entity, const int sentenceIndex)
{
	string contextLevelString = SHAREDvars.convertIntToString(contextLevel);
	NLCitem* contextLevelItem = new NLCitem(contextLevelString, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(contextLevelItem);

	NLCitem* entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	string sentenceIndexString = SHAREDvars.convertIntToString(sentenceIndex);
	NLCitem* sentenceIndexItem = new NLCitem(sentenceIndexString, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(sentenceIndexItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_CONTEXT_LIST_EXECUTE_FUNCTION;
	currentCodeBlockInTree = this->createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}

//NB createCodeBlocksClearContextListVariableExecuteFunction is embedded in printCodeBlocks()
NLCcodeblock* NLCcodeBlockClassClass::createCodeBlocksClearContextListVariableExecuteFunction(NLCcodeblock* currentCodeBlockInTree, const int contextLevel)
{
	string contextLevelString = SHAREDvars.convertIntToString(contextLevel);
	NLCitem* contextLevelItem = new NLCitem(contextLevelString, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(contextLevelItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_CLEAR_CONTEXT_LIST_EXECUTE_FUNCTION;
	currentCodeBlockInTree = this->createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}
#endif

NLCcodeblock* NLCcodeBlockClassClass::createCodeBlocksCreateContextBlock(NLCcodeblock* currentCodeBlockInTree)
{
	//required because printCodeBlocks requires at least 1 param
	NLCitem* entityItem = new NLCitem("dummyentity", NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_CONTEXT_BLOCK;
	currentCodeBlockInTree = this->createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}


#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS
NLCcodeblock* NLCcodeBlockClassClass::createCodeBlocksCastVectorNewFunction(NLCcodeblock* currentCodeBlockInTree)
{
	//required because printCodeBlocks requires at least 1 param
	NLCitem* entityItem = new NLCitem("dummyentity", NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_CAST_VECTOR_NEW_FUNCTION;
	currentCodeBlockInTree = this->createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}

NLCcodeblock* NLCcodeBlockClassClass::createCodeBlocksCastVectorExecuteFunction(NLCcodeblock* currentCodeBlockInTree, NLCitem* item, NLCitem* itemPassCastClassName)
{
	currentCodeBlockInTree->parameters.push_back(item);
	currentCodeBlockInTree->parameters.push_back(itemPassCastClassName);

	int codeBlockType = NLC_CODEBLOCK_TYPE_CAST_VECTOR_EXECUTE_FUNCTION;
	currentCodeBlockInTree = this->createCodeBlock(currentCodeBlockInTree, codeBlockType);
}
#endif

#ifdef NLC_ADVANCED_REFERENCING_SUPPORT_ALIASES
NLCcodeblock* NLCcodeBlockClassClass::createCodeBlocksAddAliasToEntityAliasList(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const string aliasName)
{

	NLCitem* entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	NLCitem* aliasEntityItem = new NLCitem(aliasName, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(aliasEntityItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_ADD_ALIAS_TO_ENTITY_ALIAS_LIST;
	currentCodeBlockInTree = this->createCodeBlock(currentCodeBlockInTree, codeBlockType);


	return currentCodeBlockInTree;
}

NLCcodeblock* NLCcodeBlockClassClass::createCodeBlocksFindAliasAndAddToCategoryListNewFunction(NLCcodeblock* currentCodeBlockInTree)
{

	//required because printCodeBlocks requires at least 1 param
	NLCitem* entityItem = new NLCitem("dummyentity", NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_FIND_ALIAS_AND_ADD_TO_CATEGORY_LIST_NEW_FUNCTION;
	currentCodeBlockInTree = this->createCodeBlock(currentCodeBlockInTree, codeBlockType);


	return currentCodeBlockInTree;
}
//NB genericListAppendName is "CategoryList"
NLCcodeblock* NLCcodeBlockClassClass::createCodeBlocksFindAliasAndAddToCategoryListExecuteFunction(NLCcodeblock* currentCodeBlockInTree, const string aliasName, const GIAentityNode* entity, const string genericListAppendName, const int sentenceIndex)
{

	NLCitem* aliasEntityItem = new NLCitem(aliasName, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(aliasEntityItem);

	//NB entity is used for both instance and category list
	NLCitem* entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT, sentenceIndex);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	NLCitem* genericListAppendItem = new NLCitem(genericListAppendName, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(genericListAppendItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_FIND_ALIAS_AND_ADD_TO_CATEGORY_LIST_EXECUTE_FUNCTION;
	currentCodeBlockInTree = this->createCodeBlock(currentCodeBlockInTree, codeBlockType);


	return currentCodeBlockInTree;
}

NLCcodeblock* NLCcodeBlockClassClass::createCodeBlocksFindAliasNewFunction(NLCcodeblock* currentCodeBlockInTree)
{

	//required because printCodeBlocks requires at least 1 param
	NLCitem* entityItem = new NLCitem("dummyentity", NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_FIND_ALIAS_NEW_FUNCTION;
	currentCodeBlockInTree = this->createCodeBlock(currentCodeBlockInTree, codeBlockType);


	return currentCodeBlockInTree;
}
NLCcodeblock* NLCcodeBlockClassClass::createCodeBlocksFindAliasExecuteFunction(NLCcodeblock* currentCodeBlockInTree, const string aliasName, const GIAentityNode* entity)
{

	NLCitem* aliasEntityItem = new NLCitem(aliasName, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(aliasEntityItem);

	//NB entity is used for both instance and category list
	NLCitem* entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_FIND_ALIAS_EXECUTE_FUNCTION;
	currentCodeBlockInTree = this->createCodeBlock(currentCodeBlockInTree, codeBlockType);


	return currentCodeBlockInTree;
}

bool NLCcodeBlockClassClass::findAliasInEntity(GIAentityNode* entity, string* aliasName)
{
	bool result = false;
	if(!(entity->aliasList.empty()))
	{
		*aliasName = entity->aliasList.back();
		result = true;
	}
	return result;
}

#ifdef NLC_ADVANCED_REFERENCING_SUPPORT_ALIASES_PREVENT_ADDING_AS_FUNCTION_ARGUMENT
unordered_map<string, string>* functionAliasClassList;	//<aliasName, aliasClassName>

unordered_map<string, string>* NLCcodeBlockClassClass::getFunctionAliasClassList()
{
	return functionAliasClassList;
}

void NLCcodeBlockClassClass::initialiseFunctionAliasClassList()
{
	//functionAliasClassList->clear();
	functionAliasClassList = new unordered_map<string, string>;
}

bool NLCcodeBlockClassClass::findEntityNameInFunctionAliasList(const string aliasName, string* aliasClassName)
{
	bool result = false;
	unordered_map<string, string>::iterator iter1 = functionAliasClassList->find(aliasName);
	if(iter1 != functionAliasClassList->end())
	{
		*aliasClassName = iter1->second;
		result = true;
	}
	return result;
}
#endif
#endif

NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockDebug(NLCcodeblock* currentCodeBlockInTree, const string warning)
{
	NLCitem* debugItem = new NLCitem(warning, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(debugItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_DEBUG;
	currentCodeBlockInTree = this->createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}

#ifdef NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY
string NLCcodeBlockClassClass::generateCategoryListPropertyCountVariableName(const GIAentityNode* entity)
{
	string categoryListPropertyCountVariableName = NLCitemClass.generateInstanceName(entity) + NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION + NLC_ITEM_TYPE_LIST_VAR_APPENDITION + NLC_ITEM_TYPE_PROPERTYCOUNT_VAR_APPENDITION;

	return categoryListPropertyCountVariableName;
}
#endif


NLCcodeblock* NLCcodeBlockClassClass::clearCodeBlock(NLCcodeblock* codeBlock)
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

NLCcodeblock* NLCcodeBlockClassClass::getLastCodeBlockInLevel(NLCcodeblock* currentCodeBlockInTree)
{
	while(currentCodeBlockInTree->next != NULL)
	{
		currentCodeBlockInTree = currentCodeBlockInTree->next;
	}
	return currentCodeBlockInTree;
}

NLCcodeblock* NLCcodeBlockClassClass::getLastSetCodeBlockInLevel(NLCcodeblock* currentCodeBlockInTree)
{
	if(currentCodeBlockInTree->next != NULL)
	{
		while(currentCodeBlockInTree->next->next != NULL)
		{
			currentCodeBlockInTree = currentCodeBlockInTree->next;
		}
	}
	return currentCodeBlockInTree;
}


#ifdef NLC_NORMALISE_TWOWAY_PREPOSITIONS
GIAentityNode* NLCcodeBlockClassClass::generateInverseConditionEntity(const GIAentityNode* conditionRelationshipEntity)
{
	GIAentityNode* conditionEntityInverse = new GIAentityNode();
	conditionEntityInverse->entityType = GIA_ENTITY_TYPE_CONDITION;
	conditionEntityInverse->entityName = conditionRelationshipEntity->entityName;
	conditionEntityInverse->idInstance = conditionRelationshipEntity->idInstance;
	conditionEntityInverse->relationshipSubjectEntity->push_back(conditionRelationshipEntity->relationshipObjectEntity->back());	//CHECKTHIS: reused existing connections
	conditionEntityInverse->relationshipObjectEntity->push_back(conditionRelationshipEntity->relationshipSubjectEntity->back());	//CHECKTHIS: reused existing connections
	return conditionEntityInverse;
}
#endif


#ifdef NLC_REDEFINITIONS
NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockCheckParentClassNameExecuteFunction1(NLCcodeblock* currentCodeBlockInTree, const string objectInstanceName, const string classNameToFind)
{
	NLCitem* objectItem = new NLCitem("object", NLC_ITEM_TYPE_OBJECT);
	objectItem->instanceName = objectInstanceName;
	currentCodeBlockInTree->parameters.push_back(objectItem);

	NLCitem* classNameToFindItem = new NLCitem(classNameToFind, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(classNameToFindItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_CHECK_PARENT_CLASS_NAME_EXECUTE_FUNCTION1;
	currentCodeBlockInTree = this->createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}
NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockCheckParentClassNameExecuteFunction1(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* object, const string classNameToFind)
{
	NLCitem* objectItem = new NLCitem(object, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(objectItem);

	NLCitem* classNameToFindItem = new NLCitem(classNameToFind, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(classNameToFindItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_CHECK_PARENT_CLASS_NAME_EXECUTE_FUNCTION1;
	currentCodeBlockInTree = this->createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}
NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockCheckParentClassNameExecuteFunction2(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* object, const string classNameToFind)
{
	NLCitem* objectItem = new NLCitem(object, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(objectItem);

	NLCitem* classNameToFindItem = new NLCitem(classNameToFind, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(classNameToFindItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_CHECK_PARENT_CLASS_NAME_EXECUTE_FUNCTION2;
	currentCodeBlockInTree = this->createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}
NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockCheckParentClassNameNewFunction(NLCcodeblock* currentCodeBlockInTree)
{
	//required because printCodeBlocks requires at least 1 param
	NLCitem* entityItem = new NLCitem("dummyentity", NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_CHECK_PARENT_CLASS_NAME_NEW_FUNCTION;
	currentCodeBlockInTree = this->createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}

NLCcodeblock* NLCcodeBlockClassClass::createCodeConvertParentToChildClass(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* parentEntity, const GIAentityNode* childEntity)
{
	NLCitem* parentItem = new NLCitem(parentEntity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(parentItem);

	NLCitem* childItem = new NLCitem(childEntity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(childItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_CONVERT_PARENT_TO_CHILD_CLASS;
	currentCodeBlockInTree = this->createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}
#endif

NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockDeclareTempVariable(NLCcodeblock* currentCodeBlockInTree, const string tempVariableClassName, const string tempVariableInstanceName)
{
	NLCitem* tempVariableItem = new NLCitem(tempVariableInstanceName, NLC_ITEM_TYPE_OBJECT);
	tempVariableItem->className = tempVariableClassName;
	tempVariableItem->instanceName = tempVariableInstanceName;
	currentCodeBlockInTree->parameters.push_back(tempVariableItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_DECLARE_TEMP_VARIABLE;
	currentCodeBlockInTree = this->createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}

NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockSetTempVariable(NLCcodeblock* currentCodeBlockInTree, const string tempVariableInstanceName, const GIAentityNode* entity)
{
	NLCitem* tempVariableItem = new NLCitem(tempVariableInstanceName, NLC_ITEM_TYPE_OBJECT);
	tempVariableItem->instanceName = tempVariableInstanceName;
	currentCodeBlockInTree->parameters.push_back(tempVariableItem);

	NLCitem* entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_SET_TEMP_VARIABLE;
	currentCodeBlockInTree = this->createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}

NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockDeclareTempVariableAndSetToEntity(NLCcodeblock* currentCodeBlockInTree, const string tempVariableClassName, const string tempVariableInstanceName, const GIAentityNode* entity)
{
	NLCitem* tempVariableItem = new NLCitem(tempVariableInstanceName, NLC_ITEM_TYPE_OBJECT);
	tempVariableItem->className = tempVariableClassName;
	tempVariableItem->instanceName = tempVariableInstanceName;
	currentCodeBlockInTree->parameters.push_back(tempVariableItem);

	NLCitem* entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_DECLARE_TEMP_VARIABLE_AND_SET_TO_ENTITY;
	currentCodeBlockInTree = this->createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}

NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockIfTempVariableEqualsEntity(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity1, const GIAentityNode* entity2)
{
	NLCitem* entityItem1 = new NLCitem(entity1, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(entityItem1);

	NLCitem* entityItem2 = new NLCitem(entity2, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(entityItem2);

	int codeBlockType = NLC_CODEBLOCK_TYPE_IF_TEMP_VARIABLE_EQUALS_ENTITY;
	currentCodeBlockInTree = this->createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}

NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockIfTempVariableEqualsEntity(NLCcodeblock* currentCodeBlockInTree, const string tempVariableClassName, const string tempVariableInstanceName, const GIAentityNode* entity)
{
	NLCitem* tempVariableItem = new NLCitem(tempVariableInstanceName, NLC_ITEM_TYPE_OBJECT);
	tempVariableItem->className = tempVariableClassName;
	tempVariableItem->instanceName = tempVariableInstanceName;
	currentCodeBlockInTree->parameters.push_back(tempVariableItem);

	NLCitem* entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_IF_TEMP_VARIABLE_EQUALS_ENTITY;
	currentCodeBlockInTree = this->createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}

#ifdef NLC_NON_LIBRARY_FUNCTIONS_EXTENDED
NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockAddPropertyNewFunction(NLCcodeblock* currentCodeBlockInTree)
{
	//required because printCodeBlocks requires at least 1 param
	NLCitem* entityItem = new NLCitem("dummyentity", NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_ADD_PROPERTY_NEW_FUNCTION;
	currentCodeBlockInTree = this->createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}

NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockAddConditionNewFunction(NLCcodeblock* currentCodeBlockInTree)
{
	//required because printCodeBlocks requires at least 1 param
	NLCitem* entityItem = new NLCitem("dummyentity", NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_ADD_CONDITION_NEW_FUNCTION;
	currentCodeBlockInTree = this->createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}
#ifdef NLC_NORMALISE_TWOWAY_PREPOSITIONS_MARK_INVERSE_CONDITIONS
NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockAddConditionInverseNewFunction(NLCcodeblock* currentCodeBlockInTree)
{
	//required because printCodeBlocks requires at least 1 param
	NLCitem* entityItem = new NLCitem("dummyentity", NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_ADD_CONDITION_INVERSE_NEW_FUNCTION;
	currentCodeBlockInTree = this->createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}
#endif
#endif


#ifdef NLC_MATH_OBJECTS
NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockTestMathObjectNumericalValue(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const GIAentityNode* valueEntity)
{
	NLCitem* entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	NLCitem* valueItem = new NLCitem(valueEntity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(valueItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_TEST_MATH_OBJECT_NUMERICAL_VALUE;
	currentCodeBlockInTree = this->createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}

NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockSetMathObjectNumericalValue(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const GIAentityNode* valueEntity)
{
	NLCitem* entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	NLCitem* valueItem = new NLCitem(valueEntity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(valueItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_SET_MATH_OBJECT_NUMERICAL_VALUE;
	currentCodeBlockInTree = this->createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}
NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockDeclareNewDecimalPointerVar(NLCcodeblock* currentCodeBlockInTree, const string decimalPointerVariableName)
{
	NLCitem* decimalPointerItem = new NLCitem(decimalPointerVariableName, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(decimalPointerItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_DECLARE_NEW_DECIMAL_POINTER_VARIABLE;

	return this->createCodeBlock(currentCodeBlockInTree, codeBlockType);
}

NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockSetDecimalPointerToEntityMathObjectNumericalValue(NLCcodeblock* currentCodeBlockInTree, const string decimalPointerVariableName, const GIAentityNode* entity)
{
	NLCitem* decimalPointerItem = new NLCitem(decimalPointerVariableName, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(decimalPointerItem);

	NLCitem* entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_SET_DECIMAL_POINTER_TO_ENTITY_MATH_OBJECT_NUMERICAL_VALUE;
	currentCodeBlockInTree = this->createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}
NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockSetMathObjectTypeAsNumerical(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity)
{
	NLCitem* entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_SET_MATH_OBJECT_TYPE_AS_NUMERICAL;
	currentCodeBlockInTree = this->createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}

#ifdef NLC_MATH_OBJECTS_ADVANCED
NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockDeclareNewGenericEntityPointerVar(NLCcodeblock* currentCodeBlockInTree, const string genericEntityPointerVariableName)
{
	NLCitem* genericEntityPointerItem = new NLCitem(genericEntityPointerVariableName, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(genericEntityPointerItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_DECLARE_NEW_GENERIC_ENTITY_POINTER_VARIABLE;

	return this->createCodeBlock(currentCodeBlockInTree, codeBlockType);
}

NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockSetGenericEntityPointerToEntity(NLCcodeblock* currentCodeBlockInTree, const string genericEntityPointerVariableName, const GIAentityNode* entity)
{
	NLCitem* genericEntityPointerItem = new NLCitem(genericEntityPointerVariableName, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(genericEntityPointerItem);

	NLCitem* entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_SET_GENERIC_ENTITY_POINTER_TO_ENTITY;
	currentCodeBlockInTree = this->createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}
#ifdef NLC_MATH_OBJECTS_STRING
NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockSetMathObjectStringValue(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const GIAentityNode* valueEntity)
{
	NLCitem* entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	NLCitem* valueItem = new NLCitem(valueEntity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(valueItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_SET_MATH_OBJECT_STRING_VALUE;
	currentCodeBlockInTree = this->createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}
NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockDeclareNewStringPointerVar(NLCcodeblock* currentCodeBlockInTree, const string stringPointerVariableName)
{
	NLCitem* decimalPointerItem = new NLCitem(stringPointerVariableName, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(decimalPointerItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_DECLARE_NEW_STRING_POINTER_VARIABLE;

	return this->createCodeBlock(currentCodeBlockInTree, codeBlockType);
}
NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockSetStringPointerToEntityMathObjectStringValue(NLCcodeblock* currentCodeBlockInTree, const string stringPointerVariableName, const GIAentityNode* entity)
{
	NLCitem* stringPointerItem = new NLCitem(stringPointerVariableName, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(stringPointerItem);

	NLCitem* entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_SET_STRING_POINTER_TO_ENTITY_MATH_OBJECT_STRING_VALUE;
	currentCodeBlockInTree = this->createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}
NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockSetMathObjectTypeAsString(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity)
{
	NLCitem* entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_SET_MATH_OBJECT_TYPE_AS_STRING;
	currentCodeBlockInTree = this->createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}
#endif
#ifdef NLC_MATH_OBJECTS_BOOLEAN
NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockSetMathObjectBooleanValue(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const GIAentityNode* valueEntity)
{
	NLCitem* entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	NLCitem* valueItem = new NLCitem(valueEntity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(valueItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_SET_MATH_OBJECT_BOOLEAN_VALUE;
	currentCodeBlockInTree = this->createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}
NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockDeclareNewBooleanPointerVar(NLCcodeblock* currentCodeBlockInTree, const string booleanPointerVariableName)
{
	NLCitem* booleanPointerItem = new NLCitem(booleanPointerVariableName, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(booleanPointerItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_DECLARE_NEW_BOOLEAN_POINTER_VARIABLE;

	return this->createCodeBlock(currentCodeBlockInTree, codeBlockType);
}
NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockSetBooleanPointerToEntityMathObjectBooleanValue(NLCcodeblock* currentCodeBlockInTree, const string booleanPointerVariableName, const GIAentityNode* entity)
{
	NLCitem* booleanPointerItem = new NLCitem(booleanPointerVariableName, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(booleanPointerItem);

	NLCitem* entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_SET_BOOLEAN_POINTER_TO_ENTITY_MATH_OBJECT_BOOLEAN_VALUE;
	currentCodeBlockInTree = this->createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}
NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockSetMathObjectTypeAsBoolean(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity)
{
	NLCitem* entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_SET_MATH_OBJECT_TYPE_AS_BOOLEAN;
	currentCodeBlockInTree = this->createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}
#endif
#endif

//check that pointer is not NULL
#ifdef NLC_MATH_OBJECTS_TEST_NULL_POINTER_MAINTAIN_CONTEXT
NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockTestDecimalPointerValue(NLCcodeblock* currentCodeBlockInTree, const string decimalPointerVariableName)
{
	NLCitem* decimalPointerItem = new NLCitem(decimalPointerVariableName, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(decimalPointerItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_TEST_POINTER_VALUE;
	currentCodeBlockInTree = this->createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}
#else
NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockCheckDecimalPointerValue(NLCcodeblock* currentCodeBlockInTree, const string decimalPointerVariableName)
{
	NLCitem* decimalPointerItem = new NLCitem(decimalPointerVariableName, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(decimalPointerItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_CHECK_POINTER_VALUE;
	currentCodeBlockInTree = this->createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}
#endif

#endif

NLCcodeblock* NLCcodeBlockClassClass::createCodeBlockIfTempVariableNameEqualsClassName(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const string className)
{
	NLCitem* tempVariableItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(tempVariableItem);

	NLCitem* classNameItem = new NLCitem(className, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(classNameItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_IF_TEMP_VARIABLE_NAME_EQUALS_CLASS_NAME;
	currentCodeBlockInTree = this->createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}


#ifdef NLC_REFERENCING_OBJECTS_IN_PLURAL_LIST_BY_NUMBER
bool NLCcodeBlockClassClass::checkNumericalReferenceToEntity(const GIAentityNode* entity)
{
	bool numericalReference = false;
	if((entity->hasQuantity) && (entity->grammaticalNumber != GRAMMATICAL_NUMBER_PLURAL))
	{
		numericalReference = true;
	}
	return numericalReference;
}
#endif

#ifdef NLC_TRANSLATOR_TEST_DEFINITE_ENTITY_EXISTENCE
NLCcodeblock* NLCcodeBlockClassClass::createCodeVerifyDefiniteReferenceExistenceNewFunction(NLCcodeblock* currentCodeBlockInTree)
{
	//required because printCodeBlocks requires at least 1 param
	NLCitem* entityItem = new NLCitem("dummyentity", NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_VERIFY_DEFINITE_ENTITY_EXISTENCE_NEW_FUNCTION;
	currentCodeBlockInTree = this->createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}

NLCcodeblock* NLCcodeBlockClassClass::createCodeVerifyDefiniteReferenceExistenceExecuteFunction(NLCcodeblock* currentCodeBlockInTree, const GIAentityNode* entity, const string genericListAppendName, const int sentenceIndex)
{
	NLCitem* entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT, sentenceIndex);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	NLCitem* genericListAppendNameItem = new NLCitem(genericListAppendName, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(genericListAppendNameItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_VERIFY_DEFINITE_ENTITY_EXISTENCE_EXECUTE_FUNCTION;
	currentCodeBlockInTree = this->createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}
#endif

GIAentityNode* NLCcodeBlockClassClass::getSameReferenceSetSubstanceNonQualityChild(GIAentityNode* parentEntity, int sentenceIndex, bool *foundChildEntity)
{
	GIAentityNode* childEntity = parentEntity;
						
	bool foundParentProperty = false;
	for(vector<GIAentityConnection*>::iterator propertyNodeListIterator = parentEntity->propertyNodeList->begin(); propertyNodeListIterator < parentEntity->propertyNodeList->end(); propertyNodeListIterator++)
	{
		GIAentityConnection* propertyConnection = *propertyNodeListIterator;
		GIAentityNode* propertyRelationshipObjectEntity = GIAtranslatorOperations.getPropertyRelationshipObjectEntity(propertyConnection);

		#ifdef NLC_DEFINE_LOCAL_VARIABLES_FOR_ALL_INDEFINATE_ENTITIES
		if(this->checkSentenceIndexParsingCodeBlocks(propertyRelationshipObjectEntity, propertyConnection, sentenceIndex, false))
		#else
		if(this->checkSentenceIndexParsingCodeBlocks(propertyRelationshipObjectEntity, propertyConnection, sentenceIndex, false) || propertyRelationshipObjectEntity->NLCparsedForCodeBlocks)	//CHECKTHIS; copied from getParent(); if parent is propertyRelationshipObjectEntity->NLCparsedForCodeBlocks && !sameSentence, then child must be propertyRelationshipObjectEntity->NLCparsedForCodeBlocks && !sameSentence
		#endif
		{
			if(!(propertyRelationshipObjectEntity->entityType == GIA_ENTITY_TYPE_QUALITY))
			{
				if(propertyConnection->sameReferenceSet)	//added 1n30a
				{
					#ifdef NLC_APPLY_GET_SAME_REFERENCE_SET_NON_QUALITY_CHILD_FIX_TO_VERIFY_NOT_POSSESSION_AUXILIARY_HAVE
					if(!(propertyConnection->possessionAuxiliaryHave))	//added 1p2b
					{					
					#endif
					#ifdef NLC_APPLY_GET_SAME_REFERENCE_SET_NON_QUALITY_CHILD_FIX_TO_VERIFY_RCMOD_DOES_NOT_INDICATE_SAME_REFERENCE_SET
					if(!(propertyConnection->rcmodIndicatesSameReferenceSet))	//added 1p2b
					{
					#endif
						childEntity = this->getSameReferenceSetSubstanceNonQualityChild(propertyRelationshipObjectEntity, sentenceIndex, foundChildEntity);
						*foundChildEntity = true;
					#ifdef NLC_APPLY_GET_SAME_REFERENCE_SET_NON_QUALITY_CHILD_FIX_TO_VERIFY_RCMOD_DOES_NOT_INDICATE_SAME_REFERENCE_SET
					}
					#endif
					#ifdef NLC_APPLY_GET_SAME_REFERENCE_SET_NON_QUALITY_CHILD_FIX_TO_VERIFY_NOT_POSSESSION_AUXILIARY_HAVE
					}
					#endif					
				}
			}
		}
	}
	
	return childEntity;
}


