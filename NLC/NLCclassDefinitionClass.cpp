 /*******************************************************************************
 *
 * License: GNU Affero General Public License version 3 (AGPLv3)
 *
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: NLCclassDefinitionClass.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2022 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler
 * Project Version: 2p1a 05-June-2022
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 * /
 *******************************************************************************/


#include "NLCclassDefinitionClass.hpp"


#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE
NLCclassDefinitionFunctionDependency::NLCclassDefinitionFunctionDependency(void)
{
	functionName = "";
	functionOwnerName = "";
	functionObjectName = "";
	hasFunctionOwnerClass = false;
	hasFunctionObjectClass = false;

	functionDefinitionListIndex = INT_DEFAULT_VALUE;
	reconciledFunctionDeclarationArguments = false;

	isReferenceElseFunctionDefinition = false;
}
NLCclassDefinitionFunctionDependency::~NLCclassDefinitionFunctionDependency(void)
{
}
#endif


NLCclassDefinition::NLCclassDefinition(string newName)
{
	name = newName;
	functionNameSpecial = "";

	isActionOrConditionInstanceNotClass = false;
	isConditionInstance = false;

	#ifdef NLC_INPUT_FUNCTION_LISTS_CHECK_ACTION_SUBJECT_CONTENTS_FOR_IMPLICITLY_DECLARED_PARAMETERS
	actionOrConditionInstance = NULL;
	#endif

	printed = false;

	#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE
	functionDependency = NULL;	//for function class definitions only
	#endif

	#ifdef NLC_LIBRARY_FUNCTION_LISTS_FOR_ARGUMENT_RECONCILIATION
	isLibraryFunctionDefinition = false;
	#endif

	#ifdef NLC_API
	#ifndef NLC_API_SEPARATE_FILE_FOR_WRAPPER_FUNCTIONS
	APIclass = false;
	APIsourceFileFullPath = "";
	APIwrapperSourceText = NULL;
	APIwrapperHeaderText = NULL;
	#endif
	#endif
}
NLCclassDefinition::NLCclassDefinition(void)
{
	name = "";
	functionNameSpecial = "";

	isActionOrConditionInstanceNotClass = false;
	isConditionInstance = false;
	#ifdef NLC_INPUT_FUNCTION_LISTS_CHECK_ACTION_SUBJECT_CONTENTS_FOR_IMPLICITLY_DECLARED_PARAMETERS
	actionOrConditionInstance = NULL;
	#endif

	printed = false;

	#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE
	functionDependency = NULL;	//for function class definitions only
	#endif

	#ifdef NLC_LIBRARY_FUNCTION_LISTS_FOR_ARGUMENT_RECONCILIATION
	isLibraryFunctionDefinition = false;
	#endif

	#ifdef NLC_API
	#ifndef NLC_API_SEPARATE_FILE_FOR_WRAPPER_FUNCTIONS
	APIclass = false;
	APIsourceFileFullPath = "";
	APIwrapperSourceText = NULL;
	APIwrapperHeaderText = NULL;
	#endif
	#endif
}
NLCclassDefinition::~NLCclassDefinition(void)
{
}


/*
bool checkSentenceIndexParsingClassHeirarchy(GIAentityNode* entity, int sentenceIndex)
{
	bool result = false;
	if(((entity->sentenceIndexTemp == sentenceIndex) || (entity->wasReference)) && !(entity->parsedForNLCclassHeirarchy))
	{
		result = true;
	}
	return result;
}
*/

#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE_DO_NOT_ADD_FUNCTION_DEPENDENCY_FOR_FUNCTION_REFERENCES

