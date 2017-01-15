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
 * File Name: NLPItranslator.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2013 Baxter AI (baxterai.com)
 * Project: Natural Language Programming Interface (compiler)
 * Project Version: 1b6b 04-October-2013
 * Requirements: requires text parsed by NLP Parser (eg Relex; available in .CFF format <relations>)
 *
 *******************************************************************************/



#include <ctime>
#include <cstdlib>	//for random number generation
#include <cmath>

#include "NLPItranslator.h"

bool translateNetwork(NLPIcodeblock * firstCodeBlockInTree, vector<NLPIclassDefinition *> * classDefinitionList, vector<GIAentityNode*> * entityNodesActiveListComplete, vector<GIAentityNode*> * entityNodesActiveListActions, int maxNumberSentences)
{
	bool result = true;

	//NLPI translator Part 1.
	if(!generateCodeBlocks(firstCodeBlockInTree, entityNodesActiveListComplete, entityNodesActiveListActions, maxNumberSentences))
	{
		result = false;
	}
	
	//NLPI translator Part 2.
	if(!generateClassHeirarchy(classDefinitionList, entityNodesActiveListComplete, maxNumberSentences))
	{
		result = false;
	}
}

bool generateCodeBlocks(NLPIcodeblock * firstCodeBlockInTree, vector<GIAentityNode*> * entityNodesActiveListComplete, vector<GIAentityNode*> * entityNodesActiveListActions, int maxNumberSentences)
{
	NLPIcodeblock * currentCodeBlockInTree = firstCodeBlockInTree;
	
	#ifdef NLPI_NOT_NECESSARY
	vector<NLPIitem *> implictlyDeclaredFunctionList;	//implictlyDeclaredFunctionList is used to capture implicitly declared functions; to be added to object class definitions at end
	vector<NLPIitem *> implictlyDeclaredFunctionListTopLevel;	//top level function list (used to store implicitly declared functions without subject/context/owner)	
	#endif
	
	currentCodeBlockInTree = createCodeBlockNewFunction(currentCodeBlockInTree, "main");

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
				#ifdef NLPI_DEBUG
				cout << "actionEntity->entityName = " << actionEntity->entityName << endl;
				#endif
				//cout << "actionEntity->isAction = " << actionEntity->isAction << endl;
				//cout << "actionEntity->hasAssociatedInstance = " << actionEntity->hasAssociatedInstance << endl;

				if(checkSentenceIndexParsingCodeBlocks(actionEntity, sentenceIndex))
				{
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

					if(actionHasObject)
					{
						bool objectRequiredTempVar = false;	//not used
						NLPIitem * objectItem = NULL;
						currentCodeBlockInTree = generateConditionBlocks(currentCodeBlockInTree, objectEntity, &objectItem, sentenceIndex, &objectRequiredTempVar);

						//cout << "h3" << endl;
						NLPIitem * functionItem = new NLPIitem(actionEntity, NLPI_ITEM_TYPE_FUNCTION);
						if(actionHasSubject)
						{
							bool subjectRequiredTempVar = false;
							NLPIitem * subjectItem = NULL;
							currentCodeBlockInTree = generateConditionBlocks(currentCodeBlockInTree, subjectEntity, &subjectItem, sentenceIndex, &subjectRequiredTempVar);
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

						}
						#ifdef NLPI_NOT_NECESSARY
						else
						{
							implictlyDeclaredFunctionListTopLevel.push_back(functionItem);					
						}
						#endif
						//cout << "h5" << endl;
						currentCodeBlockInTree = createCodeBlockExecute(currentCodeBlockInTree, functionItem, objectItem);
					}
					else if(actionHasSubject)
					{
						bool subjectRequiredTempVar = false;	//not used
						NLPIitem * subjectItem = NULL;
						currentCodeBlockInTree = generateConditionBlocks(currentCodeBlockInTree, subjectEntity, &subjectItem, sentenceIndex, &subjectRequiredTempVar);

						//cout << "h3" << endl;
						NLPIitem * functionItem = new NLPIitem(actionEntity, NLPI_ITEM_TYPE_FUNCTION);
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
						currentCodeBlockInTree = createCodeBlockExecute(currentCodeBlockInTree, functionItem);
					}

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
		}
		
		if(firstCodeBlockInSentence->next != NULL)
		{
			currentCodeBlockInTree = firstCodeBlockInSentence->next;
		}
		else
		{
			currentCodeBlockInTree = firstCodeBlockInSentence;
		}
		
		//cout << "q1" << endl;
	
		//Part 2: generate object initialisations (eg Tom has a boat) [without actions]
		//cout << "*** sentenceIndex = " << sentenceIndex << endl;
		for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
		{
			GIAentityNode * entity = *entityIter;
			if(checkSentenceIndexParsingCodeBlocks(entity, sentenceIndex))
			{	
				if(!(entity->isSubstanceConcept))
				{	
					//property initialisations
					for(vector<GIAentityConnection*>::iterator propertyNodeListIterator = entity->propertyNodeList->begin(); propertyNodeListIterator < entity->propertyNodeList->end(); propertyNodeListIterator++)
					{
						GIAentityConnection * propertyConnection = (*propertyNodeListIterator);
						if(!(propertyConnection->parsedForNLPIcodeBlocks))
						{
							GIAentityNode* propertyEntity = propertyConnection->entity;
							if(checkSentenceIndexParsingCodeBlocks(propertyEntity,  sentenceIndex))
							{//only write properties that are explicated in current sentence
								//cout << "sentenceIndexA = " << sentenceIndex << endl;
								currentCodeBlockInTree = createCodeBlockAddProperty(currentCodeBlockInTree, entity, propertyEntity, sentenceIndex);
								propertyConnection->parsedForNLPIcodeBlocks = true;
								propertyEntity->parsedForNLPIcodeBlocks = true;		//added 3 October 2013 NLPI1b2b - used for quick access of instances already declared in current context 
								entity->parsedForNLPIcodeBlocks = true;			//added 4 October 2013 NLPI1b6b  - used for quick access of instances already declared in current context 
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
							if(checkSentenceIndexParsingCodeBlocks(conditionEntity,  sentenceIndex))
							{//only write conditions that are explicated in current sentence	
								//cout << "sentenceIndexB = " << sentenceIndex << endl;
								currentCodeBlockInTree = createCodeBlockAddCondition(currentCodeBlockInTree, entity, conditionEntity, sentenceIndex);
								conditionConnection->parsedForNLPIcodeBlocks = true;
								conditionEntity->parsedForNLPIcodeBlocks = true;	//added 3 October 2013 NLPI1b2b - used for quick access of instances already declared in current context 
								entity->parsedForNLPIcodeBlocks = true;			//added 4 October 2013 NLPI1b6b  - used for quick access of instances already declared in current context 
							}
						}
					}
				}	
				
				//Part 2b: generate object initialisations based on substance concepts (class inheritance)
				for(vector<GIAentityConnection*>::iterator entityNodeDefinitionListIterator = entity->entityNodeDefinitionList->begin(); entityNodeDefinitionListIterator < entity->entityNodeDefinitionList->end(); entityNodeDefinitionListIterator++)
				{
					GIAentityConnection * definitionConnection = (*entityNodeDefinitionListIterator);
					//if(!(definitionConnection->parsedForNLPIcodeBlocks))	//probably not required
					//{
					GIAentityNode* definitionEntity = definitionConnection->entity;
					//check the definition is a substance concept
					if(definitionEntity->isSubstanceConcept)
					{
						definitionConnection->parsedForNLPIcodeBlocks = true;

						//property initialisations
						for(vector<GIAentityConnection*>::iterator propertyNodeListIterator = definitionEntity->propertyNodeList->begin(); propertyNodeListIterator < definitionEntity->propertyNodeList->end(); propertyNodeListIterator++)
						{
							GIAentityConnection * propertyConnection = (*propertyNodeListIterator);
							if(!(propertyConnection->parsedForNLPIcodeBlocks))
							{
								GIAentityNode* propertyEntity = propertyConnection->entity;
								if(checkSentenceIndexParsingCodeBlocks(propertyEntity,  sentenceIndex))
								{//only write properties that are explicated in current sentence
									//cout << "sentenceIndexA = " << sentenceIndex << endl;
									currentCodeBlockInTree = createCodeBlockAddProperty(currentCodeBlockInTree, entity, propertyEntity, sentenceIndex);
									entity->parsedForNLPIcodeBlocks = true;			//added 4 October 2013 NLPI1b6b  - used for quick access of instances already declared in current context 
								}
							}
						}
						//state initialisations
						for(vector<GIAentityConnection*>::iterator conditionNodeListIterator = definitionEntity->conditionNodeList->begin(); conditionNodeListIterator < definitionEntity->conditionNodeList->end(); conditionNodeListIterator++)
						{
							GIAentityConnection * conditionConnection = (*conditionNodeListIterator);
							if(!(conditionConnection->parsedForNLPIcodeBlocks))
							{
								GIAentityNode* conditionEntity = conditionConnection->entity;
								if(checkSentenceIndexParsingCodeBlocks(conditionEntity,  sentenceIndex))
								{//only write conditions that are explicated in current sentence	
									//cout << "sentenceIndexB = " << sentenceIndex << endl;
									currentCodeBlockInTree = createCodeBlockAddCondition(currentCodeBlockInTree, entity, conditionEntity, sentenceIndex);
									entity->parsedForNLPIcodeBlocks = true;			//added 4 October 2013 NLPI1b6b  - used for quick access of instances already declared in current context 
								}
							}
						}	
					}
					//}
				}				
			}
		}

				
		//cout << "q2" << endl;
	}
	
}

