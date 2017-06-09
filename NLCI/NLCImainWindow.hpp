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
 * File Name: NLCImainWindow.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2017 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler Interface
 * Project Version: 2c1e 01-June-2017
 * Requirements: 
 *
 *******************************************************************************/

#ifndef NLCI_MAIN_WINDOW
#define NLCI_MAIN_WINDOW

#include "NLCIglobalDefs.hpp"
#include "NLCIeditorSyntaxHighlighter.hpp"
#include "NLCIoperations.hpp"

#include <QMainWindow>

class QTextEdit;
class QLabel;
class QScrollArea;

class NLCImainWindowClass : public QMainWindow
{
	Q_OBJECT

public:
	NLCImainWindowClass(QWidget *parent = 0);

public slots:
	void about();
	
	//#ifdef USE_NLCI
	void createNewProject(QString projectFileNameFull = "");
	void selectProject(QString projectFileNameFull = "");
	void openProjectAssociatedFile(QString fileNameFull = "");
	void openProject(QString projectFileNameFull = "", bool openFiles = true);
	void addNewFileToProject(QString fileNameFull = "");
	void addExistingFileToProject(QString fileNameFull = "");
	
	void compileProject();
	void compileGeneratedCppProjectCode();
	void runGeneratedCppProjectCode();
	
	void saveProject();
	void closeProject();
	//#endif
	
	void openFile(QString fileNameFull = QString(), string projectFileNameFull = "", bool expectAssociatedFile = false);

private:
	NLCIoperationsClass NLCIoperations;

	void setupTextBrowser();
	void setupFileMenu();
	void setupHelpMenu();

	void closeEvent(QCloseEvent *e);

	QString addFileNameExtensionIfNecessary(const QString fileName, const string extensionToAddIfNecessary);
	string addFileNameExtensionIfNecessary(const string fileName, const string extensionToAddIfNecessary);
	bool findFileNameExtension(const string fileName, const string extensionToFind);
	string generateProjectFileContents();
	
	bool projectOpened;
	string projectName;

	//QLabel* textBrowser;
	QTextEdit* textBox;
	
};

#endif
