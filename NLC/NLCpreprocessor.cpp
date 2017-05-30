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
 * File Name: NLCpreprocessor.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2017 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 2b2b 21-May-2017
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/


#include "NLCpreprocessor.hpp"

//#include "NLCprintDefs.hpp" //required for progLangOpenParameterSpace

#ifdef NLC_PREPROCESSOR

bool NLCpreprocessorClass::preprocessTextForNLC(const string inputFileName, NLCfunction* firstNLCfunctionInList, bool* detectedFunctions, int* numberOfInputFilesInList, vector<string>* inputTextFileNameList, const string outputFileName)
{
	*numberOfInputFilesInList = 0;

	#ifdef NLC_PREPROCESSOR_PRINT_OUTPUT
	string inputFileText = "";
	string outputFileText = "";
	#endif
	
	bool result = true;
	ifstream parseFileObject(inputFileName.c_str());
	if(!parseFileObject.rdbuf()->is_open())
	{
		//txt file does not exist in current directory.
		cout << "Error: NLC input file does not exist in current directory: " << inputFileName << endl;
		result = false;
	}
	else
	{
		SHAREDvars.setCurrentDirectory(outputFolder);	//save output files to output folder

		NLCfunction* currentNLCfunctionInList = firstNLCfunctionInList;
		NLCpreprocessorSentence* currentNLCsentenceInList = currentNLCfunctionInList->firstNLCsentenceInFunction;
		string currentLine;
		int sentenceIndex = GIA_NLP_START_SENTENCE_INDEX;
		*detectedFunctions = false;
		string functionContents = "";
		string NLCfunctionName = "";
		string functionFileName = "";	//with NLCfunctionName with extension
		int currentLineNumber = 0;

		while(getline(parseFileObject, currentLine))
		{
			#ifdef NLC_PREPROCESSOR_PRINT_OUTPUT
			inputFileText = inputFileText + currentLine + CHAR_NEWLINE;
			#endif

			currentLineNumber++;

			#ifndef NLC_MATH_OBJECTS_ADVANCED
			#ifdef NLC_PREPROCESSOR_REDUCE_QUOTES_TO_SINGLE_WORDS
			string updatedLineTextWithQuotationsReducedToSingleWords = "";
			if(this->reduceQuotesToSingleWords(currentLine, &updatedLineTextWithQuotationsReducedToSingleWords))
			{
				currentLine = updatedLineTextWithQuotationsReducedToSingleWords;
			}
			#endif
			#endif

			#ifdef NLC_INPUT_FUNCTION_LISTS_PREPROCESSOR
			if(this->detectFunctionHeader(&currentLine))
			{
				//extract functions from file and generate separate files
				if(*detectedFunctions)
				{
					//create new function file based on current text
					SHAREDvars.writeStringToFile(functionFileName, &functionContents);
					currentNLCfunctionInList->NLCfunctionName = NLCfunctionName;
					currentNLCfunctionInList->next = new NLCfunction();
					currentNLCfunctionInList = currentNLCfunctionInList->next;
					currentNLCsentenceInList = currentNLCfunctionInList->firstNLCsentenceInFunction;
					*numberOfInputFilesInList = *numberOfInputFilesInList+1;
				}
				else
				{
					*detectedFunctions = true;
				}
				sentenceIndex = GIA_NLP_START_SENTENCE_INDEX;
				NLCfunctionName = this->getFunctionNameFromFunctionHeader(&currentLine);		//NLCfunctionName
				functionFileName = this->generateNLCfunctionFileName(NLCfunctionName);
				inputTextFileNameList->push_back(functionFileName);
				functionContents = "";
			}
			else
			{
			#endif
				int currentIndentation = 0;
				string lineContents = "";
				string indentationContents = "";
				this->extractIndentationFromCurrentLine(&currentLine, &currentIndentation, &lineContents, &indentationContents);	//this will remove the indentation from the current line

				#ifdef NLC_PREPROCESSOR_GENERATE_COMMENTS
				currentNLCsentenceInList->sentenceOriginal = lineContents;	//sentenceOriginal is stored for both isMath and !isMath (sentenceContentsOriginal is only stored for !isMath)
				#endif

				#ifdef NLC_PREPROCESSOR_MATH

				int lineLogicalConditionOperator;
				if(this->detectLogicalConditionOperatorAtStartOfLine(&lineContents, &lineLogicalConditionOperator))
				{
					currentNLCsentenceInList->hasLogicalConditionOperator = true;
					#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
					currentNLCsentenceInList->logicalConditionOperator = lineLogicalConditionOperator;
					currentNLCsentenceInList->isMath = true;
					#endif
				}
				else
				{
					if(NLCpreprocessorMath.detectMathSymbolsInLine(&lineContents))
					{
						currentNLCsentenceInList->isMath = true;
					}

					//#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
					if(NLCpreprocessorMath.detectAndReplaceIsEqualToNonLogicalConditionTextWithSymbol(&lineContents, currentNLCsentenceInList->hasLogicalConditionOperator, currentNLCsentenceInList->isMath))
					{
						currentNLCsentenceInList->isMath = true;
					}
					//#endif
				}

				if(currentNLCsentenceInList->isMath)
				{
					#ifdef NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
					bool detectedLogicalConditionCommand = false;
					NLCpreprocessorSentence* firstSentenceInLogicalConditionCommandTemp = new NLCpreprocessorSentence();
					if(currentNLCsentenceInList->hasLogicalConditionOperator)
					{
						NLCpreprocessorMath.splitMathDetectedLineLogicalConditionCommandIntoSeparateSentences(&lineContents, currentIndentation, currentNLCsentenceInList, firstSentenceInLogicalConditionCommandTemp, &detectedLogicalConditionCommand);
					}
					#endif

					NLCpreprocessorMath.splitMathDetectedLineIntoNLPparsablePhrases(&lineContents, &currentNLCsentenceInList, &sentenceIndex, currentIndentation, &functionContents, currentNLCfunctionInList, firstNLCfunctionInList);

					#ifdef NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
					if(detectedLogicalConditionCommand)
					{
						NLCpreprocessorSentence* currentSentenceInLogicalConditionCommandTemp = firstSentenceInLogicalConditionCommandTemp;
						while(currentSentenceInLogicalConditionCommandTemp->next != NULL)
						{
							#ifdef NLC_PREPROCESSOR_GENERATE_COMMENTS
							currentSentenceInLogicalConditionCommandTemp->sentenceOriginal = currentSentenceInLogicalConditionCommandTemp->firstNLPparsablePhraseInList->sentenceContents;
							#endif
							
							if(NLCpreprocessorMath.detectMathSymbolsInLine(&(currentSentenceInLogicalConditionCommandTemp->firstNLPparsablePhraseInList->sentenceContents)))
							{
								NLCpreprocessorMath.splitMathDetectedLineIntoNLPparsablePhrases(&(currentSentenceInLogicalConditionCommandTemp->firstNLPparsablePhraseInList->sentenceContents), &currentNLCsentenceInList, &sentenceIndex, currentSentenceInLogicalConditionCommandTemp->indentation, &functionContents, currentNLCfunctionInList, firstNLCfunctionInList);
							}
							else
							{
								#ifdef NLC_PREPROCESSOR_GENERATE_COMMENTS
								currentSentenceInLogicalConditionCommandTemp->sentenceContentsOriginal = this->removePrependingWhiteSpace(currentSentenceInLogicalConditionCommandTemp->firstNLPparsablePhraseInList->sentenceContents);
								#endif
								
								this->addNonLogicalConditionSentenceToList(&(currentSentenceInLogicalConditionCommandTemp->firstNLPparsablePhraseInList->sentenceContents), &currentNLCsentenceInList, &sentenceIndex,  currentSentenceInLogicalConditionCommandTemp->indentation, currentNLCfunctionInList, firstNLCfunctionInList);
								//cout << "currentSentenceInLogicalConditionCommandTemp->indentation = " << currentSentenceInLogicalConditionCommandTemp->indentation << endl;
								functionContents = functionContents + indentationContents + NLC_PREPROCESSOR_INDENTATION_CHAR + (currentSentenceInLogicalConditionCommandTemp->firstNLPparsablePhraseInList->sentenceContents) + CHAR_NEWLINE;
							}
							currentSentenceInLogicalConditionCommandTemp = currentSentenceInLogicalConditionCommandTemp->next;
						}
					}
					#endif
				}
				else
				{
				#endif

					//now for each sentence on line:
					int startOfSentenceIndex = 0;
					bool stillSentenceToParseOnLine = true;
					while(stillSentenceToParseOnLine)
					{
						bool lineFullStopDetected = false;
						#ifdef NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_SUPPORT_INTRAWORD_PUNCTUATION_MARK
						int startOfSentenceIndexNew = startOfSentenceIndex;
						bool stillFinding = true;
						while(stillFinding)
						{
							startOfSentenceIndexNew = lineContents.find(NLC_PREPROCESSOR_END_OF_SENTENCE_CHAR, startOfSentenceIndexNew);
							if(startOfSentenceIndexNew != CPP_STRING_FIND_RESULT_FAIL_VALUE)
							{
								//based on isIntrawordFullStop() code:
								if(GIApreprocessorMultiwordReduction.isIntrawordPunctuationMark(startOfSentenceIndexNew, &lineContents))
								{
									//cout << "isIntrawordPunctuationMark" << endl;
									startOfSentenceIndexNew = startOfSentenceIndexNew+1;
								}
								else
								{
									lineFullStopDetected = true;
									stillFinding = false;
								}
							}
							else
							{
								stillFinding = false;
							}
						}
						#else
						int startOfSentenceIndexNew = lineContents.find(NLC_PREPROCESSOR_END_OF_SENTENCE_CHAR, startOfSentenceIndex);
						if(startOfSentenceIndexNew != CPP_STRING_FIND_RESULT_FAIL_VALUE)
						{
							lineFullStopDetected = true;

						}
						#endif
						if(!lineFullStopDetected)	//look for question mark instead
						{
							startOfSentenceIndexNew = lineContents.find(NLC_PREPROCESSOR_END_OF_SENTENCE_QUESTION_CHAR, startOfSentenceIndex);	//NB '.' and '?' are currently supported as sentence delimiters
							if(startOfSentenceIndexNew != CPP_STRING_FIND_RESULT_FAIL_VALUE)
							{
								lineFullStopDetected = true;
							}
						}

						string sentenceContents = "";
						if(lineFullStopDetected)
						{
							sentenceContents = lineContents.substr(startOfSentenceIndex, startOfSentenceIndexNew-startOfSentenceIndex+1);	//+1 append the full stop

						}
						else
						{
							sentenceContents = lineContents.substr(startOfSentenceIndex, lineContents.length());

						}
						
						currentNLCsentenceInList->sentenceContentsOriginal = this->removePrependingWhiteSpace(sentenceContents);

						//error checking only:
						int sentenceLogicalConditionOperator;
						if(this->detectLogicalConditionOperatorAtStartOfLine(&sentenceContents, &sentenceLogicalConditionOperator))
						{
							cout << "preprocessTextForNLC{} error: !(currentNLCsentenceInList->isMath) && detectLogicalConditionOperatorAtStartOfLine" << endl;
						}

						if(!lineFullStopDetected)
						{
							//if !lineFullStopDetected, the line has to be all white space
							
							stillSentenceToParseOnLine = false;

							bool nonWhiteSpaceDetectedBetweenFinalFullStopAndEndOfLine = false;
							for(int i=startOfSentenceIndex; i<sentenceContents.length(); i++)
							{
								char c = sentenceContents[i];
								if(!SHAREDvars.isWhiteSpace(c))
								{
									nonWhiteSpaceDetectedBetweenFinalFullStopAndEndOfLine = true;
								}
							}
							
							if(!lineFullStopDetected && nonWhiteSpaceDetectedBetweenFinalFullStopAndEndOfLine)
							{
								cout << "NLC_PREPROCESSOR preprocessTextForNLC{} error: NLC_PREPROCESSOR_SUPPORT_MULTILINE_SENTENCES are not currently supported" << endl;
								cout << "sentenceContents = " << sentenceContents << endl;
								exit(EXIT_ERROR);
							}
							else
							{//!lineFullStopDetected && !nonWhiteSpaceDetectedBetweenFinalFullStopAndEndOfLine
								//assume that a sentence has already been created based on a full stop (do not support multiline sentences)
								//redundant white space will be culled from functionContents
							}
						}
						else
						{
							this->addNonLogicalConditionSentenceToList(&sentenceContents, &currentNLCsentenceInList, &sentenceIndex, currentIndentation, currentNLCfunctionInList, firstNLCfunctionInList);

							if(startOfSentenceIndexNew == lineContents.length()-1)
							{
								stillSentenceToParseOnLine = false;
							}
						}
						functionContents = functionContents + indentationContents + sentenceContents + CHAR_NEWLINE;
						startOfSentenceIndex = startOfSentenceIndexNew + 1;	//is +1 required? (to prevent current NLC_PREPROCESSOR_END_OF_SENTENCE_CHAR/CHAR_FULLSTOP from being redetected)
					}


				#ifdef NLC_PREPROCESSOR_MATH
				}
				#endif

			#ifdef NLC_INPUT_FUNCTION_LISTS_PREPROCESSOR
			}
			#endif
		}

		#ifdef NLC_INPUT_FUNCTION_LISTS_PREPROCESSOR
		if(*detectedFunctions)
		{
			//create a final function based on the final text..
			#ifdef NLC_PREPROCESSOR_PRINT_OUTPUT
			cout << "create new function, functionFileName = " << functionFileName << endl;
			cout << "functionContents = " << functionContents << endl;
			#endif
			SHAREDvars.writeStringToFile(functionFileName, &functionContents);
			currentNLCfunctionInList->NLCfunctionName = NLCfunctionName;
			currentNLCfunctionInList->next = new NLCfunction();
			currentNLCfunctionInList = currentNLCfunctionInList->next;
			currentNLCsentenceInList = currentNLCfunctionInList->firstNLCsentenceInFunction;
			*numberOfInputFilesInList = *numberOfInputFilesInList+1;
		}
		else
		{
		#endif
			#ifdef NLC_PREPROCESSOR_PRINT_OUTPUT
			cout << "create preprocessed file, outputFileName = " << outputFileName << endl;
			cout  << "functionContents = \n" << functionContents << endl;
			#endif
			#ifdef NLC_PREPROCESSOR_PRINT_OUTPUT
			outputFileText = functionContents;
			#endif
			SHAREDvars.writeStringToFile(outputFileName, &functionContents);
			*numberOfInputFilesInList = *numberOfInputFilesInList+1;
		#ifdef NLC_INPUT_FUNCTION_LISTS_PREPROCESSOR
		}
		#endif
		
		

		SHAREDvars.setCurrentDirectory(inputFolder);	//set current directory back to the original inputFolder (this is required for both NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS and GIA, even if the GIA's inputFolder is changed to outputFolder as it should be in the case of NLC preprocessed input)
	}

	/*
	#ifdef NLC_PREPROCESSOR_PRINT_OUTPUT
	NLCpreprocessorSentence* currentNLCsentenceInList = firstNLCfunctionInList->firstNLCsentenceInFunction;
	while(currentNLCsentenceInList->next != NULL)
	{
		for(int i=0;i<currentNLCsentenceInList->indentation; i++)
		{
			cout << "\t";
		}
		cout << currentNLCsentenceInList->->firstNLPparsablePhraseInList->sentenceContents;
		cout << "(sentenceIndex: " << currentNLCsentenceInList->firstNLPparsablePhraseInList->sentenceIndex << ") ";
		if(currentNLCsentenceInList->isMath)
		{
			cout << " (mathText: " << currentNLCsentenceInList->mathText << ")" << endl;
		}
		else
		{
			cout << endl;
		}
		currentNLCsentenceInList = currentNLCsentenceInList->next;
	}
	#endif
	*/

	#ifdef NLC_PREPROCESSOR_PRINT_OUTPUT
	cout << "inputFileText = \n" << inputFileText << endl;
	cout << "outputFileText = \n" << outputFileText << endl;
	cout << "NLCpreprocessorSentences = " << endl;
	NLCpreprocessorSentence* currentSentence = firstNLCfunctionInList->firstNLCsentenceInFunction;
	while(currentSentence->next != NULL)
	{
		cout << "" << endl;
		cout << "currentSentence->indentation = " << currentSentence->indentation << endl;
		cout << "currentSentence->hasLogicalConditionOperator = " << currentSentence->hasLogicalConditionOperator << endl;
		cout << "currentSentence->logicalConditionOperator = " << currentSentence->logicalConditionOperator << endl;
		cout << "currentSentence->isMath = " << currentSentence->isMath << endl;
		cout << "currentSentence->mathText = " << currentSentence->mathText << endl;
		cout << "currentSentence->mathTextNLPparsablePhraseTotal = " << currentSentence->mathTextNLPparsablePhraseTotal << endl;
		for(int i=0; i< currentSentence->mathTextVariables.size(); i++)
		{
			cout << " currentSentence->mathTextVariables[" << i << "]->name = " << currentSentence->mathTextVariables[i]->name << endl;
		}
		for(int i=0; i< currentSentence->variableNamesDetected.size(); i++)
		{
			cout << " currentSentence->variableNamesDetected[" << i << "] = " << currentSentence->variableNamesDetected[i] << endl;
		}
		cout << "currentSentence->mathTextIdentifiesMathValue = " << currentSentence->mathTextIdentifiesMathValue << endl;
		cout << "currentSentence->sentenceOriginal = " << currentSentence->sentenceOriginal << endl;
		cout << "currentSentence->sentenceContentsOriginal = " << currentSentence->sentenceContentsOriginal << endl;
		//cout << "currentSentence->singleWordSentenceActionName = " << currentSentence->singleWordSentenceActionName << endl;


		NLCpreprocessorParsablePhrase* currentParsablePhrase = currentSentence->firstNLPparsablePhraseInList;
		while(currentParsablePhrase->next != NULL)
		{	
			cout << "\tcurrentParsablePhrase->sentenceContents = " << currentParsablePhrase->sentenceContents << endl;
			cout << "\tcurrentParsablePhrase->sentenceIndex = " << currentParsablePhrase->sentenceIndex << endl;
			cout << "\tcurrentParsablePhrase->mathTextNLPparsablePhraseIndex = " << currentParsablePhrase->mathTextNLPparsablePhraseIndex << endl;
			
			currentParsablePhrase = currentParsablePhrase->next;
		}
		
		currentSentence = currentSentence->next;
	}
	#endif

	#ifdef NLC_DEBUG_PREPROCESSOR_PREMATURE_QUIT
	cout << "Premature quit for debug" << endl;
	exit(EXIT_ERROR);
	#endif	


	return result;
}

