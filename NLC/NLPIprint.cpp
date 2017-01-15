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
 * File Name: NLPIprint.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2013 Baxter AI (baxterai.com)
 * Project: Natural Language Programming Interface (compiler)
 * Project Version: 1c2a 27-October-2013
 * Requirements: requires text parsed by NLP Parser (eg Relex; available in .CFF format <relations>)
 *
 *******************************************************************************/



#include <ctime>
#include <cstdlib>	//for random number generation
#include <cmath>

#include "NLPIprint.h"

bool printCode(NLPIcodeblock * firstCodeBlockInLevel, vector<NLPIclassDefinition *> * classDefinitionList, int progLang, string * code)
{
	bool result = true;
	
	if(!printClassDefinitions(classDefinitionList, progLang, code))
	{
		result = false;
	}
	
	int level = 0;
	if(!printCodeBlocks(firstCodeBlockInLevel, progLang, code, level))
	{
		result = false;
	}

	return result;
}

/*
class className
{
public:

	className(void);
	~className(void);
	
	string name;
	
	vector<somevar *> somevarPropertyList;	//subclass
	....
	
	vector<somevar *> somevarDefinitionList;	//inherited parents
	
	...
	vector<somevar *> somevarFunctionList;
	...
};
*/
bool printClassDefinitions(vector<NLPIclassDefinition *> * classDefinitionList, int progLang, string * code)
{
	for(vector<NLPIclassDefinition*>::iterator classDefinitionIter = classDefinitionList->begin(); classDefinitionIter != classDefinitionList->end(); classDefinitionIter++)
	{	
		NLPIclassDefinition * classDefinition = *classDefinitionIter;
		
		#ifndef NLPI_BAD_IMPLEMENTATION
		if(!(classDefinition->isActionOrConditionInstanceNotClass))
		{
		#endif
			string className = classDefinition->name;
			string classDefinitionEntryText = progLangClassTitlePrepend[progLang] + className;

			bool foundDefinition = false;
			for(vector<NLPIclassDefinition*>::iterator localListIter = classDefinition->definitionList.begin(); localListIter != classDefinition->definitionList.end(); localListIter++)
			{
				if(!foundDefinition)
				{
					foundDefinition = true;
					classDefinitionEntryText = classDefinitionEntryText + " : ";
				}
				else
				{
					classDefinitionEntryText = classDefinitionEntryText + ", ";
				}
				NLPIclassDefinition * targetClassDefinition = *localListIter;
				string targetName = targetClassDefinition->name;
				classDefinitionEntryText = classDefinitionEntryText + progLangClassInheritanceHeader[progLang] + targetName;
			}
			printLine(classDefinitionEntryText, 0, code);
			printLine(progLangOpenClass[progLang], 0, code);
			printLine(progLangClassIntro[progLang], 0, code);
			string classConstructorDeclaration = className + progLangClassConstructorDestructorAppend[progLang];
			printLine(classConstructorDeclaration, 1, code);
			string classDestructorDeclaration = progLangClassDestructorPrepend[progLang] + className + progLangClassConstructorDestructorAppend[progLang];
			printLine(classDestructorDeclaration, 1, code);
			//printLine("", 1, code);
			//string classNameCode = progLangClassNameVariableType[progLang] + progLangClassNameVariableName[progLang] + progLangStringOpenClose[progLang] + className + progLangStringOpenClose[progLang] + progLangEndLine[progLang];
			//printLine(classNameCode, 1, code);
			//printLine("", 1, code);

			//cout << "className = " << className << endl;

			for(vector<NLPIclassDefinition*>::iterator localListIter = classDefinition->propertyList.begin(); localListIter != classDefinition->propertyList.end(); localListIter++)
			{
				NLPIclassDefinition * targetClassDefinition = *localListIter;			
				string propertyClassName = targetClassDefinition->name;
				string localListDeclarationText = generateCodePropertyListDefinitionText(propertyClassName, progLang) + progLangEndLine[progLang];
				printLine(localListDeclarationText, 1, code);	
			}

			for(vector<NLPIclassDefinition*>::iterator localListIter = classDefinition->conditionList.begin(); localListIter != classDefinition->conditionList.end(); localListIter++)
			{
				NLPIclassDefinition * targetClassDefinition = *localListIter;
				//string targetName = targetClassDefinition->name;	//condition instance name not used
				string conditionObjectClassName = "";
				if(!(targetClassDefinition->actionOrConditionInstance->conditionObjectEntity->empty()))
				{
					conditionObjectClassName = generateClassName((targetClassDefinition->actionOrConditionInstance->conditionObjectEntity->back())->entity);
				}
				string conditionClassName = generateClassName(targetClassDefinition->actionOrConditionInstance);	//special case (as actions and conditions are referenced by instance)
				string localListDeclarationText = generateCodeConditionListDefinitionText(conditionClassName, conditionObjectClassName, progLang) + progLangEndLine[progLang];
				printLine(localListDeclarationText, 1, code);
			}

			for(vector<NLPIclassDefinition*>::iterator localListIter = classDefinition->functionList.begin(); localListIter != classDefinition->functionList.end(); localListIter++)
			{
				NLPIclassDefinition * targetClassDefinition = *localListIter;
				string targetName = targetClassDefinition->name;
				string functionArguments = "";
				if(!(targetClassDefinition->actionOrConditionInstance->actionObjectEntity->empty()))
				{
					GIAentityNode * actionObject = (targetClassDefinition->actionOrConditionInstance->actionObjectEntity->back())->entity;
					functionArguments = generateClassName(actionObject) + progLangPointer[progLang] + STRING_SPACE + generateInstanceName(actionObject);
				}
				#ifdef NLPI_INTERPRET_ACTION_PROPERTIES_AND_CONDITIONS_AS_FUNCTION_ARGUMENTS
				functionArguments = generateFunctionPropertyConditionArgumentsWithActionConceptInheritance(targetClassDefinition->actionOrConditionInstance, functionArguments, progLang);
				#endif
				string localListDeclarationText = progLangClassMemberFunctionType[progLang] + targetName + progLangClassMemberFunctionParametersOpen[progLang] + functionArguments + progLangClassMemberFunctionParametersClose[progLang] + progLangEndLine[progLang];
				printLine(localListDeclarationText, 1, code);
			}

			printLine(progLangCloseClass[progLang], 0, code);
			printLine("", 0, code);
		#ifndef NLPI_BAD_IMPLEMENTATION
		}
		#endif			
	}
}

