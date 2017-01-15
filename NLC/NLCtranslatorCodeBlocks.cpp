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
 * Project Version: 1g14b 15-July-2014
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/



#include <ctime>
#include <cstdlib>	//for random number generation
#include <cmath>

#include "NLCtranslatorCodeBlocks.h"
#include "NLCtranslatorCodeBlocksOperations.h"
#include "GIAquery.h"
#include "GIAtranslatorOperations.h"	//required for textInTextArray()

bool generateCodeBlocks(NLCcodeblock * firstCodeBlockInTree, vector<GIAentityNode*> * entityNodesActiveListComplete, int maxNumberSentences, string NLCfunctionName)
{
	bool result = true;

	NLCcodeblock * currentCodeBlockInTree = firstCodeBlockInTree;

	#ifdef NLC_NOT_NECESSARY
	vector<NLCitem *> implictlyDeclaredFunctionList;	//implictlyDeclaredFunctionList is used to capture implicitly declared functions; to be added to object class definitions at end
	vector<NLCitem *> implictlyDeclaredFunctionListTopLevel;	//top level function list (used to store implicitly declared functions without subject/context/owner)
	#endif

	currentCodeBlockInTree = createCodeBlockNewFunction(currentCodeBlockInTree, NLCfunctionName, entityNodesActiveListComplete);

	//NLCcodeblock * nextCodeBlockInTree = NULL;	//not used now; assume only 1 command in text
	//for each action (command) in sentence;

	//cout << "maxNumberSentences = " << maxNumberSentences << endl;
	for(int sentenceIndex=1; sentenceIndex <= maxNumberSentences; sentenceIndex++)
	{
		#ifdef NLC_DEBUG
		cout << "*** sentenceIndex = " << sentenceIndex << endl;
		#endif

		#ifdef NLC_DEFINE_LOCAL_VARIABLES_FOR_ALL_INDEFINATE_ENTITIES
		//Part Prep A - declareLocalVariables (for non-specific indefinte entities, eg "a chicken", not "a blue chicken") - added 1g8a;
		#ifdef NLC_DEBUG
		cout << "generateCodeBlocksPart1declareLocalVariables:" << endl;
		#endif
		declareLocalPropertyListsForIndefiniteEntities(&currentCodeBlockInTree, entityNodesActiveListComplete, sentenceIndex, NLCfunctionName);	//added 1g8a 11-July-2014
		#endif
		
		#ifdef NLC_SUPPORT_CONDITION_LOGICAL_OPERATIONS
		//Part 1 - logical conditions (eg If the house is red, ride the boat) - added 1f1a;
		#ifdef NLC_DEBUG
		cout << "generateCodeBlocksPart2logicalConditions:" << endl;
		#endif
		if(!generateCodeBlocksPart2logicalConditions(&currentCodeBlockInTree, entityNodesActiveListComplete, sentenceIndex, NLCfunctionName))
		{
			result = false;
		}
		#endif

		//Part 2; actions (eg Tom rides the boat)
		#ifdef NLC_DEBUG
		cout << "generateCodeBlocksPart3actions:" << endl;
		#endif
		if(!generateCodeBlocksPart3actions(&currentCodeBlockInTree, entityNodesActiveListComplete, sentenceIndex, NLCfunctionName))
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
		
		#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
		clearContextGeneratedVariable(entityNodesActiveListComplete);
		#endif
	}
	return result;
}

bool declareLocalPropertyListsForIndefiniteEntities(NLCcodeblock ** currentCodeBlockInTree, vector<GIAentityNode*> * entityNodesActiveListComplete, int sentenceIndex, string NLCfunctionName)
{
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode * entity = (*entityIter);
		if(!(entity->isConcept) && !(entity->isAction) && !(entity->isSubstanceQuality) && !(entity->isSubstanceConcept) && !(entity->isCondition) && !(entity->isActionConcept))
		{
			//cout << "pass1: " << entity->entityName << endl;
			if(checkSentenceIndexParsingCodeBlocks(entity, sentenceIndex, false))
			{
				//cout << "pass2: " << entity->entityName << endl;
				if(!assumedToAlreadyHaveBeenDeclared(entity))
				{//indefinite entity found
					if(!(entity->NLClocalListVariableHasBeenDeclared))
					{
						//cout << "pass3: " << entity->entityName << endl;
						/*OLD declareLocalPropertyListsForAllNonSpecificIndefiniteEntities() code;
						bool foundPropertyInSameSentence = false;
						bool foundConditionInSameSentence = false;
						for(vector<GIAentityConnection*>::iterator propertyNodeListIterator = entity->propertyNodeList->begin(); propertyNodeListIterator < entity->propertyNodeList->end(); propertyNodeListIterator++)
						{
							GIAentityNode* propertyEntity = (*propertyNodeListIterator)->entity;
							if(checkSentenceIndexParsingCodeBlocks(propertyEntity, sentenceIndex, false))
							{
								foundPropertyInSameSentence = true;
							}
						}
						for(vector<GIAentityConnection*>::iterator conditionNodeListIterator = entity->conditionNodeList->begin(); conditionNodeListIterator < entity->conditionNodeList->end(); conditionNodeListIterator++)
						{
							GIAentityNode* conditionEntity = (*conditionNodeListIterator)->entity;
							if(checkSentenceIndexParsingCodeBlocks(conditionEntity, sentenceIndex, false))
							{
								foundConditionInSameSentence = true;
							}
						}
						if(!foundPropertyInSameSentence && !foundConditionInSameSentence)
						{
						*/
						*currentCodeBlockInTree = createCodeBlocksDeclareNewLocalListVariable(*currentCodeBlockInTree, entity);
						#ifdef NLC_DEBUG
						cout << "declareLocalPropertyListsForIndefiniteEntities(): createCodeBlocksDeclareNewLocalListVariable for " << entity->entityName << endl;
						#endif
						entity->NLClocalListVariableHasBeenDeclared = true;
						/*	
						}
						*/
					}
				}
			}
		}
	}
}

