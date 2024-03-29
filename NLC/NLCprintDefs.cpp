 /*******************************************************************************
 *
 * License: GNU Affero General Public License version 3 (AGPLv3)
 *
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: NLCprintDefs.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2022 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler
 * Project Version: 2p1a 05-June-2022
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 * /
 *******************************************************************************/


#include "NLCprintDefs.hpp"

static int progLangGlobal;
int NLCprintDefsClass::getProgLang()
{
	return progLangGlobal;
}
void NLCprintDefsClass::setProgLang(const int progLang)
{
	progLangGlobal = progLang;
}

void NLCprintDefsClass::printLine(const string command, const int level, string* code)
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

string NLCprintDefsClass::generatePropertyListName(const NLCitem* item)
{
	return generatePropertyListName(item->className);
}

string NLCprintDefsClass::generatePropertyListName(const string propertyClassName)
{
	#ifdef NLC_NONOO
	return generatePropertyListName();
	#else
	string propertyListName = propertyClassName + NLC_ITEM_TYPE_PROPERTYLIST_VAR_APPENDITION;
	return propertyListName;
	#endif
}
#ifdef NLC_NONOO
string NLCprintDefsClass::generatePropertyListName()
{
	string propertyListName = GIA_ENTITYNODECLASS_PROPERTYNODELIST_NAME;
	return propertyListName;
}
string NLCprintDefsClass::generatePropertyReverseListName()
{
	string propertyListName = GIA_ENTITYNODECLASS_PROPERTYNODEREVERSELIST_NAME;
	return propertyListName;
}
#endif

#ifdef NLC_RECORD_ACTION_HISTORY
string NLCprintDefsClass::generateActionListName(const string actionClassName)
{
	#ifdef NLC_NONOO
	return generateActionListName();
	#else
	string actionListName = generateGenericListName(actionClassName, NLC_ITEM_TYPE_ACTION_VAR_APPENDITION);
	return actionListName;
	#endif
}
string NLCprintDefsClass::generateActionIncomingListName(const string actionClassName)
{
	#ifdef NLC_NONOO
	return generateActionIncomingListName();
	#else
	string actionIncomingListName = generateGenericListName(actionClassName, NLC_ITEM_TYPE_ACTIONINCOMING_VAR_APPENDITION);
	return actionIncomingListName;
	#endif
}
string NLCprintDefsClass::generateActionSubjectListName(const string actionSubjectClassName)
{
	#ifdef NLC_NONOO
	return generateActionSubjectListName();
	#else
	string actionSubjectListName = generateGenericListName(actionSubjectClassName, NLC_ITEM_TYPE_ACTIONSUBJECT_VAR_APPENDITION);
	return actionSubjectListName;
	#endif
}
string NLCprintDefsClass::generateActionObjectListName(const string actionObjectClassName)
{
	#ifdef NLC_NONOO
	return generateActionObjectListName();
	#else
	string actionObjectListName = generateGenericListName(actionObjectClassName, NLC_ITEM_TYPE_ACTIONOBJECT_VAR_APPENDITION);
	return actionObjectListName;
	#endif
}

#ifdef NLC_NONOO
string NLCprintDefsClass::generateActionListName()
{
	string actionListName = GIA_ENTITYNODECLASS_ACTIONNODELIST_NAME;
	return actionListName;
}
string NLCprintDefsClass::generateActionIncomingListName()
{
	string actionIncomingListName = GIA_ENTITYNODECLASS_INCOMINGACTIONNODELIST_NAME;
	return actionIncomingListName;
}
string NLCprintDefsClass::generateActionSubjectListName()
{
	string actionSubjectListName = GIA_ENTITYNODECLASS_ACTIONSUBJECTLIST_NAME;
	return actionSubjectListName;
}
string NLCprintDefsClass::generateActionObjectListName()
{
	string actionObjectListName = GIA_ENTITYNODECLASS_ACTIONOBJECTLIST_NAME;
	return actionObjectListName;
}
#endif
#endif

