/*******************************************************************************
 *
 * This file is part of BAIPROJECT.
 *
 * BAIPROJECT is licensed under the GNU Affero General Public License
 * version 3, as published by the Free Software Foundation. The use of
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
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2017 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 2b1a 19-May-2017
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/


#include "NLCpreprocessorMath.hpp"

#ifdef NLC_PREPROCESSOR
#ifdef NLC_PREPROCESSOR_MATH

bool NLCpreprocessorMathClass::detectMathSymbolsInLine(const string* lineContents)
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

bool NLCpreprocessorMathClass::detectAndReplaceIsEqualToNonLogicalConditionTextWithSymbol(string* lineContents, const bool hasLogicalConditionOperator, const bool isMathText)
{
	bool result = false;
	//cout << "lineContents = " << *lineContents << endl;
	
	if(!hasLogicalConditionOperator)
	{
		#ifdef NLC_MATH_OBJECTS_ADVANCED
		//ignore string quotations during replacement
		bool stillFindingLineContentsSub = true;
		int lineContentsSubIndex = 0;
		int lineContentsSubIndexEnd = 0;
		string lineContentsNew = "";
		while(stillFindingLineContentsSub) 
		{
			int indexOfStringDelimiter = lineContents->find(NLC_MATH_OBJECTS_STRING_DELIMITER_CHAR, lineContentsSubIndex);
			if(indexOfStringDelimiter != CPP_STRING_FIND_RESULT_FAIL_VALUE)
			{	
				lineContentsSubIndexEnd = indexOfStringDelimiter+1;
			}
			else
			{
				lineContentsSubIndexEnd = lineContents->length();
				stillFindingLineContentsSub = false;
			}
			string lineContentsSub = lineContents->substr(lineContentsSubIndex, lineContentsSubIndexEnd-lineContentsSubIndex);
			//cout << "lineContentsSub = " << lineContentsSub << endl;
		#else
		string lineContentsSub = *lineContents;
		#endif
		
			//convert x is equal to/equals the number of chickens" to mathText and parsable phrase ("x = the number of chickens")
			for(int i=0; i<NLC_PREPROCESSOR_MATH_OPERATORS_NUMBER_OF_TYPES; i++)
			{
				bool foundAtLeastOneInstance = false;
				lineContentsSub = SHAREDvars.replaceAllOccurancesOfString(&lineContentsSub, preprocessorMathOperatorsEquivalentNumberOfTypes[i], preprocessorMathOperators[i], &foundAtLeastOneInstance);	//NB this is type sensitive; could be changed in the future
				if(foundAtLeastOneInstance)
				{
					result = true;	//added 1r5d
				}
			}
						
		#ifdef NLC_MATH_OBJECTS_ADVANCED
			lineContentsNew = lineContentsNew + lineContentsSub;
			if(stillFindingLineContentsSub)
			{	
				//add the string quotation text
				int indexOfStringDelimiter = lineContents->find(NLC_MATH_OBJECTS_STRING_DELIMITER_CHAR, lineContentsSubIndexEnd);
				if(indexOfStringDelimiter != CPP_STRING_FIND_RESULT_FAIL_VALUE)
				{
					lineContentsSubIndex = indexOfStringDelimiter + 1;
					lineContentsNew = lineContentsNew + lineContents->substr(lineContentsSubIndexEnd, indexOfStringDelimiter-lineContentsSubIndexEnd + 1);
					//cout << "lineContents ss = " << lineContents->substr(lineContentsSubIndexEnd, indexOfStringDelimiter-lineContentsSubIndexEnd + 1) << endl;
				}
				else
				{
					//unfinished quotation
					stillFindingLineContentsSub = false;
					lineContentsNew = lineContentsNew + lineContents->substr(lineContentsSubIndexEnd);	
					cout << "replaceLogicalConditionNaturalLanguageMathWithSymbols{} error: unfinished quotation detected" << endl;
				}			
			}
		}
		*lineContents = lineContentsNew;
		#else
		*lineContents = lineContentsSub;
		#endif
		
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
				//#ifdef NLC_DEBUG_PREPROCESSOR
				cout << "detectAndReplaceIsEqualToNonLogicalConditionTextWithSymbol{}: found 'x is ...' at start of line; convert to mathText 'x = (nlp parsable phrase)" << endl;
				//#endif
			}
		}
		//the following is not supported by NLC at present: "if x is the number of chickens", the user must say "if the number of chickens is equal to x"

	}
			
	return result;
}

#ifdef NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
bool NLCpreprocessorMathClass::splitMathDetectedLineLogicalConditionCommandIntoSeparateSentences(string* lineContents, int currentIndentation, const NLCpreprocessorSentence* fullSentence, NLCpreprocessorSentence* firstSentenceInLogicalConditionCommandTemp, bool* detectedLogicalConditionCommand)
{
	bool result = true;

	//#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE - consider moving this code out of splitMathDetectedLineLogicalConditionCommandIntoSeparateSentences as it may be required more generally (ie by some other non-advanced phrase detection functions)
	if(fullSentence->hasLogicalConditionOperator)
	{
		/*not required because brackets are added to logical condition operators, and they are not accepted as legal words for nlp parsable phrase extraction;
		//prevent logical condition operatators from being considered legal words by splitMathDetectedLineIntoNLPparsablePhrases
		startIndex = logicalConditionOperationsArray[fullSentence->logicalConditionOperator].length();
		mathText = mathText + logicalConditionOperationsArray[fullSentence->logicalConditionOperator];
		#ifdef NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
		indexOfLogicalConditionCommand = indexOfLogicalConditionCommand-logicalConditionOperationsArray[fullSentence->logicalConditionOperator].length();
		#endif
		*/

		if(fullSentence->logicalConditionOperator == NLC_LOGICAL_CONDITION_OPERATIONS_ELSE)
		{
			//add a comma after "else", such that the logical condition command will be created (in a new sentence) instead of creating an nlp parsable phrase
			if((lineContents->length() > logicalConditionOperationsArray[NLC_LOGICAL_CONDITION_OPERATIONS_ELSE].length()) && ((*lineContents)[logicalConditionOperationsArray[NLC_LOGICAL_CONDITION_OPERATIONS_ELSE].length()] != CHAR_COMMA))
			{
				lineContents->insert(logicalConditionOperationsArray[NLC_LOGICAL_CONDITION_OPERATIONS_ELSE].length(), STRING_COMMA);
			}
		}
	}
	//#endif

	string logicalConditionCommandSubphraseContents = "";
	if(fullSentence->hasLogicalConditionOperator)
	{
		int logicalConditionCommandSubphraseLineIndex = INT_DEFAULT_VALUE;
		if(!NLCpreprocessorMathLogicalConditions.generateLogicalConditionImplicitConjunctionsAndIdentifyCommand(lineContents, detectedLogicalConditionCommand, &logicalConditionCommandSubphraseContents, &logicalConditionCommandSubphraseLineIndex))
		{
			result = false;
		}
		if(*detectedLogicalConditionCommand)
		{

			*lineContents = lineContents->substr(0, logicalConditionCommandSubphraseLineIndex);
			NLCpreprocessorMathLogicalConditions.generateSeparateSentencesFromCommand(logicalConditionCommandSubphraseContents, currentIndentation+1, firstSentenceInLogicalConditionCommandTemp);
		}
	}

	return result;
}
#endif

