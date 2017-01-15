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
 * File Name: NLCtranslatorClassDefinitions.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2014 Baxter AI (baxterai.com)
 * Project: Natural Language Programming Interface (compiler)
 * Project Version: 1f14c 08-June-2014
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/



#include <ctime>
#include <cstdlib>	//for random number generation
#include <cmath>

#include "NLCtranslatorClassDefinitions.h"


bool generateClassHeirarchy(vector<NLCclassDefinition *> * classDefinitionList, vector<GIAentityNode*> * entityNodesActiveListComplete, int maxNumberSentences)
{
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode * entityNode = *entityIter;
		if(!(entityNode->disabled))
		{
			string className = generateClassName(entityNode);
			#ifdef NLC_CREATE_A_SEPARATE_CLASS_FOR_SUBSTANCE_CONCEPT_DEFINITIONS
			if(entityNode->isSubstanceConcept)
			{
				className = generateSubstanceConceptClassName(entityNode);
			}
			#endif

			//cout << "className = " << className << endl;
			bool foundClassDefinition = false;
			NLCclassDefinition * classDefinition = findClassDefinition(classDefinitionList, className, &foundClassDefinition);	//see if class definition already exists
			if(!foundClassDefinition)
			{
				classDefinition = new NLCclassDefinition(className);
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

					#ifdef NLC_SUPPORT_CONDITION_LOGICAL_OPERATIONS
					if(!(connection->NLCconditionLogicalOperations) && !(targetEntity->NLCconditionLogicalOperations))
					{
					#endif
						//cout << "targetEntity->entityName = " << targetEntity->entityName << endl;
						//cout << "targetEntity->isConcept = " << targetEntity->isConcept << endl;
						if(!(targetEntity->disabled))
						{
							string targetName = "";
							string targetClassName = "";
							if(i == GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTIONS)	//in GIA actions are treated as special connections with intermediary nodes
							{
								targetName = generateInstanceName(targetEntity);
							}
							#ifdef NLC_CREATE_A_SEPARATE_CLASS_FOR_SUBSTANCE_CONCEPT_DEFINITIONS
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
							NLCclassDefinition * targetClassDefinition = findClassDefinition(classDefinitionList, targetName, &foundTargetClassDefinition);	//see if class definition already exists
							if(!foundTargetClassDefinition)
							{
								//cout << "new NLCclassDefinition(" << targetName << endl;
								targetClassDefinition = new NLCclassDefinition(targetName);
								classDefinitionList->push_back(targetClassDefinition);
							}

							if(i == GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTIONS)
							{
								targetClassDefinition->functionNameSpecial = generateFunctionName(targetEntity);
								#ifdef NLC_SUPPORT_INPUT_FILE_LISTS_CHECK_ACTION_SUBJECT_CONTENTS_FOR_IMPLICITLY_DECLARED_PARAMETERS
								targetClassDefinition->actionOrConditionInstance = targetEntity;
								#endif
							}

							#ifdef NLC_DEBUG_PRINT_HIDDEN_CLASSES
							if(1)	//removed; || (if((targetEntity->isCondition) && !(targetEntity->isConcept)) 16 April 2014
							#else
							#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS
							if((i == GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTIONS))	//removed; ((targetEntity->isCondition) && !(targetEntity->isConcept) ||) 16 April 2014
							#else
							if((targetEntity->isAction) || (targetEntity->isActionConcept) && !(targetEntity->isConcept))	//removed; || (targetEntity->isCondition) 16 April 2014
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
								NLCclassDefinition * localClassDefinition = findClassDefinition(&(classDefinition->propertyList), targetName, &foundLocalClassDefinition);	//see if class definition already exists
								if(!foundLocalClassDefinition)
								{
									//cout << "propertyList.push_back: " << targetClassDefinition->name << endl;
									classDefinition->propertyList.push_back(targetClassDefinition);

									NLCitem * classDeclarationPropertiesListItem = new NLCitem(targetEntity, NLC_ITEM_TYPE_CLASS_DECLARATION_PROPERTY_LIST);
									targetClassDefinition->parameters.push_back(classDeclarationPropertiesListItem);
								}
							}
							else if(i == GIA_ENTITY_VECTOR_CONNECTION_TYPE_CONDITIONS)
							{//declare conditions
								//conditionList
								bool foundLocalClassDefinition = false;
								NLCclassDefinition * localClassDefinition = findClassDefinition(&(classDefinition->conditionList), targetName, &foundLocalClassDefinition);	//see if class definition already exists
								if(!foundLocalClassDefinition)
								{
									//cout << "conditionList.push_back: " << targetClassDefinition->className << endl;
									classDefinition->conditionList.push_back(targetClassDefinition);

									NLCitem * classDeclarationConditionsListItem = new NLCitem(targetEntity, NLC_ITEM_TYPE_CLASS_DECLARATION_CONDITION_LIST);
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
								#ifndef NLC_CREATE_A_SEPARATE_CLASS_FOR_SUBSTANCE_CONCEPT_DEFINITIONS
								if(targetName != className)	//eg do not create a separate class for substance concept definitions
								{
								#endif
									//definitionList
									bool foundLocalClassDefinition = false;
									NLCclassDefinition * localClassDefinition = findClassDefinition(&(classDefinition->definitionList), targetName, &foundLocalClassDefinition);	//see if class definition already exists
									if(!foundLocalClassDefinition)
									{
										//cout << "definitionList.push_back: " << targetClassDefinition->name << endl;
										classDefinition->definitionList.push_back(targetClassDefinition);
									}
								#ifndef NLC_CREATE_A_SEPARATE_CLASS_FOR_SUBSTANCE_CONCEPT_DEFINITIONS
								}
								#endif
							}
							else if(i == GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTIONS)
							{//declare functions
								//functionList
								bool foundLocalClassDefinition = false;
								NLCclassDefinition * localClassDefinition = findClassDefinition(&(classDefinition->functionList), targetName, &foundLocalClassDefinition);	//see if class definition already exists
								if(!foundLocalClassDefinition)
								{
									//cout << "functionList.push_back: " << targetClassDefinition->name << endl;
									classDefinition->functionList.push_back(targetClassDefinition);

									NLCitem * classDeclarationFunctionItem = new NLCitem(targetEntity, NLC_ITEM_TYPE_FUNCTION);	//added 1e1c
									targetClassDefinition->parameters.push_back(classDeclarationFunctionItem);
									if(!(targetEntity->actionObjectEntity->empty()))
									{
										GIAentityNode * actionObject = (targetEntity->actionObjectEntity->back())->entity;
										NLCitem * classDeclarationFunctionObjectItem = new NLCitem(actionObject, NLC_ITEM_TYPE_FUNCTION_OBJECT);	//for special case (as actions are referenced by instance)
										targetClassDefinition->parameters.push_back(classDeclarationFunctionObjectItem);
									}
									#ifdef NLC_INTERPRET_ACTION_PROPERTIES_AND_CONDITIONS_AS_FUNCTION_ARGUMENTS
									//#ifdef NLC_SUPPORT_INPUT_FILE_LISTS	//shouldn't this preprocessor requirement be enforced?
									generateFunctionPropertyConditionArgumentsWithActionConceptInheritance(targetEntity, &(targetClassDefinition->parameters));
									//#endif
									#endif
								}
							}
						}
					#ifdef NLC_SUPPORT_CONDITION_LOGICAL_OPERATIONS
					}
					/*
					else
					{
						cout << "entityNode->entityName = " << entityNode->entityName << endl;
						cout << "i = " << i << endl;
						cout << "targetEntity->entityName = " << targetEntity->entityName << endl;
					}
					*/
					#endif
				}
			}
		}
	}


	#ifdef NLC_PREVENT_INHERITANCE_DOUBLE_DECLARATIONS_OF_CLASS_LIST_VARIABLES
	//disable all double declarations
	for(vector<NLCclassDefinition*>::iterator classDefinitionIter = classDefinitionList->begin(); classDefinitionIter != classDefinitionList->end(); classDefinitionIter++)
	{
		NLCclassDefinition * classDefinition = *classDefinitionIter;

		eraseDuplicateClassDefinitionSublistItemIfFoundInParentClassDefinitionSublist(classDefinition, &(classDefinition->propertyList), GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTIONS);
		eraseDuplicateClassDefinitionSublistItemIfFoundInParentClassDefinitionSublist(classDefinition, &(classDefinition->conditionList), GIA_ENTITY_VECTOR_CONNECTION_TYPE_CONDITIONS);
		eraseDuplicateClassDefinitionSublistItemIfFoundInParentClassDefinitionSublist(classDefinition, &(classDefinition->functionList), GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTIONS);
	}
	#endif

	#ifdef NLC_CLASS_DEFINITIONS_USE_GENERIC_LIBRARY_ENTITY_CLASS
	//create a high level "genericEntity" class definition (for generic NLC library functions - that cannot rely on specific class names)
	for(vector<NLCclassDefinition*>::iterator classDefinitionIter = classDefinitionList->begin(); classDefinitionIter != classDefinitionList->end(); classDefinitionIter++)
	{
		NLCclassDefinition * classDefinition = *classDefinitionIter;
		//cout << "0classDefinition = " << classDefinition->name << endl;

		if(classDefinition->definitionList.empty() && (classDefinition->name != generateClassName(NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE)))
		{
			string targetName = generateClassName(NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE);
			//cout << "targetName = " << targetName << endl;
			bool foundTargetClassDefinition = false;
			NLCclassDefinition * targetClassDefinition = findClassDefinition(classDefinitionList, targetName, &foundTargetClassDefinition);	//see if class definition already exists

			if(!foundTargetClassDefinition)
			{
				//cout << "new NLCclassDefinition(" << targetName << endl;
				targetClassDefinition = new NLCclassDefinition(targetName);
				//classDefinitionList->push_back(targetClassDefinition);	//breaks iteration
				classDefinitionIter = classDefinitionList->insert(classDefinitionIter, targetClassDefinition);
			}

			classDefinition->definitionList.push_back(targetClassDefinition);
		}
	}	
	#endif

	return true;
}

