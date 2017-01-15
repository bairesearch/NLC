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
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2014 Baxter AI (baxterai.com)
 * Project: Natural Language Programming Interface (compiler)
 * Project Version: 1k10a 14-October-2014
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/



#include <ctime>
#include <cstdlib>	//for random number generation
#include <cmath>

#include "NLCtranslator.h"
#include "NLCtranslatorCodeBlocks.h"
#include "NLCtranslatorCodeBlocksLogicalConditions.h"	//required for tagAllEntitiesInSentenceSubsetAsPertainingToLogicalConditionOperation
#include "NLCtranslatorClassDefinitions.h"
#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS
#include "GIAtranslatorDefs.h"
#endif

#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS
NLClogicalConditionConjunctionContainer::NLClogicalConditionConjunctionContainer(void)
{
	entity = NULL;
	optimumPathIndex = 0;
}
NLClogicalConditionConjunctionContainer::NLClogicalConditionConjunctionContainer(GIAentityNode * currentEntity)
{
	entity = currentEntity;
	optimumPathIndex = 0;
}
NLClogicalConditionConjunctionContainer::~NLClogicalConditionConjunctionContainer(void)
{
}
#endif

bool translateNetwork(NLCcodeblock * firstCodeBlockInTree, vector<NLCclassDefinition *> * classDefinitionList, vector<GIAentityNode*> * entityNodesActiveListComplete, int maxNumberSentences, string NLCfunctionName, NLCfunction * currentNLCfunctionInList, bool useNLCpreprocessor)
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
	#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS
	//NLC translator Part prep B.
	if(!removeRedundantConditionConjunctions(entityNodesActiveListComplete, maxNumberSentences))
	{
		result = false;
	}
	#endif

	//NLC translator Part prep C.
	if(!identifyAndTagAllLogicalConditionOperations(entityNodesActiveListComplete, maxNumberSentences))
	{
		result = false;
	}
	#endif

	#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
	#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS
	//NLC translator Part prep B.
	if(!removeRedundantConditionConjunctions(entityNodesActiveListComplete, maxNumberSentences))
	{
		result = false;
	}
	#endif

	//NLC translator Part prep C.
	if(!identifyAndTagAllLogicalConditionOperations(entityNodesActiveListComplete, maxNumberSentences))
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
	if(!generateCodeBlocks(firstCodeBlockInTree, entityNodesActiveListComplete, maxNumberSentences, NLCfunctionName, currentNLCfunctionInList))
	{
		result = false;
	}

	//NLC translator Part 2.
	if(!generateClassHeirarchy(classDefinitionList, entityNodesActiveListComplete, maxNumberSentences))
	{
		result = false;
	}
	return result;
}

