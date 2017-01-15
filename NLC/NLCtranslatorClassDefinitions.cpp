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
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2015 Baxter AI (baxterai.com)
 * Project: Natural Language Programming Interface (compiler)
 * Project Version: 1o1d 07-February-2015
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/


#include "NLCtranslatorClassDefinitions.h"
#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS_ADVANCED
#include "GIAtranslatorDefs.h"
#endif
#ifdef NLC_CLASS_DEFINITIONS_DO_NOT_DEFINE_INHERITANCE_FOR_REDEFINITIONS
#include "NLCtranslatorCodeBlocksOperations.h"	//required for getSameReferenceSetUniqueParent()
#include "GIAtranslatorOperations.h"	//required for getPrimaryConceptNodeDefiningInstance()
#endif

bool generateClassHeirarchy(vector<NLCclassDefinition* >* classDefinitionList, vector<GIAentityNode*>* entityNodesActiveListComplete, NLCclassDefinitionFunctionDependency* parentFunctionDependency, vector<NLCclassDefinitionFunctionDependency*>* functionDependencyList)
{
	bool result = true;
	
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode* entityNode = *entityIter;

		//valid class checks added 1g12f 14-July-2014
		if(generateClassHeirarchyValidClassChecks(entityNode))
		{
			if(!(entityNode->disabled))
			{
				string className = generateClassName(entityNode);
				#ifdef NLC_CREATE_A_SEPARATE_CLASS_FOR_SUBSTANCE_CONCEPT_DEFINITIONS
				if(entityNode->isSubstanceConcept)
				{
					className = generateSubstanceConceptClassName(entityNode);
				}
				#endif

				bool foundClassDefinition = false;
				NLCclassDefinition* classDefinition = findClassDefinition(classDefinitionList, className, &foundClassDefinition);	//see if class definition already exists
				if(!foundClassDefinition)
				{
					classDefinition = new NLCclassDefinition(className);
					classDefinitionList->push_back(classDefinition);
				}
				
				#ifdef NLC_DEBUG
				cout << "generateClassHeirarchy: entityNode->entityName = " << entityNode->entityName << endl;
				#endif

				for(int i=0; i<GIA_ENTITY_NUMBER_OF_VECTOR_CONNECTION_TYPES; i++)
				{
					for(vector<GIAentityConnection*>::iterator connectionIter = entityNode->entityVectorConnectionsArray[i].begin(); connectionIter != entityNode->entityVectorConnectionsArray[i].end(); connectionIter++)
					{
						GIAentityConnection* connection = *connectionIter;
						GIAentityNode* targetEntity = connection->entity;

						#ifdef NLC_USE_ADVANCED_REFERENCING_SUPPORT_ALIASES
						if(!(connection->isAlias))
						{
						#endif
							//valid class contents checks added 1g12f 14-July-2014
							if(generateClassHeirarchyTargetValidClassChecks(targetEntity))
							{
								if(!(targetEntity->disabled))
								{
									#ifdef NLC_DEBUG
									cout << "generateClassHeirarchy(): targetEntity->entityName = " << targetEntity->entityName << endl;
									#endif
									
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
									NLCclassDefinition* targetClassDefinition = NULL;
									if(i == GIA_ENTITY_VECTOR_CONNECTION_TYPE_CONDITIONS)
									{	
										targetClassDefinition = findClassDefinitionCondition(classDefinitionList, targetEntity, &foundTargetClassDefinition);	//see if class definition already exists
									}
									else
									{
										targetClassDefinition = findClassDefinition(classDefinitionList, targetName, &foundTargetClassDefinition);	//see if class definition already exists
									}
									
									if(!foundTargetClassDefinition)
									{
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
									if(i == GIA_ENTITY_VECTOR_CONNECTION_TYPE_CONDITIONS)
									{
										targetClassDefinition->isConditionInstance = true;
									}

									#ifdef NLC_DEBUG_PRINT_HIDDEN_CLASSES
									if(1)	//removed; || (if((targetEntity->isCondition) && !(targetEntity->isConcept)) 16 April 2014
									#else
									#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS
									if((i == GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTIONS) || (i == GIA_ENTITY_VECTOR_CONNECTION_TYPE_CONDITIONS))	//removed; ((targetEntity->isCondition) && !(targetEntity->isConcept) ||) 16 April 2014	//restored || (i == GIA_ENTITY_VECTOR_CONNECTION_TYPE_CONDITIONS) 1m3a
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
										NLCclassDefinition* localClassDefinition = findClassDefinition(&(classDefinition->propertyList), targetName, &foundLocalClassDefinition);	//see if class definition already exists
										if(!foundLocalClassDefinition)
										{
											#ifdef NLC_DEBUG
											//cout << "generateClassHeirarchy(): classDefinition->propertyList.push_back: " << targetClassDefinition->name << endl;
											#endif
											
											classDefinition->propertyList.push_back(targetClassDefinition);

											NLCitem* classDeclarationPropertiesListItem = new NLCitem(targetEntity, NLC_ITEM_TYPE_CLASS_DECLARATION_PROPERTY_LIST);
											targetClassDefinition->parameters.push_back(classDeclarationPropertiesListItem);
										}
									}
									else if(i == GIA_ENTITY_VECTOR_CONNECTION_TYPE_CONDITIONS)
									{//declare conditions
										//conditionList
										if(!generateClassHeirarchyCondition(classDefinition, targetClassDefinition, targetEntity))
										{
											result = false;
										}

										#ifdef NLC_NORMALISE_TWOWAY_PREPOSITIONS_DUAL_CONDITION_LINKS_DISABLED
										if(targetEntity->conditionTwoWay)
										{
											if(!(targetEntity->conditionObjectEntity->empty()))
											{
												string conditionObjectClassName = generateClassName((targetEntity->conditionObjectEntity->back())->entity);
												bool foundClassDefinitionInverse = false;
												NLCclassDefinition* classDefinitionInverse = findClassDefinition(classDefinitionList, conditionObjectClassName, &foundClassDefinitionInverse);	//see if class definition already exists
												if(!foundClassDefinitionInverse)
												{
													classDefinitionInverse = new NLCclassDefinition(conditionObjectClassName);
													classDefinitionList->push_back(classDefinitionInverse);
												}
				
												GIAentityNode* conditionEntity = targetEntity;
												GIAentityNode* conditionEntityInverse = NULL;
												conditionEntityInverse = generateInverseConditionEntity(conditionEntity);
												#ifdef NLC_DEBUG
												cout << "conditionEntityInverse: conditionEntityInverse = " << conditionEntityInverse->entityName << endl;
												#endif
												bool foundTargetClassDefinitionInverse = false;
												NLCclassDefinition* targetClassDefinitionInverse = findClassDefinitionCondition(classDefinitionList, conditionEntityInverse, &foundTargetClassDefinition);	//see if class definition already exists
												if(!foundTargetClassDefinitionInverse)
												{
													targetClassDefinitionInverse = new NLCclassDefinition(generateClassName(conditionEntityInverse));
													classDefinitionList->push_back(targetClassDefinitionInverse);
												}
												targetClassDefinitionInverse->isConditionInstance = true;
												targetClassDefinitionInverse->isActionOrConditionInstanceNotClass = true;

												if(!generateClassHeirarchyCondition(classDefinitionInverse, targetClassDefinitionInverse, conditionEntityInverse))
												{
													result = false;
												}
											}
										}
										#endif
									}
									else if(i == GIA_ENTITY_VECTOR_CONNECTION_TYPE_DEFINITIONS)
									{//declare inheritance
										#ifdef NLC_CLASS_DEFINITIONS_DO_NOT_DEFINE_INHERITANCE_FOR_REDEFINITIONS
										#ifndef NLC_SUPPORT_REDEFINITIONS_FOR_IMMEDIATELY_DECLARED_INDEFINITE_ENTITIES
										//chickens are animals. an animal is a chicken. In practice this will not be implemented because GIA interprets indefinite-indefinite definitions as substance concepts. redefinitions are generally not implied for indefinite children (eg "an animal" in "an animal is a chicken") because they are ambiguous; this example either means a) animals are chickens (ie is a substanceConcept-substanceConcept definition; not a redefinition - and happens to be an incorrect statement based on aprior knowledge about the animal kingdom because we know chickens are animals not vice versa), or b) a newly declared animal is cast to a chicken (a specific version of animal, assuming "chickens are animals" has been declared)
										bool indefiniteChild = false;
										if(!isDefiniteEntity(entityNode))
										{
											bool parseConditionParents = true;	//default value
											bool foundDefiniteParentEntity = false;
											bool checkIsDefinite = true;
											GIAentityNode* parentTemp = getSameReferenceSetUniqueParent(entityNode, connection->sentenceIndexTemp, NULL, &foundDefiniteParentEntity, parseConditionParents, checkIsDefinite);
											if(!foundDefiniteParentEntity)
											{
												indefiniteChild = true;
											}
										}
										#endif
										bool parentClassIsChildOfTheChildClass = isParentClassAChildOfChildClass(entityNode, targetEntity);
										#ifdef NLC_SUPPORT_REDEFINITIONS_FOR_IMMEDIATELY_DECLARED_INDEFINITE_ENTITIES
										if(!parentClassIsChildOfTheChildClass)
										#else
										if(indefiniteChild || !parentClassIsChildOfTheChildClass)
										#endif
										{	
										#endif
											#ifndef NLC_CREATE_A_SEPARATE_CLASS_FOR_SUBSTANCE_CONCEPT_DEFINITIONS
											if(targetName != className)	//eg do not create a separate class for substance concept definitions
											{
											#endif
												//definitionList
												bool foundLocalClassDefinition = false;
												NLCclassDefinition* localClassDefinition = findClassDefinition(&(classDefinition->definitionList), targetName, &foundLocalClassDefinition);	//see if class definition already exists
												if(!foundLocalClassDefinition)
												{
													#ifdef NLC_DEBUG
													//cout << "generateClassHeirarchy(): classDefinition->definitionList.push_back: " << targetClassDefinition->name << endl;
													#endif

													classDefinition->definitionList.push_back(targetClassDefinition);
												}
											#ifndef NLC_CREATE_A_SEPARATE_CLASS_FOR_SUBSTANCE_CONCEPT_DEFINITIONS
											}
											#endif
										#ifdef NLC_CLASS_DEFINITIONS_DO_NOT_DEFINE_INHERITANCE_FOR_REDEFINITIONS
										}
										#endif
									}
									#ifndef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE
									else if(i == GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTIONS)
									{//declare functions
										//functionList
										bool foundLocalClassDefinition = false;
										NLCclassDefinition* localClassDefinition = findClassDefinition(&(classDefinition->functionList), targetName, &foundLocalClassDefinition);	//see if class definition already exists	//note this check will not work for functions because they are added by instance 
										if(!foundLocalClassDefinition)
										{
											bool hasActionObject = false;
											string actionObjectName = "";
											GIAentityNode* actionObject = NULL;
											if(!(targetEntity->actionObjectEntity->empty()))
											{
												actionObject = (targetEntity->actionObjectEntity->back())->entity;
												hasActionObject = true;
												actionObjectName = actionObject->entityName;
											}

											#ifdef NLC_DEBUG
											//cout << "generateClassHeirarchy(): classDefinition->functionList.push_back: " << targetClassDefinition->name << endl;
											#endif
											classDefinition->functionList.push_back(targetClassDefinition);

											#ifdef NLC_FUNCTIONS_SUPPORT_PLURAL_SUBJECTS
											//hasActionOwner is true for all actions (targetClassDefinition) with subjects (classDefinition);
											//added 1l1a for dynamic casting of children
											NLCitem* classDeclarationFunctionOwnerItem = new NLCitem(entityNode, NLC_ITEM_TYPE_FUNCTION_DECLARATION_ARGUMENT_FUNCTION_OWNER);
											targetClassDefinition->parameters.push_back(classDeclarationFunctionOwnerItem);
											#endif
												
											NLCitem* classDeclarationFunctionItem = new NLCitem(targetEntity, NLC_ITEM_TYPE_FUNCTION_DECLARATION_ARGUMENT_FUNCTION);	//added 1e1c
											targetClassDefinition->parameters.push_back(classDeclarationFunctionItem);

											if(hasActionObject)
											{
												NLCitem* classDeclarationFunctionObjectItem = new NLCitem(actionObjectName, NLC_ITEM_TYPE_FUNCTION_DECLARATION_ARGUMENT_FUNCTION_OBJECT);	//for special case (as actions are referenced by instance)
												targetClassDefinition->parameters.push_back(classDeclarationFunctionObjectItem);
											}

											#ifdef NLC_RECORD_ACTION_HISTORY
											bool foundClassDefinitionAction = false;
											string actionClassName = generateClassName(targetEntity);
											NLCclassDefinition* classDefinitionAction = findClassDefinition(classDefinitionList, actionClassName, &foundClassDefinitionAction);	//see if class definition already exists
											if(!foundClassDefinitionAction)
											{
												classDefinitionAction = new NLCclassDefinition(actionClassName);
												classDefinitionList->push_back(classDefinitionAction);
											}

											bool foundLocalClassDefinitionAction = false;
											NLCclassDefinition* localClassDefinitionAction = findClassDefinition(&(classDefinition->actionList), actionClassName, &foundLocalClassDefinitionAction);	//see if class definition already exists
											if(!foundLocalClassDefinitionAction)
											{
												classDefinition->actionList.push_back(classDefinitionAction);

											}									
											bool foundLocalClassDefinitionActionOwner = false;
											string actionOwnerClassName = className;
											NLCclassDefinition* localClassDefinitionActionOwner = findClassDefinition(&(classDefinitionAction->actionSubjectList), actionOwnerClassName, &foundLocalClassDefinitionActionOwner);	//see if class definition already exists
											if(!foundLocalClassDefinitionActionOwner)
											{
												classDefinitionAction->actionSubjectList.push_back(classDefinition);
											}		
											
											if(hasActionObject)
											{
												bool foundClassDefinitionActionObject = false;
												string actionObjectClassName = generateClassName(actionObjectName);
												NLCclassDefinition* classDefinitionActionObject = findClassDefinition(classDefinitionList, actionObjectClassName, &foundClassDefinitionActionObject);	//see if class definition already exists
												if(!foundClassDefinitionActionObject)
												{
													classDefinitionActionObject = new NLCclassDefinition(actionObjectClassName);
													classDefinitionList->push_back(classDefinitionActionObject);
													
													classDefinitionAction->actionObjectList.push_back(classDefinitionActionObject);
													classDefinitionActionObject->actionIncomingList.push_back(classDefinitionAction);
												}
												else
												{
													bool foundLocalClassDefinitionActionObject = false;
													string actionObjectClassName = generateClassName(actionObjectName);
													NLCclassDefinition* localClassDefinitionActionObject = findClassDefinition(&(classDefinitionAction->actionObjectList), actionObjectClassName, &foundLocalClassDefinitionActionObject);	//see if class definition already exists
													if(!foundLocalClassDefinitionActionObject)
													{
														classDefinitionAction->actionObjectList.push_back(classDefinitionActionObject);
													}
													bool foundLocalClassDefinitionActionIncoming = false;
													NLCclassDefinition* localClassDefinitionActionIncoming = findClassDefinition(&(classDefinitionActionObject->actionIncomingList), actionClassName, &foundLocalClassDefinitionActionIncoming);	//see if class definition already exists
													if(!foundLocalClassDefinitionActionIncoming)
													{
														classDefinitionActionObject->actionIncomingList.push_back(classDefinitionAction);
													}
												}
											}
											#endif
											
											#ifdef NLC_INTERPRET_ACTION_PROPERTIES_AND_CONDITIONS_AS_FUNCTION_ARGUMENTS
											//#ifdef NLC_SUPPORT_INPUT_FILE_LISTS	//shouldn't this preprocessor requirement be enforced?
											generateFunctionPropertyConditionArgumentsWithActionConceptInheritance(targetEntity, &(targetClassDefinition->parameters));
											//#endif
											#endif
										}
									}
									#endif
								}
							}
						#ifdef NLC_USE_ADVANCED_REFERENCING_SUPPORT_ALIASES
						}
						#endif
					}
				}
			}
		}
	}

	
	#ifdef NLC_PREVENT_INHERITANCE_DOUBLE_DECLARATIONS_OF_CLASS_LIST_VARIABLES
	//disable all double declarations
	for(vector<NLCclassDefinition*>::iterator classDefinitionIter = classDefinitionList->begin(); classDefinitionIter != classDefinitionList->end(); classDefinitionIter++)
	{
		NLCclassDefinition* classDefinition = *classDefinitionIter;

		eraseDuplicateClassDefinitionSublistItemIfFoundInParentClassDefinitionSublist(classDefinition, &(classDefinition->propertyList), GIA_ENTITY_VECTOR_CONNECTION_TYPE_PROPERTIES);	//changed from GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTIONS, 1k8b
		eraseDuplicateClassDefinitionSublistItemIfFoundInParentClassDefinitionSublist(classDefinition, &(classDefinition->conditionList), GIA_ENTITY_VECTOR_CONNECTION_TYPE_CONDITIONS);
		eraseDuplicateClassDefinitionSublistItemIfFoundInParentClassDefinitionSublist(classDefinition, &(classDefinition->functionList), GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTIONS);
	}
	#endif
	
	#ifdef NLC_CLASS_DEFINITIONS_USE_GENERIC_LIBRARY_ENTITY_CLASS
	//create a high level "genericEntity" class definition (for generic NLC library functions - that cannot rely on specific class names)
	for(vector<NLCclassDefinition*>::iterator classDefinitionIter = classDefinitionList->begin(); classDefinitionIter != classDefinitionList->end(); classDefinitionIter++)
	{
		NLCclassDefinition* classDefinition = *classDefinitionIter;

		if(classDefinition->definitionList.empty() && (classDefinition->name != generateClassName(NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE)))
		{
			string targetName = generateClassName(NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE);
			bool foundTargetClassDefinition = false;
			NLCclassDefinition* targetClassDefinition = findClassDefinition(classDefinitionList, targetName, &foundTargetClassDefinition);	//see if class definition already exists

			if(!foundTargetClassDefinition)
			{
				#ifdef NLC_DEBUG
				//cout << "generateClassHeirarchy(): NLC_CLASS_DEFINITIONS_USE_GENERIC_LIBRARY_ENTITY_CLASS: new NLCclassDefinition(" << targetName << endl;
				//cout << "classDefinition = " << classDefinition->name << endl;
				//cout << "targetName = " << targetName << endl;
				#endif

				targetClassDefinition = new NLCclassDefinition(targetName);
				//classDefinitionList->push_back(targetClassDefinition);	//breaks iteration
				classDefinitionIter = classDefinitionList->insert(classDefinitionIter, targetClassDefinition);
			}

			classDefinition->definitionList.push_back(targetClassDefinition);
		}
	}
	#endif

	return result;
}

