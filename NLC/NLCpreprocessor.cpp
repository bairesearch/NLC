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
 * Project Version: 1g17a 17-July-2014
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/



#include <ctime>
#include <cstdlib>	//for random number generation
#include <cmath>

#include "NLCpreprocessor.h"
#include "GIAentityNodeClass.h" //required for GIA_NLP_START_SENTENCE_INDEX
#include "SHAREDvars.h"	//required for convertStringToLowerCase/isWhiteSpace

NLCsentence::NLCsentence(void)
{
	sentenceContents = "";
	sentenceIndex = 0;
	indentation = 0;
	#ifdef NLC_PREPROCESSOR_LOGICAL_CONDITION_USE_ROBUST_NLP_INDEPENDENT_CODE
	elseDetected = false;
	elseIfDetected = false;
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
		char currentToken;
		int sentenceIndex = GIA_NLP_START_SENTENCE_INDEX;
		int currentIndentation = 0;
		bool parsingIndentation = true;
		bool parsingFunctionName = false;
		string functionName = "";
		*detectedFunctions = false;
		string functionContents = "";
		string sentenceContents = "";
		bool lineFullStopDetected = false;
		#ifdef NLC_SUPPORT_CONDITION_LOGICAL_OPERATIONS
		bool lineIsLogicalCondition = false;
		bool elseDetected = false;
		#endif
		bool lineNonWhiteSpaceDetected = false;
		
		while(parseFileObject.get(currentToken))
		{
			#ifdef NLC_DEBUG_PREPROCESSOR
			cout << currentToken;
			#endif
			bool whiteSpaceDetected = isWhiteSpace(currentToken);

			#ifdef NLC_SUPPORT_INPUT_FILE_LISTS
			//extract functions from file and generate separate files
			if(parsingFunctionName)
			{
				if(currentToken == CHAR_NEWLINE)
				{
					#ifdef NLC_DEBUG_PREPROCESSOR
					cout << "start function: functionName = " << functionName << endl;
					#endif
					inputTextFileNameList->push_back(functionName);
					functionContents = "";
					sentenceContents = "";
					currentIndentation = 0;
					parsingFunctionName = false;
					lineFullStopDetected = false;
					#ifdef NLC_SUPPORT_CONDITION_LOGICAL_OPERATIONS
					lineIsLogicalCondition = false;
					elseDetected = false;
					#endif
					lineNonWhiteSpaceDetected = false;
				}
				else
				{
					functionName = functionName + currentToken;
				}
			}
			else
			{
			#endif
				if(currentToken == CHAR_NEWLINE)
				{
					#ifdef NLC_SUPPORT_CONDITION_LOGICAL_OPERATIONS
					if(!lineFullStopDetected && lineIsLogicalCondition)
					{
						string lowerCaseSentenceContents = convertStringToLowerCase(&sentenceContents);
						string dummyCommand = "";
						if(elseDetected || (lowerCaseSentenceContents == NLC_LOGICAL_CONDITION_OPERATIONS_ELSE))
						{
							if(sentenceContents.length() == (string(NLC_LOGICAL_CONDITION_OPERATIONS_ELSE)).length())
							{
								//sentence was originally "Else" and has not yet been converted to "If this is done,"
								
								lineIsLogicalCondition = true;
								#ifdef NLC_PREPROCESSOR_LOGICAL_CONDITION_USE_ROBUST_NLP_INDEPENDENT_CODE
								currentNLCsentenceInList->elseDetected = true;
								#endif
								elseDetected = true;
								//replace "else" with "If this is done, "
								sentenceContents = string(NLC_PREPROCESSOR_LOGICAL_CONDITION_DUMMY_TEXT_TEST_ELSE) + sentenceContents.substr(string(NLC_LOGICAL_CONDITION_OPERATIONS_ELSE).length(), sentenceContents.length()-string(NLC_LOGICAL_CONDITION_OPERATIONS_ELSE).length());
								functionContents = functionContents.substr(0, functionContents.length()-lowerCaseSentenceContents.length()) + sentenceContents;	//"lowerCaseSentenceContents.length()" is just used to measure the original length of the sentenceContents 
						
								dummyCommand = NLC_PREPROCESSOR_LOGICAL_CONDITION_DUMMY_TEXT_COMMAND_ELSE;	//append dummy action " do this."
							}
							else if(sentenceContents.length() == string(NLC_LOGICAL_CONDITION_OPERATIONS_ELSE).length()+1)
							{
								//sentence was originally "Else " and has been converted to "If this is done,"
								dummyCommand = NLC_PREPROCESSOR_LOGICAL_CONDITION_DUMMY_TEXT_COMMAND_ELSE;	//append dummy action " do this."
							}
							else
							{
								//sentence was originally "else ___" and has been converted to "If this is done, ___" - it is invalid because it does not contain a full stop.
								cout << "NLC_USE_PREPROCESSOR preprocessTextForNLC() error: \"else\" logical condition operation detected in combination with an incomplete command (no full stop)" << endl;
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
						currentNLCsentenceInList->sentenceContents = sentenceContents + string(dummyCommand);
						functionContents = functionContents + string(dummyCommand);	
						currentNLCsentenceInList->sentenceIndex = sentenceIndex;
						currentNLCsentenceInList->indentation = currentIndentation;
						currentNLCsentenceInList->next = new NLCsentence();
						currentNLCsentenceInList = currentNLCsentenceInList->next;
						sentenceContents = "";
						sentenceIndex++;
					}
					else 
					#endif
					if(!lineFullStopDetected && lineNonWhiteSpaceDetected)
					{
						cout << "NLC_USE_PREPROCESSOR preprocessTextForNLC() error: NLC_PREPROCESSOR_SUPPORT_MULTILINE_SENTENCES are not currently supported" << endl;
						exit(0);
					}
					else
					{
						//assume that a sentence has already been created based on a full stop (do not support multiline sentences)
					}
					parsingIndentation = true;
					currentIndentation = 0;
					lineFullStopDetected = false;
					#ifdef NLC_SUPPORT_CONDITION_LOGICAL_OPERATIONS
					lineIsLogicalCondition = false;
					elseDetected = false;
					#endif
					lineNonWhiteSpaceDetected = false;
				}
				else if(currentToken == CHAR_FULLSTOP)
				{
					if(lineNonWhiteSpaceDetected)
					{
						lineFullStopDetected = true;
						parsingIndentation = false;
						#ifdef NLC_DEBUG_PREPROCESSOR
						cout << "create new sentence" << endl;
						cout << "sentenceContents = " << sentenceContents + currentToken << endl;
						#endif
						currentNLCsentenceInList->sentenceContents = sentenceContents + currentToken;	//append the fullstop
						currentNLCsentenceInList->sentenceIndex = sentenceIndex;
						currentNLCsentenceInList->indentation = currentIndentation;
						currentNLCsentenceInList->next = new NLCsentence();
						currentNLCsentenceInList = currentNLCsentenceInList->next;
						sentenceContents = "";
						sentenceIndex++;
					}
					else
					{
						cout << "NLC_USE_PREPROCESSOR preprocessTextForNLC() error: a full stop has been detected without any preceeding text on the line." << endl;
					}
				}
				else if(currentToken == NLC_PREPROCESSOR_INDENTATION_CHAR)
				{
					if(parsingIndentation)
					{
						currentIndentation++;
					}
					else
					{
						cout << "NLC_USE_PREPROCESSOR preprocessTextForNLC() warning: NLC_INDENTATION_CHAR detected and !parsingIndentation" << endl;
						sentenceContents = sentenceContents + currentToken;
					}
				}
				else if(currentToken == NLC_PREPROCESSOR_FUNCTION_HEADER_MID_CHAR)
				{
					parsingIndentation = false;
					#ifdef NLC_SUPPORT_CONDITION_LOGICAL_OPERATIONS
					string lowerCaseSentenceContents = convertStringToLowerCase(&sentenceContents);
					bool logicalConditionDetected = textInTextArray(lowerCaseSentenceContents, logicalConditionOperationsArray, NLC_LOGICAL_CONDITION_OPERATIONS_NUMBER_OF_TYPES);
					#endif
					#ifdef NLC_SUPPORT_INPUT_FILE_LISTS
					if(sentenceContents == NLC_PREPROCESSOR_FUNCTION_HEADER_STRING)	//this is a case sensitive test
					{
						if(*detectedFunctions)
						{
							functionContents = functionContents.substr(0, functionContents.length() - sentenceContents.length());
							#ifdef NLC_DEBUG_PREPROCESSOR
							cout << "end function: functionName = " << functionName << endl;
							cout << "create new function = " << functionName << endl;
							cout << "functionContents = " << functionContents << endl;
							#endif
							writeStringToFile(functionName, functionContents);
							currentNLCfunctionInList->functionName = functionName;
							currentNLCfunctionInList->next = new NLCfunction();
							currentNLCfunctionInList = currentNLCfunctionInList->next;
							currentNLCsentenceInList = currentNLCfunctionInList->firstNLCsentenceInFunction;
							functionName = "";
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
						parsingFunctionName = true;
					}
					else
					#endif
					#ifdef NLC_SUPPORT_CONDITION_LOGICAL_OPERATIONS
					if(logicalConditionDetected)
					{
						lineIsLogicalCondition = true;
						sentenceContents = sentenceContents + currentToken;
					}
					else if(lowerCaseSentenceContents == NLC_LOGICAL_CONDITION_OPERATIONS_ELSE_IF)
					{
						//#ifdef NLC_DEBUG_PREPROCESSOR
						cout << "elseIfDetected" << endl;
						//#endif
						lineIsLogicalCondition = true;
						#ifdef NLC_PREPROCESSOR_LOGICAL_CONDITION_USE_ROBUST_NLP_INDEPENDENT_CODE
						currentNLCsentenceInList->elseIfDetected = true;
						//replace "else if" with "If"
						functionContents = functionContents.substr(0, functionContents.length()-sentenceContents.length()) + NLC_PREPROCESSOR_LOGICAL_CONDITION_DUMMY_TEXT_TEST_ELSEIF;
						sentenceContents = NLC_PREPROCESSOR_LOGICAL_CONDITION_DUMMY_TEXT_TEST_ELSEIF;
						#else
						//will rely on NLP to add an "else" property to the logicalConditionObject
						#endif
						sentenceContents = sentenceContents + currentToken;
					}
					else if((sentenceContents.length() > string(NLC_LOGICAL_CONDITION_OPERATIONS_ELSE_IF).length()) && (lowerCaseSentenceContents.substr(0, string(NLC_LOGICAL_CONDITION_OPERATIONS_ELSE).length()) == NLC_LOGICAL_CONDITION_OPERATIONS_ELSE)) 
					{
						//#ifdef NLC_DEBUG_PREPROCESSOR
						cout << "elseDetected" << endl;
						//#endif
						lineIsLogicalCondition = true;
						#ifdef NLC_PREPROCESSOR_LOGICAL_CONDITION_USE_ROBUST_NLP_INDEPENDENT_CODE
						currentNLCsentenceInList->elseDetected = true;
						#endif
						elseDetected = true;
						//replace "else" with "If this is done, "
						//cout << "pre sentenceContents = " << sentenceContents << endl;
						sentenceContents = string(NLC_PREPROCESSOR_LOGICAL_CONDITION_DUMMY_TEXT_TEST_ELSE) + sentenceContents.substr(string(NLC_LOGICAL_CONDITION_OPERATIONS_ELSE).length(), sentenceContents.length()-string(NLC_LOGICAL_CONDITION_OPERATIONS_ELSE).length());
						//cout << "post sentenceContents = " << sentenceContents << endl;
						functionContents = functionContents.substr(0, functionContents.length()-lowerCaseSentenceContents.length()) + sentenceContents;	//"lowerCaseSentenceContents.length()" is just used to measure the original length of the sentenceContents 
						//cout << "post functionContents = \n" << functionContents << endl;
					}
					#endif
					else
					{
						sentenceContents = sentenceContents + currentToken;
					}
				}
				else if(whiteSpaceDetected)
				{
					cout << "NLC_USE_PREPROCESSOR preprocessTextForNLC() error / NLCglobalDefs.h preprocessor definition error:\ncurrent implementation assumes NLC_PREPROCESSOR_INDENTATION_CHAR and NLC_PREPROCESSOR_FUNCTION_HEADER_MID_CHAR encapsulate all white space characters (CHAR_TAB and CHAR_SPACE)" << endl; 
				}
				else
				{
					parsingIndentation = false;
					sentenceContents = sentenceContents + currentToken;
					lineNonWhiteSpaceDetected = true;
				}
				functionContents = functionContents + currentToken;
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
			writeStringToFile(functionName, functionContents);
			//create new function file based on current text
		}
		else
		{
		#endif
		#ifdef NLC_DEBUG_PREPROCESSOR
		cout << "create preprocessed file = " << functionName << endl;
		cout  << "functionContents = \n" << functionContents << endl;
		#endif
		writeStringToFile(outputFileName, functionContents);
		#ifdef NLC_SUPPORT_INPUT_FILE_LISTS
		}
		#endif
	}
	

	return result;
}
#endif

void writeStringToFile(string fileName, string s)
{
	ofstream writeFileObject(fileName);

	for(int i=0; i < s.size(); i++)
	{
		writeFileObject.put(s[i]);
	}

	writeFileObject.close();
}




