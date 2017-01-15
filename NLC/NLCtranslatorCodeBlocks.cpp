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
 * File Name: NLCtranslatorCodeBlocks.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2015 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 1q2c 18-August-2015
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/


#include "NLCtranslatorCodeBlocks.h"
#include "NLCtranslatorCodeBlocksLogicalConditions.h"
#include "NLCtranslatorCodeBlocksLogicalConditionsAdvanced.h"
#include "NLCtranslatorCodeBlocksOperations.h"
#include "NLCprintDefs.h"	//required for NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION
#include "GIAtranslatorOperations.h"	//required for getPrimaryConceptNodeDefiningInstance()
	
bool generateCodeBlocks(NLCcodeblock* firstCodeBlockInTree, vector<GIAentityNode*>* entityNodesActiveListComplete, map<int, vector<GIAentityNode*>*>* entityNodesActiveListSentences, int maxNumberSentences, string NLCfunctionName, NLCfunction* currentNLCfunctionInList)
{
	bool result = true;

	NLCcodeblock* currentCodeBlockInTree = firstCodeBlockInTree;
	
	#ifdef NLC_USE_ADVANCED_REFERENCING_SUPPORT_ALIASES_PREVENT_ADDING_AS_FUNCTION_ARGUMENT
	#ifndef NLC_USE_ADVANCED_REFERENCING_SUPPORT_ALIASES_CROSS_FUNCTION_ALIASES
	#ifdef NLC_DEBUG
	cout << "generateCodeBlocks{}: initialiseFunctionAliasClassList:" << endl;
	#endif
	initialiseFunctionAliasClassList();
	#endif
	#ifdef NLC_DEBUG
	cout << "generateCodeBlocks{}: fillFunctionAliasClassList:" << endl;
	#endif
	fillFunctionAliasClassList(entityNodesActiveListComplete);
	#endif
	
	currentCodeBlockInTree = createCodeBlockNewFunction(currentCodeBlockInTree, NLCfunctionName, entityNodesActiveListComplete, (currentNLCfunctionInList->firstNLCsentenceInFunction));

	//#ifdef NLC_USE_PREPROCESSOR
	NLCsentence* currentNLCsentenceInList = currentNLCfunctionInList->firstNLCsentenceInFunction;
	//#endif
	
	#ifdef NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT
	#ifdef NLC_USE_PREPROCESSOR
	#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
	if(getUseNLCpreprocessor())
	{
		currentCodeBlockInTree = createCodeBlocksDeclareContextList(currentCodeBlockInTree, 0);
	}
	#endif
	#endif
	#endif
	
	#ifdef NLC_USE_ADVANCED_REFERENCING_DECLARE_LOCAL_PROPERTY_LISTS_FOR_ALL_INDEFINITE_ENTITIES_FOR_ALL_SENTENCES
	#ifdef NLC_DEFINE_LOCAL_VARIABLES_FOR_ALL_INDEFINATE_ENTITIES
	//Part Prep A - declareLocalVariables (for non-specific indefinte entities, eg "a chicken", not "a blue chicken") - added 1g8a;
	#ifdef NLC_DEBUG
	cout << "generateCodeBlocks{}: declareLocalPropertyListsForIndefiniteEntities:" << endl;
	#endif
	declareLocalPropertyListsForIndefiniteEntities(&currentCodeBlockInTree, entityNodesActiveListComplete, 0, NLCfunctionName, currentNLCsentenceInList);
	#endif
	#endif
	
	#ifdef NLC_DEBUG
	cout << "generateCodeBlocks{}: maxNumberSentences = " << maxNumberSentences << endl;
	#endif
	for(map<int, vector<GIAentityNode*>*>::iterator sentenceIter = entityNodesActiveListSentences->begin(); sentenceIter != entityNodesActiveListSentences->end(); )
	{
		int sentenceIndex = sentenceIter->first;
		vector<GIAentityNode*>* entityNodesActiveListSentence = sentenceIter->second;
		
		/*
		cout << "\ncurrentNLCsentenceInList->sentenceContents = " << currentNLCsentenceInList->sentenceContents << endl;
		cout << "currentNLCsentenceInList->sentenceIndex = " << currentNLCsentenceInList->sentenceIndex << endl;
		cout << "currentNLCsentenceInList->indentation = " << currentNLCsentenceInList->indentation << endl;
		cout << "currentNLCsentenceInList->hasLogicalConditionOperator = " << currentNLCsentenceInList->hasLogicalConditionOperator << endl;
		cout << "currentNLCsentenceInList->logicalConditionOperator = " << currentNLCsentenceInList->logicalConditionOperator << endl;
		cout << "currentNLCsentenceInList->mathText = " << currentNLCsentenceInList->mathText << endl;
		cout << "currentNLCsentenceInList->isMath = " << currentNLCsentenceInList->isMath << endl;
		cout << "currentNLCsentenceInList->mathTextNLPparsablePhraseIndex = " << currentNLCsentenceInList->mathTextNLPparsablePhraseIndex << endl;
		cout << "currentNLCsentenceInList->mathTextNLPparsablePhraseTotal = " << currentNLCsentenceInList->mathTextNLPparsablePhraseTotal << endl;
		cout << "currentNLCsentenceInList->sentenceOriginal = " << currentNLCsentenceInList->sentenceOriginal << endl;
		cout << "currentNLCsentenceInList->sentenceContentsOriginal = " << currentNLCsentenceInList->sentenceContentsOriginal << endl;
		*/
		
		#ifdef NLC_DEBUG
		cout << "generateCodeBlocks{}: sentenceIndex = " << sentenceIndex << endl;
		#endif

		#ifdef NLC_PREPROCESSOR_GENERATE_COMMENTS
		if(getUseNLCpreprocessor())
		{
			if(currentNLCsentenceInList->isMath)
			{
				#ifdef NLC_DEBUG
				//cout << "currentNLCsentenceInList->sentenceOriginal = " << currentNLCsentenceInList->sentenceOriginal << endl;
				#endif
				currentCodeBlockInTree = createCodeBlockCommentSingleLine(currentCodeBlockInTree, currentNLCsentenceInList->sentenceOriginal);
			}
			else
			{
				#ifdef NLC_DEBUG
				//cout << "currentNLCsentenceInList->sentenceContentsOriginal = " << currentNLCsentenceInList->sentenceContentsOriginal << endl;
				#endif
				currentCodeBlockInTree = createCodeBlockCommentSingleLine(currentCodeBlockInTree, currentNLCsentenceInList->sentenceContentsOriginal);
			}		
		}
		#endif

		#ifdef NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT
		#ifdef NLC_USE_PREPROCESSOR
		#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
		if(getUseNLCpreprocessor())
		{	
			#ifdef NLC_DEBUG
			//cout << "setCurrentLogicalConditionLevel: currentNLCsentenceInList->indentation) = " << currentNLCsentenceInList->indentation) << endl;
			#endif
			setCurrentLogicalConditionLevel(currentNLCsentenceInList->indentation);
		}
		#endif
		#endif
		#endif
		
		#ifndef NLC_USE_ADVANCED_REFERENCING_DECLARE_LOCAL_PROPERTY_LISTS_FOR_ALL_INDEFINITE_ENTITIES_FOR_ALL_SENTENCES
		#ifdef NLC_DEFINE_LOCAL_VARIABLES_FOR_ALL_INDEFINATE_ENTITIES
		//Part Prep A - declareLocalVariables (for non-specific indefinite entities, eg "a chicken", not "a blue chicken") - added 1g8a;
		#ifdef NLC_DEBUG
		cout << "declareLocalPropertyListsForIndefiniteEntities:" << endl;
		#endif
		declareLocalPropertyListsForIndefiniteEntities(&currentCodeBlockInTree, entityNodesActiveListSentence, sentenceIndex, NLCfunctionName, currentNLCsentenceInList);	//added 1g8a 11-July-2014
		#endif
		#endif
		
		#ifdef NLC_GENERATE_OBJECT_INITIALISATIONS_BASED_ON_SUBSTANCE_CONCEPTS_FOR_ALL_DEFINITE_ENTITIES
		#ifdef NLC_DEBUG
		cout << "generateObjectInitialisationsBasedOnSubstanceConceptsForAllDefiniteEntities:" << endl;
		#endif
		generateObjectInitialisationsBasedOnSubstanceConceptsForAllDefiniteEntities(&currentCodeBlockInTree, entityNodesActiveListSentence, sentenceIndex);
		#endif

		#ifdef NLC_PREPROCESSOR_MATH_REPLACE_NUMERICAL_VARIABLES_NAMES_FOR_NLP
		if(getUseNLCpreprocessor())
		{
			//reconcile temporary variable name replacement
			for(int i=0; i<currentNLCsentenceInList->variableNamesDetected.size(); i++)
			{	
				if(!(currentNLCsentenceInList->isMath))
				{//only replace variables names (and reconcile temporary variable name replacement) for non math text
					int dummyNumericalValue = generateDummyNumericalValue(i+1);
					string numericalVariableName = currentNLCsentenceInList->variableNamesDetected[i];
					#ifdef NLC_DEBUG_PREPROCESSOR_MATH_REPLACE_NUMERICAL_VARIABLES
					cout << "currentNLCsentenceInList->sentenceContents = " << currentNLCsentenceInList->sentenceContents << endl; 
					cout << "dummyNumericalValue = " << dummyNumericalValue << endl;
					cout << "numericalVariableName = " << numericalVariableName << endl;
					#endif
					if(!findAndSetDummyNumericalValueForReplacement(entityNodesActiveListSentence, sentenceIndex, dummyNumericalValue, numericalVariableName))
					{
						cout << "generateCodeBlocks{} error: !findAndSetDummyNumericalValueForReplacement, dummyNumericalValueToRestore = " << dummyNumericalValue << ", numericalVariableName = " << numericalVariableName << endl;
					}
				}
				else
				{
					cout << "generateCodeBlocks{} error: currentNLCsentenceInList->variableNamesDetected && currentNLCsentenceInList->isMath" << endl;
				}
			}
		}
		#endif
		
		#ifdef NLC_PREPROCESSOR_MATH
		if(getUseNLCpreprocessor() && (currentNLCsentenceInList->isMath))
		{
			#ifdef NLC_DEBUG_PREPROCESSOR_MATH
			cout << "generateCodeBlocksFromMathText{}: currentNLCsentenceInList->mathText = " << currentNLCsentenceInList->mathText << endl;
			#endif
			
			//generateCodeBlocksFromMathText (including logical conditions) - added 1h1d;
			#ifdef NLC_DEBUG
			cout << "generateCodeBlocksFromMathText:" << endl;
			#endif
			if(!generateCodeBlocksFromMathText(&currentCodeBlockInTree, sentenceIter, sentenceIndex, currentNLCsentenceInList, NLCfunctionName))
			{
				result = false;
			}
		}
		else
		{
		#endif	
			#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
			//Part 2 - logical conditions (eg If the house is red, ride the boat) - added 1f1a;
			#ifdef NLC_DEBUG
			cout << "generateCodeBlocksPart2logicalConditions:" << endl;
			#endif
			if(!generateCodeBlocksPart2logicalConditions(&currentCodeBlockInTree, entityNodesActiveListSentence, sentenceIndex, NLCfunctionName, currentNLCsentenceInList))
			{
				result = false;
			}
			#endif

			//Part 3; subject object connections (object initialisations; actions, properties, conditions, redefinitions) (eg Tom rides the boat, Tom has a boat, Tom is near a boat, The dog is an Alsation)
			#ifdef NLC_DEBUG
			cout << "generateCodeBlocksPart3subjectObjectConnections:" << endl;
			#endif
			if(!generateCodeBlocksPart3subjectObjectConnections(&currentCodeBlockInTree, entityNodesActiveListSentence, sentenceIndex, NLCfunctionName, currentNLCsentenceInList))
			{
				result = false;
			}
			
		#ifdef NLC_PREPROCESSOR_MATH
		}
		#endif

		#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
		clearContextGeneratedVariable(entityNodesActiveListSentence);
		#endif


		#ifdef NLC_USE_PREPROCESSOR
		if(getUseNLCpreprocessor())
		{	
			if(currentNLCsentenceInList->next != NULL)
			{
				#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
				NLCsentence* nextNLCfullSentenceInList = currentNLCsentenceInList->next;
				bool currentSentenceContainsLogicalCondition = getCurrentSentenceContainsLogicalCondition();
				int currentLogicalConditionLevel = getCurrentLogicalConditionLevel();
				#elif defined NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
				NLCsentence* nextNLCfullSentenceInList = currentNLCsentenceInList;
				if(currentNLCsentenceInList->mathTextNLPparsablePhraseTotal > 0)
				{
					for(int phraseIndex=0; phraseIndex<currentNLCsentenceInList->mathTextNLPparsablePhraseTotal; phraseIndex++)
					{
						nextNLCfullSentenceInList = nextNLCfullSentenceInList->next;
					}
				}
				else
				{
					nextNLCfullSentenceInList = currentNLCsentenceInList->next;
				}
				#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
				cout << "\tcurrentNLCsentenceInList->mathTextNLPparsablePhraseTotal = " << currentNLCsentenceInList->mathTextNLPparsablePhraseTotal << endl;
				cout << "currentNLCsentenceInList->sentenceIndex = " << currentNLCsentenceInList->sentenceIndex << endl;
				cout << "currentNLCsentenceInList->sentenceContents = " << currentNLCsentenceInList->sentenceContents << endl;
				cout << "nextNLCfullSentenceInList->sentenceContents = " << nextNLCfullSentenceInList->sentenceContents << endl;
				cout << "currentNLCsentenceInList->indentation = " << currentNLCsentenceInList->indentation << endl;
				cout << "nextNLCfullSentenceInList->indentation = " << nextNLCfullSentenceInList->indentation << endl;
				#endif
				bool currentSentenceContainsLogicalCondition = currentNLCsentenceInList->hasLogicalConditionOperator;
				int currentLogicalConditionLevel = currentNLCsentenceInList->indentation;
				#else
				cout << "preprocessor error: NLC_USE_PREPROCESSOR && !NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED && !NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE" << endl;
				#endif
				
				if(nextNLCfullSentenceInList->indentation == (currentNLCsentenceInList->indentation + 1))
				{
					if(currentSentenceContainsLogicalCondition)
					{
						//indentation already correctly processed in generateCodeBlocksPart2logicalConditions()
					}
					else
					{
						cout << "NLC_USE_PREPROCESSOR generateCodeBlocks{} error: invalid indentation of nextNLCfullSentenceInList, sentenceIndex = " << sentenceIndex << endl;
						cout << "!currentSentenceContainsLogicalCondition && nextNLCfullSentenceInList->indentation == currentNLCsentenceInList->indentation + 1" << endl;
						cout << "currentNLCsentenceInList->indentation = " << currentNLCsentenceInList->indentation << endl;
						cout << "nextNLCfullSentenceInList->indentation = " << nextNLCfullSentenceInList->indentation << endl;
					}
				}
				else if(nextNLCfullSentenceInList->indentation == currentNLCsentenceInList->indentation)
				{
					if(currentSentenceContainsLogicalCondition)
					{
						//indentation already correctly processed in generateCodeBlocksPart2logicalConditions()
					}
					else
					{
						//no changes
					}
				}
				else if(nextNLCfullSentenceInList->indentation < currentNLCsentenceInList->indentation)
				{
					if(currentLogicalConditionLevel == 0)
					{
						cout << "NLC_USE_PREPROCESSOR generateCodeBlocks{} error: invalid indentation of currentNLCsentenceInList->next, sentenceIndex = " << sentenceIndex << endl;
						cout << "(currentLogicalConditionLevel == 0) && nextNLCfullSentenceInList->indentation < currentNLCsentenceInList->indentation" << endl;
						cout << "currentNLCsentenceInList->indentation = " << currentNLCsentenceInList->indentation << endl;
						cout << "nextNLCfullSentenceInList->indentation = " << nextNLCfullSentenceInList->indentation << endl;
					}
					else
					{
						currentCodeBlockInTree = getCodeBlockAtPreviousLogicalConditionBaseLevelArray(nextNLCfullSentenceInList->indentation);
						#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
						setCurrentLogicalConditionLevel(nextNLCfullSentenceInList->indentation);
						#endif
					}
				}
				else
				{
					cout << "NLC_USE_PREPROCESSOR generateCodeBlocksPart2logicalConditions{} error: invalid indentation of nextNLCfullSentenceInList, sentenceIndex = " << sentenceIndex << endl;
					cout << "nextNLCfullSentenceInList->indentation > currentNLCsentenceInList->indentation + 1" << endl;
					cout << "currentNLCsentenceInList->indentation = " << currentNLCsentenceInList->indentation << endl;
					cout << "nextNLCfullSentenceInList->indentation = " << nextNLCfullSentenceInList->indentation << endl;
				}
				
				if(nextNLCfullSentenceInList->next != NULL)
				{	
					for(int i=0; i<((nextNLCfullSentenceInList->sentenceIndex)-sentenceIndex); i++)
					{	
						sentenceIter++; 
					}
					//sentenceIndex = nextNLCfullSentenceInList->sentenceIndex;
				}
				else
				{
					for(int i=0; i<(maxNumberSentences-sentenceIndex)+1; i++)
					{
						sentenceIter++; 
					}
					//sentenceIndex = maxNumberSentences+1;
				}
				currentNLCsentenceInList = nextNLCfullSentenceInList;
				#ifdef NLC_DEBUG
				//cout << "next sentenceIndex = " << sentenceIndex << endl;
				#endif
			}
			else
			{
				sentenceIter++;
				#ifdef NLC_DEBUG
				//cout << "NLC_USE_PREPROCESSOR generateCodeBlocks{}: currentNLCsentenceInList->next == NULL, sentenceIndex = " << sentenceIndex << endl;
				#endif
			}
			#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
			setCurrentSentenceContainsLogicalCondition(false);
			#endif
		}
		else
		{
			sentenceIter++;
		}
		#else
		sentenceIter++;
		#endif

	}
	
	#ifdef NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT
	#ifdef NLC_USE_PREPROCESSOR
	#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
	if(getUseNLCpreprocessor())
	{
		currentCodeBlockInTree = createCodeBlocksClearContextListVariableExecuteFunction(currentCodeBlockInTree, 0);
	}
	#endif
	#endif
	#endif

	return result;
}
		
