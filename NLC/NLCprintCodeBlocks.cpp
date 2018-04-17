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
 * File Name: NLCprintCodeBlocks.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2017 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler
 * Project Version: 2e2a 13-December-2017
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/


#include "NLCprintCodeBlocks.hpp"

bool NLCprintCodeBlocksClass::printCodeBlocks(NLCcodeblock* firstCodeBlockInLevel, vector<NLCclassDefinition*>* classDefinitionList, int progLang, string* code, const int level)
{
	bool result = true;

	string printedCodeBlocksSourceText = "";
	#ifdef NLC_LIBRARY_GENERATE_INDIVIDUAL_FILES_ADD_CLASS_FUNCTIONS_TO_CLASS_DEFINITIONS
	string printedClassDefinitionSourceFileName = "";
	#endif
	#ifdef NLC_PREDEFINED_FUNCTION_NAME_FOR_NATURAL_LANGUAGE_CODE_WITHOUT_FUNCTION_SPECIFIED_EXECUTE_IN_MAIN
	string printedCodeBlocksSourceMainFunctionText = "";
	#endif

	NLCcodeblock* currentCodeBlockInLevel = firstCodeBlockInLevel;
	while(currentCodeBlockInLevel->next != NULL)
	{
		NLCitem* param1 = currentCodeBlockInLevel->parameters.at(0);
		string contextParam1 = NLCprintDefs.generateStringFromContextVector(&(param1->context), progLang);

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

			bool hasActionSubject = false;
			NLCitem* functionOwnerArgument = NULL;

			#ifndef NLC_NONOO_DISABLE_CLASS_HEIRACHY
			string functionOwnerNameWithReferenceDelimiter = "";
			if(NLCclassDefinitionClass.findFunctionArgument(&(currentCodeBlockInLevel->parameters), NLC_ITEM_TYPE_FUNCTION_EXECUTION_ARGUMENT_FUNCTION_OWNER, &functionOwnerArgument))
			{
				#ifdef NLC_FUNCTIONS_SUPPORT_PLURAL_SUBJECTS
				functionOwnerNameWithReferenceDelimiter = NLCprintDefs.generateExternalFunctionContext(functionOwnerArgument->name, progLang);
				#else
				functionOwnerNameWithReferenceDelimiter = functionOwnerArgument->instanceName + progLangObjectReferenceDelimiter[progLang];
				#endif
				hasActionSubject = true;
			}
			#endif

			NLCitem* functionArgument = NULL;
			string functionName = "";
			if(NLCclassDefinitionClass.findFunctionArgument(&(currentCodeBlockInLevel->parameters), NLC_ITEM_TYPE_FUNCTION_EXECUTION_ARGUMENT_FUNCTION, &functionArgument))
			{
				functionName = functionArgument->functionName;
			}

			string functionArguments = "";
			//#ifdef NLC_NONOO_DISABLE_CLASS_HEIRACHY
			string functionDeclarationOwnerName = "";
			string functionDeclarationObjectName = "";
			//#endif
			this->generateFunctionExecutionArgumentsWithActionNetworkIndexInheritanceString(classDefinitionList, &(currentCodeBlockInLevel->parameters), &functionArguments, progLang, &functionDeclarationOwnerName, &functionDeclarationObjectName);

			#ifdef NLC_NONOO_DISABLE_CLASS_HEIRACHY
			string codeBlockText = functionDeclarationOwnerName + functionArgument->name + functionDeclarationObjectName + NLC_FUNCTION_NAME_APPEND + progLangOpenParameterSpace[progLang] + functionArguments + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//context1.param1(context.param2); 	[param1 = function, context1 = subject, param2 = object]
			#else
			string codeBlockText = functionOwnerNameWithReferenceDelimiter + functionName + progLangOpenParameterSpace[progLang] + functionArguments + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//context1.param1(context.param2); 	[param1 = function, context1 = subject, param2 = object]
			#endif
			NLCprintDefs.printLine(codeBlockText, level, &printedCodeBlocksSourceText);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_NEW_FUNCTION)
		{

			NLCitem* functionArgument = NULL;
			string functionName = "";
			if(NLCclassDefinitionClass.findFunctionArgument(&(currentCodeBlockInLevel->parameters), NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION, &functionArgument))
			{
				functionName = functionArgument->functionName;
			}

			string functionArguments = "";
			#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS
			//#ifdef NLC_NONOO_DISABLE_CLASS_HEIRACHY
			string functionDeclarationOwnerName = "";
			string functionDeclarationObjectName = "";
			//#endif
			this->generateFunctionArgumentsBasedOnActionAndActionObjectVars(&(currentCodeBlockInLevel->parameters), &functionArguments, progLang, &functionDeclarationOwnerName, &functionDeclarationObjectName);
			#endif

			#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS
			this->generateLocalFunctionArgumentsBasedOnImplicitDeclarationsString(&(currentCodeBlockInLevel->parameters), &functionArguments, progLang);
			#endif

			#ifndef NLC_NONOO_DISABLE_CLASS_HEIRACHY
			string functionOwnerContext = this->generateFunctionOwnerContext(&(currentCodeBlockInLevel->parameters), progLang, &functionDeclarationOwnerName);
			#endif

			#ifdef NLC_NONOO_DISABLE_CLASS_HEIRACHY
			string codeBlockText = functionDeclarationOwnerName + functionArgument->name + functionDeclarationObjectName + NLC_FUNCTION_NAME_APPEND + progLangOpenParameterSpace[progLang] + functionArguments + progLangCloseParameterSpace[progLang];	//main(){
			#else
			string codeBlockText = functionOwnerContext + functionName + progLangOpenParameterSpace[progLang] + functionArguments + progLangCloseParameterSpace[progLang];	//main(){
			#endif
			NLCprintDefs.printLine(codeBlockText, level, &printedCodeBlocksSourceText);
			NLCprintDefs.printLine(progLangOpenBlock[progLang], level, &printedCodeBlocksSourceText);

			#ifdef NLC_LIBRARY_GENERATE_INDIVIDUAL_FILES_ADD_CLASS_FUNCTIONS_TO_CLASS_DEFINITIONS
			printedClassDefinitionSourceFileName = NLC_LIBRARY_GENERATE_INDIVIDUAL_FILES_NAME_PREPEND + functionDeclarationOwnerName + NLC_LIBRARY_GENERATE_INDIVIDUAL_FILES_EXTENSION_CPP;		//eg NLCgeneratedmoveClass.cpp
			#endif

			#ifdef NLC_PREDEFINED_FUNCTION_NAME_FOR_NATURAL_LANGUAGE_CODE_WITHOUT_FUNCTION_SPECIFIED_EXECUTE_IN_MAIN
			printedCodeBlocksSourceMainFunctionText = this->generateMainFunctionText(&(currentCodeBlockInLevel->parameters), progLang);
			#endif
		}
		#ifdef NLC_RECORD_ACTION_HISTORY
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_RECORD_HISTORY_ACTION_SUBJECT)
		{
			NLCitem* functionArgument = NULL;
			string functionName = "";
			if(NLCclassDefinitionClass.findFunctionArgument(&(currentCodeBlockInLevel->parameters), NLC_ITEM_TYPE_FUNCTION_EXECUTION_ARGUMENT_FUNCTION, &functionArgument))
			{
				functionName = functionArgument->functionName;
			}

			NLCitem* functionOwnerArgument = NULL;
			string functionOwnerName = "";
			if(NLCclassDefinitionClass.findFunctionArgument(&(currentCodeBlockInLevel->parameters), NLC_ITEM_TYPE_FUNCTION_EXECUTION_ARGUMENT_FUNCTION_OWNER, &functionOwnerArgument))
			{
				functionOwnerName = functionOwnerArgument->instanceName;
			}

			NLCprintCodeBlocksFunctions.generateCodeAddActionSubject(functionArgument, functionOwnerArgument, progLang, &printedCodeBlocksSourceText, level);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_RECORD_HISTORY_ACTION_OBJECT)
		{
			NLCitem* functionArgument = NULL;
			string functionName = "";
			if(NLCclassDefinitionClass.findFunctionArgument(&(currentCodeBlockInLevel->parameters), NLC_ITEM_TYPE_FUNCTION_EXECUTION_ARGUMENT_FUNCTION, &functionArgument))
			{
				functionName = functionArgument->functionName;
			}

			NLCitem* functionObjectArgument = NULL;
			string functionObjectName = "";
			if(NLCclassDefinitionClass.findFunctionArgument(&(currentCodeBlockInLevel->parameters), NLC_ITEM_TYPE_FUNCTION_EXECUTION_ARGUMENT_FUNCTION_OBJECT, &functionObjectArgument))
			{
				functionObjectName = functionObjectArgument->instanceName;
			}

			NLCprintCodeBlocksFunctions.generateCodeAddActionObject(functionArgument, functionObjectArgument, progLang, &printedCodeBlocksSourceText, level);
		}
		#endif
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_ADD_NEW_PROPERTY)
		{
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			string codeBlockTextCreate = NLCprintDefs.generateCodeNewEntity(param2, progLang);
			NLCprintDefs.printLine(codeBlockTextCreate, level, &printedCodeBlocksSourceText);
			NLCprintCodeBlocksFunctions.generateCodeAddProperty(param1, param2, progLang, &printedCodeBlocksSourceText, level);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_ADD_NEW_ENTITY_TO_LOCAL_LIST)
		{
			NLCprintCodeBlocksFunctions.generateCodeAddNewEntityToLocalList(param1, progLang, &printedCodeBlocksSourceText, level);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_ADD_NEW_CONDITION)
		{
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			NLCitem* param3 = currentCodeBlockInLevel->parameters.at(2);
			string codeBlockTextCreate = NLCprintDefs.generateCodeNewEntity(param3, progLang);
			NLCprintDefs.printLine(codeBlockTextCreate, level, &printedCodeBlocksSourceText);

			NLCprintCodeBlocksFunctions.generateCodeAddCondition(param1, param2, param3, progLang, &printedCodeBlocksSourceText, level, false);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_ADD_PROPERTY)
		{
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			NLCprintCodeBlocksFunctions.generateCodeAddProperty(param1, param2, progLang, &printedCodeBlocksSourceText, level);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_LOCAL_LIST)
		{
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);

			NLCprintCodeBlocksFunctions.generateCodeAddEntityToLocalList(param1, param2, progLang, &printedCodeBlocksSourceText, level);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_ADD_CONDITION)
		{
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			NLCitem* param3 = currentCodeBlockInLevel->parameters.at(2);

			NLCprintCodeBlocksFunctions.generateCodeAddCondition(param1, param2, param3, progLang, &printedCodeBlocksSourceText, level, false);
		}
		#ifdef NLC_NORMALISE_TWOWAY_PREPOSITIONS_MARK_INVERSE_CONDITIONS
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_ADD_CONDITION_INVERSE)
		{
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			NLCitem* param3 = currentCodeBlockInLevel->parameters.at(2);

			NLCprintCodeBlocksFunctions.generateCodeAddCondition(param1, param2, param3, progLang, &printedCodeBlocksSourceText, level, true);
		}
		#endif
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_FOR_PROPERTY_LIST)
		{
			NLCprintCodeBlocksFunctions.generateCodeForPropertyList(param1, contextParam1, progLang, &printedCodeBlocksSourceText, level);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_FOR_LOCAL_LIST)
		{
			NLCprintCodeBlocksFunctions.generateCodeForLocalList(param1, progLang, &printedCodeBlocksSourceText, level);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_FOR_CONDITION_LIST)
		{
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			NLCprintCodeBlocksFunctions.generateCodeForConditionList(param1, param2, contextParam1, progLang, &printedCodeBlocksSourceText, level);
		}
		#ifdef NLC_NONOO
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_IF_PROPERTY_NAME)
		{
			string tempVarEntityNameCheckText = progLangIf[progLang] + NLCprintDefs.generateCodeEntityNameTestText(param1, progLang);	 //if(tempPropertyEntity->entityName == param1->name) {
			NLCprintDefs.printLine(tempVarEntityNameCheckText, (level), &printedCodeBlocksSourceText);
			NLCprintDefs.printLine(progLangOpenBlock[progLang], level, &printedCodeBlocksSourceText);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_IF_CONDITION_NAME)
		{
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			string tempVarEntityNameCheckText = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + NLCprintDefs.generateCodeEntityNameTestText(param1, progLang) + STRING_SPACE + progLangAnd[progLang] + STRING_SPACE + NLCprintDefs.generateCodeEntityNameTestText(param2, progLang) + progLangCloseParameterSpace[progLang];	//if((tempConditionEntity->entityName == param1->name) && (tempConditionObjectEntity->entityName == param2->name)) {
			NLCprintDefs.printLine(tempVarEntityNameCheckText, (level), &printedCodeBlocksSourceText);
			NLCprintDefs.printLine(progLangOpenBlock[progLang], level, &printedCodeBlocksSourceText);
		}
		#ifdef NLC_RECORD_ACTION_HISTORY
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_IF_ACTION_NAME)
		{
			string tempVarEntityNameCheckText = progLangIf[progLang] + NLCprintDefs.generateCodeEntityNameTestText(param1, progLang);	 //if(tempActionEntity->entityName == param1->name) {
			NLCprintDefs.printLine(tempVarEntityNameCheckText, (level), &printedCodeBlocksSourceText);
			NLCprintDefs.printLine(progLangOpenBlock[progLang], level, &printedCodeBlocksSourceText);
		}
		#endif
		#endif
		#ifdef NLC_RECORD_ACTION_HISTORY
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_FOR_ACTION_LIST)
		{
			string iterIndexString = SHAREDvars.convertIntToString(level);
			string codeBlockText = progLangFor[progLang] + progLangForIterPart1[progLang] + NLCprintDefs.generateCodeEntityListDefinitionTypeTextCompact(param1->className, progLang) + progLangForIterPart2a[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart2c[progLang] + contextParam1 + NLCprintDefs.generateActionListName(param1->className) + progLangForIterPart3a[progLang] + progLangForIterPart3b[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart3c[progLang] + contextParam1 + NLCprintDefs.generateActionListName(param1->className) + progLangForIterPart4a[progLang] + progLangForIterPart4b[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart4c[progLang];
			NLCprintDefs.printLine(codeBlockText, level, &printedCodeBlocksSourceText);
			NLCprintDefs.printLine(progLangOpenBlock[progLang], level, &printedCodeBlocksSourceText);
			string tempVarDeclarationText = NLCprintDefs.generateCodeEntityDefinitionText(param1, progLang) + progLangEquals[progLang] + NLCprintDefs.generateCodeIterReference(iterIndexString, progLang) + progLangEndLine[progLang];
			NLCprintDefs.printLine(tempVarDeclarationText, (level+1), &printedCodeBlocksSourceText);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_FOR_ACTION_INCOMING_LIST)
		{
			string iterIndexString = SHAREDvars.convertIntToString(level);
			string codeBlockText = progLangFor[progLang] + progLangForIterPart1[progLang] + NLCprintDefs.generateCodeEntityListDefinitionTypeTextCompact(param1->className, progLang) + progLangForIterPart2a[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart2c[progLang] + contextParam1 + NLCprintDefs.generateActionIncomingListName(param1->className) + progLangForIterPart3a[progLang] + progLangForIterPart3b[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart3c[progLang] + contextParam1 + NLCprintDefs.generateActionIncomingListName(param1->className) + progLangForIterPart4a[progLang] + progLangForIterPart4b[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart4c[progLang];
			NLCprintDefs.printLine(codeBlockText, level, &printedCodeBlocksSourceText);
			NLCprintDefs.printLine(progLangOpenBlock[progLang], level, &printedCodeBlocksSourceText);
			string tempVarDeclarationText = NLCprintDefs.generateCodeEntityDefinitionText(param1, progLang) + progLangEquals[progLang] + NLCprintDefs.generateCodeIterReference(iterIndexString, progLang) + progLangEndLine[progLang];	//OLD:  param1->className + NLC_ITEM_TYPE_TEMP_VAR_APPENDITION
			NLCprintDefs.printLine(tempVarDeclarationText, (level+1), &printedCodeBlocksSourceText);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_FOR_ACTION_OBJECT_LIST)
		{
			string iterIndexString = SHAREDvars.convertIntToString(level);
			string codeBlockText = progLangFor[progLang] + progLangForIterPart1[progLang] + NLCprintDefs.generateCodeEntityListDefinitionTypeTextCompact(param1->className, progLang) + progLangForIterPart2a[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart2c[progLang] + contextParam1 + NLCprintDefs.generateActionObjectListName(param1->className) + progLangForIterPart3a[progLang] + progLangForIterPart3b[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart3c[progLang] + contextParam1 + NLCprintDefs.generateActionObjectListName(param1->className) + progLangForIterPart4a[progLang] + progLangForIterPart4b[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart4c[progLang];
			NLCprintDefs.printLine(codeBlockText, level, &printedCodeBlocksSourceText);
			NLCprintDefs.printLine(progLangOpenBlock[progLang], level, &printedCodeBlocksSourceText);
			string tempVarDeclarationText = NLCprintDefs.generateCodeEntityDefinitionText(param1, progLang) + progLangEquals[progLang] + NLCprintDefs.generateCodeIterReference(iterIndexString, progLang) + progLangEndLine[progLang];	//OLD:  param1->className + NLC_ITEM_TYPE_TEMP_VAR_APPENDITION
			NLCprintDefs.printLine(tempVarDeclarationText, (level+1), &printedCodeBlocksSourceText);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_FOR_ACTION_SUBJECT_LIST)
		{
			string iterIndexString = SHAREDvars.convertIntToString(level);
			string codeBlockText = progLangFor[progLang] + progLangForIterPart1[progLang] + NLCprintDefs.generateCodeEntityListDefinitionTypeTextCompact(param1->className, progLang) + progLangForIterPart2a[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart2c[progLang] + contextParam1 + NLCprintDefs.generateActionSubjectListName(param1->className) + progLangForIterPart3a[progLang] + progLangForIterPart3b[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart3c[progLang] + contextParam1 + NLCprintDefs.generateActionSubjectListName(param1->className) + progLangForIterPart4a[progLang] + progLangForIterPart4b[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart4c[progLang];
			NLCprintDefs.printLine(codeBlockText, level, &printedCodeBlocksSourceText);
			NLCprintDefs.printLine(progLangOpenBlock[progLang], level, &printedCodeBlocksSourceText);
			string tempVarDeclarationText = NLCprintDefs.generateCodeEntityDefinitionText(param1, progLang) + progLangEquals[progLang] + NLCprintDefs.generateCodeIterReference(iterIndexString, progLang) + progLangEndLine[progLang];	//OLD:  param1->className + NLC_ITEM_TYPE_TEMP_VAR_APPENDITION
			NLCprintDefs.printLine(tempVarDeclarationText, (level+1), &printedCodeBlocksSourceText);
		}
		#endif
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_FOR_INTEGER)
		{
			string iterIndexString = SHAREDvars.convertIntToString(level);
			string indexName = progLangForIndex[progLang] + iterIndexString;
			string codeBlockText = progLangFor[progLang] + progLangForIndexPart1[progLang] + progLangInteger[progLang] + indexName + progLangForIndexPart2[progLang] + indexName + progLangForIndexPart3[progLang] + param1->name + progLangForIndexPart4[progLang] + indexName + progLangForIndexPart5[progLang];
			NLCprintDefs.printLine(codeBlockText, level, &printedCodeBlocksSourceText);
			NLCprintDefs.printLine(progLangOpenBlock[progLang], level, &printedCodeBlocksSourceText);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_DECLARE_AND_INITIALISE_VARIABLE)
		{
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);

			string codeBlockTextDeclareAndInitialiseVariable = NLCprintDefs.generateCodeEntityDefinitionText(param1, progLang) + progLangEquals[progLang] + param2->instanceName + progLangEndLine[progLang];
			NLCprintDefs.printLine(codeBlockTextDeclareAndInitialiseVariable, level, &printedCodeBlocksSourceText);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_DECLARE_NEW_VARIABLE)
		{
			string codeBlockTextDeclareNewVariable = NLCprintDefs.generateCodeNewEntity(param1, progLang);
			NLCprintDefs.printLine(codeBlockTextDeclareNewVariable, level, &printedCodeBlocksSourceText);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_DECLARE_NEW_LOCAL_LIST_VARIABLE)
		{
			string localListDeclarationText = NLCprintDefs.generateCodeEntityListDefinitionTypeText(param1->className, progLang) + NLCprintDefs.generateLocalListName(param1) + progLangEndLine[progLang];	//vector<param1Class*> param1instanceList;
			NLCprintDefs.printLine(localListDeclarationText, level, &printedCodeBlocksSourceText);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_ELSE)
		{
			string codeBlockText = progLangElse[progLang];
			NLCprintDefs.printLine(codeBlockText, level, &printedCodeBlocksSourceText);
			NLCprintDefs.printLine(progLangOpenBlock[progLang], level, &printedCodeBlocksSourceText);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_WHILE)
		{
			string codeBlockText = progLangWhile[progLang] + progLangOpenParameterSpace[progLang] + param1->name + progLangCloseParameterSpace[progLang];
			NLCprintDefs.printLine(codeBlockText, level, &printedCodeBlocksSourceText);
			NLCprintDefs.printLine(progLangOpenBlock[progLang], level, &printedCodeBlocksSourceText);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_DECLARE_NEW_BOOL_VARIABLE_INITIALISE_TRUE)
		{
			string codeBlockText = progLangBoolean[progLang] + param1->name + progLangEquals[progLang] + progLangTrue[progLang] + progLangEndLine[progLang];
			NLCprintDefs.printLine(codeBlockText, level, &printedCodeBlocksSourceText);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_DECLARE_NEW_BOOL_VARIABLE_INITIALISE_FALSE)
		{
			string codeBlockText = progLangBoolean[progLang] + param1->name + progLangEquals[progLang] + progLangFalse[progLang] + progLangEndLine[progLang];
			NLCprintDefs.printLine(codeBlockText, level, &printedCodeBlocksSourceText);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_SET_BOOL_VARIABLE_TRUE)
		{
			string codeBlockText = param1->name + progLangEquals[progLang] + progLangTrue[progLang] + progLangEndLine[progLang];
			NLCprintDefs.printLine(codeBlockText, level, &printedCodeBlocksSourceText);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_SET_BOOL_VARIABLE_FALSE)
		{
			string codeBlockText = param1->name + progLangEquals[progLang] + progLangFalse[progLang] + progLangEndLine[progLang];
			NLCprintDefs.printLine(codeBlockText, level, &printedCodeBlocksSourceText);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_CHECK_BOOL_VARIABLE_TRUE)
		{
			string tempVarCheckText = NLCprintDefs.generateCodeIfVarAequalsVarB(param1->name, progLangTrue[progLang], progLang);	 //if(param1 == param2) {
			NLCprintDefs.printLine(tempVarCheckText, level, &printedCodeBlocksSourceText);
			NLCprintDefs.printLine(progLangOpenBlock[progLang], level, &printedCodeBlocksSourceText);	//{
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_CHECK_BOOL_VARIABLE_FALSE)
		{
			string tempVarCheckText = NLCprintDefs.generateCodeIfVarAequalsVarB(param1->name, progLangFalse[progLang], progLang);	 //if(param1 == param2) {
			NLCprintDefs.printLine(tempVarCheckText, level, &printedCodeBlocksSourceText);
			NLCprintDefs.printLine(progLangOpenBlock[progLang], level, &printedCodeBlocksSourceText);	//{
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_DEBUG)
		{
			string codeBlockText = param1->name;
			NLCprintDefs.printLine(codeBlockText, level, &printedCodeBlocksSourceText);
		}
		#ifdef NLC_TRANSLATE_NEGATIVE_PROPERTIES_AND_CONDITIONS
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_REMOVE_PROPERTY)
		{
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			NLCprintCodeBlocksFunctions.generateCodeRemoveProperty(param1, param2, progLang, &printedCodeBlocksSourceText, level);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_REMOVE_PROPERTIES)
		{
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			NLCprintCodeBlocksFunctions.generateCodeRemoveProperties(param1, param2, progLang, &printedCodeBlocksSourceText, level);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_REMOVE_ENTITIES_FROM_LOCAL_LIST)
		{
			//not currently used

			string codeBlockText = NLCprintDefs.generateLocalListName(param1) + progLangObjectReferenceDelimiter2[progLang] + progLangRemoveProperties[progLang] + progLangEndLine[progLang];		//param1instanceList.clear();
			NLCprintDefs.printLine(codeBlockText, level, &printedCodeBlocksSourceText);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_REMOVE_CONDITION)
		{
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			NLCitem* param3 = currentCodeBlockInLevel->parameters.at(2);
			NLCprintCodeBlocksFunctions.generateCodeRemoveCondition(param1, param2, param3, progLang, &printedCodeBlocksSourceText, level);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_REMOVE_CONDITIONS)
		{
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			NLCitem* param3 = currentCodeBlockInLevel->parameters.at(2);
			NLCprintCodeBlocksFunctions.generateCodeRemoveConditions(param1, param2, param3, progLang, &printedCodeBlocksSourceText, level);
		}
		#endif
		#ifdef NLC_PREPROCESSOR_MATH
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_MATHTEXT_LINE)
		{
			string codeBlockText = param1->name + progLangEndLine[progLang];
			NLCprintDefs.printLine(codeBlockText, level, &printedCodeBlocksSourceText);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_MATHTEXT_WITH_LOGICAL_OPERATOR)
		{
			string codeBlockText = param1->name;
			NLCprintDefs.printLine(codeBlockText, level, &printedCodeBlocksSourceText);
			NLCprintDefs.printLine(progLangOpenBlock[progLang], level, &printedCodeBlocksSourceText);
		}
		#endif
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_DECLARE_NEW_INT_VARIABLE)
		{
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			string codeBlockText = progLangInteger[progLang] + param1->name + progLangEquals[progLang] + param2->name + progLangEndLine[progLang];
			NLCprintDefs.printLine(codeBlockText, level, &printedCodeBlocksSourceText);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_INCREMENT_INT_VARIABLE)
		{
			string codeBlockText = param1->name + progLangEquals[progLang] + param1->name + progLangMathPlus[progLang] + string("1") + progLangEndLine[progLang];
			NLCprintDefs.printLine(codeBlockText, level, &printedCodeBlocksSourceText);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_COMMENT_SINGLE_LINE)
		{
			string codeBlockText = progLangOpenSingleLineComment[progLang] + param1->name;
			NLCprintDefs.printLine(codeBlockText, level, &printedCodeBlocksSourceText);
		}
		#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_REASSIGN_ITER)
		{
			string iterIndexString = SHAREDvars.convertIntToString(level-1);
			string tempVarDeclarationText = param1->instanceName + progLangEquals[progLang] + NLCprintDefs.generateCodeIterReference(iterIndexString, progLang) + progLangEndLine[progLang];
			NLCprintDefs.printLine(tempVarDeclarationText, level, &printedCodeBlocksSourceText);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_DECLARE_NEW_GENERIC_LIST_VARIABLE)
		{
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			string genericListAppendName = param2->name;

			string localListDeclarationText = NLCprintDefs.generateCodeGenericListDefinitionText(param1, genericListAppendName, progLang) + progLangEndLine[progLang];	//vector<param1Class*> param1CategoryList;
			NLCprintDefs.printLine(localListDeclarationText, level, &printedCodeBlocksSourceText);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST)
		{
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			NLCitem* param3 = currentCodeBlockInLevel->parameters.at(2);
			string genericListAppendName = param3->name;

			string codeBlockText = NLCprintDefs.generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangObjectReferenceDelimiter2[progLang] + progLangAddEntityToList[progLang] + progLangOpenParameterSpace[progLang] + param2->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//param1CategoryList.push_back(param2);
			NLCprintDefs.printLine(codeBlockText, level, &printedCodeBlocksSourceText);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_FOR_GENERIC_LIST)
		{
			string iterIndexString = SHAREDvars.convertIntToString(level);
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			string genericListAppendName = param2->name;

			string codeBlockText = progLangFor[progLang] + progLangForIterPart1[progLang] + NLCprintDefs.generateCodeEntityListDefinitionTypeTextCompact(param1->className, progLang) + progLangForIterPart2a[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart2c[progLang] + NLCprintDefs.generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangForIterPart3a[progLang] + progLangForIterPart3b[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart3c[progLang] + NLCprintDefs.generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangForIterPart4a[progLang] + progLangForIterPart4b[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart4c[progLang];
			NLCprintDefs.printLine(codeBlockText, level, &printedCodeBlocksSourceText);
			NLCprintDefs.printLine(progLangOpenBlock[progLang], level, &printedCodeBlocksSourceText);
			string tempVarDeclarationText = NLCprintDefs.generateCodeEntityDefinitionText(param1, progLang) + progLangEquals[progLang] + NLCprintDefs.generateCodeIterReference(iterIndexString, progLang) + progLangEndLine[progLang];	//OLD:  param1->className + NLC_ITEM_TYPE_TEMP_VAR_APPENDITION
			NLCprintDefs.printLine(tempVarDeclarationText, (level+1), &printedCodeBlocksSourceText);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_IF_HAS_GENERIC_ENTITY)
		{
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			string genericListAppendName = param2->name;

			string codeBlockText = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + negativeModifierString + progLangOpenParameterSpace[progLang] + NLCprintDefs.generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangObjectReferenceDelimiter2[progLang] + progLangHasEntity[progLang] + progLangCloseParameterSpace[progLang] + progLangCloseParameterSpace[progLang];		//if(!(param1CategoryList.empty())){

			NLCprintDefs.printLine(codeBlockText, level, &printedCodeBlocksSourceText);
			NLCprintDefs.printLine(progLangOpenBlock[progLang], level, &printedCodeBlocksSourceText);
		}
		#ifdef NLC_CATEGORIES_TEST_PLURALITY
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_PRINT_WARNING)
		{
			string codeBlockText = progLangPrintTextOpen[progLang] + param1->name + progLangPrintTextClose[progLang] + progLangEndLine[progLang];	//cout << "warning" << endl;
			NLCprintDefs.printLine(codeBlockText, level, &printedCodeBlocksSourceText);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_IF_HAS_GREATER_THAN_NUM_GENERIC_ENTITY)
		{
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			string genericListAppendName = param2->name;

			NLCitem* param3 = currentCodeBlockInLevel->parameters.at(2);
			string valueString = param3->name;

			string codeBlockText = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + NLCprintDefs.generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangObjectReferenceDelimiter2[progLang] + progLangSizeOfList[progLang] + progLangGreaterThan[progLang] + valueString + progLangCloseParameterSpace[progLang];		//if(param1CategoryList.size() > X){

			NLCprintDefs.printLine(codeBlockText, level, &printedCodeBlocksSourceText);
			NLCprintDefs.printLine(progLangOpenBlock[progLang], level, &printedCodeBlocksSourceText);
		}
		#endif
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_GET_BACK_GENERIC_ENTITY_LIST)
		{
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			string genericListAppendName = param2->name;

			string tempVarDeclarationText = NLCprintDefs.generateCodeEntityDefinitionText(param1, progLang) + progLangEquals[progLang] + NLCprintDefs.generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangObjectReferenceDelimiter2[progLang] + progLangGetLast[progLang] + progLangEndLine[progLang];

			NLCprintDefs.printLine(tempVarDeclarationText, level, &printedCodeBlocksSourceText);
		}
		#ifdef NLC_ADVANCED_REFERENCING		
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST_CHECK_LAST_SENTENCE_REFERENCED_SINGULAR_EXECUTE_FUNCTION)
		{

			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			NLCitem* param3 = currentCodeBlockInLevel->parameters.at(2);

			NLCprintCodeBlocksFunctions.generateCodeAddToCategoryIfPassSingularDefiniteReferencingTestsExecuteFunction(param1, param2, param3, progLang, &printedCodeBlocksSourceText, level, false);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST_CHECK_LAST_SENTENCE_REFERENCED_SINGULAR_WITH_CAST_EXECUTE_FUNCTION)
		{

			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			NLCitem* param3 = currentCodeBlockInLevel->parameters.at(2);

			NLCprintCodeBlocksFunctions.generateCodeAddToCategoryIfPassSingularDefiniteReferencingTestsExecuteFunction(param1, param2, param3, progLang, &printedCodeBlocksSourceText, level, true);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST_CHECK_LAST_SENTENCE_REFERENCED_SINGULAR_NEW_FUNCTION)
		{

			NLCprintCodeBlocksFunctions.generateCodeAddToCategoryIfPassSingularDefiniteReferencingTestsNewFunction(progLang, &printedCodeBlocksSourceText, level);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_UPDATE_LAST_SENTENCE_REFERENCED)	//execute for all new/undeclared/indefinite entities and accessed category items
		{
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			string lastSentenceReferenced = param2->name;

			#ifdef NLC_ADVANCED_REFERENCING_MONITOR_CONTEXT
			string codeBlockText = param1->instanceName + progLangObjectReferenceDelimiter[progLang] + NLC_ADVANCED_REFERENCING_LAST_SENTENCE_REFERENCED_VARIABLE_NAME + progLangObjectReferenceDelimiter2[progLang] + progLangStackGetLast[progLang] + progLangEquals[progLang] + lastSentenceReferenced + progLangEndLine[progLang];		//param1->lastSentenceReferenced.top() = x;
			#else
			string codeBlockText = param1->instanceName + progLangObjectReferenceDelimiter[progLang] + NLC_ADVANCED_REFERENCING_LAST_SENTENCE_REFERENCED_VARIABLE_NAME + progLangEquals[progLang] + lastSentenceReferenced + progLangEndLine[progLang];		//param1->lastSentenceReferenced = x;
			#endif
			NLCprintDefs.printLine(codeBlockText, level, &printedCodeBlocksSourceText);
		}
		#endif
		#endif
		#ifdef NLC_PERFORM_PLURAL_DEFINITE_REFERENCING_TESTS
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST_CHECK_LAST_SENTENCE_REFERENCED_PLURAL_EXECUTE_FUNCTION)
		{

			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			NLCitem* param3 = currentCodeBlockInLevel->parameters.at(2);

			NLCprintCodeBlocksFunctions.generateCodeAddToCategoryIfPassPluralDefiniteReferencingTestsExecuteFunction(param1, param2, param3, progLang, &printedCodeBlocksSourceText, level, false);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST_CHECK_LAST_SENTENCE_REFERENCED_PLURAL_WITH_CAST_EXECUTE_FUNCTION)
		{

			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			NLCitem* param3 = currentCodeBlockInLevel->parameters.at(2);

			NLCprintCodeBlocksFunctions.generateCodeAddToCategoryIfPassPluralDefiniteReferencingTestsExecuteFunction(param1, param2, param3, progLang, &printedCodeBlocksSourceText, level, true);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST_CHECK_LAST_SENTENCE_REFERENCED_PLURAL_NEW_FUNCTION)
		{

			NLCprintCodeBlocksFunctions.generateCodeAddToCategoryIfPassPluralDefiniteReferencingTestsNewFunction(progLang, &printedCodeBlocksSourceText, level);
		}
		#endif
		#ifdef NLC_GENERATE_TYPE_LISTS
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_DECLARE_NEW_GENERIC_LIST_VARIABLE2)
		{
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			string genericListAppendName = param2->name;

			string localListDeclarationText = NLCprintDefs.generateCodeEntityListDefinitionTypeText2(param1->className, progLang) + CHAR_SPACE + NLCprintDefs.generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangEndLine[progLang];	//vector<vector<param1Class*>> param1instanceTypeList;
			NLCprintDefs.printLine(localListDeclarationText, level, &printedCodeBlocksSourceText);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_GENERIC_LIST2)
		{
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			NLCitem* param3 = currentCodeBlockInLevel->parameters.at(2);
			NLCitem* param4 = currentCodeBlockInLevel->parameters.at(3);
			string genericListAppendName = param3->name;
			string genericListAppendName2 = param4->name;

			string codeBlockText = NLCprintDefs.generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangObjectReferenceDelimiter2[progLang] + progLangAddEntityToList[progLang] + progLangOpenParameterSpace[progLang] + NLCprintDefs.generateReferenceText(NLCprintDefs.generateGenericListName(param2->instanceName, genericListAppendName2), progLang) + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//param1instanceTypeList.push_back(&param2);
			NLCprintDefs.printLine(codeBlockText, level, &printedCodeBlocksSourceText);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_FOR_GENERIC_LIST2)
		{
			string iterIndexString = SHAREDvars.convertIntToString(level);
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			string genericListAppendName = param2->name;

			string codeBlockText = progLangFor[progLang] + progLangForIterPart1[progLang] + NLCprintDefs.generateCodeEntityListDefinitionTypeText2(param1->className, progLang) + progLangForIterPart2a[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart2c[progLang] + NLCprintDefs.generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangForIterPart3a[progLang] + progLangForIterPart3b[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart3c[progLang] + NLCprintDefs.generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangForIterPart4a[progLang] + progLangForIterPart4b[progLang] + progLangForIterName[progLang] + iterIndexString + progLangForIterPart4c[progLang];
			NLCprintDefs.printLine(codeBlockText, level, &printedCodeBlocksSourceText);
			NLCprintDefs.printLine(progLangOpenBlock[progLang], level, &printedCodeBlocksSourceText);
			string tempVarDeclarationText = NLCprintDefs.generateReferenceTypeText(NLCprintDefs.generateCodeEntityListDefinitionTypeTextCompact(param1->className, progLang), progLang) + CHAR_SPACE + NLCprintDefs.generatePropertyListName(param1) + progLangEquals[progLang] + NLCprintDefs.generatePointerText(NLCprintDefs.generateCodeIterReference(iterIndexString, progLang), progLang) + progLangEndLine[progLang];
				//check use of NLCprintDefs.generatePropertyListName(); should really be generateTempListName()
			NLCprintDefs.printLine(tempVarDeclarationText, (level+1), &printedCodeBlocksSourceText);
		}
		#endif
		#ifdef NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_IF_HAS_GREATER_THAN_OR_EQUAL_TO_NUM_GENERIC_ENTITY)
		{
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			string genericListAppendName = param2->name;

			NLCitem* param3 = currentCodeBlockInLevel->parameters.at(2);
			string valueString = param3->name;

			string codeBlockText = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + NLCprintDefs.generateGenericListName(param1->genericObjectName, genericListAppendName) + progLangObjectReferenceDelimiter2[progLang] + progLangSizeOfList[progLang] + progLangGreaterThanOrEqualTo[progLang] + valueString + progLangCloseParameterSpace[progLang];		//if(param1CategoryList.size() > X){

			NLCprintDefs.printLine(codeBlockText, level, &printedCodeBlocksSourceText);
			NLCprintDefs.printLine(progLangOpenBlock[progLang], level, &printedCodeBlocksSourceText);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_TEST_INT_VARIABLE_GREATER_THAN_OR_EQUAL_TO_NUM)
		{

			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			string valueString = param2->name;

			string codeBlockText = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + param1->name + progLangGreaterThanOrEqualTo[progLang] + valueString + progLangCloseParameterSpace[progLang];		//if(variable > x){

			NLCprintDefs.printLine(codeBlockText, level, &printedCodeBlocksSourceText);
			NLCprintDefs.printLine(progLangOpenBlock[progLang], level, &printedCodeBlocksSourceText);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_TEST_INT_VARIABLE_EQUALS_LIST_SIZE)
		{

			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);

			NLCitem* param3 = currentCodeBlockInLevel->parameters.at(2);
			string genericListAppendName = param3->name;

			string codeBlockText = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + param1->name + progLangEqualsTest[progLang] + NLCprintDefs.generateGenericListName(param2->genericObjectName, genericListAppendName) + progLangObjectReferenceDelimiter2[progLang] + progLangSizeOfList[progLang] + progLangCloseParameterSpace[progLang];		//if(variable == param1CategoryList.size()){

			NLCprintDefs.printLine(codeBlockText, level, &printedCodeBlocksSourceText);
			NLCprintDefs.printLine(progLangOpenBlock[progLang], level, &printedCodeBlocksSourceText);
		}
		/*
		#ifdef NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY_CHILDREN_BASIC
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_IF_HAS_MORE_THAN_NUM_PROPERTY)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_IF_HAS_MORE_THAN_NUM_PROPERTY" << endl;
			#endif

			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			string valueString = param2->name;

			string codeBlockText = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + contextParam1 + NLCprintDefs.generatePropertyListName(param1) + progLangObjectReferenceDelimiter2[progLang] + progLangSizeOfList[progLang] + progLangGreaterThan[progLang] + valueString + progLangCloseParameterSpace[progLang];		//if(context1->param1PropertyList.size() > x){

			NLCprintDefs.printLine(codeBlockText, level, &printedCodeBlocksSourceText);
			NLCprintDefs.printLine(progLangOpenBlock[progLang], level, &printedCodeBlocksSourceText);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_IF_HAS_MORE_THAN_NUM_CONDITION)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_IF_HAS_MORE_THAN_NUM_CONDITION" << endl;
			#endif

			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			NLCitem* param3 = currentCodeBlockInLevel->parameters.at(2);
			string valueString = param3->name;

			string codeBlockText = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + contextParam1 + NLCprintDefs.generateConditionListName(param1->className, param2->className) + progLangObjectReferenceDelimiter2[progLang] + progLangSizeOfList[progLang] + progLangGreaterThan[progLang] + valueString + progLangCloseParameterSpace[progLang];		//if(context1->param1param2ConditionList.size() > x){

			NLCprintDefs.printLine(codeBlockText, level, &printedCodeBlocksSourceText);
			NLCprintDefs.printLine(progLangOpenBlock[progLang], level, &printedCodeBlocksSourceText);
		}
		#endif
		*/
		#endif
		#ifdef NLC_ADVANCED_REFERENCING_MONITOR_CONTEXT
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_DECLARE_CONTEXT_LIST)
		{
			string contextLevelString = param1->name;

			string  genericEntityClassName = NLCitemClass.generateClassName(NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE);
			string contextListName = string(NLC_ITEM_TYPE_REFERENCECONTEXTLEVELLIST_VAR_APPENDITION) + contextLevelString;
			string contextListDeclarationText = NLCprintDefs.generateCodeEntityListDefinitionTypeText(genericEntityClassName, progLang) + contextListName + progLangEndLine[progLang];	//vector<genericEntityClass*> contextListX;
			NLCprintDefs.printLine(contextListDeclarationText, level, &printedCodeBlocksSourceText);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_CONTEXT_LIST_NEW_FUNCTION)
		{//finish coding this

			NLCprintCodeBlocksFunctions.generateCodeAddEntityToReferenceContextListNewFunction(progLang, &printedCodeBlocksSourceText, level);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_ADD_ENTITY_TO_CONTEXT_LIST_EXECUTE_FUNCTION)
		{

			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			NLCitem* param3 = currentCodeBlockInLevel->parameters.at(2);

			NLCprintCodeBlocksFunctions.generateCodeAddEntityToReferenceContextListExecuteFunction(param1, param2, param3, progLang, &printedCodeBlocksSourceText, level);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_CLEAR_CONTEXT_LIST_NEW_FUNCTION)
		{

			NLCprintCodeBlocksFunctions.generateCodeClearReferenceContextListNewFunction(progLang, &printedCodeBlocksSourceText, level);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_CLEAR_CONTEXT_LIST_EXECUTE_FUNCTION)
		{

			NLCprintCodeBlocksFunctions.generateCodeClearReferenceContextListExecuteFunction(param1, progLang, &printedCodeBlocksSourceText, level);
		}
		#endif
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_CONTEXT_BLOCK)
		{
			NLCprintDefs.printLine(progLangOpenBlock[progLang], level, &printedCodeBlocksSourceText);
		}
		#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_CAST_VECTOR_EXECUTE_FUNCTION)
		{//not used - see printCodeBlockCastVectorExecuteFunction()

			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);	//functionArgumentPassCast

			NLCprintCodeBlocksFunctions.generateCodeCastVectorExecuteFunction(param1, param2, progLang, &printedCodeBlocksSourceText, level);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_CAST_VECTOR_NEW_FUNCTION)
		{

			NLCprintCodeBlocksFunctions.generateCodeCastVectorNewFunction(progLang, &printedCodeBlocksSourceText, level);
		}
		#endif
		#ifdef NLC_ADVANCED_REFERENCING_SUPPORT_ALIASES
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_ADD_ALIAS_TO_ENTITY_ALIAS_LIST)
		{
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			string aliasName = param2->name;

			string codeBlockTextAddAliasToEntityAliasList = param1->instanceName + progLangObjectReferenceDelimiter[progLang] + NLC_ITEM_TYPE_ALIASLIST_VAR_APPENDITION + progLangObjectReferenceDelimiter2[progLang] + progLangAddProperty[progLang] + progLangOpenParameterSpace[progLang] + progLangStringOpenClose[progLang] + aliasName + progLangStringOpenClose[progLang] + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//entity->aliasList.push_back("aliasName");
			NLCprintDefs.printLine(codeBlockTextAddAliasToEntityAliasList, level, &printedCodeBlocksSourceText);

			/*
			string codeBlockTextAddEntityToAliasList = generateEntityStringMapListName(NLC_ADVANCED_REFERENCING_SUPPORT_ALIASES_ALIAS_LIST_NAME_START, NLC_ITEM_TYPE_ALIASLIST_VAR_APPENDITION) + progLangObjectReferenceDelimiter2[progLang] + progLangAddCondition[progLang] + progLangOpenParameterSpace[progLang] + generateEntityStringPairTexts(param1->name, genericEntityClassName, NLCprintDefs.generateStaticCastOfEntity(param2->instanceName, genericEntityClassName, progLang), progLang) + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//AliasList.insert(pair<string, param2className*>(param1, static_cast<NLCgenericEntityClass*>param2));
			*/
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_FIND_ALIAS_AND_ADD_TO_CATEGORY_LIST_NEW_FUNCTION)
		{

			NLCprintCodeBlocksFunctions.generateCodeFindAliasAndAddToCategoryListNewFunction(progLang, &printedCodeBlocksSourceText, level);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_FIND_ALIAS_AND_ADD_TO_CATEGORY_LIST_EXECUTE_FUNCTION)
		{

			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			NLCitem* param3 = currentCodeBlockInLevel->parameters.at(2);

			NLCprintCodeBlocksFunctions.generateCodeFindAliasAndAddToCategoryListExecuteFunction(param1, param2, param3, progLang, &printedCodeBlocksSourceText, level);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_FIND_ALIAS_NEW_FUNCTION)
		{

			NLCprintCodeBlocksFunctions.generateCodeFindAliasNewFunction(progLang, &printedCodeBlocksSourceText, level);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_FIND_ALIAS_EXECUTE_FUNCTION)
		{

			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);

			NLCprintCodeBlocksFunctions.generateCodeFindAliasExecuteFunction(param1, param2, progLang, &printedCodeBlocksSourceText, level);
		}
		#endif
		#ifdef NLC_REFERENCING_OBJECTS_IN_PLURAL_LIST_BY_NUMBER
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_IN_PROPERTY_LIST)
		{
			string iterIndexString = SHAREDvars.convertIntToString(level);
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			string listIndexString = param2->name;
			string codeBlockText = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + listIndexString + progLangLessThanOrEqualTo[progLang] + contextParam1 + NLCprintDefs.generatePropertyListName(param1) + progLangObjectReferenceDelimiter2[progLang] + progLangSizeOfList[progLang] + progLangCloseParameterSpace[progLang];		//if(X <= param1PropertyList.size()){
			NLCprintDefs.printLine(codeBlockText, level, &printedCodeBlocksSourceText);
			NLCprintDefs.printLine(progLangOpenBlock[progLang], level, &printedCodeBlocksSourceText);	//{
			string tempVarDeclarationText = NLCprintDefs.generateCodeEntityDefinitionText(param1, progLang) + progLangEquals[progLang] + contextParam1 + NLCprintDefs.generatePropertyListName(param1) + progLangGetAtPositionPart1[progLang] + listIndexString + progLangGetAtPositionPart2[progLang] + progLangEndLine[progLang];		//param1* tempVar = param1PropertyList.at(listIndex-1);
			NLCprintDefs.printLine(tempVarDeclarationText, (level+1), &printedCodeBlocksSourceText);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_IN_LOCAL_LIST)
		{
			string iterIndexString = SHAREDvars.convertIntToString(level);
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			string listIndexString = param2->name;
			string codeBlockText = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + listIndexString + progLangLessThanOrEqualTo[progLang] + NLCprintDefs.generateLocalListName(param1) + progLangObjectReferenceDelimiter2[progLang] + progLangSizeOfList[progLang] + progLangCloseParameterSpace[progLang];		//if(X <= param1LocalList.size()){
			NLCprintDefs.printLine(codeBlockText, level, &printedCodeBlocksSourceText);
			NLCprintDefs.printLine(progLangOpenBlock[progLang], level, &printedCodeBlocksSourceText);	//{
			string tempVarDeclarationText = NLCprintDefs.generateCodeEntityDefinitionText(param1, progLang) + progLangEquals[progLang] + NLCprintDefs.generateLocalListName(param1) + progLangGetAtPositionPart1[progLang] + listIndexString + progLangGetAtPositionPart2[progLang] + progLangEndLine[progLang];		//param1* tempVar = param1LocalList.at(listIndex-1);
			NLCprintDefs.printLine(tempVarDeclarationText, (level+1), &printedCodeBlocksSourceText);
		}
		#endif
		#ifdef NLC_REDEFINITIONS
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_CHECK_PARENT_CLASS_NAME_EXECUTE_FUNCTION1)
		{
			string iterIndexString = SHAREDvars.convertIntToString(level);
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);

			NLCprintCodeBlocksFunctions.generateCodeCheckParentClassNameExecuteFunction1(param1, param2, progLang, &printedCodeBlocksSourceText, level);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_CHECK_PARENT_CLASS_NAME_EXECUTE_FUNCTION2)
		{
			string iterIndexString = SHAREDvars.convertIntToString(level);
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);

			NLCprintCodeBlocksFunctions.generateCodeCheckParentClassNameExecuteFunction2(param1, param2, progLang, &printedCodeBlocksSourceText, level);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_CHECK_PARENT_CLASS_NAME_NEW_FUNCTION)
		{

			NLCprintCodeBlocksFunctions.generateCodeCheckParentClassNameNewFunction(progLang, &printedCodeBlocksSourceText, level);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_CONVERT_PARENT_TO_CHILD_CLASS)
		{
			string iterIndexString = SHAREDvars.convertIntToString(level);
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);

			string codeBlockConvertParentToChildClassText = NLCprintDefs.generateCodeEntityDefinitionText(param2, progLang) + progLangEquals[progLang] + NLCprintDefs.generateStaticCastOfEntity(param1->instanceName, param2->className, progLang) + progLangEndLine[progLang];	//param2class* param2instance = static_cast<param2class*>(param1instance);
			NLCprintDefs.printLine(codeBlockConvertParentToChildClassText, level, &printedCodeBlocksSourceText);
			string codeBlockRenameChildClassObjectToChildClassText = NLCprintDefs.generateEntityName(param2) + progLangObjectReferenceDelimiter[progLang] + progLangClassNameVariableName[progLang] + progLangEquals[progLang] + progLangStringOpenClose[progLang] + param2->name + progLangStringOpenClose[progLang] + progLangEndLine[progLang];	//param2instance->name = "param2";	//added 1n6b
			NLCprintDefs.printLine(codeBlockRenameChildClassObjectToChildClassText, level, &printedCodeBlocksSourceText);
		}
		#endif
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_DECLARE_TEMP_VARIABLE)
		{
			string tempEntityDeclarationText = NLCprintDefs.generateCodeEntityDeclarationSetToNull(param1, progLang);	//param1Class* param1 = NULL;
			NLCprintDefs.printLine(tempEntityDeclarationText, level, &printedCodeBlocksSourceText);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_SET_TEMP_VARIABLE)
		{
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			string tempEntitySetText = NLCprintDefs.generateCodeSetEntity(param1, param2, progLang);	//param1 = param2;
			NLCprintDefs.printLine(tempEntitySetText, level, &printedCodeBlocksSourceText);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_DECLARE_TEMP_VARIABLE_AND_SET_TO_ENTITY)
		{
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			string tempEntityDeclarationText = NLCprintDefs.generateCodeEntityDeclarationSetToEntity(param1, param2, progLang);	//param1Class* param1 = param2;
			NLCprintDefs.printLine(tempEntityDeclarationText, level, &printedCodeBlocksSourceText);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_IF_TEMP_VARIABLE_EQUALS_ENTITY)
		{
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			string tempVarCheckText = NLCprintDefs.generateCodeIfVarAequalsVarB(NLCprintDefs.generateEntityName(param1), NLCprintDefs.generateEntityName(param2), progLang);	 //if(param1 == param2) {
			NLCprintDefs.printLine(tempVarCheckText, level, &printedCodeBlocksSourceText);
			NLCprintDefs.printLine(progLangOpenBlock[progLang], level, &printedCodeBlocksSourceText);	//{
		}
		#ifdef NLC_NON_LIBRARY_FUNCTIONS_EXTENDED
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_ADD_PROPERTY_NEW_FUNCTION)
		{
			NLCprintCodeBlocksFunctions.generateCodeAddPropertyNewFunction(progLang, &printedCodeBlocksSourceText, level);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_ADD_CONDITION_NEW_FUNCTION)
		{
			NLCprintCodeBlocksFunctions.generateCodeAddConditionNewFunction(progLang, &printedCodeBlocksSourceText, level, false);
		}
		#ifdef NLC_NORMALISE_TWOWAY_PREPOSITIONS_MARK_INVERSE_CONDITIONS
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_ADD_CONDITION_INVERSE_NEW_FUNCTION)
		{
			NLCprintCodeBlocksFunctions.generateCodeAddConditionNewFunction(progLang, &printedCodeBlocksSourceText, level, true);
		}
		#endif
		#endif
		#ifdef NLC_MATH_OBJECTS
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_TEST_MATH_OBJECT_NUMERICAL_VALUE)
		{
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			string testEntityMathNumericalValueText = NLCprintDefs.generateCodeTestEntityMathObjectNumericalValueText(param1, param2, progLang);	//if(param1->mathObjectNumericalValue == param2)
			NLCprintDefs.printLine(testEntityMathNumericalValueText, level, &printedCodeBlocksSourceText);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_SET_MATH_OBJECT_NUMERICAL_VALUE)
		{
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			string setMathValueText = NLCprintDefs.generateCodeEntityMathObjectNumericalValueText(param1, progLang) + progLangEquals[progLang] + param2->name + progLangEndLine[progLang];	 //param1->mathObjectNumericalValue = param2;
			NLCprintDefs.printLine(setMathValueText, level, &printedCodeBlocksSourceText);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_DECLARE_NEW_DECIMAL_POINTER_VARIABLE)
		{
			string declareNewDecimalPointerVariableText = NLCprintDefs.generateCodeDeclareNewDecimalPointerVariableText(param1, progLang);	 //double* param1 = NULL;
			NLCprintDefs.printLine(declareNewDecimalPointerVariableText, level, &printedCodeBlocksSourceText);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_SET_DECIMAL_POINTER_TO_ENTITY_MATH_OBJECT_NUMERICAL_VALUE)
		{
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			string setDecimalPointerToEntityMathObjectNumericalValueText = NLCprintDefs.generateCodeSetDecimalPointerToEntityMathObjectNumericalValueText(param1, param2, progLang);	 //param1 = &(param2->mathObjectNumericalValue);
			NLCprintDefs.printLine(setDecimalPointerToEntityMathObjectNumericalValueText, level, &printedCodeBlocksSourceText);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_SET_MATH_OBJECT_TYPE_AS_NUMERICAL)
		{
			string setMathTypeText = NLCprintDefs.generateCodeEntityMathObjectTypeText(param1, progLang) + progLangEquals[progLang] + NLC_MATH_OBJECTS_VARIABLE_TYPE_NUMERICAL_DEFNAME + progLangEndLine[progLang];	 //param1->mathObjectType = NLC_MATH_OBJECTS_VARIABLE_TYPE_NUMERICAL;
			NLCprintDefs.printLine(setMathTypeText, level, &printedCodeBlocksSourceText);
		}
		#ifdef NLC_MATH_OBJECTS_ADVANCED
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_DECLARE_NEW_GENERIC_ENTITY_POINTER_VARIABLE)
		{
			string declareNewGenericPointerVariableText = NLCprintDefs.generateCodeDeclareNewGenericEntityPointerVariableText(param1, progLang);	 //NLCgenericEntityClass* param1 = NULL;
			NLCprintDefs.printLine(declareNewGenericPointerVariableText, level, &printedCodeBlocksSourceText);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_SET_GENERIC_ENTITY_POINTER_TO_ENTITY)
		{
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			string setGenericEntityPointerToEntityText = NLCprintDefs.generateCodeSetGenericEntityPointerToEntityText(param1, param2, progLang);	 //param1 = param2;
			NLCprintDefs.printLine(setGenericEntityPointerToEntityText, level, &printedCodeBlocksSourceText);
		}
		#ifdef NLC_MATH_OBJECTS_STRING
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_SET_MATH_OBJECT_STRING_VALUE)
		{
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			string setStringValueText = NLCprintDefs.generateCodeEntityMathObjectStringValueText(param1, progLang) + progLangEquals[progLang] + param2->name + progLangEndLine[progLang];	 //param1->mathObjectStringValue = param2;
			NLCprintDefs.printLine(setStringValueText, level, &printedCodeBlocksSourceText);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_DECLARE_NEW_STRING_POINTER_VARIABLE)
		{
			string declareNewStringPointerVariableText = NLCprintDefs.generateCodeDeclareNewStringPointerVariableText(param1, progLang);	 //string* param1 = NULL;
			NLCprintDefs.printLine(declareNewStringPointerVariableText, level, &printedCodeBlocksSourceText);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_SET_STRING_POINTER_TO_ENTITY_MATH_OBJECT_STRING_VALUE)
		{
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			string setStringPointerToEntityMathObjectStringValueText = NLCprintDefs.generateCodeSetStringPointerToEntityMathObjectStringValueText(param1, param2, progLang);	 //param1 = &(param2->mathObjectStringValue);
			NLCprintDefs.printLine(setStringPointerToEntityMathObjectStringValueText, level, &printedCodeBlocksSourceText);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_SET_MATH_OBJECT_TYPE_AS_STRING)
		{
			string setMathTypeText = NLCprintDefs.generateCodeEntityMathObjectTypeText(param1, progLang) + progLangEquals[progLang] + NLC_MATH_OBJECTS_VARIABLE_TYPE_STRING_DEFNAME + progLangEndLine[progLang];	 //param1->mathObjectType = NLC_MATH_OBJECTS_VARIABLE_TYPE_STRING;
			NLCprintDefs.printLine(setMathTypeText, level, &printedCodeBlocksSourceText);
		}
		#endif
		#ifdef NLC_MATH_OBJECTS_BOOLEAN
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_SET_MATH_OBJECT_BOOLEAN_VALUE)
		{
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			string setBooleanValueText = NLCprintDefs.generateCodeEntityMathObjectBooleanValueText(param1, progLang) + progLangEquals[progLang] + param2->name + progLangEndLine[progLang];	 //param1->mathObjectStringValue = param2;
			NLCprintDefs.printLine(setBooleanValueText, level, &printedCodeBlocksSourceText);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_DECLARE_NEW_BOOLEAN_POINTER_VARIABLE)
		{
			string declareNewBooleanPointerVariableText = NLCprintDefs.generateCodeDeclareNewBooleanPointerVariableText(param1, progLang);	 //string* param1 = NULL;
			NLCprintDefs.printLine(declareNewBooleanPointerVariableText, level, &printedCodeBlocksSourceText);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_SET_BOOLEAN_POINTER_TO_ENTITY_MATH_OBJECT_BOOLEAN_VALUE)
		{
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			string setBooleanPointerToEntityMathObjectBooleanValueText = NLCprintDefs.generateCodeSetBooleanPointerToEntityMathObjectBooleanValueText(param1, param2, progLang);	 //param1 = &(param2->mathObjectStringValue);
			NLCprintDefs.printLine(setBooleanPointerToEntityMathObjectBooleanValueText, level, &printedCodeBlocksSourceText);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_SET_MATH_OBJECT_TYPE_AS_BOOLEAN)
		{
			string setMathTypeText = NLCprintDefs.generateCodeEntityMathObjectTypeText(param1, progLang) + progLangEquals[progLang] + NLC_MATH_OBJECTS_VARIABLE_TYPE_BOOLEAN_DEFNAME + progLangEndLine[progLang];	 //param1->mathObjectType = NLC_MATH_OBJECTS_VARIABLE_TYPE_BOOLEAN;
			NLCprintDefs.printLine(setMathTypeText, level, &printedCodeBlocksSourceText);
		}
		#endif
		#endif
		#ifdef NLC_MATH_OBJECTS_TEST_NULL_POINTER_MAINTAIN_CONTEXT
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_TEST_POINTER_VALUE)
		{

			string ifPointerNotNullText = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + param1->name + progLangEqualsTest[progLang] + progLangNullPointer[progLang] + progLangCloseParameterSpace[progLang];	 //if(param1 == NULL)
			NLCprintDefs.printLine(ifPointerNotNullText, level, &printedCodeBlocksSourceText);
			NLCprintDefs.printLine(progLangOpenBlock[progLang], level, &printedCodeBlocksSourceText);	//{

			string throwNullPointerErrorText = string(progLangPrintTextOpen[progLang]) + NLC_MATH_OBJECTS_TEST_NULL_POINTER_MAINTAIN_CONTEXT_WARNING_TEXT + progLangPrintTextClose[progLang] + progLangEndLine[progLang];
			NLCprintDefs.printLine(throwNullPointerErrorText, level+1, &printedCodeBlocksSourceText);

			NLCprintDefs.printLine(progLangCloseBlock[progLang], level, &printedCodeBlocksSourceText);	//}
		}
		#else
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_CHECK_POINTER_VALUE)
		{

			string ifPointerNotNullText = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + param1->name + progLangIsNotEqualTo[progLang] + progLangNullPointer[progLang] + progLangCloseParameterSpace[progLang];	 //if(param1 != NULL)
			NLCprintDefs.printLine(ifPointerNotNullText, level, &printedCodeBlocksSourceText);
			NLCprintDefs.printLine(progLangOpenBlock[progLang], level, &printedCodeBlocksSourceText);	//{
		}
		#endif
		#endif
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_IF_TEMP_VARIABLE_NAME_EQUALS_CLASS_NAME)
		{
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			string ifObjectNameEqualsClassNameText = NLCprintDefs.generateCodeClassNameTestText(param1->instanceName, param2->name, progLang);
			NLCprintDefs.printLine(ifObjectNameEqualsClassNameText, level, &printedCodeBlocksSourceText);
			NLCprintDefs.printLine(progLangOpenBlock[progLang], level, &printedCodeBlocksSourceText);	//{
		}
		#ifdef NLC_TRANSLATOR_TEST_DEFINITE_ENTITY_EXISTENCE
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_VERIFY_DEFINITE_ENTITY_EXISTENCE_NEW_FUNCTION)
		{

			NLCprintCodeBlocksFunctions.generateCodeVerifyDefiniteReferenceExistenceNewFunction(progLang, &printedCodeBlocksSourceText, level);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_VERIFY_DEFINITE_ENTITY_EXISTENCE_EXECUTE_FUNCTION)
		{
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			NLCprintCodeBlocksFunctions.generateCodeVerifyDefiniteReferenceExistenceExecuteFunction(param1, param2, progLang, &printedCodeBlocksSourceText, level);
		}
		#endif
		#ifdef NLC_ADVANCED_REFERENCING_SUPPORT_ALIASES_MERGERS
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_REMOVE_ENTITY_FROM_LOCAL_LIST_EXECUTE_FUNCTION)
		{
			NLCprintCodeBlocksFunctions.findAndRemoveEntityFromLocalListExecuteFunction(param1, progLang, &printedCodeBlocksSourceText, level);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_REPLACE_ENTITY_IN_LOCAL_LIST_EXECUTE_FUNCTION)
		{
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			NLCprintCodeBlocksFunctions.findAndReplaceEntityInLocalListExecuteFunction(param1, param2, progLang, &printedCodeBlocksSourceText, level);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_MERGE_ENTITY1_ATTRIBUTES_INTO_ENTITY2_EXECUTE_FUNCTION)
		{
			NLCitem* param2 = currentCodeBlockInLevel->parameters.at(1);
			NLCprintCodeBlocksFunctions.mergeEntity1AttributesIntoEntity2ExecuteFunction(param1, param2, progLang, &printedCodeBlocksSourceText, level);
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
			this->printCodeBlocks(currentCodeBlockInLevel->lowerLevel, classDefinitionList, progLang, &printedCodeBlocksSourceText, (level+1));
			#ifdef NLC_ADVANCED_REFERENCING_MONITOR_CONTEXT
			if(currentCodeBlockInLevel->isLogicalCondition)
			{				
				//createCodeBlocksClearContextListVariableExecuteFunction:

				NLCitem param1;
				param1.name = SHAREDvars.convertIntToString(currentCodeBlockInLevel->contextLevel);
				NLCprintCodeBlocksFunctions.generateCodeClearReferenceContextListExecuteFunction(&param1, progLang, &printedCodeBlocksSourceText, level+1);
			}
			#endif
			NLCprintDefs.printLine(progLangCloseBlock[progLang], level, &printedCodeBlocksSourceText);
		}

		currentCodeBlockInLevel = currentCodeBlockInLevel->next;
	}

	#ifdef NLC_PREDEFINED_FUNCTION_NAME_FOR_NATURAL_LANGUAGE_CODE_WITHOUT_FUNCTION_SPECIFIED_EXECUTE_IN_MAIN
	printedCodeBlocksSourceText = printedCodeBlocksSourceText + printedCodeBlocksSourceMainFunctionText;
	#endif

	#ifdef NLC_LIBRARY_GENERATE_INDIVIDUAL_FILES_ADD_CLASS_FUNCTIONS_TO_CLASS_DEFINITIONS
	SHAREDvars.appendStringToFile(printedClassDefinitionSourceFileName, &printedCodeBlocksSourceText);
	#endif

	#ifdef NLC_LIBRARY_GENERATE_INDIVIDUAL_FILES
	if(printedClassDefinitionSourceFileName != "")
	{
		*code = *code + NLCprintDefs.generatePrintedFileName(printedClassDefinitionSourceFileName);
	}
	#endif
	*code = *code + printedCodeBlocksSourceText;

	return result;
}



