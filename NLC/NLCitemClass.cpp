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
 * File Name: NLCitemClass.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2016 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 1v2a 11-October-2016
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/


#include "NLCitemClass.h"
#include "GIAtranslatorOperations.h"
#include "SHAREDvars.h"	//required for convertLongToString()



NLCitem::NLCitem(void)
{
	itemType = NLC_ITEM_INSTANCE_ID_UNDEFINED;
	className = "";
	instanceName = "";
	functionName = "";
	className2 = "";
	instanceName2 = "";
	#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS
	functionArgumentCertified = false;
	functionArgumentPassCastRequired = false;
	functionArgumentPassCastClassName = "";
	#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
	functionArgumentExecutionEntityName = "";
	#endif
	//formalFunctionArgumentCorrespondsToActionSubjectUseThisAlias = false;
	#endif
	negative = false;
	#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS_ADVANCED
	conjunctionType = INT_DEFAULT_VALUE;
	#endif
	name = "";
	genericObjectName = "";
}
NLCitem::NLCitem(GIAentityNode* entity, int newItemType)
{
	itemType = newItemType;
	className = generateClassName(entity);
	instanceName = generateInstanceName(entity);
	functionName = generateFunctionName(entity);	//added 9 November 2013
	className2 = "";
	instanceName2 = "";
	#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS
	functionArgumentCertified = false;
	functionArgumentPassCastRequired = false;
	functionArgumentPassCastClassName = "";
	#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
	functionArgumentExecutionEntityName = "";
	#endif
	//formalFunctionArgumentCorrespondsToActionSubjectUseThisAlias = false;
	#endif
	negative = false;
	#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS_ADVANCED
	conjunctionType = INT_DEFAULT_VALUE;
	#endif
	name = entity->entityName;
	genericObjectName = "";
}
NLCitem::NLCitem(GIAentityNode* entity, int newItemType, int sentenceIndex)
{
	itemType = newItemType;
	className = generateClassName(entity);
	instanceName = generateInstanceName(entity);
	functionName = generateFunctionName(entity);	//added 9 November 2013
	className2 = "";
	instanceName2 = "";
	#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS
	functionArgumentCertified = false;
	functionArgumentPassCastRequired = false;
	functionArgumentPassCastClassName = "";
	#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
	functionArgumentExecutionEntityName = "";
	#endif
	//formalFunctionArgumentCorrespondsToActionSubjectUseThisAlias = false;
	#endif
	negative = false;
	#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS_ADVANCED
	conjunctionType = INT_DEFAULT_VALUE;
	#endif
	name = entity->entityName;
	genericObjectName = generateCategoryListGenericObjectName(entity, sentenceIndex);
}
NLCitem::NLCitem(GIAentityNode* entity, int newItemType, string newGenericObjectName)
{
	itemType = newItemType;
	className = generateClassName(entity);
	instanceName = generateInstanceName(entity);
	functionName = generateFunctionName(entity);	//added 9 November 2013
	className2 = "";
	instanceName2 = "";
	#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS
	functionArgumentCertified = false;
	functionArgumentPassCastRequired = false;
	functionArgumentPassCastClassName = "";
	#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
	functionArgumentExecutionEntityName = "";
	#endif
	//formalFunctionArgumentCorrespondsToActionSubjectUseThisAlias = false;
	#endif
	negative = false;
	#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS_ADVANCED
	conjunctionType = INT_DEFAULT_VALUE;
	#endif
	name = entity->entityName;
	genericObjectName = newGenericObjectName;
}
NLCitem::NLCitem(string newName, int newItemType)
{
	itemType = newItemType;
	className = generateClassName(newName);	//changed 9 November 2013
	#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS
	instanceName = newName;		//added 21 November 2013
	#else
	instanceName = ""
	#endif
	functionName = generateFunctionName(newName);	//added 9 November 2013
	className2 = "";
	instanceName2 = "";
	#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS
	functionArgumentCertified = false;
	functionArgumentPassCastRequired = false;
	functionArgumentPassCastClassName = "";
	#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
	functionArgumentExecutionEntityName = "";
	#endif
	//formalFunctionArgumentCorrespondsToActionSubjectUseThisAlias = false;
	#endif
	negative = false;
	#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS_ADVANCED
	conjunctionType = INT_DEFAULT_VALUE;
	#endif
	//if(newItemType == NLC_ITEM_TYPE_VARIABLE)
	name = newName;
	genericObjectName = "";
}
NLCitem::NLCitem(NLCitem* newItem)
{
	itemType = newItem->itemType;
	className = newItem->className;
	instanceName = newItem->instanceName;
	functionName = newItem->functionName;
	className2 = newItem->className2;
	instanceName2 = newItem->instanceName2;
	#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS
	functionArgumentCertified = newItem->functionArgumentCertified;	//updated 1k9c
	functionArgumentPassCastRequired = newItem->functionArgumentPassCastRequired;		//updated 1k9c
	functionArgumentPassCastClassName = newItem->functionArgumentPassCastClassName;
	#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
	functionArgumentExecutionEntityName = newItem->functionArgumentExecutionEntityName;
	#endif
	//formalFunctionArgumentCorrespondsToActionSubjectUseThisAlias = newItem->formalFunctionArgumentCorrespondsToActionSubjectUseThisAlias;
	#endif
	negative = false;
	#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS_ADVANCED
	conjunctionType = INT_DEFAULT_VALUE;
	#endif
	name = newItem->name;
	genericObjectName = "";
}
NLCitem::~NLCitem(void)
{
}

