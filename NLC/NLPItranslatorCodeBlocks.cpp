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
 * Project Version: 1e7b 23-November-2013
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
					//#ifdef NLPI_DEBUG
					cout << "actionEntity->entityName = " << actionEntity->entityName << endl;
					//#endif
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
						cout << "NLPI_CODEBLOCK_TYPE_DECLARE_NEW_VARIABLE" << endl;
						actionEntity->NLPIisSingularArgument = true;	//added 1e2c
						//declare an "abstract" variable for the action (that will be filled with the its properties and conditions) and passed as an argument to the function; eg "fast" of "run fast"
						currentCodeBlockInTree->parameters.push_back(functionItem);
						currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, NLPI_CODEBLOCK_TYPE_DECLARE_NEW_VARIABLE);	
						generateObjectInitialisationsBasedOnPropertiesAndConditions(actionEntity, &currentCodeBlockInTree, sentenceIndex);
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
				generateObjectInitialisationsBasedOnPropertiesAndConditions(entity, &currentCodeBlockInTree, sentenceIndex);	
				
				/*//moved 1e1b: only generate object initialisations for items based on subject concepts when items are created in context
				#ifdef GIA_TRANSLATOR_DREAM_MODE_LINK_SPECIFIC_CONCEPTS_AND_ACTIONS
				//Part 2b: generate object initialisations based on substance concepts (class inheritance)
				generateObjectInitialisationsBasedOnSubstanceConcepts(entity, &currentCodeBlockInTree, sentenceIndex);
				#endif		
				*/	
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
	
	if(!(currentEntity->propertyNodeReverseList->empty()))
	{
		GIAentityNode * parentEntity = (currentEntity->propertyNodeReverseList->back())->entity;
		/*//removed 1e7b
		if(checkSentenceIndexParsingCodeBlocks(parentEntity, sentenceIndex, false))
		{
		*/
		if(generateContextBlocksAndInitialiseParentIfNecessary(currentCodeBlockInTree, parentEntity, sentenceIndex))
		{
			result = true;
			NLPIitem * propertyItem = new NLPIitem(currentEntity, NLPI_ITEM_TYPE_CLASS);
			propertyItem->context.push_back(generateInstanceName(parentEntity));
			*currentCodeBlockInTree = createCodeBlockForPropertyList(*currentCodeBlockInTree, propertyItem);

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
		/*//removed 1e7b
		}
		else
		{
			possibleContextParentFound = true;
		}
		*/
	}
	else
	{
		/*//removed 1e7b
		if(checkSentenceIndexParsingCodeBlocks(currentEntity, sentenceIndex, false))
		{
		*/
			possibleContextParentFound = true;
		/*//removed 1e7b
		}
		*/
	}
	
	cout << "generateContextBlocksAndInitialiseParentIfNecessary, sentenceIndex = " << sentenceIndex << endl;
	cout << "\tpossibleContextParentFound = " << possibleContextParentFound << endl;
	cout << "\tcurrentEntity->entityName = " << currentEntity->entityName << endl;
	
	if(possibleContextParentFound)
	{
		result = true;
		#ifdef NLPI_CREATE_IMPLICITLY_DECLARED_ACTION_OBJECT_AND_SUBJECT_VARIABLES
		if(!assumedToAlreadyHaveBeenDeclared(currentEntity))
		{
			if(!(currentEntity->parsedForNLPIcodeBlocks))
			{	
				//cout << "createCodeBlockAddNewListVariable: " << currentEntity->entityName << endl;
				*currentCodeBlockInTree = createCodeBlockAddNewListVariable(*currentCodeBlockInTree, currentEntity, sentenceIndex);
				currentEntity->parsedForNLPIcodeBlocks = true;
				generateObjectInitialisationsBasedOnPropertiesAndConditions(currentEntity, currentCodeBlockInTree, sentenceIndex);	
				#ifdef GIA_TRANSLATOR_DREAM_MODE_LINK_SPECIFIC_CONCEPTS_AND_ACTIONS
				//Part 2b: generate object initialisations based on substance concepts (class inheritance)
				generateObjectInitialisationsBasedOnSubstanceConcepts(currentEntity, currentCodeBlockInTree, sentenceIndex);
				#endif
			}
		}
		#endif		
		NLPIitem * propertyItem = new NLPIitem(currentEntity, NLPI_ITEM_TYPE_CLASS);
		*currentCodeBlockInTree = createCodeBlockForPropertyList(*currentCodeBlockInTree, propertyItem);
	}
	
	return result;
}	
			


