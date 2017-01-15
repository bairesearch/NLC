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
 * File Name: NLCprintClassDefinitions.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2014 Baxter AI (baxterai.com)
 * Project: Natural Language Programming Interface (compiler)
 * Project Version: 1l8h 04-November-2014
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/



#include <ctime>
#include <cstdlib>	//for random number generation
#include <cmath>

#include "NLCprintClassDefinitions.h"
#include "NLCprintDefs.h"


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
bool printClassDefinitions(vector<NLCclassDefinition *> * classDefinitionList, int progLang, string * code)
{
	bool result = true;
	printLine(progLangDependenciesStandardLibaries[progLang], 0, code);
	printLine("", 0, code);
	printLine("", 0, code);
	bool stillUnprintedClassDefinitions = true;
	while(stillUnprintedClassDefinitions)
	{
		bool printedClassDefinitionThisRound = false;
		for(vector<NLCclassDefinition*>::iterator classDefinitionIter = classDefinitionList->begin(); classDefinitionIter != classDefinitionList->end(); classDefinitionIter++)
		{
			NLCclassDefinition * classDefinition = *classDefinitionIter;

			if(!(classDefinition->printed))
			{
				if(!(classDefinition->isActionOrConditionInstanceNotClass))
				{
					#ifdef NLC_DEBUG
					//cout << "printClassDefinitions(): classDefinition->name:" << classDefinition->name << endl;
					#endif
					
					bool printedParentClassDefinitions = true;
					#ifdef NLC_CLASS_DEFINITIONS_ORDER_BY_DEPENDENCIES
					//only print class definitions once their parent class definitions have been printed
					for(vector<NLCclassDefinition*>::iterator localListIter = classDefinition->definitionList.begin(); localListIter != classDefinition->definitionList.end(); localListIter++)
					{
						NLCclassDefinition * targetClassDefinition = *localListIter;
						if(!(targetClassDefinition->printed))
						{
							printedParentClassDefinitions = false;	//at least one parent class definition has not been printed
						}
					}
					for(vector<NLCclassDefinition*>::iterator localListIter = classDefinition->propertyList.begin(); localListIter != classDefinition->propertyList.end(); localListIter++)
					{
						NLCclassDefinition * targetClassDefinition = *localListIter;
						if(!(targetClassDefinition->printed))
						{
							printedParentClassDefinitions = false;	//at least one parent class definition has not been printed
						}
					}
					for(vector<NLCclassDefinition*>::iterator localListIter = classDefinition->conditionList.begin(); localListIter != classDefinition->conditionList.end(); localListIter++)
					{
						NLCclassDefinition * targetClassDefinition = *localListIter;
						if(!(targetClassDefinition->printed))
						{
							printedParentClassDefinitions = false;	//at least one parent class definition has not been printed
						}
						//isConditionObjectPrinted() is required because conditions are stored as a tuple (to prevent use of isConditionObjectPrinted, NLCclassDefinition conditionLists could be stored as an array[2]; ie vector<NLCclassDefinition *> conditionList[2])
						if(!isConditionObjectPrinted(classDefinitionList, &(targetClassDefinition->parameters)))
						{
							printedParentClassDefinitions = false;	//at least one parent class definition has not been printed
						}
					}
					for(vector<NLCclassDefinition*>::iterator localListIter = classDefinition->functionList.begin(); localListIter != classDefinition->functionList.end(); localListIter++)
					{
						NLCclassDefinition * targetClassDefinition = *localListIter;
						if(!arefunctionArgumentsPrinted(classDefinitionList, &(targetClassDefinition->parameters)))
						{
							printedParentClassDefinitions = false;	//at least one parent class definition has not been printed
						}
					}
					#endif
					
					if(printedParentClassDefinitions)
					{//only print class definitions once their parent class definitions have been printed

						string className = classDefinition->name;

						#ifdef NLC_DEBUG
						cout << "printClassDefinitions: className:" << className << endl;
						#endif

						bool foundDefinition = false;
						string classTitleText = "";

						for(vector<NLCclassDefinition*>::iterator localListIter = classDefinition->definitionList.begin(); localListIter != classDefinition->definitionList.end(); localListIter++)
						{
							NLCclassDefinition * targetClassDefinition = *localListIter;

							if(!foundDefinition)
							{
								foundDefinition = true;
								classTitleText = classTitleText + " : ";
							}
							else
							{
								classTitleText = classTitleText + ", ";
							}
							string targetName = targetClassDefinition->name;
							classTitleText = classTitleText + progLangClassInheritanceHeader[progLang] + targetName;
						}

						printedClassDefinitionThisRound = true;
						classDefinition->printed = true;

						string classDefinitionEntryText = progLangClassTitlePrepend[progLang] + className + classTitleText;

						printLine(classDefinitionEntryText, 0, code);
						printLine(progLangOpenClass[progLang], 0, code);
						printLine(progLangClassIntro[progLang], 0, code);
						string classConstructorDeclaration = className + progLangClassConstructorDestructorAppend[progLang] + progLangEndLine[progLang];
						printLine(classConstructorDeclaration, 1, code);
						#ifdef NLC_USE_DESTRUCTORS
						string classDestructorDeclaration = progLangClassDestructorPrepend[progLang] + className + progLangClassConstructorDestructorAppend[progLang] + progLangEndLine[progLang];
						printLine(classDestructorDeclaration, 1, code);
						#endif
						string classNameRaw = removeClassTextFromClassDefinitionName(className);
						//string classNameCode = progLangClassNameVariableType[progLang] + progLangClassNameVariableName[progLang] + progLangStringOpenClose[progLang] + classNameRaw + progLangStringOpenClose[progLang] + progLangEndLine[progLang];	//string name = "dog";

						#ifdef NLC_CLASS_DEFINITIONS_USE_GENERIC_LIBRARY_ENTITY_CLASS
						if(classDefinition->definitionList.empty())
						{//top level NLClibraryEntity class found
						#endif
							string classDefinitionNameCode = progLangClassNameVariableType[progLang] + progLangClassNameVariableName[progLang] + progLangEndLine[progLang];	//string name;
							printLine(classDefinitionNameCode, 1, code);
							#ifdef NLC_USE_ADVANCED_REFERENCING
							string classDefinitionLastSentenceReferencedCode = progLangClassLastSentenceReferencedVariableType[progLang] + string(NLC_USE_ADVANCED_REFERENCING_LAST_SENTENCE_REFERENCED_VARIABLE_NAME) + progLangEndLine[progLang];	//stack<int> lastSentenceReferenced;
							printLine(classDefinitionLastSentenceReferencedCode, 1, code);
							#endif
							#ifdef NLC_USE_ADVANCED_REFERENCING_SUPPORT_ALIASES
							string classDefinitionAliasListCode = progLangAliasListVariableType[progLang] + string(NLC_ITEM_TYPE_ALIASLIST_VAR_APPENDITION) + progLangEndLine[progLang];	//vector<string> aliasList;
							printLine(classDefinitionAliasListCode, 1, code);			
							#endif
						#ifdef NLC_CLASS_DEFINITIONS_USE_GENERIC_LIBRARY_ENTITY_CLASS
						}
						#endif

						for(vector<NLCclassDefinition*>::iterator localListIter = classDefinition->propertyList.begin(); localListIter != classDefinition->propertyList.end(); localListIter++)
						{
							NLCclassDefinition * targetClassDefinition = *localListIter;
							string propertyClassName = targetClassDefinition->name;
							//NLCitem * param1 = targetClassDefinition->parameters.at(0);	//not required to be used
							string localListDeclarationText = generateCodePropertyListDefinitionText(propertyClassName, progLang) + progLangEndLine[progLang];
							printLine(localListDeclarationText, 1, code);
						}

						for(vector<NLCclassDefinition*>::iterator localListIter = classDefinition->conditionList.begin(); localListIter != classDefinition->conditionList.end(); localListIter++)
						{
							NLCclassDefinition * targetClassDefinition = *localListIter;
							//string targetName = targetClassDefinition->name;	//condition instance name not used
							NLCitem * param1 = targetClassDefinition->parameters.at(0);
							string localListDeclarationText = generateCodeConditionListDefinitionText(param1->className, param1->className2, progLang) + progLangEndLine[progLang];
							printLine(localListDeclarationText, 1, code);
						}

						for(vector<NLCclassDefinition*>::iterator localListIter = classDefinition->functionList.begin(); localListIter != classDefinition->functionList.end(); localListIter++)
						{
							NLCclassDefinition * targetClassDefinition = *localListIter;
							#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE
							#ifndef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE_IGNORE_DUPLICATE_FUNCTION_DELCARATIONS
							if(targetClassDefinition->functionDependency != NULL)
							{
							#endif
							#endif
								string targetName = targetClassDefinition->functionNameSpecial;
								string functionArguments = "";

								generateFunctionDeclarationArgumentsWithActionConceptInheritanceString(&(targetClassDefinition->parameters), &functionArguments, progLang);
								string localListDeclarationText = progLangClassMemberFunctionDefaultType[progLang] + targetName + progLangClassMemberFunctionParametersOpen[progLang] + functionArguments + progLangClassMemberFunctionParametersClose[progLang] + progLangEndLine[progLang];
								printLine(localListDeclarationText, 1, code);
							#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE
							#ifndef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE_IGNORE_DUPLICATE_FUNCTION_DELCARATIONS
							}
							#endif
							#endif
						}
						
						#ifdef NLC_RECORD_ACTION_HISTORY
						for(vector<NLCclassDefinition*>::iterator localListIter = classDefinition->actionList.begin(); localListIter != classDefinition->actionList.end(); localListIter++)
						{
							NLCclassDefinition * targetClassDefinition = *localListIter;
							GIAentityNode entityAction;
							entityAction.entityName = removeClassTextFromClassDefinitionName(targetClassDefinition->name);
							NLCitem entityParamAction(&entityAction, NLC_ITEM_TYPE_OBJECT);
							entityParamAction.genericObjectName = generateClassName(entityAction.entityName);
							string genericListAppendName = NLC_ITEM_TYPE_ACTION_VAR_APPENDITION;
							string localListDeclarationText = generateCodeGenericListDefinitionText(&entityParamAction, genericListAppendName, progLang) + progLangEndLine[progLang];
							printLine(localListDeclarationText, 1, code);
						}
						for(vector<NLCclassDefinition*>::iterator localListIter = classDefinition->actionIncomingList.begin(); localListIter != classDefinition->actionIncomingList.end(); localListIter++)
						{
							NLCclassDefinition * targetClassDefinition = *localListIter;
							GIAentityNode entityAction;
							entityAction.entityName = removeClassTextFromClassDefinitionName(targetClassDefinition->name);
							NLCitem entityParamAction(&entityAction, NLC_ITEM_TYPE_OBJECT);
							entityParamAction.genericObjectName = generateClassName(entityAction.entityName);
							string genericListAppendName = NLC_ITEM_TYPE_ACTIONINCOMING_VAR_APPENDITION;
							string localListDeclarationText = generateCodeGenericListDefinitionText(&entityParamAction, genericListAppendName, progLang) + progLangEndLine[progLang];
							printLine(localListDeclarationText, 1, code);
						}
						for(vector<NLCclassDefinition*>::iterator localListIter = classDefinition->actionSubjectList.begin(); localListIter != classDefinition->actionSubjectList.end(); localListIter++)
						{
							NLCclassDefinition * targetClassDefinition = *localListIter;
							GIAentityNode entityActionSubject;
							entityActionSubject.entityName = removeClassTextFromClassDefinitionName(targetClassDefinition->name);
							NLCitem entityParamActionSubject(&entityActionSubject, NLC_ITEM_TYPE_OBJECT);
							entityParamActionSubject.genericObjectName = generateClassName(entityActionSubject.entityName);
							string genericListAppendName = NLC_ITEM_TYPE_ACTIONSUBJECT_VAR_APPENDITION;
							string localListDeclarationText = generateCodeGenericListDefinitionText(&entityParamActionSubject, genericListAppendName, progLang) + progLangEndLine[progLang];
							printLine(localListDeclarationText, 1, code);
						}
						for(vector<NLCclassDefinition*>::iterator localListIter = classDefinition->actionObjectList.begin(); localListIter != classDefinition->actionObjectList.end(); localListIter++)
						{
							NLCclassDefinition * targetClassDefinition = *localListIter;
							GIAentityNode entityActionObject;
							entityActionObject.entityName = removeClassTextFromClassDefinitionName(targetClassDefinition->name);
							NLCitem entityParamActionObject(&entityActionObject, NLC_ITEM_TYPE_OBJECT);
							entityParamActionObject.genericObjectName = generateClassName(entityActionObject.entityName);
							string genericListAppendName = NLC_ITEM_TYPE_ACTIONOBJECT_VAR_APPENDITION;
							string localListDeclarationText = generateCodeGenericListDefinitionText(&entityParamActionObject, genericListAppendName, progLang) + progLangEndLine[progLang];
							printLine(localListDeclarationText, 1, code);
						}
						#endif

						printLine(progLangCloseClass[progLang], 0, code);
						printLine("", 0, code);

						string classConstructorEntryText = classDefinition->name + progLangFunctionOwnerClassDelimiter[progLang] + classDefinition->name + progLangClassMemberFunctionParametersOpen[progLang] + progLangClassConstructorParameters[progLang] + progLangClassMemberFunctionParametersClose[progLang];
						printLine(classConstructorEntryText, 0, code);
						printLine(progLangOpenClass[progLang], 0, code);
						string classConstructorNameCode = progLangClassNameVariableName[progLang] + progLangClassNameVariableEquals[progLang] + progLangStringOpenClose[progLang] + classNameRaw + progLangStringOpenClose[progLang] + progLangEndLine[progLang];	//name = "dog";
						printLine(classConstructorNameCode, 1, code);
						#ifdef NLC_USE_ADVANCED_REFERENCING
						#ifdef NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT
						//string classConstructorLastSentenceReferencedCode = "";
						//classConstructorLastSentenceReferencedCode = classConstructorLastSentenceReferencedCode + string(NLC_USE_ADVANCED_REFERENCING_LAST_SENTENCE_REFERENCED_VARIABLE_NAME) + progLangObjectReferenceDelimiter2[progLang] + progLangStackAdd[progLang] + progLangClassMemberFunctionParametersOpen[progLang] + "0" + progLangClassMemberFunctionParametersClose[progLang] + progLangEndLine[progLang];	//lastSentenceReferenced.push(0);
						//printLine(classConstructorLastSentenceReferencedCode, 1, code);	
						#else
						string classConstructorLastSentenceReferencedCode = "";
						classConstructorLastSentenceReferencedCode = classConstructorLastSentenceReferencedCode + string(NLC_USE_ADVANCED_REFERENCING_LAST_SENTENCE_REFERENCED_VARIABLE_NAME) + progLangClassNameVariableEquals[progLang] + "0" + progLangEndLine[progLang];	//lastSentenceReferenced = 0;
						printLine(classConstructorLastSentenceReferencedCode, 1, code);	
						#endif
						#endif
						printLine(progLangCloseClass[progLang], 0, code);
						printLine("", 0, code);
					}
				}
			}
		}
		if(!printedClassDefinitionThisRound)
		{
			stillUnprintedClassDefinitions = false;
		}
	}
	return result;
}

