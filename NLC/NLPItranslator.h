/*******************************************************************************
 *
 * This file is part of BAIPROJECT.
 *
 * BAIPROJECT is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License version 3
 * only, as published by the Free Software Foundation.
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
 * File Name: NLPItranslator.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2013 Baxter AI (baxterai.com)
 * Project: Natural Language Programming Interface (compiler)
 * Project Version: 1e1a 20-November-2013
 * Requirements: requires text parsed by NLP Parser (eg Relex; available in .CFF format <relations>)
 *
 *******************************************************************************/


#ifndef HEADER_NLPI_TRANSLATOR
#define HEADER_NLPI_TRANSLATOR

//#define NLPI_NOT_NECESSARY

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
#include "NLPIcodeBlock.h"
#include "NLPIclassDefinition.h"

bool translateNetwork(NLPIcodeblock * firstCodeBlockInTree, vector<NLPIclassDefinition *> * classDefinitionList, vector<GIAentityNode*> * entityNodesActiveListComplete, vector<GIAentityNode*> * entityNodesActiveListActions, int maxNumberSentences, string functionName);
	bool generateCodeBlocks(NLPIcodeblock * firstCodeBlockInTree, vector<GIAentityNode*> * entityNodesActiveListComplete, vector<GIAentityNode*> * entityNodesActiveListActions, int maxNumberSentences, string functionName);
		NLPIcodeblock * generateConditionBlocks(NLPIcodeblock * currentCodeBlockInTree, GIAentityNode * objectOrSubjectEntity, NLPIitem ** objectOrSubjectItem, int sentenceIndex, bool * requiredTempVar, bool isObjectOrSubject);
		void generateObjectInitialisationsBasedOnPropertiesAndConditions(GIAentityNode * entity, NLPIcodeblock ** currentCodeBlockInTree, int sentenceIndex);
		#ifdef GIA_TRANSLATOR_DREAM_MODE_LINK_SPECIFIC_CONCEPTS_AND_ACTIONS
		void generateObjectInitialisationsBasedOnSubstanceConcepts(GIAentityNode * entity, NLPIcodeblock ** currentCodeBlockInTree, int sentenceIndex);
			void generateObjectInitialisationsBasedOnSubstanceConceptsRecurse(GIAentityNode * entity, GIAentityNode * definitionEntity, NLPIcodeblock ** currentCodeBlockInTree, int sentenceIndex);
		#endif
	bool generateClassHeirarchy(vector<NLPIclassDefinition *> * classDefinitionList, vector<GIAentityNode*> * entityNodesActiveListComplete, int maxNumberSentences);
		#ifdef NLPI_CREATE_A_SEPARATE_CLASS_FOR_SUBSTANCE_CONCEPT_DEFINITIONS
		string generateSubstanceConceptClassName(GIAentityNode * substanceConceptEntity);
		void generateSubstanceConceptClassNameRecurse(GIAentityNode * substanceConceptEntity, string * substanceConceptClassName);
		#endif		
		#ifdef NLPI_PREVENT_INHERITANCE_DOUBLE_DECLARATIONS_OF_CLASS_LIST_VARIABLES
		void eraseDuplicateClassDefinitionSublistItemIfFoundInParentClassDefinitionSublist(NLPIclassDefinition * classDefinition, vector<NLPIclassDefinition*> * classDefinitionSublist, int variableType);
			bool findVariableInParentClass(NLPIclassDefinition * classDefinition, string variableName, int variableType);
		#endif
#ifdef NLPI_INTERPRET_ACTION_PROPERTIES_AND_CONDITIONS_AS_FUNCTION_ARGUMENTS
void generateFunctionPropertyConditionArgumentsWithActionConceptInheritance(GIAentityNode * actionEntity, vector<NLPIitem*> * parameters);
void generateFunctionPropertyConditionArguments(GIAentityNode * actionEntity, vector<NLPIitem*> * parameters, bool performChildActionDuplicateCheck);
	bool checkDuplicateProperty(GIAentityNode * propertyEntity, vector<NLPIitem*> * parameters);
	bool checkDuplicateCondition(GIAentityNode * conditionEntity, vector<NLPIitem*> * parameters);
#endif
#ifdef NLPI_SUPPORT_INPUT_FILE_LISTS
void reconcileClassDefinitionListFunctionArgumentsBasedOnImplicitlyDeclaredVariablesInCurrentFunctionDefinition(NLPIcodeblock * firstCodeBlockInTree, vector<NLPIclassDefinition *> * classDefinitionList, string NLPIfunctionName);
	bool findFormalFunctionArgumentCorrelateInExistingList(NLPIclassDefinition * functionClassDefinition, vector<NLPIitem*> * formalFunctionArgumentList, vector<NLPIclassDefinition *> * classDefinitionList);
		bool findParentClass(NLPIclassDefinition * classDefinition, string variableName, int inheritanceLevel, int * maxInheritanceLevel, NLPIclassDefinition ** parentClass);
int getFilesFromFileList2(string inputListFileName, vector<string> * inputTextFileNameList);
#endif	
#endif	
