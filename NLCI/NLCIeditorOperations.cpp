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
 * File Name: NLCIeditorOperations.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2018 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler Interface
 * Project Version: 2f6b 16-April-2018
 * Requirements: 
 * /
 *******************************************************************************/


#include "NLCIglobalDefs.hpp"
#include "NLCIeditorOperations.hpp"
#include "LDreferenceClass.hpp"


#include <QtWidgets>


#ifdef USE_NLCI
bool NLCIeditorOperationsClass::preprepreprocessTextForNLC(QTextEdit* editor, NLCfunction* firstNLCfunctionInList)
{
	bool result = true;
	
	QString textQ = editor->toPlainText();	//.toAscii();
	string text = convertQStringToString(textQ);

	bool interpretNewLinesAsNewSentences = true;	//NB NLC interprets new lines as new sentences

	int numberOfLinesInFile = 0;
	vector<string> fileLinesList;
	if(!SHAREDvars.getLinesFromFile(&text, &fileLinesList, &numberOfLinesInFile))
	{
		cerr << "NLCIeditorOperationsClass::preprepreprocessTextForNLC{} error: !getLinesFromFile" << endl;
		exit(EXIT_ERROR);
	}
	bool detectedFunctions = false;
	int numberOfFunctionsInList = 0;
	vector<string> inputTextFileNameList;
	if(!NLCpreprocessor.preprocessTextForNLCextractFunctionsAndCreatePreprocessSentences(&fileLinesList, firstNLCfunctionInList, &detectedFunctions, &numberOfFunctionsInList, &inputTextFileNameList))
	{
		result = false;
	}
	
	return result;
}
bool NLCIeditorOperationsClass::preprepreprocessTextForNLChighlightWrapper(QVector<HighlightingRule>* highlightingRules, NLCfunction* firstNLCfunctionInList)
{
	bool result = true;
	
	string lrpFolder = string(NLCI_LRP_FOLDER) + CHAR_FOLDER_DELIMITER;
	if(!GIApreprocessorWordIdentification.initialiseLRP(lrpFolder, true))
	{
		result = false;
	}
	
	NLCfunction* currentNLCfunctionInList = firstNLCfunctionInList;
	while(currentNLCfunctionInList->next != NULL)
	{
		//cout << "currentNLCfunctionInList->NLCfunctionName = " << currentNLCfunctionInList->NLCfunctionName << endl;
		if(!preprepreprocessTextForNLChighlight(highlightingRules, currentNLCfunctionInList->firstNLCprepreprocessorSentenceInList))
		{
			result = false;
		}
		currentNLCfunctionInList = currentNLCfunctionInList->next;
	}
	
	return result;
}
#elif defined USE_GIAI
bool NLCIeditorOperationsClass::preprepreprocessTextForNLC(QTextEdit* editor, GIAtranslatorVariablesClass* translatorVariablesTemplate)
{
	bool result = true;
	
	QString textQ = editor->toPlainText();	//.toAscii();
	string text = convertQStringToString(textQ);

	bool interpretNewLinesAsNewSentences = false;	//NB NLC interprets new lines as new sentences
	bool splitMultisentenceLines = false;	//not currently supported by NLCI, as line detection must match
	if(!GIApreprocessor.createPreprocessSentences(text, translatorVariablesTemplate->firstGIApreprocessorSentenceInList, interpretNewLinesAsNewSentences, splitMultisentenceLines))
	{
		result = false;
	}
	return result;
}
bool NLCIeditorOperationsClass::preprepreprocessTextForNLChighlightWrapper(QVector<HighlightingRule>* highlightingRules, GIAtranslatorVariablesClass* translatorVariablesTemplate)
{
	bool result = true;

	string lrpFolder = string(NLCI_LRP_FOLDER) + CHAR_FOLDER_DELIMITER;
	if(!GIApreprocessorWordIdentification.initialiseLRP(lrpFolder, true))
	{
		result = false;
	}
	
	if(!preprepreprocessTextForNLChighlight(highlightingRules, translatorVariablesTemplate->firstGIApreprocessorSentenceInList))
	{
		result = false;
	}
	return result;
}
#endif

bool NLCIeditorOperationsClass::preprepreprocessTextForNLChighlight(QVector<HighlightingRule>* highlightingRules, GIApreprocessorSentence* firstNLCpreprepreprocessorSentenceInList)
{
	bool result = true;
	
	int line = 0;
	GIApreprocessorSentence* currentNLCpreprepreprocessorSentenceInList = firstNLCpreprepreprocessorSentenceInList;
	while(currentNLCpreprepreprocessorSentenceInList->next != NULL)
	{
		vector<GIApreprocessorPlainTextWord*>* sentence = &(currentNLCpreprepreprocessorSentenceInList->sentenceContentsOriginal);
		//cout << "currentNLCpreprepreprocessorSentenceInList->sentenceContentsOriginal = " << GIApreprocessorWordClassObject.generateTextFromVectorWordList(&(currentNLCpreprepreprocessorSentenceInList->sentenceContentsOriginal)) << endl;
		if(!preprepreprocessTextForNLChighlightSentence(highlightingRules, sentence, true))
		{
			result = false;
		}

		currentNLCpreprepreprocessorSentenceInList = currentNLCpreprepreprocessorSentenceInList->next;
		line++;
	}
	
	return result;
}

