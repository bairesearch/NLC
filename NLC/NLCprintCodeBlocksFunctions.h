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
 * File Name: NLCprintCodeBlocksFunctions.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2016 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 1s8b 09-September-2016
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/


#ifndef HEADER_NLC_PRINT_CODEBLOCKS_FUNCTIONS
#define HEADER_NLC_PRINT_CODEBLOCKS_FUNCTIONS

#include "NLCglobalDefs.h"
#include "NLCitemClass.h"

#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN
#ifdef NLC_USE_ADVANCED_REFERENCING
void generateCodeAddToCategoryIfPassSingularDefiniteReferencingTestsNewFunction(int progLang, string* code, int level);
void generateCodeAddToCategoryIfPassSingularDefiniteReferencingTestsExecuteFunction(NLCitem* param1, NLCitem* param2, NLCitem* param3, int progLang, string* code, int level, bool castToCategoryType);
#endif
#endif
#ifdef NLC_PERFORM_PLURAL_DEFINITE_REFERENCING_TESTS
void generateCodeAddToCategoryIfPassPluralDefiniteReferencingTestsNewFunction(int progLang, string* code, int level);
void generateCodeAddToCategoryIfPassPluralDefiniteReferencingTestsExecuteFunction(NLCitem* param1, NLCitem* param2, NLCitem* param3, int progLang, string* code, int level, bool castToCategoryType);
#endif
#ifdef NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT
void generateCodeAddEntityToReferenceContextListNewFunction(int progLang, string* code, int level);
void generateCodeAddEntityToReferenceContextListExecuteFunction(NLCitem* param1, NLCitem* param2, NLCitem* param3, int progLang, string* code, int level);
void generateCodeClearReferenceContextListNewFunction(int progLang, string* code, int level);
void generateCodeClearReferenceContextListExecuteFunction(NLCitem* param1, int progLang, string* code, int level);
#endif
#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS
void generateCodeCastVectorNewFunction(int progLang, string* code, int level);
void generateCodeCastVectorExecuteFunction(NLCitem* param1, NLCitem* param2, int progLang, string* code, int level);
#endif
#ifdef NLC_USE_ADVANCED_REFERENCING_SUPPORT_ALIASES
void generateCodeFindAliasAndAddToCategoryListNewFunction(int progLang, string* code, int level);
void generateCodeFindAliasAndAddToCategoryListExecuteFunction(NLCitem* param1, NLCitem* param2, NLCitem* param3, int progLang, string* code, int level);
void generateCodeFindAliasNewFunction(int progLang, string* code, int level);
void generateCodeFindAliasExecuteFunction(NLCitem* param1, NLCitem* param2, int progLang, string* code, int level);
#endif
#ifdef NLC_SUPPORT_REDEFINITIONS
void generateCodeCheckParentClassNameNewFunction(int progLang, string* code, int level);
void generateCodeCheckParentClassNameExecuteFunction1(NLCitem* param1, NLCitem* param2, int progLang, string* code, int level);
void generateCodeCheckParentClassNameExecuteFunction2(NLCitem* param1, NLCitem* param2, int progLang, string* code, int level);
#endif

void generateCodeAddProperty(NLCitem* param1, NLCitem* param2, int progLang, string* code, int level);
	void generateCodeAddPropertyEntityToList(NLCitem* param1, NLCitem* param2, int progLang, string* code, int level);
		void generateCodeAddEntityToList(string entityName, string listName, int progLang, string* code, int level);
#ifdef NLC_USE_LIBRARY_BASE_EXTENDED
void generateCodeAddPropertyExecuteFunction(NLCitem* param1, NLCitem* param2, int progLang, string* code, int level);
void generateCodeAddPropertyNewFunction(int progLang, string* code, int level);
#endif

void generateCodeRemoveProperty(NLCitem* param1, NLCitem* param2, int progLang, string* code, int level);
void generateCodeRemoveProperties(NLCitem* param1, NLCitem* param2, int progLang, string* code, int level);
#ifdef NLC_USE_LIBRARY_BASE_EXTENDED
void generateCodeRemovePropertyExecuteFunction(NLCitem* param1, NLCitem* param2, int progLang, string* code, int level);
void generateCodeRemovePropertiesExecuteFunction(NLCitem* param1, NLCitem* param2, int progLang, string* code, int level);
#endif

void generateCodeAddCondition(NLCitem* param1, NLCitem* param2, NLCitem* param3, int progLang, string* code, int level, bool inverseCondition);
void generateCodeAddConditionAndObjectEntityToList(NLCitem* param1, NLCitem* param2, NLCitem* param3, int progLang, string* code, int level, bool inverseCondition);
#ifdef NLC_USE_LIBRARY_BASE_EXTENDED
void generateCodeAddConditionExecuteFunction(NLCitem* param1, NLCitem* param2, NLCitem* param3, int progLang, string* code, int level, bool inverseCondition);
void generateCodeAddConditionNewFunction(int progLang, string* code, int level, bool inverseCondition);
#endif

void generateCodeRemoveCondition(NLCitem* param1, NLCitem* param2, NLCitem* param3, int progLang, string* code, int level);
void generateCodeRemoveConditions(NLCitem* param1, NLCitem* param2, NLCitem* param3, int progLang, string* code, int level);
#ifdef NLC_USE_LIBRARY_BASE_EXTENDED
void generateCodeRemoveConditionExecuteFunction(NLCitem* param1, NLCitem* param2, NLCitem* param3, int progLang, string* code, int level);
void generateCodeRemoveConditionsExecuteFunction(NLCitem* param1, NLCitem* param2, NLCitem* param3, int progLang, string* code, int level);
#endif
	
void generateCodeAddActionSubject(NLCitem* functionArgument, NLCitem* functionOwnerArgument, int progLang, string* code, int level);
#ifdef NLC_USE_LIBRARY_BASE_EXTENDED
void generateCodeAddActionSubjectExecuteFunction(NLCitem* functionArgument, NLCitem* functionOwnerArgument, int progLang, string* code, int level);
#endif
void generateCodeAddActionObject(NLCitem* functionArgument, NLCitem* functionObjectArgument, int progLang, string* code, int level);
#ifdef NLC_USE_LIBRARY_BASE_EXTENDED
void generateCodeAddActionObjectExecuteFunction(NLCitem* functionArgument, NLCitem* functionObjectArgument, int progLang, string* code, int level);
#endif

void generateCodeAddNewEntityToLocalList(NLCitem* param1, int progLang, string* code, int level);
#ifdef NLC_USE_LIBRARY_BASE_EXTENDED
void generateCodeAddNewEntityToLocalListExecuteFunction(NLCitem* param1, int progLang, string* code, int level);
#endif
void generateCodeAddEntityToLocalList(NLCitem* param1, NLCitem* param2, int progLang, string* code, int level);
#ifdef NLC_USE_LIBRARY_BASE_EXTENDED
void generateCodeAddEntityToLocalListExecuteFunction(NLCitem* param1, NLCitem* param2, int progLang, string* code, int level);
#endif

void generateCodeForPropertyList(NLCitem* param1, string contextParam1, int progLang, string* code, int level);
void generateCodeForLocalList(NLCitem* param1, int progLang, string* code, int level);
	void generateCodeForEntityList(string entityClassName, string entityListName, string entityInstanceName, int progLang, string* code, int level);
void generateCodeForConditionList(NLCitem* param1, NLCitem* param2, string contextParam1, int progLang, string* code, int level);
	void generateCodeForConditionList(string entityClassName1, string entityClassName2, string entityListName, string entityInstanceName1, string entityInstanceName2, int progLang, string* code, int level);

#endif
