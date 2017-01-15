/*******************************************************************************
 *
 * This file is part of BAIPROJECT.
 *
 * BAIPROJECT is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License version 3
 * only, as published by the Free Software Foundation. The use of
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
 * File Name: NLCmain.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2016 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 1r5c 15-August-2016
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/


#include "NLCmain.h"
#include "NLCcodeBlockClass.h"
#include "NLCclassDefinitionClass.h"
#include "NLCtranslator.h"
#include "NLCprint.h"
#include "NLCprintClassDefinitions.h"
#include "NLCprintCodeBlocks.h"
//#ifdef NLC_USE_PREPROCESSOR
#include "NLCpreprocessor.h"
//#endif
#include "NLCtranslatorClassDefinitions.h"
#include "NLCprintDefs.h"	//required for NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION
#ifdef NLC_API
#include "NLCapi.h"
#endif
#include "GIAmain.h"
#include "GIAdatabase.h"
#ifdef USE_WORDNET
#include "GIAwordnet.h"
#endif
#ifdef GIA_SAVE_SEMANTIC_RELATIONS_FOR_GIA2_SEMANTIC_PARSER
#include "GIAsemanticParserDatabase.h"
#endif
#include "GIAtranslatorOperations.h"
#ifdef NLC_TRANSFORM_THE_ACTION_OF_POSSESSION_EG_HAVING_CONDITION_INTO_A_PROPERTY_CONDITION
#include "GIAtranslatorDefs.h"
#endif
#include "XMLrulesClass.h"
#include "SHAREDvars.h"


static char errmessage[] = "Usage:  OpenNLC.exe [options]\n\n\twhere options are any of the following\n"
"\n\t-itxt [string]     : plain text .txt input filename to be parsed by the NLP parser (def: inputText.txt)"
"\n\t-ionlprel [string] : NLP dependency relation parser .xml intermediary input/output filename (def: inputNLPrelation.xml)"
"\n\t-ionlptag [string] : NLP feature tag parser .xml intermediary input/output filename (def: inputNLPfeature.xml)"
"\n\t-ixml [string]     : semantic network definition .xml input filename (def: semanticNet.xml)"
"\n\t-itxtq [string]    : query plain text .txt input filename to be parsed by the NLP processor (def: inputTextQuery.txt)"
"\n\t-ionlprelq [string]: query NLP dependency relation parser .xml intermediary input/output filename (def: inputNLPrelationQuery.xml)"
"\n\t-ionlptagq [string]: query NLP feature tag parser .xml intermediary input/output filename (def: inputNLPfeatureQuery.xml)"
"\n\t-ixmlq [string]    : query semantic network definition .xml input filename (def: semanticNetQuery.xml)"
#ifdef NLC_SUPPORT_INPUT_FUNCTION_LISTS_EXPLICIT_FROM_DEDICATED_FILE
"\n\t-ilist		: all input files (itxt, ionlprel, ionlptag, ixml) will be treated as file lists (new line delimited) referencing NLC function names ([functionSubject#]functionName)[+functionObject])"
#endif
#ifdef NLC_USE_PREPROCESSOR
"\n\t-ipreprocess	: itxt input file will be preprocessed, supporting condition block indentation (eg if the ball is red\\n\\tthe stars are bright\\n\\tthe cat is happy) and multiple functions (delimited by 'function [functionSubject#]functionName)[+functionObject]'"
#endif
#ifdef NLC_API
"\n\t-api                       : expose third party API (wrap with NLC code) using doxygen xml output"
"\n\t-apisourcefolder [string]  : location of third party API source code (def: /home/systemusername/source/doxygen)"
"\n\t-apiclasslist [string]   	: third party API class list (def: apiClassList.txt)"
#endif
"\n\t-oxml [string]     : semantic network definition .xml output filename (def: semanticNet.xml)"
"\n\t-ocxl [string]     : semantic network display .cxl vector graphics output filename (def: semanticNet.cxl)"
"\n\t-osvg [string]     : semantic network display .svg 2D vector graphics output filename (def: semanticNet.svg)"
"\n\t-oldr [string]     : semantic network display .ldr 3D vector graphics output filename (def: semanticNet.ldr)"
"\n\t-oppm [string]     : semantic network display .ppm raster graphics output filename (def: semanticNet.ppm)"
"\n\t-ocff [string]     : NLP parser generated .cff output filename (def: outputNLP.cff)"
"\n\t-oxmlq [string]    : query semantic network definition .xml output filename (def: semanticNetQuery.xml)"
"\n\t-ocxlq [string]    : query semantic network display .cxl vector graphics output filename (def: semanticNetQuery.cxl)"
"\n\t-osvgq [string]    : query semantic network display .svg 2D vector graphics output filename (def: semanticNetQuery.svg)"
"\n\t-oldrq [string]    : query semantic network display .ldr 3D vector graphics output filename (def: semanticNetQuery.ldr)"
"\n\t-oppmq [string]    : query semantic network display .ppm raster graphics output filename (def: semanticNetQuery.ppm)"
"\n\t-ocffq [string]    : query NLP parser generated .cff output filename (def: outputNLPQuery.cff)"
"\n\t-oall [string]     : semantic network display xml/.svg/.ldr/.ppm default generic output filename (def: semanticNet)"
"\n\t-oanswer [string]  : plain text .txt file containing the answer to the query (def: answer.txt)"
"\n\t-notshow           : do not display output in opengl"
"\n\t-width [int]       : raster graphics width in pixels (def: 640)"
"\n\t-height [int]      : raster graphics height in pixels (def: 480)"
"\n\t-nlprelation [int] : NLP dependency relation parser to be executed by GIA (0 - Relex, 1 - Stanford Core NLP, 2 - Stanford Parser [def])"
"\n\t-nlpfeature [int]  : NLP feature parser to be executed by GIA (0 - Relex, 1 - Stanford Core NLP [def], 2 - Stanford Parser (ie, none))"
"\n\t-nlpcompmode [int] : sets Relex into Stanford compatibility mode (0 - off [def], 1 - (assumes) Relex dependency relations are(/were) generated by Relex parser in Stanford compatibility mode, 2 - assumes Relex dependency relations were generated by GIA in cff) [UNTESTED]"
"\n\t-nlprelationq [int]: query NLP dependency relation parser to be executed by GIA (0 - Relex [def], 1 - Stanford Core NLP, 2 - Stanford Parser)"
"\n\t-nlpfeatureq [int] : query NLP feature parser to be executed by GIA (0 - Relex [def], 1 - Stanford Core NLP, 2 - Stanford Parser (ie, none))"
"\n\t-nlpcompmodeq [int]: query sets Relex into Stanford compatibility mode (0 - off [def], 1 - (assumes) Relex dependency relations are(/were) generated by Relex parser in Stanford compatibility mode, 2 - assumes Relex dependency relations were generated by GIA in cff) [UNTESTED]"
#ifdef GIA_USE_DATABASE
"\n\t-dbread            : read from database (GIA knowledge base) [improves referencing capacity]"
"\n\t-dbwrite           : write to database (GIA knowledge base) [saves knowledge]"
"\n\t-dbfolder          : database base folder path (def: /home/systemusername/source/GIAKBdatabase)"
#endif
#ifdef GIA_SAVE_SEMANTIC_RELATIONS_FOR_GIA2_SEMANTIC_PARSER
"\n\t-dbsemanticparserfolder    : direct semantic parser (corpus or optimised) database base folder path (def: /home/systemusername/source/GIAsemanticparserdatabase)"
#endif
#ifdef GIA_USE_LRP
"\n\t-lrp                               : language reduction preprocessor"
"\n\t-olrptxt [string]                  : plain text .txt output filename with GIA language reduction preprocessor applied (def: inputTextWithLRP.txt)"
"\n\t-olrptxtnlp [string]               : plain text .txt output filename with GIA language reduction preprocessor applied, word replacement with dummy prepositions/verbs for NLP compatibility (def: inputTextWithLRPforNLPonly.txt)"
"\n\t-olrptxtq [string]                 : query plain text .txt output filename with GIA language reduction preprocessor applied (def: inputTextWithLRPQuery.txt)"
"\n\t-olrptxtnlpq [string]              : query plain text .txt output filename with GIA language reduction preprocessor applied, word replacement with dummy prepositions/verbs for NLP compatibility (def: inputTextWithLRPforNLPonlyQuery.txt)"
"\n\t-lrpfolder                         : folder of LRP data files (list of multiword verbs, multiword prepositions etc) (def: same as exe)"
#endif
#ifdef USE_WORDNET
"\n\t-syndet                            : wordnet synonymn detection (0 - off, 1 - during queries only, 2 - during referencing and queries [def])"
#endif
"\n"
"\n\t-workingfolder [string]            : working directory name for input files (def: same as exe)"
"\n\t-nlprelexfolder [string]           : directory name for Relex (def: same as exe)"
"\n\t-nlpstanfordcorenlpfolder [string] : directory name for Stanford Parser (def: same as nlprelexefolder)"
"\n\t-nlpstanfordparserfolder [string]  : directory name for Stanford CoreNLP (def: same as nlprelexefolder)"
"\n\t-tempfolder [string]               : temp directory name for temporary and output files (def: same as exe)"
"\n"
"\n\n\t-version         : print version"
"\n\n\tThis program performs NLC (Natural Language Compiler) operations - generates computer code (eg C++) from natural language statements (it currently requires to be compiled with GIA source code).\n\n";

//Dependency Relationship Extractor

static int dependencyRelationsTypes[GIA_NLP_PARSER_NUMBER_OF_TYPES] = {GIA_NLP_DEPENDENCY_RELATIONS_PARSER_RELEX_DEFAULT_DEPENDENCY_RELATIONS_TYPE, GIA_NLP_DEPENDENCY_RELATIONS_PARSER_STANFORD_CORENLP_DEFAULT_DEPENDENCY_RELATIONS_TYPE, GIA_NLP_DEPENDENCY_RELATIONS_PARSER_STANFORD_PARSER_DEFAULT_DEPENDENCY_RELATIONS_TYPE};


int main(int argc, char** argv)
{
	int progLang = NLC_PROGRAMMING_LANGUAGE_DEFAULT;

	//print execution time
	struct tm* current;
	time_t now;
	time(&now);
	current = localtime(&now);
	char timeAndDateString[100];
	sprintf(timeAndDateString, "%i:%i:%i %.2i/%.2i/%i", current->tm_hour, current->tm_min, current->tm_sec, current->tm_mday, (current->tm_mon+1), (current->tm_year + TM_STRUCT_YEAR_OFFSET));
	cout << "NLC execution time: " << timeAndDateString << " (start)" << endl;

	bool result = true;

	int NLPfeatureParser = GIA_NLP_FEATURE_PARSER_FOR_INPUT_TEXT_DEFAULT;
	int NLPdependencyRelationsParser = GIA_NLP_RELATIONS_PARSER_FOR_INPUT_TEXT_DEFAULT;
	bool NLPrelexCompatibilityMode = false;			//(assumes) Relex dependency relations are(/were) generated by Relex parser in Stanford compatibility mode
	bool NLPassumePreCollapsedStanfordRelations = false;	//(assumes) Relex dependency relations are(/were) generated by Relex parser in Stanford compatibility mode / assumes Relex dependency relations were generated by GIA in cff

	int queryNLPfeatureParser = GIA_NLP_FEATURE_PARSER_FOR_INPUT_QUERY_DEFAULT;
	int queryNLPdependencyRelationsParser = GIA_NLP_RELATIONS_PARSER_FOR_INPUT_QUERY_DEFAULT;
	bool queryNLPrelexCompatibilityMode = false;			//(assumes) Relex dependency relations are(/were) generated by Relex parser in Stanford compatibility mode
	bool queryNLPassumePreCollapsedStanfordRelations = false;	//(assumes) Relex dependency relations are(/were) generated by Relex parser in Stanford compatibility mode / assumes Relex dependency relations were generated by GIA in cff

	string NLPexeFolderArray[GIA_NLP_PARSER_NUMBER_OF_TYPES];

	bool useInputTextPlainTXTFile = false;
	string inputTextPlainTXTfileName = "inputText.txt";

	bool useInputTextNLPrelationXMLFile = false;
	string inputTextNLPrelationXMLfileName = "inputNLPrelation.xml";
	bool useInputTextNLPfeatureXMLFile = false;
	string inputTextNLPfeatureXMLfileName = "inputNLPfeature.xml";
	bool useOutputTextCFFFile = false;
	string outputTextCFFFileName = "outputNLP.cff";
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
	string outputQueryCFFFileName = "outputNLPQuery.cff";
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
	bool useOutputTextAllFile = false;
	string outputTextAllFileName = "semanticNet";
	bool useOutputTextAnswerPlainTXTFile = false;
	string outputTextAnswerPlainTXTFileName = "answer.txt";

#ifdef GIA_SUPPORT_INPUT_FILE_LISTS
	bool inputFileList = false;	//not used by NLC
#endif
#ifdef NLC_SUPPORT_INPUT_FUNCTION_LISTS_EXPLICIT_FROM_DEDICATED_FILE
	bool NLCinputFileList = false;
#endif
//#ifdef NLC_USE_PREPROCESSOR
	bool useNLCpreprocessor = false;
//#endif
#ifdef NLC_API
	bool NLCapi = false;
	string APIsourceFolder = NLC_API_DEFAULT_SOURCE_FOLDER_NAME;	
	string APIclassListFileName = NLC_API_DEFAULT_CLASS_LIST_FILE_NAME;
#endif
	bool printOutput = false;
	bool printOutputQuery = false;
	bool displayInOpenGLAndOutputScreenshot = true;

	int rasterImageWidth = 640;
	int rasterImageHeight = 480;

	bool useInputQuery = false;

#ifdef GIA_USE_DATABASE
	bool readFromDatabase = false;
	bool writeToDatabase = false;
	bool useDatabase = false;
	string databaseFolderName = GIA_DATABASE_FILESYSTEM_DEFAULT_SERVER_OR_MOUNT_NAME_BASE + GIA_DATABASE_FILESYSTEM_DEFAULT_DATABASE_NAME;
#endif
#ifdef GIA_SAVE_SEMANTIC_RELATIONS_FOR_GIA2_SEMANTIC_PARSER
	string semanticParserDatabaseFolderName = GIA_DATABASE_FILESYSTEM_DEFAULT_SERVER_OR_MOUNT_NAME_BASE + GIA_SEMANTIC_PARSER_DATABASE_FILESYSTEM_DEFAULT_DATABASE_NAME;
#endif

#ifdef GIA_USE_LRP
	bool useLRP = false;
	bool useOutputLRPTextPlainTXTFile = false;
	string outputLRPTextPlainTXTFileName = "inputTextWithLRP.txt";
	bool useOutputLRPTextForNLPonlyPlainTXTFile = false;
	string outputLRPTextForNLPonlyPlainTXTFileName = "inputTextWithLRPforNLPonly.txt";
	bool useOutputQueryLRPTextPlainTXTFile = false;
	string outputQueryLRPTextPlainTXTFileName = "inputTextWithLRPQuery.txt";
	bool useOutputQueryLRPTextForNLPonlyPlainTXTFile = false;
	string outputQueryLRPTextForNLPonlyPlainTXTFileName = "inputTextWithLRPforNLPonlyQuery.txt";
	string lrpDataFolderName = "";
#endif

#ifdef USE_WORDNET
	int synonymnDetectionStatus = SYNONYMN_DETECTION_STATUS_QUERIES_AND_ADVANCED_REFERENCING;
#endif
	
	//bool train = false;
	//bool form = true;

	//basic execution flow outline; if no dataset or xml inputText file is specified, just form network - do not train network

	#ifdef USE_CE
	if(argumentExists(argc, argv, "-icodeextensions"))
	#else
	if(argumentExists(argc, argv, "-itxt") || argumentExists(argc, argv, "-ionlprel") || argumentExists(argc, argv, "-ixml"))
	#endif
	{
		if(argumentExists(argc, argv, "-itxt"))
		{
			inputTextPlainTXTfileName = getStringArgument(argc, argv, "-itxt");
			useInputTextPlainTXTFile = true;
		}

		if(argumentExists(argc, argv, "-ionlprel"))
		{
			inputTextNLPrelationXMLfileName = getStringArgument(argc, argv, "-ionlprel");
			useInputTextNLPrelationXMLFile = true;
		}
		if(argumentExists(argc, argv, "-ionlptag"))
		{
			inputTextNLPfeatureXMLfileName = getStringArgument(argc, argv, "-ionlptag");
			useInputTextNLPfeatureXMLFile = true;
		}

		if(argumentExists(argc, argv, "-ixml"))
		{
			inputTextXMLFileName = getStringArgument(argc, argv, "-ixml");
			//train = true;
			useInputTextXMLFile = true;
		}

		if(argumentExists(argc, argv, "-itxtq"))
		{
			inputQueryPlainTXTFileName = getStringArgument(argc, argv, "-itxtq");
			useInputQueryPlainTXTFile = true;
			useInputQuery = true;
		}

		if(argumentExists(argc, argv, "-ionlprelq"))
		{
			inputQueryNLPrelationXMLFileName = getStringArgument(argc, argv, "-ionlprelq");
			useInputQueryNLPrelationXMLFile = true;
			useInputQuery = true;
		}
		if(argumentExists(argc, argv, "-ionlptagq"))
		{
			inputQueryNLPfeatureXMLFileName = getStringArgument(argc, argv, "-ionlptagq");
			useInputQueryNLPfeatureXMLFile = true;
			useInputQuery = true;
		}

		if(argumentExists(argc, argv, "-ixmlq"))
		{
			inputQueryXMLFileName = getStringArgument(argc, argv, "-ixmlq");
			useInputQueryXMLFile = true;
			useInputQuery = true;
		}

	#ifdef NLC_SUPPORT_INPUT_FUNCTION_LISTS_EXPLICIT_FROM_DEDICATED_FILE
		if(argumentExists(argc, argv, "-ilist"))
		{
			NLCinputFileList = true;
		}
	#endif
	#ifdef NLC_USE_PREPROCESSOR
		if(argumentExists(argc, argv, "-ipreprocess"))
		{
			useNLCpreprocessor = true;
		}
	#endif
	#ifdef NLC_API
		if(argumentExists(argc, argv, "-api"))
		{
			NLCapi = true;
		}
		if(argumentExists(argc, argv, "-apisourcefolder"))
		{
			APIsourceFolder = getStringArgument(argc, argv, "-apisourcefolder");
		}
		if(argumentExists(argc, argv, "-apiclasslist"))
		{
			APIclassListFileName = getStringArgument(argc, argv, "-apiclasslist");
		}
	#endif

		if(argumentExists(argc, argv, "-ocff"))
		{
			outputTextCFFFileName = getStringArgument(argc, argv, "-ocff");
			useOutputTextCFFFile = true;
		}

		if(argumentExists(argc, argv, "-oxml"))
		{
			outputTextXMLFileName = getStringArgument(argc, argv, "-oxml");
			useOutputTextXMLFile = true;
		}

		if(argumentExists(argc, argv, "-ocxl"))
		{
			outputTextCXLFileName = getStringArgument(argc, argv, "-ocxl");
			useOutputTextCXLFile = true;
		}

		if(argumentExists(argc, argv, "-oldr"))
		{
			outputTextLDRFileName = getStringArgument(argc, argv, "-oldr");
			useOutputTextLDRFile = true;
			printOutput = true;
		}

		if(argumentExists(argc, argv, "-oppm"))
		{
			outputTextPPMFileName = getStringArgument(argc, argv, "-oppm");
			useOutputTextPPMFile = true;
			printOutput = true;
		}

		if(argumentExists(argc, argv, "-osvg"))
		{
			outputTextSVGFileName = getStringArgument(argc, argv, "-osvg");
			useOutputTextSVGFile = true;
			printOutput = true;
		}

		if(argumentExists(argc, argv, "-ocffq"))
		{
			outputQueryCFFFileName = getStringArgument(argc, argv, "-ocffq");
			useOutputQueryCFFFile = true;
		}

		if(argumentExists(argc, argv, "-oxmlq"))
		{
			outputQueryXMLFileName = getStringArgument(argc, argv, "-oxmlq");
			useOutputQueryXMLFile = true;
		}

		if(argumentExists(argc, argv, "-ocxlq"))
		{
			outputQueryCXLFileName = getStringArgument(argc, argv, "-ocxlq");
			useOutputQueryCXLFile = true;
		}

		if(argumentExists(argc, argv, "-oldrq"))
		{
			outputQueryLDRFileName = getStringArgument(argc, argv, "-oldrq");
			useOutputQueryLDRFile = true;
			printOutputQuery = true;
		}

		if(argumentExists(argc, argv, "-oppmq"))
		{
			outputQueryPPMFileName = getStringArgument(argc, argv, "-oppmq");
			useOutputQueryPPMFile = true;
			printOutputQuery = true;
		}

		if(argumentExists(argc, argv, "-osvgq"))
		{
			outputQuerySVGFileName = getStringArgument(argc, argv, "-osvgq");
			useOutputQuerySVGFile = true;
			printOutputQuery = true;
		}

		if(argumentExists(argc, argv, "-oall"))
		{
			outputTextAllFileName = getStringArgument(argc, argv, "-oall");
			useOutputTextAllFile = true;
			printOutput = true;
		}

		if(argumentExists(argc, argv, "-oanswer"))
		{
			outputTextAnswerPlainTXTFileName = getStringArgument(argc, argv, "-oanswer");
			useOutputTextAnswerPlainTXTFile = true;
		}

		/*
		if(argumentExists(argc, argv, "-train"))
		{
			int trainInt
			trainInt = getFloatArgument(argc, argv, "-train");
			train = (bool)trainInt;
		}
		*/

		if(argumentExists(argc, argv, "-notshow"))
		{
			displayInOpenGLAndOutputScreenshot = false;
		}

		if(argumentExists(argc, argv, "-width"))
		{
			rasterImageWidth = getFloatArgument(argc, argv, "-width");
		}
		
		if(argumentExists(argc, argv, "-height"))
		{
			rasterImageHeight = getFloatArgument(argc, argv, "-height");
		}
		
		string currentFolder = getCurrentDirectory();

		if(argumentExists(argc, argv, "-nlprelation"))
		{
			NLPdependencyRelationsParser = int(getFloatArgument(argc, argv, "-nlprelation"));
		}

		if(argumentExists(argc, argv, "-nlpfeature"))
		{
			NLPfeatureParser = int(getFloatArgument(argc, argv, "-nlpfeature"));
		}
		else
		{
			NLPfeatureParser = NLPdependencyRelationsParser;
		}
		if(argumentExists(argc, argv, "-nlpcompmode"))
		{
			if(queryNLPdependencyRelationsParser == GIA_NLP_PARSER_RELEX)
			{
				int nlpcompmode = int(getFloatArgument(argc, argv, "-nlpcompmode"));
				if(nlpcompmode == 1)
				{
					NLPrelexCompatibilityMode = true;
					NLPassumePreCollapsedStanfordRelations = true;
				}
				else if(nlpcompmode == 2)
				{
					NLPassumePreCollapsedStanfordRelations = true;
				}
			}
			else
			{
				cout << "error: nlpcompmode set but (NLPdependencyRelationsParser != GIA_NLP_PARSER_RELEX)" << endl;
				exit(0);
			}
		}

		if(argumentExists(argc, argv, "-nlprelationq"))
		{
			queryNLPdependencyRelationsParser = int(getFloatArgument(argc, argv, "-nlprelationq"));
		}

		if(argumentExists(argc, argv, "-nlpfeatureq"))
		{
			queryNLPfeatureParser = int(getFloatArgument(argc, argv, "-nlpfeatureq"));
		}
		else
		{
			queryNLPfeatureParser = queryNLPdependencyRelationsParser;
		}
		if(argumentExists(argc, argv, "-nlpcompmodeq"))
		{
			if(queryNLPdependencyRelationsParser == GIA_NLP_PARSER_RELEX)
			{
				int nlpcompmodeq = int(getFloatArgument(argc, argv, "-nlpcompmodeq"));
				if(nlpcompmodeq == 1)
				{
					queryNLPrelexCompatibilityMode = true;
					queryNLPassumePreCollapsedStanfordRelations = true;
				}
				else if(nlpcompmodeq == 2)
				{
					queryNLPassumePreCollapsedStanfordRelations = true;
				}
			}
			else
			{
				cout << "error: nlpcompmodeq set but (queryNLPdependencyRelationsParser != GIA_NLP_PARSER_RELEX)" << endl;
				exit(0);
			}
		}

	#ifdef GIA_USE_DATABASE
		if(argumentExists(argc, argv, "-dbread"))
		{
			readFromDatabase = true;
			useDatabase = true;
		}
		if(argumentExists(argc, argv, "-dbwrite"))
		{
			writeToDatabase = true;
			useDatabase = true;
		}
		if(argumentExists(argc, argv, "-dbfolder"))
		{
			databaseFolderName = getStringArgument(argc, argv, "-dbfolder");
			databaseFolderName = databaseFolderName + '/';
		}
	#endif
	#ifdef GIA_SAVE_SEMANTIC_RELATIONS_FOR_GIA2_SEMANTIC_PARSER
		if(argumentExists(argc, argv, "-dbsemanticparserfolder"))
		{
			semanticParserDatabaseFolderName = getStringArgument(argc, argv, "-dbsemanticparserfolder");
			semanticParserDatabaseFolderName = semanticParserDatabaseFolderName + '/';
		}
	#endif

	#ifdef GIA_USE_LRP
		if(argumentExists(argc, argv, "-lrp"))
		{
			useLRP = true;
		}
		if(argumentExists(argc, argv, "-olrptxt"))
		{
			outputLRPTextPlainTXTFileName = getStringArgument(argc, argv, "-olrptxt");
			useOutputLRPTextPlainTXTFile = true;
		}
		if(argumentExists(argc, argv, "-olrptxtnlp"))
		{
			outputLRPTextForNLPonlyPlainTXTFileName = getStringArgument(argc, argv, "-olrptxtnlp");
			useOutputLRPTextForNLPonlyPlainTXTFile = true;
		}
		if(argumentExists(argc, argv, "-olrptxtq"))
		{
			outputQueryLRPTextPlainTXTFileName = getStringArgument(argc, argv, "-olrptxtq");
			useOutputQueryLRPTextPlainTXTFile = true;
		}
		if(argumentExists(argc, argv, "-olrptxtnlpq"))
		{
			outputQueryLRPTextForNLPonlyPlainTXTFileName = getStringArgument(argc, argv, "-olrptxtnlpq");
			useOutputQueryLRPTextForNLPonlyPlainTXTFile = true;
		}
		if(argumentExists(argc, argv, "-lrpfolder"))
		{
			lrpDataFolderName = getStringArgument(argc, argv, "-lrpfolder");
			lrpDataFolderName = lrpDataFolderName + '/';
		}
		else
		{
			lrpDataFolderName = currentFolder;
		}
	#endif
	#ifdef USE_WORDNET
		if(argumentExists(argc, argv, "-syndet"))
		{
			synonymnDetectionStatus = int(getFloatArgument(argc, argv, "-syndet"));
		}
	#endif

		if(argumentExists(argc, argv, "-workingfolder"))
		{
			workingFolder =getStringArgument(argc, argv, "-workingfolder");
		}
		else
		{
			workingFolder = currentFolder;
		}

		if(argumentExists(argc, argv, "-nlprelexfolder"))
		{
			NLPexeFolderArray[GIA_NLP_PARSER_RELEX] =getStringArgument(argc, argv, "-nlprelexfolder");
		}
		else
		{
			NLPexeFolderArray[GIA_NLP_PARSER_RELEX] = currentFolder;
		}
		if(argumentExists(argc, argv, "-nlpstanfordcorenlpfolder"))
		{
			NLPexeFolderArray[GIA_NLP_PARSER_STANFORD_CORENLP] =getStringArgument(argc, argv, "-nlpstanfordcorenlpfolder");
		}
		else
		{
			NLPexeFolderArray[GIA_NLP_PARSER_STANFORD_CORENLP] = currentFolder;
		}
		if(argumentExists(argc, argv, "-nlpstanfordparserfolder"))
		{
			NLPexeFolderArray[GIA_NLP_PARSER_STANFORD_PARSER] =getStringArgument(argc, argv, "-nlpstanfordparserfolder");
		}
		else
		{
			NLPexeFolderArray[GIA_NLP_PARSER_STANFORD_PARSER] = currentFolder;
		}

		if(argumentExists(argc, argv, "-tempfolder"))
		{
			tempFolder = getStringArgument(argc, argv, "-tempfolder");
		}
		else
		{
			tempFolder = currentFolder;
		}

		setCurrentDirectory(workingFolder);

		if(argumentExists(argc, argv, "-version"))
		{
			cout << "OpenNLC.exe - Project Version: 1r5c 15-August-2016" << endl;
			exit(1);
		}


	}
	else
	{
		cout << "error: GIA requires either a plain text inputText file (.txt), an NPL parsed inputText file (.xml) or GIA semantic network (.xml) to be defined" << endl;
		printf(errmessage);
		exit(1);
	}

	//not currently used;
	if(!parseNLCrulesXMLfile())
	{
		cout << "warning: NLCrules.xml file not detected" << endl;
		//exit(0);
	}

	#ifndef NLC_SUPPORT_GIA_NLP_OR_XML_INPUT
	if(!useInputTextPlainTXTFile)
	{
		cout << "NLC requires useInputTextPlainTXTFile (itxt)" << endl;
	}	
	#endif
	
	int numberOfInputFilesInList = 1;
	vector<string> inputTextPlainTXTFileNameList;
	#ifdef NLC_SUPPORT_GIA_NLP_OR_XML_INPUT
	vector<string> inputTextNLPrelationXMLFileNameList;
	vector<string> inputTextNLPfeatureXMLFileNameList;
	vector<string> inputTextXMLFileNameList;
	#endif
	vector<string> functionNameList;
	
	#ifdef NLC_SUPPORT_INPUT_FUNCTION_LISTS_EXPLICIT_FROM_DEDICATED_FILE
	if(NLCinputFileList)
	{
		if(useInputTextPlainTXTFile)
		{
			if(!getFilesFromFileList(inputTextPlainTXTfileName, &inputTextPlainTXTFileNameList, &numberOfInputFilesInList))
			{
				cout << "main{} error: !getFilesFromFileList: " << inputTextPlainTXTfileName << endl;
			}
			#ifdef NLC_SUPPORT_INPUT_FUNCTION_LISTS_EXPLICIT_FROM_DEDICATED_FILE_SUPPORT_PREPROCESSOR
			else
			{
				if(useNLCpreprocessor)
				{
					//collapse all input list text files into single input text file
					inputTextPlainTXTfileName = inputTextPlainTXTfileName + NLC_SUPPORT_INPUT_FUNCTION_LISTS_EXPLICIT_FROM_DEDICATED_FILE_SUPPORT_PREPROCESSOR_COMBINED_FILE_NAME_APPEND_TEXT;
					string tempStr = "";
					setCurrentDirectory(tempFolder);
					writeStringToFile(inputTextPlainTXTfileName, &tempStr);
					setCurrentDirectory(workingFolder);
					for(vector<string>::iterator inputTextPlainTXTFileNameListIter = inputTextPlainTXTFileNameList.begin(); inputTextPlainTXTFileNameListIter != inputTextPlainTXTFileNameList.end(); inputTextPlainTXTFileNameListIter++)
					{
						string inputTextPlainTXTfileNameSeparate = *inputTextPlainTXTFileNameListIter;
						string NLCfunctionName = removeNLCfileNameExtension(inputTextPlainTXTfileNameSeparate);
						string functionName = "";
						string functionOwnerName = "";
						string functionObjectName = "";
						bool hasFunctionOwnerClass = false;
						bool hasFunctionObjectClass = false;
						parseFunctionNameFromNLCfunctionName(NLCfunctionName, &functionName, &functionOwnerName, &hasFunctionOwnerClass, &functionObjectName, &hasFunctionObjectClass);
						string NLCfunctionHeader = generateNLCfunctionHeader(functionName, functionOwnerName, hasFunctionOwnerClass, functionObjectName, hasFunctionObjectClass);
						string functionContents = getFileContents(inputTextPlainTXTfileNameSeparate);
						#ifdef NLC_DEBUG
						//cout << "inputTextPlainTXTfileNameSeparate = " << inputTextPlainTXTfileNameSeparate << endl;
						//cout << "NLCfunctionHeader = " << NLCfunctionHeader << endl;
						//cout << "functionContents = " << functionContents << endl;
						#endif
						string functionText = NLCfunctionHeader + CHAR_NEWLINE + functionContents + CHAR_NEWLINE;
						setCurrentDirectory(tempFolder);
						appendStringToFile(inputTextPlainTXTfileName, &functionText);
						setCurrentDirectory(workingFolder);
					}
					setCurrentDirectory(tempFolder);	//this is required such that NLC preprocessor can read the combined input file
					inputTextPlainTXTFileNameList.clear();	//this is required such that NLC preprocessor can fill inputTextPlainTXTFileNameList
					numberOfInputFilesInList = 1;		//this is required such that NLC preprocessor can fill inputTextPlainTXTFileNameList
				}
			}
			#endif
		}
		#ifdef NLC_SUPPORT_GIA_NLP_OR_XML_INPUT
		if(useInputTextNLPrelationXMLFile)
		{
			if(!getFilesFromFileList(inputTextNLPrelationXMLfileName, &inputTextNLPrelationXMLFileNameList, &numberOfInputFilesInList))
			{
				cout << "main{} error: !getFilesFromFileList: " << inputTextNLPrelationXMLfileName << endl;
			}
		}
		if(useInputTextNLPfeatureXMLFile)
		{
			if(!getFilesFromFileList(inputTextNLPfeatureXMLfileName, &inputTextNLPfeatureXMLFileNameList, &numberOfInputFilesInList))
			{
				cout << "main{} error: !getFilesFromFileList: " << inputTextNLPfeatureXMLfileName << endl;
			}
		}
		if(useInputTextXMLFile)
		{
			if(!getFilesFromFileList(inputTextXMLFileName, &inputTextXMLFileNameList, &numberOfInputFilesInList))
			{
				cout << "main{} error: !getFilesFromFileList: " << inputTextXMLFileName << endl;
			}
		}
		#endif
	}
	#endif
	
	//#ifdef NLC_USE_PREPROCESSOR
	NLCfunction* firstNLCfunctionInList = new NLCfunction();
	//#endif
	#ifdef NLC_USE_PREPROCESSOR
	//vector<string> inputTextPlainTXTFileNameList;
	bool preprocessorDetectedFunctions = false;
	string inputTextPlainTXTfileNameOrig = inputTextPlainTXTfileName;
	if(useNLCpreprocessor)
	{
		#ifdef NLC_DEBUG_PREPROCESSOR
		cout << "useNLCpreprocessor" << endl;
		#endif
		string outputPreprocessedTextForNLConlyPlainTXTFileName = inputTextPlainTXTfileName + NLC_USE_PREPROCESSOR_PREPROCESSED_FILE_NAME_APPEND_TEXT;
		#ifdef NLC_DEBUG
		//cout << "outputPreprocessedTextForNLConlyPlainTXTFileName = " << outputPreprocessedTextForNLConlyPlainTXTFileName << endl;
		#endif
		#ifdef NLC_SUPPORT_GIA_NLP_OR_XML_INPUT
		if(!useInputTextPlainTXTFile)
		{
			cout << "useNLCpreprocessor (ipreprocess) requires useInputTextNLPrelationXMLFile (itxt)" << endl;
		}
		if(useInputTextNLPrelationXMLFile || useInputTextNLPfeatureXMLFile || useInputTextXMLFile)
		{
			cout << "useNLCpreprocessor (ipreprocess) does not support useInputTextNLPrelationXMLFile (ionlprel), useInputTextNLPfeatureXMLFile (ionlptag), and useInputTextXMLFile (ixml)" << endl;
		}
		#endif
		
		if(preprocessTextForNLC(inputTextPlainTXTfileName, firstNLCfunctionInList, &preprocessorDetectedFunctions, &numberOfInputFilesInList, &inputTextPlainTXTFileNameList, outputPreprocessedTextForNLConlyPlainTXTFileName))
		{
			#ifdef NLC_SUPPORT_INPUT_FUNCTION_LISTS_PREPROCESSOR
			if(preprocessorDetectedFunctions)
			{
				#ifdef NLC_DEBUG_PREPROCESSOR
				cout << "preprocessorDetectedFunctions" << endl;
				#endif
				NLCinputFileList = true;
			}
			else
			{
			#endif
				inputTextPlainTXTfileNameOrig = inputTextPlainTXTfileName;
				inputTextPlainTXTfileName = outputPreprocessedTextForNLConlyPlainTXTFileName;	//execute NLP on preprocessed file
			#ifdef NLC_SUPPORT_INPUT_FUNCTION_LISTS_PREPROCESSOR
			}
			#endif
		}
		else
		{
			cout << "main{} error: !preprocessTextForNLC{}" << endl;
			exit(0);
		}
	}
	#endif


	vector<NLCclassDefinition*> classDefinitionList;
	vector<NLCcodeblock*> firstCodeBlockInTreeList;
	vector<vector<GIAentityNode*>*> entityNodesActiveListCompleteFunctions;
	vector<map<int, vector<GIAentityNode*>*>*> entityNodesActiveListSentencesFunctions;
		
	//#ifdef NLC_USE_PREPROCESSOR
	NLCfunction* currentNLCfunctionInList = firstNLCfunctionInList;
	//#endif
	#ifdef NLC_USE_ADVANCED_REFERENCING_SUPPORT_ALIASES_PREVENT_ADDING_AS_FUNCTION_ARGUMENT
	#ifdef NLC_USE_ADVANCED_REFERENCING_SUPPORT_ALIASES_CROSS_FUNCTION_ALIASES
	initialiseFunctionAliasClassList();
	#endif
	#endif

	#ifdef NLC_USE_LIBRARY_FUNCTION_LISTS_FOR_ARGUMENT_RECONCILIATION
	#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS
	//added 1p3b - add functionDefinitionClassDefinition (with functionDependency) for every NLClibraryStandard and NLClibraryUser function (not NLClibraryBase functions; whose references are automatically generated by NLC)
	//parse list of NLClibraryStandardFunctionList.txt and NLClibraryUserFunctionList.txt
	vector<string> nlcLibraryFunctionList;
	int nlcLibraryFunctionListSizeTemp;
	#ifdef NLC_USE_LIBRARY_STANDARD
	if(!getFilesFromFileList(NLC_USE_LIBRARY_STANDARD_FUNCTION_LIST_FILE_NAME, &nlcLibraryFunctionList, &nlcLibraryFunctionListSizeTemp))
	{
		#ifndef NLC_USE_LIBRARY_DISABLE_FUNCTIONS_LIST_WARNING
		cout << "main{} warning: " << NLC_USE_LIBRARY_STANDARD_FUNCTION_LIST_FILE_NAME << " function arguments will not be reconciled" << endl;
		#endif
	}
	#endif
	#ifdef NLC_USE_LIBRARY_USER
	if(!getFilesFromFileList(NLC_USE_LIBRARY_USER_FUNCTION_LIST_FILE_NAME, &nlcLibraryFunctionList, &nlcLibraryFunctionListSizeTemp))
	{
		#ifndef NLC_USE_LIBRARY_DISABLE_FUNCTIONS_LIST_WARNING
		cout << "main{} warning: " << NLC_USE_LIBRARY_USER_FUNCTION_LIST_FILE_NAME << " function arguments will not be reconciled" << endl;		
		#endif
	}
	#endif
	for(vector<string>::iterator nlcLibraryFunctionListIter = nlcLibraryFunctionList.begin(); nlcLibraryFunctionListIter != nlcLibraryFunctionList.end(); nlcLibraryFunctionListIter++)
	{
		string nlcLibraryFunctionName = (*nlcLibraryFunctionListIter);
		if(detectFunctionHeader(&nlcLibraryFunctionName))
		{
			string NLCfunctionName = getFunctionNameFromFunctionHeader(&nlcLibraryFunctionName);
			createFunctionDefinitionClassDefinition(&classDefinitionList, NLCfunctionName, FUNCTION_INDEX_LIBRARY_FUNCTION, true);
			#ifdef NLC_DEBUG
			//cout << "NLCfunctionName = " << NLCfunctionName << endl;
			//FUTURE NLC - update createFunctionDefinitionClassDefinition/parseFunctionNameFromNLCfunctionName to extract ! delimited tags also to identify auxilliary function arguments
			#endif
		}
		else
		{
			cout << "main{} error: !detectFunctionHeader: nlcLibraryFunctionName = " << nlcLibraryFunctionName << endl;
		}
	}	
	#endif
	#endif
		
	for(int functionDefinitionIndex=0; functionDefinitionIndex<numberOfInputFilesInList; functionDefinitionIndex++)
	{
		int maxNumberSentences;

		NLCcodeblock* firstCodeBlockInTree = new NLCcodeblock();
		firstCodeBlockInTreeList.push_back(firstCodeBlockInTree);

		vector<GIAentityNode*>* entityNodesActiveListComplete = new vector<GIAentityNode*>;
		entityNodesActiveListCompleteFunctions.push_back(entityNodesActiveListComplete);
		unordered_map<string, GIAentityNode*>* entityNodesActiveListConcepts = new unordered_map<string, GIAentityNode*>;
		vector<GIAentityNode*>* entityNodesActiveListSubstances = new vector<GIAentityNode*>;
		vector<GIAentityNode*>* entityNodesActiveListActions = new vector<GIAentityNode*>;
		vector<GIAentityNode*>* entityNodesActiveListConditions = new vector<GIAentityNode*>;
		map<int, vector<GIAentityNode*>*>* entityNodesActiveListSentences = new map<int, vector<GIAentityNode*>*>;
		entityNodesActiveListSentencesFunctions.push_back(entityNodesActiveListSentences);
		unordered_map<long, GIAtimeConditionNode*>* timeConditionNodesActiveList = new unordered_map<long, GIAtimeConditionNode*>;

		#ifdef NLC_SUPPORT_INPUT_FUNCTION_LISTS
		if(NLCinputFileList)
		{
			if(useInputTextPlainTXTFile)
			{
				inputTextPlainTXTfileName = inputTextPlainTXTFileNameList.at(functionDefinitionIndex);
			}
			#ifdef NLC_SUPPORT_GIA_NLP_OR_XML_INPUT
			if(useInputTextNLPrelationXMLFile)
			{
				inputTextNLPrelationXMLfileName = inputTextNLPrelationXMLFileNameList.at(functionDefinitionIndex);
			}
			if(useInputTextNLPfeatureXMLFile)
			{
				inputTextNLPfeatureXMLfileName = inputTextNLPfeatureXMLFileNameList.at(functionDefinitionIndex);
			}
			if(useInputTextXMLFile)
			{
				inputTextXMLFileName = inputTextXMLFileNameList.at(functionDefinitionIndex);
			}
			#endif
		}
		#endif
		
		setCurrentDirectory(workingFolder);	//NB executeGIA must be executed with current directory set to the original workingFolder (such that GIArules.xml can be read)
		string workingFolderOrig = workingFolder;
		#ifdef NLC_USE_PREPROCESSOR
		if(useNLCpreprocessor)
		{
			workingFolder = tempFolder;	//this is required such that GIA uses the temp folder as its input folder (ie workingFolder), considering NLP has already written its output to this folder
		}
		#endif
		
		#ifdef GIA_SUPPORT_NLC_INTEGRATION
		setFirstNLCsentenceInList(currentNLCfunctionInList->firstNLCsentenceInFunction);
		#endif
		
		#ifdef USE_CS_WORKAROUND
		executeGIA2();
		#endif
		executeGIA(

			NLPfeatureParser,
			NLPdependencyRelationsParser,
			NLPrelexCompatibilityMode,
			NLPassumePreCollapsedStanfordRelations,

			queryNLPfeatureParser,
			queryNLPdependencyRelationsParser,
			queryNLPrelexCompatibilityMode     ,
			queryNLPassumePreCollapsedStanfordRelations,

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
			useOutputTextCFFFile,
			outputTextCFFFileName,
			useInputTextXMLFile,
			inputTextXMLFileName,
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
			useOutputTextAnswerPlainTXTFile,
			outputTextAnswerPlainTXTFileName,

		#ifdef GIA_SUPPORT_INPUT_FILE_LISTS
			inputFileList,
		#endif
			printOutput,
			printOutputQuery,
			displayInOpenGLAndOutputScreenshot,

			rasterImageWidth,
			rasterImageHeight,

			useInputQuery,

		#ifdef GIA_USE_DATABASE
			readFromDatabase,
			writeToDatabase,
			useDatabase,
			databaseFolderName,
		#endif

		#ifdef GIA_SAVE_SEMANTIC_RELATIONS_FOR_GIA2_SEMANTIC_PARSER
			semanticParserDatabaseFolderName,
		#endif

		#ifdef GIA_USE_LRP
			useLRP,
			useOutputLRPTextPlainTXTFile,
			outputLRPTextPlainTXTFileName,
			useOutputLRPTextForNLPonlyPlainTXTFile,
			outputLRPTextForNLPonlyPlainTXTFileName,
			useOutputQueryLRPTextPlainTXTFile,
			outputQueryLRPTextPlainTXTFileName,
			useOutputQueryLRPTextForNLPonlyPlainTXTFile,
			outputQueryLRPTextForNLPonlyPlainTXTFileName,
			lrpDataFolderName,
		#endif

		#ifdef USE_WORDNET
			synonymnDetectionStatus,
		#endif

			entityNodesActiveListComplete,
			entityNodesActiveListConcepts,
			entityNodesActiveListSubstances,
			entityNodesActiveListActions,
			entityNodesActiveListConditions,
			entityNodesActiveListSentences,
			timeConditionNodesActiveList,

			&maxNumberSentences
		);

		setCurrentDirectory(tempFolder);	//redundant	//NB executeGIA will change the current directory to the tempFolder, meaning NLC does not have to set the current directory to the tempFolder after executing GIA
		workingFolder = workingFolderOrig;
		
		string NLCfunctionName = "";
		#ifdef NLC_USE_PREDEFINED_FUNCTION_NAME_FOR_NATURAL_LANGUAGE_CODE_WITHOUT_FUNCTION_SPECIFIED
		if(NLCinputFileList)
		{
			NLCfunctionName = inputTextPlainTXTfileName;
			NLCfunctionName = removeNLCfileNameExtension(NLCfunctionName);
		}
		else
		{
			NLCfunctionName = NLC_USE_PREDEFINED_FUNCTION_NAME_FOR_NATURAL_LANGUAGE_CODE_WITHOUT_FUNCTION_SPECIFIED_NAME;
		}
		#else
		if(useInputTextPlainTXTFile)
		{
			#ifdef NLC_USE_PREPROCESSOR
			if(useNLCpreprocessor && !NLCinputFileList)
			{
				NLCfunctionName = inputTextPlainTXTfileNameOrig;	//NLC 1i2c - do not add "afterPreprocessedforNLConly" to function name
			}
			else
			{
			#endif
				NLCfunctionName = inputTextPlainTXTfileName;
			#ifdef NLC_USE_PREPROCESSOR
			}
			#endif
		}
		#ifdef NLC_SUPPORT_GIA_NLP_OR_XML_INPUT
		else if(useInputTextNLPrelationXMLFile)
		{
			NLCfunctionName = inputTextNLPrelationXMLfileName;
		}
		else if(useInputTextNLPfeatureXMLFile)
		{
			NLCfunctionName = inputTextNLPfeatureXMLfileName;
		}
		else if(useInputTextXMLFile)
		{
			NLCfunctionName = inputTextXMLFileName;
		}
		else
		{
			cout << "error: NLC requires useInputTextPlainTXTFile or (useInputTextNLPrelationXMLFile and useInputTextNLPfeatureXMLFile) or useInputTextXMLFile" << endl;
		}
		#else
		else
		{
			cout << "error: NLC requires useInputTextPlainTXTFile" << endl;
		}		
		#endif


		#ifdef NLC_STRICT_MODE_FAVOUR_COMPILATION_RATHER_THAN_DESIGN_USE_MAIN_ENTRY_POINT
		NLCfunctionName = progLangMainEntryPointFunctionName[progLang];
		#else
		NLCfunctionName = removeFileNameExtensions(NLCfunctionName);
		#endif
		#endif

		#ifdef NLC_SUPPORT_INPUT_FUNCTION_LISTS
		functionNameList.push_back(NLCfunctionName);
		#endif

		#ifdef NLC_DEBUG
		cout << "translateNetwork{}: NLCfunctionName = " << NLCfunctionName << endl;
		#endif

		#ifdef NLC_DEBUG
		cout << "transformTheActionOfPossessionEgHavingIntoAproperty{}:" << endl;
		#endif
		#ifndef GIA_TRANSLATOR_TRANSFORM_THE_ACTION_OF_POSSESSION_EG_HAVING_INTO_A_PROPERTY_BASIC
		transformTheActionOfPossessionEgHavingIntoAproperty(entityNodesActiveListComplete);
		#endif

		#ifdef NLC_DEBUG
		cout << "removeRedundantConditionConjunctions{}:" << endl;
		#endif

		//generate class definition function declaration for new function definition (creates both functionDependency object and classDefinition object)
		createFunctionDefinitionClassDefinition(&classDefinitionList, NLCfunctionName, functionDefinitionIndex, false);
		
		translateNetwork(firstCodeBlockInTree, &classDefinitionList, entityNodesActiveListComplete, entityNodesActiveListSentences, maxNumberSentences, NLCfunctionName, currentNLCfunctionInList, useNLCpreprocessor);
		
		#ifdef NLC_USE_PREPROCESSOR
		if(useNLCpreprocessor)
		{
			currentNLCfunctionInList = currentNLCfunctionInList->next;
		}
		#endif
	}


	#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS
	if(!generateClassDefinitionFunctionDeclarationsAndReconcileArguments(numberOfInputFilesInList, &classDefinitionList, &entityNodesActiveListCompleteFunctions, &firstCodeBlockInTreeList))
	{
		result = false;
	}
	#endif

	#ifdef NLC_PREVENT_INHERITANCE_DOUBLE_DECLARATIONS_OF_CLASS_LIST_VARIABLES
	preventDoubleDeclarationsOfClassDefinitionVariablesInHeirachy(&classDefinitionList);	//moved 1q9a
	#endif
	
	string code = "";
	
	#ifdef NLC_API
	vector<string> APIclassList;
	int numberOfFilesInAPIclassList = 0;
	if(NLCapi)
	{
		#ifdef NLC_API_SEPARATE_FILE_FOR_WRAPPER_FUNCTIONS
		vector<NLCclassDefinition*>* classDefinitionListAPI = &classDefinitionList;
		#else
		vector<NLCclassDefinition*>* classDefinitionListAPI = new vector<NLCclassDefinition*>;
		#endif
		if(!getFilesFromFileList(APIclassListFileName, &APIclassList, &numberOfFilesInAPIclassList))
		{
			cout << "main{} error: !getFilesFromFileList: " << APIclassListFileName << endl;
		}	
		for(vector<string>::iterator iter = APIclassList.begin(); iter != APIclassList.end(); iter++)
		{
			string APIclassName = *iter;
			if(!parseDoxygenClassXMLfile(APIclassName, APIsourceFolder, classDefinitionListAPI, progLang))
			{
				cout << "main{} error: !parseDoxygenClassXMLfile(: " << APIsourceFolder+APIclassName << endl;
			}
		}
		#ifdef NLC_API_SEPARATE_FILE_FOR_WRAPPER_FUNCTIONS	
		#else
		if(printClassDefinitions(classDefinitionListAPI, progLang, &code))
		{
		
		}
		for(vector<NLCclassDefinition*>::iterator classDefinitionIter = classDefinitionListAPI->begin(); classDefinitionIter != classDefinitionListAPI->end(); classDefinitionIter++)
		{
			NLCclassDefinition* classDefinition = *classDefinitionIter;
			if(classDefinition->printed)
			{
				string printedClassDefinitionSourceFileName = generateCodeClassDefinitionSourceFileName(classDefinition->name);
				string printedClassDefinitionHeaderFileName = generateCodeClassDefinitionHeaderFileName(classDefinition->name);
				appendStringToFile(printedClassDefinitionSourceFileName, classDefinition->APIwrapperSourceText);
				appendStringToFile(printedClassDefinitionHeaderFileName, classDefinition->APIwrapperHeaderText);
			}
		}
		#endif
	}
	#endif
		
	#ifdef NLC_SUPPORT_INPUT_FUNCTION_LISTS	
	#ifndef NLC_NONOO_DISABLE_CLASS_HEIRACHY
	if(!printClassDefinitions(&classDefinitionList, progLang, &code))
	{
		result = false;
	}
	#endif
	#endif

	#ifndef NLC_USE_LIBRARY
	//create predefined NLC functions
	NLCcodeblock* currentCodeBlockInTree = firstCodeBlockInTreeList.at(numberOfInputFilesInList-1);	//get firstCodeBlockInTreeList in last function
	printPredefinedNLCfunctions(currentCodeBlockInTree);
	#endif
	
	for(int functionDefinitionIndex=0; functionDefinitionIndex<numberOfInputFilesInList; functionDefinitionIndex++)
	{
		NLCcodeblock* firstCodeBlockInTree = firstCodeBlockInTreeList.at(functionDefinitionIndex);
		int level = 0;
		#ifdef NLC_SUPPORT_INPUT_FUNCTION_LISTS
		if(!printCodeBlocks(firstCodeBlockInTree, &classDefinitionList, progLang, &code, level))
		{
			result = false;
		}
		#else
		if(!printCode(firstCodeBlockInTree, &classDefinitionList, progLang, &code))
		{
			result = false;
		}
		#endif
	}
	#ifndef NLC_USE_LIBRARY_GENERATE_INDIVIDUAL_FILES_ADD_CLASS_FUNCTIONS_TO_CLASS_DEFINITIONS
	cout << "code = \n" << code << endl;
	#endif
	
	//print execution time (end)
	time(&now);
	current = localtime(&now);
	sprintf(timeAndDateString, "%i:%i:%i %.2i/%.2i/%i", current->tm_hour, current->tm_min, current->tm_sec, current->tm_mday, (current->tm_mon+1), (current->tm_year + TM_STRUCT_YEAR_OFFSET));
	cout << "NLC execution time: " << timeAndDateString << " (finish)" << endl;
}

