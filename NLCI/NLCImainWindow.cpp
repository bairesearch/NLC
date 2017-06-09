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
 * File Name: NLCImainWindow.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2017 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler Interface
 * Project Version: 2c1e 01-June-2017
 * Requirements: 
 *
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
	setWindowTitle(tr("NLCI"));
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
                tr("<b>NLCI</b> enables editing of natural language code along " \
		"with the real-time display of its semantic processing (GIA) " \
		"and generated C++ output</p>"));
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

void NLCImainWindowClass::openProject(QString projectFileNameFull, bool openFiles)
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
					openFile(fileNameFull, projectName, false);
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
		openFile(fileNameFull, projectName, true);
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
		if(fileNameFull == "")
		{
			fileNameFull = QFileDialog::getSaveFileName(this, tr("New nlc file"), NLCI_NLC_INPUT_FOLDER, "nlc files (*.nlc)");
		}

		if(!fileNameFull.isEmpty()) 
		{
			fileNameFull = addFileNameExtensionIfNecessary(fileNameFull, NLC_NATURAL_LANGUAGE_CODE_FILE_NAME_EXTENSION);
			
			QFile file(fileNameFull);
			if(file.open(QFile::WriteOnly | QFile::Text))
			{
				file.close();
				openFile(fileNameFull, projectName, false);
			}
		}

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
		openFile(fileNameFull, projectName, false);
		
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
#endif


void NLCImainWindowClass::openFile(QString fileNameFull, string projectFileNameFull, bool expectAssociatedFile)
{
	if(fileNameFull == "")
	{
		fileNameFull = QFileDialog::getOpenFileName(this, tr("Open File"), NLCI_INPUT_FOLDER, "nlc files (*.nlc)");
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
	textBox->setText("Welcome to NLCI (Natural Language Compiler Interface)");

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
	fileMenu->addAction(tr("&Open text file"), this, SLOT(openFile()));	
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
