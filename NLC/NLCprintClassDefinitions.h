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
 * File Name: NLCprintClassDefinitions.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2016 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 1s1a 03-September-2016
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/


#ifndef HEADER_NLC_PRINT_CLASSDEFINITIONS
#define HEADER_NLC_PRINT_CLASSDEFINITIONS

#include "NLCclassDefinitionClass.h"

bool printClassDefinitions(vector<NLCclassDefinition*>* classDefinitionList, int progLang, string* code, bool generatingAPIclassList);
	void generateFunctionDeclarationArgumentsWithActionConceptInheritanceString(vector<NLCitem*>* parameters, string* functionArguments, int progLang);
		#ifdef NLC_USE_LIBRARY_GENERATE_INDIVIDUAL_FILES
		string generateCodeHeaderCheckOpen(string headerCheckOpenDefinition);
		string generateCodeHeaderCheckClose();
		string generateCodeHashIncludeReferenceGenerated(string className, int progLang);
			string generateCodeClassDefinitionHeaderFileName(string className);
			string generateCodeClassDefinitionSourceFileName(string className);
		string generateCodeHashIncludeReferenceLibrary(string libraryFileNameWithoutFolderOrExtension, int progLang);
		string generateCodeHashIncludeReference(string referenceFolder, string includeFileNameWithoutFolder, int progLang);
			string generateCodeHashIncludeReference(string includeFileName, int progLang);
		string generateForwardDeclaration(string className, int progLang);
		void addToForwardDeclarationList(vector<string>* printedClassDefinitionTextHeaderTopForwardDeclarationList, string className);
		#endif
		bool printClassHeirarchyValidDefinitionClassChecks(NLCclassDefinition* classDefinition);
		string generateCodeSingularDefinitionText(NLCitem* currentItem, int progLang);
		string generateCodePluralDefinitionText(NLCitem* currentItem, int progLang);
		#ifdef NLC_INTERPRET_ACTION_PROPERTIES_AND_CONDITIONS_AS_FUNCTION_ARGUMENTS
		string generateCodeConditionPairDefinitionText(NLCitem* currentItem, int progLang);
		#endif
	bool arefunctionArgumentsPrinted(vector<NLCclassDefinition*>* classDefinitionList, vector<NLCitem*>* parameters);
	bool isConditionObjectPrinted(vector<NLCclassDefinition*>* classDefinitionList, vector<NLCitem*>* parameters);
	void generateCodeGenerateObjectByNameNewFunction(vector<NLCclassDefinition*>* classDefinitionList, int progLang, string* code, int level);
		string generateCodeGenerateObjectByNameDeclareFunction(int progLang);
	void generateCodeCopyObjectByNameNewFunction(vector<NLCclassDefinition*>* classDefinitionList, int progLang, string* code, int level);
		string generateCodeCopyObjectByNameDeclareFunction(int progLang);

#endif
