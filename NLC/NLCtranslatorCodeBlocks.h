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
 * File Name: NLCtranslatorCodeBlocks.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2014 Baxter AI (baxterai.com)
 * Project: Natural Language Programming Interface (compiler)
 * Project Version: 1g4a 03-July-2014
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/


#ifndef HEADER_NLC_TRANSLATOR_CODEBLOCKS
#define HEADER_NLC_TRANSLATOR_CODEBLOCKS

//#define NLC_NOT_NECESSARY

#include <iostream>
#include <fstream>
#include <ctime>
#include <cstring>
#include <cstdlib>	//for random number generation
#include <cmath>
#include <string>
#include <vector>
using namespace std;

#include "GIAglobalDefs.h"
#include "GIAentityNodeClass.h"
#include "GIAentityConnectionClass.h"
#include "NLCcodeBlockClass.h"
#include "NLCclassDefinitionClass.h"

bool generateCodeBlocks(NLCcodeblock * firstCodeBlockInTree, vector<GIAentityNode*> * entityNodesActiveListComplete, int maxNumberSentences, string NLCfunctionName);
	#ifdef NLC_SUPPORT_CONDITION_LOGICAL_OPERATIONS
	bool generateCodeBlocksPart0(NLCcodeblock ** currentCodeBlockInTree, vector<GIAentityNode*> * entityNodesActiveListComplete, int sentenceIndex, string NLCfunctionName);
		bool searchForEquivalentSubnetToIfStatement(GIAentityNode * entityCompareConcept, GIAentityNode * entity);
		void tagAllEntitiesInSentenceSubsetAsPertainingToConditionLogicalOperation(GIAentityNode * entity, int sentenceIndex, bool tagOrUntag);
	#endif
	bool generateCodeBlocksPart1(NLCcodeblock ** currentCodeBlockInTree, vector<GIAentityNode*> * entityNodesActiveListComplete, int sentenceIndex, string NLCfunctionName);
		void generateActionCodeBlocks(NLCcodeblock ** currentCodeBlockInTree, GIAentityNode * actionEntity, int sentenceIndex, string NLCfunctionName);		//note this is a shared function with generateCodeBlocksPart0
			bool generateContextBlocksAndInitialiseParentIfNecessary(NLCcodeblock ** currentCodeBlockInTree, GIAentityNode * currentEntity, int sentenceIndex, int logicalOperation, bool negative);
			NLCcodeblock * generateConditionBlocks(NLCcodeblock * currentCodeBlockInTree, GIAentityNode * entity, NLCitem ** item, int sentenceIndex, bool * requiredTempVar, int itemType, int logicalOperation, bool negative);
		#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS
		void initialiseFunctionArguments(NLCcodeblock ** currentCodeBlockInTree, GIAentityNode * actionEntity, int sentenceIndex);
		#endif
	bool generateCodeBlocksPart2(NLCcodeblock ** currentCodeBlockInTree, vector<GIAentityNode*> * entityNodesActiveListComplete, int sentenceIndex, string NLCfunctionName);
		void generateInitialisationCodeBlock(NLCcodeblock ** currentCodeBlockInTree, GIAentityNode * entity , int sentenceIndex, string NLCfunctionName);	//note this is a shared function with generateCodeBlocksPart0
			GIAentityNode * getParent(GIAentityNode * currentEntity, int sentenceIndex);

//shared functions:
bool generateObjectInitialisationsBasedOnPropertiesAndConditions(GIAentityNode * entity, NLCcodeblock ** currentCodeBlockInTree, int sentenceIndex, string parentName, string parentConditionName);
	void generateObjectInitialisationsBasedOnPropertiesAndConditionsUpdateCodeBlockPointer(NLCcodeblock ** currentCodeBlockInTree, NLCcodeblock * firstCodeBlockBeforeRecursion, NLCcodeblock * firstCodeBlockInSection, bool performedAtLeastOneObjectInitialisationAtThisLevel, bool performedAtLeastOneObjectInitialisationAtALowerLevel, bool * performedAtLeastOneObjectInitialisation);
#ifdef GIA_TRANSLATOR_DREAM_MODE_LINK_SPECIFIC_CONCEPTS_AND_ACTIONS
void generateObjectInitialisationsBasedOnSubstanceConcepts(GIAentityNode * entity, NLCcodeblock ** currentCodeBlockInTree, int sentenceIndex);
	void generateObjectInitialisationsBasedOnSubstanceConceptsRecurse(GIAentityNode * entity, GIAentityNode * definitionEntity, NLCcodeblock ** currentCodeBlockInTree, int sentenceIndex, string parentName, string parentConditionName);
#endif

#endif
