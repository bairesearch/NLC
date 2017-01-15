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
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2015 Baxter AI (baxterai.com)
 * Project: Natural Language Programming Interface (compiler)
 * Project Version: 1o4b 13-February-2015
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/


#include "NLCprintDefs.h"

void printLine(string command, int level, string* code)
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

string generatePropertyListName(NLCitem* item)
{
	return generatePropertyListName(item->className);
}
#ifdef NLC_NONOO
string generatePropertyListName(string propertyClassName)
{
	return generatePropertyListName();
}
string generatePropertyListName()
{
	string propertyListName = GIA_ENTITYNODECLASS_PROPERTYNODELIST_NAME;
	return propertyListName;
}
string generatePropertyReverseListName()
{
	string propertyListName = GIA_ENTITYNODECLASS_PROPERTYNODEREVERSELIST_NAME;
	return propertyListName;
}
#else
string generatePropertyListName(string propertyClassName)
{
	string propertyListName = propertyClassName + NLC_ITEM_TYPE_PROPERTYLIST_VAR_APPENDITION;
	return propertyListName;
}
#endif

#ifdef NLC_RECORD_ACTION_HISTORY
#ifdef NLC_NONOO
string generateActionListName(string actionClassName)
{
	return generateActionListName();
}
string generateActionIncomingListName(string actionClassName)
{
	return generateActionIncomingListName();
}
string generateActionSubjectListName(string actionSubjectClassName)
{
	return generateActionSubjectListName();
}
string generateActionObjectListName(string actionObjectClassName)
{
	return generateActionObjectListName();
}
string generateActionListName()
{
	string actionListName = GIA_ENTITYNODECLASS_ACTIONNODELIST_NAME;
	return actionListName;
}
string generateActionIncomingListName()
{
	string actionIncomingListName = GIA_ENTITYNODECLASS_INCOMINGACTIONNODELIST_NAME;
	return actionIncomingListName;
}
string generateActionSubjectListName()
{
	string actionSubjectListName = GIA_ENTITYNODECLASS_ACTIONSUBJECTLIST_NAME;
	return actionSubjectListName;
}
string generateActionObjectListName()
{
	string actionObjectListName = GIA_ENTITYNODECLASS_ACTIONOBJECTLIST_NAME;
	return actionObjectListName;
}
#else
string generateActionListName(string actionClassName)
{
	string actionListName = generateGenericListName(actionClassName, NLC_ITEM_TYPE_ACTION_VAR_APPENDITION);
	return actionListName;
}
string generateActionIncomingListName(string actionClassName)
{
	string actionIncomingListName = generateGenericListName(actionClassName, NLC_ITEM_TYPE_ACTIONINCOMING_VAR_APPENDITION);
	return actionIncomingListName;
}
string generateActionSubjectListName(string actionSubjectClassName)
{
	string actionSubjectListName = generateGenericListName(actionSubjectClassName, NLC_ITEM_TYPE_ACTIONSUBJECT_VAR_APPENDITION);
	return actionSubjectListName;
}
string generateActionObjectListName(string actionObjectClassName)
{
	string actionObjectListName = generateGenericListName(actionObjectClassName, NLC_ITEM_TYPE_ACTIONOBJECT_VAR_APPENDITION);
	return actionObjectListName;
}
#endif
#endif

string generateLocalListName(NLCitem* item)
{
	return generateEntityListName(item);
}
string generateEntityListName(NLCitem* entityParam)
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

#ifdef NLC_NONOO
string generateConditionListName(string conditionClassName, string conditionObjectClassName)
{
	return generateConditionListName();
}
string generateConditionListName()
{
	return generateGIAconditionListName();
}
string generateGIAconditionListName()
{
	string conditionListName = GIA_ENTITYNODECLASS_CONDITIONNODELIST_NAME;
	return conditionListName;
}
string generateGIAconditionObjectListName()
{
	string conditionListName = GIA_ENTITYNODECLASS_CONDITIONOBJECTLIST_NAME;
	return conditionListName;
}
string generateGIAincomingConditionListName()
{
	string conditionListName = GIA_ENTITYNODECLASS_INCOMINGCONDITIONNODELIST_NAME;
	return conditionListName;
}
string generateGIAconditionSubjectListName()
{
	string conditionListName =  GIA_ENTITYNODECLASS_CONDITIONSUBJECTLIST_NAME;
	return conditionListName;
}
#else
string generateConditionListName(NLCitem* conditionItem, NLCitem* conditionObjectItem)
{
	return generateConditionListName(conditionItem->className, conditionObjectItem->className);
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
	string codeConditionPairTypeText = progLangClassPairTypeStart[progLang] + progLangClassList2DTypeConditionTypeVar[progLang] + progLangClassList2DTypeMiddle[progLang] + conditionObjectClassName + progLangPointer[progLang] + progLangClassPairTypeEnd[progLang] + progLangClassMemberFunctionParametersOpen[progLang] + progLangStringOpenClose[progLang] + conditionName + progLangStringOpenClose[progLang] + progLangClassMemberFunctionParametersNext[progLang] + conditionObjectInstanceName + progLangClassMemberFunctionParametersClose[progLang];
	#else
	string codeConditionPairTypeText = progLangClassPairTypeStart[progLang] + conditionClassName + progLangPointer[progLang] + progLangClassList2DTypeMiddle[progLang] + conditionObjectClassName + progLangPointer[progLang] + progLangClassPairTypeEnd[progLang] + progLangClassMemberFunctionParametersOpen[progLang] + conditionInstanceName + progLangClassMemberFunctionParametersNext[progLang] + conditionObjectInstanceName + progLangClassMemberFunctionParametersClose[progLang];	
	#endif
	return codeConditionPairTypeText;
}

