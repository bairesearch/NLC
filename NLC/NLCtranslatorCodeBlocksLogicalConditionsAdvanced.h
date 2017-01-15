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
 * File Name: NLCtranslatorCodeBlocksLogicalConditionsAdvanced.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2016 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 1u12f 30-September-2016
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/


#ifndef HEADER_NLC_TRANSLATOR_CODEBLOCKS_LOGICAL_CONDITIONS_ADVANCED
#define HEADER_NLC_TRANSLATOR_CODEBLOCKS_LOGICAL_CONDITIONS_ADVANCED

#include "GIAentityNodeClass.h"
#include "GIAentityConnectionClass.h"
#include "NLCglobalDefs.h"
#include "NLCcodeBlockClass.h"
#include "NLCclassDefinitionClass.h"
#ifdef NLC_USE_PREPROCESSOR
#include "NLCpreprocessor.h"	//required for NLCsentence
#endif


#ifdef NLC_USE_PREPROCESSOR
void initialiseLogicalConditionLevelRecordArray(bool newUseNLCpreprocessor);
bool getUseNLCpreprocessor();
NLCcodeblock* getCodeBlockAtPreviousLogicalConditionBaseLevelArray(int index);
void setCodeBlockAtPreviousLogicalConditionBaseLevelArray(int index, NLCcodeblock* codeBlockToSet);
#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
bool getCurrentSentenceContainsLogicalCondition();
void setCurrentSentenceContainsLogicalCondition(bool value);
int getCurrentLogicalConditionCase(int level);
#endif
#endif

#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
bool generateCodeBlocksPart2logicalConditions(NLCcodeblock** currentCodeBlockInTree, vector<GIAentityNode*>* entityNodesActiveListSentence, int sentenceIndex, string NLCfunctionName, NLCsentence* currentNLCsentenceInList);
	#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS_ADVANCED
	void addNewLogicalCondition(NLCcodeblock** currentCodeBlockInTree, GIAentityNode* currentLogicalConditionObject, int sentenceIndex, int logicalOperation, int* logicalConditionConjunctionIndex, NLClogicalConditionConjunction* logicalConditionConjunctionArray, GIAentityNode* previousLogicalConditionConjunction);
		void checkConditionForLogicalCondition(NLCcodeblock** currentCodeBlockInTree, GIAentityNode* conditionEntity, int sentenceIndex, int logicalOperation, int* logicalConditionConjunctionIndex, NLClogicalConditionConjunction* logicalConditionConjunctionArray);
	#endif
	void tagAllEntitiesInSentenceSubsetAsPertainingToLogicalConditionOperationAdvanced(GIAentityNode* entity, int sentenceIndex, bool tagOrUntag);
#ifdef NLC_USE_PREPROCESSOR
bool setCurrentCodeBlockInTreeToStartOfIfStatement(NLCcodeblock** currentCodeBlockInTree, NLCcodeblock** firstCodeBlockAtStartOfIfStatement, NLCcodeblock* firstCodeBlockAtStartOfElseStatement, bool elseIfDetected, bool elseDetected);
bool restoreCurrentCodeBlockInTreeToStartOfElseStatement(NLCcodeblock** currentCodeBlockInTree, NLCcodeblock* firstCodeBlockAtStartOfIfStatement, NLCcodeblock* firstCodeBlockAtStartOfElseStatement, bool elseIfDetected, bool elseDetected, NLCcodeblock** previousCodeBlockInTree);
#endif
#endif

#ifdef GIA_TRANSLATOR_DREAM_MODE_LINK_SPECIFIC_CONCEPTS_AND_ACTIONS
bool searchForEquivalentSubnetToIfStatement(GIAentityNode* entityCompareNetworkIndex, GIAentityNode* entity, bool compareConcepts);
#endif

#endif
