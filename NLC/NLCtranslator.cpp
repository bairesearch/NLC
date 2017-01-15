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
 * File Name: NLCtranslator.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2015 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 1p10a 11-July-2015
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/


#include "NLCtranslator.h"
#include "NLCtranslatorCodeBlocks.h"
#include "NLCtranslatorCodeBlocksLogicalConditionsAdvanced.h"	//required for tagAllEntitiesInSentenceSubsetAsPertainingToLogicalConditionOperationAdvanced
#include "NLCtranslatorClassDefinitions.h"
#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS_ADVANCED
#include "GIAtranslatorDefs.h"
#endif
#ifdef NLC_USE_ADVANCED_REFERENCING_SUPPORT_ALIASES
#include "NLCtranslatorCodeBlocksOperations.h"	//required for initialiseFunctionAliasClassList()
#endif

#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS_ADVANCED
NLClogicalConditionConjunctionContainer::NLClogicalConditionConjunctionContainer(void)
{
	entity = NULL;
	optimumPathIndex = 0;
}
NLClogicalConditionConjunctionContainer::NLClogicalConditionConjunctionContainer(GIAentityNode* currentEntity)
{
	entity = currentEntity;
	optimumPathIndex = 0;
}
NLClogicalConditionConjunctionContainer::~NLClogicalConditionConjunctionContainer(void)
{
}
#endif
		
bool translateNetwork(NLCcodeblock* firstCodeBlockInTree, vector<NLCclassDefinition*>* classDefinitionList, vector<GIAentityNode*>* entityNodesActiveListComplete, map<int, vector<GIAentityNode*>*>* entityNodesActiveListSentences, int maxNumberSentences, string NLCfunctionName, NLCfunction* currentNLCfunctionInList, bool useNLCpreprocessor)
{
	bool result = true;

	#ifdef NLC_USE_PREPROCESSOR
	initialiseLogicalConditionLevelRecordArray(useNLCpreprocessor);
	#endif

	/*//this is done by GIA
	#ifdef NLC_CATEGORIES_TEST_PLURALITY_ENFORCE
	#ifdef NLC_USE_PREPROCESSOR
	//NLC translator Part prep A.
	if(!identifyImplicitPluralLogicalConditionOperationsObjects(entityNodesActiveListComplete, maxNumberSentences))
	{
		result = false;
	}
	#endif
	#endif	
	*/

	#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
	#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS_ADVANCED
	//NLC translator Part prep B.
	if(!removeRedundantConditionConjunctions(entityNodesActiveListSentences, maxNumberSentences))
	{
		result = false;
	}
	#endif
	//NLC translator Part prep C.
	if(!identifyAndTagAllLogicalConditionOperations(entityNodesActiveListSentences, maxNumberSentences))
	{
		result = false;
	}
	#else
	if(!disableAllForLoopPredeterminers(entityNodesActiveListSentences, maxNumberSentences))
	{
		result = false;
	}	
	#endif
	
	#ifdef NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_SUPPORT_ALPHANUMERIC_ENTITY_NAMES_ONLY
	if(!checkAlphaNumericEntityNames(entityNodesActiveListComplete, maxNumberSentences))
	{
		result = false;
	}	
	#endif
	
	//NLC translator Part 1.
	if(!generateCodeBlocks(firstCodeBlockInTree, entityNodesActiveListComplete, entityNodesActiveListSentences, maxNumberSentences, NLCfunctionName, currentNLCfunctionInList))
	{
		result = false;
	}
	
	//cout << "finished generateCodeBlocks{}" << endl;

	//NLC translator Part 2.
	if(!generateClassHeirarchy(classDefinitionList, entityNodesActiveListComplete))
	{
		result = false;
	}
	
	//cout << "finished generateClassHeirarchy{}" << endl;
		
	return result;
}

/*
#ifdef NLC_CATEGORIES_TEST_PLURALITY_ENFORCE
#ifdef NLC_USE_PREPROCESSOR
bool identifyImplicitPluralLogicalConditionOperationsObjects(vector<GIAentityNode*>* entityNodesActiveListComplete, int maxNumberSentences)
{
	bool result = true;
	
	for(int sentenceIndex=GIA_NLP_START_SENTENCE_INDEX; sentenceIndex <= maxNumberSentences; sentenceIndex++)
	{
		for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
		{
			GIAentityNode* conditionEntity = (*entityIter);
			if(checkSentenceIndexParsingCodeBlocks(conditionEntity, sentenceIndex, true))	//could be set to false instead
			{
				//because GIA GIAsentence objects are unavailable to NLC, must parse all entities including disabled entites and locate matching entities (in same sentence and with entityIndex+1 of "for" condition):
				for(vector<GIAentityNode*>::iterator entityIter2 = entityNodesActiveListComplete->begin(); entityIter2 != entityNodesActiveListComplete->end(); entityIter2++)
				{
					GIAentityNode* entity2 = (*entityIter);
					if(entity2->sentenceIndexTemp == sentenceIndex)
					{
						if(entity2->entityIndexTemp = conditionEntity->entityIndexTemp+1)
						{	
							#ifdef NLC_USE_PREPROCESSOR
							if(entity2->entityIndexTemp == 1)	//NLP parsable phrase: "every chicken..."
							#else
							if(entity2->entityIndexTemp == 2)	//GIAsentence: "For every chicken..."
							#endif
							{
								//eg "for each chicken" / "for every chicken" / "while each chicken" / "while every chicken"
								bool wordImmediatelySucceedingForFound = textInTextArray(entity2->entityName, logicalConditionOperationsWordImmediatelySucceedingForArray, NLC_LOGICAL_CONDITION_OPERATIONS_WORD_IMMEDIATELY_SUCCEEDING_FOR_NUMBER_OF_TYPES);
								if(wordImmediatelySucceedingForFound)
								{
									cout << "identifyImplicitPluralLogicalConditionOperationsObjects{}: wordImmediatelySucceedingForFound" << endl;
									entity2->grammaticalNumber == GRAMMATICAL_NUMBER_PLURAL;
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
#endif
*/

