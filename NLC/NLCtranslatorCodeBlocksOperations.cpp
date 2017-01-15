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
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2015 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 1p12b 27-July-2015
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/


#include "NLCtranslatorCodeBlocksOperations.h"
#include "GIAtranslatorDefs.h"
#include "GIAtranslatorOperations.h"	//required for getPrimaryConceptNodeDefiningInstance()
#include "NLCprintDefs.h"	//required for NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION












bool generateContextBlocks(NLCcodeblock** currentCodeBlockInTree, GIAentityNode* parentEntity, int sentenceIndex, NLCgenerateContextBlocksVariables* generateContextBlocksVariables, bool generatedParentContext, string genericListAppendName)
{	
	#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN
	return generateContextBlocksCategories(currentCodeBlockInTree, parentEntity, sentenceIndex, generateContextBlocksVariables, generatedParentContext, genericListAppendName);	
	#else
	return generateContextBlocksSimple(currentCodeBlockInTree, parentEntity, sentenceIndex, generateContextBlocksVariables, generatedParentContext, genericListAppendName);
	#endif
}

#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN
bool generateContextBlocksCategories(NLCcodeblock** currentCodeBlockInTree, GIAentityNode* parentEntity, int sentenceIndex, NLCgenerateContextBlocksVariables* generateContextBlocksVariables, bool generatedParentContext, string genericListAppendName)
{			
	bool contextFound = false;
	#ifdef NLC_USE_ADVANCED_REFERENCING_SUPPORT_ALIASES
	string parentEntityAliasName = "";
	if(findAliasInEntity(parentEntity, &parentEntityAliasName))
	{
		//added 1k14b;
		*currentCodeBlockInTree = createCodeBlocksDeclareNewCategoryListVariable(*currentCodeBlockInTree, parentEntity, genericListAppendName);
		*currentCodeBlockInTree = createCodeBlocksFindAliasAndAddToCategoryListExecuteFunction(*currentCodeBlockInTree, parentEntityAliasName, parentEntity, genericListAppendName);
		*currentCodeBlockInTree = createCodeBlockForCategoryList(*currentCodeBlockInTree, parentEntity, genericListAppendName);
		parentEntity->NLCcontextGenerated = true;
		contextFound = true;
	}
	else
	{
	#endif
		*currentCodeBlockInTree = createCodeBlocksDeclareNewCategoryListVariable(*currentCodeBlockInTree, parentEntity, genericListAppendName);
		#ifdef NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY_CHILDREN
		if(generateContextBlocksVariables->testNumerosity)
		{
			string categoryListPropertyCountVariableName = generateCategoryListPropertyCountVariableName(parentEntity);
			*currentCodeBlockInTree = createCodeBlockDeclareNewIntVar(*currentCodeBlockInTree, categoryListPropertyCountVariableName, 0);
		}
		#endif

		NLCcodeblock* lastCodeBlockInTree = *currentCodeBlockInTree;
		if(generateContextBlocksSimple(currentCodeBlockInTree, parentEntity, sentenceIndex, generateContextBlocksVariables, generatedParentContext, genericListAppendName))
		{
			contextFound = true;
		}

		addPropertyToCategoryList(currentCodeBlockInTree, parentEntity, parentEntity, genericListAppendName, generateContextBlocksVariables);

		if(!(generatedParentContext && !contextFound))
		{
			*currentCodeBlockInTree = lastCodeBlockInTree->next;
		}

		lastCodeBlockInTree = *currentCodeBlockInTree;
		#ifdef NLC_DEBUG_PARSE_CONTEXT_CHILDREN
		cout << "contextFound: parentEntity = " << parentEntity->entityName << endl;
		#endif
		
		if(generateContextBlocksVariables->searchSubstanceConceptsForChildren)
		{
			//eg "A yellow bannana is on the table. Yellow bannanas are fruit. The fruit is tasty."
			for(vector<GIAentityConnection*>::iterator definitionNodeListIterator = parentEntity->entityNodeDefinitionList->begin(); definitionNodeListIterator < parentEntity->entityNodeDefinitionList->end(); definitionNodeListIterator++)
			{
				GIAentityNode* parentSubstanceConcept = (*definitionNodeListIterator)->entity;	//e.g. "fruit" substance concept
				if(parentSubstanceConcept->isSubstanceConcept)
				{	
					#ifdef NLC_DEBUG_PARSE_CONTEXT_CHILDREN	
					cout << "NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN: createCodeBlockForStatementsForDefinitionChildren{}: parentSubstanceConcept = " << parentSubstanceConcept->entityName << ", idInstance = " << parentSubstanceConcept->idInstance << endl;
					#endif
					if(createCodeBlockForStatementsForDefinitionChildren(currentCodeBlockInTree, &lastCodeBlockInTree, parentEntity, parentSubstanceConcept, sentenceIndex, generateContextBlocksVariables, true, genericListAppendName))
					{
						contextFound = true;
					}
				}
			}
		}

		#ifdef NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY
		#ifdef NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY_CHILDREN
		if(generateContextBlocksVariables->testNumerosity)
		{
			//test numerosity of child
			if(generateContextBlocksVariables->childQuantity > 1)
			{
				#ifdef NLC_CATEGORIES_TEST_PLURALITY_COMMENT
				*currentCodeBlockInTree = createCodeBlockCommentSingleLine(*currentCodeBlockInTree, "numerosity tests (child)");
				#endif
				string categoryListPropertyCountVariableName = generateCategoryListPropertyCountVariableName(parentEntity);
				*currentCodeBlockInTree = createCodeBlockIfIntVariableGreaterThanOrEqualToNum(*currentCodeBlockInTree, categoryListPropertyCountVariableName, generateContextBlocksVariables->childQuantity);
			}			

		}
		#endif
		#endif

		
		#ifdef NLC_FUNCTIONS_SUPPORT_PLURAL_SUBJECTS_AND_OBJECTS
		if(generateContextBlocksVariables->enterGeneratedCategoryList)
		{
		#endif
			#ifdef NLC_CATEGORIES_TEST_PLURALITY
			if((parentEntity->grammaticalNumber == GRAMMATICAL_NUMBER_SINGULAR) && assumedToAlreadyHaveBeenDeclared(parentEntity))	//added assumedToAlreadyHaveBeenDeclared(parentEntity) criteria 1j15a
			{
				#ifdef NLC_CATEGORIES_TEST_PLURALITY_WARNING
				#ifndef NLC_CATEGORIES_TEST_PLURALITY_WARNING_PLACE_IN_NLC_PREDEFINED_FUNCTION_ADDTOCATEGORYIFPASSSINGULARDEFINITEREFERENCINGTESTS
				#ifdef NLC_CATEGORIES_TEST_PLURALITY_COMMENT
				*currentCodeBlockInTree = createCodeBlockCommentSingleLine(*currentCodeBlockInTree, "Singular definite plurality tests");
				#endif
				NLCcodeblock* lastCodeBlockInTree2 = *currentCodeBlockInTree;
				*currentCodeBlockInTree = createCodeBlockIfHasGreaterThanNumCategoryItem(*currentCodeBlockInTree, parentEntity, genericListAppendName, 1);
				*currentCodeBlockInTree = createCodeBlockPrintWarning(*currentCodeBlockInTree, NLC_CATEGORIES_TEST_PLURALITY_WARNING_MESSAGE);
				*currentCodeBlockInTree = lastCodeBlockInTree2->next;
				#endif
				#endif

				#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
				if(generateContextBlocksVariables->setCodeBlockInTreeAtBaseLevel)
				{
					generateContextBlocksVariables->currentCodeBlockInTreeAtBaseLevel = *currentCodeBlockInTree;
				}
				#endif
				#ifdef NLC_CATEGORIES_TEST_PLURALITY_ENFORCE
				*currentCodeBlockInTree = createCodeBlockIfHasCategoryItem(*currentCodeBlockInTree, parentEntity, false, genericListAppendName);	//added 1j5a
				*currentCodeBlockInTree = createCodeBlockGetBackCategoryEntityList(*currentCodeBlockInTree, parentEntity, genericListAppendName);
				#else
				*currentCodeBlockInTree = createCodeBlockForCategoryList(*currentCodeBlockInTree, parentEntity, genericListAppendName);
				#endif
			}
			else
			{
			#endif
				#ifdef NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY
				if(generateContextBlocksVariables->testNumerosity)
				{
					//test numerosity of parent
					if(checkNumerosity(parentEntity))
					{
						#ifdef NLC_CATEGORIES_TEST_PLURALITY_COMMENT
						*currentCodeBlockInTree = createCodeBlockCommentSingleLine(*currentCodeBlockInTree, "numerosity tests (parent)");
						#endif
						*currentCodeBlockInTree = createCodeBlockIfHasGreaterThanOrEqualToNumCategoryItem(*currentCodeBlockInTree, parentEntity, genericListAppendName, parentEntity->quantityNumber);
					}
				}
				#endif

				#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
				if(generateContextBlocksVariables->setCodeBlockInTreeAtBaseLevel)
				{
					generateContextBlocksVariables->currentCodeBlockInTreeAtBaseLevel = *currentCodeBlockInTree;
				}
				#endif
				*currentCodeBlockInTree = createCodeBlockForCategoryList(*currentCodeBlockInTree, parentEntity, genericListAppendName);
			#ifdef NLC_CATEGORIES_TEST_PLURALITY
			}
			#endif

			#ifdef NLC_USE_ADVANCED_REFERENCING
			*currentCodeBlockInTree = createCodeBlockUpdateLastSentenceReferenced(*currentCodeBlockInTree, parentEntity, sentenceIndex);
			#endif
		
		#ifdef NLC_FUNCTIONS_SUPPORT_PLURAL_SUBJECTS_AND_OBJECTS
		}	
		#endif
		
	#ifdef NLC_USE_ADVANCED_REFERENCING_SUPPORT_ALIASES
	}
	#endif
	return contextFound;

}
#endif

bool generateContextBlocksSimple(NLCcodeblock** currentCodeBlockInTree, GIAentityNode* parentEntity, int sentenceIndex, NLCgenerateContextBlocksVariables* generateContextBlocksVariables, bool generatedParentContext, string genericListAppendName)
{
	bool contextFound = false;
	
	NLCcodeblock* originalCodeBlockInTree = *currentCodeBlockInTree;

	//#ifdef NLC_DEBUG_PARSE_CONTEXT3
	//*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("generateContextBlocksSimple{}: ") + parentEntity->entityName);
	//#endif

	#ifndef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN
	#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
	if(generateContextBlocksVariables->setCodeBlockInTreeAtBaseLevel)
	{
		generateContextBlocksVariables->currentCodeBlockInTreeAtBaseLevel = *currentCodeBlockInTree;
	}
	#endif
	#endif
			
	if(!generatedParentContext)
	{
		//context property item:
		if(assumedToAlreadyHaveBeenDeclared(parentEntity))
		{
			*currentCodeBlockInTree = createCodeBlockForOrInLocalList(*currentCodeBlockInTree, parentEntity);	
			#ifdef NLC_DEBUG_PARSE_CONTEXT3
			*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("finished generateContextBlocksSimple{}: 1createCodeBlockForOrInLocalList: ") + parentEntity->entityName);
			#endif
		}
		else
		{
			*currentCodeBlockInTree = createCodeBlockForOrInPropertyList(*currentCodeBlockInTree, parentEntity);	
			#ifdef NLC_DEBUG_PARSE_CONTEXT3
			*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("finished generateContextBlocksSimple{}: 2createCodeBlockForOrInPropertyList: ") + parentEntity->entityName);
			#endif
		}
	}

	#ifdef NLC_DEBUG
	cout << "\tgenerateContextBlocks: " << parentEntity->entityName << endl;
	#endif
	//parse the children (properties and conditions) of an undeclared definite parent
	if(!createCodeBlockForStatements(currentCodeBlockInTree, generateInstanceName(parentEntity), parentEntity, sentenceIndex, generateContextBlocksVariables))
	{
		#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
		//if(!generatedParentContext)	//considered adding 1j13b
		//{
		parentEntity->NLCcontextGenerated = true;	//added 1g14b 15-July-2014
		//}		
		#endif
	}
	else
	{
		contextFound = true;
		#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
		parentEntity->NLCcontextGenerated = true;	//added 1g14b 15-July-2014
		#endif
	}

	return contextFound;
}


#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN
bool createCodeBlockForStatementsForDefinitionChildren(NLCcodeblock** currentCodeBlockInTree, NLCcodeblock** lastCodeBlockInTree, GIAentityNode* parentInstance, GIAentityNode* parentSubstanceConcept, int sentenceIndex, NLCgenerateContextBlocksVariables* generateContextBlocksVariables, bool generateContext, string genericListAppendName)
{
	bool contextFound = false;
	#ifdef NLC_DEBUG_PARSE_CONTEXT_CHILDREN	
	cout << "\t NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN: createCodeBlockForStatementsForDefinitionChildren{}: parentSubstanceConcept = " << parentSubstanceConcept->entityName << endl;		
	#endif
	for(vector<GIAentityConnection*>::iterator reverseDefinitionNodeListIterator = parentSubstanceConcept->entityNodeDefinitionReverseList->begin(); reverseDefinitionNodeListIterator < parentSubstanceConcept->entityNodeDefinitionReverseList->end(); reverseDefinitionNodeListIterator++)
	{
		GIAentityNode* child = (*reverseDefinitionNodeListIterator)->entity;
		if(child != parentInstance)
		{
			if(child->isSubstanceConcept)
			{
				GIAentityNode* childSubstanceConcept = child;
				//recurse; eg "interesting bannanas" in "A yellow bannana is on the table. Interesting bannanas are yellow bannanas. Yellow bannanas are fruit. The fruit is tasty."
				if(createCodeBlockForStatementsForDefinitionChildren(currentCodeBlockInTree, lastCodeBlockInTree, parentInstance, childSubstanceConcept, sentenceIndex, generateContextBlocksVariables, generateContext, genericListAppendName))
				{
					contextFound = true;
				}
			}
			else
			{
				GIAentityNode* childSubstance = child;
				//definition child (e.g. apple)
				#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN_DO_NOT_PARSE_DUPLICATE_CLASSES
				if(child->entityName != parentInstance->entityName)
				{
				#endif	
					//this code is from generateContextBlocksSimple{}:

					//context property item:		
					if(assumedToAlreadyHaveBeenDeclared(childSubstance))
					{
						#ifdef NLC_DEBUG_PARSE_CONTEXT_CHILDREN	
						cout << "1 NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN createCodeBlockForLocalList{}: assumedToAlreadyHaveBeenDeclared: childSubstance = " << childSubstance->entityName << endl;
						#endif
						*currentCodeBlockInTree = createCodeBlockForLocalList(*currentCodeBlockInTree, childSubstance);
					}
					else
					{
						#ifdef NLC_DEBUG_PARSE_CONTEXT_CHILDREN	
						cout << "2 NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN createCodeBlockForPropertyList{}: !assumedToAlreadyHaveBeenDeclared: childSubstance = " << childSubstance->entityName << endl;
						#endif
						*currentCodeBlockInTree = createCodeBlockForPropertyList(*currentCodeBlockInTree, childSubstance);
					}	

					if(generateContext)
					{
						if(createCodeBlockForStatements(currentCodeBlockInTree, generateInstanceName(childSubstance), parentInstance, sentenceIndex, generateContextBlocksVariables))
						{
							contextFound = true;
						}
					}
					else
					{
						contextFound = true;
					}

					addPropertyToCategoryList(currentCodeBlockInTree, parentInstance, childSubstance, genericListAppendName, generateContextBlocksVariables);

					*currentCodeBlockInTree = getLastCodeBlockInLevel(*lastCodeBlockInTree);
					*lastCodeBlockInTree = *currentCodeBlockInTree;
					#ifdef NLC_DEBUG_PARSE_CONTEXT_CHILDREN	
					cout << "3 NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN createCodeBlockForStatements{}: contextFound: parentInstance = " << parentInstance->entityName << ", childSubstance = " << childSubstance << endl;
					#endif
				#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN_DO_NOT_PARSE_DUPLICATE_CLASSES
				}
				#endif	
			}
		}
	}
	return contextFound;
}

