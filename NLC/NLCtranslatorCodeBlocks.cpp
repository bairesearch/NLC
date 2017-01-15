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
 * Project Version: 1u1a 24-September-2016
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

	currentCodeBlockInTree = createCodeBlockNewFunction(currentCodeBlockInTree, NLCfunctionName, entityNodesActiveListComplete);

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
			bool logicalConditionBooleanStatementNegativeDetected = false;
			if(!generateCodeBlocksPart3subjectObjectConnections(&currentCodeBlockInTree, entityNodesActiveListSentence, sentenceIndex, false, &logicalConditionBooleanStatementNegativeDetected))
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


















