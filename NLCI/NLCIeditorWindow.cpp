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
 * File Name: NLCIeditorWindow.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2017 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler Interface
 * Project Version: 2c1a 01-June-2017
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

#include "NLCIeditorWindow.hpp"
#include "NLCItextDisplayWindow.hpp"
#include "GIApreprocessor.hpp"


std::vector<NLCIeditorWindowClass*> editorWindowList;

NLCIeditorWindowClass::NLCIeditorWindowClass(QWidget *parent)
	: QMainWindow(parent)
{
	setupFileMenu();
	setupHelpMenu();
	setupEditor();
	
	#ifdef USE_NLCI
	projectName = "";
	#endif
	editorName = "";

	setCentralWidget(editor);
	setWindowTitle(tr("NLCI Editor"));
	
	translatorVariablesTemplate = new GIAtranslatorVariablesClass();
	#ifdef USE_NLCI
	translatorVariablesTemplate->firstNLCprepreprocessorSentenceInList = new GIApreprocessorSentence();
	#elif defined USE_GIAI
	translatorVariablesTemplate->firstGIApreprocessorSentenceInList = new GIApreprocessorSentence();
	#endif
}

void NLCIeditorWindowClass::about()
{
#ifdef COMPILE_NLCI
    QMessageBox::about(this, tr("About NLCI (Natural Language Compiler Interface)"),
                tr("<b>NLCI</b> enables editing of natural language code along " \
		"with the real-time display of its semantic processing (GIA)" \
		"and generated C++ output</p>"));
#elif defined COMPILE_GIAI
    QMessageBox::about(this, tr("About GIAI (General Intelligence Algorithm Interface)"),
                tr("<b>NLCI</b> enables editing of natural language code along " \
		"with the real-time display of its semantic processing (GIA)" \
		"</p>"));
#endif
}




void NLCIeditorWindowClass::setupEditor()
{
	QFont font;
	font.setFamily("Courier");
	font.setFixedPitch(true);
	font.setPointSize(10);

	editor = new QTextEdit;
	editor->setFont(font);

	highlighter = new NLCIeditorSyntaxHighlighterClass(editor->document());
	//syntaxHighlighter = new QSyntaxHighlighter(editor->document());
}

void NLCIeditorWindowClass::setupFileMenu()
{
	QMenu *fileMenu = new QMenu(tr("&File"), this);
	menuBar()->addMenu(fileMenu);

	fileMenu->addAction(tr("Pre&process"), this, SLOT(prepreprocessText()));	//just performs preprocessing and syntax highlighting based on wordnet word type lookups
	fileMenu->addAction(tr("P&rocess"), this, SLOT(processText()));
	fileMenu->addAction(tr("C&lose"), this, SLOT(close()), QKeySequence::Close);
}

void NLCIeditorWindowClass::setupHelpMenu()
{
	QMenu *helpMenu = new QMenu(tr("&Help"), this);
	menuBar()->addMenu(helpMenu);

	helpMenu->addAction(tr("&About"), this, SLOT(about()));
}

void NLCIeditorWindowClass::closeEvent(QCloseEvent *event)
{
	if(closeEditorWindow())
	{
		event->accept();
	}
	else
	{
		event->ignore();
	}
}

bool NLCIeditorWindowClass::closeEditorWindow()
{
	bool result = true;

	if(saveEditorWindow())
	{
		result = true;
		eraseFromWindowList(this);
	}

	return result;
}

