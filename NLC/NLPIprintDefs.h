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
 * File Name: NLPIprintDefs.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2013 Baxter AI (baxterai.com)
 * Project: Natural Language Programming Interface (compiler)
 * Project Version: 1e8c 24-November-2013
 * Requirements: requires text parsed by NLP Parser (eg Relex; available in .CFF format <relations>)
 *
 *******************************************************************************/


#ifndef HEADER_NLPI_PRINT_DEFS
#define HEADER_NLPI_PRINT_DEFS

#include <iostream>
#include <fstream>
#include <ctime>
#include <cstring>
#include <cstdlib>	//for random number generation
#include <cmath>
#include <string>
#include <vector>
using namespace std;

#include "NLPIglobalDefs.h"

#define NLPI_PROGRAMMING_LANGUAGE_CPP (0)
#define NLPI_PROGRAMMING_LANGUAGE_JAVA (1)
#define NLPI_PROGRAMMING_LANGUAGE_VISUALBASIC (2)
#define NLPI_PROGRAMMING_LANGUAGE_CSHARP (3)
#define NLPI_PROGRAMMING_LANGUAGE_PHP (4)
#define NLPI_PROGRAMMING_LANGUAGE_PERL (5)
#define NLPI_PROGRAMMING_LANGUAGE_PYTHON (6)
#define NLPI_PROGRAMMING_LANGUAGE_DEFAULT (NLPI_PROGRAMMING_LANGUAGE_CPP)
#define NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES (7)	//this needs to be moved to NLPIglobalDefs.h

#define NLPI_ITEM_TYPE_TEMPVAR_APPENDITION "Temp"
#define NLPI_ITEM_TYPE_PROPERTYLISTVAR_APPENDITION "PropertyList"
#define NLPI_ITEM_TYPE_CONDITIONLISTVAR_APPENDITION "ConditionList"
#define NLPI_ITEM_TYPE_DEFINITIONLISTVAR_APPENDITION "DefinitionList"
#define NLPI_ITEM_TYPE_CONDITIONPAIRVAR_APPENDITION "ConditionPair"

