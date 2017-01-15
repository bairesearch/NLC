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
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2016 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 1t2h 15-September-2016
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/


#include "NLCpreprocessorSentenceClass.h"
#include "SHAREDvars.h"


NLCvariable::NLCvariable(void)
{
	name = "";
	type = INT_DEFAULT_VALUE;
	typeString = "";
}
NLCvariable::~NLCvariable(void)
{
}

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
	#ifdef NLC_PREPROCESSOR_RECORD_PARSABLE_PHRASE_POSITION_APPROXIMATE
	mathTextNLPparsablePhrasePositionApproximate = INT_DEFAULT_VALUE;
	#endif
	#ifdef NLC_USE_MATH_OBJECTS
	mathTextIdentifiesMathValue = false;
	//mathTextNLPparsablePhraseIdentifiesMathValue = false;
	#endif
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
	NLCfunctionName = "";
	firstNLCsentenceInFunction = new NLCsentence();
	next = NULL;
}
NLCfunction::~NLCfunction(void)
{
}



#ifdef NLC_PREPROCESSOR_MATH
string generateMathTextNLPparsablePhraseReference(int sentenceIndexOfFullSentence, NLCsentence* currentPhrase)
{
	#ifdef NLC_PREPROCESSOR_MATH_USE_HUMAN_READABLE_VARIABLE_NAMES
	string variableName = replaceAllOccurancesOfString(&(currentPhrase->sentenceContents), STRING_SPACE, "");
	variableName = replaceAllOccurancesOfString(&variableName, STRING_FULLSTOP, "");
	variableName = replaceAllOccurancesOfString(&variableName, STRING_APOSTROPHE, "");
	#ifdef NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_SUPPORT_ALPHANUMERIC_ENTITY_NAMES_ONLY	
	//required for NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY
	for(int i=0; i<NLC_PREPROCESSOR_MATH_VARIABLE_NAME_CHARACTERS_ILLEGAL_AS_FIRST_NUMBER_OF_TYPES; i++)
	{
		if(variableName[0] == preprocessorMathVariableNameCharactersIllegalAsFirst[i])
		{
			variableName = string(NLC_PREPROCESSOR_MATH_VARIABLE_NAME_CHARACTERS_ILLEGAL_AS_FIRST_REPLACEMENT_CHARACTER) + variableName;
			#ifdef NLC_DEBUG
			//cout << "variableName = " << variableName << endl;
			#endif
		}
	}
	#endif
	#ifdef NLC_PREPROCESSOR_SUPPORT_IDENTICAL_PARSABLE_PHRASES_IN_SENTENCE
	string mathTextNLPparsablePhraseReference = variableName + string(NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_REFERENCE_SENTENCE) + convertIntToString(sentenceIndexOfFullSentence) + string(NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_REFERENCE_PHRASE) + convertIntToString(currentPhrase->mathTextNLPparsablePhraseIndex);	
	#else
	string mathTextNLPparsablePhraseReference = variableName + convertIntToString(sentenceIndexOfFullSentence);
	#endif
	#else
	string mathTextNLPparsablePhraseReference = string(NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_REFERENCE) + string(NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_REFERENCE_SENTENCE) + convertIntToString(sentenceIndexOfFullSentence) + string(NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_REFERENCE_PHRASE) + convertIntToString(currentPhrase->mathTextNLPparsablePhraseIndex);	
	#endif
	return mathTextNLPparsablePhraseReference;
}

#ifdef NLC_PREPROCESSOR_MATH_REPLACE_NUMERICAL_VARIABLES_NAMES_FOR_NLP
int generateDummyNumber(int predefinedVariableIndex)
{
	int dummyNumber = predefinedVariableIndex + NLC_PREPROCESSOR_MATH_DUMMY_NUMBER_VALUE_BASE;
	return dummyNumber;
}
#endif

#endif

