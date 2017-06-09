/*******************************************************************************
 *
 * This file is part of BAIPROJECT.
 *
 * BAIPROJECT is licensed under the GNU Affero General Public License
 * version 3, as published by the Free Software Foundation. The use of
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
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2017 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler
 * Project Version: 2c1a 01-June-2017
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/


#include "NLCtranslator.hpp"


bool NLCtranslatorClass::translateNetwork(NLCcodeblock* firstCodeBlockInTree, vector<NLCclassDefinition*>* classDefinitionList, vector<GIAentityNode*>* entityNodesActiveListComplete, map<int, vector<GIAentityNode*>*>* entityNodesActiveListSentences, const int maxNumberSentences, string NLCfunctionName, NLCfunction* currentNLCfunctionInList, const bool useNLCpreprocessor)
{
	bool result = true;

	#ifdef NLC_PREPROCESSOR
	NLCtranslatorCodeBlocksLogicalConditionsAdvanced.initialiseLogicalConditionLevelRecordArray(useNLCpreprocessor);
	#endif

	/*//this is done by GIA
	#ifdef NLC_CATEGORIES_TEST_PLURALITY_ENFORCE
	#ifdef NLC_PREPROCESSOR
	//NLC translator Part prep A.
	if(!identifyImplicitPluralLogicalConditionOperationsObjects(entityNodesActiveListComplete, maxNumberSentences))
	{
		result = false;
	}
	#endif
	#endif
	*/

	if(!this->disableAllForLoopPredeterminers(entityNodesActiveListSentences, maxNumberSentences))
	{
		result = false;
	}

	#ifdef NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_SUPPORT_ALPHANUMERIC_ENTITY_NAMES_ONLY
	if(!this->checkAlphaNumericEntityNames(entityNodesActiveListComplete, maxNumberSentences))
	{
		result = false;
	}
	#endif

	//NLC translator Part 1.
	if(!NLCtranslatorCodeBlocks.generateCodeBlocks(firstCodeBlockInTree, entityNodesActiveListComplete, entityNodesActiveListSentences, maxNumberSentences, NLCfunctionName, currentNLCfunctionInList))
	{
		result = false;
	}


	//NLC translator Part 2.
	if(!NLCtranslatorClassDefinitions.generateClassHeirarchy(classDefinitionList, entityNodesActiveListComplete, currentNLCfunctionInList))
	{
		result = false;
	}
		

	return result;
}

/*
#ifdef NLC_CATEGORIES_TEST_PLURALITY_ENFORCE
#ifdef NLC_PREPROCESSOR
bool identifyImplicitPluralLogicalConditionOperationsObjects(vector<GIAentityNode*>* entityNodesActiveListComplete, int maxNumberSentences)
{
	bool result = true;

	for(int sentenceIndex=GIA_NLP_START_SENTENCE_INDEX; sentenceIndex <= maxNumberSentences; sentenceIndex++)
	{
		for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
		{
			GIAentityNode* conditionRelationshipEntity = (*entityIter);
			if(checkSentenceIndexParsingCodeBlocks(conditionRelationshipEntity, sentenceIndex, true))	//could be set to false instead
			{
				//because GIA GIAsentence objects are unavailable to NLC, must parse all entities including disabled entites and locate matching entities (in same sentence and with entityIndex+1 of "for" condition):
				for(vector<GIAentityNode*>::iterator entityIter2 = entityNodesActiveListComplete->begin(); entityIter2 != entityNodesActiveListComplete->end(); entityIter2++)
				{
					GIAentityNode* entity2 = (*entityIter);
					if(entity2->sentenceIndexTemp == sentenceIndex)
					{
						if(entity2->entityIndexTemp = conditionRelationshipEntity->entityIndexTemp+1)
						{
							#ifdef NLC_PREPROCESSOR
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



bool NLCtranslatorClass::disableAllForLoopPredeterminers(map<int, vector<GIAentityNode*>*>* entityNodesActiveListSentences, const int maxNumberSentences)
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
			bool wordImmediatelySucceedingForFound = SHAREDvars.textInTextArray(entity->entityName, logicalConditionOperationsWordImmediatelySucceedingForArray, NLC_LOGICAL_CONDITION_OPERATIONS_WORD_IMMEDIATELY_SUCCEEDING_FOR_NUMBER_OF_TYPES);
			if(wordImmediatelySucceedingForFound)
			{
				entity->disabled = true;	//should not be required; disableInstanceAndNetworkIndexEntityNLC(entity);
			}
		}
	}
	return result;
}
/*
void disableInstanceAndNetworkIndexEntityNLC(GIAentityNode* entity)
{
	entity->disabled = true;
	if(!(entity->instanceReverseNodeList->empty()))
	{
		GIAentityNode* networkIndexEntity = getPrimaryNetworkIndexNodeDefiningInstance(entity);
		networkIndexEntity->disabled = true
	}
}
*/


