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
 * File Name: NLCIeditorSyntaxHighlighter.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2019 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler Interface
 * Project Version: 2k1a 02-June-2020
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
