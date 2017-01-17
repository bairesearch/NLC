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
 * File Name: NLCtranslatorClassDefinitions.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2017 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 1w4a 17-January-2017
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/


#ifndef HEADER_NLC_TRANSLATOR_CLASSDEFINITIONS
#define HEADER_NLC_TRANSLATOR_CLASSDEFINITIONS

#include "GIAentityNodeClass.hpp"
#include "GIAentityConnectionClass.hpp"
#include "NLCcodeBlockClass.hpp"
#include "NLCclassDefinitionClass.hpp"
#include "GIAtranslatorDefs.hpp"
#include "NLCtranslatorCodeBlocksOperations.hpp"	//required for getSameReferenceSetUniqueParent()
#include "GIAtranslatorOperations.hpp"	//required for getPrimaryNetworkIndexNodeDefiningInstance()

class NLCtranslatorClassDefinitionsClass
{
	private: NLCcodeBlockClassClass NLCcodeBlockClass;
	private: NLCitemClassClass NLCitemClass;
	private: NLCclassDefinitionClassClass NLCclassDefinitionClass;
	private: NLCtranslatorCodeBlocksOperationsClass NLCtranslatorCodeBlocksOperations;
	private: GIAtranslatorOperationsClass GIAtranslatorOperations;
	private: NLCpreprocessorSentenceClassClass NLCpreprocessorSentenceClass;
	private: SHAREDvarsClass SHAREDvars;
	public: bool generateClassHeirarchy(vector<NLCclassDefinition*>* classDefinitionList, vector<GIAentityNode*>* entityNodesActiveListComplete, const NLCfunction* currentNLCfunctionInList);
		public: bool addClassDefinitionToList(vector<NLCclassDefinition*>* classDefinitionList, const string className, NLCclassDefinition** classDefinition);
		public: void addDefinitionToClassDefinition(NLCclassDefinition* classDefinition, NLCclassDefinition* targetClassDefinition);
		public: void addPropertyListToClassDefinition(NLCclassDefinition* classDefinition, NLCclassDefinition* targetClassDefinition);
	#ifdef NLC_CLASS_DEFINITIONS_DO_NOT_DEFINE_INHERITANCE_FOR_REDEFINITIONS
		private: bool isSubstanceEntityDefinitionAChildOfTheSubstanceEntity(const GIAentityNode* substanceEntity, GIAentityNode* parentEntity, const GIAentityConnection* connection);
	#endif
	#ifdef NLC_CLASS_DEFINITIONS_DO_NOT_DEFINE_INHERITANCE_FOR_LOGICAL_CONDITION_CONCEPTS
		private: bool entityIsConceptAndInLogicalCondition(const GIAentityNode* entity, const NLCfunction* currentNLCfunctionInList);
	#endif
		private: bool generateClassHeirarchyCondition(NLCclassDefinition* classDefinition, NLCclassDefinition* targetClassDefinition, GIAentityNode* targetEntity);
#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE
	public: bool generateClassHeirarchyFunctions(vector<NLCclassDefinition*>* classDefinitionList, vector<GIAentityNode*>* entityNodesActiveListComplete, NLCclassDefinition* parentFunctionDependencyClassDefinition);
#endif
	#ifdef NLC_RECORD_ACTION_HISTORY
		private: void fillActionLists(vector<NLCclassDefinition*>* classDefinitionList, const bool hasActionSubject, const bool hasActionObject, const string actionName, const string actionObjectName, const string actionSubjectName);
	#endif
		private: bool generateClassHeirarchyValidClassChecks(GIAentityNode* entityNode);
		private: bool generateClassHeirarchyTargetValidClassChecks(GIAentityNode* targetEntity);
	#ifdef NLC_CREATE_A_SEPARATE_CLASS_FOR_CONCEPT_DEFINITIONS
		private: string generateConceptClassName(GIAentityNode* conceptEntity);
			private: void generateConceptClassNameRecurse(GIAentityNode* conceptEntity, string* conceptClassName);
	#endif
#ifdef NLC_PREVENT_INHERITANCE_DOUBLE_DECLARATIONS_OF_CLASS_LIST_VARIABLES
	public: void preventDoubleDeclarationsOfClassDefinitionVariablesInHeirachy(vector<NLCclassDefinition*>* classDefinitionList);
		private: void eraseDuplicateClassDefinitionSublistItemIfFoundInParentClassDefinitionSublist(NLCclassDefinition* classDefinition, vector<NLCclassDefinition*>* classDefinitionSublist, const int variableType);
			private: bool findVariableInParentClass(NLCclassDefinition* classDefinition, const string variableName, const int variableType);
#endif

#ifdef NLC_INTERPRET_ACTION_PROPERTIES_AND_CONDITIONS_AS_FUNCTION_ARGUMENTS
	private: void generateFunctionPropertyConditionArgumentsWithActionNetworkIndexInheritance(GIAentityNode* actionEntity, vector<NLCitem*>* parameters);
	private: void generateFunctionPropertyConditionArguments(GIAentityNode* actionEntity, vector<NLCitem*>* parameters, const bool performChildActionDuplicateCheck);
		public: bool checkDuplicateProperty(const GIAentityNode* propertyEntity, vector<NLCitem*>* parameters);
		public: bool checkDuplicateCondition(GIAentityNode* conditionEntity, vector<NLCitem*>* parameters);
#endif
};


#endif