bool addPropertyToCategoryList(NLCcodeblock** currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* propertyEntity, string genericListAppendName, NLCgenerateContextBlocksVariables* generateContextBlocksVariables)
{
	bool result = true;
	
	#ifdef NLC_USE_ADVANCED_REFERENCING
	if((entity->grammaticalNumber == GRAMMATICAL_NUMBER_SINGULAR) && assumedToAlreadyHaveBeenDeclared(entity))	//added assumedToAlreadyHaveBeenDeclared(parentEntity) criteria 1j15a
	{
		#ifdef NLC_USE_ADVANCED_REFERENCING_COMMENT
		*currentCodeBlockInTree = createCodeBlockCommentSingleLine(*currentCodeBlockInTree, "Singular definite referencing tests");
		#endif
		*currentCodeBlockInTree = createCodeBlockAddEntityToCategoryListCheckLastSentenceReferencedSingularExecuteFunction(*currentCodeBlockInTree, entity, propertyEntity, genericListAppendName);
	}
	else
	{
		#ifdef NLC_USE_ADVANCED_REFERENCING_COMMENT
		*currentCodeBlockInTree = createCodeBlockCommentSingleLine(*currentCodeBlockInTree, "Plural definite referencing tests");
		#endif
		*currentCodeBlockInTree = createCodeBlockAddEntityToCategoryListCheckLastSentenceReferencedPluralExecuteFunction(*currentCodeBlockInTree, entity, propertyEntity, genericListAppendName);
	}
	#else
	#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN_DO_NOT_ADD_DUPLICATES
	*currentCodeBlockInTree = createCodeBlockAddEntityToCategoryListCheckLastSentenceReferencedPluralExecuteFunction(*currentCodeBlockInTree, entity, propertyEntity, genericListAppendName);	
	#else
	*currentCodeBlockInTree = createCodeBlockAddEntityToCategoryList(*currentCodeBlockInTree, entity, propertyEntity, genericListAppendName);
	#endif
	#endif

	#ifdef NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY_CHILDREN
	if(generateContextBlocksVariables->testNumerosity)
	{
		string categoryListPropertyCountVariableName = generateCategoryListPropertyCountVariableName(entity);
		*currentCodeBlockInTree = createCodeBlockIncrementIntVar(*currentCodeBlockInTree, categoryListPropertyCountVariableName);
	}
	#endif

	return result;
}	
#endif

bool createCodeBlockForStatements(NLCcodeblock** currentCodeBlockInTree, string parentInstanceName, GIAentityNode* entity, int sentenceIndex, NLCgenerateContextBlocksVariables* generateContextBlocksVariables)
{
	bool result = false;
				
	//if object near a red car / if object has a red car (if object has a car which is red)
	//if(item->has(property) && item->has(property1) etc..){
	if(createCodeBlockForConnectionType(GIA_ENTITY_VECTOR_CONNECTION_TYPE_PROPERTIES, currentCodeBlockInTree, parentInstanceName, entity, sentenceIndex, generateContextBlocksVariables))
	{
		result = true;
	}

	//if object near a car that is behind the driveway / if object has a car that is near the house
	//if(item > 3){		/	if(greaterthan(item, 3)){
	if(createCodeBlockForConnectionType(GIA_ENTITY_VECTOR_CONNECTION_TYPE_CONDITIONS, currentCodeBlockInTree, parentInstanceName, entity, sentenceIndex, generateContextBlocksVariables))
	{
		result = true;
	}
	
	#ifdef NLC_RECORD_ACTION_HISTORY
	//if object near a car that drives /if object has a car that drives
	if(createCodeBlockForConnectionType(GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTIONS, currentCodeBlockInTree, parentInstanceName, entity, sentenceIndex, generateContextBlocksVariables))
	{
		result = true;
	}

	//if object near a car that is towed by a truck / if object has a car that is towed by a truck
	if(createCodeBlockForConnectionType(GIA_ENTITY_VECTOR_CONNECTION_TYPE_INCOMING_ACTIONS, currentCodeBlockInTree, parentInstanceName, entity, sentenceIndex, generateContextBlocksVariables))
	{
		result = true;
	}
	#endif
	
	#ifdef NLC_TRANSLATOR_GENERATE_CONTEXT_BLOCKS_PARSE_DEFINITIONS
	//if object near a car that is an apple /if object has a car that is an apple
	if(createCodeBlockForConnectionType(GIA_ENTITY_VECTOR_CONNECTION_TYPE_DEFINITIONS, currentCodeBlockInTree, parentInstanceName, entity, sentenceIndex, generateContextBlocksVariables))
	{
		result = true;
	}	
	#endif

	/*
	//if object near Tom's carparentInstanceName
	currentCodeBlockInTree = createCodeBlockIfHasPropertyOwner(currentCodeBlockInTree, item, entity, sentenceIndex);
	*/
	return result;
}


bool sameReferenceSetReferencingConnectionCheck(GIAentityConnection* targetConnection, NLCgenerateContextBlocksVariables* generateContextBlocksVariables)
{
	bool sameReferenceSetReferencing = false;
	#ifdef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES
	if((targetConnection->isReference) || ((generateContextBlocksVariables->generateContextBlocksIfSameReferenceSet) && (targetConnection->sameReferenceSet)))	//NB isReference check is probably redundant given sameReferenceSet check
	#else
	if((generateContextBlocksVariables->generateContextBlocksIfSameReferenceSet) && (targetConnection->sameReferenceSet))
	#endif
	{
		sameReferenceSetReferencing = true;
	}
	return sameReferenceSetReferencing;
}
		
bool createCodeBlockForConnectionType(int connectionType, NLCcodeblock** currentCodeBlockInTree, string parentInstanceName, GIAentityNode* entity, int sentenceIndex, NLCgenerateContextBlocksVariables* generateContextBlocksVariables)
{				
	bool result = false;
	
	for(vector<GIAentityConnection*>::iterator targetNodeListIterator = entity->entityVectorConnectionsArray[connectionType].begin(); targetNodeListIterator < entity->entityVectorConnectionsArray[connectionType].end(); targetNodeListIterator++)
	{
		GIAentityConnection* targetConnection = (*targetNodeListIterator);
		#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
		//cout << "entity->entityName = " << entity->entityName  << endl;
		//cout << "targetConnection->NLCparsedForCodeBlocks = " << targetConnection->NLCparsedForCodeBlocks << endl;
		//cout << "generateContextBlocksVariables->onlyGenerateContextBlocksIfConnectionsParsedForNLCorSameReferenceSet = " << generateContextBlocksVariables->onlyGenerateContextBlocksIfConnectionsParsedForNLCorSameReferenceSet << endl;
		//cout << "targetConnection->sameReferenceSet = " << targetConnection->sameReferenceSet << endl;
		if((targetConnection->NLCparsedForCodeBlocks) || sameReferenceSetReferencingConnectionCheck(targetConnection, generateContextBlocksVariables) || !(generateContextBlocksVariables->onlyGenerateContextBlocksIfConnectionsParsedForNLCorSameReferenceSet))	//added option 1g13b/15-July-2014	//added option 1i2a 20-August-2014	//added option 1i3d 21-August-2014	//NB isReference check is probably redundant given sameReferenceSet check
		{
		#endif
			GIAentityNode* targetEntity = targetConnection->entity;
			//cout << "targetEntity->entityName = " << targetEntity->entityName  << endl;
			
			#ifdef NLC_TRANSLATOR_GENERATE_CONTEXT_BLOCKS_PARSE_PARENT_EFFICIENT
			if(!(generateContextBlocksVariables->parseParentEfficient) || (targetEntity != generateContextBlocksVariables->childEntityNotToParse))
			{
			#endif
				#ifdef NLC_NORMALISE_TWOWAY_PREPOSITIONS_DUAL_CONDITION_LINKS_ENABLED
				if(!(targetEntity->inverseConditionTwoWay) || targetConnection->isReference)	//prevent infinite loop for 2 way conditions
				{
				#endif
					if(checkSentenceIndexParsingCodeBlocks(targetEntity, targetConnection, sentenceIndex, false))	//changed from true to false 1e5b	//generateContextBlocksVariables->checkSameSentenceConnection
					{//only write conditions that are explicated in current sentence

						#ifdef NLC_DEBUG
						cout << "createCodeBlockForConnectionType{}: " << targetEntity->entityName << endl;
						#endif
						#ifdef NLC_DEBUG_PARSE_CONTEXT
						cout << "createCodeBlockForConnectionType: " << targetEntity->entityName << endl;
						cout << "\t targetConnection->NLCparsedForCodeBlocks: " << targetConnection->NLCparsedForCodeBlocks << endl;
						cout << "\t generateContextBlocksVariables->onlyGenerateContextBlocksIfConnectionsParsedForNLCorSameReferenceSet: " << generateContextBlocksVariables->onlyGenerateContextBlocksIfConnectionsParsedForNLCorSameReferenceSet << endl;
						#ifndef NLC_USE_ADVANCED_REFERENCING
						cout << "\t targetConnection->isReference: " << targetConnection->isReference << endl;
						#endif
						#endif
						#ifdef NLC_DEBUG_PARSE_CONTEXT3
						*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("createCodeBlockForConnectionType{}: ") + entity->entityName + string(" ") + targetEntity->entityName);
						#endif

						#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS_ADVANCED
						bool conjunctionConditionConnectionFound = hasConjunctionConditionConnection(targetEntity, generateContextBlocksVariables->primaryEntityInLogicalConditionConjunctionSubset, generateContextBlocksVariables->logicalConditionConjunctionIndex, &(generateContextBlocksVariables->foundLogicalConditionConjunction));	//dont need to test for mismatched logicalConditionConjunctionIndex; it is just for debugging
						if(!conjunctionConditionConnectionFound)
						{
						#endif
							bool resultTemp = false;
							bool generateContextForObject = false;
							GIAentityNode* objectEntity = NULL;
							if(connectionType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_PROPERTIES)
							{
								if(createCodeBlockForGivenProperty(currentCodeBlockInTree, parentInstanceName, targetEntity, sentenceIndex, generateContextBlocksVariables, &objectEntity, &generateContextForObject))
								{
									resultTemp = true;
									#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
									if(targetConnection->negative)
									{
										generateContextBlocksVariables->negativeDetectedInContextBlocks = true;
									}
									#endif
								}
							}
							else if(connectionType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_CONDITIONS)
							{
								if(createCodeBlockForGivenCondition(currentCodeBlockInTree, parentInstanceName, targetEntity, sentenceIndex, generateContextBlocksVariables, &objectEntity, &generateContextForObject))
								{
									resultTemp = true;
								}
							}
							#ifdef NLC_RECORD_ACTION_HISTORY
							else if(connectionType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTIONS)
							{
								if(createCodeBlockForGivenAction(currentCodeBlockInTree, parentInstanceName, targetEntity, sentenceIndex, generateContextBlocksVariables, &objectEntity, &generateContextForObject))
								{
									resultTemp = true;
								}
							}
							else if(connectionType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_INCOMING_ACTIONS)
							{
								if(createCodeBlockForGivenActionIncoming(currentCodeBlockInTree, parentInstanceName, targetEntity, sentenceIndex, generateContextBlocksVariables, &objectEntity, &generateContextForObject))
								{
									resultTemp = true;
								}
							}
							#endif
							#ifdef NLC_TRANSLATOR_GENERATE_CONTEXT_BLOCKS_PARSE_DEFINITIONS
							else if(connectionType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_DEFINITIONS)
							{	
								#ifdef NLC_USE_ADVANCED_REFERENCING_SUPPORT_ALIASES
								if(targetConnection->isAlias)
								{
									if(createCodeBlockForGivenAlias(currentCodeBlockInTree, entity, targetEntity, sentenceIndex, generateContextBlocksVariables, &objectEntity, &generateContextForObject))
									{
										//cout << "createCodeBlockForGivenAlias: parentInstanceName = " << parentInstanceName << ", targetEntity = " << targetEntity->entityName << endl;
										resultTemp = true;
									}
								}
								else
								{
								#endif
									if(createCodeBlockForGivenDefinition(currentCodeBlockInTree, parentInstanceName, targetEntity, sentenceIndex, generateContextBlocksVariables, &objectEntity, &generateContextForObject))
									{
										//cout << "createCodeBlockForGivenDefinition: parentInstanceName = " << parentInstanceName << ", targetEntity = " << targetEntity->entityName << endl;
										resultTemp = true;
									}
								#ifdef NLC_USE_ADVANCED_REFERENCING_SUPPORT_ALIASES	
								}
								#endif
							}
							#endif
							if(resultTemp)
							{
								result = true;
								targetConnection->NLCparsedForCodeBlocks = true;

								if(generateContextForObject)
								{
									#ifdef NLC_RECORD_ACTION_HISTORY
									if((connectionType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTIONS) || (connectionType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_INCOMING_ACTIONS))
									{
										targetEntity->NLCcontextGeneratedTemp = true;
									}
									#endif	

									#ifdef NLC_TRANSLATOR_GENERATE_CONTEXT_BLOCKS_PARSE_PARENT_OF_TARGET_AND_MULTIPLE_DEFINITE_ENTITIES
									bool verifyObject = false;
									bool foundParentEntityNew = false;
									GIAentityNode* parentEntityNew = NULL;

									bool parseConditionParents = NLC_PARSE_CONDITION_PARENTS_DEFAULT_VALUE;
									bool checkIsDefinite = false;	//CHECKTHIS; support isolated definite objects, indefinite parents, and definite parents; eg 1. "the chicken that is next to the pie." , 2. "the chicken that is next to a dog's pie." and 3. "the chicken that is next to the dog's pie."
									parentEntityNew = getSameReferenceSetUniqueParent(objectEntity, sentenceIndex, entity, &foundParentEntityNew, parseConditionParents, checkIsDefinite);
									if(isDefiniteEntity(objectEntity) || foundParentEntityNew)	//ie objectEntity is explicitly or implicitly definite
									{
										if(!(objectEntity->isSubstanceQuality))	//added 1n24a
										{
											verifyObject = true;
										}
									}

									if(verifyObject)
									{
										//cout << "verifyObject:" << endl;
										//cout << "entity = " << entity->entityName << endl;
										//cout << "objectEntity = " << objectEntity->entityName << endl;
										//cout << "isDefiniteEntity(objectEntity) = " << isDefiniteEntity(objectEntity) << endl;
										
										//save objectEntity as tempVariable objectEntityCandidate
										string candidateObjectClassName = generateClassName(objectEntity);
										string candidateObjectInstanceName = generateCandidateObjectName(objectEntity);
										*currentCodeBlockInTree = createCodeBlockDeclareTempVariableAndSetToEntity(*currentCodeBlockInTree, candidateObjectClassName, candidateObjectInstanceName, objectEntity);

										//NB this code is based on generateContextForChildEntity{}: it requires NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN, NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_FOR_EACH_CHILD and NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_FOR_EACH_CHILD_GET_PARENT
										bool generatedContextForChild = false;
										if(foundParentEntityNew)
										{
											if(generateContextBlocksForParentEntity(currentCodeBlockInTree, objectEntity, parentEntityNew, sentenceIndex, generateContextBlocksVariables))
											{
												generatedContextForChild = true;
											}
											else
											{
												cout << "createCodeBlockForConnectionType{}: generateContextBlocksForParentEntity{} error: !generatedContextForChild" << endl;
											}
										}
										if(generateContextBlocks(currentCodeBlockInTree, objectEntity, sentenceIndex, generateContextBlocksVariables, generatedContextForChild, NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION))
										{

										}

										//now verify that objectEntity == objectEntityCandidate
										*currentCodeBlockInTree = createCodeBlockIfTempVariableEqualsEntity(*currentCodeBlockInTree, candidateObjectClassName, candidateObjectInstanceName, objectEntity);
									}
									else
									{	//CHECKTHIS; support isolated indefinite objects; eg 4. "the chicken that is next to a pie."
									#endif
										createCodeBlockForStatements(currentCodeBlockInTree, generateInstanceName(objectEntity), objectEntity, sentenceIndex, generateContextBlocksVariables);
									#ifdef NLC_TRANSLATOR_GENERATE_CONTEXT_BLOCKS_PARSE_PARENT_OF_TARGET_AND_MULTIPLE_DEFINITE_ENTITIES
									}
									#endif

									#ifdef NLC_RECORD_ACTION_HISTORY
									if((connectionType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTIONS) || (connectionType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_INCOMING_ACTIONS))
									{
										targetEntity->NLCcontextGeneratedTemp = false;
									}
									#endif	
								}							

								#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS_ADVANCED
								targetEntity->NLClogicalConditionConjunctionIndex = generateContextBlocksVariables->logicalConditionConjunctionIndex;
								#endif
							}					
						#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS_ADVANCED
						}
						#endif
					}
				#ifdef NLC_NORMALISE_TWOWAY_PREPOSITIONS_DUAL_CONDITION_LINKS_ENABLED
				}
				#endif
			#ifdef NLC_TRANSLATOR_GENERATE_CONTEXT_BLOCKS_PARSE_PARENT_EFFICIENT
			}
			#endif
		#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
		}
		#endif
	}
	
	return result;
}

