 /*******************************************************************************
 *
 * License: GNU Affero General Public License version 3 (AGPLv3)
 *
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: NLCIeditorOperations.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2022 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler Interface
 * Project Version: 2p1a 05-June-2022
 * Requirements: 
 * /
 *******************************************************************************/


#ifndef NLCI_EDITOR_OPERATIONS
#define NLCI_EDITOR_OPERATIONS

#include "NLCIeditorOperations.hpp"
#include "NLCIoperations.hpp"
#include "GIAtranslatorOperations.hpp"
#include "LRPpreprocessorWordIdentification.hpp"
#include "LRPpreprocessor.hpp"

#include <QTextBlock>

#define NLCI_URL_DELIMITER "/"


class NLCIeditorOperationsClass
{
	//Q_OBJECT
	
private: 
	SHAREDvarsClass SHAREDvars;
	NLCIoperationsClass NLCIoperations;
	LRPpreprocessorClass LRPpreprocessor;
	LRPpreprocessorWordIdentificationClass LRPpreprocessorWordIdentification;
	LRPpreprocessorWordClassClass LRPpreprocessorWordClassObject;
	NLCpreprocessorClass NLCpreprocessor;

public:
	#ifdef USE_NLCI
	bool preprepreprocessTextForNLC(QTextEdit* editor, NLCfunction* firstNLCfunctionInList);
		bool preprepreprocessTextForNLChighlightWrapper(QVector<HighlightingRule>* highlightingRules, NLCfunction* firstNLCfunctionInList);
	#elif defined USE_GIAI
	bool preprepreprocessTextForNLC(QTextEdit* editor, GIAtranslatorVariablesClass* translatorVariablesTemplate);
		bool preprepreprocessTextForNLChighlightWrapper(QVector<HighlightingRule>* highlightingRules, GIAtranslatorVariablesClass* translatorVariablesTemplate);
	#endif
		bool preprepreprocessTextForNLChighlight(QVector<HighlightingRule>* highlightingRules, LRPpreprocessorSentence* firstNLCpreprepreprocessorSentenceInList);
	bool preprepreprocessTextForNLCsingleLine(QTextEdit* editor, QVector<HighlightingRule>* highlightingRules, const int lineIndex);
		bool preprepreprocessTextForNLCsingleLinehighlight(QVector<HighlightingRule>* highlightingRules, LRPpreprocessorSentence* currentNLCpreprepreprocessorSentenceInList, const int lineIndex);		
	bool preprepreprocessTextForNLChighlightSentence(QVector<HighlightingRule>* highlightingRules, vector<LRPpreprocessorPlainTextWord*>* sentence, const bool useOriginalSpacing);

};

#endif
