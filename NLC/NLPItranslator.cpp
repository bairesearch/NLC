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
 * Project Version: 1d3a 09-November-2013
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
				#ifdef NLPI_DEBUG
				cout << "actionEntity->entityName = " << actionEntity->entityName << endl;
				#endif
				//cout << "actionEntity->isAction = " << actionEntity->isAction << endl;
				//cout << "actionEntity->hasAssociatedInstance = " << actionEntity->hasAssociatedInstance << endl;

				if(checkSentenceIndexParsingCodeBlocks(actionEntity, sentenceIndex, true))
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


					NLPIcodeblock * functionExecuteCodeBlockInTree = NULL;
			
					if(actionHasObject)
					{
						NLPIitem * functionItem = new NLPIitem(actionEntity, NLPI_ITEM_TYPE_FUNCTION);
						bool objectRequiredTempVar = false;	//not used
						NLPIitem * objectItem = NULL;
						currentCodeBlockInTree = generateConditionBlocks(currentCodeBlockInTree, objectEntity, &objectItem, sentenceIndex, &objectRequiredTempVar);

						//cout << "h3" << endl;
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
						functionExecuteCodeBlockInTree = currentCodeBlockInTree;
						currentCodeBlockInTree = createCodeBlockExecute(currentCodeBlockInTree, functionItem, objectItem);
					}
					else if(actionHasSubject)
					{
						NLPIitem * functionItem = new NLPIitem(actionEntity, NLPI_ITEM_TYPE_FUNCTION);
						bool subjectRequiredTempVar = false;	//not used
						NLPIitem * subjectItem = NULL;
						currentCodeBlockInTree = generateConditionBlocks(currentCodeBlockInTree, subjectEntity, &subjectItem, sentenceIndex, &subjectRequiredTempVar);

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
				generateObjectInitialisationsBasedOnSubstanceConcepts(entity, &currentCodeBlockInTree, sentenceIndex);
				#endif				
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
		if(definitionEntity->isSubstanceConcept)
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
			//cout << "sentenceIndexA = " << sentenceIndex << endl;
			*currentCodeBlockInTree = createCodeBlockAddProperty(*currentCodeBlockInTree, entity, propertyEntity, sentenceIndex);
			entity->parsedForNLPIcodeBlocks = true;			//added 4 October 2013 NLPI1b6b  - used for quick access of instances already declared in current context 
			generateObjectInitialisationsBasedOnSubstanceConceptsRecurse(entity, propertyEntity, currentCodeBlockInTree, sentenceIndex);		//updated 9 November 2013 - support recursion of complex substance concept definition
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
			*currentCodeBlockInTree = createCodeBlockAddCondition(*currentCodeBlockInTree, entity, conditionEntity, sentenceIndex);
			entity->parsedForNLPIcodeBlocks = true;			//added 4 October 2013 NLPI1b6b  - used for quick access of instances already declared in current context 
			generateObjectInitialisationsBasedOnSubstanceConceptsRecurse(entity, conditionEntity, currentCodeBlockInTree, sentenceIndex);	//updated 9 November 2013 - support recursion of complex substance concept definition
		}
	}
}		
#endif


