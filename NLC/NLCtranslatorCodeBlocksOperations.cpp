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
 * File Name: NLCtranslatorCodeBlocksOperations.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2014 Baxter AI (baxterai.com)
 * Project: Natural Language Programming Interface (compiler)
 * Project Version: 1g14b 15-July-2014
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/



#include <ctime>
#include <cstdlib>	//for random number generation
#include <cmath>

#include "NLCtranslatorCodeBlocksOperations.h"
//#include "GIAquery.h"		//what is this required for?
//#include "GIAtranslatorOperations.h"	//required for textInTextArray()




bool getParentAndGenerateContextBlocksAndInitialiseParentIfNecessary(NLCcodeblock ** currentCodeBlockInTree, GIAentityNode * currentEntity, int sentenceIndex, NLClogicalConditionConjunctionVariables * logicalConditionConjunctionVariables, bool parseConditionParents, bool parseLogicalConditions)
{
	GIAentityNode * parentEntity = getParent(currentEntity, sentenceIndex, parseConditionParents);

	bool performedAtLeastParentObjectInitialisation = false;
	if(checkSentenceIndexParsingCodeBlocks(currentEntity, sentenceIndex, false))
	{//is this required?
		performedAtLeastParentObjectInitialisation = generateContextBlocksAndInitialiseParentIfNecessary(currentCodeBlockInTree, parentEntity, sentenceIndex, logicalConditionConjunctionVariables, parseConditionParents, parseLogicalConditions);
	}
	
	return performedAtLeastParentObjectInitialisation;

}
//added 1e6a
bool generateContextBlocksAndInitialiseParentIfNecessary(NLCcodeblock ** currentCodeBlockInTree, GIAentityNode * parentEntity, int sentenceIndex, NLClogicalConditionConjunctionVariables * logicalConditionConjunctionVariables, bool parseConditionParents, bool parseLogicalConditions)
{
	bool performedAtLeastParentObjectInitialisation = false;
	
	#ifdef NLC_DEBUG
	cout << "\tgenerateContextBlocksAndInitialiseParentIfNecessary parent: " << parentEntity->entityName << endl;
	#endif

	if(generateParentInitialisationCodeBlock(currentCodeBlockInTree, parentEntity, sentenceIndex, parseLogicalConditions))
	{
		performedAtLeastParentObjectInitialisation = true;
	}
	else
	{//added 1g14b 15-July-2014 (do not perform if parent and its children are already initialised)
		NLCcodeblock * originalCodeBlockInTree = *currentCodeBlockInTree;

		NLCitem * propertyItem = new NLCitem(parentEntity, NLC_ITEM_TYPE_CLASS);
		//context property item:
		if(assumedToAlreadyHaveBeenDeclared(parentEntity))
		{
			*currentCodeBlockInTree = createCodeBlockForPropertyListLocal(*currentCodeBlockInTree, propertyItem);
		}
		else
		{
			*currentCodeBlockInTree = createCodeBlockForPropertyList(*currentCodeBlockInTree, propertyItem);
		}

		#ifdef NLC_DEBUG
		cout << "\tgenerateContextBlocks: " << currentEntity->entityName << endl;
		#endif
		//parse the children (properties and conditions) of an undeclared definite parent 
		if(!generateContextBlocks(currentCodeBlockInTree, parentEntity, sentenceIndex, logicalConditionConjunctionVariables))
		{
			#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
			//if(!performedAtLeastParentObjectInitialisation)
			//{//removed 1g14b 15-July-2014: redundant 
				if(logicalConditionConjunctionVariables->onlyGenerateContextBlocksIfConnectionsParsedForNLC)
				{
					*currentCodeBlockInTree = originalCodeBlockInTree;
				}
			//}
			#endif
		}
		else
		{
			#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
			parentEntity->NLCcontextGenerated = true;	//added 1g14b 15-July-2014
			#endif		
		}
	}
	
	return performedAtLeastParentObjectInitialisation;
}

bool generateContextBlocks(NLCcodeblock ** currentCodeBlockInTree, GIAentityNode * entity, int sentenceIndex, NLClogicalConditionConjunctionVariables * logicalConditionConjunctionVariables)
{
	bool contextFound = false;
	
	contextFound = createCodeBlockForStatements(currentCodeBlockInTree, generateInstanceName(entity), entity, sentenceIndex, logicalConditionConjunctionVariables);

	return contextFound;
}








