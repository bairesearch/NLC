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
 * File Name: NLCprintCodeBlocks.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2013 Baxter AI (baxterai.com)
 * Project: Natural Language Programming Interface (compiler)
 * Project Version: 1f5a 05-January-2014
 * Requirements: requires text parsed by NLP Parser (eg Relex; available in .CFF format <relations>)
 *
 *******************************************************************************/



#include <ctime>
#include <cstdlib>	//for random number generation
#include <cmath>

#include "NLCprintCodeBlocks.h"
#include "NLCprintDefs.h"

bool printCodeBlocks(NLCcodeblock * firstCodeBlockInLevel, vector<NLCclassDefinition *> * classDefinitionList, int progLang, string * code, int level)
{
	NLCcodeblock * currentCodeBlockInLevel = firstCodeBlockInLevel;
	while(currentCodeBlockInLevel->next != NULL)
	{
		//cout << "z1" << endl;
		NLCitem * param1 = currentCodeBlockInLevel->parameters.at(0);
		string contextParam1 = generateStringFromContextVector(&(param1->context), progLang);
		
		//cout << "z2" << endl;	
		if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_EXECUTE_FUNCTION)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_EXECUTE_FUNCTION" << endl;
			#endif
			//cout << "z7a" << endl;
			//cout << "param1->className = " << param1->className << endl;
			//cout << "param2->className = " << param2->className << endl;
			//cout << "contextParam1 = " << contextParam1 << endl;						
			
			//cout << "contextParam2 = " << contextParam2 << endl;

			string functionArguments = "";
			generateFunctionExecutionArgumentsWithActionConceptInheritanceString(classDefinitionList, &(currentCodeBlockInLevel->parameters), &functionArguments, progLang);
			
			string codeBlockText = contextParam1 + param1->functionName + progLangOpenParameterSpace[progLang] + functionArguments + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//context1.param1(context.param2); 	[param1 = function, context1 = subject, param2 = object]
				//OLD before 1c5a: param1->instanceName
			//cout << "z7c" << endl;
			printLine(codeBlockText, level, code);
			
			//cout << "z9" << endl;
		}		
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_ADD_NEW_PROPERTY)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_ADD_NEW_PROPERTY" << endl;
			#endif
			NLCitem * param2 = currentCodeBlockInLevel->parameters.at(1);	
			//string contextParam2 = generateStringFromContextVector(&(param2->context), progLang);
			
			string codeBlockTextCreate = param2->className + progLangPointer[progLang] + STRING_SPACE + param2->instanceName + progLangEquals[progLang] + progLangNewObject[progLang] + param2->className + progLangOpenParameterSpace[progLang] + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	
			printLine(codeBlockTextCreate, level, code);
			string codeBlockText = contextParam1 + param1->instanceName + progLangObjectReferenceDelimiter[progLang] + param2->className + NLC_ITEM_TYPE_PROPERTYLISTVAR_APPENDITION + progLangFunctionReferenceDelimiter[progLang] + progLangAddProperty[progLang] + progLangOpenParameterSpace[progLang] + param2->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//context1->param1->param2PropertyList.push_back(param2);
			printLine(codeBlockText, level, code);
		}	
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_ADD_NEW_PROPERTY_TO_LOCAL_LIST)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_ADD_NEW_PROPERTY_TO_LOCAL_LIST" << endl;
			#endif
			NLCitem * param2 = currentCodeBlockInLevel->parameters.at(1);	
			//string contextParam2 = generateStringFromContextVector(&(param2->context), progLang);
			
			string codeBlockTextCreate = param2->className + progLangPointer[progLang] + STRING_SPACE + param2->instanceName + progLangEquals[progLang] + progLangNewObject[progLang] + param2->className + progLangOpenParameterSpace[progLang] + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	
			printLine(codeBlockTextCreate, level, code);
			#ifdef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES
			string codeBlockText = generatePropertyListName(param1->instanceName) + progLangFunctionReferenceDelimiter[progLang] + progLangAddProperty[progLang] + progLangOpenParameterSpace[progLang] + param2->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//param1instancePropertyList.push_back(param2);
			#else
			string codeBlockText = generatePropertyListName(param1->className) + progLangFunctionReferenceDelimiter[progLang] + progLangAddProperty[progLang] + progLangOpenParameterSpace[progLang] + param2->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//param1instancePropertyList.push_back(param2);			
			#endif
			printLine(codeBlockText, level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_ADD_NEW_CONDITION)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_ADD_NEW_CONDITION" << endl;
			#endif
			NLCitem * param2 = currentCodeBlockInLevel->parameters.at(1);	
			NLCitem * param3 = currentCodeBlockInLevel->parameters.at(2);	
			//string contextParam3 = generateStringFromContextVector(&(param3->context), progLang);
			string codeBlockTextCreate = param3->className + progLangPointer[progLang] + STRING_SPACE + param3->instanceName + progLangEquals[progLang] + progLangNewObject[progLang] + param3->className + progLangOpenParameterSpace[progLang] + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];
			printLine(codeBlockTextCreate, level, code);
			#ifdef NLC_USE_STRING_INDEXED_UNORDERED_MAPS_FOR_CONDITION_LISTS
			string codeBlockText = contextParam1 + param1->instanceName + progLangObjectReferenceDelimiter[progLang] + param3->className + NLC_ITEM_TYPE_CONDITIONLISTVAR_APPENDITION + progLangFunctionReferenceDelimiter[progLang] + progLangAddCondition[progLang] + progLangOpenParameterSpace[progLang] + progLangStringOpenClose[progLang] + param2->className + progLangStringOpenClose[progLang] + progLangParameterSpaceNextParam[progLang] + param3->instanceName + progLangCloseParameterSpace[progLang] + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		
			#else
			string codeBlockTextCreate2 = param2->className + progLangPointer[progLang] + STRING_SPACE + param2->instanceName + progLangEquals[progLang] + progLangNewObject[progLang] + param2->className + progLangOpenParameterSpace[progLang] + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];
			//string codeBlockText = contextParam1 + param1->instanceName + progLangObjectReferenceDelimiter[progLang] + generateConditionListName(param2->className,  param3->className) + progLangFunctionReferenceDelimiter[progLang] + progLangAddCondition[progLang] + progLangOpenParameterSpace[progLang] + param2->instanceName + progLangParameterSpaceNextParam[progLang] + STRING_SPACE + param3->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//context1->param1->param2param3ConditionList.insert(param2, param3);	
			string codeBlockText = contextParam1 + param1->instanceName + progLangObjectReferenceDelimiter[progLang] + generateConditionListName(param2->className,  param3->className) + progLangFunctionReferenceDelimiter[progLang] + progLangAddCondition[progLang] + progLangOpenParameterSpace[progLang] + generateCodeConditionPairText(param2->className, param2->instanceName, param3->className, param3->instanceName, progLang) + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//context1->param1->param2param3ConditionList.insert(pair<param2className, param3className*>(param2, param3));	
			
			printLine(codeBlockTextCreate2, level, code);
			#endif
			printLine(codeBlockText, level, code);

		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_ADD_PROPERTY)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_ADD_PROPERTY" << endl;
			#endif
			NLCitem * param2 = currentCodeBlockInLevel->parameters.at(1);	
			//string contextParam2 = generateStringFromContextVector(&(param2->context), progLang);
			
			string codeBlockText = contextParam1 + param1->instanceName + progLangObjectReferenceDelimiter[progLang] + param2->className + NLC_ITEM_TYPE_PROPERTYLISTVAR_APPENDITION + progLangFunctionReferenceDelimiter[progLang] + progLangAddProperty[progLang] + progLangOpenParameterSpace[progLang] + param2->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//context1->param1->param2PropertyList.push_back(param2);
			printLine(codeBlockText, level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_ADD_PROPERTY_TO_LOCAL_LIST)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_ADD_PROPERTY_TO_LOCAL_LIST" << endl;
			#endif
			NLCitem * param2 = currentCodeBlockInLevel->parameters.at(1);	
			
			#ifdef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES
			string codeBlockText = generatePropertyListName(param1->instanceName) + progLangFunctionReferenceDelimiter[progLang] + progLangAddProperty[progLang] + progLangOpenParameterSpace[progLang] + param2->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//param1instancePropertyList.push_back(param2);
			#else
			string codeBlockText = generatePropertyListName(param1->className) + progLangFunctionReferenceDelimiter[progLang] + progLangAddProperty[progLang] + progLangOpenParameterSpace[progLang] + param2->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//param1instancePropertyList.push_back(param2);			
			#endif
			printLine(codeBlockText, level, code);
		}	
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_ADD_CONDITION)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_ADD_CONDITION" << endl;
			#endif
			NLCitem * param2 = currentCodeBlockInLevel->parameters.at(1);	
			NLCitem * param3 = currentCodeBlockInLevel->parameters.at(2);	
			//string contextParam3 = generateStringFromContextVector(&(param3->context), progLang);
			#ifdef NLC_USE_STRING_INDEXED_UNORDERED_MAPS_FOR_CONDITION_LISTS
			string codeBlockText = contextParam1 + param1->instanceName + progLangObjectReferenceDelimiter[progLang] + param3->className + NLC_ITEM_TYPE_CONDITIONLISTVAR_APPENDITION + progLangFunctionReferenceDelimiter[progLang] + progLangAddCondition[progLang] + progLangOpenParameterSpace[progLang] + progLangStringOpenClose[progLang] + param2->className + progLangStringOpenClose[progLang] + progLangParameterSpaceNextParam[progLang] + param3->instanceName + progLangCloseParameterSpace[progLang] + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		
			#else
			string codeBlockTextCreate2 = param2->className + progLangPointer[progLang] + STRING_SPACE + param2->instanceName + progLangEquals[progLang] + progLangNewObject[progLang] + param2->className + progLangOpenParameterSpace[progLang] + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];
			//string codeBlockText = contextParam1 + param1->instanceName + progLangObjectReferenceDelimiter[progLang] + generateConditionListName(param2->className,  param3->className) + progLangFunctionReferenceDelimiter[progLang] + progLangAddCondition[progLang] + progLangOpenParameterSpace[progLang] + param2->instanceName + progLangParameterSpaceNextParam[progLang] + STRING_SPACE + param3->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//context1->param1->param2param3ConditionList.insert(param2, param3);	
			string codeBlockText = contextParam1 + param1->instanceName + progLangObjectReferenceDelimiter[progLang] + generateConditionListName(param2->className,  param3->className) + progLangFunctionReferenceDelimiter[progLang] + progLangAddCondition[progLang] + progLangOpenParameterSpace[progLang] + generateCodeConditionPairText(param2->className, param2->instanceName, param3->className, param3->instanceName, progLang) + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//context1->param1->param2param3ConditionList.insert(pair<param2className, param3className*>(param2, param3));	
			
			printLine(codeBlockTextCreate2, level, code);
			#endif
			printLine(codeBlockText, level, code);

		}			
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_FOR_PROPERTY_LIST)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_FOR_PROPERTY_LIST" << endl;
			#endif
			string codeBlockText = progLangFor[progLang] + progLangForIterPart1[progLang] + generateCodePropertyListDefinitionTypeText(param1->className, progLang) + progLangForIterPart2[progLang] + contextParam1 + generatePropertyListName(param1->className) + progLangForIterPart3[progLang] + contextParam1 + generatePropertyListName(param1->className) + progLangForIterPart4[progLang];
			printLine(codeBlockText, level, code);
			printLine(progLangOpenBlock[progLang], level, code);
			string tempVarDeclarationText = param1->className + progLangPointer[progLang] + STRING_SPACE + param1->instanceName + progLangEquals[progLang] + progLangPointer[progLang] + progLangForIterName[progLang] + progLangEndLine[progLang];	//OLD:  param1->className + NLC_ITEM_TYPE_TEMPVAR_APPENDITION
			printLine(tempVarDeclarationText, (level+1), code);

			//?cout << "error: printCodeBlocks() only yet finished for NLC_PROGRAMMING_LANGUAGE_DEFAULT" << endl; 
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_FOR_PROPERTY_LIST_LOCAL)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_FOR_PROPERTY_LIST_LOCAL" << endl;
			#endif
			#ifdef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES
			string codeBlockText = progLangFor[progLang] + progLangForIterPart1[progLang] + generateCodePropertyListDefinitionTypeText(param1->className, progLang) + progLangForIterPart2[progLang] + generatePropertyListName(param1->instanceName) + progLangForIterPart3[progLang] + generatePropertyListName(param1->instanceName) + progLangForIterPart4[progLang];
			#else
			string codeBlockText = progLangFor[progLang] + progLangForIterPart1[progLang] + generateCodePropertyListDefinitionTypeText(param1->className, progLang) + progLangForIterPart2[progLang] + generatePropertyListName(param1->className) + progLangForIterPart3[progLang] + generatePropertyListName(param1->className) + progLangForIterPart4[progLang];			
			#endif
			printLine(codeBlockText, level, code);
			printLine(progLangOpenBlock[progLang], level, code);
			string tempVarDeclarationText = param1->className + progLangPointer[progLang] + STRING_SPACE + param1->instanceName + progLangEquals[progLang] + progLangPointer[progLang] + progLangForIterName[progLang] + progLangEndLine[progLang];	//OLD:  param1->className + NLC_ITEM_TYPE_TEMPVAR_APPENDITION
			printLine(tempVarDeclarationText, (level+1), code);

			//?cout << "error: printCodeBlocks() only yet finished for NLC_PROGRAMMING_LANGUAGE_DEFAULT" << endl; 
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_FOR_CONDITION_LIST)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_FOR_CONDITION_LIST" << endl;
			#endif
			NLCitem * param2 = currentCodeBlockInLevel->parameters.at(1);
			string codeBlockText = progLangFor[progLang] + progLangForIterPart1[progLang] + generateCodeConditionListDefinitionTypeText(param1->className, param2->className, progLang) + progLangForIterPart2[progLang] + contextParam1 + generateConditionListName(param1->className, param2->className) + progLangForIterPart3[progLang] + contextParam1 + generateConditionListName(param1->className, param2->className) + progLangForIterPart4[progLang];
			printLine(codeBlockText, level, code);
			printLine(progLangOpenBlock[progLang], level, code);
			string tempVarDeclarationText = param2->className + progLangPointer[progLang] + STRING_SPACE + param2->instanceName + progLangEquals[progLang] + progLangForIterName[progLang] + progLangForIterConditionObjectReference[progLang] + progLangEndLine[progLang];
			printLine(tempVarDeclarationText, (level+1), code);

			//?cout << "error: printCodeBlocks() only yet finished for NLC_PROGRAMMING_LANGUAGE_DEFAULT" << endl; 
		}		
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_NEW_FUNCTION)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_NEW_FUNCTION" << endl;
			#endif
			string functionArguments = "";
			#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS
			generateLocalFunctionArgumentsBasedOnImplicitDeclarationsString(&(currentCodeBlockInLevel->parameters), &functionArguments, progLang);
			#endif	
			#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS
			generateFunctionArgumentsBasedOnActionAndActionObjectVars(&(currentCodeBlockInLevel->parameters), &functionArguments, progLang);
			#endif
			string functionOwnerContext = generateFunctionOwnerContext(&(currentCodeBlockInLevel->parameters), progLang);
			string codeBlockText = functionOwnerContext + param1->functionName + progLangOpenParameterSpace[progLang] + functionArguments + progLangCloseParameterSpace[progLang];	//main(){
			printLine(codeBlockText, level, code);		
			printLine(progLangOpenBlock[progLang], level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_IF_HAS_PROPERTY)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_IF_HAS_PROPERTY" << endl;
			#endif
			NLCitem * param2 = currentCodeBlockInLevel->parameters.at(1);	
			string contextParam2 = generateStringFromContextVector(&(param2->context), progLang);	//IS THIS REQUIRED????
			
			string codeBlockText = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + progLangNot[progLang] + progLangOpenParameterSpace[progLang] + contextParam1 + param1->instanceName + progLangFunctionReferenceDelimiter[progLang] + param2->className + NLC_ITEM_TYPE_PROPERTYLISTVAR_APPENDITION + progLangFunctionReferenceDelimiter[progLang] + progLangFindProperty[progLang] + progLangOpenParameterSpace[progLang] + progLangCloseParameterSpace[progLang] + progLangCloseParameterSpace[progLang] + progLangCloseParameterSpace[progLang];		//if(!(context1->param1->param2PropertyList.empty())){	
			printLine(codeBlockText, level, code);
			printLine(progLangOpenBlock[progLang], level, code);
		}		
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_IF_HAS_CONDITION)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_IF_HAS_CONDITION" << endl;
			#endif
			NLCitem * param2 = currentCodeBlockInLevel->parameters.at(1);		
			NLCitem * param3 = currentCodeBlockInLevel->parameters.at(2);
			string contextParam3 = generateStringFromContextVector(&(param3->context), progLang);
				
			string codeBlockText = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + progLangNot[progLang] + progLangOpenParameterSpace[progLang] + contextParam1 + param1->instanceName + progLangFunctionReferenceDelimiter[progLang] + generateConditionListName(param2->className, param3->className) + progLangFunctionReferenceDelimiter[progLang] + progLangFindCondition[progLang] + progLangOpenParameterSpace[progLang] + progLangCloseParameterSpace[progLang] + progLangCloseParameterSpace[progLang] + progLangCloseParameterSpace[progLang];	//if(!(context1->param1->param2param3ConditionList.empty())){	
			printLine(codeBlockText, level, code);
			printLine(progLangOpenBlock[progLang], level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_DECLARE_AND_INITIALISE_VARIABLE)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_DECLARE_AND_INITIALISE_VARIABLE" << endl;
			#endif
			NLCitem * param2 = currentCodeBlockInLevel->parameters.at(1);	
			
			string codeBlockTextDeclareAndInitialiseVariable = param1->className + progLangPointer[progLang] + STRING_SPACE + param1->instanceName + progLangEquals[progLang] + param2->instanceName + progLangEndLine[progLang];	
			printLine(codeBlockTextDeclareAndInitialiseVariable, level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_DECLARE_NEW_VARIABLE)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_DECLARE_NEW_VARIABLE" << endl;
			#endif		
			string codeBlockTextDeclareNewVariable = param1->className + progLangPointer[progLang] + STRING_SPACE + param1->instanceName + progLangEquals[progLang] + progLangNewObject[progLang] + param1->className + progLangOpenParameterSpace[progLang] + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	
			printLine(codeBlockTextDeclareNewVariable, level, code);
		}
		/*
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_CREATE_NEW_LOCAL_LIST_VARIABLE)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_CREATE_NEW_LOCAL_LIST_VARIABLE" << endl;
			#endif			
			#ifdef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES
			string localListDeclarationText = generateCodePropertyListDefinitionTypeText(param1->className, progLang) + generatePropertyListName(param1->instanceName) + progLangEndLine[progLang];	//vector<param1Class*> param1instancePropertyList;
			#else
			string localListDeclarationText = generateCodePropertyListDefinitionText(param1->className, progLang) + progLangEndLine[progLang];	//vector<param1Class*> param1PropertyList;		
			#endif
			printLine(localListDeclarationText, level, code);			
			string codeBlockTextCreate = param1->className + progLangPointer[progLang] + STRING_SPACE + param1->instanceName + progLangEquals[progLang] + progLangNewObject[progLang] + param1->className + progLangOpenParameterSpace[progLang] + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//param1Class * param1 = new param1Class();
			printLine(codeBlockTextCreate, level, code);
			#ifdef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES
			string codeBlockText = generatePropertyListName(param1->instanceName) + progLangFunctionReferenceDelimiter[progLang] + progLangAddProperty[progLang] + progLangOpenParameterSpace[progLang] + param1->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//>param1PropertyList.push_back(param1);
			#else
			string codeBlockText = generatePropertyListName(param1->className) + progLangFunctionReferenceDelimiter[progLang] + progLangAddProperty[progLang] + progLangOpenParameterSpace[progLang] + param1->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//>param1PropertyList.push_back(param1);			
			#endif
			printLine(codeBlockText, level, code);
		}
		*/
		else if(currentCodeBlockInLevel->codeBlockType == NLC_CODEBLOCK_TYPE_DECLARE_NEW_LOCAL_LIST_VARIABLE)
		{
			#ifdef NLC_DEBUG
			cout << "printCodeBlocks: NLC_CODEBLOCK_TYPE_DECLARE_NEW_LOCAL_LIST_VARIABLE" << endl;
			#endif			
			#ifdef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES
			string localListDeclarationText = generateCodePropertyListDefinitionTypeText(param1->className, progLang) + generatePropertyListName(param1->instanceName) + progLangEndLine[progLang];	//vector<param1Class*> param1instancePropertyList;
			#else
			string localListDeclarationText = generateCodePropertyListDefinitionText(param1->className, progLang) + progLangEndLine[progLang];	//vector<param1Class*> param1PropertyList;		
			#endif
			printLine(localListDeclarationText, level, code);			
		}	
		else
		{
			cout << "printCodeBlocks: error: currentCodeBlockInLevel->codeBlockType = " << currentCodeBlockInLevel->codeBlockType << endl;
		}
		/*
		else if(currentCodeBlockInLevel->codeBlockType == ...)
		{
		
		}
		...
		*/
			
		//cout << "z3" << endl;	
		if(currentCodeBlockInLevel->lowerLevel != NULL)
		{
			printCodeBlocks(currentCodeBlockInLevel->lowerLevel, classDefinitionList, progLang, code, (level+1));
			printLine(progLangCloseBlock[progLang], level, code);
		}
		
		//cout << "z4" << endl;
		currentCodeBlockInLevel = currentCodeBlockInLevel->next;
	}
}

