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
 * File Name: NLCprintDefs.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2017 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 2b3a 25-May-2017
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/


#ifndef HEADER_NLC_PRINT_DEFS
#define HEADER_NLC_PRINT_DEFS

#include "NLCglobalDefs.hpp"
#include "NLCitemClass.hpp"

//based on GIAentityNode.h;
#ifdef NLC_NONOO
#define NLCNONOO_GENERIC_ENTITY_NODE_NAME "GIAentityNode"
#define GIA_ENTITYNODECLASS_ENTITYNAME_NAME "entityName"
#define GIA_ENTITYNODECLASS_PROPERTYNODELIST_NAME "propertyNodeList"
#define GIA_ENTITYNODECLASS_PROPERTYNODEREVERSELIST_NAME "propertyReverseNodeList"
#define GIA_ENTITYNODECLASS_CONDITIONNODELIST_NAME "conditionNodeList"
#define GIA_ENTITYNODECLASS_INCOMINGCONDITIONNODELIST_NAME "conditionReverseNodeList"
#define GIA_ENTITYNODECLASS_CONDITIONSUBJECTLIST_NAME "relationshipSubjectEntity"
#define GIA_ENTITYNODECLASS_CONDITIONOBJECTLIST_NAME "relationshipObjectEntity"
#define GIA_ENTITYNODECLASS_ACTIONNODELIST_NAME "actionNodeList"
#define GIA_ENTITYNODECLASS_INCOMINGACTIONNODELIST_NAME "actionReverseNodeList"
#define GIA_ENTITYNODECLASS_ACTIONSUBJECTLIST_NAME "relationshipSubjectEntity"
#define GIA_ENTITYNODECLASS_ACTIONOBJECTLIST_NAME "relationshipObjectEntity"
#endif

#ifdef NLC_LIBRARY
#define NLC_LIBRARY_ALL_PROPERTY_LIST_NAME "propertyLists"
#define NLC_LIBRARY_ALL_PROPERTYINCOMING_LIST_NAME "propertyIncomingLists"
#define NLC_LIBRARY_ALL_CONDITION_LIST_NAME "conditionLists"
#define NLC_LIBRARY_ALL_CONDITIONINCOMING_LIST_NAME "conditionIncomingLists"
#define NLC_LIBRARY_ALL_ACTION_LIST_NAME "actionLists"
#define NLC_LIBRARY_ALL_ACTIONINCOMING_LIST_NAME "actionIncomingLists"
#define NLC_LIBRARY_ALL_ACTIONOBJECT_LIST_NAME "actionObjectLists"
#define NLC_LIBRARY_ALL_ACTIONSUBJECT_LIST_NAME "actionSubjectLists"
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
#ifdef NLC_ADVANCED_REFERENCING_MONITOR_CONTEXT
#define NLC_ITEM_TYPE_REFERENCECONTEXT_VAR_APPENDITION "referenceContext"
#endif
#ifdef NLC_ADVANCED_REFERENCING_SUPPORT_ALIASES
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
#ifdef NLC_ADVANCED_REFERENCING_SUPPORT_ALIASES
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
#ifdef NLC_LIBRARY
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
#ifdef NLC_MATH_OBJECTS
static string progLangDecimalType[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"double ", "double ", "double ", "double ", "double ", "double ", "double "};
static string progLangDecimalPointerType[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"double* ", "double* ", "double* ", "double* ", "double* ", "double* ", "double* "};
static string progLangDefaultDecimalValue[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"INT_DEFAULT_VALUE", "INT_DEFAULT_VALUE", "INT_DEFAULT_VALUE", "INT_DEFAULT_VALUE", "INT_DEFAULT_VALUE", "INT_DEFAULT_VALUE", "INT_DEFAULT_VALUE"};	//numeric_limits<double>::quiet_NaN()
#ifdef NLC_MATH_OBJECTS_ADVANCED
#ifdef NLC_MATH_OBJECTS_STRING
static string progLangStringType[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"string ", "string ", "string ", "string ", "string ", "string ", "string "};
static string progLangStringPointerType[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"string* ", "string* ", "string* ", "string* ", "string* ", "string* ", "string* "};
static string progLangDefaultStringValue[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"\"\"", "\"\"", "\"\"", "\"\"", "\"\"", "\"\"", "\"\""};
#endif
#ifdef NLC_MATH_OBJECTS_BOOLEAN
static string progLangBooleanType[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"bool ", "bool ", "bool ", "bool ", "bool ", "bool ", "bool "};
static string progLangBooleanPointerType[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"bool* ", "bool* ", "bool* ", "bool* ", "bool* ", "bool* ", "bool* "};
static string progLangDefaultBooleanValue[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"false", "false", "false", "false", "false", "false", "false"};
#endif
#endif
#endif
static string progLangGenericPointerType[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"void* ", "void* ", "void* ", "void* ", "void* ", "void* ", "void* "};