NLPIcodeblock * generateConditionBlocks(NLPIcodeblock * currentCodeBlockInTree, GIAentityNode * objectOrSubjectEntity, NLPIitem ** objectOrSubjectItem, int sentenceIndex, bool * requiredTempVar)
{
	*requiredTempVar = false;

	bool objectOrSubjectHasProperties = false;
	if(!(objectOrSubjectEntity->propertyNodeList->empty()))
	{
		objectOrSubjectHasProperties = true;
	}
	bool objectOrSubjectHasConditions = false;
	if(!(objectOrSubjectEntity->conditionNodeList->empty()))
	{
		objectOrSubjectHasConditions = true;	//not used
	}							
	bool multipleobjectOrSubjects = false;
	if(objectOrSubjectEntity->grammaticalNumber == GRAMMATICAL_NUMBER_PLURAL)
	{
		multipleobjectOrSubjects = true;
	}
	bool objectOrSubjectsHaveParent = false;
	
	//cout << "objectOrSubjectEntity->parsedForNLPIcodeBlocks = " << objectOrSubjectEntity->parsedForNLPIcodeBlocks << endl;
	
	if((multipleobjectOrSubjects || objectOrSubjectHasProperties || objectOrSubjectHasConditions) && !(objectOrSubjectEntity->parsedForNLPIcodeBlocks))	//"&& !(objectOrSubjectEntity->parsedForNLPIcodeBlocks)" added 3 October 2013 NLPI1b2b - used for quick access of instances already declared in current context 
	{//for loop required
		*requiredTempVar = true;
		
		//for(all items in context){
		NLPIitem * objectOrSubjectClass = new NLPIitem(objectOrSubjectEntity, NLPI_ITEM_TYPE_CLASS);
		objectOrSubjectsHaveParent = getEntityContext(objectOrSubjectEntity, &(objectOrSubjectClass->context), false, sentenceIndex, true);
		currentCodeBlockInTree = createCodeBlockFor(currentCodeBlockInTree, objectOrSubjectClass);
		*objectOrSubjectItem = new NLPIitem(objectOrSubjectEntity, NLPI_ITEM_TYPE_TEMPVAR);
		
		currentCodeBlockInTree = createCodeBlockIfStatements(currentCodeBlockInTree, *objectOrSubjectItem, objectOrSubjectEntity, sentenceIndex);
	}
	else
	{
		*objectOrSubjectItem = new NLPIitem(objectOrSubjectEntity, NLPI_ITEM_TYPE_OBJECT);
		objectOrSubjectsHaveParent = getEntityContext(objectOrSubjectEntity, &((*objectOrSubjectItem)->context), false, sentenceIndex, true);
	}
	return currentCodeBlockInTree;
}