bool declareLocalPropertyListsForIndefiniteEntities(NLCcodeblock** currentCodeBlockInTree, vector<GIAentityNode*>* entityNodesActiveListComplete, int sentenceIndex, string NLCfunctionName, NLCsentence* currentNLCsentenceInList)
{
	bool result = false;
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode* entity = (*entityIter);
		if(!checkSpecialCaseEntity(entity, true) && !(entity->isSubstanceQuality))
		{	
			if(declareLocalPropertyListsForIndefiniteEntitiesValidClassChecks(entity))
			{
				#ifdef NLC_USE_ADVANCED_REFERENCING_DECLARE_LOCAL_PROPERTY_LISTS_FOR_ALL_INDEFINITE_ENTITIES_FOR_ALL_SENTENCES
				if(!(entity->disabled))	//added 1k7f
				{
				#else
				if(checkSentenceIndexParsingCodeBlocks(entity, sentenceIndex, false))
				{
				#endif
					if(!assumedToAlreadyHaveBeenDeclared(entity))
					{//indefinite entity found	
						if(declareLocalPropertyListsForIndefiniteEntity(currentCodeBlockInTree, entity, currentNLCsentenceInList))
						{
							#ifdef NLC_DEBUG
							cout << "declareLocalPropertyListsForIndefiniteEntities{}: " << entity->entityName << endl;
							#endif
							result = true;
						}
					}
				}
			}
		}
	}
	return result;
}