string generateCodeConditionPairText(string conditionClassName, string conditionInstanceName, string conditionObjectClassName, string conditionObjectInstanceName, int progLang)
{
	string codeConditionPairTypeText = progLangClassPairTypeStart[progLang] + conditionClassName + progLangPointer[progLang] + progLangClassList2DTypeMiddle[progLang] + conditionObjectClassName + progLangPointer[progLang] + progLangClassPairTypeEnd[progLang] + progLangClassMemberFunctionParametersOpen[progLang] + conditionInstanceName + progLangClassMemberFunctionParametersNext[progLang] + conditionObjectInstanceName + progLangClassMemberFunctionParametersClose[progLang];
	return codeConditionPairTypeText;
}


void generateFunctionExecutionArgumentsWithActionConceptInheritanceString(vector<NLCclassDefinition *> * classDefinitionList, vector<NLCitem*> * codeBlockParameters, string * functionArguments, int progLang)
{
	vector<NLCitem*> * parameters;
	#ifdef NLC_SUPPORT_INPUT_FILE_LISTS
	NLCitem * param1 = codeBlockParameters->at(0);
	//get function arguments from class definition list (in case they have been dynamically updated based on implicit declarations within the function definition)
	bool foundLocalClassDefinition = false;
	NLCclassDefinition * localClassDefinition = findClassDefinition(classDefinitionList, param1->instanceName, &foundLocalClassDefinition);	//see if class definition already exists
	if(foundLocalClassDefinition)
	{
		parameters = &(localClassDefinition->parameters);
	}
	else
	{
		cout << "warning: !foundLocalClassDefinition: param1->instanceName = " << param1->instanceName << endl;
		cout << "(action probably has no subject)." << endl;
		parameters = codeBlockParameters;
	}
	#else		
	parameters = codeBlockParameters;				
	#endif
	//parameters = codeBlockParameters;
			
	for(vector<NLCitem*>::iterator parametersIterator = parameters->begin(); parametersIterator < parameters->end(); parametersIterator++)
	{
		NLCitem * currentItem = *parametersIterator;
		//cout << "currentItem->itemType = " << currentItem->itemType << endl;
		//do: ADD: if(functionArgumentCertified);
		
		if(currentItem->itemType == NLC_ITEM_TYPE_THIS_FUNCTION_ARGUMENT_INSTANCE_PLURAL)		
		{
			if(*functionArguments != "")
			{
				*functionArguments = *functionArguments + progLangClassMemberFunctionParametersNext[progLang];
			}
			*functionArguments = *functionArguments + generateCodeSingularReferenceText(currentItem, progLang);
			//CHECKTHIS; this requires upgrade
		}
		#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS
		else if(currentItem->itemType == NLC_ITEM_TYPE_FUNCTION)		
		{
			if(*functionArguments != "")
			{
				*functionArguments = *functionArguments + progLangClassMemberFunctionParametersNext[progLang];
			}
			*functionArguments = *functionArguments + generateCodeSingularReferenceText(currentItem, progLang);
		}
		#endif
		else if(currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_OBJECT)		
		{
			if(*functionArguments != "")
			{
				*functionArguments = *functionArguments + progLangClassMemberFunctionParametersNext[progLang];
			}
			*functionArguments = *functionArguments + generateCodeSingularReferenceText(currentItem, progLang);
		}
		#ifdef NLC_INTERPRET_ACTION_PROPERTIES_AND_CONDITIONS_AS_FUNCTION_ARGUMENTS
		else if(currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_ARGUMENT_CONDITION)
		{
			if(*functionArguments != "")
			{
				*functionArguments = *functionArguments + progLangClassMemberFunctionParametersNext[progLang];
			}
			*functionArguments = *functionArguments + generateCodeConditionPairReferenceText(currentItem, progLang);
		}
		else if(currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_ARGUMENT_PROPERTY)		
		{
			if(*functionArguments != "")
			{
				*functionArguments = *functionArguments + progLangClassMemberFunctionParametersNext[progLang];
			}
			*functionArguments = *functionArguments + generateCodeSingularReferenceText(currentItem, progLang);
		}		
		#endif
	}
}

