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
 * File Name: NLCpreprocessor.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2014 Baxter AI (baxterai.com)
 * Project: Natural Language Programming Interface (compiler)
 * Project Version: 1h1e 25-July-2014
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/



#include <ctime>
#include <cstdlib>	//for random number generation
#include <cmath>

#include "NLCpreprocessor.h"
#include "NLCprintDefs.h" //required for progLangOpenParameterSpace
#include "SHAREDvars.h"	//required for convertStringToLowerCase/isWhiteSpace
#include "GIAentityNodeClass.h" //required for GIA_NLP_START_SENTENCE_INDEX and entityNodesActiveListComplete

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

#ifdef NLC_USE_PREPROCESSOR
bool preprocessTextForNLC(string inputFileName, NLCfunction * firstNLCfunctionInList, bool * detectedFunctions, int * numberOfInputFilesInList, vector<string> * inputTextFileNameList, string outputFileName)
{
	*numberOfInputFilesInList = 1;
	
	bool result = true;
	ifstream parseFileObject(inputFileName.c_str());
	if(!parseFileObject.rdbuf( )->is_open( ))
	{
		//txt file does not exist in current directory.
		cout << "Error: NLC input file does not exist in current directory: " << inputFileName << endl;
		result = false;
	}
	else
	{
		NLCfunction * currentNLCfunctionInList = firstNLCfunctionInList;
		NLCsentence * currentNLCsentenceInList = currentNLCfunctionInList->firstNLCsentenceInFunction;
		string currentLine;
		int sentenceIndex = GIA_NLP_START_SENTENCE_INDEX;
		*detectedFunctions = false;
		string functionContents = "";
		string functionName = "";
		int currentLineNumber = 0;
		
		while(getline(parseFileObject, currentLine))
		{
			currentLineNumber++;
			#ifdef NLC_DEBUG_PREPROCESSOR
			cout << currentLineNumber << ": " << currentLine;
			#endif
			
			#ifdef NLC_SUPPORT_INPUT_FILE_LISTS
			if(detectFunctionHeader(&currentLine))
			{
				//extract functions from file and generate separate files
				if(*detectedFunctions)
				{
					#ifdef NLC_DEBUG_PREPROCESSOR
					cout << "end function: functionName = " << functionName << endl;
					cout << "create new function = " << functionName << endl;
					cout << "functionContents = " << functionContents << endl;
					#endif
					writeStringToFile(&functionName, &functionContents);
					currentNLCfunctionInList->functionName = functionName;
					currentNLCfunctionInList->next = new NLCfunction();
					currentNLCfunctionInList = currentNLCfunctionInList->next;
					currentNLCsentenceInList = currentNLCfunctionInList->firstNLCsentenceInFunction;
					*numberOfInputFilesInList = *numberOfInputFilesInList+1;
					//create new function file based on current text
				}
				else
				{
					#ifdef NLC_DEBUG_PREPROCESSOR
					cout << "detectedFunctions" << endl;
					#endif
					*detectedFunctions = true;
				}
				functionName = getFunctionNameFromFunctionHeader(&currentLine);
				functionContents = currentLine;
			}
			else
			{
			#endif
				int currentIndentation = 0;
				string lineContents = "";
				string indentationContents = "";
				extractIndentationFromCurrentLine(&currentLine, &currentIndentation, &lineContents, &indentationContents);	//this will remove the indentation from the current line
				 
				#ifdef NLC_PREPROCESSOR_MATH
				if(detectMathSymbolsInLine(&lineContents))
				{
					currentNLCsentenceInList->isMath = true;
				}
				
				int lineLogicalConditionOperator;
				if(detectLogicalConditionOperatorAtStartOfLine(&lineContents, &lineLogicalConditionOperator))
				{
					currentNLCsentenceInList->hasLogicalConditionOperator = true;
					#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
					currentNLCsentenceInList->logicalConditionOperator = lineLogicalConditionOperator;
					#endif
						
					#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
					currentNLCsentenceInList->isMath = true;
					replaceLogicalConditionNaturalLanguageMathWithSymbols(&lineContents, true, lineLogicalConditionOperator);
					#endif
				}
				
				//#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
				if(!(currentNLCsentenceInList->isMath))
				{
					if(detectAndReplaceIsEqualToInformalTextWithSymbol(&lineContents))
					{
						currentNLCsentenceInList->isMath = true;
					}
				}
				//#endif
				
				if(currentNLCsentenceInList->isMath)
				{
					#ifdef NLC_DEBUG_PREPROCESSOR_MATH
					cout << "detectMathSymbolsInSentence(lineContents)" << endl;
					#endif
					splitMathDetectedLineIntoNLPparsablePhrases(&lineContents, &currentNLCsentenceInList, &sentenceIndex, currentIndentation);
				}
				else
				{				
					#ifdef NLC_PREPROCESSOR_MATH_REPLACE_NUMERICAL_VARIABLES_NAMES_FOR_NLP
					replaceNumericalVariablesWithDummyNameIfNecessary(&lineContents, currentNLCsentenceInList, currentNLCfunctionInList, firstNLCfunctionInList);
					#endif
				#endif
					functionContents = functionContents + indentationContents;
				
					//now for each sentence on line:
					int startOfSentenceIndex = 0;
					bool stillSentenceToParseOnLine = true;
					bool lineFullStopDetected = false;
					while(stillSentenceToParseOnLine)
					{
						bool lineFullStopDetected = true;
						int startOfSentenceIndexNew = lineContents.find(CHAR_FULLSTOP, startOfSentenceIndex);
						if(startOfSentenceIndexNew == CPP_STRING_FIND_RESULT_FAIL_VALUE)
						{
							startOfSentenceIndexNew = lineContents.find(CHAR_QUESTIONMARK, startOfSentenceIndex);	//NB '.' and '?' are currently supported as sentence delimiters
							if(startOfSentenceIndexNew == CPP_STRING_FIND_RESULT_FAIL_VALUE)
							{
								lineFullStopDetected = false;
							}
						}
						
						string sentenceContents = "";
						if(lineFullStopDetected)
						{
							cout << "lineFullStopDetected" << endl;
							sentenceContents = lineContents.substr(startOfSentenceIndex, startOfSentenceIndexNew-startOfSentenceIndex+1);	//+1 append the full stop

						}
						else
						{
							cout << "!lineFullStopDetected" << endl;
							sentenceContents = lineContents.substr(startOfSentenceIndex, lineContents.length());

						}
						cout << "sentenceContents = " << sentenceContents << endl;

						bool sentenceIsLogicalCondition = false;
						int sentenceLogicalConditionOperator;
						if(detectLogicalConditionOperatorAtStartOfLine(&sentenceContents, &sentenceLogicalConditionOperator))
						{
							sentenceIsLogicalCondition = true;
							cout << "sentenceIsLogicalCondition: " << logicalConditionOperationsArray[sentenceLogicalConditionOperator] << endl;
			
							currentNLCsentenceInList->hasLogicalConditionOperator = true;
							
							/*logicalConditionOperator is only used by mathText with parsable phrases at present (ie lineLogicalConditionOperator)
							#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
							currentNLCsentenceInList->logicalConditionOperator = sentenceLogicalConditionOperator;
							#endif
							*/
												
							#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
							if(sentenceLogicalConditionOperator == NLC_LOGICAL_CONDITION_OPERATIONS_IF)
							{
								#ifdef NLC_PREPROCESSOR_LOGICAL_CONDITION_USE_ROBUST_NLP_INDEPENDENT_CODE
								currentNLCsentenceInList->ifDetected = true;
								#endif
							}
							else if(sentenceLogicalConditionOperator == NLC_LOGICAL_CONDITION_OPERATIONS_ELSE_IF)
							{
								#ifdef NLC_PREPROCESSOR_LOGICAL_CONDITION_USE_ROBUST_NLP_INDEPENDENT_CODE
								currentNLCsentenceInList->elseIfDetected = true;
								//replace "else if" with "If"
								sentenceContents.replace(0, string(NLC_LOGICAL_CONDITION_OPERATIONS_ELSE_IF_STRING).length(), string(NLC_PREPROCESSOR_LOGICAL_CONDITION_DUMMY_TEXT_TEST_ELSEIF));
								#else
								//will rely on NLP to add an "else" property to the logicalConditionObject
								#endif
							}
							else if(sentenceLogicalConditionOperator == NLC_LOGICAL_CONDITION_OPERATIONS_ELSE)
							{
								#ifdef NLC_PREPROCESSOR_LOGICAL_CONDITION_USE_ROBUST_NLP_INDEPENDENT_CODE
								currentNLCsentenceInList->elseDetected = true;
								#endif
								//replace "else" with "If this is done,"
								sentenceContents.replace(0, string(NLC_LOGICAL_CONDITION_OPERATIONS_ELSE_STRING).length(), string(NLC_PREPROCESSOR_LOGICAL_CONDITION_DUMMY_TEXT_TEST_ELSE));

							}
							#endif	
						}		
						
						if(!lineFullStopDetected)
						{								
							stillSentenceToParseOnLine = false;
							
							bool nonWhiteSpaceDetectedBetweenFinalFullStopAndEndOfLine = false;
							for(int i=startOfSentenceIndexNew; i<sentenceContents.length(); i++)
							{
								char c = sentenceContents[i];
								if(!isWhiteSpace(c))
								{
									nonWhiteSpaceDetectedBetweenFinalFullStopAndEndOfLine = true;
								}
							}
							#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
							if(!lineFullStopDetected && nonWhiteSpaceDetectedBetweenFinalFullStopAndEndOfLine && sentenceIsLogicalCondition)
							{
								string lowerCaseSentenceContents = convertStringToLowerCase(&sentenceContents);
								string dummyCommand = "";
								if(sentenceLogicalConditionOperator == NLC_LOGICAL_CONDITION_OPERATIONS_ELSE)
								{
									if(sentenceContents.length() == (string(NLC_LOGICAL_CONDITION_OPERATIONS_ELSE_STRING)).length())
									{
										//sentence was originally "Else" and has not yet been converted to "If this is done,"
										//replace "else" with "If this is done, "
										sentenceContents = string(NLC_PREPROCESSOR_LOGICAL_CONDITION_DUMMY_TEXT_TEST_ELSE);

										dummyCommand = NLC_PREPROCESSOR_LOGICAL_CONDITION_DUMMY_TEXT_COMMAND_ELSE;	//append dummy action " do this."
									}
									else
									{
										//sentence was originally "else ___" and has been converted to "If this is done, ___" - it is invalid because it does not contain a full stop.
										cout << "NLC_USE_PREPROCESSOR preprocessTextForNLC() error: \"else\" logical condition operation detected in combination with an incomplete command (no full stop): sentenceContents = " << sentenceContents << endl;
										exit(0);
									}
								}
								else
								{
									dummyCommand = NLC_PREPROCESSOR_LOGICAL_CONDITION_DUMMY_TEXT_COMMAND;	//append dummy action ", do this."
								}
								//add dummy text ", do this." to the end of the logical condition, such that NLP can parse the logical condition header, and NLC can parse the multi-sentence logical condition based on its indentation.
								#ifdef NLC_DEBUG_PREPROCESSOR
								cout << "create new sentence" << endl;
								cout << "sentenceContents = " << sentenceContents + string(dummyCommand) << endl;
								#endif
								sentenceContents = sentenceContents + string(dummyCommand);
								currentNLCsentenceInList->sentenceContents = sentenceContents;
								currentNLCsentenceInList->sentenceIndex = sentenceIndex;
								currentNLCsentenceInList->indentation = currentIndentation;
								currentNLCsentenceInList->next = new NLCsentence();
								currentNLCsentenceInList = currentNLCsentenceInList->next;
								sentenceIndex++;
							}
							else 
							#endif
							if(!lineFullStopDetected && nonWhiteSpaceDetectedBetweenFinalFullStopAndEndOfLine)
							{
								cout << "NLC_USE_PREPROCESSOR preprocessTextForNLC() error: NLC_PREPROCESSOR_SUPPORT_MULTILINE_SENTENCES are not currently supported" << endl;
								exit(0);
							}
							else
							{//!lineFullStopDetected && !nonWhiteSpaceDetectedBetweenFinalFullStopAndEndOfLine
								//assume that a sentence has already been created based on a full stop (do not support multiline sentences)
								//redundant white space will be culled from functionContents
							}
						}
						else
						{
							#ifdef NLC_DEBUG_PREPROCESSOR
							cout << "create new sentence" << endl;
							cout << "sentenceContents = " << sentenceContents + currentToken << endl;
							#endif
							currentNLCsentenceInList->sentenceContents = sentenceContents;	//full stop should already be appended
							currentNLCsentenceInList->sentenceIndex = sentenceIndex;
							currentNLCsentenceInList->indentation = currentIndentation;
							currentNLCsentenceInList->next = new NLCsentence();
							currentNLCsentenceInList = currentNLCsentenceInList->next;
							sentenceIndex++;

						}
						functionContents = functionContents + sentenceContents;
						startOfSentenceIndex = startOfSentenceIndexNew + 1;	//is +1 required? (to prevent current CHAR_FULLSTOP from being redetected)
					}

				
				#ifdef NLC_PREPROCESSOR_MATH
				}
				#endif
				
			#ifdef NLC_SUPPORT_INPUT_FILE_LISTS
			}
			#endif
		}
		
		#ifdef NLC_SUPPORT_INPUT_FILE_LISTS
		if(*detectedFunctions)
		{
			//create a final function based on the final text..
			#ifdef NLC_DEBUG_PREPROCESSOR
			cout << "create new function = " << functionName << endl;
			cout << "functionContents = " << functionContents << endl;
			#endif
			writeStringToFile(&functionName, &functionContents);
			//create new function file based on current text
		}
		else
		{
		#endif
			#ifdef NLC_DEBUG_PREPROCESSOR
			cout << "create preprocessed file = " << functionName << endl;
			cout  << "functionContents = \n" << functionContents << endl;
			#endif
			writeStringToFile(&outputFileName, &functionContents);
		#ifdef NLC_SUPPORT_INPUT_FILE_LISTS
		}
		#endif
	}

	return result;
}

	


