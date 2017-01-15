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
 * Project: Natural Language Programming Interface (compiler)
 * Project Version: 1n9c 25-January-2015
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/



#include <ctime>
#include <cstdlib>	//for random number generation
#include <cmath>

#include "NLCtranslatorCodeBlocks.h"
#include "NLCtranslatorCodeBlocksLogicalConditions.h"
#include "NLCtranslatorCodeBlocksLogicalConditionsAdvanced.h"
#include "NLCtranslatorCodeBlocksOperations.h"
#include "NLCprintDefs.h"	//required for NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION

bool generateCodeBlocks(NLCcodeblock * firstCodeBlockInTree, vector<GIAentityNode*> * entityNodesActiveListComplete, int maxNumberSentences, string NLCfunctionName, NLCfunction * currentNLCfunctionInList)
{
	bool result = true;

	NLCcodeblock * currentCodeBlockInTree = firstCodeBlockInTree;

	#ifdef NLC_NOT_NECESSARY
	vector<NLCitem *> implictlyDeclaredFunctionList;	//implictlyDeclaredFunctionList is used to capture implicitly declared functions; to be added to object class definitions at end
	vector<NLCitem *> implictlyDeclaredFunctionListTopLevel;	//top level function list (used to store implicitly declared functions without subject/context/owner)
	#endif
	
	#ifdef NLC_USE_ADVANCED_REFERENCING_SUPPORT_ALIASES_PREVENT_ADDING_AS_FUNCTION_ARGUMENT
	#ifndef NLC_USE_ADVANCED_REFERENCING_SUPPORT_ALIASES_CROSS_FUNCTION_ALIASES
	#ifdef NLC_DEBUG
	cout << "generateCodeBlocks(): initialiseFunctionAliasClassList:" << endl;
	#endif
	initialiseFunctionAliasClassList();
	#endif
	#ifdef NLC_DEBUG
	cout << "generateCodeBlocks(): fillFunctionAliasClassList:" << endl;
	#endif
	fillFunctionAliasClassList(&currentCodeBlockInTree, entityNodesActiveListComplete);
	#endif
	
	currentCodeBlockInTree = createCodeBlockNewFunction(currentCodeBlockInTree, NLCfunctionName, entityNodesActiveListComplete, (currentNLCfunctionInList->firstNLCsentenceInFunction));

	//#ifdef NLC_USE_PREPROCESSOR
	NLCsentence * currentNLCsentenceInList = currentNLCfunctionInList->firstNLCsentenceInFunction;
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
	cout << "generateCodeBlocks(): declareLocalPropertyListsForIndefiniteEntities:" << endl;
	#endif
	declareLocalPropertyListsForIndefiniteEntities(&currentCodeBlockInTree, entityNodesActiveListComplete, 0, NLCfunctionName, currentNLCsentenceInList);
	#endif
	#endif
	
	#ifdef NLC_DEBUG
	cout << "generateCodeBlocks(): maxNumberSentences = " << maxNumberSentences << endl;
	#endif
	int sentenceIndex=GIA_NLP_START_SENTENCE_INDEX;
	while(sentenceIndex <= maxNumberSentences)
	{
		#ifdef NLC_DEBUG
		cout << "generateCodeBlocks(): sentenceIndex = " << sentenceIndex << endl;
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
		//Part Prep A - declareLocalVariables (for non-specific indefinte entities, eg "a chicken", not "a blue chicken") - added 1g8a;
		#ifdef NLC_DEBUG
		cout << "declareLocalPropertyListsForIndefiniteEntities:" << endl;
		#endif
		declareLocalPropertyListsForIndefiniteEntities(&currentCodeBlockInTree, entityNodesActiveListComplete, sentenceIndex, NLCfunctionName, currentNLCsentenceInList);	//added 1g8a 11-July-2014
		#endif
		#endif
		
		#ifdef NLC_USE_ADVANCED_REFERENCING_SUPPORT_ALIASES
		#ifdef NLC_DEBUG
		cout << "identifyAliasesInCurrentSentence:" << endl;
		#endif
		identifyAliasesInCurrentSentence(&currentCodeBlockInTree, entityNodesActiveListComplete, sentenceIndex);
		#endif
		
		#ifdef NLC_GENERATE_OBJECT_INITIALISATIONS_BASED_ON_SUBSTANCE_CONCEPTS_FOR_ALL_DEFINITE_ENTITIES
		#ifdef NLC_DEBUG
		cout << "generateObjectInitialisationsBasedOnSubstanceConceptsForAllDefiniteEntities:" << endl;
		#endif
		generateObjectInitialisationsBasedOnSubstanceConceptsForAllDefiniteEntities(&currentCodeBlockInTree, entityNodesActiveListComplete, sentenceIndex);
		#endif
		
		#ifdef NLC_MARK_ACTION_SUBJECT_OBJECT_INDEFINITE_ENTITY_ACTIONS_AS_NOT_SAME_REFERENCE_SET
		#ifdef NLC_DEBUG
		cout << "markActionSubjectObjectIndefiniteEntityActionsAsNotSameReferenceSet:" << endl;
		#endif
		markActionSubjectObjectIndefiniteEntityActionsAsNotSameReferenceSet(&currentCodeBlockInTree, entityNodesActiveListComplete, sentenceIndex);
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
					if(!findAndSetDummyNumericalValueForReplacement(entityNodesActiveListComplete, sentenceIndex, dummyNumericalValue, numericalVariableName))
					{
						cout << "generateCodeBlocks() error: !findAndSetDummyNumericalValueForReplacement, dummyNumericalValueToRestore = " << dummyNumericalValue << ", numericalVariableName = " << numericalVariableName << endl;
					}
				}
				else
				{
					cout << "generateCodeBlocks() error: currentNLCsentenceInList->variableNamesDetected && currentNLCsentenceInList->isMath" << endl;
				}
			}
		}
		#endif
		
		#ifdef NLC_PREPROCESSOR_MATH
		if(getUseNLCpreprocessor() && (currentNLCsentenceInList->isMath))
		{
			#ifdef NLC_DEBUG_PREPROCESSOR_MATH
			cout << "generateCodeBlocksFromMathText(): currentNLCsentenceInList->mathText = " << currentNLCsentenceInList->mathText << endl;
			#endif
			
			//generateCodeBlocksFromMathText (including logical conditions) - added 1h1d;
			#ifdef NLC_DEBUG
			cout << "generateCodeBlocksFromMathText:" << endl;
			#endif
			if(!generateCodeBlocksFromMathText(&currentCodeBlockInTree, entityNodesActiveListComplete, sentenceIndex, currentNLCsentenceInList, NLCfunctionName))
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
			if(!generateCodeBlocksPart2logicalConditions(&currentCodeBlockInTree, entityNodesActiveListComplete, sentenceIndex, NLCfunctionName, currentNLCsentenceInList))
			{
				result = false;
			}
			#endif

			//Part 3; actions (eg Tom rides the boat)
			#ifdef NLC_DEBUG
			cout << "generateCodeBlocksPart3actions:" << endl;
			#endif
			if(!generateCodeBlocksPart3actions(&currentCodeBlockInTree, entityNodesActiveListComplete, sentenceIndex, NLCfunctionName, currentNLCsentenceInList))
			{
				result = false;
			}

			//Part 4: object initialisations (eg Tom has a boat) [without actions]
			#ifdef NLC_DEBUG
			cout << "generateCodeBlocksPart4objectInitialisations:" << endl;
			#endif
			if(!generateCodeBlocksPart4objectInitialisations(&currentCodeBlockInTree, entityNodesActiveListComplete, sentenceIndex, NLCfunctionName))
			{
				result = false;
			}
			
			#ifdef NLC_SUPPORT_REDEFINITIONS
			//Part 4: redefinitions (eg The dog is an Alsation)
			#ifdef NLC_DEBUG
			cout << "generateCodeBlocksPart5redefinitions:" << endl;
			#endif
			if(!generateCodeBlocksPart5redefinitions(&currentCodeBlockInTree, entityNodesActiveListComplete, sentenceIndex, NLCfunctionName))
			{
				result = false;
			}
			#endif
			
		#ifdef NLC_PREPROCESSOR_MATH
		}
		#endif

		#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
		clearContextGeneratedVariable(entityNodesActiveListComplete);
		#endif


		#ifdef NLC_USE_PREPROCESSOR
		if(getUseNLCpreprocessor())
		{	
			if(currentNLCsentenceInList->next != NULL)
			{
				#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
				NLCsentence * nextNLCfullSentenceInList = currentNLCsentenceInList->next;
				bool currentSentenceContainsLogicalCondition = getCurrentSentenceContainsLogicalCondition();
				int currentLogicalConditionLevel = getCurrentLogicalConditionLevel();
				#elif defined NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
				NLCsentence * nextNLCfullSentenceInList = currentNLCsentenceInList;
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
						cout << "NLC_USE_PREPROCESSOR generateCodeBlocks() error: invalid indentation of nextNLCfullSentenceInList, sentenceIndex = " << sentenceIndex << endl;
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
						cout << "NLC_USE_PREPROCESSOR generateCodeBlocks() error: invalid indentation of currentNLCsentenceInList->next, sentenceIndex = " << sentenceIndex << endl;
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
					cout << "NLC_USE_PREPROCESSOR generateCodeBlocksPart2logicalConditions() error: invalid indentation of nextNLCfullSentenceInList, sentenceIndex = " << sentenceIndex << endl;
					cout << "nextNLCfullSentenceInList->indentation > currentNLCsentenceInList->indentation + 1" << endl;
					cout << "currentNLCsentenceInList->indentation = " << currentNLCsentenceInList->indentation << endl;
					cout << "nextNLCfullSentenceInList->indentation = " << nextNLCfullSentenceInList->indentation << endl;
				}
				
				if(nextNLCfullSentenceInList->next != NULL)
				{	
					sentenceIndex = nextNLCfullSentenceInList->sentenceIndex;
				}
				else
				{
					sentenceIndex = maxNumberSentences+1;
				}
				currentNLCsentenceInList = nextNLCfullSentenceInList;
				#ifdef NLC_DEBUG
				//cout << "next sentenceIndex = " << sentenceIndex << endl;
				#endif
			}
			else
			{
				sentenceIndex++;
				#ifdef NLC_DEBUG
				//cout << "NLC_USE_PREPROCESSOR generateCodeBlocks(): currentNLCsentenceInList->next == NULL, sentenceIndex = " << sentenceIndex << endl;
				#endif
			}
			#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
			setCurrentSentenceContainsLogicalCondition(false);
			#endif
		}
		else
		{
			sentenceIndex++;
		}
		#else
		sentenceIndex++;
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

