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
 * Project Version: 1h2g 28-July-2014
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
	bool hasLogicalConditionOperator;
	#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
	int logicalConditionOperator;
	#endif
	#ifdef NLC_PREPROCESSOR_LOGICAL_CONDITION_USE_ROBUST_NLP_INDEPENDENT_CODE
	bool ifDetected;
	bool elseIfDetected;
	bool elseDetected;
	#endif
	#ifdef NLC_PREPROCESSOR_MATH
	bool isMath;		//set true for first parsable phrase only, or if no NLP parsable phrases
	string mathText;	//set true for first parsable phrase only, or if no NLP parsable phrases
	int mathTextNLPparsablePhraseIndex;
	int mathTextNLPparsablePhraseTotal;	//set true for first parsable phrase only, or if no NLP parsable phrases
	#ifdef NLC_PREPROCESSOR_MATH_REPLACE_NUMERICAL_VARIABLES_NAMES_FOR_NLP
	vector<string> mathTextVariableNames;	//required to be recorded such that future instances of variable name in non-math text can be temporarily replaced with dummy number 9999 for NLP/GIA to parse
	vector<string> variableNamesDetected;	//record of original variable name that has been replaced by dummy number for NLP/GIA to parse
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
	void writeStringToFile(string * fileName, string * s);
	void extractIndentationFromCurrentLine(string * currentLine, int * currentIndentation, string * lineContents, string * indentationContents);
	#ifdef NLC_SUPPORT_INPUT_FILE_LISTS
	bool detectFunctionHeader(string * lineContents);
	string getFunctionNameFromFunctionHeader(string * lineContents);
	#endif	
	bool detectLogicalConditionOperatorAtStartOfLine(string * lineContents, int * logicalConditionOperator);
	#ifdef NLC_PREPROCESSOR_MATH
	bool detectMathSymbolsInLine(string * lineContents);
	bool replaceExplicitVariableTypesWithNLPparsablePhraseIllegalWords(string * lineContents);
	bool detectAndReplaceIsEqualToNonLogicalConditionTextWithSymbol(string * lineContents, bool hasLogicalConditionOperator, bool isMathText);
	#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
	bool replaceLogicalConditionNaturalLanguageMathWithSymbols(string * lineContents, int logicalConditionOperator, bool * additionalClosingBracketRequired);
	#endif
	bool splitMathDetectedLineIntoNLPparsablePhrases(string * lineContents, NLCsentence ** currentNLCsentenceInList, int * sentenceIndex, int currentIndentation, string * functionContents, NLCfunction * currentNLCfunctionInList, NLCfunction * firstNLCfunctionInList, bool additionalClosingBracketRequired);
	string generateMathTextNLPparsablePhraseReference(int sentenceIndexOfFullSentence, NLCsentence * currentPhrase);
	#ifdef NLC_PREPROCESSOR_MATH_REPLACE_NUMERICAL_VARIABLES_NAMES_FOR_NLP
	bool replaceNumericalVariablesWithDummyNameIfNecessary(string * lineContents, NLCsentence * currentNLCsentenceInList, NLCfunction * currentNLCfunctionInList, NLCfunction * firstNLCfunctionInList);
		bool isWhiteSpaceOrInvalidWordCharacter(char c);
		bool findPredefinedNumericalVariable(string * currentWord, NLCfunction * currentNLCfunctionInList, NLCfunction * firstNLCfunctionInList, NLCsentence * sentenceToIgnoreWhileSearching);
			#ifdef NLC_PREPROCESSOR_REPLACE_NUMERICAL_VARIABLES_DETECT_GLOBAL_NUMERICAL_VARIABLES
			bool findPredefinedNumericalVariableInAnyFunctions(string * currentWord, NLCfunction * firstNLCfunctionInList, NLCsentence * sentenceToIgnoreWhileSearching);	//allows global numerical variable definitions; not just local numerical variable definitions
			#endif
				bool findPredefinedNumericalVariableInFunction(string * currentWord, NLCfunction * currentNLCfunctionInList, NLCsentence * sentenceToIgnoreWhileSearching);
		int generateDummyNumericalValue(int predefinedVariableIndex);
	#endif
	#endif
	#endif
#endif
