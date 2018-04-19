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
 * File Name: NLCIeditorWindow.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2018 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler Interface
 * Project Version: 2f10a 19-April-2018
 * Requirements: 
 * /
 *******************************************************************************/


#ifndef NLCI_EDITOR_WINDOW
#define NLCI_EDITOR_WINDOW

#include "NLCIglobalDefs.hpp"
#include "NLCIeditorSyntaxHighlighter.hpp"
#include "NLCIeditorOperations.hpp"
#include "NLCItextDisplayOperations.hpp"
#include "NLCIoperations.hpp"
#ifdef USE_NLCI
#include "NLCpreprocessor.hpp"
#include "NLCmain.hpp"
#endif

#include <QMainWindow>


class NLCIeditorWindowClass : public QMainWindow
{
	Q_OBJECT

public slots:
	void textChangedFunction();
	void cursorPositionChangedFunction();
	//void on_editor_textChanged();
	//void on_editor_cursorPositionChanged();
	void about();
	bool save();
	bool preprepreprocessText(const bool highlight = true);
		void ensureTextEndsWithNewLineCharacter();
		bool highlightText();
	void preprepreprocessTextLine(const bool enterWasPressed);
	bool processText();
		#ifdef USE_NLCI
		bool createNewTextDisplayWindow(NLCfunction* activeNLCfunctionInList, const bool processText);
		#elif defined USE_GIAI
		bool createNewTextDisplayWindow(const bool processText);
		#endif

public:
	NLCIeditorWindowClass(QWidget *parent = 0);
	
	#ifdef USE_NLCI
	string projectName;
	#endif
	string editorName;
	bool isPreprocessed;

	//single line update functions
	int editorCursorLineNumber;
	bool textChangedSinceListCursorMovement;

	QTextEdit* editor;
	
	bool closeEditorWindow();
	bool saveEditorWindow(const bool simple = false);
	bool eraseFromWindowList(NLCIeditorWindowClass* editorWindowRef);
	void addToWindowList(NLCIeditorWindowClass* editorWindowRef);
	
	#ifdef USE_NLCI
	NLCfunction* firstNLCfunctionInList;
	#elif defined USE_GIAI
	GIAtranslatorVariablesClass* translatorVariablesTemplate;
	#endif	

private:
	NLCIeditorOperationsClass NLCIeditorOperations;
	NLCItextDisplayOperationsClass NLCItextDisplayOperations;
	#ifdef USE_NLCI
	NLCmainClass NLCmain;
	NLCitemClassClass NLCitemClass;
	#endif

	void setupEditor();
	void setupFileMenu();
	void setupHelpMenu();

	NLCIeditorSyntaxHighlighterClass *highlighter;
	//QSyntaxHighlighter* syntaxHighlighter;
	
	void closeEvent(QCloseEvent *e);
};

bool closeEditorWindowsAll();
bool saveEditorWindowsAll();
string getFileNameFromFileNameFull(const string fileNameFull);
	QString getFileNameFromFileNameFull(QString fileNameFull);
string getPathFromFileNameFull(const string fileNameFull);
	QString getPathFromFileNameFull(QString fileNameFull);
bool saveFile(const QString& fileName, const QString& fileContents);

#ifdef USE_GIAI
NLCIeditorWindowClass* getEditorWindowText();
NLCIeditorWindowClass* getEditorWindowTextQuery();
void setEditorWindowText(NLCIeditorWindowClass* editorWindowRef);
void setEditorWindowTextQuery(NLCIeditorWindowClass* editorWindowRef);
#endif

#endif
