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
 * File Name: NLCtranslatorCodeBlocksOperations.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2017 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 2b3e 25-May-2017
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/


#ifndef HEADER_NLC_TRANSLATOR_CODEBLOCKS_OPERATIONS
#define HEADER_NLC_TRANSLATOR_CODEBLOCKS_OPERATIONS

#include "GIAentityNodeClass.hpp"
#include "GIAentityConnectionClass.hpp"
#include "NLCcodeBlockClass.hpp"
#include "NLCclassDefinitionClass.hpp"
//#ifdef NLC_PREPROCESSOR
#include "NLCpreprocessorSentenceClass.hpp"	//required for
#include "GIAtranslatorOperations.hpp"	//required for getPrimaryNetworkIndexNodeDefiningInstance()
#include "NLCprintDefs.hpp"	//required for NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION
//#endif


class NLCtranslatorCodeBlocksOperationsClass
{
	private: NLCcodeBlockClassClass NLCcodeBlockClass;
	private: NLCitemClassClass NLCitemClass;
	private: SHAREDvarsClass SHAREDvars;
	private: GIAentityNodeClassClass GIAentityNodeClass;
	private: GIAtranslatorOperationsClass GIAtranslatorOperations;
	private: NLCpreprocessorSentenceClassClass NLCpreprocessorSentenceClass;
	public: bool generateCodeBlocksPart3subjectObjectConnections(NLCcodeblock** currentCodeBlockInTree, vector<GIAentityNode*>* entityNodesActiveListSentence, int sentenceIndex, NLCgenerateContextBlocksVariables* generateContextBlocksVariablesLogicalConditionStatement);
		private: bool generateCodeBlocksPart3subjectObjectConnection(NLCcodeblock** currentCodeBlockInTree, int sentenceIndex, GIAentityNode* entity, GIAentityNode* subjectEntity, GIAentityNode* objectEntity, const GIAentityConnection* connection, const bool foundSubject, bool foundObject, const int connectionType, NLCgenerateContextBlocksVariables* generateContextBlocksVariablesLogicalConditionStatement);
			#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS
			private: bool generateObjectInitialisationsFunction(NLCcodeblock** currentCodeBlockInTree, GIAentityNode* actionRelationshipEntity, const int sentenceIndex);
			#endif
			#ifdef NLC_TRANSLATOR_TEST_DEFINITE_ENTITY_EXISTENCE
			private: void generateDefiniteEntityExistenceTest(NLCcodeblock** currentCodeBlockInTree, GIAentityNode* entity, int sentenceIndex, const string genericListAppendName, const NLCgenerateContextBlocksVariables* generateContextBlocksVariablesLogicalConditionStatement, const bool checkParent);
			#endif

		
	public: bool generateContextBlocks(NLCcodeblock** currentCodeBlockInTree, GIAentityNode* parentEntity, int sentenceIndex, NLCgenerateContextBlocksVariables* generateContextBlocksVariables, const bool generatedParentContext, const string genericListAppendName);
		#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN
		private: bool generateContextBlocksCategories(NLCcodeblock** currentCodeBlockInTree, GIAentityNode* parentEntity, int sentenceIndex, NLCgenerateContextBlocksVariables* generateContextBlocksVariables, const bool generatedParentContext, const string genericListAppendName);
		#endif
			private: bool generateContextBlocksSimple(NLCcodeblock** currentCodeBlockInTree, GIAentityNode* parentEntity, int sentenceIndex, NLCgenerateContextBlocksVariables* generateContextBlocksVariables, const bool generatedParentContext, const string genericListAppendName);
				public: bool createCodeBlockForStatements(NLCcodeblock** currentCodeBlockInTree, string parentInstanceName, GIAentityNode* entity, int sentenceIndex, NLCgenerateContextBlocksVariables* generateContextBlocksVariables);
					private: bool createCodeBlockForConnectionType(const int connectionType, NLCcodeblock** currentCodeBlockInTree, string parentInstanceName, GIAentityNode* entity, int sentenceIndex, NLCgenerateContextBlocksVariables* generateContextBlocksVariables);
						private: bool sameReferenceSetReferencingConnectionCheck(const GIAentityConnection* targetConnection, const NLCgenerateContextBlocksVariables* generateContextBlocksVariables);
						private: bool createCodeBlockForGivenProperty(NLCcodeblock** currentCodeBlockInTree, string parentInstanceName, GIAentityNode* propertyRelationshipEntity, const int sentenceIndex, NLCgenerateContextBlocksVariables* generateContextBlocksVariables, constEffective GIAentityNode** objectEntity, bool* generateContextForObject);
						private: bool createCodeBlockForGivenCondition(NLCcodeblock** currentCodeBlockInTree, const string parentInstanceName, GIAentityNode* conditionRelationshipEntity, const int sentenceIndex, NLCgenerateContextBlocksVariables* generateContextBlocksVariables, GIAentityNode** objectEntity, bool* generateContextForObject);
						#ifdef NLC_RECORD_ACTION_HISTORY
						private: bool createCodeBlockForGivenAction(NLCcodeblock** currentCodeBlockInTree, const string parentInstanceName, GIAentityNode* actionRelationshipEntity, const int sentenceIndex, NLCgenerateContextBlocksVariables* generateContextBlocksVariables, GIAentityNode** objectEntity, bool* generateContextForObject);
						private: bool createCodeBlockForGivenActionIncoming(NLCcodeblock** currentCodeBlockInTree, const string parentInstanceName, GIAentityNode* actionRelationshipEntity, const int sentenceIndex, NLCgenerateContextBlocksVariables* generateContextBlocksVariables, GIAentityNode** objectEntity, bool* generateContextForObject);
						#endif
						#ifdef NLC_TRANSLATOR_GENERATE_CONTEXT_BLOCKS_PARSE_DEFINITIONS
						private: bool createCodeBlockForGivenDefinition(NLCcodeblock** currentCodeBlockInTree, const string parentInstanceName, GIAentityNode* definitionRelationshipEntity, const int sentenceIndex, const NLCgenerateContextBlocksVariables* generateContextBlocksVariables, constEffective GIAentityNode** objectEntity, bool* generateContextForObject);
						#ifdef NLC_ADVANCED_REFERENCING_SUPPORT_ALIASES
						private: bool createCodeBlockForGivenAlias(NLCcodeblock** currentCodeBlockInTree, const GIAentityNode* entity, GIAentityNode* definitionRelationshipEntity, const int sentenceIndex, const NLCgenerateContextBlocksVariables* generateContextBlocksVariables, constEffective GIAentityNode** objectEntity, bool* generateContextForObject);
						#endif
						#endif
						#ifdef NLC_TRANSLATOR_GENERATE_CONTEXT_BLOCKS_PARSE_PARENT_OF_TARGET_AND_MULTIPLE_DEFINITE_ENTITIES
						private: string generateCandidateObjectName(const GIAentityNode* objectEntity);
						#endif
			#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN
			private: bool createCodeBlockForStatementsForDefinitionChildren(NLCcodeblock** currentCodeBlockInTree, NLCcodeblock** lastCodeBlockInTree, GIAentityNode* parentInstance, GIAentityNode* parentConcept, int sentenceIndex, NLCgenerateContextBlocksVariables* generateContextBlocksVariables, const bool generateContext, const string genericListAppendName);
				private: bool addEntityToCategoryList(NLCcodeblock** currentCodeBlockInTree, const GIAentityNode* entity, const GIAentityNode* propertyRelationshipObjectEntity, const string genericListAppendName, const NLCgenerateContextBlocksVariables* generateContextBlocksVariables, const int sentenceIndex, const bool castToCategoryType);
			#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN_SUBCLASSES
			private: bool findNearestSubClassParentEntityCorrespondingToSubclassEntityInSameContext(GIAentityNode* subclassEntity, GIAentityNode** nearestSubclassParentEntity);
				private: bool entityHasPropertyParent(GIAentityNode* entity, const string propertyParentName);
				private: bool createCodeBlockForStatementsForNearestSubClassParentReference(NLCcodeblock** currentCodeBlockInTree, NLCcodeblock** lastCodeBlockInTree, GIAentityNode* subclassEntity, GIAentityNode* nearestSubclassParentEntity, int sentenceIndex, NLCgenerateContextBlocksVariables* generateContextBlocksVariables, const bool generateContext, const string genericListAppendName);
			#endif
			#endif

