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
 * Project Version: 1d1d 02-November-2013
 * Requirements: requires text parsed by NLP Parser (eg Relex; available in .CFF format <relations>)
 *
 *******************************************************************************/



#include <ctime>
#include <cstdlib>	//for random number generation
#include <cmath>

#include "NLPItranslator.h"

bool translateNetwork(NLPIcodeblock * firstCodeBlockInTree, vector<NLPIclassDefinition *> * classDefinitionList, vector<GIAentityNode*> * entityNodesActiveListComplete, vector<GIAentityNode*> * entityNodesActiveListActions, int maxNumberSentences, string NLPIfunctionName)
{
	bool result = true;

	//NLPI translator Part 1.
	if(!generateCodeBlocks(firstCodeBlockInTree, entityNodesActiveListComplete, entityNodesActiveListActions, maxNumberSentences, NLPIfunctionName))
	{
		result = false;
	}
	
	//NLPI translator Part 2.
	if(!generateClassHeirarchy(classDefinitionList, entityNodesActiveListComplete, maxNumberSentences))
	{
		result = false;
	}
}

bool generateCodeBlocks(NLPIcodeblock * firstCodeBlockInTree, vector<GIAentityNode*> * entityNodesActiveListComplete, vector<GIAentityNode*> * entityNodesActiveListActions, int maxNumberSentences, string NLPIfunctionName)
{
	//gets "fight" from "dog::fight"
	string functionName = "";
	bool foundFunctionOwnerClass = false;
	string functionOwnerName = "";
	#ifdef NLPI_SUPPORT_INPUT_FILE_LISTS
	parseFunctionNameFromNLPIfunctionName(NLPIfunctionName, &functionName, &functionOwnerName, &foundFunctionOwnerClass);
	#else
	functionName = NLPIfunctionName;
	#endif
	
	NLPIcodeblock * currentCodeBlockInTree = firstCodeBlockInTree;
	
	#ifdef NLPI_NOT_NECESSARY
	vector<NLPIitem *> implictlyDeclaredFunctionList;	//implictlyDeclaredFunctionList is used to capture implicitly declared functions; to be added to object class definitions at end
	vector<NLPIitem *> implictlyDeclaredFunctionListTopLevel;	//top level function list (used to store implicitly declared functions without subject/context/owner)	
	#endif
	
	currentCodeBlockInTree = createCodeBlockNewFunction(currentCodeBlockInTree, functionName, entityNodesActiveListComplete);

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

				if(checkSentenceIndexParsingCodeBlocks(actionEntity, sentenceIndex, true))
				{
					//cout << "sentenceIndexC = " << sentenceIndex << endl;
					//cout << "h1" << endl;
					
					bool formalFunctionArgumentCorrespondsToActionSubjectUseThisAlias = false;
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
						#ifdef NLPI_SUPPORT_INPUT_FILE_LISTS
						if(subjectEntity->entityName == functionOwnerName)
						{
							formalFunctionArgumentCorrespondsToActionSubjectUseThisAlias = true;
						}
						#endif
					}

					//cout << "h2" << endl;


					NLPIcodeblock * functionExecuteCodeBlockInTree = NULL;
			
					if(actionHasObject)
					{
						NLPIitem * functionItem = new NLPIitem(actionEntity, NLPI_ITEM_TYPE_FUNCTION);
						bool objectRequiredTempVar = false;	//not used
						NLPIitem * objectItem = NULL;
						currentCodeBlockInTree = generateConditionBlocks(currentCodeBlockInTree, objectEntity, &objectItem, sentenceIndex, &objectRequiredTempVar, false);

						//cout << "h3" << endl;
						if(actionHasSubject)
						{
							bool subjectRequiredTempVar = false;
							NLPIitem * subjectItem = NULL;
							currentCodeBlockInTree = generateConditionBlocks(currentCodeBlockInTree, subjectEntity, &subjectItem, sentenceIndex, &subjectRequiredTempVar, formalFunctionArgumentCorrespondsToActionSubjectUseThisAlias);
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
						functionExecuteCodeBlockInTree = currentCodeBlockInTree;
						currentCodeBlockInTree = createCodeBlockExecute(currentCodeBlockInTree, functionItem, objectItem);
					}
					else if(actionHasSubject)
					{
						NLPIitem * functionItem = new NLPIitem(actionEntity, NLPI_ITEM_TYPE_FUNCTION);
						bool subjectRequiredTempVar = false;	//not used
						NLPIitem * subjectItem = NULL;
						currentCodeBlockInTree = generateConditionBlocks(currentCodeBlockInTree, subjectEntity, &subjectItem, sentenceIndex, &subjectRequiredTempVar, formalFunctionArgumentCorrespondsToActionSubjectUseThisAlias);

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
					}					

					if(actionHasObject || actionHasSubject)
					{						
						#ifdef NLPI_INTERPRET_ACTION_PROPERTIES_AND_CONDITIONS_AS_FUNCTION_ARGUMENTS
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
						#endif
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
			if(checkSentenceIndexParsingCodeBlocks(entity, sentenceIndex, false))
			{	
				if(!(entity->isSubstanceConcept) && !(entity->isActionConcept))
				{	
					//property initialisations
					for(vector<GIAentityConnection*>::iterator propertyNodeListIterator = entity->propertyNodeList->begin(); propertyNodeListIterator < entity->propertyNodeList->end(); propertyNodeListIterator++)
					{
						GIAentityConnection * propertyConnection = (*propertyNodeListIterator);
						if(!(propertyConnection->parsedForNLPIcodeBlocks))
						{
							GIAentityNode* propertyEntity = propertyConnection->entity;
							if(checkSentenceIndexParsingCodeBlocks(propertyEntity,  sentenceIndex, false))
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
							if(checkSentenceIndexParsingCodeBlocks(conditionEntity,  sentenceIndex, false))
							{//only write conditions that are explicated in current sentence	
								//cout << "sentenceIndexB = " << sentenceIndex << endl;
								currentCodeBlockInTree = createCodeBlockAddCondition(currentCodeBlockInTree, entity, conditionEntity, sentenceIndex);
								conditionConnection->parsedForNLPIcodeBlocks = true;
								conditionEntity->parsedForNLPIcodeBlocks = true;	//added 3 October 2013 NLPI1b2b - used for quick access of instances already declared in current context 
								entity->parsedForNLPIcodeBlocks = true;		//added 4 October 2013 NLPI1b6b  - used for quick access of instances already declared in current context 
							}
						}
					}
				}	
				
				#ifdef GIA_TRANSLATOR_DREAM_MODE_LINK_SPECIFIC_CONCEPTS_AND_ACTIONS
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
						//cout << "isSubstanceConcept" << endl;
						definitionConnection->parsedForNLPIcodeBlocks = true;

						//property initialisations
						for(vector<GIAentityConnection*>::iterator propertyNodeListIterator = definitionEntity->propertyNodeList->begin(); propertyNodeListIterator < definitionEntity->propertyNodeList->end(); propertyNodeListIterator++)
						{
							GIAentityConnection * propertyConnection = (*propertyNodeListIterator);
							GIAentityNode* propertyEntity = propertyConnection->entity;
														
							bool alreadyAdded = checkDuplicateProperty(propertyEntity, entity);
							if(!alreadyAdded)
							{
								//cout << "sentenceIndexA = " << sentenceIndex << endl;
								currentCodeBlockInTree = createCodeBlockAddProperty(currentCodeBlockInTree, entity, propertyEntity, sentenceIndex);
								entity->parsedForNLPIcodeBlocks = true;			//added 4 October 2013 NLPI1b6b  - used for quick access of instances already declared in current context 
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
								//cout << "sentenceIndexB = " << sentenceIndex << endl;
								currentCodeBlockInTree = createCodeBlockAddCondition(currentCodeBlockInTree, entity, conditionEntity, sentenceIndex);
								entity->parsedForNLPIcodeBlocks = true;			//added 4 October 2013 NLPI1b6b  - used for quick access of instances already declared in current context 
							}
						}	
					}
					//}
				}
				#endif				
			}
		}

				
		//cout << "q2" << endl;
	}
	
}

													
NLPIcodeblock * generateConditionBlocks(NLPIcodeblock * currentCodeBlockInTree, GIAentityNode * objectOrSubjectEntity, NLPIitem ** objectOrSubjectItem, int sentenceIndex, bool * requiredTempVar, bool formalFunctionArgumentCorrespondsToActionSubjectUseThisAlias)
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
		NLPIitem * objectOrSubjectClass = new NLPIitem(objectOrSubjectEntity, NLPI_ITEM_TYPE_CLASS, formalFunctionArgumentCorrespondsToActionSubjectUseThisAlias);
		objectOrSubjectsHaveParent = getEntityContext(objectOrSubjectEntity, &(objectOrSubjectClass->context), false, sentenceIndex, true);
		currentCodeBlockInTree = createCodeBlockFor(currentCodeBlockInTree, objectOrSubjectClass);
		*objectOrSubjectItem = new NLPIitem(objectOrSubjectEntity, NLPI_ITEM_TYPE_TEMPVAR);
		
		currentCodeBlockInTree = createCodeBlockIfStatements(currentCodeBlockInTree, *objectOrSubjectItem, objectOrSubjectEntity, sentenceIndex);
	}
	else
	{
		*objectOrSubjectItem = new NLPIitem(objectOrSubjectEntity, NLPI_ITEM_TYPE_OBJECT, formalFunctionArgumentCorrespondsToActionSubjectUseThisAlias);
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
					
					if(!(targetEntity->disabled))
					{
					
						string targetName = "";
						string targetClassName = "";
						if(i == GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTIONS)	//in GIA actions are treated as special connections with intermediary nodes
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
						
						if(i == GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTIONS)
						{
							targetClassDefinition->classNameSpecial = generateClassName(targetEntity);
							#ifdef NLPI_SUPPORT_INPUT_FILE_LISTS_CHECK_ACTION_SUBJECT_CONTENTS_FOR_IMPLICITLY_DECLARED_PARAMETERS
							targetClassDefinition->actionOrConditionInstance = targetEntity;
							#endif
						}
						
						#ifndef NLPI_BAD_IMPLEMENTATION
						//if((targetEntity->isAction) || (targetEntity->isActionConcept) || (targetEntity->isCondition) && !(targetEntity->isConcept))	//CAN BE TEMPORARILY MODIFED FOR DEBUGGING
						if((targetEntity->isCondition) && !(targetEntity->isConcept))
						{
							targetClassDefinition->isActionOrConditionInstanceNotClass = true;
							//cout << "classDefinition->isActionOrConditionInstanceNotClass" << endl;
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

								NLPIitem * classDeclarationPropertiesListItem = new NLPIitem(targetEntity, NLPI_ITEM_TYPE_CLASS_DECLARATION_PROPERTY_LIST);
								targetClassDefinition->parameters.push_back(classDeclarationPropertiesListItem);
							}
						}
						else if(i == GIA_ENTITY_VECTOR_CONNECTION_TYPE_CONDITIONS)
						{//declare conditions
							//conditionList
							bool foundLocalClassDefinition = false;
							NLPIclassDefinition * localClassDefinition = findClassDefinition(&(classDefinition->conditionList), targetName, &foundLocalClassDefinition);	//see if class definition already exists
							if(!foundLocalClassDefinition)
							{
								//cout << "conditionList.push_back: " << targetClassDefinition->className << endl;
								classDefinition->conditionList.push_back(targetClassDefinition);

								NLPIitem * classDeclarationConditionsListItem = new NLPIitem(targetEntity, NLPI_ITEM_TYPE_CLASS_DECLARATION_CONDITION_LIST);
								if(!(targetEntity->conditionObjectEntity->empty()))
								{								
									string conditionObjectClassName = generateClassName((targetEntity->conditionObjectEntity->back())->entity);
									classDeclarationConditionsListItem->className2 = conditionObjectClassName;				
								}				
								targetClassDefinition->parameters.push_back(classDeclarationConditionsListItem);
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

								//NLPIitem * classDeclarationFunctionItem = new NLPIitem(targetEntity, NLPI_ITEM_TYPE_CLASS_DECLARATION_FUNCTION);
								//targetClassDefinition->parameters.push_back(classDeclarationFunctionItem);	//required for NLPI 1c5a+ (print function class name not instance name)
								if(!(targetEntity->actionObjectEntity->empty()))
								{							
									GIAentityNode * actionObject = (targetEntity->actionObjectEntity->back())->entity;
									NLPIitem * classDeclarationFunctionObjectItem = new NLPIitem(actionObject, NLPI_ITEM_TYPE_CLASS_DECLARATION_FUNCTION_OBJECT);	//for special case (as actions are referenced by instance)
									targetClassDefinition->parameters.push_back(classDeclarationFunctionObjectItem);
								}
								#ifdef NLPI_INTERPRET_ACTION_PROPERTIES_AND_CONDITIONS_AS_FUNCTION_ARGUMENTS
								generateFunctionPropertyConditionArgumentsWithActionConceptInheritance(targetEntity, &(targetClassDefinition->parameters));
								#endif								
							}
						}
					}
				}
			}
		}
	}
	
	
	#ifdef NLPI_PREVENT_INHERITANCE_DOUBLE_DECLARATIONS_OF_CLASS_LIST_VARIABLES
	//disable all double declarations
	for(vector<NLPIclassDefinition*>::iterator classDefinitionIter = classDefinitionList->begin(); classDefinitionIter != classDefinitionList->end(); classDefinitionIter++)
	{	
		NLPIclassDefinition * classDefinition = *classDefinitionIter;

		eraseDuplicateClassDefinitionSublistItemIfFoundInParentClassDefinitionSublist(classDefinition, &(classDefinition->propertyList), GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTIONS);
		eraseDuplicateClassDefinitionSublistItemIfFoundInParentClassDefinitionSublist(classDefinition, &(classDefinition->conditionList), GIA_ENTITY_VECTOR_CONNECTION_TYPE_CONDITIONS);
		eraseDuplicateClassDefinitionSublistItemIfFoundInParentClassDefinitionSublist(classDefinition, &(classDefinition->functionList), GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTIONS);
	}		
	#endif
}	

