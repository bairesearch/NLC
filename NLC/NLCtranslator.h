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
 * Project Version: 1g15b 16-July-2014
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/


#ifndef HEADER_NLC_TRANSLATOR
#define HEADER_NLC_TRANSLATOR

//#define NLC_NOT_NECESSARY

#include <iostream>
#include <fstream>
#include <ctime>
#include <cstring>
#include <cstdlib>	//for random number generation
#include <cmath>
#include <string>
#include <vector>
using namespace std;

#include "GIAglobalDefs.h"
#include "GIAentityNodeClass.h"
#include "GIAentityConnectionClass.h"
#include "NLCglobalDefs.h"
#include "NLCcodeBlockClass.h"
#include "NLCclassDefinitionClass.h"

#ifdef NLC_LOGICAL_CONDITIONS_SUPPORT_CONJUNCTIONS
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

bool translateNetwork(NLCcodeblock * firstCodeBlockInTree, vector<NLCclassDefinition *> * classDefinitionList, vector<GIAentityNode*> * entityNodesActiveListComplete, int maxNumberSentences, string NLCfunctionName);
	#ifdef NLC_LOGICAL_CONDITIONS_SUPPORT_CONJUNCTIONS
	bool removeRedundantConditionConjunctions(vector<GIAentityNode*> * entityNodesActiveListComplete, int maxNumberSentences);
		int addConjunctionsConnectedToConditionConjunctionObject(GIAentityNode * conditionEntity, NLClogicalConditionConjunctionContainer * logicalConditionConjunctionContainer, int sentenceIndex);
		bool traceConditionConjunctionsOptimiumPathAndSeeIfConditionConjunctionEntityIsOnIt(NLClogicalConditionConjunctionContainer * logicalConditionConjunctionContainer, GIAentityNode * logicalConditionConjunctionToTest);
	#endif
	#ifdef NLC_SUPPORT_CONDITION_LOGICAL_OPERATIONS
	bool identifyAndTagAllLogicalConditionOperations(vector<GIAentityNode*> * entityNodesActiveListComplete, int maxNumberSentences);
	#endif


#ifdef NLC_SUPPORT_INPUT_FILE_LISTS
void reconcileClassDefinitionListFunctionArgumentsBasedOnImplicitlyDeclaredVariablesInCurrentFunctionDefinition(NLCcodeblock * firstCodeBlockInTree, vector<NLCclassDefinition *> * classDefinitionList, string NLCfunctionName);
	bool findFormalFunctionArgumentCorrelateInExistingList(NLCclassDefinition * functionClassDefinition, vector<NLCitem*> * formalFunctionArgumentList, vector<NLCclassDefinition *> * classDefinitionList);
		bool findParentClass(NLCclassDefinition * classDefinition, string variableName, int inheritanceLevel, int * maxInheritanceLevel, NLCclassDefinition ** parentClass);
int getFilesFromFileList2(string inputListFileName, vector<string> * inputTextFileNameList);
#endif
#endif
