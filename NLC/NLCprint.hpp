 /*******************************************************************************
 *
 * License: GNU Affero General Public License version 3 (AGPLv3)
 *
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: NLCprint.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2022 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler
 * Project Version: 2p1a 05-June-2022
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 * /
 *******************************************************************************/


#ifndef HEADER_NLC_PRINT
#define HEADER_NLC_PRINT

#include "NLCcodeBlockClass.hpp"
#include "NLCclassDefinitionClass.hpp"
#include "NLCpreprocessorSentenceClass.hpp"	//required for NLC_CLASS_DEFINITIONS_PRINT_UNDEFINED_BUT_REFERENCED_FUNCTIONS
#include "NLCprintClassDefinitions.hpp"
#include "NLCprintCodeBlocks.hpp"
#include "NLCprintDefs.hpp"

#ifndef NLC_INPUT_FUNCTION_LISTS
class NLCprintClass
{
	private: NLCprintClassDefinitionsClass NLCprintClassDefinitions;
	private: NLCprintCodeBlocksClass NLCprintCodeBlocks;
	public: bool printCode(NLCcodeblock* firstCodeBlockInLevel, vector<NLCclassDefinition*>* classDefinitionList, int progLang, string* code, NLCfunction* firstNLCfunctionInList);
};
#endif

#endif
