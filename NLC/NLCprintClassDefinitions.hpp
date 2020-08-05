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
 * File Name: NLCprintClassDefinitions.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2019 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler
 * Project Version: 2k1a 02-June-2020
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 * /
 *******************************************************************************/


#ifndef HEADER_NLC_PRINT_CLASSDEFINITIONS
#define HEADER_NLC_PRINT_CLASSDEFINITIONS

#include "NLCclassDefinitionClass.hpp"
#include "NLCpreprocessorSentenceClass.hpp"	//required for NLC_CLASS_DEFINITIONS_PRINT_UNDEFINED_BUT_REFERENCED_FUNCTIONS
#include "NLCprintDefs.hpp"

class NLCprintClassDefinitionsClass
{
	private: NLCclassDefinitionClassClass NLCclassDefinitionClass;
	private: NLCitemClassClass NLCitemClass;
	private: SHAREDvarsClass SHAREDvars;
	private: NLCprintDefsClass NLCprintDefs;
	public: bool printClassDefinitions(vector<NLCclassDefinition*>* classDefinitionList, int progLang, string* code, const bool generatingAPIclassList, NLCfunction* firstNLCfunctionInList);
		private: void generateFunctionDeclarationArgumentsWithActionNetworkIndexInheritanceString(vector<NLCitem*>* parameters, string* functionArguments, int progLang);
			#ifdef NLC_LIBRARY_GENERATE_INDIVIDUAL_FILES
			private: string generateCodeHeaderCheckOpen(const string headerCheckOpenDefinition);
			private: string generateCodeHeaderCheckClose();
			private: string generateCodeHashIncludeReferenceGenerated(const string className, const int progLang);
				public: string generateCodeClassDefinitionHeaderFileName(const string className);
				public: string generateCodeClassDefinitionSourceFileName(const string className);
			private: string generateCodeHashIncludeReferenceLibrary(const string libraryFileNameWithoutFolderOrExtension, const int progLang);
			public: string generateCodeHashIncludeReference(const string referenceFolder, const string includeFileNameWithoutFolder, const int progLang);
				public: string generateCodeHashIncludeReference(const string includeFileName, const int progLang);
			private: string generateForwardDeclaration(const string className, const int progLang);
			private: void addToForwardDeclarationList(vector<string>* printedClassDefinitionTextHeaderTopForwardDeclarationList, string className);
			#endif
			private: bool printClassHeirarchyValidDefinitionClassChecks(const NLCclassDefinition* classDefinition);
			private: string generateCodeSingularDefinitionText(NLCitem* currentItem, const int progLang);
			private: string generateCodePluralDefinitionText(NLCitem* currentItem, const int progLang);
			#ifdef NLC_INTERPRET_ACTION_PROPERTIES_AND_CONDITIONS_AS_FUNCTION_ARGUMENTS
			private: string generateCodeConditionPairDefinitionText(const NLCitem* currentItem, const int progLang);
			#endif
		private: bool arefunctionArgumentsPrinted(vector<NLCclassDefinition*>* classDefinitionList, vector<NLCitem*>* parameters);
		private: bool isConditionObjectPrinted(vector<NLCclassDefinition*>* classDefinitionList, vector<NLCitem*>* parameters);
		private: void generateCodeGenerateObjectByNameNewFunction(vector<NLCclassDefinition*>* classDefinitionList, const int progLang, string* code, int level);
			private: string generateCodeGenerateObjectByNameDeclareFunction(const int progLang);
		private: void generateCodeCopyObjectByNameNewFunction(vector<NLCclassDefinition*>* classDefinitionList, const int progLang, string* code, int level);
			private: string generateCodeCopyObjectByNameDeclareFunction(const int progLang);
};

#endif
