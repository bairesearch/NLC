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
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2016 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 1t3b 21-September-2016
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/


#include "NLCprintDefs.h"

static int progLangGlobal;
int getProgLang()
{
	return progLangGlobal;
}
void setProgLang(int progLang)
{
	progLangGlobal = progLang;
}

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

string generatePropertyListName(string propertyClassName)
{
	#ifdef NLC_NONOO
	return generatePropertyListName();
	#else
	string propertyListName = propertyClassName + NLC_ITEM_TYPE_PROPERTYLIST_VAR_APPENDITION;
	return propertyListName;
	#endif
}
#ifdef NLC_NONOO
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
#endif

#ifdef NLC_RECORD_ACTION_HISTORY
string generateActionListName(string actionClassName)
{
	#ifdef NLC_NONOO
	return generateActionListName();
	#else
	string actionListName = generateGenericListName(actionClassName, NLC_ITEM_TYPE_ACTION_VAR_APPENDITION);
	return actionListName;
	#endif
}
string generateActionIncomingListName(string actionClassName)
{
	#ifdef NLC_NONOO
	return generateActionIncomingListName();
	#else
	string actionIncomingListName = generateGenericListName(actionClassName, NLC_ITEM_TYPE_ACTIONINCOMING_VAR_APPENDITION);
	return actionIncomingListName;
	#endif
}
string generateActionSubjectListName(string actionSubjectClassName)
{
	#ifdef NLC_NONOO
	return generateActionSubjectListName();
	#else
	string actionSubjectListName = generateGenericListName(actionSubjectClassName, NLC_ITEM_TYPE_ACTIONSUBJECT_VAR_APPENDITION);
	return actionSubjectListName;
	#endif
}
string generateActionObjectListName(string actionObjectClassName)
{
	#ifdef NLC_NONOO
	return generateActionObjectListName();
	#else
	string actionObjectListName = generateGenericListName(actionObjectClassName, NLC_ITEM_TYPE_ACTIONOBJECT_VAR_APPENDITION);
	return actionObjectListName;
	#endif
}

#ifdef NLC_NONOO
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
#endif
#endif

string generateLocalListName(string className, string instanceName)
{
	NLCitem item;
	item.className = className;
	item.instanceName = instanceName;
	return generateEntityListName(&item);
}
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


string generateCategoryListName(NLCitem* param, string genericListAppendName)
{
	string propertyListName = generateGenericListName(param->genericObjectName, genericListAppendName);
	return propertyListName;
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
	#ifdef NLC_NONOO
	return generateConditionListName();
	#else
	#ifdef NLC_CONDITION_LISTS_STORE_CONDITION_AS_STRING
	string conditionListName = conditionObjectClassName + NLC_ITEM_TYPE_CONDITIONLIST_VAR_APPENDITION;
	#else
	string conditionListName = conditionClassName + conditionObjectClassName + NLC_ITEM_TYPE_CONDITIONLIST_VAR_APPENDITION;
	#endif
	return conditionListName;
	#endif
}

#ifdef NLC_NONOO
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

string generateConditionPairDefinitionName(string conditionClassName, string conditionObjectClassName)
{
	#ifdef NLC_CONDITION_LISTS_STORE_CONDITION_AS_STRING
	string conditionListName = conditionObjectClassName + NLC_ITEM_TYPE_CONDITIONPAIR_VAR_APPENDITION;
	#else
	string conditionListName = conditionClassName + conditionObjectClassName + NLC_ITEM_TYPE_CONDITIONPAIR_VAR_APPENDITION;
	#endif
	return conditionListName;
}

#ifdef NLC_CONDITION_LISTS_VECTOR
string generateCodeConditionNewPairText(string conditionName, string conditionClassName, string conditionInstanceName, string conditionObjectClassName, string conditionObjectInstanceName, int progLang)
{
	string codeConditionNewPairText = progLangNewObject[progLang] + generateCodeConditionPairText(conditionName, conditionClassName, conditionInstanceName, conditionObjectClassName, conditionObjectInstanceName, progLang);
	return codeConditionNewPairText;
}
#endif

string generateCodeConditionPairText(string conditionName, string conditionClassName, string conditionInstanceName, string conditionObjectClassName, string conditionObjectInstanceName, int progLang)
{
	#ifdef NLC_CONDITION_LISTS_STORE_CONDITION_AS_STRING
	string codeConditionPairTypeText = progLangClassPairTypeStart[progLang] + progLangClassList2DTypeConditionTypeStringVar[progLang] + progLangClassList2DMapTypeMiddle[progLang] + generatePointerTypeText(conditionObjectClassName, progLang) + progLangClassPairTypeEnd[progLang] + progLangClassMemberFunctionParametersOpen[progLang] + progLangStringOpenClose[progLang] + conditionName + progLangStringOpenClose[progLang] + progLangClassMemberFunctionParametersNext[progLang] + conditionObjectInstanceName + progLangClassMemberFunctionParametersClose[progLang];
	#else
	string codeConditionPairTypeText = progLangClassPairTypeStart[progLang] + conditionClassName + progLangPointer[progLang] + progLangClassList2DMapTypeMiddle[progLang] + generatePointerTypeText(conditionObjectClassName, progLang) + progLangClassPairTypeEnd[progLang] + progLangClassMemberFunctionParametersOpen[progLang] + conditionInstanceName + progLangClassMemberFunctionParametersNext[progLang] + conditionObjectInstanceName + progLangClassMemberFunctionParametersClose[progLang];
	#endif
	return codeConditionPairTypeText;
}