string generateCodeConditionPairTextWithContext(string conditionName, string conditionClassName, string conditionInstanceName, string conditionObjectClassName, string conditionObjectInstanceName, vector<string>* conditionContext, int progLang)
{
	#ifdef NLC_USE_STRING_INDEXED_UNORDERED_MAPS_FOR_CONDITION_LISTS
	string codeConditionPairTypeText = progLangClassPairTypeStart[progLang] + progLangClassList2DTypeConditionTypeVar[progLang] + progLangClassList2DTypeMiddle[progLang] + conditionObjectClassName + progLangPointer[progLang] + progLangClassPairTypeEnd[progLang] + progLangClassMemberFunctionParametersOpen[progLang] + progLangStringOpenClose[progLang] + generateInstanceNameWithContext(conditionInstanceName, conditionContext, progLang) + progLangStringOpenClose[progLang] + progLangClassMemberFunctionParametersNext[progLang] + generateInstanceNameWithContext(conditionObjectInstanceName, conditionContext, progLang) + progLangClassMemberFunctionParametersClose[progLang];
	#else
	string codeConditionPairTypeText = progLangClassPairTypeStart[progLang] + conditionClassName + progLangPointer[progLang] + progLangClassList2DTypeMiddle[progLang] + conditionObjectClassName + progLangPointer[progLang] + progLangClassPairTypeEnd[progLang] + progLangClassMemberFunctionParametersOpen[progLang] + generateInstanceNameWithContext(conditionInstanceName, conditionContext, progLang) + progLangClassMemberFunctionParametersNext[progLang] + generateInstanceNameWithContext(conditionObjectInstanceName, conditionContext, progLang) + progLangClassMemberFunctionParametersClose[progLang];	
	#endif
	return codeConditionPairTypeText;
}
#endif

string generateInstanceNameWithContext(string instanceName, vector<string>* context, int progLang)
{
	string instanceNameWithContext = "";
	string contextString = generateStringFromContextVector(context, progLang);
	instanceNameWithContext = contextString + instanceName;
	return instanceNameWithContext;
}

string generateStringFromContextVector(vector<string>* context, int progLang)
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

string generateCodeEntityListDefinitionText(NLCitem* entityParam, int progLang)
{
	#ifdef NLC_NONOO
	string codeEntityListDefinitionText = generateCodeEntityListDefinitionTypeText(progLang) + generateEntityListName(entityParam);
	#else
	string codeEntityListDefinitionText = generateCodeEntityListDefinitionTypeText(entityParam->className, progLang) + generateEntityListName(entityParam);
	#endif
	return codeEntityListDefinitionText;
}
string generateCodeEntityListDefinitionText(string className, string instanceName, int progLang)
{
	#ifdef NLC_NONOO
	string codeEntityListDefinitionText = generateCodeEntityListDefinitionTypeText(NLCNONOO_GENERIC_ENTITY_NODE_NAME, progLang) + instanceName;
	#else
	string codeEntityListDefinitionText = generateCodeEntityListDefinitionTypeText(className, progLang) + instanceName;
	#endif
	return codeEntityListDefinitionText;
}


#ifdef NLC_NONOO
string generateCodeEntityListDefinitionTypeText(string entityClassName, int progLang)
{
	return generateCodeEntityListDefinitionTypeText(progLang);
}
string generateCodeEntityListDefinitionTypeText(int progLang)
{
	string codeEntityListDefinitionTypeText = progLangClassListTypeStart[progLang] + NLCNONOO_GENERIC_ENTITY_NODE_NAME + progLangPointer[progLang] + progLangClassListTypeEnd[progLang];
	return codeEntityListDefinitionTypeText;
}
#else
string generateCodeEntityListDefinitionTypeText(string entityClassName, int progLang)
{
	string codeEntityListDefinitionTypeText = progLangClassListTypeStart[progLang] + entityClassName + progLangPointer[progLang] + progLangClassListTypeEnd[progLang];	//vector<entityClassName*>
	return codeEntityListDefinitionTypeText;
}
string generateCodeEntityListDefinitionTypeTextPointer(string entityClassName, int progLang)
{
	string codePropertyListDefinitionTextPointer = generateCodeEntityListDefinitionTypeText(entityClassName, progLang) + progLangPointer[progLang];		//vector<entityClassName*>* 
	return codePropertyListDefinitionTextPointer;
}
#ifdef NLC_GENERATE_TYPE_LISTS
string generateCodeEntityListDefinitionTypeText2(string propertyClassName, int progLang)
{
	string codePropertyListDefinitionText = progLangClassListTypeStart[progLang] + progLangClassListTypeStart[progLang] + propertyClassName + progLangPointer[progLang] + progLangClassListTypeEnd[progLang] + progLangClassListTypeEnd[progLang];
	return codePropertyListDefinitionText;
}
#endif
#endif