#ifdef NLC_SUPPORT_CONDITION_LOGICAL_OPERATIONS
bool generateCodeBlocksPart2logicalConditions(NLCcodeblock ** currentCodeBlockInTree, vector<GIAentityNode*> * entityNodesActiveListComplete, int sentenceIndex, string NLCfunctionName)
{
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode * logicalConditionEntity = (*entityIter);
		if(logicalConditionEntity->isCondition)
		{
			if(checkSentenceIndexParsingCodeBlocks(logicalConditionEntity, sentenceIndex, true))	//could be set to false instead
			{
				bool foundLogicalConditionOperation = false;
				int logicalOperation = INT_DEFAULT_VALUE;
				if(logicalConditionEntity->NLClogicalConditionOperation)	//used to test more complex sentence context requirements of some logical condition operations eg "for" is required to be immediately succeeded by "each", "all", or every
				{
					bool foundLogicalConditionOperationBasic = textInTextArray(logicalConditionEntity->entityName, logicalConditionOperationsArray, NLC_LOGICAL_CONDITION_OPERATIONS_NUMBER_OF_TYPES, &logicalOperation);
					if((logicalOperation == NLC_CONDITION_LOGICAL_OPERATIONS_FOR) || (logicalOperation == NLC_CONDITION_LOGICAL_OPERATIONS_IF) || (logicalOperation == NLC_CONDITION_LOGICAL_OPERATIONS_WHILE))
					{//these are the only logical condition operations supported by NLC at this time
						foundLogicalConditionOperation = true;
					}
				}
				if(foundLogicalConditionOperation)
				{	
					GIAentityNode * logicalConditionSubject = NULL;
					GIAentityNode * logicalConditionObject = NULL;
					bool foundConditionSubject = false;
					bool foundConditionObject = false;
					if(!(logicalConditionEntity->conditionSubjectEntity->empty()))
					{
						logicalConditionSubject = (logicalConditionEntity->conditionSubjectEntity->back())->entity;
						foundConditionSubject = true;
					}
					if(!(logicalConditionEntity->conditionObjectEntity->empty()))
					{
						logicalConditionObject = (logicalConditionEntity->conditionObjectEntity->back())->entity;
						foundConditionObject = true;
					}
					if(foundConditionSubject && foundConditionObject)
					{
						bool simpleNonConjunctionLogicalConditionNegative = false;
						if(logicalConditionObject->negative)
						{
							simpleNonConjunctionLogicalConditionNegative = true;
						}

						//cout << "foundConditionSubject && foundConditionObject" << endl;
						//1. disable all classStructure formation based on condition object subset

						NLCcodeblock * currentCodeBlockInTreeAtBaseLevel = *currentCodeBlockInTree;
						
						bool passedConditionObject = false;
						if((logicalOperation == NLC_CONDITION_LOGICAL_OPERATIONS_IF) && (logicalConditionObject->isConcept || logicalConditionObject->isSubstanceConcept))
						{//eg If red dogs are pies, eat the cabbage
							//cout << "logicalConditionObject->isSubstanceConcept = " << logicalConditionObject->isSubstanceConcept << endl;
							#ifdef NLC_SUPPORT_CONDITION_LOGICAL_OPERATIONS_BASED_ON_CONCEPTS
							//isSubstanceConcept case not yet coded
							//logical operations on concepts are performed by NLC (code is not generated for them by NLC as they are not performed at runtime) - eg If red dogs are pies, eat the cabbage.	[as opposed to: "if the red dog is the/a pie, eat the cabbage"]
							//verify the truth of the if statement now (if the statement is false, disable all classStructure formation based on condition subject subset)
							if(logicalConditionObject->isConcept)
							{
								cout << "generateCodeBlocks() error: NLC_SUPPORT_CONDITION_LOGICAL_OPERATIONS_BASED_ON_CONCEPTS only handles substance concepts. GIA_CREATE_SUBSTANCE_CONCEPTS_FOR_ALL_SENTENCES_WITH_CONCEPTS must be enabled." << endl;
								cout << "logicalConditionObject = " << logicalConditionObject->entityName;
							}
							else if(logicalConditionObject->isSubstanceConcept)
							{
								cout << "logicalConditionObject->isSubstanceConcept" << endl;
								GIAentityNode * substanceConceptEntityCompare = logicalConditionObject;	//if statement comparison...
								GIAentityNode * substanceConceptEntityCompareConcept = (substanceConceptEntityCompare->entityNodeDefiningThisInstance->back())->entity;

								logicalConditionSubject->disabled = true;	//temporarily disable logicalConditionSubject to prevent it from being parsed
								if(searchForEquivalentSubnetToIfStatement(substanceConceptEntityCompareConcept, logicalConditionObject))
								{
									if(!simpleNonConjunctionLogicalConditionNegative)
									{
										passedConditionObject = true;
									}
								}
								logicalConditionSubject->disabled = false;
							}
							#endif
						}
						else if((logicalOperation == NLC_CONDITION_LOGICAL_OPERATIONS_IF) && (logicalConditionObject->isAction || logicalConditionObject->isActionConcept))
						{
							//eg The sun fights. If the sun fights, the dog is happy. / If the sun fights, eat the cabbage.

							//cout << "logicalConditionObject->isAction" << endl;
							#ifdef NLC_SUPPORT_CONDITION_LOGICAL_OPERATIONS_BASED_ON_ACTIONS
							//verify the truth of the if statement now
							//NO: get class and see if it has the relevant action (function) defined with the relevant action object
							//perform an exact trace of logicalConditionObject (actionEntityCompare) with every actionEntity that matches actionEntityCompare->entityName to verify that such a specific action already [ie sentence <= currentSentence] exists (actionEntityCompare)

							GIAentityNode * actionEntityCompare = logicalConditionObject;	//if statement comparison...
							GIAentityNode * actionEntityCompareConcept = (actionEntityCompare->entityNodeDefiningThisInstance->back())->entity;

							logicalConditionSubject->disabled = true;	//temporarily disable logicalConditionSubject to prevent it from being parsed
							if(searchForEquivalentSubnetToIfStatement(actionEntityCompareConcept, logicalConditionObject))
							{
								if(!simpleNonConjunctionLogicalConditionNegative)
								{
									passedConditionObject = true;
								}
								//cout << "passedConditionObject" << endl;
							}
							logicalConditionSubject->disabled = false;
							#endif
						}
						else
						{//eg If/While the sun is bright, the dog is happy. / If/While the sun is bright, eat the cabbage.	[OLD:if the red dog is the/a pie, eat the cabbage]
							
						#ifdef NLC_LOGICAL_CONDITIONS_SUPPORT_CONJUNCTIONS
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

							string whileLogicalConditionConjunctionBooleanName = generateWhileLogicalConditionConjunctionBooleanName(1);	//MUST CHANGE THIS TO logicalConditionLevel once indentation is being parsed by NLC preprocessor					
							if(logicalOperation == NLC_CONDITION_LOGICAL_OPERATIONS_WHILE)
							{
								*currentCodeBlockInTree = createCodeBlockDeclareNewBoolVar(*currentCodeBlockInTree, whileLogicalConditionConjunctionBooleanName, true);
								currentCodeBlockInTreeAtBaseLevel = *currentCodeBlockInTree;
								*currentCodeBlockInTree = createCodeBlockWhileHasBool(*currentCodeBlockInTree, whileLogicalConditionConjunctionBooleanName);
								*currentCodeBlockInTree = createCodeBlockSetBoolVar(*currentCodeBlockInTree, whileLogicalConditionConjunctionBooleanName, false);
							}

							NLClogicalConditionConjunction logicalConditionConjunctionArray[NLC_MAXIMUM_NUMBER_OF_CONJUNCTIONS_IN_SENTENCE];
							int logicalConditionConjunctionIndex = 0;	// try to start all variables seen by the user at 1 instead of 0: NOT POSSIBLE HERE AS USES ARRAY
							if(logicalOperation != NLC_CONDITION_LOGICAL_OPERATIONS_FOR)
							{
								for(int i=0; i<NLC_MAXIMUM_NUMBER_OF_CONJUNCTIONS_IN_SENTENCE; i++)
								{
									logicalConditionConjunctionArray[i].conjunctionType = INT_DEFAULT_VALUE;
									logicalConditionConjunctionArray[i].negative = false;
								}
								*currentCodeBlockInTree = createCodeBlockDeclareNewBoolArray(*currentCodeBlockInTree, NLC_LOGICAL_CONDITION_CONJUNCTION_BOOLEAN_VARIABLE_NAME, false);	
								
								//logicalConditionObject->NLCparsedForCodeBlocks = true;	//is this required?????? [NB only connections are being parsed...]
								if(logicalConditionObject->negative)
								{//added 1g6i
									logicalConditionConjunctionArray[logicalConditionConjunctionIndex].negative = true;	
								}
							}
							logicalConditionObject->NLClogicalConditionConjunctionIndex = logicalConditionConjunctionIndex;	//set initial logicalConditionConjunctionIndex value 

							//cout << "logicalConditionObject = " << logicalConditionObject->entityName << endl;
							addNewLogicalCondition(currentCodeBlockInTree, logicalConditionObject, sentenceIndex, logicalOperation, &logicalConditionConjunctionIndex, logicalConditionConjunctionArray, logicalConditionObject);

							if(logicalOperation != NLC_CONDITION_LOGICAL_OPERATIONS_FOR)
							{
								#ifdef NLC_DEBUG_LOGICAL_CONDITION_CONJUNCTIONS
								cout << "conj: 1" << endl;
								#endif
								int logicalConditionConjunctionIndexMax = logicalConditionConjunctionIndex;
								//error checking:
								for(int i=1; i<logicalConditionConjunctionIndexMax; i++)	//i=0 should not have a conjunction type assigned
								{
									if(logicalConditionConjunctionArray[i].conjunctionType == INT_DEFAULT_VALUE)
									{
										cout << "generateCodeBlocksPart2logicalConditions() error: missing conjunction type: " << i << endl;
									}
								}
								#ifdef NLC_DEBUG_LOGICAL_CONDITION_CONJUNCTIONS
								cout << "conj: 2" << endl;
								#endif
								if(logicalOperation == NLC_CONDITION_LOGICAL_OPERATIONS_IF)
								{
									currentCodeBlockInTreeAtBaseLevel = *currentCodeBlockInTree;
								}
								*currentCodeBlockInTree = createCodeBlockLogicalConditionConjunctionOfBools(*currentCodeBlockInTree, NLC_CONDITION_LOGICAL_OPERATIONS_IF, logicalConditionConjunctionArray, logicalConditionConjunctionIndexMax);
								if(logicalOperation == NLC_CONDITION_LOGICAL_OPERATIONS_WHILE)
								{
									*currentCodeBlockInTree = createCodeBlockSetBoolVar(*currentCodeBlockInTree, whileLogicalConditionConjunctionBooleanName, true);
								}	
								#ifdef NLC_DEBUG_LOGICAL_CONDITION_CONJUNCTIONS
								cout << "conj: 3" << endl;
								#endif
								
							}						
						#else
							//this code is suitable for for/while/if logical conditions without conjunctions:

							//code copied from [*^]
							//handle property logical operations; eg "If the sun is bright" in "If the sun is bright, the dog is happy"
							NLClogicalConditionConjunctionVariables logicalConditionConjunctionVariables;
							logicalConditionConjunctionVariables.logicalOperation = logicalOperation;
							logicalConditionConjunctionVariables.negative = simpleNonConjunctionLogicalConditionNegative;
								//NB this will set NLCparsedForCodeBlocks to true, so NLCparsedForlogicalConditionOperations can be set to false without causing any problems (ie generateCodeBlocksPart3actions/generateCodeBlocksPart4objectInitialisations will not reparse the if statement)	//CHECKTHIS; AndInitialiseParentIfNecessary component
							getParentAndGenerateContextBlocksAndInitialiseParentIfNecessary(currentCodeBlockInTree, logicalConditionObject, sentenceIndex, &logicalConditionConjunctionVariables, false, true);		//NB parseConditionParents is set false a) in accordance with original implementation [although the GIA specification supports such arrangements, in practice however they probably can't be generated as x will always be a condition subject not a condition object of y in "x is near the y"], and b) as a simple method to prevent logical conditions (eg if) and logical condition conjunctions (eg and) from being parsed
							tagAllEntitiesInSentenceSubsetAsPertainingToLogicalConditionOperation(logicalConditionObject, sentenceIndex, false);	//used to enable class definition printing of conditional statements
					
						#endif
							
							passedConditionObject = true;
						}

						if(passedConditionObject)
						{
							#ifdef NLC_DEBUG_LOGICAL_CONDITION_CONJUNCTIONS
							cout << "conj: 4" << endl;
							#endif
							//check if logicalConditionSubject is special "do" action with "this" action; if so ignore it and look for following indented sentences
							
							if(logicalConditionSubject->isConcept || logicalConditionSubject->isSubstanceConcept)
							{
								#ifdef NLC_SUPPORT_CONDITION_LOGICAL_OPERATIONS_BASED_ON_CONCEPTS
								if(logicalConditionSubject->isConcept)
								{
									cout << "generateCodeBlocks() error: NLC_SUPPORT_CONDITION_LOGICAL_OPERATIONS_BASED_ON_CONCEPTS only handles substance concepts. GIA_CREATE_SUBSTANCE_CONCEPTS_FOR_ALL_SENTENCES_WITH_CONCEPTS must be enabled." << endl;
									cout << "logicalConditionSubject = " << logicalConditionSubject->entityName;
								}
								else if(logicalConditionSubject->isSubstanceConcept)
								{
									tagAllEntitiesInSentenceSubsetAsPertainingToLogicalConditionOperation(logicalConditionSubject, sentenceIndex, false);
								}
								#endif
							}
							else if(logicalConditionSubject->isAction)
							{
								//eg If the sun is bright, eat the cabbage.
								tagAllEntitiesInSentenceSubsetAsPertainingToLogicalConditionOperation(logicalConditionSubject, sentenceIndex, false);	//used to enable class definition printing of conditional statements

								generateActionCodeBlocks(currentCodeBlockInTree, logicalConditionSubject, sentenceIndex, NLCfunctionName);
								*currentCodeBlockInTree = currentCodeBlockInTreeAtBaseLevel->next;
							}
							else
							{
								//eg If the sun is bright, the dog is happy.
								tagAllEntitiesInSentenceSubsetAsPertainingToLogicalConditionOperation(logicalConditionSubject, sentenceIndex, false);	//used to enable class definition printing of conditional statements

								#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
								generateCodeBlocksObjectInitialisationsForEntity(currentCodeBlockInTree, logicalConditionSubject, sentenceIndex);
								#else
								GIAentityNode * parentEntity = getParent(logicalConditionSubject, sentenceIndex, true);		//CHECKTHIS check parseConditionParents value here
								if(!generateParentInitialisationCodeBlock(currentCodeBlockInTree, parentEntity, sentenceIndex, false))
								{
									generateObjectInitialisationsBasedOnPropertiesAndConditions(parentEntity, currentCodeBlockInTree , sentenceIndex, "", "", false);
								}
								#endif
				
								*currentCodeBlockInTree = currentCodeBlockInTreeAtBaseLevel->next;
							}
							#ifdef NLC_DEBUG_LOGICAL_CONDITION_CONJUNCTIONS
							cout << "conj: 5" << endl;
							#endif
						}
					}
				}
			}
		}
	}
	return true;
}