string generateCategoryListGenericObjectName(GIAentityNode* entity, int sentenceIndex)
{
	#ifdef NLC_GENERIC_LISTS_CATEGORIES_AND_SUBJECT_OBJECT_NAME_BY_INSTANCE_ID_AND_SENTENCE_INDEX
	string categoryListInstanceName = entity->entityName + string(NLC_GENERIC_LISTS_CATEGORIES_AND_SUBJECT_OBJECT_NAME_BY_INSTANCE_ID_AND_SENTENCE_INDEX_INSTANCE_NAME) + convertLongToString(entity->idInstance) + string(NLC_GENERIC_LISTS_CATEGORIES_AND_SUBJECT_OBJECT_NAME_BY_INSTANCE_ID_AND_SENTENCE_INDEX_SENTENCE_NAME) + convertIntToString(sentenceIndex);
	#else
	string categoryListInstanceName = generateInstanceName(entity);
	#endif
	return categoryListInstanceName;
}

string generateClassName(GIAentityNode* entity)
{
	string className = generateClassName(entity->entityName);
	return className;
}
string generateClassName(string entityName)
{
	string className = entityName + NLC_CLASS_NAME_APPEND;
	return className;
}
string generateFunctionName(GIAentityNode* entity)
{
	return generateFunctionName(entity->entityName);
}
string generateFunctionName(string entityName)
{
	string functionName = entityName + NLC_FUNCTION_NAME_APPEND;
	return functionName;
}
string generateInstanceName(GIAentityNode* entity)
{
	return generateInstanceName(entity->entityName, entity->idInstance);
}
string generateInstanceName(string entityName, long idInstance)
{
	string idInstanceString = convertLongToString(idInstance);
	#ifdef NLC_TRANSLATOR_LOGICAL_CONDITIONS_BOOLEAN_STATEMENTS_INTERPRET_SUBJECT_AND_OBJECT_INDEPENDENTLY
	if(idInstance == NLC_TRANSLATOR_LOGICAL_CONDITIONS_BOOLEAN_STATEMENTS_INTERPRET_SUBJECT_AND_OBJECT_INDEPENDENTLY_COMPARISON_IDINSTANCE)
	{
		idInstanceString = NLC_TRANSLATOR_LOGICAL_CONDITIONS_BOOLEAN_STATEMENTS_INTERPRET_SUBJECT_AND_OBJECT_INDEPENDENTLY_COMPARISON_IDINSTANCE_STRING;
	}
	#endif
	string instanceName = entityName + idInstanceString;
	return instanceName;
}