string removeFileNameExtensions(string NLCfunctionName)
{
	string NLCfunctionNameCleaned = NLCfunctionName;
	int indexOfFirstFileExtension = NLCfunctionName.find(".");
	if(indexOfFirstFileExtension != CPP_STRING_FIND_RESULT_FAIL_VALUE)
	{
		NLCfunctionNameCleaned = NLCfunctionName.substr(0, indexOfFirstFileExtension);
	}
	return NLCfunctionNameCleaned;
}

string removeNLCfileNameExtension(string NLCfunctionName)
{
	string NLCfunctionNameCleaned = NLCfunctionName;
	int indexOfFirstFileExtension = NLCfunctionName.find(NLC_NATURAL_LANGUAGE_CODE_FILE_NAME_EXTENSION);
	if(indexOfFirstFileExtension != CPP_STRING_FIND_RESULT_FAIL_VALUE)
	{
		NLCfunctionNameCleaned = NLCfunctionName.substr(0, indexOfFirstFileExtension);
	}
	#ifdef NLC_SUPPORT_INPUT_FUNCTION_LISTS_EXPLICIT_FROM_DEDICATED_FILE_ENFORCE_NLC_FILE_EXTENSIONS
	else
	{
		cout << "removeNLCfileNameExtension{} error: .nlc (natural language code) file extension expected, NLCfunctionName = " << NLCfunctionName << endl;
		exit(0);
	}
	#endif
	return NLCfunctionNameCleaned;
}



