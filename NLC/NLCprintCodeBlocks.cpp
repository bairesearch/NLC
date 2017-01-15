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
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2015 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 1p2b 12-June-2015
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/


#include "NLCprintCodeBlocks.h"
#include "NLCprintCodeBlocksFunctions.h"
#include "NLCprintDefs.h"
#include "GIAtranslatorDefs.h"	//required for ENTITY_COORDINATINGCONJUNCTION_ARRAY_INDEX_AND/ENTITY_COORDINATINGCONJUNCTION_ARRAY_INDEX_OR

bool printCodeBlocks(NLCcodeblock* firstCodeBlockInLevel, vector<NLCclassDefinition*>* classDefinitionList, int progLang, string* code, int level)
{
	NLCcodeblock* currentCodeBlockInLevel = firstCodeBlockInLevel;
	while(currentCodeBlockInLevel->next != NULL)
	{
		NLCitem* param1 = currentCodeBlockInLevel->parameters.at(0);
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
			NLCitem* functionOwnerArgument = NULL;
			
			#ifndef NLC_NONOO_DISABLE_CLASS_HEIRACHY
			string functionOwnerNameWithReferenceDelimiter = "";
			if(findFunctionArgument(&(currentCodeBlockInLevel->parameters), NLC_ITEM_TYPE_FUNCTION_EXECUTION_ARGUMENT_FUNCTION_OWNER, &functionOwnerArgument))
			{
				#ifdef NLC_FUNCTIONS_SUPPORT_PLURAL_SUBJECTS
				functionOwnerNameWithReferenceDelimiter = generateNewObject(functionOwnerArgument->name, progLang) + progLangObjectReferenceDelimiter[progLang];
				#else
				functionOwnerNameWithReferenceDelimiter = functionOwnerArgument->instanceName + progLangObjectReferenceDelimiter[progLang];
				#endif
				hasActionSubject = true;
			}
			#endif
			
			NLCitem* functionArgument = NULL;
			string functionName = "";
			if(findFunctionArgument(&(currentCodeBlockInLevel->parameters), NLC_ITEM_TYPE_FUNCTION_EXECUTION_ARGUMENT_FUNCTION, &functionArgument))
			{
				functionName = functionArgument->functionName;
			}
			
			string functionArguments = "";
			//#ifdef NLC_NONOO_DISABLE_CLASS_HEIRACHY
			string functionDeclarationOwnerName = "";
			string functionDeclarationObjectName = "";
			//#endif
			generateFunctionExecutionArgumentsWithActionConceptInheritanceString(classDefinitionList, &(currentCodeBlockInLevel->parameters), &functionArguments, progLang, &functionDeclarationOwnerName, &functionDeclarationObjectName);
			
			#ifdef NLC_NONOO_DISABLE_CLASS_HEIRACHY
			string codeBlockText = functionDeclarationOwnerName + functionArgument->name + functionDeclarationObjectName + NLC_FUNCTION_NAME_APPEND + progLangOpenParameterSpace[progLang] + functionArguments + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//context1.param1(context.param2); 	[param1 = function, context1 = subject, param2 = object]			
			#else
			string codeBlockText = functionOwnerNameWithReferenceDelimiter + functionName + progLangOpenParameterSpace[progLang] + functionArguments + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//context1.param1(context.param2); 	[param1 = function, context1 = subject, param2 = object]			
			#endif
			printLine(codeBlockText, level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_NEW_FUNCTION)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_NEW_FUNCTION" << endl;
			#endif
			
			NLCitem* functionArgument = NULL;
			string functionName = "";
			if(findFunctionArgument(&(currentCodeBlockInLevel->parameters), NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION, &functionArgument))
			{
				functionName = functionArgument->functionName;
			}
			
			string functionArguments = "";
			#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS
			//#ifdef NLC_NONOO_DISABLE_CLASS_HEIRACHY
			string functionDeclarationOwnerName = "";
			string functionDeclarationObjectName = "";
			//#endif
			generateFunctionArgumentsBasedOnActionAndActionObjectVars(&(currentCodeBlockInLevel->parameters), &functionArguments, progLang, &functionDeclarationOwnerName, &functionDeclarationObjectName);
			#endif
			
			#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS
			generateLocalFunctionArgumentsBasedOnImplicitDeclarationsString(&(currentCodeBlockInLevel->parameters), &functionArguments, progLang);
			#endif
			
			#ifndef NLC_NONOO_DISABLE_CLASS_HEIRACHY
			string functionOwnerContext = generateFunctionOwnerContext(&(currentCodeBlockInLevel->parameters), progLang);
			#endif
			
			#ifdef NLC_NONOO_DISABLE_CLASS_HEIRACHY
			string codeBlockText = functionDeclarationOwnerName + functionArgument->name + functionDeclarationObjectName + NLC_FUNCTION_NAME_APPEND + progLangOpenParameterSpace[progLang] + functionArguments + progLangCloseParameterSpace[progLang];	//main(){
			#else
			string codeBlockText = functionOwnerContext + functionName + progLangOpenParameterSpace[progLang] + functionArguments + progLangCloseParameterSpace[progLang];	//main(){
			#endif
			printLine(codeBlockText, level, code);
			printLine(progLangOpenBlock[progLang], level, code);
		}
		#ifdef NLC_RECORD_ACTION_HISTORY
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_RECORD_HISTORY_ACTION_SUBJECT)
		{
			NLCitem* functionArgument = NULL;
			string functionName = "";
			if(findFunctionArgument(&(currentCodeBlockInLevel->parameters), NLC_ITEM_TYPE_FUNCTION_EXECUTION_ARGUMENT_FUNCTION, &functionArgument))
			{
				functionName = functionArgument->functionName;
			}
			
			NLCitem* functionOwnerArgument = NULL;
			string functionOwnerName = "";
			if(findFunctionArgument(&(currentCodeBlockInLevel->parameters), NLC_ITEM_TYPE_FUNCTION_EXECUTION_ARGUMENT_FUNCTION_OWNER, &functionOwnerArgument))
			{
				functionOwnerName = functionOwnerArgument->instanceName;
			}
			
			generateCodeAddActionSubject(functionArgument, functionOwnerArgument, progLang, code, level);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_RECORD_HISTORY_ACTION_OBJECT)
		{
			NLCitem* functionArgument = NULL;
			string functionName = "";
			if(findFunctionArgument(&(currentCodeBlockInLevel->parameters), NLC_ITEM_TYPE_FUNCTION_EXECUTION_ARGUMENT_FUNCTION, &functionArgument))
			{
				functionName = functionArgument->functionName;
			}
			
			NLCitem* functionObjectArgument = NULL;
			string functionObjectName = "";
			if(findFunctionArgument(&(currentCodeBlockInLevel->parameters), NLC_ITEM_TYPE_FUNCTION_EXECUTION_ARGUMENT_FUNCTION_OBJECT, &functionObjectArgument))
			{
				functionObjectName = functionObjectArgument->instanceName;
			}
			
			generateCodeAddActionObject(functionArgument, functionObjectArgument, progLang, code, level);
		}	
		#endif	
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_ADD_NEW_PROPERTY)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_ADD_NEW_PROPERTY" << endl;
			#endif
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			string codeBlockTextCreate = generateCodeNewEntity(param2, progLang);
			printLine(codeBlockTextCreate, level, code);
			generateCodeAddProperty(param1, param2, progLang, code, level);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_ADD_NEW_ENTITY_TO_LOCAL_LIST)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_ADD_NEW_ENTITY_TO_LOCAL_LIST" << endl;
			#endif			
			generateCodeAddNewEntityToLocalList(param1, progLang, code, level);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_ADD_NEW_CONDITION)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_ADD_NEW_CONDITION" << endl;
			#endif
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			NLCitem* param3 = currentCodeBlockInLevel->parameters.at(2);
			string codeBlockTextCreate = generateCodeNewEntity(param3, progLang);
			printLine(codeBlockTextCreate, level, code);

			generateCodeAddCondition(param1, param2, param3, progLang, code, level);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_ADD_PROPERTY)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_ADD_PROPERTY" << endl;
			#endif
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			generateCodeAddProperty(param1, param2, progLang, code, level);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_LOCAL_LIST)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_LOCAL_LIST" << endl;
			#endif
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);

			generateCodeAddEntityToLocalList(param1, param2, progLang, code, level);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_ADD_CONDITION)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_ADD_CONDITION" << endl;
			#endif
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			NLCitem* param3 = currentCodeBlockInLevel->parameters.at(2);
			
			generateCodeAddCondition(param1, param2, param3, progLang, code, level);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_FOR_PROPERTY_LIST)
		{
			string iterIndexString = convertIntToString(level);
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_FOR_PROPERTY_LIST" << endl;
			#endif
			string codeBlockText = progLangFor[progLang] + progLangForIterPart1[progLang] + generateCodeEntityListDefinitionTypeText(param1->className, progLang) + progLangForIterPart2a[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart2c[progLang] + contextParam1 + generatePropertyListName(param1) + progLangForIterPart3a[progLang] + progLangForIterPart3b[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart3c[progLang] + contextParam1 + generatePropertyListName(param1) + progLangForIterPart4a[progLang] + progLangForIterPart4b[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart4c[progLang];
			printLine(codeBlockText, level, code);
			printLine(progLangOpenBlock[progLang], level, code);
			string tempVarDeclarationText = generateCodeEntityDefinitionText(param1, progLang) + progLangEquals[progLang] + progLangPointer[progLang] + progLangForIterName[progLang] + iterIndexString + progLangEndLine[progLang];	//OLD:  param1->className + NLC_ITEM_TYPE_TEMP_VAR_APPENDITION
			printLine(tempVarDeclarationText, (level+1), code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_FOR_LOCAL_LIST)
		{
			string iterIndexString = convertIntToString(level);
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_FOR_LOCAL_LIST" << endl;
			#endif
			string codeBlockText = progLangFor[progLang] + progLangForIterPart1[progLang] + generateCodeEntityListDefinitionTypeText(param1->className, progLang) + progLangForIterPart2a[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart2c[progLang] + generateLocalListName(param1) + progLangForIterPart3a[progLang] + progLangForIterPart3b[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart3c[progLang] + generateLocalListName(param1) + progLangForIterPart4a[progLang] + progLangForIterPart4b[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart4c[progLang];			
			printLine(codeBlockText, level, code);
			printLine(progLangOpenBlock[progLang], level, code);
			string tempVarDeclarationText = generateCodeEntityDefinitionText(param1, progLang) + progLangEquals[progLang] + progLangPointer[progLang] + progLangForIterName[progLang] + iterIndexString + progLangEndLine[progLang];	//OLD:  param1->className + NLC_ITEM_TYPE_TEMP_VAR_APPENDITION
			printLine(tempVarDeclarationText, (level+1), code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_FOR_CONDITION_LIST)
		{
			string iterIndexString = convertIntToString(level);
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_FOR_CONDITION_LIST" << endl;
			#endif
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			string codeBlockText = progLangFor[progLang] + progLangForIterPart1[progLang] + generateCodeConditionListDefinitionTypeText(param1->className, param2->className, progLang) + progLangForIterPart2a[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart2c[progLang] + contextParam1 + generateConditionListName(param1->className, param2->className) + progLangForIterPart3a[progLang] + progLangForIterPart3b[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart3cMap[progLang] + contextParam1 + generateConditionListName(param1->className, param2->className) + progLangForIterPart4a[progLang] + progLangForIterPart4b[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart4c[progLang];
			printLine(codeBlockText, level, code);
			printLine(progLangOpenBlock[progLang], level, code);
			#ifdef NLC_NONOO
			string tempVarDeclarationText = generateCodeEntityDefinitionText(param1, progLang) + progLangEquals[progLang] +  progLangPointer[progLang] + progLangForIterName[progLang] + iterIndexString + progLangEndLine[progLang];
			printLine(tempVarDeclarationText, (level+1), code);
			string tempVarDeclarationText2 = generateCodeEntityDefinitionText(param2, progLang) + progLangEquals[progLang] + progLangOpenParameterSpace[progLang] + progLangPointer[progLang] + progLangForIterName[progLang] + iterIndexString + progLangCloseParameterSpace[progLang] + progLangObjectReferenceDelimiter[progLang] + generateGIAconditionObjectListName() + progLangEndLine[progLang];
			printLine(tempVarDeclarationText2, (level+1), code);
			#else
			string tempVarDeclarationText = generateCodeEntityDefinitionText(param2, progLang) + progLangEquals[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterConditionObjectReference[progLang] + progLangEndLine[progLang];
			printLine(tempVarDeclarationText, (level+1), code);
			#endif
		}
		#ifdef NLC_NONOO
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_IF_PROPERTY_NAME)
		{
			string tempVarEntityNameCheckText = progLangIf[progLang] + generateCodeEntityNameTestText(param1, progLang);	 //if(tempPropertyEntity->entityName == param1->name) {
			printLine(tempVarEntityNameCheckText, (level), code);
			printLine(progLangOpenBlock[progLang], level, code);		
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_IF_CONDITION_NAME)
		{
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			string tempVarEntityNameCheckText = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + generateCodeEntityNameTestText(param1, progLang) + STRING_SPACE + progLangAnd[progLang] + STRING_SPACE + generateCodeEntityNameTestText(param2, progLang) + progLangCloseParameterSpace[progLang];	//if((tempConditionEntity->entityName == param1->name) && (tempConditionObjectEntity->entityName == param2->name)) {
			printLine(tempVarEntityNameCheckText, (level), code);
			printLine(progLangOpenBlock[progLang], level, code);
		}
		#ifdef NLC_RECORD_ACTION_HISTORY
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_IF_ACTION_NAME)
		{
			string tempVarEntityNameCheckText = progLangIf[progLang] + generateCodeEntityNameTestText(param1, progLang);	 //if(tempActionEntity->entityName == param1->name) {
			printLine(tempVarEntityNameCheckText, (level), code);
			printLine(progLangOpenBlock[progLang], level, code);
		}
		#endif
		#endif
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
			string tempVarDeclarationText = generateCodeEntityDefinitionText(param1, progLang) + progLangEquals[progLang] + progLangPointer[progLang] + progLangForIterName[progLang] + iterIndexString + progLangEndLine[progLang];
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
			string tempVarDeclarationText = generateCodeEntityDefinitionText(param1, progLang) + progLangEquals[progLang] + progLangPointer[progLang] + progLangForIterName[progLang] + iterIndexString + progLangEndLine[progLang];	//OLD:  param1->className + NLC_ITEM_TYPE_TEMP_VAR_APPENDITION
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
			string tempVarDeclarationText = generateCodeEntityDefinitionText(param1, progLang) + progLangEquals[progLang] + progLangPointer[progLang] + progLangForIterName[progLang] + iterIndexString + progLangEndLine[progLang];	//OLD:  param1->className + NLC_ITEM_TYPE_TEMP_VAR_APPENDITION
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
			string tempVarDeclarationText = generateCodeEntityDefinitionText(param1, progLang) + progLangEquals[progLang] + progLangPointer[progLang] + progLangForIterName[progLang] + iterIndexString + progLangEndLine[progLang];	//OLD:  param1->className + NLC_ITEM_TYPE_TEMP_VAR_APPENDITION
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
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_DECLARE_AND_INITIALISE_VARIABLE)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_DECLARE_AND_INITIALISE_VARIABLE" << endl;
			#endif
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);

			string codeBlockTextDeclareAndInitialiseVariable = generateCodeEntityDefinitionText(param1, progLang) + progLangEquals[progLang] + param2->instanceName + progLangEndLine[progLang];
			printLine(codeBlockTextDeclareAndInitialiseVariable, level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_DECLARE_NEW_VARIABLE)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_DECLARE_NEW_VARIABLE" << endl;
			#endif
			string codeBlockTextDeclareNewVariable = generateCodeEntityDefinitionText(param1, progLang) + progLangEquals[progLang] + progLangNewObject[progLang] + param1->className + progLangOpenParameterSpace[progLang] + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];
			printLine(codeBlockTextDeclareNewVariable, level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_DECLARE_NEW_LOCAL_LIST_VARIABLE)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_DECLARE_NEW_LOCAL_LIST_VARIABLE" << endl;
			#endif
			string localListDeclarationText = generateCodeEntityListDefinitionTypeText(param1->className, progLang) + generateLocalListName(param1) + progLangEndLine[progLang];	//vector<param1Class*> param1instanceList;
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

			string codeBlockText = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + negativeModifierString + progLangOpenParameterSpace[progLang] + contextParam1 + generatePropertyListName(param1) + progLangObjectReferenceDelimiter2[progLang] + progLangHasEntity[progLang] + progLangCloseParameterSpace[progLang] + progLangCloseParameterSpace[progLang];		//if(!(context1->param1PropertyList.empty())){

			printLine(codeBlockText, level, code);
			printLine(progLangOpenBlock[progLang], level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_IF_HAS_CONDITION)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_IF_HAS_CONDITION" << endl;
			#endif

			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			string codeBlockText = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + negativeModifierString + progLangOpenParameterSpace[progLang] + contextParam1 + generateConditionListName(param1->className, param2->className) + progLangObjectReferenceDelimiter2[progLang] + progLangHasCondition[progLang] + progLangCloseParameterSpace[progLang] + progLangCloseParameterSpace[progLang];	//if(!(context1->param1param2ConditionList.empty())){
			printLine(codeBlockText, level, code);
			printLine(progLangOpenBlock[progLang], level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_WHILE_HAS_PROPERTY)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_WHILE_HAS_PROPERTY" << endl;
			#endif

			string codeBlockText = progLangWhile[progLang] + progLangOpenParameterSpace[progLang] + negativeModifierString + progLangOpenParameterSpace[progLang] + contextParam1 + generatePropertyListName(param1) + progLangObjectReferenceDelimiter2[progLang] + progLangHasEntity[progLang] + progLangCloseParameterSpace[progLang] + progLangCloseParameterSpace[progLang];		//while(!(context1->param1PropertyList.empty())){

			printLine(codeBlockText, level, code);
			printLine(progLangOpenBlock[progLang], level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_WHILE_HAS_CONDITION)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_WHILE_HAS_CONDITION" << endl;
			#endif

			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);

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
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_REMOVE_PROPERTY)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_REMOVE_PROPERTY" << endl;
			#endif
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			generateCodeRemoveProperty(param1, param2, progLang, code, level);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_REMOVE_PROPERTIES)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_REMOVE_PROPERTIES" << endl;
			#endif
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			generateCodeRemoveProperties(param1, param2, progLang, code, level);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_REMOVE_ENTITIES_FROM_LOCAL_LIST)
		{
			//not currently used
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_REMOVE_ENTITIES_FROM_LOCAL_LIST" << endl;
			#endif

			string codeBlockText = generateLocalListName(param1) + progLangObjectReferenceDelimiter2[progLang] + progLangRemoveProperties[progLang] + progLangEndLine[progLang];		//param1instanceList.clear();
			printLine(codeBlockText, level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_REMOVE_CONDITION)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_REMOVE_CONDITION" << endl;
			#endif
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			NLCitem* param3 = currentCodeBlockInLevel->parameters.at(2);
			generateCodeRemoveCondition(param1, param2, param3, progLang, code, level);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_REMOVE_CONDITIONS)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_REMOVE_CONDITIONS" << endl;
			#endif
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			NLCitem* param3 = currentCodeBlockInLevel->parameters.at(2);
			generateCodeRemoveConditions(param1, param2, param3, progLang, code, level);
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
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
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
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			string genericListAppendName = param2->name;
	
			string localListDeclarationText = generateCodeGenericListDefinitionText(param1, genericListAppendName, progLang) + progLangEndLine[progLang];	//vector<param1Class*> param1CategoryList;
			printLine(localListDeclarationText, level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST" << endl;
			#endif
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			NLCitem* param3 = currentCodeBlockInLevel->parameters.at(2);
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
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			string genericListAppendName = param2->name;
			
			string codeBlockText = progLangFor[progLang] + progLangForIterPart1[progLang] + generateCodeEntityListDefinitionTypeText(param1->className, progLang) + progLangForIterPart2a[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart2c[progLang] + generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangForIterPart3a[progLang] + progLangForIterPart3b[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart3c[progLang] + generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangForIterPart4a[progLang] + progLangForIterPart4b[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart4c[progLang];
			printLine(codeBlockText, level, code);
			printLine(progLangOpenBlock[progLang], level, code);
			string tempVarDeclarationText = generateCodeEntityDefinitionText(param1, progLang) + progLangEquals[progLang] + progLangPointer[progLang] + progLangForIterName[progLang] + iterIndexString + progLangEndLine[progLang];	//OLD:  param1->className + NLC_ITEM_TYPE_TEMP_VAR_APPENDITION
			printLine(tempVarDeclarationText, (level+1), code);
		}
		#ifdef NLC_CATEGORIES_TEST_PLURALITY
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_IF_HAS_GENERIC_ENTITY)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_IF_HAS_GENERIC_ENTITY" << endl;
			#endif
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
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
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			string genericListAppendName = param2->name;

			NLCitem* param3 = currentCodeBlockInLevel->parameters.at(2);
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
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			string genericListAppendName = param2->name;

			string tempVarDeclarationText = generateCodeEntityDefinitionText(param1, progLang) + progLangEquals[progLang] + generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangObjectReferenceDelimiter2[progLang] + progLangGetLast[progLang] + progLangEndLine[progLang];

			printLine(tempVarDeclarationText, level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST_CHECK_LAST_SENTENCE_REFERENCED_SINGULAR_EXECUTE_FUNCTION)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST_CHECK_LAST_SENTENCE_REFERENCED_SINGULAR_EXECUTE_FUNCTION" << endl;
			#endif

			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			NLCitem* param3 = currentCodeBlockInLevel->parameters.at(2);
			
			generateCodeAddToCategoryIfPassSingularDefiniteReferencingTestsExecuteFunction(param1, param2, param3, progLang, code, level);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST_CHECK_LAST_SENTENCE_REFERENCED_SINGULAR_NEW_FUNCTION)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST_CHECK_LAST_SENTENCE_REFERENCED_SINGULAR_NEW_FUNCTION" << endl;
			#endif
			
			generateCodeAddToCategoryIfPassSingularDefiniteReferencingTestsNewFunction(progLang, code, level);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_UPDATE_LAST_SENTENCE_REFERENCED)	//execute for all new/undeclared/indefinite entities and accessed category items
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_UPDATE_LAST_SENTENCE_REFERENCED" << endl;
			#endif
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
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
		#ifdef NLC_PERFORM_PLURAL_DEFINITE_REFERENCING_TESTS
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST_CHECK_LAST_SENTENCE_REFERENCED_PLURAL_EXECUTE_FUNCTION)
		{//finish coding this
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST_CHECK_LAST_SENTENCE_REFERENCED_PLURAL_EXECUTE_FUNCTION" << endl;
			#endif

			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			NLCitem* param3 = currentCodeBlockInLevel->parameters.at(2);
			
			generateCodeAddToCategoryIfPassPluralDefiniteReferencingTestsExecuteFunction(param1, param2, param3, progLang, code, level);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST_CHECK_LAST_SENTENCE_REFERENCED_PLURAL_NEW_FUNCTION)
		{//finish coding this
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST_CHECK_LAST_SENTENCE_REFERENCED_PLURAL_NEW_FUNCTION" << endl;
			#endif
			
			generateCodeAddToCategoryIfPassPluralDefiniteReferencingTestsNewFunction(progLang, code, level);
		}	
		#endif	
		#ifdef NLC_GENERATE_TYPE_LISTS
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_DECLARE_NEW_GENERIC_LIST_VARIABLE2)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_DECLARE_NEW_GENERIC_LIST_VARIABLE2" << endl;
			#endif
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			string genericListAppendName = param2->name;
	
			string localListDeclarationText = generateCodeEntityListDefinitionTypeText2(param1->className, progLang) + generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangEndLine[progLang];	//vector<vector<param1Class*>> param1instanceTypeList;
			printLine(localListDeclarationText, level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST2)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST2" << endl;
			#endif
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			NLCitem* param3 = currentCodeBlockInLevel->parameters.at(2);
			NLCitem* param4 = currentCodeBlockInLevel->parameters.at(3);
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
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			string genericListAppendName = param2->name;
			
			string codeBlockText = progLangFor[progLang] + progLangForIterPart1[progLang] + generateCodeEntityListDefinitionTypeText2(param1->className, progLang) + progLangForIterPart2a[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart2c[progLang] + generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangForIterPart3a[progLang] + progLangForIterPart3b[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart3c[progLang] + generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangForIterPart4a[progLang] + progLangForIterPart4b[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart4c[progLang];
			printLine(codeBlockText, level, code);
			printLine(progLangOpenBlock[progLang], level, code);
			string tempVarDeclarationText = generateCodeEntityListDefinitionTypeText(param1->className, progLang) + generatePropertyListName(param1) + progLangEquals[progLang] + progLangPointer[progLang] + progLangForIterName[progLang] + iterIndexString + progLangEndLine[progLang];	//OLD:  param1->className + NLC_ITEM_TYPE_TEMP_VAR_APPENDITION
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
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			string genericListAppendName = param2->name;

			NLCitem* param3 = currentCodeBlockInLevel->parameters.at(2);
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

			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
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

			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			string valueString = param2->name;

			string codeBlockText = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + contextParam1 + generatePropertyListName(param1) + progLangObjectReferenceDelimiter2[progLang] + progLangSizeOfList[progLang] + progLangGreaterThan[progLang] + valueString + progLangCloseParameterSpace[progLang];		//if(context1->param1PropertyList.size() > x){

			printLine(codeBlockText, level, code);
			printLine(progLangOpenBlock[progLang], level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_IF_HAS_MORE_THAN_NUM_CONDITION)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_IF_HAS_MORE_THAN_NUM_CONDITION" << endl;
			#endif

			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);			
			NLCitem* param3 = currentCodeBlockInLevel->parameters.at(2);
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

			generateCodeAddEntityToReferenceContextListNewFunction(progLang, code, level);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_CONTEXT_LIST_EXECUTE_FUNCTION)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_CONTEXT_LIST_EXECUTE_FUNCTION" << endl;
			#endif
			
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			NLCitem* param3 = currentCodeBlockInLevel->parameters.at(2);
			
			generateCodeAddEntityToReferenceContextListExecuteFunction(param1, param2, param3, progLang, code, level);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_CLEAR_CONTEXT_LIST_NEW_FUNCTION)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_CLEAR_CONTEXT_LIST_NEW_FUNCTION" << endl;
			#endif
			
			generateCodeClearReferenceContextListNewFunction(progLang, code, level);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_CLEAR_CONTEXT_LIST_EXECUTE_FUNCTION)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_CLEAR_CONTEXT_LIST_EXECUTE_FUNCTION" << endl;
			#endif
			
			generateCodeClearReferenceContextListExecuteFunction(param1, progLang, code, level);
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
			
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);	//functionArgumentPassCast
			
			generateCodeCastVectorExecuteFunction(param1, param2, progLang, code, level);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_CAST_VECTOR_NEW_FUNCTION)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_CAST_VECTOR_NEW_FUNCTION" << endl;
			#endif

			generateCodeCastVectorNewFunction(progLang, code, level);
		}
		#endif
		#ifdef NLC_USE_ADVANCED_REFERENCING_SUPPORT_ALIASES
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_ADD_ALIAS_TO_ENTITY_ALIAS_LIST)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_ADD_ALIAS_TO_ENTITY_ALIAS_LIST" << endl;
			#endif
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			string aliasName = param2->name;

			string codeBlockTextAddAliasToEntityAliasList = param1->instanceName + progLangObjectReferenceDelimiter[progLang] + NLC_ITEM_TYPE_ALIASLIST_VAR_APPENDITION + progLangObjectReferenceDelimiter2[progLang] + progLangAddProperty[progLang] + progLangOpenParameterSpace[progLang] + progLangStringOpenClose[progLang] + aliasName + progLangStringOpenClose[progLang] + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//entity->aliasList.push_back("aliasName");			
			printLine(codeBlockTextAddAliasToEntityAliasList, level, code);
				
			/*
			string codeBlockTextAddEntityToAliasList = generateEntityStringMapListName(NLC_USE_ADVANCED_REFERENCING_SUPPORT_ALIASES_ALIAS_LIST_NAME_START, NLC_ITEM_TYPE_ALIASLIST_VAR_APPENDITION) + progLangObjectReferenceDelimiter2[progLang] + progLangAddCondition[progLang] + progLangOpenParameterSpace[progLang] + generateEntityStringPairTexts(param1->name, genericEntityClassName, generateDynamicCastOfEntity(param2->instanceName, genericEntityClassName, progLang), progLang) + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//AliasList.insert(pair<string, param2className*>(param1, dynamic_cast<genericEntity*>param2));
			*/
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_FIND_ALIAS_AND_ADD_TO_CATEGORY_LIST_NEW_FUNCTION)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_FIND_ALIAS_AND_ADD_TO_CATEGORY_LIST_NEW_FUNCTION" << endl;
			#endif

			generateCodeFindAliasAndAddToCategoryListNewFunction(progLang, code, level);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_FIND_ALIAS_AND_ADD_TO_CATEGORY_LIST_EXECUTE_FUNCTION)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_FIND_ALIAS_AND_ADD_TO_CATEGORY_LIST_EXECUTE_FUNCTION" << endl;
			#endif
			
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			NLCitem* param3 = currentCodeBlockInLevel->parameters.at(2);

			generateCodeFindAliasAndAddToCategoryListExecuteFunction(param1, param2, param3, progLang, code, level);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_FIND_ALIAS_NEW_FUNCTION)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_FIND_ALIAS_NEW_FUNCTION" << endl;
			#endif

			generateCodeFindAliasNewFunction(progLang, code, level);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_FIND_ALIAS_EXECUTE_FUNCTION)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_FIND_ALIAS_EXECUTE_FUNCTION" << endl;
			#endif
			
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			
			generateCodeFindAliasExecuteFunction(param1, param2, progLang, code, level);
		}
		#endif
		#ifdef NLC_USE_SUPPORT_REFERENCING_OBJECTS_IN_PLURAL_LIST_BY_NUMBER
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_IN_PROPERTY_LIST)
		{
			string iterIndexString = convertIntToString(level);
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_IN_PROPERTY_LIST" << endl;
			#endif
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			string listIndexString = param2->name;
			string codeBlockText = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + listIndexString + progLangLessThanOrEqualTo[progLang] + contextParam1 + generatePropertyListName(param1) + progLangObjectReferenceDelimiter2[progLang] + progLangSizeOfList[progLang] + progLangCloseParameterSpace[progLang];		//if(X <= param1PropertyList.size()){
			printLine(codeBlockText, level, code);
			printLine(progLangOpenBlock[progLang], level, code);	//{
			string tempVarDeclarationText = generateCodeEntityDefinitionText(param1, progLang) + progLangEquals[progLang] + contextParam1 + generatePropertyListName(param1) + progLangGetAtPositionPart1[progLang] + listIndexString + progLangGetAtPositionPart2[progLang] + progLangEndLine[progLang];		//param1* tempVar = param1PropertyList.at(listIndex-1);
			printLine(tempVarDeclarationText, (level+1), code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_IN_LOCAL_LIST)
		{
			string iterIndexString = convertIntToString(level);
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_IN_LOCAL_LIST" << endl;
			#endif
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			string listIndexString = param2->name;
			string codeBlockText = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + listIndexString + progLangLessThanOrEqualTo[progLang] + generateLocalListName(param1) + progLangObjectReferenceDelimiter2[progLang] + progLangSizeOfList[progLang] + progLangCloseParameterSpace[progLang];		//if(X <= param1LocalList.size()){
			printLine(codeBlockText, level, code);
			printLine(progLangOpenBlock[progLang], level, code);	//{
			string tempVarDeclarationText = generateCodeEntityDefinitionText(param1, progLang) + progLangEquals[progLang] + generateLocalListName(param1) + progLangGetAtPositionPart1[progLang] + listIndexString + progLangGetAtPositionPart2[progLang] + progLangEndLine[progLang];		//param1* tempVar = param1LocalList.at(listIndex-1);
			printLine(tempVarDeclarationText, (level+1), code);
		}
		#endif
		#ifdef NLC_SUPPORT_REDEFINITIONS
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_CHECK_PARENT_CLASS_NAME_EXECUTE_FUNCTION1)
		{
			string iterIndexString = convertIntToString(level);
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_CHECK_PARENT_CLASS_NAME_EXECUTE_FUNCTION1" << endl;
			#endif
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			
			generateCodeCheckParentClassNameExecuteFunction1(param1, param2, progLang, code, level);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_CHECK_PARENT_CLASS_NAME_EXECUTE_FUNCTION2)
		{
			string iterIndexString = convertIntToString(level);
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_CHECK_PARENT_CLASS_NAME_EXECUTE_FUNCTION2" << endl;
			#endif
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			
			generateCodeCheckParentClassNameExecuteFunction2(param1, param2, progLang, code, level);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_CHECK_PARENT_CLASS_NAME_NEW_FUNCTION)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_CHECK_PARENT_CLASS_NAME_NEW_FUNCTION" << endl;
			#endif

			generateCodeCheckParentClassNameNewFunction(progLang, code, level);
		}		
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_CONVERT_PARENT_TO_CHILD_CLASS)
		{
			string iterIndexString = convertIntToString(level);
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_CONVERT_PARENT_TO_CHILD_CLASS" << endl;
			#endif
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			
			string codeBlockConvertParentToChildClassText = generateCodeEntityDefinitionText(param2, progLang) + progLangEquals[progLang] + generateDynamicCastOfEntity(param1->instanceName, param2->className, progLang) + progLangEndLine[progLang];	//param2class* param2instance = dynamic_cast<param2class*>(param1instance);
			printLine(codeBlockConvertParentToChildClassText, level, code);
			string codeBlockRenameChildClassObjectToChildClassText = generateEntityName(param2) + progLangObjectReferenceDelimiter[progLang] + progLangClassNameVariableName[progLang] + progLangEquals[progLang] + progLangStringOpenClose[progLang] + param2->name + progLangStringOpenClose[progLang] + progLangEndLine[progLang];	//param2instance->name = "param2";	//added 1n6b
			printLine(codeBlockRenameChildClassObjectToChildClassText, level, code);
		}	
		#endif
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_DECLARE_TEMP_VARIABLE)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_DECLARE_TEMP_VARIABLE" << endl;
			#endif
			string tempEntityDeclarationText = generateCodeEntityDeclarationSetToNull(param1, progLang);	//param1Class* param1 = NULL;
			printLine(tempEntityDeclarationText, level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_SET_TEMP_VARIABLE)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_SET_TEMP_VARIABLE" << endl;
			#endif
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			string tempEntitySetText = generateCodeSetEntity(param1, param2, progLang);	//param1 = param2;
			printLine(tempEntitySetText, level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_DECLARE_TEMP_VARIABLE_AND_SET_TO_ENTITY)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_DECLARE_TEMP_VARIABLE_AND_SET_TO_ENTITY" << endl;
			#endif
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			string tempEntityDeclarationText = generateCodeEntityDeclarationSetToEntity(param1, param2, progLang);	//param1Class* param1 = param2;
			printLine(tempEntityDeclarationText, level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_IF_TEMP_VARIABLE_EQUALS_ENTITY)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_IF_TEMP_VARIABLE_EQUALS_ENTITY" << endl;
			#endif
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			string tempVarCheckText = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + generateEntityName(param1) + progLangStringEqualsTest[progLang] + generateEntityName(param2) + progLangCloseParameterSpace[progLang];	 //if(param1 == param2) {
			printLine(tempVarCheckText, level, code);	
			printLine(progLangOpenBlock[progLang], level, code);	//{
		}
		#ifdef NLC_USE_NON_LIBRARY_FUNCTIONS_EXTENDED
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_ADD_PROPERTY_NEW_FUNCTION)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_ADD_PROPERTY_NEW_FUNCTION" << endl;
			#endif	
			generateCodeAddPropertyNewFunction(progLang, code, level);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_ADD_CONDITION_NEW_FUNCTION)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_ADD_CONDITION_NEW_FUNCTION" << endl;
			#endif	
			generateCodeAddConditionNewFunction(progLang, code, level);
		}		
		#endif
		#ifdef NLC_USE_MATH_OBJECTS
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_SET_MATH_VALUE)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_SET_MATH_VALUE" << endl;
			#endif
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			string setMathValueText = generateCodeEntityMathValueText(param1, progLang) + progLangEquals[progLang] + param2->name + progLangEndLine[progLang];	 //param1->value = param2;
			printLine(setMathValueText, level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_DECLARE_NEW_DECIMAL_POINTER_VARIABLE)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_DECLARE_NEW_DECIMAL_POINTER_VARIABLE" << endl;
			#endif
			string declareNewDecimalPointerVariableText = generateCodeDeclareNewDecimalPointerVariableText(param1, progLang);	 //double* param1 = NULL;
			printLine(declareNewDecimalPointerVariableText, level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_SET_DECIMAL_POINTER_TO_ENTITY_MATH_VALUE)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_SET_DECIMAL_POINTER_TO_ENTITY_MATH_VALUE" << endl;
			#endif
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			string setDecimalPointerToEntityMathValueText = generateCodePointerValueText(param1, progLang) + progLangEquals[progLang] + generateCodeEntityMathValueText(param2, progLang) + progLangEndLine[progLang];	 //*param1 = param2->value;
			printLine(setDecimalPointerToEntityMathValueText, level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_CHECK_DECIMAL_POINTER_VALUE)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_CHECK_DECIMAL_POINTER_VALUE" << endl;
			#endif
			
			string ifDecimalPointerNotNullText = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + param1->name + progLangIsNotEqualTo[progLang] + progLangNullPointer[progLang] + progLangCloseParameterSpace[progLang];	 //if(param1 != NULL)
			printLine(ifDecimalPointerNotNullText, level, code);
			printLine(progLangOpenBlock[progLang], level, code);	//{			
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



