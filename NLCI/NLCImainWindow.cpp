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
 * File Name: NLCImainWindow.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2018 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler Interface
 * Project Version: 2f8a 18-April-2018
 * Requirements: 
 * /
 *******************************************************************************/


#include <QtWidgets>

#include "NLCImainWindow.hpp"
#include "NLCIeditorWindow.hpp"


vector<string> projectNLCfilesList;

NLCImainWindowClass::NLCImainWindowClass(QWidget *parent)
	: QMainWindow(parent)
{
	setupFileMenu();
	setupHelpMenu();
	setupTextBrowser();
	
	projectOpened = false;
	projectName = "";

	setCentralWidget(textBox);
	setWindowTitle(tr(NLCI_MAIN_WINDOW_TITLE));
	
}

void NLCImainWindowClass::about()
{
#ifdef USE_NLCI
    QMessageBox::about(this, tr("About NLCI (Natural Language Compiler Interface)"),
                tr("<b>NLCI</b> enables editing of natural language code along " \
		"with the real-time display of its semantic processing (GIA) " \
		"and generated C++ output</p>"));
#elif defined USE_GIAI
	QMessageBox::about(this, tr("About GIAI (General Intelligence Algorithm Interface)"),
				tr("<b>GIAI</b> enables editing of natural language text along " \
		"with the real-time display of its semantic processing (GIA) " \
		"</p>"));
#endif
}


#ifdef USE_NLCI
void NLCImainWindowClass::createNewProject(QString projectFileNameFull)
{
	if(projectFileNameFull != "")
	{
		closeProject();
	}

	if(projectFileNameFull == "")
	{
		projectFileNameFull = QFileDialog::getSaveFileName(this, tr("New nlc project file"), NLCI_NLC_INPUT_FOLDER, "nlc project files (*.nlcp)");
	}
	
	if(!projectFileNameFull.isEmpty()) 
	{
		projectFileNameFull = addFileNameExtensionIfNecessary(projectFileNameFull, NLC_NATURAL_LANGUAGE_CODE_PROJECT_FILE_NAME_EXTENSION);
		
		QFile file(projectFileNameFull);
		if(file.open(QFile::WriteOnly | QFile::Text))
		{
			file.close();			
			projectName = convertQStringToString(projectFileNameFull);	//sets the mainWindow project name (only 1 project can be opened)
		}
	}
}

void NLCImainWindowClass::openProject(QString projectFileNameFull, const bool openFiles)
{
	if(projectFileNameFull != "")
	{
		closeProject();
	}
	
	//qDebug() << "NLCI_NLC_INPUT_FOLDER = " << NLCI_NLC_INPUT_FOLDER;
	
	if(projectFileNameFull == "")
	{
		projectFileNameFull = QFileDialog::getOpenFileName(this, tr("Open nlc project file"), NLCI_NLC_INPUT_FOLDER, "nlc project files (*.nlcp)");
	}
	
	if(!projectFileNameFull.isEmpty()) 
	{
		QFile file(projectFileNameFull);
		if(file.open(QFile::ReadOnly | QFile::Text))
		{
			QString fileContentQ = file.readAll();
			string fileContent = convertQStringToString(fileContentQ);
			file.close();
			
			QString projectFileNamePath = getPathFromFileNameFull(projectFileNameFull);
			QString projectFileName = getFileNameFromFileNameFull(projectFileNameFull);
			
			projectName = convertQStringToString(projectFileNameFull);	//sets the mainWindow project name (only 1 project can be opened)
			
			vector<string> fileNameList;
			int numberOfInputFilesInList = 0;
			if(!SHAREDvarsClass().getLinesFromFile(&fileContent, &fileNameList, &numberOfInputFilesInList))
			{
				cout << "NLCImainWindowClass::openProject{} error: !getLinesFromFile: content source = " << projectName << endl;
			}
				
			for(int i=0; i<numberOfInputFilesInList; i++)
			{
				QString fileNameFull = projectFileNamePath + "/" + convertStringToQString(fileNameList[i]);
				if(openFiles)
				{
					openFile(fileNameFull, projectName, false, false);
				}
				else
				{
					#ifdef NLCI_PROJECT_NLC_FILE_LIST_STORE_FULL_PATHS
					string fileName = convertQStringToString(fileNameFull);
					#else
					string fileName = getFileNameFromFileNameFull(convertQStringToString(fileNameFull));
					#endif
					projectNLCfilesList.push_back(fileName);
				}
			}
		}
	}
}