void writeStringToFile(string * fileName, string * s)
{
	ofstream writeFileObject(*fileName);

	for(int i=0; i < s->size(); i++)
	{
		writeFileObject.put((*s)[i]);
	}

	writeFileObject.close();
}

void extractIndentationFromCurrentLine(string * currentLine, int * currentIndentation, string * lineContents, string * indentationContents)
{
	int i = 0; 
	while((i < currentLine->length()) && (isWhiteSpace((*currentLine)[i]) || (*currentLine)[i] == NLC_PREPROCESSOR_INDENTATION_CHAR))	//in case NLC_PREPROCESSOR_INDENTATION_CHAR is not a form of white space
	{
		char c = (*currentLine)[i];
		if(c == NLC_PREPROCESSOR_INDENTATION_CHAR)
		{
			*currentIndentation = *currentIndentation + 1;
		}
		i++;
	}
	*indentationContents = currentLine->substr(0, i);
	*lineContents = currentLine->substr(i, (lineContents->length()-i));
}

#ifdef NLC_SUPPORT_INPUT_FILE_LISTS
bool detectFunctionHeader(string * lineContents)
{
	bool functionHeaderFound = false;
	int index = lineContents->find(string(NLC_PREPROCESSOR_FUNCTION_HEADER_STRING));
	if((index != CPP_STRING_FIND_RESULT_FAIL_VALUE) && (index == 0))
	{
		functionHeaderFound = true;
		cout << "detectFunctionHeader(): functionHeaderFound = " << NLC_PREPROCESSOR_FUNCTION_HEADER_STRING << endl; 
	}
	return functionHeaderFound;
}
string getFunctionNameFromFunctionHeader(string * lineContents)
{
	string functionName = lineContents->substr(string(NLC_PREPROCESSOR_FUNCTION_HEADER_STRING).length()+1);	//+1 for NLC_PREPROCESSOR_FUNCTION_HEADER_MID_CHAR
	cout << "getFunctionNameFromFunctionHeader(): functionName = " << functionName << endl; 
	return functionName;
	
}
#endif


