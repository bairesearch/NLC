 /*******************************************************************************
 *
 * License: GNU Affero General Public License version 3 (AGPLv3)
 *
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: NLCitemClass.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2022 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler
 * Project Version: 2p1a 05-June-2022
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 * /
 *******************************************************************************/


#include "NLCitemClass.hpp"


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
	name = "";
	genericObjectName = "";
}
NLCitem::NLCitem(const GIAentityNode* entity, const int newItemType)
{
	itemType = newItemType;
	className = NLCitemClassClass().generateClassName(entity);
	instanceName = NLCitemClassClass().generateInstanceName(entity);
	functionName = NLCitemClassClass().generateFunctionName(entity);	//added 9 November 2013
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
	name = entity->entityName;
	genericObjectName = "";
}
NLCitem::NLCitem(const GIAentityNode* entity, const int newItemType, const int sentenceIndex)
{
	itemType = newItemType;
	className = NLCitemClassClass().generateClassName(entity);
	instanceName = NLCitemClassClass().generateInstanceName(entity);
	functionName = NLCitemClassClass().generateFunctionName(entity);	//added 9 November 2013
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
	name = entity->entityName;
	genericObjectName = NLCitemClassClass().generateCategoryListGenericObjectName(entity, sentenceIndex);
}
NLCitem::NLCitem(const GIAentityNode* entity, const int newItemType, const string newGenericObjectName)
{
	itemType = newItemType;
	className = NLCitemClassClass().generateClassName(entity);
	instanceName = NLCitemClassClass().generateInstanceName(entity);
	functionName = NLCitemClassClass().generateFunctionName(entity);	//added 9 November 2013
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
	name = entity->entityName;
	genericObjectName = newGenericObjectName;
}
NLCitem::NLCitem(const string newName, const int newItemType)
{
	itemType = newItemType;
	className = NLCitemClassClass().generateClassName(newName);	//changed 9 November 2013
	#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS
	instanceName = newName;		//added 21 November 2013
	#else
	instanceName = ""
	#endif
	functionName = NLCitemClassClass().generateFunctionName(newName);	//added 9 November 2013
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
	//if(newItemType == NLC_ITEM_TYPE_VARIABLE)
	name = newName;
	genericObjectName = "";
}
NLCitem::NLCitem(const NLCitem* newItem)
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
	name = newItem->name;
	genericObjectName = "";
}
NLCitem::~NLCitem(void)
{
}

string NLCitemClassClass::generateCategoryListGenericObjectName(const GIAentityNode* entity, const int sentenceIndex)
{
	#ifdef NLC_GENERIC_LISTS_CATEGORIES_AND_SUBJECT_OBJECT_NAME_BY_INSTANCE_ID_AND_SENTENCE_INDEX
	string categoryListInstanceName = entity->entityName + string(NLC_GENERIC_LISTS_CATEGORIES_AND_SUBJECT_OBJECT_NAME_BY_INSTANCE_ID_AND_SENTENCE_INDEX_INSTANCE_NAME) + SHAREDvars.convertLongToString(entity->idInstance) + string(NLC_GENERIC_LISTS_CATEGORIES_AND_SUBJECT_OBJECT_NAME_BY_INSTANCE_ID_AND_SENTENCE_INDEX_SENTENCE_NAME) + SHAREDvars.convertIntToString(sentenceIndex);
	#else
	string categoryListInstanceName = generateInstanceName(entity);
	#endif
	return categoryListInstanceName;
}

