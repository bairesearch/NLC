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
 * File Name: NLCclassDefinitionClass.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2014 Baxter AI (baxterai.com)
 * Project: Natural Language Programming Interface (compiler)
 * Project Version: 1k16e 24-October-2014
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/




#include "NLCclassDefinitionClass.h"


//#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE
NLCclassDefinitionFunctionDependency::NLCclassDefinitionFunctionDependency(void)
{	
	functionName = "";
	functionOwnerName = "";
	functionObjectName = "";
	hasFunctionOwnerClass = false;
	hasFunctionObjectClass = false;
	
	functionNameListIndex = INT_DEFAULT_VALUE;
	reconciledFunctionDeclarationArguments = false;
	
	#ifdef NLC_CLASS_DEFINITIONS_CREATE_FUNCTION_DECLARATIONS_FOR_NEW_FUNCTION_DEFINITIONS
	isReference = false;
	#endif
}
NLCclassDefinitionFunctionDependency::~NLCclassDefinitionFunctionDependency(void)
{
}
//#endif


NLCclassDefinition::NLCclassDefinition(string newName)
{
	name = newName;
	functionNameSpecial = "";

	isActionOrConditionInstanceNotClass = false;
	#ifdef NLC_SUPPORT_INPUT_FILE_LISTS_CHECK_ACTION_SUBJECT_CONTENTS_FOR_IMPLICITLY_DECLARED_PARAMETERS
	actionOrConditionInstance = NULL;
	#endif

	printed = false;
	
	#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE
	functionDependency = NULL;	//for function class definitions only
	#endif
}
NLCclassDefinition::NLCclassDefinition(void)
{
	name = "";
	functionNameSpecial = "";

	isActionOrConditionInstanceNotClass = false;
	#ifdef NLC_SUPPORT_INPUT_FILE_LISTS_CHECK_ACTION_SUBJECT_CONTENTS_FOR_IMPLICITLY_DECLARED_PARAMETERS
	actionOrConditionInstance = NULL;
	#endif

	printed = false;
	
	#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE
	functionDependency = NULL;	//for function class definitions only
	#endif
}
NLCclassDefinition::~NLCclassDefinition(void)
{
}


/*
bool checkSentenceIndexParsingClassHeirarchy(GIAentityNode * entity, int sentenceIndex)
{
	bool result = false;
	if(((entity->sentenceIndexTemp == sentenceIndex) || (entity->wasReference)) && !(entity->parsedForNLCclassHeirarchy))
	{
		result = true;
	}
	return result;
}
*/

NLCclassDefinition * findClassDefinition(vector<NLCclassDefinition *> * classDefinitionList, string name, bool * foundClassDefinition)
{
	NLCclassDefinition * classDefinitionFound = NULL;
	for(vector<NLCclassDefinition*>::iterator classDefinitionIter = classDefinitionList->begin(); classDefinitionIter != classDefinitionList->end(); classDefinitionIter++)
	{
		NLCclassDefinition *  currentClassDef = *classDefinitionIter;
		if(currentClassDef->name == name)
		{
			//cout << "foundClassDefinition: className = " << currentClassDef->name << endl;
			classDefinitionFound = currentClassDef;
			*foundClassDefinition = true;
		}
	}
	return classDefinitionFound;
}

bool findFunctionDependencyInList(vector<NLCclassDefinitionFunctionDependency*> * functionDependencyList, string functionName, string functionOwnerName, string functionObjectName, bool hasFunctionOwnerClass, bool hasFunctionObjectClass, NLCclassDefinitionFunctionDependency ** functionDependencyFound)
{
	bool foundFunctionDependency = false;
	for(vector<NLCclassDefinitionFunctionDependency*>::iterator functionDependencyIter = functionDependencyList->begin(); functionDependencyIter != functionDependencyList->end(); functionDependencyIter++)
	{
		NLCclassDefinitionFunctionDependency * functionDependency = *functionDependencyIter;
		if(compareFunctionDependency(functionDependency, functionName, functionOwnerName, functionObjectName, hasFunctionOwnerClass, hasFunctionObjectClass))
		{
			//cout << "foundFunctionDependency: functionName = " << functionName << endl;
			*functionDependencyFound = functionDependency;
			foundFunctionDependency = true;
		}
	}
	return foundFunctionDependency;
}

