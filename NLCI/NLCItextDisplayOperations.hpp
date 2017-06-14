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
 * File Name: NLCItextDisplayOperations.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2017 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler Interface
 * Project Version: 2c2a 12-June-2017
 * Requirements: 
 *
 *******************************************************************************/

#ifndef NLCI_TEXT_DISPLAY_OPERATIONS
#define NLCI_TEXT_DISPLAY_OPERATIONS

#include "NLCIglobalDefs.hpp"
#include "NLCIoperations.hpp"
#include "GIAtranslatorOperations.hpp"
#include "GIAentityNodeClass.hpp"

#include <QTextBrowser>

#define NLCI_URL_DELIMITER "/"

class NLCItextDisplayOperationsClass
{
	//Q_OBJECT
	
private:
	NLCIoperationsClass NLCIoperations;
	SHAREDvarsClass SHAREDvars;
	
public:	
	#ifdef USE_NLCI
	bool processTextForNLC(QTextBrowser* textBrowser, GIAtranslatorVariablesClass* translatorVariablesTemplate, NLCfunction* NLCfunctionInList, bool displayLRPprocessedText);
	#elif defined USE_GIAI
	bool processTextForNLC(QTextBrowser* textBrowser, GIAtranslatorVariablesClass* translatorVariablesTemplate, bool displayLRPprocessedText);
	#endif
		bool processTextForNLChighlight(QTextBrowser* textBrowser, GIApreprocessorSentence* firstNLCprepreprocessorSentenceInList, bool displayLRPprocessedText, const int functionIndex);
			bool processTextForNLChighlightSentence(QTextBrowser* textBrowser, vector<GIApreprocessorWord*>* sentence, const int sentenceIndex, const int functionIndex, string* htmlSource);
	#ifdef USE_NLCI
	//bool NLCItextDisplayOperationsClass::getWordByIndex(const int functionIndex, const int sentenceIndex, const int wordIndex, NLCfunction* firstNLCfunctionInList, GIApreprocessorWord** wordTagFound);
	bool getWordByIndex(const int sentenceIndex, const int wordIndex, NLCfunction* NLCfunctionInList, GIApreprocessorWord** wordTagFound);
	#elif defined USE_GIAI
	bool getWordByIndex(const int sentenceIndex, const int wordIndex, GIAtranslatorVariablesClass* translatorVariablesTemplate, GIApreprocessorWord** wordTagFound);
	#endif	
		bool getWordByIndex(const int sentenceIndex, const int wordIndex, GIApreprocessorSentence* firstNLCprepreprocessorSentenceInList, GIApreprocessorWord** wordTagFound);

};


#endif