#ifdef NLPI_INTERPRET_ACTION_PROPERTIES_AND_CONDITIONS_AS_FUNCTION_ARGUMENTS
string generateFunctionPropertyConditionArgumentsWithActionConceptInheritance(GIAentityNode * actionEntity, string functionArguments, int progLang)
{
	functionArguments = generateFunctionPropertyConditionArguments(actionEntity, functionArguments, progLang);
	
	#ifdef GIA_TRANSLATOR_DREAM_MODE_LINK_SPECIFIC_CONCEPTS_AND_ACTIONS
	//Part b: generate object initialisations based on action concepts (class inheritance)
	for(vector<GIAentityConnection*>::iterator entityNodeDefinitionListIterator = actionEntity->entityNodeDefinitionList->begin(); entityNodeDefinitionListIterator < actionEntity->entityNodeDefinitionList->end(); entityNodeDefinitionListIterator++)
	{
		GIAentityConnection * definitionConnection = (*entityNodeDefinitionListIterator);
		definitionConnection->parsedForNLPIcodeBlocks = true;
		GIAentityNode* definitionEntity = definitionConnection->entity;
		if(definitionEntity->isActionConcept)
		{
			functionArguments = generateFunctionPropertyConditionArguments(definitionEntity, functionArguments, progLang);
		}
	}
	#endif
	
	return functionArguments;
}