string generateTypeName(string entityName)
{
	string typeName = entityName;
	return typeName;
}

string removeClassTextFromClassDefinitionName(string className)
{
	string classNameRaw = "";
	int classTextIndex = className.find(NLC_CLASS_NAME_APPEND);
	if(classTextIndex != CPP_STRING_FIND_RESULT_FAIL_VALUE)
	{
		classNameRaw = className.substr(0, className.length()-strlen(NLC_CLASS_NAME_APPEND));
	}
	else
	{
		cout << "removeClassTextFromClassDefinitionName{} error: (classTextIndex == CPP_STRING_FIND_RESULT_FAIL_VALUE)" << endl;
	}
	return classNameRaw;
}



#ifdef NLC_SUPPORT_INPUT_FUNCTION_LISTS
string parseFunctionNameFromNLCfunctionName(string NLCfunctionName)
{
	//gets "fight" from "dog::fight"
	string functionName = "";
	bool hasFunctionOwnerClass = false;
	string functionOwnerName = "";
	parseFunctionNameFromNLCfunctionName(NLCfunctionName, &functionName, &functionOwnerName, &hasFunctionOwnerClass);
	return functionName;
}

void parseFunctionNameFromNLCfunctionName(string NLCfunctionName, string* functionName, string* functionOwnerName, bool* hasFunctionOwnerClass)
{
	//gets "fight" from "dog::fight"
	bool hasFunctionObjectClass = false;
	string functionObjectName = "";
	parseFunctionNameFromNLCfunctionName(NLCfunctionName, functionName, functionOwnerName, hasFunctionOwnerClass, &functionObjectName, &hasFunctionObjectClass);
}

void parseFunctionNameFromNLCfunctionName(string NLCfunctionName, string* functionName, string* functionOwnerName, bool* hasFunctionOwnerClass, string* functionObjectName, bool* hasFunctionObjectClass)
{
	vector<NLCitem*> additionalArgumentsTempNotUsed;
	parseFunctionNameFromNLCgeneralFunctionName(NLCfunctionName, functionName, functionOwnerName, hasFunctionOwnerClass, functionObjectName, hasFunctionObjectClass, &additionalArgumentsTempNotUsed);
}

#ifdef NLC_USE_LIBRARY
void parseFunctionNameFromNLClibFunctionName(string NLCfunctionName, string* functionName, string* functionOwnerName, bool* hasFunctionOwnerClass, string* functionObjectName, bool* hasFunctionObjectClass, vector<NLCitem*>* additionalArguments)
{
	parseFunctionNameFromNLCgeneralFunctionName(NLCfunctionName, functionName, functionOwnerName, hasFunctionOwnerClass, functionObjectName, hasFunctionObjectClass, additionalArguments);
}
#endif

