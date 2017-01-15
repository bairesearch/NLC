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
 * File Name: NLCpreprocessorMathLogicalConditions.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2015 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 1q12a 22-August-2015
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/


#ifndef HEADER_NLC_PREPROCESSOR_MATH_LOGICAL_CONDITIONS
#define HEADER_NLC_PREPROCESSOR_MATH_LOGICAL_CONDITIONS

#include "NLCglobalDefs.h"
#include "NLCpreprocessorSentenceClass.h"

#ifdef NLC_PREPROCESSOR_MATH
#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE

#ifdef NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
class NLCsubphrase
{
public:

	NLCsubphrase(void);
	~NLCsubphrase(void);

	int lineIndexOfFirstCharacterInPhrase;
	string phraseContents;
	bool hasConjunction;
	int conjunctionType;
	
	NLCsubphrase* next;
};
#endif

bool replaceLogicalConditionNaturalLanguageMathWithSymbols(string* lineContents, int logicalConditionOperator, bool* additionalClosingBracketRequired, bool parallelReplacement);
bool replaceLogicalConditionNaturalLanguageMathWithSymbolsEnd(NLCsentence* firstNLCsentenceInFullSentence, bool additionalClosingBracketRequired);

bool splitMathDetectedLineIntoNLPparsablePhrasesLogicalConditionCommands(NLCsentence* firstNLCsentenceInFullSentence, NLCsentence** currentNLCsentenceInList, int* sentenceIndex, bool additionalClosingBracketRequired, bool detectedLogicalConditionCommand, int phraseIndexOfFirstLogicalCommand, string logicalConditionCommandSubphraseContents);
bool splitMathDetectedLineIntoNLPparsablePhrasesLogicalConditionAddExplicitSubjectTextForConjunctions(NLCsentence* firstNLCsentenceInFullSentence, NLCsentence** currentNLCsentenceInList, int* sentenceIndex, bool additionalClosingBracketRequired);

#ifdef NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
bool generateLogicalConditionImplicitConjunctionsAndIdentifyCommand(string* lineContents, bool* detectedLogicalConditionCommand, bool* foundImplicitConjunctions, string* logicalConditionCommandSubphraseContents);
bool generateSeparateSentencesFromMathTextAndParsablePhrasesInCommand(NLCsentence** currentNLCsentenceInList, NLCsentence* firstPhraseInCommand, string mathTextInCommand, int* sentenceIndex, int sentenceIndexOfFullSentence, int currentIndentation);
#endif
	
#endif
#endif

#endif