string generateFunctionPropertyConditionArguments(GIAentityNode * actionEntity, string functionArguments, int progLang)
{
	for(vector<GIAentityConnection*>::iterator entityIter = actionEntity->conditionNodeList->begin(); entityIter != actionEntity->conditionNodeList->end(); entityIter++)
	{
		//string actionConditionObject = (*localListIter2)->second;
		//string actionConditionObject = *localListIter2;
		if(functionArguments != "")
		{
			functionArguments = functionArguments + progLangClassMemberFunctionParametersNext[progLang];
		}					
		GIAentityNode * actionCondition = (*entityIter)->entity;
		string conditionObjectClassName = "";
		if(!(actionCondition->conditionObjectEntity->empty()))
		{
			conditionObjectClassName = generateClassName((actionCondition->conditionObjectEntity->back())->entity);
		}
		string conditionClassName = generateClassName(actionCondition);				
		functionArguments = functionArguments + generateCodeConditionPairDefinitionText(conditionClassName, conditionObjectClassName, progLang);
	}
	for(vector<GIAentityConnection*>::iterator entityIter = actionEntity->propertyNodeList->begin(); entityIter != actionEntity->propertyNodeList->end(); entityIter++)				
	{
		//string actionProperty = *localListIter2;
		GIAentityNode * actionProperty = (*entityIter)->entity;
		if(functionArguments != "")
		{
			functionArguments = functionArguments + progLangClassMemberFunctionParametersNext[progLang];
		}
		string propertyClassName = generateClassName(actionProperty);
		functionArguments = functionArguments + generateCodePropertyDefinitionText(propertyClassName, progLang);
	}
	return functionArguments;
}
#endif

