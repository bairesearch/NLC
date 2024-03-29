 /*******************************************************************************
 *
 * License: GNU Affero General Public License version 3 (AGPLv3)
 *
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: NLCpreprocessor.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2022 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler
 * Project Version: 2p1a 05-June-2022
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 * /
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
		currentNLCfunctionInList->firstNLCprepreprocessorSentenceInList = new LRPpreprocessorSentence();
		bool interpretNewLinesAsNewSentences = true;	//NB NLC interprets new lines as new sentences
		#ifdef NLC_PREPROCESSOR_SUPPORT_MULTI_SENTENCE_LINES
		bool splitMultisentenceLines = true;
		#else
		bool splitMultisentenceLines = false;
		#endif
		if(!LRPpreprocessor.createPreprocessSentences(currentNLCfunctionInList->functionContentsRaw, currentNLCfunctionInList->firstNLCprepreprocessorSentenceInList, interpretNewLinesAsNewSentences, splitMultisentenceLines))	//NB NLC interprets new lines as new sentences
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
		
		if(detectFunctionHeader(&currentLine))
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
			NLCfunctionName = getFunctionNameFromFunctionHeader(&currentLine);		//NLCfunctionName
			functionFileName = generateNLCfunctionFileName(NLCfunctionName);
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
		LRPpreprocessorSentence* currentNLCprepreprocessorSentenceInList = currentNLCfunctionInList->firstNLCprepreprocessorSentenceInList;
		int sentenceIndex = LRP_NLP_START_SENTENCE_INDEX;	//NLC sentence index
		while(currentNLCprepreprocessorSentenceInList->next != NULL)
		{
			vector<LRPpreprocessorPlainTextWord*> lineContents = currentNLCprepreprocessorSentenceInList->sentenceContentsOriginal;
			if(lineContents.size() == 0)
			{
				currentNLCsentenceInList->isMath = true;
				currentNLCsentenceInList->sentenceOriginal = "";
				currentNLCsentenceInList->indentation = currentNLCprepreprocessorSentenceInList->indentation;
				NLCpreprocessorParsablePhrase* currentParsablePhraseInList = currentNLCsentenceInList->firstNLPparsablePhraseInList;
				LRPpreprocessorWordClassObject.addStringArrayToWordList((&currentParsablePhraseInList->sentenceContents), preprocessorMathNLPparsablePhraseDummyWordArray, NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_DUMMY_NUMBER_OF_WORDS);
				currentNLCsentenceInList->isBlankSentence = true;
				currentParsablePhraseInList->sentenceIndex = sentenceIndex;
				currentParsablePhraseInList->next = new NLCpreprocessorParsablePhrase();
				currentParsablePhraseInList = currentParsablePhraseInList->next;
				currentNLCsentenceInList->next = new NLCpreprocessorSentence();
				currentNLCsentenceInList = currentNLCsentenceInList->next;
				sentenceIndex = sentenceIndex+1;
			}
			else
			{
				//cout << "lineContents = " << LRPpreprocessorWordClassObject.generateTextFromVectorWordList(&lineContents) << endl;
				//cout << "lineContents.size() = " << lineContents.size() << endl;

				#ifdef NLC_PREPROCESSOR_PRINT_OUTPUT
				string currentLine = LRPpreprocessorWordClassObject.generateTextFromVectorWordList(&lineContents);
				inputFileText = inputFileText + currentLine + CHAR_NEWLINE;
				#endif
				int currentIndentation = currentNLCprepreprocessorSentenceInList->indentation;
				#ifdef NLC_PREPROCESSOR_GENERATE_COMMENTS
				currentNLCsentenceInList->sentenceOriginal = LRPpreprocessorWordClassObject.generateTextFromVectorWordList(&lineContents); 	//sentenceOriginal is stored for both isMath and !isMath (sentenceContentsOriginal is only stored for !isMath)
				#endif

				#ifdef NLC_PREPROCESSOR_MATH
				int lineLogicalConditionOperator;
				if(detectLogicalConditionOperatorAtStartOfLine(&lineContents, &lineLogicalConditionOperator))
				{
					currentNLCsentenceInList->hasLogicalConditionOperator = true;
					#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
					currentNLCsentenceInList->logicalConditionOperator = lineLogicalConditionOperator;
					currentNLCsentenceInList->isMath = true;
					#endif
					
					if(NLCpreprocessorMath.detectAndReplaceIsTextWithSymbol(&lineContents, currentNLCsentenceInList->hasLogicalConditionOperator, currentNLCsentenceInList->isMath))
					{
						currentNLCsentenceInList->isMath = true;
					}
				}
				else
				{
					if(NLCpreprocessorMath.detectMathSymbolsInLine(&lineContents))
					{
						currentNLCsentenceInList->isMath = true;
					}

					//#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
					if(NLCpreprocessorMath.detectAndReplaceIsTextWithSymbol(&lineContents, currentNLCsentenceInList->hasLogicalConditionOperator, currentNLCsentenceInList->isMath))
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
							currentSentenceInLogicalConditionCommandTemp->sentenceOriginal = LRPpreprocessorWordClassObject.generateTextFromVectorWordList(&(currentSentenceInLogicalConditionCommandTemp->firstNLPparsablePhraseInList->sentenceContents));
							#endif

							if(NLCpreprocessorMath.detectMathSymbolsInLine(&(currentSentenceInLogicalConditionCommandTemp->firstNLPparsablePhraseInList->sentenceContents)))
							{
								NLCpreprocessorMath.splitMathDetectedLineIntoNLPparsablePhrases(&(currentSentenceInLogicalConditionCommandTemp->firstNLPparsablePhraseInList->sentenceContents), &currentNLCsentenceInList, &sentenceIndex, currentSentenceInLogicalConditionCommandTemp->indentation, currentNLCfunctionInList, firstNLCfunctionInList);
							}
							else
							{
								#ifdef NLC_PREPROCESSOR_GENERATE_COMMENTS
								currentSentenceInLogicalConditionCommandTemp->sentenceContentsOriginal = LRPpreprocessorWordClassObject.generateTextFromVectorWordList(&(currentSentenceInLogicalConditionCommandTemp->firstNLPparsablePhraseInList->sentenceContents));
								#endif

								addNonLogicalConditionSentenceToList(&(currentSentenceInLogicalConditionCommandTemp->firstNLPparsablePhraseInList->sentenceContents), &currentNLCsentenceInList, &sentenceIndex, currentSentenceInLogicalConditionCommandTemp->indentation, currentNLCfunctionInList, firstNLCfunctionInList);
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
					currentNLCsentenceInList->sentenceContentsOriginal = LRPpreprocessorWordClassObject.generateTextFromVectorWordList(&lineContents);		//sentenceOriginal is stored for both isMath and !isMath (sentenceContentsOriginal is only stored for !isMath)

					addNonLogicalConditionSentenceToList(&lineContents, &currentNLCsentenceInList, &sentenceIndex, currentIndentation, currentNLCfunctionInList, firstNLCfunctionInList);

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
		currentNLCfunctionInList->firstLRPpreprocessorSentenceInList = new LRPpreprocessorSentence();
		LRPpreprocessorSentence* currentLRPpreprocessorSentenceInList = currentNLCfunctionInList->firstLRPpreprocessorSentenceInList;
		#endif
		int sentenceIndexOriginal = LRP_NLP_START_SENTENCE_INDEX;
		while(currentSentence->next != NULL)
		{
			string indentationContents = LRPpreprocessor.generateIndentationContents(currentSentence->indentation);

			NLCpreprocessorParsablePhrase* currentParsablePhrase = currentSentence->firstNLPparsablePhraseInList;
			bool first = true;
			while(currentParsablePhrase->next != NULL || (!currentSentence->isMath && first))
			{	
				first = false;
				
				#ifdef NLC_PREPROCESSOR_REMOVE_REDUNDANT_PRECEEDING_IS_FROM_NUMERICAL_OPERATORS_OLD_METHOD
				//OLD method; yet to update mathText:
				if(currentSentence->isMath)
				{
					if(currentSentence->hasLogicalConditionOperator)
					{
						if(currentSentence->mathTextNLPparsablePhraseTotal > 0)	//not required
						{
							vector<LRPpreprocessorPlainTextWord*>* parsablePhraseSentenceContents = &(currentParsablePhrase->sentenceContents);
							if(parsablePhraseSentenceContents->size() > 3)	//at least 3 words are required in parsable phrase for NLC_PREPROCESSOR_MATH_OPERATOR_LIKELY_PREPEND_NATURAL_LANGUAGE_WORD to exist
							{
								//cout << "parsablePhraseSentenceContents->back()->tagName = " << parsablePhraseSentenceContents->back()->tagName << endl;
								vector<LRPpreprocessorPlainTextWord*>::iterator iter = parsablePhraseSentenceContents->end()-2;
								if((*iter)->tagName == NLC_PREPROCESSOR_MATH_OPERATOR_LIKELY_PREPEND_NATURAL_LANGUAGE_WORD)	//second last word as last word is full stop
								{
									//cout << "NLC_PREPROCESSOR_REMOVE_REDUNDANT_PRECEEDING_IS_FROM_NUMERICAL_OPERATORS" << endl;
									//LRPpreprocessorWordClassObject.printWordList(parsablePhraseSentenceContents);
									
									//1. modify sentence mathText;
									string parsablePhraseReferenceName = NLCpreprocessorSentenceClass.generateMathTextNLPparsablePhraseReference(currentParsablePhrase->sentenceIndex, currentParsablePhrase);
									string mathTextSubphraseContainingNLPparsablePhrase = "";
									int mathTextSubphraseContainingNLPparsablePhraseStartIndex = 0;
									int mathTextSubphraseContainingNLPparsablePhraseEndIndex = 0;
									NLCtranslatorCodeBlocksLogicalConditions.getMathTextSubphraseContainingNLPparsablePhrase(currentSentence->mathText, parsablePhraseReferenceName, &mathTextSubphraseContainingNLPparsablePhrase, &mathTextSubphraseContainingNLPparsablePhraseStartIndex, &mathTextSubphraseContainingNLPparsablePhraseEndIndex);
									
									//cout << "parsablePhraseReferenceName = " << parsablePhraseReferenceName << endl;
									//cout << "currentSentence->mathText = " << currentSentence->mathText << endl;
									//cout << "mathTextSubphraseContainingNLPparsablePhrase = " << mathTextSubphraseContainingNLPparsablePhrase << endl;

									int indexOfMathOperatorLikelyPrependNaturalLanguageWord = mathTextSubphraseContainingNLPparsablePhrase.rfind(NLC_PREPROCESSOR_MATH_OPERATOR_LIKELY_PREPEND_NATURAL_LANGUAGE_WORD);	//find the last instance of "is" in the mathText parasble phrase string
									if(indexOfMathOperatorLikelyPrependNaturalLanguageWord != INT_DEFAULT_VALUE)
									{
										int indexAfterIsWord = indexOfMathOperatorLikelyPrependNaturalLanguageWord + string(NLC_PREPROCESSOR_MATH_OPERATOR_LIKELY_PREPEND_NATURAL_LANGUAGE_WORD).size();
										string mathTextSubphraseContainingNLPparsablePhraseModified = mathTextSubphraseContainingNLPparsablePhrase.substr(0, indexOfMathOperatorLikelyPrependNaturalLanguageWord) + mathTextSubphraseContainingNLPparsablePhrase.substr(indexAfterIsWord);
										currentSentence->mathText.replace(mathTextSubphraseContainingNLPparsablePhraseStartIndex, mathTextSubphraseContainingNLPparsablePhrase.length(), mathTextSubphraseContainingNLPparsablePhraseModified);
										
										//cout << "mathTextSubphraseContainingNLPparsablePhraseModified = " << mathTextSubphraseContainingNLPparsablePhraseModified << endl;
										//cout << "currentSentence->mathText = " << currentSentence->mathText << endl;
									}
									else
									{
										cerr << "NLCpreprocessorClass::preprocessTextForNLC{} error: indexOfMathOperatorLikelyPrependNaturalLanguageWord == INT_DEFAULT_VALUE)" << endl;
										exit(EXIT_ERROR);
									}
									
									//2. modify parsablePhrase sentenceContents;
									
									parsablePhraseSentenceContents->erase(iter);
		
									//LRPpreprocessorWordClassObject.printWordList(parsablePhraseSentenceContents);
								}
							}
						}
					}
				}
				#endif
				
				functionContents = functionContents + indentationContents + LRPpreprocessorWordClassObject.generateTextFromVectorWordList(&(currentParsablePhrase->sentenceContents)) + CHAR_NEWLINE;
				
				#ifdef GIA_POS_REL_TRANSLATOR_RULES_PARSE_ISOLATED_SUBREFERENCE_SETS_OPTIMISED
				if(!(currentSentence->isBlankSentence))
				{
					if(currentSentence->isMath)
					{
						//cout << "(currentSentence->isMath) currentSentence->mathText = : " << currentSentence->mathText << endl;
						if(!NLCtranslatorCodeBlocksLogicalConditions.getMathObjectVariableTypeBooleanExpressionBeforeGIAestimate(currentSentence, currentParsablePhrase))	//if estimated to have foundBooleanStatementExpression, then !parseIsolatedSubreferenceSets	//added 2f6b
						{
							//cout << "\tgetMathObjectVariableTypeBooleanExpressionBeforeGIAestimate" << endl;
							currentLRPpreprocessorSentenceInList->parseIsolatedSubreferenceSets = true;
							currentLRPpreprocessorSentenceInList->parseIsolatedSubreferenceSetsFirst = true;
							if(!(currentSentence->hasLogicalConditionOperator))
							{
								//cout << "(!(currentSentence->hasLogicalConditionOperator))" << endl;
								currentLRPpreprocessorSentenceInList->parseIsolatedSubreferenceSetsOnly = true;
							}
						}
					}
				}
				#endif
				
				#ifndef NLC_PREPROCESSOR_SAVE_OUTPUT_TO_FILE
				currentLRPpreprocessorSentenceInList->sentenceIndexOriginal = sentenceIndexOriginal;
				currentLRPpreprocessorSentenceInList->sentenceContentsOriginal = currentParsablePhrase->sentenceContents;	//precondition: words in logicReferenceVariableWordList are unique across all logicReferenceVariableWordLists in memory
				#ifdef NLC_PREPROCESSOR_DEBUG
				cout << "currentLRPpreprocessorSentenceInList = " << LRPpreprocessorWordClassObject.generateTextFromVectorWordList(&(currentLRPpreprocessorSentenceInList->sentenceContentsOriginal)) << endl;
				#endif
				currentLRPpreprocessorSentenceInList->next = new LRPpreprocessorSentence();
				currentLRPpreprocessorSentenceInList = currentLRPpreprocessorSentenceInList->next;
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
				cout << "\tcurrentParsablePhrase->sentenceContents = " << LRPpreprocessorWordClassObject.generateTextFromVectorWordList(&(currentParsablePhrase->sentenceContents)) << endl;
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


	
void NLCpreprocessorClass::addNonLogicalConditionSentenceToList(vector<LRPpreprocessorPlainTextWord*>* lineContents, NLCpreprocessorSentence** currentNLCsentenceInList, int* sentenceIndex, const int currentIndentation, NLCfunction* currentNLCfunctionInList, const NLCfunction* firstNLCfunctionInList)
{
	#ifdef NLC_PREPROCESSOR_MATH
	#ifdef NLC_PREPROCESSOR_MATH_REPLACE_NUMERICAL_VARIABLES_NAMES_FOR_NLP
	NLCpreprocessorMath.replaceNumericalVariablesWithDummyNumberIfNecessary(lineContents, *currentNLCsentenceInList, currentNLCfunctionInList, firstNLCfunctionInList);
	#endif
	#endif
	
	#ifdef NLC_MATH_OBJECTS_ADVANCED
	if(detectMathObjectStringDelimiter(lineContents))
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
			LRPpreprocessorWordClassObject.addStringArrayToWordList(lineContents, preprocessorInterpretSingleWordSentencesAsActionsDummyTextActionFullWordArray, NLC_PREPROCESSOR_INTERPRET_SINGLE_WORD_SENTENCES_AS_ACTIONS_DUMMY_TEXT_ACTION_FULL_NUMBER_OF_WORDS);
			LRPpreprocessorWordClassObject.addStringToWordList(lineContents, STRING_FULLSTOP);
			#else
			lineContents->clear();
			LRPpreprocessorWordClassObject.addStringToWordList(lineContents, actionName);
			LRPpreprocessorWordClassObject.addStringArrayToWordList(lineContents, preprocessorInterpretSingleWordSentencesAsActionsDummyTextActionObjectFullWordArray, NLC_PREPROCESSOR_INTERPRET_SINGLE_WORD_SENTENCES_AS_ACTIONS_DUMMY_TEXT_ACTION_OBJECT_FULL_NUMBER_OF_WORDS);
			LRPpreprocessorWordClassObject.addStringToWordList(lineContents, STRING_FULLSTOP);
			#endif
		}
	}
	#endif
	
	//cout << "lineContents = " << LRPpreprocessorWordClassObject.generateTextFromVectorWordList(lineContents) << endl;

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

bool NLCpreprocessorClass::detectLogicalConditionOperatorAtStartOfLine(const vector<LRPpreprocessorPlainTextWord*>* lineContents, int* logicalConditionOperator)
{
	*logicalConditionOperator = INT_DEFAULT_VALUE;
	bool logicalConditionOperatorFound = false;

	//get first word in line
	for(int i=0; i<NLC_LOGICAL_CONDITION_OPERATIONS_NUMBER_OF_TYPES; i++)
	{
		if(LRPpreprocessorWordClassObject.findSimpleSubstringInWordListAtIndex(lineContents, logicalConditionOperationsArray[i], 0, true))
		{
			logicalConditionOperatorFound = true;
			*logicalConditionOperator = i;
			//cout << "logicalConditionOperator = " << i << endl; 
		}
	}
	return logicalConditionOperatorFound;
}

#ifdef NLC_MATH_OBJECTS_ADVANCED
bool NLCpreprocessorClass::detectMathObjectStringDelimiter(const vector<LRPpreprocessorPlainTextWord*>* lineContents)
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






