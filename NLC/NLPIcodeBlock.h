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
 * Project Version: 1a1b 14-September-2013
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

#include "GIAglobalDefs.h"
#include "GIAentityNodeClass.h"
#include "GIAentityConnectionClass.h"

#define NLPI_CODEBLOCK_TYPE_UNDEFINED (-1)
#define NLPI_CODEBLOCK_TYPE_EXECUTE_FUNCTION (2)	//context.param1(param2); [param1 = function, context = subject, param2 = object]
#define NLPI_CODEBLOCK_TYPE_FOR (3)			//forall(context.param1){
#define NLPI_CODEBLOCK_TYPE_NEW_FUNCTION (4)		main(){
#define NLPI_CODEBLOCK_TYPE_IF_HAS_CONDITION (12)	//if(param2(context.param1, context.param3)){
#define NLPI_CODEBLOCK_TYPE_IF_HAS_PROPERTY (13)	//if(context.param1->has(param2)){
#define NLPI_CODEBLOCK_TYPE_CONTAINERS (NLPI_CODEBLOCK_TYPE_FOR)

#define NLPI_PROGRAMMING_LANGUAGE_CPP (0)
#define NLPI_PROGRAMMING_LANGUAGE_JAVA (1)
#define NLPI_PROGRAMMING_LANGUAGE_VISUALBASIC (2)
#define NLPI_PROGRAMMING_LANGUAGE_CSHARP (3)
#define NLPI_PROGRAMMING_LANGUAGE_PHP (4)
#define NLPI_PROGRAMMING_LANGUAGE_PERL (5)
#define NLPI_PROGRAMMING_LANGUAGE_PYTHON (6)
#define NLPI_PROGRAMMING_LANGUAGE_DEFAULT (NLPI_PROGRAMMING_LANGUAGE_CPP)
#define NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES (7)

static bool progLangOpenBlock[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"{", "{", "{", "{", "{", "{", "{"};
static bool progLangCloseBlock[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"}", "}", "}", "}", "}", "}", "}"};
static bool progLangObjectReferenceDelimiter[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {".", ".", ".", ".", ".", ".", "."};
static bool progLangOpenParameterSpace[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"(", "(", "(", "(", "(", "(", "("};
static bool progLangCloseParameterSpace[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {")", ")", ")", ")", ")", ")", ")"};
static bool progLangEndLine[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {";", ";", ";", ";", ";", ";", ";"};
static bool progLangFor[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"for", "for", "for", "for", "for", "for", "for"};
static bool progLangIf[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"if", "if", "if", "if", "if", "if", "if"};
static bool progLangObjectCheckHasPropertyFunction[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"has", "has", "has", "has", "has", "has", "has"};


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

class NLPIitem
{
public:

	NLPIitem(void);
	NLPIitem(string newName);
	~NLPIitem(void);

	string name;
	vector<string> context;	//item context
};


class NLPIcodeblock
{
public:

	NLPIcodeblock(void);
	~NLPIcodeblock(void);

	int codeBlockType;
	vector<NLPIitem*> parameters;
	
	//used by language specific code generator (eg C++, java);
	string codeBlockName; 	//eg "for"
	string openingText;	//eg "for(...){"
	string closingText; 	//eg "}";
	
	NLPIcodeblock * lowerLevel;
	NLPIcodeblock * next;
};




NLPIcodeblock * createCodeBlockFor(NLPIcodeblock * currentCodeBlockInTree, NLPIitem * item);
NLPIcodeblock * createCodeBlockIfHasProperties(NLPIcodeblock * currentCodeBlockInTree, NLPIitem * item, GIAentityNode * entity, int sentenceIndex);
	NLPIcodeblock * createCodeBlockIfHasProperty(NLPIcodeblock * currentCodeBlockInTree, NLPIitem * item, GIAentityNode* propertyEntity, int sentenceIndex);
NLPIcodeblock * createCodeBlockIfHasConditions(NLPIcodeblock * currentCodeBlockInTree, NLPIitem * item,  GIAentityNode * entity, int sentenceIndex);
	NLPIcodeblock * createCodeBlockIfHasCondition(NLPIcodeblock * currentCodeBlockInTree, NLPIitem * item, GIAentityNode* conditionEntity, int sentenceIndex);
NLPIcodeblock * createCodeBlockExecute(NLPIcodeblock * currentCodeBlockInTree, NLPIitem * functionItem, NLPIitem* objectItem);
NLPIcodeblock * createCodeBlockNewFunction(NLPIcodeblock * currentCodeBlockInTree, string functionName);
NLPIcodeblock * createLowerLevel(NLPIcodeblock * currentCodeBlockInTree);
bool getEntityContext(GIAentityNode * entity, vector<string> * context, bool includePresentObject);
	NLPIcodeblock * createCodeBlock(NLPIcodeblock * currentCodeBlockInTree, int codeBlockType);

string generateStringFromContextVector(vector<string> * context, int progLang);

#endif
