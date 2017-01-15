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
 * File Name: NLCtranslatorCodeBlocksOperations.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2014 Baxter AI (baxterai.com)
 * Project: Natural Language Programming Interface (compiler)
 * Project Version: 1l9e 05-November-2014
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/



#include <ctime>
#include <cstdlib>	//for random number generation
#include <cmath>

#include "NLCtranslatorCodeBlocksOperations.h"
#include "GIAtranslatorDefs.h"
#include "GIAtranslatorOperations.h"	//required for getPrimaryConceptNodeDefiningInstance()
#include "NLCprintDefs.h"	//required for NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION

void generateActionCodeBlocks(NLCcodeblock ** currentCodeBlockInTree, GIAentityNode * actionEntity, int sentenceIndex, string NLCfunctionName)
{
	NLCcodeblock * firstCodeBlockInSentence = *currentCodeBlockInTree;

	#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
	if(!(actionEntity->NLCparsedForlogicalConditionOperations))
	{
	#endif
		#ifdef NLC_DEBUG
		cout << "actionEntity->entityName = " << actionEntity->entityName << endl;
		cout << "sentenceIndex = " << sentenceIndex << endl;
		cout << "actionEntity->wasReference = " << actionEntity->wasReference << endl;
		#endif

		#ifdef NLC_RECORD_ACTION_HISTORY_GENERALISABLE
		bool sameReferenceSet = false;
		#endif
		
		bool actionIsSingleWord = false;
		bool actionHasObject = false;
		GIAentityNode * objectEntity = NULL;
		GIAentityConnection * actionObjectConnection = NULL;
		if(getActionObjectEntityConnection(actionEntity, sentenceIndex, &actionObjectConnection))
		{
			//cout << "actionObjectConnection->sameReferenceSet = " << actionObjectConnection->sameReferenceSet << endl;
			#ifdef NLC_RECORD_ACTION_HISTORY_GENERALISABLE
			if(!(actionObjectConnection->sameReferenceSet))
			{
			#endif
				actionHasObject = true;
				objectEntity = actionObjectConnection->entity;
				#ifdef NLC_PREPROCESSOR_INTERPRET_SINGLE_WORD_SENTENCES_AS_ACTIONS
				if(objectEntity->entityName == NLC_PREPROCESSOR_INTERPRET_SINGLE_WORD_SENTENCES_AS_ACTIONS_DUMMY_TEXT_ACTION_OBJECT)
				{
					actionIsSingleWord = true;
					actionHasObject = false;
					objectEntity->disabled = true;	//prevent parsing of dummyActionObject by generateCodeBlocksPart4objectInitialisations()
				}
				#endif	
			#ifdef NLC_RECORD_ACTION_HISTORY_GENERALISABLE
			}
			#endif
		}
		bool actionHasSubject = false;
		GIAentityNode * subjectEntity = NULL;
		GIAentityConnection * actionSubjectConnection = NULL;
		if(getActionSubjectEntityConnection(actionEntity, sentenceIndex, &actionSubjectConnection))
		{
			//cout << "actionSubjectConnection->sameReferenceSet = " << actionSubjectConnection->sameReferenceSet << endl;
			#ifdef NLC_RECORD_ACTION_HISTORY_GENERALISABLE
			if(!(actionSubjectConnection->sameReferenceSet))
			{
			#endif
				actionHasSubject = true;
				subjectEntity = actionSubjectConnection->entity;
			#ifdef NLC_RECORD_ACTION_HISTORY_GENERALISABLE
			}
			#endif
		}
		
			
		NLCcodeblock * functionExecuteCodeBlockInTree = NULL;

		NLCitem * functionItem = NULL;
		if(actionHasObject || actionHasSubject || actionIsSingleWord)
		{
			functionItem = new NLCitem(actionEntity, NLC_ITEM_TYPE_FUNCTION_EXECUTION_ARGUMENT_FUNCTION);

			#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS
			initialiseFunctionArguments(currentCodeBlockInTree, actionEntity, sentenceIndex);
			//firstCodeBlockInSentence = *currentCodeBlockInTree;		//removed 1f1b... [CHECKTHIS]
			#endif

			#ifndef NLC_DEFINE_LOCAL_VARIABLES_FOR_ALL_INDEFINATE_ENTITIES
			//this is where original getParentAndInitialiseParentIfNecessaryOrGenerateContextBlocks code went (for both subjectEntity and objectEntity)
			if(actionHasSubject)
			{
				getParentAndGenerateParentInitialisationCodeBlock(currentCodeBlockInTree, subjectEntity, sentenceIndex, true, false);	//parseConditionParents was previously set false in original implementation [although the GIA specification supports such arrangements, in practice however they probably can't be generated as x will always be a condition subject not a condition object of y in "x is near the y"]
			}
			if(actionHasObject)
			{
				getParentAndGenerateParentInitialisationCodeBlock(currentCodeBlockInTree, objectEntity, sentenceIndex, true, false);	//parseConditionParents was previously set false in original implementation [although the GIA specification supports such arrangements, in practice however they probably can't be generated as x will always be a condition subject not a condition object of y in "x is near the y"]
			}
			#endif

		}

		NLCgenerateContextBlocksVariables generateContextBlocksVariables;
		generateContextBlocksVariables.onlyGenerateContextBlocksIfConnectionsParsedForNLC = true;

		if(actionHasObject)
		{
			#ifdef NLC_FUNCTIONS_SUPPORT_PLURAL_OBJECTS
			#ifdef NLC_FUNCTIONS_SUPPORT_PLURAL_OBJECTS_ENTER_GENERATED_CATEGORY_LIST
			generateContextBlocksVariables.enterGeneratedCategoryList = true;	//is required for createCodeBlockUpdateLastSentenceReferenced()
			NLCcodeblock * codeBlockInTreeBeforeParseContext = *currentCodeBlockInTree;
			#else
			generateContextBlocksVariables.enterGeneratedCategoryList = false;
			#endif
			#endif
			if(getParentAndInitialiseParentIfNecessaryOrGenerateContextBlocks(currentCodeBlockInTree, objectEntity, sentenceIndex, &generateContextBlocksVariables, true, false))	//parseConditionParents was previously set false in original implementation [although the GIA specification supports such arrangements, in practice however they probably can't be generated as x will always be a condition subject not a condition object of y in "x is near the y"]
			{
				#ifdef NLC_DEBUG
				//cout << "actionHasObject: parent and its children initialised" << endl;
				#endif
			}

			NLCitem *functionObjectItem = new NLCitem(objectEntity, NLC_ITEM_TYPE_FUNCTION_EXECUTION_ARGUMENT_FUNCTION_OBJECT);
			#ifdef NLC_RECORD_ACTION_HISTORY
			*currentCodeBlockInTree = createCodeBlockRecordHistoryActionObject(*currentCodeBlockInTree, functionItem, functionObjectItem);
			#endif

			#ifdef NLC_FUNCTIONS_SUPPORT_PLURAL_OBJECTS
			#ifdef NLC_FUNCTIONS_SUPPORT_PLURAL_OBJECTS_ENTER_GENERATED_CATEGORY_LIST
			*currentCodeBlockInTree = getLastCodeBlockInLevel(codeBlockInTreeBeforeParseContext);
			#endif
			#endif

			NLCitem *functionSubjectItem = NULL;
			if(actionHasSubject)
			{
				#ifdef NLC_FUNCTIONS_SUPPORT_PLURAL_SUBJECTS
				#ifdef NLC_FUNCTIONS_SUPPORT_PLURAL_SUBJECTS_ENTER_GENERATED_CATEGORY_LIST
				generateContextBlocksVariables.enterGeneratedCategoryList = true;	//is required for createCodeBlockUpdateLastSentenceReferenced()
				codeBlockInTreeBeforeParseContext = *currentCodeBlockInTree;
				#else
				generateContextBlocksVariables.enterGeneratedCategoryList = false;	
				#endif
				#endif
				if(getParentAndInitialiseParentIfNecessaryOrGenerateContextBlocks(currentCodeBlockInTree, subjectEntity, sentenceIndex, &generateContextBlocksVariables, true, false))	//parseConditionParents was previously set false in original implementation [although the GIA specification supports such arrangements, in practice however they probably can't be generated as x will always be a condition subject not a condition object of y in "x is near the y"]
				{
					#ifdef NLC_DEBUG
					//cout << "actionHasSubject2: parent and its children initialised" << endl;
					#endif
				}

				functionSubjectItem = new NLCitem(subjectEntity, NLC_ITEM_TYPE_FUNCTION_EXECUTION_ARGUMENT_FUNCTION_OWNER);
				#ifdef NLC_RECORD_ACTION_HISTORY
				*currentCodeBlockInTree = createCodeBlockRecordHistoryActionSubject(*currentCodeBlockInTree, functionItem, functionSubjectItem);
				#endif

				#ifdef NLC_FUNCTIONS_SUPPORT_PLURAL_SUBJECTS
				#ifdef NLC_FUNCTIONS_SUPPORT_PLURAL_SUBJECTS_ENTER_GENERATED_CATEGORY_LIST
				*currentCodeBlockInTree = getLastCodeBlockInLevel(codeBlockInTreeBeforeParseContext);
				#endif
				#endif

				functionExecuteCodeBlockInTree = *currentCodeBlockInTree;
				#ifdef NLC_RECORD_ACTION_HISTORY_GENERALISABLE_DO_NOT_EXECUTE_PAST_TENSE_ACTIONS
				if(!hasTimeConditionNodePast(actionEntity))
				{
				#endif
					*currentCodeBlockInTree = createCodeBlockExecuteSubjectObject(*currentCodeBlockInTree, functionItem, functionSubjectItem, functionObjectItem);
				#ifdef NLC_RECORD_ACTION_HISTORY_GENERALISABLE_DO_NOT_EXECUTE_PAST_TENSE_ACTIONS
				}
				#endif

				//subjectEntity->parsedForNLCcodeBlocksActionRound = true;
			}
			else
			{
				functionExecuteCodeBlockInTree = *currentCodeBlockInTree;
				#ifdef NLC_RECORD_ACTION_HISTORY_GENERALISABLE_DO_NOT_EXECUTE_PAST_TENSE_ACTIONS
				if(!hasTimeConditionNodePast(actionEntity))
				{
				#endif
					*currentCodeBlockInTree = createCodeBlockExecuteObject(*currentCodeBlockInTree, functionItem, functionObjectItem);
				#ifdef NLC_RECORD_ACTION_HISTORY_GENERALISABLE_DO_NOT_EXECUTE_PAST_TENSE_ACTIONS
				}
				#endif
			}

			actionEntity->NLCparsedForCodeBlocks = true;
			//actionEntity->parsedForNLCcodeBlocksActionRound = true;
			//objectEntity->parsedForNLCcodeBlocksActionRound = true;
		}
		else if(actionHasSubject)
		{
			#ifdef NLC_FUNCTIONS_SUPPORT_PLURAL_SUBJECTS
			#ifdef NLC_FUNCTIONS_SUPPORT_PLURAL_SUBJECTS_ENTER_GENERATED_CATEGORY_LIST
			generateContextBlocksVariables.enterGeneratedCategoryList = true;	//is required for createCodeBlockUpdateLastSentenceReferenced()
			NLCcodeblock * codeBlockInTreeBeforeParseContext = *currentCodeBlockInTree;
			#else
			generateContextBlocksVariables.enterGeneratedCategoryList = false;	
			#endif
			#endif
			if(getParentAndInitialiseParentIfNecessaryOrGenerateContextBlocks(currentCodeBlockInTree, subjectEntity, sentenceIndex, &generateContextBlocksVariables, true, false))	//parseConditionParents was previously set false in original implementation [although the GIA specification supports such arrangements, in practice however they probably can't be generated as x will always be a condition subject not a condition object of y in "x is near the y"]
			{
				#ifdef NLC_DEBUG
				//cout << "actionHasSubject: parent and its children initialised" << endl;
				#endif
			}

			NLCitem *functionSubjectItem = new NLCitem(subjectEntity, NLC_ITEM_TYPE_FUNCTION_EXECUTION_ARGUMENT_FUNCTION_OWNER);

			#ifdef NLC_RECORD_ACTION_HISTORY
			*currentCodeBlockInTree = createCodeBlockRecordHistoryActionSubject(*currentCodeBlockInTree, functionItem, functionSubjectItem);
			#endif

			#ifdef NLC_FUNCTIONS_SUPPORT_PLURAL_SUBJECTS
			#ifdef NLC_FUNCTIONS_SUPPORT_PLURAL_SUBJECTS_ENTER_GENERATED_CATEGORY_LIST
			*currentCodeBlockInTree = getLastCodeBlockInLevel(codeBlockInTreeBeforeParseContext);	
			#endif
			#endif

			functionExecuteCodeBlockInTree = *currentCodeBlockInTree;
			#ifdef NLC_RECORD_ACTION_HISTORY_GENERALISABLE_DO_NOT_EXECUTE_PAST_TENSE_ACTIONS
			if(!hasTimeConditionNodePast(actionEntity))
			{
			#endif
				*currentCodeBlockInTree = createCodeBlockExecuteSubject(*currentCodeBlockInTree, functionItem, functionSubjectItem);
			#ifdef NLC_RECORD_ACTION_HISTORY_GENERALISABLE_DO_NOT_EXECUTE_PAST_TENSE_ACTIONS
			}
			#endif
			actionEntity->NLCparsedForCodeBlocks = true;
			//actionEntity->parsedForNLCcodeBlocksActionRound = true;
			//subjectEntity->parsedForNLCcodeBlocksActionRound = true;
		}
		#ifdef NLC_PREPROCESSOR_INTERPRET_SINGLE_WORD_SENTENCES_AS_ACTIONS
		else if(actionIsSingleWord)
		{
			functionExecuteCodeBlockInTree = *currentCodeBlockInTree;
			*currentCodeBlockInTree = createCodeBlockExecute(*currentCodeBlockInTree, functionItem);

			actionEntity->NLCparsedForCodeBlocks = true;	
		}
		#endif

		#ifdef NLC_INTERPRET_ACTION_PROPERTIES_AND_CONDITIONS_AS_FUNCTION_ARGUMENTS
		if(actionHasObject || actionHasSubject || actionIsSingleWord)
		{
			#ifndef NLC_SUPPORT_INPUT_FILE_LISTS
			generateFunctionDeclarationArgumentsWithActionConceptInheritance(actionEntity, &(functionExecuteCodeBlockInTree->parameters));	//#ifdef NLC_SUPPORT_INPUT_FILE_LISTS use class definition parameters instead
			#endif

			//detect action properties and conditions (and disable these for NLC generate code block parse: they will become function execution arguments)
			for(vector<GIAentityConnection*>::iterator entityIter = actionEntity->conditionNodeList->begin(); entityIter != actionEntity->conditionNodeList->end(); entityIter++)
			{
				GIAentityNode * actionCondition = (*entityIter)->entity;
				(*entityIter)->NLCparsedForCodeBlocks = true;
				actionCondition->NLCparsedForCodeBlocks = true;
			}
			for(vector<GIAentityConnection*>::iterator entityIter = actionEntity->propertyNodeList->begin(); entityIter != actionEntity->propertyNodeList->end(); entityIter++)
			{
				GIAentityNode * actionProperty = (*entityIter)->entity;
				(*entityIter)->NLCparsedForCodeBlocks = true;
				actionProperty->NLCparsedForCodeBlocks = true;
			}
		}
		#endif
	#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
	}
	#endif
	
	*currentCodeBlockInTree = getLastCodeBlockInLevel(firstCodeBlockInSentence);
}

