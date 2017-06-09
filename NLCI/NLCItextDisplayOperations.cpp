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
 * Project Version: 2c1f 01-June-2017
 * Requirements: 
 *
 *******************************************************************************/

#include "NLCItextDisplayOperations.hpp"
#include "GIApreprocessor.hpp"
#include "GIAdraw.hpp"
#include "LDreferenceClass.hpp"


#ifdef USE_NLCI
bool NLCItextDisplayOperationsClass::processTextForNLC(QTextBrowser* textBrowser, GIAtranslatorVariablesClass* translatorVariablesTemplate, NLCfunction* activeNLCfunctionInList, bool displayLRPprocessedText)
{
	bool result = true;
	
	NLCfunction* backupOfNextFunctionInList = activeNLCfunctionInList->next;
	activeNLCfunctionInList->next = new NLCfunction();	//this is to prevent executeNLC from executing multiple functions in the list
	if(!NLCIoperations.executeNLCwrapper(translatorVariablesTemplate, activeNLCfunctionInList))
	{
		result = false;
	}
	activeNLCfunctionInList->next = backupOfNextFunctionInList;
	if(!processTextForNLChighlight(textBrowser, activeNLCfunctionInList->firstNLCprepreprocessorSentenceInList, displayLRPprocessedText, activeNLCfunctionInList->functionIndexTemp))
	{
		result = false;
	}

	return result;
}
#elif defined USE_GIAI
bool NLCItextDisplayOperationsClass::processTextForNLC(QTextBrowser* textBrowser, GIAtranslatorVariablesClass* translatorVariablesTemplate, bool displayLRPprocessedText)
{
	bool result = true;
	
	if(!NLCIoperations.executeGIAwrapper(translatorVariablesTemplate, false))
	{
		result = false;
	}	
	if(!processTextForNLChighlight(textBrowser, translatorVariablesTemplate->firstGIApreprocessorSentenceInList, displayLRPprocessedText, 0))
	{
		result = false;
	}

	return result;
}
#endif

bool NLCItextDisplayOperationsClass::processTextForNLChighlight(QTextBrowser* textBrowser, GIApreprocessorSentence* firstNLCprepreprocessorSentenceInList, bool displayLRPprocessedText, const int functionIndex)
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

		//prepend indentation (tabulation currently set to 8 characters)
		string indentationHTML = "";
		for(int i=0; i<currentNLCprepreprocessorSentenceInList->indentation; i++)
		{
			indentationHTML = indentationHTML + "&nbsp;" + "&nbsp;" + "&nbsp;" + "&nbsp;" + "&nbsp;" + "&nbsp;" + "&nbsp;" + "&nbsp;";
		}
		htmlSource = htmlSource + indentationHTML;

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
				if(i == wordIndex)
				{
					GIApreprocessorWord* wordTag = (*sentence)[i];
					*wordTagFound = wordTag;
					result = true;
				}
			}
		}

		currentNLCprepreprocessorSentenceInList = currentNLCprepreprocessorSentenceInList->next;
		currentSentenceIndex++;
	}

	return result;
}
	
						









