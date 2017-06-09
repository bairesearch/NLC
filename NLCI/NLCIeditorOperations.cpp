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
 * Project Version: 2c1b 01-June-2017
 * Requirements: 
 *
 *******************************************************************************/
 
/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "NLCIglobalDefs.hpp"
#include "NLCIeditorOperations.hpp"
#include "GIAdraw.hpp"
#include "LDreferenceClass.hpp"


#define GIA_DRAW_VERB_NODE_COLOUR (GIA_DRAW_ACTION_NODE_COLOUR)
#define GIA_DRAW_PREPOSITION_NODE_COLOUR (GIA_DRAW_CONDITION_NODE_COLOUR)
#define GIA_DRAW_ADVERB_NODE_COLOUR (GIA_DRAW_SUBSTANCE_QUALITY_NODE_COLOUR)
#define GIA_DRAW_ADJECTIVE_NODE_COLOUR (GIA_DRAW_SUBSTANCE_QUALITY_NODE_COLOUR)
#define GIA_DRAW_NOUN_NODE_COLOUR (GIA_DRAW_PROPERTY_NODE_COLOUR)


#include <QtWidgets>


#ifdef USE_NLCI
bool NLCIeditorOperationsClass::preprepreprocessTextForNLC(QTextEdit* editor, QVector<HighlightingRule>* highlightingRules, NLCfunction* firstNLCfunctionInList)
{
	bool result = true;
	
	QString textQ = editor->toPlainText();	//.toAscii();
	string text = convertQStringToString(textQ);

	bool interpretNewLinesAsNewSentences = true;	//NB NLC interprets new lines as new sentences

	int numberOfLinesInFile = 0;
	vector<string> fileLinesList;
	if(!SHAREDvars.getLinesFromFile(&text, &fileLinesList, &numberOfLinesInFile))
	{
		cout << "NLCIeditorOperationsClass::preprepreprocessTextForNLC{} error: !getLinesFromFile" << endl;
		exit(EXIT_ERROR);
	}
	bool detectedFunctions = false;
	int numberOfFunctionsInList = 0;
	vector<string> inputTextFileNameList;
	if(!NLCpreprocessor.preprocessTextForNLCextractFunctionsAndCreatePreprocessSentences(&fileLinesList, firstNLCfunctionInList, &detectedFunctions, &numberOfFunctionsInList, &inputTextFileNameList))
	{
		result = false;
	}
	NLCfunction* currentNLCfunctionInList = firstNLCfunctionInList;
	while(currentNLCfunctionInList->next != NULL)
	{
		if(!preprepreprocessTextForNLChighlightFast(editor, highlightingRules, currentNLCfunctionInList->firstNLCprepreprocessorSentenceInList))
		{
			result = false;
		}
		currentNLCfunctionInList = currentNLCfunctionInList->next;
	}
	
	return result;
}
#elif defined USE_GIAI
bool NLCIeditorOperationsClass::preprepreprocessTextForNLC(QTextEdit* editor, QVector<HighlightingRule>* highlightingRules, GIAtranslatorVariablesClass* translatorVariablesTemplate)
{
	bool result = true;
	
	QString textQ = editor->toPlainText();	//.toAscii();
	string text = convertQStringToString(textQ);

	bool interpretNewLinesAsNewSentences = false;
	
	if(!GIApreprocessor.createPreprocessSentences(text, translatorVariablesTemplate->firstGIAprepreprocessorSentenceInList, interpretNewLinesAsNewSentences))
	{
		result = false;
	}
	if(!preprepreprocessTextForNLChighlightFast(editor, highlightingRules, translatorVariablesTemplate->firstGIApreprocessorSentenceInList))
	{
		result = false;
	}
	
	return result;
}
#endif
bool NLCIeditorOperationsClass::preprepreprocessTextForNLChighlightFast(QTextEdit* editor, QVector<HighlightingRule>* highlightingRules, GIApreprocessorSentence* firstNLCpreprepreprocessorSentenceInList)
{
	bool result = true;
	
	#ifdef NLCI_EDITOR_HIGHLIGHT_HTML
	editor->clear();
	QTextCursor cursor(editor->textCursor());
	// textEdit->moveCursor( QTextCursor::End );
	#else
	QTextCursor cursor;
	#endif
	
	int line = 0;
	GIApreprocessorSentence* currentNLCpreprepreprocessorSentenceInList = firstNLCpreprepreprocessorSentenceInList;
	while(currentNLCpreprepreprocessorSentenceInList->next != NULL)
	{
		vector<GIApreprocessorWord*>* sentence = &(currentNLCpreprepreprocessorSentenceInList->sentenceContentsOriginal);
		if(!preprepreprocessTextForNLChighlightFastSentence(editor, highlightingRules, sentence, &cursor, true))
		{
			result = false;
		}

		currentNLCpreprepreprocessorSentenceInList = currentNLCpreprepreprocessorSentenceInList->next;
		line++;
	}
	
	return result;
}