	private: bool getParentAndInitialiseParentIfNecessary(NLCcodeblock** currentCodeBlockInTree, GIAentityNode* currentEntity, int sentenceIndex, NLCgenerateContextBlocksVariables* generateContextBlocksVariables, bool parseLogicalConditions, GIAentityNode** parentEntity, bool* newInitialisation);
	public: bool getParentAndInitialiseParentIfNecessaryAndGenerateContextBlocks(NLCcodeblock** currentCodeBlockInTree, GIAentityNode* currentEntity, int sentenceIndex, NLCgenerateContextBlocksVariables* generateContextBlocksVariables, bool parseLogicalConditions, GIAentityNode** parentEntity, bool* newInitialisation);
	public: bool generateParentInitialisationCodeBlockWithChecks(NLCcodeblock** currentCodeBlockInTree, GIAentityNode* parentEntity, int sentenceIndex, const bool parseLogicalConditions, const bool testOnly);
		private: bool generateObjectInitialisations(NLCcodeblock** currentCodeBlockInTree, GIAentityNode* entity, int sentenceIndex);
			private: bool generateObjectInitialisationsForConnectionType(NLCcodeblock** currentCodeBlockInTree, const int connectionType, GIAentityNode* entity, int sentenceIndex);
				private: bool generateCodeBlocksAddConnection(NLCcodeblock** currentCodeBlockInTree, const int connectionType, const GIAentityConnection* connection, GIAentityNode* subjectEntity, GIAentityNode* objectEntity, GIAentityNode* actionOrConditionRelationshipEntity, const bool foundSubject, const bool foundObject, int sentenceIndex, const GIAentityNode* subjectParentEntity, const bool primary);
					#ifdef NLC_RECORD_ACTION_HISTORY_GENERALISABLE_DO_NOT_EXECUTE_PAST_TENSE_ACTIONS
					private: bool isNonImmediateAction(const GIAentityNode* actionRelationshipEntity);
					private: bool isPotentialAction(const GIAentityNode* actionRelationshipEntity);
					#endif
				#ifdef NLC_TRANSLATOR_LOGICAL_CONDITIONS_BOOLEAN_STATEMENTS_INTERPRET_SUBJECT_AND_OBJECT_INDEPENDENTLY
				private: bool generateCodeBlocksVerifyConnection(NLCcodeblock** currentCodeBlockInTree, const int connectionType, const GIAentityConnection* connection, GIAentityNode* subjectEntity, GIAentityNode* objectEntity, GIAentityNode* actionOrConditionRelationshipEntity, const bool foundSubject, const bool foundObject, const int sentenceIndex, const bool effectiveEach, NLCgenerateContextBlocksVariables* generateContextBlocksVariablesLogicalConditionStatement);
				#endif
			/*
			bool getActionSubjectCheckSameReferenceSetAndSentence(GIAentityNode* actionRelationshipEntity, GIAentityNode** subjectEntity, GIAentityConnection** actionSubjectConnection, int sentenceIndex, bool sameReferenceSet);
				bool getActionSubjectEntityConnection(GIAentityNode* actionRelationshipEntity, int sentenceIndex, GIAentityConnection** actionSubjectConnection);
			bool getActionObjectCheckSameReferenceSetAndSentence(GIAentityNode* actionRelationshipEntity, GIAentityNode** objectEntity, GIAentityConnection** actionObjectConnection, int sentenceIndex, bool sameReferenceSet);
				bool getActionObjectEntityConnection(GIAentityNode* actionRelationshipEntity, int sentenceIndex, GIAentityConnection** actionObjectConnection);
			bool getConditionSubjectCheckSameReferenceSetAndSentence(GIAentityNode* conditionRelationshipEntity, GIAentityNode** subjectEntity, GIAentityConnection** conditionSubjectConnection, int sentenceIndex, bool sameReferenceSet);
				bool getConditionSubjectEntityConnection(GIAentityNode* conditionRelationshipEntity, int sentenceIndex, GIAentityConnection** conditionSubjectConnection);
			bool getConditionObjectCheckSameReferenceSetAndSentence(GIAentityNode* conditionRelationshipEntity, GIAentityNode** objectEntity, GIAentityConnection** conditionObjectConnection, int sentenceIndex, bool sameReferenceSet);
				bool getConditionObjectEntityConnection(GIAentityNode* conditionRelationshipEntity, int sentenceIndex, GIAentityConnection** conditionObjectConnection);
			*/
				public: bool getEntityCheckSameReferenceSetAndSentence(GIAentityNode* entity, GIAentityNode** entityToFind, GIAentityConnection** connection, const int sentenceIndex, const bool sameReferenceSet, int connectionType);
					private: bool connectionTypeIsCondition(const int connectionType, const GIAentityConnection* connection);
					private: bool getEntityConnection(GIAentityNode* entity, const int sentenceIndex, GIAentityConnection** entityConnection, int connectionType);

