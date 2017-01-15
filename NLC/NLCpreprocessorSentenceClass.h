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
 * File Name: NLCpreprocessorSentenceClass.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2016 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 1v1a 11-October-2016
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/


#ifndef HEADER_NLC_PREPROCESSOR_SENTENCE_CLASS
#define HEADER_NLC_PREPROCESSOR_SENTENCE_CLASS

#include "NLCglobalDefs.h"

class NLCvariable
{
public:

	NLCvariable(void);
	~NLCvariable(void);

	string name;
	int type;
	string typeString;
};

class NLCsentence
{
public:

	NLCsentence(void);
	~NLCsentence(void);

	string sentenceContents;
	int sentenceIndex;
	int indentation;
	bool hasLogicalConditionOperator;	//set true for first parsable phrase only, or if no NLP parsable phrases [CHECKTHIS]
	#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
	int logicalConditionOperator;		//set true for first parsable phrase only, or if no NLP parsable phrases [CHECKTHIS]
	#endif
	#ifdef NLC_PREPROCESSOR_LOGICAL_CONDITION_USE_ROBUST_NLP_INDEPENDENT_CODE
	bool ifDetected;
	bool elseIfDetected;
	bool elseDetected;
	#endif
	#ifdef NLC_PREPROCESSOR_MATH
	bool isMath;		//set true for first parsable phrase only, or if no NLP parsable phrases
	string mathText;	//set for first parsable phrase only, or if no NLP parsable phrases
	int mathTextNLPparsablePhraseIndex;
	int mathTextNLPparsablePhraseTotal;	//set for first parsable phrase only, or if no NLP parsable phrases
	#ifdef NLC_PREPROCESSOR_RECORD_PARSABLE_PHRASE_POSITION_APPROXIMATE
	int mathTextNLPparsablePhrasePositionApproximate;	//rough position of parsable phrase within full sentence (first character); will not be accurate due to replaceLogicalConditionNaturalLanguageMathWithSymbolsEnd/restoreExplicitVariableTypes
	#endif
	#ifdef NLC_PREPROCESSOR_MATH_REPLACE_NUMERICAL_VARIABLES_NAMES_FOR_NLP
	vector<NLCvariable*> mathTextVariables;	//required to be recorded such that future instances of variable name in non-math text can be temporarily replaced with dummy number 9999 for NLP/GIA to parse
	vector<string> variableNamesDetected;	//record of original variable name that has been replaced by dummy number for NLP/GIA to parse
	#endif
	#ifdef NLC_USE_MATH_OBJECTS
	bool mathTextIdentifiesMathValue;
	//bool mathTextNLPparsablePhraseIdentifiesMathValue;
	#endif
	#endif
	#ifdef NLC_PREPROCESSOR_GENERATE_COMMENTS
	string sentenceOriginal;	//set for first parsable phrase only, or if no NLP parsable phrases
	string sentenceContentsOriginal;
	#endif
	#ifdef NLC_PREPROCESSOR_INTERPRET_SINGLE_WORD_SENTENCES_AS_ACTIONS_REPLACE_ACTION_ALSO_DUE_TO_NLP_LIMITATION
	string singleWordSentenceActionName;
	#endif
	NLCsentence* next;

};

class NLCfunction
{
public:

	NLCfunction(void);
	~NLCfunction(void);

	string NLCfunctionName;
	NLCsentence* firstNLCsentenceInFunction;
	NLCfunction* next;
};


#ifdef NLC_PREPROCESSOR_MATH
string generateMathTextNLPparsablePhraseReference(int sentenceIndexOfFullSentence, NLCsentence* currentPhrase);
#ifdef NLC_PREPROCESSOR_MATH_REPLACE_NUMERICAL_VARIABLES_NAMES_FOR_NLP
int generateDummyNumber(int predefinedVariableIndex);
#endif
#endif
bool isStringNLPparsableWord(string phrase, bool preprocessorMath);
bool isStringValidVariableName(string phrase, bool preprocessor);
bool isStringNumberPreprocessorMath(string phrase);
bool isStringNumberOrFractional(string phrase);
	bool isDecimalPlace(int indexOfCurrentToken, string* lineContents);
bool isStringAliasFileName(string phrase);
#ifdef NLC_VERIFY_LEGAL_TARGET_SOURCE_CHARACTERS
bool isStringIllegalTargetSourceCharacter(string phrase);
#endif
bool sentencePertainsToLogicalCondition(NLCsentence* currentNLCsentenceInList);

#endif
