 /*******************************************************************************
 *
 * License: GNU Affero General Public License version 3 (AGPLv3)
 *
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: NLCtranslator.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2022 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler
 * Project Version: 2p1a 05-June-2022
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 * /
 *******************************************************************************/


#ifndef HEADER_NLC_TRANSLATOR
#define HEADER_NLC_TRANSLATOR

#include "GIAentityNodeClass.hpp"
#include "GIAentityConnectionClass.hpp"
#include "NLCglobalDefs.hpp"
#include "NLCcodeBlockClass.hpp"
#include "NLCclassDefinitionClass.hpp"
//#ifdef NLC_PREPROCESSOR
#include "NLCpreprocessorSentenceClass.hpp"	//required for NLCfunction
#include "NLCtranslatorCodeBlocks.hpp"
#include "NLCtranslatorCodeBlocksLogicalConditionsAdvanced.hpp"	//required for tagAllEntitiesInSentenceSubsetAsPertainingToLogicalConditionOperationAdvanced
#include "NLCtranslatorClassDefinitions.hpp"
#include "NLCtranslatorCodeBlocksOperations.hpp"	//required for initialiseFunctionAliasClassList()
//#endif


class NLCtranslatorClass
{
	private: NLCtranslatorCodeBlocksClass NLCtranslatorCodeBlocks;
	private: NLCtranslatorCodeBlocksLogicalConditionsAdvancedClass NLCtranslatorCodeBlocksLogicalConditionsAdvanced;
	private: NLCtranslatorClassDefinitionsClass NLCtranslatorClassDefinitions;
	private: SHAREDvarsClass SHAREDvars;
	private: NLCcodeBlockClassClass NLCcodeBlockClass;
	private: NLCclassDefinitionClassClass NLCclassDefinitionClass;
	private: NLCitemClassClass NLCitemClass;
	private: NLCpreprocessorSentenceClassClass NLCpreprocessorSentenceClass;
	public: bool translateNetwork(NLCcodeblock* firstCodeBlockInTree, vector<NLCclassDefinition*>* classDefinitionList, vector<GIAentityNode*>* entityNodesActiveListComplete, map<int, vector<GIAentityNode*>*>* entityNodesActiveListSentences, const int maxNumberSentences, string NLCfunctionName, NLCfunction* currentNLCfunctionInList, const bool useNLCpreprocessor);
	/*
	#ifdef NLC_CATEGORIES_TEST_PLURALITY_ENFORCE
	#ifdef NLC_PREPROCESSOR
	bool identifyImplicitPluralLogicalConditionOperationsObjects(vector<GIAentityNode*>* entityNodesActiveListComplete, int maxNumberSentences);
	#endif
	#endif
	*/
		private: bool disableAllForLoopPredeterminers(map<int, vector<GIAentityNode*>*>* entityNodesActiveListSentences, const int maxNumberSentences);
	/*
	#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE
	bool addFunctionDependenciesWithoutOwners(vector<GIAentityNode*>* entityNodesActiveListComplete, int maxNumberSentences, NLCclassDefinitionFunctionDependency* parentFunctionDependencies, vector<NLCclassDefinitionFunctionDependency*>* functionDependencyList);
	#endif
	*/

	#ifdef NLC_INPUT_FUNCTION_LISTS
	#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS
	public: void reconcileFunctionDefinitionClassDefinitionArgumentsBasedOnImplicitlyDeclaredVariablesInCurrentFunctionDefinition(NLCcodeblock* firstCodeBlockInTree, vector<NLCclassDefinition*>* classDefinitionList, NLCclassDefinition* functionDefinitionClassDefinition);
		#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_BASED_ON_IMPLICITLY_DECLARED_VARIABLES_IN_CURRENT_FUNCTION_DEFINITION
		#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
		private: void addImplicitlyDeclaredVariablesInCurrentFunctionDefinitionArgumentsToFunctionDefinition(vector<NLCitem*>* functionDefinitionSourceArgumentList, NLCclassDefinition* functionDefinition);
		#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE
		private: void addImplicitlyDeclaredVariablesInCurrentFunctionDefinitionToFunctionDefinition(NLCclassDefinition* functionDefinitionSource, NLCclassDefinition* functionDefinition);
		private: void addImplicitlyDeclaredVariablesInCurrentFunctionDefinitionToFunctionDefinitionArguments(NLCclassDefinition* functionDefinitionSource, vector<NLCitem*>* functionDefinitionArgumentList);
		#endif
		#else
		//bool findFormalFunctionArgumentCorrelateInExistingList(NLCclassDefinition* functionClassDefinition, vector<NLCitem*>* formalFunctionArgumentList, vector<NLCclassDefinition*>* classDefinitionList);
		#endif
		#endif
	#endif
	#endif
	#ifdef NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_SUPPORT_ALPHANUMERIC_ENTITY_NAMES_ONLY
	private: bool checkAlphaNumericEntityNames(vector<GIAentityNode*>* entityNodesActiveListComplete, const int maxNumberSentences);
	#endif

	public: bool createFunctionDefinitionClassDefinition(vector<NLCclassDefinition*>* classDefinitionList, string NLCfunctionName, const int functionDefinitionIndex, const bool libraryFunctionDeclaration);
		public: NLCclassDefinition* createFunctionDefinitionClassDefinition(vector<NLCclassDefinition*>* classDefinitionList, const string functionName, const string functionOwnerName, const string functionObjectName, const bool hasFunctionOwnerClass, const bool hasFunctionObjectClass, const string functionClassDefinitionName, const string functionOwnerClassDefinitionName, const int functionDefinitionIndex, const bool isReferenceElseFunctionDefinition);
};


#endif