void generateFunctionDeclarationArgumentsWithActionConceptInheritanceString(vector<NLCitem*> * parameters, string * functionArguments, int progLang)
{
	for(vector<NLCitem*>::iterator parametersIterator = parameters->begin(); parametersIterator < parameters->end(); parametersIterator++)
	{
		//do: add: if(functionArgumentCertified)?
		
		NLCitem * currentItem = *parametersIterator;
		
		#ifdef NLC_DEBUG
		//cout << "generateFunctionDeclarationArgumentsWithActionConceptInheritanceString(): " << endl;
		//cout << "currentItem->itemType = " << currentItem->itemType << endl;
		//cout << "currentItem->className = " << currentItem->className << endl;
		//cout << "currentItem->instanceName = " << currentItem->instanceName << endl;
		#endif
		
		if(currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_DECLARATION_ARGUMENT_INSTANCE_OR_CLASS_LIST)
		{
			if(*functionArguments != "")
			{
				*functionArguments = *functionArguments + progLangClassMemberFunctionParametersNext[progLang];
			}
			*functionArguments = *functionArguments + generateCodePluralDefinitionText(currentItem, progLang);
		}
		#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS
		else if(currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_INSTANCE_OR_CLASS_LIST)	//this is required as function arguments in function definition may be copied to function arguments in function declaration [although they are not currently copied to function arguments in function execution references]
		{
			if(*functionArguments != "")
			{
				*functionArguments = *functionArguments + progLangClassMemberFunctionParametersNext[progLang];
			}
			*functionArguments = *functionArguments + generateCodePluralDefinitionText(currentItem, progLang);
		}
		#endif
		#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS
		#ifdef NLC_FUNCTIONS_SUPPORT_PLURAL_SUBJECTS
		else if(currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_DECLARATION_ARGUMENT_FUNCTION_OWNER)
		{
			if(*functionArguments != "")
			{
				*functionArguments = *functionArguments + progLangClassMemberFunctionParametersNext[progLang];
			}
			#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS_PASS_AS_LISTS
			*functionArguments = *functionArguments + generateCodePluralDefinitionText(currentItem, progLang);	
			#else
			*functionArguments = *functionArguments + generateCodeSingularDefinitionText(currentItem, progLang);
			#endif
		}
		#endif
		else if(currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_DECLARATION_ARGUMENT_FUNCTION)
		{
			if(*functionArguments != "")
			{
				*functionArguments = *functionArguments + progLangClassMemberFunctionParametersNext[progLang];
			}
			#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS_PASS_AS_LISTS
			*functionArguments = *functionArguments + generateCodePluralDefinitionText(currentItem, progLang);	
			#else
			*functionArguments = *functionArguments + generateCodeSingularDefinitionText(currentItem, progLang);
			#endif
		}
		else if(currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_DECLARATION_ARGUMENT_FUNCTION_OBJECT)
		{
			if(*functionArguments != "")
			{
				*functionArguments = *functionArguments + progLangClassMemberFunctionParametersNext[progLang];
			}
			#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS_PASS_AS_LISTS
			*functionArguments = *functionArguments + generateCodePluralDefinitionText(currentItem, progLang);
			#else
			*functionArguments = *functionArguments + generateCodeSingularDefinitionText(currentItem, progLang);
			#endif
		}
		#endif
		#ifdef NLC_INTERPRET_ACTION_PROPERTIES_AND_CONDITIONS_AS_FUNCTION_ARGUMENTS
		else if(currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_DECLARATION_ARGUMENT_CONDITION)
		{
			if(*functionArguments != "")
			{
				*functionArguments = *functionArguments + progLangClassMemberFunctionParametersNext[progLang];
			}
			*functionArguments = *functionArguments + generateCodeConditionPairDefinitionText(currentItem, progLang);
		}
		else if(currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_DECLARATION_ARGUMENT_PROPERTY)
		{
			if(*functionArguments != "")
			{
				*functionArguments = *functionArguments + progLangClassMemberFunctionParametersNext[progLang];
			}
			*functionArguments = *functionArguments + generateCodeSingularDefinitionText(currentItem, progLang);
		}
		#endif
	}
}