#ifdef NLC_TRANSLATOR_GENERATE_CONTEXT_BLOCKS_PARSE_PARENT_OF_TARGET_AND_MULTIPLE_DEFINITE_ENTITIES
string generateCandidateObjectName(GIAentityNode* objectEntity)
{
	string candidateObjectName = objectEntity->entityName + NLC_TRANSLATOR_GENERATE_CONTEXT_BLOCKS_PARSE_PARENT_OF_TARGET_AND_MULTIPLE_DEFINITE_ENTITIES_CANDIDATE_OBJECT_NAME_PREPEND;
	return candidateObjectName;
}
#endif
	
bool createCodeBlockForGivenProperty(NLCcodeblock** currentCodeBlockInTree, string parentInstanceName, GIAentityNode* propertyEntity, int sentenceIndex, NLCgenerateContextBlocksVariables* generateContextBlocksVariables, GIAentityNode** objectEntity, bool* generateContextForObject)
{
	bool result = true;
	*generateContextForObject = true;
	
	#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
	propertyEntity->NLCcontextGenerated = true;	//added 1g14b 15-July-2014
	#endif
	
	#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS_BASIC
	if(logicalOperation == NLC_LOGICAL_CONDITION_OPERATIONS_FOR)
	{
		*currentCodeBlockInTree = createCodeBlockForPropertyList(*currentCodeBlockInTree, propertyEntity, parentInstanceName);
	}
	else if(logicalOperation == NLC_LOGICAL_CONDITION_OPERATIONS_IF)
	{
		*currentCodeBlockInTree = createCodeBlockIfHasProperty(*currentCodeBlockInTree, propertyEntity, parentInstanceName, generateContextBlocksVariables->negative);
	}
	else if(logicalOperation == NLC_LOGICAL_CONDITION_OPERATIONS_WHILE)
	{
		*currentCodeBlockInTree = createCodeBlockWhileHasProperty(*currentCodeBlockInTree, propertyEntity, parentInstanceName, generateContextBlocksVariables->negative);
	}
	#else
	*currentCodeBlockInTree = createCodeBlockForOrInPropertyList(*currentCodeBlockInTree, propertyEntity, parentInstanceName);
	#endif

	#ifdef NLC_DEBUG
	//cout << "createCodeBlockForGivenProperty{}: propertyEntity = " << propertyEntity->entityName << endl;
	//*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, propertyEntity->entityName);
	#endif

	#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
	if(propertyEntity->isSubstanceQuality)
	{
		if(propertyEntity->negative)
		{
			//cout << "propertyEntity->negative: propertyEntity->entityName = " << propertyEntity->entityName << endl;
			generateContextBlocksVariables->negativeDetectedInContextBlocks = true;
		}
	}
	#endif
	#ifdef NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY_CHILDREN
	if(generateContextBlocksVariables->testNumerosity)
	{
		if(checkNumerosity(propertyEntity))
		{
			generateContextBlocksVariables->childQuantity = propertyEntity->quantityNumber;
			//cout << "generateContextBlocksVariables->childQuantity = " << generateContextBlocksVariables->childQuantity << endl;
		}
	}
	#endif
	
	/*
	createCodeBlockForStatements(currentCodeBlockInTree, generateInstanceName(propertyEntity), propertyEntity, sentenceIndex, generateContextBlocksVariables);
	*/
	*objectEntity = propertyEntity;
					
	return result;
}

bool createCodeBlockForGivenCondition(NLCcodeblock** currentCodeBlockInTree, string parentInstanceName, GIAentityNode* conditionEntity, int sentenceIndex, NLCgenerateContextBlocksVariables* generateContextBlocksVariables, GIAentityNode** objectEntity, bool* generateContextForObject)
{
	bool result = false;

	#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS_ADVANCED
	bool conjunctionConditionFound = textInTextArray(conditionEntity->entityName, entityCoordinatingConjunctionArray, ENTITY_COORDINATINGCONJUNCTION_ARRAY_NUMBER_OF_TYPES);
	if(!conjunctionConditionFound)
	{//do not parse conjunction conditions
	#endif
	
		if(!(conditionEntity->conditionObjectEntity->empty()))
		{		
			GIAentityNode* conditionObject = (conditionEntity->conditionObjectEntity->back())->entity;
			result = true;	
			*generateContextForObject = true;

			#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
			conditionObject->NLCcontextGenerated = true;	//added 1g14b 15-July-2014
			#endif

			#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS_BASIC
			if(logicalOperation == NLC_LOGICAL_CONDITION_OPERATIONS_FOR)
			{
				*currentCodeBlockInTree = createCodeBlockForConditionList(*currentCodeBlockInTree, conditionEntity, conditionObject, parentInstanceName);
			}
			else if(logicalOperation == NLC_LOGICAL_CONDITION_OPERATIONS_IF)
			{
				*currentCodeBlockInTree = createCodeBlockIfHasCondition(*currentCodeBlockInTree, conditionEntity, conditionObject, parentInstanceName, generateContextBlocksVariables->negative);
			}
			else if(logicalOperation == NLC_LOGICAL_CONDITION_OPERATIONS_WHILE)
			{
				*currentCodeBlockInTree = createCodeBlockWhileHasCondition(*currentCodeBlockInTree, conditionEntity, conditionObject, parentInstanceName, generateContextBlocksVariables->negative);
			}
			#else
			*currentCodeBlockInTree = createCodeBlockForConditionList(*currentCodeBlockInTree, conditionEntity, conditionObject, parentInstanceName);
			#endif

			#ifdef NLC_DEBUG
			//cout << "createCodeBlockForGivenCondition{}: " << conditionObjectItem->instanceName << endl;
			#endif

			#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
			if(conditionEntity->negative)
			{
				generateContextBlocksVariables->negativeDetectedInContextBlocks = true;
			}
			#endif
			#ifdef NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY_CHILDREN
			if(generateContextBlocksVariables->testNumerosity)
			{
				if(checkNumerosity(conditionObject))
				{
					generateContextBlocksVariables->childQuantity = conditionObject->quantityNumber;
				}
			}
			#endif
			
			/*
			createCodeBlockForStatements(currentCodeBlockInTree, generateInstanceName(conditionObject), conditionObject, sentenceIndex, generateContextBlocksVariables);
			*/
			*objectEntity = conditionObject;
		}
		else
		{
			result = false;
			cout << "error createCodeBlockForGivenCondition{}: condition does not have object" << endl;
		}
	#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS_ADVANCED
	}
	else
	{
		generateContextBlocksVariables->foundLogicalConditionConjunction = conditionEntity;
	}
	#endif
	
	return result;
}

#ifdef NLC_RECORD_ACTION_HISTORY
bool createCodeBlockForGivenAction(NLCcodeblock** currentCodeBlockInTree, string parentInstanceName, GIAentityNode* actionEntity, int sentenceIndex, NLCgenerateContextBlocksVariables* generateContextBlocksVariables, GIAentityNode** objectEntity, bool* generateContextForObject)
{
	bool result = false;

	if(!(actionEntity->NLCcontextGeneratedTemp))
	{
		result = true;
		
		#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
		actionEntity->NLCcontextGenerated = true;
		#endif

		*currentCodeBlockInTree = createCodeBlockForActionList(*currentCodeBlockInTree, actionEntity, parentInstanceName);	

		#ifdef NLC_DEBUG
		//cout << "createCodeBlockForGivenAction{}: " << actionItem->instanceName << endl;
		#endif

		#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
		if(actionEntity->negative)
		{
			generateContextBlocksVariables->negativeDetectedInContextBlocks = true;
		}
		#endif
			
		bool hasActionObject = false;
		if(!(actionEntity->actionObjectEntity->empty()))
		{
			*generateContextForObject = true;
			
			GIAentityNode* actionObject = (actionEntity->actionObjectEntity->back())->entity;
			#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
			actionObject->NLCcontextGenerated = true;
			#endif
			#ifdef NLC_RECORD_ACTION_HISTORY_COMPENSATE_FOR_EFFECTIVE_DEFINITE_ENTITIES_IMPLEMENTATION1
			actionObject->grammaticalDefiniteTemp = true;
			#endif

			hasActionObject = true;
			*currentCodeBlockInTree = createCodeBlockForActionObjectList(*currentCodeBlockInTree, actionObject, generateInstanceName(actionEntity));

			/*
			actionEntity->NLCcontextGeneratedTemp = true;
			createCodeBlockForStatements(currentCodeBlockInTree, generateInstanceName(actionObject), actionObject, sentenceIndex, generateContextBlocksVariables);	//OLD: generateInstanceName(actionEntity)
			actionEntity->NLCcontextGeneratedTemp = false;
			*/
			*objectEntity = actionObject;
		}
	}

	return result;
}

bool createCodeBlockForGivenActionIncoming(NLCcodeblock** currentCodeBlockInTree, string parentInstanceName, GIAentityNode* actionEntity, int sentenceIndex, NLCgenerateContextBlocksVariables* generateContextBlocksVariables, GIAentityNode** objectEntity, bool* generateContextForObject)
{
	bool result = false;

	if(!(actionEntity->NLCcontextGeneratedTemp))
	{
		result = true;
		
		#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
		actionEntity->NLCcontextGenerated = true;
		#endif

		*currentCodeBlockInTree = createCodeBlockForActionIncomingList(*currentCodeBlockInTree, actionEntity, parentInstanceName);	

		#ifdef NLC_DEBUG
		//cout << "createCodeBlockForGivenActionIncoming{}: " << actionItem->instanceName << endl;
		#endif

		#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
		if(actionEntity->negative)
		{
			generateContextBlocksVariables->negativeDetectedInContextBlocks = true;
		}
		#endif
		
		bool hasActionSubject = false;
		if(!(actionEntity->actionSubjectEntity->empty()))
		{
			*generateContextForObject = true;
			
			GIAentityNode* actionSubject = (actionEntity->actionSubjectEntity->back())->entity;
			#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
			actionSubject->NLCcontextGenerated = true;
			#endif
			#ifdef NLC_RECORD_ACTION_HISTORY_COMPENSATE_FOR_EFFECTIVE_DEFINITE_ENTITIES_IMPLEMENTATION1
			actionSubject->grammaticalDefiniteTemp = true;
			#endif
		
			hasActionSubject = true;
			*currentCodeBlockInTree = createCodeBlockForActionSubjectList(*currentCodeBlockInTree, actionSubject, generateInstanceName(actionEntity));
			
			/*
			actionEntity->NLCcontextGeneratedTemp = true;
			createCodeBlockForStatements(currentCodeBlockInTree, generateInstanceName(actionSubject), actionSubject, sentenceIndex, generateContextBlocksVariables);	//OLD: generateInstanceName(actionEntity)
			actionEntity->NLCcontextGeneratedTemp = false;
			*/
			*objectEntity = actionSubject;
		}
	}
							
	return result;
}
#endif
#ifdef NLC_TRANSLATOR_GENERATE_CONTEXT_BLOCKS_PARSE_DEFINITIONS
bool createCodeBlockForGivenDefinition(NLCcodeblock** currentCodeBlockInTree, string parentInstanceName, GIAentityNode* definitionEntity, int sentenceIndex, NLCgenerateContextBlocksVariables* generateContextBlocksVariables, GIAentityNode** objectEntity, bool* generateContextForObject)
{
	bool result = true;
	*generateContextForObject = true;
	
	#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
	definitionEntity->NLCcontextGenerated = true;
	#endif
	
	*currentCodeBlockInTree = createCodeBlockCheckParentClassNameExecuteFunction1(*currentCodeBlockInTree, parentInstanceName, definitionEntity->entityName);
					
	#ifdef NLC_DEBUG
	//cout << "createCodeBlockForGivenDefinition{}: definitionEntity = " << definitionEntity->entityName << endl;
	//*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, definitionEntity->entityName);
	#endif
	
	/*
	createCodeBlockForStatements(currentCodeBlockInTree, parentInstanceName, definitionEntity, sentenceIndex, generateContextBlocksVariables);	//creates for statements (generates context) according to the properties/conditions of the substance concept (assuming it is a specific concept eg "blue" in "if the boat is a blue chicken")
	*/
	*objectEntity = definitionEntity;
				
	return result;
}
#ifdef NLC_USE_ADVANCED_REFERENCING_SUPPORT_ALIASES	
bool createCodeBlockForGivenAlias(NLCcodeblock** currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* definitionEntity, int sentenceIndex, NLCgenerateContextBlocksVariables* generateContextBlocksVariables, GIAentityNode** objectEntity, bool* generateContextForObject)
{
	bool result = true;	
	*generateContextForObject = false;	//do not parse context past alias definition links
	
	#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
	definitionEntity->NLCcontextGenerated = true;
	#endif
	
	string aliasName = definitionEntity->entityName;
	
	/*FUTURE CHECK alias has been added to definition entity?;
	if(findAliasInEntity(definitionEntity, &aliasName)
	{
	*/
		
	*currentCodeBlockInTree = createCodeBlocksFindAliasExecuteFunction(*currentCodeBlockInTree, aliasName, entity);

	#ifdef NLC_DEBUG
	//cout << "createCodeBlocksFindAliasExecuteFunction{}: definitionEntity = " << definitionEntity->entityName << endl;
	//*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, definitionEntity->entityName);
	#endif

	return result;
}
#endif
#endif

#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS_ADVANCED
bool hasConjunctionConditionConnection(GIAentityNode* conditionEntity, GIAentityNode* primaryEntityInLogicalConditionConjunctionSubset, int logicalConditionConjunctionIndex, GIAentityNode** foundLogicalConditionConjunction)	//dont need to test for mismatched logicalConditionConjunctionIndex; it is just for debugging
{
	bool conjunctionConditionConnectionFound = false;

	for(vector<GIAentityConnection*>::iterator conditionNodeListIterator = conditionEntity->conditionNodeList->begin(); conditionNodeListIterator < conditionEntity->conditionNodeList->end(); conditionNodeListIterator++)
	{
		GIAentityConnection* conditionConnection = (*conditionNodeListIterator);
		GIAentityNode* conditionEntity2 = conditionConnection->entity;
		bool conjunctionConditionFound = textInTextArray(conditionEntity2->entityName, entityCoordinatingConjunctionArray, ENTITY_COORDINATINGCONJUNCTION_ARRAY_NUMBER_OF_TYPES);
		if(conjunctionConditionFound)
		{
			if(conditionEntity != primaryEntityInLogicalConditionConjunctionSubset)
			{//ignore primaryEntityInLogicalConditionConjunctionSubset
				if(conditionEntity2->NLCconjunctionCondition)
				{//condition added 1g6h; do not parse nodes with conjunction condition connections if the conjunction condition has already been parsed by checkConditionForLogicalCondition()
					conjunctionConditionConnectionFound = true;
				}
			}
			//if(conditionEntity != primaryEntityInLogicalConditionConjunctionSubset) {//removed NLC 1g6j - 10 July 2014
			if(!(conditionEntity2->NLCconjunctionCondition))
			{//do not reparse same conjunction conditions - added NLC 1g7b/11 July 2014
				if(*foundLogicalConditionConjunction == NULL)
				{//do not overwrite foundLogicalConditionConjunction; always take the first conjunction in subset as the one to parse next - added NLC 1g6j/10 July 2014
					*foundLogicalConditionConjunction = conditionEntity2;
				}
			}
			//}
		}
	}
	if(conditionEntity != primaryEntityInLogicalConditionConjunctionSubset)
	{
		for(vector<GIAentityConnection*>::iterator conditionNodeListIterator = conditionEntity->incomingConditionNodeList->begin(); conditionNodeListIterator < conditionEntity->incomingConditionNodeList->end(); conditionNodeListIterator++)
		{
			GIAentityConnection* conditionConnection = (*conditionNodeListIterator);
			GIAentityNode* conditionEntity2 = conditionConnection->entity;
			bool conjunctionConditionFound = textInTextArray(conditionEntity2->entityName, entityCoordinatingConjunctionArray, ENTITY_COORDINATINGCONJUNCTION_ARRAY_NUMBER_OF_TYPES);
			if(conjunctionConditionFound)
			{
				conjunctionConditionConnectionFound = true;
				//*foundLogicalConditionConjunction = conditionEntity2;	//NB only parse conjunction conditions in forwards direction
			}
		}
	}

	/*
	//for debugging only:
	if(!conjunctionConditionConnectionFound)
	{
		if((conditionEntity->NLClogicalConditionConjunctionIndex != logicalConditionConjunctionIndex) && (conditionEntity->NLClogicalConditionConjunctionIndex != INT_DEFAULT_VALUE))
		{
			cout << "hasConjunctionConditionConnection{} error: child of primaryEntityInLogicalConditionConjunctionSubset has been declared as pertaining to a different logicalConditionConjunctionSubset - is this a shared context?" << endl;
		}
	}
	*/

	return conjunctionConditionConnectionFound;
}
#endif





