bool findFunctionDependencyInList(vector<NLCclassDefinitionFunctionDependency*> * functionDependencyList, int functionIndex, NLCclassDefinitionFunctionDependency ** functionDependencyFound)
{
	bool foundFunctionDependency = false;
	for(vector<NLCclassDefinitionFunctionDependency*>::iterator functionDependencyIter = functionDependencyList->begin(); functionDependencyIter != functionDependencyList->end(); functionDependencyIter++)
	{
		NLCclassDefinitionFunctionDependency * functionDependency = *functionDependencyIter;
		if(functionDependency->functionNameListIndex == functionIndex)
		{ 
			//cout << "foundFunctionDependency: functionName = " << functionName << endl;
			*functionDependencyFound = functionDependency;
			foundFunctionDependency = true;
		}
	}
	return foundFunctionDependency;
}
			
bool compareFunctionDependency(NLCclassDefinitionFunctionDependency * functionDependency, string functionName, string functionOwnerName, string functionObjectName, bool hasFunctionOwnerClass, bool hasFunctionObjectClass)
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

#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE

bool findFunctionDependencyInParent(NLCclassDefinitionFunctionDependency * parentFunctionDependency, string functionName, string functionOwnerName, string functionObjectName, bool hasFunctionOwnerClass, bool hasFunctionObjectClass, NLCclassDefinitionFunctionDependency ** functionDependencyFound)
{
	bool foundFunctionDependency = false;
	for(vector<NLCclassDefinitionFunctionDependency*>::iterator functionDependencyIter = parentFunctionDependency->functionDependencyList.begin(); functionDependencyIter != parentFunctionDependency->functionDependencyList.end(); functionDependencyIter++)
	{
		NLCclassDefinitionFunctionDependency * functionDependency = *functionDependencyIter;
		if(compareFunctionDependency(functionDependency, functionName, functionOwnerName, functionObjectName, hasFunctionOwnerClass, hasFunctionObjectClass))
		{
			//cout << "foundFunctionDependency: functionName = " << functionName << endl;
			*functionDependencyFound = functionDependency;
			foundFunctionDependency = true;
		}
	}
	return foundFunctionDependency;
}