NLCclassDefinition* NLCclassDefinitionClassClass::findClassDefinitionFunction(vector<NLCclassDefinition*>* functionList, const string functionName, const string functionOwnerName, const string functionObjectName, const bool hasFunctionOwnerClass, const bool hasFunctionObjectClass, bool* foundClassDefinition)
{
	NLCclassDefinition* classDefinitionFound = NULL;
	for(vector<NLCclassDefinition*>::iterator classDefinitionIter = functionList->begin(); classDefinitionIter != functionList->end(); classDefinitionIter++)
	{
		NLCclassDefinition* currentClassDef = *classDefinitionIter;
		if(!(currentClassDef->isConditionInstance))
		{
			bool passed = false;
			if(findItemInList(&(currentClassDef->parameters), NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION, functionName))
			{
				passed = true;
			}
			if(passed)
			{
				if(hasFunctionOwnerClass)
				{
					passed = false;
					if(findItemInList(&(currentClassDef->parameters), NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION_OWNER, functionOwnerName))
					{
						passed = true;
					}
				}
			}
			if(passed)
			{
				if(hasFunctionObjectClass)
				{
					passed = false;
					if(findItemInList(&(currentClassDef->parameters), NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION_OBJECT, functionObjectName))
					{
						passed = true;
					}
				}
			}
			if(passed)
			{
				classDefinitionFound = currentClassDef;
				*foundClassDefinition = true;
			}
		}
	}
	return classDefinitionFound;
}

bool NLCclassDefinitionClassClass::findItemInList(vector<NLCitem*>* parameters, const int itemType, const string itemName)
{
	bool foundItem = false;
	for(vector<NLCitem*>::iterator parametersIter = parameters->begin(); parametersIter != parameters->end(); parametersIter++)
	{
		NLCitem* currentItem = *parametersIter;
		if(currentItem->itemType == itemType)
		{
			if(currentItem->name == itemName)
			{
				foundItem = true;
			}
		}
	}
	return foundItem;
}

#endif

NLCclassDefinition* NLCclassDefinitionClassClass::findClassDefinition(vector<NLCclassDefinition*>* classDefinitionList, const string name, bool* foundClassDefinition)
{
	NLCclassDefinition* classDefinitionFound = NULL;
	for(vector<NLCclassDefinition*>::iterator classDefinitionIter = classDefinitionList->begin(); classDefinitionIter != classDefinitionList->end(); classDefinitionIter++)
	{
		NLCclassDefinition* currentClassDef = *classDefinitionIter;
		if(!(currentClassDef->isConditionInstance))
		{
			if(currentClassDef->name == name)
			{
				classDefinitionFound = currentClassDef;
				*foundClassDefinition = true;
			}
		}
	}
	return classDefinitionFound;
}

NLCclassDefinition* NLCclassDefinitionClassClass::findClassDefinitionCondition(vector<NLCclassDefinition*>* classDefinitionList, GIAentityNode* targetEntity, bool* foundClassDefinition)
{
	NLCclassDefinition* classDefinitionFound = NULL;
	if(!(targetEntity->relationshipObjectEntity->empty()))
	{
		string conditionObjectClassName = NLCitemClass.generateClassName((targetEntity->relationshipObjectEntity->back())->entity);

		for(vector<NLCclassDefinition*>::iterator classDefinitionIter = classDefinitionList->begin(); classDefinitionIter != classDefinitionList->end(); classDefinitionIter++)
		{
			NLCclassDefinition* currentClassDef = *classDefinitionIter;
			if(currentClassDef->name == NLCitemClass.generateClassName(targetEntity))
			{
				if(!(currentClassDef->parameters.empty()))
				{
					NLCitem* classDeclarationConditionsListItem = currentClassDef->parameters.back();
					if(classDeclarationConditionsListItem->className2 == conditionObjectClassName)
					{
						classDefinitionFound = currentClassDef;
						*foundClassDefinition = true;
					}
				}
			}
		}
	}
	else
	{
		cout << "findClassDefinitionCondition{} error: condition has no object" << endl;
	}
	return classDefinitionFound;
}