string NLCprintDefsClass::generateLocalListName(const string className, const string instanceName)
{
	NLCitem item;
	item.className = className;
	item.instanceName = instanceName;
	return generateEntityListName(&item);
}
string NLCprintDefsClass::generateLocalListName(const NLCitem* item)
{
	return generateEntityListName(item);
}
string NLCprintDefsClass::generateEntityListName(const NLCitem* entityParam)
{
	#ifdef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES
		string instanceName = entityParam->instanceName;
		#ifdef NLC_ORIGINAL_INSTANCE_LIST_NAMES
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

string NLCprintDefsClass::generateEntityListAppendName()
{
	#ifdef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES
		#ifdef NLC_ORIGINAL_INSTANCE_LIST_NAMES
		string entityLocalListAppendName = NLC_ITEM_TYPE_PROPERTYLIST_VAR_APPENDITION;
		#else
		string entityLocalListAppendName = NLC_ITEM_TYPE_INSTANCELIST_VAR_APPENDITION;
		#endif
	#else
		string entityLocalListAppendName =  NLC_ITEM_TYPE_LIST_VAR_APPENDITION;
	#endif
	return entityLocalListAppendName;
}


string NLCprintDefsClass::generateCategoryListName(const NLCitem* param, const string genericListAppendName)
{
	string propertyListName = generateGenericListName(param->genericObjectName, genericListAppendName);
	return propertyListName;
}

string NLCprintDefsClass::generateGenericListName(const string genericObjectName, const string genericListAppendName)
{
	#ifdef NLC_ORIGINAL_INSTANCE_LIST_NAMES
	string propertyListName = genericObjectName + genericListAppendName + NLC_ITEM_TYPE_PROPERTYLIST_VAR_APPENDITION;
	#else
	string propertyListName = genericObjectName + genericListAppendName + NLC_ITEM_TYPE_LIST_VAR_APPENDITION;
	#endif
	return propertyListName;
}

string NLCprintDefsClass::generateConditionListName(const string conditionClassName, const string conditionObjectClassName)
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
string NLCprintDefsClass::generateConditionListName()
{
	return generateGIAconditionListName();
}
string NLCprintDefsClass::generateGIAconditionListName()
{
	string conditionListName = GIA_ENTITYNODECLASS_CONDITIONNODELIST_NAME;
	return conditionListName;
}
string NLCprintDefsClass::generateGIAconditionObjectListName()
{
	string conditionListName = GIA_ENTITYNODECLASS_CONDITIONOBJECTLIST_NAME;
	return conditionListName;
}
string NLCprintDefsClass::generateGIAincomingConditionListName()
{
	string conditionListName = GIA_ENTITYNODECLASS_INCOMINGCONDITIONNODELIST_NAME;
	return conditionListName;
}
string NLCprintDefsClass::generateGIAconditionSubjectListName()
{
	string conditionListName =  GIA_ENTITYNODECLASS_CONDITIONSUBJECTLIST_NAME;
	return conditionListName;
}
#else
string NLCprintDefsClass::generateConditionListName(const NLCitem* conditionItem, const NLCitem* conditionObjectItem)
{
	return generateConditionListName(conditionItem->className, conditionObjectItem->className);
}

string NLCprintDefsClass::generateConditionPairDefinitionName(const string conditionClassName, const string conditionObjectClassName)
{
	#ifdef NLC_CONDITION_LISTS_STORE_CONDITION_AS_STRING
	string conditionListName = conditionObjectClassName + NLC_ITEM_TYPE_CONDITIONPAIR_VAR_APPENDITION;
	#else
	string conditionListName = conditionClassName + conditionObjectClassName + NLC_ITEM_TYPE_CONDITIONPAIR_VAR_APPENDITION;
	#endif
	return conditionListName;
}

#ifdef NLC_CONDITION_LISTS_VECTOR
string NLCprintDefsClass::generateCodeConditionNewPairText(const string conditionName, const string conditionClassName, const string conditionInstanceName, const string conditionObjectClassName, const string conditionObjectInstanceName, const int progLang)
{
	string codeConditionNewPairText = progLangNewObject[progLang] + generateCodeConditionPairText(conditionName, conditionClassName, conditionInstanceName, conditionObjectClassName, conditionObjectInstanceName, progLang);
	return codeConditionNewPairText;
}
#endif

string NLCprintDefsClass::generateCodeConditionPairText(const string conditionName, const string conditionClassName, const string conditionInstanceName, const string conditionObjectClassName, const string conditionObjectInstanceName, const int progLang)
{
	#ifdef NLC_CONDITION_LISTS_STORE_CONDITION_AS_STRING
	string codeConditionPairTypeText = progLangClassPairTypeStart[progLang] + progLangClassList2DTypeConditionTypeStringVar[progLang] + progLangClassList2DMapTypeMiddle[progLang] + generatePointerTypeText(conditionObjectClassName, progLang) + progLangClassPairTypeEnd[progLang] + progLangClassMemberFunctionParametersOpen[progLang] + progLangStringOpenClose[progLang] + conditionName + progLangStringOpenClose[progLang] + progLangClassMemberFunctionParametersNext[progLang] + conditionObjectInstanceName + progLangClassMemberFunctionParametersClose[progLang];
	#else
	string codeConditionPairTypeText = progLangClassPairTypeStart[progLang] + conditionClassName + progLangPointer[progLang] + progLangClassList2DMapTypeMiddle[progLang] + generatePointerTypeText(conditionObjectClassName, progLang) + progLangClassPairTypeEnd[progLang] + progLangClassMemberFunctionParametersOpen[progLang] + conditionInstanceName + progLangClassMemberFunctionParametersNext[progLang] + conditionObjectInstanceName + progLangClassMemberFunctionParametersClose[progLang];
	#endif
	return codeConditionPairTypeText;
}

string NLCprintDefsClass::generateCodeConditionPairTextWithContext(const string conditionName, const string conditionClassName, const string conditionInstanceName, const string conditionObjectClassName, const string conditionObjectInstanceName, vector<string>* conditionContext, const int progLang)
{
	#ifdef NLC_CONDITION_LISTS_STORE_CONDITION_AS_STRING
	string codeConditionPairTypeText = progLangClassPairTypeStart[progLang] + progLangClassList2DTypeConditionTypeStringVar[progLang] + progLangClassList2DMapTypeMiddle[progLang] + generatePointerTypeText(conditionObjectClassName, progLang) + progLangClassPairTypeEnd[progLang] + progLangClassMemberFunctionParametersOpen[progLang] + progLangStringOpenClose[progLang] + generateInstanceNameWithContext(conditionInstanceName, conditionContext, progLang) + progLangStringOpenClose[progLang] + progLangClassMemberFunctionParametersNext[progLang] + generateInstanceNameWithContext(conditionObjectInstanceName, conditionContext, progLang) + progLangClassMemberFunctionParametersClose[progLang];
	#else
	string codeConditionPairTypeText = progLangClassPairTypeStart[progLang] + generatePointerTypeText(conditionClassName, progLang) + progLangClassList2DMapTypeMiddle[progLang] + generatePointerTypeText(conditionObjectClassName, progLang) + progLangClassPairTypeEnd[progLang] + progLangClassMemberFunctionParametersOpen[progLang] + generateInstanceNameWithContext(conditionInstanceName, conditionContext, progLang) + progLangClassMemberFunctionParametersNext[progLang] + generateInstanceNameWithContext(conditionObjectInstanceName, conditionContext, progLang) + progLangClassMemberFunctionParametersClose[progLang];
	#endif
	return codeConditionPairTypeText;
}
#endif

string NLCprintDefsClass::generateInstanceNameWithContext(const string instanceName, vector<string>* context, const int progLang)
{
	string instanceNameWithContext = "";
	string contextString = generateStringFromContextVector(context, progLang);
	instanceNameWithContext = contextString + instanceName;
	return instanceNameWithContext;
}

string NLCprintDefsClass::generateStringFromContextVector(vector<string>* context, const int progLang)
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


string NLCprintDefsClass::generateCodePropertyListDefinitionText(const NLCitem* entityParam, const int progLang)
{
	return generateCodePropertyListDefinitionText(entityParam->className, progLang);
}
string NLCprintDefsClass::generateCodePropertyListDefinitionText(const string propertyClassName, const int progLang)
{
	string codePropertyListDefinitionText = generateCodeEntityListDefinitionTypeText(propertyClassName, progLang) + generatePropertyListName(propertyClassName);
	return codePropertyListDefinitionText;
}
string NLCprintDefsClass::generateCodeEntityListDefinitionText(const NLCitem* entityParam, const int progLang)
{
	#ifdef NLC_NONOO
	string codeEntityListDefinitionText = generateCodeEntityListDefinitionTypeTextNonOO(progLang) + generateEntityListName(entityParam);
	#else
	string codeEntityListDefinitionText = generateCodeEntityListDefinitionTypeText(entityParam->className, progLang) + generateEntityListName(entityParam);
	#endif
	return codeEntityListDefinitionText;
}
string NLCprintDefsClass::generateCodeEntityListDefinitionText(const string className, const string instanceName, const int progLang)
{
	#ifdef NLC_NONOO
	string codeEntityListDefinitionText = generateCodeEntityListDefinitionTypeTextNonOO(progLang) + instanceName;
	#else
	string codeEntityListDefinitionText = generateCodeEntityListDefinitionTypeText(className, progLang) + instanceName;
	#endif
	return codeEntityListDefinitionText;
}
string NLCprintDefsClass::generateCodeEntityListDefinitionTypeText(const string entityClassName, const int progLang)
{
	return generateCodeEntityListDefinitionTypeTextCompact(entityClassName, progLang) + CHAR_SPACE;
}
string NLCprintDefsClass::generateCodeEntityListDefinitionTypeTextCompact(const string entityClassName, const int progLang)
{
	#ifdef NLC_NONOO
	return generateCodeEntityListDefinitionTypeTextNonOO(progLang);
	#else
	return generateCodeVectorListDefinitionTypeText(entityClassName, progLang);
	#endif
}
#ifdef NLC_NONOO
string NLCprintDefsClass::generateCodeEntityListDefinitionTypeTextNonOO(const int progLang)
{
	string codeEntityListDefinitionTypeText = progLangClassListTypeStart[progLang] + generatePointerTypeText(NLCNONOO_GENERIC_ENTITY_NODE_NAME, progLang) + progLangClassListTypeEnd[progLang];
	return codeEntityListDefinitionTypeText;
}
#else
string NLCprintDefsClass::generateCodeEntityListDefinitionTypeTextPointer(const string entityClassName, const int progLang)
{
	string codePropertyListDefinitionTextPointer = generatePointerTypeText(generateCodeEntityListDefinitionTypeTextCompact(entityClassName, progLang), progLang);		//vector<entityClassName*>*
	return codePropertyListDefinitionTextPointer;
}
#ifdef NLC_GENERATE_TYPE_LISTS
string NLCprintDefsClass::generateCodeEntityListDefinitionTypeText2(const string propertyClassName, const int progLang)
{
	string codePropertyListDefinitionText = progLangClassListTypeStart[progLang] + generateCodeVectorListDefinitionTypeTextPointer(propertyClassName, progLang) + progLangClassListTypeEnd[progLang];
	return codePropertyListDefinitionText;
}
#endif
#endif
string NLCprintDefsClass::generateCodeVectorListDefinitionTypeText(const string entityClassName, const int progLang)
{
	string codeVectorListDefinitionText = progLangClassListTypeStart[progLang] + generatePointerTypeText(entityClassName, progLang) + progLangClassListTypeEnd[progLang];	//vector<entityClassName*>
	return codeVectorListDefinitionText;
}
string NLCprintDefsClass::generateCodeVectorListDefinitionTypeTextPointer(const string entityClassName, const int progLang)
{
	string codeVectorListDefinitionTextPointer = generatePointerTypeText(generateCodeVectorListDefinitionTypeText(entityClassName, progLang), progLang);		//vector<entityClassName*>*
	return codeVectorListDefinitionTextPointer;
}
string NLCprintDefsClass::generateCodeVectorListDefinitionTypeText2(const string vectorClassName, const int progLang)
{
	string codePropertyListDefinitionText = progLangClassListTypeStart[progLang] + progLangClassListTypeStart[progLang] + generatePointerTypeText(vectorClassName, progLang) + progLangClassListTypeEnd[progLang] + progLangClassListTypeEnd[progLang];
	return codePropertyListDefinitionText;
}

string NLCprintDefsClass::generateCodeEntityListDefinitionReferenceText(const NLCitem* entityParam, const int progLang)
{
	string codeEntityListDefinitionReferenceText = generateCodeEntityListDefinitionTypeTextReference(entityParam->className, progLang) + generateEntityListName(entityParam);
	return codeEntityListDefinitionReferenceText;
}

string NLCprintDefsClass::generateCodeEntityListDefinitionTypeTextReferenceCompact(const string entityClassName, const int progLang)
{
	#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_PASS_LISTS_BY_REFERENCE
	string codeEntityListDefinitionReferenceTypeText = generateCodeEntityListDefinitionTypeTextCompact(entityClassName, progLang) + progLangReference[progLang];
	#else
	string codeEntityListDefinitionReferenceTypeText = generateCodeEntityListDefinitionTypeTextCompact(entityClassName, progLang);
	#endif
	return codeEntityListDefinitionReferenceTypeText;
}

string NLCprintDefsClass::generateCodeEntityListDefinitionTypeTextReference(const string entityClassName, const int progLang)
{
	string codeEntityListDefinitionReferenceTypeText = generateCodeEntityListDefinitionTypeTextReferenceCompact(entityClassName, progLang) + CHAR_SPACE;
	return codeEntityListDefinitionReferenceTypeText;
}

string NLCprintDefsClass::generateCodeGenericListDefinitionText(const NLCitem* entityParam, const string genericListAppendName, const int progLang)
{
	string codeGenericListDefinitionText = generateCodeEntityListDefinitionTypeText(entityParam->className, progLang) + generateGenericListName(entityParam->genericObjectName, genericListAppendName);
	return codeGenericListDefinitionText;
}



string NLCprintDefsClass::generateCodeConditionListDefinitionText(const NLCitem* conditionParam, const NLCitem* conditionObjectParam, const int progLang)
{
	return generateCodeConditionListDefinitionText(conditionParam->className, conditionObjectParam->className, progLang);
}
string NLCprintDefsClass::generateCodeConditionListDefinitionText(const string conditionClassName, const string conditionObjectClassName, const int progLang)
{
	string codeConditionListDefinitionText = generateCodeConditionListDefinitionTypeText(conditionClassName, conditionObjectClassName, progLang) + generateConditionListName(conditionClassName, conditionObjectClassName);
	return codeConditionListDefinitionText;
}
string NLCprintDefsClass::generateCodeConditionListDefinitionTypeText(const string conditionClassName, const string conditionObjectClassName, const int progLang)
{
	string codeConditionListDefinitionTypeText = generateCodeConditionListDefinitionTypeTextCompact(conditionClassName, conditionObjectClassName, progLang) + CHAR_SPACE;
	return codeConditionListDefinitionTypeText;
}
string NLCprintDefsClass::generateCodeConditionListDefinitionTypeTextCompact(const string conditionClassName, const string conditionObjectClassName, const int progLang)
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
string NLCprintDefsClass::generateCodeVectorPairListDefinitionTypeText(const string conditionClassName, const string conditionObjectClassName, const int progLang)
{
	#ifdef NLC_CONDITION_LISTS_STORE_CONDITION_AS_STRING
	string codeConditionListDefinitionTypeText = progLangClassList2DTypeStart[progLang] + generateCodePairTypeText(progLangClassList2DTypeConditionTypeStringVar[progLang], generatePointerTypeText(conditionObjectClassName, progLang), progLang) + progLangPointer[progLang] + progLangClassListTypeEnd[progLang];	//vector<pair<string, conditionObjectClassName*>*>
	#else
	string codeConditionListDefinitionTypeText = progLangClassList2DTypeStart[progLang] + generateCodePairTypeText(generatePointerTypeText(conditionClassName, progLang), generatePointerTypeText(conditionObjectClassName, progLang), progLang) + progLangPointer[progLang] + progLangClassListTypeEnd[progLang];	//vector<pair<conditionClassName*, conditionObjectClassName*>*>
	#endif
	return codeConditionListDefinitionTypeText;
}
#else
string NLCprintDefsClass::generateCodeMapsListDefinitionTypeText(const string conditionClassName, const string conditionObjectClassName, const int progLang)
{
	#ifdef NLC_CONDITION_LISTS_STORE_CONDITION_AS_STRING
	string codeConditionListDefinitionTypeText = progLangClassList2DMapTypeStart[progLang] + progLangClassList2DTypeConditionTypeStringVar[progLang] + progLangClassList2DMapTypeMiddle[progLang] + generatePointerTypeText(conditionObjectClassName, progLang) + progLangClassListTypeEnd[progLang];	//unordered_map<string,conditionObjectClassName*>
	#else
	string codeConditionListDefinitionTypeText = progLangClassList2DMapTypeStart[progLang] + generatePointerTypeText(conditionClassName, progLang) + progLangClassList2DMapTypeMiddle[progLang] + generatePointerTypeText(conditionObjectClassName, progLang) + progLangClassListTypeEnd[progLang];	//unordered_map<conditionClassName*, conditionObjectClassName*>
	#endif
	return codeConditionListDefinitionTypeText;
}
#endif

#ifdef NLC_NONOO
string NLCprintDefsClass::generateCodeConditionListDefinitionTypeTextNonOO(const int progLang)
{
	string codeConditionListDefinitionTypeText = generateCodeEntityListDefinitionTypeTextNonOO(progLang);
	return codeConditionListDefinitionTypeText;
}
#else
string NLCprintDefsClass::generateCodeConditionListDefinitionTypeTextPointer(const string conditionClassName, const string conditionObjectClassName, const int progLang)
{
	string codeConditionListDefinitionTypeTextPointer = generateCodeConditionListDefinitionTypeTextCompact(conditionClassName, conditionObjectClassName, progLang) + progLangPointer[progLang];	//e.g. unordered_map<conditionClassName*, conditionObjectClassName*>*
	return codeConditionListDefinitionTypeTextPointer;
}
#endif






#ifdef NLC_NONOO
string NLCprintDefsClass::generateGIAentityName()
{
	string GIAentityName = GIA_ENTITYNODECLASS_ENTITYNAME_NAME;
	return GIAentityName;
}

string NLCprintDefsClass::generateCodeEntityNameTestText(const NLCitem* param, const int progLang)
{
	string entityNameTestText = progLangOpenParameterSpace[progLang] + generateEntityName(param) + progLangObjectReferenceDelimiter[progLang] + generateGIAentityName() + progLangStringEqualsTest[progLang] + progLangStringOpenClose[progLang] + param->name + progLangStringOpenClose[progLang] + progLangCloseParameterSpace[progLang];
	return entityNameTestText;
}
#endif
string NLCprintDefsClass::generateCodeClassNameTestText(const string objectName, const string className, const int progLang)
{
	string ifObjectNameEqualsClassNameText = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + objectName + progLangObjectReferenceDelimiter[progLang] + progLangClassNameVariableName[progLang] + progLangEqualsTest[progLang] + progLangStringOpenClose[progLang] + className + progLangStringOpenClose[progLang] + progLangCloseParameterSpace[progLang];	//if(object->name == "className")
	return ifObjectNameEqualsClassNameText;
}


string NLCprintDefsClass::generateCodeNewEntity(const NLCitem* param, const int progLang)
{
	#ifdef NLC_NONOO
	string newTempEntityText = generateCodeEntityDefinitionText(param, progLang) + progLangEquals[progLang] + progLangNewObject[progLang] + generateEntityClassName(param) + progLangOpenParameterSpace[progLang] + progLangStringOpenClose[progLang] + param->name + progLangStringOpenClose[progLang] + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];
	#else
	string newTempEntityText = generateCodeEntityDefinitionText(param, progLang) + progLangEquals[progLang] + progLangNewObject[progLang] + generateEntityClassName(param) + progLangOpenParameterSpace[progLang] + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];
	#endif
	return newTempEntityText;
}

