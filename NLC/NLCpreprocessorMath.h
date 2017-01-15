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
 * File Name: NLCpreprocessorMath.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2014 Baxter AI (baxterai.com)
 * Project: Natural Language Programming Interface (compiler)
 * Project Version: 1i4b 22-August-2014
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/


#ifndef HEADER_NLC_PREPROCESSOR_MATH
#define HEADER_NLC_PREPROCESSOR_MATH


#include <iostream>
#include <fstream>
#include <ctime>
#include <cstring>
#include <cstdlib>	//for random number generation
#include <cmath>
#include <string>
#include <vector>
using namespace std;

#include "NLCglobalDefs.h"
#include "NLCpreprocessorSentenceClass.h"

#ifdef NLC_USE_PREPROCESSOR
#ifdef NLC_PREPROCESSOR_MATH

bool detectMathSymbolsInLine(string * lineContents);
bool replaceExplicitVariableTypesWithNLPparsablePhraseIllegalWords(string * lineContents);
bool detectAndReplaceIsEqualToNonLogicalConditionTextWithSymbol(string * lineContents, bool hasLogicalConditionOperator, bool isMathText);

bool splitMathDetectedLineIntoNLPparsablePhrases(string * lineContents, NLCsentence ** currentNLCsentenceInList, int * sentenceIndex, int currentIndentation, string * functionContents, NLCfunction * currentNLCfunctionInList, NLCfunction * firstNLCfunctionInList);
#endif

#ifdef NLC_PREPROCESSOR_MATH_REPLACE_NUMERICAL_VARIABLES_NAMES_FOR_NLP
bool replaceNumericalVariablesWithDummyNameIfNecessary(string * lineContents, NLCsentence * currentNLCsentenceInList, NLCfunction * currentNLCfunctionInList, NLCfunction * firstNLCfunctionInList);
	bool isWhiteSpaceOrInvalidWordCharacter(char c);
	bool findPredefinedNumericalVariable(string * currentWord, NLCfunction * currentNLCfunctionInList, NLCfunction * firstNLCfunctionInList, NLCsentence * sentenceToIgnoreWhileSearching);
		#ifdef NLC_PREPROCESSOR_REPLACE_NUMERICAL_VARIABLES_DETECT_GLOBAL_NUMERICAL_VARIABLES
		bool findPredefinedNumericalVariableInAnyFunctions(string * currentWord, NLCfunction * firstNLCfunctionInList, NLCsentence * sentenceToIgnoreWhileSearching);	//allows global numerical variable definitions; not just local numerical variable definitions
		#endif
			bool findPredefinedNumericalVariableInFunction(string * currentWord, NLCfunction * currentNLCfunctionInList, NLCsentence * sentenceToIgnoreWhileSearching);
#endif
#endif

#endif