#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS_ADVANCED
bool removeRedundantConditionConjunctions(map<int, vector<GIAentityNode*>*>* entityNodesActiveListSentences, int maxNumberSentences)
{
	bool result = true;
	for(map<int, vector<GIAentityNode*>*>::iterator sentenceIter = entityNodesActiveListSentences->begin(); sentenceIter != entityNodesActiveListSentences->end(); sentenceIter++)
	{
		int sentenceIndex = sentenceIter->first;
		vector<GIAentityNode*>* entityNodesActiveListSentence = sentenceIter->second;
	
		NLClogicalConditionConjunctionContainer* logicalConditionConjunctionContainerFirstInOptimumPath = NULL;
		int maximumNumberOfConjunctions = 0;
		for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListSentence->begin(); entityIter != entityNodesActiveListSentence->end(); entityIter++)
		{
			GIAentityNode* conditionEntity = (*entityIter);
			if(conditionEntity->isCondition)
			{
				if(checkSentenceIndexParsingCodeBlocks(conditionEntity, sentenceIndex, false))
				{
					int conjunctionType = INT_DEFAULT_VALUE;
					bool conjunctionConditionFound = textInTextArray(conditionEntity->entityName, entityCoordinatingConjunctionArray, ENTITY_COORDINATINGCONJUNCTION_ARRAY_NUMBER_OF_TYPES, &conjunctionType);
					if(conjunctionConditionFound)
					{
						NLClogicalConditionConjunctionContainer* logicalConditionConjunctionContainer = new NLClogicalConditionConjunctionContainer(conditionEntity);
						int numberOfConjunctions = addConjunctionsConnectedToConditionConjunctionObject(conditionEntity, logicalConditionConjunctionContainer, sentenceIndex);
						if(numberOfConjunctions > maximumNumberOfConjunctions)
						{
							logicalConditionConjunctionContainerFirstInOptimumPath = logicalConditionConjunctionContainer;
							maximumNumberOfConjunctions = numberOfConjunctions;
							//cout << "maximumNumberOfConjunctions = " << maximumNumberOfConjunctions << endl;
						}
					}
				}
			}
		}

		#ifdef NLC_DEBUG
		cout << "maximumNumberOfConjunctions = " << maximumNumberOfConjunctions << endl;
		#endif
		if(maximumNumberOfConjunctions > 0)
		{
			for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
			{
				GIAentityNode* conditionEntity = (*entityIter);
				if(conditionEntity->isCondition)
				{
					if(checkSentenceIndexParsingCodeBlocks(conditionEntity, sentenceIndex, false))
					{
						int conjunctionType = INT_DEFAULT_VALUE;
						bool conjunctionConditionFound = textInTextArray(conditionEntity->entityName, entityCoordinatingConjunctionArray, ENTITY_COORDINATINGCONJUNCTION_ARRAY_NUMBER_OF_TYPES, &conjunctionType);
						if(conjunctionConditionFound)
						{
							if(!traceConditionConjunctionsOptimiumPathAndSeeIfConditionConjunctionEntityIsOnIt(logicalConditionConjunctionContainerFirstInOptimumPath, conditionEntity))
							{
								GIAentityNode* logicalConditionConjunctionObjectEntity = (conditionEntity->conditionObjectEntity->back())->entity;
								GIAentityNode* logicalConditionConjunctionSubjectEntity = (conditionEntity->conditionSubjectEntity->back())->entity;
								#ifdef NLC_DEBUG
								cout << "disabling conditionEntity: " << conditionEntity->entityName << endl;
								cout << "logicalConditionConjunctionObjectEntity: " << logicalConditionConjunctionObjectEntity->entityName << endl;
								cout << "logicalConditionConjunctionSubjectEntity: " << logicalConditionConjunctionSubjectEntity->entityName << endl;
								#endif

								conditionEntity->disabled = true;
							}
						}
					}
				}
			}
		}
	}
	return result;
}