#ifdef NLC_INPUT_FUNCTION_LISTS
#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS
//NB firstCodeBlockInTree contains the new function codeblock (NLC_CODEBLOCK_TYPE_NEW_FUNCTION) parameters: NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION_OWNER, NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION_OBJECT, NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION_OBJECT, NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_INSTANCE_OR_CLASS_LIST
void NLCtranslatorClass::reconcileFunctionDefinitionClassDefinitionArgumentsBasedOnImplicitlyDeclaredVariablesInCurrentFunctionDefinition(NLCcodeblock* firstCodeBlockInTree, vector<NLCclassDefinition*>* classDefinitionList, NLCclassDefinition* functionDefinitionClassDefinition)
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

	#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_BASED_ON_IMPLICITLY_DECLARED_VARIABLES_IN_CURRENT_FUNCTION_DEFINITION

	//adds the arguments from firstCodeBlockInTree (NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_INSTANCE_OR_CLASS_LIST) to the functionDefinition classDefinition
	this->addImplicitlyDeclaredVariablesInCurrentFunctionDefinitionArgumentsToFunctionDefinition(&(firstCodeBlockInTree->parameters), functionDefinitionClassDefinition);	//note this has already been done for libraryFunctions

	#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE_ACTIVE
	//propogates arguments from dependency child functionDefintions to current functionDefintion
	for(vector<NLCclassDefinition*>::iterator classDefinitionListIter = functionDefinitionClassDefinition->functionDependencyList.begin(); classDefinitionListIter != functionDefinitionClassDefinition->functionDependencyList.end(); classDefinitionListIter++)
	{
		NLCclassDefinitionFunctionDependency* functionDefinitionFunctionDependencyChild = (*classDefinitionListIter)->functionDependency;
		NLCclassDefinition* functionDefinitionClassDefinition2 = NULL;
		//find the dependency child functionDefinition
		if(NLCclassDefinitionClass.findFunctionDefinitionClassDefinition(classDefinitionList, functionDefinitionFunctionDependencyChild->functionName, functionDefinitionFunctionDependencyChild->functionOwnerName, functionDefinitionFunctionDependencyChild->functionObjectName, functionDefinitionFunctionDependencyChild->hasFunctionOwnerClass, functionDefinitionFunctionDependencyChild->hasFunctionObjectClass, findFunctionOwnerExactMatch, findFunctionObjectExactMatch, &functionDefinitionClassDefinition2, rearrangeClassList))	//should find exact match as class definitions have already been created for all new function definitions (and their implicit declarations have been added to their function argument lists)
		{
			this->addImplicitlyDeclaredVariablesInCurrentFunctionDefinitionToFunctionDefinition(functionDefinitionClassDefinition2, functionDefinitionClassDefinition);	//pass arguments from child to parent
			this->addImplicitlyDeclaredVariablesInCurrentFunctionDefinitionToFunctionDefinitionArguments(functionDefinitionClassDefinition2, &(firstCodeBlockInTree->parameters));	//note can use functionDefinitionClassDefinition instead of functionDefinitionClassDefinition2
		}
	}
	#endif
	#endif

	#else
	cout << "reconcileFunctionDefinitionClassDefinitionArgumentsBasedOnImplicitlyDeclaredVariablesInCurrentFunctionDefinition{} error: !NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED no longer supported" << endl;
	exit(EXIT_ERROR);
	#endif
}

