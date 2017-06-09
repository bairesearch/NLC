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
 * Project Version: 2c1d 01-June-2017
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


vector<NLCIeditorWindowClass*> editorWindowList;

NLCIeditorWindowClass::NLCIeditorWindowClass(QWidget *parent): QMainWindow(parent)
{
	setupFileMenu();
	setupHelpMenu();
	setupEditor();
	
	#ifdef USE_NLCI
	projectName = "";
	#endif
	editorName = "";
	isPreprocessed = false;

	//single line update functions
	editorCursorLineNumber = 0;
	textChangedSinceListCursorMovement = false;

	setCentralWidget(editor);
	setWindowTitle(tr("NLCI Editor"));
	
	/*
	//these are reinitialised everytime the preprocessor is called
	#ifdef USE_NLCI
	firstNLCfunctionInList = new NLCfunction();
	#elif defined USE_GIAI
	translatorVariablesTemplate = new GIAtranslatorVariablesClass();
	translatorVariablesTemplate->firstGIApreprocessorSentenceInList = new GIApreprocessorSentence();	
	#endif
	*/
}



void NLCIeditorWindowClass::textChangedFunction()
{
	//cout << "textChangedFunction" << endl;
	textChangedSinceListCursorMovement = true;
}


void NLCIeditorWindowClass::cursorPositionChangedFunction()
{
	//update editorCursorLineNumber to new position:
	QTextEdit *edit = qobject_cast<QTextEdit*>(sender());
	Q_ASSERT(edit);
	QTextCursor cursor = edit->textCursor();
	cursor.movePosition(QTextCursor::StartOfLine);

	int lines = 0;
	while(cursor.positionInBlock()>0)
	{
		cursor.movePosition(QTextCursor::Up);
		lines++;
	}
	QTextBlock block = cursor.block().previous();

	while(block.isValid())
	{
		lines += block.lineCount();
		block = block.previous();
	}

	if(lines != editorCursorLineNumber)
	{
		//cout << "cursorPositionChangedFunction" << endl;
		//reprocess line at last cursor position:
		if(isPreprocessed && textChangedSinceListCursorMovement)
		{
			preprepreprocessTextLine(false);
			textChangedSinceListCursorMovement = false;
		}

		editorCursorLineNumber = lines;
	}
	//cout << "on_editor_cursorPositionChanged(): editorCursorLineNumber = " << editorCursorLineNumber << endl;
}

void NLCIeditorWindowClass::about()
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
		"</p>"));
#endif
}


bool NLCIeditorWindowClass::save()
{
	return saveEditorWindowSimple();
}

bool NLCIeditorWindowClass::preprepreprocessText()
{
	bool result = true;

	//cout << "preprepreprocessText:" << endl;

	if(!isPreprocessed || editor->document()->isModified())
	{
		closeTextDisplayWindowsAll();
		isPreprocessed = true;
		#ifdef USE_NLCI
		firstNLCfunctionInList = new NLCfunction();
		if(!NLCIeditorOperations.preprepreprocessTextForNLC(editor, &(highlighter->highlightingRules), firstNLCfunctionInList))
		#elif defined USE_GIAI
		translatorVariablesTemplate = new GIAtranslatorVariablesClass();
		translatorVariablesTemplate->firstGIApreprocessorSentenceInList = new GIApreprocessorSentence();
		if(!NLCIeditorOperations.preprepreprocessTextForNLC(editor, &(highlighter->highlightingRules), translatorVariablesTemplate))
		#endif
		{
			result = false;
		}

		highlighter->rehighlight();
	}

	return result;
}

void NLCIeditorWindowClass::preprepreprocessTextLine(bool enterWasPressed)
{
	bool result = true;
	if(isPreprocessed)
	{
		int lineIndex = editorCursorLineNumber;
		/*
		if(enterWasPressed)
		{
			lineIndex = lineIndex - 1;	//reprocess the text on the previous line
		}
		*/

		//cout << "preprepreprocessTextForNLCsingleLine; lineIndex = " << lineIndex << endl;

		if(!NLCIeditorOperations.preprepreprocessTextForNLCsingleLine(editor, &(highlighter->highlightingRules), firstNLCfunctionInList, editorCursorLineNumber))
		{
			result = false;
		}
		highlighter->rehighlight();
	}
}

bool NLCIeditorWindowClass::processText()
{
	bool result = true;

	isPreprocessed = false;
	preprepreprocessText();
	
	#ifdef USE_NLCI
	NLCfunction* currentNLCfunctionInList = firstNLCfunctionInList;
	while(currentNLCfunctionInList->next != NULL)
	{
		//cout << "currentNLCfunctionInList:" << endl;
		if(!createNewTextDisplayWindow(currentNLCfunctionInList))
		{
			result = false;
		}
		currentNLCfunctionInList = currentNLCfunctionInList->next;
	}	
	#elif defined USE_GIAI
	if(!createNewTextDisplayWindow(NULL))
	{
		result = false;
	}
	#endif
	
	return result;
}

