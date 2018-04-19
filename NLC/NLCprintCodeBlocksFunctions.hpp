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
 * File Name: NLCprintCodeBlocksFunctions.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2018 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler
 * Project Version: 2f9a 18-April-2018
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 * /
 *******************************************************************************/


#ifndef HEADER_NLC_PRINT_CODEBLOCKS_FUNCTIONS
#define HEADER_NLC_PRINT_CODEBLOCKS_FUNCTIONS

#include "NLCglobalDefs.hpp"
#include "NLCitemClass.hpp"
#include "NLCprintDefs.hpp"


class NLCprintCodeBlocksFunctionsClass
{
	private: SHAREDvarsClass SHAREDvars;
	private: NLCprintDefsClass NLCprintDefs;
	private: NLCitemClassClass NLCitemClass;
	#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN
	#ifdef NLC_ADVANCED_REFERENCING
	public: void generateCodeAddToCategoryIfPassSingularDefiniteReferencingTestsNewFunction(const int progLang, string* code, const int level);
	public: void generateCodeAddToCategoryIfPassSingularDefiniteReferencingTestsExecuteFunction(const NLCitem* param1, const NLCitem* param2, const NLCitem* param3, const int progLang, string* code, const int level, const bool castToCategoryType);
	#endif
	#endif
	#ifdef NLC_PERFORM_PLURAL_DEFINITE_REFERENCING_TESTS
	public: void generateCodeAddToCategoryIfPassPluralDefiniteReferencingTestsNewFunction(const int progLang, string* code, const int level);
	public: void generateCodeAddToCategoryIfPassPluralDefiniteReferencingTestsExecuteFunction(const NLCitem* param1, const NLCitem* param2, const NLCitem* param3, const int progLang, string* code, const int level, const bool castToCategoryType);
	#endif
	#ifdef NLC_ADVANCED_REFERENCING_MONITOR_CONTEXT
	public: void generateCodeAddEntityToReferenceContextListNewFunction(const int progLang, string* code, const int level);
	public: void generateCodeAddEntityToReferenceContextListExecuteFunction(const NLCitem* param1, const NLCitem* param2, const NLCitem* param3, const int progLang, string* code, const int level);
	public: void generateCodeClearReferenceContextListNewFunction(const int progLang, string* code, const int level);
	public: void generateCodeClearReferenceContextListExecuteFunction(const NLCitem* param1, const int progLang, string* code, const int level);
	#endif
	#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS
	public: void generateCodeCastVectorNewFunction(const int progLang, string* code, const int level);
	public: void generateCodeCastVectorExecuteFunction(const NLCitem* param1, const NLCitem* param2, const int progLang, string* code, const int level);
	#endif
	#ifdef NLC_ADVANCED_REFERENCING_SUPPORT_ALIASES
	public: void generateCodeFindAliasAndAddToCategoryListNewFunction(const int progLang, string* code, const int level);
	public: void generateCodeFindAliasAndAddToCategoryListExecuteFunction(const NLCitem* param1, const NLCitem* param2, const NLCitem* param3, const int progLang, string* code, const int level);
	public: void generateCodeFindAliasNewFunction(const int progLang, string* code, const int level);
	public: void generateCodeFindAliasExecuteFunction(const NLCitem* param1, const NLCitem* param2, const int progLang, string* code, const int level);
	#endif
	#ifdef NLC_REDEFINITIONS
	public: void generateCodeCheckParentClassNameNewFunction(const int progLang, string* code, const int level);
	public: void generateCodeCheckParentClassNameExecuteFunction1(const NLCitem* param1, const NLCitem* param2, const int progLang, string* code, const int level);
	public: void generateCodeCheckParentClassNameExecuteFunction2(const NLCitem* param1, const NLCitem* param2, const int progLang, string* code, const int level);
	#endif

	public: void generateCodeAddProperty(NLCitem* param1, const NLCitem* param2, const int progLang, string* code, const int level);
		private: void generateCodeAddPropertyEntityToList(NLCitem* param1, const NLCitem* param2, const int progLang, string* code, const int level);
			public: void generateCodeAddEntityToList(const string entityName, const string listName, const int progLang, string* code, const int level);
	#ifdef NLC_LIBRARY_BASE_EXTENDED
	private: void generateCodeAddPropertyExecuteFunction(NLCitem* param1, const NLCitem* param2, const int progLang, string* code, const int level);
	public: void generateCodeAddPropertyNewFunction(const int progLang, string* code, const int level);
	#endif

	public: void generateCodeRemoveProperty(NLCitem* param1, const NLCitem* param2, const int progLang, string* code, const int level);
	public: void generateCodeRemoveProperties(NLCitem* param1, const NLCitem* param2, const int progLang, string* code, const int level);
	#ifdef NLC_LIBRARY_BASE_EXTENDED
	private: void generateCodeRemovePropertyExecuteFunction(NLCitem* param1, const NLCitem* param2, const int progLang, string* code, const int level);
	private: void generateCodeRemovePropertiesExecuteFunction(NLCitem* param1, const NLCitem* param2, const int progLang, string* code, const int level);
	#endif