string generateCodePluralDefinitionText(NLCitem * currentItem, int progLang)
{
	#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_BASED_ON_IMPLICITLY_DECLARED_VARIABLES_IN_CURRENT_FUNCTION_DEFINITION
	#ifndef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
	string backupClassName = currentItem->className;
	if(currentItem->functionArgumentPassCastRequired)
	{
		currentItem->className = currentItem->functionArgumentPassCastClassName;
	}
	#endif
	#endif
	#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_PASS_LISTS_BY_REFERENCE
	string codePluralDefinitionText = generateCodeEntityListDefinitionReferenceText(currentItem, progLang);
	#else
	string codePluralDefinitionText = generateCodeEntityListDefinitionText(currentItem, progLang);	//OLD: generateCodePropertyListDefinitionText / progLangClassListTypeStart[progLang] + pluralClassName + progLangPointer[progLang] + progLangClassListTypeEnd[progLang] + pluralClassName + NLC_ITEM_TYPE_PROPERTYLIST_VAR_APPENDITION; 
	#endif
	#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_BASED_ON_IMPLICITLY_DECLARED_VARIABLES_IN_CURRENT_FUNCTION_DEFINITION
	#ifndef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
	currentItem->className = backupClassName;
	#endif
	#endif
	return codePluralDefinitionText;
}

