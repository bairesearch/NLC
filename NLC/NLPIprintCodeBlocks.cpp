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
 * File Name: NLPIprintCodeBlocks.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2013 Baxter AI (baxterai.com)
 * Project: Natural Language Programming Interface (compiler)
 * Project Version: 1e9a 25-November-2013
 * Requirements: requires text parsed by NLP Parser (eg Relex; available in .CFF format <relations>)
 *
 *******************************************************************************/



#include <ctime>
#include <cstdlib>	//for random number generation
#include <cmath>

#include "NLPIprintCodeBlocks.h"
#include "NLPIprintDefs.h"

bool printCodeBlocks(NLPIcodeblock * firstCodeBlockInLevel, vector<NLPIclassDefinition *> * classDefinitionList, int progLang, string * code, int level)
{
	NLPIcodeblock * currentCodeBlockInLevel = firstCodeBlockInLevel;
	while(currentCodeBlockInLevel->next != NULL)
	{
		//cout << "z1" << endl;
		NLPIitem * param1 = currentCodeBlockInLevel->parameters.at(0);
		string contextParam1 = generateStringFromContextVector(&(param1->context), progLang);
		
		//cout << "z2" << endl;	
		if(currentCodeBlockInLevel->codeBlockType == NLPI_CODEBLOCK_TYPE_EXECUTE_FUNCTION)
		{
			#ifdef NLPI_DEBUG
			cout << "printCodeBlocks: NLPI_CODEBLOCK_TYPE_EXECUTE_FUNCTION" << endl;
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
		else if(currentCodeBlockInLevel->codeBlockType == NLPI_CODEBLOCK_TYPE_ADD_NEW_PROPERTY)
		{
			#ifdef NLPI_DEBUG
			cout << "printCodeBlocks: NLPI_CODEBLOCK_TYPE_ADD_NEW_PROPERTY" << endl;
			#endif
			NLPIitem * param2 = currentCodeBlockInLevel->parameters.at(1);	
			//string contextParam2 = generateStringFromContextVector(&(param2->context), progLang);
			
			string codeBlockTextCreate = param2->className + progLangPointer[progLang] + STRING_SPACE + param2->instanceName + progLangEquals[progLang] + progLangNewObject[progLang] + param2->className + progLangOpenParameterSpace[progLang] + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	
			printLine(codeBlockTextCreate, level, code);
			string codeBlockText = contextParam1 + param1->instanceName + progLangObjectReferenceDelimiter[progLang] + param2->className + NLPI_ITEM_TYPE_PROPERTYLISTVAR_APPENDITION + progLangFunctionReferenceDelimiter[progLang] + progLangAddProperty[progLang] + progLangOpenParameterSpace[progLang] + param2->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//context1->param1->param2PropertyList.push_back(param2);
			printLine(codeBlockText, level, code);
		}	
		else if(currentCodeBlockInLevel->codeBlockType == NLPI_CODEBLOCK_TYPE_ADD_NEW_CONDITION)
		{
			#ifdef NLPI_DEBUG
			cout << "printCodeBlocks: NLPI_CODEBLOCK_TYPE_ADD_NEW_CONDITION" << endl;
			#endif
			NLPIitem * param2 = currentCodeBlockInLevel->parameters.at(1);	
			NLPIitem * param3 = currentCodeBlockInLevel->parameters.at(2);	
			//string contextParam3 = generateStringFromContextVector(&(param3->context), progLang);
			string codeBlockTextCreate = param3->className + progLangPointer[progLang] + STRING_SPACE + param3->instanceName + progLangEquals[progLang] + progLangNewObject[progLang] + param3->className + progLangOpenParameterSpace[progLang] + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];
			printLine(codeBlockTextCreate, level, code);
			#ifdef NLPI_USE_STRING_INDEXED_UNORDERED_MAPS_FOR_CONDITION_LISTS
			string codeBlockText = contextParam1 + param1->instanceName + progLangObjectReferenceDelimiter[progLang] + param3->className + NLPI_ITEM_TYPE_CONDITIONLISTVAR_APPENDITION + progLangFunctionReferenceDelimiter[progLang] + progLangAddCondition[progLang] + progLangOpenParameterSpace[progLang] + progLangStringOpenClose[progLang] + param2->className + progLangStringOpenClose[progLang] + progLangParameterSpaceNextParam[progLang] + param3->instanceName + progLangCloseParameterSpace[progLang] + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		
			#else
			string codeBlockTextCreate2 = param2->className + progLangPointer[progLang] + STRING_SPACE + param2->instanceName + progLangEquals[progLang] + progLangNewObject[progLang] + param2->className + progLangOpenParameterSpace[progLang] + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];
			string codeBlockText = contextParam1 + param1->instanceName + progLangObjectReferenceDelimiter[progLang] + generateConditionListName(param2->className,  param3->className) + progLangFunctionReferenceDelimiter[progLang] + progLangAddCondition[progLang] + progLangOpenParameterSpace[progLang] + param2->instanceName + progLangParameterSpaceNextParam[progLang] + STRING_SPACE + param3->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//context1->param1->param2param3ConditionList.insert(param2, param3);	
			printLine(codeBlockTextCreate2, level, code);
			#endif
			printLine(codeBlockText, level, code);

		}
		else if(currentCodeBlockInLevel->codeBlockType == NLPI_CODEBLOCK_TYPE_ADD_PROPERTY)
		{
			#ifdef NLPI_DEBUG
			cout << "printCodeBlocks: NLPI_CODEBLOCK_TYPE_ADD_PROPERTY" << endl;
			#endif
			NLPIitem * param2 = currentCodeBlockInLevel->parameters.at(1);	
			//string contextParam2 = generateStringFromContextVector(&(param2->context), progLang);
			
			string codeBlockText = contextParam1 + param1->instanceName + progLangObjectReferenceDelimiter[progLang] + param2->className + NLPI_ITEM_TYPE_PROPERTYLISTVAR_APPENDITION + progLangFunctionReferenceDelimiter[progLang] + progLangAddProperty[progLang] + progLangOpenParameterSpace[progLang] + param2->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//context1->param1->param2PropertyList.push_back(param2);
			printLine(codeBlockText, level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLPI_CODEBLOCK_TYPE_ADD_PROPERTY_TO_LOCAL_LIST)
		{
			#ifdef NLPI_DEBUG
			cout << "printCodeBlocks: NLPI_CODEBLOCK_TYPE_ADD_PROPERTY_TO_LOCAL_LIST" << endl;
			#endif
			NLPIitem * param2 = currentCodeBlockInLevel->parameters.at(1);	
			
			#ifdef NLPI_LOCAL_LISTS_USE_INSTANCE_NAMES
			string codeBlockText = generatePropertyListName(param1->instanceName) + progLangFunctionReferenceDelimiter[progLang] + progLangAddProperty[progLang] + progLangOpenParameterSpace[progLang] + param2->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//param1instancePropertyList.push_back(param2);
			#else
			string codeBlockText = generatePropertyListName(param1->className) + progLangFunctionReferenceDelimiter[progLang] + progLangAddProperty[progLang] + progLangOpenParameterSpace[progLang] + param2->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//param1instancePropertyList.push_back(param2);			
			#endif
			printLine(codeBlockText, level, code);
		}	
		else if(currentCodeBlockInLevel->codeBlockType == NLPI_CODEBLOCK_TYPE_ADD_CONDITION)
		{
			#ifdef NLPI_DEBUG
			cout << "printCodeBlocks: NLPI_CODEBLOCK_TYPE_ADD_CONDITION" << endl;
			#endif
			NLPIitem * param2 = currentCodeBlockInLevel->parameters.at(1);	
			NLPIitem * param3 = currentCodeBlockInLevel->parameters.at(2);	
			//string contextParam3 = generateStringFromContextVector(&(param3->context), progLang);
			#ifdef NLPI_USE_STRING_INDEXED_UNORDERED_MAPS_FOR_CONDITION_LISTS
			string codeBlockText = contextParam1 + param1->instanceName + progLangObjectReferenceDelimiter[progLang] + param3->className + NLPI_ITEM_TYPE_CONDITIONLISTVAR_APPENDITION + progLangFunctionReferenceDelimiter[progLang] + progLangAddCondition[progLang] + progLangOpenParameterSpace[progLang] + progLangStringOpenClose[progLang] + param2->className + progLangStringOpenClose[progLang] + progLangParameterSpaceNextParam[progLang] + param3->instanceName + progLangCloseParameterSpace[progLang] + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		
			#else
			string codeBlockTextCreate2 = param2->className + progLangPointer[progLang] + STRING_SPACE + param2->instanceName + progLangEquals[progLang] + progLangNewObject[progLang] + param2->className + progLangOpenParameterSpace[progLang] + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];
			string codeBlockText = contextParam1 + param1->instanceName + progLangObjectReferenceDelimiter[progLang] + generateConditionListName(param2->className,  param3->className) + progLangFunctionReferenceDelimiter[progLang] + progLangAddCondition[progLang] + progLangOpenParameterSpace[progLang] + param2->instanceName + progLangParameterSpaceNextParam[progLang] + STRING_SPACE + param3->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//context1->param1->param2param3ConditionList.insert(param2, param3);	
			printLine(codeBlockTextCreate2, level, code);
			#endif
			printLine(codeBlockText, level, code);

		}			
		else if(currentCodeBlockInLevel->codeBlockType == NLPI_CODEBLOCK_TYPE_FOR_PROPERTY_LIST)
		{
			#ifdef NLPI_DEBUG
			cout << "printCodeBlocks: NLPI_CODEBLOCK_TYPE_FOR_PROPERTY_LIST" << endl;
			#endif
			string codeBlockText = progLangFor[progLang] + progLangForIterPart1[progLang] + generateCodePropertyListDefinitionTypeText(param1->className, progLang) + progLangForIterPart2[progLang] + contextParam1 + generatePropertyListName(param1->className) + progLangForIterPart3[progLang] + contextParam1 + generatePropertyListName(param1->className) + progLangForIterPart4[progLang];
			printLine(codeBlockText, level, code);
			printLine(progLangOpenBlock[progLang], level, code);
			string tempVarDeclarationText = param1->className + progLangPointer[progLang] + STRING_SPACE + param1->instanceName + progLangEquals[progLang] + progLangPointer[progLang] + progLangForIterName[progLang] + progLangEndLine[progLang];	//OLD:  param1->className + NLPI_ITEM_TYPE_TEMPVAR_APPENDITION
			printLine(tempVarDeclarationText, (level+1), code);

			//?cout << "error: printCodeBlocks() only yet finished for NLPI_PROGRAMMING_LANGUAGE_DEFAULT" << endl; 
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLPI_CODEBLOCK_TYPE_FOR_PROPERTY_LIST_LOCAL)
		{
			#ifdef NLPI_DEBUG
			cout << "printCodeBlocks: NLPI_CODEBLOCK_TYPE_FOR_PROPERTY_LIST_LOCAL" << endl;
			#endif
			#ifdef NLPI_LOCAL_LISTS_USE_INSTANCE_NAMES
			string codeBlockText = progLangFor[progLang] + progLangForIterPart1[progLang] + generateCodePropertyListDefinitionTypeText(param1->className, progLang) + progLangForIterPart2[progLang] + generatePropertyListName(param1->instanceName) + progLangForIterPart3[progLang] + generatePropertyListName(param1->instanceName) + progLangForIterPart4[progLang];
			#else
			string codeBlockText = progLangFor[progLang] + progLangForIterPart1[progLang] + generateCodePropertyListDefinitionTypeText(param1->className, progLang) + progLangForIterPart2[progLang] + generatePropertyListName(param1->className) + progLangForIterPart3[progLang] + generatePropertyListName(param1->className) + progLangForIterPart4[progLang];			
			#endif
			printLine(codeBlockText, level, code);
			printLine(progLangOpenBlock[progLang], level, code);
			string tempVarDeclarationText = param1->className + progLangPointer[progLang] + STRING_SPACE + param1->instanceName + progLangEquals[progLang] + progLangPointer[progLang] + progLangForIterName[progLang] + progLangEndLine[progLang];	//OLD:  param1->className + NLPI_ITEM_TYPE_TEMPVAR_APPENDITION
			printLine(tempVarDeclarationText, (level+1), code);

			//?cout << "error: printCodeBlocks() only yet finished for NLPI_PROGRAMMING_LANGUAGE_DEFAULT" << endl; 
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLPI_CODEBLOCK_TYPE_FOR_CONDITION_LIST)
		{
			#ifdef NLPI_DEBUG
			cout << "printCodeBlocks: NLPI_CODEBLOCK_TYPE_FOR_CONDITION_LIST" << endl;
			#endif
			NLPIitem * param2 = currentCodeBlockInLevel->parameters.at(1);
			string codeBlockText = progLangFor[progLang] + progLangForIterPart1[progLang] + generateCodeConditionListDefinitionTypeText(param1->className, param2->className, progLang) + progLangForIterPart2[progLang] + contextParam1 + generateConditionListName(param1->className, param2->className) + progLangForIterPart3[progLang] + contextParam1 + generateConditionListName(param1->className, param2->className) + progLangForIterPart4[progLang];
			printLine(codeBlockText, level, code);
			printLine(progLangOpenBlock[progLang], level, code);
			string tempVarDeclarationText = param2->className + progLangPointer[progLang] + STRING_SPACE + param2->instanceName + progLangEquals[progLang] + progLangForIterName[progLang] + progLangForIterConditionObjectReference[progLang] + progLangEndLine[progLang];
			printLine(tempVarDeclarationText, (level+1), code);

			//?cout << "error: printCodeBlocks() only yet finished for NLPI_PROGRAMMING_LANGUAGE_DEFAULT" << endl; 
		}		
		else if(currentCodeBlockInLevel->codeBlockType == NLPI_CODEBLOCK_TYPE_NEW_FUNCTION)
		{
			#ifdef NLPI_DEBUG
			cout << "printCodeBlocks: NLPI_CODEBLOCK_TYPE_NEW_FUNCTION" << endl;
			#endif
			string functionArguments = "";
			#ifdef NLPI_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS
			generateLocalFunctionArgumentsBasedOnImplicitDeclarationsString(&(currentCodeBlockInLevel->parameters), &functionArguments, progLang);
			#endif	
			#ifdef NLPI_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS
			generateFunctionArgumentsBasedOnActionAndActionObjectVars(&(currentCodeBlockInLevel->parameters), &functionArguments, progLang);
			#endif
			string functionOwnerContext = generateFunctionOwnerContext(&(currentCodeBlockInLevel->parameters), progLang);
			string codeBlockText = functionOwnerContext + param1->functionName + progLangOpenParameterSpace[progLang] + functionArguments + progLangCloseParameterSpace[progLang];	//main(){
			printLine(codeBlockText, level, code);		
			printLine(progLangOpenBlock[progLang], level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLPI_CODEBLOCK_TYPE_IF_HAS_PROPERTY)
		{
			#ifdef NLPI_DEBUG
			cout << "printCodeBlocks: NLPI_CODEBLOCK_TYPE_IF_HAS_PROPERTY" << endl;
			#endif
			NLPIitem * param2 = currentCodeBlockInLevel->parameters.at(1);	
			string contextParam2 = generateStringFromContextVector(&(param2->context), progLang);	//IS THIS REQUIRED????
			
			string codeBlockText = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + progLangNot[progLang] + progLangOpenParameterSpace[progLang] + contextParam1 + param1->instanceName + progLangFunctionReferenceDelimiter[progLang] + param2->className + NLPI_ITEM_TYPE_PROPERTYLISTVAR_APPENDITION + progLangFunctionReferenceDelimiter[progLang] + progLangFindProperty[progLang] + progLangOpenParameterSpace[progLang] + progLangCloseParameterSpace[progLang] + progLangCloseParameterSpace[progLang] + progLangCloseParameterSpace[progLang];		//if(!(context1->param1->param2PropertyList.empty())){	
			printLine(codeBlockText, level, code);
			printLine(progLangOpenBlock[progLang], level, code);
		}		
		else if(currentCodeBlockInLevel->codeBlockType == NLPI_CODEBLOCK_TYPE_IF_HAS_CONDITION)
		{
			#ifdef NLPI_DEBUG
			cout << "printCodeBlocks: NLPI_CODEBLOCK_TYPE_IF_HAS_CONDITION" << endl;
			#endif
			NLPIitem * param2 = currentCodeBlockInLevel->parameters.at(1);		
			NLPIitem * param3 = currentCodeBlockInLevel->parameters.at(2);
			string contextParam3 = generateStringFromContextVector(&(param3->context), progLang);
				
			string codeBlockText = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + progLangNot[progLang] + progLangOpenParameterSpace[progLang] + contextParam1 + param1->instanceName + progLangFunctionReferenceDelimiter[progLang] + generateConditionListName(param2->className, param3->className) + progLangFunctionReferenceDelimiter[progLang] + progLangFindCondition[progLang] + progLangOpenParameterSpace[progLang] + progLangCloseParameterSpace[progLang] + progLangCloseParameterSpace[progLang] + progLangCloseParameterSpace[progLang];	//if(!(context1->param1->param2param3ConditionList.empty())){	
			printLine(codeBlockText, level, code);
			printLine(progLangOpenBlock[progLang], level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLPI_CODEBLOCK_TYPE_DECLARE_AND_INITIALISE_VARIABLE)
		{
			#ifdef NLPI_DEBUG
			cout << "printCodeBlocks: NLPI_CODEBLOCK_TYPE_DECLARE_AND_INITIALISE_VARIABLE" << endl;
			#endif
			NLPIitem * param2 = currentCodeBlockInLevel->parameters.at(1);	
			
			string codeBlockTextDeclareAndInitialiseVariable = param1->className + progLangPointer[progLang] + STRING_SPACE + param1->instanceName + progLangEquals[progLang] + param2->instanceName + progLangEndLine[progLang];	
			printLine(codeBlockTextDeclareAndInitialiseVariable, level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLPI_CODEBLOCK_TYPE_DECLARE_NEW_VARIABLE)
		{
			#ifdef NLPI_DEBUG
			cout << "printCodeBlocks: NLPI_CODEBLOCK_TYPE_DECLARE_NEW_VARIABLE" << endl;
			#endif		
			string codeBlockTextDeclareNewVariable = param1->className + progLangPointer[progLang] + STRING_SPACE + param1->instanceName + progLangEquals[progLang] + progLangNewObject[progLang] + param1->className + progLangOpenParameterSpace[progLang] + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	
			printLine(codeBlockTextDeclareNewVariable, level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLPI_CODEBLOCK_TYPE_CREATE_NEW_LOCAL_LIST_VARIABLE)
		{
			#ifdef NLPI_DEBUG
			cout << "printCodeBlocks: NLPI_CODEBLOCK_TYPE_CREATE_NEW_LOCAL_LIST_VARIABLE" << endl;
			#endif			
			#ifdef NLPI_LOCAL_LISTS_USE_INSTANCE_NAMES
			string localListDeclarationText = generateCodePropertyListDefinitionText(param1->instanceName, progLang) + progLangEndLine[progLang];	//vector<param1Class*> param1PropertyList;
			#else
			string localListDeclarationText = generateCodePropertyListDefinitionText(param1->className, progLang) + progLangEndLine[progLang];	//vector<param1Class*> param1PropertyList;		
			#endif
			printLine(localListDeclarationText, level, code);			
			string codeBlockTextCreate = param1->className + progLangPointer[progLang] + STRING_SPACE + param1->instanceName + progLangEquals[progLang] + progLangNewObject[progLang] + param1->className + progLangOpenParameterSpace[progLang] + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//param1Class * param1 = new param1Class();
			printLine(codeBlockTextCreate, level, code);
			#ifdef NLPI_LOCAL_LISTS_USE_INSTANCE_NAMES
			string codeBlockText = generatePropertyListName(param1->instanceName) + progLangFunctionReferenceDelimiter[progLang] + progLangAddProperty[progLang] + progLangOpenParameterSpace[progLang] + param1->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//>param1PropertyList.push_back(param1);
			#else
			string codeBlockText = generatePropertyListName(param1->className) + progLangFunctionReferenceDelimiter[progLang] + progLangAddProperty[progLang] + progLangOpenParameterSpace[progLang] + param1->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//>param1PropertyList.push_back(param1);			
			#endif
			printLine(codeBlockText, level, code);
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


void generateFunctionExecutionArgumentsWithActionConceptInheritanceString(vector<NLPIclassDefinition *> * classDefinitionList, vector<NLPIitem*> * codeBlockParameters, string * functionArguments, int progLang)
{
	vector<NLPIitem*> * parameters;
	#ifdef NLPI_SUPPORT_INPUT_FILE_LISTS
	NLPIitem * param1 = codeBlockParameters->at(0);
	//get function arguments from class definition list (in case they have been dynamically updated based on implicit declarations within the function definition)
	bool foundLocalClassDefinition = false;
	NLPIclassDefinition * localClassDefinition = findClassDefinition(classDefinitionList, param1->instanceName, &foundLocalClassDefinition);	//see if class definition already exists
	if(foundLocalClassDefinition)
	{
		parameters = &(localClassDefinition->parameters);
	}
	else
	{
		cout << "error: !foundLocalClassDefinition: param1->instanceName = " << param1->instanceName << endl;
	}
	#else		
	parameters = codeBlockParameters;				
	#endif
	//parameters = codeBlockParameters;
			
	for(vector<NLPIitem*>::iterator parametersIterator = parameters->begin(); parametersIterator < parameters->end(); parametersIterator++)
	{
		NLPIitem * currentItem = *parametersIterator;
		//cout << "currentItem->itemType = " << currentItem->itemType << endl;
		//do: ADD: if(functionArgumentCertified);
		
		if(currentItem->itemType == NLPI_ITEM_TYPE_THIS_FUNCTION_ARGUMENT_INSTANCE_PLURAL)		
		{
			if(*functionArguments != "")
			{
				*functionArguments = *functionArguments + progLangClassMemberFunctionParametersNext[progLang];
			}
			*functionArguments = *functionArguments + generateCodeSingularReferenceText(currentItem, progLang);
			//CHECKTHIS; this requires upgrade
		}
		#ifdef NLPI_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS
		else if(currentItem->itemType == NLPI_ITEM_TYPE_FUNCTION)		
		{
			if(*functionArguments != "")
			{
				*functionArguments = *functionArguments + progLangClassMemberFunctionParametersNext[progLang];
			}
			*functionArguments = *functionArguments + generateCodeSingularReferenceText(currentItem, progLang);
		}
		#endif
		else if(currentItem->itemType == NLPI_ITEM_TYPE_FUNCTION_OBJECT)		
		{
			if(*functionArguments != "")
			{
				*functionArguments = *functionArguments + progLangClassMemberFunctionParametersNext[progLang];
			}
			*functionArguments = *functionArguments + generateCodeSingularReferenceText(currentItem, progLang);
		}
		#ifdef NLPI_INTERPRET_ACTION_PROPERTIES_AND_CONDITIONS_AS_FUNCTION_ARGUMENTS
		else if(currentItem->itemType == NLPI_ITEM_TYPE_FUNCTION_ARGUMENT_CONDITION)
		{
			if(*functionArguments != "")
			{
				*functionArguments = *functionArguments + progLangClassMemberFunctionParametersNext[progLang];
			}
			*functionArguments = *functionArguments + generateCodeConditionPairReferenceText(currentItem, progLang);
		}
		else if(currentItem->itemType == NLPI_ITEM_TYPE_FUNCTION_ARGUMENT_PROPERTY)		
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

string generateCodeSingularReferenceText(NLPIitem * functionArgumentItem, int progLang)
{
	string codePropertyTypeText = functionArgumentItem->instanceName;
	#ifdef NLPI_SUPPORT_INPUT_FILE_LISTS
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

#ifdef NLPI_INTERPRET_ACTION_PROPERTIES_AND_CONDITIONS_AS_FUNCTION_ARGUMENTS
string generateCodeConditionPairReferenceText(NLPIitem * functionArgumentConditionItem, int progLang)
{
	//do: ADD dynamic_cast<functionArgumentPassCastClassName> if functionArgumentPassCastClassName != ""
	#ifdef NLPI_USE_STRING_INDEXED_UNORDERED_MAPS_FOR_CONDITION_LISTS
	string codeConditionPairTypeText = progLangClassPairTypeStart[progLang] + progLangClassList2DTypeConditionTypeVar[progLang] + progLangClassList2DTypeMiddle[progLang] + functionArgumentConditionItem->className + progLangPointer[progLang] + progLangClassPairTypeEnd[progLang] + progLangClassMemberFunctionParametersOpen[progLang] + generateInstanceNameWithContext(functionArgumentConditionItem->instanceName, &(functionArgumentConditionItem->context), progLang) + progLangClassMemberFunctionParametersNext[progLang] + generateInstanceNameWithContext(functionArgumentConditionItem->instanceName2, &(functionArgumentConditionItem->context), progLang) + progLangClassMemberFunctionParametersClose[progLang];
	#else
	string codeConditionPairTypeText = progLangClassPairTypeStart[progLang] + functionArgumentConditionItem->className + progLangPointer[progLang] + progLangClassList2DTypeMiddle[progLang] + functionArgumentConditionItem->className2 + progLangPointer[progLang] + progLangClassPairTypeEnd[progLang] + progLangClassMemberFunctionParametersOpen[progLang] + generateInstanceNameWithContext(functionArgumentConditionItem->instanceName, &(functionArgumentConditionItem->context), progLang) + progLangClassMemberFunctionParametersNext[progLang] + generateInstanceNameWithContext(functionArgumentConditionItem->instanceName2, &(functionArgumentConditionItem->context), progLang) + progLangClassMemberFunctionParametersClose[progLang];			
	#endif
	return codeConditionPairTypeText;
}
#endif


#ifdef NLPI_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS
void generateLocalFunctionArgumentsBasedOnImplicitDeclarationsString(vector<NLPIitem*> * parameters, string * functionArguments, int progLang)
{
	for(vector<NLPIitem*>::iterator parametersIterator = parameters->begin(); parametersIterator < parameters->end(); parametersIterator++)
	{
		NLPIitem * currentItem = *parametersIterator;
		if(currentItem->itemType == NLPI_ITEM_TYPE_THIS_FUNCTION_ARGUMENT_INSTANCE_PLURAL)
		{
			if(*functionArguments != "")
			{
				*functionArguments = *functionArguments + progLangClassMemberFunctionParametersNext[progLang];
			}
			*functionArguments = *functionArguments + progLangClassListTypeStart[progLang] + currentItem->className + progLangPointer[progLang] + progLangClassListTypeEnd[progLang] + currentItem->className + NLPI_ITEM_TYPE_PROPERTYLISTVAR_APPENDITION;
		}
	}
}		
#endif

#ifdef NLPI_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS
void generateFunctionArgumentsBasedOnActionAndActionObjectVars(vector<NLPIitem*> * parameters, string * functionArguments, int progLang)
{
	for(vector<NLPIitem*>::iterator parametersIterator = parameters->begin(); parametersIterator < parameters->end(); parametersIterator++)
	{
		NLPIitem * currentItem = *parametersIterator;
		//cout << "\tcurrentItem->itemType = " << currentItem->itemType << endl;
		//cout << "currentItem->instanceName = " << currentItem->instanceName << endl;
		if(currentItem->itemType == NLPI_ITEM_TYPE_FUNCTION)
		{
			if(*functionArguments != "")
			{
				*functionArguments = *functionArguments + progLangClassMemberFunctionParametersNext[progLang];
			}
			*functionArguments = *functionArguments + currentItem->className + progLangPointer[progLang] + STRING_SPACE + currentItem->instanceName;
		}
		else if(currentItem->itemType == NLPI_ITEM_TYPE_FUNCTION_OBJECT)
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
			


string generateFunctionOwnerContext(vector<NLPIitem*> * parameters, int progLang)
{
	bool foundFunctionOwner = false;
	string functionOwnerContext = "";
	#ifdef NLPI_SUPPORT_INPUT_FILE_LISTS
	for(vector<NLPIitem*>::iterator parametersIterator = parameters->begin(); parametersIterator < parameters->end(); parametersIterator++)
	{
		NLPIitem * currentItem = *parametersIterator;
		if(currentItem->itemType == NLPI_ITEM_TYPE_FUNCTION_OWNER)
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
		if(progLang == NLPI_PROGRAMMING_LANGUAGE_DEFAULT)
		{
			delimiter = progLangObjectReferenceDelimiter[progLang];
		}
		else
		{
			cout << "error: generateStringFromContextVector() only yet finished for NLPI_PROGRAMMING_LANGUAGE_DEFAULT" << endl; 
		}
		*/
		contextString = currentContext + progLangObjectReferenceDelimiter[progLang] + contextString;
	}
	
	#ifdef NLPI_PRINT_EXPLICIT_LOCAL_CONTEXT
	if(contextString == "")
	{
		contextString = string(NLPI_LOCAL_CONTEXT_NAME) + progLangObjectReferenceDelimiter[progLang];
	}
	#endif
	
	return contextString;
}
