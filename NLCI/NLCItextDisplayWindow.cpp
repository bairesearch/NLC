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
 * File Name: NLCItextDisplayWindow.cpp
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
#include <QSvgWidget>

#include "NLCItextDisplayWindow.hpp"
#include "NLCIeditorOperations.hpp"


std::vector<NLCItextDisplayWindowClass*> textDisplayWindowList;

NLCItextDisplayWindowClass::NLCItextDisplayWindowClass(QWidget *parent)
	: QMainWindow(parent)
{
	setupFileMenu();
	setupHelpMenu();
	setupTextBrowser();

	textDisplayFileName = "";

	setCentralWidget(textBrowser);
	setWindowTitle(tr("NLCI Text Display"));
	
	#ifdef USE_NLCI
	activeNLCfunctionInList = NULL;
	translatorVariablesTemplate = new GIAtranslatorVariablesClass();
	#elif defined USE_GIAI
	translatorVariablesTemplate = NULL;	
	#endif
}

void NLCItextDisplayWindowClass::about()
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

void NLCItextDisplayWindowClass::linkActivated(const QUrl &link)
{
	bool result = true;

	QString linkStringQ = link.toEncoded();
	QStringList pieces = linkStringQ.split(NLCI_URL_DELIMITER);
	QString functionIndexStringQ = pieces.value(0);
	QString sentenceIndexStringQ = pieces.value(1);
	QString wordIndexStringQ = pieces.value(2);
	string functionIndexString = convertQStringToString(functionIndexStringQ);
	string sentenceIndexString = convertQStringToString(sentenceIndexStringQ);
	string wordIndexString = convertQStringToString(wordIndexStringQ);
	int functionIndex = SHAREDvars.convertStringToInt(functionIndexString);
	int sentenceIndex = SHAREDvars.convertStringToInt(sentenceIndexString);
	int wordIndex = SHAREDvars.convertStringToInt(wordIndexString);

	GIApreprocessorWord* wordTagFound = NULL;

	if(NLCItextDisplayOperations.getWordByIndex(sentenceIndex, wordIndex, activeNLCfunctionInList, &wordTagFound))
	//if(NLCItextDisplayOperations.getWordByIndex(functionIndex, sentenceIndex, wordIndex, firstNLCfunctionInList, &wordTagFound))	//use this function in case linkActivated can't distinguish between the NLCItextDisplayWindowClass class object which triggered the function
	{

		#ifdef USE_NLCI
		//1. create a new text display window to show NLC generated (e.g. C++) code
		NLCItextDisplayWindowClass* textDisplayWindow2 = new NLCItextDisplayWindowClass();
		textDisplayWindow2->translatorVariablesTemplate = translatorVariablesTemplate;
		textDisplayWindow2->textDisplayFileName = textDisplayFileName;
		string textDisplayWindowName = textDisplayWindow2->textDisplayFileName + " (generated code)";
		textDisplayWindow2->setWindowTitle(convertStringToQString(textDisplayWindowName));
		textDisplayWindow2->resize(NLCI_TEXT_DISPLAY_WINDOW_NLC_GENERATED_WIDTH, NLCI_TEXT_DISPLAY_WINDOW_NLC_GENERATED_HEIGHT);
		textDisplayWindow2->show();
		string code = translatorVariablesTemplate->nlcGeneratedCode;
		QString codeQ = convertStringToQString(code);
		textDisplayWindow2->textBrowser->setText(codeQ);
		addToWindowList(textDisplayWindow2);
		#endif

		//2. draw the entity in SVG
		string writeFileStringSVG = "";
		int width = NLCI_SEMANTIC_NETWORK_DISPLAY_WINDOW_WIDTH;
		int height = NLCI_SEMANTIC_NETWORK_DISPLAY_WINDOW_HEIGHT;
		//cout << "functionIndex = " << functionIndex << endl;
		//cout << "sentenceIndex = " << sentenceIndex << endl;
		//cout << "wordIndex = " << wordIndex << endl;
		int sentenceIndexGIA = sentenceIndex + GIA_NLP_START_SENTENCE_INDEX;
		if(GIAdraw.printGIAnetworkNodesToSVGstring(translatorVariablesTemplate, width, height, sentenceIndexGIA, &writeFileStringSVG, wordTagFound->entityReference))
		{
			cout << "writeFileStringSVG = " << writeFileStringSVG << endl;
			QString writeFileStringSVGQ = convertStringToQString(writeFileStringSVG);
			QByteArray writeFileStringSVGQbyteArray= writeFileStringSVGQ.toUtf8();
			QSvgWidget* svgDisplayWindow = new QSvgWidget();
			svgDisplayWindow->load(writeFileStringSVGQbyteArray);
			string svgDisplayWindowName = textDisplayWindow2->textDisplayFileName + " (semantic network)";
			svgDisplayWindow->setWindowTitle(convertStringToQString(svgDisplayWindowName));
			svgDisplayWindow->resize(NLCI_SEMANTIC_NETWORK_DISPLAY_WINDOW_WIDTH, NLCI_SEMANTIC_NETWORK_DISPLAY_WINDOW_HEIGHT);
			svgDisplayWindow->show();
		}
		else
		{
			cout << "!printGIAnetworkNodesToSVGstring" << endl;
			result = false;
		}
	}
	else
	{
		cout << "linkActivated error{}: !getWordByIndex; sentenceIndex = " << sentenceIndex << ", wordIndex = " << wordIndex << endl;
		exit(EXIT_ERROR);
	}
}