int addConjunctionsConnectedToConditionConjunctionObject(GIAentityNode* conditionEntity, NLClogicalConditionConjunctionContainer* logicalConditionConjunctionContainer, int sentenceIndex)
{
	int maximumNumberOfConjunctions = 0;
	GIAentityNode* conditionObjectEntity = NULL;
	GIAentityConnection* conditionConnection = NULL;
	bool conditionHasObject = false;
	if(!(conditionEntity->conditionObjectEntity->empty()))
	{
		conditionHasObject = true;
		conditionConnection = conditionEntity->conditionObjectEntity->back();
		conditionObjectEntity = conditionConnection->entity;
	}
	if(conditionHasObject)
	{
		if(checkSentenceIndexParsingCodeBlocks(conditionObjectEntity, conditionConnection, sentenceIndex, false))
		{
			int conjunctionIndex = 0;
			for(vector<GIAentityConnection*>::iterator connectionIter = conditionObjectEntity->conditionNodeList->begin(); connectionIter != conditionObjectEntity->conditionNodeList->end(); connectionIter++)
			{
				GIAentityConnection* conditionConnection2 = (*connectionIter);
				GIAentityNode* conditionEntity2 = conditionConnection2->entity;
				if(checkSentenceIndexParsingCodeBlocks(conditionEntity2, conditionConnection2, sentenceIndex, false))
				{
					int conjunctionType = INT_DEFAULT_VALUE;
					bool conjunctionConditionFound = textInTextArray(conditionEntity2->entityName, entityCoordinatingConjunctionArray, ENTITY_COORDINATINGCONJUNCTION_ARRAY_NUMBER_OF_TYPES, &conjunctionType);
					if(conjunctionConditionFound)
					{
						//NB #ifdef NLC_NORMALISE_INVERSE_PREPOSITIONS checks are not required because ENTITY_COORDINATINGCONJUNCTION_ARRAY_NUMBER_OF_TYPES are not defined to be two way
						
						NLClogicalConditionConjunctionContainer* logicalConditionConjunctionContainer2 = new NLClogicalConditionConjunctionContainer(conditionEntity2);
						logicalConditionConjunctionContainer->nextConditionConjunctions.push_back(logicalConditionConjunctionContainer2);
						int numberOfConjunctions = addConjunctionsConnectedToConditionConjunctionObject(conditionEntity2, logicalConditionConjunctionContainer2, sentenceIndex);
						if(numberOfConjunctions > maximumNumberOfConjunctions)
						{
							logicalConditionConjunctionContainer->optimumPathIndex = conjunctionIndex;
							maximumNumberOfConjunctions = numberOfConjunctions;
						}
						conjunctionIndex++;
					}
				}
			}
		}
	}
	else
	{
		cout << "addConjunctionsConnectedToConditionConjunctionObject{} error: !conditionHasObject" << endl;
	}
	return maximumNumberOfConjunctions + 1;
}

bool traceConditionConjunctionsOptimiumPathAndSeeIfConditionConjunctionEntityIsOnIt(NLClogicalConditionConjunctionContainer* logicalConditionConjunctionContainer, GIAentityNode* logicalConditionConjunctionToTest)
{
	bool foundLogicalConditionConjunctionOnOptimumPath = false;
	if(logicalConditionConjunctionToTest == logicalConditionConjunctionContainer->entity)
	{
		foundLogicalConditionConjunctionOnOptimumPath = true;
	}
	else
	{
		if(!(logicalConditionConjunctionContainer->nextConditionConjunctions.empty()))
		{
			if(traceConditionConjunctionsOptimiumPathAndSeeIfConditionConjunctionEntityIsOnIt(logicalConditionConjunctionContainer->nextConditionConjunctions[logicalConditionConjunctionContainer->optimumPathIndex], logicalConditionConjunctionToTest))
			{
				foundLogicalConditionConjunctionOnOptimumPath = true;
			}
		}
	}
	return foundLogicalConditionConjunctionOnOptimumPath;
	/*
	for(vector<NLClogicalConditionConjunctionContainer*>::iterator iter = logicalConditionConjunctionContainer->nextConditionConjunctions->begin(); iter != logicalConditionConjunctionContainer->nextConditionConjunctions->end(); iter++)
	{

	}
	*/
}
#endif

