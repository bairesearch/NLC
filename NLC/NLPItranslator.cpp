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
 * File Name: NLPItranslator.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2013 Baxter AI (baxterai.com)
 * Project: Natural Language Programming Interface (compiler)
 * Project Version: 1e6e 23-November-2013
 * Requirements: requires text parsed by NLP Parser (eg Relex; available in .CFF format <relations>)
 *
 *******************************************************************************/



#include <ctime>
#include <cstdlib>	//for random number generation
#include <cmath>

#include "NLPItranslator.h"
#include "NLPItranslatorCodeBlocks.h"
#include "NLPItranslatorClassDefinitions.h"

bool translateNetwork(NLPIcodeblock * firstCodeBlockInTree, vector<NLPIclassDefinition *> * classDefinitionList, vector<GIAentityNode*> * entityNodesActiveListComplete, vector<GIAentityNode*> * entityNodesActiveListActions, int maxNumberSentences, string NLPIfunctionName)
{
	bool result = true;

	//NLPI translator Part 1.
	if(!generateCodeBlocks(firstCodeBlockInTree, entityNodesActiveListComplete, entityNodesActiveListActions, maxNumberSentences, NLPIfunctionName))
	{
		result = false;
	}
	
	//NLPI translator Part 2.
	if(!generateClassHeirarchy(classDefinitionList, entityNodesActiveListComplete, maxNumberSentences))
	{
		result = false;
	}
}


#ifdef NLPI_SUPPORT_INPUT_FILE_LISTS

void reconcileClassDefinitionListFunctionArgumentsBasedOnImplicitlyDeclaredVariablesInCurrentFunctionDefinition(NLPIcodeblock * firstCodeBlockInTree, vector<NLPIclassDefinition *> * classDefinitionList, string NLPIfunctionName)
{		
	//reconcile function arguments (both class function header and code function reference)
	string functionName = "";	
	string functionOwnerName = "";
	bool foundFunctionOwnerClass = false; 
	parseFunctionNameFromNLPIfunctionName(NLPIfunctionName, &functionName, &functionOwnerName, &foundFunctionOwnerClass);	//gets "fight" from "dog::fight"

	NLPIclassDefinition * classDefinitionFound = NULL;
	for(vector<NLPIclassDefinition*>::iterator classDefinitionIter = classDefinitionList->begin(); classDefinitionIter != classDefinitionList->end(); classDefinitionIter++)
	{	
		NLPIclassDefinition * currentClassDef = *classDefinitionIter;
		//cout << "currentClassDef->name = " << currentClassDef->name << endl;
		//cout << "functionOwnerName = " << functionOwnerName << endl;
		if((currentClassDef->name == generateClassName(functionOwnerName)) || !foundFunctionOwnerClass)
		{
			//cout << "currentClassDef->name = " << currentClassDef->name << endl;
			for(vector<NLPIclassDefinition*>::iterator localListIter = currentClassDef->functionList.begin(); localListIter != currentClassDef->functionList.end(); localListIter++)
			{
				NLPIclassDefinition * functionClassDefinition = *localListIter;
				//cout << "functionClassDefinition->functionNameSpecial = " << functionClassDefinition->functionNameSpecial << endl;
				//cout << "functionName = " << functionName << endl;
				if(functionClassDefinition->functionNameSpecial == generateFunctionName(functionName))
				{
					#ifdef NLPI_DEBUG
					cout << "reconcileClassDefinitionListFunctionArgumentsBasedOnImplicitlyDeclaredVariablesInCurrentFunctionDefinition() functionName = " << functionName << endl;
					#endif
					//contrast and compare function class arguments vs 

					findFormalFunctionArgumentCorrelateInExistingList(functionClassDefinition, &(firstCodeBlockInTree->parameters), classDefinitionList); 
				}	
			}
		}
	}
}
		