//isStringNLPparsableWord: either variable name or all numbers
bool isStringNLPparsableWord(string phrase, bool preprocessorMath)
{
	bool stringIsNLPparsableWord = false;
	if(phrase.length() == 0)
	{
		#ifdef NLC_DEBUG
		//cout << "isStringNLPparsableWord{} error: phrase.length() == 0" << endl;
		#endif
	}
	
	if(isStringValidVariableName(phrase, preprocessorMath))
	{
		stringIsNLPparsableWord = true;
	}
	#ifdef NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_SUPPORT_ALPHANUMERIC_VARIABLE_NAMES_SUPPORT_FRACTIONAL_VALUES
	if(preprocessorMath)
	{
	#endif
		//eg "If 3 baskets have a pie, eat the apple." <- don't interpret "3" as math, interpret as an NLP parsable phrase entity
		if(isStringNumberPreprocessorMath(phrase))
		{
			stringIsNLPparsableWord = true;
		}
	#ifdef NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_SUPPORT_ALPHANUMERIC_VARIABLE_NAMES_SUPPORT_FRACTIONAL_VALUES
	}
	else
	{
		if(isStringNumberOrFractional(phrase))
		{
			stringIsNLPparsableWord = true;
		}	
	}
	#endif
	
	#ifdef NLC_DEBUG
	//cout << "isStringNLPparsableWord: " << phrase << " = " << stringIsNLPparsableWord << endl;
	#endif
	return stringIsNLPparsableWord;
}

//isStringValidVariableName: alphanumeric string but can't start with number 
bool isStringValidVariableName(string phrase, bool preprocessor)
{
	if(phrase.length() == 0)
	{
		#ifdef NLC_DEBUG
		//cout << "isStringValidVariableName{} error: phrase.length() == 0" << endl;
		#endif
	}
	
	bool stringIsNLPparsableWord = true;
	bool variableNameMandatoryCharacterFoundInCurrentWord = false;
	for(int i=0; i<phrase.length(); i++)
	{
		char c = phrase[i];
		bool legalWordCharacterFound;
		if(preprocessor)
		{
			legalWordCharacterFound = charInCharArray(c, preprocessorMathNLPparsableCharacters, NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_CHARACTERS_NUMBER_OF_TYPES);
		}
		else
		{
			legalWordCharacterFound = charInCharArray(c, NLPparsableCharacters, NLC_NLP_PARSABLE_PHRASE_CHARACTERS_NUMBER_OF_TYPES);			
		}
		if(!legalWordCharacterFound)
		{
			stringIsNLPparsableWord = false;
			#ifdef NLC_DEBUG
			//cout << "!legalWordCharacterFound: " << c << endl;
			//cout << "phrase = " << phrase << endl;
			//cout << "i = " << i << endl;
			#endif
		}	
		if(charInCharArray(c, preprocessorMathVariableNameCharactersMandatory, NLC_PREPROCESSOR_MATH_VARIABLE_NAME_CHARACTERS_MANDATORY_NUMBER_OF_TYPES))
		{
			variableNameMandatoryCharacterFoundInCurrentWord = true;
		}
	}
	if(!variableNameMandatoryCharacterFoundInCurrentWord)
	{
		#ifdef NLC_DEBUG
		//cout << "!variableNameMandatoryCharacterFoundInCurrentWord" << endl;
		#endif
		stringIsNLPparsableWord = false;
	}
	#ifdef NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_SUPPORT_ALPHANUMERIC_VARIABLE_NAMES_ONLY
	bool illegalFirstWordCharacterFound = charInCharArray(phrase[0], preprocessorMathVariableNameCharactersIllegalAsFirst, NLC_PREPROCESSOR_MATH_VARIABLE_NAME_CHARACTERS_ILLEGAL_AS_FIRST_NUMBER_OF_TYPES);
	if(illegalFirstWordCharacterFound)
	{
		stringIsNLPparsableWord = false;
	}
	#endif

	#ifdef NLC_DEBUG
	//cout << "isStringValidVariableName: " << phrase << " = " << stringIsNLPparsableWord << endl;
	#endif
	return stringIsNLPparsableWord;
}

