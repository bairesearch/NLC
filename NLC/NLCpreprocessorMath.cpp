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
 * Project: Natural Language Compiler
 * Project Version: 2e2a 13-December-2017
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/


#include "NLCpreprocessorMath.hpp"

#ifdef NLC_PREPROCESSOR
#ifdef NLC_PREPROCESSOR_MATH

bool NLCpreprocessorMathClass::detectMathSymbolsInLine(const vector<GIApreprocessorWord*>* lineContents)
{
	bool mathSymbolFound = false;
	for(int i=0; i<NLC_PREPROCESSOR_MATH_OPERATORS_NUMBER_OF_TYPES; i++)
	{
		for(int w = 0; w < lineContents->size(); w++)
		{
			string currentWord = (*lineContents)[w]->tagName;
			int symbolFoundIndex = currentWord.find(preprocessorMathOperators[i]);
			if(symbolFoundIndex != CPP_STRING_FIND_RESULT_FAIL_VALUE)
			{
				mathSymbolFound = true;
			}
		}
	}
	return mathSymbolFound;
}

bool NLCpreprocessorMathClass::detectAndReplaceIsEqualToNonLogicalConditionTextWithSymbol(vector<GIApreprocessorWord*>* lineContents, const bool hasLogicalConditionOperator, const bool isMathText)
{
	bool result = false;
	//cout << "lineContents = " << *lineContents << endl;
	
	if(!hasLogicalConditionOperator)
	{
		for(int i=0; i<NLC_PREPROCESSOR_MATH_OPERATORS_NUMBER_OF_TYPES; i++)
		{
			//convert x is equal to/equals the number of chickens" to mathText and parsable phrase ("x = the number of chickens")
			//cout << "lineContents = " << GIApreprocessorMultiwordReductionClassObject.generateTextFromVectorWordList(lineContents) << endl;
			//cout << "preprocessorMathOperatorsEquivalentNumberOfTypes[i] = " << preprocessorMathOperatorsEquivalentNumberOfTypes[i] << endl;
			//cout << "preprocessorMathOperators[i] = " << preprocessorMathOperators[i] << endl;
			if(GIApreprocessorMultiwordReductionClassObject.findAndReplaceAllOccurancesSimpleSubstringInWordListWithSimpleSubstring(lineContents, preprocessorMathOperatorsEquivalentNumberOfTypes[i], preprocessorMathOperators[i]))
			{
				result = true;
			}
		}
		
		#ifdef NLC_MATH_OBJECTS_ADVANCED
		//special case reimplemented 2b3g;
		for(int w=0; w<lineContents->size()-1; w++)
		{
			if((*lineContents)[w]->tagName == NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_IS)
			{
				if(((*lineContents)[w+1]->tagName)[0] == NLC_MATH_OBJECTS_STRING_DELIMITER_CHAR)
				{
					//ie 'is "' NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_IS_STRING
					(*lineContents)[w]->tagName = NLC_PREPROCESSOR_MATH_OPERATOR_STRING_EQUALS_SET; 	//NLC_PREPROCESSOR_MATH_OPERATOR_STRING_EQUALS_SET_NEW
					result = true;
					//cout << "lineContents = " <<  GIApreprocessorMultiwordReductionClassObject.generateTextFromVectorWordList(lineContents) << endl;
				}
			}
		}
		#endif
		
		//"x is equal to number of chickens." is supported by mathText, with "number of chickens" parsable phrase
		//the following cannot be parsed by NLP/GIA; "x is the number of chickens" as dummy numerical variable replacement only works for previously defined variables.
		//convert "x is the number of chickens" to mathText and parsable phrase ("x = the number of chickens")
		bool foundMatchedString = false;
		if(GIApreprocessorMultiwordReductionClassObject.findAndReplaceSimpleSubstringInWordListAtIndexWithSimpleSubstring(lineContents, NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_IS_EQUAL_TO_INFORMAL, 1, NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_SET))
		{
			result = true;
			
			//#ifdef NLC_DEBUG_PREPROCESSOR
			cout << "detectAndReplaceIsEqualToNonLogicalConditionTextWithSymbol{}: found 'x is ...' at start of line; convert to mathText 'x = (nlp parsable phrase)" << endl;
			//#endif
		
			//the following is not supported by NLC at present: "if x is the number of chickens", the user must say "if the number of chickens is equal to x"
		}
	}
			
	return result;
}

