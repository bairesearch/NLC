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
 * File Name: NLCapi.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2016 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 1t2i 15-September-2016
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/


#ifndef HEADER_NLC_API
#define HEADER_NLC_API

#include "NLCglobalDefs.h"
#include "NLCclassDefinitionClass.h"
#include "XMLparserClass.h"

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

bool parseDoxygenClassXMLfile(string APIclassName, string APIsourceFolder, vector<NLCclassDefinition*>* classDefinitionList, int progLang);
	void generatePropertyClassLists(XMLparserTag* currentTagUpdated, vector<NLCclassDefinition*>* classDefinitionList, NLCclassDefinition* classDefinition, string APIclassName, string* APIwrapperSourceWrapObjectFunctionText, string* APIwrapperSourceUnwrapObjectFunctionText, int progLang);
	void generateFunctionClassLists(XMLparserTag* currentTagUpdated, vector<NLCclassDefinition*>* classDefinitionList, NLCclassDefinition* classDefinition, string APIclassName, string* APIwrapperSourceWrapFunctionFunctionsText, string* APIwrapperHeaderWrapFunctionFunctionsText, int progLang);
		string getType(XMLparserTag* typeTag);
		void detectVariableTypeDetails(vector<NLCclassDefinition*>* classDefinitionList, NLCclassDefinition* classDefinition, string variableName, string variableType, string* variableType1, string* variableType1ClassName, string* variableType2, bool* variableTypeList, bool* variableTypeStandard, int* mathtextVariableType);
		void generateCodeWrapObject(string variableName, string variableType1ClassName, string APIclassName, bool variableTypeList, bool variableTypeStandard, int mathtextVariableType, int level, string* APIwrapperSourceWrapObjectFunctionText, int progLang);
		void generateCodeUnwrapObject(string variableName, string variableType1ClassName, string variableType1, bool variableTypeList, bool variableTypeStandard, int mathtextVariableType, int level, string* APIwrapperSourceUnwrapObjectFunctionText, int progLang, bool useLocalList);
		string generateInstanceNameArbitrary(string classNameRaw);
		bool variableTypeIsStandard(string variableType, int* type);
		bool variableTypeIsList(string variableType, string* variableTypeEmbedded);

	string generateAPIwrapperSourceWrapOrUnwrapObjectFunctionHeaderText(string functionNamePrepend, string classNameRaw, int progLang);
	string generateAPIwrapperSourceWrapFunctionFunctionHeaderText(string functionNamePrepend, string classNameRaw, string argumentsDefinitionText, int progLang);
	string generateAPIwrapperSourceWrapperFunctionName(string functionNamePrepend, string classNameRaw);
	string generateAPIwrapperSourceWrapperFunctionArgumentDefinitionText(string classNameRaw, int progLang);
	string generateFunctionHeader(string functionName, string argumentText, int progLang);
	
#endif

#endif
