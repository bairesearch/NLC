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
 * File Name: NLCtranslatorCodeBlocksLogicalConditionsAdvanced.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2016 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 1v10a 23-October-2016
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/


#include "NLCtranslatorCodeBlocksLogicalConditionsAdvanced.h"
#include "NLCtranslatorCodeBlocksOperations.h"
#include "GIAquery.h"	//required for testReferencedEntityNodeForExactNameMatch2/traceEntityNode
#include "GIAtranslatorDefs.h"

#ifdef NLC_USE_PREPROCESSOR
static bool useNLCpreprocessor;
static NLCcodeblock* codeBlockAtPreviousLogicalConditionBaseLevelArray[NLC_PREPROCESSOR_MAX_INDENTATION_LEVELS];
#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
static bool currentSentenceContainsLogicalCondition;
static NLCcodeblock* codeBlockAtPreviousLogicalConditionBaseStartOfIfStatementLevelArray[NLC_PREPROCESSOR_MAX_INDENTATION_LEVELS];
static int currentLogicalConditionCase[NLC_PREPROCESSOR_MAX_INDENTATION_LEVELS];
#endif
void initialiseLogicalConditionLevelRecordArray(bool newUseNLCpreprocessor)
{
	useNLCpreprocessor = newUseNLCpreprocessor;
	for(int i=0; i<NLC_PREPROCESSOR_MAX_INDENTATION_LEVELS; i++)
	{
		codeBlockAtPreviousLogicalConditionBaseLevelArray[i] = NULL;
	}
	#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
	setCurrentLogicalConditionLevel(0);
	currentSentenceContainsLogicalCondition = false;
	for(int i=0; i<NLC_PREPROCESSOR_MAX_INDENTATION_LEVELS; i++)
	{
		codeBlockAtPreviousLogicalConditionBaseStartOfIfStatementLevelArray[i] = NULL;
		currentLogicalConditionCase[i] = 0;
	}
	#endif
}
bool getUseNLCpreprocessor()
{
	return useNLCpreprocessor;
}
NLCcodeblock* getCodeBlockAtPreviousLogicalConditionBaseLevelArray(int index)
{
	return codeBlockAtPreviousLogicalConditionBaseLevelArray[index];
}
void setCodeBlockAtPreviousLogicalConditionBaseLevelArray(int index, NLCcodeblock* codeBlockToSet)
{
	codeBlockAtPreviousLogicalConditionBaseLevelArray[index] = codeBlockToSet;
}
#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
bool getCurrentSentenceContainsLogicalCondition()
{
	return currentSentenceContainsLogicalCondition;
}
void setCurrentSentenceContainsLogicalCondition(bool value)
{
	currentSentenceContainsLogicalCondition = value;
}
int getCurrentLogicalConditionCase(int level)
{
	return currentLogicalConditionCase[level];
}
#endif
#endif