#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS
void initialiseFunctionArguments(NLCcodeblock ** currentCodeBlockInTree, GIAentityNode * actionEntity, int sentenceIndex)
{
	actionEntity->NLCisSingularArgument = true;	//added 1e2c

	//declare an "abstract" variable for the action (that will be filled with the its properties and conditions) and passed as an argument to the function; eg "fast" of "run fast"
	if(!generateParentInitialisationCodeBlock(currentCodeBlockInTree, actionEntity, sentenceIndex))
	{
		
	}
}
#endif

#ifdef NLC_RECORD_ACTION_HISTORY_GENERALISABLE_DO_NOT_EXECUTE_PAST_TENSE_ACTIONS
bool hasTimeConditionNodePast(GIAentityNode * actionEntity)
{
	bool timeConditionPast = false;
	if(actionEntity->timeConditionNode != NULL)
	{
		GIAtimeConditionNode * timeCondition = actionEntity->timeConditionNode;
		if(timeCondition->tense == GRAMMATICAL_TENSE_PAST)
		{
			timeConditionPast = true;
		}
	}
	return timeConditionPast;
}
#endif

bool getParentAndInitialiseParentIfNecessaryOrGenerateContextBlocks(NLCcodeblock ** currentCodeBlockInTree, GIAentityNode * currentEntity, int sentenceIndex, NLCgenerateContextBlocksVariables * generateContextBlocksVariables, bool parseConditionParents, bool parseLogicalConditions)
{
	GIAentityNode * parentEntity = getParent(currentEntity, sentenceIndex, parseConditionParents);

	bool result = false;
	if(checkSentenceIndexParsingCodeBlocks(currentEntity, sentenceIndex, false))
	{//is this required?
	
		#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_BLOCKS_FOR_PARENT_INITIALISATION_SPECIAL
		//in the case that the action subject[/object] is indefinite and has an indefinite parent (eg A chicken's barrel eats the bike.) the actionSubject[/object]'s category list must be created here such that it can be accessed by a) createCodeBlockForCategoryList/createCodeBlockForLocalList and b) NLC_FUNCTIONS_SUPPORT_PLURAL_SUBJECTS_AND_OBJECTS: executeFunction(with plural action subject[/object] argument actionSubject[/Object]CategoryList) 
		*currentCodeBlockInTree = createCodeBlocksDeclareNewCategoryListVariable(*currentCodeBlockInTree, currentEntity, NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION);	//create new category list
		currentEntity->NLCcategoryListCreatedTemp = true;
		#endif
		
		if(generateParentInitialisationCodeBlockWithChecks(currentCodeBlockInTree, parentEntity, sentenceIndex, parseLogicalConditions))
		{
			result = true;
			//eg A chicken's barrel eats the bike.
			/*
			NB this code aligns with generateObjectInitialisationsBasedOnPropertiesAndConditions part c)
			definite children of indefinite parents are illegal here, eg "A chicken has the barrel - eat the bike" [NB ignoring irrelevant case "A chicken has the barrel that eats the bike" because the action is sameReferenceSet and as such will not be parsed by generateActionCodeBlocks()]
			indefinite children of definite parents are illegal here also, eg "The chicken has a barrel - eat the bike" [NB ignoring irrelevant case "The chicken has a barrel that eats the bike" because the action is sameReferenceSet and as such will not be parsed by generateActionCodeBlocks()]
			only indefinite children of indefinite parents are legal eg "A chicken's barrel eats the bike"
			This means that if the parent is indefinite, the child is also, and as such the child's full context does not have to be generated (ie can use createCodeBlockForCategoryList/createCodeBlockForLocalList instead of generateContextForChildEntity)
			*/
			#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_BLOCKS_FOR_PARENT_INITIALISATION_SPECIAL
			*currentCodeBlockInTree = createCodeBlockForCategoryList(*currentCodeBlockInTree, currentEntity, NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION);
			#else
			NLCitem * entityItem = new NLCitem(currentEntity, NLC_ITEM_TYPE_OBJECT);
			*currentCodeBlockInTree = createCodeBlockForLocalList(*currentCodeBlockInTree, entityItem);
			#endif
		}
		else
		{
			//eg The chicken's barrel eats the bike.
			if(generateContextForChildEntity(NULL, currentEntity, currentCodeBlockInTree, sentenceIndex, true))	//NB parent entity parameter is set to NULL such that it can be obtained by getSameReferenceSetDefiniteUniqueParent()
			{
				result = true;
			}
		}
		
		#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_BLOCKS_FOR_PARENT_INITIALISATION_SPECIAL
		currentEntity->NLCcategoryListCreatedTemp = false;
		#endif
	}

	return result;

}









#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN
bool generateContextBlocks(NLCcodeblock ** currentCodeBlockInTree, GIAentityNode * parentEntity, int sentenceIndex, NLCgenerateContextBlocksVariables * generateContextBlocksVariables, bool generatedParentContext, string genericListAppendName)
{	
	return generateContextBlocksCategories(currentCodeBlockInTree, parentEntity, sentenceIndex, generateContextBlocksVariables, generatedParentContext, genericListAppendName);	
}

bool generateContextBlocksCategories(NLCcodeblock ** currentCodeBlockInTree, GIAentityNode * parentEntity, int sentenceIndex, NLCgenerateContextBlocksVariables * generateContextBlocksVariables, bool generatedParentContext, string genericListAppendName)
{			
	bool contextFound = false;
	#ifdef NLC_USE_ADVANCED_REFERENCING_SUPPORT_ALIASES
	string parentEntityAliasName = "";
	if(findAliasInEntity(parentEntity, &parentEntityAliasName))
	{
		//added 1k14b;
		*currentCodeBlockInTree = createCodeBlocksDeclareNewCategoryListVariable(*currentCodeBlockInTree, parentEntity, genericListAppendName);
		*currentCodeBlockInTree = createCodeBlocksFindAliasAndAddToCategoryListExecuteFunction(*currentCodeBlockInTree, parentEntityAliasName, parentEntity, genericListAppendName);
		*currentCodeBlockInTree = createCodeBlockForCategoryList(*currentCodeBlockInTree, parentEntity, genericListAppendName);
		parentEntity->NLCcontextGenerated = true;
		contextFound = true;
	}
	else
	{
	#endif
		*currentCodeBlockInTree = createCodeBlocksDeclareNewCategoryListVariable(*currentCodeBlockInTree, parentEntity, genericListAppendName);
		#ifdef NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY_CHILDREN
		if(generateContextBlocksVariables->testNumerosity)
		{
			string categoryListPropertyCountVariableName = generateCategoryListPropertyCountVariableName(parentEntity);
			*currentCodeBlockInTree = createCodeBlockDeclareNewIntVar(*currentCodeBlockInTree, categoryListPropertyCountVariableName, 0);
		}
		#endif

		NLCcodeblock * lastCodeBlockInTree = *currentCodeBlockInTree;
		if(generateContextBlocksSimple(currentCodeBlockInTree, parentEntity, sentenceIndex, generateContextBlocksVariables, generatedParentContext, genericListAppendName))
		{
			contextFound = true;
		}

		addPropertyToCategoryList(currentCodeBlockInTree, parentEntity, parentEntity, genericListAppendName, generateContextBlocksVariables);

		if(!(generatedParentContext && !contextFound))
		{
			*currentCodeBlockInTree = lastCodeBlockInTree->next;
		}

		lastCodeBlockInTree = *currentCodeBlockInTree;
		#ifdef NLC_DEBUG_PARSE_CONTEXT_CHILDREN
		cout << "contextFound: parentEntity = " << parentEntity->entityName << endl;
		#endif
		
		//eg "A yellow bannana is on the table. Yellow bannanas are fruit. The fruit is tasty."
		for(vector<GIAentityConnection*>::iterator definitionNodeListIterator = parentEntity->entityNodeDefinitionList->begin(); definitionNodeListIterator < parentEntity->entityNodeDefinitionList->end(); definitionNodeListIterator++)
		{
			GIAentityNode* parentSubstanceConcept = (*definitionNodeListIterator)->entity;	//e.g. "fruit" substance concept
			if(parentSubstanceConcept->isSubstanceConcept)
			{		
				#ifdef NLC_DEBUG_PARSE_CONTEXT_CHILDREN	
				cout << "NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN: createCodeBlockForStatementsForDefinitionChildren(): parentSubstanceConcept = " << parentSubstanceConcept->entityName << ", idInstance = " << parentSubstanceConcept->idInstance << endl;
				#endif
				if(createCodeBlockForStatementsForDefinitionChildren(currentCodeBlockInTree, &lastCodeBlockInTree, parentEntity, parentSubstanceConcept, sentenceIndex, generateContextBlocksVariables, true, genericListAppendName))
				{
					contextFound = true;
				}
			}
		}

		#ifdef NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY
		#ifdef NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY_CHILDREN
		if(generateContextBlocksVariables->testNumerosity)
		{
			//test numerosity of child
			if(generateContextBlocksVariables->childQuantity > 1)
			{
				#ifdef NLC_CATEGORIES_TEST_PLURALITY_COMMENT
				*currentCodeBlockInTree = createCodeBlockCommentSingleLine(*currentCodeBlockInTree, "numerosity tests (child)");
				#endif
				string categoryListPropertyCountVariableName = generateCategoryListPropertyCountVariableName(parentEntity);
				*currentCodeBlockInTree = createCodeBlockIfIntVariableGreaterThanOrEqualToNum(*currentCodeBlockInTree, categoryListPropertyCountVariableName, generateContextBlocksVariables->childQuantity);
			}			

		}
		#endif
		#endif

		
		#ifdef NLC_FUNCTIONS_SUPPORT_PLURAL_SUBJECTS_AND_OBJECTS
		if(generateContextBlocksVariables->enterGeneratedCategoryList)
		{
		#endif
			#ifdef NLC_CATEGORIES_TEST_PLURALITY
			if((parentEntity->grammaticalNumber == GRAMMATICAL_NUMBER_SINGULAR) && assumedToAlreadyHaveBeenDeclared(parentEntity))	//added assumedToAlreadyHaveBeenDeclared(parentEntity) criteria 1j15a
			{
				#ifdef NLC_CATEGORIES_TEST_PLURALITY_WARNING
				#ifndef NLC_CATEGORIES_TEST_PLURALITY_WARNING_PLACE_IN_NLC_PREDEFINED_FUNCTION_ADDTOCATEGORYIFPASSSINGULARDEFINITEREFERENCINGTESTS
				#ifdef NLC_CATEGORIES_TEST_PLURALITY_COMMENT
				*currentCodeBlockInTree = createCodeBlockCommentSingleLine(*currentCodeBlockInTree, "Singular definite plurality tests");
				#endif
				NLCcodeblock * lastCodeBlockInTree2 = *currentCodeBlockInTree;
				*currentCodeBlockInTree = createCodeBlockIfHasGreaterThanNumCategoryItem(*currentCodeBlockInTree, parentEntity, genericListAppendName, 1);
				*currentCodeBlockInTree = createCodeBlockPrintWarning(*currentCodeBlockInTree, NLC_CATEGORIES_TEST_PLURALITY_WARNING_MESSAGE);
				*currentCodeBlockInTree = lastCodeBlockInTree2->next;
				#endif
				#endif

				#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
				if(generateContextBlocksVariables->setCodeBlockInTreeAtBaseLevel)
				{
					generateContextBlocksVariables->currentCodeBlockInTreeAtBaseLevel = *currentCodeBlockInTree;
				}
				#endif
				#ifdef NLC_CATEGORIES_TEST_PLURALITY_ENFORCE
				*currentCodeBlockInTree = createCodeBlockIfHasCategoryItem(*currentCodeBlockInTree, parentEntity, false, genericListAppendName);	//added 1j5a
				*currentCodeBlockInTree = createCodeBlockGetBackCategoryEntityList(*currentCodeBlockInTree, parentEntity, genericListAppendName);
				#else
				*currentCodeBlockInTree = createCodeBlockForCategoryList(*currentCodeBlockInTree, parentEntity, genericListAppendName);
				#endif
			}
			else
			{
			#endif
				#ifdef NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY
				if(generateContextBlocksVariables->testNumerosity)
				{
					//test numerosity of parent
					if(parentEntity->hasQuantity)
					{
						#ifdef NLC_CATEGORIES_TEST_PLURALITY_COMMENT
						*currentCodeBlockInTree = createCodeBlockCommentSingleLine(*currentCodeBlockInTree, "numerosity tests (parent)");
						#endif
						*currentCodeBlockInTree = createCodeBlockIfHasGreaterThanOrEqualToNumCategoryItem(*currentCodeBlockInTree, parentEntity, genericListAppendName, parentEntity->quantityNumber);
					}
				}
				#endif

				#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
				if(generateContextBlocksVariables->setCodeBlockInTreeAtBaseLevel)
				{
					generateContextBlocksVariables->currentCodeBlockInTreeAtBaseLevel = *currentCodeBlockInTree;
				}
				#endif
				*currentCodeBlockInTree = createCodeBlockForCategoryList(*currentCodeBlockInTree, parentEntity, genericListAppendName);
			#ifdef NLC_CATEGORIES_TEST_PLURALITY
			}
			#endif

			#ifdef NLC_USE_ADVANCED_REFERENCING
			*currentCodeBlockInTree = createCodeBlockUpdateLastSentenceReferenced(*currentCodeBlockInTree, parentEntity, sentenceIndex);
			#endif
		
		#ifdef NLC_FUNCTIONS_SUPPORT_PLURAL_SUBJECTS_AND_OBJECTS
		}	
		#endif
		
	#ifdef NLC_USE_ADVANCED_REFERENCING_SUPPORT_ALIASES
	}
	#endif
	return contextFound;

}

bool generateContextBlocksSimple(NLCcodeblock ** currentCodeBlockInTree, GIAentityNode * parentEntity, int sentenceIndex, NLCgenerateContextBlocksVariables * generateContextBlocksVariables, bool generatedParentContext, string genericListAppendName)
#else
bool generateContextBlocks(NLCcodeblock ** currentCodeBlockInTree, GIAentityNode * parentEntity, int sentenceIndex, NLCgenerateContextBlocksVariables * generateContextBlocksVariables, bool generatedParentContext, string genericListAppendName)
#endif
{
	bool contextFound = false;
	
	NLCcodeblock * originalCodeBlockInTree = *currentCodeBlockInTree;

	//#ifdef NLC_DEBUG_PARSE_CONTEXT3
	//*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("generateContextBlocksSimple(): ") + parentEntity->entityName);
	//#endif

	#ifndef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN
	#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
	if(generateContextBlocksVariables->setCodeBlockInTreeAtBaseLevel)
	{
		generateContextBlocksVariables->currentCodeBlockInTreeAtBaseLevel = *currentCodeBlockInTree;
	}
	#endif
	#endif
			
	if(!generatedParentContext)
	{
		NLCitem * propertyItem = new NLCitem(parentEntity, NLC_ITEM_TYPE_OBJECT);
		//context property item:
		if(assumedToAlreadyHaveBeenDeclared(parentEntity))
		{
			*currentCodeBlockInTree = createCodeBlockForLocalList(*currentCodeBlockInTree, propertyItem);
			#ifdef NLC_DEBUG_PARSE_CONTEXT3
			*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("finished generateContextBlocksSimple(): 1createCodeBlockForPropertyListLocal: ") + parentEntity->entityName);
			#endif
		}
		else
		{
			*currentCodeBlockInTree = createCodeBlockForPropertyList(*currentCodeBlockInTree, propertyItem);
			#ifdef NLC_DEBUG_PARSE_CONTEXT3
			*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("finished generateContextBlocksSimple(): 2createCodeBlockForPropertyList: ") + parentEntity->entityName);
			#endif
		}
	}

	#ifdef NLC_DEBUG
	cout << "\tgenerateContextBlocks: " << parentEntity->entityName << endl;
	#endif
	//parse the children (properties and conditions) of an undeclared definite parent
	if(!createCodeBlockForStatements(currentCodeBlockInTree, generateInstanceName(parentEntity), parentEntity, sentenceIndex, generateContextBlocksVariables))
	{
		#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
		//if(!generatedParentContext)	//considered adding 1j13b
		//{
		parentEntity->NLCcontextGenerated = true;	//added 1g14b 15-July-2014
		//}		
		#endif
	}
	else
	{
		contextFound = true;
		#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
		parentEntity->NLCcontextGenerated = true;	//added 1g14b 15-July-2014
		#endif
	}

	return contextFound;
}