bool NLCclassDefinitionClassClass::findFunctionDefinitionFunctionDependencyInList(vector<NLCclassDefinition*>* classDefinitionList, const string functionName, const string functionOwnerName, const string functionObjectName, const bool hasFunctionOwnerClass, const bool hasFunctionObjectClass, NLCclassDefinitionFunctionDependency** functionDependencyFound)
{
	bool foundFunctionDefinitionFunctionDependency = false;
	NLCclassDefinition* functionDependencyClassDefinitionFound = NULL;
	if(findFunctionDependencyClassDefinitionInList(classDefinitionList, functionName, functionOwnerName, functionObjectName, hasFunctionOwnerClass, hasFunctionObjectClass, &functionDependencyClassDefinitionFound))
	{
		*functionDependencyFound = functionDependencyClassDefinitionFound->functionDependency;
		if(!((*functionDependencyFound)->isReferenceElseFunctionDefinition))
		{
			foundFunctionDefinitionFunctionDependency = true;
		}
	}
	return foundFunctionDefinitionFunctionDependency;
}

bool NLCclassDefinitionClassClass::findFunctionDependencyClassDefinitionInList(vector<NLCclassDefinition*>* classDefinitionList, const string functionName, const string functionOwnerName, const string functionObjectName, const bool hasFunctionOwnerClass, const bool hasFunctionObjectClass, constEffective NLCclassDefinition** classDefinitionFound)
{
	bool foundFunctionDependencyClassDefinition = false;
	for(vector<NLCclassDefinition*>::iterator classDefinitionListIter = classDefinitionList->begin(); classDefinitionListIter != classDefinitionList->end(); classDefinitionListIter++)
	{
		NLCclassDefinition* classDefinition = *classDefinitionListIter;
		if(classDefinition->functionDependency != NULL)
		{
			NLCclassDefinitionFunctionDependency* functionDependency = classDefinition->functionDependency;
			if(compareFunctionDependency(functionDependency, functionName, functionOwnerName, functionObjectName, hasFunctionOwnerClass, hasFunctionObjectClass))
			{
				*classDefinitionFound = classDefinition;
				foundFunctionDependencyClassDefinition = true;
			}
		}
	}
	return foundFunctionDependencyClassDefinition;
}

bool NLCclassDefinitionClassClass::compareFunctionDependency(const NLCclassDefinitionFunctionDependency* functionDependency, const string functionName, const string functionOwnerName, const string functionObjectName, const bool hasFunctionOwnerClass, const bool hasFunctionObjectClass)
{
	bool result = false;
	if(functionDependency->functionName == functionName)
	{
		bool passFunctionOwnerRequirements = false;
		if(hasFunctionOwnerClass)
		{
			if(functionDependency->hasFunctionOwnerClass)
			{
				if(functionDependency->functionOwnerName == functionOwnerName)
				{
					passFunctionOwnerRequirements = true;
				}
			}
		}
		else
		{
			if(!(functionDependency->hasFunctionOwnerClass))
			{
				passFunctionOwnerRequirements = true;
			}
		}
		bool passFunctionObjectRequirements = false;
		if(hasFunctionObjectClass)
		{
			if(functionDependency->hasFunctionObjectClass)
			{
				if(functionDependency->functionObjectName == functionObjectName)
				{
					passFunctionObjectRequirements = true;
				}
			}
		}
		else
		{
			if(!(functionDependency->hasFunctionObjectClass))
			{
				passFunctionObjectRequirements = true;
			}
		}
		if(passFunctionObjectRequirements && passFunctionOwnerRequirements)
		{
			result = true;
		}
	}
	return result;
}

bool NLCclassDefinitionClassClass::findFunctionDefinitionFunctionDependencyInListByIndex(vector<NLCclassDefinition*>* classDefinitionList, const int functionIndex, NLCclassDefinitionFunctionDependency** functionDependencyFound)
{
	bool foundFunctionDefinitionFunctionDependency = false;
	NLCclassDefinition* functionDefinitionClassDefinitionFound = NULL;
	if(findFunctionDependencyClassDefinitionInListByIndex(classDefinitionList, functionIndex, &functionDefinitionClassDefinitionFound))
	{
		*functionDependencyFound = functionDefinitionClassDefinitionFound->functionDependency;
		if(!((*functionDependencyFound)->isReferenceElseFunctionDefinition))	//redundant test (as already testing functionIndex)
		{
			foundFunctionDefinitionFunctionDependency = true;
		}
	}
	return foundFunctionDefinitionFunctionDependency;
}

