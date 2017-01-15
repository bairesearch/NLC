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
 * File Name: NLCtranslator.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2014 Baxter AI (baxterai.com)
 * Project: Natural Language Programming Interface (compiler)
 * Project Version: 1g5e 07-July-2014
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/



#include <ctime>
#include <cstdlib>	//for random number generation
#include <cmath>

#include "NLCtranslator.h"
#include "NLCtranslatorCodeBlocks.h"
#include "NLCtranslatorClassDefinitions.h"

bool translateNetwork(NLCcodeblock * firstCodeBlockInTree, vector<NLCclassDefinition *> * classDefinitionList, vector<GIAentityNode*> * entityNodesActiveListComplete, int maxNumberSentences, string NLCfunctionName)
{
	bool result = true;

	#ifdef NLC_SUPPORT_CONDITION_LOGICAL_OPERATIONS
	//NLC translator Part 0.
	if(!identifyAndTagAllConditionLogicalOperations(entityNodesActiveListComplete, maxNumberSentences))
	{
		result = false;
	}
	#endif

	//NLC translator Part 1.
	if(!generateCodeBlocks(firstCodeBlockInTree, entityNodesActiveListComplete, maxNumberSentences, NLCfunctionName))
	{
		result = false;
	}

	//NLC translator Part 2.
	if(!generateClassHeirarchy(classDefinitionList, entityNodesActiveListComplete, maxNumberSentences))
	{
		result = false;
	}
	return result;
}


#ifdef NLC_SUPPORT_CONDITION_LOGICAL_OPERATIONS
bool identifyAndTagAllConditionLogicalOperations(vector<GIAentityNode*> * entityNodesActiveListComplete, int maxNumberSentences)
{
	for(int sentenceIndex=1; sentenceIndex <= maxNumberSentences; sentenceIndex++)
	{
		for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
		{
			GIAentityNode * conditionEntity = (*entityIter);
			if(conditionEntity->isCondition)
			{
				if(checkSentenceIndexParsingCodeBlocks(conditionEntity, sentenceIndex, true))	//could be set to false instead
				{
					bool foundConditionLogicalOperation = false;
					for(int i=1; i<NLC_CONDITION_LOGICAL_OPERATIONS_NUMBER_OF_TYPES; i++)		//i=1 to ignore "for"
					{
						if(conditionEntity->entityName == conditionLogicalOperationsArray[i])
						{
							foundConditionLogicalOperation = true;
						}
					}
					if(foundConditionLogicalOperation)
					{
						GIAentityNode * conditionSubject = NULL;
						GIAentityNode * conditionObject = NULL;
						bool foundConditionSubject = false;
						bool foundConditionObject = false;
						if(!(conditionEntity->conditionSubjectEntity->empty()))
						{
							conditionSubject = (conditionEntity->conditionSubjectEntity->back())->entity;
							foundConditionSubject = true;
						}
						if(!(conditionEntity->conditionObjectEntity->empty()))
						{
							conditionObject = (conditionEntity->conditionObjectEntity->back())->entity;
							foundConditionObject = true;
						}
						if(foundConditionSubject && foundConditionObject)
						{
							conditionEntity->NLCconditionLogicalOperations = true;
							//cout << "tagged: conditionEntity->entityName = " << conditionEntity->entityName << endl;

							if(conditionObject->isConcept)
							{
								cout << "identifyAndTagAllConditionLogicalOperations() error: NLC_SUPPORT_CONDITION_LOGICAL_OPERATIONS_BASED_ON_CONCEPTS only handles substance concepts. GIA_CREATE_SUBSTANCE_CONCEPTS_FOR_ALL_SENTENCES_WITH_CONCEPTS must be enabled." << endl;
								cout << "conditionObject = " << conditionObject->entityName;
							}
							else
							{
								tagAllEntitiesInSentenceSubsetAsPertainingToConditionLogicalOperation(conditionObject, sentenceIndex, true);
							}
							if(conditionSubject->isConcept)
							{
								cout << "identifyAndTagAllConditionLogicalOperations() error: NLC_SUPPORT_CONDITION_LOGICAL_OPERATIONS_BASED_ON_CONCEPTS only handles substance concepts. GIA_CREATE_SUBSTANCE_CONCEPTS_FOR_ALL_SENTENCES_WITH_CONCEPTS must be enabled." << endl;
								cout << "conditionSubject = " << conditionSubject->entityName;
							}
							else
							{
								tagAllEntitiesInSentenceSubsetAsPertainingToConditionLogicalOperation(conditionSubject, sentenceIndex, true);
							}
						}
					}
				}
			}
		}
	}
	return true;
}
#endif