#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN
bool createCodeBlockForStatementsForDefinitionChildren(NLCcodeblock ** currentCodeBlockInTree, NLCcodeblock ** lastCodeBlockInTree, GIAentityNode* parentInstance, GIAentityNode* parentSubstanceConcept, int sentenceIndex, NLCgenerateContextBlocksVariables * generateContextBlocksVariables, bool generateContext, string genericListAppendName)
{
	bool contextFound = false;
	#ifdef NLC_DEBUG_PARSE_CONTEXT_CHILDREN	
	cout << "\t NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN: createCodeBlockForStatementsForDefinitionChildren(): parentSubstanceConcept = " << parentSubstanceConcept->entityName << endl;		
	#endif
	for(vector<GIAentityConnection*>::iterator reverseDefinitionNodeListIterator = parentSubstanceConcept->entityNodeDefinitionReverseList->begin(); reverseDefinitionNodeListIterator < parentSubstanceConcept->entityNodeDefinitionReverseList->end(); reverseDefinitionNodeListIterator++)
	{
		GIAentityNode* child = (*reverseDefinitionNodeListIterator)->entity;
		if(child != parentInstance)
		{
			if(child->isSubstanceConcept)
			{
				GIAentityNode* childSubstanceConcept = child;
				//recurse; eg "interesting bannanas" in "A yellow bannana is on the table. Interesting bannanas are yellow bannanas. Yellow bannanas are fruit. The fruit is tasty."
				if(createCodeBlockForStatementsForDefinitionChildren(currentCodeBlockInTree, lastCodeBlockInTree, parentInstance, childSubstanceConcept, sentenceIndex, generateContextBlocksVariables, generateContext, genericListAppendName))
				{
					contextFound = true;
				}
			}
			else
			{
				GIAentityNode* childSubstance = child;
				//definition child (e.g. apple)

				//this code is from generateContextBlocksSimple():
				
				NLCitem * propertyItem = new NLCitem(childSubstance, NLC_ITEM_TYPE_OBJECT);
				//context property item:		
				if(assumedToAlreadyHaveBeenDeclared(childSubstance))
				{
					#ifdef NLC_DEBUG_PARSE_CONTEXT_CHILDREN	
					cout << "1 NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN createCodeBlockForLocalList(): assumedToAlreadyHaveBeenDeclared: childSubstance = " << childSubstance->entityName << endl;
					#endif
					*currentCodeBlockInTree = createCodeBlockForLocalList(*currentCodeBlockInTree, propertyItem);
				}
				else
				{
					#ifdef NLC_DEBUG_PARSE_CONTEXT_CHILDREN	
					cout << "2 NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN createCodeBlockForPropertyList(): !assumedToAlreadyHaveBeenDeclared: childSubstance = " << childSubstance->entityName << endl;
					#endif
					*currentCodeBlockInTree = createCodeBlockForPropertyList(*currentCodeBlockInTree, propertyItem);
				}	

				if(generateContext)
				{
					if(createCodeBlockForStatements(currentCodeBlockInTree, generateInstanceName(childSubstance), parentInstance, sentenceIndex, generateContextBlocksVariables))
					{
						contextFound = true;
					}
				}
				else
				{
					contextFound = true;
				}
				
				addPropertyToCategoryList(currentCodeBlockInTree, parentInstance, childSubstance, genericListAppendName, generateContextBlocksVariables);
				
				*currentCodeBlockInTree = getLastCodeBlockInLevel(*lastCodeBlockInTree);
				*lastCodeBlockInTree = *currentCodeBlockInTree;
				#ifdef NLC_DEBUG_PARSE_CONTEXT_CHILDREN	
				cout << "3 NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN createCodeBlockForStatements(): contextFound: parentInstance = " << parentInstance->entityName << ", childSubstance = " << childSubstance << endl;
				#endif
			}
		}
	}
	return contextFound;
}

bool addPropertyToCategoryList(NLCcodeblock ** currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* propertyEntity, string genericListAppendName, NLCgenerateContextBlocksVariables * generateContextBlocksVariables)
{
	bool result = true;
	
	#ifdef NLC_USE_ADVANCED_REFERENCING
	if((entity->grammaticalNumber == GRAMMATICAL_NUMBER_SINGULAR) && assumedToAlreadyHaveBeenDeclared(entity))	//added assumedToAlreadyHaveBeenDeclared(parentEntity) criteria 1j15a
	{
		#ifdef NLC_USE_ADVANCED_REFERENCING_COMMENT
		*currentCodeBlockInTree = createCodeBlockCommentSingleLine(*currentCodeBlockInTree, "Singular definite referencing tests");
		#endif
		*currentCodeBlockInTree = createCodeBlockAddEntityToCategoryListCheckLastSentenceReferencedSingularExecuteFunction(*currentCodeBlockInTree, entity, propertyEntity, genericListAppendName);
	}
	else
	{
		#ifdef NLC_USE_ADVANCED_REFERENCING_COMMENT
		*currentCodeBlockInTree = createCodeBlockCommentSingleLine(*currentCodeBlockInTree, "Plural definite referencing tests");
		#endif
		*currentCodeBlockInTree = createCodeBlockAddEntityToCategoryListCheckLastSentenceReferencedPluralExecuteFunction(*currentCodeBlockInTree, entity, propertyEntity, genericListAppendName);
	}
	#else
	*currentCodeBlockInTree = createCodeBlockAddEntityToCategoryList(*currentCodeBlockInTree, entity, propertyEntity, genericListAppendName);
	#endif

	#ifdef NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY_CHILDREN
	if(generateContextBlocksVariables->testNumerosity)
	{
		string categoryListPropertyCountVariableName = generateCategoryListPropertyCountVariableName(entity);
		*currentCodeBlockInTree = createCodeBlockIncrementIntVar(*currentCodeBlockInTree, categoryListPropertyCountVariableName);
	}
	#endif

	return result;
}	
#endif

bool createCodeBlockForStatements(NLCcodeblock ** currentCodeBlockInTree, string parentInstanceName, GIAentityNode* entity, int sentenceIndex, NLCgenerateContextBlocksVariables * generateContextBlocksVariables)
{
	bool result = false;

	//if object near a red car / if object has a red car (if object has a car which is red)
	//if(item->has(property) && item->has(property1) etc..){
	if(createCodeBlockForConnectionType(GIA_ENTITY_VECTOR_CONNECTION_TYPE_PROPERTIES, currentCodeBlockInTree, parentInstanceName, entity, sentenceIndex, generateContextBlocksVariables))
	{
		result = true;
	}

	//if object near a car that is behind the driveway / if object has a car that is near the house
	//if(item > 3){		/	if(greaterthan(item, 3)){
	if(createCodeBlockForConnectionType(GIA_ENTITY_VECTOR_CONNECTION_TYPE_CONDITIONS, currentCodeBlockInTree, parentInstanceName, entity, sentenceIndex, generateContextBlocksVariables))
	{
		result = true;
	}
	
	#ifdef NLC_RECORD_ACTION_HISTORY
	//if object near a car that drives /if object has a car that drives
	if(createCodeBlockForConnectionType(GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTIONS, currentCodeBlockInTree, parentInstanceName, entity, sentenceIndex, generateContextBlocksVariables))
	{
		result = true;
	}

	//if object near a car that is towed by a truck / if object has a car that is towed by a truck
	if(createCodeBlockForConnectionType(GIA_ENTITY_VECTOR_CONNECTION_TYPE_INCOMING_ACTIONS, currentCodeBlockInTree, parentInstanceName, entity, sentenceIndex, generateContextBlocksVariables))
	{
		result = true;
	}
	#endif
	
	/*
	//if object near car that is a flyingCar
	currentCodeBlockInTree = createCodeBlockIfHasDefinition(currentCodeBlockInTree, item, entity, sentenceIndex);

	//if object near Tom's carparentInstanceName
	currentCodeBlockInTree = createCodeBlockIfHasPropertyOwner(currentCodeBlockInTree, item, entity, sentenceIndex);
	*/
	return result;
}
		
bool createCodeBlockForConnectionType(int connectionType, NLCcodeblock ** currentCodeBlockInTree, string parentInstanceName, GIAentityNode * entity, int sentenceIndex, NLCgenerateContextBlocksVariables * generateContextBlocksVariables)
{
	bool result = false;
	
	for(vector<GIAentityConnection*>::iterator targetNodeListIterator = entity->entityVectorConnectionsArray[connectionType].begin(); targetNodeListIterator < entity->entityVectorConnectionsArray[connectionType].end(); targetNodeListIterator++)
	{
		GIAentityConnection * targetConnection = (*targetNodeListIterator);
		#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
		#ifndef GIA_DISABLE_CROSS_SENTENCE_REFERENCING
		if((targetConnection->NLCparsedForCodeBlocks) || !(generateContextBlocksVariables->onlyGenerateContextBlocksIfConnectionsParsedForNLC) || (targetConnection->isReference) || ((generateContextBlocksVariables->generateContextBlocksIfSameReferenceSet) && (targetConnection->sameReferenceSet)))	//added option 1g13b/15-July-2014	//added option 1i2a 20-August-2014	//added option 1i3d 21-August-2014	//NB isReference check is probably redundant given sameReferenceSet check
		#else
		if((targetConnection->NLCparsedForCodeBlocks) || !(generateContextBlocksVariables->onlyGenerateContextBlocksIfConnectionsParsedForNLC) || ((generateContextBlocksVariables->generateContextBlocksIfSameReferenceSet) && (targetConnection->sameReferenceSet)))	//added option 1g13b/15-July-2014	//added option 1i2a 20-August-2014	//added option 1i3d 21-August-2014
		#endif
		{
		#endif
			GIAentityNode* targetEntity = targetConnection->entity;
			if(checkSentenceIndexParsingCodeBlocks(targetEntity, targetConnection, sentenceIndex, false))	//changed from true to false 1e5b	//generateContextBlocksVariables->checkSameSentenceConnection
			{//only write conditions that are explicated in current sentence
			
				#ifdef NLC_DEBUG
				cout << "createCodeBlockForConnectionType(): " << targetEntity->entityName << endl;
				#endif
				#ifdef NLC_DEBUG_PARSE_CONTEXT
				cout << "createCodeBlockForConnectionType: " << targetEntity->entityName << endl;
				cout << "\t targetConnection->NLCparsedForCodeBlocks: " << targetConnection->NLCparsedForCodeBlocks << endl;
				cout << "\t generateContextBlocksVariables->onlyGenerateContextBlocksIfConnectionsParsedForNLC: " << generateContextBlocksVariables->onlyGenerateContextBlocksIfConnectionsParsedForNLC << endl;
				#ifndef GIA_DISABLE_CROSS_SENTENCE_REFERENCING
				cout << "\t targetConnection->isReference: " << targetConnection->isReference << endl;
				#endif
				#endif
				#ifdef NLC_DEBUG_PARSE_CONTEXT3
				*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("createCodeBlockForConnectionType(): ") + entity->entityName + string(" ") + targetEntity->entityName);
				#endif
				
				targetConnection->NLCparsedForCodeBlocks = true;
				#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS_ADVANCED
				bool conjunctionConditionConnectionFound = hasConjunctionConditionConnection(targetEntity, generateContextBlocksVariables->primaryEntityInLogicalConditionConjunctionSubset, generateContextBlocksVariables->logicalConditionConjunctionIndex, &(generateContextBlocksVariables->foundLogicalConditionConjunction));	//dont need to test for mismatched logicalConditionConjunctionIndex; it is just for debugging
				if(!conjunctionConditionConnectionFound)
				{
				#endif
					bool resultTemp = false;
					if(connectionType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_PROPERTIES)
					{
						if(createCodeBlockForGivenProperty(currentCodeBlockInTree, parentInstanceName, targetEntity, sentenceIndex, generateContextBlocksVariables))
						{
							resultTemp = true;
							#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
							if(targetConnection->negative)
							{
								generateContextBlocksVariables->negativeDetectedInContextBlocks = true;
							}
							#endif
						}
					}
					else if(connectionType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_CONDITIONS)
					{
						if(createCodeBlockForGivenCondition(currentCodeBlockInTree, parentInstanceName, targetEntity, sentenceIndex, generateContextBlocksVariables))
						{
							resultTemp = true;
						}
					}
					#ifdef NLC_RECORD_ACTION_HISTORY
					else if(connectionType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTIONS)
					{
						if(createCodeBlockForGivenAction(currentCodeBlockInTree, parentInstanceName, targetEntity, sentenceIndex, generateContextBlocksVariables))
						{
							resultTemp = true;
						}
					}
					else if(connectionType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_INCOMING_ACTIONS)
					{
						if(createCodeBlockForGivenActionIncoming(currentCodeBlockInTree, parentInstanceName, targetEntity, sentenceIndex, generateContextBlocksVariables))
						{
							resultTemp = true;
						}
					}
					#endif
					if(resultTemp)
					{
						result = true;
						#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS_ADVANCED
						targetEntity->NLClogicalConditionConjunctionIndex = generateContextBlocksVariables->logicalConditionConjunctionIndex;
						#endif
					}					
				#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS_ADVANCED
				}
				#endif
			}
		#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
		}
		#endif
	}
	return result;
}
bool createCodeBlockForGivenProperty(NLCcodeblock ** currentCodeBlockInTree, string parentInstanceName, GIAentityNode* propertyEntity, int sentenceIndex, NLCgenerateContextBlocksVariables * generateContextBlocksVariables)
{
	bool result = true;
	
	#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
	propertyEntity->NLCcontextGenerated = true;	//added 1g14b 15-July-2014
	#endif
					
	NLCitem * propertyItem = new NLCitem(propertyEntity, NLC_ITEM_TYPE_OBJECT);

	propertyItem->context.push_back(parentInstanceName);
	
	#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS_BASIC
	if(logicalOperation == NLC_LOGICAL_CONDITION_OPERATIONS_FOR)
	{
		*currentCodeBlockInTree = createCodeBlockForPropertyList(*currentCodeBlockInTree, propertyItem);
	}
	else if(logicalOperation == NLC_LOGICAL_CONDITION_OPERATIONS_IF)
	{
		*currentCodeBlockInTree = createCodeBlockIfHasProperty(*currentCodeBlockInTree, propertyItem, generateContextBlocksVariables->negative);
	}
	else if(logicalOperation == NLC_LOGICAL_CONDITION_OPERATIONS_WHILE)
	{
		*currentCodeBlockInTree = createCodeBlockWhileHasProperty(*currentCodeBlockInTree, propertyItem, generateContextBlocksVariables->negative);
	}
	#else
	*currentCodeBlockInTree = createCodeBlockForPropertyList(*currentCodeBlockInTree, propertyItem);	
	#endif

	#ifdef NLC_DEBUG
	//cout << "createCodeBlockForGivenProperty(): propertyEntity = " << propertyEntity->entityName << endl;
	//*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, propertyEntity->entityName);
	#endif
	
	createCodeBlockForStatements(currentCodeBlockInTree, propertyItem->instanceName, propertyEntity, sentenceIndex, generateContextBlocksVariables);

	#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
	if(propertyEntity->isSubstanceQuality)
	{
		if(propertyEntity->negative)
		{
			//cout << "propertyEntity->negative: propertyEntity->entityName = " << propertyEntity->entityName << endl;
			generateContextBlocksVariables->negativeDetectedInContextBlocks = true;
		}
	}
	#endif
	#ifdef NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY_CHILDREN
	if(generateContextBlocksVariables->testNumerosity)
	{
		if(propertyEntity->hasQuantity)
		{
			generateContextBlocksVariables->childQuantity = propertyEntity->quantityNumber;
			//cout << "generateContextBlocksVariables->childQuantity = " << generateContextBlocksVariables->childQuantity << endl;
		}
	}
	#endif
					
	return result;
}

