 /*******************************************************************************
 *
 * License: GNU Affero General Public License version 3 (AGPLv3)
 *
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: NLCpreprocessorMathLogicalConditions.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2022 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler
 * Project Version: 2p1a 05-June-2022
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 * /
 *******************************************************************************/


#ifndef HEADER_NLC_PREPROCESSOR_MATH_LOGICAL_CONDITIONS
#define HEADER_NLC_PREPROCESSOR_MATH_LOGICAL_CONDITIONS

#include "NLCglobalDefs.hpp"
#include "NLCpreprocessorSentenceClass.hpp"
#include "LRPpreprocessorWordClass.hpp"
#include "SHAREDvars.hpp"

#ifdef NLC_PREPROCESSOR_MATH
#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE

#ifdef NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
class NLCsubphrase
{
public:

	NLCsubphrase(void);
	~NLCsubphrase(void);

	int lineIndexOfFirstWordInPhrase;
	vector<LRPpreprocessorPlainTextWord*> phraseContents;
	bool hasConjunction;
	int conjunctionType;

	NLCsubphrase* next;
};
#endif

class NLCpreprocessorMathLogicalConditionsClass
{
	private: SHAREDvarsClass SHAREDvars;
	private: NLCpreprocessorSentenceClassClass NLCpreprocessorSentenceClass;
	private: LRPpreprocessorWordClassClass LRPpreprocessorWordClassObject;

	public: bool replaceLogicalConditionNaturalLanguageMathWithSymbols(vector<LRPpreprocessorPlainTextWord*>* lineContents, int logicalConditionOperator, bool* additionalClosingBracketRequired, const bool parallelReplacement);
	public: bool replaceLogicalConditionNaturalLanguageMathWithSymbolsEnd(NLCpreprocessorSentence* fullSentence, const bool additionalClosingBracketRequired);

	public: bool splitMathDetectedLineIntoNLPparsablePhrasesLogicalConditionAddExplicitSubjectTextForConjunctions(NLCpreprocessorSentence* fullSentence, const int* sentenceIndex, const bool additionalClosingBracketRequired);

	#ifdef NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
	public: bool generateLogicalConditionImplicitConjunctionsAndIdentifyCommand(vector<LRPpreprocessorPlainTextWord*>* lineContents, bool* detectedLogicalConditionCommand, vector<LRPpreprocessorPlainTextWord*>* logicalConditionCommandSubphraseContents, int* logicalConditionCommandSubphraseLineIndex);
	public: bool generateSeparateSentencesFromCommand(vector<LRPpreprocessorPlainTextWord*>* logicalConditionCommandSubphraseContents, int currentIndentation, NLCpreprocessorSentence* firstSentenceInLogicalConditionCommandTemp);
	#endif
};


#endif
#endif

#endif