#ifdef NLC_SUPPORT_INPUT_FILE_LISTS

void reconcileClassDefinitionListFunctionArgumentsBasedOnImplicitlyDeclaredVariablesInCurrentFunctionDefinition(NLCcodeblock * firstCodeBlockInTree, vector<NLCclassDefinition *> * classDefinitionList, string NLCfunctionName)
{
	//reconcile function arguments (both class function header and code function reference)
	string functionName = "";
	string functionOwnerName = "";
	bool foundFunctionOwnerClass = false;
	parseFunctionNameFromNLCfunctionName(NLCfunctionName, &functionName, &functionOwnerName, &foundFunctionOwnerClass);	//gets "fight" from "dog::fight"

	NLCclassDefinition * classDefinitionFound = NULL;
	for(vector<NLCclassDefinition*>::iterator classDefinitionIter = classDefinitionList->begin(); classDefinitionIter != classDefinitionList->end(); classDefinitionIter++)
	{
		NLCclassDefinition * currentClassDef = *classDefinitionIter;
		if((currentClassDef->name == generateClassName(functionOwnerName)) || !foundFunctionOwnerClass)
		{
			//cout << "currentClassDef->name = " << currentClassDef->name << endl;
			for(vector<NLCclassDefinition*>::iterator localListIter = currentClassDef->functionList.begin(); localListIter != currentClassDef->functionList.end(); localListIter++)
			{
				NLCclassDefinition * functionClassDefinition = *localListIter;
				//cout << "functionClassDefinition->functionNameSpecial = " << functionClassDefinition->functionNameSpecial << endl;
				//cout << "functionName = " << functionName << endl;
				if(functionClassDefinition->functionNameSpecial == generateFunctionName(functionName))
				{
					#ifdef NLC_DEBUG
					cout << "reconcileClassDefinitionListFunctionArgumentsBasedOnImplicitlyDeclaredVariablesInCurrentFunctionDefinition() functionName = " << functionName << endl;
					#endif
					//contrast and compare function class arguments vs

					findFormalFunctionArgumentCorrelateInExistingList(functionClassDefinition, &(firstCodeBlockInTree->parameters), classDefinitionList);
				}
			}
		}
	}
}

