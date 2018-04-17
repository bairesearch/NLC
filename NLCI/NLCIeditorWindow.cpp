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
 * Project Version: 2e3b 16-December-2017
 * Requirements: 
 *
 *******************************************************************************/

#include <QtWidgets>

#include "NLCIeditorWindow.hpp"
#include "NLCItextDisplayWindow.hpp"
#include "GIApreprocessor.hpp"


vector<NLCIeditorWindowClass*> editorWindowList;
#ifdef USE_GIAI
NLCIeditorWindowClass* editorWindowText = NULL;
NLCIeditorWindowClass* editorWindowTextQuery = NULL;
#endif

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


//CHECKTHIS: ensure that cursorPositionChangedFunction ignores textbox wrapping
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
				tr("<b>GIAI</b> enables editing of natural language text along " \
		"with the real-time display of its semantic processing (GIA) " \
		"</p>"));
#endif
}


bool NLCIeditorWindowClass::save()
{
	return saveEditorWindow(true);
}

bool NLCIeditorWindowClass::preprepreprocessText(const bool highlight)
{
	bool result = true;

	//cout << "preprepreprocessText:" << endl;

	closeTextDisplayWindowsAll();
	isPreprocessed = true;
	
	ensureTextEndsWithNewLineCharacter();
	
	#ifdef USE_NLCI
	firstNLCfunctionInList = new NLCfunction();
	if(!NLCIeditorOperations.preprepreprocessTextForNLC(editor, firstNLCfunctionInList))
	{
		result = false;
	}
	#elif defined USE_GIAI
	translatorVariablesTemplate = new GIAtranslatorVariablesClass();
	translatorVariablesTemplate->firstGIApreprocessorSentenceInList = new GIApreprocessorSentence();
	if(!NLCIeditorOperations.preprepreprocessTextForNLC(editor, translatorVariablesTemplate))
	{
		result = false;
	}
	#endif
	
	highlighter->reinitialiseSyntaxHighlighterRules();
	if(highlight)
	{
		if(!highlightText())
		{
			result = false;
		}
	}

	return result;
}

void NLCIeditorWindowClass::ensureTextEndsWithNewLineCharacter()
{
	//if necessary, insert a newline character at the end of the text window (this is required based on standardised definition of text files)
	QString textQ = editor->toPlainText();
	string text = convertQStringToString(textQ);
	if(text[text.length()-1] != CHAR_NEWLINE)
	{
		editor->append(convertStringToQString(""));
	}
}

bool NLCIeditorWindowClass::highlightText()
{
	bool result = true;
	#ifdef USE_NLCI
	if(!NLCIeditorOperations.preprepreprocessTextForNLChighlightWrapper(&(highlighter->highlightingRules), firstNLCfunctionInList))
	{
		result = false;
	}
	#elif defined USE_GIAI
	if(!NLCIeditorOperations.preprepreprocessTextForNLChighlightWrapper(&(highlighter->highlightingRules), translatorVariablesTemplate))
	{
		result = false;
	}
	#endif
	highlighter->rehighlight();
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

		if(!NLCIeditorOperations.preprepreprocessTextForNLCsingleLine(editor, &(highlighter->highlightingRules), editorCursorLineNumber))
		{
			result = false;
		}
		highlighter->rehighlight();
	}
}

bool NLCIeditorWindowClass::processText()
{
	bool result = true;

	preprepreprocessText(false);
	
	#ifdef USE_NLCI
	NLCfunction* currentNLCfunctionInList = firstNLCfunctionInList;
	while(currentNLCfunctionInList->next != NULL)
	{
		//cout << "currentNLCfunctionInList:" << endl;
		if(!createNewTextDisplayWindow(currentNLCfunctionInList, true))
		{
			result = false;
		}
		currentNLCfunctionInList = currentNLCfunctionInList->next;
	}	
	#elif defined USE_GIAI
	if(!createNewTextDisplayWindow(true))
	{
		result = false;
	}
	#endif

	//recalculate the syntax highlighting based on GIA parsed text
	if(!highlightText())
	{
		result = false;
	}

	return result;
}

#ifdef USE_NLCI
bool NLCIeditorWindowClass::createNewTextDisplayWindow(NLCfunction* activeNLCfunctionInList, const bool processText)
#elif defined USE_GIAI
bool NLCIeditorWindowClass::createNewTextDisplayWindow(const bool processText)
#endif
{
	bool result = true;
	
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
	if(!NLCItextDisplayOperations.processTextForNLC(textDisplayWindow->textBrowser, textDisplayWindow->translatorVariablesTemplate, activeNLCfunctionInList, displayLRPprocessedText, processText))
	#else
	if(!NLCItextDisplayOperations.processTextForNLC(textDisplayWindow->textBrowser, textDisplayWindow->translatorVariablesTemplate, displayLRPprocessedText, processText))
	#endif
	{
		result = false;
	}
	
	return result;
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

bool NLCIeditorWindowClass::saveEditorWindow(const bool simple)
{
	bool result = true;

	if(!(editor->document()->isModified()))
	{
		result = true;
	}
	else
	{
		bool cancelExit = false;
		QMessageBox::StandardButton ret;
		if(simple)
		{
			ret = QMessageBox::warning(this, tr("Application"), tr("The document has been modified.\nDo you want to save your changes?"), QMessageBox::Save | QMessageBox::Cancel);
		}
		else
		{
			ret = QMessageBox::warning(this, tr("Application"),tr("The document has been modified.\nDo you want to save your changes?"), QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
		}

		if(ret == QMessageBox::Save)
		{
			ensureTextEndsWithNewLineCharacter();
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

	#ifdef USE_GIAI
	if(editorWindowRef == editorWindowText)
	{
		editorWindowText = NULL;
	}
	if(editorWindowRef == editorWindowTextQuery)
	{
		editorWindowTextQuery = NULL;
	}
	#endif
		
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

#ifdef USE_GIAI
NLCIeditorWindowClass* getEditorWindowText()
{
	return editorWindowText;
}
NLCIeditorWindowClass* getEditorWindowTextQuery()
{
	return editorWindowTextQuery;
}
void setEditorWindowText(NLCIeditorWindowClass* editorWindowRef)
{
	editorWindowText = editorWindowRef;
}
void setEditorWindowTextQuery(NLCIeditorWindowClass* editorWindowRef)
{
	editorWindowTextQuery = editorWindowRef;
}
#endif



