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
 * File Name: NLCpreprocessorSentenceClass.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2014 Baxter AI (baxterai.com)
 * Project: Natural Language Programming Interface (compiler)
 * Project Version: 1k6a 14-October-2014
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/



#include <ctime>
#include <cstdlib>	//for random number generation
#include <cmath>

#include "NLCpreprocessorSentenceClass.h"
#include "SHAREDvars.h"

NLCsentence::NLCsentence(void)
{
	sentenceContents = "";
	sentenceIndex = 0;
	indentation = 0;
	hasLogicalConditionOperator = false;
	#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
	logicalConditionOperator = INT_DEFAULT_VALUE;
	#endif	
	#ifdef NLC_PREPROCESSOR_LOGICAL_CONDITION_USE_ROBUST_NLP_INDEPENDENT_CODE
	ifDetected = false;
	elseIfDetected = false;
	elseDetected = false;
	#endif
	#ifdef NLC_PREPROCESSOR_MATH
	isMath = false;
	mathText = "";
	mathTextNLPparsablePhraseIndex = INT_DEFAULT_VALUE;
	mathTextNLPparsablePhraseTotal = INT_DEFAULT_VALUE;
	#endif
	#ifdef NLC_PREPROCESSOR_GENERATE_COMMENTS
	sentenceOriginal = "";
	sentenceContentsOriginal = "";
	#endif
	#ifdef NLC_PREPROCESSOR_INTERPRET_SINGLE_WORD_SENTENCES_AS_ACTIONS_REPLACE_ACTION_ALSO_DUE_TO_NLP_LIMITATION
	singleWordSentenceActionName = "";
	#endif
	next = NULL;
}
NLCsentence::~NLCsentence(void)
{
}

NLCfunction::NLCfunction(void)
{
	functionName = "";
	firstNLCsentenceInFunction = new NLCsentence();
	next = NULL;
}
NLCfunction::~NLCfunction(void)
{
}

#ifdef NLC_PREPROCESSOR_MATH
string generateMathTextNLPparsablePhraseReference(int sentenceIndexOfFullSentence, NLCsentence * currentPhrase)
{
	#ifdef NLC_PREPROCESSOR_MATH_USE_HUMAN_READABLE_VARIABLE_NAMES
	string variableName = replaceAllOccurancesOfString(&(currentPhrase->sentenceContents), STRING_SPACE, "");
	variableName = replaceAllOccurancesOfString(&variableName, STRING_FULLSTOP, "");
	string mathTextNLPparsablePhraseReference = variableName + convertIntToString(sentenceIndexOfFullSentence);
	#else
	string mathTextNLPparsablePhraseReference = string(NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_REFERENCE) + string(NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_REFERENCE_PHRASE) + convertIntToString(currentPhrase->phraseIndex) + string(NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_REFERENCE_SENTENCE) + convertIntToString(sentenceIndexOfFullSentence);	
	#endif
	return mathTextNLPparsablePhraseReference;
}

#ifdef NLC_PREPROCESSOR_MATH_REPLACE_NUMERICAL_VARIABLES_NAMES_FOR_NLP
int generateDummyNumericalValue(int predefinedVariableIndex)
{
	int dummyNumericalValue = predefinedVariableIndex + NLC_PREPROCESSOR_MATH_DUMMY_NUMERICAL_VALUE_BASE;
	return dummyNumericalValue;
}
#endif

#endif





