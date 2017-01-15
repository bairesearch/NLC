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
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2016 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 1u9b 29-September-2016
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/


#ifndef HEADER_NLC_PREPROCESSOR_MATH
#define HEADER_NLC_PREPROCESSOR_MATH

#include "NLCglobalDefs.h"
#include "NLCpreprocessorSentenceClass.h"

#ifdef NLC_USE_PREPROCESSOR
#ifdef NLC_PREPROCESSOR_MATH

bool detectMathSymbolsInLine(string* lineContents);
bool detectAndReplaceIsEqualToNonLogicalConditionTextWithSymbol(string* lineContents, bool hasLogicalConditionOperator, bool isMathText);

#ifdef NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
bool splitMathDetectedLineLogicalConditionCommandIntoSeparateSentences(string* lineContents, int currentIndentation, NLCsentence* firstNLCsentenceInFullSentence, NLCsentence* firstSentenceInLogicalConditionCommandTemp, bool* detectedLogicalConditionCommand);
#endif

bool splitMathDetectedLineIntoNLPparsablePhrases(string* lineContents, NLCsentence** currentNLCsentenceInList, int* sentenceIndex, int currentIndentation, string* functionContents, NLCfunction* currentNLCfunctionInList, NLCfunction* firstNLCfunctionInList);
	bool findCharacterAtIndexOrAfterSpace(string* lineContents, int i, char characterToFind, int* indexOfCharacterFound);
	#ifdef NLC_PREPROCESSOR_MATH_SUPPORT_USER_VARIABLE_TYPE_DECLARATIONS
	bool replaceExplicitVariableTypesWithNLPparsablePhraseIllegalWords(string* lineContents);
	bool restoreExplicitVariableTypes(string* mathText);
	string replaceSubstringAtStartOfString(string* textOrig, string stringToFind, string replacementString);
	#endif
	void addNewMathTextVariable(NLCsentence* sentence, string variableName, int variableTypeObject);
	void removeLastMathTextVariable(NLCsentence* sentence);

#ifdef NLC_PREPROCESSOR_MATH_REPLACE_NUMERICAL_VARIABLES_NAMES_FOR_NLP
bool replaceNumericalVariablesWithDummyNumberIfNecessary(string* lineContents, NLCsentence* currentNLCsentenceInList, NLCfunction* currentNLCfunctionInList, NLCfunction* firstNLCfunctionInList);
	bool isWhiteSpaceOrInvalidWordCharacter(char c);
#endif

bool findPredefinedMathtextVariable(string* currentWord, NLCfunction* currentNLCfunctionInList, NLCfunction* firstNLCfunctionInList, NLCsentence* sentenceToIgnoreWhileSearching, int* variableType);
	#ifdef NLC_PREPROCESSOR_REPLACE_NUMERICAL_VARIABLES_DETECT_GLOBAL_NUMERICAL_VARIABLES
	bool findPredefinedMathtextVariableInAnyFunctions(string* currentWord, NLCfunction* firstNLCfunctionInList, NLCsentence* sentenceToIgnoreWhileSearching, int* variableType);	//allows global numerical variable definitions; not just local numerical variable definitions
	#endif
		bool findPredefinedMathtextVariableInFunction(string* currentWord, NLCfunction* currentNLCfunctionInList, NLCsentence* sentenceToIgnoreWhileSearching, int* variableType);

#ifdef NLC_USE_MATH_OBJECTS_ADVANCED_INFER_TYPE_BASED_ON_PREVIOUSLY_DECLARED_MATHTEXT_VARIABLES_ADVANCED
bool findMathTextVariableWithinMathText(string mathTextVariableName, string mathText);
#endif

#endif
#endif

#endif