bool NLCpreprocessorMathClass::splitMathDetectedLineIntoNLPparsablePhrases(string* lineContents, NLCpreprocessorSentence** currentNLCsentenceInList, int* sentenceIndex, const int currentIndentation, string* functionContents, NLCfunction* currentNLCfunctionInList, const NLCfunction* firstNLCfunctionInList)
{
	bool result = true;

	int startIndex = 0;

	NLCpreprocessorSentence* fullSentence = *currentNLCsentenceInList;

	int sentenceIndexOfFullSentence = *sentenceIndex;
	NLCpreprocessorParsablePhrase* currentParsablePhraseInList = fullSentence->firstNLPparsablePhraseInList;

	#ifdef NLC_PREPROCESSOR_MATH_DETECT_AND_DECLARE_IMPLICITLY_DECLARED_VARIABLES
	string newlyDeclaredVariable = "";
	#endif

	#ifdef NLC_PREPROCESSOR_MATH_SUPPORT_USER_VARIABLE_TYPE_DECLARATIONS
	this->replaceExplicitVariableTypesWithNLPparsablePhraseIllegalWords(lineContents);
	#endif

	#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
	bool additionalClosingBracketRequired = false;
	if(fullSentence->hasLogicalConditionOperator)
	{
		if(!NLCpreprocessorMathLogicalConditions.replaceLogicalConditionNaturalLanguageMathWithSymbols(lineContents, fullSentence->logicalConditionOperator, &additionalClosingBracketRequired, false))
		{
			result = false;
		}
	}
	#endif

	//NLP parsable phrase is taken to be at least 2 consecutive words delimited by a space ie, [a-zA-Z0-9_] [a-zA-Z0-9_]
	int wordIndex = 0;
	int phraseIndex = NLC_PREPROCESSOR_MATH_FIRST_PARSABLE_PHRASE_INDEX;
	string currentWord = "";
	string currentPhrase = "";
	string mathText = "";
	bool NLPparsableMandatoryCharacterFoundInCurrentWord = false;	//NB NLPparsableMandatoryCharacterFoundInCurrentWord is not currently used with NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_SUPPORT_ALPHANUMERIC_VARIABLE_NAMES
	bool parsingWhiteSpace = false;	//added 1h5b 30-July-2014


	#ifdef NLC_MATH_OBJECTS_ADVANCED
	bool parsingQuotation = false;
	#endif

	bool finalWordInSentenceFoundAndIsLegal = false;
	for(int i=startIndex; i<lineContents->length(); i++)
	{
		//eg y = x+the number of house in the park
		//eg y = x+(the number of house in the park)
		char c = (*lineContents)[i];

		bool legalWordCharacterFound = SHAREDvars.charInCharArray(c, preprocessorMathNLPparsableCharacters, NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_CHARACTERS_NUMBER_OF_TYPES);
		if(legalWordCharacterFound)
		{
			NLPparsableMandatoryCharacterFoundInCurrentWord = true;
		}

		#ifdef NLC_MATH_OBJECTS_ADVANCED
		if(c == NLC_MATH_OBJECTS_STRING_DELIMITER_CHAR)
		{
			if(parsingQuotation)
			{
				parsingQuotation = false;
			}
			else
			{
				parsingQuotation = true;
			}
		}
		if(parsingQuotation)
		{
			NLPparsableMandatoryCharacterFoundInCurrentWord = false;
		}
		#endif

		finalWordInSentenceFoundAndIsLegal = false;
		if(legalWordCharacterFound && (i == lineContents->length()-1))
		{
			if(wordIndex >= (NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_MIN_NUMBER_WORDS-1))
			{
				//add final word in sentence to phrase if it is legal
				currentWord = currentWord + c;
				#ifdef NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_SUPPORT_ALPHANUMERIC_VARIABLE_NAMES_ONLY
				if(NLCpreprocessorSentenceClass.isStringNLPparsableWord(currentWord, true))
				{
				#endif
					finalWordInSentenceFoundAndIsLegal = true;
				#ifdef NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_SUPPORT_ALPHANUMERIC_VARIABLE_NAMES_ONLY
				}
				#endif
			}

		}
		bool wordDelimiterCharacterFound = SHAREDvars.charInCharArray(c, preprocessorMathNLPparsableCharactersDelimiter, NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_CHARACTERS_DELIMITER_NUMBER_OF_TYPES);

		if(!legalWordCharacterFound || finalWordInSentenceFoundAndIsLegal)
		{//!legalWordCharacterFound or (legalWordCharacterFound && last character in sentence)


			//current word checks:
			#ifdef NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_SUPPORT_ALPHANUMERIC_VARIABLE_NAMES_ONLY
			if(!NLCpreprocessorSentenceClass.isStringNLPparsableWord(currentWord, true))
			{
				cout << "splitMathDetectedLineIntoNLPparsablePhrases{}: user input error - variables names cannot start with numbers: " << currentWord << endl;
				exit(EXIT_ERROR);
			}
			#endif

			if((fullSentence->hasLogicalConditionOperator))
			{
				if(i == currentWord.length())
				{
					if(SHAREDvars.textInTextArray(currentWord, logicalConditionOperationsArray, NLC_LOGICAL_CONDITION_OPERATIONS_NUMBER_OF_TYPES))
					{
						NLPparsableMandatoryCharacterFoundInCurrentWord = false;
					}
				}

			}

			#ifdef NLC_PREPROCESSOR_MATH_DETECT_AND_DECLARE_IMPLICITLY_DECLARED_VARIABLES
			if(!(fullSentence->hasLogicalConditionOperator))
			{
				int indexOfMathEqualsSetCommand = INT_DEFAULT_VALUE;
				bool foundMathEqualsSetCommand = this->findCharacterAtIndexOrAfterSpace(lineContents, i, NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_SET_CHAR, &indexOfMathEqualsSetCommand);	//mathText eg: "X=.." OR "X =.."
				if(foundMathEqualsSetCommand)
				{
					if(currentWord.length() != 0)
					{//added 1r5l
						int variableTypeTemp = INT_DEFAULT_VALUE;
						string variableName = currentWord;
						if(!this->findPredefinedMathtextVariable(&currentWord, currentNLCfunctionInList, firstNLCfunctionInList, fullSentence, &variableTypeTemp))
						{//variable not detected in previous sentences (found first use of variable in current sentence)

							string variableTypeMathtext = "";
							int variableTypeObject = INT_DEFAULT_VALUE;
							bool addMathTextVariable = false;

							if(i == currentWord.length())	//word comprises first mathText contents
							{//first word in mathText (type will automatically be assigned) (eg "X = ")

								#ifdef NLC_MATH_OBJECTS_ADVANCED
								string mathTextSubphraseContainingNLPparsablePhrase = lineContents->substr(indexOfMathEqualsSetCommand);
								int mathObjectVariableType = NLC_MATH_OBJECTS_VARIABLE_TYPE_UNKNOWN;

								for(int j=0; j<NLC_MATH_OBJECTS_VARIABLE_TYPE_BOOLEAN_OPERATORS_NUMBER_OF_TYPES; j++)
								{
									if(mathTextSubphraseContainingNLPparsablePhrase.find(mathObjectsVariableTypeBooleanOperators[j]) != CPP_STRING_FIND_RESULT_FAIL_VALUE)
									{
										mathObjectVariableType = NLC_MATH_OBJECTS_VARIABLE_TYPE_BOOLEAN;
									}
								}

								for(int j=0; j<NLC_MATH_OBJECTS_VARIABLE_TYPE_NUMERICAL_OPERATORS_NUMBER_OF_TYPES; j++)
								{
									if(mathTextSubphraseContainingNLPparsablePhrase.find(mathObjectsVariableTypeNumericalOperators[j]) != CPP_STRING_FIND_RESULT_FAIL_VALUE)
									{
										mathObjectVariableType = NLC_MATH_OBJECTS_VARIABLE_TYPE_NUMERICAL;
									}
								}

								for(int j=0; j<NLC_MATH_OBJECTS_VARIABLE_TYPE_STRING_OPERATORS_NUMBER_OF_TYPES; j++)
								{
									if(mathTextSubphraseContainingNLPparsablePhrase.find(mathObjectsVariableTypeStringOperators[j]) != CPP_STRING_FIND_RESULT_FAIL_VALUE)
									{
										mathObjectVariableType = NLC_MATH_OBJECTS_VARIABLE_TYPE_STRING;
									}
								}

								if(mathObjectVariableType == NLC_MATH_OBJECTS_VARIABLE_TYPE_BOOLEAN)
								{
									variableTypeMathtext = NLC_PREPROCESSOR_MATH_MATHTEXT_VARIABLE_TYPE_BOOLEAN;
									variableTypeObject = NLC_MATH_OBJECTS_VARIABLE_TYPE_BOOLEAN;
								}
								else if(mathObjectVariableType == NLC_MATH_OBJECTS_VARIABLE_TYPE_NUMERICAL)
								{
									variableTypeMathtext = NLC_PREPROCESSOR_MATH_MATHTEXT_VARIABLE_TYPE_NUMERICAL;
									variableTypeObject = NLC_MATH_OBJECTS_VARIABLE_TYPE_NUMERICAL;
								}
								else if(mathObjectVariableType == NLC_MATH_OBJECTS_VARIABLE_TYPE_STRING)
								{
									variableTypeMathtext = NLC_PREPROCESSOR_MATH_MATHTEXT_VARIABLE_TYPE_STRING;
									variableTypeObject = NLC_MATH_OBJECTS_VARIABLE_TYPE_STRING;
								}
								else if(mathObjectVariableType == NLC_MATH_OBJECTS_VARIABLE_TYPE_UNKNOWN)
								{
									cout << "splitMathDetectedLineIntoNLPparsablePhrases{} error: implicitly declared mathText variable and variable type cannot be statically detected based on line contents" << endl;
									exit(EXIT_ERROR);
								}
								#else
								variableTypeMathtext = NLC_PREPROCESSOR_MATH_MATHTEXT_VARIABLE_TYPE_NUMERICAL;
								variableTypeObject = NLC_MATH_OBJECTS_VARIABLE_TYPE_NUMERICAL;
								#endif

								//NB considering the current phrase contains an equal sign it will be classified as mathText, not an nlp parsable phrase
								//#ifdef NLC_DEBUG_PREPROCESSOR_MATH_DETECT_AND_DECLARE_UNDECLARED_VARIABLES
								cout << "implicitly declared mathText variable detected: declaring " << variableTypeMathtext << currentWord << endl;	//inserting mathText variable declaration type (eg double)
								//#endif
								currentPhrase.insert(0, variableTypeMathtext);

								newlyDeclaredVariable = currentWord;
								NLPparsableMandatoryCharacterFoundInCurrentWord = false;
								addMathTextVariable = true;
							}
							else
							{//explicit type may have been provided (mathText eg: "int X = ")
								bool explictTypeFound = false;
								for(int j=0; j<NLC_PREPROCESSOR_MATH_MATHTEXT_VARIABLES_NUMBER_OF_TYPES; j++)
								{
									#ifdef NLC_PREPROCESSOR_MATH_SUPPORT_USER_VARIABLE_TYPE_DECLARATIONS
									int indexOfType = lineContents->find(preprocessorMathMathTextVariables[j]);
									#else
									int indexOfType = lineContents->find(preprocessorMathNaturalLanguageVariables[j]);
									#endif
									if((indexOfType != CPP_STRING_FIND_RESULT_FAIL_VALUE) && (indexOfType < i))
									{
										explictTypeFound = true;

										newlyDeclaredVariable = currentWord;
										NLPparsableMandatoryCharacterFoundInCurrentWord = false;
										variableTypeObject = preprocessorMathTextVariableMathObjectTypes[j];
										addMathTextVariable = true;
									}
								}
							}

							if(addMathTextVariable)
							{
								this->addNewMathTextVariable(fullSentence, variableName, variableTypeObject);
							}

						}
						#ifdef NLC_PREPROCESSOR_MATH_FIX_BUG_ADD_MATH_TEXT_VARIABLES_DUPLICATES
						else
						{
							this->addNewMathTextVariable(fullSentence, variableName, variableTypeTemp);
						}
						#endif
					}
				}
			}
			#endif

			if(NLPparsableMandatoryCharacterFoundInCurrentWord)
			{
				if(!parsingWhiteSpace)
				{
					this->addNewMathTextVariable(fullSentence, currentWord, NLC_MATH_OBJECTS_VARIABLE_TYPE_UNKNOWN);
				}
				else
				{
					if(currentWord != "")
					{
						cout << "splitMathDetectedLineIntoNLPparsablePhrases{} error: currentWord != "" && parsingWhiteSpace" << endl;
					}
				}
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


						//remove all mathTextVariable nlp parsable phrase (as an NLP parsable phrase does not contain mathText variable names, or if it does the mathText variable are references to predefined mathText variables and will be detected later)
						for(int i=0; i<wordIndex; i++)
						{
							this->removeLastMathTextVariable(fullSentence);
						}

						//split sentence and add phrase
						currentParsablePhraseInList->mathTextNLPparsablePhraseIndex = phraseIndex;
						#ifdef NLC_PREPROCESSOR_RECORD_PARSABLE_PHRASE_POSITION_APPROXIMATE
						currentParsablePhraseInList->mathTextNLPparsablePhrasePositionApproximate = i - currentPhrase.length();	//CHECKTHIS
						#endif
						#ifdef NLC_PREPROCESSOR_MATH_USE_HUMAN_READABLE_VARIABLE_NAMES
						bool spaceAtEndOfPhrase = false;
						if(currentPhrase[currentPhrase.length()-1] == CHAR_SPACE)
						{
							spaceAtEndOfPhrase = true;
							currentPhrase = currentPhrase.substr(0, currentPhrase.length()-1);
						}
						#endif
						bool lastCharacterOfPhraseIsFullStop = false;
						if(currentPhrase[currentPhrase.length()-1] == NLC_PREPROCESSOR_END_OF_SENTENCE_CHAR)
						{
							lastCharacterOfPhraseIsFullStop = true;
						}
						#ifdef NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_SUPPORT_FILENAMES_WITH_FULLSTOPS
						if(!lastCharacterOfPhraseIsFullStop)
						{
						#endif
							currentParsablePhraseInList->sentenceContents = currentPhrase + NLC_PREPROCESSOR_END_OF_SENTENCE_CHAR;	//append a fullstop to the NLP parsable phrase to make it readable by NLP
						#ifdef NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_SUPPORT_FILENAMES_WITH_FULLSTOPS
						}
						else
						{
							currentParsablePhraseInList->sentenceContents = currentPhrase;
						}
						#endif
						currentParsablePhraseInList->sentenceIndex = *sentenceIndex;
						mathText = mathText + NLCpreprocessorSentenceClass.generateMathTextNLPparsablePhraseReference(sentenceIndexOfFullSentence, currentParsablePhraseInList);

						#ifdef NLC_PREPROCESSOR_MATH_USE_HUMAN_READABLE_VARIABLE_NAMES
						if(spaceAtEndOfPhrase)
						{
							//readd the final space to the mathText since it has been removed from the nlp parsable phrase
							mathText = mathText + CHAR_SPACE;
						}
						#endif
						currentParsablePhraseInList->next = new NLCpreprocessorParsablePhrase();
						currentParsablePhraseInList = currentParsablePhraseInList->next;
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

					}
					else
					{
						//currentWord is a mathText variable name (c is likely a mathematical operator)
						currentPhrase = currentPhrase + currentWord + c;	//add previous words in the failed NLP parsable phrase (if existent) and the currentWord to the mathText
						mathText = mathText + currentPhrase;
						currentPhrase = "";	//restart phrase (assuming it contains text)
					}
					wordIndex = 0;
					parsingWhiteSpace = false;
				}
				else
				{//wordDelimiterCharacterFound
					currentPhrase = currentPhrase + currentWord + c;
					parsingWhiteSpace = true;
				}
			}
			else
			{
				//currentWord is disgarded as math (OLD: eg numbers) in mathText as it does not contain a mandatory character
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
		{//legalWordCharacterFound || !finalWordInSentenceFoundAndIsLegal
			currentWord = currentWord + c;
			parsingWhiteSpace = false;
		}
	}
	if(!finalWordInSentenceFoundAndIsLegal)
	{
		//insufficient number of words in final phrase detected to create an NLP parsable phrase; add words to mathText instead
		//currentWord is [assumed to be] a mathText variable name
		currentPhrase = currentPhrase + currentWord;	//add previous words in the failed NLP parsable phrase (if existent) and the currentWord to the mathText
		mathText = mathText + currentPhrase;
		currentPhrase = "";	//restart phrase (assuming it contains text)	//redundant (as it is the final word in the sentence)

		#ifdef NLC_PREPROCESSOR_MATH_DETECT_MATHTEXT_VARIABLES_AT_END_OF_LINE
		if(NLPparsableMandatoryCharacterFoundInCurrentWord)
		{
			this->addNewMathTextVariable(fullSentence, currentWord, NLC_MATH_OBJECTS_VARIABLE_TYPE_UNKNOWN);	//added 1p12d
		}
		#endif
	}

	//now write the full mathText to each sub sentence (NLP parsable phrase) - required for NLC to regenerate the correct math and variable definitions (based on NLP parsable phrases)
	fullSentence->isMath = true;
	fullSentence->mathTextNLPparsablePhraseTotal = phraseIndex;
	fullSentence->mathText = mathText;
	fullSentence->indentation = currentIndentation;
	if(fullSentence->mathTextNLPparsablePhraseTotal == 0)
	{
		//add dummy phrase for NLP to parse (will not be used by NLC; create NLP/GIA sentence as a filler for math text replacement only)
		currentParsablePhraseInList->sentenceContents = string(NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_DUMMY);
		currentParsablePhraseInList->sentenceIndex = (*sentenceIndex);	//added 1r5h
		currentParsablePhraseInList->next = new NLCpreprocessorParsablePhrase();
		currentParsablePhraseInList = currentParsablePhraseInList->next;
		(*sentenceIndex) = (*sentenceIndex) + 1;
	}


	//remove all numbers from mathTextVariables - added 1l7a
	for(vector<NLCvariable*>::iterator iter = fullSentence->mathTextVariables.begin(); iter != fullSentence->mathTextVariables.end();)
	{
		string mathTextVariableName = (*iter)->name;
		bool variableNameIsIllegal = false;
		if(NLCpreprocessorSentenceClass.isStringNumberPreprocessorMath(mathTextVariableName))
		{
			variableNameIsIllegal = true;
		}

		#ifdef NLC_PREPROCESSOR_MATH_DETECT_MATHTEXT_FUNCTIONS_SUPPORTED_BY_TARGET_LANGUAGE
		if(SHAREDvars.textInTextArray(mathTextVariableName, preprocessorMathTextFunctionsSupportedByTargetLanguage, NLC_PREPROCESSOR_MATH_DETECT_MATHTEXT_FUNCTIONS_SUPPORTED_BY_TARGET_LANGUAGE_NUMBER_OF_TYPES))
		{
			variableNameIsIllegal = true;
		}
		#endif
		if(variableNameIsIllegal)
		{
			iter = fullSentence->mathTextVariables.erase(iter);
		}
		else
		{
			iter++;
		}
	}


	#ifdef NLC_PREPROCESSOR_MATH_DETECT_USE_OF_UNDECLARED_VARIABLES
	//if(!(fullSentence->hasLogicalConditionOperator))
	//{
	for(vector<NLCvariable*>::iterator iter = fullSentence->mathTextVariables.begin(); iter != fullSentence->mathTextVariables.end(); )
	{
		NLCvariable* mathTextVariable = (*iter);
		string mathTextVariableName = mathTextVariable->name;

		bool ignoreVariable = false;
		bool removeVariable = false;
		if((fullSentence->hasLogicalConditionOperator))
		{
			if(SHAREDvars.textInTextArray(mathTextVariableName, logicalConditionOperationsArray, NLC_LOGICAL_CONDITION_OPERATIONS_NUMBER_OF_TYPES))
			{
				#ifdef NLC_PREPROCESSOR_MATH_FIX_BUG_DO_NOT_ADD_LOGICAL_CONDITION_OPERATORS_TO_MATH_TEXT_VARIABLES
				removeVariable = true;	//remove type eg "if"
				#else
				ignoreVariable = true;
				#endif
			}
		}
		if(SHAREDvars.textInTextArray(mathTextVariableName, preprocessorMathNaturalLanguageVariables, NLC_PREPROCESSOR_MATH_MATHTEXT_VARIABLES_NUMBER_OF_TYPES))	//NB do not check preprocessorMathMathTextVariables because currentWord will not contain the appended $ character
		{
			#ifdef NLC_PREPROCESSOR_MATH_FIX_BUG_DO_NOT_ADD_TYPES_TO_MATH_TEXT_VARIABLES
			removeVariable = true;	//remove type eg "double"
			#else
			ignoreVariable = true;
			#endif
		}

		if(removeVariable)
		{
			iter = fullSentence->mathTextVariables.erase(iter);
		}
		else
		{
			if(mathTextVariableName != newlyDeclaredVariable)
			{
				int variableTypeTemp = INT_DEFAULT_VALUE;
				if(this->findPredefinedMathtextVariable(&mathTextVariableName, currentNLCfunctionInList, firstNLCfunctionInList, fullSentence, &variableTypeTemp))
				{
					#ifdef NLC_MATH_OBJECTS_ADVANCED_INFER_TYPE_BASED_ON_PREVIOUSLY_DECLARED_MATHTEXT_VARIABLES
					if(variableTypeTemp == NLC_MATH_OBJECTS_VARIABLE_TYPE_UNKNOWN)
					{
						cout << "NLC_MATH_OBJECTS_ADVANCED_INFER_TYPE_BASED_ON_PREVIOUSLY_DECLARED_MATHTEXT_VARIABLES: splitMathDetectedLineIntoNLPparsablePhrases{} error: first instance of mathText variable type in function == NLC_MATH_OBJECTS_VARIABLE_TYPE_UNKNOWN" << endl;
						exit(EXIT_ERROR);
					}
					else
					{
						/*
						required for:
						String l = ""
						l = the house
						*/
						mathTextVariable->type = variableTypeTemp;
					}
					#endif
				}
				else
				{
					if(!ignoreVariable)
					{
						cout << "splitMathDetectedLineIntoNLPparsablePhrases{} error: mathText variable " << mathTextVariableName << " is undeclared" << endl;
						//cout << "lineContents = " <<* lineContents << endl;
						#ifndef NLC_PREPROCESSOR_MATH_ALLOW_UNDECLARED_MATHTEXT_VARIABLES_TO_BE_REFERENCED_BY_MATH
						exit(EXIT_ERROR);
						#endif
					}
				}
			}
			iter++;
		}
	}
	//}
	#endif


	#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE

	//#ifndef NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
	if(fullSentence->hasLogicalConditionOperator)
	{
	//#endif
		if(!NLCpreprocessorMathLogicalConditions.splitMathDetectedLineIntoNLPparsablePhrasesLogicalConditionAddExplicitSubjectTextForConjunctions(fullSentence, sentenceIndex, additionalClosingBracketRequired))
		{
			result = false;
		}
	//#ifndef NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
	}
	//#endif

	if(fullSentence->hasLogicalConditionOperator)
	{
		if(!NLCpreprocessorMathLogicalConditions.replaceLogicalConditionNaturalLanguageMathWithSymbolsEnd(fullSentence, additionalClosingBracketRequired))
		{
			result = false;
		}

	}

	#endif

	#ifdef NLC_PREPROCESSOR_MATH_SUPPORT_USER_VARIABLE_TYPE_DECLARATIONS
	this->restoreExplicitVariableTypes(&(fullSentence->mathText));
	#endif

	
	currentParsablePhraseInList = fullSentence->firstNLPparsablePhraseInList;
	while(currentParsablePhraseInList->next != NULL)
	{
		*functionContents = *functionContents + currentParsablePhraseInList->sentenceContents + CHAR_NEWLINE;
		currentParsablePhraseInList = currentParsablePhraseInList->next;
	}

	(*currentNLCsentenceInList)->next = new NLCpreprocessorSentence();
	(*currentNLCsentenceInList) = (*currentNLCsentenceInList)->next;
					
	return result;
}