void parseFunctionNameFromNLCgeneralFunctionName(string NLCfunctionName, string* functionName, string* functionOwnerName, bool* hasFunctionOwnerClass, string* functionObjectName, bool* hasFunctionObjectClass, vector<NLCitem*>* additionalArguments)
{
	//gets "fight" from "dog::fight"
	*hasFunctionOwnerClass = false;
	*functionOwnerName = "";
	*hasFunctionObjectClass = false;
	*functionObjectName = "";
	*functionName = NLCfunctionName;
	int indexOfActionName = NLCfunctionName.find(NLC_SUPPORT_INPUT_FUNCTION_LISTS_ACTION_DELIMITER);
	int indexOfObjectName = NLCfunctionName.find(NLC_SUPPORT_INPUT_FUNCTION_LISTS_ACTION_OBJECT_DELIMITER);
	int indexOfFirstArgumentName = NLCfunctionName.find(NLC_SUPPORT_INPUT_FUNCTION_LISTS_ACTION_ARGUMENT_DELIMITER);
	int indexOfFirstArgumentOrEnd = NLCfunctionName.length();
	#ifdef NLC_USE_LIBRARY
	if(indexOfFirstArgumentName != CPP_STRING_FIND_RESULT_FAIL_VALUE)
	{
		indexOfFirstArgumentOrEnd = indexOfFirstArgumentName;
	}
	#endif
	if(indexOfActionName != CPP_STRING_FIND_RESULT_FAIL_VALUE)
	{
		if(indexOfObjectName != CPP_STRING_FIND_RESULT_FAIL_VALUE)
		{
			*functionName = NLCfunctionName.substr(indexOfActionName+NLC_SUPPORT_INPUT_FUNCTION_LISTS_ACTION_DELIMITER_LENGTH, indexOfObjectName-indexOfActionName-NLC_SUPPORT_INPUT_FUNCTION_LISTS_ACTION_DELIMITER_LENGTH);
			*functionOwnerName = NLCfunctionName.substr(0, indexOfActionName);
			*functionObjectName = NLCfunctionName.substr(indexOfObjectName+NLC_SUPPORT_INPUT_FUNCTION_LISTS_ACTION_OBJECT_DELIMITER_LENGTH, indexOfFirstArgumentOrEnd-indexOfObjectName-(NLC_SUPPORT_INPUT_FUNCTION_LISTS_ACTION_OBJECT_DELIMITER_LENGTH));
			*hasFunctionOwnerClass = true;
			*hasFunctionObjectClass = true;
			#ifdef NLC_DEBUG
			cout << "parseFunctionNameFromNLCfunctionName{}:" << endl;
			cout << "NLCfunctionName = " << NLCfunctionName << endl;
			cout << "functionName = " <<* functionName << endl;
			cout << "functionOwnerName = " <<* functionOwnerName << endl;
			cout << "functionObjectName = " <<* functionObjectName << endl;
			#endif
		}
		else
		{
			*functionName = NLCfunctionName.substr(indexOfActionName+NLC_SUPPORT_INPUT_FUNCTION_LISTS_ACTION_DELIMITER_LENGTH, indexOfFirstArgumentOrEnd-indexOfActionName-NLC_SUPPORT_INPUT_FUNCTION_LISTS_ACTION_DELIMITER_LENGTH);
			*functionOwnerName = NLCfunctionName.substr(0, indexOfActionName);
			*hasFunctionOwnerClass = true;
			#ifdef NLC_DEBUG
			cout << "parseFunctionNameFromNLCfunctionName{}:" << endl;
			cout << "NLCfunctionName = " << NLCfunctionName << endl;
			cout << "functionName = " <<* functionName << endl;
			cout << "functionOwnerName = " <<* functionOwnerName << endl;
			#endif
		}
	}
	else if(indexOfObjectName != CPP_STRING_FIND_RESULT_FAIL_VALUE)
	{
		*functionName = NLCfunctionName.substr(0, indexOfObjectName);
		*functionObjectName = NLCfunctionName.substr(indexOfObjectName+NLC_SUPPORT_INPUT_FUNCTION_LISTS_ACTION_OBJECT_DELIMITER_LENGTH, indexOfFirstArgumentOrEnd-indexOfObjectName-(NLC_SUPPORT_INPUT_FUNCTION_LISTS_ACTION_OBJECT_DELIMITER_LENGTH));
		*hasFunctionObjectClass = true;
		#ifdef NLC_DEBUG
		cout << "parseFunctionNameFromNLCfunctionName{}:" << endl;
		cout << "NLCfunctionName = " << NLCfunctionName << endl;
		cout << "functionName = " <<* functionName << endl;
		cout << "functionObjectName = " <<* functionObjectName << endl;
		#endif
	}
	else
	{
		*functionName = NLCfunctionName.substr(0, indexOfFirstArgumentOrEnd);
	}

	#ifdef NLC_USE_LIBRARY
	if(indexOfFirstArgumentName != CPP_STRING_FIND_RESULT_FAIL_VALUE)
	{
		int indexOfArgument = indexOfFirstArgumentName+NLC_SUPPORT_INPUT_FUNCTION_LISTS_ACTION_ARGUMENT_DELIMITER_LENGTH;
		bool stillFindingArguments = true;
		while(stillFindingArguments)
		{
			string argumentName = "";
			int indexOfArgumentNew = NLCfunctionName.find(NLC_SUPPORT_INPUT_FUNCTION_LISTS_ACTION_ARGUMENT_DELIMITER, indexOfArgument);
			if(indexOfArgumentNew != CPP_STRING_FIND_RESULT_FAIL_VALUE)
			{
				argumentName = NLCfunctionName.substr(indexOfArgument, indexOfArgumentNew-indexOfArgument);
			}
			else
			{
				argumentName = NLCfunctionName.substr(indexOfArgument, NLCfunctionName.length()-indexOfArgument);
				stillFindingArguments = false;
			}
			#ifdef NLC_DEBUG
			//cout << "argumentName = " << argumentName << endl;
			#endif
			NLCitem* functionArgumentItem = new NLCitem(argumentName, NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_INSTANCE_OR_CLASS_LIST);	//NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_INSTANCE_OR_CLASS_LIST
			additionalArguments->push_back(functionArgumentItem);
			indexOfArgument = indexOfArgumentNew+NLC_SUPPORT_INPUT_FUNCTION_LISTS_ACTION_ARGUMENT_DELIMITER_LENGTH;
		}
	}
	#endif
}

