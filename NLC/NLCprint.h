/*******************************************************************************
 *
 * This file is part of BAIPROJECT.
 *
 * BAIPROJECT is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License version 3
 * only, as published by the Free Software Foundation.
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
 * File Name: NLCprint.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2014 Baxter AI (baxterai.com)
 * Project: Natural Language Programming Interface (compiler)
 * Project Version: 1f9a 11-April-2014
 * Requirements: requires text parsed by NLP Parser (eg Relex; available in .CFF format <relations>)
 *
 *******************************************************************************/


#ifndef HEADER_NLC_PRINT
#define HEADER_NLC_PRINT

#include <iostream>
#include <fstream>
#include <ctime>
#include <cstring>
#include <cstdlib>	//for random number generation
#include <cmath>
#include <string>
#include <vector>
using namespace std;

#include "NLCcodeBlockClass.h"
#include "NLCclassDefinitionClass.h"
	
#define NLC_PROGRAMMING_LANGUAGE_CPP (0)
#define NLC_PROGRAMMING_LANGUAGE_JAVA (1)
#define NLC_PROGRAMMING_LANGUAGE_VISUALBASIC (2)
#define NLC_PROGRAMMING_LANGUAGE_CSHARP (3)
#define NLC_PROGRAMMING_LANGUAGE_PHP (4)
#define NLC_PROGRAMMING_LANGUAGE_PERL (5)
#define NLC_PROGRAMMING_LANGUAGE_PYTHON (6)
#define NLC_PROGRAMMING_LANGUAGE_DEFAULT (NLC_PROGRAMMING_LANGUAGE_CPP)
#define NLC_NUMBER_OF_PROGRAMMING_LANGUAGES (7)	//this needs to be moved to NLCglobalDefs.h