void NLCImainWindowClass::selectProject(QString projectFileNameFull)
{
	openProject(projectFileNameFull, false);
}

void NLCImainWindowClass::openProjectAssociatedFile(QString fileNameFull)
{
	if(projectName != "")
	{
		openFile(fileNameFull, projectName, true, false);
	}
	else
	{
		cout << "NLCImainWindowClass::openProjectAssociatedFile{} warning: project not open or selected" << endl;
	}
}


void NLCImainWindowClass::addNewFileToProject(QString fileNameFull)
{
	if(projectName != "")
	{
		createNewFile(fileNameFull, false);

		saveProject();
	}
	else
	{
		cout << "NLCImainWindowClass::addNewFileToProject{} warning: project not open or selected" << endl;
	}
}

void NLCImainWindowClass::addExistingFileToProject(QString fileNameFull)
{
	if(projectName != "")
	{
		openFile(fileNameFull, projectName, false, false);
		
		saveProject();
	}
	else
	{
		cout << "NLCImainWindowClass::addExistingFileToProject{} warning: project not open or selected" << endl;
	}
}

void NLCImainWindowClass::compileProject()
{
	bool result = true;
	if(projectName != "")
	{	
		bool useNLCinputFileList = true;
		string NLCinputFileListName = getFileNameFromFileNameFull(projectName);
		cout << "compileProject(): NLCinputFileListName = " << NLCinputFileListName << endl;
		GIAtranslatorVariablesClass translatorVariablesTemplate;	//global (project level) translatorVariablesTemplate will be disgarded
		if(!NLCIoperations.executeNLCwrapper(&translatorVariablesTemplate, useNLCinputFileList, NLCinputFileListName))
		{
			result = false;
		}
		else
		{
			string outputDisplayText = string("compileProject output:\n\n") + translatorVariablesTemplate.nlcGeneratedCode;
			textBox->setText(convertStringToQString(outputDisplayText));
		}
	}
	else
	{
		cout << "NLCImainWindowClass::compileProject{} warning: project not open or selected" << endl;
	}
}

void NLCImainWindowClass::compileGeneratedCppProjectCode()
{
	if(projectName != "")
	{
		QProcess *process = new QProcess(this);
		string executableFolder = string(NLCI_NLC_OUTPUT_FOLDER);
		process->setWorkingDirectory(convertStringToQString(executableFolder));
		string executableFile = executableFolder + CHAR_FOLDER_DELIMITER + NLCI_NLC_EXE_NAME_COMPILE_NLC_LIBRARY_GENERATED;
		cout << "compileGeneratedCppProjectCode(): executableFile = " << executableFile << endl;
		process->start(convertStringToQString(executableFile));
		process->waitForFinished(-1); // will wait forever until finished
		QString stdout = process->readAllStandardOutput();
		QString stderr = process->readAllStandardError();
		textBox->setText(stdout + stderr);
	}
	else
	{
		cout << "NLCImainWindowClass::compileGeneratedCppProjectCode{} warning: project not open or selected" << endl;
	}
}

void NLCImainWindowClass::runGeneratedCppProjectCode()
{
	if(projectName != "")
	{
		QProcess *process = new QProcess(this);
		string executableFolder = string(NLCI_NLC_OUTPUT_FOLDER);
		process->setWorkingDirectory(convertStringToQString(executableFolder));
		string executableFile = executableFolder + CHAR_FOLDER_DELIMITER + NLCI_NLC_EXE_NAME_NLC_GENERATED_PROGRAM;
		cout << "runGeneratedCppProjectCode(): executableFile = " << executableFile << endl;
		process->start(convertStringToQString(executableFile));
		process->waitForFinished(-1); // will wait forever until finished
		QString stdout = process->readAllStandardOutput();
		QString stderr = process->readAllStandardError();
		textBox->setText(stdout + stderr);
	}
	else
	{
		cout << "NLCImainWindowClass::runGeneratedCppProjectCode{} warning: project not open or selected" << endl;
	}
}

