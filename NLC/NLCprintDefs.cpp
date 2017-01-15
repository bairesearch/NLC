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
 * File Name: NLCprintDefs.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2014 Baxter AI (baxterai.com)
 * Project: Natural Language Programming Interface (compiler)
 * Project Version: 1l9a 05-November-2014
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/

#include "NLCprintDefs.h"

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

string generatePropertyListName(string propertyClassName)
{
	string propertyListName = propertyClassName + NLC_ITEM_TYPE_PROPERTYLIST_VAR_APPENDITION;
	return propertyListName;
}

#ifdef NLC_RECORD_ACTION_HISTORY
string generateActionListName(string actionClassName)
{
	string actionListName = actionClassName + NLC_ITEM_TYPE_ACTION_VAR_APPENDITION;
	return actionListName;
}
string generateActionIncomingListName(string actionClassName)
{
	string actionIncomingListName = actionClassName + NLC_ITEM_TYPE_ACTIONINCOMING_VAR_APPENDITION;
	return actionIncomingListName;
}
string generateActionSubjectListName(string actionSubjectClassName)
{
	string actionSubjectListName = actionSubjectClassName + NLC_ITEM_TYPE_ACTIONSUBJECT_VAR_APPENDITION;
	return actionSubjectListName;
}
string generateActionObjectListName(string actionObjectClassName)
{
	string actionObjectListName = actionObjectClassName + NLC_ITEM_TYPE_ACTIONOBJECT_VAR_APPENDITION;
	return actionObjectListName;
}
#endif

string generateEntityListName(NLCitem * entityParam)
{
	#ifdef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES
		string instanceName = entityParam->instanceName;
		#ifdef NLC_USE_ORIGINAL_INSTANCE_LIST_NAMES
		string entityListName = instanceName + generateEntityListAppendName();
		#else
		string entityListName = instanceName + generateEntityListAppendName();	
		#endif
	#else
		string className = entityParam->className;
		string entityListName = className + generateEntityListAppendName();		
	#endif
	return entityListName;
}

string generateEntityListAppendName()
{
	#ifdef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES
		#ifdef NLC_USE_ORIGINAL_INSTANCE_LIST_NAMES
		string entityLocalListAppendName = NLC_ITEM_TYPE_PROPERTYLIST_VAR_APPENDITION;
		#else
		string entityLocalListAppendName = NLC_ITEM_TYPE_INSTANCELIST_VAR_APPENDITION;	
		#endif
	#else
		string entityLocalListAppendName =  NLC_ITEM_TYPE_LIST_VAR_APPENDITION;		
	#endif
	return entityLocalListAppendName;
}

string generateGenericListName(string genericObjectName, string genericListAppendName)
{
	#ifdef NLC_USE_ORIGINAL_INSTANCE_LIST_NAMES
	string propertyListName = genericObjectName + genericListAppendName + NLC_ITEM_TYPE_PROPERTYLIST_VAR_APPENDITION;
	#else
	string propertyListName = genericObjectName + genericListAppendName + NLC_ITEM_TYPE_LIST_VAR_APPENDITION;
	#endif
	return propertyListName;
}

string generateConditionListName(string conditionClassName, string conditionObjectClassName)
{
	#ifdef NLC_USE_STRING_INDEXED_UNORDERED_MAPS_FOR_CONDITION_LISTS
	string conditionListName = conditionObjectClassName + NLC_ITEM_TYPE_CONDITIONLIST_VAR_APPENDITION;	
	#else
	string conditionListName = conditionClassName + conditionObjectClassName + NLC_ITEM_TYPE_CONDITIONLIST_VAR_APPENDITION;
	#endif
	return conditionListName;
}

string generateConditionPairDefinitionName(string conditionClassName, string conditionObjectClassName)
{
	#ifdef NLC_USE_STRING_INDEXED_UNORDERED_MAPS_FOR_CONDITION_LISTS
	string conditionListName = conditionObjectClassName + NLC_ITEM_TYPE_CONDITIONPAIR_VAR_APPENDITION;
	#else
	string conditionListName = conditionClassName + conditionObjectClassName + NLC_ITEM_TYPE_CONDITIONPAIR_VAR_APPENDITION;
	#endif
	return conditionListName;
}