string NLCprintDefsClass::generateCodeNewEntity(const string className, const string instanceName, const int progLang)
{
	#ifdef NLC_NONOO
	string newTempEntityText = generateCodeEntityDefinitionText(className, instanceName, progLang) + progLangEquals[progLang] + progLangNewObject[progLang] + className + progLangOpenParameterSpace[progLang] + progLangStringOpenClose[progLang] + NLCitemClass.removeClassTextFromClassDefinitionName(className) + progLangStringOpenClose[progLang] + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];
	#else
	string newTempEntityText = generateCodeEntityDefinitionText(className, instanceName, progLang) + progLangEquals[progLang] + progLangNewObject[progLang] + className + progLangOpenParameterSpace[progLang] + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];
	#endif
	return newTempEntityText;
}

string NLCprintDefsClass::generateCodeEntityDefinitionText(const NLCitem* param, const int progLang)
{
	string tempVariableName = generateCodeEntityDefinitionText(generateEntityClassName(param), generateEntityName(param), progLang);	//ClassName* instanceName
	return tempVariableName;
}

string NLCprintDefsClass::generateCodeEntityDefinitionText(const string className, const string instanceName, const int progLang)
{
	#ifdef NLC_NONOO
	string tempVariableName = string(NLCNONOO_GENERIC_ENTITY_NODE_NAME) + progLangPointer[progLang] + STRING_SPACE + instanceName;	//GIAentityNode* instanceName
	#else
	string tempVariableName = className + progLangPointer[progLang] + STRING_SPACE + instanceName;	//ClassName* instanceName
	#endif
	return tempVariableName;
}

