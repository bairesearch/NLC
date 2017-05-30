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
 * Project Version: 2b3b 25-May-2017
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/


#include "NLCpreprocessor.hpp"

//#include "NLCprintDefs.hpp" //required for progLangOpenParameterSpace

#ifdef NLC_PREPROCESSOR




bool NLCpreprocessorClass::preprocessTextForNLC(const string inputFileName, NLCfunction* firstNLCfunctionInList, bool* detectedFunctions, int* numberOfInputFilesInList, vector<string>* inputTextFileNameList, const string outputFileName, GIApreprocessorSentence* firstGIApreprocessorSentenceInListTemplate)
{
	bool result = true;
	
	if(firstGIApreprocessorSentenceInListTemplate == NULL)
	{		
		#ifdef NLC_INPUT_FUNCTION_LISTS_PREPROCESSOR
		if(!preprocessTextForNLCextractFunctions(inputFileName, firstNLCfunctionInList, detectedFunctions, numberOfInputFilesInList, inputTextFileNameList))
		{
			result = false;
		}
		#else
		*numberOfInputFilesInList = 1;
		#endif
		
		NLCfunction* currentNLCfunctionInList = firstNLCfunctionInList;
		for(int functionDefinitionIndex=0; functionDefinitionIndex<*numberOfInputFilesInList; functionDefinitionIndex++)
		{
			currentNLCfunctionInList->firstGIApreprocessorSentenceInList = new GIApreprocessorSentence();
			if(!GIApreprocessor.createPreprocessSentences(currentNLCfunctionInList->functionContentsRaw, currentNLCfunctionInList->firstGIApreprocessorSentenceInList, true))	//NB NLC interprets new lines as new sentences
			{
				result = false;
			}
			currentNLCfunctionInList = currentNLCfunctionInList->next;
		}
	}
	else
	{
		firstNLCfunctionInList->firstGIApreprocessorSentenceInList = firstGIApreprocessorSentenceInListTemplate;
		*numberOfInputFilesInList = 1;
	}	

	#ifdef NLC_PREPROCESSOR_PRINT_OUTPUT
	string inputFileText = "";
	#endif
	
	NLCfunction* currentNLCfunctionInList = firstNLCfunctionInList;
	for(int functionDefinitionIndex=0; functionDefinitionIndex<*numberOfInputFilesInList; functionDefinitionIndex++)
	{
		int currentLineNumber = 0;
		NLCpreprocessorSentence* currentNLCsentenceInList = currentNLCfunctionInList->firstNLCsentenceInFunction;
		GIApreprocessorSentence* currentGIApreprocessorSentenceInList = currentNLCfunctionInList->firstGIApreprocessorSentenceInList;
		int sentenceIndex = GIA_NLP_START_SENTENCE_INDEX;	//NLC sentence index
		while(currentGIApreprocessorSentenceInList->next != NULL)
		{
			vector<GIApreprocessorWord*> lineContents;
			if(!GIApreprocessorMultiwordReductionClassObject.generateSentenceWordList(currentGIApreprocessorSentenceInList->sentenceContentsOriginalFirstWord, &lineContents))
			{
				cout << "NLCpreprocessorClass::preprocessTextForNLC{} error: !generateSentenceWordList" << endl;
				exit(EXIT_ERROR);
			}
			//cout << "lineContents = " << GIApreprocessorMultiwordReductionClassObject.generateTextFromVectorWordList(&lineContents) << endl;

			#ifdef NLC_PREPROCESSOR_PRINT_OUTPUT
			string currentLine = GIApreprocessorMultiwordReductionClassObject.generateTextFromVectorWordList(&lineContents);
			inputFileText = inputFileText + currentLine + CHAR_NEWLINE;
			#endif
			int currentIndentation = currentGIApreprocessorSentenceInList->indentation;
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

			currentLineNumber++;
			currentGIApreprocessorSentenceInList = currentGIApreprocessorSentenceInList->next;
		}
		currentNLCfunctionInList = currentNLCfunctionInList->next;
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

	//#ifdef NLC_DEBUG_PREPROCESSOR_PREMATURE_QUIT
	cout << "Premature quit for debug" << endl;
	exit(EXIT_ERROR);
	//#endif

	return result;
}

#ifdef NLC_INPUT_FUNCTION_LISTS_PREPROCESSOR
bool NLCpreprocessorClass::preprocessTextForNLCextractFunctions(const string inputFileName, NLCfunction* firstNLCfunctionInList, bool* detectedFunctions, int* numberOfInputFilesInList, vector<string>* inputTextFileNameList)
{
	bool result = true;

	*numberOfInputFilesInList = 0;

	#ifdef NLC_PREPROCESSOR_PRINT_OUTPUT
	string inputFileText = "";
	#endif
			
	ifstream parseFileObject(inputFileName.c_str());
	if(!parseFileObject.rdbuf()->is_open())
	{
		//txt file does not exist in current directory.
		cout << "Error: NLC input file does not exist in current directory: " << inputFileName << endl;
		result = false;
	}
	else
	{
		NLCfunction* currentNLCfunctionInList = firstNLCfunctionInList;
		NLCpreprocessorSentence* currentNLCsentenceInList = currentNLCfunctionInList->firstNLCsentenceInFunction;
		string currentLine;
		*detectedFunctions = false;
		string functionContentsRaw = "";
		string NLCfunctionName = "";
		string functionFileName = "";	//with NLCfunctionName with extension
		int currentLineNumber = 0;

		while(getline(parseFileObject, currentLine))
		{
			#ifdef NLC_PREPROCESSOR_PRINT_OUTPUT
			inputFileText = inputFileText + currentLine + CHAR_NEWLINE;
			#endif

			if(this->detectFunctionHeader(&currentLine))
			{
				//extract functions from file
				if(*detectedFunctions)
				{
					currentNLCfunctionInList->NLCfunctionName = NLCfunctionName;
					currentNLCfunctionInList->functionContentsRaw = functionContentsRaw;
					currentNLCfunctionInList->next = new NLCfunction();
					currentNLCfunctionInList = currentNLCfunctionInList->next;
					currentNLCsentenceInList = currentNLCfunctionInList->firstNLCsentenceInFunction;
					*numberOfInputFilesInList = *numberOfInputFilesInList+1;
				}
				else
				{
					*detectedFunctions = true;
				}
				NLCfunctionName = this->getFunctionNameFromFunctionHeader(&currentLine);		//NLCfunctionName
				functionFileName = this->generateNLCfunctionFileName(NLCfunctionName);
				inputTextFileNameList->push_back(functionFileName);
				functionContentsRaw = "";
			}
			else
			{
				functionContentsRaw = functionContentsRaw + currentLine + CHAR_NEWLINE;
			}
			
			currentLineNumber++;
		}

		//create a final function based on the final text..
		if(*detectedFunctions)
		{
			currentNLCfunctionInList->NLCfunctionName = NLCfunctionName;
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
		*numberOfInputFilesInList = *numberOfInputFilesInList+1;
	}

	#ifdef NLC_PREPROCESSOR_PRINT_OUTPUT
	NLCfunction* currentNLCfunctionInList = firstNLCfunctionInList;
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
			GIApreprocessorMultiwordReductionClassObject.addStringToWordList(lineContents, NLC_PREPROCESSOR_INTERPRET_SINGLE_WORD_SENTENCES_AS_ACTIONS_DUMMY_TEXT_ACTION_FULL);
			GIApreprocessorMultiwordReductionClassObject.addStringToWordList(lineContents, STRING_FULLSTOP);
			#else
			lineContents->clear();
			GIApreprocessorMultiwordReductionClassObject.addStringToWordList(lineContents, actionName);
			GIApreprocessorMultiwordReductionClassObject.addStringToWordList(lineContents, NLC_PREPROCESSOR_INTERPRET_SINGLE_WORD_SENTENCES_AS_ACTIONS_DUMMY_TEXT_ACTION_OBJECT_FULL);
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
		if(lineContents->size() >= 1)
		{
			string firstWordOnLine = (*lineContents)[0]->tagName;
			string firstWordOnLineLowerCase = SHAREDvars.convertStringToLowerCase(&firstWordOnLine);
			if(firstWordOnLineLowerCase == logicalConditionOperationsArray[i])
			{
				logicalConditionOperatorFound = true;
				*logicalConditionOperator = i;
			}
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