//static int haltForDebug = false;

bool generateCodeBlocksObjectInitialisationsForEntity(NLCcodeblock ** currentCodeBlockInTree, GIAentityNode * entity, int sentenceIndex)
{
	#ifdef NLC_PARSE_CONTEXT_DEBUG
	cout << "\ngenerateCodeBlocksPart4objectInitialisations(): sentenceIndex = " << sentenceIndex << endl;
	cout << "\tentity->entityName = " << entity->entityName << endl;
	#endif
	
	NLCcodeblock * originalCodeBlockInLevel = *currentCodeBlockInTree;
	NLClogicalConditionConjunctionVariables logicalConditionConjunctionVariables;
	logicalConditionConjunctionVariables.onlyGenerateContextBlocksIfConnectionsParsedForNLC = true;

	#ifdef NLC_PARSE_CONTEXT_DEBUG
	cout << "generateCodeBlocksObjectInitialisationsForEntity: getParent()" << endl;
	#endif
	GIAentityNode * parentEntity = getParent(entity, sentenceIndex, true);
	#ifdef NLC_PARSE_CONTEXT_DEBUG
	cout << "\tparentEntity = " << parentEntity->entityName << endl;
	cout << "generateCodeBlocksObjectInitialisationsForEntity: generateContextBlocksAndInitialiseParentIfNecessary()" << endl;
	#endif
	if(!generateContextBlocksAndInitialiseParentIfNecessary(currentCodeBlockInTree, parentEntity, sentenceIndex, &logicalConditionConjunctionVariables, true, false))	//parse condition parents in accordance with original generateCodeBlocksPart4objectInitialisations implementation
	{
		#ifdef NLC_PARSE_CONTEXT_DEBUG
		cout << "\tfail generateContextBlocksAndInitialiseParentIfNecessary" << endl;
		cout << "generateCodeBlocksObjectInitialisationsForEntity: generateObjectInitialisationsBasedOnPropertiesAndConditions()" << endl;
		#endif
		//if(!getParentAndGenerateParentInitialisationCodeBlock(currentCodeBlockInTree, entity , sentenceIndex, true, false, false))
		if(!generateObjectInitialisationsBasedOnPropertiesAndConditions(parentEntity, currentCodeBlockInTree , sentenceIndex, "", "", true))
		{
			*currentCodeBlockInTree = originalCodeBlockInLevel;
			originalCodeBlockInLevel->codeBlockType = NLC_CODEBLOCK_TYPE_UNDEFINED;
			originalCodeBlockInLevel->next = NULL;
			originalCodeBlockInLevel->lowerLevel = NULL;
			originalCodeBlockInLevel->parameters.clear();

			#ifdef NLC_PARSE_CONTEXT_DEBUG
			cout << "\tfail generateObjectInitialisationsBasedOnPropertiesAndConditions" << endl;
			#endif
		}
		else
		{
			#ifdef NLC_PARSE_CONTEXT_DEBUG
			cout << "\tpass generateObjectInitialisationsBasedOnPropertiesAndConditions" << endl;
			#endif
		}
	}
	else
	{
		#ifdef NLC_PARSE_CONTEXT_DEBUG
		cout << "\tpass generateContextBlocksAndInitialiseParentIfNecessary" << endl;
		#endif
	}
}

bool getParentAndGenerateParentInitialisationCodeBlock(NLCcodeblock ** currentCodeBlockInTree, GIAentityNode * entity, int sentenceIndex, bool parseConditionParents, bool parseLogicalConditions)
{	
	GIAentityNode * parentEntity = getParent(entity, sentenceIndex, parseConditionParents);
	//cout << "parentEntity = " << parentEntity->entityName << endl;

	bool performedAtLeastParentObjectInitialisation = false;

	performedAtLeastParentObjectInitialisation = generateParentInitialisationCodeBlock(currentCodeBlockInTree, parentEntity, sentenceIndex, parseLogicalConditions);
}
		