bool identifyAndTagAllLogicalConditionOperations(map<int, vector<GIAentityNode*>*>* entityNodesActiveListSentences, int maxNumberSentences)
{
	bool result = true;
	
	for(map<int, vector<GIAentityNode*>*>::iterator sentenceIter = entityNodesActiveListSentences->begin(); sentenceIter != entityNodesActiveListSentences->end(); sentenceIter++)
	{
		int sentenceIndex = sentenceIter->first;
		vector<GIAentityNode*>* entityNodesActiveListSentence = sentenceIter->second;
	
		for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListSentence->begin(); entityIter != entityNodesActiveListSentence->end(); entityIter++)
		{
			GIAentityNode* conditionEntity = (*entityIter);
			if(checkSentenceIndexParsingCodeBlocks(conditionEntity, sentenceIndex, true))	//could be set to false instead
			{
				bool foundLogicalConditionOperation = false;
				int logicalOperation;
				bool foundLogicalConditionOperationBasic = textInTextArray(conditionEntity->entityName, logicalConditionOperationsArray, NLC_LOGICAL_CONDITION_OPERATIONS_NUMBER_OF_TYPES, &logicalOperation);
				if(foundLogicalConditionOperationBasic && (logicalOperation == NLC_LOGICAL_CONDITION_OPERATIONS_FOR))
				{
					//FUTURE: NB this implementation must be made compatible with GIAdatabase.cpp and GIAxmlConversion.cpp (eg store entityIndex and sentenceIndexTemp). NB sentenceIndexTemp is necessary for other NLC functions also.
					#ifdef NLC_ONLY_SUPPORT_LOGICAL_CONJUNCTION_FOR_AT_START_OF_SENTENCE
					if(conditionEntity->entityIndexTemp == 1)
					{
						foundLogicalConditionOperation = true;
					}
					#else
					//because GIA GIAsentence objects are unavailable to NLC, must parse all entities including disabled entites and locate matching entities (in same sentence and with entityIndex+1 of "for" condition):
					for(vector<GIAentityNode*>::iterator entityIter2 = entityNodesActiveListComplete->begin(); entityIter2 != entityNodesActiveListComplete->end(); entityIter2++)
					{
						GIAentityNode* entity2 = (*entityIter);
						if(entity2->sentenceIndexTemp == sentenceIndex)
						{
							if(entity2->entityIndexTemp = conditionEntity->entityIndex+1)
							{
								bool wordImmediatelySucceedingForFound = textInTextArray(entity2->entityName, logicalConditionOperationsWordImmediatelySucceedingForArray, NLC_LOGICAL_CONDITION_OPERATIONS_WORD_IMMEDIATELY_SUCCEEDING_FOR_NUMBER_OF_TYPES);
								foundLogicalConditionOperation = true;
							}
						}
					}
					#endif
				}
				else if(foundLogicalConditionOperationBasic)
				{
					foundLogicalConditionOperation = true;
				}
				if(foundLogicalConditionOperation)
				{
					//concepts must be tagged as NLClogicalConditionOperation to prevent generateClassHeirarchy from creating class definitions for logical conditions
					#ifdef NLC_DEBUG
					cout << "foundLogicalConditionOperation: " << conditionEntity->entityName << endl;
					#endif
					conditionEntity->NLClogicalConditionOperation = true;

					if(conditionEntity->isCondition)
					{//ignore concepts

						GIAentityNode* conditionSubject = NULL;
						GIAentityNode* conditionObject = NULL;
						bool foundConditionSubject = false;
						bool foundConditionObject = false;
						if(!(conditionEntity->conditionSubjectEntity->empty()))
						{
							conditionSubject = (conditionEntity->conditionSubjectEntity->back())->entity;
							foundConditionSubject = true;
						}
						if(!(conditionEntity->conditionObjectEntity->empty()))
						{
							conditionObject = (conditionEntity->conditionObjectEntity->back())->entity;
							foundConditionObject = true;
						}
						if(foundConditionSubject && foundConditionObject)
						{
							conditionEntity->NLCparsedForlogicalConditionOperations = true;
							//cout << "tagged: conditionEntity->entityName = " << conditionEntity->entityName << endl;

							if(conditionObject->isConcept)
							{
								cout << "identifyAndTagAllLogicalConditionOperations{} error: NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_BASED_ON_CONCEPTS only handles substance concepts. GIA_CREATE_SUBSTANCE_CONCEPTS_FOR_ALL_SENTENCES_WITH_CONCEPTS must be enabled." << endl;
								cout << "conditionObject = " << conditionObject->entityName;
							}
							else
							{
								tagAllEntitiesInSentenceSubsetAsPertainingToLogicalConditionOperationAdvanced(conditionObject, sentenceIndex, true);
							}
							if(conditionSubject->isConcept)
							{
								cout << "identifyAndTagAllLogicalConditionOperations{} error: NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_BASED_ON_CONCEPTS only handles substance concepts. GIA_CREATE_SUBSTANCE_CONCEPTS_FOR_ALL_SENTENCES_WITH_CONCEPTS must be enabled." << endl;
								cout << "conditionSubject = " << conditionSubject->entityName;
							}
							else
							{
								tagAllEntitiesInSentenceSubsetAsPertainingToLogicalConditionOperationAdvanced(conditionSubject, sentenceIndex, true);
							}
						}
					}
				}
			}
		}
	}
	return result;
}
#else


bool disableAllForLoopPredeterminers(map<int, vector<GIAentityNode*>*>* entityNodesActiveListSentences, int maxNumberSentences)
{
	//this function prevents predeterminers from being parsed by generateCodeBlocksFromMathTextNLPparsablePhrase/generateCodeBlocksFromMathTextNLPparsablePhraseLogicalConditionFor (which prevents all entities from being parsed by generateCodeBlocksFromMathTextNLPparsablePhrase/generateCodeBlocksFromMathTextNLPparsablePhraseLogicalConditionFor)
	bool result = true;
	
	for(map<int, vector<GIAentityNode*>*>::iterator sentenceIter = entityNodesActiveListSentences->begin(); sentenceIter != entityNodesActiveListSentences->end(); sentenceIter++)
	{
		int sentenceIndex = sentenceIter->first;
		vector<GIAentityNode*>* entityNodesActiveListSentence = sentenceIter->second;
	
		for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListSentence->begin(); entityIter != entityNodesActiveListSentence->end(); entityIter++)
		{
			GIAentityNode* entity = (*entityIter);
			bool wordImmediatelySucceedingForFound = textInTextArray(entity->entityName, logicalConditionOperationsWordImmediatelySucceedingForArray, NLC_LOGICAL_CONDITION_OPERATIONS_WORD_IMMEDIATELY_SUCCEEDING_FOR_NUMBER_OF_TYPES);
			if(wordImmediatelySucceedingForFound)
			{
				entity->disabled = true;	//should not be required; disableInstanceAndConceptEntityNLC(entity);
			}
		}
	}
	return result;
}
/*
void disableInstanceAndConceptEntityNLC(GIAentityNode* entity)
{
	entity->disabled = true;
	if(!(entity->entityNodeDefiningThisInstance->empty()))
	{
		GIAentityNode* conceptEntity = getPrimaryConceptNodeDefiningInstance(entity);
		conceptEntity->disabled = true
	}
}
*/