bool NLCclassDefinitionClassClass::findFunctionDependencyClassDefinitionInListByIndex(vector<NLCclassDefinition*>* classDefinitionList, const int functionIndex, constEffective NLCclassDefinition** functionDefinitionFound)
{
	bool foundFunctionDefinitionClassDefinition = false;
	for(vector<NLCclassDefinition*>::iterator classDefinitionListIter = classDefinitionList->begin(); classDefinitionListIter != classDefinitionList->end(); classDefinitionListIter++)
	{
		NLCclassDefinition* classDefinition = *classDefinitionListIter;
		if(classDefinition->functionDependency != NULL)
		{
			NLCclassDefinitionFunctionDependency* functionDependency = classDefinition->functionDependency;
			if(functionDependency->functionDefinitionListIndex == functionIndex)
			{
				*functionDefinitionFound = classDefinition;
				foundFunctionDefinitionClassDefinition = true;
			}
		}
	}
	return foundFunctionDefinitionClassDefinition;
}


#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE

bool NLCclassDefinitionClassClass::findFunctionDependencyInParent(NLCclassDefinition* parentFunctionDependencyClassDefinition, const string functionName, const string functionOwnerName, const string functionObjectName, const bool hasFunctionOwnerClass, const bool hasFunctionObjectClass, NLCclassDefinitionFunctionDependency** functionDependencyFound)
{
	bool foundFunctionDependency = false;
	for(vector<NLCclassDefinition*>::iterator functionDependencyListIter = parentFunctionDependencyClassDefinition->functionDependencyList.begin(); functionDependencyListIter != parentFunctionDependencyClassDefinition->functionDependencyList.end(); functionDependencyListIter++)
	{
		NLCclassDefinitionFunctionDependency* functionDependency = (*functionDependencyListIter)->functionDependency;
		if(compareFunctionDependency(functionDependency, functionName, functionOwnerName, functionObjectName, hasFunctionOwnerClass, hasFunctionObjectClass))
		{
			*functionDependencyFound = functionDependency;
			foundFunctionDependency = true;
		}
	}
	return foundFunctionDependency;
}

/*
bool findFunctionDependencyInClassDefinitionList(vector<NLCclassDefinition*>* classDefinitionList, string functionName, string functionOwnerName, string functionObjectName, bool hasFunctionOwnerClass, bool hasFunctionObjectClass, NLCclassDefinitionFunctionDependency** functionDependencyFound)
{
	bool foundFunctionDependency = false;
	if(hasFunctionOwnerClass)	//if !hasFunctionOwnerClass, functionDependency is not part of class definition list and are declared independently
	{
		for(vector<NLCclassDefinition*>::iterator classDefinitionIter = classDefinitionList->begin(); classDefinitionIter != classDefinitionList->end(); classDefinitionIter++)
		{
			NLCclassDefinition* currentClassDef = *classDefinitionIter;
			if(currentClassDef->name == generateClassName(functionOwnerName))	//not necessary as this test is handled by compareFunctionDependency()
			{
				for(vector<NLCclassDefinition*>::iterator localListIter = currentClassDef->functionList.begin(); localListIter != currentClassDef->functionList.end(); localListIter++)
				{
					NLCclassDefinition* currentClassDefFunctionReference = *localListIter;
					if(compareFunctionDependency(currentClassDefFunctionReference->functionDependencies, functionName, functionOwnerName, functionObjectName, hasFunctionOwnerClass, hasFunctionObjectClass))
					{
						#ifdef NLC_DEBUG
						//cout << "foundFunctionDependency: functionName = " << functionName << endl;
						#endif
						*functionDependencyFound = currentClassDefFunctionReference->functionDependencies;
						foundFunctionDependency = true;
					}
				}
			}
		}
	}
	return foundFunctionDependency;
}
*/
#endif