#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
bool generateCodeBlocksPart2logicalConditions(NLCcodeblock** currentCodeBlockInTree, vector<GIAentityNode*>* entityNodesActiveListSentence, int sentenceIndex, string NLCfunctionName, NLCsentence* currentNLCsentenceInList)
{
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListSentence->begin(); entityIter != entityNodesActiveListSentence->end(); entityIter++)
	{
		GIAentityNode* logicalConditionOperationEntity = (*entityIter);
		if(logicalConditionOperationEntity->entityType == GIA_ENTITY_TYPE_TYPE_CONDITION)
		{
			if(checkSentenceIndexParsingCodeBlocks(logicalConditionOperationEntity, sentenceIndex, true))	//could be set to false instead
			{
				bool foundLogicalConditionOperation = false;
				int logicalOperation = INT_DEFAULT_VALUE;
				if(logicalConditionOperationEntity->NLClogicalConditionOperation)	//used to test more complex sentence context requirements of some logical condition operations eg "for" is required to be immediately succeeded by "each", "all", or every
				{
					bool foundLogicalConditionOperationBasic = textInTextArray(logicalConditionOperationEntity->entityName, logicalConditionOperationsArray, NLC_LOGICAL_CONDITION_OPERATIONS_NUMBER_OF_TYPES, &logicalOperation);
					if((logicalOperation == NLC_LOGICAL_CONDITION_OPERATIONS_FOR) || (logicalOperation == NLC_LOGICAL_CONDITION_OPERATIONS_IF) || (logicalOperation == NLC_LOGICAL_CONDITION_OPERATIONS_WHILE))
					{//these are the only logical condition operations supported by NLC at this time
						foundLogicalConditionOperation = true;
					}
				}
				if(foundLogicalConditionOperation)
				{
					GIAentityNode* logicalConditionOperationSubject = NULL;
					GIAentityNode* logicalConditionOperationObject = NULL;
					bool foundConditionSubject = false;
					bool foundConditionObject = false;
					if(!(logicalConditionOperationEntity->conditionSubjectEntity->empty()))
					{
						logicalConditionOperationSubject = (logicalConditionOperationEntity->conditionSubjectEntity->back())->entity;
						foundConditionSubject = true;
					}
					if(!(logicalConditionOperationEntity->conditionObjectEntity->empty()))
					{
						logicalConditionOperationObject = (logicalConditionOperationEntity->conditionObjectEntity->back())->entity;
						foundConditionObject = true;
					}
					if(foundConditionSubject && foundConditionObject)
					{
						bool simpleNonConjunctionLogicalConditionNegative = false;
						if(logicalConditionOperationObject->negative)
						{
							simpleNonConjunctionLogicalConditionNegative = true;
						}

						#ifdef NLC_USE_PREPROCESSOR
						bool elseIfDetected = false;
						bool elseDetected = false;
						#ifdef NLC_PREPROCESSOR_LOGICAL_CONDITION_USE_ROBUST_NLP_INDEPENDENT_CODE
						if(currentNLCsentenceInList->elseIfDetected)
						{
							elseIfDetected = true;
						}
						#else
						for(vector<GIAentityConnection*>::iterator propertyIter = logicalConditionOperationObject->propertyNodeList->begin(); propertyIter != logicalConditionOperationObject->propertyNodeList->end(); propertyIter++)
						{
							GIAentityNode* propertyEntity = (*propertyIter)->entity;
							if(propertyEntity->entityName == NLC_LOGICAL_CONDITION_OPERATIONS_ELSE_STRING)
							{//this is only known to hold using Stanford NLP
								elseIfDetected = true;
							}
						}
						#endif
						#ifdef NLC_PREPROCESSOR_LOGICAL_CONDITION_USE_ROBUST_NLP_INDEPENDENT_CODE
						if((logicalConditionOperationObject->entityName == NLC_PREPROCESSOR_LOGICAL_CONDITION_DUMMY_TEXT_ACTION) && (currentNLCsentenceInList->elseDetected))
						#else
						if(logicalConditionOperationObject->entityName == NLC_PREPROCESSOR_LOGICAL_CONDITION_DUMMY_TEXT_ACTION)
						#endif
						{
							elseDetected = true;
						}
						#endif
						#ifdef NLC_PREPROCESSOR_LOGICAL_CONDITION_USE_ROBUST_NLP_INDEPENDENT_CODE
						//perform additional checks;
						if(currentNLCsentenceInList->ifDetected || currentNLCsentenceInList->elseIfDetected || currentNLCsentenceInList->elseDetected)
						{
							if(logicalOperation != NLC_LOGICAL_CONDITION_OPERATIONS_IF)
							{
								cout << "generateCodeBlocksPart2logicalConditions{} error: (currentNLCsentenceInList->ifDetected || currentNLCsentenceInList->elseIfDetected || currentNLCsentenceInList->elseDetected) && (logicalOperation != NLC_LOGICAL_CONDITION_OPERATIONS_IF)" << endl;
							}
						}
						#endif
						if(!(currentNLCsentenceInList->hasLogicalConditionOperator))
						{
							cout << "generateCodeBlocksPart2logicalConditions{} error: !(currentNLCsentenceInList->hasLogicalConditionOperator)" << endl;
						}

						#ifdef NLC_DEBUG
						//cout << "foundConditionSubject && foundConditionObject" << endl;
						#endif
						//1. disable all classStructure formation based on condition object subset

						NLCcodeblock* currentCodeBlockInTreeAtBaseLevel = *currentCodeBlockInTree;
						NLCcodeblock* previousCodeBlockInTreeAtBaseLevel = currentCodeBlockInTreeAtBaseLevel;

						bool passedLogicalConditionObject = false;
						if((logicalOperation == NLC_LOGICAL_CONDITION_OPERATIONS_IF) && (logicalConditionOperationObject->isNetworkIndex || logicalConditionOperationObject->entityType == GIA_ENTITY_TYPE_TYPE_CONCEPT))
						{//eg If red dogs are pies, eat the cabbage
							#ifdef NLC_DEBUG
							//cout << "logicalConditionOperationObject->isConcept = " << logicalConditionOperationObject->isConcept << endl;
							#endif
							#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_BASED_ON_CONCEPTS
							//isConcept case not yet coded
							//logical operations on networkIndexes are performed by NLC (code is not generated for them by NLC as they are not performed at runtime) - eg If red dogs are pies, eat the cabbage.	[as opposed to: "if the red dog is the/a pie, eat the cabbage"]
							//verify the truth of the if statement now (if the statement is false, disable all classStructure formation based on condition subject subset)
							if(logicalConditionOperationObject->entityType == GIA_ENTITY_TYPE_TYPE_NETWORK_INDEX)
							{
								cout << "generateCodeBlocks{} error: NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_BASED_ON_CONCEPTS only handles concepts. GIA_CREATE_CONCEPTS_FOR_ALL_SENTENCES_WITH_NETWORK_INDEXES must be enabled." << endl;
								cout << "logicalConditionOperationObject = " << logicalConditionOperationObject->entityName;
							}
							else if(logicalConditionOperationObject->entityType == GIA_ENTITY_TYPE_TYPE_CONCEPT)
							{
								cout << "logicalConditionOperationObject->isConcept" << endl;
								GIAentityNode* conceptEntityCompare = logicalConditionOperationObject;	//if statement comparison...
								GIAentityNode* conceptEntityCompareNetworkIndex = getPrimaryNetworkIndexNodeDefiningInstance(conceptEntityCompare);

								logicalConditionOperationSubject->disabled = true;	//temporarily disable logicalConditionOperationSubject to prevent it from being parsed
								if(searchForEquivalentSubnetToIfStatement(conceptEntityCompareNetworkIndex, logicalConditionOperationObject, true))
								{
									if(!simpleNonConjunctionLogicalConditionNegative)
									{
										passedLogicalConditionObject = true;
									}
								}
								logicalConditionOperationSubject->disabled = false;
							}
							#endif
						}
						else if((logicalOperation == NLC_LOGICAL_CONDITION_OPERATIONS_IF) && (logicalConditionOperationObject->entityType == GIA_ENTITY_TYPE_TYPE_ACTION))	//removed || (logicalConditionOperationObject->isActionConcept) 1u15a
						{
							#ifdef NLC_USE_PREPROCESSOR
							if(elseDetected)
							{
								*currentCodeBlockInTree = createCodeBlockElse(*currentCodeBlockInTree);
								passedLogicalConditionObject = true;
							}
							else
							{
							#endif
								//eg The sun fights. If the sun fights, the dog is happy. / If the sun fights, eat the cabbage.

								#ifdef NLC_DEBUG
								//cout << "logicalConditionOperationObject->isAction" << endl;
								#endif
								#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_BASED_ON_ACTIONS
								//verify the truth of the if statement now
								//NO: get class and see if it has the relevant action (function) defined with the relevant action object
								//perform an exact trace of logicalConditionOperationObject (actionEntityCompare) with every actionEntity that matches actionEntityCompare->entityName to verify that such a specific action already [ie sentence <= currentSentence] exists (actionEntityCompare)

								GIAentityNode* actionEntityCompare = logicalConditionOperationObject;	//if statement comparison...
								GIAentityNode* actionEntityCompareNetworkIndex = getPrimaryNetworkIndexNodeDefiningInstance(actionEntityCompare);

								logicalConditionOperationSubject->disabled = true;	//temporarily disable logicalConditionOperationSubject to prevent it from being parsed
								if(searchForEquivalentSubnetToIfStatement(actionEntityCompareNetworkIndex, logicalConditionOperationObject, false))
								{
									if(!simpleNonConjunctionLogicalConditionNegative)
									{
										passedLogicalConditionObject = true;
									}
									#ifdef NLC_DEBUG
									//cout << "passedLogicalConditionObject" << endl;
									#endif
								}
								logicalConditionOperationSubject->disabled = false;
								#endif
							#ifdef NLC_USE_PREPROCESSOR
							}
							#endif
						}
						else
						{//eg If/While the sun is bright, the dog is happy. / If/While the sun is bright, eat the cabbage.	[OLD:if the red dog is the/a pie, eat the cabbage]

						#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS_ADVANCED
							/*
							eg; for all the reds dog near the park, and the blue tea trees, eat the pie
							for(all the red dog near the park)
							{
								for(all blue tea trees)
								{
									eat the pie
								}
							}

							eg; if the red dog near the park has an apple, and the tea tree is blue, eat the pie
							bool logicalCondition[100] = {false};
							if(the red dog near the park has an apple)
							{
								logicalCondition[1] = true;
							}
							if(the tea tree is blue)
							{
								logicalCondition[2] = true;
							}
							if(logicalCondition[1] && logicalCondition[2])	//where && is dynamic (it could be ||)
							{
								whileLogicalCondition = true;
								eat the pie
							}

							eg; while the red dog near the park has an apple, and the tea tree is blue, eat the pie
							bool whileLogicalCondition = true;
							while(whileLogicalCondition)
							{
								whileLogicalCondition = false;
								bool logicalCondition[100] = {false};
								if(the red dog near the park has an apple)
								{
									logicalCondition[1] = true;
								}
								if(the tea tree is blue)
								{
									logicalCondition[2] = true;
								}
								if(logicalCondition[1] && logicalCondition[2])	//where && is dynamic (it could be ||)
								{
									whileLogicalCondition = true;
									eat the pie
								}
							}
							*/

							#ifdef NLC_USE_PREPROCESSOR
							NLCcodeblock* firstCodeBlockAtStartOfElseStatement = *currentCodeBlockInTree;
							NLCcodeblock* firstCodeBlockAtStartOfIfStatement = NULL;
							NLCcodeblock* previousCodeBlockInTree = NULL;
							if(logicalOperation == NLC_LOGICAL_CONDITION_OPERATIONS_IF)
							{
								if(setCurrentCodeBlockInTreeToStartOfIfStatement(currentCodeBlockInTree, &firstCodeBlockAtStartOfIfStatement, firstCodeBlockAtStartOfElseStatement, elseIfDetected, elseDetected))
								{
									currentLogicalConditionCase[getCurrentLogicalConditionLevel()] = currentLogicalConditionCase[getCurrentLogicalConditionLevel()] + 1;
								}
								else
								{
									//!elseIfDetected
									currentLogicalConditionCase[getCurrentLogicalConditionLevel()] = 0;
								}
							}
							#endif

							#ifndef NLC_USE_PREPROCESSOR
							int currentLogicalConditionCase[1] = {0};	//multiple cases not supported (ie else if, else)
							#endif
							string whileLogicalConditionConjunctionBooleanName = generateWhileLogicalConditionConjunctionBooleanName(getCurrentLogicalConditionLevel());
							if(logicalOperation == NLC_LOGICAL_CONDITION_OPERATIONS_WHILE)
							{
								*currentCodeBlockInTree = createCodeBlockDeclareNewBoolVar(*currentCodeBlockInTree, whileLogicalConditionConjunctionBooleanName, true);
								currentCodeBlockInTreeAtBaseLevel = *currentCodeBlockInTree;
								*currentCodeBlockInTree = createCodeBlockWhileHasBool(*currentCodeBlockInTree, whileLogicalConditionConjunctionBooleanName);
								*currentCodeBlockInTree = createCodeBlockSetBoolVar(*currentCodeBlockInTree, whileLogicalConditionConjunctionBooleanName, false);
							}

							NLClogicalConditionConjunction logicalConditionConjunctionArray[NLC_MAXIMUM_NUMBER_OF_CONJUNCTIONS_IN_SENTENCE];
							int logicalConditionConjunctionIndex = 0;	// try to start all variables seen by the user at 1 instead of 0: NOT POSSIBLE HERE AS USES ARRAY
							if(logicalOperation != NLC_LOGICAL_CONDITION_OPERATIONS_FOR)
							{
								for(int i=0; i<NLC_MAXIMUM_NUMBER_OF_CONJUNCTIONS_IN_SENTENCE; i++)
								{
									logicalConditionConjunctionArray[i].conjunctionType = INT_DEFAULT_VALUE;
									logicalConditionConjunctionArray[i].negative = false;
								}
								string logicalConditionConjunctionBooleanName = generateLogicalConditionConjunctionBooleanName(getCurrentLogicalConditionLevel(), currentLogicalConditionCase[getCurrentLogicalConditionLevel()], logicalOperation);

								*currentCodeBlockInTree = createCodeBlockDeclareNewBoolArray(*currentCodeBlockInTree, logicalConditionConjunctionBooleanName, false);

								//logicalConditionOperationObject->NLCparsedForCodeBlocks = true;	//is this required?????? [NB only connections are being parsed...]
								if(logicalConditionOperationObject->negative)
								{//added 1g6i
									logicalConditionConjunctionArray[logicalConditionConjunctionIndex].negative = true;
								}
							}
							logicalConditionOperationObject->NLClogicalConditionConjunctionIndex = logicalConditionConjunctionIndex;	//set initial logicalConditionConjunctionIndex value

							if(logicalOperation == NLC_LOGICAL_CONDITION_OPERATIONS_IF)
							{
								previousCodeBlockInTreeAtBaseLevel = *currentCodeBlockInTree;
							}
							#ifdef NLC_USE_PREPROCESSOR
							previousCodeBlockInTree = *currentCodeBlockInTree;
							#endif

							#ifdef NLC_DEBUG
							//cout << "logicalConditionOperationObject = " << logicalConditionOperationObject->entityName << endl;
							#endif
							addNewLogicalCondition(currentCodeBlockInTree, logicalConditionOperationObject, sentenceIndex, logicalOperation, &logicalConditionConjunctionIndex, logicalConditionConjunctionArray, logicalConditionOperationObject);


							#ifdef NLC_USE_PREPROCESSOR
							#ifdef NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT
							//CHECKTHIS
							if((logicalOperation == NLC_LOGICAL_CONDITION_OPERATIONS_IF) || (logicalOperation == NLC_LOGICAL_CONDITION_OPERATIONS_WHILE) || (logicalOperation == NLC_LOGICAL_CONDITION_OPERATIONS_FOR))
							{
								*currentCodeBlockInTree = createCodeBlocksDeclareContextList(*currentCodeBlockInTree, currentNLCsentenceInList->indentation+1);
								(*currentCodeBlockInTree)->isLogicalCondition = true;
								(*currentCodeBlockInTree)->contextLevel = currentNLCsentenceInList->indentation+1;
								if(firstNLCsentenceInFullSentence->logicalConditionOperator == NLC_LOGICAL_CONDITION_OPERATIONS_FOR)
								{
									//must create a new code block to embed for statment
									*currentCodeBlockInTree = createCodeBlocksCreateContextBlock(*currentCodeBlockInTree);
								}
							}
							#endif
							#endif

							if(logicalOperation != NLC_LOGICAL_CONDITION_OPERATIONS_FOR)
							{
								#ifdef NLC_USE_PREPROCESSOR
								if(logicalOperation == NLC_LOGICAL_CONDITION_OPERATIONS_IF)
								{
									restoreCurrentCodeBlockInTreeToStartOfElseStatement(currentCodeBlockInTree, firstCodeBlockAtStartOfIfStatement, firstCodeBlockAtStartOfElseStatement, elseIfDetected, elseDetected, &previousCodeBlockInTree);
								}
								#endif

								#ifdef NLC_DEBUG_LOGICAL_CONDITION_CONJUNCTIONS
								cout << "conj: 1" << endl;
								#endif
								int logicalConditionConjunctionIndexMax = logicalConditionConjunctionIndex;
								//error checking:
								for(int i=1; i<logicalConditionConjunctionIndexMax; i++)	//i=0 should not have a conjunction type assigned
								{
									if(logicalConditionConjunctionArray[i].conjunctionType == INT_DEFAULT_VALUE)
									{
										cout << "generateCodeBlocksPart2logicalConditions{} error: missing conjunction type: " << i << endl;
									}
								}
								#ifdef NLC_DEBUG_LOGICAL_CONDITION_CONJUNCTIONS
								cout << "generateCodeBlocksPart2logicalConditions{}: 2" << endl;
								#endif
								if(logicalOperation == NLC_LOGICAL_CONDITION_OPERATIONS_IF)
								{
									currentCodeBlockInTreeAtBaseLevel = *currentCodeBlockInTree;
								}

								#ifndef NLC_USE_PREPROCESSOR
								bool elseIfDetected = false;
								#endif
								int logicalOperation2 = logicalOperation;
								if(logicalOperation == NLC_LOGICAL_CONDITION_OPERATIONS_WHILE)
								{
									logicalOperation2 = NLC_LOGICAL_CONDITION_OPERATIONS_IF;
								}

								*currentCodeBlockInTree = createCodeBlockLogicalConditionConjunctionOfBools(*currentCodeBlockInTree, logicalOperation2, logicalConditionConjunctionArray, logicalConditionConjunctionIndexMax, getCurrentLogicalConditionLevel(), currentLogicalConditionCase[getCurrentLogicalConditionLevel()], elseIfDetected);

								if(logicalOperation == NLC_LOGICAL_CONDITION_OPERATIONS_WHILE)
								{
									*currentCodeBlockInTree = createCodeBlockSetBoolVar(*currentCodeBlockInTree, whileLogicalConditionConjunctionBooleanName, true);
								}
								#ifdef NLC_DEBUG_LOGICAL_CONDITION_CONJUNCTIONS
								cout << "generateCodeBlocksPart2logicalConditions{}: 3" << endl;
								#endif

							}
						#else
							//this code is suitable for for/while/if logical conditions without conjunctions:

							//code copied from [*^]
							//handle property logical operations; eg "If the sun is bright" in "If the sun is bright, the dog is happy"
							NLCgenerateContextBlocksVariables generateContextBlocksVariables;
							generateContextBlocksVariables.onlyGenerateContextBlocksIfConnectionsParsedForNLCorSameReferenceSet = false;
							generateContextBlocksVariables.logicalOperation = logicalOperation;
							generateContextBlocksVariables.negative = simpleNonConjunctionLogicalConditionNegative;
								//NB this will set NLCparsedForCodeBlocks to true, so NLCparsedForlogicalConditionOperations can be set to false without causing any problems (ie generateCodeBlocksPart3actions/generateCodeBlocksPart4objectInitialisations will not reparse the if statement)	//CHECKTHIS; AndInitialiseParentIfNecessary component

							#ifdef NLC_LOGICAL_CONDITION_OPERATIONS_SUPPORT_INDEFINITE_LOGICAL_CONDITION_OBJECTS
							if(!assumedToAlreadyHaveBeenDeclared(logicalConditionOperationObject))
							{
								#ifdef NLC_GENERATE_TYPE_LISTS
								//1i implementation
								currentCodeBlockInTree = createCodeBlockForPropertyTypeClass(currentCodeBlockInTree, logicalConditionOperationObject);	//eg "If a house is green, do this", an instanceList (OLD: localList) for "a house" is assumed to have already been declared, one of which may be green, so search all house instanceLists within house typeList...
								//if at least one instanceList of type currentLogicalConditionObject has not previously been declared, then the code will result in a compilation error
								//if at least one instanceList of type currentLogicalConditionObject has previously been declared, but does not have the required properties (eg green), then the code will compile but the if statement will fail
								#else
								//1j implementation
								entity->grammaticalDefiniteTemp = true;		//set NLClocalListVariableHasBeenInitialised instead?
								#endif
							}
							#endif
							getParentAndGenerateContextBlocks(currentCodeBlockInTree, logicalConditionOperationObject, sentenceIndex, &generateContextBlocksVariables);

							tagAllEntitiesInSentenceSubsetAsPertainingToLogicalConditionOperationAdvanced(logicalConditionOperationObject, sentenceIndex, false);	//used to enable class definition printing of conditional statements

						#endif

							passedLogicalConditionObject = true;
						}

						if(passedLogicalConditionObject)
						{
							#ifdef NLC_DEBUG_LOGICAL_CONDITION_CONJUNCTIONS
							cout << "generateCodeBlocksPart2logicalConditions{}: 4" << endl;
							#endif
							//check if logicalConditionOperationSubject is special "do" action with "this" action; if so ignore it and look for following indented sentences

							if(logicalConditionOperationSubject->isNetworkIndex || logicalConditionOperationSubject->entityType == GIA_ENTITY_TYPE_TYPE_CONCEPT)
							{
								#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_BASED_ON_CONCEPTS
								if(logicalConditionOperationSubject->entityType == GIA_ENTITY_TYPE_TYPE_NETWORK_INDEX)
								{
									cout << "generateCodeBlocks{} error: NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_BASED_ON_CONCEPTS only handles concepts. GIA_CREATE_CONCEPTS_FOR_ALL_SENTENCES_WITH_NETWORK_INDEXES must be enabled." << endl;
									cout << "logicalConditionOperationSubject = " << logicalConditionOperationSubject->entityName;
								}
								else if(logicalConditionOperationSubject->entityType == GIA_ENTITY_TYPE_TYPE_CONCEPT)
								{
									tagAllEntitiesInSentenceSubsetAsPertainingToLogicalConditionOperationAdvanced(logicalConditionOperationSubject, sentenceIndex, false);
								}
								#endif
							}
							else
							{
								if(logicalConditionOperationSubject->entityType == GIA_ENTITY_TYPE_TYPE_ACTION)
								{
									#ifdef NLC_USE_PREPROCESSOR
									if(logicalConditionOperationSubject->entityName == NLC_PREPROCESSOR_LOGICAL_CONDITION_DUMMY_TEXT_ACTION)
									{
										//eg If the sun is bright, do this.
										//leave action entity as tagged NLCparsedForlogicalConditionOperations (such that it is not processed by generateActionCodeBlocks)
										//assume the next line(s) is indented and contains the real logical condition command
									}
									else
									{
									#endif
										//eg If the sun is bright, eat the cabbage.
										tagAllEntitiesInSentenceSubsetAsPertainingToLogicalConditionOperationAdvanced(logicalConditionOperationSubject, sentenceIndex, false);	//used to enable class definition printing of conditional statements

										generateActionCodeBlocks(currentCodeBlockInTree, logicalConditionOperationSubject, sentenceIndex, NLCfunctionName);
									#ifdef NLC_USE_PREPROCESSOR
									}
									#endif
								}
								else
								{
									//eg If the sun is bright, the dog is happy.
									tagAllEntitiesInSentenceSubsetAsPertainingToLogicalConditionOperationAdvanced(logicalConditionOperationSubject, sentenceIndex, false);	//used to enable class definition printing of conditional statements

									#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
									generateCodeBlocksObjectInitialisationsForEntity(currentCodeBlockInTree, logicalConditionOperationSubject, sentenceIndex);
									#else
									GIAentityNode* parentEntity = getParent(logicalConditionOperationSubject, sentenceIndex, true);		//CHECKTHIS check parseConditionParents value here
									if(!generateParentInitialisationCodeBlockWithChecks(currentCodeBlockInTree, parentEntity, sentenceIndex, false, false))
									{
										generateObjectInitialisationsBasedOnPropertiesAndConditions(logicalConditionOperationSubject, currentCodeBlockInTree , sentenceIndex, "", "", false, false);
									}
									#endif
								}

								#ifdef NLC_USE_PREPROCESSOR
								if(useNLCpreprocessor)
								{
									if((logicalOperation == NLC_LOGICAL_CONDITION_OPERATIONS_IF) && !elseIfDetected && !elseDetected)
									{
										#ifdef NLC_DEBUG
										//cout << "codeBlockAtPreviousLogicalConditionBaseStartOfIfStatementLevelArray " << getCurrentLogicalConditionLevel() << "is being defined" << endl;
										#endif
										codeBlockAtPreviousLogicalConditionBaseStartOfIfStatementLevelArray[getCurrentLogicalConditionLevel()] = previousCodeBlockInTreeAtBaseLevel;
									}

									currentSentenceContainsLogicalCondition = true;
									if(currentNLCsentenceInList->next->indentation == (currentNLCsentenceInList->indentation + 1))
									{
										//do not, just record the in the tree
										codeBlockAtPreviousLogicalConditionBaseLevelArray[getCurrentLogicalConditionLevel()] = currentCodeBlockInTreeAtBaseLevel->next;
										setCurrentLogicalConditionLevel(getCurrentLogicalConditionLevel + 1);
									}
									else if(currentNLCsentenceInList->next->indentation <= currentNLCsentenceInList->indentation)
									{
										*currentCodeBlockInTree = currentCodeBlockInTreeAtBaseLevel->next;
										//NB if(currentNLCsentenceInList->next->indentation < currentNLCsentenceInList->indentation) will be processed later by generateCodeBlocks()
									}
									else
									{
										cout << "NLC_USE_PREPROCESSOR generateCodeBlocksPart2logicalConditions{} error: invalid indentation of currentNLCsentenceInList->next, sentenceIndex = " << sentenceIndex << endl;
										cout << "currentNLCsentenceInList->next->indentation <= currentNLCsentenceInList->indentation + 1" << endl;
										cout << "currentNLCsentenceInList->indentation = " << currentNLCsentenceInList->indentation << endl;
										cout << "currentNLCsentenceInList->next->indentation = " << currentNLCsentenceInList->next->indentation << endl;
									}
								}
								else
								{
									*currentCodeBlockInTree = currentCodeBlockInTreeAtBaseLevel->next;
								}
								#else
								*currentCodeBlockInTree = currentCodeBlockInTreeAtBaseLevel->next;
								#endif
							}
							#ifdef NLC_DEBUG_LOGICAL_CONDITION_CONJUNCTIONS
							cout << "generateCodeBlocksPart2logicalConditions{}: 5" << endl;
							#endif
						}
					}
				}
			}
		}
	}
	return true;
}

