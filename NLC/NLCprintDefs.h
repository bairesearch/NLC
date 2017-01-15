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
 * File Name: NLCprintDefs.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2015 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 1q13a 23-August-2015
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/


#ifndef HEADER_NLC_PRINT_DEFS
#define HEADER_NLC_PRINT_DEFS

#include "NLCglobalDefs.h"
#include "NLCitemClass.h"

//based on GIAentityNode.h;
#ifdef NLC_NONOO
#define NLCNONOO_GENERIC_ENTITY_NODE_NAME "GIAentityNode"
#define GIA_ENTITYNODECLASS_ENTITYNAME_NAME "entityName"
#define GIA_ENTITYNODECLASS_PROPERTYNODELIST_NAME "propertyNodeList"
#define GIA_ENTITYNODECLASS_PROPERTYNODEREVERSELIST_NAME "propertyNodeReverseList"
#define GIA_ENTITYNODECLASS_CONDITIONNODELIST_NAME "conditionNodeList"
#define GIA_ENTITYNODECLASS_INCOMINGCONDITIONNODELIST_NAME "incomingConditionNodeList"
#define GIA_ENTITYNODECLASS_CONDITIONSUBJECTLIST_NAME "conditionSubjectEntity"
#define GIA_ENTITYNODECLASS_CONDITIONOBJECTLIST_NAME "conditionObjectEntity"
#define GIA_ENTITYNODECLASS_ACTIONNODELIST_NAME "actionNodeList"
#define GIA_ENTITYNODECLASS_INCOMINGACTIONNODELIST_NAME "incomingActionNodeList"
#define GIA_ENTITYNODECLASS_ACTIONSUBJECTLIST_NAME "actionSubjectEntity"
#define GIA_ENTITYNODECLASS_ACTIONOBJECTLIST_NAME "actionObjectEntity"
#endif

#ifdef NLC_USE_LIBRARY
#define NLC_USE_LIBRARY_ALL_PROPERTY_LIST_NAME "propertyLists"
#define NLC_USE_LIBRARY_ALL_PROPERTYINCOMING_LIST_NAME "propertyIncomingLists"
#define NLC_USE_LIBRARY_ALL_CONDITION_LIST_NAME "conditionLists"
#define NLC_USE_LIBRARY_ALL_CONDITIONINCOMING_LIST_NAME "conditionIncomingLists"
#define NLC_USE_LIBRARY_ALL_ACTION_LIST_NAME "actionLists"
#define NLC_USE_LIBRARY_ALL_ACTIONINCOMING_LIST_NAME "actionIncomingLists"
#define NLC_USE_LIBRARY_ALL_ACTIONOBJECT_LIST_NAME "actionObjectLists"
#define NLC_USE_LIBRARY_ALL_ACTIONSUBJECT_LIST_NAME "actionSubjectLists"
#endif


#define NLC_PROGRAMMING_LANGUAGE_CPP (0)
#define NLC_PROGRAMMING_LANGUAGE_JAVA (1)
#define NLC_PROGRAMMING_LANGUAGE_VISUALBASIC (2)
#define NLC_PROGRAMMING_LANGUAGE_CSHARP (3)
#define NLC_PROGRAMMING_LANGUAGE_PHP (4)
#define NLC_PROGRAMMING_LANGUAGE_PERL (5)
#define NLC_PROGRAMMING_LANGUAGE_PYTHON (6)
#define NLC_PROGRAMMING_LANGUAGE_DEFAULT (NLC_PROGRAMMING_LANGUAGE_CPP)
#define NLC_NUMBER_OF_PROGRAMMING_LANGUAGES (7)	//this needs to be moved to NLCglobalDefs.h

#define NLC_ITEM_TYPE_TEMP_VAR_APPENDITION "Temp"
#define NLC_ITEM_TYPE_LIST_VAR_APPENDITION "List"
#define NLC_ITEM_TYPE_TYPE_VAR_APPENDITION "Type"

#define NLC_ITEM_TYPE_CLASS_VAR_APPENDITION NLC_CLASS_NAME_APPEND //"Class"
#define NLC_ITEM_TYPE_PROPERTY_VAR_APPENDITION "Property"
#define NLC_ITEM_TYPE_CONDITION_VAR_APPENDITION "Condition"
#define NLC_ITEM_TYPE_DEFINITION_VAR_APPENDITION "Definition"
#define NLC_ITEM_TYPE_INSTANCE_VAR_APPENDITION "Instance"
#define NLC_ITEM_TYPE_PAIR_VAR_APPENDITION "Pair"

