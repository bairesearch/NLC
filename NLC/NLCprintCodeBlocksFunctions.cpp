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
 * File Name: NLCprintCodeBlocksFunctions.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2017 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler
 * Project Version: 2c1a 01-June-2017
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/


#include "NLCprintCodeBlocksFunctions.hpp"

#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN
#ifdef NLC_ADVANCED_REFERENCING
void NLCprintCodeBlocksFunctionsClass::generateCodeAddToCategoryIfPassSingularDefiniteReferencingTestsNewFunction(const int progLang, string* code, const int level)
{
	string genericObjectName = "entity";
	NLCitem* param1 = new NLCitem(genericObjectName, NLC_ITEM_TYPE_OBJECT);
	NLCitem* param2 = new NLCitem(genericObjectName, NLC_ITEM_TYPE_OBJECT);
	//OLD: param2->instanceName = "entity0";
	string genericListAppendName = NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION;

	string negativeModifierString = progLangNot[progLang];

	#ifdef NLC_NONOO
	string templateName1 = NLCNONOO_GENERIC_ENTITY_NODE_NAME;
	string templateName2 = NLCNONOO_GENERIC_ENTITY_NODE_NAME;
	string codeBlockTextTemplateHeader = "";
	#else
	string templateName1 = "E1";
	string templateName2 = "E2";
	string codeBlockTextTemplateHeader = progLangTemplateHeaderPart1[progLang] + progLangTemplateHeaderClassType[progLang] + templateName1 + progLangTemplateUseClassSeparator[progLang] + progLangTemplateHeaderClassType[progLang] + templateName2 + progLangTemplateHeaderPart2[progLang];  //template <class E1, class E2>
	#endif

	string codeBlockTextFunctionHeader = progLangClassMemberFunctionTypeDefault[progLang] + NLC_ADVANCED_REFERENCING_SINGULAR_DEFINITE_REFERENCING_TESTS_FUNCTION_NAME + progLangOpenParameterSpace[progLang] + NLCprintDefs.generateCodeEntityListDefinitionTypeTextReference(templateName1, progLang) + NLCprintDefs.generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangClassMemberFunctionParametersNext[progLang] + NLCprintDefs.generateCodeEntityDefinitionText(templateName2, param2->instanceName, progLang) + progLangCloseParameterSpace[progLang];	//void addToCategoryIfPassSingularDefinitePluralityTests(vector<E1*>& param1CategoryList, E2* param2instanceName)

	string codeBlockText6 = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + negativeModifierString + progLangOpenParameterSpace[progLang] + param2->instanceName + progLangObjectReferenceDelimiter[progLang] + NLC_ADVANCED_REFERENCING_LAST_SENTENCE_REFERENCED_VARIABLE_NAME + progLangObjectReferenceDelimiter2[progLang] + progLangHasEntity[progLang] + progLangCloseParameterSpace[progLang] + progLangCloseParameterSpace[progLang];		//if(!(param2->lastSentenceReferenced.empty())){

	string codeBlockText4 = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + NLCprintDefs.generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangObjectReferenceDelimiter2[progLang] + progLangHasEntity[progLang] + progLangCloseParameterSpace[progLang];		//if(param1CategoryList.empty()){
		//NB this code could be generated using existing codeblock (NLC_CODEBLOCK_TYPE_IF_HAS_GENERIC_ENTITY)
	string codeBlockText5 = progLangElse[progLang];

	#ifdef NLC_ADVANCED_REFERENCING_MONITOR_CONTEXT
	string codeBlockText1 = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + param2->instanceName + progLangObjectReferenceDelimiter[progLang] + NLC_ADVANCED_REFERENCING_LAST_SENTENCE_REFERENCED_VARIABLE_NAME + progLangObjectReferenceDelimiter2[progLang] + progLangStackGetLast[progLang] + progLangGreaterThan[progLang] + progLangOpenParameterSpace[progLang] + NLCprintDefs.generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangObjectReferenceDelimiter2[progLang] + progLangGetLast[progLang] + progLangCloseParameterSpace[progLang] + progLangObjectReferenceDelimiter[progLang] + NLC_ADVANCED_REFERENCING_LAST_SENTENCE_REFERENCED_VARIABLE_NAME + progLangObjectReferenceDelimiter2[progLang] + progLangStackGetLast[progLang] + progLangCloseParameterSpace[progLang];		//if(param2->lastSentenceReferenced.top() > param1CategoryList.back()->lastSentenceReferenced.top())
	string codeBlockText2 = progLangElseIf[progLang] + progLangOpenParameterSpace[progLang] + param2->instanceName + progLangObjectReferenceDelimiter[progLang] + NLC_ADVANCED_REFERENCING_LAST_SENTENCE_REFERENCED_VARIABLE_NAME + progLangObjectReferenceDelimiter2[progLang] + progLangStackGetLast[progLang] + progLangEqualsTest[progLang] + progLangOpenParameterSpace[progLang] + NLCprintDefs.generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangObjectReferenceDelimiter2[progLang] + progLangGetLast[progLang] + progLangCloseParameterSpace[progLang] + progLangObjectReferenceDelimiter[progLang] + NLC_ADVANCED_REFERENCING_LAST_SENTENCE_REFERENCED_VARIABLE_NAME + progLangObjectReferenceDelimiter2[progLang] + progLangStackGetLast[progLang] + progLangCloseParameterSpace[progLang];		//if(param2->lastSentenceReferenced.top() == param1CategoryList.back()->lastSentenceReferenced.top())
	#else
	string codeBlockText1 = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + param2->instanceName + progLangObjectReferenceDelimiter[progLang] + NLC_ADVANCED_REFERENCING_LAST_SENTENCE_REFERENCED_VARIABLE_NAME + progLangGreaterThan[progLang] + progLangOpenParameterSpace[progLang] + NLCprintDefs.generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangObjectReferenceDelimiter2[progLang] + progLangGetLast[progLang] + progLangCloseParameterSpace[progLang] + progLangObjectReferenceDelimiter[progLang] + NLC_ADVANCED_REFERENCING_LAST_SENTENCE_REFERENCED_VARIABLE_NAME + progLangCloseParameterSpace[progLang];		//if(param2->lastSentenceReferenced > param1CategoryList.back()->lastSentenceReferenced)
	string codeBlockText2 = progLangElseIf[progLang] + progLangOpenParameterSpace[progLang] + param2->instanceName + progLangObjectReferenceDelimiter[progLang] + NLC_ADVANCED_REFERENCING_LAST_SENTENCE_REFERENCED_VARIABLE_NAME + progLangEqualsTest[progLang] + progLangOpenParameterSpace[progLang] + NLCprintDefs.generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangObjectReferenceDelimiter2[progLang] + progLangGetLast[progLang] + progLangCloseParameterSpace[progLang] + progLangObjectReferenceDelimiter[progLang] + NLC_ADVANCED_REFERENCING_LAST_SENTENCE_REFERENCED_VARIABLE_NAME + progLangCloseParameterSpace[progLang];		//if(param2->lastSentenceReferenced == param1CategoryList.back()->lastSentenceReferenced)
	#endif
	string codeBlockText3 = progLangElse[progLang];

	string removeCategoryListItemsText = NLCprintDefs.generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangObjectReferenceDelimiter2[progLang] + progLangRemoveProperties[progLang] + progLangEndLine[progLang];		//param1CategoryList.clear();
		//NB this code could be moved to a new codeblock (NLC_CODEBLOCK_TYPE_REMOVE_PROPERTIES_GENERIC_LIST)

	string addCategoryItemText = NLCprintDefs.generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangObjectReferenceDelimiter2[progLang] + progLangAddEntityToList[progLang] + progLangOpenParameterSpace[progLang] + param2->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//param1CategoryList.push_back(param2);
		//NB this code could be generated using existing codeblock (NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST)

	#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN_DO_NOT_ADD_DUPLICATES
	string negativeModifierStringFind = progLangNot[progLang];	//if not found (negative find)
	string findCategoryItemText = progLangFindPart1[progLang] + negativeModifierStringFind + progLangFindPart2[progLang] + NLCprintDefs.generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangFindPart3[progLang] + NLCprintDefs.generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangFindPart4[progLang] + param2->instanceName + progLangFindPart5[progLang] + NLCprintDefs.generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangFindPart6[progLang];	//if(!find(param1CategoryList.begin(), param1CategoryList.end(), param2) != param1CategoryList.end())
		//NB this code could be moved to a new codeblock  (NLC_CODEBLOCK_TYPE_FIND_PROPERTY_IN_GENERIC_LIST)
	#endif

	int q = 0;
	NLCprintDefs.printLine("", level, code);
	NLCprintDefs.printLine(codeBlockTextTemplateHeader, level, code);
	NLCprintDefs.printLine(codeBlockTextFunctionHeader, level, code);
	NLCprintDefs.printLine(progLangOpenBlock[progLang], level, code);
	q++;
		#ifdef NLC_ADVANCED_REFERENCING_MONITOR_CONTEXT
		NLCprintDefs.printLine(codeBlockText6, level+q, code);
		NLCprintDefs.printLine(progLangOpenBlock[progLang], level+q, code);
		q++;
		#endif

			NLCprintDefs.printLine(codeBlockText4, level+q, code);
			NLCprintDefs.printLine(progLangOpenBlock[progLang], level+q, code);
				NLCprintDefs.printLine(addCategoryItemText, level+q+1, code);
			NLCprintDefs.printLine(progLangCloseBlock[progLang], level+q, code);
			NLCprintDefs.printLine(codeBlockText5, level+q, code);
			NLCprintDefs.printLine(progLangOpenBlock[progLang], level+q, code);
			q++;
				NLCprintDefs.printLine(codeBlockText1, level+q, code);
				NLCprintDefs.printLine(progLangOpenBlock[progLang], level+q, code);
				NLCprintDefs.printLine(removeCategoryListItemsText, level+q+1, code);
				NLCprintDefs.printLine(addCategoryItemText, level+q+1, code);
				NLCprintDefs.printLine(progLangCloseBlock[progLang], level+q, code);

				NLCprintDefs.printLine(codeBlockText2, level+q, code);
				NLCprintDefs.printLine(progLangOpenBlock[progLang], level+q, code);
				#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN_DO_NOT_ADD_DUPLICATES
				NLCprintDefs.printLine(findCategoryItemText, level+q+1, code);
				NLCprintDefs.printLine(progLangOpenBlock[progLang], level+q+1, code);
					NLCprintDefs.printLine(addCategoryItemText, level+q+2, code);
				NLCprintDefs.printLine(progLangCloseBlock[progLang], level+q+1, code);
				#else
				NLCprintDefs.printLine(addCategoryItemText, level+q+1, code);
				#endif
				NLCprintDefs.printLine(progLangCloseBlock[progLang], level+q, code);

				NLCprintDefs.printLine(codeBlockText3, level+q, code);
				NLCprintDefs.printLine(progLangOpenBlock[progLang], level+q, code);
				NLCprintDefs.printLine(progLangCloseBlock[progLang], level+q, code);
			q--;
			NLCprintDefs.printLine(progLangCloseBlock[progLang], level+q, code);

			/*
			if(!(param1CategoryList.empty()))
			{
				param1CategoryList.push_back(param2);
			}
			else
			{
				if(param1->lastSentenceReferenced > param1CategoryList.back()->lastSentenceReferenced)
				{
					param1CategoryList.clear();
					param1CategoryList.push_back(param2);
				}
				else if(param1->lastSentenceReferenced == param1CategoryList.back()->lastSentenceReferenced)
				{
					if(!find(param1CategoryList.begin(), param1CategoryList.end(), param2) != param1CategoryList.end())
					{
						param1CategoryList.push_back(param2);
					}
				}
				else
				{

				}
			}
			*/

		#ifdef NLC_ADVANCED_REFERENCING_MONITOR_CONTEXT
		q--;
		NLCprintDefs.printLine(progLangCloseBlock[progLang], level+q, code);
		#endif

		#ifdef NLC_CATEGORIES_TEST_PLURALITY_WARNING
		#ifdef NLC_CATEGORIES_TEST_PLURALITY_WARNING_PLACE_IN_NLC_PREDEFINED_FUNCTION_ADDTOCATEGORYIFPASSSINGULARDEFINITEREFERENCINGTESTS
		#ifdef NLC_CATEGORIES_TEST_PLURALITY_COMMENT
		string comment = "Singular definite plurality tests";
		string codeBlockText7 = progLangOpenSingleLineComment[progLang] + comment;
		NLCprintDefs.printLine(codeBlockText7, level+q, code);
			//NB this code could be moved to a new codeblock (NLC_CODEBLOCK_TYPE_COMMENT_SINGLE_LINE)
		#endif
		int value = 1;	//see generateContextBlocksCategories
		string intValueString = SHAREDvars.convertIntToString(value);
		string codeBlockText8 = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + NLCprintDefs.generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangObjectReferenceDelimiter2[progLang] + progLangSizeOfList[progLang] + progLangGreaterThan[progLang] + intValueString + progLangCloseParameterSpace[progLang];		//if(param1CategoryList.size() > 1){
		NLCprintDefs.printLine(codeBlockText8, level+q, code);
		NLCprintDefs.printLine(progLangOpenBlock[progLang], level+q, code);
			//NB this code could be moved to a new codeblock (NLC_CODEBLOCK_TYPE_IF_HAS_GREATER_THAN_NUM_GENERIC_ENTITY)
		string codeBlockText9 = progLangPrintTextOpen[progLang] + NLC_CATEGORIES_TEST_PLURALITY_WARNING_MESSAGE + progLangPrintTextClose[progLang]  + progLangEndLine[progLang];	//cout << "Execution warning: multiple objects have been added to a singular definite variable (category) - should the entity have been defined as plural instead?" << endl;
		NLCprintDefs.printLine(codeBlockText9, level+q+1, code);
			//NB this code could be moved to a new codeblock (NLC_CODEBLOCK_TYPE_PRINT_WARNING)
		NLCprintDefs.printLine(progLangCloseBlock[progLang], level+q, code);
		#endif
		#endif

	q--;
	NLCprintDefs.printLine(progLangCloseBlock[progLang], level+q, code);

	delete param1;
	delete param2;
}

