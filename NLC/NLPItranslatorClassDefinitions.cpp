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
 * File Name: NLPItranslatorClassDefinitions.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2013 Baxter AI (baxterai.com)
 * Project: Natural Language Programming Interface (compiler)
 * Project Version: 1e9b 25-November-2013
 * Requirements: requires text parsed by NLP Parser (eg Relex; available in .CFF format <relations>)
 *
 *******************************************************************************/



#include <ctime>
#include <cstdlib>	//for random number generation
#include <cmath>

#include "NLPItranslatorClassDefinitions.h"


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
						#ifdef NLPI_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS
						if(((targetEntity->isCondition) && !(targetEntity->isConcept)) || (i == GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTIONS))
						#else
						if((targetEntity->isAction) || (targetEntity->isActionConcept) || (targetEntity->isCondition) && !(targetEntity->isConcept))
						#endif
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

								NLPIitem * classDeclarationFunctionItem = new NLPIitem(targetEntity, NLPI_ITEM_TYPE_FUNCTION);	//added 1e1c
								targetClassDefinition->parameters.push_back(classDeclarationFunctionItem);
								if(!(targetEntity->actionObjectEntity->empty()))
								{							
									GIAentityNode * actionObject = (targetEntity->actionObjectEntity->back())->entity;
									NLPIitem * classDeclarationFunctionObjectItem = new NLPIitem(actionObject, NLPI_ITEM_TYPE_FUNCTION_OBJECT);	//for special case (as actions are referenced by instance)
									targetClassDefinition->parameters.push_back(classDeclarationFunctionObjectItem);
								}
								#ifdef NLPI_INTERPRET_ACTION_PROPERTIES_AND_CONDITIONS_AS_FUNCTION_ARGUMENTS
								//#ifdef NLPI_SUPPORT_INPUT_FILE_LISTS	//shouldn't this preprocessor requirement be enforced?
								generateFunctionPropertyConditionArgumentsWithActionConceptInheritance(targetEntity, &(targetClassDefinition->parameters));
								//#endif
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






