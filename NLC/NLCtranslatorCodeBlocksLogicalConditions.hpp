 /*******************************************************************************
 *
 * License: GNU Affero General Public License version 3 (AGPLv3)
 *
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: NLCtranslatorCodeBlocksLogicalConditions.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2022 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler
 * Project Version: 2p1a 05-June-2022
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 * /
 *******************************************************************************/


#ifndef HEADER_NLC_TRANSLATOR_CODEBLOCKS_LOGICAL_CONDITIONS
#define HEADER_NLC_TRANSLATOR_CODEBLOCKS_LOGICAL_CONDITIONS

#include "GIAentityNodeClass.hpp"
#include "GIAentityConnectionClass.hpp"
#include "NLCglobalDefs.hpp"
#include "NLCcodeBlockClass.hpp"
#include "NLCclassDefinitionClass.hpp"
//#ifdef NLC_PREPROCESSOR
#include "NLCpreprocessorSentenceClass.hpp"
#include "NLCtranslatorCodeBlocksLogicalConditionsAdvanced.hpp"
#include "NLCtranslatorCodeBlocksOperations.hpp"
#include "GIAtranslatorOperations.hpp"	//required for getPrimaryNetworkIndexNodeDefiningInstance{}
#include "NLCprintDefs.hpp"	//required for NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION
#include "NLCpreprocessorMath.hpp"	//required for findCharacterAtIndexOrAfterSpace{}
#include "LRPpreprocessorWordClass.hpp"
#include "LRPpreprocessorWordIdentification.hpp"
//#endif