void NLCpreprocessorClass::addNonLogicalConditionSentenceToList(string* sentenceContents, NLCpreprocessorSentence** currentNLCsentenceInList, int* sentenceIndex, const int currentIndentation, NLCfunction* currentNLCfunctionInList, const NLCfunction* firstNLCfunctionInList)
{
	#ifdef NLC_PREPROCESSOR_MATH
	#ifdef NLC_PREPROCESSOR_MATH_REPLACE_NUMERICAL_VARIABLES_NAMES_FOR_NLP
	NLCpreprocessorMath.replaceNumericalVariablesWithDummyNumberIfNecessary(sentenceContents, *currentNLCsentenceInList, currentNLCfunctionInList, firstNLCfunctionInList);
	#endif
	#endif
	
	#ifdef NLC_MATH_OBJECTS_ADVANCED
	if(this->detectMathObjectStringDelimiter(sentenceContents))
	{
		cout << "preprocessTextForNLC{} error: quotation marks detected without mathtext expression (illegal: 'Print \"this text\"'. legal: 'the value = \"this text\". print the value.')" << endl;
	}
	#endif

	#ifdef NLC_PREPROCESSOR_INTERPRET_SINGLE_WORD_SENTENCES_AS_ACTIONS
	if(NLCpreprocessorSentenceClass.isStringValidVariableName(*sentenceContents, true))
	{
		#ifdef NLC_PREPROCESSOR_INTERPRET_SINGLE_WORD_SENTENCES_AS_ACTIONS_REPLACE_ACTION_ALSO_DUE_TO_NLP_LIMITATION
		string actionName = sentenceContents->substr(0, sentenceContents->length()-1);
		(*currentNLCsentenceInList)->singleWordSentenceActionName = actionName;
		*sentenceContents = "" + NLC_PREPROCESSOR_INTERPRET_SINGLE_WORD_SENTENCES_AS_ACTIONS_DUMMY_TEXT_ACTION_FULL + STRING_FULLSTOP;
		#else
		*sentenceContents = "" + actionName + NLC_PREPROCESSOR_INTERPRET_SINGLE_WORD_SENTENCES_AS_ACTIONS_DUMMY_TEXT_ACTION_OBJECT_FULL + STRING_FULLSTOP; //sentenceContents = sentenceContents.insert((sentenceContents.length()-1), NLC_PREPROCESSOR_INTERPRET_SINGLE_WORD_SENTENCES_AS_ACTIONS_DUMMY_TEXT_ACTION_OBJECT_FULL);
		#endif
	}
	#endif

	(*currentNLCsentenceInList)->firstNLPparsablePhraseInList->sentenceContents = *sentenceContents;	//full stop should already be appended
	(*currentNLCsentenceInList)->firstNLPparsablePhraseInList->sentenceIndex = (*sentenceIndex);
	(*currentNLCsentenceInList)->indentation = currentIndentation;
	(*currentNLCsentenceInList)->next = new NLCpreprocessorSentence();
	(*currentNLCsentenceInList) = (*currentNLCsentenceInList)->next;
	(*sentenceIndex) = (*sentenceIndex)+1;
}

