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
	if(!LRPpreprocessorWordIdentification.initialiseLRP(lrpFolder, true))
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
    if(!LRPpreprocessor.createPreprocessSentences(text, translatorVariablesTemplate->LRPpreprocessorTranslatorVariables.firstLRPpreprocessorSentenceInList, interpretNewLinesAsNewSentences, splitMultisentenceLines))
	{
		result = false;
	}
	return result;
}
bool NLCIeditorOperationsClass::preprepreprocessTextForNLChighlightWrapper(QVector<HighlightingRule>* highlightingRules, GIAtranslatorVariablesClass* translatorVariablesTemplate)
{
	bool result = true;

	string lrpFolder = string(NLCI_LRP_FOLDER) + CHAR_FOLDER_DELIMITER;
	if(!LRPpreprocessorWordIdentification.initialiseLRP(lrpFolder, true))
	{
		result = false;
	}
	
    if(!preprepreprocessTextForNLChighlight(highlightingRules, translatorVariablesTemplate->LRPpreprocessorTranslatorVariables.firstLRPpreprocessorSentenceInList))
	{
		result = false;
	}
	return result;
}
#endif

bool NLCIeditorOperationsClass::preprepreprocessTextForNLChighlight(QVector<HighlightingRule>* highlightingRules, LRPpreprocessorSentence* firstNLCpreprepreprocessorSentenceInList)
{
	bool result = true;
	
	int line = 0;
	LRPpreprocessorSentence* currentNLCpreprepreprocessorSentenceInList = firstNLCpreprepreprocessorSentenceInList;
	while(currentNLCpreprepreprocessorSentenceInList->next != NULL)
	{
		vector<LRPpreprocessorPlainTextWord*>* sentence = &(currentNLCpreprepreprocessorSentenceInList->sentenceContentsOriginal);
		//cout << "currentNLCpreprepreprocessorSentenceInList->sentenceContentsOriginal = " << LRPpreprocessorWordClassObject.generateTextFromVectorWordList(&(currentNLCpreprepreprocessorSentenceInList->sentenceContentsOriginal)) << endl;
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
	
	LRPpreprocessorSentence* modifiedNLCpreprepreprocessorSentenceInList = new LRPpreprocessorSentence();
	if(!LRPpreprocessor.createPreprocessSentences(lineText, modifiedNLCpreprepreprocessorSentenceInList, interpretNewLinesAsNewSentences, splitMultisentenceLines))
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
		
bool NLCIeditorOperationsClass::preprepreprocessTextForNLCsingleLinehighlight(QVector<HighlightingRule>* highlightingRules, LRPpreprocessorSentence* currentNLCpreprepreprocessorSentenceInList, const int lineIndex)
{
	bool result = true;

	vector<LRPpreprocessorPlainTextWord*>* sentence = &(currentNLCpreprepreprocessorSentenceInList->sentenceContentsOriginal);
	//cout << "preprepreprocessTextForNLCsingleLinehighlight{}: currentNLCpreprepreprocessorSentenceInList->sentenceContentsOriginal = " << LRPpreprocessorWordClassObject.generateTextFromVectorWordList(&(currentNLCpreprepreprocessorSentenceInList->sentenceContentsOriginal)) << endl;
	if(!preprepreprocessTextForNLChighlightSentence(highlightingRules, sentence, true))
	{
		result = false;
	}
	
	return result;
}

bool NLCIeditorOperationsClass::preprepreprocessTextForNLChighlightSentence(QVector<HighlightingRule>* highlightingRules, vector<LRPpreprocessorPlainTextWord*>* sentence, const bool useOriginalSpacing)
{
	int characterIndexFirst = 0;
	int charCount = 0;
	for(int i=0; i<sentence->size(); i++)
	{
		string spaceText = STRING_SPACE;
		LRPpreprocessorPlainTextWord* wordTag = (*sentence)[i];
		string word = wordTag->tagName;

		bool ignoreWord = false;

        for(int i=0; i<LRP_NLP_NUMBER_OF_MATH_CHARACTERS; i++)
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