string NLCitemClassClass::generateClassName(const GIAentityNode* entity)
{
	string className = generateClassName(entity->entityName);
	return className;
}
string NLCitemClassClass::generateClassName(const string entityName)
{
	string className = entityName + NLC_CLASS_NAME_APPEND;
	return className;
}
string NLCitemClassClass::generateFunctionName(const GIAentityNode* entity)
{
	return generateFunctionName(entity->entityName);
}
string NLCitemClassClass::generateFunctionName(const string entityName)
{
	string functionName = entityName + NLC_FUNCTION_NAME_APPEND;
	return functionName;
}
string NLCitemClassClass::generateInstanceName(const GIAentityNode* entity)
{
	return generateInstanceName(entity->entityName, entity->idInstance);
}
string NLCitemClassClass::generateInstanceName(const string entityName, const int64_t idInstance)
{
	string idInstanceString = SHAREDvars.convertLongToString(idInstance);
	#ifdef NLC_TRANSLATOR_LOGICAL_CONDITIONS_BOOLEAN_STATEMENTS_INTERPRET_SUBJECT_AND_OBJECT_INDEPENDENTLY
	if(idInstance == NLC_TRANSLATOR_LOGICAL_CONDITIONS_BOOLEAN_STATEMENTS_INTERPRET_SUBJECT_AND_OBJECT_INDEPENDENTLY_COMPARISON_IDINSTANCE)
	{
		idInstanceString = NLC_TRANSLATOR_LOGICAL_CONDITIONS_BOOLEAN_STATEMENTS_INTERPRET_SUBJECT_AND_OBJECT_INDEPENDENTLY_COMPARISON_IDINSTANCE_STRING;
	}
	#endif
	string instanceName = entityName + idInstanceString;
	return instanceName;
}

string NLCitemClassClass::generateTypeName(string entityName)
{
	string typeName = entityName;
	return typeName;
}

string NLCitemClassClass::removeClassTextFromClassDefinitionName(const string className)
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



#ifdef NLC_INPUT_FUNCTION_LISTS
string NLCitemClassClass::parseFunctionNameFromNLCfunctionName(const string NLCfunctionName)
{
	//gets "fight" from "dog::fight"
	string functionName = "";
	bool hasFunctionOwnerClass = false;
	string functionOwnerName = "";
	parseFunctionNameFromNLCfunctionName(NLCfunctionName, &functionName, &functionOwnerName, &hasFunctionOwnerClass);
	return functionName;
}

void NLCitemClassClass::parseFunctionNameFromNLCfunctionName(const string NLCfunctionName, string* functionName, string* functionOwnerName, bool* hasFunctionOwnerClass)
{
	//gets "fight" from "dog::fight"
	bool hasFunctionObjectClass = false;
	string functionObjectName = "";
	parseFunctionNameFromNLCfunctionName(NLCfunctionName, functionName, functionOwnerName, hasFunctionOwnerClass, &functionObjectName, &hasFunctionObjectClass);
}

void NLCitemClassClass::parseFunctionNameFromNLCfunctionName(const string NLCfunctionName, string* functionName, string* functionOwnerName, bool* hasFunctionOwnerClass, string* functionObjectName, bool* hasFunctionObjectClass)
{
	vector<NLCitem*> additionalArgumentsTempNotUsed;
	parseFunctionNameFromNLCgeneralFunctionName(NLCfunctionName, functionName, functionOwnerName, hasFunctionOwnerClass, functionObjectName, hasFunctionObjectClass, &additionalArgumentsTempNotUsed);
}

#ifdef NLC_LIBRARY
void NLCitemClassClass::parseFunctionNameFromNLClibFunctionName(const string NLCfunctionName, string* functionName, string* functionOwnerName, bool* hasFunctionOwnerClass, string* functionObjectName, bool* hasFunctionObjectClass, vector<NLCitem*>* additionalArguments)
{
	parseFunctionNameFromNLCgeneralFunctionName(NLCfunctionName, functionName, functionOwnerName, hasFunctionOwnerClass, functionObjectName, hasFunctionObjectClass, additionalArguments);
}
#endif

