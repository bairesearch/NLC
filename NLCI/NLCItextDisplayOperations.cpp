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
 * File Name: NLCItextDisplayOperations.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2017 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler Interface
 * Project Version: 2c1c 01-June-2017
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

#include "NLCItextDisplayOperations.hpp"
#include "GIApreprocessor.hpp"
#include "GIAdraw.hpp"
#include "LDreferenceClass.hpp"


#ifdef USE_NLCI
bool NLCItextDisplayOperationsClass::processTextForNLC(QLabel* label, GIAtranslatorVariablesClass* translatorVariablesTemplate, NLCfunction* activeNLCfunctionInList, bool displayLRPprocessedText)
{
	bool result = true;
	
	if(!NLCIoperations.executeNLCwrapper(translatorVariablesTemplate, activeNLCfunctionInList))
	{
		result = false;
	}
	if(!processTextForNLChighlight(label, activeNLCfunctionInList->firstNLCprepreprocessorSentenceInList, displayLRPprocessedText, activeNLCfunctionInList->functionIndexTemp))
	{
		result = false;
	}

	return result;
}
#elif defined USE_GIAI
bool NLCItextDisplayOperationsClass::processTextForNLC(QLabel* label, GIAtranslatorVariablesClass* translatorVariablesTemplate, bool displayLRPprocessedText)
{
	bool result = true;
	
	if(!NLCIoperations.executeGIAwrapper(translatorVariablesTemplate, false))
	{
		result = false;
	}	
	if(!processTextForNLChighlight(label, translatorVariablesTemplate->firstGIApreprocessorSentenceInList, displayLRPprocessedText, 0))
	{
		result = false;
	}

	return result;
}
#endif

bool NLCItextDisplayOperationsClass::processTextForNLChighlight(QLabel* label, GIApreprocessorSentence* firstNLCprepreprocessorSentenceInList, bool displayLRPprocessedText, const int functionIndex)
{
	bool result = true;
	
	label->clear();

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

		if(!processTextForNLChighlightSentence(label, sentence, sentenceIndex, functionIndex))
		{
			result = false;
		}

		currentNLCprepreprocessorSentenceInList = currentNLCprepreprocessorSentenceInList->next;
		sentenceIndex++;
	}
	
	return result;
}