#ifdef NLC_CLASS_DEFINITIONS_DO_NOT_DEFINE_INHERITANCE_FOR_REDEFINITIONS
bool isParentClassAChildOfChildClass(GIAentityNode* childEntity, GIAentityNode* parentEntity)
{	
	bool parentClassIsChildOfChildClass = false;
	GIAentityNode* parentConceptEntity = getPrimaryConceptNodeDefiningInstance(parentEntity);

	for(vector<GIAentityConnection*>::iterator connectionIter = parentConceptEntity->associatedInstanceNodeList->begin(); connectionIter != parentConceptEntity->associatedInstanceNodeList->end(); connectionIter++)
	{
		GIAentityNode* parentSubstanceConceptEntity = (*connectionIter)->entity;
		if(parentSubstanceConceptEntity->isSubstanceConcept || parentSubstanceConceptEntity->isActionConcept)
		{
			for(vector<GIAentityConnection*>::iterator connectionIter2 = parentSubstanceConceptEntity->entityNodeDefinitionList->begin(); connectionIter2 != parentSubstanceConceptEntity->entityNodeDefinitionList->end(); connectionIter2++)
			{
				GIAentityNode* parentSubstanceConceptParentEntity = (*connectionIter2)->entity;
				if(parentSubstanceConceptParentEntity->entityName == childEntity->entityName)
				{
					parentClassIsChildOfChildClass = true;
				}
			}
		}
	}
	return parentClassIsChildOfChildClass;
}										
#endif