bool getParentAndInitialiseParentIfNecessaryOrGenerateContextBlocks(NLCcodeblock** currentCodeBlockInTree, GIAentityNode* currentEntity, int sentenceIndex, NLCgenerateContextBlocksVariables* generateContextBlocksVariables, bool parseLogicalConditions, GIAentityNode** parentEntity, bool* newInitialisation, bool testOnly)
{
	bool result = false;
	
	*parentEntity = getParent(currentEntity, sentenceIndex, generateContextBlocksVariables);
	
	//cout << "getParentAndInitialiseParentIfNecessaryOrGenerateContextBlocks:" << endl;
	//cout << "currentEntity = " << currentEntity->entityName << endl;
	//cout << "*parentEntity = " << (*parentEntity)->entityName << endl;
	
	if(checkSentenceIndexParsingCodeBlocks(currentEntity, sentenceIndex, false))
	{//is this required?

		#ifdef NLC_DEBUG_PARSE_CONTEXT4
		*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("getParentAndInitialiseParentIfNecessaryOrGenerateContextBlocks{}: generateContextBasedOnDeclaredParent; currentEntity: ") + currentEntity->entityName + string(", parentEntity: ") + (*parentEntity)->entityName);
		#endif

		if(generateParentInitialisationCodeBlockWithChecks(currentCodeBlockInTree, *parentEntity, sentenceIndex, parseLogicalConditions, testOnly))
		{
			//cout << "generateParentInitialisationCodeBlockWithChecks passed" << endl;
			
			result = true;
			*newInitialisation = true;
			//eg "barrel" in "A chicken's barrel eats the bike."
			
			if(!testOnly)
			{
				if(*parentEntity == currentEntity)
				{
					#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_BLOCKS_FOR_PARENT_INITIALISATION_SPECIAL
					*currentCodeBlockInTree = createCodeBlockForCategoryList(*currentCodeBlockInTree, currentEntity, NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION);
					#else
					*currentCodeBlockInTree = createCodeBlockForLocalList(*currentCodeBlockInTree, currentEntity);
					#endif
				}
				else
				{//case added 1n25a
					#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_BLOCKS_FOR_PARENT_INITIALISATION_SPECIAL
					*currentCodeBlockInTree = createCodeBlockForCategoryList(*currentCodeBlockInTree, *parentEntity, NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION);
					#else
					*currentCodeBlockInTree = createCodeBlockForLocalList(*currentCodeBlockInTree, *parentEntity);
					#endif
					*currentCodeBlockInTree = createCodeBlockForOrInPropertyList(*currentCodeBlockInTree, currentEntity, generateInstanceName(*parentEntity));	
				}
			}
		}
		else
		{
			if(!testOnly)
			{
				if(generateContextForChildEntity(currentCodeBlockInTree, NULL, currentEntity, sentenceIndex, true))	//NB parent entity parameter is set to NULL such that it can be obtained by getSameReferenceSetUniqueParent()
				{
					result = true;
				}
			}
		}
	}
	
	return result;

}

bool generateParentInitialisationCodeBlockWithChecks(NLCcodeblock** currentCodeBlockInTree, GIAentityNode* parentEntity, int sentenceIndex, bool parseLogicalConditions, bool testOnly)
{
	bool result = false;

	//cout << "generateParentInitialisationCodeBlockWithChecks: parentEntity->NLCparsedForlogicalConditionOperations = " << parentEntity->NLCparsedForlogicalConditionOperations << endl;
	//cout << "a1" << endl;
	#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
	if(!(parentEntity->NLCparsedForlogicalConditionOperations) || parseLogicalConditions)	//CHECKTHIS; change from !(entity->NLCparsedForlogicalConditionOperations) to !(parentEntity->NLCparsedForlogicalConditionOperations) 1g14a 15-July-2014
	{
	#endif
		//moved here 1e8a (out of generateObjectInitialisationsBasedOnPropertiesAndConditions)
		//added 1e6c: eg A chicken's hat has a bike. / A blue dog has a bike.
		if(!checkConceptTypeEntity(parentEntity)) //OLD 1n: if(!checkSpecialCaseEntity(parentEntity, true))
		{
			if(!(parentEntity->NLCparsedForCodeBlocks))	// && !(entity->parsedForNLCcodeBlocksActionRound)
			{
				if(!assumedToAlreadyHaveBeenDeclared(parentEntity))
				{
					#ifndef NLC_DEFINE_LOCAL_VARIABLES_FOR_ALL_INDEFINATE_ENTITIES
					if(checkSentenceIndexParsingCodeBlocks(parentEntity, sentenceIndex, false))	//this is redundant with NLC_DEFINE_LOCAL_VARIABLES_FOR_ALL_INDEFINATE_ENTITIES
					{
					#endif
						#ifdef NLC_VERIFY_CONNECTIONS_SENTENCE_INDEX
						if(parentEntity->sentenceIndexTemp == sentenceIndex)	//ie "wasReference" is not a sufficient condition to initialise parent
						{
						#endif
							#ifdef NLC_RECORD_ACTION_HISTORY_GENERALISABLE
							if(!(parentEntity->NLCcontextGenerated))	//added 1l3b
							{
							#endif
								result = true;
								if(!testOnly)
								{
									#ifdef NLC_DEBUG
									cout << "generateParentInitialisationCodeBlockWithChecks{}: generateParentInitialisationCodeBlock: parentEntity = " << parentEntity->entityName << endl;
									#endif
									generateObjectInitialisations(currentCodeBlockInTree, parentEntity, sentenceIndex);
								}
							#ifdef NLC_RECORD_ACTION_HISTORY_GENERALISABLE
							}		
							#endif								
						#ifdef NLC_VERIFY_CONNECTIONS_SENTENCE_INDEX
						}
						#endif
					#ifndef NLC_DEFINE_LOCAL_VARIABLES_FOR_ALL_INDEFINATE_ENTITIES
					}
					#endif
				}
			}
		}

	#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
	}
	#endif

	return result;
}

bool generateObjectInitialisations(NLCcodeblock** currentCodeBlockInTree, GIAentityNode* entity, int sentenceIndex)
{
	bool result = true;

	#ifdef NLC_DEBUG
	cout << "generateObjectInitialisations: " << entity->entityName << endl;
	cout << "sentenceIndex = " << sentenceIndex << endl;
	#endif
	#ifdef NLC_DEBUG_PARSE_CONTEXT3
	*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("generateObjectInitialisations{}: ") + entity->entityName);
	#endif
	
	NLCcodeblock* codeBlockInTreeBeforeGenerateParentInitialisation = *currentCodeBlockInTree;
	
	*currentCodeBlockInTree = createCodeBlocksCreateNewLocalListVariable(*currentCodeBlockInTree, entity, sentenceIndex);

	entity->NLCparsedForCodeBlocks = true;
	entity->NLClocalListVariableHasBeenInitialised = true;
	//cout << "createCodeBlocksCreateNewLocalListVariable: " << entity->entityName << endl;
	
	#ifdef GIA_TRANSLATOR_DREAM_MODE_LINK_SPECIFIC_CONCEPTS_AND_ACTIONS
	//Part 2b: generate object initialisations based on substance concepts (class inheritance)
	generateObjectInitialisationsBasedOnSubstanceConcepts(entity, currentCodeBlockInTree, sentenceIndex, true);
	#endif

	//*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("generateObjectInitialisations{}: ") + entity->entityName);

	NLCcodeblock* codeBlockInTreeBeforeGenerateObjectInitialisations = *currentCodeBlockInTree;
	#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_BLOCKS_FOR_PARENT_INITIALISATION_SPECIAL	//CHECKTHIS
	*currentCodeBlockInTree = createCodeBlockForCategoryList(*currentCodeBlockInTree, entity, NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION);
	#else
	*currentCodeBlockInTree = createCodeBlockForLocalList(*currentCodeBlockInTree, entity);
	#endif
	
	bool addObject = false;
	//a ball that has a car...
	if(generateObjectInitialisationsForConnectionType(currentCodeBlockInTree, GIA_ENTITY_VECTOR_CONNECTION_TYPE_PROPERTIES, entity, sentenceIndex))
	{
		addObject = true;
	}
	//a ball which is near a car
	if(generateObjectInitialisationsForConnectionType(currentCodeBlockInTree, GIA_ENTITY_VECTOR_CONNECTION_TYPE_CONDITIONS, entity, sentenceIndex))
	{
		addObject = true;
	}
	#ifdef NLC_RECORD_ACTION_HISTORY
	//a ball which drives a car...
	if(generateObjectInitialisationsForConnectionType(currentCodeBlockInTree, GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTIONS, entity, sentenceIndex))
	{
		addObject = true;
	}
	//a ball which is driven by a car
	if(generateObjectInitialisationsForConnectionType(currentCodeBlockInTree, GIA_ENTITY_VECTOR_CONNECTION_TYPE_INCOMING_ACTIONS, entity, sentenceIndex))
	{
		addObject = true;
	}
	#endif
	#ifdef NLC_SUPPORT_REDEFINITIONS
	//a ball which is a car
	if(generateObjectInitialisationsForConnectionType(currentCodeBlockInTree, GIA_ENTITY_VECTOR_CONNECTION_TYPE_DEFINITIONS, entity, sentenceIndex))
	{
		addObject = true;
	}	
	#endif
	
	if(!addObject)
	{
		*currentCodeBlockInTree = clearCodeBlock(codeBlockInTreeBeforeGenerateObjectInitialisations);
	}
	
	*currentCodeBlockInTree = getLastCodeBlockInLevel(codeBlockInTreeBeforeGenerateParentInitialisation);
	
	return result;
}
	
bool generateObjectInitialisationsForConnectionType(NLCcodeblock** currentCodeBlockInTree, int connectionType, GIAentityNode* entity, int sentenceIndex)
{
	bool result = false;
	for(vector<GIAentityConnection*>::iterator targetNodeListIterator = entity->entityVectorConnectionsArray[connectionType].begin(); targetNodeListIterator < entity->entityVectorConnectionsArray[connectionType].end(); targetNodeListIterator++)
	{
		GIAentityConnection* targetConnection = *targetNodeListIterator;
		GIAentityNode* targetEntity = targetConnection->entity;
		if(checkSentenceIndexParsingCodeBlocks(targetEntity, targetConnection, sentenceIndex, false))
		{
			if(targetConnection->sameReferenceSet)
			{
				if(!(targetEntity->NLCcontextGeneratedTemp))
				{
					bool addObject = false;
					GIAentityNode* actionOrConditionEntity = NULL;
					GIAentityNode* objectEntity = NULL;
					GIAentityNode* subjectEntity = NULL;
					bool foundObject = false;
					bool foundSubject = false;
					bool recurse = false;
					GIAentityNode* recurseEntity = NULL;
					if(connectionType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_PROPERTIES)
					{
						//foundSubject = true;
						foundObject = true;
						subjectEntity = entity;
						objectEntity = targetEntity;
						recurse = true;
						recurseEntity = targetEntity;
						//cout << "GIA_ENTITY_VECTOR_CONNECTION_TYPE_PROPERTIES; targetEntity = " << targetEntity->entityName << endl;
						addObject = true;

					}
					else if(connectionType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_CONDITIONS)
					{
						GIAentityConnection* conditionObjectConnection = NULL;
						if(getConditionObjectCheckSameReferenceSetAndSentence(targetEntity, &objectEntity, &conditionObjectConnection, sentenceIndex, true))
						{
							foundSubject = true;
							subjectEntity = entity;
							actionOrConditionEntity = targetEntity;

							foundObject = true;
							recurse = true;
							recurseEntity = objectEntity;

							addObject = true;
						}
					}
					#ifdef NLC_RECORD_ACTION_HISTORY
					else if(connectionType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTIONS)
					{
						//foundSubject = true;
						subjectEntity = entity;
						actionOrConditionEntity = targetEntity;
						GIAentityConnection* actionObjectConnection = NULL;
						if(getActionObjectCheckSameReferenceSetAndSentence(targetEntity, &objectEntity, &actionObjectConnection, sentenceIndex, true))
						{
							foundObject = true;
							recurse = true;
							recurseEntity = objectEntity;
						}
						addObject = true;
					}
					else if(connectionType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_INCOMING_ACTIONS)
					{
						//foundObject = true;
						objectEntity = entity;
						actionOrConditionEntity = targetEntity;
						GIAentityConnection* actionSubjectConnection = NULL;
						if(getActionSubjectCheckSameReferenceSetAndSentence(targetEntity, &subjectEntity, &actionSubjectConnection, sentenceIndex, true))
						{
							foundSubject = true;
							recurse = true;
							recurseEntity = subjectEntity;
						}
						addObject = true;
					}
					#endif
					#ifdef NLC_TRANSLATOR_GENERATE_CONTEXT_BLOCKS_PARSE_DEFINITIONS
					else if(connectionType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_DEFINITIONS)
					{	
						//foundSubject = true;
						foundObject = true;
						subjectEntity = entity;
						objectEntity = targetEntity;
						recurse = false;
						addObject = true;
					}
					#endif

					//targetEntity->NLCparsedForCodeBlocks = true;
					if((connectionType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTIONS) || (connectionType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_INCOMING_ACTIONS))
					{
						//initialise the action
						if(generateObjectInitialisations(currentCodeBlockInTree, actionOrConditionEntity, sentenceIndex))	//subset of initialiseFunctionArguments()
						{

						}
					}

					if(recurse)
					{
						//cout << "recurse; connectionType = " << entityVectorConnectionNameArray[connectionType] << endl;

						NLCgenerateContextBlocksVariables generateContextBlocksVariables;
						generateContextBlocksVariables.getParentCheckLastParent = true;
						generateContextBlocksVariables.lastParent = entity;
						if((connectionType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTIONS) || (connectionType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_INCOMING_ACTIONS))
						{
							actionOrConditionEntity->NLCcontextGeneratedTemp = true;	//prevent actionEntity from being parsed by getParentAndInitialiseParentIfNecessaryOrGenerateContextBlocks:generateContextBlocks;
						}
						//cout << "actionOrConditionEntity->NLCcontextGeneratedTemp = " << actionOrConditionEntity->entityName << endl;

						GIAentityNode* recurseEntityParent = NULL;
						bool newInitialisation = false;
						if(getParentAndInitialiseParentIfNecessaryOrGenerateContextBlocks(currentCodeBlockInTree, recurseEntity, sentenceIndex, &generateContextBlocksVariables, false, &recurseEntityParent, &newInitialisation, false))
						{
							//*currentCodeBlockInTree = createCodeBlockAddEntityToCategoryListCheckLastSentenceReferencedPluralExecuteFunction(*currentCodeBlockInTree, recurseEntity, recurseEntity, NLC_ITEM_TYPE_RECURSEENTITYCATEGORY_VAR_APPENDITION);
						}
						/*NO:	
						if(generateObjectInitialisations(currentCodeBlockInTree, recurseEntity, sentenceIndex))
						{

						}
						*/
					}

					if((connectionType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTIONS) || (connectionType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_INCOMING_ACTIONS))
					{
						actionOrConditionEntity->NLCcontextGeneratedTemp = false;	//redundant
					}

					if(addObject)
					{
						//cout << "addObject; connectionType = " << entityVectorConnectionNameArray[connectionType] << endl;

						result = true;
						bool isPrimary = false;
						if(!generateCodeBlocksAddConnection(currentCodeBlockInTree, connectionType, targetConnection, subjectEntity, objectEntity, actionOrConditionEntity, foundSubject, foundObject, sentenceIndex, NULL, isPrimary))
						{

						}
					}
				}
			}
		}
	}
	
	return result;
}

