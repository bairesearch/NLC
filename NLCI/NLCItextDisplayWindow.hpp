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
 * File Name: NLCItextDisplayWindow.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2019 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler Interface
 * Project Version: 2m7a 11-September-2020
 * Requirements: 
 * /
 *******************************************************************************/


#ifndef NLCI_TEXT_DISPLAY_WINDOW
#define NLCI_TEXT_DISPLAY_WINDOW

#include "NLCIglobalDefs.hpp"
#include "NLCItextDisplayOperations.hpp"
#include "GIAdraw.hpp"

#include <QMainWindow>

class QLabel;

class NLCItextDisplayWindowClass : public QMainWindow
{
	Q_OBJECT

public slots:
	void about();
	void linkActivated(const QUrl &link);
	//#ifdef USE_GIAI
	bool displayPreprocessedText();
	bool displaySemanticNetwork();
	//#endif
		bool displaySemanticNetwork(int sentenceIndex, GIAentityNode* entityReference);
	//bool displayNLPoutput();

public:
	NLCItextDisplayWindowClass(QWidget *parent = 0);

	string textDisplayFileName;
	GIAtranslatorVariablesClass* translatorVariablesTemplate;
	#ifdef USE_NLCI
	NLCfunction* activeNLCfunctionInList;
	#endif

	QTextBrowser* textBrowser;
	
	bool closeTextDisplayWindow();
	bool eraseFromWindowList(NLCItextDisplayWindowClass* textDisplayWindowRef);
	void addToWindowList(NLCItextDisplayWindowClass* textDisplayWindowRef);

private:
	GIAdrawClass GIAdraw;
	NLCItextDisplayOperationsClass NLCItextDisplayOperations;
	SHAREDvarsClass SHAREDvars;
	
	void setupTextBrowser();
	void setupFileMenu();
	void setupHelpMenu();

	//NLCIeditorSyntaxHighlighterClass *highlighter;
	//QSyntaxHighlighter* syntaxHighlighter;
	
	void closeEvent(QCloseEvent *e);
};

bool closeTextDisplayWindowsAll();

#endif
