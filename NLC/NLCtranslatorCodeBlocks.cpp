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
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2016 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 1u12a 30-September-2016
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/


#include "NLCtranslatorCodeBlocks.h"
#include "NLCtranslatorCodeBlocksLogicalConditions.h"
#include "NLCtranslatorCodeBlocksLogicalConditionsAdvanced.h"
#include "NLCtranslatorCodeBlocksOperations.h"
#include "NLCprintDefs.h"	//required for NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION
#include "GIAtranslatorOperations.h"	//required for getPrimaryNetworkIndexNodeDefiningInstance()

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

	currentCodeBlockInTree = createCodeBlockNewFunction(currentCodeBlockInTree, NLCfunctionName, entityNodesActiveListComplete, currentNLCfunctionInList);

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
	//Part Prep A - declareLocalVariables (for non-specific indefinite entities, eg "a chicken") - added 1g8a;
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

		#ifdef NLC_DEBUG
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
		#endif

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
		//Part Prep A - declareLocalVariables (for non-specific indefinite entities, eg "a chicken") - added 1g8a;
		#ifdef NLC_DEBUG
		cout << "declareLocalPropertyListsForIndefiniteEntities:" << endl;
		#endif
		declareLocalPropertyListsForIndefiniteEntities(&currentCodeBlockInTree, entityNodesActiveListSentence, sentenceIndex, NLCfunctionName, currentNLCsentenceInList);	//added 1g8a 11-July-2014
		#endif
		#endif

		#ifdef NLC_GENERATE_OBJECT_INITIALISATIONS_BASED_ON_CONCEPTS_FOR_ALL_DEFINITE_ENTITIES
		#ifdef NLC_DEBUG
		cout << "generateObjectInitialisationsBasedOnConceptsForAllDefiniteEntities:" << endl;
		#endif
		generateObjectInitialisationsBasedOnConceptsForAllDefiniteEntities(&currentCodeBlockInTree, entityNodesActiveListSentence, sentenceIndex);
		#endif

		#ifdef NLC_PREPROCESSOR_MATH_REPLACE_NUMERICAL_VARIABLES_NAMES_FOR_NLP
		if(getUseNLCpreprocessor())
		{
			//reconcile temporary variable name replacement
			for(int i=0; i<currentNLCsentenceInList->variableNamesDetected.size(); i++)
			{
				if(!(currentNLCsentenceInList->isMath))
				{//only replace variables names (and reconcile temporary variable name replacement) for non math text
					int dummyNumber = generateDummyNumber(i+1);
					string numericalVariableName = currentNLCsentenceInList->variableNamesDetected[i];
					#ifdef NLC_DEBUG_PREPROCESSOR_MATH_REPLACE_NUMERICAL_VARIABLES
					cout << "currentNLCsentenceInList->sentenceContents = " << currentNLCsentenceInList->sentenceContents << endl;
					cout << "dummyNumber = " << dummyNumber << endl;
					cout << "numericalVariableName = " << numericalVariableName << endl;
					#endif
					if(!findDummyNumberAndReplaceWithOriginalNumericalVariableName(entityNodesActiveListSentence, sentenceIndex, dummyNumber, numericalVariableName))
					{
						cout << "generateCodeBlocks{} error: !findDummyNumberAndReplaceWithOriginalNumericalVariableName, dummyNumericalValueToRestore = " << dummyNumber << ", numericalVariableName = " << numericalVariableName << endl;
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

			#ifdef NLC_GENERATE_UNIQUE_CONTEXT_BLOCK_FOR_EACH_SENTENCE
			//added 1q10b - used prevent redeclarations of xSubjectCategoryList/xObjectCategoryList//xCategoryList
			//NB createCodeBlocksCreateContextBlock be executed after generateObjectInitialisationsBasedOnConceptsForAllDefiniteEntities because newlyDeclaredEntityInCategoryList=false is set (ie category lists are not created)
			NLCcodeblock* firstCodeBlockInSentence = currentCodeBlockInTree;
			currentCodeBlockInTree = createCodeBlocksCreateContextBlock(currentCodeBlockInTree);
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
			NLCgenerateContextBlocksVariables generateContextBlocksVariablesLogicalConditionStatement;	//not used
			if(!generateCodeBlocksPart3subjectObjectConnections(&currentCodeBlockInTree, entityNodesActiveListSentence, sentenceIndex, &generateContextBlocksVariablesLogicalConditionStatement))
			{
				result = false;
			}

			#ifdef NLC_GENERATE_UNIQUE_CONTEXT_BLOCK_FOR_EACH_SENTENCE
			currentCodeBlockInTree = firstCodeBlockInSentence->next;
			#endif

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
						sentenceIter++;	//go to last sentence in list (finish parsing full sentences)
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
				sentenceIter++;	//standard iteration - go to last sentence in list (finish parsing full sentences)?
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
			sentenceIter++;	//standard iteration
		}
		#else
		sentenceIter++;	//standard iteration
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
		#ifdef NLC_DO_NOT_PREDECLARE_LOCAL_LISTS_FOR_QUALITIES
		if(!checkSpecialCaseEntity(entity, true) && !(entity->entityType == GIA_ENTITY_TYPE_TYPE_QUALITY))
		#else
		if(!checkSpecialCaseEntity(entity, true))
		#endif
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

	//added 1q14e
	if(isStringAliasFileName(entityNode->entityName))
	{
		validClassContents = false;
	}

	#ifdef NLC_VERIFY_LEGAL_TARGET_SOURCE_CHARACTERS
	//added 1q14e - CHECKTHIS: is this required?
	if(isStringIllegalTargetSourceCharacter(entityNode->entityName))
	{
		if(validClassContents)
		{
			cout << "declareLocalPropertyListsForIndefiniteEntitiesValidClassChecks{} error: isStringIllegalTargetSourceCharacter; entityNode->entityName = " << entityNode->entityName << endl;
		}
		validClassContents = false;
	}
	#endif

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


#ifdef NLC_GENERATE_OBJECT_INITIALISATIONS_BASED_ON_CONCEPTS_FOR_ALL_DEFINITE_ENTITIES
bool generateObjectInitialisationsBasedOnConceptsForAllDefiniteEntities(NLCcodeblock** currentCodeBlockInTree, vector<GIAentityNode*>* entityNodesActiveListSentence, int sentenceIndex)
{
	bool result = true;
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListSentence->begin(); entityIter != entityNodesActiveListSentence->end(); entityIter++)
	{
		GIAentityNode* entity = (*entityIter);
		if(!checkSpecialCaseEntity(entity, true) && !(entity->entityType == GIA_ENTITY_TYPE_TYPE_QUALITY))
		{
			if(entity->sentenceIndexTemp == sentenceIndex)	//changed 1l15a
			//if(checkSentenceIndexParsingCodeBlocks(entity, sentenceIndex, false))
			{
				if(!(entity->disabled))
				{
					if(assumedToAlreadyHaveBeenDeclared(entity))
					{//definite entity found
						#ifdef NLC_DEBUG
						cout << "generateObjectInitialisationsBasedOnConceptsForAllDefiniteEntities{}: entity: " << entity->entityName << endl;
						#endif
						generateObjectInitialisationsBasedOnConcepts(entity, entity, currentCodeBlockInTree, sentenceIndex, false);
					}
				}
			}
		}
	}
	return result;
}
#endif


NLCcodeblock* createCodeBlockNewFunction(NLCcodeblock* currentCodeBlockInTree, string NLCfunctionName, vector<GIAentityNode*>* entityNodesActiveListComplete, NLCfunction* currentNLCfunctionInList)
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
		if(!(entity->entityType == GIA_ENTITY_TYPE_TYPE_NETWORK_INDEX) && !(entity->entityType == GIA_ENTITY_TYPE_TYPE_CONCEPT))
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
			#ifdef NLC_DEBUG
			//cout << "functionObjectName2 = " << functionObjectName << endl;
			#endif
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
	generateLocalFunctionArgumentsBasedOnImplicitDeclarations(entityNodesActiveListComplete, &(currentCodeBlockInTree->parameters), currentNLCfunctionInList);
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



#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS
void generateLocalFunctionArgumentsBasedOnImplicitDeclarations(vector<GIAentityNode*>* entityNodesActiveListComplete, vector<NLCitem*>* parameters, NLCfunction* currentNLCfunctionInList)
{
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode* entity = *entityIter;
		if(isDefiniteEntityInitialisation(entity, currentNLCfunctionInList))
		{
			#ifdef NLC_DEBUG
			//cout << "isDefiniteEntityInitialisation, entity = " << entity->entityName << endl;
			#endif

			#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS_SUPPORT_LOCAL_LISTS_USE_CLASS_NAMES
			if(!findIndefiniteEntityCorrespondingToDefiniteEntityInSameContext(entityNodesActiveListComplete, entity))	//NB findIndefiniteEntityCorrespondingToDefiniteEntityInSameContext() could be reimplemented to be performed during generateCodeBlocks() sentence parsing, but then generateLocalFunctionArgumentsBasedOnImplicitDeclarations() could not be decared at start of generateCodeBlocks(), ie it would have to be moved out of createCodeBlockNewFunction()
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
					#ifdef NLC_TRANSLATOR_INTERPRET_PROPERNOUNS_WITH_DEFINITION_LINK_AS_NEWLY_DECLARED
					if(!findPropernounDefinitionLink(entityNodesActiveListComplete, entity))
					{
					#endif
						#ifdef NLC_USE_ADVANCED_REFERENCING
						NLCitem* functionArgumentTemp = NULL;
						if(!findFunctionArgument(parameters, entity, NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_INSTANCE_OR_CLASS_LIST, &functionArgumentTemp))
						{
						#endif
							#ifdef NLC_DEBUG
							//cout << "generateLocalFunctionArgumentsBasedOnImplicitDeclarations: entity->entityName = " << entity->entityName << endl;
							#endif
							//detected "the x" without declaring x (ie implicit declaration)
							NLCitem* thisFunctionArgumentInstanceItem = new NLCitem(entity, NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_INSTANCE_OR_CLASS_LIST);
							parameters->push_back(thisFunctionArgumentInstanceItem);

							//added 1j5d
							#ifdef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES
							entity->NLClocalListVariableHasBeenDeclared = true;	//redundant
							#else
							GIAentityNode* networkIndexEntity = getPrimaryNetworkIndexNodeDefiningInstance(entity);
							if(!(networkIndexEntity->NLClocalListVariableHasBeenDeclared))	//redundant test
							{
								entity->NLClocalListVariableHasBeenDeclared = true;
								networkIndexEntity->NLClocalListVariableHasBeenDeclared = true;
							}
							#endif
						#ifdef NLC_USE_ADVANCED_REFERENCING
						}
						#endif
					#ifdef NLC_TRANSLATOR_INTERPRET_PROPERNOUNS_WITH_DEFINITION_LINK_AS_NEWLY_DECLARED
					}
					#endif
				#ifdef NLC_USE_ADVANCED_REFERENCING_SUPPORT_ALIASES
				}
				#endif
			#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS_SUPPORT_LOCAL_LISTS_USE_CLASS_NAMES
			}
			#endif
		}
	}
}


