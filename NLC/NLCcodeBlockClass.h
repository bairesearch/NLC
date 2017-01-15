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
 * File Name: NLCcodeBlockClass.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2014 Baxter AI (baxterai.com)
 * Project: Natural Language Programming Interface (compiler)
 * Project Version: 1g2a 01-July-2014
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/


#ifndef HEADER_NLC_CODEBLOCK_CLASS
#define HEADER_NLC_CODEBLOCK_CLASS

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

#include "NLCglobalDefs.h"
#include "NLCitemClass.h"
#include "GIAglobalDefs.h"
#include "GIAentityNodeClass.h"
#include "GIAentityConnectionClass.h"

#define NLC_CODEBLOCK_TYPE_UNDEFINED (-1)
//statements:
#define NLC_CODEBLOCK_TYPE_EXECUTE_FUNCTION (1)				//context1.param1(context.param2); 	[param1 = function, context1 = subject, param2 = object]
#define NLC_CODEBLOCK_TYPE_ADD_NEW_PROPERTY (3)				//context1->param1->param2PropertyList.push_back(param2);		//OLD2: context1.param1.param2PropertyList.addProperty(context2.param2);
#define NLC_CODEBLOCK_TYPE_ADD_NEW_CONDITION (4)			//context1->param1->param2param3ConditionList.insert(param2, param3);	//OLD2: context1.param1.param3ConditionList.addCondition(context3.param3, param2);
#define NLC_CODEBLOCK_TYPE_DECLARE_AND_INITIALISE_VARIABLE (5)
#define NLC_CODEBLOCK_TYPE_DECLARE_NEW_VARIABLE (6)
#define NLC_CODEBLOCK_TYPE_ADD_PROPERTY (7)				//context1->param1->param2PropertyList.push_back(param2);
#define NLC_CODEBLOCK_TYPE_ADD_CONDITION (8)				//context1->param1->param2param3ConditionList.insert(param2, param3);
#define NLC_CODEBLOCK_TYPE_ADD_NEW_PROPERTY_TO_LOCAL_LIST (9)
//#define NLC_CODEBLOCK_TYPE_CREATE_NEW_LOCAL_LIST_VARIABLE (9)
#define NLC_CODEBLOCK_TYPE_ADD_PROPERTY_TO_LOCAL_LIST (10)		//param1instancePropertyList.push_back(param2);
#define NLC_CODEBLOCK_TYPE_ADD_PROPERTY (11)
#define NLC_CODEBLOCK_TYPE_ADD_CONDITION (13)
#define NLC_CODEBLOCK_TYPE_DECLARE_NEW_LOCAL_LIST_VARIABLE (14)

//containers:
#define NLC_CODEBLOCK_TYPE_FOR_PROPERTY_LIST (20)		//forall(context1.param1PropertyList){
#define NLC_CODEBLOCK_TYPE_FOR_CONDITION_LIST (21)		//forall(context1.param1param2ConditionList){
#define NLC_CODEBLOCK_TYPE_NEW_FUNCTION (22)			//main(){
#define NLC_CODEBLOCK_TYPE_IF_HAS_PROPERTY (23)			//if(!(context1->param1PropertyList.empty())){			//OLD2:	if(context1.param1.param2PropertyList.findProperty(context2.param2)){		//OLD: if(context.param1->has(param2)){
#define NLC_CODEBLOCK_TYPE_IF_HAS_CONDITION (24)		//if(!(context1->param1param2ConditionList.empty())){		//OLD2: if(context1.param1.param3ConditionList.findCondition(context3.param3, param2)){	//OLD: if(param2(context.param1, context.param3)){
#define NLC_CODEBLOCK_TYPE_FOR_PROPERTY_LIST_LOCAL (25)	//forall(param1instance){
#define NLC_CODEBLOCK_TYPE_WHILE_HAS_PROPERTY (26)		//while(!(context1->param1PropertyList.empty())){
#define NLC_CODEBLOCK_TYPE_WHILE_HAS_CONDITION (27)		//while(!(context1->param1param2ConditionList.empty())){
#define NLC_CODEBLOCK_TYPE_CONTAINERS (NLC_CODEBLOCK_TYPE_FOR_PROPERTY_LIST)