#ifndef GIA_TRANSLATOR_TRANSFORM_THE_ACTION_OF_POSSESSION_EG_HAVING_INTO_A_PROPERTY_BASIC
//this is required for NLC as NLC assumes GIA_TRANSLATOR_TRANSFORM_THE_ACTION_OF_POSSESSION_EG_HAVING_INTO_A_PROPERTY_BASIC
void transformTheActionOfPossessionEgHavingIntoAproperty(vector<GIAentityNode*>* entityNodesActiveListComplete)
{
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode* actionEntity = (*entityIter);
		if((actionEntity->isAction) && !(actionEntity->isConcept) && !(actionEntity->disabled))
		{
			if(isActionSpecialPossessive(actionEntity))
			{
				bool actionHasObject = false;
				GIAentityNode* actionObjectEntity = NULL;
				if(!(actionEntity->actionObjectEntity->empty()))
				{
					actionHasObject = true;
					actionObjectEntity = (actionEntity->actionObjectEntity->back())->entity;
				}
				bool actionHasSubject = false;
				GIAentityNode* actionSubjectEntity = NULL;
				if(!(actionEntity->actionSubjectEntity->empty()))
				{
					actionHasSubject = true;
					actionSubjectEntity = (actionEntity->actionSubjectEntity->back())->entity;
				}
				#ifdef NLC_DEBUG
				//cout << "transformTheActionOfPossessionEgHavingIntoAproperty{}: found and replacing possessive action entity with property" << endl;
				#endif
				if(actionHasSubject && actionHasObject)
				{
					#ifdef NLC_DEBUG
					cout << "transformTheActionOfPossessionEgHavingIntoAproperty{}:" << endl;
					cout << "actionSubjectEntity->entityName = " << actionSubjectEntity->entityName << endl;
					cout << "actionObjectEntity->entityName = " << actionObjectEntity->entityName << endl;
					#endif
				
					#ifdef NLC_TRANSFORM_THE_ACTION_OF_POSSESSION_EG_HAVING_CONDITION_INTO_A_PROPERTY_CONDITION
					/*
					eg case A:

					a
					|
					has	and/if/etc	x
					|
					b

					->

					a
					|
					b	and/if/etc 	x
					*/
					for(vector<GIAentityConnection*>::iterator connectionIter = actionEntity->conditionNodeList->begin(); connectionIter !=  actionEntity->conditionNodeList->end(); )
					{
						GIAentityNode* conditionEntity = (*connectionIter)->entity;

						(conditionEntity->conditionSubjectEntity->back())->entity = actionObjectEntity;
						connectConditionInstanceToSubject(actionObjectEntity, conditionEntity, (*connectionIter)->sameReferenceSet);		//changed 1p2b to use existing sameReferenceSet value
						#ifdef NLC_DEBUG
						cout << "transformTheActionOfPossessionEgHavingIntoAproperty{}:  NLC_TRANSFORM_THE_ACTION_OF_POSSESSION_EG_HAVING_CONDITION_INTO_A_PROPERTY_CONDITION case A" << endl;
						#endif
						connectionIter = actionEntity->conditionNodeList->erase(connectionIter);
					}
					for(vector<GIAentityConnection*>::iterator connectionIter = actionEntity->incomingConditionNodeList->begin(); connectionIter !=  actionEntity->incomingConditionNodeList->end(); )
					{
						GIAentityNode* conditionEntity = (*connectionIter)->entity;

						(conditionEntity->conditionObjectEntity->back())->entity = actionObjectEntity;
						connectConditionInstanceToObject(actionObjectEntity, conditionEntity, (*connectionIter)->sameReferenceSet);		//changed 1p2b to use existing sameReferenceSet value
						#ifdef NLC_DEBUG
						cout << "transformTheActionOfPossessionEgHavingIntoAproperty{}:  NLC_TRANSFORM_THE_ACTION_OF_POSSESSION_EG_HAVING_CONDITION_INTO_A_PROPERTY_CONDITION case B" << endl;
						#endif
						connectionIter = actionEntity->incomingConditionNodeList->erase(connectionIter);
					}
					#endif
					
					#ifdef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES	//#ifndef GIA_DISABLE_CROSS_SENTENCE_REFERENCING
					int numberOfDuplicateConnections = actionEntity->actionSubjectEntity->size();
					if(numberOfDuplicateConnections != actionEntity->actionObjectEntity->size())
					{
						cout << "transformTheActionOfPossessionEgHavingIntoAproperty{} error: numberOfDuplicateConnections inconsistent between action object and action subject" << endl;
						exit(0);
					}
					for(int i=0; i < numberOfDuplicateConnections; i++)
					{
						#ifdef NLC_DEBUG
						//cout << "i = " << i << endl;
						#endif
					#endif
						
						int sentenceIndex = (actionEntity->actionSubjectEntity->back())->sentenceIndexTemp;
						#ifdef NLC_DEBUG
						//cout << "sentenceIndex = " << sentenceIndex << endl;
						#endif
						if(sentenceIndex != (actionEntity->actionObjectEntity->back())->sentenceIndexTemp)
						{
							cout << "transformTheActionOfPossessionEgHavingIntoAproperty{} error: sentenceIndex inconsistent between action object and action subject" << endl;
							exit(0);
						}
						
						//added 1i8g
						bool sameReferenceSet = (actionEntity->actionSubjectEntity->back())->sameReferenceSet;
						#ifdef NLC_DEBUG
						//cout << "sameReferenceSet = " << sameReferenceSet << endl;
						#endif
						if(sameReferenceSet != (actionEntity->actionObjectEntity->back())->sameReferenceSet)
						{
							cout << "transformTheActionOfPossessionEgHavingIntoAproperty{} error: sameReferenceSet inconsistent between action object and action subject" << endl;
							exit(0);
						}
						
						#ifdef GIA_TRANSLATOR_MARK_DOUBLE_LINKS_AS_REFERENCE_CONNECTIONS
						bool isReference = (actionEntity->actionSubjectEntity->back())->isReference;
						#ifdef NLC_DEBUG
						//cout << "isReference = " << isReference << endl;
						#endif
						if(isReference != (actionEntity->actionObjectEntity->back())->isReference)
						{
							cout << "transformTheActionOfPossessionEgHavingIntoAproperty{} error: isReference inconsistent between action object and action subject" << endl;
							exit(0);
						}
						#endif
						
						bool foundConnection = false;
						foundConnection = false;
						for(vector<GIAentityConnection*>::iterator connectionIter = actionEntity->actionSubjectEntity->begin(); connectionIter != actionEntity->actionSubjectEntity->end(); )
						{
							GIAentityConnection* connection = (*connectionIter);
							if(connection->sentenceIndexTemp == sentenceIndex)
							{
								if(connection->entity == actionSubjectEntity)
								{
									connectionIter = actionEntity->actionSubjectEntity->erase(connectionIter);
									if(foundConnection)
									{
										cout << "transformTheActionOfPossessionEgHavingIntoAproperty{} error: dual action connections detected" << endl;
									}
									foundConnection = true;
								}
								else
								{
									connectionIter++;
								}
							}
							else
							{
								connectionIter++;
							}
						}
						if(!foundConnection)
						{
							cout << "transformTheActionOfPossessionEgHavingIntoAproperty{} error: !foundConnection - defined connections and their respective sentence indicies are inconsistent between action object and action subject" << endl;
							exit(0);
						}
						foundConnection = false;
						for(vector<GIAentityConnection*>::iterator connectionIter = actionEntity->actionObjectEntity->begin(); connectionIter != actionEntity->actionObjectEntity->end(); )
						{
							GIAentityConnection* connection = (*connectionIter);
							if(connection->sentenceIndexTemp == sentenceIndex)
							{
								if(connection->entity == actionObjectEntity)
								{
									connectionIter = actionEntity->actionObjectEntity->erase(connectionIter);
									if(foundConnection)
									{
										cout << "transformTheActionOfPossessionEgHavingIntoAproperty{} error: dual action connections detected" << endl;
									}
									foundConnection = true;
								}
								else
								{
									connectionIter++;
								}
							}
							else
							{
								connectionIter++;
							}
						}
						if(!foundConnection)
						{
							cout << "transformTheActionOfPossessionEgHavingIntoAproperty{} error: !foundConnection - defined connections and their respective sentence indicies are inconsistent between action object and action subject" << endl;
							exit(0);
						}
						foundConnection = false;
						for(vector<GIAentityConnection*>::iterator connectionIter = actionSubjectEntity->actionNodeList->begin(); connectionIter != actionSubjectEntity->actionNodeList->end(); )
						{
							GIAentityConnection* connection = (*connectionIter);
							if(connection->sentenceIndexTemp == sentenceIndex)
							{
								if(connection->entity == actionEntity)
								{
									connectionIter = actionSubjectEntity->actionNodeList->erase(connectionIter);
									if(foundConnection)
									{
										cout << "transformTheActionOfPossessionEgHavingIntoAproperty{} error: dual action connections detected" << endl;
									}
									foundConnection = true;
								}
								else
								{
									connectionIter++;
								}
							}
							else
							{
								connectionIter++;
							}
						}
						if(!foundConnection)
						{
							cout << "transformTheActionOfPossessionEgHavingIntoAproperty{} error: !foundConnection - defined connections and their respective sentence indicies are inconsistent between action object and action subject" << endl;
							exit(0);
						}
						foundConnection = false;
						for(vector<GIAentityConnection*>::iterator connectionIter = actionObjectEntity->incomingActionNodeList->begin(); connectionIter != actionObjectEntity->incomingActionNodeList->end(); )
						{
							GIAentityConnection* connection = (*connectionIter);
							if(connection->sentenceIndexTemp == sentenceIndex)
							{
								if(connection->entity == actionEntity)
								{
									connectionIter = actionObjectEntity->incomingActionNodeList->erase(connectionIter);
									if(foundConnection)
									{
										cout << "transformTheActionOfPossessionEgHavingIntoAproperty{} error: dual action connections detected" << endl;
									}
									foundConnection = true;
								}
								else
								{
									connectionIter++;
								}
							}
							else
							{
								connectionIter++;
							}
						}
						if(!foundConnection)
						{
							cout << "transformTheActionOfPossessionEgHavingIntoAproperty{} error: !foundConnection - defined connections and their respective sentence indicies are inconsistent between action object and action subject" << endl;
							exit(0);
						}			

						#ifdef GIA_TRANSLATOR_TRANSFORM_THE_ACTION_OF_POSSESSION_EG_HAVING_INTO_A_PROPERTY_BASIC_HYBRID
						bool artificialHaveEntityDetected = false;
						for(vector<GIAentityConnection*>::iterator connectionIter = actionSubjectEntity->propertyNodeList->begin(); connectionIter != actionSubjectEntity->propertyNodeList->end(); connectionIter++)
						{
							GIAentityConnection* connection = (*connectionIter);
							if(connection->sentenceIndexTemp == sentenceIndex)
							{
								if(connection->entity == actionObjectEntity)
								{
									if(artificialHaveEntityDetected)
									{
										cout << "transformTheActionOfPossessionEgHavingIntoAproperty{} error: dual property connections detected" << endl;
									}
									artificialHaveEntityDetected = true;
								}
							}
						}
						if(artificialHaveEntityDetected)
						{
							artificialHaveEntityDetected = false;
							for(vector<GIAentityConnection*>::iterator connectionIter = actionObjectEntity->propertyNodeReverseList->begin(); connectionIter != actionObjectEntity->propertyNodeReverseList->end(); connectionIter++)
							{
								GIAentityConnection* connection = (*connectionIter);
								if(connection->sentenceIndexTemp == sentenceIndex)
								{
									if(connection->entity == actionSubjectEntity)
									{
										if(artificialHaveEntityDetected)
										{
											cout << "transformTheActionOfPossessionEgHavingIntoAproperty{} error: dual property connections detected" << endl;
										}
										artificialHaveEntityDetected = true;
									}
								}
							}
							if(!artificialHaveEntityDetected)
							{
								cout << "transformTheActionOfPossessionEgHavingIntoAproperty{} error: artificialHaveEntityDetected - connection (or sentence indicies) is inconsistent between property parent and property" << endl;
								exit(0);
							}
						}
						if(artificialHaveEntityDetected)
						{
							//leave existing property connection in tact (do not set possessionAuxiliaryHave)
						}
						else
						{
						#endif
						
							#ifdef NLC_VERIFY_CONNECTIONS_SENTENCE_INDEX
							/*not required:
							#ifndef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES	//#ifdef GIA_DISABLE_CROSS_SENTENCE_REFERENCING
							sentenceIndex = actionEntity->sentenceIndexTemp;
							#endif
							*/
							setCurrentSentenceIndex(sentenceIndex);
							#endif
							//addOrConnectPropertyToEntity(actionSubjectEntity, actionObjectEntity, false);
							GIAentityConnection* propertyConnection = writeVectorConnection(actionSubjectEntity, actionObjectEntity, GIA_ENTITY_VECTOR_CONNECTION_TYPE_PROPERTIES, sameReferenceSet);
							GIAentityConnection* propertyConnectionReverse = writeVectorConnection(actionObjectEntity, actionSubjectEntity, GIA_ENTITY_VECTOR_CONNECTION_TYPE_REVERSE_PROPERTIES, sameReferenceSet);
							#ifdef NLC_TRANSLATE_NEGATIVE_PROPERTIES_AND_CONDITIONS
							if(actionEntity->negative)
							{
								propertyConnection->negative = true;	//this is required for the 1g16a 16-July-2014 "remove properties/conditions" implementation
								propertyConnectionReverse->negative = true;	//not used
							}
							#endif
							#ifndef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_BASIC_GENERATE_CONTEXT_BLOCKS_IF_SAME_REFERENCE_SET
							//imitates old code before 1i8g fix:
							propertyConnection->sameReferenceSet = false;
							propertyConnectionReverse->sameReferenceSet = false;
							#endif
							#ifdef GIA_TRANSLATOR_MARK_DOUBLE_LINKS_AS_REFERENCE_CONNECTIONS
							//added 1l8h - NB overwrite isReference is required these values will have been incorrectly determined by writeVectorConnection() - an alternative means of correction would be to use "int sentenceIndex = (actionEntity->actionSubjectEntity->front())->sentenceIndexTemp;", as the first connection added between 2 nodes is always deemed to be !isReference, and all additional connections are auto designated as isReference
							propertyConnection->isReference = isReference;
							propertyConnectionReverse->isReference = isReference;
							#endif
							#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
							if(actionEntity->negative)
							{
								actionObjectEntity->negative = true;	//this is required to be set for the current logical conditions/conjunctions implementation
							}
							#endif
							#ifdef NLC_APPLY_GET_SAME_REFERENCE_SET_NON_QUALITY_CHILD_FIX_TO_VERIFY_NOT_POSSESSION_AUXILIARY_HAVE
							if(actionEntity->entityName == RELATION_ENTITY_SPECIAL_ACTION_NAME_FOR_EFFECTIVE_PROPERTIES)		//GIA_RECORD_POSSESSION_AUXILIARY_HAS_INFORMATION_GENERAL_IMPLEMENTATION: this should more precisely be set to RELATION_ENTITY_SPECIAL_ACTION_NAME_FOR_EFFECTIVE_PROPERTIES_HAVE  
							{
								propertyConnection->possessionAuxiliaryHave = true;	//added 1p10a
								propertyConnectionReverse->possessionAuxiliaryHave = true;	//added 1p10a
							}
							#endif
						#ifdef GIA_TRANSLATOR_TRANSFORM_THE_ACTION_OF_POSSESSION_EG_HAVING_INTO_A_PROPERTY_BASIC_HYBRID
						}
						#endif
					#ifdef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES	//#ifndef GIA_DISABLE_CROSS_SENTENCE_REFERENCING
					}
					#endif

					actionEntity->isAction = false;
					actionEntity->disabled = true;	//disable have instance entity
					if(!(actionEntity->entityNodeDefiningThisInstance->empty()))
					{
						getPrimaryConceptNodeDefiningInstance(actionEntity)->disabled = true;	//disable have concept entity
					}
				}
			}
		}
	}
}

