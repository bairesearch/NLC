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
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2016 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 1u12b 30-September-2016
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/


#include "NLCtranslatorClassDefinitions.h"
#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS_ADVANCED
#include "GIAtranslatorDefs.h"
#endif
#ifdef NLC_CLASS_DEFINITIONS_DO_NOT_DEFINE_INHERITANCE_FOR_REDEFINITIONS
#include "NLCtranslatorCodeBlocksOperations.h"	//required for getSameReferenceSetUniqueParent()
#include "GIAtranslatorOperations.h"	//required for getPrimaryNetworkIndexNodeDefiningInstance()
#endif


bool generateClassHeirarchy(vector<NLCclassDefinition*>* classDefinitionList, vector<GIAentityNode*>* entityNodesActiveListComplete, NLCfunction* currentNLCfunctionInList)
{
	bool result = true;

	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode* entityNode = *entityIter;

		//valid class checks added 1g12f 14-July-2014
		if(!(entityNode->disabled))
		{
			if(generateClassHeirarchyValidClassChecks(entityNode))
			{
				#ifdef NLC_CLASS_DEFINITIONS_DO_NOT_DEFINE_INHERITANCE_FOR_LOGICAL_CONDITION_CONCEPTS
				if(!entityIsConceptAndInLogicalCondition(entityNode, currentNLCfunctionInList))
				{
				#endif
					string className = generateClassName(entityNode);
					#ifdef NLC_CREATE_A_SEPARATE_CLASS_FOR_CONCEPT_DEFINITIONS
					if(entityNode->entityType == GIA_ENTITY_TYPE_TYPE_CONCEPT)
					{
						className = generateConceptClassName(entityNode);
					}
					#endif

					NLCclassDefinition* classDefinition = NULL;
					addClassDefinitionToList(classDefinitionList, className, &classDefinition);

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
										cout << "generateClassHeirarchy{}: targetEntity->entityName = " << targetEntity->entityName << endl;
										#endif

										string targetName = "";
										string targetClassName = "";
										if(i == GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTIONS)	//in GIA actions are treated as special connections with intermediary nodes
										{
											targetName = generateInstanceName(targetEntity);
										}
										#ifdef NLC_CREATE_A_SEPARATE_CLASS_FOR_CONCEPT_DEFINITIONS
										else if((i == GIA_ENTITY_VECTOR_CONNECTION_TYPE_DEFINITIONS) && (targetEntity->entityType == GIA_ENTITY_TYPE_TYPE_CONCEPT))
										{
											targetName = generateConceptClassName(targetEntity);
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
											#ifdef NLC_SUPPORT_INPUT_FUNCTION_LISTS_CHECK_ACTION_SUBJECT_CONTENTS_FOR_IMPLICITLY_DECLARED_PARAMETERS
											targetClassDefinition->actionOrConditionInstance = targetEntity;
											#endif
										}
										if(i == GIA_ENTITY_VECTOR_CONNECTION_TYPE_CONDITIONS)
										{
											targetClassDefinition->isConditionInstance = true;
										}

										#ifdef NLC_DEBUG_PRINT_HIDDEN_CLASSES
										if(1)	//removed; || (if((targetEntity->entityType == GIA_ENTITY_TYPE_TYPE_CONDITION) && !(targetEntity->entityType == GIA_ENTITY_TYPE_TYPE_NETWORK_INDEX)) 16 April 2014
										#else
										#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS
										if((i == GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTIONS) || (i == GIA_ENTITY_VECTOR_CONNECTION_TYPE_CONDITIONS))	//removed; ((targetEntity->entityType == GIA_ENTITY_TYPE_TYPE_CONDITION) && !(targetEntity->entityType == GIA_ENTITY_TYPE_TYPE_NETWORK_INDEX) ||) 16 April 2014	//restored || (i == GIA_ENTITY_VECTOR_CONNECTION_TYPE_CONDITIONS) 1m3a
										#else
										if((targetEntity->entityType == GIA_ENTITY_TYPE_TYPE_ACTION) || (targetEntity->isActionConcept) && !(targetEntity->entityType == GIA_ENTITY_TYPE_TYPE_NETWORK_INDEX))	//removed; || (targetEntity->entityType == GIA_ENTITY_TYPE_TYPE_CONDITION) 16 April 2014
										#endif
										#endif
										{
											targetClassDefinition->isActionOrConditionInstanceNotClass = true;
											#ifdef NLC_DEBUG
											//cout << "classDefinition->isActionOrConditionInstanceNotClass" << endl;
											#endif
										}

										if(i == GIA_ENTITY_VECTOR_CONNECTION_TYPE_PROPERTIES)
										{//declare subclass

											addPropertyListToClassDefinition(classDefinition, targetClassDefinition);

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
											//chickens are animals. an animal is a chicken. In practice this will not be implemented because GIA interprets indefinite-indefinite definitions as concepts. redefinitions are generally not implied for indefinite children (eg "an animal" in "an animal is a chicken") because they are ambiguous; this example either means a) animals are chickens (ie is a concept-concept definition; not a redefinition - and happens to be an incorrect statement based on aprior knowledge about the animal kingdom because we know chickens are animals not vice versa), or b) a newly declared animal is cast to a chicken (a specific version of animal, assuming "chickens are animals" has been declared)
											bool indefiniteChild = false;
											if(!isDefiniteEntity(entityNode))
											{
												bool parseConditionParents = NLC_PARSE_CONDITION_PARENTS_DEFAULT_VALUE;
												bool foundDefiniteParentEntity = false;
												bool checkIsDefinite = true;
												GIAentityNode* parentTemp = getSameReferenceSetUniqueParent(entityNode, connection->sentenceIndexTemp, NULL, &foundDefiniteParentEntity, parseConditionParents, checkIsDefinite);
												if(!foundDefiniteParentEntity)
												{
													indefiniteChild = true;
												}
											}
											#endif
											bool substanceEntityDefinitionIsAChildOfTheSubstanceEntity = isSubstanceEntityDefinitionAChildOfTheSubstanceEntity(entityNode, targetEntity, connection);
											#ifdef NLC_SUPPORT_REDEFINITIONS_FOR_IMMEDIATELY_DECLARED_INDEFINITE_ENTITIES
											if(!substanceEntityDefinitionIsAChildOfTheSubstanceEntity)
											#else
											if(indefiniteChild || !substanceEntityDefinitionIsAChildOfTheSubstanceEntity)
											#endif
											{
											#endif
												#ifndef NLC_CREATE_A_SEPARATE_CLASS_FOR_CONCEPT_DEFINITIONS
												if(targetName != className)	//eg do not create a separate class for concept definitions
												{
												#endif
													addDefinitionToClassDefinition(classDefinition, targetClassDefinition);

												#ifndef NLC_CREATE_A_SEPARATE_CLASS_FOR_CONCEPT_DEFINITIONS
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
												//cout << "generateClassHeirarchy{}: classDefinition->functionList.push_back: " << targetClassDefinition->name << endl;
												#endif
												classDefinition->functionList.push_back(targetClassDefinition);

												#ifdef NLC_FUNCTIONS_SUPPORT_PLURAL_SUBJECTS
												//hasActionOwner is true for all actions (targetClassDefinition) with subjects (classDefinition);
												//added 1l1a for dynamic casting of children
												NLCitem* classDeclarationFunctionOwnerItem = new NLCitem(entityNode, NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION_OWNER);
												targetClassDefinition->parameters.push_back(classDeclarationFunctionOwnerItem);
												#endif

												NLCitem* classDeclarationFunctionItem = new NLCitem(targetEntity, NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION);	//added 1e1c
												targetClassDefinition->parameters.push_back(classDeclarationFunctionItem);

												if(hasActionObject)
												{
													NLCitem* classDeclarationFunctionObjectItem = new NLCitem(actionObjectName, NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION_OBJECT);	//for special case (as actions are referenced by instance)
													targetClassDefinition->parameters.push_back(classDeclarationFunctionObjectItem);
												}

												#ifdef NLC_RECORD_ACTION_HISTORY
												fillActionLists(classDefinitionList, true, hasActionObject, targetEntity->entityName, actionObjectName, entityNode->entityName);
												#endif

												#ifdef NLC_INTERPRET_ACTION_PROPERTIES_AND_CONDITIONS_AS_FUNCTION_ARGUMENTS
												//#ifdef NLC_SUPPORT_INPUT_FUNCTION_LISTS	//shouldn't this preprocessor requirement be enforced?
												generateFunctionPropertyConditionArgumentsWithActionNetworkIndexInheritance(targetEntity, &(targetClassDefinition->parameters));
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
				#ifdef NLC_CLASS_DEFINITIONS_DO_NOT_DEFINE_INHERITANCE_FOR_LOGICAL_CONDITION_CONCEPTS
				}
				#endif
			}
		}
	}

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
				//cout << "generateClassHeirarchy{}: NLC_CLASS_DEFINITIONS_USE_GENERIC_LIBRARY_ENTITY_CLASS: new NLCclassDefinition(" << targetName << endl;
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

bool addClassDefinitionToList(vector<NLCclassDefinition*>* classDefinitionList, string className, NLCclassDefinition** classDefinition)
{
	bool foundClassDefinition = false;
	*classDefinition = findClassDefinition(classDefinitionList, className, &foundClassDefinition);	//see if class definition already exists
	if(!foundClassDefinition)
	{
		*classDefinition = new NLCclassDefinition(className);
		classDefinitionList->push_back(*classDefinition);
		foundClassDefinition = true;
	}
	return foundClassDefinition;
}

void addDefinitionToClassDefinition(NLCclassDefinition* classDefinition, NLCclassDefinition* targetClassDefinition)
{
	//definitionList
	bool foundLocalClassDefinition = false;
	NLCclassDefinition* localClassDefinition = findClassDefinition(&(classDefinition->definitionList), targetClassDefinition->name, &foundLocalClassDefinition);	//see if class definition already exists
	if(!foundLocalClassDefinition)
	{
		#ifdef NLC_DEBUG
		//cout << "generateClassHeirarchy{}: classDefinition->definitionList.push_back: " << targetClassDefinition->name << endl;
		#endif

		classDefinition->definitionList.push_back(targetClassDefinition);
	}
}

void addPropertyListToClassDefinition(NLCclassDefinition* classDefinition, NLCclassDefinition* targetClassDefinition)
{
	//propertyList
	bool foundLocalClassDefinition = false;
	NLCclassDefinition* localClassDefinition = findClassDefinition(&(classDefinition->propertyList), targetClassDefinition->name, &foundLocalClassDefinition);	//see if class definition already exists
	if(!foundLocalClassDefinition)
	{
		#ifdef NLC_DEBUG
		//cout << "generateClassHeirarchy{}: classDefinition->propertyList.push_back: " << targetClassDefinition->name << endl;
		#endif
		classDefinition->propertyList.push_back(targetClassDefinition);

		NLCitem* classDeclarationPropertiesListItem = new NLCitem(targetClassDefinition->name, NLC_ITEM_TYPE_CLASS_DECLARATION_PROPERTY_LIST);	//CHECKTHIS
		targetClassDefinition->parameters.push_back(classDeclarationPropertiesListItem);
	}
}



#ifdef NLC_CLASS_DEFINITIONS_DO_NOT_DEFINE_INHERITANCE_FOR_LOGICAL_CONDITION_CONCEPTS
bool entityIsConceptAndInLogicalCondition(GIAentityNode* entity, NLCfunction* currentNLCfunctionInList)
{
	bool result = false;
	NLCsentence* currentNLCsentenceInList = currentNLCfunctionInList->firstNLCsentenceInFunction;
	while(currentNLCsentenceInList->next != NULL)
	{
		if(currentNLCsentenceInList->sentenceIndex == entity->sentenceIndexTemp)	//note (with USE_NLC) separate concept entites are created for logical condition NLP parsable phrases (GIA advanced referencing is not applied), therefore a direct test of sentenceIndexTemp can be made
		{
			if(sentencePertainsToLogicalCondition(currentNLCsentenceInList))
			{
				if(entity->entityType == GIA_ENTITY_TYPE_TYPE_CONCEPT)
				{
					result = true;
				}
			}
		}

		currentNLCsentenceInList = currentNLCsentenceInList->next;
	}
	return result;

}
#endif

#ifdef NLC_CLASS_DEFINITIONS_DO_NOT_DEFINE_INHERITANCE_FOR_REDEFINITIONS
bool isSubstanceEntityDefinitionAChildOfTheSubstanceEntity(GIAentityNode* substanceEntity, GIAentityNode* parentEntity, GIAentityConnection* connection)
{
	bool parentClassIsChildOfChildClass = false;


	if(substanceEntity->entityType == GIA_ENTITY_TYPE_TYPE_CONCEPT)	//added 1t2g
	{
		//ignore this case
	}
	#ifndef GIA_CREATE_NON_SPECIFIC_CONCEPTS_FOR_ALL_NETWORK_INDEXES
	else if(substanceEntity->entityType == GIA_ENTITY_TYPE_TYPE_NETWORK_INDEX))	//added 1t2g (old implementation: 1r1a)
	{
		//ignore this case
	}
	#endif
	else if(parentEntity->entityType != GIA_ENTITY_TYPE_TYPE_CONCEPT)
	{
		#ifdef NLC_USE_ADVANCED_REFERENCING_SUPPORT_ALIASES
		if(!(connection->isAlias))
		{
			cout << "isSubstanceEntityDefinitionAChildOfTheSubstanceEntity{} error: a substance has a non-alias definition connection to a substance" << endl;
			exit(0);
		}
		#endif
	}
	else
	{
		GIAentityNode* parentNetworkIndexEntity = parentNetworkIndexEntity = getPrimaryNetworkIndexNodeDefiningInstance(parentEntity);
		for(vector<GIAentityConnection*>::iterator connectionIter = parentNetworkIndexEntity->associatedInstanceNodeList->begin(); connectionIter != parentNetworkIndexEntity->associatedInstanceNodeList->end(); connectionIter++)
		{
			GIAentityNode* parentConceptEntity = (*connectionIter)->entity;
			if(parentConceptEntity->entityType == GIA_ENTITY_TYPE_TYPE_CONCEPT)
			{
				for(vector<GIAentityConnection*>::iterator connectionIter2 = parentConceptEntity->entityNodeDefinitionList->begin(); connectionIter2 != parentConceptEntity->entityNodeDefinitionList->end(); connectionIter2++)
				{
					GIAentityNode* parentConceptParentEntity = (*connectionIter2)->entity;
					if(parentConceptParentEntity->entityName == substanceEntity->entityName)
					{
						parentClassIsChildOfChildClass = true;
					}
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
		//cout << "generateClassHeirarchy{}: classDefinition->conditionList.push_back: " << targetClassDefinition->name << endl;
		#endif

		classDefinition->conditionList.push_back(targetClassDefinition);

		NLCitem* classDeclarationConditionsListItem = new NLCitem(targetEntity, NLC_ITEM_TYPE_CLASS_DECLARATION_CONDITION_LIST);

		if(!(targetEntity->conditionObjectEntity->empty()))
		{
			string conditionObjectClassName = generateClassName((targetEntity->conditionObjectEntity->back())->entity);
			classDeclarationConditionsListItem->className2 = conditionObjectClassName;
			#ifdef NLC_DEBUG
			//cout << "\tgenerateClassHeirarchy{}: conditionObjectClassName = " << conditionObjectClassName << endl;
			#endif
		}
		else
		{
			cout << "generateClassHeirarchy{} error: condition has no object" << endl;
		}

		targetClassDefinition->parameters.push_back(classDeclarationConditionsListItem);
	}

	return result;
}

#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE
bool generateClassHeirarchyFunctions(vector<NLCclassDefinition*>* classDefinitionList, vector<GIAentityNode*>* entityNodesActiveListComplete, NLCclassDefinition* parentFunctionDependencyClassDefinition)
{
	#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
	cout << "generateClassHeirarchyFunctions:" << endl;
	#endif

	bool result = true;

	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode* actionEntity = *entityIter;

		#ifdef NLC_DEBUG
		//cout << "generateClassHeirarchyFunctions{}: actionEntity = " << actionEntity->entityName << endl;
		#endif
		//valid class checks added 1g12f 14-July-2014
		if(!(actionEntity->disabled))
		{
			if(generateClassHeirarchyValidClassChecks(actionEntity))
			{
				if(actionEntity->entityType == GIA_ENTITY_TYPE_TYPE_ACTION)
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

					//valid class contents checks added 1g12f 14-July-2014
					if(passSubjectObjectValidClassChecks)
					{
						#ifdef NLC_DEBUG
						//cout << "generateClassHeirarchyFunctions{}: passSubjectObjectValidClassChecks, actionEntity = " << actionEntity->entityName << endl;
						#endif

						string functionName = actionEntity->entityName;
						string functionOwnerName = actionSubjectName;
						string functionObjectName = actionObjectName;
						bool hasFunctionOwnerClass = hasActionSubject;
						bool hasFunctionObjectClass = hasActionObject;
						bool foundFunctionOwnerExactMatch = false;
						bool foundFunctionObjectExactMatch = false;
						bool rearrangeClassList = false;
						NLCclassDefinition* functionDefinitionClassDefinition = NULL;
						#ifdef NLC_DEBUG
						cout << "hasFunctionOwnerClass = " << hasFunctionOwnerClass << endl;
						cout << "hasFunctionObjectClass = " << hasFunctionObjectClass << endl;
						cout << "functionName = " << functionName << endl;
						cout << "functionOwnerName = " << functionOwnerName << endl;
						cout << "functionObjectName = " << functionObjectName << endl;
						#endif
						//look for both exact and non-exact matches here as functionDependencies have already been created for all functions explicitly declared+defined by the user (don't yet reconcile arguments however)
						if(findFunctionDefinitionClassDefinitionExactOrNonExactMatch(classDefinitionList, functionName, functionOwnerName, functionObjectName, hasFunctionOwnerClass, hasFunctionObjectClass, &functionDefinitionClassDefinition, rearrangeClassList, &foundFunctionOwnerExactMatch, &foundFunctionObjectExactMatch))
						{
							#ifdef NLC_DEBUG
							cout << "findFunctionDefinitionClassDefinitionExactOrNonExactMatch pass: " << functionName << endl;
							cout << "findFunctionDefinitionClassDefinitionExactOrNonExactMatch pass: " << functionOwnerName << endl;
							cout << "findFunctionDefinitionClassDefinitionExactOrNonExactMatch pass: " << functionObjectName << endl;
							#endif
							NLCclassDefinitionFunctionDependency* functionDependenciesInParentTemp = NULL;
							bool foundFunctionDependencyInParent = findFunctionDependencyInParent(parentFunctionDependencyClassDefinition, functionName, functionOwnerName, functionObjectName, hasFunctionOwnerClass, hasFunctionObjectClass, &functionDependenciesInParentTemp);
							if(!foundFunctionDependencyInParent)
							{
								parentFunctionDependencyClassDefinition->functionDependencyList.push_back(functionDefinitionClassDefinition);
							}

							#ifdef NLC_RECORD_ACTION_HISTORY
							fillActionLists(classDefinitionList, hasActionSubject, hasActionObject, actionEntity->entityName, actionObjectName, actionSubjectName);
							#endif
						}
						else
						{
							#ifdef NLC_DEBUG
							cout << "findFunctionDefinitionClassDefinitionExactOrNonExactMatch fail: " << functionName << endl;
							cout << "findFunctionDependencyInList: " << functionName << endl;
							#endif
							//function execution reference does not correspond to a new function definition, so create a function declaration for it

							NLCclassDefinition* functionReferenceClassDefinition = NULL;
							bool foundFunctionDependencyInList = findFunctionDependencyClassDefinitionInList(classDefinitionList, functionName, functionOwnerName, functionObjectName, true, hasFunctionObjectClass, &functionReferenceClassDefinition);
							bool duplicateFunctionDeclarationDetected = false;
							if(foundFunctionDependencyInList)
							{
								//this will be true if an action (function reference) has been declared twice, but the action (function) has not been defined, eg "A chicken ate a pie. The chicken that ate a pie rowed the boat."
								#ifdef NLC_DEBUG
								cout << "generateClassHeirarchyFunctions{}: foundFunctionDependencyInList" << endl;
								cout << "functionName: " << functionName << endl;
								cout << "functionOwnerName: " << functionOwnerName << endl;
								cout << "functionObjectName: " << functionObjectName << endl;
								#endif
								#ifndef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE_DO_NOT_ADD_FUNCTION_DEPENDENCY_FOR_FUNCTION_REFERENCES
								NLCclassDefinitionFunctionDependency* functionDependenciesInParentTemp = NULL;
								bool foundFunctionDependencyInParent = findFunctionDependencyInParent(parentFunctionDependencyClassDefinition, functionName, functionOwnerName, functionObjectName, true, hasFunctionObjectClass, &functionDependenciesInParentTemp);
								if(!foundFunctionDependencyInParent)
								{
									#ifdef NLC_DEBUG
									//cout << "generateClassHeirarchyFunctions{}: !foundFunctionDependencyInParent" << endl;
									#endif
									parentFunctionDependencyClassDefinition->functionDependencyList.push_back(functionReferenceClassDefinition);
								}
								else
								{
									#ifdef NLC_DEBUG
									//cout << "generateClassHeirarchyFunctions{}: foundFunctionDependencyInParent" << endl;
									#endif
									duplicateFunctionDeclarationDetected = true;
									//duplicate function declarations will be ignored
								}
								#else
								cout << "generateClassHeirarchyFunctions{} error: !findFunctionDefinitionClassDefinitionExactOrNonExactMatch && findFunctionDependencyClassDefinitionInList" << endl;
								cout << "functionName: " << functionName << endl;
								cout << "functionOwnerName: " << functionOwnerName << endl;
								cout << "functionObjectName: " << functionObjectName << endl;
								exit(0);
								#endif

							}
							else
							{
								#ifdef NLC_DEBUG
								cout << "generateClassHeirarchyFunctions{}: !foundFunctionDependencyInList" << endl;
								cout << "generateClassHeirarchyFunctions{}: functionName = " << functionName << endl;
								cout << "generateClassHeirarchyFunctions{}: functionOwnerName = " << functionOwnerName << endl;
								cout << "generateClassHeirarchyFunctions{}: functionObjectName = " << functionObjectName << endl;
								#endif

								#ifndef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE_DO_NOT_ADD_FUNCTION_DEPENDENCY_FOR_FUNCTION_REFERENCES
								NLCclassDefinitionFunctionDependency* functionDependency = new NLCclassDefinitionFunctionDependency();
								functionDependency->functionName = functionName;
								functionDependency->functionOwnerName = functionOwnerName;
								functionDependency->functionObjectName = functionObjectName;
								#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE_PATCH
								functionDependency->hasFunctionOwnerClass = hasFunctionOwnerClass;	//changed from true 1l1a
								#else
								functionDependency->hasFunctionOwnerClass = true;
								#endif
								functionDependency->hasFunctionObjectClass = hasFunctionObjectClass;
								functionDependency->isReferenceElseFunctionDefinition = true;		//functionReference functionDependency assigned
								#endif

								string classDefinitionFunctionOwnerName = "";
								if(hasActionSubject)
								{
									classDefinitionFunctionOwnerName = generateClassName(actionSubject);
									#ifdef NLC_CREATE_A_SEPARATE_CLASS_FOR_CONCEPT_DEFINITIONS
									if(actionEntity->entityType == GIA_ENTITY_TYPE_TYPE_CONCEPT)
									{
										classDefinitionFunctionOwnerName = generateConceptClassName(actionSubject);	//is this still required?
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
									//cout << "generateClassHeirarchyFunctions{}: !foundClassDefinitionFunctionOwner" << endl;
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
									//cout << "generateClassHeirarchyFunctions{}: !foundClassDefinitionFunction" << endl;
									//cout << "new NLCclassDefinition(" << classDefinitionFunctionName << endl;
									#endif
								}

								#ifndef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE_DO_NOT_ADD_FUNCTION_DEPENDENCY_FOR_FUNCTION_REFERENCES
								classDefinitionFunction->functionDependency = functionDependency;	//new for 1p4a - functionDependencies are now currently assigned to functionReference classDefinitions (not just functionDefinition classDefinitions)
								parentFunctionDependencyClassDefinition->functionDependencyList.push_back(classDefinitionFunction);
								#endif

								classDefinitionFunction->functionNameSpecial = generateFunctionName(actionEntity);
								#ifdef NLC_SUPPORT_INPUT_FUNCTION_LISTS_CHECK_ACTION_SUBJECT_CONTENTS_FOR_IMPLICITLY_DECLARED_PARAMETERS
								classDefinitionFunction->actionOrConditionInstance = actionEntity;
								#endif
								classDefinitionFunction->isActionOrConditionInstanceNotClass = true;

								bool foundLocalClassDefinitionFunction = false;
								/*
								cout << "functionName = " << functionName << endl;
								cout << "functionOwnerName = " << functionOwnerName << endl;
								cout << "functionObjectName = " << functionObjectName << endl;
								*/
								#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE_DO_NOT_ADD_FUNCTION_DEPENDENCY_FOR_FUNCTION_REFERENCES
								NLCclassDefinition* localClassDefinitionFunction = findClassDefinitionFunction(&(classDefinitionFunctionOwner->functionList), functionName, functionOwnerName, functionObjectName, hasFunctionOwnerClass, hasFunctionObjectClass, &foundLocalClassDefinitionFunction);	//see if class definition already exists
								#else
								NLCclassDefinition* localClassDefinitionFunction = findClassDefinition(&(classDefinitionFunctionOwner->functionList), classDefinitionFunctionName, &foundLocalClassDefinitionFunction);	//see if class definition already exists	//note this check will not work for functions because they are added by instance (but unique functionDependency check has already been performed above so this unique functionReference in functionList check is not required and will always give !foundLocalClassDefinitionFunction)
								#endif
								if(!foundLocalClassDefinitionFunction)
								{
									//declare functions

									/*
									#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE
									classDefinitionFunction->functionDependency = functionDependency;	//already set
									#endif
									*/

									classDefinitionFunctionOwner->functionList.push_back(classDefinitionFunction);

									#ifdef NLC_FUNCTIONS_SUPPORT_PLURAL_SUBJECTS
									//added 1l1a for dynamic casting of children
									if(hasFunctionOwnerClass)
									{
										NLCitem* classDeclarationFunctionOwnerItem = new NLCitem(actionSubject, NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION_OWNER);	//corrected 1p5a
										classDefinitionFunction->parameters.push_back(classDeclarationFunctionOwnerItem);
									}
									#endif

									NLCitem* classDeclarationFunctionItem = new NLCitem(actionEntity, NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION);	//added 1e1c
									classDefinitionFunction->parameters.push_back(classDeclarationFunctionItem);

									if(hasFunctionObjectClass)
									{
										NLCitem* classDeclarationFunctionObjectItem = new NLCitem(actionObjectName, NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION_OBJECT);	//for special case (as actions are referenced by instance)	//why use actionObject instead of actionObjectName?
										classDefinitionFunction->parameters.push_back(classDeclarationFunctionObjectItem);
									}

									#ifdef NLC_RECORD_ACTION_HISTORY
									fillActionLists(classDefinitionList, hasActionSubject, hasActionObject, actionEntity->entityName, actionObjectName, actionSubjectName);	//fillActionLists will find classDefinitionFunctionOwner
									#endif

									#ifdef NLC_INTERPRET_ACTION_PROPERTIES_AND_CONDITIONS_AS_FUNCTION_ARGUMENTS
									//#ifdef NLC_SUPPORT_INPUT_FUNCTION_LISTS	//shouldn't this preprocessor requirement be enforced?
									generateFunctionPropertyConditionArgumentsWithActionNetworkIndexInheritance(actionEntity, &(classDefinitionFunction->parameters));
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

	return result;
}
#endif

#ifdef NLC_RECORD_ACTION_HISTORY
void fillActionLists(vector<NLCclassDefinition*>* classDefinitionList, bool hasActionSubject, bool hasActionObject, string actionName, string actionObjectName, string actionSubjectName)
{
	bool foundClassDefinitionAction = false;
	string actionClassName =  generateClassName(actionName);
	NLCclassDefinition* classDefinitionAction = findClassDefinition(classDefinitionList, actionClassName, &foundClassDefinitionAction);	//see if class definition already exists
	if(!foundClassDefinitionAction)
	{
		classDefinitionAction = new NLCclassDefinition(actionClassName);
		classDefinitionList->push_back(classDefinitionAction);
	}

	if(hasActionSubject)
	{
		string classDefinitionFunctionOwnerName = generateClassName(actionSubjectName);
		bool foundClassDefinitionFunctionOwner = false;
		NLCclassDefinition* classDefinitionFunctionOwner = findClassDefinition(classDefinitionList, classDefinitionFunctionOwnerName, &foundClassDefinitionFunctionOwner);	//see if class definition already exists
		if(!foundClassDefinitionFunctionOwner)
		{
			classDefinitionFunctionOwner = new NLCclassDefinition(classDefinitionFunctionOwnerName);
			classDefinitionList->push_back(classDefinitionFunctionOwner);
			classDefinitionFunctionOwner->actionList.push_back(classDefinitionAction);
			classDefinitionAction->actionSubjectList.push_back(classDefinitionFunctionOwner);
		}
		else
		{
			bool foundLocalClassDefinitionAction = false;
			NLCclassDefinition* localClassDefinitionAction = findClassDefinition(&(classDefinitionFunctionOwner->actionList), actionClassName, &foundLocalClassDefinitionAction);	//see if class definition already exists
			if(!foundLocalClassDefinitionAction)
			{
				classDefinitionFunctionOwner->actionList.push_back(classDefinitionAction);

			}
			bool foundLocalClassDefinitionActionOwner = false;
			string actionOwnerClassName = classDefinitionFunctionOwner->name;
			NLCclassDefinition* localClassDefinitionActionOwner = findClassDefinition(&(classDefinitionAction->actionSubjectList), actionOwnerClassName, &foundLocalClassDefinitionActionOwner);	//see if class definition already exists
			if(!foundLocalClassDefinitionActionOwner)
			{
				classDefinitionAction->actionSubjectList.push_back(classDefinitionFunctionOwner);
			}
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
		#ifdef NLC_DEBUG
		//cout << "entityNode->entityName = " << entityNode->entityName << endl;
		#endif
		validClass = false;
	}
	#ifdef NLC_PREPROCESSOR_INTERPRET_SINGLE_WORD_SENTENCES_AS_ACTIONS_REPLACE_ACTION_ALSO_DUE_TO_NLP_LIMITATION
	if(entityNode->entityName == NLC_PREPROCESSOR_INTERPRET_SINGLE_WORD_SENTENCES_AS_ACTIONS_DUMMY_TEXT_ACTION)
	{
		validClass = false;
	}
	#endif
	#endif
	#ifdef GIA_CREATE_NON_SPECIFIC_CONCEPTS_FOR_ALL_NETWORK_INDEXES
	if(entityNode->entityType == GIA_ENTITY_TYPE_TYPE_NETWORK_INDEX)	//added 1n2f
	{
		validClass = false;
	}
	#endif
	#ifdef NLC_USE_ADVANCED_REFERENCING_SUPPORT_ALIASES
	if(entityNode->NLCisAlias)
	{
		validClass = false;
	}
	#endif

	if(isStringNumberOrFractional(entityNode->entityName))
	{
		validClass = false;
	}

	/*
	cout << "\nentityNode->entityName = " << entityNode->entityName << endl;
	cout << "entityNode->isSubstance = " << entityNode->isSubstance << endl;
	cout << "entityNode->isNetworkIndex = " << entityNode->isNetworkIndex << endl;
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

	//added 1q14f
	if(isStringAliasFileName(entityNode->entityName))
	{
		validClass = false;
	}

	#ifdef NLC_VERIFY_LEGAL_TARGET_SOURCE_CHARACTERS
	//added 1q14f - CHECKTHIS: is this required?
	if(isStringIllegalTargetSourceCharacter(entityNode->entityName))
	{
		if(validClass)
		{
			cout << "printClassHeirarchyValidDefinitionClassChecks{} error: isStringIllegalTargetSourceCharacter; entityNode->entityName = " << entityNode->entityName << endl;
		}
		validClass = false;
	}
	#endif

	return validClass;
}

bool generateClassHeirarchyTargetValidClassChecks(GIAentityNode* targetEntity)
{
	bool validClass = generateClassHeirarchyValidClassChecks(targetEntity);

	return validClass;
}




#ifdef NLC_CREATE_A_SEPARATE_CLASS_FOR_CONCEPT_DEFINITIONS
string generateConceptClassName(GIAentityNode* conceptEntity)
{
	string conceptClassName = conceptEntity->entityName;
	generateConceptClassNameRecurse(conceptEntity, &conceptClassName);
	conceptClassName = conceptClassName + NLC_CLASS_NAME_APPEND;
	return conceptClassName;
}

void generateConceptClassNameRecurse(GIAentityNode* conceptEntity, string* conceptClassName)
{
	for(vector<GIAentityConnection*>::iterator entityIter = conceptEntity->conditionNodeList->begin(); entityIter != conceptEntity->conditionNodeList->end(); entityIter++)
	{
		GIAentityNode* conceptCondition = (*entityIter)->entity;
		#ifdef NLC_NORMALISE_TWOWAY_PREPOSITIONS_DUAL_CONDITION_LINKS_ENABLED
		if(!(conceptCondition->inverseConditionTwoWay) || (*entityIter)->isReferenceElseFunctionDefinition)		//prevent infinite loop for 2 way conditions
		{
		#endif
			if(!(conceptCondition->conditionObjectEntity->empty()))
			{
				GIAentityNode* conceptConditionObject = (conceptCondition->conditionObjectEntity->back())->entity;
				*conceptClassName = *conceptClassName + NLC_CONCEPT_CLASS_PREPEND + conceptCondition->entityName + conceptConditionObject->entityName + NLC_CONCEPT_CLASS_CONDITION;
				*conceptClassName = *conceptClassName + generateConceptClassNameRecurse(conceptConditionObject, conceptClassName);	//recurse in case of very detailed concept eg "red dogs next to blue cows"
			}
			else
			{
				cout << "generateConceptClassNameRecurse{} error: condition has no object" << endl;
			}
		#ifdef NLC_NORMALISE_TWOWAY_PREPOSITIONS_DUAL_CONDITION_LINKS_ENABLED
		}
		#endif
	}
	for(vector<GIAentityConnection*>::iterator entityIter = conceptEntity->propertyNodeList->begin(); entityIter != conceptEntity->propertyNodeList->end(); entityIter++)
	{
		GIAentityNode* conceptProperty = (*entityIter)->entity;
		*conceptClassName = *conceptClassName + NLC_CONCEPT_CLASS_PREPEND + conceptProperty->entityName + NLC_CONCEPT_CLASS_PROPERTY;
		*conceptClassName = *conceptClassName + generateConceptClassNameRecurse(conceptProperty, conceptClassName);	//recurse in case of very detailed concept eg "red dogs next to blue cows"
	}
}

#endif

#ifdef NLC_PREVENT_INHERITANCE_DOUBLE_DECLARATIONS_OF_CLASS_LIST_VARIABLES

void preventDoubleDeclarationsOfClassDefinitionVariablesInHeirachy(vector<NLCclassDefinition*>* classDefinitionList)
{
	//disable all double declarations
	for(vector<NLCclassDefinition*>::iterator classDefinitionIter = classDefinitionList->begin(); classDefinitionIter != classDefinitionList->end(); classDefinitionIter++)
	{
		NLCclassDefinition* classDefinition = *classDefinitionIter;
		eraseDuplicateClassDefinitionSublistItemIfFoundInParentClassDefinitionSublist(classDefinition, &(classDefinition->propertyList), GIA_ENTITY_VECTOR_CONNECTION_TYPE_PROPERTIES);	//changed from GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTIONS, 1k8b
		eraseDuplicateClassDefinitionSublistItemIfFoundInParentClassDefinitionSublist(classDefinition, &(classDefinition->conditionList), GIA_ENTITY_VECTOR_CONNECTION_TYPE_CONDITIONS);
		eraseDuplicateClassDefinitionSublistItemIfFoundInParentClassDefinitionSublist(classDefinition, &(classDefinition->functionList), NLC_ENTITY_VECTOR_CONNECTION_TYPE_FUNCTIONS);
		#ifdef NLC_RECORD_ACTION_HISTORY
		eraseDuplicateClassDefinitionSublistItemIfFoundInParentClassDefinitionSublist(classDefinition, &(classDefinition->actionList), GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTIONS);
		eraseDuplicateClassDefinitionSublistItemIfFoundInParentClassDefinitionSublist(classDefinition, &(classDefinition->actionIncomingList), GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTIONS);
		eraseDuplicateClassDefinitionSublistItemIfFoundInParentClassDefinitionSublist(classDefinition, &(classDefinition->actionSubjectList), GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTION_SUBJECT);	//?not currently required as actionSubject/actionObject lists are defined after function (arguments) have been reconciled
		eraseDuplicateClassDefinitionSublistItemIfFoundInParentClassDefinitionSublist(classDefinition, &(classDefinition->actionObjectList), GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTION_OBJECT);		//?not currently required as actionSubject/actionObject lists are defined after function (arguments) have been reconciled
		#endif
	}
}

void eraseDuplicateClassDefinitionSublistItemIfFoundInParentClassDefinitionSublist(NLCclassDefinition* classDefinition, vector<NLCclassDefinition*>* classDefinitionSublist, int variableType)
{
	for(vector<NLCclassDefinition*>::iterator localListIter = classDefinitionSublist->begin(); localListIter != classDefinitionSublist->end();)
	{
		bool localListIterErased = false;
		NLCclassDefinition* variableClassDefinition = *localListIter;
		string variableName = variableClassDefinition->name;
		#ifdef NLC_DEBUG
		//cout << "variableName = " << variableName << endl;
		//cout << "variableType = " << entityVectorConnectionNameArray[min(variableType, 12)] << endl;
		#endif
		for(vector<NLCclassDefinition*>::iterator parentListIter = classDefinition->definitionList.begin(); parentListIter != classDefinition->definitionList.end(); parentListIter++)
		{
			if(!localListIterErased)
			{
				NLCclassDefinition* targetClassDefinition = *parentListIter;
				#ifdef NLC_DEBUG
				//cout << "targetClassDefinition = " << targetClassDefinition->name << endl;
				#endif

				if(findVariableInParentClass(targetClassDefinition, variableName, variableType))
				{
					localListIter = classDefinitionSublist->erase(localListIter);
					localListIterErased = true;
					#ifdef NLC_DEBUG
					cout << "eraseDuplicateClassDefinitionSublistItemIfFoundInParentClassDefinitionSublist{}: localListIterErased" << endl;
					cout << "variableClassDefinition->name = " << variableClassDefinition->name << endl;
					cout << "classDefinition->name = " << classDefinition->name << endl;
					cout << "targetClassDefinition->name = " << targetClassDefinition->name << endl;
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
	else if(variableType == NLC_ENTITY_VECTOR_CONNECTION_TYPE_FUNCTIONS)
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
	#ifdef NLC_RECORD_ACTION_HISTORY
	else if(variableType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTIONS)
	{
		for(vector<NLCclassDefinition*>::iterator localListIter = classDefinition->actionList.begin(); localListIter != classDefinition->actionList.end(); localListIter++)
		{
			NLCclassDefinition* targetClassDefinition = *localListIter;
			string targetName = targetClassDefinition->name;
			if(targetName == variableName)
			{
				foundVariable = true;
			}
		}
	}
	else if(variableType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_INCOMING_ACTIONS)
	{
		for(vector<NLCclassDefinition*>::iterator localListIter = classDefinition->actionIncomingList.begin(); localListIter != classDefinition->actionIncomingList.end(); localListIter++)
		{
			NLCclassDefinition* targetClassDefinition = *localListIter;
			string targetName = targetClassDefinition->name;
			if(targetName == variableName)
			{
				foundVariable = true;
			}
		}
	}
	else if(variableType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTION_SUBJECT)
	{
		for(vector<NLCclassDefinition*>::iterator localListIter = classDefinition->actionSubjectList.begin(); localListIter != classDefinition->actionSubjectList.end(); localListIter++)
		{
			NLCclassDefinition* targetClassDefinition = *localListIter;
			string targetName = targetClassDefinition->name;
			if(targetName == variableName)
			{
				foundVariable = true;
			}
		}
	}
	else if(variableType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTION_OBJECT)
	{
		for(vector<NLCclassDefinition*>::iterator localListIter = classDefinition->actionObjectList.begin(); localListIter != classDefinition->actionObjectList.end(); localListIter++)
		{
			NLCclassDefinition* targetClassDefinition = *localListIter;
			string targetName = targetClassDefinition->name;
			if(targetName == variableName)
			{
				foundVariable = true;
			}
		}
	}
	#endif
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
void generateFunctionPropertyConditionArgumentsWithActionNetworkIndexInheritance(GIAentityNode* actionEntity, vector<NLCitem*>* parameters)
{
	generateFunctionPropertyConditionArguments(actionEntity, parameters, false);

	#ifdef GIA_TRANSLATOR_DREAM_MODE_LINK_SPECIFIC_CONCEPTS_AND_ACTIONS
	//Part b: generate object initialisations based on action networkIndexes (class inheritance)
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