bool generateClassHeirarchyCondition(NLCclassDefinition* classDefinition, NLCclassDefinition* targetClassDefinition, GIAentityNode* targetEntity)
{
	bool result = true;
	
	//conditionList
	bool foundLocalClassDefinition = false;
	NLCclassDefinition* localClassDefinition = findClassDefinitionCondition(&(classDefinition->conditionList), targetEntity, &foundLocalClassDefinition);	//see if class definition already exists
	if(!foundLocalClassDefinition)
	{
		#ifdef NLC_DEBUG
		//cout << "generateClassHeirarchy(): classDefinition->conditionList.push_back: " << targetClassDefinition->name << endl;
		#endif

		classDefinition->conditionList.push_back(targetClassDefinition);

		NLCitem* classDeclarationConditionsListItem = new NLCitem(targetEntity, NLC_ITEM_TYPE_CLASS_DECLARATION_CONDITION_LIST);

		if(!(targetEntity->conditionObjectEntity->empty()))
		{
			string conditionObjectClassName = generateClassName((targetEntity->conditionObjectEntity->back())->entity);
			classDeclarationConditionsListItem->className2 = conditionObjectClassName;
			//cout << "\tgenerateClassHeirarchy(): conditionObjectClassName = " << conditionObjectClassName << endl;
		}
		else
		{
			cout << "generateClassHeirarchy() error: condition has no object" << endl;
		}

		targetClassDefinition->parameters.push_back(classDeclarationConditionsListItem);
	}
	
	return result;
}