#ifdef NLPI_PREVENT_INHERITANCE_DOUBLE_DECLARATIONS_OF_CLASS_LIST_VARIABLES
void eraseDuplicateClassDefinitionSublistItemIfFoundInParentClassDefinitionSublist(NLPIclassDefinition * classDefinition, vector<NLPIclassDefinition*> * classDefinitionSublist, int variableType)
{
	for(vector<NLPIclassDefinition*>::iterator localListIter = classDefinitionSublist->begin(); localListIter != classDefinitionSublist->end();)
	{
		bool localListIterErased = false;
		NLPIclassDefinition * variableClassDefinition = *localListIter;
		string variableName = variableClassDefinition->name;
		for(vector<NLPIclassDefinition*>::iterator parentListIter = classDefinition->definitionList.begin(); parentListIter != classDefinition->definitionList.end(); parentListIter++)
		{
			if(!localListIterErased)
			{
				NLPIclassDefinition * targetClassDefinition = *parentListIter;
				if(findVariableInParentClass(classDefinition, variableName, variableType))
				{
					localListIter = classDefinitionSublist->erase(localListIter);	
					localListIterErased = true;
					//cout << "classDefinition->name = " << classDefinition->name << endl;
					//cout << "variableClassDefinition->name = " << variableClassDefinition->name << endl;
				}
			}
		}
		if(!localListIterErased)
		{
			localListIter++;
		}			
	}
}