void NLCprintCodeBlocksClass::generateFunctionExecutionArgumentsWithActionNetworkIndexInheritanceString(vector<NLCclassDefinition*>* classDefinitionList, vector<NLCitem*>* codeBlockParameters, string* functionArguments, int progLang, string* functionDeclarationOwnerName, string* functionDeclarationObjectName)
{
	vector<NLCitem*>* parameters;
	#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS
	#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
	parameters = codeBlockParameters;

	string functionName = "";
	NLCitem* functionArgument = NULL;
	if(NLCclassDefinitionClass.findFunctionArgument(codeBlockParameters, NLC_ITEM_TYPE_FUNCTION_EXECUTION_ARGUMENT_FUNCTION, &functionArgument))
	{
		functionName = functionArgument->name;
	}
	else
	{
		cerr << "generateFunctionExecutionArgumentsWithActionNetworkIndexInheritanceString{}: NLC_ITEM_TYPE_FUNCTION_EXECUTION_ARGUMENT_FUNCTION not found" << endl;
		exit(EXIT_ERROR);
	}

	string functionOwnerName = "";
	NLCitem* functionOwnerArgument = NULL;
	bool hasFunctionOwnerClass = false;
	if(NLCclassDefinitionClass.findFunctionArgument(codeBlockParameters, NLC_ITEM_TYPE_FUNCTION_EXECUTION_ARGUMENT_FUNCTION_OWNER, &functionOwnerArgument))
	{
		hasFunctionOwnerClass = true;
		functionOwnerName = functionOwnerArgument->name;
	}

	string functionObjectName = "";
	NLCitem* functionObjectArgument = NULL;
	bool hasFunctionObjectClass = false;
	if(NLCclassDefinitionClass.findFunctionArgument(codeBlockParameters, NLC_ITEM_TYPE_FUNCTION_EXECUTION_ARGUMENT_FUNCTION_OBJECT, &functionObjectArgument))
	{
		hasFunctionObjectClass = true;
		functionObjectName = functionObjectArgument->name;
	}

	bool foundFunctionOwnerExactMatch = false;
	bool foundFunctionObjectExactMatch = false;
	bool rearrangeClassList = false;
	NLCclassDefinition* functionDefinitionClassDefinition = NULL;
	if(NLCclassDefinitionClass.findFunctionDefinitionClassDefinitionExactOrNonExactMatch(classDefinitionList, functionName, functionOwnerName, functionObjectName, hasFunctionOwnerClass, hasFunctionObjectClass, &functionDefinitionClassDefinition, rearrangeClassList, &foundFunctionOwnerExactMatch, &foundFunctionObjectExactMatch))
	{

		#ifdef NLC_FUNCTIONS_SUPPORT_PLURAL_SUBJECTS
		if(hasFunctionOwnerClass && !foundFunctionOwnerExactMatch)
		{
			NLCitem* functionOwnerArgumentDeclaration = NULL;
			if(NLCclassDefinitionClass.findFunctionArgument(&(functionDefinitionClassDefinition->parameters), NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION_OWNER, &functionOwnerArgumentDeclaration))
			{
				functionOwnerArgument->functionArgumentPassCastRequired = true;
				functionOwnerArgument->functionArgumentPassCastClassName = NLCitemClass.generateClassName(functionOwnerArgumentDeclaration->name);
				#ifdef NLC_NONOO_DISABLE_CLASS_HEIRACHY
				*functionDeclarationOwnerName = functionOwnerArgumentDeclaration->name;
				#endif
				//functionOwnerArgument already added to parameters
			}
			else
			{
				cout << "generateFunctionExecutionArgumentsWithActionNetworkIndexInheritanceString{} error: !findFunctionArgument: NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION_OWNER - functionName = " << functionName << endl;
			}
		}
		#endif
		if(hasFunctionObjectClass && !foundFunctionObjectExactMatch)
		{
			NLCitem* functionObjectArgumentDeclaration = NULL;
			if(NLCclassDefinitionClass.findFunctionArgument(&(functionDefinitionClassDefinition->parameters), NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION_OBJECT, &functionObjectArgumentDeclaration))
			{
				functionObjectArgument->functionArgumentPassCastRequired = true;
				functionObjectArgument->functionArgumentPassCastClassName = NLCitemClass.generateClassName(functionObjectArgumentDeclaration->name);
				#ifdef NLC_NONOO_DISABLE_CLASS_HEIRACHY
				*functionDeclarationObjectName = functionObjectArgumentDeclaration->name;
				#endif
				//functionObjectArgument already added to parameters
			}
			else
			{
				cout << "generateFunctionExecutionArgumentsWithActionNetworkIndexInheritanceString{} error: !findFunctionArgument: NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION_OBJECT - functionName = " << functionName << endl;
			}
		}

		#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_BASED_ON_IMPLICITLY_DECLARED_VARIABLES_IN_CURRENT_FUNCTION_DEFINITION
		for(vector<NLCitem*>::iterator parametersIterator = functionDefinitionClassDefinition->parameters.begin(); parametersIterator < functionDefinitionClassDefinition->parameters.end(); parametersIterator++)
		{
			NLCitem* currentItem = *parametersIterator;
			if(currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_INSTANCE_OR_CLASS_LIST)
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

		#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS
		#ifdef NLC_FUNCTIONS_SUPPORT_PLURAL_SUBJECTS
		if(currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_EXECUTION_ARGUMENT_FUNCTION_OWNER)
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
			*functionArguments = *functionArguments + this->generateCodePluralReferenceText(currentItem, progLang, categoryList, NLC_ITEM_TYPE_SUBJECTCATEGORY_VAR_APPENDITION);
			#else
			*functionArguments = *functionArguments + this->generateCodeSingularReferenceText(currentItem, progLang);
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
			#ifdef NLC_LIBRARY_ASSUME_STANDARD_AND_USER_LIBRARY_FUNCTIONS_ACTION_ARGUMENT_TYPE_IS_NLC_GENERIC_ENTITY_CLASS
			if(functionDefinitionClassDefinition != NULL)
			{
				if(functionDefinitionClassDefinition->isLibraryFunctionDefinition)
				{
					currentItem->functionArgumentPassCastRequired = true;
					currentItem->functionArgumentPassCastClassName = NLCitemClass.generateClassName(NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE);
				}
			}
			#endif
			if(*functionArguments != "")
			{
				*functionArguments = *functionArguments + progLangClassMemberFunctionParametersNext[progLang];
			}
			#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS_PASS_AS_LISTS
			bool categoryList = false;
			*functionArguments = *functionArguments + this->generateCodePluralReferenceText(currentItem, progLang, categoryList, "");
			#else
			*functionArguments = *functionArguments + this->generateCodeSingularReferenceText(currentItem, progLang);
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
			*functionArguments = *functionArguments + this->generateCodePluralReferenceText(currentItem, progLang, categoryList, NLC_ITEM_TYPE_OBJECTCATEGORY_VAR_APPENDITION);
			#else
			*functionArguments = *functionArguments + this->generateCodeSingularReferenceText(currentItem, progLang);
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
			*functionArguments = *functionArguments + this->generateCodeSingularReferenceText(currentItem, progLang);
		}
		#endif
		*/
		else if(currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_EXECUTION_ARGUMENT_INSTANCE_OR_CLASS_LIST)
		{
			if(*functionArguments != "")
			{
				*functionArguments = *functionArguments + progLangClassMemberFunctionParametersNext[progLang];
			}

			bool categoryList = false;
			*functionArguments = *functionArguments + this->generateCodePluralReferenceText(currentItem, progLang, categoryList, "");
			//*functionArguments = *functionArguments + this->generateCodeSingularReferenceText(currentItem, progLang);	//OLD
		}
	}
}