string generateCodeSingularDefinitionText(NLCitem * currentItem, int progLang)
{
	#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_BASED_ON_IMPLICITLY_DECLARED_VARIABLES_IN_CURRENT_FUNCTION_DEFINITION
	#ifndef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
	string backupClassName = currentItem->className;
	if(currentItem->functionArgumentPassCastRequired)
	{
		currentItem->className = currentItem->functionArgumentPassCastClassName;
	}
	#endif
	#endif
	string codeSingularDefinitionText = generateEntityDeclaration(currentItem, progLang);
	#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_BASED_ON_IMPLICITLY_DECLARED_VARIABLES_IN_CURRENT_FUNCTION_DEFINITION
	#ifndef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
	currentItem->className = backupClassName;
	#endif
	#endif
	return codeSingularDefinitionText;
}

#ifdef NLC_INTERPRET_ACTION_PROPERTIES_AND_CONDITIONS_AS_FUNCTION_ARGUMENTS
string generateCodeConditionPairDefinitionText(NLCitem * currentItem, int progLang)
{
	string conditionClassName = currentItem->className;
	string conditionObjectClassName = currentItem->className2;
	#ifdef NLC_USE_STRING_INDEXED_UNORDERED_MAPS_FOR_CONDITION_LISTS
	string codeConditionListDefinitionText = progLangClassPairTypeStart[progLang] + progLangClassList2DTypeConditionTypeVar[progLang] + progLangClassList2DTypeMiddle[progLang] + conditionClassName + progLangPointer[progLang] + progLangClassPairTypeEnd[progLang] + STRING_SPACE + conditionClassName + NLC_ITEM_TYPE_CONDITIONPAIR_VAR_APPENDITION;
	#else
	string codeConditionListDefinitionText = progLangClassPairTypeStart[progLang] + conditionClassName + progLangPointer[progLang] + progLangClassList2DTypeMiddle[progLang] + conditionObjectClassName + progLangPointer[progLang] + progLangClassPairTypeEnd[progLang]+ STRING_SPACE + generateConditionPairDefinitionName(conditionClassName, conditionObjectClassName);
	#endif
	return codeConditionListDefinitionText;
}
#endif