#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_BASED_ON_IMPLICITLY_DECLARED_VARIABLES_IN_CURRENT_FUNCTION_DEFINITION
#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED

//fine; this function is not duplicating arguments
void NLCtranslatorClass::addImplicitlyDeclaredVariablesInCurrentFunctionDefinitionArgumentsToFunctionDefinition(vector<NLCitem*>* functionDefinitionSourceArgumentList, NLCclassDefinition* functionDefinition)
{
	vector<NLCitem*>* functionDefinitionArgumentList = &(functionDefinition->parameters);

	/*
	#ifdef NLC_DEBUG
	cout << "addImplicitlyDeclaredVariablesInCurrentFunctionDefinitionArgumentsToFunctionDefinition{}: functionDefinition->name = " << functionDefinition->name << endl;
	#endif
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
			if(!NLCclassDefinitionClass.findFunctionArgument(functionDefinitionArgumentList, functionDefinitionSourceArgument, NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_INSTANCE_OR_CLASS_LIST, &functionArgumentTemp))
			{
				NLCitem* newFunctionArgument = new NLCitem(functionDefinitionSourceArgument);	//NLC by default uses plural (lists) not singular entities
				newFunctionArgument->itemType = NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_INSTANCE_OR_CLASS_LIST;
				functionDefinitionArgumentList->push_back(newFunctionArgument);
			}
		}
	}
}
#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE
//fine; this function is not duplicating arguments
void NLCtranslatorClass::addImplicitlyDeclaredVariablesInCurrentFunctionDefinitionToFunctionDefinition(NLCclassDefinition* functionDefinitionSource, NLCclassDefinition* functionDefinition)
{
	vector<NLCitem*>* functionDefinitionSourceArgumentList = &(functionDefinitionSource->parameters);
	vector<NLCitem*>* functionDefinitionArgumentList = &(functionDefinition->parameters);
	for(vector<NLCitem*>::iterator parametersIterator = functionDefinitionSourceArgumentList->begin(); parametersIterator < functionDefinitionSourceArgumentList->end(); parametersIterator++)
	{
		NLCitem* functionDeclarationSourceArgument = *parametersIterator;
		if(functionDeclarationSourceArgument->itemType == NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_INSTANCE_OR_CLASS_LIST)
		{
			//add a new function argument to the existing function argument list
			NLCitem* functionArgumentTemp = NULL;
			if(!NLCclassDefinitionClass.findFunctionArgument(functionDefinitionArgumentList, functionDeclarationSourceArgument, NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_INSTANCE_OR_CLASS_LIST, &functionArgumentTemp))
			{
				NLCitem* newFunctionArgument = new NLCitem(functionDeclarationSourceArgument);
				newFunctionArgument->itemType = NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_INSTANCE_OR_CLASS_LIST;
				functionDefinitionArgumentList->push_back(newFunctionArgument);
			}
		}
	}
}

//fine; this function is not duplicating arguments
void NLCtranslatorClass::addImplicitlyDeclaredVariablesInCurrentFunctionDefinitionToFunctionDefinitionArguments(NLCclassDefinition* functionDefinitionSource, vector<NLCitem*>* functionDefinitionArgumentList)
{
	vector<NLCitem*>* functionDefinitionSourceArgumentList = &(functionDefinitionSource->parameters);
	for(vector<NLCitem*>::iterator parametersIterator = functionDefinitionSourceArgumentList->begin(); parametersIterator < functionDefinitionSourceArgumentList->end(); parametersIterator++)
	{
		NLCitem* functionDeclarationSourceArgument = *parametersIterator;
		if(functionDeclarationSourceArgument->itemType == NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_INSTANCE_OR_CLASS_LIST)
		{
			//add a new function argument to the existing function argument list
			NLCitem* functionArgumentTemp = NULL;
			if(!NLCclassDefinitionClass.findFunctionArgument(functionDefinitionArgumentList, functionDeclarationSourceArgument, NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_INSTANCE_OR_CLASS_LIST, &functionArgumentTemp))
			{
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


#endif

#ifdef NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_SUPPORT_ALPHANUMERIC_ENTITY_NAMES_ONLY
bool NLCtranslatorClass::checkAlphaNumericEntityNames(vector<GIAentityNode*>* entityNodesActiveListComplete, const int maxNumberSentences)
{
	bool result = true;
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode* entity = (*entityIter);
		if(!(entity->disabled))
		{
			if(!NLCpreprocessorSentenceClass.isStringNLPparsableWord(entity->entityName, false))
			{
				result = false;
				cout << "checkAlphaNumericEntityNames{}: user input error - entity names cannot start with numbers: " << entity->entityName << endl;
				exit(EXIT_ERROR);
			}
		}
	}
	return result;
}
#endif


bool NLCtranslatorClass::createFunctionDefinitionClassDefinition(vector<NLCclassDefinition*>* classDefinitionList, string NLCfunctionName, const int functionDefinitionIndex, const bool libraryFunctionDeclaration)
{
	NLCclassDefinitionFunctionDependency* functionDependency = NULL;

	string functionName = "";
	string functionOwnerName = "";
	string functionObjectName = "";
	bool hasFunctionOwnerClass = false;
	bool hasFunctionObjectClass = false;
	#ifdef NLC_LIBRARY
	vector<NLCitem*> parameters;
	if(libraryFunctionDeclaration)
	{
		NLCitemClass.parseFunctionNameFromNLClibFunctionName(NLCfunctionName, &functionName, &functionOwnerName, &hasFunctionOwnerClass, &functionObjectName, &hasFunctionObjectClass, &parameters);	//gets "fight" from "dog#fight+box!argument1!argument2"
	}
	else
	{
	#endif
		NLCitemClass.parseFunctionNameFromNLCfunctionName(NLCfunctionName, &functionName, &functionOwnerName, &hasFunctionOwnerClass, &functionObjectName, &hasFunctionObjectClass);	//gets "fight" from "dog#fight+box"
	#ifdef NLC_LIBRARY
	}
	#endif

	string functionClassDefinitionName = functionName + NLC_CLASS_DEFINITIONS_CREATE_FUNCTION_DECLARATIONS_FOR_NEW_FUNCTION_DEFINITIONS_CLASS_DEFINITION_HIDDEN_NAME_APPEND;

	string functionOwnerClassDefinitionName = "";
	bool passNewFunctionDefinitionChecks = true;
	if(hasFunctionOwnerClass)
	{
		functionOwnerClassDefinitionName = NLCitemClass.generateClassName(functionOwnerName);
	}
	else
	{
		functionOwnerClassDefinitionName = NLCitemClass.generateClassName(NLC_CLASS_DEFINITIONS_SUPPORT_FUNCTIONS_WITHOUT_SUBJECT_ARTIFICIAL_CLASS_NAME);
	}
	if(passNewFunctionDefinitionChecks)
	{
		bool isReferenceElseFunctionDefinition = false;		//ie isFunctionDefinition
		NLCclassDefinition* functionClassDefinition = this->createFunctionDefinitionClassDefinition(classDefinitionList, functionName, functionOwnerName, functionObjectName, hasFunctionOwnerClass, hasFunctionObjectClass, functionClassDefinitionName, functionOwnerClassDefinitionName, functionDefinitionIndex, isReferenceElseFunctionDefinition);
		#ifdef NLC_LIBRARY
		if(functionClassDefinition != NULL)
		{
			this->addImplicitlyDeclaredVariablesInCurrentFunctionDefinitionArgumentsToFunctionDefinition(&parameters, functionClassDefinition);
		}
		#ifdef NLC_LIBRARY_FUNCTION_LISTS_FOR_ARGUMENT_RECONCILIATION
		if(libraryFunctionDeclaration)
		{
			functionClassDefinition->isLibraryFunctionDefinition = true;

			/*//OLD: 1q6aTEMP1
			//create an ordinary (non-function definition) class definition for the function action object and set isLibraryFunctionDefinition (this is required to prevent printClassDefinitions from printing this class)
			bool foundClassDefinitionAction = false;
			string actionClassName =  NLCitemClass.generateClassName(functionName);
			NLCclassDefinition* classDefinitionAction = findClassDefinition(classDefinitionList, actionClassName, &foundClassDefinitionAction);	//see if class definition already exists
			if(!foundClassDefinitionAction)
			{
				classDefinitionAction = new NLCclassDefinition(actionClassName);
				classDefinitionList->push_back(classDefinitionAction);
				classDefinitionAction->isLibraryFunctionDefinition = true;
			}
			*/
		}
		#endif
		#endif
	}

	return functionDependency;
}