string NLCprintCodeBlocksClass::generateCodePluralReferenceText(const NLCitem* functionArgumentItem, const int progLang, const bool categoryList, const string categoryVarAppendName)
{
	string codeFunctionArgumentName = "";
	string codeFunctionArgumentNameWithCast = "";

	#ifdef NLC_ACTION_CATEGORY_LISTS_USE_AS_FUNCTION_EXECUTION_ARGUMENTS
	if(categoryList)
	{
		codeFunctionArgumentName = NLCprintDefs.generateCategoryListName(functionArgumentItem, categoryVarAppendName);
	}
	else
	{
	#endif
		codeFunctionArgumentName = NLCprintDefs.generateEntityListName(functionArgumentItem);
	#ifdef NLC_ACTION_CATEGORY_LISTS_USE_AS_FUNCTION_EXECUTION_ARGUMENTS
	}
	#endif

	codeFunctionArgumentNameWithCast = codeFunctionArgumentName;
	#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_ENABLE_TYPE_CASTING
	#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
	if(functionArgumentItem->functionArgumentPassCastRequired)
	{
		codeFunctionArgumentNameWithCast = this->printCodeBlockCastVectorExecuteFunction(functionArgumentItem, progLang, codeFunctionArgumentName);
	}
	#endif
	#endif

	return codeFunctionArgumentNameWithCast;
}

