 /*******************************************************************************
 *
 * License: GNU Affero General Public License version 3 (AGPLv3)
 *
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: NLCIeditorSyntaxHighlighter.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2022 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler Interface
 * Project Version: 2p1a 05-June-2022
 * Requirements: 
 * /
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