//from NLPIclassDefinition.h
static string progLangClassTitlePrepend[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"class ", "class ", "class ", "class ", "class ", "class ", "class "};
static string progLangOpenClass[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"{", "{", "{", "{", "{", "{", "{"};
static string progLangCloseClass[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"};", "};", "};", "};", "};", "};", "};"};
static string progLangClassIntro[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"public:", "public:", "public:", "public:", "public:", "public:", "public:"};
static string progLangClassConstructorDestructorAppend[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"(void);", "(void);", "(void);", "(void);", "(void);", "(void);", "(void);"};
static string progLangClassDestructorPrepend[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"~", "~", "~", "~", "~", "~", "~"};
static string progLangClassListTypeStart[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"vector<", "vector<", "vector<", "vector<", "vector<", "vector<", "vector<"};
static string progLangClassListTypeEnd[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"> ", "> ", "> ", "> ", "> ", "> ", "> "};
static string progLangClassList2DTypeStart[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"unordered_map<", "unordered_map<", "unordered_map<", "unordered_map<", "unordered_map<", "unordered_map<", "unordered_map<"};
static string progLangClassList2DTypeMiddle[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {", ", ", ", ", ", ", ", ", ", ", ", ", "};
static string progLangClassList2DTypeConditionTypeVar[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"string", "string", "string", "string", "string", "string", "string"};
static string progLangClassPairTypeStart[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"pair<", "pair<", "pair<", "pair<", "pair<", "pair<", "pair<"};
static string progLangClassPairTypeEnd[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {">", ">", ">", ">", ">", ">", ">"};

static string progLangClassNameVariableType[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"string ", "string ", "string ", "string ", "string ", "string ", "string "};
static string progLangClassNameVariableName[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"name = ", "name = ", "name = ", "name = ", "name = ", "name = ", "name = "};
static string progLangClassMemberFunctionType[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"void ", "void ", "void ", "void ", "void ", "void ", "void "};
static string progLangClassMemberFunctionParameters[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"()", "()", "()", "()", "()", "()", "()"};
static string progLangClassMemberFunctionParametersOpen[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"(", "(", "(", "(", "(", "(", "("};
static string progLangClassMemberFunctionParametersClose[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {")", ")", ")", ")", ")", ")", ")"};
static string progLangClassMemberFunctionParametersNext[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {", ", ", ", ", ", ", ", ", ", ", ", ", "};
static string progLangClassInheritanceHeader[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"public ", "public ", "public ", "public ", "public ", "public ", "public "};
static string progLangStringOpenClose[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"\"", "\"", "\"", "\"", "\"", "\"", "\""};

static string progLangDynamicCastStart[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"dynamic_cast<", "dynamic_cast<", "dynamic_cast<", "dynamic_cast<", "dynamic_cast<", "dynamic_cast<", "dynamic_cast<"};
static string progLangDynamicCastEnd[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"*>", "*>", "*>", "*>", "*>", "*>", "*>"};
static string progLangFunctionOwnerClassDelimiter[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"::", "::", "::", "::", "::", "::", "::"};

//from NLPIcodeBlock.h
static string progLangOpenBlock[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"{", "{", "{", "{", "{", "{", "{"};
static string progLangCloseBlock[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"}", "}", "}", "}", "}", "}", "}"};
static string progLangObjectReferenceDelimiter[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"->", "->", "->", "->", "->", "->", "->"};
static string progLangFunctionReferenceDelimiter[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {".", ".", ".", ".", ".", ".", "."};
static string progLangOpenParameterSpace[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"(", "(", "(", "(", "(", "(", "("};
static string progLangCloseParameterSpace[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {")", ")", ")", ")", ")", ")", ")"};
static string progLangEndLine[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {";", ";", ";", ";", ";", ";", ";"};
static string progLangFor[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"for", "for", "for", "for", "for", "for", "for"};
static string progLangIf[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"if", "if", "if", "if", "if", "if", "if"};
static string progLangObjectCheckHasPropertyFunction[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"hasObjectOfClass", "hasObjectOfClass", "hasObjectOfClass", "hasObjectOfClass", "hasObjectOfClass", "hasObjectOfClass", "hasObjectOfClass"};
static string progLangParameterSpaceNextParam[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {",", ",", ",", ",", ",", ",", ","};
static string progLangPointer[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"*", "*", "*", "*", "*", "*", "*"};
static string progLangNot[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"!", "!", "!", "!", "!", "!", "!"};
static string progLangEquals[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {" = ", " = ", " = ", " = ", " = ", " = ", " = "};
static string progLangForIterPart1[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"(", "(", "(", "(", "(", "(", "("};
static string progLangForIterPart2[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"::iterator iter = ", "::iterator iter = ", "::iterator iter = ", "::iterator iter = ", "::iterator iter = ", "::iterator iter = ", "::iterator iter = "};
static string progLangForIterPart3[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {".begin(); iter < ", ".begin(); iter < ", ".begin(); iter < ", ".begin(); iter < ", ".begin(); iter < ", ".begin(); iter < ", ".begin(); iter < "};
static string progLangForIterPart4[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {".end(); iter++)", ".end(); iter++)", ".end(); iter++)", ".end(); iter++)", ".end(); iter++)", ".end(); iter++)", ".end(); iter++)"};
static string progLangForIterName[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"iter", "iter", "iter", "iter", "iter", "iter", "iter"};
static string progLangForIterConditionObjectReference[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"->second", "->second", "->second", "->second", "->second", "->second", "->second"};

static string progLangNewObject[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"new ", "new ", "new ", "new ", "new ", "new ", "new "};
static string progLangAddProperty[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"push_back", "push_back", "push_back", "push_back", "push_back", "push_back", "push_back"};
static string progLangAddCondition[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"insert", "insert", "insert", "insert", "insert", "insert", "insert"};
static string progLangFindProperty[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"empty", "empty", "empty", "empty", "empty", "empty", "empty"};
static string progLangFindCondition[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"empty", "empty", "empty", "empty", "empty", "empty", "empty"};

static string progLangMainEntryPointFunctionName[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"main", "main", "main", "main", "main", "main", "main"};

void printLine(string command, int level, string * code);
string generatePropertyListName(string propertyClassName);
string generateConditionListName(string conditionClassName, string conditionObjectClassName);
string generateConditionPairName(string conditionClassName, string conditionObjectClassName);
string generateCodePropertyListDefinitionText(string targetClassName, int progLang);
	string generateCodePropertyListDefinitionTypeText(string targetClassName, int progLang);
string generateCodeConditionListDefinitionText(string conditionClassName, string conditionObjectClassName, int progLang);
	string generateCodeConditionListDefinitionTypeText(string conditionClassName, string conditionObjectClassName, int progLang);


#endif
