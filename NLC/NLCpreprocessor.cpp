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
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2016 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 1u2c 26-September-2016
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/


#include "NLCpreprocessor.h"
#include "NLCpreprocessorSentenceClass.h"
#include "NLCpreprocessorMath.h"
#include "NLCpreprocessorMathLogicalConditions.h"

//#include "NLCprintDefs.h" //required for progLangOpenParameterSpace
#include "SHAREDvars.h"	//required for convertStringToLowerCase/isWhiteSpace
#include "GIAentityNodeClass.h" //required for GIA_NLP_START_SENTENCE_INDEX and entityNodesActiveListComplete
#include "GIAlrp.h"	//requied for isIntrawordPunctuationMark, nlpQuotationMarkCharacterArray/GIA_TRANSLATOR_UNIQUE_CONCATENATION_TYPES_QUOTES_DELIMITER

#ifdef NLC_USE_PREPROCESSOR

bool preprocessTextForNLC(string inputFileName, NLCfunction* firstNLCfunctionInList, bool* detectedFunctions, int* numberOfInputFilesInList, vector<string>* inputTextFileNameList, string outputFileName)
{
	*numberOfInputFilesInList = 1;

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
		setCurrentDirectory(tempFolder);	//save output files to temp folder

		NLCfunction* currentNLCfunctionInList = firstNLCfunctionInList;
		NLCsentence* currentNLCsentenceInList = currentNLCfunctionInList->firstNLCsentenceInFunction;
		string currentLine;
		int sentenceIndex = GIA_NLP_START_SENTENCE_INDEX;
		*detectedFunctions = false;
		string functionContents = "";
		string NLCfunctionName = "";
		string functionFileName = "";	//with NLCfunctionName with extension
		int currentLineNumber = 0;

		while(getline(parseFileObject, currentLine))
		{
			currentLineNumber++;
			#ifdef NLC_DEBUG_PREPROCESSOR
			cout << currentLineNumber << ": " << currentLine << endl;
			#endif

			#ifndef NLC_USE_MATH_OBJECTS_ADVANCED
			#ifdef NLC_PREPROCESSOR_REDUCE_QUOTES_TO_SINGLE_WORDS
			string updatedLineTextWithQuotationsReducedToSingleWords = "";
			if(reduceQuotesToSingleWords(currentLine, &updatedLineTextWithQuotationsReducedToSingleWords))
			{
				currentLine = updatedLineTextWithQuotationsReducedToSingleWords;
			}
			#endif
			#endif

			#ifdef NLC_SUPPORT_INPUT_FUNCTION_LISTS_PREPROCESSOR
			if(detectFunctionHeader(&currentLine))
			{
				//extract functions from file and generate separate files
				if(*detectedFunctions)
				{
					#ifdef NLC_DEBUG_PREPROCESSOR
					cout << "end function: NLCfunctionName = " << NLCfunctionName << endl;
					cout << "create new function = " << NLCfunctionName << endl;
					cout << "functionContents = " << functionContents << endl;
					#endif
					writeStringToFile(functionFileName, &functionContents);
					currentNLCfunctionInList->NLCfunctionName = NLCfunctionName;
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
				NLCfunctionName = getFunctionNameFromFunctionHeader(&currentLine);		//NLCfunctionName
				functionFileName = generateNLCfunctionFileName(NLCfunctionName);
				inputTextFileNameList->push_back(functionFileName);
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

				#ifdef NLC_PREPROCESSOR_GENERATE_COMMENTS
				currentNLCsentenceInList->sentenceOriginal = lineContents;
				#endif

				#ifdef NLC_PREPROCESSOR_MATH

				int lineLogicalConditionOperator;
				if(detectLogicalConditionOperatorAtStartOfLine(&lineContents, &lineLogicalConditionOperator))
				{
					#ifdef NLC_DEBUG
					//cout << "hasLogicalConditionOperator" << endl;
					#endif
					currentNLCsentenceInList->hasLogicalConditionOperator = true;
					#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
					currentNLCsentenceInList->logicalConditionOperator = lineLogicalConditionOperator;
					currentNLCsentenceInList->isMath = true;
					#endif
				}
				else
				{
					if(detectMathSymbolsInLine(&lineContents))
					{
						currentNLCsentenceInList->isMath = true;
					}

					//#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
					if(detectAndReplaceIsEqualToNonLogicalConditionTextWithSymbol(&lineContents, currentNLCsentenceInList->hasLogicalConditionOperator, currentNLCsentenceInList->isMath))
					{
						currentNLCsentenceInList->isMath = true;
					}
					//#endif
				}

				if(currentNLCsentenceInList->isMath)
				{
					#ifdef NLC_DEBUG_PREPROCESSOR_MATH
					cout << "splitMathDetectedLineIntoNLPparsablePhrases{}:" << endl;
					#endif
					#ifdef NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
					bool detectedLogicalConditionCommand = false;
					NLCsentence* firstSentenceInLogicalConditionCommandTemp = new NLCsentence();
					if(currentNLCsentenceInList->hasLogicalConditionOperator)
					{
						splitMathDetectedLineLogicalConditionCommandIntoSeparateSentences(&lineContents, currentIndentation, currentNLCsentenceInList, firstSentenceInLogicalConditionCommandTemp, &detectedLogicalConditionCommand);
					}
					#endif

					splitMathDetectedLineIntoNLPparsablePhrases(&lineContents, &currentNLCsentenceInList, &sentenceIndex, currentIndentation, &functionContents, currentNLCfunctionInList, firstNLCfunctionInList);

					#ifdef NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
					if(detectedLogicalConditionCommand)
					{
						NLCsentence* currentSentenceInLogicalConditionCommandTemp = firstSentenceInLogicalConditionCommandTemp;
						while(currentSentenceInLogicalConditionCommandTemp->next != NULL)
						{
							if(detectMathSymbolsInLine(&(currentSentenceInLogicalConditionCommandTemp->sentenceContents)))
							{
								splitMathDetectedLineIntoNLPparsablePhrases(&(currentSentenceInLogicalConditionCommandTemp->sentenceContents), &currentNLCsentenceInList, &sentenceIndex, currentSentenceInLogicalConditionCommandTemp->indentation, &functionContents, currentNLCfunctionInList, firstNLCfunctionInList);
							}
							else
							{
								addNonLogicalConditionSentenceToList(&(currentSentenceInLogicalConditionCommandTemp->sentenceContents), &currentNLCsentenceInList, &sentenceIndex,  currentSentenceInLogicalConditionCommandTemp->indentation, currentNLCfunctionInList, firstNLCfunctionInList);
								functionContents = functionContents + (currentSentenceInLogicalConditionCommandTemp->sentenceContents) + CHAR_NEWLINE;
							}
							currentSentenceInLogicalConditionCommandTemp = currentSentenceInLogicalConditionCommandTemp->next;
						}
					}
					#endif
				}
				else
				{
				#endif

					functionContents = functionContents + indentationContents;

					//now for each sentence on line:
					int startOfSentenceIndex = 0;
					bool stillSentenceToParseOnLine = true;
					while(stillSentenceToParseOnLine)
					{
						bool lineFullStopDetected = false;
						#ifdef NLC_DEBUG
						//cout << "stillSentenceToParseOnLine: lineContents = " << lineContents << endl;
						#endif
						#ifdef NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_SUPPORT_FILENAMES_WITH_FULLSTOPS
						int startOfSentenceIndexNew = startOfSentenceIndex;
						#ifdef NLC_DEBUG
						//cout << "lineContents.length = " << lineContents.length() << endl;
						#endif
						bool stillFinding = true;
						while(stillFinding)
						{
							startOfSentenceIndexNew = lineContents.find(NLC_PREPROCESSOR_END_OF_SENTENCE_CHAR, startOfSentenceIndexNew);
							if(startOfSentenceIndexNew != CPP_STRING_FIND_RESULT_FAIL_VALUE)
							{
								//based on isIntrawordFullStop() code:
								#ifdef NLC_DEBUG
								//cout << "startOfSentenceIndexNew1 = " << startOfSentenceIndexNew << endl;
								#endif
								if(isIntrawordPunctuationMark(startOfSentenceIndexNew, &lineContents))
								{
									//cout << "isIntrawordPunctuationMark" << endl;
									startOfSentenceIndexNew = startOfSentenceIndexNew+1;
								}
								else
								{
									lineFullStopDetected = true;
									stillFinding = false;
								}
								#ifdef NLC_DEBUG
								//cout << "startOfSentenceIndexNew2 = " << startOfSentenceIndexNew << endl;
								#endif
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
							#ifdef NLC_DEBUG_PREPROCESSOR
							cout << "lineFullStopDetected" << endl;
							#endif
							sentenceContents = lineContents.substr(startOfSentenceIndex, startOfSentenceIndexNew-startOfSentenceIndex+1);	//+1 append the full stop
							#ifdef NLC_DEBUG
							//cout << "sentenceContents = " << sentenceContents << endl;
							#endif

						}
						else
						{
							#ifdef NLC_DEBUG_PREPROCESSOR
							cout << "!lineFullStopDetected" << endl;
							#endif
							sentenceContents = lineContents.substr(startOfSentenceIndex, lineContents.length());

						}
						#ifdef NLC_PREPROCESSOR_GENERATE_COMMENTS
						currentNLCsentenceInList->sentenceContentsOriginal = removePrependingWhiteSpace(sentenceContents);
						#endif

						#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED

						#ifdef NLC_PREPROCESSOR_MATH
						#ifdef NLC_PREPROCESSOR_MATH_REPLACE_NUMERICAL_VARIABLES_NAMES_FOR_NLP
						replaceNumericalVariablesWithDummyNumberIfNecessary(&sentenceContents, currentNLCsentenceInList, currentNLCfunctionInList, firstNLCfunctionInList);
						#endif
						#endif
						#ifdef NLC_DEBUG
						//cout << "sentenceContents = " << sentenceContents << endl;
						#endif

						#ifdef NLC_USE_MATH_OBJECTS_ADVANCED
						if(detectMathObjectStringDelimiter(&sentenceContents))
						{
							cout << "preprocessTextForNLC{} error: quotation marks detected without mathtext expression (illegal: 'Print \"this text\"'. legal: 'the value = \"this text\". print the value.')" << endl;
						}
						#endif

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
						}
						#else
						//error checking only:
						int sentenceLogicalConditionOperator;
						if(detectLogicalConditionOperatorAtStartOfLine(&sentenceContents, &sentenceLogicalConditionOperator))
						{
							cout << "preprocessTextForNLC{} error: !NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED && !(currentNLCsentenceInList->isMath) && detectLogicalConditionOperatorAtStartOfLine" << endl;
						}
						#endif

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
									#ifdef NLC_DEBUG
									//cout << "nonWhiteSpaceDetectedBetweenFinalFullStopAndEndOfLine" << endl;
									#endif
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
										cout << "NLC_USE_PREPROCESSOR preprocessTextForNLC{} error: \"else\" logical condition operation detected in combination with an incomplete command (no full stop): sentenceContents = " << sentenceContents << endl;
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
								cout << "NLC_USE_PREPROCESSOR preprocessTextForNLC{} error: NLC_PREPROCESSOR_SUPPORT_MULTILINE_SENTENCES are not currently supported" << endl;
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
							addNonLogicalConditionSentenceToList(&sentenceContents, &currentNLCsentenceInList, &sentenceIndex, currentIndentation, currentNLCfunctionInList, firstNLCfunctionInList);

							if(startOfSentenceIndexNew == lineContents.length()-1)
							{
								#ifdef NLC_DEBUG
								//cout << "stillSentenceToParseOnLine = false" << endl;
								#endif
								stillSentenceToParseOnLine = false;
							}
						}
						functionContents = functionContents + sentenceContents + CHAR_NEWLINE;
						startOfSentenceIndex = startOfSentenceIndexNew + 1;	//is +1 required? (to prevent current NLC_PREPROCESSOR_END_OF_SENTENCE_CHAR/CHAR_FULLSTOP from being redetected)
					}


				#ifdef NLC_PREPROCESSOR_MATH
				}
				#endif

			#ifdef NLC_SUPPORT_INPUT_FUNCTION_LISTS_PREPROCESSOR
			}
			#endif
		}

		#ifdef NLC_SUPPORT_INPUT_FUNCTION_LISTS_PREPROCESSOR
		if(*detectedFunctions)
		{
			//create a final function based on the final text..
			#ifdef NLC_DEBUG_PREPROCESSOR
			cout << "create new function, functionFileName = " << functionFileName << endl;
			cout << "functionContents = " << functionContents << endl;
			#endif
			writeStringToFile(functionFileName, &functionContents);
			//create new function file based on current text
		}
		else
		{
		#endif
			#ifdef NLC_DEBUG_PREPROCESSOR
			cout << "create preprocessed file, outputFileName = " << outputFileName << endl;
			cout  << "functionContents = \n" << functionContents << endl;
			#endif
			writeStringToFile(outputFileName, &functionContents);
		#ifdef NLC_SUPPORT_INPUT_FUNCTION_LISTS_PREPROCESSOR
		}
		#endif

		setCurrentDirectory(workingFolder);	//set current directory back to the original workingFolder (this is required for both NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS and GIA, even if the GIA's workingFolder is changed to tempFolder as it should be in the case of NLC preprocessed input)
	}

	#ifdef NLC_PREPROCESSOR_PRINT_OUTPUT
	NLCsentence* currentNLCsentenceInList = firstNLCfunctionInList->firstNLCsentenceInFunction;
	while(currentNLCsentenceInList->next != NULL)
	{
		for(int i=0;i<currentNLCsentenceInList->indentation; i++)
		{
			cout << "\t";
		}
		cout << currentNLCsentenceInList->sentenceContents;
		cout << "(sentenceIndex: " << currentNLCsentenceInList->sentenceIndex << ") ";
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

	#ifdef NLC_DEBUG_PREPROCESSOR_PREMATURE_QUIT
	cout << "Premature quit for debug" << endl;
	exit(0);
	#endif


	NLCsentence* currentSentence = firstNLCfunctionInList->firstNLCsentenceInFunction;
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
		currentSentence = currentSentence->next;
	}


	return result;
}

