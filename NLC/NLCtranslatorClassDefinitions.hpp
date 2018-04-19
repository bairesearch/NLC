/*******************************************************************************
 *
 * No License
 * 
 * This work is under exclusive copyright (c) Baxter AI (baxterai.com). 
 * Nobody else can use, copy, distribute, or modify this work without being 
 * at risk of take-downs, shake-downs, or litigation. 
 * 
 * By publishing this source code in a public repository on GitHub, Terms of 
 * Service have been accepted by which Baxter AI have allowed others to view 
 * and fork their repository.
 * 
 * If you find software that doesn't have a license, that generally means you 
 * have no permission from the creators of the software to use, modify, or 
 * share the software. Although a code host such as GitHub may allow you to 
 * view and fork the code, this does not imply that you are permitted to use, 
 * modify, or share the software for any purpose.
 *
 * This notice has been derived from https://choosealicense.com/no-permission 
 * (https://web.archive.org/web/20180312144938/https://choosealicense.com/no-permission)
 *
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: NLCtranslatorClassDefinitions.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2018 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler
 * Project Version: 2f8a 18-April-2018
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 * /
 *******************************************************************************/


#ifndef HEADER_NLC_TRANSLATOR_CLASSDEFINITIONS
#define HEADER_NLC_TRANSLATOR_CLASSDEFINITIONS

#include "GIAentityNodeClass.hpp"
#include "GIAentityConnectionClass.hpp"
#include "NLCcodeBlockClass.hpp"
#include "NLCclassDefinitionClass.hpp"
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
	private: void generateFunctionPropertyConditionArgumentsWithActionNetworkIndexInheritance(GIAentityNode* actionRelationshipEntity, vector<NLCitem*>* parameters);
	private: void generateFunctionPropertyConditionArguments(GIAentityNode* actionRelationshipEntity, vector<NLCitem*>* parameters, const bool performChildActionDuplicateCheck);
		public: bool checkDuplicateProperty(const GIAentityNode* propertyRelationshipObjectEntity, vector<NLCitem*>* parameters);
		public: bool checkDuplicateCondition(GIAentityNode* conditionRelationshipEntity, vector<NLCitem*>* parameters);
	#endif
};


#endif
