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
 * File Name: NLCtranslatorCodeBlocks.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2017 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler
 * Project Version: 2c2b 12-June-2017
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/


#include "NLCtranslatorCodeBlocks.hpp"

bool NLCtranslatorCodeBlocksClass::generateCodeBlocks(NLCcodeblock* firstCodeBlockInTree, vector<GIAentityNode*>* entityNodesActiveListComplete, map<int, vector<GIAentityNode*>*>* entityNodesActiveListSentences, const int maxNumberSentences, string NLCfunctionName, NLCfunction* currentNLCfunctionInList)
{
	bool result = true;

	NLCcodeblock* currentCodeBlockInTree = firstCodeBlockInTree;

	#ifdef NLC_ADVANCED_REFERENCING_SUPPORT_ALIASES_PREVENT_ADDING_AS_FUNCTION_ARGUMENT
	#ifndef NLC_ADVANCED_REFERENCING_SUPPORT_ALIASES_CROSS_FUNCTION_ALIASES
	NLCcodeBlockClass.initialiseFunctionAliasClassList();
	#endif
	NLCtranslatorCodeBlocksOperations.fillFunctionAliasClassList(entityNodesActiveListComplete);
	#endif

	currentCodeBlockInTree = this->createCodeBlockNewFunction(currentCodeBlockInTree, NLCfunctionName, entityNodesActiveListComplete, currentNLCfunctionInList);

	//#ifdef NLC_PREPROCESSOR
	NLCpreprocessorSentence* currentNLCsentenceInList = currentNLCfunctionInList->firstNLCsentenceInFunction;
	//#endif

	#ifdef NLC_ADVANCED_REFERENCING_MONITOR_CONTEXT
	#ifdef NLC_PREPROCESSOR
	#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
	if(NLCtranslatorCodeBlocksLogicalConditionsAdvanced.getUseNLCpreprocessor())
	{
		currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlocksDeclareContextList(currentCodeBlockInTree, 0);
	}
	#endif
	#endif
	#endif

	#ifdef NLC_ADVANCED_REFERENCING_DECLARE_LOCAL_PROPERTY_LISTS_FOR_ALL_INDEFINITE_ENTITIES_FOR_ALL_SENTENCES
	#ifdef NLC_DEFINE_LOCAL_VARIABLES_FOR_ALL_INDEFINATE_ENTITIES
	//Part Prep A - declareLocalVariables (for non-specific indefinite entities, eg "a chicken") - added 1g8a;
	this->declareLocalPropertyListsForIndefiniteEntities(&currentCodeBlockInTree, entityNodesActiveListComplete, 0, NLCfunctionName, currentNLCsentenceInList);
	#endif
	#endif

	for(map<int, vector<GIAentityNode*>*>::iterator sentenceIter = entityNodesActiveListSentences->begin(); sentenceIter != entityNodesActiveListSentences->end(); )
	{
		int sentenceIndex = sentenceIter->first;
		vector<GIAentityNode*>* entityNodesActiveListSentence = sentenceIter->second;



		#ifdef NLC_PREPROCESSOR_GENERATE_COMMENTS
		if(NLCtranslatorCodeBlocksLogicalConditionsAdvanced.getUseNLCpreprocessor())
		{
			if(currentNLCsentenceInList->isMath)
			{
				currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockCommentSingleLine(currentCodeBlockInTree, currentNLCsentenceInList->sentenceOriginal);
			}
			else
			{
				currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockCommentSingleLine(currentCodeBlockInTree, currentNLCsentenceInList->sentenceContentsOriginal);
			}
		}
		#endif

		#ifdef NLC_ADVANCED_REFERENCING_MONITOR_CONTEXT
		#ifdef NLC_PREPROCESSOR
		#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
		if(NLCtranslatorCodeBlocksLogicalConditionsAdvanced.getUseNLCpreprocessor())
		{
			NLCcodeBlockClass.setCurrentLogicalConditionLevel(currentNLCsentenceInList->indentation);
		}
		#endif
		#endif
		#endif

		#ifndef NLC_ADVANCED_REFERENCING_DECLARE_LOCAL_PROPERTY_LISTS_FOR_ALL_INDEFINITE_ENTITIES_FOR_ALL_SENTENCES
		#ifdef NLC_DEFINE_LOCAL_VARIABLES_FOR_ALL_INDEFINATE_ENTITIES
		//Part Prep A - declareLocalVariables (for non-specific indefinite entities, eg "a chicken") - added 1g8a;
		this->declareLocalPropertyListsForIndefiniteEntities(&currentCodeBlockInTree, entityNodesActiveListSentence, sentenceIndex, NLCfunctionName, currentNLCsentenceInList);	//added 1g8a 11-July-2014
		#endif
		#endif

		#ifdef NLC_GENERATE_OBJECT_INITIALISATIONS_BASED_ON_CONCEPTS_FOR_ALL_DEFINITE_ENTITIES
		this->generateObjectInitialisationsBasedOnConceptsForAllDefiniteEntities(&currentCodeBlockInTree, entityNodesActiveListSentence, sentenceIndex);
		#endif

		#ifdef NLC_PREPROCESSOR_MATH_REPLACE_NUMERICAL_VARIABLES_NAMES_FOR_NLP
		if(NLCtranslatorCodeBlocksLogicalConditionsAdvanced.getUseNLCpreprocessor())
		{
			//reconcile temporary variable name replacement
			for(int i=0; i<currentNLCsentenceInList->variableNamesDetected.size(); i++)
			{
				if(!(currentNLCsentenceInList->isMath))
				{//only replace variables names (and reconcile temporary variable name replacement) for non math text
					int dummyNumber = NLCpreprocessorSentenceClass.generateDummyNumber(i+1);
					string numericalVariableName = currentNLCsentenceInList->variableNamesDetected[i];
					if(!NLCtranslatorCodeBlocksLogicalConditions.findDummyNumberAndReplaceWithOriginalNumericalVariableName(entityNodesActiveListSentence, sentenceIndex, dummyNumber, numericalVariableName))
					{
						cout << "generateCodeBlocks{} error: !findDummyNumberAndReplaceWithOriginalNumericalVariableName, dummyNumericalValueToRestore = " << dummyNumber << ", numericalVariableName = " << numericalVariableName << endl;
					}
				}
				else
				{
					cout << "generateCodeBlocks{} error: currentNLCsentenceInList->variableNamesDetected && currentNLCsentenceInList->isMath" << endl;
				}
			}
		}
		#endif

		#ifdef NLC_PREPROCESSOR_MATH
		if(NLCtranslatorCodeBlocksLogicalConditionsAdvanced.getUseNLCpreprocessor() && (currentNLCsentenceInList->isMath))
		{

			//generateCodeBlocksFromMathText (including logical conditions) - added 1h1d;
			if(!NLCtranslatorCodeBlocksLogicalConditions.generateCodeBlocksFromMathText(&currentCodeBlockInTree, sentenceIter, sentenceIndex, currentNLCsentenceInList, NLCfunctionName))
			{
				result = false;
			}
		}
		else
		{
		#endif
			#ifdef NLC_GENERATE_UNIQUE_CONTEXT_BLOCK_FOR_EACH_SENTENCE
			//added 1q10b - used prevent redeclarations of xSubjectCategoryList/xObjectCategoryList//xCategoryList
			//NB createCodeBlocksCreateContextBlock be executed after generateObjectInitialisationsBasedOnConceptsForAllDefiniteEntities because newlyDeclaredEntityInCategoryList=false is set (ie category lists are not created)
			NLCcodeblock* firstCodeBlockInSentence = currentCodeBlockInTree;
			currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlocksCreateContextBlock(currentCodeBlockInTree);
			#endif

			//Part 3; subject object connections (object initialisations; actions, properties, conditions, redefinitions) (eg Tom rides the boat, Tom has a boat, Tom is near a boat, The dog is an Alsation)
			NLCgenerateContextBlocksVariables generateContextBlocksVariablesLogicalConditionStatement;	//not used
			if(!NLCtranslatorCodeBlocksOperations.generateCodeBlocksPart3subjectObjectConnections(&currentCodeBlockInTree, entityNodesActiveListSentence, sentenceIndex, &generateContextBlocksVariablesLogicalConditionStatement))
			{
				result = false;
			}

			#ifdef NLC_GENERATE_UNIQUE_CONTEXT_BLOCK_FOR_EACH_SENTENCE
			currentCodeBlockInTree = firstCodeBlockInSentence->next;
			#endif

		#ifdef NLC_PREPROCESSOR_MATH
		}
		#endif

		#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
		this->clearContextGeneratedVariable(entityNodesActiveListSentence);
		#endif


		#ifdef NLC_PREPROCESSOR
		if(NLCtranslatorCodeBlocksLogicalConditionsAdvanced.getUseNLCpreprocessor())
		{
			if(currentNLCsentenceInList->next != NULL)
			{
				#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
				NLCpreprocessorSentence* nextNLCsentenceInList = currentNLCsentenceInList->next;
				bool currentSentenceContainsLogicalCondition = currentNLCsentenceInList->hasLogicalConditionOperator;
				int currentLogicalConditionLevel = currentNLCsentenceInList->indentation;
				#else
				cout << "preprocessor error: !NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE" << endl;
				#endif

				if(nextNLCsentenceInList->indentation == (currentNLCsentenceInList->indentation + 1))
				{
					if(currentSentenceContainsLogicalCondition)
					{
						//indentation already correctly processed in NLCtranslatorCodeBlocksLogicalConditionsAdvanced.generateCodeBlocksPart2logicalConditions()
					}
					else
					{
						cout << "NLC_PREPROCESSOR generateCodeBlocks{} error: invalid indentation of nextNLCsentenceInList, sentenceIndex = " << sentenceIndex << endl;
						cout << "!currentSentenceContainsLogicalCondition && nextNLCsentenceInList->indentation == currentNLCsentenceInList->indentation + 1" << endl;
						cout << "currentNLCsentenceInList->indentation = " << currentNLCsentenceInList->indentation << endl;
						cout << "nextNLCsentenceInList->indentation = " << nextNLCsentenceInList->indentation << endl;
					}
				}
				else if(nextNLCsentenceInList->indentation == currentNLCsentenceInList->indentation)
				{
					if(currentSentenceContainsLogicalCondition)
					{
						//indentation already correctly processed in NLCtranslatorCodeBlocksLogicalConditionsAdvanced.generateCodeBlocksPart2logicalConditions()
					}
					else
					{
						//no changes
					}
				}
				else if(nextNLCsentenceInList->indentation < currentNLCsentenceInList->indentation)
				{
					if(currentLogicalConditionLevel == 0)
					{
						cout << "NLC_PREPROCESSOR generateCodeBlocks{} error: invalid indentation of currentNLCsentenceInList->next, sentenceIndex = " << sentenceIndex << endl;
						cout << "(currentLogicalConditionLevel == 0) && nextNLCsentenceInList->indentation < currentNLCsentenceInList->indentation" << endl;
						cout << "currentNLCsentenceInList->indentation = " << currentNLCsentenceInList->indentation << endl;
						cout << "nextNLCsentenceInList->indentation = " << nextNLCsentenceInList->indentation << endl;
					}
					else
					{
						currentCodeBlockInTree = NLCtranslatorCodeBlocksLogicalConditionsAdvanced.getCodeBlockAtPreviousLogicalConditionBaseLevelArray(nextNLCsentenceInList->indentation);
					}
				}
				else
				{
					cout << "NLC_PREPROCESSOR generateCodeBlocksPart2logicalConditions{} error: invalid indentation of nextNLCsentenceInList, sentenceIndex = " << sentenceIndex << endl;
					cout << "nextNLCsentenceInList->indentation > currentNLCsentenceInList->indentation + 1" << endl;
					cout << "currentNLCsentenceInList->indentation = " << currentNLCsentenceInList->indentation << endl;
					cout << "nextNLCsentenceInList->indentation = " << nextNLCsentenceInList->indentation << endl;
				}

				if(currentNLCsentenceInList->mathTextNLPparsablePhraseTotal > 0)
				{
					NLCpreprocessorParsablePhrase* currentParsablePhrase = currentNLCsentenceInList->firstNLPparsablePhraseInList;
					while(currentParsablePhrase->next != NULL)
					{	
						sentenceIter++;
						currentParsablePhrase = currentParsablePhrase->next;
					}
				}
				else
				{
					sentenceIter++;	
				}

				currentNLCsentenceInList = nextNLCsentenceInList;
			}
			else
			{
				sentenceIter++;	//standard iteration - go to last sentence in list (finish parsing full sentences)?
			}
						
			#ifdef NLC_LOGICAL_CONDITION_OPERATIONS_ADVANCED
			NLCtranslatorCodeBlocksLogicalConditionsAdvanced.setCurrentSentenceContainsLogicalCondition(false);
			#endif
		}
		else
		{
			sentenceIter++;	//standard iteration
		}
		#else
		sentenceIter++;	//standard iteration
		#endif
	}

	#ifdef NLC_ADVANCED_REFERENCING_MONITOR_CONTEXT
	#ifdef NLC_PREPROCESSOR
	#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
	if(NLCtranslatorCodeBlocksLogicalConditionsAdvanced.getUseNLCpreprocessor())
	{
		currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlocksClearContextListVariableExecuteFunction(currentCodeBlockInTree, 0);
	}
	#endif
	#endif
	#endif

	return result;
}

