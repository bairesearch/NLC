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
 * Project Version: 1g8h 11-July-2014
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/



#include <ctime>
#include <cstdlib>	//for random number generation
#include <cmath>

#include "NLCtranslatorCodeBlocks.h"
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

		declareLocalPropertyListsForAllNonSpecificIndefiniteEntities(&currentCodeBlockInTree, entityNodesActiveListComplete, sentenceIndex, NLCfunctionName);	//added 1g8a 11-July-2014
		
		#ifdef NLC_SUPPORT_CONDITION_LOGICAL_OPERATIONS
		//Part 0 - added 1f1a;
		#ifdef NLC_DEBUG
		cout << "generateCodeBlocksPart0:" << endl;
		#endif
		if(!generateCodeBlocksPart0(&currentCodeBlockInTree, entityNodesActiveListComplete, sentenceIndex, NLCfunctionName))
		{
			result = false;
		}
		#endif

		//Part 1;
		#ifdef NLC_DEBUG
		cout << "generateCodeBlocksPart1:" << endl;
		#endif
		if(!generateCodeBlocksPart1(&currentCodeBlockInTree, entityNodesActiveListComplete, sentenceIndex, NLCfunctionName))
		{
			result = false;
		}

		//Part 2: generate object initialisations (eg Tom has a boat) [without actions]
		#ifdef NLC_DEBUG
		cout << "generateCodeBlocksPart2:" << endl;
		#endif
		if(!generateCodeBlocksPart2(&currentCodeBlockInTree, entityNodesActiveListComplete, sentenceIndex, NLCfunctionName))
		{
			result = false;
		}
	}
	return result;
}

bool declareLocalPropertyListsForAllNonSpecificIndefiniteEntities(NLCcodeblock ** currentCodeBlockInTree, vector<GIAentityNode*> * entityNodesActiveListComplete, int sentenceIndex, string NLCfunctionName)
{
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode * entity = (*entityIter);
		if(!(entity->isConcept) && !(entity->isAction) && !(entity->isSubstanceQuality) && !(entity->isSubstanceConcept) && !(entity->isCondition))
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
							*currentCodeBlockInTree = createCodeBlocksDeclareNewLocalListVariable(*currentCodeBlockInTree, entity);
							#ifdef NLC_DEBUG
							cout << "declareLocalPropertyListsForAllNonSpecificIndefiniteEntities(): createCodeBlocksDeclareNewLocalListVariable for " << entity->entityName << endl;
							#endif
							entity->NLClocalListVariableHasBeenDeclared = true;
						}
						/*
						bool foundProperty = false;
						bool foundCondition = false;
						if(!(entity->propertyNodeList->empty()))
						{
							foundProperty = true;
						}
						if(!(entity->conditionNodeList->empty()))
						{
							foundCondition = true;
						}
						if(!foundProperty && !foundCondition)
						{
							*currentCodeBlockInTree = createCodeBlocksDeclareNewLocalListVariable(*currentCodeBlockInTree, entity);
						}
						*/
					}
				}
			}
		}
	}
}