#ifdef NLC_CREATE_A_SEPARATE_CLASS_FOR_SUBSTANCE_CONCEPT_DEFINITIONS
string generateSubstanceConceptClassName(GIAentityNode * substanceConceptEntity)
{
	string substanceConceptClassName = substanceConceptEntity->entityName;
	generateSubstanceConceptClassNameRecurse(substanceConceptEntity, &substanceConceptClassName);
	substanceConceptClassName = substanceConceptClassName + NLC_CLASS_NAME_APPEND;
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
			*substanceConceptClassName = *substanceConceptClassName + NLC_SUBSTANCE_CONCEPT_CLASS_PREPEND + substanceConceptCondition->entityName + substanceConceptConditionObject->entityName + NLC_SUBSTANCE_CONCEPT_CLASS_CONDITION;
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
		*substanceConceptClassName = *substanceConceptClassName + NLC_SUBSTANCE_CONCEPT_CLASS_PREPEND + substanceConceptProperty->entityName + NLC_SUBSTANCE_CONCEPT_CLASS_PROPERTY;
		generateSubstanceConceptClassName(substanceConceptProperty);	//recurse in case of very detailed substance concept eg "red dogs next to blue cows"
	}
}
#endif

#ifdef NLC_PREVENT_INHERITANCE_DOUBLE_DECLARATIONS_OF_CLASS_LIST_VARIABLES
void eraseDuplicateClassDefinitionSublistItemIfFoundInParentClassDefinitionSublist(NLCclassDefinition * classDefinition, vector<NLCclassDefinition*> * classDefinitionSublist, int variableType)
{
	for(vector<NLCclassDefinition*>::iterator localListIter = classDefinitionSublist->begin(); localListIter != classDefinitionSublist->end();)
	{
		bool localListIterErased = false;
		NLCclassDefinition * variableClassDefinition = *localListIter;
		string variableName = variableClassDefinition->name;
		for(vector<NLCclassDefinition*>::iterator parentListIter = classDefinition->definitionList.begin(); parentListIter != classDefinition->definitionList.end(); parentListIter++)
		{
			if(!localListIterErased)
			{
				NLCclassDefinition * targetClassDefinition = *parentListIter;
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

bool findVariableInParentClass(NLCclassDefinition * classDefinition, string variableName, int variableType)
{
	bool foundVariable = false;
	if(variableType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_PROPERTIES)
	{
		for(vector<NLCclassDefinition*>::iterator localListIter = classDefinition->propertyList.begin(); localListIter != classDefinition->propertyList.end(); localListIter++)
		{
			NLCclassDefinition * targetClassDefinition = *localListIter;
			string targetName = targetClassDefinition->name;
			if(targetName == variableName)
			{
				foundVariable = true;
			}
		}
	}
	else if(variableType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_CONDITIONS)
	{
		for(vector<NLCclassDefinition*>::iterator localListIter = classDefinition->conditionList.begin(); localListIter != classDefinition->conditionList.end(); localListIter++)
		{
			NLCclassDefinition * targetClassDefinition = *localListIter;
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
		for(vector<NLCclassDefinition*>::iterator localListIter = classDefinition->functionList.begin(); localListIter != classDefinition->functionList.end(); localListIter++)
		{
			NLCclassDefinition * targetClassDefinition = *localListIter;
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
		for(vector<NLCclassDefinition*>::iterator localListIter = classDefinition->definitionList.begin(); localListIter != classDefinition->definitionList.end(); localListIter++)
		{
			NLCclassDefinition * targetClassDefinition = *localListIter;
			if(findVariableInParentClass(targetClassDefinition, variableName, variableType))
			{
				foundVariable = true;
			}
		}
	}
	return foundVariable;
}
#endif



#ifdef NLC_INTERPRET_ACTION_PROPERTIES_AND_CONDITIONS_AS_FUNCTION_ARGUMENTS
void generateFunctionPropertyConditionArgumentsWithActionConceptInheritance(GIAentityNode * actionEntity, vector<NLCitem*> * parameters)
{
	generateFunctionPropertyConditionArguments(actionEntity, parameters, false);

	#ifdef GIA_TRANSLATOR_DREAM_MODE_LINK_SPECIFIC_CONCEPTS_AND_ACTIONS
	//Part b: generate object initialisations based on action concepts (class inheritance)
	for(vector<GIAentityConnection*>::iterator entityNodeDefinitionListIterator = actionEntity->entityNodeDefinitionList->begin(); entityNodeDefinitionListIterator < actionEntity->entityNodeDefinitionList->end(); entityNodeDefinitionListIterator++)
	{
		GIAentityConnection * definitionConnection = (*entityNodeDefinitionListIterator);
		definitionConnection->parsedForNLCcodeBlocks = true;
		GIAentityNode* definitionEntity = definitionConnection->entity;
		if(definitionEntity->isActionConcept)
		{
			generateFunctionPropertyConditionArguments(definitionEntity, parameters, true);
		}
	}
	#endif
}

void generateFunctionPropertyConditionArguments(GIAentityNode * actionEntity, vector<NLCitem*> * parameters, bool performChildActionDuplicateCheck)
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
			NLCitem * argumentConditionItem = new NLCitem(actionCondition, NLC_ITEM_TYPE_FUNCTION_ARGUMENT_CONDITION);
			argumentConditionItem->className2 = generateClassName(conditionObject);
			argumentConditionItem->instanceName2 = generateInstanceName(conditionObject);
			parameters->push_back(argumentConditionItem);
		}
	}
	for(vector<GIAentityConnection*>::iterator entityIter = actionEntity->propertyNodeList->begin(); entityIter != actionEntity->propertyNodeList->end(); entityIter++)
	{
		GIAentityNode * actionProperty = (*entityIter)->entity;
		bool alreadyAdded = false;
		if(performChildActionDuplicateCheck)
		{
			alreadyAdded = checkDuplicateProperty(actionProperty, parameters);
		}
		if(!alreadyAdded)
		{
			NLCitem * argumentPropertyItem = new NLCitem(actionProperty, NLC_ITEM_TYPE_FUNCTION_ARGUMENT_PROPERTY);
			parameters->push_back(argumentPropertyItem);
		}
	}
}

bool checkDuplicateProperty(GIAentityNode * propertyEntity, vector<NLCitem*> * parameters)
{
	bool alreadyAdded = false;
	for(vector<NLCitem*>::iterator parametersIterator = parameters->begin(); parametersIterator < parameters->end(); parametersIterator++)
	{
		NLCitem * currentItem = *parametersIterator;
		if(currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_ARGUMENT_PROPERTY)
		{
			if(generateClassName(propertyEntity) == currentItem->className)
			{
				alreadyAdded = true;
			}
		}

	}
	return alreadyAdded;
}

bool checkDuplicateCondition(GIAentityNode * conditionEntity, vector<NLCitem*> * parameters)
{
	bool alreadyAdded = false;
	for(vector<NLCitem*>::iterator parametersIterator = parameters->begin(); parametersIterator < parameters->end(); parametersIterator++)
	{
		NLCitem * currentItem = *parametersIterator;
		if(currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_ARGUMENT_CONDITION)
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






