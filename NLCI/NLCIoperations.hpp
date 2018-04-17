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
 * File Name: NLCIoperations.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2017 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler Interface
 * Project Version: 2e1a 07-December-2017
 * Requirements: 
 *
 *******************************************************************************/

#ifndef NLCI_OPERATIONS
#define NLCI_OPERATIONS

#include "NLCIglobalDefs.hpp"
#include "SHAREDvars.hpp"
#include "LDreferenceClass.hpp"
#include "GIAtranslatorOperations.hpp"
#include "NLCpreprocessor.hpp"
#include "GIAdraw.hpp"

#include <QTextCharFormat>
#include <QTextEdit>

#define GIA_DRAW_VERB_NODE_COLOUR (GIA_DRAW_ACTION_NODE_COLOUR)
#define GIA_DRAW_PREPOSITION_NODE_COLOUR (GIA_DRAW_CONDITION_NODE_COLOUR)
#define GIA_DRAW_ADVERB_NODE_COLOUR (GIA_DRAW_SUBSTANCE_QUALITY_NODE_COLOUR)
#define GIA_DRAW_ADJECTIVE_NODE_COLOUR (GIA_DRAW_SUBSTANCE_QUALITY_NODE_COLOUR)
#define GIA_DRAW_NOUN_NODE_COLOUR (GIA_DRAW_PROPERTY_NODE_COLOUR)
#define NLCI_EDITOR_DEFAULT_FONT_COLOUR (DAT_FILE_COLOUR_BLACK)

#define NLCI_EDITOR_SYNTAX_HIGHLIGHTER_LOGICAL_CONDITION_COLOUR (DAT_FILE_COLOUR_DARKYELLOW)
#define NLCI_EDITOR_SYNTAX_HIGHLIGHTER_MATHTEXT_VARIABLE_TYPE_COLOUR (DAT_FILE_COLOUR_DARKYELLOW)

class HighlightingRule
{
public:
	QRegExp pattern;
	QTextCharFormat format;
};	

class NLCIoperationsClass
{
	//Q_OBJECT
public:
	GIApreprocessorMultiwordReductionClass GIApreprocessorMultiwordReduction;
	LDreferenceClassClass LDreferenceClass;

	QColor generateColourQ(int colourIndex);
		QColor generateColourQ(colour* col);	
	
	#ifdef USE_NLCI
	bool executeNLCwrapper(GIAtranslatorVariablesClass* translatorVariablesTemplate, const bool useNLCinputFileList, const string NLCinputFileListName);
	bool executeNLCwrapper(GIAtranslatorVariablesClass* translatorVariablesTemplate, NLCfunction* firstNLCfunctionInList);
		bool executeNLCwrapper(GIAtranslatorVariablesClass* translatorVariablesTemplate, NLCfunction* firstNLCfunctionInList, const bool useNLCinputFileList, const string NLCinputFileListName);
	#else
	bool executeGIAwrapper(GIAtranslatorVariablesClass* translatorVariablesTemplate, GIAtranslatorVariablesClass* translatorVariablesQuery, const bool query);
	#endif	
	
	int preprepreprocessTextForNLChighlightWordDetermineColourIndex(const string* word);
	int processTextForNLChighlightWordDetermineColourIndex(GIAentityNode* entity);

};

QString convertStringToQString(const string str);
string convertQStringToString(const QString qstr);
QString convertByteArrayToQString(const QByteArray& ba);



#endif