bool NLCtranslatorCodeBlocksClass::declareLocalPropertyListsForIndefiniteEntities(NLCcodeblock** currentCodeBlockInTree, vector<GIAentityNode*>* entityNodesActiveListComplete, const int sentenceIndex, const string NLCfunctionName, const NLCpreprocessorSentence* currentNLCsentenceInList)
{
	bool result = false;
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode* entity = (*entityIter);
		#ifdef NLC_DO_NOT_PREDECLARE_LOCAL_LISTS_FOR_QUALITIES
		if(!NLCtranslatorCodeBlocksOperations.checkSpecialCaseEntity(entity, true) && !(entity->entityType == GIA_ENTITY_TYPE_QUALITY))
		#else
		if(!NLCtranslatorCodeBlocksOperations.checkSpecialCaseEntity(entity, true))
		#endif
		{
			if(this->declareLocalPropertyListsForIndefiniteEntitiesValidClassChecks(entity))
			{
				#ifdef NLC_ADVANCED_REFERENCING_DECLARE_LOCAL_PROPERTY_LISTS_FOR_ALL_INDEFINITE_ENTITIES_FOR_ALL_SENTENCES
				if(!(entity->disabled))	//added 1k7f
				{
				#else
				if(NLCcodeBlockClass.checkSentenceIndexParsingCodeBlocks(entity, sentenceIndex, false))
				{
				#endif
					if(!NLCcodeBlockClass.assumedToAlreadyHaveBeenDeclared(entity))
					{//indefinite entity found
						if(this->declareLocalPropertyListsForIndefiniteEntity(currentCodeBlockInTree, entity, currentNLCsentenceInList))
						{
							result = true;
						}
					}
					#ifdef NLC_GENERATE_TYPE_LISTS_ADD_DEFINITE_FUNCTION_ARGUMENTS_TO_TYPE_LIST
					else
					{
						*currentCodeBlockInTree = NLCcodeBlockClass.createIfNecessaryAndAddToTypeList(*currentCodeBlockInTree, entity);
					}
					#endif
				}
			}
		}
	}
	return result;
}

