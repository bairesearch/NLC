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
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2014 Baxter AI (baxterai.com)
 * Project: Natural Language Programming Interface (compiler)
 * Project Version: 1n2f 09-January-2015
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/



#include <ctime>
#include <cstdlib>	//for random number generation
#include <cmath>

#include "NLCtranslatorCodeBlocks.h"
#include "NLCtranslatorCodeBlocksLogicalConditions.h"
#include "NLCtranslatorCodeBlocksOperations.h"
#include "GIAtranslatorOperations.h"	//required for getPrimaryConceptNodeDefiningInstance()
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
			
			//Part Prep B - generateCodeBlocksFromMathText - added 1h1d;
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
			//Part 1 - logical conditions (eg If the house is red, ride the boat) - added 1f1a;
			#ifdef NLC_DEBUG
			cout << "generateCodeBlocksPart2logicalConditions:" << endl;
			#endif
			if(!generateCodeBlocksPart2logicalConditions(&currentCodeBlockInTree, entityNodesActiveListComplete, sentenceIndex, NLCfunctionName, currentNLCsentenceInList))
			{
				result = false;
			}
			#endif

			//Part 2; actions (eg Tom rides the boat)
			#ifdef NLC_DEBUG
			cout << "generateCodeBlocksPart3actions:" << endl;
			#endif
			if(!generateCodeBlocksPart3actions(&currentCodeBlockInTree, entityNodesActiveListComplete, sentenceIndex, NLCfunctionName, currentNLCsentenceInList))
			{
				result = false;
			}

			//Part 3: object initialisations (eg Tom has a boat) [without actions]
			#ifdef NLC_DEBUG
			cout << "generateCodeBlocksPart4objectInitialisations:" << endl;
			#endif
			if(!generateCodeBlocksPart4objectInitialisations(&currentCodeBlockInTree, entityNodesActiveListComplete, sentenceIndex, NLCfunctionName))
			{
				result = false;
			}
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
		
		
		
