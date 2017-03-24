/*******************************************************************************
 *
 * This file is part of BAIPROJECT.
 *
 * BAIPROJECT is licensed under the GNU Affero General Public License
 * version 3, as published by the Free Software Foundation. The use of
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
 * File Name: NLCapi.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2017 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 2a1b 26-February-2017
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
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
