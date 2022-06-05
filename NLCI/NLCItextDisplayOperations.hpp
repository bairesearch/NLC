 /*******************************************************************************
 *
 * License: GNU Affero General Public License version 3 (AGPLv3)
 *
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: NLCItextDisplayOperations.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2022 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler Interface
 * Project Version: 2p1a 05-June-2022
 * Requirements: 
 * /
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
	bool processTextForNLC(QTextBrowser* textBrowser, GIAtranslatorVariablesClass* translatorVariablesTemplate, NLCfunction* NLCfunctionInList, const bool displayLRPprocessedText, const bool processText);
	#elif defined USE_GIAI
	bool processTextForNLC(QTextBrowser* textBrowser, GIAtranslatorVariablesClass* translatorVariablesTemplate, const bool displayLRPprocessedText, const bool processText);
	#endif
		bool processTextForNLChighlight(QTextBrowser* textBrowser, LRPpreprocessorSentence* firstNLCprepreprocessorSentenceInList, const bool displayLRPprocessedText, const int functionIndex);
			bool processTextForNLChighlightSentence(QTextBrowser* textBrowser, vector<LRPpreprocessorPlainTextWord*>* sentence, const int sentenceIndex, const int functionIndex, string* htmlSource);
	#ifdef USE_NLCI
	//bool NLCItextDisplayOperationsClass::getWordByIndex(const int functionIndex, const int sentenceIndex, const int wordIndex, NLCfunction* firstNLCfunctionInList, LRPpreprocessorPlainTextWord** wordTagFound);
	bool getWordByIndex(const int sentenceIndex, const int wordIndex, NLCfunction* NLCfunctionInList, LRPpreprocessorPlainTextWord** wordTagFound, int* sentenceIndexUpdated);
	#elif defined USE_GIAI
	bool getWordByIndex(const int sentenceIndex, const int wordIndex, GIAtranslatorVariablesClass* translatorVariablesTemplate, LRPpreprocessorPlainTextWord** wordTagFound, int* sentenceIndexUpdated);
	#endif	
		bool getWordByIndex(const int sentenceIndex, const int wordIndex, LRPpreprocessorSentence* firstNLCprepreprocessorSentenceInList, LRPpreprocessorPlainTextWord** wordTagFound, int* sentenceIndexUpdated);

};


#endif