bool createCodeBlockForGivenCondition(NLCcodeblock ** currentCodeBlockInTree, string parentInstanceName, GIAentityNode* conditionEntity, int sentenceIndex, NLCgenerateContextBlocksVariables * generateContextBlocksVariables)
{
	bool result = false;

	#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS_ADVANCED
	bool conjunctionConditionFound = textInTextArray(conditionEntity->entityName, entityCoordinatingConjunctionArray, ENTITY_COORDINATINGCONJUNCTION_ARRAY_NUMBER_OF_TYPES);
	if(!conjunctionConditionFound)
	{//do not parse conjunction conditions
	#endif	
		if(!(conditionEntity->conditionObjectEntity->empty()))
		{	
			result = true;	
			GIAentityNode * conditionObject = (conditionEntity->conditionObjectEntity->back())->entity;

			#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
			conditionObject->NLCcontextGenerated = true;	//added 1g14b 15-July-2014
			#endif
					
			NLCitem * conditionItem = new NLCitem(conditionEntity, NLC_ITEM_TYPE_OBJECT);
			NLCitem * conditionObjectItem = new NLCitem(conditionObject, NLC_ITEM_TYPE_OBJECT);

			conditionItem->context.push_back(parentInstanceName);
			conditionObjectItem->context.push_back(parentInstanceName);	//redundant

			#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS_BASIC
			if(logicalOperation == NLC_LOGICAL_CONDITION_OPERATIONS_FOR)
			{
				*currentCodeBlockInTree = createCodeBlockForConditionList(*currentCodeBlockInTree, conditionItem, conditionObjectItem);
			}
			else if(logicalOperation == NLC_LOGICAL_CONDITION_OPERATIONS_IF)
			{
				*currentCodeBlockInTree = createCodeBlockIfHasCondition(*currentCodeBlockInTree, conditionItem, conditionObjectItem, generateContextBlocksVariables->negative);
			}
			else if(logicalOperation == NLC_LOGICAL_CONDITION_OPERATIONS_WHILE)
			{
				*currentCodeBlockInTree = createCodeBlockWhileHasCondition(*currentCodeBlockInTree, conditionItem, conditionObjectItem, generateContextBlocksVariables->negative);
			}
			#else
			*currentCodeBlockInTree = createCodeBlockForConditionList(*currentCodeBlockInTree, conditionItem, conditionObjectItem);
			#endif

			#ifdef NLC_DEBUG
			//cout << "createCodeBlockForGivenCondition(): " << conditionObjectItem->instanceName << endl;
			#endif
			
			createCodeBlockForStatements(currentCodeBlockInTree, conditionObjectItem->instanceName, conditionObject, sentenceIndex, generateContextBlocksVariables);
			
			#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
			if(conditionEntity->negative)
			{
				generateContextBlocksVariables->negativeDetectedInContextBlocks = true;
			}
			#endif
			#ifdef NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY_CHILDREN
			if(generateContextBlocksVariables->testNumerosity)
			{
				if(conditionObject->hasQuantity)
				{
					generateContextBlocksVariables->childQuantity = conditionObject->quantityNumber;
				}
			}
			#endif
		}
		else
		{
			result = false;
			cout << "error createCodeBlockForGivenCondition(): condition does not have object" << endl;
		}
	#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS_ADVANCED
	}
	else
	{
		generateContextBlocksVariables->foundLogicalConditionConjunction = conditionEntity;
	}
	#endif
	
	return result;
}

#ifdef NLC_RECORD_ACTION_HISTORY
bool createCodeBlockForGivenAction(NLCcodeblock ** currentCodeBlockInTree, string parentInstanceName, GIAentityNode* actionEntity, int sentenceIndex, NLCgenerateContextBlocksVariables * generateContextBlocksVariables)
{
	bool result = false;

	if(!(actionEntity->NLCcontextGeneratedTemp))
	{
		result = true;

		#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
		actionEntity->NLCcontextGenerated = true;
		#endif

		NLCitem * actionItem = new NLCitem(actionEntity, NLC_ITEM_TYPE_OBJECT);
		actionItem->context.push_back(parentInstanceName);
		*currentCodeBlockInTree = createCodeBlockForActionList(*currentCodeBlockInTree, actionItem);	

		#ifdef NLC_DEBUG
		//cout << "createCodeBlockForGivenAction(): " << actionItem->instanceName << endl;
		#endif
		
		bool hasActionObject = false;
		if(!(actionEntity->actionObjectEntity->empty()))
		{
			GIAentityNode * actionObject = (actionEntity->actionObjectEntity->back())->entity;
			#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
			actionObject->NLCcontextGenerated = true;
			#endif

			NLCitem * actionObjectItem = new NLCitem(actionObject, NLC_ITEM_TYPE_OBJECT);
			hasActionObject = true;
			actionObjectItem->context.push_back(actionItem->instanceName);
			*currentCodeBlockInTree = createCodeBlockForActionObjectList(*currentCodeBlockInTree, actionObjectItem);

			actionEntity->NLCcontextGeneratedTemp = true;
			createCodeBlockForStatements(currentCodeBlockInTree, actionItem->instanceName, actionObject, sentenceIndex, generateContextBlocksVariables);
			actionEntity->NLCcontextGeneratedTemp = false;
		}

		#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
		if(actionEntity->negative)
		{
			generateContextBlocksVariables->negativeDetectedInContextBlocks = true;
		}
		#endif
	}

	return result;
}

bool createCodeBlockForGivenActionIncoming(NLCcodeblock ** currentCodeBlockInTree, string parentInstanceName, GIAentityNode* actionEntity, int sentenceIndex, NLCgenerateContextBlocksVariables * generateContextBlocksVariables)
{
	bool result = false;

	if(!(actionEntity->NLCcontextGeneratedTemp))
	{
		result = true;
		
		#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
		actionEntity->NLCcontextGenerated = true;
		#endif

		NLCitem * actionItem = new NLCitem(actionEntity, NLC_ITEM_TYPE_OBJECT);
		actionItem->context.push_back(parentInstanceName);
		*currentCodeBlockInTree = createCodeBlockForActionIncomingList(*currentCodeBlockInTree, actionItem);	

		#ifdef NLC_DEBUG
		//cout << "createCodeBlockForGivenActionIncoming(): " << actionItem->instanceName << endl;
		#endif
		
		bool hasActionSubject = false;
		if(!(actionEntity->actionSubjectEntity->empty()))
		{
			GIAentityNode * actionSubject = (actionEntity->actionSubjectEntity->back())->entity;
			#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
			actionSubject->NLCcontextGenerated = true;
			#endif
		
			NLCitem * actionSubjectItem = new NLCitem(actionSubject, NLC_ITEM_TYPE_OBJECT);
			hasActionSubject = true;
			actionSubjectItem->context.push_back(actionItem->instanceName);
			*currentCodeBlockInTree = createCodeBlockForActionSubjectList(*currentCodeBlockInTree, actionSubjectItem);

			actionEntity->NLCcontextGeneratedTemp = true;
			createCodeBlockForStatements(currentCodeBlockInTree, actionItem->instanceName, actionSubject, sentenceIndex, generateContextBlocksVariables);
			actionEntity->NLCcontextGeneratedTemp = false;
		}

		#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
		if(actionEntity->negative)
		{
			generateContextBlocksVariables->negativeDetectedInContextBlocks = true;
		}
		#endif
	}
							
	return result;
}
#endif

#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS_ADVANCED
bool hasConjunctionConditionConnection(GIAentityNode * conditionEntity, GIAentityNode * primaryEntityInLogicalConditionConjunctionSubset, int logicalConditionConjunctionIndex, GIAentityNode ** foundLogicalConditionConjunction)	//dont need to test for mismatched logicalConditionConjunctionIndex; it is just for debugging
{
	bool conjunctionConditionConnectionFound = false;

	for(vector<GIAentityConnection*>::iterator conditionNodeListIterator = conditionEntity->conditionNodeList->begin(); conditionNodeListIterator < conditionEntity->conditionNodeList->end(); conditionNodeListIterator++)
	{
		GIAentityConnection * conditionConnection = (*conditionNodeListIterator);
		GIAentityNode* conditionEntity2 = conditionConnection->entity;
		bool conjunctionConditionFound = textInTextArray(conditionEntity2->entityName, entityCoordinatingConjunctionArray, ENTITY_COORDINATINGCONJUNCTION_ARRAY_NUMBER_OF_TYPES);
		if(conjunctionConditionFound)
		{
			if(conditionEntity != primaryEntityInLogicalConditionConjunctionSubset)
			{//ignore primaryEntityInLogicalConditionConjunctionSubset
				if(conditionEntity2->NLCconjunctionCondition)
				{//condition added 1g6h; do not parse nodes with conjunction condition connections if the conjunction condition has already been parsed by checkConditionForLogicalCondition()
					conjunctionConditionConnectionFound = true;
				}
			}
			//if(conditionEntity != primaryEntityInLogicalConditionConjunctionSubset) {//removed NLC 1g6j - 10 July 2014
			if(!(conditionEntity2->NLCconjunctionCondition))
			{//do not reparse same conjunction conditions - added NLC 1g7b/11 July 2014
				if(*foundLogicalConditionConjunction == NULL)
				{//do not overwrite foundLogicalConditionConjunction; always take the first conjunction in subset as the one to parse next - added NLC 1g6j/10 July 2014
					*foundLogicalConditionConjunction = conditionEntity2;
				}
			}
			//}
		}
	}
	if(conditionEntity != primaryEntityInLogicalConditionConjunctionSubset)
	{
		for(vector<GIAentityConnection*>::iterator conditionNodeListIterator = conditionEntity->incomingConditionNodeList->begin(); conditionNodeListIterator < conditionEntity->incomingConditionNodeList->end(); conditionNodeListIterator++)
		{
			GIAentityConnection * conditionConnection = (*conditionNodeListIterator);
			GIAentityNode* conditionEntity2 = conditionConnection->entity;
			bool conjunctionConditionFound = textInTextArray(conditionEntity2->entityName, entityCoordinatingConjunctionArray, ENTITY_COORDINATINGCONJUNCTION_ARRAY_NUMBER_OF_TYPES);
			if(conjunctionConditionFound)
			{
				conjunctionConditionConnectionFound = true;
				//*foundLogicalConditionConjunction = conditionEntity2;	//NB only parse conjunction conditions in forwards direction
			}
		}
	}

	/*
	//for debugging only:
	if(!conjunctionConditionConnectionFound)
	{
		if((conditionEntity->NLClogicalConditionConjunctionIndex != logicalConditionConjunctionIndex) && (conditionEntity->NLClogicalConditionConjunctionIndex != INT_DEFAULT_VALUE))
		{
			cout << "hasConjunctionConditionConnection() error: child of primaryEntityInLogicalConditionConjunctionSubset has been declared as pertaining to a different logicalConditionConjunctionSubset - is this a shared context?" << endl;
		}
	}
	*/

	return conjunctionConditionConnectionFound;
}
#endif

















#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
bool generateCodeBlocksObjectInitialisationsForEntity(NLCcodeblock ** currentCodeBlockInTree, GIAentityNode * entity, int sentenceIndex)
{
	bool result = true;

	#ifdef NLC_DEBUG_PARSE_CONTEXT
	cout << "\ngenerateCodeBlocksPart4objectInitialisations(): sentenceIndex = " << sentenceIndex << endl;
	cout << "\tentity->entityName = " << entity->entityName << endl;
	#endif

	NLCcodeblock * originalCodeBlockInLevel = *currentCodeBlockInTree;

	#ifdef NLC_DEBUG_PARSE_CONTEXT
	cout << "generateCodeBlocksObjectInitialisationsForEntity: getParent()" << endl;
	#endif
	GIAentityNode * parentEntity = getParent(entity, sentenceIndex, true);	//parse condition parents in accordance with original generateCodeBlocksPart4objectInitialisations implementation
	if(!checkSpecialCaseEntity(parentEntity, false))
	{
		#ifdef NLC_DEBUG_PARSE_CONTEXT
		cout << "\tentity = " << entity->entityName << endl;
		cout << "\tparentEntity = " << parentEntity->entityName << endl;
		cout << "generateCodeBlocksObjectInitialisationsForEntity: generateParentInitialisationCodeBlockWithChecks()" << endl;
		#endif
		if(!generateParentInitialisationCodeBlockWithChecks(currentCodeBlockInTree, parentEntity, sentenceIndex, false))
		{
			#ifdef NLC_DEBUG_PARSE_CONTEXT
			cout << "\tfail generateParentInitialisationCodeBlockWithChecks" << endl;
			cout << "generateCodeBlocksObjectInitialisationsForEntity: generateContextBlocksAndGenerateObjectInitialisationsBasedOnPropertiesAndConditions()" << endl;
			#endif
			if(!generateObjectInitialisationsBasedOnPropertiesAndConditions(parentEntity, currentCodeBlockInTree , sentenceIndex, "", "", true, false))
			{
				*currentCodeBlockInTree = originalCodeBlockInLevel;
				clearCodeBlock(originalCodeBlockInLevel);

				#ifdef NLC_DEBUG_PARSE_CONTEXT
				cout << "\tfail generateContextBlocksAndGenerateObjectInitialisationsBasedOnPropertiesAndConditions" << endl;
				#endif
			}
			else
			{
				*currentCodeBlockInTree = getLastCodeBlockInLevel(originalCodeBlockInLevel);
				#ifdef NLC_DEBUG_PARSE_CONTEXT
				cout << "\tpass generateContextBlocksAndGenerateObjectInitialisationsBasedOnPropertiesAndConditions" << endl;
				#endif
			}
		}
		else
		{
			#ifdef NLC_DEBUG_PARSE_CONTEXT
			cout << "\tpass generateParentInitialisationCodeBlockWithChecks" << endl;
			#endif
		}
	}
	return result;
}

#endif

















bool getParentAndGenerateParentInitialisationCodeBlock(NLCcodeblock ** currentCodeBlockInTree, GIAentityNode * entity, int sentenceIndex, bool parseConditionParents, bool parseLogicalConditions)
{
	bool result = false;
	GIAentityNode * parentEntity = getParent(entity, sentenceIndex, parseConditionParents);
	#ifdef NLC_DEBUG
	//cout << "parentEntity = " << parentEntity->entityName << endl;
	#endif

	result = generateParentInitialisationCodeBlockWithChecks(currentCodeBlockInTree, parentEntity, sentenceIndex, parseLogicalConditions);
	return result;
}