void NLCprintCodeBlocksFunctionsClass::generateCodeAddToCategoryIfPassSingularDefiniteReferencingTestsExecuteFunction(const NLCitem* param1, const NLCitem* param2, const NLCitem* param3, const int progLang, string* code, const int level, const bool castToCategoryType)
{
	string genericListAppendName = param3->name;

	string codeBlockText = "";
	if(castToCategoryType)
	{
		#ifdef NLC_NONOO
		string codeBlockTextTemplateDefinition = "";
		#else
		string codeBlockTextTemplateDefinition = progLangTemplateUsePart1[progLang] + param1->className + progLangTemplateUseClassSeparator[progLang] + param1->className + progLangTemplateUsePart2[progLang]; 	//<param1class, param1class>
		#endif
		codeBlockText = codeBlockText + NLC_ADVANCED_REFERENCING_SINGULAR_DEFINITE_REFERENCING_TESTS_FUNCTION_NAME + codeBlockTextTemplateDefinition + progLangOpenParameterSpace[progLang] + NLCprintDefs.generateCategoryListName(param1, genericListAppendName) + progLangClassMemberFunctionParametersNext[progLang] + NLCprintDefs.generateDynamicCastOfEntity(param2->instanceName, param1->className, progLang) + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//addToCategoryIfPassSingularDefinitePluralityTests<param1class, param2class>(param1CategoryList, dynamic_cast<param1class*>(param2instanceName));
	}
	else
	{
		#ifdef NLC_NONOO
		string codeBlockTextTemplateDefinition = "";
		#else
		string codeBlockTextTemplateDefinition = progLangTemplateUsePart1[progLang] + param1->className + progLangTemplateUseClassSeparator[progLang] + param2->className + progLangTemplateUsePart2[progLang]; 	//<param1class, param2class>
		#endif
		codeBlockText = codeBlockText + NLC_ADVANCED_REFERENCING_SINGULAR_DEFINITE_REFERENCING_TESTS_FUNCTION_NAME + codeBlockTextTemplateDefinition + progLangOpenParameterSpace[progLang] + NLCprintDefs.generateCategoryListName(param1, genericListAppendName) + progLangClassMemberFunctionParametersNext[progLang] + param2->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//addToCategoryIfPassSingularDefinitePluralityTests<param1class, param2class>(param1CategoryList, param2instanceName);
	}
	NLCprintDefs.printLine(codeBlockText, level, code);
}
#endif
#endif

#ifdef NLC_PERFORM_PLURAL_DEFINITE_REFERENCING_TESTS
void NLCprintCodeBlocksFunctionsClass::generateCodeAddToCategoryIfPassPluralDefiniteReferencingTestsNewFunction(const int progLang, string* code, const int level)
{
	string genericObjectName = "entity";
	NLCitem* param1 = new NLCitem(genericObjectName, NLC_ITEM_TYPE_OBJECT);
	NLCitem* param2 = new NLCitem(genericObjectName, NLC_ITEM_TYPE_OBJECT);
	//OLD: param2->instanceName = "entity0";
	string genericListAppendName = NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION;

	#ifdef NLC_NONOO
	string templateName1 = NLCNONOO_GENERIC_ENTITY_NODE_NAME;
	string templateName2 = NLCNONOO_GENERIC_ENTITY_NODE_NAME;
	string codeBlockTextTemplateHeader = "";
	#else
	string templateName1 = "E1";
	string templateName2 = "E2";
	string codeBlockTextTemplateHeader = progLangTemplateHeaderPart1[progLang] + progLangTemplateHeaderClassType[progLang] + templateName1 + progLangTemplateUseClassSeparator[progLang] + progLangTemplateHeaderClassType[progLang] + templateName2 + progLangTemplateHeaderPart2[progLang];  //template <class E1, class E2>
	#endif
	string codeBlockTextFunctionHeader = progLangClassMemberFunctionTypeDefault[progLang] + NLC_ADVANCED_REFERENCING_PLURAL_DEFINITE_REFERENCING_TESTS_FUNCTION_NAME + progLangOpenParameterSpace[progLang] + NLCprintDefs.generateCodeEntityListDefinitionTypeTextReference(templateName1, progLang) + NLCprintDefs.generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangClassMemberFunctionParametersNext[progLang] + NLCprintDefs.generateCodeEntityDefinitionText(templateName2, param2->instanceName, progLang) + progLangCloseParameterSpace[progLang];	//void addToCategoryIfPassPluralDefiniteReferencingTests(vector<E1*>& param1CategoryList, E2* param2instanceName)

	//string codeBlockText6 = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + negativeModifierString + progLangOpenParameterSpace[progLang] + param2->instanceName + progLangObjectReferenceDelimiter[progLang] + NLC_ADVANCED_REFERENCING_LAST_SENTENCE_REFERENCED_VARIABLE_NAME + progLangObjectReferenceDelimiter2[progLang] + progLangHasEntity[progLang] + progLangCloseParameterSpace[progLang] + progLangCloseParameterSpace[progLang];		//if(!(param2->lastSentenceReferenced.empty())){

	string addCategoryItemText = NLCprintDefs.generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangObjectReferenceDelimiter2[progLang] + progLangAddEntityToList[progLang] + progLangOpenParameterSpace[progLang] + param2->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//param1CategoryList.push_back(param2);
		//NB this code could be generated using existing codeblock (NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST)

	#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN_DO_NOT_ADD_DUPLICATES
	string negativeModifierStringFind = progLangNot[progLang];	//if not found (negative find)
	string findCategoryItemText = progLangFindPart1[progLang] + negativeModifierStringFind + progLangFindPart2[progLang] + NLCprintDefs.generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangFindPart3[progLang] + NLCprintDefs.generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangFindPart4[progLang] + param2->instanceName + progLangFindPart5[progLang] + NLCprintDefs.generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangFindPart6[progLang];	//if(!find(param1CategoryList.begin(), param1CategoryList.end(), param2) != param1CategoryList.end())
		//NB this code could be moved to a new codeblock  (NLC_CODEBLOCK_TYPE_FIND_PROPERTY_IN_GENERIC_LIST)
	#endif

	int q = 0;
	NLCprintDefs.printLine("", level+q, code);
	NLCprintDefs.printLine(codeBlockTextTemplateHeader, level+q, code);
	NLCprintDefs.printLine(codeBlockTextFunctionHeader, level+q, code);
	NLCprintDefs.printLine(progLangOpenBlock[progLang], level+q, code);

		/*
		#ifdef NLC_ADVANCED_REFERENCING_MONITOR_CONTEXT
		q++;
		NLCprintDefs.printLine(codeBlockText6, level+q, code);
		NLCprintDefs.printLine(progLangOpenBlock[progLang], level+q, code);
		#endif
		*/
		q++;
			#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN_DO_NOT_ADD_DUPLICATES
			NLCprintDefs.printLine(findCategoryItemText, level+q, code);
			NLCprintDefs.printLine(progLangOpenBlock[progLang], level+q, code);
			NLCprintDefs.printLine(addCategoryItemText, level+q+1, code);
			NLCprintDefs.printLine(progLangCloseBlock[progLang], level+q, code);
			#else
			NLCprintDefs.printLine(addCategoryItemText, level+q, code);
			#endif

			/*
			if(!find(param1CategoryList.begin(), param1CategoryList.end(), param2) != param1CategoryList.end())
			{
				param1CategoryList.push_back(param2);
			}
			*/

		/*
		#ifdef NLC_ADVANCED_REFERENCING_MONITOR_CONTEXT
		q--;
		NLCprintDefs.printLine(progLangCloseBlock[progLang], level+q, code);
		#endif
		*/

		q--;
	NLCprintDefs.printLine(progLangCloseBlock[progLang], level+q, code);

	delete param1;
	delete param2;
}

void NLCprintCodeBlocksFunctionsClass::generateCodeAddToCategoryIfPassPluralDefiniteReferencingTestsExecuteFunction(const NLCitem* param1, const NLCitem* param2, const NLCitem* param3, const int progLang, string* code, const int level, const bool castToCategoryType)
{
	string genericListAppendName = param3->name;

	string codeBlockText = "";
	if(castToCategoryType)
	{
		#ifdef NLC_NONOO
		string codeBlockTextTemplateDefinition = "";
		#else
		string codeBlockTextTemplateDefinition = progLangTemplateUsePart1[progLang] + param1->className + progLangTemplateUseClassSeparator[progLang] + param1->className + progLangTemplateUsePart2[progLang]; 	//<param1class, param1class>
		#endif
		codeBlockText = codeBlockText + NLC_ADVANCED_REFERENCING_PLURAL_DEFINITE_REFERENCING_TESTS_FUNCTION_NAME + codeBlockTextTemplateDefinition + progLangOpenParameterSpace[progLang] + NLCprintDefs.generateCategoryListName(param1, genericListAppendName) + progLangClassMemberFunctionParametersNext[progLang] + NLCprintDefs.generateDynamicCastOfEntity(param2->instanceName, param1->className, progLang) + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//addToCategoryIfPassPluralDefiniteReferencingTests<param1class, param2class>(param1CategoryList, dynamic_cast<param1class*>(param2instanceName));
	}
	else
	{
		#ifdef NLC_NONOO
		string codeBlockTextTemplateDefinition = "";
		#else
		string codeBlockTextTemplateDefinition = progLangTemplateUsePart1[progLang] + param1->className + progLangTemplateUseClassSeparator[progLang] + param2->className + progLangTemplateUsePart2[progLang]; 	//<param1class, param2class>
		#endif
		codeBlockText = codeBlockText + NLC_ADVANCED_REFERENCING_PLURAL_DEFINITE_REFERENCING_TESTS_FUNCTION_NAME + codeBlockTextTemplateDefinition + progLangOpenParameterSpace[progLang] + NLCprintDefs.generateCategoryListName(param1, genericListAppendName) + progLangClassMemberFunctionParametersNext[progLang] + param2->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//addToCategoryIfPassPluralDefiniteReferencingTests<param1class, param2class>(param1CategoryList, param2instanceName);
	}
	NLCprintDefs.printLine(codeBlockText, level, code);
}
#endif


#ifdef NLC_ADVANCED_REFERENCING_MONITOR_CONTEXT
void NLCprintCodeBlocksFunctionsClass::generateCodeAddEntityToReferenceContextListNewFunction(const int progLang, string* code, const int level)
{
	string genericEntityClassName = NLCitemClass.generateClassName(NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE);
	string contextListName = string(NLC_ITEM_TYPE_REFERENCECONTEXTLEVELLIST_VAR_APPENDITION);
	string entityToAddName = NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE;

	string codeBlockTextFunctionHeader = progLangClassMemberFunctionTypeDefault[progLang] + NLC_ADVANCED_REFERENCING_MONITOR_CONTEXT_ADD_ENTITY_TO_CONTEXT_LIST_FUNCTION_NAME + progLangOpenParameterSpace[progLang] + NLCprintDefs.generateCodeEntityListDefinitionTypeTextReference(genericEntityClassName, progLang) + contextListName + progLangClassMemberFunctionParametersNext[progLang] + NLCprintDefs.generateCodeEntityDefinitionText(genericEntityClassName, entityToAddName, progLang) + progLangClassMemberFunctionParametersNext[progLang] + progLangClassLastSentenceIndexVariableType[progLang] + NLC_ADVANCED_REFERENCING_MONITOR_CONTEXT_SENTENCE_INDEX_VARIABLE_NAME + progLangCloseParameterSpace[progLang];	//void addVariableToContextList(vector<genericEntityClass*>& contextList, genericEntityClass* genericEntity, int sentenceIndex)

	NLCprintDefs.printLine("", level, code);
	NLCprintDefs.printLine(codeBlockTextFunctionHeader, level, code);
	NLCprintDefs.printLine(progLangOpenBlock[progLang], level, code);
		string pushLastSentenceReferencedText = contextListName + progLangObjectReferenceDelimiter2[progLang] + progLangAddEntityToList[progLang] + progLangOpenParameterSpace[progLang] + entityToAddName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//contextList.push_back(genericEntity);
		NLCprintDefs.printLine(pushLastSentenceReferencedText, (level+1), code);
		string codeBlockUpdateLastSentenceReferencedText = entityToAddName + progLangObjectReferenceDelimiter[progLang] + NLC_ADVANCED_REFERENCING_LAST_SENTENCE_REFERENCED_VARIABLE_NAME + progLangObjectReferenceDelimiter2[progLang] + progLangStackAdd[progLang] + progLangOpenParameterSpace[progLang] + NLC_ADVANCED_REFERENCING_MONITOR_CONTEXT_SENTENCE_INDEX_VARIABLE_NAME + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//genericEntity->lastSentenceReferenced.push(sentenceIndex);
		NLCprintDefs.printLine(codeBlockUpdateLastSentenceReferencedText, (level+1), code);
	NLCprintDefs.printLine(progLangCloseBlock[progLang], level, code);
}