bool detectLogicalConditionOperatorAtStartOfLine(string * lineContents, int * logicalConditionOperator)
{
	*logicalConditionOperator = INT_DEFAULT_VALUE;
	bool logicalConditionOperatorFound = false;
	
	string lowerCaseSentenceContents = convertStringToLowerCase(lineContents);
	//get first word in line
	for(int i=0; i<NLC_LOGICAL_CONDITION_OPERATIONS_NUMBER_OF_TYPES; i++)
	{
		int index = lineContents->find(logicalConditionOperationsArray[i]);
		if((index != CPP_STRING_FIND_RESULT_FAIL_VALUE) && (index == 0))
		{
			logicalConditionOperatorFound = true;
			*logicalConditionOperator = i;
			cout << "detectLogicalConditionOperatorAtStartOfLine(): logicalConditionOperatorFound" << logicalConditionOperationsArray[i] << endl; 
		}
	}
	return logicalConditionOperatorFound;
}
	
#ifdef NLC_PREPROCESSOR_MATH
bool detectMathSymbolsInLine(string * lineContents)
{
	bool mathSymbolFound = false;
	for(int i=0; i<NLC_PREPROCESSOR_MATH_OPERATORS_NUMBER_OF_TYPES; i++)
	{
		int symbolFoundIndex = lineContents->find(preprocessorMathOperatorsNumberOfTypes[i]);
		if(symbolFoundIndex != CPP_STRING_FIND_RESULT_FAIL_VALUE)
		{
			mathSymbolFound = true;
		}
	}
	return mathSymbolFound;
}

