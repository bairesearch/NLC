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
 * File Name: NLPIprintCodeBlocks.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2013 Baxter AI (baxterai.com)
 * Project: Natural Language Programming Interface (compiler)
 * Project Version: 1e7b 23-November-2013
 * Requirements: requires text parsed by NLP Parser (eg Relex; available in .CFF format <relations>)
 *
 *******************************************************************************/


#ifndef HEADER_NLPI_PRINT_CODEBLOCKS
#define HEADER_NLPI_PRINT_CODEBLOCKS

#include <iostream>
#include <fstream>
#include <ctime>
#include <cstring>
#include <cstdlib>	//for random number generation
#include <cmath>
#include <string>
#include <vector>
using namespace std;

#include "NLPIcodeBlock.h"
#include "NLPIclassDefinition.h"

bool printCodeBlocks(NLPIcodeblock * firstCodeBlockInLevel, vector<NLPIclassDefinition *> * classDefinitionList, int progLang, string * code, int level);	//classDefinitionList is required by NLPI_SUPPORT_INPUT_FILE_LISTS only
	void generateFunctionExecutionArgumentsWithActionConceptInheritanceString(vector<NLPIclassDefinition *> * classDefinitionList, vector<NLPIitem*> * codeBlockParameters, string * functionArguments, int progLang);
		string generateCodeSingularReferenceText(NLPIitem * functionArgumentPropertyItem, int progLang);
			string generateInstanceNameWithContext(string instanceName, vector<string> * context, int progLang);
		#ifdef NLPI_INTERPRET_ACTION_PROPERTIES_AND_CONDITIONS_AS_FUNCTION_ARGUMENTS
		string generateCodeConditionPairReferenceText(NLPIitem * functionArgumentConditionItem, int progLang);
		#endif
	#ifdef NLPI_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS
	void generateLocalFunctionArgumentsBasedOnImplicitDeclarationsString(vector<NLPIitem*> * parameters, string * functionArguments, int progLang);
	#endif
	#ifdef NLPI_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS
	void generateFunctionArgumentsBasedOnActionAndActionObjectVars(vector<NLPIitem*> * parameters, string * functionArguments, int progLang);
	#endif
	string generateFunctionOwnerContext(vector<NLPIitem*> * parameters, int progLang);
string generateStringFromContextVector(vector<string> * context, int progLang);
			

#endif