string NLCprintDefsClass::generateEntityName(const NLCitem* param)
{
	return param->instanceName;
}

string NLCprintDefsClass::generateEntityClassName(const NLCitem* param)
{
	#ifdef NLC_NONOO
	return NLCNONOO_GENERIC_ENTITY_NODE_NAME;
	#else
	return param->className;
	#endif
}


string NLCprintDefsClass::generateDynamicCastOfEntity(const string entityName, const string castClassName, const int progLang)
{
	string castText = progLangDynamicCastStart[progLang] + castClassName + progLangDynamicCastEnd[progLang] + progLangOpenParameterSpace[progLang] + entityName + progLangCloseParameterSpace[progLang];	//dynamic_cast<castClassName*>(entityName)
	return castText;
}
string NLCprintDefsClass::generateStaticCastOfEntity(const string entityName, const string castClassName, const int progLang)
{
	string castText = progLangStaticCastStart[progLang] + castClassName + progLangStaticCastEnd[progLang] + progLangOpenParameterSpace[progLang] + entityName + progLangCloseParameterSpace[progLang];	//static_cast<castClassName*>(entityName)
	return castText;
}
string NLCprintDefsClass::generateStaticCastOfNewEntity(const string entityClassName, const string castClassName, const int progLang)
{
	string castText = progLangStaticCastStart[progLang] + castClassName + progLangStaticCastEnd[progLang] + progLangOpenParameterSpace[progLang] + progLangNewObject[progLang] + entityClassName + progLangCloseParameterSpace[progLang];	//static_cast<castClassName*>(new entityClassName)
	return castText;
}
string NLCprintDefsClass::generateReinterpretCastOfVector(const string vectorName, const string castClassName, const int progLang)
{
	string castText = progLangReinterpretCastStart[progLang] + generateCodeEntityListDefinitionTypeTextPointer(castClassName, progLang) + progLangReinterpretCastEnd[progLang] + progLangOpenParameterSpace[progLang] + progLangAddress[progLang] + vectorName + progLangCloseParameterSpace[progLang];	//reinterpret_cast<vector<castClassName*>*>(&vectorName)	//creates pointer
	return castText;
}
string NLCprintDefsClass::generateReinterpretCastOfVectorReference(const string vectorName, const string castClassName, const int progLang)
{
	string castText = progLangReinterpretCastStart[progLang] + generateCodeEntityListDefinitionTypeTextReferenceCompact(castClassName, progLang) + progLangReinterpretCastEnd[progLang] + progLangOpenParameterSpace[progLang] + vectorName + progLangCloseParameterSpace[progLang];	//reinterpret_cast<vector<castClassName*>&>(vectorReferenceName)	//CHECKTHIS	//creates reference
	return castText;
}
string NLCprintDefsClass::generateReinterpretCastOfConditionList(const string vectorName, const string castClassName1, const string castClassName2, const int progLang)
{
	string castText = progLangReinterpretCastStart[progLang] + generateCodeConditionListDefinitionTypeTextPointer(castClassName1, castClassName2, progLang) + progLangReinterpretCastEnd[progLang] + progLangOpenParameterSpace[progLang] + progLangAddress[progLang] + vectorName + progLangCloseParameterSpace[progLang];	//reinterpret_cast<unordered_map<castClassName1*, castClassName2*>*>(&vectorName)
	return castText;
}



//this code is not currently used;
string NLCprintDefsClass::generateCodeGenericStringMapListDefinitionText(const string entityClassName, const string genericListNameStart, const string genericListAppendName, const int progLang)
{
	string codeEntityStringMapListDefinitionText = generateCodeEntityStringMapListDefinitionTypeText(entityClassName, progLang) + generateGenericStringMapListName(genericListNameStart, genericListAppendName);	//unordered_map<string,entityClassName*> genericListNameStart+genericListAppendName;
	return codeEntityStringMapListDefinitionText;
}
string NLCprintDefsClass::generateGenericStringMapListName(const string genericListNameStart, const string genericListAppendName)
{
	string codeEntityStringPairPairText = genericListNameStart + genericListAppendName;	//genericListNameStart+genericListAppendName
	return codeEntityStringPairPairText;
}

string NLCprintDefsClass::generateExternalFunctionContext(const string objectName, const int progLang)
{
	string externalFunctionContext = generateNewObject(objectName, progLang) + progLangObjectReferenceDelimiter[progLang];	//(new objectNameClass)->
	return externalFunctionContext;
}
string NLCprintDefsClass::generateNewObject(const string objectName, const int progLang)
{
	string newObjectText = progLangOpenParameterSpace[progLang] + progLangNewObject[progLang] + NLCitemClass.generateClassName(objectName) + progLangCloseParameterSpace[progLang];	//(new objectNameClass)
	return newObjectText;
}




#ifdef NLC_LIBRARY

string NLCprintDefsClass::generateCodeAllPropertyListAddText(const string propertyClassName, const int progLang)
{
	string propertyListName = generatePropertyListName(propertyClassName);
	string propertyClassNameRaw = NLCitemClass.removeClassTextFromClassDefinitionName(propertyClassName);
	string propertyListKeyName = string(STRING_INVERTEDCOMMAS) + propertyClassNameRaw + string(STRING_INVERTEDCOMMAS);
	string codeAllPropertyListAddText = generateCodeAllVectorListAddText(generateAllPropertyListName(), propertyListName, propertyListKeyName, progLang);	//propertyLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("propertyListKeyName", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&propertyListName)));
	return codeAllPropertyListAddText;
}
string NLCprintDefsClass::generateCodeAllPropertyListDefinitionText(const int progLang)
{
	string codePropertyListDefinitionText = generateCodeAllVectorListDefinitionTypeText(progLang) + generateAllPropertyListName() + progLangEndLine[progLang];
	return codePropertyListDefinitionText;
}
string NLCprintDefsClass::generateAllPropertyListName()
{
	return NLC_LIBRARY_ALL_PROPERTY_LIST_NAME;
}