#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS_ADVANCED
void addNewLogicalCondition(NLCcodeblock** currentCodeBlockInTree, GIAentityNode* currentLogicalConditionObject, int sentenceIndex, int logicalOperation, int* logicalConditionConjunctionIndex, NLClogicalConditionConjunction* logicalConditionConjunctionArray, GIAentityNode* previousLogicalConditionConjunction)
{
	NLCcodeblock* currentCodeBlockInTreeAtCurrentLevel1 = *currentCodeBlockInTree;

	#ifdef NLC_DEBUG_LOGICAL_CONDITION_CONJUNCTIONS
	cout << "addNewLogicalCondition{}: currentLogicalConditionObject = " << currentLogicalConditionObject->entityName << endl;
	#endif

	if(logicalOperation == NLC_LOGICAL_CONDITION_OPERATIONS_FOR)
	{
		//set currentLogicalConditionObject to isDefiniteTemp, eg "chicken" in "For every/each chicken.." NB "chicken" in "For all chickens..." is parsed as definite by GIA fillGrammaticalArraysStanford() already
		currentLogicalConditionObject->grammaticalDefiniteTemp = true;
	}

	//handle property logical operations; eg "If the sun is bright" in "If the sun is bright, the dog is happy"
	NLCgenerateContextBlocksVariables generateContextBlocksVariables;
	generateContextBlocksVariables.onlyGenerateContextBlocksIfConnectionsParsedForNLCorSameReferenceSet = false;
	generateContextBlocksVariables.logicalOperation = logicalOperation;
	generateContextBlocksVariables.logicalConditionConjunctionIndex = *logicalConditionConjunctionIndex;
	generateContextBlocksVariables.primaryEntityInLogicalConditionConjunctionSubset = previousLogicalConditionConjunction;
		//NB this will set NLCparsedForCodeBlocks to true, so NLCparsedForlogicalConditionOperations can be set to false without causing any problems (ie generateCodeBlocksPart3actions/generateCodeBlocksPart4objectInitialisations will not reparse the if statement)	//CHECKTHIS; AndInitialiseParentIfNecessary component

	if(checkSentenceIndexParsingCodeBlocks(currentLogicalConditionObject, sentenceIndex, false))
	{
		#ifdef NLC_LOGICAL_CONDITION_OPERATIONS_SUPPORT_INDEFINITE_LOGICAL_CONDITION_OBJECTS
		if(!assumedToAlreadyHaveBeenDeclared(currentLogicalConditionObject))
		{
			#ifdef NLC_GENERATE_TYPE_LISTS
			//1i implementation
			currentCodeBlockInTree = createCodeBlockForPropertyTypeClass(currentCodeBlockInTree, currentLogicalConditionObject);	//eg "If a house is green, do this", an instanceList (OLD: localList) for "a house" is assumed to have already been declared, one of which may be green, so search all house instanceLists within house typeList...
			//if at least one instanceList of type currentLogicalConditionObject has not previously been declared, then the code will result in a compilation error
			//if at least one instanceList of type currentLogicalConditionObject has previously been declared, but does not have the required properties (eg green), then the code will compile but the if statement will fail
			#else
			//1j implementation
			entity->grammaticalDefiniteTemp = true;		//set NLClocalListVariableHasBeenInitialised instead?
			#endif
		}
		#endif
		getParentAndGenerateContextBlocks(currentCodeBlockInTree, currentLogicalConditionObject, sentenceIndex, &generateContextBlocksVariables))

		if(logicalOperation != NLC_LOGICAL_CONDITION_OPERATIONS_FOR)
		{
			#ifndef NLC_USE_PREPROCESSOR
			int currentLogicalConditionCase[1] = {0};	//multiple cases not supported
			#endif
			string logicalConditionConjunctionBooleanName = generateLogicalConditionConjunctionBooleanName(getCurrentLogicalConditionLevel(), currentLogicalConditionCase[getCurrentLogicalConditionLevel()],* logicalConditionConjunctionIndex, logicalOperation);
			*currentCodeBlockInTree = createCodeBlockSetBoolVar(*currentCodeBlockInTree, logicalConditionConjunctionBooleanName, true);
			currentCodeBlockInTreeAtCurrentLevel1 = currentCodeBlockInTreeAtCurrentLevel1->next;
			*currentCodeBlockInTree = currentCodeBlockInTreeAtCurrentLevel1;
		}
		*logicalConditionConjunctionIndex = *logicalConditionConjunctionIndex + 1;
		#ifdef NLC_DEBUG_LOGICAL_CONDITION_CONJUNCTIONS
		cout << "*logicalConditionConjunctionIndex = " <<* logicalConditionConjunctionIndex << endl;
		#endif
	}
	else
	{
		*currentCodeBlockInTree = currentCodeBlockInTreeAtCurrentLevel1;
	}

	tagAllEntitiesInSentenceSubsetAsPertainingToLogicalConditionOperationAdvanced(currentLogicalConditionObject, sentenceIndex, false);	//used to enable class definition printing of conditional statements

	if(generateContextBlocksVariables.foundLogicalConditionConjunction != NULL)
	{
		#ifdef NLC_DEBUG_LOGICAL_CONDITION_CONJUNCTIONS
		cout << "generateContextBlocksVariables.foundLogicalConditionConjunction defined: " << generateContextBlocksVariables.foundLogicalConditionConjunction->entityName << endl;
		cout << "generateContextBlocksVariables.foundLogicalConditionConjunction->subject: " << (generateContextBlocksVariables.foundLogicalConditionConjunction->conditionObjectEntity->back())->entity->entityName << endl;
		#endif
		checkConditionForLogicalCondition(currentCodeBlockInTree, generateContextBlocksVariables.foundLogicalConditionConjunction, sentenceIndex, logicalOperation, logicalConditionConjunctionIndex, logicalConditionConjunctionArray);
	}

	#ifdef NLC_DEBUG_LOGICAL_CONDITION_CONJUNCTIONS
	cout << "addNewLogicalCondition{}: end" << endl;
	#endif
}