bool NLCtranslatorCodeBlocksClass::declareLocalPropertyListsForIndefiniteEntity(NLCcodeblock** currentCodeBlockInTree, GIAentityNode* entity, const NLCpreprocessorSentence* currentNLCsentenceInList)
{
	bool result = true;

	*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlocksDeclareNewLocalListVariableIfNecessary(*currentCodeBlockInTree, entity);


	return result;
}

bool NLCtranslatorCodeBlocksClass::declareLocalPropertyListsForIndefiniteEntitiesValidClassChecks(GIAentityNode* entityNode)
{
	bool validClassContents = true;

	#ifdef NLC_PREPROCESSOR_INTERPRET_SINGLE_WORD_SENTENCES_AS_ACTIONS
	if(entityNode->entityName == NLC_PREPROCESSOR_INTERPRET_SINGLE_WORD_SENTENCES_AS_ACTIONS_DUMMY_TEXT_ACTION_OBJECT)
	{
		validClassContents = false;
	}
	#endif

	//added 1k7g
	if(NLCpreprocessorSentenceClass.isStringNumberOrFractional(entityNode->entityName))
	{
		validClassContents = false;
		//entityNode->disabled = true;	//this could be used instead (more general implementation)
	}

	//added 1q14e
	if(NLCpreprocessorSentenceClass.isStringAliasFileName(entityNode->entityName))
	{
		validClassContents = false;
	}

	#ifdef NLC_VERIFY_LEGAL_TARGET_SOURCE_CHARACTERS
	//added 1q14e - CHECKTHIS: is this required?
	if(NLCpreprocessorSentenceClass.isStringIllegalTargetSourceCharacter(entityNode->entityName))
	{
		if(validClassContents)
		{
			cout << "declareLocalPropertyListsForIndefiniteEntitiesValidClassChecks{} error: isStringIllegalTargetSourceCharacter; entityNode->entityName = " << entityNode->entityName << endl;
		}
		validClassContents = false;
	}
	#endif

	return validClassContents;
}