string NLCprintDefsClass::generateCodeAllVectorListAddText(const string allListName, const string vectorListName, const string vectorListKeyName, const int progLang)
{
	string NLCgenericClassName = NLCitemClass.generateClassName(NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE);
	string codeAllVectorListAddText = allListName + progLangObjectReferenceDelimiter2[progLang] + progLangAddAllList[progLang] + progLangOpenParameterSpace[progLang] + generateCodePairText(NLC_LIBRARY_ALL_LISTS_KEY_TYPE, generateCodeEntityListDefinitionTypeTextPointer(NLCgenericClassName, progLang), vectorListKeyName, generateReinterpretCastOfVector(vectorListName, NLCgenericClassName, progLang), progLang) + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//vectorListAll.insert(pair<string, vector<NLCgenericEntityClass*>*>("vectorListKeyName", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&vectorListName)));
	return codeAllVectorListAddText;
}
string NLCprintDefsClass::generateCodeAllVectorListDefinitionTypeText(const int progLang)
{
	string codeEntityStringMapListDefinitionTypeText = generateCodeEntityMapListDefinitionTypeText(NLC_LIBRARY_ALL_LISTS_KEY_TYPE, NLCitemClass.generateClassName(NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE), progLang) + CHAR_SPACE;	//unordered_map<string,vector<NLCgenericEntityClass*>*>
	return codeEntityStringMapListDefinitionTypeText;
}
string NLCprintDefsClass::generateCodeEntityMapListDefinitionTypeText(const string pairItem1className, const string entityClassName, const int progLang)
{
	string codeEntityStringMapListDefinitionTypeText = progLangClassList2DMapTypeStart[progLang] + pairItem1className + progLangClassList2DMapTypeMiddle[progLang] + generateCodeEntityListDefinitionTypeTextPointer(entityClassName, progLang) + progLangClassListTypeEnd[progLang];	//unordered_map<x, vector<x*>*>
	return codeEntityStringMapListDefinitionTypeText;
}
string NLCprintDefsClass::generateCodePairText(const string pairItem1className, const string pairItem2className, const string pairItem1instanceName, const string pairItem2instanceName, const int progLang)
{
	string codeConditionPairText = generateCodePairTypeText(pairItem1className, pairItem2className, progLang) + progLangClassMemberFunctionParametersOpen[progLang] + pairItem1instanceName + progLangClassMemberFunctionParametersNext[progLang] + pairItem2instanceName + progLangClassMemberFunctionParametersClose[progLang];	//pair<pairItem1className, pairItem2className>(pairItem1, pairItem2)
	return codeConditionPairText;
}
string NLCprintDefsClass::generateCodePairTextNew(const string pairItem1className, const string pairItem2className, const string pairItem1instanceName, const string pairItem2instanceName, const int progLang)
{
	string codeConditionPairTypeTextNew = progLangNewObject[progLang] + generateCodePairText(pairItem1className, pairItem2className, pairItem1instanceName, pairItem2instanceName, progLang);	//new pair<pairItem1className, pairItem2className>(pairItem1, pairItem2)
	return codeConditionPairTypeTextNew;
}

string NLCprintDefsClass::generateCodeAllPropertyIncomingListDefinitionText(const int progLang)
{
	string codePropertyListDefinitionText = generateCodeAllPropertyIncomingListDefinitionTypeText(progLang) + generateAllPropertyIncomingListName() + progLangEndLine[progLang];
	return codePropertyListDefinitionText;
}
string NLCprintDefsClass::generateCodeAllPropertyIncomingListDefinitionTypeText(const int progLang)
{
	return generateCodeVectorListDefinitionTypeText(NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE, progLang);
}
string NLCprintDefsClass::generateAllPropertyIncomingListName()
{
	return NLC_LIBRARY_ALL_PROPERTYINCOMING_LIST_NAME;
}

string NLCprintDefsClass::generateCodeAllConditionListAddText(const string conditionClassName, const string conditionObjectClassName, const int progLang)
{
	string conditionListName = generateConditionListName(conditionClassName, conditionObjectClassName);
	string conditionName = NLCitemClass.removeClassTextFromClassDefinitionName(conditionClassName);
	string conditionObjectName = NLCitemClass.removeClassTextFromClassDefinitionName(conditionObjectClassName);
	string conditionListKeyName1 = string(STRING_INVERTEDCOMMAS) + conditionName + string(STRING_INVERTEDCOMMAS);
	string conditionListKeyName2 = string(STRING_INVERTEDCOMMAS) + conditionObjectName + string(STRING_INVERTEDCOMMAS);
	string codeAllConditionListAddText = generateCodeAllMapListAddText(generateAllConditionListName(), conditionListName, conditionListKeyName1, conditionListKeyName2, progLang);	//conditionListAll.insert(pair<pair<string, string>*, unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>*>(new pair<string, string>("conditionListKeyName1", "conditionListKeyName2"), reinterpret_cast<unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>*>(&conditionListName)));
	return codeAllConditionListAddText;
}
string NLCprintDefsClass::generateCodeAllConditionListDefinitionText(const int progLang)
{
	string codeConditionListDefinitionText = generateCodeAllConditionListDefinitionTypeText(progLang) + generateAllConditionListName() + progLangEndLine[progLang];
	return codeConditionListDefinitionText;
}
string NLCprintDefsClass::generateAllConditionListName()
{
	return NLC_LIBRARY_ALL_CONDITION_LIST_NAME;
}

string NLCprintDefsClass::generateCodeAllMapListAddText(const string allListName, const string mapListName, const string mapListKeyName1, const string mapListKeyName2, const int progLang)
{
	string NLCgenericClassName = NLCitemClass.generateClassName(NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE);
	string codeAllMapListAddText = allListName + progLangObjectReferenceDelimiter2[progLang] + progLangAddAllList[progLang] + progLangOpenParameterSpace[progLang] + generateCodePairPairText(NLC_LIBRARY_ALL_LISTS_KEY_TYPE, NLC_LIBRARY_ALL_LISTS_KEY_TYPE, generateCodeConditionListDefinitionTypeTextPointer(NLCgenericClassName, NLCgenericClassName, progLang), mapListKeyName1, mapListKeyName2, generateReinterpretCastOfConditionList(mapListName, NLCgenericClassName, NLCgenericClassName, progLang), progLang) + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//conditionListAll.insert(pair<pair<string, string>*, unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>*>(new pair<string, string>("mapListKeyName1", "mapListKeyName2"), reinterpret_cast<unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>*>(&mapListName)));
	//string codeAllMapListAddText = allListName + progLangObjectReferenceDelimiter2[progLang] + progLangAddAllList[progLang] + progLangAddAllListKey1open[progLang] + generateCodePairTextNew(NLC_LIBRARY_ALL_LISTS_KEY_TYPE, NLC_LIBRARY_ALL_LISTS_KEY_TYPE, mapListKeyName1, mapListKeyName2, progLang) + progLangAddAllListKey1close[progLang] + progLangOpenParameterSpace[progLang] + generateReinterpretCastOfConditionList(mapListName, NLCgenericClassName, NLCgenericClassName, progLang) + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	//conditionListAll.insert[new pair<string, string>("mapListKeyName1", "mapListKeyName2")](reinterpret_cast<unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>*>(&mapListName));
	return codeAllMapListAddText;
}
string NLCprintDefsClass::generateCodeAllConditionListDefinitionTypeText(const int progLang)
{
	string NLCgenericClassName = NLCitemClass.generateClassName(NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE);
	string codeEntityStringMapListDefinitionTypeText = generateCodeEntityPairMapListDefinitionTypeText(NLC_LIBRARY_ALL_LISTS_KEY_TYPE, NLC_LIBRARY_ALL_LISTS_KEY_TYPE, generateCodeConditionListDefinitionTypeText(NLCgenericClassName, NLCgenericClassName, progLang), progLang) + CHAR_SPACE;	//e.g. unordered_map<pair<string, string>*, unordered_map<x*, x*>*>
	return codeEntityStringMapListDefinitionTypeText;
}
string NLCprintDefsClass::generateCodeEntityPairMapListDefinitionTypeText(const string pairItem1className, const string pairItem2className, const string entityClassName, const int progLang)
{
	string codeEntityStringMapListDefinitionTypeText = progLangClassList2DMapTypeStart[progLang] + generateCodePairTypeText(pairItem1className, pairItem2className, progLang) + progLangPointer[progLang] + progLangClassList2DMapTypeMiddle[progLang] + entityClassName + progLangPointer[progLang] + progLangClassListTypeEnd[progLang];	//unordered_map<pair<x, x>*, x*>
	return codeEntityStringMapListDefinitionTypeText;
}
string NLCprintDefsClass::generateCodePairTypeText(const string pairItem1className, const string pairItem2className, const int progLang)
{
	string codeConditionPairTypeText = progLangClassPairTypeStart[progLang] + pairItem1className + progLangClassList2DMapTypeMiddle[progLang] + pairItem2className + progLangClassPairTypeEnd[progLang];	//pair<pairItem2className, pairItem2className>
	return codeConditionPairTypeText;
}
string NLCprintDefsClass::generateCodePairTypeTextPointer(const string pairItem1className, const string pairItem2className, const int progLang)
{
	string codeConditionPairTypeTextPointer = generateCodePairTypeText(pairItem1className, pairItem2className, progLang) + progLangPointer[progLang];	//pair<pairItem2className, pairItem2className>*
	return codeConditionPairTypeTextPointer;
}
string NLCprintDefsClass::generateCodePairPairText(const string pairItem1AclassName, const string pairItem1BclassName, const string pairItem2className, const string pairItem1AinstanceName, const string pairItem1BinstanceName, const string pairItem2instanceName, const int progLang)
{
	string codeConditionPairTypeText = progLangClassPairTypeStart[progLang] + generateCodePairTypeTextPointer(pairItem1AclassName, pairItem1BclassName, progLang) + progLangClassList2DMapTypeMiddle[progLang] + pairItem2className + progLangClassPairTypeEnd[progLang] + progLangClassMemberFunctionParametersOpen[progLang] + generateCodePairTextNew(pairItem1AclassName, pairItem1BclassName, pairItem1AinstanceName, pairItem1BinstanceName, progLang) + progLangClassMemberFunctionParametersNext[progLang] + pairItem2instanceName + progLangClassMemberFunctionParametersClose[progLang];	//pair<pair<pairItem1AclassName, pairItem1BclassName>*, pairItem2className*>(new pair<pairItem1AclassName, pairItem1BclassName>(pairItem1A, pairItem1B), pairItem2)
	return codeConditionPairTypeText;
}