bool generateParentInitialisationCodeBlockWithChecks(NLCcodeblock ** currentCodeBlockInTree, GIAentityNode * parentEntity, int sentenceIndex, bool parseLogicalConditions)
{
	bool result = false;

	//cout << "generateParentInitialisationCodeBlockWithChecks: entity->NLCparsedForlogicalConditionOperations = " << entity->NLCparsedForlogicalConditionOperations << endl;
	#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
	if(!(parentEntity->NLCparsedForlogicalConditionOperations) || parseLogicalConditions)	//CHECKTHIS; change from !(entity->NLCparsedForlogicalConditionOperations) to !(parentEntity->NLCparsedForlogicalConditionOperations) 1g14a 15-July-2014
	{
	#endif
		//moved here 1e8a (out of generateObjectInitialisationsBasedOnPropertiesAndConditions)
		//added 1e6c: eg A chicken's hat has a bike. / A blue dog has a bike.
		if(!(parentEntity->isConcept) && !(parentEntity->isAction) && !(parentEntity->isSubstanceConcept) && !(parentEntity->isActionConcept))
		{
			if(!(parentEntity->NLCparsedForCodeBlocks))	// && !(entity->parsedForNLCcodeBlocksActionRound)
			{
				if(!assumedToAlreadyHaveBeenDeclared(parentEntity))
				{
					#ifndef NLC_DEFINE_LOCAL_VARIABLES_FOR_ALL_INDEFINATE_ENTITIES
					if(checkSentenceIndexParsingCodeBlocks(parentEntity, sentenceIndex, false))	//this is redundant with NLC_DEFINE_LOCAL_VARIABLES_FOR_ALL_INDEFINATE_ENTITIES
					{
					#endif
						#ifdef NLC_VERIFY_CONNECTIONS_SENTENCE_INDEX
						if(parentEntity->sentenceIndexTemp == sentenceIndex)	//ie "wasReference" is not a sufficient condition to initialise parent
						{
						#endif
							#ifdef NLC_RECORD_ACTION_HISTORY_GENERALISABLE
							if(!(parentEntity->NLCcontextGenerated))	//added 1l3b
							{
							#endif
								#ifdef NLC_DEBUG
								//cout << "generateParentInitialisationCodeBlockWithChecks(): generateParentInitialisationCodeBlock: parentEntity = " << parentEntity->entityName << endl;
								#endif
								generateParentInitialisationCodeBlock(currentCodeBlockInTree, parentEntity, sentenceIndex);
								result = true;
							#ifdef NLC_RECORD_ACTION_HISTORY_GENERALISABLE
							}		
							#endif								
						#ifdef NLC_VERIFY_CONNECTIONS_SENTENCE_INDEX
						}
						#endif
					#ifndef NLC_DEFINE_LOCAL_VARIABLES_FOR_ALL_INDEFINATE_ENTITIES
					}
					#endif
				}
			}
		}

	#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
	}
	#endif

	return result;
}

bool generateParentInitialisationCodeBlock(NLCcodeblock ** currentCodeBlockInTree, GIAentityNode * parentEntity, int sentenceIndex)
{
	bool performedAtLeastParentObjectInitialisation = false;
	
	#ifdef NLC_DEBUG
	cout << "createCodeBlocksCreateNewLocalListVariable: " << parentEntity->entityName << endl;
	#endif
	#ifdef NLC_DEBUG_PARSE_CONTEXT3
	*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("generateParentInitialisationCodeBlockWithChecks(): ") + parentEntity->entityName);
	#endif
	
	*currentCodeBlockInTree = createCodeBlocksCreateNewLocalListVariable(*currentCodeBlockInTree, parentEntity, sentenceIndex);

	parentEntity->NLCparsedForCodeBlocks = true;
	parentEntity->NLClocalListVariableHasBeenInitialised = true;
	//cout << "createCodeBlocksCreateNewLocalListVariable: " << parentEntity->entityName << endl;

	#ifdef GIA_TRANSLATOR_DREAM_MODE_LINK_SPECIFIC_CONCEPTS_AND_ACTIONS
	//Part 2b: generate object initialisations based on substance concepts (class inheritance)
	generateObjectInitialisationsBasedOnSubstanceConcepts(parentEntity, currentCodeBlockInTree, sentenceIndex, true);
	#endif

	#ifdef NLC_DEBUG
	cout << "\tgenerateObjectInitialisationsBasedOnPropertiesAndConditions:" << parentEntity->entityName << endl;
	cout << "sentenceIndex = " << sentenceIndex << endl;
	#endif

	NLCcodeblock * lastCodeBlockInTree = *currentCodeBlockInTree;
	performedAtLeastParentObjectInitialisation = generateObjectInitialisationsBasedOnPropertiesAndConditions(parentEntity, currentCodeBlockInTree, sentenceIndex, "", "", false, false);
	
	*currentCodeBlockInTree = lastCodeBlockInTree;
	if(performedAtLeastParentObjectInitialisation)
	{
		*currentCodeBlockInTree = getLastCodeBlockInLevel(*currentCodeBlockInTree);
	}
	else
	{
		clearCodeBlock(*currentCodeBlockInTree);
	}
			
	return performedAtLeastParentObjectInitialisation;
}






GIAentityNode * getParent(GIAentityNode * currentEntity, int sentenceIndex, bool parseConditionParents)
{
	GIAentityNode * parentEntityNew = currentEntity;
	
	bool foundParentProperty = false;
	for(vector<GIAentityConnection*>::iterator propertyNodeListIterator = currentEntity->propertyNodeReverseList->begin(); propertyNodeListIterator < currentEntity->propertyNodeReverseList->end(); propertyNodeListIterator++)
	{
		GIAentityConnection * parentConnection = *propertyNodeListIterator;
		GIAentityNode * parentEntity = parentConnection->entity;
		
		#ifdef NLC_DEFINE_LOCAL_VARIABLES_FOR_ALL_INDEFINATE_ENTITIES
		if(checkSentenceIndexParsingCodeBlocks(parentEntity, parentConnection, sentenceIndex, false))	//NB will parse references to entities in previous sentence
		#else
		if(checkSentenceIndexParsingCodeBlocks(parentEntity, parentConnection, sentenceIndex, false) || parentEntity->NLCparsedForCodeBlocks)
		#endif
		{
			parentEntityNew = getParent(parentEntity, sentenceIndex, parseConditionParents);
		}
		foundParentProperty = true;

	}
	if(!foundParentProperty && parseConditionParents)
	{//added 1e9a
		for(vector<GIAentityConnection*>::iterator conditionNodeListIterator = currentEntity->incomingConditionNodeList->begin(); conditionNodeListIterator < currentEntity->incomingConditionNodeList->end(); conditionNodeListIterator++)
		{
			GIAentityConnection * conditionConnection = *conditionNodeListIterator;
			GIAentityNode * conditionEntity = conditionConnection->entity;

			bool foundConditionSubject = false;
			GIAentityNode * conditionSubject = NULL;
			if(!(conditionEntity->conditionSubjectEntity->empty()))
			{
				conditionSubject = (conditionEntity->conditionSubjectEntity->back())->entity;

				foundConditionSubject = true;

				#ifdef NLC_DEFINE_LOCAL_VARIABLES_FOR_ALL_INDEFINATE_ENTITIES
				if(checkSentenceIndexParsingCodeBlocks(conditionSubject, conditionConnection, sentenceIndex, false))	//NB will parse references to entities in previous sentence
				#else
				if(checkSentenceIndexParsingCodeBlocks(conditionSubject, conditionConnection, sentenceIndex, false) || conditionSubject->NLCparsedForCodeBlocks)
				#endif
				{
					parentEntityNew = getParent(conditionSubject, sentenceIndex, parseConditionParents);
				}
			}
		}
	}

	return parentEntityNew;
}

bool getParentAndGenerateContextBlocks(NLCcodeblock ** currentCodeBlockInTree, GIAentityNode * currentEntity, int sentenceIndex, NLCgenerateContextBlocksVariables * generateContextBlocksVariables, bool parseConditionParents)
{
	GIAentityNode * parentEntity = getParent(currentEntity, sentenceIndex, parseConditionParents);

	bool generatedContextBlocks = generateContextBlocks(currentCodeBlockInTree, parentEntity, sentenceIndex, generateContextBlocksVariables, false, NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION);

	return generatedContextBlocks;

}






//added recursion 1e8a
//onlyGenerateContextBlocksIfContextNotGeneratedForNLC removed 1i3b