#ifdef NLC_SUPPORT_CONDITION_LOGICAL_OPERATIONS
bool generateCodeBlocksPart0(NLCcodeblock ** currentCodeBlockInTree, vector<GIAentityNode*> * entityNodesActiveListComplete, int sentenceIndex, string NLCfunctionName)
{
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode * logicalConditionEntity = (*entityIter);
		if(logicalConditionEntity->isCondition)
		{
			if(checkSentenceIndexParsingCodeBlocks(logicalConditionEntity, sentenceIndex, true))	//could be set to false instead
			{
				bool foundConditionLogicalOperation = false;
				int logicalOperation;
				for(int i=1; i<NLC_CONDITION_LOGICAL_OPERATIONS_NUMBER_OF_TYPES; i++)		//i=1 to ignore "for"
				{
					if((i == NLC_CONDITION_LOGICAL_OPERATIONS_IF) || (i == NLC_CONDITION_LOGICAL_OPERATIONS_WHILE))
					{//only "if" statements are currently supported by NLC
						if(logicalConditionEntity->entityName == conditionLogicalOperationsArray[i])
						{
							logicalOperation = i;
							foundConditionLogicalOperation = true;
						}
					}
				}
				if(foundConditionLogicalOperation)
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
							if(logicalOperation != NLC_CONDITION_LOGICAL_OPERATIONS_FOR)
							{
								/*
								eg; while the red dog near the park has an apple, and the tea tree is blue
								bool whileLogicalCondition = true;
								while(whileLogicalCondition)	//where && is dynamic (it could be ||)
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
									if(logicalCondition[1] && logicalCondition[2])
									{
										whileLogicalCondition = true;
										the tea tree is blue
									}
								}
								*/	
										
								string whileLogicalConditionConjunctionBooleanName = generateWhileLogicalConditionConjunctionBooleanName(1);	//MUST CHANGE THIS TO logicalConditionLevel once indentation is being parsed by NLC preprocessor					
								if(logicalOperation == NLC_CONDITION_LOGICAL_OPERATIONS_WHILE)
								{
									*currentCodeBlockInTree = createCodeBlockDeclareNewBoolVar(*currentCodeBlockInTree, whileLogicalConditionConjunctionBooleanName, true);
									*currentCodeBlockInTree = createCodeBlockWhileHasBool(*currentCodeBlockInTree, whileLogicalConditionConjunctionBooleanName);
									*currentCodeBlockInTree = createCodeBlockSetBoolVar(*currentCodeBlockInTree, whileLogicalConditionConjunctionBooleanName, false);
								}
								
								NLClogicalConditionConjunction logicalConditionConjunctionArray[NLC_MAXIMUM_NUMBER_OF_CONJUNCTIONS_IN_SENTENCE];
								for(int i=0; i<NLC_MAXIMUM_NUMBER_OF_CONJUNCTIONS_IN_SENTENCE; i++)
								{
									logicalConditionConjunctionArray[i].conjunctionType = INT_DEFAULT_VALUE;
									logicalConditionConjunctionArray[i].negative = false;
								}
								*currentCodeBlockInTree = createCodeBlockDeclareNewBoolArray(*currentCodeBlockInTree, NLC_LOGICAL_CONDITION_CONJUNCTION_BOOLEAN_VARIABLE_NAME, false);	

								int logicalConditionConjunctionIndex = 0;	// try to start all variables seen by the user at 1 instead of 0: NOT POSSIBLE HERE AS USES ARRAY
								logicalConditionObject->NLClogicalConditionConjunctionIndex = logicalConditionConjunctionIndex;	//set initial logicalConditionConjunctionIndex value 
								//logicalConditionObject->parsedForNLCcodeBlocks = true;	//is this required?????? [NB only connections are being parsed...]
								if(logicalConditionObject->negative)
								{//added 1g6i
									logicalConditionConjunctionArray[logicalConditionConjunctionIndex].negative = true;	
								}
								//cout << "logicalConditionObject = " << logicalConditionObject->entityName << endl;
								addNewLogicalCondition(currentCodeBlockInTree, logicalConditionObject, sentenceIndex, logicalOperation, &logicalConditionConjunctionIndex, logicalConditionConjunctionArray, logicalConditionObject);
							
								#ifdef NLC_DEBUG_LOGICAL_CONDITION_CONJUNCTIONS
								cout << "conj: 1" << endl;
								#endif
								int logicalConditionConjunctionIndexMax = logicalConditionConjunctionIndex;
								//error checking:
								for(int i=1; i<logicalConditionConjunctionIndexMax; i++)	//i=0 should not have a conjunction type assigned
								{
									if(logicalConditionConjunctionArray[i].conjunctionType == INT_DEFAULT_VALUE)
									{
										cout << "generateCodeBlocksPart0() error: missing conjunction type: " << i << endl;
									}
								}
								#ifdef NLC_DEBUG_LOGICAL_CONDITION_CONJUNCTIONS
								cout << "conj: 2" << endl;
								#endif
								*currentCodeBlockInTree = createCodeBlockLogicalConditionConjunctionOfBools(*currentCodeBlockInTree, NLC_CONDITION_LOGICAL_OPERATIONS_IF, logicalConditionConjunctionArray, logicalConditionConjunctionIndexMax);
								if(logicalOperation == NLC_CONDITION_LOGICAL_OPERATIONS_WHILE)
								{
									*currentCodeBlockInTree = createCodeBlockSetBoolVar(*currentCodeBlockInTree, whileLogicalConditionConjunctionBooleanName, true);
								}	
								#ifdef NLC_DEBUG_LOGICAL_CONDITION_CONJUNCTIONS
								cout << "conj: 3" << endl;
								#endif							
							}
							else
							{//this code is suitable for NLC_CONDITION_LOGICAL_OPERATIONS_FOR
							#endif
								//code copied from [*^]
								//handle property logical operations; eg "If the sun is bright" in "If the sun is bright, the dog is happy"
								bool contextFound = false;
								NLClogicalConditionConjunctionVariables logicalConditionConjunctionVariables;
								logicalConditionConjunctionVariables.logicalOperation = logicalOperation;
								logicalConditionConjunctionVariables.negative = simpleNonConjunctionLogicalConditionNegative;
								generateContextBlocksAndInitialiseParentIfNecessary(currentCodeBlockInTree, logicalConditionObject, sentenceIndex, &contextFound, &logicalConditionConjunctionVariables);	//NB this will set parsedForNLCcodeBlocks to true, so NLCconditionLogicalOperations can be set to false without causing any problems (ie generateCodeBlocksPart1/generateCodeBlocksPart2 will not reparse the if statement)	//CHECKTHIS; AndInitialiseParentIfNecessary component
								tagAllEntitiesInSentenceSubsetAsPertainingToConditionLogicalOperation(logicalConditionObject, sentenceIndex, false);	//used to enable class definition printing of conditional statements
								
								#ifndef NLC_PARSE_CHILD_PROPERTIES_AND_CONDITIONS_OF_CONTEXT_PARENT
								//handle condition logical operations; eg "If the basket is near the house" in "If the basket is near the house, the dog is happy." //added GIA 1g3a
								*currentCodeBlockInTree = generateConditionBlocks(*currentCodeBlockInTree, logicalConditionObject, sentenceIndex, &logicalConditionConjunctionVariables);	
								#endif
							#ifdef NLC_LOGICAL_CONDITIONS_SUPPORT_CONJUNCTIONS
							}
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
									tagAllEntitiesInSentenceSubsetAsPertainingToConditionLogicalOperation(logicalConditionSubject, sentenceIndex, false);
								}
								#endif
							}
							else if(logicalConditionSubject->isAction)
							{
								//eg If the sun is bright, eat the cabbage.
								tagAllEntitiesInSentenceSubsetAsPertainingToConditionLogicalOperation(logicalConditionSubject, sentenceIndex, false);	//used to enable class definition printing of conditional statements

								generateActionCodeBlocks(currentCodeBlockInTree, logicalConditionSubject, sentenceIndex, NLCfunctionName);
							}
							else
							{
								//eg If the sun is bright, the dog is happy.
								tagAllEntitiesInSentenceSubsetAsPertainingToConditionLogicalOperation(logicalConditionSubject, sentenceIndex, false);	//used to enable class definition printing of conditional statements

								generateInitialisationCodeBlock(currentCodeBlockInTree, logicalConditionSubject, sentenceIndex, NLCfunctionName);
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
	
	//code copied from [*^]
	
	#ifdef NLC_DEBUG_LOGICAL_CONDITION_CONJUNCTIONS
	cout << "conj: q1" << endl;
	#endif
	
	//handle property logical operations; eg "If the sun is bright" in "If the sun is bright, the dog is happy"
	bool contextFound = false;
	NLClogicalConditionConjunctionVariables logicalConditionConjunctionVariables;
	logicalConditionConjunctionVariables.logicalOperation = logicalOperation;
	logicalConditionConjunctionVariables.logicalConditionConjunctionIndex = *logicalConditionConjunctionIndex;
	logicalConditionConjunctionVariables.primaryEntityInLogicalConditionConjunctionSubset = previousLogicalConditionConjunction;
	if(generateContextBlocksAndInitialiseParentIfNecessary(currentCodeBlockInTree, currentLogicalConditionObject, sentenceIndex, &contextFound, &logicalConditionConjunctionVariables))	//NB this will set parsedForNLCcodeBlocks to true, so NLCconditionLogicalOperations can be set to false without causing any problems (ie generateCodeBlocksPart1/generateCodeBlocksPart2 will not reparse the if statement)	//CHECKTHIS; AndInitialiseParentIfNecessary component
	{
	#ifndef NLC_PARSE_CHILD_PROPERTIES_AND_CONDITIONS_OF_CONTEXT_PARENT
	}
	if(contextFound)
	{
	#endif
		string logicalConditionConjunctionBooleanName = generateLogicalConditionConjunctionBooleanName(*logicalConditionConjunctionIndex);
		*currentCodeBlockInTree = createCodeBlockSetBoolVar(*currentCodeBlockInTree, logicalConditionConjunctionBooleanName, true);
		*logicalConditionConjunctionIndex = *logicalConditionConjunctionIndex + 1;
		#ifdef NLC_DEBUG_LOGICAL_CONDITION_CONJUNCTIONS
		cout << "A: *logicalConditionConjunctionIndex = " << *logicalConditionConjunctionIndex << endl;
		#endif
		currentCodeBlockInTreeAtCurrentLevel1 = currentCodeBlockInTreeAtCurrentLevel1->next;
	}

	tagAllEntitiesInSentenceSubsetAsPertainingToConditionLogicalOperation(currentLogicalConditionObject, sentenceIndex, false);	//used to enable class definition printing of conditional statements
	
	#ifdef NLC_DEBUG_LOGICAL_CONDITION_CONJUNCTIONS
	cout << "conj: q2" << endl;
	#endif
	
#ifdef NLC_PARSE_CHILD_PROPERTIES_AND_CONDITIONS_OF_CONTEXT_PARENT
	*currentCodeBlockInTree = currentCodeBlockInTreeAtCurrentLevel1;	
	if(logicalConditionConjunctionVariables.foundLogicalConditionConjunction != NULL)
	{	
		#ifdef NLC_DEBUG_LOGICAL_CONDITION_CONJUNCTIONS	
		cout << "logicalConditionConjunctionVariables.foundLogicalConditionConjunction defined: " << logicalConditionConjunctionVariables.foundLogicalConditionConjunction->entityName << endl;
		cout << "logicalConditionConjunctionVariables.foundLogicalConditionConjunction->subject: " << (logicalConditionConjunctionVariables.foundLogicalConditionConjunction->conditionObjectEntity->back())->entity->entityName << endl;
		#endif
		checkConditionForLogicalCondition(currentCodeBlockInTree, logicalConditionConjunctionVariables.foundLogicalConditionConjunction, sentenceIndex, logicalOperation, logicalConditionConjunctionIndex, logicalConditionConjunctionArray);
	}
#else	
	//handle condition logical operations; eg "If the basket is near the house" in "If the basket is near the house, the dog is happy." //added GIA 1g3a
	//if object near a red car / if object has a red car (if object has a car which is red)
	//if(item->has(property) && item->has(property1) etc..){

	NLCcodeblock * currentCodeBlockInTreeAtCurrentLevel2 = currentCodeBlockInTreeAtCurrentLevel1;
	NLCitem * conditionObjectItem1 = new NLCitem(currentLogicalConditionObject, NLC_ITEM_TYPE_TEMPVAR);	//not used
	if(createCodeBlockForGivenProperties(currentCodeBlockInTree, conditionObjectItem1, currentLogicalConditionObject, sentenceIndex, &logicalConditionConjunctionVariables))
	{
		string logicalConditionConjunctionBooleanName = generateLogicalConditionConjunctionBooleanName(*logicalConditionConjunctionIndex);
		*currentCodeBlockInTree = createCodeBlockSetBoolVar(*currentCodeBlockInTree, logicalConditionConjunctionBooleanName, true);
		*logicalConditionConjunctionIndex = *logicalConditionConjunctionIndex + 1;
		//cout << "B: *logicalConditionConjunctionIndex = " << *logicalConditionConjunctionIndex << endl;
		*currentCodeBlockInTree = currentCodeBlockInTreeAtCurrentLevel2->next;
		currentCodeBlockInTreeAtCurrentLevel2 = currentCodeBlockInTreeAtCurrentLevel2->next;
		if(!contextFound)
		{
			currentCodeBlockInTreeAtCurrentLevel1 = currentCodeBlockInTreeAtCurrentLevel1->next;
		}
	}
		
		//REDUNDANT: only createCodeBlockForGivenConditions() is necessary here [because logical conditions and conjunction conditions will be connected to the children already]
		//NB am attempting to create a general implementation (ie NLP independent, based on what is semantically correct based on GIA specification); therefore need to handle all cases, not just those generated by NLP at present: therefore implement REDUNDANT case 
	//if object near a car that is behind the driveway / if object has a car that is near the house
	//if(item > 3){		/	if(greaterthan(item, 3)){
	NLCitem * conditionObjectItem2 = new NLCitem(currentLogicalConditionObject, NLC_ITEM_TYPE_TEMPVAR);	//not used
	if(createCodeBlockForGivenConditions(currentCodeBlockInTree, conditionObjectItem2, currentLogicalConditionObject, sentenceIndex, &logicalConditionConjunctionVariables))
	{
		string logicalConditionConjunctionBooleanName = generateLogicalConditionConjunctionBooleanName(*logicalConditionConjunctionIndex);
		*currentCodeBlockInTree = createCodeBlockSetBoolVar(*currentCodeBlockInTree, logicalConditionConjunctionBooleanName, true);
		*logicalConditionConjunctionIndex = *logicalConditionConjunctionIndex + 1;
		//cout << "C: *logicalConditionConjunctionIndex = " << *logicalConditionConjunctionIndex << endl;
		*currentCodeBlockInTree = currentCodeBlockInTreeAtCurrentLevel2->next;
		currentCodeBlockInTreeAtCurrentLevel2 = currentCodeBlockInTreeAtCurrentLevel2->next;
		if(!contextFound)
		{
			currentCodeBlockInTreeAtCurrentLevel1 = currentCodeBlockInTreeAtCurrentLevel1->next;
		}
	}
		
	*currentCodeBlockInTree = currentCodeBlockInTreeAtCurrentLevel1;
	
	//a) look for conjunction conditions connected to the logical condition ("if/while") object
	for(vector<GIAentityConnection*>::iterator connectionIter = currentLogicalConditionObject->conditionNodeList->begin(); connectionIter != currentLogicalConditionObject->conditionNodeList->end(); connectionIter++)
	{
		GIAentityNode * conditionEntity = (*connectionIter)->entity;
		checkConditionForLogicalCondition(currentCodeBlockInTree, conditionEntity, sentenceIndex, logicalOperation, logicalConditionConjunctionIndex, logicalConditionConjunctionArray);
	}
	
	//b) look for conjunction conditions connected to the conditions of the logical condition ("if/while") object
	for(vector<GIAentityConnection*>::iterator connectionIter2 = currentLogicalConditionObject->conditionNodeList->begin(); connectionIter2 != currentLogicalConditionObject->conditionNodeList->end(); connectionIter2++)
	{
		GIAentityNode * conditionEntity2 = (*connectionIter2)->entity;
		for(vector<GIAentityConnection*>::iterator connectionIter = conditionEntity2->conditionNodeList->begin(); connectionIter != conditionEntity2->conditionNodeList->end(); connectionIter++)
		{
			GIAentityNode * conditionEntity = (*connectionIter)->entity;
			checkConditionForLogicalCondition(currentCodeBlockInTree, conditionEntity, sentenceIndex, logicalOperation, logicalConditionConjunctionIndex, logicalConditionConjunctionArray);
		}
	}

	//c) look for condition conjunctions connected to the properties of the logical condition ("if/while") object  [REDUNDANT: because logical conditions and conjunction conditions will be connected to the children already]
	//NB am attempting to create a general implementation (ie NLP independent, based on what is semantically correct based on GIA specification); therefore need to handle all cases, not just those generated by NLP at present: therefore implement REDUNDANT case 
	for(vector<GIAentityConnection*>::iterator connectionIter = currentLogicalConditionObject->propertyNodeList->begin(); connectionIter != currentLogicalConditionObject->propertyNodeList->end(); connectionIter++)
	{
		GIAentityNode * propertyEntity = (*connectionIter)->entity;
		for(vector<GIAentityConnection*>::iterator connectionIter2 = propertyEntity->conditionNodeList->begin(); connectionIter2 != propertyEntity->conditionNodeList->end(); connectionIter2++)
		{
			GIAentityNode * conditionEntity = (*connectionIter)->entity;
			checkConditionForLogicalCondition(currentCodeBlockInTree, conditionEntity, sentenceIndex, logicalOperation, logicalConditionConjunctionIndex, logicalConditionConjunctionArray);
		}
	}
	
	//d) look for conjunction conditions connected to the parent of the logical condition ("if/while") object
	for(vector<GIAentityConnection*>::iterator connectionIter = currentLogicalConditionObject->propertyNodeReverseList->begin(); connectionIter != currentLogicalConditionObject->propertyNodeReverseList->end(); connectionIter++)
	{
		GIAentityNode * parentEntity = (*connectionIter)->entity;
		for(vector<GIAentityConnection*>::iterator connectionIter2 = parentEntity->conditionNodeList->begin(); connectionIter2 != parentEntity->conditionNodeList->end(); connectionIter2++)
		{
			GIAentityNode * conditionEntity = (*connectionIter)->entity;
			checkConditionForLogicalCondition(currentCodeBlockInTree, conditionEntity, sentenceIndex, logicalOperation, logicalConditionConjunctionIndex, logicalConditionConjunctionArray);
		}
	}
#endif			
	
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
					(conditionEntity->conditionSubjectEntity->back())->parsedForNLCcodeBlocks = true;
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
					(conditionEntity->conditionObjectEntity->back())->parsedForNLCcodeBlocks = true;
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
					(conditionEntity->conditionObjectEntity->back())->parsedForNLCcodeBlocks = true;

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

void tagAllEntitiesInSentenceSubsetAsPertainingToConditionLogicalOperation(GIAentityNode * entity, int sentenceIndex, bool tagOrUntag)
{
	for(int i=0; i<GIA_ENTITY_NUMBER_OF_VECTOR_CONNECTION_TYPES; i++)
	{
		if(i != GIA_ENTITY_VECTOR_CONNECTION_TYPE_NODE_DEFINING_INSTANCE)
		{
			for(vector<GIAentityConnection*>::iterator connectionIter = entity->entityVectorConnectionsArray[i].begin(); connectionIter != entity->entityVectorConnectionsArray[i].end(); connectionIter++)
			{
				GIAentityConnection * connection = (*connectionIter);
				GIAentityNode * connectedEntity = connection->entity;
				if((tagOrUntag && !(connectedEntity->NLCconditionLogicalOperations)) || (!tagOrUntag && (connectedEntity->NLCconditionLogicalOperations)))
				{
					bool foundConditionLogicalOperation = false;
					for(int i=1; i<NLC_CONDITION_LOGICAL_OPERATIONS_NUMBER_OF_TYPES; i++)		//i=1 to ignore "for"
					{
						if(connectedEntity->entityName == conditionLogicalOperationsArray[i])
						{
							foundConditionLogicalOperation = true;
						}
					}
					if(!foundConditionLogicalOperation)
					{//don't cross the "if" boundary
						if(checkSentenceIndexParsingCodeBlocks(connectedEntity, sentenceIndex, false))
						{
							if(connectedEntity->isConcept)
							{
								cout << "setAllEntitiesInSentenceSubsetAsPertainingToConditionLogicalOperation() error: NLC_SUPPORT_CONDITION_LOGICAL_OPERATIONS_BASED_ON_CONCEPTS only handles substance concepts. GIA_CREATE_SUBSTANCE_CONCEPTS_FOR_ALL_SENTENCES_WITH_CONCEPTS must be enabled." << endl;
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
									connection->NLCconditionLogicalOperations = true;
									connectedEntity->NLCconditionLogicalOperations = true;
								}
								else
								{
									#ifdef NLC_DEBUG5
									cout << "untagged: " << connectedEntity->entityName << endl;
									#endif
									connection->NLCconditionLogicalOperations = false;
									connectedEntity->NLCconditionLogicalOperations = false;
								}
								tagAllEntitiesInSentenceSubsetAsPertainingToConditionLogicalOperation(connectedEntity, sentenceIndex, tagOrUntag);
							}
						}
					}
				}
			}
		}
	}
}
#endif

bool generateCodeBlocksPart1(NLCcodeblock ** currentCodeBlockInTree, vector<GIAentityNode*> * entityNodesActiveListComplete, int sentenceIndex, string NLCfunctionName)
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
	if(!(actionEntity->NLCconditionLogicalOperations))
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

			#ifndef NLC_PARSE_CHILD_PROPERTIES_AND_CONDITIONS_OF_CONTEXT_PARENT
			bool contextFound = false;
			NLClogicalConditionConjunctionVariables logicalConditionConjunctionVariables;	//not used
			if(actionHasSubject)
			{
				//[*^]
				//cout << "executing generateContextBlocksAndInitialiseParentIfNecessary subjectEntity" << endl;
				generateContextBlocksAndInitialiseParentIfNecessary(currentCodeBlockInTree, subjectEntity, sentenceIndex, &contextFound, &logicalConditionConjunctionVariables);
			}
			if(actionHasObject)
			{
				generateContextBlocksAndInitialiseParentIfNecessary(currentCodeBlockInTree, objectEntity, sentenceIndex, &contextFound, &logicalConditionConjunctionVariables);
			}
			#endif
		}


		if(actionHasObject)
		{
			#ifdef NLC_PARSE_CHILD_PROPERTIES_AND_CONDITIONS_OF_CONTEXT_PARENT
			bool objectContextFound = false;
			NLClogicalConditionConjunctionVariables logicalConditionConjunctionVariables;	//not used
			generateContextBlocksAndInitialiseParentIfNecessary(currentCodeBlockInTree, objectEntity, sentenceIndex, &objectContextFound, &logicalConditionConjunctionVariables);
			#else
			*currentCodeBlockInTree = generateConditionBlocks(*currentCodeBlockInTree, objectEntity, sentenceIndex, NLC_ITEM_TYPE_FUNCTION_OBJECT, &logicalConditionConjunctionVariables);
			#endif
			
			if(actionHasSubject)
			{
				#ifdef NLC_PARSE_CHILD_PROPERTIES_AND_CONDITIONS_OF_CONTEXT_PARENT
				bool subjectContextFound = false;
				NLClogicalConditionConjunctionVariables logicalConditionConjunctionVariables;	//not used
				generateContextBlocksAndInitialiseParentIfNecessary(currentCodeBlockInTree, subjectEntity, sentenceIndex, &subjectContextFound, &logicalConditionConjunctionVariables);
				#else
				*currentCodeBlockInTree = generateConditionBlocks(*currentCodeBlockInTree, subjectEntity, sentenceIndex, NLC_ITEM_TYPE_FUNCTION_OWNER, &logicalConditionConjunctionVariables);
				#endif
				
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

			actionEntity->parsedForNLCcodeBlocks = true;
			//actionEntity->parsedForNLCcodeBlocksActionRound = true;
			//objectEntity->parsedForNLCcodeBlocksActionRound = true;
		}
		else if(actionHasSubject)
		{
			//[**^]
			#ifdef NLC_PARSE_CHILD_PROPERTIES_AND_CONDITIONS_OF_CONTEXT_PARENT
			bool subjectContextFound = false;
			NLClogicalConditionConjunctionVariables logicalConditionConjunctionVariables;
			generateContextBlocksAndInitialiseParentIfNecessary(currentCodeBlockInTree, subjectEntity, sentenceIndex, &subjectContextFound, &logicalConditionConjunctionVariables);
			#else
			*currentCodeBlockInTree = generateConditionBlocks(*currentCodeBlockInTree, subjectEntity, sentenceIndex, NLC_ITEM_TYPE_FUNCTION_OWNER, &logicalConditionConjunctionVariables);
			#endif
				
			//cout << "subjectRequiredTempVar" << endl;
			functionItem->context.push_back(generateInstanceName(subjectEntity));

			functionExecuteCodeBlockInTree = *currentCodeBlockInTree;
			*currentCodeBlockInTree = createCodeBlockExecute(*currentCodeBlockInTree, functionItem);

			actionEntity->parsedForNLCcodeBlocks = true;
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
				(*entityIter)->parsedForNLCcodeBlocks = true;
				actionCondition->parsedForNLCcodeBlocks = true;
			}
			for(vector<GIAentityConnection*>::iterator entityIter = actionEntity->propertyNodeList->begin(); entityIter != actionEntity->propertyNodeList->end(); entityIter++)
			{
				GIAentityNode * actionProperty = (*entityIter)->entity;
				(*entityIter)->parsedForNLCcodeBlocks = true;
				actionProperty->parsedForNLCcodeBlocks = true;
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

	generateObjectInitialisationsBasedOnPropertiesAndConditions(actionEntity, currentCodeBlockInTree, sentenceIndex, "", "");
	generateObjectInitialisationsBasedOnSubstanceConcepts(actionEntity, currentCodeBlockInTree, sentenceIndex);
}
#endif

//added 1e6a
bool generateContextBlocksAndInitialiseParentIfNecessary(NLCcodeblock ** currentCodeBlockInTree, GIAentityNode * currentEntity, int sentenceIndex, bool * contextFound, NLClogicalConditionConjunctionVariables * logicalConditionConjunctionVariables)
{
	bool result = false;
	bool possibleContextParentFound = false;

	//cout << "generateContextBlocksAndInitialiseParentIfNecessary: currentEntity = " << currentEntity->entityName << endl;
	if(checkSentenceIndexParsingCodeBlocks(currentEntity, sentenceIndex, false) || currentEntity->parsedForNLCcodeBlocks || assumedToAlreadyHaveBeenDeclared(currentEntity))
	{
		if(!(currentEntity->propertyNodeReverseList->empty()))
		{
			GIAentityNode * parentEntity = (currentEntity->propertyNodeReverseList->back())->entity;
			if(checkSentenceIndexParsingCodeBlocks(parentEntity, sentenceIndex, false) || parentEntity->parsedForNLCcodeBlocks || assumedToAlreadyHaveBeenDeclared(parentEntity))
			{
				if(generateContextBlocksAndInitialiseParentIfNecessary(currentCodeBlockInTree, parentEntity, sentenceIndex, contextFound, logicalConditionConjunctionVariables))
				{
					//cout << "\tgenerateContextBlocksAndInitialiseParentIfNecessary passed: " << currentEntity->entityName << endl;

					result = true;
					*contextFound = true;
				#ifndef NLC_PARSE_CHILD_PROPERTIES_AND_CONDITIONS_OF_CONTEXT_PARENT
					NLCitem * propertyItem = new NLCitem(currentEntity, NLC_ITEM_TYPE_CLASS);
					
					//target property item:
					if(assumedToAlreadyHaveBeenDeclared(currentEntity))
					{
					
						#ifndef NLC_LOGICAL_CONDITIONS_SUPPORT_CONJUNCTIONS
						if(logicalOperation == NLC_CONDITION_LOGICAL_OPERATIONS_FOR)
						{
						#endif
							*currentCodeBlockInTree = createCodeBlockForPropertyListLocal(*currentCodeBlockInTree, propertyItem);
						#ifndef NLC_LOGICAL_CONDITIONS_SUPPORT_CONJUNCTIONS
						}
						else if(logicalOperation == NLC_CONDITION_LOGICAL_OPERATIONS_IF)
						{
							*currentCodeBlockInTree = createCodeBlockIfHasPropertyLocal(*currentCodeBlockInTree, propertyItem, logicalConditionConjunctionVariables->negative);
						}
						else if(logicalOperation == NLC_CONDITION_LOGICAL_OPERATIONS_WHILE)
						{
							*currentCodeBlockInTree = createCodeBlockWhileHasPropertyLocal(*currentCodeBlockInTree, propertyItem, logicalConditionConjunctionVariables->negative);
						}	
						#endif
					}
					else
					{
						propertyItem->context.push_back(generateInstanceName(parentEntity));
						#ifndef NLC_LOGICAL_CONDITIONS_SUPPORT_CONJUNCTIONS
						if(logicalOperation == NLC_CONDITION_LOGICAL_OPERATIONS_FOR)
						{
						#endif
							*currentCodeBlockInTree = createCodeBlockForPropertyList(*currentCodeBlockInTree, propertyItem);
						#ifndef NLC_LOGICAL_CONDITIONS_SUPPORT_CONJUNCTIONS
						}
						else if(logicalOperation == NLC_CONDITION_LOGICAL_OPERATIONS_IF)
						{
							*currentCodeBlockInTree = createCodeBlockIfHasProperty(*currentCodeBlockInTree, propertyItem, logicalConditionConjunctionVariables->negative);
						}
						else if(logicalOperation == NLC_CONDITION_LOGICAL_OPERATIONS_WHILE)
						{
							*currentCodeBlockInTree = createCodeBlockWhileHasProperty(*currentCodeBlockInTree, propertyItem, logicalConditionConjunctionVariables->negative);
						}	
						#endif
					}

					//IS THIS REQUIRED?
					if(checkSentenceIndexParsingCodeBlocks(parentEntity, sentenceIndex, false))	//added 1e7b
					{
						//required to prevent generateObjectInitialisationsBasedOnPropertiesAndConditions() from writing property:
						for(vector<GIAentityConnection*>::iterator propertyNodeListIterator = parentEntity->propertyNodeList->begin(); propertyNodeListIterator < parentEntity->propertyNodeList->end(); propertyNodeListIterator++)
						{
							GIAentityConnection * propertyConnection = (*propertyNodeListIterator);
							GIAentityNode * propertyEntity = propertyConnection->entity;
							if(propertyEntity == currentEntity)
							{
								propertyConnection->parsedForNLCcodeBlocks = true;
							}
						}
						parentEntity->parsedForNLCcodeBlocks = true;	//CHECKTHIS is no longer required as generateConditionBlocks() [in NLC_PARSE_CHILD_PROPERTIES_AND_CONDITIONS_OF_CONTEXT_PARENT below] does not set entity's parsedForNLCcodeBlocks tag
					}
				#endif
				}
			}
			else
			{
				possibleContextParentFound = true;
			}
		}
		else
		{
			possibleContextParentFound = true;
		}

		//cout << "generateContextBlocksAndInitialiseParentIfNecessary, sentenceIndex = " << sentenceIndex << endl;
		//cout << "\tpossibleContextParentFound = " << possibleContextParentFound << endl;
		//cout << "\tcurrentEntity->entityName = " << currentEntity->entityName << endl;

		if(possibleContextParentFound)
		{
			/*
			cout << "\tpossibleContextParentFound: " << currentEntity->entityName << endl;
			cout << "currentEntity->grammaticalDefiniteTemp = " << currentEntity->grammaticalDefiniteTemp << endl;
			cout << "currentEntity->grammaticalProperNounTemp = " << currentEntity->grammaticalProperNounTemp << endl;
			cout << "currentEntity->NLClocalListVariableHasBeenInitialised = " << currentEntity->NLClocalListVariableHasBeenInitialised << endl;
			cout << "currentEntity->NLCisSingularArgument = " << currentEntity->NLCisSingularArgument << endl;
			*/
			result = true;
			#ifdef NLC_CREATE_IMPLICITLY_DECLARED_ACTION_OBJECT_AND_SUBJECT_VARIABLES
			if(!assumedToAlreadyHaveBeenDeclared(currentEntity))
			{
				//cout << "!assumedToAlreadyHaveBeenDeclared" << endl;
				if(!(currentEntity->parsedForNLCcodeBlocks))
				{
					#ifdef NLC_DEBUG
					cout << "createCodeBlocksCreateNewLocalListVariable: " << currentEntity->entityName << endl;
					#endif
					
					if(currentEntity->NLClocalListVariableHasBeenDeclared)
					{//added 1g8a 11-July-2014
						*currentCodeBlockInTree = createCodeBlockAddNewPropertyToLocalList(*currentCodeBlockInTree, currentEntity, currentEntity);
					}
					else
					{
						*currentCodeBlockInTree = createCodeBlocksCreateNewLocalListVariable(*currentCodeBlockInTree, currentEntity);
					}			
					currentEntity->parsedForNLCcodeBlocks = true;
					currentEntity->NLClocalListVariableHasBeenInitialised = true;
					//NLCcodeblock firstCodeBlockInSection = *currentCodeBlockInTree;
					generateObjectInitialisationsBasedOnPropertiesAndConditions(currentEntity, currentCodeBlockInTree, sentenceIndex, "", "");

					#ifdef GIA_TRANSLATOR_DREAM_MODE_LINK_SPECIFIC_CONCEPTS_AND_ACTIONS
					//Part 2b: generate object initialisations based on substance concepts (class inheritance)
					generateObjectInitialisationsBasedOnSubstanceConcepts(currentEntity, currentCodeBlockInTree, sentenceIndex);
					#endif
				}
			}
			#endif

			NLCitem * propertyItem = new NLCitem(currentEntity, NLC_ITEM_TYPE_CLASS);
			//context property item:
			if(assumedToAlreadyHaveBeenDeclared(currentEntity))
			{
				*currentCodeBlockInTree = createCodeBlockForPropertyListLocal(*currentCodeBlockInTree, propertyItem);
			}
			else
			{
				*currentCodeBlockInTree = createCodeBlockForPropertyList(*currentCodeBlockInTree, propertyItem);
			}

			#ifdef NLC_PARSE_CHILD_PROPERTIES_AND_CONDITIONS_OF_CONTEXT_PARENT			
			//added 1g6a
			//if((currentEntity->grammaticalDefiniteTemp) && !(currentEntity->grammaticalProperNounTemp) && !(currentEntity->NLClocalListVariableHasBeenInitialised) && !(currentEntity->NLCisSingularArgument))
			//{
			#ifdef NLC_DEBUG
			cout << "\tgenerateConditionBlocks: " << currentEntity->entityName << endl;
			#endif
			//parse the children (properties and conditions) of an undeclared definite parent 
			*currentCodeBlockInTree = generateConditionBlocks(*currentCodeBlockInTree, currentEntity, sentenceIndex, logicalConditionConjunctionVariables);
			//}
			#endif

		}
	}

	return result;
}

NLCcodeblock * generateConditionBlocks(NLCcodeblock * currentCodeBlockInTree, GIAentityNode * entity, int sentenceIndex, NLClogicalConditionConjunctionVariables * logicalConditionConjunctionVariables)
{
	bool entityHasParent = false;

	//cout << "itemType = " << itemType << endl;
	
	createCodeBlockForStatements(&currentCodeBlockInTree, generateInstanceName(entity), entity, sentenceIndex, logicalConditionConjunctionVariables);

	return currentCodeBlockInTree;
}



bool generateCodeBlocksPart2(NLCcodeblock ** currentCodeBlockInTree, vector<GIAentityNode*> * entityNodesActiveListComplete, int sentenceIndex, string NLCfunctionName)
{
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode * entity = *entityIter;
		if(checkSentenceIndexParsingCodeBlocks(entity, sentenceIndex, false))
		{
			generateInitialisationCodeBlock(currentCodeBlockInTree, entity , sentenceIndex, NLCfunctionName);
		}
	}
	return true;
}

