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
 * File Name: NLCtranslatorCodeBlocksOperations.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2014 Baxter AI (baxterai.com)
 * Project: Natural Language Programming Interface (compiler)
 * Project Version: 1l12d 07-November-2014
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/


#ifndef HEADER_NLC_TRANSLATOR_CODEBLOCKS_OPERATIONS
#define HEADER_NLC_TRANSLATOR_CODEBLOCKS_OPERATIONS

#include <iostream>
#include <fstream>
#include <ctime>
#include <cstring>
#include <cstdlib>	//for random number generation
#include <cmath>
#include <string>
#include <vector>
using namespace std;

#include "GIAentityNodeClass.h"
#include "GIAentityConnectionClass.h"
#include "NLCcodeBlockClass.h"
#include "NLCclassDefinitionClass.h"
//#ifdef NLC_USE_PREPROCESSOR
#include "NLCpreprocessorSentenceClass.h"	//required for 
//#endif

void generateActionCodeBlocks(NLCcodeblock ** currentCodeBlockInTree, GIAentityNode * actionEntity, int sentenceIndex, string NLCfunctionName);
	#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS
	void initialiseFunctionArguments(NLCcodeblock ** currentCodeBlockInTree, GIAentityNode * actionEntity, int sentenceIndex);
	#endif
	#ifdef NLC_RECORD_ACTION_HISTORY_GENERALISABLE_DO_NOT_EXECUTE_PAST_TENSE_ACTIONS
	bool hasTimeConditionNodePast(GIAentityNode * actionEntity);
	#endif
		
bool getParentAndInitialiseParentIfNecessaryOrGenerateContextBlocks(NLCcodeblock ** currentCodeBlockInTree, GIAentityNode * currentEntity, int sentenceIndex, NLCgenerateContextBlocksVariables * generateContextBlocksVariables, bool parseConditionParents, bool parseLogicalConditions);

bool generateContextBlocks(NLCcodeblock ** currentCodeBlockInTree, GIAentityNode * parentEntity, int sentenceIndex, NLCgenerateContextBlocksVariables * generateContextBlocksVariables, bool generatedParentContext, string genericListAppendName);
	#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN
	bool generateContextBlocksCategories(NLCcodeblock ** currentCodeBlockInTree, GIAentityNode * parentEntity, int sentenceIndex, NLCgenerateContextBlocksVariables * generateContextBlocksVariables, bool generatedParentContext, string genericListAppendName);
		bool generateContextBlocksSimple(NLCcodeblock ** currentCodeBlockInTree, GIAentityNode * parentEntity, int sentenceIndex, NLCgenerateContextBlocksVariables * generateContextBlocksVariables, bool generatedParentContext, string genericListAppendName);
		#endif	
			bool createCodeBlockForStatements(NLCcodeblock ** currentCodeBlockInTree, string parentInstanceName, GIAentityNode* entity, int sentenceIndex, NLCgenerateContextBlocksVariables * generateContextBlocksVariables);
				bool createCodeBlockForConnectionType(int connectionType, NLCcodeblock ** currentCodeBlockInTree, string parentInstanceName, GIAentityNode * entity, int sentenceIndex, NLCgenerateContextBlocksVariables * generateContextBlocksVariables);
					bool createCodeBlockForGivenProperty(NLCcodeblock ** currentCodeBlockInTree, string parentInstanceName, GIAentityNode* propertyEntity, int sentenceIndex, NLCgenerateContextBlocksVariables * generateContextBlocksVariables);
					bool createCodeBlockForGivenCondition(NLCcodeblock ** currentCodeBlockInTree, string parentInstanceName, GIAentityNode* conditionEntity, int sentenceIndex, NLCgenerateContextBlocksVariables * generateContextBlocksVariables);
					#ifdef NLC_RECORD_ACTION_HISTORY
					bool createCodeBlockForGivenAction(NLCcodeblock ** currentCodeBlockInTree, string parentInstanceName, GIAentityNode* actionEntity, int sentenceIndex, NLCgenerateContextBlocksVariables * generateContextBlocksVariables);
					bool createCodeBlockForGivenActionIncoming(NLCcodeblock ** currentCodeBlockInTree, string parentInstanceName, GIAentityNode* actionEntity, int sentenceIndex, NLCgenerateContextBlocksVariables * generateContextBlocksVariables);
					#endif
					#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS_ADVANCED
					bool hasConjunctionConditionConnection(GIAentityNode * conditionEntity, GIAentityNode * primaryEntityInLogicalConditionConjunctionSubset, int logicalConditionConjunctionIndex, GIAentityNode ** foundLogicalConditionConjunction);
					#endif
		#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN
		bool createCodeBlockForStatementsForDefinitionChildren(NLCcodeblock ** currentCodeBlockInTree, NLCcodeblock ** lastCodeBlockInTree, GIAentityNode* parentInstance, GIAentityNode* parentSubstanceConcept, int sentenceIndex, NLCgenerateContextBlocksVariables * generateContextBlocksVariables, bool generateContext, string genericListAppendName);
			bool addPropertyToCategoryList(NLCcodeblock ** currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* propertyEntity, string genericListAppendName, NLCgenerateContextBlocksVariables * generateContextBlocksVariables);
		#endif
		