string generateCodeConditionPairTextWithContext(string conditionName, string conditionClassName, string conditionInstanceName, string conditionObjectClassName, string conditionObjectInstanceName, vector<string>* conditionContext, int progLang)
{
	#ifdef NLC_CONDITION_LISTS_STORE_CONDITION_AS_STRING
	string codeConditionPairTypeText = progLangClassPairTypeStart[progLang] + progLangClassList2DTypeConditionTypeStringVar[progLang] + progLangClassList2DMapTypeMiddle[progLang] + generatePointerTypeText(conditionObjectClassName, progLang) + progLangClassPairTypeEnd[progLang] + progLangClassMemberFunctionParametersOpen[progLang] + progLangStringOpenClose[progLang] + generateInstanceNameWithContext(conditionInstanceName, conditionContext, progLang) + progLangStringOpenClose[progLang] + progLangClassMemberFunctionParametersNext[progLang] + generateInstanceNameWithContext(conditionObjectInstanceName, conditionContext, progLang) + progLangClassMemberFunctionParametersClose[progLang];
	#else
	string codeConditionPairTypeText = progLangClassPairTypeStart[progLang] + generatePointerTypeText(conditionClassName, progLang) + progLangClassList2DMapTypeMiddle[progLang] + generatePointerTypeText(conditionObjectClassName, progLang) + progLangClassPairTypeEnd[progLang] + progLangClassMemberFunctionParametersOpen[progLang] + generateInstanceNameWithContext(conditionInstanceName, conditionContext, progLang) + progLangClassMemberFunctionParametersNext[progLang] + generateInstanceNameWithContext(conditionObjectInstanceName, conditionContext, progLang) + progLangClassMemberFunctionParametersClose[progLang];
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


string generateCodePropertyListDefinitionText(NLCitem* entityParam, int progLang)
{
	return generateCodePropertyListDefinitionText(entityParam->className, progLang);
}
string generateCodePropertyListDefinitionText(string propertyClassName, int progLang)
{
	string codePropertyListDefinitionText = generateCodeEntityListDefinitionTypeText(propertyClassName, progLang) + generatePropertyListName(propertyClassName);
	return codePropertyListDefinitionText;
}
string generateCodeEntityListDefinitionText(NLCitem* entityParam, int progLang)
{
	#ifdef NLC_NONOO
	string codeEntityListDefinitionText = generateCodeEntityListDefinitionTypeTextNonOO(progLang) + generateEntityListName(entityParam);
	#else
	string codeEntityListDefinitionText = generateCodeEntityListDefinitionTypeText(entityParam->className, progLang) + generateEntityListName(entityParam);
	#endif
	return codeEntityListDefinitionText;
}
string generateCodeEntityListDefinitionText(string className, string instanceName, int progLang)
{
	#ifdef NLC_NONOO
	string codeEntityListDefinitionText = generateCodeEntityListDefinitionTypeTextNonOO(progLang) + instanceName;
	#else
	string codeEntityListDefinitionText = generateCodeEntityListDefinitionTypeText(className, progLang) + instanceName;
	#endif
	return codeEntityListDefinitionText;
}
string generateCodeEntityListDefinitionTypeText(string entityClassName, int progLang)
{
	return generateCodeEntityListDefinitionTypeTextCompact(entityClassName, progLang) + CHAR_SPACE;
}
string generateCodeEntityListDefinitionTypeTextCompact(string entityClassName, int progLang)
{
	#ifdef NLC_NONOO
	return generateCodeEntityListDefinitionTypeTextNonOO(progLang);
	#else
	return generateCodeVectorListDefinitionTypeText(entityClassName, progLang);
	#endif
}
#ifdef NLC_NONOO
string generateCodeEntityListDefinitionTypeTextNonOO(int progLang)
{
	string codeEntityListDefinitionTypeText = progLangClassListTypeStart[progLang] + generatePointerTypeText(NLCNONOO_GENERIC_ENTITY_NODE_NAME, progLang) + progLangClassListTypeEnd[progLang];
	return codeEntityListDefinitionTypeText;
}
#else
string generateCodeEntityListDefinitionTypeTextPointer(string entityClassName, int progLang)
{
	string codePropertyListDefinitionTextPointer = generatePointerTypeText(generateCodeEntityListDefinitionTypeTextCompact(entityClassName, progLang), progLang);		//vector<entityClassName*>*
	return codePropertyListDefinitionTextPointer;
}
#ifdef NLC_GENERATE_TYPE_LISTS
string generateCodeEntityListDefinitionTypeText2(string propertyClassName, int progLang)
{
	string codePropertyListDefinitionText = progLangClassListTypeStart[progLang] + progLangClassListTypeStart[progLang] + generatePointerTypeText(propertyClassName, progLang) + progLangClassListTypeEnd[progLang] + progLangClassListTypeEnd[progLang];
	return codePropertyListDefinitionText;
}
#endif
#endif
string generateCodeVectorListDefinitionTypeText(string entityClassName, int progLang)
{
	string codeVectorListDefinitionText = progLangClassListTypeStart[progLang] + generatePointerTypeText(entityClassName, progLang) + progLangClassListTypeEnd[progLang];	//vector<entityClassName*>
	return codeVectorListDefinitionText;
}
string generateCodeVectorListDefinitionTypeTextPointer(string entityClassName, int progLang)
{
	string codeVectorListDefinitionTextPointer = generatePointerTypeText(generateCodeVectorListDefinitionTypeText(entityClassName, progLang), progLang);		//vector<entityClassName*>*
	return codeVectorListDefinitionTextPointer;
}
string generateCodeVectorListDefinitionTypeText2(string vectorClassName, int progLang)
{
	string codePropertyListDefinitionText = progLangClassListTypeStart[progLang] + progLangClassListTypeStart[progLang] + generatePointerTypeText(vectorClassName, progLang) + progLangClassListTypeEnd[progLang] + progLangClassListTypeEnd[progLang];
	return codePropertyListDefinitionText;
}

string generateCodeEntityListDefinitionReferenceText(NLCitem* entityParam, int progLang)
{
	string codeEntityListDefinitionReferenceText = generateCodeEntityListDefinitionTypeTextReference(entityParam->className, progLang) + generateEntityListName(entityParam);
	return codeEntityListDefinitionReferenceText;
}

string generateCodeEntityListDefinitionTypeTextReferenceCompact(string entityClassName, int progLang)
{
	#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_PASS_LISTS_BY_REFERENCE
	string codeEntityListDefinitionReferenceTypeText = generateCodeEntityListDefinitionTypeTextCompact(entityClassName, progLang) + progLangReference[progLang];
	#else
	string codeEntityListDefinitionReferenceTypeText = generateCodeEntityListDefinitionTypeTextCompact(entityClassName, progLang);
	#endif
	return codeEntityListDefinitionReferenceTypeText;
}

string generateCodeEntityListDefinitionTypeTextReference(string entityClassName, int progLang)
{
	string codeEntityListDefinitionReferenceTypeText = generateCodeEntityListDefinitionTypeTextReferenceCompact(entityClassName, progLang) + CHAR_SPACE;
	return codeEntityListDefinitionReferenceTypeText;
}

string generateCodeGenericListDefinitionText(NLCitem* entityParam, string genericListAppendName, int progLang)
{
	string codeGenericListDefinitionText = generateCodeEntityListDefinitionTypeText(entityParam->className, progLang) + generateGenericListName(entityParam->genericObjectName, genericListAppendName);
	return codeGenericListDefinitionText;
}



string generateCodeConditionListDefinitionText(NLCitem* conditionParam, NLCitem* conditionObjectParam, int progLang)
{
	return generateCodeConditionListDefinitionText(conditionParam->className, conditionObjectParam->className, progLang);
}
string generateCodeConditionListDefinitionText(string conditionClassName, string conditionObjectClassName, int progLang)
{
	string codeConditionListDefinitionText = generateCodeConditionListDefinitionTypeText(conditionClassName, conditionObjectClassName, progLang) + generateConditionListName(conditionClassName, conditionObjectClassName);
	return codeConditionListDefinitionText;
}
string generateCodeConditionListDefinitionTypeText(string conditionClassName, string conditionObjectClassName, int progLang)
{
	string codeConditionListDefinitionTypeText = generateCodeConditionListDefinitionTypeTextCompact(conditionClassName, conditionObjectClassName, progLang) + CHAR_SPACE;
	return codeConditionListDefinitionTypeText;
}
string generateCodeConditionListDefinitionTypeTextCompact(string conditionClassName, string conditionObjectClassName, int progLang)
{
	#ifdef NLC_NONOO
	return generateCodeConditionListDefinitionTypeTextNonOO(progLang);
	#else
	#ifdef NLC_CONDITION_LISTS_VECTOR
	return generateCodeVectorPairListDefinitionTypeText(conditionClassName, conditionObjectClassName, progLang);	//vector<pair<conditionClassName*, conditionObjectClassName*>*>
	#else
	return generateCodeMapsListDefinitionTypeText(conditionClassName, conditionObjectClassName, progLang);	//unordered_map<conditionClassName*, conditionObjectClassName*>
	#endif
	#endif
}
#ifdef NLC_CONDITION_LISTS_VECTOR
string generateCodeVectorPairListDefinitionTypeText(string conditionClassName, string conditionObjectClassName, int progLang)
{
	#ifdef NLC_CONDITION_LISTS_STORE_CONDITION_AS_STRING
	string codeConditionListDefinitionTypeText = progLangClassList2DTypeStart[progLang] + generateCodePairTypeText(progLangClassList2DTypeConditionTypeStringVar[progLang], generatePointerTypeText(conditionObjectClassName, progLang), progLang) + progLangPointer[progLang] + progLangClassListTypeEnd[progLang];	//vector<pair<string, conditionObjectClassName*>*>
	#else
	string codeConditionListDefinitionTypeText = progLangClassList2DTypeStart[progLang] + generateCodePairTypeText(generatePointerTypeText(conditionClassName, progLang), generatePointerTypeText(conditionObjectClassName, progLang), progLang) + progLangPointer[progLang] + progLangClassListTypeEnd[progLang];	//vector<pair<conditionClassName*, conditionObjectClassName*>*>
	#endif
	return codeConditionListDefinitionTypeText;
}
#else
string generateCodeMapsListDefinitionTypeText(string conditionClassName, string conditionObjectClassName, int progLang)
{
	#ifdef NLC_CONDITION_LISTS_STORE_CONDITION_AS_STRING
	string codeConditionListDefinitionTypeText = progLangClassList2DMapTypeStart[progLang] + progLangClassList2DTypeConditionTypeStringVar[progLang] + progLangClassList2DMapTypeMiddle[progLang] + generatePointerTypeText(conditionObjectClassName, progLang) + progLangClassListTypeEnd[progLang];	//unordered_map<string, conditionObjectClassName*>
	#else
	string codeConditionListDefinitionTypeText = progLangClassList2DMapTypeStart[progLang] + generatePointerTypeText(conditionClassName, progLang) + progLangClassList2DMapTypeMiddle[progLang] + generatePointerTypeText(conditionObjectClassName, progLang) + progLangClassListTypeEnd[progLang];	//unordered_map<conditionClassName*, conditionObjectClassName*>
	#endif
	return codeConditionListDefinitionTypeText;
}
#endif

#ifdef NLC_NONOO
string generateCodeConditionListDefinitionTypeTextNonOO(int progLang)
{
	string codeConditionListDefinitionTypeText = generateCodeEntityListDefinitionTypeTextNonOO(progLang);
	return codeConditionListDefinitionTypeText;
}
#else
string generateCodeConditionListDefinitionTypeTextPointer(string conditionClassName, string conditionObjectClassName, int progLang)
{
	string codeConditionListDefinitionTypeTextPointer = generateCodeConditionListDefinitionTypeTextCompact(conditionClassName, conditionObjectClassName, progLang) + progLangPointer[progLang];	//e.g. unordered_map<conditionClassName*, conditionObjectClassName*>*
	return codeConditionListDefinitionTypeTextPointer;
}
#endif






#ifdef NLC_NONOO
string generateGIAentityName()
{
	string GIAentityName = GIA_ENTITYNODECLASS_ENTITYNAME_NAME;
	return GIAentityName;
}

string generateCodeEntityNameTestText(NLCitem* param, int progLang)
{
	string entityNameTestText = progLangOpenParameterSpace[progLang] + generateEntityName(param) + progLangObjectReferenceDelimiter[progLang] + generateGIAentityName() + progLangStringEqualsTest[progLang] + progLangStringOpenClose[progLang] + param->name + progLangStringOpenClose[progLang] + progLangCloseParameterSpace[progLang];
	return entityNameTestText;
}
#endif
string generateCodeClassNameTestText(string objectName, string className, int progLang)
{
	string ifObjectNameEqualsClassNameText = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + objectName + progLangObjectReferenceDelimiter[progLang] + progLangClassNameVariableName[progLang] + progLangEqualsTest[progLang] + progLangStringOpenClose[progLang] + className + progLangStringOpenClose[progLang] + progLangCloseParameterSpace[progLang];	//if(object->name == "className")
	return ifObjectNameEqualsClassNameText;
}


string generateCodeNewEntity(NLCitem* param, int progLang)
{
	#ifdef NLC_NONOO
	string newTempEntityText = generateCodeEntityDefinitionText(param, progLang) + progLangEquals[progLang] + progLangNewObject[progLang] + generateEntityClassName(param) + progLangOpenParameterSpace[progLang] + progLangStringOpenClose[progLang] + param->name + progLangStringOpenClose[progLang] + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];
	#else
	string newTempEntityText = generateCodeEntityDefinitionText(param, progLang) + progLangEquals[progLang] + progLangNewObject[progLang] + generateEntityClassName(param) + progLangOpenParameterSpace[progLang] + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];
	#endif
	return newTempEntityText;
}