#ifdef NLC_PREPROCESSOR_MATH
bool generateCodeBlocksFromMathText(NLCcodeblock ** currentCodeBlockInTree, vector<GIAentityNode*> * entityNodesActiveListComplete, int sentenceIndex, NLCsentence * firstNLCsentenceInFullSentence, string NLCfunctionName)
{
	#ifdef NLC_DEBUG_PREPROCESSOR_MATH
	cout << "\n generateCodeBlocksFromMathText(): sentenceIndex = " << sentenceIndex << endl;
	#endif
	bool result = true;

	NLCcodeblock * currentCodeBlockInTreeAtBaseLevel = *currentCodeBlockInTree;
	string whileLogicalConditionConjunctionBooleanName = generateWhileLogicalConditionConjunctionBooleanName(firstNLCsentenceInFullSentence->indentation);
	
	#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
	if(firstNLCsentenceInFullSentence->hasLogicalConditionOperator)
	{
		if(firstNLCsentenceInFullSentence->logicalConditionOperator == NLC_LOGICAL_CONDITION_OPERATIONS_WHILE)
		{
			*currentCodeBlockInTree = createCodeBlockDeclareNewBoolVar(*currentCodeBlockInTree, whileLogicalConditionConjunctionBooleanName, true);
			currentCodeBlockInTreeAtBaseLevel = *currentCodeBlockInTree;
			*currentCodeBlockInTree = createCodeBlockWhileHasBool(*currentCodeBlockInTree, whileLogicalConditionConjunctionBooleanName);
			*currentCodeBlockInTree = createCodeBlockSetBoolVar(*currentCodeBlockInTree, whileLogicalConditionConjunctionBooleanName, false);
		}
						
		//CHECKTHIS; is NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE required for non-logical condition mathText?
		if((firstNLCsentenceInFullSentence->logicalConditionOperator == NLC_LOGICAL_CONDITION_OPERATIONS_IF) || (firstNLCsentenceInFullSentence->logicalConditionOperator == NLC_LOGICAL_CONDITION_OPERATIONS_WHILE) || (firstNLCsentenceInFullSentence->logicalConditionOperator == NLC_LOGICAL_CONDITION_OPERATIONS_FOR))
		{
			#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
			cout << "firstNLCsentenceInFullSentence->logicalConditionOperator == NLC_LOGICAL_CONDITION_OPERATIONS_IF" << endl;
			#endif
			int caseIndex = 0;
			int currentLevel = firstNLCsentenceInFullSentence->indentation;
			int currentLogicalConditionOperator = firstNLCsentenceInFullSentence->logicalConditionOperator;
			bool stillFindingLogicalConditionAtCurrentLevel = true;
			NLCsentence * currentSentence = firstNLCsentenceInFullSentence;
			while(stillFindingLogicalConditionAtCurrentLevel)
			{//this loop is only required by NLC_LOGICAL_CONDITION_OPERATIONS_IF (it is not used by NLC_LOGICAL_CONDITION_OPERATIONS_WHILE and NLC_LOGICAL_CONDITION_OPERATIONS_FOR)
				
				#ifdef NLC_DISABLE_1i_CODE_FOR_DEBUG
				declareLocalPropertyListsForIndefiniteEntities(currentCodeBlockInTree, entityNodesActiveListComplete, sentenceIndex, NLCfunctionName, currentSentence);	//indefinite logical condition objects (eg "a house" in "if a house is green, do this") must have been previously declared else output code will not compile [as these statements implicitly assume the existence of "a house"; which may or may not be "green"]
				#endif
				
				#ifdef NLC_PREPROCESSOR_MATH_USE_LOGICAL_CONDITION_OPERATIONS_ADVANCED_BACKWARDS_COMPATIBLE_VARIABLE_NAMES
				if(firstNLCsentenceInFullSentence->logicalConditionOperator != NLC_LOGICAL_CONDITION_OPERATIONS_FOR)
				{
					//use the same logical condition check naming scheme as NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED;
					string logicalConditionConjunctionBooleanName = generateLogicalConditionConjunctionBooleanName(currentSentence->indentation, caseIndex, NLC_LOGICAL_CONDITION_OPERATIONS_IF);							
					*currentCodeBlockInTree = createCodeBlockDeclareNewBoolArray(*currentCodeBlockInTree, logicalConditionConjunctionBooleanName, false);
				}
				#endif
			
				bool isLogicalConditionOperatorAtCurrentLevel = false;
				if(firstNLCsentenceInFullSentence->logicalConditionOperator == NLC_LOGICAL_CONDITION_OPERATIONS_IF)
				{
					if(currentSentence == firstNLCsentenceInFullSentence)
					{
						isLogicalConditionOperatorAtCurrentLevel = true;
					}
					else if(currentSentence->hasLogicalConditionOperator)
					{
						#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
						cout << "currentSentence->hasLogicalConditionOperator: " << logicalConditionOperationsArray[currentSentence->logicalConditionOperator] << endl;
						#endif
						if(currentSentence->indentation == firstNLCsentenceInFullSentence->indentation)
						{
							if((currentSentence->logicalConditionOperator > firstNLCsentenceInFullSentence->logicalConditionOperator) || (currentSentence->logicalConditionOperator == NLC_LOGICAL_CONDITION_OPERATIONS_ELSE_IF))	//allow multiple else if statements
							{
								isLogicalConditionOperatorAtCurrentLevel = true;
							}
							else
							{
								stillFindingLogicalConditionAtCurrentLevel = false;
							}
						}
						else if(currentSentence->indentation > firstNLCsentenceInFullSentence->indentation)
						{
							//gone up a level, ignore all logical condition operators
						}
						else if(currentSentence->indentation < firstNLCsentenceInFullSentence->indentation)
						{
							//gone down (back) a level; quit search for logical Condition operator sentences at current level (if, else if, else)
							stillFindingLogicalConditionAtCurrentLevel = false;
						}			
					}
				}
				else
				{//while and for loops do not use cases (only if statements use cases)
					isLogicalConditionOperatorAtCurrentLevel = true;	//NB currentSentence == firstNLCsentenceInFullSentence
					stillFindingLogicalConditionAtCurrentLevel = false;
				}
				
				
				if(isLogicalConditionOperatorAtCurrentLevel)
				{
					int sentenceIndexOfFullSentence = currentSentence->sentenceIndex;
					#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
					cout << "isLogicalConditionOperatorAtCurrentLevel: " << currentSentence->sentenceIndex << ", " << currentSentence->sentenceContents << endl;
					cout << "currentSentence->mathTextNLPparsablePhraseTotal = " << currentSentence->mathTextNLPparsablePhraseTotal << endl;
					#endif
					
					if((firstNLCsentenceInFullSentence->logicalConditionOperator == NLC_LOGICAL_CONDITION_OPERATIONS_FOR) && (currentSentence->mathTextNLPparsablePhraseTotal > 1))
					{
						//assume "and" conjunction(s) has been specified; eg "For all baskets in the house and apples in the tree, eat the pie."
					}
					
					if(currentSentence->mathTextNLPparsablePhraseTotal > 0)
					{
						NLCsentence * parsablePhrase = currentSentence;
						for(int phraseIndex=0; phraseIndex<currentSentence->mathTextNLPparsablePhraseTotal; phraseIndex++)
						{
							if(parsablePhrase->mathTextNLPparsablePhraseIndex != phraseIndex)
							{
								cout << "generateCodeBlocksFromMathText() error: (currentSentence->mathTextNLPparsablePhraseIndex != i)" << endl;
							}
							if(firstNLCsentenceInFullSentence->logicalConditionOperator == NLC_LOGICAL_CONDITION_OPERATIONS_FOR)
							{
								if(!generateCodeBlocksFromMathTextNLPparsablePhraseLogicalConditionFor(currentCodeBlockInTree, entityNodesActiveListComplete, parsablePhrase->sentenceIndex, currentSentence, parsablePhrase, phraseIndex, &currentCodeBlockInTreeAtBaseLevel, firstNLCsentenceInFullSentence))
								{
									result = false;
								}
							}
							else
							{
								GIAentityNode * logicalConditionOperationObject = NULL;
								#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_BASED_ON_ACTIONS_BASIC
								if(checkIfPhraseContainsAction(entityNodesActiveListComplete, parsablePhrase->sentenceIndex, &logicalConditionOperationObject))
								{//eg "The sun fights. / If the sun fights, the dog is happy."
								
									string parsablePhraseReferenceName = generateMathTextNLPparsablePhraseReference(currentSentence->sentenceIndex, parsablePhrase);
									*currentCodeBlockInTree = createCodeBlockDeclareNewBoolVar(*currentCodeBlockInTree, parsablePhraseReferenceName, false);

									setDummyReferenceSetIDforAllEntitiesInPhrase(entityNodesActiveListComplete, parsablePhrase->sentenceIndex);	//this is required for searchForEquivalentSubnetToIfStatement()
									GIAentityNode * actionEntityCompare = logicalConditionOperationObject;	//if statement comparison...
									GIAentityNode * actionEntityCompareConcept = getPrimaryConceptNodeDefiningInstance(actionEntityCompare);
									if(searchForEquivalentSubnetToIfStatement(actionEntityCompareConcept, logicalConditionOperationObject, false))
									{
										*currentCodeBlockInTree = createCodeBlockSetBoolVar(*currentCodeBlockInTree, parsablePhraseReferenceName, true);
										#ifdef NLC_DEBUG
										//cout << "NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_BASED_ON_ACTIONS_BASIC: passed logical condition" << endl;
										#endif
									}								
								} else 
								#endif
								#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_BASED_ON_CONCEPTS_BASIC
								if(checkIfPhraseContainsSubstanceConceptWithDefinitionLink(entityNodesActiveListComplete, parsablePhrase->sentenceIndex, &logicalConditionOperationObject))
								{//eg "Red dogs are pies. / If red dogs are pies, eat the cabbage."
								
									//logical operations on concepts are performed by NLC (code is not generated for them by NLC as they are not performed at runtime) - eg If red dogs are pies, eat the cabbage.	[as opposed to: "if the red dog is the/a pie, eat the cabbage"]
									//verify the truth of the if statement now (if the statement is false, disable all classStructure formation based on condition subject subset)
								
									//cout << "logicalConditionOperationObject->isSubstanceConcept" << endl;
									string parsablePhraseReferenceName = generateMathTextNLPparsablePhraseReference(currentSentence->sentenceIndex, parsablePhrase);
									*currentCodeBlockInTree = createCodeBlockDeclareNewBoolVar(*currentCodeBlockInTree, parsablePhraseReferenceName, false);

									setDummyReferenceSetIDforAllEntitiesInPhrase(entityNodesActiveListComplete, parsablePhrase->sentenceIndex);	//this is required for searchForEquivalentSubnetToIfStatement()
									GIAentityNode * substanceConceptEntityCompare = logicalConditionOperationObject;	//if statement comparison...
									GIAentityNode * substanceConceptEntityCompareConcept = getPrimaryConceptNodeDefiningInstance(substanceConceptEntityCompare);
									if(searchForEquivalentSubnetToIfStatement(substanceConceptEntityCompareConcept, logicalConditionOperationObject, true))
									{
										*currentCodeBlockInTree = createCodeBlockSetBoolVar(*currentCodeBlockInTree, parsablePhraseReferenceName, true);
										#ifdef NLC_DEBUG
										//cout << "NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_BASED_ON_CONCEPTS: passed logical condition" << endl;
										#endif
									}
								} else
								#endif
								if(!generateCodeBlocksFromMathTextNLPparsablePhrase(currentCodeBlockInTree, entityNodesActiveListComplete, parsablePhrase->sentenceIndex, currentSentence, parsablePhrase, phraseIndex, caseIndex))
								{
									result = false;
								}
							}
							#ifdef NLC_DEBUG_PREPROCESSOR_MATH
							cout << "finished generateCodeBlocksFromMathTextNLPparsablePhrase()" << endl;
							#endif
							parsablePhrase = parsablePhrase->next;
						}
						caseIndex++;
						currentSentence = parsablePhrase;
					}
					else
					{
						caseIndex++;
						currentSentence = currentSentence->next;						
					}
				}
				else
				{
					if(currentSentence->next != NULL)
					{
						currentSentence = currentSentence->next;
					}
					else
					{
						stillFindingLogicalConditionAtCurrentLevel = false;
					}
				}
			}
		
			if(firstNLCsentenceInFullSentence->logicalConditionOperator == NLC_LOGICAL_CONDITION_OPERATIONS_IF)
			{
				currentCodeBlockInTreeAtBaseLevel = (*currentCodeBlockInTree);
			}			
		}
		else if((firstNLCsentenceInFullSentence->logicalConditionOperator == NLC_LOGICAL_CONDITION_OPERATIONS_ELSE_IF) || (firstNLCsentenceInFullSentence->logicalConditionOperator == NLC_LOGICAL_CONDITION_OPERATIONS_ELSE))
		{
			currentCodeBlockInTreeAtBaseLevel = *currentCodeBlockInTree;		
		}
		else
		{
			cout << "generateCodeBlocksFromMathText() error: illegal firstNLCsentenceInFullSentence->logicalConditionOperator" << endl;
			exit(0);
		}
		
		#ifdef NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT
		if(firstNLCsentenceInFullSentence->logicalConditionOperator != NLC_LOGICAL_CONDITION_OPERATIONS_FOR)
		{
			(*currentCodeBlockInTree)->isLogicalCondition = true;
			(*currentCodeBlockInTree)->contextLevel = firstNLCsentenceInFullSentence->indentation+1;
		}
		#endif
	}
	else
	{
	#endif
		NLCsentence * parsablePhrase = firstNLCsentenceInFullSentence;
		for(int phraseIndex=0; phraseIndex<firstNLCsentenceInFullSentence->mathTextNLPparsablePhraseTotal; phraseIndex++)
		{
			if(parsablePhrase->mathTextNLPparsablePhraseIndex != phraseIndex)
			{
				cout << "generateCodeBlocksFromMathText() error: (currentSentence->mathTextNLPparsablePhraseIndex != i)" << endl;
			}
			if(!generateCodeBlocksFromMathTextNLPparsablePhrase(currentCodeBlockInTree, entityNodesActiveListComplete, parsablePhrase->sentenceIndex, firstNLCsentenceInFullSentence, parsablePhrase, phraseIndex, 0))
			{
				result = false;
			}
			parsablePhrase = parsablePhrase->next;
		}
	#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
	}
	#endif	

	#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
	if(firstNLCsentenceInFullSentence->hasLogicalConditionOperator)
	{
		if(firstNLCsentenceInFullSentence->logicalConditionOperator == NLC_LOGICAL_CONDITION_OPERATIONS_WHILE)
		{
			firstNLCsentenceInFullSentence->mathText.replace(0, string(NLC_LOGICAL_CONDITION_OPERATIONS_WHILE_STRING).length(), string(NLC_LOGICAL_CONDITION_OPERATIONS_IF_STRING));	//replace "while" with "if" for the purposes of generating final code (while loop has already been defined)
		}
			
		if(firstNLCsentenceInFullSentence->logicalConditionOperator != NLC_LOGICAL_CONDITION_OPERATIONS_FOR)
		{
			#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
			cout << "createCodeBlockMathTextWithLogicalOperator: firstNLCsentenceInFullSentence->mathText = " << firstNLCsentenceInFullSentence->mathText << endl;
			#endif
			*currentCodeBlockInTree = createCodeBlockMathTextWithLogicalOperator(*currentCodeBlockInTree, firstNLCsentenceInFullSentence->mathText);
		}
		
		if(firstNLCsentenceInFullSentence->logicalConditionOperator == NLC_LOGICAL_CONDITION_OPERATIONS_WHILE)
		{
			*currentCodeBlockInTree = createCodeBlockSetBoolVar(*currentCodeBlockInTree, whileLogicalConditionConjunctionBooleanName, true);
		}
		
		#ifdef NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT
		*currentCodeBlockInTree = createCodeBlocksDeclareContextList(*currentCodeBlockInTree, firstNLCsentenceInFullSentence->indentation+1);
		#endif
		
		if(firstNLCsentenceInFullSentence->next != NULL)
		{
			NLCsentence * nextNLCfullSentenceInList = firstNLCsentenceInFullSentence;
			bool hasNextSentence = false;
			if(firstNLCsentenceInFullSentence->mathTextNLPparsablePhraseTotal > 0)
			{
				for(int phraseIndex=0; phraseIndex<firstNLCsentenceInFullSentence->mathTextNLPparsablePhraseTotal; phraseIndex++)
				{
					nextNLCfullSentenceInList = nextNLCfullSentenceInList->next;
				}
			}
			else
			{
				nextNLCfullSentenceInList = firstNLCsentenceInFullSentence->next;			
			}
			
			#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE	
			cout << "firstNLCsentenceInFullSentence->sentenceContents = " << firstNLCsentenceInFullSentence->sentenceContents << endl;
			cout << "nextNLCfullSentenceInList->sentenceContents = " << nextNLCfullSentenceInList->sentenceContents << endl;
			cout << "firstNLCsentenceInFullSentence->indentation = " << firstNLCsentenceInFullSentence->indentation << endl;
			cout << "nextNLCfullSentenceInList->indentation = " << nextNLCfullSentenceInList->indentation << endl;
			#endif
			
			if(nextNLCfullSentenceInList->indentation == (firstNLCsentenceInFullSentence->indentation + 1))
			{
				#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
				cout << "(nextNLCfullSentenceInList->indentation == (firstNLCsentenceInFullSentence->indentation + 1))" << endl;
				#endif
				//do not, just record the in the tree
				setCodeBlockAtPreviousLogicalConditionBaseLevelArray(firstNLCsentenceInFullSentence->indentation, currentCodeBlockInTreeAtBaseLevel->next);
			}
			else if(nextNLCfullSentenceInList->indentation <= firstNLCsentenceInFullSentence->indentation)
			{
				#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
				cout << "(nextNLCfullSentenceInList->indentation <= firstNLCsentenceInFullSentence->indentation)" << endl;
				#endif			
				*currentCodeBlockInTree = currentCodeBlockInTreeAtBaseLevel->next;
				//NB if(nextNLCfullSentenceInList->indentation < firstNLCsentenceInFullSentence->indentation) will be processed later by generateCodeBlocks()
			}
			else
			{
				cout << "NLC_USE_PREPROCESSOR generateCodeBlocksPart2logicalConditions() error: invalid indentation of nextNLCfullSentenceInList, sentenceIndex = " << sentenceIndex << endl;
				cout << "nextNLCfullSentenceInList->indentation <= firstNLCsentenceInFullSentence->indentation + 1" << endl;
				cout << "firstNLCsentenceInFullSentence->indentation = " << firstNLCsentenceInFullSentence->indentation << endl;
				cout << "nextNLCfullSentenceInList->indentation = " << nextNLCfullSentenceInList->indentation << endl;
			}
		}
									
	}
	else
	{
	#endif
		*currentCodeBlockInTree = createCodeBlockMathTextLine(*currentCodeBlockInTree, firstNLCsentenceInFullSentence->mathText);
	#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
	}
	#endif
	
	#ifdef NLC_DEBUG_PREPROCESSOR_MATH
	cout << "finished generateCodeBlocksFromMathText()" << endl;
	#endif
	
	return result;
}	