void generateFunctionExecutionArgumentsWithActionConceptInheritanceString(vector<NLCclassDefinition*>* classDefinitionList, vector<NLCitem*>* codeBlockParameters, string* functionArguments, int progLang, string* functionDeclarationOwnerName, string* functionDeclarationObjectName)
{
	vector<NLCitem*>* parameters;
	#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS
	#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
	parameters = codeBlockParameters;

	string functionName = "";
	NLCitem* functionArgument = NULL;
	if(findFunctionArgument(codeBlockParameters, NLC_ITEM_TYPE_FUNCTION_EXECUTION_ARGUMENT_FUNCTION, &functionArgument))
	{
		functionName = functionArgument->name;
	}
	else
	{
		cout << "generateFunctionExecutionArgumentsWithActionConceptInheritanceString{}: NLC_ITEM_TYPE_FUNCTION_EXECUTION_ARGUMENT_FUNCTION not found" << endl;
		exit(0);
	}
	
	string functionOwnerName = "";
	NLCitem* functionOwnerArgument = NULL;
	bool hasFunctionOwnerClass = false;
	if(findFunctionArgument(codeBlockParameters, NLC_ITEM_TYPE_FUNCTION_EXECUTION_ARGUMENT_FUNCTION_OWNER, &functionOwnerArgument))
	{
		hasFunctionOwnerClass = true;
		functionOwnerName = functionOwnerArgument->name;
	}
	
	string functionObjectName = "";
	NLCitem* functionObjectArgument = NULL;
	bool hasFunctionObjectClass = false;
	if(findFunctionArgument(codeBlockParameters, NLC_ITEM_TYPE_FUNCTION_EXECUTION_ARGUMENT_FUNCTION_OBJECT, &functionObjectArgument))
	{
		hasFunctionObjectClass = true;
		functionObjectName = functionObjectArgument->name;		
	}
	
	bool foundFunctionOwnerExactMatch = false;
	bool foundFunctionObjectExactMatch = false;
	#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
	cout << "\n\n\n\n generateFunctionExecutionArgumentsWithActionConceptInheritanceString{}:" << endl;
	cout << "functionName = " << functionName << endl;
	cout << "functionOwnerName = " << functionOwnerName << endl;
	cout << "functionObjectName = " << functionObjectName << endl;
	#endif
	NLCclassDefinition* functionDeclaration = NULL;	//NB "functionDeclaration" should be "functionDeclaration"
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
			NLCitem* functionOwnerArgumentDeclaration = NULL;
			if(findFunctionArgument(&(functionDeclaration->parameters), NLC_ITEM_TYPE_FUNCTION_DECLARATION_ARGUMENT_FUNCTION_OWNER, &functionOwnerArgumentDeclaration))
			{
				functionOwnerArgument->functionArgumentPassCastRequired = true;
				functionOwnerArgument->functionArgumentPassCastClassName = generateClassName(functionOwnerArgumentDeclaration->name);
				#ifdef NLC_NONOO_DISABLE_CLASS_HEIRACHY
				*functionDeclarationOwnerName = functionOwnerArgumentDeclaration->name;
				#endif
			}
			else
			{
				cout << "generateFunctionExecutionArgumentsWithActionConceptInheritanceString{} error: !findFunctionArgument: NLC_ITEM_TYPE_FUNCTION_DECLARATION_ARGUMENT_FUNCTION_OBJECT - functionName = " << functionName << endl;
			}
		}	
		#endif
		if(hasFunctionObjectClass && !foundFunctionObjectExactMatch)
		{
			#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
			cout << "(hasFunctionObjectClass && !foundFunctionObjectExactMatch)" << endl;
			#endif
			NLCitem* functionObjectArgumentDeclaration = NULL;
			if(findFunctionArgument(&(functionDeclaration->parameters), NLC_ITEM_TYPE_FUNCTION_DECLARATION_ARGUMENT_FUNCTION_OBJECT, &functionObjectArgumentDeclaration))
			{
				functionObjectArgument->functionArgumentPassCastRequired = true;
				functionObjectArgument->functionArgumentPassCastClassName = generateClassName(functionObjectArgumentDeclaration->name);
				#ifdef NLC_NONOO_DISABLE_CLASS_HEIRACHY
				*functionDeclarationObjectName = functionObjectArgumentDeclaration->name;
				#endif
			}
			else
			{
				cout << "generateFunctionExecutionArgumentsWithActionConceptInheritanceString{} error: !findFunctionArgument: NLC_ITEM_TYPE_FUNCTION_DECLARATION_ARGUMENT_FUNCTION_OBJECT - functionName = " << functionName << endl;
			}
		}
		
		#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_BASED_ON_IMPLICITLY_DECLARED_VARIABLES_IN_CURRENT_FUNCTION_DEFINITION
		for(vector<NLCitem*>::iterator parametersIterator = functionDeclaration->parameters.begin(); parametersIterator < functionDeclaration->parameters.end(); parametersIterator++)
		{
			NLCitem* currentItem = *parametersIterator;
			//cout << "1 currentItem->itemType = " << currentItem->itemType << endl;
			if(currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_DECLARATION_ARGUMENT_INSTANCE_OR_CLASS_LIST)
			{
				NLCitem* newFunctionArgument = new NLCitem(currentItem);
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
		NLCitem* currentItem = *parametersIterator;

		//cout << "2 currentItem->itemType = " << currentItem->itemType << endl;
		if(currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_EXECUTION_ARGUMENT_INSTANCE_OR_CLASS_LIST)
		{
			//cout << "3 currentItem->name = " << currentItem->name << endl;
			if(*functionArguments != "")
			{
				*functionArguments = *functionArguments + progLangClassMemberFunctionParametersNext[progLang];
			}
			
			bool categoryList = false;
			*functionArguments = *functionArguments + generateCodePluralReferenceText(currentItem, progLang, categoryList, "");
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
			#ifdef NLC_FUNCTIONS_SUPPORT_PLURAL_SUBJECTS
			categoryList = true;
			#endif
			*functionArguments = *functionArguments + generateCodePluralReferenceText(currentItem, progLang, categoryList, NLC_ITEM_TYPE_SUBJECTCATEGORY_VAR_APPENDITION);
			#else
			*functionArguments = *functionArguments + generateCodeSingularReferenceText(currentItem, progLang);
			#endif
			
			#ifdef NLC_NONOO_DISABLE_CLASS_HEIRACHY
			if(*functionDeclarationOwnerName == "")
			{
				*functionDeclarationOwnerName = currentItem->name;	
			}
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
			*functionArguments = *functionArguments + generateCodePluralReferenceText(currentItem, progLang, categoryList, "");
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
			#ifdef NLC_FUNCTIONS_SUPPORT_PLURAL_OBJECTS
			categoryList = true;
			#endif
			*functionArguments = *functionArguments + generateCodePluralReferenceText(currentItem, progLang, categoryList, NLC_ITEM_TYPE_OBJECTCATEGORY_VAR_APPENDITION);
			#else
			*functionArguments = *functionArguments + generateCodeSingularReferenceText(currentItem, progLang);
			#endif
			
			#ifdef NLC_NONOO_DISABLE_CLASS_HEIRACHY
			if(*functionDeclarationObjectName == "")
			{
				*functionDeclarationObjectName = currentItem->name;	
			}
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


string generateCodePluralReferenceText(NLCitem* functionArgumentItem, int progLang, bool categoryList, string categoryVarAppendName)
{
	string codePropertyTypeText = "";
	#ifdef NLC_ACTION_CATEGORY_LISTS_USE_AS_FUNCTION_EXECUTION_ARGUMENTS
	if(categoryList)
	{
		codePropertyTypeText = generateGenericListName(functionArgumentItem->instanceName, categoryVarAppendName);
	}
	else
	{
	#endif
		codePropertyTypeText = generateEntityListName(functionArgumentItem);
	#ifdef NLC_ACTION_CATEGORY_LISTS_USE_AS_FUNCTION_EXECUTION_ARGUMENTS
	}
	#endif
	
	#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_ENABLE_TYPE_CASTING
	#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
	if(functionArgumentItem->functionArgumentPassCastRequired)
	{	
		#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
		cout << "generateCodePluralReferenceText{}: functionArgumentItem->functionArgumentPassCastRequired" << endl;
		#endif
		codePropertyTypeText = printCodeBlockCastVectorExecuteFunction(functionArgumentItem, progLang, categoryList);
	}
	#endif
	#endif

	return codePropertyTypeText;
}

string generateCodeSingularReferenceText(NLCitem* functionArgumentItem, int progLang)
{
	string codePropertyTypeText = functionArgumentItem->instanceName;
	#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_ENABLE_TYPE_CASTING
	#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
	if(functionArgumentItem->functionArgumentPassCastRequired)
	{
		#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
		cout << "generateCodeSingularReferenceText{}: functionArgumentItem->functionArgumentPassCastRequired" << endl;
		#endif
		codePropertyTypeText = generateDynamicCastOfEntity(functionArgumentItem->instanceName, functionArgumentItem->functionArgumentPassCastClassName, progLang); 	//dynamic_cast<parentClass*>(childClassInstance);
	}
	#endif
	#endif
	return codePropertyTypeText;
}

#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS
string printCodeBlockCastVectorExecuteFunction(NLCitem* functionArgumentItem, int progLang, bool categoryList)
{
	//see NLC_CODEBLOCK_TYPE_CAST_VECTOR_EXECUTE_FUNCTION
	
	string codeBlockTextTemplateDefinition = progLangTemplateUsePart1[progLang] + functionArgumentItem->className + progLangTemplateUseClassSeparator[progLang] + functionArgumentItem->functionArgumentPassCastClassName + progLangTemplateUsePart2[progLang] + STRING_SPACE; 	//<param1class, param2class>
	string codeBlockExecuteFunctionText = "";
	#ifdef NLC_ACTION_CATEGORY_LISTS_USE_AS_FUNCTION_EXECUTION_ARGUMENTS
	if(categoryList)
	{
		//codeBlockExecuteFunctionText = string(NLC_CAST_VECTOR_FUNCTION_NAME) + codeBlockTextTemplateDefinition + progLangOpenParameterSpace[progLang] + generateGenericListName(functionArgumentItem->instanceName, NLC_ITEM_TYPE_ACTIONCATEGORY_VAR_APPENDITION) + progLangCloseParameterSpace[progLang];	//castVector<param1class, param2class> (param1CategoryList)				
		codeBlockExecuteFunctionText = progLangPointer[progLang] + progLangOpenParameterSpace[progLang] + string(NLC_CAST_VECTOR_FUNCTION_NAME) + codeBlockTextTemplateDefinition + progLangOpenParameterSpace[progLang] + generateGenericListName(functionArgumentItem->instanceName, NLC_ITEM_TYPE_ACTIONCATEGORY_VAR_APPENDITION) + progLangCloseParameterSpace[progLang] + progLangCloseParameterSpace[progLang];	//*(castVector<param1class, param2class> (param1CategoryList))				
	}
	else
	{
	#endif
		//codeBlockExecuteFunctionText = string(NLC_CAST_VECTOR_FUNCTION_NAME) + codeBlockTextTemplateDefinition + progLangOpenParameterSpace[progLang] + generateEntityListName(functionArgumentItem) + progLangCloseParameterSpace[progLang];	//castVector<param1class, param2class> (param1InstanceList)
		codeBlockExecuteFunctionText = progLangPointer[progLang] + progLangOpenParameterSpace[progLang] + string(NLC_CAST_VECTOR_FUNCTION_NAME) + codeBlockTextTemplateDefinition + progLangOpenParameterSpace[progLang] + generateEntityListName(functionArgumentItem) + progLangCloseParameterSpace[progLang] + progLangCloseParameterSpace[progLang];	//*(castVector<param1class, param2class> (param1InstanceList))			
	#ifdef NLC_ACTION_CATEGORY_LISTS_USE_AS_FUNCTION_EXECUTION_ARGUMENTS	
	}
	#endif
	
	return codeBlockExecuteFunctionText;
}
#endif
		
#ifdef NLC_INTERPRET_ACTION_PROPERTIES_AND_CONDITIONS_AS_FUNCTION_ARGUMENTS
string generateCodeConditionPairReferenceText(NLCitem* functionArgumentConditionItem, int progLang)
{
	//do: add dynamic_cast<functionArgumentPassCastClassName> if functionArgumentPassCastClassName != ""
	string codeConditionPairTypeText = generateCodeConditionPairTextWithContext(functionArgumentConditionItem->name, functionArgumentConditionItem->className, functionArgumentConditionItem->instanceName, functionArgumentConditionItem->className2, functionArgumentConditionItem->instanceName2, &(functionArgumentConditionItem->context), progLang);
	return codeConditionPairTypeText;
}
#endif


#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS
void generateLocalFunctionArgumentsBasedOnImplicitDeclarationsString(vector<NLCitem*>* parameters, string* functionArguments, int progLang)
{
	for(vector<NLCitem*>::iterator parametersIterator = parameters->begin(); parametersIterator < parameters->end(); parametersIterator++)
	{
		NLCitem* currentItem = *parametersIterator;
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
void generateFunctionArgumentsBasedOnActionAndActionObjectVars(vector<NLCitem*>* parameters, string* functionArguments, int progLang, string* functionDeclarationOwnerName, string* functionDeclarationObjectName)
{
	for(vector<NLCitem*>::iterator parametersIterator = parameters->begin(); parametersIterator < parameters->end(); parametersIterator++)
	{
		NLCitem* currentItem = *parametersIterator;
		#ifdef NLC_DEBUG
		//cout << "generateFunctionArgumentsBasedOnActionAndActionObjectVars{}:" << endl;
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
			*functionArguments = *functionArguments + generateCodeEntityDefinitionText(currentItem, progLang);
			#endif
			#ifdef NLC_NONOO_DISABLE_CLASS_HEIRACHY
			*functionDeclarationOwnerName = currentItem->name;
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
			*functionArguments = *functionArguments + generateCodeEntityDefinitionText(currentItem, progLang);
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
			*functionArguments = *functionArguments + generateCodeEntityDefinitionText(currentItem, progLang);
			#endif	
			#ifdef NLC_NONOO_DISABLE_CLASS_HEIRACHY
			*functionDeclarationObjectName = currentItem->name;
			#endif		
		}

	}
}
#endif





string generateFunctionOwnerContext(vector<NLCitem*>* parameters, int progLang)
{
	bool foundFunctionOwner = false;
	string functionOwnerContext = "";
	#ifdef NLC_SUPPORT_INPUT_FILE_LISTS
	for(vector<NLCitem*>::iterator parametersIterator = parameters->begin(); parametersIterator < parameters->end(); parametersIterator++)
	{
		NLCitem* currentItem = *parametersIterator;
		if(currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION_OWNER)
		{
			functionOwnerContext = progLangClassMemberFunctionTypeDefault[progLang] + currentItem->className + progLangFunctionOwnerClassDelimiter[progLang];
			foundFunctionOwner = true;
		}
	}
	#endif
	if(!foundFunctionOwner)
	{
		functionOwnerContext = progLangClassMemberFunctionTypeDefault[progLang];
	}
	return functionOwnerContext;
}

#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS_ADVANCED
string generateLogicalConjunctionOfBoolsText(vector<NLCitem*>* parameters, int progLang)
{
	string logicalConjunctionOfBoolsText = "";
	for(vector<NLCitem*>::iterator parametersIterator = parameters->begin(); parametersIterator < parameters->end(); parametersIterator++)
	{
		NLCitem* currentItem = *parametersIterator;
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