#endif

#ifdef NLC_SUPPORT_INPUT_FUNCTION_LISTS
#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS
//NB firstCodeBlockInTree contains the new function codeblock (NLC_CODEBLOCK_TYPE_NEW_FUNCTION) parameters: NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION_OWNER, NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION_OBJECT, NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION_OBJECT, NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_INSTANCE_OR_CLASS_LIST
void reconcileFunctionDefinitionClassDefinitionArgumentsBasedOnImplicitlyDeclaredVariablesInCurrentFunctionDefinition(NLCcodeblock* firstCodeBlockInTree, vector<NLCclassDefinition*>* classDefinitionList, NLCclassDefinition* functionDefinitionClassDefinition)
{
	//reconcile functionDefinition classDefinition arguments (ie class function header) - NB functionReference [classDefinition?] arguments are reconciled in printCodeBlocks()  

	NLCclassDefinitionFunctionDependency* functionDefinitionFunctionDependency = functionDefinitionClassDefinition->functionDependency;
	
	string functionName = functionDefinitionFunctionDependency->functionName;
	string functionOwnerName = functionDefinitionFunctionDependency->functionOwnerName;
	string functionObjectName = functionDefinitionFunctionDependency->functionObjectName;
	bool hasFunctionOwnerClass = functionDefinitionFunctionDependency->hasFunctionOwnerClass;
	bool hasFunctionObjectClass = functionDefinitionFunctionDependency->hasFunctionObjectClass;

	#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
	bool findFunctionOwnerExactMatch = true;
	bool findFunctionObjectExactMatch = true;
	bool rearrangeClassList = false;	//irrelevant
	//NB findFunctionDefinitionClassDefinition parses (reconcile/rearranges) functionDefinition classDefinitions only (isReferenceElseFunctionDefinition==false)
		
	#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
	cout << "addImplicitlyDeclaredVariablesInCurrentFunctionDefinitionArgumentsToFunctionDefinition" << endl;
	#endif
	#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_BASED_ON_IMPLICITLY_DECLARED_VARIABLES_IN_CURRENT_FUNCTION_DEFINITION

	//adds the arguments from firstCodeBlockInTree (NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_INSTANCE_OR_CLASS_LIST) to the functionDefinition classDefinition
	addImplicitlyDeclaredVariablesInCurrentFunctionDefinitionArgumentsToFunctionDefinition(&(firstCodeBlockInTree->parameters), functionDefinitionClassDefinition);	//note this has already been done for libraryFunctions

	#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE_ACTIVE
	//propogates arguments from dependency child functionDefintions to current functionDefintion
	for(vector<NLCclassDefinition*>::iterator classDefinitionListIter = functionDefinitionClassDefinition->functionDependencyList.begin(); classDefinitionListIter != functionDefinitionClassDefinition->functionDependencyList.end(); classDefinitionListIter++)
	{
		NLCclassDefinitionFunctionDependency* functionDefinitionFunctionDependencyChild = (*classDefinitionListIter)->functionDependency;
		NLCclassDefinition* functionDefinitionClassDefinition2 = NULL;
		//find the dependency child functionDefinition
		if(findFunctionDefinitionClassDefinition(classDefinitionList, functionDefinitionFunctionDependencyChild->functionName, functionDefinitionFunctionDependencyChild->functionOwnerName, functionDefinitionFunctionDependencyChild->functionObjectName, functionDefinitionFunctionDependencyChild->hasFunctionOwnerClass, functionDefinitionFunctionDependencyChild->hasFunctionObjectClass, findFunctionOwnerExactMatch, findFunctionObjectExactMatch, &functionDefinitionClassDefinition2, rearrangeClassList))	//should find exact match as class definitions have already been created for all new function definitions (and their implicit declarations have been added to their function argument lists)
		{
			addImplicitlyDeclaredVariablesInCurrentFunctionDefinitionToFunctionDefinition(functionDefinitionClassDefinition2, functionDefinitionClassDefinition);	//pass arguments from child to parent
			addImplicitlyDeclaredVariablesInCurrentFunctionDefinitionToFunctionDefinitionArguments(functionDefinitionClassDefinition2, &(firstCodeBlockInTree->parameters));	//note can use functionDefinitionClassDefinition instead of functionDefinitionClassDefinition2
		}
	}
	#endif
	#endif

	#else
	cout << "reconcileFunctionDefinitionClassDefinitionArgumentsBasedOnImplicitlyDeclaredVariablesInCurrentFunctionDefinition{} error: !NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED no longer supported" << endl;
	exit(0);
	#endif
}

#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_BASED_ON_IMPLICITLY_DECLARED_VARIABLES_IN_CURRENT_FUNCTION_DEFINITION
#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED

//fine; this function is not duplicating arguments
void addImplicitlyDeclaredVariablesInCurrentFunctionDefinitionArgumentsToFunctionDefinition(vector<NLCitem*>* functionDefinitionSourceArgumentList, NLCclassDefinition* functionDefinition)
{
	//cout << "addImplicitlyDeclaredVariablesInCurrentFunctionDefinitionArgumentsToFunctionDefinition{}: functionDefinition->name = " << functionDefinition->name << endl;
	vector<NLCitem*>* functionDefinitionArgumentList = &(functionDefinition->parameters);
	
	/*
	cout << "addImplicitlyDeclaredVariablesInCurrentFunctionDefinitionArgumentsToFunctionDefinition{}: functionDefinition->name = " << functionDefinition->name << endl;
	for(vector<NLCitem*>::iterator parametersIterator = functionDefinitionArgumentList->begin(); parametersIterator < functionDefinitionArgumentList->end(); parametersIterator++)
	{
		NLCitem* temp = *parametersIterator;
		cout << "temp->name = " << temp->name << endl;
	}
	*/
	
	for(vector<NLCitem*>::iterator parametersIterator = functionDefinitionSourceArgumentList->begin(); parametersIterator < functionDefinitionSourceArgumentList->end(); parametersIterator++)
	{
		NLCitem* functionDefinitionSourceArgument = *parametersIterator;
		if(functionDefinitionSourceArgument->itemType == NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_INSTANCE_OR_CLASS_LIST)
		{
			//add a new function argument to the existing function argument list
			NLCitem* functionArgumentTemp = NULL;
			if(!findFunctionArgument(functionDefinitionArgumentList, functionDefinitionSourceArgument, NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_INSTANCE_OR_CLASS_LIST, &functionArgumentTemp))
			{
				#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
				cout << "addImplicitlyDeclaredVariablesInCurrentfunctionDefinitionSourceToFunctionDeclaration: functionDefinitionSourceArgument->name = " << functionDefinitionSourceArgument->name << endl;
				cout << "adding: functionDefinitionSourceArgument->name = " << functionDefinitionSourceArgument->name << " to " << "functionDefinition->functionName = " << functionDefinition->name << endl;
				#endif
				NLCitem* newFunctionArgument = new NLCitem(functionDefinitionSourceArgument);	//NLC by default uses plural (lists) not singular entities
				newFunctionArgument->itemType = NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_INSTANCE_OR_CLASS_LIST;
				functionDefinitionArgumentList->push_back(newFunctionArgument);
			}
		}
	}
}
#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE
//fine; this function is not duplicating arguments
void addImplicitlyDeclaredVariablesInCurrentFunctionDefinitionToFunctionDefinition(NLCclassDefinition* functionDefinitionSource, NLCclassDefinition* functionDefinition)
{
	//cout << "addImplicitlyDeclaredVariablesInCurrentFunctionDefinitionToFunctionDefinition{}: functionDefinitionSource->name = " << functionDefinitionSource->name << endl;
	//cout << "addImplicitlyDeclaredVariablesInCurrentFunctionDefinitionToFunctionDefinition{}: functionDefinition->name = " << functionDefinition->name << endl;
	vector<NLCitem*>* functionDefinitionSourceArgumentList = &(functionDefinitionSource->parameters);
	vector<NLCitem*>* functionDefinitionArgumentList = &(functionDefinition->parameters);
	for(vector<NLCitem*>::iterator parametersIterator = functionDefinitionSourceArgumentList->begin(); parametersIterator < functionDefinitionSourceArgumentList->end(); parametersIterator++)
	{
		NLCitem* functionDeclarationSourceArgument = *parametersIterator;
		if(functionDeclarationSourceArgument->itemType == NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_INSTANCE_OR_CLASS_LIST)
		{
			//add a new function argument to the existing function argument list
			NLCitem* functionArgumentTemp = NULL;
			if(!findFunctionArgument(functionDefinitionArgumentList, functionDeclarationSourceArgument, NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_INSTANCE_OR_CLASS_LIST, &functionArgumentTemp))
			{
				#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
				cout << "addImplicitlyDeclaredVariablesInCurrentFunctionDefinitionToFunctionDefinition: functionDeclarationSourceArgument->name = " << functionDeclarationSourceArgument->name << endl;
				cout << "adding: functionDeclarationSourceArgument->name = " << functionDeclarationSourceArgument->name << " to " << "functionDefinition->functionName = " << functionDefinition->name << endl;
				#endif
				NLCitem* newFunctionArgument = new NLCitem(functionDeclarationSourceArgument);
				newFunctionArgument->itemType = NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_INSTANCE_OR_CLASS_LIST;
				functionDefinitionArgumentList->push_back(newFunctionArgument);
			}
		}
	}
}