bool NLCpreprocessorMathClass::findCharacterAtIndexOrAfterSpace(const string* lineContents, int i, char characterToFind, int* indexOfCharacterFound)
{
	bool foundCharacter = false;
	bool wordDelimiterCharacterFound = SHAREDvars.charInCharArray((*lineContents)[i], preprocessorMathNLPparsableCharactersDelimiter, NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_CHARACTERS_DELIMITER_NUMBER_OF_TYPES);

	if((*lineContents)[i] == characterToFind)		//mathText eg1 (=): "X=.., eg2 (") "\".."
	{
		*indexOfCharacterFound = i;
		foundCharacter = true;
	}
	if(wordDelimiterCharacterFound && (i+1 < lineContents->length()) && ((*lineContents)[i+1] == characterToFind))	//mathText eg1 (=): "X =..", eg2 (") " \".."
	{
		*indexOfCharacterFound = i+1;
		foundCharacter = true;
	}
	return foundCharacter;
}


#ifdef NLC_PREPROCESSOR_MATH_SUPPORT_USER_VARIABLE_TYPE_DECLARATIONS
bool NLCpreprocessorMathClass::replaceExplicitVariableTypesWithNLPparsablePhraseIllegalWords(string* lineContents)
{
	bool result = false;
	//replaceExplicitVariableTypesWithNLPparsablePhraseIllegalWords() is required to prevent creation of nlp parsable phrase from 2 word variable declarations
	for(int i=0; i<NLC_PREPROCESSOR_MATH_MATHTEXT_VARIABLES_NUMBER_OF_TYPES; i++)
	{
		*lineContents = this->replaceSubstringAtStartOfString(lineContents, preprocessorMathNaturalLanguageVariables[i]+STRING_SPACE, preprocessorMathMathTextVariables[i]+STRING_SPACE);	//NB this is type sensitive; could be changed in the future
		result = true;
	}

	return result;
}

