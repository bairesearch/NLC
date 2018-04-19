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
 * File Name: NLCItextDisplayOperations.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2018 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler Interface
 * Project Version: 2e4a 15-January-2018
 * Requirements: 
 *
 *******************************************************************************/

#include "NLCItextDisplayOperations.hpp"
#include "GIApreprocessor.hpp"
#include "GIAdraw.hpp"
#include "LDreferenceClass.hpp"


#ifdef USE_NLCI
bool NLCItextDisplayOperationsClass::processTextForNLC(QTextBrowser* textBrowser, GIAtranslatorVariablesClass* translatorVariablesTemplate, NLCfunction* activeNLCfunctionInList, const bool displayLRPprocessedText, const bool processText)
{
	bool result = true;
	
	if(processText)
	{
		NLCfunction* backupOfNextFunctionInList = activeNLCfunctionInList->next;
		activeNLCfunctionInList->next = new NLCfunction();	//this is to prevent executeNLC from executing multiple functions in the list
		if(!NLCIoperations.executeNLCwrapper(translatorVariablesTemplate, activeNLCfunctionInList))
		{
			result = false;
		}
		activeNLCfunctionInList->next = backupOfNextFunctionInList;
	}
	if(!processTextForNLChighlight(textBrowser, activeNLCfunctionInList->firstNLCprepreprocessorSentenceInList, displayLRPprocessedText, activeNLCfunctionInList->functionIndexTemp))
	{
		result = false;
	}

	return result;
}
#elif defined USE_GIAI
bool NLCItextDisplayOperationsClass::processTextForNLC(QTextBrowser* textBrowser, GIAtranslatorVariablesClass* translatorVariablesTemplate, const bool displayLRPprocessedText, const bool processText)
{
	bool result = true;
	
	if(processText)
	{
		if(!NLCIoperations.executeGIAwrapper(translatorVariablesTemplate, NULL, false))
		{
			result = false;
		}	
	}
	if(!processTextForNLChighlight(textBrowser, translatorVariablesTemplate->firstGIApreprocessorSentenceInList, displayLRPprocessedText, 0))
	{
		result = false;
	}

	return result;
}
#endif

bool NLCItextDisplayOperationsClass::processTextForNLChighlight(QTextBrowser* textBrowser, GIApreprocessorSentence* firstNLCprepreprocessorSentenceInList, const bool displayLRPprocessedText, const int functionIndex)
{
	bool result = true;
	
	textBrowser->clear();

	string htmlSource = "";
	int sentenceIndex = 0;
	GIApreprocessorSentence* currentNLCprepreprocessorSentenceInList = firstNLCprepreprocessorSentenceInList;
	while(currentNLCprepreprocessorSentenceInList->next != NULL)
	{
		vector<GIApreprocessorWord*>* sentence = NULL;
		#ifdef USE_GIAI
		if(displayLRPprocessedText)
		{
			sentence = &(currentNLCprepreprocessorSentenceInList->sentenceContentsLRP);
		}
		else
		{
		#endif
			sentence = &(currentNLCprepreprocessorSentenceInList->sentenceContentsOriginal);
		#ifdef USE_GIAI
		}
		#endif

		#ifdef USE_NLCI
		//prepend indentation (tabulation currently set to 8 characters)
		string indentationHTML = "";
		for(int i=0; i<currentNLCprepreprocessorSentenceInList->indentation; i++)
		{
			indentationHTML = indentationHTML + "&nbsp;" + "&nbsp;" + "&nbsp;" + "&nbsp;" + "&nbsp;" + "&nbsp;" + "&nbsp;" + "&nbsp;";
		}
		htmlSource = htmlSource + indentationHTML;
		#endif

		if(!processTextForNLChighlightSentence(textBrowser, sentence, sentenceIndex, functionIndex, &htmlSource))
		{
			result = false;
		}

		currentNLCprepreprocessorSentenceInList = currentNLCprepreprocessorSentenceInList->next;
		sentenceIndex++;
	}
	
	textBrowser->setHtml(convertStringToQString(htmlSource));
	
	return result;
}