#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
bool NLCtranslatorCodeBlocksClass::clearContextGeneratedVariable(vector<GIAentityNode*>* entityNodesActiveListComplete)
{
	bool result = true;
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode* entity = *entityIter;
		entity->NLCcontextGenerated = false;
	}
	return result;
}
#endif


#ifdef NLC_GENERATE_OBJECT_INITIALISATIONS_BASED_ON_CONCEPTS_FOR_ALL_DEFINITE_ENTITIES
bool NLCtranslatorCodeBlocksClass::generateObjectInitialisationsBasedOnConceptsForAllDefiniteEntities(NLCcodeblock** currentCodeBlockInTree, vector<GIAentityNode*>* entityNodesActiveListSentence, int sentenceIndex)
{
	bool result = true;
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListSentence->begin(); entityIter != entityNodesActiveListSentence->end(); entityIter++)
	{
		GIAentityNode* entity = (*entityIter);
		
		if(!NLCtranslatorCodeBlocksOperations.checkSpecialCaseEntity(entity, true) && !(entity->entityType == GIA_ENTITY_TYPE_QUALITY))
		{
			if(entity->sentenceIndexTemp == sentenceIndex)	//changed 1l15a
			//if(checkSentenceIndexParsingCodeBlocks(entity, sentenceIndex, false))
			{
				if(!(entity->disabled))
				{
					if(NLCcodeBlockClass.assumedToAlreadyHaveBeenDeclared(entity))
					{//definite entity found

						NLCtranslatorCodeBlocksOperations.generateObjectInitialisationsBasedOnConcepts(entity, entity, currentCodeBlockInTree, sentenceIndex, false);
					}
				}
			}
		}
	}
	return result;
}
#endif


