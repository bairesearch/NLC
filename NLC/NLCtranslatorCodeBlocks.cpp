/*******************************************************************************
 *
 * This file is part of BAIPROJECT.
 *
 * BAIPROJECT is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License version 3
 * only, as published by the Free Software Foundation.
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
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2013 Baxter AI (baxterai.com)
 * Project: Natural Language Programming Interface (compiler)
 * Project Version: 1f1b 09-December-2013
 * Requirements: requires text parsed by NLP Parser (eg Relex; available in .CFF format <relations>)
 *
 *******************************************************************************/



#include <ctime>
#include <cstdlib>	//for random number generation
#include <cmath>

#include "NLCtranslatorCodeBlocks.h"
#include "GIAquery.h"


bool generateCodeBlocks(NLCcodeblock * firstCodeBlockInTree, vector<GIAentityNode*> * entityNodesActiveListComplete, vector<GIAentityNode*> * entityNodesActiveListActions, int maxNumberSentences, string NLCfunctionName)
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
	
}

#ifdef NLC_SUPPORT_CONDITION_LOGICAL_OPERATIONS
bool generateCodeBlocksPart0(NLCcodeblock ** currentCodeBlockInTree, vector<GIAentityNode*> * entityNodesActiveListComplete, int sentenceIndex, string NLCfunctionName)
{
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{		
		GIAentityNode * conditionEntity = (*entityIter);
		if(conditionEntity->isCondition)
		{
			if(checkSentenceIndexParsingCodeBlocks(conditionEntity, sentenceIndex, true))	//could be set to false instead
			{
				bool foundConditionLogicalOperation = false;
				for(int i=0; i<NLC_CONDITION_LOGICAL_OPERATIONS_NUMBER_OF_TYPES; i++)
				{
					if(i == NLC_CONDITION_LOGICAL_OPERATIONS_IF)
					{//only "if" statements are currently supported by NLC
						if(conditionEntity->entityName == conditionLogicalOperationsArray[i])
						{
							foundConditionLogicalOperation = true;
						}
					}
				}
				if(foundConditionLogicalOperation)
				{
					GIAentityNode * conditionSubject = NULL;	
					GIAentityNode * conditionObject = NULL;
					bool foundConditionSubject = false;
					bool foundConditionObject = false;
					if(!(conditionEntity->conditionSubjectEntity->empty()))
					{
						conditionSubject = (conditionEntity->conditionSubjectEntity->back())->entity;
						foundConditionSubject = true;
					}
					if(!(conditionEntity->conditionObjectEntity->empty()))
					{
						conditionObject = (conditionEntity->conditionObjectEntity->back())->entity;
						foundConditionObject = true;
					}
					if(foundConditionSubject && foundConditionObject)
					{
						//1. disable all classStructure formation based on condition object subset

						bool passedConditionObject = false;
						if(conditionObject->isConcept || conditionObject->isSubstanceConcept)
						{//eg If red dogs are pies, eat the cabbage
							#ifdef NLC_SUPPORT_CONDITION_LOGICAL_OPERATIONS_BASED_ON_CONCEPTS
							//isSubstanceConcept case not yet coded
							//logical operations on concepts are performed by NLC (code is not generated for them by NLC as they are not performed at runtime) - eg If red dogs are pies, eat the cabbage.	[as opposed to: "if the red dog is the/a pie, eat the cabbage"] 
							//verify the truth of the if statement now (if the statement is false, disable all classStructure formation based on condition subject subset)
							if(conditionObject->isConcept)
							{
								cout << "generateCodeBlocks() error: NLC_SUPPORT_CONDITION_LOGICAL_OPERATIONS_BASED_ON_CONCEPTS only handles substance concepts. GIA_CREATE_SUBSTANCE_CONCEPTS_FOR_ALL_SENTENCES_WITH_CONCEPTS must be enabled.
								cout << "conditionObject = " << conditionObject->entityName;
							}
							else if(conditionObject->isSubstanceConcept)
							{
								GIAentityNode * substanceConceptEntityCompare = conditionObject;	//if statement comparison... 
								GIAentityNode * substanceConceptEntityCompareConcept = (substanceConceptEntityCompare->entityNodeDefiningThisInstance->back())->entity;

								conditionSubject->disabled = true;	//temporarily disable conditionSubject to prevent it from being parsed
								if(searchForEquivalentSubnetToIfStatement(substanceConceptEntityCompareConcept, conditionObject))
								{
									passedConditionObject = true;
								}
								conditionSubject->disabled = false;
							}
							#endif
						}
						else if(conditionObject->isAction || conditionObject->isActionConcept)
						{
							#ifdef NLC_SUPPORT_CONDITION_LOGICAL_OPERATIONS_BASED_ON_ACTIONS
							//verify the truth of the if statement now
							//NO: get class and see if it has the relevant action (function) defined with the relevant action object
							//perform an exact trace of conditionObject (actionEntityCompare) with every actionEntity that matches actionEntityCompare->entityName to verify that such a specific action already [ie sentence <= currentSentence] exists (actionEntityCompare) 

							GIAentityNode * actionEntityCompare = conditionObject;	//if statement comparison... 
							GIAentityNode * actionEntityCompareConcept = (actionEntityCompare->entityNodeDefiningThisInstance->back())->entity;

							conditionSubject->disabled = true;	//temporarily disable conditionSubject to prevent it from being parsed
							if(searchForEquivalentSubnetToIfStatement(actionEntityCompareConcept, conditionObject))
							{
								passedConditionObject = true;
							}
							conditionSubject->disabled = false;
							#endif		
						}
						else
						{//eg if the red dog is the/a pie, eat the cabbage
							cout << "q3a" << endl;
							//code copied from [*^]
							generateContextBlocksAndInitialiseParentIfNecessary(currentCodeBlockInTree, conditionObject, sentenceIndex);	//CHECKTHIS; AndInitialiseParentIfNecessary component
							tagAllEntitiesInSentenceSubsetAsPertainingToConditionLogicalOperation(conditionObject, sentenceIndex, false);	//used to enable class definition printing of conditional statements
							passedConditionObject = true;
							cout << "q3aEND" << endl;
						}

						if(passedConditionObject)
						{	
							if(conditionSubject->isConcept || conditionSubject->isSubstanceConcept)
							{
								#ifdef NLC_SUPPORT_CONDITION_LOGICAL_OPERATIONS_BASED_ON_CONCEPTS
								if(conditionSubject->isConcept)
								{
									cout << "generateCodeBlocks() error: NLC_SUPPORT_CONDITION_LOGICAL_OPERATIONS_BASED_ON_CONCEPTS only handles substance concepts. GIA_CREATE_SUBSTANCE_CONCEPTS_FOR_ALL_SENTENCES_WITH_CONCEPTS must be enabled.
									cout << "conditionSubject = " << conditionSubject->entityName;
								}
								else if(conditionSubject->isSubstanceConcept)
								{
									tagAllEntitiesInSentenceSubsetAsPertainingToConditionLogicalOperation(conditionSubject, sentenceIndex, false);
								}
								#endif
							}
							else if(conditionSubject->isAction)
							{
								generateActionCodeBlocks(currentCodeBlockInTree, conditionSubject, sentenceIndex, NLCfunctionName);
								
								tagAllEntitiesInSentenceSubsetAsPertainingToConditionLogicalOperation(conditionSubject, sentenceIndex, false);	//used to enable class definition printing of conditional statements
							}
							else
							{
								cout << "q3b" << endl;
								
								//code copied from [***^]

								GIAentityNode * parentEntity = getParent(conditionSubject, sentenceIndex);

								*currentCodeBlockInTree = createCodeBlocksCreateNewLocalListVariable(*currentCodeBlockInTree, parentEntity);
								parentEntity->parsedForNLCcodeBlocks = true;
								parentEntity->NLClocalListVariableHasBeenDeclared = true;
								//cout << "createCodeBlocksCreateNewLocalListVariable: " << parentEntity->entityName << endl;
								
								#ifdef GIA_TRANSLATOR_DREAM_MODE_LINK_SPECIFIC_CONCEPTS_AND_ACTIONS
								//Part 2b: generate object initialisations based on substance concepts (class inheritance)
								generateObjectInitialisationsBasedOnSubstanceConcepts(parentEntity, currentCodeBlockInTree, sentenceIndex);
								#endif

								generateObjectInitialisationsBasedOnPropertiesAndConditions(parentEntity, currentCodeBlockInTree, sentenceIndex, "", "");
								
								tagAllEntitiesInSentenceSubsetAsPertainingToConditionLogicalOperation(conditionSubject, sentenceIndex, false);	//used to enable class definition printing of conditional statements
							}
						}
					} 
				}
			}
		}
	}
}