void checkConditionForLogicalCondition(NLCcodeblock** currentCodeBlockInTree, GIAentityNode* conditionEntity, int sentenceIndex, int logicalOperation, int* logicalConditionConjunctionIndex, NLClogicalConditionConjunction* logicalConditionConjunctionArray)
{
	int conjunctionType = INT_DEFAULT_VALUE;
	bool conjunctionConditionFound = textInTextArray(conditionEntity->entityName, entityCoordinatingConjunctionArray, ENTITY_COORDINATINGCONJUNCTION_ARRAY_NUMBER_OF_TYPES, &conjunctionType);
	if(conjunctionConditionFound)
	{
		if(!(conditionEntity->NLCconjunctionCondition))
		{
			#ifdef NLC_DEBUG
			//cout << "conditionEntity = " << conditionEntity->entityName << endl;
			#endif
			conditionEntity->NLCconjunctionCondition = true;
			GIAentityConnection* logicalConditionConjunctionObjectConnection = conditionEntity->conditionObjectEntity->back();
			GIAentityConnection* logicalConditionConjunctionSubjectConnection = conditionEntity->conditionSubjectEntity->back();
			GIAentityNode* logicalConditionConjunctionObjectEntity = logicalConditionConjunctionObjectConnection->entity;
			GIAentityNode* logicalConditionConjunctionSubjectEntity = logicalConditionConjunctionSubjectConnection->entity;

			if(checkSentenceIndexParsingCodeBlocks(logicalConditionConjunctionObjectEntity, logicalConditionConjunctionObjectConnection, sentenceIndex, false))
			{//added 1g7a for safety: shouldnt be required
				if(logicalConditionConjunctionSubjectEntity->NLClogicalConditionConjunctionIndex != INT_DEFAULT_VALUE)
				{
					#ifdef NLC_DEBUG_LOGICAL_CONDITION_CONJUNCTIONS
					cout << "logicalConditionConjunctionSubjectEntity->NLClogicalConditionConjunctionIndex != INT_DEFAULT_VALUE: " << logicalConditionConjunctionSubjectEntity->NLClogicalConditionConjunctionIndex << endl;
					#endif
					if(logicalConditionConjunctionSubjectEntity->NLClogicalConditionConjunctionIndex > 0)
					{//conjunction type (eg and/or) is not set for first logicalCondition in array
						logicalConditionConjunctionArray[logicalConditionConjunctionSubjectEntity->NLClogicalConditionConjunctionIndex].conjunctionType = conjunctionType;
					}
					logicalConditionConjunctionArray[logicalConditionConjunctionSubjectEntity->NLClogicalConditionConjunctionIndex].negative = logicalConditionConjunctionSubjectEntity->negative;
					(conditionEntity->conditionSubjectEntity->back())->NLCparsedForCodeBlocks = true;
				}
				else
				{
					cout << "checkConditionForLogicalCondition{} error: logicalConditionConjunctionSubjectEntity = " << logicalConditionConjunctionSubjectEntity->entityName << endl;
					cout << "logicalConditionConjunctionSubjectEntity->NLClogicalConditionConjunctionIndex == INT_DEFAULT_VALUE" << endl;
				}

				if(logicalConditionConjunctionObjectEntity->NLClogicalConditionConjunctionIndex != INT_DEFAULT_VALUE)
				{
					#ifdef NLC_DEBUG_LOGICAL_CONDITION_CONJUNCTIONS
					cout << "logicalConditionConjunctionObjectEntity->NLClogicalConditionConjunctionIndex != INT_DEFAULT_VALUE: " << logicalConditionConjunctionObjectEntity->NLClogicalConditionConjunctionIndex << endl;
					#endif
					if(logicalConditionConjunctionObjectEntity->NLClogicalConditionConjunctionIndex > 0)
					{//conjunction type (eg and/or) is not set for first logicalCondition in array
						logicalConditionConjunctionArray[logicalConditionConjunctionObjectEntity->NLClogicalConditionConjunctionIndex].conjunctionType = conjunctionType;
					}
					logicalConditionConjunctionArray[logicalConditionConjunctionObjectEntity->NLClogicalConditionConjunctionIndex].negative = logicalConditionConjunctionObjectEntity->negative;
					(conditionEntity->conditionObjectEntity->back())->NLCparsedForCodeBlocks = true;
				}
				else
				{
					#ifdef NLC_DEBUG_LOGICAL_CONDITION_CONJUNCTIONS
					cout << "logicalConditionConjunctionObjectEntity->NLClogicalConditionConjunctionIndex == INT_DEFAULT_VALUE: " << logicalConditionConjunctionObjectEntity->NLClogicalConditionConjunctionIndex << endl;
					#endif
					logicalConditionConjunctionObjectEntity->NLClogicalConditionConjunctionIndex = *logicalConditionConjunctionIndex;	//set initial logicalConditionConjunctionIndex value
					if(logicalConditionConjunctionObjectEntity->NLClogicalConditionConjunctionIndex > 0)
					{//conjunction type (eg and/or) is not set for first logicalCondition in array
						logicalConditionConjunctionArray[logicalConditionConjunctionObjectEntity->NLClogicalConditionConjunctionIndex].conjunctionType = conjunctionType;
					}
					logicalConditionConjunctionArray[logicalConditionConjunctionObjectEntity->NLClogicalConditionConjunctionIndex].negative = logicalConditionConjunctionObjectEntity->negative;
					(conditionEntity->conditionObjectEntity->back())->NLCparsedForCodeBlocks = true;

					if(logicalConditionConjunctionObjectEntity->entityType == GIA_ENTITY_TYPE_TYPE_CONDITION)
					{//added 1g5g
						addNewLogicalCondition(currentCodeBlockInTree, (logicalConditionConjunctionObjectEntity->conditionSubjectEntity->back())->entity, sentenceIndex, logicalOperation, logicalConditionConjunctionIndex, logicalConditionConjunctionArray, logicalConditionConjunctionObjectEntity);
					}
					else
					{
						addNewLogicalCondition(currentCodeBlockInTree, logicalConditionConjunctionObjectEntity, sentenceIndex, logicalOperation, logicalConditionConjunctionIndex, logicalConditionConjunctionArray, logicalConditionConjunctionObjectEntity);
					}
				}
			}
			else
			{
				cout << "addNewLogicalCondition{} error: logicalConditionConjunctionObjectEntity has bad sentence index" << endl;
			}
		}
		else
		{
			cout << "addNewLogicalCondition{} error: (conditionEntity->NLCconjunctionCondition)" << endl;
		}
	}
}

