 /*******************************************************************************
 *
 * License: GNU Affero General Public License version 3 (AGPLv3)
 *
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: NLCItextDisplayWindow.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2022 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler Interface
 * Project Version: 2p1a 05-June-2022
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