//fine; this function is not duplicating arguments
void addImplicitlyDeclaredVariablesInCurrentFunctionDefinitionToFunctionDefinitionArguments(NLCclassDefinition* functionDefinitionSource, vector<NLCitem*>* functionDefinitionArgumentList)
{
	//cout << "addImplicitlyDeclaredVariablesInCurrentFunctionDefinitionToFunctionDefinitionArguments{}: functionDefinitionSource->name = " << functionDefinitionSource->name << endl;
	vector<NLCitem*>* functionDefinitionSourceArgumentList = &(functionDefinitionSource->parameters);
	for(vector<NLCitem*>::iterator parametersIterator = functionDefinitionSourceArgumentList->begin(); parametersIterator < functionDefinitionSourceArgumentList->end(); parametersIterator++)
	{
		NLCitem* functionDeclarationSourceArgument = *parametersIterator;
		if(functionDeclarationSourceArgument->itemType == NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_INSTANCE_OR_CLASS_LIST)
		{
			//add a new function argument to the existing function argument list
			NLCitem* functionArgumentTemp = NULL;
			if(!findFunctionArgument(functionDefinitionArgumentList, functionDeclarationSourceArgument, NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_INSTANCE_OR_CLASS_LIST, &functionArgumentTemp))
			{
				#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
				cout << "addImplicitlyDeclaredVariablesInCurrentFunctionDefinitionToFunctionDefinitionArguments: functionDeclarationSourceArgument->name = " << functionDeclarationSourceArgument->name << endl;
				cout << "adding: functionDeclarationSourceArgument->name = " << functionDeclarationSourceArgument->name << " to " << "functionDefinitionArgumentList" << endl;
				#endif
				NLCitem* newFunctionArgument = new NLCitem(functionDeclarationSourceArgument);
				newFunctionArgument->itemType = NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_INSTANCE_OR_CLASS_LIST;
				functionDefinitionArgumentList->push_back(newFunctionArgument);
			}
		}
	}
}

#endif
#endif
#endif
#endif


bool getFilesFromFileList(string inputListFileName, vector<string>* inputTextFileNameList, int* numberOfInputFilesInList)
{
	bool result = true;
	*numberOfInputFilesInList = 0;
	ifstream parseFileObject(inputListFileName.c_str());
	if(!parseFileObject.rdbuf()->is_open())
	{
		//txt file does not exist in current directory.
		#ifndef NLC_USE_LIBRARY_DISABLE_FUNCTIONS_LIST_WARNING
		cout << "Error: input list file does not exist in current directory: " << inputListFileName << endl;
		#endif
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
		*numberOfInputFilesInList = fileNameIndex;
	}
	#ifdef GIA_MAIN_DEBUG
	//cout << "*numberOfInputFilesInList = " <<* numberOfInputFilesInList << endl;
	#endif
	return result;
}

#endif

#ifdef NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_SUPPORT_ALPHANUMERIC_ENTITY_NAMES_ONLY
bool checkAlphaNumericEntityNames(vector<GIAentityNode*>* entityNodesActiveListComplete, int maxNumberSentences)
{
	bool result = true;
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode* entity = (*entityIter);
		if(!(entity->disabled))
		{
			//cout << "entity = " << entity->entityName << endl;
			if(!isStringNLPparsableWord(entity->entityName, false))
			{
				result = false;
				cout << "checkAlphaNumericEntityNames{}: user input error - entity names cannot start with numbers: " << entity->entityName << endl;
				exit(0);
			}
		}
	}
	return result;
}
#endif


bool createFunctionDefinitionClassDefinition(vector<NLCclassDefinition*>* classDefinitionList, string NLCfunctionName, int functionDefinitionIndex, bool libraryFunctionDeclaration)
{
	NLCclassDefinitionFunctionDependency* functionDependency = NULL;
	 
	string functionName = "";
	string functionOwnerName = "";
	string functionObjectName = "";
	bool hasFunctionOwnerClass = false;
	bool hasFunctionObjectClass = false;
	#ifdef NLC_USE_LIBRARY
	vector<NLCitem*> parameters;
	if(libraryFunctionDeclaration)
	{
		parseFunctionNameFromNLClibFunctionName(NLCfunctionName, &functionName, &functionOwnerName, &hasFunctionOwnerClass, &functionObjectName, &hasFunctionObjectClass, &parameters);	//gets "fight" from "dog#fight+box!argument1!argument2"	
	}
	else
	{
	#endif
		parseFunctionNameFromNLCfunctionName(NLCfunctionName, &functionName, &functionOwnerName, &hasFunctionOwnerClass, &functionObjectName, &hasFunctionObjectClass);	//gets "fight" from "dog#fight+box"
	#ifdef NLC_USE_LIBRARY
	}
	#endif
	
	string functionClassDefinitionName = functionName + NLC_CLASS_DEFINITIONS_CREATE_FUNCTION_DECLARATIONS_FOR_NEW_FUNCTION_DEFINITIONS_CLASS_DEFINITION_HIDDEN_NAME_APPEND;
	
	string functionOwnerClassDefinitionName = "";
	bool passNewFunctionDefinitionChecks = true;
	if(hasFunctionOwnerClass)
	{
		functionOwnerClassDefinitionName = generateClassName(functionOwnerName);
	}
	else
	{
		functionOwnerClassDefinitionName = generateClassName(NLC_CLASS_DEFINITIONS_SUPPORT_FUNCTIONS_WITHOUT_SUBJECT_ARTIFICIAL_CLASS_NAME);
	}
	if(passNewFunctionDefinitionChecks)
	{	
		#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED	
		cout << "createNewClassDefinitionFunctionDeclaration (!isReferenceElseFunctionDefinition): functionName  = " << functionName << endl;
		#endif
		bool isReferenceElseFunctionDefinition = false;		//ie isFunctionDefinition
		NLCclassDefinition* functionClassDefinition = createFunctionDefinitionClassDefinition(classDefinitionList, functionName, functionOwnerName, functionObjectName, hasFunctionOwnerClass, hasFunctionObjectClass, functionClassDefinitionName, functionOwnerClassDefinitionName, functionDefinitionIndex, isReferenceElseFunctionDefinition);
		#ifdef NLC_USE_LIBRARY
		if(functionClassDefinition != NULL)
		{
			addImplicitlyDeclaredVariablesInCurrentFunctionDefinitionArgumentsToFunctionDefinition(&parameters, functionClassDefinition);
		}
		if(libraryFunctionDeclaration)
		{
			functionClassDefinition->isLibraryFunctionDefinition = true;
		}
		#endif
	}
		
	return functionDependency;
}