#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS
#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
bool NLCclassDefinitionClassClass::findFunctionDefinitionClassDefinitionExactOrNonExactMatch(vector<NLCclassDefinition*>* classDefinitionList, const string functionName, const string functionOwnerName, const string functionObjectName, const bool hasFunctionOwnerClass, const bool hasFunctionObjectClass, constEffective NLCclassDefinition** functionDefinitionClassDefinitionFound, const bool rearrangeClassList, bool* foundFunctionOwnerExactMatch, bool* foundFunctionObjectExactMatch)
{
	bool foundFunctionDefinitionClassDefinition = false;

	bool findFunctionOwnerExactMatch;
	bool findFunctionObjectExactMatch;

	//reconcile function execution "The animal eats the object."/animal->eat(vector object) with function definition "animal#eat+object"/animal::eat(vector object)
	findFunctionOwnerExactMatch = true;
	findFunctionObjectExactMatch = true;
	if(findFunctionDefinitionClassDefinition(classDefinitionList, functionName, functionOwnerName, functionObjectName, hasFunctionOwnerClass, hasFunctionObjectClass, findFunctionOwnerExactMatch, findFunctionObjectExactMatch, functionDefinitionClassDefinitionFound, rearrangeClassList))
	{
		foundFunctionDefinitionClassDefinition = true;
		*foundFunctionOwnerExactMatch = true;
		*foundFunctionObjectExactMatch = true;
	}
	else
	{
		//reconcile function execution "The animal eats the ball."/dog->eat(vector ball) with function definition "animal#eat+object"/animal::eat(vector object)
		findFunctionOwnerExactMatch = true;
		findFunctionObjectExactMatch = false;
		if(findFunctionDefinitionClassDefinition(classDefinitionList, functionName, functionOwnerName, functionObjectName, hasFunctionOwnerClass, hasFunctionObjectClass, findFunctionOwnerExactMatch, findFunctionObjectExactMatch, functionDefinitionClassDefinitionFound, rearrangeClassList))
		{
			foundFunctionDefinitionClassDefinition = true;
			*foundFunctionOwnerExactMatch = true;
			*foundFunctionObjectExactMatch = false;
		}
		else
		{
			//reconcile function execution "The dog eats the object."/dog->eat(vector object) with function definition "animal#eat+object"/animal::eat(vector object)
			findFunctionOwnerExactMatch = false;
			findFunctionObjectExactMatch = true;
			if(findFunctionDefinitionClassDefinition(classDefinitionList, functionName, functionOwnerName, functionObjectName, hasFunctionOwnerClass, hasFunctionObjectClass, findFunctionOwnerExactMatch, findFunctionObjectExactMatch, functionDefinitionClassDefinitionFound, rearrangeClassList))
			{
				foundFunctionDefinitionClassDefinition = true;
				*foundFunctionOwnerExactMatch = false;
				*foundFunctionObjectExactMatch = true;
			}
			else
			{
				//reconcile function execution "The dog eats the ball."/dog->eat(vector ball) with function definition "animal#eat+object"/animal::eat(vector object)
				findFunctionOwnerExactMatch = false;
				findFunctionObjectExactMatch = false;
				if(findFunctionDefinitionClassDefinition(classDefinitionList, functionName, functionOwnerName, functionObjectName, hasFunctionOwnerClass, hasFunctionObjectClass, findFunctionOwnerExactMatch, findFunctionObjectExactMatch, functionDefinitionClassDefinitionFound, rearrangeClassList))
				{
					foundFunctionDefinitionClassDefinition = true;
					*foundFunctionOwnerExactMatch = false;
					*foundFunctionObjectExactMatch = false;
				}
			}
		}
	}
	return foundFunctionDefinitionClassDefinition;
}