#ifdef NLC_MARK_ACTION_SUBJECT_OBJECT_INDEFINITE_ENTITY_ACTIONS_AS_NOT_SAME_REFERENCE_SET
bool markActionSubjectObjectIndefiniteEntityActionsAsNotSameReferenceSet(NLCcodeblock ** currentCodeBlockInTree, vector<GIAentityNode*> * entityNodesActiveListComplete, int sentenceIndex)
{
	bool result = true;
	//e.g. "a chicken" in "A chicken that ate a pie rows the boat."/"A chicken that ate the pie rows the boat" - set all actions as !sameReferenceSet such that they are not parsed by future references to generateContextBlocks(), but are instead treated as actions
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode * actionEntity = (*entityIter);
		if(actionEntity->isAction)
		{
			if(!(actionEntity->isActionConcept))	//CHECKTHIS
			{
				for(vector<GIAentityConnection*>::iterator iter = actionEntity->actionSubjectEntity->begin(); iter < actionEntity->actionSubjectEntity->end(); iter++)
				{
					GIAentityConnection * actionSubjectConnection = *iter;
					GIAentityNode * actionSubjectEntity = actionSubjectConnection->entity;
					if(!assumedToAlreadyHaveBeenDeclared(actionSubjectEntity))
					{//indefinite action subject entity found
						if(actionSubjectConnection->sameReferenceSet)
						{
							//Only perform markActionSubjectObjectIndefiniteEntityActionsAsNotSameReferenceSet for the first sentence in which the action is defined. Although not required for !NLC_LOCAL_LISTS_USE_INSTANCE_NAMES (as actions are never assigned connections across multiple sentence indices), this is critically important for NLC_LOCAL_LISTS_USE_INSTANCE_NAMES (ie GIA_ADVANCED_REFERENCING); eg to prevent the action connections in the second sentence of "A chicken that ate a pie rows the boat. The chicken that ate the pie is happy." from being changed to !sameReferenceSet 
							if(actionEntity->sentenceIndexTemp == actionSubjectConnection->sentenceIndexTemp) 
							{
								bool hasSameSentenceSameReferenceSetActionObject = false;
								bool hasSameSentenceSameReferenceSetIndefiniteActionObject = false;
								for(vector<GIAentityConnection*>::iterator iter = actionEntity->actionObjectEntity->begin(); iter < actionEntity->actionObjectEntity->end(); iter++)
								{
									GIAentityConnection * actionObjectConnection = *iter;
									GIAentityNode * actionObjectEntity = actionObjectConnection->entity;
									if(actionObjectConnection->sentenceIndexTemp == actionSubjectConnection->sentenceIndexTemp)
									{
										if(actionObjectConnection->sameReferenceSet)
										{
											hasSameSentenceSameReferenceSetActionObject = true;
											if(!assumedToAlreadyHaveBeenDeclared(actionObjectEntity))
											{//indefinite action subject entity found
												//e.g. "A chicken that ate a pie rows the boat." [not: "A chicken that ate the pie rows the boat." as the context of "the pie" will be parsed by generateContextBlocks()]
												actionObjectConnection->sameReferenceSet = false;
												#ifdef NLC_DEBUG
												cout << "markActionSubjectObjectIndefiniteEntityActionsAsNotSameReferenceSet() 1: actionObjectEntity = " << actionObjectEntity->entityName << ", action = " << actionEntity->entityName << endl;
												#endif
												hasSameSentenceSameReferenceSetIndefiniteActionObject = true;
											}
										}
									}
								}
								if(!hasSameSentenceSameReferenceSetActionObject || hasSameSentenceSameReferenceSetIndefiniteActionObject)
								{
									//e.g. "A chicken that ate rows the boat."/"A chicken that ate a pie rows the boat."
									actionSubjectConnection->sameReferenceSet = false;
									#ifdef NLC_DEBUG
									cout << "markActionSubjectObjectIndefiniteEntityActionsAsNotSameReferenceSet() 2: actionSubjectEntity = " << actionSubjectEntity->entityName << ", action = " << actionEntity->entityName << endl;
									#endif
								}
								else if(hasSameSentenceSameReferenceSetActionObject)
								{
									//e.g. "A chicken that ate the pie rows the boat." - mark "a chicken" as definite such that its context will be parsed by generateContextBlocks()
									actionSubjectEntity->grammaticalDefiniteTemp = true;
								}
							}
						}
					}
				}
				for(vector<GIAentityConnection*>::iterator iter = actionEntity->actionObjectEntity->begin(); iter < actionEntity->actionObjectEntity->end(); iter++)
				{
					GIAentityConnection * actionObjectConnection = *iter;
					GIAentityNode * actionObjectEntity = actionObjectConnection->entity;
					if(!assumedToAlreadyHaveBeenDeclared(actionObjectEntity))
					{//indefinite action object entity found
						if(actionObjectConnection->sameReferenceSet)
						{
							//Only perform markActionObjectSubjectIndefiniteEntityActionsAsNotSameReferenceSet for the first sentence in which the action is defined. Although not required for !NLC_LOCAL_LISTS_USE_INSTANCE_NAMES (as actions are never assigned connections across multiple sentence indices), this is critically important for NLC_LOCAL_LISTS_USE_INSTANCE_NAMES (ie GIA_ADVANCED_REFERENCING); eg to prevent the action connections in the second sentence of "A chicken that ate a pie rows the boat. The chicken that ate the pie is happy." from being changed to !sameReferenceSet 
							if(actionEntity->sentenceIndexTemp == actionObjectConnection->sentenceIndexTemp) 
							{
								bool hasSameSentenceSameReferenceSetActionSubject = false;
								bool hasSameSentenceSameReferenceSetIndefiniteActionSubject = false;
								for(vector<GIAentityConnection*>::iterator iter = actionEntity->actionSubjectEntity->begin(); iter < actionEntity->actionSubjectEntity->end(); iter++)
								{
									GIAentityConnection * actionSubjectConnection = *iter;
									GIAentityNode * actionSubjectEntity = actionSubjectConnection->entity;
									if(actionSubjectConnection->sentenceIndexTemp == actionObjectConnection->sentenceIndexTemp)
									{
										if(actionSubjectConnection->sameReferenceSet)
										{
											hasSameSentenceSameReferenceSetActionSubject = true;
											if(!assumedToAlreadyHaveBeenDeclared(actionSubjectEntity))
											{//indefinite action object entity found
												//e.g. "A pie that was eaten by a chicken rows the boat." [not: "A pie that was eaten by the chicken rows the boat." as the context of "the chicken" will be parsed by generateContextBlocks()]
												actionSubjectConnection->sameReferenceSet = false;
												#ifdef NLC_DEBUG
												cout << "markActionObjectSubjectIndefiniteEntityActionsAsNotSameReferenceSet() 3: actionSubjectEntity = " << actionSubjectEntity->entityName << ", action = " << actionEntity->entityName << endl;
												#endif
												hasSameSentenceSameReferenceSetIndefiniteActionSubject = true;
											}
										}
									}
								}
								if(!hasSameSentenceSameReferenceSetActionSubject || hasSameSentenceSameReferenceSetIndefiniteActionSubject)
								{
									//e.g. "A pie that was eaten by a chicken rows the boat."/"A pie that was eaten rows the boat."
									actionObjectConnection->sameReferenceSet = false;
									#ifdef NLC_DEBUG
									cout << "markActionObjectSubjectIndefiniteEntityActionsAsNotSameReferenceSet() 4: actionObjectEntity = " << actionObjectEntity->entityName << ", action = " << actionEntity->entityName << endl;
									#endif
								}
								else if(hasSameSentenceSameReferenceSetActionSubject)
								{
									//NOTNECESSARY based on current implementation of generateCodeBlocksFromMathTextNLPparsablePhrase():
									//e.g. "A pie that was eaten by the chicken rows the boat." -  mark "a pie" as definite such that its context will be parsed by generateContextBlocks()
									//actionObjectEntity->grammaticalDefiniteTemp = true;
								}
							}
						}
					}
				}
			}
		}
	}
	return result;
}	
#endif
		
