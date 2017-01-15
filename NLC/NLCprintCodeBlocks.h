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
 * File Name: NLCprintCodeBlocks.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2015 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 1q3b 18-August-2015
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/


#ifndef HEADER_NLC_PRINT_CODEBLOCKS
#define HEADER_NLC_PRINT_CODEBLOCKS

#include "NLCcodeBlockClass.h"
#include "NLCclassDefinitionClass.h"

bool printCodeBlocks(NLCcodeblock* firstCodeBlockInLevel, vector<NLCclassDefinition*>* classDefinitionList, int progLang, string* code, int level);	//classDefinitionList is required by NLC_SUPPORT_INPUT_FUNCTION_LISTS only
	void generateFunctionExecutionArgumentsWithActionConceptInheritanceString(vector<NLCclassDefinition*>* classDefinitionList, vector<NLCitem*>* codeBlockParameters, string* functionArguments, int progLang, string* functionDeclarationOwnerName, string* functionDeclarationObjectName);
		string generateCodePluralReferenceText(NLCitem* functionArgumentItem, int progLang, bool categoryList, string categoryVarAppendName);
		string generateCodeSingularReferenceText(NLCitem* functionArgumentItem, int progLang);
			#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS
			string printCodeBlockCastVectorExecuteFunction(NLCitem* functionArgumentItem, int progLang, string codeFunctionArgumentName);
			#endif
		#ifdef NLC_INTERPRET_ACTION_PROPERTIES_AND_CONDITIONS_AS_FUNCTION_ARGUMENTS
		string generateCodeConditionPairReferenceText(NLCitem* functionArgumentConditionItem, int progLang);
		#endif
	#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS
	void generateLocalFunctionArgumentsBasedOnImplicitDeclarationsString(vector<NLCitem*>* parameters, string* functionArguments, int progLang);
	#endif
	#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS
	void generateFunctionArgumentsBasedOnActionAndActionObjectVars(vector<NLCitem*>* parameters, string* functionArguments, int progLang, string* functionDeclarationOwnerName, string* functionDeclarationObjectName);
	#endif
	string generateFunctionOwnerContext(vector<NLCitem*>* parameters, int progLang, string* functionOwnerName);
#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS_ADVANCED
string generateLogicalConjunctionOfBoolsText(vector<NLCitem*>* parameters, int progLang);
#endif

#endif
