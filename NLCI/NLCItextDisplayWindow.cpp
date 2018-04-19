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
 * File Name: NLCItextDisplayWindow.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2018 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler Interface
 * Project Version: 2f6b 16-April-2018
 * Requirements: 
 * /
 *******************************************************************************/


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
				tr("<b>GIAI</b> enables editing of natural language text along " \
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

	GIApreprocessorPlainTextWord* wordTagFound = NULL;

	int sentenceIndexUpdated = INT_DEFAULT_VALUE;
	#ifdef USE_NLCI
	if(NLCItextDisplayOperations.getWordByIndex(sentenceIndex, wordIndex, activeNLCfunctionInList, &wordTagFound, &sentenceIndexUpdated))
	//if(NLCItextDisplayOperations.getWordByIndex(functionIndex, sentenceIndex, wordIndex, firstNLCfunctionInList, &wordTagFound))	//use this function in case linkActivated can't distinguish between the NLCItextDisplayWindowClass class object which triggered the function
	#elif defined USE_GIAI
	if(NLCItextDisplayOperations.getWordByIndex(sentenceIndex, wordIndex, translatorVariablesTemplate, &wordTagFound, &sentenceIndexUpdated))
	#endif
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
		displaySemanticNetwork(sentenceIndexUpdated, wordTagFound->entityReference);
	}
	else
	{
		cout << "linkActivated error{}: !getWordByIndex; sentenceIndex = " << sentenceIndex << ", wordIndex = " << wordIndex << endl;
		exit(EXIT_ERROR);
	}
}

#ifdef USE_GIAI
bool NLCItextDisplayWindowClass::displayPreprocessedText()
{
	bool result = true;
	
	//1. create a new text display window to show NLC/GIA prepreprocessed text (ie without modifications)
	NLCItextDisplayWindowClass* textDisplayWindow = new NLCItextDisplayWindowClass();
	textDisplayWindow->translatorVariablesTemplate = translatorVariablesTemplate;
	textDisplayWindow->textDisplayFileName = textDisplayFileName;
	string textDisplayWindowName = textDisplayWindow->textDisplayFileName + " (LRP)";
	textDisplayWindow->setWindowTitle(convertStringToQString(textDisplayWindowName));
	textDisplayWindow->resize(NLCI_TEXT_DISPLAY_WINDOW_WIDTH, NLCI_TEXT_DISPLAY_WINDOW_HEIGHT);
	textDisplayWindow->show();
	textDisplayWindow->addToWindowList(textDisplayWindow);

	bool displayLRPprocessedText = true;
	if(!NLCItextDisplayOperations.processTextForNLChighlight(textDisplayWindow->textBrowser, translatorVariablesTemplate->firstGIApreprocessorSentenceInList, displayLRPprocessedText, 0))
	{
		result = false;
	}

	return result;
}
#else
bool NLCItextDisplayWindowClass::displayPreprocessedText()
{
	return true;
}
#endif


#ifdef USE_GIAI
bool NLCItextDisplayWindowClass::displaySemanticNetwork()
{
	return displaySemanticNetwork(GIA_DRAW_SENTENCE_INDEX_PRINT_ALL_SENTENCES, NULL);
}
#else
bool NLCItextDisplayWindowClass::displaySemanticNetwork()
{
	return true;
}
#endif
bool NLCItextDisplayWindowClass::displaySemanticNetwork(int sentenceIndex, GIAentityNode* entityReference)
{
	bool result = true;

	string writeFileStringSVG = "";
	int width = NLCI_SEMANTIC_NETWORK_DISPLAY_WINDOW_WIDTH;
	int height = NLCI_SEMANTIC_NETWORK_DISPLAY_WINDOW_HEIGHT;
	//cout << "functionIndex = " << functionIndex << endl;
	//cout << "sentenceIndex = " << sentenceIndex << endl;
	//cout << "wordIndex = " << wordIndex << endl;
	if(GIAdraw.printGIAnetworkNodesToSVGstring(translatorVariablesTemplate, width, height, sentenceIndex, &writeFileStringSVG, entityReference))
	{
		//cout << "writeFileStringSVG = " << writeFileStringSVG << endl;
		QString writeFileStringSVGQ = convertStringToQString(writeFileStringSVG);
		QByteArray writeFileStringSVGQbyteArray= writeFileStringSVGQ.toUtf8();
		QSvgWidget* svgDisplayWindow = new QSvgWidget();
		svgDisplayWindow->load(writeFileStringSVGQbyteArray);
		string svgDisplayWindowName = textDisplayFileName + " (semantic network)";
		svgDisplayWindow->setWindowTitle(convertStringToQString(svgDisplayWindowName));
		svgDisplayWindow->resize(NLCI_SEMANTIC_NETWORK_DISPLAY_WINDOW_WIDTH, NLCI_SEMANTIC_NETWORK_DISPLAY_WINDOW_HEIGHT);
		svgDisplayWindow->show();
	}
	else
	{
		cout << "!printGIAnetworkNodesToSVGstring" << endl;
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
	fileMenu->addAction(tr("Display semantic network"), this, SLOT(displaySemanticNetwork()));	//shows GIA generated svg file
	#endif
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











