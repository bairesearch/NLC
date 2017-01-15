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
 * File Name: NLCtranslator.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2014 Baxter AI (baxterai.com)
 * Project: Natural Language Programming Interface (compiler)
 * Project Version: 1l8g 04-November-2014
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/


#ifndef HEADER_NLC_TRANSLATOR
#define HEADER_NLC_TRANSLATOR

#include <iostream>
#include <fstream>
#include <ctime>
#include <cstring>
#include <cstdlib>	//for random number generation
#include <cmath>
#include <string>
#include <vector>
using namespace std;

#include "GIAentityNodeClass.h"
#include "GIAentityConnectionClass.h"
#include "NLCglobalDefs.h"
#include "NLCcodeBlockClass.h"
#include "NLCclassDefinitionClass.h"
//#ifdef NLC_USE_PREPROCESSOR
#include "NLCpreprocessorSentenceClass.h"	//required for NLCfunction
//#endif

#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS_ADVANCED
class NLClogicalConditionConjunctionContainer
{
public:

	NLClogicalConditionConjunctionContainer(void);
	NLClogicalConditionConjunctionContainer(GIAentityNode * entity);
	~NLClogicalConditionConjunctionContainer(void);

	GIAentityNode * entity;
	vector<NLClogicalConditionConjunctionContainer*> nextConditionConjunctions;
	int optimumPathIndex;
};
#endif

bool translateNetwork(NLCcodeblock * firstCodeBlockInTree, vector<NLCclassDefinition *> * classDefinitionList, vector<GIAentityNode*> * entityNodesActiveListComplete, int maxNumberSentences, string NLCfunctionName, NLCfunction * currentNLCfunctionInList, bool useNLCpreprocessor, NLCclassDefinitionFunctionDependency * functionDependency, vector<NLCclassDefinitionFunctionDependency*> * functionDependencyList);
	/*
	#ifdef NLC_CATEGORIES_TEST_PLURALITY_ENFORCE
	#ifdef NLC_USE_PREPROCESSOR
	bool identifyImplicitPluralLogicalConditionOperationsObjects(vector<GIAentityNode*> * entityNodesActiveListComplete, int maxNumberSentences);
	#endif
	#endif	
	*/
	#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
	#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS_ADVANCED
	bool removeRedundantConditionConjunctions(vector<GIAentityNode*> * entityNodesActiveListComplete, int maxNumberSentences);
		int addConjunctionsConnectedToConditionConjunctionObject(GIAentityNode * conditionEntity, NLClogicalConditionConjunctionContainer * logicalConditionConjunctionContainer, int sentenceIndex);
		bool traceConditionConjunctionsOptimiumPathAndSeeIfConditionConjunctionEntityIsOnIt(NLClogicalConditionConjunctionContainer * logicalConditionConjunctionContainer, GIAentityNode * logicalConditionConjunctionToTest);
	#endif
	bool identifyAndTagAllLogicalConditionOperations(vector<GIAentityNode*> * entityNodesActiveListComplete, int maxNumberSentences);
	#endif
	/*
	#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE
	bool addFunctionDependenciesWithoutOwners(vector<GIAentityNode*> * entityNodesActiveListComplete, int maxNumberSentences, NLCclassDefinitionFunctionDependency * parentFunctionDependencies, vector<NLCclassDefinitionFunctionDependency*> * functionDependencyList);
	#endif
	*/

#ifdef NLC_SUPPORT_INPUT_FILE_LISTS
#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS
void reconcileClassDefinitionListFunctionDeclarationArgumentsBasedOnImplicitlyDeclaredVariablesInCurrentFunctionDefinition(NLCcodeblock * firstCodeBlockInTree, vector<NLCclassDefinition *> * classDefinitionList, NLCclassDefinitionFunctionDependency * functionDependency);
	#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_BASED_ON_IMPLICITLY_DECLARED_VARIABLES_IN_CURRENT_FUNCTION_DEFINITION
	#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
	void addImplicitlyDeclaredVariablesInCurrentFunctionDefinitionToFunctionDeclaration(vector<NLCitem*> * functionDefinitionSourceArgumentList, NLCclassDefinition * functionDeclaration);
	#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE
	void addImplicitlyDeclaredVariablesInCurrentFunctionDeclarationToFunctionDeclaration(NLCclassDefinition * functionDeclarationSource, NLCclassDefinition * functionDeclaration);
	void addImplicitlyDeclaredVariablesInCurrentFunctionDeclarationToFunctionDefinition(NLCclassDefinition * functionDeclarationSource, vector<NLCitem*> * functionDefinitionArgumentList);
	#endif
	#else
	//bool findFormalFunctionArgumentCorrelateInExistingList(NLCclassDefinition * functionClassDefinition, vector<NLCitem*> * formalFunctionArgumentList, vector<NLCclassDefinition *> * classDefinitionList);
	#endif	
	#endif
#endif
bool getFilesFromFileList2(string inputListFileName, vector<string> * inputTextFileNameList, int * numberOfInputFilesInList);
#endif
#ifdef NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_SUPPORT_ALPHANUMERIC_ENTITY_NAMES_ONLY
bool checkAlphaNumericEntityNames(vector<GIAentityNode*> * entityNodesActiveListComplete, int maxNumberSentences);
#endif

NLCclassDefinitionFunctionDependency * createFunctionDependencyForNewFunctionDefinition(string NLCfunctionName, vector<NLCclassDefinition *> * classDefinitionList, vector<NLCclassDefinitionFunctionDependency*> * functionDependencyList, int functionIndex);
	NLCclassDefinitionFunctionDependency * createNewClassDefinitionFunctionDeclaration(vector<NLCclassDefinition *> * classDefinitionList, string functionName, string functionOwnerName, string functionObjectName, bool hasFunctionOwnerClass, bool hasFunctionObjectClass, string functionClassDefinitionName, string functionOwnerClassDefinitionName, bool hasParent, NLCclassDefinitionFunctionDependency * parentFunctionDependency, vector<NLCclassDefinitionFunctionDependency*> * functionDependencyList, bool isReference, bool createClassDefinition);


#endif