bool findFormalFunctionArgumentCorrelateInExistingList(NLPIclassDefinition * functionClassDefinition, vector<NLPIitem*> * formalFunctionArgumentList, vector<NLPIclassDefinition *> * classDefinitionList)
{
	vector<NLPIitem*> * existingFunctionArgumentList = &(functionClassDefinition->parameters);
	
	for(vector<NLPIitem*>::iterator parametersIterator = formalFunctionArgumentList->begin(); parametersIterator < formalFunctionArgumentList->end(); parametersIterator++)
	{
		NLPIitem * formalFunctionArgument = *parametersIterator;
		NLPIclassDefinition * classDefinitionCorrespondingToExistingFunctionArgument = NULL;
		NLPIclassDefinition * classDefinitionCorrespondingToFormalFunctionArgument = NULL;	//not used
		NLPIitem * existingFunctionArgument = NULL;	
		bool foundFormalFunctionArgumentCorrelateForExistingArgument = false;
		int foundFormalFunctionArgumentCorrelateForExistingArgumentInheritanceLevel = NLPI_SUPPORT_INPUT_FILE_LISTS_MAX_INHERITANCE_DEPTH_FOR_CLASS_CASTING;			
		if(formalFunctionArgument->itemType == NLPI_ITEM_TYPE_THIS_FUNCTION_ARGUMENT_INSTANCE_PLURAL)
		{
			#ifdef NLPI_DEBUG
			cout << "formalFunctionArgument->className = " << formalFunctionArgument->className << endl;
			#endif
			for(vector<NLPIitem*>::iterator parametersIterator = existingFunctionArgumentList->begin(); parametersIterator < existingFunctionArgumentList->end(); parametersIterator++)
			{
				NLPIitem * currentExistingFunctionArgument = *parametersIterator;

				bool foundClassDefinitionCorrespondingToExistingFunctionArgument = false;
				for(vector<NLPIclassDefinition*>::iterator classDefinitionIter = classDefinitionList->begin(); classDefinitionIter != classDefinitionList->end(); classDefinitionIter++)
				{
					NLPIclassDefinition * currentClassDef = *classDefinitionIter;
					if(currentClassDef->name == currentExistingFunctionArgument->className)
					{
						classDefinitionCorrespondingToExistingFunctionArgument = currentClassDef;
						foundClassDefinitionCorrespondingToExistingFunctionArgument = true;
					}
				}

				if(foundClassDefinitionCorrespondingToExistingFunctionArgument)
				{
					#ifdef NLPI_DEBUG
					cout << "foundClassDefinitionCorrespondingToExistingFunctionArgument: " << classDefinitionCorrespondingToExistingFunctionArgument->name << endl;
					#endif
					if(formalFunctionArgument->itemType == NLPI_ITEM_TYPE_THIS_FUNCTION_ARGUMENT_INSTANCE_PLURAL)
					{//CHECKTHIS; do not currently distinguish between plural and singular variables - this will need to be updated in future
						int inheritanceLevel = 0;
						NLPIclassDefinition * tempClassDef = NULL;
						//cout << "classDefinitionCorrespondingToExistingFunctionArgument->name = " << classDefinitionCorrespondingToExistingFunctionArgument->name << endl;
						//cout << "formalFunctionArgument->className = " << formalFunctionArgument->className << endl;
						if(findParentClass(classDefinitionCorrespondingToExistingFunctionArgument, formalFunctionArgument->className, 0, &inheritanceLevel, &tempClassDef))
						{
							//cout << "here2" << endl;
							if(inheritanceLevel < foundFormalFunctionArgumentCorrelateForExistingArgumentInheritanceLevel)
							{
								//cout << "foundFormalFunctionArgumentCorrelateForExistingArgument" << endl;
								foundFormalFunctionArgumentCorrelateForExistingArgument = true;
								foundFormalFunctionArgumentCorrelateForExistingArgumentInheritanceLevel = inheritanceLevel;
								classDefinitionCorrespondingToFormalFunctionArgument = tempClassDef;
								existingFunctionArgument = currentExistingFunctionArgument; 
							}
						}
					}
					else
					{
						//cout << "unsupported function argument: formalFunctionArgument->itemType = " << formalFunctionArgument->itemType << endl;
					}
				}
				else
				{	
					cout << "findFormalFunctionArgumentCorrelateInExistingList() error: !foundClassDefinitionCorrespondingToExistingFunctionArgument: " << currentExistingFunctionArgument->className << endl;
				}
			}
			if(foundFormalFunctionArgumentCorrelateForExistingArgument)
			{
				existingFunctionArgument->functionArgumentCertified = true;

				//store cast information for more generic class type passed as function argument
				if(existingFunctionArgument->className != formalFunctionArgument->className)
				{
					existingFunctionArgument->functionArgumentPassCastClassName = formalFunctionArgument->className;
					existingFunctionArgument->functionArgumentPassCastRequired = true;
				}
			}
			else
			{
				#ifdef NLPI_SUPPORT_INPUT_FILE_LISTS_CHECK_ACTION_SUBJECT_CONTENTS_FOR_IMPLICITLY_DECLARED_PARAMETERS
				bool foundFunctionArgumentInActionSubjectContents = false;
				GIAentityNode * actionEntity = functionClassDefinition->actionOrConditionInstance;
				if(!(actionEntity->actionSubjectEntity->empty()))
				{							
					GIAentityNode * actionSubject = (actionEntity->actionSubjectEntity->back())->entity;
					//cout << "actionSubject = " << actionSubject->entityName << endl;
					//cout << "formalFunctionArgument->className = " << formalFunctionArgument->className << endl;
					if(formalFunctionArgument->className == generateClassName(actionSubject))
					{
						foundFunctionArgumentInActionSubjectContents = true;
						#ifdef NLPI_DEBUG
						cout << "foundFunctionArgumentInActionSubjectContents: " << formalFunctionArgument->className << endl;
						#endif
						//formalFunctionArgument->formalFunctionArgumentCorrespondsToActionSubjectUseThisAlias = true;	//not done; this is now handled by generateConditionBlocks()	
					}
					/*//ignore conditions of actionSubject; they will need to be explicitly referenced by the function
					for(vector<GIAentityConnection*>::iterator entityIter = actionSubject->conditionNodeList->begin(); entityIter != actionSubject->conditionNodeList->end(); entityIter++)
					{
						GIAentityNode * actionCondition = (*entityIter)->entity;
					}
					*/
					for(vector<GIAentityConnection*>::iterator entityIter = actionSubject->propertyNodeList->begin(); entityIter != actionSubject->propertyNodeList->end(); entityIter++)				
					{
						GIAentityNode * actionProperty = (*entityIter)->entity;
						if(formalFunctionArgument->className == generateClassName(actionProperty))
						{//NB these implicitly declared parameters in the function definition will be referenced as plural (lists) not singular entities 
								//NO: check this is the case; eg the dog eats the pie; 'the dog' should be extracted from dogList if it was not passed as a parameter
								//1dXy: all parameters should be passed as lists (temporary lists should be created if specific variables require passing)
							foundFunctionArgumentInActionSubjectContents = true;
						}
					}
				}

				if(!foundFunctionArgumentInActionSubjectContents)
				{
					cout << "NLPI compiler warning: !foundFormalFunctionArgumentCorrelateForExistingArgument && !foundFunctionArgumentInActionSubjectContents (function arguments will not map): " << formalFunctionArgument->className << endl;
				#else
					cout << "NLPI compiler warning: !foundFormalFunctionArgumentCorrelateForExistingArgument (function arguments will not map): " << formalFunctionArgument->className << endl;
				#endif
					//add a new function argument to the existing function argument list
					NLPIitem * formalFunctionArgumentToAddExistingFunctionArgumentList = new NLPIitem(formalFunctionArgument);	//NLPI by default uses plural (lists) not singular entities
					existingFunctionArgumentList->push_back(formalFunctionArgumentToAddExistingFunctionArgumentList);		
				#ifdef NLPI_SUPPORT_INPUT_FILE_LISTS_CHECK_ACTION_SUBJECT_CONTENTS_FOR_IMPLICITLY_DECLARED_PARAMETERS
				}
				#endif
			}
		}
	}
}