bool declareLocalPropertyListsForIndefiniteEntity(NLCcodeblock** currentCodeBlockInTree, GIAentityNode* entity, NLCsentence* currentNLCsentenceInList)
{
	bool result = true;
	
	#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
	#ifdef NLC_USE_PREPROCESSOR
	#ifdef NLC_PREPROCESSOR_LOGICAL_CONDITION_USE_ROBUST_NLP_INDEPENDENT_CODE
	NLCcodeblock* firstCodeBlockAtStartOfElseStatement = *currentCodeBlockInTree;
	NLCcodeblock* firstCodeBlockAtStartOfIfStatement = NULL;
	NLCcodeblock* previousCodeBlockInTree = NULL;
	setCurrentCodeBlockInTreeToStartOfIfStatement(currentCodeBlockInTree, &firstCodeBlockAtStartOfIfStatement, firstCodeBlockAtStartOfElseStatement, currentNLCsentenceInList->elseIfDetected, currentNLCsentenceInList->elseDetected);
	previousCodeBlockInTree = *currentCodeBlockInTree;
	#endif
	#endif
	#endif

	*currentCodeBlockInTree = createCodeBlocksDeclareNewLocalListVariableIfNecessary(*currentCodeBlockInTree, entity);

	#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
	#ifdef NLC_USE_PREPROCESSOR
	#ifdef NLC_PREPROCESSOR_LOGICAL_CONDITION_USE_ROBUST_NLP_INDEPENDENT_CODE
	restoreCurrentCodeBlockInTreeToStartOfElseStatement(currentCodeBlockInTree, firstCodeBlockAtStartOfIfStatement, firstCodeBlockAtStartOfElseStatement, currentNLCsentenceInList->elseIfDetected, currentNLCsentenceInList->elseDetected, &previousCodeBlockInTree);
	#endif
	#endif
	#endif

	#ifdef NLC_DEBUG
	cout << "declareLocalPropertyListsForIndefiniteEntities{}: createCodeBlocksDeclareNewLocalListVariable for " << entity->entityName << endl;
	#endif	
	
	return result;
}

