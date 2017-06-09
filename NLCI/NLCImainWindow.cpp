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
 * Project Version: 2c1b 01-June-2017
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

#include <QtWidgets>

#include "NLCImainWindow.hpp"
#include "NLCIeditorWindow.hpp"


NLCImainWindowClass::NLCImainWindowClass(QWidget *parent)
	: QMainWindow(parent)
{
	setupFileMenu();
	setupHelpMenu();
	setupLabel();
	
	projectOpened = false;
	projectName = "";

	setCentralWidget(label);
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
	closeProject();
	
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

void NLCImainWindowClass::openProject(QString projectFileNameFull)
{
	closeProject();
	
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
				openFile(fileNameFull, projectName);
			}
		}
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
				openFile(fileNameFull, projectName);
			}
		}

		saveProject();
	}
}

void NLCImainWindowClass::addExistingFileToProject(QString fileNameFull)
{
	if(projectName != "")
	{
		openFile(fileNameFull, projectName);
	}
}

void NLCImainWindowClass::compileProject()
{
	bool result = true;
	if(projectName != "")
	{	
		bool useNLCinputFileList = true;
		string NLCinputFileListName = getFileNameFromFileNameFull(projectName);
		cout << "compileProject: NLCinputFileListName = " << NLCinputFileListName << endl;
		if(!NLCIoperations.executeNLCwrapper(useNLCinputFileList, NLCinputFileListName))
		{
			result = false;
		}
	}
}

void NLCImainWindowClass::compileGeneratedCppProjectCode()
{
	if(projectName != "")
	{
		QProcess *process = new QProcess(this);
		QString file = QString(NLCI_NLC_OUTPUT_FOLDER) + QString(NLCI_NLC_EXE_NAME_COMPILE_NLC_LIBRARY_GENERATED);
		process->start(file);
		process->waitForFinished(-1); // will wait forever until finished
		QString stdout = process->readAllStandardOutput();
		QString stderr = process->readAllStandardError();
		//label->setText(stdout);
		label->setText(stderr);
	}
}

void NLCImainWindowClass::runGeneratedCppProjectCode()
{
	if(projectName != "")
	{
		QProcess *process = new QProcess(this);
		QString file = QString(NLCI_NLC_OUTPUT_FOLDER) + QString(NLCI_NLC_EXE_NAME_NLC_GENERATED_PROGRAM);
		process->start(file);
		process->waitForFinished(-1); // will wait forever until finished
		QString stdout = process->readAllStandardOutput();
		QString stderr = process->readAllStandardError();
		//label->setText(stdout);
		label->setText(stderr);
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
}

void NLCImainWindowClass::closeProject()
{
	if(projectName != "")
	{
		projectName = "";
		closeEditorWindowsAll();
	}
}
#endif


void NLCImainWindowClass::openFile(QString fileNameFull, string projectFileNameFull)
{
	if(fileNameFull == "")
	{
		fileNameFull = QFileDialog::getOpenFileName(this, tr("Open File"), NLCI_INPUT_FOLDER, "nlc files (*.nlc)");
	}
	
	if(!fileNameFull.isEmpty()) 
	{
		QFile file(fileNameFull);
		if(file.open(QFile::ReadOnly | QFile::Text))
		{
			//create an editor window
			NLCIeditorWindowClass* editorWindow = new NLCIeditorWindowClass();
			editorWindow->editorName = convertQStringToString(fileNameFull);
			editorWindow->resize(640, 512);
			editorWindow->show();
			#ifdef USE_NLCI
			editorWindow->projectName = projectFileNameFull;
			#endif

			editorWindow->editor->setPlainText(file.readAll());
			editorWindow->addToWindowList(editorWindow);
		}
	}
}

void NLCImainWindowClass::setupLabel()
{
	QFont font;
	font.setFamily("Courier");
	font.setFixedPitch(true);
	font.setPointSize(10);

	label = new QLabel;
	//label->setTextFormat(Qt::RichText);
	//label->setTextInteractionFlags(Qt::TextBrowserInteraction);
}

void NLCImainWindowClass::setupFileMenu()
{
	QMenu *fileMenu = new QMenu(tr("&File"), this);
	menuBar()->addMenu(fileMenu);

	#ifdef USE_NLCI
	fileMenu->addAction(tr("&Create new nlc project"), this, SLOT(createNewProject()));
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