#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE
bool generateClassHeirarchyFunctions(vector<NLCclassDefinition* >* classDefinitionList, vector<GIAentityNode*>* entityNodesActiveListComplete, NLCclassDefinitionFunctionDependency* parentFunctionDependency, vector<NLCclassDefinitionFunctionDependency*>* functionDependencyList)
{
	#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
	cout << "generateClassHeirarchyFunctions:" << endl;
	#endif
	
	bool result = true;
	
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode* actionEntity = *entityIter;

		#ifdef NLC_DEBUG
		//cout << "generateClassHeirarchyFunctions(): actionEntity = " << actionEntity->entityName << endl;
		#endif
		//valid class checks added 1g12f 14-July-2014
		if(generateClassHeirarchyValidClassChecks(actionEntity))
		{
			if(!(actionEntity->disabled))
			{
				if(actionEntity->isAction)
				{
					string actionOwnerClassDefinitionName = generateClassName(NLC_CLASS_DEFINITIONS_SUPPORT_FUNCTIONS_WITHOUT_SUBJECT_ARTIFICIAL_CLASS_NAME);
					
					bool passSubjectObjectValidClassChecks = true;
					
					bool hasActionSubject = false;
					string actionSubjectName = "";
					GIAentityNode* actionSubject = NULL;
					if(!(actionEntity->actionSubjectEntity->empty()))
					{
						actionSubject = (actionEntity->actionSubjectEntity->back())->entity;
						hasActionSubject = true;
						actionSubjectName = actionSubject->entityName;
						
						passSubjectObjectValidClassChecks = false;
						//valid class contents checks added 1g12f 14-July-2014
						if(generateClassHeirarchyTargetValidClassChecks(actionSubject))
						{
							if(!(actionSubject->disabled))
							{
								passSubjectObjectValidClassChecks = true;
							}
						}
					}
					
					bool hasActionObject = false;
					string actionObjectName = "";
					GIAentityNode* actionObject = NULL;
					if(!(actionEntity->actionObjectEntity->empty()))
					{
						actionObject = (actionEntity->actionObjectEntity->back())->entity;
						hasActionObject = true;
						actionObjectName = actionObject->entityName;
					}
						
					#ifndef NLC_CLASS_DEFINITIONS_SUPPORT_FUNCTIONS_WITHOUT_SUBJECT
					if(!hasActionSubject)
					{
						passSubjectObjectValidClassChecks = false;
					}
					#endif
					
					//valid class contents checks added 1g12f 14-July-2014
					if(passSubjectObjectValidClassChecks)
					{
						#ifdef NLC_DEBUG
						//cout << "generateClassHeirarchyFunctions(): passSubjectObjectValidClassChecks, actionEntity = " << actionEntity->entityName << endl;
						#endif

						string functionName = actionEntity->entityName;
						string functionOwnerName = actionSubjectName;
						string functionObjectName = actionObjectName;
						bool hasFunctionOwnerClass = hasActionSubject;
						bool hasFunctionObjectClass = hasActionObject;

						bool foundFunctionOwnerExactMatch = false;
						bool foundFunctionObjectExactMatch = false;
						NLCclassDefinition* functionDeclaration = NULL;
						if(findFunctionDeclarationClassDefinitionExactOrNonExactMatch(classDefinitionList, functionName, functionOwnerName, functionObjectName, hasFunctionOwnerClass, hasFunctionObjectClass, &functionDeclaration, false, &foundFunctionOwnerExactMatch, &foundFunctionObjectExactMatch))
						{
							NLCclassDefinitionFunctionDependency* functionDependenciesInParentTemp = NULL;
							bool foundFunctionDependencyInParent = findFunctionDependencyInParent(parentFunctionDependency, functionName, functionOwnerName, functionObjectName, hasFunctionOwnerClass, hasFunctionObjectClass, &functionDependenciesInParentTemp);
							if(!foundFunctionDependencyInParent)
							{
								parentFunctionDependency->functionDependencyList.push_back(functionDeclaration->functionDependency);
							}
						}
						else
						{
							//function execution reference does not correspond to a new function definition, so create a function declaration for it
							//cout << "findFunctionDependencyInList: " << targetName << endl;

							NLCclassDefinitionFunctionDependency* functionDependency = NULL;
							bool foundFunctionDependencyInList = findFunctionDependencyInList(functionDependencyList, functionName, functionOwnerName, functionObjectName, true, hasFunctionObjectClass, &functionDependency);
							bool duplicateFunctionDeclarationDetected = false;
							if(foundFunctionDependencyInList)
							{
								//this will be true if an action (function reference) has been declared twice, but the action (function) has not been defined, eg "A chicken ate a pie. The chicken that ate a pie rowed the boat."
								#ifdef NLC_DEBUG
								//cout << "generateClassHeirarchyFunctions(): foundFunctionDependencyInList" << endl;
								//cout << "functionName: " << functionName << endl;
								//cout << "functionOwnerName: " << functionOwnerName << endl;
								//cout << "functionObjectName: " << functionObjectName << endl;
								#endif
								NLCclassDefinitionFunctionDependency* functionDependenciesInParentTemp = NULL;
								bool foundFunctionDependencyInParent = findFunctionDependencyInParent(parentFunctionDependency, functionName, functionOwnerName, functionObjectName, true, hasFunctionObjectClass, &functionDependenciesInParentTemp);
								if(!foundFunctionDependencyInParent)
								{
									#ifdef NLC_DEBUG
									//cout << "generateClassHeirarchyFunctions(): !foundFunctionDependencyInParent" << endl;	
									#endif	
									parentFunctionDependency->functionDependencyList.push_back(functionDependency);
								}
								else
								{
									#ifdef NLC_DEBUG
									//cout << "generateClassHeirarchyFunctions(): foundFunctionDependencyInParent" << endl;	
									#endif
									duplicateFunctionDeclarationDetected = true;
									//duplicate function declarations will be ignored
								}
							}
							else
							{
								#ifdef NLC_DEBUG
								//cout << "generateClassHeirarchyFunctions(): !foundFunctionDependencyInList" 
								//cout << "generateClassHeirarchyFunctions(): functionName = " << functionName << endl;
								//cout << "generateClassHeirarchyFunctions(): functionOwnerName = " << functionOwnerName << endl;
								//cout << "generateClassHeirarchyFunctions(): functionObjectName = " << functionObjectName << endl;
								#endif

								functionDependency = new NLCclassDefinitionFunctionDependency();
								functionDependency->functionName = functionName;
								functionDependency->functionOwnerName = functionOwnerName;
								functionDependency->functionObjectName = functionObjectName;
								#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE_PATCH
								functionDependency->hasFunctionOwnerClass = hasFunctionOwnerClass;	//changed from true 1l1a
								#else
								functionDependency->hasFunctionOwnerClass = true;
								#endif
								functionDependency->hasFunctionObjectClass = hasFunctionObjectClass;
								#ifdef NLC_CLASS_DEFINITIONS_CREATE_FUNCTION_DECLARATIONS_FOR_NEW_FUNCTION_DEFINITIONS
								functionDependency->isReference = true;
								#endif
								parentFunctionDependency->functionDependencyList.push_back(functionDependency);
								functionDependencyList->push_back(functionDependency);

								string classDefinitionFunctionOwnerName = "";
								if(hasActionSubject)
								{
									classDefinitionFunctionOwnerName = generateClassName(actionSubject);
									#ifdef NLC_CREATE_A_SEPARATE_CLASS_FOR_SUBSTANCE_CONCEPT_DEFINITIONS
									if(actionEntity->isSubstanceConcept)
									{
										classDefinitionFunctionOwnerName = generateSubstanceConceptClassName(actionSubject);	//is this still required?
									}
									#endif
								}
								else
								{
									classDefinitionFunctionOwnerName = generateClassName(NLC_CLASS_DEFINITIONS_SUPPORT_FUNCTIONS_WITHOUT_SUBJECT_ARTIFICIAL_CLASS_NAME);
								}
								bool foundClassDefinitionFunctionOwner = false;
								NLCclassDefinition* classDefinitionFunctionOwner = findClassDefinition(classDefinitionList, classDefinitionFunctionOwnerName, &foundClassDefinitionFunctionOwner);	//see if class definition already exists
								if(!foundClassDefinitionFunctionOwner)
								{
									classDefinitionFunctionOwner = new NLCclassDefinition(classDefinitionFunctionOwnerName);
									classDefinitionList->push_back(classDefinitionFunctionOwner);
									#ifdef NLC_DEBUG
									//cout << "generateClassHeirarchyFunctions(): !foundClassDefinitionFunctionOwner" << endl;
									//cout << "new NLCclassDefinition(" << classDefinitionFunctionOwnerName << endl;
									#endif
								}

								string classDefinitionFunctionName = generateInstanceName(actionEntity);
								bool foundClassDefinitionFunction = false;
								NLCclassDefinition* classDefinitionFunction = findClassDefinition(classDefinitionList, classDefinitionFunctionName, &foundClassDefinitionFunction);	//see if class definition already exists
								if(!foundClassDefinitionFunction)
								{
									classDefinitionFunction = new NLCclassDefinition(classDefinitionFunctionName);
									classDefinitionList->push_back(classDefinitionFunction);
									#ifdef NLC_DEBUG
									//cout << "generateClassHeirarchyFunctions(): !foundClassDefinitionFunction" << endl;
									//cout << "new NLCclassDefinition(" << classDefinitionFunctionName << endl;
									#endif
								}
								
								classDefinitionFunction->functionNameSpecial = generateFunctionName(actionEntity);
								#ifdef NLC_SUPPORT_INPUT_FILE_LISTS_CHECK_ACTION_SUBJECT_CONTENTS_FOR_IMPLICITLY_DECLARED_PARAMETERS
								classDefinitionFunction->actionOrConditionInstance = actionEntity;
								#endif
								classDefinitionFunction->isActionOrConditionInstanceNotClass = true;

								bool foundLocalClassDefinitionFunction = false;
								NLCclassDefinition* localClassDefinitionFunction = findClassDefinition(&(classDefinitionFunctionOwner->functionList), classDefinitionFunctionName, &foundLocalClassDefinitionFunction);	//see if class definition already exists	//note this check will not work for functions because they are added by instance 
								if(!foundLocalClassDefinitionFunction)
								{
									//declare functions
									
									#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE
									classDefinitionFunction->functionDependency = functionDependency;
									#endif

									classDefinitionFunctionOwner->functionList.push_back(classDefinitionFunction);
									
									#ifdef NLC_FUNCTIONS_SUPPORT_PLURAL_SUBJECTS
									//added 1l1a for dynamic casting of children
									if(hasFunctionOwnerClass)
									{
										NLCitem* classDeclarationFunctionOwnerItem = new NLCitem(actionEntity, NLC_ITEM_TYPE_FUNCTION_DECLARATION_ARGUMENT_FUNCTION_OWNER);
										classDefinitionFunction->parameters.push_back(classDeclarationFunctionOwnerItem);
									}
									#endif
																		
									NLCitem* classDeclarationFunctionItem = new NLCitem(actionEntity, NLC_ITEM_TYPE_FUNCTION_DECLARATION_ARGUMENT_FUNCTION);	//added 1e1c
									classDefinitionFunction->parameters.push_back(classDeclarationFunctionItem);
									
									if(hasFunctionObjectClass)
									{
										NLCitem* classDeclarationFunctionObjectItem = new NLCitem(actionObjectName, NLC_ITEM_TYPE_FUNCTION_DECLARATION_ARGUMENT_FUNCTION_OBJECT);	//for special case (as actions are referenced by instance)
										classDefinitionFunction->parameters.push_back(classDeclarationFunctionObjectItem);
									}

									#ifdef NLC_RECORD_ACTION_HISTORY
									bool foundClassDefinitionAction = false;
									string actionClassName =  generateClassName(actionEntity);
									NLCclassDefinition* classDefinitionAction = findClassDefinition(classDefinitionList, actionClassName, &foundClassDefinitionAction);	//see if class definition already exists
									if(!foundClassDefinitionAction)
									{
										classDefinitionAction = new NLCclassDefinition(actionClassName);
										classDefinitionList->push_back(classDefinitionAction);
									}
									if(hasActionSubject)
									{
										bool foundLocalClassDefinitionAction = false;
										NLCclassDefinition* localClassDefinitionAction = findClassDefinition(&(classDefinitionFunctionOwner->actionList), actionClassName, &foundLocalClassDefinitionAction);	//see if class definition already exists
										if(!foundLocalClassDefinitionAction)
										{
											classDefinitionFunctionOwner->actionList.push_back(classDefinitionAction);

										}
										bool foundLocalClassDefinitionActionOwner = false;
										string actionOwnerClassName = classDefinitionFunctionOwnerName;
										NLCclassDefinition* localClassDefinitionActionOwner = findClassDefinition(&(classDefinitionAction->actionSubjectList), actionOwnerClassName, &foundLocalClassDefinitionActionOwner);	//see if class definition already exists
										if(!foundLocalClassDefinitionActionOwner)
										{
											classDefinitionAction->actionSubjectList.push_back(classDefinitionFunctionOwner);
										}
									}
									
									if(hasActionObject)
									{
										bool foundClassDefinitionActionObject = false;
										string actionObjectClassName = generateClassName(actionObjectName);
										NLCclassDefinition* classDefinitionActionObject = findClassDefinition(classDefinitionList, actionObjectClassName, &foundClassDefinitionActionObject);	//see if class definition already exists
										if(!foundClassDefinitionActionObject)
										{
											classDefinitionActionObject = new NLCclassDefinition(actionObjectClassName);
											classDefinitionList->push_back(classDefinitionActionObject);
											//cout << "!foundClassDefinition" << endl;
											classDefinitionAction->actionObjectList.push_back(classDefinitionActionObject);
											classDefinitionActionObject->actionIncomingList.push_back(classDefinitionAction);
										}
										else
										{
											bool foundLocalClassDefinitionActionObject = false;
											string actionObjectClassName = generateClassName(actionObjectName);
											NLCclassDefinition* localClassDefinitionActionObject = findClassDefinition(&(classDefinitionAction->actionObjectList), actionObjectClassName, &foundLocalClassDefinitionActionObject);	//see if class definition already exists
											if(!foundLocalClassDefinitionActionObject)
											{
												classDefinitionAction->actionObjectList.push_back(classDefinitionActionObject);
											}
											bool foundLocalClassDefinitionActionIncoming = false;
											NLCclassDefinition* localClassDefinitionActionIncoming = findClassDefinition(&(classDefinitionActionObject->actionIncomingList), actionClassName, &foundLocalClassDefinitionActionIncoming);	//see if class definition already exists
											if(!foundLocalClassDefinitionActionIncoming)
											{
												classDefinitionActionObject->actionIncomingList.push_back(classDefinitionAction);
											}
										}
									}
									#endif

									#ifdef NLC_INTERPRET_ACTION_PROPERTIES_AND_CONDITIONS_AS_FUNCTION_ARGUMENTS
									//#ifdef NLC_SUPPORT_INPUT_FILE_LISTS	//shouldn't this preprocessor requirement be enforced?
									generateFunctionPropertyConditionArgumentsWithActionConceptInheritance(actionEntity, &(classDefinitionFunction->parameters));
									//#endif
									#endif
								}
							}
						}
					}
				}
			}
		}
	}

	/*
	#ifdef NLC_PREVENT_INHERITANCE_DOUBLE_DECLARATIONS_OF_CLASS_LIST_VARIABLES
	//disable all double declarations
	for(vector<NLCclassDefinition*>::iterator classDefinitionIter = classDefinitionList->begin(); classDefinitionIter != classDefinitionList->end(); classDefinitionIter++)
	{
		NLCclassDefinition* classDefinition = *classDefinitionIter;

		eraseDuplicateClassDefinitionSublistItemIfFoundInParentClassDefinitionSublist(classDefinition, &(classDefinition->propertyList), GIA_ENTITY_VECTOR_CONNECTION_TYPE_PROPERTIES);	//changed from GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTIONS, 1k8b
		eraseDuplicateClassDefinitionSublistItemIfFoundInParentClassDefinitionSublist(classDefinition, &(classDefinition->conditionList), GIA_ENTITY_VECTOR_CONNECTION_TYPE_CONDITIONS);
		eraseDuplicateClassDefinitionSublistItemIfFoundInParentClassDefinitionSublist(classDefinition, &(classDefinition->functionList), GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTIONS);
	}
	#endif
	*/

	return result;
}
#endif


