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
 * File Name: NLCIeditorSyntaxHighlighter.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2017 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler Interface
 * Project Version: 2e1a 07-December-2017
 * Requirements: 
 *
 *******************************************************************************/

#ifndef HEADER_NLCI_EDITOR_SYNTAX_HIGHLIGHTER
#define HEADER_NLCI_EDITOR_SYNTAX_HIGHLIGHTER

#include <QSyntaxHighlighter>

#include "NLCIglobalDefs.hpp"
#include "NLCIoperations.hpp"

class QTextDocument;

class NLCIeditorSyntaxHighlighterClass : public QSyntaxHighlighter
{
	Q_OBJECT

public:
	NLCIeditorSyntaxHighlighterClass(QTextDocument *parent = 0);
	void reinitialiseSyntaxHighlighterRules();
	
	QVector<HighlightingRule> highlightingRules;	//consider changing this to a map (will increase the change time, but decrease the lookup time; in the event of repeated words)
	
protected:
	void highlightBlock(const QString &text) override;

private:
	NLCIoperationsClass NLCIoperations;
	QTextCharFormat functionFormat1;
	QTextCharFormat functionFormat2;
	QTextCharFormat logicalConditionFormat;
	QTextCharFormat mathtextVariableTypeFormat;
};

#endif