/*
//#define NLC_CODEBLOCK_TYPE_IF_IS_ACTION_SUBJECT (10)
//#define NLC_CODEBLOCK_TYPE_IF_IS_ACTION_OBJECT (11)
#define NLC_CODEBLOCK_TYPE_IF_HAS_CONDITION (12)
#define NLC_CODEBLOCK_TYPE_IF_HAS_PROPERTY (13)
//#define NLC_CODEBLOCK_TYPE_IF_IS_PROPERTY (14)
//#define NLC_CODEBLOCK_TYPE_IF_HAS_DEFINITION (15)
//#define NLC_CODEBLOCK_TYPE_IF_IS_DEFINITION (16)
static bool codeBlockTypeIfStatementArrayUseVectorEntityConnection[GIA_ENTITY_NUMBER_OF_VECTOR_CONNECTION_TYPES] = {true, true, true, true, true, true, true, true, true, true, true, false, false, false};
static int codeBlockTypeIfStatementArray[GIA_ENTITY_NUMBER_OF_VECTOR_CONNECTION_TYPES] = {NLC_CODEBLOCK_TYPE_IF_IS_ACTION_SUBJECT, NLC_CODEBLOCK_TYPE_IF_IS_ACTION_OBJECT, NLC_CODEBLOCK_TYPE_IF_HAS_CONDITION, -1, NLC_CODEBLOCK_TYPE_IF_HAS_PROPERTY, NLC_CODEBLOCK_TYPE_IF_IS_PROPERTY, NLC_CODEBLOCK_TYPE_IF_HAS_DEFINITION, NLC_CODEBLOCK_TYPE_IF_IS_DEFINITION, -1, -1, -1, -1, -1, -1};
*/

//shared with GIAtranslatorDefineReferencing.cpp

class NLCcodeblock
{
public:

	NLCcodeblock(void);
	~NLCcodeblock(void);

	int codeBlockType;
	vector<NLCitem*> parameters;

	/*
	//used by language specific code generator (eg C++, java);
	string codeBlockName; 	//eg "for"
	string openingText;	//eg "for(...){"
	string closingText; 	//eg "}";
	*/

	NLCcodeblock * lowerLevel;
	NLCcodeblock * next;
};

NLCcodeblock * createCodeBlockExecute(NLCcodeblock * currentCodeBlockInTree, NLCitem * functionItem, NLCitem* objectItem);
NLCcodeblock * createCodeBlockExecute(NLCcodeblock * currentCodeBlockInTree, NLCitem * functionItem);
NLCcodeblock * createCodeBlockAddNewProperty(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* propertyEntity, int sentenceIndex);
	NLCcodeblock * createCodeBlockAddNewPropertyToLocalList(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* propertyEntity);
	NLCcodeblock * createCodeBlockAddPropertyToLocalList(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* propertyEntity);
	NLCcodeblock * createCodeBlockAddProperty(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* propertyEntity, int sentenceIndex);
NLCcodeblock * createCodeBlockAddNewCondition(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* conditionEntity, int sentenceIndex);
	NLCcodeblock * createCodeBlockAddCondition(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* conditionEntity, int sentenceIndex);