bool generateClassHeirarchyValidClassChecks(GIAentityNode* entityNode)
{
	bool validClass = true;
	
	#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
	if(entityNode->NLClogicalConditionOperation)
	{
		validClass = false;
	}
	#ifdef NLC_USE_PREPROCESSOR
	if((entityNode->entityName == NLC_PREPROCESSOR_LOGICAL_CONDITION_DUMMY_TEXT_ACTION) || (entityNode->entityName == NLC_PREPROCESSOR_LOGICAL_CONDITION_DUMMY_TEXT_ACTION_OBJECT))
	{
		validClass = false;
	}
	#endif
	#endif
	#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS_ADVANCED
	bool conjunctionConditionFound = textInTextArray(entityNode->entityName, entityCoordinatingConjunctionArray, ENTITY_COORDINATINGCONJUNCTION_ARRAY_NUMBER_OF_TYPES);
	if(conjunctionConditionFound)
	{
		validClass = false;
	}
	#endif
	#ifdef NLC_PREPROCESSOR_MATH
	#ifdef NLC_PREPROCESSOR_MATH_OLD_NUMBER_OF_IMPLEMENTATION_USING_QVARS
	if(entityNode->entityName == REFERENCE_TYPE_QUESTION_COMPARISON_VARIABLE)
	{
		validClass = false;	
	}
	#endif
	#endif
	#ifdef NLC_PREPROCESSOR_INTERPRET_SINGLE_WORD_SENTENCES_AS_ACTIONS
	if(entityNode->entityName == NLC_PREPROCESSOR_INTERPRET_SINGLE_WORD_SENTENCES_AS_ACTIONS_DUMMY_TEXT_ACTION_OBJECT)
	{
		//cout << "entityNode->entityName = " << entityNode->entityName << endl;
		validClass = false;	
	}
	#ifdef NLC_PREPROCESSOR_INTERPRET_SINGLE_WORD_SENTENCES_AS_ACTIONS_REPLACE_ACTION_ALSO_DUE_TO_NLP_LIMITATION
	if(entityNode->entityName == NLC_PREPROCESSOR_INTERPRET_SINGLE_WORD_SENTENCES_AS_ACTIONS_DUMMY_TEXT_ACTION)
	{
		validClass = false;	
	}
	#endif
	#endif
	if(entityNode->isConcept)	//added 1n2f
	{
		validClass = false;
	}
	#ifdef NLC_USE_ADVANCED_REFERENCING_SUPPORT_ALIASES
	if(entityNode->NLCisAlias)
	{
		validClass = false;
	}
	#endif
	
	/*
	cout << "\nentityNode->entityName = " << entityNode->entityName << endl;
	cout << "entityNode->isSubstance = " << entityNode->isSubstance << endl;
	cout << "entityNode->isConcept = " << entityNode->isConcept << endl;
	cout << "entityNode->disabled = " << entityNode->disabled << endl;
	*/
	
	/*
	#ifdef NLC_USE_ADVANCED_REFERENCING_SUPPORT_ALIASES
	string aliasClassName = "";
	if(findEntityNameInFunctionAliasList(entityNode->entityName, &aliasClassName))
	{
		entityNode->entityName = aliasClassName;	//entity name can be overwritten as generateCodeBlocks has already been executed 
	}
	#endif
	*/
	
	return validClass;
}

