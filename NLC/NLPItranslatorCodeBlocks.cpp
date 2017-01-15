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
 * File Name: NLPItranslatorCodeBlocks.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2013 Baxter AI (baxterai.com)
 * Project: Natural Language Programming Interface (compiler)
 * Project Version: 1e9d 25-November-2013
 * Requirements: requires text parsed by NLP Parser (eg Relex; available in .CFF format <relations>)
 *
 *******************************************************************************/



#include <ctime>
#include <cstdlib>	//for random number generation
#include <cmath>

#include "NLPItranslatorCodeBlocks.h"


bool generateCodeBlocks(NLPIcodeblock * firstCodeBlockInTree, vector<GIAentityNode*> * entityNodesActiveListComplete, vector<GIAentityNode*> * entityNodesActiveListActions, int maxNumberSentences, string NLPIfunctionName)
{
	NLPIcodeblock * currentCodeBlockInTree = firstCodeBlockInTree;
	
	#ifdef NLPI_NOT_NECESSARY
	vector<NLPIitem *> implictlyDeclaredFunctionList;	//implictlyDeclaredFunctionList is used to capture implicitly declared functions; to be added to object class definitions at end
	vector<NLPIitem *> implictlyDeclaredFunctionListTopLevel;	//top level function list (used to store implicitly declared functions without subject/context/owner)	
	#endif
	
	currentCodeBlockInTree = createCodeBlockNewFunction(currentCodeBlockInTree, NLPIfunctionName, entityNodesActiveListComplete);

	//NLPIcodeblock * nextCodeBlockInTree = NULL;	//not used now; assume only 1 command in text
	//for each action (command) in sentence;
	
	//cout << "maxNumberSentences = " << maxNumberSentences << endl;
	for(int sentenceIndex=1; sentenceIndex <= maxNumberSentences; sentenceIndex++)
	{	
		NLPIcodeblock * firstCodeBlockInSentence = currentCodeBlockInTree;
			
		//method1;
		for(vector<GIAentityNode*>::iterator entityNodesActiveListActionsIterator = entityNodesActiveListActions->begin(); entityNodesActiveListActionsIterator < entityNodesActiveListActions->end(); entityNodesActiveListActionsIterator++)
		{		
			GIAentityNode * actionEntity = (*entityNodesActiveListActionsIterator);
			if(!(actionEntity->isActionConcept))
			{
				//cout << "actionEntity->isAction = " << actionEntity->isAction << endl;
				//cout << "actionEntity->hasAssociatedInstance = " << actionEntity->hasAssociatedInstance << endl;

				if(checkSentenceIndexParsingCodeBlocks(actionEntity, sentenceIndex, true))
				{
					#ifdef NLPI_DEBUG
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


					NLPIcodeblock * functionExecuteCodeBlockInTree = NULL;
			
					NLPIitem * functionItem = NULL;
					if(actionHasObject || actionHasSubject)
					{
						functionItem = new NLPIitem(actionEntity, NLPI_ITEM_TYPE_FUNCTION);
						
						#ifdef NLPI_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS
						//cout << "NLPI_CODEBLOCK_TYPE_DECLARE_NEW_VARIABLE" << endl;
						actionEntity->NLPIisSingularArgument = true;	//added 1e2c
						//declare an "abstract" variable for the action (that will be filled with the its properties and conditions) and passed as an argument to the function; eg "fast" of "run fast"
						//cout << "functionItem->instanceName = " << functionItem->instanceName << endl;
						//cout << "functionItem->className = " << functionItem->className << endl;
						currentCodeBlockInTree->parameters.push_back(functionItem);
						currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, NLPI_CODEBLOCK_TYPE_DECLARE_NEW_VARIABLE);	
						generateObjectInitialisationsBasedOnPropertiesAndConditions(actionEntity, &currentCodeBlockInTree, sentenceIndex, "", "");
						generateObjectInitialisationsBasedOnSubstanceConcepts(actionEntity, &currentCodeBlockInTree, sentenceIndex);
						firstCodeBlockInSentence = currentCodeBlockInTree;	
						#endif
						
						if(actionHasSubject)
						{
							generateContextBlocksAndInitialiseParentIfNecessary(&currentCodeBlockInTree, subjectEntity, sentenceIndex);
						}
						if(actionHasObject)
						{
							generateContextBlocksAndInitialiseParentIfNecessary(&currentCodeBlockInTree, objectEntity, sentenceIndex);
						}					
					}
					
					
					if(actionHasObject)
					{
						bool objectRequiredTempVar = false;	//not used
						NLPIitem * objectItem = NULL;
						currentCodeBlockInTree = generateConditionBlocks(currentCodeBlockInTree, objectEntity, &objectItem, sentenceIndex, &objectRequiredTempVar, NLPI_ITEM_TYPE_FUNCTION_OBJECT);

						//cout << "h3" << endl;
						if(actionHasSubject)
						{
							bool subjectRequiredTempVar = false;
							NLPIitem * subjectItem = NULL;
							currentCodeBlockInTree = generateConditionBlocks(currentCodeBlockInTree, subjectEntity, &subjectItem, sentenceIndex, &subjectRequiredTempVar, NLPI_ITEM_TYPE_FUNCTION_OWNER);
							//cout << "h4" << endl;
							if(subjectRequiredTempVar)
							{	
								//cout << "subjectRequiredTempVar" << endl;						
								functionItem->context.push_back(subjectItem->instanceName);

								#ifdef NLPI_NOT_NECESSARY
								//required just for implictlyDeclaredFunctionList...;
								NLPIitem * functionItemFullContextForRecordOnly = new NLPIitem(actionEntity, NLPI_ITEM_TYPE_FUNCTION); 
								getEntityContext(subjectEntity, &(functionItemFullContextForRecordOnly->context), true, sentenceIndex, true);
								implictlyDeclaredFunctionList.push_back(functionItemFullContextForRecordOnly);
								#endif
							}
							else
							{
								getEntityContext(subjectEntity, &(functionItem->context), true, sentenceIndex, true);
								#ifdef NLPI_NOT_NECESSARY
								implictlyDeclaredFunctionList.push_back(functionItem);
								#endif
							}
							
							//subjectEntity->parsedForNLPIcodeBlocksActionRound = true;
						}
						#ifdef NLPI_NOT_NECESSARY
						else
						{
							implictlyDeclaredFunctionListTopLevel.push_back(functionItem);					
						}
						#endif
						//cout << "h5" << endl;
						functionExecuteCodeBlockInTree = currentCodeBlockInTree;
						currentCodeBlockInTree = createCodeBlockExecute(currentCodeBlockInTree, functionItem, objectItem);
						
						actionEntity->parsedForNLPIcodeBlocks = true;
						//actionEntity->parsedForNLPIcodeBlocksActionRound = true;
						//objectEntity->parsedForNLPIcodeBlocksActionRound = true;
					}
					else if(actionHasSubject)
					{
						bool subjectRequiredTempVar = false;	//not used
						NLPIitem * subjectItem = NULL;
						currentCodeBlockInTree = generateConditionBlocks(currentCodeBlockInTree, subjectEntity, &subjectItem, sentenceIndex, &subjectRequiredTempVar, NLPI_ITEM_TYPE_FUNCTION_OWNER);

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
						functionExecuteCodeBlockInTree = currentCodeBlockInTree;
						currentCodeBlockInTree = createCodeBlockExecute(currentCodeBlockInTree, functionItem);
						
						actionEntity->parsedForNLPIcodeBlocks = true;
						//actionEntity->parsedForNLPIcodeBlocksActionRound = true;
						//subjectEntity->parsedForNLPIcodeBlocksActionRound = true;
					}	

					#ifdef NLPI_INTERPRET_ACTION_PROPERTIES_AND_CONDITIONS_AS_FUNCTION_ARGUMENTS
					if(actionHasObject || actionHasSubject)
					{											
						#ifndef NLPI_SUPPORT_INPUT_FILE_LISTS
						generateFunctionPropertyConditionArgumentsWithActionConceptInheritance(actionEntity, &(functionExecuteCodeBlockInTree->parameters));	//#ifdef NLPI_SUPPORT_INPUT_FILE_LISTS use class definition parameters instead
						#endif
						
						//detect action properties and conditions (and disable these for NLPI generate code block parse: they will become function execution arguments)
						for(vector<GIAentityConnection*>::iterator entityIter = actionEntity->conditionNodeList->begin(); entityIter != actionEntity->conditionNodeList->end(); entityIter++)
						{					
							GIAentityNode * actionCondition = (*entityIter)->entity;
							(*entityIter)->parsedForNLPIcodeBlocks = true;
							actionCondition->parsedForNLPIcodeBlocks = true;
						}
						for(vector<GIAentityConnection*>::iterator entityIter = actionEntity->propertyNodeList->begin(); entityIter != actionEntity->propertyNodeList->end(); entityIter++)				
						{
							//string actionProperty = *localListIter2;
							GIAentityNode * actionProperty = (*entityIter)->entity;
							(*entityIter)->parsedForNLPIcodeBlocks = true;
							actionProperty->parsedForNLPIcodeBlocks = true;
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
			}
			
			currentCodeBlockInTree = firstCodeBlockInSentence;
			while(currentCodeBlockInTree->next != NULL)
			{
				currentCodeBlockInTree = currentCodeBlockInTree->next;
			}
		}
		
		//cout << "q1" << endl;
	
	
		//Part 2: generate object initialisations (eg Tom has a boat) [without actions]
		//cout << "*** sentenceIndex = " << sentenceIndex << endl;
		for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
		{			
			GIAentityNode * entity = *entityIter;
			if(checkSentenceIndexParsingCodeBlocks(entity, sentenceIndex, false))
			{	
				GIAentityNode * parentEntity = getParent(entity, sentenceIndex);
				
				#ifdef NLPI_CREATE_IMPLICITLY_DECLARED_ACTION_OBJECT_AND_SUBJECT_VARIABLES
				//moved here 1e8a (out of generateObjectInitialisationsBasedOnPropertiesAndConditions)
				//added 1e6c: eg A chicken's hat has a bike. / A blue dog has a bike.
				if(!(parentEntity->isConcept))
				{
					if(!(parentEntity->parsedForNLPIcodeBlocks))	// && !(entity->parsedForNLPIcodeBlocksActionRound)
					{
						if(!assumedToAlreadyHaveBeenDeclared(parentEntity))	
						{
							if(!(parentEntity->isAction))	//added 1e6d
							{
								if(checkSentenceIndexParsingCodeBlocks(parentEntity, sentenceIndex, false))
								{
									if(!(parentEntity->isCondition))
									{
										//cout << "createCodeBlocksCreateNewLocalListVariable: " << parentEntity->entityName << endl;
										currentCodeBlockInTree = createCodeBlocksCreateNewLocalListVariable(currentCodeBlockInTree, parentEntity);
										parentEntity->parsedForNLPIcodeBlocks = true;
										parentEntity->NLPIlocalListVariableHasBeenDeclared = true;
										//cout << "createCodeBlocksCreateNewLocalListVariable: " << parentEntity->entityName << endl;

										#ifdef GIA_TRANSLATOR_DREAM_MODE_LINK_SPECIFIC_CONCEPTS_AND_ACTIONS
										//Part 2b: generate object initialisations based on substance concepts (class inheritance)
										generateObjectInitialisationsBasedOnSubstanceConcepts(parentEntity, &currentCodeBlockInTree, sentenceIndex);
										#endif
									}
								}
							}
						}
					}
				}
				#endif
				generateObjectInitialisationsBasedOnPropertiesAndConditions(parentEntity, &currentCodeBlockInTree, sentenceIndex, "", "");
			}
		}	
		//cout << "q2" << endl;
	}
	
}

//added 1e6a
bool generateContextBlocksAndInitialiseParentIfNecessary(NLPIcodeblock ** currentCodeBlockInTree, GIAentityNode * currentEntity, int sentenceIndex)
{
	bool result = false;
	bool possibleContextParentFound = false;

	if(checkSentenceIndexParsingCodeBlocks(currentEntity, sentenceIndex, false) || currentEntity->parsedForNLPIcodeBlocks)
	{
		if(!(currentEntity->propertyNodeReverseList->empty()))
		{
			GIAentityNode * parentEntity = (currentEntity->propertyNodeReverseList->back())->entity;
			if(checkSentenceIndexParsingCodeBlocks(parentEntity, sentenceIndex, false) || parentEntity->parsedForNLPIcodeBlocks)
			{
				if(generateContextBlocksAndInitialiseParentIfNecessary(currentCodeBlockInTree, parentEntity, sentenceIndex))
				{
					result = true;
					NLPIitem * propertyItem = new NLPIitem(currentEntity, NLPI_ITEM_TYPE_CLASS);
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
								propertyConnection->parsedForNLPIcodeBlocks = true;
							}
						}
						parentEntity->parsedForNLPIcodeBlocks = true;
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
			result = true;
			#ifdef NLPI_CREATE_IMPLICITLY_DECLARED_ACTION_OBJECT_AND_SUBJECT_VARIABLES
			if(!assumedToAlreadyHaveBeenDeclared(currentEntity))
			{
				if(!(currentEntity->parsedForNLPIcodeBlocks))
				{				
					//cout << "createCodeBlocksCreateNewLocalListVariable: " << currentEntity->entityName << endl;
					*currentCodeBlockInTree = createCodeBlocksCreateNewLocalListVariable(*currentCodeBlockInTree, currentEntity);
					currentEntity->parsedForNLPIcodeBlocks = true;
					currentEntity->NLPIlocalListVariableHasBeenDeclared = true;
					//NLPIcodeblock firstCodeBlockInSection = *currentCodeBlockInTree;
					generateObjectInitialisationsBasedOnPropertiesAndConditions(currentEntity, currentCodeBlockInTree, sentenceIndex, "", "");

					#ifdef GIA_TRANSLATOR_DREAM_MODE_LINK_SPECIFIC_CONCEPTS_AND_ACTIONS
					//Part 2b: generate object initialisations based on substance concepts (class inheritance)
					generateObjectInitialisationsBasedOnSubstanceConcepts(currentEntity, currentCodeBlockInTree, sentenceIndex);
					#endif
				}
			}
			#endif		
			NLPIitem * propertyItem = new NLPIitem(currentEntity, NLPI_ITEM_TYPE_CLASS);
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
			


NLPIcodeblock * generateConditionBlocks(NLPIcodeblock * currentCodeBlockInTree, GIAentityNode * entity, NLPIitem ** item, int sentenceIndex, bool * requiredTempVar, int itemType)
{

	bool entityHasParent = false;
			
	//cout << "itemType = " << itemType << endl;
	
	*requiredTempVar = true;

	*item = new NLPIitem(entity, itemType);	//OLD: NLPI_ITEM_TYPE_TEMPVAR

	currentCodeBlockInTree = createCodeBlockForStatements(currentCodeBlockInTree, *item, entity, sentenceIndex);

	return currentCodeBlockInTree;
}

GIAentityNode * getParent(GIAentityNode * currentEntity, int sentenceIndex)
{
	if(!(currentEntity->propertyNodeReverseList->empty()))
	{
		GIAentityNode * parentEntity = (currentEntity->propertyNodeReverseList->back())->entity;
		
		if(checkSentenceIndexParsingCodeBlocks(parentEntity, sentenceIndex, false) || parentEntity->parsedForNLPIcodeBlocks)
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
			
			if(checkSentenceIndexParsingCodeBlocks(conditionSubject, sentenceIndex, false) || conditionSubject->parsedForNLPIcodeBlocks)
			{
				currentEntity = getParent(conditionSubject, sentenceIndex);
			}	
		}
	}

	return currentEntity;
}	
		
		
//added recursion 1e8a
bool generateObjectInitialisationsBasedOnPropertiesAndConditions(GIAentityNode * entity, NLPIcodeblock ** currentCodeBlockInTree, int sentenceIndex, string parentName, string parentConditionName)
{
	bool performedAtLeastOneObjectInitialisation = false;
	if(!(entity->isSubstanceConcept) && !(entity->isActionConcept))
	{
		//property initialisations
		for(vector<GIAentityConnection*>::iterator propertyNodeListIterator = entity->propertyNodeList->begin(); propertyNodeListIterator < entity->propertyNodeList->end(); propertyNodeListIterator++)
		{
			GIAentityConnection * propertyConnection = (*propertyNodeListIterator);			
			GIAentityNode* propertyEntity = propertyConnection->entity;

			if(checkSentenceIndexParsingCodeBlocks(propertyEntity, sentenceIndex, false) || propertyEntity->parsedForNLPIcodeBlocks)
			{//only write properties that are explicated in current sentence

				bool performedAtLeastOneObjectInitialisationAtThisLevel = false;
				NLPIcodeblock * firstCodeBlockInSection = *currentCodeBlockInTree;

				//cout << "entity->entityName = " << entity->entityName << endl;
				//for(all items in context){
				NLPIitem * entityClass = new NLPIitem(entity, NLPI_ITEM_TYPE_CLASS);
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

				if(!(propertyConnection->parsedForNLPIcodeBlocks) && !(propertyEntity->parsedForNLPIcodeBlocks))
				{
					#ifdef NLPI_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS
					if(assumedToAlreadyHaveBeenDeclared(propertyEntity))
					{
						//use function argument PropertyList (do not create a new property); eg "the ball" in "Tom has the ball"
						//cout << "propertyEntity->entityName = " << propertyEntity->entityName << endl;
						//for(all items in context){
						
						NLPIcodeblock * firstCodeBlockInSection2 = *currentCodeBlockInTree;
						
						NLPIitem * propertyClass = new NLPIitem(propertyEntity, NLPI_ITEM_TYPE_CLASS);
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
					#ifdef NLPI_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS
					}
					#endif

					/*
					cout << "generateObjectInitialisationsBasedOnPropertiesAndConditions():" << endl;		
					cout << "entity->entityName = " << entity->entityName << endl;
					cout << "propertyEntity->entityName = " << propertyEntity->entityName << endl;
					*/

					propertyConnection->parsedForNLPIcodeBlocks = true;
					propertyEntity->parsedForNLPIcodeBlocks = true;		//added 3 October 2013 NLPI1b2b - used for quick access of instances already declared in current context 

					//moved 1e1b: only generate object initialisations for items based on subject concepts when items are created in context
					#ifdef GIA_TRANSLATOR_DREAM_MODE_LINK_SPECIFIC_CONCEPTS_AND_ACTIONS
					//Part 2b: generate object initialisations based on substance concepts (class inheritance)
					generateObjectInitialisationsBasedOnSubstanceConcepts(propertyEntity, currentCodeBlockInTree, sentenceIndex);
					#endif
					
					performedAtLeastOneObjectInitialisationAtThisLevel = true;
				}	

				NLPIcodeblock * firstCodeBlockBeforeRecursion = *currentCodeBlockInTree;
				bool performedAtLeastOneObjectInitialisationAtALowerLevel = generateObjectInitialisationsBasedOnPropertiesAndConditions(propertyEntity, currentCodeBlockInTree, sentenceIndex, generateInstanceName(entity), "");
				
				generateObjectInitialisationsBasedOnPropertiesAndConditionsUpdateCodeBlockPointer(currentCodeBlockInTree, firstCodeBlockBeforeRecursion, firstCodeBlockInSection, performedAtLeastOneObjectInitialisationAtThisLevel, performedAtLeastOneObjectInitialisationAtALowerLevel, &performedAtLeastOneObjectInitialisation);
			}
		}
		//state initialisations
		for(vector<GIAentityConnection*>::iterator conditionNodeListIterator = entity->conditionNodeList->begin(); conditionNodeListIterator < entity->conditionNodeList->end(); conditionNodeListIterator++)
		{
			GIAentityConnection * conditionConnection = (*conditionNodeListIterator);	
			GIAentityNode* conditionEntity = conditionConnection->entity;
			bool foundConditionObject = false;
			GIAentityNode * conditionObject = NULL;
			if(!(conditionEntity->conditionObjectEntity->empty()))
			{
				conditionObject = (conditionEntity->conditionObjectEntity->back())->entity;
				foundConditionObject = true;

				if(checkSentenceIndexParsingCodeBlocks(conditionEntity,  sentenceIndex, false) || conditionEntity->parsedForNLPIcodeBlocks)
				{//only write conditions that are explicated in current sentence	

					bool performedAtLeastOneObjectInitialisationAtThisLevel = false;
					NLPIcodeblock * firstCodeBlockInSection = *currentCodeBlockInTree;

					//cout << "entity->entityName = " << entity->entityName << endl; 
					//for(all items in context){
					NLPIitem * entityClass = new NLPIitem(entity, NLPI_ITEM_TYPE_CLASS);
					NLPIitem * conditionObjectClass = new NLPIitem(conditionObject, NLPI_ITEM_TYPE_CLASS);
					
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
						NLPIitem * parentConditionItem = new NLPIitem(parentConditionName, NLPI_ITEM_TYPE_CLASS);
						parentConditionItem->context.push_back(parentName);
						*currentCodeBlockInTree = createCodeBlockForConditionList(*currentCodeBlockInTree, parentConditionItem, entityClass);	
					}

					if(!(conditionConnection->parsedForNLPIcodeBlocks) && !(conditionEntity->parsedForNLPIcodeBlocks))
					{
						//cout << "!(conditionConnection->parsedForNLPIcodeBlocks): " << conditionObject->entityName << endl;
						
						#ifdef NLPI_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS		
						if(assumedToAlreadyHaveBeenDeclared(conditionObject))
						{
							NLPIcodeblock * firstCodeBlockInSection2 = *currentCodeBlockInTree;
							
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
						#ifdef NLPI_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS
						}
						#endif

						//cout << "sentenceIndexB = " << sentenceIndex << endl;
						conditionConnection->parsedForNLPIcodeBlocks = true;
						conditionEntity->parsedForNLPIcodeBlocks = true;	//added 3 October 2013 NLPI1b2b - used for quick access of instances already declared in current context 
						conditionObject->parsedForNLPIcodeBlocks = true;	//added 1e6d

						//moved 1e1b: only generate object initialisations for items based on subject concepts when items are created in context
						#ifdef GIA_TRANSLATOR_DREAM_MODE_LINK_SPECIFIC_CONCEPTS_AND_ACTIONS
						//Part 2b: generate object initialisations based on substance concepts (class inheritance)
						generateObjectInitialisationsBasedOnSubstanceConcepts(conditionEntity, currentCodeBlockInTree, sentenceIndex);
						#endif

						performedAtLeastOneObjectInitialisationAtThisLevel = true;	
					}
					

					NLPIcodeblock * firstCodeBlockBeforeRecursion = *currentCodeBlockInTree;
					bool performedAtLeastOneObjectInitialisationAtALowerLevel = generateObjectInitialisationsBasedOnPropertiesAndConditions(conditionObject, currentCodeBlockInTree, sentenceIndex, generateInstanceName(entity), conditionEntity->entityName);

					generateObjectInitialisationsBasedOnPropertiesAndConditionsUpdateCodeBlockPointer(currentCodeBlockInTree, firstCodeBlockBeforeRecursion, firstCodeBlockInSection, performedAtLeastOneObjectInitialisationAtThisLevel, performedAtLeastOneObjectInitialisationAtALowerLevel, &performedAtLeastOneObjectInitialisation);
				}
			}
			else
			{
				//no condition object
			}
		}
	}
	return performedAtLeastOneObjectInitialisation;
}

void generateObjectInitialisationsBasedOnPropertiesAndConditionsUpdateCodeBlockPointer(NLPIcodeblock ** currentCodeBlockInTree, NLPIcodeblock * firstCodeBlockBeforeRecursion, NLPIcodeblock * firstCodeBlockInSection, bool performedAtLeastOneObjectInitialisationAtThisLevel, bool performedAtLeastOneObjectInitialisationAtALowerLevel, bool * performedAtLeastOneObjectInitialisation)
{
	if(!performedAtLeastOneObjectInitialisationAtALowerLevel)
	{
		if(performedAtLeastOneObjectInitialisationAtThisLevel)
		{
			firstCodeBlockBeforeRecursion->codeBlockType = NLPI_CODEBLOCK_TYPE_UNDEFINED;
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
			(*currentCodeBlockInTree)->codeBlockType = NLPI_CODEBLOCK_TYPE_UNDEFINED;
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
void generateObjectInitialisationsBasedOnSubstanceConcepts(GIAentityNode * entity, NLPIcodeblock ** currentCodeBlockInTree, int sentenceIndex)
{	
	for(vector<GIAentityConnection*>::iterator entityNodeDefinitionListIterator = entity->entityNodeDefinitionList->begin(); entityNodeDefinitionListIterator < entity->entityNodeDefinitionList->end(); entityNodeDefinitionListIterator++)
	{
		GIAentityConnection * definitionConnection = (*entityNodeDefinitionListIterator);
		//if(!(definitionConnection->parsedForNLPIcodeBlocks))	//probably not required
		//{
		GIAentityNode* definitionEntity = definitionConnection->entity;
		//check the definition is a substance concept
		if((definitionEntity->isSubstanceConcept) || (definitionEntity->isActionConcept))	//added (definitionEntity->isActionConcept)  changed 1e2e
		{
			//cout << "isSubstanceConcept" << endl;
			definitionConnection->parsedForNLPIcodeBlocks = true;

			generateObjectInitialisationsBasedOnSubstanceConceptsRecurse(entity, definitionEntity, currentCodeBlockInTree, sentenceIndex);
		}
		//}
	}
}

void generateObjectInitialisationsBasedOnSubstanceConceptsRecurse(GIAentityNode * entity, GIAentityNode * definitionEntity, NLPIcodeblock ** currentCodeBlockInTree, int sentenceIndex)
{
	//property initialisations
	for(vector<GIAentityConnection*>::iterator propertyNodeListIterator = definitionEntity->propertyNodeList->begin(); propertyNodeListIterator < definitionEntity->propertyNodeList->end(); propertyNodeListIterator++)
	{
		GIAentityConnection * propertyConnection = (*propertyNodeListIterator);
		GIAentityNode* propertyEntity = propertyConnection->entity;

		bool alreadyAdded = checkDuplicateProperty(propertyEntity, entity);
		if(!alreadyAdded)
		{
			NLPIcodeblock * firstCodeBlockInSection = *currentCodeBlockInTree;
			bool loopUsed = false;
			#ifdef NLPI_SUPPORT_INPUT_FILE_LISTS
			if(!(entity->NLPIisSingularArgument))
			{
				//cout << "entity->entityName = " << entity->entityName << endl;
				//for(all items in context){
				NLPIitem * entityClass = new NLPIitem(entity, NLPI_ITEM_TYPE_CLASS);
				bool entityHasParent = getEntityContext(entity, &(entityClass->context), false, sentenceIndex, true);
				*currentCodeBlockInTree = createCodeBlockForPropertyList(*currentCodeBlockInTree, entityClass);
				loopUsed = true;		
			}
			#endif
			
			//cout << "sentenceIndexA = " << sentenceIndex << endl;
			*currentCodeBlockInTree = createCodeBlockAddNewProperty(*currentCodeBlockInTree, entity, propertyEntity, sentenceIndex);
			
			entity->parsedForNLPIcodeBlocks = true;			//added 4 October 2013 NLPI1b6b  - used for quick access of instances already declared in current context 
			generateObjectInitialisationsBasedOnSubstanceConceptsRecurse(entity, propertyEntity, currentCodeBlockInTree, sentenceIndex);		//updated 9 November 2013 - support recursion of complex substance concept definition
			
			if(loopUsed)
			{
				*currentCodeBlockInTree = firstCodeBlockInSection->next;
			}				
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
			NLPIcodeblock * firstCodeBlockInSection = *currentCodeBlockInTree;
			bool loopUsed = false;
			#ifdef NLPI_SUPPORT_INPUT_FILE_LISTS
			if(!(entity->NLPIisSingularArgument))
			{
				//cout << "entity->entityName = " << entity->entityName << endl;
				//for(all items in context){
				NLPIitem * entityClass = new NLPIitem(entity, NLPI_ITEM_TYPE_CLASS);
				bool entityHasParent = getEntityContext(entity, &(entityClass->context), false, sentenceIndex, true);
				*currentCodeBlockInTree = createCodeBlockForPropertyList(*currentCodeBlockInTree, entityClass);
				loopUsed = true;		
			}
			#endif
								
			//cout << "sentenceIndexB = " << sentenceIndex << endl;
			*currentCodeBlockInTree = createCodeBlockAddNewCondition(*currentCodeBlockInTree, entity, conditionEntity, sentenceIndex);
			
			entity->parsedForNLPIcodeBlocks = true;			//added 4 October 2013 NLPI1b6b  - used for quick access of instances already declared in current context 
			generateObjectInitialisationsBasedOnSubstanceConceptsRecurse(entity, conditionEntity, currentCodeBlockInTree, sentenceIndex);	//updated 9 November 2013 - support recursion of complex substance concept definition
		
			if(loopUsed)
			{
				*currentCodeBlockInTree = firstCodeBlockInSection->next;
			}

		}
	}
}		
#endif