void NLCImainWindowClass::saveProject()
{
	if(projectName != "")
	{
		saveEditorWindowsAll();
		string projectFileContents = generateProjectFileContents();
		QString projectFileContentsQ = convertStringToQString(projectFileContents);
		if(!saveFile(convertStringToQString(projectName), projectFileContentsQ))
		{
			cout << "NLCImainWindowClass::saveProject{} error: !saveFile: " << projectName << endl;
		}		
	}
	else
	{
		cout << "NLCImainWindowClass::saveProject{} warning: project not open or selected" << endl;
	}
}

void NLCImainWindowClass::closeProject()
{
	if(projectName != "")
	{
		projectName = "";
		closeEditorWindowsAll();
		projectNLCfilesList.clear();
	}
	else
	{
		cout << "NLCImainWindowClass::closeProject{} warning: project not open or selected" << endl;
	}
}
#else
void NLCImainWindowClass::createNewProject(QString projectFileNameFull)
{
}
void NLCImainWindowClass::openProject(QString projectFileNameFull, const bool openFiles)
{
}
void NLCImainWindowClass::selectProject(QString projectFileNameFull)
{
}
void NLCImainWindowClass::openProjectAssociatedFile(QString fileNameFull)
{
}
void NLCImainWindowClass::addNewFileToProject(QString fileNameFull)
{
}
void NLCImainWindowClass::addExistingFileToProject(QString fileNameFull)
{
}
void NLCImainWindowClass::compileProject()
{
}
void NLCImainWindowClass::compileGeneratedCppProjectCode()
{
}
void NLCImainWindowClass::runGeneratedCppProjectCode()
{
}
void NLCImainWindowClass::saveProject()
{
}
void NLCImainWindowClass::closeProject()
{
}
#endif

#ifdef USE_GIAI
void NLCImainWindowClass::openTextFile(QString fileNameFull)
{
	openFile(fileNameFull, "", false, false);
}
void NLCImainWindowClass::openTextQueryFile(QString fileNameFull)
{
	openFile(fileNameFull, "", false, true);
}
void NLCImainWindowClass::createNewTextFile(QString fileNameFull)
{
	createNewFile(fileNameFull, false);
}
void NLCImainWindowClass::createNewTextQueryFile(QString fileNameFull)
{
	createNewFile(fileNameFull, true);
}	
bool NLCImainWindowClass::performQuery()
{
	bool result = true;
	
	if((getEditorWindowText() != NULL) && (getEditorWindowTextQuery() != NULL))
	{
		getEditorWindowText()->preprepreprocessText(false);
		getEditorWindowTextQuery()->preprepreprocessText(false);
		
		if(!NLCIoperations.executeGIAwrapper(getEditorWindowText()->translatorVariablesTemplate, getEditorWindowTextQuery()->translatorVariablesTemplate, true))
		{
			result = false;
		}
		else
		{
			string outputDisplayText = string("performQuery output:\n\n") + getEditorWindowText()->translatorVariablesTemplate->giaQueryAnswer;
			textBox->setText(convertStringToQString(outputDisplayText));	
			
			if(!getEditorWindowText()->createNewTextDisplayWindow(false))
			{
				result = false;
			}
			if(!getEditorWindowTextQuery()->createNewTextDisplayWindow(false))
			{
				result = false;
			}
	
			getEditorWindowText()->highlightText();
			getEditorWindowTextQuery()->highlightText();	
		}
	}
	else
	{
		if(getEditorWindowText() == NULL) 
		{
			cout << "editorWindowText{} warning: (editorWindowTextQuery == NULL)" << endl;
		}
		else if(getEditorWindowTextQuery() == NULL)
		{
			cout << "performQuery{} warning: (editorWindowTextQuery == NULL)" << endl;

		}
	}	

	return result;
}
#else
void NLCImainWindowClass::openTextFile(QString fileNameFull)
{
}
void NLCImainWindowClass::openTextQueryFile(QString fileNameFull)
{
}
void NLCImainWindowClass::createNewTextFile(QString fileNameFull)
{
}
void NLCImainWindowClass::createNewTextQueryFile(QString fileNameFull)
{
}
bool NLCImainWindowClass::performQuery()
{
	bool result = true;
	return result;
}
#endif