bool generateClassHeirarchy(vector<NLPIclassDefinition *> * classDefinitionList, vector<GIAentityNode*> * entityNodesActiveListComplete, int maxNumberSentences)
{	
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode * entityNode = *entityIter;
		if(!(entityNode->disabled))
		{
			string className = generateClassName(entityNode);
			#ifdef NLPI_CREATE_A_SEPARATE_CLASS_FOR_SUBSTANCE_CONCEPT_DEFINITIONS
			if(entityNode->isSubstanceConcept)
			{
				className = generateSubstanceConceptClassName(entityNode);
			}
			#endif
					
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
							targetName = generateInstanceName(targetEntity);
						}
						#ifdef NLPI_CREATE_A_SEPARATE_CLASS_FOR_SUBSTANCE_CONCEPT_DEFINITIONS
						else if((i == GIA_ENTITY_VECTOR_CONNECTION_TYPE_DEFINITIONS) && (targetEntity->isSubstanceConcept))
						{
							targetName = generateSubstanceConceptClassName(targetEntity);
						}
						#endif
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
							targetClassDefinition->functionNameSpecial = generateFunctionName(targetEntity);
							#ifdef NLPI_SUPPORT_INPUT_FILE_LISTS_CHECK_ACTION_SUBJECT_CONTENTS_FOR_IMPLICITLY_DECLARED_PARAMETERS
							targetClassDefinition->actionOrConditionInstance = targetEntity;
							#endif
						}
						
						#ifdef NLPI_DEBUG_PRINT_HIDDEN_CLASSES
						if((targetEntity->isCondition) && !(targetEntity->isConcept))
						#else
						if((targetEntity->isAction) || (targetEntity->isActionConcept) || (targetEntity->isCondition) && !(targetEntity->isConcept))	//CAN BE TEMPORARILY MODIFED FOR DEBUGGING
						#endif
						{
							targetClassDefinition->isActionOrConditionInstanceNotClass = true;
							//cout << "classDefinition->isActionOrConditionInstanceNotClass" << endl;
						}

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
								else
								{
									cout << "generateClassHeirarchy() error: condition has no object" << endl;
								}												
								targetClassDefinition->parameters.push_back(classDeclarationConditionsListItem);
							}						
						}	
						else if(i == GIA_ENTITY_VECTOR_CONNECTION_TYPE_DEFINITIONS) 
						{//declare inheritance
							#ifndef NLPI_CREATE_A_SEPARATE_CLASS_FOR_SUBSTANCE_CONCEPT_DEFINITIONS
							if(targetName != className)	//eg do not create a separate class for substance concept definitions
							{
							#endif
								//definitionList
								bool foundLocalClassDefinition = false;
								NLPIclassDefinition * localClassDefinition = findClassDefinition(&(classDefinition->definitionList), targetName, &foundLocalClassDefinition);	//see if class definition already exists
								if(!foundLocalClassDefinition)
								{
									//cout << "definitionList.push_back: " << targetClassDefinition->name << endl;
									classDefinition->definitionList.push_back(targetClassDefinition);
								}
							#ifndef NLPI_CREATE_A_SEPARATE_CLASS_FOR_SUBSTANCE_CONCEPT_DEFINITIONS
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

#ifdef NLPI_CREATE_A_SEPARATE_CLASS_FOR_SUBSTANCE_CONCEPT_DEFINITIONS
string generateSubstanceConceptClassName(GIAentityNode * substanceConceptEntity)
{
	string substanceConceptClassName = substanceConceptEntity->entityName;
	generateSubstanceConceptClassNameRecurse(substanceConceptEntity, &substanceConceptClassName);
	substanceConceptClassName = substanceConceptClassName + NLPI_CLASS_NAME_APPEND;
	return substanceConceptClassName;
}

void generateSubstanceConceptClassNameRecurse(GIAentityNode * substanceConceptEntity, string * substanceConceptClassName)
{
	for(vector<GIAentityConnection*>::iterator entityIter = substanceConceptEntity->conditionNodeList->begin(); entityIter != substanceConceptEntity->conditionNodeList->end(); entityIter++)
	{
		GIAentityNode * substanceConceptCondition = (*entityIter)->entity;
		if(!(substanceConceptCondition->conditionObjectEntity->empty()))
		{								
			GIAentityNode * substanceConceptConditionObject = (substanceConceptCondition->conditionObjectEntity->back())->entity;
			*substanceConceptClassName = *substanceConceptClassName + NLPI_SUBSTANCE_CONCEPT_CLASS_PREPEND + substanceConceptCondition->entityName + substanceConceptConditionObject->entityName + NLPI_SUBSTANCE_CONCEPT_CLASS_CONDITION;
			generateSubstanceConceptClassName(substanceConceptConditionObject);	//recurse in case of very detailed substance concept eg "red dogs next to blue cows"
		}
		else
		{
			cout << "generateSubstanceConceptClassNameRecurse() error: condition has no object" << endl;
		}					
	}
	for(vector<GIAentityConnection*>::iterator entityIter = substanceConceptEntity->propertyNodeList->begin(); entityIter != substanceConceptEntity->propertyNodeList->end(); entityIter++)				
	{
		GIAentityNode * substanceConceptProperty = (*entityIter)->entity;
		*substanceConceptClassName = *substanceConceptClassName + NLPI_SUBSTANCE_CONCEPT_CLASS_PREPEND + substanceConceptProperty->entityName + NLPI_SUBSTANCE_CONCEPT_CLASS_PROPERTY;
		generateSubstanceConceptClassName(substanceConceptProperty);	//recurse in case of very detailed substance concept eg "red dogs next to blue cows"
	}
}
#endif
			
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

void reconcileClassDefinitionListFunctionArgumentsBasedOnImplicitlyDeclaredVariablesInCurrentFunctionDefinition(NLPIcodeblock * firstCodeBlockInTree, vector<NLPIclassDefinition *> * classDefinitionList, string NLPIfunctionName)
{		
	//reconcile function arguments (both class function header and code function reference)
	string functionName = "";	
	string functionOwnerName = "";
	bool foundFunctionOwnerClass = false; 
	parseFunctionNameFromNLPIfunctionName(NLPIfunctionName, &functionName, &functionOwnerName, &foundFunctionOwnerClass);	//gets "fight" from "dog::fight"

	NLPIclassDefinition * classDefinitionFound = NULL;
	for(vector<NLPIclassDefinition*>::iterator classDefinitionIter = classDefinitionList->begin(); classDefinitionIter != classDefinitionList->end(); classDefinitionIter++)
	{	
		NLPIclassDefinition * currentClassDef = *classDefinitionIter;
		//cout << "currentClassDef->name = " << currentClassDef->name << endl;
		//cout << "functionOwnerName = " << functionOwnerName << endl;
		if((currentClassDef->name == generateClassName(functionOwnerName)) || !foundFunctionOwnerClass)
		{
			//cout << "currentClassDef->name = " << currentClassDef->name << endl;
			for(vector<NLPIclassDefinition*>::iterator localListIter = currentClassDef->functionList.begin(); localListIter != currentClassDef->functionList.end(); localListIter++)
			{
				NLPIclassDefinition * functionClassDefinition = *localListIter;
				//cout << "functionClassDefinition->functionNameSpecial = " << functionClassDefinition->functionNameSpecial << endl;
				//cout << "functionName = " << functionName << endl;
				if(functionClassDefinition->functionNameSpecial ==  generateFunctionName(functionName))
				{
					#ifdef NLPI_DEBUG
					cout << "reconcileClassDefinitionListFunctionArgumentsBasedOnImplicitlyDeclaredVariablesInCurrentFunctionDefinition() functionName = " << functionName << endl;
					#endif
					//contrast and compare function class arguments vs 

					findFormalFunctionArgumentCorrelateInExistingList(functionClassDefinition, &(firstCodeBlockInTree->parameters), classDefinitionList); 
				}	
			}
		}
	}
}
		
bool findFormalFunctionArgumentCorrelateInExistingList(NLPIclassDefinition * functionClassDefinition, vector<NLPIitem*> * formalFunctionArgumentList, vector<NLPIclassDefinition *> * classDefinitionList)
{
	vector<NLPIitem*> * existingFunctionArgumentList = &(functionClassDefinition->parameters);
	
	for(vector<NLPIitem*>::iterator parametersIterator = formalFunctionArgumentList->begin(); parametersIterator < formalFunctionArgumentList->end(); parametersIterator++)
	{
		NLPIitem * formalFunctionArgument = *parametersIterator;
		NLPIclassDefinition * classDefinitionCorrespondingToExistingFunctionArgument = NULL;
		NLPIclassDefinition * classDefinitionCorrespondingToFormalFunctionArgument = NULL;	//not used
		NLPIitem * existingFunctionArgument = NULL;	
		bool foundFormalFunctionArgumentCorrelateForExistingArgument = false;
		int foundFormalFunctionArgumentCorrelateForExistingArgumentInheritanceLevel = NLPI_SUPPORT_INPUT_FILE_LISTS_MAX_INHERITANCE_DEPTH_FOR_CLASS_CASTING;			
		if((formalFunctionArgument->itemType == NLPI_ITEM_TYPE_THIS_FUNCTION_ARGUMENT_INSTANCE) || (formalFunctionArgument->itemType == NLPI_ITEM_TYPE_THIS_FUNCTION_ARGUMENT_INSTANCE_PLURAL))
		{
			#ifdef NLPI_DEBUG
			cout << "formalFunctionArgument->className = " << formalFunctionArgument->className << endl;
			#endif
			for(vector<NLPIitem*>::iterator parametersIterator = existingFunctionArgumentList->begin(); parametersIterator < existingFunctionArgumentList->end(); parametersIterator++)
			{
				NLPIitem * currentExistingFunctionArgument = *parametersIterator;

				bool foundClassDefinitionCorrespondingToExistingFunctionArgument = false;
				for(vector<NLPIclassDefinition*>::iterator classDefinitionIter = classDefinitionList->begin(); classDefinitionIter != classDefinitionList->end(); classDefinitionIter++)
				{
					NLPIclassDefinition * currentClassDef = *classDefinitionIter;
					if(currentClassDef->name == currentExistingFunctionArgument->className)
					{
						classDefinitionCorrespondingToExistingFunctionArgument = currentClassDef;
						foundClassDefinitionCorrespondingToExistingFunctionArgument = true;
					}
				}

				if(foundClassDefinitionCorrespondingToExistingFunctionArgument)
				{
					#ifdef NLPI_DEBUG
					cout << "foundClassDefinitionCorrespondingToExistingFunctionArgument: " << classDefinitionCorrespondingToExistingFunctionArgument->name << endl;
					#endif
					if((formalFunctionArgument->itemType == NLPI_ITEM_TYPE_THIS_FUNCTION_ARGUMENT_INSTANCE_PLURAL) || (formalFunctionArgument->itemType == NLPI_ITEM_TYPE_THIS_FUNCTION_ARGUMENT_INSTANCE))
					{//CHECKTHIS; do not currently distinguish between plural and singular variables - this will need to be updated in future
						int inheritanceLevel = 0;
						NLPIclassDefinition * tempClassDef = NULL;
						//cout << "classDefinitionCorrespondingToExistingFunctionArgument->name = " << classDefinitionCorrespondingToExistingFunctionArgument->name << endl;
						//cout << "formalFunctionArgument->className = " << formalFunctionArgument->className << endl;
						if(findParentClass(classDefinitionCorrespondingToExistingFunctionArgument, formalFunctionArgument->className, 0, &inheritanceLevel, &tempClassDef))
						{
							//cout << "here2" << endl;
							if(inheritanceLevel < foundFormalFunctionArgumentCorrelateForExistingArgumentInheritanceLevel)
							{
								//cout << "foundFormalFunctionArgumentCorrelateForExistingArgument" << endl;
								foundFormalFunctionArgumentCorrelateForExistingArgument = true;
								foundFormalFunctionArgumentCorrelateForExistingArgumentInheritanceLevel = inheritanceLevel;
								classDefinitionCorrespondingToFormalFunctionArgument = tempClassDef;
								existingFunctionArgument = currentExistingFunctionArgument; 
							}
						}
					}
					else
					{
						//cout << "unsupported function argument: formalFunctionArgument->itemType = " << formalFunctionArgument->itemType << endl;
					}
				}
				else
				{	
					cout << "findFormalFunctionArgumentCorrelateInExistingList() error: !foundClassDefinitionCorrespondingToExistingFunctionArgument: " << currentExistingFunctionArgument->className << endl;
				}
			}
			if(foundFormalFunctionArgumentCorrelateForExistingArgument)
			{
				existingFunctionArgument->functionArgumentCertified = true;

				//store cast information for more generic class type passed as function argument
				if(existingFunctionArgument->className != formalFunctionArgument->className)
				{
					existingFunctionArgument->functionArgumentPassCastClassName = formalFunctionArgument->className;
					existingFunctionArgument->functionArgumentPassCastRequired = true;
				}
			}
			else
			{
				#ifdef NLPI_SUPPORT_INPUT_FILE_LISTS_CHECK_ACTION_SUBJECT_CONTENTS_FOR_IMPLICITLY_DECLARED_PARAMETERS
				bool foundFunctionArgumentInActionSubjectContents = false;
				GIAentityNode * actionEntity = functionClassDefinition->actionOrConditionInstance;
				if(!(actionEntity->actionSubjectEntity->empty()))
				{							
					GIAentityNode * actionSubject = (actionEntity->actionSubjectEntity->back())->entity;
					//cout << "actionSubject = " << actionSubject->entityName << endl;
					//cout << "formalFunctionArgument->className = " << formalFunctionArgument->className << endl;
					if(formalFunctionArgument->className == generateClassName(actionSubject))
					{
						foundFunctionArgumentInActionSubjectContents = true;
						#ifdef NLPI_DEBUG
						cout << "foundFunctionArgumentInActionSubjectContents: " << formalFunctionArgument->className << endl;
						#endif
						//formalFunctionArgument->formalFunctionArgumentCorrespondsToActionSubjectUseThisAlias = true;	//not done; this is now handled by generateConditionBlocks()	
					}
					/*//ignore conditions of actionSubject; they will need to be explicitly referenced by the function
					for(vector<GIAentityConnection*>::iterator entityIter = actionSubject->conditionNodeList->begin(); entityIter != actionSubject->conditionNodeList->end(); entityIter++)
					{
						GIAentityNode * actionCondition = (*entityIter)->entity;
					}
					*/
					for(vector<GIAentityConnection*>::iterator entityIter = actionSubject->propertyNodeList->begin(); entityIter != actionSubject->propertyNodeList->end(); entityIter++)				
					{
						GIAentityNode * actionProperty = (*entityIter)->entity;
						if(formalFunctionArgument->className == generateClassName(actionProperty))
						{//NB these implicitly declared parameters in the function definition will be referenced as plural (lists) not singular entities 
								//NO: check this is the case; eg the dog eats the pie; 'the dog' should be extracted from dogList if it was not passed as a parameter
								//1dXy: all parameters should be passed as lists (temporary lists should be created if specific variables require passing)
							foundFunctionArgumentInActionSubjectContents = true;
						}
					}
				}

				if(!foundFunctionArgumentInActionSubjectContents)
				{
					cout << "NLPI compiler warning: !foundFormalFunctionArgumentCorrelateForExistingArgument && !foundFunctionArgumentInActionSubjectContents (function arguments will not map): " << formalFunctionArgument->className << endl;
				#else
					cout << "NLPI compiler warning: !foundFormalFunctionArgumentCorrelateForExistingArgument (function arguments will not map): " << formalFunctionArgument->className << endl;
				#endif
					//add a new function argument to the existing function argument list
					NLPIitem * formalFunctionArgumentToAddExistingFunctionArgumentList = new NLPIitem(formalFunctionArgument);	//NLPI by default uses plural (lists) not singular entities
					existingFunctionArgumentList->push_back(formalFunctionArgumentToAddExistingFunctionArgumentList);		
				#ifdef NLPI_SUPPORT_INPUT_FILE_LISTS_CHECK_ACTION_SUBJECT_CONTENTS_FOR_IMPLICITLY_DECLARED_PARAMETERS
				}
				#endif
			}
		}
	}
}

bool findParentClass(NLPIclassDefinition * classDefinition, string variableName, int inheritanceLevel, int * maxInheritanceLevel, NLPIclassDefinition ** parentClass)
{
	bool foundVariable = false;
	if(classDefinition->name == variableName)
	{
		foundVariable = true;
		*maxInheritanceLevel = inheritanceLevel;
		*parentClass = classDefinition;
	}
	else 
	{	
		for(vector<NLPIclassDefinition*>::iterator localListIter = classDefinition->definitionList.begin(); localListIter != classDefinition->definitionList.end(); localListIter++)
		{
			NLPIclassDefinition * targetClassDefinition = *localListIter;
			if(findParentClass(targetClassDefinition, variableName, (inheritanceLevel+1), maxInheritanceLevel, parentClass))
			{
				foundVariable = true;
			}
		}
	}
	return foundVariable;
}

int getFilesFromFileList2(string inputListFileName, vector<string> * inputTextFileNameList)
{
	bool result = true;
	int numberOfInputFilesInList = 0;
	ifstream parseFileObject(inputListFileName.c_str());
	if(!parseFileObject.rdbuf( )->is_open( ))
	{
		//txt file does not exist in current directory.
		cout << "Error: input list file does not exist in current directory: " << inputListFileName << endl;
		result = false;
	}
	else
	{
		char currentToken;
		int fileNameIndex = 0;
		int charCount = 0;
		string currentFileName = "";
		while(parseFileObject.get(currentToken))
		{
			if(currentToken == CHAR_NEWLINE)
			{
				inputTextFileNameList->push_back(currentFileName);
				#ifdef GIA_MAIN_DEBUG
				//cout << "currentFileName = " << currentFileName << endl;
				#endif
				currentFileName = "";
				fileNameIndex++;
			}
			else
			{
				currentFileName = currentFileName + currentToken;
			}
			charCount++;
		}
		numberOfInputFilesInList = fileNameIndex;
	}
	#ifdef GIA_MAIN_DEBUG
	//cout << "numberOfInputFilesInList = " << numberOfInputFilesInList << endl;
	#endif
	return numberOfInputFilesInList;
}

#endif




