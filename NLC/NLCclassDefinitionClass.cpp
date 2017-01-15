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
 * Project Version: 1k12b 17-October-2014
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/




#include "NLCclassDefinitionClass.h"


NLCclassDefinition::NLCclassDefinition(string newName)
{
	name = newName;
	functionNameSpecial = "";

	isActionOrConditionInstanceNotClass = false;
	#ifdef NLC_SUPPORT_INPUT_FILE_LISTS_CHECK_ACTION_SUBJECT_CONTENTS_FOR_IMPLICITLY_DECLARED_PARAMETERS
	actionOrConditionInstance = NULL;
	#endif

	printed = false;
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

#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_BASED_ON_IMPLICITLY_DECLARED_VARIABLES_IN_CURRENT_FUNCTION_DEFINITION
#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_BASED_ON_IMPLICITLY_DECLARED_VARIABLES_IN_CURRENT_FUNCTION_DEFINITION_ADVANCED
bool findFunctionDeclarationClassDefinition(vector<NLCclassDefinition *> * classDefinitionList, string functionName, string functionOwnerName, string functionObjectName, bool hasFunctionOwnerClass, bool hasFunctionObjectClass, NLCclassDefinition ** functionClassDeclarationFound, bool rearrangeClassList, bool * foundFunctionOwnerExactMatch, bool * foundFunctionObjectExactMatch)
{
	bool foundFunctionDeclarationClassDefinition = false;
	
	//reconcile function execution "The animal eats the object."/animal->eat(vector object) with function definition "animal#eat+object"/animal::eat(vector object)	
	bool findFunctionOwnerExactMatch = true;
	bool findFunctionObjectExactMatch = true;
	#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_BASED_ON_IMPLICITLY_DECLARED_VARIABLES_IN_CURRENT_FUNCTION_DEFINITION_ADVANCED
	cout << "findFunctionOwnerExactMatch && findFunctionObjectExactMatch" << endl;
	#endif
	if(findFunctionDeclarationClassDefinition(classDefinitionList, functionName, functionOwnerName, functionObjectName, hasFunctionOwnerClass, hasFunctionObjectClass, findFunctionOwnerExactMatch, findFunctionObjectExactMatch, functionClassDeclarationFound, rearrangeClassList))
	{
		foundFunctionDeclarationClassDefinition = true;
		*foundFunctionOwnerExactMatch = true;
		*foundFunctionObjectExactMatch = true;
		//cout << "\t1" << endl;
	}
	else
	{
		//reconcile function execution "The animal eats the ball."/dog->eat(vector ball) with function definition "animal#eat+object"/animal::eat(vector object)	
		findFunctionOwnerExactMatch = true;
		findFunctionObjectExactMatch = false;
		#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_BASED_ON_IMPLICITLY_DECLARED_VARIABLES_IN_CURRENT_FUNCTION_DEFINITION_ADVANCED
		cout << "findFunctionOwnerExactMatch && !findFunctionObjectExactMatch" << endl;
		#endif
		if(findFunctionDeclarationClassDefinition(classDefinitionList, functionName, functionOwnerName, functionObjectName, hasFunctionOwnerClass, hasFunctionObjectClass, findFunctionOwnerExactMatch, findFunctionObjectExactMatch, functionClassDeclarationFound, rearrangeClassList))
		{
			foundFunctionDeclarationClassDefinition = true;
			*foundFunctionOwnerExactMatch = true;
			*foundFunctionObjectExactMatch = false;
			//cout << "\t2" << endl;
		}
		else
		{
			//reconcile function execution "The dog eats the object."/dog->eat(vector object) with function definition "animal#eat+object"/animal::eat(vector object)	
			findFunctionOwnerExactMatch = false;
			findFunctionObjectExactMatch = true;
			#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_BASED_ON_IMPLICITLY_DECLARED_VARIABLES_IN_CURRENT_FUNCTION_DEFINITION_ADVANCED
			cout << "!findFunctionOwnerExactMatch && findFunctionObjectExactMatch" << endl;
			#endif
			if(findFunctionDeclarationClassDefinition(classDefinitionList, functionName, functionOwnerName, functionObjectName, hasFunctionOwnerClass, hasFunctionObjectClass, findFunctionOwnerExactMatch, findFunctionObjectExactMatch, functionClassDeclarationFound, rearrangeClassList))
			{
				foundFunctionDeclarationClassDefinition = true;
				*foundFunctionOwnerExactMatch = false;
				*foundFunctionObjectExactMatch = true;
				//cout << "\t3" << endl;
			}
			else
			{
				//reconcile function execution "The dog eats the ball."/dog->eat(vector ball) with function definition "animal#eat+object"/animal::eat(vector object)	
				findFunctionOwnerExactMatch = false;
				findFunctionObjectExactMatch = false;
				#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_BASED_ON_IMPLICITLY_DECLARED_VARIABLES_IN_CURRENT_FUNCTION_DEFINITION_ADVANCED
				cout << "!findFunctionOwnerExactMatch && !findFunctionObjectExactMatch" << endl;
				#endif
				if(findFunctionDeclarationClassDefinition(classDefinitionList, functionName, functionOwnerName, functionObjectName, hasFunctionOwnerClass, hasFunctionObjectClass, findFunctionOwnerExactMatch, findFunctionObjectExactMatch, functionClassDeclarationFound, rearrangeClassList))
				{
					foundFunctionDeclarationClassDefinition = true;
					*foundFunctionOwnerExactMatch = false;
					*foundFunctionObjectExactMatch = false;
					//cout << "\t4" << endl;
				}
				else
				{
					#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_BASED_ON_IMPLICITLY_DECLARED_VARIABLES_IN_CURRENT_FUNCTION_DEFINITION_ADVANCED
					cout << "class definition (generated from function execution reference) corresponding to formal function definition not found:" << functionOwnerName << "#" << functionName << "+" << functionObjectName << endl;
					#endif
				}
			}		
		}		
	}
	return foundFunctionDeclarationClassDefinition;
}

bool findFunctionDeclarationClassDefinition(vector<NLCclassDefinition *> * classDefinitionList, string functionName, string functionOwnerName, string functionObjectName, bool hasFunctionOwnerClass, bool hasFunctionObjectClass, bool findFunctionOwnerExactMatch, bool findFunctionObjectExactMatch, NLCclassDefinition ** functionClassDeclarationFound, bool rearrangeClassList)
{
	#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_BASED_ON_IMPLICITLY_DECLARED_VARIABLES_IN_CURRENT_FUNCTION_DEFINITION_ADVANCED
	cout << "findFunctionDeclarationClassDefinition():" << endl;
	cout << "functionName = " << functionName << endl;
	#endif
	bool foundFunctionDeclarationClassDefinition = false;
	NLCclassDefinition * classDefinitionFound = NULL;
	for(vector<NLCclassDefinition*>::iterator classDefinitionIter = classDefinitionList->begin(); classDefinitionIter != classDefinitionList->end(); classDefinitionIter++)
	{
		NLCclassDefinition * currentClassDef = *classDefinitionIter;
		#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_BASED_ON_IMPLICITLY_DECLARED_VARIABLES_IN_CURRENT_FUNCTION_DEFINITION_ADVANCED
		cout << "currentClassDef->name = " << currentClassDef->name << endl;
		#endif
		for(vector<NLCclassDefinition*>::iterator localListIter = currentClassDef->functionList.begin(); localListIter != currentClassDef->functionList.end(); )
		{
			bool removedFunctionClassDefinitionFromChildOwner = false;
			NLCclassDefinition * functionDeclaration = *localListIter;
			#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_BASED_ON_IMPLICITLY_DECLARED_VARIABLES_IN_CURRENT_FUNCTION_DEFINITION_ADVANCED
			cout << "functionDeclaration->name = " << functionDeclaration->name << endl;
			cout << "functionDeclaration->functionNameSpecial = " << functionDeclaration->functionNameSpecial << endl;
			#endif
			if(functionDeclaration->functionNameSpecial == generateFunctionName(functionName))
			{
				NLCclassDefinition * parentFunctionOwnerClassDef = NULL;
				NLCclassDefinition * parentFunctionObjectClassDef = NULL;
				//NLCitem * functionOwnerArgument = NULL;
				NLCitem * functionObjectArgument = NULL;
				bool passFunctionDefinitionRequirements = true;
				#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_BASED_ON_IMPLICITLY_DECLARED_VARIABLES_IN_CURRENT_FUNCTION_DEFINITION_ADVANCED
				cout << "(functionDeclaration->functionNameSpecial == generateFunctionName(functionName)) = " << functionDeclaration->functionNameSpecial << endl;
				#endif
				if(hasFunctionOwnerClass)
				{
					passFunctionDefinitionRequirements = false;
					if(findFunctionOwnerExactMatch)
					{
						if(currentClassDef->name == generateClassName(functionOwnerName))
						{
							#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_BASED_ON_IMPLICITLY_DECLARED_VARIABLES_IN_CURRENT_FUNCTION_DEFINITION_ADVANCED
							cout << "1 (currentClassDef->name == generateClassName(functionOwnerName))" << endl;
							#endif
							passFunctionDefinitionRequirements = true;
						}
					}
					else
					{
						int inheritanceLevel = 0;
						//cout << "\n\nfunctionOwnerName = " << functionOwnerName << endl;
						if(rearrangeClassList)
						{
							if(findParentClass(currentClassDef, generateClassName(functionOwnerName), 0, &inheritanceLevel, &parentFunctionOwnerClassDef))
							{
								if(currentClassDef != parentFunctionOwnerClassDef)
								{
									passFunctionDefinitionRequirements = true;
									#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_BASED_ON_IMPLICITLY_DECLARED_VARIABLES_IN_CURRENT_FUNCTION_DEFINITION_ADVANCED
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
										#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_BASED_ON_IMPLICITLY_DECLARED_VARIABLES_IN_CURRENT_FUNCTION_DEFINITION_ADVANCED
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
				}
				if(hasFunctionObjectClass)
				{
					if(passFunctionDefinitionRequirements)
					{
						passFunctionDefinitionRequirements = false;
						if(findFunctionObjectExactMatch)
						{
							//cout << "findFunctionObjectExactMatch..." << endl;
							//cout << "functionObjectName = " << functionObjectName << endl;
							if(findFunctionArgument(&(functionDeclaration->parameters), functionObjectName, NLC_ITEM_TYPE_FUNCTION_DECLARATION_ARGUMENT_FUNCTION_OBJECT, &functionObjectArgument))	//NB generateClassName(functionObjectName) not required
							{
								passFunctionDefinitionRequirements = true;
								#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_BASED_ON_IMPLICITLY_DECLARED_VARIABLES_IN_CURRENT_FUNCTION_DEFINITION_ADVANCED
								cout << "3 findFunctionArgument(functionDeclaration, functionObjectName, NLC_ITEM_TYPE_FUNCTION_DECLARATION_ARGUMENT_FUNCTION_OBJECT, &functionObjectArgument)" << endl;
								#endif
							}
						}
						else
						{
							//cout << "!findFunctionObjectExactMatch ... " << endl;
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
												#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_BASED_ON_IMPLICITLY_DECLARED_VARIABLES_IN_CURRENT_FUNCTION_DEFINITION_ADVANCED
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
												#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_BASED_ON_IMPLICITLY_DECLARED_VARIABLES_IN_CURRENT_FUNCTION_DEFINITION_ADVANCED
												cout << "4 findParentClass(classDefinitionCorrespondingToFunctionObject, generateClassName(functionObjectName), 0, &inheritanceLevel, &parentFunctionObjectClassDef)" << endl;
												#endif
											}
										}
									}
								}
							}
						}
					}					
				}
				if(passFunctionDefinitionRequirements)
				{
					#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_BASED_ON_IMPLICITLY_DECLARED_VARIABLES_IN_CURRENT_FUNCTION_DEFINITION_ADVANCED
					cout << "passFunctionDefinitionRequirements" << endl;
					#endif
					foundFunctionDeclarationClassDefinition = true;
					*functionClassDeclarationFound = functionDeclaration;
					if(rearrangeClassList)
					{
						if(hasFunctionOwnerClass)
						{
							if(!findFunctionOwnerExactMatch)
							{
								//now update class definitions function declaration arguments based on formal function definition arguments 
								removedFunctionClassDefinitionFromChildOwner = true;
								parentFunctionOwnerClassDef->functionList.push_back(functionDeclaration);
							}
						}
						if(hasFunctionObjectClass)
						{
							if(!findFunctionObjectExactMatch)
							{
								//now update class definitions function declaration arguments based on formal function definition arguments
								functionObjectArgument->name = removeClassTextFromClassDefinitionName(parentFunctionObjectClassDef->name);	//OLD: functionObjectArgument->name = parentFunctionObjectClassDef->name;
								functionObjectArgument->className = parentFunctionObjectClassDef->name;
								/*removed 1k10b - moved to 
								functionObjectArgument->functionArgumentExecutionEntityName = functionObjectArgument->name;
								functionObjectArgument->functionArgumentPassCastRequired = true;
								*/
							}
							functionObjectArgument->functionArgumentCertified = true;	//not currently used
						}
					}
				}
			}
			
			if(removedFunctionClassDefinitionFromChildOwner)
			{
				localListIter = currentClassDef->functionList.erase(localListIter);
			}
			else
			{
				localListIter++;
			}
		}
	}
	#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_BASED_ON_IMPLICITLY_DECLARED_VARIABLES_IN_CURRENT_FUNCTION_DEFINITION_ADVANCED
	cout << "exit foundFunctionDeclarationClassDefinition = " << foundFunctionDeclarationClassDefinition << endl;
	#endif
	return foundFunctionDeclarationClassDefinition;
}
#endif

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
			if(currentItem->name == itemName)
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