bool findFormalFunctionArgumentCorrelateInExistingList(NLCclassDefinition * functionClassDefinition, vector<NLCitem*> * formalFunctionArgumentList, vector<NLCclassDefinition *> * classDefinitionList)
{
	vector<NLCitem*> * existingFunctionArgumentList = &(functionClassDefinition->parameters);

	for(vector<NLCitem*>::iterator parametersIterator = formalFunctionArgumentList->begin(); parametersIterator < formalFunctionArgumentList->end(); parametersIterator++)
	{
		NLCitem * formalFunctionArgument = *parametersIterator;
		NLCclassDefinition * classDefinitionCorrespondingToExistingFunctionArgument = NULL;
		NLCclassDefinition * classDefinitionCorrespondingToFormalFunctionArgument = NULL;	//not used
		NLCitem * existingFunctionArgument = NULL;
		bool foundFormalFunctionArgumentCorrelateForExistingArgument = false;
		int foundFormalFunctionArgumentCorrelateForExistingArgumentInheritanceLevel = NLC_SUPPORT_INPUT_FILE_LISTS_MAX_INHERITANCE_DEPTH_FOR_CLASS_CASTING;
		if(formalFunctionArgument->itemType == NLC_ITEM_TYPE_THIS_FUNCTION_ARGUMENT_INSTANCE_PLURAL)
		{
			#ifdef NLC_DEBUG
			cout << "formalFunctionArgument->className = " << formalFunctionArgument->className << endl;
			#endif
			for(vector<NLCitem*>::iterator parametersIterator = existingFunctionArgumentList->begin(); parametersIterator < existingFunctionArgumentList->end(); parametersIterator++)
			{
				NLCitem * currentExistingFunctionArgument = *parametersIterator;

				bool foundClassDefinitionCorrespondingToExistingFunctionArgument = false;
				for(vector<NLCclassDefinition*>::iterator classDefinitionIter = classDefinitionList->begin(); classDefinitionIter != classDefinitionList->end(); classDefinitionIter++)
				{
					NLCclassDefinition * currentClassDef = *classDefinitionIter;
					if(currentClassDef->name == currentExistingFunctionArgument->className)
					{
						classDefinitionCorrespondingToExistingFunctionArgument = currentClassDef;
						foundClassDefinitionCorrespondingToExistingFunctionArgument = true;
					}
				}

				if(foundClassDefinitionCorrespondingToExistingFunctionArgument)
				{
					#ifdef NLC_DEBUG
					cout << "foundClassDefinitionCorrespondingToExistingFunctionArgument: " << classDefinitionCorrespondingToExistingFunctionArgument->name << endl;
					#endif
					if(formalFunctionArgument->itemType == NLC_ITEM_TYPE_THIS_FUNCTION_ARGUMENT_INSTANCE_PLURAL)
					{//CHECKTHIS; do not currently distinguish between plural and singular variables - this will need to be updated in future
						int inheritanceLevel = 0;
						NLCclassDefinition * tempClassDef = NULL;
						//cout << "classDefinitionCorrespondingToExistingFunctionArgument->name = " << classDefinitionCorrespondingToExistingFunctionArgument->name << endl;
						//cout << "formalFunctionArgument->className = " << formalFunctionArgument->className << endl;
						if(findParentClass(classDefinitionCorrespondingToExistingFunctionArgument, formalFunctionArgument->className, 0, &inheritanceLevel, &tempClassDef))
						{
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
				#ifdef NLC_SUPPORT_INPUT_FILE_LISTS_CHECK_ACTION_SUBJECT_CONTENTS_FOR_IMPLICITLY_DECLARED_PARAMETERS
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
						#ifdef NLC_DEBUG
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
					cout << "NLC compiler warning: !foundFormalFunctionArgumentCorrelateForExistingArgument && !foundFunctionArgumentInActionSubjectContents (function arguments will not map): " << formalFunctionArgument->className << endl;
				#else
					cout << "NLC compiler warning: !foundFormalFunctionArgumentCorrelateForExistingArgument (function arguments will not map): " << formalFunctionArgument->className << endl;
				#endif
					//add a new function argument to the existing function argument list
					NLCitem * formalFunctionArgumentToAddExistingFunctionArgumentList = new NLCitem(formalFunctionArgument);	//NLC by default uses plural (lists) not singular entities
					existingFunctionArgumentList->push_back(formalFunctionArgumentToAddExistingFunctionArgumentList);
				#ifdef NLC_SUPPORT_INPUT_FILE_LISTS_CHECK_ACTION_SUBJECT_CONTENTS_FOR_IMPLICITLY_DECLARED_PARAMETERS
				}
				#endif
			}
		}
	}
	return true;
}

bool findParentClass(NLCclassDefinition * classDefinition, string variableName, int inheritanceLevel, int * maxInheritanceLevel, NLCclassDefinition ** parentClass)
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
		for(vector<NLCclassDefinition*>::iterator localListIter = classDefinition->definitionList.begin(); localListIter != classDefinition->definitionList.end(); localListIter++)
		{
			NLCclassDefinition * targetClassDefinition = *localListIter;
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