#ifdef NLC_LOGICAL_CONDITIONS_SUPPORT_CONJUNCTIONS
void addNewLogicalCondition(NLCcodeblock ** currentCodeBlockInTree, GIAentityNode * currentLogicalConditionObject, int sentenceIndex, int logicalOperation, int * logicalConditionConjunctionIndex, NLClogicalConditionConjunction * logicalConditionConjunctionArray, GIAentityNode * previousLogicalConditionConjunction)
{
	NLCcodeblock * currentCodeBlockInTreeAtCurrentLevel1 = *currentCodeBlockInTree;
		
	#ifdef NLC_DEBUG_LOGICAL_CONDITION_CONJUNCTIONS
	cout << "conj: q1: currentLogicalConditionObject = " << currentLogicalConditionObject->entityName << endl;
	#endif
	
	if(logicalOperation == NLC_CONDITION_LOGICAL_OPERATIONS_FOR)
	{
		//set currentLogicalConditionObject to isDefiniteTemp, eg "chicken" in "For every/each chicken.." NB "chicken" in "For all chickens..." is parsed as definite by GIA fillGrammaticalArraysStanford() already
		currentLogicalConditionObject->grammaticalDefiniteTemp = true;
	}
	
	//handle property logical operations; eg "If the sun is bright" in "If the sun is bright, the dog is happy"
	NLClogicalConditionConjunctionVariables logicalConditionConjunctionVariables;
	logicalConditionConjunctionVariables.logicalOperation = logicalOperation;
	logicalConditionConjunctionVariables.logicalConditionConjunctionIndex = *logicalConditionConjunctionIndex;
	logicalConditionConjunctionVariables.primaryEntityInLogicalConditionConjunctionSubset = previousLogicalConditionConjunction;
		//NB this will set NLCparsedForCodeBlocks to true, so NLCparsedForlogicalConditionOperations can be set to false without causing any problems (ie generateCodeBlocksPart3actions/generateCodeBlocksPart4objectInitialisations will not reparse the if statement)	//CHECKTHIS; AndInitialiseParentIfNecessary component	

	if(checkSentenceIndexParsingCodeBlocks(currentLogicalConditionObject, sentenceIndex, false))
	{	
		getParentAndGenerateContextBlocksAndInitialiseParentIfNecessary(currentCodeBlockInTree, currentLogicalConditionObject, sentenceIndex, &logicalConditionConjunctionVariables, false, true);	//NB parseConditionParents is set false a) in accordance with original implementation [although the GIA specification supports such arrangements, in practice however they probably can't be generated as x will always be a condition subject not a condition object of y in "x is near the y"], and b) as a simple method to prevent logical conditions (eg if) and logical condition conjunctions (eg and) from being parsed
		
		if(logicalOperation != NLC_CONDITION_LOGICAL_OPERATIONS_FOR)
		{
			string logicalConditionConjunctionBooleanName = generateLogicalConditionConjunctionBooleanName(*logicalConditionConjunctionIndex);
			*currentCodeBlockInTree = createCodeBlockSetBoolVar(*currentCodeBlockInTree, logicalConditionConjunctionBooleanName, true);
			currentCodeBlockInTreeAtCurrentLevel1 = currentCodeBlockInTreeAtCurrentLevel1->next;
			*currentCodeBlockInTree = currentCodeBlockInTreeAtCurrentLevel1;
		}
		*logicalConditionConjunctionIndex = *logicalConditionConjunctionIndex + 1;
		#ifdef NLC_DEBUG_LOGICAL_CONDITION_CONJUNCTIONS
		cout << "A: *logicalConditionConjunctionIndex = " << *logicalConditionConjunctionIndex << endl;
		#endif
	}
	else
	{
		*currentCodeBlockInTree = currentCodeBlockInTreeAtCurrentLevel1;
	}

	tagAllEntitiesInSentenceSubsetAsPertainingToLogicalConditionOperation(currentLogicalConditionObject, sentenceIndex, false);	//used to enable class definition printing of conditional statements
	
	#ifdef NLC_DEBUG_LOGICAL_CONDITION_CONJUNCTIONS
	cout << "conj: q2" << endl;
	#endif
	
	if(logicalConditionConjunctionVariables.foundLogicalConditionConjunction != NULL)
	{	
		#ifdef NLC_DEBUG_LOGICAL_CONDITION_CONJUNCTIONS	
		cout << "logicalConditionConjunctionVariables.foundLogicalConditionConjunction defined: " << logicalConditionConjunctionVariables.foundLogicalConditionConjunction->entityName << endl;
		cout << "logicalConditionConjunctionVariables.foundLogicalConditionConjunction->subject: " << (logicalConditionConjunctionVariables.foundLogicalConditionConjunction->conditionObjectEntity->back())->entity->entityName << endl;
		#endif
		checkConditionForLogicalCondition(currentCodeBlockInTree, logicalConditionConjunctionVariables.foundLogicalConditionConjunction, sentenceIndex, logicalOperation, logicalConditionConjunctionIndex, logicalConditionConjunctionArray);
	}
		
	
}