bool searchForEquivalentSubnetToIfStatement(GIAentityNode * entityCompareConcept, GIAentityNode * entity)
{
	bool result = false;
	
	//code copied from [*****^] (identifyComparisonVariableAlternateMethod.cpp)

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
					for(int i=0; i<NLC_CONDITION_LOGICAL_OPERATIONS_NUMBER_OF_TYPES; i++)
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
									cout << "tagged: " << connectedEntity->entityName << endl;
									connection->NLCconditionLogicalOperations = true;
									connectedEntity->NLCconditionLogicalOperations = true;
								}
								else
								{
									cout << "untagged: " << connectedEntity->entityName << endl;
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
}

void generateActionCodeBlocks(NLCcodeblock ** currentCodeBlockInTree, GIAentityNode * actionEntity, int sentenceIndex, string NLCfunctionName)
{
	#ifdef NLC_DEBUG
	cout << "actionEntity->entityName = " << actionEntity->entityName << endl;
	#endif
	//cout << "sentenceIndexC = " << sentenceIndex << endl;
	//cout << "h1" << endl;

	bool actionHasObject = false;
	GIAentityNode * objectEntity = NULL;
	if(!(actionEntity->actionObjectEntity->empty()))
	{
		actionHasObject = true;
		objectEntity = (actionEntity->actionObjectEntity->back())->entity;
	}
	//cout << "h1b" << endl;
	bool actionHasSubject = false;
	GIAentityNode * subjectEntity = NULL;
	if(!(actionEntity->actionSubjectEntity->empty()))
	{
		actionHasSubject = true;
		subjectEntity = (actionEntity->actionSubjectEntity->back())->entity;
	}

	//cout << "h2" << endl;


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

		if(actionHasSubject)
		{
			//[*^]
			cout << "executing generateContextBlocksAndInitialiseParentIfNecessary subjectEntity" << endl;
			generateContextBlocksAndInitialiseParentIfNecessary(currentCodeBlockInTree, subjectEntity, sentenceIndex);
		}
		if(actionHasObject)
		{
			generateContextBlocksAndInitialiseParentIfNecessary(currentCodeBlockInTree, objectEntity, sentenceIndex);
		}					
	}


	if(actionHasObject)
	{
		bool objectRequiredTempVar = false;	//not used
		NLCitem * objectItem = NULL;
		*currentCodeBlockInTree = generateConditionBlocks(*currentCodeBlockInTree, objectEntity, &objectItem, sentenceIndex, &objectRequiredTempVar, NLC_ITEM_TYPE_FUNCTION_OBJECT);

		//cout << "h3" << endl;
		if(actionHasSubject)
		{
			bool subjectRequiredTempVar = false;
			NLCitem * subjectItem = NULL;
			*currentCodeBlockInTree = generateConditionBlocks(*currentCodeBlockInTree, subjectEntity, &subjectItem, sentenceIndex, &subjectRequiredTempVar, NLC_ITEM_TYPE_FUNCTION_OWNER);
			//cout << "h4" << endl;
			if(subjectRequiredTempVar)
			{	
				//cout << "subjectRequiredTempVar" << endl;						
				functionItem->context.push_back(subjectItem->instanceName);

				#ifdef NLC_NOT_NECESSARY
				//required just for implictlyDeclaredFunctionList...;
				NLCitem * functionItemFullContextForRecordOnly = new NLCitem(actionEntity, NLC_ITEM_TYPE_FUNCTION); 
				getEntityContext(subjectEntity, &(functionItemFullContextForRecordOnly->context), true, sentenceIndex, true);
				implictlyDeclaredFunctionList.push_back(functionItemFullContextForRecordOnly);
				#endif
			}
			else
			{
				getEntityContext(subjectEntity, &(functionItem->context), true, sentenceIndex, true);
				#ifdef NLC_NOT_NECESSARY
				implictlyDeclaredFunctionList.push_back(functionItem);
				#endif
			}

			//subjectEntity->parsedForNLCcodeBlocksActionRound = true;
		}
		#ifdef NLC_NOT_NECESSARY
		else
		{
			implictlyDeclaredFunctionListTopLevel.push_back(functionItem);					
		}
		#endif
		//cout << "h5" << endl;
		functionExecuteCodeBlockInTree = *currentCodeBlockInTree;
		*currentCodeBlockInTree = createCodeBlockExecute(*currentCodeBlockInTree, functionItem, objectItem);

		actionEntity->parsedForNLCcodeBlocks = true;
		//actionEntity->parsedForNLCcodeBlocksActionRound = true;
		//objectEntity->parsedForNLCcodeBlocksActionRound = true;
	}
	else if(actionHasSubject)
	{
		//[**^]
		bool subjectRequiredTempVar = false;	//not used
		NLCitem * subjectItem = NULL;
		*currentCodeBlockInTree = generateConditionBlocks(*currentCodeBlockInTree, subjectEntity, &subjectItem, sentenceIndex, &subjectRequiredTempVar, NLC_ITEM_TYPE_FUNCTION_OWNER);

		//cout << "h3" << endl;
		if(subjectRequiredTempVar)
		{	
			//cout << "subjectRequiredTempVar" << endl;						
			functionItem->context.push_back(subjectItem->instanceName);
		}
		else
		{
			getEntityContext(subjectEntity, &(functionItem->context), true, sentenceIndex, true);
		}
		//cout << "h5" << endl;
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
			//string actionProperty = *localListIter2;
			GIAentityNode * actionProperty = (*entityIter)->entity;
			(*entityIter)->parsedForNLCcodeBlocks = true;
			actionProperty->parsedForNLCcodeBlocks = true;
		}
	}
	#endif


	//cout << "h6" << endl;
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
	/*OLD:
	currentCodeBlockInTree->parameters.push_back(functionItem);
	currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, NLC_CODEBLOCK_TYPE_DECLARE_NEW_VARIABLE);	
	*/
	generateObjectInitialisationsBasedOnPropertiesAndConditions(actionEntity, currentCodeBlockInTree, sentenceIndex, "", "");
	generateObjectInitialisationsBasedOnSubstanceConcepts(actionEntity, currentCodeBlockInTree, sentenceIndex);
}
#endif