bool declareLocalPropertyListsForIndefiniteEntities(NLCcodeblock ** currentCodeBlockInTree, vector<GIAentityNode*> * entityNodesActiveListComplete, int sentenceIndex, string NLCfunctionName, NLCsentence * currentNLCsentenceInList)
{
	bool result = false;
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode * entity = (*entityIter);
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
							cout << "declareLocalPropertyListsForIndefiniteEntities(): " << entity->entityName << endl;
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

bool declareLocalPropertyListsForIndefiniteEntity(NLCcodeblock ** currentCodeBlockInTree, GIAentityNode * entity, NLCsentence * currentNLCsentenceInList)
{
	bool result = true;
	
	#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
	#ifdef NLC_USE_PREPROCESSOR
	#ifdef NLC_PREPROCESSOR_LOGICAL_CONDITION_USE_ROBUST_NLP_INDEPENDENT_CODE
	NLCcodeblock * firstCodeBlockAtStartOfElseStatement = *currentCodeBlockInTree;
	NLCcodeblock * firstCodeBlockAtStartOfIfStatement = NULL;
	NLCcodeblock * previousCodeBlockInTree = NULL;
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
	cout << "declareLocalPropertyListsForIndefiniteEntities(): createCodeBlocksDeclareNewLocalListVariable for " << entity->entityName << endl;
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
	if(isStringNumber(entityNode->entityName))
	{
		validClassContents = false;
		//entityNode->disabled = true;	//this could be used instead (more general implementation)
	}
	
	return validClassContents;
}








bool generateCodeBlocksPart3actions(NLCcodeblock ** currentCodeBlockInTree, vector<GIAentityNode*> * entityNodesActiveListComplete, int sentenceIndex, string NLCfunctionName, NLCsentence * currentNLCsentenceInList)
{
	bool result = true;
	
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode * actionEntity = (*entityIter);
		if(actionEntity->isAction)
		{
			if(!(actionEntity->isActionConcept))
			{
				#ifdef NLC_DEBUG
				//cout << "generateCodeBlocksPart3actions(): " << endl;
				//cout << "actionEntity->entityName = " << actionEntity->entityName << endl;
				//cout << "currentNLCsentenceInList->singleWordSentenceActionName = " << currentNLCsentenceInList->singleWordSentenceActionName << endl;
				//cout << "actionEntity->isAction = " << actionEntity->isAction << endl;
				//cout << "actionEntity->hasAssociatedInstance = " << actionEntity->hasAssociatedInstance << endl;
				#endif
				
				if(checkSentenceIndexParsingCodeBlocks(actionEntity, sentenceIndex, true))
				{
					#ifdef NLC_PREPROCESSOR_INTERPRET_SINGLE_WORD_SENTENCES_AS_ACTIONS_REPLACE_ACTION_ALSO_DUE_TO_NLP_LIMITATION
					if(actionEntity->entityName == NLC_PREPROCESSOR_INTERPRET_SINGLE_WORD_SENTENCES_AS_ACTIONS_DUMMY_TEXT_ACTION)
					{
						actionEntity->entityName = currentNLCsentenceInList->singleWordSentenceActionName;
					}
					#endif

					generateActionCodeBlocks(currentCodeBlockInTree, actionEntity, sentenceIndex, NLCfunctionName);
				}
			}
		}
	}
	
	#ifdef NLC_ACTION_CATEGORY_LISTS_USE_FOR_PLURAL_ACTION_SUBJECTSOBJECTS_IN_MULTIACTION_INITIALISATION_SENTENCES
	#ifdef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES	//note NLCcategoryListCreatedTemp is only required to be cleared between sentences for !GIA_DISABLE_CROSS_SENTENCE_REFERENCING (ie GIA_USE_ADVANCED_REFERENCING)
	//clear for next sentence 
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode * entity = (*entityIter);
		if(entity->NLCcategoryListCreatedTemp)
		{
			entity->NLCcategoryListCreatedTemp = false;
		}
	}
	#endif
	#endif
	
	return result;
}






