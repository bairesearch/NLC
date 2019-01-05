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
 * File Name: NLCImainWindow.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2018 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler Interface
 * Project Version: 2f11a 20-April-2018
 * Requirements: 
 * /
 *******************************************************************************/


#ifndef NLCI_MAIN_WINDOW
#define NLCI_MAIN_WINDOW

#include "NLCIglobalDefs.hpp"
#include "NLCIeditorSyntaxHighlighter.hpp"
#include "NLCIoperations.hpp"

#include <QMainWindow>

class QTextEdit;
class QLabel;
class QScrollArea;

class NLCImainWindowClass : public QMainWindow
{
	Q_OBJECT

public:
	NLCImainWindowClass(QWidget *parent = 0);

public slots:
	void about();
	
	//#ifdef USE_NLCI
	void createNewProject(QString projectFileNameFull = "");
	void selectProject(QString projectFileNameFull = "");
	void openProjectAssociatedFile(QString fileNameFull = "");
	void addNewFileToProject(QString fileNameFull = "");
	void openProject(QString projectFileNameFull = "", const bool openFiles = true);	
	void addExistingFileToProject(QString fileNameFull = "");
	void compileProject();
	void compileGeneratedCppProjectCode();
	void runGeneratedCppProjectCode();
	
	void saveProject();
	void closeProject();
	//#endif
	//#ifdef USE_GIAI
	void openTextFile(QString fileNameFull = "");
	void openTextQueryFile(QString fileNameFull = "");
	void createNewTextFile(QString fileNameFull = "");
	void createNewTextQueryFile(QString fileNameFull = "");
	bool performQuery();
	//#endif
	
	void createNewFile(QString fileNameFull = "", const bool isQuery = false);
	void openFile(QString fileNameFull = "", string projectFileNameFull = "", const bool expectAssociatedFile = false, const bool isQuery = false);

private:
	NLCIoperationsClass NLCIoperations;

	void setupTextBrowser();
	void setupFileMenu();
	void setupHelpMenu();

	void closeEvent(QCloseEvent *e);

	QString addFileNameExtensionIfNecessary(const QString fileName, const string extensionToAddIfNecessary);
	string addFileNameExtensionIfNecessary(const string fileName, const string extensionToAddIfNecessary);
	bool findFileNameExtension(const string fileName, const string extensionToFind);
	string generateProjectFileContents();
	
	bool projectOpened;
	string projectName;

	//QLabel* textBrowser;
	QTextEdit* textBox;
	

};

#endif