string generateCodeEntityListDefinitionReferenceText(NLCitem* entityParam, int progLang)
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

string generateCodeGenericListDefinitionText(NLCitem* entityParam, string genericListAppendName, int progLang)
{
	string codeGenericListDefinitionText = generateCodeEntityListDefinitionTypeText(entityParam->className, progLang) + generateGenericListName(entityParam->genericObjectName, genericListAppendName);
	return codeGenericListDefinitionText;
}




string generateCodeConditionListDefinitionText(string conditionClassName, string conditionObjectClassName, int progLang)
{
	string codeConditionListDefinitionText = generateCodeConditionListDefinitionTypeText(conditionClassName, conditionObjectClassName, progLang) + generateConditionListName(conditionClassName, conditionObjectClassName);
	return codeConditionListDefinitionText;
}
#ifdef NLC_NONOO
string generateCodeConditionListDefinitionTypeText(string conditionClassName, string conditionObjectClassName, int progLang)
{
	return generateCodeConditionListDefinitionTypeText(progLang);
}
string generateCodeConditionListDefinitionTypeText(int progLang)
{
	string codeConditionListDefinitionTypeText = generateCodeEntityListDefinitionTypeText(progLang);
	return codeConditionListDefinitionTypeText;
}
#else
string generateCodeConditionListDefinitionTypeText(string conditionClassName, string conditionObjectClassName, int progLang)
{
	#ifdef NLC_USE_STRING_INDEXED_UNORDERED_MAPS_FOR_CONDITION_LISTS
	string codeConditionListDefinitionTypeText = progLangClassList2DTypeStart[progLang] + progLangClassList2DTypeConditionTypeVar[progLang] + progLangClassList2DTypeMiddle[progLang] + conditionObjectClassName + progLangPointer[progLang] + progLangClassListTypeEnd[progLang];	//unordered_map<string, conditionObjectClassName*>
	#else
	string codeConditionListDefinitionTypeText = progLangClassList2DTypeStart[progLang] + conditionClassName + progLangPointer[progLang] + progLangClassList2DTypeMiddle[progLang] + conditionObjectClassName + progLangPointer[progLang] + progLangClassListTypeEnd[progLang];	//unordered_map<conditionClassName*, conditionObjectClassName*>
	#endif
	return codeConditionListDefinitionTypeText;
}
string generateCodeConditionListDefinitionTypeTextPointer(string conditionClassName, string conditionObjectClassName, int progLang)
{
	string codeConditionListDefinitionTypeTextPointer = generateCodeConditionListDefinitionTypeText(conditionClassName, conditionObjectClassName, progLang) + progLangPointer[progLang];	//unordered_map<conditionClassName*, conditionObjectClassName*>* 
	return codeConditionListDefinitionTypeTextPointer;
}
#endif

//NB NLC_NONOO requires !NLC_USE_STRING_INDEXED_UNORDERED_MAPS_FOR_CONDITION_LISTS
void generateCodeAddConditionAndObjectEntityToList(NLCitem* param1, NLCitem* param2, NLCitem* param3, int progLang, string* code, int level)
{
	string contextParam1 = generateStringFromContextVector(&(param1->context), progLang);
	#ifdef NLC_NONOO
	string codeBlockText = contextParam1 + param1->instanceName + progLangObjectReferenceDelimiter[progLang] + generateGIAconditionListName() + progLangObjectReferenceDelimiter2[progLang] + progLangAddProperty[progLang] + progLangOpenParameterSpace[progLang] + param2->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//context1->param1->param2ConditionList.push_back(param2);
	printLine(codeBlockText, level, code);
	codeBlockText = param2->instanceName + progLangObjectReferenceDelimiter[progLang] + generateGIAconditionObjectListName() + progLangObjectReferenceDelimiter2[progLang] + progLangAddProperty[progLang] + progLangOpenParameterSpace[progLang] + param3->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//param2->param2ConditionObjectList.push_back(param3);
	printLine(codeBlockText, level, code);
	#ifdef NLC_NONOO_CREATE_REVERSE_LISTS
	codeBlockText = param3->instanceName + progLangObjectReferenceDelimiter[progLang] + generateGIAincomingConditionListName() + progLangObjectReferenceDelimiter2[progLang] + progLangAddProperty[progLang] + progLangOpenParameterSpace[progLang] + param2->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//param3->param2IncomingConditionList.push_back(param2);
	printLine(codeBlockText, level, code);
	codeBlockText = param2->instanceName + progLangObjectReferenceDelimiter[progLang] + generateGIAconditionSubjectListName() + progLangObjectReferenceDelimiter2[progLang] + progLangAddProperty[progLang] + progLangOpenParameterSpace[progLang] + contextParam1 + param1->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//param2->param2ConditionSubjectList.push_back(context1->param1);
	printLine(codeBlockText, level, code);
	#endif
	#else
	string codeBlockText = contextParam1 + param1->instanceName + progLangObjectReferenceDelimiter[progLang] + generateConditionListName(param2->className, param3->className) + progLangObjectReferenceDelimiter2[progLang] + progLangAddCondition[progLang] + progLangOpenParameterSpace[progLang] + generateCodeConditionPairText(param2->name, param2->className, param2->instanceName, param3->className, param3->instanceName, progLang) + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//context1->param1->param2param3ConditionList.insert(pair<param2className, param3className*>(param2, param3));
	printLine(codeBlockText, level, code);
	#endif
}