void checkConditionForLogicalCondition(NLCcodeblock ** currentCodeBlockInTree, GIAentityNode * conditionEntity, int sentenceIndex, int logicalOperation, int * logicalConditionConjunctionIndex, NLClogicalConditionConjunction * logicalConditionConjunctionArray)
{
	int conjunctionType = INT_DEFAULT_VALUE;
	bool conjunctionConditionFound = textInTextArray(conditionEntity->entityName, entityCoordinatingConjunctionArray, ENTITY_COORDINATINGCONJUNCTION_ARRAY_NUMBER_OF_TYPES, &conjunctionType);
	if(conjunctionConditionFound)
	{
		if(!(conditionEntity->NLCconjunctionCondition))
		{
			cout << "conditionEntity = " << conditionEntity->entityName << endl;
			conditionEntity->NLCconjunctionCondition = true;
			GIAentityNode * logicalConditionConjunctionObjectEntity = (conditionEntity->conditionObjectEntity->back())->entity;
			GIAentityNode * logicalConditionConjunctionSubjectEntity = (conditionEntity->conditionSubjectEntity->back())->entity;

			if(checkSentenceIndexParsingCodeBlocks(logicalConditionConjunctionObjectEntity, sentenceIndex, false))
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
					cout << "logicalConditionConjunctionSubjectEntity = " << logicalConditionConjunctionSubjectEntity->entityName << endl;
					cout << "error: logicalConditionConjunctionSubjectEntity->NLClogicalConditionConjunctionIndex == INT_DEFAULT_VALUE" << endl;
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

					if(logicalConditionConjunctionObjectEntity->isCondition)
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
				cout << "addNewLogicalCondition() error: logicalConditionConjunctionObjectEntity has bad sentence index" << endl;
			}
		}
		else
		{
			cout << "addNewLogicalCondition() error: (conditionEntity->NLCconjunctionCondition)" << endl;
		}
	}
}

