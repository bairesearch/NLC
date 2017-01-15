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
 * File Name: NLPItranslatorCodeBlocks.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2013 Baxter AI (baxterai.com)
 * Project: Natural Language Programming Interface (compiler)
 * Project Version: 1e10b 25-November-2013
 * Requirements: requires text parsed by NLP Parser (eg Relex; available in .CFF format <relations>)
 *
 *******************************************************************************/


#ifndef HEADER_NLPI_TRANSLATOR_CODEBLOCKS
#define HEADER_NLPI_TRANSLATOR_CODEBLOCKS

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

bool generateCodeBlocks(NLPIcodeblock * firstCodeBlockInTree, vector<GIAentityNode*> * entityNodesActiveListComplete, vector<GIAentityNode*> * entityNodesActiveListActions, int maxNumberSentences, string functionName);
	GIAentityNode * getParent(GIAentityNode * currentEntity, int sentenceIndex);
	bool generateContextBlocksAndInitialiseParentIfNecessary(NLPIcodeblock ** currentCodeBlockInTree, GIAentityNode * currentEntity, int sentenceIndex);	
	NLPIcodeblock * generateConditionBlocks(NLPIcodeblock * currentCodeBlockInTree, GIAentityNode * entity, NLPIitem ** item, int sentenceIndex, bool * requiredTempVar, int itemType);
	bool generateObjectInitialisationsBasedOnPropertiesAndConditions(GIAentityNode * entity, NLPIcodeblock ** currentCodeBlockInTree, int sentenceIndex, string parentName, string parentConditionName);
		void generateObjectInitialisationsBasedOnPropertiesAndConditionsUpdateCodeBlockPointer(NLPIcodeblock ** currentCodeBlockInTree, NLPIcodeblock * firstCodeBlockBeforeRecursion, NLPIcodeblock * firstCodeBlockInSection, bool performedAtLeastOneObjectInitialisationAtThisLevel, bool performedAtLeastOneObjectInitialisationAtALowerLevel, bool * performedAtLeastOneObjectInitialisation);
	#ifdef GIA_TRANSLATOR_DREAM_MODE_LINK_SPECIFIC_CONCEPTS_AND_ACTIONS
	void generateObjectInitialisationsBasedOnSubstanceConcepts(GIAentityNode * entity, NLPIcodeblock ** currentCodeBlockInTree, int sentenceIndex);
		void generateObjectInitialisationsBasedOnSubstanceConceptsRecurse(GIAentityNode * entity, GIAentityNode * definitionEntity, NLPIcodeblock ** currentCodeBlockInTree, int sentenceIndex);
	#endif
	
#endif	