/*
#ifdef NLC_CATEGORIES_TEST_PLURALITY_ENFORCE
#ifdef NLC_USE_PREPROCESSOR
bool identifyImplicitPluralLogicalConditionOperationsObjects(vector<GIAentityNode*> * entityNodesActiveListComplete, int maxNumberSentences)
{
	bool result = true;
	
	for(int sentenceIndex=GIA_NLP_START_SENTENCE_INDEX; sentenceIndex <= maxNumberSentences; sentenceIndex++)
	{
		for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
		{
			GIAentityNode * conditionEntity = (*entityIter);
			if(checkSentenceIndexParsingCodeBlocks(conditionEntity, sentenceIndex, true))	//could be set to false instead
			{
				//because GIA Sentence objects are unavailable to NLC, must parse all entities including disabled entites and locate matching entities (in same sentence and with entityIndex+1 of "for" condition):
				for(vector<GIAentityNode*>::iterator entityIter2 = entityNodesActiveListComplete->begin(); entityIter2 != entityNodesActiveListComplete->end(); entityIter2++)
				{
					GIAentityNode * entity2 = (*entityIter);
					if(entity2->sentenceIndexTemp == sentenceIndex)
					{
						if(entity2->entityIndexTemp = conditionEntity->entityIndexTemp+1)
						{	
							#ifdef NLC_USE_PREPROCESSOR
							if(entity2->entityIndexTemp == 1)	//NLP parsable phrase: "every chicken..."
							#else
							if(entity2->entityIndexTemp == 2)	//Sentence: "For every chicken..."
							#endif
							{
								//eg "for each chicken" / "for every chicken" / "while each chicken" / "while every chicken"
								bool wordImmediatelySucceedingForFound = textInTextArray(entity2->entityName, logicalConditionOperationsWordImmediatelySucceedingForArray, NLC_LOGICAL_CONDITION_OPERATIONS_WORD_IMMEDIATELY_SUCCEEDING_FOR_NUMBER_OF_TYPES);
								if(wordImmediatelySucceedingForFound)
								{
									cout << "identifyImplicitPluralLogicalConditionOperationsObjects(): wordImmediatelySucceedingForFound" << endl;
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
#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS
bool removeRedundantConditionConjunctions(vector<GIAentityNode*> * entityNodesActiveListComplete, int maxNumberSentences)
{
	bool result = true;
	for(int sentenceIndex=GIA_NLP_START_SENTENCE_INDEX; sentenceIndex <= maxNumberSentences; sentenceIndex++)
	{
		NLClogicalConditionConjunctionContainer * logicalConditionConjunctionContainerFirstInOptimumPath = NULL;
		int maximumNumberOfConjunctions = 0;
		for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
		{
			GIAentityNode * conditionEntity = (*entityIter);
			if(conditionEntity->isCondition)
			{
				if(checkSentenceIndexParsingCodeBlocks(conditionEntity, sentenceIndex, false))
				{
					int conjunctionType = INT_DEFAULT_VALUE;
					bool conjunctionConditionFound = textInTextArray(conditionEntity->entityName, entityCoordinatingConjunctionArray, ENTITY_COORDINATINGCONJUNCTION_ARRAY_NUMBER_OF_TYPES, &conjunctionType);
					if(conjunctionConditionFound)
					{
						NLClogicalConditionConjunctionContainer * logicalConditionConjunctionContainer = new NLClogicalConditionConjunctionContainer(conditionEntity);
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
				GIAentityNode * conditionEntity = (*entityIter);
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
								GIAentityNode * logicalConditionConjunctionObjectEntity = (conditionEntity->conditionObjectEntity->back())->entity;
								GIAentityNode * logicalConditionConjunctionSubjectEntity = (conditionEntity->conditionSubjectEntity->back())->entity;
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

int addConjunctionsConnectedToConditionConjunctionObject(GIAentityNode * conditionEntity, NLClogicalConditionConjunctionContainer * logicalConditionConjunctionContainer, int sentenceIndex)
{
	int maximumNumberOfConjunctions = 0;
	GIAentityNode * conditionObjectEntity = NULL;
	GIAentityConnection * conditionConnection = NULL;
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
				GIAentityConnection * conditionConnection2 = (*connectionIter);
				GIAentityNode * conditionEntity2 = conditionConnection2->entity;
				if(checkSentenceIndexParsingCodeBlocks(conditionEntity2, conditionConnection2, sentenceIndex, false))
				{
					int conjunctionType = INT_DEFAULT_VALUE;
					bool conjunctionConditionFound = textInTextArray(conditionEntity2->entityName, entityCoordinatingConjunctionArray, ENTITY_COORDINATINGCONJUNCTION_ARRAY_NUMBER_OF_TYPES, &conjunctionType);
					if(conjunctionConditionFound)
					{
						NLClogicalConditionConjunctionContainer * logicalConditionConjunctionContainer2 = new NLClogicalConditionConjunctionContainer(conditionEntity2);
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
		cout << "addConjunctionsConnectedToConditionConjunctionObject() error: !conditionHasObject" << endl;
	}
	return maximumNumberOfConjunctions + 1;
}

bool traceConditionConjunctionsOptimiumPathAndSeeIfConditionConjunctionEntityIsOnIt(NLClogicalConditionConjunctionContainer * logicalConditionConjunctionContainer, GIAentityNode * logicalConditionConjunctionToTest)
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

bool identifyAndTagAllLogicalConditionOperations(vector<GIAentityNode*> * entityNodesActiveListComplete, int maxNumberSentences)
{
	bool result = true;
	
	for(int sentenceIndex=GIA_NLP_START_SENTENCE_INDEX; sentenceIndex <= maxNumberSentences; sentenceIndex++)
	{
		for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
		{
			GIAentityNode * conditionEntity = (*entityIter);
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
					//because GIA Sentence objects are unavailable to NLC, must parse all entities including disabled entites and locate matching entities (in same sentence and with entityIndex+1 of "for" condition):
					for(vector<GIAentityNode*>::iterator entityIter2 = entityNodesActiveListComplete->begin(); entityIter2 != entityNodesActiveListComplete->end(); entityIter2++)
					{
						GIAentityNode * entity2 = (*entityIter);
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

						GIAentityNode * conditionSubject = NULL;
						GIAentityNode * conditionObject = NULL;
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
								cout << "identifyAndTagAllLogicalConditionOperations() error: NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_BASED_ON_CONCEPTS only handles substance concepts. GIA_CREATE_SUBSTANCE_CONCEPTS_FOR_ALL_SENTENCES_WITH_CONCEPTS must be enabled." << endl;
								cout << "conditionObject = " << conditionObject->entityName;
							}
							else
							{
								tagAllEntitiesInSentenceSubsetAsPertainingToLogicalConditionOperation(conditionObject, sentenceIndex, true);
							}
							if(conditionSubject->isConcept)
							{
								cout << "identifyAndTagAllLogicalConditionOperations() error: NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_BASED_ON_CONCEPTS only handles substance concepts. GIA_CREATE_SUBSTANCE_CONCEPTS_FOR_ALL_SENTENCES_WITH_CONCEPTS must be enabled." << endl;
								cout << "conditionSubject = " << conditionSubject->entityName;
							}
							else
							{
								tagAllEntitiesInSentenceSubsetAsPertainingToLogicalConditionOperation(conditionSubject, sentenceIndex, true);
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

#ifdef NLC_SUPPORT_INPUT_FILE_LISTS
#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_BASED_ON_IMPLICITLY_DECLARED_VARIABLES_IN_CURRENT_FUNCTION_DEFINITION
void reconcileClassDefinitionListFunctionDeclarationArgumentsBasedOnImplicitlyDeclaredVariablesInCurrentFunctionDefinition(NLCcodeblock * firstCodeBlockInTree, vector<NLCclassDefinition *> * classDefinitionList, string NLCfunctionName)
{
	//reconcile function arguments (both class function header and code function reference)
	string functionName = "";
	string functionOwnerName = "";
	bool hasFunctionOwnerClass = false;
	string functionObjectName = "";
	bool hasFunctionObjectClass = false;
	parseFunctionNameFromNLCfunctionName(NLCfunctionName, &functionName, &functionOwnerName, &hasFunctionOwnerClass, &functionObjectName, &hasFunctionObjectClass);	//gets "fight" from "dog::fight"

	#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_BASED_ON_IMPLICITLY_DECLARED_VARIABLES_IN_CURRENT_FUNCTION_DEFINITION_ADVANCED
	NLCclassDefinition * functionClassDeclaration = NULL;
	//reconcile function execution "The animal eats the object."/animal->eat(vector object) with function definition "animal#eat+object"/animal::eat(vector object)	
	bool findFunctionOwnerExactMatch = true;
	bool findFunctionObjectExactMatch = true;
	#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_BASED_ON_IMPLICITLY_DECLARED_VARIABLES_IN_CURRENT_FUNCTION_DEFINITION_ADVANCED
	cout << "findFunctionOwnerExactMatch && findFunctionObjectExactMatch" << endl;
	#endif
	if(findFunctionDeclarationClassDefinition(classDefinitionList, functionName, functionOwnerName, functionObjectName, hasFunctionOwnerClass, hasFunctionObjectClass, findFunctionOwnerExactMatch, findFunctionObjectExactMatch, &functionClassDeclaration))
	{
		addImplicitlyDeclaredVariablesInCurrentFunctionDefinitionToClassDefinition(functionClassDeclaration, &(firstCodeBlockInTree->parameters));
	}
	else
	{
		//reconcile function execution "The animal eats the ball."/dog->eat(vector ball) with function definition "animal#eat+object"/animal::eat(vector object)	
		findFunctionOwnerExactMatch = true;
		findFunctionObjectExactMatch = false;
		#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_BASED_ON_IMPLICITLY_DECLARED_VARIABLES_IN_CURRENT_FUNCTION_DEFINITION_ADVANCED
		cout << "findFunctionOwnerExactMatch && !findFunctionObjectExactMatch" << endl;
		#endif
		if(findFunctionDeclarationClassDefinition(classDefinitionList, functionName, functionOwnerName, functionObjectName, hasFunctionOwnerClass, hasFunctionObjectClass, findFunctionOwnerExactMatch, findFunctionObjectExactMatch, &functionClassDeclaration))
		{
			addImplicitlyDeclaredVariablesInCurrentFunctionDefinitionToClassDefinition(functionClassDeclaration, &(firstCodeBlockInTree->parameters));
		}
		else
		{
			//reconcile function execution "The dog eats the object."/dog->eat(vector object) with function definition "animal#eat+object"/animal::eat(vector object)	
			findFunctionOwnerExactMatch = false;
			findFunctionObjectExactMatch = true;
			#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_BASED_ON_IMPLICITLY_DECLARED_VARIABLES_IN_CURRENT_FUNCTION_DEFINITION_ADVANCED
			cout << "!findFunctionOwnerExactMatch && findFunctionObjectExactMatch" << endl;
			#endif
			if(findFunctionDeclarationClassDefinition(classDefinitionList, functionName, functionOwnerName, functionObjectName, hasFunctionOwnerClass, hasFunctionObjectClass, findFunctionOwnerExactMatch, findFunctionObjectExactMatch, &functionClassDeclaration))
			{
				addImplicitlyDeclaredVariablesInCurrentFunctionDefinitionToClassDefinition(functionClassDeclaration, &(firstCodeBlockInTree->parameters));
			}
			else
			{
				//reconcile function execution "The dog eats the ball."/dog->eat(vector ball) with function definition "animal#eat+object"/animal::eat(vector object)	
				findFunctionOwnerExactMatch = false;
				findFunctionObjectExactMatch = false;
				#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_BASED_ON_IMPLICITLY_DECLARED_VARIABLES_IN_CURRENT_FUNCTION_DEFINITION_ADVANCED
				cout << "!findFunctionOwnerExactMatch && !findFunctionObjectExactMatch" << endl;
				#endif
				if(findFunctionDeclarationClassDefinition(classDefinitionList, functionName, functionOwnerName, functionObjectName, hasFunctionOwnerClass, hasFunctionObjectClass, findFunctionOwnerExactMatch, findFunctionObjectExactMatch, &functionClassDeclaration))
				{
					addImplicitlyDeclaredVariablesInCurrentFunctionDefinitionToClassDefinition(functionClassDeclaration, &(firstCodeBlockInTree->parameters));
				}
				else
				{
					#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_BASED_ON_IMPLICITLY_DECLARED_VARIABLES_IN_CURRENT_FUNCTION_DEFINITION_ADVANCED
					cout << "class definition (generated from function execution reference) corresponding to formal function definition not found:" << functionOwnerName << "#" << functionName << "+" << functionObjectName << endl;
					#endif
				}
			}		
		}		
	}	
	#else
	NLCclassDefinition * classDefinitionFound = NULL;
	for(vector<NLCclassDefinition*>::iterator classDefinitionIter = classDefinitionList->begin(); classDefinitionIter != classDefinitionList->end(); classDefinitionIter++)
	{
		NLCclassDefinition * currentClassDef = *classDefinitionIter;
		//cout << "currentClassDef->name = " << currentClassDef->name << endl;
		for(vector<NLCclassDefinition*>::iterator localListIter = currentClassDef->functionList.begin(); localListIter != currentClassDef->functionList.end(); localListIter++)
		{
			NLCclassDefinition * functionClassDeclaration = *localListIter;
			//cout << "functionClassDeclaration->functionNameSpecial = " << functionClassDeclaration->functionNameSpecial << endl;
			//cout << "functionName = " << functionName << endl;
			if(functionClassDeclaration->functionNameSpecial == generateFunctionName(functionName))
			{
				if((currentClassDef->name == generateClassName(functionOwnerName)) || !hasFunctionOwnerClass)
				{
					#ifdef NLC_DEBUG
					cout << "reconcileClassDefinitionListFunctionDeclarationArgumentsBasedOnImplicitlyDeclaredVariablesInCurrentFunctionDefinition() functionName = " << functionName << endl;
					#endif
					//contrast and compare function class arguments vs

					findFormalFunctionArgumentCorrelateInExistingList(functionClassDeclaration, &(firstCodeBlockInTree->parameters), classDefinitionList);
				}
			}
		}
	}	
	#endif
}

#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_BASED_ON_IMPLICITLY_DECLARED_VARIABLES_IN_CURRENT_FUNCTION_DEFINITION_ADVANCED
bool findFunctionDeclarationClassDefinition(vector<NLCclassDefinition *> * classDefinitionList, string functionName, string functionOwnerName, string functionObjectName, bool hasFunctionOwnerClass, bool hasFunctionObjectClass, bool findFunctionOwnerExactMatch, bool findFunctionObjectExactMatch, NLCclassDefinition ** functionClassDeclarationFound)
{
	#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_BASED_ON_IMPLICITLY_DECLARED_VARIABLES_IN_CURRENT_FUNCTION_DEFINITION_ADVANCED
	cout << "findFunctionDeclarationClassDefinition():" << endl;
	cout << "functionName = " << functionName << endl;
	#endif
	bool foundFunctionDeclarationClassDefinition = false;
	NLCclassDefinition * classDefinitionFound = NULL;
	for(vector<NLCclassDefinition*>::iterator classDefinitionIter = classDefinitionList->begin(); classDefinitionIter != classDefinitionList->end(); classDefinitionIter++)
	{
		NLCclassDefinition * currentClassDef = *classDefinitionIter;
		#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_BASED_ON_IMPLICITLY_DECLARED_VARIABLES_IN_CURRENT_FUNCTION_DEFINITION_ADVANCED
		cout << "currentClassDef->name = " << currentClassDef->name << endl;
		#endif
		for(vector<NLCclassDefinition*>::iterator localListIter = currentClassDef->functionList.begin(); localListIter != currentClassDef->functionList.end(); )
		{
			bool removedFunctionClassDefinitionFromChildOwner = false;
			NLCclassDefinition * functionClassDeclaration = *localListIter;
			#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_BASED_ON_IMPLICITLY_DECLARED_VARIABLES_IN_CURRENT_FUNCTION_DEFINITION_ADVANCED
			cout << "functionClassDeclaration->name = " << functionClassDeclaration->name << endl;
			cout << "functionClassDeclaration->functionNameSpecial = " << functionClassDeclaration->functionNameSpecial << endl;
			#endif
			if(functionClassDeclaration->functionNameSpecial == generateFunctionName(functionName))
			{
				NLCclassDefinition * parentFunctionOwnerClassDef = NULL;
				NLCclassDefinition * parentFunctionObjectClassDef = NULL;
				//NLCitem * functionOwnerArgument = NULL;
				NLCitem * functionObjectArgument = NULL;
				bool passFunctionDefinitionRequirements = true;
				#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_BASED_ON_IMPLICITLY_DECLARED_VARIABLES_IN_CURRENT_FUNCTION_DEFINITION_ADVANCED
				cout << "(functionClassDeclaration->functionNameSpecial == generateFunctionName(functionName)) = " << functionClassDeclaration->functionNameSpecial << endl;
				#endif
				if(hasFunctionOwnerClass)
				{
					passFunctionDefinitionRequirements = false;
					if(findFunctionOwnerExactMatch)
					{
						if(currentClassDef->name == generateClassName(functionOwnerName))
						{
							#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_BASED_ON_IMPLICITLY_DECLARED_VARIABLES_IN_CURRENT_FUNCTION_DEFINITION_ADVANCED
							cout << "1 (currentClassDef->name == generateClassName(functionOwnerName))" << endl;
							#endif
							passFunctionDefinitionRequirements = true;
						}
					}
					else
					{
						int inheritanceLevel = 0;
						//cout << "\n\nfunctionOwnerName = " << functionOwnerName << endl;
						if(findParentClass(currentClassDef, generateClassName(functionOwnerName), 0, &inheritanceLevel, &parentFunctionOwnerClassDef))
						{
							if(currentClassDef != parentFunctionOwnerClassDef)
							{
								passFunctionDefinitionRequirements = true;
								#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_BASED_ON_IMPLICITLY_DECLARED_VARIABLES_IN_CURRENT_FUNCTION_DEFINITION_ADVANCED
								cout << "2 findParentClass(currentClassDef, generateClassName(functionOwnerName), 0, &inheritanceLevel, &parentFunctionOwnerClassDef)" << endl;
								#endif
								/*
								if(!findFunctionArgument(functionClassDeclaration, NLC_ITEM_TYPE_FUNCTION_DECLARATION_ARGUMENT_FUNCTION_OWNER, &functionOwnerArgument))
								{
									cout << "findFunctionDeclarationClassDefinition() error: !findFunctionArgument NLC_ITEM_TYPE_FUNCTION_DECLARATION_ARGUMENT_FUNCTION_OWNER" << endl;
								}
								*/
							}
						}
					}
				}
				if(hasFunctionObjectClass)
				{
					if(passFunctionDefinitionRequirements)
					{
						passFunctionDefinitionRequirements = false;
						if(findFunctionObjectExactMatch)
						{
							if(findFunctionArgument(functionClassDeclaration, functionObjectName, NLC_ITEM_TYPE_FUNCTION_DECLARATION_ARGUMENT_FUNCTION_OBJECT, &functionObjectArgument))	//NB generateClassName(functionObjectName) not required
							{
								passFunctionDefinitionRequirements = true;
								#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_BASED_ON_IMPLICITLY_DECLARED_VARIABLES_IN_CURRENT_FUNCTION_DEFINITION_ADVANCED
								cout << "3 findFunctionArgument(functionClassDeclaration, functionObjectName, NLC_ITEM_TYPE_FUNCTION_DECLARATION_ARGUMENT_FUNCTION_OBJECT, &functionObjectArgument)" << endl;
								#endif
							}
						}
						else
						{
							if(findFunctionArgument(functionClassDeclaration, NLC_ITEM_TYPE_FUNCTION_DECLARATION_ARGUMENT_FUNCTION_OBJECT, &functionObjectArgument))
							{
								bool foundClassDefinitionCorrespondingToFunctionObject = false;
								NLCclassDefinition * classDefinitionCorrespondingToFunctionObject = findClassDefinition(classDefinitionList, generateClassName(functionObjectArgument->name), &foundClassDefinitionCorrespondingToFunctionObject);

								if(foundClassDefinitionCorrespondingToFunctionObject)
								{
									int inheritanceLevel = 0;
									//cout << "classDefinitionCorrespondingToExistingFunctionArgument->name = " << classDefinitionCorrespondingToExistingFunctionArgument->name << endl;
									//cout << "formalFunctionArgument->className = " << formalFunctionArgument->className << endl;
									if(findParentClass(classDefinitionCorrespondingToFunctionObject, generateClassName(functionObjectName), 0, &inheritanceLevel, &parentFunctionObjectClassDef))
									{
										if(classDefinitionCorrespondingToFunctionObject != parentFunctionObjectClassDef)
										{
											passFunctionDefinitionRequirements = true;
											#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_BASED_ON_IMPLICITLY_DECLARED_VARIABLES_IN_CURRENT_FUNCTION_DEFINITION_ADVANCED
											cout << "4 findParentClass(classDefinitionCorrespondingToFunctionObject, generateClassName(functionObjectName), 0, &inheritanceLevel, &parentFunctionObjectClassDef)" << endl;
											#endif
										}
									}
								}
							}
						}
					}					
				}
				if(passFunctionDefinitionRequirements)
				{
					#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_BASED_ON_IMPLICITLY_DECLARED_VARIABLES_IN_CURRENT_FUNCTION_DEFINITION_ADVANCED
					cout << "passFunctionDefinitionRequirements" << endl;
					#endif
					foundFunctionDeclarationClassDefinition = true;
					*functionClassDeclarationFound = functionClassDeclaration;
					if(hasFunctionOwnerClass)
					{
						if(!findFunctionOwnerExactMatch)
						{
							//now update class definitions function declaration arguments based on formal function definition arguments 
							removedFunctionClassDefinitionFromChildOwner = true;
							parentFunctionOwnerClassDef->functionList.push_back(functionClassDeclaration);
							/*
							functionOwnerArgument->functionArgumentExecutionEntityName = functionOwnerArgument->name;
							functionOwnerArgument->name = parentFunctionOwnerClassDef->name;
							functionOwnerArgument->functionArgumentPassCastRequired = true;
							*/
						}
						//functionOwnerArgument->functionArgumentCertified = true;	//not currently used
					}
					if(hasFunctionObjectClass)
					{
						if(!findFunctionObjectExactMatch)
						{
							//now update class definitions function declaration arguments based on formal function definition arguments 
							functionObjectArgument->functionArgumentExecutionEntityName = functionObjectArgument->name;
							functionObjectArgument->name = parentFunctionObjectClassDef->name;
							functionObjectArgument->className = parentFunctionObjectClassDef->name;
							functionObjectArgument->functionArgumentPassCastRequired = true;
						}
						functionObjectArgument->functionArgumentCertified = true;	//not currently used
					}
				}
			}
			
			if(removedFunctionClassDefinitionFromChildOwner)
			{
				localListIter = currentClassDef->functionList.erase(localListIter);
			}
			else
			{
				localListIter++;
			}
		}
	}
	#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_BASED_ON_IMPLICITLY_DECLARED_VARIABLES_IN_CURRENT_FUNCTION_DEFINITION_ADVANCED
	cout << "exit foundFunctionDeclarationClassDefinition = " << foundFunctionDeclarationClassDefinition << endl;
	#endif
	return foundFunctionDeclarationClassDefinition;
}