NLPIcodeblock * generateConditionBlocks(NLPIcodeblock * currentCodeBlockInTree, GIAentityNode * entity, NLPIitem ** item, int sentenceIndex, bool * requiredTempVar, int itemType)
{
	*requiredTempVar = false;

	bool entityHasParent = false;
			
	//cout << "itemType = " << itemType << endl;
	
	if(!(entity->NLPIisSingularArgument))	//changed 1e2c 	//OLD:"!(entity->parsedForNLPIcodeBlocks)" added 3 October 2013 NLPI1b2b - used for quick access of instances already declared in current context 
	{//for loop required
		*requiredTempVar = true;
		
		//for(all items in context){
		//NLPIitem * entityClass = new NLPIitem(entity, NLPI_ITEM_TYPE_CLASS);					//removed 1e6a
		//entityHasParent = getEntityContext(entity, &(entityClass->context), false, sentenceIndex, true);	//removed 1e6a
		//currentCodeBlockInTree = createCodeBlockForPropertyList(currentCodeBlockInTree, entityClass);		//removed 1e6a
		*item = new NLPIitem(entity, itemType);	//OLD: NLPI_ITEM_TYPE_TEMPVAR
		//cout << "generateConditionBlocks, entity = " << entity->entityName << endl;
		//cout << "!parsedForNLPIcodeBlocks, entity = " << entity->entityName << endl;
		
		currentCodeBlockInTree = createCodeBlockForStatements(currentCodeBlockInTree, *item, entity, sentenceIndex);
	}
	else
	{
		//*item = new NLPIitem(entity, itemType);	//OLD: NLPI_ITEM_TYPE_OBJECT
		//entityHasParent = getEntityContext(entity, &((*item)->context), false, sentenceIndex, true);	//removed 1e6a
		//cout << "entity = " << entity->entityName << endl;
	}
	return currentCodeBlockInTree;
}