#define NLC_ITEM_TYPE_PROPERTYCOUNT_VAR_APPENDITION "PropertyCount"
//#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN
#define NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION "Category"
#ifdef NLC_ACTION_CATEGORY_LISTS
#define NLC_ITEM_TYPE_ACTIONCATEGORY_VAR_APPENDITION "ActionCategory"
#endif
//#endif
#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN
#define NLC_ITEM_TYPE_LOGICALCONDITION_VAR_APPENDITION "LogicalCondition"	//1j15b
#endif
#ifdef NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT
#define NLC_ITEM_TYPE_REFERENCECONTEXT_VAR_APPENDITION "referenceContext"
#endif
#ifdef NLC_USE_ADVANCED_REFERENCING_SUPPORT_ALIASES
#define NLC_ITEM_TYPE_ALIAS_VAR_APPENDITION "alias"
#endif
#define NLC_ITEM_TYPE_SUBJECTCATEGORY_VAR_APPENDITION "SubjectCategory"
#define NLC_ITEM_TYPE_OBJECTCATEGORY_VAR_APPENDITION "ObjectCategory"

#define NLC_ITEM_TYPE_CLASSLIST_VAR_APPENDITION NLC_ITEM_TYPE_CLASS_VAR_APPENDITION NLC_ITEM_TYPE_LIST_VAR_APPENDITION	//"ClassList"
#define NLC_ITEM_TYPE_PROPERTYLIST_VAR_APPENDITION NLC_ITEM_TYPE_PROPERTY_VAR_APPENDITION NLC_ITEM_TYPE_LIST_VAR_APPENDITION	//"PropertyList"
#define NLC_ITEM_TYPE_CONDITIONLIST_VAR_APPENDITION NLC_ITEM_TYPE_CONDITION_VAR_APPENDITION NLC_ITEM_TYPE_LIST_VAR_APPENDITION	//"ConditionList"
#define NLC_ITEM_TYPE_DEFINITIONLIST_VAR_APPENDITION NLC_ITEM_TYPE_DEFINITION_VAR_APPENDITION NLC_ITEM_TYPE_LIST_VAR_APPENDITION	//"DefinitionList"
#define NLC_ITEM_TYPE_INSTANCELIST_VAR_APPENDITION NLC_ITEM_TYPE_INSTANCE_VAR_APPENDITION NLC_ITEM_TYPE_LIST_VAR_APPENDITION	//"InstanceList"
#define NLC_ITEM_TYPE_CONDITIONPAIR_VAR_APPENDITION NLC_ITEM_TYPE_CONDITION_VAR_APPENDITION NLC_ITEM_TYPE_PAIR_VAR_APPENDITION	//"ConditionPair"

#define NLC_ITEM_TYPE_CATEGORYLIST_VAR_APPENDITION NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION NLC_ITEM_TYPE_LIST_VAR_APPENDITION	//"CategoryList"
#define NLC_ITEM_TYPE_REFERENCECONTEXTLEVELLIST_VAR_APPENDITION NLC_ITEM_TYPE_REFERENCECONTEXT_VAR_APPENDITION NLC_ITEM_TYPE_LIST_VAR_APPENDITION	//"referenceContextList"
#ifdef NLC_USE_ADVANCED_REFERENCING_SUPPORT_ALIASES
#define NLC_ITEM_TYPE_ALIASLIST_VAR_APPENDITION NLC_ITEM_TYPE_ALIAS_VAR_APPENDITION NLC_ITEM_TYPE_LIST_VAR_APPENDITION	//"aliasList"
#endif