void NLCImainWindowClass::createNewFile(QString fileNameFull, const bool isQuery)
{
	if(fileNameFull == "")
	{
		fileNameFull = QFileDialog::getSaveFileName(this, tr("New nlc file"), NLCI_INPUT_FOLDER, NLCI_FILE_TYPE_FILTER_NAME);
	}

	if(!fileNameFull.isEmpty()) 
	{
		fileNameFull = addFileNameExtensionIfNecessary(fileNameFull, NLCI_FILE_TYPE);
		
		QFile file(fileNameFull);
		if(file.open(QFile::WriteOnly | QFile::Text))
		{
			file.close();
			openFile(fileNameFull, projectName, false, isQuery);
		}
	}
}

void NLCImainWindowClass::openFile(QString fileNameFull, string projectFileNameFull, const bool expectAssociatedFile, const bool isQuery)
{
	if(fileNameFull == "")
	{
		fileNameFull = QFileDialog::getOpenFileName(this, tr("Open File"), NLCI_INPUT_FOLDER, NLCI_FILE_TYPE_FILTER_NAME);
	}
	
	if(!fileNameFull.isEmpty()) 
	{

		bool fileAssociatedWithProject = false;
		#ifdef NLCI_PROJECT_NLC_FILE_LIST_STORE_FULL_PATHS
		string fileName = convertQStringToString(fileNameFull);
		#else
		string fileName = getFileNameFromFileNameFull(convertQStringToString(fileNameFull));
		#endif
		vector<string>::iterator iter = std::find(projectNLCfilesList.begin(), projectNLCfilesList.end(), fileName);
		if(iter != projectNLCfilesList.end())
		{
			fileAssociatedWithProject = true;
		}

		if(expectAssociatedFile && !fileAssociatedWithProject)
		{
			cout << "openFile{} warning: expect associated file and file is not associated with the project (to avoid this warning user should select 'Add new/existing nlc file to project')" << endl;
		}
		else
		{
			QFile file(fileNameFull);
			if(file.open(QFile::ReadOnly | QFile::Text))
			{
				//create an editor window
				NLCIeditorWindowClass* editorWindow = new NLCIeditorWindowClass();
				editorWindow->editorName = convertQStringToString(fileNameFull);
				QString editorWindowName = getFileNameFromFileNameFull(fileNameFull);
				editorWindow->setWindowTitle(editorWindowName);
				editorWindow->resize(NLCI_EDITOR_WINDOW_WIDTH, NLCI_EDITOR_WINDOW_HEIGHT);
				editorWindow->show();

				#ifdef USE_NLCI
				if(projectFileNameFull != "")
				{
					editorWindow->projectName = projectFileNameFull;

					//add file to project list if not already added;
					if(!fileAssociatedWithProject)
					{
						projectNLCfilesList.push_back(fileName);
					}
					else
					{
						if(!expectAssociatedFile)
						{
							cout << "openFile{} warning: fileName already added to project (to avoid this warning user should select 'Open nlc project associated file')" << endl;
						}
					}
				}
				#endif

				editorWindow->editor->setPlainText(file.readAll());
				editorWindow->addToWindowList(editorWindow);
				
				#ifdef USE_GIAI
				if(isQuery)
				{
					setEditorWindowTextQuery(editorWindow);
				}
				else
				{
					setEditorWindowText(editorWindow);
				}
				#endif
			}
		}
	}
}


void NLCImainWindowClass::setupTextBrowser()
{
	/*
	textBrowser = new QLabel(mainWindowScrollArea);
	//textBrowser->setTextFormat(Qt::RichText);
	textBrowser->setText("Welcome");
	//textBrowser->setTextInteractionFlags(Qt::TextBrowserInteraction);
	*/


	textBox = new QTextEdit();
	textBox->setReadOnly(true);
	textBox->setText(NLCI_WELCOME_MESSAGE);

	/*
	QPalette* palette = new QPalette();
	palette->setColor(QPalette::Base, Qt::gray);
	palette->setColor(QPalette::Text, Qt::black);
	textBox->setPalette(*palette);
	*/
}