NLCcodeblock* NLCtranslatorCodeBlocksClass::createCodeBlockNewFunction(NLCcodeblock* currentCodeBlockInTree, string NLCfunctionName, vector<GIAentityNode*>* entityNodesActiveListComplete, constEffective NLCfunction* currentNLCfunctionInList)
{
	#ifdef NLC_INPUT_FUNCTION_LISTS
	//gets "fight" from "dog::fight"
	string functionName = "";
	bool hasFunctionOwnerClass = false;
	string functionOwnerName = "";
	bool hasFunctionObjectClass = false;
	string functionObjectName = "";
	NLCitemClass.parseFunctionNameFromNLCfunctionName(NLCfunctionName, &functionName, &functionOwnerName, &hasFunctionOwnerClass, &functionObjectName, &hasFunctionObjectClass);

	GIAentityNode* functionOwner = NULL;
	GIAentityNode* functionObject = NULL;
	GIAentityNode* function = NULL;
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode* entity = *entityIter;
		if(!(entity->entityType == GIA_ENTITY_TYPE_NETWORK_INDEX) && !(entity->entityType == GIA_ENTITY_TYPE_CONCEPT))
		{
			if(entity->entityName == functionOwnerName)
			{
				#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS_PASS_FIRST_INSTANCE
				if(entity->idInstance == GIA_ENTITY_ID_INSTANCE_FIRST_INSTANCE_ENTITY)
				{
				#endif
					entity->NLCisSingularArgument = true;	//formalFunctionArgumentCorrespondsToActionSubjectUseThisAlias
					entity->NLCparsedForCodeBlocks = true;

					functionOwner = entity;		
				#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS_PASS_FIRST_INSTANCE
				}
				#endif
			}
			else if(entity->entityName == functionObjectName)
			{
				#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS_PASS_FIRST_INSTANCE
				if(entity->idInstance == GIA_ENTITY_ID_INSTANCE_FIRST_INSTANCE_ENTITY)
				{
				#endif
					entity->NLCisSingularArgument = true;
					entity->NLCparsedForCodeBlocks = true;

					functionObject = entity;
				#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS_PASS_FIRST_INSTANCE
				}
				#endif
			}
			else if(entity->entityName == functionName)
			{
				entity->NLCisSingularArgument = true;
				entity->NLCparsedForCodeBlocks = true;

				function = entity;
			}
		}
	}
	#else
	string functionName = NLCfunctionName;
	#endif

	#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS
	if(hasFunctionOwnerClass)
	{
		#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS_PASS_FIRST_INSTANCE
		//updated 1v5a;
		if(functionOwner != NULL)
		{//functionOwner is used by the function definition: use functionOwner instance name
			NLCitem* functionOwnerItem = new NLCitem(functionOwner, NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION_OWNER);
			currentCodeBlockInTree->parameters.push_back(functionOwnerItem);
		}
		else
		{//functionOwner is not used by the function definition
		#endif
			NLCitem* functionOwnerItem = new NLCitem(functionOwnerName, NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION_OWNER);
			currentCodeBlockInTree->parameters.push_back(functionOwnerItem);
		#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS_PASS_FIRST_INSTANCE
		}
		#endif
	}
	#endif

	NLCitem* functionItem = new NLCitem(functionName, NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION);
	currentCodeBlockInTree->parameters.push_back(functionItem);

	#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS
	if(hasFunctionObjectClass)	//added 21 November 2013
	{
		#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS_PASS_FIRST_INSTANCE
		if(functionObject != NULL)
		{//functionObject is used by the function definition: use functionObject instance name
			NLCitem* functionObjectItem = new NLCitem(functionObject, NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION_OBJECT);
			currentCodeBlockInTree->parameters.push_back(functionObjectItem);
		}
		else
		{//functionObject is not used by the function definition
		#endif
			NLCitem* functionObjectItem = new NLCitem(functionObjectName, NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION_OBJECT);
			currentCodeBlockInTree->parameters.push_back(functionObjectItem);
		#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS_PASS_FIRST_INSTANCE
		}
		#endif
	}
	#endif

	#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS
	this->generateLocalFunctionArgumentsBasedOnImplicitDeclarations(entityNodesActiveListComplete, &(currentCodeBlockInTree->parameters), currentNLCfunctionInList);
	#endif

	currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlock(currentCodeBlockInTree, NLC_CODEBLOCK_TYPE_NEW_FUNCTION);

	#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS
	#ifndef NLC_FUNCTIONS_SUPPORT_PLURAL_SUBJECTS
	if(functionOwner != NULL)
	{
		currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockDeclareAndInitialiseVariableForActionSubject(currentCodeBlockInTree, functionOwner);
		currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlocksAddVariableToNewList(currentCodeBlockInTree, functionOwner);
	}
	#endif
	#ifndef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS_PASS_AS_LISTS
	if(functionObject != NULL)
	{
		currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlocksAddVariableToNewList(currentCodeBlockInTree, functionObject);
	}
	if(function != NULL)
	{
		currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlocksAddVariableToNewList(currentCodeBlockInTree, function);
	}
	#endif
	#endif

	return currentCodeBlockInTree;
}