#endif


void tagAllEntitiesInSentenceSubsetAsPertainingToLogicalConditionOperationAdvanced(GIAentityNode* entity, int sentenceIndex, bool tagOrUntag)
{
	for(int i=0; i<GIA_ENTITY_NUMBER_OF_VECTOR_CONNECTION_TYPES; i++)
	{
		if(i != GIA_ENTITY_VECTOR_CONNECTION_TYPE_NODE_DEFINING_INSTANCE)
		{
			for(vector<GIAentityConnection*>::iterator connectionIter = entity->entityVectorConnectionsArray[i].begin(); connectionIter != entity->entityVectorConnectionsArray[i].end(); connectionIter++)
			{
				GIAentityConnection* connection = (*connectionIter);
				GIAentityNode* connectedEntity = connection->entity;
				if((tagOrUntag && !(connectedEntity->NLCparsedForlogicalConditionOperations)) || (!tagOrUntag && (connectedEntity->NLCparsedForlogicalConditionOperations)))
				{
					if(!(connectedEntity->NLClogicalConditionOperation))
					{//don't cross the "if" boundary
						if(checkSentenceIndexParsingCodeBlocks(connectedEntity, connection, sentenceIndex, false))
						{
							if(connectedEntity->entityType == GIA_ENTITY_TYPE_TYPE_NETWORK_INDEX)
							{
								cout << "tagAllEntitiesInSentenceSubsetAsPertainingToLogicalConditionOperationAdvanced{} error: NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_BASED_ON_CONCEPTS only handles concepts. GIA_CREATE_CONCEPTS_FOR_ALL_SENTENCES_WITH_NETWORK_INDEXES must be enabled." << endl;
								cout << "connectedEntity = " << connectedEntity->entityName;
							}
							else
							{
								#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_BASED_ON_ACTIONS
								connectedEntity->referenceSetID = NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_BASED_ON_ACTIONS_OR_NETWORK_INDEXES_DUMMY_REFERENCE_SET_ID;
								#endif
								if(tagOrUntag)
								{
									#ifdef NLC_DEBUG
									//cout << "tagAllEntitiesInSentenceSubsetAsPertainingToLogicalConditionOperationAdvanced{}: tagged: " << connectedEntity->entityName << endl;
									#endif
									connection->NLCparsedForlogicalConditionOperations = true;
									connectedEntity->NLCparsedForlogicalConditionOperations = true;
								}
								else
								{
									#ifdef NLC_DEBUG
									//cout << "tagAllEntitiesInSentenceSubsetAsPertainingToLogicalConditionOperationAdvanced{}: untagged: " << connectedEntity->entityName << endl;
									#endif
									connection->NLCparsedForlogicalConditionOperations = false;
									connectedEntity->NLCparsedForlogicalConditionOperations = false;
								}
								tagAllEntitiesInSentenceSubsetAsPertainingToLogicalConditionOperationAdvanced(connectedEntity, sentenceIndex, tagOrUntag);
							}
						}
					}
				}
			}
		}
	}
}