string NLCprintDefsClass::generateCodeAllConditionIncomingListDefinitionText(const int progLang)
{
	string codeConditionIncomingListDefinitionText = generateCodeAllConditionIncomingListDefinitionTypeText(progLang) + generateAllConditionIncomingListName() + progLangEndLine[progLang];
	return codeConditionIncomingListDefinitionText;
}
string NLCprintDefsClass::generateCodeAllConditionIncomingListDefinitionTypeText(const int progLang)
{
	string codeConditionIncmoingListDefinitionTypeText = generateCodeEntityStringMapListDefinitionTypeText(NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE, progLang);
	return codeConditionIncmoingListDefinitionTypeText;
}
string NLCprintDefsClass::generateAllConditionIncomingListName()
{
	return NLC_LIBRARY_ALL_CONDITIONINCOMING_LIST_NAME;
}

string NLCprintDefsClass::generateCodeEntityStringMapListDefinitionText(const string entityClassName, const string mapListName, const int progLang)
{
	string codeEntityStringMapListDefinitionText = generateCodeEntityStringMapListDefinitionTypeText(entityClassName, progLang) + mapListName;	//unordered_map<string,entityClassName*> mapListName;
	return codeEntityStringMapListDefinitionText;
}
string NLCprintDefsClass::generateCodeEntityStringMapListDefinitionTypeText(const string entityClassName, const int progLang)
{
	string codeEntityStringMapListDefinitionTypeText = progLangClassList2DMapTypeStart[progLang] + progLangClassList2DTypeConditionTypeStringVar[progLang] + progLangClassList2DMapTypeMiddle[progLang] + entityClassName + progLangPointer[progLang] + progLangClassListTypeEnd[progLang];	//unordered_map<string,entityClassName*>
	return codeEntityStringMapListDefinitionTypeText;
}
string NLCprintDefsClass::generateEntityStringPairText(const string entity1Name, const string entity2ClassName, const string entity2Name, const int progLang)
{
	string codeEntityStringPairPairTypeText = progLangClassPairTypeStart[progLang] + progLangClassList2DTypeConditionTypeStringVar[progLang] + progLangClassList2DMapTypeMiddle[progLang] + entity2ClassName + progLangPointer[progLang] + progLangClassPairTypeEnd[progLang] + progLangClassMemberFunctionParametersOpen[progLang] + progLangStringOpenClose[progLang] + entity1Name + progLangStringOpenClose[progLang] + progLangClassMemberFunctionParametersNext[progLang] + entity2Name + progLangClassMemberFunctionParametersClose[progLang];	//pair<string, entity2className*>(entity1name, entity2name)
	return codeEntityStringPairPairTypeText;
}



string NLCprintDefsClass::generateCodeAllActionListAddText(const string actionClassName, const int progLang)
{
	string actionListName = generateActionListName(actionClassName);
	string actionClassNameRaw = NLCitemClass.removeClassTextFromClassDefinitionName(actionClassName);
	string actionListKeyName = string(STRING_INVERTEDCOMMAS) + actionClassNameRaw + string(STRING_INVERTEDCOMMAS);
	string codeAllActionListAddText = generateCodeAllVectorListAddText(generateAllActionListName(), actionListName, actionListKeyName, progLang);	//actionListAll.insert(pair<string, vector<NLCgenericEntityClass*>* >("actionName", reinterpret_cast<vector<NLCgenericEntityClass*>* >(&actionListName)));
	return codeAllActionListAddText;
}
string NLCprintDefsClass::generateCodeAllActionListDefinitionText(const int progLang)
{
	string codeActionListDefinitionText = generateCodeAllVectorListDefinitionTypeText(progLang) + generateAllActionListName() + progLangEndLine[progLang];
	return codeActionListDefinitionText;
}
string NLCprintDefsClass::generateAllActionListName()
{
	return NLC_LIBRARY_ALL_ACTION_LIST_NAME;
}

string NLCprintDefsClass::generateCodeAllActionIncomingListAddText(const string actionIncomingClassName, const int progLang)
{
	string actionIncomingListName = generateActionIncomingListName(actionIncomingClassName);
	string actionIncomingClassNameRaw = NLCitemClass.removeClassTextFromClassDefinitionName(actionIncomingClassName);
	string actionIncomingListKeyName = string(STRING_INVERTEDCOMMAS) + actionIncomingClassNameRaw + string(STRING_INVERTEDCOMMAS);
	string codeAllActionIncomingListAddText = generateCodeAllVectorListAddText(generateAllActionIncomingListName(), actionIncomingListName, actionIncomingListKeyName, progLang);	//actionIncomingListAll.insert(pair<string, vector<NLCgenericEntityClass*>* >("actionIncomingName", reinterpret_cast<vector<NLCgenericEntityClass*>* >(&actionIncomingListName)));
	return codeAllActionIncomingListAddText;
}
string NLCprintDefsClass::generateCodeAllActionIncomingListDefinitionText(const int progLang)
{
	string codeActionIncomingListDefinitionText = generateCodeAllVectorListDefinitionTypeText(progLang) + generateAllActionIncomingListName() + progLangEndLine[progLang];
	return codeActionIncomingListDefinitionText;
}
string NLCprintDefsClass::generateAllActionIncomingListName()
{
	return NLC_LIBRARY_ALL_ACTIONINCOMING_LIST_NAME;
}

