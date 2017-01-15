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
 * Project Version: 1p3e 25-June-2015
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
void reconcileClassDefinitionListFunctionDeclarationArgumentsBasedOnImplicitlyDeclaredVariablesInCurrentFunctionDefinition(NLCcodeblock* firstCodeBlockInTree, vector<NLCclassDefinition*>* classDefinitionList, NLCclassDefinitionFunctionDependency* functionDependency)
{
	//reconcile function arguments (class function header) - NB code function reference arguments are reconciled in printCodeBlocks()  

	string functionName = functionDependency->functionName;
	string functionOwnerName = functionDependency->functionOwnerName;
	string functionObjectName = functionDependency->functionObjectName;
	bool hasFunctionOwnerClass = functionDependency->hasFunctionOwnerClass;
	bool hasFunctionObjectClass = functionDependency->hasFunctionObjectClass;

	#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
	bool findFunctionOwnerExactMatch = true;
	bool findFunctionObjectExactMatch = true;
	bool rearrangeClassList = true;
	bool isReferenceElseFunctionDefinition = false;
	NLCclassDefinition* functionDeclaration = NULL;
	//NB findFunctionDeclarationClassDefinition parses (reconcile/rearranges) function declaration classDefinitions only (isReferenceElseFunctionDefinition==true)
		//but what if there are multiple function declarations (won't each one need to have its arguments reconciled?)
	if(findFunctionDeclarationClassDefinition(classDefinitionList, functionName, functionOwnerName, functionObjectName, hasFunctionOwnerClass, hasFunctionObjectClass, findFunctionOwnerExactMatch, findFunctionObjectExactMatch, &functionDeclaration, rearrangeClassList, isReferenceElseFunctionDefinition))
	{
		#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
		cout << "addImplicitlyDeclaredVariablesInCurrentFunctionDefinitionToFunctionDeclaration" << endl;
		#endif
		#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_BASED_ON_IMPLICITLY_DECLARED_VARIABLES_IN_CURRENT_FUNCTION_DEFINITION
		//adds the arguments from firstCodeBlockInTree (NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_INSTANCE_OR_CLASS_LIST) to the functionDeclaration classDefinition
		addImplicitlyDeclaredVariablesInCurrentFunctionDefinitionToFunctionDeclaration(&(firstCodeBlockInTree->parameters), functionDeclaration);
		
		#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE_ACTIVE
		//propogates arguments to parent ("dependency child") function?
		for(vector<NLCclassDefinitionFunctionDependency*>::iterator functionDependencyIter = functionDependency->functionDependencyList.begin(); functionDependencyIter != functionDependency->functionDependencyList.end(); functionDependencyIter++)
		{
			NLCclassDefinitionFunctionDependency* functionDependencyChild = *functionDependencyIter;
			NLCclassDefinition* functionDeclaration2 = NULL;
			if(findFunctionDeclarationClassDefinition(classDefinitionList, functionDependencyChild->functionName, functionDependencyChild->functionOwnerName, functionDependencyChild->functionObjectName, functionDependencyChild->hasFunctionOwnerClass, functionDependencyChild->hasFunctionObjectClass, findFunctionOwnerExactMatch, findFunctionObjectExactMatch, &functionDeclaration2, rearrangeClassList, isReferenceElseFunctionDefinition))	//should find exact match as class definitions have already been created for all new function definitions (and their implicit declarations have been added to their function argument lists)
			{
				addImplicitlyDeclaredVariablesInCurrentFunctionDeclarationToFunctionDeclaration(functionDeclaration2, functionDeclaration);
				addImplicitlyDeclaredVariablesInCurrentFunctionDeclarationToFunctionDefinition(functionDeclaration, &(firstCodeBlockInTree->parameters));
			}
		}
		#endif
		#endif
	}
	#else
	cout << "reconcileClassDefinitionListFunctionDeclarationArgumentsBasedOnImplicitlyDeclaredVariablesInCurrentFunctionDefinition{} error: !NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED no longer supported" << endl;
	exit(0);
	#endif
}

#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_BASED_ON_IMPLICITLY_DECLARED_VARIABLES_IN_CURRENT_FUNCTION_DEFINITION
#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED

void addImplicitlyDeclaredVariablesInCurrentFunctionDefinitionToFunctionDeclaration(vector<NLCitem*>* functionDefinitionSourceArgumentList, NLCclassDefinition* functionDeclaration)
{
	//cout << "addImplicitlyDeclaredVariablesInCurrentFunctionDefinitionToFunctionDeclaration{}: functionDeclaration->name = " << functionDeclaration->name << endl;
	vector<NLCitem*>* functionDeclarationArgumentList = &(functionDeclaration->parameters);
	for(vector<NLCitem*>::iterator parametersIterator = functionDefinitionSourceArgumentList->begin(); parametersIterator < functionDefinitionSourceArgumentList->end(); parametersIterator++)
	{
		NLCitem* functionDefinitionSourceArgument = *parametersIterator;
		if(functionDefinitionSourceArgument->itemType == NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_INSTANCE_OR_CLASS_LIST)
		{
			//add a new function argument to the existing function argument list
			NLCitem* functionArgumentTemp = NULL;
			if(!findFunctionArgument(functionDeclarationArgumentList, functionDefinitionSourceArgument, NLC_ITEM_TYPE_FUNCTION_DECLARATION_ARGUMENT_INSTANCE_OR_CLASS_LIST, &functionArgumentTemp))
			{
				#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
				cout << "addImplicitlyDeclaredVariablesInCurrentfunctionDefinitionSourceToFunctionDeclaration: functionDefinitionSourceArgument->name = " << functionDefinitionSourceArgument->name << endl;
				cout << "adding: functionDefinitionSourceArgument->name = " << functionDefinitionSourceArgument->name << " to " << "functionDeclaration->functionName = " << functionDeclaration->name << endl;
				#endif
				NLCitem* newFunctionArgument = new NLCitem(functionDefinitionSourceArgument);	//NLC by default uses plural (lists) not singular entities
				newFunctionArgument->itemType = NLC_ITEM_TYPE_FUNCTION_DECLARATION_ARGUMENT_INSTANCE_OR_CLASS_LIST;
				functionDeclarationArgumentList->push_back(newFunctionArgument);
			}
		}
	}
}
#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE
void addImplicitlyDeclaredVariablesInCurrentFunctionDeclarationToFunctionDeclaration(NLCclassDefinition* functionDeclarationSource, NLCclassDefinition* functionDeclaration)
{
	//cout << "addImplicitlyDeclaredVariablesInCurrentFunctionDeclarationToFunctionDeclaration{}: functionDeclarationSource->name = " << functionDeclarationSource->name << endl;
	//cout << "addImplicitlyDeclaredVariablesInCurrentFunctionDeclarationToFunctionDeclaration{}: functionDeclaration->name = " << functionDeclaration->name << endl;
	vector<NLCitem*>* functionDeclarationSourceArgumentList = &(functionDeclarationSource->parameters);
	vector<NLCitem*>* functionDeclarationArgumentList = &(functionDeclaration->parameters);
	for(vector<NLCitem*>::iterator parametersIterator = functionDeclarationSourceArgumentList->begin(); parametersIterator < functionDeclarationSourceArgumentList->end(); parametersIterator++)
	{
		NLCitem* functionDeclarationSourceArgument = *parametersIterator;
		if(functionDeclarationSourceArgument->itemType == NLC_ITEM_TYPE_FUNCTION_DECLARATION_ARGUMENT_INSTANCE_OR_CLASS_LIST)
		{
			//add a new function argument to the existing function argument list
			NLCitem* functionArgumentTemp = NULL;
			if(!findFunctionArgument(functionDeclarationArgumentList, functionDeclarationSourceArgument, NLC_ITEM_TYPE_FUNCTION_DECLARATION_ARGUMENT_INSTANCE_OR_CLASS_LIST, &functionArgumentTemp))
			{
				#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
				cout << "addImplicitlyDeclaredVariablesInCurrentFunctionDeclarationToFunctionDeclaration: functionDeclarationSourceArgument->name = " << functionDeclarationSourceArgument->name << endl;
				cout << "adding: functionDeclarationSourceArgument->name = " << functionDeclarationSourceArgument->name << " to " << "functionDeclaration->functionName = " << functionDeclaration->name << endl;
				#endif
				NLCitem* newFunctionArgument = new NLCitem(functionDeclarationSourceArgument);
				newFunctionArgument->itemType = NLC_ITEM_TYPE_FUNCTION_DECLARATION_ARGUMENT_INSTANCE_OR_CLASS_LIST;
				functionDeclarationArgumentList->push_back(newFunctionArgument);
			}
		}
	}
}