void generateCodeAddPropertyEntityToList(NLCitem* param1, NLCitem* param2, int progLang, string* code, int level)
{
	string contextParam1 = generateStringFromContextVector(&(param1->context), progLang);
	#ifdef NLC_NONOO
	string codeBlockText = contextParam1 + param1->instanceName + progLangObjectReferenceDelimiter[progLang] + generatePropertyListName() + progLangObjectReferenceDelimiter2[progLang] + progLangAddProperty[progLang] + progLangOpenParameterSpace[progLang] + param2->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//context1->param1->param2PropertyList.push_back(param2);
	printLine(codeBlockText, level, code);
	codeBlockText = param2->instanceName + progLangObjectReferenceDelimiter[progLang] + generatePropertyReverseListName() + progLangObjectReferenceDelimiter2[progLang] + progLangAddProperty[progLang] + progLangOpenParameterSpace[progLang] + contextParam1 + param1->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//param2->param2IncomingPropertyList.push_back(context1->param1);
	printLine(codeBlockText, level, code);
	#else
	string codeBlockText = contextParam1 + param1->instanceName + progLangObjectReferenceDelimiter[progLang] + generatePropertyListName(param2->className) + progLangObjectReferenceDelimiter2[progLang] + progLangAddProperty[progLang] + progLangOpenParameterSpace[progLang] + param2->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//context1->param1->param2PropertyList.push_back(param2);	
	printLine(codeBlockText, level, code);
	#endif
}


			
#ifdef NLC_NONOO
string generateGIAentityName()
{
	string GIAentityName = GIA_ENTITYNODECLASS_ENTITYNAME_NAME;
	return GIAentityName;
}

string generateCodeEntityNameTestText(NLCitem* param, int progLang)
{
	string entityNameTestText = progLangOpenParameterSpace[progLang] + generateTempEntityName(param) + progLangObjectReferenceDelimiter[progLang] + generateGIAentityName() + progLangStringEqualsTest[progLang] + progLangStringOpenClose[progLang] + param->name + progLangStringOpenClose[progLang] + progLangCloseParameterSpace[progLang];
	return entityNameTestText;
}
#endif

string generateCodeNewTempEntity(NLCitem* param, int progLang)
{
	#ifdef NLC_NONOO
	string newTempEntityText = generateTempEntityDeclaration(param, progLang) + progLangEquals[progLang] + progLangNewObject[progLang] + generateTempEntityClassName(param) + progLangOpenParameterSpace[progLang] + progLangStringOpenClose[progLang] + param->name + progLangStringOpenClose[progLang] + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	
	#else
	string newTempEntityText = generateTempEntityDeclaration(param, progLang) + progLangEquals[progLang] + progLangNewObject[progLang] + generateTempEntityClassName(param) + progLangOpenParameterSpace[progLang] + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];
	#endif
	return newTempEntityText;
}

string generateCodeNewTempEntity(string className, string instanceName, int progLang)
{
	#ifdef NLC_NONOO
	string newTempEntityText = generateTempEntityDeclaration(className, instanceName, progLang) + progLangEquals[progLang] + progLangNewObject[progLang] + className + progLangOpenParameterSpace[progLang] + progLangStringOpenClose[progLang] + removeClassTextFromClassDefinitionName(className) + progLangStringOpenClose[progLang] + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	
	#else
	string newTempEntityText = generateTempEntityDeclaration(className, instanceName, progLang) + progLangEquals[progLang] + progLangNewObject[progLang] + className + progLangOpenParameterSpace[progLang] + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];
	#endif
	return newTempEntityText;
}

string generateTempEntityDeclaration(NLCitem* param, int progLang)
{
	string tempVariableName = generateTempEntityDeclaration(generateTempEntityClassName(param), generateTempEntityName(param), progLang);	//ClassName* instanceName
	return tempVariableName;
}

string generateTempEntityName(NLCitem* param)
{
	return param->instanceName;
}

string generateTempEntityClassName(NLCitem* param)
{
	#ifdef NLC_NONOO
	return NLCNONOO_GENERIC_ENTITY_NODE_NAME;
	#else
	return param->className;
	#endif
}

string generateTempEntityDeclaration(string className, string instanceName, int progLang)
{
	#ifdef NLC_NONOO
	string tempVariableName = string(NLCNONOO_GENERIC_ENTITY_NODE_NAME) + progLangPointer[progLang] + STRING_SPACE + instanceName;	//GIAentityNode* instanceName
	#else
	string tempVariableName = className + progLangPointer[progLang] + STRING_SPACE + instanceName;	//ClassName* instanceName
	#endif
	return tempVariableName;
}