bool generateCodeBlocksPart4objectInitialisations(NLCcodeblock ** currentCodeBlockInTree, vector<GIAentityNode*> * entityNodesActiveListComplete, int sentenceIndex, string NLCfunctionName)
{
	bool result = true;
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode * entity = *entityIter;
		if(checkSentenceIndexParsingCodeBlocks(entity, sentenceIndex, false))
		{
			if(!checkSpecialCaseEntity(entity, true))
			{
				#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
				generateCodeBlocksObjectInitialisationsForEntity(currentCodeBlockInTree, entity, sentenceIndex);
				#else
				//This code is effectively identical to generateCodeBlocksObjectInitialisationsForEntity(), without the generateParentContext argument;
				GIAentityNode * parentEntity = getParent(entity, sentenceIndex, true);
				if(!checkSpecialCaseEntity(parentEntity, true))
				{
					if(!generateParentInitialisationCodeBlockWithChecks(currentCodeBlockInTree, parentEntity , sentenceIndex, false))
					{
						generateObjectInitialisationsBasedOnPropertiesAndConditions(parentEntity, currentCodeBlockInTree , sentenceIndex, NULL, "", false, false);
					}
				}
				#endif
			}
		}
	}
	return result;
}

#ifdef NLC_SUPPORT_REDEFINITIONS
bool generateCodeBlocksPart5redefinitions(NLCcodeblock ** currentCodeBlockInTree, vector<GIAentityNode*> * entityNodesActiveListComplete, int sentenceIndex, string NLCfunctionName)
{
	//eg [Alsations are dogs. The pound has a dog. The dog is happy.] The dog is an alsation.  ; converts dog to alsation
	bool result = true;
	GIAentityNode * entity = NULL;
	GIAentityNode * definitionEntity = NULL;
	if(checkIfPhraseContainsSubstanceWithDefinitionLink(entityNodesActiveListComplete, sentenceIndex, &entity, &definitionEntity))
	{
		if(!checkSpecialCaseEntity(entity, true))	//is this required?
		{	
			NLCcodeblock * firstCodeBlockInLevel = *currentCodeBlockInTree;
			
			//1. get parent of the dog (eg pound)
			GIAentityNode * parentEntity = getParent(entity, sentenceIndex, true);
			
			//2. generate context of the dog
			NLCgenerateContextBlocksVariables generateContextBlocksVariables;
			generateContextBlocksVariables.searchSubstanceConceptsForChildren = false;	//added 1n5g (only check the explicit variable for definition)
			bool generatedContextBlocks = generateContextBlocks(currentCodeBlockInTree, parentEntity, sentenceIndex, &generateContextBlocksVariables, false, NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION);	//check if should parse categories here

			//3. verify that alsations are dogs
			*currentCodeBlockInTree = createCodeBlockCheckParentClassNameExecuteFunction2(*currentCodeBlockInTree, definitionEntity, entity->entityName);
									
			//4. cast the dog to alsation
			*currentCodeBlockInTree = createCodeConvertParentToChildClass(*currentCodeBlockInTree, entity, definitionEntity);
			
			//5. add alsation to alsation property list of pound 
				//LIMITATION: NB the dog will still be added to the dog property list of pound; therefore these must remain synced; ie the dog or the alsation cannot be deleted from the pound...
				//to avoid this limitation at present the user must define an object by its most specific class initially (avoiding redefinitions). NLC will automatically search for references to the child based on substance concept definition link to its parent [dream mode has connected substance concept definiton links to all instantations thereof]
			if(parentEntity != entity)
			{
				*currentCodeBlockInTree =  createCodeBlockAddProperty(*currentCodeBlockInTree, parentEntity, definitionEntity, sentenceIndex);
			}
			
			//6. add alsation to alsation local list
			*currentCodeBlockInTree =  createCodeBlockAddEntityToLocalList(*currentCodeBlockInTree, definitionEntity, definitionEntity);
			
			*currentCodeBlockInTree = getLastCodeBlockInLevel(firstCodeBlockInLevel);

		}
	}
	return result;
}
#endif