bool NLCpreprocessorMathClass::restoreExplicitVariableTypes(string* mathText)
{
	bool result = false;
	for(int i=0; i<NLC_PREPROCESSOR_MATH_MATHTEXT_VARIABLES_NUMBER_OF_TYPES; i++)
	{
		*mathText = this->replaceSubstringAtStartOfString(mathText, preprocessorMathMathTextVariables[i]+STRING_SPACE, preprocessorMathNaturalLanguageVariables[i]+STRING_SPACE);
		result = true;
	}

	return result;
}

string NLCpreprocessorMathClass::replaceSubstringAtStartOfString(const string* textOrig, string stringToFind, string replacementString)
{
	string text = *textOrig;
	int startCharacterOfSentence = 0;
	if(text.substr(startCharacterOfSentence, stringToFind.length()) == stringToFind)
	{
		text.replace(startCharacterOfSentence, stringToFind.length(), replacementString);
	}
	/*
	int pos = text.find(preprocessorMathNaturalLanguageVariables[i], startCharacterOfSentence)
	if(pos == startCharacterOfSentence)
	{
		text.replace(pos, stringToFind.length(), replacementString);
	}
	*/
	return text;
}

#endif

//NB variableType is in mathObject type format
void NLCpreprocessorMathClass::addNewMathTextVariable(NLCpreprocessorSentence* sentence, const string variableName, const int variableTypeObject)
{
	NLCvariable* mathtextVariable = new NLCvariable();
	mathtextVariable->name = variableName;
	mathtextVariable->type = variableTypeObject;
	sentence->mathTextVariables.push_back(mathtextVariable);
}

