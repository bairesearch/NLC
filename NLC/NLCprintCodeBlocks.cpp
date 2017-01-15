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
 * File Name: NLCprintCodeBlocks.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2014 Baxter AI (baxterai.com)
 * Project: Natural Language Programming Interface (compiler)
 * Project Version: 1l9f 05-November-2014
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/



#include <ctime>
#include <cstdlib>	//for random number generation
#include <cmath>

#include "NLCprintCodeBlocks.h"
#include "NLCprintDefs.h"
#include "GIAtranslatorDefs.h"	//required for ENTITY_COORDINATINGCONJUNCTION_ARRAY_INDEX_AND/ENTITY_COORDINATINGCONJUNCTION_ARRAY_INDEX_OR

bool printCodeBlocks(NLCcodeblock * firstCodeBlockInLevel, vector<NLCclassDefinition *> * classDefinitionList, int progLang, string * code, int level)
{
	NLCcodeblock * currentCodeBlockInLevel = firstCodeBlockInLevel;
	while(currentCodeBlockInLevel->next != NULL)
	{
		NLCitem * param1 = currentCodeBlockInLevel->parameters.at(0);
		string contextParam1 = generateStringFromContextVector(&(param1->context), progLang);

		//for logical operations only (NLC_CODEBLOCK_TYPE_IF_HAS_PROPERTY/NLC_CODEBLOCK_TYPE_IF_HAS_CONDITION/NLC_CODEBLOCK_TYPE_WHILE_HAS_PROPERTY/NLC_CODEBLOCK_TYPE_WHILE_HAS_CONDITION);
		string negativeModifierString = "";
		if(param1->negative)
		{
			negativeModifierString = "";
		}
		else
		{
			negativeModifierString = progLangNot[progLang];
		}

		if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_EXECUTE_FUNCTION)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_EXECUTE_FUNCTION" << endl;
			#endif

			bool hasActionSubject = false;
			NLCitem * functionOwnerArgument = NULL;
			string functionOwnerName = "";
			string functionOwnerNameWithReferenceDelimiter = "";
			if(findFunctionArgument(&(currentCodeBlockInLevel->parameters), NLC_ITEM_TYPE_FUNCTION_EXECUTION_ARGUMENT_FUNCTION_OWNER, &functionOwnerArgument))
			{
				functionOwnerName = functionOwnerArgument->instanceName;
				functionOwnerNameWithReferenceDelimiter = functionOwnerName + progLangObjectReferenceDelimiter[progLang];
				hasActionSubject = true;
			}
			
			NLCitem * functionArgument = NULL;
			string functionName = "";
			if(findFunctionArgument(&(currentCodeBlockInLevel->parameters), NLC_ITEM_TYPE_FUNCTION_EXECUTION_ARGUMENT_FUNCTION, &functionArgument))
			{
				functionName = functionArgument->functionName;
			}
			
			string functionArguments = "";
			generateFunctionExecutionArgumentsWithActionConceptInheritanceString(classDefinitionList, &(currentCodeBlockInLevel->parameters), &functionArguments, progLang);
			
			string codeBlockText = functionOwnerNameWithReferenceDelimiter + functionName + progLangOpenParameterSpace[progLang] + functionArguments + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//context1.param1(context.param2); 	[param1 = function, context1 = subject, param2 = object]			
			printLine(codeBlockText, level, code);
		}
		#ifdef NLC_RECORD_ACTION_HISTORY
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_RECORD_HISTORY_ACTION_SUBJECT)
		{
			NLCitem * functionArgument = NULL;
			string functionName = "";
			if(findFunctionArgument(&(currentCodeBlockInLevel->parameters), NLC_ITEM_TYPE_FUNCTION_EXECUTION_ARGUMENT_FUNCTION, &functionArgument))
			{
				functionName = functionArgument->functionName;
			}
			
			NLCitem * functionOwnerArgument = NULL;
			string functionOwnerName = "";
			if(findFunctionArgument(&(currentCodeBlockInLevel->parameters), NLC_ITEM_TYPE_FUNCTION_EXECUTION_ARGUMENT_FUNCTION_OWNER, &functionOwnerArgument))
			{
				functionOwnerName = functionOwnerArgument->instanceName;
			}
			
			string codeBlockTextAddAction = functionOwnerArgument->instanceName + progLangObjectReferenceDelimiter[progLang] + generateGenericListName(functionArgument->className, NLC_ITEM_TYPE_ACTION_VAR_APPENDITION) + progLangObjectReferenceDelimiter2[progLang] + progLangAddEntityToList[progLang] + progLangOpenParameterSpace[progLang] + functionArgument->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//actionSubject1->actionClassActionList.push_back(action1);
			printLine(codeBlockTextAddAction, level, code);
			string codeBlockTextAddAction2 = functionArgument->instanceName + progLangObjectReferenceDelimiter[progLang] + generateGenericListName(functionOwnerArgument->className, NLC_ITEM_TYPE_ACTIONSUBJECT_VAR_APPENDITION) + progLangObjectReferenceDelimiter2[progLang] + progLangAddEntityToList[progLang] + progLangOpenParameterSpace[progLang] + functionOwnerArgument->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//action1->actionSubjectClassActionSubjectList.push_back(actionSubject1);
			printLine(codeBlockTextAddAction2, level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_RECORD_HISTORY_ACTION_OBJECT)
		{
			NLCitem * functionArgument = NULL;
			string functionName = "";
			if(findFunctionArgument(&(currentCodeBlockInLevel->parameters), NLC_ITEM_TYPE_FUNCTION_EXECUTION_ARGUMENT_FUNCTION, &functionArgument))
			{
				functionName = functionArgument->functionName;
			}
			
			NLCitem * functionObjectArgument = NULL;
			string functionObjectName = "";
			if(findFunctionArgument(&(currentCodeBlockInLevel->parameters), NLC_ITEM_TYPE_FUNCTION_EXECUTION_ARGUMENT_FUNCTION_OBJECT, &functionObjectArgument))
			{
				functionObjectName = functionObjectArgument->instanceName;
			}
			
			string codeBlockTextAddAction = functionObjectArgument->instanceName + progLangObjectReferenceDelimiter[progLang] + generateGenericListName(functionArgument->className, NLC_ITEM_TYPE_ACTIONINCOMING_VAR_APPENDITION) + progLangObjectReferenceDelimiter2[progLang] + progLangAddEntityToList[progLang] + progLangOpenParameterSpace[progLang] + functionArgument->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//actionObject1->actionClassActionIncomingList.push_back(action1);
			printLine(codeBlockTextAddAction, level, code);
			string codeBlockTextAddAction2 = functionArgument->instanceName + progLangObjectReferenceDelimiter[progLang] + generateGenericListName(functionObjectArgument->className, NLC_ITEM_TYPE_ACTIONOBJECT_VAR_APPENDITION) + progLangObjectReferenceDelimiter2[progLang] + progLangAddEntityToList[progLang] + progLangOpenParameterSpace[progLang] + functionObjectArgument->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//action1->actionSubjectClassActionSubjectList.push_back(actionSubject1);
			printLine(codeBlockTextAddAction2, level, code);
		}	
		#endif	
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_ADD_NEW_PROPERTY)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_ADD_NEW_PROPERTY" << endl;
			#endif
			NLCitem * param2 = currentCodeBlockInLevel->parameters.at(1);

			string codeBlockTextCreate = generateEntityDeclaration(param2, progLang) + progLangEquals[progLang] + progLangNewObject[progLang] + param2->className + progLangOpenParameterSpace[progLang] + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];
			printLine(codeBlockTextCreate, level, code);
			string codeBlockText = contextParam1 + param1->instanceName + progLangObjectReferenceDelimiter[progLang] + generatePropertyListName(param2->className) + progLangObjectReferenceDelimiter2[progLang] + progLangAddProperty[progLang] + progLangOpenParameterSpace[progLang] + param2->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//context1->param1->param2PropertyList.push_back(param2);
			printLine(codeBlockText, level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_ADD_NEW_ENTITY_TO_LOCAL_LIST)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_ADD_NEW_ENTITY_TO_LOCAL_LIST" << endl;
			#endif
			NLCitem * param2 = currentCodeBlockInLevel->parameters.at(1);

			string codeBlockTextCreate = generateEntityDeclaration(param2, progLang) + progLangEquals[progLang] + progLangNewObject[progLang] + param2->className + progLangOpenParameterSpace[progLang] + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];
			printLine(codeBlockTextCreate, level, code);
			string codeBlockText = generateEntityListName(param1) + progLangObjectReferenceDelimiter2[progLang] + progLangAddEntityToList[progLang] + progLangOpenParameterSpace[progLang] + param2->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//param1instanceList.push_back(param2);
			printLine(codeBlockText, level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_ADD_NEW_CONDITION)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_ADD_NEW_CONDITION" << endl;
			#endif
			NLCitem * param2 = currentCodeBlockInLevel->parameters.at(1);
			NLCitem * param3 = currentCodeBlockInLevel->parameters.at(2);
			string codeBlockTextCreate = generateEntityDeclaration(param3, progLang) + progLangEquals[progLang] + progLangNewObject[progLang] + param3->className + progLangOpenParameterSpace[progLang] + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];
			printLine(codeBlockTextCreate, level, code);
			#ifndef NLC_USE_STRING_INDEXED_UNORDERED_MAPS_FOR_CONDITION_LISTS
			string codeBlockTextCreate2 = generateEntityDeclaration(param2, progLang) + progLangEquals[progLang] + progLangNewObject[progLang] + param2->className + progLangOpenParameterSpace[progLang] + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];
			printLine(codeBlockTextCreate2, level, code);
			#endif
			string codeBlockText = contextParam1 + param1->instanceName + progLangObjectReferenceDelimiter[progLang] + generateConditionListName(param2->className, param3->className) + progLangObjectReferenceDelimiter2[progLang] + progLangAddCondition[progLang] + progLangOpenParameterSpace[progLang] + generateCodeConditionPairText(param2->name, param2->className, param2->instanceName, param3->className, param3->instanceName, progLang) + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//context1->param1->param2param3ConditionList.insert(pair<param2className, param3className*>(param2, param3));
			printLine(codeBlockText, level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_ADD_PROPERTY)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_ADD_PROPERTY" << endl;
			#endif
			NLCitem * param2 = currentCodeBlockInLevel->parameters.at(1);

			string codeBlockText = contextParam1 + param1->instanceName + progLangObjectReferenceDelimiter[progLang] + generatePropertyListName(param2->className) + progLangObjectReferenceDelimiter2[progLang] + progLangAddProperty[progLang] + progLangOpenParameterSpace[progLang] + param2->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//context1->param1->param2PropertyList.push_back(param2);
			printLine(codeBlockText, level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_LOCAL_LIST)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_LOCAL_LIST" << endl;
			#endif
			NLCitem * param2 = currentCodeBlockInLevel->parameters.at(1);

			string codeBlockText = generateEntityListName(param1) + progLangObjectReferenceDelimiter2[progLang] + progLangAddEntityToList[progLang] + progLangOpenParameterSpace[progLang] + param2->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//param1instanceList.push_back(param2);
			
			printLine(codeBlockText, level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_ADD_CONDITION)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_ADD_CONDITION" << endl;
			#endif
			NLCitem * param2 = currentCodeBlockInLevel->parameters.at(1);
			NLCitem * param3 = currentCodeBlockInLevel->parameters.at(2);
			#ifndef NLC_USE_STRING_INDEXED_UNORDERED_MAPS_FOR_CONDITION_LISTS
			string codeBlockTextCreate2 = generateEntityDeclaration(param2, progLang) + progLangEquals[progLang] + progLangNewObject[progLang] + param2->className + progLangOpenParameterSpace[progLang] + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];
			printLine(codeBlockTextCreate2, level, code);
			#endif
			string codeBlockText = contextParam1 + param1->instanceName + progLangObjectReferenceDelimiter[progLang] + generateConditionListName(param2->className,  param3->className) + progLangObjectReferenceDelimiter2[progLang] + progLangAddCondition[progLang] + progLangOpenParameterSpace[progLang] + generateCodeConditionPairText(param2->name, param2->className, param2->instanceName, param3->className, param3->instanceName, progLang) + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//context1->param1->param2param3ConditionList.insert(pair<param2className, param3className*>(param2, param3));
			printLine(codeBlockText, level, code);

		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_FOR_PROPERTY_LIST)
		{
			string iterIndexString = convertIntToString(level);
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_FOR_PROPERTY_LIST" << endl;
			#endif
			string codeBlockText = progLangFor[progLang] + progLangForIterPart1[progLang] + generateCodeEntityListDefinitionTypeText(param1->className, progLang) + progLangForIterPart2a[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart2c[progLang] + contextParam1 + generatePropertyListName(param1->className) + progLangForIterPart3a[progLang] + progLangForIterPart3b[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart3c[progLang] + contextParam1 + generatePropertyListName(param1->className) + progLangForIterPart4a[progLang] + progLangForIterPart4b[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart4c[progLang];
			printLine(codeBlockText, level, code);
			printLine(progLangOpenBlock[progLang], level, code);
			string tempVarDeclarationText = generateEntityDeclaration(param1, progLang) + progLangEquals[progLang] + progLangPointer[progLang] + progLangForIterName[progLang] + iterIndexString + progLangEndLine[progLang];	//OLD:  param1->className + NLC_ITEM_TYPE_TEMP_VAR_APPENDITION
			printLine(tempVarDeclarationText, (level+1), code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_FOR_LOCAL_LIST)
		{
			string iterIndexString = convertIntToString(level);
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_FOR_LOCAL_LIST" << endl;
			#endif
			string codeBlockText = progLangFor[progLang] + progLangForIterPart1[progLang] + generateCodeEntityListDefinitionTypeText(param1->className, progLang) + progLangForIterPart2a[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart2c[progLang] + generateEntityListName(param1) + progLangForIterPart3a[progLang] + progLangForIterPart3b[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart3c[progLang] + generateEntityListName(param1) + progLangForIterPart4a[progLang] + progLangForIterPart4b[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart4c[progLang];
			printLine(codeBlockText, level, code);
			printLine(progLangOpenBlock[progLang], level, code);
			string tempVarDeclarationText = generateEntityDeclaration(param1, progLang) + progLangEquals[progLang] + progLangPointer[progLang] + progLangForIterName[progLang] + iterIndexString + progLangEndLine[progLang];	//OLD:  param1->className + NLC_ITEM_TYPE_TEMP_VAR_APPENDITION
			printLine(tempVarDeclarationText, (level+1), code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_FOR_CONDITION_LIST)
		{
			string iterIndexString = convertIntToString(level);
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_FOR_CONDITION_LIST" << endl;
			#endif
			NLCitem * param2 = currentCodeBlockInLevel->parameters.at(1);
			string codeBlockText = progLangFor[progLang] + progLangForIterPart1[progLang] + generateCodeConditionListDefinitionTypeText(param1->className, param2->className, progLang) + progLangForIterPart2a[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart2c[progLang] + contextParam1 + generateConditionListName(param1->className, param2->className) + progLangForIterPart3a[progLang] + progLangForIterPart3b[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart3cMap[progLang] + contextParam1 + generateConditionListName(param1->className, param2->className) + progLangForIterPart4a[progLang] + progLangForIterPart4b[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart4c[progLang];
			printLine(codeBlockText, level, code);
			printLine(progLangOpenBlock[progLang], level, code);
			string tempVarDeclarationText = generateEntityDeclaration(param2, progLang) + progLangEquals[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterConditionObjectReference[progLang] + progLangEndLine[progLang];
			printLine(tempVarDeclarationText, (level+1), code);
		}
		#ifdef NLC_RECORD_ACTION_HISTORY
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_FOR_ACTION_LIST)
		{
			string iterIndexString = convertIntToString(level);
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_FOR_ACTION_LIST" << endl;
			#endif
			string codeBlockText = progLangFor[progLang] + progLangForIterPart1[progLang] + generateCodeEntityListDefinitionTypeText(param1->className, progLang) + progLangForIterPart2a[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart2c[progLang] + contextParam1 + generateActionListName(param1->className) + progLangForIterPart3a[progLang] + progLangForIterPart3b[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart3c[progLang] + contextParam1 + generateActionListName(param1->className) + progLangForIterPart4a[progLang] + progLangForIterPart4b[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart4c[progLang];
			printLine(codeBlockText, level, code);
			printLine(progLangOpenBlock[progLang], level, code);
			string tempVarDeclarationText = generateEntityDeclaration(param1, progLang) + progLangEquals[progLang] + progLangPointer[progLang] + progLangForIterName[progLang] + iterIndexString + progLangEndLine[progLang];
			printLine(tempVarDeclarationText, (level+1), code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_FOR_ACTION_INCOMING_LIST)
		{
			string iterIndexString = convertIntToString(level);
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_FOR_ACTION_INCOMING_LIST" << endl;
			#endif
			string codeBlockText = progLangFor[progLang] + progLangForIterPart1[progLang] + generateCodeEntityListDefinitionTypeText(param1->className, progLang) + progLangForIterPart2a[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart2c[progLang] + contextParam1 + generateActionIncomingListName(param1->className) + progLangForIterPart3a[progLang] + progLangForIterPart3b[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart3c[progLang] + contextParam1 + generateActionIncomingListName(param1->className) + progLangForIterPart4a[progLang] + progLangForIterPart4b[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart4c[progLang];
			printLine(codeBlockText, level, code);
			printLine(progLangOpenBlock[progLang], level, code);
			string tempVarDeclarationText = generateEntityDeclaration(param1, progLang) + progLangEquals[progLang] + progLangPointer[progLang] + progLangForIterName[progLang] + iterIndexString + progLangEndLine[progLang];	//OLD:  param1->className + NLC_ITEM_TYPE_TEMP_VAR_APPENDITION
			printLine(tempVarDeclarationText, (level+1), code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_FOR_ACTION_OBJECT_LIST)
		{
			string iterIndexString = convertIntToString(level);
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_FOR_ACTION_OBJECT_LIST" << endl;
			#endif
			string codeBlockText = progLangFor[progLang] + progLangForIterPart1[progLang] + generateCodeEntityListDefinitionTypeText(param1->className, progLang) + progLangForIterPart2a[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart2c[progLang] + contextParam1 + generateActionObjectListName(param1->className) + progLangForIterPart3a[progLang] + progLangForIterPart3b[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart3c[progLang] + contextParam1 + generateActionObjectListName(param1->className) + progLangForIterPart4a[progLang] + progLangForIterPart4b[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart4c[progLang];
			printLine(codeBlockText, level, code);
			printLine(progLangOpenBlock[progLang], level, code);
			string tempVarDeclarationText = generateEntityDeclaration(param1, progLang) + progLangEquals[progLang] + progLangPointer[progLang] + progLangForIterName[progLang] + iterIndexString + progLangEndLine[progLang];	//OLD:  param1->className + NLC_ITEM_TYPE_TEMP_VAR_APPENDITION
			printLine(tempVarDeclarationText, (level+1), code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_FOR_ACTION_SUBJECT_LIST)
		{
			string iterIndexString = convertIntToString(level);
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_FOR_ACTION_SUBJECT_LIST" << endl;
			#endif
			string codeBlockText = progLangFor[progLang] + progLangForIterPart1[progLang] + generateCodeEntityListDefinitionTypeText(param1->className, progLang) + progLangForIterPart2a[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart2c[progLang] + contextParam1 + generateActionSubjectListName(param1->className) + progLangForIterPart3a[progLang] + progLangForIterPart3b[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart3c[progLang] + contextParam1 + generateActionSubjectListName(param1->className) + progLangForIterPart4a[progLang] + progLangForIterPart4b[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart4c[progLang];
			printLine(codeBlockText, level, code);
			printLine(progLangOpenBlock[progLang], level, code);
			string tempVarDeclarationText = generateEntityDeclaration(param1, progLang) + progLangEquals[progLang] + progLangPointer[progLang] + progLangForIterName[progLang] + iterIndexString + progLangEndLine[progLang];	//OLD:  param1->className + NLC_ITEM_TYPE_TEMP_VAR_APPENDITION
			printLine(tempVarDeclarationText, (level+1), code);
		}
		#endif
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_FOR_INTEGER)
		{
			string iterIndexString = convertIntToString(level);
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_FOR_INTEGER" << endl;
			#endif
			string indexName = progLangForIndex[progLang] + iterIndexString;
			string codeBlockText = progLangFor[progLang] + progLangForIndexPart1[progLang] + progLangInteger[progLang] + indexName + progLangForIndexPart2[progLang] + indexName + progLangForIndexPart3[progLang] + param1->name + progLangForIndexPart4[progLang] + indexName + progLangForIndexPart5[progLang];
			printLine(codeBlockText, level, code);
			printLine(progLangOpenBlock[progLang], level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_NEW_FUNCTION)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_NEW_FUNCTION" << endl;
			#endif
			
			NLCitem * functionArgument = NULL;
			string functionName = "";
			if(findFunctionArgument(&(currentCodeBlockInLevel->parameters), NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION, &functionArgument))
			{
				functionName = functionArgument->functionName;
			}
			
			string functionArguments = "";
			#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS
			generateFunctionArgumentsBasedOnActionAndActionObjectVars(&(currentCodeBlockInLevel->parameters), &functionArguments, progLang);
			#endif
			#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS
			generateLocalFunctionArgumentsBasedOnImplicitDeclarationsString(&(currentCodeBlockInLevel->parameters), &functionArguments, progLang);
			#endif
			string functionOwnerContext = generateFunctionOwnerContext(&(currentCodeBlockInLevel->parameters), progLang);
			string codeBlockText = functionOwnerContext + functionName + progLangOpenParameterSpace[progLang] + functionArguments + progLangCloseParameterSpace[progLang];	//main(){
			printLine(codeBlockText, level, code);
			printLine(progLangOpenBlock[progLang], level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_DECLARE_AND_INITIALISE_VARIABLE)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_DECLARE_AND_INITIALISE_VARIABLE" << endl;
			#endif
			NLCitem * param2 = currentCodeBlockInLevel->parameters.at(1);

			string codeBlockTextDeclareAndInitialiseVariable = generateEntityDeclaration(param1, progLang) + progLangEquals[progLang] + param2->instanceName + progLangEndLine[progLang];
			printLine(codeBlockTextDeclareAndInitialiseVariable, level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_DECLARE_NEW_VARIABLE)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_DECLARE_NEW_VARIABLE" << endl;
			#endif
			string codeBlockTextDeclareNewVariable = generateEntityDeclaration(param1, progLang) + progLangEquals[progLang] + progLangNewObject[progLang] + param1->className + progLangOpenParameterSpace[progLang] + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];
			printLine(codeBlockTextDeclareNewVariable, level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_DECLARE_NEW_LOCAL_LIST_VARIABLE)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_DECLARE_NEW_LOCAL_LIST_VARIABLE" << endl;
			#endif
			string localListDeclarationText = generateCodeEntityListDefinitionTypeText(param1->className, progLang) + generateEntityListName(param1) + progLangEndLine[progLang];	//vector<param1Class*> param1instanceList;
			printLine(localListDeclarationText, level, code);
		}
		#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
		#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS_ADVANCED
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_IF_LOGICAL_CONJUNCTION_OF_BOOLS)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_IF_LOGICAL_CONJUNCTION_OF_BOOLS" << endl;
			#endif
			string codeBlockText =  progLangIf[progLang] + progLangOpenParameterSpace[progLang] + generateLogicalConjunctionOfBoolsText(&(currentCodeBlockInLevel->parameters), progLang) + progLangCloseParameterSpace[progLang];
			printLine(codeBlockText, level, code);
			printLine(progLangOpenBlock[progLang], level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_ELSE_IF_LOGICAL_CONJUNCTION_OF_BOOLS)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_ELSE_IF_LOGICAL_CONJUNCTION_OF_BOOLS" << endl;
			#endif
			string codeBlockText = progLangElseIf[progLang] + progLangOpenParameterSpace[progLang] + generateLogicalConjunctionOfBoolsText(&(currentCodeBlockInLevel->parameters), progLang) + progLangCloseParameterSpace[progLang];
			printLine(codeBlockText, level, code);
			printLine(progLangOpenBlock[progLang], level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_WHILE_LOGICAL_CONJUNCTION_OF_BOOLS)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_WHILE_LOGICAL_CONJUNCTION_OF_BOOLS" << endl;
			#endif
			string codeBlockText = progLangWhile[progLang] + progLangOpenParameterSpace[progLang] + generateLogicalConjunctionOfBoolsText(&(currentCodeBlockInLevel->parameters), progLang) + progLangCloseParameterSpace[progLang];
			printLine(codeBlockText, level, code);
			printLine(progLangOpenBlock[progLang], level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_DECLARE_NEW_BOOL_ARRAY_INITIALISE_TRUE)
		{//CHECK THIS: not used
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_DECLARE_NEW_BOOL_ARRAY_INITIALISE_TRUE" << endl;
			#endif
			string arraySizeString = convertIntToString(NLC_MAXIMUM_NUMBER_OF_CONJUNCTIONS_IN_SENTENCE);	//make this dynamic
			string codeBlockText = progLangBoolean[progLang] + param1->name + progLangArrayOpen[progLang] + arraySizeString + progLangArrayClose[progLang] + progLangEquals[progLang] + progLangArrayInitialisationOpen[progLang] + progLangTrue[progLang] + progLangArrayInitialisationClose[progLang] + progLangEndLine[progLang];
			printLine(codeBlockText, level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_DECLARE_NEW_BOOL_ARRAY_INITIALISE_FALSE)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_DECLARE_NEW_BOOL_ARRAY_INITIALISE_FALSE" << endl;
			#endif
			string arraySizeString = convertIntToString(NLC_MAXIMUM_NUMBER_OF_CONJUNCTIONS_IN_SENTENCE);	//make this dynamic
			string codeBlockText = progLangBoolean[progLang] + param1->name + progLangArrayOpen[progLang] + arraySizeString + progLangArrayClose[progLang] + progLangEquals[progLang] + progLangArrayInitialisationOpen[progLang] + progLangFalse[progLang] + progLangArrayInitialisationClose[progLang] + progLangEndLine[progLang];
			printLine(codeBlockText, level, code);
		}
		#else
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_IF_HAS_PROPERTY)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_IF_HAS_PROPERTY" << endl;
			#endif

			string codeBlockText = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + negativeModifierString + progLangOpenParameterSpace[progLang] + contextParam1 + generatePropertyListName(param1->className) + progLangObjectReferenceDelimiter2[progLang] + progLangHasEntity[progLang] + progLangCloseParameterSpace[progLang] + progLangCloseParameterSpace[progLang];		//if(!(context1->param1PropertyList.empty())){

			printLine(codeBlockText, level, code);
			printLine(progLangOpenBlock[progLang], level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_IF_HAS_CONDITION)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_IF_HAS_CONDITION" << endl;
			#endif

			NLCitem * param2 = currentCodeBlockInLevel->parameters.at(1);
			string codeBlockText = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + negativeModifierString + progLangOpenParameterSpace[progLang] + contextParam1 + generateConditionListName(param1->className, param2->className) + progLangObjectReferenceDelimiter2[progLang] + progLangHasCondition[progLang] + progLangCloseParameterSpace[progLang] + progLangCloseParameterSpace[progLang];	//if(!(context1->param1param2ConditionList.empty())){
			printLine(codeBlockText, level, code);
			printLine(progLangOpenBlock[progLang], level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_WHILE_HAS_PROPERTY)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_WHILE_HAS_PROPERTY" << endl;
			#endif

			string codeBlockText = progLangWhile[progLang] + progLangOpenParameterSpace[progLang] + negativeModifierString + progLangOpenParameterSpace[progLang] + contextParam1 + generatePropertyListName(param1->className) + progLangObjectReferenceDelimiter2[progLang] + progLangHasEntity[progLang] + progLangCloseParameterSpace[progLang] + progLangCloseParameterSpace[progLang];		//while(!(context1->param1PropertyList.empty())){

			printLine(codeBlockText, level, code);
			printLine(progLangOpenBlock[progLang], level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_WHILE_HAS_CONDITION)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_WHILE_HAS_CONDITION" << endl;
			#endif

			NLCitem * param2 = currentCodeBlockInLevel->parameters.at(1);

			string codeBlockText = progLangWhile[progLang] + progLangOpenParameterSpace[progLang] + negativeModifierString + progLangOpenParameterSpace[progLang] + contextParam1 + generateConditionListName(param1->className, param2->className) + progLangObjectReferenceDelimiter2[progLang] + progLangHasCondition[progLang] + progLangCloseParameterSpace[progLang] + progLangCloseParameterSpace[progLang];	//while(!(context1->param1param2ConditionList.empty())){
			printLine(codeBlockText, level, code);
			printLine(progLangOpenBlock[progLang], level, code);
		}
		#endif
		#endif
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_ELSE)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_ELSE" << endl;
			#endif
			string codeBlockText = progLangElse[progLang];
			printLine(codeBlockText, level, code);
			printLine(progLangOpenBlock[progLang], level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_WHILE)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_WHILE" << endl;
			#endif
			string codeBlockText = progLangWhile[progLang] + progLangOpenParameterSpace[progLang] + param1->name + progLangCloseParameterSpace[progLang];
			printLine(codeBlockText, level, code);
			printLine(progLangOpenBlock[progLang], level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_DECLARE_NEW_BOOL_VARIABLE_INITIALISE_TRUE)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_DECLARE_NEW_BOOL_VARIABLE_INITIALISE_TRUE" << endl;
			#endif
			string codeBlockText = progLangBoolean[progLang] + param1->name + progLangEquals[progLang] + progLangTrue[progLang] + progLangEndLine[progLang];
			printLine(codeBlockText, level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_DECLARE_NEW_BOOL_VARIABLE_INITIALISE_FALSE)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_DECLARE_NEW_BOOL_VARIABLE_INITIALISE_FALSE" << endl;
			#endif
			string codeBlockText = progLangBoolean[progLang] + param1->name + progLangEquals[progLang] + progLangFalse[progLang] + progLangEndLine[progLang];
			printLine(codeBlockText, level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_SET_BOOL_VARIABLE_TRUE)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_SET_BOOL_VARIABLE_TRUE" << endl;
			#endif
			string codeBlockText = param1->name + progLangEquals[progLang] + progLangTrue[progLang] + progLangEndLine[progLang];
			printLine(codeBlockText, level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_SET_BOOL_VARIABLE_FALSE)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_SET_BOOL_VARIABLE_FALSE" << endl;
			#endif
			string codeBlockText = param1->name + progLangEquals[progLang] + progLangFalse[progLang] + progLangEndLine[progLang];
			printLine(codeBlockText, level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_DEBUG)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_DEBUG" << endl;
			#endif
			string codeBlockText = param1->name;
			printLine(codeBlockText, level, code);
		}
		#ifdef NLC_TRANSLATE_NEGATIVE_PROPERTIES_AND_CONDITIONS
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_REMOVE_PROPERTIES)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_REMOVE_PROPERTIES" << endl;
			#endif
			NLCitem * param2 = currentCodeBlockInLevel->parameters.at(1);

			string codeBlockText = contextParam1 + param1->instanceName + progLangObjectReferenceDelimiter[progLang] + generatePropertyListName(param2->className) + progLangObjectReferenceDelimiter2[progLang] + progLangRemoveProperties[progLang] + progLangEndLine[progLang];		//context1->param1->param2PropertyList.clear();
			printLine(codeBlockText, level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_REMOVE_ENTITIES_FROM_LOCAL_LIST)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_REMOVE_ENTITIES_FROM_LOCAL_LIST" << endl;
			#endif

			string codeBlockText = generateEntityListName(param1) + progLangObjectReferenceDelimiter2[progLang] + progLangRemoveProperties[progLang] + progLangEndLine[progLang];		//param1instanceList.clear();
			printLine(codeBlockText, level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_REMOVE_CONDITIONS)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_REMOVE_CONDITIONS" << endl;
			#endif
			NLCitem * param2 = currentCodeBlockInLevel->parameters.at(1);
			NLCitem * param3 = currentCodeBlockInLevel->parameters.at(2);
			string codeBlockText = contextParam1 + param1->instanceName + progLangObjectReferenceDelimiter[progLang] + generateConditionListName(param2->className,  param3->className) + progLangObjectReferenceDelimiter2[progLang] + progLangRemoveConditions[progLang] + progLangEndLine[progLang];	//context1->param1->param2param3ConditionList.clear();
			printLine(codeBlockText, level, code);

		}
		#endif
		#ifdef NLC_PREPROCESSOR_MATH
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_MATHTEXT_LINE)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_MATHTEXT_LINE" << endl;
			#endif
			string codeBlockText = param1->name + progLangEndLine[progLang];
			printLine(codeBlockText, level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_MATHTEXT_WITH_LOGICAL_OPERATOR)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_MATHTEXT_WITH_LOGICAL_OPERATOR" << endl;
			#endif
			string codeBlockText = param1->name;
			printLine(codeBlockText, level, code);
			printLine(progLangOpenBlock[progLang], level, code);
		}		
		#endif
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_DECLARE_NEW_INT_VARIABLE)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_DECLARE_NEW_INT_VARIABLE" << endl;
			#endif
			NLCitem * param2 = currentCodeBlockInLevel->parameters.at(1);
			string codeBlockText = progLangInteger[progLang] + param1->name + progLangEquals[progLang] + param2->name + progLangEndLine[progLang];
			printLine(codeBlockText, level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_INCREMENT_INT_VARIABLE)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_INCREMENT_INT_VARIABLE" << endl;
			#endif
			string codeBlockText = param1->name + progLangEquals[progLang] + param1->name + progLangMathPlus[progLang] + string("1") + progLangEndLine[progLang];
			printLine(codeBlockText, level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_COMMENT_SINGLE_LINE)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_COMMENT_SINGLE_LINE" << endl;
			#endif
			string codeBlockText = progLangOpenSingleLineComment[progLang] + param1->name;
			printLine(codeBlockText, level, code);
		}
		#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_REASSIGN_ITER)
		{
			string iterIndexString = convertIntToString(level-1);
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_REASSIGN_ITER" << endl;
			#endif
			string tempVarDeclarationText = param1->instanceName + progLangEquals[progLang] + progLangPointer[progLang] + progLangForIterName[progLang] + iterIndexString + progLangEndLine[progLang];
			printLine(tempVarDeclarationText, level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_DECLARE_NEW_GENERIC_LIST_VARIABLE)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_DECLARE_NEW_GENERIC_LIST_VARIABLE" << endl;
			#endif
			NLCitem * param2 = currentCodeBlockInLevel->parameters.at(1);
			string genericListAppendName = param2->name;
	
			string localListDeclarationText = generateCodeGenericListDefinitionText(param1, genericListAppendName, progLang) + progLangEndLine[progLang];	//vector<param1Class*> param1CategoryList;
			printLine(localListDeclarationText, level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST" << endl;
			#endif
			NLCitem * param2 = currentCodeBlockInLevel->parameters.at(1);
			NLCitem * param3 = currentCodeBlockInLevel->parameters.at(2);
			string genericListAppendName = param3->name;

			string codeBlockText = generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangObjectReferenceDelimiter2[progLang] + progLangAddEntityToList[progLang] + progLangOpenParameterSpace[progLang] + param2->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//param1CategoryList.push_back(param2);
			printLine(codeBlockText, level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_FOR_GENERIC_LIST)
		{
			string iterIndexString = convertIntToString(level);
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_FOR_GENERIC_LIST" << endl;
			#endif
			NLCitem * param2 = currentCodeBlockInLevel->parameters.at(1);
			string genericListAppendName = param2->name;
			
			string codeBlockText = progLangFor[progLang] + progLangForIterPart1[progLang] + generateCodeEntityListDefinitionTypeText(param1->className, progLang) + progLangForIterPart2a[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart2c[progLang] + generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangForIterPart3a[progLang] + progLangForIterPart3b[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart3c[progLang] + generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangForIterPart4a[progLang] + progLangForIterPart4b[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart4c[progLang];
			printLine(codeBlockText, level, code);
			printLine(progLangOpenBlock[progLang], level, code);
			string tempVarDeclarationText = generateEntityDeclaration(param1, progLang) + progLangEquals[progLang] + progLangPointer[progLang] + progLangForIterName[progLang] + iterIndexString + progLangEndLine[progLang];	//OLD:  param1->className + NLC_ITEM_TYPE_TEMP_VAR_APPENDITION
			printLine(tempVarDeclarationText, (level+1), code);
		}
		#ifdef NLC_CATEGORIES_TEST_PLURALITY
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_IF_HAS_GENERIC_ENTITY)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_IF_HAS_GENERIC_ENTITY" << endl;
			#endif
			NLCitem * param2 = currentCodeBlockInLevel->parameters.at(1);
			string genericListAppendName = param2->name;

			string codeBlockText = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + negativeModifierString + progLangOpenParameterSpace[progLang] + generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangObjectReferenceDelimiter2[progLang] + progLangHasEntity[progLang] + progLangCloseParameterSpace[progLang] + progLangCloseParameterSpace[progLang];		//if(!(param1CategoryList.empty())){

			printLine(codeBlockText, level, code);
			printLine(progLangOpenBlock[progLang], level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_PRINT_WARNING)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_PRINT_WARNING" << endl;
			#endif
			string codeBlockText = progLangPrintTextOpen[progLang] + param1->name + progLangPrintTextClose[progLang]  + progLangEndLine[progLang];	//cout << "warning" << endl;
			printLine(codeBlockText, level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_IF_HAS_GREATER_THAN_NUM_GENERIC_ENTITY)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_IF_HAS_GREATER_THAN_NUM_GENERIC_ENTITY" << endl;
			#endif
			NLCitem * param2 = currentCodeBlockInLevel->parameters.at(1);
			string genericListAppendName = param2->name;

			NLCitem * param3 = currentCodeBlockInLevel->parameters.at(2);
			string valueString = param3->name;

			string codeBlockText = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangObjectReferenceDelimiter2[progLang] + progLangSizeOfList[progLang] + progLangGreaterThan[progLang] + valueString + progLangCloseParameterSpace[progLang];		//if(param1CategoryList.size() > X){

			printLine(codeBlockText, level, code);
			printLine(progLangOpenBlock[progLang], level, code);
		}
		#endif
		#ifdef NLC_USE_ADVANCED_REFERENCING
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_GET_BACK_GENERIC_ENTITY_LIST)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_GET_BACK_GENERIC_ENTITY_LIST" << endl;
			#endif
			NLCitem * param2 = currentCodeBlockInLevel->parameters.at(1);
			string genericListAppendName = param2->name;

			string tempVarDeclarationText = generateEntityDeclaration(param1, progLang) + progLangEquals[progLang] + generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangObjectReferenceDelimiter2[progLang] + progLangGetLast[progLang] + progLangEndLine[progLang];

			printLine(tempVarDeclarationText, level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST_CHECK_LAST_SENTENCE_REFERENCED_SINGULAR_EXECUTE_FUNCTION)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST_CHECK_LAST_SENTENCE_REFERENCED_SINGULAR_EXECUTE_FUNCTION" << endl;
			#endif

			NLCitem * param2 = currentCodeBlockInLevel->parameters.at(1);
			NLCitem * param3 = currentCodeBlockInLevel->parameters.at(2);
			string genericListAppendName = param3->name;
			
			string codeBlockText = "";
			string codeBlockTextTemplateDefinition = progLangTemplateUsePart1[progLang] + param1->className + progLangTemplateUseClassSeparator[progLang] + STRING_SPACE + param2->className + progLangTemplateUsePart2[progLang] + STRING_SPACE; 	//<param1class, param2class> 
			codeBlockText = codeBlockText + NLC_USE_ADVANCED_REFERENCING_SINGULAR_DEFINITE_REFERENCING_TESTS_FUNCTION_NAME + codeBlockTextTemplateDefinition + progLangOpenParameterSpace[progLang] + generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangClassMemberFunctionParametersNext[progLang] + param2->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//addToCategoryIfPassSingularDefinitePluralityTests<param1class, param2class> (param1CategoryList, param2instanceName);				
			printLine(codeBlockText, level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST_CHECK_LAST_SENTENCE_REFERENCED_SINGULAR_NEW_FUNCTION)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST_CHECK_LAST_SENTENCE_REFERENCED_SINGULAR_NEW_FUNCTION" << endl;
			#endif
			NLCitem * param2 = currentCodeBlockInLevel->parameters.at(1);
			NLCitem * param3 = currentCodeBlockInLevel->parameters.at(2);
			string genericListAppendName = param3->name;
			
			string templateName1 = "E1";
			string templateName2 = "E2";
			string codeBlockTextTemplateHeader = progLangTemplateHeaderPart1[progLang] + progLangTemplateHeaderClassType[progLang] + templateName1 + progLangTemplateUseClassSeparator[progLang] + STRING_SPACE + progLangTemplateHeaderClassType[progLang] + templateName2 + progLangTemplateHeaderPart2[progLang];  //template <class E1, class E2>
			string codeBlockTextFunctionHeader = progLangClassMemberFunctionDefaultType[progLang] + NLC_USE_ADVANCED_REFERENCING_SINGULAR_DEFINITE_REFERENCING_TESTS_FUNCTION_NAME + progLangOpenParameterSpace[progLang] + generateCodeEntityListDefinitionReferenceTypeText(templateName1, progLang) + generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangClassMemberFunctionParametersNext[progLang] + templateName2 + progLangPointer[progLang] + STRING_SPACE + param2->instanceName + progLangCloseParameterSpace[progLang];	//void addToCategoryIfPassSingularDefinitePluralityTests(vector<E1*> &param1CategoryList, E2* param2instanceName)

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

			#ifdef NLC_USE_ADVANCED_REFERENCING_DO_NOT_ADD_DUPLICATES
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
						#ifdef NLC_USE_ADVANCED_REFERENCING_DO_NOT_ADD_DUPLICATES
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
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST_CHECK_LAST_SENTENCE_REFERENCED_PLURAL_EXECUTE_FUNCTION)
		{//finish coding this
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST_CHECK_LAST_SENTENCE_REFERENCED_PLURAL_EXECUTE_FUNCTION" << endl;
			#endif

			NLCitem * param2 = currentCodeBlockInLevel->parameters.at(1);
			NLCitem * param3 = currentCodeBlockInLevel->parameters.at(2);
			string genericListAppendName = param3->name;
			
			string codeBlockText = "";
			string codeBlockTextTemplateDefinition = progLangTemplateUsePart1[progLang] + param1->className + progLangTemplateUseClassSeparator[progLang] + STRING_SPACE + param2->className + progLangTemplateUsePart2[progLang] + STRING_SPACE; 	////<param1class, param2class> 
			codeBlockText = codeBlockText + NLC_USE_ADVANCED_REFERENCING_PLURAL_DEFINITE_REFERENCING_TESTS_FUNCTION_NAME + codeBlockTextTemplateDefinition + progLangOpenParameterSpace[progLang] + generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangClassMemberFunctionParametersNext[progLang] + param2->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//addToCategoryIfPassSingularDefinitePluralityTests<param1class, param2class> (param1CategoryList, param2instanceName);				
			printLine(codeBlockText, level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST_CHECK_LAST_SENTENCE_REFERENCED_PLURAL_NEW_FUNCTION)
		{//finish coding this
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST_CHECK_LAST_SENTENCE_REFERENCED_PLURAL_NEW_FUNCTION" << endl;
			#endif
			NLCitem * param2 = currentCodeBlockInLevel->parameters.at(1);
			NLCitem * param3 = currentCodeBlockInLevel->parameters.at(2);
			string genericListAppendName = param3->name;
			
			string templateName1 = "E1";
			string templateName2 = "E2";
			string codeBlockTextTemplateHeader = progLangTemplateHeaderPart1[progLang] + progLangTemplateHeaderClassType[progLang] + templateName1 + progLangTemplateUseClassSeparator[progLang] + STRING_SPACE + progLangTemplateHeaderClassType[progLang] + templateName2 + progLangTemplateHeaderPart2[progLang];  //template <class E1, class E2>
			string codeBlockTextFunctionHeader = progLangClassMemberFunctionDefaultType[progLang] + NLC_USE_ADVANCED_REFERENCING_PLURAL_DEFINITE_REFERENCING_TESTS_FUNCTION_NAME + progLangOpenParameterSpace[progLang] + generateCodeEntityListDefinitionReferenceTypeText(templateName1, progLang) + generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangClassMemberFunctionParametersNext[progLang] + templateName2 + progLangPointer[progLang] + STRING_SPACE + param2->instanceName + progLangCloseParameterSpace[progLang];	//void addToCategoryIfPassSingularDefinitePluralityTests(vector<E1*> &param1CategoryList, E2* param2instanceName)

			string codeBlockText6 = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + negativeModifierString + progLangOpenParameterSpace[progLang] + param2->instanceName + progLangObjectReferenceDelimiter[progLang] + NLC_USE_ADVANCED_REFERENCING_LAST_SENTENCE_REFERENCED_VARIABLE_NAME + progLangObjectReferenceDelimiter2[progLang] + progLangHasEntity[progLang] + progLangCloseParameterSpace[progLang] + progLangCloseParameterSpace[progLang];		//if(!(param2->lastSentenceReferenced.empty())){

			string addCategoryItemText = generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangObjectReferenceDelimiter2[progLang] + progLangAddEntityToList[progLang] + progLangOpenParameterSpace[progLang] + param2->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//param1CategoryList.push_back(param2);
				//NB this code could be generated using existing codeblock (NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST)

			#ifdef NLC_USE_ADVANCED_REFERENCING_DO_NOT_ADD_DUPLICATES
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
					#ifdef NLC_USE_ADVANCED_REFERENCING_DO_NOT_ADD_DUPLICATES
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
		}		
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_UPDATE_LAST_SENTENCE_REFERENCED)	//execute for all new/undeclared/indefinite entities and accessed category items
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_UPDATE_LAST_SENTENCE_REFERENCED" << endl;
			#endif
			NLCitem * param2 = currentCodeBlockInLevel->parameters.at(1);
			string lastSentenceReferenced = param2->name;

			#ifdef NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT
			string codeBlockText = param1->instanceName + progLangObjectReferenceDelimiter[progLang] + NLC_USE_ADVANCED_REFERENCING_LAST_SENTENCE_REFERENCED_VARIABLE_NAME + progLangObjectReferenceDelimiter2[progLang] + progLangStackGetLast[progLang] + progLangEquals[progLang] + lastSentenceReferenced + progLangEndLine[progLang];		//param1->lastSentenceReferenced.top() = x;		
			#else
			string codeBlockText = param1->instanceName + progLangObjectReferenceDelimiter[progLang] + NLC_USE_ADVANCED_REFERENCING_LAST_SENTENCE_REFERENCED_VARIABLE_NAME + progLangEquals[progLang] + lastSentenceReferenced + progLangEndLine[progLang];		//param1->lastSentenceReferenced = x;
			#endif
			printLine(codeBlockText, level, code);
		}
		#endif
		#endif	
		#ifdef NLC_GENERATE_TYPE_LISTS
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_DECLARE_NEW_GENERIC_LIST_VARIABLE2)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_DECLARE_NEW_GENERIC_LIST_VARIABLE2" << endl;
			#endif
			NLCitem * param2 = currentCodeBlockInLevel->parameters.at(1);
			string genericListAppendName = param2->name;
	
			string localListDeclarationText = generateCodeEntityListDefinitionTypeText2(param1->className, progLang) + generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangEndLine[progLang];	//vector<vector<param1Class*>> param1instanceTypeList;
			printLine(localListDeclarationText, level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST2)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST2" << endl;
			#endif
			NLCitem * param2 = currentCodeBlockInLevel->parameters.at(1);
			NLCitem * param3 = currentCodeBlockInLevel->parameters.at(2);
			NLCitem * param4 = currentCodeBlockInLevel->parameters.at(3);
			string genericListAppendName = param3->name;
			string genericListAppendName2 = param4->name;

			string codeBlockText = generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangObjectReferenceDelimiter2[progLang] + progLangAddEntityToList[progLang] + progLangOpenParameterSpace[progLang] + generateGenericListName(param2->instanceName, genericListAppendName2) + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//param1instanceTypeList.push_back(param2);
			printLine(codeBlockText, level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_FOR_GENERIC_LIST2)
		{
			string iterIndexString = convertIntToString(level);
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_FOR_GENERIC_LIST2" << endl;
			#endif
			NLCitem * param2 = currentCodeBlockInLevel->parameters.at(1);
			string genericListAppendName = param2->name;
			
			string codeBlockText = progLangFor[progLang] + progLangForIterPart1[progLang] + generateCodeEntityListDefinitionTypeText2(param1->className, progLang) + progLangForIterPart2a[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart2c[progLang] + generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangForIterPart3a[progLang] + progLangForIterPart3b[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart3c[progLang] + generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangForIterPart4a[progLang] + progLangForIterPart4b[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart4c[progLang];
			printLine(codeBlockText, level, code);
			printLine(progLangOpenBlock[progLang], level, code);
			string tempVarDeclarationText = generateCodeEntityListDefinitionTypeText(param1->className, progLang) + generatePropertyListName(param1->className) + progLangEquals[progLang] + progLangPointer[progLang] + progLangForIterName[progLang] + iterIndexString + progLangEndLine[progLang];	//OLD:  param1->className + NLC_ITEM_TYPE_TEMP_VAR_APPENDITION
				//check use of generatePropertyListName(); should really be generateTempListName()
			printLine(tempVarDeclarationText, (level+1), code);
		}
		#endif
		#ifdef NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_IF_HAS_GREATER_THAN_OR_EQUAL_TO_NUM_GENERIC_ENTITY)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_IF_HAS_GREATER_THAN_OR_EQUAL_TO_NUM_GENERIC_ENTITY" << endl;
			#endif
			NLCitem * param2 = currentCodeBlockInLevel->parameters.at(1);
			string genericListAppendName = param2->name;

			NLCitem * param3 = currentCodeBlockInLevel->parameters.at(2);
			string valueString = param3->name;

			string codeBlockText = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangObjectReferenceDelimiter2[progLang] + progLangSizeOfList[progLang] + progLangGreaterThanOrEqualTo[progLang] + valueString + progLangCloseParameterSpace[progLang];		//if(param1CategoryList.size() > X){

			printLine(codeBlockText, level, code);
			printLine(progLangOpenBlock[progLang], level, code);
		}
		#ifdef NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY_CHILDREN
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_TEST_INT_VARIABLE_GREATER_THAN_OR_EQUAL_TO_NUM)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_TEST_INT_VARIABLE_GREATER_THAN_OR_EQUAL_TO_NUM" << endl;
			#endif

			NLCitem * param2 = currentCodeBlockInLevel->parameters.at(1);
			string valueString = param2->name;

			string codeBlockText = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + param1->name + progLangGreaterThanOrEqualTo[progLang] + valueString + progLangCloseParameterSpace[progLang];		//if(variable > x){

			printLine(codeBlockText, level, code);
			printLine(progLangOpenBlock[progLang], level, code);
		}
		#endif
		/*	
		#ifdef NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY_CHILDREN
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_IF_HAS_MORE_THAN_NUM_PROPERTY)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_IF_HAS_MORE_THAN_NUM_PROPERTY" << endl;
			#endif

			NLCitem * param2 = currentCodeBlockInLevel->parameters.at(1);
			string valueString = param2->name;

			string codeBlockText = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + contextParam1 + generatePropertyListName(param1->className) + progLangObjectReferenceDelimiter2[progLang] + progLangSizeOfList[progLang] + progLangGreaterThan[progLang] + valueString + progLangCloseParameterSpace[progLang];		//if(context1->param1PropertyList.size() > x){

			printLine(codeBlockText, level, code);
			printLine(progLangOpenBlock[progLang], level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_IF_HAS_MORE_THAN_NUM_CONDITION)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_IF_HAS_MORE_THAN_NUM_CONDITION" << endl;
			#endif

			NLCitem * param2 = currentCodeBlockInLevel->parameters.at(1);			
			NLCitem * param3 = currentCodeBlockInLevel->parameters.at(2);
			string valueString = param3->name;

			string codeBlockText = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + contextParam1 + generateConditionListName(param1->className, param2->className) + progLangObjectReferenceDelimiter2[progLang] + progLangSizeOfList[progLang] + progLangGreaterThan[progLang] + valueString + progLangCloseParameterSpace[progLang];		//if(context1->param1param2ConditionList.size() > x){

			printLine(codeBlockText, level, code);
			printLine(progLangOpenBlock[progLang], level, code);
		}
		#endif
		*/
		#endif
		#ifdef NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_DECLARE_CONTEXT_LIST)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_DECLARE_CONTEXT_LIST" << endl;
			#endif
			string contextLevelString = param1->name;
			
			string  genericEntityClassName = generateClassName(NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE);
			string contextListName = string(NLC_ITEM_TYPE_REFERENCECONTEXTLEVELLIST_VAR_APPENDITION) + contextLevelString;
			string contextListDeclarationText = generateCodeEntityListDefinitionTypeText(genericEntityClassName, progLang) + contextListName + progLangEndLine[progLang];	//vector<genericEntityClass*> contextListX;
			printLine(contextListDeclarationText, level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_CONTEXT_LIST_NEW_FUNCTION)
		{//finish coding this
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_CONTEXT_LIST_NEW_FUNCTION" << endl;
			#endif

			string genericEntityClassName = generateClassName(NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE);
			string contextListName = string(NLC_ITEM_TYPE_REFERENCECONTEXTLEVELLIST_VAR_APPENDITION);
			string entityToAddName = NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE;
			
			string codeBlockTextFunctionHeader = progLangClassMemberFunctionDefaultType[progLang] + NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT_ADD_ENTITY_TO_CONTEXT_LIST_FUNCTION_NAME + progLangOpenParameterSpace[progLang] + generateCodeEntityListDefinitionReferenceTypeText(genericEntityClassName, progLang) + contextListName + progLangClassMemberFunctionParametersNext[progLang] + generateEntityDeclaration(genericEntityClassName, entityToAddName, progLang) + progLangClassMemberFunctionParametersNext[progLang] + progLangClassLastSentenceIndexVariableType[progLang] + NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT_SENTENCE_INDEX_VARIABLE_NAME + progLangCloseParameterSpace[progLang];	//void addVariableToContextList(vector<genericEntityClass*> &contextList, genericEntityClass* genericEntity, int sentenceIndex)

			printLine("", level, code);
			printLine(codeBlockTextFunctionHeader, level, code);
			printLine(progLangOpenBlock[progLang], level, code);
				string pushLastSentenceReferencedText = contextListName + progLangObjectReferenceDelimiter2[progLang] + progLangAddEntityToList[progLang] + progLangOpenParameterSpace[progLang] + entityToAddName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//contextList.push_back(genericEntity);
				printLine(pushLastSentenceReferencedText, (level+1), code);
				string codeBlockUpdateLastSentenceReferencedText = entityToAddName + progLangObjectReferenceDelimiter[progLang] + NLC_USE_ADVANCED_REFERENCING_LAST_SENTENCE_REFERENCED_VARIABLE_NAME + progLangObjectReferenceDelimiter2[progLang] + progLangStackAdd[progLang] + progLangOpenParameterSpace[progLang] + NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT_SENTENCE_INDEX_VARIABLE_NAME + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//genericEntity->lastSentenceReferenced.push(sentenceIndex);		
				printLine(codeBlockUpdateLastSentenceReferencedText, (level+1), code);
			printLine(progLangCloseBlock[progLang], level, code);	
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_CONTEXT_LIST_EXECUTE_FUNCTION)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_CONTEXT_LIST_EXECUTE_FUNCTION" << endl;
			#endif
			
			NLCitem * param2 = currentCodeBlockInLevel->parameters.at(1);
			NLCitem * param3 = currentCodeBlockInLevel->parameters.at(2);
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
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_CLEAR_CONTEXT_LIST_NEW_FUNCTION)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_CLEAR_CONTEXT_LIST_NEW_FUNCTION" << endl;
			#endif
			
			string iterIndexString = convertIntToString(1);	//functions declared at level 1
			string genericEntityClassName = generateClassName(NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE);
			string contextListName = string(NLC_ITEM_TYPE_REFERENCECONTEXTLEVELLIST_VAR_APPENDITION);
			string tempVariableName = string(NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE);
				
			string codeBlockTextFunctionHeader = progLangClassMemberFunctionDefaultType[progLang] + NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT_CLEAR_CONTEXT_LIST_FUNCTION_NAME + progLangOpenParameterSpace[progLang] + generateCodeEntityListDefinitionReferenceTypeText(genericEntityClassName, progLang) + contextListName + progLangCloseParameterSpace[progLang];	//void clearContextList(vector<genericEntityClass*> &contextList)

			printLine("", level, code);
			printLine(codeBlockTextFunctionHeader, level, code);
			printLine(progLangOpenBlock[progLang], level, code);
				string codeBlockText = progLangFor[progLang] + progLangForIterPart1[progLang] + generateCodeEntityListDefinitionTypeText(genericEntityClassName, progLang) + progLangForIterPart2a[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart2c[progLang] + contextListName + progLangForIterPart3a[progLang] + progLangForIterPart3b[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart3c[progLang] + contextListName + progLangForIterPart4a[progLang] + progLangForIterPart4b[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart4c[progLang];	//for(vector<genericEntityClass*> ::iterator iterX = contextList.begin(); iterX < contextList.end(); iterX++)
				printLine(codeBlockText, (level+1), code);
					printLine(progLangOpenBlock[progLang], (level+1), code);	//{
					string tempVarDeclarationText = generateEntityDeclaration(genericEntityClassName, tempVariableName, progLang) + progLangEquals[progLang] + progLangPointer[progLang] + progLangForIterName[progLang] + iterIndexString + progLangEndLine[progLang];	//genericEntityClass* genericEntity = *iter2;
					printLine(tempVarDeclarationText, (level+2), code);
					string popLastSentenceReferencedText = tempVariableName + progLangObjectReferenceDelimiter[progLang] + NLC_USE_ADVANCED_REFERENCING_LAST_SENTENCE_REFERENCED_VARIABLE_NAME + progLangObjectReferenceDelimiter2[progLang] + progLangStackRemove[progLang] + progLangEndLine[progLang];	//genericEntity->lastSentenceReferenced.pop();
					printLine(popLastSentenceReferencedText, (level+2), code);
				printLine(progLangCloseBlock[progLang], (level+1), code);
				string clearContextListText = contextListName + progLangObjectReferenceDelimiter2[progLang] + progLangRemoveProperties[progLang] + progLangEndLine[progLang];		//contextList.clear();
				printLine(clearContextListText, (level+1), code);
			printLine(progLangCloseBlock[progLang], level, code);	
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_CLEAR_CONTEXT_LIST_EXECUTE_FUNCTION)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_CLEAR_CONTEXT_LIST_EXECUTE_FUNCTION" << endl;
			#endif
			
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
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_CONTEXT_BLOCK)
		{
			printLine(progLangOpenBlock[progLang], level, code);		
		}
		#endif
		#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS	
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_CAST_VECTOR_EXECUTE_FUNCTION)
		{//not used - see printCodeBlockCastVectorExecuteFunction()
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_CAST_VECTOR_EXECUTE_FUNCTION" << endl;
			#endif
			
			NLCitem * param2 = currentCodeBlockInLevel->parameters.at(1);	//functionArgumentPassCast

			string codeBlockTextTemplateDefinition = progLangTemplateUsePart1[progLang] + param1->className + progLangTemplateUseClassSeparator[progLang] + STRING_SPACE + param2->className + progLangTemplateUsePart2[progLang] + STRING_SPACE; 	//<param1class, param2class>
			string codeBlockExecuteFunctionText = string("") + NLC_CAST_VECTOR_FUNCTION_NAME + codeBlockTextTemplateDefinition + progLangOpenParameterSpace[progLang] + generateEntityListName(param1) + progLangCloseParameterSpace[progLang];	//castVector<param1class, param2class> (param1InstanceList)	
			//string codeBlockTextTemplateDefinition = progLangTemplateUsePart1[progLang] + param1->className + progLangTemplateUsePart2[progLang] + STRING_SPACE; 	//<param1class>
			//string codeBlockExecuteFunctionText = string("") + NLC_CAST_VECTOR_FUNCTION_NAME + codeBlockTextTemplateDefinition + progLangOpenParameterSpace[progLang] + generateEntityListName(param1) + progLangCloseParameterSpace[progLang];	//castVector<param1class> (param1InstanceList)			
			printLine(codeBlockExecuteFunctionText, level, code);

		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_CAST_VECTOR_NEW_FUNCTION)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_CAST_VECTOR_NEW_FUNCTION" << endl;
			#endif

			string iterIndexString = convertIntToString(1);	//functions declared at level 1
			string templateName1 = "E1";
			string templateName2 = "E2";
			string entity1InstanceListName = templateName1 + generateEntityListAppendName();
			string entity2InstanceListName = templateName2 + generateEntityListAppendName();
			string tempVariableName = string(NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE);

			string codeBlockTextTemplateHeader = progLangTemplateHeaderPart1[progLang] + progLangTemplateHeaderClassType[progLang] + templateName1 + progLangTemplateUseClassSeparator[progLang] + STRING_SPACE + progLangTemplateHeaderClassType[progLang] + templateName2 + progLangTemplateHeaderPart2[progLang];  //template <class E1, class E2>
			string codeBlockTextFunctionHeader = generateCodeEntityListDefinitionTypeText(templateName1, progLang) + NLC_CAST_VECTOR_FUNCTION_NAME + progLangOpenParameterSpace[progLang] + generateCodeEntityListDefinitionReferenceTypeText(templateName1, progLang) + entity1InstanceListName + progLangCloseParameterSpace[progLang];	//vector<E2*> castVector(vector<E1*> &E1InstanceList)

			printLine("", level, code);
			printLine(codeBlockTextTemplateHeader, level, code);
			printLine(codeBlockTextFunctionHeader, level, code);
			printLine(progLangOpenBlock[progLang], level, code);
				string codeBlockTextDeclareNewVector = generateCodeEntityListDefinitionTypeText(templateName2, progLang) + entity2InstanceListName + progLangEndLine[progLang];	//vector<E2*> E2InstanceList;
				printLine(codeBlockTextDeclareNewVector, (level+1), code);
				string codeBlockTextForLoop = progLangFor[progLang] + progLangForIterPart1[progLang] + progLangTypeName[progLang] + generateCodeEntityListDefinitionTypeText(templateName1, progLang) + progLangForIterPart2a[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart2c[progLang] + entity1InstanceListName + progLangForIterPart3a[progLang] + progLangForIterPart3b[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart3c[progLang] + entity1InstanceListName + progLangForIterPart4a[progLang] + progLangForIterPart4b[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart4c[progLang];	//for(typename vector<E1*> ::iterator iterX = E1InstanceList.begin(); iterX < E1InstanceList.end(); iterX++)
				printLine(codeBlockTextForLoop, (level+1), code);
				printLine(progLangOpenBlock[progLang], (level+1), code);	//{
					string tempVarDeclarationText = generateEntityDeclaration(templateName1, tempVariableName, progLang) + progLangEquals[progLang] + progLangPointer[progLang] + progLangForIterName[progLang] + iterIndexString + progLangEndLine[progLang];	//E1* genericEntity = *iter1;
					printLine(tempVarDeclarationText, (level+2), code);;
					string addCastedEntityToVectorText = entity2InstanceListName + progLangObjectReferenceDelimiter2[progLang] + progLangAddEntityToList[progLang] + progLangOpenParameterSpace[progLang] + generateDynamicCastOfEntity(tempVariableName, templateName2, progLang) + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//E2InstanceList.push_back(dynamic_cast<E2*>(genericEntity));
					printLine(addCastedEntityToVectorText, (level+2), code);
				printLine(progLangCloseBlock[progLang], (level+1), code);	//}
				string codeBlockTextReturnNewVector = progLangReturn[progLang] + entity2InstanceListName + progLangEndLine[progLang];		//return E2InstanceList;
				printLine(codeBlockTextReturnNewVector, (level+1), code);
			printLine(progLangCloseBlock[progLang], level, code);	//}

		}
		#endif
		#ifdef NLC_USE_ADVANCED_REFERENCING_SUPPORT_ALIASES
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_ADD_ALIAS_TO_ENTITY_ALIAS_LIST)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_ADD_ALIAS_TO_ENTITY_ALIAS_LIST" << endl;
			#endif
			NLCitem * param2 = currentCodeBlockInLevel->parameters.at(1);
			string aliasName = param2->name;

			string codeBlockTextAddAliasToEntityAliasList = param1->instanceName + progLangObjectReferenceDelimiter[progLang] + NLC_ITEM_TYPE_ALIASLIST_VAR_APPENDITION + progLangObjectReferenceDelimiter2[progLang] + progLangAddProperty[progLang] + progLangOpenParameterSpace[progLang] + aliasName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//entity->aliasList.push_back(aliasName);			
			printLine(codeBlockTextAddAliasToEntityAliasList, level, code);
			
			
			/*
			string codeBlockTextAddEntityToAliasList = generateEntityStringPairListName(NLC_USE_ADVANCED_REFERENCING_SUPPORT_ALIASES_ALIAS_LIST_NAME_START, NLC_ITEM_TYPE_ALIASLIST_VAR_APPENDITION) + progLangObjectReferenceDelimiter2[progLang] + progLangAddCondition[progLang] + progLangOpenParameterSpace[progLang] + generateEntityStringPairTexts(param1->name, genericEntityClassName, generateDynamicCastOfEntity(param2->instanceName, genericEntityClassName, progLang), progLang) + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//AliasList.insert(pair<string, param2className*>(param1, dynamic_cast<genericEntity*>param2));
			*/
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_FIND_ALIAS_AND_ADD_TO_CATEGORY_LIST_NEW_FUNCTION)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_FIND_ALIAS_AND_ADD_TO_CATEGORY_LIST_NEW_FUNCTION" << endl;
			#endif

			string iterIndexString = convertIntToString(1);	//functions declared at level 1

			string genericEntityClassName = generateClassName(NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE);
			string aliasListName = NLC_ITEM_TYPE_ALIASLIST_VAR_APPENDITION;
			string aliasName = NLC_USE_ADVANCED_REFERENCING_SUPPORT_ALIASES_ALIAS_NAME;

			string templateName1 = "E1";
			string entity1InstanceListName = templateName1 + generateEntityListAppendName();
			string entity1CategoryListName = templateName1 + NLC_ITEM_TYPE_CATEGORYLIST_VAR_APPENDITION;
			string tempVariableName = string(NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE);	//NLCgenericEntity
			string tempVariableAliasListName = tempVariableName + progLangObjectReferenceDelimiter[progLang] + NLC_ITEM_TYPE_ALIASLIST_VAR_APPENDITION;

			string codeBlockTextTemplateHeader = progLangTemplateHeaderPart1[progLang] + progLangTemplateHeaderClassType[progLang] + templateName1 + progLangTemplateHeaderPart2[progLang];  //template <class E1>

			string codeBlockTextFunctionHeader = progLangClassMemberFunctionDefaultType[progLang] + NLC_USE_ADVANCED_REFERENCING_FIND_ALIAS_AND_ADD_TO_CATEGORY_LIST_FUNCTION_NAME + progLangOpenParameterSpace[progLang] + generateCodeEntityListDefinitionReferenceTypeText(templateName1, progLang) + entity1InstanceListName + progLangClassMemberFunctionParametersNext[progLang] + progLangAliasNameVariableType[progLang] + aliasName + progLangClassMemberFunctionParametersNext[progLang] + generateCodeEntityListDefinitionReferenceTypeText(templateName1, progLang) + entity1CategoryListName + progLangCloseParameterSpace[progLang];	//void findAliasAndAddToCategoryListNewFunction(vector<E1*> &E1instanceList, string aliasName, vector<E1*> &E1CategoryList)

			int q = 0;
			printLine("", level+q, code);
			printLine(codeBlockTextTemplateHeader, level+q, code);
			printLine(codeBlockTextFunctionHeader, level+q, code);
			printLine(progLangOpenBlock[progLang], level+q, code);
				
				q++;
				string codeBlockTextForLoop = progLangFor[progLang] + progLangForIterPart1[progLang] + progLangTypeName[progLang] + generateCodeEntityListDefinitionTypeText(templateName1, progLang) + progLangForIterPart2a[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart2c[progLang] + entity1InstanceListName + progLangForIterPart3a[progLang] + progLangForIterPart3b[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart3c[progLang] + entity1InstanceListName + progLangForIterPart4a[progLang] + progLangForIterPart4b[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart4c[progLang];	//for(typename vector<E1*> ::iterator iterX = E1InstanceList.begin(); iterX < E1InstanceList.end(); iterX++)
				printLine(codeBlockTextForLoop, level+q, code);
				printLine(progLangOpenBlock[progLang], level+q, code);	//{
					q++;
					string tempVarDeclarationText = generateEntityDeclaration(templateName1, tempVariableName, progLang) + progLangEquals[progLang] + progLangPointer[progLang] + progLangForIterName[progLang] + iterIndexString + progLangEndLine[progLang];	//E1* genericEntity = *iter1;
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

			/*
			//NEW (optimised):
			string codeBlockTextFindAliasEntity = progLangFor[progLang] + progLangForIterPart1[progLang] + generateCodeEntityStringPairListDefinitionTypeText(genericEntityClassName, progLang) + progLangForIterPart2a[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart2c[progLang] + aliasListName + progLangObjectReferenceDelimiter[progLang] + progLangOpenParameterSpace[progLang] + aliasName progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];  	//unordered_map<string, genericEntityClassName*>::iterator iter1 = AliasList->find(aliasName);
			printLine(codeBlockTextFindAliasEntity, level+1, code);
			string codeBlockTextTestFindAliasEntity = progLangTestEntityPairFindPart1[progLang] + progLangForIterName[progLang] + iterIndexString + progLangTestEntityPairFindPart2[progLang] + aliasListName + progLangTestEntityPairFindPart3[progLang] //if(iter1 != aliasListName->end())
			printLine(codeBlockTextTestFindAliasEntity, level+1, code);
			printLine(progLangOpenBlock[progLang], level+1, code);	//{
				string tempVarDeclarationText = generateEntityDeclaration(genericEntityClassName, tempVariableName, progLang) + progLangEquals[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterEntityPairListEntityReference[progLang] + progLangEndLine[progLang];	//genericEntityClass* genericEntity = iter1->second;
				printLine(tempVarDeclarationText, (level+2), code);
			//OLD (unoptimised):
			//string codeBlockText = progLangFor[progLang] + progLangForIterPart1[progLang] + generateCodeEntityStringPairListDefinitionText(genericEntityClassName, progLang) + progLangForIterPart2a[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart2c[progLang] + generateEntityStringPairListName(genericEntityClassName) + progLangForIterPart3a[progLang] + progLangForIterPart3b[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart3cMap[progLang] + generateEntityStringPairListName(genericEntityClassName) + progLangForIterPart4a[progLang] + progLangForIterPart4b[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart4c[progLang];
			//printLine(codeBlockText, level+1, code);
			//printLine(progLangOpenBlock[progLang], level+1, code);
			//string tempVarDeclarationText = generateEntityDeclaration(param2, progLang) + progLangEquals[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterEntityPairListEntityReference[progLang] + progLangEndLine[progLang];
			//printLine(tempVarDeclarationText, (level+2), code);	
				//printLine(progLangOpenBlock[progLang], (level+1), code);	//{
				//UNFINISHED; string codeBlockTextIfEntityNameEqualsAliasName = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + contextParam1 + generateConditionListName(param1->className, param2->className) + progLangObjectReferenceDelimiter2[progLang] + progLangSizeOfList[progLang] + progLangGreaterThan[progLang] + valueString + progLangCloseParameterSpace[progLang];		//if(genericEntity->entityName == aliasName)

				string addCastedEntityToVectorText = entity1CategoryListName + progLangObjectReferenceDelimiter2[progLang] + progLangAddEntityToList[progLang] + progLangOpenParameterSpace[progLang] + generateDynamicCastOfEntity(tempVariableName, templateName1, progLang) + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//E1CategoryList.push_back(dynamic_cast<E1*>(genericEntity));
				printLine(addCastedEntityToVectorText, (level+2), code);

			printLine(progLangCloseBlock[progLang], (level+1), code);	//}
			*/
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_FIND_ALIAS_AND_ADD_TO_CATEGORY_LIST_EXECUTE_FUNCTION)
		{//not used - see printCodeBlockCastVectorExecuteFunction()
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_FIND_ALIAS_AND_ADD_TO_CATEGORY_LIST_EXECUTE_FUNCTION" << endl;
			#endif
			
			NLCitem * param2 = currentCodeBlockInLevel->parameters.at(1);
			NLCitem * param3 = currentCodeBlockInLevel->parameters.at(2);
			string genericListAppendName = param3->name;

			string codeBlockTextTemplateDefinition = progLangTemplateUsePart1[progLang] + param2->className + progLangTemplateUsePart2[progLang] + STRING_SPACE; 	//<param2class>
			string codeBlockExecuteFunctionText = string("") + NLC_USE_ADVANCED_REFERENCING_FIND_ALIAS_AND_ADD_TO_CATEGORY_LIST_FUNCTION_NAME + codeBlockTextTemplateDefinition + progLangOpenParameterSpace[progLang] + generateEntityListName(param2) + progLangClassMemberFunctionParametersNext[progLang] + param1->name + progLangClassMemberFunctionParametersNext[progLang] + generateGenericListName(param2->instanceName, genericListAppendName) + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//findAliasAndAddToCategoryList<param2class> (param2InstanceList, param1aliasName, param3CategoryList);
			printLine(codeBlockExecuteFunctionText, level, code);

		}
		#endif
		
		/*
		else if(currentCodeBlockInLevel->codeBlockType == ...)
		{

		}
		...
		*/
		else
		{
			cout << "printCodeBlocks: error: currentCodeBlockInLevel->codeBlockType = " << currentCodeBlockInLevel->codeBlockType << endl;
		}

		if(currentCodeBlockInLevel->lowerLevel != NULL)
		{
			printCodeBlocks(currentCodeBlockInLevel->lowerLevel, classDefinitionList, progLang, code, (level+1));
			#ifdef NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT
			if(currentCodeBlockInLevel->isLogicalCondition)
			{
				//createCodeBlocksClearContextListVariableExecuteFunction:
				#ifdef NLC_DEBUG
				cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_CLEAR_CONTEXT_LIST_EXECUTE_FUNCTION" << endl;
				#endif

				string genericEntityClassName = generateClassName(NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE);
				#ifdef NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT_PRINT_LEVEL_USED_INSTEAD_OF_CONTEXT_LEVEL
				string contextLevelString = convertIntToString(level + 1);
				#else
				string contextLevelString = convertIntToString(currentCodeBlockInLevel->contextLevel);
				#endif
				string contextListName = string(NLC_ITEM_TYPE_REFERENCECONTEXTLEVELLIST_VAR_APPENDITION) + contextLevelString;
				//cout << "contextLevelString = " << contextLevelString << endl;

				string codeBlockExecuteFunctionText = "";
				codeBlockExecuteFunctionText = codeBlockExecuteFunctionText + NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT_CLEAR_CONTEXT_LIST_FUNCTION_NAME +  progLangOpenParameterSpace[progLang] + contextListName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//clearContextLevelList(contextListX);
				printLine(codeBlockExecuteFunctionText, level+1, code);
			}
			#endif
			printLine(progLangCloseBlock[progLang], level, code);
		}

		currentCodeBlockInLevel = currentCodeBlockInLevel->next;
	}
	return true;
}



void generateFunctionExecutionArgumentsWithActionConceptInheritanceString(vector<NLCclassDefinition *> * classDefinitionList, vector<NLCitem*> * codeBlockParameters, string * functionArguments, int progLang)
{
	vector<NLCitem*> * parameters;
	#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS
	#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
	parameters = codeBlockParameters;

	string functionName = "";
	NLCitem * functionArgument = NULL;
	if(findFunctionArgument(codeBlockParameters, NLC_ITEM_TYPE_FUNCTION_EXECUTION_ARGUMENT_FUNCTION, &functionArgument))
	{
		functionName = functionArgument->name;
	}
	else
	{
		cout << "generateFunctionExecutionArgumentsWithActionConceptInheritanceString(): NLC_ITEM_TYPE_FUNCTION_EXECUTION_ARGUMENT_FUNCTION not found" << endl;
		exit(0);
	}
	
	string functionOwnerName = "";
	NLCitem * functionOwnerArgument = NULL;
	bool hasFunctionOwnerClass = false;
	if(findFunctionArgument(codeBlockParameters, NLC_ITEM_TYPE_FUNCTION_EXECUTION_ARGUMENT_FUNCTION_OWNER, &functionOwnerArgument))
	{
		hasFunctionOwnerClass = true;
		functionOwnerName = functionOwnerArgument->name;
	}
	
	string functionObjectName = "";
	NLCitem * functionObjectArgument = NULL;
	bool hasFunctionObjectClass = false;
	if(findFunctionArgument(codeBlockParameters, NLC_ITEM_TYPE_FUNCTION_EXECUTION_ARGUMENT_FUNCTION_OBJECT, &functionObjectArgument))
	{
		hasFunctionObjectClass = true;
		functionObjectName = functionObjectArgument->name;		
	}
	
	bool foundFunctionOwnerExactMatch = false;
	bool foundFunctionObjectExactMatch = false;
	#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
	cout << "\n\n\n\n generateFunctionExecutionArgumentsWithActionConceptInheritanceString():" << endl;
	cout << "functionName = " << functionName << endl;
	cout << "functionOwnerName = " << functionOwnerName << endl;
	cout << "functionObjectName = " << functionObjectName << endl;
	#endif
	NLCclassDefinition * functionDeclaration = NULL;	//NB "functionDeclaration" should be "functionDeclaration"
	if(findFunctionDeclarationClassDefinitionExactOrNonExactMatch(classDefinitionList, functionName, functionOwnerName, functionObjectName, hasFunctionOwnerClass, hasFunctionObjectClass, &functionDeclaration, false, &foundFunctionOwnerExactMatch, &foundFunctionObjectExactMatch))
	{
		#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
		cout << "findFunctionDeclarationClassDefinition" << endl;
		#endif
		
		#ifdef NLC_FUNCTIONS_SUPPORT_PLURAL_SUBJECTS
		if(hasFunctionOwnerClass && !foundFunctionOwnerExactMatch)
		{
			#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
			cout << "(hasFunctionOwnerClass && !foundFunctionOwnerExactMatch)" << endl;
			#endif
			NLCitem * functionOwnerArgumentDeclaration = NULL;
			if(findFunctionArgument(&(functionDeclaration->parameters), NLC_ITEM_TYPE_FUNCTION_DECLARATION_ARGUMENT_FUNCTION_OWNER, &functionOwnerArgumentDeclaration))
			{
				functionOwnerArgument->functionArgumentPassCastRequired = true;
				functionOwnerArgument->functionArgumentPassCastClassName = generateClassName(functionOwnerArgumentDeclaration->name);
			}
			else
			{
				cout << "generateFunctionExecutionArgumentsWithActionConceptInheritanceString() error: !findFunctionArgument: NLC_ITEM_TYPE_FUNCTION_DECLARATION_ARGUMENT_FUNCTION_OBJECT - functionName = " << functionName << endl;
			}
		}	
		#endif
		if(hasFunctionObjectClass && !foundFunctionObjectExactMatch)
		{
			#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
			cout << "(hasFunctionObjectClass && !foundFunctionObjectExactMatch)" << endl;
			#endif
			NLCitem * functionObjectArgumentDeclaration = NULL;
			if(findFunctionArgument(&(functionDeclaration->parameters), NLC_ITEM_TYPE_FUNCTION_DECLARATION_ARGUMENT_FUNCTION_OBJECT, &functionObjectArgumentDeclaration))
			{
				functionObjectArgument->functionArgumentPassCastRequired = true;
				functionObjectArgument->functionArgumentPassCastClassName = generateClassName(functionObjectArgumentDeclaration->name);
			}
			else
			{
				cout << "generateFunctionExecutionArgumentsWithActionConceptInheritanceString() error: !findFunctionArgument: NLC_ITEM_TYPE_FUNCTION_DECLARATION_ARGUMENT_FUNCTION_OBJECT - functionName = " << functionName << endl;
			}
		}
		
		#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_BASED_ON_IMPLICITLY_DECLARED_VARIABLES_IN_CURRENT_FUNCTION_DEFINITION
		for(vector<NLCitem*>::iterator parametersIterator = functionDeclaration->parameters.begin(); parametersIterator < functionDeclaration->parameters.end(); parametersIterator++)
		{
			NLCitem * currentItem = *parametersIterator;
			//cout << "1 currentItem->itemType = " << currentItem->itemType << endl;
			if(currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_DECLARATION_ARGUMENT_INSTANCE_OR_CLASS_LIST)
			{
				NLCitem * newFunctionArgument = new NLCitem(currentItem);
				newFunctionArgument->itemType = NLC_ITEM_TYPE_FUNCTION_EXECUTION_ARGUMENT_INSTANCE_OR_CLASS_LIST;
				parameters->push_back(newFunctionArgument);
			}
		}
		#endif
	}
	#endif
	#else
	parameters = codeBlockParameters;
	#endif

	for(vector<NLCitem*>::iterator parametersIterator = parameters->begin(); parametersIterator < parameters->end(); parametersIterator++)
	{
		NLCitem * currentItem = *parametersIterator;

		//cout << "2 currentItem->itemType = " << currentItem->itemType << endl;
		if(currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_EXECUTION_ARGUMENT_INSTANCE_OR_CLASS_LIST)
		{
			//cout << "3 currentItem->name = " << currentItem->name << endl;
			if(*functionArguments != "")
			{
				*functionArguments = *functionArguments + progLangClassMemberFunctionParametersNext[progLang];
			}
			
			bool categoryList = false;
			*functionArguments = *functionArguments + generateCodePluralReferenceText(currentItem, progLang, categoryList);
			//*functionArguments = *functionArguments + generateCodeSingularReferenceText(currentItem, progLang);	//OLD
		}
		#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS
		#ifdef NLC_FUNCTIONS_SUPPORT_PLURAL_SUBJECTS
		else if(currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_EXECUTION_ARGUMENT_FUNCTION_OWNER)
		{
			if(*functionArguments != "")
			{
				*functionArguments = *functionArguments + progLangClassMemberFunctionParametersNext[progLang];
			}
			
			#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS_PASS_AS_LISTS
			bool categoryList = false;
			#ifndef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES
			#ifdef NLC_FUNCTIONS_SUPPORT_PLURAL_SUBJECTS
			categoryList = true;
			#endif
			#endif
			*functionArguments = *functionArguments + generateCodePluralReferenceText(currentItem, progLang, categoryList);
			#else
			*functionArguments = *functionArguments + generateCodeSingularReferenceText(currentItem, progLang);
			#endif
		}
		#endif
		else if(currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_EXECUTION_ARGUMENT_FUNCTION)
		{
			if(*functionArguments != "")
			{
				*functionArguments = *functionArguments + progLangClassMemberFunctionParametersNext[progLang];
			}
			#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS_PASS_AS_LISTS
			bool categoryList = false;
			*functionArguments = *functionArguments + generateCodePluralReferenceText(currentItem, progLang, categoryList);
			#else
			*functionArguments = *functionArguments + generateCodeSingularReferenceText(currentItem, progLang);
			#endif
		}
		else if(currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_EXECUTION_ARGUMENT_FUNCTION_OBJECT)
		{
			if(*functionArguments != "")
			{
				*functionArguments = *functionArguments + progLangClassMemberFunctionParametersNext[progLang];
			}
			
			#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS_PASS_AS_LISTS
			bool categoryList = false;
			#ifndef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES
			#ifdef NLC_FUNCTIONS_SUPPORT_PLURAL_OBJECTS
			categoryList = true;
			#endif
			#endif
			*functionArguments = *functionArguments + generateCodePluralReferenceText(currentItem, progLang, categoryList);
			#else
			*functionArguments = *functionArguments + generateCodeSingularReferenceText(currentItem, progLang);
			#endif
		}
		#endif
		/*
		#ifdef NLC_INTERPRET_ACTION_PROPERTIES_AND_CONDITIONS_AS_FUNCTION_ARGUMENTS
		else if(currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_EXECUTION_ARGUMENT_CONDITION)
		{
			if(*functionArguments != "")
			{
				*functionArguments = *functionArguments + progLangClassMemberFunctionParametersNext[progLang];
			}
			*functionArguments = *functionArguments + generateCodeConditionPairReferenceText(currentItem, progLang);
		}
		else if(currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_EXECUTION_ARGUMENT_PROPERTY)
		{
			if(*functionArguments != "")
			{
				*functionArguments = *functionArguments + progLangClassMemberFunctionParametersNext[progLang];
			}
			*functionArguments = *functionArguments + generateCodeSingularReferenceText(currentItem, progLang);
		}
		#endif
		*/
	}
}


string generateCodePluralReferenceText(NLCitem * functionArgumentItem, int progLang, bool categoryList)
{
	string codePropertyTypeText = "";
	#ifndef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES
	#ifdef NLC_FUNCTIONS_SUPPORT_PLURAL_SUBJECTS_AND_OBJECTS
	if(categoryList)
	{
		codePropertyTypeText = generateGenericListName(functionArgumentItem->instanceName, NLC_ITEM_TYPE_ACTIONCATEGORY_VAR_APPENDITION);
	}
	else
	{
	#endif
	#endif
		codePropertyTypeText = generateEntityListName(functionArgumentItem);
	#ifndef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES
	#ifdef NLC_FUNCTIONS_SUPPORT_PLURAL_SUBJECTS_AND_OBJECTS
	}
	#endif
	#endif
	
	#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_ENABLE_TYPE_CASTING
	#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
	if(functionArgumentItem->functionArgumentPassCastRequired)
	{	
		#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
		cout << "generateCodePluralReferenceText(): functionArgumentItem->functionArgumentPassCastRequired" << endl;
		#endif
		codePropertyTypeText = printCodeBlockCastVectorExecuteFunction(functionArgumentItem, progLang, categoryList);
	}
	#endif
	#endif

	return codePropertyTypeText;
}

string generateCodeSingularReferenceText(NLCitem * functionArgumentItem, int progLang)
{
	string codePropertyTypeText = functionArgumentItem->instanceName;
	#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_ENABLE_TYPE_CASTING
	#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
	if(functionArgumentItem->functionArgumentPassCastRequired)
	{
		#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
		cout << "generateCodeSingularReferenceText(): functionArgumentItem->functionArgumentPassCastRequired" << endl;
		#endif
		codePropertyTypeText = generateDynamicCastOfEntity(functionArgumentItem->instanceName, functionArgumentItem->functionArgumentPassCastClassName, false); 	//dynamic_cast<parentClass*>(childClassInstance);
	}
	#endif
	#endif
	return codePropertyTypeText;
}

#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS
string printCodeBlockCastVectorExecuteFunction(NLCitem * functionArgumentItem, int progLang, bool categoryList)
{
	//see NLC_CODEBLOCK_TYPE_CAST_VECTOR_EXECUTE_FUNCTION
	
	string codeBlockTextTemplateDefinition = progLangTemplateUsePart1[progLang] + functionArgumentItem->className + progLangTemplateUseClassSeparator[progLang] + STRING_SPACE + functionArgumentItem->functionArgumentPassCastClassName + progLangTemplateUsePart2[progLang] + STRING_SPACE; 	//<param1class, param2class>
	string codeBlockExecuteFunctionText = "";
	#ifndef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES
	#ifdef NLC_FUNCTIONS_SUPPORT_PLURAL_SUBJECTS_AND_OBJECTS
	if(categoryList)
	{
		codeBlockExecuteFunctionText = string(NLC_CAST_VECTOR_FUNCTION_NAME) + codeBlockTextTemplateDefinition + progLangOpenParameterSpace[progLang] + generateGenericListName(functionArgumentItem->instanceName, NLC_ITEM_TYPE_ACTIONCATEGORY_VAR_APPENDITION) + progLangCloseParameterSpace[progLang];	//castVector<param1class, param2class> (param1CategoryList)				
	}
	else
	{
	#endif
	#endif
		codeBlockExecuteFunctionText = string(NLC_CAST_VECTOR_FUNCTION_NAME) + codeBlockTextTemplateDefinition + progLangOpenParameterSpace[progLang] + generateEntityListName(functionArgumentItem) + progLangCloseParameterSpace[progLang];	//castVector<param1class, param2class> (param1InstanceList)				
		//string codeBlockTextTemplateDefinition = progLangTemplateUsePart1[progLang] + functionArgumentItem->className + progLangTemplateUsePart2[progLang] + STRING_SPACE; 	//<param1class>
		//string codeBlockExecuteFunctionText = string(NLC_CAST_VECTOR_FUNCTION_NAME) + codeBlockTextTemplateDefinition + progLangOpenParameterSpace[progLang] + generateEntityListName(functionArgumentItem) + progLangCloseParameterSpace[progLang];	//castVector<param1class> (param1InstanceList)
	#ifndef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES
	#ifdef NLC_FUNCTIONS_SUPPORT_PLURAL_SUBJECTS_AND_OBJECTS	
	}
	#endif
	#endif
	
	return codeBlockExecuteFunctionText;
}
#endif
		
#ifdef NLC_INTERPRET_ACTION_PROPERTIES_AND_CONDITIONS_AS_FUNCTION_ARGUMENTS
string generateCodeConditionPairReferenceText(NLCitem * functionArgumentConditionItem, int progLang)
{
	//do: add dynamic_cast<functionArgumentPassCastClassName> if functionArgumentPassCastClassName != ""
	string codeConditionPairTypeText = generateCodeConditionPairTextWithContext(functionArgumentConditionItem->name, functionArgumentConditionItem->className, functionArgumentConditionItem->instanceName, functionArgumentConditionItem->className2, functionArgumentConditionItem->instanceName2, &(functionArgumentConditionItem->context), progLang);
	return codeConditionPairTypeText;
}
#endif


#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS
void generateLocalFunctionArgumentsBasedOnImplicitDeclarationsString(vector<NLCitem*> * parameters, string * functionArguments, int progLang)
{
	for(vector<NLCitem*>::iterator parametersIterator = parameters->begin(); parametersIterator < parameters->end(); parametersIterator++)
	{
		NLCitem * currentItem = *parametersIterator;
		if(currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_INSTANCE_OR_CLASS_LIST)
		{
			if(*functionArguments != "")
			{
				*functionArguments = *functionArguments + progLangClassMemberFunctionParametersNext[progLang];
			}
			*functionArguments = *functionArguments + generateCodeEntityListDefinitionReferenceText(currentItem, progLang);
		}
	}
}
#endif

#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS
void generateFunctionArgumentsBasedOnActionAndActionObjectVars(vector<NLCitem*> * parameters, string * functionArguments, int progLang)
{
	for(vector<NLCitem*>::iterator parametersIterator = parameters->begin(); parametersIterator < parameters->end(); parametersIterator++)
	{
		NLCitem * currentItem = *parametersIterator;
		#ifdef NLC_DEBUG
		//cout << "generateFunctionArgumentsBasedOnActionAndActionObjectVars():" << endl;
		//cout << "\tcurrentItem->itemType = " << currentItem->itemType << endl;
		//cout << "currentItem->instanceName = " << currentItem->instanceName << endl;
		#endif
		#ifdef NLC_FUNCTIONS_SUPPORT_PLURAL_SUBJECTS
		if(currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION_OWNER)
		{
			#ifdef NLC_DEBUG
			//cout << "NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION_OWNER" << endl;
			#endif
			if(*functionArguments != "")
			{
				*functionArguments = *functionArguments + progLangClassMemberFunctionParametersNext[progLang];
			}
			#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS_PASS_AS_LISTS
			*functionArguments = *functionArguments + generateCodeEntityListDefinitionReferenceText(currentItem, progLang);
			#else
			*functionArguments = *functionArguments + generateEntityDeclaration(currentItem, progLang);
			#endif
		}
		else 
		#endif
		if(currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION)
		{
			#ifdef NLC_DEBUG
			//cout << "NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION" << endl;
			#endif
			if(*functionArguments != "")
			{
				*functionArguments = *functionArguments + progLangClassMemberFunctionParametersNext[progLang];
			}
			#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS_PASS_AS_LISTS
			*functionArguments = *functionArguments + generateCodeEntityListDefinitionReferenceText(currentItem, progLang);
			#else
			*functionArguments = *functionArguments + generateEntityDeclaration(currentItem, progLang);
			#endif
		}
		else if(currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION_OBJECT)
		{
			#ifdef NLC_DEBUG
			//cout << "NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION_OBJECT" << endl;
			#endif
			if(*functionArguments != "")
			{
				*functionArguments = *functionArguments + progLangClassMemberFunctionParametersNext[progLang];
			}
			#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS_PASS_AS_LISTS
			*functionArguments = *functionArguments + generateCodeEntityListDefinitionReferenceText(currentItem, progLang);
			#else
			*functionArguments = *functionArguments + generateEntityDeclaration(currentItem, progLang);
			#endif			
		}

	}
}
#endif





string generateFunctionOwnerContext(vector<NLCitem*> * parameters, int progLang)
{
	bool foundFunctionOwner = false;
	string functionOwnerContext = "";
	#ifdef NLC_SUPPORT_INPUT_FILE_LISTS
	for(vector<NLCitem*>::iterator parametersIterator = parameters->begin(); parametersIterator < parameters->end(); parametersIterator++)
	{
		NLCitem * currentItem = *parametersIterator;
		if(currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION_OWNER)
		{
			functionOwnerContext = progLangClassMemberFunctionDefaultType[progLang] + currentItem->className + progLangFunctionOwnerClassDelimiter[progLang];
			foundFunctionOwner = true;
		}
	}
	#endif
	if(!foundFunctionOwner)
	{
		functionOwnerContext = progLangClassMemberFunctionDefaultType[progLang];
	}
	return functionOwnerContext;
}

#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS_ADVANCED
string generateLogicalConjunctionOfBoolsText(vector<NLCitem*> * parameters, int progLang)
{
	string logicalConjunctionOfBoolsText = "";
	for(vector<NLCitem*>::iterator parametersIterator = parameters->begin(); parametersIterator < parameters->end(); parametersIterator++)
	{
		NLCitem * currentItem = *parametersIterator;
		if(currentItem->conjunctionType == ENTITY_COORDINATINGCONJUNCTION_ARRAY_INDEX_AND)
		{
			logicalConjunctionOfBoolsText = logicalConjunctionOfBoolsText + STRING_SPACE + progLangAnd[progLang] + STRING_SPACE;
		}
		else if(currentItem->conjunctionType == ENTITY_COORDINATINGCONJUNCTION_ARRAY_INDEX_OR)
		{
			logicalConjunctionOfBoolsText = logicalConjunctionOfBoolsText + STRING_SPACE + progLangOr[progLang] + STRING_SPACE;
		}

		if(currentItem->negative)
		{
			logicalConjunctionOfBoolsText = logicalConjunctionOfBoolsText + progLangNot[progLang];
		}

		logicalConjunctionOfBoolsText = logicalConjunctionOfBoolsText + currentItem->name;	//should create a new currentItem variable called variableName for non-objects
	}
	return logicalConjunctionOfBoolsText;
}
#endif