bool declareLocalPropertyListsForIndefiniteEntitiesValidClassChecks(GIAentityNode* entityNode)
{
	bool validClassContents = true;

	#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
	#ifdef NLC_USE_PREPROCESSOR
	if((entity->entityName == NLC_PREPROCESSOR_LOGICAL_CONDITION_DUMMY_TEXT_ACTION) || (entity->entityName == NLC_PREPROCESSOR_LOGICAL_CONDITION_DUMMY_TEXT_ACTION_OBJECT))
	{
		validClassContents = false;
	}
	#endif
	#endif
	#ifdef NLC_PREPROCESSOR_INTERPRET_SINGLE_WORD_SENTENCES_AS_ACTIONS
	if(entityNode->entityName == NLC_PREPROCESSOR_INTERPRET_SINGLE_WORD_SENTENCES_AS_ACTIONS_DUMMY_TEXT_ACTION_OBJECT)
	{
		validClassContents = false;	
	}
	#endif

	//added 1k7g
	if(isStringNumberOrFractional(entityNode->entityName))
	{
		validClassContents = false;
		//entityNode->disabled = true;	//this could be used instead (more general implementation)
	}
	
	return validClassContents;
}











#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
bool clearContextGeneratedVariable(vector<GIAentityNode*>* entityNodesActiveListComplete)
{
	bool result = true;
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode* entity = *entityIter;
		entity->NLCcontextGenerated = false;
	}
	return result;
}
#endif