static string progLangFunctionParameterStringType[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"string ", "string ", "string ", "string ", "string ", "string ", "string "};
static string progLangFunctionParameterBooleanType[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"bool ", "bool ", "bool ", "bool ", "bool ", "bool ", "bool "};

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
static string progLangStringEqualsTest[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {" == ", " == ", " == ", " == ", " == ", " == ", " == "};
static string progLangStringAdd[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {" + ", " + ", " + ", " + ", " + ", " + ", " + "};

#ifdef NLC_ADVANCED_REFERENCING
#ifdef NLC_ADVANCED_REFERENCING_MONITOR_CONTEXT
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

#ifdef NLC_ADVANCED_REFERENCING_SUPPORT_ALIASES
static string progLangAliasNameVariableType[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"string ", "string ", "string ", "string ", "string ", "string ", "string "};
static string progLangAliasListVariableType[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"vector<string> ", "vector<string> ", "vector<string> ", "vector<string> ", "vector<string> ", "vector<string> ", "vector<string> "};
#endif
static string progLangForIterEntityMapListEntityReference[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"->second", "->second", "->second", "->second", "->second", "->second", "->second"};
static string progLangTestEntityPairFindPart1[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"if(", "if(", "if(", "if(", "if(", "if(", "if("};
static string progLangTestEntityPairFindPart2[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {" != ", " != ", " != ", " != ", " != ", " != ", " != "};
static string progLangTestEntityPairFindPart3[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"->end())", "->end())", "->end())", "->end())", "->end())", "->end())", "->end())"};

static string progLangTypeName[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"typename ", "typename ", "typename ", "typename ", "typename ", "typename ", "typename "};	//required for C++; "error: need typename before std::vector<Ex*> because std::vector<Ex*> is a dependent scope"

static string progLangAddAllList[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"insert", "insert", "insert", "insert", "insert", "insert", "insert"};
static string progLangAddAllListKey1open[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"[", "[", "[", "[", "[", "[", "["};
static string progLangAddAllListKey1close[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"]", "]", "]", "]", "]", "]", "]"};
static string progLangMakePair[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"make_pair", "make_pair", "make_pair", "make_pair", "make_pair", "make_pair", "make_pair"};
static string progLangNewPair[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"new pair", "new pair", "new pair", "new pair", "new pair", "new pair", "new pair"};
#define NLC_LIBRARY_ALL_LISTS_KEY_TYPE "string"
static string progLangReinterpretCastStart[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"reinterpret_cast<", "reinterpret_cast<", "reinterpret_cast<", "reinterpret_cast<", "reinterpret_cast<", "reinterpret_cast<", "reinterpret_cast<"};
static string progLangReinterpretCastEnd[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {">", ">", ">", ">", ">", ">", ">"};
static string progLangAddress[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"&", "&", "&", "&", "&", "&", "&"};
static string progLangNullPointer[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL"};

#ifdef NLC_REFERENCING_OBJECTS_IN_PLURAL_LIST_BY_NUMBER
static string progLangGetAtPositionPart1[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {".at(", ".at(", ".at(", ".at(", ".at(", ".at(", ".at("};
static string progLangGetAtPositionPart2[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"-1)", "-1)", "-1)", "-1)", "-1)", "-1)", "-1)"};
#endif

#ifdef NLC_PREDEFINED_FUNCTION_NAME_FOR_NATURAL_LANGUAGE_CODE_WITHOUT_FUNCTION_SPECIFIED_EXECUTE_IN_MAIN
static string progLangMainFunctionDeclaration[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"int main()", "int main()", "int main()", "int main()", "int main()", "int main()", "int main()"};
#endif

static string progLangSpace[NLC_NUMBER_OF_PROGRAMMING_LANGUAGES] = {" ", " ", " ", " ", " ", " ", " "};


class NLCprintDefsClass
{
	private: NLCitemClassClass NLCitemClass;
	public: int getProgLang();
	public: void setProgLang(const int progLang);

	public: void printLine(const string command, const int level, string* code);
	public: string generatePropertyListName(const NLCitem* item);

	public: string generatePropertyListName(const string propertyClassName);	//NLC_NONOO: backwards compatibility wrapper only
	#ifdef NLC_NONOO
	public: string generatePropertyListName();
	public: string generatePropertyReverseListName();
	#endif

	#ifdef NLC_RECORD_ACTION_HISTORY
	public: string generateActionListName(const string actionClassName);	//NLC_NONOO: backwards compatibility wrapper only
	public: string generateActionIncomingListName(const string actionClassName);	//NLC_NONOO: backwards compatibility wrapper only
	public: string generateActionSubjectListName(const string actionSubjectClassName);	//NLC_NONOO: backwards compatibility wrapper only
	public: string generateActionObjectListName(const string actionObjectClassName);	//NLC_NONOO: backwards compatibility wrapper only
	#ifdef NLC_NONOO
	public: string generateActionListName();
	public: string generateActionIncomingListName();
	public: string generateActionSubjectListName();
	public: string generateActionObjectListName();
	#endif
	#endif
	public: string generateLocalListName(const string className, const string instanceName);
	public: string generateLocalListName(const NLCitem* item);
	public: string generateEntityListName(const NLCitem* entityParam);	//added 1i6a
	public: string generateEntityListAppendName();
	public: string generateCategoryListName(const NLCitem* param, const string genericListAppendName);
	public: string generateGenericListName(const string genericObjectName, const string genericListAppendName);
	public: string generateConditionListName(const string conditionClassName, const string conditionObjectClassName);
	#ifdef NLC_NONOO
	public: string generateConditionListName();
	public: string generateGIAconditionListName();
	public: string generateGIAconditionObjectListName();
	public: string generateGIAincomingConditionListName();
	public: string generateGIAconditionSubjectListName();
	#else
	public: string generateConditionListName(const NLCitem* conditionItem, const NLCitem* conditionObjectItem);
	public: string generateConditionPairDefinitionName(const string conditionClassName, const string conditionObjectClassName);
	#ifdef NLC_CONDITION_LISTS_VECTOR
	public: string generateCodeConditionNewPairText(const string conditionName, const string conditionClassName, const string conditionInstanceName, const string conditionObjectClassName, const string conditionObjectInstanceName, const int progLang);
	#endif
	public: string generateCodeConditionPairText(const string conditionName, const string conditionClassName, const string conditionInstanceName, const string conditionObjectClassName, const string conditionObjectInstanceName, const int progLang);
	public: string generateCodeConditionPairTextWithContext(const string conditionName, const string conditionClassName, const string conditionInstanceName, const string conditionObjectClassName, const string conditionObjectInstanceName, vector<string>* conditionContext, const int progLang);
	#endif
		private: string generateInstanceNameWithContext(const string instanceName, vector<string>* context, const int progLang);
			public: string generateStringFromContextVector(vector<string>* context, const int progLang);

	public: string generateCodePropertyListDefinitionText(const NLCitem* entityParam, const int progLang);
	public: string generateCodePropertyListDefinitionText(const string propertyClassName, const int progLang);
	public: string generateCodeEntityListDefinitionText(const NLCitem* entityParam, const int progLang);
	public: string generateCodeEntityListDefinitionText(const string className, const string instanceName, const int progLang);
		public: string generateCodeEntityListDefinitionTypeText(const string entityClassName, const int progLang);	//NLC_NONOO: backwards compatibility wrapper only
			public: string generateCodeEntityListDefinitionTypeTextCompact(const string entityClassName, const int progLang);
				#ifdef NLC_NONOO
				private: string generateCodeEntityListDefinitionTypeTextNonOO(const int progLang);
				#else
				private: string generateCodeEntityListDefinitionTypeTextPointer(const string entityClassName, const int progLang);
				#ifdef NLC_GENERATE_TYPE_LISTS
				public: string generateCodeEntityListDefinitionTypeText2(const string propertyClassName, const int progLang);
				#endif
				#endif
				private: string generateCodeVectorListDefinitionTypeText(const string entityClassName, const int progLang);
				private: string generateCodeVectorListDefinitionTypeTextPointer(const string entityClassName, const int progLang);
				private: string generateCodeVectorListDefinitionTypeText2(const string vectorClassName, const int progLang);

	public: string generateCodeEntityListDefinitionReferenceText(const NLCitem* entityParam, const int progLang);
		public: string generateCodeEntityListDefinitionTypeTextReference(const string entityClassName, const int progLang);
		public: string generateCodeEntityListDefinitionTypeTextReferenceCompact(const string entityClassName, const int progLang);
	public: string generateCodeGenericListDefinitionText(const NLCitem* entityParam, const string genericListAppendName, const int progLang);
	public: string generateCodeConditionListDefinitionText(const NLCitem* conditionParam, const NLCitem* conditionObjectParam, const int progLang);
	public: string generateCodeConditionListDefinitionText(const string conditionClassName, const string conditionObjectClassName, const int progLang);
		private: string generateCodeConditionListDefinitionTypeText(const string conditionClassName, const string conditionObjectClassName, const int progLang);	//NLC_NONOO: backwards compatibility wrapper only
			public: string generateCodeConditionListDefinitionTypeTextCompact(const string conditionClassName, const string conditionObjectClassName, const int progLang);
				#ifdef NLC_CONDITION_LISTS_VECTOR
				private: string generateCodeVectorPairListDefinitionTypeText(const string conditionClassName, const string conditionObjectClassName, const int progLang);
				#else
				private: string generateCodeMapsListDefinitionTypeText(const string conditionClassName, const string conditionObjectClassName, const int progLang);
				#endif
		#ifdef NLC_NONOO
		private: string generateCodeConditionListDefinitionTypeTextNonOO(const int progLang);
		#else
		private: string generateCodeConditionListDefinitionTypeTextPointer(const string conditionClassName, const string conditionObjectClassName, const int progLang);
		#endif

	#ifdef NLC_NONOO
	private: string generateGIAentityName();
	public: string generateCodeEntityNameTestText(const NLCitem* param, const int progLang);
	#endif
	public: string generateCodeClassNameTestText(const string objectName, const string className, const int progLang);

	public: string generateCodeNewEntity(const NLCitem* param, const int progLang);
	public: string generateCodeNewEntity(const string className, const string instanceName, const int progLang);
		public: string generateCodeEntityDefinitionText(const NLCitem* param, const int progLang);
		public: string generateCodeEntityDefinitionText(const string className, const string instanceName, const int progLang);
			public: string generateEntityName(const NLCitem* param);
			private: string generateEntityClassName(const NLCitem* param);

	public: string generateCodeEntityDeclarationSetToNull(const NLCitem* param1, const int progLang);
	public: string generateCodeSetEntity(const NLCitem* param1, const NLCitem* param2, const int progLang);
	public: string generateCodeEntityDeclarationSetToEntity(const NLCitem* param1, const NLCitem* param2, const int progLang);

	public: string generateDynamicCastOfEntity(const string entityName, const string castClassName, const int progLang);
	public: string generateStaticCastOfEntity(const string entityName, const string castClassName, const int progLang);
	public: string generateStaticCastOfNewEntity(const string entityClassName, const string castClassName, const int progLang);
	private: string generateReinterpretCastOfVector(const string vectorName, const string castClassName, const int progLang);
	public: string generateReinterpretCastOfVectorReference(const string vectorName, const string castClassName, const int progLang);	//CHECKTHIS
	private: string generateReinterpretCastOfConditionList(const string vectorName, const string castClassName1, const string castClassName2, const int progLang);

	//this code is not currently used;
	private: string generateCodeGenericStringMapListDefinitionText(const string entityClassName, const string genericListNameStart, const string genericListAppendName, const int progLang);
	private: string generateGenericStringMapListName(const string genericListNameStart, const string genericListAppendName);	//OLD: generateEntityStringMapListName

	public: string generateExternalFunctionContext(const string objectName, const int progLang);
	private: string generateNewObject(const string objectName, const int progLang);


	#ifdef NLC_LIBRARY
	public: string generateCodeAllPropertyListAddText(const string propertyClassName, const int progLang);
	public: string generateCodeAllPropertyListDefinitionText(const int progLang);
	private: string generateAllPropertyListName();

	private: string generateCodeAllVectorListAddText(const string allListName, const string vectorListName, const string vectorListKeyName, const int progLang);
	private: string generateCodeAllVectorListDefinitionTypeText(const int progLang);
	private: string generateCodeEntityMapListDefinitionTypeText(const string pairItem1className, const string entityClassName, const int progLang);
	private: string generateCodePairText(const string pairItem1className, const string pairItem2className, const string pairItem1instanceName, const string pairItem2instanceName, const int progLang);
		private: string generateCodePairTextNew(const string pairItem1className, const string pairItem2className, const string pairItem1instanceName, const string pairItem2instanceName, const int progLang);

	public: string generateCodeAllPropertyIncomingListDefinitionText(const int progLang);
	private: string generateCodeAllPropertyIncomingListDefinitionTypeText(const int progLang);
	public: string generateAllPropertyIncomingListName();

	public: string generateCodeAllConditionListAddText(const string conditionClassName, const string conditionObjectClassName, const int progLang);
	public: string generateCodeAllConditionListDefinitionText(const int progLang);
	private: string generateAllConditionListName();

	private: string generateCodeAllMapListAddText(const string allListName, const string mapListName, const string mapListKeyName1, const string mapListKeyName2, const int progLang);
	private: string generateCodeAllConditionListDefinitionTypeText(const int progLang);
	private: string generateCodeEntityPairMapListDefinitionTypeText(const string pairItem1className, const string pairItem2className, const string entityClassName, const int progLang);
	private: string generateCodePairTypeText(const string pairItem1className, const string pairItem2className, const int progLang);
		private: string generateCodePairTypeTextPointer(const string pairItem1className, const string pairItem2className, const int progLang);
	private: string generateCodePairPairText(const string pairItem1AclassName, const string pairItem1BclassName, const string pairItem2className, const string pairItem1AinstanceName, const string pairItem1BinstanceName, const string pairItem2instanceName, const int progLang);

	public: string generateCodeAllConditionIncomingListDefinitionText(const int progLang);
	private: string generateCodeAllConditionIncomingListDefinitionTypeText(const int progLang);
	private: string generateAllConditionIncomingListName();

	private: string generateCodeEntityStringMapListDefinitionText(const string entityClassName, const string mapListName, const int progLang);
	private: string generateCodeEntityStringMapListDefinitionTypeText(const string entityClassName, const int progLang);
	private: string generateEntityStringPairText(const string entity1Name, const string entity2ClassName, const string entity2Name, const int progLang);

	public: string generateCodeAllActionListAddText(const string actionClassName, const int progLang);
	public: string generateCodeAllActionListDefinitionText(const int progLang);
	private: string generateAllActionListName();
	public: string generateCodeAllActionIncomingListAddText(const string actionIncomingClassName, const int progLang);
	public: string generateCodeAllActionIncomingListDefinitionText(const int progLang);
	private: string generateAllActionIncomingListName();
	public: string generateCodeAllActionSubjectListAddText(const string actionSubjectClassName, const int progLang);
	public: string generateCodeAllActionSubjectListDefinitionText(const int progLang);
	private: string generateAllActionSubjectListName();
	public: string generateCodeAllActionObjectListAddText(const string actionObjectClassName, const int progLang);
	public: string generateCodeAllActionObjectListDefinitionText(const int progLang);
	private: string generateAllActionObjectListName();

	#endif

	public: string generateCodeDeclareBoolTextAndSetFalse(const string variableName, const int progLang);
	public: string generateCodeSetBoolTextTrue(const string variableName, const int progLang);
	public: string generateCodeReturnText(const string variableName, const int progLang);

	public: string generateCodeClassNameVariableDefinitionText(const NLCitem* param1, const int progLang);
	public: string generateCodeNameVariableDefinitionText(const NLCitem* param1, const int progLang);

	#ifdef NLC_MATH_OBJECTS
	public: string generateCodeTestEntityMathObjectNumericalValueText(const NLCitem* param1, const NLCitem* param2, const int progLang);
	public: string generateCodeEntityMathObjectNumericalValueText(const NLCitem* param1, const int progLang);
	public: string generateCodeEntityMathValuePointerText(const string entityName, const int progLang);
	public: string generateCodeDeclareNewDecimalPointerVariableText(const NLCitem* param1, const int progLang);
	public: string generateCodeSetDecimalPointerToEntityMathObjectNumericalValueText(const NLCitem* param1, const NLCitem* param2, const int progLang);
	#ifdef NLC_MATH_OBJECTS_ADVANCED
	public: string generateCodeDeclareNewGenericEntityPointerVariableText(const NLCitem* param1, const int progLang);
	public: string generateCodeSetGenericEntityPointerToEntityText(const NLCitem* param1, const NLCitem* param2, const int progLang);
	#ifdef NLC_MATH_OBJECTS_STRING
	public: string generateCodeEntityMathObjectStringValueText(const NLCitem* param1, const int progLang);
	public: string generateCodeDeclareNewStringPointerVariableText(const NLCitem* param1, const int progLang);
	public: string generateCodeSetStringPointerToEntityMathObjectStringValueText(const NLCitem* param1, const NLCitem* param2, const int progLang);
	#endif
	#ifdef NLC_MATH_OBJECTS_BOOLEAN
	public: string generateCodeEntityMathObjectBooleanValueText(const NLCitem* param1, const int progLang);
	public: string generateCodeDeclareNewBooleanPointerVariableText(const NLCitem* param1, const int progLang);
	public: string generateCodeSetBooleanPointerToEntityMathObjectBooleanValueText(const NLCitem* param1, const NLCitem* param2, const int progLang);
	#endif
	#endif
	private: string generateCodePointerValueText(const NLCitem* param1, const int progLang);
	private: string generateCodePointerValueText(const string entityName, const int progLang);
	public: string generateCodeEntityMathObjectValueText(const string entityName, const int mathtextVariableType, const int progLang);
	public: string generateCodeEntityMathObjectTypeText(const NLCitem* param1, const int progLang);
	#endif
	public: string generateReferenceText(const string entityName, const int progLang);
	public: string generatePointerText(const string entityName, const int progLang);
	public: string generatePointerTypeText(const string entityName, const int progLang);
	public: string generateReferenceTypeText(const string entityName, const int progLang);
	public: string generateCodeListPointer(const string list, const int progLang);

	public: string generateCodeIterReference(const string iterIndexString, const int progLang);
	public: string generateCodeIterReferenceConditionObject(const string iterIndexString, const int progLang);
	private: string generateCodeIterName(const string iterIndexString, const int progLang);

	#ifdef NLC_NORMALISE_TWOWAY_PREPOSITIONS_MARK_INVERSE_CONDITIONS
	public: string generateCodeEntityInverseConditionText(const NLCitem* param1, const int progLang);
	#endif


	public: string generateDefinitionText(const string variableType, const string variableName);
	public: string generateCodeSetText(const string variableNameToSet, const string variableNameValue, const int progLang);
	public: string generateCodeReferenceText(const string variableName, const string component, const int progLang);


	public: string generateCodeIfVarAequalsVarB(const string varA, const string varB, const int progLang);
};

#endif