NLCclassDefinition* createFunctionDefinitionClassDefinition(vector<NLCclassDefinition*>* classDefinitionList, string functionName, string functionOwnerName, string functionObjectName, bool hasFunctionOwnerClass, bool hasFunctionObjectClass, string functionClassDefinitionName, string functionOwnerClassDefinitionName, int functionDefinitionIndex, bool isReferenceElseFunctionDefinition)
{
	NLCclassDefinitionFunctionDependency* functionDependency = NULL;
	NLCclassDefinition* functionClassDefinition = NULL;
	
	#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE
	bool duplicateFunctionDeclarationDetected = false;
	bool foundFunctionDependencyInList = findFunctionDefinitionFunctionDependencyInList(classDefinitionList, functionName, functionOwnerName, functionObjectName, hasFunctionOwnerClass, hasFunctionObjectClass, &functionDependency);	//note at this stage only functionDefinition functionDependencies have been created (so the functionDefintion check is not actually required)...
	if(foundFunctionDependencyInList)
	{
		cout << "createFunctionDefinitionClassDefinition{}:createNewClassDefinitionFunctionDeclaration{} error: duplicate functionDefinition classDefinition defined" << endl;
		exit(0);
	}
	else
	{
		functionDependency = new NLCclassDefinitionFunctionDependency();
		functionDependency->functionDefinitionListIndex = functionDefinitionIndex;

		functionDependency->functionName = functionName;
		functionDependency->functionOwnerName = functionOwnerName;
		functionDependency->functionObjectName = functionObjectName;
		functionDependency->hasFunctionOwnerClass = hasFunctionOwnerClass;
		functionDependency->hasFunctionObjectClass = hasFunctionObjectClass;
		functionDependency->isReferenceElseFunctionDefinition = isReferenceElseFunctionDefinition;	
	#endif

		//cout << "functionOwnerClassDefinitionName = " << functionOwnerClassDefinitionName << endl;

		bool foundFunctionOwnerClassDefinition = false;
		NLCclassDefinition* functionOwnerClassDefinition = findClassDefinition(classDefinitionList, functionOwnerClassDefinitionName, &foundFunctionOwnerClassDefinition);	//see if class definition already exists
		if(!foundFunctionOwnerClassDefinition)
		{
			functionOwnerClassDefinition = new NLCclassDefinition(functionOwnerClassDefinitionName);
			classDefinitionList->push_back(functionOwnerClassDefinition);
			//cout << "!foundClassDefinition" << endl;
		}

		//cout << "functionClassDefinitionName: " << functionClassDefinitionName << endl;

		bool foundFunctionClassDefinition = false;
		functionClassDefinition = findClassDefinition(classDefinitionList, functionClassDefinitionName, &foundFunctionClassDefinition);	//see if class definition already exists
		if(!foundFunctionClassDefinition)
		{
			//cout << "new NLCclassDefinition(" << functionClassDefinitionName << endl;
			functionClassDefinition = new NLCclassDefinition(functionClassDefinitionName);
			classDefinitionList->push_back(functionClassDefinition);
		}

		functionClassDefinition->functionNameSpecial = generateFunctionName(functionName);

		functionClassDefinition->isActionOrConditionInstanceNotClass = true;
		//cout << "functionOwnerClassDefinition->isActionOrConditionInstanceNotClass" << endl;

		functionOwnerClassDefinition->functionList.push_back(functionClassDefinition);

		#ifdef NLC_FUNCTIONS_SUPPORT_PLURAL_SUBJECTS
		if(hasFunctionOwnerClass)
		{
			//added 1l1a for dynamic casting of children
			NLCitem* classDeclarationFunctionOwnerItem = new NLCitem(functionOwnerName, NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION_OWNER);	//changed from NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION_OWNER 1p4a
			functionClassDefinition->parameters.push_back(classDeclarationFunctionOwnerItem);
		}
		#endif

		NLCitem* classDeclarationFunctionItem = new NLCitem(functionName, NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION);	//changed from NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION 1p4a
		functionClassDefinition->parameters.push_back(classDeclarationFunctionItem);

		if(hasFunctionObjectClass)
		{
			NLCitem* classDeclarationFunctionObjectItem = new NLCitem(functionObjectName, NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION_OBJECT);		//changed from NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION_OBJECT 1p4a
			functionClassDefinition->parameters.push_back(classDeclarationFunctionObjectItem);
		}

	#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE
		functionClassDefinition->functionDependency = functionDependency;
	}
	#endif
	
	return functionClassDefinition;
}

	




