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
 * File Name: NLCtranslatorCodeBlocksLogicalConditionsAdvanced.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2018 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler
 * Project Version: 2f7b 17-April-2018
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
