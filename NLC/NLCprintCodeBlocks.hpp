 /*******************************************************************************
 *
 * License: GNU Affero General Public License version 3 (AGPLv3)
 *
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: NLCprintCodeBlocks.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2022 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler
 * Project Version: 2p1a 05-June-2022
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 * /
 *******************************************************************************/


#ifndef HEADER_NLC_PRINT_CODEBLOCKS
#define HEADER_NLC_PRINT_CODEBLOCKS

#include "NLCcodeBlockClass.hpp"
#include "NLCclassDefinitionClass.hpp"
#include "NLCprintCodeBlocksFunctions.hpp"
#include "NLCprintDefs.hpp"

class NLCprintCodeBlocksClass
{
	private: NLCitemClassClass NLCitemClass;
	private: NLCclassDefinitionClassClass NLCclassDefinitionClass;
	private: SHAREDvarsClass SHAREDvars;
	private: NLCprintDefsClass NLCprintDefs;
	private: NLCprintCodeBlocksFunctionsClass NLCprintCodeBlocksFunctions;
	public: bool printCodeBlocks(NLCcodeblock* firstCodeBlockInLevel, vector<NLCclassDefinition*>* classDefinitionList, int progLang, string* code, const int level);	//classDefinitionList is required by NLC_INPUT_FUNCTION_LISTS only
		private: void generateFunctionExecutionArgumentsWithActionNetworkIndexInheritanceString(vector<NLCclassDefinition*>* classDefinitionList, vector<NLCitem*>* codeBlockParameters, string* functionArguments, int progLang, string* functionDeclarationOwnerName, string* functionDeclarationObjectName);
			private: string generateCodePluralReferenceText(const NLCitem* functionArgumentItem, const int progLang, const bool categoryList, const string categoryVarAppendName);
			private: string generateCodeSingularReferenceText(const NLCitem* functionArgumentItem, const int progLang);
				#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS
				private: string printCodeBlockCastVectorExecuteFunction(const NLCitem* functionArgumentItem, const int progLang, const string codeFunctionArgumentName);
				#endif
			#ifdef NLC_INTERPRET_ACTION_PROPERTIES_AND_CONDITIONS_AS_FUNCTION_ARGUMENTS
			private: string generateCodeConditionPairReferenceText(NLCitem* functionArgumentConditionItem, const int progLang);
			#endif
		#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS
		private: void generateLocalFunctionArgumentsBasedOnImplicitDeclarationsString(vector<NLCitem*>* parameters, string* functionArguments, int progLang);
		#endif
		#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS
		private: void generateFunctionArgumentsBasedOnActionAndActionObjectVars(vector<NLCitem*>* parameters, string* functionArguments, int progLang, string* functionDeclarationOwnerName, string* functionDeclarationObjectName);
		#endif
		private: string generateFunctionOwnerContext(vector<NLCitem*>* parameters, const int progLang, string* functionOwnerName);
	#ifdef NLC_PREDEFINED_FUNCTION_NAME_FOR_NATURAL_LANGUAGE_CODE_WITHOUT_FUNCTION_SPECIFIED_EXECUTE_IN_MAIN
	private: string generateMainFunctionText(vector<NLCitem*>* parameters, const int progLang);
	#endif
};


#endif
