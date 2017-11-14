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
 * Project: Natural Language Compiler
 * Project Version: 2d3a 12-November-2017
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/


#include "NLCpreprocessor.hpp"

//#include "NLCprintDefs.hpp" //required for progLangOpenParameterSpace

#ifdef NLC_PREPROCESSOR




bool NLCpreprocessorClass::preprocessTextForNLCwrapper(const string inputFileName, NLCfunction** firstNLCfunctionInList, bool* detectedFunctions, int* numberOfFunctionsInList, vector<string>* inputTextFileNameList, const string outputFileName)
{
	bool result = true;
	
	if(*firstNLCfunctionInList == NULL)
	{	
		*firstNLCfunctionInList = new NLCfunction();
		
		int numberOfLinesInFile = 0;
		vector<string> fileLinesList;
		if(!SHAREDvars.getLinesFromFile(inputFileName, &fileLinesList, &numberOfLinesInFile))
		{
			cerr << "NLCpreprocessorClass::preprocessTextForNLCwrapper{} error: !getLinesFromFile: inputFileName = " << inputFileName << endl;
			exit(EXIT_ERROR);
		}

		#ifdef NLC_PREPROCESSOR_PRINT_OUTPUT
		cout << "fileLinesList.size() = " << fileLinesList.size() << endl;
		#endif
		if(!preprocessTextForNLCextractFunctionsAndCreatePreprocessSentences(&fileLinesList, *firstNLCfunctionInList, detectedFunctions, numberOfFunctionsInList, inputTextFileNameList))
		{
			result = false;
		}
	}
	else
	{
		//assume function list has already been created externally
		NLCfunction* currentNLCfunctionInList = *firstNLCfunctionInList;
		*numberOfFunctionsInList = 0;
		while(currentNLCfunctionInList->next != NULL)
		{
			(*numberOfFunctionsInList) = (*numberOfFunctionsInList) + 1;
			currentNLCfunctionInList = currentNLCfunctionInList->next;
		}
	}
	
	if(!preprocessTextForNLC(*firstNLCfunctionInList, detectedFunctions, *numberOfFunctionsInList, outputFileName))
	{
		result = false;
	}
	
	return result;	
}


bool NLCpreprocessorClass::preprocessTextForNLCextractFunctionsAndCreatePreprocessSentences(vector<string>* fileLinesList, NLCfunction* firstNLCfunctionInList, bool* detectedFunctions, int* numberOfFunctionsInList, vector<string>* inputTextFileNameList)
{
	bool result = true;
	
	#ifdef NLC_INPUT_FUNCTION_LISTS_PREPROCESSOR
	if(!preprocessTextForNLCextractFunctions(fileLinesList, firstNLCfunctionInList, detectedFunctions, numberOfFunctionsInList, inputTextFileNameList))
	{
		result = false;
	}
	#else
	*numberOfFunctionsInList = 1;
	#endif

	NLCfunction* currentNLCfunctionInList = firstNLCfunctionInList;
	for(int functionDefinitionIndex=0; functionDefinitionIndex<*numberOfFunctionsInList; functionDefinitionIndex++)
	{
		currentNLCfunctionInList->firstNLCprepreprocessorSentenceInList = new GIApreprocessorSentence();
		bool interpretNewLinesAsNewSentences = true;	//NB NLC interprets new lines as new sentences
		#ifdef NLC_PREPROCESSOR_SUPPORT_MULTI_SENTENCE_LINES
		bool splitMultisentenceLines = true;
		#else
		bool splitMultisentenceLines = false;
		#endif
		if(!GIApreprocessor.createPreprocessSentences(currentNLCfunctionInList->functionContentsRaw, currentNLCfunctionInList->firstNLCprepreprocessorSentenceInList, interpretNewLinesAsNewSentences, splitMultisentenceLines))	//NB NLC interprets new lines as new sentences
		{
			result = false;
		}
		currentNLCfunctionInList = currentNLCfunctionInList->next;
	}
	
	return result;
}

#ifdef NLC_INPUT_FUNCTION_LISTS_PREPROCESSOR
		
