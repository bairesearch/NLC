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
 * File Name: NLCtranslatorCodeBlocks.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2016 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 1v3a 12-October-2016
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/


#ifndef HEADER_NLC_TRANSLATOR_CODEBLOCKS
#define HEADER_NLC_TRANSLATOR_CODEBLOCKS

#include "GIAentityNodeClass.h"
#include "GIAentityConnectionClass.h"
#include "NLCglobalDefs.h"
#include "NLCcodeBlockClass.h"
#include "NLCclassDefinitionClass.h"
//#ifdef NLC_USE_PREPROCESSOR
#include "NLCpreprocessorSentenceClass.h"
//#endif


bool generateCodeBlocks(NLCcodeblock* firstCodeBlockInTree, vector<GIAentityNode*>* entityNodesActiveListComplete, map<int, vector<GIAentityNode*>*>* entityNodesActiveListSentences, int maxNumberSentences, string NLCfunctionName, NLCfunction* currentNLCfunctionInList);
	NLCcodeblock* createCodeBlockNewFunction(NLCcodeblock* currentCodeBlockInTree, string NLCfunctionName, vector<GIAentityNode*>* entityNodesActiveListComplete, NLCfunction* currentNLCfunctionInList);
		#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS
		void generateLocalFunctionArgumentsBasedOnImplicitDeclarations(vector<GIAentityNode*>* entityNodesActiveListComplete, vector<NLCitem*>* parameters, NLCfunction* currentNLCfunctionInList);
			bool isDefiniteEntityInitialisation(GIAentityNode* entity, NLCfunction* currentNLCfunctionInList);
				bool generateLocalFunctionArgumentsBasedOnImplicitDeclarationsValidClassChecks(GIAentityNode* entityNode);
				bool getSentenceInFunction(GIAentityNode* entity, NLCfunction* currentNLCfunctionInList, NLCsentence** sentenceFound);
			#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS_SUPPORT_LOCAL_LISTS_USE_CLASS_NAMES
			bool findIndefiniteEntityCorrespondingToDefiniteEntityInSameContext(vector<GIAentityNode*>* entityNodesActiveListComplete, GIAentityNode* definiteEntity);
				bool isIndefiniteEntityCorrespondingToDefiniteEntityInSameContext(GIAentityNode* indefiniteEntity, GIAentityNode* definiteEntity);
			#endif
			#ifdef NLC_TRANSLATOR_INTERPRET_PROPERNOUNS_WITH_DEFINITION_LINK_AS_NEWLY_DECLARED
			bool findPropernounDefinitionLink(vector<GIAentityNode*>* entityNodesActiveListComplete, GIAentityNode* definiteEntity);
			#endif
		#endif
	bool declareLocalPropertyListsForIndefiniteEntities(NLCcodeblock** currentCodeBlockInTree, vector<GIAentityNode*>* entityNodesActiveListComplete, int sentenceIndex, string NLCfunctionName, NLCsentence* currentNLCsentenceInList);	//added 1g8a 11-July-2014
		bool declareLocalPropertyListsForIndefiniteEntitiesValidClassChecks(GIAentityNode* entityNode);
		bool declareLocalPropertyListsForIndefiniteEntity(NLCcodeblock** currentCodeBlockInTree, GIAentityNode* entity, NLCsentence* currentNLCsentenceInList);
	#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
	bool clearContextGeneratedVariable(vector<GIAentityNode*>* entityNodesActiveListComplete);
	#endif

	#ifdef NLC_GENERATE_OBJECT_INITIALISATIONS_BASED_ON_CONCEPTS_FOR_ALL_DEFINITE_ENTITIES
	bool generateObjectInitialisationsBasedOnConceptsForAllDefiniteEntities(NLCcodeblock** currentCodeBlockInTree, vector<GIAentityNode*>* entityNodesActiveListSentence, int sentenceIndex);
	#endif

#endif