bool findVariableInParentClass(NLPIclassDefinition * classDefinition, string variableName, int variableType)
{
	bool foundVariable = false;
	if(variableType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_PROPERTIES)
	{
		for(vector<NLPIclassDefinition*>::iterator localListIter = classDefinition->propertyList.begin(); localListIter != classDefinition->propertyList.end(); localListIter++)
		{
			NLPIclassDefinition * targetClassDefinition = *localListIter;
			string targetName = targetClassDefinition->name;
			if(targetName == variableName)
			{
				foundVariable = true;
			}
		}
	}
	else if(variableType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_CONDITIONS)
	{
		for(vector<NLPIclassDefinition*>::iterator localListIter = classDefinition->conditionList.begin(); localListIter != classDefinition->conditionList.end(); localListIter++)
		{
			NLPIclassDefinition * targetClassDefinition = *localListIter;
			//string targetName = targetClassDefinition->actionOrConditionInstance->entityName;
			string targetName = targetClassDefinition->name;
			if(targetName == variableName)
			{
				foundVariable = true;
			}	
		}
	}
	else if(variableType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTIONS)
	{
		for(vector<NLPIclassDefinition*>::iterator localListIter = classDefinition->functionList.begin(); localListIter != classDefinition->functionList.end(); localListIter++)
		{
			NLPIclassDefinition * targetClassDefinition = *localListIter;
			//string targetName = targetClassDefinition->actionOrConditionInstance->entityName;
			string targetName = targetClassDefinition->name;
			if(targetName == variableName)
			{
				foundVariable = true;
			}	
		}
	}
	if(!foundVariable)
	{	
		for(vector<NLPIclassDefinition*>::iterator localListIter = classDefinition->definitionList.begin(); localListIter != classDefinition->definitionList.end(); localListIter++)
		{
			NLPIclassDefinition * targetClassDefinition = *localListIter;
			if(findVariableInParentClass(targetClassDefinition, variableName, variableType))
			{
				foundVariable = true;
			}
		}
	}
	return foundVariable;
}
#endif