void generateInitialisationCodeBlock(NLCcodeblock ** currentCodeBlockInTree, GIAentityNode * entity , int sentenceIndex, string NLCfunctionName)
{
	#ifdef NLC_SUPPORT_CONDITION_LOGICAL_OPERATIONS
	if(!(entity->NLCconditionLogicalOperations))
	{
	#endif

		GIAentityNode * parentEntity = getParent(entity, sentenceIndex);

		#ifdef NLC_CREATE_IMPLICITLY_DECLARED_ACTION_OBJECT_AND_SUBJECT_VARIABLES
		//moved here 1e8a (out of generateObjectInitialisationsBasedOnPropertiesAndConditions)
		//added 1e6c: eg A chicken's hat has a bike. / A blue dog has a bike.
		if(!(parentEntity->isConcept))
		{
			if(!(parentEntity->parsedForNLCcodeBlocks))	// && !(entity->parsedForNLCcodeBlocksActionRound)
			{
				if(!assumedToAlreadyHaveBeenDeclared(parentEntity))
				{
					if(!(parentEntity->isAction))	//added 1e6d
					{
						if(checkSentenceIndexParsingCodeBlocks(parentEntity, sentenceIndex, false))
						{
							if(!(parentEntity->isCondition))
							{
								if(!(parentEntity->isSubstanceConcept) && !(parentEntity->isActionConcept))
								{
									#ifdef NLC_DEBUG
									cout << "createCodeBlocksCreateNewLocalListVariable: " << parentEntity->entityName << endl;
									#endif
									if(parentEntity->NLClocalListVariableHasBeenDeclared)
									{//added 1g8a 11-July-2014
										*currentCodeBlockInTree = createCodeBlockAddNewPropertyToLocalList(*currentCodeBlockInTree, parentEntity, parentEntity);
									}
									else
									{
										*currentCodeBlockInTree = createCodeBlocksCreateNewLocalListVariable(*currentCodeBlockInTree, parentEntity);
									}
									parentEntity->parsedForNLCcodeBlocks = true;
									parentEntity->NLClocalListVariableHasBeenInitialised = true;
									//cout << "createCodeBlocksCreateNewLocalListVariable: " << parentEntity->entityName << endl;

									#ifdef GIA_TRANSLATOR_DREAM_MODE_LINK_SPECIFIC_CONCEPTS_AND_ACTIONS
									//Part 2b: generate object initialisations based on substance concepts (class inheritance)
									generateObjectInitialisationsBasedOnSubstanceConcepts(parentEntity, currentCodeBlockInTree, sentenceIndex);
									#endif
								}
							}
						}
					}
				}
			}
		}
		#endif
		#ifdef NLC_DEBUG
		cout << "\tgenerateObjectInitialisationsBasedOnPropertiesAndConditions:" << endl;
		#endif
		generateObjectInitialisationsBasedOnPropertiesAndConditions(parentEntity, currentCodeBlockInTree, sentenceIndex, "", "");
	#ifdef NLC_SUPPORT_CONDITION_LOGICAL_OPERATIONS
	}
	#endif
}