#ifdef NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
bool NLCpreprocessorMathClass::splitMathDetectedLineLogicalConditionCommandIntoSeparateSentences(vector<GIApreprocessorWord*>* lineContents, int currentIndentation, const NLCpreprocessorSentence* fullSentence, NLCpreprocessorSentence* firstSentenceInLogicalConditionCommandTemp, bool* detectedLogicalConditionCommand)
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
			if((lineContents->size() >= 2) && ((*lineContents)[1]->tagName != STRING_COMMA))
			{ 
				GIApreprocessorMultiwordReductionClassObject.insertStringIntoWordList(lineContents, STRING_COMMA, 1);
			}
		}
	}
	//#endif

	vector<GIApreprocessorWord*> logicalConditionCommandSubphraseContents;
	if(fullSentence->hasLogicalConditionOperator)
	{
		int logicalConditionCommandSubphraseLineIndex = INT_DEFAULT_VALUE;
		if(!NLCpreprocessorMathLogicalConditions.generateLogicalConditionImplicitConjunctionsAndIdentifyCommand(lineContents, detectedLogicalConditionCommand, &logicalConditionCommandSubphraseContents, &logicalConditionCommandSubphraseLineIndex))
		{
			result = false;
		}
		if(*detectedLogicalConditionCommand)
		{
			*lineContents = GIApreprocessorMultiwordReductionClassObject.extractSubWordListInWordList(lineContents, 0, logicalConditionCommandSubphraseLineIndex); 
			NLCpreprocessorMathLogicalConditions.generateSeparateSentencesFromCommand(&logicalConditionCommandSubphraseContents, currentIndentation+1, firstSentenceInLogicalConditionCommandTemp);
		}
	}

	return result;
}
#endif