bool findParentClass(NLPIclassDefinition * classDefinition, string variableName, int inheritanceLevel, int * maxInheritanceLevel, NLPIclassDefinition ** parentClass)
{
	bool foundVariable = false;
	if(classDefinition->name == variableName)
	{
		foundVariable = true;
		*maxInheritanceLevel = inheritanceLevel;
		*parentClass = classDefinition;
	}
	else 
	{	
		for(vector<NLPIclassDefinition*>::iterator localListIter = classDefinition->definitionList.begin(); localListIter != classDefinition->definitionList.end(); localListIter++)
		{
			NLPIclassDefinition * targetClassDefinition = *localListIter;
			if(findParentClass(targetClassDefinition, variableName, (inheritanceLevel+1), maxInheritanceLevel, parentClass))
			{
				foundVariable = true;
			}
		}
	}
	return foundVariable;
}

int getFilesFromFileList2(string inputListFileName, vector<string> * inputTextFileNameList)
{
	bool result = true;
	int numberOfInputFilesInList = 0;
	ifstream parseFileObject(inputListFileName.c_str());
	if(!parseFileObject.rdbuf( )->is_open( ))
	{
		//txt file does not exist in current directory.
		cout << "Error: input list file does not exist in current directory: " << inputListFileName << endl;
		result = false;
	}
	else
	{
		char currentToken;
		int fileNameIndex = 0;
		int charCount = 0;
		string currentFileName = "";
		while(parseFileObject.get(currentToken))
		{
			if(currentToken == CHAR_NEWLINE)
			{
				inputTextFileNameList->push_back(currentFileName);
				#ifdef GIA_MAIN_DEBUG
				//cout << "currentFileName = " << currentFileName << endl;
				#endif
				currentFileName = "";
				fileNameIndex++;
			}
			else
			{
				currentFileName = currentFileName + currentToken;
			}
			charCount++;
		}
		numberOfInputFilesInList = fileNameIndex;
	}
	#ifdef GIA_MAIN_DEBUG
	//cout << "numberOfInputFilesInList = " << numberOfInputFilesInList << endl;
	#endif
	return numberOfInputFilesInList;
}

#endif




