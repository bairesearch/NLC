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
 * File Name: NLCapi.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2018 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler
 * Project Version: 2f4a 14-April-2018
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 * /
 *******************************************************************************/


#ifndef HEADER_NLC_API
#define HEADER_NLC_API

#include "NLCglobalDefs.hpp"
#include "NLCclassDefinitionClass.hpp"
#include "XMLparserClass.hpp"
#include "NLCtranslatorClassDefinitions.hpp"
#include "NLCprintClassDefinitions.hpp"
#include "NLCprintDefs.hpp"
#include "NLCprintCodeBlocksFunctions.hpp"

#define NET_XML_TAG_doxygen "doxygen"
#define NET_XML_TAG_compounddef "compounddef"
#define NET_XML_TAG_compoundname "compoundname"
#define NET_XML_TAG_basecompoundref "basecompoundref"
#define NET_XML_TAG_includes "includes"
#define NET_XML_TAG_sectiondef "sectiondef"
#define NET_XML_ATTRIBUTE_kind "kind"
#define NET_XML_TAG_sectiondef_ATTRIBUTE_kind_VALUE_privateattrib "private-attrib"
#define NET_XML_TAG_sectiondef_ATTRIBUTE_kind_VALUE_publicattrib "public-attrib"
#define NET_XML_TAG_sectiondef_ATTRIBUTE_kind_VALUE_protectedattrib "protected-attrib"
#define NET_XML_TAG_sectiondef_ATTRIBUTE_kind_VALUE_privatefunc "private-func"
#define NET_XML_TAG_sectiondef_ATTRIBUTE_kind_VALUE_publicfunc "public-func"
#define NET_XML_TAG_sectiondef_ATTRIBUTE_kind_VALUE_protectedfunc "protected-func"
#define NET_XML_TAG_memberdef "memberdef"
#define NET_XML_TAG_name "name"
#define NET_XML_TAG_type "type"
#define NET_XML_TAG_param "param"
#define NET_XML_TAG_declname "declname"
#define NET_XML_TAG_ref "ref"
#define NET_XML_TAG_memberdef_ATTRIBUTE_kind_VALUE_variable "variable"
#define NET_XML_TAG_memberdef_ATTRIBUTE_kind_VALUE_function "function"

#ifdef NLC_API

class NLCapiClass
{
	private: NLCitemClassClass NLCitemClass;
	private: SHAREDvarsClass SHAREDvars;
	private: XMLparserClassClass XMLparserClass;
	private: NLCtranslatorClassDefinitionsClass NLCtranslatorClassDefinitions;
	private: NLCprintDefsClass NLCprintDefs;
	private: NLCprintClassDefinitionsClass NLCprintClassDefinitions;
	private: NLCprintCodeBlocksFunctionsClass NLCprintCodeBlocksFunctions;
	public: bool parseDoxygenClassXMLfile(const string APIclassName, const string APIsourceFolder, vector<NLCclassDefinition*>* classDefinitionList, int progLang);
		private: void generatePropertyClassLists(XMLparserTag* currentTagUpdated, vector<NLCclassDefinition*>* classDefinitionList, NLCclassDefinition* classDefinition, const string APIclassName, string* APIwrapperSourceWrapObjectFunctionText, string* APIwrapperSourceUnwrapObjectFunctionText, const int progLang);
		private: void generateFunctionClassLists(XMLparserTag* currentTagUpdated, vector<NLCclassDefinition*>* classDefinitionList, NLCclassDefinition* classDefinition, const string APIclassName, string* APIwrapperSourceWrapFunctionFunctionsText, string* APIwrapperHeaderWrapFunctionFunctionsText, int progLang);
			private: string getType(const XMLparserTag* typeTag);
			private: void detectVariableTypeDetails(vector<NLCclassDefinition*>* classDefinitionList, NLCclassDefinition* classDefinition, string variableName, string variableType, string* variableType1, string* variableType1ClassName, string* variableType2, const bool* variableTypeList, bool* variableTypeStandard, int* mathtextVariableType);
			private: void generateCodeWrapObject(const string variableName, const string variableType1ClassName, const string APIclassName, const bool variableTypeList, const bool variableTypeStandard, const int mathtextVariableType, const int level, string* APIwrapperSourceWrapObjectFunctionText, const int progLang);
			private: void generateCodeUnwrapObject(const string variableName, const string variableType1ClassName, const string variableType1, const bool variableTypeList, const bool variableTypeStandard, const int mathtextVariableType, const int level, string* APIwrapperSourceUnwrapObjectFunctionText, const int progLang, const bool useLocalList);
			private: string generateInstanceNameArbitrary(const string classNameRaw);
			private: bool variableTypeIsStandard(const string variableType, int* type);
			private: bool variableTypeIsList(string variableType, string* variableTypeEmbedded);

		private: string generateAPIwrapperSourceWrapOrUnwrapObjectFunctionHeaderText(string functionNamePrepend, const string classNameRaw, const int progLang);
		private: string generateAPIwrapperSourceWrapFunctionFunctionHeaderText(string functionNamePrepend, const string classNameRaw, const string argumentsDefinitionText, const int progLang);
		private: string generateAPIwrapperSourceWrapperFunctionName(string functionNamePrepend, const string classNameRaw);
		private: string generateAPIwrapperSourceWrapperFunctionArgumentDefinitionText(const string classNameRaw, const int progLang);
		private: string generateFunctionHeader(const string functionName, const string argumentText, const int progLang);
};

#endif

#endif
