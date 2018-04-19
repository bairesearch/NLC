/*******************************************************************************
 *
 * No License
 * 
 * This work is under exclusive copyright (c) Baxter AI (baxterai.com). 
 * Nobody else can use, copy, distribute, or modify this work without being 
 * at risk of take-downs, shake-downs, or litigation. 
 * 
 * By publishing this source code in a public repository on GitHub, Terms of 
 * Service have been accepted by which Baxter AI have allowed others to view 
 * and fork their repository.
 * 
 * If you find software that doesn't have a license, that generally means you 
 * have no permission from the creators of the software to use, modify, or 
 * share the software. Although a code host such as GitHub may allow you to 
 * view and fork the code, this does not imply that you are permitted to use, 
 * modify, or share the software for any purpose.
 *
 * This notice has been derived from https://choosealicense.com/no-permission 
 * (https://web.archive.org/web/20180312144938/https://choosealicense.com/no-permission)
 *
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: NLCtranslatorClassDefinitions.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2018 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler
 * Project Version: 2f1b 22-February-2018
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 * /
 *******************************************************************************/


#include "NLCtranslatorClassDefinitions.hpp"

#ifdef NLC_CLASS_DEFINITIONS_DO_NOT_DEFINE_INHERITANCE_FOR_REDEFINITIONS
#endif