bool isDefiniteEntityInitialisation(GIAentityNode* entity, NLCfunction* currentNLCfunctionInList)
{
	bool foundDefiniteEntity = false;
	
	#ifdef NLC_TRANSLATOR_LOGICAL_CONDITIONS_BOOLEAN_STATEMENTS_INTERPRET_SUBJECT_AND_OBJECT_INDEPENDENTLY_SUPPORT_INDEFINITE_SUBJECT_PASS_AS_FUNCTION_ARGUMENT
	bool isLogicalConditionIndefiniteSubjectEntity = false;
	if(!isDefiniteEntity(entity))
	{
		if(entity->entityType == GIA_ENTITY_TYPE_TYPE_SUBSTANCE)
		{
			NLCsentence* sentence = NULL;
			if(getSentenceInFunction(entity, currentNLCfunctionInList, &sentence))
			{
				if(sentencePertainsToLogicalCondition(sentence))
				{
					bool entityIsEffectiveSubject = false;

					bool foundAction = false;
					bool foundActionIncoming = false;
					bool foundChildEntity = false;
					int sentenceIndex = entity->sentenceIndexTemp;
					GIAentityNode* childEntity = getSameReferenceSetSubstanceNonQualityChild(entity, sentenceIndex, &foundChildEntity);

					GIAentityNode* targetEntity = NULL;
					GIAentityConnection* connection = NULL;
					if(getEntityCheckSameReferenceSetAndSentence(childEntity, &targetEntity, &connection, sentenceIndex, false, GIA_ENTITY_VECTOR_CONNECTION_TYPE_CONDITIONS))
					{
						entityIsEffectiveSubject = true;
					}
					else if(getEntityCheckSameReferenceSetAndSentence(childEntity, &targetEntity, &connection, sentenceIndex, false, GIA_ENTITY_VECTOR_CONNECTION_TYPE_PROPERTIES))
					{
						entityIsEffectiveSubject = true;
					}
					else if(getEntityCheckSameReferenceSetAndSentence(childEntity, &targetEntity, &connection, sentenceIndex, false, GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTIONS))
					{
						entityIsEffectiveSubject = true;
					}
					else if(getEntityCheckSameReferenceSetAndSentence(entity, &targetEntity, &connection, sentenceIndex, false, GIA_ENTITY_VECTOR_CONNECTION_TYPE_INCOMING_ACTIONS))
					{
						foundActionIncoming = true;
						GIAentityNode* actionSubject = NULL;
						GIAentityConnection* actionSubjectConnection = NULL;
						if(!getEntityCheckSameReferenceSetAndSentence(targetEntity, &actionSubject, &actionSubjectConnection, sentenceIndex, false, GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTION_SUBJECT))
						{
							entityIsEffectiveSubject = true;	//this is required to sync with generateCodeBlocksPart3subjectObjectConnection implementation
						}
					}
					
					if(entityIsEffectiveSubject)
					{
						isLogicalConditionIndefiniteSubjectEntity = true;
					}
				}
			}
		}
	}
	if(isDefiniteEntity(entity) || isLogicalConditionIndefiniteSubjectEntity)
	#else
	if(isDefiniteEntity(entity))
	#endif
	{
		if(!(entity->entityType == GIA_ENTITY_TYPE_TYPE_NETWORK_INDEX))
		{
			#ifdef NLC_SUPPORT_INPUT_FUNCTION_LISTS
			if(!entity->NLCisSingularArgument)
			{
			#endif
				if(generateLocalFunctionArgumentsBasedOnImplicitDeclarationsValidClassChecks(entity))
				{
					foundDefiniteEntity = true;
				}
			#ifdef NLC_SUPPORT_INPUT_FUNCTION_LISTS
			}
			#endif
		}
	}
	return foundDefiniteEntity;
}

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
	if(entityNode->entityType == GIA_ENTITY_TYPE_TYPE_CONCEPT)
	{
		validClass = false;
	}

	return validClass;
}