bool NLCItextDisplayOperationsClass::processTextForNLChighlightSentence(QTextBrowser* textBrowser, vector<GIApreprocessorWord*>* sentence, const int sentenceIndex, const int functionIndex, string* htmlSource)
{
	bool result = true;

	int characterIndexFirst = 0;
	int charCount = 0;
	string lineHtmlText = "";

	for(int i=0; i<sentence->size(); i++)
	{
		GIApreprocessorWord* wordTag = (*sentence)[i];
		string word = wordTag->tagName;
		//cout << "word = " << word << endl;

		//int characterIndex = currentNLCprepreprocessorSentenceInList->characterIndexInSentenceContentsOriginalText;
	
		int colourIndex = NLCIoperations.processTextForNLChighlightWordDetermineColourIndex(wordTag->entityReference);

		bool logicalConditionFound = false;
		if(SHAREDvars.textInTextArray(word, logicalConditionOperationsWordsBasicArray, NLC_LOGICAL_CONDITION_OPERATIONS_WORDS_BASIC_NUMBER_OF_TYPES))
		{
			logicalConditionFound = true;
			colourIndex = NLCI_EDITOR_SYNTAX_HIGHLIGHTER_LOGICAL_CONDITION_COLOUR;
		}
		bool mathtextVariableTypeFound = false;
		if(SHAREDvars.textInTextArray(word, preprocessorMathNaturalLanguageVariables, NLC_PREPROCESSOR_MATH_MATHTEXT_VARIABLES_NUMBER_OF_TYPES))
		{
			mathtextVariableTypeFound = true;
			colourIndex = NLCI_EDITOR_SYNTAX_HIGHLIGHTER_MATHTEXT_VARIABLE_TYPE_COLOUR;
		}

		QColor colour = NLCIoperations.generateColourQ(colourIndex);
		string colourHex = convertQStringToString(colour.name());
		string functionIndexString = SHAREDvars.convertIntToString(functionIndex);
		string sentenceIndexString = SHAREDvars.convertIntToString(sentenceIndex);
		string wordIndexString = SHAREDvars.convertIntToString(i);
		string link = functionIndexString + NLCI_URL_DELIMITER + sentenceIndexString + NLCI_URL_DELIMITER + wordIndexString;	//this format is important

		string wordHtmlText = "";
		if(wordTag->entityReference != NULL)
		{
			wordHtmlText = wordHtmlText + "<a href=\"" + link + "\" style=\"color:" + colourHex + "\">" + word + "</a>";
		}
		else if(logicalConditionFound || mathtextVariableTypeFound)
		{
			wordHtmlText = wordHtmlText + "<font color=" + colourHex + ">" + word + "</font>";
		}
		else
		{
			wordHtmlText = wordHtmlText + word;
		}
		charCount = charCount + word.length();

		if(i != sentence->size()-1)
		{
			wordHtmlText = wordHtmlText + STRING_SPACE;
		}
		charCount++;
		//cout << "wordHtmlText = " << wordHtmlText << endl;
		
		lineHtmlText = lineHtmlText + wordHtmlText;

		/*
		QTextCharFormat classFormat;
		classFormat.setForeground(generateColourQ(colourIndex));
		editorWindow->syntaxHighlighter->setFormat(characterIndex, word.size(), classFormat);
		*/	
	}

	lineHtmlText = lineHtmlText + "<br />";
	//cout << "lineHtmlText = " << lineHtmlText << endl;
	
	*htmlSource = *htmlSource + lineHtmlText;
	
	return result;
}




#ifdef USE_NLCI
/*
//use this function in case label_linkActivated can't distinguish between the NLCItextDisplayWindowClass class object which triggered the function
bool NLCItextDisplayOperationsClass::getWordByIndex(const int functionIndex, const int sentenceIndex, const int wordIndex, NLCfunction* firstNLCfunctionInList, GIApreprocessorWord** wordTagFound)
{
	bool result = true;
	NLCfunction* currentNLCfunctionInList = firstNLCfunctionInList;
	while(currentNLCfunctionInList->next != NULL)
	{
		if(currentNLCfunctionInList->functionIndexTemp == functionIndex)
		{
			if(getWordByIndex(sentenceIndex, wordIndex, currentNLCfunctionInList, &wordTagFound))
			{
				result = false;
			}
		}
		currentNLCfunctionInList = currentNLCfunctionInList->next;
	}
	return result;
}
*/
bool NLCItextDisplayOperationsClass::getWordByIndex(const int sentenceIndex, const int wordIndex, NLCfunction* activeNLCfunctionInList, GIApreprocessorWord** wordTagFound, int* sentenceIndexUpdated)
{
	return getWordByIndex(sentenceIndex, wordIndex, activeNLCfunctionInList->firstNLCprepreprocessorSentenceInList, wordTagFound, sentenceIndexUpdated);
}
#elif defined USE_GIAI
bool NLCItextDisplayOperationsClass::getWordByIndex(const int sentenceIndex, const int wordIndex, GIAtranslatorVariablesClass* translatorVariablesTemplate, GIApreprocessorWord** wordTagFound, int* sentenceIndexUpdated)
{
	return getWordByIndex(sentenceIndex, wordIndex,  translatorVariablesTemplate->firstGIApreprocessorSentenceInList, wordTagFound, sentenceIndexUpdated);
}
#endif
bool NLCItextDisplayOperationsClass::getWordByIndex(const int sentenceIndex, const int wordIndex, GIApreprocessorSentence* firstNLCprepreprocessorSentenceInList, GIApreprocessorWord** wordTagFound, int* sentenceIndexUpdated)
{
	bool result = false;

	int currentSentenceIndex = 0;
	GIApreprocessorSentence* currentNLCprepreprocessorSentenceInList = firstNLCprepreprocessorSentenceInList;
	//cout << "getWordByIndex" << endl;
	while(currentNLCprepreprocessorSentenceInList->next != NULL)
	{
		if(sentenceIndex == currentSentenceIndex)
		{
			//cout << "currentSentenceIndex = " << currentSentenceIndex << endl;
			vector<GIApreprocessorWord*>* sentence = &(currentNLCprepreprocessorSentenceInList->sentenceContentsOriginal);
			for(int i=0; i<sentence->size(); i++)
			{
				if(i == wordIndex)
				{
					GIApreprocessorWord* wordTag = (*sentence)[i];
					*wordTagFound = wordTag;
					#ifdef USE_GIAI
					#ifdef GIA_PREPROCESSOR_ASSIGN_UNIQUE_SENTENCE_INDICES_FOR_SENTENCES
					*sentenceIndexUpdated = currentNLCprepreprocessorSentenceInList->sentenceIndex;
					#else
					*sentenceIndexUpdated = currentSentenceIndex + GIA_NLP_START_SENTENCE_INDEX;
					#endif
					/*
					cout << "* wordTag = " << wordTag->tagName << endl;
					cout << "* wordIndex = " << wordIndex << endl;
					cout << "currentNLCprepreprocessorSentenceInList->sentenceIndex = " << currentNLCprepreprocessorSentenceInList->sentenceIndex << endl;
					*/
					#else
					*sentenceIndexUpdated = currentSentenceIndex + GIA_NLP_START_SENTENCE_INDEX;
					#endif
					result = true;
				}
			}
		}

		currentNLCprepreprocessorSentenceInList = currentNLCprepreprocessorSentenceInList->next;
		currentSentenceIndex++;
	}

	return result;
}
	
						









