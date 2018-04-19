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
 * File Name: NLCtranslatorCodeBlocks.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2018 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler
 * Project Version: 2f6b 16-April-2018
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 * /
 *******************************************************************************/


#ifndef HEADER_NLC_TRANSLATOR_CODEBLOCKS
#define HEADER_NLC_TRANSLATOR_CODEBLOCKS

#include "GIAentityNodeClass.hpp"
#include "GIAentityConnectionClass.hpp"
#include "NLCglobalDefs.hpp"
#include "NLCcodeBlockClass.hpp"
#include "NLCclassDefinitionClass.hpp"
//#ifdef NLC_PREPROCESSOR
#include "NLCpreprocessorSentenceClass.hpp"
#include "NLCtranslatorCodeBlocksLogicalConditions.hpp"
#include "NLCtranslatorCodeBlocksLogicalConditionsAdvanced.hpp"
#include "NLCtranslatorCodeBlocksOperations.hpp"
#include "NLCprintDefs.hpp"	//required for NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION
#include "GIAtranslatorOperations.hpp"	//required for getPrimaryNetworkIndexNodeDefiningInstance()
//#endif


class NLCtranslatorCodeBlocksClass
{
	private: NLCcodeBlockClassClass NLCcodeBlockClass;
	private: NLCpreprocessorSentenceClassClass NLCpreprocessorSentenceClass;
	private: NLCtranslatorCodeBlocksLogicalConditionsClass NLCtranslatorCodeBlocksLogicalConditions;
	private: NLCtranslatorCodeBlocksLogicalConditionsAdvancedClass NLCtranslatorCodeBlocksLogicalConditionsAdvanced;
	private: NLCtranslatorCodeBlocksOperationsClass NLCtranslatorCodeBlocksOperations;
	private: NLCitemClassClass NLCitemClass;
	private: GIAtranslatorOperationsClass GIAtranslatorOperations;
	public: bool generateCodeBlocks(NLCcodeblock* firstCodeBlockInTree, vector<GIAentityNode*>* entityNodesActiveListComplete, map<int, vector<GIAentityNode*>*>* entityNodesActiveListSentences, const int maxNumberSentences, string NLCfunctionName, NLCfunction* currentNLCfunctionInList);
		private: NLCcodeblock* createCodeBlockNewFunction(NLCcodeblock* currentCodeBlockInTree, string NLCfunctionName, vector<GIAentityNode*>* entityNodesActiveListComplete, constEffective NLCfunction* currentNLCfunctionInList);
			#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS
			private: void generateLocalFunctionArgumentsBasedOnImplicitDeclarations(vector<GIAentityNode*>* entityNodesActiveListComplete, vector<NLCitem*>* parameters, constEffective NLCfunction* currentNLCfunctionInList);
				private: bool isDefiniteEntityInitialisation(GIAentityNode* entity, constEffective NLCfunction* currentNLCfunctionInList);
					private: bool generateLocalFunctionArgumentsBasedOnImplicitDeclarationsValidClassChecks(const GIAentityNode* entityNode);
				#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS_SUPPORT_LOCAL_LISTS_USE_CLASS_NAMES
				private: bool findIndefiniteEntityCorrespondingToDefiniteEntityInSameContext(vector<GIAentityNode*>* entityNodesActiveListComplete, const GIAentityNode* definiteEntity);
					private: bool isIndefiniteEntityCorrespondingToDefiniteEntityInSameContext(const GIAentityNode* indefiniteEntity, const GIAentityNode* definiteEntity);
				#endif
				#ifdef NLC_TRANSLATOR_INTERPRET_PROPERNOUNS_WITH_DEFINITION_LINK_AS_NEWLY_DECLARED
				private: bool findPropernounDefinitionLink(vector<GIAentityNode*>* entityNodesActiveListComplete, const GIAentityNode* definiteEntity);
				#endif
			#endif
		private: bool declareLocalPropertyListsForIndefiniteEntities(NLCcodeblock** currentCodeBlockInTree, vector<GIAentityNode*>* entityNodesActiveListComplete, const int sentenceIndex, const string NLCfunctionName, const NLCpreprocessorSentence* currentNLCsentenceInList);	//added 1g8a 11-July-2014
			private: bool declareLocalPropertyListsForIndefiniteEntitiesValidClassChecks(GIAentityNode* entityNode);
			private: bool declareLocalPropertyListsForIndefiniteEntity(NLCcodeblock** currentCodeBlockInTree, GIAentityNode* entity, const NLCpreprocessorSentence* currentNLCsentenceInList);
		#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
		private: bool clearContextGeneratedVariable(vector<GIAentityNode*>* entityNodesActiveListComplete);
		#endif

		#ifdef NLC_GENERATE_OBJECT_INITIALISATIONS_BASED_ON_CONCEPTS_FOR_ALL_DEFINITE_ENTITIES
		private: bool generateObjectInitialisationsBasedOnConceptsForAllDefiniteEntities(NLCcodeblock** currentCodeBlockInTree, vector<GIAentityNode*>* entityNodesActiveListSentence, int sentenceIndex);
		#endif
};
	

#endif