NLCcodeblock * createCodeBlocksCreateNewLocalListVariable(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* entity);
NLCcodeblock * createCodeBlocksDeclareNewLocalListVariable(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* entity);
NLCcodeblock * createCodeBlockForPropertyList(NLCcodeblock * currentCodeBlockInTree, NLCitem * item);
NLCcodeblock * createCodeBlockForPropertyListLocal(NLCcodeblock * currentCodeBlockInTree, NLCitem * item);
NLCcodeblock * createCodeBlockForConditionList(NLCcodeblock * currentCodeBlockInTree, NLCitem * item, NLCitem * objectItem);
NLCcodeblock * createCodeBlockNewFunction(NLCcodeblock * currentCodeBlockInTree, string NLCfunctionName, vector<GIAentityNode*> * entityNodesActiveListComplete);
	NLCcodeblock * createCodeBlockDeclareAndInitialiseVariableForActionSubject(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* functionOwner);
	NLCcodeblock * createCodeBlocksAddVariableToNewList(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* entity);
	#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS
	void generateLocalFunctionArgumentsBasedOnImplicitDeclarations(vector<GIAentityNode*> * entityNodesActiveListComplete, vector<NLCitem*> * parameters);
		bool assumedToAlreadyHaveBeenDeclared(GIAentityNode* entity);
	#endif
NLCcodeblock * createCodeBlockForStatements(NLCcodeblock * currentCodeBlockInTree, NLCitem * item, GIAentityNode* entity, int sentenceIndex);
	NLCcodeblock * createCodeBlockForGivenProperties(NLCcodeblock * currentCodeBlockInTree, NLCitem * item, GIAentityNode * entity, int sentenceIndex);
		NLCcodeblock * createCodeBlockForGivenProperty(NLCcodeblock * currentCodeBlockInTree, NLCitem * item, GIAentityNode* propertyEntity, int sentenceIndex);
	NLCcodeblock * createCodeBlockForGivenConditions(NLCcodeblock * currentCodeBlockInTree, NLCitem * item,  GIAentityNode * entity, int sentenceIndex);
		NLCcodeblock * createCodeBlockForGivenCondition(NLCcodeblock * currentCodeBlockInTree, NLCitem * item, GIAentityNode* conditionEntity, int sentenceIndex);

NLCcodeblock * createCodeBlock(NLCcodeblock * currentCodeBlockInTree, int codeBlockType);
NLCcodeblock * createLowerLevel(NLCcodeblock * currentCodeBlockInTree);

bool getEntityContext(GIAentityNode * entity, vector<string> * context, bool includePresentObject, int sentenceIndex, bool markSameSentenceParentsAsParsed);

bool checkSentenceIndexParsingCodeBlocks(GIAentityNode * entity, int sentenceIndex, bool checkIfEntityHasBeenParsedForNLCcodeBlocks);

bool checkDuplicateProperty(GIAentityNode * propertyEntity, GIAentityNode * childActionEntity);
bool checkDuplicateCondition(GIAentityNode * conditionEntity, GIAentityNode * childActionEntity);

#ifdef NLC_SUPPORT_INPUT_FILE_LISTS
string parseFunctionNameFromNLCfunctionName(string NLCfunctionName);
void parseFunctionNameFromNLCfunctionName(string NLCfunctionName, string * functionName, string * functionOwnerName, bool * foundFunctionOwnerClass);
void parseFunctionNameFromNLCfunctionName(string NLCfunctionName, string * functionName, string * functionOwnerName, bool * foundFunctionOwnerClass, string * functionObjectName, bool * foundFunctionObjectClass);
#endif

NLCcodeblock * createCodeBlockIfHasProperty(NLCcodeblock * currentCodeBlockInTree, NLCitem * itemProperty, bool negative);
NLCcodeblock * createCodeBlockIfHasCondition(NLCcodeblock * currentCodeBlockInTree, NLCitem * itemCondition, NLCitem * itemConditionObject, bool negative);
NLCcodeblock * createCodeBlockWhileHasProperty(NLCcodeblock * currentCodeBlockInTree, NLCitem * itemProperty, bool negative);
NLCcodeblock * createCodeBlockWhileHasCondition(NLCcodeblock * currentCodeBlockInTree, NLCitem * itemCondition, NLCitem * itemConditionObject, bool negative);


#endif