bool generateObjectInitialisationsBasedOnPropertiesAndConditions(GIAentityNode * entity, NLCcodeblock ** currentCodeBlockInTree, int sentenceIndex, string parentName, string parentConditionName, bool generateParentContextTopLevel, bool generateParentContextPassThrough)
{
	#ifdef NLC_DEBUG
	//cout << "generateObjectInitialisationsBasedOnPropertiesAndConditions(): entity = " << entity->entityName << endl;
	//cout << "parentName = " << parentName << endl;
	#endif
				
	#ifdef NLC_DEBUG_PARSE_CONTEXT3
	string generateParentContextStringTemp = "false";
	if(generateParentContextTopLevel)
	{
		generateParentContextStringTemp = "true";
	}
	*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("generateObjectInitialisationsBasedOnPropertiesAndConditions(): ") + entity->entityName + ", generateParentContextTopLevel = " + generateParentContextStringTemp);
	#endif

	#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
	//new implementation: only create context for parent (ie for parent entities...) at start of each generateObjectInitialisationsBasedOnPropertiesAndConditions() if a, b or c;
	//a) first call to generateObjectInitialisationsBasedOnPropertiesAndConditions;
	//added 1i8a->1i8c, moved 1i11d
	if(generateParentContextTopLevel)
	{	
		#ifdef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES	//ie #ifndef GIA_DISABLE_CROSS_SENTENCE_REFERENCING
		if(!(entity->isSubstanceQuality))	//this is required because referenced entities may have a connection to a parent defined in a preceeding sentence, yet generateObjectInitialisationsBasedOnPropertiesAndConditions is still executed on these entities (because they are tagged as wasReference and are accepted by checkSentenceIndexParsingCodeBlocks themselves)
		{
		#endif	
			#ifdef NLC_DEBUG
			cout << "generateObjectInitialisationsBasedOnPropertiesAndConditions(): a) generateContextForChildEntity(): " << entity->entityName << endl;
			#endif
		
			if(generateContextForChildEntity(NULL, entity, currentCodeBlockInTree, sentenceIndex, true))
			{
				//cout << "generateContextForChildEntity pass: entity = " << entity->entityName << endl;
			}
			else
			{
				cout << "generateObjectInitialisationsBasedOnPropertiesAndConditions() error: generateParentContextTopLevel && !assumedToAlreadyHaveBeenDeclared: entity = " << entity->entityName << ", sentenceIndex = " << sentenceIndex << endl;
				exit(0);
			}
		#ifdef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES	//ie #ifndef GIA_DISABLE_CROSS_SENTENCE_REFERENCING
		}
		else
		{
			/*
			eg 1 A red dog rides a bike. Tom is the red Dog. Tom is happy.
			eg 2 A yellow banana is on the table. The yellow banana is a fruit. Apples are fruit. An apple is on the green tree. The yellow fruit is tasty.
			*/		
		}
		#endif
	}
	
	#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN
	if(generateParentContextPassThrough)
	{
		//b) the previous level call generateObjectInitialisationsBasedOnPropertiesAndConditions resulted in parsing sameReferenceSet connnections without the creation of a new property/conditionObject (pass through);
		//added 1i11l, moved 1l8b (fixed context 1l8i)
		//eg Tom's apple is blue.
		#ifdef NLC_DEBUG
		cout << "generateObjectInitialisationsBasedOnPropertiesAndConditions(): b) createCodeBlockForPropertyList: " << entity->entityName << endl;
		#endif

		NLCitem * propertyEntityClass = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
		propertyEntityClass->context.push_back(parentName);
		*currentCodeBlockInTree = createCodeBlockForPropertyList(*currentCodeBlockInTree, propertyEntityClass);

		//Tom's bright apple is blue.
		//generateContextBlocks(currentCodeBlockInTree, entity, sentenceIndex, &generateContextBlocksVariables);
		//parse the children (properties and conditions) of an undeclared definite parent
		NLCgenerateContextBlocksVariables generateContextBlocksVariables;
		generateContextBlocksVariables.onlyGenerateContextBlocksIfConnectionsParsedForNLC = true;
		createCodeBlockForStatements(currentCodeBlockInTree, generateInstanceName(entity), entity, sentenceIndex, &generateContextBlocksVariables);		//added 1i11n
	}
	else
	{
	#endif
		//c) the previous level call generateObjectInitialisationsBasedOnPropertiesAndConditions resulted in the creation of a new property/conditionObject (its context has not yet been generated);
		if(!(entity->NLCcontextGenerated))
		{//context block already created by generateContextBlocks()	//added 1g14b 15-July-2014
			if(!(entity->isSubstanceQuality))	//added 1l6f - ignore qualities as they will not have NLClocalListVariableHasBeenInitialised set when they were added as a property, because they will not have NLClocalListVariableHasBeenDeclared set - see declareLocalPropertyListsForIndefiniteEntities()
			{
				NLCitem * entityClass = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
				if(assumedToAlreadyHaveBeenDeclared(entity))
				{
					#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_BLOCKS_FOR_PARENT_INITIALISATION_SPECIAL
					#ifdef NLC_DEBUG
					cout << "generateObjectInitialisationsBasedOnPropertiesAndConditions(): c) createCodeBlockForCategoryList(): " << entity->entityName << endl;
					#endif
					#ifdef NLC_DEBUG_PARSE_CONTEXT2
					*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("generateObjectInitialisationsBasedOnPropertiesAndConditions(): c) createCodeBlockForCategoryList: ") + entity->entityName);
					#endif
					*currentCodeBlockInTree = createCodeBlockForCategoryList(*currentCodeBlockInTree, entity, NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION);
					entity->NLCcontextGenerated = true;	//is this required?
					#else
					#ifdef NLC_DEBUG
					cout << "generateObjectInitialisationsBasedOnPropertiesAndConditions(): c) createCodeBlockForLocalList(): " << entity->entityName << endl;
					#endif
					#ifdef NLC_DEBUG_PARSE_CONTEXT2
					*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("generateObjectInitialisationsBasedOnPropertiesAndConditions(): c) createCodeBlockForLocalList: ") + entity->entityName);
					#endif
					*currentCodeBlockInTree = createCodeBlockForLocalList(*currentCodeBlockInTree, entityClass);
					#endif
				}
				#ifdef NLC_DEFINE_LOCAL_VARIABLES_FOR_ALL_INDEFINATE_ENTITIES
				else
				{
					cout << "generateObjectInitialisationsBasedOnPropertiesAndConditions() error: !(entity->NLCcontextGenerated) && !assumedToAlreadyHaveBeenDeclared: entity = " << entity->entityName  << ", sentenceIndex = " << sentenceIndex << endl;
					cout << "NB it is possible a substance concept has been defined as a property of a non-substance concept entity, eg 'The pies near the house have red cars.' instead of 'The pies near the house have some red cars.'/'The pies near the house has 7 red cars.'" << endl;
						//NB this possibility can be corrected for with checkSpecialCaseEntity() check for substance concepts
					//OLD: corrected for with NLC_DEFINE_LOCAL_VARIABLES_FOR_ALL_INDEFINATE_ENTITIES condition; cout << "NB it is also possible that NLC_DEFINE_LOCAL_VARIABLES_FOR_ALL_INDEFINATE_ENTITIES has been disabled: (if !isSubstanceQuality) NLClocalListVariableHasBeenInitialised must be set when variables are added as a property" << endl;
				}
				#endif
			}
		}
	#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN
	}
	#endif
	#else
	//old implementation: always create context for parent at start of each call to generateObjectInitialisationsBasedOnPropertiesAndConditions() - this is a simpler implementation however it does not handle the case in which the previous child has already have had its context generated
	NLCitem * entityClass = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
	if(assumedToAlreadyHaveBeenDeclared(entity))
	{
		#ifdef NLC_DEBUG_PARSE_CONTEXT2
		*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("generateObjectInitialisationsBasedOnPropertiesAndConditions(): old implementation: createCodeBlockForPropertyListLocal: ") + entity->entityName);
		#endif
		*currentCodeBlockInTree = createCodeBlockForLocalList(*currentCodeBlockInTree, entityClass);
	}	
	else
	{
		#ifdef NLC_DEBUG_PARSE_CONTEXT2
		*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("generateObjectInitialisationsBasedOnPropertiesAndConditions(): old implementation: createCodeBlockForPropertyList: ") + entity->entityName);
		#endif

		entityClass->context.push_back(parentName);
		*currentCodeBlockInTree = createCodeBlockForPropertyList(*currentCodeBlockInTree, entityClass);
	}
	#endif
	
	bool performedAtLeastOneObjectInitialisation = false;
	if(!checkSpecialCaseEntity(entity, false))
	{
		//property initialisations
		for(vector<GIAentityConnection*>::iterator propertyNodeListIterator = entity->propertyNodeList->begin(); propertyNodeListIterator < entity->propertyNodeList->end(); propertyNodeListIterator++)
		{
			GIAentityConnection * propertyConnection = (*propertyNodeListIterator);
			GIAentityNode* propertyEntity = propertyConnection->entity;
			#ifdef NLC_DEBUG
			cout << "\t\tpropertyConnection->sentenceIndexTemp = " << propertyConnection->sentenceIndexTemp << endl;
			#endif

			#ifdef NLC_VERIFY_CONNECTIONS_SENTENCE_INDEX
			if((checkSentenceIndexParsingCodeBlocks(propertyEntity, sentenceIndex, false) || propertyEntity->NLCparsedForCodeBlocks) && (propertyConnection->sentenceIndexTemp == sentenceIndex))
			#else
			if((checkSentenceIndexParsingCodeBlocks(propertyEntity, sentenceIndex, false) || propertyEntity->NLCparsedForCodeBlocks))			
			#endif
			{//only write properties that are explicated in current sentence

				bool newlyDeclaredEntityInCategoryList2 = false;
				bool performedAtLeastOneObjectInitialisationAtThisLevel = false;
				NLCcodeblock * firstCodeBlockInSection = *currentCodeBlockInTree;

				bool generatedContextForChild = generateContextForChildEntity(entity, propertyEntity, currentCodeBlockInTree, sentenceIndex, false);
				bool passThrough = !generatedContextForChild;
				
				if(!(propertyConnection->NLCparsedForCodeBlocks))
				{					
					#ifdef NLC_TRANSLATE_NEGATIVE_PROPERTIES_AND_CONDITIONS
					if(propertyConnection->negative || (propertyEntity->isSubstanceQuality && propertyEntity->negative))
					{
						#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS
						if(assumedToAlreadyHaveBeenDeclared(propertyEntity))
						{
							#ifdef NLC_DEBUG_PARSE_CONTEXT2
							*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("generateObjectInitialisationsBasedOnPropertiesAndConditions(): 3createCodeBlockRemoveProperties: ") + entity->entityName + string(" ") + propertyEntity->entityName);
							#endif
							#ifdef NLC_DEBUG
							cout << "createCodeBlockRemoveProperties: " << entity->entityName << ", " << propertyEntity->entityName << endl;
							#endif

							NLCitem * propertyClass = new NLCitem(propertyEntity, NLC_ITEM_TYPE_OBJECT);
							*currentCodeBlockInTree = createCodeBlockRemoveEntitiesFromLocalList(*currentCodeBlockInTree, propertyEntity);
							*currentCodeBlockInTree = createCodeBlockRemoveProperties(*currentCodeBlockInTree, entity, propertyEntity);
						}
						else
						{
						#endif
							//remove properties; eg "a ball" in "Tom does not have a ball."
							#ifdef NLC_DEBUG_PARSE_CONTEXT2
							*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("generateObjectInitialisationsBasedOnPropertiesAndConditions():  4createCodeBlockRemoveProperties: ") + entity->entityName + string(" ") + propertyEntity->entityName);
							#endif
							#ifdef NLC_DEBUG
							cout << "createCodeBlockRemoveProperties: " << entity->entityName << ", " << propertyEntity->entityName << endl;
							#endif

							*currentCodeBlockInTree = createCodeBlockRemoveProperties(*currentCodeBlockInTree, entity, propertyEntity);
						#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS
						}
						#endif
					}
					else
					{
					#endif
						#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS
						if(assumedToAlreadyHaveBeenDeclared(propertyEntity))
						{
							//use function argument PropertyList (do not create a new property); eg "the ball" in "Tom has the ball"
							#ifdef NLC_DEBUG_PARSE_CONTEXT2
							*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("generateObjectInitialisationsBasedOnPropertiesAndConditions(): 3createCodeBlockAddProperty: ") + entity->entityName + string(" ") + convertIntToString(entity->NLClocalListVariableHasBeenInitialised) + string(" ") + propertyEntity->entityName + string(" ") + convertIntToString(propertyEntity->NLClocalListVariableHasBeenInitialised));
							#endif
							#ifdef NLC_DEBUG
							cout << "createCodeBlockAddProperty: " << entity->entityName << ", " << propertyEntity->entityName << endl;
							#endif

							#ifndef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_FOR_EACH_CHILD
							NLCcodeblock * firstCodeBlockInSection2 = *currentCodeBlockInTree;
							NLCitem * propertyClass = new NLCitem(propertyEntity, NLC_ITEM_TYPE_OBJECT);
							*currentCodeBlockInTree = createCodeBlockForLocalList(*currentCodeBlockInTree, propertyClass);
							#endif

							*currentCodeBlockInTree = createCodeBlockAddProperty(*currentCodeBlockInTree, entity, propertyEntity, sentenceIndex);

							#ifndef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_FOR_EACH_CHILD
							*currentCodeBlockInTree = firstCodeBlockInSection2->next;
							#endif
						}
						else
						{
						#endif
							//create a new property; eg "a ball" in "Tom has a ball"
							#ifdef NLC_DEBUG_PARSE_CONTEXT2
							*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("generateObjectInitialisationsBasedOnPropertiesAndConditions(): 4createCodeBlockAddNewProperty: ") + entity->entityName + string(" ") + propertyEntity->entityName);
							#endif
							#ifdef NLC_DEBUG
							cout << "createCodeBlockAddNewProperty: " << entity->entityName << ", " << propertyEntity->entityName << endl;
							#endif

							newlyDeclaredEntityInCategoryList2 = true;
							*currentCodeBlockInTree = createCodeBlockCreateNewProperty(*currentCodeBlockInTree, entity, propertyEntity, sentenceIndex, true);

						#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS
						}
						#endif

						#ifdef GIA_TRANSLATOR_DREAM_MODE_LINK_SPECIFIC_CONCEPTS_AND_ACTIONS
						//moved 1e1b: only generate object initialisations for items based on subject concepts when items are created in context
						//Part 2b: generate object initialisations based on substance concepts (class inheritance)
						generateObjectInitialisationsBasedOnSubstanceConcepts(propertyEntity, currentCodeBlockInTree, sentenceIndex, newlyDeclaredEntityInCategoryList2);
						#endif
					#ifdef NLC_TRANSLATE_NEGATIVE_PROPERTIES_AND_CONDITIONS
					}
					#endif

					#ifdef NLC_DEBUG
					cout << "generateObjectInitialisationsBasedOnPropertiesAndConditions():" << endl;
					cout << "entity->entityName = " << entity->entityName << endl;
					cout << "propertyEntity->entityName = " << propertyEntity->entityName << endl;
					#endif

					propertyConnection->NLCparsedForCodeBlocks = true;
					propertyEntity->NLCparsedForCodeBlocks = true;		//added 3 October 2013 NLC1b2b - used for quick access of instances already declared in current context

					performedAtLeastOneObjectInitialisationAtThisLevel = true;
					
					passThrough = false;	//added 1l8b
				}

				NLCcodeblock * firstCodeBlockBeforeRecursion = *currentCodeBlockInTree;
				bool performedAtLeastOneObjectInitialisationAtALowerLevel = generateObjectInitialisationsBasedOnPropertiesAndConditions(propertyEntity, currentCodeBlockInTree, sentenceIndex, generateInstanceName(entity), "", false, passThrough);
				#ifdef NLC_DEBUG
				cout << "performedAtLeastOneObjectInitialisationAtALowerLevel = " << performedAtLeastOneObjectInitialisationAtALowerLevel << endl;
				#endif
				generateObjectInitialisationsBasedOnPropertiesAndConditionsUpdateCodeBlockPointer(currentCodeBlockInTree, firstCodeBlockBeforeRecursion, firstCodeBlockInSection, performedAtLeastOneObjectInitialisationAtThisLevel, performedAtLeastOneObjectInitialisationAtALowerLevel, &performedAtLeastOneObjectInitialisation);
			}
		}

		#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS_ADVANCED
		//added NLC 1g5e:
		if(!(entity->isCondition))
		{//do not parse conditions of conditions as one of the conditions is a logical condition conjunction (ie and/or)
		#endif
			//state initialisations
			for(vector<GIAentityConnection*>::iterator conditionNodeListIterator = entity->conditionNodeList->begin(); conditionNodeListIterator < entity->conditionNodeList->end(); conditionNodeListIterator++)
			{
				GIAentityConnection * conditionConnection = (*conditionNodeListIterator);
				GIAentityNode* conditionEntity = conditionConnection->entity;

				#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
				if(!(conditionEntity->NLClogicalConditionOperation))		//if(!(conditionConnection->NLCparsedForlogicalConditionOperations) && !(conditionEntity->NLCparsedForlogicalConditionOperations))	//this alternative test would require "tagAllEntitiesInSentenceSubsetAsPertainingToLogicalConditionOperationAdvanced(conditionSubject, sentenceIndex, false);" to be called before "generateObjectInitialisationsBasedOnPropertiesAndConditions()"
				{
				#endif
					bool foundConditionObject = false;
					GIAentityNode * conditionObject = NULL;
					if(!(conditionEntity->conditionObjectEntity->empty()))
					{
						conditionObject = (conditionEntity->conditionObjectEntity->back())->entity;
						foundConditionObject = true;

						#ifdef NLC_VERIFY_CONNECTIONS_SENTENCE_INDEX
						if((checkSentenceIndexParsingCodeBlocks(conditionEntity, sentenceIndex, false) || conditionEntity->NLCparsedForCodeBlocks) && (conditionConnection->sentenceIndexTemp == sentenceIndex))
						#else
						if((checkSentenceIndexParsingCodeBlocks(conditionEntity, sentenceIndex, false) || conditionEntity->NLCparsedForCodeBlocks))
						#endif
						{//only write conditions that are explicated in current sentence

							bool newlyDeclaredEntityInCategoryList2 = false;
							bool performedAtLeastOneObjectInitialisationAtThisLevel = false;
							NLCcodeblock * firstCodeBlockInSection = *currentCodeBlockInTree;

							NLCitem * entityClass = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
							NLCitem * conditionObjectClass = new NLCitem(conditionObject, NLC_ITEM_TYPE_OBJECT);

							bool generatedContextForChild = generateContextForChildEntity(entity, conditionObject, currentCodeBlockInTree, sentenceIndex, true);
							bool passThrough = !generatedContextForChild;
							
							if(!(conditionConnection->NLCparsedForCodeBlocks))
							{
								#ifdef NLC_TRANSLATE_NEGATIVE_PROPERTIES_AND_CONDITIONS
								if(conditionEntity->negative)
								{
									#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS
									if(assumedToAlreadyHaveBeenDeclared(conditionObject))
									{
										#ifdef NLC_DEBUG_PARSE_CONTEXT2
										*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("generateObjectInitialisationsBasedOnPropertiesAndConditions(): 3BcreateCodeBlockRemoveConditions: ") + entity->entityName + string(" ") + conditionEntity->entityName);
										#endif

										*currentCodeBlockInTree = createCodeBlockRemoveEntitiesFromLocalList(*currentCodeBlockInTree, conditionObject);
										*currentCodeBlockInTree = createCodeBlockRemoveConditions(*currentCodeBlockInTree, entity, conditionEntity);
									}
									else
									{
									#endif
										#ifdef NLC_DEBUG_PARSE_CONTEXT2
										*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("generateObjectInitialisationsBasedOnPropertiesAndConditions():  4BcreateCodeBlockRemoveProperties: ") + entity->entityName + string(" ") + conditionEntity->entityName);
										#endif

										*currentCodeBlockInTree = createCodeBlockRemoveConditions(*currentCodeBlockInTree, entity, conditionEntity);
									#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS
									}
									#endif
								}
								else
								{
								#endif
									#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS
									if(assumedToAlreadyHaveBeenDeclared(conditionObject))
									{
										//use function argument PropertyList (do not create a new property to insert into condition); eg "the house" in "Tom is near a house"

										#ifdef NLC_DEBUG_PARSE_CONTEXT2
										*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("generateObjectInitialisationsBasedOnPropertiesAndConditions(): 3BcreateCodeBlockCondition: ") + entity->entityName + string(" ") + convertIntToString(entity->NLClocalListVariableHasBeenInitialised) + string(" ") + conditionObject->entityName + string(" ") + convertIntToString(conditionObject->NLClocalListVariableHasBeenInitialised));
										#endif

										#ifndef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_FOR_EACH_CHILD
										NLCcodeblock * firstCodeBlockInSection2 = *currentCodeBlockInTree;
										*currentCodeBlockInTree = createCodeBlockForLocalList(*currentCodeBlockInTree, conditionObjectClass);
										#endif

										*currentCodeBlockInTree = createCodeBlockAddCondition(*currentCodeBlockInTree, entity, conditionEntity, sentenceIndex);

										#ifndef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_FOR_EACH_CHILD
										*currentCodeBlockInTree = firstCodeBlockInSection2->next;
										#endif
									}
									else
									{
									#endif
										#ifdef NLC_DEBUG_PARSE_CONTEXT2
										*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("generateObjectInitialisationsBasedOnPropertiesAndConditions(): 4BcreateCodeBlockAddNewCondition: ") + entity->entityName + string(" ") + conditionObject->entityName);
										#endif

										//create a new condition; eg "a house" in "Tom is near a house"
										newlyDeclaredEntityInCategoryList2 = true;
										*currentCodeBlockInTree = createCodeBlockCreateNewCondition(*currentCodeBlockInTree, entity, conditionEntity, sentenceIndex, true);

									#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS
									}
									#endif

									#ifdef GIA_TRANSLATOR_DREAM_MODE_LINK_SPECIFIC_CONCEPTS_AND_ACTIONS
									//moved 1e1b: only generate object initialisations for items based on subject concepts when items are created in context
									//Part 2b: generate object initialisations based on substance concepts (class inheritance)
									generateObjectInitialisationsBasedOnSubstanceConcepts(conditionEntity, currentCodeBlockInTree, sentenceIndex, newlyDeclaredEntityInCategoryList2);
									#endif
								#ifdef NLC_TRANSLATE_NEGATIVE_PROPERTIES_AND_CONDITIONS
								}
								#endif

								conditionConnection->NLCparsedForCodeBlocks = true;
								conditionEntity->NLCparsedForCodeBlocks = true;	//added NLC 1b2b/3 October 2013 - used for quick access of instances already declared in current context
								conditionObject->NLCparsedForCodeBlocks = true;	//added 1e6d

								performedAtLeastOneObjectInitialisationAtThisLevel = true;
								
								passThrough = false;	//added 1l8b
							}

							NLCcodeblock * firstCodeBlockBeforeRecursion = *currentCodeBlockInTree;
							bool performedAtLeastOneObjectInitialisationAtALowerLevel = generateObjectInitialisationsBasedOnPropertiesAndConditions(conditionObject, currentCodeBlockInTree, sentenceIndex, generateInstanceName(entity), conditionEntity->entityName, false, passThrough);

							generateObjectInitialisationsBasedOnPropertiesAndConditionsUpdateCodeBlockPointer(currentCodeBlockInTree, firstCodeBlockBeforeRecursion, firstCodeBlockInSection, performedAtLeastOneObjectInitialisationAtThisLevel, performedAtLeastOneObjectInitialisationAtALowerLevel, &performedAtLeastOneObjectInitialisation);
						}
					}
					else
					{
						//no condition object
					}
				#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
				}
				#endif
			}
		#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS_ADVANCED
		}
		#endif
	}
	//cout << "performedAtLeastOneObjectInitialisation = " << performedAtLeastOneObjectInitialisation << " entity = " << entity->entityName << endl;
	
	return performedAtLeastOneObjectInitialisation;
}

