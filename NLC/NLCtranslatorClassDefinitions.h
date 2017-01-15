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
 * File Name: NLCtranslatorClassDefinitions.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2015 Baxter AI (baxterai.com)
 * Project: Natural Language Programming Interface (compiler)
 * Project Version: 1n15f 28-January-2015
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/


#ifndef HEADER_NLC_TRANSLATOR_CLASSDEFINITIONS
#define HEADER_NLC_TRANSLATOR_CLASSDEFINITIONS

#include "GIAentityNodeClass.h"
#include "GIAentityConnectionClass.h"
#include "NLCcodeBlockClass.h"
#include "NLCclassDefinitionClass.h"

bool generateClassHeirarchy(vector<NLCclassDefinition* >* classDefinitionList, vector<GIAentityNode*>* entityNodesActiveListComplete, NLCclassDefinitionFunctionDependency* parentFunctionDependency, vector<NLCclassDefinitionFunctionDependency*>* functionDependencyList);
	bool generateClassHeirarchyCondition(NLCclassDefinition* classDefinition, NLCclassDefinition* targetClassDefinition, GIAentityNode* targetEntity);
#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE
bool generateClassHeirarchyFunctions(vector<NLCclassDefinition* >* classDefinitionList, vector<GIAentityNode*>* entityNodesActiveListComplete, NLCclassDefinitionFunctionDependency* parentFunctionDependency, vector<NLCclassDefinitionFunctionDependency*>* functionDependencyList);
#endif	
	bool generateClassHeirarchyValidClassChecks(GIAentityNode* entityNode);
	bool generateClassHeirarchyTargetValidClassChecks(GIAentityNode* targetEntity);
	#ifdef NLC_CREATE_A_SEPARATE_CLASS_FOR_SUBSTANCE_CONCEPT_DEFINITIONS
	string generateSubstanceConceptClassName(GIAentityNode* substanceConceptEntity);
		void generateSubstanceConceptClassNameRecurse(GIAentityNode* substanceConceptEntity, string* substanceConceptClassName);
	#endif
	#ifdef NLC_PREVENT_INHERITANCE_DOUBLE_DECLARATIONS_OF_CLASS_LIST_VARIABLES
	void eraseDuplicateClassDefinitionSublistItemIfFoundInParentClassDefinitionSublist(NLCclassDefinition* classDefinition, vector<NLCclassDefinition*>* classDefinitionSublist, int variableType);
		bool findVariableInParentClass(NLCclassDefinition* classDefinition, string variableName, int variableType);
	#endif

#ifdef NLC_INTERPRET_ACTION_PROPERTIES_AND_CONDITIONS_AS_FUNCTION_ARGUMENTS
void generateFunctionPropertyConditionArgumentsWithActionConceptInheritance(GIAentityNode* actionEntity, vector<NLCitem*>* parameters);
void generateFunctionPropertyConditionArguments(GIAentityNode* actionEntity, vector<NLCitem*>* parameters, bool performChildActionDuplicateCheck);
	bool checkDuplicateProperty(GIAentityNode* propertyEntity, vector<NLCitem*>* parameters);
	bool checkDuplicateCondition(GIAentityNode* conditionEntity, vector<NLCitem*>* parameters);
#endif

#endif