bool printCodeBlocks(NLPIcodeblock * firstCodeBlockInLevel, int progLang, string * code, int level)
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
			//cout << "z7" << endl;
			NLPIitem * param2 = currentCodeBlockInLevel->parameters.at(1);
			//cout << "z7a" << endl;
			//cout << "param1->name = " << param1->name << endl;
			//cout << "param2->name = " << param2->name << endl;
			//cout << "contextParam1 = " << contextParam1 << endl;						
			
			//cout << "contextParam2 = " << contextParam2 << endl;
		
			string contextParam2 = generateStringFromContextVector(&(param2->context), progLang);
			string functionArguments = contextParam2 + param2->instanceName;
						
			#ifdef NLPI_INTERPRET_ACTION_PROPERTIES_AND_CONDITIONS_AS_FUNCTION_ARGUMENTS
			functionArguments = generateFunctionExecutionPropertyConditionArgumentsWithActionConceptInheritance(param1->actionInstance, functionArguments, progLang);
			#endif
			
			string codeBlockText = contextParam1 + param1->instanceName + progLangOpenParameterSpace[progLang] + functionArguments + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//context1.param1(context.param2); 	[param1 = function, context1 = subject, param2 = object]
			//cout << "z7c" << endl;
			printLine(codeBlockText, level, code);
			
			//cout << "z9" << endl;
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLPI_CODEBLOCK_TYPE_EXECUTE_FUNCTION_NO_OBJECT)
		{
			string functionArguments = "";
			#ifdef NLPI_INTERPRET_ACTION_PROPERTIES_AND_CONDITIONS_AS_FUNCTION_ARGUMENTS
			functionArguments = generateFunctionExecutionPropertyConditionArgumentsWithActionConceptInheritance(param1->actionInstance, functionArguments, progLang);
			#endif
					
			string codeBlockText = contextParam1 + param1->name + progLangOpenParameterSpace[progLang] + functionArguments + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//context1.param1(); 	[param1 = function, context1 = subject]
			printLine(codeBlockText, level, code);
			
			//cout << "z9b" << endl;
		}		
		else if(currentCodeBlockInLevel->codeBlockType == NLPI_CODEBLOCK_TYPE_ADD_PROPERTY)
		{
			NLPIitem * param2 = currentCodeBlockInLevel->parameters.at(1);	
			string contextParam2 = generateStringFromContextVector(&(param2->context), progLang);
			
			string codeBlockTextCreate = param2->name + progLangPointer[progLang] + STRING_SPACE + param2->instanceName + progLangEquals[progLang] + progLangNewObject[progLang] + param2->name + progLangOpenParameterSpace[progLang] + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	
			printLine(codeBlockTextCreate, level, code);
			string codeBlockText = contextParam1 + param1->instanceName + progLangObjectReferenceDelimiter[progLang] + param2->name + NLPI_ITEM_TYPE_PROPERTYLISTVAR_APPENDITION + progLangFunctionReferenceDelimiter[progLang] + progLangAddProperty[progLang] + progLangOpenParameterSpace[progLang] + param2->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//context1->param1->param2PropertyList.push_back(param2);
			printLine(codeBlockText, level, code);
		}	
		else if(currentCodeBlockInLevel->codeBlockType == NLPI_CODEBLOCK_TYPE_ADD_CONDITION)
		{
			NLPIitem * param2 = currentCodeBlockInLevel->parameters.at(1);	
			NLPIitem * param3 = currentCodeBlockInLevel->parameters.at(2);	
			string contextParam3 = generateStringFromContextVector(&(param3->context), progLang);
			string codeBlockTextCreate = param3->name + progLangPointer[progLang] + STRING_SPACE + param3->instanceName + progLangEquals[progLang] + progLangNewObject[progLang] + param3->name + progLangOpenParameterSpace[progLang] + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];
			printLine(codeBlockTextCreate, level, code);
			#ifdef NLPI_USE_STRING_INDEXED_UNORDERED_MAPS_FOR_CONDITION_LISTS
			string codeBlockText = contextParam1 + param1->instanceName + progLangObjectReferenceDelimiter[progLang] + param3->name + NLPI_ITEM_TYPE_CONDITIONLISTVAR_APPENDITION + progLangFunctionReferenceDelimiter[progLang] + progLangAddCondition[progLang] + progLangOpenParameterSpace[progLang] + progLangStringOpenClose[progLang] + param2->name + progLangStringOpenClose[progLang] + progLangParameterSpaceNextParam[progLang] + param3->instanceName + progLangCloseParameterSpace[progLang] + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		
			#else
			string codeBlockTextCreate2 = param2->name + progLangPointer[progLang] + STRING_SPACE + param2->instanceName + progLangEquals[progLang] + progLangNewObject[progLang] + param2->name + progLangOpenParameterSpace[progLang] + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];
			string codeBlockText = contextParam1 + param1->instanceName + progLangObjectReferenceDelimiter[progLang] + generateConditionListName(param2->name,  param3->name) + progLangFunctionReferenceDelimiter[progLang] + progLangAddCondition[progLang] + progLangOpenParameterSpace[progLang] + param2->instanceName + progLangParameterSpaceNextParam[progLang] + STRING_SPACE + param3->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//context1->param1->param2param3ConditionList.insert(param2, param3);	
			printLine(codeBlockTextCreate2, level, code);
			#endif
			printLine(codeBlockText, level, code);

		}			
		else if(currentCodeBlockInLevel->codeBlockType == NLPI_CODEBLOCK_TYPE_FOR)
		{
			if(progLang == NLPI_PROGRAMMING_LANGUAGE_DEFAULT)
			{
				string codeBlockText = progLangFor[progLang] + progLangForVectorIterPart1[progLang] + param1->name + progLangForVectorIterPart2[progLang] + contextParam1 + param1->name + NLPI_ITEM_TYPE_PROPERTYLISTVAR_APPENDITION + progLangForVectorIterPart3[progLang] + contextParam1 + param1->name + NLPI_ITEM_TYPE_PROPERTYLISTVAR_APPENDITION + progLangForVectorIterPart4[progLang];
				printLine(codeBlockText, level, code);
				printLine(progLangOpenBlock[progLang], level, code);
				string tempVarDeclarationText = param1->name + progLangPointer[progLang] + STRING_SPACE + param1->instanceName + progLangEquals[progLang] + progLangPointer[progLang] + progLangForVectorIterName[progLang] + progLangEndLine[progLang];	//OLD:  param1->name + NLPI_ITEM_TYPE_TEMPVAR_APPENDITION
				printLine(tempVarDeclarationText, (level+1), code);
			}
			else
			{
				cout << "error: printCodeBlocks() only yet finished for NLPI_PROGRAMMING_LANGUAGE_DEFAULT" << endl; 
			}
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLPI_CODEBLOCK_TYPE_NEW_FUNCTION)
		{
			string codeBlockText = param1->name + progLangOpenParameterSpace[progLang] + progLangCloseParameterSpace[progLang];	//main(){
			printLine(codeBlockText, level, code);		
			printLine(progLangOpenBlock[progLang], level, code);
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLPI_CODEBLOCK_TYPE_IF_HAS_PROPERTY)
		{
			NLPIitem * param2 = currentCodeBlockInLevel->parameters.at(1);	
			string contextParam2 = generateStringFromContextVector(&(param2->context), progLang);	//IS THIS REQUIRED????
			
			string codeBlockText = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + progLangNot[progLang] + progLangOpenParameterSpace[progLang] + contextParam1 + param1->instanceName + progLangFunctionReferenceDelimiter[progLang] + param2->name + NLPI_ITEM_TYPE_PROPERTYLISTVAR_APPENDITION + progLangFunctionReferenceDelimiter[progLang] + progLangFindProperty[progLang] + progLangOpenParameterSpace[progLang] + progLangCloseParameterSpace[progLang] + progLangCloseParameterSpace[progLang] + progLangCloseParameterSpace[progLang];		//if(!(context1->param1->param2PropertyList.empty())){	
			printLine(codeBlockText, level, code);
			printLine(progLangOpenBlock[progLang], level, code);
		}		
		else if(currentCodeBlockInLevel->codeBlockType == NLPI_CODEBLOCK_TYPE_IF_HAS_CONDITION)
		{
			NLPIitem * param2 = currentCodeBlockInLevel->parameters.at(1);		
			NLPIitem * param3 = currentCodeBlockInLevel->parameters.at(2);
			string contextParam3 = generateStringFromContextVector(&(param3->context), progLang);
				
			string codeBlockText = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + progLangNot[progLang] + progLangOpenParameterSpace[progLang] + contextParam1 + param1->instanceName + progLangFunctionReferenceDelimiter[progLang] + generateConditionListName(param2->name, param3->name) + progLangFunctionReferenceDelimiter[progLang] + progLangFindCondition[progLang] + progLangOpenParameterSpace[progLang] + progLangCloseParameterSpace[progLang] + progLangCloseParameterSpace[progLang] + progLangCloseParameterSpace[progLang];	//if(!(context1->param1->param2param3ConditionList.empty())){	
			printLine(codeBlockText, level, code);
			printLine(progLangOpenBlock[progLang], level, code);
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
			printCodeBlocks(currentCodeBlockInLevel->lowerLevel, progLang, code, (level+1));
			printLine(progLangCloseBlock[progLang], level, code);
		}
		
		//cout << "z4" << endl;
		currentCodeBlockInLevel = currentCodeBlockInLevel->next;
	}
}

