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
 * File Name: NLCprintCodeBlocksFunctions.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2015 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 1q2c 18-August-2015
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/


#include "NLCprintCodeBlocksFunctions.h"
#include "NLCprintDefs.h"

#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN
#ifdef NLC_USE_ADVANCED_REFERENCING
void generateCodeAddToCategoryIfPassSingularDefiniteReferencingTestsNewFunction(int progLang, string* code, int level)
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

	string codeBlockTextFunctionHeader = progLangClassMemberFunctionTypeDefault[progLang] + NLC_USE_ADVANCED_REFERENCING_SINGULAR_DEFINITE_REFERENCING_TESTS_FUNCTION_NAME + progLangOpenParameterSpace[progLang] + generateCodeEntityListDefinitionTypeTextReference(templateName1, progLang) + generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangClassMemberFunctionParametersNext[progLang] + templateName2 + progLangPointer[progLang] + STRING_SPACE + param2->instanceName + progLangCloseParameterSpace[progLang];	//void addToCategoryIfPassSingularDefinitePluralityTests(vector<E1*>& param1CategoryList, E2* param2instanceName)

	string codeBlockText6 = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + negativeModifierString + progLangOpenParameterSpace[progLang] + param2->instanceName + progLangObjectReferenceDelimiter[progLang] + NLC_USE_ADVANCED_REFERENCING_LAST_SENTENCE_REFERENCED_VARIABLE_NAME + progLangObjectReferenceDelimiter2[progLang] + progLangHasEntity[progLang] + progLangCloseParameterSpace[progLang] + progLangCloseParameterSpace[progLang];		//if(!(param2->lastSentenceReferenced.empty())){

	string codeBlockText4 = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangObjectReferenceDelimiter2[progLang] + progLangHasEntity[progLang] + progLangCloseParameterSpace[progLang];		//if(param1CategoryList.empty()){
		//NB this code could be generated using existing codeblock (NLC_CODEBLOCK_TYPE_IF_HAS_GENERIC_ENTITY)
	string codeBlockText5 = progLangElse[progLang];

	#ifdef NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT
	string codeBlockText1 = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + param2->instanceName + progLangObjectReferenceDelimiter[progLang] + NLC_USE_ADVANCED_REFERENCING_LAST_SENTENCE_REFERENCED_VARIABLE_NAME + progLangObjectReferenceDelimiter2[progLang] + progLangStackGetLast[progLang] + progLangGreaterThan[progLang] + progLangOpenParameterSpace[progLang] + generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangObjectReferenceDelimiter2[progLang] + progLangGetLast[progLang] + progLangCloseParameterSpace[progLang] + progLangObjectReferenceDelimiter[progLang] + NLC_USE_ADVANCED_REFERENCING_LAST_SENTENCE_REFERENCED_VARIABLE_NAME + progLangObjectReferenceDelimiter2[progLang] + progLangStackGetLast[progLang] + progLangCloseParameterSpace[progLang];		//if(param2->lastSentenceReferenced.top() > param1CategoryList.back()->lastSentenceReferenced.top())
	string codeBlockText2 = progLangElseIf[progLang] + progLangOpenParameterSpace[progLang] + param2->instanceName + progLangObjectReferenceDelimiter[progLang] + NLC_USE_ADVANCED_REFERENCING_LAST_SENTENCE_REFERENCED_VARIABLE_NAME + progLangObjectReferenceDelimiter2[progLang] + progLangStackGetLast[progLang] + progLangEqualsTest[progLang] + progLangOpenParameterSpace[progLang] + generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangObjectReferenceDelimiter2[progLang] + progLangGetLast[progLang] + progLangCloseParameterSpace[progLang] + progLangObjectReferenceDelimiter[progLang] + NLC_USE_ADVANCED_REFERENCING_LAST_SENTENCE_REFERENCED_VARIABLE_NAME + progLangObjectReferenceDelimiter2[progLang] + progLangStackGetLast[progLang] + progLangCloseParameterSpace[progLang];		//if(param2->lastSentenceReferenced.top() == param1CategoryList.back()->lastSentenceReferenced.top())
	#else
	string codeBlockText1 = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + param2->instanceName + progLangObjectReferenceDelimiter[progLang] + NLC_USE_ADVANCED_REFERENCING_LAST_SENTENCE_REFERENCED_VARIABLE_NAME + progLangGreaterThan[progLang] + progLangOpenParameterSpace[progLang] + generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangObjectReferenceDelimiter2[progLang] + progLangGetLast[progLang] + progLangCloseParameterSpace[progLang] + progLangObjectReferenceDelimiter[progLang] + NLC_USE_ADVANCED_REFERENCING_LAST_SENTENCE_REFERENCED_VARIABLE_NAME + progLangCloseParameterSpace[progLang];		//if(param2->lastSentenceReferenced > param1CategoryList.back()->lastSentenceReferenced)
	string codeBlockText2 = progLangElseIf[progLang] + progLangOpenParameterSpace[progLang] + param2->instanceName + progLangObjectReferenceDelimiter[progLang] + NLC_USE_ADVANCED_REFERENCING_LAST_SENTENCE_REFERENCED_VARIABLE_NAME + progLangEqualsTest[progLang] + progLangOpenParameterSpace[progLang] + generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangObjectReferenceDelimiter2[progLang] + progLangGetLast[progLang] + progLangCloseParameterSpace[progLang] + progLangObjectReferenceDelimiter[progLang] + NLC_USE_ADVANCED_REFERENCING_LAST_SENTENCE_REFERENCED_VARIABLE_NAME + progLangCloseParameterSpace[progLang];		//if(param2->lastSentenceReferenced == param1CategoryList.back()->lastSentenceReferenced)			
	#endif
	string codeBlockText3 = progLangElse[progLang];

	string removeCategoryListItemsText = generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangObjectReferenceDelimiter2[progLang] + progLangRemoveProperties[progLang] + progLangEndLine[progLang];		//param1CategoryList.clear();
		//NB this code could be moved to a new codeblock (NLC_CODEBLOCK_TYPE_REMOVE_PROPERTIES_GENERIC_LIST)

	string addCategoryItemText = generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangObjectReferenceDelimiter2[progLang] + progLangAddEntityToList[progLang] + progLangOpenParameterSpace[progLang] + param2->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//param1CategoryList.push_back(param2);
		//NB this code could be generated using existing codeblock (NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST)

	#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN_DO_NOT_ADD_DUPLICATES
	string negativeModifierStringFind = progLangNot[progLang];	//if not found (negative find)
	string findCategoryItemText = progLangFindPart1[progLang] + negativeModifierStringFind + progLangFindPart2[progLang] + generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangFindPart3[progLang] + generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangFindPart4[progLang] + param2->instanceName + progLangFindPart5[progLang] + generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangFindPart6[progLang];	//if(!find(param1CategoryList.begin(), param1CategoryList.end(), param2) != param1CategoryList.end()) 
		//NB this code could be moved to a new codeblock  (NLC_CODEBLOCK_TYPE_FIND_PROPERTY_IN_GENERIC_LIST)
	#endif

	int q = 0;
	printLine("", level, code);
	printLine(codeBlockTextTemplateHeader, level, code);
	printLine(codeBlockTextFunctionHeader, level, code);
	printLine(progLangOpenBlock[progLang], level, code);
	#ifdef NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT
	q++;
		printLine(codeBlockText6, level+q, code);
		printLine(progLangOpenBlock[progLang], level+q, code);
		#endif		
		q++;
			printLine(codeBlockText4, level+q, code);
			printLine(progLangOpenBlock[progLang], level+q, code);
			printLine(addCategoryItemText, level+q+1, code);
			printLine(progLangCloseBlock[progLang], level+q, code);
			printLine(codeBlockText5, level+q, code);
			printLine(progLangOpenBlock[progLang], level+q, code);
			q++;
				printLine(codeBlockText1, level+q, code);
				printLine(progLangOpenBlock[progLang], level+q, code);
				printLine(removeCategoryListItemsText, level+q+1, code);
				printLine(addCategoryItemText, level+q+1, code);
				printLine(progLangCloseBlock[progLang], level+q, code);

				printLine(codeBlockText2, level+q, code);
				printLine(progLangOpenBlock[progLang], level+q, code);
				#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN_DO_NOT_ADD_DUPLICATES
				printLine(findCategoryItemText, level+q+1, code);
				printLine(progLangOpenBlock[progLang], level+q+1, code);
				printLine(addCategoryItemText, level+q+2, code);
				printLine(progLangCloseBlock[progLang], level+q+1, code);
				#else
				printLine(addCategoryItemText, level+q+1, code);
				#endif
				printLine(progLangCloseBlock[progLang], level+q, code);

				printLine(codeBlockText3, level+q, code);
				printLine(progLangOpenBlock[progLang], level+q, code);
				printLine(progLangCloseBlock[progLang], level+q, code);		
			q--;
			printLine(progLangCloseBlock[progLang], level+q, code);

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

		#ifdef NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT
		q--;							
		printLine(progLangCloseBlock[progLang], level+q, code);
		#endif	

		#ifdef NLC_CATEGORIES_TEST_PLURALITY_WARNING
		#ifdef NLC_CATEGORIES_TEST_PLURALITY_WARNING_PLACE_IN_NLC_PREDEFINED_FUNCTION_ADDTOCATEGORYIFPASSSINGULARDEFINITEREFERENCINGTESTS
		#ifdef NLC_CATEGORIES_TEST_PLURALITY_COMMENT
		string comment = "Singular definite plurality tests";
		string codeBlockText7 = progLangOpenSingleLineComment[progLang] + comment;
		printLine(codeBlockText7, level+q, code);
			//NB this code could be moved to a new codeblock (NLC_CODEBLOCK_TYPE_COMMENT_SINGLE_LINE)
		#endif
		int value = 1;	//see generateContextBlocksCategories
		string intValueString = convertIntToString(value);
		string codeBlockText8 = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangObjectReferenceDelimiter2[progLang] + progLangSizeOfList[progLang] + progLangGreaterThan[progLang] + intValueString + progLangCloseParameterSpace[progLang];		//if(param1CategoryList.size() > 1){
		printLine(codeBlockText8, level+q, code);
		printLine(progLangOpenBlock[progLang], level+q, code);
			//NB this code could be moved to a new codeblock (NLC_CODEBLOCK_TYPE_IF_HAS_GREATER_THAN_NUM_GENERIC_ENTITY)
		string codeBlockText9 = progLangPrintTextOpen[progLang] + NLC_CATEGORIES_TEST_PLURALITY_WARNING_MESSAGE + progLangPrintTextClose[progLang]  + progLangEndLine[progLang];	//cout << "Execution warning: multiple objects have been added to a singular definite variable (category) - should the entity have been defined as plural instead?" << endl;
		printLine(codeBlockText9, level+q+1, code);
			//NB this code could be moved to a new codeblock (NLC_CODEBLOCK_TYPE_PRINT_WARNING)
		printLine(progLangCloseBlock[progLang], level+q, code);
		#endif
		#endif

	q--;							
	printLine(progLangCloseBlock[progLang], level+q, code);		
	
	delete param1;
	delete param2;
}