#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS
void NLCtranslatorCodeBlocksClass::generateLocalFunctionArgumentsBasedOnImplicitDeclarations(vector<GIAentityNode*>* entityNodesActiveListComplete, vector<NLCitem*>* parameters, constEffective NLCfunction* currentNLCfunctionInList)
{
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode* entity = *entityIter;
		if(this->isDefiniteEntityInitialisation(entity, currentNLCfunctionInList))
		{

			#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS_SUPPORT_LOCAL_LISTS_USE_CLASS_NAMES
			if(!this->findIndefiniteEntityCorrespondingToDefiniteEntityInSameContext(entityNodesActiveListComplete, entity))	//NB this->findIndefiniteEntityCorrespondingToDefiniteEntityInSameContext() could be reimplemented to be performed during generateCodeBlocks() sentence parsing, but then generateLocalFunctionArgumentsBasedOnImplicitDeclarations() could not be decared at start of generateCodeBlocks(), ie it would have to be moved out of createCodeBlockNewFunction()
			{
			#endif

				#ifdef NLC_ADVANCED_REFERENCING_SUPPORT_ALIASES_PREVENT_ADDING_AS_FUNCTION_ARGUMENT
				bool entityIsAlias = false;
				string aliasClassName = "";
				if(NLCcodeBlockClass.findEntityNameInFunctionAliasList(entity->entityName, &aliasClassName))
				{
					entityIsAlias = true;
				}
				/*
				for(vector<GIAentityConnection*>::iterator entityNodeDefinitionListReverseIterator = entity->definitionReverseNodeList->begin(); entityNodeDefinitionListReverseIterator < entity->definitionReverseNodeList->end(); entityNodeDefinitionListReverseIterator++)
				{
					GIAentityConnection* definitionConnection = (*entityNodeDefinitionListReverseIterator);
					if(definitionConnection->isAlias)
					{
						entityIsAlias = true;
						cout << "entityIsAlias: " << entity->entityName << endl;
					}
				}
				*/
				if(!entityIsAlias)
				{
				#endif
					#ifdef NLC_TRANSLATOR_INTERPRET_PROPERNOUNS_WITH_DEFINITION_LINK_AS_NEWLY_DECLARED
					if(!this->findPropernounDefinitionLink(entityNodesActiveListComplete, entity))
					{
					#endif
						#ifdef NLC_ADVANCED_REFERENCING
						NLCitem* functionArgumentTemp = NULL;
						if(!NLCitemClass.findFunctionArgument(parameters, entity, NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_INSTANCE_OR_CLASS_LIST, &functionArgumentTemp))
						{
						#endif
							//detected "the x" without declaring x (ie implicit declaration)
							NLCitem* thisFunctionArgumentInstanceItem = new NLCitem(entity, NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_INSTANCE_OR_CLASS_LIST);
							parameters->push_back(thisFunctionArgumentInstanceItem);

							//added 1j5d
							#ifdef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES
							entity->NLClocalListVariableHasBeenDeclared = true;	//redundant
							#else
							GIAentityNode* networkIndexEntity = GIAtranslatorOperations.getPrimaryNetworkIndexNodeDefiningInstance(entity);
							if(!(networkIndexEntity->NLClocalListVariableHasBeenDeclared))	//redundant test
							{
								entity->NLClocalListVariableHasBeenDeclared = true;
								networkIndexEntity->NLClocalListVariableHasBeenDeclared = true;
							}
							#endif
						#ifdef NLC_ADVANCED_REFERENCING
						}
						#endif
					#ifdef NLC_TRANSLATOR_INTERPRET_PROPERNOUNS_WITH_DEFINITION_LINK_AS_NEWLY_DECLARED
					}
					#endif
				#ifdef NLC_ADVANCED_REFERENCING_SUPPORT_ALIASES
				}
				#endif
			#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS_SUPPORT_LOCAL_LISTS_USE_CLASS_NAMES
			}
			#endif
		}
	}
}