string NLCprintCodeBlocksClass::generateCodeSingularReferenceText(const NLCitem* functionArgumentItem, const int progLang)
{
	string codePropertyTypeText = functionArgumentItem->instanceName;
	#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_ENABLE_TYPE_CASTING
	#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
	if(functionArgumentItem->functionArgumentPassCastRequired)
	{
		codePropertyTypeText = NLCprintDefs.generateStaticCastOfEntity(functionArgumentItem->instanceName, functionArgumentItem->functionArgumentPassCastClassName, progLang); 	//static_cast<parentClass*>(childClassInstance);
	}
	#endif
	#endif
	return codePropertyTypeText;
}

#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS
string NLCprintCodeBlocksClass::printCodeBlockCastVectorExecuteFunction(const NLCitem* functionArgumentItem, const int progLang, const string codeFunctionArgumentName)
{
	//see NLC_CODEBLOCK_TYPE_CAST_VECTOR_EXECUTE_FUNCTION

	string codeBlockTextTemplateDefinition = progLangTemplateUsePart1[progLang] + functionArgumentItem->className + progLangTemplateUseClassSeparator[progLang] + functionArgumentItem->functionArgumentPassCastClassName + progLangTemplateUsePart2[progLang]; 	//<param1class, param2class>
	string codeBlockCastVectorExecuteFunctionText = string(NLC_CAST_VECTOR_FUNCTION_NAME) + codeBlockTextTemplateDefinition + progLangOpenParameterSpace[progLang] + codeFunctionArgumentName + progLangCloseParameterSpace[progLang];	//castVector<param1class, param2class> (param1InstanceList)

	return codeBlockCastVectorExecuteFunctionText;
}
#endif

