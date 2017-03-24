/*******************************************************************************
 *
 * This file is part of BAIPROJECT.
 *
 * BAIPROJECT is licensed under the GNU Affero General Public License
 * version 3, as published by the Free Software Foundation. The use of
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
 * File Name: NLCprint.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2017 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 2a1g 26-February-2017
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
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