#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
bool clearContextGeneratedVariable(vector<GIAentityNode*> * entityNodesActiveListComplete)
{
	bool result = true;
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode * entity = *entityIter;
		entity->NLCcontextGenerated = false;
	}
	return result;
}
#endif


#ifdef NLC_GENERATE_OBJECT_INITIALISATIONS_BASED_ON_SUBSTANCE_CONCEPTS_FOR_ALL_DEFINITE_ENTITIES
bool generateObjectInitialisationsBasedOnSubstanceConceptsForAllDefiniteEntities(NLCcodeblock ** currentCodeBlockInTree, vector<GIAentityNode*> * entityNodesActiveListComplete, int sentenceIndex)
{
	bool result = true;
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode * entity = (*entityIter);
		if(!(entity->isConcept) && !(entity->isAction) && !(entity->isSubstanceQuality) && !(entity->isSubstanceConcept) && !(entity->isCondition) && !(entity->isActionConcept))
		{
			if(entity->sentenceIndexTemp == sentenceIndex)	//changed 1l15a
			//if(checkSentenceIndexParsingCodeBlocks(entity, sentenceIndex, false))
			{
				if(!(entity->disabled))
				{
					if(assumedToAlreadyHaveBeenDeclared(entity))
					{//definite entity found
						#ifdef NLC_DEBUG
						cout << "generateObjectInitialisationsBasedOnSubstanceConceptsForAllDefiniteEntities(): entity: " << entity->entityName << endl;
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