bool generateContextForChildEntity(GIAentityNode * entity, GIAentityNode * childEntity, NLCcodeblock ** currentCodeBlockInTree, int sentenceIndex, bool topLevel)
{	
	#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_FOR_EACH_CHILD
	NLCgenerateContextBlocksVariables generateContextBlocksVariables;
	generateContextBlocksVariables.onlyGenerateContextBlocksIfConnectionsParsedForNLC = true;
	//research context in case, eg "The chicken has the ball which is near the park." (ie when initialisation property is definite; as distinguished from "The chicken has a ball near the park.")	
	bool generatedContextForChild = false;
	#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_FOR_EACH_CHILD_GET_PARENT
	bool foundParentEntityNew = false;
	GIAentityNode * parentEntityNew = getSameReferenceSetDefiniteUniqueParent(childEntity, sentenceIndex, entity, &foundParentEntityNew);
	#ifdef NLC_DEBUG_PARSE_CONTEXT4
	*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("generateContextForChildEntity() getSameReferenceSetDefiniteUniqueParent result; childEntity: ") + childEntity->entityName + string(", parentEntityNew: ") + parentEntityNew->entityName);
	#endif	
	if(foundParentEntityNew)
	{
		//eg Tom has Jack's ball
		#ifdef NLC_DEBUG
		cout << "generateContextForChildEntity(): foundParentEntityNew: childEntity = " << childEntity->entityName << endl;
		#endif
		#ifdef NLC_DEBUG_PARSE_CONTEXT4
		*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("generateContextForChildEntity(): (foundParentEntityNew) childEntity: ") + childEntity->entityName + string(", parentEntityNew: ") + parentEntityNew->entityName);
		#endif
		if(generateContextBlocks(currentCodeBlockInTree, parentEntityNew, sentenceIndex, &generateContextBlocksVariables, false, NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION))		//changed from generateCategories 1i11o
		{
			//eg Tom has Jack's blue ball
			generatedContextForChild = true;
			#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN
			NLCitem * propertyEntityClass = new NLCitem(childEntity, NLC_ITEM_TYPE_OBJECT);
			propertyEntityClass->context.push_back(generateInstanceName(parentEntityNew));
			*currentCodeBlockInTree = createCodeBlockForPropertyList(*currentCodeBlockInTree, propertyEntityClass);	
			#endif		
			#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_FOR_EACH_CHILD_GET_PARENT_ORIGINAL_IMPLEMENTATION		
			*currentCodeBlockInTree = createCodeBlockAddEntityToLocalList(*currentCodeBlockInTree, childEntity, childEntity);	//removed 1j10a
			#endif
			childEntity->NLClocalListVariableHasBeenInitialised = true;
		}
	}
	#endif
	
	if(assumedToAlreadyHaveBeenDeclared(childEntity))
	{
		#ifndef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN
		if(!generatedContextForChild)
		{
		#endif
			//eg Tom has the blue ball 
			#ifdef NLC_DEBUG
			cout << "generateContextForChildEntity(): assumedToAlreadyHaveBeenDeclared && !generatedContextForChild: childEntity = " << childEntity->entityName << endl;
			#endif
			#ifdef NLC_DEBUG_PARSE_CONTEXT4
			*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("generateContextForChildEntity(): assumedToAlreadyHaveBeenDeclared(childEntity): ") + childEntity->entityName);
			#endif
			if(generateContextBlocks(currentCodeBlockInTree, childEntity, sentenceIndex, &generateContextBlocksVariables, generatedContextForChild, NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION))	//pass generatedContextForChild 1j10a
			{
				
			}
			
			generatedContextForChild = true;
		#ifndef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN
		}
		#endif				
	}
	#ifdef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES	//ie #ifndef GIA_DISABLE_CROSS_SENTENCE_REFERENCING
	else 
	{
		if(!generatedContextForChild)
		{
			if(generateContextBasedOnDeclaredParent(childEntity, currentCodeBlockInTree, topLevel, entity))
			{
				#ifdef NLC_DEBUG
				cout << "generateContextForChildEntity(): generateContextBasedOnDeclaredParent: childEntity = " << childEntity->entityName << endl;
				#endif
				/*for cases in which GIA advanced referencing has referenced entities whose parent was defined in a previous sentence;
				eg 1 Tom's boat is red. The chicken rowed the red boat.
				eg 2 Tom's boat is red. The red boat is new
				NOT: Tom's boat is red. Tom's boat is new
				*/
				generatedContextForChild = true;
			}
		}
	}
	#endif
	#endif
				
	return generatedContextForChild;
}

#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_FOR_EACH_CHILD_GET_PARENT
GIAentityNode * getSameReferenceSetDefiniteUniqueParent(GIAentityNode * currentEntity, int sentenceIndex, GIAentityNode * generateObjectInitialisationsLastParent, bool * foundParentEntityNew)
{
	*foundParentEntityNew = false;
	GIAentityNode * parentEntityNew = currentEntity;
	
	for(vector<GIAentityConnection*>::iterator propertyNodeListIterator = currentEntity->propertyNodeReverseList->begin(); propertyNodeListIterator < currentEntity->propertyNodeReverseList->end(); propertyNodeListIterator++)
	{
		GIAentityConnection * parentConnection = *propertyNodeListIterator;
		GIAentityNode * parentEntity = parentConnection->entity;
		
		#ifdef NLC_DEFINE_LOCAL_VARIABLES_FOR_ALL_INDEFINATE_ENTITIES
		if(checkSentenceIndexParsingCodeBlocks(parentEntity, parentConnection, sentenceIndex, false))	//NB will parse references to entities in previous sentence
		#else
		if(checkSentenceIndexParsingCodeBlocks(parentEntity, parentConnection, sentenceIndex, false) || parentEntity->NLCparsedForCodeBlocks)
		#endif
		{
			if(parentConnection->sameReferenceSet)
			{
				//removed 1i11e, readded 1i11j
				if(parentEntity != generateObjectInitialisationsLastParent)
				{
					/*
					//added 1i11f, removed 1i11j
					if(!(parentEntity->NLCcontextGenerated))
					{
					*/
						if((parentEntity->grammaticalDefiniteTemp) || (parentEntity->grammaticalProperNounTemp))
						{
							bool foundParentEntityNewTemp = false;
							parentEntityNew = getSameReferenceSetDefiniteUniqueParent(parentEntity, sentenceIndex, generateObjectInitialisationsLastParent, &foundParentEntityNewTemp);
							*foundParentEntityNew = true;
						}
					/*	
					}
					*/
				}
			}
		}
	}
	return parentEntityNew;
}
#endif



void generateObjectInitialisationsBasedOnPropertiesAndConditionsUpdateCodeBlockPointer(NLCcodeblock ** currentCodeBlockInTree, NLCcodeblock * firstCodeBlockBeforeRecursion, NLCcodeblock * firstCodeBlockInSection, bool performedAtLeastOneObjectInitialisationAtThisLevel, bool performedAtLeastOneObjectInitialisationAtALowerLevel, bool * performedAtLeastOneObjectInitialisation)
{
	if(!performedAtLeastOneObjectInitialisationAtALowerLevel)
	{
		if(performedAtLeastOneObjectInitialisationAtThisLevel)
		{
			clearCodeBlock(firstCodeBlockBeforeRecursion);

			*currentCodeBlockInTree = getLastCodeBlockInLevel(firstCodeBlockInSection);
		}
		else
		{
			//erase redundant for loops:
			*currentCodeBlockInTree = firstCodeBlockInSection;
			clearCodeBlock(*currentCodeBlockInTree);
		}
	}
	else
	{
		*currentCodeBlockInTree = getLastCodeBlockInLevel(firstCodeBlockInSection);
	}
	if(performedAtLeastOneObjectInitialisationAtThisLevel || performedAtLeastOneObjectInitialisationAtALowerLevel)
	{
		*performedAtLeastOneObjectInitialisation = true;
	}
}

#ifdef GIA_TRANSLATOR_DREAM_MODE_LINK_SPECIFIC_CONCEPTS_AND_ACTIONS
void generateObjectInitialisationsBasedOnSubstanceConcepts(GIAentityNode * entity, NLCcodeblock ** currentCodeBlockInTree, int sentenceIndex, bool newlyDeclaredEntityInCategoryList)
{
	//added 6 December 2013: take into account plain concepts; eg "Dogs are fat. The dog rides the bike." <- the dog will be given the property 'fat'
	GIAentityNode * conceptEntity = getPrimaryConceptNodeDefiningInstance(entity);
	generateObjectInitialisationsBasedOnSubstanceConceptsRecurse(entity, conceptEntity, currentCodeBlockInTree, sentenceIndex, "", "", newlyDeclaredEntityInCategoryList);

	for(vector<GIAentityConnection*>::iterator entityNodeDefinitionListIterator = entity->entityNodeDefinitionList->begin(); entityNodeDefinitionListIterator < entity->entityNodeDefinitionList->end(); entityNodeDefinitionListIterator++)
	{
		GIAentityConnection * definitionConnection = (*entityNodeDefinitionListIterator);
		//if(!(definitionConnection->NLCparsedForCodeBlocks))	//probably not required
		//{
		GIAentityNode* definitionEntity = definitionConnection->entity;
		//check the definition is a substance concept
		if((definitionEntity->isSubstanceConcept) || (definitionEntity->isActionConcept))	//added (definitionEntity->isActionConcept)  changed 1e2e
		{
			definitionConnection->NLCparsedForCodeBlocks = true;

			generateObjectInitialisationsBasedOnSubstanceConceptsRecurse(entity, definitionEntity, currentCodeBlockInTree, sentenceIndex, "", "", newlyDeclaredEntityInCategoryList);
		}
		//}
	}
}

void generateObjectInitialisationsBasedOnSubstanceConceptsRecurse(GIAentityNode * entity, GIAentityNode * definitionEntity, NLCcodeblock ** currentCodeBlockInTree, int sentenceIndex, string parentName, string parentConditionName, bool newlyDeclaredEntityInCategoryList)
{
	#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_BASED_ON_CONCEPTS
	if(!(definitionEntity->NLCparsedForlogicalConditionOperations))
	{
	#endif
		//property initialisations
		for(vector<GIAentityConnection*>::iterator propertyNodeListIterator = definitionEntity->propertyNodeList->begin(); propertyNodeListIterator < definitionEntity->propertyNodeList->end(); propertyNodeListIterator++)
		{
			GIAentityConnection * propertyConnection = (*propertyNodeListIterator);
			GIAentityNode* propertyEntity = propertyConnection->entity;

			bool alreadyAdded = checkDuplicateProperty(propertyEntity, entity);
			if(!alreadyAdded)
			{
				NLCcodeblock * firstCodeBlockInSection = *currentCodeBlockInTree;
				bool loopUsed = false;

				#ifdef NLC_DEBUG
				//cout << "generateObjectInitialisationsBasedOnSubstanceConceptsRecurse(): property initialisation: entity->entityName = " << entity->entityName << endl;
				#endif
				NLCitem * entityClass = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
				#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_BLOCKS_FOR_PARENT_INITIALISATION_SPECIAL
				if(newlyDeclaredEntityInCategoryList)
				{
					*currentCodeBlockInTree = createCodeBlockForCategoryList(*currentCodeBlockInTree, entity, NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION);
				}
				else
				{
				#endif
					if(assumedToAlreadyHaveBeenDeclared(entity))
					{
						*currentCodeBlockInTree = createCodeBlockForLocalList(*currentCodeBlockInTree, entityClass);
					}
					else
					{
						entityClass->context.push_back(parentName);
						*currentCodeBlockInTree = createCodeBlockForPropertyList(*currentCodeBlockInTree, entityClass);
					}
				#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_BLOCKS_FOR_PARENT_INITIALISATION_SPECIAL
				}
				#endif

				*currentCodeBlockInTree = createCodeBlockCreateNewProperty(*currentCodeBlockInTree, entity, propertyEntity, sentenceIndex, false);

				entity->NLCparsedForCodeBlocks = true;			//added NLC 1b6b/4 October 2013 - used for quick access of instances already declared in current context
				generateObjectInitialisationsBasedOnSubstanceConceptsRecurse(entity, propertyEntity, currentCodeBlockInTree, sentenceIndex, generateInstanceName(definitionEntity), "", true);		//updated 9 November 2013 - support recursion of complex substance concept definition

				*currentCodeBlockInTree = firstCodeBlockInSection->next;
			}
		}
		//state initialisations
		for(vector<GIAentityConnection*>::iterator conditionNodeListIterator = definitionEntity->conditionNodeList->begin(); conditionNodeListIterator < definitionEntity->conditionNodeList->end(); conditionNodeListIterator++)
		{
			GIAentityConnection * conditionConnection = (*conditionNodeListIterator);
			GIAentityNode* conditionEntity = conditionConnection->entity;

			bool alreadyAdded = checkDuplicateCondition(conditionEntity, entity);
			if(!alreadyAdded)
			{
				NLCcodeblock * firstCodeBlockInSection = *currentCodeBlockInTree;

				bool foundConditionObject = false;
				GIAentityNode * conditionObject = NULL;
				if(!(conditionEntity->conditionObjectEntity->empty()))
				{
					conditionObject = (conditionEntity->conditionObjectEntity->back())->entity;
					foundConditionObject = true;

					#ifdef NLC_DEBUG
					//cout << "generateObjectInitialisationsBasedOnSubstanceConceptsRecurse(): condition initialisation:  entity->entityName = " << entity->entityName << endl;
					#endif
					NLCitem * entityClass = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);

					#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_BLOCKS_FOR_PARENT_INITIALISATION_SPECIAL
					if(newlyDeclaredEntityInCategoryList)
					{
						*currentCodeBlockInTree = createCodeBlockForCategoryList(*currentCodeBlockInTree, entity, NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION);
					}
					else
					{
					#endif
						if(assumedToAlreadyHaveBeenDeclared(entity))
						{
							*currentCodeBlockInTree = createCodeBlockForLocalList(*currentCodeBlockInTree, entityClass);
						}
						else
						{
							NLCitem * parentConditionItem = new NLCitem(parentConditionName, NLC_ITEM_TYPE_OBJECT);
							parentConditionItem->context.push_back(parentName);
							*currentCodeBlockInTree = createCodeBlockForConditionList(*currentCodeBlockInTree, parentConditionItem, entityClass);
						}
					#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_BLOCKS_FOR_PARENT_INITIALISATION_SPECIAL
					}
					#endif
				
					*currentCodeBlockInTree = createCodeBlockCreateNewCondition(*currentCodeBlockInTree, entity, conditionEntity, sentenceIndex, false);

					entity->NLCparsedForCodeBlocks = true;			//added NLC 1b6b/4 October 2013 - used for quick access of instances already declared in current context
					generateObjectInitialisationsBasedOnSubstanceConceptsRecurse(entity, conditionObject, currentCodeBlockInTree, sentenceIndex, generateInstanceName(definitionEntity), conditionEntity->entityName, true);	//updated 9 November 2013 - support recursion of complex substance concept definition

					*currentCodeBlockInTree = firstCodeBlockInSection->next;
				}

			}
		}
	#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_BASED_ON_CONCEPTS
	}
	#endif
}
#endif


