 /*******************************************************************************
 *
 * License: GNU Affero General Public License version 3 (AGPLv3)
 *
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: NLCprint.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2022 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler
 * Project Version: 2p1a 05-June-2022
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 * /
 *******************************************************************************/


#include "NLCprint.hpp"

#ifndef NLC_INPUT_FUNCTION_LISTS
bool NLCprintClass::printCode(NLCcodeblock* firstCodeBlockInLevel, vector<NLCclassDefinition*>* classDefinitionList, int progLang, string* code, NLCfunction* firstNLCfunctionInList)
{
	bool result = true;

	#ifndef NLC_NONOO_DISABLE_CLASS_HEIRACHY
	if(!NLCprintClassDefinitions.printClassDefinitions(classDefinitionList, progLang, code, false, firstNLCfunctionInList))
	{
		result = false;
	}
	#endif

	int level = 0;
	if(!NLCprintCodeBlocks.printCodeBlocks(firstCodeBlockInLevel, classDefinitionList, progLang, code, level))
	{
		result = false;
	}

	return result;
}
#endif