void generateCodeAddToCategoryIfPassSingularDefiniteReferencingTestsExecuteFunction(NLCitem* param1, NLCitem* param2, NLCitem* param3, int progLang, string* code, int level)
{
	string genericListAppendName = param3->name;

	string codeBlockText = "";
	#ifdef NLC_NONOO
	string codeBlockTextTemplateDefinition = "";
	#else
	string codeBlockTextTemplateDefinition = progLangTemplateUsePart1[progLang] + param1->className + progLangTemplateUseClassSeparator[progLang] + param2->className + progLangTemplateUsePart2[progLang] + STRING_SPACE; 	//<param1class, param2class> 
	#endif
	codeBlockText = codeBlockText + NLC_USE_ADVANCED_REFERENCING_SINGULAR_DEFINITE_REFERENCING_TESTS_FUNCTION_NAME + codeBlockTextTemplateDefinition + progLangOpenParameterSpace[progLang] + generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangClassMemberFunctionParametersNext[progLang] + param2->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//addToCategoryIfPassSingularDefinitePluralityTests<param1class, param2class> (param1CategoryList, param2instanceName);				
	printLine(codeBlockText, level, code);
}
#endif
#endif

#ifdef NLC_PERFORM_PLURAL_DEFINITE_REFERENCING_TESTS
void generateCodeAddToCategoryIfPassPluralDefiniteReferencingTestsNewFunction(int progLang, string* code, int level)
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
	string codeBlockTextFunctionHeader = progLangClassMemberFunctionTypeDefault[progLang] + NLC_USE_ADVANCED_REFERENCING_PLURAL_DEFINITE_REFERENCING_TESTS_FUNCTION_NAME + progLangOpenParameterSpace[progLang] + generateCodeEntityListDefinitionTypeTextReference(templateName1, progLang) + generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangClassMemberFunctionParametersNext[progLang] + templateName2 + progLangPointer[progLang] + STRING_SPACE + param2->instanceName + progLangCloseParameterSpace[progLang];	//void addToCategoryIfPassPluralDefiniteReferencingTests(vector<E1*>& param1CategoryList, E2* param2instanceName)

	//string codeBlockText6 = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + negativeModifierString + progLangOpenParameterSpace[progLang] + param2->instanceName + progLangObjectReferenceDelimiter[progLang] + NLC_USE_ADVANCED_REFERENCING_LAST_SENTENCE_REFERENCED_VARIABLE_NAME + progLangObjectReferenceDelimiter2[progLang] + progLangHasEntity[progLang] + progLangCloseParameterSpace[progLang] + progLangCloseParameterSpace[progLang];		//if(!(param2->lastSentenceReferenced.empty())){

	string addCategoryItemText = generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangObjectReferenceDelimiter2[progLang] + progLangAddEntityToList[progLang] + progLangOpenParameterSpace[progLang] + param2->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//param1CategoryList.push_back(param2);
		//NB this code could be generated using existing codeblock (NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST)

	#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN_DO_NOT_ADD_DUPLICATES
	string negativeModifierStringFind = progLangNot[progLang];	//if not found (negative find)
	string findCategoryItemText = progLangFindPart1[progLang] + negativeModifierStringFind + progLangFindPart2[progLang] + generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangFindPart3[progLang] + generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangFindPart4[progLang] + param2->instanceName + progLangFindPart5[progLang] + generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangFindPart6[progLang];	//if(!find(param1CategoryList.begin(), param1CategoryList.end(), param2) != param1CategoryList.end()) 
		//NB this code could be moved to a new codeblock  (NLC_CODEBLOCK_TYPE_FIND_PROPERTY_IN_GENERIC_LIST)
	#endif

	int q = 0;
	printLine("", level+q, code);
	printLine(codeBlockTextTemplateHeader, level+q, code);
	printLine(codeBlockTextFunctionHeader, level+q, code);
	printLine(progLangOpenBlock[progLang], level+q, code);

		/*
		#ifdef NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT
		q++;
		printLine(codeBlockText6, level+q, code);
		printLine(progLangOpenBlock[progLang], level+q, code);
		#endif
		*/
		q++;		
			#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN_DO_NOT_ADD_DUPLICATES
			printLine(findCategoryItemText, level+q, code);
			printLine(progLangOpenBlock[progLang], level+q, code);
			printLine(addCategoryItemText, level+q+1, code);
			printLine(progLangCloseBlock[progLang], level+q, code);
			#else
			printLine(addCategoryItemText, level+q, code);
			#endif	

			/*
			if(!find(param1CategoryList.begin(), param1CategoryList.end(), param2) != param1CategoryList.end()) 
			{
				param1CategoryList.push_back(param2);
			}
			*/

		/*
		#ifdef NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT
		q--;							
		printLine(progLangCloseBlock[progLang], level+q, code);	
		#endif
		*/

		q--;
	printLine(progLangCloseBlock[progLang], level+q, code);	
	
	delete param1;
	delete param2;
}

void generateCodeAddToCategoryIfPassPluralDefiniteReferencingTestsExecuteFunction(NLCitem* param1, NLCitem* param2, NLCitem* param3, int progLang, string* code, int level)
{
	string genericListAppendName = param3->name;

	string codeBlockText = "";
	#ifdef NLC_NONOO
	string codeBlockTextTemplateDefinition = "";
	#else
	string codeBlockTextTemplateDefinition = progLangTemplateUsePart1[progLang] + param1->className + progLangTemplateUseClassSeparator[progLang] + param2->className + progLangTemplateUsePart2[progLang] + STRING_SPACE; 	////<param1class, param2class> 
	#endif
	codeBlockText = codeBlockText + NLC_USE_ADVANCED_REFERENCING_PLURAL_DEFINITE_REFERENCING_TESTS_FUNCTION_NAME + codeBlockTextTemplateDefinition + progLangOpenParameterSpace[progLang] + generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangClassMemberFunctionParametersNext[progLang] + param2->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//addToCategoryIfPassPluralDefiniteReferencingTests<param1class, param2class> (param1CategoryList, param2instanceName);				
	printLine(codeBlockText, level, code);
}
#endif


#ifdef NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT
void generateCodeAddEntityToReferenceContextListNewFunction(int progLang, string* code, int level)
{
	string genericEntityClassName = generateClassName(NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE);
	string contextListName = string(NLC_ITEM_TYPE_REFERENCECONTEXTLEVELLIST_VAR_APPENDITION);
	string entityToAddName = NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE;

	string codeBlockTextFunctionHeader = progLangClassMemberFunctionTypeDefault[progLang] + NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT_ADD_ENTITY_TO_CONTEXT_LIST_FUNCTION_NAME + progLangOpenParameterSpace[progLang] + generateCodeEntityListDefinitionTypeTextReference(genericEntityClassName, progLang) + contextListName + progLangClassMemberFunctionParametersNext[progLang] + generateCodeEntityDefinitionText(genericEntityClassName, entityToAddName, progLang) + progLangClassMemberFunctionParametersNext[progLang] + progLangClassLastSentenceIndexVariableType[progLang] + NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT_SENTENCE_INDEX_VARIABLE_NAME + progLangCloseParameterSpace[progLang];	//void addVariableToContextList(vector<genericEntityClass*>& contextList, genericEntityClass* genericEntity, int sentenceIndex)

	printLine("", level, code);
	printLine(codeBlockTextFunctionHeader, level, code);
	printLine(progLangOpenBlock[progLang], level, code);
		string pushLastSentenceReferencedText = contextListName + progLangObjectReferenceDelimiter2[progLang] + progLangAddEntityToList[progLang] + progLangOpenParameterSpace[progLang] + entityToAddName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//contextList.push_back(genericEntity);
		printLine(pushLastSentenceReferencedText, (level+1), code);
		string codeBlockUpdateLastSentenceReferencedText = entityToAddName + progLangObjectReferenceDelimiter[progLang] + NLC_USE_ADVANCED_REFERENCING_LAST_SENTENCE_REFERENCED_VARIABLE_NAME + progLangObjectReferenceDelimiter2[progLang] + progLangStackAdd[progLang] + progLangOpenParameterSpace[progLang] + NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT_SENTENCE_INDEX_VARIABLE_NAME + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//genericEntity->lastSentenceReferenced.push(sentenceIndex);		
		printLine(codeBlockUpdateLastSentenceReferencedText, (level+1), code);
	printLine(progLangCloseBlock[progLang], level, code);
}

