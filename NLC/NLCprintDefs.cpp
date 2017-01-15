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
 * Project Version: 1n1a 04-January-2014
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

#ifdef USE_NLCNONOO
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
#ifdef USE_NLCNONOO
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

#ifdef USE_NLCNONOO
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

string generateCodeConditionPairTextWithContext(string conditionName, string conditionClassName, string conditionInstanceName, string conditionObjectClassName, string conditionObjectInstanceName, vector<string> * conditionContext, int progLang)
{
	#ifdef NLC_USE_STRING_INDEXED_UNORDERED_MAPS_FOR_CONDITION_LISTS
	string codeConditionPairTypeText = progLangClassPairTypeStart[progLang] + progLangClassList2DTypeConditionTypeVar[progLang] + progLangClassList2DTypeMiddle[progLang] + conditionObjectClassName + progLangPointer[progLang] + progLangClassPairTypeEnd[progLang] + progLangClassMemberFunctionParametersOpen[progLang] + progLangStringOpenClose[progLang] + generateInstanceNameWithContext(conditionInstanceName, conditionContext, progLang) + progLangStringOpenClose[progLang] + progLangClassMemberFunctionParametersNext[progLang] + generateInstanceNameWithContext(conditionObjectInstanceName, conditionContext, progLang) + progLangClassMemberFunctionParametersClose[progLang];
	#else
	string codeConditionPairTypeText = progLangClassPairTypeStart[progLang] + conditionClassName + progLangPointer[progLang] + progLangClassList2DTypeMiddle[progLang] + conditionObjectClassName + progLangPointer[progLang] + progLangClassPairTypeEnd[progLang] + progLangClassMemberFunctionParametersOpen[progLang] + generateInstanceNameWithContext(conditionInstanceName, conditionContext, progLang) + progLangClassMemberFunctionParametersNext[progLang] + generateInstanceNameWithContext(conditionObjectInstanceName, conditionContext, progLang) + progLangClassMemberFunctionParametersClose[progLang];	
	#endif
	return codeConditionPairTypeText;
}
#endif

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
	#ifdef USE_NLCNONOO
	string codeEntityListDefinitionText = generateCodeEntityListDefinitionTypeText(progLang) + generateEntityListName(entityParam);
	#else
	string codeEntityListDefinitionText = generateCodeEntityListDefinitionTypeText(entityParam->className, progLang) + generateEntityListName(entityParam);
	#endif
	return codeEntityListDefinitionText;
}

#ifdef USE_NLCNONOO
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
	string codeEntityListDefinitionTypeText = progLangClassListTypeStart[progLang] + entityClassName + progLangPointer[progLang] + progLangClassListTypeEnd[progLang];	
	return codeEntityListDefinitionTypeText;
}
#ifdef NLC_GENERATE_TYPE_LISTS
string generateCodeEntityListDefinitionTypeText2(string propertyClassName, int progLang)
{
	string codePropertyListDefinitionText = progLangClassListTypeStart[progLang] + progLangClassListTypeStart[progLang] + propertyClassName + progLangPointer[progLang] + progLangClassListTypeEnd[progLang] + progLangClassListTypeEnd[progLang];
	return codePropertyListDefinitionText;
}
#endif
#endif

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
#ifdef USE_NLCNONOO
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
	string codeConditionListDefinitionTypeText = progLangClassList2DTypeStart[progLang] + progLangClassList2DTypeConditionTypeVar[progLang] + progLangClassList2DTypeMiddle[progLang] + conditionObjectClassName + progLangPointer[progLang] + progLangClassListTypeEnd[progLang];
	#else
	string codeConditionListDefinitionTypeText = progLangClassList2DTypeStart[progLang] + conditionClassName + progLangPointer[progLang] + progLangClassList2DTypeMiddle[progLang] + conditionObjectClassName + progLangPointer[progLang] + progLangClassListTypeEnd[progLang];
	#endif
	return codeConditionListDefinitionTypeText;
}
#endif