string generateDynamicCastOfEntity(string entityName, string castClassName, int progLang)
{
	string castText = progLangDynamicCastStart[progLang] + castClassName + progLangDynamicCastEnd[progLang] + progLangOpenParameterSpace[progLang] + entityName + progLangCloseParameterSpace[progLang];	//dynamic_cast<castClassName*>(entityName)
	return castText;
}
string generateDynamicCastOfNewEntity(string entityClassName, string castClassName, int progLang)
{
	string castText = progLangDynamicCastStart[progLang] + castClassName + progLangDynamicCastEnd[progLang] + progLangOpenParameterSpace[progLang] + progLangNewObject[progLang] + entityClassName + progLangCloseParameterSpace[progLang];	//dynamic_cast<castClassName*>(new entityClassName)
	return castText;
}
string generateReinterpretCastOfVector(string vectorName, string castClassName, int progLang)
{
	string castText = progLangReinterpretCastStart[progLang] + generateCodeEntityListDefinitionTypeTextPointer(castClassName, progLang) + progLangReinterpretCastEnd[progLang] + progLangOpenParameterSpace[progLang] + progLangAddress[progLang] + vectorName + progLangCloseParameterSpace[progLang];	//reinterpret_cast<vector<castClassName*>* >(&vectorName)
	return castText;
}
string generateReinterpretCastOfMap(string vectorName, string castClassName1, string castClassName2, int progLang)
{
	string castText = progLangReinterpretCastStart[progLang] + generateCodeConditionListDefinitionTypeTextPointer(castClassName1, castClassName2, progLang) + progLangReinterpretCastEnd[progLang] + progLangOpenParameterSpace[progLang] + progLangAddress[progLang] + vectorName + progLangCloseParameterSpace[progLang];	//reinterpret_cast<unordered_map<castClassName1*, castClassName2*>* >(&vectorName)
	return castText;
}


//this code is not currently used;
string generateCodeEntityStringMapListDefinitionText(string entityClassName, string genericListNameStart, string genericListAppendName, int progLang)
{
	string codeEntityStringMapListDefinitionText = generateCodeEntityStringMapListDefinitionTypeText(entityClassName, progLang) + generateEntityStringMapListName(genericListNameStart, genericListAppendName);	//unordered_map<string, entityClassName*> genericListNameStart+genericListAppendName;
	return codeEntityStringMapListDefinitionText;
}
string generateCodeEntityStringMapListDefinitionTypeText(string entityClassName, int progLang)
{
	string codeEntityStringMapListDefinitionTypeText = progLangClassList2DTypeStart[progLang] + progLangClassList2DTypeConditionTypeVar[progLang] + progLangClassList2DTypeMiddle[progLang] + entityClassName + progLangPointer[progLang] + progLangClassListTypeEnd[progLang];	//unordered_map<string, entityClassName*>
	return codeEntityStringMapListDefinitionTypeText;
}
string generateEntityStringMapListName(string genericListNameStart, string genericListAppendName)
{
	string codeEntityStringPairPairText = genericListNameStart + genericListAppendName;	//genericListNameStart+genericListAppendName
	return codeEntityStringPairPairText;
}
string generateEntityStringPairText(string entity1Name, string entity2ClassName, string entity2Name, int progLang)
{
	string codeEntityStringPairPairTypeText = progLangClassPairTypeStart[progLang] + progLangClassList2DTypeConditionTypeVar[progLang] + progLangClassList2DTypeMiddle[progLang] + entity2ClassName + progLangPointer[progLang] + progLangClassPairTypeEnd[progLang] + progLangClassMemberFunctionParametersOpen[progLang] + progLangStringOpenClose[progLang] + entity1Name + progLangStringOpenClose[progLang] + progLangClassMemberFunctionParametersNext[progLang] + entity2Name + progLangClassMemberFunctionParametersClose[progLang];	//pair<string, entity2className*>(entity1name, entity2name)
	return codeEntityStringPairPairTypeText;
}

string generateNewObject(string objectName, int progLang)
{
	string newObjectText = progLangOpenParameterSpace[progLang] + progLangNewObject[progLang] + generateClassName(objectName) + progLangCloseParameterSpace[progLang];	//(new objectNameClass)
	return newObjectText;
}





#ifdef NLC_USE_LIBRARY

string generateCodeAllPropertyListAddText(string propertyClassName, int progLang)
{
	string propertyListName = generatePropertyListName(propertyClassName);
	string propertyClassNameRaw = removeClassTextFromClassDefinitionName(propertyClassName);
	string propertyListKeyName = string(STRING_INVERTEDCOMMAS) + propertyClassNameRaw + string(STRING_INVERTEDCOMMAS);
	string codeAllPropertyListAddText = generateCodeAllVectorListAddText(generateAllPropertyListName(), propertyListName, propertyListKeyName, progLang);	//propertyListAll.insert(pair<string, NLCgenericEntityClass*>("propertyListKeyName", reinterpret_cast<vector<NLCgenericEntityClass*>* >(&propertyListName)));
	return codeAllPropertyListAddText;
}
string generateCodeAllPropertyListDefinitionText(int progLang)
{
	string codePropertyListDefinitionText = generateCodeAllVectorListDefinitionTypeText(progLang) + generateAllPropertyListName() + progLangEndLine[progLang];
	return codePropertyListDefinitionText;
}
string generateAllPropertyListName()
{
	return NLC_USE_LIBRARY_ALL_PROPERTY_LIST_NAME;
}

