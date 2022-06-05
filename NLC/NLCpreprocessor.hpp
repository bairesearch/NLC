 /*******************************************************************************
 *
 * License: GNU Affero General Public License version 3 (AGPLv3)
 *
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: NLCpreprocessor.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2022 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler
 * Project Version: 2p1a 05-June-2022
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
#include "GIAentityNodeClass.hpp" //required for LRP_NLP_START_SENTENCE_INDEX and entityNodesActiveListComplete
#include "LRPpreprocessor.hpp"
#include "LRPpreprocessorWordClass.hpp"
#include "GIAtranslatorOperations.hpp"


#ifdef NLC_PREPROCESSOR
class NLCpreprocessorClass
{
	private: SHAREDvarsClass SHAREDvars;
	private: NLCpreprocessorMathClass NLCpreprocessorMath;
	private: LRPpreprocessorClass LRPpreprocessor;
	private: LRPpreprocessorWordClassClass LRPpreprocessorWordClassObject;
	private: NLCpreprocessorSentenceClassClass NLCpreprocessorSentenceClass;
	private: NLCtranslatorCodeBlocksLogicalConditionsClass NLCtranslatorCodeBlocksLogicalConditions;

	public: bool preprocessTextForNLCwrapper(const string inputFileName, NLCfunction** firstNLCfunctionInList, bool* detectedFunctions, int* numberOfFunctionsInList, vector<string>* inputTextFileNameList, const string outputFileName);
		public: bool preprocessTextForNLCextractFunctionsAndCreatePreprocessSentences(vector<string>* fileLinesList, NLCfunction* firstNLCfunctionInList, bool* detectedFunctions, int* numberOfFunctionsInList, vector<string>* inputTextFileNameList);
			#ifdef NLC_INPUT_FUNCTION_LISTS_PREPROCESSOR
			private: bool preprocessTextForNLCextractFunctions(vector<string>* fileLinesList, NLCfunction* firstNLCfunctionInList, bool* detectedFunctions, int* numberOfFunctionsInList, vector<string>* inputTextFileNameList);
			#endif
				private: string printStringVector(vector<string>* stringVector);	
		private: bool preprocessTextForNLC(NLCfunction* firstNLCfunctionInList, bool detectedFunctions, int numberOfFunctionsInList, const string outputFileName);
			private: void addNonLogicalConditionSentenceToList(vector<LRPpreprocessorPlainTextWord*>* lineContents, NLCpreprocessorSentence** currentNLCsentenceInList, int* sentenceIndex, const int currentIndentation, NLCfunction* currentNLCfunctionInList, const NLCfunction* firstNLCfunctionInList);
			#ifdef NLC_INPUT_FUNCTION_LISTS
			public: bool detectFunctionHeader(const string* lineContents);
			public: string getFunctionNameFromFunctionHeader(const string* lineContents);
			private: string generateNLCfunctionFileName(const string NLCfunctionName);
			#endif
			private: bool detectLogicalConditionOperatorAtStartOfLine(const vector<LRPpreprocessorPlainTextWord*>* lineContents, int* logicalConditionOperator);
			#ifdef NLC_MATH_OBJECTS_ADVANCED
			private: bool detectMathObjectStringDelimiter(const vector<LRPpreprocessorPlainTextWord*>* lineContents);
			#endif
};
#endif

#endif