bool NLCtranslatorCodeBlocksClass::isDefiniteEntityInitialisation(GIAentityNode* entity, constEffective NLCfunction* currentNLCfunctionInList)
{
	bool foundDefiniteEntity = false;
	
	#ifdef NLC_TRANSLATOR_LOGICAL_CONDITIONS_BOOLEAN_STATEMENTS_INTERPRET_SUBJECT_AND_OBJECT_INDEPENDENTLY_SUPPORT_INDEFINITE_SUBJECT_PASS_AS_FUNCTION_ARGUMENT
	bool isLogicalConditionIndefiniteSubjectEntity = false;
	if(!NLCcodeBlockClass.isDefiniteEntity(entity))
	{
		if(entity->entityName != NLC_PREPROCESSOR_LOGICAL_CONDITION_DUMMY_TEXT_ACTION_OBJECT)
		{
			if(entity->entityType == GIA_ENTITY_TYPE_SUBSTANCE)
			{
				NLCpreprocessorSentence* sentence = NULL;
				if(NLCpreprocessorSentenceClass.getSentenceInFunction(entity->sentenceIndexTemp, currentNLCfunctionInList, &sentence))
				{
					if(NLCpreprocessorSentenceClass.sentencePertainsToLogicalCondition(sentence))
					{
						bool entityIsEffectiveSubject = false;

						bool foundAction = false;
						bool foundActionIncoming = false;
						bool foundChildEntity = false;
						int sentenceIndex = entity->sentenceIndexTemp;
						GIAentityNode* childEntity = NLCcodeBlockClass.getSameReferenceSetSubstanceNonQualityChild(entity, sentenceIndex, &foundChildEntity);

						GIAentityNode* targetEntity = NULL;
						GIAentityConnection* connection = NULL;
						if(NLCtranslatorCodeBlocksOperations.getEntityCheckSameReferenceSetAndSentence(childEntity, &targetEntity, &connection, sentenceIndex, false, GIA_ENTITY_VECTOR_CONNECTION_TYPE_CONDITION))
						{
							entityIsEffectiveSubject = true;
						}
						else if(NLCtranslatorCodeBlocksOperations.getEntityCheckSameReferenceSetAndSentence(childEntity, &targetEntity, &connection, sentenceIndex, false, GIA_ENTITY_VECTOR_CONNECTION_TYPE_PROPERTY))
						{
							entityIsEffectiveSubject = true;
						}
						else if(NLCtranslatorCodeBlocksOperations.getEntityCheckSameReferenceSetAndSentence(childEntity, &targetEntity, &connection, sentenceIndex, false, GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTION))
						{
							entityIsEffectiveSubject = true;
						}
						else if(NLCtranslatorCodeBlocksOperations.getEntityCheckSameReferenceSetAndSentence(entity, &targetEntity, &connection, sentenceIndex, false, GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTION_REVERSE))
						{
							foundActionIncoming = true;
							GIAentityNode* actionRelationshipSubjectEntity = NULL;
							GIAentityConnection* actionSubjectConnection = NULL;
							if(!NLCtranslatorCodeBlocksOperations.getEntityCheckSameReferenceSetAndSentence(targetEntity, &actionRelationshipSubjectEntity, &actionSubjectConnection, sentenceIndex, false, GIA_ENTITY_VECTOR_CONNECTION_TYPE_RELATIONSHIP_SUBJECT))
							{
								entityIsEffectiveSubject = true;	//this is required to sync with generateCodeBlocksPart3subjectObjectConnection implementation
							}
						}

						if(entityIsEffectiveSubject)
						{
							isLogicalConditionIndefiniteSubjectEntity = true;
						}
					}
				}
			}
		}
	}
	if(NLCcodeBlockClass.isDefiniteEntity(entity) || isLogicalConditionIndefiniteSubjectEntity)
	#else
	if(NLCcodeBlockClass.isDefiniteEntity(entity))
	#endif
	{
		if(!(entity->entityType == GIA_ENTITY_TYPE_NETWORK_INDEX))
		{
			#ifdef NLC_INPUT_FUNCTION_LISTS
			#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS_PASS_FIRST_INSTANCE
			if((!entity->NLCisSingularArgument) || (entity->idInstance != GIA_ENTITY_ID_INSTANCE_FIRST_INSTANCE_ENTITY))
			{
			#else
			if(!entity->NLCisSingularArgument)
			{
			#endif	
			#endif
				if(this->generateLocalFunctionArgumentsBasedOnImplicitDeclarationsValidClassChecks(entity))
				{
					foundDefiniteEntity = true;
				}
			#ifdef NLC_INPUT_FUNCTION_LISTS
			}
			#endif
		}
	}
	return foundDefiniteEntity;
}

bool NLCtranslatorCodeBlocksClass::generateLocalFunctionArgumentsBasedOnImplicitDeclarationsValidClassChecks(const GIAentityNode* entityNode)
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
	if(entityNode->entityType == GIA_ENTITY_TYPE_CONCEPT)
	{
		validClass = false;
	}
	
	return validClass;
}




#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS_SUPPORT_LOCAL_LISTS_USE_CLASS_NAMES
bool NLCtranslatorCodeBlocksClass::findIndefiniteEntityCorrespondingToDefiniteEntityInSameContext(vector<GIAentityNode*>* entityNodesActiveListComplete, const GIAentityNode* definiteEntity)
{
	bool foundIndefiniteEntity = false;

	#ifdef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES
	/*
	NB the following scenario;
		A red car.
		The green car...
	or this scenario;
		A car is next to the house.
		The car is red.
		The green car...
	or this scenario;
		The green car...
		A car is next to the house.
		The car is red.
	the red car will be advanced referenced to its indefinite originator (assume GIA_NLC_INTEGRATION:GIA_NLC_INTEGRATION_DEFINE_REFERENCE_CONTEXT_BY_TEXT_INDENTATION)
	*/
	foundIndefiniteEntity = false;
	#else
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode* entity = *entityIter;
		if(this->isIndefiniteEntityCorrespondingToDefiniteEntityInSameContext(entity, definiteEntity))
		{
			foundIndefiniteEntity = true;
		}
	}
	#endif
	return foundIndefiniteEntity;
}

