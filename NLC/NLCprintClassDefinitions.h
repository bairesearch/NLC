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
 * File Name: NLCprintClassDefinitions.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2014 Baxter AI (baxterai.com)
 * Project: Natural Language Programming Interface (compiler)
 * Project Version: 1i8c 24-August-2014
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/


#ifndef HEADER_NLC_PRINT_CLASSDEFINITIONS
#define HEADER_NLC_PRINT_CLASSDEFINITIONS

#include <iostream>
#include <fstream>
#include <ctime>
#include <cstring>
#include <cstdlib>	//for random number generation
#include <cmath>
#include <string>
#include <vector>
using namespace std;

#include "NLCclassDefinitionClass.h"

bool printClassDefinitions(vector<NLCclassDefinition *> * classDefinitionList, int progLang, string * code);
	void generateFunctionArgumentsWithActionConceptInheritanceString(vector<NLCitem*> * parameters, string * functionArguments, int progLang);
		string generateCodeSingularDefinitionText(NLCitem * currentItem, int progLang);
		string generateCodePluralDefinitionText(NLCitem * currentItem, int progLang);
		#ifdef NLC_INTERPRET_ACTION_PROPERTIES_AND_CONDITIONS_AS_FUNCTION_ARGUMENTS
		string generateCodeConditionPairDefinitionText(NLCitem * currentItem, int progLang);
		#endif
	bool arefunctionArgumentsPrinted(vector<NLCclassDefinition *> * classDefinitionList, vector<NLCitem*> * parameters);
	bool isConditionObjectPrinted(vector<NLCclassDefinition *> * classDefinitionList, vector<NLCitem*> * parameters);

#endif