bool getSentenceInFunction(GIAentityNode* entity, NLCfunction* currentNLCfunctionInList, NLCsentence** sentenceFound)
{
	bool result = false;
	NLCsentence* currentNLCsentence = currentNLCfunctionInList->firstNLCsentenceInFunction;
	while(currentNLCsentence->next != NULL)
	{
		if(currentNLCsentence->sentenceIndex == entity->sentenceIndexTemp)	//NB entity->sentenceIndexTemp can be tested here as entities within logical conditions are not advanced referenced (even if GIA advance referencing is enabled)
		{
			*sentenceFound = currentNLCsentence;
			result = true;
		}
		
		currentNLCsentence = currentNLCsentence->next;
	}
	
	return result;
}



#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS_SUPPORT_LOCAL_LISTS_USE_CLASS_NAMES
bool findIndefiniteEntityCorrespondingToDefiniteEntityInSameContext(vector<GIAentityNode*>* entityNodesActiveListComplete, GIAentityNode* definiteEntity)
{
	bool foundIndefiniteEntity = false;

	#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS_SUPPORT_LOCAL_LISTS_USE_CLASS_NAMES_ADVANCED

	/*
	NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS_SUPPORT_LOCAL_LISTS_USE_CLASS_NAMES_ADVANCED:
	Is designed for the following scenario;
		A red car.
		The green car...
	But fails in this scenario;
		A car is next to the house.
		The car is red.
		The green/red car...

	PLANNED SOLUTION (TEMPORARY WORKAROUND): disable NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS_SUPPORT_LOCAL_LISTS_USE_CLASS_NAMES_ADVANCED and do not support this scenario.
	If it must either be passed to the function as the function object, or referenced first within the function (or block), ie;
		The green car...
		A car is next to the house.
		The car is red.
	*/

	int referenceSetID = 0;
	//see identifyReferenceSetsSpecificConceptsAndLinkWithConcepts()

	int minimumEntityIndexOfReferenceSet = definiteEntity->entityIndexTemp;

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
		#endif
		referenceTraceParameters.ensureSameReferenceSetQueryConnections = true;	//added 1n28b

		#ifdef GIA_QUERY_SIMPLIFIED_SEARCH_ENFORCE_EXACT_MATCH
		int irrelevant;
		string printEntityNodeString = "";
		int maxNumberOfMatchedNodesPossible = 0;
		bool traceInstantiations = GIA_QUERY_TRACE_NETWORK_INDEX_NODES_DEFINING_INSTANTIATIONS_VALUE;
		traceEntityNode(firstNodeNetworkIndexEntityNodesListQuery, GIA_QUERY_TRACE_ENTITY_NODES_FUNCTION_DETERMINE_MAX_NUMBER_MATCHED_NODES_SAME_SET_ONLY, &maxNumberOfMatchedNodesPossible, NULL, false, referenceSetID, traceInstantiations);
		traceEntityNode(currentQueryEntityNode, GIA_QUERY_TRACE_ENTITY_NODES_FUNCTION_RESET_TESTEDFORQUERYCOMPARISONTEMP, &irrelevant, &printEntityNodeString, false, NULL, traceInstantiations);
		#endif

		for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
		{
			GIAentityNode* indefiniteEntity = *entityIter;

			#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS_USE_MORE_PRECISE_BUT_REDUNDANT_FUNCTIONS
			if(!assumedToAlreadyHaveBeenDeclaredInitialisation(indefiniteEntity))
			#else
			if(!assumedToAlreadyHaveBeenDeclared(indefiniteEntity))
			#endif
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
				bool traceInstantiations = GIA_QUERY_TRACE_NETWORK_INDEX_NODES_DEFINING_INSTANTIATIONS_VALUE;
				traceEntityNode(definiteEntity, GIA_QUERY_TRACE_ENTITY_NODES_FUNCTION_RESET_TESTEDFORQUERYCOMPARISONTEMP, &irrelevant, &printEntityNodeString, false, NULL, traceInstantiations);
				traceEntityNode(indefiniteEntity, GIA_QUERY_TRACE_ENTITY_NODES_FUNCTION_RESET_TESTEDFORQUERYCOMPARISONTEMP, &irrelevant, &printEntityNodeString, false, NULL, traceInstantiations);

			}
		}
		referenceSetID	= referenceSetID + 1;
	}
	#else
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode* entity = *entityIter;
		if(isIndefiniteEntityCorrespondingToDefiniteEntityInSameContext(entity, definiteEntity))
		{
			foundIndefiniteEntity = true;
		}
	}
	#endif
	return foundIndefiniteEntity;
}