bool generateClassHeirarchyTargetValidClassChecks(GIAentityNode* targetEntity)
{
	bool validClass = true;

	#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
	if(targetEntity->NLClogicalConditionOperation)
	{
		validClass = false;
	}
	/*OLD:
	if(!(connection->NLCparsedForlogicalConditionOperations) && !(targetEntity->NLCparsedForlogicalConditionOperations))
	{

	}
	*/
	#ifdef NLC_USE_PREPROCESSOR
	if((targetEntity->entityName == NLC_PREPROCESSOR_LOGICAL_CONDITION_DUMMY_TEXT_ACTION) || (targetEntity->entityName == NLC_PREPROCESSOR_LOGICAL_CONDITION_DUMMY_TEXT_ACTION_OBJECT))
	{
		validClass = false;
	}
	#endif
	#endif
	
	//#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED	//this criteria was used [perhaps unintentionally] before 1k6a
	#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS_ADVANCED
	bool conjunctionConditionFound = textInTextArray(targetEntity->entityName, entityCoordinatingConjunctionArray, ENTITY_COORDINATINGCONJUNCTION_ARRAY_NUMBER_OF_TYPES);
	if(conjunctionConditionFound)
	{
		validClass = false;
	}
	#endif
	//#endif	
	
	//these checks are not required as single word sentences utilise both replacement action and replacement object			
	#ifdef NLC_PREPROCESSOR_INTERPRET_SINGLE_WORD_SENTENCES_AS_ACTIONS
	if(targetEntity->entityName == NLC_PREPROCESSOR_INTERPRET_SINGLE_WORD_SENTENCES_AS_ACTIONS_DUMMY_TEXT_ACTION_OBJECT)
	{
		//cout << "targetEntity->entityName = " << targetEntity->entityName << endl;
		validClass = false;	
	}
	#ifdef NLC_PREPROCESSOR_INTERPRET_SINGLE_WORD_SENTENCES_AS_ACTIONS_REPLACE_ACTION_ALSO_DUE_TO_NLP_LIMITATION
	if(targetEntity->entityName == NLC_PREPROCESSOR_INTERPRET_SINGLE_WORD_SENTENCES_AS_ACTIONS_DUMMY_TEXT_ACTION)
	{
		validClass = false;	
	}
	#endif
	#endif
	
	if(targetEntity->isConcept)	//added 1n2f
	{
		validClass = false;
	}
	
	/*
	#ifdef NLC_USE_ADVANCED_REFERENCING_SUPPORT_ALIASES
	string aliasClassName = "";
	if(findEntityNameInFunctionAliasList(targetEntity->entityName, &aliasClassName))
	{
		targetEntity->entityName = aliasClassName;	//entity name can be overwritten as generateCodeBlocks has already been executed 
	}
	#endif
	*/
	
	return validClass;
}




