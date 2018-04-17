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
 * File Name: NLCItextDisplayWindow.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2017 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler Interface
 * Project Version: 2e3a 16-December-2017
 * Requirements: 
 *
 *******************************************************************************/

#ifndef NLCI_TEXT_DISPLAY_WINDOW
#define NLCI_TEXT_DISPLAY_WINDOW

#include "NLCIglobalDefs.hpp"
#include "NLCItextDisplayOperations.hpp"
#include "GIAdraw.hpp"

#include <QMainWindow>

class QLabel;

class NLCItextDisplayWindowClass : public QMainWindow
{
	Q_OBJECT

public slots:
	void about();
	void linkActivated(const QUrl &link);
	//#ifdef USE_GIAI
	bool displayPreprocessedText();
	bool displaySemanticNetwork();
	//#endif
		bool displaySemanticNetwork(int sentenceIndex, GIAentityNode* entityReference);
	//bool displayNLPoutput();

public:
	NLCItextDisplayWindowClass(QWidget *parent = 0);

	string textDisplayFileName;
	GIAtranslatorVariablesClass* translatorVariablesTemplate;
	#ifdef USE_NLCI
	NLCfunction* activeNLCfunctionInList;
	#endif

	QTextBrowser* textBrowser;
	
	bool closeTextDisplayWindow();
	bool eraseFromWindowList(NLCItextDisplayWindowClass* textDisplayWindowRef);
	void addToWindowList(NLCItextDisplayWindowClass* textDisplayWindowRef);

private:
	GIAdrawClass GIAdraw;
	NLCItextDisplayOperationsClass NLCItextDisplayOperations;
	SHAREDvarsClass SHAREDvars;
	
	void setupTextBrowser();
	void setupFileMenu();
	void setupHelpMenu();

	//NLCIeditorSyntaxHighlighterClass *highlighter;
	//QSyntaxHighlighter* syntaxHighlighter;
	
	void closeEvent(QCloseEvent *e);
};

bool closeTextDisplayWindowsAll();

#endif
