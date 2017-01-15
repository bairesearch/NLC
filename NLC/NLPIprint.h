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
 * File Name: NLPIprint.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2013 Baxter AI (baxterai.com)
 * Project: Natural Language Programming Interface (compiler)
 * Project Version: 1c3b 27-October-2013
 * Requirements: requires text parsed by NLP Parser (eg Relex; available in .CFF format <relations>)
 *
 *******************************************************************************/


#ifndef HEADER_NLPI_PRINT
#define HEADER_NLPI_PRINT

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

bool printCode(NLPIcodeblock * firstCodeBlockInLevel, vector<NLPIclassDefinition *> * classDefinitionList, int progLang, string * code);
	bool printClassDefinitions(vector<NLPIclassDefinition *> * classDefinitionList, int progLang, string * code);
		#ifdef NLPI_INTERPRET_ACTION_PROPERTIES_AND_CONDITIONS_AS_FUNCTION_ARGUMENTS
		string generateFunctionPropertyConditionArgumentsWithActionConceptInheritance(GIAentityNode * actionEntity, string functionArguments, int progLang);
			string generateFunctionPropertyConditionArguments(GIAentityNode * actionEntity, string functionArguments, int progLang);
		#endif	
	bool printCodeBlocks(NLPIcodeblock * firstCodeBlockInLevel, int progLang, string * code, int level);
		void printLine(string command, int level, string * code);
		#ifdef NLPI_INTERPRET_ACTION_PROPERTIES_AND_CONDITIONS_AS_FUNCTION_ARGUMENTS
		string generateFunctionExecutionPropertyConditionArgumentsWithActionConceptInheritance(GIAentityNode * actionEntity, string functionArguments, int progLang);			
			string generateFunctionExecutionPropertyConditionArguments(GIAentityNode * actionEntity, string functionArguments, int progLang);
				string generateCodeConditionPairReferenceText(GIAentityNode * conditionEntity, GIAentityNode * conditionObjectEntity, int progLang);
				//string generateCodePropertyReferenceText(GIAentityNode * propertyEntity, int progLang);
					string generateInstanceNameWithContext(GIAentityNode * entity, int progLang);
			string generateCodeConditionPairDefinitionText(string conditionClassName, string conditionObjectClassName, int progLang);
			string generateCodePropertyDefinitionText(string propertyClassName, int progLang);
		#endif
		string generateConditionListName(string conditionClassName, string conditionObjectClassName);
		string generateConditionPairName(string conditionClassName, string conditionObjectClassName);
				
string generateCodeConditionListDefinitionText(string conditionClassName, string conditionObjectClassName, int progLang);
string generateCodePropertyListDefinitionText(string targetClassName, int progLang);

#endif