void generateCodeAddEntityToReferenceContextListExecuteFunction(NLCitem* param1, NLCitem* param2, NLCitem* param3, int progLang, string* code, int level)
{
	#ifdef NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT_PRINT_LEVEL_USED_INSTEAD_OF_CONTEXT_LEVEL
	string contextLevelString = convertIntToString(level);
	#else
	string contextLevelString = param1->name;
	#endif
	string entityToAddName = param2->instanceName;
	string sentenceIndexString = param3->name;

	string genericEntityClassName = generateClassName(NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE);
	string contextListName = string(NLC_ITEM_TYPE_REFERENCECONTEXTLEVELLIST_VAR_APPENDITION) + contextLevelString;
	string tempVariableName = string(NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE);

	string codeBlockText = "";
	codeBlockText = codeBlockText + NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT_ADD_ENTITY_TO_CONTEXT_LIST_FUNCTION_NAME + progLangOpenParameterSpace[progLang] + contextListName + progLangClassMemberFunctionParametersNext[progLang] + param2->instanceName + progLangClassMemberFunctionParametersNext[progLang] + sentenceIndexString + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//addVariableToContextList(contextListX, entityName, sentenceIndex);			
	printLine(codeBlockText, level, code);
}

void generateCodeClearReferenceContextListNewFunction(int progLang, string* code, int level)
{
	string iterIndexString = convertIntToString(1);	//functions declared at level 1
	string genericEntityClassName = generateClassName(NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE);
	string contextListName = string(NLC_ITEM_TYPE_REFERENCECONTEXTLEVELLIST_VAR_APPENDITION);
	string tempVariableName = string(NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE);

	string codeBlockTextFunctionHeader = progLangClassMemberFunctionTypeDefault[progLang] + NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT_CLEAR_CONTEXT_LIST_FUNCTION_NAME + progLangOpenParameterSpace[progLang] + generateCodeEntityListDefinitionTypeTextReference(genericEntityClassName, progLang) + contextListName + progLangCloseParameterSpace[progLang];	//void clearContextList(vector<genericEntityClass*>& contextList)

	printLine("", level, code);
	printLine(codeBlockTextFunctionHeader, level, code);
	printLine(progLangOpenBlock[progLang], level, code);
		string codeBlockText = progLangFor[progLang] + progLangForIterPart1[progLang] + generateCodeEntityListDefinitionTypeTextCompact(genericEntityClassName, progLang) + progLangForIterPart2a[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart2c[progLang] + contextListName + progLangForIterPart3a[progLang] + progLangForIterPart3b[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart3c[progLang] + contextListName + progLangForIterPart4a[progLang] + progLangForIterPart4b[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart4c[progLang];	//for(vector<genericEntityClass*>::iterator iterX = contextList.begin(); iterX < contextList.end(); iterX++)
		printLine(codeBlockText, (level+1), code);
			printLine(progLangOpenBlock[progLang], (level+1), code);	//{
			string tempVarDeclarationText = generateCodeEntityDefinitionText(genericEntityClassName, tempVariableName, progLang) + progLangEquals[progLang] + progLangPointer[progLang] + progLangForIterName[progLang] + iterIndexString + progLangEndLine[progLang];	//genericEntityClass* genericEntity = *iter2;
			printLine(tempVarDeclarationText, (level+2), code);
			string popLastSentenceReferencedText = tempVariableName + progLangObjectReferenceDelimiter[progLang] + NLC_USE_ADVANCED_REFERENCING_LAST_SENTENCE_REFERENCED_VARIABLE_NAME + progLangObjectReferenceDelimiter2[progLang] + progLangStackRemove[progLang] + progLangEndLine[progLang];	//genericEntity->lastSentenceReferenced.pop();
			printLine(popLastSentenceReferencedText, (level+2), code);
		printLine(progLangCloseBlock[progLang], (level+1), code);
		string clearContextListText = contextListName + progLangObjectReferenceDelimiter2[progLang] + progLangRemoveProperties[progLang] + progLangEndLine[progLang];		//contextList.clear();
		printLine(clearContextListText, (level+1), code);
	printLine(progLangCloseBlock[progLang], level, code);
}

void generateCodeClearReferenceContextListExecuteFunction(NLCitem* param1, int progLang, string* code, int level)
{
	#ifdef NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT_PRINT_LEVEL_USED_INSTEAD_OF_CONTEXT_LEVEL
	string contextLevelString = convertIntToString(level);
	#else
	string contextLevelString = param1->name;
	//cout << "contextLevelString = " << contextLevelString << endl;
	#endif
			
	string contextListName = string(NLC_ITEM_TYPE_REFERENCECONTEXTLEVELLIST_VAR_APPENDITION) + contextLevelString;

	string codeBlockExecuteFunctionText = "";
	codeBlockExecuteFunctionText = codeBlockExecuteFunctionText + NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT_CLEAR_CONTEXT_LIST_FUNCTION_NAME +  progLangOpenParameterSpace[progLang] + contextListName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//clearContextLevelList(contextListX);
	printLine(codeBlockExecuteFunctionText, level, code);
}

#endif
#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS
void generateCodeCastVectorNewFunction(int progLang, string* code, int level)
{
	string iterIndexString = convertIntToString(1);	//functions declared at level 1
	string templateName1 = "E1";
	string templateName2 = "E2";
	string entity1InstanceListName = templateName1 + generateEntityListAppendName();
	string entity2InstanceListName = templateName2 + generateEntityListAppendName();
	string tempVariableName = string(NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE);

	string codeBlockTextTemplateHeader = progLangTemplateHeaderPart1[progLang] + progLangTemplateHeaderClassType[progLang] + templateName1 + progLangTemplateUseClassSeparator[progLang] + progLangTemplateHeaderClassType[progLang] + templateName2 + progLangTemplateHeaderPart2[progLang];  //template <class E1, class E2>
	string codeBlockTextFunctionHeader = generateCodeEntityListDefinitionTypeTextReference(templateName2, progLang) + NLC_CAST_VECTOR_FUNCTION_NAME + progLangOpenParameterSpace[progLang] + generateCodeEntityListDefinitionTypeTextReference(templateName1, progLang) + entity1InstanceListName + progLangCloseParameterSpace[progLang];	//vector<E2*>& castVector(vector<E1*>& E1InstanceList)

	printLine("", level, code);
	printLine(codeBlockTextTemplateHeader, level, code);
	printLine(codeBlockTextFunctionHeader, level, code);
	printLine(progLangOpenBlock[progLang], level, code);
		string codeBlockTextDeclareVectorPointerAndSet = generateCodeEntityListDefinitionTypeTextReference(templateName2, progLang) + entity2InstanceListName + progLangEquals[progLang] + generateReinterpretCastOfVectorReference(entity1InstanceListName, templateName2, progLang) + progLangEndLine[progLang];	//vector<E2*>& E2InstanceList = reinterpret_cast<vector<E2*>& >(E1List);
		printLine(codeBlockTextDeclareVectorPointerAndSet, (level+1), code);

		string codeBlockTextReturnNewVector = progLangReturn[progLang] + entity2InstanceListName + progLangEndLine[progLang];		//return E2InstanceList;
		printLine(codeBlockTextReturnNewVector, (level+1), code);
	printLine(progLangCloseBlock[progLang], level, code);	//}
}

void generateCodeCastVectorExecuteFunction(NLCitem* param1, NLCitem* param2, int progLang, string* code, int level)
{
	string codeBlockTextTemplateDefinition = progLangTemplateUsePart1[progLang] + param1->className + progLangTemplateUseClassSeparator[progLang] + param2->className + progLangTemplateUsePart2[progLang] + STRING_SPACE; 	//<param1class, param2class>
	string codeBlockExecuteFunctionText = string("") + NLC_CAST_VECTOR_FUNCTION_NAME + codeBlockTextTemplateDefinition + progLangOpenParameterSpace[progLang] + generateEntityListName(param1) + progLangCloseParameterSpace[progLang];	//castVector<param1class, param2class> (param1InstanceList)
	printLine(codeBlockExecuteFunctionText, level, code);
}

#endif
#ifdef NLC_USE_ADVANCED_REFERENCING_SUPPORT_ALIASES
void generateCodeFindAliasAndAddToCategoryListNewFunction(int progLang, string* code, int level)
{
	string iterIndexString = convertIntToString(1);	//functions declared at level 1

	string genericEntityClassName = generateClassName(NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE);
	string aliasListName = NLC_ITEM_TYPE_ALIASLIST_VAR_APPENDITION;
	string aliasName = NLC_USE_ADVANCED_REFERENCING_SUPPORT_ALIASES_ALIAS_NAME;

	#ifdef NLC_NONOO
	string templateName1 = NLCNONOO_GENERIC_ENTITY_NODE_NAME;
	#else
	string templateName1 = "E1";
	#endif
	string entity1InstanceListName = templateName1 + generateEntityListAppendName();
	string entity1CategoryListName = templateName1 + NLC_ITEM_TYPE_CATEGORYLIST_VAR_APPENDITION;
	string tempVariableName = string(NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE);	//NLCgenericEntity
	string tempVariableAliasListName = tempVariableName + progLangObjectReferenceDelimiter[progLang] + NLC_ITEM_TYPE_ALIASLIST_VAR_APPENDITION;

	#ifdef NLC_NONOO
	string codeBlockTextTemplateHeader = "";
	#else
	string codeBlockTextTemplateHeader = progLangTemplateHeaderPart1[progLang] + progLangTemplateHeaderClassType[progLang] + templateName1 + progLangTemplateHeaderPart2[progLang];  //template <class E1>
	#endif

	string codeBlockTextFunctionHeader = progLangClassMemberFunctionTypeDefault[progLang] + NLC_USE_ADVANCED_REFERENCING_FIND_ALIAS_AND_ADD_TO_CATEGORY_LIST_FUNCTION_NAME + progLangOpenParameterSpace[progLang] + generateCodeEntityListDefinitionTypeTextReference(templateName1, progLang) + entity1InstanceListName + progLangClassMemberFunctionParametersNext[progLang] + progLangAliasNameVariableType[progLang] + aliasName + progLangClassMemberFunctionParametersNext[progLang] + generateCodeEntityListDefinitionTypeTextReference(templateName1, progLang) + entity1CategoryListName + progLangCloseParameterSpace[progLang];	//void findAliasAndAddToCategoryListNewFunction(vector<E1*>& E1instanceList, string aliasName, vector<E1*>& E1CategoryList)

	int q = 0;
	printLine("", level+q, code);
	printLine(codeBlockTextTemplateHeader, level+q, code);
	printLine(codeBlockTextFunctionHeader, level+q, code);
	printLine(progLangOpenBlock[progLang], level+q, code);
	q++;
		string codeBlockTextForLoop = progLangFor[progLang] + progLangForIterPart1[progLang] + progLangTypeName[progLang] + generateCodeEntityListDefinitionTypeTextCompact(templateName1, progLang) + progLangForIterPart2a[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart2c[progLang] + entity1InstanceListName + progLangForIterPart3a[progLang] + progLangForIterPart3b[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart3c[progLang] + entity1InstanceListName + progLangForIterPart4a[progLang] + progLangForIterPart4b[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart4c[progLang];	//for(typename vector<E1*>::iterator iterX = E1InstanceList.begin(); iterX < E1InstanceList.end(); iterX++)
		printLine(codeBlockTextForLoop, level+q, code);
		printLine(progLangOpenBlock[progLang], level+q, code);	//{
			q++;
			string tempVarDeclarationText = generateCodeEntityDefinitionText(templateName1, tempVariableName, progLang) + progLangEquals[progLang] + progLangPointer[progLang] + progLangForIterName[progLang] + iterIndexString + progLangEndLine[progLang];	//E1* genericEntity = *iter1;
			printLine(tempVarDeclarationText, (level+q), code);
			//NB this code could be generated using existing codeblock (NLC_CODEBLOCK_TYPE_FOR_GENERIC_LIST)

			string negativeModifierStringFind = "";	//if found (positive find)
			string findAliasNameInAliasListText = progLangFindPart1[progLang] + negativeModifierStringFind + progLangFindPart2[progLang] + tempVariableAliasListName + progLangFindPart3[progLang] + tempVariableAliasListName + progLangFindPart4[progLang] + aliasName + progLangFindPart5[progLang] + tempVariableAliasListName + progLangFindPart6[progLang];	//if(!find(genericEntity->aliasList.begin(), genericEntity->aliasList.end(), aliasName) != genericEntity->aliasList.end()) 
				//NB this code could be moved to a new codeblock  (NLC_CODEBLOCK_TYPE_FIND_PROPERTY_IN_GENERIC_LIST)
			printLine(findAliasNameInAliasListText, level+q, code);
			printLine(progLangOpenBlock[progLang], level+q, code);
			q++;
				string addEntityToCategoryText = entity1CategoryListName + progLangObjectReferenceDelimiter2[progLang] + progLangAddEntityToList[progLang] + progLangOpenParameterSpace[progLang] + tempVariableName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//E1CategoryList.push_back(genericEntity);
				printLine(addEntityToCategoryText, (level+q), code);

			q--;
			printLine(progLangCloseBlock[progLang], level+q, code);	//}
		q--;
		printLine(progLangCloseBlock[progLang], level+q, code);	//}
	q--;
	printLine(progLangCloseBlock[progLang], level+q, code);	//}
}

void generateCodeFindAliasAndAddToCategoryListExecuteFunction(NLCitem* param1, NLCitem* param2, NLCitem* param3, int progLang, string* code, int level)
{
	string genericListAppendName = param3->name;

	#ifdef NLC_NONOO
	string codeBlockTextTemplateDefinition = "";
	#else
	string codeBlockTextTemplateDefinition = progLangTemplateUsePart1[progLang] + param2->className + progLangTemplateUsePart2[progLang] + STRING_SPACE; 	//<param2class>
	#endif
	string codeBlockExecuteFunctionText = string("") + NLC_USE_ADVANCED_REFERENCING_FIND_ALIAS_AND_ADD_TO_CATEGORY_LIST_FUNCTION_NAME + codeBlockTextTemplateDefinition + progLangOpenParameterSpace[progLang] + generateEntityListName(param2) + progLangClassMemberFunctionParametersNext[progLang] + progLangStringOpenClose[progLang] + param1->name + progLangStringOpenClose[progLang] + progLangClassMemberFunctionParametersNext[progLang] + generateGenericListName(param2->instanceName, genericListAppendName) + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//findAliasAndAddToCategoryList<param2class> (param2InstanceList, "param1aliasName", param3CategoryList);
	printLine(codeBlockExecuteFunctionText, level, code);
}

void generateCodeFindAliasNewFunction(int progLang, string* code, int level)
{
	string iterIndexString = convertIntToString(1);	//functions declared at level 1

	string aliasName = NLC_USE_ADVANCED_REFERENCING_SUPPORT_ALIASES_ALIAS_NAME;

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

	string codeBlockTextFunctionHeader = progLangClassMemberFunctionTypeBool[progLang] + NLC_USE_ADVANCED_REFERENCING_FIND_ALIAS_FUNCTION_NAME + progLangOpenParameterSpace[progLang] + generateCodeEntityDefinitionText(templateName1, entity1InstanceName, progLang) + progLangClassMemberFunctionParametersNext[progLang] + progLangAliasNameVariableType[progLang] + aliasName + progLangCloseParameterSpace[progLang];	//bool findAliasNewFunction(E1* E1instance, string aliasName)

	int q = 0;
	printLine("", level+q, code);
	printLine(codeBlockTextTemplateHeader, level+q, code);
	printLine(codeBlockTextFunctionHeader, level+q, code);
	printLine(progLangOpenBlock[progLang], level+q, code);
	q++;
		string declareText = generateCodeDeclareBoolTextAndSetFalse(resultName, progLang);	//bool result = false;
		printLine(declareText, level+q, code);

		string negativeModifierStringFind = "";	//if found (positive find)
		string findAliasNameInAliasListText = progLangFindPart1[progLang] + negativeModifierStringFind + progLangFindPart2[progLang] + entity1aliasListName + progLangFindPart3[progLang] + entity1aliasListName + progLangFindPart4[progLang] + aliasName + progLangFindPart5[progLang] + entity1aliasListName + progLangFindPart6[progLang];	//if(!find(E1instance->aliasList.begin(), E1instance->aliasList.end(), aliasName) != E1instance->aliasList.end()) 
			//NB this code could be moved to a new codeblock  (NLC_CODEBLOCK_TYPE_FIND_PROPERTY_IN_GENERIC_LIST)
		printLine(findAliasNameInAliasListText, level+q, code);
		printLine(progLangOpenBlock[progLang], level+q, code);
		q++;
			string setText = generateCodeSetBoolTextTrue(resultName, progLang);	//result = true;
			printLine(setText, (level+q), code);
		q--;
		printLine(progLangCloseBlock[progLang], level+q, code);	//}

		string returnText = generateCodeReturnText(resultName, progLang);	//return result;
		printLine(returnText, level+q, code);
	q--;
	printLine(progLangCloseBlock[progLang], level+q, code);	//}
}

void generateCodeFindAliasExecuteFunction(NLCitem* param1, NLCitem* param2, int progLang, string* code, int level)
{
	#ifdef NLC_NONOO
	string codeBlockTextTemplateDefinition = "";
	#else
	string codeBlockTextTemplateDefinition = progLangTemplateUsePart1[progLang] + param2->className + progLangTemplateUsePart2[progLang] + STRING_SPACE; 	//<param2class>
	#endif
	string codeBlockExecuteFunctionText = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + NLC_USE_ADVANCED_REFERENCING_FIND_ALIAS_FUNCTION_NAME + codeBlockTextTemplateDefinition + progLangOpenParameterSpace[progLang] + generateEntityName(param2) + progLangClassMemberFunctionParametersNext[progLang] + progLangStringOpenClose[progLang] + param1->name + progLangStringOpenClose[progLang] + progLangCloseParameterSpace[progLang] + progLangCloseParameterSpace[progLang];	//if(findAlias<param2class> (param2, "param1aliasName"))
	printLine(codeBlockExecuteFunctionText, level, code);
	printLine(progLangOpenBlock[progLang], level, code);	//{
}

#endif
#ifdef NLC_SUPPORT_REDEFINITIONS
void generateCodeCheckParentClassNameNewFunction(int progLang, string* code, int level)
{
	string iterIndexString = convertIntToString(1);	//functions declared at level 1

	string objectName = "object";
	string genericEntityClassName = generateClassName(NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE);
	string className = "className";
	string parentName = "parent";
	string resultName = "result";

	string codeBlockTextFunctionHeader = progLangClassMemberFunctionTypeBool[progLang] + NLC_CLASS_PARENT_CHECK_PARENT_CLASS_NAME_FUNCTION_NAME + progLangOpenParameterSpace[progLang] + generateCodeEntityDefinitionText(genericEntityClassName, objectName, progLang) + progLangClassMemberFunctionParametersNext[progLang] + progLangClassNameVariableType[progLang] + className + progLangCloseParameterSpace[progLang];	//bool checkParentClassName(NLCgenericEntityClass* object, string className)

	int q = 0;
	printLine("", level+q, code);
	printLine(codeBlockTextFunctionHeader, level+q, code);
	printLine(progLangOpenBlock[progLang], level+q, code);
	q++;
		string declareText = generateCodeDeclareBoolTextAndSetFalse(resultName, progLang);	//bool result = false;
		printLine(declareText, level+q, code);

		string negativeModifierStringFind = "";	//if found (positive find)
		string ifObjectNameEqualsClassNameText = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + objectName + progLangObjectReferenceDelimiter[progLang] + progLangClassNameVariableName[progLang] + progLangEqualsTest[progLang] + className + progLangCloseParameterSpace[progLang];	//if(object->name == className)
			//NB this code could be moved to a new codeblock  (NLC_CODEBLOCK_TYPE_IF_OBJECT_NAME_EQUALS_STRING)
		printLine(ifObjectNameEqualsClassNameText, level+q, code);
		printLine(progLangOpenBlock[progLang], level+q, code);
		q++;
			string setText = generateCodeSetBoolTextTrue(resultName, progLang);	//result = true;
			printLine(setText, (level+q), code);
		q--;
		printLine(progLangCloseBlock[progLang], level+q, code);	//}


		string contextParam1 = objectName + progLangObjectReferenceDelimiter[progLang];
		string codeBlockText = progLangFor[progLang] + progLangForIterPart1[progLang] + generateCodeEntityListDefinitionTypeTextCompact(genericEntityClassName, progLang) + progLangForIterPart2a[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart2c[progLang] + contextParam1 + NLC_CLASS_PARENT_CLASS_LIST_NAME + progLangForIterPart3a[progLang] + progLangForIterPart3b[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart3c[progLang] + contextParam1 + NLC_CLASS_PARENT_CLASS_LIST_NAME + progLangForIterPart4a[progLang] + progLangForIterPart4b[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart4c[progLang];	//for(vector<NLCgenericEntityClass*>::iterator iter1 = object->parentClassList.begin(); iter1 < object->parentClassList.end(); iter1++)
		printLine(codeBlockText, level+q, code);
		printLine(progLangOpenBlock[progLang], level+q, code);
		q++;
			string tempVarDeclarationText = generateCodeEntityDefinitionText(genericEntityClassName, parentName, progLang) + progLangEquals[progLang] + progLangPointer[progLang] + progLangForIterName[progLang] + iterIndexString + progLangEndLine[progLang];	//NLCgenericEntityClass* parent = *iter1;
			printLine(tempVarDeclarationText, (level+q), code);
			string codeBlockExecuteFunctionText = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + NLC_CLASS_PARENT_CHECK_PARENT_CLASS_NAME_FUNCTION_NAME + progLangOpenParameterSpace[progLang] + parentName + progLangClassMemberFunctionParametersNext[progLang] + className + progLangCloseParameterSpace[progLang] + progLangCloseParameterSpace[progLang];	//if(checkParentClassName(parent, className))
			printLine(codeBlockExecuteFunctionText, level+q, code);
			printLine(progLangOpenBlock[progLang], level+q, code);
			q++;
				printLine(setText, (level+q), code);
			q--;
			printLine(progLangCloseBlock[progLang], level+q, code);	//}
		q--;
		printLine(progLangCloseBlock[progLang], level+q, code);	//}

		string returnText = generateCodeReturnText(resultName, progLang);	//return result;
		printLine(returnText, level+q, code);
	q--;
	printLine(progLangCloseBlock[progLang], level+q, code);	//}
}

void generateCodeCheckParentClassNameExecuteFunction1(NLCitem* param1, NLCitem* param2, int progLang, string* code, int level)
{
	string objectName = param1->instanceName;
	string classNameToFind = param2->name;
	string genericEntityClassName = generateClassName(NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE);
	string codeBlockExecuteFunctionText = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + string(NLC_CLASS_PARENT_CHECK_PARENT_CLASS_NAME_FUNCTION_NAME) + progLangOpenParameterSpace[progLang] + generateStaticCastOfEntity(objectName, genericEntityClassName, progLang) + progLangClassMemberFunctionParametersNext[progLang] + progLangStringOpenClose[progLang] + classNameToFind + progLangStringOpenClose[progLang] + progLangCloseParameterSpace[progLang] + progLangCloseParameterSpace[progLang];	//if(checkParentClassName(static_cast<NLCgenericEntityClass*>(param1), param2))
	printLine(codeBlockExecuteFunctionText, level, code);
	printLine(progLangOpenBlock[progLang], level, code);	//{
}

void generateCodeCheckParentClassNameExecuteFunction2(NLCitem* param1, NLCitem* param2, int progLang, string* code, int level)
{
	string objectClassName = param1->className; 
	string classNameToFind = param2->name;
	string genericEntityClassName = generateClassName(NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE);
	string codeBlockExecuteFunctionText = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + string(NLC_CLASS_PARENT_CHECK_PARENT_CLASS_NAME_FUNCTION_NAME) + progLangOpenParameterSpace[progLang] + generateStaticCastOfNewEntity(objectClassName, genericEntityClassName, progLang) + progLangClassMemberFunctionParametersNext[progLang] + progLangStringOpenClose[progLang] + classNameToFind + progLangStringOpenClose[progLang] + progLangCloseParameterSpace[progLang] + progLangCloseParameterSpace[progLang];	//if(checkParentClassName(static_cast<NLCgenericEntityClass*>(new param1Class), param2))
	printLine(codeBlockExecuteFunctionText, level, code);
	printLine(progLangOpenBlock[progLang], level, code);	//{
}

#endif


void generateCodeAddProperty(NLCitem* param1, NLCitem* param2, int progLang, string* code, int level)
{
	#ifdef NLC_USE_LIBRARY_BASE_EXTENDED
	generateCodeAddPropertyExecuteFunction(param1, param2, progLang, code, level);
	#else
	#ifdef NLC_USE_NON_LIBRARY_FUNCTIONS_EXTENDED
	generateCodeAddPropertyExecuteFunction(param1, param2, progLang, code, level);	
	#else
	generateCodeAddPropertyEntityToList(param1, param2, progLang, code, level);
	#endif
	#endif
}
void generateCodeAddPropertyEntityToList(NLCitem* param1, NLCitem* param2, int progLang, string* code, int level)
{
	string contextParam1 = generateStringFromContextVector(&(param1->context), progLang);
	#ifdef NLC_NONOO
	string codeBlockText = contextParam1 + param1->instanceName + progLangObjectReferenceDelimiter[progLang] + generatePropertyListName() + progLangObjectReferenceDelimiter2[progLang] + progLangAddProperty[progLang] + progLangOpenParameterSpace[progLang] + param2->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//context1->param1->param2PropertyList.push_back(param2);
	printLine(codeBlockText, level, code);
	codeBlockText = param2->instanceName + progLangObjectReferenceDelimiter[progLang] + generatePropertyReverseListName() + progLangObjectReferenceDelimiter2[progLang] + progLangAddProperty[progLang] + progLangOpenParameterSpace[progLang] + contextParam1 + param1->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//param2->param2IncomingPropertyList.push_back(context1->param1);
	printLine(codeBlockText, level, code);
	#else
	string codeBlockText = contextParam1 + param1->instanceName + progLangObjectReferenceDelimiter[progLang] + generatePropertyListName(param2->className) + progLangObjectReferenceDelimiter2[progLang] + progLangAddProperty[progLang] + progLangOpenParameterSpace[progLang] + param2->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//context1->param1->param2PropertyList.push_back(param2);	
	printLine(codeBlockText, level, code);
	codeBlockText = param2->instanceName + progLangObjectReferenceDelimiter[progLang] + generateAllPropertyIncomingListName() + progLangObjectReferenceDelimiter2[progLang] + progLangAddProperty[progLang] + progLangOpenParameterSpace[progLang] + contextParam1 + param1->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//param2->propertyIncomingList.push_back(context1->param1);	//added 1p1b	
	printLine(codeBlockText, level, code);
	#endif
}

#ifdef NLC_USE_LIBRARY_BASE_EXTENDED
void generateCodeAddPropertyExecuteFunction(NLCitem* param1, NLCitem* param2, int progLang, string* code, int level)
{
	string contextParam1 = generateStringFromContextVector(&(param1->context), progLang);
	string codeBlockTextTemplateDefinition = progLangTemplateUsePart1[progLang] + param1->className + progLangTemplateUseClassSeparator[progLang] + param2->className + progLangTemplateUsePart2[progLang]; 	//<param1class, param2class>
	string codeBlockExecuteFunctionText = "";
	codeBlockExecuteFunctionText = codeBlockExecuteFunctionText + NLC_USE_LIBRARY_BASE_EXTENDED_FUNCTION_NAME_ADD_PROPERTY + codeBlockTextTemplateDefinition + progLangOpenParameterSpace[progLang] + contextParam1 + param1->instanceName + progLangClassMemberFunctionParametersNext[progLang] + generateCodeListPointer(contextParam1 + param1->instanceName + progLangObjectReferenceDelimiter[progLang] + generatePropertyListName(param2), progLang) + progLangClassMemberFunctionParametersNext[progLang] + param2->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//addProperty<param1class, param2class>(context1->param1, &(context1->param1.param2PropertyList), param2);
	printLine(codeBlockExecuteFunctionText, level, code);	
}
#endif
#ifdef NLC_USE_NON_LIBRARY_FUNCTIONS_EXTENDED
void generateCodeAddPropertyNewFunction(int progLang, string* code, int level)
{
	#ifdef NLC_USE_ENUM_LISTS
	cout << "NLC_USE_NON_LIBRARY_FUNCTIONS_EXTENDED:generateCodeAddPropertyNewFunction{} error: does not support NLC_USE_ENUM_LISTS, use NLC_USE_LIBRARY:NLC_USE_LIBRARY_BASE_EXTENDED instead (NLClibraryBase.cpp)" << endl;
	#else
	string templateName1 = "E1";
	string templateName2 = "E2";
	NLCitem param1(templateName1, NLC_ITEM_TYPE_OBJECT);
	NLCitem param2(templateName2, NLC_ITEM_TYPE_OBJECT);
	param1->instanceName = templateName1 + generateEntityListAppendName();
	param2->instanceName = templateName2 + generateEntityListAppendName();

	string codeBlockTextTemplateHeader = progLangTemplateHeaderPart1[progLang] + progLangTemplateHeaderClassType[progLang] + templateName1 + progLangTemplateUseClassSeparator[progLang] + progLangTemplateHeaderClassType[progLang] + templateName2 + progLangTemplateHeaderPart2[progLang];  //template <class E1, class E2>
	string codeBlockTextFunctionHeader = progLangClassMemberFunctionTypeDefault[progLang] + NLC_USE_LIBRARY_BASE_EXTENDED_FUNCTION_NAME_ADD_PROPERTY + progLangOpenParameterSpace[progLang] +  generateCodeEntityDefinitionText(param1, progLang) + progLangParameterSpaceNextParam[progLang] + generateCodePropertyListDefinitionText(param2, progLang) + progLangParameterSpaceNextParam[progLang] + generateCodeEntityDefinitionText(param2, progLang) + progLangCloseParameterSpace[progLang];	//void addProperty(E1* E1Instance, vector<E2*>* E2PropertyList, E2* E2Instance)

	int q = 0;
	printLine("", level+q, code);
	printLine(codeBlockTextTemplateHeader, level+q, code);
	printLine(codeBlockTextFunctionHeader, level+q, code);
	printLine(progLangOpenBlock[progLang], level+q, code);
		
	q++;
	string codeBlockText = generatePropertyListName(param2) + progLangObjectReferenceDelimiter2[progLang] + progLangAddProperty[progLang] + progLangOpenParameterSpace[progLang] + param2->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//param2PropertyList.push_back(param2);	
	printLine(codeBlockText, level+q, code);
	codeBlockText = param2->instanceName + progLangObjectReferenceDelimiter[progLang] + generateAllPropertyIncomingListName() + progLangObjectReferenceDelimiter2[progLang] + progLangAddProperty[progLang] + progLangOpenParameterSpace[progLang] + contextParam1 + param1->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//param2->propertyIncomingList.push_back(context1->param1);	
	printLine(codeBlockText, level+q, code);
	
	q--;
	printLine(progLangCloseBlock[progLang], level+q, code);
	#endif
}
#endif


void generateCodeRemoveProperty(NLCitem* param1, NLCitem* param2, int progLang, string* code, int level)
{
	#ifdef NLC_USE_LIBRARY_BASE_EXTENDED
	generateCodeRemovePropertyExecuteFunction(param1, param2, progLang, code, level);
	#else
	FINISHTHIS
	printLine(codeBlockText, level, code);
	#endif
}
void generateCodeRemoveProperties(NLCitem* param1, NLCitem* param2, int progLang, string* code, int level)
{
	#ifdef NLC_USE_LIBRARY_BASE_EXTENDED
	generateCodeRemovePropertiesExecuteFunction(param1, param2, progLang, code, level);
	#else
	string codeBlockText = contextParam1 + param1->instanceName + progLangObjectReferenceDelimiter[progLang] + generatePropertyListName(param2) + progLangObjectReferenceDelimiter2[progLang] + progLangRemoveProperties[progLang] + progLangEndLine[progLang];		//context1->param1->param2PropertyList.clear();
	printLine(codeBlockText, level, code);	
	#endif
}
#ifdef NLC_USE_LIBRARY_BASE_EXTENDED
void generateCodeRemovePropertyExecuteFunction(NLCitem* param1, NLCitem* param2, int progLang, string* code, int level)
{
	string contextParam1 = generateStringFromContextVector(&(param1->context), progLang);
	string codeBlockTextTemplateDefinition = progLangTemplateUsePart1[progLang] + param1->className + progLangTemplateUseClassSeparator[progLang] + param2->className + progLangTemplateUsePart2[progLang]; 	//<param1class, param2class>
	string codeBlockExecuteFunctionText = "";
	codeBlockExecuteFunctionText = codeBlockExecuteFunctionText + NLC_USE_LIBRARY_BASE_EXTENDED_FUNCTION_NAME_REMOVE_PROPERTY + codeBlockTextTemplateDefinition + progLangOpenParameterSpace[progLang] + contextParam1 + param1->instanceName + progLangClassMemberFunctionParametersNext[progLang] + generateCodeListPointer(contextParam1 + param1->instanceName + progLangObjectReferenceDelimiter[progLang] + generatePropertyListName(param2), progLang) + progLangClassMemberFunctionParametersNext[progLang] + param2->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//removeProperty<param1class, param2class>(context1->param1, &(context1->param1.param2PropertyList), param2);
	printLine(codeBlockExecuteFunctionText, level, code);	
}
void generateCodeRemovePropertiesExecuteFunction(NLCitem* param1, NLCitem* param2, int progLang, string* code, int level)
{
	string contextParam1 = generateStringFromContextVector(&(param1->context), progLang);
	string codeBlockTextTemplateDefinition = progLangTemplateUsePart1[progLang] + param1->className + progLangTemplateUseClassSeparator[progLang] + param2->className + progLangTemplateUsePart2[progLang]; 	//<param1class, param2class>
	string codeBlockExecuteFunctionText = "";
	codeBlockExecuteFunctionText = codeBlockExecuteFunctionText + NLC_USE_LIBRARY_BASE_EXTENDED_FUNCTION_NAME_REMOVE_PROPERTIES + codeBlockTextTemplateDefinition + progLangOpenParameterSpace[progLang] + contextParam1 + param1->instanceName + progLangClassMemberFunctionParametersNext[progLang] + generateCodeListPointer(contextParam1 + param1->instanceName + progLangObjectReferenceDelimiter[progLang] + generatePropertyListName(param2), progLang) + progLangClassMemberFunctionParametersNext[progLang] + param2->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//removeProperties<param1class, param2class>(context1->param1, &(context1->param1.param2PropertyList), param2);
	printLine(codeBlockExecuteFunctionText, level, code);	
}
#endif


void generateCodeAddCondition(NLCitem* param1, NLCitem* param2, NLCitem* param3, int progLang, string* code, int level)
{
	#ifdef NLC_USE_LIBRARY_BASE_EXTENDED
	generateCodeAddConditionExecuteFunction(param1, param2, param3, progLang, code, level);
	#else
	#ifdef NLC_USE_NON_LIBRARY_FUNCTIONS_EXTENDED
	generateCodeAddConditionExecuteFunction(param1, param2, param3, progLang, code, level);
	#else
	generateCodeAddConditionAndObjectEntityToList(param1, param2, param3, progLang, code, level);
	#endif
	#endif
}
//NB NLC_NONOO requires !NLC_USE_STRING_INDEXED_UNORDERED_MAPS_FOR_CONDITION_LISTS
void generateCodeAddConditionAndObjectEntityToList(NLCitem* param1, NLCitem* param2, NLCitem* param3, int progLang, string* code, int level)
{
	string contextParam1 = generateStringFromContextVector(&(param1->context), progLang);
	#ifndef NLC_USE_STRING_INDEXED_UNORDERED_MAPS_FOR_CONDITION_LISTS
	string codeBlockTextCreate2 = generateCodeNewEntity(param2, progLang);
	printLine(codeBlockTextCreate2, level, code);
	#endif
	#ifdef NLC_NONOO
	string codeBlockText = contextParam1 + param1->instanceName + progLangObjectReferenceDelimiter[progLang] + generateGIAconditionListName() + progLangObjectReferenceDelimiter2[progLang] + progLangAddProperty[progLang] + progLangOpenParameterSpace[progLang] + param2->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//context1->param1->param2ConditionList.push_back(param2);
	printLine(codeBlockText, level, code);
	codeBlockText = param2->instanceName + progLangObjectReferenceDelimiter[progLang] + generateGIAconditionObjectListName() + progLangObjectReferenceDelimiter2[progLang] + progLangAddProperty[progLang] + progLangOpenParameterSpace[progLang] + param3->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//param2->param2ConditionObjectList.push_back(param3);
	printLine(codeBlockText, level, code);
	#ifdef NLC_NONOO_CREATE_REVERSE_LISTS
	codeBlockText = param3->instanceName + progLangObjectReferenceDelimiter[progLang] + generateGIAincomingConditionListName() + progLangObjectReferenceDelimiter2[progLang] + progLangAddProperty[progLang] + progLangOpenParameterSpace[progLang] + param2->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//param3->param2IncomingConditionList.push_back(param2);
	printLine(codeBlockText, level, code);
	codeBlockText = param2->instanceName + progLangObjectReferenceDelimiter[progLang] + generateGIAconditionSubjectListName() + progLangObjectReferenceDelimiter2[progLang] + progLangAddProperty[progLang] + progLangOpenParameterSpace[progLang] + contextParam1 + param1->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//param2->param2ConditionSubjectList.push_back(context1->param1);
	printLine(codeBlockText, level, code);
	#endif
	#else
	string codeBlockText = contextParam1 + param1->instanceName + progLangObjectReferenceDelimiter[progLang] + generateConditionListName(param2->className, param3->className) + progLangObjectReferenceDelimiter2[progLang] + progLangAddCondition[progLang] + progLangOpenParameterSpace[progLang] + generateCodeConditionPairText(param2->name, generatePointerText(param2->className, progLang), param2->instanceName, generatePointerText(param3->className, progLang), param3->instanceName, progLang) + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//context1->param1->param2param3ConditionList.insert(pair<param2className*, param3className*>(param2, param3));
	printLine(codeBlockText, level, code);
	#endif
}
#ifdef NLC_USE_LIBRARY_BASE_EXTENDED
void generateCodeAddConditionExecuteFunction(NLCitem* param1, NLCitem* param2, NLCitem* param3, int progLang, string* code, int level)
{
	string contextParam1 = generateStringFromContextVector(&(param1->context), progLang);
	string codeBlockTextTemplateDefinition = progLangTemplateUsePart1[progLang] + param1->className + progLangTemplateUseClassSeparator[progLang] + param2->className + progLangTemplateUseClassSeparator[progLang] + param3->className + progLangTemplateUsePart2[progLang]; 	//<param1class, param2class, param3class>
	string codeBlockExecuteFunctionText = "";
	codeBlockExecuteFunctionText = codeBlockExecuteFunctionText + NLC_USE_LIBRARY_BASE_EXTENDED_FUNCTION_NAME_ADD_CONDITION + codeBlockTextTemplateDefinition + progLangOpenParameterSpace[progLang] + contextParam1 + param1->instanceName + progLangClassMemberFunctionParametersNext[progLang] + generateCodeListPointer(contextParam1 + param1->instanceName + progLangObjectReferenceDelimiter[progLang] + generateConditionListName(param2->className, param3->className), progLang) + progLangClassMemberFunctionParametersNext[progLang] + progLangStringOpenClose[progLang] + param2->name + progLangStringOpenClose[progLang] + progLangClassMemberFunctionParametersNext[progLang] + param3->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//addCondition<param1class, param2class, param3class>(context1->param1, &(context1->param1.param2param3ConditionList), "param2", param3);
	printLine(codeBlockExecuteFunctionText, level, code);	
}
#endif
#ifdef NLC_USE_NON_LIBRARY_FUNCTIONS_EXTENDED
void generateCodeAddConditionNewFunction(int progLang, string* code, int level)
{
	#ifdef NLC_USE_ENUM_LISTS
	cout << "NLC_USE_NON_LIBRARY_FUNCTIONS_EXTENDED:generateCodeAddConditionNewFunction{} error: does not support NLC_USE_ENUM_LISTS, use NLC_USE_LIBRARY:NLC_USE_LIBRARY_BASE_EXTENDED instead (NLClibraryBase.cpp)" << endl;
	#else
	string templateName1 = "E1";
	string templateName2 = "E2";
	string templateName3 = "E3";
	NLCitem param1(templateName1, NLC_ITEM_TYPE_OBJECT);
	NLCitem param2(templateName2, NLC_ITEM_TYPE_OBJECT);
	NLCitem param2(templateName3, NLC_ITEM_TYPE_OBJECT);
	param1->instanceName = templateName1 + generateEntityListAppendName();
	param2->instanceName = templateName2 + generateEntityListAppendName();
	param3->instanceName = templateName3 + generateEntityListAppendName();

	string codeBlockTextTemplateHeader = progLangTemplateHeaderPart1[progLang] + progLangTemplateHeaderClassType[progLang] + templateName1 + progLangTemplateUseClassSeparator[progLang] + progLangTemplateHeaderClassType[progLang] + templateName2 + progLangTemplateUseClassSeparator[progLang] + progLangTemplateHeaderClassType[progLang] + templateName3 + progLangTemplateHeaderPart2[progLang];  //template <class E1, class E2>
	string codeBlockTextFunctionHeader = progLangClassMemberFunctionTypeDefault[progLang] + NLC_USE_LIBRARY_BASE_EXTENDED_FUNCTION_NAME_ADD_CONDITION + progLangOpenParameterSpace[progLang] +  generateCodeEntityDefinitionText(param1, progLang) + progLangParameterSpaceNextParam[progLang] + generateCodeConditionListDefinitionText(param2, param3, progLang) + progLangParameterSpaceNextParam[progLang] + generateCodeClassNameVariableDefinitionText(param2, progLang) + progLangParameterSpaceNextParam[progLang] + generateCodeEntityDefinitionText(param3, progLang) + progLangCloseParameterSpace[progLang];	//void addCondition(E1* E1Instance, unordered_map<E2*, E3*>* E2E3conditionList, string E2className, E3* E3Instance)

	int q = 0;
	printLine("", level+q, code);
	printLine(codeBlockTextTemplateHeader, level+q, code);
	printLine(codeBlockTextFunctionHeader, level+q, code);
	printLine(progLangOpenBlock[progLang], level+q, code);
		
	q++;		
	string codeBlockTextCreate2 = generateCodeNewEntity(param2, progLang);
	printLine(codeBlockTextCreate2, level+q, code);
	string codeBlockText = generateConditionListName(param2, param3) + progLangObjectReferenceDelimiter2[progLang] + progLangAddCondition[progLang] + progLangOpenParameterSpace[progLang] + generateCodeConditionPairText(param2->name, generatePointerText(param2->className, progLang), param2->instanceName, generatePointerText(param3->className, progLang), param3->instanceName, progLang) + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//param2param3ConditionList.insert(pair<param2className*, param3className*>(param2, param3));
	printLine(codeBlockText, level+q, code);	

	q--;
	printLine(progLangCloseBlock[progLang], level+q, code);	
	#endif
}
#endif

void generateCodeRemoveCondition(NLCitem* param1, NLCitem* param2, NLCitem* param3, int progLang, string* code, int level)
{
	#ifdef NLC_USE_LIBRARY_BASE_EXTENDED
	generateCodeRemoveConditionExecuteFunction(param1, param2, param3, progLang, code, level);
	#else
	FINISHTHIS
	//printLine(codeBlockText, level, code);
	#endif
}
void generateCodeRemoveConditions(NLCitem* param1, NLCitem* param2, NLCitem* param3, int progLang, string* code, int level)
{
	#ifdef NLC_USE_LIBRARY_BASE_EXTENDED
	generateCodeRemoveConditionsExecuteFunction(param1, param2, param3, progLang, code, level);
	#else
	string codeBlockText = contextParam1 + param1->instanceName + progLangObjectReferenceDelimiter[progLang] + generateConditionListName(param2->className,  param3->className) + progLangObjectReferenceDelimiter2[progLang] + progLangRemoveConditions[progLang] + progLangEndLine[progLang];	//context1->param1->param2param3ConditionList.clear();
	printLine(codeBlockText, level, code);
	#endif
}
#ifdef NLC_USE_LIBRARY_BASE_EXTENDED
void generateCodeRemoveConditionExecuteFunction(NLCitem* param1, NLCitem* param2, NLCitem* param3, int progLang, string* code, int level)
{
	string contextParam1 = generateStringFromContextVector(&(param1->context), progLang);
	string codeBlockTextTemplateDefinition = progLangTemplateUsePart1[progLang] + param1->className + progLangTemplateUseClassSeparator[progLang] + param2->className + progLangTemplateUseClassSeparator[progLang] + param3->className + progLangTemplateUsePart2[progLang]; 	//<param1class, param2class, param3class>
	string codeBlockExecuteFunctionText = "";
	codeBlockExecuteFunctionText = codeBlockExecuteFunctionText + NLC_USE_LIBRARY_BASE_EXTENDED_FUNCTION_NAME_REMOVE_CONDITION + codeBlockTextTemplateDefinition + progLangOpenParameterSpace[progLang] + contextParam1 + param1->instanceName + progLangClassMemberFunctionParametersNext[progLang] + generateCodeListPointer(contextParam1 + param1->instanceName + progLangObjectReferenceDelimiter[progLang] + generateConditionListName(param2->className, param3->className), progLang) + progLangClassMemberFunctionParametersNext[progLang] + progLangStringOpenClose[progLang] + param2->name + progLangStringOpenClose[progLang] + progLangClassMemberFunctionParametersNext[progLang] + param3->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//removeCondition<param1class, param2class, param3class>(context1->param1, &(context1->param1.param2param3ConditionList), "param2", param3);
	printLine(codeBlockExecuteFunctionText, level, code);	
}
void generateCodeRemoveConditionsExecuteFunction(NLCitem* param1, NLCitem* param2, NLCitem* param3, int progLang, string* code, int level)
{
	string contextParam1 = generateStringFromContextVector(&(param1->context), progLang);
	string codeBlockTextTemplateDefinition = progLangTemplateUsePart1[progLang] + param1->className + progLangTemplateUseClassSeparator[progLang] + param2->className + progLangTemplateUseClassSeparator[progLang] + param3->className + progLangTemplateUsePart2[progLang]; 	//<param1class, param2class, param3class>
	string codeBlockExecuteFunctionText = "";
	codeBlockExecuteFunctionText = codeBlockExecuteFunctionText + NLC_USE_LIBRARY_BASE_EXTENDED_FUNCTION_NAME_REMOVE_CONDITIONS + codeBlockTextTemplateDefinition + progLangOpenParameterSpace[progLang] + contextParam1 + param1->instanceName + progLangClassMemberFunctionParametersNext[progLang] + generateCodeListPointer(contextParam1 + param1->instanceName + progLangObjectReferenceDelimiter[progLang] + generateConditionListName(param2->className, param3->className), progLang) + progLangClassMemberFunctionParametersNext[progLang] + progLangStringOpenClose[progLang] + param2->name + progLangStringOpenClose[progLang] + progLangClassMemberFunctionParametersNext[progLang] + param3->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//removeConditions<param1class, param2class, param3class>(context1->param1, &(context1->param1.param2param3ConditionList), "param2", param3);
	printLine(codeBlockExecuteFunctionText, level, code);	
}
#endif


void generateCodeAddActionSubject(NLCitem* functionArgument, NLCitem* functionOwnerArgument, int progLang, string* code, int level)
{
	#ifdef NLC_USE_LIBRARY_BASE_EXTENDED
	generateCodeAddActionSubjectExecuteFunction(functionArgument, functionOwnerArgument, progLang, code, level);
	#else
	string codeBlockTextAddAction = functionOwnerArgument->instanceName + progLangObjectReferenceDelimiter[progLang] + generateActionListName(functionArgument->className) + progLangObjectReferenceDelimiter2[progLang] + progLangAddEntityToList[progLang] + progLangOpenParameterSpace[progLang] + functionArgument->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//actionSubject1->actionClassActionList.push_back(action1);
	printLine(codeBlockTextAddAction, level, code);
	string codeBlockTextAddAction2 = functionArgument->instanceName + progLangObjectReferenceDelimiter[progLang] + generateActionSubjectListName(functionOwnerArgument->className) + progLangObjectReferenceDelimiter2[progLang] + progLangAddEntityToList[progLang] + progLangOpenParameterSpace[progLang] + functionOwnerArgument->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//action1->actionSubjectClassActionSubjectList.push_back(actionSubject1);
	printLine(codeBlockTextAddAction2, level, code);
	#endif
}
#ifdef NLC_USE_LIBRARY_BASE_EXTENDED
void generateCodeAddActionSubjectExecuteFunction(NLCitem* functionArgument, NLCitem* functionOwnerArgument, int progLang, string* code, int level)
{
	string codeBlockTextTemplateDefinition = progLangTemplateUsePart1[progLang] + functionArgument->className + progLangTemplateUseClassSeparator[progLang] + functionOwnerArgument->className + progLangTemplateUsePart2[progLang]; 	//<param1class, param2class>
	string codeBlockExecuteFunctionText = "";
	codeBlockExecuteFunctionText = codeBlockExecuteFunctionText + NLC_USE_LIBRARY_BASE_EXTENDED_FUNCTION_NAME_ADD_ACTIONSUBJECT + codeBlockTextTemplateDefinition + progLangOpenParameterSpace[progLang] + functionArgument->instanceName + progLangClassMemberFunctionParametersNext[progLang] + functionOwnerArgument->instanceName + progLangClassMemberFunctionParametersNext[progLang] + generateCodeListPointer(functionOwnerArgument->instanceName + progLangObjectReferenceDelimiter[progLang] + generateActionListName(functionArgument->className), progLang) + progLangClassMemberFunctionParametersNext[progLang] + generateCodeListPointer(functionArgument->instanceName + progLangObjectReferenceDelimiter[progLang] + generateActionSubjectListName(functionOwnerArgument->className), progLang) + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//addActionSubject<param1class, param2class>(functionArgument, functionOwnerArgument, &(functionOwnerArgument->actionClassActionList), &(functionArgument->actionSubjectClassActionSubjectList));
	printLine(codeBlockExecuteFunctionText, level, code);	
}
#endif

void generateCodeAddActionObject(NLCitem* functionArgument, NLCitem* functionObjectArgument, int progLang, string* code, int level)
{
	#ifdef NLC_USE_LIBRARY_BASE_EXTENDED
	generateCodeAddActionObjectExecuteFunction(functionArgument, functionObjectArgument, progLang, code, level);
	#else
	string codeBlockTextAddAction = functionObjectArgument->instanceName + progLangObjectReferenceDelimiter[progLang] + generateActionIncomingListName(functionArgument->className) + progLangObjectReferenceDelimiter2[progLang] + progLangAddEntityToList[progLang] + progLangOpenParameterSpace[progLang] + functionArgument->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//actionObject1->actionClassActionIncomingList.push_back(action1);
	printLine(codeBlockTextAddAction, level, code);
	string codeBlockTextAddAction2 = functionArgument->instanceName + progLangObjectReferenceDelimiter[progLang] + generateActionObjectListName(functionObjectArgument->className) + progLangObjectReferenceDelimiter2[progLang] + progLangAddEntityToList[progLang] + progLangOpenParameterSpace[progLang] + functionObjectArgument->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//action1->actionObjectClassActionObjectList.push_back(actionSubject1);
	printLine(codeBlockTextAddAction2, level, code);
	#endif
}
#ifdef NLC_USE_LIBRARY_BASE_EXTENDED
void generateCodeAddActionObjectExecuteFunction(NLCitem* functionArgument, NLCitem* functionObjectArgument, int progLang, string* code, int level)
{
	string codeBlockTextTemplateDefinition = progLangTemplateUsePart1[progLang] + functionArgument->className + progLangTemplateUseClassSeparator[progLang] + functionObjectArgument->className + progLangTemplateUsePart2[progLang]; 	//<param1class, param2class>
	string codeBlockExecuteFunctionText = "";
	codeBlockExecuteFunctionText = codeBlockExecuteFunctionText + NLC_USE_LIBRARY_BASE_EXTENDED_FUNCTION_NAME_ADD_ACTIONOBJECT + codeBlockTextTemplateDefinition + progLangOpenParameterSpace[progLang] + functionArgument->instanceName + progLangClassMemberFunctionParametersNext[progLang] + functionObjectArgument->instanceName + progLangClassMemberFunctionParametersNext[progLang] + generateCodeListPointer(functionObjectArgument->instanceName + progLangObjectReferenceDelimiter[progLang] + generateActionIncomingListName(functionArgument->className), progLang) + progLangClassMemberFunctionParametersNext[progLang] + generateCodeListPointer(functionArgument->instanceName + progLangObjectReferenceDelimiter[progLang] + generateActionObjectListName(functionObjectArgument->className), progLang) + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//addActionObject<param1class, param2class>(functionArgument, functionObjectArgument, &(functionObjectArgument->generateActionIncomingListName), &(functionArgument->actionObjectClassActionObjectList));
	printLine(codeBlockExecuteFunctionText, level, code);	
}
#endif



void generateCodeAddNewEntityToLocalList(NLCitem* param1, int progLang, string* code, int level)
{
	#ifdef NLC_USE_LIBRARY_BASE_EXTENDED
	generateCodeAddNewEntityToLocalListExecuteFunction(param1, progLang, code, level);
	#else
	string codeBlockTextCreate = generateCodeNewEntity(param1, progLang);		//param1className* param1 = new param1className();
	printLine(codeBlockTextCreate, level, code);
	string codeBlockText = generateLocalListName(param1) + progLangObjectReferenceDelimiter2[progLang] + progLangAddEntityToList[progLang] + progLangOpenParameterSpace[progLang] + param1->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//param1instanceList.push_back(param1);
	printLine(codeBlockText, level, code);
	#endif
}
#ifdef NLC_USE_LIBRARY_BASE_EXTENDED
void generateCodeAddNewEntityToLocalListExecuteFunction(NLCitem* param1, int progLang, string* code, int level)
{
	string codeBlockTextTemplateDefinition = progLangTemplateUsePart1[progLang] + param1->className + progLangTemplateUsePart2[progLang]; 	//<param1class>
	string codeBlockExecuteFunctionText = "";
	codeBlockExecuteFunctionText = generateCodeEntityDefinitionText(param1, progLang) + progLangEquals[progLang] + codeBlockExecuteFunctionText + NLC_USE_LIBRARY_BASE_EXTENDED_FUNCTION_NAME_ADD_NEW_ENTITY_TO_LOCAL_LIST + codeBlockTextTemplateDefinition + progLangOpenParameterSpace[progLang] + generateCodeListPointer(generateLocalListName(param1), progLang) + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//param1class* param1 = addNewEntityToLocalList<param1class>(&(param1localList));
	printLine(codeBlockExecuteFunctionText, level, code);
}
#endif

void generateCodeAddEntityToLocalList(NLCitem* param1, NLCitem* param2, int progLang, string* code, int level)
{
	#ifdef NLC_USE_LIBRARY_BASE_EXTENDED
	generateCodeAddEntityToLocalListExecuteFunction(param1, param2, progLang, code, level);
	#else
	string codeBlockText = generateLocalListName(param1) + progLangObjectReferenceDelimiter2[progLang] + progLangAddEntityToList[progLang] + progLangOpenParameterSpace[progLang] + param2->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//param1instanceList.push_back(param2);	
	printLine(codeBlockText, level, code);
	#endif
}
#ifdef NLC_USE_LIBRARY_BASE_EXTENDED
void generateCodeAddEntityToLocalListExecuteFunction(NLCitem* param1, NLCitem* param2, int progLang, string* code, int level)
{
	string codeBlockTextTemplateDefinition = progLangTemplateUsePart1[progLang] + param1->className + progLangTemplateUsePart2[progLang]; 	//<param1class>
	string codeBlockExecuteFunctionText = "";
	codeBlockExecuteFunctionText = codeBlockExecuteFunctionText + NLC_USE_LIBRARY_BASE_EXTENDED_FUNCTION_NAME_ADD_ENTITY_TO_LOCAL_LIST + codeBlockTextTemplateDefinition + progLangOpenParameterSpace[progLang] + generateCodeListPointer(generateLocalListName(param1), progLang) + progLangClassMemberFunctionParametersNext[progLang] + param2->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//addEntityToLocalList<param1class>(&(param1localList), param2);
	printLine(codeBlockExecuteFunctionText, level, code);
}
#endif