	public: GIAentityNode* getParent(GIAentityNode* currentEntity, int sentenceIndex);
		public: GIAentityNode* getParent(GIAentityNode* currentEntity, int sentenceIndex, NLCgenerateContextBlocksVariables* generateContextBlocksVariables);
	public: bool getParentAndGenerateContextBlocks(NLCcodeblock** currentCodeBlockInTree, GIAentityNode* currentEntity, int sentenceIndex, NLCgenerateContextBlocksVariables* generateContextBlocksVariables);

	private: bool generateContextForChildEntity(NLCcodeblock** currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* childEntity, int sentenceIndex, const bool topLevel, NLCgenerateContextBlocksVariables* generateContextBlocksVariablesLogicalConditionStatement);
		public: bool generateContextBlocksForParentEntity(NLCcodeblock** currentCodeBlockInTree, GIAentityNode* childEntity, GIAentityNode* parentEntity, const int sentenceIndex, NLCgenerateContextBlocksVariables* generateContextBlocksVariables);
		#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_FOR_EACH_CHILD_GET_PARENT
		public: GIAentityNode* getSameReferenceSetUniqueParent(GIAentityNode* currentEntity, int sentenceIndex, GIAentityNode* generateObjectInitialisationsLastParent, bool* foundParentEntityNew, bool parseConditionParents, bool checkIsDefinite);
		#endif

