 /*******************************************************************************
 *
 * License: GNU Affero General Public License version 3 (AGPLv3)
 *
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: NLCImainWindow.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2022 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler Interface
 * Project Version: 2p1a 05-June-2022
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