bool generateCodeBlocksAddConnection(NLCcodeblock** currentCodeBlockInTree, int connectionType, GIAentityConnection* connection, GIAentityNode* subjectEntity, GIAentityNode* objectEntity, GIAentityNode* actionOrConditionEntity, bool foundSubject, bool foundObject, int sentenceIndex, GIAentityNode* subjectParentEntity, bool primary)
{
	bool result = false;

	NLCcodeblock* codeBlockInTreeBeforeParseContext = *currentCodeBlockInTree;
	
	if(connectionType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTIONS)
	{
		result = true;
		GIAentityNode* actionEntity = actionOrConditionEntity;
		if(foundSubject)
		{
			if(primary)
			{
				*currentCodeBlockInTree = createCodeBlockForCategoryList(*currentCodeBlockInTree, subjectEntity, NLC_ITEM_TYPE_SUBJECTCATEGORY_VAR_APPENDITION);
			}
			#ifdef NLC_RECORD_ACTION_HISTORY
			*currentCodeBlockInTree = createCodeBlockRecordHistoryActionSubject(*currentCodeBlockInTree, actionEntity, subjectEntity);
			#endif	
		}
		*currentCodeBlockInTree = getLastCodeBlockInLevel(codeBlockInTreeBeforeParseContext);
		if(foundObject)
		{
			if(primary)
			{
				*currentCodeBlockInTree = createCodeBlockForCategoryList(*currentCodeBlockInTree, objectEntity, NLC_ITEM_TYPE_OBJECTCATEGORY_VAR_APPENDITION);
			}
			#ifdef NLC_RECORD_ACTION_HISTORY
			*currentCodeBlockInTree = createCodeBlockRecordHistoryActionObject(*currentCodeBlockInTree, actionEntity, objectEntity);
			#endif
			#ifdef NLC_USE_LIBRARY_FROM_CONDITIONS
			if(objectParentEntity != objectEntity)
			{
				//*currentCodeBlockInTree = createCodeBlockSetTempVariable(*currentCodeBlockInTree, NLC_USE_LIBRARY_MOVE_FUNCTION_ACTIONOBJECT_PARENT_TEMP_VARIABLE_NAME, parentEntityFunctionObject);
				GIAentityNode* parentEntityFromCondition = new GIAentityNode();
				parentEntityFromCondition->entityName = NLC_USE_LIBRARY_MOVE_FUNCTION_ACTION_CONDITION_FROM_NAME;
				addOrConnectConditionToEntity(actionEntity, parentEntityFunctionObject, parentEntityFromCondition, false);	//this is required so that generateClassHeirarchyFunctions() adds the "from" condition to the action, but need to check that GIA supports NLC's use of the addOrConnectConditionToEntity() function
				*currentCodeBlockInTree = createCodeBlockAddConditionSimple(*currentCodeBlockInTree, actionEntity, parentEntityFromCondition, parentEntityFunctionObject);
			}
			#endif
		}
		*currentCodeBlockInTree = getLastCodeBlockInLevel(codeBlockInTreeBeforeParseContext);
		
		if(primary)
		{
			#ifdef NLC_RECORD_ACTION_HISTORY_GENERALISABLE_DO_NOT_EXECUTE_PAST_TENSE_ACTIONS
			if(!isNonImmediateAction(actionEntity))
			{
			#endif
				#ifndef NLC_FUNCTIONS_SUPPORT_PLURAL_OBJECTS
				if(foundSubject)
				{
					*currentCodeBlockInTree = createCodeBlockForCategoryList(*currentCodeBlockInTree, subjectEntity, NLC_ITEM_TYPE_SUBJECTCATEGORY_VAR_APPENDITION);
				}	
				if(foundObject)
				{
					*currentCodeBlockInTree = createCodeBlockForCategoryList(*currentCodeBlockInTree, objectEntity, NLC_ITEM_TYPE_OBJECTCATEGORY_VAR_APPENDITION);
				}
				#endif

				if(foundSubject && foundObject)
				{
					*currentCodeBlockInTree = createCodeBlockExecuteSubjectObject(*currentCodeBlockInTree, actionEntity, subjectEntity, objectEntity);
				}	
				else if(foundSubject)
				{
					*currentCodeBlockInTree = createCodeBlockExecuteSubject(*currentCodeBlockInTree, actionEntity, subjectEntity);
				}	
				else if(foundObject)
				{
					*currentCodeBlockInTree = createCodeBlockExecuteObject(*currentCodeBlockInTree, actionEntity, objectEntity);
				}			
				else
				{
					*currentCodeBlockInTree = createCodeBlockExecute(*currentCodeBlockInTree, actionEntity);
				}
			#ifdef NLC_RECORD_ACTION_HISTORY_GENERALISABLE_DO_NOT_EXECUTE_PAST_TENSE_ACTIONS	
			}
			#endif	
		}
	}
	else
	{
		if(primary)
		{
			if(foundSubject)
			{
				*currentCodeBlockInTree = createCodeBlockForCategoryList(*currentCodeBlockInTree, subjectEntity, NLC_ITEM_TYPE_SUBJECTCATEGORY_VAR_APPENDITION);
			}	
			if(foundObject)
			{
				*currentCodeBlockInTree = createCodeBlockForCategoryList(*currentCodeBlockInTree, objectEntity, NLC_ITEM_TYPE_OBJECTCATEGORY_VAR_APPENDITION);
			}
		}
		
		if(connectionType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_PROPERTIES)
		{
			GIAentityNode* propertyEntity = objectEntity;

			result = true;
			#ifdef NLC_TRANSLATE_NEGATIVE_PROPERTIES_AND_CONDITIONS
			if(connection->negative || (propertyEntity->isSubstanceQuality && propertyEntity->negative))
			{
				if(isDefiniteEntity(propertyEntity))	//added 1p1b - CHECKTHIS
				{
					//remove property link; eg "the ball" in "Tom does not have the ball."
					#ifdef NLC_DEBUG_PARSE_CONTEXT2
					*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("generateCodeBlocksPart3subjectObjectConnections{}: createCodeBlockRemoveProperty: ") + subjectEntity->entityName + string(" ") + propertyEntity->entityName);
					#endif
					#ifdef NLC_DEBUG
					cout << "createCodeBlockRemoveProperty: " << subjectEntity->entityName << ", " << propertyEntity->entityName << endl;
					#endif
					*currentCodeBlockInTree = createCodeBlockRemoveProperty(*currentCodeBlockInTree, subjectEntity, propertyEntity);
				}
				else
				{
					//remove property links; eg "a ball" in "Tom does not have a ball."
					#ifdef NLC_DEBUG_PARSE_CONTEXT2
					*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("generateCodeBlocksPart3subjectObjectConnections{}: createCodeBlockRemoveProperties: ") + subjectEntity->entityName + string(" ") + propertyEntity->entityName);
					#endif
					#ifdef NLC_DEBUG
					cout << "createCodeBlockRemoveProperties: " << subjectEntity->entityName << ", " << propertyEntity->entityName << endl;
					#endif
					*currentCodeBlockInTree = createCodeBlockRemoveProperties(*currentCodeBlockInTree, subjectEntity, propertyEntity);
				}
			}
			else
			{
			#endif
				//add property links; eg "the ball" in "Tom has a/the ball"
				#ifdef NLC_DEBUG_PARSE_CONTEXT2
				*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("generateCodeBlocksPart3subjectObjectConnections{}: createCodeBlockAddProperty: ") + subjectEntity->entityName + string(" ") + propertyEntity->entityName);
				#endif
				#ifdef NLC_DEBUG
				cout << "createCodeBlockAddProperty: " << subjectEntity->entityName << ", " << propertyEntity->entityName << endl;
				#endif
				*currentCodeBlockInTree = createCodeBlockAddProperty(*currentCodeBlockInTree, subjectEntity, propertyEntity, sentenceIndex);
			#ifdef NLC_TRANSLATE_NEGATIVE_PROPERTIES_AND_CONDITIONS
			}
			#endif				
		}
		else if(connectionType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_CONDITIONS)
		{
			result = true;
			GIAentityNode* conditionEntity = actionOrConditionEntity;
			GIAentityNode* conditionObject = NULL;
			if(!(conditionEntity->conditionObjectEntity->empty()))
			{		
				conditionObject = (conditionEntity->conditionObjectEntity->back())->entity;
			}
			
			#ifdef NLC_TRANSLATE_NEGATIVE_PROPERTIES_AND_CONDITIONS
			if(conditionEntity->negative)
			{
				if(isDefiniteEntity(conditionObject))	//added 1p1b - CHECKTHIS
				{
					//remove condition link; eg "a house" in "Tom is not near the house"
					#ifdef NLC_DEBUG_PARSE_CONTEXT2
					*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("generateCodeBlocksPart3subjectObjectConnections{}: createCodeBlockRemoveCondition: ") + subjectEntity->entityName + string(" ") + conditionEntity->entityName);
					#endif
					*currentCodeBlockInTree = createCodeBlockRemoveCondition(*currentCodeBlockInTree, subjectEntity, conditionEntity);
				}
				else
				{
					//remove condition links; eg "a house" in "Tom is not near a house"
					#ifdef NLC_DEBUG_PARSE_CONTEXT2
					*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("generateCodeBlocksPart3subjectObjectConnections{}: createCodeBlockRemoveConditions: ") + subjectEntity->entityName + string(" ") + conditionEntity->entityName);
					#endif
					*currentCodeBlockInTree = createCodeBlockRemoveConditions(*currentCodeBlockInTree, subjectEntity, conditionEntity);
				}
			}
			else
			{
			#endif
				//add condition links; eg "the house" in "Tom is near a/the house"
				#ifdef NLC_DEBUG_PARSE_CONTEXT2
				*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("generateObjectInitialisationsBasedOnPropertiesAndConditions{}: createCodeBlockAddCondition: ") + subjectEntity->entityName + string(" ") + conditionObject->entityName);
				#endif
				*currentCodeBlockInTree = createCodeBlockAddCondition(*currentCodeBlockInTree, subjectEntity, conditionEntity, sentenceIndex);
			#ifdef NLC_TRANSLATE_NEGATIVE_PROPERTIES_AND_CONDITIONS
			}
			#endif
		}
		else if(connectionType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_DEFINITIONS)
		{
			GIAentityNode* definitionEntity = objectEntity;

			#ifdef NLC_USE_MATH_OBJECTS
			if(isStringNumberOrFractional(definitionEntity->entityName)) 
			{
				//eg The value is 5.5
				//cout << "NLC_USE_MATH_OBJECTS: generateCodeBlocksAddConnection{} found value = " << definitionEntity->entityName << endl;
				*currentCodeBlockInTree = createCodeBlockSetMathValue(*currentCodeBlockInTree, subjectEntity, definitionEntity);
			}
			else
			{
			#endif
				#ifdef NLC_USE_ADVANCED_REFERENCING_SUPPORT_ALIASES
				if(connection->isAlias)
				{
					result = true;
					bool aliasAlreadyInitialised = false;
					string aliasName = definitionEntity->entityName;
					string aliasClassName = subjectEntity->entityName;

					string aliasNameTemp = "";
					if(findAliasInEntity(definitionEntity, &aliasNameTemp)) //*
					{
						aliasAlreadyInitialised = true;
					}
					if(!aliasAlreadyInitialised)
					{	
						//check this code
						#ifdef NLC_DEBUG_ADVANCED_REFERENCING_SUPPORT_ALIASES
						cout << "generateCodeBlocksPart3subjectObjectConnections (alias):" << endl;
						cout << "definitionEntity (aliasName) = " << definitionEntity->entityName << endl;
						cout << "subjectEntity (aliasClassName) = " << subjectEntity->entityName << endl;
						#endif

						NLCcodeblock* firstCodeBlockInSentence = *currentCodeBlockInTree;
						GIAentityNode* parentEntity = NULL;

						*currentCodeBlockInTree = createCodeBlocksAddAliasToEntityAliasList(*currentCodeBlockInTree, subjectEntity, aliasName);

						//1k14c; replace all alias GIA entities with their respective class (eg dog), and add an alias to their vector list (eg Tom)
						GIAentityNode* aliasConceptEntity = getPrimaryConceptNodeDefiningInstance(definitionEntity);
						for(vector<GIAentityConnection*>::iterator iter2 = aliasConceptEntity->associatedInstanceNodeList->begin(); iter2 < aliasConceptEntity->associatedInstanceNodeList->end(); iter2++)
						{
							GIAentityNode* entity2 = (*iter2)->entity;
							if(entity2->entityName == aliasName)
							{
								if(entity2->sentenceIndexTemp > definitionEntity->sentenceIndexTemp)	//this test isn't required because of* 
								{
									entity2->aliasList.push_back(aliasName);
									entity2->entityName = aliasClassName;	
								}
							}
						}

						definitionEntity->NLCisAlias = true; //added 1o1b (prevents addition of alias to class heirachy)	
					}
				}
				else
				{
				#endif
					//eg [Alsations are dogs. The pound has a dog. The dog is happy.] The dog is an alsation.  ; converts dog to alsation

					#ifndef NLC_SUPPORT_REDEFINITIONS_FOR_IMMEDIATELY_DECLARED_INDEFINITE_ENTITIES
					//eg chickens are animals. an animal is a chicken. In practice this will not be implemented because GIA interprets indefinite-indefinite definitions as substance concepts. redefinitions are generally not implied for indefinite children (eg "an animal" in "an animal is a chicken") because they are ambiguous; this example either means a) animals are chickens (ie is a substanceConcept-substanceConcept definition; not a redefinition - and happens to be an incorrect statement based on aprior knowledge about the animal kingdom because we know chickens are animals not vice versa), or b) a newly declared animal is cast to a chicken (a specific version of animal, assuming "chickens are animals" has been declared)
					if(!isDefiniteEntity(definitionEntity))
					{
						bool foundDefiniteParentOfEntity = false;
						bool parseConditionParents = NLC_PARSE_CONDITION_PARENTS_DEFAULT_VALUE;
						bool checkIsDefinite = true;
						GIAentityNode* parentEntity = getSameReferenceSetUniqueParent(subjectEntity, sentenceIndex, NULL, &foundDefiniteParentOfEntity, parseConditionParents, checkIsDefinite);
						if(isDefiniteEntity(subjectEntity) || foundDefiniteParentOfEntity)
						{
					#endif
							if(subjectEntity->entityName != definitionEntity->entityName)
							{//ignore substanceConcept definitions for for entities of same name

								result = true;
								#ifdef NLC_DEBUG
								cout << "generateCodeBlocksPart5redefinitions (definition):" << endl;
								cout << "sentenceIndex = " << sentenceIndex << endl;
								cout << "subjectEntity = " << subjectEntity->entityName << endl;
								cout << "definitionEntity = " << definitionEntity->entityName << endl;
								#endif

								NLCcodeblock* firstCodeBlockInSentence = *currentCodeBlockInTree;

								GIAentityNode* parentEntity = NULL;

								//1. and 2. get parent of the dog (eg pound) and generate context of the dog (already done)
								//generateContextBlocksVariables.searchSubstanceConceptsForChildren = false;	//added 1n5g (only check the explicit variable for definition; do not parse categories) - CHECKTHIS

								//3. verify that alsations are dogs
								*currentCodeBlockInTree = createCodeBlockCheckParentClassNameExecuteFunction2(*currentCodeBlockInTree, definitionEntity, subjectEntity->entityName);

								//4. cast the dog to alsation
								*currentCodeBlockInTree = createCodeConvertParentToChildClass(*currentCodeBlockInTree, subjectEntity, definitionEntity);

								//5. add alsation to alsation property list of pound 
									//LIMITATION: NB the dog will still be added to the dog property list of pound; therefore these must remain synced; ie the dog or the alsation cannot be deleted from the pound...
									//to avoid this limitation at present the user must define an object by its most specific class initially (avoiding redefinitions). NLC will automatically search for references to the child based on substance concept definition link to its parent [dream mode has connected substance concept definiton links to all instantations thereof]
								if(subjectParentEntity != subjectEntity)
								{
									*currentCodeBlockInTree =  createCodeBlockAddProperty(*currentCodeBlockInTree, subjectParentEntity, definitionEntity, sentenceIndex);
								}

								//6. add alsation to alsation local list
								*currentCodeBlockInTree =  createCodeBlockAddEntityToLocalList(*currentCodeBlockInTree, definitionEntity, definitionEntity);

								/*
								#ifdef GIA_TRANSLATOR_DREAM_MODE_LINK_SPECIFIC_CONCEPTS_AND_ACTIONS
								//7. generate object initialisations based on substance concepts (class inheritance)
								generateObjectInitialisationsBasedOnSubstanceConcepts(definitionEntity, currentCodeBlockInTree, sentenceIndex, true);
								#endif
								*/							

							}
					#ifndef NLC_SUPPORT_REDEFINITIONS_FOR_IMMEDIATELY_DECLARED_INDEFINITE_ENTITIES
						}
						else
						{
							cout << "checkIfPhraseContainsSubstanceWithDefinitionLink() warning: !(isDefiniteEntity(subjectEntity) || foundDefiniteParentOfEntity))" << endl;
						}
					}
					else
					{
						cout << "checkIfPhraseContainsSubstanceWithDefinitionLink() warning: isDefiniteEntity(definitionEntity))" << endl;
					}
					#endif
				#ifdef NLC_USE_ADVANCED_REFERENCING_SUPPORT_ALIASES						
				}
				#endif
			#ifdef NLC_USE_MATH_OBJECTS						
			}
			#endif				
		}
	}
	return result;
}


