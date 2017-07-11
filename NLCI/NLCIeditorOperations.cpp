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
 * File Name: NLCIeditorOperations.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2017 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler Interface
 * Project Version: 2d1a 10-July-2017
 * Requirements: 
 *
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
	if(!GIApreprocessorMultiwordReduction.initialiseLRP(lrpFolder, true))
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
	if(!GIApreprocessorMultiwordReduction.initialiseLRP(lrpFolder, true))
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
		vector<GIApreprocessorWord*>* sentence = &(currentNLCpreprepreprocessorSentenceInList->sentenceContentsOriginal);
		//cout << "currentNLCpreprepreprocessorSentenceInList->sentenceContentsOriginal = " << GIApreprocessorMultiwordReductionClassObject.generateTextFromVectorWordList(&(currentNLCpreprepreprocessorSentenceInList->sentenceContentsOriginal)) << endl;
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

	vector<GIApreprocessorWord*>* sentence = &(currentNLCpreprepreprocessorSentenceInList->sentenceContentsOriginal);
	//cout << "preprepreprocessTextForNLCsingleLinehighlight{}: currentNLCpreprepreprocessorSentenceInList->sentenceContentsOriginal = " << GIApreprocessorMultiwordReductionClassObject.generateTextFromVectorWordList(&(currentNLCpreprepreprocessorSentenceInList->sentenceContentsOriginal)) << endl;
	if(!preprepreprocessTextForNLChighlightSentence(highlightingRules, sentence, true))
	{
		result = false;
	}
	
	return result;
}

bool NLCIeditorOperationsClass::preprepreprocessTextForNLChighlightSentence(QVector<HighlightingRule>* highlightingRules, vector<GIApreprocessorWord*>* sentence, const bool useOriginalSpacing)
{
	int characterIndexFirst = 0;
	int charCount = 0;
	for(int i=0; i<sentence->size(); i++)
	{
		string spaceText = STRING_SPACE;
		GIApreprocessorWord* wordTag = (*sentence)[i];
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