#endif

								
bool searchForEquivalentSubnetToIfStatement(GIAentityNode * entityCompareConcept, GIAentityNode * entity)
{
	bool result = false;

	//code copied from [*****^] (identifyReferenceSetsSpecificConceptsAndLinkWithSubstanceConcepts() in GIAtranslatorDefineReferencing.cpp)

	int referenceSetID = NLC_SUPPORT_CONDITION_LOGICAL_OPERATIONS_BASED_ON_ACTIONS_DUMMY_REFERENCE_SET_ID;

	bool traceModeIsQuery = false;
	GIAreferenceTraceParameters referenceTraceParameters;
	referenceTraceParameters.referenceSetID = referenceSetID;
	referenceTraceParameters.linkSpecificConceptsAndActions = true;

	for(vector<GIAentityConnection*>::iterator entityIter = entityCompareConcept->associatedInstanceNodeList->begin(); entityIter != entityCompareConcept->associatedInstanceNodeList->end(); entityIter++)
	{
		GIAentityNode * entityCompare = (*entityIter)->entity;
		#ifdef GIA_DREAMMODE_REFERENCING_DEBUG
		cout << "\t identifyReferenceSetsSpecificConcepts: " << entityCompare->entityName << endl;
		#endif

		if(!(entityCompare->disabled))
		{
			if(entity != entityCompare)
			{
				GIAqueryTraceParameters queryTraceParameters;		//not used

				//cout << "entityCompare->entityName = " << entityCompare->entityName << endl;
				//cout << "entity->entityName = " << entity->entityName << endl;

				int numberOfMatchedNodesTemp = 0;
				int numberOfMatchedNodesRequiredSynonymnDetectionTemp = 0;
				bool exactMatch = testReferencedEntityNodeForExactNameMatch2(entity, entityCompare, &numberOfMatchedNodesTemp, false, &numberOfMatchedNodesRequiredSynonymnDetectionTemp, traceModeIsQuery, &queryTraceParameters, &referenceTraceParameters);

				if(exactMatch)
				{
					if(numberOfMatchedNodesTemp > 0)
					{
						//cout << "exactMatch: numberOfMatchedNodesTemp = " << numberOfMatchedNodesTemp << endl;
						result = true;
					}
				}

				//now reset the matched nodes as unpassed (required such that they are retracable using a the different path)
				int irrelevant;
				string printEntityNodeString = "";
				bool traceInstantiations = GIA_QUERY_TRACE_CONCEPT_NODES_DEFINING_INSTANTIATIONS_VALUE;
				traceEntityNode(entityCompare, GIA_QUERY_TRACE_ENTITY_NODES_FUNCTION_RESET_TESTEDFORQUERYCOMPARISONTEMP, &irrelevant, &printEntityNodeString, false, NULL, traceInstantiations);
				traceEntityNode(entity, GIA_QUERY_TRACE_ENTITY_NODES_FUNCTION_RESET_TESTEDFORQUERYCOMPARISONTEMP, &irrelevant, &printEntityNodeString, false, NULL, traceInstantiations);
			}
		}
	}
	return result;
}