string generateCodeConditionPairText(string conditionName, string conditionClassName, string conditionInstanceName, string conditionObjectClassName, string conditionObjectInstanceName, int progLang)
{
	#ifdef NLC_USE_STRING_INDEXED_UNORDERED_MAPS_FOR_CONDITION_LISTS
	//OLD: string codeConditionPairTypeText = progLangStringOpenClose[progLang] + conditionName + progLangStringOpenClose[progLang] + progLangParameterSpaceNextParam[progLang] + conditionObjectInstanceName + progLangCloseParameterSpace[progLang]
	string codeConditionPairTypeText = progLangClassPairTypeStart[progLang] + progLangClassList2DTypeConditionTypeVar[progLang] + progLangClassList2DTypeMiddle[progLang] + conditionObjectClassName + progLangPointer[progLang] + progLangClassPairTypeEnd[progLang] + progLangClassMemberFunctionParametersOpen[progLang] + progLangStringOpenClose[progLang] + conditionName + progLangStringOpenClose[progLang] + progLangClassMemberFunctionParametersNext[progLang] + conditionObjectInstanceName + progLangClassMemberFunctionParametersClose[progLang];
	//TEMP: string codeConditionPairTypeText = progLangClassPairTypeStart[progLang] + progLangClassList2DTypeConditionTypeVar[progLang] + progLangPointer[progLang] + progLangClassList2DTypeMiddle[progLang] + conditionObjectClassName + progLangPointer[progLang] + progLangClassPairTypeEnd[progLang] + progLangClassMemberFunctionParametersOpen[progLang] + conditionInstanceName + progLangClassMemberFunctionParametersNext[progLang] + conditionObjectInstanceName + progLangClassMemberFunctionParametersClose[progLang];
	#else
	string codeConditionPairTypeText = progLangClassPairTypeStart[progLang] + conditionClassName + progLangPointer[progLang] + progLangClassList2DTypeMiddle[progLang] + conditionObjectClassName + progLangPointer[progLang] + progLangClassPairTypeEnd[progLang] + progLangClassMemberFunctionParametersOpen[progLang] + conditionInstanceName + progLangClassMemberFunctionParametersNext[progLang] + conditionObjectInstanceName + progLangClassMemberFunctionParametersClose[progLang];	
	#endif
	return codeConditionPairTypeText;
}

string generateCodeConditionPairTextWithContext(string conditionName, string conditionClassName, string conditionInstanceName, string conditionObjectClassName, string conditionObjectInstanceName, vector<string> * conditionContext, int progLang)
{
	#ifdef NLC_USE_STRING_INDEXED_UNORDERED_MAPS_FOR_CONDITION_LISTS
	//OLD: string codeConditionPairTypeText = progLangStringOpenClose[progLang] + conditionName + progLangStringOpenClose[progLang] + progLangParameterSpaceNextParam[progLang] + conditionObjectInstanceName + progLangCloseParameterSpace[progLang]
	string codeConditionPairTypeText = progLangClassPairTypeStart[progLang] + progLangClassList2DTypeConditionTypeVar[progLang] + progLangClassList2DTypeMiddle[progLang] + conditionObjectClassName + progLangPointer[progLang] + progLangClassPairTypeEnd[progLang] + progLangClassMemberFunctionParametersOpen[progLang] + progLangStringOpenClose[progLang] + generateInstanceNameWithContext(conditionInstanceName, conditionContext, progLang) + progLangStringOpenClose[progLang] + progLangClassMemberFunctionParametersNext[progLang] + generateInstanceNameWithContext(conditionObjectInstanceName, conditionContext, progLang) + progLangClassMemberFunctionParametersClose[progLang];
	//TEMP: string codeConditionPairTypeText = progLangClassPairTypeStart[progLang] + progLangClassList2DTypeConditionTypeVar[progLang] + progLangPointer[progLang] + progLangClassList2DTypeMiddle[progLang] + conditionObjectClassName + progLangPointer[progLang] + progLangClassPairTypeEnd[progLang] + progLangClassMemberFunctionParametersOpen[progLang] + generateInstanceNameWithContext(conditionInstanceName, conditionContext, progLang) + progLangClassMemberFunctionParametersNext[progLang] + generateInstanceNameWithContext(conditionObjectInstanceName, conditionContext, progLang) + progLangClassMemberFunctionParametersClose[progLang];
	#else
	string codeConditionPairTypeText = progLangClassPairTypeStart[progLang] + conditionClassName + progLangPointer[progLang] + progLangClassList2DTypeMiddle[progLang] + conditionObjectClassName + progLangPointer[progLang] + progLangClassPairTypeEnd[progLang] + progLangClassMemberFunctionParametersOpen[progLang] + generateInstanceNameWithContext(conditionInstanceName, conditionContext, progLang) + progLangClassMemberFunctionParametersNext[progLang] + generateInstanceNameWithContext(conditionObjectInstanceName, conditionContext, progLang) + progLangClassMemberFunctionParametersClose[progLang];	
	#endif
	return codeConditionPairTypeText;
}