//NB if rearrangeClassList, will return functionDefinitionClassDefinitionFound corresponding to the functionDefinition classDefinition child of the function subject/object searched for (but this won't have isReferenceElseFunctionDefinition set)
bool NLCclassDefinitionClassClass::findFunctionDefinitionClassDefinition(vector<NLCclassDefinition*>* classDefinitionList, const string functionName, const string functionOwnerName, const string functionObjectName, const bool hasFunctionOwnerClass, const bool hasFunctionObjectClass, const bool findFunctionOwnerExactMatch, const bool findFunctionObjectExactMatch, constEffective NLCclassDefinition** functionDefinitionClassDefinitionFound, const bool rearrangeClassList)
{
	bool foundFunctionDeclarationClassDefinition = false;
	NLCclassDefinition* classDefinitionFound = NULL;
	for(vector<NLCclassDefinition*>::iterator classDefinitionIter = classDefinitionList->begin(); classDefinitionIter != classDefinitionList->end(); classDefinitionIter++)
	{
		NLCclassDefinition* currentClassDef = *classDefinitionIter;
		for(vector<NLCclassDefinition*>::iterator localListIter = currentClassDef->functionList.begin(); localListIter != currentClassDef->functionList.end(); localListIter++)
		{
			NLCclassDefinition* functionDefinitionClassDefinition = *localListIter;
			if(functionDefinitionClassDefinition->functionNameSpecial == NLCitemClass.generateFunctionName(functionName))
			{
				bool passFunctionDependencyChecks = false;
				#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE_DO_NOT_ADD_FUNCTION_DEPENDENCY_FOR_FUNCTION_REFERENCES
				if(functionDefinitionClassDefinition->functionDependency != NULL)
				{
				#endif
					if(!(functionDefinitionClassDefinition->functionDependency->isReferenceElseFunctionDefinition))
					{
						passFunctionDependencyChecks = true;	//functionReference classDefinition found
					}
				#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE_DO_NOT_ADD_FUNCTION_DEPENDENCY_FOR_FUNCTION_REFERENCES
				}
				#endif
				if(passFunctionDependencyChecks)
				{

					NLCclassDefinition* parentFunctionOwnerClassDef = NULL;
					NLCclassDefinition* parentFunctionObjectClassDef = NULL;
					#ifdef NLC_FUNCTIONS_SUPPORT_PLURAL_SUBJECTS
					NLCitem* functionOwnerArgument = NULL;
					#endif
					NLCitem* functionObjectArgument = NULL;
					bool passFunctionDefinitionRequirements = true;
					if(hasFunctionOwnerClass)
					{
						passFunctionDefinitionRequirements = false;
						if(findFunctionOwnerExactMatch)
						{
							if(currentClassDef->name == NLCitemClass.generateClassName(functionOwnerName))
							{
								passFunctionDefinitionRequirements = true;
							}
						}
						#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ACCEPT_NON_EXACT_MATCH_SUBJECT
						else
						{
							int inheritanceLevel = 0;
							#ifndef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE_DO_NOT_ADD_FUNCTION_DEPENDENCY_FOR_FUNCTION_REFERENCES
							if(rearrangeClassList)
							{
								if(findParentClass(currentClassDef, NLCitemClass.generateClassName(functionOwnerName), 0, &inheritanceLevel, &parentFunctionOwnerClassDef))
								{
									if(currentClassDef != parentFunctionOwnerClassDef)
									{
										passFunctionDefinitionRequirements = true;
										#ifdef NLC_FUNCTIONS_SUPPORT_PLURAL_SUBJECTS
										if(!findFunctionArgument(&(functionDefinitionClassDefinition->parameters), NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION_OWNER, &functionOwnerArgument))
										{
											cout << "findFunctionDefinitionClassDefinition{} error: !findFunctionArgument NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION_OWNER 1" << endl;
										}
										#endif
									}
								}
							}
							else
							{
							#endif
							bool foundClassDefinitionCorrespondingToFunctionOwner = false;
							NLCclassDefinition* classDefinitionCorrespondingToFunctionOwner = findClassDefinition(classDefinitionList, NLCitemClass.generateClassName(functionOwnerName), &foundClassDefinitionCorrespondingToFunctionOwner);

							if(foundClassDefinitionCorrespondingToFunctionOwner)
							{
								if(findParentClass(classDefinitionCorrespondingToFunctionOwner, currentClassDef->name, 0, &inheritanceLevel, &parentFunctionOwnerClassDef))
								{
									if(classDefinitionCorrespondingToFunctionOwner != parentFunctionOwnerClassDef)
									{
										passFunctionDefinitionRequirements = true;
										#ifdef NLC_FUNCTIONS_SUPPORT_PLURAL_SUBJECTS
										if(!findFunctionArgument(&(functionDefinitionClassDefinition->parameters), NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION_OWNER, &functionOwnerArgument))
										{
											cout << "findFunctionDefinitionClassDefinition{} error: !findFunctionArgument NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION_OWNER 2" << endl;
										}
										#endif
									}
								}
							}
							#ifndef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE_DO_NOT_ADD_FUNCTION_DEPENDENCY_FOR_FUNCTION_REFERENCES
							}
							#endif
						}
						#endif
					}
					#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_ARGUMENTS_NO_SUBJECT
					else
					{
						if(currentClassDef->name != NLCitemClass.generateClassName(NLC_CLASS_DEFINITIONS_SUPPORT_FUNCTIONS_WITHOUT_SUBJECT_ARTIFICIAL_CLASS_NAME))
						{
							passFunctionDefinitionRequirements = false;
						}
					}
					#endif
					if(hasFunctionObjectClass)
					{
						if(passFunctionDefinitionRequirements)
						{
							passFunctionDefinitionRequirements = false;
							if(findFunctionObjectExactMatch)
							{
								if(findFunctionArgument(&(functionDefinitionClassDefinition->parameters), functionObjectName, NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION_OBJECT, &functionObjectArgument))	//NB NLCitemClass.generateClassName(functionObjectName) not required
								{
									passFunctionDefinitionRequirements = true;
								}
							}
							#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ACCEPT_NON_EXACT_MATCH_OBJECT
							else
							{
								if(findFunctionArgument(&(functionDefinitionClassDefinition->parameters), NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION_OBJECT, &functionObjectArgument))
								{
									#ifndef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE_DO_NOT_ADD_FUNCTION_DEPENDENCY_FOR_FUNCTION_REFERENCES
									if(rearrangeClassList)
									{
										bool foundClassDefinitionCorrespondingToFunctionObject = false;
										NLCclassDefinition* classDefinitionCorrespondingToFunctionObject = findClassDefinition(classDefinitionList, NLCitemClass.generateClassName(functionObjectArgument->name), &foundClassDefinitionCorrespondingToFunctionObject);

										if(foundClassDefinitionCorrespondingToFunctionObject)
										{
											int inheritanceLevel = 0;
											if(findParentClass(classDefinitionCorrespondingToFunctionObject, NLCitemClass.generateClassName(functionObjectName), 0, &inheritanceLevel, &parentFunctionObjectClassDef))
											{
												if(classDefinitionCorrespondingToFunctionObject != parentFunctionObjectClassDef)
												{
													passFunctionDefinitionRequirements = true;
												}
											}
										}
									}
									else
									{
									#endif
									bool foundClassDefinitionCorrespondingToFunctionObject = false;
									NLCclassDefinition* classDefinitionCorrespondingToFunctionObject = findClassDefinition(classDefinitionList, NLCitemClass.generateClassName(functionObjectName), &foundClassDefinitionCorrespondingToFunctionObject);

									if(foundClassDefinitionCorrespondingToFunctionObject)
									{
										int inheritanceLevel = 0;
										if(findParentClass(classDefinitionCorrespondingToFunctionObject, NLCitemClass.generateClassName(functionObjectArgument->name), 0, &inheritanceLevel, &parentFunctionObjectClassDef))
										{
											if(classDefinitionCorrespondingToFunctionObject != parentFunctionObjectClassDef)
											{
												passFunctionDefinitionRequirements = true;
											}
										}
									}
									#ifndef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE_DO_NOT_ADD_FUNCTION_DEPENDENCY_FOR_FUNCTION_REFERENCES
									}
									#endif
								}
							}
							#endif
						}
					}
					#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_ARGUMENTS_NO_OBJECT
					else
					{
						if(findFunctionArgument(&(functionDefinitionClassDefinition->parameters), NLC_ITEM_TYPE_FUNCTION_DEFINITION_ARGUMENT_FUNCTION_OBJECT, &functionObjectArgument))
						{
							passFunctionDefinitionRequirements = false;
							cout << "NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_ARGUMENTS_NO_OBJECT: passFunctionDefinitionRequirements = false;" << endl;
						}
					}
					#endif
					if(passFunctionDefinitionRequirements)
					{
						foundFunctionDeclarationClassDefinition = true;
						*functionDefinitionClassDefinitionFound = functionDefinitionClassDefinition;
					}
				}
			}
		}
	}
	return foundFunctionDeclarationClassDefinition;
}
#endif