#ifdef NLC_GENERATE_OBJECT_INITIALISATIONS_BASED_ON_SUBSTANCE_CONCEPTS_FOR_ALL_DEFINITE_ENTITIES
bool generateObjectInitialisationsBasedOnSubstanceConceptsForAllDefiniteEntities(NLCcodeblock** currentCodeBlockInTree, vector<GIAentityNode*>* entityNodesActiveListSentence, int sentenceIndex)
{
	bool result = true;
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListSentence->begin(); entityIter != entityNodesActiveListSentence->end(); entityIter++)
	{
		GIAentityNode* entity = (*entityIter);
		if(!checkSpecialCaseEntity(entity, true) && !(entity->isSubstanceQuality))
		{
			if(entity->sentenceIndexTemp == sentenceIndex)	//changed 1l15a
			//if(checkSentenceIndexParsingCodeBlocks(entity, sentenceIndex, false))
			{
				if(!(entity->disabled))
				{
					if(assumedToAlreadyHaveBeenDeclared(entity))
					{//definite entity found
						#ifdef NLC_DEBUG
						cout << "generateObjectInitialisationsBasedOnSubstanceConceptsForAllDefiniteEntities{}: entity: " << entity->entityName << endl;
						#endif
						generateObjectInitialisationsBasedOnSubstanceConcepts(entity, currentCodeBlockInTree, sentenceIndex, false);
					}
				}	
			}
		}
	}
	return result;
}
#endif