#ifdef USE_GIAI
bool NLCIeditorWindowClass::displayPreprocessedText()
{
	bool result = true;

	//1. create a new text display window to show NLC/GIA prepreprocessed text (ie without modifications)
	NLCItextDisplayWindowClass* textDisplayWindow = new NLCItextDisplayWindowClass();
	textDisplayWindow->translatorVariablesTemplate = translatorVariablesTemplate;
	textDisplayWindow->textDisplayFileName = editorFileName;
	string textDisplayWindowName = textDisplayWindow->textDisplayFileName;
	textDisplayWindow->setWindowTitle(convertStringtoStringQ(textDisplayWindowName));
	textDisplayWindow->resize(NLCI_TEXT_DISPLAY_WINDOW_WIDTH, NLCI_TEXT_DISPLAY_WINDOW_HEIGHT);
	textDisplayWindow->show();
	textDisplayWindow->addToWindowList(textDisplayWindow);

	bool displayLRPprocessedText = true;
	NLCItextDisplayOperations.processTextForNLC(textDisplayWindow->textBrowser, translatorVariablesTemplate, displayLRPprocessedText);

	return result;
}
#endif


bool NLCItextDisplayWindowClass::displaySemanticNetwork()
{
	bool result = true;

	string writeFileStringSVG = "";
	int width = NLCI_SEMANTIC_NETWORK_FULL_DISPLAY_WINDOW_WIDTH;
	int height = NLCI_SEMANTIC_NETWORK_FULLDISPLAY_WINDOW_HEIGHT;
	int sentenceIndex = GIA_DRAW_SENTENCE_INDEX_PRINT_ALL_SENTENCES;
	GIAentityNode* entityReference = NULL;

	if(GIAdraw.printGIAnetworkNodesToSVGstring(translatorVariablesTemplate, width, height, sentenceIndex, &writeFileStringSVG, entityReference))
	{
		QString writeFileStringSVGQ = convertStringToQString(writeFileStringSVG);
		QByteArray writeFileStringSVGQbyteArray= writeFileStringSVGQ.toUtf8();
		QSvgWidget* svgDisplayWindow = new QSvgWidget();
		svgDisplayWindow->load(writeFileStringSVGQbyteArray);
	}
	else
	{
		result = false;
	}

	return result;
}

/*
bool NLCItextDisplayWindowClass::displayNLPoutput()
{
	bool result = true;

	return result;
}
*/





void NLCItextDisplayWindowClass::setupTextBrowser()
{
	QFont font;
	font.setFamily("Courier");
	font.setFixedPitch(true);
	font.setPointSize(10);

	textBrowser = new QTextBrowser;
	textBrowser->setOpenExternalLinks(false);
	textBrowser->setOpenLinks(false);
	//textBrowser->setTextInteractionFlags(Qt::TextBrowserInteraction);

	connect(textBrowser, SIGNAL(anchorClicked(QUrl)), this, SLOT(linkActivated(QUrl)));
}

void NLCItextDisplayWindowClass::setupFileMenu()
{
	QMenu *fileMenu = new QMenu(tr("&File"), this);
	menuBar()->addMenu(fileMenu);

	#ifdef USE_GIAI
	fileMenu->addAction(tr("Display GIA LRP preprocessed text"), this, SLOT(displayPreprocessedText()));
	#endif
	fileMenu->addAction(tr("Display semantic network"), this, SLOT(displaySemanticNetwork()));	//shows GIA generated svg file
	//fileMenu->addAction(tr("Display NLP output"), this, SLOT(displayNLPoutput()));
	fileMenu->addAction(tr("C&lose"), this, SLOT(close()), QKeySequence::Close);
}

void NLCItextDisplayWindowClass::setupHelpMenu()
{
	QMenu *helpMenu = new QMenu(tr("&Help"), this);
	menuBar()->addMenu(helpMenu);

	helpMenu->addAction(tr("&About"), this, SLOT(about()));
}

void NLCItextDisplayWindowClass::closeEvent(QCloseEvent *event)
{
	if(closeTextDisplayWindow())
	{
		event->accept();
	}
	else
	{
		event->ignore();
	}
}

bool NLCItextDisplayWindowClass::closeTextDisplayWindow()
{
	bool result = true;

	eraseFromWindowList(this);

	return result;
}

bool NLCItextDisplayWindowClass::eraseFromWindowList(NLCItextDisplayWindowClass* textDisplayWindowRef)
{
	bool result = false;
	std::vector<NLCItextDisplayWindowClass*>::iterator iter = std::find(textDisplayWindowList.begin(), textDisplayWindowList.end(), textDisplayWindowRef);
	if(iter != textDisplayWindowList.end())
	{
		result = true;
		textDisplayWindowList.erase(iter);
		//qInfo("textDisplayWindowList");
	}
	return result;
}

void NLCItextDisplayWindowClass::addToWindowList(NLCItextDisplayWindowClass* textDisplayWindowRef)
{
	textDisplayWindowList.push_back(textDisplayWindowRef);
}


bool closeTextDisplayWindowsAll()
{
	bool result = true;
	//qDebug() << "closeTextDisplayWindowsAll(): textDisplayWindowList.size() = " << textDisplayWindowList.size();
	bool stillWindowsToClose =  true;
	while(stillWindowsToClose)
	{
		if(textDisplayWindowList.size() > 0)
		{
			//qDebug() << "closeTextDisplayWindowsAll(): textDisplayWindowList[0] = ";
			if(!(textDisplayWindowList[0]->close()))
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