bool NLCtranslatorCodeBlocksClass::isIndefiniteEntityCorrespondingToDefiniteEntityInSameContext(const GIAentityNode* indefiniteEntity, const GIAentityNode* definiteEntity)
{
	bool foundIndefiniteEntity = false;

	if(indefiniteEntity->entityName == definiteEntity->entityName)
	{
		if(!(indefiniteEntity->entityType == GIA_ENTITY_TYPE_CONCEPT))
		{		
			#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS_USE_MORE_PRECISE_BUT_REDUNDANT_FUNCTIONS
			if(!NLCcodeBlockClass.assumedToAlreadyHaveBeenDeclaredInitialisation(indefiniteEntity))
			#else
			if(!NLCcodeBlockClass.assumedToAlreadyHaveBeenDeclared(indefiniteEntity))
			#endif
			{
				if(((indefiniteEntity->grammaticalNumber == GRAMMATICAL_NUMBER_SINGULAR) && ((definiteEntity->grammaticalNumber == GRAMMATICAL_NUMBER_SINGULAR) || (definiteEntity->grammaticalNumber == GRAMMATICAL_NUMBER_UNDEFINED))) || (indefiniteEntity->grammaticalNumber == GRAMMATICAL_NUMBER_PLURAL))
				{
					int indentationDifferenceFound = INT_DEFAULT_VALUE;	//not used
					if(NLCtranslatorCodeBlocksOperations.checkIndefiniteEntityCorrespondingToDefiniteEntityInSameContext(indefiniteEntity, definiteEntity, &indentationDifferenceFound))
					{
						foundIndefiniteEntity = true;
					}
				}
			}
		}
	}

	return foundIndefiniteEntity;
}
#endif

#ifdef NLC_TRANSLATOR_INTERPRET_PROPERNOUNS_WITH_DEFINITION_LINK_AS_NEWLY_DECLARED
bool NLCtranslatorCodeBlocksClass::findPropernounDefinitionLink(vector<GIAentityNode*>* entityNodesActiveListComplete, const GIAentityNode* definiteEntity)
{
	//find a propernoun of the same name with a definition link within the context (function)
	//requirements: this function assumes that it will also be tested that the propernoun is not an alias
	bool foundPropernounDefinitionLink = false;
	if(definiteEntity->grammaticalProperNounTemp)
	{
		GIAentityNode* firstReferenceToPropernounInContext = NULL;
		int firstReferenceToPropernounInContextSentenceIndex = NLC_MAX_NUMBER_SENTENCES_PER_FUNCTION;
		for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
		{
			GIAentityNode* entity = *entityIter;
			if(entity->entityType != GIA_ENTITY_TYPE_NETWORK_INDEX)	//added 1u9a
			{
				if(entity->entityName == definiteEntity->entityName)
				{
					if(entity->grammaticalProperNounTemp)
					{
						if(entity->sentenceIndexTemp < firstReferenceToPropernounInContextSentenceIndex)
						{
							//NB this method doesn't support multiple declarations of a given propernoun in a given context (function)
							firstReferenceToPropernounInContextSentenceIndex = entity->sentenceIndexTemp;
							firstReferenceToPropernounInContext = entity;
						}
						for(vector<GIAentityConnection*>::iterator entityNodeDefinitionListIterator = entity->definitionNodeList->begin(); entityNodeDefinitionListIterator < entity->definitionNodeList->end(); entityNodeDefinitionListIterator++)
						{
							GIAentityConnection* definitionConnection = (*entityNodeDefinitionListIterator);
							GIAentityNode* definitionRelationshipObjectEntity = GIAtranslatorOperations.getDefinitionRelationshipObjectEntity(definitionConnection);
							if(definitionRelationshipObjectEntity->entityType == GIA_ENTITY_TYPE_CONCEPT)
							{
								if(definitionRelationshipObjectEntity->entityName != entity->entityName)	//ignore dream mode definitions connections
								{
									//if NLC ref, verify sentence index TODO
									//eg Africa is a country. Africa has a castle with knights.
									foundPropernounDefinitionLink = true;
								}
							}
						}
					}
				}
			}
		}
		if(foundPropernounDefinitionLink)
		{
			firstReferenceToPropernounInContext->NLCfirstInstanceOfProperNounInContext = true;	//so that the entity will be interpreted as a new declaration by isDefiniteEntity
		}
	}
	return foundPropernounDefinitionLink;
}
#endif


#endif
