void addNonLogicalConditionSentenceToList(string* sentenceContents, NLCsentence** currentNLCsentenceInList, int* sentenceIndex, int currentIndentation, NLCfunction* currentNLCfunctionInList, NLCfunction* firstNLCfunctionInList)
{
	#ifdef NLC_PREPROCESSOR_MATH
	#ifdef NLC_PREPROCESSOR_MATH_REPLACE_NUMERICAL_VARIABLES_NAMES_FOR_NLP
	replaceNumericalVariablesWithDummyNumberIfNecessary(sentenceContents, *currentNLCsentenceInList, currentNLCfunctionInList, firstNLCfunctionInList);
	#endif
	#endif
	#ifdef NLC_DEBUG
	//cout << "sentenceContents = " << sentenceContents << endl;
	#endif

	#ifdef NLC_USE_MATH_OBJECTS_ADVANCED
	if(detectMathObjectStringDelimiter(sentenceContents))
	{
		cout << "preprocessTextForNLC{} error: quotation marks detected without mathtext expression (illegal: 'Print \"this text\"'. legal: 'the value = \"this text\". print the value.')" << endl;
	}
	#endif

	#ifdef NLC_PREPROCESSOR_INTERPRET_SINGLE_WORD_SENTENCES_AS_ACTIONS
	if(isStringValidVariableName(*sentenceContents, true))
	{
		#ifdef NLC_PREPROCESSOR_INTERPRET_SINGLE_WORD_SENTENCES_AS_ACTIONS_REPLACE_ACTION_ALSO_DUE_TO_NLP_LIMITATION
		string actionName = sentenceContents->substr(0, sentenceContents->length()-1);
		(*currentNLCsentenceInList)->singleWordSentenceActionName = actionName;
		*sentenceContents = "" + NLC_PREPROCESSOR_INTERPRET_SINGLE_WORD_SENTENCES_AS_ACTIONS_DUMMY_TEXT_ACTION_FULL + STRING_FULLSTOP;
		#else
		*sentenceContents = "" + actionName + NLC_PREPROCESSOR_INTERPRET_SINGLE_WORD_SENTENCES_AS_ACTIONS_DUMMY_TEXT_ACTION_OBJECT_FULL + STRING_FULLSTOP; //sentenceContents = sentenceContents.insert((sentenceContents.length()-1), NLC_PREPROCESSOR_INTERPRET_SINGLE_WORD_SENTENCES_AS_ACTIONS_DUMMY_TEXT_ACTION_OBJECT_FULL);
		#endif
		#ifdef NLC_DEBUG
		//cout << "sentenceContents = " << sentenceContents << endl;
		#endif
	}
	#endif

	#ifdef NLC_DEBUG_PREPROCESSOR
	cout << "create new sentence" << endl;
	cout << sentenceIndex << ": sentenceContents = " << sentenceContents << endl;
	#endif
	(*currentNLCsentenceInList)->sentenceContents = *sentenceContents;	//full stop should already be appended
	(*currentNLCsentenceInList)->sentenceIndex = (*sentenceIndex);
	(*currentNLCsentenceInList)->indentation = currentIndentation;
	(*currentNLCsentenceInList)->next = new NLCsentence();
	(*currentNLCsentenceInList) = (*currentNLCsentenceInList)->next;
	(*sentenceIndex)++;
}