void tagAllEntitiesInSentenceSubsetAsPertainingToLogicalConditionOperation(GIAentityNode * entity, int sentenceIndex, bool tagOrUntag)
{
	for(int i=0; i<GIA_ENTITY_NUMBER_OF_VECTOR_CONNECTION_TYPES; i++)
	{
		if(i != GIA_ENTITY_VECTOR_CONNECTION_TYPE_NODE_DEFINING_INSTANCE)
		{
			for(vector<GIAentityConnection*>::iterator connectionIter = entity->entityVectorConnectionsArray[i].begin(); connectionIter != entity->entityVectorConnectionsArray[i].end(); connectionIter++)
			{
				GIAentityConnection * connection = (*connectionIter);
				GIAentityNode * connectedEntity = connection->entity;
				if((tagOrUntag && !(connectedEntity->NLCparsedForlogicalConditionOperations)) || (!tagOrUntag && (connectedEntity->NLCparsedForlogicalConditionOperations)))
				{
					if(!(connectedEntity->NLClogicalConditionOperation))
					{//don't cross the "if" boundary
						if(checkSentenceIndexParsingCodeBlocks(connectedEntity, sentenceIndex, false))
						{
							if(connectedEntity->isConcept)
							{
								cout << "tagAllEntitiesInSentenceSubsetAsPertainingToLogicalConditionOperation() error: NLC_SUPPORT_CONDITION_LOGICAL_OPERATIONS_BASED_ON_CONCEPTS only handles substance concepts. GIA_CREATE_SUBSTANCE_CONCEPTS_FOR_ALL_SENTENCES_WITH_CONCEPTS must be enabled." << endl;
								cout << "connectedEntity = " << connectedEntity->entityName;
							}
							else
							{
								#ifdef NLC_SUPPORT_CONDITION_LOGICAL_OPERATIONS_BASED_ON_ACTIONS
								connectedEntity->referenceSetID = NLC_SUPPORT_CONDITION_LOGICAL_OPERATIONS_BASED_ON_ACTIONS_DUMMY_REFERENCE_SET_ID;
								#endif
								if(tagOrUntag)
								{
									#ifdef NLC_DEBUG5
									cout << "tagged: " << connectedEntity->entityName << endl;
									#endif
									connection->NLCparsedForlogicalConditionOperations = true;
									connectedEntity->NLCparsedForlogicalConditionOperations = true;
								}
								else
								{
									#ifdef NLC_DEBUG5
									cout << "untagged: " << connectedEntity->entityName << endl;
									#endif
									connection->NLCparsedForlogicalConditionOperations = false;
									connectedEntity->NLCparsedForlogicalConditionOperations = false;
								}
								tagAllEntitiesInSentenceSubsetAsPertainingToLogicalConditionOperation(connectedEntity, sentenceIndex, tagOrUntag);
							}
						}
					}
				}
			}
		}
	}
}
#endif

