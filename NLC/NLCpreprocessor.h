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
 * File Name: NLCpreprocessor.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2014 Baxter AI (baxterai.com)
 * Project: Natural Language Programming Interface (compiler)
 * Project Version: 1h1c 22-July-2014
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/


#ifndef HEADER_NLC_PREPROCESSOR
#define HEADER_NLC_PREPROCESSOR


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

class NLCsentence
{
public:

	NLCsentence(void);
	~NLCsentence(void);

	string sentenceContents;
	int sentenceIndex;
	int indentation;
	#ifdef NLC_PREPROCESSOR_LOGICAL_CONDITION_USE_ROBUST_NLP_INDEPENDENT_CODE
	bool ifDetected;
	bool elseIfDetected;
	bool elseDetected;
	#endif
	#ifdef NLC_PREPROCESSOR_SUPPORT_MATH
	bool isMath;
	string mathText;
	int mathTextNLPparsablePhraseIndex;
	#ifdef NLC_PREPROCESSOR_SUPPORT_MATH_DETECT_NUMERICAL_VARIABLES
	vector mathTextVariableNames;	//required to be recorded such that future instances of variable name in non-math text can be temporarily replaced with dummy number 9999 for NLP/GIA to parse
	vector variableNamesDetected;	//record of original variable name that has been replaced by dummy number for NLP/GIA to parse
	#endif
	#endif
	NLCsentence* next;
};

class NLCfunction
{
public:

	NLCfunction(void);
	~NLCfunction(void);

	string functionName;
	NLCsentence* firstNLCsentenceInFunction;
	NLCfunction* next;
};

#ifdef NLC_USE_PREPROCESSOR
bool preprocessTextForNLC(string inputFileName, NLCfunction * firstNLCfunctionInList, bool * detectedFunctions, int * numberOfInputFilesInList, vector<string> * inputTextFileNameList, string outputFileName);
void writeStringToFile(string fileName, string s);
#ifdef NLC_PREPROCESSOR_SUPPORT_MATH
bool detectMathSymbolsInSentence(string * sentenceContents);
bool splitMathDetectedSentenceIntoNLPparsablePhrases(string * sentenceContents, NLCsentence ** currentNLCsentenceInList, int * sentenceIndex, int currentIndentation);
string generateMathTextNLPparsablePhraseReference(int phraseIndex)
#ifdef NLC_PREPROCESSOR_SUPPORT_MATH_DETECT_NUMERICAL_VARIABLES
bool replaceCurrentWordWithDummyNameIfNecessary(string * currentWord, string * functionContents, string * sentenceContents, NLCsentence * currentNLCsentenceInList, NLCfunction * currentNLCfunctionInList, NLCfunction * firstNLCfunctionInList);
	bool findPredefinedNumericalVariable(string * currentWord, NLCfunction * currentNLCfunctionInList, NLCfunction * firstNLCfunctionInList);	//pass firstNLCfunctionInList and update findPredefinedNumericalVariable() accordingly to allow global numerical variable definitions; not just local numerical variable definitions
	string generateDummyNumericalValue(int predefinedVariableDetectedSentenceIndex);
#endif
#endif
#endif

#endif
