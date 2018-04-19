/*******************************************************************************
 *
 * No License
 * 
 * This work is under exclusive copyright (c) Baxter AI (baxterai.com). 
 * Nobody else can use, copy, distribute, or modify this work without being 
 * at risk of take-downs, shake-downs, or litigation. 
 * 
 * By publishing this source code in a public repository on GitHub, Terms of 
 * Service have been accepted by which Baxter AI have allowed others to view 
 * and fork their repository.
 * 
 * If you find software that doesn't have a license, that generally means you 
 * have no permission from the creators of the software to use, modify, or 
 * share the software. Although a code host such as GitHub may allow you to 
 * view and fork the code, this does not imply that you are permitted to use, 
 * modify, or share the software for any purpose.
 *
 * This notice has been derived from https://choosealicense.com/no-permission 
 * (https://web.archive.org/web/20180312144938/https://choosealicense.com/no-permission)
 *
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: NLCpreprocessorSentenceClass.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2018 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler
 * Project Version: 2f8b 18-April-2018
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 * /
 *******************************************************************************/


#include "NLCpreprocessorSentenceClass.hpp"


NLCvariable::NLCvariable(void)
{
	name = "";
	type = INT_DEFAULT_VALUE;
	typeString = "";
}
NLCvariable::~NLCvariable(void)
{
}

NLCpreprocessorParsablePhrase::NLCpreprocessorParsablePhrase(void)
{
	sentenceIndex = 0;
	//sentenceContents = "";
	#ifdef NLC_PREPROCESSOR_MATH;
	mathTextNLPparsablePhraseIndex = INT_DEFAULT_VALUE;
	#ifdef NLC_PREPROCESSOR_RECORD_PARSABLE_PHRASE_POSITION_APPROXIMATE
	mathTextNLPparsablePhrasePositionApproximate = INT_DEFAULT_VALUE;
	#endif
	#endif
	
	next = NULL;
}
NLCpreprocessorParsablePhrase::~NLCpreprocessorParsablePhrase(void)
{
}

NLCpreprocessorSentence::NLCpreprocessorSentence(void)
{
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
	mathTextNLPparsablePhraseTotal = INT_DEFAULT_VALUE;
	firstNLPparsablePhraseInList = new NLCpreprocessorParsablePhrase();
	#ifdef NLC_PREPROCESSOR_RECORD_PARSABLE_PHRASE_POSITION_APPROXIMATE
	mathTextNLPparsablePhrasePositionApproximate = INT_DEFAULT_VALUE;
	#endif
	#ifdef NLC_MATH_OBJECTS
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
	isBlankSentence = false;
	
	next = NULL;
}
NLCpreprocessorSentence::~NLCpreprocessorSentence(void)
{
}

NLCfunction::NLCfunction(void)
{
	#ifdef USE_NLCI
	lineIndexOfFunctionHeaderTemp = 0;
	functionIndexTemp = 0;
	#endif
	NLCfunctionName = "";
	functionContentsRaw = "";
	firstNLCprepreprocessorSentenceInList = NULL;
	firstGIApreprocessorSentenceInList = NULL;
	firstNLCsentenceInFunction = new NLCpreprocessorSentence();
	next = NULL;
}
NLCfunction::~NLCfunction(void)
{
}



#ifdef NLC_PREPROCESSOR_MATH
string NLCpreprocessorSentenceClassClass::generateMathTextNLPparsablePhraseReference(const int sentenceIndexOfFullSentence, const NLCpreprocessorParsablePhrase* currentPhrase)
{
	#ifdef NLC_PREPROCESSOR_MATH_USE_HUMAN_READABLE_VARIABLE_NAMES
	string variableName = GIApreprocessorWordClassObject.generateTextFromVectorWordList(&(currentPhrase->sentenceContents));
	variableName = SHAREDvars.replaceAllOccurancesOfString(&variableName, STRING_SPACE, "");
	variableName = SHAREDvars.replaceAllOccurancesOfString(&variableName, STRING_FULLSTOP, "");
	variableName = SHAREDvars.replaceAllOccurancesOfString(&variableName, STRING_APOSTROPHE, "");
	#ifdef NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_SUPPORT_ALPHANUMERIC_ENTITY_NAMES_ONLY
	//required for NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY
	for(int i=0; i<NLC_PREPROCESSOR_MATH_VARIABLE_NAME_CHARACTERS_ILLEGAL_AS_FIRST_NUMBER_OF_TYPES; i++)
	{
		if(variableName[0] == preprocessorMathVariableNameCharactersIllegalAsFirst[i])
		{
			variableName = string(NLC_PREPROCESSOR_MATH_VARIABLE_NAME_CHARACTERS_ILLEGAL_AS_FIRST_REPLACEMENT_CHARACTER) + variableName;
		}
	}
	#endif
	#ifdef NLC_PREPROCESSOR_SUPPORT_IDENTICAL_PARSABLE_PHRASES_IN_SENTENCE
	string mathTextNLPparsablePhraseReference = variableName + string(NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_REFERENCE_SENTENCE) + SHAREDvars.convertIntToString(sentenceIndexOfFullSentence) + string(NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_REFERENCE_PHRASE) + SHAREDvars.convertIntToString(currentPhrase->mathTextNLPparsablePhraseIndex);
	#else
	string mathTextNLPparsablePhraseReference = variableName + SHAREDvars.convertIntToString(sentenceIndexOfFullSentence);
	#endif
	#else
	string mathTextNLPparsablePhraseReference = string(NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_REFERENCE) + string(NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_REFERENCE_SENTENCE) + SHAREDvars.convertIntToString(sentenceIndexOfFullSentence) + string(NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_REFERENCE_PHRASE) + SHAREDvars.convertIntToString(currentPhrase->mathTextNLPparsablePhraseIndex);
	#endif
	return mathTextNLPparsablePhraseReference;
}