bool generateParentInitialisationCodeBlock(NLCcodeblock ** currentCodeBlockInTree, GIAentityNode * parentEntity, int sentenceIndex, bool parseLogicalConditions)
{
	bool performedAtLeastParentObjectInitialisation = false;
	
	//cout << "getParentAndGenerateParentInitialisationCodeBlock: entity->NLCparsedForlogicalConditionOperations = " << entity->NLCparsedForlogicalConditionOperations << endl;
	#ifdef NLC_SUPPORT_CONDITION_LOGICAL_OPERATIONS
	if(!(parentEntity->NLCparsedForlogicalConditionOperations) || parseLogicalConditions)	//CHECKTHIS; change from !(entity->NLCparsedForlogicalConditionOperations) to !(parentEntity->NLCparsedForlogicalConditionOperations) 1g14a 15-July-2014
	{
	#endif
		#ifdef NLC_CREATE_IMPLICITLY_DECLARED_ACTION_OBJECT_AND_SUBJECT_VARIABLES
		//moved here 1e8a (out of generateObjectInitialisationsBasedOnPropertiesAndConditions)
		//added 1e6c: eg A chicken's hat has a bike. / A blue dog has a bike.
		if(!(parentEntity->isConcept))
		{
			if(!(parentEntity->NLCparsedForCodeBlocks))	// && !(entity->parsedForNLCcodeBlocksActionRound)
			{
				if(!assumedToAlreadyHaveBeenDeclared(parentEntity))
				{
					if(!(parentEntity->isAction))	//added 1e6d
					{
						#ifndef NLC_DEFINE_LOCAL_VARIABLES_FOR_ALL_INDEFINATE_ENTITIES
						if(checkSentenceIndexParsingCodeBlocks(parentEntity, sentenceIndex, false))	//this is redundant with NLC_DEFINE_LOCAL_VARIABLES_FOR_ALL_INDEFINATE_ENTITIES
						{
						#endif
							if(!(parentEntity->isCondition))
							{
								if(!(parentEntity->isSubstanceConcept) && !(parentEntity->isActionConcept))
								{
									#ifdef NLC_DEBUG
									cout << "createCodeBlocksCreateNewLocalListVariable: " << parentEntity->entityName << endl;
									#endif
									#ifdef NLC_DEFINE_LOCAL_VARIABLES_FOR_ALL_INDEFINATE_ENTITIES
									if(parentEntity->NLClocalListVariableHasBeenDeclared)
									{//added 1g8a 11-July-2014
										*currentCodeBlockInTree = createCodeBlockAddNewPropertyToLocalList(*currentCodeBlockInTree, parentEntity, parentEntity);
									}
									else
									{
									#endif
										
										*currentCodeBlockInTree = createCodeBlocksCreateNewLocalListVariable(*currentCodeBlockInTree, parentEntity);	//is this ever called with NLC_DEFINE_LOCAL_VARIABLES_FOR_ALL_INDEFINATE_ENTITIES?
									#ifdef NLC_DEFINE_LOCAL_VARIABLES_FOR_ALL_INDEFINATE_ENTITIES
									}
									#endif
									parentEntity->NLCparsedForCodeBlocks = true;
									parentEntity->NLClocalListVariableHasBeenInitialised = true;
									//cout << "createCodeBlocksCreateNewLocalListVariable: " << parentEntity->entityName << endl;

									#ifdef GIA_TRANSLATOR_DREAM_MODE_LINK_SPECIFIC_CONCEPTS_AND_ACTIONS
									//Part 2b: generate object initialisations based on substance concepts (class inheritance)
									generateObjectInitialisationsBasedOnSubstanceConcepts(parentEntity, currentCodeBlockInTree, sentenceIndex);
									#endif
									
									#ifdef NLC_DEBUG
									cout << "\tgenerateObjectInitialisationsBasedOnPropertiesAndConditions:" << parentEntity->entityName << endl;
									cout << "sentenceIndex = " << sentenceIndex << endl;
									#endif
									performedAtLeastParentObjectInitialisation = generateObjectInitialisationsBasedOnPropertiesAndConditions(parentEntity, currentCodeBlockInTree, sentenceIndex, "", "", false);
								}
							}
						#ifndef NLC_DEFINE_LOCAL_VARIABLES_FOR_ALL_INDEFINATE_ENTITIES
						}
						#endif
					}
				}
			}
		}
		#endif
		
	#ifdef NLC_SUPPORT_CONDITION_LOGICAL_OPERATIONS
	}
	#endif
	
	return performedAtLeastParentObjectInitialisation;
}