//from NLCclassDefinitionClass.h
static string progLangClassTitlePrepend[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"class ", "class ", "class ", "class ", "class ", "class ", "class "};
static string progLangOpenClass[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"{", "{", "{", "{", "{", "{", "{"};
static string progLangCloseClass[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"};", "};", "};", "};", "};", "};", "};"};
static string progLangClassIntro[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"public:", "public:", "public:", "public:", "public:", "public:", "public:"};
static string progLangClassConstructorDestructorAppend[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"(void);", "(void);", "(void);", "(void);", "(void);", "(void);", "(void);"};
static string progLangClassDestructorPrepend[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"~", "~", "~", "~", "~", "~", "~"};
static string progLangClassListTypeStart[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"vector<", "vector<", "vector<", "vector<", "vector<", "vector<", "vector<"};
static string progLangClassListTypeEnd[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"> ", "> ", "> ", "> ", "> ", "> ", "> "};
static string progLangClassList2DTypeStart[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"unordered_map<", "unordered_map<", "unordered_map<", "unordered_map<", "unordered_map<", "unordered_map<", "unordered_map<"};
static string progLangClassList2DTypeMiddle[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {", ", ", ", ", ", ", ", ", ", ", ", ", "};
static string progLangClassList2DTypeConditionTypeVar[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"string", "string", "string", "string", "string", "string", "string"};
static string progLangClassPairTypeStart[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"pair<", "pair<", "pair<", "pair<", "pair<", "pair<", "pair<"};
static string progLangClassPairTypeEnd[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {">", ">", ">", ">", ">", ">", ">"};

static string progLangClassNameVariableType[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"string ", "string ", "string ", "string ", "string ", "string ", "string "};
static string progLangClassNameVariableName[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"name = ", "name = ", "name = ", "name = ", "name = ", "name = ", "name = "};
static string progLangClassMemberFunctionType[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"void ", "void ", "void ", "void ", "void ", "void ", "void "};
static string progLangClassMemberFunctionParameters[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"()", "()", "()", "()", "()", "()", "()"};
static string progLangClassMemberFunctionParametersOpen[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"(", "(", "(", "(", "(", "(", "("};
static string progLangClassMemberFunctionParametersClose[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {")", ")", ")", ")", ")", ")", ")"};
static string progLangClassMemberFunctionParametersNext[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {", ", ", ", ", ", ", ", ", ", ", ", ", "};
static string progLangClassInheritanceHeader[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"public ", "public ", "public ", "public ", "public ", "public ", "public "};
static string progLangStringOpenClose[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"\"", "\"", "\"", "\"", "\"", "\"", "\""};

static string progLangDynamicCastStart[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"dynamic_cast<", "dynamic_cast<", "dynamic_cast<", "dynamic_cast<", "dynamic_cast<", "dynamic_cast<", "dynamic_cast<"};
static string progLangDynamicCastEnd[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"*>", "*>", "*>", "*>", "*>", "*>", "*>"};
static string progLangFunctionOwnerClassDelimiter[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"::", "::", "::", "::", "::", "::", "::"};

//from NLCcodeBlockClass.h
static string progLangOpenBlock[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"{", "{", "{", "{", "{", "{", "{"};
static string progLangCloseBlock[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"}", "}", "}", "}", "}", "}", "}"};
static string progLangObjectReferenceDelimiter[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"->", "->", "->", "->", "->", "->", "->"};
static string progLangFunctionReferenceDelimiter[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {".", ".", ".", ".", ".", ".", "."};
static string progLangOpenParameterSpace[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"(", "(", "(", "(", "(", "(", "("};
static string progLangCloseParameterSpace[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {")", ")", ")", ")", ")", ")", ")"};
static string progLangEndLine[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {";", ";", ";", ";", ";", ";", ";"};
static string progLangFor[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"for", "for", "for", "for", "for", "for", "for"};
static string progLangIf[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"if", "if", "if", "if", "if", "if", "if"};
static string progLangObjectCheckHasPropertyFunction[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"hasObjectOfClass", "hasObjectOfClass", "hasObjectOfClass", "hasObjectOfClass", "hasObjectOfClass", "hasObjectOfClass", "hasObjectOfClass"};
static string progLangParameterSpaceNextParam[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {",", ",", ",", ",", ",", ",", ","};
static string progLangPointer[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"*", "*", "*", "*", "*", "*", "*"};
static string progLangNot[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"!", "!", "!", "!", "!", "!", "!"};
static string progLangEquals[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {" = ", " = ", " = ", " = ", " = ", " = ", " = "};
static string progLangForIterPart1[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"(vector<", "(vector<", "(vector<", "(vector<", "(vector<", "(vector<", "(vector<"};
static string progLangForIterPart2[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"*>::iterator iter = ", "*>::iterator iter = ", "*>::iterator iter = ", "*>::iterator iter = ", "*>::iterator iter = ", "*>::iterator iter = ", "*>::iterator iter = "};
static string progLangForIterPart3[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {".begin(); iter < ", ".begin(); iter < ", ".begin(); iter < ", ".begin(); iter < ", ".begin(); iter < ", ".begin(); iter < ", ".begin(); iter < "};
static string progLangForIterPart4[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {".end(); iter++)", ".end(); iter++)", ".end(); iter++)", ".end(); iter++)", ".end(); iter++)", ".end(); iter++)", ".end(); iter++)"};
static string progLangForIterName[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"iter", "iter", "iter", "iter", "iter", "iter", "iter"};

static string progLangNewObject[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"new ", "new ", "new ", "new ", "new ", "new ", "new "};
static string progLangAddProperty[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"push_back", "push_back", "push_back", "push_back", "push_back", "push_back", "push_back"};
static string progLangAddCondition[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"insert", "insert", "insert", "insert", "insert", "insert", "insert"};
static string progLangFindProperty[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"empty", "empty", "empty", "empty", "empty", "empty", "empty"};
static string progLangFindCondition[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"empty", "empty", "empty", "empty", "empty", "empty", "empty"};

static string progLangMainEntryPointFunctionName[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"main", "main", "main", "main", "main", "main", "main"};

/*
#define NLC_ITEM_TYPE_PROPERTYLISTADDFUNCTION "addProperty"
#define NLC_ITEM_TYPE_CONDITIONLISTADDFUNCTION "addCondition"
#define NLC_ITEM_TYPE_PROPERTYLISTFINDFUNCTION "findProperty"
#define NLC_ITEM_TYPE_CONDITIONLISTFINDFUNCTION "findCondition"
*/

#ifndef NLC_SUPPORT_INPUT_FILE_LISTS
bool printCode(NLCcodeblock * firstCodeBlockInLevel, vector<NLCclassDefinition *> * classDefinitionList, int progLang, string * code);
#endif	

#endif
