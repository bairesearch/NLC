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
 * File Name: NLCpreprocessorMath.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2015 Baxter AI (baxterai.com)
 * Project: Natural Language Programming Interface (compiler)
 * Project Version: 1o1e 07-February-2015
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/


#include "NLCpreprocessorMath.h"
#include "NLCpreprocessorMathLogicalConditions.h"
#include "NLCprintDefs.h" //required for progLangOpenParameterSpace
#include "SHAREDvars.h"	//required for convertStringToLowerCase/isWhiteSpace
#include "GIAentityNodeClass.h" //required for GIA_NLP_START_SENTENCE_INDEX and entityNodesActiveListComplete

#ifdef NLC_USE_PREPROCESSOR
#ifdef NLC_PREPROCESSOR_MATH

bool detectMathSymbolsInLine(string* lineContents)
{
	bool mathSymbolFound = false;
	for(int i=0; i<NLC_PREPROCESSOR_MATH_OPERATORS_NUMBER_OF_TYPES; i++)
	{
		int symbolFoundIndex = lineContents->find(preprocessorMathOperators[i]);
		if(symbolFoundIndex != CPP_STRING_FIND_RESULT_FAIL_VALUE)
		{
			mathSymbolFound = true;
		}
	}
	return mathSymbolFound;
}

bool detectAndReplaceIsEqualToNonLogicalConditionTextWithSymbol(string* lineContents, bool hasLogicalConditionOperator, bool isMathText)
{
	bool result = false;
	
	if(!hasLogicalConditionOperator)
	{
		//convert x is equal to/equals the number of chickens" to mathText and arsable phrase ("x = the number of chickens")
		for(int i=0; i<NLC_PREPROCESSOR_MATH_OPERATORS_NUMBER_OF_TYPES; i++)
		{	
			*lineContents = replaceAllOccurancesOfString(lineContents, preprocessorMathOperatorsEquivalentNumberOfTypes[i], preprocessorMathOperators[i]);	//NB this is type sensitive; could be changed in the future
		}			

		//"x is equal to number of chickens." is supported by mathText, with "number of chickens" parsable phrase
		//the following cannot be parsed by NLP/GIA; "x is the number of chickens" as dummy numerical variable replacement only works for previously defined variables.
		//convert "x is the number of chickens" to mathText and parsable phrase ("x = the number of chickens")
		int indexOfFirstSpace = lineContents->find(CHAR_SPACE);
		if(indexOfFirstSpace != CPP_STRING_FIND_RESULT_FAIL_VALUE)
		{
			int indexOfIs = lineContents->find(string(NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_IS_EQUAL_TO_INFORMAL), indexOfFirstSpace);
			if((indexOfIs != CPP_STRING_FIND_RESULT_FAIL_VALUE) && (indexOfIs == 0))
			{
				lineContents->replace(indexOfIs, string(NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_IS_EQUAL_TO_INFORMAL).length(), string(NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_SET));

				result = true;
				#ifdef NLC_DEBUG_PREPROCESSOR
				cout << "detectAndReplaceIsEqualToNonLogicalConditionTextWithSymbol(): found 'x is ...' at start of line; convert to mathText 'x = (nlp parsable phrase)" << endl;
				#endif
			}	
		}
		//the following is not supported by NLC at present: "if x is the number of chickens", the user must say "if the number of chickens is equal to x"
	}
	
	return result;
}
				
