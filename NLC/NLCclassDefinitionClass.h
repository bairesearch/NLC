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
 * File Name: NLCclassDefinitionClass.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2015 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 1p3e 25-June-2015
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/


#ifndef HEADER_NLC_CLASSDEFINITION_CLASS
#define HEADER_NLC_CLASSDEFINITION_CLASS

#include "NLCglobalDefs.h"
#include "NLCitemClass.h"
#include "GIAentityNodeClass.h"
#include "GIAentityConnectionClass.h"

	//progLangEndLine

#ifdef NLC_USE_LIBRARY
	#define FUNCTION_INDEX_LIBRARY_FUNCTION (INT_DEFAULT_VALUE)	//library functions do not have a function index assigned to them	//NO: 999999999
#endif

//#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE
//used to create a dependency tree of functions
class NLCclassDefinitionFunctionDependency
{
public:
	NLCclassDefinitionFunctionDependency(void);
	NLCclassDefinitionFunctionDependency(string newName);
	~NLCclassDefinitionFunctionDependency(void);

	string functionName;
	string functionOwnerName;
	string functionObjectName;
	bool hasFunctionOwnerClass;
	bool hasFunctionObjectClass;
	
	int functionDefinitionListIndex;
	bool reconciledFunctionDeclarationArguments;
	
	#ifdef NLC_CLASS_DEFINITIONS_CREATE_FUNCTION_DECLARATIONS_FOR_NEW_FUNCTION_DEFINITIONS
	bool isReferenceElseFunctionDefinition;
	#endif
	vector<NLCclassDefinitionFunctionDependency* > functionDependencyList;
};
//#endif

class NLCclassDefinition
{
public:

	NLCclassDefinition(void);
	NLCclassDefinition(string newName);
	~NLCclassDefinition(void);

	string name;	//className (or instanceName if isActionOrConditionInstanceNotClass)
	string functionNameSpecial;
	
		//classdefinition sublists;
	vector<NLCclassDefinition* > propertyList;	//subclass
	vector<NLCclassDefinition* > conditionList;	//declared conditions
	vector<NLCclassDefinition* > definitionList;	//inherited parents
	vector<NLCclassDefinition* > functionList;
	#ifdef NLC_RECORD_ACTION_HISTORY
	vector<NLCclassDefinition* > actionList;		//used by action subjects only
	vector<NLCclassDefinition* > actionIncomingList;	//used by action objects only
	vector<NLCclassDefinition* > actionSubjectList;	//used by action class definitions only (these are distinct from invisible function reference class definitions)
	vector<NLCclassDefinition* > actionObjectList;	//used by action class definitions only (these are distinct from invisible function reference class definitions)
	#endif

	bool isActionOrConditionInstanceNotClass;
	bool isConditionInstance;	//added 1m3a

	#ifdef NLC_SUPPORT_INPUT_FUNCTION_LISTS_CHECK_ACTION_SUBJECT_CONTENTS_FOR_IMPLICITLY_DECLARED_PARAMETERS
	GIAentityNode* actionOrConditionInstance;
	#endif
	vector<NLCitem*> parameters;

	bool isDisabledChildReplicantDeclaration;
	
	bool printed;
	
	#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE
	NLCclassDefinitionFunctionDependency* functionDependency;	//for function class definitions only
	#endif
};


NLCclassDefinition* findClassDefinition(vector<NLCclassDefinition*>* classDefinitionList, string name, bool* foundClassDefinition);
NLCclassDefinition* findClassDefinitionCondition(vector<NLCclassDefinition*>* classDefinitionList, GIAentityNode* targetEntity, bool* foundClassDefinition);
bool findFunctionDependencyInList(vector<NLCclassDefinitionFunctionDependency*>* functionDependencyList, string functionName, string functionOwnerName, string functionObjectName, bool hasFunctionOwnerClass, bool hasFunctionObjectClass, NLCclassDefinitionFunctionDependency** functionDependencyFound);
bool findFunctionDefinitionFunctionDependencyInList(vector<NLCclassDefinitionFunctionDependency*>* functionDependencyList, int functionIndex, NLCclassDefinitionFunctionDependency** functionDependencyFound);	
	bool compareFunctionDependency(NLCclassDefinitionFunctionDependency* functionDependency, string functionName, string functionOwnerName, string functionObjectName, bool hasFunctionOwnerClass, bool hasFunctionObjectClass);
#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE
bool findFunctionDependencyInParent(NLCclassDefinitionFunctionDependency* parentFunctionDependency, string functionName, string functionOwnerName, string functionObjectName, bool hasFunctionOwnerClass, bool hasFunctionObjectClass, NLCclassDefinitionFunctionDependency** functionDependencyFound);
#endif

#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS
#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
bool findFunctionDeclarationClassDefinitionExactOrNonExactMatch(vector<NLCclassDefinition*>* classDefinitionList, string functionName, string functionOwnerName, string functionObjectName, bool hasFunctionOwnerClass, bool hasFunctionObjectClass, NLCclassDefinition** functionClassDeclarationFound, bool rearrangeClassList, bool* foundFunctionOwnerExactMatch, bool* foundFunctionObjectExactMatch);
	bool findFunctionDeclarationClassDefinition(vector<NLCclassDefinition*>* classDefinitionList, string functionName, string functionOwnerName, string functionObjectName, bool hasFunctionOwnerClass, bool hasFunctionObjectClass, bool findFunctionOwnerExactMatch, bool findFunctionObjectExactMatch, NLCclassDefinition** functionClassDeclarationFound, bool rearrangeClassList, bool isReferenceElseFunctionDefinition);
		bool eraseFunctionDependencyFromFunctionDependencyList(vector<NLCclassDefinitionFunctionDependency*>* functionDependencyList, NLCclassDefinitionFunctionDependency* functionDependencyToErase);
#endif
bool findParentClass(NLCclassDefinition* classDefinition, string variableName, int inheritanceLevel, int* maxInheritanceLevel, NLCclassDefinition** parentClass);	
#endif
//see NLCcodeBlocks.cpp for other versions of this function;
bool findFunctionArgument(vector<NLCitem*>* parameters, string itemName, int itemType, NLCitem** functionArgument);
bool findFunctionArgument(vector<NLCitem*>* parameters, NLCitem* item, int itemType, NLCitem** functionArgument);
bool findFunctionArgument(vector<NLCitem*>* parameters, int itemType, NLCitem** functionArgument);



#endif
