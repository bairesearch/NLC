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
 * File Name: NLCIeditorWindow.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2017 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler Interface
 * Project Version: 2c2a 12-June-2017
 * Requirements: 
 *
 *******************************************************************************/

#ifndef NLCI_EDITOR_WINDOW
#define NLCI_EDITOR_WINDOW

#include "NLCIglobalDefs.hpp"
#include "NLCIeditorSyntaxHighlighter.hpp"
#include "NLCIeditorOperations.hpp"
#include "NLCItextDisplayOperations.hpp"
#include "NLCIoperations.hpp"
#ifdef USE_NLCI
#include "NLCpreprocessor.hpp"
#include "NLCmain.hpp"
#endif

#include <QMainWindow>


class NLCIeditorWindowClass : public QMainWindow
{
	Q_OBJECT

public slots:
	void textChangedFunction();
	void cursorPositionChangedFunction();
	//void on_editor_textChanged();
	//void on_editor_cursorPositionChanged();
	void about();
	bool save();
	bool preprepreprocessText(const bool highlight = true);
		void ensureTextEndsWithNewLineCharacter();
		bool highlightText();
	void preprepreprocessTextLine(const bool enterWasPressed);
	bool processText();
		#ifdef USE_NLCI
		bool createNewTextDisplayWindow(NLCfunction* activeNLCfunctionInList);
		#elif defined USE_GIAI
		bool createNewTextDisplayWindow();
		#endif

public:
	NLCIeditorWindowClass(QWidget *parent = 0);
	
	#ifdef USE_NLCI
	string projectName;
	#endif
	string editorName;
	bool isPreprocessed;

	//single line update functions
	int editorCursorLineNumber;
	bool textChangedSinceListCursorMovement;

	QTextEdit* editor;
	
	bool closeEditorWindow();
	bool saveEditorWindow(const bool simple = false);
	bool eraseFromWindowList(NLCIeditorWindowClass* editorWindowRef);
	void addToWindowList(NLCIeditorWindowClass* editorWindowRef);

private:
	NLCIeditorOperationsClass NLCIeditorOperations;
	NLCItextDisplayOperationsClass NLCItextDisplayOperations;
	#ifdef USE_NLCI
	NLCmainClass NLCmain;
	NLCitemClassClass NLCitemClass;
	#endif

	void setupEditor();
	void setupFileMenu();
	void setupHelpMenu();

	NLCIeditorSyntaxHighlighterClass *highlighter;
	//QSyntaxHighlighter* syntaxHighlighter;
	
	void closeEvent(QCloseEvent *e);
		
	#ifdef USE_NLCI
	NLCfunction* firstNLCfunctionInList;
	#elif defined USE_GIAI
	GIAtranslatorVariablesClass* translatorVariablesTemplate;
	#endif
};

bool closeEditorWindowsAll();
bool saveEditorWindowsAll();
string getFileNameFromFileNameFull(const string fileNameFull);
	QString getFileNameFromFileNameFull(QString fileNameFull);
string getPathFromFileNameFull(const string fileNameFull);
	QString getPathFromFileNameFull(QString fileNameFull);
bool saveFile(const QString& fileName, const QString& fileContents);


#endif