#ifdef NLPI_INTERPRET_ACTION_PROPERTIES_AND_CONDITIONS_AS_FUNCTION_ARGUMENTS

string generateFunctionExecutionPropertyConditionArgumentsWithActionConceptInheritance(GIAentityNode * actionEntity, string functionArguments, int progLang)
{
	functionArguments = generateFunctionExecutionPropertyConditionArguments(actionEntity, functionArguments, progLang);
	#ifdef GIA_TRANSLATOR_DREAM_MODE_LINK_SPECIFIC_CONCEPTS_AND_ACTIONS
	//Part b: generate object initialisations based on action concepts (class inheritance)
	for(vector<GIAentityConnection*>::iterator entityNodeDefinitionListIterator = actionEntity->entityNodeDefinitionList->begin(); entityNodeDefinitionListIterator < actionEntity->entityNodeDefinitionList->end(); entityNodeDefinitionListIterator++)
	{
		GIAentityConnection * definitionConnection = (*entityNodeDefinitionListIterator);
		definitionConnection->parsedForNLPIcodeBlocks = true;
		GIAentityNode* definitionEntity = definitionConnection->entity;
		if(definitionEntity->isActionConcept)
		{
			functionArguments = generateFunctionExecutionPropertyConditionArguments(definitionEntity, functionArguments, progLang);
		}
	}
	#endif
	return functionArguments;
}