string generateCodeAllVectorListAddText(string allListName, string vectorListName, string vectorListKeyName, int progLang)
{
	string NLCgenericClassName = generateClassName(NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE);
	string codeAllVectorListAddText = allListName + progLangObjectReferenceDelimiter2[progLang] + progLangAddAllList[progLang] + progLangOpenParameterSpace[progLang] + generateCodePairText(NLC_USE_LIBRARY_ALL_LISTS_KEY_TYPE, generateCodeEntityListDefinitionTypeTextPointer(NLCgenericClassName, progLang), vectorListKeyName, generateReinterpretCastOfVector(vectorListName, NLCgenericClassName, progLang), progLang) + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//vectorListAll.insert(pair<string, vector<NLCgenericEntityClass*>*>("vectorListKeyName", reinterpret_cast<vector<NLCgenericEntityClass*>* >(&vectorListName)));
	return codeAllVectorListAddText;
}
string generateCodeAllVectorListDefinitionTypeText(int progLang)
{
	string codeEntityStringMapListDefinitionTypeText = generateCodeEntityMapListDefinitionTypeText(NLC_USE_LIBRARY_ALL_LISTS_KEY_TYPE, generateClassName(NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE), progLang);	//unordered_map<string, vector<NLCgenericEntityClass*>* >
	return codeEntityStringMapListDefinitionTypeText;
}
string generateCodeEntityMapListDefinitionTypeText(string pairItem1className, string entityClassName, int progLang)
{
	string codeEntityStringMapListDefinitionTypeText = progLangClassList2DTypeStart[progLang] + pairItem1className + progLangClassList2DTypeMiddle[progLang] + generateCodeEntityListDefinitionTypeTextPointer(entityClassName, progLang) + progLangClassListTypeEnd[progLang];	//unordered_map<x, vector<x*>* >
	return codeEntityStringMapListDefinitionTypeText;
}
string generateCodePairText(string pairItem1className, string pairItem2className, string pairItem1instanceName, string pairItem2instanceName, int progLang)
{
	string codeConditionPairTypeText = progLangClassPairTypeStart[progLang] + pairItem1className + progLangClassList2DTypeMiddle[progLang] + pairItem2className + progLangClassPairTypeEnd[progLang] + progLangClassMemberFunctionParametersOpen[progLang] + pairItem1instanceName + progLangClassMemberFunctionParametersNext[progLang] + pairItem2instanceName + progLangClassMemberFunctionParametersClose[progLang];	//pair<pairItem1className, pairItem2className*>(pairItem1, pairItem2)	
	return codeConditionPairTypeText;
}

string generateCodeAllConditionListAddText(string conditionClassName, string conditionObjectClassName, int progLang)
{
	string conditionListName = generateConditionListName(conditionClassName, conditionObjectClassName);
	string conditionName = removeClassTextFromClassDefinitionName(conditionClassName);
	string conditionObjectName = removeClassTextFromClassDefinitionName(conditionObjectClassName);
	string conditionListKeyName1 = string(STRING_INVERTEDCOMMAS) + conditionName + string(STRING_INVERTEDCOMMAS);
	string conditionListKeyName2 = string(STRING_INVERTEDCOMMAS) + conditionObjectName + string(STRING_INVERTEDCOMMAS);
	string codeAllConditionListAddText = generateCodeAllMapListAddText(generateAllConditionListName(), conditionListName, conditionListKeyName1, conditionListKeyName2, progLang);	//conditionListAll.insert(pair<pair<string, string>, unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>* >(<pair, pair>("conditionListKeyName1", "conditionListKeyName2"), reinterpret_cast<unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>* >(&conditionListName)));
	return codeAllConditionListAddText;
}
string generateCodeAllConditionListDefinitionText(int progLang)
{
	string codeConditionListDefinitionText = generateCodeAllConditionListDefinitionTypeText(progLang) + generateAllConditionListName() + progLangEndLine[progLang];
	return codeConditionListDefinitionText;
}
string generateAllConditionListName()
{
	return NLC_USE_LIBRARY_ALL_CONDITION_LIST_NAME;
}