#ifdef NLC_CREATE_A_SEPARATE_CLASS_FOR_SUBSTANCE_CONCEPT_DEFINITIONS
string generateSubstanceConceptClassName(GIAentityNode* substanceConceptEntity)
{
	string substanceConceptClassName = substanceConceptEntity->entityName;
	generateSubstanceConceptClassNameRecurse(substanceConceptEntity, &substanceConceptClassName, NULL);
	substanceConceptClassName = substanceConceptClassName + NLC_CLASS_NAME_APPEND;
	return substanceConceptClassName;
}

void generateSubstanceConceptClassNameRecurse(GIAentityNode* substanceConceptEntity, string* substanceConceptClassName)
{
	for(vector<GIAentityConnection*>::iterator entityIter = substanceConceptEntity->conditionNodeList->begin(); entityIter != substanceConceptEntity->conditionNodeList->end(); entityIter++)
	{
		GIAentityNode* substanceConceptCondition = (*entityIter)->entity;
		#ifdef NLC_NORMALISE_TWOWAY_PREPOSITIONS_DUAL_CONDITION_LINKS_ENABLED
		if(!(substanceConceptCondition->inverseConditionTwoWay) || (*entityIter)->isReference)		//prevent infinite loop for 2 way conditions
		{
		#endif
			if(!(substanceConceptCondition->conditionObjectEntity->empty()))
			{
				GIAentityNode* substanceConceptConditionObject = (substanceConceptCondition->conditionObjectEntity->back())->entity;
				*substanceConceptClassName = *substanceConceptClassName + NLC_SUBSTANCE_CONCEPT_CLASS_PREPEND + substanceConceptCondition->entityName + substanceConceptConditionObject->entityName + NLC_SUBSTANCE_CONCEPT_CLASS_CONDITION;
				*substanceConceptClassName = *substanceConceptClassName + generateSubstanceConceptClassNameRecurse(substanceConceptConditionObject);	//recurse in case of very detailed substance concept eg "red dogs next to blue cows"
			}
			else
			{
				cout << "generateSubstanceConceptClassNameRecurse() error: condition has no object" << endl;
			}
		#ifdef NLC_NORMALISE_TWOWAY_PREPOSITIONS_DUAL_CONDITION_LINKS_ENABLED
		}
		#endif
	}
	for(vector<GIAentityConnection*>::iterator entityIter = substanceConceptEntity->propertyNodeList->begin(); entityIter != substanceConceptEntity->propertyNodeList->end(); entityIter++)
	{
		GIAentityNode* substanceConceptProperty = (*entityIter)->entity;
		*substanceConceptClassName = *substanceConceptClassName + NLC_SUBSTANCE_CONCEPT_CLASS_PREPEND + substanceConceptProperty->entityName + NLC_SUBSTANCE_CONCEPT_CLASS_PROPERTY;
		*substanceConceptClassName = *substanceConceptClassName + generateSubstanceConceptClassNameRecurse(substanceConceptProperty, substanceConceptEntity);	//recurse in case of very detailed substance concept eg "red dogs next to blue cows"
	}
}
			