#ifdef NLC_PREPROCESSOR_REDUCE_QUOTES_TO_SINGLE_WORDS
bool NLCpreprocessorClass::reduceQuotesToSingleWords(const string lineText, string* updatedLineText)
{
	bool result = false;
	*updatedLineText = "";
	bool readingQuotation = false;
	for(int i=0; i<lineText.length(); i++)
	{
		char currentToken = lineText[i];
		bool quotationMarkFound = false;
		if(currentToken == CHAR_INVERTED_COMMAS)
		{//only support "" quotation marks (not '') at present
			quotationMarkFound = true;
		}
		/*
		if(charInCharArray(currentToken, nlpQuotationMarkCharacterArray, GIA_NLP_NUMBER_OF_QUOTATIONMARK_CHARACTERS))
		{
			quotationMarkFound = true;
		}
		*/

		bool whiteSpaceFound = false;
		if(currentToken == CHAR_SPACE)
		{//only support " " white space within quotations at present
			whiteSpaceFound = true;
		}
		/*
		if(charInCharArray(currentToken, nlpWhitespaceCharacterArray, GIA_NLP_NUMBER_OF_WHITESPACE_CHARACTERS))
		{
			whiteSpaceFound = true;
		}
		*/

		if(quotationMarkFound)
		{//NB imbedded/recursive quotation marks not currently supported eg "'hello'"
			if(!readingQuotation)
			{
				readingQuotation = true;
			}
			else
			{
				readingQuotation = false;
				result = true;
			}
			//do not add quotation marks; *updatedLineText = *updatedLineText + currentToken;
		}
		else if(readingQuotation && whiteSpaceFound)
		{
			*updatedLineText = *updatedLineText + GIA_TRANSLATOR_UNIQUE_CONCATENATION_TYPES_QUOTES_DELIMITER;
		}
		else
		{
			*updatedLineText = *updatedLineText + currentToken;
		}
	}

	if(readingQuotation)
	{
		cout << "reduceQuotesToSingleWords{} error; quotation mark not ended on current line. Multiline quotations are not currently supported by NLC" << endl;
		result = false;
	}

	return result;
}
#endif


