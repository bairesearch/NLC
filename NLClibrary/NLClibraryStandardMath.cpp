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
 * File Name: NLClibraryStandardMath.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2018 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 2f7c 17-April-2018
 * Requirements: requires C++ code to be generated by NLC
 *
 *******************************************************************************/
 
#include "NLClibraryStandardMath.hpp"
#include "NLClibraryStandardOperations.hpp"
#include "SHAREDvars.hpp"	//required for charInCharArray

#ifdef NLC_MATH_OBJECTS

bool isStringNumberOrFractional(string phrase)
{
	bool stringIsNumberOrFractional = true;
	if(phrase.length() == 0)
	{
		//cout << "isStringNumberOrFractional() error: phrase.length() == 0" << endl;
	}
	for(int i=0; i<phrase.length(); i++)
	{
		char c = phrase[i];	
		bool numberFound = SHAREDvarsClass().charInCharArray(c, preprocessorMathNLPparsableNumericalCharacters, NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_NUMERICAL_CHARACTERS_NUMBER_OF_TYPES);
		bool decimalPlaceFound = isDecimalPlace(i, &phrase);
		if(!(numberFound || decimalPlaceFound))
		{
			stringIsNumberOrFractional = false;
		}
	}
	//cout << "isStringNumberOrFractional: " << phrase << " = " << stringIsNumberOrFractional << endl;
	return stringIsNumberOrFractional;
}

bool isDecimalPlace(int indexOfCurrentToken, string* lineContents)
{
	bool decimalPlace = false;
	char currentToken = (*lineContents)[indexOfCurrentToken];
	if(currentToken == CHAR_FULLSTOP) 
	{
		if(indexOfCurrentToken < lineContents->length()-1)	//ensure fullstop is not immediately succeded by an numeric character, which indicates a decimal place, eg "5.5"
		{	
			char characterImmediatelySucceedingPunctuationMark = (*lineContents)[indexOfCurrentToken+1];
			bool isPunctuationMarkImmediatelySucceededByNumericCharacter = SHAREDvarsClass().charInCharArray(characterImmediatelySucceedingPunctuationMark, preprocessorMathNLPparsableNumericalCharacters, NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_NUMERICAL_CHARACTERS_NUMBER_OF_TYPES);
			if(isPunctuationMarkImmediatelySucceededByNumericCharacter)
			{
				decimalPlace = true;
			}		
		}
	}
	return decimalPlace;
}

#endif