#endif


#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS
bool generateClassDefinitionFunctionDeclarationsAndReconcileArguments(int numberOfInputFilesInList, vector<NLCclassDefinition*>* classDefinitionList, vector<vector<GIAentityNode*>*>* entityNodesActiveListCompleteFunctions, vector<NLCcodeblock*>* firstCodeBlockInTreeList)
{
	bool result = true;
	
	#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE
	//added 1k13g - generate class definition function declarations for all function execution references (generateClassHeirarchyFunctions has been separated from generateClassHeirarchy since non-exact function reconciliation can only occur once class definition heirachy has been established)
	for(int functionDefinitionIndex=0; functionDefinitionIndex<numberOfInputFilesInList; functionDefinitionIndex++)
	{
		NLCclassDefinition* functionDefinitionClassDefinition = NULL;
		if(findFunctionDependencyClassDefinitionInListByIndex(classDefinitionList, functionDefinitionIndex, &functionDefinitionClassDefinition))
		{	
			vector<GIAentityNode*>* entityNodesActiveListComplete = entityNodesActiveListCompleteFunctions->at(functionDefinitionIndex);
			
			//NLC translator Part 2b.
			if(!generateClassHeirarchyFunctions(classDefinitionList, entityNodesActiveListComplete, functionDefinitionClassDefinition))
			{
				result = false;
			}
		}
	}
	#endif
	
	#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
	for(vector<NLCclassDefinition*>::iterator classDefinitionListIter = classDefinitionList->begin(); classDefinitionListIter != classDefinitionList->end(); classDefinitionListIter++)
	{
		NLCclassDefinition* classDefinition = *classDefinitionListIter;	
		if(classDefinition->functionDependency != NULL)
		{
			NLCclassDefinitionFunctionDependency* functionDependencyTemp = classDefinition->functionDependency;
			cout << "1. ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
			cout << "functionDependency->functionDefinitionListIndex = " << functionDependencyTemp->functionDefinitionListIndex << endl;
			cout << "functionDependency->functionName = " << functionDependencyTemp->functionName << endl;
			cout << "functionDependency->functionObject = " << functionDependencyTemp->functionObjectName << endl;
			cout << "functionDependency->functionOwner = " << functionDependencyTemp->functionOwnerName << endl;
			for(vector<NLCclassDefinition*>::iterator classDefinitionListIter2 = classDefinition->functionDependencyList.begin(); classDefinitionListIter2 != classDefinition->functionDependencyList.end(); classDefinitionListIter2++)
			{	
				NLCclassDefinitionFunctionDependency* functionDependencyTemp2 = (*classDefinitionListIter2)->functionDependency;
				cout << "  2. ---------------------------------------------------" << endl;
				cout << "  functionDependencyTemp2->functionDefinitionListIndex = " << functionDependencyTemp2->functionDefinitionListIndex << endl;
				cout << "  functionDependencyTemp2->functionName = " << functionDependencyTemp2->functionName << endl;
				cout << "  functionDependencyTemp2->functionObject = " << functionDependencyTemp2->functionObjectName << endl;
				cout << "  functionDependencyTemp2->functionOwner = " << functionDependencyTemp2->functionOwnerName << endl;
			}
		}
	}
	#endif
			
		
	#ifdef NLC_SUPPORT_INPUT_FUNCTION_LISTS
	#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE_ACTIVE
	bool stillUnreconciledFunctionDeclarationArguments = true;
	while(stillUnreconciledFunctionDeclarationArguments)
	{
		stillUnreconciledFunctionDeclarationArguments = false;
		for(vector<NLCclassDefinition*>::iterator classDefinitionListIter = classDefinitionList->begin(); classDefinitionListIter != classDefinitionList->end(); classDefinitionListIter++)
		{
			NLCclassDefinition* classDefinition = *classDefinitionListIter;	
			if(classDefinition->functionDependency != NULL)
			{
				NLCclassDefinitionFunctionDependency* functionDefinitionFunctionDependency = classDefinition->functionDependency;
				#ifdef NLC_DEBUG
				//cout << "functionDefinitionFunctionDependency->functionName = " << functionDefinitionFunctionDependency->functionName << endl;
				#endif
				#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE_DO_NOT_ADD_FUNCTION_DEPENDENCY_FOR_FUNCTION_REFERENCES
				if(functionDefinitionFunctionDependency->functionDefinitionListIndex != FUNCTION_INDEX_LIBRARY_FUNCTION)	//redundant check (NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE_DO_NOT_ADD_FUNCTION_DEPENDENCY_FOR_FUNCTION_REFERENCES: functionDependencies are now only defined for functionDefinition classDefinitions)
				#else
				if(functionDefinitionFunctionDependency->functionDefinitionListIndex != INT_DEFAULT_VALUE)	//redundant check (NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE_DO_NOT_ADD_FUNCTION_DEPENDENCY_FOR_FUNCTION_REFERENCES: functionDependencies are now only defined for functionDefinition classDefinitions)
				#endif
				{
					if(!(functionDefinitionFunctionDependency->isReferenceElseFunctionDefinition))	//redundant check (checking functionDefinitionListIndex already)
					{
						if(!(functionDefinitionFunctionDependency->reconciledFunctionDeclarationArguments))
						{
							#ifdef NLC_DEBUG
							//cout << "(!(functionDefinitionFunctionDependency->reconciledFunctionDeclarationArguments))" << endl;
							#endif
							bool reconciledChildFunctionDeclarationArguments = true;
							for(vector<NLCclassDefinition*>::iterator classDefinitionListIter2 = classDefinition->functionDependencyList.begin(); classDefinitionListIter2 != classDefinition->functionDependencyList.end(); classDefinitionListIter2++)
							{
								NLCclassDefinitionFunctionDependency* functionDefinitionFunctionDependencyChild = (*classDefinitionListIter2)->functionDependency;
								#ifdef NLC_DEBUG
								//cout << "functionDefinitionFunctionDependencyChild->functionName = " << functionDefinitionFunctionDependencyChild->functionName << endl;
								#endif
								#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE_DO_NOT_ADD_FUNCTION_DEPENDENCY_FOR_FUNCTION_REFERENCES
								if(functionDefinitionFunctionDependencyChild->functionDefinitionListIndex != FUNCTION_INDEX_LIBRARY_FUNCTION)
								#else
								if(functionDefinitionFunctionDependencyChild->functionDefinitionListIndex != INT_DEFAULT_VALUE)
								#endif
								{
									if(!(functionDefinitionFunctionDependencyChild->isReferenceElseFunctionDefinition))	//redundant check (checking functionDefinitionListIndex already)
									{
										if(!(functionDefinitionFunctionDependencyChild->reconciledFunctionDeclarationArguments))
										{
											reconciledChildFunctionDeclarationArguments = false;
											#ifdef NLC_DEBUG
											//cout << "reconciledChildFunctionDeclarationArguments: functionDefinitionFunctionDependencyChild->functionName = " << functionDefinitionFunctionDependencyChild->functionName << endl;
											#endif
										}
									}
									else
									{
										cout << "NLCmain error: functionDefinitionFunctionDependencyChild->functionDefinitionListIndex != INT_DEFAULT_VALUE && functionDefinitionFunctionDependencyChild->isReferenceElseFunctionDefinition" << endl;
										exit(0);
									}									
								}
								#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE_DO_NOT_ADD_FUNCTION_DEPENDENCY_FOR_FUNCTION_REFERENCES
								#ifndef NLC_USE_LIBRARY
								else
								{
									cout << "NLCmain error: functionDefinitionFunctionDependencyChild->functionDefinitionListIndex == INT_DEFAULT_VALUE. FunctionDependencies are only defined for functionDefinition classDefinitions" << endl;
									exit(0);
								}
								#endif
								#endif
							}
							if(reconciledChildFunctionDeclarationArguments)
							{
								//updates all classDefinition functionList function declaration arguments corresponding to a single defined function (functionDefinitionFunctionDependency->functionDefinitionListIndex)

								NLCcodeblock* firstCodeBlockInTree = firstCodeBlockInTreeList->at(functionDefinitionFunctionDependency->functionDefinitionListIndex);
								
								#ifdef NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
								cout << "************" << endl;
								cout << "start reconcile: functionName = " << functionDefinitionFunctionDependency->functionName << endl;
								cout << "start reconcile: functionObject = " << functionDefinitionFunctionDependency->functionObjectName << endl;
								cout << "start reconcile: functionOwner = " << functionDefinitionFunctionDependency->functionOwnerName << endl;
								#endif
								reconcileFunctionDefinitionClassDefinitionArgumentsBasedOnImplicitlyDeclaredVariablesInCurrentFunctionDefinition(firstCodeBlockInTree, classDefinitionList, classDefinition);

								functionDefinitionFunctionDependency->reconciledFunctionDeclarationArguments = true;
							}
							stillUnreconciledFunctionDeclarationArguments = true;
						}
					}
					else
					{
						cout << "NLCmain error: functionDefinitionFunctionDependency->functionDefinitionListIndex != INT_DEFAULT_VALUE && functionDefinitionFunctionDependency->isReferenceElseFunctionDefinition" << endl;
						exit(0);
					}
				}
				#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE_DO_NOT_ADD_FUNCTION_DEPENDENCY_FOR_FUNCTION_REFERENCES
				#ifndef NLC_USE_LIBRARY
				else
				{
					cout << "NLCmain error: functionDefinitionFunctionDependency->functionDefinitionListIndex == INT_DEFAULT_VALUE. FunctionDependencies are only defined for functionDefinition classDefinitions" << endl;
					exit(0);
				}
				#endif
				#endif
			}
		}	
	}
	#else
	for(int functionDefinitionIndex=0; functionDefinitionIndex<numberOfInputFilesInList; functionDefinitionIndex++)
	{
		NLCclassDefinition* functionDefinitionClassDefinition = NULL;
		if(findFunctionDependencyClassDefinitionInListByIndex(&functionDependencyList, functionDefinitionIndex, &functionDefinitionClassDefinition))
		{
			if(functionDefinitionClassDefinition->functionDependency != NULL)
			{
				NLCclassDefinitionFunctionDependency* functionDefinitionFunctionDependency = functionDefinitionClassDefinition->functionDependency;
				if(functionDefinitionFunctionDependency->functionDefinitionListIndex != INT_DEFAULT_VALUE)
				{
					//updates all classDefinition functionList function declaration arguments corresponding to a single defined function (functionDefinitionFunctionDependency->functionDefinitionListIndex)

					NLCcodeblock* firstCodeBlockInTree = firstCodeBlockInTreeList->at(functionDefinitionFunctionDependency->functionDefinitionListIndex);

					#ifdef NLC_DEBUG
					cout << "" << endl;
					cout << "start reconcile: functionName = " << functionDefinitionFunctionDependency->functionName << endl;
					cout << "start reconcile: functionObject = " << functionDefinitionFunctionDependency->functionObjectName << endl;
					cout << "start reconcile: functionOwner = " << functionDefinitionFunctionDependency->functionOwnerName << endl;
					#endif
					isLibraryFunction = false;

					reconcileFunctionDefinitionClassDefinitionArgumentsBasedOnImplicitlyDeclaredVariablesInCurrentFunctionDefinition(firstCodeBlockInTree, &classDefinitionList, functionDefinitionClassDefinition);

					//update variable names in function to 'this' if necessary based on formalFunctionArgumentCorrespondsToActionSubjectUseThisAlias
				}
				#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE_DO_NOT_ADD_FUNCTION_DEPENDENCY_FOR_FUNCTION_REFERENCES
				#ifndef NLC_USE_LIBRARY
				else
				{
					cout << "NLCmain error: functionDefinitionFunctionDependency->functionDefinitionListIndex == INT_DEFAULT_VALUE. FunctionDependencies are only defined for functionDefinition classDefinitions" << endl;
					exit(0);
				}
				#endif
				#endif

			}
		}
	}
	#endif
	#endif
	
	return result;
}
#endif