bool findFunctionArgument(NLCclassDefinition * classDefinition, string itemName, int itemType, NLCitem ** functionArgument)
{
	bool foundFunctionArgument = false;
	for(vector<NLCitem*>::iterator parametersIterator = classDefinition->parameters.begin(); parametersIterator < classDefinition->parameters.end(); parametersIterator++)
	{
		NLCitem * currentItem = *parametersIterator;
		//cout << "currentItem->itemType = " << currentItem->itemType << endl;
		if(currentItem->itemType == itemType)
		{
			//cout << "(currentItem->itemType == itemType)" << endl;
			if(currentItem->name == itemName)
			{
				//cout << "(currentItem->name)" << endl;
				*functionArgument = currentItem;
				foundFunctionArgument = true;	
			}
		}
	}
	return foundFunctionArgument;
}

bool findFunctionArgument(NLCclassDefinition * classDefinition, int itemType, NLCitem ** functionArgument)
{
	bool foundFunctionArgument = false;
	for(vector<NLCitem*>::iterator parametersIterator = classDefinition->parameters.begin(); parametersIterator < classDefinition->parameters.end(); parametersIterator++)
	{
		NLCitem * currentItem = *parametersIterator;
		//cout << "currentItem->itemType = " << currentItem->itemType << endl;
		if(currentItem->itemType == itemType)
		{
			*functionArgument = currentItem;
			foundFunctionArgument = true;
		}
	}
	return foundFunctionArgument;
}