void NLCpreprocessorClass::extractIndentationFromCurrentLine(string* currentLine, int* currentIndentation, string* lineContents, string* indentationContents)
{
	int i = 0;
	while((i < currentLine->length()) && (SHAREDvars.isWhiteSpace((*currentLine)[i]) || (*currentLine)[i] == NLC_PREPROCESSOR_INDENTATION_CHAR))	//in case NLC_PREPROCESSOR_INDENTATION_CHAR is not a form of white space
	{
		char c = (*currentLine)[i];
		if(c == NLC_PREPROCESSOR_INDENTATION_CHAR)
		{
			*currentIndentation = *currentIndentation + 1;
		}
		i++;
	}
	*indentationContents = currentLine->substr(0, i);
	*lineContents = currentLine->substr(i, (currentLine->length()-i));
}

#ifdef NLC_INPUT_FUNCTION_LISTS_PREPROCESSOR
bool NLCpreprocessorClass::detectFunctionHeader(const string* lineContents)
{
	bool functionHeaderFound = false;
	int index = lineContents->find(string(NLC_PREPROCESSOR_FUNCTION_HEADER_STRING));
	if((index != CPP_STRING_FIND_RESULT_FAIL_VALUE) && (index == 0))
	{
		functionHeaderFound = true;
	}
	return functionHeaderFound;
}
string NLCpreprocessorClass::getFunctionNameFromFunctionHeader(const string* lineContents)
{
	string NLCfunctionName = lineContents->substr(string(NLC_PREPROCESSOR_FUNCTION_HEADER_STRING).length() + string(NLC_PREPROCESSOR_FUNCTION_HEADER_MID_CHAR).length());
	return NLCfunctionName;

}
string NLCpreprocessorClass::generateNLCfunctionFileName(const string NLCfunctionName)
{
	string functionFileName = NLCfunctionName + NLC_NATURAL_LANGUAGE_CODE_FILE_NAME_EXTENSION;	//NLC_NATURAL_LANGUAGE_CODE_FILE_NAME_EXTENSION added 1m5a
	return functionFileName;
}
#endif