void NLCpreprocessorMathClass::removeLastMathTextVariable(NLCpreprocessorSentence* sentence)
{
	sentence->mathTextVariables.pop_back();
}


#ifdef NLC_PREPROCESSOR_MATH_REPLACE_NUMERICAL_VARIABLES_NAMES_FOR_NLP

bool NLCpreprocessorMathClass::replaceNumericalVariablesWithDummyNumberIfNecessary(string* lineContents, NLCpreprocessorSentence* currentNLCsentenceInList, NLCfunction* currentNLCfunctionInList, const NLCfunction* firstNLCfunctionInList)
{
	bool result = true;

	string currentWord = "";
	bool parsingWhiteSpace = true;
	int i = 0;
	while(i < lineContents->length())
	{
		char c = (*lineContents)[i];
		if(this->isWhiteSpaceOrInvalidWordCharacter(c))
		{//new word detected
			if(!parsingWhiteSpace)
			{
				int variableTypeTemp = INT_DEFAULT_VALUE;
				if(this->findPredefinedMathtextVariable(&currentWord, currentNLCfunctionInList, firstNLCfunctionInList, NULL, &variableTypeTemp))	//pass firstNLCfunctionInList and update this->findPredefinedMathtextVariable() accordingly to allow global numerical variable definitions; not just local numerical variable definitions
				{
					if(variableTypeTemp == NLC_MATH_OBJECTS_VARIABLE_TYPE_NUMERICAL)	//CHECKTHIS: is this required?
					{
						//replace the variable name with a dummy number
						currentNLCsentenceInList->variableNamesDetected.push_back(currentWord);
						int dummyNumber = NLCpreprocessorSentenceClass.generateDummyNumber(currentNLCsentenceInList->variableNamesDetected.size());
						string dummyNumberString = SHAREDvars.convertIntToString(dummyNumber);
						lineContents->replace(i-currentWord.length(), currentWord.length(), dummyNumberString);
						i = i-currentWord.length()+dummyNumberString.length();
					}
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
		int variableTypeTemp = INT_DEFAULT_VALUE;
		if(this->findPredefinedMathtextVariable(&currentWord, currentNLCfunctionInList, firstNLCfunctionInList, NULL, &variableTypeTemp))	//pass firstNLCfunctionInList and update this->findPredefinedMathtextVariable() accordingly to allow global numerical variable definitions; not just local numerical variable definitions
		{
			if(variableTypeTemp == NLC_MATH_OBJECTS_VARIABLE_TYPE_NUMERICAL)		//CHECKTHIS: is this required?
			{
				//replace the variable name with a dummy number
				currentNLCsentenceInList->variableNamesDetected.push_back(currentWord);
				int dummyNumber = NLCpreprocessorSentenceClass.generateDummyNumber(currentNLCsentenceInList->variableNamesDetected.size());
				string dummyNumberString = SHAREDvars.convertIntToString(dummyNumber);
				lineContents->replace(lineContents->length()-currentWord.length(), currentWord.length(), dummyNumberString);
			}
		}
	}
	return result;
}

bool NLCpreprocessorMathClass::isWhiteSpaceOrInvalidWordCharacter(const char c)
{
	/*
	bool whiteSpaceOrInvalidWordCharacter = false;
	if(isWhiteSpace(c) || (c == CHAR_COMMA))
	{
		whiteSpaceOrInvalidWordCharacter = true;
	}
	*/
	bool legalWordCharacterFound = SHAREDvars.charInCharArray(c, preprocessorMathNLPparsableCharacters, NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_CHARACTERS_NUMBER_OF_TYPES);
	bool whiteSpaceOrInvalidWordCharacter = true;
	if(legalWordCharacterFound)
	{
		whiteSpaceOrInvalidWordCharacter = false;
	}

	return whiteSpaceOrInvalidWordCharacter;
}

#endif

bool NLCpreprocessorMathClass::findPredefinedMathtextVariable(const string* currentWord, NLCfunction* currentNLCfunctionInList, const NLCfunction* firstNLCfunctionInList, const NLCpreprocessorSentence* sentenceToIgnoreWhileSearching, int* variableType)
{
	#ifdef NLC_PREPROCESSOR_REPLACE_NUMERICAL_VARIABLES_DETECT_GLOBAL_NUMERICAL_VARIABLES
	return this->findPredefinedMathtextVariableInAnyFunctions(currentWord, firstNLCfunctionInList, sentenceToIgnoreWhileSearching, variableType);
	#else
	return this->findPredefinedMathtextVariableInFunction(currentWord, currentNLCfunctionInList, sentenceToIgnoreWhileSearching, variableType);
	#endif
}

#ifdef NLC_PREPROCESSOR_REPLACE_NUMERICAL_VARIABLES_DETECT_GLOBAL_NUMERICAL_VARIABLES
bool NLCpreprocessorMathClass::findPredefinedMathtextVariableInAnyFunctions(const string* currentWord, const NLCfunction* firstNLCfunctionInList, const NLCpreprocessorSentence* sentenceToIgnoreWhileSearching, int* variableType)
{
	bool result = false;
	currentNLCfunctionInList = firstNLCfunctionInList;
	while(currentNLCfunctionInList->next != NULL)
	{
		NLCpreprocessorSentence* currentNLCsentenceInList = currentNLCfunctionInList->firstNLCsentenceInFunction;
		if(this->findPredefinedMathtextVariableInFunction(currentWord, currentNLCfunctionInList, sentenceToIgnoreWhileSearching, variableType)
		{
			result = true;
		}

		currentNLCfunctionInList = currentNLCfunctionInList->next;
	}
	return result;
}
#endif

bool NLCpreprocessorMathClass::findPredefinedMathtextVariableInFunction(const string* currentWord, NLCfunction* currentNLCfunctionInList, const NLCpreprocessorSentence* sentenceToIgnoreWhileSearching, int* variableType)	//pass firstNLCfunctionInList and update findPredefinedMathtextVariable() accordingly to allow global numerical variable definitions; not just local numerical variable definitions
{
	bool result = false;

	NLCpreprocessorSentence* currentNLCsentenceInList = currentNLCfunctionInList->firstNLCsentenceInFunction;
	while(currentNLCsentenceInList->next != NULL)
	{
		if(currentNLCsentenceInList != sentenceToIgnoreWhileSearching)
		{
			for(vector<NLCvariable*>::iterator iter = currentNLCsentenceInList->mathTextVariables.begin(); iter != currentNLCsentenceInList->mathTextVariables.end(); iter++)
			{
				string mathTextVariableName = (*iter)->name;
				if(*currentWord == mathTextVariableName)
				{
					if(!result)	//only the first reference to the mathtext variable (ie its declaration sentence) will contain its type
					{
						*variableType = (*iter)->type;
						result = true;
					}
				}
			}
		}
		currentNLCsentenceInList = currentNLCsentenceInList->next;
	}

	return result;
}

#ifdef NLC_MATH_OBJECTS_ADVANCED_INFER_TYPE_BASED_ON_PREVIOUSLY_DECLARED_MATHTEXT_VARIABLES_ADVANCED
bool NLCpreprocessorMathClass::findMathTextVariableWithinMathText(string mathTextVariableName, string mathText)
{
	//assume: isStringValidVariableName(mathTextVariableName) == true

	bool result = false;
	bool stillFindingInstances = true;
	int currentIndexOfMathtextVariable = 0;
	while(stillFindingInstances)
	{
		currentIndexOfMathtextVariable = mathText.find(mathTextVariableName, currentIndexOfMathtextVariable);
		if(currentIndexOfMathtextVariable != CPP_STRING_FIND_RESULT_FAIL_VALUE)
		{
			//now check contents of text either side of potential mathText variable instance within mathText
			bool foundVariable = true;
			if(currentIndexOfMathtextVariable > 0)
			{
				if(!this->isWhiteSpaceOrInvalidWordCharacter(mathText[currentIndexOfMathtextVariable-1]))
				{
					foundVariable = false;
				}
			}

			if(currentIndexOfMathtextVariable < mathText.length()-mathTextVariableName.length())
			{
				if(!this->isWhiteSpaceOrInvalidWordCharacter(mathText[currentIndexOfMathtextVariable + mathTextVariableName.length()]))
				{
					foundVariable = false;
				}
			}

			if(foundVariable)
			{
				result = true;
			}

			currentIndexOfMathtextVariable = currentIndexOfMathtextVariable+1;
		}
		else
		{
			stillFindingInstances = false;
		}
	}

	return result;
}
#endif



#endif
#endif