bool arefunctionArgumentsPrinted(vector<NLCclassDefinition *> * classDefinitionList, vector<NLCitem*> * parameters)
{
	bool functionArgumentsPrinted = true;

	for(vector<NLCitem*>::iterator parametersIterator = parameters->begin(); parametersIterator < parameters->end(); parametersIterator++)
	{
		//do: add: if(functionArgumentCertified)?
		
		NLCitem * currentItem = *parametersIterator;
		
		#ifdef NLC_DEBUG
		//cout << "arefunctionArgumentsPrinted(): " << endl;
		//cout << "currentItem->itemType = " << currentItem->itemType << endl;
		//cout << "currentItem->className = " << currentItem->className << endl;
		//cout << "currentItem->instanceName = " << currentItem->instanceName << endl;
		#endif
		
		bool functionArgumentFound = false;
		if(currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_DECLARATION_ARGUMENT_INSTANCE_OR_CLASS_LIST)
		{
			functionArgumentFound = true;
		}
		#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS
		#ifdef NLC_FUNCTIONS_SUPPORT_PLURAL_SUBJECTS
		else if(currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_DECLARATION_ARGUMENT_FUNCTION_OWNER)
		{
			functionArgumentFound = true;
		}
		#endif
		else if(currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_DECLARATION_ARGUMENT_FUNCTION)
		{
			functionArgumentFound = true;
		}
		else if(currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_DECLARATION_ARGUMENT_FUNCTION_OBJECT)
		{
			functionArgumentFound = true;
		}
		#endif
		#ifdef NLC_INTERPRET_ACTION_PROPERTIES_AND_CONDITIONS_AS_FUNCTION_ARGUMENTS
		else if(currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_DECLARATION_ARGUMENT_CONDITION)
		{
			functionArgumentFound = true;
		}
		else if(currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_DECLARATION_ARGUMENT_PROPERTY)
		{
			functionArgumentFound = true;
		}
		#endif

		if(functionArgumentFound)
		{
			bool foundLocalClassDefinition = false;
			NLCclassDefinition * localClassDefinition = findClassDefinition(classDefinitionList, currentItem->className, &foundLocalClassDefinition);	//see if class definition already exists
			if(foundLocalClassDefinition)
			{
				if(!(localClassDefinition->printed))
				{
					//cout << "!printed: localClassDefinition->name = " << localClassDefinition->name << endl;
					#ifdef NLC_FUNCTIONS_SUPPORT_PLURAL_SUBJECTS
					if(currentItem->itemType != NLC_ITEM_TYPE_FUNCTION_DECLARATION_ARGUMENT_FUNCTION_OWNER)	//NB function subject entity cant be printed without its function, and function cant be printed without its subject
					{
					#endif
						functionArgumentsPrinted = false;
					#ifdef NLC_FUNCTIONS_SUPPORT_PLURAL_SUBJECTS
					}
					#endif
				}
				else
				{
					#ifdef NLC_DEBUG
					//cout << "arefunctionArgumentsPrinted(): foundLocalClassDefinition && (localClassDefinition->printed): localClassDefinition->name = " << localClassDefinition->name << endl;
					#endif
				}
			}
			else
			{
				#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS
				if(!((currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_DECLARATION_ARGUMENT_FUNCTION) || (currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_DECLARATION_ARGUMENT_FUNCTION_OBJECT)))
				{//NB function definition/declaration names and function object names will not necessarily have a class definition (they will if the function is executed, or if the function object is used)
				#endif
					#ifdef NLC_FUNCTIONS_SUPPORT_PLURAL_SUBJECTS
					if(currentItem->itemType != NLC_ITEM_TYPE_FUNCTION_DECLARATION_ARGUMENT_FUNCTION_OWNER)
					{
					#endif
						cout << "arefunctionArgumentsPrinted(): error: !foundLocalClassDefinition; currentItem->className = " << currentItem->className << endl;
					#ifdef NLC_FUNCTIONS_SUPPORT_PLURAL_SUBJECTS
					}
					#endif
				#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS	
				}
				#endif
			}
		}
	}
	return functionArgumentsPrinted;
}

bool isConditionObjectPrinted(vector<NLCclassDefinition *> * classDefinitionList, vector<NLCitem*> * parameters)
{
	bool functionArgumentsPrinted = true;

	for(vector<NLCitem*>::iterator parametersIterator = parameters->begin(); parametersIterator < parameters->end(); parametersIterator++)
	{
		NLCitem * currentItem = *parametersIterator;
		if(currentItem->itemType == NLC_ITEM_TYPE_CLASS_DECLARATION_CONDITION_LIST)
		{
			bool foundLocalClassDefinition = false;
			NLCclassDefinition * localClassDefinition = findClassDefinition(classDefinitionList, currentItem->className2, &foundLocalClassDefinition);	//see if class definition already exists
			if(foundLocalClassDefinition)
			{
				if(!(localClassDefinition->printed))
				{
					functionArgumentsPrinted = false;
				}
			}
			else
			{
				cout << "isConditionObjectPrinted(): error: !foundLocalClassDefinition; currentItem->className2 = " << currentItem->className2 << endl;
			}
		}
	}
	return functionArgumentsPrinted;
}