string generateCodeNewEntity(string className, string instanceName, int progLang)
{
	#ifdef NLC_NONOO
	string newTempEntityText = generateCodeEntityDefinitionText(className, instanceName, progLang) + progLangEquals[progLang] + progLangNewObject[progLang] + className + progLangOpenParameterSpace[progLang] + progLangStringOpenClose[progLang] + removeClassTextFromClassDefinitionName(className) + progLangStringOpenClose[progLang] + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];
	#else
	string newTempEntityText = generateCodeEntityDefinitionText(className, instanceName, progLang) + progLangEquals[progLang] + progLangNewObject[progLang] + className + progLangOpenParameterSpace[progLang] + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];
	#endif
	return newTempEntityText;
}

string generateCodeEntityDefinitionText(NLCitem* param, int progLang)
{
	string tempVariableName = generateCodeEntityDefinitionText(generateEntityClassName(param), generateEntityName(param), progLang);	//ClassName* instanceName
	return tempVariableName;
}

string generateCodeEntityDefinitionText(string className, string instanceName, int progLang)
{
	#ifdef NLC_NONOO
	string tempVariableName = string(NLCNONOO_GENERIC_ENTITY_NODE_NAME) + progLangPointer[progLang] + STRING_SPACE + instanceName;	//GIAentityNode* instanceName
	#else
	string tempVariableName = className + progLangPointer[progLang] + STRING_SPACE + instanceName;	//ClassName* instanceName
	#endif
	return tempVariableName;
}