bool generateCodeBlocksPart3actions(NLCcodeblock ** currentCodeBlockInTree, vector<GIAentityNode*> * entityNodesActiveListComplete, int sentenceIndex, string NLCfunctionName)
{
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode * actionEntity = (*entityIter);
		if(actionEntity->isAction)
		{
			NLCcodeblock * firstCodeBlockInSentence = *currentCodeBlockInTree;

			if(!(actionEntity->isActionConcept))
			{
				//cout << "actionEntity->isAction = " << actionEntity->isAction << endl;
				//cout << "actionEntity->hasAssociatedInstance = " << actionEntity->hasAssociatedInstance << endl;

				if(checkSentenceIndexParsingCodeBlocks(actionEntity, sentenceIndex, true))
				{
					generateActionCodeBlocks(currentCodeBlockInTree, actionEntity, sentenceIndex, NLCfunctionName);
				}
			}

			*currentCodeBlockInTree = firstCodeBlockInSentence;
			while((*currentCodeBlockInTree)->next != NULL)
			{
				*currentCodeBlockInTree = (*currentCodeBlockInTree)->next;
			}
		}
	}
	return true;
}

void generateActionCodeBlocks(NLCcodeblock ** currentCodeBlockInTree, GIAentityNode * actionEntity, int sentenceIndex, string NLCfunctionName)
{
	#ifdef NLC_SUPPORT_CONDITION_LOGICAL_OPERATIONS
	if(!(actionEntity->NLCparsedForlogicalConditionOperations))
	{
	#endif
		#ifdef NLC_DEBUG
		cout << "actionEntity->entityName = " << actionEntity->entityName << endl;
		#endif
		//cout << "sentenceIndexC = " << sentenceIndex << endl;

		bool actionHasObject = false;
		GIAentityNode * objectEntity = NULL;
		if(!(actionEntity->actionObjectEntity->empty()))
		{
			actionHasObject = true;
			objectEntity = (actionEntity->actionObjectEntity->back())->entity;
		}

		bool actionHasSubject = false;
		GIAentityNode * subjectEntity = NULL;
		if(!(actionEntity->actionSubjectEntity->empty()))
		{
			actionHasSubject = true;
			subjectEntity = (actionEntity->actionSubjectEntity->back())->entity;
		}

		NLCcodeblock * functionExecuteCodeBlockInTree = NULL;

		NLCitem * functionItem = NULL;
		if(actionHasObject || actionHasSubject)
		{
			//[q**^]
			functionItem = new NLCitem(actionEntity, NLC_ITEM_TYPE_FUNCTION);

			#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS
			initialiseFunctionArguments(currentCodeBlockInTree, actionEntity, sentenceIndex);
			//firstCodeBlockInSentence = *currentCodeBlockInTree;		//removed 1f1b... [CHECKTHIS]
			#endif
			
			#ifndef NLC_DEFINE_LOCAL_VARIABLES_FOR_ALL_INDEFINATE_ENTITIES
			//this is where original getParentAndGenerateContextBlocksAndInitialiseParentIfNecessary code whent (for both subjectEntity and objectEntity)
			getParentAndGenerateParentInitialisationCodeBlock(currentCodeBlockInTree, subjectEntity, sentenceIndex, true, false);	//parseConditionParents was previously set false in original implementation [although the GIA specification supports such arrangements, in practice however they probably can't be generated as x will always be a condition subject not a condition object of y in "x is near the y"]
			getParentAndGenerateParentInitialisationCodeBlock(currentCodeBlockInTree, objectEntity, sentenceIndex, true, false);	//parseConditionParents was previously set false in original implementation [although the GIA specification supports such arrangements, in practice however they probably can't be generated as x will always be a condition subject not a condition object of y in "x is near the y"]
			#endif
	
		}


		if(actionHasObject)
		{
			NLClogicalConditionConjunctionVariables logicalConditionConjunctionVariables;	//not used
			getParentAndGenerateContextBlocksAndInitialiseParentIfNecessary(currentCodeBlockInTree, objectEntity, sentenceIndex, &logicalConditionConjunctionVariables, true, false);	//parseConditionParents was previously set false in original implementation [although the GIA specification supports such arrangements, in practice however they probably can't be generated as x will always be a condition subject not a condition object of y in "x is near the y"]
			
			if(actionHasSubject)
			{
				NLClogicalConditionConjunctionVariables logicalConditionConjunctionVariables;	//not used
				getParentAndGenerateContextBlocksAndInitialiseParentIfNecessary(currentCodeBlockInTree, subjectEntity, sentenceIndex, &logicalConditionConjunctionVariables, true, false);	//parseConditionParents was previously set false in original implementation [although the GIA specification supports such arrangements, in practice however they probably can't be generated as x will always be a condition subject not a condition object of y in "x is near the y"]
				
				functionItem->context.push_back(generateInstanceName(subjectEntity));

				#ifdef NLC_NOT_NECESSARY
				//required just for implictlyDeclaredFunctionList...;
				NLCitem * functionItemFullContextForRecordOnly = new NLCitem(actionEntity, NLC_ITEM_TYPE_FUNCTION);
				getEntityContext(subjectEntity, &(functionItemFullContextForRecordOnly->context), true, sentenceIndex, true);
				implictlyDeclaredFunctionList.push_back(functionItemFullContextForRecordOnly);
				#endif

				//subjectEntity->parsedForNLCcodeBlocksActionRound = true;
			}
			#ifdef NLC_NOT_NECESSARY
			else
			{
				implictlyDeclaredFunctionListTopLevel.push_back(functionItem);
			}
			#endif

			functionExecuteCodeBlockInTree = *currentCodeBlockInTree;
			NLCitem *objectItem = new NLCitem(objectEntity, NLC_ITEM_TYPE_FUNCTION_OBJECT);
			*currentCodeBlockInTree = createCodeBlockExecute(*currentCodeBlockInTree, functionItem, objectItem);

			actionEntity->NLCparsedForCodeBlocks = true;
			//actionEntity->parsedForNLCcodeBlocksActionRound = true;
			//objectEntity->parsedForNLCcodeBlocksActionRound = true;
		}
		else if(actionHasSubject)
		{
			//[**^]
			NLClogicalConditionConjunctionVariables logicalConditionConjunctionVariables;
			getParentAndGenerateContextBlocksAndInitialiseParentIfNecessary(currentCodeBlockInTree, subjectEntity, sentenceIndex, &logicalConditionConjunctionVariables, true, false);	//parseConditionParents was previously set false in original implementation [although the GIA specification supports such arrangements, in practice however they probably can't be generated as x will always be a condition subject not a condition object of y in "x is near the y"]
				
			//cout << "subjectRequiredTempVar" << endl;
			functionItem->context.push_back(generateInstanceName(subjectEntity));

			functionExecuteCodeBlockInTree = *currentCodeBlockInTree;
			*currentCodeBlockInTree = createCodeBlockExecute(*currentCodeBlockInTree, functionItem);

			actionEntity->NLCparsedForCodeBlocks = true;
			//actionEntity->parsedForNLCcodeBlocksActionRound = true;
			//subjectEntity->parsedForNLCcodeBlocksActionRound = true;
		}

		#ifdef NLC_INTERPRET_ACTION_PROPERTIES_AND_CONDITIONS_AS_FUNCTION_ARGUMENTS
		if(actionHasObject || actionHasSubject)
		{
			#ifndef NLC_SUPPORT_INPUT_FILE_LISTS
			generateFunctionPropertyConditionArgumentsWithActionConceptInheritance(actionEntity, &(functionExecuteCodeBlockInTree->parameters));	//#ifdef NLC_SUPPORT_INPUT_FILE_LISTS use class definition parameters instead
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

		/*
		findContextOfObject(objectEntity)

		#ifdef GIA_SEMANTIC_NET_DO_NOT_WRITE_DISABLED_ENTITY_NODES
		if(!(currentEntity->disabled))
		{
		#endif

		#ifdef GIA_SEMANTIC_NET_DO_NOT_WRITE_DISABLED_ENTITY_NODES
		}
		#endif
		*/
	#ifdef NLC_SUPPORT_CONDITION_LOGICAL_OPERATIONS
	}
	#endif
}

#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS
void initialiseFunctionArguments(NLCcodeblock ** currentCodeBlockInTree, GIAentityNode * actionEntity, int sentenceIndex)
{
	//cout << "NLC_CODEBLOCK_TYPE_DECLARE_NEW_VARIABLE" << endl;
	actionEntity->NLCisSingularArgument = true;	//added 1e2c

	//declare an "abstract" variable for the action (that will be filled with the its properties and conditions) and passed as an argument to the function; eg "fast" of "run fast"
	//cout << "functionItem->instanceName = " << functionItem->instanceName << endl;
	//cout << "functionItem->className = " << functionItem->className << endl;
	*currentCodeBlockInTree = createCodeBlocksCreateNewLocalListVariable(*currentCodeBlockInTree, actionEntity);	//changed 1e10b

	generateObjectInitialisationsBasedOnPropertiesAndConditions(actionEntity, currentCodeBlockInTree, sentenceIndex, "", "", false);
	generateObjectInitialisationsBasedOnSubstanceConcepts(actionEntity, currentCodeBlockInTree, sentenceIndex);
}
#endif





bool generateCodeBlocksPart4objectInitialisations(NLCcodeblock ** currentCodeBlockInTree, vector<GIAentityNode*> * entityNodesActiveListComplete, int sentenceIndex, string NLCfunctionName)
{
	bool result = true;
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode * entity = *entityIter;
		if(checkSentenceIndexParsingCodeBlocks(entity, sentenceIndex, false))
		{
			if(!(entity->isConcept) && !(entity->isAction) && !(entity->isSubstanceConcept) && !(entity->isCondition) && !(entity->isActionConcept))
			{
				#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
				generateCodeBlocksObjectInitialisationsForEntity(currentCodeBlockInTree, entity, sentenceIndex);
				#else
				GIAentityNode * parentEntity = getParent(entity, sentenceIndex, true);
				if(!generateParentInitialisationCodeBlock(currentCodeBlockInTree, parentEntity , sentenceIndex, false))
				{
					generateObjectInitialisationsBasedOnPropertiesAndConditions(parentEntity, currentCodeBlockInTree , sentenceIndex, "", "", false);
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





