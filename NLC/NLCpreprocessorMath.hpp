 /*******************************************************************************
 *
 * License: GNU Affero General Public License version 3 (AGPLv3)
 *
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: NLCpreprocessorMath.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2022 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler
 * Project Version: 2p1a 05-June-2022
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 * /
 *******************************************************************************/


#ifndef HEADER_NLC_PREPROCESSOR_MATH
#define HEADER_NLC_PREPROCESSOR_MATH

#include "NLCglobalDefs.hpp"
#include "NLCpreprocessorSentenceClass.hpp"
#include "NLCpreprocessorMathLogicalConditions.hpp"
#include "LRPpreprocessorWordClass.hpp"
#include "NLCprintDefs.hpp" //required for progLangOpenParameterSpace
#include "SHAREDvars.hpp"	//required for convertStringToLowerCase/isWhiteSpace
#include "GIAentityNodeClass.hpp" //required for LRP_NLP_START_SENTENCE_INDEX and entityNodesActiveListComplete

#ifdef NLC_PREPROCESSOR
#ifdef NLC_PREPROCESSOR_MATH

class NLCpreprocessorMathClass
{
	private: SHAREDvarsClass SHAREDvars;
	private: NLCpreprocessorMathLogicalConditionsClass NLCpreprocessorMathLogicalConditions;
	private: NLCpreprocessorSentenceClassClass NLCpreprocessorSentenceClass;
	private: LRPpreprocessorWordClassClass LRPpreprocessorWordClassObject;
	
	public: bool detectMathSymbolsInLine(const vector<LRPpreprocessorPlainTextWord*>* lineContents);
	public: bool detectAndReplaceIsTextWithSymbol(vector<LRPpreprocessorPlainTextWord*>* lineContents, const bool hasLogicalConditionOperator, const bool isMathText);

	#ifdef NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
	public: bool splitMathDetectedLineLogicalConditionCommandIntoSeparateSentences(vector<LRPpreprocessorPlainTextWord*>* lineContents, int currentIndentation, const NLCpreprocessorSentence* fullSentence, NLCpreprocessorSentence* firstSentenceInLogicalConditionCommandTemp, bool* detectedLogicalConditionCommand);
	#endif

	public: bool splitMathDetectedLineIntoNLPparsablePhrases(vector<LRPpreprocessorPlainTextWord*>* lineContents, NLCpreprocessorSentence** currentNLCsentenceInList, int* sentenceIndex, const int currentIndentation, NLCfunction* currentNLCfunctionInList, const NLCfunction* firstNLCfunctionInList);
		#ifdef NLC_PREPROCESSOR_MATH_MAINTAIN_CONSISTENT_WHITESPACE_FOR_BRACKETS_IN_MATHTEXT		
		public: void determineSpacingForAppendingMathText(const string* mathText, const string currentWord, string* spaceTextBefore, const bool previousWordWasLogicalConditionOperator);
		public: void determineSpacingForAppendingMathTextNLPparsablePhrase(const string* mathText, const string currentWord, string* spaceTextBefore);		
		#endif
		public: bool findCharacterAtIndexOrAfterSpace(const string* lineContents, const int i, const char characterToFind, int* indexOfCharacterFound);
		public: bool findWordAtIndex(const vector<LRPpreprocessorPlainTextWord*>* wordList, const int index, const string wordToFind);
		#ifdef NLC_PREPROCESSOR_MATH_SUPPORT_USER_VARIABLE_TYPE_DECLARATIONS
		private: bool replaceExplicitVariableTypesWithNLPparsablePhraseIllegalWords(vector<LRPpreprocessorPlainTextWord*>* lineContents);
		private: bool restoreExplicitVariableTypes(string* mathText);
			private: string replaceSubstringAtStartOfString(const string* textOrig, string stringToFind, string replacementString);
		#endif
		private: void addNewMathTextVariable(NLCpreprocessorSentence* sentence, const string variableName, const int variableTypeObject);
		private: void removeLastMathTextVariable(NLCpreprocessorSentence* sentence);

	#ifdef NLC_PREPROCESSOR_MATH_REPLACE_NUMERICAL_VARIABLES_NAMES_FOR_NLP
	public: bool replaceNumericalVariablesWithDummyNumberIfNecessary(vector<LRPpreprocessorPlainTextWord*>* lineContents, NLCpreprocessorSentence* currentNLCsentenceInList, NLCfunction* currentNLCfunctionInList, const NLCfunction* firstNLCfunctionInList);
		private: bool isWhiteSpaceOrInvalidWordCharacter(const char c);
	#endif

	private: bool findPredefinedMathtextVariable(const string* currentWord, NLCfunction* currentNLCfunctionInList, const NLCfunction* firstNLCfunctionInList, const NLCpreprocessorSentence* sentenceToIgnoreWhileSearching, int* variableType);
		#ifdef NLC_PREPROCESSOR_REPLACE_NUMERICAL_VARIABLES_DETECT_GLOBAL_NUMERICAL_VARIABLES
		private: bool findPredefinedMathtextVariableInAnyFunctions(const string* currentWord, const NLCfunction* firstNLCfunctionInList, const NLCpreprocessorSentence* sentenceToIgnoreWhileSearching, int* variableType);	//allows global numerical variable definitions; not just local numerical variable definitions
		#endif
			private: bool findPredefinedMathtextVariableInFunction(const string* currentWord, NLCfunction* currentNLCfunctionInList, const NLCpreprocessorSentence* sentenceToIgnoreWhileSearching, int* variableType);

	#ifdef NLC_MATH_OBJECTS_ADVANCED_INFER_TYPE_BASED_ON_PREVIOUSLY_DECLARED_MATHTEXT_VARIABLES_ADVANCED
	public: bool findMathTextVariableWithinMathText(string mathTextVariableName, string mathText);
	#endif
};


#endif
#endif

#endif