NLCclassDefinition* NLCtranslatorClass::createFunctionDefinitionClassDefinition(vector<NLCclassDefinition*>* classDefinitionList, const string functionName, const string functionOwnerName, const string functionObjectName, const bool hasFunctionOwnerClass, const bool hasFunctionObjectClass, const string functionClassDefinitionName, const string functionOwnerClassDefinitionName, const int functionDefinitionIndex, const bool isReferenceElseFunctionDefinition)
{
	NLCclassDefinitionFunctionDependency* functionDependency = NULL;
	NLCclassDefinition* functionClassDefinition = NULL;

	#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE
	bool duplicateFunctionDeclarationDetected = false;
	bool foundFunctionDependencyInList = NLCclassDefinitionClass.findFunctionDefinitionFunctionDependencyInList(classDefinitionList, functionName, functionOwnerName, functionObjectName, hasFunctionOwnerClass, hasFunctionObjectClass, &functionDependency);	//note at this stage only functionDefinition functionDependencies have been created (so the functionDefintion check is not actually required)...
	if(foundFunctionDependencyInList)
	{
		cout << "createFunctionDefinitionClassDefinition{}:createNewClassDefinitionFunctionDeclaration{} error: duplicate functionDefinition classDefinition defined" << endl;
		exit(EXIT_ERROR);
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


		bool foundFunctionOwnerClassDefinition = false;
		//NB if(hasFunctionOwnerClass), then functionOwnerClassDefinitionName will be set to NLC_CLASS_DEFINITIONS_SUPPORT_FUNCTIONS_WITHOUT_SUBJECT_ARTIFICIAL_CLASS_NAME
		NLCclassDefinition* functionOwnerClassDefinition = NLCclassDefinitionClass.findClassDefinition(classDefinitionList, functionOwnerClassDefinitionName, &foundFunctionOwnerClassDefinition);	//see if class definition already exists
		if(!foundFunctionOwnerClassDefinition)
		{
			functionOwnerClassDefinition = new NLCclassDefinition(functionOwnerClassDefinitionName);
			classDefinitionList->push_back(functionOwnerClassDefinition);
		}


		bool foundFunctionClassDefinition = false;
		functionClassDefinition = NLCclassDefinitionClass.findClassDefinition(classDefinitionList, functionClassDefinitionName, &foundFunctionClassDefinition);	//see if class definition already exists
		if(!foundFunctionClassDefinition)
		{
			functionClassDefinition = new NLCclassDefinition(functionClassDefinitionName);
			classDefinitionList->push_back(functionClassDefinition);
		}

		functionClassDefinition->functionNameSpecial = NLCitemClass.generateFunctionName(functionName);

		functionClassDefinition->isActionOrConditionInstanceNotClass = true;

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

		/*
		#ifdef NLC_RECORD_ACTION_HISTORY
		//added 1q1b, removed 1q6a
		//NB classDefinitionAction must be generated by fillActionLists (functionClassDefinition cannot be used) because functionClassDefinitionName (e.g. printNewFunctionDefinition) is not the same as functionClassName (e.g. printClass)
		fillActionLists(classDefinitionList, hasFunctionOwnerClass, hasFunctionObjectClass, functionName, functionObjectName, functionOwnerClassDefinition);
		#endif
		*/

	#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE
		functionClassDefinition->functionDependency = functionDependency;
	}
	#endif

	return functionClassDefinition;
}