string generateCodeAllMapListAddText(string allListName, string mapListName, string mapListKeyName1, string mapListKeyName2, int progLang)
{
	string NLCgenericClassName = generateClassName(NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE);
	string codeAllMapListAddText = allListName + progLangObjectReferenceDelimiter2[progLang] + progLangAddAllList[progLang] + progLangOpenParameterSpace[progLang] + generateCodePairPairText(NLC_USE_LIBRARY_ALL_LISTS_KEY_TYPE, NLC_USE_LIBRARY_ALL_LISTS_KEY_TYPE, generateCodeConditionListDefinitionTypeTextPointer(NLCgenericClassName, NLCgenericClassName, progLang), mapListKeyName1, mapListKeyName2, generateReinterpretCastOfMap(mapListName, NLCgenericClassName, NLCgenericClassName, progLang), progLang) + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//conditionListAll.insert(pair<pair<string, string>, unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>* >(<pair, pair>("mapListKeyName1", "mapListKeyName2"), reinterpret_cast<unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>* >(mapListName)));
	return codeAllMapListAddText;
}
string generateCodeAllConditionListDefinitionTypeText(int progLang)
{
	string NLCgenericClassName = generateClassName(NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE);
	string codeEntityStringMapListDefinitionTypeText = generateCodeEntityPairMapListDefinitionTypeText(NLC_USE_LIBRARY_ALL_LISTS_KEY_TYPE, NLC_USE_LIBRARY_ALL_LISTS_KEY_TYPE, generateCodeConditionListDefinitionTypeText(NLCgenericClassName, NLCgenericClassName, progLang), progLang);	//unordered_map<pair<string, string>, unordered_map<x*, x*>*>
	return codeEntityStringMapListDefinitionTypeText;
}
string generateCodeEntityPairMapListDefinitionTypeText(string pairItem1className, string pairItem2className, string entityClassName, int progLang)
{
	string codeEntityStringMapListDefinitionTypeText = progLangClassList2DTypeStart[progLang] + generateCodePairTypeText(pairItem1className, pairItem2className, progLang) + progLangClassList2DTypeMiddle[progLang] + entityClassName + progLangPointer[progLang] + progLangClassListTypeEnd[progLang];	//unordered_map<pair<x, x>, x*>
	return codeEntityStringMapListDefinitionTypeText;
}
string generateCodePairTypeText(string pairItem1className, string pairItem2className, int progLang)
{
	string codeConditionPairTypeText = progLangClassPairTypeStart[progLang] + pairItem1className + progLangClassList2DTypeMiddle[progLang] + pairItem2className + progLangClassPairTypeEnd[progLang];	//pair<pairItem2className, pairItem2className>
	return codeConditionPairTypeText;
}
string generateCodePairPairText(string pairItem1AclassName, string pairItem1BclassName, string pairItem2className, string pairItem1AinstanceName, string pairItem1BinstanceName, string pairItem2instanceName, int progLang)
{
	string codeConditionPairTypeText = progLangClassPairTypeStart[progLang] + generateCodePairTypeText(pairItem1AclassName, pairItem1BclassName, progLang) + progLangClassList2DTypeMiddle[progLang] + pairItem2className + progLangClassPairTypeEnd[progLang] + progLangClassMemberFunctionParametersOpen[progLang] + generateCodePairText(pairItem1AclassName, pairItem1BclassName, pairItem1AinstanceName, pairItem1BinstanceName, progLang) + progLangClassMemberFunctionParametersNext[progLang] + pairItem2instanceName + progLangClassMemberFunctionParametersClose[progLang];	//pair<pair<pairItem1AclassName, pairItem1BclassName>, pairItem2className*>(pair<pairItem1AclassName, pairItem1BclassName*>(pairItem1A, pairItem1B), pairItem2)	
	return codeConditionPairTypeText;
}


string generateCodeAllActionListAddText(string actionClassName, int progLang)
{
	string actionListName = generateActionListName(actionClassName);
	string actionClassNameRaw = removeClassTextFromClassDefinitionName(actionClassName);
	string actionListKeyName = string(STRING_INVERTEDCOMMAS) + actionClassNameRaw + string(STRING_INVERTEDCOMMAS);
	string codeAllActionListAddText = generateCodeAllVectorListAddText(generateAllActionListName(), actionListName, actionListKeyName, progLang);	//actionListAll.insert(pair<string, vector<NLCgenericEntityClass*>* >("actionName", reinterpret_cast<vector<NLCgenericEntityClass*>* >(&actionListName)));
	return codeAllActionListAddText;
}
string generateCodeAllActionListDefinitionText(int progLang)
{
	string codeActionListDefinitionText = generateCodeAllVectorListDefinitionTypeText(progLang) + generateAllActionListName() + progLangEndLine[progLang];
	return codeActionListDefinitionText;
}
string generateAllActionListName()
{
	return NLC_USE_LIBRARY_ALL_ACTION_LIST_NAME;
}

