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
 * Project Version: 1h5b 30-July-2014
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

#ifdef NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
NLCsuperphrase::NLCsuperphrase(void)
{
	lineIndexOfFirstCharacterInPhrase = INT_DEFAULT_VALUE;
	phraseContents = "";
	hasConjunction = false;
	conjunctionType = INT_DEFAULT_VALUE;
	next = NULL;
}
NLCsuperphrase::~NLCsuperphrase(void)
{
}
#endif

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
		setCurrentDirectory(tempFolderCharStar);	//save output files to temp folder

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
			cout << currentLineNumber << ": " << currentLine << endl;
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
				sentenceIndex = GIA_NLP_START_SENTENCE_INDEX;
				functionName = getFunctionNameFromFunctionHeader(&currentLine);
				inputTextFileNameList->push_back(functionName);
				functionContents = "";
			}
			else
			{
			#endif
				int currentIndentation = 0;
				string lineContents = "";
				string indentationContents = "";
				extractIndentationFromCurrentLine(&currentLine, &currentIndentation, &lineContents, &indentationContents);	//this will remove the indentation from the current line
				#ifdef NLC_DEBUG_PREPROCESSOR
				//cout << "currentIndentation = " << currentIndentation << endl;
				#endif
				
				#ifdef NLC_PREPROCESSOR_MATH
				if(detectMathSymbolsInLine(&lineContents))
				{
					currentNLCsentenceInList->isMath = true;
				}
				
				int lineLogicalConditionOperator;
				bool additionalClosingBracketRequired = false;
				if(detectLogicalConditionOperatorAtStartOfLine(&lineContents, &lineLogicalConditionOperator))
				{
					//cout << "hasLogicalConditionOperator" << endl;
					currentNLCsentenceInList->hasLogicalConditionOperator = true;
					#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
					currentNLCsentenceInList->logicalConditionOperator = lineLogicalConditionOperator;
					#endif
						
					#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
					currentNLCsentenceInList->isMath = true;
					replaceLogicalConditionNaturalLanguageMathWithSymbols(&lineContents, lineLogicalConditionOperator, &additionalClosingBracketRequired);
					#endif
				}
				else
				{
					//#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
					if(detectAndReplaceIsEqualToNonLogicalConditionTextWithSymbol(&lineContents, currentNLCsentenceInList->hasLogicalConditionOperator, currentNLCsentenceInList->isMath))
					{
						currentNLCsentenceInList->isMath = true;
					}
					//#endif
				}
				
				if(currentNLCsentenceInList->isMath)
				{
					#ifdef NLC_PREPROCESSOR_MATH_SUPPORT_USER_VARIABLE_TYPE_DECLARATIONS
					replaceExplicitVariableTypesWithNLPparsablePhraseIllegalWords(&lineContents);
					#endif
					
					#ifdef NLC_DEBUG_PREPROCESSOR_MATH
					cout << "splitMathDetectedLineIntoNLPparsablePhrases():" << endl;
					#endif
					splitMathDetectedLineIntoNLPparsablePhrases(&lineContents, &currentNLCsentenceInList, &sentenceIndex, currentIndentation, &functionContents, currentNLCfunctionInList, firstNLCfunctionInList, additionalClosingBracketRequired);
				}
				else
				{				
					#ifdef NLC_PREPROCESSOR_MATH_REPLACE_NUMERICAL_VARIABLES_NAMES_FOR_NLP
					replaceNumericalVariablesWithDummyNameIfNecessary(&lineContents, currentNLCsentenceInList, currentNLCfunctionInList, firstNLCfunctionInList);
					#endif
				#endif
					//cout << "at-1" << endl;
					functionContents = functionContents + indentationContents;
				
					//now for each sentence on line:
					int startOfSentenceIndex = 0;
					bool stillSentenceToParseOnLine = true;
					while(stillSentenceToParseOnLine)
					{
						bool lineFullStopDetected = false;
						int startOfSentenceIndexNew = lineContents.find(NLC_PREPROCESSOR_END_OF_SENTENCE_CHAR, startOfSentenceIndex);
						if(startOfSentenceIndexNew != CPP_STRING_FIND_RESULT_FAIL_VALUE)
						{
							lineFullStopDetected = true;
						}
						else
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
							#ifdef NLC_DEBUG_PREPROCESSOR
							cout << "lineFullStopDetected" << endl;
							#endif
							sentenceContents = lineContents.substr(startOfSentenceIndex, startOfSentenceIndexNew-startOfSentenceIndex+1);	//+1 append the full stop

						}
						else
						{
							#ifdef NLC_DEBUG_PREPROCESSOR
							cout << "!lineFullStopDetected" << endl;
							#endif
							sentenceContents = lineContents.substr(startOfSentenceIndex, lineContents.length());

						}
						//cout << "sentenceContents = " << sentenceContents << endl;

						bool sentenceIsLogicalCondition = false;
						int sentenceLogicalConditionOperator;
						if(detectLogicalConditionOperatorAtStartOfLine(&sentenceContents, &sentenceLogicalConditionOperator))
						{
							sentenceIsLogicalCondition = true;
							#ifdef NLC_DEBUG_PREPROCESSOR
							cout << "sentenceIsLogicalCondition: " << logicalConditionOperationsArray[sentenceLogicalConditionOperator] << endl;
							#endif
							currentNLCsentenceInList->hasLogicalConditionOperator = true;
							
							/*logicalConditionOperator is only used by mathText with parsable phrases at present (ie lineLogicalConditionOperator)
							#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
							currentNLCsentenceInList->logicalConditionOperator = sentenceLogicalConditionOperator;
							#endif
							*/
												
							#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
							//cout << "at0" << endl;
							if(sentenceLogicalConditionOperator == NLC_LOGICAL_CONDITION_OPERATIONS_IF)
							{
								//cout << "at1" << endl;
								#ifdef NLC_PREPROCESSOR_LOGICAL_CONDITION_USE_ROBUST_NLP_INDEPENDENT_CODE
								currentNLCsentenceInList->ifDetected = true;
								#endif
							}
							else if(sentenceLogicalConditionOperator == NLC_LOGICAL_CONDITION_OPERATIONS_ELSE_IF)
							{
								//cout << "at2" << endl;
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
								//cout << "at3" << endl;
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
							for(int i=startOfSentenceIndex; i<sentenceContents.length(); i++)
							{
								char c = sentenceContents[i];
								if(!isWhiteSpace(c))
								{
									nonWhiteSpaceDetectedBetweenFinalFullStopAndEndOfLine = true;
									//cout << "nonWhiteSpaceDetectedBetweenFinalFullStopAndEndOfLine" << endl;
								}
							}
							#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
							if(!lineFullStopDetected && nonWhiteSpaceDetectedBetweenFinalFullStopAndEndOfLine && sentenceIsLogicalCondition)
							{
								#ifdef NLC_DEBUG_PREPROCESSOR
								cout << "(!lineFullStopDetected && nonWhiteSpaceDetectedBetweenFinalFullStopAndEndOfLine && sentenceIsLogicalCondition)" << endl;
								#endif
								
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
								cout << sentenceIndex << ": sentenceContents = " << sentenceContents + string(dummyCommand) << endl;
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
							cout << sentenceIndex << ": sentenceContents = " << sentenceContents << endl;
							#endif
							currentNLCsentenceInList->sentenceContents = sentenceContents;	//full stop should already be appended
							currentNLCsentenceInList->sentenceIndex = sentenceIndex;
							currentNLCsentenceInList->indentation = currentIndentation;
							currentNLCsentenceInList->next = new NLCsentence();
							currentNLCsentenceInList = currentNLCsentenceInList->next;
							sentenceIndex++;
							
							if(startOfSentenceIndexNew == lineContents.length()-1)
							{
								stillSentenceToParseOnLine = false;
							}
						}
						functionContents = functionContents + sentenceContents + CHAR_NEWLINE;
						startOfSentenceIndex = startOfSentenceIndexNew + 1;	//is +1 required? (to prevent current NLC_PREPROCESSOR_END_OF_SENTENCE_CHAR/CHAR_FULLSTOP from being redetected)
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
	
	#ifdef NLC_PREPROCESSOR_PRINT_OUTPUT
	NLCsentence * currentNLCsentenceInList = firstNLCfunctionInList->firstNLCsentenceInFunction;
	while(currentNLCsentenceInList->next != NULL)
	{
		for(int i=0;i<currentNLCsentenceInList->indentation; i++)
		{
			cout << "\t";
		}
		cout << currentNLCsentenceInList->sentenceContents;
		if(currentNLCsentenceInList->isMath)
		{
			cout << " (mathText = " << currentNLCsentenceInList->mathText << ")" << endl;
		}
		else
		{
			cout << endl;
		}
		currentNLCsentenceInList = currentNLCsentenceInList->next;
	}
	#endif
	
	#ifdef NLC_DEBUG_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
	cout << "Premature quit for debug" << endl;	
	//exit(0);
	#endif

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
	*lineContents = currentLine->substr(i, (currentLine->length()-i));
}

#ifdef NLC_SUPPORT_INPUT_FILE_LISTS
bool detectFunctionHeader(string * lineContents)
{
	bool functionHeaderFound = false;
	int index = lineContents->find(string(NLC_PREPROCESSOR_FUNCTION_HEADER_STRING));
	if((index != CPP_STRING_FIND_RESULT_FAIL_VALUE) && (index == 0))
	{
		functionHeaderFound = true;
		
		//cout << "detectFunctionHeader(): functionHeaderFound = " << NLC_PREPROCESSOR_FUNCTION_HEADER_STRING << endl; 
	}
	return functionHeaderFound;
}
string getFunctionNameFromFunctionHeader(string * lineContents)
{
	string functionName = lineContents->substr(string(NLC_PREPROCESSOR_FUNCTION_HEADER_STRING).length()+1);	//+1 for NLC_PREPROCESSOR_FUNCTION_HEADER_MID_CHAR
	//cout << "getFunctionNameFromFunctionHeader(): functionName = " << functionName << endl; 
	return functionName;
	
}
#endif


bool detectLogicalConditionOperatorAtStartOfLine(string * lineContents, int * logicalConditionOperator)
{
	//cout << "detectLogicalConditionOperatorAtStartOfLine() lineContents = " << *lineContents << endl;

	*logicalConditionOperator = INT_DEFAULT_VALUE;
	bool logicalConditionOperatorFound = false;
	
	string lowerCaseSentenceContents = convertStringToLowerCase(lineContents);
	//get first word in line
	for(int i=0; i<NLC_LOGICAL_CONDITION_OPERATIONS_NUMBER_OF_TYPES; i++)
	{
		int index = lowerCaseSentenceContents.find(logicalConditionOperationsArray[i]);
		if((index != CPP_STRING_FIND_RESULT_FAIL_VALUE) && (index == 0))
		{
			logicalConditionOperatorFound = true;
			*logicalConditionOperator = i;
			#ifdef NLC_DEBUG_PREPROCESSOR
			cout << "detectLogicalConditionOperatorAtStartOfLine(): logicalConditionOperatorFound" << logicalConditionOperationsArray[i] << endl;
			#endif
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
		int symbolFoundIndex = lineContents->find(preprocessorMathOperators[i]);
		if(symbolFoundIndex != CPP_STRING_FIND_RESULT_FAIL_VALUE)
		{
			mathSymbolFound = true;
		}
	}
	return mathSymbolFound;
}

#ifdef NLC_PREPROCESSOR_MATH_SUPPORT_USER_VARIABLE_TYPE_DECLARATIONS
bool replaceExplicitVariableTypesWithNLPparsablePhraseIllegalWords(string * lineContents)
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
#endif

bool detectAndReplaceIsEqualToNonLogicalConditionTextWithSymbol(string * lineContents, bool hasLogicalConditionOperator, bool isMathText)
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
				
#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
bool replaceLogicalConditionNaturalLanguageMathWithSymbols(string * lineContents, int logicalConditionOperator, bool * additionalClosingBracketRequired)
{
	for(int i=0; i<NLC_PREPROCESSOR_MATH_OPERATORS_NUMBER_OF_TYPES; i++)
	{
		*lineContents = replaceAllOccurancesOfString(lineContents, preprocessorMathOperatorsEquivalentNumberOfTypes[i], preprocessorMathOperatorsForLogicalConditions[i]);	//NB this is type sensitive; could be changed in the future
	}
	
	//replace the logical condition operator with a lower case version if necessary
	lineContents->replace(0, logicalConditionOperationsArray[logicalConditionOperator].length(), logicalConditionOperationsArray[logicalConditionOperator]);
	
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
	
	if(logicalConditionOperator != NLC_LOGICAL_CONDITION_OPERATIONS_ELSE)
	{
		//detect conjunctions...
		*additionalClosingBracketRequired = false;
		#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE_REPLACE_COMMAS_WITH_BRACKETS
		for(int i=0; i<NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_COORDINATING_CONJUNCTION_WITH_PAUSE_ARRAY_NUMBER_OF_TYPES; i++)
		{
			int index = (*lineContents).find(preprocessorMathOperatorsEquivalentConjunctionsWithPause[i]);	//NB this is type sensitive; could be changed in the future
			if(index != CPP_STRING_FIND_RESULT_FAIL_VALUE)
			{
				*additionalClosingBracketRequired = true;
			}
			#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
			cout << "additionalClosingBracketRequired" << endl;
			#endif
		}
		#endif
		for(int i=0; i<NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_COORDINATING_CONJUNCTION_ARRAY_NUMBER_OF_TYPES; i++)
		{
			*lineContents = replaceAllOccurancesOfString(lineContents, preprocessorMathOperatorsEquivalentConjunctions[i], progLangCoordinatingConjunctions[i]);	//NB this is type sensitive; could be changed in the future
		}

		//ensure all logical condition operators have enclosing brackets eg if(...) - this is done to prevent "if" in "if the house is cold" from being merged into an NLP parsable phrase

		char characterAfterLogicalConditionOperator = lineContents->at(logicalConditionOperationsArray[logicalConditionOperator].length());
		if(characterAfterLogicalConditionOperator == NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_OPEN_BRACKET)
		{//NB intermediary white text not currently supported, eg "if (...)"
			#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE_REPLACE_COMMAS_WITH_BRACKETS
			if(*additionalClosingBracketRequired)
			{
				lineContents->insert(logicalConditionOperationsArray[logicalConditionOperator].length()+1, 1, NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_OPEN_BRACKET);
			}
			#endif
		}
		else if(characterAfterLogicalConditionOperator == CHAR_SPACE)
		{
			lineContents->replace(logicalConditionOperationsArray[logicalConditionOperator].length(), 1, NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_OPEN_BRACKET_STRING);
			#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE_REPLACE_COMMAS_WITH_BRACKETS
			if(*additionalClosingBracketRequired)
			{
				lineContents->insert(logicalConditionOperationsArray[logicalConditionOperator].length()+1, 1, NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_OPEN_BRACKET);
			}	
			#endif
		}
		else
		{
			cout << "replaceLogicalConditionNaturalLanguageMathWithSymbols() error: invalid symbol found after logicalConditionOperator: " << logicalConditionOperationsArray[logicalConditionOperator] << characterAfterLogicalConditionOperator << endl;
		}
	}
	
	#ifdef NLC_PREPROCESSOR_MATH_FIX_USER_INAPPROPRIATE_USE_OF_EQUALS_SET_IN_LOGICAL_CONDITIONS
	*lineContents = replaceAllOccurancesOfString(lineContents, NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_SET_WITH_PADDING, NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_TEST_WITH_PADDING);
	#endif
}
#endif

bool splitMathDetectedLineIntoNLPparsablePhrases(string * lineContents, NLCsentence ** currentNLCsentenceInList, int * sentenceIndex, int currentIndentation, string * functionContents, NLCfunction * currentNLCfunctionInList, NLCfunction * firstNLCfunctionInList, bool additionalClosingBracketRequired)
{
	//cout << "sentenceIndex at start of nlp parsable phrase extraction = " << *sentenceIndex << endl;

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
				cout << "lineContents = " << *lineContents << endl;
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
	int indexOfLogicalConditionCommand = INT_DEFAULT_VALUE;
	if(firstNLCsentenceInFullSentence->hasLogicalConditionOperator)
	{
		if(!generateLogicalConditionImplicitConjunctionsAndIdentifyCommand(lineContents, &detectedLogicalConditionCommand, &foundImplicitConjunctions, &indexOfLogicalConditionCommand))
		{
			result = false;
		}
	}
	#ifdef NLC_DEBUG_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
	cout << "indexOfLogicalConditionCommand = " << indexOfLogicalConditionCommand << endl;
	#endif
	int phraseIndexOfFirstLogicalCommand = INT_DEFAULT_VALUE;
	#endif

	bool parsingWhiteSpace = false;	//added 1h5b 30-July-2014
	
	bool finalWordInSentenceFoundAndIsLegal = false;
	for(int i=startIndex; i<lineContents->length(); i++)
	{
		//eg y = x+the number of house in the park
		//eg y = x+(the number of house in the park)
		char c = (*lineContents)[i];
		
		#ifdef NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
		if(i >= indexOfLogicalConditionCommand)
		{
			if(phraseIndexOfFirstLogicalCommand == INT_DEFAULT_VALUE)
			{//do not overwrite phraseIndexOfFirstLogicalCommand
				phraseIndexOfFirstLogicalCommand = phraseIndex;
			}
		}
		#endif
		
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
				#ifdef NLC_DEBUG_PREPROCESSOR_MATH
				cout << "finalWordInSentenceFoundAndIsLegal" << endl;
				#endif
				//add final word in sentence to phrase if it is legal
				currentWord = currentWord + c;
				finalWordInSentenceFoundAndIsLegal = true;
			}
		}
		bool wordDelimiterCharacterFound = charInCharArray(c, preprocessorMathNLPparsableCharactersDelimiter, NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_CHARACTERS_DELIMITER_NUMBER_OF_TYPES);

		if(!legalWordCharacterFound || finalWordInSentenceFoundAndIsLegal)
		{//!legalWordCharacterFound or (legalWordCharacterFound && last character in sentence)

			//cout << "!legalWordCharacterFound || finalWordInSentenceFoundAndIsLegal): " << c << endl;
			
			//current word checks:
			if(mandatoryCharacterFoundInCurrentWord)
			{
				if((firstNLCsentenceInFullSentence->hasLogicalConditionOperator))
				{
					if(i == currentWord.length())
					{
						if(textInTextArray(currentWord, logicalConditionOperationsArray, NLC_LOGICAL_CONDITION_OPERATIONS_NUMBER_OF_TYPES))
						{
							#ifdef NLC_DEBUG_PREPROCESSOR_MATH
							cout << "logical condition operator detected: mandatoryCharacterFoundInCurrentWord = false" << endl;
							#endif
							mandatoryCharacterFoundInCurrentWord = false;
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
								//cout << "old currentPhrase = " << currentPhrase << endl;
								currentPhrase.insert(0, NLC_PREPROCESSOR_MATH_MATHTEXT_VARIABLE_TYPE_DEFAULT);
								//cout << "new currentPhrase = " << currentPhrase << endl;

								newlyDeclaredVariable = currentWord;
								mandatoryCharacterFoundInCurrentWord = false;
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
										mandatoryCharacterFoundInCurrentWord = false;
										(*currentNLCsentenceInList)->mathTextVariableNames.push_back(currentWord);
									}
								}
							}
						}
					}
				}
				#endif
			}			
						
			if(mandatoryCharacterFoundInCurrentWord)
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
				cout << "mandatoryCharacterFoundInCurrentWord: " << currentWord << endl;
				cout << "wordDelimiterCharacterFound = " << wordDelimiterCharacterFound << endl;
				cout << "wordIndex = " << wordIndex << endl;
				#endif
				if(!parsingWhiteSpace)
				{
					wordIndex++;
				}
				
				if(!wordDelimiterCharacterFound || finalWordInSentenceFoundAndIsLegal)
				{
					mandatoryCharacterFoundInCurrentWord = false;

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
						(*currentNLCsentenceInList)->sentenceContents = currentPhrase + NLC_PREPROCESSOR_END_OF_SENTENCE_CHAR;	//append a fullstop to the NLP parsable phrase to make it readable by NLP
						(*currentNLCsentenceInList)->sentenceIndex = *sentenceIndex;
						//(*currentNLCsentenceInList)->indentation = currentIndentation;	//indentation not recorded for NLC parsable phrases
						mathText = mathText + generateMathTextNLPparsablePhraseReference(sentenceIndexOfFullSentence, (*currentNLCsentenceInList));
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
						if(!finalWordInSentenceFoundAndIsLegal)
						{
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
				//currentWord is disgarded as math (eg numbers) in mathText as it does not contain a mandatory character
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
	int maxPhraseIndex = phraseIndex;
	if(maxPhraseIndex == 0)
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
					//cout << "lineContents = " << *lineContents << endl;
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

	//cout << "sentenceIndex at end of nlp parsable phrase extraction = " << *sentenceIndex << endl;
	
	#ifdef NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
	if(firstNLCsentenceInFullSentence->hasLogicalConditionOperator)
	{
		if(detectedLogicalConditionCommand)
		{
			#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
			cout << "detectedLogicalConditionCommand: mathText = " << firstNLCsentenceInFullSentence->mathText << endl;
			cout << "phraseIndexOfFirstLogicalCommand = " << phraseIndexOfFirstLogicalCommand << endl;
			#endif
			
			NLCsentence * firstPhraseInLogicalConditionCommandOld = firstNLCsentenceInFullSentence;
			NLCsentence * lastPhraseBeforeLogicalConditionCommand = firstNLCsentenceInFullSentence;
			
			if(phraseIndexOfFirstLogicalCommand > 0)
			{
				for(int phraseIndex = 0; phraseIndex < phraseIndexOfFirstLogicalCommand; phraseIndex++)
				{
					lastPhraseBeforeLogicalConditionCommand = firstPhraseInLogicalConditionCommandOld;
					firstPhraseInLogicalConditionCommandOld = firstPhraseInLogicalConditionCommandOld->next;
				}
			}

			string firstParsablePhraseReferenceInLogicalConditionCommand = generateMathTextNLPparsablePhraseReference(firstNLCsentenceInFullSentence->sentenceIndex, firstPhraseInLogicalConditionCommandOld);
			int indexOfLogicalConditionCommandInMathText = firstNLCsentenceInFullSentence->mathText.find(firstParsablePhraseReferenceInLogicalConditionCommand);
			if(indexOfLogicalConditionCommandInMathText != CPP_STRING_FIND_RESULT_FAIL_VALUE)
			{
				//disconnect logical condition command parsable phrases from mathText
				
				int indentationOfLogicalCommand = firstNLCsentenceInFullSentence->indentation + 1;
				//cout << "indentationOfLogicalCommand = " << indentationOfLogicalCommand << endl;
				NLCsentence * firstPhraseInLogicalConditionCommand = new NLCsentence();
				firstPhraseInLogicalConditionCommand->indentation = indentationOfLogicalCommand;
				firstPhraseInLogicalConditionCommand->next = firstPhraseInLogicalConditionCommandOld->next;
				firstPhraseInLogicalConditionCommand->sentenceContents = firstPhraseInLogicalConditionCommandOld->sentenceContents;
				if(phraseIndexOfFirstLogicalCommand > 0)
				{
					lastPhraseBeforeLogicalConditionCommand->next = new NLCsentence();
					(*currentNLCsentenceInList) = lastPhraseBeforeLogicalConditionCommand->next;
					*sentenceIndex = firstNLCsentenceInFullSentence->sentenceIndex + phraseIndexOfFirstLogicalCommand;
				}
				else
				{
					firstNLCsentenceInFullSentence->next = new NLCsentence();
					(*currentNLCsentenceInList) = firstNLCsentenceInFullSentence;
					(*currentNLCsentenceInList) = (*currentNLCsentenceInList)->next;
					firstNLCsentenceInFullSentence->sentenceContents = string(NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_DUMMY);
					*sentenceIndex = firstNLCsentenceInFullSentence->sentenceIndex + 1;	//sentenceIndex is unchanged by this assignment		
				}
				
				string mathTextOfLogicalConditionCommand = firstNLCsentenceInFullSentence->mathText.substr(indexOfLogicalConditionCommandInMathText, firstNLCsentenceInFullSentence->mathText.length());
				firstNLCsentenceInFullSentence->mathTextNLPparsablePhraseTotal = phraseIndexOfFirstLogicalCommand;
				firstNLCsentenceInFullSentence->mathText = firstNLCsentenceInFullSentence->mathText.substr(0, indexOfLogicalConditionCommandInMathText);	//remove parsable phrase reference from mathText	//-2 to take into account intermediary comma CHAR_COMMA and white space CHAR_SPACE

				
									
				#ifdef NLC_DEBUG_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
				cout << "detectedLogicalConditionCommand; modified mathText for firstNLCsentenceInFullSentence = " << firstNLCsentenceInFullSentence->mathText << endl;
				cout << "now generateSeparateSentencesFromMathTextAndParsablePhrasesInCommand()... " << endl;
				cout << "sentenceIndex = " << *sentenceIndex << endl;
				#endif
				if(!generateSeparateSentencesFromMathTextAndParsablePhrasesInCommand(currentNLCsentenceInList, firstPhraseInLogicalConditionCommand, mathTextOfLogicalConditionCommand, sentenceIndex, sentenceIndexOfFullSentence, indentationOfLogicalCommand))
				{
					result = false;
				}
				
				maxPhraseIndex = phraseIndexOfFirstLogicalCommand;	//required for automated phrase subject regeneration for phrase subject references based on auxillaries (see below)	
			}
			else
			{
				cout << "splitMathDetectedLineIntoNLPparsablePhrases() error: firstParsablePhraseReferenceInLogicalConditionCommand " << firstParsablePhraseReferenceInLogicalConditionCommand << " not found in mathText " << firstNLCsentenceInFullSentence->mathText << endl;
			}

		}
	}
	#endif
	
	#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
	/*
	if(firstNLCsentenceInFullSentence->hasLogicalConditionOperator)
	{
		//need to parse "is" as equals, eg "if x is 33534"; for all mathText which is not NLP parsable text, replace "is" with "=" 
		//replace all instances of "is" in all mathText which is not NLP parsable text with "="
		firstNLCsentenceInFullSentence->mathText = replaceAllOccurancesOfString(&(firstNLCsentenceInFullSentence->mathText), string(NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_IS_EQUAL_TO_INFORMAL), string(NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_TEST));	//NB this is type sensitive; could be changed in the future

		//"x is equal to number of chickens." is supported by mathText, with "number of chickens" parsable phrase
		//the following cannot be parsed by NLP/GIA; "x is the number of chickens" as dummy numerical variable replacement only works for previously defined variables.; convert to mathText and parsable phrase ("x = the number of chickens")*
	}
	*/

	#ifndef NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
	if(firstNLCsentenceInFullSentence->hasLogicalConditionOperator)
	{
		//how do deal with logical condition commands? eg "if the dog has a ball and [the dog] has an apple, ride the bike."? must detect comma as a new NLP parsable phrase, and any parsable phrase without a starting conjunction as a logical condition command
		if(firstNLCsentenceInFullSentence->mathText[firstNLCsentenceInFullSentence->mathText.length()-1] == NLC_PREPROCESSOR_END_OF_SENTENCE_CHAR)
		{
			if(maxPhraseIndex > 1)
			{
				NLCsentence * currentPhrase2 = firstNLCsentenceInFullSentence;
				for(int phraseIndex = 0; phraseIndex < maxPhraseIndex-1; phraseIndex++)
				{
					currentPhrase2 = currentPhrase2->next;
				}
				//currentPhrase2 is the last phrase in the firstNLCsentenceInFullSentence
				//get first word in line
				
				#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
				cout << "maxPhraseIndex > 1" << endl;
				#endif
				
				string finalParsablePhraseReference = generateMathTextNLPparsablePhraseReference(firstNLCsentenceInFullSentence->sentenceIndex, currentPhrase2);
				int finalParsablePhraseReferencePos = firstNLCsentenceInFullSentence->mathText.rfind(finalParsablePhraseReference);
				if((finalParsablePhraseReferencePos != CPP_STRING_FIND_RESULT_FAIL_VALUE) && (finalParsablePhraseReferencePos == (firstNLCsentenceInFullSentence->mathText.length() - finalParsablePhraseReference.length() - 1)))	//-1 to take into account final NLC_PREPROCESSOR_END_OF_SENTENCE_CHAR
				{//the last text in math text is a parsable phrase; it is therefore a logical condition command candidate
			
					#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
					cout << "finalParsablePhraseReferencePos indicates that the last text in math text is a parsable phrase" << endl;	
					#endif
					
					bool finalParsablePhraseIsLogicalConditionCommand = false;
					//if(firstNLCsentenceInFullSentence->mathText[finalParsablePhraseReferencePos - 2] == CHAR_COMMA)	//-2 to take into account intermediary comma CHAR_COMMA and white space CHAR_SPACE
					int index = firstNLCsentenceInFullSentence->mathText.find(NLC_PREPROCESSOR_MATH_PARSABLE_PHRASE_START_TEXT_INDICATING_LOGICAL_CONDITION_COMMAND, finalParsablePhraseReferencePos - string(NLC_PREPROCESSOR_MATH_PARSABLE_PHRASE_START_TEXT_INDICATING_LOGICAL_CONDITION_COMMAND).length());
					if((index != CPP_STRING_FIND_RESULT_FAIL_VALUE) && (index == 0))
					{
						//e.g. If the basket that is near the house is above the tray, and the basket is blue, the dog is happy.*
						finalParsablePhraseIsLogicalConditionCommand = true;
						cout << "finalParsablePhraseIsLogicalConditionCommand" << endl;
					}
					/*OLD:
					bool finalParsablePhraseIsLogicalConditionCommand = true;
					//NB conjunctions in mathText will already have been replaced with code (so dont check entityCoordinatingConjunctionArray)
					for(int i=0; i<NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_COORDINATING_CONJUNCTION_ARRAY_NUMBER_OF_TYPES; i++)
					{
						int index = firstNLCsentenceInFullSentence->mathText.find(progLangCoordinatingConjunctions[i], finalParsablePhraseReferencePos - progLangCoordinatingConjunctions[i].length() - 1);	//-1 to take into account intermediary white space CHAR_SPACE
						if((index != CPP_STRING_FIND_RESULT_FAIL_VALUE) && (index == 0))
						{
							//"&&"/"||" is the final text in the mathText
							finalParsablePhraseIsLogicalConditionCommand = false;
						}					
					}
					for(int i=0; i<NLC_PREPROCESSOR_MATH_OPERATORS_NUMBER_OF_TYPES; i++)
					{
						int index = firstNLCsentenceInFullSentence->mathText.find(preprocessorMathOperators[i], finalParsablePhraseReferencePos - preprocessorMathOperators[i].length() - 1);	//-1 to take into account intermediary white space CHAR_SPACE
						if((index != CPP_STRING_FIND_RESULT_FAIL_VALUE) && (index == 0))
						{
							//">"/"<"/"="/"+" is the final text in the mathText
							finalParsablePhraseIsLogicalConditionCommand = false;
						}					
					}
					*/							

					if(finalParsablePhraseIsLogicalConditionCommand)
					{
						#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
						cout << "finalParsablePhraseIsLogicalConditionCommand:" << currentPhrase2->sentenceContents << endl;
						#endif
						//disconnect logical condition command parsable phrase from mathText
						maxPhraseIndex = maxPhraseIndex - 1;
						firstNLCsentenceInFullSentence->mathTextNLPparsablePhraseTotal = firstNLCsentenceInFullSentence->mathTextNLPparsablePhraseTotal - 1;
						firstNLCsentenceInFullSentence->mathText = firstNLCsentenceInFullSentence->mathText.substr(0, firstNLCsentenceInFullSentence->mathText.length()-finalParsablePhraseReference.length()-2);	//remove parsable phrase reference from mathText	//-2 to take into account intermediary comma CHAR_COMMA and white space CHAR_SPACE
						//OLD: firstNLCsentenceInFullSentence->mathText = firstNLCsentenceInFullSentence->mathText.substr(0, generateMathTextNLPparsablePhraseReference(sentenceIndexOfFullSentence, currentPhrase2).length());	//remove parsable phrase reference from mathText
						#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
						cout << "finalParsablePhraseIsLogicalConditionCommand; modified mathText = " << firstNLCsentenceInFullSentence->mathText << endl;
						#endif
						currentPhrase2->indentation = currentIndentation + 1;
						currentPhrase2->mathTextNLPparsablePhraseIndex = INT_DEFAULT_VALUE;		
					}
				}
			}
		}
	}
	#endif

	#ifndef NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
	if(firstNLCsentenceInFullSentence->hasLogicalConditionOperator)
	{
	#endif	
		//for logical condition NLP parsable phrases, look for first instance of keywords has/is, and take the preceeding text as the context
		//this enables elimination for need for referencing in conjunctions, eg "if{(}the dog has a ball and [the dog] has an apple{)}"
		//FINISH THIS...
		NLCsentence * currentPhrasePrimarySubject = firstNLCsentenceInFullSentence;
		#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
		cout << "maxPhraseIndex = " << maxPhraseIndex << endl;
		#endif
		for(int phraseIndex=0; phraseIndex<maxPhraseIndex; phraseIndex++)
		{
			#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
			cout << "currentPhrasePrimarySubject->sentenceContents = " << currentPhrasePrimarySubject->sentenceContents << endl; 
			#endif
			bool phraseContainsPrimarySubject = true; 
			for(int i=0; i<NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_AUXILLARY_KEYWORDS_TAGGING_SUBJECT_OR_REFERENCE_NUMBER_OF_TYPES; i++)
			{
				int indexOfAuxillaryTemp = currentPhrasePrimarySubject->sentenceContents.find(preprocessorMathAuxillaryKeywordsTaggingSubjectOrReference[i], 0);
				if((indexOfAuxillaryTemp != CPP_STRING_FIND_RESULT_FAIL_VALUE) && (indexOfAuxillaryTemp == 0))
				{
					#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
					//cout << "phrase: " << currentPhrasePrimarySubject->sentenceContents << ": first word in phrase is an auxillary; it does not contain a subject (does not contain a primary subject)" << endl;
					#endif
					phraseContainsPrimarySubject = false;
				}
			}
			for(int i=0; i<NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_COORDINATING_CONJUNCTION_ARRAY_NUMBER_OF_TYPES; i++)
			{
				string parsablePhraseReference = generateMathTextNLPparsablePhraseReference(sentenceIndexOfFullSentence, currentPhrasePrimarySubject);
				int indexOfParsablePhraseReferenceInMathText = firstNLCsentenceInFullSentence->mathText.find(parsablePhraseReference);
				if(indexOfParsablePhraseReferenceInMathText != CPP_STRING_FIND_RESULT_FAIL_VALUE)
				{
					int expectedPosOfConjunctionIfExistent = indexOfParsablePhraseReferenceInMathText - progLangCoordinatingConjunctions[i].length();
					int indexOfConjunction = firstNLCsentenceInFullSentence->mathText.find(progLangCoordinatingConjunctions[i], expectedPosOfConjunctionIfExistent);	
					if((indexOfConjunction != CPP_STRING_FIND_RESULT_FAIL_VALUE) && (indexOfConjunction == expectedPosOfConjunctionIfExistent))
					{
						#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
						//cout << "phrase: " << currentPhrasePrimarySubject->sentenceContents << ": is preceeded by a conjunction (and/or); it may not contain a subject (and certainly does not contain a primary subject)" << endl;
						#endif
						phraseContainsPrimarySubject = false;
					}
				}
				else
				{
					cout << "splitMathDetectedLineIntoNLPparsablePhrases() error: parsablePhraseReference " << parsablePhraseReference << " not found in mathText " << firstNLCsentenceInFullSentence->mathText << endl;
				}
			}
							
			if(phraseContainsPrimarySubject)
			{	
				#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
				cout << "\nphraseContainsPrimarySubject: " << currentPhrasePrimarySubject->sentenceContents << endl;
				#endif
				
				int indexOfPrimaryAuxillaryTaggingSubject = CPP_STRING_FIND_RESULT_FAIL_VALUE;
				int primaryAuxillaryType;

				bool stillFindingPrimaryAuxillary = true;
				int startPosToSearchForAuxillary = 0;
				while(stillFindingPrimaryAuxillary)
				{
					int indexOfNextClosestAuxillary = NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_MAX_CHARACTERS;
					bool foundAnAuxillaryButItWasIgnored = false;
					int indexOfClosestIgnoredAuxillary = NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_MAX_CHARACTERS;
					for(int i=0; i<NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_AUXILLARY_KEYWORDS_TAGGING_SUBJECT_OR_REFERENCE_NUMBER_OF_TYPES; i++)
					{
						int indexOfAuxillaryTemp = currentPhrasePrimarySubject->sentenceContents.find(preprocessorMathAuxillaryKeywordsTaggingSubjectOrReference[i], startPosToSearchForAuxillary);	
						if((indexOfAuxillaryTemp != CPP_STRING_FIND_RESULT_FAIL_VALUE) && (indexOfAuxillaryTemp < indexOfNextClosestAuxillary))
						{
							//ignore auxillary if has a preceeding 'that'/'which'; eg "the dog that is[ignore] near the house has[take] a ball or has[reference] an apple"
							//"If the basket that is near the house is above the tray, and the basket is blue, the dog is happy."
							//"If the basket that is near the house is above the tray and is blue, the dog is happy.
							bool ignoreAuxillary = false;
							for(int i2=0; i2<NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_RCMOD_SAME_REFERENCE_SET_DELIMITER_NUMBER_OF_TYPES; i2++)
							{
								int expectedPosOfRcmodSameReferenceSetDelimiterIfExistent = indexOfAuxillaryTemp - preprocessorMathRcmodSameReferenceSetDelimiter[i2].length() - 1;
								int indexOfRcmodSameReferenceSet = currentPhrasePrimarySubject->sentenceContents.find(preprocessorMathRcmodSameReferenceSetDelimiter[i2], expectedPosOfRcmodSameReferenceSetDelimiterIfExistent);	
								if((indexOfRcmodSameReferenceSet != CPP_STRING_FIND_RESULT_FAIL_VALUE) && (indexOfRcmodSameReferenceSet == expectedPosOfRcmodSameReferenceSetDelimiterIfExistent))
								{
									ignoreAuxillary = true;
									foundAnAuxillaryButItWasIgnored = true;
									if(indexOfAuxillaryTemp < indexOfClosestIgnoredAuxillary)
									{
										indexOfClosestIgnoredAuxillary = indexOfAuxillaryTemp;
									}
									#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
									//cout << "ignoreAuxillary" << endl;
									#endif
								}
							}

							if(!ignoreAuxillary)
							{
								indexOfNextClosestAuxillary = indexOfAuxillaryTemp;
								primaryAuxillaryType = i;
								#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
								//cout << "found nextClosestAuxillary: " << preprocessorMathAuxillaryKeywordsTaggingSubjectOrReference[i] << ", indexOfNextClosestAuxillary = " << indexOfNextClosestAuxillary << endl;
								#endif
							}
						}
					}
					if(indexOfNextClosestAuxillary != NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_MAX_CHARACTERS)
					{
						indexOfPrimaryAuxillaryTaggingSubject = indexOfNextClosestAuxillary;
						stillFindingPrimaryAuxillary = false;
					}
					else if(foundAnAuxillaryButItWasIgnored)
					{
						startPosToSearchForAuxillary = indexOfClosestIgnoredAuxillary + 1;
						#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
						//cout << "startPosToSearchForAuxillary = indexOfClosestIgnoredAuxillary: " << indexOfClosestIgnoredAuxillary << endl;
						#endif
					}
					else
					{
						stillFindingPrimaryAuxillary = false;
					}
				}

				if(indexOfPrimaryAuxillaryTaggingSubject != CPP_STRING_FIND_RESULT_FAIL_VALUE)
				{
					string subjectText = currentPhrasePrimarySubject->sentenceContents.substr(0, indexOfPrimaryAuxillaryTaggingSubject);	//check -1 is not required
					#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
					cout << "primary auxillary found for phrase: " << currentPhrasePrimarySubject->sentenceContents << ", i = " << indexOfPrimaryAuxillaryTaggingSubject << endl;
					cout << "subjectText = " << subjectText << endl;
					#endif
					
					NLCsentence * currentPhraseReferenceToPrimarySubject = currentPhrasePrimarySubject->next;
					for(int phraseIndex2=phraseIndex+1; phraseIndex2<maxPhraseIndex; phraseIndex2++)					
					{
						//now for each secondary auxillary referencing the subject, artificially generate (copy) the subject text
						#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
						cout << "currentPhraseReferenceToPrimarySubject = " << currentPhraseReferenceToPrimarySubject->sentenceContents << endl;
						cout << "preprocessorMathAuxillaryKeywordsTaggingSubjectOrReference[primaryAuxillaryType] = " << preprocessorMathAuxillaryKeywordsTaggingSubjectOrReference[primaryAuxillaryType] << endl;
						#endif
						int indexOfSecondaryAuxillaryReferencingSubject = currentPhraseReferenceToPrimarySubject->sentenceContents.find(preprocessorMathAuxillaryKeywordsTaggingSubjectOrReference[primaryAuxillaryType]);	
						if((indexOfSecondaryAuxillaryReferencingSubject != CPP_STRING_FIND_RESULT_FAIL_VALUE) && (indexOfSecondaryAuxillaryReferencingSubject == 0))
						{
							//cout << "phrase: " << currentPhraseReferenceToPrimarySubject->sentenceContents << ": found secondary auxillary" << endl;
							bool secondaryChecks = false;
							for(int i=0; i<NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_COORDINATING_CONJUNCTION_ARRAY_NUMBER_OF_TYPES; i++)
							{
								string parsablePhraseReference = generateMathTextNLPparsablePhraseReference(sentenceIndexOfFullSentence, currentPhraseReferenceToPrimarySubject);
								int indexOfParsablePhraseReferenceInMathText = firstNLCsentenceInFullSentence->mathText.find(parsablePhraseReference);
								if(indexOfParsablePhraseReferenceInMathText != CPP_STRING_FIND_RESULT_FAIL_VALUE)
								{
									int expectedPosOfConjunctionIfExistent = indexOfParsablePhraseReferenceInMathText - progLangCoordinatingConjunctions[i].length();
									int indexOfConjunction = firstNLCsentenceInFullSentence->mathText.find(progLangCoordinatingConjunctions[i], expectedPosOfConjunctionIfExistent);	
									if((indexOfConjunction != CPP_STRING_FIND_RESULT_FAIL_VALUE) && (indexOfConjunction == expectedPosOfConjunctionIfExistent))
									{
										#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
										cout << "phrase: " << currentPhraseReferenceToPrimarySubject->sentenceContents << ": phrase is preceeded by a conjunction (and/or); it is a reference to a primary subject" << endl;
										#endif
										secondaryChecks = true;
									}
								}
								else
								{
									cout << "splitMathDetectedLineIntoNLPparsablePhrases() error: parsablePhraseReference " << parsablePhraseReference << " not found in mathText " << firstNLCsentenceInFullSentence->mathText << endl;
								}
							}

							if(secondaryChecks)
							{
								//insert subject content
								#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
								cout << "insert subject content" << endl;
								cout << "old currentPhraseReferenceToPrimarySubject->sentenceContents = " << currentPhraseReferenceToPrimarySubject->sentenceContents << endl;
								#endif
								string parsablePhraseReferenceOld = generateMathTextNLPparsablePhraseReference(sentenceIndexOfFullSentence, currentPhraseReferenceToPrimarySubject);
								
								currentPhraseReferenceToPrimarySubject->sentenceContents.insert(indexOfSecondaryAuxillaryReferencingSubject, subjectText);
						
								string parsablePhraseReferenceNew = generateMathTextNLPparsablePhraseReference(sentenceIndexOfFullSentence, currentPhraseReferenceToPrimarySubject);
								int parsablePhraseReferenceOldPos = firstNLCsentenceInFullSentence->mathText.find(parsablePhraseReferenceOld);
								if(parsablePhraseReferenceOldPos != CPP_STRING_FIND_RESULT_FAIL_VALUE)
								{
									firstNLCsentenceInFullSentence->mathText.replace(parsablePhraseReferenceOldPos, parsablePhraseReferenceOld.length(), parsablePhraseReferenceNew);
								}
								else
								{
									cout << "splitMathDetectedLineIntoNLPparsablePhrases() error: parsablePhraseReferenceOld " << parsablePhraseReferenceOld << " not found in mathText " << firstNLCsentenceInFullSentence->mathText << endl;
								}
								
								#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
								cout << "new currentPhraseReferenceToPrimarySubject->sentenceContents = " << currentPhraseReferenceToPrimarySubject->sentenceContents << endl;
								#endif
							}
						}
						currentPhraseReferenceToPrimarySubject = currentPhraseReferenceToPrimarySubject->next;
					}
				}
			}

			currentPhrasePrimarySubject = currentPhrasePrimarySubject->next;					
		}
	#ifndef NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
	}
	#endif	
	
	/*
	//currently disabled (untested): theoretically allows multiple commands to be defined on a single line separated by conjunctions, eg "X = 3+5 and eat the blue apple" 
	#ifdef NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
	if(!(firstNLCsentenceInFullSentence->hasLogicalConditionOperator))
	{
		#ifdef NLC_DEBUG_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
		cout << "generateSeparateSentencesFromMathTextAndParsablePhrasesInCommand(): " << endl;
		#endif
		if(!generateSeparateSentencesFromMathTextAndParsablePhrasesInCommand(currentNLCsentenceInList, firstNLCsentenceInFullSentence, firstNLCsentenceInFullSentence->mathText, sentenceIndex, sentenceIndexOfFullSentence, currentIndentation))
		{
			result = false;
		}
	}	
	#endif
	*/
	
	if(firstNLCsentenceInFullSentence->hasLogicalConditionOperator)
	{	
		//remove all commas from mathText:
		firstNLCsentenceInFullSentence->mathText = replaceAllOccurancesOfString(&(firstNLCsentenceInFullSentence->mathText), STRING_COMMA, "");
		#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
		cout << "remove all commas from mathText: mathText = " << firstNLCsentenceInFullSentence->mathText << endl;
		#endif
	
		if(firstNLCsentenceInFullSentence->logicalConditionOperator != NLC_LOGICAL_CONDITION_OPERATIONS_ELSE)
		{	
			char lastCharacterInMathText = firstNLCsentenceInFullSentence->mathText[firstNLCsentenceInFullSentence->mathText.length()-1];
			if(lastCharacterInMathText == NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_CLOSE_BRACKET)
			{//NB intermediary white text not currently supported, eg "if (...)"
				#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE_REPLACE_COMMAS_WITH_BRACKETS
				if(additionalClosingBracketRequired)
				{
					firstNLCsentenceInFullSentence->mathText.insert(firstNLCsentenceInFullSentence->mathText.length(), 1, NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_CLOSE_BRACKET);
				}
				#endif
			}
			else
			{
				firstNLCsentenceInFullSentence->mathText.insert(firstNLCsentenceInFullSentence->mathText.length(), 1, NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_CLOSE_BRACKET);
				#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE_REPLACE_COMMAS_WITH_BRACKETS
				if(additionalClosingBracketRequired)
				{
					firstNLCsentenceInFullSentence->mathText.insert(firstNLCsentenceInFullSentence->mathText.length(), 1, NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_CLOSE_BRACKET);
				}	
				#endif
				#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
				cout << "insert CLOSE_BRACKET: mathText = " << firstNLCsentenceInFullSentence->mathText << endl;
				#endif
			}
		}
	}
	#endif
	
	NLCsentence * currentSentence = firstNLCsentenceInFullSentence;
	while(currentSentence->next != NULL)
	{
		*functionContents = *functionContents + currentSentence->sentenceContents + CHAR_NEWLINE;
		currentSentence = currentSentence->next;
	}
	
	return result;
}

#ifdef NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
bool generateLogicalConditionImplicitConjunctionsAndIdentifyCommand(string * lineContentsOrig, bool * detectedLogicalConditionCommand, bool * foundImplicitConjunctions, int * indexOfLogicalConditionCommand)
{
	bool result = true;
	
	*foundImplicitConjunctions = false;
	*detectedLogicalConditionCommand = false;
	string lineContents = *lineContentsOrig;
	
	#ifdef NLC_DEBUG_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
	cout << "generateLogicalConditionImplicitConjunctionsAndIdentifyCommand: lineContents = " << lineContents << endl;
	#endif
	
	NLCsuperphrase * firstNLCsuperphraseInList = new NLCsuperphrase();
	NLCsuperphrase * currentNLCsuperphraseInList = firstNLCsuperphraseInList;
	
	int startPosToSearchForComma = 0;
	int commaIndex = 0;
	bool stillCommasToFind = true;
	while(stillCommasToFind)
	{
		int indexOfNextComma = lineContents.find(CHAR_COMMA, startPosToSearchForComma);	
		if(indexOfNextComma == CPP_STRING_FIND_RESULT_FAIL_VALUE)
		{
			stillCommasToFind = false;
			indexOfNextComma = lineContents.length();
		}
		
		bool conjunctionFoundInSuperphrase = false;
		int conjunctionTypeOfConjunction = INT_DEFAULT_VALUE;
		for(int i=0; i<NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_COORDINATING_CONJUNCTION_ARRAY_NUMBER_OF_TYPES; i++)
		{
			int expectedPosOfConjunctionIfExistent = indexOfNextComma + 1;	//+1 for CHAR_SPACE
			int indexOfConjunctionTemp = lineContents.find(progLangCoordinatingConjunctions[i], expectedPosOfConjunctionIfExistent);	
			if((indexOfConjunctionTemp != CPP_STRING_FIND_RESULT_FAIL_VALUE) && (indexOfConjunctionTemp == 0))
			{
				conjunctionFoundInSuperphrase = true;
				conjunctionTypeOfConjunction = i;
			}
		}

		string superphraseContents = lineContents.substr(startPosToSearchForComma, indexOfNextComma);

		currentNLCsuperphraseInList->phraseContents = superphraseContents;
		currentNLCsuperphraseInList->lineIndexOfFirstCharacterInPhrase = startPosToSearchForComma;
		currentNLCsuperphraseInList->hasConjunction = conjunctionFoundInSuperphrase;
		if(conjunctionFoundInSuperphrase)
		{
			currentNLCsuperphraseInList->conjunctionType = conjunctionTypeOfConjunction;
		}
		
		#ifdef NLC_DEBUG_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
		cout << "generateLogicalConditionImplicitConjunctionsAndIdentifyCommand(): create new NLCsuperphrase" << endl;
		cout << "lineContents = " << lineContents << endl;
		cout << "currentNLCsuperphraseInList->phraseContents = " << currentNLCsuperphraseInList->phraseContents << endl;
		cout << "currentNLCsuperphraseInList->lineIndexOfFirstCharacterInPhrase = " << currentNLCsuperphraseInList->lineIndexOfFirstCharacterInPhrase << endl;
		cout << "currentNLCsuperphraseInList->hasConjunction = " << currentNLCsuperphraseInList->hasConjunction << endl;
		cout << "currentNLCsuperphraseInList->conjunctionType = " << currentNLCsuperphraseInList->conjunctionType << endl;
		#endif
		
		currentNLCsuperphraseInList->next = new NLCsuperphrase();
		currentNLCsuperphraseInList = currentNLCsuperphraseInList->next;
				
		if(stillCommasToFind)
		{
			startPosToSearchForComma = indexOfNextComma + 1;			
		}		
		
		commaIndex++;
	}
	
	int numberOfSuperPhrases = commaIndex;	
	/*
	//now;
	DOING NLC 1h3a - support multiple logical condition commands in one one; NLC_PREPROCESSOR_MATH_SUPPORT_MULTIPLE_LOGICAL_CONDITION_COMMANDS_IN_ONE_LINE eg "if the house is blue, write the letter and read the book"/"else write the letter and read the book."
	DOING NLC 1h3a - support logical condition mathText commands on same line NLC_PREPROCESSOR_MATH_SUPPORT_LOGICAL_CONDITION_MATHTEXT_COMMANDS_ON_SAME_LINE eg "if the house is blue, X = 3+5"
	DOING NLC 1h3a - NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION support implicit conjunctions, eg "if the house is blue, the cat is green, and the bike is tall, ride the bike"
		algorithm: to determine whether text belongs to the logical condition test or command;
			if a phrase without a preceeding conjunction occurs after a phrase with a preceeding conjunction, take this phrase as the start of the logical condition command
				all other phrases without a preceeding conjuction are artifically assigned a preceeding conjunction of type based on the conjunction preceeding the last phrase in the logical condition test of command
		NB with NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION, splitMathDetectedLineIntoNLPparsablePhrases() can be used to support multiple commands on the same line for non-logical conditions; by generating separate NLC sentences for these parsable phrases 
	*/
	
	
	//all other phrases without a preceeding conjuction are artifically assigned a preceeding conjunction of type based on the conjunction preceeding the last phrase in the logical condition test of command
	currentNLCsuperphraseInList = firstNLCsuperphraseInList;
	bool previousPhraseHadConjunction = false;
	bool firstPhrase = true;
	while(currentNLCsuperphraseInList->next != NULL)
	{
		if(firstPhrase)
		{
		
		}
		else if(!(currentNLCsuperphraseInList->hasConjunction))
		{
			NLCsuperphrase * currentNLCsuperphraseInList2 = currentNLCsuperphraseInList;
			bool foundConjunctionOfFuturePhrase = false;
			int conjunctionTypeOfFuturePhrase = INT_DEFAULT_VALUE;
			while(currentNLCsuperphraseInList2->next != NULL)
			{
				if(!foundConjunctionOfFuturePhrase)
				{
					if(currentNLCsuperphraseInList2->hasConjunction)
					{
						foundConjunctionOfFuturePhrase = true;
						conjunctionTypeOfFuturePhrase = currentNLCsuperphraseInList2->conjunctionType;
					}
				}
				currentNLCsuperphraseInList2 = currentNLCsuperphraseInList2->next;
			}
			if(foundConjunctionOfFuturePhrase)
			{
				currentNLCsuperphraseInList->hasConjunction = true;				//redundant
				currentNLCsuperphraseInList->conjunctionType = conjunctionTypeOfFuturePhrase;	//redundant
				//update the lineContents with an artifical conjunction
				#ifdef NLC_DEBUG_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
				cout << "generateLogicalConditionImplicitConjunctionsAndIdentifyCommand(): foundConjunctionOfFuturePhrase" << endl;
				cout << "update the lineContents with an artifical conjunction: currentNLCsuperphraseInList->phraseContents = " << currentNLCsuperphraseInList->phraseContents << endl;
				cout << "old lineContents = " << lineContents << endl;
				#endif
				#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE_REPLACE_COMMAS_WITH_BRACKETS
				lineContents.insert(currentNLCsuperphraseInList->lineIndexOfFirstCharacterInPhrase, progLangCoordinatingConjunctionsWithPause[conjunctionTypeOfFuturePhrase]);
				#else
				lineContents.insert(currentNLCsuperphraseInList->lineIndexOfFirstCharacterInPhrase, progLangCoordinatingConjunctions[conjunctionTypeOfFuturePhrase]);
				#endif
				#ifdef NLC_DEBUG_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
				cout << "new lineContents = " << lineContents << endl;
				#endif
			}
		}
		
		currentNLCsuperphraseInList = currentNLCsuperphraseInList->next;
		firstPhrase = false;
	}
	

		
	//if a phrase without a preceeding conjunction occurs after a phrase with a preceeding conjunction, take this phrase as the start of the logical condition command
	currentNLCsuperphraseInList = firstNLCsuperphraseInList;
	previousPhraseHadConjunction = false;
	firstPhrase = true;
	commaIndex = 0;
	while(currentNLCsuperphraseInList->next != NULL)
	{
		if(firstPhrase)	//redundant
		{
		
		}
		else if(!(currentNLCsuperphraseInList->hasConjunction))
		{
			if(previousPhraseHadConjunction || (commaIndex = numberOfSuperPhrases-1))
			{
				//found first phrase in logical condition command
				#ifdef NLC_DEBUG_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
				cout << "generateLogicalConditionImplicitConjunctionsAndIdentifyCommand(): found first phrase in logical condition command" << endl;
				#endif
				*detectedLogicalConditionCommand = true; 
				*indexOfLogicalConditionCommand = currentNLCsuperphraseInList->lineIndexOfFirstCharacterInPhrase;
			}
		} 
		
		if(currentNLCsuperphraseInList->hasConjunction)
		{
			previousPhraseHadConjunction = true;
		}
		else
		{
			previousPhraseHadConjunction = false;
		}
		
		currentNLCsuperphraseInList = currentNLCsuperphraseInList->next;
		firstPhrase = false;
		commaIndex++;
	}

	*lineContentsOrig = lineContents;
	return result;
}	



bool generateSeparateSentencesFromMathTextAndParsablePhrasesInCommand(NLCsentence ** currentNLCsentenceInList, NLCsentence * firstPhraseInCommand, string mathTextInCommand, int * sentenceIndex, int sentenceIndexOfFullSentence, int currentIndentation)
{	
	int startPosToSearchForConjunction = 0;
	int conjunctionIndex = 0;
	bool stillConjunctionsToFind = true;
	while(stillConjunctionsToFind)
	{
		int indexOfNextConjunction = NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_MAX_CHARACTERS;
		int conjunctionTypeOfNextConjunction = INT_DEFAULT_VALUE;
		for(int i=0; i<NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_COORDINATING_CONJUNCTION_ARRAY_NUMBER_OF_TYPES; i++)
		{
			int indexOfConjunctionTemp = mathTextInCommand.find(progLangCoordinatingConjunctions[i], startPosToSearchForConjunction);	
			if(indexOfConjunctionTemp != CPP_STRING_FIND_RESULT_FAIL_VALUE)
			{
				cout << "mathTextInCommand = " << mathTextInCommand << endl;
				cout << "indexOfConjunctionTemp = " << indexOfConjunctionTemp << endl;
				
				if(indexOfConjunctionTemp < indexOfNextConjunction)
				{
					indexOfNextConjunction = indexOfConjunctionTemp;
					conjunctionTypeOfNextConjunction = i;
					if(i != NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_COORDINATING_CONJUNCTION_AND_INDEX)
					{
						cout << "generateSeparateSentencesFromMathTextAndParsablePhrasesInCommand(): error: command mathText has a conjunction that is not '&&' (and)" << endl;
						exit(0);
					}
				}
			}
		}
		if(indexOfNextConjunction == NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_MAX_CHARACTERS)
		{
			stillConjunctionsToFind = false;
			indexOfNextConjunction = mathTextInCommand.length();
		}
		
		string subCommandContents = mathTextInCommand.substr(startPosToSearchForConjunction, indexOfNextConjunction);
		#ifdef NLC_DEBUG_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
		cout << "generateSeparateSentencesFromMathTextAndParsablePhrasesInCommand(): new conjunction found (or last ~phrase in list)" << endl;
		cout << "mathTextInCommand = " << mathTextInCommand << endl;
		cout << "subCommandContents = " << subCommandContents << endl;
		#endif
		
		NLCsentence * fullSentenceInCommand = (*currentNLCsentenceInList);
		(*currentNLCsentenceInList)->mathText = mathTextInCommand;
		(*currentNLCsentenceInList)->isMath = true;
		(*currentNLCsentenceInList)->sentenceContents = "";
		
		NLCsentence * currentPhraseInCommand = firstPhraseInCommand;
		int phraseIndexInSubCommand = 0;
		while(currentPhraseInCommand->next != NULL)
		{
			#ifdef NLC_DEBUG_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
			cout << "currentPhraseInCommand->sentenceContents = " << currentPhraseInCommand->sentenceContents << endl;
			#endif
			
			string parsablePhraseReference = generateMathTextNLPparsablePhraseReference(sentenceIndexOfFullSentence, currentPhraseInCommand);
			int indexOfParsablePhraseReferenceInSubCommand = subCommandContents.find(parsablePhraseReference);
			string parsablePhraseReferenceWithAppendedFullstop = parsablePhraseReference + NLC_PREPROCESSOR_END_OF_SENTENCE_CHAR;
			if(indexOfParsablePhraseReferenceInSubCommand != CPP_STRING_FIND_RESULT_FAIL_VALUE)
			{	
				//reference to currentPhraseInCommand is in subCommandContents
				#ifdef NLC_DEBUG_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
				cout << "parsablePhraseReference = " << parsablePhraseReference << endl;
				#endif
				if((parsablePhraseReferenceWithAppendedFullstop == mathTextInCommand) && (conjunctionIndex == 0) && !stillConjunctionsToFind)	//check the "(parsablePhraseReference == mathTextInCommand)" exact test is sufficient (or if white space can be allowed either side of test)
				{
					//no mathText detected
					#ifdef NLC_DEBUG_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
					cout << "generateSeparateSentencesFromMathTextAndParsablePhrasesInCommand(): no mathText detected in subcommand: " << mathTextInCommand << endl;
					#endif
					(*currentNLCsentenceInList)->mathText = "";
					(*currentNLCsentenceInList)->isMath = false;
					(*currentNLCsentenceInList)->indentation = currentIndentation;
					(*currentNLCsentenceInList)->sentenceContents = currentPhraseInCommand->sentenceContents;
					(*currentNLCsentenceInList)->sentenceIndex = (*sentenceIndex);
					(*currentNLCsentenceInList)->mathTextNLPparsablePhraseTotal = 0;
					(*currentNLCsentenceInList)->next = new NLCsentence();
					(*currentNLCsentenceInList) = (*currentNLCsentenceInList)->next;
					(*sentenceIndex) = (*sentenceIndex) + 1;				
				}
				else
				{
					#ifdef NLC_DEBUG_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
					cout << "generateSeparateSentencesFromMathTextAndParsablePhrasesInCommand(): mathText detected in subcommand: " << mathTextInCommand << endl;
					#endif
					(*currentNLCsentenceInList)->mathTextNLPparsablePhraseIndex = phraseIndexInSubCommand;
					(*currentNLCsentenceInList)->indentation = currentIndentation;
					(*currentNLCsentenceInList)->sentenceContents = currentPhraseInCommand->sentenceContents;
					(*currentNLCsentenceInList)->sentenceIndex = (*sentenceIndex);
					fullSentenceInCommand->mathTextNLPparsablePhraseTotal = fullSentenceInCommand->mathTextNLPparsablePhraseTotal + 1;
					(*currentNLCsentenceInList)->next = new NLCsentence();
					(*currentNLCsentenceInList) = (*currentNLCsentenceInList)->next;
					(*sentenceIndex) = (*sentenceIndex) + 1;	
					
					phraseIndexInSubCommand++;
				}		
			}

			currentPhraseInCommand = currentPhraseInCommand->next;
		}

		if(stillConjunctionsToFind)		
		{	
			startPosToSearchForConjunction = indexOfNextConjunction + 1;
		}
		
				
		conjunctionIndex++;
	}			
}


#endif
	
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

bool replaceNumericalVariablesWithDummyNameIfNecessary(string * lineContents, NLCsentence * currentNLCsentenceInList, NLCfunction * currentNLCfunctionInList, NLCfunction * firstNLCfunctionInList)
{
	bool result = true;
	#ifdef NLC_DEBUG_PREPROCESSOR_MATH_REPLACE_NUMERICAL_VARIABLES
	cout << "replaceNumericalVariablesWithDummyNameIfNecessary: lineContents = " << *lineContents << endl;
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

bool findPredefinedNumericalVariable(string * currentWord, NLCfunction * currentNLCfunctionInList, NLCfunction * firstNLCfunctionInList, NLCsentence * sentenceToIgnoreWhileSearching)
{
	#ifdef NLC_PREPROCESSOR_REPLACE_NUMERICAL_VARIABLES_DETECT_GLOBAL_NUMERICAL_VARIABLES
	return findPredefinedNumericalVariableInAnyFunctions(currentWord, firstNLCfunctionInList, sentenceToIgnoreWhileSearching);
	#else
	return findPredefinedNumericalVariableInFunction(currentWord, currentNLCfunctionInList, sentenceToIgnoreWhileSearching);	
	#endif
}

#ifdef NLC_PREPROCESSOR_REPLACE_NUMERICAL_VARIABLES_DETECT_GLOBAL_NUMERICAL_VARIABLES
bool findPredefinedNumericalVariableInAnyFunctions(string * currentWord, NLCfunction * firstNLCfunctionInList, NLCsentence * sentenceToIgnoreWhileSearching)
{
	bool result = false;
	currentNLCfunctionInList = firstNLCfunctionInList;
	while(currentNLCfunctionInList->next != NULL)
	{
		NLCsentence * currentNLCsentenceInList = currentNLCfunctionInList->firstNLCsentenceInFunction;
		if(findPredefinedNumericalVariableInFunction(currentWord, currentNLCfunctionInList, sentenceToIgnoreWhileSearching)
		{
			result = true;
		}
	
		currentNLCfunctionInList = currentNLCfunctionInList->next;
	}
	return result;
}
#endif

bool findPredefinedNumericalVariableInFunction(string * currentWord, NLCfunction * currentNLCfunctionInList, NLCsentence * sentenceToIgnoreWhileSearching)	//pass firstNLCfunctionInList and update findPredefinedNumericalVariable() accordingly to allow global numerical variable definitions; not just local numerical variable definitions
{
	bool result = false;

	NLCsentence * currentNLCsentenceInList = currentNLCfunctionInList->firstNLCsentenceInFunction;
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
		
int generateDummyNumericalValue(int predefinedVariableIndex)
{
	int dummyNumericalValue = predefinedVariableIndex + NLC_PREPROCESSOR_MATH_DUMMY_NUMERICAL_VALUE_BASE;
	return dummyNumericalValue;
}
				
#endif


#endif

#endif