void NLCprintCodeBlocksFunctionsClass::generateCodeAddEntityToReferenceContextListExecuteFunction(const NLCitem* param1, const NLCitem* param2, const NLCitem* param3, const int progLang, string* code, const int level)
{
	#ifdef NLC_ADVANCED_REFERENCING_MONITOR_CONTEXT_PRINT_LEVEL_USED_INSTEAD_OF_CONTEXT_LEVEL
	string contextLevelString = SHAREDvars.convertIntToString(level);
	#else
	string contextLevelString = param1->name;
	#endif
	string entityToAddName = param2->instanceName;
	string sentenceIndexString = param3->name;

	string genericEntityClassName = NLCitemClass.generateClassName(NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE);
	string contextListName = string(NLC_ITEM_TYPE_REFERENCECONTEXTLEVELLIST_VAR_APPENDITION) + contextLevelString;
	string tempVariableName = string(NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE);

	string codeBlockText = "";
	codeBlockText = codeBlockText + NLC_ADVANCED_REFERENCING_MONITOR_CONTEXT_ADD_ENTITY_TO_CONTEXT_LIST_FUNCTION_NAME + progLangOpenParameterSpace[progLang] + contextListName + progLangClassMemberFunctionParametersNext[progLang] + param2->instanceName + progLangClassMemberFunctionParametersNext[progLang] + sentenceIndexString + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//addVariableToContextList(contextListX, entityName, sentenceIndex);
	NLCprintDefs.printLine(codeBlockText, level, code);
}