#ifdef NLC_RECORD_ACTION_HISTORY_GENERALISABLE_DO_NOT_EXECUTE_PAST_TENSE_ACTIONS
bool isNonImmediateAction(GIAentityNode* actionEntity)
{
	//updated 1m2a
	bool isNonImmediateAction = false;
	if(actionEntity->grammaticalTenseModifierArrayTemp[GRAMMATICAL_TENSE_MODIFIER_STATE] == true)
	{
		isNonImmediateAction = true;
	}
	else if(actionEntity->grammaticalTenseModifierArrayTemp[GRAMMATICAL_TENSE_MODIFIER_POTENTIAL] == true)	//redundant, as this is already filtered by isPotentialAction()
	{
		isNonImmediateAction = true;
	}
	else if(actionEntity->grammaticalTenseModifierArrayTemp[GRAMMATICAL_TENSE_MODIFIER_PROGRESSIVE] == true)
	{
		isNonImmediateAction = true;
	}
	else if(actionEntity->grammaticalTenseModifierArrayTemp[GRAMMATICAL_TENSE_MODIFIER_PASSIVE] == true)	//added 1n8a
	{
		isNonImmediateAction = true;
	}
	//CHECKTHIS; check GRAMMATICAL_TENSE_MODIFIER_INFINITIVE is being generated correctly (ie is being correctly distinguished from VBP/present not third person singular) - otherwise isNonImmediateAction will have to check for GRAMMATICAL_TENSE_MODIFIER_INFINITIVE also
		
	if(actionEntity->timeConditionNode != NULL)
	{
		GIAtimeConditionNode* timeCondition = actionEntity->timeConditionNode;
		if(timeCondition->tense == GRAMMATICAL_TENSE_PAST)
		{
			isNonImmediateAction = true;
		}
	}
	return isNonImmediateAction;
}

bool isPotentialAction(GIAentityNode* actionEntity)
{
	//updated 1m2a
	bool isPotentialAction = false;
	if(actionEntity->grammaticalTenseModifierArrayTemp[GRAMMATICAL_TENSE_MODIFIER_POTENTIAL] == true)
	{
		isPotentialAction = true;
	}
	return isPotentialAction;
}
#endif

bool getActionSubjectCheckSameReferenceSetAndSentence(GIAentityNode* actionEntity, GIAentityNode** subjectEntity, GIAentityConnection** actionSubjectConnection, int sentenceIndex, bool sameReferenceSet)
{
	bool foundSubject = false;
	if(getActionSubjectEntityConnection(actionEntity, sentenceIndex, actionSubjectConnection))
	{
		if((*actionSubjectConnection)->sameReferenceSet == sameReferenceSet)
		{		
			*subjectEntity = (*actionSubjectConnection)->entity;
			if(checkSentenceIndexParsingCodeBlocks(*subjectEntity, *actionSubjectConnection, sentenceIndex, false))
			{
				foundSubject = true;	
			}
		}
	}
	return foundSubject;
}

bool getActionSubjectEntityConnection(GIAentityNode* actionEntity, int sentenceIndex, GIAentityConnection** actionSubjectConnection)
{
	bool actionHasSubject = false;
	#ifdef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES	//&& #defined NLC_RECORD_ACTION_HISTORY_GENERALISABLE
	//required because GIA advanced referencing may connect a given action to multiple subjects/objects (ie across multiple sentences)
	for(vector<GIAentityConnection*>::iterator iter = actionEntity->actionSubjectEntity->begin(); iter < actionEntity->actionSubjectEntity->end(); iter++)
	{
		GIAentityConnection* actionSubjectConnectionTemp = *iter;
		if(actionSubjectConnectionTemp->sentenceIndexTemp == sentenceIndex)
		{
			#ifdef NLC_DEBUG
			//cout << "getActionSubjectEntityConnection{}: actionSubjectConnectionTemp->sentenceIndexTemp = " << actionSubjectConnectionTemp->sentenceIndexTemp << endl;
			#endif
			*actionSubjectConnection = actionSubjectConnectionTemp;
			actionHasSubject = true;	
		}
	}
	#else
	if(!(actionEntity->actionSubjectEntity->empty()))
	{
		*actionSubjectConnection = (actionEntity->actionSubjectEntity->back());
		actionHasSubject = true;
	}	
	#endif
	return actionHasSubject;
}	

bool getActionObjectCheckSameReferenceSetAndSentence(GIAentityNode* actionEntity, GIAentityNode** objectEntity, GIAentityConnection** actionObjectConnection, int sentenceIndex, bool sameReferenceSet)
{	
	bool foundObject = false;
	if(getActionObjectEntityConnection(actionEntity, sentenceIndex, actionObjectConnection))
	{
		if((*actionObjectConnection)->sameReferenceSet == sameReferenceSet)
		{		
			*objectEntity = (*actionObjectConnection)->entity;
			if(checkSentenceIndexParsingCodeBlocks(*objectEntity, *actionObjectConnection, actionEntity->sentenceIndexTemp, false))
			{
				foundObject = true;
			}	
		}
	}
	return foundObject;
}

bool getActionObjectEntityConnection(GIAentityNode* actionEntity, int sentenceIndex, GIAentityConnection** actionObjectConnection)
{
	bool actionHasObject = false;
	#ifdef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES	//&& #defined NLC_RECORD_ACTION_HISTORY_GENERALISABLE
	//required because GIA advanced referencing may connect a given action to multiple subjects/objects across sentences (ie across multiple sentences)
	for(vector<GIAentityConnection*>::iterator iter = actionEntity->actionObjectEntity->begin(); iter < actionEntity->actionObjectEntity->end(); iter++)
	{
		GIAentityConnection* actionObjectConnectionTemp = *iter;
		if(actionObjectConnectionTemp->sentenceIndexTemp == sentenceIndex)
		{	
			#ifdef NLC_DEBUG
			//cout << "getActionObjectEntityConnection{}: actionObjectConnectionTemp->sentenceIndexTemp = " << actionObjectConnectionTemp->sentenceIndexTemp << endl;
			#endif
			*actionObjectConnection = actionObjectConnectionTemp;
			actionHasObject = true;	
		}
	}
	#else
	if(!(actionEntity->actionObjectEntity->empty()))
	{
		*actionObjectConnection = (actionEntity->actionObjectEntity->back());
		actionHasObject = true;
	}	
	#endif
	return actionHasObject;
}


bool getConditionSubjectCheckSameReferenceSetAndSentence(GIAentityNode* conditionEntity, GIAentityNode** subjectEntity, GIAentityConnection** conditionSubjectConnection, int sentenceIndex, bool sameReferenceSet)
{
	bool foundObject = false;
	if(getConditionSubjectEntityConnection(conditionEntity, sentenceIndex, conditionSubjectConnection))
	{
		if((*conditionSubjectConnection)->sameReferenceSet == sameReferenceSet)
		{		
			*subjectEntity = (*conditionSubjectConnection)->entity;
			#ifdef NLC_NORMALISE_TWOWAY_PREPOSITIONS_DUAL_CONDITION_LINKS_ENABLED
			if(!(conditionEntity->inverseConditionTwoWay) || (*conditionSubjectConnection)->isReference)	//prevent infinite loop for 2 way conditions 
			{
			#endif
				if(checkSentenceIndexParsingCodeBlocks(*subjectEntity, *conditionSubjectConnection, sentenceIndex, false))
				{
					foundObject = true;	
				}
			#ifdef NLC_NORMALISE_TWOWAY_PREPOSITIONS_DUAL_CONDITION_LINKS_ENABLED
			}
			#endif
		}
	}
	return foundObject;
}

bool getConditionSubjectEntityConnection(GIAentityNode* conditionEntity, int sentenceIndex, GIAentityConnection** conditionSubjectConnection)
{
	bool conditionHasSubject = false;
	#ifdef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES	//&& #defined NLC_RECORD_ACTION_HISTORY_GENERALISABLE
	//required because GIA advanced referencing may connect a given action to multiple subjects/objects across sentences (ie across multiple sentences)
	for(vector<GIAentityConnection*>::iterator iter = conditionEntity->conditionSubjectEntity->begin(); iter < conditionEntity->conditionSubjectEntity->end(); iter++)
	{
		GIAentityConnection* conditionSubjectConnectionTemp = *iter;
		if(conditionSubjectConnectionTemp->sentenceIndexTemp == sentenceIndex)
		{	
			#ifdef NLC_DEBUG
			//cout << "getActionSubjectEntityConnection{}: conditionSubjectConnectionTemp->sentenceIndexTemp = " << conditionSubjectConnectionTemp->sentenceIndexTemp << endl;
			#endif
			*conditionSubjectConnection = conditionSubjectConnectionTemp;
			conditionHasSubject = true;	
		}
	}
	#else
	if(!(conditionEntity->conditionSubjectEntity->empty()))
	{
		*conditionSubjectConnection = (conditionEntity->conditionSubjectEntity->back());
		conditionHasSubject = true;
	}	
	#endif
	return conditionHasSubject;
}

bool getConditionObjectCheckSameReferenceSetAndSentence(GIAentityNode* conditionEntity, GIAentityNode** objectEntity, GIAentityConnection** conditionObjectConnection, int sentenceIndex, bool sameReferenceSet)
{
	bool foundObject = false;
	if(getConditionObjectEntityConnection(conditionEntity, sentenceIndex, conditionObjectConnection))
	{
		if((*conditionObjectConnection)->sameReferenceSet == sameReferenceSet)
		{		
			*objectEntity = (*conditionObjectConnection)->entity;
			#ifdef NLC_NORMALISE_TWOWAY_PREPOSITIONS_DUAL_CONDITION_LINKS_ENABLED
			if(!(conditionEntity->inverseConditionTwoWay) || (*conditionObjectConnection)->isReference)	//prevent infinite loop for 2 way conditions 
			{
			#endif
				if(checkSentenceIndexParsingCodeBlocks(*objectEntity, *conditionObjectConnection, sentenceIndex, false))
				{
					foundObject = true;	
				}
			#ifdef NLC_NORMALISE_TWOWAY_PREPOSITIONS_DUAL_CONDITION_LINKS_ENABLED
			}
			#endif
		}
	}
	return foundObject;
}

bool getConditionObjectEntityConnection(GIAentityNode* conditionEntity, int sentenceIndex, GIAentityConnection** conditionObjectConnection)
{
	bool conditionHasObject = false;
	#ifdef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES	//&& #defined NLC_RECORD_ACTION_HISTORY_GENERALISABLE
	//required because GIA advanced referencing may connect a given action to multiple subjects/objects across sentences (ie across multiple sentences)
	for(vector<GIAentityConnection*>::iterator iter = conditionEntity->conditionObjectEntity->begin(); iter < conditionEntity->conditionObjectEntity->end(); iter++)
	{
		GIAentityConnection* conditionObjectConnectionTemp = *iter;
		if(conditionObjectConnectionTemp->sentenceIndexTemp == sentenceIndex)
		{	
			#ifdef NLC_DEBUG
			//cout << "getActionObjectEntityConnection{}: conditionObjectConnectionTemp->sentenceIndexTemp = " << conditionObjectConnectionTemp->sentenceIndexTemp << endl;
			#endif
			*conditionObjectConnection = conditionObjectConnectionTemp;
			conditionHasObject = true;	
		}
	}
	#else
	if(!(conditionEntity->conditionObjectEntity->empty()))
	{
		*conditionObjectConnection = (conditionEntity->conditionObjectEntity->back());
		conditionHasObject = true;
	}	
	#endif
	return conditionHasObject;
}










GIAentityNode* getParent(GIAentityNode* currentEntity, int sentenceIndex)
{
	NLCgenerateContextBlocksVariables generateContextBlocksVariables;
	return getParent(currentEntity, sentenceIndex, &generateContextBlocksVariables);
}

GIAentityNode* getParent(GIAentityNode* currentEntity, int sentenceIndex, NLCgenerateContextBlocksVariables* generateContextBlocksVariables)
{	 
	GIAentityNode* parentEntityNew = currentEntity;
						
	bool foundParentProperty = false;
	for(vector<GIAentityConnection*>::iterator propertyNodeListIterator = currentEntity->propertyNodeReverseList->begin(); propertyNodeListIterator < currentEntity->propertyNodeReverseList->end(); propertyNodeListIterator++)
	{
		GIAentityConnection* propertyConnection = *propertyNodeListIterator;
		GIAentityNode* parentEntity = propertyConnection->entity;

		#ifdef NLC_DEFINE_LOCAL_VARIABLES_FOR_ALL_INDEFINATE_ENTITIES
		if(checkSentenceIndexParsingCodeBlocks(parentEntity, propertyConnection, sentenceIndex, false))	//NB will parse references to entities in previous sentence
		#else
		if(checkSentenceIndexParsingCodeBlocks(parentEntity, propertyConnection, sentenceIndex, false) || parentEntity->NLCparsedForCodeBlocks)
		#endif
		{
			if(!(generateContextBlocksVariables->getParentCheckLastParent) || (parentEntity != generateContextBlocksVariables->lastParent))
			{
				parentEntityNew = getParent(parentEntity, sentenceIndex, generateContextBlocksVariables);
				foundParentProperty = true;
			}
		}
	}
	#ifdef NLC_PARSE_CONDITION_PARENTS
	if(!foundParentProperty && generateContextBlocksVariables->parseConditionParents)
	{//added 1e9a
		for(vector<GIAentityConnection*>::iterator conditionNodeListIterator = currentEntity->incomingConditionNodeList->begin(); conditionNodeListIterator < currentEntity->incomingConditionNodeList->end(); conditionNodeListIterator++)
		{
			GIAentityConnection* conditionConnection = *conditionNodeListIterator;
			GIAentityNode* conditionEntity = conditionConnection->entity;
			//cout << "conditionEntity = " << conditionEntity->entityName << endl;

			#ifdef NLC_NORMALISE_TWOWAY_PREPOSITIONS_DUAL_CONDITION_LINKS_ENABLED
			if(!(conditionEntity->inverseConditionTwoWay) || conditionConnection->isReference)	//prevent infinite loop for 2 way conditions 
			{
			#endif
				#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
				if(checkConditionLogicalConditionAdvancedTests(conditionEntity))
				{
				#endif
					bool foundConditionSubject = false;
					GIAentityNode* conditionSubject = NULL;
					if(!(conditionEntity->conditionSubjectEntity->empty()))
					{
						conditionSubject = (conditionEntity->conditionSubjectEntity->back())->entity;
						//cout << "conditionSubject = " << conditionSubject->entityName << endl;

						foundConditionSubject = true;

						#ifdef NLC_DEFINE_LOCAL_VARIABLES_FOR_ALL_INDEFINATE_ENTITIES
						if(checkSentenceIndexParsingCodeBlocks(conditionSubject, conditionConnection, sentenceIndex, false))	//NB will parse references to entities in previous sentence
						#else
						if(checkSentenceIndexParsingCodeBlocks(conditionSubject, conditionConnection, sentenceIndex, false) || conditionSubject->NLCparsedForCodeBlocks)
						#endif
						{
							if(!(generateContextBlocksVariables->getParentCheckLastParent) || (conditionSubject != generateContextBlocksVariables->lastParent))
							{
								//cout << "checkSentenceIndexParsingCodeBlocks conditionSubject pass" << endl;
								parentEntityNew = getParent(conditionSubject, sentenceIndex, generateContextBlocksVariables);
							}
						}
					}		
				#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
				}
				#endif
			#ifdef NLC_NORMALISE_TWOWAY_PREPOSITIONS_DUAL_CONDITION_LINKS_ENABLED
			}
			#endif
		}
	}
	#endif

	return parentEntityNew;
}
								