#ifdef NLC_INTERPRET_ACTION_PROPERTIES_AND_CONDITIONS_AS_FUNCTION_ARGUMENTS
string NLCprintCodeBlocksClass::generateCodeConditionPairReferenceText(NLCitem* functionArgumentConditionItem, const int progLang)
{
	//do: add dynamic_cast<functionArgumentPassCastClassName> if functionArgumentPassCastClassName != ""
	string codeConditionPairTypeText = NLCprintDefs.generateCodeConditionPairTextWithContext(functionArgumentConditionItem->name, functionArgumentConditionItem->className, functionArgumentConditionItem->instanceName, functionArgumentConditionItem->className2, functionArgumentConditionItem->instanceName2, &(functionArgumentConditionItem->context), progLang);
	return codeConditionPairTypeText;
}
#endif


#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS
void NLCprintCodeBlocksClass::generateLocalFunctionArgumentsBasedOnImplicitDeclarationsString(vector<NLCitem*>* parameters, string* functionArguments, int progLang)
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
			*functionArguments = *functionArguments + NLCprintDefs.generateCodeEntityListDefinitionReferenceText(currentItem, progLang);
		}
	}
}
#endif

#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS
void NLCprintCodeBlocksClass::generateFunctionArgumentsBasedOnActionAndActionObjectVars(vector<NLCitem*>* parameters, string* functionArguments, int progLang, string* functionDeclarationOwnerName, string* functionDeclarationObjectName)
{
	for(vector<NLCitem*>::iterator parametersIterator = parameters->begin(); parametersIterator < parameters->end(); parametersIterator++)
	{
		NLCitem* currentItem = *parametersIterator;
		#ifdef NLC_FUNCTIONS_SUPPORT_PLURAL_SUBJECTS
		if(currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION_OWNER)
		{
			if(*functionArguments != "")
			{
				*functionArguments = *functionArguments + progLangClassMemberFunctionParametersNext[progLang];
			}
			#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS_PASS_AS_LISTS
			*functionArguments = *functionArguments + NLCprintDefs.generateCodeEntityListDefinitionReferenceText(currentItem, progLang);
			#else
			*functionArguments = *functionArguments + NLCprintDefs.generateCodeEntityDefinitionText(currentItem, progLang);
			#endif
			#ifdef NLC_NONOO_DISABLE_CLASS_HEIRACHY
			*functionDeclarationOwnerName = currentItem->name;
			#endif
		}
		else
		#endif
		if(currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION)
		{
			#ifdef NLC_PREDEFINED_FUNCTION_NAME_FOR_NATURAL_LANGUAGE_CODE_WITHOUT_FUNCTION_SPECIFIED_DO_NOT_PRINT_ACTION_ARGUMENT
			if(currentItem->className != NLCitemClass.generateClassName(NLC_PREDEFINED_FUNCTION_NAME_FOR_NATURAL_LANGUAGE_CODE_WITHOUT_FUNCTION_SPECIFIED_NAME))
			{
			#endif
				if(*functionArguments != "")
				{
					*functionArguments = *functionArguments + progLangClassMemberFunctionParametersNext[progLang];
				}
				#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS_PASS_AS_LISTS
				*functionArguments = *functionArguments + NLCprintDefs.generateCodeEntityListDefinitionReferenceText(currentItem, progLang);
				#else
				*functionArguments = *functionArguments + NLCprintDefs.generateCodeEntityDefinitionText(currentItem, progLang);
				#endif
			#ifdef NLC_PREDEFINED_FUNCTION_NAME_FOR_NATURAL_LANGUAGE_CODE_WITHOUT_FUNCTION_SPECIFIED_DO_NOT_PRINT_ACTION_ARGUMENT
			}
			#endif
		}
		else if(currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION_OBJECT)
		{
			if(*functionArguments != "")
			{
				*functionArguments = *functionArguments + progLangClassMemberFunctionParametersNext[progLang];
			}
			#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS_PASS_AS_LISTS
			*functionArguments = *functionArguments + NLCprintDefs.generateCodeEntityListDefinitionReferenceText(currentItem, progLang);
			#else
			*functionArguments = *functionArguments + NLCprintDefs.generateCodeEntityDefinitionText(currentItem, progLang);
			#endif
			#ifdef NLC_NONOO_DISABLE_CLASS_HEIRACHY
			*functionDeclarationObjectName = currentItem->name;
			#endif
		}

	}
}
#endif





