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
 * Project Version: 1j7a 10-September-2014
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
					#ifdef NLC_CLASS_DEFINITIONS_ORDER_BY_DEPENDENCIES
					//only print class definitions once their parent class definitions have been printed
					bool printedParentClassDefinitions = true;
					for(vector<NLCclassDefinition*>::iterator localListIter = classDefinition->definitionList.begin(); localListIter != classDefinition->definitionList.end(); localListIter++)
					{
						NLCclassDefinition * targetClassDefinition = *localListIter;
						if(!(targetClassDefinition->printed))
						{
							//cout << "1 classDefinition = " << classDefinition->name << endl;
							printedParentClassDefinitions = false;	//at least one parent class definition has not been printed
						}
					}
					for(vector<NLCclassDefinition*>::iterator localListIter = classDefinition->propertyList.begin(); localListIter != classDefinition->propertyList.end(); localListIter++)
					{
						NLCclassDefinition * targetClassDefinition = *localListIter;
						if(!(targetClassDefinition->printed))
						{
							//cout << "2 classDefinition = " << classDefinition->name << endl;
							printedParentClassDefinitions = false;	//at least one parent class definition has not been printed
						}
					}
					for(vector<NLCclassDefinition*>::iterator localListIter = classDefinition->conditionList.begin(); localListIter != classDefinition->conditionList.end(); localListIter++)
					{
						NLCclassDefinition * targetClassDefinition = *localListIter;
						if(!(targetClassDefinition->printed))
						{
							//cout << "3 classDefinition = " << classDefinition->name << endl;
							printedParentClassDefinitions = false;	//at least one parent class definition has not been printed
						}
						//isConditionObjectPrinted() is required because conditions are stored as a tuple (to prevent use of isConditionObjectPrinted, NLCclassDefinition conditionLists could be stored as an array[2]; ie vector<NLCclassDefinition *> conditionList[2])
						if(!isConditionObjectPrinted(classDefinitionList, &(targetClassDefinition->parameters)))
						{
							//cout << "4 classDefinition = " << classDefinition->name << endl;
							printedParentClassDefinitions = false;	//at least one parent class definition has not been printed
						}
					}
					for(vector<NLCclassDefinition*>::iterator localListIter = classDefinition->functionList.begin(); localListIter != classDefinition->functionList.end(); localListIter++)
					{
						NLCclassDefinition * targetClassDefinition = *localListIter;
						if(!arefunctionArgumentsPrinted(classDefinitionList, &(targetClassDefinition->parameters)))
						{
							//cout << "5 classDefinition = " << classDefinition->name << endl;
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
						string classNameRaw = className.substr(0, className.length()-strlen(NLC_CLASS_NAME_APPEND));
						//string classNameCode = progLangClassNameVariableType[progLang] + progLangClassNameVariableName[progLang] + progLangStringOpenClose[progLang] + classNameRaw + progLangStringOpenClose[progLang] + progLangEndLine[progLang];	//string name = "dog";

						#ifdef NLC_CLASS_DEFINITIONS_USE_GENERIC_LIBRARY_ENTITY_CLASS
						if(classDefinition->definitionList.empty())
						{//top level NLClibraryEntity class found
						#endif
							string classDefinitionNameCode = progLangClassNameVariableType[progLang] + progLangClassNameVariableName[progLang] + progLangEndLine[progLang];	//string name;
							printLine(classDefinitionNameCode, 1, code);
							#ifdef NLC_USE_ADVANCED_REFERENCING
							string classDefinitionLastSentenceReferencedCode = progLangClassLastSentenceReferencedVariableType[progLang] + string(NLC_USE_ADVANCED_REFERENCING_LAST_SENTENCE_REFERENCED_VARIABLE_NAME) + progLangEndLine[progLang];	//int lastSentenceReferenced;
							printLine(classDefinitionLastSentenceReferencedCode, 1, code);
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
							string targetName = targetClassDefinition->functionNameSpecial;
							string functionArguments = "";

							generateFunctionArgumentsWithActionConceptInheritanceString(&(targetClassDefinition->parameters), &functionArguments, progLang);
							string localListDeclarationText = progLangClassMemberFunctionType[progLang] + targetName + progLangClassMemberFunctionParametersOpen[progLang] + functionArguments + progLangClassMemberFunctionParametersClose[progLang] + progLangEndLine[progLang];
							printLine(localListDeclarationText, 1, code);
						}

						printLine(progLangCloseClass[progLang], 0, code);
						printLine("", 0, code);

						string classConstructorEntryText = classDefinition->name + progLangFunctionOwnerClassDelimiter[progLang] + classDefinition->name + progLangClassMemberFunctionParametersOpen[progLang] + progLangClassConstructorParameters[progLang] + progLangClassMemberFunctionParametersClose[progLang];
						printLine(classConstructorEntryText, 0, code);
						printLine(progLangOpenClass[progLang], 0, code);
						string classConstructorNameCode = progLangClassNameVariableName[progLang] + progLangClassNameVariableEquals[progLang] + progLangStringOpenClose[progLang] + classNameRaw + progLangStringOpenClose[progLang] + progLangEndLine[progLang];	//name = "dog";
						printLine(classConstructorNameCode, 1, code);
						#ifdef NLC_USE_ADVANCED_REFERENCING
						string classConstructorLastSentenceReferencedCode = "";
						classConstructorLastSentenceReferencedCode = classConstructorLastSentenceReferencedCode + string(NLC_USE_ADVANCED_REFERENCING_LAST_SENTENCE_REFERENCED_VARIABLE_NAME) + progLangClassNameVariableEquals[progLang] + "0" + progLangEndLine[progLang];	//lastSentenceReferenced = 0;
						printLine(classConstructorLastSentenceReferencedCode, 1, code);		
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
	return true;
}

void generateFunctionArgumentsWithActionConceptInheritanceString(vector<NLCitem*> * parameters, string * functionArguments, int progLang)
{
	for(vector<NLCitem*>::iterator parametersIterator = parameters->begin(); parametersIterator < parameters->end(); parametersIterator++)
	{
		//do: ADD: if(functionArgumentCertified);
		NLCitem * currentItem = *parametersIterator;
		/*
		cout << "\tcurrentItem->itemType = " << currentItem->itemType << endl;
		cout << "currentItem->className = " << currentItem->className << endl;
		cout << "currentItem->instanceName = " << currentItem->instanceName << endl;
		*/
		if(currentItem->itemType == NLC_ITEM_TYPE_THIS_FUNCTION_ARGUMENT_INSTANCE_PLURAL)
		{
			if(*functionArguments != "")
			{
				*functionArguments = *functionArguments + progLangClassMemberFunctionParametersNext[progLang];
			}
			*functionArguments = *functionArguments + generateCodePluralDefinitionText(currentItem, progLang);
		}
		#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS
		else if(currentItem->itemType == NLC_ITEM_TYPE_FUNCTION)
		{
			if(*functionArguments != "")
			{
				*functionArguments = *functionArguments + progLangClassMemberFunctionParametersNext[progLang];
			}
			*functionArguments = *functionArguments + generateCodeSingularDefinitionText(currentItem, progLang);
		}
		#endif
		else if(currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_OBJECT)	//is this used?
		{
			if(*functionArguments != "")
			{
				*functionArguments = *functionArguments + progLangClassMemberFunctionParametersNext[progLang];
			}
			*functionArguments = *functionArguments + generateCodeSingularDefinitionText(currentItem, progLang);
		}
		#ifdef NLC_INTERPRET_ACTION_PROPERTIES_AND_CONDITIONS_AS_FUNCTION_ARGUMENTS
		else if(currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_ARGUMENT_CONDITION)
		{
			if(*functionArguments != "")
			{
				*functionArguments = *functionArguments + progLangClassMemberFunctionParametersNext[progLang];
			}
			*functionArguments = *functionArguments + generateCodeConditionPairDefinitionText(currentItem, progLang);
		}
		else if(currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_ARGUMENT_PROPERTY)
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
	string pluralClassName = currentItem->className;
	string pluralInstanceName = currentItem->instanceName;
	#ifdef NLC_SUPPORT_INPUT_FILE_LISTS
	if(currentItem->functionArgumentPassCastRequired)
	{
		pluralClassName = currentItem->functionArgumentPassCastClassName;
	}
	#endif
	string codePluralDefinitionText = progLangClassListTypeStart[progLang] + pluralClassName + progLangPointer[progLang] + progLangClassListTypeEnd[progLang] + pluralClassName + NLC_ITEM_TYPE_PROPERTYLISTVAR_APPENDITION;
	return codePluralDefinitionText;
}

string generateCodeSingularDefinitionText(NLCitem * currentItem, int progLang)
{
	string singularClassName = currentItem->className;
	string singularInstanceName = currentItem->instanceName;
	#ifdef NLC_SUPPORT_INPUT_FILE_LISTS
	if(currentItem->functionArgumentPassCastRequired)
	{
		singularClassName = currentItem->functionArgumentPassCastClassName;
	}
	#endif
	string codeSingularDefinitionText = singularClassName + progLangPointer[progLang] + STRING_SPACE + singularInstanceName;
	return codeSingularDefinitionText;
}

#ifdef NLC_INTERPRET_ACTION_PROPERTIES_AND_CONDITIONS_AS_FUNCTION_ARGUMENTS
string generateCodeConditionPairDefinitionText(NLCitem * currentItem, int progLang)
{
	string conditionClassName = currentItem->className;
	string conditionObjectClassName = currentItem->className2;
	#ifdef NLC_USE_STRING_INDEXED_UNORDERED_MAPS_FOR_CONDITION_LISTS
	string codeConditionListDefinitionText = progLangClassPairTypeStart[progLang] + progLangClassList2DTypeConditionTypeVar[progLang] + progLangClassList2DTypeMiddle[progLang] + conditionClassName + progLangPointer[progLang] + progLangClassPairTypeEnd[progLang] + STRING_SPACE + conditionClassName + NLC_ITEM_TYPE_CONDITIONPAIRVAR_APPENDITION;
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
		//do: ADD: if(functionArgumentCertified);
		NLCitem * currentItem = *parametersIterator;
		/*
		cout << "\tcurrentItem->itemType = " << currentItem->itemType << endl;
		cout << "currentItem->className = " << currentItem->className << endl;
		cout << "currentItem->instanceName = " << currentItem->instanceName << endl;
		*/
		bool functionArgumentFound = false;
		if(currentItem->itemType == NLC_ITEM_TYPE_THIS_FUNCTION_ARGUMENT_INSTANCE_PLURAL)
		{
			functionArgumentFound = true;
		}
		#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS
		else if(currentItem->itemType == NLC_ITEM_TYPE_FUNCTION)
		{
			functionArgumentFound = true;
		}
		#endif
		else if(currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_OBJECT)
		{
			functionArgumentFound = true;
		}
		#ifdef NLC_INTERPRET_ACTION_PROPERTIES_AND_CONDITIONS_AS_FUNCTION_ARGUMENTS
		else if(currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_ARGUMENT_CONDITION)
		{
			functionArgumentFound = true;
		}
		else if(currentItem->itemType == NLC_ITEM_TYPE_FUNCTION_ARGUMENT_PROPERTY)
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
					functionArgumentsPrinted = false;
				}
			}
			else
			{
				cout << "arefunctionArgumentsPrinted(): error: !foundLocalClassDefinition; currentItem->className = " << currentItem->className << endl;
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