#ifdef NLC_PREPROCESSOR_REDUCE_QUOTES_TO_SINGLE_WORDS
bool reduceQuotesToSingleWords(string lineText, string* updatedLineText)
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

	#ifdef NLC_DEBUG_PREPROCESSOR
	if(result)
	{
		cout << "reduceQuotesToSingleWords{}:" << endl;
		cout << "lineText = " << lineText << endl;
		cout << "*updatedLineText = " << *updatedLineText << endl;
	}
	#endif
	return result;
}
#endif


void extractIndentationFromCurrentLine(string* currentLine, int* currentIndentation, string* lineContents, string* indentationContents)
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

#ifdef NLC_SUPPORT_INPUT_FUNCTION_LISTS_PREPROCESSOR
bool detectFunctionHeader(string* lineContents)
{
	bool functionHeaderFound = false;
	int index = lineContents->find(string(NLC_PREPROCESSOR_FUNCTION_HEADER_STRING));
	if((index != CPP_STRING_FIND_RESULT_FAIL_VALUE) && (index == 0))
	{
		functionHeaderFound = true;
		#ifdef NLC_DEBUG
		//cout << "detectFunctionHeader{}: functionHeaderFound = " << NLC_PREPROCESSOR_FUNCTION_HEADER_STRING << endl;
		#endif
	}
	return functionHeaderFound;
}
string getFunctionNameFromFunctionHeader(string* lineContents)
{
	string NLCfunctionName = lineContents->substr(string(NLC_PREPROCESSOR_FUNCTION_HEADER_STRING).length() + string(NLC_PREPROCESSOR_FUNCTION_HEADER_MID_CHAR).length());
	#ifdef NLC_DEBUG
	//cout << "getFunctionNameFromFunctionHeader{}: NLCfunctionName = " << NLCfunctionName << endl;
	#endif
	return NLCfunctionName;

}
string generateNLCfunctionFileName(string NLCfunctionName)
{
	string functionFileName = NLCfunctionName + NLC_NATURAL_LANGUAGE_CODE_FILE_NAME_EXTENSION;	//NLC_NATURAL_LANGUAGE_CODE_FILE_NAME_EXTENSION added 1m5a
	return functionFileName;
}
#endif

bool detectLogicalConditionOperatorAtStartOfLine(string* lineContents, int* logicalConditionOperator)
{
	#ifdef NLC_DEBUG
	//cout << "detectLogicalConditionOperatorAtStartOfLine() lineContents = " <<* lineContents << endl;
	#endif

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
			cout << "detectLogicalConditionOperatorAtStartOfLine{}: logicalConditionOperatorFound" << logicalConditionOperationsArray[i] << endl;
			#endif
		}
	}
	return logicalConditionOperatorFound;
}

string removePrependingWhiteSpace(string sentenceContents)
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

#ifdef NLC_USE_MATH_OBJECTS_ADVANCED
bool detectMathObjectStringDelimiter(string* lineContents)
{
	bool result = false;
	if(lineContents->find(NLC_USE_MATH_OBJECTS_STRING_DELIMITER_CHAR) != CPP_STRING_FIND_RESULT_FAIL_VALUE)
	{
		result = true;
	}
	return result;
}
#endif

#endif