GIAentityNode * getParent(GIAentityNode * currentEntity, int sentenceIndex)
{
	if(!(currentEntity->propertyNodeReverseList->empty()))
	{
		GIAentityNode * parentEntity = (currentEntity->propertyNodeReverseList->back())->entity;

		if(checkSentenceIndexParsingCodeBlocks(parentEntity, sentenceIndex, false) || parentEntity->parsedForNLCcodeBlocks)
		{
			currentEntity = getParent(parentEntity, sentenceIndex);
		}
	}
	else if(!(currentEntity->incomingConditionNodeList->empty()))
	{//added 1e9a
		GIAentityNode * conditionEntity = (currentEntity->incomingConditionNodeList->back())->entity;

		bool foundConditionSubject = false;
		GIAentityNode * conditionSubject = NULL;
		if(!(conditionEntity->conditionSubjectEntity->empty()))
		{
			conditionSubject = (conditionEntity->conditionSubjectEntity->back())->entity;
			foundConditionSubject = true;

			if(checkSentenceIndexParsingCodeBlocks(conditionSubject, sentenceIndex, false) || conditionSubject->parsedForNLCcodeBlocks)
			{
				currentEntity = getParent(conditionSubject, sentenceIndex);
			}
		}
	}

	return currentEntity;
}