bool generateCodeBlocksPart3subjectObjectConnections(NLCcodeblock** currentCodeBlockInTree, vector<GIAentityNode*>* entityNodesActiveListSentence, int sentenceIndex, string NLCfunctionName, NLCsentence* currentNLCsentenceInList)
{
	bool result = true;
	
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListSentence->begin(); entityIter != entityNodesActiveListSentence->end(); entityIter++)
	{
		GIAentityNode* entity = (*entityIter);
		
		if(checkSentenceIndexParsingCodeBlocks(entity, sentenceIndex, false))
		{
			if(!checkConceptTypeEntity(entity))
			{
				#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
				if(!(entity->NLCparsedForlogicalConditionOperations))
				{
				#endif
					GIAentityNode* subjectEntity = NULL;
					GIAentityNode* objectEntity = NULL;
					GIAentityConnection* connection = NULL;

					bool foundSubject = false;
					bool foundObject = false;
					bool foundSubjectObjectConnection = false;

					int connectionType = -1;
	
					if(entity->isAction)
					{
						/*//CHECKTHIS;
						if(!(entity->isActionConcept))
						{
						*/
						#ifdef NLC_RECORD_ACTION_HISTORY_GENERALISABLE_DO_NOT_EXECUTE_PAST_TENSE_ACTIONS
						if(!isPotentialAction(entity))
						{
						#endif
							bool actionIsSingleWord = false;
							GIAentityConnection* actionSubjectConnection = NULL;
							if(getActionSubjectCheckSameReferenceSetAndSentence(entity, &subjectEntity, &actionSubjectConnection, sentenceIndex, false))
							{
								if(!(actionSubjectConnection->NLCparsedForCodeBlocks))	//added 1o3a (required if GIA adds identical entities to entityNodesActiveListSentence for a given sentenceIndex; eg during GIA_USE_ADVANCED_REFERENCING aliasing)
								{
									if(!checkConceptTypeEntity(subjectEntity))	//redundant
									{
										foundSubject = true;	
									}
								}
							}
							GIAentityConnection* actionObjectConnection = NULL;
							if(getActionObjectCheckSameReferenceSetAndSentence(entity, &objectEntity, &actionObjectConnection, sentenceIndex, false))
							{
								if(!(actionObjectConnection->NLCparsedForCodeBlocks))	//added 1o3a (required if GIA adds identical entities to entityNodesActiveListSentence for a given sentenceIndex; eg during GIA_USE_ADVANCED_REFERENCING aliasing)
								{
									if(!checkConceptTypeEntity(objectEntity))	//redundant
									{
										foundObject = true;
										#ifdef NLC_PREPROCESSOR_INTERPRET_SINGLE_WORD_SENTENCES_AS_ACTIONS
										if(objectEntity->entityName == NLC_PREPROCESSOR_INTERPRET_SINGLE_WORD_SENTENCES_AS_ACTIONS_DUMMY_TEXT_ACTION_OBJECT)
										{
											actionIsSingleWord = true;
											foundObject = false;
											objectEntity->disabled = true;	//prevent parsing of dummyActionObject
											actionIsSingleWord = true;
										}
										#endif	
									}
								}
							}
							if(foundSubject || foundObject || actionIsSingleWord)
							{
								foundSubjectObjectConnection = true;	
								connectionType = GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTIONS;
								
								//cout << "sentenceIndex = " << sentenceIndex << endl;
								if(generateCodeBlocksPart3subjectObjectConnection(currentCodeBlockInTree, sentenceIndex, entity, subjectEntity, objectEntity, connection, foundSubject, foundObject, connectionType))
								{
									if(foundSubject)
									{
										actionSubjectConnection->NLCparsedForCodeBlocks = true;	//added 1o3a
									}
									if(foundObject)
									{
										actionObjectConnection->NLCparsedForCodeBlocks = true;	//added 1o3a
									}
								}
							}
						#ifdef NLC_RECORD_ACTION_HISTORY_GENERALISABLE_DO_NOT_EXECUTE_PAST_TENSE_ACTIONS
						}
						#endif

						/*
						}
						*/
					}
					else if(entity->isCondition)
					{
						GIAentityConnection* conditionSubjectConnection = NULL;
						if(getConditionSubjectCheckSameReferenceSetAndSentence(entity, &subjectEntity, &conditionSubjectConnection, sentenceIndex, false))
						{
							if(!(conditionSubjectConnection->NLCparsedForCodeBlocks))	//added 1o3a (required if GIA adds identical entities to entityNodesActiveListSentence for a given sentenceIndex; eg during GIA_USE_ADVANCED_REFERENCING aliasing)
							{
								foundSubject = true;
							}
						}
						GIAentityConnection* conditionObjectConnection = NULL;
						if(getConditionObjectCheckSameReferenceSetAndSentence(entity, &objectEntity, &conditionObjectConnection, sentenceIndex, false))
						{
							if(!(conditionObjectConnection->NLCparsedForCodeBlocks))	//added 1o3a (required if GIA adds identical entities to entityNodesActiveListSentence for a given sentenceIndex; eg during GIA_USE_ADVANCED_REFERENCING aliasing)
							{
								foundObject = true;
							}
						}
						if(foundSubject && foundObject)
						{
							foundSubjectObjectConnection = true;	
							connectionType = GIA_ENTITY_VECTOR_CONNECTION_TYPE_CONDITIONS;

							if(generateCodeBlocksPart3subjectObjectConnection(currentCodeBlockInTree, sentenceIndex, entity, subjectEntity, objectEntity, connection, foundSubject, foundObject, connectionType))
							{
								conditionSubjectConnection->NLCparsedForCodeBlocks = true;	//added 1o3a
								conditionObjectConnection->NLCparsedForCodeBlocks = true;	//added 1o3a
							}
						}
					}
					else
					{
						for(vector<GIAentityConnection*>::iterator iter = entity->propertyNodeList->begin(); iter < entity->propertyNodeList->end(); iter++)
						{
							GIAentityConnection* propertyConnection = *iter;
							GIAentityNode* propertyEntity = propertyConnection->entity;
							if(checkSentenceIndexParsingCodeBlocks(propertyEntity, propertyConnection, sentenceIndex, false))
							{
								if(!(propertyConnection->sameReferenceSet))
								{
									if(!(propertyConnection->NLCparsedForCodeBlocks))	//added 1o3a (required if GIA adds identical entities to entityNodesActiveListSentence for a given sentenceIndex; eg during GIA_USE_ADVANCED_REFERENCING aliasing)
									{
										if(!checkConceptTypeEntity(propertyEntity))	//redundant
										{
											subjectEntity = entity;
											objectEntity = propertyEntity;
											foundSubject = true;
											foundObject = true;
											foundSubjectObjectConnection = true;	
											connectionType = GIA_ENTITY_VECTOR_CONNECTION_TYPE_PROPERTIES;
											connection = propertyConnection;

											if(generateCodeBlocksPart3subjectObjectConnection(currentCodeBlockInTree, sentenceIndex, entity, subjectEntity, objectEntity, connection, foundSubject, foundObject, connectionType))
											{
												propertyConnection->NLCparsedForCodeBlocks = true;	//added 1o3a
											}
										}
									}
								}
							}
						}

						for(vector<GIAentityConnection*>::iterator iter = entity->entityNodeDefinitionList->begin(); iter < entity->entityNodeDefinitionList->end(); iter++)
						{
							GIAentityConnection* definitionConnection = *iter;
							GIAentityNode* definitionEntity = definitionConnection->entity;
							if(checkSentenceIndexParsingCodeBlocks(definitionEntity, definitionConnection, sentenceIndex, false))
							{
								if(!(definitionConnection->sameReferenceSet))
								{
									if(!(definitionConnection->NLCparsedForCodeBlocks))	//added 1o3a (required if GIA adds identical entities to entityNodesActiveListSentence for a given sentenceIndex; eg during GIA_USE_ADVANCED_REFERENCING aliasing)
									{
										if(definitionEntity->entityName != entity->entityName)	//ignore these dream mode definition connections
										{
											subjectEntity = entity;
											objectEntity = definitionEntity;
											foundSubject = true;
											foundObject = false;
											foundSubjectObjectConnection = true;	
											connectionType = GIA_ENTITY_VECTOR_CONNECTION_TYPE_DEFINITIONS;
											connection = definitionConnection;

											if(generateCodeBlocksPart3subjectObjectConnection(currentCodeBlockInTree, sentenceIndex, entity, subjectEntity, objectEntity, connection, foundSubject, foundObject, connectionType))
											{
												definitionConnection->NLCparsedForCodeBlocks = true;	//added 1o3a
											}	
										}
									}
								}
							}
						}
					}

				#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
				}
				#endif	
			}
		}
	}
	
	return result;
}