#ifdef NLPI_INTERPRET_ACTION_PROPERTIES_AND_CONDITIONS_AS_FUNCTION_ARGUMENTS
void generateFunctionPropertyConditionArgumentsWithActionConceptInheritance(GIAentityNode * actionEntity, vector<NLPIitem*> * parameters)
{
	generateFunctionPropertyConditionArguments(actionEntity, parameters, false);
	
	#ifdef GIA_TRANSLATOR_DREAM_MODE_LINK_SPECIFIC_CONCEPTS_AND_ACTIONS
	//Part b: generate object initialisations based on action concepts (class inheritance)
	for(vector<GIAentityConnection*>::iterator entityNodeDefinitionListIterator = actionEntity->entityNodeDefinitionList->begin(); entityNodeDefinitionListIterator < actionEntity->entityNodeDefinitionList->end(); entityNodeDefinitionListIterator++)
	{
		GIAentityConnection * definitionConnection = (*entityNodeDefinitionListIterator);
		definitionConnection->parsedForNLPIcodeBlocks = true;
		GIAentityNode* definitionEntity = definitionConnection->entity;
		if(definitionEntity->isActionConcept)
		{
			generateFunctionPropertyConditionArguments(definitionEntity, parameters, true);
		}
	}
	#endif
}

void generateFunctionPropertyConditionArguments(GIAentityNode * actionEntity, vector<NLPIitem*> * parameters, bool performChildActionDuplicateCheck)
{
	for(vector<GIAentityConnection*>::iterator entityIter = actionEntity->conditionNodeList->begin(); entityIter != actionEntity->conditionNodeList->end(); entityIter++)
	{
		GIAentityNode * actionCondition = (*entityIter)->entity;
		bool alreadyAdded = false;
		if(performChildActionDuplicateCheck)
		{
			alreadyAdded = checkDuplicateCondition(actionCondition, parameters);
		}
		if(!alreadyAdded)
		{
			GIAentityNode * conditionObject = NULL;
			if(!(actionCondition->conditionObjectEntity->empty()))
			{
				conditionObject = (actionCondition->conditionObjectEntity->back())->entity;
			}					
			NLPIitem * argumentConditionItem = new NLPIitem(actionCondition, NLPI_ITEM_TYPE_FUNCTION_ARGUMENT_CONDITION);
			argumentConditionItem->className2 = generateClassName(conditionObject);
			argumentConditionItem->instanceName2 = generateInstanceName(conditionObject);
			parameters->push_back(argumentConditionItem);		
		}
	}
	for(vector<GIAentityConnection*>::iterator entityIter = actionEntity->propertyNodeList->begin(); entityIter != actionEntity->propertyNodeList->end(); entityIter++)				
	{
		//string actionProperty = *localListIter2;
		GIAentityNode * actionProperty = (*entityIter)->entity;
		bool alreadyAdded = false;
		if(performChildActionDuplicateCheck)
		{
			alreadyAdded = checkDuplicateProperty(actionProperty, parameters);
		}
		if(!alreadyAdded)
		{	
			NLPIitem * argumentPropertyItem = new NLPIitem(actionProperty, NLPI_ITEM_TYPE_FUNCTION_ARGUMENT_PROPERTY);
			parameters->push_back(argumentPropertyItem);		
		}
	}
}