//NB USE_NLCNONOO requires !NLC_USE_STRING_INDEXED_UNORDERED_MAPS_FOR_CONDITION_LISTS
void generateCodeAddConditionAndObjectEntityToList(NLCitem * param1, NLCitem * param2, NLCitem * param3, int progLang, string * code, int level)
{
	string contextParam1 = generateStringFromContextVector(&(param1->context), progLang);
	#ifdef USE_NLCNONOO
	string codeBlockText = contextParam1 + param1->instanceName + progLangObjectReferenceDelimiter[progLang] + generateGIAconditionListName() + progLangObjectReferenceDelimiter2[progLang] + progLangAddProperty[progLang] + progLangOpenParameterSpace[progLang] + param2->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//context1->param1->param2ConditionList.push_back(param2);
	printLine(codeBlockText, level, code);
	codeBlockText = param2->instanceName + progLangObjectReferenceDelimiter[progLang] + generateGIAconditionObjectListName() + progLangObjectReferenceDelimiter2[progLang] + progLangAddProperty[progLang] + progLangOpenParameterSpace[progLang] + param3->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//param2->param2ConditionObjectList.push_back(param3);
	printLine(codeBlockText, level, code);
	#ifdef USE_NLCNONOO_CREATE_REVERSE_LISTS
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

void generateCodeAddPropertyEntityToList(NLCitem * param1, NLCitem * param2, int progLang, string * code, int level)
{
	string contextParam1 = generateStringFromContextVector(&(param1->context), progLang);
	#ifdef USE_NLCNONOO
	string codeBlockText = contextParam1 + param1->instanceName + progLangObjectReferenceDelimiter[progLang] + generatePropertyListName() + progLangObjectReferenceDelimiter2[progLang] + progLangAddProperty[progLang] + progLangOpenParameterSpace[progLang] + param2->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//context1->param1->param2PropertyList.push_back(param2);
	printLine(codeBlockText, level, code);
	codeBlockText = param2->instanceName + progLangObjectReferenceDelimiter[progLang] + generatePropertyReverseListName() + progLangObjectReferenceDelimiter2[progLang] + progLangAddProperty[progLang] + progLangOpenParameterSpace[progLang] + contextParam1 + param1->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//param2->param2IncomingPropertyList.push_back(context1->param1);
	printLine(codeBlockText, level, code);
	#else
	string codeBlockText = contextParam1 + param1->instanceName + progLangObjectReferenceDelimiter[progLang] + generatePropertyListName(param2->className) + progLangObjectReferenceDelimiter2[progLang] + progLangAddProperty[progLang] + progLangOpenParameterSpace[progLang] + param2->instanceName + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];		//context1->param1->param2PropertyList.push_back(param2);	
	printLine(codeBlockText, level, code);
	#endif
}


			
#ifdef USE_NLCNONOO
string generateGIAentityName()
{
	string GIAentityName = GIA_ENTITYNODECLASS_ENTITYNAME_NAME;
	return GIAentityName;
}

string generateCodeEntityNameTestText(NLCitem * param, int progLang)
{
	string entityNameTestText = progLangOpenParameterSpace[progLang] + generateTempEntityName(param) + progLangObjectReferenceDelimiter[progLang] + generateGIAentityName() + progLangStringEqualsTest[progLang] + progLangStringOpenClose[progLang] + param->name + progLangStringOpenClose[progLang] + progLangCloseParameterSpace[progLang];
	return entityNameTestText;
}
#endif

string generateCodeNewTempEntity(NLCitem * param, int progLang)
{
	#ifdef USE_NLCNONOO
	string newTempEntityText = generateTempEntityDeclaration(param, progLang) + progLangEquals[progLang] + progLangNewObject[progLang] + generateTempEntityClassName(param) + progLangOpenParameterSpace[progLang] + progLangStringOpenClose[progLang] + param->name + progLangStringOpenClose[progLang] + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	
	#else
	string newTempEntityText = generateTempEntityDeclaration(param, progLang) + progLangEquals[progLang] + progLangNewObject[progLang] + generateTempEntityClassName(param) + progLangOpenParameterSpace[progLang] + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];
	#endif
	return newTempEntityText;
}

string generateTempEntityDeclaration(NLCitem * param, int progLang)
{
	string tempVariableName = generateTempEntityDeclaration(generateTempEntityClassName(param), generateTempEntityName(param), progLang);
	return tempVariableName;
}

string generateTempEntityName(NLCitem * param)
{
	return param->instanceName;
}

string generateTempEntityClassName(NLCitem * param)
{
	#ifdef USE_NLCNONOO
	return NLCNONOO_GENERIC_ENTITY_NODE_NAME;
	#else
	return param->className;
	#endif
}

string generateTempEntityDeclaration(string className, string instanceName, int progLang)
{
	#ifdef USE_NLCNONOO
	string tempVariableName = string(NLCNONOO_GENERIC_ENTITY_NODE_NAME) + progLangPointer[progLang] + STRING_SPACE + instanceName;
	#else
	string tempVariableName = className + progLangPointer[progLang] + STRING_SPACE + instanceName;	
	#endif
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

string generateNewObject(string objectName, int progLang)
{
	string newObjectText = progLangOpenParameterSpace[progLang] + progLangNewObject[progLang] + generateClassName(objectName) + progLangCloseParameterSpace[progLang];	//(new objectNameClass)
	return newObjectText;
}