string NLCprintCodeBlocksClass::generateFunctionOwnerContext(vector<NLCitem*>* parameters, const int progLang, string* functionOwnerName)
{
	bool foundFunctionOwner = false;
	string functionOwnerContext = "";
	#ifdef NLC_INPUT_FUNCTION_LISTS
	for(vector<NLCitem*>::iterator parametersIterator = parameters->begin(); parametersIterator < parameters->end(); parametersIterator++)
	{
		NLCitem* currentItem = *parametersIterator;
		if(currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION_OWNER)
		{
			*functionOwnerName = currentItem->className;
			functionOwnerContext = progLangClassMemberFunctionTypeDefault[progLang] + *functionOwnerName + progLangFunctionOwnerClassDelimiter[progLang];
			foundFunctionOwner = true;
		}
	}
	#endif
	if(!foundFunctionOwner)
	{
		functionOwnerContext = progLangClassMemberFunctionTypeDefault[progLang];	//void
		#ifdef NLC_LIBRARY_GENERATE_INDIVIDUAL_FILES_ADD_CLASS_FUNCTIONS_TO_CLASS_DEFINITIONS
		functionOwnerContext = functionOwnerContext + NLCitemClass.generateClassName(NLC_CLASS_DEFINITIONS_SUPPORT_FUNCTIONS_WITHOUT_SUBJECT_ARTIFICIAL_CLASS_NAME) + progLangFunctionOwnerClassDelimiter[progLang];	//void functionsWithNoSubjectArtificialClass::
		*functionOwnerName = NLCitemClass.generateClassName(NLC_CLASS_DEFINITIONS_SUPPORT_FUNCTIONS_WITHOUT_SUBJECT_ARTIFICIAL_CLASS_NAME);
		#endif
	}
	return functionOwnerContext;
}