GIAentityNode * getParent(GIAentityNode * currentEntity, int sentenceIndex, bool parseConditionParents)
{
	if(!(currentEntity->propertyNodeReverseList->empty()))
	{
		GIAentityNode * parentEntity = (currentEntity->propertyNodeReverseList->back())->entity;

		#ifdef NLC_DEFINE_LOCAL_VARIABLES_FOR_ALL_INDEFINATE_ENTITIES
		if(checkSentenceIndexParsingCodeBlocks(parentEntity, sentenceIndex, false))	//NB will parse references to entities in previous sentence
		#else
		if(checkSentenceIndexParsingCodeBlocks(parentEntity, sentenceIndex, false) || parentEntity->NLCparsedForCodeBlocks)
		#endif
		{
			currentEntity = getParent(parentEntity, sentenceIndex, parseConditionParents);
		}
	}
	else if(!(currentEntity->incomingConditionNodeList->empty()) && parseConditionParents)
	{//added 1e9a
		GIAentityNode * conditionEntity = (currentEntity->incomingConditionNodeList->back())->entity;

		bool foundConditionSubject = false;
		GIAentityNode * conditionSubject = NULL;
		if(!(conditionEntity->conditionSubjectEntity->empty()))
		{
			conditionSubject = (conditionEntity->conditionSubjectEntity->back())->entity;
			foundConditionSubject = true;

			#ifdef NLC_DEFINE_LOCAL_VARIABLES_FOR_ALL_INDEFINATE_ENTITIES
			if(checkSentenceIndexParsingCodeBlocks(conditionSubject, sentenceIndex, false))	//NB will parse references to entities in previous sentence
			#else
			if(checkSentenceIndexParsingCodeBlocks(conditionSubject, sentenceIndex, false) || conditionSubject->NLCparsedForCodeBlocks)
			#endif
			{
				currentEntity = getParent(conditionSubject, sentenceIndex, parseConditionParents);
			}
		}
	}

	return currentEntity;
}







