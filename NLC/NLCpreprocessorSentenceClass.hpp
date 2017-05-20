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
 * File Name: NLCpreprocessorSentenceClass.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2017 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 2a4a 27-April-2017
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/


#ifndef HEADER_NLC_PREPROCESSOR_SENTENCE_CLASS
#define HEADER_NLC_PREPROCESSOR_SENTENCE_CLASS

#include "NLCglobalDefs.hpp"
#include "SHAREDvars.hpp"

class NLCvariable
{
public:

	NLCvariable(void);
	~NLCvariable(void);

	string name;
	int type;
	string typeString;
};

class NLCpreprocessorParsablePhrase
{
public:

	NLCpreprocessorParsablePhrase(void);
	~NLCpreprocessorParsablePhrase(void);

	int sentenceIndex;
	string sentenceContents;	//OLD: sentenceContents
	#ifdef NLC_PREPROCESSOR_MATH;
	int mathTextNLPparsablePhraseIndex;
	#ifdef NLC_PREPROCESSOR_RECORD_PARSABLE_PHRASE_POSITION_APPROXIMATE
	int mathTextNLPparsablePhrasePositionApproximate;	//rough position of parsable phrase within full sentence (first character); will not be accurate due to replaceLogicalConditionNaturalLanguageMathWithSymbolsEnd/restoreExplicitVariableTypes
	#endif
	#endif
	
	NLCpreprocessorParsablePhrase* next;
};

class NLCpreprocessorSentence
{
public:

	NLCpreprocessorSentence(void);
	~NLCpreprocessorSentence(void);

	//int sentenceIndex;
	int indentation;
	bool hasLogicalConditionOperator;
	#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
	int logicalConditionOperator;
	#endif
	#ifdef NLC_PREPROCESSOR_LOGICAL_CONDITION_USE_ROBUST_NLP_INDEPENDENT_CODE
	bool ifDetected;
	bool elseIfDetected;
	bool elseDetected;
	#endif
	#ifdef NLC_PREPROCESSOR_MATH
	bool isMath;
	string mathText;
	int mathTextNLPparsablePhraseTotal;
	NLCpreprocessorParsablePhrase* firstNLPparsablePhraseInList;	//added 2a1a
	#ifdef NLC_PREPROCESSOR_MATH_REPLACE_NUMERICAL_VARIABLES_NAMES_FOR_NLP
	vector<NLCvariable*> mathTextVariables;	//required to be recorded such that future instances of variable name in non-math text can be temporarily replaced with dummy number 9999 for NLP/GIA to parse
	vector<string> variableNamesDetected;	//record of original variable name that has been replaced by dummy number for NLP/GIA to parse
	#endif
	#ifdef NLC_MATH_OBJECTS
	bool mathTextIdentifiesMathValue;
	//bool mathTextNLPparsablePhraseIdentifiesMathValue;
	#endif
	#endif
	#ifdef NLC_PREPROCESSOR_GENERATE_COMMENTS
	string sentenceOriginal;		//sentenceOriginal is stored for both isMath and !isMath (sentenceContentsOriginal is only stored for !isMath)
	string sentenceContentsOriginal;	//this is for !isMath sentences only (it is designed for lines with more than 1 sentence).
	#endif
	#ifdef NLC_PREPROCESSOR_INTERPRET_SINGLE_WORD_SENTENCES_AS_ACTIONS_REPLACE_ACTION_ALSO_DUE_TO_NLP_LIMITATION
	string singleWordSentenceActionName;
	#endif
	
	NLCpreprocessorSentence* next;

};

class NLCfunction
{
public:

	NLCfunction(void);
	~NLCfunction(void);

	string NLCfunctionName;
	NLCpreprocessorSentence* firstNLCsentenceInFunction;
	NLCfunction* next;
};


#ifdef NLC_PREPROCESSOR_MATH
class NLCpreprocessorSentenceClassClass
{
	private: SHAREDvarsClass SHAREDvars;
	public: string generateMathTextNLPparsablePhraseReference(const int sentenceIndexOfFullSentence, const NLCpreprocessorParsablePhrase* currentPhrase);
	#ifdef NLC_PREPROCESSOR_MATH_REPLACE_NUMERICAL_VARIABLES_NAMES_FOR_NLP
	public: int generateDummyNumber(const int predefinedVariableIndex);
	#endif
	#endif
	public: bool isStringNLPparsableWord(string phrase, const bool preprocessorMath);
	public: bool isStringValidVariableName(string phrase, const bool preprocessor);
	public: bool isStringNumberPreprocessorMath(string phrase);
	public: bool isStringNumberOrFractional(string phrase);
		private: bool isDecimalPlace(int indexOfCurrentToken, string* lineContents);
	public: bool isStringAliasFileName(const string phrase);
	#ifdef NLC_VERIFY_LEGAL_TARGET_SOURCE_CHARACTERS
	public: bool isStringIllegalTargetSourceCharacter(const string phrase);
	#endif	
	public: bool getSentenceInFunction(const int sentenceIndex, const NLCfunction* currentNLCfunctionInList, NLCpreprocessorSentence** sentenceFound);
		public: bool getSentenceInSentenceList(const int sentenceIndex, constEffective NLCpreprocessorSentence* firstNLCsentenceInFunction, NLCpreprocessorSentence** sentenceFound);
	public: bool sentencePertainsToLogicalCondition(const NLCpreprocessorSentence* currentNLCsentenceInList);

};

#endif
