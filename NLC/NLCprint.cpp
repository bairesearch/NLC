/*******************************************************************************
 *
 * No License
 * 
 * This work is under exclusive copyright (c) Baxter AI (baxterai.com). 
 * Nobody else can use, copy, distribute, or modify this work without being 
 * at risk of take-downs, shake-downs, or litigation. 
 * 
 * By publishing this source code in a public repository on GitHub, Terms of 
 * Service have been accepted by which Baxter AI have allowed others to view 
 * and fork their repository.
 * 
 * If you find software that doesn't have a license, that generally means you 
 * have no permission from the creators of the software to use, modify, or 
 * share the software. Although a code host such as GitHub may allow you to 
 * view and fork the code, this does not imply that you are permitted to use, 
 * modify, or share the software for any purpose.
 *
 * This notice has been derived from https://choosealicense.com/no-permission 
 * (https://web.archive.org/web/20180312144938/https://choosealicense.com/no-permission)
 *
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: NLCprint.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2019 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler
 * Project Version: 2o2a 08-November-2020
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