#ifdef NLC_USE_PREPROCESSOR
bool setCurrentCodeBlockInTreeToStartOfIfStatement(NLCcodeblock** currentCodeBlockInTree, NLCcodeblock** firstCodeBlockAtStartOfIfStatement, NLCcodeblock* firstCodeBlockAtStartOfElseStatement, bool elseIfDetected, bool elseDetected)
{
	bool result = false;
	if(useNLCpreprocessor)
	{
		if(elseDetected || elseIfDetected)
		{
			if(codeBlockAtPreviousLogicalConditionBaseStartOfIfStatementLevelArray[getCurrentLogicalConditionLevel()] != NULL)
			{
				result = true;
				#ifdef NLC_DEBUG
				cout << "setCurrentCodeBlockInTreeToStartOfIfStatement{}:" << endl;
				#endif
				*firstCodeBlockAtStartOfIfStatement = codeBlockAtPreviousLogicalConditionBaseStartOfIfStatementLevelArray[getCurrentLogicalConditionLevel()]->next;
				*currentCodeBlockInTree = codeBlockAtPreviousLogicalConditionBaseStartOfIfStatementLevelArray[getCurrentLogicalConditionLevel()];
				(*currentCodeBlockInTree)->next = new NLCcodeblock; //temporarily disconnect the if statment such that additional condition bools can be declared (required for new else statement)
				(*currentCodeBlockInTree) = (*currentCodeBlockInTree)->next;
			}
			else
			{
				cout << "setCurrentCodeBlockInTreeToStartOfIfStatement{} error: codeBlockAtPreviousLogicalConditionBaseStartOfIfStatementLevelArray[getCurrentLogicalConditionLevel()] is undefined and new else (if) statement is being created" << endl;
			}
		}
	}
	return result;
}