bool checkDuplicateProperty(GIAentityNode * propertyEntity, vector<NLPIitem*> * parameters)
{
	bool alreadyAdded = false;
	for(vector<NLPIitem*>::iterator parametersIterator = parameters->begin(); parametersIterator < parameters->end(); parametersIterator++)
	{
		NLPIitem * currentItem = *parametersIterator;
		if(currentItem->itemType == NLPI_ITEM_TYPE_FUNCTION_ARGUMENT_PROPERTY)
		{
			if(generateClassName(propertyEntity) == currentItem->className)
			{
				alreadyAdded = true;
			}
		}
		
	}
	return alreadyAdded;
}

bool checkDuplicateCondition(GIAentityNode * conditionEntity, vector<NLPIitem*> * parameters)
{
	bool alreadyAdded = false;
	for(vector<NLPIitem*>::iterator parametersIterator = parameters->begin(); parametersIterator < parameters->end(); parametersIterator++)
	{
		NLPIitem * currentItem = *parametersIterator;
		if(currentItem->itemType == NLPI_ITEM_TYPE_FUNCTION_ARGUMENT_CONDITION)
		{
			GIAentityNode * conditionObjectEntity = NULL;
			if(!(conditionEntity->conditionObjectEntity->empty()))
			{
				conditionObjectEntity = (conditionEntity->conditionObjectEntity->back())->entity;
			}
			
			if((generateClassName(conditionEntity) == currentItem->className) && (generateClassName(conditionObjectEntity) == currentItem->className2))
			{
				alreadyAdded = true;
			}
		}
	}
	return alreadyAdded;
}