bool splitMathDetectedLineIntoNLPparsablePhrases(string* lineContents, NLCsentence** currentNLCsentenceInList, int* sentenceIndex, int currentIndentation, string* functionContents, NLCfunction* currentNLCfunctionInList, NLCfunction* firstNLCfunctionInList)
{
	//cout << "sentenceIndex at start of nlp parsable phrase extraction = " <<* sentenceIndex << endl;
	bool result = true;

	#ifdef NLC_PREPROCESSOR_MATH_SUPPORT_USER_VARIABLE_TYPE_DECLARATIONS
	replaceExplicitVariableTypesWithNLPparsablePhraseIllegalWords(lineContents);
	#endif
					
	int sentenceIndexOfFullSentence = *sentenceIndex;
	NLCsentence* firstNLCsentenceInFullSentence = *currentNLCsentenceInList;
	
	int startIndex = 0;
	#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
	if(firstNLCsentenceInFullSentence->hasLogicalConditionOperator)
	{
		/*not required because brackets are added to logical condition operators, and they are not accepted as legal words for nlp parsable phrase extraction;
		//prevent logical condition operatators from being considered legal words by splitMathDetectedLineIntoNLPparsablePhrases
		startIndex = logicalConditionOperationsArray[firstNLCsentenceInFullSentence->logicalConditionOperator].length();
		mathText = mathText + logicalConditionOperationsArray[firstNLCsentenceInFullSentence->logicalConditionOperator];
		#ifdef NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
		indexOfLogicalConditionCommand = indexOfLogicalConditionCommand-logicalConditionOperationsArray[firstNLCsentenceInFullSentence->logicalConditionOperator].length();
		#endif
		*/
		
		if(firstNLCsentenceInFullSentence->logicalConditionOperator == NLC_LOGICAL_CONDITION_OPERATIONS_ELSE)
		{
			//add a comma after "else", such that the logical condition command will be created (in a new sentence) instead of creating an nlp parsable phrase
			#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
			cout << "splitMathDetectedLineIntoNLPparsablePhrases() else detected" << endl;
			#endif
			if((lineContents->length() > logicalConditionOperationsArray[NLC_LOGICAL_CONDITION_OPERATIONS_ELSE].length()) && ((*lineContents)[logicalConditionOperationsArray[NLC_LOGICAL_CONDITION_OPERATIONS_ELSE].length()] != CHAR_COMMA)) 
			{
				lineContents->insert(logicalConditionOperationsArray[NLC_LOGICAL_CONDITION_OPERATIONS_ELSE].length(), STRING_COMMA);
				#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
				cout << "creating artificial comma for logical condition command to be detected" << endl;
				cout << "lineContents = " <<* lineContents << endl;
				#endif
			}
		}	
	}
	#endif

	#ifdef NLC_PREPROCESSOR_MATH_DETECT_AND_DECLARE_UNDECLARED_VARIABLES
	string newlyDeclaredVariable = "";
	#endif
	
	#ifdef NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
	bool detectedLogicalConditionCommand = false;
	bool foundImplicitConjunctions = false;	//not used
	string logicalConditionCommandSuperphraseContents = "";
	if(firstNLCsentenceInFullSentence->hasLogicalConditionOperator)
	{
		if(!generateLogicalConditionImplicitConjunctionsAndIdentifyCommand(lineContents, &detectedLogicalConditionCommand, &foundImplicitConjunctions, &logicalConditionCommandSuperphraseContents))
		{
			result = false;
		}
		#ifdef NLC_DEBUG_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
		if(detectedLogicalConditionCommand)
		{
			cout << "\n logicalConditionCommandSuperphraseContents = " << logicalConditionCommandSuperphraseContents << endl;
		}
		#endif
	}
	int phraseIndexOfFirstLogicalCommand = INT_DEFAULT_VALUE;
	#endif
	
	#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
	bool additionalClosingBracketRequired = false;
	if(firstNLCsentenceInFullSentence->hasLogicalConditionOperator)
	{
		if(!replaceLogicalConditionNaturalLanguageMathWithSymbols(lineContents, firstNLCsentenceInFullSentence->logicalConditionOperator, &additionalClosingBracketRequired, false))
		{
			result = false;
		}
		#ifdef NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
		if(detectedLogicalConditionCommand)
		{
			bool tempNotUsed = false;
			if(!replaceLogicalConditionNaturalLanguageMathWithSymbols(&logicalConditionCommandSuperphraseContents, firstNLCsentenceInFullSentence->logicalConditionOperator, &tempNotUsed, true))
			{
				result = false;
			}
			#ifdef NLC_DEBUG_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
			cout << "\n lineContents = " <<* lineContents << endl;
			cout << "logicalConditionCommandSuperphraseContents = " << logicalConditionCommandSuperphraseContents << endl;
			#endif
		}
		#endif
	}		
	#endif

	int mathTextNLPparsablePhraseIndex = 0;
	//NLP parsable phrase is taken to be at least 2 consecutive words delimited by a space ie, [a-zA-Z0-9_] [a-zA-Z0-9_]
	int wordIndex = 0;
	int phraseIndex = 0;
	string currentWord = "";
	string currentPhrase = "";
	string mathText = "";
	bool NLPparsableMandatoryCharacterFoundInCurrentWord = false;	//NB NLPparsableMandatoryCharacterFoundInCurrentWord is not currently used with NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_SUPPORT_ALPHANUMERIC_VARIABLE_NAMES
	bool parsingWhiteSpace = false;	//added 1h5b 30-July-2014
	
	//cout << "lineContents = " <<* lineContents << endl;
	//cout << "lineContents->length() = " << lineContents->length() << endl;
	//cout << "lineContents[lineContents->length()-1] = " << (*lineContents)[lineContents->length()-1] << endl;
	//exit(0);
	
	bool finalWordInSentenceFoundAndIsLegal = false;
	for(int i=startIndex; i<lineContents->length(); i++)
	{
		//eg y = x+the number of house in the park
		//eg y = x+(the number of house in the park)
		char c = (*lineContents)[i];
		
		#ifdef NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
		int indexOfLogicalConditionCommand = lineContents->find(logicalConditionCommandSuperphraseContents, i);
		if((indexOfLogicalConditionCommand != CPP_STRING_FIND_RESULT_FAIL_VALUE) && (indexOfLogicalConditionCommand == i))
		{
			if(phraseIndexOfFirstLogicalCommand == INT_DEFAULT_VALUE)
			{//do not overwrite phraseIndexOfFirstLogicalCommand
				phraseIndexOfFirstLogicalCommand = phraseIndex;
				#ifdef NLC_DEBUG_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
				cout << "\n phraseIndexOfFirstLogicalCommand = " << phraseIndexOfFirstLogicalCommand << endl;
				#endif
			}
		}
		#endif
		
		bool legalWordCharacterFound = charInCharArray(c, preprocessorMathNLPparsableCharacters, NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_CHARACTERS_NUMBER_OF_TYPES);
		#ifdef NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_SUPPORT_ALPHANUMERIC_VARIABLE_NAMES_REMOVE_REDUNDANT_CODE
		if(legalWordCharacterFound)
		{
			NLPparsableMandatoryCharacterFoundInCurrentWord = true;
		}
		#else
		if(charInCharArray(c, preprocessorMathNLPparsableCharactersMandatory, NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_CHARACTERS_MANDATORY_NUMBER_OF_TYPES))
		{
			NLPparsableMandatoryCharacterFoundInCurrentWord = true;
		}
		#endif
		finalWordInSentenceFoundAndIsLegal = false;
		if(legalWordCharacterFound && (i == lineContents->length()-1) && NLPparsableMandatoryCharacterFoundInCurrentWord)
		{
			if(wordIndex >= (NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_MIN_NUMBER_WORDS-1))
			{
				#ifdef NLC_DEBUG_PREPROCESSOR_MATH
				cout << "finalWordInSentenceFoundAndIsLegal" << endl;
				#endif
				//add final word in sentence to phrase if it is legal
				currentWord = currentWord + c;
				#ifdef NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_SUPPORT_ALPHANUMERIC_VARIABLE_NAMES_ONLY
				if(isStringNLPparsableWord(currentWord, true))
				{
				#endif
					finalWordInSentenceFoundAndIsLegal = true;
				#ifdef NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_SUPPORT_ALPHANUMERIC_VARIABLE_NAMES_ONLY
				}
				#endif
			}

		}
		bool wordDelimiterCharacterFound = charInCharArray(c, preprocessorMathNLPparsableCharactersDelimiter, NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_CHARACTERS_DELIMITER_NUMBER_OF_TYPES);

		if(!legalWordCharacterFound || finalWordInSentenceFoundAndIsLegal)
		{//!legalWordCharacterFound or (legalWordCharacterFound && last character in sentence)

			//cout << "!legalWordCharacterFound || finalWordInSentenceFoundAndIsLegal): " << c << endl;
			
			//current word checks:
			#ifndef NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_SUPPORT_ALPHANUMERIC_VARIABLE_NAMES_REMOVE_REDUNDANT_CODE
			//NB NLPparsableMandatoryCharacterFoundInCurrentWord is not currently used with NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_SUPPORT_ALPHANUMERIC_VARIABLE_NAMES
			if(NLPparsableMandatoryCharacterFoundInCurrentWord)
			{
			#endif
				#ifdef NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_SUPPORT_ALPHANUMERIC_VARIABLE_NAMES_ONLY
				if(!isStringNLPparsableWord(currentWord, true))
				{
					cout << "splitMathDetectedLineIntoNLPparsablePhrases(): user input error - variables names cannot start with numbers: " << currentWord << endl;
					exit(0);
				}
				#endif
			
				if((firstNLCsentenceInFullSentence->hasLogicalConditionOperator))
				{
					if(i == currentWord.length())
					{
						if(textInTextArray(currentWord, logicalConditionOperationsArray, NLC_LOGICAL_CONDITION_OPERATIONS_NUMBER_OF_TYPES))
						{
							#ifdef NLC_DEBUG_PREPROCESSOR_MATH
							cout << "logical condition operator detected: NLPparsableMandatoryCharacterFoundInCurrentWord = false" << endl;
							#endif
							NLPparsableMandatoryCharacterFoundInCurrentWord = false;
						}
					}

				}
				
				#ifdef NLC_PREPROCESSOR_MATH_DETECT_AND_DECLARE_UNDECLARED_VARIABLES
				if(!(firstNLCsentenceInFullSentence->hasLogicalConditionOperator))
				{
					if((c == NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_SET_CHAR) || (wordDelimiterCharacterFound && (i<lineContents->length()+1) && ((*lineContents)[i+1] == NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_SET_CHAR)))	//mathText: "X=.." or "X =..."
					{
						if(!findPredefinedNumericalVariable(&currentWord, currentNLCfunctionInList, firstNLCfunctionInList, (*currentNLCsentenceInList)))
						{								
							if(i == currentWord.length())	//word comprises first mathText contents
							{//first word in mathText (type will automatically be assigned)
								
								//NB considering the current phrase contains an equal sign it will be classified as mathText, not an nlp parsable phrase
								//#ifdef NLC_DEBUG_PREPROCESSOR_MATH_DETECT_AND_DECLARE_UNDECLARED_VARIABLES
								cout << "undeclared mathText variable detected: declaring " << NLC_PREPROCESSOR_MATH_MATHTEXT_VARIABLE_TYPE_DEFAULT << currentWord << endl;	//inserting mathText variable declaration type (eg double)
								//#endif
								currentPhrase.insert(0, NLC_PREPROCESSOR_MATH_MATHTEXT_VARIABLE_TYPE_DEFAULT);

								newlyDeclaredVariable = currentWord;
								NLPparsableMandatoryCharacterFoundInCurrentWord = false;
								(*currentNLCsentenceInList)->mathTextVariableNames.push_back(currentWord);
							}
							else
							{//explicit type provided
								
								for(int i2=0; i2<NLC_PREPROCESSOR_MATH_MATHTEXT_VARIABLES_NUMBER_OF_TYPES; i2++)
								{
									#ifdef NLC_PREPROCESSOR_MATH_SUPPORT_USER_VARIABLE_TYPE_DECLARATIONS
									int indexOfType = lineContents->find(preprocessorMathMathTextVariables[i2]);
									#else
									int indexOfType = lineContents->find(preprocessorMathNaturalLanguageVariables[i2]);
									#endif
									if((indexOfType != CPP_STRING_FIND_RESULT_FAIL_VALUE) && (indexOfType < i))
									{
										//#ifdef NLC_DEBUG_PREPROCESSOR_MATH_DETECT_AND_DECLARE_UNDECLARED_VARIABLES
										cout << "explicit mathText variable type detected for currentWord: " << preprocessorMathNaturalLanguageVariables[i2] << " " << currentWord << endl;
										//#endif									
										newlyDeclaredVariable = currentWord;
										NLPparsableMandatoryCharacterFoundInCurrentWord = false;
										(*currentNLCsentenceInList)->mathTextVariableNames.push_back(currentWord);
									}
								}
							}
						}
					}
				}
				#endif
			#ifndef NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_SUPPORT_ALPHANUMERIC_VARIABLE_NAMES_REMOVE_REDUNDANT_CODE
			}	
			#endif		
						
			if(NLPparsableMandatoryCharacterFoundInCurrentWord)
			{
				if(!parsingWhiteSpace)
				{	
					(*currentNLCsentenceInList)->mathTextVariableNames.push_back(currentWord);	//note if the currentWord turns out not to belong to an NLP parsable phrase instead of mathtext it will be removed from mathTextVariableNames
				}
				else
				{
					if(currentWord != "")
					{
						cout << "splitMathDetectedLineIntoNLPparsablePhrases() error: currentWord != "" && parsingWhiteSpace" << endl;
					}				
				}
				#ifdef NLC_DEBUG_PREPROCESSOR_MATH
				cout << "NLPparsableMandatoryCharacterFoundInCurrentWord: " << currentWord << endl;
				cout << "wordDelimiterCharacterFound = " << wordDelimiterCharacterFound << endl;
				cout << "wordIndex = " << wordIndex << endl;
				#endif
				if(!parsingWhiteSpace)
				{
					wordIndex++;
				}
				
				if(!wordDelimiterCharacterFound || finalWordInSentenceFoundAndIsLegal)
				{
					NLPparsableMandatoryCharacterFoundInCurrentWord = false;

					//currentWord is either a mathText variable name or part of an NLP parsable phrase (c is a space or comma)
					if(wordIndex >= NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_MIN_NUMBER_WORDS)
					{
						currentPhrase = currentPhrase + currentWord;
						
						#ifdef NLC_DEBUG_PREPROCESSOR_MATH
						cout << "splitMathDetectedLineIntoNLPparsablePhrases(): create new NLP parsable phrase: currentPhrase = " << currentPhrase << endl;
						#endif
						
						//remove all mathTextVariableNames nlp parsable phrase (as an NLP parsable phrase does not contain mathText variable names, or if it does the mathText variable are references to predefined mathText variables and will be detected later)
						//cout << "wordIndex = " << wordIndex << endl;
						for(int i=0; i<wordIndex; i++)
						{
							//cout << "(*currentNLCsentenceInList)->mathTextVariableNames.back() = " << (*currentNLCsentenceInList)->mathTextVariableNames.back() << endl;
							(*currentNLCsentenceInList)->mathTextVariableNames.pop_back();
						}

						//split sentence and add phrase
						(*currentNLCsentenceInList)->mathTextNLPparsablePhraseIndex = phraseIndex;
						#ifdef NLC_PREPROCESSOR_MATH_USE_HUMAN_READABLE_VARIABLE_NAMES
						bool spaceAtEndOfPhrase = false;
						if(currentPhrase[currentPhrase.length()-1] == CHAR_SPACE)
						{
							spaceAtEndOfPhrase = true;
							currentPhrase = currentPhrase.substr(0, currentPhrase.length()-1);
						}
						#endif
						//cout << "currentPhrase = " << currentPhrase << endl;
						bool lastCharacterOfPhraseIsFullStop = false;
						if(currentPhrase[currentPhrase.length()-1] == NLC_PREPROCESSOR_END_OF_SENTENCE_CHAR)
						{
							lastCharacterOfPhraseIsFullStop = true;
						}
						#ifdef NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_SUPPORT_FILENAMES_WITH_FULLSTOPS
						if(!lastCharacterOfPhraseIsFullStop)
						{
						#endif
							(*currentNLCsentenceInList)->sentenceContents = currentPhrase + NLC_PREPROCESSOR_END_OF_SENTENCE_CHAR;	//append a fullstop to the NLP parsable phrase to make it readable by NLP
						#ifdef NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_SUPPORT_FILENAMES_WITH_FULLSTOPS
						}
						else
						{
							(*currentNLCsentenceInList)->sentenceContents = currentPhrase;
						}
						#endif
						(*currentNLCsentenceInList)->sentenceIndex = *sentenceIndex;
						//(*currentNLCsentenceInList)->indentation = currentIndentation;	//indentation not recorded for NLC parsable phrases
						//cout << "generateMathTextNLPparsablePhraseReference = " << endl;
						//cout << "(*currentNLCsentenceInList)->sentenceContents = " << (*currentNLCsentenceInList)->sentenceContents << endl;
						mathText = mathText + generateMathTextNLPparsablePhraseReference(sentenceIndexOfFullSentence, (*currentNLCsentenceInList));
						//cout << "mathText = " << mathText << endl;
						#ifdef NLC_PREPROCESSOR_MATH_USE_HUMAN_READABLE_VARIABLE_NAMES
						if(spaceAtEndOfPhrase)
						{
							//readd the final space to the mathText since it has been removed from the nlp parsable phrase
							mathText = mathText + CHAR_SPACE;
						}
						#endif
						(*currentNLCsentenceInList)->next = new NLCsentence();
						(*currentNLCsentenceInList) = (*currentNLCsentenceInList)->next;
						(*sentenceIndex) = (*sentenceIndex) + 1;
						phraseIndex++;

						//restart phrase
						currentPhrase = "";
						#ifdef NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_SUPPORT_FILENAMES_WITH_FULLSTOPS
						if(!finalWordInSentenceFoundAndIsLegal || lastCharacterOfPhraseIsFullStop)	//ie !finalWordInSentenceFoundAndIsLegal || (finalWordInSentenceFoundAndIsLegal && lastCharacterOfPhraseIsFullStop)
						{
						#else
						if(!finalWordInSentenceFoundAndIsLegal)			//!finalWordInSentenceFoundAndIsLegal (because fullstop will already have been added to sentenceContents and therefore mathText)
						{
						#endif
							mathText = mathText + c;
						}
						
						#ifdef NLC_DEBUG_PREPROCESSOR_MATH	
						cout << "mathText = " << mathText << endl;
						#endif			
					}
					else
					{
						//currentWord is a mathText variable name (c is likely a mathematical operator)
						#ifdef NLC_DEBUG_PREPROCESSOR_MATH	
						//cout << "currentWord is a mathText variable name (c is likely a mathematical operator)" << endl;
						#endif
						currentPhrase = currentPhrase + currentWord + c;	//add previous words in the failed NLP parsable phrase (if existent) and the currentWord to the mathText   
						mathText = mathText + currentPhrase;
						currentPhrase = "";	//restart phrase (assuming it contains text)
					}
					wordIndex = 0;
					parsingWhiteSpace = false;
				}
				else
				{//wordDelimiterCharacterFound
					#ifdef NLC_DEBUG_PREPROCESSOR_MATH	
					//cout << "wordDelimiterCharacterFound" << endl;
					#endif
					currentPhrase = currentPhrase + currentWord + c;
					parsingWhiteSpace = true;
				}
			}
			else
			{
				//currentWord is disgarded as math (OLD: eg numbers) in mathText as it does not contain a mandatory character
				#ifdef NLC_DEBUG_PREPROCESSOR_MATH	
				//cout << "currentWord is disgarded as math (eg numbers) in mathText as it does not contain a mandatory character" << endl;
				#endif
				currentPhrase = currentPhrase + currentWord + c;	//add previous words in the failed NLP parsable phrase (if existent) and the currentWord to the mathText   
				mathText = mathText + currentPhrase;
				currentPhrase = "";	//restart phrase (assuming it contains text)
				wordIndex = 0;
				parsingWhiteSpace = false;
			}
			//restart word
			currentWord = "";
		}
		else
		{//legalWordCharacterFound
			currentWord = currentWord + c;
			parsingWhiteSpace = false;
		}
	}
	if(!finalWordInSentenceFoundAndIsLegal)
	{
		//cout << "!finalWordInSentenceFoundAndIsLegal" << endl;
		//insufficient number of words in final phrase detected to create an NLP parsable phrase; add words to mathText instead
		//currentWord is [assumed to be] a mathText variable name
		currentPhrase = currentPhrase + currentWord;	//add previous words in the failed NLP parsable phrase (if existent) and the currentWord to the mathText   
		mathText = mathText + currentPhrase;
		currentPhrase = "";	//restart phrase (assuming it contains text)	//redundant (as it is the final word in the sentence)
	}
	#ifdef NLC_DEBUG_PREPROCESSOR_MATH	
	cout << "mathText = " << mathText << endl;
	#endif	
	
	//now write the full mathText to each sub sentence (NLP parsable phrase) - required for NLC to regenerate the correct math and variable definitions (based on NLP parsable phrases) 
	firstNLCsentenceInFullSentence->isMath = true;
	firstNLCsentenceInFullSentence->mathTextNLPparsablePhraseTotal = phraseIndex;
	firstNLCsentenceInFullSentence->mathText = mathText;
	//cout << "mathText = " << mathText << endl;
	firstNLCsentenceInFullSentence->indentation = currentIndentation;
	if(firstNLCsentenceInFullSentence->mathTextNLPparsablePhraseTotal == 0)
	{
		//add dummy phrase for NLP to parse (will not be used by NLC; create NLP/GIA sentence as a filler for math text replacement only)
		#ifdef NLC_DEBUG_PREPROCESSOR_MATH
		cout << "add dummy phrase for NLP to parse: " << string(NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_DUMMY) << endl;
		#endif
		(*currentNLCsentenceInList)->sentenceContents = string(NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_DUMMY);
		(*currentNLCsentenceInList)->next = new NLCsentence();
		(*currentNLCsentenceInList) = (*currentNLCsentenceInList)->next;
		(*sentenceIndex) = (*sentenceIndex) + 1;
	}

	#ifdef NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_SUPPORT_ALPHANUMERIC_VARIABLE_NAMES_REMOVE_REDUNDANT_CODE
	//remove all numbers from mathTextVariableNames - added 1l7a
	for(vector<string>::iterator iter = firstNLCsentenceInFullSentence->mathTextVariableNames.begin(); iter != firstNLCsentenceInFullSentence->mathTextVariableNames.end();)
	{
		string mathTextVariableName = *iter;
		bool variableNameIsNumber = isStringNumber(mathTextVariableName);
		if(variableNameIsNumber)
		{
			iter = firstNLCsentenceInFullSentence->mathTextVariableNames.erase(iter);
		}
		else
		{
			iter++;
		}
	}
	#endif
	
	#ifdef NLC_PREPROCESSOR_MATH_DETECT_AND_DECLARE_UNDECLARED_VARIABLES
	//if(!(firstNLCsentenceInFullSentence->hasLogicalConditionOperator))
	//{
	for(vector<string>::iterator iter = firstNLCsentenceInFullSentence->mathTextVariableNames.begin(); iter != firstNLCsentenceInFullSentence->mathTextVariableNames.end(); iter++)
	{
		string mathTextVariableName = *iter;
		
		bool ignoreVariable = false;
		if((firstNLCsentenceInFullSentence->hasLogicalConditionOperator))
		{
			if(textInTextArray(mathTextVariableName, logicalConditionOperationsArray, NLC_LOGICAL_CONDITION_OPERATIONS_NUMBER_OF_TYPES))
			{
				#ifdef NLC_DEBUG_PREPROCESSOR_MATH
				cout << "logical condition operator detected: ignoreVariable = true" << endl;
				#endif
				ignoreVariable = true;
			}
		}
		if(textInTextArray(mathTextVariableName, preprocessorMathNaturalLanguageVariables, NLC_PREPROCESSOR_MATH_MATHTEXT_VARIABLES_NUMBER_OF_TYPES))
		{
			#ifdef NLC_DEBUG_PREPROCESSOR_MATH
			cout << "mathText variable type detected: ignoreVariable = true" << endl;
			#endif
			ignoreVariable = true;
		}
		if(currentWord == "")
		{
			ignoreVariable = true;
		}
		
		if(!ignoreVariable)
		{			
			if(mathTextVariableName != newlyDeclaredVariable)
			{
				//cout << "mathTextVariableName = " << mathTextVariableName << endl;
				if(!findPredefinedNumericalVariable(&mathTextVariableName, currentNLCfunctionInList, firstNLCfunctionInList, firstNLCsentenceInFullSentence))
				{
					cout << "splitMathDetectedLineIntoNLPparsablePhrases() error: mathText variable " << mathTextVariableName << " is undeclared" << endl;
					//cout << "lineContents = " <<* lineContents << endl;
					#ifndef NLC_PREPROCESSOR_MATH_ALLOW_UNDECLARED_MATHTEXT_VARIABLES_TO_BE_REFERENCED_BY_MATH
					exit(0);
					#endif
					result = true;
				} 
			}
		}
	}	
	//}	
	#endif

	//cout << "sentenceIndex at end of nlp parsable phrase extraction = " <<* sentenceIndex << endl;
	


	#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
	if(firstNLCsentenceInFullSentence->hasLogicalConditionOperator)
	{	
		//cout << "hasLogicalConditionOperator" << endl; 
		if(!splitMathDetectedLineIntoNLPparsablePhrasesLogicalConditionCommands(firstNLCsentenceInFullSentence, currentNLCsentenceInList, sentenceIndex, additionalClosingBracketRequired, detectedLogicalConditionCommand, phraseIndexOfFirstLogicalCommand, logicalConditionCommandSuperphraseContents))
		{
			result = false;
		}
	}

	//#ifndef NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
	if(firstNLCsentenceInFullSentence->hasLogicalConditionOperator)
	{
	//#endif
		if(!splitMathDetectedLineIntoNLPparsablePhrasesLogicalConditionAddExplicitSubjectTextForConjunctions(firstNLCsentenceInFullSentence, currentNLCsentenceInList, sentenceIndex, additionalClosingBracketRequired))
		{
			result = false;
		}
	//#ifndef NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
	}
	//#endif		

	//currently disabled (untested): theoretically allows multiple commands to be defined on a single line separated by conjunctions, eg "X = 3+5 and eat the blue apple" 
	#ifdef NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
	#ifdef NLC_PREPROCESSOR_MATH_SUPPORT_MULTIPLE_LOGICAL_CONDITION_COMMANDS_ON_ONE_LINE
	if(!(firstNLCsentenceInFullSentence->hasLogicalConditionOperator))
	{
		#ifdef NLC_DEBUG_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
		cout << "generateSeparateSentencesFromMathTextAndParsablePhrasesInCommand(): " << endl;
		#endif
		if(!generateSeparateSentencesFromMathTextAndParsablePhrasesInCommand(currentNLCsentenceInList, firstNLCsentenceInFullSentence, firstNLCsentenceInFullSentence->mathText, sentenceIndex, firstNLCsentenceInFullSentence->sentenceIndex, currentIndentation))
		{
			result = false;
		}
	}
	#endif	
	#endif
	
	if(firstNLCsentenceInFullSentence->hasLogicalConditionOperator)
	{	
		if(!replaceLogicalConditionNaturalLanguageMathWithSymbolsEnd(firstNLCsentenceInFullSentence, additionalClosingBracketRequired))
		{
			result = false;
		}

	}

	#endif
	
	#ifdef NLC_PREPROCESSOR_MATH_SUPPORT_USER_VARIABLE_TYPE_DECLARATIONS
	restoreExplicitVariableTypes(&(firstNLCsentenceInFullSentence->mathText));
	#endif
	
	NLCsentence* currentSentence = firstNLCsentenceInFullSentence;
	while(currentSentence->next != NULL)
	{
		/*
		cout << "\ncurrentSentence->sentenceContents = " << currentSentence->sentenceContents << endl;
		cout << "currentSentence->sentenceIndex = " << currentSentence->sentenceIndex << endl;
		cout << "currentSentence->indentation = " << currentSentence->indentation << endl;
		cout << "currentSentence->hasLogicalConditionOperator = " << currentSentence->hasLogicalConditionOperator << endl;
		cout << "currentSentence->logicalConditionOperator = " << currentSentence->logicalConditionOperator << endl;
		cout << "currentSentence->mathText = " << currentSentence->mathText << endl;
		cout << "currentSentence->isMath = " << currentSentence->isMath << endl;
		cout << "currentSentence->mathTextNLPparsablePhraseIndex = " << currentSentence->mathTextNLPparsablePhraseIndex << endl;
		cout << "currentSentence->mathTextNLPparsablePhraseTotal = " << currentSentence->mathTextNLPparsablePhraseTotal << endl;
		cout << "currentSentence->sentenceOriginal = " << currentSentence->sentenceOriginal << endl;
		cout << "currentSentence->sentenceContentsOriginal = " << currentSentence->sentenceContentsOriginal << endl;
		*/
		*functionContents = *functionContents + currentSentence->sentenceContents + CHAR_NEWLINE;
		currentSentence = currentSentence->next;
	}
	
	return result;
}

#ifdef NLC_PREPROCESSOR_MATH_SUPPORT_USER_VARIABLE_TYPE_DECLARATIONS
bool replaceExplicitVariableTypesWithNLPparsablePhraseIllegalWords(string* lineContents)
{	
	bool result = false;
	//replaceExplicitVariableTypesWithNLPparsablePhraseIllegalWords() is required to prevent creation of nlp parsable phrase from 2 word variable declarations
	for(int i=0; i<NLC_PREPROCESSOR_MATH_MATHTEXT_VARIABLES_NUMBER_OF_TYPES; i++)
	{
		*lineContents = replaceAllOccurancesOfString(lineContents, preprocessorMathNaturalLanguageVariables[i], preprocessorMathMathTextVariables[i]);	//NB this is type sensitive; could be changed in the future
		result = true;
	}

	return result;
}

bool restoreExplicitVariableTypes(string* mathText)
{	
	bool result = false;
	for(int i=0; i<NLC_PREPROCESSOR_MATH_MATHTEXT_VARIABLES_NUMBER_OF_TYPES; i++)
	{
		*mathText = replaceAllOccurancesOfString(mathText, preprocessorMathMathTextVariables[i] , preprocessorMathNaturalLanguageVariables[i]);
		result = true;
	}

	return result;
}
#endif


#ifdef NLC_PREPROCESSOR_MATH_REPLACE_NUMERICAL_VARIABLES_NAMES_FOR_NLP

bool replaceNumericalVariablesWithDummyNameIfNecessary(string* lineContents, NLCsentence* currentNLCsentenceInList, NLCfunction* currentNLCfunctionInList, NLCfunction* firstNLCfunctionInList)
{
	bool result = true;
	#ifdef NLC_DEBUG_PREPROCESSOR_MATH_REPLACE_NUMERICAL_VARIABLES
	cout << "replaceNumericalVariablesWithDummyNameIfNecessary: lineContents = " <<* lineContents << endl;
	#endif
	
	string currentWord = "";
	bool parsingWhiteSpace = true;
	int i = 0;
	while(i < lineContents->length())
	{
		char c = (*lineContents)[i];
		if(isWhiteSpaceOrInvalidWordCharacter(c))
		{//new word detected
			if(!parsingWhiteSpace)
			{
				if(findPredefinedNumericalVariable(&currentWord, currentNLCfunctionInList, firstNLCfunctionInList, NULL))	//pass firstNLCfunctionInList and update findPredefinedNumericalVariable() accordingly to allow global numerical variable definitions; not just local numerical variable definitions
				{
					//replace the variable name with a dummy number
					currentNLCsentenceInList->variableNamesDetected.push_back(currentWord);
					int dummyNumericalValue = generateDummyNumericalValue(currentNLCsentenceInList->variableNamesDetected.size());
					string dummyNumericalValueString = convertIntToString(dummyNumericalValue);
					#ifdef NLC_DEBUG_PREPROCESSOR_MATH_REPLACE_NUMERICAL_VARIABLES
					cout << "replaceNumericalVariablesWithDummyNameIfNecessary(): currentWord = " << currentWord << endl;
					cout << "replaceNumericalVariablesWithDummyNameIfNecessary(): dummyNumericalValueString = " << dummyNumericalValueString << endl;
					#endif
					lineContents->replace(i-currentWord.length(), currentWord.length(), dummyNumericalValueString);
					i = i-currentWord.length()+dummyNumericalValueString.length();
				}
				parsingWhiteSpace = true;
				currentWord = "";
			}	
		}
		else
		{	
			currentWord = currentWord + c;
			parsingWhiteSpace = false;
		}
		i++;
	}
	if(!parsingWhiteSpace)
	{//perform any necessary variable name replacements for last word in sentence
		if(findPredefinedNumericalVariable(&currentWord, currentNLCfunctionInList, firstNLCfunctionInList, NULL))	//pass firstNLCfunctionInList and update findPredefinedNumericalVariable() accordingly to allow global numerical variable definitions; not just local numerical variable definitions
		{
			//replace the variable name with a dummy number
			currentNLCsentenceInList->variableNamesDetected.push_back(currentWord);
			int dummyNumericalValue = generateDummyNumericalValue(currentNLCsentenceInList->variableNamesDetected.size());
			string dummyNumericalValueString = convertIntToString(dummyNumericalValue);
			#ifdef NLC_DEBUG_PREPROCESSOR_MATH_REPLACE_NUMERICAL_VARIABLES
			cout << "replaceNumericalVariablesWithDummyNameIfNecessary(): currentWord = " << currentWord << endl;
			cout << "replaceNumericalVariablesWithDummyNameIfNecessary(): dummyNumericalValueString = " << dummyNumericalValueString << endl;
			#endif
			lineContents->replace(lineContents->length()-currentWord.length(), currentWord.length(), dummyNumericalValueString);	
		}	
	}
	return result;
}

bool isWhiteSpaceOrInvalidWordCharacter(char c)
{
	/*
	bool whiteSpaceOrInvalidWordCharacter = false;
	if(isWhiteSpace(c) || (c == CHAR_COMMA))
	{
		whiteSpaceOrInvalidWordCharacter = true;
	}
	*/
	bool legalWordCharacterFound = charInCharArray(c, preprocessorMathNLPparsableCharacters, NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_CHARACTERS_NUMBER_OF_TYPES);
	bool whiteSpaceOrInvalidWordCharacter = true;
	if(legalWordCharacterFound)
	{
		whiteSpaceOrInvalidWordCharacter = false;
	}

	return whiteSpaceOrInvalidWordCharacter;
}

bool findPredefinedNumericalVariable(string* currentWord, NLCfunction* currentNLCfunctionInList, NLCfunction* firstNLCfunctionInList, NLCsentence* sentenceToIgnoreWhileSearching)
{
	#ifdef NLC_PREPROCESSOR_REPLACE_NUMERICAL_VARIABLES_DETECT_GLOBAL_NUMERICAL_VARIABLES
	return findPredefinedNumericalVariableInAnyFunctions(currentWord, firstNLCfunctionInList, sentenceToIgnoreWhileSearching);
	#else
	return findPredefinedNumericalVariableInFunction(currentWord, currentNLCfunctionInList, sentenceToIgnoreWhileSearching);	
	#endif
}

#ifdef NLC_PREPROCESSOR_REPLACE_NUMERICAL_VARIABLES_DETECT_GLOBAL_NUMERICAL_VARIABLES
bool findPredefinedNumericalVariableInAnyFunctions(string* currentWord, NLCfunction* firstNLCfunctionInList, NLCsentence* sentenceToIgnoreWhileSearching)
{
	bool result = false;
	currentNLCfunctionInList = firstNLCfunctionInList;
	while(currentNLCfunctionInList->next != NULL)
	{
		NLCsentence* currentNLCsentenceInList = currentNLCfunctionInList->firstNLCsentenceInFunction;
		if(findPredefinedNumericalVariableInFunction(currentWord, currentNLCfunctionInList, sentenceToIgnoreWhileSearching)
		{
			result = true;
		}
	
		currentNLCfunctionInList = currentNLCfunctionInList->next;
	}
	return result;
}
#endif

bool findPredefinedNumericalVariableInFunction(string* currentWord, NLCfunction* currentNLCfunctionInList, NLCsentence* sentenceToIgnoreWhileSearching)	//pass firstNLCfunctionInList and update findPredefinedNumericalVariable() accordingly to allow global numerical variable definitions; not just local numerical variable definitions
{
	bool result = false;

	NLCsentence* currentNLCsentenceInList = currentNLCfunctionInList->firstNLCsentenceInFunction;
	while(currentNLCsentenceInList->next != NULL)
	{
		if(currentNLCsentenceInList != sentenceToIgnoreWhileSearching)
		{
			for(vector<string>::iterator iter = currentNLCsentenceInList->mathTextVariableNames.begin(); iter != currentNLCsentenceInList->mathTextVariableNames.end(); iter++)
			{
				string mathTextVariableName = *iter;
				if(*currentWord == mathTextVariableName)
				{
					result = true;
				} 
			}
		}			
		currentNLCsentenceInList = currentNLCsentenceInList->next;
	}	

	return result;
}
				
#endif


#endif
#endif




