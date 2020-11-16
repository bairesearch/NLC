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
 * File Name: NLCItextDisplayOperations.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2019 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler Interface
 * Project Version: 2o2a 08-November-2020
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