void generateObjectInitialisationsBasedOnPropertiesAndConditions(GIAentityNode * entity, NLPIcodeblock ** currentCodeBlockInTree, int sentenceIndex)
{
	if(!(entity->isSubstanceConcept) && !(entity->isActionConcept))
	{
		
		#ifdef NLPI_CREATE_IMPLICITLY_DECLARED_ACTION_OBJECT_AND_SUBJECT_VARIABLES
		//added 1e6c: eg A chicken's hat has a bike. / A blue dog has a bike.
		if(!(entity->isConcept))
		{
			if(!(entity->parsedForNLPIcodeBlocks))	// && !(entity->parsedForNLPIcodeBlocksActionRound)
			{
				if(!assumedToAlreadyHaveBeenDeclared(entity))	
				{
					if(entity->propertyNodeReverseList->empty())
					{
						if(!(entity->isAction))	//added 1e6d
						{
							//cout << "createCodeBlockAddNewListVariable: " << currentEntity->entityName << endl;
							*currentCodeBlockInTree = createCodeBlockAddNewListVariable(*currentCodeBlockInTree, entity, sentenceIndex);
							entity->parsedForNLPIcodeBlocks = true;
							cout << "createCodeBlockAddNewListVariable: " << entity->entityName << endl;
						}
					}
				}
			}
		}
		#endif
		
		//property initialisations
		for(vector<GIAentityConnection*>::iterator propertyNodeListIterator = entity->propertyNodeList->begin(); propertyNodeListIterator < entity->propertyNodeList->end(); propertyNodeListIterator++)
		{
			GIAentityConnection * propertyConnection = (*propertyNodeListIterator);
			if(!(propertyConnection->parsedForNLPIcodeBlocks))
			{
				GIAentityNode* propertyEntity = propertyConnection->entity;
				if(checkSentenceIndexParsingCodeBlocks(propertyEntity,  sentenceIndex, false))
				{//only write properties that are explicated in current sentence
					
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
						//cout << "createCodeBlockForPropertyList: " << entity->entityName << endl;
						loopUsed = true;		
					}
					#endif
					#ifdef NLPI_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS
					if(assumedToAlreadyHaveBeenDeclared(propertyEntity))
					{
						//use function argument PropertyList (do not create a new property); eg "the ball" in "Tom has the ball"
						//cout << "propertyEntity->entityName = " << propertyEntity->entityName << endl;
						//for(all items in context){
						if(!(propertyEntity->NLPIisSingularArgument))
						{
						      NLPIitem * entityClass = new NLPIitem(propertyEntity, NLPI_ITEM_TYPE_CLASS);
						   //   bool entityHasParent = getEntityContext(propertyEntity, &(entityClass->context), false, sentenceIndex, true);	//removed 1e6b
						      *currentCodeBlockInTree = createCodeBlockForPropertyList(*currentCodeBlockInTree, entityClass);
						}  
						*currentCodeBlockInTree = createCodeBlockAddProperty(*currentCodeBlockInTree, entity, propertyEntity, sentenceIndex);	
						loopUsed = true;
						//cout << "createCodeBlockAddProperty: " << entity->entityName << ", " << propertyEntity->entityName << endl;
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
					entity->parsedForNLPIcodeBlocks = true;			//added 4 October 2013 NLPI1b6b  - used for quick access of instances already declared in current context 
				
					//moved 1e1b: only generate object initialisations for items based on subject concepts when items are created in context
					#ifdef GIA_TRANSLATOR_DREAM_MODE_LINK_SPECIFIC_CONCEPTS_AND_ACTIONS
					//Part 2b: generate object initialisations based on substance concepts (class inheritance)
					generateObjectInitialisationsBasedOnSubstanceConcepts(propertyEntity, currentCodeBlockInTree, sentenceIndex);
					#endif		
					
					if(loopUsed)
					{
						*currentCodeBlockInTree = firstCodeBlockInSection->next;
					}			
				}
			}
		}
		//state initialisations
		for(vector<GIAentityConnection*>::iterator conditionNodeListIterator = entity->conditionNodeList->begin(); conditionNodeListIterator < entity->conditionNodeList->end(); conditionNodeListIterator++)
		{
			GIAentityConnection * conditionConnection = (*conditionNodeListIterator);
			if(!(conditionConnection->parsedForNLPIcodeBlocks))
			{
				GIAentityNode* conditionEntity = conditionConnection->entity;
				if(checkSentenceIndexParsingCodeBlocks(conditionEntity,  sentenceIndex, false))
				{//only write conditions that are explicated in current sentence	
				
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
					#ifdef NLPI_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS
					bool foundConditionObject = false;
					GIAentityNode * conditionObject = NULL;
					if(!(conditionEntity->conditionObjectEntity->empty()))
					{
						conditionObject = (conditionEntity->conditionObjectEntity->back())->entity;
						foundConditionObject = true;
					}		
					if(foundConditionObject && assumedToAlreadyHaveBeenDeclared(conditionObject))
					{
						//use function argument PropertyList (do not create a new property to insert into condition); eg "the house" in "Tom is near a house"
						//cout << "conditionObject->entityName = " << conditionObject->entityName << endl;
						//for(all items in context){
						if(!(conditionObject->NLPIisSingularArgument))
						{
							NLPIitem * entityClass = new NLPIitem(conditionObject, NLPI_ITEM_TYPE_CLASS);
							//bool entityHasParent = getEntityContext(conditionObject, &(entityClass->context), false, sentenceIndex, true);	//removed 1e6b
							*currentCodeBlockInTree = createCodeBlockForPropertyList(*currentCodeBlockInTree, entityClass);
						}	
						*currentCodeBlockInTree = createCodeBlockAddCondition(*currentCodeBlockInTree, entity, conditionEntity, sentenceIndex);
						loopUsed = true;
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
					entity->parsedForNLPIcodeBlocks = true;		//added 4 October 2013 NLPI1b6b  - used for quick access of instances already declared in current context 
				
					//moved 1e1b: only generate object initialisations for items based on subject concepts when items are created in context
					#ifdef GIA_TRANSLATOR_DREAM_MODE_LINK_SPECIFIC_CONCEPTS_AND_ACTIONS
					//Part 2b: generate object initialisations based on substance concepts (class inheritance)
					generateObjectInitialisationsBasedOnSubstanceConcepts(conditionEntity, currentCodeBlockInTree, sentenceIndex);
					#endif
					
					if(loopUsed)
					{
						*currentCodeBlockInTree = firstCodeBlockInSection->next;
					}	
				}
			}
		}
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