bool getParentAndGenerateContextBlocks(NLCcodeblock** currentCodeBlockInTree, GIAentityNode* currentEntity, int sentenceIndex, NLCgenerateContextBlocksVariables* generateContextBlocksVariables)
{
	GIAentityNode* parentEntity = getParent(currentEntity, sentenceIndex, generateContextBlocksVariables);

	bool generatedContextBlocks = generateContextBlocks(currentCodeBlockInTree, parentEntity, sentenceIndex, generateContextBlocksVariables, false, NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION);

	return generatedContextBlocks;

}







bool generateContextForChildEntity(NLCcodeblock** currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* childEntity, int sentenceIndex, bool topLevel)
{	
	#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_FOR_EACH_CHILD
	NLCgenerateContextBlocksVariables generateContextBlocksVariables;
	generateContextBlocksVariables.onlyGenerateContextBlocksIfConnectionsParsedForNLCorSameReferenceSet = true;
	//research context in case, eg "The chicken has the ball which is near the park." (ie when initialisation property is definite; as distinguished from "The chicken has a ball near the park.")	
	bool generatedContextForChild = false;
	#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_FOR_EACH_CHILD_GET_PARENT
	bool foundDefiniteParentEntityNew = false;
	bool parseConditionParents = NLC_PARSE_CONDITION_PARENTS_DEFAULT_VALUE;
	bool checkIsDefinite = true;	//CHECKTHIS
	GIAentityNode* parentEntityNew = getSameReferenceSetUniqueParent(childEntity, sentenceIndex, entity, &foundDefiniteParentEntityNew, parseConditionParents, checkIsDefinite);
	#ifdef NLC_DEBUG_PARSE_CONTEXT4
	string parentEntityName = "";
	if(entity != NULL)
	{
		parentEntityName = entity->entityName;
	}
	*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("generateContextForChildEntity() getSameReferenceSetUniqueParent result; entity: ") + parentEntityName + string(", childEntity: ") + childEntity->entityName + string(", parentEntityNew: ") + parentEntityNew->entityName);
	#endif	
	if(foundDefiniteParentEntityNew)
	{
		//eg Tom has Jack's ball
		#ifdef NLC_DEBUG
		cout << "generateContextForChildEntity{}: foundDefiniteParentEntityNew: childEntity = " << childEntity->entityName << endl;
		#endif
		if(generateContextBlocksForParentEntity(currentCodeBlockInTree, childEntity, parentEntityNew, sentenceIndex, &generateContextBlocksVariables))
		{
			generatedContextForChild = true;
		}
		else
		{
			cout << "generateContextForChildEntity{}: generateContextBlocksForParentEntity{} error: !generatedContextForChild" << endl;
		}
	}
	#endif
	
	if(assumedToAlreadyHaveBeenDeclared(childEntity))
	{
		#ifndef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN
		#ifndef NLC_TRANSLATOR_GENERATE_CONTEXT_BLOCKS_PARSE_PARENT_EFFICIENT
		if(!generatedContextForChild)
		{
		#endif
		#endif
			//eg Tom has the blue ball 
			#ifdef NLC_DEBUG
			cout << "generateContextForChildEntity{}: assumedToAlreadyHaveBeenDeclared: childEntity = " << childEntity->entityName << endl;
			#endif
			#ifdef NLC_DEBUG_PARSE_CONTEXT4
			*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("generateContextForChildEntity{}: assumedToAlreadyHaveBeenDeclared(childEntity): ") + childEntity->entityName);
			#endif
			if(generateContextBlocks(currentCodeBlockInTree, childEntity, sentenceIndex, &generateContextBlocksVariables, generatedContextForChild, NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION))	//pass generatedContextForChild 1j10a
			{
				
			}
			
			generatedContextForChild = true;
			
		#ifndef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN
		#ifndef NLC_TRANSLATOR_GENERATE_CONTEXT_BLOCKS_PARSE_PARENT_EFFICIENT
		}
		#endif
		#endif				
	}
	#ifdef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES	//ie #ifndef NLC_USE_ADVANCED_REFERENCING
	else 
	{
		if(!generatedContextForChild)
		{
			#ifdef NLC_DEBUG
			cout << "generateContextForChildEntity{}: generateContextBasedOnDeclaredParent: childEntity = " << childEntity->entityName << endl;
			#endif
			#ifdef NLC_DEBUG_PARSE_CONTEXT4
			*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("generateContextForChildEntity{}: generateContextBasedOnDeclaredParent(childEntity): ") + childEntity->entityName);
			#endif
			if(generateContextBasedOnDeclaredParent(childEntity, currentCodeBlockInTree, topLevel, entity, sentenceIndex))
			{
				/*for cases in which GIA advanced referencing has referenced entities whose parent was defined in a previous sentence;
				eg 1 Tom's boat is red. The chicken rowed the red boat.
				eg 2 Tom's boat is red. The red boat is new
				NOT: Tom's boat is red. Tom's boat is new
				*/
				generatedContextForChild = true;
				#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_FOR_EACH_CHILD_GET_PARENT_ORIGINAL_IMPLEMENTATION		
				addIntermediaryImplicitlyDeclaredEntityToLocalList(currentCodeBlockInTree, childEntity);
				#endif
				childEntity->NLClocalListVariableHasBeenInitialised = true;	//added 1m4b
			}
		}
	}
	#endif
	#endif
				
	return generatedContextForChild;
}

bool generateContextBlocksForParentEntity(NLCcodeblock** currentCodeBlockInTree, GIAentityNode* childEntity, GIAentityNode* parentEntity, int sentenceIndex, NLCgenerateContextBlocksVariables* generateContextBlocksVariables)
{
	bool result = false;
	
	#ifdef NLC_TRANSLATOR_GENERATE_CONTEXT_BLOCKS_PARSE_PARENT_EFFICIENT
	generateContextBlocksVariables->parseParentEfficient = true;
	generateContextBlocksVariables->childEntityNotToParse = childEntity;
	#endif
	
	#ifdef NLC_DEBUG_PARSE_CONTEXT4
	*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("generateContextBlocksForParentEntity{}: childEntity: ") + childEntity->entityName + string(", parentEntity: ") + parentEntity->entityName);
	#endif
	if(generateContextBlocks(currentCodeBlockInTree, parentEntity, sentenceIndex, generateContextBlocksVariables, false, NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION))		//changed from generateCategories 1i11o
	{
		//eg Tom has Jack's blue ball
		#ifndef NLC_TRANSLATOR_GENERATE_CONTEXT_BLOCKS_PARSE_PARENT_EFFICIENT
		result = true;
		#endif
	}
		
	#ifdef NLC_TRANSLATOR_GENERATE_CONTEXT_BLOCKS_PARSE_PARENT_EFFICIENT
	generateContextBlocksVariables->parseParentEfficient = false;
	generateContextBlocksVariables->childEntityNotToParse = NULL;
	result = true;	//in case parent entity has no independent children (eg "red" in "The chicken's car" vs "The red chicken's car")
	#endif
		
	if(result)
	{
		#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN
		*currentCodeBlockInTree = createCodeBlockForOrInPropertyList(*currentCodeBlockInTree, childEntity, generateInstanceName(parentEntity));	
		#endif

		#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_FOR_EACH_CHILD_GET_PARENT_ORIGINAL_IMPLEMENTATION		
		addIntermediaryImplicitlyDeclaredEntityToLocalList(currentCodeBlockInTree, childEntity);
		#endif
		childEntity->NLClocalListVariableHasBeenInitialised = true;
	}
	
	return result;
}


#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_FOR_EACH_CHILD_GET_PARENT
GIAentityNode* getSameReferenceSetUniqueParent(GIAentityNode* currentEntity, int sentenceIndex, GIAentityNode* generateObjectInitialisationsLastParent, bool* foundParentEntityNew, bool parseConditionParents, bool checkIsDefinite)
{
	*foundParentEntityNew = false;
	GIAentityNode* parentEntityNew = currentEntity;
	bool foundParentProperty = false;

	for(vector<GIAentityConnection*>::iterator propertyNodeListIterator = currentEntity->propertyNodeReverseList->begin(); propertyNodeListIterator < currentEntity->propertyNodeReverseList->end(); propertyNodeListIterator++)
	{
		GIAentityConnection* parentConnection = *propertyNodeListIterator;
		GIAentityNode* parentEntity = parentConnection->entity;
		
		#ifdef NLC_DEFINE_LOCAL_VARIABLES_FOR_ALL_INDEFINATE_ENTITIES
		if(checkSentenceIndexParsingCodeBlocks(parentEntity, parentConnection, sentenceIndex, false))	//NB will parse references to entities in previous sentence
		#else
		if(checkSentenceIndexParsingCodeBlocks(parentEntity, parentConnection, sentenceIndex, false) || parentEntity->NLCparsedForCodeBlocks)
		#endif
		{
			if(parentConnection->sameReferenceSet)
			{
				//removed 1i11e, readded 1i11j
				if(parentEntity != generateObjectInitialisationsLastParent)
				{
					/*
					//added 1i11f, removed 1i11j
					if(!(parentEntity->NLCcontextGenerated))
					{
					*/
					if(isDefiniteEntity(parentEntity) || !checkIsDefinite)
					{
						bool foundParentEntityNewTemp = false;
						parentEntityNew = getSameReferenceSetUniqueParent(parentEntity, sentenceIndex, generateObjectInitialisationsLastParent, &foundParentEntityNewTemp, parseConditionParents, checkIsDefinite);
						*foundParentEntityNew = true;
						foundParentProperty = true;
					}
					/*	
					}
					*/
				}
			}
		}
	}

	#ifdef NLC_PARSE_CONDITION_PARENTS
	if(!foundParentProperty && parseConditionParents)
	{//added 1e9a
		for(vector<GIAentityConnection*>::iterator conditionNodeListIterator = currentEntity->incomingConditionNodeList->begin(); conditionNodeListIterator < currentEntity->incomingConditionNodeList->end(); conditionNodeListIterator++)
		{
			GIAentityConnection* conditionConnection = *conditionNodeListIterator;
			GIAentityNode* conditionEntity = conditionConnection->entity;
			#ifdef NLC_NORMALISE_TWOWAY_PREPOSITIONS_DUAL_CONDITION_LINKS_ENABLED
			if(!(conditionEntity->inverseConditionTwoWay) || conditionConnection->isReference)	//prevent infinite loop for 2 way conditions 
			{
			#endif
				#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
				if(checkConditionLogicalConditionAdvancedTests(conditionEntity))
				{
				#endif
					bool foundConditionSubject = false;
					GIAentityNode* conditionSubject = NULL;
					if(!(conditionEntity->conditionSubjectEntity->empty()))
					{
						conditionSubject = (conditionEntity->conditionSubjectEntity->back())->entity;
						foundConditionSubject = true;

						#ifdef NLC_DEFINE_LOCAL_VARIABLES_FOR_ALL_INDEFINATE_ENTITIES
						if(checkSentenceIndexParsingCodeBlocks(conditionSubject, conditionConnection, sentenceIndex, false))	//NB will parse references to entities in previous sentence
						#else
						if(checkSentenceIndexParsingCodeBlocks(conditionSubject, conditionConnection, sentenceIndex, false) || conditionSubject->NLCparsedForCodeBlocks)
						#endif
						{
							if(conditionConnection->sameReferenceSet)
							{
								//removed 1i11e, readded 1i11j
								if(conditionSubject != generateObjectInitialisationsLastParent)
								{
									if(isDefiniteEntity(conditionSubject) || !checkIsDefinite)
									{
										bool foundParentEntityNewTemp = false;
										parentEntityNew = getSameReferenceSetUniqueParent(conditionSubject, sentenceIndex, generateObjectInitialisationsLastParent, &foundParentEntityNewTemp, parseConditionParents, checkIsDefinite);
										*foundParentEntityNew = true;
									}
								}
							}
						}
					}		
				#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
				}
				#endif
			#ifdef NLC_NORMALISE_TWOWAY_PREPOSITIONS_DUAL_CONDITION_LINKS_ENABLED
			}
			#endif
		}
	}
	#endif
		
	return parentEntityNew;
}
#endif

GIAentityNode* getSameReferenceSetSubstanceNonQualityChild(GIAentityNode* parentEntity, int sentenceIndex, bool *foundChildEntity)
{
	GIAentityNode* childEntity = parentEntity;
						
	bool foundParentProperty = false;
	for(vector<GIAentityConnection*>::iterator propertyNodeListIterator = parentEntity->propertyNodeList->begin(); propertyNodeListIterator < parentEntity->propertyNodeList->end(); propertyNodeListIterator++)
	{
		GIAentityConnection* propertyConnection = *propertyNodeListIterator;
		GIAentityNode* propertyEntity = propertyConnection->entity;

		#ifdef NLC_DEFINE_LOCAL_VARIABLES_FOR_ALL_INDEFINATE_ENTITIES
		if(checkSentenceIndexParsingCodeBlocks(propertyEntity, propertyConnection, sentenceIndex, false))
		#else
		if(checkSentenceIndexParsingCodeBlocks(propertyEntity, propertyConnection, sentenceIndex, false) || propertyEntity->NLCparsedForCodeBlocks)	//CHECKTHIS; copied from getParent(); if parent is propertyEntity->NLCparsedForCodeBlocks && !sameSentence, then child must be propertyEntity->NLCparsedForCodeBlocks && !sameSentence
		#endif
		{
			if(!(propertyEntity->isSubstanceQuality))
			{
				if(propertyConnection->sameReferenceSet)	//added 1n30a
				{
					#ifdef NLC_APPLY_GET_SAME_REFERENCE_SET_NON_QUALITY_CHILD_FIX_TO_VERIFY_NOT_POSSESSION_AUXILIARY_HAVE
					if(!(propertyConnection->possessionAuxiliaryHave))	//added 1p2b
					{					
					#endif
					#ifdef NLC_APPLY_GET_SAME_REFERENCE_SET_NON_QUALITY_CHILD_FIX_TO_VERIFY_RCMOD_DOES_NOT_INDICATE_SAME_REFERENCE_SET
					if(!(propertyConnection->rcmodIndicatesSameReferenceSet))	//added 1p2b
					{
					#endif
						childEntity = getSameReferenceSetSubstanceNonQualityChild(propertyEntity, sentenceIndex, foundChildEntity);
						*foundChildEntity = true;
					#ifdef NLC_APPLY_GET_SAME_REFERENCE_SET_NON_QUALITY_CHILD_FIX_TO_VERIFY_RCMOD_DOES_NOT_INDICATE_SAME_REFERENCE_SET
					}
					#endif
					#ifdef NLC_APPLY_GET_SAME_REFERENCE_SET_NON_QUALITY_CHILD_FIX_TO_VERIFY_NOT_POSSESSION_AUXILIARY_HAVE
					}
					#endif					
				}
			}
		}
	}
	
	return childEntity;
}