bool NLCtranslatorClassDefinitionsClass::generateClassHeirarchy(vector<NLCclassDefinition*>* classDefinitionList, vector<GIAentityNode*>* entityNodesActiveListComplete, const NLCfunction* currentNLCfunctionInList)
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
					string className = NLCitemClass.generateClassName(entityNode);
					#ifdef NLC_CREATE_A_SEPARATE_CLASS_FOR_CONCEPT_DEFINITIONS
					if(entityNode->entityType == GIA_ENTITY_TYPE_CONCEPT)
					{
						className = generateConceptClassName(entityNode);
					}
					#endif

					NLCclassDefinition* classDefinition = NULL;
					addClassDefinitionToList(classDefinitionList, className, &classDefinition);

					for(int i=0; i<GIA_ENTITY_NUMBER_OF_VECTOR_CONNECTION_TYPES; i++)
					{
						for(vector<GIAentityConnection*>::iterator connectionIter = entityNode->entityVectorConnectionsArray[i].begin(); connectionIter != entityNode->entityVectorConnectionsArray[i].end(); connectionIter++)
						{
							GIAentityConnection* connection = *connectionIter;
							GIAentityNode* targetEntity = connection->entity;

							//skip over property/definition relationship entities;
							if(i == GIA_ENTITY_VECTOR_CONNECTION_TYPE_PROPERTY)
							{
								targetEntity = GIAtranslatorOperations.getPropertyRelationshipObjectEntity(connection);
							}
							else if(i == GIA_ENTITY_VECTOR_CONNECTION_TYPE_DEFINITION)
							{
								targetEntity = GIAtranslatorOperations.getDefinitionRelationshipObjectEntity(connection);
							}
							else if(i == GIA_ENTITY_VECTOR_CONNECTION_TYPE_PROPERTY_REVERSE)
							{
								targetEntity = GIAtranslatorOperations.getPropertyRelationshipSubjectEntity(connection);
							}
							else if(i == GIA_ENTITY_VECTOR_CONNECTION_TYPE_DEFINITION_REVERSE)
							{
								targetEntity = GIAtranslatorOperations.getDefinitionRelationshipSubjectEntity(connection);
							}											
											
							#ifdef NLC_ADVANCED_REFERENCING_SUPPORT_ALIASES
							if(!GIAtranslatorOperations.connectionIsAlias(connection))
							{
							#endif
								//valid class contents checks added 1g12f 14-July-2014
								if(generateClassHeirarchyTargetValidClassChecks(targetEntity))
								{
									if(!(targetEntity->disabled))
									{

										string targetName = "";
										string targetClassName = "";
										if(i == GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTION)	//in GIA actions are treated as special connections with intermediary nodes
										{
											targetName = NLCitemClass.generateInstanceName(targetEntity);
										}
										#ifdef NLC_CREATE_A_SEPARATE_CLASS_FOR_CONCEPT_DEFINITIONS
										else if((i == GIA_ENTITY_VECTOR_CONNECTION_TYPE_DEFINITION) && (targetEntity->entityType == GIA_ENTITY_TYPE_CONCEPT))
										{
											targetName = generateConceptClassName(targetEntity);
										}
										#endif
										else
										{
											targetName = NLCitemClass.generateClassName(targetEntity);
										}

										bool foundTargetClassDefinition = false;
										NLCclassDefinition* targetClassDefinition = NULL;
										if(i == GIA_ENTITY_VECTOR_CONNECTION_TYPE_CONDITION)
										{
											targetClassDefinition = NLCclassDefinitionClass.findClassDefinitionCondition(classDefinitionList, targetEntity, &foundTargetClassDefinition);	//see if class definition already exists
										}
										else
										{
											targetClassDefinition = NLCclassDefinitionClass.findClassDefinition(classDefinitionList, targetName, &foundTargetClassDefinition);	//see if class definition already exists
										}

										if(!foundTargetClassDefinition)
										{
											targetClassDefinition = new NLCclassDefinition(targetName);
											classDefinitionList->push_back(targetClassDefinition);
										}

										if(i == GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTION)
										{
											targetClassDefinition->functionNameSpecial = NLCitemClass.generateFunctionName(targetEntity);
											#ifdef NLC_INPUT_FUNCTION_LISTS_CHECK_ACTION_SUBJECT_CONTENTS_FOR_IMPLICITLY_DECLARED_PARAMETERS
											targetClassDefinition->actionOrConditionInstance = targetEntity;
											#endif
										}
										if(i == GIA_ENTITY_VECTOR_CONNECTION_TYPE_CONDITION)
										{
											targetClassDefinition->isConditionInstance = true;
										}

										#ifndef NLC_DEBUG_PRINT_HIDDEN_CLASSES
										#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS
										if((i == GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTION) || (i == GIA_ENTITY_VECTOR_CONNECTION_TYPE_CONDITION))	//removed; ((targetEntity->entityType == GIA_ENTITY_TYPE_CONDITION) && !(targetEntity->entityType == GIA_ENTITY_TYPE_NETWORK_INDEX) ||) 16 April 2014	//restored || (i == GIA_ENTITY_VECTOR_CONNECTION_TYPE_CONDITION) 1m3a
										#else
										if((targetEntity->entityType == GIA_ENTITY_TYPE_ACTION) && !(targetEntity->entityType == GIA_ENTITY_TYPE_NETWORK_INDEX))	//removed; || (targetEntity->entityType == GIA_ENTITY_TYPE_CONDITION) 16 April 2014	//removed || (targetEntity->isActionConcept) 1u15a
										#endif
										#endif
										{
											targetClassDefinition->isActionOrConditionInstanceNotClass = true;
										}

										if(i == GIA_ENTITY_VECTOR_CONNECTION_TYPE_PROPERTY)
										{//declare subclass
											//cout << "classDefinition = " << classDefinition->name << endl;
											//cout << "targetClassDefinition = " << targetClassDefinition->name << endl;
											addPropertyListToClassDefinition(classDefinition, targetClassDefinition);

										}
										else if(i == GIA_ENTITY_VECTOR_CONNECTION_TYPE_CONDITION)
										{//declare conditions
											//conditionList
											if(!generateClassHeirarchyCondition(classDefinition, targetClassDefinition, targetEntity))
											{
												result = false;
											}

											#ifdef NLC_NORMALISE_TWOWAY_PREPOSITIONS_DUAL_CONDITION_LINKS_DISABLED
											if(targetEntity->conditionTwoWay)
											{
												if(!(targetEntity->relationshipObjectEntity->empty()))
												{
													string conditionObjectClassName = NLCitemClass.generateClassName((targetEntity->relationshipObjectEntity->back())->entity);
													bool foundClassDefinitionInverse = false;
													NLCclassDefinition* classDefinitionInverse = NLCclassDefinitionClass.findClassDefinition(classDefinitionList, conditionObjectClassName, &foundClassDefinitionInverse);	//see if class definition already exists
													if(!foundClassDefinitionInverse)
													{
														classDefinitionInverse = new NLCclassDefinition(conditionObjectClassName);
														classDefinitionList->push_back(classDefinitionInverse);
													}

													GIAentityNode* conditionRelationshipEntity = targetEntity;
													GIAentityNode* conditionEntityInverse = NULL;
													conditionEntityInverse = NLCcodeBlockClass.generateInverseConditionEntity(conditionRelationshipEntity);
													bool foundTargetClassDefinitionInverse = false;
													NLCclassDefinition* targetClassDefinitionInverse = NLCclassDefinitionClass.findClassDefinitionCondition(classDefinitionList, conditionEntityInverse, &foundTargetClassDefinition);	//see if class definition already exists
													if(!foundTargetClassDefinitionInverse)
													{
														targetClassDefinitionInverse = new NLCclassDefinition(NLCitemClass.generateClassName(conditionEntityInverse));
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
										else if(i == GIA_ENTITY_VECTOR_CONNECTION_TYPE_DEFINITION)
										{//declare inheritance
											#ifdef NLC_CLASS_DEFINITIONS_DO_NOT_DEFINE_INHERITANCE_FOR_REDEFINITIONS
											#ifndef NLC_REDEFINITIONS_FOR_IMMEDIATELY_DECLARED_INDEFINITE_ENTITIES
											//chickens are animals. an animal is a chicken. In practice this will not be implemented because GIA interprets indefinite-indefinite definitions as concepts. redefinitions are generally not implied for indefinite children (eg "an animal" in "an animal is a chicken") because they are ambiguous; this example either means a) animals are chickens (ie is a concept-concept definition; not a redefinition - and happens to be an incorrect statement based on aprior knowledge about the animal kingdom because we know chickens are animals not vice versa), or b) a newly declared animal is cast to a chicken (a specific version of animal, assuming "chickens are animals" has been declared)
											bool indefiniteChild = false;
											if(!NLCcodeBlockClass.isDefiniteEntity(entityNode))
											{
												bool parseConditionParents = NLC_PARSE_CONDITION_PARENTS_DEFAULT_VALUE;
												bool foundDefiniteParentEntity = false;
												bool checkIsDefinite = true;
												GIAentityNode* parentTemp = NLCtranslatorCodeBlocksOperations.getSameReferenceSetUniqueParent(entityNode, connection->sentenceIndexTemp, NULL, &foundDefiniteParentEntity, parseConditionParents, checkIsDefinite);
												if(!foundDefiniteParentEntity)
												{
													indefiniteChild = true;
												}
											}
											#endif
											bool substanceEntityDefinitionIsAChildOfTheSubstanceEntity = isSubstanceEntityDefinitionAChildOfTheSubstanceEntity(entityNode, targetEntity, connection);
											#ifdef NLC_REDEFINITIONS_FOR_IMMEDIATELY_DECLARED_INDEFINITE_ENTITIES
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
										else if(i == GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTION)
										{//declare functions
											//functionList
											bool foundLocalClassDefinition = false;
											NLCclassDefinition* localClassDefinition = NLCclassDefinitionClass.findClassDefinition(&(classDefinition->functionList), targetName, &foundLocalClassDefinition);	//see if class definition already exists	//note this check will not work for functions because they are added by instance
											if(!foundLocalClassDefinition)
											{
												bool hasActionObject = false;
												string actionObjectName = "";
												GIAentityNode* actionRelationshipObjectEntity = NULL;
												if(!(targetEntity->relationshipObjectEntity->empty()))
												{
													actionRelationshipObjectEntity = (targetEntity->relationshipObjectEntity->back())->entity;
													hasActionObject = true;
													actionObjectName = actionRelationshipObjectEntity->entityName;
												}

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
												//#ifdef NLC_INPUT_FUNCTION_LISTS	//shouldn't this preprocessor requirement be enforced?
												generateFunctionPropertyConditionArgumentsWithActionNetworkIndexInheritance(targetEntity, &(targetClassDefinition->parameters));
												//#endif
												#endif
											}
										}
										#endif
									}
								}
							#ifdef NLC_ADVANCED_REFERENCING_SUPPORT_ALIASES
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

		if(classDefinition->definitionList.empty() && (classDefinition->name != NLCitemClass.generateClassName(NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE)))
		{
			string targetName = NLCitemClass.generateClassName(NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE);
			bool foundTargetClassDefinition = false;
			NLCclassDefinition* targetClassDefinition = NLCclassDefinitionClass.findClassDefinition(classDefinitionList, targetName, &foundTargetClassDefinition);	//see if class definition already exists

			if(!foundTargetClassDefinition)
			{

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

bool NLCtranslatorClassDefinitionsClass::addClassDefinitionToList(vector<NLCclassDefinition*>* classDefinitionList, const string className, NLCclassDefinition** classDefinition)
{
	bool foundClassDefinition = false;
	*classDefinition = NLCclassDefinitionClass.findClassDefinition(classDefinitionList, className, &foundClassDefinition);	//see if class definition already exists
	if(!foundClassDefinition)
	{
		*classDefinition = new NLCclassDefinition(className);
		classDefinitionList->push_back(*classDefinition);
		foundClassDefinition = true;
	}
	return foundClassDefinition;
}

void NLCtranslatorClassDefinitionsClass::addDefinitionToClassDefinition(NLCclassDefinition* classDefinition, NLCclassDefinition* targetClassDefinition)
{
	//definitionList
	bool foundLocalClassDefinition = false;
	NLCclassDefinition* localClassDefinition = NLCclassDefinitionClass.findClassDefinition(&(classDefinition->definitionList), targetClassDefinition->name, &foundLocalClassDefinition);	//see if class definition already exists
	if(!foundLocalClassDefinition)
	{

		classDefinition->definitionList.push_back(targetClassDefinition);
	}
}

void NLCtranslatorClassDefinitionsClass::addPropertyListToClassDefinition(NLCclassDefinition* classDefinition, NLCclassDefinition* targetClassDefinition)
{
	//propertyList
	bool foundLocalClassDefinition = false;
	NLCclassDefinition* localClassDefinition = NLCclassDefinitionClass.findClassDefinition(&(classDefinition->propertyList), targetClassDefinition->name, &foundLocalClassDefinition);	//see if class definition already exists
	if(!foundLocalClassDefinition)
	{
		classDefinition->propertyList.push_back(targetClassDefinition);

		NLCitem* classDeclarationPropertiesListItem = new NLCitem(targetClassDefinition->name, NLC_ITEM_TYPE_CLASS_DECLARATION_PROPERTY_LIST);	//CHECKTHIS
		targetClassDefinition->parameters.push_back(classDeclarationPropertiesListItem);
	}
}



#ifdef NLC_CLASS_DEFINITIONS_DO_NOT_DEFINE_INHERITANCE_FOR_LOGICAL_CONDITION_CONCEPTS
bool NLCtranslatorClassDefinitionsClass::entityIsConceptAndInLogicalCondition(const GIAentityNode* entity, const NLCfunction* currentNLCfunctionInList)
{
	bool result = false;	
	NLCpreprocessorSentence* sentence = NULL;
	if(NLCpreprocessorSentenceClass.getSentenceInFunction(entity->sentenceIndexTemp, currentNLCfunctionInList, &sentence))
	{//note (with USE_NLC) separate concept entites are created for logical condition NLP parsable phrases (GIA advanced referencing is not applied), therefore a direct test of sentenceIndexTemp can be made
		if(NLCpreprocessorSentenceClass.sentencePertainsToLogicalCondition(sentence))
		{
			if(entity->entityType == GIA_ENTITY_TYPE_CONCEPT)
			{
				result = true;
			}
		}
	}
	return result;

}
#endif

#ifdef NLC_CLASS_DEFINITIONS_DO_NOT_DEFINE_INHERITANCE_FOR_REDEFINITIONS
bool NLCtranslatorClassDefinitionsClass::isSubstanceEntityDefinitionAChildOfTheSubstanceEntity(const GIAentityNode* substanceEntity, GIAentityNode* parentEntity, const GIAentityConnection* connection)
{
	bool parentClassIsChildOfChildClass = false;


	if(substanceEntity->entityType == GIA_ENTITY_TYPE_CONCEPT)	//added 1t2g
	{
		//ignore this case
	}
	#ifndef GIA_CREATE_NON_SPECIFIC_CONCEPTS_FOR_ALL_NETWORK_INDEXES
	else if(substanceEntity->entityType == GIA_ENTITY_TYPE_NETWORK_INDEX))	//added 1t2g (old implementation: 1r1a)
	{
		//ignore this case
	}
	#endif
	else if(parentEntity->entityType != GIA_ENTITY_TYPE_CONCEPT)
	{
		#ifdef NLC_ADVANCED_REFERENCING_SUPPORT_ALIASES
		if(!GIAtranslatorOperations.connectionIsAlias(connection))
		{
			cerr << "isSubstanceEntityDefinitionAChildOfTheSubstanceEntity{} error: a substance has a non-alias definition connection to a substance" << endl;
			exit(EXIT_ERROR);
		}
		#endif
	}
	else
	{
		GIAentityNode* parentNetworkIndexEntity = parentNetworkIndexEntity = GIAtranslatorOperations.getPrimaryNetworkIndexNodeDefiningInstance(parentEntity);
		for(vector<GIAentityConnection*>::iterator connectionIter = parentNetworkIndexEntity->instanceNodeList->begin(); connectionIter != parentNetworkIndexEntity->instanceNodeList->end(); connectionIter++)
		{
			GIAentityNode* parentConceptEntity = (*connectionIter)->entity;
			if(parentConceptEntity->entityType == GIA_ENTITY_TYPE_CONCEPT)
			{
				for(vector<GIAentityConnection*>::iterator connectionIter2 = parentConceptEntity->definitionNodeList->begin(); connectionIter2 != parentConceptEntity->definitionNodeList->end(); connectionIter2++)
				{
					GIAentityNode* parentConceptParentEntity = GIAtranslatorOperations.getDefinitionRelationshipObjectEntity(*connectionIter2);
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

bool NLCtranslatorClassDefinitionsClass::generateClassHeirarchyCondition(NLCclassDefinition* classDefinition, NLCclassDefinition* targetClassDefinition, GIAentityNode* targetEntity)
{
	bool result = true;

	//conditionList
	bool foundLocalClassDefinition = false;
	NLCclassDefinition* localClassDefinition = NLCclassDefinitionClass.findClassDefinitionCondition(&(classDefinition->conditionList), targetEntity, &foundLocalClassDefinition);	//see if class definition already exists
	if(!foundLocalClassDefinition)
	{

		classDefinition->conditionList.push_back(targetClassDefinition);

		NLCitem* classDeclarationConditionsListItem = new NLCitem(targetEntity, NLC_ITEM_TYPE_CLASS_DECLARATION_CONDITION_LIST);

		if(!(targetEntity->relationshipObjectEntity->empty()))
		{
			string conditionObjectClassName = NLCitemClass.generateClassName((targetEntity->relationshipObjectEntity->back())->entity);
			classDeclarationConditionsListItem->className2 = conditionObjectClassName;
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
bool NLCtranslatorClassDefinitionsClass::generateClassHeirarchyFunctions(vector<NLCclassDefinition*>* classDefinitionList, vector<GIAentityNode*>* entityNodesActiveListComplete, NLCclassDefinition* parentFunctionDependencyClassDefinition)
{

	bool result = true;

	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode* actionRelationshipEntity = *entityIter;

		//valid class checks added 1g12f 14-July-2014
		if(!(actionRelationshipEntity->disabled))
		{
			if(generateClassHeirarchyValidClassChecks(actionRelationshipEntity))
			{
				if(actionRelationshipEntity->entityType == GIA_ENTITY_TYPE_ACTION)
				{
					string actionOwnerClassDefinitionName = NLCitemClass.generateClassName(NLC_CLASS_DEFINITIONS_SUPPORT_FUNCTIONS_WITHOUT_SUBJECT_ARTIFICIAL_CLASS_NAME);

					bool passSubjectObjectValidClassChecks = true;

					bool hasActionSubject = false;
					string actionSubjectName = "";
					GIAentityNode* actionRelationshipSubjectEntity = NULL;
					if(!(actionRelationshipEntity->relationshipSubjectEntity->empty()))
					{
						actionRelationshipSubjectEntity = (actionRelationshipEntity->relationshipSubjectEntity->back())->entity;
						hasActionSubject = true;
						actionSubjectName = actionRelationshipSubjectEntity->entityName;

						passSubjectObjectValidClassChecks = false;
						//valid class contents checks added 1g12f 14-July-2014
						if(generateClassHeirarchyTargetValidClassChecks(actionRelationshipSubjectEntity))
						{
							if(!(actionRelationshipSubjectEntity->disabled))
							{
								passSubjectObjectValidClassChecks = true;
							}
						}
					}

					bool hasActionObject = false;
					string actionObjectName = "";
					GIAentityNode* actionRelationshipObjectEntity = NULL;
					if(!(actionRelationshipEntity->relationshipObjectEntity->empty()))
					{
						actionRelationshipObjectEntity = (actionRelationshipEntity->relationshipObjectEntity->back())->entity;
						hasActionObject = true;
						actionObjectName = actionRelationshipObjectEntity->entityName;
					}

					//valid class contents checks added 1g12f 14-July-2014
					if(passSubjectObjectValidClassChecks)
					{

						string functionName = actionRelationshipEntity->entityName;
						string functionOwnerName = actionSubjectName;
						string functionObjectName = actionObjectName;
						bool hasFunctionOwnerClass = hasActionSubject;
						bool hasFunctionObjectClass = hasActionObject;
						bool foundFunctionOwnerExactMatch = false;
						bool foundFunctionObjectExactMatch = false;
						bool rearrangeClassList = false;
						NLCclassDefinition* functionDefinitionClassDefinition = NULL;
						//look for both exact and non-exact matches here as functionDependencies have already been created for all functions explicitly declared+defined by the user (don't yet reconcile arguments however)
						if(NLCclassDefinitionClass.findFunctionDefinitionClassDefinitionExactOrNonExactMatch(classDefinitionList, functionName, functionOwnerName, functionObjectName, hasFunctionOwnerClass, hasFunctionObjectClass, &functionDefinitionClassDefinition, rearrangeClassList, &foundFunctionOwnerExactMatch, &foundFunctionObjectExactMatch))
						{
							NLCclassDefinitionFunctionDependency* functionDependenciesInParentTemp = NULL;
							bool foundFunctionDependencyInParent = NLCclassDefinitionClass.findFunctionDependencyInParent(parentFunctionDependencyClassDefinition, functionName, functionOwnerName, functionObjectName, hasFunctionOwnerClass, hasFunctionObjectClass, &functionDependenciesInParentTemp);
							if(!foundFunctionDependencyInParent)
							{
								parentFunctionDependencyClassDefinition->functionDependencyList.push_back(functionDefinitionClassDefinition);
							}

							#ifdef NLC_RECORD_ACTION_HISTORY
							fillActionLists(classDefinitionList, hasActionSubject, hasActionObject, actionRelationshipEntity->entityName, actionObjectName, actionSubjectName);
							#endif
						}
						else
						{
							//function execution reference does not correspond to a new function definition, so create a function declaration for it

							NLCclassDefinition* functionReferenceClassDefinition = NULL;
							bool foundFunctionDependencyInList = NLCclassDefinitionClass.findFunctionDependencyClassDefinitionInList(classDefinitionList, functionName, functionOwnerName, functionObjectName, true, hasFunctionObjectClass, &functionReferenceClassDefinition);
							bool duplicateFunctionDeclarationDetected = false;
							if(foundFunctionDependencyInList)
							{
								//this will be true if an action (function reference) has been declared twice, but the action (function) has not been defined, eg "A chicken ate a pie. The chicken that ate a pie rowed the boat."
								#ifndef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE_DO_NOT_ADD_FUNCTION_DEPENDENCY_FOR_FUNCTION_REFERENCES
								NLCclassDefinitionFunctionDependency* functionDependenciesInParentTemp = NULL;
								bool foundFunctionDependencyInParent = NLCclassDefinitionClass.findFunctionDependencyInParent(parentFunctionDependencyClassDefinition, functionName, functionOwnerName, functionObjectName, true, hasFunctionObjectClass, &functionDependenciesInParentTemp);
								if(!foundFunctionDependencyInParent)
								{
									parentFunctionDependencyClassDefinition->functionDependencyList.push_back(functionReferenceClassDefinition);
								}
								else
								{
									duplicateFunctionDeclarationDetected = true;
									//duplicate function declarations will be ignored
								}
								#else
								cerr << "generateClassHeirarchyFunctions{} error: !findFunctionDefinitionClassDefinitionExactOrNonExactMatch && findFunctionDependencyClassDefinitionInList" << endl;
								cerr << "functionName: " << functionName << endl;
								cerr << "functionOwnerName: " << functionOwnerName << endl;
								cerr << "functionObjectName: " << functionObjectName << endl;
								exit(EXIT_ERROR);
								#endif

							}
							else
							{

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
									classDefinitionFunctionOwnerName = NLCitemClass.generateClassName(actionRelationshipSubjectEntity);
									#ifdef NLC_CREATE_A_SEPARATE_CLASS_FOR_CONCEPT_DEFINITIONS
									if(actionRelationshipEntity->entityType == GIA_ENTITY_TYPE_CONCEPT)
									{
										classDefinitionFunctionOwnerName = generateConceptClassName(actionRelationshipSubjectEntity);	//is this still required?
									}
									#endif
								}
								else
								{
									classDefinitionFunctionOwnerName = NLCitemClass.generateClassName(NLC_CLASS_DEFINITIONS_SUPPORT_FUNCTIONS_WITHOUT_SUBJECT_ARTIFICIAL_CLASS_NAME);
								}
								bool foundClassDefinitionFunctionOwner = false;
								NLCclassDefinition* classDefinitionFunctionOwner = NLCclassDefinitionClass.findClassDefinition(classDefinitionList, classDefinitionFunctionOwnerName, &foundClassDefinitionFunctionOwner);	//see if class definition already exists
								if(!foundClassDefinitionFunctionOwner)
								{
									classDefinitionFunctionOwner = new NLCclassDefinition(classDefinitionFunctionOwnerName);
									classDefinitionList->push_back(classDefinitionFunctionOwner);
								}

								string classDefinitionFunctionName = NLCitemClass.generateInstanceName(actionRelationshipEntity);
								bool foundClassDefinitionFunction = false;
								NLCclassDefinition* classDefinitionFunction = NLCclassDefinitionClass.findClassDefinition(classDefinitionList, classDefinitionFunctionName, &foundClassDefinitionFunction);	//see if class definition already exists
								if(!foundClassDefinitionFunction)
								{
									classDefinitionFunction = new NLCclassDefinition(classDefinitionFunctionName);
									classDefinitionList->push_back(classDefinitionFunction);
								}

								#ifndef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE_DO_NOT_ADD_FUNCTION_DEPENDENCY_FOR_FUNCTION_REFERENCES
								classDefinitionFunction->functionDependency = functionDependency;	//new for 1p4a - functionDependencies are now currently assigned to functionReference classDefinitions (not just functionDefinition classDefinitions)
								parentFunctionDependencyClassDefinition->functionDependencyList.push_back(classDefinitionFunction);
								#endif

								classDefinitionFunction->functionNameSpecial = NLCitemClass.generateFunctionName(actionRelationshipEntity);
								#ifdef NLC_INPUT_FUNCTION_LISTS_CHECK_ACTION_SUBJECT_CONTENTS_FOR_IMPLICITLY_DECLARED_PARAMETERS
								classDefinitionFunction->actionOrConditionInstance = actionRelationshipEntity;
								#endif
								classDefinitionFunction->isActionOrConditionInstanceNotClass = true;

								bool foundLocalClassDefinitionFunction = false;
								/*
								cout << "functionName = " << functionName << endl;
								cout << "functionOwnerName = " << functionOwnerName << endl;
								cout << "functionObjectName = " << functionObjectName << endl;
								*/
								#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE_DO_NOT_ADD_FUNCTION_DEPENDENCY_FOR_FUNCTION_REFERENCES
								NLCclassDefinition* localClassDefinitionFunction = NLCclassDefinitionClass.findClassDefinitionFunction(&(classDefinitionFunctionOwner->functionList), functionName, functionOwnerName, functionObjectName, hasFunctionOwnerClass, hasFunctionObjectClass, &foundLocalClassDefinitionFunction);	//see if class definition already exists
								#else
								NLCclassDefinition* localClassDefinitionFunction = NLCclassDefinitionClass.findClassDefinition(&(classDefinitionFunctionOwner->functionList), classDefinitionFunctionName, &foundLocalClassDefinitionFunction);	//see if class definition already exists	//note this check will not work for functions because they are added by instance (but unique functionDependency check has already been performed above so this unique functionReference in functionList check is not required and will always give !foundLocalClassDefinitionFunction)
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
										NLCitem* classDeclarationFunctionOwnerItem = new NLCitem(actionRelationshipSubjectEntity, NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION_OWNER);	//corrected 1p5a
										classDefinitionFunction->parameters.push_back(classDeclarationFunctionOwnerItem);
									}
									#endif

									NLCitem* classDeclarationFunctionItem = new NLCitem(actionRelationshipEntity, NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION);	//added 1e1c
									classDefinitionFunction->parameters.push_back(classDeclarationFunctionItem);

									if(hasFunctionObjectClass)
									{
										NLCitem* classDeclarationFunctionObjectItem = new NLCitem(actionObjectName, NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION_OBJECT);	//for special case (as actions are referenced by instance)	//why use actionRelationshipObjectEntity instead of actionObjectName?
										classDefinitionFunction->parameters.push_back(classDeclarationFunctionObjectItem);
									}

									#ifdef NLC_RECORD_ACTION_HISTORY
									fillActionLists(classDefinitionList, hasActionSubject, hasActionObject, actionRelationshipEntity->entityName, actionObjectName, actionSubjectName);	//fillActionLists will find classDefinitionFunctionOwner
									#endif

									#ifdef NLC_INTERPRET_ACTION_PROPERTIES_AND_CONDITIONS_AS_FUNCTION_ARGUMENTS
									//#ifdef NLC_INPUT_FUNCTION_LISTS	//shouldn't this preprocessor requirement be enforced?
									generateFunctionPropertyConditionArgumentsWithActionNetworkIndexInheritance(actionRelationshipEntity, &(classDefinitionFunction->parameters));
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
void NLCtranslatorClassDefinitionsClass::fillActionLists(vector<NLCclassDefinition*>* classDefinitionList, const bool hasActionSubject, const bool hasActionObject, const string actionName, const string actionObjectName, const string actionSubjectName)
{
	bool foundClassDefinitionAction = false;
	string actionClassName =  NLCitemClass.generateClassName(actionName);
	NLCclassDefinition* classDefinitionAction = NLCclassDefinitionClass.findClassDefinition(classDefinitionList, actionClassName, &foundClassDefinitionAction);	//see if class definition already exists
	if(!foundClassDefinitionAction)
	{
		classDefinitionAction = new NLCclassDefinition(actionClassName);
		classDefinitionList->push_back(classDefinitionAction);
	}

	if(hasActionSubject)
	{
		string classDefinitionFunctionOwnerName = NLCitemClass.generateClassName(actionSubjectName);
		bool foundClassDefinitionFunctionOwner = false;
		NLCclassDefinition* classDefinitionFunctionOwner = NLCclassDefinitionClass.findClassDefinition(classDefinitionList, classDefinitionFunctionOwnerName, &foundClassDefinitionFunctionOwner);	//see if class definition already exists
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
			NLCclassDefinition* localClassDefinitionAction = NLCclassDefinitionClass.findClassDefinition(&(classDefinitionFunctionOwner->actionList), actionClassName, &foundLocalClassDefinitionAction);	//see if class definition already exists
			if(!foundLocalClassDefinitionAction)
			{
				classDefinitionFunctionOwner->actionList.push_back(classDefinitionAction);

			}
			bool foundLocalClassDefinitionActionOwner = false;
			string actionOwnerClassName = classDefinitionFunctionOwner->name;
			NLCclassDefinition* localClassDefinitionActionOwner = NLCclassDefinitionClass.findClassDefinition(&(classDefinitionAction->actionSubjectList), actionOwnerClassName, &foundLocalClassDefinitionActionOwner);	//see if class definition already exists
			if(!foundLocalClassDefinitionActionOwner)
			{
				classDefinitionAction->actionSubjectList.push_back(classDefinitionFunctionOwner);
			}
		}
	}

	if(hasActionObject)
	{
		bool foundClassDefinitionActionObject = false;
		string actionObjectClassName = NLCitemClass.generateClassName(actionObjectName);
		NLCclassDefinition* classDefinitionActionObject = NLCclassDefinitionClass.findClassDefinition(classDefinitionList, actionObjectClassName, &foundClassDefinitionActionObject);	//see if class definition already exists
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
			string actionObjectClassName = NLCitemClass.generateClassName(actionObjectName);
			NLCclassDefinition* localClassDefinitionActionObject = NLCclassDefinitionClass.findClassDefinition(&(classDefinitionAction->actionObjectList), actionObjectClassName, &foundLocalClassDefinitionActionObject);	//see if class definition already exists
			if(!foundLocalClassDefinitionActionObject)
			{
				classDefinitionAction->actionObjectList.push_back(classDefinitionActionObject);
			}
			bool foundLocalClassDefinitionActionIncoming = false;
			NLCclassDefinition* localClassDefinitionActionIncoming = NLCclassDefinitionClass.findClassDefinition(&(classDefinitionActionObject->actionIncomingList), actionClassName, &foundLocalClassDefinitionActionIncoming);	//see if class definition already exists
			if(!foundLocalClassDefinitionActionIncoming)
			{
				classDefinitionActionObject->actionIncomingList.push_back(classDefinitionAction);
			}
		}
	}
}
#endif

bool NLCtranslatorClassDefinitionsClass::generateClassHeirarchyValidClassChecks(GIAentityNode* entityNode)
{
	bool validClass = true;

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
	if(entityNode->entityType == GIA_ENTITY_TYPE_NETWORK_INDEX)	//added 1n2f
	{
		validClass = false;
	}
	#endif
	#ifdef NLC_ADVANCED_REFERENCING_SUPPORT_ALIASES
	if(entityNode->NLCisAlias)
	{
		validClass = false;
	}
	#endif

	if(NLCpreprocessorSentenceClass.isStringNumberOrFractional(entityNode->entityName))
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
	#ifdef NLC_ADVANCED_REFERENCING_SUPPORT_ALIASES
	string aliasClassName = "";
	if(findEntityNameInFunctionAliasList(entityNode->entityName, &aliasClassName))
	{
		entityNode->entityName = aliasClassName;	//entity name can be overwritten as generateCodeBlocks has already been executed
	}
	#endif
	*/

	//added 1q14f
	if(NLCpreprocessorSentenceClass.isStringAliasFileName(entityNode->entityName))
	{
		validClass = false;
	}

	#ifdef NLC_VERIFY_LEGAL_TARGET_SOURCE_CHARACTERS
	//added 1q14f - CHECKTHIS: is this required?
	if(NLCpreprocessorSentenceClass.isStringIllegalTargetSourceCharacter(entityNode->entityName))
	{
		if(validClass)
		{
			cout << "printClassHeirarchyValidDefinitionClassChecks{} error: isStringIllegalTargetSourceCharacter; entityNode->entityName = " << entityNode->entityName << endl;
		}
		validClass = false;
	}
	#endif

	#ifdef GIA_ADD_ARTIFICIAL_AUXILIARY_FOR_ALL_PROPERTIES_AND_DEFINITIONS
	if((entityNode->entityType == GIA_ENTITY_TYPE_PROPERTY) || (entityNode->entityType == GIA_ENTITY_TYPE_DEFINITION))
	{
		validClass = false;
	}
	#endif
	
	return validClass;
}

bool NLCtranslatorClassDefinitionsClass::generateClassHeirarchyTargetValidClassChecks(GIAentityNode* targetEntity)
{
	bool validClass = generateClassHeirarchyValidClassChecks(targetEntity);

	return validClass;
}




#ifdef NLC_CREATE_A_SEPARATE_CLASS_FOR_CONCEPT_DEFINITIONS
string NLCtranslatorClassDefinitionsClass::generateConceptClassName(GIAentityNode* conceptEntity)
{
	string conceptClassName = conceptEntity->entityName;
	generateConceptClassNameRecurse(conceptEntity, &conceptClassName);
	conceptClassName = conceptClassName + NLC_CLASS_NAME_APPEND;
	return conceptClassName;
}

void NLCtranslatorClassDefinitionsClass::generateConceptClassNameRecurse(GIAentityNode* conceptEntity, string* conceptClassName)
{
	for(vector<GIAentityConnection*>::iterator entityIter = conceptEntity->conditionNodeList->begin(); entityIter != conceptEntity->conditionNodeList->end(); entityIter++)
	{
		GIAentityNode* conceptConditionRelationshipEntity = (*entityIter)->entity;
		#ifdef NLC_NORMALISE_TWOWAY_PREPOSITIONS_DUAL_CONDITION_LINKS_ENABLED
		if(!(conceptConditionRelationshipEntity->inverseConditionTwoWay) || (*entityIter)->isReferenceElseFunctionDefinition)		//prevent infinite loop for 2 way conditions
		{
		#endif
			if(!(conceptConditionRelationshipEntity->relationshipObjectEntity->empty()))
			{
				GIAentityNode* conceptConditionRelationshipObjectEntity = (conceptCondition->relationshipObjectEntity->back())->entity;
				*conceptClassName = *conceptClassName + NLC_CONCEPT_CLASS_PREPEND + conceptConditionRelationshipEntity->entityName + conceptConditionRelationshipObjectEntity->entityName + NLC_CONCEPT_CLASS_CONDITION;
				*conceptClassName = *conceptClassName + generateConceptClassNameRecurse(conceptConditionRelationshipObjectEntity, conceptClassName);	//recurse in case of very detailed concept eg "red dogs next to blue cows"
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
		GIAentityNode* conceptPropertyRelationshipObjectEntity = getPropertyRelationshipObjectEntity(*entityIter);
		*conceptClassName = *conceptClassName + NLC_CONCEPT_CLASS_PREPEND + conceptPropertyRelationshipObjectEntity->entityName + NLC_CONCEPT_CLASS_PROPERTY;
		*conceptClassName = *conceptClassName + generateConceptClassNameRecurse(conceptPropertyRelationshipObjectEntity, conceptClassName);	//recurse in case of very detailed concept eg "red dogs next to blue cows"
	}
}

#endif

#ifdef NLC_PREVENT_INHERITANCE_DOUBLE_DECLARATIONS_OF_CLASS_LIST_VARIABLES

void NLCtranslatorClassDefinitionsClass::preventDoubleDeclarationsOfClassDefinitionVariablesInHeirachy(vector<NLCclassDefinition*>* classDefinitionList)
{
	//disable all double declarations
	for(vector<NLCclassDefinition*>::iterator classDefinitionIter = classDefinitionList->begin(); classDefinitionIter != classDefinitionList->end(); classDefinitionIter++)
	{
		NLCclassDefinition* classDefinition = *classDefinitionIter;
		eraseDuplicateClassDefinitionSublistItemIfFoundInParentClassDefinitionSublist(classDefinition, &(classDefinition->propertyList), GIA_ENTITY_VECTOR_CONNECTION_TYPE_PROPERTY);	//changed from GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTION, 1k8b
		eraseDuplicateClassDefinitionSublistItemIfFoundInParentClassDefinitionSublist(classDefinition, &(classDefinition->conditionList), GIA_ENTITY_VECTOR_CONNECTION_TYPE_CONDITION);
		eraseDuplicateClassDefinitionSublistItemIfFoundInParentClassDefinitionSublist(classDefinition, &(classDefinition->functionList), NLC_ENTITY_VECTOR_CONNECTION_TYPE_FUNCTIONS);
		#ifdef NLC_RECORD_ACTION_HISTORY
		eraseDuplicateClassDefinitionSublistItemIfFoundInParentClassDefinitionSublist(classDefinition, &(classDefinition->actionList), GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTION);
		eraseDuplicateClassDefinitionSublistItemIfFoundInParentClassDefinitionSublist(classDefinition, &(classDefinition->actionIncomingList), GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTION);
		eraseDuplicateClassDefinitionSublistItemIfFoundInParentClassDefinitionSublist(classDefinition, &(classDefinition->actionSubjectList), GIA_ENTITY_VECTOR_CONNECTION_TYPE_RELATIONSHIP_SUBJECT);	//?not currently required as actionRelationshipSubjectEntity/actionRelationshipObjectEntity lists are defined after function (arguments) have been reconciled
		eraseDuplicateClassDefinitionSublistItemIfFoundInParentClassDefinitionSublist(classDefinition, &(classDefinition->actionObjectList), GIA_ENTITY_VECTOR_CONNECTION_TYPE_RELATIONSHIP_OBJECT);		//?not currently required as actionRelationshipSubjectEntity/actionRelationshipObjectEntity lists are defined after function (arguments) have been reconciled
		#endif
	}
}

void NLCtranslatorClassDefinitionsClass::eraseDuplicateClassDefinitionSublistItemIfFoundInParentClassDefinitionSublist(NLCclassDefinition* classDefinition, vector<NLCclassDefinition*>* classDefinitionSublist, const int variableType)
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
				}
			}
		}
		if(!localListIterErased)
		{
			localListIter++;
		}
	}
}

bool NLCtranslatorClassDefinitionsClass::findVariableInParentClass(NLCclassDefinition* classDefinition, const string variableName, const int variableType)
{
	bool foundVariable = false;
	if(variableType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_PROPERTY)
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
	else if(variableType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_CONDITION)
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
	else if(variableType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTION)
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
	else if(variableType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTION_REVERSE)
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
	else if(variableType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_RELATIONSHIP_SUBJECT)
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
	else if(variableType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_RELATIONSHIP_OBJECT)
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
void NLCtranslatorClassDefinitionsClass::generateFunctionPropertyConditionArgumentsWithActionNetworkIndexInheritance(GIAentityNode* actionRelationshipEntity, vector<NLCitem*>* parameters)
{
	generateFunctionPropertyConditionArguments(actionRelationshipEntity, parameters, false);

	#ifdef GIA_TRANSLATOR_DREAM_MODE_LINK_SPECIFIC_CONCEPTS_AND_ACTIONS
	//Part b: generate object initialisations based on action networkIndexes (class inheritance)
	for(vector<GIAentityConnection*>::iterator entityNodeDefinitionListIterator = actionRelationshipEntity->definitionNodeList->begin(); entityNodeDefinitionListIterator < actionRelationshipEntity->definitionNodeList->end(); entityNodeDefinitionListIterator++)
	{
		GIAentityConnection* definitionConnection = (*entityNodeDefinitionListIterator);
		definitionConnection->NLCparsedForCodeBlocks = true;
		GIAentityNode* definitionRelationshipObjectEntity = getDefinitionRelationshipObjectEntity(definitionConnection);
		if(definitionRelationshipObjectEntity->isActionConcept)
		{
			generateFunctionPropertyConditionArguments(definitionRelationshipObjectEntity, parameters, true);
		}
	}
	#endif
}

void NLCtranslatorClassDefinitionsClass::generateFunctionPropertyConditionArguments(GIAentityNode* actionRelationshipEntity, vector<NLCitem*>* parameters, const bool performChildActionDuplicateCheck)
{
	for(vector<GIAentityConnection*>::iterator entityIter = actionRelationshipEntity->conditionNodeList->begin(); entityIter != actionRelationshipEntity->conditionNodeList->end(); entityIter++)
	{
		GIAentityNode* actionCondition = (*entityIter)->entity;
		bool alreadyAdded = false;
		if(performChildActionDuplicateCheck)
		{
			alreadyAdded = NLCcodeBlockClass.checkDuplicateCondition(actionCondition, parameters);
		}
		if(!alreadyAdded)
		{
			GIAentityNode* conditionRelationshipObjectEntity = NULL;
			if(!(actionCondition->relationshipObjectEntity->empty()))
			{
				conditionRelationshipObjectEntity = (actionCondition->relationshipObjectEntity->back())->entity;
			}
			NLCitem* argumentConditionItem = new NLCitem(actionCondition, NLC_ITEM_TYPE_FUNCTION_DECLARATION_ARGUMENT_CONDITION);
			argumentConditionItem->className2 = NLCitemClass.generateClassName(conditionRelationshipObjectEntity);
			argumentConditionItem->instanceName2 = NLCitemClass.generateInstanceName(conditionRelationshipObjectEntity);
			parameters->push_back(argumentConditionItem);
		}
	}
	for(vector<GIAentityConnection*>::iterator entityIter = actionRelationshipEntity->propertyNodeList->begin(); entityIter != actionRelationshipEntity->propertyNodeList->end(); entityIter++)
	{
		GIAentityNode* actionProperty = getPropertyRelationshipObjectEntity(*entityIter);
		bool alreadyAdded = false;
		if(performChildActionDuplicateCheck)
		{
			alreadyAdded = NLCcodeBlockClass.checkDuplicateProperty(actionProperty, parameters);
		}
		if(!alreadyAdded)
		{
			NLCitem* argumentPropertyItem = new NLCitem(actionProperty, NLC_ITEM_TYPE_FUNCTION_DECLARATION_ARGUMENT_PROPERTY);
			parameters->push_back(argumentPropertyItem);
		}
	}
}

bool NLCtranslatorClassDefinitionsClass::checkDuplicateProperty(const GIAentityNode* propertyRelationshipObjectEntity, vector<NLCitem*>* parameters)
{
	bool alreadyAdded = false;
	for(vector<NLCitem*>::iterator parametersIterator = parameters->begin(); parametersIterator < parameters->end(); parametersIterator++)
	{
		NLCitem* currentItem = *parametersIterator;
		if(currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_DECLARATION_ARGUMENT_PROPERTY)
		{
			if(NLCitemClass.generateClassName(propertyRelationshipObjectEntity) == currentItem->className)
			{
				alreadyAdded = true;
			}
		}

	}
	return alreadyAdded;
}

bool NLCtranslatorClassDefinitionsClass::checkDuplicateCondition(GIAentityNode* conditionRelationshipEntity, vector<NLCitem*>* parameters)
{
	bool alreadyAdded = false;
	for(vector<NLCitem*>::iterator parametersIterator = parameters->begin(); parametersIterator < parameters->end(); parametersIterator++)
	{
		NLCitem* currentItem = *parametersIterator;
		if(currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_DECLARATION_ARGUMENT_CONDITION)
		{
			GIAentityNode* relationshipObjectEntity = NULL;
			if(!(conditionRelationshipEntity->relationshipObjectEntity->empty()))
			{
				relationshipObjectEntity = (conditionRelationshipEntity->relationshipObjectEntity->back())->entity;
			}

			if((NLCitemClass.generateClassName(conditionRelationshipEntity) == currentItem->className) && (NLCitemClass.generateClassName(relationshipObjectEntity) == currentItem->className2))
			{
				alreadyAdded = true;
			}
		}
	}
	return alreadyAdded;
}

#endif