	#ifdef GIA_TRANSLATOR_DREAM_MODE_LINK_SPECIFIC_CONCEPTS_AND_ACTIONS
	public: void generateObjectInitialisationsBasedOnConcepts(GIAentityNode* targetEntity, GIAentityNode* entity, NLCcodeblock** currentCodeBlockInTree, int sentenceIndex, const bool newlyDeclaredEntityInCategoryList);
		private: void generateObjectInitialisationsBasedOnConceptsRecurse(GIAentityNode* targetEntity, GIAentityNode* definitionRelationshipObjectEntity, NLCcodeblock** currentCodeBlockInTree, int sentenceIndex, const GIAentityNode* parentEntity, const string parentConditionName, const bool newlyDeclaredEntityInCategoryList);
	#endif

	#ifdef NLC_ADVANCED_REFERENCING_SUPPORT_ALIASES
	public: void fillFunctionAliasClassList(vector<GIAentityNode*>* entityNodesActiveListComplete);
	#endif

	public: bool checkSpecialCaseEntity(const GIAentityNode* entity, const bool detectActions);
	private: bool checkNetworkIndexTypeEntity(const GIAentityNode* entity);

	#ifdef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES
	private: bool generateContextBasedOnDeclaredParent(GIAentityNode* entity, NLCcodeblock** currentCodeBlockInTree, const bool topLevel, const GIAentityNode* generateObjectInitialisationsLastParent, int sentenceIndex, const NLCgenerateContextBlocksVariables* generateContextBlocksVariablesLogicalConditionStatement);
	#endif

	#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_FOR_EACH_CHILD_GET_PARENT_ORIGINAL_IMPLEMENTATION
	private: void addIntermediaryImplicitlyDeclaredEntityToLocalList(NLCcodeblock** currentCodeBlockInTree, const GIAentityNode* childEntity, const int sentenceIndex);
	#endif

	private: bool checkNumerosity(const GIAentityNode* entity);

	private: bool generateObjectInitialisationsAction(NLCcodeblock** currentCodeBlockInTree, GIAentityNode* actionRelationshipEntity, const int sentenceIndex);

	private: bool checkParentExists(GIAentityNode* object, const string parentName);

	#ifdef NLC_TRANSLATOR_LOGICAL_CONDITIONS_BOOLEAN_STATEMENTS_INTERPRET_SUBJECT_AND_OBJECT_INDEPENDENTLY
	private: void secondaryComparisonSetIDinstance(GIAentityNode* entity);
	private: void secondaryComparisonRestoreIDinstance(GIAentityNode* entity);
	#endif

	private: NLCpreprocessorSentence* getFirstNLCsentenceInList();
	public: void setFirstNLCsentenceInList(NLCpreprocessorSentence* firstNLCsentenceInListNew);
	public: bool checkIndefiniteEntityCorrespondingToDefiniteEntityInSameContext(const GIAentityNode* indefiniteEntity, const GIAentityNode* definiteEntity, int* indentationDifferenceFound);

};

#endif
