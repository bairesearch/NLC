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
 * File Name: NLCtranslatorCodeBlocksLogicalConditions.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2015 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 1q2c 18-August-2015
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/


#ifndef HEADER_NLC_TRANSLATOR_CODEBLOCKS_LOGICAL_CONDITIONS
#define HEADER_NLC_TRANSLATOR_CODEBLOCKS_LOGICAL_CONDITIONS

#include "GIAentityNodeClass.h"
#include "GIAentityConnectionClass.h"
#include "NLCglobalDefs.h"
#include "NLCcodeBlockClass.h"
#include "NLCclassDefinitionClass.h"
//#ifdef NLC_USE_PREPROCESSOR
#include "NLCpreprocessorSentenceClass.h"
//#endif


#ifdef NLC_PREPROCESSOR_MATH
bool generateCodeBlocksFromMathText(NLCcodeblock** currentCodeBlockInTree, map<int, vector<GIAentityNode*>*>::iterator sentenceIterFirstInFullSentence, int sentenceIndex, NLCsentence* firstNLCsentenceInFullSentence, string NLCfunctionName);
	bool generateCodeBlocksFromMathTextNLPparsablePhrase(NLCcodeblock** currentCodeBlockInTree, vector<GIAentityNode*>* entityNodesActiveListComplete, int sentenceIndex, NLCsentence* currentFullSentence, NLCsentence* parsablePhrase, int phraseIndex, int caseIndex);
		#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_BASED_ON_ACTIONS_BASIC
		bool checkIfPhraseContainsAction(vector<GIAentityNode*>* entityNodesActiveListComplete, int sentenceIndex, GIAentityNode** logicalConditionOperationObject);
		#endif
		#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_BASED_ON_CONCEPTS_BASIC
		bool checkIfPhraseContainsSubstanceConceptWithDefinitionLink(vector<GIAentityNode*>* entityNodesActiveListComplete, int sentenceIndex, GIAentityNode** logicalConditionOperationObject);
		#endif
		#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_BASED_ON_CONCEPTS_BASIC_DYNAMIC
		bool checkIfPhraseContainsSubstanceWithDefinitionLink(vector<GIAentityNode*>* entityNodesActiveListComplete, int sentenceIndex, GIAentityNode** logicalConditionOperationObject, GIAentityNode** definitionEntity);
		#endif
		void setDummyReferenceSetIDforAllEntitiesInPhrase(vector<GIAentityNode*>* entityNodesActiveListComplete, int sentenceIndex);
	bool generateCodeBlocksFromMathTextNLPparsablePhraseLogicalConditionFor(NLCcodeblock** currentCodeBlockInTree, vector<GIAentityNode*>* entityNodesActiveListComplete, int sentenceIndex, NLCsentence* currentFullSentence, NLCsentence* parsablePhrase, int phraseIndex, NLCcodeblock** currentCodeBlockInTreeAtBaseLevel, NLCsentence* firstNLCsentenceInFullSentence);
		bool parseParsablePhraseParent(NLCcodeblock** currentCodeBlockInTree, int sentenceIndex, GIAentityNode* parentEntity, NLCgenerateContextBlocksVariables* generateContextBlocksVariables, GIAentityNode** childEntity, int logicalConditionOperator);
#endif
#ifdef NLC_PREPROCESSOR_MATH_REPLACE_NUMERICAL_VARIABLES_NAMES_FOR_NLP
bool findAndSetDummyNumericalValueForReplacement(vector<GIAentityNode*>* entityNodesActiveListComplete, int sentenceIndex, int dummyNumericalValue, string numericalVariableName);
#endif
/*
#ifdef NLC_PREPROCESSOR_MATH
string parsablePhraseGenerateNumberOfElementCounterName(int phraseIndex);
#endif
*/
bool readParsablePhraseEntryEntityChecks(GIAentityNode* entity);

	
	
#endif