//added recursion 1e8a
bool generateObjectInitialisationsBasedOnPropertiesAndConditions(GIAentityNode * entity, NLCcodeblock ** currentCodeBlockInTree, int sentenceIndex, string parentName, string parentConditionName)
{
	bool performedAtLeastOneObjectInitialisation = false;
	if(!(entity->isSubstanceConcept) && !(entity->isActionConcept))
	{
		//property initialisations
		for(vector<GIAentityConnection*>::iterator propertyNodeListIterator = entity->propertyNodeList->begin(); propertyNodeListIterator < entity->propertyNodeList->end(); propertyNodeListIterator++)
		{
			GIAentityConnection * propertyConnection = (*propertyNodeListIterator);
			GIAentityNode* propertyEntity = propertyConnection->entity;

			if(checkSentenceIndexParsingCodeBlocks(propertyEntity, sentenceIndex, false) || propertyEntity->parsedForNLCcodeBlocks)
			{//only write properties that are explicated in current sentence

				bool performedAtLeastOneObjectInitialisationAtThisLevel = false;
				NLCcodeblock * firstCodeBlockInSection = *currentCodeBlockInTree;

				//cout << "entity->entityName = " << entity->entityName << endl;
				//for(all items in context){
				NLCitem * entityClass = new NLCitem(entity, NLC_ITEM_TYPE_CLASS);
				if(assumedToAlreadyHaveBeenDeclared(entity))
				{
					*currentCodeBlockInTree = createCodeBlockForPropertyListLocal(*currentCodeBlockInTree, entityClass);
				}
				else
				{
					entityClass->context.push_back(parentName);
					*currentCodeBlockInTree = createCodeBlockForPropertyList(*currentCodeBlockInTree, entityClass);
				}

				//cout << "createCodeBlockForPropertyList: " << entity->entityName << endl;

				if(!(propertyConnection->parsedForNLCcodeBlocks) && !(propertyEntity->parsedForNLCcodeBlocks))
				{
					#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS
					if(assumedToAlreadyHaveBeenDeclared(propertyEntity))
					{
						//use function argument PropertyList (do not create a new property); eg "the ball" in "Tom has the ball"
						//cout << "propertyEntity->entityName = " << propertyEntity->entityName << endl;
						//for(all items in context){

						NLCcodeblock * firstCodeBlockInSection2 = *currentCodeBlockInTree;

						NLCitem * propertyClass = new NLCitem(propertyEntity, NLC_ITEM_TYPE_CLASS);
						*currentCodeBlockInTree = createCodeBlockForPropertyListLocal(*currentCodeBlockInTree, propertyClass);

						*currentCodeBlockInTree = createCodeBlockAddProperty(*currentCodeBlockInTree, entity, propertyEntity, sentenceIndex);
						//cout << "createCodeBlockAddProperty: " << entity->entityName << ", " << propertyEntity->entityName << endl;

						*currentCodeBlockInTree = firstCodeBlockInSection2->next;
					}
					else
					{
					#endif
						//create a new property; eg "a ball" in "Tom has a ball"

						*currentCodeBlockInTree = createCodeBlockAddNewProperty(*currentCodeBlockInTree, entity, propertyEntity, sentenceIndex);
						//cout << "createCodeBlockAddNewProperty: " << entity->entityName << ", " << propertyEntity->entityName << endl;
						
						if(propertyEntity->NLClocalListVariableHasBeenDeclared)
						{//added 1g8a 11-July-2014
							*currentCodeBlockInTree = createCodeBlockAddPropertyToLocalList(*currentCodeBlockInTree, propertyEntity, propertyEntity);
						}

					#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS
					}
					#endif

					/*
					cout << "generateObjectInitialisationsBasedOnPropertiesAndConditions():" << endl;
					cout << "entity->entityName = " << entity->entityName << endl;
					cout << "propertyEntity->entityName = " << propertyEntity->entityName << endl;
					*/

					propertyConnection->parsedForNLCcodeBlocks = true;
					propertyEntity->parsedForNLCcodeBlocks = true;		//added 3 October 2013 NLC1b2b - used for quick access of instances already declared in current context

					//moved 1e1b: only generate object initialisations for items based on subject concepts when items are created in context
					#ifdef GIA_TRANSLATOR_DREAM_MODE_LINK_SPECIFIC_CONCEPTS_AND_ACTIONS
					//Part 2b: generate object initialisations based on substance concepts (class inheritance)
					generateObjectInitialisationsBasedOnSubstanceConcepts(propertyEntity, currentCodeBlockInTree, sentenceIndex);
					#endif

					performedAtLeastOneObjectInitialisationAtThisLevel = true;
				}

				NLCcodeblock * firstCodeBlockBeforeRecursion = *currentCodeBlockInTree;
				bool performedAtLeastOneObjectInitialisationAtALowerLevel = generateObjectInitialisationsBasedOnPropertiesAndConditions(propertyEntity, currentCodeBlockInTree, sentenceIndex, generateInstanceName(entity), "");

				generateObjectInitialisationsBasedOnPropertiesAndConditionsUpdateCodeBlockPointer(currentCodeBlockInTree, firstCodeBlockBeforeRecursion, firstCodeBlockInSection, performedAtLeastOneObjectInitialisationAtThisLevel, performedAtLeastOneObjectInitialisationAtALowerLevel, &performedAtLeastOneObjectInitialisation);
			}
		}

		#ifdef NLC_LOGICAL_CONDITIONS_SUPPORT_CONJUNCTIONS
		//added NLC 1g5e:
		if(!(entity->isCondition))
		{//do not parse conditions of conditions as one of the conditions is a logical condition conjunction (ie and/or)
		#endif	
			//state initialisations
			for(vector<GIAentityConnection*>::iterator conditionNodeListIterator = entity->conditionNodeList->begin(); conditionNodeListIterator < entity->conditionNodeList->end(); conditionNodeListIterator++)
			{
				GIAentityConnection * conditionConnection = (*conditionNodeListIterator);
				GIAentityNode* conditionEntity = conditionConnection->entity;

				#ifdef NLC_SUPPORT_CONDITION_LOGICAL_OPERATIONS
				bool foundConditionLogicalOperation = false;
				for(int i=1; i<NLC_CONDITION_LOGICAL_OPERATIONS_NUMBER_OF_TYPES; i++)	//i=1 to ignore "for"
				{
					if(conditionEntity->entityName == conditionLogicalOperationsArray[i])
					{
						foundConditionLogicalOperation = true;
					}
				}
				if(!foundConditionLogicalOperation)
				//if(!(conditionConnection->NLCconditionLogicalOperations) && !(conditionEntity->NLCconditionLogicalOperations))	//this alternative test would require "tagAllEntitiesInSentenceSubsetAsPertainingToConditionLogicalOperation(conditionSubject, sentenceIndex, false);" to be called before "generateObjectInitialisationsBasedOnPropertiesAndConditions()"
				{
				#endif
					bool foundConditionObject = false;
					GIAentityNode * conditionObject = NULL;
					if(!(conditionEntity->conditionObjectEntity->empty()))
					{
						conditionObject = (conditionEntity->conditionObjectEntity->back())->entity;
						foundConditionObject = true;

						if(checkSentenceIndexParsingCodeBlocks(conditionEntity,  sentenceIndex, false) || conditionEntity->parsedForNLCcodeBlocks)
						{//only write conditions that are explicated in current sentence

							bool performedAtLeastOneObjectInitialisationAtThisLevel = false;
							NLCcodeblock * firstCodeBlockInSection = *currentCodeBlockInTree;

							//cout << "entity->entityName = " << entity->entityName << endl;
							//for(all items in context){
							NLCitem * entityClass = new NLCitem(entity, NLC_ITEM_TYPE_CLASS);
							NLCitem * conditionObjectClass = new NLCitem(conditionObject, NLC_ITEM_TYPE_CLASS);

							if(assumedToAlreadyHaveBeenDeclared(entity))
							{
								/*
								cout << "\tassumedToAlreadyHaveBeenDeclared" << endl;
								cout << "parentName = " << parentName << endl;
								cout << "entity = " << entity->entityName << endl;
								cout << "conditionEntity = " << conditionEntity->entityName << endl;
								cout << "conditionObject = " << conditionObject->entityName << endl;
								*/
								*currentCodeBlockInTree = createCodeBlockForPropertyListLocal(*currentCodeBlockInTree, entityClass);
							}
							else
							{
								/*
								cout << "\t!assumedToAlreadyHaveBeenDeclared" << endl;
								cout << "parentName = " << parentName << endl;
								cout << "entity = " << entity->entityName << endl;
								cout << "conditionEntity = " << conditionEntity->entityName << endl;
								cout << "conditionObject = " << conditionObject->entityName << endl;
								*/
								NLCitem * parentConditionItem = new NLCitem(parentConditionName, NLC_ITEM_TYPE_CLASS);
								parentConditionItem->context.push_back(parentName);
								*currentCodeBlockInTree = createCodeBlockForConditionList(*currentCodeBlockInTree, parentConditionItem, entityClass);
							}

							if(!(conditionConnection->parsedForNLCcodeBlocks) && !(conditionEntity->parsedForNLCcodeBlocks))
							{
								#ifdef NLC_DEBUG
								cout << "!(conditionConnection->parsedForNLCcodeBlocks): " << conditionObject->entityName << endl;
								#endif
								
								#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS
								if(assumedToAlreadyHaveBeenDeclared(conditionObject))
								{
									NLCcodeblock * firstCodeBlockInSection2 = *currentCodeBlockInTree;

									//use function argument PropertyList (do not create a new property to insert into condition); eg "the house" in "Tom is near a house"
									//cout << "conditionObject->entityName = " << conditionObject->entityName << endl;
									//for(all items in context){

									*currentCodeBlockInTree = createCodeBlockForPropertyListLocal(*currentCodeBlockInTree, conditionObjectClass);

									*currentCodeBlockInTree = createCodeBlockAddCondition(*currentCodeBlockInTree, entity, conditionEntity, sentenceIndex);

									*currentCodeBlockInTree = firstCodeBlockInSection2->next;
								}
								else
								{
								#endif
									//create a new condition; eg "a house" in "Tom is near a house"
									*currentCodeBlockInTree = createCodeBlockAddNewCondition(*currentCodeBlockInTree, entity, conditionEntity, sentenceIndex);
									
									if(conditionEntity->NLClocalListVariableHasBeenDeclared)
									{//added 1g8a 11-July-2014
										if(!(conditionEntity->conditionObjectEntity->empty()))
										{
											GIAentityNode * conditionObject = (conditionEntity->conditionObjectEntity->back())->entity;
											*currentCodeBlockInTree = createCodeBlockAddPropertyToLocalList(*currentCodeBlockInTree, conditionObject, conditionObject);
										}
									}
								#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS
								}
								#endif

								conditionConnection->parsedForNLCcodeBlocks = true;
								conditionEntity->parsedForNLCcodeBlocks = true;	//added 3 October 2013 NLC1b2b - used for quick access of instances already declared in current context
								conditionObject->parsedForNLCcodeBlocks = true;	//added 1e6d

								//moved 1e1b: only generate object initialisations for items based on subject concepts when items are created in context
								#ifdef GIA_TRANSLATOR_DREAM_MODE_LINK_SPECIFIC_CONCEPTS_AND_ACTIONS
								//Part 2b: generate object initialisations based on substance concepts (class inheritance)
								generateObjectInitialisationsBasedOnSubstanceConcepts(conditionEntity, currentCodeBlockInTree, sentenceIndex);
								#endif

								performedAtLeastOneObjectInitialisationAtThisLevel = true;
							}


							NLCcodeblock * firstCodeBlockBeforeRecursion = *currentCodeBlockInTree;
							bool performedAtLeastOneObjectInitialisationAtALowerLevel = generateObjectInitialisationsBasedOnPropertiesAndConditions(conditionObject, currentCodeBlockInTree, sentenceIndex, generateInstanceName(entity), conditionEntity->entityName);

							generateObjectInitialisationsBasedOnPropertiesAndConditionsUpdateCodeBlockPointer(currentCodeBlockInTree, firstCodeBlockBeforeRecursion, firstCodeBlockInSection, performedAtLeastOneObjectInitialisationAtThisLevel, performedAtLeastOneObjectInitialisationAtALowerLevel, &performedAtLeastOneObjectInitialisation);
						}
					}
					else
					{
						//no condition object
					}
				#ifdef NLC_SUPPORT_CONDITION_LOGICAL_OPERATIONS
				}
				#endif
			}
		#ifdef NLC_LOGICAL_CONDITIONS_SUPPORT_CONJUNCTIONS
		}
		#endif
	}
	return performedAtLeastOneObjectInitialisation;
}