bool isIndefiniteEntityCorrespondingToDefiniteEntityInSameContext(GIAentityNode* indefiniteEntity, GIAentityNode* definiteEntity)
{
	bool foundIndefiniteEntity = false;

	if(indefiniteEntity->entityName == definiteEntity->entityName)
	{
		if(!(indefiniteEntity->entityType == GIA_ENTITY_TYPE_TYPE_CONCEPT))
		{
			#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS_USE_MORE_PRECISE_BUT_REDUNDANT_FUNCTIONS
			if(!assumedToAlreadyHaveBeenDeclaredInitialisation(indefiniteEntity))
			#else
			if(!assumedToAlreadyHaveBeenDeclared(indefiniteEntity))
			#endif
			{
				if(((indefiniteEntity->grammaticalNumber == GRAMMATICAL_NUMBER_SINGULAR) && (definiteEntity->grammaticalNumber == GRAMMATICAL_NUMBER_SINGULAR)) || (indefiniteEntity->grammaticalNumber == GRAMMATICAL_NUMBER_PLURAL))
				{
					int indentationDifferenceFound = INT_DEFAULT_VALUE;	//not used
					if(checkIndefiniteEntityCorrespondingToDefiniteEntityInSameContext(indefiniteEntity, definiteEntity, &indentationDifferenceFound))
					{
						foundIndefiniteEntity = true;
						#ifdef NLC_DEBUG
						/*
						cout << "\nisIndefiniteEntityCorrespondingToDefiniteEntityInSameContext, indefiniteEntity = " << indefiniteEntity->entityName << endl;
						cout << "isIndefiniteEntityCorrespondingToDefiniteEntityInSameContext, definiteEntity = " << definiteEntity->entityName << endl;
						cout << "indefiniteEntity->sentenceIndexTemp = " << indefiniteEntity->sentenceIndexTemp << endl;
						cout << "definiteEntity->sentenceIndexTemp = " << definiteEntity->sentenceIndexTemp << endl;
						*/
						#endif
					}
				}
			}
		}
	}

	return foundIndefiniteEntity;
}
#endif