bool NLCpreprocessorClass::preprocessTextForNLCextractFunctions(vector<string>* fileLinesList, NLCfunction* firstNLCfunctionInList, bool* detectedFunctions, int* numberOfFunctionsInList, vector<string>* inputTextFileNameList)
{
	bool result = true;

	*numberOfFunctionsInList = 0;

	NLCfunction* currentNLCfunctionInList = firstNLCfunctionInList;
	NLCpreprocessorSentence* currentNLCsentenceInList = currentNLCfunctionInList->firstNLCsentenceInFunction;
	*detectedFunctions = false;
	string functionContentsRaw = "";
	string NLCfunctionName = "";
	string functionFileName = "";	//with NLCfunctionName with extension
	#ifdef USE_NLCI
	int lineIndexOfFunctionHeader = 0;
	#endif
	for(int currentLineNumber=0; currentLineNumber<fileLinesList->size(); currentLineNumber++)
	{
		string currentLine = (*fileLinesList)[currentLineNumber];
		
		if(this->detectFunctionHeader(&currentLine))
		{
			//extract functions from file
			if(*detectedFunctions)
			{
				#ifdef USE_NLCI
				currentNLCfunctionInList->lineIndexOfFunctionHeaderTemp = lineIndexOfFunctionHeader;
				currentNLCfunctionInList->functionIndexTemp = *numberOfFunctionsInList;
				#endif
				currentNLCfunctionInList->NLCfunctionName = NLCfunctionName;
				currentNLCfunctionInList->functionContentsRaw = functionContentsRaw;
				currentNLCfunctionInList->next = new NLCfunction();
				currentNLCfunctionInList = currentNLCfunctionInList->next;
				currentNLCsentenceInList = currentNLCfunctionInList->firstNLCsentenceInFunction;
				*numberOfFunctionsInList = *numberOfFunctionsInList+1;
			}
			else
			{
				*detectedFunctions = true;
			}
			#ifdef USE_NLCI
			lineIndexOfFunctionHeader = currentLineNumber;
			#endif
			NLCfunctionName = this->getFunctionNameFromFunctionHeader(&currentLine);		//NLCfunctionName
			functionFileName = this->generateNLCfunctionFileName(NLCfunctionName);
			inputTextFileNameList->push_back(functionFileName);
			functionContentsRaw = "";
		}
		else
		{
			functionContentsRaw = functionContentsRaw + currentLine + CHAR_NEWLINE;
		}

	}

	//create a final function based on the final text..
	if(*detectedFunctions)
	{
		currentNLCfunctionInList->NLCfunctionName = NLCfunctionName;
		#ifdef USE_NLCI
		currentNLCfunctionInList->lineIndexOfFunctionHeaderTemp = lineIndexOfFunctionHeader;
		currentNLCfunctionInList->functionIndexTemp = *numberOfFunctionsInList;
		#endif
	}
	else
	{
		#ifdef NLC_PREPROCESSOR_PRINT_OUTPUT
		cout << "create new artificial function" << endl;
		#endif	
	}
	currentNLCfunctionInList->functionContentsRaw = functionContentsRaw;
	currentNLCfunctionInList->next = new NLCfunction();
	currentNLCfunctionInList = currentNLCfunctionInList->next;
	*numberOfFunctionsInList = *numberOfFunctionsInList+1;

	#ifdef NLC_PREPROCESSOR_PRINT_OUTPUT
	currentNLCfunctionInList = firstNLCfunctionInList;
	while(currentNLCfunctionInList->next != NULL)
	{
		cout << "NLCfunctionName = " << currentNLCfunctionInList->NLCfunctionName << endl;
		cout << "functionContentsRaw = \n" << currentNLCfunctionInList->functionContentsRaw << endl;
		currentNLCfunctionInList = currentNLCfunctionInList->next;
	}
	#endif

	return result;
}
#endif

string NLCpreprocessorClass::printStringVector(vector<string>* stringVector)
{
	string text = "";
	for(vector<string>::iterator iter = stringVector->begin(); iter != stringVector->end(); iter++)
	{
		text = text + *iter + CHAR_NEWLINE;
	}
	return text;
}