string generateEntityName(NLCitem* param)
{
	return param->instanceName;
}

string generateEntityClassName(NLCitem* param)
{
	#ifdef NLC_NONOO
	return NLCNONOO_GENERIC_ENTITY_NODE_NAME;
	#else
	return param->className;
	#endif
}


string generateDynamicCastOfEntity(string entityName, string castClassName, int progLang)
{
	string castText = progLangDynamicCastStart[progLang] + castClassName + progLangDynamicCastEnd[progLang] + progLangOpenParameterSpace[progLang] + entityName + progLangCloseParameterSpace[progLang];	//dynamic_cast<castClassName*>(entityName)
	return castText;
}
string generateStaticCastOfEntity(string entityName, string castClassName, int progLang)
{
	string castText = progLangStaticCastStart[progLang] + castClassName + progLangStaticCastEnd[progLang] + progLangOpenParameterSpace[progLang] + entityName + progLangCloseParameterSpace[progLang];	//static_cast<castClassName*>(entityName)
	return castText;
}
string generateStaticCastOfNewEntity(string entityClassName, string castClassName, int progLang)
{
	string castText = progLangStaticCastStart[progLang] + castClassName + progLangStaticCastEnd[progLang] + progLangOpenParameterSpace[progLang] + progLangNewObject[progLang] + entityClassName + progLangCloseParameterSpace[progLang];	//static_cast<castClassName*>(new entityClassName)
	return castText;
}
string generateReinterpretCastOfVector(string vectorName, string castClassName, int progLang)
{
	string castText = progLangReinterpretCastStart[progLang] + generateCodeEntityListDefinitionTypeTextPointer(castClassName, progLang) + progLangReinterpretCastEnd[progLang] + progLangOpenParameterSpace[progLang] + progLangAddress[progLang] + vectorName + progLangCloseParameterSpace[progLang];	//reinterpret_cast<vector<castClassName*>*>(&vectorName)	//creates pointer
	return castText;
}
string generateReinterpretCastOfVectorReference(string vectorName, string castClassName, int progLang)
{
	string castText = progLangReinterpretCastStart[progLang] + generateCodeEntityListDefinitionTypeTextReferenceCompact(castClassName, progLang) + progLangReinterpretCastEnd[progLang] + progLangOpenParameterSpace[progLang] + vectorName + progLangCloseParameterSpace[progLang];	//reinterpret_cast<vector<castClassName*>&>(vectorReferenceName)	//CHECKTHIS	//creates reference
	return castText;
}
string generateReinterpretCastOfConditionList(string vectorName, string castClassName1, string castClassName2, int progLang)
{
	string castText = progLangReinterpretCastStart[progLang] + generateCodeConditionListDefinitionTypeTextPointer(castClassName1, castClassName2, progLang) + progLangReinterpretCastEnd[progLang] + progLangOpenParameterSpace[progLang] + progLangAddress[progLang] + vectorName + progLangCloseParameterSpace[progLang];	//reinterpret_cast<unordered_map<castClassName1*, castClassName2*>*>(&vectorName)
	return castText;
}