void NLCitemClassClass::parseFunctionNameFromNLCgeneralFunctionName(const string NLCfunctionName, string* functionName, string* functionOwnerName, bool* hasFunctionOwnerClass, string* functionObjectName, bool* hasFunctionObjectClass, vector<NLCitem*>* additionalArguments)
{
	//gets "fight" from "dog::fight"
	*hasFunctionOwnerClass = false;
	*functionOwnerName = "";
	*hasFunctionObjectClass = false;
	*functionObjectName = "";
	*functionName = NLCfunctionName;
	int indexOfActionName = NLCfunctionName.find(NLC_INPUT_FUNCTION_LISTS_ACTION_DELIMITER);
	int indexOfObjectName = NLCfunctionName.find(NLC_INPUT_FUNCTION_LISTS_ACTION_OBJECT_DELIMITER);
	int indexOfFirstArgumentName = NLCfunctionName.find(NLC_INPUT_FUNCTION_LISTS_ACTION_ARGUMENT_DELIMITER);
	int indexOfFirstArgumentOrEnd = NLCfunctionName.length();
	#ifdef NLC_LIBRARY
	if(indexOfFirstArgumentName != CPP_STRING_FIND_RESULT_FAIL_VALUE)
	{
		indexOfFirstArgumentOrEnd = indexOfFirstArgumentName;
	}
	#endif
	if(indexOfActionName != CPP_STRING_FIND_RESULT_FAIL_VALUE)
	{
		if(indexOfObjectName != CPP_STRING_FIND_RESULT_FAIL_VALUE)
		{
			*functionName = NLCfunctionName.substr(indexOfActionName+NLC_INPUT_FUNCTION_LISTS_ACTION_DELIMITER_LENGTH, indexOfObjectName-indexOfActionName-NLC_INPUT_FUNCTION_LISTS_ACTION_DELIMITER_LENGTH);
			*functionOwnerName = NLCfunctionName.substr(0, indexOfActionName);
			*functionObjectName = NLCfunctionName.substr(indexOfObjectName+NLC_INPUT_FUNCTION_LISTS_ACTION_OBJECT_DELIMITER_LENGTH, indexOfFirstArgumentOrEnd-indexOfObjectName-(NLC_INPUT_FUNCTION_LISTS_ACTION_OBJECT_DELIMITER_LENGTH));
			*hasFunctionOwnerClass = true;
			*hasFunctionObjectClass = true;
		}
		else
		{
			*functionName = NLCfunctionName.substr(indexOfActionName+NLC_INPUT_FUNCTION_LISTS_ACTION_DELIMITER_LENGTH, indexOfFirstArgumentOrEnd-indexOfActionName-NLC_INPUT_FUNCTION_LISTS_ACTION_DELIMITER_LENGTH);
			*functionOwnerName = NLCfunctionName.substr(0, indexOfActionName);
			*hasFunctionOwnerClass = true;
		}
	}
	else if(indexOfObjectName != CPP_STRING_FIND_RESULT_FAIL_VALUE)
	{
		*functionName = NLCfunctionName.substr(0, indexOfObjectName);
		*functionObjectName = NLCfunctionName.substr(indexOfObjectName+NLC_INPUT_FUNCTION_LISTS_ACTION_OBJECT_DELIMITER_LENGTH, indexOfFirstArgumentOrEnd-indexOfObjectName-(NLC_INPUT_FUNCTION_LISTS_ACTION_OBJECT_DELIMITER_LENGTH));
		*hasFunctionObjectClass = true;
	}
	else
	{
		*functionName = NLCfunctionName.substr(0, indexOfFirstArgumentOrEnd);
	}

	#ifdef NLC_LIBRARY
	if(indexOfFirstArgumentName != CPP_STRING_FIND_RESULT_FAIL_VALUE)
	{
		int indexOfArgument = indexOfFirstArgumentName+NLC_INPUT_FUNCTION_LISTS_ACTION_ARGUMENT_DELIMITER_LENGTH;
		bool stillFindingArguments = true;
		while(stillFindingArguments)
		{
			string argumentName = "";
			int indexOfArgumentNew = NLCfunctionName.find(NLC_INPUT_FUNCTION_LISTS_ACTION_ARGUMENT_DELIMITER, indexOfArgument);
			if(indexOfArgumentNew != CPP_STRING_FIND_RESULT_FAIL_VALUE)
			{
				argumentName = NLCfunctionName.substr(indexOfArgument, indexOfArgumentNew-indexOfArgument);
			}
			else
			{
				argumentName = NLCfunctionName.substr(indexOfArgument, NLCfunctionName.length()-indexOfArgument);
				stillFindingArguments = false;
			}
			NLCitem* functionArgumentItem = new NLCitem(argumentName, NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_INSTANCE_OR_CLASS_LIST);	//NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_INSTANCE_OR_CLASS_LIST
			additionalArguments->push_back(functionArgumentItem);
			indexOfArgument = indexOfArgumentNew+NLC_INPUT_FUNCTION_LISTS_ACTION_ARGUMENT_DELIMITER_LENGTH;
		}
	}
	#endif
}