string generateCodeSingularReferenceText(NLCitem * functionArgumentItem, int progLang)
{
	string codePropertyTypeText = functionArgumentItem->instanceName;
	#ifdef NLC_SUPPORT_INPUT_FILE_LISTS
	if(functionArgumentItem->functionArgumentPassCastRequired)
	{
		codePropertyTypeText = progLangDynamicCastStart[progLang] + functionArgumentItem->functionArgumentPassCastClassName + progLangDynamicCastEnd[progLang] + progLangOpenParameterSpace[progLang] + functionArgumentItem->instanceName + progLangCloseParameterSpace[progLang];	//dynamic_cast<parentClass*>(childClassInstance); 
	}
	#endif	
	return codePropertyTypeText;
}

string generateInstanceNameWithContext(string instanceName, vector<string> * context, int progLang)
{
	string instanceNameWithContext = "";
	#define IRRELVANT -1
	string contextString = generateStringFromContextVector(context, progLang);
	instanceNameWithContext = contextString + instanceName;
	return instanceNameWithContext;
}

#ifdef NLC_INTERPRET_ACTION_PROPERTIES_AND_CONDITIONS_AS_FUNCTION_ARGUMENTS
string generateCodeConditionPairReferenceText(NLCitem * functionArgumentConditionItem, int progLang)
{
	//do: ADD dynamic_cast<functionArgumentPassCastClassName> if functionArgumentPassCastClassName != ""
	#ifdef NLC_USE_STRING_INDEXED_UNORDERED_MAPS_FOR_CONDITION_LISTS
	string codeConditionPairTypeText = progLangClassPairTypeStart[progLang] + progLangClassList2DTypeConditionTypeVar[progLang] + progLangClassList2DTypeMiddle[progLang] + functionArgumentConditionItem->className + progLangPointer[progLang] + progLangClassPairTypeEnd[progLang] + progLangClassMemberFunctionParametersOpen[progLang] + generateInstanceNameWithContext(functionArgumentConditionItem->instanceName, &(functionArgumentConditionItem->context), progLang) + progLangClassMemberFunctionParametersNext[progLang] + generateInstanceNameWithContext(functionArgumentConditionItem->instanceName2, &(functionArgumentConditionItem->context), progLang) + progLangClassMemberFunctionParametersClose[progLang];
	#else
	string codeConditionPairTypeText = progLangClassPairTypeStart[progLang] + functionArgumentConditionItem->className + progLangPointer[progLang] + progLangClassList2DTypeMiddle[progLang] + functionArgumentConditionItem->className2 + progLangPointer[progLang] + progLangClassPairTypeEnd[progLang] + progLangClassMemberFunctionParametersOpen[progLang] + generateInstanceNameWithContext(functionArgumentConditionItem->instanceName, &(functionArgumentConditionItem->context), progLang) + progLangClassMemberFunctionParametersNext[progLang] + generateInstanceNameWithContext(functionArgumentConditionItem->instanceName2, &(functionArgumentConditionItem->context), progLang) + progLangClassMemberFunctionParametersClose[progLang];			
	#endif
	return codeConditionPairTypeText;
}
#endif