/*
bool findFunctionDependencyInClassDefinitionList(vector<NLCclassDefinition *> * classDefinitionList, string functionName, string functionOwnerName, string functionObjectName, bool hasFunctionOwnerClass, bool hasFunctionObjectClass, NLCclassDefinitionFunctionDependency ** functionDependencyFound)
{
	bool foundFunctionDependency = false;
	if(hasFunctionOwnerClass)	//if !hasFunctionOwnerClass, functionDependency is not part of class definition list and are declared independently
	{
		for(vector<NLCclassDefinition*>::iterator classDefinitionIter = classDefinitionList->begin(); classDefinitionIter != classDefinitionList->end(); classDefinitionIter++)
		{
			NLCclassDefinition *  currentClassDef = *classDefinitionIter;
			if(currentClassDef->name == generateClassName(functionOwnerName))	//not necessary as this test is handled by compareFunctionDependency()
			{
				for(vector<NLCclassDefinition*>::iterator localListIter = currentClassDef->functionList.begin(); localListIter != currentClassDef->functionList.end(); localListIter++)
				{
					NLCclassDefinition * currentClassDefFunctionReference = *localListIter;
					if(compareFunctionDependency(currentClassDefFunctionReference->functionDependencies, functionName, functionOwnerName, functionObjectName, hasFunctionOwnerClass, hasFunctionObjectClass))
					{
						//cout << "foundFunctionDependency: functionName = " << functionName << endl;
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
bool findFunctionDeclarationClassDefinitionExactOrNonExactMatch(vector<NLCclassDefinition *> * classDefinitionList, string functionName, string functionOwnerName, string functionObjectName, bool hasFunctionOwnerClass, bool hasFunctionObjectClass, NLCclassDefinition ** functionClassDeclarationFound, bool rearrangeClassList, bool * foundFunctionOwnerExactMatch, bool * foundFunctionObjectExactMatch)
{
	#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
	//cout << "888888888888888888888888888888888888888888888888888888888888888" << endl;
	cout << "findFunctionDeclarationClassDefinitionExactOrNonExactMatch(): " << endl;
	cout << "functionName = " << functionName << endl;
	cout << "functionOwnerName = " << functionOwnerName << endl;
	cout << "functionObjectName = " << functionObjectName << endl;
	#endif
	bool foundFunctionDeclarationClassDefinition = false;
	
	bool isReference = false;	
	bool findFunctionOwnerExactMatch;
	bool findFunctionObjectExactMatch;
		
	//reconcile function execution "The animal eats the object."/animal->eat(vector object) with function definition "animal#eat+object"/animal::eat(vector object)	
	findFunctionOwnerExactMatch = true;
	findFunctionObjectExactMatch = true;
	#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
	cout << "start: findFunctionOwnerExactMatch && findFunctionObjectExactMatch" << endl;
	#endif
	if(findFunctionDeclarationClassDefinition(classDefinitionList, functionName, functionOwnerName, functionObjectName, hasFunctionOwnerClass, hasFunctionObjectClass, findFunctionOwnerExactMatch, findFunctionObjectExactMatch, functionClassDeclarationFound, rearrangeClassList, isReference))
	{
		foundFunctionDeclarationClassDefinition = true;
		*foundFunctionOwnerExactMatch = true;
		*foundFunctionObjectExactMatch = true;
		#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
		cout << "passed findFunctionOwnerExactMatch && findFunctionObjectExactMatch" << endl;
		#endif
	}
	else
	{
		//reconcile function execution "The animal eats the ball."/dog->eat(vector ball) with function definition "animal#eat+object"/animal::eat(vector object)
		findFunctionOwnerExactMatch = true;
		findFunctionObjectExactMatch = false;
		#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
		cout << "start: findFunctionOwnerExactMatch && !findFunctionObjectExactMatch" << endl;
		#endif
		if(findFunctionDeclarationClassDefinition(classDefinitionList, functionName, functionOwnerName, functionObjectName, hasFunctionOwnerClass, hasFunctionObjectClass, findFunctionOwnerExactMatch, findFunctionObjectExactMatch, functionClassDeclarationFound, rearrangeClassList, isReference))
		{
			foundFunctionDeclarationClassDefinition = true;
			*foundFunctionOwnerExactMatch = true;
			*foundFunctionObjectExactMatch = false;
			#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
			cout << "passed: findFunctionOwnerExactMatch && !findFunctionObjectExactMatch" << endl;
			#endif
		}
		else
		{
			//reconcile function execution "The dog eats the object."/dog->eat(vector object) with function definition "animal#eat+object"/animal::eat(vector object)
			findFunctionOwnerExactMatch = false;
			findFunctionObjectExactMatch = true;
			#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
			cout << "start: !findFunctionOwnerExactMatch && findFunctionObjectExactMatch" << endl;
			#endif
			if(findFunctionDeclarationClassDefinition(classDefinitionList, functionName, functionOwnerName, functionObjectName, hasFunctionOwnerClass, hasFunctionObjectClass, findFunctionOwnerExactMatch, findFunctionObjectExactMatch, functionClassDeclarationFound, rearrangeClassList, isReference))
			{
				foundFunctionDeclarationClassDefinition = true;
				*foundFunctionOwnerExactMatch = false;
				*foundFunctionObjectExactMatch = true;
				#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
				cout << "passed: !findFunctionOwnerExactMatch && findFunctionObjectExactMatch" << endl;
				#endif
			}
			else
			{
				//reconcile function execution "The dog eats the ball."/dog->eat(vector ball) with function definition "animal#eat+object"/animal::eat(vector object)
				findFunctionOwnerExactMatch = false;
				findFunctionObjectExactMatch = false;
				#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
				cout << "start: !findFunctionOwnerExactMatch && !findFunctionObjectExactMatch" << endl;
				#endif
				if(findFunctionDeclarationClassDefinition(classDefinitionList, functionName, functionOwnerName, functionObjectName, hasFunctionOwnerClass, hasFunctionObjectClass, findFunctionOwnerExactMatch, findFunctionObjectExactMatch, functionClassDeclarationFound, rearrangeClassList, isReference))
				{
					foundFunctionDeclarationClassDefinition = true;
					*foundFunctionOwnerExactMatch = false;
					*foundFunctionObjectExactMatch = false;
					#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
					cout << "passed !findFunctionOwnerExactMatch && !findFunctionObjectExactMatch" << endl;
					#endif
				}
			}		
		}		
	}
	return foundFunctionDeclarationClassDefinition;
}

bool findFunctionDeclarationClassDefinition(vector<NLCclassDefinition *> * classDefinitionList, string functionName, string functionOwnerName, string functionObjectName, bool hasFunctionOwnerClass, bool hasFunctionObjectClass, bool findFunctionOwnerExactMatch, bool findFunctionObjectExactMatch, NLCclassDefinition ** functionClassDeclarationFound, bool rearrangeClassList, bool isReference)
{
	#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
	cout << "findFunctionDeclarationClassDefinition():" << endl;
	cout << "functionName = " << functionName << endl;
	#endif
	bool foundFunctionDeclarationClassDefinition = false;
	NLCclassDefinition * classDefinitionFound = NULL;
	for(vector<NLCclassDefinition*>::iterator classDefinitionIter = classDefinitionList->begin(); classDefinitionIter != classDefinitionList->end(); classDefinitionIter++)
	{
		NLCclassDefinition * currentClassDef = *classDefinitionIter;
		#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
		cout << "currentClassDef->name = " << currentClassDef->name << endl;
		#endif
		for(vector<NLCclassDefinition*>::iterator localListIter = currentClassDef->functionList.begin(); localListIter != currentClassDef->functionList.end(); localListIter++)
		{
			NLCclassDefinition * functionDeclaration = *localListIter;
			#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
			cout << "functionDeclaration->functionNameSpecial = " << functionDeclaration->functionNameSpecial << endl;
			#endif
			if(functionDeclaration->functionNameSpecial == generateFunctionName(functionName))
			{
				#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
				cout << "(functionDeclaration->functionNameSpecial == generateFunctionName(functionName))" << endl;
				#endif
				#ifdef NLC_CLASS_DEFINITIONS_CREATE_FUNCTION_DECLARATIONS_FOR_NEW_FUNCTION_DEFINITIONS
				if(functionDeclaration->functionDependency->isReference == isReference)
				{
					#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
					cout << "functionDeclaration->functionDependency->isReference = " << functionDeclaration->functionDependency->isReference << endl;
					#endif
				#endif
					NLCclassDefinition * parentFunctionOwnerClassDef = NULL;
					NLCclassDefinition * parentFunctionObjectClassDef = NULL;
					//NLCitem * functionOwnerArgument = NULL;
					NLCitem * functionObjectArgument = NULL;
					bool passFunctionDefinitionRequirements = true;
					#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
					//cout << "(functionDeclaration->functionNameSpecial == generateFunctionName(functionName)) = " << functionDeclaration->functionNameSpecial << endl;
					#endif
					if(hasFunctionOwnerClass)
					{
						passFunctionDefinitionRequirements = false;
						if(findFunctionOwnerExactMatch)
						{
							if(currentClassDef->name == generateClassName(functionOwnerName))
							{
								#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
								cout << "1 (currentClassDef->name == generateClassName(functionOwnerName))" << endl;
								#endif
								passFunctionDefinitionRequirements = true;
							}
						}
						#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ACCEPT_NON_EXACT_MATCH_SUBJECT
						else
						{
							int inheritanceLevel = 0;
							#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
							cout << "functionOwnerName = " << functionOwnerName << endl;
							#endif
							if(rearrangeClassList)
							{
								//cout << "k1" << endl;
								if(findParentClass(currentClassDef, generateClassName(functionOwnerName), 0, &inheritanceLevel, &parentFunctionOwnerClassDef))
								{
									//cout << "k2" << endl;
									if(currentClassDef != parentFunctionOwnerClassDef)
									{
										passFunctionDefinitionRequirements = true;
										#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
										cout << "2 findParentClass(currentClassDef, generateClassName(functionOwnerName), 0, &inheritanceLevel, &parentFunctionOwnerClassDef)" << endl;
										#endif
										/*
										if(!findFunctionArgument(&(functionDeclaration->parameters), NLC_ITEM_TYPE_FUNCTION_DECLARATION_ARGUMENT_FUNCTION_OWNER, &functionOwnerArgument))
										{
											cout << "findFunctionDeclarationClassDefinition() error: !findFunctionArgument NLC_ITEM_TYPE_FUNCTION_DECLARATION_ARGUMENT_FUNCTION_OWNER" << endl;
										}
										*/
									}
								}
							}
							else
							{
								//cout << "!findFunctionOwnerExactMatch ... " << endl;
								//cout << "k1" << endl;
								bool foundClassDefinitionCorrespondingToFunctionOwner = false;
								NLCclassDefinition * classDefinitionCorrespondingToFunctionOwner = findClassDefinition(classDefinitionList, generateClassName(functionOwnerName), &foundClassDefinitionCorrespondingToFunctionOwner);

								if(foundClassDefinitionCorrespondingToFunctionOwner)
								{
									//cout << "k2" << endl;
									//cout << "currentClassDef->name (function declaration subject) = " << currentClassDef->name << endl;
									//cout << "classDefinitionCorrespondingToFunctionOwner->name = " << classDefinitionCorrespondingToFunctionOwner->name << endl;
									if(findParentClass(classDefinitionCorrespondingToFunctionOwner, currentClassDef->name, 0, &inheritanceLevel, &parentFunctionOwnerClassDef))
									{
										//cout << "k3" << endl;
										if(classDefinitionCorrespondingToFunctionOwner != parentFunctionOwnerClassDef)
										{
											passFunctionDefinitionRequirements = true;
											#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
											cout << "2 findParentClass(currentClassDef, generateClassName(functionOwnerName), 0, &inheritanceLevel, &parentFunctionOwnerClassDef)" << endl;
											#endif
											/*
											if(!findFunctionArgument(&(functionDeclaration->parameters), NLC_ITEM_TYPE_FUNCTION_DECLARATION_ARGUMENT_FUNCTION_OWNER, &functionOwnerArgument))
											{
												cout << "findFunctionDeclarationClassDefinition() error: !findFunctionArgument NLC_ITEM_TYPE_FUNCTION_DECLARATION_ARGUMENT_FUNCTION_OWNER" << endl;
											}
											*/
										}
									}
								}
							}
						}
						#endif
					}
					#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_ARGUMENTS_NO_SUBJECT
					else
					{
						if(currentClassDef->name != generateClassName(NLC_CLASS_DEFINITIONS_SUPPORT_FUNCTIONS_WITHOUT_SUBJECT_ARTIFICIAL_CLASS_NAME))
						{
							passFunctionDefinitionRequirements = false;
							#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
							cout << "NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_ARGUMENTS_NO_SUBJECT: passFunctionDefinitionRequirements = false;" << endl;
							#endif
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
								#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
								cout << "findFunctionObjectExactMatch..." << endl;
								cout << "functionObjectName = " << functionObjectName << endl;
								#endif
								if(findFunctionArgument(&(functionDeclaration->parameters), functionObjectName, NLC_ITEM_TYPE_FUNCTION_DECLARATION_ARGUMENT_FUNCTION_OBJECT, &functionObjectArgument))	//NB generateClassName(functionObjectName) not required
								{
									passFunctionDefinitionRequirements = true;
									#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
									cout << "3 findFunctionArgument(functionDeclaration, functionObjectName, NLC_ITEM_TYPE_FUNCTION_DECLARATION_ARGUMENT_FUNCTION_OBJECT, &functionObjectArgument)" << endl;
									#endif
								}
							}
							#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ACCEPT_NON_EXACT_MATCH_OBJECT
							else
							{
								#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
								cout << "!findFunctionObjectExactMatch ... " << endl;
								#endif
								if(findFunctionArgument(&(functionDeclaration->parameters), NLC_ITEM_TYPE_FUNCTION_DECLARATION_ARGUMENT_FUNCTION_OBJECT, &functionObjectArgument))
								{
									//cout << "k1" << endl;
									//cout << "functionObjectArgument->name = " << functionObjectArgument->name << endl;
									if(rearrangeClassList)
									{
										bool foundClassDefinitionCorrespondingToFunctionObject = false;
										NLCclassDefinition * classDefinitionCorrespondingToFunctionObject = findClassDefinition(classDefinitionList, generateClassName(functionObjectArgument->name), &foundClassDefinitionCorrespondingToFunctionObject);

										if(foundClassDefinitionCorrespondingToFunctionObject)
										{
											//cout << "k2" << endl;
											int inheritanceLevel = 0;
											//cout << "classDefinitionCorrespondingToFunctionObject->name = " << classDefinitionCorrespondingToFunctionObject->name << endl;
											//cout << "functionObjectArgument->className = " << functionObjectArgument->className << endl;
											if(findParentClass(classDefinitionCorrespondingToFunctionObject, generateClassName(functionObjectName), 0, &inheritanceLevel, &parentFunctionObjectClassDef))
											{
												//cout << "k3" << endl;
												if(classDefinitionCorrespondingToFunctionObject != parentFunctionObjectClassDef)
												{
													passFunctionDefinitionRequirements = true;
													#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
													cout << "4 findParentClass(classDefinitionCorrespondingToFunctionObject, generateClassName(functionObjectName), 0, &inheritanceLevel, &parentFunctionObjectClassDef)" << endl;
													#endif
												}
											}
										}
									}
									else
									{
										bool foundClassDefinitionCorrespondingToFunctionObject = false;
										NLCclassDefinition * classDefinitionCorrespondingToFunctionObject = findClassDefinition(classDefinitionList, generateClassName(functionObjectName), &foundClassDefinitionCorrespondingToFunctionObject);

										if(foundClassDefinitionCorrespondingToFunctionObject)
										{
											//cout << "k2" << endl;
											int inheritanceLevel = 0;
											//cout << "classDefinitionCorrespondingToFunctionObject->name = " << classDefinitionCorrespondingToFunctionObject->name << endl;
											//cout << "functionObjectArgument->className = " << functionObjectArgument->className << endl;
											if(findParentClass(classDefinitionCorrespondingToFunctionObject, generateClassName(functionObjectArgument->name), 0, &inheritanceLevel, &parentFunctionObjectClassDef))
											{
												//cout << "k3" << endl;
												if(classDefinitionCorrespondingToFunctionObject != parentFunctionObjectClassDef)
												{
													passFunctionDefinitionRequirements = true;
													#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
													cout << "4 findParentClass(classDefinitionCorrespondingToFunctionObject, generateClassName(functionObjectName), 0, &inheritanceLevel, &parentFunctionObjectClassDef)" << endl;
													#endif
												}
											}
										}
									}
								}
							}
							#endif
						}					
					}
					#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_ARGUMENTS_NO_OBJECT
					else
					{
						if(findFunctionArgument(&(functionDeclaration->parameters), NLC_ITEM_TYPE_FUNCTION_DECLARATION_ARGUMENT_FUNCTION_OBJECT, &functionObjectArgument))
						{
							passFunctionDefinitionRequirements = false;
							cout << "NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_ARGUMENTS_NO_OBJECT: passFunctionDefinitionRequirements = false;" << endl;
						}	
					}
					#endif
					if(passFunctionDefinitionRequirements)
					{
						#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
						cout << "passFunctionDefinitionRequirements" << endl;
						#endif
						foundFunctionDeclarationClassDefinition = true;
						*functionClassDeclarationFound = functionDeclaration;
					}
				#ifdef NLC_CLASS_DEFINITIONS_CREATE_FUNCTION_DECLARATIONS_FOR_NEW_FUNCTION_DEFINITIONS
				}
				#endif
			}
		}
	}
	#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
	cout << "exit foundFunctionDeclarationClassDefinition = " << foundFunctionDeclarationClassDefinition << endl;
	#endif
	return foundFunctionDeclarationClassDefinition;
}
#endif