//this code is not currently used;
string generateCodeGenericStringMapListDefinitionText(string entityClassName, string genericListNameStart, string genericListAppendName, int progLang)
{
	string codeEntityStringMapListDefinitionText = generateCodeEntityStringMapListDefinitionTypeText(entityClassName, progLang) + generateGenericStringMapListName(genericListNameStart, genericListAppendName);	//unordered_map<string, entityClassName*> genericListNameStart+genericListAppendName;
	return codeEntityStringMapListDefinitionText;
}
string generateGenericStringMapListName(string genericListNameStart, string genericListAppendName)
{
	string codeEntityStringPairPairText = genericListNameStart + genericListAppendName;	//genericListNameStart+genericListAppendName
	return codeEntityStringPairPairText;
}

string generateExternalFunctionContext(string objectName, int progLang)
{
	string externalFunctionContext = generateNewObject(objectName, progLang) + progLangObjectReferenceDelimiter[progLang];	//(new objectNameClass)->
	return externalFunctionContext;
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
	string codeAllPropertyListAddText = generateCodeAllVectorListAddText(generateAllPropertyListName(), propertyListName, propertyListKeyName, progLang);	//propertyLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("propertyListKeyName", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&propertyListName)));
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
	string codeAllVectorListAddText = allListName + progLangObjectReferenceDelimiter2[progLang] + progLangAddAllList[progLang] + progLangOpenParameterSpace[progLang] + generateCodePairText(NLC_USE_LIBRARY_ALL_LISTS_KEY_TYPE, generateCodeEntityListDefinitionTypeTextPointer(NLCgenericClassName, progLang), vectorListKeyName, generateReinterpretCastOfVector(vectorListName, NLCgenericClassName, progLang), progLang) + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//vectorListAll.insert(pair<string, vector<NLCgenericEntityClass*>*>("vectorListKeyName", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&vectorListName)));
	return codeAllVectorListAddText;
}
string generateCodeAllVectorListDefinitionTypeText(int progLang)
{
	string codeEntityStringMapListDefinitionTypeText = generateCodeEntityMapListDefinitionTypeText(NLC_USE_LIBRARY_ALL_LISTS_KEY_TYPE, generateClassName(NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE), progLang) + CHAR_SPACE;	//unordered_map<string, vector<NLCgenericEntityClass*>*>
	return codeEntityStringMapListDefinitionTypeText;
}
string generateCodeEntityMapListDefinitionTypeText(string pairItem1className, string entityClassName, int progLang)
{
	string codeEntityStringMapListDefinitionTypeText = progLangClassList2DMapTypeStart[progLang] + pairItem1className + progLangClassList2DMapTypeMiddle[progLang] + generateCodeEntityListDefinitionTypeTextPointer(entityClassName, progLang) + progLangClassListTypeEnd[progLang];	//unordered_map<x, vector<x*>*>
	return codeEntityStringMapListDefinitionTypeText;
}
string generateCodePairText(string pairItem1className, string pairItem2className, string pairItem1instanceName, string pairItem2instanceName, int progLang)
{
	string codeConditionPairText = generateCodePairTypeText(pairItem1className, pairItem2className, progLang) + progLangClassMemberFunctionParametersOpen[progLang] + pairItem1instanceName + progLangClassMemberFunctionParametersNext[progLang] + pairItem2instanceName + progLangClassMemberFunctionParametersClose[progLang];	//pair<pairItem1className, pairItem2className>(pairItem1, pairItem2)
	return codeConditionPairText;
}
string generateCodePairTextNew(string pairItem1className, string pairItem2className, string pairItem1instanceName, string pairItem2instanceName, int progLang)
{
	string codeConditionPairTypeTextNew = progLangNewObject[progLang] + generateCodePairText(pairItem1className, pairItem2className, pairItem1instanceName, pairItem2instanceName, progLang);	//new pair<pairItem1className, pairItem2className>(pairItem1, pairItem2)
	return codeConditionPairTypeTextNew;
}

string generateCodeAllPropertyIncomingListDefinitionText(int progLang)
{
	string codePropertyListDefinitionText = generateCodeAllPropertyIncomingListDefinitionTypeText(progLang) + generateAllPropertyIncomingListName() + progLangEndLine[progLang];
	return codePropertyListDefinitionText;
}
string generateCodeAllPropertyIncomingListDefinitionTypeText(int progLang)
{
	return generateCodeVectorListDefinitionTypeText(NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE, progLang);
}
string generateAllPropertyIncomingListName()
{
	return NLC_USE_LIBRARY_ALL_PROPERTYINCOMING_LIST_NAME;
}