bool detectAndReplaceIsEqualToInformalTextWithSymbol(string * lineContents)
{
	bool result = false;
	
	//"x is equal to number of chickens." is supported by mathText, with "number of chickens" parsable phrase
	//the following cannot be parsed by NLP/GIA; "x is the number of chickens" as dummy numerical variable replacement only works for previously defined variables.; convert to mathText and parsable phrase ("x = the number of chickens")*
	int indexOfFirstSpace = lineContents->find(CHAR_SPACE);
	if(indexOfFirstSpace != CPP_STRING_FIND_RESULT_FAIL_VALUE)
	{
		int indexOfIs = lineContents->find(string(NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_IS_EQUAL_TO_INFORMAL), indexOfFirstSpace);
		if((indexOfIs != CPP_STRING_FIND_RESULT_FAIL_VALUE) && (indexOfIs == 0))
		{
			lineContents->replace(indexOfIs, string(NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_IS_EQUAL_TO_INFORMAL).length(), string(NLC_PREPROCESSOR_MATH_OPERATOR_IS_EQUAL_TO));
			result = true;
			cout << "found 'x is ...' at start of line; convert to mathText 'x = (nlp parsable phrase)" << endl;
		}	
	}
	//the following is not supported by NLC at present: "if x is the number of chickens", the user must say "if the number of chickens is equal to x"
	
	return result;
}
				