void generateObjectInitialisationsBasedOnPropertiesAndConditionsUpdateCodeBlockPointer(NLCcodeblock ** currentCodeBlockInTree, NLCcodeblock * firstCodeBlockBeforeRecursion, NLCcodeblock * firstCodeBlockInSection, bool performedAtLeastOneObjectInitialisationAtThisLevel, bool performedAtLeastOneObjectInitialisationAtALowerLevel, bool * performedAtLeastOneObjectInitialisation)
{
	if(!performedAtLeastOneObjectInitialisationAtALowerLevel)
	{
		if(performedAtLeastOneObjectInitialisationAtThisLevel)
		{
			firstCodeBlockBeforeRecursion->codeBlockType = NLC_CODEBLOCK_TYPE_UNDEFINED;
			firstCodeBlockBeforeRecursion->next = NULL;
			firstCodeBlockBeforeRecursion->lowerLevel = NULL;
			firstCodeBlockBeforeRecursion->parameters.clear();

			*currentCodeBlockInTree = firstCodeBlockInSection;
			while((*currentCodeBlockInTree)->next != NULL)
			{
				*currentCodeBlockInTree = (*currentCodeBlockInTree)->next;
			}
		}
		else
		{
			//erase redundant for loops:
			*currentCodeBlockInTree = firstCodeBlockInSection;
			(*currentCodeBlockInTree)->codeBlockType = NLC_CODEBLOCK_TYPE_UNDEFINED;
			(*currentCodeBlockInTree)->next = NULL;
			(*currentCodeBlockInTree)->lowerLevel = NULL;
			(*currentCodeBlockInTree)->parameters.clear();
		}
	}
	else
	{
		*currentCodeBlockInTree = firstCodeBlockInSection;
		while((*currentCodeBlockInTree)->next != NULL)
		{
			*currentCodeBlockInTree = (*currentCodeBlockInTree)->next;
		}
	}
	if(performedAtLeastOneObjectInitialisationAtThisLevel || performedAtLeastOneObjectInitialisationAtALowerLevel)
	{
		*performedAtLeastOneObjectInitialisation = true;
	}
}

