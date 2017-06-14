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
 * File Name: NLCIeditorOperations.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2017 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler Interface
 * Project Version: 2c2a 12-June-2017
 * Requirements: 
 *
 *******************************************************************************/

#ifndef NLCI_EDITOR_OPERATIONS
#define NLCI_EDITOR_OPERATIONS

#include "NLCIeditorOperations.hpp"
#include "NLCIoperations.hpp"
#include "GIAtranslatorOperations.hpp"
#include "GIApreprocessor.hpp"

#include <QTextBlock>

#define NLCI_URL_DELIMITER "/"


class NLCIeditorOperationsClass
{
	//Q_OBJECT
	
private: 
	SHAREDvarsClass SHAREDvars;
	NLCIoperationsClass NLCIoperations;
	GIApreprocessorClass GIApreprocessor;
	GIApreprocessorMultiwordReductionClass GIApreprocessorMultiwordReduction;
	GIApreprocessorMultiwordReductionClassClass GIApreprocessorMultiwordReductionClassObject;
	NLCpreprocessorClass NLCpreprocessor;

public:
	#ifdef USE_NLCI
	bool preprepreprocessTextForNLC(QTextEdit* editor, NLCfunction* firstNLCfunctionInList);
		bool preprepreprocessTextForNLChighlightWrapper(QVector<HighlightingRule>* highlightingRules, NLCfunction* firstNLCfunctionInList);
	#elif defined USE_GIAI
	bool preprepreprocessTextForNLC(QTextEdit* editor, GIAtranslatorVariablesClass* translatorVariablesTemplate);
		bool preprepreprocessTextForNLChighlightWrapper(QVector<HighlightingRule>* highlightingRules, GIAtranslatorVariablesClass* translatorVariablesTemplate);
	#endif
		bool preprepreprocessTextForNLChighlight(QVector<HighlightingRule>* highlightingRules, GIApreprocessorSentence* firstNLCpreprepreprocessorSentenceInList);
	bool preprepreprocessTextForNLCsingleLine(QTextEdit* editor, QVector<HighlightingRule>* highlightingRules, int lineIndex);
		bool preprepreprocessTextForNLCsingleLinehighlight(QVector<HighlightingRule>* highlightingRules, GIApreprocessorSentence* currentNLCpreprepreprocessorSentenceInList, int lineIndex);		
	bool preprepreprocessTextForNLChighlightSentence(QVector<HighlightingRule>* highlightingRules, vector<GIApreprocessorWord*>* sentence, bool useOriginalSpacing);

};

#endif
