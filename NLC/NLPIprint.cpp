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
 * Project Version: 1a3a 03-October-2013
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
			classDefinitionEntryText = classDefinitionEntryText + "public " + targetName;
		}
		printLine(classDefinitionEntryText, 0, code);
		printLine(progLangOpenClass[progLang], 0, code);
		printLine(progLangClassIntro[progLang], 0, code);
		string classConstructorDeclaration = className + progLangClassConstructorDestructorAppend[progLang];
		printLine(classConstructorDeclaration, 1, code);
		string classDestructorDeclaration = progLangClassDestructorPrepend[progLang] + className + progLangClassConstructorDestructorAppend[progLang];
		printLine(classDestructorDeclaration, 1, code);
		printLine(STRING_NEW_LINE, 1, code);
		string classNameCode = progLangClassNameType[progLang] + "name = " + className + progLangEndLine[progLang];
		printLine(classNameCode, 1, code);
		printLine(STRING_NEW_LINE, 1, code);
		
		//cout << "className = " << className << endl;
				
		for(vector<NLPIclassDefinition*>::iterator localListIter = classDefinition->propertyList.begin(); localListIter != classDefinition->propertyList.end(); localListIter++)
		{
			NLPIclassDefinition * targetClassDefinition = *localListIter;
			string targetName = targetClassDefinition->name;
			string localListDeclarationText = progLangClassListTypeStart[progLang] + targetName +  progLangClassListTypeEnd[progLang] + targetName + NLPI_ITEM_TYPE_PROPERTYLISTVAR_APPENDITION + progLangEndLine[progLang];
			printLine(localListDeclarationText, 1, code);	
		}

		for(vector<NLPIclassDefinition*>::iterator localListIter = classDefinition->conditionList.begin(); localListIter != classDefinition->conditionList.end(); localListIter++)
		{
			NLPIclassDefinition * targetClassDefinition = *localListIter;
			string targetName = targetClassDefinition->name;
			string localListDeclarationText = progLangClassListTypeStart[progLang] + targetName +  progLangClassListTypeEnd[progLang] + targetName + NLPI_ITEM_TYPE_CONDITIONLISTVAR_APPENDITION + progLangEndLine[progLang];
			printLine(localListDeclarationText, 1, code);	
		}
		
		for(vector<NLPIclassDefinition*>::iterator localListIter = classDefinition->functionList.begin(); localListIter != classDefinition->functionList.end(); localListIter++)
		{
			NLPIclassDefinition * targetClassDefinition = *localListIter;
			string targetName = targetClassDefinition->name;
			string localListDeclarationText = progLangClassMemberFunctionType[progLang] + targetName + progLangClassMemberFunctionParameters[progLang] + progLangEndLine[progLang];
			printLine(localListDeclarationText, 1, code);	
		}
						
		printLine(progLangCloseClass[progLang], 0, code);
		printLine(STRING_NEW_LINE, 0, code);
	}
} 

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
			string contextParam2 = generateStringFromContextVector(&(param2->context), progLang);
			//cout << "contextParam2 = " << contextParam2 << endl;
			
			string codeBlockText = contextParam1 + param1->name + progLangOpenParameterSpace[progLang] + contextParam2 + param2->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//context1.param1(context.param2); 	[param1 = function, context1 = subject, param2 = object]
			//cout << "z7c" << endl;
			printLine(codeBlockText, level, code);
			
			//cout << "z9" << endl;
		}
		else if(currentCodeBlockInLevel->codeBlockType == NLPI_CODEBLOCK_TYPE_EXECUTE_FUNCTION_NO_OBJECT)
		{
			string codeBlockText = contextParam1 + param1->name + progLangOpenParameterSpace[progLang] + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//context1.param1(); 	[param1 = function, context1 = subject]
			printLine(codeBlockText, level, code);
			
			//cout << "z9b" << endl;
		}		
		else if(currentCodeBlockInLevel->codeBlockType == NLPI_CODEBLOCK_TYPE_ADD_PROPERTY)
		{
			NLPIitem * param2 = currentCodeBlockInLevel->parameters.at(1);	
			string contextParam2 = generateStringFromContextVector(&(param2->context), progLang);
				
			string codeBlockText = contextParam1 + param1->instanceName + progLangFunctionReferenceDelimiter[progLang] + param2->name + NLPI_ITEM_TYPE_PROPERTYLISTVAR_APPENDITION + progLangFunctionReferenceDelimiter[progLang] + NLPI_ITEM_TYPE_PROPERTYLISTADDFUNCTION + progLangOpenParameterSpace[progLang] + contextParam2 + param2->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//context1.param1.param2PropertyList.addProperty(context2.param2);
			printLine(codeBlockText, level, code);
		}	
		else if(currentCodeBlockInLevel->codeBlockType == NLPI_CODEBLOCK_TYPE_ADD_CONDITION)
		{
			NLPIitem * param2 = currentCodeBlockInLevel->parameters.at(1);	
			NLPIitem * param3 = currentCodeBlockInLevel->parameters.at(2);	
			string contextParam3 = generateStringFromContextVector(&(param3->context), progLang);
	
			string codeBlockText = contextParam1 + param1->instanceName + progLangFunctionReferenceDelimiter[progLang] + param3->name + NLPI_ITEM_TYPE_CONDITIONLISTVAR_APPENDITION + progLangFunctionReferenceDelimiter[progLang] + NLPI_ITEM_TYPE_CONDITIONLISTADDFUNCTION + progLangOpenParameterSpace[progLang] + contextParam3 + param3->instanceName + progLangParameterSpaceNextParam[progLang] + NLPI_ITEM_TYPE_CONDITIONLISTCONDITIONPARAMETERINVERTACOMMAS + param2->name + NLPI_ITEM_TYPE_CONDITIONLISTCONDITIONPARAMETERINVERTACOMMAS + progLangCloseParameterSpace[progLang] + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//context1.param1.param3ConditionList.addCondition(context3.param3, "param2");	
			printLine(codeBlockText, level, code);
		}			
		else if(currentCodeBlockInLevel->codeBlockType == NLPI_CODEBLOCK_TYPE_FOR)
		{
			if(progLang == NLPI_PROGRAMMING_LANGUAGE_DEFAULT)
			{
				//string codeBlockText = progLangFor[progLang] + progLangOpenParameterSpace[progLang] + contextParam1 + param1->name + progLangCloseParameterSpace[progLang];	//for(vector<class*>::iterator iter = classContext.classPropertyList->begin(); iter < classContext.classPropertyList->end(); iter++)
				string codeBlockText = progLangFor[progLang] + "(vector<" + param1->name + "*>::iterator iter = " + contextParam1 + param1->name + NLPI_ITEM_TYPE_PROPERTYLISTVAR_APPENDITION + "->begin(); iter < " + contextParam1 + param1->name + NLPI_ITEM_TYPE_PROPERTYLISTVAR_APPENDITION + 	"->end(); iter++)";
				printLine(codeBlockText, level, code);
				printLine(progLangOpenBlock[progLang], level, code);
				string tempVarDeclarationText = param1->name + progLangPointer[progLang] + " " + param1->instanceName + " = " + progLangPointer[progLang] + "iter;";	//OLD:  param1->name + NLPI_ITEM_TYPE_TEMPVAR_APPENDITION
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
			
			//OLD: string codeBlockText = progLangIf[progLang] + progLangOpenParameterSpace[progLang] +  contextParam1 + param1->name + progLangFunctionReferenceDelimiter[progLang] + progLangObjectCheckHasPropertyFunction[progLang] + progLangOpenParameterSpace[progLang] + param2->name + progLangCloseParameterSpace[progLang] + progLangCloseParameterSpace[progLang];	//if(context.param1->has(param2)){
			string codeBlockText = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + contextParam1 + param1->instanceName + progLangFunctionReferenceDelimiter[progLang] + param2->name + NLPI_ITEM_TYPE_PROPERTYLISTVAR_APPENDITION + progLangFunctionReferenceDelimiter[progLang] + NLPI_ITEM_TYPE_PROPERTYLISTFINDFUNCTION + progLangOpenParameterSpace[progLang] + contextParam2 + param2->instanceName + progLangCloseParameterSpace[progLang] + progLangCloseParameterSpace[progLang];		//if(context1.param1.param2PropertyList.findProperty(context2.param2)){	
			printLine(codeBlockText, level, code);
			printLine(progLangOpenBlock[progLang], level, code);
		}		
		else if(currentCodeBlockInLevel->codeBlockType == NLPI_CODEBLOCK_TYPE_IF_HAS_CONDITION)
		{
			NLPIitem * param2 = currentCodeBlockInLevel->parameters.at(1);		
			NLPIitem * param3 = currentCodeBlockInLevel->parameters.at(2);
			string contextParam3 = generateStringFromContextVector(&(param3->context), progLang);
				
			//OLD: string codeBlockText = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + param2->name + progLangOpenParameterSpace[progLang] + contextParam1 + param1->name + progLangParameterSpaceNextParam[progLang] + contextParam3 + param3->name + progLangCloseParameterSpace[progLang] + progLangCloseParameterSpace[progLang];	//if(param2(context.param1, context.param3)){
			string codeBlockText = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + contextParam1 + param1->instanceName + progLangFunctionReferenceDelimiter[progLang] + param3->name + NLPI_ITEM_TYPE_CONDITIONLISTVAR_APPENDITION + progLangFunctionReferenceDelimiter[progLang] + NLPI_ITEM_TYPE_CONDITIONLISTFINDFUNCTION + progLangOpenParameterSpace[progLang] + contextParam3 + param3->instanceName + progLangParameterSpaceNextParam[progLang] + NLPI_ITEM_TYPE_CONDITIONLISTCONDITIONPARAMETERINVERTACOMMAS + param2->name + NLPI_ITEM_TYPE_CONDITIONLISTCONDITIONPARAMETERINVERTACOMMAS + progLangCloseParameterSpace[progLang] + progLangCloseParameterSpace[progLang];	//if(context1.param1.param3ConditionList.findCondition(context3.param3, "param2")){	
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

void printLine(string command, int level, string * code)
{
	string line = "";
	for(int i=0; i<level; i++)
	{
		line = line + CHAR_TAB;
	}
	line = line + command;
	line = line + CHAR_NEWLINE;
	*code = *code + line;
}