bool eraseFunctionDependencyFromFunctionDependencyList(vector<NLCclassDefinitionFunctionDependency*> * functionDependencyList, NLCclassDefinitionFunctionDependency * functionDependencyToErase)
{
	bool result = false;
	for(vector<NLCclassDefinitionFunctionDependency*>::iterator iter = functionDependencyList->begin(); iter != functionDependencyList->end(); )
	{
		NLCclassDefinitionFunctionDependency * functionDependency = *iter;
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
		
bool findParentClass(NLCclassDefinition * classDefinition, string variableName, int inheritanceLevel, int * maxInheritanceLevel, NLCclassDefinition ** parentClass)
{
	//cout << "findParentClass: variableName = " << variableName << endl;
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
			NLCclassDefinition * targetClassDefinition = *localListIter;
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
bool findFunctionArgument(vector<NLCitem*> * parameters, string itemName, int itemType, NLCitem ** functionArgument)
{
	bool foundFunctionArgument = false;
	for(vector<NLCitem*>::iterator parametersIterator = parameters->begin(); parametersIterator < parameters->end(); parametersIterator++)
	{
		NLCitem * currentItem = *parametersIterator;
		//cout << "currentItem->itemType = " << currentItem->itemType << endl;
		if(currentItem->itemType == itemType)
		{
			//cout << "(currentItem->itemType == itemType)" << endl;
			#ifdef NLC_USE_ADVANCED_REFERENCING
			if(currentItem->name == itemName)
			#else
			if(currentItem->name == itemName)
			#endif
			{
				//cout << "(currentItem->name)" << endl;
				*functionArgument = currentItem;
				foundFunctionArgument = true;	
			}
		}
	}
	return foundFunctionArgument;
}

bool findFunctionArgument(vector<NLCitem*> * parameters, NLCitem * item, int itemType, NLCitem ** functionArgument)
{
	bool foundFunctionArgument = false;
	for(vector<NLCitem*>::iterator parametersIterator = parameters->begin(); parametersIterator < parameters->end(); parametersIterator++)
	{
		NLCitem * currentItem = *parametersIterator;
		//cout << "currentItem->itemType = " << currentItem->itemType << endl;
		if(currentItem->itemType == itemType)
		{
			//cout << "(currentItem->itemType == itemType)" << endl;
			#ifdef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES
			if(currentItem->instanceName == item->instanceName)
			#else
			if(currentItem->name == item->name)	//or if(currentItem->className == generateClassName(item->name))
			#endif
			{
				//cout << "(currentItem->name)" << endl;
				*functionArgument = currentItem;
				foundFunctionArgument = true;	
			}
		}
	}
	return foundFunctionArgument;
}

bool findFunctionArgument(vector<NLCitem*> * parameters, int itemType, NLCitem ** functionArgument)
{
	bool foundFunctionArgument = false;
	for(vector<NLCitem*>::iterator parametersIterator = parameters->begin(); parametersIterator < parameters->end(); parametersIterator++)
	{
		NLCitem * currentItem = *parametersIterator;
		//cout << "currentItem->itemType = " << currentItem->itemType << endl;
		if(currentItem->itemType == itemType)
		{
			*functionArgument = currentItem;
			foundFunctionArgument = true;
		}
	}
	return foundFunctionArgument;
}