string NLCitemClassClass::generateNLCfunctionHeader(const string functionName, const string functionOwnerName, const bool hasFunctionOwnerClass, const string functionObjectName, const bool hasFunctionObjectClass)
{
	string NLCfunctionHeader = string(NLC_PREPROCESSOR_FUNCTION_HEADER_STRING) + NLC_PREPROCESSOR_FUNCTION_HEADER_MID_CHAR;
	if(hasFunctionOwnerClass)
	{
		NLCfunctionHeader = NLCfunctionHeader + functionOwnerName + NLC_INPUT_FUNCTION_LISTS_ACTION_DELIMITER;
	}
	NLCfunctionHeader = NLCfunctionHeader + functionName;
	if(hasFunctionObjectClass)
	{
		NLCfunctionHeader = NLCfunctionHeader + NLC_INPUT_FUNCTION_LISTS_ACTION_OBJECT_DELIMITER + functionObjectName;
	}
	NLCfunctionHeader = NLCfunctionHeader + CHAR_NEWLINE;
	return NLCfunctionHeader;
}

#endif

bool NLCitemClassClass::findFunctionArgument(vector<NLCitem*>* parameters, const GIAentityNode* entity, const int itemType, constEffective NLCitem** functionArgument)
{
	bool foundFunctionArgument = false;
	for(vector<NLCitem*>::iterator parametersIterator = parameters->begin(); parametersIterator < parameters->end(); parametersIterator++)
	{
		NLCitem* currentItem = *parametersIterator;
		if(currentItem->itemType == itemType)
		{
			#ifdef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES
			if(currentItem->instanceName == generateInstanceName(entity))
			#else
			if(currentItem->name == entity->entityName)	//or if(currentItem->className == generateClassName(entity->entityName))
			#endif
			{
				*functionArgument = currentItem;
				foundFunctionArgument = true;
			}
		}
	}
	return foundFunctionArgument;
}

bool NLCitemClassClass::detectPredeterminer(GIAentityNode* entity, int sentenceIndex)
{
	bool predeterminerDetected = false;
	
	#ifdef GIA_ADVANCED_REFERENCING_SUPPORT_REFERENCING_OF_ENTITIES_WITH_PREDETERMINERS			
	unordered_map<int,int>::iterator iterTemp = entity->grammaticalPredeterminerTempSentenceArray.find(sentenceIndex);
	if(iterTemp !=  entity->grammaticalPredeterminerTempSentenceArray.end())
	//if(entity->grammaticalPredeterminerTempSentenceArray.at(sentenceIndex) != -1)
	{
		//predeterminerDetected = SHAREDvars.intInIntArray(grammaticalPredeterminerTempSentenceArray.at(sentenceIndex)->second, entityPredeterminerSmallArray, GRAMMATICAL_PREDETERMINER_SMALL_ARRAY_NUMBER_OF_TYPES);
		predeterminerDetected = SHAREDvars.intInIntArray(iterTemp->second, entityPredeterminerSmallArray, GRAMMATICAL_PREDETERMINER_SMALL_ARRAY_NUMBER_OF_TYPES);
	}
	#else
	predeterminerDetected = SHAREDvars.intInIntArray(entity->grammaticalPredeterminerTemp, entityPredeterminerSmallArray, GRAMMATICAL_PREDETERMINER_SMALL_ARRAY_NUMBER_OF_TYPES);
	#endif
	
	return predeterminerDetected;
}