#ifdef GIA_TRANSLATOR_DREAM_MODE_LINK_SPECIFIC_CONCEPTS_AND_ACTIONS
void generateObjectInitialisationsBasedOnSubstanceConcepts(GIAentityNode * entity, NLCcodeblock ** currentCodeBlockInTree, int sentenceIndex)
{
	//added 6 December 2013: take into account plain concepts; eg "dogs are fat. The dog rides the bike." <- the dog will be given the property 'fat'
	GIAentityNode * conceptEntity = (entity->entityNodeDefiningThisInstance->back())->entity;
	generateObjectInitialisationsBasedOnSubstanceConceptsRecurse(entity, conceptEntity, currentCodeBlockInTree, sentenceIndex, "", "");

	for(vector<GIAentityConnection*>::iterator entityNodeDefinitionListIterator = entity->entityNodeDefinitionList->begin(); entityNodeDefinitionListIterator < entity->entityNodeDefinitionList->end(); entityNodeDefinitionListIterator++)
	{
		GIAentityConnection * definitionConnection = (*entityNodeDefinitionListIterator);
		//if(!(definitionConnection->parsedForNLCcodeBlocks))	//probably not required
		//{
		GIAentityNode* definitionEntity = definitionConnection->entity;
		//check the definition is a substance concept
		if((definitionEntity->isSubstanceConcept) || (definitionEntity->isActionConcept))	//added (definitionEntity->isActionConcept)  changed 1e2e
		{
			//cout << "isSubstanceConcept" << endl;
			definitionConnection->parsedForNLCcodeBlocks = true;

			generateObjectInitialisationsBasedOnSubstanceConceptsRecurse(entity, definitionEntity, currentCodeBlockInTree, sentenceIndex, "", "");
		}
		//}
	}
}