string generateCodeAllActionIncomingListAddText(string actionIncomingClassName, int progLang)
{
	string actionIncomingListName = generateActionIncomingListName(actionIncomingClassName);
	string actionIncomingClassNameRaw = removeClassTextFromClassDefinitionName(actionIncomingClassName);
	string actionIncomingListKeyName = string(STRING_INVERTEDCOMMAS) + actionIncomingClassNameRaw + string(STRING_INVERTEDCOMMAS);
	string codeAllActionIncomingListAddText = generateCodeAllVectorListAddText(generateAllActionIncomingListName(), actionIncomingListName, actionIncomingListKeyName, progLang);	//actionIncomingListAll.insert(pair<string, vector<NLCgenericEntityClass*>* >("actionIncomingName", reinterpret_cast<vector<NLCgenericEntityClass*>* >(&actionIncomingListName)));
	return codeAllActionIncomingListAddText;
}
string generateCodeAllActionIncomingListDefinitionText(int progLang)
{
	string codeActionIncomingListDefinitionText = generateCodeAllVectorListDefinitionTypeText(progLang) + generateAllActionIncomingListName() + progLangEndLine[progLang];
	return codeActionIncomingListDefinitionText;
}
string generateAllActionIncomingListName()
{
	return NLC_USE_LIBRARY_ALL_ACTIONINCOMING_LIST_NAME;
}

string generateCodeAllActionSubjectListAddText(string actionSubjectClassName, int progLang)
{
	string actionSubjectListName = generateActionSubjectListName(actionSubjectClassName);
	string actionSubjectClassNameRaw = removeClassTextFromClassDefinitionName(actionSubjectClassName);
	string actionSubjectListKeyName = string(STRING_INVERTEDCOMMAS) + actionSubjectClassNameRaw + string(STRING_INVERTEDCOMMAS);
	string codeAllActionSubjectListAddText = generateCodeAllVectorListAddText(generateAllActionSubjectListName(), actionSubjectListName, actionSubjectListKeyName, progLang);	//actionSubjectListAll.insert(pair<string, vector<NLCgenericEntityClass*>* >("actionSubjectName", reinterpret_cast<vector<NLCgenericEntityClass*>* >(&actionSubjectListName)));
	return codeAllActionSubjectListAddText;
}
string generateCodeAllActionSubjectListDefinitionText(int progLang)
{
	string codeActionSubjectListDefinitionText = generateCodeAllVectorListDefinitionTypeText(progLang) + generateAllActionSubjectListName() + progLangEndLine[progLang];
	return codeActionSubjectListDefinitionText;
}
string generateAllActionSubjectListName()
{
	return NLC_USE_LIBRARY_ALL_ACTIONSUBJECT_LIST_NAME;
}

string generateCodeAllActionObjectListAddText(string actionObjectClassName, int progLang)
{
	string actionObjectListName = generateActionObjectListName(actionObjectClassName);
	string actionObjectClassNameRaw = removeClassTextFromClassDefinitionName(actionObjectClassName);
	string actionObjectListKeyName = string(STRING_INVERTEDCOMMAS) + actionObjectClassNameRaw + string(STRING_INVERTEDCOMMAS);
	string codeAllActionObjectListAddText = generateCodeAllVectorListAddText(generateAllActionObjectListName(), actionObjectListName, actionObjectListKeyName, progLang);	//actionObjectListAll.insert(pair<string, vector<NLCgenericEntityClass*>* >("actionObjectName", reinterpret_cast<vector<NLCgenericEntityClass*>* >(&actionObjectListName)));
	return codeAllActionObjectListAddText;
}
string generateCodeAllActionObjectListDefinitionText(int progLang)
{
	string codeActionObjectListDefinitionText = generateCodeAllVectorListDefinitionTypeText(progLang) + generateAllActionObjectListName() + progLangEndLine[progLang];
	return codeActionObjectListDefinitionText;
}
string generateAllActionObjectListName()
{
	return NLC_USE_LIBRARY_ALL_ACTIONOBJECT_LIST_NAME;
}

#endif


string generateTempEntityDeclarationSetToNull(NLCitem* param1, int progLang)
{
	string tempEntityDeclarationText = generateTempEntityDeclaration(param1, progLang) + progLangEquals[progLang] + progLangNullPointer[progLang] + progLangEndLine[progLang];	//param1Class* param1 = NULL;
	return tempEntityDeclarationText;
}
string generateCodeSetTempEntity(NLCitem* param1, NLCitem* param2, int progLang)
{
	string tempVariableName = generateTempEntityName(param1) + progLangEquals[progLang] + generateTempEntityName(param2) + progLangEndLine[progLang];	//param1 = param2;
	return tempVariableName;	
}
string generateTempEntityDeclarationSetToEntity(NLCitem* param1, NLCitem* param2, int progLang)
{
	string tempEntityDeclarationText = generateTempEntityDeclaration(param1, progLang) + progLangEquals[progLang] + generateTempEntityName(param2) + progLangEndLine[progLang];	//param1Class* param1 = param2;
	return tempEntityDeclarationText;
}

string generateDeclareBoolTextAndSetFalse(string variableName, int progLang)
{
	string declareText = progLangBoolean[progLang] + variableName + progLangEquals[progLang] + progLangFalse[progLang] + progLangEndLine[progLang];	//bool variable = false;
	return declareText;
}
string generateSetBoolTextTrue(string variableName, int progLang)
{
	string setText = variableName + progLangEquals[progLang] + progLangTrue[progLang] + progLangEndLine[progLang];	//variable = true;
	return setText;
}
string generateReturnText(string variableName, int progLang)
{
	string returnText = progLangReturn[progLang] + variableName + progLangEndLine[progLang];	//return variable;
	return returnText;
}