#ifdef GIA_TRANSLATOR_DREAM_MODE_LINK_SPECIFIC_CONCEPTS_AND_ACTIONS
void generateObjectInitialisationsBasedOnSubstanceConcepts(GIAentityNode* entity, NLCcodeblock** currentCodeBlockInTree, int sentenceIndex, bool newlyDeclaredEntityInCategoryList)
{
	//added 6 December 2013: take into account plain concepts; eg "Dogs are fat. The dog rides the bike." <- the dog will be given the property 'fat'
	GIAentityNode* conceptEntity = getPrimaryConceptNodeDefiningInstance(entity);
	generateObjectInitialisationsBasedOnSubstanceConceptsRecurse(entity, conceptEntity, currentCodeBlockInTree, sentenceIndex, NULL, "", newlyDeclaredEntityInCategoryList);

	for(vector<GIAentityConnection*>::iterator entityNodeDefinitionListIterator = entity->entityNodeDefinitionList->begin(); entityNodeDefinitionListIterator < entity->entityNodeDefinitionList->end(); entityNodeDefinitionListIterator++)
	{
		GIAentityConnection* definitionConnection = (*entityNodeDefinitionListIterator);
		//if(!(definitionConnection->NLCparsedForCodeBlocks))	//probably not required
		//{
		GIAentityNode* definitionEntity = definitionConnection->entity;
		//check the definition is a substance concept
		if((definitionEntity->isSubstanceConcept) || (definitionEntity->isActionConcept))	//added (definitionEntity->isActionConcept)  changed 1e2e
		{
			#ifndef NLC_TRANSLATOR_GENERATE_CONTEXT_BLOCKS_PARSE_DEFINITIONS
			definitionConnection->NLCparsedForCodeBlocks = true;
			#endif
			
			generateObjectInitialisationsBasedOnSubstanceConceptsRecurse(entity, definitionEntity, currentCodeBlockInTree, sentenceIndex, NULL, "", newlyDeclaredEntityInCategoryList);
		}
		//}
	}
}

void generateObjectInitialisationsBasedOnSubstanceConceptsRecurse(GIAentityNode* entity, GIAentityNode* definitionEntity, NLCcodeblock** currentCodeBlockInTree, int sentenceIndex, GIAentityNode* parentEntity, string parentConditionName, bool newlyDeclaredEntityInCategoryList)
{
	string parentName = "";
	if(parentEntity != NULL)
	{
		parentName = generateInstanceName(parentEntity);
	}
	
	#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_BASED_ON_CONCEPTS
	if(!(definitionEntity->NLCparsedForlogicalConditionOperations))
	{
	#endif
		//property initialisations
		for(vector<GIAentityConnection*>::iterator propertyNodeListIterator = definitionEntity->propertyNodeList->begin(); propertyNodeListIterator < definitionEntity->propertyNodeList->end(); propertyNodeListIterator++)
		{
			GIAentityConnection* propertyConnection = (*propertyNodeListIterator);
			#ifdef GIA_ENABLE_SUBSTANCE_CONCEPT_ADVANCED_REFERENCING
			if(!(propertyConnection->isReference))
			{
			#endif
				GIAentityNode* propertyEntity = propertyConnection->entity;

				bool alreadyAdded = checkDuplicateProperty(propertyEntity, entity);
				if(!alreadyAdded)
				{
					NLCcodeblock* firstCodeBlockInSection = *currentCodeBlockInTree;
					bool loopUsed = false;

					#ifdef NLC_DEBUG
					cout << "generateObjectInitialisationsBasedOnSubstanceConceptsRecurse{}: property initialisation: entity->entityName = " << entity->entityName << endl;
					#endif
					#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_BLOCKS_FOR_PARENT_INITIALISATION_SPECIAL
					if(newlyDeclaredEntityInCategoryList)
					{
						*currentCodeBlockInTree = createCodeBlockForCategoryList(*currentCodeBlockInTree, entity, NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION);
					}
					else
					{
					#endif
						if(assumedToAlreadyHaveBeenDeclared(entity))
						{
							*currentCodeBlockInTree = createCodeBlockForLocalList(*currentCodeBlockInTree, entity);
						}
						else
						{
							*currentCodeBlockInTree = createCodeBlockForPropertyList(*currentCodeBlockInTree, entity, parentName);
						}
					#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_BLOCKS_FOR_PARENT_INITIALISATION_SPECIAL
					}
					#endif

					*currentCodeBlockInTree = createCodeBlockCreateNewProperty(*currentCodeBlockInTree, entity, propertyEntity, sentenceIndex, false);

					entity->NLCparsedForCodeBlocks = true;			//added NLC 1b6b/4 October 2013 - used for quick access of instances already declared in current context
					generateObjectInitialisationsBasedOnSubstanceConceptsRecurse(entity, propertyEntity, currentCodeBlockInTree, sentenceIndex, definitionEntity, "", true);		//updated 9 November 2013 - support recursion of complex substance concept definition

					*currentCodeBlockInTree = firstCodeBlockInSection->next;
				}
			#ifdef GIA_ENABLE_SUBSTANCE_CONCEPT_ADVANCED_REFERENCING
			}
			#endif
		}
		//state initialisations
		for(vector<GIAentityConnection*>::iterator conditionNodeListIterator = definitionEntity->conditionNodeList->begin(); conditionNodeListIterator < definitionEntity->conditionNodeList->end(); conditionNodeListIterator++)
		{
			GIAentityConnection* conditionConnection = (*conditionNodeListIterator);
			#ifdef GIA_ENABLE_SUBSTANCE_CONCEPT_ADVANCED_REFERENCING
			if(!(conditionConnection->isReference))
			{
			#endif
				GIAentityNode* conditionEntity = conditionConnection->entity;

				#ifdef NLC_NORMALISE_TWOWAY_PREPOSITIONS_DUAL_CONDITION_LINKS_ENABLED
				if(!(conditionEntity->inverseConditionTwoWay) || conditionConnection->isReference)	//prevent infinite loop for 2 way conditions
				{
				#endif		
					bool alreadyAdded = checkDuplicateCondition(conditionEntity, entity);
					if(!alreadyAdded)
					{
						NLCcodeblock* firstCodeBlockInSection = *currentCodeBlockInTree;

						bool foundConditionObject = false;
						GIAentityNode* conditionObject = NULL;
						if(!(conditionEntity->conditionObjectEntity->empty()))
						{
							conditionObject = (conditionEntity->conditionObjectEntity->back())->entity;
							foundConditionObject = true;

							#ifdef NLC_DEBUG
							cout << "generateObjectInitialisationsBasedOnSubstanceConceptsRecurse{}: condition initialisation:  entity->entityName = " << entity->entityName << endl;
							#endif

							#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_BLOCKS_FOR_PARENT_INITIALISATION_SPECIAL
							if(newlyDeclaredEntityInCategoryList)
							{
								*currentCodeBlockInTree = createCodeBlockForCategoryList(*currentCodeBlockInTree, entity, NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION);
							}
							else
							{
							#endif
								if(assumedToAlreadyHaveBeenDeclared(entity))
								{
									*currentCodeBlockInTree = createCodeBlockForLocalList(*currentCodeBlockInTree, entity);
								}
								else
								{
									NLCitem* entityClass = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
									NLCitem* parentConditionItem = new NLCitem(parentConditionName, NLC_ITEM_TYPE_OBJECT);
									parentConditionItem->context.push_back(parentName);
									*currentCodeBlockInTree = createCodeBlockForConditionList(*currentCodeBlockInTree, parentConditionItem, entityClass);
								}
							#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_BLOCKS_FOR_PARENT_INITIALISATION_SPECIAL
							}
							#endif

							*currentCodeBlockInTree = createCodeBlockCreateNewCondition(*currentCodeBlockInTree, entity, conditionEntity, sentenceIndex, false);

							entity->NLCparsedForCodeBlocks = true;			//added NLC 1b6b/4 October 2013 - used for quick access of instances already declared in current context
							generateObjectInitialisationsBasedOnSubstanceConceptsRecurse(entity, conditionObject, currentCodeBlockInTree, sentenceIndex, definitionEntity, conditionEntity->entityName, true);	//updated 9 November 2013 - support recursion of complex substance concept definition

							*currentCodeBlockInTree = firstCodeBlockInSection->next;

						}
					}
				#ifdef NLC_NORMALISE_TWOWAY_PREPOSITIONS_DUAL_CONDITION_LINKS_ENABLED
				}
				#endif
			#ifdef GIA_ENABLE_SUBSTANCE_CONCEPT_ADVANCED_REFERENCING
			}
			#endif
		}
	#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_BASED_ON_CONCEPTS
	}
	#endif
}
#endif


#ifdef NLC_USE_ADVANCED_REFERENCING_SUPPORT_ALIASES

#ifdef NLC_USE_ADVANCED_REFERENCING_SUPPORT_ALIASES_PREVENT_ADDING_AS_FUNCTION_ARGUMENT
//CURRENTLYILLEGAL: "Tom rides a bike. Tom is the red dog."
void fillFunctionAliasClassList(NLCcodeblock** currentCodeBlockInTree, vector<GIAentityNode*>* entityNodesActiveListComplete)
{	
	#ifdef NLC_DEBUG_ADVANCED_REFERENCING_SUPPORT_ALIASES
	cout << "start fillFunctionAliasClassList{}:" << endl;
	#endif
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode* aliasClassEntity = (*entityIter);

		for(vector<GIAentityConnection*>::iterator entityNodeDefinitionListIterator = aliasClassEntity->entityNodeDefinitionList->begin(); entityNodeDefinitionListIterator < aliasClassEntity->entityNodeDefinitionList->end(); entityNodeDefinitionListIterator++)
		{
			GIAentityConnection* definitionConnection = (*entityNodeDefinitionListIterator);
			GIAentityNode* aliasEntity = definitionConnection->entity;

			if(definitionConnection->isAlias)
			{
				string aliasName = aliasEntity->entityName;
				string aliasClassName = aliasClassEntity->entityName;
					
				unordered_map<string, string>* functionAliasClassList = getFunctionAliasClassList();
				functionAliasClassList->insert(pair<string, string>(aliasName, aliasClassName));
			}
		}
	}
	#ifdef NLC_DEBUG_ADVANCED_REFERENCING_SUPPORT_ALIASES
	cout << "end fillFunctionAliasClassList{}:" << endl;
	#endif
}
#endif

#endif

bool checkSpecialCaseEntity(GIAentityNode* entity, bool detectActions)
{
	bool specialCaseEntity = false;
	if((entity->isConcept) || (entity->isSubstanceConcept) || (entity->isActionConcept) || (entity->isCondition))
	{
		specialCaseEntity = true;
	}
	else if(detectActions && (entity->isAction))
	{
		specialCaseEntity = true;
	}
	return specialCaseEntity;
}	

bool checkConceptTypeEntity(GIAentityNode* entity)
{
	bool conceptTypeEntity = false;
	if((entity->isConcept) || (entity->isSubstanceConcept) || (entity->isActionConcept))
	{
		conceptTypeEntity = true;
	}
	return conceptTypeEntity;
}
		

#ifdef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES
bool generateContextBasedOnDeclaredParent(GIAentityNode* entity, NLCcodeblock** currentCodeBlockInTree, bool topLevel, GIAentityNode* generateObjectInitialisationsLastParent, int sentenceIndex)
{
	bool foundParentProperty = false;
	for(vector<GIAentityConnection*>::iterator propertyNodeListIterator = entity->propertyNodeReverseList->begin(); propertyNodeListIterator < entity->propertyNodeReverseList->end(); propertyNodeListIterator++)
	{
		GIAentityConnection* parentConnection = *propertyNodeListIterator;
		GIAentityNode* parentEntity = parentConnection->entity;
				
		if(!foundParentProperty)
		{
			if(parentEntity->sentenceIndexTemp <= entity->sentenceIndexTemp)	//no strict same sentence check as this function assumes GIA referencing
			{
				if(!(parentEntity->disabled))
				{
					if(assumedToAlreadyHaveBeenDeclared(parentEntity))
					{
						if(parentEntity != generateObjectInitialisationsLastParent)	//added 1l7h
						{
							foundParentProperty = true;
							if(topLevel)
							{						
								*currentCodeBlockInTree = createCodeBlockForLocalList(*currentCodeBlockInTree, parentEntity);	
							}
							
							*currentCodeBlockInTree = createCodeBlockForPropertyList(*currentCodeBlockInTree, entity, generateInstanceName(parentEntity));	
							entity->NLCcontextGenerated = true;
							NLCgenerateContextBlocksVariables generateContextBlocksVariables;
							generateContextBlocksVariables.onlyGenerateContextBlocksIfConnectionsParsedForNLCorSameReferenceSet = true;	//CHECKTHIS
							generateContextBlocks(currentCodeBlockInTree, entity, sentenceIndex, &generateContextBlocksVariables, true, NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION);		//added 1l13b
							//createCodeBlockForStatements(currentCodeBlockInTree, generateInstanceName(entity), entity, sentenceIndex, &generateContextBlocksVariables);	//added 1l13a	//or generateContextBlocksSimple(currentCodeBlockInTree, entity, sentenceIndex, &generateContextBlocksVariables, true, NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION)
	
							/*//alternative implementation not possible, because of "Tom's boat is red. The chicken rowed the red boat."
							NLCgenerateContextBlocksVariables generateContextBlocksVariables;
							generateContextBlocksVariables.onlyGenerateContextBlocksIfConnectionsParsedForNLCorSameReferenceSet = true;	//CHECKTHIS
							if(generateContextBlocksSimple(currentCodeBlockInTree, entity, sentenceIndex, &generateContextBlocksVariables, false, NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION))
							{

							}
							*/
							
							#ifdef NLC_DEBUG
							cout << "generateContextBasedOnDeclaredParent: entity: " << entity->entityName << endl;
							cout << "generateContextBasedOnDeclaredParent: foundParentProperty: " << parentEntity->entityName << endl;
							#endif
						}
					}
				}
			}
		}
	}
	return foundParentProperty;
}
#endif

#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_FOR_EACH_CHILD_GET_PARENT_ORIGINAL_IMPLEMENTATION		
void addIntermediaryImplicitlyDeclaredEntityToLocalList(NLCcodeblock** currentCodeBlockInTree, GIAentityNode* childEntity)
{
	#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN_DO_NOT_ADD_DUPLICATES
	#ifdef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES
	*currentCodeBlockInTree = createCodeBlockAddEntityToGenericListCheckLastSentenceReferencedPluralExecuteFunction(*currentCodeBlockInTree, childEntity, generateInstanceName(childEntity), NLC_ITEM_TYPE_INSTANCE_VAR_APPENDITION, childEntity);	
	#else
	*currentCodeBlockInTree = createCodeBlockAddEntityToGenericListCheckLastSentenceReferencedPluralExecuteFunction(*currentCodeBlockInTree, childEntity, childEntity->entityName, NLC_ITEM_TYPE_CLASS_VAR_APPENDITION, childEntity);		//OR; ... , generateClassName(entity), "", ...		
	#endif
	#else
	*currentCodeBlockInTree = createCodeBlockAddEntityToLocalList(*currentCodeBlockInTree, childEntity, childEntity);	//removed 1j10a, restored 1j12b for NLC_LOCAL_LISTS_USE_INSTANCE_NAMES only, restored for !NLC_LOCAL_LISTS_USE_INSTANCE_NAMES 1l12a
	#endif
}
#endif
			
#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
bool checkConditionLogicalConditionAdvancedTests(GIAentityNode* conditionEntity)
{
	bool logicalConditionTests = true;
	//prevent logical conditions (eg if) and logical condition conjunctions (eg and) from being parsed - this enables generateCodeBlocksPart2logicalConditions{}:getParentAndGenerateContextBlocks() to parseConditionParents

	#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS_ADVANCED
	bool conjunctionConditionFound = textInTextArray(conditionEntity->entityName, entityCoordinatingConjunctionArray, ENTITY_COORDINATINGCONJUNCTION_ARRAY_NUMBER_OF_TYPES);
	if(conjunctionConditionFound)
	{
		logicalConditionTests = false;
	}	
	#endif		
	if(logicalConditionOperationEntity->NLClogicalConditionOperation)	//used to test more complex sentence context requirements of some logical condition operations eg "for" is required to be immediately succeeded by "each", "all", or every
	{
		int logicalOperation = INT_DEFAULT_VALUE;
		bool logicalConditionOperationFound = textInTextArray(conditionEntity->entityName, logicalConditionOperationsArray, NLC_LOGICAL_CONDITION_OPERATIONS_NUMBER_OF_TYPES, &logicalOperation);
		if(logicalConditionOperationFound)
		{
			logicalConditionTests = false;
		}
	}
	
	return logicalConditionTests;
}
#endif

#ifdef NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY
bool checkNumerosity(GIAentityNode* entity)
{
	bool hasNumerosity = false;
	if((entity->hasQuantity) && (entity->grammaticalNumber == GRAMMATICAL_NUMBER_PLURAL))
	{
		hasNumerosity = true;
	}
	return hasNumerosity;
}
#endif
					