#ifndef NLC_USE_LIBRARY
void printPredefinedNLCfunctions(NLCcodeblock* currentCodeBlockInTree);
{
	//create predefined NLC functions
	currentCodeBlockInTree = getLastCodeBlockInLevel(currentCodeBlockInTree);
	currentCodeBlockInTree = createCodeBlockAddEntityToCategoryListCheckLastSentenceReferencedPluralNewFunction(currentCodeBlockInTree);
	#ifdef NLC_USE_ADVANCED_REFERENCING
	currentCodeBlockInTree = createCodeBlockAddEntityToCategoryListCheckLastSentenceReferencedSingularNewFunction(currentCodeBlockInTree);
	#ifdef NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT
	currentCodeBlockInTree = createCodeBlocksAddEntityToContextLevelListNewFunction(currentCodeBlockInTree);
	currentCodeBlockInTree = createCodeBlocksClearContextListNewFunction(currentCodeBlockInTree);
	#endif
	#endif
	#ifndef NLC_NONOO
	#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS
	currentCodeBlockInTree = createCodeBlocksCastVectorNewFunction(currentCodeBlockInTree);	
	#endif
	#endif
	#ifdef NLC_USE_ADVANCED_REFERENCING_SUPPORT_ALIASES
	currentCodeBlockInTree = createCodeBlocksFindAliasAndAddToCategoryListNewFunction(currentCodeBlockInTree);
	currentCodeBlockInTree = createCodeBlocksFindAliasNewFunction(currentCodeBlockInTree);
	#endif
	#ifdef NLC_SUPPORT_REDEFINITIONS
	currentCodeBlockInTree = createCodeBlockCheckParentClassNameNewFunction(currentCodeBlockInTree);
	#endif
	#ifdef NLC_USE_NON_LIBRARY_FUNCTIONS_EXTENDED
	currentCodeBlockInTree = createCodeBlockAddPropertyNewFunction(currentCodeBlockInTree);
	currentCodeBlockInTree = createCodeBlockAddConditionNewFunction(currentCodeBlockInTree);
	#endif
}
#endif