bool NLCpreprocessorClass::detectLogicalConditionOperatorAtStartOfLine(const string* lineContents, int* logicalConditionOperator)
{

	*logicalConditionOperator = INT_DEFAULT_VALUE;
	bool logicalConditionOperatorFound = false;

	string lowerCaseSentenceContents = SHAREDvars.convertStringToLowerCase(lineContents);
	//get first word in line
	for(int i=0; i<NLC_LOGICAL_CONDITION_OPERATIONS_NUMBER_OF_TYPES; i++)
	{
		int index = lowerCaseSentenceContents.find(logicalConditionOperationsArray[i]);
		if((index != CPP_STRING_FIND_RESULT_FAIL_VALUE) && (index == 0))
		{
			logicalConditionOperatorFound = true;
			*logicalConditionOperator = i;
		}
	}
	return logicalConditionOperatorFound;
}

string NLCpreprocessorClass::removePrependingWhiteSpace(string sentenceContents)
{
	//this function is used in case the current sentence occurs after a previous sentence on the same line (ie after ". ")
	if(sentenceContents.length() > 0)
	{
		if(sentenceContents[0] == CHAR_SPACE)
		{
			sentenceContents = sentenceContents.substr(1, sentenceContents.length()-1);
		}
	}

	return sentenceContents;
}

#ifdef NLC_MATH_OBJECTS_ADVANCED
bool NLCpreprocessorClass::detectMathObjectStringDelimiter(string* lineContents)
{
	bool result = false;
	if(lineContents->find(NLC_MATH_OBJECTS_STRING_DELIMITER_CHAR) != CPP_STRING_FIND_RESULT_FAIL_VALUE)
	{
		result = true;
	}
	return result;
}
#endif

#endif






