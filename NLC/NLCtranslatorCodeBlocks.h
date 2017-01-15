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
 * Project Version: 1j9a 11-September-2014
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

#include "GIAentityNodeClass.h"
#include "GIAentityConnectionClass.h"
#include "NLCglobalDefs.h"
#include "NLCcodeBlockClass.h"
#include "NLCclassDefinitionClass.h"
//#ifdef NLC_USE_PREPROCESSOR
#include "NLCpreprocessorSentenceClass.h"
//#endif


bool generateCodeBlocks(NLCcodeblock * firstCodeBlockInTree, vector<GIAentityNode*> * entityNodesActiveListComplete, int maxNumberSentences, string NLCfunctionName, NLCfunction * currentNLCfunctionInList);
	#ifdef NLC_PREPROCESSOR_MATH
	bool generateCodeBlocksFromMathText(NLCcodeblock ** currentCodeBlockInTree, vector<GIAentityNode*> * entityNodesActiveListComplete, int sentenceIndex, NLCsentence * firstNLCsentenceInFullSentence, string NLCfunctionName);
		bool generateCodeBlocksFromMathTextNLPparsablePhrase(NLCcodeblock ** currentCodeBlockInTree, vector<GIAentityNode*> * entityNodesActiveListComplete, int sentenceIndex, NLCsentence * currentFullSentence, NLCsentence * parsablePhrase, int phraseIndex, int caseIndex);
		bool generateCodeBlocksFromMathTextNLPparsablePhraseLogicalConditionFor(NLCcodeblock ** currentCodeBlockInTree, vector<GIAentityNode*> * entityNodesActiveListComplete, int sentenceIndex, NLCsentence * currentFullSentence, NLCsentence * parsablePhrase, int phraseIndex);
	#endif
	bool declareLocalPropertyListsForIndefiniteEntities(NLCcodeblock ** currentCodeBlockInTree, vector<GIAentityNode*> * entityNodesActiveListComplete, int sentenceIndex, string NLCfunctionName, NLCsentence * currentNLCsentenceInList);	//added 1g8a 11-July-2014
	bool generateCodeBlocksPart3actions(NLCcodeblock ** currentCodeBlockInTree, vector<GIAentityNode*> * entityNodesActiveListComplete, int sentenceIndex, string NLCfunctionName);
	bool generateCodeBlocksPart4objectInitialisations(NLCcodeblock ** currentCodeBlockInTree, vector<GIAentityNode*> * entityNodesActiveListComplete, int sentenceIndex, string NLCfunctionName);
	
	#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
	bool clearContextGeneratedVariable(vector<GIAentityNode*> * entityNodesActiveListComplete);
	#endif

	#ifdef NLC_PREPROCESSOR_MATH_REPLACE_NUMERICAL_VARIABLES_NAMES_FOR_NLP
	bool findAndSetDummyNumericalValueForReplacement(vector<GIAentityNode*> * entityNodesActiveListComplete, int sentenceIndex, int dummyNumericalValue, string numericalVariableName);
	#endif
	/*
	#ifdef NLC_PREPROCESSOR_MATH
	string parsablePhraseGenerateNumberOfElementCounterName(int phraseIndex);
	#endif
	*/
	#ifdef NLC_GENERATE_OBJECT_INITIALISATIONS_BASED_ON_SUBSTANCE_CONCEPTS_FOR_ALL_DEFINITE_ENTITIES
	bool generateObjectInitialisationsBasedOnSubstanceConceptsForAllDefiniteEntities(NLCcodeblock ** currentCodeBlockInTree, vector<GIAentityNode*> * entityNodesActiveListComplete, int sentenceIndex);
	#endif
#endif