#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
bool replaceLogicalConditionNaturalLanguageMathWithSymbols(string * lineContents, bool hasLogicalConditionOperator, int logicalConditionOperator)
{
	if(hasLogicalConditionOperator)
	{
		//ensure all logical condition operators have enclosing brackets eg if(...) - this is done to prevent "if" in "if the house is cold" from being merged into an NLP parsable phrase
		char characterAfterLogicalConditionOperator = lineContents->at(logicalConditionOperationsArray[logicalConditionOperator].length());
		if(characterAfterLogicalConditionOperator != NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_OPEN_BRACKET)
		{//NB intermediary white text not currently supported, eg "if (...)"
			lineContents->insert(logicalConditionOperationsArray[logicalConditionOperator].length(), 1, NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_OPEN_BRACKET);
			lineContents->insert(lineContents->length(), 1, NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_CLOSE_BRACKET);
		}
	}
	
	for(int i=0; i<NLC_PREPROCESSOR_MATH_OPERATORS_NUMBER_OF_TYPES; i++)
	{
		replaceAllOccurancesOfString(lineContents, preprocessorMathOperatorsEquivalentNumberOfTypes[i], preprocessorMathOperatorsNumberOfTypes[i]);	//NB this is type sensitive; could be changed in the future
	}
	
	/*
	for(int i=0; i<NLC_LOGICAL_CONDITION_OPERATIONS_NUMBER_OF_TYPES; i++)
	{
		int index = lineContents->find(logicalConditionOperationsArray[i]);
		if((index != CPP_STRING_FIND_RESULT_FAIL_VALUE) && (index == 0))
		{
			logicalConditionOperatorFound = true;
			*logicalConditionOperator = i;
			cout << "detectLogicalConditionOperatorAtStartOfLine(): logicalConditionOperatorFound" << logicalConditionOperationsArray[i] << endl; 
		}
	}
	*/

	//detect conjunctions...
	for(int i=0; i<NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_COORDINATING_CONJUNCTION_ARRAY_NUMBER_OF_TYPES; i++)
	{
		replaceAllOccurancesOfString(lineContents, preprocessorMathOperatorsEquivalentConjunctions[i], progLangCoordinatingConjunctions[i]);	//NB this is type sensitive; could be changed in the future
	}
	
}
#endif

