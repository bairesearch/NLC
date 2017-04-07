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
 * File Name: NLCpreprocessor.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2017 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 2a3b 26-March-2017
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/


#ifndef HEADER_NLC_PREPROCESSOR
#define HEADER_NLC_PREPROCESSOR

#include "NLCglobalDefs.hpp"
#include "NLCpreprocessorSentenceClass.hpp"
#include "NLCpreprocessorMath.hpp"
#include "NLCpreprocessorMathLogicalConditions.hpp"
#include "SHAREDvars.hpp"	//required for convertStringToLowerCase/isWhiteSpace
#include "GIAentityNodeClass.hpp" //required for GIA_NLP_START_SENTENCE_INDEX and entityNodesActiveListComplete
#include "GIApreprocessorMultiwordReduction.hpp"	//required for isIntrawordPunctuationMark only


#ifdef NLC_PREPROCESSOR
class NLCpreprocessorClass
{
	private: SHAREDvarsClass SHAREDvars;
	private: NLCpreprocessorMathClass NLCpreprocessorMath;
	private: GIApreprocessorMultiwordReductionClass GIApreprocessorMultiwordReduction;
	private: NLCpreprocessorSentenceClassClass NLCpreprocessorSentenceClass;
	public: bool preprocessTextForNLC(const string inputFileName, NLCfunction* firstNLCfunctionInList, bool* detectedFunctions, int* numberOfInputFilesInList, vector<string>* inputTextFileNameList, const string outputFileName);
		#ifdef NLC_PREPROCESSOR_REDUCE_QUOTES_TO_SINGLE_WORDS
		private: bool reduceQuotesToSingleWords(const string lineText, string* updatedLineText);
		#endif
		private: void addNonLogicalConditionSentenceToList(string* sentenceContents, NLCpreprocessorSentence** currentNLCsentenceInList, int* sentenceIndex, const int currentIndentation, NLCfunction* currentNLCfunctionInList, const NLCfunction* firstNLCfunctionInList);
		private: void extractIndentationFromCurrentLine(string* currentLine, int* currentIndentation, string* lineContents, string* indentationContents);
		#ifdef NLC_INPUT_FUNCTION_LISTS
		public: bool detectFunctionHeader(const string* lineContents);
		public: string getFunctionNameFromFunctionHeader(const string* lineContents);
		private: string generateNLCfunctionFileName(const string NLCfunctionName);
		#endif
		private: bool detectLogicalConditionOperatorAtStartOfLine(const string* lineContents, int* logicalConditionOperator);
		private: string removePrependingWhiteSpace(string sentenceContents);
		#ifdef NLC_MATH_OBJECTS_ADVANCED
		private: bool detectMathObjectStringDelimiter(string* lineContents);
		#endif
};
#endif

#endif