#ifdef USE_NLCI
bool NLCIeditorOperationsClass::preprepreprocessTextForNLCsingleLine(QTextEdit* editor, QVector<HighlightingRule>* highlightingRules, NLCfunction* firstNLCfunctionInList, int lineIndex)
#elif defined USE_GIAI
bool NLCIeditorOperationsClass::preprepreprocessTextForNLCsingleLine(QTextEdit* editor, QVector<HighlightingRule>* highlightingRules, GIApreprocessorSentence* firstGIApreprocessorSentenceInList, int lineIndex)
#endif
{
	bool result = true;
	
	QTextDocument* textDocQ = editor->document();
	QTextBlock textBlockQ = textDocQ->findBlockByLineNumber(lineIndex);
	QString textQ = textBlockQ.text();
	string text = convertQStringToString(textQ);
	
	#ifdef USE_NLCI
	bool interpretNewLinesAsNewSentences = true;	//NB NLC interprets new lines as new sentences
	#elif defined USE_GIAI
	bool interpretNewLinesAsNewSentences = false;	//this implementation will not work as line detection won't match
	#endif
	
	GIApreprocessorSentence* modifiedNLCpreprepreprocessorSentenceInList = new GIApreprocessorSentence();
	if(!GIApreprocessor.createPreprocessSentences(text, modifiedNLCpreprepreprocessorSentenceInList, interpretNewLinesAsNewSentences))
	{
		result = false;
	}
	
	//now replace the sentence in the existing list;
	GIApreprocessorSentence* activeNLCprepreprocessorSentenceInList = NULL;
	int currentLineNumber = 0;
	bool foundActiveSentence = false;
	#ifdef USE_NLCI
	NLCfunction* currentNLCfunctionInList = firstNLCfunctionInList;
	NLCfunction* activeNLCfunctionInList = NULL;
	while(currentNLCfunctionInList->next != NULL)
	{
		currentLineNumber++;	//for function header
		if(getActiveSentenceInList(&currentLineNumber, currentNLCfunctionInList->firstNLCprepreprocessorSentenceInList, &activeNLCprepreprocessorSentenceInList, lineIndex))
		{
			foundActiveSentence = true;
			activeNLCfunctionInList = currentNLCfunctionInList;
		}

		currentNLCfunctionInList = currentNLCfunctionInList->next;
	}
	#elif defined USE_GIAI
	if(getActiveSentenceInList(&currentLineNumber, firstGIApreprocessorSentenceInList, &activeNLCprepreprocessorSentenceInList))
	{
		foundActiveSentence = true;
	}
	#endif
	
	if(foundActiveSentence)
	{
		//replace activeNLCprepreprocessorSentenceInList with modifiedNLCpreprepreprocessorSentenceInList
		activeNLCprepreprocessorSentenceInList->sentenceContentsOriginalText = modifiedNLCpreprepreprocessorSentenceInList->sentenceContentsOriginalText;
		activeNLCprepreprocessorSentenceInList->sentenceContentsOriginal = modifiedNLCpreprepreprocessorSentenceInList->sentenceContentsOriginal;
		activeNLCprepreprocessorSentenceInList->indentation = modifiedNLCpreprepreprocessorSentenceInList->indentation;
		if(activeNLCprepreprocessorSentenceInList->sentenceIndexOriginal != modifiedNLCpreprepreprocessorSentenceInList->sentenceIndexOriginal)
		{
			cout << "NLCIeditorOperationsClass::preprepreprocessTextForNLCsingleLine{} error: (activeNLCprepreprocessorSentenceInList->sentenceIndex != modifiedNLCpreprepreprocessorSentenceInList->sentenceIndex)" << endl;
		}
	}
	else
	{
		result = false;
	}

	if(!preprepreprocessTextForNLCsingleLineHighlightFast(editor, highlightingRules, activeNLCprepreprocessorSentenceInList, lineIndex, &textBlockQ))
	{
		result = false;
	}
	
	return result;
}

bool NLCIeditorOperationsClass::getActiveSentenceInList(int* currentLineNumber, GIApreprocessorSentence* firstNLCprepreprocessorSentenceInList, GIApreprocessorSentence** activeNLCprepreprocessorSentenceInList, const int lineIndex)
{
	bool result = false;
	
	GIApreprocessorSentence* currentNLCprepreprocessorSentenceInList = firstNLCprepreprocessorSentenceInList;
	while(currentNLCprepreprocessorSentenceInList->next != NULL)
	{
		if(*currentLineNumber == lineIndex)
		{
			*activeNLCprepreprocessorSentenceInList = currentNLCprepreprocessorSentenceInList;
			result = true;	
		}
		
		(*currentLineNumber) = (*currentLineNumber) + 1;
		currentNLCprepreprocessorSentenceInList = currentNLCprepreprocessorSentenceInList->next;
	}
	
	return result;
}
		
