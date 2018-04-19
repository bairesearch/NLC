/*******************************************************************************
 *
 * No License
 * 
 * This work is under exclusive copyright (c) Baxter AI (baxterai.com). 
 * Nobody else can use, copy, distribute, or modify this work without being 
 * at risk of take-downs, shake-downs, or litigation. 
 * 
 * By publishing this source code in a public repository on GitHub, Terms of 
 * Service have been accepted by which Baxter AI have allowed others to view 
 * and fork their repository.
 * 
 * If you find software that doesn't have a license, that generally means you 
 * have no permission from the creators of the software to use, modify, or 
 * share the software. Although a code host such as GitHub may allow you to 
 * view and fork the code, this does not imply that you are permitted to use, 
 * modify, or share the software for any purpose.
 *
 * This notice has been derived from https://choosealicense.com/no-permission 
 * (https://web.archive.org/web/20180312144938/https://choosealicense.com/no-permission)
 *
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: NLCpreprocessor.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2018 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler
 * Project Version: 2f7c 17-April-2018
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 * /
 *******************************************************************************/


#ifndef HEADER_NLC_PREPROCESSOR
#define HEADER_NLC_PREPROCESSOR

#include "NLCglobalDefs.hpp"
#include "NLCpreprocessorSentenceClass.hpp"
#include "NLCpreprocessorMath.hpp"
#include "NLCpreprocessorMathLogicalConditions.hpp"
#include "NLCtranslatorCodeBlocksLogicalConditions.hpp"
#include "SHAREDvars.hpp"	//required for convertStringToLowerCase/isWhiteSpace
#include "GIAentityNodeClass.hpp" //required for GIA_NLP_START_SENTENCE_INDEX and entityNodesActiveListComplete
#include "GIApreprocessor.hpp"
#include "GIApreprocessorWordClass.hpp"
#include "GIAtranslatorOperations.hpp"


#ifdef NLC_PREPROCESSOR
class NLCpreprocessorClass
{
	private: SHAREDvarsClass SHAREDvars;
	private: NLCpreprocessorMathClass NLCpreprocessorMath;
	private: GIApreprocessorClass GIApreprocessor;
	private: GIApreprocessorWordClassClass GIApreprocessorWordClassObject;
	private: NLCpreprocessorSentenceClassClass NLCpreprocessorSentenceClass;
	private: NLCtranslatorCodeBlocksLogicalConditionsClass NLCtranslatorCodeBlocksLogicalConditions;

	public: bool preprocessTextForNLCwrapper(const string inputFileName, NLCfunction** firstNLCfunctionInList, bool* detectedFunctions, int* numberOfFunctionsInList, vector<string>* inputTextFileNameList, const string outputFileName);
		public: bool preprocessTextForNLCextractFunctionsAndCreatePreprocessSentences(vector<string>* fileLinesList, NLCfunction* firstNLCfunctionInList, bool* detectedFunctions, int* numberOfFunctionsInList, vector<string>* inputTextFileNameList);
			#ifdef NLC_INPUT_FUNCTION_LISTS_PREPROCESSOR
			private: bool preprocessTextForNLCextractFunctions(vector<string>* fileLinesList, NLCfunction* firstNLCfunctionInList, bool* detectedFunctions, int* numberOfFunctionsInList, vector<string>* inputTextFileNameList);
			#endif
				private: string printStringVector(vector<string>* stringVector);	
		private: bool preprocessTextForNLC(NLCfunction* firstNLCfunctionInList, bool detectedFunctions, int numberOfFunctionsInList, const string outputFileName);
			private: void addNonLogicalConditionSentenceToList(vector<GIApreprocessorPlainTextWord*>* lineContents, NLCpreprocessorSentence** currentNLCsentenceInList, int* sentenceIndex, const int currentIndentation, NLCfunction* currentNLCfunctionInList, const NLCfunction* firstNLCfunctionInList);
			#ifdef NLC_INPUT_FUNCTION_LISTS
			public: bool detectFunctionHeader(const string* lineContents);
			public: string getFunctionNameFromFunctionHeader(const string* lineContents);
			private: string generateNLCfunctionFileName(const string NLCfunctionName);
			#endif
			private: bool detectLogicalConditionOperatorAtStartOfLine(const vector<GIApreprocessorPlainTextWord*>* lineContents, int* logicalConditionOperator);
			#ifdef NLC_MATH_OBJECTS_ADVANCED
			private: bool detectMathObjectStringDelimiter(const vector<GIApreprocessorPlainTextWord*>* lineContents);
			#endif
};
#endif

#endif