bool generateCodeBlocksPart3subjectObjectConnection(NLCcodeblock** currentCodeBlockInTree, int sentenceIndex, GIAentityNode* entity, GIAentityNode* subjectEntity, GIAentityNode* objectEntity, GIAentityConnection* connection, bool foundSubject, bool foundObject, int connectionType)
{
	bool result = true;
	
	NLCcodeblock* firstCodeBlockInSentence = *currentCodeBlockInTree;
	
	NLCgenerateContextBlocksVariables generateContextBlocksVariables;
	GIAentityNode* subjectParentEntity = NULL;
	
	//entity->NLCparsedForCodeBlocks = true;
	if(connectionType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTIONS)
	{
		//initialise the action
		if(initialiseFunctionArguments(currentCodeBlockInTree, entity, sentenceIndex))
		{

		}
		entity->NLCcontextGeneratedTemp = true;
	}

	#ifdef NLC_DEBUG
	cout << "entity = " << entity->entityName << endl;
	cout << "entity->sentenceIndexTemp = " << entity->sentenceIndexTemp << endl;
	cout << "connectionType = " << entityVectorConnectionNameArray[connectionType] << endl;
	#endif

	bool addNewObjectForEachSubject = false;
	/*
	implement all/each;
		case 1: if detect "each"/"every"/"all" predeterminer and object is singular [REDUNDANT: or quantity entity] then add a new object for each subject
			eg Each player has a colour.
		case 2: if detect plural subject and indefinite plural object, then add a new object for each subject 
			eg Each player has 16 pieces.
			eg the players have pieces.
		case 3: if detect plural subject and quality object, then add a new object for each subject 
	*/
	if(connectionType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_PROPERTIES || connectionType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_CONDITIONS)
	{
		if(foundSubject && foundObject)
		{//this should always be the case for properties and conditions

			bool newInitialisationObject = false;
			generateContextBlocksVariables.getParentCheckLastParent = true;
			generateContextBlocksVariables.lastParent = subjectEntity;	//is this required? (designed for dual/two-way condition connections only)
			GIAentityNode* objectParentEntity = NULL;
			getParentAndInitialiseParentIfNecessaryOrGenerateContextBlocks(currentCodeBlockInTree, objectEntity, sentenceIndex, &generateContextBlocksVariables, false, &objectParentEntity, &newInitialisationObject, true);
			
			bool subjectEntityPredeterminerDetected = false;
			#ifdef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES			
			unordered_map<int,int>::iterator iterTemp = subjectEntity->grammaticalPredeterminerTempSentenceArray.find(sentenceIndex);
			if(iterTemp !=  subjectEntity->grammaticalPredeterminerTempSentenceArray.end())
			//if(subjectEntity->grammaticalPredeterminerTempSentenceArray.at(sentenceIndex) != -1)
			{
				//subjectEntityPredeterminerDetected = intInIntArray(grammaticalPredeterminerTempSentenceArray.at(sentenceIndex)->second, entityPredeterminerSmallArray, GRAMMATICAL_PREDETERMINER_SMALL_ARRAY_NUMBER_OF_TYPES);
				subjectEntityPredeterminerDetected = intInIntArray(iterTemp->second, entityPredeterminerSmallArray, GRAMMATICAL_PREDETERMINER_SMALL_ARRAY_NUMBER_OF_TYPES);
			}
			#else
			subjectEntityPredeterminerDetected = intInIntArray(subjectEntity->grammaticalPredeterminerTemp, entityPredeterminerSmallArray, GRAMMATICAL_PREDETERMINER_SMALL_ARRAY_NUMBER_OF_TYPES);
			#endif
			if(subjectEntityPredeterminerDetected && (objectEntity->grammaticalNumber != GRAMMATICAL_NUMBER_PLURAL))
			{
				addNewObjectForEachSubject = true;
			}
			if((subjectEntity->grammaticalNumber == GRAMMATICAL_NUMBER_PLURAL) && (objectEntity->grammaticalNumber == GRAMMATICAL_NUMBER_PLURAL) && newInitialisationObject)
			{
				addNewObjectForEachSubject = true;
			}
			if((subjectEntity->grammaticalNumber == GRAMMATICAL_NUMBER_PLURAL) && (objectEntity->isSubstanceQuality))
			{
				addNewObjectForEachSubject = true;
			}
		}
	}
		
	if(foundSubject)
	{
		#ifdef NLC_DEBUG
		cout << "subjectEntity = " << subjectEntity->entityName << endl;
		//cout << "\tobjectEntity = " << objectEntity->entityName << endl;
		#endif
		generateContextBlocksVariables.getParentCheckLastParent = true;
		generateContextBlocksVariables.lastParent = objectEntity;	//is this required? (designed for dual/two-way condition connections only)
		
		NLCcodeblock* codeBlockInTreeBeforeParseContext = *currentCodeBlockInTree;
		*currentCodeBlockInTree = createCodeBlocksDeclareNewCategoryListVariable(*currentCodeBlockInTree, subjectEntity, NLC_ITEM_TYPE_SUBJECTCATEGORY_VAR_APPENDITION);	//create new subject category list
		bool newInitialisationSubject = false;
		if(getParentAndInitialiseParentIfNecessaryOrGenerateContextBlocks(currentCodeBlockInTree, subjectEntity, sentenceIndex, &generateContextBlocksVariables, false, &subjectParentEntity, &newInitialisationSubject, false))
		{
			//if(!addNewObjectForEachSubject)	//optional (removes redundancy but lowers consistency)
			//{
			*currentCodeBlockInTree = createCodeBlockAddEntityToCategoryListCheckLastSentenceReferencedPluralExecuteFunction(*currentCodeBlockInTree, subjectEntity, subjectEntity, NLC_ITEM_TYPE_SUBJECTCATEGORY_VAR_APPENDITION);
			//}
		}
		
		if(!addNewObjectForEachSubject)
		{
			*currentCodeBlockInTree = getLastCodeBlockInLevel(codeBlockInTreeBeforeParseContext);	
		}
	}
	if(foundObject)
	{
		#ifdef NLC_DEBUG
		cout << "objectEntity = " << objectEntity->entityName << endl;
		#endif
		generateContextBlocksVariables.getParentCheckLastParent = true;
		generateContextBlocksVariables.lastParent = subjectEntity;

		NLCcodeblock* codeBlockInTreeBeforeParseContext = *currentCodeBlockInTree;
		*currentCodeBlockInTree = createCodeBlocksDeclareNewCategoryListVariable(*currentCodeBlockInTree, objectEntity, NLC_ITEM_TYPE_OBJECTCATEGORY_VAR_APPENDITION);	//create new object category list
		GIAentityNode* objectParentEntity = NULL;
		bool newInitialisationObject = false;
		if(getParentAndInitialiseParentIfNecessaryOrGenerateContextBlocks(currentCodeBlockInTree, objectEntity, sentenceIndex, &generateContextBlocksVariables, false, &objectParentEntity, &newInitialisationObject, false))
		{
			//if(!addNewObjectForEachSubject)	//optional (removes redundancy but lowers consistency)
			//{
			*currentCodeBlockInTree = createCodeBlockAddEntityToCategoryListCheckLastSentenceReferencedPluralExecuteFunction(*currentCodeBlockInTree, objectEntity, objectEntity, NLC_ITEM_TYPE_OBJECTCATEGORY_VAR_APPENDITION);
			//}
		}

		if(!addNewObjectForEachSubject)
		{
			*currentCodeBlockInTree = getLastCodeBlockInLevel(codeBlockInTreeBeforeParseContext);
		}
	}

	if(connectionType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTIONS)
	{
		entity->NLCcontextGeneratedTemp = false;
	}


	bool isPrimary = true;
	if(addNewObjectForEachSubject)
	{
		isPrimary = false;
	}
	if(generateCodeBlocksAddConnection(currentCodeBlockInTree, connectionType, connection, subjectEntity, objectEntity, entity, foundSubject, foundObject, sentenceIndex, subjectParentEntity, isPrimary))
	{

	}

	*currentCodeBlockInTree = getLastCodeBlockInLevel(firstCodeBlockInSentence);
	
	return result;
}


#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS
bool initialiseFunctionArguments(NLCcodeblock** currentCodeBlockInTree, GIAentityNode* actionEntity, int sentenceIndex)
{
	bool result = true;
	actionEntity->NLCisSingularArgument = true;	//added 1e2c

	//declare an "abstract" variable for the action (that will be filled with the its properties and conditions) and passed as an argument to the function; eg "fast" of "run fast"
	if(!generateObjectInitialisations(currentCodeBlockInTree, actionEntity, sentenceIndex))
	{
		result = false;
	}
	return result;
}
#endif















