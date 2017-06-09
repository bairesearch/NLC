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
 * File Name: NLCIeditorSyntaxHighlighter.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2017 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler Interface
 * Project Version: 2c1e 01-June-2017
 * Requirements: 
 *
 *******************************************************************************/

#include "NLCIeditorSyntaxHighlighter.hpp"

NLCIeditorSyntaxHighlighterClass::NLCIeditorSyntaxHighlighterClass(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
	reinitialiseSyntaxHighlighterRules();
}

void NLCIeditorSyntaxHighlighterClass::reinitialiseSyntaxHighlighterRules()
{
	HighlightingRule rule;
	
	highlightingRules.clear();
	
	logicalConditionFormat.setForeground(Qt::yellow);
	logicalConditionFormat.setFontWeight(QFont::Bold);
	QStringList keywordPatterns1;
	keywordPatterns1 << "\\bif\\b" << "\\belse\\b" << "\\bfor\\b";
	foreach (const QString &pattern, keywordPatterns1)
	{
		rule.pattern = QRegExp(pattern);
		rule.format = logicalConditionFormat;
		highlightingRules.append(rule);
	}
	
	mathtextVariableTypeFormat.setForeground(Qt::yellow);
	mathtextVariableTypeFormat.setFontWeight(QFont::Bold);
	QStringList keywordPatterns2;
	keywordPatterns2 << "\\bint\\b" << "\\bstring\\b" << "\\bbool\\b";
	foreach (const QString &pattern, keywordPatterns2)
	{
		rule.pattern = QRegExp(pattern);
		rule.format = mathtextVariableTypeFormat;
		highlightingRules.append(rule);
	}
	
	functionFormat1.setFontItalic(true);
	functionFormat1.setForeground(Qt::blue);
	QStringList keywordPatterns3;
	keywordPatterns3 << "\\bfunction\\b";
	foreach (const QString &pattern, keywordPatterns3)
	{
		rule.pattern = QRegExp(pattern);
		rule.format = functionFormat1;
		highlightingRules.append(rule);
	}
	
	functionFormat2.setFontItalic(true);
	functionFormat2.setForeground(Qt::blue);
	rule.pattern = QRegExp("\\b[A-Za-z0-9_]+(?=\\()");
	rule.format = functionFormat2;
	highlightingRules.append(rule);
}

void NLCIeditorSyntaxHighlighterClass::highlightBlock(const QString &text)
{
	foreach(const HighlightingRule &rule, highlightingRules) 
	{
		QRegExp expression(rule.pattern);
		int index = expression.indexIn(text);
		while(index >= 0) 
		{
			int length = expression.matchedLength();
			setFormat(index, length, rule.format);
			index = expression.indexIn(text, index + length);
		}
	}
}