bool splitMathDetectedLineIntoNLPparsablePhrases(string * lineContents, NLCsentence ** currentNLCsentenceInList, int * sentenceIndex, int currentIndentation)
{
	int sentenceIndexOfFullSentence = *sentenceIndex;
	NLCsentence * firstNLCsentenceInFullSentence = *currentNLCsentenceInList;
	
	bool result = true;
	int mathTextNLPparsablePhraseIndex = 0;
	//NLP parsable phrase is taken to be at least 2 consecutive words delimited by a space ie, [a-zA-Z0-9_] [a-zA-Z0-9_]
	int wordIndex = 0;
	int phraseIndex = 0;
	string currentWord = "";
	string currentPhrase = "";
	string mathText = "";
	bool mandatoryCharacterFoundInCurrentWord = false;
	bool parsingWhiteSpace = true;
	
	bool finalWordInSentenceFoundAndIsLegal = false;
	for(int i=0; i<lineContents->length(); i++)
	{
		//eg y = x+the number of house in the park
		//eg y = x+(the number of house in the park)
		char c = (*lineContents)[i];
		
		bool legalWordCharacterFound = charInCharArray(c, preprocessorMathNLPparsableCharacters, NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_CHARACTERS_NUMBER_OF_TYPES);
		if(charInCharArray(c, preprocessorMathNLPparsableCharactersMandatory, NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_CHARACTERS_MANDATORY_NUMBER_OF_TYPES))
		{
			mandatoryCharacterFoundInCurrentWord = true;
		}
		finalWordInSentenceFoundAndIsLegal = false;
		if(legalWordCharacterFound && (i == lineContents->length()-1) && mandatoryCharacterFoundInCurrentWord)
		{
			if(wordIndex >= NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_MIN_NUMBER_WORDS)
			{
				//add final word in sentence to phrase if it is legal
				wordIndex++;
				finalWordInSentenceFoundAndIsLegal = true;
			}
		}
		bool wordDelimiterCharacterFound = charInCharArray(c, preprocessorMathNLPparsableCharactersDelimiter, NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_CHARACTERS_DELIMITER_NUMBER_OF_TYPES);

		if(!legalWordCharacterFound || finalWordInSentenceFoundAndIsLegal)
		{//!legalWordCharacterFound or (legalWordCharacterFound && last character in sentence)
		
			if(mandatoryCharacterFoundInCurrentWord)
			{
				(*currentNLCsentenceInList)->mathTextVariableNames.push_back(currentWord);	//note if the currentWord turns out not to belong to an NLP parsable phrase instead of mathtext it will be removed from mathTextVariableNames
				wordIndex++;
				mandatoryCharacterFoundInCurrentWord = false;
				if(wordDelimiterCharacterFound || finalWordInSentenceFoundAndIsLegal)
				{
					currentPhrase = currentPhrase + currentWord + c;
					//currentWord is either a mathText variable name or part of an NLP parsable phrase (c is a space or comma)
					if(wordIndex >= NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_MIN_NUMBER_WORDS)
					{
						#ifdef NLC_DEBUG_PREPROCESSOR_MATH
						cout << "splitMathDetectedLineIntoNLPparsablePhrases(): create new NLP parsable phrase: currentPhrase = " << currentPhrase << endl;
						#endif
						
						//remove all mathTextVariableNames from sentence (as an NLP parsable phrase does not contain mathText variable names, or if it does the mathText variable are references to predefined mathText variables and will be detected later)
						(*currentNLCsentenceInList)->mathTextVariableNames.clear();
						
						//split sentence and add phrase
						(*currentNLCsentenceInList)->mathTextNLPparsablePhraseIndex = phraseIndex;
						(*currentNLCsentenceInList)->sentenceContents = currentPhrase + CHAR_FULLSTOP;	//append a fullstop to the NLP parsable phrase to make it readable by NLP
						(*currentNLCsentenceInList)->sentenceIndex = *sentenceIndex;
						//(*currentNLCsentenceInList)->indentation = currentIndentation;	//indentation not recorded for NLC parsable phrases
						(*currentNLCsentenceInList)->next = new NLCsentence();
						(*currentNLCsentenceInList) = (*currentNLCsentenceInList)->next;
						(*sentenceIndex) = (*sentenceIndex) + 1;
						phraseIndex++;
						mathText = mathText + generateMathTextNLPparsablePhraseReference(sentenceIndexOfFullSentence, phraseIndex);

						//restart phrase
						currentPhrase = "";
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
			}
			else if(wordDelimiterCharacterFound)
			{//additional white space detected
				currentWord = currentWord + c;
			}
			else
			{
				//currentWord is disgarded as math (eg numbers) in mathText as it does not contain a mandatory character
				currentPhrase = currentPhrase + currentWord + c;	//add previous words in the failed NLP parsable phrase (if existent) and the currentWord to the mathText   
				mathText = mathText + currentPhrase;
				currentPhrase = "";	//restart phrase (assuming it contains text)
				
			}
			//restart word
			currentWord = "";
		}
		else if(legalWordCharacterFound)
		{
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
	}
	
	//now write the full mathText to each sub sentence (NLP parsable phrase) - required for NLC to regenerate the correct math and variable definitions (based on NLP parsable phrases) 
	firstNLCsentenceInFullSentence->isMath = true;
	firstNLCsentenceInFullSentence->mathTextNLPparsablePhraseTotal = phraseIndex;
	firstNLCsentenceInFullSentence->mathText = mathText;
	firstNLCsentenceInFullSentence->indentation = currentIndentation;
	int maxPhraseIndex = phraseIndex - 1;
	if(maxPhraseIndex == 0)
	{
		//add dummy phrase for NLP to parse (will not be used by NLC; create NLP/GIA sentence as a filler for math text replacement only)
		#ifdef NLC_DEBUG_PREPROCESSOR_MATH
		cout << "add dummy phrase for NLP to parse: " << string(NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_DUMMY) << endl;
		#endif
		firstNLCsentenceInFullSentence->sentenceContents = string(NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_DUMMY);
	}
	
	#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
	if(firstNLCsentenceInFullSentence->hasLogicalConditionOperator)
	{
		//need to parse "is" as equals, eg if "x is 33534"; for all mathText which is not NLP parsable text, replace "is" with "=" 
		//replace all instances of "is" in all mathText which is not NLP parsable text with "="
		replaceAllOccurancesOfString(&(firstNLCsentenceInFullSentence->mathText), string(NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_IS_EQUAL_TO_INFORMAL), string(NLC_PREPROCESSOR_MATH_OPERATOR_IS_EQUAL_TO));	//NB this is type sensitive; could be changed in the future
			
		//"x is equal to number of chickens." is supported by mathText, with "number of chickens" parsable phrase
		//the following cannot be parsed by NLP/GIA; "x is the number of chickens" as dummy numerical variable replacement only works for previously defined variables.; convert to mathText and parsable phrase ("x = the number of chickens")*

		//how do deal with logical condition commands? eg "if the dog has a ball and [the dog] has an apple, ride the bike"? must detect comma as a new NLP parsable phrase, and any parsable phrase without a starting conjunction as a logical condition command
		if(finalWordInSentenceFoundAndIsLegal)
		{//the last text is math text is a parsable phrase; it is therefore a logical condition command candidate
			if(maxPhraseIndex > 1)
			{
				NLCsentence * currentPhrase = firstNLCsentenceInFullSentence;
				while(currentPhrase->next != NULL)
				{
					currentPhrase = currentPhrase->next;
				}
				//currentPhrase is the last phrase
				//get first word in line

				bool finalParsablePhraseIsLogicalConditionCommand = true;
				//NB conjunctions in mathText will already have been replaced with code (so dont check entityCoordinatingConjunctionArray)
				for(int i=0; i<NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_COORDINATING_CONJUNCTION_ARRAY_NUMBER_OF_TYPES; i++)
				{
					int index = firstNLCsentenceInFullSentence->mathText.find(progLangCoordinatingConjunctions[i], firstNLCsentenceInFullSentence->mathText.length() - progLangCoordinatingConjunctions[i].length());
					if((index != CPP_STRING_FIND_RESULT_FAIL_VALUE) && (index == 0))
					{
						//"&&"/"||" is the final text in the mathText
						finalParsablePhraseIsLogicalConditionCommand = false;
					}					
				}
				for(int i=0; i<NLC_PREPROCESSOR_MATH_OPERATORS_NUMBER_OF_TYPES; i++)
				{
					int index = firstNLCsentenceInFullSentence->mathText.find(preprocessorMathOperatorsNumberOfTypes[i], firstNLCsentenceInFullSentence->mathText.length() - preprocessorMathOperatorsNumberOfTypes[i].length());	
					if((index != CPP_STRING_FIND_RESULT_FAIL_VALUE) && (index == 0))
					{
						//">"/"<"/"="/"+" is the final text in the mathText
						finalParsablePhraseIsLogicalConditionCommand = false;
					}					
				}								

				if(finalParsablePhraseIsLogicalConditionCommand)
				{
					cout << "finalParsablePhraseIsLogicalConditionCommand:" << currentPhrase->sentenceContents << endl;
					//disconnect logical condition command parsable phrase from mathText
					firstNLCsentenceInFullSentence->mathTextNLPparsablePhraseTotal = firstNLCsentenceInFullSentence->mathTextNLPparsablePhraseTotal - 1;
					firstNLCsentenceInFullSentence->mathText = firstNLCsentenceInFullSentence->mathText.substr(firstNLCsentenceInFullSentence->mathText.length()-generateMathTextNLPparsablePhraseReference(sentenceIndexOfFullSentence, maxPhraseIndex).length(), generateMathTextNLPparsablePhraseReference(sentenceIndexOfFullSentence, maxPhraseIndex).length());	//remove parsable phrase reference from mathText
					//OLD: firstNLCsentenceInFullSentence->mathText = firstNLCsentenceInFullSentence->mathText.substr(0, generateMathTextNLPparsablePhraseReference(sentenceIndexOfFullSentence, maxPhraseIndex).length());	//remove parsable phrase reference from mathText
					cout << "finalParsablePhraseIsLogicalConditionCommand; modified mathText = " << firstNLCsentenceInFullSentence->mathText << endl;
					currentPhrase->indentation = currentIndentation + 1;			
				}
			}
		}
		
		//for logical condition NLP parsable phrases, look for first instance of keywords has/is, and take the preceeding text as the context
		//this enables elimination for need for referencing in conjunctions, eg "if{(}the dog has a ball and [the dog] has an apple{)}"
		//FINISH THIS...
		NLCsentence * currentPhrase = firstNLCsentenceInFullSentence;
		for(int phraseIndex=0; phraseIndex<maxPhraseIndex; phraseIndex++)
		{
			int indexOfPrimaryAuxillaryTaggingSubject = NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_MAX_CHARACTERS;
			int primaryAuxillaryType;
			for(int i=0; i<NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_AUXILLARY_KEYWORDS_TAGGING_SUBJECT_OR_REFERENCE_NUMBER_OF_TYPES; i++)
			{
				bool stillFindingPrimaryAuxillary = true;
				int startPosToSearchForAuxillary = 0;
				while(stillFindingPrimaryAuxillary)
				{
					int indexOfAuxillaryTemp = currentPhrase->sentenceContents.find(preprocessorMathAuxillaryKeywordsTaggingSubjectOrReference[i], startPosToSearchForAuxillary);	
					if((indexOfAuxillaryTemp != CPP_STRING_FIND_RESULT_FAIL_VALUE) && (indexOfAuxillaryTemp < indexOfPrimaryAuxillaryTaggingSubject))
					{
						//ignore auxillary if has a preceeding 'that'/'which'; eg "the dog that is[ignore] near the house has[take] a ball or has[reference] an apple"
						//"If the basket that is near the house is above the tray, and the basket is blue, the dog is happy."
						//"If the basket that is near the house is above the tray and is blue, the dog is happy.
						bool ignoreAuxillary = false;
						for(int i2=0; i2<NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_RCMOD_SAME_REFERENCE_SET_DELIMITER_NUMBER_OF_TYPES; i2++)
						{
							int expectedPosOfRcmodSameReferenceSetDelimiterIfExistent = indexOfAuxillaryTemp - preprocessorMathRcmodSameReferenceSetDelimiter[i2].length() - 1;
							int indexOfRcmodSameReferenceSet = currentPhrase->sentenceContents.find(preprocessorMathRcmodSameReferenceSetDelimiter[i2], expectedPosOfRcmodSameReferenceSetDelimiterIfExistent);	
							if((indexOfRcmodSameReferenceSet != CPP_STRING_FIND_RESULT_FAIL_VALUE) && (indexOfRcmodSameReferenceSet == expectedPosOfRcmodSameReferenceSetDelimiterIfExistent))
							{
								ignoreAuxillary = true;
							}
						}

						if(!ignoreAuxillary)
						{
							indexOfPrimaryAuxillaryTaggingSubject = indexOfAuxillaryTemp;
							primaryAuxillaryType = i;
							stillFindingPrimaryAuxillary = false;
						}
						else
						{
							startPosToSearchForAuxillary = indexOfAuxillaryTemp + 1;	//check +1 is required
						}
					}
					else
					{
						stillFindingPrimaryAuxillary = false;
					}
				}
			}
			if(indexOfPrimaryAuxillaryTaggingSubject != NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_MAX_CHARACTERS)
			{
				string subjectText = currentPhrase->sentenceContents.substr(0, indexOfPrimaryAuxillaryTaggingSubject);	//check -1 is not required
				cout << "primary auxillary found for phrase: " << currentPhrase->sentenceContents << endl;
				cout << "subjectText = " << subjectText << endl;
				//now for each secondary auxillary referencing the subject, artificially generate (copy) the subject text
				bool stillFindingSecondaryAuxillary = false;
				int startPosToSearchForAuxillary = indexOfPrimaryAuxillaryTaggingSubject;
				while(stillFindingSecondaryAuxillary)
				{
					int indexOfSecondaryAuxillaryReferencingSubject = currentPhrase->sentenceContents.find(preprocessorMathAuxillaryKeywordsTaggingSubjectOrReference[primaryAuxillaryType], startPosToSearchForAuxillary);	
					if(indexOfSecondaryAuxillaryReferencingSubject != CPP_STRING_FIND_RESULT_FAIL_VALUE)
					{
						bool secondaryChecks = false;
						for(int i2=0; i2<NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_COORDINATING_CONJUNCTION_ARRAY_NUMBER_OF_TYPES; i2++)
						{
							int expectedPosOfConjunctionIfExistent = indexOfSecondaryAuxillaryReferencingSubject - preprocessorMathOperatorsEquivalentConjunctions[i2].length() - 1;
							int indexOfConjunction = currentPhrase->sentenceContents.find(preprocessorMathOperatorsEquivalentConjunctions[i2], expectedPosOfConjunctionIfExistent);	
							if((indexOfConjunction != CPP_STRING_FIND_RESULT_FAIL_VALUE) && (indexOfConjunction == expectedPosOfConjunctionIfExistent))
							{
								secondaryChecks = true;
							}
						}
						if(secondaryChecks)
						{
							//insert subject content
							cout << "insert subject content" << endl;
							cout << "old currentPhrase->sentenceContents = " << currentPhrase->sentenceContents << endl;
							currentPhrase->sentenceContents.insert(indexOfSecondaryAuxillaryReferencingSubject, subjectText);
							cout << "new currentPhrase->sentenceContents = " << currentPhrase->sentenceContents << endl;
							startPosToSearchForAuxillary = startPosToSearchForAuxillary + subjectText.length() + 1;	//check +1 is required
						}
					}
					else
					{
						stillFindingSecondaryAuxillary = false;
					}
				}
				
			}

			currentPhrase = currentPhrase->next;					
		}
		
		
	}
	#endif
	
	return result;
}

string generateMathTextNLPparsablePhraseReference(int sentenceIndexOfFullSentence, int phraseIndex)
{
	string mathTextNLPparsablePhraseReference = string(NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_REFERENCE) + string(NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_REFERENCE_SENTENCE) + convertIntToString(sentenceIndexOfFullSentence) + string(NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_REFERENCE_PHRASE) + convertIntToString(phraseIndex);
	return mathTextNLPparsablePhraseReference;
}


#ifdef NLC_PREPROCESSOR_MATH_REPLACE_NUMERICAL_VARIABLES_NAMES_FOR_NLP

bool replaceNumericalVariablesWithDummyNameIfNecessary(string * lineContents, NLCsentence * currentNLCsentenceInList, NLCfunction * currentNLCfunctionInList, NLCfunction * firstNLCfunctionInList)
{
	bool result = true;
	
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
				if(findPredefinedNumericalVariable(&currentWord, currentNLCfunctionInList, firstNLCfunctionInList))	//pass firstNLCfunctionInList and update findPredefinedNumericalVariable() accordingly to allow global numerical variable definitions; not just local numerical variable definitions
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
		if(findPredefinedNumericalVariable(&currentWord, currentNLCfunctionInList, firstNLCfunctionInList))	//pass firstNLCfunctionInList and update findPredefinedNumericalVariable() accordingly to allow global numerical variable definitions; not just local numerical variable definitions
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

bool findPredefinedNumericalVariable(string * currentWord, NLCfunction * currentNLCfunctionInList, NLCfunction * firstNLCfunctionInList)	//pass firstNLCfunctionInList and update findPredefinedNumericalVariable() accordingly to allow global numerical variable definitions; not just local numerical variable definitions
{
	bool result = false;
	#ifdef NLC_PREPROCESSOR_REPLACE_NUMERICAL_VARIABLES_DETECT_GLOBAL_NUMERICAL_VARIABLES
	currentNLCfunctionInList = firstNLCfunctionInList;
	while(currentNLCfunctionInList->next != NULL)
	{
	#endif
		NLCsentence * currentNLCsentenceInList = currentNLCfunctionInList->firstNLCsentenceInFunction;
		while(currentNLCsentenceInList->next != NULL)
		{
			for(vector<string>::iterator iter = currentNLCsentenceInList->mathTextVariableNames.begin(); iter != currentNLCsentenceInList->mathTextVariableNames.end(); iter++)
			{
				string mathTextVariableName = *iter;
				if(*currentWord == mathTextVariableName)
				{
					result = true;
				} 
			}			
			currentNLCsentenceInList = currentNLCsentenceInList->next;
		}		
	
	#ifdef NLC_PREPROCESSOR_REPLACE_NUMERICAL_VARIABLES_DETECT_GLOBAL_NUMERICAL_VARIABLES
		currentNLCfunctionInList = currentNLCfunctionInList->next;
	}
	#endif
	return result;
}
			
int generateDummyNumericalValue(int predefinedVariableIndex)
{
	int dummyNumericalValue = predefinedVariableIndex + NLC_PREPROCESSOR_MATH_DUMMY_NUMERICAL_VALUE_BASE;
	return dummyNumericalValue;
}
				
#endif


#endif

#endif