#ifdef NLC_USE_ADVANCED_REFERENCING_SUPPORT_ALIASES

#ifdef NLC_USE_ADVANCED_REFERENCING_SUPPORT_ALIASES_PREVENT_ADDING_AS_FUNCTION_ARGUMENT
//CURRENTLYILLEGAL: "Tom rides a bike. Tom is the red dog."
void fillFunctionAliasClassList(NLCcodeblock ** currentCodeBlockInTree, vector<GIAentityNode*> * entityNodesActiveListComplete)
{	
	#ifdef NLC_DEBUG_ADVANCED_REFERENCING_SUPPORT_ALIASES
	cout << "start fillFunctionAliasClassList():" << endl;
	#endif
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode * aliasClassEntity = (*entityIter);

		for(vector<GIAentityConnection*>::iterator entityNodeDefinitionListIterator = aliasClassEntity->entityNodeDefinitionList->begin(); entityNodeDefinitionListIterator < aliasClassEntity->entityNodeDefinitionList->end(); entityNodeDefinitionListIterator++)
		{
			GIAentityConnection * definitionConnection = (*entityNodeDefinitionListIterator);
			GIAentityNode * aliasEntity = definitionConnection->entity;

			if(definitionConnection->isAlias)
			{
				string aliasName = aliasEntity->entityName;
				string aliasClassName = aliasClassEntity->entityName;
					
				unordered_map<string, string> *  functionAliasClassList = getFunctionAliasClassList();
				functionAliasClassList->insert(pair<string, string>(aliasName, aliasClassName));
			}
		}
	}
	#ifdef NLC_DEBUG_ADVANCED_REFERENCING_SUPPORT_ALIASES
	cout << "end fillFunctionAliasClassList():" << endl;
	#endif
}
#endif
/*
//CURRENTLYILLEGAL; "Tom rides a bike. Tom is a/the red dog."
void fillFunctionAliasClassList(NLCcodeblock ** currentCodeBlockInTree, vector<GIAentityNode*> * entityNodesActiveListComplete)
{	
	#ifdef NLC_DEBUG_ADVANCED_REFERENCING_SUPPORT_ALIASES
	cout << "start fillFunctionAliasClassList():" << endl;
	#endif
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode * aliasClassEntity = (*entityIter);

		for(vector<GIAentityConnection*>::iterator entityNodeDefinitionListIterator = aliasClassEntity->entityNodeDefinitionList->begin(); entityNodeDefinitionListIterator < aliasClassEntity->entityNodeDefinitionList->end(); entityNodeDefinitionListIterator++)
		{
			GIAentityConnection * definitionConnection = (*entityNodeDefinitionListIterator);
			GIAentityNode * aliasEntity = definitionConnection->entity;

			if(definitionConnection->isAlias)
			{
				string aliasName = aliasEntity->entityName;
				string aliasClassName = aliasClassEntity->entityName;
				
				//now initialise the entity corresponding to the alias (appropriate for "Tom rides a bike. Tom is a red dog." but not appropriate for "A red dog rides a bike. The name of the red dog is Tom."/"A red dog rides a bike. Tom is the red Dog."
				//see if the first reference to the alias (eg Tom) occurs during its definition, and if not initialise the object it is referencing (eg dog)
				bool aliasIsReferencedBeforeItIsDefined = false;
				for(vector<GIAentityNode*>::iterator entityIter2 = entityNodesActiveListComplete->begin(); entityIter2 != entityNodesActiveListComplete->end(); entityIter2++)
				{
					GIAentityNode * entity2 = (*entityIter2);
					if(entity2->entityName == aliasName)
					{
						if(entity2->sentenceIndexTemp < aliasEntity->sentenceIndexTemp)
						{
							aliasIsReferencedBeforeItIsDefined = true;		
						}
					}
				}
				if(aliasIsReferencedBeforeItIsDefined)
				{
					#ifdef NLC_DEBUG_ADVANCED_REFERENCING_SUPPORT_ALIASES
					cout << "fillFunctionAliasClassList(): aliasIsReferencedBeforeItIsDefined" << endl;
					cout << "aliasName = " << aliasName << endl;
					cout << "aliasClassName = " << aliasClassName << endl;
					#endif
						
					unordered_map<string, string> *  functionAliasClassList = getFunctionAliasClassList();
					functionAliasClassList->insert(pair<string, string>(aliasName, aliasClassName));
				
					*currentCodeBlockInTree = createCodeBlocksDeclareNewLocalListVariableIfNecessary(*currentCodeBlockInTree, aliasClassEntity);
				
					int sentenceIndexTempNotUsed = 0;
					*currentCodeBlockInTree = createCodeBlockAddNewEntityToLocalList(*currentCodeBlockInTree, aliasClassEntity, sentenceIndexTempNotUsed, false);
					*currentCodeBlockInTree = createCodeBlocksAddAliasToEntityAliasList(*currentCodeBlockInTree, aliasClassEntity, aliasName);
				}
			}
		}
	}
	#ifdef NLC_DEBUG_ADVANCED_REFERENCING_SUPPORT_ALIASES
	cout << "end fillFunctionAliasClassList():" << endl;
	#endif
}
*/

//"A red dog rides a bike. The name of the red dog is Tom."/"A red dog rides a bike. Tom is the red Dog."
void identifyAliasesInCurrentSentence(NLCcodeblock ** currentCodeBlockInTree, vector<GIAentityNode*> * entityNodesActiveListComplete, int sentenceIndex)
{
	#ifdef NLC_DEBUG_ADVANCED_REFERENCING_SUPPORT_ALIASES
	cout << "start identifyAliasesInCurrentSentence():" << endl;
	#endif
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode * aliasClassEntity = (*entityIter);
		if(checkSentenceIndexParsingCodeBlocks(aliasClassEntity, sentenceIndex, false))
		{
			for(vector<GIAentityConnection*>::iterator entityNodeDefinitionListIterator = aliasClassEntity->entityNodeDefinitionList->begin(); entityNodeDefinitionListIterator < aliasClassEntity->entityNodeDefinitionList->end(); entityNodeDefinitionListIterator++)
			{
				GIAentityConnection * definitionConnection = (*entityNodeDefinitionListIterator);
				GIAentityNode * aliasEntity = definitionConnection->entity;
				if(checkSentenceIndexParsingCodeBlocks(aliasEntity, sentenceIndex, false))
				{
					if(definitionConnection->isAlias)
					{
						#ifdef NLC_VERIFY_CONNECTIONS_SENTENCE_INDEX
						if(definitionConnection->sentenceIndexTemp == sentenceIndex)
						{
						#endif
							bool aliasAlreadyInitialised = false;
							string aliasName = aliasEntity->entityName;
							string aliasClassName = aliasClassEntity->entityName;
							
							string aliasNameTemp = "";
							if(findAliasInEntity(aliasEntity, &aliasNameTemp)) //*
							{
								aliasAlreadyInitialised = true;
							}
							if(!aliasAlreadyInitialised)
							{
								#ifdef NLC_DEBUG_ADVANCED_REFERENCING_SUPPORT_ALIASES
								cout << "identifyAliasesInCurrentSentence():" << endl;
								cout << "aliasName = " << aliasName << endl;
								cout << "aliasClassName = " << aliasClassName << endl;
								#endif
							
								/*
								unordered_map<string, string> *  functionAliasClassList = getFunctionAliasClassList();
								functionAliasClassList->insert(pair<string, string>(aliasName, aliasClassName));
								*/
								
								NLCgenerateContextBlocksVariables generateContextBlocksVariables;	//CHECKTHIS
								bool generatedParentContext = false;	//CHECKTHIS
								NLCcodeblock * firstCodeBlockInSentence = *currentCodeBlockInTree;
								if(!generateContextBlocks(currentCodeBlockInTree, aliasClassEntity, sentenceIndex, &generateContextBlocksVariables, generatedParentContext, NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION))
								{
									#ifdef NLC_DEBUG_ADVANCED_REFERENCING_SUPPORT_ALIASES
									cout << "identifyAliasesInCurrentSentence(): !generateContextBlocks: aliasClassEntity = " << aliasClassEntity->entityName << endl;
									#endif
								}
								
								*currentCodeBlockInTree = createCodeBlocksAddAliasToEntityAliasList(*currentCodeBlockInTree, aliasClassEntity, aliasName);
								
								*currentCodeBlockInTree = getLastCodeBlockInLevel(firstCodeBlockInSentence);
								
								//1k14c; replace all alias GIA entities with their respective class (eg dog), and add an alias to their vector list (eg Tom)
								for(vector<GIAentityNode*>::iterator entityIter2 = entityNodesActiveListComplete->begin(); entityIter2 != entityNodesActiveListComplete->end(); entityIter2++)
								{
									GIAentityNode * entity2 = (*entityIter2);
									if(entity2->entityName == aliasName)
									{
										if(entity2->sentenceIndexTemp > aliasEntity->sentenceIndexTemp)	//this test isn't required because of *
										{
											entity2->aliasList.push_back(aliasName);
											entity2->entityName = aliasClassName;	
										}
									}
								}	
							}
						#ifdef NLC_VERIFY_CONNECTIONS_SENTENCE_INDEX
						}
						#endif
					}
				}
			}
		}
	}
	#ifdef NLC_DEBUG_ADVANCED_REFERENCING_SUPPORT_ALIASES
	cout << "end identifyAliasesInCurrentSentence():" << endl;
	#endif
}

#endif

bool checkSpecialCaseEntity(GIAentityNode * entity, bool detectActions)
{
	bool specialCaseEntity = false;
	if((entity->isConcept) || (entity->isSubstanceConcept) || (entity->isActionConcept) || (entity->isCondition))
	{
		specialCaseEntity = true;
	}
	else if(detectActions && (entity->isAction))
	{
		specialCaseEntity = true;
	}
	return specialCaseEntity;
}			

#ifdef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES
bool generateContextBasedOnDeclaredParent(GIAentityNode * entity, NLCcodeblock ** currentCodeBlockInTree, bool topLevel, GIAentityNode * generateObjectInitialisationsLastParent)
{
	bool foundParentProperty = false;
	for(vector<GIAentityConnection*>::iterator propertyNodeListIterator = entity->propertyNodeReverseList->begin(); propertyNodeListIterator < entity->propertyNodeReverseList->end(); propertyNodeListIterator++)
	{
		GIAentityConnection * parentConnection = *propertyNodeListIterator;
		GIAentityNode * parentEntity = parentConnection->entity;
				
		if(!foundParentProperty)
		{
			if(parentEntity->sentenceIndexTemp <= entity->sentenceIndexTemp)	//no strict same sentence check as this function assumes GIA referencing
			{
				if(!(parentEntity->disabled))
				{
					if(assumedToAlreadyHaveBeenDeclared(parentEntity))
					{
						if(parentEntity != generateObjectInitialisationsLastParent)	//added 1l7h
						{
							foundParentProperty = true;
							if(topLevel)
							{						
								NLCitem * parentEntityClass = new NLCitem(parentEntity, NLC_ITEM_TYPE_OBJECT);
								*currentCodeBlockInTree = createCodeBlockForLocalList(*currentCodeBlockInTree, parentEntityClass);	
							}
							NLCitem * propertyEntityClass = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
							propertyEntityClass->context.push_back(generateInstanceName(parentEntity));
							*currentCodeBlockInTree = createCodeBlockForPropertyList(*currentCodeBlockInTree, propertyEntityClass);	
							entity->NLCcontextGenerated = true;
							#ifdef NLC_DEBUG
							//cout << "generateContextBasedOnDeclaredParent: entity: " << entity->entityName << endl;
							//cout << "generateContextBasedOnDeclaredParent: foundParentProperty: " << parentEntity->entityName << endl;
							#endif
						}
					}
				}
			}
		}
	}
	return foundParentProperty;
}
#endif
	
bool getActionSubjectEntityConnection(GIAentityNode * actionEntity, int sentenceIndex, GIAentityConnection ** actionSubjectConnection)
{
	bool actionHasSubject = false;
	#ifdef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES	//&& #defined NLC_RECORD_ACTION_HISTORY_GENERALISABLE
	//required because GIA advanced referencing may connect a given action to multiple subjects/objects (ie across multiple sentences)
	for(vector<GIAentityConnection*>::iterator iter = actionEntity->actionSubjectEntity->begin(); iter < actionEntity->actionSubjectEntity->end(); iter++)
	{
		GIAentityConnection * actionSubjectConnectionTemp = *iter;
		if(actionSubjectConnectionTemp->sentenceIndexTemp == sentenceIndex)
		{
			#ifdef NLC_DEBUG
			//cout << "getActionSubjectEntityConnection(): actionSubjectConnectionTemp->sentenceIndexTemp = " << actionSubjectConnectionTemp->sentenceIndexTemp << endl;
			#endif
			*actionSubjectConnection = actionSubjectConnectionTemp;
			actionHasSubject = true;	
		}
	}
	#else
	if(!(actionEntity->actionSubjectEntity->empty()))
	{
		*actionSubjectConnection = (actionEntity->actionSubjectEntity->back());
		actionHasSubject = true;
	}	
	#endif
	return actionHasSubject;
}	

bool getActionObjectEntityConnection(GIAentityNode * actionEntity, int sentenceIndex, GIAentityConnection ** actionObjectConnection)
{
	bool actionHasObject = false;
	#ifdef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES	//&& #defined NLC_RECORD_ACTION_HISTORY_GENERALISABLE
	//required because GIA advanced referencing may connect a given action to multiple subjects/objects across sentences (ie across multiple sentences)
	for(vector<GIAentityConnection*>::iterator iter = actionEntity->actionObjectEntity->begin(); iter < actionEntity->actionObjectEntity->end(); iter++)
	{
		GIAentityConnection * actionObjectConnectionTemp = *iter;
		if(actionObjectConnectionTemp->sentenceIndexTemp == sentenceIndex)
		{	
			#ifdef NLC_DEBUG
			//cout << "getActionObjectEntityConnection(): actionObjectConnectionTemp->sentenceIndexTemp = " << actionObjectConnectionTemp->sentenceIndexTemp << endl;
			#endif
			*actionObjectConnection = actionObjectConnectionTemp;
			actionHasObject = true;	
		}
	}
	#else
	if(!(actionEntity->actionObjectEntity->empty()))
	{
		*actionObjectConnection = (actionEntity->actionObjectEntity->back());
		actionHasObject = true;
	}	
	#endif
	return actionHasObject;
}
	
