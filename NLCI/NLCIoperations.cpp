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
 * File Name: NLCIoperations.cpp
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


#include "NLCIoperations.hpp"
#include "NLCmain.hpp"
#include "GIAmain.hpp"
#include "GIApreprocessor.hpp"


QColor NLCIoperationsClass::generateColourQ(int colourIndex)
{
	colour col;
	LDreferenceClass.convertLdrawColourToDatFileRGB(colourIndex, &col);
	return generateColourQ(&col);
}

QColor NLCIoperationsClass::generateColourQ(colour* col)
{
	return QColor(col->r, col->g, col->b);
}

#ifdef USE_NLCI
bool NLCIoperationsClass::executeNLCwrapper(bool useNLCinputFileList, string NLCinputFileListName)
{
	GIAtranslatorVariablesClass translatorVariablesTemplate;	//global (project level) translatorVariablesTemplate will be disgarded
	NLCfunction* firstNLCfunctionInList = NULL;
	return executeNLCwrapper(&translatorVariablesTemplate, firstNLCfunctionInList, useNLCinputFileList, NLCinputFileListName);
	
}
bool NLCIoperationsClass::executeNLCwrapper(GIAtranslatorVariablesClass* translatorVariablesTemplate, NLCfunction* firstNLCfunctionInList)
{
	bool useNLCinputFileList = false;
	string NLCinputFileListName = "inputFileList.nlcp";
	return executeNLCwrapper(translatorVariablesTemplate, firstNLCfunctionInList, useNLCinputFileList, NLCinputFileListName);
	
}
bool NLCIoperationsClass::executeNLCwrapper(GIAtranslatorVariablesClass* translatorVariablesTemplate, NLCfunction* firstNLCfunctionInList, bool useNLCinputFileList, string NLCinputFileListName)
{
	bool result = true;

	string inputFolderLocal = NLCI_NLC_INPUT_FOLDER;
	string outputFolderLocal = NLCI_NLC_OUTPUT_FOLDER;
	
	int NLPfeatureParser = NLCI_NLC_NLP_FEATURE_PARSER;
	int NLPdependencyRelationsParser = NLCI_NLC_NLP_DEPENDENCY_RELATIONS_PARSER;
	bool NLPrelexCompatibilityMode = false;			//(assumes) Relex dependency relations are(/were) generated by Relex parser in Stanford compatibility mode
	bool NLPassumePreCollapsedStanfordRelations = false;	//(assumes) Relex dependency relations are(/were) generated by Relex parser in Stanford compatibility mode / assumes Relex dependency relations were generated by GIA in cff
	#ifdef GIA_NLP_CLIENT_SERVER
	bool NLPclient = NLCI_NLC_NLP_CLIENT;
	#endif

	string NLPexeFolderArray[GIA_NLP_PARSER_NUMBER_OF_TYPES];
	NLPexeFolderArray[GIA_NLP_PARSER_RELEX] = NLCI_NLC_NLP_RELEX_FOLDER;
	NLPexeFolderArray[GIA_NLP_PARSER_STANFORD_CORENLP] = NLCI_NLC_NLP_STANFORD_CORE_NLP_FOLDER;
	NLPexeFolderArray[GIA_NLP_PARSER_STANFORD_PARSER] = NLCI_NLC_NLP_STANFORD_PARSER_FOLDER;

	bool useInputTextPlainTXTFile = false;	//passing data instead
	string inputTextPlainTXTfileName = "inputText.nlc";
	
	string outputTextNLPrelationXMLfileName = "inputNLPrelation.xml";
	string outputTextNLPfeatureXMLfileName = "inputNLPfeature.xml";
	bool useOutputTextCFFFile = false;
	string outputTextCFFFileName = "outputNLP.cff";
	bool useOutputTextXMLFile = false;
	string outputTextXMLFileName = "semanticNet.xml";
	bool useOutputTextCXLFile = false;
	string outputTextCXLFileName = "semanticNet.cxl";
	bool useOutputTextLDRFile = false;
	string outputTextLDRFileName = "semanticNet.ldr";
	bool useOutputTextPPMFile = false;
	string outputTextPPMFileName = "semanticNet.ppm";
	bool useOutputTextSVGFile = false;
	string outputTextSVGFileName = "semanticNet.svg";

	bool useOutputTextAllFile = NLCI_NLC_USE_OUTPUT_TEXT_ALL_FILE;
	string outputTextAllFileName = NLCI_NLC_OUTPUT_TEXT_ALL_FILE_NAME;

	//#ifdef NLC_PREPROCESSOR
	bool useNLCpreprocessor = NLCI_NLC_USE_NLC_PREPROCESSOR;
	//#endif
	#ifdef NLC_API
	bool NLCapi = false;
	string APIsourceFolder = NLC_API_DEFAULT_SOURCE_FOLDER_NAME;
	string APIclassListFileName = NLC_API_DEFAULT_CLASS_LIST_FILE_NAME;
	#endif
	bool printOutput = NLCI_NLC_PRINT_OUTPUT;
	bool displayInOpenGLAndOutputScreenshot = false;

	int rasterImageWidth = 640;
	int rasterImageHeight = 480;


	#ifdef GIA_DATABASE
	bool readFromDatabase = false;
	bool writeToDatabase = false;
	bool useDatabase = false;
	string databaseFolderName = GIA_DATABASE_FILESYSTEM_DEFAULT_SERVER_OR_MOUNT_NAME_BASE + GIA_DATABASE_FILESYSTEM_DEFAULT_DATABASE_NAME;
	#endif
	#ifdef GIA_SEMANTIC_PARSER
	string semanticParserDatabaseFolderName = GIA_DATABASE_FILESYSTEM_DEFAULT_SERVER_OR_MOUNT_NAME_BASE + GIA_SEMANTIC_PARSER_DATABASE_FILESYSTEM_DEFAULT_DATABASE_NAME;
	#endif

	#ifdef GIA_PREPROCESSOR
	bool useLRP = NLCI_NLC_USE_LRP;
	bool useOutputLRPTextPlainTXTFile = false;
	string outputLRPTextPlainTXTFileName = "inputTextWithLRP.txt";
	string lrpDataFolderName = NLCI_NLC_LRP_FOLDER;
	#endif

	#ifdef USE_WORDNET
	#ifdef GIA_SYNONYMN_DETECTION_DEFAULT_QUERIES_AND_ADVANCED_REFERENCING
	int synonymnDetectionStatus = SYNONYMN_DETECTION_STATUS_QUERIES_AND_ADVANCED_REFERENCING;
	#else
	int synonymnDetectionStatus = SYNONYMN_DETECTION_STATUS_QUERIES_ONLY;
	#endif
	#endif

	//bool train = false;
	//bool form = true;

	//basic execution flow outline; if no dataset or xml inputText file is specified, just form network - do not train network

	string currentFolder = SHAREDvarsClass().getCurrentDirectory();

	translatorVariablesTemplate->isQuery = false;
	translatorVariablesTemplate->entityNodesActiveListComplete = new vector<GIAentityNode*>;	//NOT USED
	translatorVariablesTemplate->entityNodesActiveListNetworkIndexes = new unordered_map<string, GIAentityNode*>;	//NOT USED
	translatorVariablesTemplate->timeConditionNodesActiveList = new unordered_map<long, GIAtimeConditionNode*>;	//NOT USED
	translatorVariablesTemplate->entityNodesActiveListSentences = new map<int, vector<GIAentityNode*>*>;	//NOT USED
	translatorVariablesTemplate->NLPfeatureParser = NLPfeatureParser;
	translatorVariablesTemplate->NLPdependencyRelationsParser = NLPdependencyRelationsParser;
	translatorVariablesTemplate->NLPrelexCompatibilityMode = NLPrelexCompatibilityMode;
	translatorVariablesTemplate->NLPassumePreCollapsedStanfordRelations = NLPassumePreCollapsedStanfordRelations;
	#ifdef GIA_NLP_CLIENT_SERVER
	translatorVariablesTemplate->NLPclient = NLPclient;
	#endif

	NLCmainClass().executeNLC(

		firstNLCfunctionInList, 
		translatorVariablesTemplate,

		inputFolderLocal,
		outputFolderLocal,
		NLPexeFolderArray,

		useInputTextPlainTXTFile,
		inputTextPlainTXTfileName,
		#ifdef NLC_INPUT_FUNCTION_LISTS_EXPLICIT_FROM_DEDICATED_FILE
		useNLCinputFileList,
		NLCinputFileListName,
		#endif
		
		outputTextNLPrelationXMLfileName,
		outputTextNLPfeatureXMLfileName,
		useOutputTextCFFFile,
		outputTextCFFFileName,
		useOutputTextXMLFile,
		outputTextXMLFileName,
		useOutputTextCXLFile,
		outputTextCXLFileName,
		useOutputTextLDRFile,
		outputTextLDRFileName,
		useOutputTextPPMFile,
		outputTextPPMFileName,
		useOutputTextSVGFile,
		outputTextSVGFileName,

		useOutputTextAllFile,
		outputTextAllFileName,
		#ifdef GIA_QUERY_WRITE_ANSWER_TO_FILE
		useOutputTextAnswerPlainTXTFile,
		outputTextAnswerPlainTXTFileName,
		#endif

		//#ifdef NLC_PREPROCESSOR
		useNLCpreprocessor,
		//#endif
		#ifdef NLC_API
		NLCapi,
		APIsourceFolder,
		APIclassListFileName,
		#endif

		printOutput,
		displayInOpenGLAndOutputScreenshot,

		rasterImageWidth,
		rasterImageHeight,

		#ifdef GIA_DATABASE
		readFromDatabase,
		writeToDatabase,
		useDatabase,
		databaseFolderName,
		#endif

		#ifdef GIA_SEMANTIC_PARSER
		semanticParserDatabaseFolderName,
		#endif

		#ifdef GIA_PREPROCESSOR
		useLRP,
		useOutputLRPTextPlainTXTFile,
		outputLRPTextPlainTXTFileName,
		lrpDataFolderName,
		#endif

		#ifdef USE_WORDNET
		synonymnDetectionStatus
		#endif
	);
	
	return result;
}

