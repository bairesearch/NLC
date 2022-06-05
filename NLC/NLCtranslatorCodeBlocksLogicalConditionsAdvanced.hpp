 /*******************************************************************************
 *
 * License: GNU Affero General Public License version 3 (AGPLv3)
 *
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: NLCtranslatorCodeBlocksLogicalConditionsAdvanced.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2022 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler
 * Project Version: 2p1a 05-June-2022
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 * /
 *******************************************************************************/


#ifndef HEADER_NLC_TRANSLATOR_CODEBLOCKS_LOGICAL_CONDITIONS_ADVANCED
#define HEADER_NLC_TRANSLATOR_CODEBLOCKS_LOGICAL_CONDITIONS_ADVANCED

#include "GIAentityNodeClass.hpp"
#include "GIAentityConnectionClass.hpp"
#include "NLCglobalDefs.hpp"
#include "NLCcodeBlockClass.hpp"
#include "NLCclassDefinitionClass.hpp"
#ifdef NLC_PREPROCESSOR
#include "NLCpreprocessorSentenceClass.hpp"	//required for NLCpreprocessorSentence
#include "NLCtranslatorCodeBlocksOperations.hpp"
#include "GIAquery.hpp"	//required for testReferencedEntityNodeForExactNameMatch2/traceEntityNode
#endif


#ifdef NLC_PREPROCESSOR
class NLCtranslatorCodeBlocksLogicalConditionsAdvancedClass
{
	private: NLCcodeBlockClassClass NLCcodeBlockClass;
	private: SHAREDvarsClass SHAREDvars;
	private: GIAtranslatorOperationsClass GIAtranslatorOperations;
	private: NLCtranslatorCodeBlocksOperationsClass NLCtranslatorCodeBlocksOperations;
	private: GIAqueryClass GIAquery;
	public: void initialiseLogicalConditionLevelRecordArray(const bool newUseNLCpreprocessor);
	public: bool getUseNLCpreprocessor();
	public: NLCcodeblock* getCodeBlockAtPreviousLogicalConditionBaseLevelArray(const int index);
	public: void setCodeBlockAtPreviousLogicalConditionBaseLevelArray(const int index, NLCcodeblock* codeBlockToSet);
	#endif

	#ifdef GIA_TRANSLATOR_DREAM_MODE_LINK_SPECIFIC_CONCEPTS_AND_ACTIONS
	public: bool searchForEquivalentSubnetToIfStatement(GIAentityNode* entityCompareNetworkIndex, GIAentityNode* entity, const bool compareConcepts);
	#endif
};


#endif
