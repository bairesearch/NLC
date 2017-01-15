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
 * File Name: NLPIclassDefinition.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2013 Baxter AI (baxterai.com)
 * Project: Natural Language Programming Interface (compiler)
 * Project Version: 1e1a 20-November-2013
 * Requirements: requires text parsed by NLP Parser (eg Relex; available in .CFF format <relations>)
 *
 *******************************************************************************/


#ifndef HEADER_NLPI_CLASSDEFINITION
#define HEADER_NLPI_CLASSDEFINITION

#include <iostream>
#include <fstream>
#include <ctime>
#include <cstring>
#include <cstdlib>	//for random number generation
#include <cmath>
#include <string>
#include <vector>
#include <vector>
#include <unordered_map>
using namespace std;

#include "NLPIglobalDefs.h"
#include "NLPIitem.h"
#include "GIAglobalDefs.h"
#include "GIAentityNodeClass.h"
#include "GIAentityConnectionClass.h"

	//progLangEndLine
	
class NLPIclassDefinition
{
public:

	NLPIclassDefinition(void);
	NLPIclassDefinition(string newName);
	~NLPIclassDefinition(void);
	
	string name;	//className (or instanceName if isActionOrConditionInstanceNotClass) 
	string functionNameSpecial;
		//classdefinition sublists;
	vector<NLPIclassDefinition *> propertyList;	//subclass
	vector<NLPIclassDefinition *> conditionList;	//declared conditions
	vector<NLPIclassDefinition *> definitionList;	//inherited parents
	vector<NLPIclassDefinition *> functionList;

	bool isActionOrConditionInstanceNotClass;
	#ifdef NLPI_SUPPORT_INPUT_FILE_LISTS_CHECK_ACTION_SUBJECT_CONTENTS_FOR_IMPLICITLY_DECLARED_PARAMETERS
	GIAentityNode * actionOrConditionInstance;
	#endif
	vector<NLPIitem*> parameters;
	
	bool isDisabledChildReplicantDeclaration;
};

NLPIclassDefinition * findClassDefinition(vector<NLPIclassDefinition *> * classDefinitionList, string name, bool * foundClassDefinition);




#endif