#ifdef NLC_TRANSLATOR_INTERPRET_PROPERNOUNS_WITH_DEFINITION_LINK_AS_NEWLY_DECLARED
bool findPropernounDefinitionLink(vector<GIAentityNode*>* entityNodesActiveListComplete, GIAentityNode* definiteEntity)
{
	//find a propernoun of the same name with a definition link within the context (function)
	//requirements: this function assumes that it will also be tested that the propernoun is not an alias
	bool foundPropernounDefinitionLink = false;
	if(definiteEntity->grammaticalProperNounTemp)
	{
		GIAentityNode* firstReferenceToPropernounInContext = NULL;
		int firstReferenceToPropernounInContextSentenceIndex = NLC_MAX_NUMBER_SENTENCES_PER_FUNCTION;
		for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
		{
			GIAentityNode* entity = *entityIter;
			if(entity->entityType != GIA_ENTITY_TYPE_TYPE_NETWORK_INDEX)	//added 1u9a
			{
				if(entity->entityName == definiteEntity->entityName)
				{
					if(entity->grammaticalProperNounTemp)
					{
						if(entity->sentenceIndexTemp < firstReferenceToPropernounInContextSentenceIndex)
						{
							//NB this method doesn't support multiple declarations of a given propernoun in a given context (function)
							firstReferenceToPropernounInContextSentenceIndex = entity->sentenceIndexTemp;
							firstReferenceToPropernounInContext = entity;
						}
						for(vector<GIAentityConnection*>::iterator entityNodeDefinitionListIterator = entity->entityNodeDefinitionList->begin(); entityNodeDefinitionListIterator < entity->entityNodeDefinitionList->end(); entityNodeDefinitionListIterator++)
						{
							GIAentityConnection* definitionConnection = (*entityNodeDefinitionListIterator);
							GIAentityNode* definitionEntity = definitionConnection->entity;
							if(definitionEntity->entityType == GIA_ENTITY_TYPE_TYPE_CONCEPT)
							{
								if(definitionEntity->entityName != entity->entityName)	//ignore dream mode definitions connections
								{
									//if NLC ref, verify sentence index TODO
									//eg Africa is a country. Africa has a castle with knights.
									foundPropernounDefinitionLink = true;
								}
							}
						}
					}
				}
			}
		}
		if(foundPropernounDefinitionLink)
		{
			firstReferenceToPropernounInContext->NLCfirstInstanceOfProperNounInContext = true;	//so that the entity will be interpreted as a new declaration by isDefiniteEntity
		}
	}
	return foundPropernounDefinitionLink;
}
#endif


#endif
