bool NLCIeditorWindowClass::createNewTextDisplayWindow(NLCfunction* activeNLCfunctionInList)
{
	//1. create a new text display window to show NLC/GIA prepreprocessed text (ie without modifications)
	NLCItextDisplayWindowClass* textDisplayWindow = new NLCItextDisplayWindowClass();
	#ifdef USE_NLCI
	textDisplayWindow->activeNLCfunctionInList = activeNLCfunctionInList;
	textDisplayWindow->textDisplayFileName = activeNLCfunctionInList->NLCfunctionName;	//NLCitemClass.parseFunctionNameFromNLCfunctionName(activeNLCfunctionInList->NLCfunctionName);
	#elif defined USE_GIAI
	textDisplayWindow->translatorVariablesTemplate = translatorVariablesTemplate;
	textDisplayWindow->textDisplayFileName = getFileNameFromFileNameFull(editorName);
	#endif
	string textDisplayWindowName = textDisplayWindow->textDisplayFileName;
	textDisplayWindow->setWindowTitle(convertStringToQString(textDisplayWindowName));
	textDisplayWindow->resize(NLCI_TEXT_DISPLAY_WINDOW_WIDTH, NLCI_TEXT_DISPLAY_WINDOW_HEIGHT);
	textDisplayWindow->show();
	textDisplayWindow->addToWindowList(textDisplayWindow);

	bool displayLRPprocessedText = false;
	#ifdef USE_NLCI
	NLCItextDisplayOperations.processTextForNLC(textDisplayWindow->textBrowser, textDisplayWindow->translatorVariablesTemplate, activeNLCfunctionInList, displayLRPprocessedText);
	#else
	NLCItextDisplayOperations.processTextForNLC(textDisplayWindow->textBrowser, textDisplayWindow->translatorVariablesTemplate, displayLRPprocessedText);
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

	connect(editor, SIGNAL(textChanged()), this, SLOT(textChangedFunction()));
	connect(editor, SIGNAL(cursorPositionChanged()), this, SLOT(cursorPositionChangedFunction()));
}

void NLCIeditorWindowClass::setupFileMenu()
{
	QMenu *fileMenu = new QMenu(tr("&File"), this);
	menuBar()->addMenu(fileMenu);

	fileMenu->addAction(tr("Save"), this, SLOT(save()), QKeySequence::Save);
	fileMenu->addAction(tr("Preprepre&process"), this, SLOT(preprepreprocessText()));	//just performs preprocessing and syntax highlighting based on wordnet word type lookups
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
			if(!saveFile(convertStringToQString(editorName), editor->toPlainText()))	//.toAscii();
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

		editor->document()->setModified(false);

		result = !cancelExit;
	}

	return result;
}

bool NLCIeditorWindowClass::saveEditorWindowSimple()
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
						   QMessageBox::Save | QMessageBox::Cancel);
		if(ret == QMessageBox::Save)
		{
			if(!saveFile(convertStringToQString(editorName), editor->toPlainText()))	//.toAscii();
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

		editor->document()->setModified(false);

		result = !cancelExit;
	}

	return result;
}


bool NLCIeditorWindowClass::eraseFromWindowList(NLCIeditorWindowClass* editorWindowRef)
{
	bool result = false;
	vector<NLCIeditorWindowClass*>::iterator iter = std::find(editorWindowList.begin(), editorWindowList.end(), editorWindowRef);
	if(iter != editorWindowList.end())
	{
		result = true;
		editorWindowList.erase(iter);
		//qDebug() << "eraseFromWindowList: editorWindowList size = " << editorWindowList.size();
	}
	return result;
}

void NLCIeditorWindowClass::addToWindowList(NLCIeditorWindowClass* editorWindowRef)
{
	editorWindowList.push_back(editorWindowRef);
	//qDebug() << "addToWindowList: editorWindowList size = " << editorWindowList.size();
}



bool closeEditorWindowsAll()
{
	bool result = true;
	
	//qDebug() << "closeEditorWindowsAll(): editorWindowList.size() = " << editorWindowList.size();
	bool stillWindowsToClose =  true;
	while(stillWindowsToClose)
	{	
		if(editorWindowList.size() > 0)
		{
			//qDebug() << "closeEditorWindowsAll(): editorWindowList[0] = ";
			if(!(editorWindowList[0]->close()))
			{
				result = false;
			}
		}
		else
		{
			stillWindowsToClose = false;
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

string getFileNameFromFileNameFull(const string fileNameFull)
{
	return convertQStringToString(getFileNameFromFileNameFull(convertStringToQString(fileNameFull)));
}
QString getFileNameFromFileNameFull(QString fileNameFull)
{
	return QFileInfo(fileNameFull).fileName();
}

string getPathFromFileNameFull(const string fileNameFull)
{
	return convertQStringToString(getPathFromFileNameFull(convertStringToQString(fileNameFull)));
}
QString getPathFromFileNameFull(QString fileNameFull)
{
	return QFileInfo(fileNameFull).absolutePath();
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