class NLCtranslatorCodeBlocksLogicalConditionsClass
{
	private: SHAREDvarsClass SHAREDvars;
	private: NLCcodeBlockClassClass NLCcodeBlockClass;
	private: NLCitemClassClass NLCitemClass;
	private: GIAtranslatorOperationsClass GIAtranslatorOperations;
	private: NLCpreprocessorSentenceClassClass NLCpreprocessorSentenceClass;
	private: LRPpreprocessorWordClassClass LRPpreprocessorWordClassObject;
	private: NLCprintDefsClass NLCprintDefs;
	private: NLCtranslatorCodeBlocksLogicalConditionsAdvancedClass NLCtranslatorCodeBlocksLogicalConditionsAdvanced;
	private: NLCtranslatorCodeBlocksOperationsClass NLCtranslatorCodeBlocksOperations;
	private: LRPpreprocessorWordIdentificationClass LRPpreprocessorWordIdentification;
	private: NLCpreprocessorMathClass NLCpreprocessorMath;
	#ifdef NLC_PREPROCESSOR_MATH
	public: bool generateCodeBlocksFromMathText(NLCcodeblock** currentCodeBlockInTree, map<int, vector<GIAentityNode*>*>::iterator sentenceIterFirstInFullSentence, int sentenceIndex, NLCpreprocessorSentence* fullSentence, const string NLCfunctionName);	
		private: bool generateCodeBlocksFromMathTextNLPparsablePhrase(NLCcodeblock** currentCodeBlockInTree, vector<GIAentityNode*>* entityNodesActiveListParsablePhrase, int sentenceIndex, NLCpreprocessorSentence* currentFullSentence, const NLCpreprocessorParsablePhrase* parsablePhrase, const int phraseIndex, const int caseIndex);
			private: int getMathObjectVariableTypeAfterGIA(vector<GIAentityNode*>* entityNodesActiveListComplete, const int sentenceIndex, NLCpreprocessorSentence* currentFullSentence, const NLCpreprocessorParsablePhrase* parsablePhrase);
			//private: int getMathObjectVariableTypeBeforeGIA(NLCpreprocessorSentence* currentFullSentence, const NLCpreprocessorParsablePhrase* parsablePhrase);	//not currently used
				private: bool getMathObjectVariableTypeBooleanExpressionAfterGIA(vector<GIAentityNode*>* entityNodesActiveListComplete, const int sentenceIndex);
				public: bool getMathObjectVariableTypeBooleanExpressionBeforeGIAestimate(NLCpreprocessorSentence* currentFullSentence, const NLCpreprocessorParsablePhrase* parsablePhrase);
					private: bool isWordAuxiliaryOrVerb(LRPpreprocessorPlainTextWord* currentWord);
				private: int getMathObjectVariableTypeSharedWrapper(bool foundBooleanStatementExpression, NLCpreprocessorSentence* currentFullSentence, const NLCpreprocessorParsablePhrase* parsablePhrase);
					private: int getMathObjectVariableTypeShared(NLCpreprocessorSentence* currentFullSentence, const NLCpreprocessorParsablePhrase* parsablePhrase, string* mathTextSubphraseContainingNLPparsablePhraseRecord);
						public: bool getMathTextSubphraseContainingNLPparsablePhrase(string mathText, const string parsablePhraseReferenceName, string* mathTextSubphraseContainingNLPparsablePhrase, int* mathTextSubphraseContainingNLPparsablePhraseStartIndex, int* mathTextSubphraseContainingNLPparsablePhraseEndIndex);
							private: bool findMatchingBrackets(string subphraseTemp, int* subphraseStartPositionTemp, int* subphraseEndPositionTemp);
			#ifdef NLC_MATH_OBJECTS_ADVANCED
			private: string generateAssignMathTextValueExecuteFunctionMathText(const NLCpreprocessorSentence* currentFullSentence, string parsablePhraseReferenceName, const bool hasLogicalConditionOperator);
				private: bool findInvertedCommasEitherSideOfCharacter(const string* mathText, int indexOfCharacter);
				private: string getTargetValueText(const string* mathText, int indexOfCommand, string command, int progLang);
				private: string getSourceValueText(const string* mathText, const int indexOfCommand, int progLang);
					#ifdef NLC_MATH_OBJECTS_ADVANCED_ADDITIONS
					private: string replaceAllAdditionSymbolsWithAdditionFunction(string text, int progLang);
					#endif
				private: bool removeSurroundingBracketsOfSubphrase(string* subphraseText);
			private: bool isNumberOf(const GIAentityNode* entity);
		private: bool generateCodeBlocksFromMathTextNLPparsablePhraseLogicalConditionFor(NLCcodeblock** currentCodeBlockInTree, vector<GIAentityNode*>* entityNodesActiveListComplete, int sentenceIndex, const NLCpreprocessorSentence* currentFullSentence, const NLCpreprocessorParsablePhrase* parsablePhrase, const int phraseIndex, NLCcodeblock** currentCodeBlockInTreeAtBaseLevel, const NLCpreprocessorSentence* fullSentence);
			#ifdef NLC_TRANSLATOR_DO_NOT_REPARSE_CONTEXT_BLOCKS_IF_ALREADY_PARSED_DURING_ENTITY_INITIALISATION
			private: void parseLogicalConditionEntity(NLCcodeblock** currentCodeBlockInTree, GIAentityNode* entity, int sentenceIndex, const bool hasLogicalConditionOperator, GIAentityNode** childEntity, NLCgenerateContextBlocksVariables* generateContextBlocksVariables);
			#else
			private: bool parseParsablePhraseParent(NLCcodeblock** currentCodeBlockInTree, int sentenceIndex, GIAentityNode* parentEntity, NLCgenerateContextBlocksVariables* generateContextBlocksVariables, GIAentityNode** childEntity, const int logicalConditionOperator);
			#endif
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
		private: bool checkIfPhraseContainsSubstanceWithDefinitionLink(vector<GIAentityNode*>* entityNodesActiveListComplete, int sentenceIndex, constEffective GIAentityNode** logicalConditionOperationObject, constEffective GIAentityNode** definitionRelationshipObjectEntity);
		#endif
		#endif
		private: void setDummyReferenceSetIDforAllEntitiesInPhrase(vector<GIAentityNode*>* entityNodesActiveListComplete, const int sentenceIndex);
/*
#ifdef NLC_PREPROCESSOR_MATH
string parsablePhraseGenerateNumberOfElementCounterName(int phraseIndex);
#endif
*/
	private: bool readParsablePhraseEntryEntityChecks(const GIAentityNode* entity);
	#ifdef NLC_PREPROCESSOR_MATH_REPLACE_NUMERICAL_VARIABLES_NAMES_FOR_NLP
	public: bool findDummyNumberAndReplaceWithOriginalNumericalVariableName(vector<GIAentityNode*>* entityNodesActiveListComplete, const int sentenceIndex, const int dummyNumber, string numericalVariableName);
	#endif
	#endif
};



#endif