string generateNLCfunctionHeader(string functionName, string functionOwnerName, bool hasFunctionOwnerClass, string functionObjectName, bool hasFunctionObjectClass)
{
	string NLCfunctionHeader = string(NLC_PREPROCESSOR_FUNCTION_HEADER_STRING) + NLC_PREPROCESSOR_FUNCTION_HEADER_MID_CHAR;
	if(hasFunctionOwnerClass)
	{
		NLCfunctionHeader = NLCfunctionHeader + functionOwnerName + NLC_SUPPORT_INPUT_FUNCTION_LISTS_ACTION_DELIMITER;
	}
	NLCfunctionHeader = NLCfunctionHeader + functionName;
	if(hasFunctionObjectClass)
	{
		NLCfunctionHeader = NLCfunctionHeader + NLC_SUPPORT_INPUT_FUNCTION_LISTS_ACTION_OBJECT_DELIMITER + functionObjectName;
	}
	NLCfunctionHeader = NLCfunctionHeader + CHAR_NEWLINE;
	return NLCfunctionHeader;
}

#endif

bool findFunctionArgument(vector<NLCitem*>* parameters, GIAentityNode* entity, int itemType, NLCitem** functionArgument)
{
	bool foundFunctionArgument = false;
	for(vector<NLCitem*>::iterator parametersIterator = parameters->begin(); parametersIterator < parameters->end(); parametersIterator++)
	{
		NLCitem* currentItem = *parametersIterator;
		#ifdef NLC_DEBUG
		//cout << "currentItem->itemType = " << currentItem->itemType << endl;
		#endif
		if(currentItem->itemType == itemType)
		{
			#ifdef NLC_DEBUG
			//cout << "(currentItem->itemType == itemType)" << endl;
			#endif
			#ifdef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES
			if(currentItem->instanceName == generateInstanceName(entity))
			#else
			if(currentItem->name == entity->entityName)	//or if(currentItem->className == generateClassName(entity->entityName))
			#endif
			{
				#ifdef NLC_DEBUG
				//cout << "(currentItem->name)" << endl;
				#endif
				*functionArgument = currentItem;
				foundFunctionArgument = true;
			}
		}
	}
	return foundFunctionArgument;
}