string generateCodeAllConditionListAddText(string conditionClassName, string conditionObjectClassName, int progLang)
{
	string conditionListName = generateConditionListName(conditionClassName, conditionObjectClassName);
	string conditionName = removeClassTextFromClassDefinitionName(conditionClassName);
	string conditionObjectName = removeClassTextFromClassDefinitionName(conditionObjectClassName);
	string conditionListKeyName1 = string(STRING_INVERTEDCOMMAS) + conditionName + string(STRING_INVERTEDCOMMAS);
	string conditionListKeyName2 = string(STRING_INVERTEDCOMMAS) + conditionObjectName + string(STRING_INVERTEDCOMMAS);
	string codeAllConditionListAddText = generateCodeAllMapListAddText(generateAllConditionListName(), conditionListName, conditionListKeyName1, conditionListKeyName2, progLang);	//conditionListAll.insert(pair<pair<string, string>*, unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>*>(new pair<string, string>("conditionListKeyName1", "conditionListKeyName2"), reinterpret_cast<unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>*>(&conditionListName)));
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
	string codeAllMapListAddText = allListName + progLangObjectReferenceDelimiter2[progLang] + progLangAddAllList[progLang] + progLangOpenParameterSpace[progLang] + generateCodePairPairText(NLC_USE_LIBRARY_ALL_LISTS_KEY_TYPE, NLC_USE_LIBRARY_ALL_LISTS_KEY_TYPE, generateCodeConditionListDefinitionTypeTextPointer(NLCgenericClassName, NLCgenericClassName, progLang), mapListKeyName1, mapListKeyName2, generateReinterpretCastOfConditionList(mapListName, NLCgenericClassName, NLCgenericClassName, progLang), progLang) + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//conditionListAll.insert(pair<pair<string, string>*, unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>*>(new pair<string, string>("mapListKeyName1", "mapListKeyName2"), reinterpret_cast<unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>*>(&mapListName)));
	//string codeAllMapListAddText = allListName + progLangObjectReferenceDelimiter2[progLang] + progLangAddAllList[progLang] + progLangAddAllListKey1open[progLang] + generateCodePairTextNew(NLC_USE_LIBRARY_ALL_LISTS_KEY_TYPE, NLC_USE_LIBRARY_ALL_LISTS_KEY_TYPE, mapListKeyName1, mapListKeyName2, progLang) + progLangAddAllListKey1close[progLang] + progLangOpenParameterSpace[progLang] + generateReinterpretCastOfConditionList(mapListName, NLCgenericClassName, NLCgenericClassName, progLang) + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//conditionListAll.insert[new pair<string, string>("mapListKeyName1", "mapListKeyName2")](reinterpret_cast<unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>*>(&mapListName));
	return codeAllMapListAddText;
}
string generateCodeAllConditionListDefinitionTypeText(int progLang)
{
	string NLCgenericClassName = generateClassName(NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE);
	string codeEntityStringMapListDefinitionTypeText = generateCodeEntityPairMapListDefinitionTypeText(NLC_USE_LIBRARY_ALL_LISTS_KEY_TYPE, NLC_USE_LIBRARY_ALL_LISTS_KEY_TYPE, generateCodeConditionListDefinitionTypeText(NLCgenericClassName, NLCgenericClassName, progLang), progLang) + CHAR_SPACE;	//e.g. unordered_map<pair<string, string>*, unordered_map<x*, x*>*>
	return codeEntityStringMapListDefinitionTypeText;
}
string generateCodeEntityPairMapListDefinitionTypeText(string pairItem1className, string pairItem2className, string entityClassName, int progLang)
{
	string codeEntityStringMapListDefinitionTypeText = progLangClassList2DMapTypeStart[progLang] + generateCodePairTypeText(pairItem1className, pairItem2className, progLang) + progLangPointer[progLang] + progLangClassList2DMapTypeMiddle[progLang] + entityClassName + progLangPointer[progLang] + progLangClassListTypeEnd[progLang];	//unordered_map<pair<x, x>*, x*>
	return codeEntityStringMapListDefinitionTypeText;
}
string generateCodePairTypeText(string pairItem1className, string pairItem2className, int progLang)
{
	string codeConditionPairTypeText = progLangClassPairTypeStart[progLang] + pairItem1className + progLangClassList2DMapTypeMiddle[progLang] + pairItem2className + progLangClassPairTypeEnd[progLang];	//pair<pairItem2className, pairItem2className>
	return codeConditionPairTypeText;
}
string generateCodePairTypeTextPointer(string pairItem1className, string pairItem2className, int progLang)
{
	string codeConditionPairTypeTextPointer = generateCodePairTypeText(pairItem1className, pairItem2className, progLang) + progLangPointer[progLang];	//pair<pairItem2className, pairItem2className>*
	return codeConditionPairTypeTextPointer;
}
string generateCodePairPairText(string pairItem1AclassName, string pairItem1BclassName, string pairItem2className, string pairItem1AinstanceName, string pairItem1BinstanceName, string pairItem2instanceName, int progLang)
{
	string codeConditionPairTypeText = progLangClassPairTypeStart[progLang] + generateCodePairTypeTextPointer(pairItem1AclassName, pairItem1BclassName, progLang) + progLangClassList2DMapTypeMiddle[progLang] + pairItem2className + progLangClassPairTypeEnd[progLang] + progLangClassMemberFunctionParametersOpen[progLang] + generateCodePairTextNew(pairItem1AclassName, pairItem1BclassName, pairItem1AinstanceName, pairItem1BinstanceName, progLang) + progLangClassMemberFunctionParametersNext[progLang] + pairItem2instanceName + progLangClassMemberFunctionParametersClose[progLang];	//pair<pair<pairItem1AclassName, pairItem1BclassName>*, pairItem2className*>(new pair<pairItem1AclassName, pairItem1BclassName>(pairItem1A, pairItem1B), pairItem2)
	return codeConditionPairTypeText;
}

string generateCodeAllConditionIncomingListDefinitionText(int progLang)
{
	string codeConditionIncomingListDefinitionText = generateCodeAllConditionIncomingListDefinitionTypeText(progLang) + generateAllConditionIncomingListName() + progLangEndLine[progLang];
	return codeConditionIncomingListDefinitionText;
}
string generateCodeAllConditionIncomingListDefinitionTypeText(int progLang)
{
	string codeConditionIncmoingListDefinitionTypeText = generateCodeEntityStringMapListDefinitionTypeText(NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE, progLang);
	return codeConditionIncmoingListDefinitionTypeText;
}
string generateAllConditionIncomingListName()
{
	return NLC_USE_LIBRARY_ALL_CONDITIONINCOMING_LIST_NAME;
}