void addImplicitlyDeclaredVariablesInCurrentFunctionDefinitionToClassDefinition(NLCclassDefinition * functionClassDeclaration, vector<NLCitem*> * formalFunctionArgumentList)
{
	//cout << "addImplicitlyDeclaredVariablesInCurrentFunctionDefinitionToClassDefinition(): functionClassDeclaration->name = " << functionClassDeclaration->name << endl;
	vector<NLCitem*> * existingFunctionArgumentList = &(functionClassDeclaration->parameters);
	for(vector<NLCitem*>::iterator parametersIterator = formalFunctionArgumentList->begin(); parametersIterator < formalFunctionArgumentList->end(); parametersIterator++)
	{
		NLCitem * formalFunctionArgument = *parametersIterator;
		if(formalFunctionArgument->itemType == NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_INSTANCE_OR_CLASS_LIST)
		{
			//add a new function argument to the existing function argument list
			//cout << "formalFunctionArgumentToAddExistingFunctionArgumentList: formalFunctionArgument->name = " << formalFunctionArgument->name << endl;
			NLCitem * formalFunctionArgumentToAddExistingFunctionArgumentList = new NLCitem(formalFunctionArgument);	//NLC by default uses plural (lists) not singular entities
			formalFunctionArgumentToAddExistingFunctionArgumentList->itemType = NLC_ITEM_TYPE_FUNCTION_DECLARATION_ARGUMENT_INSTANCE_OR_CLASS_LIST;
			existingFunctionArgumentList->push_back(formalFunctionArgumentToAddExistingFunctionArgumentList);
		}
	}
}