bool NLCpreprocessorMathClass::splitMathDetectedLineIntoNLPparsablePhrases(vector<GIApreprocessorWord*>* lineContents, NLCpreprocessorSentence** currentNLCsentenceInList, int* sentenceIndex, const int currentIndentation, NLCfunction* currentNLCfunctionInList, const NLCfunction* firstNLCfunctionInList)
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
	int logicalConditionOperatorNumberWords = 0; 
	if(fullSentence->hasLogicalConditionOperator)
	{
		vector<GIApreprocessorWord*> logicalConditionOperationWordList;
		GIApreprocessorMultiwordReductionClassObject.generateSentenceWordListFromStringSimple(&logicalConditionOperationWordList, &(logicalConditionOperationsArray[fullSentence->logicalConditionOperator]));
		logicalConditionOperatorNumberWords = logicalConditionOperationWordList.size();
		
		if(!NLCpreprocessorMathLogicalConditions.replaceLogicalConditionNaturalLanguageMathWithSymbols(lineContents, fullSentence->logicalConditionOperator, &additionalClosingBracketRequired, false))
		{
			result = false;
		}
	}
	#endif

	#ifdef NLC_PREPROCESSOR_DEBUG
	cout << "splitMathDetectedLineIntoNLPparsablePhrases lineContents = " <<  GIApreprocessorMultiwordReductionClassObject.generateTextFromVectorWordList(lineContents) << endl;
	#endif

	int phraseIndex = NLC_PREPROCESSOR_MATH_FIRST_PARSABLE_PHRASE_INDEX;
	int wordIndex = 0;	//wordIndex in parsable phrase
	vector<GIApreprocessorWord*> currentPhrase;
	string mathText = "";
	bool previousWordWasNLPparsable = false;
	bool previousWordWasLogicalConditionOperator = false;
	
	for(int w=0; w<lineContents->size(); w++)
	{
		GIApreprocessorWord* currentWordTag = (*lineContents)[w];
		string currentWord = currentWordTag->tagName;
		//NLP parsable phrase is taken to be at least 2 consecutive words delimited by a space ie, [a-zA-Z0-9_] [a-zA-Z0-9_]
				
		//eg y = x+the number of house in the park
		//eg y = x+(the number of house in the park)
		
		bool wordIsNLPparsable = false;
		if(NLCpreprocessorSentenceClass.isStringNLPparsableWord(currentWord, true))
		{
			wordIsNLPparsable = true;	
		}
		if(currentWord == STRING_FULLSTOP)	//required because GIA preprocessor interprets STRING_FULLSTOP as a separate word
		{
			wordIsNLPparsable = true;
		}
		if(wordIsNLPparsable)
		{
			//cout << "wordIsNLPparsable" << endl;
			for(int i=0; i<currentWord.length(); i++)
			{
				bool legalWordCharacterFound = SHAREDvars.charInCharArray(currentWord[i], preprocessorMathNLPparsableCharacters, NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_CHARACTERS_NUMBER_OF_TYPES);
				if(!legalWordCharacterFound)
				{
					cerr << "splitMathDetectedLineIntoNLPparsablePhrases{} error: wordIsNLPparsable && !legalWordCharacterFound" << endl;
					exit(EXIT_ERROR);
				}
			}
		}
		
		//cout << "currentWord = " << currentWord << endl;
		//cout << "wordIsNLPparsable = " << wordIsNLPparsable << endl;

		bool logicalConditionOperatorInSentence = false;
		if((fullSentence->hasLogicalConditionOperator))
		{
			if(w < logicalConditionOperatorNumberWords)
			{
				logicalConditionOperatorInSentence = true;
			}
		}	
		
		bool finalWordInSentence = false;
		if(w == lineContents->size()-1)
		{
			finalWordInSentence = true;
		}
		
		bool firstWordInSentence = false;
		if(w == 0)
		{
			firstWordInSentence = true;
		}
		
		bool finalWordInSentenceAndWordIsNLPparsable = false;
		if(wordIsNLPparsable && finalWordInSentence)
		{
			finalWordInSentenceAndWordIsNLPparsable = true;
		}
	
		#ifdef NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_SUPPORT_ALPHANUMERIC_VARIABLE_NAMES_ONLY
		//this test needs to be reworked and inserted	
		if(!wordIsNLPparsable)
		{
			if(previousWordWasNLPparsable)
			{
				if(SHAREDvars.charInCharArray(currentWord[0], preprocessorMathNLPparsableNumericalCharacters, NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_NUMERICAL_CHARACTERS_NUMBER_OF_TYPES))
				{
					cerr << "splitMathDetectedLineIntoNLPparsablePhrases{}: user input error - variables names cannot start with numbers: " << currentWord << endl;
					exit(EXIT_ERROR);
				}
			}
		}
		#endif
		
		#ifdef NLC_PREPROCESSOR_MATH_DETECT_AND_DECLARE_IMPLICITLY_DECLARED_VARIABLES
		bool addMathTextVariable = false;
		if(!(fullSentence->hasLogicalConditionOperator))
		{
			if(findWordAtIndex(lineContents, w+1, SHAREDvars.convertCharToString(NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_SET_CHAR)))
			{				
				//mathText eg: "X=.." OR "X =.."
				//foundMathEqualsSetCommand = true;

				int variableTypeTemp = INT_DEFAULT_VALUE;
				string variableName = currentWord;
				if(!this->findPredefinedMathtextVariable(&currentWord, currentNLCfunctionInList, firstNLCfunctionInList, fullSentence, &variableTypeTemp))
				{//variable not detected in previous sentences (found first use of variable in current sentence)

					string variableTypeMathtext = "";
					int variableTypeObject = INT_DEFAULT_VALUE;

					if(w == 0)	//word comprises first mathText contents
					{//first word in mathText (type will automatically be assigned) (eg "X = ")

						#ifdef NLC_MATH_OBJECTS_ADVANCED
						vector<GIApreprocessorWord*> mathTextSubphraseContainingNLPparsablePhrase = GIApreprocessorMultiwordReductionClassObject.extractSubWordListInWordList(lineContents, 1);	//why not 2 (ie after = character)?
						int mathObjectVariableType = NLC_MATH_OBJECTS_VARIABLE_TYPE_UNKNOWN;

						for(int j=0; j<NLC_MATH_OBJECTS_VARIABLE_TYPE_BOOLEAN_OPERATORS_NUMBER_OF_TYPES; j++)
						{
							//OR: if(GIApreprocessorMultiwordReductionClassObject.findStringInWordList(&mathTextSubphraseContainingNLPparsablePhrase, mathObjectsVariableTypeBooleanOperators[j]) != CPP_STRING_FIND_RESULT_FAIL_VALUE)
							if(GIApreprocessorMultiwordReductionClassObject.findSubstringAtStartOfWordInWordList(&mathTextSubphraseContainingNLPparsablePhrase, mathObjectsVariableTypeBooleanOperators[j]))
							{
								mathObjectVariableType = NLC_MATH_OBJECTS_VARIABLE_TYPE_BOOLEAN;
							}
						}

						for(int j=0; j<NLC_MATH_OBJECTS_VARIABLE_TYPE_NUMERICAL_OPERATORS_NUMBER_OF_TYPES; j++)
						{
							if(GIApreprocessorMultiwordReductionClassObject.findSubstringAtStartOfWordInWordList(&mathTextSubphraseContainingNLPparsablePhrase, mathObjectsVariableTypeNumericalOperators[j]))
							{
								mathObjectVariableType = NLC_MATH_OBJECTS_VARIABLE_TYPE_NUMERICAL;
							}
							if(GIApreprocessorMultiwordReductionClassObject.findSimpleSubstringInWordList(&mathTextSubphraseContainingNLPparsablePhrase, mathObjectsVariableTypeNumericalOperators[j]))
							{
								mathObjectVariableType = NLC_MATH_OBJECTS_VARIABLE_TYPE_NUMERICAL;
							}
						}

						for(int j=0; j<NLC_MATH_OBJECTS_VARIABLE_TYPE_STRING_OPERATORS_NUMBER_OF_TYPES; j++)
						{
							if(GIApreprocessorMultiwordReductionClassObject.findSubstringAtStartOfWordInWordList(&mathTextSubphraseContainingNLPparsablePhrase, mathObjectsVariableTypeStringOperators[j]))
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
							cerr << "splitMathDetectedLineIntoNLPparsablePhrases{} error: implicitly declared mathText variable and variable type cannot be statically detected based on line contents" << endl;
							exit(EXIT_ERROR);
						}
						#else
						variableTypeMathtext = NLC_PREPROCESSOR_MATH_MATHTEXT_VARIABLE_TYPE_NUMERICAL;
						variableTypeObject = NLC_MATH_OBJECTS_VARIABLE_TYPE_NUMERICAL;
						#endif

						//NB considering the current phrase contains an equal sign it will be classified as mathText, not an nlp parsable phrase
						//#ifdef NLC_DEBUG_PREPROCESSOR_MATH_DETECT_AND_DECLARE_UNDECLARED_VARIABLES
						cout << "implicitly declared mathText variable detected: declaring " << variableTypeMathtext << " " << currentWord << endl;	//inserting mathText variable declaration type (eg double)
						//#endif
						GIApreprocessorMultiwordReductionClassObject.insertStringIntoWordList(&currentPhrase, variableTypeMathtext, 0);
						//cout << " currentPhrase = " << GIApreprocessorMultiwordReductionClassObject.generateTextFromVectorWordList(&currentPhrase) << endl;

						newlyDeclaredVariable = currentWord;
						addMathTextVariable = true;
					}
					else
					{//explicit type may have been provided (mathText eg: "int X = ")
						bool explictTypeFound = false;
						for(int j=0; j<NLC_PREPROCESSOR_MATH_MATHTEXT_VARIABLES_NUMBER_OF_TYPES; j++)
						{
							#ifdef NLC_PREPROCESSOR_MATH_SUPPORT_USER_VARIABLE_TYPE_DECLARATIONS
							int indexOfType = GIApreprocessorMultiwordReductionClassObject.findStringInWordList(lineContents, preprocessorMathMathTextVariables[j]);
							#else
							int indexOfType = GIApreprocessorMultiwordReductionClassObject.findStringInWordList(lineContents, preprocessorMathNaturalLanguageVariables[j]);
							#endif
							if((indexOfType != CPP_STRING_FIND_RESULT_FAIL_VALUE) && (indexOfType < w))	//e.g. variableType(w-1) variableName(w) =(w+1)
							{
								explictTypeFound = true;

								newlyDeclaredVariable = currentWord;
								variableTypeObject = preprocessorMathTextVariableMathObjectTypes[j];
								addMathTextVariable = true;
								
								//cout << "explicitly declared mathText variable detected: declaring " << preprocessorMathNaturalLanguageVariables[j] << " " << currentWord << endl;
							}
						}
					}

					if(addMathTextVariable)
					{
						//cout << "addNewMathTextVariable; variableName = " << variableName << endl;
						this->addNewMathTextVariable(fullSentence, variableName, variableTypeObject);
					}

				}
				#ifdef NLC_PREPROCESSOR_MATH_FIX_BUG_ADD_MATH_TEXT_VARIABLES_DUPLICATES
				else
				{
					//cout << "addNewMathTextVariable; variableName = " << variableName << endl;
					this->addNewMathTextVariable(fullSentence, variableName, variableTypeTemp);
				}
				#endif
			}
		}
		#endif

		if(logicalConditionOperatorInSentence)
		{
			mathText = mathText + GIApreprocessorMultiwordReductionClassObject.generateTextFromPreprocessorSentenceWord(currentWordTag, false, firstWordInSentence);
			currentPhrase.clear();
		}
		else
		{
			if(!wordIsNLPparsable || finalWordInSentenceAndWordIsNLPparsable)
			{
				//cout << "(!wordIsNLPparsable || finalWordInSentenceAndWordIsNLPparsable)" << endl;

				if(finalWordInSentenceAndWordIsNLPparsable)
				{
					if(!addMathTextVariable)	//CHECKTHIS - is this check required?
					{
						addNewMathTextVariable(fullSentence, currentWord, NLC_MATH_OBJECTS_VARIABLE_TYPE_UNKNOWN);
						currentPhrase.push_back(currentWordTag);
						wordIndex++;
					}
				}
					
				//currentWord is either a mathText variable name or part of an NLP parsable phrase (c is a space or comma)
				if(wordIndex >= NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_MIN_NUMBER_WORDS)
				{
					//cout << "(wordIndex >= NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_MIN_NUMBER_WORDS)" << endl;

					//CHECKTHIS; //remove all mathTextVariable nlp parsable phrase (as an NLP parsable phrase does not contain mathText variable names, or if it does the mathText variable are references to predefined mathText variables and will be detected later)
					for(int i=0; i<currentPhrase.size(); i++)
					{
						//cout << "removing mathText variable: " << fullSentence->mathTextVariables.back()->name << endl;
						this->removeLastMathTextVariable(fullSentence);
					}

					//split sentence and add phrase
					currentParsablePhraseInList->mathTextNLPparsablePhraseIndex = phraseIndex;
					#ifdef NLC_PREPROCESSOR_RECORD_PARSABLE_PHRASE_POSITION_APPROXIMATE
					currentParsablePhraseInList->mathTextNLPparsablePhrasePositionApproximate = w - currentPhrase.size();	//CHECKTHIS
					#endif

					bool lastWordOfPhraseIsFullStop = false;
					if(currentWord == SHAREDvars.convertCharToString(NLC_PREPROCESSOR_END_OF_SENTENCE_CHAR))
					{
						lastWordOfPhraseIsFullStop = true;
					}
					#ifdef NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_SUPPORT_INTRAWORD_PUNCTUATION_MARK
					if(!lastWordOfPhraseIsFullStop)
					{
					#endif
						GIApreprocessorMultiwordReductionClassObject.addStringToWordList(&currentPhrase, SHAREDvars.convertCharToString(NLC_PREPROCESSOR_END_OF_SENTENCE_CHAR));	//append a fullstop to the NLP parsable phrase to make it readable by NLP
					#ifdef NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_SUPPORT_INTRAWORD_PUNCTUATION_MARK
					}
					#endif

					currentParsablePhraseInList->sentenceContents = currentPhrase;
					currentParsablePhraseInList->sentenceIndex = *sentenceIndex;
					
					string spaceTextBefore = "";
					#ifdef NLC_PREPROCESSOR_MATH_MAINTAIN_CONSISTENT_WHITESPACE_FOR_BRACKETS_IN_MATHTEXT
					determineSpacingForAppendingMathTextNLPparsablePhrase(&mathText, currentWord, &spaceTextBefore);
					/*
					cout << "currentWord = " << currentWord << endl;
					cout << "w = " << w << endl;
					cout << "wordIndex = " << wordIndex << endl;
					*/
					if(w == wordIndex)
					{
						spaceTextBefore = "";	//effective firstWordInSentence
					}
					#endif
					mathText = mathText + spaceTextBefore + NLCpreprocessorSentenceClass.generateMathTextNLPparsablePhraseReference(sentenceIndexOfFullSentence, currentParsablePhraseInList);
					
					if(!finalWordInSentenceAndWordIsNLPparsable)
					{
						#ifdef NLC_PREPROCESSOR_MATH_MAINTAIN_CONSISTENT_WHITESPACE_FOR_BRACKETS_IN_MATHTEXT
						spaceTextBefore = "";
						determineSpacingForAppendingMathText(&mathText, currentWord, &spaceTextBefore, previousWordWasLogicalConditionOperator);
						#endif
						bool prependWhiteSpace = false;
						if(!firstWordInSentence)
						{
							#ifdef NLC_PREPROCESSOR_MATH_MAINTAIN_CONSISTENT_WHITESPACE_FOR_BRACKETS_IN_MATHTEXT
							if(spaceTextBefore == STRING_SPACE)
							{
							#endif
								prependWhiteSpace = true;
							#ifdef NLC_PREPROCESSOR_MATH_MAINTAIN_CONSISTENT_WHITESPACE_FOR_BRACKETS_IN_MATHTEXT
							}
							#endif
						}

						mathText = mathText + GIApreprocessorMultiwordReductionClassObject.generateTextFromPreprocessorSentenceWord(currentWordTag, false, !prependWhiteSpace);
					}
					
					#ifndef NLC_PREPROCESSOR_MATH_MAINTAIN_CONSISTENT_WHITESPACE_FOR_BRACKETS_IN_MATHTEXT
					#ifdef NLC_PREPROCESSOR_MATH_USE_HUMAN_READABLE_VARIABLE_NAMES
					//readd the final space to the mathText since it has been removed from the nlp parsable phrase
					mathText = mathText + CHAR_SPACE;
					#endif
					#endif

					currentParsablePhraseInList->next = new NLCpreprocessorParsablePhrase();
					currentParsablePhraseInList = currentParsablePhraseInList->next;
					(*sentenceIndex) = (*sentenceIndex) + 1;
					phraseIndex++;
				}
				else
				{
					//currentWord is a mathText variable name (c is likely a mathematical operator)
					if(!finalWordInSentenceAndWordIsNLPparsable)
					{
						currentPhrase.push_back(currentWordTag);	//add previous words in the failed NLP parsable phrase (if existent) and the currentWord to the mathText
					}
										
					//added 2b3g;
					//cout << "mathText = mathText + " <<  GIApreprocessorMultiwordReductionClassObject.generateTextFromVectorWordList(&currentPhrase) << endl;
					string spaceTextBefore = "";
					string spaceTextAfter = "";
					
					#ifdef NLC_PREPROCESSOR_MATH_MAINTAIN_CONSISTENT_WHITESPACE_FOR_BRACKETS_IN_MATHTEXT
					determineSpacingForAppendingMathText(&mathText, currentWord, &spaceTextBefore, previousWordWasLogicalConditionOperator);	
					#else
					#ifdef NLC_PREPROCESSOR_MATH_SUPPORT_USER_VARIABLE_TYPE_DECLARATIONS
					bool isMathTextVariableType = SHAREDvars.textInTextArray(currentWord, preprocessorMathMathTextVariables, NLC_PREPROCESSOR_MATH_MATHTEXT_VARIABLES_NUMBER_OF_TYPES);
					#else
					bool isMathTextVariableType = SHAREDvars.textInTextArray(currentWord, preprocessorMathNaturalLanguageVariables, NLC_PREPROCESSOR_MATH_MATHTEXT_VARIABLES_NUMBER_OF_TYPES);
					#endif
					if(isMathTextVariableType)
					{
						*spaceTextAfter = STRING_SPACE;
					}	
					#endif
					
					mathText = mathText + spaceTextBefore + GIApreprocessorMultiwordReductionClassObject.generateTextFromVectorWordList(&currentPhrase) + spaceTextAfter;
				}

				currentPhrase.clear();	//restart phrase (assuming it contains text)
				wordIndex = 0;
			}
			else if(wordIsNLPparsable)
			{
				currentPhrase.push_back(currentWordTag);	//add the nlpParsable word to the currentPhrase
				if(!addMathTextVariable)
				{
					//cout << "addNewMathTextVariable; currentWord = " << currentWord << endl;
					addNewMathTextVariable(fullSentence, currentWord, NLC_MATH_OBJECTS_VARIABLE_TYPE_UNKNOWN);
				}
				wordIndex++;
			}
		}
		
		previousWordWasLogicalConditionOperator = logicalConditionOperatorInSentence;
		previousWordWasNLPparsable = wordIsNLPparsable;
	}
	

	//now write the full mathText to each sub sentence (NLP parsable phrase) - required for NLC to regenerate the correct math and variable definitions (based on NLP parsable phrases)
	fullSentence->isMath = true;
	fullSentence->mathTextNLPparsablePhraseTotal = phraseIndex;
	fullSentence->mathText = mathText;
	#ifdef NLC_PREPROCESSOR_DEBUG
	cout << "fullSentence->mathText = " << fullSentence->mathText << endl;
	#endif
	fullSentence->indentation = currentIndentation;
	if(fullSentence->mathTextNLPparsablePhraseTotal == 0)
	{
		//add dummy phrase for NLP to parse (will not be used by NLC; create NLP/GIA sentence as a filler for math text replacement only)
		GIApreprocessorMultiwordReductionClassObject.addStringArrayToWordList((&currentParsablePhraseInList->sentenceContents), preprocessorMathNLPparsablePhraseDummyWordArray, NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_DUMMY_NUMBER_OF_WORDS);
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
						cerr << "NLC_MATH_OBJECTS_ADVANCED_INFER_TYPE_BASED_ON_PREVIOUSLY_DECLARED_MATHTEXT_VARIABLES: splitMathDetectedLineIntoNLPparsablePhrases{} error: first instance of mathText variable type in function == NLC_MATH_OBJECTS_VARIABLE_TYPE_UNKNOWN" << endl;
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
						//cout << "findPredefinedMathtextVariable: mathTextVariable->type = " << mathTextVariable->type << endl;
					}
					#endif
				}
				else
				{
					if(!ignoreVariable)
					{
						cerr << "splitMathDetectedLineIntoNLPparsablePhrases{} error: mathText variable " << mathTextVariableName << " is undeclared" << endl;
						//cerr << "lineContents = " <<* lineContents << endl;
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

	(*currentNLCsentenceInList)->next = new NLCpreprocessorSentence();
	(*currentNLCsentenceInList) = (*currentNLCsentenceInList)->next;
					
	return result;
}

#ifdef NLC_PREPROCESSOR_MATH_MAINTAIN_CONSISTENT_WHITESPACE_FOR_BRACKETS_IN_MATHTEXT
void NLCpreprocessorMathClass::determineSpacingForAppendingMathText(const string* mathText, const string currentWord, string* spaceTextBefore, const bool previousWordWasLogicalConditionOperator)
{
	*spaceTextBefore = "";
	
	//when generating mathtext from word lists parse brackets specially. For right/closing brackets don't prepend white space, left/opening brackets; don't prepend white space if previous character is an opening bracket. For normal words don't prepend white space if previous character is an opening bracket).
	//see nlpMathCharacterUngroupedArray for why this is safe to do for CHAR_OPEN_BRACKET and CHAR_CLOSE_BRACKET
	if(mathText->length() >= 1)
	{
		bool previousCharacterIsOpeningBracketOrExclamationMark = false;
		char previousCharacterInMathtext = (*mathText)[mathText->length()-1];
		if(previousCharacterInMathtext == NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_OPEN_BRACKET)
		{
			previousCharacterIsOpeningBracketOrExclamationMark = true;
		}
		if(previousCharacterInMathtext == NLC_PREPROCESSOR_MATH_OPERATOR_NEGATIVE_CHAR)
		{
			previousCharacterIsOpeningBracketOrExclamationMark = true;
		}
		if(currentWord == SHAREDvars.convertCharToString(NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_CLOSE_BRACKET))
		{
			*spaceTextBefore = "";
		}
		else //if(currentWord == SHAREDvars.convertCharToString(CHAR_OPEN_BRACKET))
		{
			if(previousCharacterIsOpeningBracketOrExclamationMark)
			{
				*spaceTextBefore = "";
			}
			else
			{
				if(!previousWordWasLogicalConditionOperator)
				{
					*spaceTextBefore = STRING_SPACE;
				}
			}	
		}
	}
}

void NLCpreprocessorMathClass::determineSpacingForAppendingMathTextNLPparsablePhrase(const string* mathText, const string currentWord, string* spaceTextBefore)
{
	*spaceTextBefore = "";
									
	//when generating mathtext from word lists parse brackets specially. For normal words don't prepend white space if previous character is an opening bracket).
	//see nlpMathCharacterUngroupedArray for why this is safe to do for CHAR_OPEN_BRACKET and CHAR_CLOSE_BRACKET
	bool previousCharacterIsOpeningBracketOrExclamationMark = false;
	if(mathText->length() >= 1)
	{
		char previousCharacterInMathtext = (*mathText)[mathText->length()-1];
		if(previousCharacterInMathtext == NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_OPEN_BRACKET)
		{
			previousCharacterIsOpeningBracketOrExclamationMark = true;
		}
		if(previousCharacterInMathtext == NLC_PREPROCESSOR_MATH_OPERATOR_NEGATIVE_CHAR)
		{
			previousCharacterIsOpeningBracketOrExclamationMark = true;
		}
	}	
	if(previousCharacterIsOpeningBracketOrExclamationMark)
	{
		*spaceTextBefore = "";
	}
	else
	{
		*spaceTextBefore = CHAR_SPACE;
	}
}
#endif


bool NLCpreprocessorMathClass::findCharacterAtIndexOrAfterSpace(const string* lineContents, const int i, const char characterToFind, int* indexOfCharacterFound)
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
	
bool NLCpreprocessorMathClass::findWordAtIndex(const vector<GIApreprocessorWord*>* wordList, const int index, const string wordToFind)
{
	bool result = false;
	if(index < wordList->size())
	{
		if((*wordList)[index]->tagName == wordToFind)
		{
			result = true;
		}
	}	
	
	return result;
}


#ifdef NLC_PREPROCESSOR_MATH_SUPPORT_USER_VARIABLE_TYPE_DECLARATIONS
bool NLCpreprocessorMathClass::replaceExplicitVariableTypesWithNLPparsablePhraseIllegalWords(vector<GIApreprocessorWord*>* lineContents)
{
	bool result = false;
	//replaceExplicitVariableTypesWithNLPparsablePhraseIllegalWords() is required to prevent creation of nlp parsable phrase from 2 word variable declarations
	if(lineContents->size() >= 1)
	{
		for(int i=0; i<NLC_PREPROCESSOR_MATH_MATHTEXT_VARIABLES_NUMBER_OF_TYPES; i++)
		{
			if((*lineContents)[0]->tagName == preprocessorMathNaturalLanguageVariables[i])
			{
				result = true;
				(*lineContents)[0]->tagName = preprocessorMathMathTextVariables[i];	//NB this is type sensitive; could be changed in the future
			}
		}
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

bool NLCpreprocessorMathClass::replaceNumericalVariablesWithDummyNumberIfNecessary(vector<GIApreprocessorWord*>* lineContents, NLCpreprocessorSentence* currentNLCsentenceInList, NLCfunction* currentNLCfunctionInList, const NLCfunction* firstNLCfunctionInList)
{
	bool result = true;

	for(int w = 0; w < lineContents->size(); w++)
	{
		string currentWord = (*lineContents)[w]->tagName;
		int variableTypeTemp = INT_DEFAULT_VALUE;
		if(this->findPredefinedMathtextVariable(&currentWord, currentNLCfunctionInList, firstNLCfunctionInList, NULL, &variableTypeTemp))	//pass firstNLCfunctionInList and update this->findPredefinedMathtextVariable() accordingly to allow global numerical variable definitions; not just local numerical variable definitions
		{
			if(variableTypeTemp == NLC_MATH_OBJECTS_VARIABLE_TYPE_NUMERICAL)	//CHECKTHIS: is this required?
			{
				//replace the variable name with a dummy number
				currentNLCsentenceInList->variableNamesDetected.push_back(currentWord);
				int dummyNumber = NLCpreprocessorSentenceClass.generateDummyNumber(currentNLCsentenceInList->variableNamesDetected.size());
				string dummyNumberString = SHAREDvars.convertIntToString(dummyNumber);
				(*lineContents)[w]->tagName = dummyNumberString;
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