bool NLCIeditorOperationsClass::preprepreprocessTextForNLCsingleLineHighlightFast(QTextEdit* editor, QVector<HighlightingRule>* highlightingRules, GIApreprocessorSentence* currentNLCpreprepreprocessorSentenceInList, int lineIndex, QTextBlock* textBlockQ)
{
	bool result = true;
		
	#ifdef NLCI_EDITOR_HIGHLIGHT_HTML
	QTextCursor cursor = central_widget_TextEdit->textCursor();
	cursor.setPosition(textBlockQ->position());	
	//central_widget_TextEdit->setFocus();
	//central_widget_TextEdit->setTextCursor (text_cursor);
	textBlockQ->clear();
	#else
	QTextCursor cursor;
	#endif

	vector<GIApreprocessorWord*>* sentence = &(currentNLCpreprepreprocessorSentenceInList->sentenceContentsOriginal);
	if(!preprepreprocessTextForNLChighlightFastSentence(editor, highlightingRules, sentence, &cursor, true))
	{
		result = false;
	}
	
	return result;
}

/*
FUTURE; parse these;
	#ifdef GIA_PREPROCESSOR_RECORD_REFERENCES
	GIApreprocessorMultiwordReductionPlainTextWord* preprocessorUpperLevelWordReference;
	int preprocessorUpperLevelWordReferenceSize;	//number of words in preprocessor upper level phrase corresponding to preprocessor word
	GIApreprocessorMultiwordReductionPlainTextWord* preprocessorLowerLevelWordReference;
	#endif
*/


bool NLCIeditorOperationsClass::preprepreprocessTextForNLChighlightFastSentence(QTextEdit* editor, QVector<HighlightingRule>* highlightingRules, vector<GIApreprocessorWord*>* sentence, QTextCursor* cursor, bool useOriginalSpacing)
{
	int characterIndexFirst = 0;
	int charCount = 0;
	for(int i=0; i<sentence->size(); i++)
	{
		string spaceText = STRING_SPACE;
		GIApreprocessorWord* wordTag = (*sentence)[i];
		string word = wordTag->tagName;
		int colourIndex = preprepreprocessTextForNLChighlightFastWordDetermineColourIndex(&word);

		#ifdef NLCI_EDITOR_HIGHLIGHT_HTML
		int characterIndex = currentNLCpreprepreprocessorSentenceInList->characterIndexInSentenceContentsOriginalText;
		if(useOriginalSpacing)
		{
			if(i == 0)
			{
				characterIndexFirst = characterIndex;
			}
			else
			{
				for(int q=0; q<characterIndex-charCount; q++)
				{
					cursor->insertText(spaceText);
					charCount++;
				}
			}
		}
				
		QTextCharFormat format;
		//format.setFontWeight(QFont::DemiBold);
		QColor colour = generateColourQ(colourIndex);
		format.setForeground(QBrush(colour));
		cursor->setCharFormat(format);
		cursor->insertText(word);
		charCount = charCount + word.length();
		if(!useOriginalSpacing)
		{
			cursor->insertText(spaceText);
			charCount++;
		}
		#else

		QTextCharFormat classFormat;
		classFormat.setForeground(NLCIoperations.generateColourQ(colourIndex));
		HighlightingRule rule;
		string patternString = "";
		patternString = patternString + "\\b" + word + "\\b";
		QString patternStringQ = convertStringToQString(patternString);
		rule.pattern = QRegExp(patternStringQ);
		rule.format = classFormat;
		highlightingRules->push_back(rule);
		
		/*
		QTextCharFormat classFormat;
		classFormat.setForeground(generateColourQ(colourIndex));
		editorWindow.syntaxHighlighter->setFormat(characterIndex, word.size(), classFormat);
		*/	
		#endif
	}
}

int NLCIeditorOperationsClass::preprepreprocessTextForNLChighlightFastWordDetermineColourIndex(const string* word)
{
	int colourIndex = DAT_FILE_COLOUR_BLACK;
	int grammaticalBaseTenseForm = INT_DEFAULT_VALUE;
	if(GIApreprocessorMultiwordReduction.determineVerbCaseStandardWithAdditional(*word, &grammaticalBaseTenseForm))
	{
		colourIndex = GIA_DRAW_VERB_NODE_COLOUR;
	}
	else if(GIApreprocessorMultiwordReduction.determineIsPreposition(*word))
	{
		colourIndex = GIA_DRAW_PREPOSITION_NODE_COLOUR;
	}
	else if(GIApreprocessorMultiwordReduction.determineIsAdverb(*word))
	{
		colourIndex = GIA_DRAW_ADVERB_NODE_COLOUR;
	}
	else if(GIApreprocessorMultiwordReduction.determineIsAdjective(*word))
	{
		colourIndex = GIA_DRAW_ADJECTIVE_NODE_COLOUR;
	}
	else if(GIApreprocessorMultiwordReduction.determineIsNoun(*word))
	{
		colourIndex = GIA_DRAW_NOUN_NODE_COLOUR;
	}
	return colourIndex;
}