bool generateClassHeirarchy(vector<NLPIclassDefinition *> * classDefinitionList, vector<GIAentityNode*> * entityNodesActiveListComplete, int maxNumberSentences)
{	
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode * entityNode = *entityIter;
		if(!(entityNode->disabled))
		{
			string className = generateClassName(entityNode);
			//cout << "className = " << className << endl;
			bool foundClassDefinition = false;
			NLPIclassDefinition * classDefinition = findClassDefinition(classDefinitionList, className, &foundClassDefinition);	//see if class definition already exists
			if(!foundClassDefinition)
			{
				classDefinition = new NLPIclassDefinition(className);
				classDefinitionList->push_back(classDefinition);
				//cout << "!foundClassDefinition" << endl;
			}
			//cout << "generateClassHeirarchy: " << className << endl;


			for(int i=0; i<GIA_ENTITY_NUMBER_OF_VECTOR_CONNECTION_TYPES; i++)
			{
				for(vector<GIAentityConnection*>::iterator connectionIter = entityNode->entityVectorConnectionsArray[i].begin(); connectionIter != entityNode->entityVectorConnectionsArray[i].end(); connectionIter++)
				{
					GIAentityConnection * connection = *connectionIter;
					GIAentityNode * targetEntity = connection->entity;

					if(i == GIA_ENTITY_VECTOR_CONNECTION_TYPE_CONDITIONS)
					{
						if(!(targetEntity->conditionObjectEntity->empty()))
						{					
							targetEntity = (targetEntity->conditionObjectEntity->back())->entity;
						}
						else
						{
							cout << "error generateClassHeirarchy(): condition does not have object" << endl;
						}
					}
					
					string targetName = "";

					if(i == GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTIONS)
					{
						#ifndef NLPI_BAD_IMPLEMENTATION
						targetName = generateInstanceName(targetEntity);
						#else
						targetName = generateActionName(targetEntity);
						#endif
					}
					else
					{
						targetName = generateClassName(targetEntity);
					}
					
					bool foundTargetClassDefinition = false;
					NLPIclassDefinition * targetClassDefinition = findClassDefinition(classDefinitionList, targetName, &foundTargetClassDefinition);	//see if class definition already exists
					if(!foundTargetClassDefinition)
					{
						//cout << "new NLPIclassDefinition(" << targetName << endl;
						targetClassDefinition = new NLPIclassDefinition(targetName);
						classDefinitionList->push_back(targetClassDefinition);
					}
					#ifndef NLPI_BAD_IMPLEMENTATION
					if(targetEntity->isAction)
					{
						targetClassDefinition->actionInstanceNotClassButFunction = true;
						//cout << "classDefinition->actionInstanceNotClassButFunction" << endl;
					}
					#endif					

					if(i == GIA_ENTITY_VECTOR_CONNECTION_TYPE_PROPERTIES)
					{//declare subclass
						//propertyList
						bool foundLocalClassDefinition = false;
						NLPIclassDefinition * localClassDefinition = findClassDefinition(&(classDefinition->propertyList), targetName, &foundLocalClassDefinition);	//see if class definition already exists
						if(!foundLocalClassDefinition)
						{
							//cout << "propertyList.push_back: " << targetClassDefinition->name << endl;
							classDefinition->propertyList.push_back(targetClassDefinition);
						}
					}
					else if(i == GIA_ENTITY_VECTOR_CONNECTION_TYPE_CONDITIONS)
					{//declare conditions
						//conditionList
						bool foundLocalClassDefinition = false;
						NLPIclassDefinition * localClassDefinition = findClassDefinition(&(classDefinition->conditionList), targetName, &foundLocalClassDefinition);	//see if class definition already exists
						if(!foundLocalClassDefinition)
						{
							//cout << "conditionList.push_back: " << targetClassDefinition->name << endl;
							classDefinition->conditionList.push_back(targetClassDefinition);
						}						
					}	
					#ifndef NLPI_BAD_IMPLEMENTATION
					else if(i == GIA_ENTITY_VECTOR_CONNECTION_TYPE_DEFINITIONS) 
					{//declare inheritance
						if(targetName != className)	//eg do not create a separate class for substance concept definitions
						{
					#else			
					else if((i == GIA_ENTITY_VECTOR_CONNECTION_TYPE_DEFINITIONS) || (i == GIA_ENTITY_VECTOR_CONNECTION_TYPE_NODE_DEFINING_INSTANCE))
					{//declare inheritance					
					#endif
							//definitionList
							bool foundLocalClassDefinition = false;
							NLPIclassDefinition * localClassDefinition = findClassDefinition(&(classDefinition->definitionList), targetName, &foundLocalClassDefinition);	//see if class definition already exists
							if(!foundLocalClassDefinition)
							{
								//cout << "definitionList.push_back: " << targetClassDefinition->name << endl;
								classDefinition->definitionList.push_back(targetClassDefinition);
							}
						#ifndef NLPI_BAD_IMPLEMENTATION
						}
						#endif
					}
					else if(i == GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTIONS)
					{//declare functions
						//functionList
						bool foundLocalClassDefinition = false;
						NLPIclassDefinition * localClassDefinition = findClassDefinition(&(classDefinition->functionList), targetName, &foundLocalClassDefinition);	//see if class definition already exists
						if(!foundLocalClassDefinition)
						{
							//cout << "functionList.push_back: " << targetClassDefinition->name << endl;
							classDefinition->functionList.push_back(targetClassDefinition);

							if(!(targetEntity->actionObjectEntity->empty()))
							{
								GIAentityNode * actionObject = (targetEntity->actionObjectEntity->back())->entity;
								targetClassDefinition->actionObjectClassName = generateClassName(actionObject);
								targetClassDefinition->actionObjectInstanceName = generateInstanceName(actionObject);
							}
						}
					}
				}
			}
		}
	}
}	

