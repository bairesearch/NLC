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
 * File Name: NLPIcodeBlock.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2013 Baxter AI (baxterai.com)
 * Project: Natural Language Programming Interface (compiler)
 * Project Version: 1c4c 29-October-2013
 * Requirements: requires text parsed by NLP Parser (eg Relex; available in .CFF format <relations>)
 *
 *******************************************************************************/


#ifndef HEADER_NLPI_CODEBLOCK
#define HEADER_NLPI_CODEBLOCK

#include <iostream>
#include <fstream>
#include <ctime>
#include <cstring>
#include <cstdlib>	//for random number generation
#include <cmath>
#include <string>
#include <vector>
#include <vector>
#include <unordered_map>
using namespace std;

#include "NLPIglobalDefs.h"
#include "NLPIitem.h"
#include "GIAglobalDefs.h"
#include "GIAentityNodeClass.h"
#include "GIAentityConnectionClass.h"

#define NLPI_CODEBLOCK_TYPE_UNDEFINED (-1)
#define NLPI_CODEBLOCK_TYPE_EXECUTE_FUNCTION (1)		//context1.param1(context.param2); 	[param1 = function, context1 = subject, param2 = object]
#define NLPI_CODEBLOCK_TYPE_EXECUTE_FUNCTION_NO_OBJECT (2)	//context1.param1(); 	[param1 = function, context1 = subject]
#define NLPI_CODEBLOCK_TYPE_ADD_PROPERTY (3)			//context1->param1->param2PropertyList.push_back(param2);		//OLD2: context1.param1.param2PropertyList.addProperty(context2.param2);
#define NLPI_CODEBLOCK_TYPE_ADD_CONDITION (4)			//context1->param1->param2param3ConditionList.insert(param2, param3);	//OLD2: context1.param1.param3ConditionList.addCondition(context3.param3, param2);
#define NLPI_CODEBLOCK_TYPE_FOR (5)				//forall(context.param1){
#define NLPI_CODEBLOCK_TYPE_NEW_FUNCTION (6)			//main(){
#define NLPI_CODEBLOCK_TYPE_IF_HAS_PROPERTY (12)		//if(!(context1->param1->param2PropertyList.empty())){			//OLD2:	if(context1.param1.param2PropertyList.findProperty(context2.param2)){		//OLD: if(context.param1->has(param2)){
#define NLPI_CODEBLOCK_TYPE_IF_HAS_CONDITION (13)		//if(!(context1->param1->param2param3ConditionList.empty())){		//OLD2: if(context1.param1.param3ConditionList.findCondition(context3.param3, param2)){	//OLD: if(param2(context.param1, context.param3)){
#define NLPI_CODEBLOCK_TYPE_CONTAINERS (NLPI_CODEBLOCK_TYPE_FOR)

