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
 * File Name: NLCIoperations.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2018 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler Interface
 * Project Version: 2f1b 22-February-2018
 * Requirements: 
 * /
 *******************************************************************************/


#ifndef NLCI_OPERATIONS
#define NLCI_OPERATIONS

#include "NLCIglobalDefs.hpp"
#include "SHAREDvars.hpp"
#include "LDreferenceClass.hpp"
#include "GIAtranslatorOperations.hpp"
#include "NLCpreprocessor.hpp"
#include "GIAdraw.hpp"

#include <QTextCharFormat>
#include <QTextEdit>

#define GIA_DRAW_VERB_NODE_COLOUR (GIA_DRAW_ACTION_NODE_COLOUR)
#define GIA_DRAW_PREPOSITION_NODE_COLOUR (GIA_DRAW_CONDITION_NODE_COLOUR)
#define GIA_DRAW_ADVERB_NODE_COLOUR (GIA_DRAW_SUBSTANCE_QUALITY_NODE_COLOUR)
#define GIA_DRAW_ADJECTIVE_NODE_COLOUR (GIA_DRAW_SUBSTANCE_QUALITY_NODE_COLOUR)
#define GIA_DRAW_NOUN_NODE_COLOUR (GIA_DRAW_PROPERTY_NODE_COLOUR)
#define NLCI_EDITOR_DEFAULT_FONT_COLOUR (DAT_FILE_COLOUR_BLACK)

#define NLCI_EDITOR_SYNTAX_HIGHLIGHTER_LOGICAL_CONDITION_COLOUR (DAT_FILE_COLOUR_DARKYELLOW)
#define NLCI_EDITOR_SYNTAX_HIGHLIGHTER_MATHTEXT_VARIABLE_TYPE_COLOUR (DAT_FILE_COLOUR_DARKYELLOW)

class HighlightingRule
{
public:
	QRegExp pattern;
	QTextCharFormat format;
};	

class NLCIoperationsClass
{
	//Q_OBJECT
public:
	GIApreprocessorMultiwordReductionClass GIApreprocessorMultiwordReduction;
	LDreferenceClassClass LDreferenceClass;

	QColor generateColourQ(int colourIndex);
		QColor generateColourQ(colour* col);	
	
	#ifdef USE_NLCI
	bool executeNLCwrapper(GIAtranslatorVariablesClass* translatorVariablesTemplate, const bool useNLCinputFileList, const string NLCinputFileListName);
	bool executeNLCwrapper(GIAtranslatorVariablesClass* translatorVariablesTemplate, NLCfunction* firstNLCfunctionInList);
		bool executeNLCwrapper(GIAtranslatorVariablesClass* translatorVariablesTemplate, NLCfunction* firstNLCfunctionInList, const bool useNLCinputFileList, const string NLCinputFileListName);
	#else
	bool executeGIAwrapper(GIAtranslatorVariablesClass* translatorVariablesTemplate, GIAtranslatorVariablesClass* translatorVariablesQuery, const bool query);
	#endif	
	
	int preprepreprocessTextForNLChighlightWordDetermineColourIndex(const string* word);
	int processTextForNLChighlightWordDetermineColourIndex(GIAentityNode* entity);

};

QString convertStringToQString(const string str);
string convertQStringToString(const QString qstr);
QString convertByteArrayToQString(const QByteArray& ba);



#endif