#else
bool findFormalFunctionArgumentCorrelateInExistingList(NLCclassDefinition * functionClassDeclaration, vector<NLCitem*> * formalFunctionArgumentList, vector<NLCclassDefinition *> * classDefinitionList)
{
	bool result = true;
	vector<NLCitem*> * existingFunctionArgumentList = &(functionClassDeclaration->parameters);

	for(vector<NLCitem*>::iterator parametersIterator = formalFunctionArgumentList->begin(); parametersIterator < formalFunctionArgumentList->end(); parametersIterator++)
	{
		NLCitem * formalFunctionArgument = *parametersIterator;
		if((formalFunctionArgument->itemType == NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION) || (formalFunctionArgument->itemType == NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION_OBJECT))	//OLD before 1k9b - if(formalFunctionArgument->itemType == NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_INSTANCE_OR_CLASS_LIST)
		{
			NLCclassDefinition * classDefinitionCorrespondingToExistingFunctionArgument = NULL;
			NLCclassDefinition * classDefinitionCorrespondingToFormalFunctionArgument = NULL;	//not used
			NLCitem * existingFunctionArgument = NULL;
			bool foundFormalFunctionArgumentCorrelateForExistingArgument = false;
			int foundFormalFunctionArgumentCorrelateForExistingArgumentInheritanceLevel = NLC_SUPPORT_INPUT_FILE_LISTS_MAX_INHERITANCE_DEPTH_FOR_CLASS_CASTING;
			
			#ifdef NLC_DEBUG
			cout << "formalFunctionArgument->className = " << formalFunctionArgument->className << endl;
			#endif
			for(vector<NLCitem*>::iterator parametersIterator = existingFunctionArgumentList->begin(); parametersIterator < existingFunctionArgumentList->end(); parametersIterator++)
			{
				NLCitem * currentExistingFunctionArgument = *parametersIterator;

				bool foundClassDefinitionCorrespondingToExistingFunctionArgument = false;
				classDefinitionCorrespondingToExistingFunctionArgument = findClassDefinition(classDefinitionList, currentExistingFunctionArgument->className, &foundClassDefinitionCorrespondingToExistingFunctionArgument);

				if(foundClassDefinitionCorrespondingToExistingFunctionArgument)
				{
					#ifdef NLC_DEBUG
					cout << "foundClassDefinitionCorrespondingToExistingFunctionArgument: " << classDefinitionCorrespondingToExistingFunctionArgument->name << endl;
					#endif
					if(formalFunctionArgument->itemType == NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_INSTANCE_OR_CLASS_LIST)
					{//CHECKTHIS; do not currently distinguish between plural and singular variables - this will need to be updated in future
						int inheritanceLevel = 0;
						NLCclassDefinition * tempClassDef = NULL;
						//cout << "classDefinitionCorrespondingToExistingFunctionArgument->name = " << classDefinitionCorrespondingToExistingFunctionArgument->name << endl;
						//cout << "formalFunctionArgument->className = " << formalFunctionArgument->className << endl;
						if(findParentClass(classDefinitionCorrespondingToExistingFunctionArgument, formalFunctionArgument->className, 0, &inheritanceLevel, &tempClassDef))
						{
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
		}
		else if(formalFunctionArgument->itemType == NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_INSTANCE_OR_CLASS_LIST)
		{
			#ifdef NLC_SUPPORT_INPUT_FILE_LISTS_CHECK_ACTION_SUBJECT_CONTENTS_FOR_IMPLICITLY_DECLARED_PARAMETERS
			bool foundFunctionArgumentInActionSubjectContents = false;
			GIAentityNode * actionEntity = functionClassDeclaration->actionOrConditionInstance;
			if(!(actionEntity->actionSubjectEntity->empty()))
			{
				GIAentityNode * actionSubject = (actionEntity->actionSubjectEntity->back())->entity;
				//cout << "actionSubject = " << actionSubject->entityName << endl;
				//cout << "formalFunctionArgument->className = " << formalFunctionArgument->className << endl;
				if(formalFunctionArgument->className == generateClassName(actionSubject))
				{
					foundFunctionArgumentInActionSubjectContents = true;
					#ifdef NLC_DEBUG
					cout << "foundFunctionArgumentInActionSubjectContents: " << formalFunctionArgument->className << endl;
					#endif
					//formalFunctionArgument->formalFunctionArgumentCorrespondsToActionSubjectUseThisAlias = true;	//not done; this is now handled by generateContextBlocks()
				}
				//ignore conditions of actionSubject; they will need to be explicitly referenced by the function
				//for(vector<GIAentityConnection*>::iterator entityIter = actionSubject->conditionNodeList->begin(); entityIter != actionSubject->conditionNodeList->end(); entityIter++)
				//{
				//	GIAentityNode * actionCondition = (*entityIter)->entity;
				//}
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
				//this warning was created for a previous NLC rev;
				//cout << "NLC compiler warning: !foundFormalFunctionArgumentCorrelateForExistingArgument && !foundFunctionArgumentInActionSubjectContents (function arguments will not map): " << formalFunctionArgument->className << endl;
			#else
				//this warning was created for a previous NLC rev;
				//cout << "NLC compiler warning: !foundFormalFunctionArgumentCorrelateForExistingArgument (function arguments will not map): " << formalFunctionArgument->className << endl;
			#endif
				//add a new function argument to the existing function argument list
				NLCitem * formalFunctionArgumentToAddExistingFunctionArgumentList = new NLCitem(formalFunctionArgument);	//NLC by default uses plural (lists) not singular entities
				existingFunctionArgumentList->push_back(formalFunctionArgumentToAddExistingFunctionArgumentList);
			#ifdef NLC_SUPPORT_INPUT_FILE_LISTS_CHECK_ACTION_SUBJECT_CONTENTS_FOR_IMPLICITLY_DECLARED_PARAMETERS
			}
			#endif
		}
	}
	return result;
}
#endif

bool findParentClass(NLCclassDefinition * classDefinition, string variableName, int inheritanceLevel, int * maxInheritanceLevel, NLCclassDefinition ** parentClass)
{
	//cout << "findParentClass: variableName = " << variableName << endl;
	bool foundVariable = false;
	if(classDefinition->name == variableName)
	{
		foundVariable = true;
		*maxInheritanceLevel = inheritanceLevel;
		*parentClass = classDefinition;
	}
	else
	{
		for(vector<NLCclassDefinition*>::iterator localListIter = classDefinition->definitionList.begin(); localListIter != classDefinition->definitionList.end(); localListIter++)
		{
			NLCclassDefinition * targetClassDefinition = *localListIter;
			if(findParentClass(targetClassDefinition, variableName, (inheritanceLevel+1), maxInheritanceLevel, parentClass))
			{
				foundVariable = true;
			}
		}
	}
	return foundVariable;
}
#endif

bool getFilesFromFileList2(string inputListFileName, vector<string> * inputTextFileNameList, int * numberOfInputFilesInList)
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
	//cout << "*numberOfInputFilesInList = " << *numberOfInputFilesInList << endl;
	#endif
	return result;
}

#endif

#ifdef NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_SUPPORT_ALPHANUMERIC_ENTITY_NAMES_ONLY
bool checkAlphaNumericEntityNames(vector<GIAentityNode*> * entityNodesActiveListComplete, int maxNumberSentences)
{
	bool result = true;
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode * entity = (*entityIter);
		if(!isStringNLPparsableWord(entity->entityName))
		{
			result = false;
			cout << "checkAlphaNumericEntityNames(): user input error - entity names cannot start with numbers: " << entity->entityName << endl;
			exit(0);
		}
	}
	return result;
}
#endif
	