	public: void generateCodeAddCondition(NLCitem* param1, const NLCitem* param2, const NLCitem* param3, const int progLang, string* code, const int level, const bool inverseCondition);
	private: void generateCodeAddConditionAndObjectEntityToList(NLCitem* param1, const NLCitem* param2, const NLCitem* param3, const int progLang, string* code, const int level, const bool inverseCondition);
	#ifdef NLC_LIBRARY_BASE_EXTENDED
	private: void generateCodeAddConditionExecuteFunction(NLCitem* param1, const NLCitem* param2, const NLCitem* param3, const int progLang, string* code, const int level, const bool inverseCondition);
	public: void generateCodeAddConditionNewFunction(const int progLang, string* code, const int level, const bool inverseCondition);
	#endif

	public: void generateCodeRemoveCondition(NLCitem* param1, const NLCitem* param2, const NLCitem* param3, const int progLang, string* code, const int level);
	public: void generateCodeRemoveConditions(NLCitem* param1, const NLCitem* param2, const NLCitem* param3, const int progLang, string* code, const int level);
	#ifdef NLC_LIBRARY_BASE_EXTENDED
	private: void generateCodeRemoveConditionExecuteFunction(NLCitem* param1, const NLCitem* param2, const NLCitem* param3, const int progLang, string* code, const int level);
	private: void generateCodeRemoveConditionsExecuteFunction(NLCitem* param1, const NLCitem* param2, const NLCitem* param3, const int progLang, string* code, const int level);
	#endif

	public: void generateCodeAddActionSubject(const NLCitem* functionArgument, const NLCitem* functionOwnerArgument, const int progLang, string* code, const int level);
	#ifdef NLC_LIBRARY_BASE_EXTENDED
	private: void generateCodeAddActionSubjectExecuteFunction(const NLCitem* functionArgument, const NLCitem* functionOwnerArgument, const int progLang, string* code, const int level);
	#endif
	public: void generateCodeAddActionObject(const NLCitem* functionArgument, const NLCitem* functionObjectArgument, const int progLang, string* code, const int level);
	#ifdef NLC_LIBRARY_BASE_EXTENDED
	private: void generateCodeAddActionObjectExecuteFunction(const NLCitem* functionArgument, const NLCitem* functionObjectArgument, const int progLang, string* code, const int level);
	#endif

	public: void generateCodeAddNewEntityToLocalList(const NLCitem* param1, const int progLang, string* code, const int level);
	#ifdef NLC_LIBRARY_BASE_EXTENDED
	private: void generateCodeAddNewEntityToLocalListExecuteFunction(const NLCitem* param1, const int progLang, string* code, const int level);
	#endif
	public: void generateCodeAddEntityToLocalList(const NLCitem* param1, const NLCitem* param2, const int progLang, string* code, const int level);
	#ifdef NLC_LIBRARY_BASE_EXTENDED
	private: void generateCodeAddEntityToLocalListExecuteFunction(const NLCitem* param1, const NLCitem* param2, const int progLang, string* code, const int level);
	#endif

	public: void generateCodeForPropertyList(const NLCitem* param1, const string contextParam1, const int progLang, string* code, const int level);
	public: void generateCodeForLocalList(const NLCitem* param1, const int progLang, string* code, const int level);
		public: void generateCodeForEntityList(const string entityClassName, const string entityListName, const string entityInstanceName, const int progLang, string* code, const int level);
	public: void generateCodeForConditionList(const NLCitem* param1, const NLCitem* param2, const string contextParam1, const int progLang, string* code, const int level);
		public: void generateCodeForConditionList(const string entityClassName1, const string entityClassName2, const string entityListName, const string entityInstanceName1, const string entityInstanceName2, const int progLang, string* code, const int level);

	#ifdef NLC_TRANSLATOR_TEST_DEFINITE_ENTITY_EXISTENCE_SUBJECT_OBJECT
	public: void generateCodeVerifyDefiniteReferenceExistenceNewFunction(const int progLang, string* code, const int level);
	public: void generateCodeVerifyDefiniteReferenceExistenceExecuteFunction(const NLCitem* param1, const NLCitem* param2, const int progLang, string* code, const int level);
	#endif
	
	#ifdef NLC_ADVANCED_REFERENCING_SUPPORT_ALIASES_MERGERS
	public: void findAndRemoveEntityFromLocalListExecuteFunction(const NLCitem* param1, const int progLang, string* code, const int level);
	public: void findAndReplaceEntityInLocalListExecuteFunction(const NLCitem* param1, const NLCitem* param2, const int progLang, string* code, const int level);
	public: void mergeEntity1AttributesIntoEntity2ExecuteFunction(const NLCitem* param1, const NLCitem* param2, const int progLang, string* code, const int level);
	#endif
};


#endif