#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS
void generateLocalFunctionArgumentsBasedOnImplicitDeclarationsString(vector<NLCitem*> * parameters, string * functionArguments, int progLang)
{
	for(vector<NLCitem*>::iterator parametersIterator = parameters->begin(); parametersIterator < parameters->end(); parametersIterator++)
	{
		NLCitem * currentItem = *parametersIterator;
		if(currentItem->itemType == NLC_ITEM_TYPE_THIS_FUNCTION_ARGUMENT_INSTANCE_PLURAL)
		{
			if(*functionArguments != "")
			{
				*functionArguments = *functionArguments + progLangClassMemberFunctionParametersNext[progLang];
			}
			#ifdef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES
			*functionArguments = *functionArguments + progLangClassListTypeStart[progLang] + currentItem->className + progLangPointer[progLang] + progLangClassListTypeEnd[progLang] + currentItem->instanceName + NLC_ITEM_TYPE_PROPERTYLISTVAR_APPENDITION;			
			#else
			*functionArguments = *functionArguments + progLangClassListTypeStart[progLang] + currentItem->className + progLangPointer[progLang] + progLangClassListTypeEnd[progLang] + currentItem->className + NLC_ITEM_TYPE_PROPERTYLISTVAR_APPENDITION;
			#endif
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
		//cout << "\tcurrentItem->itemType = " << currentItem->itemType << endl;
		//cout << "currentItem->instanceName = " << currentItem->instanceName << endl;
		if(currentItem->itemType == NLC_ITEM_TYPE_FUNCTION)
		{
			if(*functionArguments != "")
			{
				*functionArguments = *functionArguments + progLangClassMemberFunctionParametersNext[progLang];
			}
			*functionArguments = *functionArguments + currentItem->className + progLangPointer[progLang] + STRING_SPACE + currentItem->instanceName;
		}
		else if(currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_OBJECT)
		{
			if(*functionArguments != "")
			{
				*functionArguments = *functionArguments + progLangClassMemberFunctionParametersNext[progLang];
			}
			*functionArguments = *functionArguments + currentItem->className + progLangPointer[progLang] + STRING_SPACE + currentItem->instanceName;
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
		if(currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_OWNER)
		{
			functionOwnerContext = currentItem->className + progLangFunctionOwnerClassDelimiter[progLang];
			foundFunctionOwner = true;
		}
	}
	#endif
	if(!foundFunctionOwner)
	{
		functionOwnerContext = progLangClassMemberFunctionType[progLang];
	}
	return functionOwnerContext;
}


string generateStringFromContextVector(vector<string> * context, int progLang)
{
	string contextString = "";
	for(vector<string>::iterator contextIterator = context->begin(); contextIterator < context->end(); contextIterator++)
	{
		string currentContext = *contextIterator;
		/*
		string delimiter = "":
		if(progLang == NLC_PROGRAMMING_LANGUAGE_DEFAULT)
		{
			delimiter = progLangObjectReferenceDelimiter[progLang];
		}
		else
		{
			cout << "error: generateStringFromContextVector() only yet finished for NLC_PROGRAMMING_LANGUAGE_DEFAULT" << endl; 
		}
		*/
		contextString = currentContext + progLangObjectReferenceDelimiter[progLang] + contextString;
	}
	
	#ifdef NLC_PRINT_EXPLICIT_LOCAL_CONTEXT
	if(contextString == "")
	{
		contextString = string(NLC_LOCAL_CONTEXT_NAME) + progLangObjectReferenceDelimiter[progLang];
	}
	#endif
	
	return contextString;
}