void NLCprintCodeBlocksFunctionsClass::generateCodeClearReferenceContextListNewFunction(const int progLang, string* code, const int level)
{
	string iterIndexString = SHAREDvars.convertIntToString(1);	//functions declared at level 1
	string genericEntityClassName = NLCitemClass.generateClassName(NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE);
	string contextListName = string(NLC_ITEM_TYPE_REFERENCECONTEXTLEVELLIST_VAR_APPENDITION);
	string tempVariableName = string(NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE);

	string codeBlockTextFunctionHeader = progLangClassMemberFunctionTypeDefault[progLang] + NLC_ADVANCED_REFERENCING_MONITOR_CONTEXT_CLEAR_CONTEXT_LIST_FUNCTION_NAME + progLangOpenParameterSpace[progLang] + NLCprintDefs.generateCodeEntityListDefinitionTypeTextReference(genericEntityClassName, progLang) + contextListName + progLangCloseParameterSpace[progLang];	//void clearContextList(vector<genericEntityClass*>& contextList)

	NLCprintDefs.printLine("", level, code);
	NLCprintDefs.printLine(codeBlockTextFunctionHeader, level, code);
	NLCprintDefs.printLine(progLangOpenBlock[progLang], level, code);
		string codeBlockText = progLangFor[progLang] + progLangForIterPart1[progLang] + NLCprintDefs.generateCodeEntityListDefinitionTypeTextCompact(genericEntityClassName, progLang) + progLangForIterPart2a[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart2c[progLang] + contextListName + progLangForIterPart3a[progLang] + progLangForIterPart3b[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart3c[progLang] + contextListName + progLangForIterPart4a[progLang] + progLangForIterPart4b[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart4c[progLang];	//for(vector<genericEntityClass*>::iterator iterX = contextList.begin(); iterX < contextList.end(); iterX++)
		NLCprintDefs.printLine(codeBlockText, (level+1), code);
			NLCprintDefs.printLine(progLangOpenBlock[progLang], (level+1), code);	//{
			string tempVarDeclarationText = NLCprintDefs.generateCodeEntityDefinitionText(genericEntityClassName, tempVariableName, progLang) + progLangEquals[progLang] + NLCprintDefs.generateCodeIterReference(iterIndexString, progLang) + progLangEndLine[progLang];	//genericEntityClass* genericEntity = *iter2;
			NLCprintDefs.printLine(tempVarDeclarationText, (level+2), code);
			string popLastSentenceReferencedText = tempVariableName + progLangObjectReferenceDelimiter[progLang] + NLC_ADVANCED_REFERENCING_LAST_SENTENCE_REFERENCED_VARIABLE_NAME + progLangObjectReferenceDelimiter2[progLang] + progLangStackRemove[progLang] + progLangEndLine[progLang];	//genericEntity->lastSentenceReferenced.pop();
			NLCprintDefs.printLine(popLastSentenceReferencedText, (level+2), code);
		NLCprintDefs.printLine(progLangCloseBlock[progLang], (level+1), code);
		string clearContextListText = contextListName + progLangObjectReferenceDelimiter2[progLang] + progLangRemoveProperties[progLang] + progLangEndLine[progLang];		//contextList.clear();
		NLCprintDefs.printLine(clearContextListText, (level+1), code);
	NLCprintDefs.printLine(progLangCloseBlock[progLang], level, code);
}

void NLCprintCodeBlocksFunctionsClass::generateCodeClearReferenceContextListExecuteFunction(const NLCitem* param1, const int progLang, string* code, const int level)
{
	#ifdef NLC_ADVANCED_REFERENCING_MONITOR_CONTEXT_PRINT_LEVEL_USED_INSTEAD_OF_CONTEXT_LEVEL
	string contextLevelString = SHAREDvars.convertIntToString(level);
	#else
	string contextLevelString = param1->name;
	#endif

	string contextListName = string(NLC_ITEM_TYPE_REFERENCECONTEXTLEVELLIST_VAR_APPENDITION) + contextLevelString;

	string codeBlockExecuteFunctionText = "";
	codeBlockExecuteFunctionText = codeBlockExecuteFunctionText + NLC_ADVANCED_REFERENCING_MONITOR_CONTEXT_CLEAR_CONTEXT_LIST_FUNCTION_NAME +  progLangOpenParameterSpace[progLang] + contextListName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//clearContextLevelList(contextListX);
	NLCprintDefs.printLine(codeBlockExecuteFunctionText, level, code);
}

#endif
#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS
void NLCprintCodeBlocksFunctionsClass::generateCodeCastVectorNewFunction(const int progLang, string* code, const int level)
{
	string iterIndexString = SHAREDvars.convertIntToString(1);	//functions declared at level 1
	string templateName1 = "E1";
	string templateName2 = "E2";
	string entity1InstanceListName = templateName1 + NLCprintDefs.generateEntityListAppendName();
	string entity2InstanceListName = templateName2 + NLCprintDefs.generateEntityListAppendName();
	string tempVariableName = string(NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE);

	string codeBlockTextTemplateHeader = progLangTemplateHeaderPart1[progLang] + progLangTemplateHeaderClassType[progLang] + templateName1 + progLangTemplateUseClassSeparator[progLang] + progLangTemplateHeaderClassType[progLang] + templateName2 + progLangTemplateHeaderPart2[progLang];  //template <class E1, class E2>
	string codeBlockTextFunctionHeader = NLCprintDefs.generateCodeEntityListDefinitionTypeTextReference(templateName2, progLang) + NLC_CAST_VECTOR_FUNCTION_NAME + progLangOpenParameterSpace[progLang] + NLCprintDefs.generateCodeEntityListDefinitionTypeTextReference(templateName1, progLang) + entity1InstanceListName + progLangCloseParameterSpace[progLang];	//vector<E2*>& castVector(vector<E1*>& E1InstanceList)

	NLCprintDefs.printLine("", level, code);
	NLCprintDefs.printLine(codeBlockTextTemplateHeader, level, code);
	NLCprintDefs.printLine(codeBlockTextFunctionHeader, level, code);
	NLCprintDefs.printLine(progLangOpenBlock[progLang], level, code);
		string codeBlockTextDeclareVectorPointerAndSet = NLCprintDefs.generateCodeEntityListDefinitionTypeTextReference(templateName2, progLang) + entity2InstanceListName + progLangEquals[progLang] + NLCprintDefs.generateReinterpretCastOfVectorReference(entity1InstanceListName, templateName2, progLang) + progLangEndLine[progLang];	//vector<E2*>& E2InstanceList = reinterpret_cast<vector<E2*>&>(E1List);
		NLCprintDefs.printLine(codeBlockTextDeclareVectorPointerAndSet, (level+1), code);

		string codeBlockTextReturnNewVector = progLangReturn[progLang] + entity2InstanceListName + progLangEndLine[progLang];		//return E2InstanceList;
		NLCprintDefs.printLine(codeBlockTextReturnNewVector, (level+1), code);
	NLCprintDefs.printLine(progLangCloseBlock[progLang], level, code);	//}
}

void NLCprintCodeBlocksFunctionsClass::generateCodeCastVectorExecuteFunction(const NLCitem* param1, const NLCitem* param2, const int progLang, string* code, const int level)
{
	string codeBlockTextTemplateDefinition = progLangTemplateUsePart1[progLang] + param1->className + progLangTemplateUseClassSeparator[progLang] + param2->className + progLangTemplateUsePart2[progLang]; 	//<param1class, param2class>
	string codeBlockExecuteFunctionText = string("") + NLC_CAST_VECTOR_FUNCTION_NAME + codeBlockTextTemplateDefinition + progLangOpenParameterSpace[progLang] + NLCprintDefs.generateEntityListName(param1) + progLangCloseParameterSpace[progLang];	//castVector<param1class, param2class>(param1InstanceList)
	NLCprintDefs.printLine(codeBlockExecuteFunctionText, level, code);
}

#endif
#ifdef NLC_ADVANCED_REFERENCING_SUPPORT_ALIASES
void NLCprintCodeBlocksFunctionsClass::generateCodeFindAliasAndAddToCategoryListNewFunction(const int progLang, string* code, const int level)
{
	string iterIndexString = SHAREDvars.convertIntToString(1);	//functions declared at level 1

	string genericEntityClassName = NLCitemClass.generateClassName(NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE);
	string aliasListName = NLC_ITEM_TYPE_ALIASLIST_VAR_APPENDITION;
	string aliasName = NLC_ADVANCED_REFERENCING_SUPPORT_ALIASES_ALIAS_NAME;

	#ifdef NLC_NONOO
	string templateName1 = NLCNONOO_GENERIC_ENTITY_NODE_NAME;
	#else
	string templateName1 = "E1";
	#endif
	string entity1InstanceListName = templateName1 + NLCprintDefs.generateEntityListAppendName();
	string entity1CategoryListName = templateName1 + NLC_ITEM_TYPE_CATEGORYLIST_VAR_APPENDITION;
	string tempVariableName = string(NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE);	//NLCgenericEntity
	string tempVariableAliasListName = tempVariableName + progLangObjectReferenceDelimiter[progLang] + NLC_ITEM_TYPE_ALIASLIST_VAR_APPENDITION;

	#ifdef NLC_NONOO
	string codeBlockTextTemplateHeader = "";
	#else
	string codeBlockTextTemplateHeader = progLangTemplateHeaderPart1[progLang] + progLangTemplateHeaderClassType[progLang] + templateName1 + progLangTemplateHeaderPart2[progLang];  //template <class E1>
	#endif

	string codeBlockTextFunctionHeader = progLangClassMemberFunctionTypeDefault[progLang] + NLC_ADVANCED_REFERENCING_FIND_ALIAS_AND_ADD_TO_CATEGORY_LIST_FUNCTION_NAME + progLangOpenParameterSpace[progLang] + NLCprintDefs.generateCodeEntityListDefinitionTypeTextReference(templateName1, progLang) + entity1InstanceListName + progLangClassMemberFunctionParametersNext[progLang] + progLangAliasNameVariableType[progLang] + aliasName + progLangClassMemberFunctionParametersNext[progLang] + NLCprintDefs.generateCodeEntityListDefinitionTypeTextReference(templateName1, progLang) + entity1CategoryListName + progLangCloseParameterSpace[progLang];	//void findAliasAndAddToCategoryListNewFunction(vector<E1*>& E1instanceList, string aliasName, vector<E1*>& E1CategoryList)

	int q = 0;
	NLCprintDefs.printLine("", level+q, code);
	NLCprintDefs.printLine(codeBlockTextTemplateHeader, level+q, code);
	NLCprintDefs.printLine(codeBlockTextFunctionHeader, level+q, code);
	NLCprintDefs.printLine(progLangOpenBlock[progLang], level+q, code);
	q++;
		string codeBlockTextForLoop = progLangFor[progLang] + progLangForIterPart1[progLang] + progLangTypeName[progLang] + NLCprintDefs.generateCodeEntityListDefinitionTypeTextCompact(templateName1, progLang) + progLangForIterPart2a[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart2c[progLang] + entity1InstanceListName + progLangForIterPart3a[progLang] + progLangForIterPart3b[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart3c[progLang] + entity1InstanceListName + progLangForIterPart4a[progLang] + progLangForIterPart4b[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart4c[progLang];	//for(typename vector<E1*>::iterator iterX = E1InstanceList.begin(); iterX < E1InstanceList.end(); iterX++)
		NLCprintDefs.printLine(codeBlockTextForLoop, level+q, code);
		NLCprintDefs.printLine(progLangOpenBlock[progLang], level+q, code);	//{
			q++;
			string tempVarDeclarationText = NLCprintDefs.generateCodeEntityDefinitionText(templateName1, tempVariableName, progLang) + progLangEquals[progLang] + NLCprintDefs.generateCodeIterReference(iterIndexString, progLang) + progLangEndLine[progLang];	//E1* genericEntity = *iter1;
			NLCprintDefs.printLine(tempVarDeclarationText, (level+q), code);
			//NB this code could be generated using existing codeblock (NLC_CODEBLOCK_TYPE_FOR_GENERIC_LIST)

			string negativeModifierStringFind = "";	//if found (positive find)
			string findAliasNameInAliasListText = progLangFindPart1[progLang] + negativeModifierStringFind + progLangFindPart2[progLang] + tempVariableAliasListName + progLangFindPart3[progLang] + tempVariableAliasListName + progLangFindPart4[progLang] + aliasName + progLangFindPart5[progLang] + tempVariableAliasListName + progLangFindPart6[progLang];	//if(!find(genericEntity->aliasList.begin(), genericEntity->aliasList.end(), aliasName) != genericEntity->aliasList.end())
				//NB this code could be moved to a new codeblock  (NLC_CODEBLOCK_TYPE_FIND_PROPERTY_IN_GENERIC_LIST)
			NLCprintDefs.printLine(findAliasNameInAliasListText, level+q, code);
			NLCprintDefs.printLine(progLangOpenBlock[progLang], level+q, code);
			q++;
				string addEntityToCategoryText = entity1CategoryListName + progLangObjectReferenceDelimiter2[progLang] + progLangAddEntityToList[progLang] + progLangOpenParameterSpace[progLang] + tempVariableName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//E1CategoryList.push_back(genericEntity);
				NLCprintDefs.printLine(addEntityToCategoryText, (level+q), code);

			q--;
			NLCprintDefs.printLine(progLangCloseBlock[progLang], level+q, code);	//}
		q--;
		NLCprintDefs.printLine(progLangCloseBlock[progLang], level+q, code);	//}
	q--;
	NLCprintDefs.printLine(progLangCloseBlock[progLang], level+q, code);	//}
}

void NLCprintCodeBlocksFunctionsClass::generateCodeFindAliasAndAddToCategoryListExecuteFunction(const NLCitem* param1, const NLCitem* param2, const NLCitem* param3, const int progLang, string* code, const int level)
{
	string genericListAppendName = param3->name;

	#ifdef NLC_NONOO
	string codeBlockTextTemplateDefinition = "";
	#else
	string codeBlockTextTemplateDefinition = progLangTemplateUsePart1[progLang] + param2->className + progLangTemplateUsePart2[progLang]; 	//<param2class>
	#endif
	string codeBlockExecuteFunctionText = string("") + NLC_ADVANCED_REFERENCING_FIND_ALIAS_AND_ADD_TO_CATEGORY_LIST_FUNCTION_NAME + codeBlockTextTemplateDefinition + progLangOpenParameterSpace[progLang] + NLCprintDefs.generateEntityListName(param2) + progLangClassMemberFunctionParametersNext[progLang] + progLangStringOpenClose[progLang] + param1->name + progLangStringOpenClose[progLang] + progLangClassMemberFunctionParametersNext[progLang] + NLCprintDefs.generateCategoryListName(param2, genericListAppendName) + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//findAliasAndAddToCategoryList<param2class>(param2InstanceList, "param1aliasName", param3CategoryList);
	NLCprintDefs.printLine(codeBlockExecuteFunctionText, level, code);
}

void NLCprintCodeBlocksFunctionsClass::generateCodeFindAliasNewFunction(const int progLang, string* code, const int level)
{
	string iterIndexString = SHAREDvars.convertIntToString(1);	//functions declared at level 1

	string aliasName = NLC_ADVANCED_REFERENCING_SUPPORT_ALIASES_ALIAS_NAME;

	#ifdef NLC_NONOO
	string templateName1 = NLCNONOO_GENERIC_ENTITY_NODE_NAME;
	#else
	string templateName1 = "E1";
	#endif
	string entity1InstanceName = templateName1 + NLC_ITEM_TYPE_INSTANCE_VAR_APPENDITION;
	string entity1aliasListName = entity1InstanceName + progLangObjectReferenceDelimiter[progLang] + NLC_ITEM_TYPE_ALIASLIST_VAR_APPENDITION;

	string resultName = "result";

	#ifdef NLC_NONOO
	string codeBlockTextTemplateHeader = "";
	#else
	string codeBlockTextTemplateHeader = progLangTemplateHeaderPart1[progLang] + progLangTemplateHeaderClassType[progLang] + templateName1 + progLangTemplateHeaderPart2[progLang];  //template <class E1>
	#endif

	string codeBlockTextFunctionHeader = progLangClassMemberFunctionTypeBool[progLang] + NLC_ADVANCED_REFERENCING_FIND_ALIAS_FUNCTION_NAME + progLangOpenParameterSpace[progLang] + NLCprintDefs.generateCodeEntityDefinitionText(templateName1, entity1InstanceName, progLang) + progLangClassMemberFunctionParametersNext[progLang] + progLangAliasNameVariableType[progLang] + aliasName + progLangCloseParameterSpace[progLang];	//bool findAliasNewFunction(E1* E1instance, string aliasName)

	int q = 0;
	NLCprintDefs.printLine("", level+q, code);
	NLCprintDefs.printLine(codeBlockTextTemplateHeader, level+q, code);
	NLCprintDefs.printLine(codeBlockTextFunctionHeader, level+q, code);
	NLCprintDefs.printLine(progLangOpenBlock[progLang], level+q, code);
	q++;
		string declareText = NLCprintDefs.generateCodeDeclareBoolTextAndSetFalse(resultName, progLang);	//bool result = false;
		NLCprintDefs.printLine(declareText, level+q, code);

		string negativeModifierStringFind = "";	//if found (positive find)
		string findAliasNameInAliasListText = progLangFindPart1[progLang] + negativeModifierStringFind + progLangFindPart2[progLang] + entity1aliasListName + progLangFindPart3[progLang] + entity1aliasListName + progLangFindPart4[progLang] + aliasName + progLangFindPart5[progLang] + entity1aliasListName + progLangFindPart6[progLang];	//if(!find(E1instance->aliasList.begin(), E1instance->aliasList.end(), aliasName) != E1instance->aliasList.end())
			//NB this code could be moved to a new codeblock  (NLC_CODEBLOCK_TYPE_FIND_PROPERTY_IN_GENERIC_LIST)
		NLCprintDefs.printLine(findAliasNameInAliasListText, level+q, code);
		NLCprintDefs.printLine(progLangOpenBlock[progLang], level+q, code);
		q++;
			string setText = NLCprintDefs.generateCodeSetBoolTextTrue(resultName, progLang);	//result = true;
			NLCprintDefs.printLine(setText, (level+q), code);
		q--;
		NLCprintDefs.printLine(progLangCloseBlock[progLang], level+q, code);	//}

		string returnText = NLCprintDefs.generateCodeReturnText(resultName, progLang);	//return result;
		NLCprintDefs.printLine(returnText, level+q, code);
	q--;
	NLCprintDefs.printLine(progLangCloseBlock[progLang], level+q, code);	//}
}

void NLCprintCodeBlocksFunctionsClass::generateCodeFindAliasExecuteFunction(const NLCitem* param1, const NLCitem* param2, const int progLang, string* code, const int level)
{
	#ifdef NLC_NONOO
	string codeBlockTextTemplateDefinition = "";
	#else
	string codeBlockTextTemplateDefinition = progLangTemplateUsePart1[progLang] + param2->className + progLangTemplateUsePart2[progLang]; 	//<param2class>
	#endif
	string codeBlockExecuteFunctionText = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + NLC_ADVANCED_REFERENCING_FIND_ALIAS_FUNCTION_NAME + codeBlockTextTemplateDefinition + progLangOpenParameterSpace[progLang] + NLCprintDefs.generateEntityName(param2) + progLangClassMemberFunctionParametersNext[progLang] + progLangStringOpenClose[progLang] + param1->name + progLangStringOpenClose[progLang] + progLangCloseParameterSpace[progLang] + progLangCloseParameterSpace[progLang];	//if(findAlias<param2class>(param2, "param1aliasName"))
	NLCprintDefs.printLine(codeBlockExecuteFunctionText, level, code);
	NLCprintDefs.printLine(progLangOpenBlock[progLang], level, code);	//{
}

#endif
#ifdef NLC_REDEFINITIONS
void NLCprintCodeBlocksFunctionsClass::generateCodeCheckParentClassNameNewFunction(const int progLang, string* code, const int level)
{
	string iterIndexString = SHAREDvars.convertIntToString(1);	//functions declared at level 1

	string objectName = "object";
	string genericEntityClassName = NLCitemClass.generateClassName(NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE);
	string className = "className";
	string parentName = "parent";
	string resultName = "result";

	string codeBlockTextFunctionHeader = progLangClassMemberFunctionTypeBool[progLang] + NLC_CLASS_PARENT_CHECK_PARENT_CLASS_NAME_FUNCTION_NAME + progLangOpenParameterSpace[progLang] + NLCprintDefs.generateCodeEntityDefinitionText(genericEntityClassName, objectName, progLang) + progLangClassMemberFunctionParametersNext[progLang] + progLangClassNameVariableType[progLang] + className + progLangCloseParameterSpace[progLang];	//bool checkParentClassName(NLCgenericEntityClass* object, string className)

	int q = 0;
	NLCprintDefs.printLine("", level+q, code);
	NLCprintDefs.printLine(codeBlockTextFunctionHeader, level+q, code);
	NLCprintDefs.printLine(progLangOpenBlock[progLang], level+q, code);
	q++;
		string declareText = NLCprintDefs.generateCodeDeclareBoolTextAndSetFalse(resultName, progLang);	//bool result = false;
		NLCprintDefs.printLine(declareText, level+q, code);

		string negativeModifierStringFind = "";	//if found (positive find)
		string ifObjectNameEqualsClassNameText = NLCprintDefs.generateCodeClassNameTestText(objectName, className, progLang);	//if(object->name == className)
			//NB this code could be moved to a new codeblock  (NLC_CODEBLOCK_TYPE_IF_OBJECT_NAME_EQUALS_STRING)
		NLCprintDefs.printLine(ifObjectNameEqualsClassNameText, level+q, code);
		NLCprintDefs.printLine(progLangOpenBlock[progLang], level+q, code);
		q++;
			string setText = NLCprintDefs.generateCodeSetBoolTextTrue(resultName, progLang);	//result = true;
			NLCprintDefs.printLine(setText, (level+q), code);
		q--;
		NLCprintDefs.printLine(progLangCloseBlock[progLang], level+q, code);	//}


		string contextParam1 = objectName + progLangObjectReferenceDelimiter[progLang];
		string codeBlockText = progLangFor[progLang] + progLangForIterPart1[progLang] + NLCprintDefs.generateCodeEntityListDefinitionTypeTextCompact(genericEntityClassName, progLang) + progLangForIterPart2a[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart2c[progLang] + contextParam1 + NLC_CLASS_PARENT_CLASS_LIST_NAME + progLangForIterPart3a[progLang] + progLangForIterPart3b[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart3c[progLang] + contextParam1 + NLC_CLASS_PARENT_CLASS_LIST_NAME + progLangForIterPart4a[progLang] + progLangForIterPart4b[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart4c[progLang];	//for(vector<NLCgenericEntityClass*>::iterator iter1 = object->parentClassList.begin(); iter1 < object->parentClassList.end(); iter1++)
		NLCprintDefs.printLine(codeBlockText, level+q, code);
		NLCprintDefs.printLine(progLangOpenBlock[progLang], level+q, code);
		q++;
			string tempVarDeclarationText = NLCprintDefs.generateCodeEntityDefinitionText(genericEntityClassName, parentName, progLang) + progLangEquals[progLang] + NLCprintDefs.generateCodeIterReference(iterIndexString, progLang) + progLangEndLine[progLang];	//NLCgenericEntityClass* parent = *iter1;
			NLCprintDefs.printLine(tempVarDeclarationText, (level+q), code);
			string codeBlockExecuteFunctionText = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + NLC_CLASS_PARENT_CHECK_PARENT_CLASS_NAME_FUNCTION_NAME + progLangOpenParameterSpace[progLang] + parentName + progLangClassMemberFunctionParametersNext[progLang] + className + progLangCloseParameterSpace[progLang] + progLangCloseParameterSpace[progLang];	//if(checkParentClassName(parent, className))
			NLCprintDefs.printLine(codeBlockExecuteFunctionText, level+q, code);
			NLCprintDefs.printLine(progLangOpenBlock[progLang], level+q, code);
			q++;
				NLCprintDefs.printLine(setText, (level+q), code);
			q--;
			NLCprintDefs.printLine(progLangCloseBlock[progLang], level+q, code);	//}
		q--;
		NLCprintDefs.printLine(progLangCloseBlock[progLang], level+q, code);	//}

		string returnText = NLCprintDefs.generateCodeReturnText(resultName, progLang);	//return result;
		NLCprintDefs.printLine(returnText, level+q, code);
	q--;
	NLCprintDefs.printLine(progLangCloseBlock[progLang], level+q, code);	//}
}

void NLCprintCodeBlocksFunctionsClass::generateCodeCheckParentClassNameExecuteFunction1(const NLCitem* param1, const NLCitem* param2, const int progLang, string* code, const int level)
{
	string objectName = param1->instanceName;
	string classNameToFind = param2->name;
	string genericEntityClassName = NLCitemClass.generateClassName(NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE);
	string codeBlockExecuteFunctionText = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + string(NLC_CLASS_PARENT_CHECK_PARENT_CLASS_NAME_FUNCTION_NAME) + progLangOpenParameterSpace[progLang] + NLCprintDefs.generateStaticCastOfEntity(objectName, genericEntityClassName, progLang) + progLangClassMemberFunctionParametersNext[progLang] + progLangStringOpenClose[progLang] + classNameToFind + progLangStringOpenClose[progLang] + progLangCloseParameterSpace[progLang] + progLangCloseParameterSpace[progLang];	//if(checkParentClassName(static_cast<NLCgenericEntityClass*>(param1), param2))
	NLCprintDefs.printLine(codeBlockExecuteFunctionText, level, code);
	NLCprintDefs.printLine(progLangOpenBlock[progLang], level, code);	//{
}

void NLCprintCodeBlocksFunctionsClass::generateCodeCheckParentClassNameExecuteFunction2(const NLCitem* param1, const NLCitem* param2, const int progLang, string* code, const int level)
{
	string objectClassName = param1->className;
	string classNameToFind = param2->name;
	string genericEntityClassName = NLCitemClass.generateClassName(NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE);
	string codeBlockExecuteFunctionText = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + string(NLC_CLASS_PARENT_CHECK_PARENT_CLASS_NAME_FUNCTION_NAME) + progLangOpenParameterSpace[progLang] + NLCprintDefs.generateStaticCastOfNewEntity(objectClassName, genericEntityClassName, progLang) + progLangClassMemberFunctionParametersNext[progLang] + progLangStringOpenClose[progLang] + classNameToFind + progLangStringOpenClose[progLang] + progLangCloseParameterSpace[progLang] + progLangCloseParameterSpace[progLang];	//if(checkParentClassName(static_cast<NLCgenericEntityClass*>(new param1Class), param2))
	NLCprintDefs.printLine(codeBlockExecuteFunctionText, level, code);
	NLCprintDefs.printLine(progLangOpenBlock[progLang], level, code);	//{
}

#endif


void NLCprintCodeBlocksFunctionsClass::generateCodeAddProperty(NLCitem* param1, const NLCitem* param2, const int progLang, string* code, const int level)
{
	#ifdef NLC_LIBRARY_BASE_EXTENDED
	this->generateCodeAddPropertyExecuteFunction(param1, param2, progLang, code, level);
	#else
	#ifdef NLC_NON_LIBRARY_FUNCTIONS_EXTENDED
	this->generateCodeAddPropertyExecuteFunction(param1, param2, progLang, code, level);
	#else
	this->generateCodeAddPropertyEntityToList(param1, param2, progLang, code, level);
	#endif
	#endif
}
void NLCprintCodeBlocksFunctionsClass::generateCodeAddPropertyEntityToList(NLCitem* param1, const NLCitem* param2, const int progLang, string* code, const int level)
{
	string contextParam1 = NLCprintDefs.generateStringFromContextVector(&(param1->context), progLang);
	#ifdef NLC_NONOO
	this->generateCodeAddEntityToList(contextParam1 + param1->instanceName + progLangObjectReferenceDelimiter[progLang] + NLCprintDefs.generatePropertyListName(), param2->instanceName, progLang, code, level);
	this->generateCodeAddEntityToList(param2->instanceName + progLangObjectReferenceDelimiter[progLang] + NLCprintDefs.generatePropertyReverseListName(), contextParam1 + param1->instanceName, progLang, code, level);
	#else
	this->generateCodeAddEntityToList(contextParam1 + param1->instanceName + progLangObjectReferenceDelimiter[progLang] + NLCprintDefs.generatePropertyListName(param2->className), param2->instanceName, progLang, code, level);
	this->generateCodeAddEntityToList(param2->instanceName + progLangObjectReferenceDelimiter[progLang] + NLCprintDefs.generateAllPropertyIncomingListName(), contextParam1 + param1->instanceName, progLang, code, level);
	#endif
}

void NLCprintCodeBlocksFunctionsClass::generateCodeAddEntityToList(const string entityName, const string listName, const int progLang, string* code, const int level)
{
	string codeBlockText = listName + progLangObjectReferenceDelimiter2[progLang] + progLangAddProperty[progLang] + progLangOpenParameterSpace[progLang] + entityName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//eg listName.push_back(entityName);
	NLCprintDefs.printLine(codeBlockText, level, code);
}


#ifdef NLC_LIBRARY_BASE_EXTENDED
void NLCprintCodeBlocksFunctionsClass::generateCodeAddPropertyExecuteFunction(NLCitem* param1, const NLCitem* param2, const int progLang, string* code, const int level)
{
	string contextParam1 = NLCprintDefs.generateStringFromContextVector(&(param1->context), progLang);
	string codeBlockTextTemplateDefinition = progLangTemplateUsePart1[progLang] + param1->className + progLangTemplateUseClassSeparator[progLang] + param2->className + progLangTemplateUsePart2[progLang]; 	//<param1class, param2class>
	string codeBlockExecuteFunctionText = "";
	codeBlockExecuteFunctionText = codeBlockExecuteFunctionText + NLC_LIBRARY_BASE_EXTENDED_FUNCTION_NAME_ADD_PROPERTY + codeBlockTextTemplateDefinition + progLangOpenParameterSpace[progLang] + contextParam1 + param1->instanceName + progLangClassMemberFunctionParametersNext[progLang] + NLCprintDefs.generateCodeListPointer(contextParam1 + param1->instanceName + progLangObjectReferenceDelimiter[progLang] + NLCprintDefs.generatePropertyListName(param2), progLang) + progLangClassMemberFunctionParametersNext[progLang] + param2->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//addProperty<param1class, param2class>(context1->param1, &(context1->param1.param2PropertyList), param2);
	NLCprintDefs.printLine(codeBlockExecuteFunctionText, level, code);
}
#endif
#ifdef NLC_NON_LIBRARY_FUNCTIONS_EXTENDED
void NLCprintCodeBlocksFunctionsClass::generateCodeAddPropertyNewFunction(const int progLang, string* code, const int level)
{
	#ifdef NLC_ENUM_LISTS
	cout << "NLC_NON_LIBRARY_FUNCTIONS_EXTENDED:generateCodeAddPropertyNewFunction{} error: does not support NLC_ENUM_LISTS, use NLC_LIBRARY:NLC_LIBRARY_BASE_EXTENDED instead (NLClibraryBase.cpp)" << endl;
	#else
	string templateName1 = "E1";
	string templateName2 = "E2";
	NLCitem param1(templateName1, NLC_ITEM_TYPE_OBJECT);
	NLCitem param2(templateName2, NLC_ITEM_TYPE_OBJECT);
	param1->instanceName = templateName1 + NLCprintDefs.generateEntityListAppendName();
	param2->instanceName = templateName2 + NLCprintDefs.generateEntityListAppendName();

	string codeBlockTextTemplateHeader = progLangTemplateHeaderPart1[progLang] + progLangTemplateHeaderClassType[progLang] + templateName1 + progLangTemplateUseClassSeparator[progLang] + progLangTemplateHeaderClassType[progLang] + templateName2 + progLangTemplateHeaderPart2[progLang];  //template <class E1, class E2>
	string codeBlockTextFunctionHeader = progLangClassMemberFunctionTypeDefault[progLang] + NLC_LIBRARY_BASE_EXTENDED_FUNCTION_NAME_ADD_PROPERTY + progLangOpenParameterSpace[progLang] +  NLCprintDefs.generateCodeEntityDefinitionText(param1, progLang) + progLangParameterSpaceNextParam[progLang] + NLCprintDefs.generateCodePropertyListDefinitionText(param2, progLang) + progLangParameterSpaceNextParam[progLang] + NLCprintDefs.generateCodeEntityDefinitionText(param2, progLang) + progLangCloseParameterSpace[progLang];	//void addProperty(E1* E1Instance, vector<E2*>* E2PropertyList, E2* E2Instance)

	int q = 0;
	NLCprintDefs.printLine("", level+q, code);
	NLCprintDefs.printLine(codeBlockTextTemplateHeader, level+q, code);
	NLCprintDefs.printLine(codeBlockTextFunctionHeader, level+q, code);
	NLCprintDefs.printLine(progLangOpenBlock[progLang], level+q, code);

	q++;
	string codeBlockText = NLCprintDefs.generatePropertyListName(param2) + progLangObjectReferenceDelimiter2[progLang] + progLangAddProperty[progLang] + progLangOpenParameterSpace[progLang] + param2->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//param2PropertyList.push_back(param2);
	NLCprintDefs.printLine(codeBlockText, level+q, code);
	codeBlockText = param2->instanceName + progLangObjectReferenceDelimiter[progLang] + NLCprintDefs.generateAllPropertyIncomingListName() + progLangObjectReferenceDelimiter2[progLang] + progLangAddProperty[progLang] + progLangOpenParameterSpace[progLang] + contextParam1 + param1->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//param2->propertyIncomingList.push_back(context1->param1);
	NLCprintDefs.printLine(codeBlockText, level+q, code);

	q--;
	NLCprintDefs.printLine(progLangCloseBlock[progLang], level+q, code);
	#endif
}
#endif


void NLCprintCodeBlocksFunctionsClass::generateCodeRemoveProperty(NLCitem* param1, const NLCitem* param2, const int progLang, string* code, const int level)
{
	#ifdef NLC_LIBRARY_BASE_EXTENDED
	this->generateCodeRemovePropertyExecuteFunction(param1, param2, progLang, code, level);
	#else
	FINISHTHIS
	NLCprintDefs.printLine(codeBlockText, level, code);
	#endif
}
void NLCprintCodeBlocksFunctionsClass::generateCodeRemoveProperties(NLCitem* param1, const NLCitem* param2, const int progLang, string* code, const int level)
{
	#ifdef NLC_LIBRARY_BASE_EXTENDED
	this->generateCodeRemovePropertiesExecuteFunction(param1, param2, progLang, code, level);
	#else
	string codeBlockText = contextParam1 + param1->instanceName + progLangObjectReferenceDelimiter[progLang] + NLCprintDefs.generatePropertyListName(param2) + progLangObjectReferenceDelimiter2[progLang] + progLangRemoveProperties[progLang] + progLangEndLine[progLang];		//context1->param1->param2PropertyList.clear();
	NLCprintDefs.printLine(codeBlockText, level, code);
	#endif
}
#ifdef NLC_LIBRARY_BASE_EXTENDED
void NLCprintCodeBlocksFunctionsClass::generateCodeRemovePropertyExecuteFunction(NLCitem* param1, const NLCitem* param2, const int progLang, string* code, const int level)
{
	string contextParam1 = NLCprintDefs.generateStringFromContextVector(&(param1->context), progLang);
	string codeBlockTextTemplateDefinition = progLangTemplateUsePart1[progLang] + param1->className + progLangTemplateUseClassSeparator[progLang] + param2->className + progLangTemplateUsePart2[progLang]; 	//<param1class, param2class>
	string codeBlockExecuteFunctionText = "";
	codeBlockExecuteFunctionText = codeBlockExecuteFunctionText + NLC_LIBRARY_BASE_EXTENDED_FUNCTION_NAME_REMOVE_PROPERTY + codeBlockTextTemplateDefinition + progLangOpenParameterSpace[progLang] + contextParam1 + param1->instanceName + progLangClassMemberFunctionParametersNext[progLang] + NLCprintDefs.generateCodeListPointer(contextParam1 + param1->instanceName + progLangObjectReferenceDelimiter[progLang] + NLCprintDefs.generatePropertyListName(param2), progLang) + progLangClassMemberFunctionParametersNext[progLang] + param2->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//removeProperty<param1class, param2class>(context1->param1, &(context1->param1.param2PropertyList), param2);
	NLCprintDefs.printLine(codeBlockExecuteFunctionText, level, code);
}
void NLCprintCodeBlocksFunctionsClass::generateCodeRemovePropertiesExecuteFunction(NLCitem* param1, const NLCitem* param2, const int progLang, string* code, const int level)
{
	string contextParam1 = NLCprintDefs.generateStringFromContextVector(&(param1->context), progLang);
	string codeBlockTextTemplateDefinition = progLangTemplateUsePart1[progLang] + param1->className + progLangTemplateUseClassSeparator[progLang] + param2->className + progLangTemplateUsePart2[progLang]; 	//<param1class, param2class>
	string codeBlockExecuteFunctionText = "";
	codeBlockExecuteFunctionText = codeBlockExecuteFunctionText + NLC_LIBRARY_BASE_EXTENDED_FUNCTION_NAME_REMOVE_PROPERTIES + codeBlockTextTemplateDefinition + progLangOpenParameterSpace[progLang] + contextParam1 + param1->instanceName + progLangClassMemberFunctionParametersNext[progLang] + NLCprintDefs.generateCodeListPointer(contextParam1 + param1->instanceName + progLangObjectReferenceDelimiter[progLang] + NLCprintDefs.generatePropertyListName(param2), progLang) + progLangClassMemberFunctionParametersNext[progLang] + param2->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//removeProperties<param1class, param2class>(context1->param1, &(context1->param1.param2PropertyList), param2);
	NLCprintDefs.printLine(codeBlockExecuteFunctionText, level, code);
}
#endif


void NLCprintCodeBlocksFunctionsClass::generateCodeAddCondition(NLCitem* param1, const NLCitem* param2, const NLCitem* param3, const int progLang, string* code, const int level, const bool inverseCondition)
{
	#ifdef NLC_LIBRARY_BASE_EXTENDED
	this->generateCodeAddConditionExecuteFunction(param1, param2, param3, progLang, code, level, inverseCondition);
	#else
	#ifdef NLC_NON_LIBRARY_FUNCTIONS_EXTENDED
	this->generateCodeAddConditionExecuteFunction(param1, param2, param3, progLang, code, level, inverseCondition);
	#else
	this->generateCodeAddConditionAndObjectEntityToList(param1, param2, param3, progLang, code, level, inverseCondition);
	#endif
	#endif
}
//NB NLC_NONOO requires !NLC_CONDITION_LISTS_STORE_CONDITION_AS_STRING
void NLCprintCodeBlocksFunctionsClass::generateCodeAddConditionAndObjectEntityToList(NLCitem* param1, const NLCitem* param2, const NLCitem* param3, const int progLang, string* code, const int level, const bool inverseCondition)
{
	string contextParam1 = NLCprintDefs.generateStringFromContextVector(&(param1->context), progLang);
	#ifndef NLC_CONDITION_LISTS_STORE_CONDITION_AS_STRING
	string codeBlockTextCreate2 = NLCprintDefs.generateCodeNewEntity(param2, progLang);
	NLCprintDefs.printLine(codeBlockTextCreate2, level, code);
	#ifdef NLC_NORMALISE_TWOWAY_PREPOSITIONS_MARK_INVERSE_CONDITIONS
	if(inverseCondition)
	{
		string codeBlockTextSetInverseCondition = NLCprintDefs.generateCodeSetBoolTextTrue(NLCprintDefs.generateCodeEntityInverseConditionText(param2, progLang), progLang);	//param2->inverseConditionTwoWay = true;
		NLCprintDefs.printLine(codeBlockTextSetInverseCondition, level, code);
	}
	#endif
	#endif
	#ifdef NLC_NONOO
	string codeBlockText = contextParam1 + param1->instanceName + progLangObjectReferenceDelimiter[progLang] + NLCprintDefs.generateGIAconditionListName() + progLangObjectReferenceDelimiter2[progLang] + progLangAddProperty[progLang] + progLangOpenParameterSpace[progLang] + param2->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//context1->param1->param2ConditionList.push_back(param2);
	NLCprintDefs.printLine(codeBlockText, level, code);
	codeBlockText = param2->instanceName + progLangObjectReferenceDelimiter[progLang] + NLCprintDefs.generateGIAconditionObjectListName() + progLangObjectReferenceDelimiter2[progLang] + progLangAddProperty[progLang] + progLangOpenParameterSpace[progLang] + param3->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//param2->param2ConditionObjectList.push_back(param3);
	NLCprintDefs.printLine(codeBlockText, level, code);
	#ifdef NLC_NONOO_CREATE_REVERSE_LISTS
	codeBlockText = param3->instanceName + progLangObjectReferenceDelimiter[progLang] + NLCprintDefs.generateGIAincomingConditionListName() + progLangObjectReferenceDelimiter2[progLang] + progLangAddProperty[progLang] + progLangOpenParameterSpace[progLang] + param2->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//param3->param2IncomingConditionList.push_back(param2);
	NLCprintDefs.printLine(codeBlockText, level, code);
	codeBlockText = param2->instanceName + progLangObjectReferenceDelimiter[progLang] + NLCprintDefs.generateGIAconditionSubjectListName() + progLangObjectReferenceDelimiter2[progLang] + progLangAddProperty[progLang] + progLangOpenParameterSpace[progLang] + contextParam1 + param1->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//param2->param2ConditionSubjectList.push_back(context1->param1);
	NLCprintDefs.printLine(codeBlockText, level, code);
	#endif
	#else
	#ifdef NLC_CONDITION_LISTS_VECTOR
	string codeBlockText = contextParam1 + param1->instanceName + progLangObjectReferenceDelimiter[progLang] + NLCprintDefs.generateConditionListName(param2->className, param3->className) + progLangObjectReferenceDelimiter2[progLang] + progLangAddCondition[progLang] + progLangOpenParameterSpace[progLang] + NLCprintDefs.generateCodeConditionNewPairText(param2->name, NLCprintDefs.generatePointerTypeText(param2->className, progLang), param2->instanceName, NLCprintDefs.generatePointerTypeText(param3->className, progLang), param3->instanceName, progLang) + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//context1->param1->param2param3ConditionList.push_back(new pair<param2className*, param3className*>(param2, param3));
	#else
	string codeBlockText = contextParam1 + param1->instanceName + progLangObjectReferenceDelimiter[progLang] + NLCprintDefs.generateConditionListName(param2->className, param3->className) + progLangObjectReferenceDelimiter2[progLang] + progLangAddCondition[progLang] + progLangOpenParameterSpace[progLang] + NLCprintDefs.generateCodeConditionPairText(param2->name, NLCprintDefs.generatePointerTypeText(param2->className, progLang), param2->instanceName, NLCprintDefs.generatePointerTypeText(param3->className, progLang), param3->instanceName, progLang) + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//context1->param1->param2param3ConditionList.insert(pair<param2className*, param3className*>(param2, param3));
	#endif
	NLCprintDefs.printLine(codeBlockText, level, code);
	#endif
}
#ifdef NLC_LIBRARY_BASE_EXTENDED
void NLCprintCodeBlocksFunctionsClass::generateCodeAddConditionExecuteFunction(NLCitem* param1, const NLCitem* param2, const NLCitem* param3, const int progLang, string* code, const int level, const bool inverseCondition)
{
	string functionName = NLC_LIBRARY_BASE_EXTENDED_FUNCTION_NAME_ADD_CONDITION;
	#ifdef NLC_NORMALISE_TWOWAY_PREPOSITIONS_MARK_INVERSE_CONDITIONS
	if(inverseCondition)
	{
		functionName = NLC_LIBRARY_BASE_EXTENDED_FUNCTION_NAME_ADD_CONDITION_INVERSE;
	}
	#endif

	string contextParam1 = NLCprintDefs.generateStringFromContextVector(&(param1->context), progLang);
	string codeBlockTextTemplateDefinition = progLangTemplateUsePart1[progLang] + param1->className + progLangTemplateUseClassSeparator[progLang] + param2->className + progLangTemplateUseClassSeparator[progLang] + param3->className + progLangTemplateUsePart2[progLang]; 	//<param1class, param2class, param3class>
	string codeBlockExecuteFunctionText = "";
	codeBlockExecuteFunctionText = codeBlockExecuteFunctionText + functionName + codeBlockTextTemplateDefinition + progLangOpenParameterSpace[progLang] + contextParam1 + param1->instanceName + progLangClassMemberFunctionParametersNext[progLang] + NLCprintDefs.generateCodeListPointer(contextParam1 + param1->instanceName + progLangObjectReferenceDelimiter[progLang] + NLCprintDefs.generateConditionListName(param2->className, param3->className), progLang) + progLangClassMemberFunctionParametersNext[progLang] + progLangStringOpenClose[progLang] + param2->name + progLangStringOpenClose[progLang] + progLangClassMemberFunctionParametersNext[progLang] + param3->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//addCondition<param1class, param2class, param3class>(context1->param1, &(context1->param1.param2param3ConditionList), "param2", param3);
	NLCprintDefs.printLine(codeBlockExecuteFunctionText, level, code);
}
#endif
#ifdef NLC_NON_LIBRARY_FUNCTIONS_EXTENDED
void NLCprintCodeBlocksFunctionsClass::generateCodeAddConditionNewFunction(const int progLang, string* code, const int level, const bool inverseCondition)
{
	#ifdef NLC_ENUM_LISTS
	cout << "NLC_NON_LIBRARY_FUNCTIONS_EXTENDED:generateCodeAddConditionNewFunction{} error: does not support NLC_ENUM_LISTS, use NLC_LIBRARY:NLC_LIBRARY_BASE_EXTENDED instead (NLClibraryBase.cpp)" << endl;
	#else

	string functionName = NLC_LIBRARY_BASE_EXTENDED_FUNCTION_NAME_ADD_CONDITION;
	#ifdef NLC_NORMALISE_TWOWAY_PREPOSITIONS_MARK_INVERSE_CONDITIONS
	if(inverseCondition)
	{
		functionName = NLC_LIBRARY_BASE_EXTENDED_FUNCTION_NAME_ADD_CONDITION_INVERSE;
	}
	#endif

	string templateName1 = "E1";
	string templateName2 = "E2";
	string templateName3 = "E3";
	NLCitem param1(templateName1, NLC_ITEM_TYPE_OBJECT);
	NLCitem param2(templateName2, NLC_ITEM_TYPE_OBJECT);
	NLCitem param2(templateName3, NLC_ITEM_TYPE_OBJECT);
	param1->instanceName = templateName1 + NLCprintDefs.generateEntityListAppendName();
	param2->instanceName = templateName2 + NLCprintDefs.generateEntityListAppendName();
	param3->instanceName = templateName3 + NLCprintDefs.generateEntityListAppendName();

	string codeBlockTextTemplateHeader = progLangTemplateHeaderPart1[progLang] + progLangTemplateHeaderClassType[progLang] + templateName1 + progLangTemplateUseClassSeparator[progLang] + progLangTemplateHeaderClassType[progLang] + templateName2 + progLangTemplateUseClassSeparator[progLang] + progLangTemplateHeaderClassType[progLang] + templateName3 + progLangTemplateHeaderPart2[progLang];  //template <class E1, class E2>
	string codeBlockTextFunctionHeader = progLangClassMemberFunctionTypeDefault[progLang] + functionName + progLangOpenParameterSpace[progLang] +  NLCprintDefs.generateCodeEntityDefinitionText(param1, progLang) + progLangParameterSpaceNextParam[progLang] + NLCprintDefs.generateCodeConditionListDefinitionText(param2, param3, progLang) + progLangParameterSpaceNextParam[progLang] + NLCprintDefs.generateCodeClassNameVariableDefinitionText(param2, progLang) + progLangParameterSpaceNextParam[progLang] + NLCprintDefs.generateCodeEntityDefinitionText(param3, progLang) + progLangCloseParameterSpace[progLang];	//e.g. void addCondition(E1* E1Instance, unordered_map<E2*, E3*>* E2E3conditionList, string E2className, E3* E3Instance)

	int q = 0;
	NLCprintDefs.printLine("", level+q, code);
	NLCprintDefs.printLine(codeBlockTextTemplateHeader, level+q, code);
	NLCprintDefs.printLine(codeBlockTextFunctionHeader, level+q, code);
	NLCprintDefs.printLine(progLangOpenBlock[progLang], level+q, code);

	q++;
	string codeBlockTextCreate2 = NLCprintDefs.generateCodeNewEntity(param2, progLang);
	NLCprintDefs.printLine(codeBlockTextCreate2, level+q, code);
	#ifdef NLC_NORMALISE_TWOWAY_PREPOSITIONS_MARK_INVERSE_CONDITIONS
	if(inverseCondition)
	{
		string codeBlockTextSetInverseCondition = NLCprintDefs.generateCodeSetBoolTextTrue(NLCprintDefs.generateCodeEntityInverseConditionText(param2, progLang), progLang);	//param2->inverseConditionTwoWay = true;
		NLCprintDefs.printLine(codeBlockTextSetInverseCondition, level+q, code);
	}
	#endif
	#ifdef NLC_CONDITION_LISTS_VECTOR
	string codeBlockText = NLCprintDefs.generateConditionListName(param2, param3) + progLangObjectReferenceDelimiter2[progLang] + progLangAddCondition[progLang] + progLangOpenParameterSpace[progLang] + NLCprintDefs.generateCodeConditionNewPairText(param2->name, NLCprintDefs.generatePointerTypeText(param2->className, progLang), param2->instanceName, NLCprintDefs.generatePointerTypeText(param3->className, progLang), param3->instanceName, progLang) + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//param2param3ConditionList.push_back(new pair<param2className*, param3className*>(param2, param3));
	#else
	string codeBlockText = NLCprintDefs.generateConditionListName(param2, param3) + progLangObjectReferenceDelimiter2[progLang] + progLangAddCondition[progLang] + progLangOpenParameterSpace[progLang] + NLCprintDefs.generateCodeConditionPairText(param2->name, NLCprintDefs.generatePointerTypeText(param2->className, progLang), param2->instanceName, NLCprintDefs.generatePointerTypeText(param3->className, progLang), param3->instanceName, progLang) + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//param2param3ConditionList.insert(pair<param2className*, param3className*>(param2, param3));
	#endif
	NLCprintDefs.printLine(codeBlockText, level+q, code);

	q--;
	NLCprintDefs.printLine(progLangCloseBlock[progLang], level+q, code);
	#endif
}
#endif

void NLCprintCodeBlocksFunctionsClass::generateCodeRemoveCondition(NLCitem* param1, const NLCitem* param2, const NLCitem* param3, const int progLang, string* code, const int level)
{
	#ifdef NLC_LIBRARY_BASE_EXTENDED
	this->generateCodeRemoveConditionExecuteFunction(param1, param2, param3, progLang, code, level);
	#else
	FINISHTHIS
	//printLine(codeBlockText, level, code);
	#endif
}
void NLCprintCodeBlocksFunctionsClass::generateCodeRemoveConditions(NLCitem* param1, const NLCitem* param2, const NLCitem* param3, const int progLang, string* code, const int level)
{
	#ifdef NLC_LIBRARY_BASE_EXTENDED
	this->generateCodeRemoveConditionsExecuteFunction(param1, param2, param3, progLang, code, level);
	#else
	string codeBlockText = contextParam1 + param1->instanceName + progLangObjectReferenceDelimiter[progLang] + NLCprintDefs.generateConditionListName(param2->className,  param3->className) + progLangObjectReferenceDelimiter2[progLang] + progLangRemoveConditions[progLang] + progLangEndLine[progLang];	//context1->param1->param2param3ConditionList.clear();
	NLCprintDefs.printLine(codeBlockText, level, code);
	#endif
}
#ifdef NLC_LIBRARY_BASE_EXTENDED
void NLCprintCodeBlocksFunctionsClass::generateCodeRemoveConditionExecuteFunction(NLCitem* param1, const NLCitem* param2, const NLCitem* param3, const int progLang, string* code, const int level)
{
	string contextParam1 = NLCprintDefs.generateStringFromContextVector(&(param1->context), progLang);
	string codeBlockTextTemplateDefinition = progLangTemplateUsePart1[progLang] + param1->className + progLangTemplateUseClassSeparator[progLang] + param2->className + progLangTemplateUseClassSeparator[progLang] + param3->className + progLangTemplateUsePart2[progLang]; 	//<param1class, param2class, param3class>
	string codeBlockExecuteFunctionText = "";
	codeBlockExecuteFunctionText = codeBlockExecuteFunctionText + NLC_LIBRARY_BASE_EXTENDED_FUNCTION_NAME_REMOVE_CONDITION + codeBlockTextTemplateDefinition + progLangOpenParameterSpace[progLang] + contextParam1 + param1->instanceName + progLangClassMemberFunctionParametersNext[progLang] + NLCprintDefs.generateCodeListPointer(contextParam1 + param1->instanceName + progLangObjectReferenceDelimiter[progLang] + NLCprintDefs.generateConditionListName(param2->className, param3->className), progLang) + progLangClassMemberFunctionParametersNext[progLang] + progLangStringOpenClose[progLang] + param2->name + progLangStringOpenClose[progLang] + progLangClassMemberFunctionParametersNext[progLang] + param3->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//removeCondition<param1class, param2class, param3class>(context1->param1, &(context1->param1.param2param3ConditionList), "param2", param3);
	NLCprintDefs.printLine(codeBlockExecuteFunctionText, level, code);
}
void NLCprintCodeBlocksFunctionsClass::generateCodeRemoveConditionsExecuteFunction(NLCitem* param1, const NLCitem* param2, const NLCitem* param3, const int progLang, string* code, const int level)
{
	string contextParam1 = NLCprintDefs.generateStringFromContextVector(&(param1->context), progLang);
	string codeBlockTextTemplateDefinition = progLangTemplateUsePart1[progLang] + param1->className + progLangTemplateUseClassSeparator[progLang] + param2->className + progLangTemplateUseClassSeparator[progLang] + param3->className + progLangTemplateUsePart2[progLang]; 	//<param1class, param2class, param3class>
	string codeBlockExecuteFunctionText = "";
	codeBlockExecuteFunctionText = codeBlockExecuteFunctionText + NLC_LIBRARY_BASE_EXTENDED_FUNCTION_NAME_REMOVE_CONDITIONS + codeBlockTextTemplateDefinition + progLangOpenParameterSpace[progLang] + contextParam1 + param1->instanceName + progLangClassMemberFunctionParametersNext[progLang] + NLCprintDefs.generateCodeListPointer(contextParam1 + param1->instanceName + progLangObjectReferenceDelimiter[progLang] + NLCprintDefs.generateConditionListName(param2->className, param3->className), progLang) + progLangClassMemberFunctionParametersNext[progLang] + progLangStringOpenClose[progLang] + param2->name + progLangStringOpenClose[progLang] + progLangClassMemberFunctionParametersNext[progLang] + param3->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//removeConditions<param1class, param2class, param3class>(context1->param1, &(context1->param1.param2param3ConditionList), "param2", param3);
	NLCprintDefs.printLine(codeBlockExecuteFunctionText, level, code);
}
#endif


void NLCprintCodeBlocksFunctionsClass::generateCodeAddActionSubject(const NLCitem* functionArgument, const NLCitem* functionOwnerArgument, const int progLang, string* code, const int level)
{
	#ifdef NLC_LIBRARY_BASE_EXTENDED
	this->generateCodeAddActionSubjectExecuteFunction(functionArgument, functionOwnerArgument, progLang, code, level);
	#else
	string codeBlockTextAddAction = functionOwnerArgument->instanceName + progLangObjectReferenceDelimiter[progLang] + NLCprintDefs.generateActionListName(functionArgument->className) + progLangObjectReferenceDelimiter2[progLang] + progLangAddEntityToList[progLang] + progLangOpenParameterSpace[progLang] + functionArgument->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//actionSubject1->actionClassActionList.push_back(action1);
	NLCprintDefs.printLine(codeBlockTextAddAction, level, code);
	string codeBlockTextAddAction2 = functionArgument->instanceName + progLangObjectReferenceDelimiter[progLang] + NLCprintDefs.generateActionSubjectListName(functionOwnerArgument->className) + progLangObjectReferenceDelimiter2[progLang] + progLangAddEntityToList[progLang] + progLangOpenParameterSpace[progLang] + functionOwnerArgument->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//action1->actionSubjectClassActionSubjectList.push_back(actionSubject1);
	NLCprintDefs.printLine(codeBlockTextAddAction2, level, code);
	#endif
}
#ifdef NLC_LIBRARY_BASE_EXTENDED
void NLCprintCodeBlocksFunctionsClass::generateCodeAddActionSubjectExecuteFunction(const NLCitem* functionArgument, const NLCitem* functionOwnerArgument, const int progLang, string* code, const int level)
{
	string codeBlockTextTemplateDefinition = progLangTemplateUsePart1[progLang] + functionArgument->className + progLangTemplateUseClassSeparator[progLang] + functionOwnerArgument->className + progLangTemplateUsePart2[progLang]; 	//<param1class, param2class>
	string codeBlockExecuteFunctionText = "";
	codeBlockExecuteFunctionText = codeBlockExecuteFunctionText + NLC_LIBRARY_BASE_EXTENDED_FUNCTION_NAME_ADD_ACTIONSUBJECT + codeBlockTextTemplateDefinition + progLangOpenParameterSpace[progLang] + functionArgument->instanceName + progLangClassMemberFunctionParametersNext[progLang] + functionOwnerArgument->instanceName + progLangClassMemberFunctionParametersNext[progLang] + NLCprintDefs.generateCodeListPointer(functionOwnerArgument->instanceName + progLangObjectReferenceDelimiter[progLang] + NLCprintDefs.generateActionListName(functionArgument->className), progLang) + progLangClassMemberFunctionParametersNext[progLang] + NLCprintDefs.generateCodeListPointer(functionArgument->instanceName + progLangObjectReferenceDelimiter[progLang] + NLCprintDefs.generateActionSubjectListName(functionOwnerArgument->className), progLang) + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//addActionSubject<param1class, param2class>(functionArgument, functionOwnerArgument, &(functionOwnerArgument->actionClassActionList), &(functionArgument->actionSubjectClassActionSubjectList));
	NLCprintDefs.printLine(codeBlockExecuteFunctionText, level, code);
}
#endif

void NLCprintCodeBlocksFunctionsClass::generateCodeAddActionObject(const NLCitem* functionArgument, const NLCitem* functionObjectArgument, const int progLang, string* code, const int level)
{
	#ifdef NLC_LIBRARY_BASE_EXTENDED
	this->generateCodeAddActionObjectExecuteFunction(functionArgument, functionObjectArgument, progLang, code, level);
	#else
	string codeBlockTextAddAction = functionObjectArgument->instanceName + progLangObjectReferenceDelimiter[progLang] + NLCprintDefs.generateActionIncomingListName(functionArgument->className) + progLangObjectReferenceDelimiter2[progLang] + progLangAddEntityToList[progLang] + progLangOpenParameterSpace[progLang] + functionArgument->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//actionObject1->actionClassActionIncomingList.push_back(action1);
	NLCprintDefs.printLine(codeBlockTextAddAction, level, code);
	string codeBlockTextAddAction2 = functionArgument->instanceName + progLangObjectReferenceDelimiter[progLang] + NLCprintDefs.generateActionObjectListName(functionObjectArgument->className) + progLangObjectReferenceDelimiter2[progLang] + progLangAddEntityToList[progLang] + progLangOpenParameterSpace[progLang] + functionObjectArgument->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//action1->actionObjectClassActionObjectList.push_back(actionSubject1);
	NLCprintDefs.printLine(codeBlockTextAddAction2, level, code);
	#endif
}
#ifdef NLC_LIBRARY_BASE_EXTENDED
void NLCprintCodeBlocksFunctionsClass::generateCodeAddActionObjectExecuteFunction(const NLCitem* functionArgument, const NLCitem* functionObjectArgument, const int progLang, string* code, const int level)
{
	string codeBlockTextTemplateDefinition = progLangTemplateUsePart1[progLang] + functionArgument->className + progLangTemplateUseClassSeparator[progLang] + functionObjectArgument->className + progLangTemplateUsePart2[progLang]; 	//<param1class, param2class>
	string codeBlockExecuteFunctionText = "";
	codeBlockExecuteFunctionText = codeBlockExecuteFunctionText + NLC_LIBRARY_BASE_EXTENDED_FUNCTION_NAME_ADD_ACTIONOBJECT + codeBlockTextTemplateDefinition + progLangOpenParameterSpace[progLang] + functionArgument->instanceName + progLangClassMemberFunctionParametersNext[progLang] + functionObjectArgument->instanceName + progLangClassMemberFunctionParametersNext[progLang] + NLCprintDefs.generateCodeListPointer(functionObjectArgument->instanceName + progLangObjectReferenceDelimiter[progLang] + NLCprintDefs.generateActionIncomingListName(functionArgument->className), progLang) + progLangClassMemberFunctionParametersNext[progLang] + NLCprintDefs.generateCodeListPointer(functionArgument->instanceName + progLangObjectReferenceDelimiter[progLang] + NLCprintDefs.generateActionObjectListName(functionObjectArgument->className), progLang) + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//addActionObject<param1class, param2class>(functionArgument, functionObjectArgument, &(functionObjectArgument->generateActionIncomingListName), &(functionArgument->actionObjectClassActionObjectList));
	NLCprintDefs.printLine(codeBlockExecuteFunctionText, level, code);
}
#endif



void NLCprintCodeBlocksFunctionsClass::generateCodeAddNewEntityToLocalList(const NLCitem* param1, const int progLang, string* code, const int level)
{
	#ifdef NLC_LIBRARY_BASE_EXTENDED
	this->generateCodeAddNewEntityToLocalListExecuteFunction(param1, progLang, code, level);
	#else
	string codeBlockTextCreate = NLCprintDefs.generateCodeNewEntity(param1, progLang);		//const param1className* param1 = new param1className();
	NLCprintDefs.printLine(codeBlockTextCreate, level, code);
	string codeBlockText = NLCprintDefs.generateLocalListName(param1) + progLangObjectReferenceDelimiter2[progLang] + progLangAddEntityToList[progLang] + progLangOpenParameterSpace[progLang] + param1->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//param1instanceList.push_back(param1);
	NLCprintDefs.printLine(codeBlockText, level, code);
	#endif
}
#ifdef NLC_LIBRARY_BASE_EXTENDED
void NLCprintCodeBlocksFunctionsClass::generateCodeAddNewEntityToLocalListExecuteFunction(const NLCitem* param1, const int progLang, string* code, const int level)
{
	string codeBlockTextTemplateDefinition = progLangTemplateUsePart1[progLang] + param1->className + progLangTemplateUsePart2[progLang]; 	//<param1class>
	string codeBlockExecuteFunctionText = "";
	codeBlockExecuteFunctionText = NLCprintDefs.generateCodeEntityDefinitionText(param1, progLang) + progLangEquals[progLang] + codeBlockExecuteFunctionText + NLC_LIBRARY_BASE_EXTENDED_FUNCTION_NAME_ADD_NEW_ENTITY_TO_LOCAL_LIST + codeBlockTextTemplateDefinition + progLangOpenParameterSpace[progLang] + NLCprintDefs.generateCodeListPointer(NLCprintDefs.generateLocalListName(param1), progLang) + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//const param1class* param1 = addNewEntityToLocalList<param1class>(&(param1localList));
	NLCprintDefs.printLine(codeBlockExecuteFunctionText, level, code);
}
#endif

void NLCprintCodeBlocksFunctionsClass::generateCodeAddEntityToLocalList(const NLCitem* param1, const NLCitem* param2, const int progLang, string* code, const int level)
{
	#ifdef NLC_LIBRARY_BASE_EXTENDED
	this->generateCodeAddEntityToLocalListExecuteFunction(param1, param2, progLang, code, level);
	#else
	string codeBlockText = NLCprintDefs.generateLocalListName(param1) + progLangObjectReferenceDelimiter2[progLang] + progLangAddEntityToList[progLang] + progLangOpenParameterSpace[progLang] + param2->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//param1instanceList.push_back(param2);
	NLCprintDefs.printLine(codeBlockText, level, code);
	#endif
}
#ifdef NLC_LIBRARY_BASE_EXTENDED
void NLCprintCodeBlocksFunctionsClass::generateCodeAddEntityToLocalListExecuteFunction(const NLCitem* param1, const NLCitem* param2, const int progLang, string* code, const int level)
{
	string codeBlockTextTemplateDefinition = progLangTemplateUsePart1[progLang] + param1->className + progLangTemplateUsePart2[progLang]; 	//<param1class>
	string codeBlockExecuteFunctionText = "";
	codeBlockExecuteFunctionText = codeBlockExecuteFunctionText + NLC_LIBRARY_BASE_EXTENDED_FUNCTION_NAME_ADD_ENTITY_TO_LOCAL_LIST + codeBlockTextTemplateDefinition + progLangOpenParameterSpace[progLang] + NLCprintDefs.generateCodeListPointer(NLCprintDefs.generateLocalListName(param1), progLang) + progLangClassMemberFunctionParametersNext[progLang] + param2->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//addEntityToLocalList<param1class>(&(param1localList), param2);
	NLCprintDefs.printLine(codeBlockExecuteFunctionText, level, code);
}
#endif

void NLCprintCodeBlocksFunctionsClass::generateCodeForPropertyList(const NLCitem* param1, const string contextParam1, const int progLang, string* code, const int level)
{
	string entityClassName = param1->className;
	string entityListName = contextParam1 + NLCprintDefs.generatePropertyListName(param1);
	string entityInstanceName = NLCprintDefs.generateEntityName(param1);
	this->generateCodeForEntityList(entityClassName, entityListName, entityInstanceName, progLang, code, level);
}

void NLCprintCodeBlocksFunctionsClass::generateCodeForLocalList(const NLCitem* param1, const int progLang, string* code, const int level)
{
	string entityClassName = param1->className;
	string entityListName = NLCprintDefs.generateLocalListName(param1);
	string entityInstanceName = NLCprintDefs.generateEntityName(param1);
	this->generateCodeForEntityList(entityClassName, entityListName, entityInstanceName, progLang, code, level);
}

void NLCprintCodeBlocksFunctionsClass::generateCodeForEntityList(const string entityClassName, const string entityListName, const string entityInstanceName, const int progLang, string* code, const int level)
{
	string iterIndexString = SHAREDvars.convertIntToString(level);
	string codeBlockText = progLangFor[progLang] + progLangForIterPart1[progLang] + NLCprintDefs.generateCodeEntityListDefinitionTypeTextCompact(entityClassName, progLang) + progLangForIterPart2a[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart2c[progLang] + entityListName + progLangForIterPart3a[progLang] + progLangForIterPart3b[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart3c[progLang] + entityListName + progLangForIterPart4a[progLang] + progLangForIterPart4b[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart4c[progLang];	//for()
	NLCprintDefs.printLine(codeBlockText, level, code);
	NLCprintDefs.printLine(progLangOpenBlock[progLang], level, code);
	string tempVarDeclarationText = NLCprintDefs.generateCodeEntityDefinitionText(entityClassName, entityInstanceName, progLang) + progLangEquals[progLang] + NLCprintDefs.generateCodeIterReference(iterIndexString, progLang) + progLangEndLine[progLang];
	NLCprintDefs.printLine(tempVarDeclarationText, (level+1), code);
}

void NLCprintCodeBlocksFunctionsClass::generateCodeForConditionList(const NLCitem* param1, const NLCitem* param2, const string contextParam1, const int progLang, string* code, const int level)
{
	string entityListName = contextParam1 + NLCprintDefs.generateConditionListName(param1->className, param2->className);
	string entityInstanceName1 = NLCprintDefs.generateEntityName(param1);
	string entityInstanceName2 = NLCprintDefs.generateEntityName(param2);
	this->generateCodeForConditionList(param1->className, param2->className, entityListName, entityInstanceName1, entityInstanceName2, progLang, code, level);
}

void NLCprintCodeBlocksFunctionsClass::generateCodeForConditionList(const string entityClassName1, const string entityClassName2, const string entityListName, const string entityInstanceName1, const string entityInstanceName2, const int progLang, string* code, const int level)
{
	string iterIndexString = SHAREDvars.convertIntToString(level);
	string codeBlockText = progLangFor[progLang] + progLangForIterPart1[progLang] + NLCprintDefs.generateCodeConditionListDefinitionTypeTextCompact(entityClassName1, entityClassName2, progLang) + progLangForIterPart2a[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart2c[progLang] + entityListName + progLangForIterPart3a[progLang] + progLangForIterPart3b[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart3cMap[progLang] + entityListName + progLangForIterPart4a[progLang] + progLangForIterPart4b[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart4c[progLang];	//for()
	NLCprintDefs.printLine(codeBlockText, level, code);
	NLCprintDefs.printLine(progLangOpenBlock[progLang], level, code);
	#ifdef NLC_NONOO
	string tempVarDeclarationText = NLCprintDefs.generateCodeEntityDefinitionText(entityClassName1, entityInstanceName1, progLang) + progLangEquals[progLang] + NLCprintDefs.generateCodeIterReference(iterIndexString, progLang) + progLangEndLine[progLang];
	NLCprintDefs.printLine(tempVarDeclarationText, (level+1), code);
	string tempVarDeclarationText2 = NLCprintDefs.generateCodeEntityDefinitionText(entityClassName2, entityInstanceName2, progLang) + progLangEquals[progLang] + progLangOpenParameterSpace[progLang] + NLCprintDefs.generateCodeIterReference(iterIndexString, progLang) + progLangCloseParameterSpace[progLang] + progLangObjectReferenceDelimiter[progLang] + NLCprintDefs.generateGIAconditionObjectListName() + progLangEndLine[progLang];
	NLCprintDefs.printLine(tempVarDeclarationText2, (level+1), code);
	#else
	string tempVarDeclarationText = NLCprintDefs.generateCodeEntityDefinitionText(entityClassName2, entityInstanceName2, progLang) + progLangEquals[progLang] + NLCprintDefs.generateCodeIterReferenceConditionObject(iterIndexString, progLang) + progLangEndLine[progLang];
	NLCprintDefs.printLine(tempVarDeclarationText, (level+1), code);
	#endif
}

#ifdef NLC_TRANSLATOR_TEST_DEFINITE_ENTITY_EXISTENCE_SUBJECT_OBJECT
void NLCprintCodeBlocksFunctionsClass::generateCodeVerifyDefiniteReferenceExistenceNewFunction(const int progLang, string* code, const int level)
{
	string entityToVerifyName = NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE;
	string emptyName = NLC_TRANSLATOR_TEST_DEFINITE_ENTITY_EXISTENCE_FUNCTION_PARAMETER_EMPTY_NAME;

	string codeBlockTextFunctionHeader = progLangClassMemberFunctionTypeDefault[progLang] + NLC_TRANSLATOR_TEST_DEFINITE_ENTITY_EXISTENCE_FUNCTION_NAME + progLangOpenParameterSpace[progLang] + progLangFunctionParameterBooleanType[progLang] + emptyName + progLangClassMemberFunctionParametersNext[progLang] + progLangFunctionParameterStringType[progLang] + entityToVerifyName + progLangClassMemberFunctionParametersNext[progLang] + progLangFunctionParameterStringType[progLang] + NLC_TRANSLATOR_TEST_DEFINITE_ENTITY_EXISTENCE_FUNCTION_PARAMETER_GENERIC_LIST_APPEND_NAME + progLangCloseParameterSpace[progLang];	//void verifyDefiniteReferenceExistence(bool empty, string entityName, string genericListAppendName)

	NLCprintDefs.printLine("", level, code);
	NLCprintDefs.printLine(codeBlockTextFunctionHeader, level, code);
	NLCprintDefs.printLine(progLangOpenBlock[progLang], level, code);
		string text = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + emptyName + progLangCloseParameterSpace[progLang];		//if(empty){
		NLCprintDefs.printLine(text, (level+1), code);
			
			string warningMessageName = "warningMessage";
			text = progLangFunctionParameterStringType[progLang] + warningMessageName + progLangEquals[progLang] + NLC_RUNTIME_ERROR_PREPEND + progLangStringAdd[progLang] + NLC_TRANSLATOR_TEST_DEFINITE_ENTITY_EXISTENCE_FUNCTION_PARAMETER_GENERIC_LIST_APPEND_NAME + progLangStringAdd[progLang] + NLC_TRANSLATOR_TEST_DEFINITE_ENTITY_EXISTENCE_WARNING_TEXT_APPEND + progLangStringAdd[progLang] + entityToVerifyName + progLangEndLine[progLang];	//string warningMessage = "NLC runtime error: " + genericListAppendName + "definite entity not found (ensure to initialise all entities before referencing them):" + entityName;
			NLCprintDefs.printLine(text, (level+2), code);
			text = progLangPrintTextOpen[progLang] + warningMessageName + progLangPrintTextClose[progLang] + progLangEndLine[progLang];		
			NLCprintDefs.printLine(text, (level+2), code);

		NLCprintDefs.printLine(progLangCloseBlock[progLang], level+1, code);
	NLCprintDefs.printLine(progLangCloseBlock[progLang], level, code);
}

void NLCprintCodeBlocksFunctionsClass::generateCodeVerifyDefiniteReferenceExistenceExecuteFunction(const NLCitem* param1, const NLCitem* param2, const int progLang, string* code, const int level)
{
	string entityToVerifyName = NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE;
	string genericListAppendName = param2->name;
	string testEmptyText = NLCprintDefs.generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangObjectReferenceDelimiter2[progLang] + progLangHasEntity[progLang];		//param1CategoryList.empty()

	string codeBlockText = "";
	codeBlockText = codeBlockText + NLC_TRANSLATOR_TEST_DEFINITE_ENTITY_EXISTENCE_FUNCTION_NAME + progLangOpenParameterSpace[progLang] + testEmptyText + progLangClassMemberFunctionParametersNext[progLang] + progLangStringOpenClose[progLang] + param1->className + progLangStringOpenClose[progLang] + progLangClassMemberFunctionParametersNext[progLang] + progLangStringOpenClose[progLang] + param2->name + progLangStringOpenClose[progLang] + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//verifyDefiniteReferenceExistenceExecuteFunction(entityCategoryList.empty(), "entityName", genericListAppendName);
	NLCprintDefs.printLine(codeBlockText, level, code);
}

#endif

#ifdef NLC_ADVANCED_REFERENCING_SUPPORT_ALIASES_MERGERS
void NLCprintCodeBlocksFunctionsClass::findAndRemoveEntityFromLocalListExecuteFunction(const NLCitem* param1, const int progLang, string* code, const int level)
{
	string codeBlockExecuteFunctionText = string("") + REMOVE_ENTITY_FROM_LOCAL_LIST_FUNCTION_NAME + progLangOpenParameterSpace[progLang] + NLCprintDefs.generateLocalListName(param1) + progLangClassMemberFunctionParametersNext[progLang] + NLCprintDefs.generateInstanceName(param1) + progLangCloseParameterSpace[progLang];	//findAndRemoveEntityFromLocalList(param1instanceList, param1instance);
	NLCprintDefs.printLine(codeBlockExecuteFunctionText, level, code);
}
void NLCprintCodeBlocksFunctionsClass::findAndReplaceEntityInLocalListExecuteFunction(const NLCitem* param1, const NLCitem* param2, const int progLang, string* code, const int level)
{
	string codeBlockExecuteFunctionText = string("") + REPLACE_ENTITY_IN_LOCAL_LIST_FUNCTION_NAME + progLangOpenParameterSpace[progLang] + NLCprintDefs.generateLocalListName(param1) + progLangClassMemberFunctionParametersNext[progLang] + NLCprintDefs.generateInstanceName(param1) + progLangClassMemberFunctionParametersNext[progLang] + NLCprintDefs.generateInstanceName(param2) + progLangCloseParameterSpace[progLang];	//findAndReplaceEntityInLocalList(param1instanceList, param1instance, param2instance);
	NLCprintDefs.printLine(codeBlockExecuteFunctionText, level, code);
}
void NLCprintCodeBlocksFunctionsClass::mergeEntity1AttributesIntoEntity2ExecuteFunction(const NLCitem* param1, const NLCitem* param2, const int progLang, string* code, const int level)
{
	string codeBlockExecuteFunctionText = string("") + MERGE_ENTITY1_ATTRIBUTES_INTO_ENTITY2_FUNCTION_NAME + progLangOpenParameterSpace[progLang] + NLCprintDefs.generateInstanceName(param1) + progLangClassMemberFunctionParametersNext[progLang] + NLCprintDefs.generateInstanceName(param2) + progLangCloseParameterSpace[progLang];	//mergeEntity1AttributesIntoEntity2(param1instance, param2instance);
	NLCprintDefs.printLine(codeBlockExecuteFunctionText, level, code);
}
#endif


