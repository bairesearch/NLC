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
 * Project Version: 1e9a 25-November-2013
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
//statements:
#define NLPI_CODEBLOCK_TYPE_EXECUTE_FUNCTION (1)		//context1.param1(context.param2); 	[param1 = function, context1 = subject, param2 = object]
#define NLPI_CODEBLOCK_TYPE_ADD_NEW_PROPERTY (3)			//context1->param1->param2PropertyList.push_back(param2);		//OLD2: context1.param1.param2PropertyList.addProperty(context2.param2);
#define NLPI_CODEBLOCK_TYPE_ADD_NEW_CONDITION (4)			//context1->param1->param2param3ConditionList.insert(param2, param3);	//OLD2: context1.param1.param3ConditionList.addCondition(context3.param3, param2);
#define NLPI_CODEBLOCK_TYPE_DECLARE_AND_INITIALISE_VARIABLE (5)
#define NLPI_CODEBLOCK_TYPE_DECLARE_NEW_VARIABLE (6)	
#define NLPI_CODEBLOCK_TYPE_ADD_PROPERTY (7)				//context1->param1->param2PropertyList.push_back(param2);
#define NLPI_CODEBLOCK_TYPE_ADD_CONDITION (8)				//context1->param1->param2param3ConditionList.insert(param2, param3);	
#define NLPI_CODEBLOCK_TYPE_CREATE_NEW_LOCAL_LIST_VARIABLE (9)
#define NLPI_CODEBLOCK_TYPE_ADD_PROPERTY_TO_LOCAL_LIST (10)		//param1instancePropertyList.push_back(param2);
#define NLPI_CODEBLOCK_TYPE_ADD_PROPERTY (11)
#define NLPI_CODEBLOCK_TYPE_ADD_CONDITION (13)

//containers:
#define NLPI_CODEBLOCK_TYPE_FOR_PROPERTY_LIST (20)		//forall(context.param1){
#define NLPI_CODEBLOCK_TYPE_FOR_CONDITION_LIST (21)		//forall(context.param1){
#define NLPI_CODEBLOCK_TYPE_NEW_FUNCTION (22)			//main(){
#define NLPI_CODEBLOCK_TYPE_IF_HAS_PROPERTY (23)		//if(!(context1->param1->param2PropertyList.empty())){			//OLD2:	if(context1.param1.param2PropertyList.findProperty(context2.param2)){		//OLD: if(context.param1->has(param2)){
#define NLPI_CODEBLOCK_TYPE_IF_HAS_CONDITION (24)		//if(!(context1->param1->param2param3ConditionList.empty())){		//OLD2: if(context1.param1.param3ConditionList.findCondition(context3.param3, param2)){	//OLD: if(param2(context.param1, context.param3)){
#define NLPI_CODEBLOCK_TYPE_FOR_PROPERTY_LIST_LOCAL (25)	//forall(param1instance){
#define NLPI_CODEBLOCK_TYPE_CONTAINERS (NLPI_CODEBLOCK_TYPE_FOR_PROPERTY_LIST)



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
NLPIcodeblock * createCodeBlockAddNewProperty(NLPIcodeblock * currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* propertyEntity, int sentenceIndex);
	NLPIcodeblock * createCodeBlockAddPropertyToLocalList(NLPIcodeblock * currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* propertyEntity, int sentenceIndex);
	NLPIcodeblock * createCodeBlockAddProperty(NLPIcodeblock * currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* propertyEntity, int sentenceIndex);
NLPIcodeblock * createCodeBlockAddNewCondition(NLPIcodeblock * currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* conditionEntity, int sentenceIndex);
	NLPIcodeblock * createCodeBlockAddCondition(NLPIcodeblock * currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* conditionEntity, int sentenceIndex);
NLPIcodeblock * createCodeBlocksCreateNewLocalListVariable(NLPIcodeblock * currentCodeBlockInTree, GIAentityNode* entity);
NLPIcodeblock * createCodeBlockForPropertyList(NLPIcodeblock * currentCodeBlockInTree, NLPIitem * item);
NLPIcodeblock * createCodeBlockForPropertyListLocal(NLPIcodeblock * currentCodeBlockInTree, NLPIitem * item);
NLPIcodeblock * createCodeBlockForConditionList(NLPIcodeblock * currentCodeBlockInTree, NLPIitem * item, NLPIitem * objectItem);
NLPIcodeblock * createCodeBlockNewFunction(NLPIcodeblock * currentCodeBlockInTree, string NLPIfunctionName, vector<GIAentityNode*> * entityNodesActiveListComplete);
	NLPIcodeblock * createCodeBlockDeclareAndInitialiseVariableForActionSubject(NLPIcodeblock * currentCodeBlockInTree, GIAentityNode* functionOwner);
	NLPIcodeblock * createCodeBlocksAddVariableToNewList(NLPIcodeblock * currentCodeBlockInTree, GIAentityNode* entity);
	#ifdef NLPI_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS
	void generateLocalFunctionArgumentsBasedOnImplicitDeclarations(vector<GIAentityNode*> * entityNodesActiveListComplete, vector<NLPIitem*> * parameters);
		bool assumedToAlreadyHaveBeenDeclared(GIAentityNode* entity);
	#endif
NLPIcodeblock * createCodeBlockForStatements(NLPIcodeblock * currentCodeBlockInTree, NLPIitem * item, GIAentityNode* entity, int sentenceIndex);
	NLPIcodeblock * createCodeBlockForGivenProperties(NLPIcodeblock * currentCodeBlockInTree, NLPIitem * item, GIAentityNode * entity, int sentenceIndex);
		NLPIcodeblock * createCodeBlockForGivenProperty(NLPIcodeblock * currentCodeBlockInTree, NLPIitem * item, GIAentityNode* propertyEntity, int sentenceIndex);
	NLPIcodeblock * createCodeBlockForGivenConditions(NLPIcodeblock * currentCodeBlockInTree, NLPIitem * item,  GIAentityNode * entity, int sentenceIndex);
		NLPIcodeblock * createCodeBlockForGivenCondition(NLPIcodeblock * currentCodeBlockInTree, NLPIitem * item, GIAentityNode* conditionEntity, int sentenceIndex);

NLPIcodeblock * createCodeBlock(NLPIcodeblock * currentCodeBlockInTree, int codeBlockType);
NLPIcodeblock * createLowerLevel(NLPIcodeblock * currentCodeBlockInTree);

bool getEntityContext(GIAentityNode * entity, vector<string> * context, bool includePresentObject, int sentenceIndex, bool markSameSentenceParentsAsParsed);

bool checkSentenceIndexParsingCodeBlocks(GIAentityNode * entity, int sentenceIndex, bool checkIfEntityHasBeenParsedForNLPIcodeBlocks);

bool checkDuplicateProperty(GIAentityNode * propertyEntity, GIAentityNode * childActionEntity);
bool checkDuplicateCondition(GIAentityNode * conditionEntity, GIAentityNode * childActionEntity);

#ifdef NLPI_SUPPORT_INPUT_FILE_LISTS
string parseFunctionNameFromNLPIfunctionName(string NLPIfunctionName);
void parseFunctionNameFromNLPIfunctionName(string NLPIfunctionName, string * functionName, string * functionOwnerName, bool * foundFunctionOwnerClass);
void parseFunctionNameFromNLPIfunctionName(string NLPIfunctionName, string * functionName, string * functionOwnerName, bool * foundFunctionOwnerClass, string * functionObjectName, bool * foundFunctionObjectClass);
#endif

#endif