string NLCprintDefsClass::generateCodeAllActionSubjectListAddText(const string actionSubjectClassName, const int progLang)
{
	string actionSubjectListName = generateActionSubjectListName(actionSubjectClassName);
	string actionSubjectClassNameRaw = NLCitemClass.removeClassTextFromClassDefinitionName(actionSubjectClassName);
	string actionSubjectListKeyName = string(STRING_INVERTEDCOMMAS) + actionSubjectClassNameRaw + string(STRING_INVERTEDCOMMAS);
	string codeAllActionSubjectListAddText = generateCodeAllVectorListAddText(generateAllActionSubjectListName(), actionSubjectListName, actionSubjectListKeyName, progLang);	//actionSubjectListAll.insert(pair<string, vector<NLCgenericEntityClass*>* >("actionSubjectName", reinterpret_cast<vector<NLCgenericEntityClass*>* >(&actionSubjectListName)));
	return codeAllActionSubjectListAddText;
}
string NLCprintDefsClass::generateCodeAllActionSubjectListDefinitionText(const int progLang)
{
	string codeActionSubjectListDefinitionText = generateCodeAllVectorListDefinitionTypeText(progLang) + generateAllActionSubjectListName() + progLangEndLine[progLang];
	return codeActionSubjectListDefinitionText;
}
string NLCprintDefsClass::generateAllActionSubjectListName()
{
	return NLC_LIBRARY_ALL_ACTIONSUBJECT_LIST_NAME;
}

string NLCprintDefsClass::generateCodeAllActionObjectListAddText(const string actionObjectClassName, const int progLang)
{
	string actionObjectListName = generateActionObjectListName(actionObjectClassName);
	string actionObjectClassNameRaw = NLCitemClass.removeClassTextFromClassDefinitionName(actionObjectClassName);
	string actionObjectListKeyName = string(STRING_INVERTEDCOMMAS) + actionObjectClassNameRaw + string(STRING_INVERTEDCOMMAS);
	string codeAllActionObjectListAddText = generateCodeAllVectorListAddText(generateAllActionObjectListName(), actionObjectListName, actionObjectListKeyName, progLang);	//actionObjectListAll.insert(pair<string, vector<NLCgenericEntityClass*>* >("actionObjectName", reinterpret_cast<vector<NLCgenericEntityClass*>* >(&actionObjectListName)));
	return codeAllActionObjectListAddText;
}
string NLCprintDefsClass::generateCodeAllActionObjectListDefinitionText(const int progLang)
{
	string codeActionObjectListDefinitionText = generateCodeAllVectorListDefinitionTypeText(progLang) + generateAllActionObjectListName() + progLangEndLine[progLang];
	return codeActionObjectListDefinitionText;
}
string NLCprintDefsClass::generateAllActionObjectListName()
{
	return NLC_LIBRARY_ALL_ACTIONOBJECT_LIST_NAME;
}

#endif

string NLCprintDefsClass::generateCodeEntityDeclarationSetToNull(const NLCitem* param1, const int progLang)
{
	string tempEntityDeclarationText = generateCodeEntityDefinitionText(param1, progLang) + progLangEquals[progLang] + progLangNullPointer[progLang] + progLangEndLine[progLang];	//const param1Class* param1 = NULL;
	return tempEntityDeclarationText;
}
string NLCprintDefsClass::generateCodeSetEntity(const NLCitem* param1, const NLCitem* param2, const int progLang)
{
	string tempVariableName = generateEntityName(param1) + progLangEquals[progLang] + generateEntityName(param2) + progLangEndLine[progLang];	//param1 = param2;
	return tempVariableName;
}
string NLCprintDefsClass::generateCodeEntityDeclarationSetToEntity(const NLCitem* param1, const NLCitem* param2, const int progLang)
{
	string tempEntityDeclarationText = generateCodeEntityDefinitionText(param1, progLang) + progLangEquals[progLang] + generateEntityName(param2) + progLangEndLine[progLang];	//const param1Class* param1 = param2;
	return tempEntityDeclarationText;
}

string NLCprintDefsClass::generateCodeDeclareBoolTextAndSetFalse(const string variableName, const int progLang)
{
	string declareText = progLangBoolean[progLang] + variableName + progLangEquals[progLang] + progLangFalse[progLang] + progLangEndLine[progLang];	//bool variable = false;
	return declareText;
}
string NLCprintDefsClass::generateCodeSetBoolTextTrue(const string variableName, const int progLang)
{
	string setText = variableName + progLangEquals[progLang] + progLangTrue[progLang] + progLangEndLine[progLang];	//variable = true;
	return setText;
}
string NLCprintDefsClass::generateCodeReturnText(const string variableName, const int progLang)
{
	string returnText = progLangReturn[progLang] + variableName + progLangEndLine[progLang];	//return variable;
	return returnText;
}

string NLCprintDefsClass::generateCodeClassNameVariableDefinitionText(const NLCitem* param1, const int progLang)
{
	string classNameVariableDefinitionText = progLangClassNameVariableType[progLang] + STRING_SPACE + param1->name + progLangClassNameVariableNameAppend[progLang];	//string param1className
	return classNameVariableDefinitionText;
}

string NLCprintDefsClass::generateCodeNameVariableDefinitionText(const NLCitem* param1, const int progLang)
{
	string classNameVariableDefinitionDefaultText = progLangClassNameVariableType[progLang] + param1->name;	//string name
	return classNameVariableDefinitionDefaultText;
}


#ifdef NLC_MATH_OBJECTS
string NLCprintDefsClass::generateCodeTestEntityMathObjectNumericalValueText(const NLCitem* param1, const NLCitem* param2, const int progLang)
{
	string testEntityMathNumericalValueText = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + generateCodeEntityMathObjectNumericalValueText(param1, progLang) + progLangStringEqualsTest[progLang] + param2->name + progLangCloseParameterSpace[progLang];	//if(param1->mathObjectNumericalValue == param2)
	return testEntityMathNumericalValueText;
}