//added 1e6a
bool generateContextBlocksAndInitialiseParentIfNecessary(NLCcodeblock ** currentCodeBlockInTree, GIAentityNode * currentEntity, int sentenceIndex)
{
	bool result = false;
	bool possibleContextParentFound = false;

	//cout << "generateContextBlocksAndInitialiseParentIfNecessary: currentEntity = " << currentEntity->entityName << endl;
	if(checkSentenceIndexParsingCodeBlocks(currentEntity, sentenceIndex, false) || currentEntity->parsedForNLCcodeBlocks || assumedToAlreadyHaveBeenDeclared(currentEntity))
	{
		//cout << "a1" << endl;
		if(!(currentEntity->propertyNodeReverseList->empty()))
		{
			//cout << "a2" << endl;
			GIAentityNode * parentEntity = (currentEntity->propertyNodeReverseList->back())->entity;
			if(checkSentenceIndexParsingCodeBlocks(parentEntity, sentenceIndex, false) || parentEntity->parsedForNLCcodeBlocks || assumedToAlreadyHaveBeenDeclared(parentEntity))
			{
				//cout << "a3" << endl;
				if(generateContextBlocksAndInitialiseParentIfNecessary(currentCodeBlockInTree, parentEntity, sentenceIndex))
				{
					//cout << "\tpassed: " << currentEntity->entityName << endl;
					
					result = true;
					NLCitem * propertyItem = new NLCitem(currentEntity, NLC_ITEM_TYPE_CLASS);
					if(assumedToAlreadyHaveBeenDeclared(currentEntity))
					{
						*currentCodeBlockInTree = createCodeBlockForPropertyListLocal(*currentCodeBlockInTree, propertyItem);
					}
					else
					{
						propertyItem->context.push_back(generateInstanceName(parentEntity));
						*currentCodeBlockInTree = createCodeBlockForPropertyList(*currentCodeBlockInTree, propertyItem);
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
						parentEntity->parsedForNLCcodeBlocks = true;
					}
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
			//cout << "\tpossibleContextParentFound: " << currentEntity->entityName << endl;
			
			result = true;
			#ifdef NLC_CREATE_IMPLICITLY_DECLARED_ACTION_OBJECT_AND_SUBJECT_VARIABLES
			if(!assumedToAlreadyHaveBeenDeclared(currentEntity))
			{
				if(!(currentEntity->parsedForNLCcodeBlocks))
				{				
					//cout << "createCodeBlocksCreateNewLocalListVariable: " << currentEntity->entityName << endl;
					*currentCodeBlockInTree = createCodeBlocksCreateNewLocalListVariable(*currentCodeBlockInTree, currentEntity);
					currentEntity->parsedForNLCcodeBlocks = true;
					currentEntity->NLClocalListVariableHasBeenDeclared = true;
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
			if(assumedToAlreadyHaveBeenDeclared(currentEntity))
			{
				*currentCodeBlockInTree = createCodeBlockForPropertyListLocal(*currentCodeBlockInTree, propertyItem);
			}
			else
			{
				*currentCodeBlockInTree = createCodeBlockForPropertyList(*currentCodeBlockInTree, propertyItem);
			}
		}
	}

	return result;
}	

NLCcodeblock * generateConditionBlocks(NLCcodeblock * currentCodeBlockInTree, GIAentityNode * entity, NLCitem ** item, int sentenceIndex, bool * requiredTempVar, int itemType)
{

	bool entityHasParent = false;
			
	//cout << "itemType = " << itemType << endl;
	
	*requiredTempVar = true;

	*item = new NLCitem(entity, itemType);	//OLD: NLC_ITEM_TYPE_TEMPVAR

	currentCodeBlockInTree = createCodeBlockForStatements(currentCodeBlockInTree, *item, entity, sentenceIndex);

	return currentCodeBlockInTree;
}


				
bool generateCodeBlocksPart2(NLCcodeblock ** currentCodeBlockInTree, vector<GIAentityNode*> * entityNodesActiveListComplete, int sentenceIndex, string NLCfunctionName)
{
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{			
		GIAentityNode * entity = *entityIter;
		if(checkSentenceIndexParsingCodeBlocks(entity, sentenceIndex, false))
		{	
			//[***^]
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
										//cout << "createCodeBlocksCreateNewLocalListVariable: " << parentEntity->entityName << endl;
										*currentCodeBlockInTree = createCodeBlocksCreateNewLocalListVariable(*currentCodeBlockInTree, parentEntity);
										parentEntity->parsedForNLCcodeBlocks = true;
										parentEntity->NLClocalListVariableHasBeenDeclared = true;
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
			generateObjectInitialisationsBasedOnPropertiesAndConditions(parentEntity, currentCodeBlockInTree, sentenceIndex, "", "");
		}
	}
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
						//   bool entityHasParent = getEntityContext(propertyEntity, &(propertyClass->context), false, sentenceIndex, true);	//removed 1e6b
						*currentCodeBlockInTree = createCodeBlockForPropertyListLocal(*currentCodeBlockInTree, propertyClass);

						*currentCodeBlockInTree = createCodeBlockAddProperty(*currentCodeBlockInTree, entity, propertyEntity, sentenceIndex);	
						//cout << "createCodeBlockAddProperty: " << entity->entityName << ", " << propertyEntity->entityName << endl;
						
						*currentCodeBlockInTree = firstCodeBlockInSection2->next;
					}
					else
					{
					#endif
						//create a new property; eg "a ball" in "Tom has a ball"

						//cout << "sentenceIndexA = " << sentenceIndex << endl;
						*currentCodeBlockInTree = createCodeBlockAddNewProperty(*currentCodeBlockInTree, entity, propertyEntity, sentenceIndex);
						//cout << "createCodeBlockAddNewProperty: " << entity->entityName << ", " << propertyEntity->entityName << endl;
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
		//state initialisations
		for(vector<GIAentityConnection*>::iterator conditionNodeListIterator = entity->conditionNodeList->begin(); conditionNodeListIterator < entity->conditionNodeList->end(); conditionNodeListIterator++)
		{
			GIAentityConnection * conditionConnection = (*conditionNodeListIterator);	
			GIAentityNode* conditionEntity = conditionConnection->entity;
		
			#ifdef NLC_SUPPORT_CONDITION_LOGICAL_OPERATIONS
			bool foundConditionLogicalOperation = false;
			for(int i=0; i<NLC_CONDITION_LOGICAL_OPERATIONS_NUMBER_OF_TYPES; i++)
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
							cout << "\th1" << endl;
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
							cout << "\th2" << endl;
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
							//cout << "!(conditionConnection->parsedForNLCcodeBlocks): " << conditionObject->entityName << endl;

							#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS		
							if(assumedToAlreadyHaveBeenDeclared(conditionObject))
							{
								NLCcodeblock * firstCodeBlockInSection2 = *currentCodeBlockInTree;

								//use function argument PropertyList (do not create a new property to insert into condition); eg "the house" in "Tom is near a house"
								//cout << "conditionObject->entityName = " << conditionObject->entityName << endl;
								//for(all items in context){

								//bool entityHasParent = getEntityContext(conditionObject, &(conditionObjectClass->context), false, sentenceIndex, true);	//removed 1e6b
								*currentCodeBlockInTree = createCodeBlockForPropertyListLocal(*currentCodeBlockInTree, conditionObjectClass);

								*currentCodeBlockInTree = createCodeBlockAddCondition(*currentCodeBlockInTree, entity, conditionEntity, sentenceIndex);

								*currentCodeBlockInTree = firstCodeBlockInSection2->next;
							}
							else
							{
							#endif
								//create a new condition; eg "a house" in "Tom is near a house"
								*currentCodeBlockInTree = createCodeBlockAddNewCondition(*currentCodeBlockInTree, entity, conditionEntity, sentenceIndex);
							#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS
							}
							#endif

							//cout << "sentenceIndexB = " << sentenceIndex << endl;
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

				//cout << "entity->entityName = " << entity->entityName << endl;
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

				//cout << "sentenceIndexA = " << sentenceIndex << endl;
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

					//cout << "entity->entityName = " << entity->entityName << endl;
					//for(all items in context){
					NLCitem * entityClass = new NLCitem(entity, NLC_ITEM_TYPE_CLASS);

					if(assumedToAlreadyHaveBeenDeclared(entity))
					{
						*currentCodeBlockInTree = createCodeBlockForPropertyListLocal(*currentCodeBlockInTree, entityClass);			
					}
					else
					{
						//bool entityHasParent = getEntityContext(entity, &(entityClass->context), false, sentenceIndex, true);
						NLCitem * parentConditionItem = new NLCitem(parentConditionName, NLC_ITEM_TYPE_CLASS);
						parentConditionItem->context.push_back(parentName);
						*currentCodeBlockInTree = createCodeBlockForConditionList(*currentCodeBlockInTree, parentConditionItem, entityClass);
					}			

					//cout << "sentenceIndexB = " << sentenceIndex << endl;
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