bool NLCpreprocessorClass::preprocessTextForNLC(NLCfunction* firstNLCfunctionInList, bool detectedFunctions, int numberOfFunctionsInList, const string outputFileName)
{
	bool result = true;
	
	#ifdef NLC_PREPROCESSOR_PRINT_OUTPUT
	string inputFileText = "";
	#endif
	
	NLCfunction* currentNLCfunctionInList = firstNLCfunctionInList;
	for(int functionDefinitionIndex=0; functionDefinitionIndex<numberOfFunctionsInList; functionDefinitionIndex++)
	{
		int currentLineNumber = 0;
		NLCpreprocessorSentence* currentNLCsentenceInList = currentNLCfunctionInList->firstNLCsentenceInFunction;
		GIApreprocessorSentence* currentNLCprepreprocessorSentenceInList = currentNLCfunctionInList->firstNLCprepreprocessorSentenceInList;
		int sentenceIndex = GIA_NLP_START_SENTENCE_INDEX;	//NLC sentence index
		while(currentNLCprepreprocessorSentenceInList->next != NULL)
		{
			vector<GIApreprocessorWord*> lineContents = currentNLCprepreprocessorSentenceInList->sentenceContentsOriginal;
			if(lineContents.size() == 0)
			{
				currentNLCsentenceInList->isMath = true;
				currentNLCsentenceInList->sentenceOriginal = "";
				currentNLCsentenceInList->indentation = currentNLCprepreprocessorSentenceInList->indentation;
				NLCpreprocessorParsablePhrase* currentParsablePhraseInList = currentNLCsentenceInList->firstNLPparsablePhraseInList;
				GIApreprocessorMultiwordReductionClassObject.addStringArrayToWordList((&currentParsablePhraseInList->sentenceContents), preprocessorMathNLPparsablePhraseDummyWordArray, NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_DUMMY_NUMBER_OF_WORDS);
				currentParsablePhraseInList->sentenceIndex = sentenceIndex;
				currentParsablePhraseInList->next = new NLCpreprocessorParsablePhrase();
				currentParsablePhraseInList = currentParsablePhraseInList->next;
				currentNLCsentenceInList->next = new NLCpreprocessorSentence();
				currentNLCsentenceInList = currentNLCsentenceInList->next;
				sentenceIndex = sentenceIndex+1;
			}
			else
			{
				//cout << "lineContents = " << GIApreprocessorMultiwordReductionClassObject.generateTextFromVectorWordList(&lineContents) << endl;
				//cout << "lineContents.size() = " << lineContents.size() << endl;

				#ifdef NLC_PREPROCESSOR_PRINT_OUTPUT
				string currentLine = GIApreprocessorMultiwordReductionClassObject.generateTextFromVectorWordList(&lineContents);
				inputFileText = inputFileText + currentLine + CHAR_NEWLINE;
				#endif
				int currentIndentation = currentNLCprepreprocessorSentenceInList->indentation;
				#ifdef NLC_PREPROCESSOR_GENERATE_COMMENTS
				currentNLCsentenceInList->sentenceOriginal = GIApreprocessorMultiwordReductionClassObject.generateTextFromVectorWordList(&lineContents); 	//sentenceOriginal is stored for both isMath and !isMath (sentenceContentsOriginal is only stored for !isMath)
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

					NLCpreprocessorMath.splitMathDetectedLineIntoNLPparsablePhrases(&lineContents, &currentNLCsentenceInList, &sentenceIndex, currentIndentation, currentNLCfunctionInList, firstNLCfunctionInList);

					#ifdef NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
					if(detectedLogicalConditionCommand)
					{
						NLCpreprocessorSentence* currentSentenceInLogicalConditionCommandTemp = firstSentenceInLogicalConditionCommandTemp;
						while(currentSentenceInLogicalConditionCommandTemp->next != NULL)
						{
							#ifdef NLC_PREPROCESSOR_GENERATE_COMMENTS
							currentSentenceInLogicalConditionCommandTemp->sentenceOriginal = GIApreprocessorMultiwordReductionClassObject.generateTextFromVectorWordList(&(currentSentenceInLogicalConditionCommandTemp->firstNLPparsablePhraseInList->sentenceContents));
							#endif

							if(NLCpreprocessorMath.detectMathSymbolsInLine(&(currentSentenceInLogicalConditionCommandTemp->firstNLPparsablePhraseInList->sentenceContents)))
							{
								NLCpreprocessorMath.splitMathDetectedLineIntoNLPparsablePhrases(&(currentSentenceInLogicalConditionCommandTemp->firstNLPparsablePhraseInList->sentenceContents), &currentNLCsentenceInList, &sentenceIndex, currentSentenceInLogicalConditionCommandTemp->indentation, currentNLCfunctionInList, firstNLCfunctionInList);
							}
							else
							{
								#ifdef NLC_PREPROCESSOR_GENERATE_COMMENTS
								currentSentenceInLogicalConditionCommandTemp->sentenceContentsOriginal = GIApreprocessorMultiwordReductionClassObject.generateTextFromVectorWordList(&(currentSentenceInLogicalConditionCommandTemp->firstNLPparsablePhraseInList->sentenceContents));
								#endif

								this->addNonLogicalConditionSentenceToList(&(currentSentenceInLogicalConditionCommandTemp->firstNLPparsablePhraseInList->sentenceContents), &currentNLCsentenceInList, &sentenceIndex, currentSentenceInLogicalConditionCommandTemp->indentation, currentNLCfunctionInList, firstNLCfunctionInList);
								//cout << "currentSentenceInLogicalConditionCommandTemp->indentation = " << currentSentenceInLogicalConditionCommandTemp->indentation << endl;
							}
							currentSentenceInLogicalConditionCommandTemp = currentSentenceInLogicalConditionCommandTemp->next;
						}
					}
					#endif
				}
				else
				{
				#endif
					currentNLCsentenceInList->sentenceContentsOriginal = GIApreprocessorMultiwordReductionClassObject.generateTextFromVectorWordList(&lineContents);		//sentenceOriginal is stored for both isMath and !isMath (sentenceContentsOriginal is only stored for !isMath)

					this->addNonLogicalConditionSentenceToList(&lineContents, &currentNLCsentenceInList, &sentenceIndex, currentIndentation, currentNLCfunctionInList, firstNLCfunctionInList);

				#ifdef NLC_PREPROCESSOR_MATH
				}
				#endif
			}

			currentLineNumber++;
			currentNLCprepreprocessorSentenceInList = currentNLCprepreprocessorSentenceInList->next;
		}
		currentNLCfunctionInList = currentNLCfunctionInList->next;
	}


	currentNLCfunctionInList = firstNLCfunctionInList;
	while(currentNLCfunctionInList->next != NULL)
	{
		string functionContents = "";
		NLCpreprocessorSentence* currentSentence = currentNLCfunctionInList->firstNLCsentenceInFunction;
		
		#ifndef NLC_PREPROCESSOR_SAVE_OUTPUT_TO_FILE
		currentNLCfunctionInList->firstGIApreprocessorSentenceInList = new GIApreprocessorSentence();
		GIApreprocessorSentence* currentGIApreprocessorSentenceInList = currentNLCfunctionInList->firstGIApreprocessorSentenceInList;
		#endif
		int sentenceIndexOriginal = GIA_NLP_START_SENTENCE_INDEX;
		while(currentSentence->next != NULL)
		{
			string indentationContents = GIApreprocessor.generateIndentationContents(currentSentence->indentation);

			NLCpreprocessorParsablePhrase* currentParsablePhrase = currentSentence->firstNLPparsablePhraseInList;
			bool first = true;
			while(currentParsablePhrase->next != NULL || (!currentSentence->isMath && first))
			{	
				first = false;
				functionContents = functionContents + indentationContents + GIApreprocessorMultiwordReductionClassObject.generateTextFromVectorWordList(&(currentParsablePhrase->sentenceContents)) + CHAR_NEWLINE;
				
				#ifndef NLC_PREPROCESSOR_SAVE_OUTPUT_TO_FILE
				currentGIApreprocessorSentenceInList->sentenceIndexOriginal = sentenceIndexOriginal;
				currentGIApreprocessorSentenceInList->sentenceContentsOriginal = currentParsablePhrase->sentenceContents;	//precondition: words in logicReferenceVariableWordList are unique across all logicReferenceVariableWordLists in memory
				#ifdef NLC_PREPROCESSOR_DEBUG
				cout << "currentGIApreprocessorSentenceInList = " << GIApreprocessorMultiwordReductionClassObject.generateTextFromVectorWordList(&(currentGIApreprocessorSentenceInList->sentenceContentsOriginal)) << endl;
				#endif
				currentGIApreprocessorSentenceInList->next = new GIApreprocessorSentence();
				currentGIApreprocessorSentenceInList = currentGIApreprocessorSentenceInList->next;
				sentenceIndexOriginal++;
				#endif
				
				if(currentSentence->isMath)
				{
					currentParsablePhrase = currentParsablePhrase->next;
				}
			}
			currentSentence = currentSentence->next;
		}
		
		#ifdef NLC_PREPROCESSOR_SAVE_OUTPUT_TO_FILE
		string functionName = currentNLCfunctionInList->NLCfunctionName;
		if(!detectedFunctions)
		{
			functionName = outputFileName;
		}
		SHAREDvars.writeStringToFile(functionName, &functionContents);
		#endif
		
		currentNLCfunctionInList = currentNLCfunctionInList->next;
	}

	#ifdef NLC_PREPROCESSOR_PRINT_OUTPUT
	//cout << "inputFileText = \n" << inputFileText << endl;
	currentNLCfunctionInList = firstNLCfunctionInList;
	while(currentNLCfunctionInList->next != NULL)
	{
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
			bool first = true;
			while(currentParsablePhrase->next != NULL || (!currentSentence->isMath && first))
			{	
				first = false;
				cout << "\tcurrentParsablePhrase->sentenceContents = " << GIApreprocessorMultiwordReductionClassObject.generateTextFromVectorWordList(&(currentParsablePhrase->sentenceContents)) << endl;
				cout << "\tcurrentParsablePhrase->sentenceIndex = " << currentParsablePhrase->sentenceIndex << endl;
				cout << "\tcurrentParsablePhrase->mathTextNLPparsablePhraseIndex = " << currentParsablePhrase->mathTextNLPparsablePhraseIndex << endl;

				if(currentSentence->isMath)
				{
					currentParsablePhrase = currentParsablePhrase->next;
				}
			}

			currentSentence = currentSentence->next;
		}
		currentNLCfunctionInList = currentNLCfunctionInList->next;
	}
	#endif

	#ifdef NLC_DEBUG_PREPROCESSOR_PREMATURE_QUIT
	cerr << "Premature quit for debug" << endl;
	exit(EXIT_ERROR);
	#endif

	return result;
}


	
void NLCpreprocessorClass::addNonLogicalConditionSentenceToList(vector<GIApreprocessorWord*>* lineContents, NLCpreprocessorSentence** currentNLCsentenceInList, int* sentenceIndex, const int currentIndentation, NLCfunction* currentNLCfunctionInList, const NLCfunction* firstNLCfunctionInList)
{
	#ifdef NLC_PREPROCESSOR_MATH
	#ifdef NLC_PREPROCESSOR_MATH_REPLACE_NUMERICAL_VARIABLES_NAMES_FOR_NLP
	NLCpreprocessorMath.replaceNumericalVariablesWithDummyNumberIfNecessary(lineContents, *currentNLCsentenceInList, currentNLCfunctionInList, firstNLCfunctionInList);
	#endif
	#endif
	
	#ifdef NLC_MATH_OBJECTS_ADVANCED
	if(this->detectMathObjectStringDelimiter(lineContents))
	{
		cout << "preprocessTextForNLC{} error: quotation marks detected without mathtext expression (illegal: 'Print \"this text\"'. legal: 'the value = \"this text\". print the value.')" << endl;
	}
	#endif

	#ifdef NLC_PREPROCESSOR_INTERPRET_SINGLE_WORD_SENTENCES_AS_ACTIONS
	if((lineContents->size() == 2) && ((*lineContents)[1]->tagName == STRING_FULLSTOP))
	{		
		string firstWordInSentence = (*lineContents)[0]->tagName;
		if(NLCpreprocessorSentenceClass.isStringValidVariableName(firstWordInSentence, true))
		{
			#ifdef NLC_PREPROCESSOR_INTERPRET_SINGLE_WORD_SENTENCES_AS_ACTIONS_REPLACE_ACTION_ALSO_DUE_TO_NLP_LIMITATION
			string actionName = firstWordInSentence;
			(*currentNLCsentenceInList)->singleWordSentenceActionName = actionName;
			lineContents->clear();
			GIApreprocessorMultiwordReductionClassObject.addStringArrayToWordList(lineContents, preprocessorInterpretSingleWordSentencesAsActionsDummyTextActionFullWordArray, NLC_PREPROCESSOR_INTERPRET_SINGLE_WORD_SENTENCES_AS_ACTIONS_DUMMY_TEXT_ACTION_FULL_NUMBER_OF_WORDS);
			GIApreprocessorMultiwordReductionClassObject.addStringToWordList(lineContents, STRING_FULLSTOP);
			#else
			lineContents->clear();
			GIApreprocessorMultiwordReductionClassObject.addStringToWordList(lineContents, actionName);
			GIApreprocessorMultiwordReductionClassObject.addStringArrayToWordList(lineContents, preprocessorInterpretSingleWordSentencesAsActionsDummyTextActionObjectFullWordArray, NLC_PREPROCESSOR_INTERPRET_SINGLE_WORD_SENTENCES_AS_ACTIONS_DUMMY_TEXT_ACTION_OBJECT_FULL_NUMBER_OF_WORDS);
			GIApreprocessorMultiwordReductionClassObject.addStringToWordList(lineContents, STRING_FULLSTOP);
			#endif
		}
	}
	#endif
	
	//cout << "lineContents = " << GIApreprocessorMultiwordReductionClassObject.generateTextFromVectorWordList(lineContents) << endl;

	(*currentNLCsentenceInList)->firstNLPparsablePhraseInList->sentenceContents = *lineContents;	//full stop should already be appended
	(*currentNLCsentenceInList)->firstNLPparsablePhraseInList->sentenceIndex = (*sentenceIndex);
	(*currentNLCsentenceInList)->indentation = currentIndentation;
	(*currentNLCsentenceInList)->next = new NLCpreprocessorSentence();
	(*currentNLCsentenceInList) = (*currentNLCsentenceInList)->next;
	(*sentenceIndex) = (*sentenceIndex)+1;
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

bool NLCpreprocessorClass::detectLogicalConditionOperatorAtStartOfLine(const vector<GIApreprocessorWord*>* lineContents, int* logicalConditionOperator)
{
	*logicalConditionOperator = INT_DEFAULT_VALUE;
	bool logicalConditionOperatorFound = false;

	//get first word in line
	for(int i=0; i<NLC_LOGICAL_CONDITION_OPERATIONS_NUMBER_OF_TYPES; i++)
	{
		if(GIApreprocessorMultiwordReductionClassObject.findSimpleSubstringInWordListAtIndex(lineContents, logicalConditionOperationsArray[i], 0, true))
		{
			logicalConditionOperatorFound = true;
			*logicalConditionOperator = i;
			//cout << "logicalConditionOperator = " << i << endl; 
		}
	}
	return logicalConditionOperatorFound;
}

#ifdef NLC_MATH_OBJECTS_ADVANCED
bool NLCpreprocessorClass::detectMathObjectStringDelimiter(const vector<GIApreprocessorWord*>* lineContents)
{
	bool result = false;
	for(int w = 0; w < lineContents->size(); w++)
	{
		string currentWord = (*lineContents)[w]->tagName;
		if(currentWord.find(NLC_MATH_OBJECTS_STRING_DELIMITER_CHAR) != CPP_STRING_FIND_RESULT_FAIL_VALUE)
		{
			result = true;
		}
	}
	
	return result;
}
#endif

#endif