string NLCprintDefsClass::generateCodeEntityMathObjectNumericalValueText(const NLCitem* param1, const int progLang)
{
	string entityMathNumericalValueText = generateCodeEntityMathObjectValueText(generateEntityName(param1), NLC_MATH_OBJECTS_VARIABLE_TYPE_NUMERICAL, progLang);
	return entityMathNumericalValueText;
}
string NLCprintDefsClass::generateCodeEntityMathValuePointerText(const string entityName, const int progLang)
{
	string entityMathValueText = generateCodePointerValueText(entityName, progLang);		//*entityName
	return entityMathValueText;
}
string NLCprintDefsClass::generateCodeDeclareNewDecimalPointerVariableText(const NLCitem* param1, const int progLang)
{
	string declareNewDecimalPointerVariableText = progLangDecimalPointerType[progLang] + param1->name + progLangEquals[progLang] + progLangNullPointer[progLang] + progLangEndLine[progLang];			 //const double* param1 = NULL;
	return declareNewDecimalPointerVariableText;
}
string NLCprintDefsClass::generateCodeSetDecimalPointerToEntityMathObjectNumericalValueText(const NLCitem* param1, const NLCitem* param2, const int progLang)
{
	string setDecimalPointerToEntityMathObjectNumericalValueText = param1->name + progLangEquals[progLang] + progLangAddress[progLang] + progLangOpenParameterSpace[progLang] + generateCodeEntityMathObjectNumericalValueText(param2, progLang) + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	 //param1 = &(param2->mathObjectNumericalValue);
	return setDecimalPointerToEntityMathObjectNumericalValueText;
}
#ifdef NLC_MATH_OBJECTS_ADVANCED
string NLCprintDefsClass::generateCodeDeclareNewGenericEntityPointerVariableText(const NLCitem* param1, const int progLang)
{
	string declareNewDecimalPointerVariableText = generatePointerTypeText(NLCitemClass.generateClassName(NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE), progLang) + STRING_SPACE + param1->name + progLangEquals[progLang] + progLangNullPointer[progLang] + progLangEndLine[progLang];			 //const NLCgenericEntityClass* param1 = NULL;
	return declareNewDecimalPointerVariableText;
}
string NLCprintDefsClass::generateCodeSetGenericEntityPointerToEntityText(const NLCitem* param1, const NLCitem* param2, const int progLang)
{
	string setGenericEntityPointerToEntityText = param1->name + progLangEquals[progLang] + param2->name + progLangEndLine[progLang];	 //param1 = param2;
	return setGenericEntityPointerToEntityText;
}
#ifdef NLC_MATH_OBJECTS_STRING
string NLCprintDefsClass::generateCodeEntityMathObjectStringValueText(const NLCitem* param1, const int progLang)
{
	return generateCodeEntityMathObjectValueText(generateEntityName(param1), NLC_MATH_OBJECTS_VARIABLE_TYPE_STRING, progLang);
}
string NLCprintDefsClass::generateCodeDeclareNewStringPointerVariableText(const NLCitem* param1, const int progLang)
{
	string declareNewDecimalPointerVariableText = progLangStringPointerType[progLang] + param1->name + progLangEquals[progLang] + progLangNullPointer[progLang] + progLangEndLine[progLang];			 //const string* param1 = NULL;
	return declareNewDecimalPointerVariableText;
}
string NLCprintDefsClass::generateCodeSetStringPointerToEntityMathObjectStringValueText(const NLCitem* param1, const NLCitem* param2, const int progLang)
{
	string setStringPointerToEntityMathObjectStringValueText = param1->name + progLangEquals[progLang] + progLangAddress[progLang] + progLangOpenParameterSpace[progLang] + generateCodeEntityMathObjectStringValueText(param2, progLang) + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	 //param1 = &(param2->mathObjectStringValue);
	return setStringPointerToEntityMathObjectStringValueText;
}
#endif
#ifdef NLC_MATH_OBJECTS_BOOLEAN
string NLCprintDefsClass::generateCodeEntityMathObjectBooleanValueText(const NLCitem* param1, const int progLang)
{
	return generateCodeEntityMathObjectValueText(generateEntityName(param1), NLC_MATH_OBJECTS_VARIABLE_TYPE_BOOLEAN, progLang);
}
string NLCprintDefsClass::generateCodeDeclareNewBooleanPointerVariableText(const NLCitem* param1, const int progLang)
{
	string declareNewDecimalPointerVariableText = progLangBooleanPointerType[progLang] + param1->name + progLangEquals[progLang] + progLangNullPointer[progLang] + progLangEndLine[progLang];			 //const bool* param1 = NULL;
	return declareNewDecimalPointerVariableText;
}
string NLCprintDefsClass::generateCodeSetBooleanPointerToEntityMathObjectBooleanValueText(const NLCitem* param1, const NLCitem* param2, const int progLang)
{
	string setBooleanPointerToEntityMathObjectBooleanValueText = param1->name + progLangEquals[progLang] + progLangAddress[progLang] + progLangOpenParameterSpace[progLang] + generateCodeEntityMathObjectBooleanValueText(param2, progLang) + progLangCloseParameterSpace[progLang] + progLangEndLine[progLang];	 //param1 = &(param2->mathObjectBooleanValue);
	return setBooleanPointerToEntityMathObjectBooleanValueText;
}
#endif
#endif
string NLCprintDefsClass::generateCodePointerValueText(const NLCitem* param1, const int progLang)
{
	string pointerValueText = progLangPointer[progLang] + param1->name;	//*param1
	return pointerValueText;
}
string NLCprintDefsClass::generateCodePointerValueText(const string entityName, const int progLang)
{
	string pointerValueText = progLangPointer[progLang] + entityName;	//*entityName
	return pointerValueText;
}
string NLCprintDefsClass::generateCodeEntityMathObjectValueText(const string entityName, const int mathtextVariableType, const int progLang)
{
	string entityMathValueText = entityName + progLangObjectReferenceDelimiter[progLang] + preprocessorMathObjectVariables[mathtextVariableType];		//eg entity->mathObjectNumericalValue
	return entityMathValueText;
}
string NLCprintDefsClass::generateCodeEntityMathObjectTypeText(const NLCitem* param1, const int progLang)
{
	string entityMathObjectTypeText = generateEntityName(param1) + progLangObjectReferenceDelimiter[progLang] + NLC_MATH_OBJECTS_VARIABLE_TYPE_NAME;	 //entity->mathObjectType;
	return entityMathObjectTypeText;
}
#endif

string NLCprintDefsClass::generateReferenceText(const string entityName, const int progLang)
{
	string pointerValueText = progLangReference[progLang] + entityName;	//&entityName
	return pointerValueText;
}

string NLCprintDefsClass::generatePointerText(const string entityName, const int progLang)
{
	string pointerValueText = progLangPointer[progLang] + entityName;	//*entityName
	return pointerValueText;
}

string NLCprintDefsClass::generatePointerTypeText(const string entityName, const int progLang)
{
	string pointerVariableText = entityName + progLangPointer[progLang];	//entityName*
	return pointerVariableText;
}

string NLCprintDefsClass::generateReferenceTypeText(const string entityName, const int progLang)
{
	string pointerValueText = entityName + progLangReference[progLang];	//entityName&
	return pointerValueText;
}

string NLCprintDefsClass::generateCodeListPointer(const string list, const int progLang)
{
	string listPointer = string(progLangAddress[progLang]) + progLangOpenParameterSpace[progLang] + list + progLangCloseParameterSpace[progLang];
	return listPointer;
}

string NLCprintDefsClass::generateCodeIterReference(const string iterIndexString, const int progLang)
{
	string iterReference = generatePointerText(generateCodeIterName(iterIndexString, progLang), progLang);
	return iterReference;
}
string NLCprintDefsClass::generateCodeIterReferenceConditionObject(const string iterIndexString, const int progLang)
{
	#ifdef NLC_CONDITION_LISTS_VECTOR
	string iterConditionObject = progLangOpenParameterSpace[progLang] + generateCodeIterReference(iterIndexString, progLang) + progLangCloseParameterSpace[progLang] + progLangForIterConditionObjectReference[progLang];
	#else
	string iterConditionObject =  generateCodeIterName(iterIndexString, progLang) + progLangForIterConditionObjectReference[progLang];
	#endif
	return iterConditionObject;
}
string NLCprintDefsClass::generateCodeIterName(const string iterIndexString, const int progLang)
{
	string iterName = progLangForIterName[progLang] + iterIndexString;
	return iterName;
}


#ifdef NLC_NORMALISE_TWOWAY_PREPOSITIONS_MARK_INVERSE_CONDITIONS
string NLCprintDefsClass::generateCodeEntityInverseConditionText(const NLCitem* param1, const int progLang)
{
	string entityInverseConditionText = generateEntityName(param1) + progLangObjectReferenceDelimiter[progLang] + string(NLC_NORMALISE_TWOWAY_PREPOSITIONS_MARK_INVERSE_CONDITIONS_NAME);		//param1->inverseConditionTwoWay
	return entityInverseConditionText;
}
#endif


string NLCprintDefsClass::generateDefinitionText(const string variableType, const string variableName)
{
	string definitionText = variableType + CHAR_SPACE + variableName;
	return definitionText;
}

string NLCprintDefsClass::generateCodeSetText(const string variableNameToSet, const string variableNameValue, const int progLang)
{
	string setText = variableNameToSet + progLangEquals[progLang] + variableNameValue + progLangEndLine[progLang];	//variableNameToSet = variableNameValue;
	return setText;
}

string NLCprintDefsClass::generateCodeReferenceText(const string variableName, const string component, const int progLang)
{
	string referenceText = variableName + progLangObjectReferenceDelimiter[progLang] + component;	//variableName->component
	return referenceText;
}


string NLCprintDefsClass::generateCodeIfVarAequalsVarB(const string varA, const string varB, const int progLang)
{
	string tempVarCheckText = progLangIf[progLang] + progLangOpenParameterSpace[progLang] + varA + progLangStringEqualsTest[progLang] + varB + progLangCloseParameterSpace[progLang];	 //if(varA == varB) {
	return tempVarCheckText;
}

string NLCprintDefsClass::generatePrintedFileName(string fileName)
{
	string printedFileName = "";
	printedFileName = printedFileName + "\n**********************************************************************\n" + fileName + ":\n**********************************************************************\n";
	return printedFileName;
}

