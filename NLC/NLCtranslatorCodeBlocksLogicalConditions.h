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
 * File Name: NLCtranslatorCodeBlocksLogicalConditions.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2017 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 1w3b 14-January-2017
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/


#ifndef HEADER_NLC_TRANSLATOR_CODEBLOCKS_LOGICAL_CONDITIONS
#define HEADER_NLC_TRANSLATOR_CODEBLOCKS_LOGICAL_CONDITIONS

#include "GIAentityNodeClass.h"
#include "GIAentityConnectionClass.h"
#include "NLCglobalDefs.h"
#include "NLCcodeBlockClass.h"
#include "NLCclassDefinitionClass.h"
//#ifdef NLC_PREPROCESSOR
#include "NLCpreprocessorSentenceClass.h"
#include "NLCtranslatorCodeBlocksLogicalConditionsAdvanced.h"
#include "NLCtranslatorCodeBlocksOperations.h"
#include "GIAtranslatorOperations.h"	//required for getPrimaryNetworkIndexNodeDefiningInstance{}
#include "NLCprintDefs.h"	//required for NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION
#include "NLCpreprocessorMath.h"	//required for findCharacterAtIndexOrAfterSpace{}
//#endif


#ifdef NLC_PREPROCESSOR_MATH
class NLCtranslatorCodeBlocksLogicalConditionsClass
{
	private: SHAREDvarsClass SHAREDvars;
	private: NLCcodeBlockClassClass NLCcodeBlockClass;
	private: NLCitemClassClass NLCitemClass;
	private: GIAtranslatorOperationsClass GIAtranslatorOperations;
	private: NLCpreprocessorSentenceClassClass NLCpreprocessorSentenceClass;
	private: NLCprintDefsClass NLCprintDefs;
	private: NLCtranslatorCodeBlocksLogicalConditionsAdvancedClass NLCtranslatorCodeBlocksLogicalConditionsAdvanced;
	private: NLCtranslatorCodeBlocksOperationsClass NLCtranslatorCodeBlocksOperations;
	private: NLCpreprocessorMathClass NLCpreprocessorMath;
	public: bool generateCodeBlocksFromMathText(NLCcodeblock** currentCodeBlockInTree, map<int, vector<GIAentityNode*>*>::iterator sentenceIterFirstInFullSentence, int sentenceIndex, NLCsentence* firstNLCsentenceInFullSentence, const string NLCfunctionName);	
		private: bool generateCodeBlocksFromMathTextNLPparsablePhrase(NLCcodeblock** currentCodeBlockInTree, vector<GIAentityNode*>* entityNodesActiveListParsablePhrase, int sentenceIndex, NLCsentence* currentFullSentence, const NLCsentence* parsablePhrase, const int phraseIndex, const int caseIndex);
		#ifdef NLC_MATH_OBJECTS_ADVANCED
			private: int getMathObjectVariableType(vector<GIAentityNode*>* entityNodesActiveListComplete, const int sentenceIndex, NLCsentence* currentFullSentence, const NLCsentence* parsablePhrase);
				private: bool getMathTextSubphraseContainingNLPparsablePhrase(string mathText, const string parsablePhraseReferenceName, string* mathTextSubphraseContainingNLPparsablePhrase, int* mathTextSubphraseContainingNLPparsablePhraseIndex);
					private: bool findMatchingBrackets(string subphraseTemp, int* subphraseStartPositionTemp, int* subphraseEndPositionTemp);
			private: string generateAssignMathTextValueExecuteFunctionMathText(const NLCsentence* currentFullSentence, string parsablePhraseReferenceName, const bool hasLogicalConditionOperator);
				private: bool findInvertedCommasEitherSideOfCharacter(const string* mathText, int indexOfCharacter);
				private: string getTargetValueText(const string* mathText, int indexOfCommand, string command, int progLang);
				private: string getSourceValueText(const string* mathText, const int indexOfCommand, int progLang);
				#ifdef NLC_MATH_OBJECTS_ADVANCED_ADDITIONS
					private: string replaceAllAdditionSymbolsWithAdditionFunction(string text, int progLang);
				#endif
				private: bool removeSurroundingBracketsOfSubphrase(string* subphraseText);
		#endif
			private: bool isNumberOf(const GIAentityNode* entity);
		private: bool generateCodeBlocksFromMathTextNLPparsablePhraseLogicalConditionFor(NLCcodeblock** currentCodeBlockInTree, vector<GIAentityNode*>* entityNodesActiveListComplete, int sentenceIndex, const NLCsentence* currentFullSentence, const NLCsentence* parsablePhrase, const int phraseIndex, NLCcodeblock** currentCodeBlockInTreeAtBaseLevel, const NLCsentence* firstNLCsentenceInFullSentence);
		#ifdef NLC_TRANSLATOR_DO_NOT_REPARSE_CONTEXT_BLOCKS_IF_ALREADY_PARSED_DURING_ENTITY_INITIALISATION
			private: void parseLogicalConditionEntity(NLCcodeblock** currentCodeBlockInTree, GIAentityNode* entity, int sentenceIndex, const bool hasLogicalConditionOperator, GIAentityNode** childEntity, NLCgenerateContextBlocksVariables* generateContextBlocksVariables);
		#else
			private: bool parseParsablePhraseParent(NLCcodeblock** currentCodeBlockInTree, int sentenceIndex, GIAentityNode* parentEntity, NLCgenerateContextBlocksVariables* generateContextBlocksVariables, GIAentityNode** childEntity, const int logicalConditionOperator);
		#endif
	#ifdef NLC_LOGICAL_CONDITION_OPERATIONS_BASED_ON_ACTIONS_BASIC
		private: bool checkIfPhraseContainsAction(vector<GIAentityNode*>* entityNodesActiveListComplete, const int sentenceIndex, constEffective GIAentityNode** logicalConditionOperationObject);
	#endif
	#ifdef NLC_LOGICAL_CONDITION_OPERATIONS_BASED_ON_CONCEPTS
	#ifdef NLC_LOGICAL_CONDITION_OPERATIONS_BASED_ON_CONCEPTS_BASIC
		private: bool checkIfPhraseContainsConceptWithDefinitionLink(vector<GIAentityNode*>* entityNodesActiveListComplete, const int sentenceIndex, constEffective GIAentityNode** logicalConditionOperationObject);
	#else
		private: bool checkIfPhraseContainsConcept(vector<GIAentityNode*>* entityNodesActiveListComplete, const int sentenceIndex, constEffective GIAentityNode** logicalConditionOperationObject);
	#endif
	#ifdef NLC_LOGICAL_CONDITION_OPERATIONS_BASED_ON_CONCEPTS_BASIC_REDEFINITIONS
		private: bool checkIfPhraseContainsSubstanceWithDefinitionLink(vector<GIAentityNode*>* entityNodesActiveListComplete, int sentenceIndex, constEffective GIAentityNode** logicalConditionOperationObject, constEffective GIAentityNode** definitionEntity);
	#endif
	#endif
		private: void setDummyReferenceSetIDforAllEntitiesInPhrase(vector<GIAentityNode*>* entityNodesActiveListComplete, const int sentenceIndex);
	#endif
/*
#ifdef NLC_PREPROCESSOR_MATH
string parsablePhraseGenerateNumberOfElementCounterName(int phraseIndex);
#endif
*/
	private: bool readParsablePhraseEntryEntityChecks(const GIAentityNode* entity);
	#ifdef NLC_PREPROCESSOR_MATH_REPLACE_NUMERICAL_VARIABLES_NAMES_FOR_NLP
	public: bool findDummyNumberAndReplaceWithOriginalNumericalVariableName(vector<GIAentityNode*>* entityNodesActiveListComplete, const int sentenceIndex, const int dummyNumber, string numericalVariableName);
	#endif
};



#endif