#ifdef NLC_PREDEFINED_FUNCTION_NAME_FOR_NATURAL_LANGUAGE_CODE_WITHOUT_FUNCTION_SPECIFIED_EXECUTE_IN_MAIN
string NLCprintCodeBlocksClass::generateMainFunctionText(vector<NLCitem*>* parameters, const int progLang)
{
	string printedCodeBlocksSourceMainFunctionText = "";

	bool implicitlyDeclaredFunctionDetected = false;

	string functionName = "";
	NLCitem* functionArgument = NULL;
	if(NLCclassDefinitionClass.findFunctionArgument(parameters, NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION, &functionArgument))
	{
		if(functionArgument->className == NLCitemClass.generateClassName(NLC_PREDEFINED_FUNCTION_NAME_FOR_NATURAL_LANGUAGE_CODE_WITHOUT_FUNCTION_SPECIFIED_NAME))
		{
			implicitlyDeclaredFunctionDetected = true;
			functionName = functionArgument->functionName;
		}
		#ifdef NLC_PREDEFINED_FUNCTION_NAME_FOR_NATURAL_LANGUAGE_CODE_WITHOUT_FUNCTION_SPECIFIED_EXECUTE_IN_MAIN_DETECT_USER_DECLARED_MAIN
		if(functionArgument->className == NLCitemClass.generateClassName(NLC_PREDEFINED_FUNCTION_NAME_FOR_NATURAL_LANGUAGE_CODE_WITHOUT_FUNCTION_SPECIFIED_EXECUTE_IN_MAIN_DETECT_USER_DECLARED_MAIN_FUNCTION_NAME))
		{
			implicitlyDeclaredFunctionDetected = true;
			functionName = functionArgument->functionName;
		}		
		#endif
	}
	NLCitem* functionOwnerArgument = NULL;
	string functionOwnerName = "";
	if(NLCclassDefinitionClass.findFunctionArgument(parameters, NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION_OWNER, &functionOwnerArgument))	//this may not be set
	{
		if(functionOwnerArgument->className == NLCitemClass.generateClassName(NLC_CLASS_DEFINITIONS_SUPPORT_FUNCTIONS_WITHOUT_SUBJECT_ARTIFICIAL_CLASS_NAME))
		{
			functionOwnerName = NLC_CLASS_DEFINITIONS_SUPPORT_FUNCTIONS_WITHOUT_SUBJECT_ARTIFICIAL_CLASS_NAME;
		}
		else
		{
			implicitlyDeclaredFunctionDetected = false;
		}
	}
	else
	{
		functionOwnerName = NLC_CLASS_DEFINITIONS_SUPPORT_FUNCTIONS_WITHOUT_SUBJECT_ARTIFICIAL_CLASS_NAME;	
	}
	
	if(implicitlyDeclaredFunctionDetected)
	{
		string functionArgumentsDeclaration = "";
		string functionArguments = "";
		for(vector<NLCitem*>::iterator parametersIterator = parameters->begin(); parametersIterator < parameters->end(); parametersIterator++)
		{
			NLCitem* currentItem = *parametersIterator;

			if((currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_INSTANCE_OR_CLASS_LIST) || (currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION))
			{
				if(functionArguments != "")
				{
					functionArguments = functionArguments + progLangClassMemberFunctionParametersNext[progLang];	//,
				}
				functionArguments = functionArguments + NLCprintDefs.generateEntityListName(currentItem);	//xClassList
				functionArgumentsDeclaration = functionArgumentsDeclaration + CHAR_TAB + NLCprintDefs.generateCodeEntityListDefinitionText(currentItem, progLang) + progLangEndLine[progLang] + CHAR_NEWLINE;	//eg \tvector<xClass> xClassList;
			}
		}
		printedCodeBlocksSourceMainFunctionText = printedCodeBlocksSourceMainFunctionText + CHAR_NEWLINE + progLangMainFunctionDeclaration[progLang] + CHAR_NEWLINE + progLangOpenBlock[progLang] + CHAR_NEWLINE;	//int main()\n{
		printedCodeBlocksSourceMainFunctionText = printedCodeBlocksSourceMainFunctionText + functionArgumentsDeclaration;
		printedCodeBlocksSourceMainFunctionText = printedCodeBlocksSourceMainFunctionText + CHAR_TAB + NLCprintDefs.generateExternalFunctionContext(functionOwnerName, progLang) + functionName + progLangOpenParameterSpace[progLang] + functionArguments + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang] + CHAR_NEWLINE;	//(new functionsWithNoSubjectArtificial)->NLCimplicitlyDeclaredFunctionArtificialFunction/mainFunction(xClassList, ...);\n
		printedCodeBlocksSourceMainFunctionText = printedCodeBlocksSourceMainFunctionText + progLangCloseBlock[progLang] + CHAR_NEWLINE;		//}\n
	}

	return printedCodeBlocksSourceMainFunctionText;
}
#endif