//all numbers
bool isStringNumberPreprocessorMath(string phrase)
{
	bool stringIsNumber = true;
	if(phrase.length() == 0)
	{
		#ifdef NLC_DEBUG
		//cout << "isStringNumberPreprocessorMath{} error: phrase.length() == 0" << endl;
		#endif
	}
	for(int i=0; i<phrase.length(); i++)
	{
		char c = phrase[i];	
		bool numberFound = charInCharArray(c, preprocessorMathNLPparsableNumericalCharacters, NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_NUMERICAL_CHARACTERS_NUMBER_OF_TYPES);
		if(!numberFound)
		{
			stringIsNumber = false;
		}
	}
	#ifdef NLC_DEBUG
	//cout << "isStringNumberPreprocessorMath: " << phrase << " = " << stringIsNumber << endl;
	#endif
	return stringIsNumber;
}

bool isStringNumberOrFractional(string phrase)
{
	bool stringIsNumberOrFractional = true;
	if(phrase.length() == 0)
	{
		#ifdef NLC_DEBUG
		//cout << "isStringNumberOrFractional{} error: phrase.length() == 0" << endl;
		#endif
	}
	for(int i=0; i<phrase.length(); i++)
	{
		char c = phrase[i];	
		bool numberFound = charInCharArray(c, preprocessorMathNLPparsableNumericalCharacters, NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_NUMERICAL_CHARACTERS_NUMBER_OF_TYPES);
		bool decimalPlaceFound = isDecimalPlace(i, &phrase);
		if(!(numberFound || decimalPlaceFound))
		{
			stringIsNumberOrFractional = false;
		}
	}
	#ifdef NLC_DEBUG
	//cout << "isStringNumberOrFractional: " << phrase << " = " << stringIsNumberOrFractional << endl;
	#endif
	return stringIsNumberOrFractional;
}

//based on isIntrawordPunctuationMark{}
bool isDecimalPlace(int indexOfCurrentToken, string* lineContents)
{
	bool decimalPlace = false;
	char currentToken = (*lineContents)[indexOfCurrentToken];
	if(currentToken == CHAR_FULLSTOP) 
	{
		if(indexOfCurrentToken < lineContents->length()-1)	//ensure fullstop is not immediately succeded by an numeric character, which indicates a decimal place, eg "5.5"
		{	
			char characterImmediatelySucceedingPunctuationMark = (*lineContents)[indexOfCurrentToken+1];
			bool isPunctuationMarkImmediatelySucceededByNumericCharacter = charInCharArray(characterImmediatelySucceedingPunctuationMark, preprocessorMathNLPparsableNumericalCharacters, NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_NUMERICAL_CHARACTERS_NUMBER_OF_TYPES);
			if(isPunctuationMarkImmediatelySucceededByNumericCharacter)
			{
				decimalPlace = true;
			}		
		}
	}
	return decimalPlace;
}

//simple algorithm just detects full stops
bool isStringAliasFileName(string phrase)
{
	bool stringIsAliasFileName = false;
	for(int i=0; i<phrase.length(); i++)
	{
		char c = phrase[i];
		if(c == CHAR_FULLSTOP)
		//if(!charInCharArray(c, preprocessorMathNLPparsableCharactersMandatory, NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_CHARACTERS_MANDATORY_NUMBER_OF_TYPES))
		{
			stringIsAliasFileName = true;
		}
	}
	return stringIsAliasFileName;
}

#ifdef NLC_VERIFY_LEGAL_TARGET_SOURCE_CHARACTERS
bool isStringIllegalTargetSourceCharacter(string phrase)
{
	bool stringContainsIllegalTargetSourceCharacter = false;
	for(int i=0; i<phrase.length(); i++)
	{
		char c = phrase[i];
		if(!charInCharArray(c, legalTargetSourceCharacters, NLC_VERIFY_LEGAL_TARGET_SOURCE_CHARACTERS_NUMBER_OF_TYPES))
		{
			stringContainsIllegalTargetSourceCharacter = true;
		}
	}
	return stringContainsIllegalTargetSourceCharacter;
}
#endif
	
bool sentencePertainsToLogicalCondition(NLCsentence* currentNLCsentenceInList)
{
	bool result = false; 
	if(currentNLCsentenceInList->hasLogicalConditionOperator || currentNLCsentenceInList->mathTextNLPparsablePhraseIndex != NLC_PREPROCESSOR_MATH_FIRST_PARSABLE_PHRASE_INDEX)
	{
		result = true;	//sentence pertains to a logical condition (first parsable phrase in a logical condition || non-first parsable phrase in a logical condition)
	}
	return result;
}