bool generateCodeBlocksFromMathTextNLPparsablePhrase(NLCcodeblock ** currentCodeBlockInTree, vector<GIAentityNode*> * entityNodesActiveListComplete, int sentenceIndex, NLCsentence * currentFullSentence, NLCsentence * parsablePhrase, int phraseIndex, int caseIndex)
{
	bool foundParsablePhrase = false;
	
	#ifdef NLC_DEBUG_PREPROCESSOR_MATH
	cout << "generateCodeBlocksFromMathTextNLPparsablePhrase() part 1" << endl;
	#endif
	//generate NLP parsable phrase eg "the number of chickens" in "if(the number of chickens > the number of apples...)"
	NLCcodeblock * currentCodeBlockAtStartOfparsablePhrase = *currentCodeBlockInTree;
	string parsablePhraseReferenceName = generateMathTextNLPparsablePhraseReference(currentFullSentence->sentenceIndex, parsablePhrase);	//parsablePhraseGenerateNumberOfElementCounterName
	*currentCodeBlockInTree = createCodeBlockDeclareNewIntVar(*currentCodeBlockInTree, parsablePhraseReferenceName, 0);	//?this will need to be changed to createCodeBlockDeclareNewIntArray in the future to support multiple cases (ie if, else if, else)
	
	//if !NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE, currently only accept entities with $qVar defined, eg "Number of red dogs". prep_of(number-4, dogs-7) [NLP] / _quantity(dog[8], _$qVar[1]) [GIA]
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode * entity = (*entityIter);
		if(checkSentenceIndexParsingCodeBlocks(entity, sentenceIndex, false))
		{
			if(!(entity->isConcept) && !(entity->isCondition))
			{//redundant	
				#ifdef NLC_PREPROCESSOR_MATH_OLD_NUMBER_OF_IMPLEMENTATION_USING_QVARS
				if(entity->isQuery)
				#else
				if(entity->isNumberOf)
				#endif
				{
					#ifdef NLC_DEBUG
					//cout << "generateCodeBlocksFromMathTextNLPparsablePhrase(): sentenceIndex = " << sentenceIndex << endl;
					//cout << "generateCodeBlocksFromMathTextNLPparsablePhrase(): " << entity->entityName << ", entity->sentenceIndexTemp = " << entity->sentenceIndexTemp << endl;
					#endif
					
					if(foundParsablePhrase)
					{
						cout << "generateCodeBlocksFromMathTextNLPparsablePhrase() error: more than one parsable phrase primary entity found" << endl;
					}
					foundParsablePhrase = true;

					#ifdef NLC_DEBUG_PREPROCESSOR_MATH
					cout << "generateCodeBlocksFromMathTextNLPparsablePhrase(): found 'number of' designation, entity: " << entity->entityName << endl;
					#endif
					NLCgenerateContextBlocksVariables generateContextBlocksVariables;
					#ifdef NLC_LOGICAL_CONDITION_OPERATIONS_SUPPORT_INDEFINITE_LOGICAL_CONDITION_OBJECTS
					//number of statements must be expressed using definite variables, but they will not be advanced referenced by GIA (and so must be located in the typeList)
					//if(!assumedToAlreadyHaveBeenDeclared(entity))	//"the number of x" will have already been declared, but is not advanced referenced, so much search the typeList
					//{
						#ifdef NLC_GENERATE_TYPE_LISTS
						//1i implementation
						*currentCodeBlockInTree = createCodeBlockForPropertyTypeClass(*currentCodeBlockInTree, entity);	//eg "If a house is green, do this", an instanceList (OLD: localList) for "a house" is assumed to have already been declared, one of which may be green, so search all house instanceLists within house typeList...
						//if at least one instanceList of type currentLogicalConditionObject has not previously been declared, then the code will result in a compilation error
						//if at least one instanceList of type currentLogicalConditionObject has previously been declared, but does not have the required properties (eg green), then the code will compile but the if statement will fail
						#else
						//1j implementation
						entity->grammaticalDefiniteTemp = true;		//removed 1j15a
						#endif					
					//}
					#endif
					if(!getParentAndGenerateContextBlocks(currentCodeBlockInTree, entity, sentenceIndex, &generateContextBlocksVariables, true))	//NB parseConditionParents probably does not need to ever be set to true (unless condition subject/object are switched and condition name is updated accordingly to reflect this inversion of relationship)
					{
						#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
						cout << "generateCodeBlocksFromMathTextNLPparsablePhrase() error: !getParentAndGenerateContextBlocks: " << entity->entityName << endl;
						#endif
					}

					*currentCodeBlockInTree = createCodeBlockIncrementIntVar(*currentCodeBlockInTree, parsablePhraseReferenceName);

					*currentCodeBlockInTree = getLastCodeBlockInLevel(currentCodeBlockAtStartOfparsablePhrase);				
				}
			}
		}
	}	
	if(!foundParsablePhrase)
	{
		#ifndef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
		cout << "generateCodeBlocksFromMathTextNLPparsablePhrase() error: !foundParsablePhrase" << endl;		
		#endif
		*currentCodeBlockInTree = currentCodeBlockAtStartOfparsablePhrase;	//redundant
		clearCodeBlock(currentCodeBlockAtStartOfparsablePhrase);
	
	
		#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
		
		#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
		cout << "generateCodeBlocksFromMathTextNLPparsablePhrase() part 2" << endl;
		#endif
		
		#ifdef NLC_PREPROCESSOR_MATH_USE_LOGICAL_CONDITION_OPERATIONS_ADVANCED_BACKWARDS_COMPATIBLE_VARIABLE_NAMES
		parsablePhraseReferenceName = generateLogicalConditionConjunctionBooleanName(currentFullSentence->indentation, caseIndex, phraseIndex, NLC_LOGICAL_CONDITION_OPERATIONS_IF);
		#else
		*currentCodeBlockInTree = createCodeBlockDeclareNewBoolVar(*currentCodeBlockInTree, parsablePhraseReferenceName, false);	//?this will need to be changed to createCodeBlockDeclareNewBoolArray in the future to support multiple cases (ie if, else if, else)
		#endif
		
		//generate NLP parsable phrase eg "the red chicken is next to the house" in "if(the red chicken is next to the house && the blue box has an apple)"
		if(currentFullSentence->hasLogicalConditionOperator)	//CHECKTHIS; is NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE required for non-logical condition mathText?
		{
			foundParsablePhrase = false;
			for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
			{
				GIAentityNode * entity = (*entityIter);
				if(checkSentenceIndexParsingCodeBlocks(entity, sentenceIndex, false))
				{
					if(!(entity->isConcept) && !(entity->isCondition))
					{//required			
						#ifdef NLC_PREPROCESSOR_MATH_OLD_NUMBER_OF_IMPLEMENTATION_USING_QVARS
						if(entity->isQuery)
						#else
						if(entity->isNumberOf)
						#endif
						{
							#ifdef NLC_DEBUG
							//cout << "generateCodeBlocksFromMathTextNLPparsablePhrase() error: entity->isNumberOf && !(entity->NLCcontextGenerated): part 1 must have failed" << endl;
							#endif
						}
						else
						{		
							if(!foundParsablePhrase)
							{
								#ifdef NLC_DEBUG_PREPROCESSOR_MATH
								cout << "generateCodeBlocksFromMathTextNLPparsablePhrase(): found entity: " << entity->entityName << endl;
								#endif

								GIAentityNode * parentEntity = getParent(entity, sentenceIndex, true);	//NB parseConditionParents probably does not need to ever be set to true (unless condition subject/object are switched and condition name is updated accordingly to reflect this inversion of relationship)

								NLCgenerateContextBlocksVariables generateContextBlocksVariables;
								NLCcodeblock * NLCcodeBlockBeforeGenerateContext = *currentCodeBlockInTree; 
								bool contextFound = false;

								#ifdef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES
								#ifdef NLC_LOGICAL_CONDITION_OPERATIONS_SUPPORT_INDEFINITE_LOGICAL_CONDITION_OBJECTS
								//if/while statements can be expressed using either definite or indefinate variables, but if they indefinite they will not be advanced referenced by GIA (and so must be located in the typeList)
								if(!assumedToAlreadyHaveBeenDeclared(parentEntity))
								{
									#ifdef NLC_GENERATE_TYPE_LISTS
									//1i implementation
									*currentCodeBlockInTree = createCodeBlockForPropertyTypeClass(*currentCodeBlockInTree, parentEntity);	//eg "If a house is green, do this", an instanceList (OLD: localList) for "a house" is assumed to have already been declared, one of which may be green, so search all house instanceLists within house typeList...
									//if at least one instanceList of type currentLogicalConditionObject has not previously been declared, then the code will result in a compilation error
									//if at least one instanceList of type currentLogicalConditionObject has previously been declared, but does not have the required properties (eg green), then the code will compile but the if statement will fail
									#else
									//1j implementation
									//parentEntity->grammaticalDefiniteTemp = true;		//removed 1j15a
									#endif
								}
								#endif
								if(generateContextBlocks(currentCodeBlockInTree, parentEntity, sentenceIndex, &generateContextBlocksVariables, false, NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION))
								{
									contextFound = true;
								}
								#else
								//*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("generateCodeBlocksFromMathTextNLPparsablePhrase():  1 generateContextBlocks: ") + parentEntity->entityName);
								//NB logicalConditionOperator != NLC_LOGICAL_CONDITION_OPERATIONS_FOR (if so generateCodeBlocksFromMathTextNLPparsablePhraseLogicalConditionFor is executed instead)
								//therefore logicalConditionOperator == NLC_LOGICAL_CONDITION_OPERATIONS_IF/NLC_LOGICAL_CONDITION_OPERATIONS_ELSE_IF/NLC_LOGICAL_CONDITION_OPERATIONS_ELSE_WHILE
								generateContextBlocksVariables.onlyGenerateContextBlocksIfConnectionsParsedForNLC = true;
								if(generateContextBlocks(currentCodeBlockInTree, parentEntity, sentenceIndex, &generateContextBlocksVariables, false, NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION))
								{
									contextFound = true;
								}
								generateContextBlocksVariables.onlyGenerateContextBlocksIfConnectionsParsedForNLC = false;
								#ifdef NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY
								generateContextBlocksVariables.testNumerosity = true;
								#endif
								//*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("generateCodeBlocksFromMathTextNLPparsablePhrase():  2 generateContextBlocks: ") + parentEntity->entityName);
								if(generateContextBlocks(currentCodeBlockInTree, parentEntity, sentenceIndex, &generateContextBlocksVariables, true, NLC_ITEM_TYPE_LOGICALCONDITION_VAR_APPENDITION))
								{
									contextFound = true;
								}	
								#endif
	
								if(!contextFound)
								{
									#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
									cout << "generateCodeBlocksFromMathTextNLPparsablePhrase() error: !getParentAndGenerateContextBlocks: sentenceIndex = " << sentenceIndex << endl;
									#endif
									
									*currentCodeBlockInTree = NLCcodeBlockBeforeGenerateContext;
									clearCodeBlock(*currentCodeBlockInTree);							
								}
								else
								{
									#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
									cout << "generateCodeBlocksFromMathTextNLPparsablePhrase() pass: getParentAndGenerateContextBlocks: sentenceIndex = " << sentenceIndex << endl;
									#endif
									
									foundParsablePhrase = true;
									
									if(generateContextBlocksVariables.negativeDetectedInContextBlocks)
									{
										int parsablePhraseReferenceNamePosInMathText = currentFullSentence->mathText.find(parsablePhraseReferenceName);
										if(parsablePhraseReferenceNamePosInMathText != CPP_STRING_FIND_RESULT_FAIL_VALUE)	//&& (parsablePhraseReferenceNamePosInMathText > 0
										{
											currentFullSentence->mathText.insert(parsablePhraseReferenceNamePosInMathText, 1, NLC_PREPROCESSOR_MATH_OPERATOR_NEGATIVE_CHAR);
											#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
											cout << "negativeDetectedInContextBlocks detected; inserting NLC_PREPROCESSOR_MATH_OPERATOR_NEGATIVE_CHAR into mathText logical condition" << endl;
											#endif
										}
									}
									
									*currentCodeBlockInTree = createCodeBlockSetBoolVar(*currentCodeBlockInTree, parsablePhraseReferenceName, true);

									*currentCodeBlockInTree = getLastCodeBlockInLevel(currentCodeBlockAtStartOfparsablePhrase);								
								}
							}
						}
					}
				}
			}			
		}
		#endif
		if(!foundParsablePhrase)
		{
			cout << "generateCodeBlocksFromMathTextNLPparsablePhrase() error: !foundParsablePhrase" << endl;		
			*currentCodeBlockInTree = currentCodeBlockAtStartOfparsablePhrase;	//redundant
			clearCodeBlock(currentCodeBlockAtStartOfparsablePhrase);
		}
	}
	
	return foundParsablePhrase;
}