void NLCImainWindowClass::setupFileMenu()
{
	QMenu *fileMenu = new QMenu(tr("&File"), this);
	menuBar()->addMenu(fileMenu);

	#ifdef USE_NLCI
	fileMenu->addAction(tr("&Create new nlc project"), this, SLOT(createNewProject()));
	fileMenu->addAction(tr("&Select nlc project"), this, SLOT(selectProject()));
	fileMenu->addAction(tr("&Open nlc project associated file"), this, SLOT(openProjectAssociatedFile()));
	fileMenu->addAction(tr("&Open nlc project"), this, SLOT(openProject()));
	fileMenu->addAction(tr("&Add new nlc file to project"), this, SLOT(addNewFileToProject()));
	fileMenu->addAction(tr("&Add existing nlc file to project"), this, SLOT(addExistingFileToProject()));

	fileMenu->addAction(tr("&Compile nlc project"), this, SLOT(compileProject()));
	fileMenu->addAction(tr("&Compile Generated Cpp Project Code"), this, SLOT(compileGeneratedCppProjectCode()));
	fileMenu->addAction(tr("&Run Generated Cpp Project Code"), this, SLOT(runGeneratedCppProjectCode()));
	
	fileMenu->addAction(tr("&Save nlc project"), this, SLOT(saveProject()));
	fileMenu->addAction(tr("&Close nlc project"), this, SLOT(closeProject()));
	
	fileMenu->addAction(tr("&Open nlc file (without project)"), this, SLOT(openFile()));
	#elif defined USE_GIAI
	fileMenu->addAction(tr("&Open text file"), this, SLOT(openTextFile()));	
	fileMenu->addAction(tr("&Open text file (query)"), this, SLOT(openTextQueryFile()));	
	fileMenu->addAction(tr("&Create new text file"), this, SLOT(createNewTextFile()));	
	fileMenu->addAction(tr("&Create new text file (query)"), this, SLOT(createNewTextQueryFile()));
	fileMenu->addAction(tr("&Perform Query"), this, SLOT(performQuery()));
	#endif
	
	
	fileMenu->addAction(tr("E&xit"), qApp, SLOT(quit()), QKeySequence::Quit);
}

void NLCImainWindowClass::setupHelpMenu()
{
	QMenu *helpMenu = new QMenu(tr("&Help"), this);
	menuBar()->addMenu(helpMenu);

	helpMenu->addAction(tr("&About"), this, SLOT(about()));
}

void NLCImainWindowClass::closeEvent(QCloseEvent *event)
{
	if(closeEditorWindowsAll())
	{
		event->accept();
	}
	else
	{
		event->ignore();
	}
}

QString NLCImainWindowClass::addFileNameExtensionIfNecessary(const QString fileName, const string extensionToAddIfNecessary)
{
	return convertStringToQString(addFileNameExtensionIfNecessary(convertQStringToString(fileName), extensionToAddIfNecessary));
}

string NLCImainWindowClass::addFileNameExtensionIfNecessary(const string fileName, const string extensionToAddIfNecessary)
{
	string fileNameModified = fileName;
	if(!findFileNameExtension(fileName, extensionToAddIfNecessary))
	{
		fileNameModified = fileNameModified + extensionToAddIfNecessary;
	}
	return fileNameModified;
}

bool NLCImainWindowClass::findFileNameExtension(const string fileName, const string extensionToFind)
{
	bool foundExtension = false;
	int indexOfLastFileExtension = fileName.rfind(extensionToFind);
	if(indexOfLastFileExtension == fileName.length()-extensionToFind.length())
	{
		foundExtension = true;
	}
	return foundExtension;
}


string NLCImainWindowClass::generateProjectFileContents()
{
	string projectFileContents = "";
	for(int i=0; i<projectNLCfilesList.size(); i++)
	{
		#ifdef NLCI_PROJECT_NLC_FILE_LIST_STORE_FULL_PATHS
		QString editorFileNameFull = convertStringToQString(projectNLCfilesList[i]);
		QString editorFileName = getFileNameFromFileNameFull(editorFileNameFull);
		projectFileContents = projectFileContents + convertQStringToString(editorFileName) + CHAR_NEWLINE;
		#else
		projectFileContents = projectFileContents + projectNLCfilesList[i] + CHAR_NEWLINE;
		#endif
	}
	
	return projectFileContents;
}