bool NLCclassDefinitionClassClass::eraseFunctionDependencyFromFunctionDependencyList(vector<NLCclassDefinitionFunctionDependency*>* functionDependencyList, const NLCclassDefinitionFunctionDependency* functionDependencyToErase)
{
	bool result = false;
	for(vector<NLCclassDefinitionFunctionDependency*>::iterator iter = functionDependencyList->begin(); iter != functionDependencyList->end(); )
	{
		NLCclassDefinitionFunctionDependency* functionDependency = *iter;
		if(functionDependency == functionDependencyToErase)
		{
			iter = functionDependencyList->erase(iter);
			result = true;
		}
		else
		{
			iter++;
		}
	}
	return result;
}

bool NLCclassDefinitionClassClass::findParentClass(NLCclassDefinition* classDefinition, const string variableName, int inheritanceLevel, int* maxInheritanceLevel, constEffective NLCclassDefinition** parentClass)
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
			NLCclassDefinition* targetClassDefinition = *localListIter;
			if(findParentClass(targetClassDefinition, variableName, (inheritanceLevel+1), maxInheritanceLevel, parentClass))
			{
				foundVariable = true;
			}
		}
	}
	return foundVariable;
}
#endif

//only appropriate for use with functionName/functionObjectName/functionClassName (as not compatible with NLC_LOCAL_LISTS_USE_INSTANCE_NAMES otherwise);
bool NLCclassDefinitionClassClass::findFunctionArgument(vector<NLCitem*>* parameters, const string itemName, const int itemType, constEffective NLCitem** functionArgument)
{
	bool foundFunctionArgument = false;
	for(vector<NLCitem*>::iterator parametersIterator = parameters->begin(); parametersIterator < parameters->end(); parametersIterator++)
	{
		NLCitem* currentItem = *parametersIterator;
		if(currentItem->itemType == itemType)
		{
			#ifdef NLC_ADVANCED_REFERENCING
			if(currentItem->name == itemName)
			#else
			if(currentItem->name == itemName)
			#endif
			{
				*functionArgument = currentItem;
				foundFunctionArgument = true;
			}
		}
	}
	return foundFunctionArgument;
}

