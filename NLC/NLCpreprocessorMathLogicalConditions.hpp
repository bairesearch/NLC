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
 * File Name: NLCpreprocessorMathLogicalConditions.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2017 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler
 * Project Version: 2d1a 10-July-2017
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/


#ifndef HEADER_NLC_PREPROCESSOR_MATH_LOGICAL_CONDITIONS
#define HEADER_NLC_PREPROCESSOR_MATH_LOGICAL_CONDITIONS

#include "NLCglobalDefs.hpp"
#include "NLCpreprocessorSentenceClass.hpp"
#include "GIApreprocessorMultiwordReductionClass.hpp"
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
	vector<GIApreprocessorWord*> phraseContents;
	bool hasConjunction;
	int conjunctionType;

	NLCsubphrase* next;
};
#endif

class NLCpreprocessorMathLogicalConditionsClass
{
	private: SHAREDvarsClass SHAREDvars;
	private: NLCpreprocessorSentenceClassClass NLCpreprocessorSentenceClass;
	private: GIApreprocessorMultiwordReductionClassClass GIApreprocessorMultiwordReductionClassObject;

	public: bool replaceLogicalConditionNaturalLanguageMathWithSymbols(vector<GIApreprocessorWord*>* lineContents, int logicalConditionOperator, bool* additionalClosingBracketRequired, const bool parallelReplacement);
	public: bool replaceLogicalConditionNaturalLanguageMathWithSymbolsEnd(NLCpreprocessorSentence* fullSentence, const bool additionalClosingBracketRequired);

	public: bool splitMathDetectedLineIntoNLPparsablePhrasesLogicalConditionAddExplicitSubjectTextForConjunctions(NLCpreprocessorSentence* fullSentence, const int* sentenceIndex, const bool additionalClosingBracketRequired);

	#ifdef NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
	public: bool generateLogicalConditionImplicitConjunctionsAndIdentifyCommand(vector<GIApreprocessorWord*>* lineContents, bool* detectedLogicalConditionCommand, vector<GIApreprocessorWord*>* logicalConditionCommandSubphraseContents, int* logicalConditionCommandSubphraseLineIndex);
	public: bool generateSeparateSentencesFromCommand(vector<GIApreprocessorWord*>* logicalConditionCommandSubphraseContents, int currentIndentation, NLCpreprocessorSentence* firstSentenceInLogicalConditionCommandTemp);
	#endif
};


#endif
#endif

#endif
