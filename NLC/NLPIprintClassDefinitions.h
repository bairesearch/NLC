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
 * File Name: NLPIprintClassDefinitions.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2013 Baxter AI (baxterai.com)
 * Project: Natural Language Programming Interface (compiler)
 * Project Version: 1e9d 25-November-2013
 * Requirements: requires text parsed by NLP Parser (eg Relex; available in .CFF format <relations>)
 *
 *******************************************************************************/


#ifndef HEADER_NLPI_PRINT_CLASSDEFINITIONS
#define HEADER_NLPI_PRINT_CLASSDEFINITIONS

#include <iostream>
#include <fstream>
#include <ctime>
#include <cstring>
#include <cstdlib>	//for random number generation
#include <cmath>
#include <string>
#include <vector>
using namespace std;

#include "NLPIclassDefinition.h"
	
bool printClassDefinitions(vector<NLPIclassDefinition *> * classDefinitionList, int progLang, string * code);	
	void generateFunctionArgumentsWithActionConceptInheritanceString(vector<NLPIitem*> * parameters, string * functionArguments, int progLang);
		string generateCodeSingularDefinitionText(NLPIitem * currentItem, int progLang);
		string generateCodePluralDefinitionText(NLPIitem * currentItem, int progLang);
		#ifdef NLPI_INTERPRET_ACTION_PROPERTIES_AND_CONDITIONS_AS_FUNCTION_ARGUMENTS
		string generateCodeConditionPairDefinitionText(NLPIitem * currentItem, int progLang);
		#endif
			
#endif