//from NLCclassDefinitionClass.h
static string progLangClassTitlePrepend[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"class ", "class ", "class ", "class ", "class ", "class ", "class "};
static string progLangOpenClass[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"{", "{", "{", "{", "{", "{", "{"};
static string progLangCloseClass[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"};", "};", "};", "};", "};", "};", "};"};
static string progLangClassIntro[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"public:", "public:", "public:", "public:", "public:", "public:", "public:"};
static string progLangClassConstructorDestructorAppend[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"(void)", "(void)", "(void)", "(void)", "(void)", "(void)", "(void)"};
static string progLangClassDestructorPrepend[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"~", "~", "~", "~", "~", "~", "~"};
static string progLangClassListTypeStart[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"vector<", "vector<", "vector<", "vector<", "vector<", "vector<", "vector<"};
static string progLangClassListTypeEnd[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {">", ">", ">", ">", ">", ">", ">"};
static string progLangClassList2DTypeStart[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"vector<", "vector<", "vector<", "vector<", "vector<", "vector<", "vector<"};
static string progLangClassList2DTypeConditionTypeStringVar[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"string", "string", "string", "string", "string", "string", "string"};
static string progLangClassList2DMapTypeStart[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"unordered_map<", "unordered_map<", "unordered_map<", "unordered_map<", "unordered_map<", "unordered_map<", "unordered_map<"};
static string progLangClassList2DMapTypeMiddle[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {", ", ", ", ", ", ", ", ", ", ", ", ", "};
static string progLangClassPairTypeStart[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"pair<", "pair<", "pair<", "pair<", "pair<", "pair<", "pair<"};
static string progLangClassPairTypeEnd[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {">", ">", ">", ">", ">", ">", ">"};

static string progLangDependenciesStandardLibaries[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"#include <string>\n#include <vector>\n#include <stack>\n#include <unordered_map>\n#include <utility>\n#include <algorithm>\n#include <iostream>\nusing namespace std;\n", "", "", "", "", "", ""};
#ifdef NLC_USE_LIBRARY
static string progLangDependenciesNLClibary[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"#include \"NLClibrary.hpp\"", "", "", "", "", "", ""};
#endif
static string progLangIncludeStart[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"#include \"", "#include \"", "#include \"", "#include \"", "#include \"", "#include \"", "#include \""};
static string progLangIncludeEnd[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"\"", "\"", "\"", "\"", "\"", "\"", "\""};

static string progLangClassConstructorParameters[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"void", "void", "void", "void", "void", "void", "void"};

static string progLangClassNameVariableType[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"string ", "string ", "string ", "string ", "string ", "string ", "string "};
static string progLangClassNameVariableName[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"name", "name", "name", "name", "name", "name", "name"};
static string progLangClassNameVariableNameAppend[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"className", "className", "className", "className", "className", "className", "className"};
static string progLangClassNameVariableEquals[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {" = ", " = ", " = ", " = ", " = ", " = ", " = "};
static string progLangClassMemberFunctionTypeDefault[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"void ", "void ", "void ", "void ", "void ", "void ", "void "};
static string progLangClassMemberFunctionTypeBool[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"bool ", "bool ", "bool ", "bool ", "bool ", "bool ", "bool "};
static string progLangClassMemberFunctionParameters[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"()", "()", "()", "()", "()", "()", "()"};
static string progLangClassMemberFunctionParametersOpen[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"(", "(", "(", "(", "(", "(", "("};
static string progLangClassMemberFunctionParametersClose[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {")", ")", ")", ")", ")", ")", ")"};
static string progLangClassMemberFunctionParametersNext[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {", ", ", ", ", ", ", ", ", ", ", ", ", "};
static string progLangClassInheritanceHeader[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"public ", "public ", "public ", "public ", "public ", "public ", "public "};
static string progLangStringOpenClose[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"\"", "\"", "\"", "\"", "\"", "\"", "\""};

static string progLangStaticCastStart[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"static_cast<", "static_cast<", "static_cast<", "static_cast<", "static_cast<", "static_cast<", "static_cast<"};
static string progLangStaticCastEnd[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"*>", "*>", "*>", "*>", "*>", "*>", "*>"};
static string progLangDynamicCastStart[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"dynamic_cast<", "dynamic_cast<", "dynamic_cast<", "dynamic_cast<", "dynamic_cast<", "dynamic_cast<", "dynamic_cast<"};
static string progLangDynamicCastEnd[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"*>", "*>", "*>", "*>", "*>", "*>", "*>"};
static string progLangFunctionOwnerClassDelimiter[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"::", "::", "::", "::", "::", "::", "::"};

//from NLCcodeBlockClass.h
static string progLangOpenBlock[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"{", "{", "{", "{", "{", "{", "{"};
static string progLangCloseBlock[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"}", "}", "}", "}", "}", "}", "}"};
static string progLangObjectReferenceDelimiter[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"->", "->", "->", "->", "->", "->", "->"};
static string progLangObjectReferenceDelimiter2[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {".", ".", ".", ".", ".", ".", "."};
static string progLangOpenParameterSpace[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"(", "(", "(", "(", "(", "(", "("};
static string progLangCloseParameterSpace[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {")", ")", ")", ")", ")", ")", ")"};
static string progLangEndLine[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {";", ";", ";", ";", ";", ";", ";"};
static string progLangFor[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"for", "for", "for", "for", "for", "for", "for"};
static string progLangIf[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"if", "if", "if", "if", "if", "if", "if"};
static string progLangElseIf[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"else if", "else if", "else if", "else if", "else if", "else if", "else if"};
static string progLangElse[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"else", "else", "else", "else", "else", "else", "else"};
static string progLangWhile[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"while", "while", "while", "while", "while", "while", "while"};
static string progLangObjectCheckHasPropertyFunction[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"hasObjectOfClass", "hasObjectOfClass", "hasObjectOfClass", "hasObjectOfClass", "hasObjectOfClass", "hasObjectOfClass", "hasObjectOfClass"};
static string progLangParameterSpaceNextParam[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {",", ",", ",", ",", ",", ",", ","};
static string progLangPointer[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"*", "*", "*", "*", "*", "*", "*"};
static string progLangNot[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"!", "!", "!", "!", "!", "!", "!"};
static string progLangEquals[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {" = ", " = ", " = ", " = ", " = ", " = ", " = "};
static string progLangForIterPart1[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"(", "(", "(", "(", "(", "(", "("};
static string progLangForIterPart2a[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"::iterator ", "::iterator ", "::iterator ", "::iterator ", "::iterator ", "::iterator ", "::iterator "};
static string progLangForIterPart2c[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {" = ", " = ", " = ", " = ", " = ", " = ", " = "};
//#ifdef NLC_CATEGORIES_TEST_PLURALITY
//static string progLangForIterPart3a[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {".rbegin()", ".rbegin()", ".rbegin()", ".rbegin()", ".rbegin()", ".rbegin()", ".rbegin()"};
//#else
static string progLangForIterPart3a[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {".begin()", ".begin()", ".begin()", ".begin()", ".begin()", ".begin()", ".begin()"};
//#endif
static string progLangForIterPart3b[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"; ", "; ", "; ", "; ", "; ", "; ", "; "};
static string progLangForIterPart3c[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {" < ", " < ", " < ", " < ", " < ", " < ", " < "};
static string progLangForIterPart3cMap[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {" != ", " != ", " != ", " != ", " != ", " != ", " != "};
//#ifdef NLC_CATEGORIES_TEST_PLURALITY
//static string progLangForIterPart3a[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {".rend()", ".rend()", ".rend()", ".rend()", ".rend()", ".rend()", ".rend()"};
//#else
static string progLangForIterPart4a[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {".end()", ".end()", ".end()", ".end()", ".end()", ".end()", ".end()"};
//#endif
static string progLangForIterPart4b[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"; ", "; ", "; ", "; ", "; ", "; ", "; "};
static string progLangForIterPart4c[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"++) ", "++) ", "++)", "++)", "++)", "++)", "++)"};
static string progLangForIterName[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"iter", "iter", "iter", "iter", "iter", "iter", "iter"};
static string progLangForIterConditionObjectReference[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"->second", "->second", "->second", "->second", "->second", "->second", "->second"};

static string progLangForIndexPart1[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"(", "(", "(", "(", "(", "(", "("};
static string progLangForIndexPart2[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {" = 0; ", " = 0; ", " = 0; ", " = 0; ", " = 0; ", " = 0; ", " = 0; "};
static string progLangForIndexPart3[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {" < ", " < ", " < ", " < ", " < ", " < ", " < "};
static string progLangForIndexPart4[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"; ", "; ", "; ", "; ", "; ", "; ", "; "};
static string progLangForIndexPart5[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"++) ", "++) ", "++)", "++)", "++)", "++)", "++)"};


static string progLangNewObject[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"new ", "new ", "new ", "new ", "new ", "new ", "new "};
static string progLangAddEntityToList[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"push_back", "push_back", "push_back", "push_back", "push_back", "push_back", "push_back"};
static string progLangAddProperty[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"push_back", "push_back", "push_back", "push_back", "push_back", "push_back", "push_back"};
#ifdef NLC_CONDITION_LISTS_VECTOR
static string progLangAddCondition[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"push_back", "push_back", "push_back", "push_back", "push_back", "push_back", "push_back"};
#else
static string progLangAddCondition[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"insert", "insert", "insert", "insert", "insert", "insert", "insert"};
#endif
static string progLangHasEntity[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"empty()", "empty()", "empty()", "empty()", "empty()", "empty()", "empty()"};
static string progLangHasCondition[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"empty()", "empty()", "empty()", "empty()", "empty()", "empty()", "empty()"};

static string progLangMainEntryPointFunctionName[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"main", "main", "main", "main", "main", "main", "main"};

static string progLangBoolean[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"bool ", "bool ", "bool ", "bool ", "bool ", "bool ", "bool "};
static string progLangFalse[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"false", "false", "false", "false", "false", "false", "false"};
static string progLangTrue[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"true", "true", "true", "true", "true", "true", "true"};
static string progLangInteger[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"int ", "int ", "int ", "int ", "int ", "int ", "int "};
static string progLangForIndex[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"index", "index", "index", "index", "index", "index", "index"};
static string progLangDecimalType[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"double ", "double ", "double ", "double ", "double ", "double ", "double "};
static string progLangDecimalPointerType[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"double* ", "double* ", "double* ", "double* ", "double* ", "double* ", "double* "};

static string progLangAnd[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"&&", "&&", "&&", "&&", "&&", "&&", "&&"};
static string progLangOr[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"||", "||", "||", "||", "||", "||", "||"};
static string progLangArrayOpen[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"[", "[", "[", "[", "[", "[", "["};
static string progLangArrayClose[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"]", "]", "]", "]", "]", "]", "]"};
static string progLangArrayInitialisationOpen[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"{", "{", "{", "{", "{", "{", "{"};
static string progLangArrayInitialisationClose[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"}", "}", "}", "}", "}", "}", "}"};



static string progLangMathPlus[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {" + ", " + ", " + ", " + ", " + ", " + ", " + "};
static string progLangMathMinus[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {" - ", " - ", " - ", " - ", " - ", " - ", " - "};
static string progLangMathMultiply[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"* ", "* ", "* ", "* ", "* ", "* ", "* "};
static string progLangMathDivide[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {" / ", " / ", " / ", " / ", " / ", " / ", " / "};

#ifdef NLC_TRANSLATE_NEGATIVE_PROPERTIES_AND_CONDITIONS
static string progLangRemoveProperties[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"clear()", "clear()", "clear()", "clear()", "clear()", "clear()", "clear()"};
static string progLangRemoveConditions[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"clear()", "clear()", "clear()", "clear()", "clear()", "clear()", "clear()"};
#endif

static string progLangOpenSingleLineComment[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"//", "//", "//", "//", "//", "//", "//"};

static string progLangPrintTextOpen[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"cout << \"", "cout << \"", "cout << \"", "cout << \"", "cout << \"", "cout << \"", "cout << \""};
static string progLangPrintTextClose[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"\" << endl", "\" << endl", "\" << endl", "\" << endl", "\" << endl", "\" << endl", "\" << endl"};
static string progLangGetLast[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"back()", "back()", "back()", "back()", "back()", "back()", "back()"};
static string progLangGreaterThan[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {" > ", " > ", " > ", " > ", " > ", " > ", " > "};	//must be synced with NLC_PREPROCESSOR_MATH_OPERATOR_GREATER_THAN
static string progLangGreaterThanOrEqualTo[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {" >= ", " >= ", " >= ", " >= ", " >= ", " >= ", " >= "};	//must be synced with NLC_PREPROCESSOR_MATH_OPERATOR_GREATER_THAN_OR_EQUAL_TO
static string progLangEqualsTest[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {" == ", " == ", " == ", " == ", " == ", " == ", " == "};	//must be synced with NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_TEST
static string progLangSizeOfList[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"size()", "size()", "size()", "size()", "size()", "size()", "size()"};
static string progLangLessThan[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {" < ", " < ", " < ", " < ", " < ", " < ", " < "};	//must be synced with NLC_PREPROCESSOR_MATH_OPERATOR_LESS_THAN
static string progLangLessThanOrEqualTo[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {" <= ", " <= ", " <= ", " <= ", " <= ", " <= ", " <= "};	//must be synced with NLC_PREPROCESSOR_MATH_OPERATOR_LESS_THAN_OR_EQUAL_TO
static string progLangIsNotEqualTo[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {" != ", " != ", " != ", " != ", " != ", " != ", " != "};	//NO: must be synced with NLC_PREPROCESSOR_MATH_OPERATOR_IS_NOT_EQUAL_TO

#ifdef NLC_USE_ADVANCED_REFERENCING
#ifdef NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT
static string progLangClassLastSentenceReferencedVariableType[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"stack<int> ", "stack<int> ", "stack<int> ", "stack<int> ", "stack<int> ", "stack<int> ", "stack<int> "};
static string progLangStackAdd[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"push", "push", "push", "push", "push", "push", "push"};
static string progLangStackRemove[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"pop()", "pop()", "pop()", "pop()", "pop()", "pop()", "pop()"};
static string progLangStackGetLast[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"top()", "top()", "top()", "top()", "top()", "top()", "top()"};
static string progLangClassLastSentenceIndexVariableType[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"int ", "int ", "int ", "int ", "int ", "int ", "int "};
#else
static string progLangClassLastSentenceReferencedVariableType[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"int ", "int ", "int ", "int ", "int ", "int ", "int "};
#endif
#endif
#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN_DO_NOT_ADD_DUPLICATES
static string progLangFindPart1[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"if(", "if(", "if(", "if(", "if(", "if(", "if("};
static string progLangFindPart2[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"(find(", "(find(", "(find(", "(find(", "(find(", "(find(", "(find("};
static string progLangFindPart3[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {".begin(), ", ".begin(), ", ".begin(), ", ".begin(), ", ".begin(), ", ".begin(), ", ".begin(), "};
static string progLangFindPart4[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {".end(), ", ".end(), ", ".end(), ", ".end(), ", ".end(), ", ".end(), ", ".end(), "};
static string progLangFindPart5[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {") != ", ") != ", ") != ", ") != ", ") != ", ") != ", ") != "};
static string progLangFindPart6[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {".end()))", ".end()))", ".end()))", ".end()))", ".end()))", ".end()))", ".end()))"};
#endif
static string progLangTemplateHeaderPart1[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"template <", "template <", "template <", "template <", "template <", "template <", "template <"};
static string progLangTemplateHeaderPart2[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {">", ">", ">", ">", ">", ">", ">"};
static string progLangTemplateHeaderClassType[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"class ", "class ", "class ", "class ", "class ", "class ", "class "};
static string progLangTemplateHeaderClassSeparator[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {",", ",", ",", ",", ",", ",", ","};
static string progLangTemplateUsePart1[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"<", "<", "<", "<", "<", "<", "<"};
static string progLangTemplateUsePart2[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {">", ">", ">", ">", ">", ">", ">"};
static string progLangTemplateUseClassSeparator[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {", ", ", ", ", ", ", ", ", ", ", ", ", "};

static string progLangReference[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"&", "&", "&", "&", "&", "&", "&"};
static string progLangReturn[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"return ", "return ", "return ", "return ", "return ", "return ", "return "};

#ifdef NLC_USE_ADVANCED_REFERENCING_SUPPORT_ALIASES
static string progLangAliasNameVariableType[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"string ", "string ", "string ", "string ", "string ", "string ", "string "};
static string progLangAliasListVariableType[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"vector<string> ", "vector<string> ", "vector<string> ", "vector<string> ", "vector<string> ", "vector<string> ", "vector<string> "};
#endif
static string progLangForIterEntityMapListEntityReference[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"->second", "->second", "->second", "->second", "->second", "->second", "->second"};
static string progLangTestEntityPairFindPart1[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"if(", "if(", "if(", "if(", "if(", "if(", "if("};
static string progLangTestEntityPairFindPart2[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {" != ", " != ", " != ", " != ", " != ", " != ", " != "};
static string progLangTestEntityPairFindPart3[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"->end())", "->end())", "->end())", "->end())", "->end())", "->end())", "->end())"};

static string progLangTypeName[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"typename ", "typename ", "typename ", "typename ", "typename ", "typename ", "typename "};	//required for C++; "error: need typename before std::vector<Ex*> because std::vector<Ex*> is a dependent scope"

static string progLangStringEqualsTest[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {" == ", " == ", " == ", " == ", " == ", " == ", " == "};

static string progLangAddAllList[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"insert", "insert", "insert", "insert", "insert", "insert", "insert"};
static string progLangAddAllListKey1open[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"[", "[", "[", "[", "[", "[", "["};
static string progLangAddAllListKey1close[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"]", "]", "]", "]", "]", "]", "]"};
static string progLangMakePair[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"make_pair", "make_pair", "make_pair", "make_pair", "make_pair", "make_pair", "make_pair"};
static string progLangNewPair[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"new pair", "new pair", "new pair", "new pair", "new pair", "new pair", "new pair"};
#define NLC_USE_LIBRARY_ALL_LISTS_KEY_TYPE "string"
static string progLangReinterpretCastStart[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"reinterpret_cast<", "reinterpret_cast<", "reinterpret_cast<", "reinterpret_cast<", "reinterpret_cast<", "reinterpret_cast<", "reinterpret_cast<"};
static string progLangReinterpretCastEnd[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {">", ">", ">", ">", ">", ">", ">"};
static string progLangAddress[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"&", "&", "&", "&", "&", "&", "&"};
static string progLangNullPointer[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL"};

#ifdef NLC_USE_SUPPORT_REFERENCING_OBJECTS_IN_PLURAL_LIST_BY_NUMBER
static string progLangGetAtPositionPart1[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {".at(", ".at(", ".at(", ".at(", ".at(", ".at(", ".at("};
static string progLangGetAtPositionPart2[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"-1)", "-1)", "-1)", "-1)", "-1)", "-1)", "-1)"};
#endif
#ifdef NLC_USE_MATH_OBJECTS
static string progLangDefaultDecimalValue[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"numeric_limits<double>::quiet_NaN()", "numeric_limits<double>::quiet_NaN()", "numeric_limits<double>::quiet_NaN()", "numeric_limits<double>::quiet_NaN()", "numeric_limits<double>::quiet_NaN()", "numeric_limits<double>::quiet_NaN()", "numeric_limits<double>::quiet_NaN()"};
#endif

#ifdef NLC_USE_PREDEFINED_FUNCTION_NAME_FOR_NATURAL_LANGUAGE_CODE_WITHOUT_FUNCTION_SPECIFIED_EXECUTE_IN_MAIN
static string progLangMainFunctionDeclaration[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"int main()", "int main()", "int main()", "int main()", "int main()", "int main()", "int main()"};
#endif


void printLine(string command, int level, string* code);
string generatePropertyListName(NLCitem* item);

string generatePropertyListName(string propertyClassName);	//NLC_NONOO: backwards compatibility wrapper only
#ifdef NLC_NONOO
string generatePropertyListName();
string generatePropertyReverseListName();
#endif

#ifdef NLC_RECORD_ACTION_HISTORY
string generateActionListName(string actionClassName);	//NLC_NONOO: backwards compatibility wrapper only
string generateActionIncomingListName(string actionClassName);	//NLC_NONOO: backwards compatibility wrapper only
string generateActionSubjectListName(string actionSubjectClassName);	//NLC_NONOO: backwards compatibility wrapper only
string generateActionObjectListName(string actionObjectClassName);	//NLC_NONOO: backwards compatibility wrapper only
#ifdef NLC_NONOO
string generateActionListName();
string generateActionIncomingListName();
string generateActionSubjectListName();
string generateActionObjectListName();
#endif
#endif
string generateLocalListName(NLCitem* item);
string generateEntityListName(NLCitem* entityParam);	//added 1i6a
string generateEntityListAppendName();
string generateCategoryListName(NLCitem* param, string genericListAppendName);
string generateGenericListName(string genericObjectName, string genericListAppendName);
string generateConditionListName(string conditionClassName, string conditionObjectClassName);
#ifdef NLC_NONOO
string generateConditionListName();
string generateGIAconditionListName();
string generateGIAconditionObjectListName();
string generateGIAincomingConditionListName();
string generateGIAconditionSubjectListName();
#else
string generateConditionListName(NLCitem* conditionItem, NLCitem* conditionObjectItem);
string generateConditionPairDefinitionName(string conditionClassName, string conditionObjectClassName);
#ifdef NLC_CONDITION_LISTS_VECTOR
string generateCodeConditionNewPairText(string conditionName, string conditionClassName, string conditionInstanceName, string conditionObjectClassName, string conditionObjectInstanceName, int progLang);
#endif
string generateCodeConditionPairText(string conditionName, string conditionClassName, string conditionInstanceName, string conditionObjectClassName, string conditionObjectInstanceName, int progLang);
string generateCodeConditionPairTextWithContext(string conditionName, string conditionClassName, string conditionInstanceName, string conditionObjectClassName, string conditionObjectInstanceName, vector<string>* conditionContext, int progLang);
#endif
	string generateInstanceNameWithContext(string instanceName, vector<string>* context, int progLang);
		string generateStringFromContextVector(vector<string>* context, int progLang);

string generateCodePropertyListDefinitionText(NLCitem* entityParam, int progLang);
string generateCodePropertyListDefinitionText(string propertyClassName, int progLang);
string generateCodeEntityListDefinitionText(NLCitem* entityParam, int progLang);
string generateCodeEntityListDefinitionText(string className, string instanceName, int progLang);
	string generateCodeEntityListDefinitionTypeText(string entityClassName, int progLang);	//NLC_NONOO: backwards compatibility wrapper only
		string generateCodeEntityListDefinitionTypeTextCompact(string entityClassName, int progLang);
			#ifdef NLC_NONOO
			string generateCodeEntityListDefinitionTypeTextNonOO(int progLang);
			#else
			string generateCodeEntityListDefinitionTypeTextPointer(string entityClassName, int progLang);
			#ifdef NLC_GENERATE_TYPE_LISTS
			string generateCodeEntityListDefinitionTypeText2(string propertyClassName, int progLang);
			#endif
			#endif
			string generateCodeVectorListDefinitionTypeText(string entityClassName, int progLang);
			string generateCodeVectorListDefinitionTypeTextPointer(string entityClassName, int progLang);
			string generateCodeVectorListDefinitionTypeText2(string vectorClassName, int progLang);

string generateCodeEntityListDefinitionReferenceText(NLCitem* entityParam, int progLang);
	string generateCodeEntityListDefinitionTypeTextReference(string entityClassName, int progLang);
string generateCodeGenericListDefinitionText(NLCitem* entityParam, string genericListAppendName, int progLang);
string generateCodeConditionListDefinitionText(NLCitem* conditionParam, NLCitem* conditionObjectParam, int progLang);
string generateCodeConditionListDefinitionText(string conditionClassName, string conditionObjectClassName, int progLang);
	string generateCodeConditionListDefinitionTypeText(string conditionClassName, string conditionObjectClassName, int progLang);	//NLC_NONOO: backwards compatibility wrapper only
		string generateCodeConditionListDefinitionTypeTextCompact(string conditionClassName, string conditionObjectClassName, int progLang);
			#ifdef NLC_CONDITION_LISTS_VECTOR
			string generateCodeVectorPairListDefinitionTypeText(string conditionClassName, string conditionObjectClassName, int progLang);
			#else
			string generateCodeMapsListDefinitionTypeText(string conditionClassName, string conditionObjectClassName, int progLang);
			#endif
	#ifdef NLC_NONOO
	string generateCodeConditionListDefinitionTypeTextNonOO(int progLang);
	#else
	string generateCodeConditionListDefinitionTypeTextPointer(string conditionClassName, string conditionObjectClassName, int progLang);
	#endif

#ifdef NLC_NONOO
string generateGIAentityName();
string generateCodeEntityNameTestText(NLCitem* param, int progLang);
#endif

string generateCodeNewEntity(NLCitem* param, int progLang);
string generateCodeNewEntity(string className, string instanceName, int progLang);
	string generateCodeEntityDefinitionText(NLCitem* param, int progLang);
	string generateCodeEntityDefinitionText(string className, string instanceName, int progLang);
		string generateEntityName(NLCitem* param);
		string generateEntityClassName(NLCitem* param);

string generateCodeEntityDeclarationSetToNull(NLCitem* param1, int progLang);
string generateCodeSetEntity(NLCitem* param1, NLCitem* param2, int progLang);
string generateCodeEntityDeclarationSetToEntity(NLCitem* param1, NLCitem* param2, int progLang);

string generateDynamicCastOfEntity(string entityName, string castClassName, int progLang);
string generateStaticCastOfEntity(string entityName, string castClassName, int progLang);
string generateStaticCastOfNewEntity(string entityClassName, string castClassName, int progLang);
string generateReinterpretCastOfVector(string vectorName, string castClassName, int progLang);
string generateReinterpretCastOfVectorReference(string vectorName, string castClassName, int progLang);	//CHECKTHIS
string generateReinterpretCastOfConditionList(string vectorName, string castClassName1, string castClassName2, int progLang);

//this code is not currently used;
string generateCodeGenericStringMapListDefinitionText(string entityClassName, string genericListNameStart, string genericListAppendName, int progLang);
string generateGenericStringMapListName(string genericListNameStart, string genericListAppendName);	//OLD: generateEntityStringMapListName

string generateExternalFunctionContext(string objectName, int progLang);
string generateNewObject(string objectName, int progLang);


#ifdef NLC_USE_LIBRARY
string generateCodeAllPropertyListAddText(string propertyClassName, int progLang);
string generateCodeAllPropertyListDefinitionText(int progLang);
string generateAllPropertyListName();

string generateCodeAllVectorListAddText(string allListName, string vectorListName, string vectorListKeyName, int progLang);
string generateCodeAllVectorListDefinitionTypeText(int progLang);
string generateCodeEntityMapListDefinitionTypeText(string pairItem1className, string entityClassName, int progLang);
string generateCodePairText(string pairItem1className, string pairItem2className, string pairItem1instanceName, string pairItem2instanceName, int progLang);
	string generateCodePairTextNew(string pairItem1className, string pairItem2className, string pairItem1instanceName, string pairItem2instanceName, int progLang);

string generateCodeAllPropertyIncomingListDefinitionText(int progLang);
string generateCodeAllPropertyIncomingListDefinitionTypeText(int progLang);
string generateAllPropertyIncomingListName();

string generateCodeAllConditionListAddText(string conditionClassName, string conditionObjectClassName, int progLang);
string generateCodeAllConditionListDefinitionText(int progLang);
string generateAllConditionListName();

string generateCodeAllMapListAddText(string allListName, string mapListName, string mapListKeyName1, string mapListKeyName2, int progLang);
string generateCodeAllConditionListDefinitionTypeText(int progLang);
string generateCodeEntityPairMapListDefinitionTypeText(string pairItem1className, string pairItem2className, string entityClassName, int progLang);
string generateCodePairTypeText(string pairItem1className, string pairItem2className, int progLang);
	string generateCodePairTypeTextPointer(string pairItem1className, string pairItem2className, int progLang);
string generateCodePairPairText(string pairItem1AclassName, string pairItem1BclassName, string pairItem2className, string pairItem1AinstanceName, string pairItem1BinstanceName, string pairItem2instanceName, int progLang);

string generateCodeAllConditionIncomingListDefinitionText(int progLang);
string generateCodeAllConditionIncomingListDefinitionTypeText(int progLang);
string generateAllConditionIncomingListName();

string generateCodeEntityStringMapListDefinitionText(string entityClassName, string mapListName, int progLang);
string generateCodeEntityStringMapListDefinitionTypeText(string entityClassName, int progLang);
string generateEntityStringPairText(string entity1Name, string entity2ClassName, string entity2Name, int progLang);

string generateCodeAllActionListAddText(string actionClassName, int progLang);
string generateCodeAllActionListDefinitionText(int progLang);
string generateAllActionListName();
string generateCodeAllActionIncomingListAddText(string actionIncomingClassName, int progLang);
string generateCodeAllActionIncomingListDefinitionText(int progLang);
string generateAllActionIncomingListName();
string generateCodeAllActionSubjectListAddText(string actionSubjectClassName, int progLang);
string generateCodeAllActionSubjectListDefinitionText(int progLang);
string generateAllActionSubjectListName();
string generateCodeAllActionObjectListAddText(string actionObjectClassName, int progLang);
string generateCodeAllActionObjectListDefinitionText(int progLang);
string generateAllActionObjectListName();

#endif

string generateCodeDeclareBoolTextAndSetFalse(string variableName, int progLang);
string generateCodeSetBoolTextTrue(string variableName, int progLang);
string generateCodeReturnText(string variableName, int progLang);

string generateCodeClassNameVariableDefinitionText(NLCitem* param1, int progLang);
string generateCodeNameVariableDefinitionText(NLCitem* param1, int progLang);

#ifdef NLC_USE_MATH_OBJECTS
string generateCodeEntityMathValueText(NLCitem* param1, int progLang);
string generateCodeEntityMathValueText(string entityName, int progLang);
string generateCodeDeclareNewDecimalPointerVariableText(NLCitem* param1, int progLang);
string generateCodePointerValueText(NLCitem* param1, int progLang);
string generateCodePointerValueText(string entityName, int progLang);
#endif
string generatePointerText(string entityName, int progLang);
string generatePointerTypeText(string entityName, int progLang);
string generateCodeListPointer(string list, int progLang);

string generateCodeIterReference(string iterIndexString, int progLang);
string generateCodeIterReferenceConditionObject(string iterIndexString, int progLang);
string generateCodeIterName(string iterIndexString, int progLang);


#endif