bool NLCIeditorWindowClass::saveEditorWindow()
{
	bool result = true;

	if(!(editor->document()->isModified()))
	{
		result = true;
	}
	else
	{
		bool cancelExit = false;
		const QMessageBox::StandardButton ret = QMessageBox::warning(this, tr("Application"),
						   tr("The document has been modified.\n"
							  "Do you want to save your changes?"),
						   QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
		if(ret == QMessageBox::Save)
		{
			if(!saveFile(QString::fromStdString(editorName), editor->toPlainText()))	//.toAscii();
			{
				cancelExit = true;
				//qInfo("1cancelExit");
			}
			else
			{
				//qInfo("2acceptExit");
			}
		}
		else if(ret == QMessageBox::Cancel)
		{
			cancelExit = true;
			//qInfo("3cancelExit");
		}
		else
		{

		}

		result = !cancelExit;
	}

	return result;
}


bool NLCIeditorWindowClass::eraseFromWindowList(NLCIeditorWindowClass* editorWindowRef)
{
	bool result = false;
	std::vector<NLCIeditorWindowClass*>::iterator iter = std::find(editorWindowList.begin(), editorWindowList.end(), editorWindowRef);
	if(iter != editorWindowList.end())
	{
		result = true;
		editorWindowList.erase(iter);
		//qInfo("eraseFromWindowList");
	}
	return result;
}

void NLCIeditorWindowClass::addToWindowList(NLCIeditorWindowClass* editorWindowRef)
{
	editorWindowList.push_back(editorWindowRef);
}


bool NLCIeditorWindowClass::prepreprocessText()
{
	bool result = true;
	
	NLCIeditorOperations.prepreprocessTextForNLC(editor, &(highlighter->highlightingRules), translatorVariablesTemplate);

	return result;
}

bool NLCIeditorWindowClass::processText()
{
	bool result = true;
		
	//1. create a new text display window to show NLC/GIA prepreprocessed text (ie without modifications)
	NLCItextDisplayWindowClass* textDisplayWindow = new NLCItextDisplayWindowClass();
	textDisplayWindow->translatorVariablesTemplate = translatorVariablesTemplate;
	textDisplayWindow->textDisplayFileName = editorName;
	textDisplayWindow->resize(NLCI_TEXT_DISPLAY_WINDOW_WIDTH, NLCI_TEXT_DISPLAY_WINDOW_HEIGHT);
	textDisplayWindow->show();
	textDisplayWindow->addToWindowList(textDisplayWindow);
			
	bool displayLRPprocessedText = false;
	NLCItextDisplayOperations.processTextForNLC(textDisplayWindow->label, translatorVariablesTemplate, displayLRPprocessedText);
			
	return result;
}



string generateProjectFileContents()
{
	string projectFileContents = "";
	
	for(int i=0; i<editorWindowList.size(); i++)
	{
		NLCIeditorWindowClass* editorWindow = editorWindowList[i];
		if(editorWindow->projectName != "")
		{
			QString editorFileNameFull = QString::fromStdString(editorWindow->editorName);
			QString editorFileName = getFileNameFromFileNameFull(editorFileNameFull);
			projectFileContents = projectFileContents + editorFileName.toStdString() + CHAR_NEWLINE;
		}
	}
	
	return projectFileContents;
}

bool closeEditorWindowsAll()
{
	bool result = true;
	
	for(int i=0; i<editorWindowList.size(); i++)
	{
		if(!(editorWindowList[i]->closeEditorWindow()))
		{
			result = false;
		}
	}
	
	return result;
}

bool saveEditorWindowsAll()
{
	bool result = true;
	
	for(int i=0; i<editorWindowList.size(); i++)
	{
		if(!(editorWindowList[i]->saveEditorWindow()))
		{
			result = false;
		}
	}
	
	return result;
}

QString getFileNameFromFileNameFull(QString fileNameFull)
{
	return QFileInfo(fileNameFull).fileName();
}

QString getPathFromFileNameFull(QString fileNameFull)
{
	return QFileInfo(fileNameFull).absolutePath();
}

bool generateNLCfunctionList(NLCfunction* firstNLCfunctionInList)
{
	bool result = true;
	
	NLCfunction* currentNLCfunctionInList = firstNLCfunctionInList;
	for(int i=0; i<editorWindowList.size(); i++)
	{
		NLCIeditorWindowClass* editorWindow = editorWindowList[i];
		if(editorWindow->projectName != "")
		{
			QString editorFileNameFull = QString::fromStdString(editorWindow->editorName);
			QString editorFileName = getFileNameFromFileNameFull(editorFileNameFull);
			
			//code copied from NLCmain::executeNLC();
			string NLCfunctionName = NLCmainClass().removeNLCfileNameExtension(editorFileName.toStdString());
			cout << "generateNLCfunctionList{}: NLCfunctionName = " << NLCfunctionName << endl;
			string functionName = "";
			string functionOwnerName = "";
			bool hasFunctionOwnerClass = "";
			string functionObjectName = "";
			bool hasFunctionObjectClass = "";
			NLCitemClassClass().parseFunctionNameFromNLCfunctionName(NLCfunctionName, &functionName, &functionOwnerName, &hasFunctionOwnerClass, &functionObjectName, &hasFunctionObjectClass);
			string NLCfunctionHeader = NLCitemClassClass().generateNLCfunctionHeader(functionName, functionOwnerName, hasFunctionOwnerClass, functionObjectName, hasFunctionObjectClass);
			QString functionContentsQ = editorWindow->editor->toPlainText();	//.toAscii();
			string functionContents = functionContentsQ.toStdString();
			string functionText = NLCfunctionHeader + CHAR_NEWLINE + functionContents + CHAR_NEWLINE;	//not used
				
			//code copied from NLCpreprocessor::preprocessTextForNLC();			
			currentNLCfunctionInList->NLCfunctionName = NLCfunctionName;
			currentNLCfunctionInList->functionContentsRaw = functionContents;
			currentNLCfunctionInList->firstNLCprepreprocessorSentenceInList = new GIApreprocessorSentence();
			if(!GIApreprocessorClass().createPreprocessSentences(currentNLCfunctionInList->functionContentsRaw, currentNLCfunctionInList->firstNLCprepreprocessorSentenceInList, true))	//NB NLC interprets new lines as new sentences
			{
				result = false;
			}
			
			currentNLCfunctionInList->next = new NLCfunction();
			currentNLCfunctionInList = currentNLCfunctionInList->next;
		}
	}
	
	return result;
}

bool saveFile(const QString& fileName, const QString& fileContents)
{
	bool result = true;

	QFile file(fileName);

	if (!file.open(QFile::WriteOnly | QFile::Text))
	{
		QString errorMessage = "Cannot write file " + fileName + ":\n" + file.errorString() + ".";
		QMessageBox::warning(NULL, "Application", errorMessage);
		result = false;
	}
	else
	{
		QTextStream out(&file);
	#ifndef QT_NO_CURSOR
		QApplication::setOverrideCursor(Qt::WaitCursor);
	#endif
		out << fileContents;
	#ifndef QT_NO_CURSOR
		QApplication::restoreOverrideCursor();
	#endif
	}

	return result;
}