bool NLCclassDefinitionClassClass::findFunctionArgument(vector<NLCitem*>* parameters, const NLCitem* item, const int itemType, constEffective NLCitem** functionArgument)
{
	bool foundFunctionArgument = false;
	for(vector<NLCitem*>::iterator parametersIterator = parameters->begin(); parametersIterator < parameters->end(); parametersIterator++)
	{
		NLCitem* currentItem = *parametersIterator;
		if(currentItem->itemType == itemType)
		{
			#ifdef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES
			if(currentItem->instanceName == item->instanceName)
			#else
			if(currentItem->name == item->name)	//or if(currentItem->className == generateClassName(item->name))
			#endif
			{
				*functionArgument = currentItem;
				foundFunctionArgument = true;
			}
		}
	}
	return foundFunctionArgument;
}

bool NLCclassDefinitionClassClass::findFunctionArgument(vector<NLCitem*>* parameters, const int itemType, constEffective NLCitem** functionArgument)
{
	bool foundFunctionArgument = false;
	for(vector<NLCitem*>::iterator parametersIterator = parameters->begin(); parametersIterator < parameters->end(); parametersIterator++)
	{
		NLCitem* currentItem = *parametersIterator;
		if(currentItem->itemType == itemType)
		{
			*functionArgument = currentItem;
			foundFunctionArgument = true;
		}
	}
	return foundFunctionArgument;
}