void generateObjectInitialisationsBasedOnSubstanceConceptsRecurse(GIAentityNode * entity, GIAentityNode * definitionEntity, NLCcodeblock ** currentCodeBlockInTree, int sentenceIndex, string parentName, string parentConditionName)
{
	#ifdef NLC_SUPPORT_CONDITION_LOGICAL_OPERATIONS_BASED_ON_CONCEPTS
	if(!(definitionEntity->NLCconditionLogicalOperations))
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

				//cout << "property initialisation: entity->entityName = " << entity->entityName << endl;
				//for(all items in context){
				NLCitem * entityClass = new NLCitem(entity, NLC_ITEM_TYPE_CLASS);
				if(assumedToAlreadyHaveBeenDeclared(entity))
				{
					*currentCodeBlockInTree = createCodeBlockForPropertyListLocal(*currentCodeBlockInTree, entityClass);
				}
				else
				{
					//bool entityHasParent = getEntityContext(entity, &(entityClass->context), false, sentenceIndex, true);
					entityClass->context.push_back(parentName);
					*currentCodeBlockInTree = createCodeBlockForPropertyList(*currentCodeBlockInTree, entityClass);
				}

				*currentCodeBlockInTree = createCodeBlockAddNewProperty(*currentCodeBlockInTree, entity, propertyEntity, sentenceIndex);

				entity->parsedForNLCcodeBlocks = true;			//added 4 October 2013 NLC1b6b  - used for quick access of instances already declared in current context
				generateObjectInitialisationsBasedOnSubstanceConceptsRecurse(entity, propertyEntity, currentCodeBlockInTree, sentenceIndex, generateInstanceName(definitionEntity), "");		//updated 9 November 2013 - support recursion of complex substance concept definition

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

					//cout << "condition initialisation:  entity->entityName = " << entity->entityName << endl;
					//for(all items in context){
					NLCitem * entityClass = new NLCitem(entity, NLC_ITEM_TYPE_CLASS);

					if(assumedToAlreadyHaveBeenDeclared(entity))
					{
						*currentCodeBlockInTree = createCodeBlockForPropertyListLocal(*currentCodeBlockInTree, entityClass);
					}
					else
					{
						NLCitem * parentConditionItem = new NLCitem(parentConditionName, NLC_ITEM_TYPE_CLASS);
						parentConditionItem->context.push_back(parentName);
						*currentCodeBlockInTree = createCodeBlockForConditionList(*currentCodeBlockInTree, parentConditionItem, entityClass);
					}

					*currentCodeBlockInTree = createCodeBlockAddNewCondition(*currentCodeBlockInTree, entity, conditionEntity, sentenceIndex);

					entity->parsedForNLCcodeBlocks = true;			//added 4 October 2013 NLC1b6b  - used for quick access of instances already declared in current context
					generateObjectInitialisationsBasedOnSubstanceConceptsRecurse(entity, conditionObject, currentCodeBlockInTree, sentenceIndex, generateInstanceName(definitionEntity), conditionEntity->entityName);	//updated 9 November 2013 - support recursion of complex substance concept definition

					*currentCodeBlockInTree = firstCodeBlockInSection->next;
				}

			}
		}
	#ifdef NLC_SUPPORT_CONDITION_LOGICAL_OPERATIONS_BASED_ON_CONCEPTS
	}
	#endif
}
#endif