//added recursion 1e8a
bool generateObjectInitialisationsBasedOnPropertiesAndConditions(GIAentityNode * entity, NLCcodeblock ** currentCodeBlockInTree, int sentenceIndex, string parentName, string parentConditionName, bool onlyGenerateContextBlocksIfContextNotGeneratedForNLC)
{
	bool performedAtLeastOneObjectInitialisation = false;
	if(!(entity->isSubstanceConcept) && !(entity->isActionConcept))
	{
		//property initialisations
		for(vector<GIAentityConnection*>::iterator propertyNodeListIterator = entity->propertyNodeList->begin(); propertyNodeListIterator < entity->propertyNodeList->end(); propertyNodeListIterator++)
		{
			GIAentityConnection * propertyConnection = (*propertyNodeListIterator);
			GIAentityNode* propertyEntity = propertyConnection->entity;

			if(checkSentenceIndexParsingCodeBlocks(propertyEntity, sentenceIndex, false) || propertyEntity->NLCparsedForCodeBlocks)
			{//only write properties that are explicated in current sentence

				bool performedAtLeastOneObjectInitialisationAtThisLevel = false;
				NLCcodeblock * firstCodeBlockInSection = *currentCodeBlockInTree;

				#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
				if(!onlyGenerateContextBlocksIfContextNotGeneratedForNLC || !(entity->NLCcontextGenerated))
				{//context block already created by generateContextBlocksAndInitialiseParentIfNecessary():generateContextBlocks()	//added 1g14b 15-July-2014
				#endif
					//cout << "entity->entityName = " << entity->entityName << endl;
					//for(all items in context){
					NLCitem * entityClass = new NLCitem(entity, NLC_ITEM_TYPE_CLASS);
					if(assumedToAlreadyHaveBeenDeclared(entity))
					{
						*currentCodeBlockInTree = createCodeBlockForPropertyListLocal(*currentCodeBlockInTree, entityClass);
					}
					else
					{
						entityClass->context.push_back(parentName);
						*currentCodeBlockInTree = createCodeBlockForPropertyList(*currentCodeBlockInTree, entityClass);
					}
				#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
				}
				#endif

				#ifdef NLC_DEBUG
				cout << "createCodeBlockForPropertyList: " << entity->entityName << endl;
				#endif
				
				if(!(propertyConnection->NLCparsedForCodeBlocks))
				{
					#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS
					if(assumedToAlreadyHaveBeenDeclared(propertyEntity))
					{
						//use function argument PropertyList (do not create a new property); eg "the ball" in "Tom has the ball"
						//cout << "propertyEntity->entityName = " << propertyEntity->entityName << endl;
						//for(all items in context){

						NLCcodeblock * firstCodeBlockInSection2 = *currentCodeBlockInTree;

						#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
						if(!onlyGenerateContextBlocksIfContextNotGeneratedForNLC)
						{//context block already created by generateContextBlocksAndInitialiseParentIfNecessary():generateContextBlocks()	//added 1g14b 15-July-2014
						#endif
							NLCitem * propertyClass = new NLCitem(propertyEntity, NLC_ITEM_TYPE_CLASS);
							*currentCodeBlockInTree = createCodeBlockForPropertyListLocal(*currentCodeBlockInTree, propertyClass);
						#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
						}
						#endif

						*currentCodeBlockInTree = createCodeBlockAddProperty(*currentCodeBlockInTree, entity, propertyEntity, sentenceIndex);
						#ifdef NLC_DEBUG
						cout << "createCodeBlockAddProperty: " << entity->entityName << ", " << propertyEntity->entityName << endl;
						#endif
						*currentCodeBlockInTree = firstCodeBlockInSection2->next;
					}
					else
					{
					#endif
						//create a new property; eg "a ball" in "Tom has a ball"

						*currentCodeBlockInTree = createCodeBlockAddNewProperty(*currentCodeBlockInTree, entity, propertyEntity, sentenceIndex, true);
						#ifdef NLC_DEBUG
						cout << "createCodeBlockAddNewProperty: " << entity->entityName << ", " << propertyEntity->entityName << endl;
						#endif
					#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS
					}
					#endif

					#ifdef NLC_DEBUG
					cout << "generateObjectInitialisationsBasedOnPropertiesAndConditions():" << endl;
					cout << "entity->entityName = " << entity->entityName << endl;
					cout << "propertyEntity->entityName = " << propertyEntity->entityName << endl;
					#endif

					propertyConnection->NLCparsedForCodeBlocks = true;
					propertyEntity->NLCparsedForCodeBlocks = true;		//added 3 October 2013 NLC1b2b - used for quick access of instances already declared in current context

					//moved 1e1b: only generate object initialisations for items based on subject concepts when items are created in context
					#ifdef GIA_TRANSLATOR_DREAM_MODE_LINK_SPECIFIC_CONCEPTS_AND_ACTIONS
					//Part 2b: generate object initialisations based on substance concepts (class inheritance)
					generateObjectInitialisationsBasedOnSubstanceConcepts(propertyEntity, currentCodeBlockInTree, sentenceIndex);
					#endif

					performedAtLeastOneObjectInitialisationAtThisLevel = true;
				}

				NLCcodeblock * firstCodeBlockBeforeRecursion = *currentCodeBlockInTree;
				bool performedAtLeastOneObjectInitialisationAtALowerLevel = generateObjectInitialisationsBasedOnPropertiesAndConditions(propertyEntity, currentCodeBlockInTree, sentenceIndex, generateInstanceName(entity), "", onlyGenerateContextBlocksIfContextNotGeneratedForNLC);
				#ifdef NLC_DEBUG
				cout << "performedAtLeastOneObjectInitialisationAtALowerLevel = " << performedAtLeastOneObjectInitialisationAtALowerLevel << endl;
				#endif
				generateObjectInitialisationsBasedOnPropertiesAndConditionsUpdateCodeBlockPointer(currentCodeBlockInTree, firstCodeBlockBeforeRecursion, firstCodeBlockInSection, performedAtLeastOneObjectInitialisationAtThisLevel, performedAtLeastOneObjectInitialisationAtALowerLevel, &performedAtLeastOneObjectInitialisation);
			}
		}

		#ifdef NLC_LOGICAL_CONDITIONS_SUPPORT_CONJUNCTIONS
		//added NLC 1g5e:
		if(!(entity->isCondition))
		{//do not parse conditions of conditions as one of the conditions is a logical condition conjunction (ie and/or)
		#endif	
			//state initialisations
			for(vector<GIAentityConnection*>::iterator conditionNodeListIterator = entity->conditionNodeList->begin(); conditionNodeListIterator < entity->conditionNodeList->end(); conditionNodeListIterator++)
			{
				GIAentityConnection * conditionConnection = (*conditionNodeListIterator);
				GIAentityNode* conditionEntity = conditionConnection->entity;

				#ifdef NLC_SUPPORT_CONDITION_LOGICAL_OPERATIONS
				if(!(conditionEntity->NLClogicalConditionOperation))
				//if(!(conditionConnection->NLCparsedForlogicalConditionOperations) && !(conditionEntity->NLCparsedForlogicalConditionOperations))	//this alternative test would require "tagAllEntitiesInSentenceSubsetAsPertainingToLogicalConditionOperation(conditionSubject, sentenceIndex, false);" to be called before "generateObjectInitialisationsBasedOnPropertiesAndConditions()"
				{
				#endif
					bool foundConditionObject = false;
					GIAentityNode * conditionObject = NULL;
					if(!(conditionEntity->conditionObjectEntity->empty()))
					{
						conditionObject = (conditionEntity->conditionObjectEntity->back())->entity;
						foundConditionObject = true;

						if(checkSentenceIndexParsingCodeBlocks(conditionEntity,  sentenceIndex, false) || conditionEntity->NLCparsedForCodeBlocks)
						{//only write conditions that are explicated in current sentence

							bool performedAtLeastOneObjectInitialisationAtThisLevel = false;
							NLCcodeblock * firstCodeBlockInSection = *currentCodeBlockInTree;

							//cout << "entity->entityName = " << entity->entityName << endl;
							//for(all items in context){
							NLCitem * entityClass = new NLCitem(entity, NLC_ITEM_TYPE_CLASS);
							NLCitem * conditionObjectClass = new NLCitem(conditionObject, NLC_ITEM_TYPE_CLASS);

							#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
							if(!onlyGenerateContextBlocksIfContextNotGeneratedForNLC || !(entity->NLCcontextGenerated))
							{//context block already created by generateContextBlocksAndInitialiseParentIfNecessary():generateContextBlocks()	//added 1g14b 15-July-2014
							#endif
								if(assumedToAlreadyHaveBeenDeclared(entity))
								{
									/*
									cout << "\tassumedToAlreadyHaveBeenDeclared" << endl;
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
									cout << "\t!assumedToAlreadyHaveBeenDeclared" << endl;
									cout << "parentName = " << parentName << endl;
									cout << "entity = " << entity->entityName << endl;
									cout << "conditionEntity = " << conditionEntity->entityName << endl;
									cout << "conditionObject = " << conditionObject->entityName << endl;
									*/
									NLCitem * parentConditionItem = new NLCitem(parentConditionName, NLC_ITEM_TYPE_CLASS);
									parentConditionItem->context.push_back(parentName);
									*currentCodeBlockInTree = createCodeBlockForConditionList(*currentCodeBlockInTree, parentConditionItem, entityClass);
								}
							#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
							}
							#endif

							if(!(conditionConnection->NLCparsedForCodeBlocks))
							{
								#ifdef NLC_DEBUG
								cout << "!(conditionConnection->NLCparsedForCodeBlocks): " << conditionObject->entityName << endl;
								#endif
								
								#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS
								if(assumedToAlreadyHaveBeenDeclared(conditionObject))
								{
									NLCcodeblock * firstCodeBlockInSection2 = *currentCodeBlockInTree;

									//use function argument PropertyList (do not create a new property to insert into condition); eg "the house" in "Tom is near a house"
									//cout << "conditionObject->entityName = " << conditionObject->entityName << endl;
									//for(all items in context){

									#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
									if(!onlyGenerateContextBlocksIfContextNotGeneratedForNLC)
									{//context block already created by generateContextBlocksAndInitialiseParentIfNecessary():generateContextBlocks()	//added 1g14b 15-July-2014
									#endif	
										*currentCodeBlockInTree = createCodeBlockForPropertyListLocal(*currentCodeBlockInTree, conditionObjectClass);
									#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
									}
									#endif

									*currentCodeBlockInTree = createCodeBlockAddCondition(*currentCodeBlockInTree, entity, conditionEntity, sentenceIndex);

									*currentCodeBlockInTree = firstCodeBlockInSection2->next;
								}
								else
								{
								#endif
									//create a new condition; eg "a house" in "Tom is near a house"
									*currentCodeBlockInTree = createCodeBlockAddNewCondition(*currentCodeBlockInTree, entity, conditionEntity, sentenceIndex, true);
									
								#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS
								}
								#endif

								conditionConnection->NLCparsedForCodeBlocks = true;
								conditionEntity->NLCparsedForCodeBlocks = true;	//added 3 October 2013 NLC1b2b - used for quick access of instances already declared in current context
								conditionObject->NLCparsedForCodeBlocks = true;	//added 1e6d

								//moved 1e1b: only generate object initialisations for items based on subject concepts when items are created in context
								#ifdef GIA_TRANSLATOR_DREAM_MODE_LINK_SPECIFIC_CONCEPTS_AND_ACTIONS
								//Part 2b: generate object initialisations based on substance concepts (class inheritance)
								generateObjectInitialisationsBasedOnSubstanceConcepts(conditionEntity, currentCodeBlockInTree, sentenceIndex);
								#endif

								performedAtLeastOneObjectInitialisationAtThisLevel = true;
							}


							NLCcodeblock * firstCodeBlockBeforeRecursion = *currentCodeBlockInTree;
							bool performedAtLeastOneObjectInitialisationAtALowerLevel = generateObjectInitialisationsBasedOnPropertiesAndConditions(conditionObject, currentCodeBlockInTree, sentenceIndex, generateInstanceName(entity), conditionEntity->entityName, onlyGenerateContextBlocksIfContextNotGeneratedForNLC);

							generateObjectInitialisationsBasedOnPropertiesAndConditionsUpdateCodeBlockPointer(currentCodeBlockInTree, firstCodeBlockBeforeRecursion, firstCodeBlockInSection, performedAtLeastOneObjectInitialisationAtThisLevel, performedAtLeastOneObjectInitialisationAtALowerLevel, &performedAtLeastOneObjectInitialisation);
						}
					}
					else
					{
						//no condition object
					}
				#ifdef NLC_SUPPORT_CONDITION_LOGICAL_OPERATIONS
				}
				#endif
			}
		#ifdef NLC_LOGICAL_CONDITIONS_SUPPORT_CONJUNCTIONS
		}
		#endif
	}
	return performedAtLeastOneObjectInitialisation;
}