#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
bool generateCodeBlocksObjectInitialisationsForEntity(NLCcodeblock ** currentCodeBlockInTree, GIAentityNode * entity, int sentenceIndex);
#endif

bool getParentAndGenerateParentInitialisationCodeBlock(NLCcodeblock ** currentCodeBlockInTree, GIAentityNode * entity, int sentenceIndex, bool parseConditionParents, bool parseLogicalConditions);
	bool generateParentInitialisationCodeBlockWithChecks(NLCcodeblock ** currentCodeBlockInTree, GIAentityNode * parentEntity, int sentenceIndex, bool parseLogicalConditions);
		bool generateParentInitialisationCodeBlock(NLCcodeblock ** currentCodeBlockInTree, GIAentityNode * parentEntity, int sentenceIndex);

GIAentityNode * getParent(GIAentityNode * currentEntity, int sentenceIndex, bool parseConditionParents);
bool getParentAndGenerateContextBlocks(NLCcodeblock ** currentCodeBlockInTree, GIAentityNode * currentEntity, int sentenceIndex, NLCgenerateContextBlocksVariables * generateContextBlocksVariables, bool parseConditionParents);
	
bool generateObjectInitialisationsBasedOnPropertiesAndConditions(GIAentityNode * entity, NLCcodeblock ** currentCodeBlockInTree, int sentenceIndex, string parentName, string parentConditionName, bool generateParentContextTopLevel, bool generateParentContextPassThrough);
	void generateObjectInitialisationsBasedOnPropertiesAndConditionsUpdateCodeBlockPointer(NLCcodeblock ** currentCodeBlockInTree, NLCcodeblock * firstCodeBlockBeforeRecursion, NLCcodeblock * firstCodeBlockInSection, bool performedAtLeastOneObjectInitialisationAtThisLevel, bool performedAtLeastOneObjectInitialisationAtALowerLevel, bool * performedAtLeastOneObjectInitialisation);
	bool generateContextForChildEntity(GIAentityNode * entity, GIAentityNode * childEntity, NLCcodeblock ** currentCodeBlockInTree, int sentenceIndex, bool topLevel);
		#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_FOR_EACH_CHILD_GET_PARENT
		GIAentityNode * getSameReferenceSetDefiniteUniqueParent(GIAentityNode * currentEntity, int sentenceIndex, GIAentityNode * generateObjectInitialisationsLastParent, bool * foundParentEntityNew);
		#endif

#ifdef GIA_TRANSLATOR_DREAM_MODE_LINK_SPECIFIC_CONCEPTS_AND_ACTIONS
void generateObjectInitialisationsBasedOnSubstanceConcepts(GIAentityNode * entity, NLCcodeblock ** currentCodeBlockInTree, int sentenceIndex, bool newlyDeclaredEntityInCategoryList);
	void generateObjectInitialisationsBasedOnSubstanceConceptsRecurse(GIAentityNode * entity, GIAentityNode * definitionEntity, NLCcodeblock ** currentCodeBlockInTree, int sentenceIndex, string parentName, string parentConditionName, bool newlyDeclaredEntityInCategoryList);
#endif

#ifdef NLC_USE_ADVANCED_REFERENCING_SUPPORT_ALIASES
void fillFunctionAliasClassList(NLCcodeblock ** currentCodeBlockInTree, vector<GIAentityNode*> * entityNodesActiveListComplete);
void identifyAliasesInCurrentSentence(NLCcodeblock ** currentCodeBlockInTree, vector<GIAentityNode*> * entityNodesActiveListComplete, int sentenceIndex);
#endif

bool checkSpecialCaseEntity(GIAentityNode * entity, bool detectActions);

#ifdef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES
bool generateContextBasedOnDeclaredParent(GIAentityNode * entity, NLCcodeblock ** currentCodeBlockInTree, bool topLevel, GIAentityNode * generateObjectInitialisationsLastParent);
#endif

bool getActionSubjectEntityConnection(GIAentityNode * actionEntity, int sentenceIndex, GIAentityConnection ** actionSubjectConnection);
bool getActionObjectEntityConnection(GIAentityNode * actionEntity, int sentenceIndex, GIAentityConnection ** actionObjectConnection);

#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_FOR_EACH_CHILD_GET_PARENT_ORIGINAL_IMPLEMENTATION		
void addIntermediaryImplicitlyDeclaredEntityToLocalList(NLCcodeblock ** currentCodeBlockInTree, GIAentityNode * childEntity);
#endif

#endif