bool generateCodeBlocksFromMathTextNLPparsablePhraseLogicalConditionFor(NLCcodeblock ** currentCodeBlockInTree, vector<GIAentityNode*> * entityNodesActiveListComplete, int sentenceIndex, NLCsentence * currentFullSentence, NLCsentence * parsablePhrase, int phraseIndex, NLCcodeblock ** currentCodeBlockInTreeAtBaseLevel, NLCsentence * firstNLCsentenceInFullSentence)
{
	bool foundParsablePhrase = false;
	
	#ifdef NLC_DEBUG_PREPROCESSOR_MATH
	cout << "generateCodeBlocksFromMathTextNLPparsablePhraseLogicalConditionFor()" << endl;
	#endif
	//generate NLP parsable phrase eg "all apples in the cart" in "for(all the apples in the cart)"
	
	if((currentFullSentence->hasLogicalConditionOperator) && (currentFullSentence->logicalConditionOperator == NLC_LOGICAL_CONDITION_OPERATIONS_FOR))
	{
		foundParsablePhrase = false;
		for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
		{
			GIAentityNode * entity = (*entityIter);
			if(checkSentenceIndexParsingCodeBlocks(entity, sentenceIndex, false))
			{
				if(!(entity->isConcept) && !(entity->isCondition))
				{//required
					if(!foundParsablePhrase)
					{
						NLCgenerateContextBlocksVariables generateContextBlocksVariables;
						#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
						generateContextBlocksVariables.setCodeBlockInTreeAtBaseLevel = true;
						#endif
						NLCcodeblock * NLCcodeBlockBeforeGenerateContext = *currentCodeBlockInTree; 
						/*//for statements must be expressed using definite variables, and they will be advanced referenced by GIA (ie "for all the chickens...", not "for a chicken..")
						if(!assumedToAlreadyHaveBeenDeclared(entity))
						{
						      *currentCodeBlockInTree = createCodeBlockForPropertyTypeClass(*currentCodeBlockInTree, entity);   //eg "If a house is green, do this", an instanceList (OLD: localList) for "a house" is assumed to have already been declared, one of which may be green, so search all house instanceLists within house typeList...
						      //if at least one instanceList of type currentLogicalConditionObject has not previously been declared, then the code will result in a compilation error
						      //if at least one instanceList of type currentLogicalConditionObject has previously been declared, but does not have the required properties (eg green), then the code will compile but the if statement will fail
						}
						*/
						if(!getParentAndGenerateContextBlocks(currentCodeBlockInTree, entity, sentenceIndex, &generateContextBlocksVariables, true))	//NB parseConditionParents probably does not need to ever be set to true (unless condition subject/object are switched and condition name is updated accordingly to reflect this inversion of relationship)
						{
							#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
							cout << "generateCodeBlocksFromMathTextNLPparsablePhrase() error: !getParentAndGenerateContextBlocks: sentenceIndex = " << sentenceIndex << endl;
							#endif

							*currentCodeBlockInTree = NLCcodeBlockBeforeGenerateContext;
							clearCodeBlock(*currentCodeBlockInTree);							
						}
						else
						{
							#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
							*currentCodeBlockInTreeAtBaseLevel = generateContextBlocksVariables.currentCodeBlockInTreeAtBaseLevel;
							#ifdef NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT
							(*currentCodeBlockInTreeAtBaseLevel)->isLogicalCondition = true;
							(*currentCodeBlockInTreeAtBaseLevel)->contextLevel = firstNLCsentenceInFullSentence->indentation+1;
							#endif
							#endif
							foundParsablePhrase = true;
						}
					}	
				}
			}
		}
	}
	return foundParsablePhrase;
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
							//cout << "declareLocalPropertyListsForIndefiniteEntities(): " << entity->entityName << endl;
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

#ifdef NLC_PREPROCESSOR_MATH_REPLACE_NUMERICAL_VARIABLES_NAMES_FOR_NLP
bool findAndSetDummyNumericalValueForReplacement(vector<GIAentityNode*> * entityNodesActiveListComplete, int sentenceIndex, int dummyNumericalValue, string numericalVariableName)
{
	bool result = true;
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode * entity = (*entityIter);
		if(checkSentenceIndexParsingCodeBlocks(entity, sentenceIndex, false))
		{
			if(entity->quantityNumber == dummyNumericalValue)
			{
				#ifdef NLC_DEBUG
				//cout << "findAndSetDummyNumericalValueForReplacement(): " << endl;
				//cout << "entity->quantityNumber = " << entity->quantityNumber << endl;
				//cout << "dummyNumericalValue = " << dummyNumericalValue << endl;
				//cout << "sentenceIndex = " << sentenceIndex << endl;
				#endif
				entity->NLCoriginalNumericalVariableName = numericalVariableName;
				result = true;
			}
		}	
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

#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_BASED_ON_ACTIONS_BASIC
bool checkIfPhraseContainsAction(vector<GIAentityNode*> * entityNodesActiveListComplete, int sentenceIndex, GIAentityNode ** logicalConditionOperationObject)
{
	bool phraseContainsAction = false;
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode * connectedEntity = (*entityIter);
		if(checkSentenceIndexParsingCodeBlocks(connectedEntity, sentenceIndex, false))
		{		
			if(connectedEntity->isAction || connectedEntity->isActionConcept)
			{
				phraseContainsAction = true;
				*logicalConditionOperationObject = connectedEntity;
			}
		}
	}
	return phraseContainsAction;
}
#endif

#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_BASED_ON_CONCEPTS_BASIC
bool checkIfPhraseContainsSubstanceConceptWithDefinitionLink(vector<GIAentityNode*> * entityNodesActiveListComplete, int sentenceIndex, GIAentityNode ** logicalConditionOperationObject)
{
	bool phraseContainsSubstanceConcept = false;
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode * connectedEntity = (*entityIter);
		if(checkSentenceIndexParsingCodeBlocks(connectedEntity, sentenceIndex, false))
		{		
			if(connectedEntity->isSubstanceConcept)
			{
				if(!(connectedEntity->entityNodeDefinitionList->empty()))
				{
					phraseContainsSubstanceConcept = true;
					*logicalConditionOperationObject = connectedEntity;
				}
			}
		}
	}
	return phraseContainsSubstanceConcept;
}
#endif

void setDummyReferenceSetIDforAllEntitiesInPhrase(vector<GIAentityNode*> * entityNodesActiveListComplete, int sentenceIndex)
{
	//cout << "setDummyReferenceSetIDforAllEntitiesInPhrase: " << endl;
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode * connectedEntity = (*entityIter);
		if(checkSentenceIndexParsingCodeBlocks(connectedEntity, sentenceIndex, false))
		{			
			connectedEntity->referenceSetID = NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_BASED_ON_ACTIONS_OR_CONCEPTS_DUMMY_REFERENCE_SET_ID;
			#ifdef NLC_DEBUG
			//cout << "setDummyReferenceSetIDforAllEntitiesInPhrase():" << endl;
			//cout << "connectedEntity = " << connectedEntity->entityName << endl;
			//cout << "connectedEntity->isConcept = " << connectedEntity->isConcept << endl;
			#endif
		}
	}
}