string generateFunctionExecutionPropertyConditionArguments(GIAentityNode * actionEntity, string functionArguments, int progLang)
{
	for(vector<GIAentityConnection*>::iterator entityIter = actionEntity->conditionNodeList->begin(); entityIter != actionEntity->conditionNodeList->end(); entityIter++)
	{
		if(functionArguments != "")
		{
			functionArguments = functionArguments + progLangClassMemberFunctionParametersNext[progLang];
		}					
		GIAentityNode * actionCondition = (*entityIter)->entity;
		GIAentityNode * conditionObject = NULL;
		if(!(actionCondition->conditionObjectEntity->empty()))
		{
			conditionObject = (actionCondition->conditionObjectEntity->back())->entity;
		}
		functionArguments = functionArguments + generateCodeConditionPairReferenceText(actionCondition, conditionObject, progLang);
	}
	for(vector<GIAentityConnection*>::iterator entityIter = actionEntity->propertyNodeList->begin(); entityIter != actionEntity->propertyNodeList->end(); entityIter++)				
	{
		GIAentityNode * propertyEntity = (*entityIter)->entity;
		if(functionArguments != "")
		{
			functionArguments = functionArguments + progLangClassMemberFunctionParametersNext[progLang];
		}
		functionArguments = functionArguments + generateInstanceName(propertyEntity); //generateCodePropertyReferenceText(propertyEntity, progLang);
	}
	return functionArguments;
}

string generateCodeConditionPairReferenceText(GIAentityNode * conditionEntity, GIAentityNode * conditionObjectEntity, int progLang)
{
	#ifdef NLPI_USE_STRING_INDEXED_UNORDERED_MAPS_FOR_CONDITION_LISTS
	string codeConditionPairReferenceText = progLangClassPairTypeStart[progLang] + progLangClassList2DTypeConditionTypeVar[progLang] + progLangClassList2DTypeMiddle[progLang] + generateClassName(conditionEntity) + progLangPointer[progLang] + progLangClassPairTypeEnd[progLang] + progLangClassMemberFunctionParametersOpen[progLang] + generateInstanceNameWithContext(conditionEntity, progLang) + progLangClassMemberFunctionParametersNext[progLang] + generateInstanceNameWithContext(conditionObjectEntity, progLang) + progLangClassMemberFunctionParametersClose[progLang];
	#else
	string codeConditionPairTypeText = progLangClassPairTypeStart[progLang] + generateClassName(conditionEntity) + progLangPointer[progLang] + progLangClassList2DTypeMiddle[progLang] + generateClassName(conditionObjectEntity) + progLangPointer[progLang] + progLangClassPairTypeEnd[progLang] + progLangClassMemberFunctionParametersOpen[progLang] + generateInstanceNameWithContext(conditionEntity, progLang) + progLangClassMemberFunctionParametersNext[progLang] + generateInstanceNameWithContext(conditionObjectEntity, progLang) + progLangClassMemberFunctionParametersClose[progLang];			
	#endif
	return codeConditionPairTypeText;
}

/*
//do not add context as it will generate context based on action
string generateCodePropertyReferenceText(GIAentityNode * propertyEntity, int progLang)
{
	string codePropertyReferenceText = generateInstanceNameWithContext(propertyEntity, progLang);	
	return codePropertyReferenceText;
}
*/