void addImplicitlyDeclaredVariablesInCurrentFunctionDeclarationToFunctionDefinition(NLCclassDefinition* functionDeclarationSource, vector<NLCitem*>* functionDefinitionArgumentList)
{
	//cout << "addImplicitlyDeclaredVariablesInCurrentFunctionDeclarationToFunctionDefinition{}: functionDeclarationSource->name = " << functionDeclarationSource->name << endl;
	vector<NLCitem*>* functionDeclarationSourceArgumentList = &(functionDeclarationSource->parameters);
	for(vector<NLCitem*>::iterator parametersIterator = functionDeclarationSourceArgumentList->begin(); parametersIterator < functionDeclarationSourceArgumentList->end(); parametersIterator++)
	{
		NLCitem* functionDeclarationSourceArgument = *parametersIterator;
		if(functionDeclarationSourceArgument->itemType == NLC_ITEM_TYPE_FUNCTION_DECLARATION_ARGUMENT_INSTANCE_OR_CLASS_LIST)
		{
			//add a new function argument to the existing function argument list
			NLCitem* functionArgumentTemp = NULL;
			if(!findFunctionArgument(functionDefinitionArgumentList, functionDeclarationSourceArgument, NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_INSTANCE_OR_CLASS_LIST, &functionArgumentTemp))
			{
				#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
				cout << "addImplicitlyDeclaredVariablesInCurrentFunctionDeclarationToFunctionDefinition: functionDeclarationSourceArgument->name = " << functionDeclarationSourceArgument->name << endl;
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
	if(!parseFileObject.rdbuf( )->is_open())
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


NLCclassDefinitionFunctionDependency* createFunctionDependencyForNewFunctionDefinition(string NLCfunctionName, vector<NLCclassDefinition*>* classDefinitionList, vector<NLCclassDefinitionFunctionDependency*>* functionDependencyList, int functionDefinitionIndex, bool libraryFunctionDeclaration)
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
	
	#ifdef NLC_CLASS_DEFINITIONS_CREATE_FUNCTION_DECLARATIONS_FOR_NEW_FUNCTION_DEFINITIONS
	bool createClassDefinition = true;
	#else
	bool createClassDefinition = false;
	#endif
	
	string functionClassDefinitionName = "";
	/*
	if(libraryFunctionDeclaration)
	{
		functionClassDefinitionName = functionName;
	}
	else
	{
	*/
	functionClassDefinitionName = functionName + NLC_CLASS_DEFINITIONS_CREATE_FUNCTION_DECLARATIONS_FOR_NEW_FUNCTION_DEFINITIONS_CLASS_DEFINITION_HIDDEN_NAME_APPEND;
	/*
	}
	*/
	
	string functionOwnerClassDefinitionName = "";
	bool passNewFunctionDefinitionChecks = true;
	if(hasFunctionOwnerClass)
	{
		functionOwnerClassDefinitionName = generateClassName(functionOwnerName);
	}
	else
	{
		#ifdef NLC_CLASS_DEFINITIONS_SUPPORT_FUNCTIONS_WITHOUT_SUBJECT
		functionOwnerClassDefinitionName = generateClassName(NLC_CLASS_DEFINITIONS_SUPPORT_FUNCTIONS_WITHOUT_SUBJECT_ARTIFICIAL_CLASS_NAME);
		#else
		passNewFunctionDefinitionChecks = false;
		#endif
	}
	if(passNewFunctionDefinitionChecks)
	{	
		#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED	
		cout << "createNewClassDefinitionFunctionDeclaration (!isReferenceElseFunctionDefinition): functionName  = " << functionName << endl;
		#endif
		NLCclassDefinitionFunctionDependency* parentFunctionDependencyTemp = NULL;
		bool hasParent = false;
		bool isReferenceElseFunctionDefinition = false;		//ie isFunctionDefinition
		functionDependency = createNewClassDefinitionFunctionDeclaration(classDefinitionList, functionName, functionOwnerName, functionObjectName, hasFunctionOwnerClass, hasFunctionObjectClass, functionClassDefinitionName, functionOwnerClassDefinitionName, hasParent, parentFunctionDependencyTemp, functionDependencyList, isReferenceElseFunctionDefinition, createClassDefinition);
	}
	
	functionDependency->functionDefinitionListIndex = functionDefinitionIndex;
	
	return functionDependency;
}

NLCclassDefinitionFunctionDependency* createNewClassDefinitionFunctionDeclaration(vector<NLCclassDefinition*>* classDefinitionList, string functionName, string functionOwnerName, string functionObjectName, bool hasFunctionOwnerClass, bool hasFunctionObjectClass, string functionClassDefinitionName, string functionOwnerClassDefinitionName, bool hasParent, NLCclassDefinitionFunctionDependency* parentFunctionDependency, vector<NLCclassDefinitionFunctionDependency*>* functionDependencyList, bool isReferenceElseFunctionDefinition, bool createClassDefinition)
{
	NLCclassDefinitionFunctionDependency* functionDependency = NULL;

	#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE
	bool duplicateFunctionDeclarationDetected = false;
	bool foundFunctionDependencyInList = findFunctionDependencyInList(functionDependencyList, functionName, functionOwnerName, functionObjectName, hasFunctionOwnerClass, hasFunctionObjectClass, &functionDependency);
	if(foundFunctionDependencyInList)
	{
		#ifdef NLC_CLASS_DEFINITIONS_CREATE_FUNCTION_DECLARATIONS_FOR_NEW_FUNCTION_DEFINITIONS
		#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE
		if(!isReferenceElseFunctionDefinition)
		{
			//note generateClassHeirarchyFunctions has not yet been executed; functionReference functionDependencies have not yet been created and there have been 2 identical functions definitions created by the user (same functionSubjectName, functionName, and functionObjectName)
			cout << "createFunctionDependencyForNewFunctionDefinition{}:createNewClassDefinitionFunctionDeclaration{} error: duplicate functionDefinition functionDependency defined" << endl;
			exit(0);
		}	
		else
		{
		#endif
		#endif
			//cout << "findFunctionDependencyInList" << endl;
			if(hasParent)
			{
				//cout << "findFunctionDependencyInList" << endl;
				NLCclassDefinitionFunctionDependency* functionDependenciesInParentTemp = NULL;
				bool foundFunctionDependencyInParent = findFunctionDependencyInParent(parentFunctionDependency, functionName, functionOwnerName, functionObjectName, hasFunctionOwnerClass, hasFunctionObjectClass, &functionDependenciesInParentTemp);
				if(!foundFunctionDependencyInParent)
				{
					//cout << "!foundFunctionDependencyInParent" << endl;
					parentFunctionDependency->functionDependencyList.push_back(functionDependency);
				}
				else
				{
					//cout << "foundFunctionDependencyInParent" << endl;
					//duplicate function declarations will be ignored
					duplicateFunctionDeclarationDetected = true;
				}
			}
			#ifdef NLC_CLASS_DEFINITIONS_CREATE_FUNCTION_DECLARATIONS_FOR_NEW_FUNCTION_DEFINITIONS
			if(!isReferenceElseFunctionDefinition)
			{
				functionDependency->isReferenceElseFunctionDefinition = false;	//upgrade isReferenceElseFunctionDefinition value (!isReferenceElseFunctionDefinition takes priority)
			}
			#endif
		#ifdef NLC_CLASS_DEFINITIONS_CREATE_FUNCTION_DECLARATIONS_FOR_NEW_FUNCTION_DEFINITIONS
		#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE
		}
		#endif
		#endif
	}
	else
	{
		functionDependency = new NLCclassDefinitionFunctionDependency();
		functionDependency->functionName = functionName;
		functionDependency->functionOwnerName = functionOwnerName;
		functionDependency->functionObjectName = functionObjectName;
		functionDependency->hasFunctionOwnerClass = hasFunctionOwnerClass;
		functionDependency->hasFunctionObjectClass = hasFunctionObjectClass;
		#ifdef NLC_CLASS_DEFINITIONS_CREATE_FUNCTION_DECLARATIONS_FOR_NEW_FUNCTION_DEFINITIONS
		functionDependency->isReferenceElseFunctionDefinition = isReferenceElseFunctionDefinition;	
		#endif
		if(hasParent)
		{
			parentFunctionDependency->functionDependencyList.push_back(functionDependency);
		}
		functionDependencyList->push_back(functionDependency);
	}
	#endif
	#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE_IGNORE_DUPLICATE_FUNCTION_DELCARATIONS
	if(!foundFunctionDependencyInList)
	{
	#endif
		if(createClassDefinition)
		{
			//cout << "functionOwnerClassDefinitionName = " << functionOwnerClassDefinitionName << endl;
			
			bool foundClassDefinition = false;
			NLCclassDefinition* functionOwnerClassDefinition = findClassDefinition(classDefinitionList, functionOwnerClassDefinitionName, &foundClassDefinition);	//see if class definition already exists
			if(!foundClassDefinition)
			{
				functionOwnerClassDefinition = new NLCclassDefinition(functionOwnerClassDefinitionName);
				classDefinitionList->push_back(functionOwnerClassDefinition);
				//cout << "!foundClassDefinition" << endl;
			}
			
			//cout << "functionClassDefinitionName: " << functionClassDefinitionName << endl;

			bool foundTargetClassDefinition = false;
			NLCclassDefinition* functionClassDefinition = findClassDefinition(classDefinitionList, functionClassDefinitionName, &foundTargetClassDefinition);	//see if class definition already exists
			if(!foundTargetClassDefinition)
			{
				//cout << "new NLCclassDefinition(" << functionClassDefinitionName << endl;
				functionClassDefinition = new NLCclassDefinition(functionClassDefinitionName);
				classDefinitionList->push_back(functionClassDefinition);
			}

			#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE
			functionClassDefinition->functionDependency = functionDependency;
			#endif

			functionClassDefinition->functionNameSpecial = generateFunctionName(functionName);
			/*no longer supported;
			#ifdef NLC_SUPPORT_INPUT_FUNCTION_LISTS_CHECK_ACTION_SUBJECT_CONTENTS_FOR_IMPLICITLY_DECLARED_PARAMETERS
			functionClassDefinition->actionOrConditionInstance = targetEntity;
			#endif
			*/

			functionClassDefinition->isActionOrConditionInstanceNotClass = true;
			//cout << "functionOwnerClassDefinition->isActionOrConditionInstanceNotClass" << endl;

			functionOwnerClassDefinition->functionList.push_back(functionClassDefinition);

			#ifdef NLC_FUNCTIONS_SUPPORT_PLURAL_SUBJECTS
			if(hasFunctionOwnerClass)
			{
				//added 1l1a for dynamic casting of children
				NLCitem* classDeclarationFunctionOwnerItem = new NLCitem(functionOwnerName, NLC_ITEM_TYPE_FUNCTION_DECLARATION_ARGUMENT_FUNCTION_OWNER);
				functionClassDefinition->parameters.push_back(classDeclarationFunctionOwnerItem);
			}
			#endif
			
			NLCitem* classDeclarationFunctionItem = new NLCitem(functionName, NLC_ITEM_TYPE_FUNCTION_DECLARATION_ARGUMENT_FUNCTION);
			functionClassDefinition->parameters.push_back(classDeclarationFunctionItem);
			
			if(hasFunctionObjectClass)
			{
				//NLCitem* classDeclarationFunctionObjectItem = new NLCitem(functionObject, NLC_ITEM_TYPE_FUNCTION_DECLARATION_ARGUMENT_FUNCTION_OBJECT);
				NLCitem* classDeclarationFunctionObjectItem = new NLCitem(functionObjectName, NLC_ITEM_TYPE_FUNCTION_DECLARATION_ARGUMENT_FUNCTION_OBJECT);
				functionClassDefinition->parameters.push_back(classDeclarationFunctionObjectItem);
			}

			/*no longer supported;
			#ifdef NLC_INTERPRET_ACTION_PROPERTIES_AND_CONDITIONS_AS_FUNCTION_ARGUMENTS
			//#ifdef NLC_SUPPORT_INPUT_FUNCTION_LISTS	//shouldn't this preprocessor requirement be enforced?
			generateFunctionDeclarationArgumentsWithActionConceptInheritance(targetEntity, &(functionClassDefinition->parameters));
			//#endif
			#endif
			*/
		}

	#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE_IGNORE_DUPLICATE_FUNCTION_DELCARATIONS
	}
	#endif
	
	return functionDependency;
}

	