void generateObjectInitialisationsBasedOnPropertiesAndConditionsUpdateCodeBlockPointer(NLCcodeblock ** currentCodeBlockInTree, NLCcodeblock * firstCodeBlockBeforeRecursion, NLCcodeblock * firstCodeBlockInSection, bool performedAtLeastOneObjectInitialisationAtThisLevel, bool performedAtLeastOneObjectInitialisationAtALowerLevel, bool * performedAtLeastOneObjectInitialisation)
{
	if(!performedAtLeastOneObjectInitialisationAtALowerLevel)
	{
		if(performedAtLeastOneObjectInitialisationAtThisLevel)
		{
			firstCodeBlockBeforeRecursion->codeBlockType = NLC_CODEBLOCK_TYPE_UNDEFINED;
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
			(*currentCodeBlockInTree)->codeBlockType = NLC_CODEBLOCK_TYPE_UNDEFINED;
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
void generateObjectInitialisationsBasedOnSubstanceConcepts(GIAentityNode * entity, NLCcodeblock ** currentCodeBlockInTree, int sentenceIndex)
{
	//added 6 December 2013: take into account plain concepts; eg "dogs are fat. The dog rides the bike." <- the dog will be given the property 'fat'
	GIAentityNode * conceptEntity = (entity->entityNodeDefiningThisInstance->back())->entity;
	generateObjectInitialisationsBasedOnSubstanceConceptsRecurse(entity, conceptEntity, currentCodeBlockInTree, sentenceIndex, "", "");

	for(vector<GIAentityConnection*>::iterator entityNodeDefinitionListIterator = entity->entityNodeDefinitionList->begin(); entityNodeDefinitionListIterator < entity->entityNodeDefinitionList->end(); entityNodeDefinitionListIterator++)
	{
		GIAentityConnection * definitionConnection = (*entityNodeDefinitionListIterator);
		//if(!(definitionConnection->NLCparsedForCodeBlocks))	//probably not required
		//{
		GIAentityNode* definitionEntity = definitionConnection->entity;
		//check the definition is a substance concept
		if((definitionEntity->isSubstanceConcept) || (definitionEntity->isActionConcept))	//added (definitionEntity->isActionConcept)  changed 1e2e
		{
			//cout << "isSubstanceConcept" << endl;
			definitionConnection->NLCparsedForCodeBlocks = true;

			generateObjectInitialisationsBasedOnSubstanceConceptsRecurse(entity, definitionEntity, currentCodeBlockInTree, sentenceIndex, "", "");
		}
		//}
	}
}

void generateObjectInitialisationsBasedOnSubstanceConceptsRecurse(GIAentityNode * entity, GIAentityNode * definitionEntity, NLCcodeblock ** currentCodeBlockInTree, int sentenceIndex, string parentName, string parentConditionName)
{
	#ifdef NLC_SUPPORT_CONDITION_LOGICAL_OPERATIONS_BASED_ON_CONCEPTS
	if(!(definitionEntity->NLCparsedForlogicalConditionOperations))
	{
	#endif
		//property initialisations
		for(vector<GIAentityConnection*>::iterator propertyNodeListIterator = definitionEntity->propertyNodeList->begin(); propertyNodeListIterator < definitionEntity->propertyNodeList->end(); propertyNodeListIterator++)
		{
			GIAentityConnection * propertyConnection = (*propertyNodeListIterator);
			GIAentityNode* propertyEntity = propertyConnection->entity;

			bool alreadyAdded = checkDuplicateProperty(propertyEntity, entity);
			if(!alreadyAdded)
			{
				NLCcodeblock * firstCodeBlockInSection = *currentCodeBlockInTree;
				bool loopUsed = false;

				//cout << "property initialisation: entity->entityName = " << entity->entityName << endl;
				//for(all items in context){
				NLCitem * entityClass = new NLCitem(entity, NLC_ITEM_TYPE_CLASS);
				if(assumedToAlreadyHaveBeenDeclared(entity))
				{
					*currentCodeBlockInTree = createCodeBlockForPropertyListLocal(*currentCodeBlockInTree, entityClass);
				}
				else
				{
					//bool entityHasParent = getEntityContext(entity, &(entityClass->context), false, sentenceIndex, true);
					entityClass->context.push_back(parentName);
					*currentCodeBlockInTree = createCodeBlockForPropertyList(*currentCodeBlockInTree, entityClass);
				}

				*currentCodeBlockInTree = createCodeBlockAddNewProperty(*currentCodeBlockInTree, entity, propertyEntity, sentenceIndex, false);

				entity->NLCparsedForCodeBlocks = true;			//added 4 October 2013 NLC1b6b  - used for quick access of instances already declared in current context
				generateObjectInitialisationsBasedOnSubstanceConceptsRecurse(entity, propertyEntity, currentCodeBlockInTree, sentenceIndex, generateInstanceName(definitionEntity), "");		//updated 9 November 2013 - support recursion of complex substance concept definition

				*currentCodeBlockInTree = firstCodeBlockInSection->next;
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
				NLCcodeblock * firstCodeBlockInSection = *currentCodeBlockInTree;

				bool foundConditionObject = false;
				GIAentityNode * conditionObject = NULL;
				if(!(conditionEntity->conditionObjectEntity->empty()))
				{
					conditionObject = (conditionEntity->conditionObjectEntity->back())->entity;
					foundConditionObject = true;

					//cout << "condition initialisation:  entity->entityName = " << entity->entityName << endl;
					//for(all items in context){
					NLCitem * entityClass = new NLCitem(entity, NLC_ITEM_TYPE_CLASS);

					if(assumedToAlreadyHaveBeenDeclared(entity))
					{
						*currentCodeBlockInTree = createCodeBlockForPropertyListLocal(*currentCodeBlockInTree, entityClass);
					}
					else
					{
						NLCitem * parentConditionItem = new NLCitem(parentConditionName, NLC_ITEM_TYPE_CLASS);
						parentConditionItem->context.push_back(parentName);
						*currentCodeBlockInTree = createCodeBlockForConditionList(*currentCodeBlockInTree, parentConditionItem, entityClass);
					}

					*currentCodeBlockInTree = createCodeBlockAddNewCondition(*currentCodeBlockInTree, entity, conditionEntity, sentenceIndex, false);

					entity->NLCparsedForCodeBlocks = true;			//added 4 October 2013 NLC1b6b  - used for quick access of instances already declared in current context
					generateObjectInitialisationsBasedOnSubstanceConceptsRecurse(entity, conditionObject, currentCodeBlockInTree, sentenceIndex, generateInstanceName(definitionEntity), conditionEntity->entityName);	//updated 9 November 2013 - support recursion of complex substance concept definition

					*currentCodeBlockInTree = firstCodeBlockInSection->next;
				}

			}
		}
	#ifdef NLC_SUPPORT_CONDITION_LOGICAL_OPERATIONS_BASED_ON_CONCEPTS
	}
	#endif
}
#endif



