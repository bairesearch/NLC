 /*******************************************************************************
 *
 * License: GNU Affero General Public License version 3 (AGPLv3)
 *
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: NLCIeditorSyntaxHighlighter.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2022 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler Interface
 * Project Version: 2p1a 05-June-2022
 * Requirements: 
 * /
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
	
	QColor logicalConditionFormatColour = NLCIoperations.generateColourQ(NLCI_EDITOR_SYNTAX_HIGHLIGHTER_LOGICAL_CONDITION_COLOUR);
	logicalConditionFormat.setForeground(logicalConditionFormatColour);	//Qt::darkYellow
	logicalConditionFormat.setFontWeight(QFont::Bold);
	QStringList keywordPatterns1;
	for(int i=0; i<NLC_LOGICAL_CONDITION_OPERATIONS_WORDS_BASIC_NUMBER_OF_TYPES; i++)
	{
		string logicalConditionName = logicalConditionOperationsWordsBasicArray[i];
		string logicalConditionNameRegEx = string("\\b") + logicalConditionName + string("\\b");
		keywordPatterns1 << convertStringToQString(logicalConditionNameRegEx);
	}
	foreach (const QString &pattern, keywordPatterns1)
	{
		rule.pattern = QRegExp(pattern);
		rule.format = logicalConditionFormat;
		highlightingRules.append(rule);
	}
	
	QColor mathtextVariableTypeFormatColour = NLCIoperations.generateColourQ(NLCI_EDITOR_SYNTAX_HIGHLIGHTER_MATHTEXT_VARIABLE_TYPE_COLOUR);
	mathtextVariableTypeFormat.setForeground(mathtextVariableTypeFormatColour);	//Qt::darkYellow
	mathtextVariableTypeFormat.setFontWeight(QFont::Bold);
	QStringList keywordPatterns2;
	for(int i=0; i<NLC_PREPROCESSOR_MATH_MATHTEXT_VARIABLES_NUMBER_OF_TYPES; i++)
	{
		string mathtextVariableTypeName = preprocessorMathNaturalLanguageVariables[i];
		string mathtextVariableTypeNameRegEx = string("\\b") + mathtextVariableTypeName + string("\\b");
		keywordPatterns2 << convertStringToQString(mathtextVariableTypeNameRegEx);
	}
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
