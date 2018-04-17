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
 * Project: Natural Language Compiler
 * Project Version: 2e3a 16-December-2017
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
#include "GIApreprocessor.hpp"
#include "GIApreprocessorMultiwordReductionClass.hpp"
#include "GIAtranslatorOperations.hpp"


#ifdef NLC_PREPROCESSOR
class NLCpreprocessorClass
{
	private: SHAREDvarsClass SHAREDvars;
	private: NLCpreprocessorMathClass NLCpreprocessorMath;
	private: GIApreprocessorClass GIApreprocessor;
	private: GIApreprocessorMultiwordReductionClassClass GIApreprocessorMultiwordReductionClassObject;
	private: NLCpreprocessorSentenceClassClass NLCpreprocessorSentenceClass;
	public: bool preprocessTextForNLCwrapper(const string inputFileName, NLCfunction** firstNLCfunctionInList, bool* detectedFunctions, int* numberOfFunctionsInList, vector<string>* inputTextFileNameList, const string outputFileName);
		public: bool preprocessTextForNLCextractFunctionsAndCreatePreprocessSentences(vector<string>* fileLinesList, NLCfunction* firstNLCfunctionInList, bool* detectedFunctions, int* numberOfFunctionsInList, vector<string>* inputTextFileNameList);
			#ifdef NLC_INPUT_FUNCTION_LISTS_PREPROCESSOR
			private: bool preprocessTextForNLCextractFunctions(vector<string>* fileLinesList, NLCfunction* firstNLCfunctionInList, bool* detectedFunctions, int* numberOfFunctionsInList, vector<string>* inputTextFileNameList);
			#endif
				private: string printStringVector(vector<string>* stringVector);	
		private: bool preprocessTextForNLC(NLCfunction* firstNLCfunctionInList, bool detectedFunctions, int numberOfFunctionsInList, const string outputFileName);
			private: void addNonLogicalConditionSentenceToList(vector<GIApreprocessorWord*>* lineContents, NLCpreprocessorSentence** currentNLCsentenceInList, int* sentenceIndex, const int currentIndentation, NLCfunction* currentNLCfunctionInList, const NLCfunction* firstNLCfunctionInList);
			#ifdef NLC_INPUT_FUNCTION_LISTS
			public: bool detectFunctionHeader(const string* lineContents);
			public: string getFunctionNameFromFunctionHeader(const string* lineContents);
			private: string generateNLCfunctionFileName(const string NLCfunctionName);
			#endif
			private: bool detectLogicalConditionOperatorAtStartOfLine(const vector<GIApreprocessorWord*>* lineContents, int* logicalConditionOperator);
			#ifdef NLC_MATH_OBJECTS_ADVANCED
			private: bool detectMathObjectStringDelimiter(const vector<GIApreprocessorWord*>* lineContents);
			#endif
};
#endif

#endif