#else

bool NLCIoperationsClass::executeGIAwrapper(GIAtranslatorVariablesClass* translatorVariablesTemplate, bool query)
{
	bool result = true;

	string inputFolderLocal = GIAI_GIA_INPUT_FOLDER;
	string outputFolderLocal = GIAI_GIA_OUTPUT_FOLDER;

	#ifdef GIA_NLP_CLIENT_SERVER
	bool NLPclient = GIAI_GIA_NLP_CLIENT;
	#endif
	
	int NLPfeatureParser = GIAI_GIA_NLP_FEATURE_PARSER;
	int NLPdependencyRelationsParser = GIAI_GIA_NLP_DEPENDENCY_RELATIONS_PARSER;
	bool NLPrelexCompatibilityMode = false;			//(assumes) Relex dependency relations are(/were) generated by Relex parser in Stanford compatibility mode
	bool NLPassumePreCollapsedStanfordRelations = false;	//(assumes) Relex dependency relations are(/were) generated by Relex parser in Stanford compatibility mode / assumes Relex dependency relations were generated by GIA in cff
	
	int queryNLPfeatureParser = GIAI_GIA_NLP_FEATURE_PARSER_QUERY;
	int queryNLPdependencyRelationsParser = GIAI_GIA_NLP_FEATURE_PARSER_QUERY;
	bool queryNLPrelexCompatibilityMode = false;			//(assumes) Relex dependency relations are(/were) generated by Relex parser in Stanford compatibility mode
	bool queryNLPassumePreCollapsedStanfordRelations = false;	//(assumes) Relex dependency relations are(/were) generated by Relex parser in Stanford compatibility mode / assumes Relex dependency relations were generated by GIA in cff

	string NLPexeFolderArray[GIA_NLP_PARSER_NUMBER_OF_TYPES];
	NLPexeFolderArray[GIA_NLP_PARSER_RELEX] = GIAI_GIA_NLP_RELEX_FOLDER;
	NLPexeFolderArray[GIA_NLP_PARSER_STANFORD_CORENLP] = GIAI_GIA_NLP_STANFORD_CORE_NLP_FOLDER;
	NLPexeFolderArray[GIA_NLP_PARSER_STANFORD_PARSER] = GIAI_GIA_NLP_STANFORD_PARSER_FOLDER;
	
	bool useInputTextPlainTXTFile = false;
	string inputTextPlainTXTfileName = "inputText.txt";

	#ifdef USE_CE
	bool useInputTextCodeextensionsTXTFileName = false;
	string inputTextCodeextensionsTXTFileName = "codeextensionsEnumerated.txt";
	#endif

	bool useInputTextNLPrelationXMLFile = false;
	string inputTextNLPrelationXMLfileName = "inputNLPrelation.xml";
	bool useInputTextNLPfeatureXMLFile = false;
	string inputTextNLPfeatureXMLfileName = "inputNLPfeature.xml";
	bool useOutputTextCFFFile = false;
	string outputTextCFFFileName = "semanticNet.cff";
	bool useInputTextXMLFile = false;
	string inputTextXMLFileName = "semanticNet.xml";
	bool useOutputTextXMLFile = false;
	string outputTextXMLFileName = "semanticNet.xml";
	bool useOutputTextCXLFile = false;
	string outputTextCXLFileName = "semanticNet.cxl";
	bool useOutputTextLDRFile = false;
	string outputTextLDRFileName = "semanticNet.ldr";
	bool useOutputTextPPMFile = false;
	string outputTextPPMFileName = "semanticNet.ppm";
	bool useOutputTextSVGFile = false;
	string outputTextSVGFileName = "semanticNet.svg";
	bool useInputQueryPlainTXTFile = false;
	string inputQueryPlainTXTFileName = "inputTextQuery.txt";
	bool useInputQueryNLPrelationXMLFile = false;
	string inputQueryNLPrelationXMLFileName = "inputNLPrelationQuery.xml";
	bool useInputQueryNLPfeatureXMLFile = false;
	string inputQueryNLPfeatureXMLFileName = "inputNLPfeatureQuery.xml";
	bool useOutputQueryCFFFile = false;
	string outputQueryCFFFileName = "semanticNetQuery.cff";
	bool useInputQueryXMLFile = false;
	string inputQueryXMLFileName = "semanticNetQuery.xml";
	bool useOutputQueryXMLFile = false;
	string outputQueryXMLFileName = "semanticNetQuery.xml";
	bool useOutputQueryCXLFile = false;
	string outputQueryCXLFileName = "semanticNetQuery.cxl";
	bool useOutputQueryLDRFile = false;
	string outputQueryLDRFileName = "semanticNetQuery.ldr";
	bool useOutputQueryPPMFile = false;
	string outputQueryPPMFileName = "semanticNetQuery.ppm";
	bool useOutputQuerySVGFile = false;
	string outputQuerySVGFileName = "semanticNetQuery.svg";
	bool useOutputTextAllFile = GIAI_GIA_USE_OUTPUT_TEXT_ALL_FILE;
	string outputTextAllFileName = GIAI_GIA_OUTPUT_TEXT_ALL_FILE_NAME;
	#ifdef GIA_QUERY_WRITE_ANSWER_TO_FILE
	bool useOutputTextAnswerPlainTXTFile = false;
	string outputTextAnswerPlainTXTFileName = "answer.txt";
	#endif
	
	#ifdef GIA_INPUT_FILE_LISTS
	bool inputFileList = false;
	#endif
	bool printOutput = GIAI_GIA_PRINT_OUTPUT;
	bool printOutputQuery = GIAI_GIA_PRINT_OUTPUT_QUERY;
	bool displayInOpenGLAndOutputScreenshot = true;

	int rasterImageWidth = 640;
	int rasterImageHeight = 480;

	bool useInputQuery = false;
	if(query)
	{
		useInputQuery = true;
	}

	#ifdef GIA_DATABASE
	bool readFromDatabase = false;
	bool writeToDatabase = false;
	bool useDatabase = false;
	string databaseFolderName = GIA_DATABASE_FILESYSTEM_DEFAULT_SERVER_OR_MOUNT_NAME_BASE + GIA_DATABASE_FILESYSTEM_DEFAULT_DATABASE_NAME;
	#endif
	#ifdef GIA_SEMANTIC_PARSER
	string semanticParserDatabaseFolderName = GIA_DATABASE_FILESYSTEM_DEFAULT_SERVER_OR_MOUNT_NAME_BASE + GIA_SEMANTIC_PARSER_DATABASE_FILESYSTEM_DEFAULT_DATABASE_NAME;
	#endif

	#ifdef GIA_PREPROCESSOR
	bool useLRP = GIAI_GIA_USE_LRP;
	bool useOutputLRPTextPlainTXTFile = false;
	string outputLRPTextPlainTXTFileName = "inputTextWithLRP.txt";
	bool useOutputQueryLRPTextPlainTXTFile = false;
	string outputQueryLRPTextPlainTXTFileName = "inputTextWithLRPQuery.txt";
	string lrpDataFolderName = GIAI_GIA_LRP_FOLDER;
	#endif

	#ifdef USE_WORDNET
	#ifdef GIA_SYNONYMN_DETECTION_DEFAULT_QUERIES_AND_ADVANCED_REFERENCING
	int synonymnDetectionStatus = SYNONYMN_DETECTION_STATUS_QUERIES_AND_ADVANCED_REFERENCING;
	#else
	int synonymnDetectionStatus = SYNONYMN_DETECTION_STATUS_QUERIES_ONLY;
	#endif
	#endif
	


	string currentFolder = SHAREDvarsClass().getCurrentDirectory();

	translatorVariablesTemplate->isQuery = false;
	translatorVariablesTemplate->entityNodesActiveListComplete = new vector<GIAentityNode*>;	//NOT USED
	translatorVariablesTemplate->entityNodesActiveListNetworkIndexes = new unordered_map<string, GIAentityNode*>;	//NOT USED
	translatorVariablesTemplate->timeConditionNodesActiveList = new unordered_map<long, GIAtimeConditionNode*>;	//NOT USED
	translatorVariablesTemplate->entityNodesActiveListSentences = new map<int, vector<GIAentityNode*>*>;	//NOT USED
	translatorVariablesTemplate->NLPfeatureParser = NLPfeatureParser;
	translatorVariablesTemplate->NLPdependencyRelationsParser = NLPdependencyRelationsParser;
	translatorVariablesTemplate->NLPrelexCompatibilityMode = NLPrelexCompatibilityMode;
	translatorVariablesTemplate->NLPassumePreCollapsedStanfordRelations = NLPassumePreCollapsedStanfordRelations;
	#ifdef GIA_NLP_CLIENT_SERVER
	translatorVariablesTemplate->NLPclient = NLPclient;
	#endif
	
	GIAtranslatorVariablesClass* translatorVariablesQuery;
	if(query)
	{
		translatorVariablesQuery = new GIAtranslatorVariablesClass();
		translatorVariablesQuery->isQuery = true;
		translatorVariablesQuery->entityNodesActiveListComplete = new vector<GIAentityNode*>;
		translatorVariablesQuery->entityNodesActiveListNetworkIndexes = new unordered_map<string, GIAentityNode*>;
		translatorVariablesQuery->timeConditionNodesActiveList = new unordered_map<long, GIAtimeConditionNode*>;
		translatorVariablesQuery->entityNodesActiveListSentences = new map<int, vector<GIAentityNode*>*>;
		translatorVariablesQuery->NLPfeatureParser = queryNLPfeatureParser;
		translatorVariablesQuery->NLPdependencyRelationsParser = queryNLPdependencyRelationsParser;
		translatorVariablesQuery->NLPrelexCompatibilityMode = queryNLPrelexCompatibilityMode;
		translatorVariablesQuery->NLPassumePreCollapsedStanfordRelations = queryNLPassumePreCollapsedStanfordRelations;
		#ifdef GIA_NLP_CLIENT_SERVER
		translatorVariablesQuery->NLPclient = NLPclient;
		#endif
	}
	

	GIAmainClass().executeGIA(

		translatorVariables,
		translatorVariablesQuery,

		inputFolderLocal,
		outputFolderLocal,
		NLPexeFolderArray,

		useInputTextPlainTXTFile,
		inputTextPlainTXTfileName,
		#ifdef USE_CE
		useInputTextCodeextensionsTXTFileName,
		inputTextCodeextensionsTXTFileName,
		#endif
		useInputTextNLPrelationXMLFile,
		inputTextNLPrelationXMLfileName,
		useInputTextNLPfeatureXMLFile,
		inputTextNLPfeatureXMLfileName,
		useInputTextXMLFile,
		inputTextXMLFileName,		
		
		useOutputTextCFFFile,
		outputTextCFFFileName,
		useOutputTextXMLFile,
		outputTextXMLFileName,
		useOutputTextCXLFile,
		outputTextCXLFileName,
		useOutputTextLDRFile,
		outputTextLDRFileName,
		useOutputTextPPMFile,
		outputTextPPMFileName,
		useOutputTextSVGFile,
		outputTextSVGFileName,
		useInputQueryPlainTXTFile,
		inputQueryPlainTXTFileName,
		useInputQueryNLPrelationXMLFile,
		inputQueryNLPrelationXMLFileName,
		useInputQueryNLPfeatureXMLFile,
		inputQueryNLPfeatureXMLFileName,
		useOutputQueryCFFFile,
		outputQueryCFFFileName,
		useInputQueryXMLFile,
		inputQueryXMLFileName,
		useOutputQueryXMLFile,
		outputQueryXMLFileName,
		useOutputQueryCXLFile,
		outputQueryCXLFileName,
		useOutputQueryLDRFile,
		outputQueryLDRFileName,
		useOutputQueryPPMFile,
		outputQueryPPMFileName,
		useOutputQuerySVGFile,
		outputQuerySVGFileName,
		useOutputTextAllFile,
		outputTextAllFileName,
		#ifdef GIA_QUERY_WRITE_ANSWER_TO_FILE
		useOutputTextAnswerPlainTXTFile,
		outputTextAnswerPlainTXTFileName,
		#endif

		#ifdef GIA_INPUT_FILE_LISTS
		inputFileList,
		#endif
		printOutput,
		printOutputQuery,
		displayInOpenGLAndOutputScreenshot,

		rasterImageWidth,
		rasterImageHeight,

		useInputQuery,

		#ifdef GIA_DATABASE
		readFromDatabase,
		writeToDatabase,
		useDatabase,
		databaseFolderName,
		#endif

		#ifdef GIA_SEMANTIC_PARSER
		semanticParserDatabaseFolderName,
		#endif

		#ifdef GIA_PREPROCESSOR
		useLRP,
		useOutputLRPTextPlainTXTFile,
		outputLRPTextPlainTXTFileName,
		useOutputQueryLRPTextPlainTXTFile,
		outputQueryLRPTextPlainTXTFileName,
		lrpDataFolderName,
		#endif

		#ifdef USE_WORDNET
		synonymnDetectionStatus
		#endif

	);
	
	return result;
}

#endif

QString convertStringToQString(const string str)
{
	return QString::fromStdString(str);
}

string convertQStringToString(const QString qstr)
{
	return qstr.toStdString();
}












