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
 * File Name: NLCmain.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2016 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 1u2e 26-September-2016
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/


#ifndef HEADER_NLC_MAIN
#define HEADER_NLC_MAIN

#include "NLCglobalDefs.h"
#include "NLCcodeBlockClass.h"
#include "NLCclassDefinitionClass.h"

int main(int argc, char** argv);
	string removeFileNameExtensions(string NLCfunctionName);
	#ifdef NLC_USE_PREDEFINED_FUNCTION_NAME_FOR_NATURAL_LANGUAGE_CODE_WITHOUT_FUNCTION_SPECIFIED
	string removeNLCfileNameExtension(string NLCfunctionName);
	#endif
	//#ifndef GIA_TRANSLATOR_TRANSFORM_THE_ACTION_OF_POSSESSION_EG_HAVING_INTO_A_PROPERTY_BASIC
	void transformTheActionOfPossessionEgHavingIntoAproperty(vector<GIAentityNode*>* entityNodesActiveListComplete);
	//#endif
	#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS
	bool generateClassDefinitionFunctionDeclarationsAndReconcileArguments(int numberOfInputFilesInList, vector<NLCclassDefinition*>* classDefinitionList, vector<vector<GIAentityNode*>*>* entityNodesActiveListCompleteFunctions, vector<NLCcodeblock*>* firstCodeBlockInTreeList);
	#endif
	#ifndef NLC_USE_LIBRARY
	void printPredefinedNLCfunctions(NLCcodeblock* currentCodeBlockInTree);
	#endif


#endif