string generateInstanceNameWithContext(GIAentityNode * entity, int progLang)
{
	string instanceNameWithContext = "";
	#define IRRELVANT -1
	vector<string> context;
	getEntityContext(entity, &context, false, IRRELVANT, false);
	string contextString = generateStringFromContextVector(&context, progLang);
	instanceNameWithContext = contextString + generateInstanceName(entity);
	return instanceNameWithContext;
}

string generateCodeConditionPairDefinitionText(string conditionClassName, string conditionObjectClassName, int progLang)
{
	#ifdef NLPI_USE_STRING_INDEXED_UNORDERED_MAPS_FOR_CONDITION_LISTS
	string codeConditionListDefinitionText = progLangClassPairTypeStart[progLang] + progLangClassList2DTypeConditionTypeVar[progLang] + progLangClassList2DTypeMiddle[progLang] + conditionClassName + progLangPointer[progLang] + progLangClassPairTypeEnd[progLang] + STRING_SPACE + conditionClassName + NLPI_ITEM_TYPE_CONDITIONPAIRVAR_APPENDITION;
	#else
	string codeConditionListDefinitionText = progLangClassPairTypeStart[progLang] + conditionClassName + progLangPointer[progLang] + progLangClassList2DTypeMiddle[progLang] + conditionObjectClassName + progLangPointer[progLang] + progLangClassPairTypeEnd[progLang]+ STRING_SPACE + generateConditionPairName(conditionClassName, conditionObjectClassName);				
	#endif
	return codeConditionListDefinitionText;
}

string generateCodePropertyDefinitionText(string propertyClassName, int progLang)
{				 
	string codePropertyDefinitionText = propertyClassName + progLangPointer[progLang] + STRING_SPACE + propertyClassName;
	return codePropertyDefinitionText;
}

#endif

string generateCodeConditionListDefinitionText(string conditionClassName, string conditionObjectClassName, int progLang)
{
	#ifdef NLPI_USE_STRING_INDEXED_UNORDERED_MAPS_FOR_CONDITION_LISTS
	string codeConditionListDefinitionText = progLangClassList2DTypeStart[progLang] + progLangClassList2DTypeConditionTypeVar[progLang] + progLangClassList2DTypeMiddle[progLang] + conditionClassName + progLangPointer[progLang] + progLangClassListTypeEnd[progLang] + conditionClassName + NLPI_ITEM_TYPE_CONDITIONLISTVAR_APPENDITION;
	#else
	string codeConditionListDefinitionText = progLangClassList2DTypeStart[progLang] + conditionClassName + progLangPointer[progLang] + progLangClassList2DTypeMiddle[progLang] + conditionObjectClassName + progLangPointer[progLang] + progLangClassListTypeEnd[progLang] + generateConditionListName(conditionClassName, conditionObjectClassName);				
	#endif
	return codeConditionListDefinitionText;
}

string generateCodePropertyListDefinitionText(string propertyClassName, int progLang)
{				 
	string codePropertyListDefinitionText = progLangClassListTypeStart[progLang] + propertyClassName + progLangPointer[progLang] + progLangClassListTypeEnd[progLang] + propertyClassName + NLPI_ITEM_TYPE_PROPERTYLISTVAR_APPENDITION + progLangEndLine[progLang];
	return codePropertyListDefinitionText;
}


void printLine(string command, int level, string * code)
{
	//if(command != "")
	//{
	string line = "";
	for(int i=0; i<level; i++)
	{
		line = line + CHAR_TAB;
	}
	line = line + command;
	line = line + CHAR_NEWLINE;
	*code = *code + line;
	//}
}

string generateConditionListName(string conditionClassName, string conditionObjectClassName)
{
	string conditionListName = conditionClassName + conditionObjectClassName + NLPI_ITEM_TYPE_CONDITIONLISTVAR_APPENDITION;
	return conditionListName;
}

string generateConditionPairName(string conditionClassName, string conditionObjectClassName)
{
	string conditionListName = conditionClassName + conditionObjectClassName + NLPI_ITEM_TYPE_CONDITIONPAIRVAR_APPENDITION;
	return conditionListName;
}