string generateCodeEntityStringMapListDefinitionText(string entityClassName, string mapListName, int progLang)
{
	string codeEntityStringMapListDefinitionText = generateCodeEntityStringMapListDefinitionTypeText(entityClassName, progLang) + mapListName;	//unordered_map<string, entityClassName*> mapListName;
	return codeEntityStringMapListDefinitionText;
}
string generateCodeEntityStringMapListDefinitionTypeText(string entityClassName, int progLang)
{
	string codeEntityStringMapListDefinitionTypeText = progLangClassList2DMapTypeStart[progLang] + progLangClassList2DTypeConditionTypeStringVar[progLang] + progLangClassList2DMapTypeMiddle[progLang] + entityClassName + progLangPointer[progLang] + progLangClassListTypeEnd[progLang];	//unordered_map<string, entityClassName*>
	return codeEntityStringMapListDefinitionTypeText;
}
string generateEntityStringPairText(string entity1Name, string entity2ClassName, string entity2Name, int progLang)
{
	string codeEntityStringPairPairTypeText = progLangClassPairTypeStart[progLang] + progLangClassList2DTypeConditionTypeStringVar[progLang] + progLangClassList2DMapTypeMiddle[progLang] + entity2ClassName + progLangPointer[progLang] + progLangClassPairTypeEnd[progLang] + progLangClassMemberFunctionParametersOpen[progLang] + progLangStringOpenClose[progLang] + entity1Name + progLangStringOpenClose[progLang] + progLangClassMemberFunctionParametersNext[progLang] + entity2Name + progLangClassMemberFunctionParametersClose[progLang];	//pair<string, entity2className*>(entity1name, entity2name)
	return codeEntityStringPairPairTypeText;
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

string generateCodeEntityDeclarationSetToNull(NLCitem* param1, int progLang)
{
	string tempEntityDeclarationText = generateCodeEntityDefinitionText(param1, progLang) + progLangEquals[progLang] + progLangNullPointer[progLang] + progLangEndLine[progLang];	//param1Class* param1 = NULL;
	return tempEntityDeclarationText;
}
string generateCodeSetEntity(NLCitem* param1, NLCitem* param2, int progLang)
{
	string tempVariableName = generateEntityName(param1) + progLangEquals[progLang] + generateEntityName(param2) + progLangEndLine[progLang];	//param1 = param2;
	return tempVariableName;
}
string generateCodeEntityDeclarationSetToEntity(NLCitem* param1, NLCitem* param2, int progLang)
{
	string tempEntityDeclarationText = generateCodeEntityDefinitionText(param1, progLang) + progLangEquals[progLang] + generateEntityName(param2) + progLangEndLine[progLang];	//param1Class* param1 = param2;
	return tempEntityDeclarationText;
}

string generateCodeDeclareBoolTextAndSetFalse(string variableName, int progLang)
{
	string declareText = progLangBoolean[progLang] + variableName + progLangEquals[progLang] + progLangFalse[progLang] + progLangEndLine[progLang];	//bool variable = false;
	return declareText;
}
string generateCodeSetBoolTextTrue(string variableName, int progLang)
{
	string setText = variableName + progLangEquals[progLang] + progLangTrue[progLang] + progLangEndLine[progLang];	//variable = true;
	return setText;
}
string generateCodeReturnText(string variableName, int progLang)
{
	string returnText = progLangReturn[progLang] + variableName + progLangEndLine[progLang];	//return variable;
	return returnText;
}

string generateCodeClassNameVariableDefinitionText(NLCitem* param1, int progLang)
{
	string classNameVariableDefinitionText = progLangClassNameVariableType[progLang] + STRING_SPACE + param1->name + progLangClassNameVariableNameAppend[progLang];	//string param1className
	return classNameVariableDefinitionText;
}

string generateCodeNameVariableDefinitionText(NLCitem* param1, int progLang)
{
	string classNameVariableDefinitionDefaultText = progLangClassNameVariableType[progLang] + param1->name;	//string name
	return classNameVariableDefinitionDefaultText;
}


#ifdef NLC_USE_MATH_OBJECTS
string generateCodeTestEntityMathNumericalValueText(NLCitem* param1, NLCitem* param2, int progLang)
{
	string testEntityMathNumericalValueText = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + generateCodeEntityMathNumericalValueText(param1, progLang) + progLangStringEqualsTest[progLang] + param2->name + progLangCloseParameterSpace[progLang];	//if(param1->numericalValue == param2)
	return testEntityMathNumericalValueText;
}

string generateCodeEntityMathNumericalValueText(NLCitem* param1, int progLang)
{
	string entityMathNumericalValueText = generateCodeEntityMathValueText(generateEntityName(param1), NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_NUMERICAL, progLang);
	return entityMathNumericalValueText;
}
string generateCodeEntityMathValuePointerText(string entityName, int progLang)
{
	string entityMathValueText = generateCodePointerValueText(entityName, progLang);		//*entityName
	return entityMathValueText;
}
string generateCodeDeclareNewDecimalPointerVariableText(NLCitem* param1, int progLang)
{
	string declareNewDecimalPointerVariableText = progLangDecimalPointerType[progLang] + param1->name + progLangEquals[progLang] + progLangNullPointer[progLang] + progLangEndLine[progLang];			 //double* param1 = NULL;
	return declareNewDecimalPointerVariableText;
}
string generateCodeSetDecimalPointerToEntityMathNumericalValueText(NLCitem* param1, NLCitem* param2, int progLang)
{
	string setDecimalPointerToEntityMathNumericalValueText = param1->name + progLangEquals[progLang] + progLangAddress[progLang] + progLangOpenParameterSpace[progLang] + generateCodeEntityMathNumericalValueText(param2, progLang) + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	 //param1 = &(param2->numericalValue);
	return setDecimalPointerToEntityMathNumericalValueText;
}
#ifdef NLC_USE_MATH_OBJECTS_ADVANCED
string generateCodeDeclareNewGenericEntityPointerVariableText(NLCitem* param1, int progLang)
{
	string declareNewDecimalPointerVariableText = generatePointerTypeText(generateClassName(NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE), progLang) + STRING_SPACE + param1->name + progLangEquals[progLang] + progLangNullPointer[progLang] + progLangEndLine[progLang];			 //NLCgenericEntityClass* param1 = NULL;
	return declareNewDecimalPointerVariableText;
}
string generateCodeSetGenericEntityPointerToEntityText(NLCitem* param1, NLCitem* param2, int progLang)
{
	string setGenericEntityPointerToEntityText = param1->name + progLangEquals[progLang] + param2->name + progLangEndLine[progLang];	 //param1 = param2;
	return setGenericEntityPointerToEntityText;
}
#ifdef NLC_USE_MATH_OBJECTS_STRING
string generateCodeEntityMathStringValueText(NLCitem* param1, int progLang)
{
	return generateCodeEntityMathValueText(generateEntityName(param1), NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_STRING, progLang);
}
string generateCodeDeclareNewStringPointerVariableText(NLCitem* param1, int progLang)
{
	string declareNewDecimalPointerVariableText = progLangStringPointerType[progLang] + param1->name + progLangEquals[progLang] + progLangNullPointer[progLang] + progLangEndLine[progLang];			 //string* param1 = NULL;
	return declareNewDecimalPointerVariableText;
}
string generateCodeSetStringPointerToEntityMathStringValueText(NLCitem* param1, NLCitem* param2, int progLang)
{
	string setStringPointerToEntityMathStringValueText = param1->name + progLangEquals[progLang] + progLangAddress[progLang] + progLangOpenParameterSpace[progLang] + generateCodeEntityMathStringValueText(param2, progLang) + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	 //param1 = &(param2->stringValue);
	return setStringPointerToEntityMathStringValueText;
}
#endif
#ifdef NLC_USE_MATH_OBJECTS_BOOLEAN
string generateCodeEntityMathBooleanValueText(NLCitem* param1, int progLang)
{
	return generateCodeEntityMathValueText(generateEntityName(param1), NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_BOOLEAN, progLang);
}
string generateCodeDeclareNewBooleanPointerVariableText(NLCitem* param1, int progLang)
{
	string declareNewDecimalPointerVariableText = progLangBooleanPointerType[progLang] + param1->name + progLangEquals[progLang] + progLangNullPointer[progLang] + progLangEndLine[progLang];			 //string* param1 = NULL;
	return declareNewDecimalPointerVariableText;
}
string generateCodeSetBooleanPointerToEntityMathBooleanValueText(NLCitem* param1, NLCitem* param2, int progLang)
{
	string setBooleanPointerToEntityMathBooleanValueText = param1->name + progLangEquals[progLang] + progLangAddress[progLang] + progLangOpenParameterSpace[progLang] + generateCodeEntityMathBooleanValueText(param2, progLang) + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	 //param1 = &(param2->booleanValue);
	return setBooleanPointerToEntityMathBooleanValueText;
}
#endif
#endif
string generateCodePointerValueText(NLCitem* param1, int progLang)
{
	string pointerValueText = progLangPointer[progLang] + param1->name;	//*param1
	return pointerValueText;
}
string generateCodePointerValueText(string entityName, int progLang)
{
	string pointerValueText = progLangPointer[progLang] + entityName;	//*entityName
	return pointerValueText;
}
string generateCodeEntityMathValueText(string entityName, int mathtextVariableType, int progLang)
{
	string entityMathValueText = entityName + progLangObjectReferenceDelimiter[progLang] + preprocessorMathObjectVariables[mathtextVariableType];		//eg entity->numericalValue
	return entityMathValueText;
}
#endif

string generateReferenceText(string entityName, int progLang)
{
	string pointerValueText = progLangReference[progLang] + entityName;	//&entityName
	return pointerValueText;
}

string generatePointerText(string entityName, int progLang)
{
	string pointerValueText = progLangPointer[progLang] + entityName;	//*entityName
	return pointerValueText;
}

string generatePointerTypeText(string entityName, int progLang)
{
	string pointerVariableText = entityName + progLangPointer[progLang];	//entityName*
	return pointerVariableText;
}

string generateCodeListPointer(string list, int progLang)
{
	string listPointer = string(progLangAddress[progLang]) + progLangOpenParameterSpace[progLang] + list + progLangCloseParameterSpace[progLang];
	return listPointer;
}

string generateCodeIterReference(string iterIndexString, int progLang)
{
	string iterReference = generatePointerText(generateCodeIterName(iterIndexString, progLang), progLang);
	return iterReference;
}
string generateCodeIterReferenceConditionObject(string iterIndexString, int progLang)
{
	#ifdef NLC_CONDITION_LISTS_VECTOR
	string iterConditionObject = progLangOpenParameterSpace[progLang] + generateCodeIterReference(iterIndexString, progLang) + progLangCloseParameterSpace[progLang] + progLangForIterConditionObjectReference[progLang];
	#else
	string iterConditionObject =  generateCodeIterName(iterIndexString, progLang) + progLangForIterConditionObjectReference[progLang];
	#endif
	return iterConditionObject;
}
string generateCodeIterName(string iterIndexString, int progLang)
{
	string iterName = progLangForIterName[progLang] + iterIndexString;
	return iterName;
}


#ifdef NLC_NORMALISE_TWOWAY_PREPOSITIONS_MARK_INVERSE_CONDITIONS
string generateCodeEntityInverseConditionText(NLCitem* param1, int progLang)
{
	string entityInverseConditionText = generateEntityName(param1) + progLangObjectReferenceDelimiter[progLang] + string(NLC_NORMALISE_TWOWAY_PREPOSITIONS_MARK_INVERSE_CONDITIONS_NAME);		//param1->inverseConditionTwoWay
	return entityInverseConditionText;
}
#endif

string generateDefinitionText(string variableType, string variableName)
{
	string definitionText = variableType + CHAR_SPACE + variableName;
	return definitionText;
}

string generateCodeSetText(string variableNameToSet, string variableNameValue, int progLang)
{
	string setText = variableNameToSet + progLangEquals[progLang] + variableNameValue + progLangEndLine[progLang];	//variableNameToSet = variableNameValue;
	return setText;
}

string generateCodeReferenceText(string variableName, string component, int progLang)
{
	string referenceText = variableName + progLangObjectReferenceDelimiter[progLang] + component;	//variableName->component
	return referenceText;
}