#endif

#ifdef NLC_PREVENT_INHERITANCE_DOUBLE_DECLARATIONS_OF_CLASS_LIST_VARIABLES
void eraseDuplicateClassDefinitionSublistItemIfFoundInParentClassDefinitionSublist(NLCclassDefinition* classDefinition, vector<NLCclassDefinition*>* classDefinitionSublist, int variableType)
{
	for(vector<NLCclassDefinition*>::iterator localListIter = classDefinitionSublist->begin(); localListIter != classDefinitionSublist->end();)
	{
		bool localListIterErased = false;
		NLCclassDefinition* variableClassDefinition = *localListIter;
		string variableName = variableClassDefinition->name;
		for(vector<NLCclassDefinition*>::iterator parentListIter = classDefinition->definitionList.begin(); parentListIter != classDefinition->definitionList.end(); parentListIter++)
		{
			if(!localListIterErased)
			{
				NLCclassDefinition* targetClassDefinition = *parentListIter;	

				if(findVariableInParentClass(targetClassDefinition, variableName, variableType))
				{
					localListIter = classDefinitionSublist->erase(localListIter);
					localListIterErased = true;
					#ifdef NLC_DEBUG
					//cout << "eraseDuplicateClassDefinitionSublistItemIfFoundInParentClassDefinitionSublist(): localListIterErased" << endl;
					//cout << "variableClassDefinition->name = " << variableClassDefinition->name << endl;
					//cout << "classDefinition->name = " << classDefinition->name << endl;
					//cout << "targetClassDefinition->name = " << targetClassDefinition->name << endl;
					#endif
				}
			}
		}
		if(!localListIterErased)
		{
			localListIter++;
		}
	}
}

bool findVariableInParentClass(NLCclassDefinition* classDefinition, string variableName, int variableType)
{
	bool foundVariable = false;
	if(variableType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_PROPERTIES)
	{
		for(vector<NLCclassDefinition*>::iterator localListIter = classDefinition->propertyList.begin(); localListIter != classDefinition->propertyList.end(); localListIter++)
		{
			NLCclassDefinition* targetClassDefinition = *localListIter;
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
			NLCclassDefinition* targetClassDefinition = *localListIter;
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
			NLCclassDefinition* targetClassDefinition = *localListIter;
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
			NLCclassDefinition* targetClassDefinition = *localListIter;
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
void generateFunctionPropertyConditionArgumentsWithActionConceptInheritance(GIAentityNode* actionEntity, vector<NLCitem*>* parameters)
{
	generateFunctionPropertyConditionArguments(actionEntity, parameters, false);

	#ifdef GIA_TRANSLATOR_DREAM_MODE_LINK_SPECIFIC_CONCEPTS_AND_ACTIONS
	//Part b: generate object initialisations based on action concepts (class inheritance)
	for(vector<GIAentityConnection*>::iterator entityNodeDefinitionListIterator = actionEntity->entityNodeDefinitionList->begin(); entityNodeDefinitionListIterator < actionEntity->entityNodeDefinitionList->end(); entityNodeDefinitionListIterator++)
	{
		GIAentityConnection* definitionConnection = (*entityNodeDefinitionListIterator);
		definitionConnection->NLCparsedForCodeBlocks = true;
		GIAentityNode* definitionEntity = definitionConnection->entity;
		if(definitionEntity->isActionConcept)
		{
			generateFunctionPropertyConditionArguments(definitionEntity, parameters, true);
		}
	}
	#endif
}

void generateFunctionPropertyConditionArguments(GIAentityNode* actionEntity, vector<NLCitem*>* parameters, bool performChildActionDuplicateCheck)
{
	for(vector<GIAentityConnection*>::iterator entityIter = actionEntity->conditionNodeList->begin(); entityIter != actionEntity->conditionNodeList->end(); entityIter++)
	{
		GIAentityNode* actionCondition = (*entityIter)->entity;
		bool alreadyAdded = false;
		if(performChildActionDuplicateCheck)
		{
			alreadyAdded = checkDuplicateCondition(actionCondition, parameters);
		}
		if(!alreadyAdded)
		{
			GIAentityNode* conditionObject = NULL;
			if(!(actionCondition->conditionObjectEntity->empty()))
			{
				conditionObject = (actionCondition->conditionObjectEntity->back())->entity;
			}
			NLCitem* argumentConditionItem = new NLCitem(actionCondition, NLC_ITEM_TYPE_FUNCTION_DECLARATION_ARGUMENT_CONDITION);
			argumentConditionItem->className2 = generateClassName(conditionObject);
			argumentConditionItem->instanceName2 = generateInstanceName(conditionObject);
			parameters->push_back(argumentConditionItem);
		}
	}
	for(vector<GIAentityConnection*>::iterator entityIter = actionEntity->propertyNodeList->begin(); entityIter != actionEntity->propertyNodeList->end(); entityIter++)
	{
		GIAentityNode* actionProperty = (*entityIter)->entity;
		bool alreadyAdded = false;
		if(performChildActionDuplicateCheck)
		{
			alreadyAdded = checkDuplicateProperty(actionProperty, parameters);
		}
		if(!alreadyAdded)
		{
			NLCitem* argumentPropertyItem = new NLCitem(actionProperty, NLC_ITEM_TYPE_FUNCTION_DECLARATION_ARGUMENT_PROPERTY);
			parameters->push_back(argumentPropertyItem);
		}
	}
}

bool checkDuplicateProperty(GIAentityNode* propertyEntity, vector<NLCitem*>* parameters)
{
	bool alreadyAdded = false;
	for(vector<NLCitem*>::iterator parametersIterator = parameters->begin(); parametersIterator < parameters->end(); parametersIterator++)
	{
		NLCitem* currentItem = *parametersIterator;
		if(currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_DECLARATION_ARGUMENT_PROPERTY)
		{
			if(generateClassName(propertyEntity) == currentItem->className)
			{
				alreadyAdded = true;
			}
		}

	}
	return alreadyAdded;
}

bool checkDuplicateCondition(GIAentityNode* conditionEntity, vector<NLCitem*>* parameters)
{
	bool alreadyAdded = false;
	for(vector<NLCitem*>::iterator parametersIterator = parameters->begin(); parametersIterator < parameters->end(); parametersIterator++)
	{
		NLCitem* currentItem = *parametersIterator;
		if(currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_DECLARATION_ARGUMENT_CONDITION)
		{
			GIAentityNode* conditionObjectEntity = NULL;
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