#ifdef NLC_PREPROCESSOR_MATH_REPLACE_NUMERICAL_VARIABLES_NAMES_FOR_NLP
int NLCpreprocessorSentenceClassClass::generateDummyNumber(const int predefinedVariableIndex)
{
	int dummyNumber = predefinedVariableIndex + NLC_PREPROCESSOR_MATH_DUMMY_NUMBER_VALUE_BASE;
	return dummyNumber;
}
#endif

#endif

//isStringNLPparsableWord: either variable name or all numbers
bool NLCpreprocessorSentenceClassClass::isStringNLPparsableWord(string phrase, const bool preprocessorMath)
{
	bool stringIsNLPparsableWord = false;
	if(phrase.length() == 0)
	{
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

	return stringIsNLPparsableWord;
}

//isStringValidVariableName: alphanumeric string but can't start with number
bool NLCpreprocessorSentenceClassClass::isStringValidVariableName(string phrase, const bool preprocessor)
{
	if(phrase.length() == 0)
	{
	}

	bool stringIsNLPparsableWord = true;
	bool variableNameMandatoryCharacterFoundInCurrentWord = false;
	for(int i=0; i<phrase.length(); i++)
	{
		char c = phrase[i];
		bool legalWordCharacterFound;
		if(preprocessor)
		{
			legalWordCharacterFound = SHAREDvars.charInCharArray(c, preprocessorMathNLPparsableCharacters, NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_CHARACTERS_NUMBER_OF_TYPES);
		}
		else
		{
			legalWordCharacterFound = SHAREDvars.charInCharArray(c, NLPparsableCharacters, NLC_NLP_PARSABLE_PHRASE_CHARACTERS_NUMBER_OF_TYPES);
		}
		if(!legalWordCharacterFound)
		{
			stringIsNLPparsableWord = false;
		}
		if(SHAREDvars.charInCharArray(c, preprocessorMathVariableNameCharactersMandatory, NLC_PREPROCESSOR_MATH_VARIABLE_NAME_CHARACTERS_MANDATORY_NUMBER_OF_TYPES))
		{
			variableNameMandatoryCharacterFoundInCurrentWord = true;
		}
	}
	if(!variableNameMandatoryCharacterFoundInCurrentWord)
	{
		stringIsNLPparsableWord = false;
	}
	#ifdef NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_SUPPORT_ALPHANUMERIC_VARIABLE_NAMES_ONLY
	bool illegalFirstWordCharacterFound = SHAREDvars.charInCharArray(phrase[0], preprocessorMathVariableNameCharactersIllegalAsFirst, NLC_PREPROCESSOR_MATH_VARIABLE_NAME_CHARACTERS_ILLEGAL_AS_FIRST_NUMBER_OF_TYPES);
	if(illegalFirstWordCharacterFound)
	{
		stringIsNLPparsableWord = false;
	}
	#endif

	return stringIsNLPparsableWord;
}

//all numbers
bool NLCpreprocessorSentenceClassClass::isStringNumberPreprocessorMath(const string phrase)
{
	bool stringIsNumber = true;
	if(phrase.length() == 0)
	{
	}
	for(int i=0; i<phrase.length(); i++)
	{
		char c = phrase[i];
		bool numberFound = SHAREDvars.charInCharArray(c, preprocessorMathNLPparsableNumericalCharacters, NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_NUMERICAL_CHARACTERS_NUMBER_OF_TYPES);
		if(!numberFound)
		{
			stringIsNumber = false;
		}
	}
	return stringIsNumber;
}

bool NLCpreprocessorSentenceClassClass::isStringNumberOrFractional(const string phrase)
{
	bool stringIsNumberOrFractional = true;
	if(phrase.length() == 0)
	{
	}
	for(int i=0; i<phrase.length(); i++)
	{
		char c = phrase[i];
		bool numberFound = SHAREDvars.charInCharArray(c, preprocessorMathNLPparsableNumericalCharacters, NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_NUMERICAL_CHARACTERS_NUMBER_OF_TYPES);
		bool decimalPlaceFound = isDecimalPlace(i, &phrase);
		if(!(numberFound || decimalPlaceFound))
		{
			stringIsNumberOrFractional = false;
		}
	}
	return stringIsNumberOrFractional;
}

//based on isIntrawordPunctuationMark{}
bool NLCpreprocessorSentenceClassClass::isDecimalPlace(int indexOfCurrentToken, const string* lineContents)
{
	bool decimalPlace = false;
	char currentToken = (*lineContents)[indexOfCurrentToken];
	if(currentToken == CHAR_FULLSTOP)
	{
		if(indexOfCurrentToken < lineContents->length()-1)	//ensure fullstop is not immediately succeded by an numeric character, which indicates a decimal place, eg "5.5"
		{
			char characterImmediatelySucceedingPunctuationMark = (*lineContents)[indexOfCurrentToken+1];
			bool isPunctuationMarkImmediatelySucceededByNumericCharacter = SHAREDvars.charInCharArray(characterImmediatelySucceedingPunctuationMark, preprocessorMathNLPparsableNumericalCharacters, NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_NUMERICAL_CHARACTERS_NUMBER_OF_TYPES);
			if(isPunctuationMarkImmediatelySucceededByNumericCharacter)
			{
				decimalPlace = true;
			}
		}
	}
	return decimalPlace;
}

//simple algorithm just detects full stops
bool NLCpreprocessorSentenceClassClass::isStringAliasFileName(const string phrase)
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
bool NLCpreprocessorSentenceClassClass::isStringIllegalTargetSourceCharacter(const string phrase)
{
	bool stringContainsIllegalTargetSourceCharacter = false;
	for(int i=0; i<phrase.length(); i++)
	{
		char c = phrase[i];
		if(!SHAREDvars.charInCharArray(c, legalTargetSourceCharacters, NLC_VERIFY_LEGAL_TARGET_SOURCE_CHARACTERS_NUMBER_OF_TYPES))
		{
			stringContainsIllegalTargetSourceCharacter = true;
		}
	}
	return stringContainsIllegalTargetSourceCharacter;
}
#endif

bool NLCpreprocessorSentenceClassClass::getSentenceInFunction(const int sentenceIndex, const NLCfunction* currentNLCfunctionInList, NLCpreprocessorSentence** sentenceFound)
{
	return getSentenceInSentenceList(sentenceIndex, currentNLCfunctionInList->firstNLCsentenceInFunction, sentenceFound);
}

bool NLCpreprocessorSentenceClassClass::getSentenceInSentenceList(const int sentenceIndex, constEffective NLCpreprocessorSentence* firstNLCsentenceInFunction, NLCpreprocessorSentence** sentenceFound)
{
	bool result = false;
	constEffective NLCpreprocessorSentence* currentNLCsentence = firstNLCsentenceInFunction;
	while(currentNLCsentence->next != NULL)
	{	
		NLCpreprocessorParsablePhrase* currentParsablePhrase = currentNLCsentence->firstNLPparsablePhraseInList;
		if(currentNLCsentence->mathTextNLPparsablePhraseTotal > 0)
		{
			while(currentParsablePhrase->next != NULL)
			{
				if(currentParsablePhrase->sentenceIndex == sentenceIndex)	//NB entity->sentenceIndexTemp can be tested here as entities within logical conditions are not advanced referenced (even if GIA advance referencing is enabled)
				{
					*sentenceFound = currentNLCsentence;
					result = true;
				}
				currentParsablePhrase = currentParsablePhrase->next;
			}
		}
		else if(currentParsablePhrase->sentenceIndex == sentenceIndex)	//NB entity->sentenceIndexTemp can be tested here as entities within logical conditions are not advanced referenced (even if GIA advance referencing is enabled)
		{
			*sentenceFound = currentNLCsentence;
			result = true;
		}
		
		currentNLCsentence = currentNLCsentence->next;
	}
	
	return result;
}

bool NLCpreprocessorSentenceClassClass::sentencePertainsToLogicalCondition(const NLCpreprocessorSentence* currentNLCsentenceInList)
{
	bool result = false;
	if(currentNLCsentenceInList->hasLogicalConditionOperator || currentNLCsentenceInList->mathTextNLPparsablePhraseTotal > 0)	//REDUNDANT: || currentNLCsentenceInList->mathTextNLPparsablePhraseTotal > 0
	{
		result = true;	//sentence pertains to a logical condition
	}
	return result;
}


