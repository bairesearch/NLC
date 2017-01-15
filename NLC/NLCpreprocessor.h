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
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2017 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 1w3a 14-January-2017
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/


#ifndef HEADER_NLC_PREPROCESSOR
#define HEADER_NLC_PREPROCESSOR

#include "NLCglobalDefs.h"
#include "NLCpreprocessorSentenceClass.h"


#ifdef NLC_PREPROCESSOR
bool preprocessTextForNLC(const string inputFileName, NLCfunction* firstNLCfunctionInList, bool* detectedFunctions, int* numberOfInputFilesInList, vector<string>* inputTextFileNameList, const string outputFileName);
	#ifdef NLC_PREPROCESSOR_REDUCE_QUOTES_TO_SINGLE_WORDS
	bool reduceQuotesToSingleWords(const string lineText, string* updatedLineText);
	#endif
	void addNonLogicalConditionSentenceToList(string* sentenceContents, NLCsentence** currentNLCsentenceInList, int* sentenceIndex, const int currentIndentation, NLCfunction* currentNLCfunctionInList, const NLCfunction* firstNLCfunctionInList);
	void extractIndentationFromCurrentLine(string* currentLine, int* currentIndentation, string* lineContents, string* indentationContents);
	#ifdef NLC_INPUT_FUNCTION_LISTS
	bool detectFunctionHeader(const string* lineContents);
	string getFunctionNameFromFunctionHeader(const string* lineContents);
	string generateNLCfunctionFileName(const string NLCfunctionName);
	#endif
	bool detectLogicalConditionOperatorAtStartOfLine(const string* lineContents, int* logicalConditionOperator);
	string removePrependingWhiteSpace(string sentenceContents);
	#ifdef NLC_MATH_OBJECTS_ADVANCED
	bool detectMathObjectStringDelimiter(string* lineContents);
	#endif
#endif

#endif