string generateInstanceNameWithContext(string instanceName, vector<string> * context, int progLang)
{
	string instanceNameWithContext = "";
	string contextString = generateStringFromContextVector(context, progLang);
	instanceNameWithContext = contextString + instanceName;
	return instanceNameWithContext;
}

string generateStringFromContextVector(vector<string> * context, int progLang)
{
	string contextString = "";
	for(vector<string>::iterator contextIterator = context->begin(); contextIterator < context->end(); contextIterator++)
	{
		string currentContext = *contextIterator;
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


string generateCodePropertyListDefinitionText(string propertyClassName, int progLang)
{
	string codePropertyListDefinitionText = generateCodeEntityListDefinitionTypeText(propertyClassName, progLang) + generatePropertyListName(propertyClassName);
	return codePropertyListDefinitionText;
}

string generateCodeEntityListDefinitionText(NLCitem * entityParam, int progLang)
{
	string codeEntityListDefinitionText = generateCodeEntityListDefinitionTypeText(entityParam->className, progLang) + generateEntityListName(entityParam);
	return codeEntityListDefinitionText;
}

string generateCodeEntityListDefinitionTypeText(string entityClassName, int progLang)
{
	string codeEntityListDefinitionTypeText = progLangClassListTypeStart[progLang] + entityClassName + progLangPointer[progLang] + progLangClassListTypeEnd[progLang];
	return codeEntityListDefinitionTypeText;
}

string generateCodeEntityListDefinitionReferenceText(NLCitem * entityParam, int progLang)
{
	string codeEntityListDefinitionReferenceText = generateCodeEntityListDefinitionReferenceTypeText(entityParam->className, progLang) + generateEntityListName(entityParam);
	return codeEntityListDefinitionReferenceText;
}

string generateCodeEntityListDefinitionReferenceTypeText(string entityClassName, int progLang)
{
	#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_PASS_LISTS_BY_REFERENCE
	string codeEntityListDefinitionReferenceTypeText = generateCodeEntityListDefinitionTypeText(entityClassName, progLang) + progLangReference[progLang];
	#else
	string codeEntityListDefinitionReferenceTypeText = generateCodeEntityListDefinitionTypeText(entityClassName, progLang);	
	#endif
	return codeEntityListDefinitionReferenceTypeText;
}

string generateCodeGenericListDefinitionText(NLCitem * entityParam, string genericListAppendName, int progLang)
{
	string codeGenericListDefinitionText = generateCodeEntityListDefinitionTypeText(entityParam->className, progLang) + generateGenericListName(entityParam->genericObjectName, genericListAppendName);
	return codeGenericListDefinitionText;
}



string generateCodeConditionListDefinitionText(string conditionClassName, string conditionObjectClassName, int progLang)
{
	string codeConditionListDefinitionText = generateCodeConditionListDefinitionTypeText(conditionClassName, conditionObjectClassName, progLang) + generateConditionListName(conditionClassName, conditionObjectClassName);
	return codeConditionListDefinitionText;
}
string generateCodeConditionListDefinitionTypeText(string conditionClassName, string conditionObjectClassName, int progLang)
{
	#ifdef NLC_USE_STRING_INDEXED_UNORDERED_MAPS_FOR_CONDITION_LISTS
	string codeConditionListDefinitionTypeText = progLangClassList2DTypeStart[progLang] + progLangClassList2DTypeConditionTypeVar[progLang] + progLangClassList2DTypeMiddle[progLang] + conditionObjectClassName + progLangPointer[progLang] + progLangClassListTypeEnd[progLang];
	#else
	string codeConditionListDefinitionTypeText = progLangClassList2DTypeStart[progLang] + conditionClassName + progLangPointer[progLang] + progLangClassList2DTypeMiddle[progLang] + conditionObjectClassName + progLangPointer[progLang] + progLangClassListTypeEnd[progLang];
	#endif
	return codeConditionListDefinitionTypeText;
}

#ifdef NLC_GENERATE_TYPE_LISTS
string generateCodeEntityListDefinitionTypeText2(string propertyClassName, int progLang)
{
	string codePropertyListDefinitionText = progLangClassListTypeStart[progLang] + progLangClassListTypeStart[progLang] + propertyClassName + progLangPointer[progLang] + progLangClassListTypeEnd[progLang] + progLangClassListTypeEnd[progLang];
	return codePropertyListDefinitionText;
}
#endif

string generateEntityDeclaration(NLCitem * param, int progLang)
{
	string tempVariableName = generateEntityDeclaration(param->className, param->instanceName, progLang);
	return tempVariableName;
}

string generateEntityDeclaration(string className, string instanceName, int progLang)
{
	string tempVariableName = className + progLangPointer[progLang] + STRING_SPACE + instanceName;
	return tempVariableName;
}

string generateDynamicCastOfEntity(string entityName, string castClassName, int progLang)
{
	string castText = progLangDynamicCastStart[progLang] + castClassName + progLangDynamicCastEnd[progLang] + progLangOpenParameterSpace[progLang] + entityName + progLangCloseParameterSpace[progLang];	//dynamic_cast<castClassName*>(entityName)
	return castText;
}

//this code is not currently used;
string generateCodeEntityStringPairListDefinitionText(string entityClassName, string genericListNameStart, string genericListAppendName, int progLang)
{
	string codeEntityStringPairListDefinitionText = generateCodeEntityStringPairListDefinitionTypeText(entityClassName, progLang) + generateEntityStringPairListName(genericListNameStart, genericListAppendName);	//unordered_map<string, entityClassName*> genericListNameStart+genericListAppendName;
	return codeEntityStringPairListDefinitionText;
}
string generateCodeEntityStringPairListDefinitionTypeText(string entityClassName, int progLang)
{
	string codeEntityStringPairListDefinitionTypeText = progLangClassList2DTypeStart[progLang] + progLangClassList2DTypeConditionTypeVar[progLang] + progLangClassList2DTypeMiddle[progLang] + entityClassName + progLangPointer[progLang] + progLangClassListTypeEnd[progLang];	//unordered_map<string, entityClassName*>
	return codeEntityStringPairListDefinitionTypeText;
}
string generateEntityStringPairListName(string genericListNameStart, string genericListAppendName)
{
	string codeEntityStringPairPairText = genericListNameStart + genericListAppendName;	//genericListNameStart+genericListAppendName
	return codeEntityStringPairPairText;
}
string generateEntityStringPairText(string entity1Name, string entity2ClassName, string entity2Name, int progLang)
{
	string codeEntityStringPairPairTypeText = progLangClassPairTypeStart[progLang] + progLangClassList2DTypeConditionTypeVar[progLang] + progLangClassList2DTypeMiddle[progLang] + entity2ClassName + progLangPointer[progLang] + progLangClassPairTypeEnd[progLang] + progLangClassMemberFunctionParametersOpen[progLang] + progLangStringOpenClose[progLang] + entity1Name + progLangStringOpenClose[progLang] + progLangClassMemberFunctionParametersNext[progLang] + entity2Name + progLangClassMemberFunctionParametersClose[progLang];	//pair<string, entity2className*>(entity1name, entity2name)
	return codeEntityStringPairPairTypeText;
}