#endif

#ifdef NLPI_SUPPORT_INPUT_FILE_LISTS
string parseFunctionNameFromNLPIfunctionName(string NLPIfunctionName)
{
	//gets "fight" from "dog::fight"
	string functionName = "";
	bool foundFunctionOwnerClass = false;
	string functionOwnerName = "";
	parseFunctionNameFromNLPIfunctionName(NLPIfunctionName, &functionName, &functionOwnerName, &foundFunctionOwnerClass);	
	return functionName;
}

void parseFunctionNameFromNLPIfunctionName(string NLPIfunctionName, string * functionName, string * functionOwnerName, bool * foundFunctionOwnerClass)
{
	//gets "fight" from "dog::fight"
	*foundFunctionOwnerClass = false;
	*functionOwnerName = "";
	*functionName = NLPIfunctionName;
	int indexOfClassContext = NLPIfunctionName.find("::");
	if(indexOfClassContext != string::npos)
	{
		*functionName = NLPIfunctionName.substr(indexOfClassContext, NLPIfunctionName.length()-indexOfClassContext);
		*functionOwnerName = NLPIfunctionName.substr(0, indexOfClassContext);
		cout << "NLPIfunctionName = " << NLPIfunctionName << endl;
		cout << "functionName = " << *functionName << endl;
		cout << "functionOwnerName = " << *functionOwnerName << endl;
		*foundFunctionOwnerClass = true;
	}
}
#endif




