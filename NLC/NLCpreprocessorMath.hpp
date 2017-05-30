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
 * File Name: NLCpreprocessorMath.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2017 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 2b2b 21-May-2017
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/


#ifndef HEADER_NLC_PREPROCESSOR_MATH
#define HEADER_NLC_PREPROCESSOR_MATH

#include "NLCglobalDefs.hpp"
#include "NLCpreprocessorSentenceClass.hpp"
#include "NLCpreprocessorMathLogicalConditions.hpp"
#include "NLCprintDefs.hpp" //required for progLangOpenParameterSpace
#include "SHAREDvars.hpp"	//required for convertStringToLowerCase/isWhiteSpace
#include "GIAentityNodeClass.hpp" //required for GIA_NLP_START_SENTENCE_INDEX and entityNodesActiveListComplete

#ifdef NLC_PREPROCESSOR
#ifdef NLC_PREPROCESSOR_MATH

class NLCpreprocessorMathClass
{
	private: SHAREDvarsClass SHAREDvars;
	private: NLCpreprocessorMathLogicalConditionsClass NLCpreprocessorMathLogicalConditions;
	private: NLCpreprocessorSentenceClassClass NLCpreprocessorSentenceClass;
	public: bool detectMathSymbolsInLine(const string* lineContents);
	public: bool detectAndReplaceIsEqualToNonLogicalConditionTextWithSymbol(string* lineContents, const bool hasLogicalConditionOperator, const bool isMathText);

	#ifdef NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
	public: bool splitMathDetectedLineLogicalConditionCommandIntoSeparateSentences(string* lineContents, int currentIndentation, const NLCpreprocessorSentence* fullSentence, NLCpreprocessorSentence* firstSentenceInLogicalConditionCommandTemp, bool* detectedLogicalConditionCommand);
	#endif

	public: bool splitMathDetectedLineIntoNLPparsablePhrases(string* lineContents, NLCpreprocessorSentence** currentNLCsentenceInList, int* sentenceIndex, const int currentIndentation, string* functionContents, NLCfunction* currentNLCfunctionInList, const NLCfunction* firstNLCfunctionInList);
		public: bool findCharacterAtIndexOrAfterSpace(const string* lineContents, int i, char characterToFind, int* indexOfCharacterFound);
		#ifdef NLC_PREPROCESSOR_MATH_SUPPORT_USER_VARIABLE_TYPE_DECLARATIONS
		private: bool replaceExplicitVariableTypesWithNLPparsablePhraseIllegalWords(string* lineContents);
		private: bool restoreExplicitVariableTypes(string* mathText);
		private: string replaceSubstringAtStartOfString(const string* textOrig, string stringToFind, string replacementString);
		#endif
		private: void addNewMathTextVariable(NLCpreprocessorSentence* sentence, const string variableName, const int variableTypeObject);
		private: void removeLastMathTextVariable(NLCpreprocessorSentence* sentence);

	#ifdef NLC_PREPROCESSOR_MATH_REPLACE_NUMERICAL_VARIABLES_NAMES_FOR_NLP
	public: bool replaceNumericalVariablesWithDummyNumberIfNecessary(string* lineContents, NLCpreprocessorSentence* currentNLCsentenceInList, NLCfunction* currentNLCfunctionInList, const NLCfunction* firstNLCfunctionInList);
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