bool restoreCurrentCodeBlockInTreeToStartOfElseStatement(NLCcodeblock** currentCodeBlockInTree, NLCcodeblock* firstCodeBlockAtStartOfIfStatement, NLCcodeblock* firstCodeBlockAtStartOfElseStatement, bool elseIfDetected, bool elseDetected, NLCcodeblock** previousCodeBlockInTree)
{
	bool result = false;
	if(useNLCpreprocessor)
	{
		if(elseIfDetected || elseDetected)
		{
			#ifdef NLC_DEBUG
			cout << "restoreCurrentCodeBlockInTreeToStartOfElseStatement{}:" << endl;
			#endif
			//restore currentCodeBlockInTree
			(*previousCodeBlockInTree)->next = firstCodeBlockAtStartOfIfStatement;
			*currentCodeBlockInTree = firstCodeBlockAtStartOfElseStatement;
			result = true;
		}
	}
	return result;
}
#endif


#endif

#ifdef GIA_TRANSLATOR_DREAM_MODE_LINK_SPECIFIC_CONCEPTS_AND_ACTIONS
bool searchForEquivalentSubnetToIfStatement(GIAentityNode* entityCompareNetworkIndex, GIAentityNode* entity, bool compareConcepts)
{
	bool result = false;

	//code copied from identifyReferenceSetsSpecificConceptsAndLinkWithConcepts() in GIAtranslatorDefineReferencing.cpp

	int referenceSetID = NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_BASED_ON_ACTIONS_OR_NETWORK_INDEXES_DUMMY_REFERENCE_SET_ID;

	bool traceModeIsQuery = false;
	GIAreferenceTraceParameters referenceTraceParameters;
	referenceTraceParameters.referenceSetID = referenceSetID;
	referenceTraceParameters.sameReferenceSetTests = true;
	if(!compareConcepts)
	{
		referenceTraceParameters.linkSpecificConceptsAndActions = true;
	}

	for(vector<GIAentityConnection*>::iterator entityIter = entityCompareNetworkIndex->associatedInstanceNodeList->begin(); entityIter != entityCompareNetworkIndex->associatedInstanceNodeList->end(); entityIter++)
	{
		GIAentityNode* entityCompare = (*entityIter)->entity;
		#ifdef GIA_DREAMMODE_REFERENCING_DEBUG
		cout << "searchForEquivalentSubnetToIfStatement{}: identifyReferenceSetsSpecificConcepts: " << entityCompare->entityName << endl;
		#endif

		if(!(entityCompare->disabled))
		{
			if(entity != entityCompare)
			{
				GIAqueryTraceParameters queryTraceParameters;		//not used

				#ifdef NLC_DEBUG
				//cout << "searchForEquivalentSubnetToIfStatement{}:" << endl;
				//cout << "entityCompare->entityName = " << entityCompare->entityName << endl;
				//cout << "entity->entityName = " << entity->entityName << endl;
				#endif

				int numberOfMatchedNodesTemp = 0;
				int numberOfMatchedNodesRequiredSynonymnDetectionTemp = 0;
				bool exactMatch = testReferencedEntityNodeForExactNameMatch2(entity, entityCompare, &numberOfMatchedNodesTemp, false, &numberOfMatchedNodesRequiredSynonymnDetectionTemp, traceModeIsQuery, &queryTraceParameters, &referenceTraceParameters);

				if(exactMatch)
				{
					if(numberOfMatchedNodesTemp > 0)
					{
						#ifdef NLC_DEBUG
						//cout << "exactMatch: numberOfMatchedNodesTemp = " << numberOfMatchedNodesTemp << endl;
						#endif
						result = true;
					}
				}

				//now reset the matched nodes as unpassed (required such that they are retracable using a the different path)
				int irrelevant;
				string printEntityNodeString = "";
				bool traceInstantiations = GIA_QUERY_TRACE_NETWORK_INDEX_NODES_DEFINING_INSTANTIATIONS_VALUE;
				traceEntityNode(entityCompare, GIA_QUERY_TRACE_ENTITY_NODES_FUNCTION_RESET_TESTEDFORQUERYCOMPARISONTEMP, &irrelevant, &printEntityNodeString, false, NULL, traceInstantiations);
				traceEntityNode(entity, GIA_QUERY_TRACE_ENTITY_NODES_FUNCTION_RESET_TESTEDFORQUERYCOMPARISONTEMP, &irrelevant, &printEntityNodeString, false, NULL, traceInstantiations);
			}
		}
	}
	return result;
}
#endif