#define NLPI_PROGRAMMING_LANGUAGE_CPP (0)
#define NLPI_PROGRAMMING_LANGUAGE_JAVA (1)
#define NLPI_PROGRAMMING_LANGUAGE_VISUALBASIC (2)
#define NLPI_PROGRAMMING_LANGUAGE_CSHARP (3)
#define NLPI_PROGRAMMING_LANGUAGE_PHP (4)
#define NLPI_PROGRAMMING_LANGUAGE_PERL (5)
#define NLPI_PROGRAMMING_LANGUAGE_PYTHON (6)
#define NLPI_PROGRAMMING_LANGUAGE_DEFAULT (NLPI_PROGRAMMING_LANGUAGE_CPP)
#define NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES (7)	//this needs to be moved to NLPIglobalDefs.h

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
static string progLangForVectorIterPart1[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"(vector<", "(vector<", "(vector<", "(vector<", "(vector<", "(vector<", "(vector<"};
static string progLangForVectorIterPart2[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"*>::iterator iter = ", "*>::iterator iter = ", "*>::iterator iter = ", "*>::iterator iter = ", "*>::iterator iter = ", "*>::iterator iter = ", "*>::iterator iter = "};
static string progLangForVectorIterPart3[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {".begin(); iter < ", ".begin(); iter < ", ".begin(); iter < ", ".begin(); iter < ", ".begin(); iter < ", ".begin(); iter < ", ".begin(); iter < "};
static string progLangForVectorIterPart4[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {".end(); iter++)", ".end(); iter++)", ".end(); iter++)", ".end(); iter++)", ".end(); iter++)", ".end(); iter++)", ".end(); iter++)"};
static string progLangForVectorIterName[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"iter", "iter", "iter", "iter", "iter", "iter", "iter"};

static string progLangNewObject[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"new ", "new ", "new ", "new ", "new ", "new ", "new "};
static string progLangAddProperty[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"push_back", "push_back", "push_back", "push_back", "push_back", "push_back", "push_back"};
static string progLangAddCondition[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"insert", "insert", "insert", "insert", "insert", "insert", "insert"};
static string progLangFindProperty[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"empty", "empty", "empty", "empty", "empty", "empty", "empty"};
static string progLangFindCondition[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"empty", "empty", "empty", "empty", "empty", "empty", "empty"};
/*
#define NLPI_ITEM_TYPE_PROPERTYLISTADDFUNCTION "addProperty"
#define NLPI_ITEM_TYPE_CONDITIONLISTADDFUNCTION "addCondition"
#define NLPI_ITEM_TYPE_PROPERTYLISTFINDFUNCTION "findProperty"
#define NLPI_ITEM_TYPE_CONDITIONLISTFINDFUNCTION "findCondition"
*/


/*
//#define NLPI_CODEBLOCK_TYPE_IF_IS_ACTION_SUBJECT (10)
//#define NLPI_CODEBLOCK_TYPE_IF_IS_ACTION_OBJECT (11)
#define NLPI_CODEBLOCK_TYPE_IF_HAS_CONDITION (12)
#define NLPI_CODEBLOCK_TYPE_IF_HAS_PROPERTY (13)
//#define NLPI_CODEBLOCK_TYPE_IF_IS_PROPERTY (14)
//#define NLPI_CODEBLOCK_TYPE_IF_HAS_DEFINITION (15)
//#define NLPI_CODEBLOCK_TYPE_IF_IS_DEFINITION (16)
static bool codeBlockTypeIfStatementArrayUseVectorEntityConnection[GIA_ENTITY_NUMBER_OF_VECTOR_CONNECTION_TYPES] = {true, true, true, true, true, true, true, true, true, true, true, false, false, false};
static int codeBlockTypeIfStatementArray[GIA_ENTITY_NUMBER_OF_VECTOR_CONNECTION_TYPES] = {NLPI_CODEBLOCK_TYPE_IF_IS_ACTION_SUBJECT, NLPI_CODEBLOCK_TYPE_IF_IS_ACTION_OBJECT, NLPI_CODEBLOCK_TYPE_IF_HAS_CONDITION, -1, NLPI_CODEBLOCK_TYPE_IF_HAS_PROPERTY, NLPI_CODEBLOCK_TYPE_IF_IS_PROPERTY, NLPI_CODEBLOCK_TYPE_IF_HAS_DEFINITION, NLPI_CODEBLOCK_TYPE_IF_IS_DEFINITION, -1, -1, -1, -1, -1, -1};
*/

//shared with GIAtranslatorDefineReferencing.cpp

class NLPIcodeblock
{
public:

	NLPIcodeblock(void);
	~NLPIcodeblock(void);

	int codeBlockType;
	vector<NLPIitem*> parameters;
	
	/*
	//used by language specific code generator (eg C++, java);
	string codeBlockName; 	//eg "for"
	string openingText;	//eg "for(...){"
	string closingText; 	//eg "}";
	*/
	
	NLPIcodeblock * lowerLevel;
	NLPIcodeblock * next;
};

NLPIcodeblock * createCodeBlockExecute(NLPIcodeblock * currentCodeBlockInTree, NLPIitem * functionItem, NLPIitem* objectItem);
NLPIcodeblock * createCodeBlockExecute(NLPIcodeblock * currentCodeBlockInTree, NLPIitem * functionItem);
NLPIcodeblock * createCodeBlockAddProperty(NLPIcodeblock * currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* propertyEntity, int sentenceIndex);
NLPIcodeblock * createCodeBlockAddCondition(NLPIcodeblock * currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* conditionEntity, int sentenceIndex);
NLPIcodeblock * createCodeBlockFor(NLPIcodeblock * currentCodeBlockInTree, NLPIitem * item);
NLPIcodeblock * createCodeBlockNewFunction(NLPIcodeblock * currentCodeBlockInTree, string functionName, vector<GIAentityNode*> * entityNodesActiveListComplete);
	#ifdef NLPI_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS
	void generateLocalFunctionArgumentsBasedOnImplicitDeclarations(vector<GIAentityNode*> * entityNodesActiveListComplete, vector<NLPIitem*> * parameters);
	#endif
NLPIcodeblock * createCodeBlockIfHasProperties(NLPIcodeblock * currentCodeBlockInTree, NLPIitem * item, GIAentityNode * entity, int sentenceIndex);
	NLPIcodeblock * createCodeBlockIfHasProperty(NLPIcodeblock * currentCodeBlockInTree, NLPIitem * item, GIAentityNode* propertyEntity, int sentenceIndex);
NLPIcodeblock * createCodeBlockIfHasConditions(NLPIcodeblock * currentCodeBlockInTree, NLPIitem * item,  GIAentityNode * entity, int sentenceIndex);
	NLPIcodeblock * createCodeBlockIfHasCondition(NLPIcodeblock * currentCodeBlockInTree, NLPIitem * item, GIAentityNode* conditionEntity, int sentenceIndex);
		NLPIcodeblock * createCodeBlockIfStatements(NLPIcodeblock * currentCodeBlockInTree, NLPIitem * item, GIAentityNode* entity, int sentenceIndex);

NLPIcodeblock * createCodeBlock(NLPIcodeblock * currentCodeBlockInTree, int codeBlockType);
NLPIcodeblock * createLowerLevel(NLPIcodeblock * currentCodeBlockInTree);

bool getEntityContext(GIAentityNode * entity, vector<string> * context, bool includePresentObject, int sentenceIndex, bool markSameSentenceParentsAsParsed);
string generateStringFromContextVector(vector<string> * context, int progLang);

bool checkSentenceIndexParsingCodeBlocks(GIAentityNode * entity, int sentenceIndex, bool checkIfEntityHasBeenParsedForNLPIcodeBlocks);

bool checkDuplicateProperty(GIAentityNode * propertyEntity, GIAentityNode * childActionEntity);
bool checkDuplicateCondition(GIAentityNode * conditionEntity, GIAentityNode * childActionEntity);

#endif