bool NLCIeditorOperationsClass::preprepreprocessTextForNLCsingleLine(QTextEdit* editor, QVector<HighlightingRule>* highlightingRules, const int lineIndex)
{
	bool result = true;
	
	QTextDocument* textDocQ = editor->document();
	QTextBlock textBlockQ = textDocQ->findBlockByLineNumber(lineIndex);
	QString lineTextQ = textBlockQ.text();
	string lineText = convertQStringToString(lineTextQ);
	lineText = lineText + CHAR_NEWLINE;

	#ifdef USE_NLCI
	bool interpretNewLinesAsNewSentences = true;	//NB NLC interprets new lines as new sentences
	#elif defined USE_GIAI
	bool interpretNewLinesAsNewSentences = true;	//ideally this should be false, but this implementation will not work as line detection won't match
	#endif
	bool splitMultisentenceLines = false;	//not currently supported by NLCI, as line detection must match
	
	GIApreprocessorSentence* modifiedNLCpreprepreprocessorSentenceInList = new GIApreprocessorSentence();
	if(!GIApreprocessor.createPreprocessSentences(lineText, modifiedNLCpreprepreprocessorSentenceInList, interpretNewLinesAsNewSentences, splitMultisentenceLines))
	{
		result = false;
	}

	if(!preprepreprocessTextForNLCsingleLinehighlight(highlightingRules, modifiedNLCpreprepreprocessorSentenceInList, lineIndex))
	{
		result = false;
	}
	
	//delete modifiedNLCpreprepreprocessorSentenceInList;

	return result;
}
		
bool NLCIeditorOperationsClass::preprepreprocessTextForNLCsingleLinehighlight(QVector<HighlightingRule>* highlightingRules, GIApreprocessorSentence* currentNLCpreprepreprocessorSentenceInList, const int lineIndex)
{
	bool result = true;

	vector<GIApreprocessorPlainTextWord*>* sentence = &(currentNLCpreprepreprocessorSentenceInList->sentenceContentsOriginal);
	//cout << "preprepreprocessTextForNLCsingleLinehighlight{}: currentNLCpreprepreprocessorSentenceInList->sentenceContentsOriginal = " << GIApreprocessorWordClassObject.generateTextFromVectorWordList(&(currentNLCpreprepreprocessorSentenceInList->sentenceContentsOriginal)) << endl;
	if(!preprepreprocessTextForNLChighlightSentence(highlightingRules, sentence, true))
	{
		result = false;
	}
	
	return result;
}

bool NLCIeditorOperationsClass::preprepreprocessTextForNLChighlightSentence(QVector<HighlightingRule>* highlightingRules, vector<GIApreprocessorPlainTextWord*>* sentence, const bool useOriginalSpacing)
{
	int characterIndexFirst = 0;
	int charCount = 0;
	for(int i=0; i<sentence->size(); i++)
	{
		string spaceText = STRING_SPACE;
		GIApreprocessorPlainTextWord* wordTag = (*sentence)[i];
		string word = wordTag->tagName;

		bool ignoreWord = false;

		for(int i=0; i<GIA_NLP_NUMBER_OF_MATH_CHARACTERS; i++)
		{
			if(word.find(nlpMathCharacterArray[i]) != CPP_STRING_FIND_RESULT_FAIL_VALUE)
			{
				ignoreWord = true;
			}
		}

		int colourIndex = NLCI_EDITOR_DEFAULT_FONT_COLOUR;
		if(wordTag->entityReference != NULL)
		{
			colourIndex = NLCIoperations.processTextForNLChighlightWordDetermineColourIndex(wordTag->entityReference);
		}
		else
		{
			colourIndex = NLCIoperations.preprepreprocessTextForNLChighlightWordDetermineColourIndex(&word);
		}
		if(colourIndex == NLCI_EDITOR_DEFAULT_FONT_COLOUR)
		{
			ignoreWord = true;
		}

		if(!ignoreWord)
		{

			//cout << "word = " << word << endl;
			//cout << "colourIndex = " << colourIndex << endl;

			QTextCharFormat classFormat;
			classFormat.setForeground(NLCIoperations.generateColourQ(colourIndex));
			HighlightingRule rule;
			string patternString = "";
			patternString = patternString + "\\b" + word + "\\b";
			QString patternStringQ = convertStringToQString(patternString);
			rule.pattern = QRegExp(patternStringQ);
			rule.format = classFormat;
			highlightingRules->push_back(rule);
		}
	}
}