bool NLCItextDisplayOperationsClass::processTextForNLChighlightSentence(QLabel* label, vector<GIApreprocessorWord*>* sentence, const int sentenceIndex, const int functionIndex)
{
	bool result = true;

	int characterIndexFirst = 0;
	int charCount = 0;
	string lineHtmlText = "";

	for(int i=0; i<sentence->size(); i++)
	{
		GIApreprocessorWord* wordTag = (*sentence)[i];
		string word = wordTag->tagName;
		//int characterIndex = currentNLCprepreprocessorSentenceInList->characterIndexInSentenceContentsOriginalText;
	
		int colourIndex = processTextForNLChighlightWordDetermineColourIndex(wordTag->entityReference);
		QColor colour = NLCIoperations.generateColourQ(colourIndex);
		string colourHex = convertQStringToString(colour.name());
		
		string functionIndexString = SHAREDvars.convertIntToString(functionIndex);
		string sentenceIndexString = SHAREDvars.convertIntToString(sentenceIndex);
		string wordIndexString = SHAREDvars.convertIntToString(i);
		string link = functionIndexString + NLCI_URL_DELIMITER + sentenceIndexString + NLCI_URL_DELIMITER + wordIndexString;	//this format is important

		string wordHtmlText = "";
		if(wordTag->entityReference != NULL)
		{
			wordHtmlText = wordHtmlText + "<a href=\"" + link + " style=\"color:" + colourHex + " \">" + word + "</a>";
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

		lineHtmlText = lineHtmlText + wordHtmlText;

		/*
		QTextCharFormat classFormat;
		classFormat.setForeground(generateColourQ(colourIndex));
		editorWindow->syntaxHighlighter->setFormat(characterIndex, word.size(), classFormat);
		*/	
	}

	lineHtmlText = lineHtmlText + "<br />";

	QString wordHtmlTextQ = convertStringToQString(lineHtmlText);
	QString temp = label->text() + wordHtmlTextQ;
	label->setText(temp);

	return result;
}

int NLCItextDisplayOperationsClass::processTextForNLChighlightWordDetermineColourIndex(GIAentityNode* entity)
{
	int colourIndex = DAT_FILE_COLOUR_BLACK;
	if(entity != NULL)
	{
		if(entity->entityType == GIA_ENTITY_TYPE_NETWORK_INDEX)
		{
			colourIndex = GIA_DRAW_NETWORK_INDEX_NODE_COLOUR;	//error
		}
		else if(entity->entityType == GIA_ENTITY_TYPE_SUBSTANCE)
		{
			colourIndex = GIA_DRAW_SUBSTANCE_NODE_COLOUR;
		}
		else if(entity->entityType == GIA_ENTITY_TYPE_CONCEPT)
		{
			colourIndex = GIA_DRAW_CONCEPT_NODE_COLOUR;
		}
		else if(entity->entityType == GIA_ENTITY_TYPE_ACTION)
		{
			colourIndex = GIA_DRAW_ACTION_NODE_COLOUR;
		}
		else if(entity->entityType == GIA_ENTITY_TYPE_CONDITION)
		{
			colourIndex = GIA_DRAW_CONDITION_NODE_COLOUR;
		}
		else if(entity->entityType == GIA_ENTITY_TYPE_DEFINITION)
		{
			colourIndex = GIA_DRAW_DEFINITION_NODE_COLOUR;
		}
		else if(entity->entityType == GIA_ENTITY_TYPE_QUALITY)
		{
			colourIndex = GIA_DRAW_SUBSTANCE_QUALITY_NODE_COLOUR;
		}
		else if(entity->entityType == GIA_ENTITY_TYPE_PROPERTY)
		{
			colourIndex = GIA_DRAW_PROPERTY_NODE_COLOUR;
		}
	}
	return colourIndex;		
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
bool NLCItextDisplayOperationsClass::getWordByIndex(const int sentenceIndex, const int wordIndex, NLCfunction* activeNLCfunctionInList, GIApreprocessorWord** wordTagFound)
{
	return getWordByIndex(sentenceIndex, wordIndex, activeNLCfunctionInList->firstNLCprepreprocessorSentenceInList, wordTagFound);
}
#elif defined USE_GIAI
bool NLCItextDisplayOperationsClass::getWordByIndex(const int sentenceIndex, const int wordIndex, GIApreprocessorSentence* translatorVariablesTemplate, NLCfunction* NLCfunctionInList, GIApreprocessorWord** wordTagFound)
{
	return getWordByIndex(sentenceIndex, wordIndex,  translatorVariablesTemplate->firstGIApreprocessorSentenceInList, wordTagFound);
}
#endif
bool NLCItextDisplayOperationsClass::getWordByIndex(const int sentenceIndex, const int wordIndex, GIApreprocessorSentence* firstNLCprepreprocessorSentenceInList, GIApreprocessorWord** wordTagFound)
{
	bool result = false;

	int currentSentenceIndex = 0;
	GIApreprocessorSentence* currentNLCprepreprocessorSentenceInList = firstNLCprepreprocessorSentenceInList;
	while(currentNLCprepreprocessorSentenceInList->next != NULL)
	{
		if(sentenceIndex == currentSentenceIndex)
		{
			vector<GIApreprocessorWord*>* sentence = &(currentNLCprepreprocessorSentenceInList->sentenceContentsOriginal);
			for(int i=0; i<sentence->size(); i++)
			{
				GIApreprocessorWord* wordTag = (*sentence)[i];
				*wordTagFound = wordTag;
				result = true;
			}
		}

		currentNLCprepreprocessorSentenceInList = currentNLCprepreprocessorSentenceInList->next;
		currentSentenceIndex++;
	}

	return result;
}
	
						










