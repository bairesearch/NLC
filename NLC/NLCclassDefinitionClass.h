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
 * File Name: NLCclassDefinitionClass.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2014 Baxter AI (baxterai.com)
 * Project: Natural Language Programming Interface (compiler)
 * Project Version: 1j13b 12-September-2014
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/


#ifndef HEADER_NLC_CLASSDEFINITION_CLASS
#define HEADER_NLC_CLASSDEFINITION_CLASS

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

#include "NLCglobalDefs.h"
#include "NLCitemClass.h"
#include "GIAentityNodeClass.h"
#include "GIAentityConnectionClass.h"

	//progLangEndLine

class NLCclassDefinition
{
public:

	NLCclassDefinition(void);
	NLCclassDefinition(string newName);
	~NLCclassDefinition(void);

	string name;	//className (or instanceName if isActionOrConditionInstanceNotClass)
	string functionNameSpecial;
		//classdefinition sublists;
	vector<NLCclassDefinition *> propertyList;	//subclass
	vector<NLCclassDefinition *> conditionList;	//declared conditions
	vector<NLCclassDefinition *> definitionList;	//inherited parents
	vector<NLCclassDefinition *> functionList;

	bool isActionOrConditionInstanceNotClass;
	#ifdef NLC_SUPPORT_INPUT_FILE_LISTS_CHECK_ACTION_SUBJECT_CONTENTS_FOR_IMPLICITLY_DECLARED_PARAMETERS
	GIAentityNode * actionOrConditionInstance;
	#endif
	vector<NLCitem*> parameters;

	bool isDisabledChildReplicantDeclaration;

	bool printed;
};

NLCclassDefinition * findClassDefinition(vector<NLCclassDefinition *> * classDefinitionList, string name, bool * foundClassDefinition);




#endif
