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
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2014 Baxter AI (baxterai.com)
 * Project: Natural Language Programming Interface (compiler)
 * Project Version: 1k9a 14-October-2014
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/



#include <ctime>
#include <cstdlib>	//for random number generation
#include <cmath>

#include "NLCmain.h"
#include "NLCcodeBlockClass.h"
#include "NLCclassDefinitionClass.h"
#include "NLCtranslator.h"
#include "NLCprint.h"
#include "NLCprintClassDefinitions.h"
#include "NLCprintCodeBlocks.h"

#include "GIAmain.h"
#include "GIAdatabase.h"
#include "SHAREDvars.h"
#ifdef USE_WORDNET
#include "GIAwordnet.h"
#endif
#ifdef GIA_USE_CORPUS_DATABASE
#include "GIAcorpusDatabase.h"
#endif
#ifndef GIA_TRANSLATOR_TRANSFORM_THE_ACTION_OF_POSSESSION_EG_HAVING_INTO_A_PROPERTY_BASIC
#include "GIAtranslatorOperations.h"
#endif
#ifdef NLC_TRANSFORM_THE_ACTION_OF_POSSESSION_EG_HAVING_CONDITION_INTO_A_PROPERTY_CONDITION
#include "GIAtranslatorDefs.h"
#endif
//#ifdef NLC_USE_PREPROCESSOR
#include "NLCpreprocessor.h"
//#endif

static char errmessage[] = "Usage:  OpenNLC.exe [options]\n\n\twhere options are any of the following\n"
"\n\t-itxt [string]     : plain text .txt input filename to be parsed by the NLP parser (def: inputText.txt)"
"\n\t-ionlprel [string] : NLP dependency relation parser .xml intermediary input/output filename (def: inputNLPrelation.xml)"
"\n\t-ionlptag [string] : NLP feature tag parser .xml intermediary input/output filename (def: inputNLPfeature.xml)"
"\n\t-ixml [string]     : semantic network definition .xml input filename (def: semanticNet.xml)"
"\n\t-itxtq [string]    : query plain text .txt input filename to be parsed by the NLP processor (def: inputTextQuery.txt)"
"\n\t-ionlprelq [string]: query NLP dependency relation parser .xml intermediary input/output filename (def: inputNLPrelationQuery.xml)"
"\n\t-ionlptagq [string]: query NLP feature tag parser .xml intermediary input/output filename (def: inputNLPfeatureQuery.xml)"
"\n\t-ixmlq [string]    : query semantic network definition .xml input filename (def: semanticNetQuery.xml)"
#ifdef NLC_SUPPORT_INPUT_FILE_LISTS
"\n\t-ilist		: all input files (itxt, ionlprel, ionlptag, ixml) will be treated as file lists (new line delimited) referencing NLC function names ([functionSubject#]functionName)[+functionObject])"
#endif
#ifdef NLC_USE_PREPROCESSOR
"\n\t-ipreprocess	: itxt input file will be preprocessed, supporting condition block indentation (eg if the ball is red\\n\\tthe stars are bright\\n\\tthe cat is happy) and multiple functions (delimited by 'function [functionSubject#]functionName)[+functionObject]'"
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
#ifdef GIA_USE_CORPUS_DATABASE
"\n\t-dbcorpusfolder    : corpus database base folder path (def: /home/systemusername/source/GIAcorpusDatabase)"
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
#ifdef GIA_USE_

#endif
"\n"
"\n\t-workingfolder [string]            : working directory name for input files (def: same as exe)"
"\n\t-nlprelexfolder [string]           : directory name for Relex (def: same as exe)"
"\n\t-nlpstanfordcorenlpfolder [string] : directory name for Stanford Parser (def: same as nlprelexefolder)"
"\n\t-nlpstanfordparserfolder [string]  : directory name for Stanford CoreNLP (def: same as nlprelexefolder)"
"\n\t-tempfolder [string]               : temp directory name for temporary and output files (def: same as exe)"
"\n"
"\n\n\t-version         : print version"
"\n\n\tThis program performs NLC (Natural Language Programming Interface) operations - generates computer code (eg C++) from natural language statements (it currently requires to be compiled with GIA source code).\n\n";

//Dependency Relationship Extractor

static int dependencyRelationsTypes[GIA_NLP_PARSER_NUMBER_OF_TYPES] = {GIA_NLP_DEPENDENCY_RELATIONS_PARSER_RELEX_DEFAULT_DEPENDENCY_RELATIONS_TYPE, GIA_NLP_DEPENDENCY_RELATIONS_PARSER_STANFORD_CORENLP_DEFAULT_DEPENDENCY_RELATIONS_TYPE, GIA_NLP_DEPENDENCY_RELATIONS_PARSER_STANFORD_PARSER_DEFAULT_DEPENDENCY_RELATIONS_TYPE};


int main(int argc,char **argv)
{
	int progLang = NLC_PROGRAMMING_LANGUAGE_DEFAULT;

	#ifdef GIA_TRIAL_WORD_NET_SYNONYM_LOOKUP
	initialiseWordNet();
	string wordExample = "like";
	bool wordIsFound = false;
	string listOfSynonyms[WORDNET_FINDTHEINFO_OUTPUT_MAX_NUMBER_SYNONYMS];
	int wordNetPOS = VERB;	//NOUN	VERB
	checkIfSynsetListContainsSynonymousEntityNamesAndRecordMostPopularSynset(wordExample, &wordIsFound, wordNetPOS);
	//findSynonymsOLD(wordExample, &wordIsFound, listOfSynonyms, wordNetPOS);
	exit(0);
	#endif

	//print execution time
	struct tm *current;
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
#ifdef NLC_SUPPORT_INPUT_FILE_LISTS
	bool NLCinputFileList = false;
#endif
//#ifdef NLC_USE_PREPROCESSOR
	bool useNLCpreprocessor = false;
//#endif

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
#ifdef GIA_USE_CORPUS_DATABASE
	string corpusDatabaseFolderName = GIA_DATABASE_FILESYSTEM_DEFAULT_SERVER_OR_MOUNT_NAME_BASE + GIA_CORPUS_DATABASE_FILESYSTEM_DEFAULT_DATABASE_NAME;
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
	if(argumentExists(argc,argv,"-icodeextensions"))
	#else
	if(argumentExists(argc,argv,"-itxt") || argumentExists(argc,argv,"-ionlprel") || argumentExists(argc,argv,"-ixml"))
	#endif
	{
		if(argumentExists(argc,argv,"-itxt"))
		{
			inputTextPlainTXTfileName=getCharArgument(argc,argv,"-itxt");
			useInputTextPlainTXTFile = true;
		}

		if(argumentExists(argc,argv,"-ionlprel"))
		{
			inputTextNLPrelationXMLfileName=getCharArgument(argc,argv,"-ionlprel");
			useInputTextNLPrelationXMLFile = true;
		}
		if(argumentExists(argc,argv,"-ionlptag"))
		{
			inputTextNLPfeatureXMLfileName=getCharArgument(argc,argv,"-ionlptag");
			useInputTextNLPfeatureXMLFile = true;
		}

		if(argumentExists(argc,argv,"-ixml"))
		{
			inputTextXMLFileName=getCharArgument(argc,argv,"-ixml");
			//train = true;
			useInputTextXMLFile = true;
		}

		if(argumentExists(argc,argv,"-itxtq"))
		{
			inputQueryPlainTXTFileName=getCharArgument(argc,argv,"-itxtq");
			useInputQueryPlainTXTFile = true;
			useInputQuery = true;
		}

		if(argumentExists(argc,argv,"-ionlprelq"))
		{
			inputQueryNLPrelationXMLFileName=getCharArgument(argc,argv,"-ionlprelq");
			useInputQueryNLPrelationXMLFile = true;
			useInputQuery = true;
		}
		if(argumentExists(argc,argv,"-ionlptagq"))
		{
			inputQueryNLPfeatureXMLFileName=getCharArgument(argc,argv,"-ionlptagq");
			useInputQueryNLPfeatureXMLFile = true;
			useInputQuery = true;
		}

		if(argumentExists(argc,argv,"-ixmlq"))
		{
			inputQueryXMLFileName=getCharArgument(argc,argv,"-ixmlq");
			useInputQueryXMLFile = true;
			useInputQuery = true;
		}

	#ifdef NLC_SUPPORT_INPUT_FILE_LISTS
		if(argumentExists(argc,argv,"-ilist"))
		{
			NLCinputFileList = true;
		}
	#endif
	#ifdef NLC_USE_PREPROCESSOR
		if(argumentExists(argc,argv,"-ipreprocess"))
		{
			useNLCpreprocessor = true;
		}
	#endif


		if(argumentExists(argc,argv,"-ocff"))
		{
			outputTextCFFFileName=getCharArgument(argc,argv,"-ocff");
			useOutputTextCFFFile = true;
		}

		if(argumentExists(argc,argv,"-oxml"))
		{
			outputTextXMLFileName=getCharArgument(argc,argv,"-oxml");
			useOutputTextXMLFile = true;
		}

		if(argumentExists(argc,argv,"-ocxl"))
		{
			outputTextCXLFileName=getCharArgument(argc,argv,"-ocxl");
			useOutputTextCXLFile = true;
		}

		if(argumentExists(argc,argv,"-oldr"))
		{
			outputTextLDRFileName=getCharArgument(argc,argv,"-oldr");
			useOutputTextLDRFile = true;
			printOutput = true;
		}

		if(argumentExists(argc,argv,"-oppm"))
		{
			outputTextPPMFileName=getCharArgument(argc,argv,"-oppm");
			useOutputTextPPMFile = true;
			printOutput = true;
		}

		if(argumentExists(argc,argv,"-osvg"))
		{
			outputTextSVGFileName=getCharArgument(argc,argv,"-osvg");
			useOutputTextSVGFile = true;
			printOutput = true;
		}

		if(argumentExists(argc,argv,"-ocffq"))
		{
			outputQueryCFFFileName=getCharArgument(argc,argv,"-ocffq");
			useOutputQueryCFFFile = true;
		}

		if(argumentExists(argc,argv,"-oxmlq"))
		{
			outputQueryXMLFileName=getCharArgument(argc,argv,"-oxmlq");
			useOutputQueryXMLFile = true;
		}

		if(argumentExists(argc,argv,"-ocxlq"))
		{
			outputQueryCXLFileName=getCharArgument(argc,argv,"-ocxlq");
			useOutputQueryCXLFile = true;
		}

		if(argumentExists(argc,argv,"-oldrq"))
		{
			outputQueryLDRFileName=getCharArgument(argc,argv,"-oldrq");
			useOutputQueryLDRFile = true;
			printOutputQuery = true;
		}

		if(argumentExists(argc,argv,"-oppmq"))
		{
			outputQueryPPMFileName=getCharArgument(argc,argv,"-oppmq");
			useOutputQueryPPMFile = true;
			printOutputQuery = true;
		}

		if(argumentExists(argc,argv,"-osvgq"))
		{
			outputQuerySVGFileName=getCharArgument(argc,argv,"-osvgq");
			useOutputQuerySVGFile = true;
			printOutputQuery = true;
		}

		if(argumentExists(argc,argv,"-oall"))
		{
			outputTextAllFileName=getCharArgument(argc,argv,"-oall");
			useOutputTextAllFile = true;
			printOutput = true;
		}

		if(argumentExists(argc,argv,"-oanswer"))
		{
			outputTextAnswerPlainTXTFileName=getCharArgument(argc,argv,"-oanswer");
			useOutputTextAnswerPlainTXTFile = true;
		}

		/*
		if(argumentExists(argc,argv,"-train"))
		{
			int trainInt
			trainInt=getFloatArgument(argc,argv,"-train");
			train = (bool)trainInt;
		}
		*/

		if (argumentExists(argc,argv,"-notshow"))
		{
			displayInOpenGLAndOutputScreenshot = false;
		}

		if (argumentExists(argc,argv,"-width"))
		rasterImageWidth=getFloatArgument(argc,argv,"-width");

		if (argumentExists(argc,argv,"-height"))
		rasterImageHeight=getFloatArgument(argc,argv,"-height");

		char currentFolder[EXE_FOLDER_PATH_MAX_LENGTH];
		getCurrentDirectory(currentFolder);

		if(argumentExists(argc,argv,"-nlprelation"))
		{
			NLPdependencyRelationsParser = int(getFloatArgument(argc,argv,"-nlprelation"));
		}

		if(argumentExists(argc,argv,"-nlpfeature"))
		{
			NLPfeatureParser = int(getFloatArgument(argc,argv,"-nlpfeature"));
		}
		else
		{
			NLPfeatureParser = NLPdependencyRelationsParser;
		}
		if(argumentExists(argc,argv,"-nlpcompmode"))
		{
			if(queryNLPdependencyRelationsParser == GIA_NLP_PARSER_RELEX)
			{
				int nlpcompmode = int(getFloatArgument(argc,argv,"-nlpcompmode"));
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

		if(argumentExists(argc,argv,"-nlprelationq"))
		{
			queryNLPdependencyRelationsParser = int(getFloatArgument(argc,argv,"-nlprelationq"));
		}

		if(argumentExists(argc,argv,"-nlpfeatureq"))
		{
			queryNLPfeatureParser = int(getFloatArgument(argc,argv,"-nlpfeatureq"));
		}
		else
		{
			queryNLPfeatureParser = queryNLPdependencyRelationsParser;
		}
		if(argumentExists(argc,argv,"-nlpcompmodeq"))
		{
			if(queryNLPdependencyRelationsParser == GIA_NLP_PARSER_RELEX)
			{
				int nlpcompmodeq = int(getFloatArgument(argc,argv,"-nlpcompmodeq"));
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
		if(argumentExists(argc,argv,"-dbread"))
		{
			readFromDatabase = true;
			useDatabase = true;
		}
		if(argumentExists(argc,argv,"-dbwrite"))
		{
			writeToDatabase = true;
			useDatabase = true;
		}
		if(argumentExists(argc,argv,"-dbfolder"))
		{
			databaseFolderName=getCharArgument(argc,argv,"-dbfolder");
			databaseFolderName = databaseFolderName + '/';
		}
	#endif
	#ifdef GIA_USE_CORPUS_DATABASE
		if(argumentExists(argc,argv,"-dbcorpusfolder"))
		{
			corpusDatabaseFolderName=getCharArgument(argc,argv,"-dbcorpusfolder");
			corpusDatabaseFolderName = corpusDatabaseFolderName + '/';
		}
	#endif

	#ifdef GIA_USE_LRP
		if(argumentExists(argc,argv,"-lrp"))
		{
			useLRP = true;
		}
		if(argumentExists(argc,argv,"-olrptxt"))
		{
			outputLRPTextPlainTXTFileName=getCharArgument(argc,argv,"-olrptxt");
			useOutputLRPTextPlainTXTFile = true;
		}
		if(argumentExists(argc,argv,"-olrptxtnlp"))
		{
			outputLRPTextForNLPonlyPlainTXTFileName=getCharArgument(argc,argv,"-olrptxtnlp");
			useOutputLRPTextForNLPonlyPlainTXTFile = true;
		}
		if(argumentExists(argc,argv,"-olrptxtq"))
		{
			outputQueryLRPTextPlainTXTFileName=getCharArgument(argc,argv,"-olrptxtq");
			useOutputQueryLRPTextPlainTXTFile = true;
		}
		if(argumentExists(argc,argv,"-olrptxtnlpq"))
		{
			outputQueryLRPTextForNLPonlyPlainTXTFileName=getCharArgument(argc,argv,"-olrptxtnlpq");
			useOutputQueryLRPTextForNLPonlyPlainTXTFile = true;
		}
		if(argumentExists(argc,argv,"-lrpfolder"))
		{
			lrpDataFolderName=getCharArgument(argc,argv,"-lrpfolder");
			lrpDataFolderName = lrpDataFolderName + '/';
		}
		else
		{
			lrpDataFolderName = currentFolder;
		}
	#endif
	#ifdef USE_WORDNET
		if(argumentExists(argc,argv,"-syndet"))
		{
			synonymnDetectionStatus = int(getFloatArgument(argc,argv,"-syndet"));
		}
	#endif

		if (argumentExists(argc,argv,"-workingfolder"))
		{
			workingFolderCharStar =getCharArgument(argc,argv,"-workingfolder");
		}
		else
		{
			workingFolderCharStar = currentFolder;
		}

		if (argumentExists(argc,argv,"-nlprelexfolder"))
		{
			NLPexeFolderArray[GIA_NLP_PARSER_RELEX] =getCharArgument(argc,argv,"-nlprelexfolder");
		}
		else
		{
			NLPexeFolderArray[GIA_NLP_PARSER_RELEX] = currentFolder;
		}
		if (argumentExists(argc,argv,"-nlpstanfordcorenlpfolder"))
		{
			NLPexeFolderArray[GIA_NLP_PARSER_STANFORD_CORENLP] =getCharArgument(argc,argv,"-nlpstanfordcorenlpfolder");
		}
		else
		{
			NLPexeFolderArray[GIA_NLP_PARSER_STANFORD_CORENLP] = currentFolder;
		}
		if (argumentExists(argc,argv,"-nlpstanfordparserfolder"))
		{
			NLPexeFolderArray[GIA_NLP_PARSER_STANFORD_PARSER] =getCharArgument(argc,argv,"-nlpstanfordparserfolder");
		}
		else
		{
			NLPexeFolderArray[GIA_NLP_PARSER_STANFORD_PARSER] = currentFolder;
		}

		if (argumentExists(argc,argv,"-tempfolder"))
		{
			tempFolderCharStar=getCharArgument(argc,argv,"-tempfolder");
		}
		else
		{
			tempFolderCharStar = currentFolder;
		}

		setCurrentDirectory(workingFolderCharStar);

		if (argumentExists(argc,argv,"-version"))
		{
			cout << "OpenNLC.exe - Project Version: 1k9a 14-October-2014" << endl;
			exit(1);
		}


	}
	else
	{
		cout << "error: GIA requires either a plain text inputText file (.txt), an NPL parsed inputText file (.xml) or GIA semantic network (.xml) to be defined" << endl;
		printf(errmessage);
		exit(1);
	}

	int numberOfInputFilesInList = 1;
	#ifdef NLC_SUPPORT_INPUT_FILE_LISTS
	vector<string> inputTextPlainTXTFileNameList;
	vector<string> inputTextNLPrelationXMLFileNameList;
	vector<string> inputTextNLPfeatureXMLFileNameList;
	vector<string> inputTextXMLFileNameList;
	vector<string> functionNameList;
	if(NLCinputFileList)
	{
		if(useInputTextPlainTXTFile)
		{
			if(!getFilesFromFileList2(inputTextPlainTXTfileName, &inputTextPlainTXTFileNameList, &numberOfInputFilesInList))
			{
				cout << "main() error: !getFilesFromFileList2()" << endl;
			}
		}
		if(useInputTextNLPrelationXMLFile)
		{
			if(!getFilesFromFileList2(inputTextNLPrelationXMLfileName, &inputTextNLPrelationXMLFileNameList, &numberOfInputFilesInList))
			{
				cout << "main() error: !getFilesFromFileList2()" << endl;
			}
		}
		if(useInputTextNLPfeatureXMLFile)
		{
			if(!getFilesFromFileList2(inputTextNLPfeatureXMLfileName, &inputTextNLPfeatureXMLFileNameList, &numberOfInputFilesInList))
			{
				cout << "main() error: !getFilesFromFileList2()" << endl;
			}
		}
		if(useInputTextXMLFile)
		{
			if(!getFilesFromFileList2(inputTextXMLFileName, &inputTextXMLFileNameList, &numberOfInputFilesInList))
			{
				cout << "main() error: !getFilesFromFileList2()" << endl;
			}
		}
	}
	#endif

	NLCfunction * firstNLCfunctionInList = new NLCfunction();
	#ifdef NLC_USE_PREPROCESSOR
	//vector<string> inputTextPlainTXTFileNameList;
	bool preprocessorDetectedFunctions = false;
	string inputTextPlainTXTfileNameOrig = inputTextPlainTXTfileName;
	if(useNLCpreprocessor)
	{
		#ifdef NLC_DEBUG_PREPROCESSOR
		cout << "useNLCpreprocessor" << endl;
		#endif
		string outputPreprocessedTextForNLConlyPlainTXTFileName = inputTextPlainTXTfileName + "afterPreprocessedforNLConly.txt";
		if(!useInputTextPlainTXTFile)
		{
			cout << "useNLCpreprocessor (ipreprocess) requires useInputTextNLPrelationXMLFile (itxt)" << endl;
		}
		if(useInputTextNLPrelationXMLFile || useInputTextNLPfeatureXMLFile || useInputTextXMLFile)
		{
			cout << "useNLCpreprocessor (ipreprocess) does not support useInputTextNLPrelationXMLFile (ionlprel), useInputTextNLPfeatureXMLFile (ionlptag), and useInputTextXMLFile (ixml)" << endl;
		}
		if(preprocessTextForNLC(inputTextPlainTXTfileName, firstNLCfunctionInList, &preprocessorDetectedFunctions, &numberOfInputFilesInList, &inputTextPlainTXTFileNameList, outputPreprocessedTextForNLConlyPlainTXTFileName))
		{
			#ifdef NLC_SUPPORT_INPUT_FILE_LISTS
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
			#ifdef NLC_SUPPORT_INPUT_FILE_LISTS
			}
			#endif
		}
		else
		{
			cout << "main() error: !preprocessTextForNLC()" << endl;
			exit(0);
		}


	}
	#endif

	vector<NLCcodeblock*> firstCodeBlockInTreeList;
	vector<NLCclassDefinition *> classDefinitionList;

	//#ifdef NLC_USE_PREPROCESSOR
	NLCfunction * currentNLCfunctionInList = firstNLCfunctionInList;
	//#endif

	for(int i=0; i<numberOfInputFilesInList; i++)
	{
		int maxNumberSentences;

		NLCcodeblock * firstCodeBlockInTree = new NLCcodeblock();
		firstCodeBlockInTreeList.push_back(firstCodeBlockInTree);

		vector<GIAentityNode*> * entityNodesActiveListComplete = new vector<GIAentityNode*>;
		unordered_map<string, GIAentityNode*> * entityNodesActiveListConcepts = new unordered_map<string, GIAentityNode*>;
		vector<GIAentityNode*> * entityNodesActiveListSubstances = new vector<GIAentityNode*>;
		vector<GIAentityNode*> * entityNodesActiveListActions = new vector<GIAentityNode*>;
		vector<GIAentityNode*> * entityNodesActiveListConditions = new vector<GIAentityNode*>;
		unordered_map<long, GIAtimeConditionNode*> * timeConditionNodesActiveList = new unordered_map<long, GIAtimeConditionNode*>;

		#ifdef NLC_SUPPORT_INPUT_FILE_LISTS
		if(NLCinputFileList)
		{
			if(useInputTextPlainTXTFile)
			{
				inputTextPlainTXTfileName = inputTextPlainTXTFileNameList.at(i);
			}
			if(useInputTextNLPrelationXMLFile)
			{
				inputTextNLPrelationXMLfileName = inputTextNLPrelationXMLFileNameList.at(i);
			}
			if(useInputTextNLPfeatureXMLFile)
			{
				inputTextNLPfeatureXMLfileName = inputTextNLPfeatureXMLFileNameList.at(i);
			}
			if(useInputTextXMLFile)
			{
				inputTextXMLFileName = inputTextXMLFileNameList.at(i);
			}
		}
		#endif

		#ifdef NLC_USE_PREPROCESSOR
		if(useNLCpreprocessor)
		{
			workingFolderCharStar = tempFolderCharStar;	//this is required such that GIA uses the temp folder as its input folder (ie workingFolder), considering NLP has already written its output to this folder
		}
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

		#ifdef GIA_USE_CORPUS_DATABASE
			corpusDatabaseFolderName,
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
			timeConditionNodesActiveList,

			&maxNumberSentences
		);

		string NLCfunctionName = "";
		if(useInputTextPlainTXTFile)
		{
			#ifdef NLC_USE_PREPROCESSOR
			if(useNLCpreprocessor && !preprocessorDetectedFunctions)
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

		#ifdef NLC_STRICT_MODE_FAVOUR_COMPILATION_RATHER_THAN_DESIGN_USE_MAIN_ENTRY_POINT
		NLCfunctionName = progLangMainEntryPointFunctionName[progLang];
		#else
		#ifdef NLC_SUPPORT_INPUT_FILE_LISTS
		if(!NLCinputFileList)
		{
		#endif
			NLCfunctionName = removeFileNameExtensions(NLCfunctionName);
		#ifdef NLC_SUPPORT_INPUT_FILE_LISTS
		}
		#endif
		#endif

		#ifdef NLC_SUPPORT_INPUT_FILE_LISTS
		functionNameList.push_back(NLCfunctionName);
		#endif

		#ifdef NLC_DEBUG
		cout << "translateNetwork(): NLCfunctionName = " << NLCfunctionName << endl;
		#endif

		#ifdef NLC_DEBUG
		cout << "transformTheActionOfPossessionEgHavingIntoAproperty():" << endl;
		#endif
		#ifndef GIA_TRANSLATOR_TRANSFORM_THE_ACTION_OF_POSSESSION_EG_HAVING_INTO_A_PROPERTY_BASIC
		transformTheActionOfPossessionEgHavingIntoAproperty(entityNodesActiveListComplete);
		#endif

		#ifdef NLC_DEBUG
		cout << "removeRedundantConditionConjunctions():" << endl;
		#endif

		translateNetwork(firstCodeBlockInTree, &classDefinitionList, entityNodesActiveListComplete, maxNumberSentences, NLCfunctionName, currentNLCfunctionInList, useNLCpreprocessor);

		#ifdef NLC_USE_PREPROCESSOR
		if(useNLCpreprocessor)
		{
			currentNLCfunctionInList = currentNLCfunctionInList->next;
		}
		#endif
	}

	#ifdef NLC_SUPPORT_INPUT_FILE_LISTS
	#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_BASED_ON_IMPLICITLY_DECLARED_VARIABLES_IN_CURRENT_FUNCTION_DEFINITION
	for(int i=0; i<numberOfInputFilesInList; i++)
	{
		//updates all classDefinition functionList function arguments corresponding to a single defined function (i)

		NLCcodeblock * firstCodeBlockInTree = firstCodeBlockInTreeList.at(i);

		string NLCfunctionName = functionNameList.at(i);

		#ifdef NLC_DEBUG
		cout << "start reconcile: NLCfunctionName = " << NLCfunctionName << endl;
		#endif
		/*
		for(vector<NLCitem*>::iterator parametersIterator = firstCodeBlockInTree->parameters.begin(); parametersIterator < firstCodeBlockInTree->parameters.end(); parametersIterator++)
		{
			NLCitem * formalFunctionArgument = *parametersIterator;
			cout << "formalFunctionArgument->className = " << formalFunctionArgument->className << endl;
			cout << "formalFunctionArgument->itemType = " << formalFunctionArgument->itemType << endl;
		}
		*/
		
		reconcileClassDefinitionListFunctionDeclarationArgumentsBasedOnImplicitlyDeclaredVariablesInCurrentFunctionDefinition(firstCodeBlockInTree, &classDefinitionList, NLCfunctionName);
		
		//update variable names in function to 'this' if necessary based on formalFunctionArgumentCorrespondsToActionSubjectUseThisAlias
	}
	#endif
	
	string code = "";
	if(!printClassDefinitions(&classDefinitionList, progLang, &code))
	{
		result = false;
	}
	#endif

	//create predefined NLC functions
	#ifdef NLC_USE_ADVANCED_REFERENCING
	NLCcodeblock * currentCodeBlockInTree = firstCodeBlockInTreeList.at(numberOfInputFilesInList-1);	//get firstCodeBlockInTreeList in last function
	while(currentCodeBlockInTree->next != NULL)
	{
		currentCodeBlockInTree = currentCodeBlockInTree->next;
	}
	currentCodeBlockInTree = createCodeBlockAddEntityToCategoryListCheckLastSentenceReferencedSingularNewFunction(currentCodeBlockInTree, NLC_ITEM_TYPE_CATEGORYVAR_APPENDITION);
	currentCodeBlockInTree = createCodeBlockAddEntityToCategoryListCheckLastSentenceReferencedPluralNewFunction(currentCodeBlockInTree, NLC_ITEM_TYPE_CATEGORYVAR_APPENDITION);
	#ifdef NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT
	currentCodeBlockInTree = addEntityToContextLevelListNewFunction(currentCodeBlockInTree);
	currentCodeBlockInTree = createCodeBlocksClearContextListNewFunction(currentCodeBlockInTree);
	#endif
	#endif
	
	for(int i=0; i<numberOfInputFilesInList; i++)
	{
		NLCcodeblock * firstCodeBlockInTree = firstCodeBlockInTreeList.at(i);
		int level = 0;
		#ifdef NLC_SUPPORT_INPUT_FILE_LISTS
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
	cout << "code = \n" << code << endl;

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
	if(indexOfFirstFileExtension != string::npos)
	{
		NLCfunctionNameCleaned = NLCfunctionName.substr(0, indexOfFirstFileExtension);
	}
	return NLCfunctionNameCleaned;
}

#ifndef GIA_TRANSLATOR_TRANSFORM_THE_ACTION_OF_POSSESSION_EG_HAVING_INTO_A_PROPERTY_BASIC
//this is required for NLC as NLC assumes GIA_TRANSLATOR_TRANSFORM_THE_ACTION_OF_POSSESSION_EG_HAVING_INTO_A_PROPERTY_BASIC
void transformTheActionOfPossessionEgHavingIntoAproperty(vector<GIAentityNode*> * entityNodesActiveListComplete)
{
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode * actionEntity = (*entityIter);
		if((actionEntity->isAction) && !(actionEntity->isConcept) && !(actionEntity->disabled))
		{
			if(actionEntity->entityName == RELATION_ENTITY_SPECIAL_POSSESSIVE)
			{
				#ifdef NLC_DEBUG
				cout << "actionEntity->entityName = " << actionEntity->entityName << endl;
				#endif

				bool actionHasObject = false;
				GIAentityNode * actionObjectEntity = NULL;
				if(!(actionEntity->actionObjectEntity->empty()))
				{
					actionHasObject = true;
					actionObjectEntity = (actionEntity->actionObjectEntity->back())->entity;
				}
				bool actionHasSubject = false;
				GIAentityNode * actionSubjectEntity = NULL;
				if(!(actionEntity->actionSubjectEntity->empty()))
				{
					actionHasSubject = true;
					actionSubjectEntity = (actionEntity->actionSubjectEntity->back())->entity;
				}
				//cout << "transformTheActionOfPossessionEgHavingIntoAproperty(): found and replacing possessive action entity with property" << endl;
				if(actionHasSubject && actionHasObject)
				{
					#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_BASIC_GENERATE_CONTEXT_BLOCKS_IF_SAME_REFERENCE_SET
					//added 1i8g
					bool sameReferenceSet = false;
					GIAentityConnection * actionSubjectConnection = actionEntity->actionSubjectEntity->back();
					GIAentityConnection * actionObjectConnection = actionEntity->actionObjectEntity->back();
					if(actionSubjectConnection->sameReferenceSet && actionObjectConnection->sameReferenceSet)
					{
						sameReferenceSet = true;
					}
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
						GIAentityNode * conditionEntity = (*connectionIter)->entity;

						(conditionEntity->conditionSubjectEntity->back())->entity = actionObjectEntity;
						connectConditionInstanceToSubject(actionObjectEntity, conditionEntity, DEFAULT_SAME_REFERENCE_SET_VALUE_FOR_CONDITIONS);
						#ifdef NLC_DEBUG
						cout << "transformTheActionOfPossessionEgHavingIntoAproperty():  NLC_TRANSFORM_THE_ACTION_OF_POSSESSION_EG_HAVING_CONDITION_INTO_A_PROPERTY_CONDITION case A" << endl;
						#endif
						connectionIter = actionEntity->conditionNodeList->erase(connectionIter);
					}
					for(vector<GIAentityConnection*>::iterator connectionIter = actionEntity->incomingConditionNodeList->begin(); connectionIter !=  actionEntity->incomingConditionNodeList->end(); )
					{
						GIAentityNode * conditionEntity = (*connectionIter)->entity;

						(conditionEntity->conditionObjectEntity->back())->entity = actionObjectEntity;
						connectConditionInstanceToObject(actionObjectEntity, conditionEntity, DEFAULT_SAME_REFERENCE_SET_VALUE_FOR_CONDITIONS);
						#ifdef NLC_DEBUG
						cout << "transformTheActionOfPossessionEgHavingIntoAproperty():  NLC_TRANSFORM_THE_ACTION_OF_POSSESSION_EG_HAVING_CONDITION_INTO_A_PROPERTY_CONDITION case B" << endl;
						#endif
						connectionIter = actionEntity->incomingConditionNodeList->erase(connectionIter);
					}
					#endif

					actionEntity->actionSubjectEntity->clear();
					actionEntity->actionObjectEntity->clear();
					actionEntity->isAction = false;
					actionEntity->disabled = true;	//disable have instance entity
					if(!(actionEntity->entityNodeDefiningThisInstance->empty()))
					{
						getPrimaryConceptNodeDefiningInstance(actionEntity)->disabled = true;	//disable have concept entity
					}

					for(vector<GIAentityConnection*>::iterator connectionIter = actionSubjectEntity->actionNodeList->begin(); connectionIter != actionSubjectEntity->actionNodeList->end(); )
					{
						GIAentityNode * actionEntity2 = (*connectionIter)->entity;
						if(actionEntity2 == actionEntity)
						{
							connectionIter = actionSubjectEntity->actionNodeList->erase(connectionIter);
						}
						else
						{
							connectionIter++;
						}
					}
					for(vector<GIAentityConnection*>::iterator connectionIter = actionObjectEntity->incomingActionNodeList->begin(); connectionIter != actionObjectEntity->incomingActionNodeList->end(); )
					{
						GIAentityNode * actionEntity2 = (*connectionIter)->entity;
						if(actionEntity2 == actionEntity)
						{
							connectionIter = actionObjectEntity->incomingActionNodeList->erase(connectionIter);
						}
						else
						{
							connectionIter++;
						}
					}
					
					#ifdef NLC_VERIFY_CONNECTIONS_SENTENCE_INDEX
					int sentenceIndex = actionEntity->sentenceIndexTemp;
					setCurrentSentenceIndex(sentenceIndex);
					#endif
					//addOrConnectPropertyToEntity(actionSubjectEntity, actionObjectEntity, false);
					GIAentityConnection * propertyConnection = writeVectorConnection(actionSubjectEntity, actionObjectEntity, GIA_ENTITY_VECTOR_CONNECTION_TYPE_PROPERTIES, false);
					GIAentityConnection * propertyConnectionReverse = writeVectorConnection(actionObjectEntity, actionSubjectEntity, GIA_ENTITY_VECTOR_CONNECTION_TYPE_REVERSE_PROPERTIES, false);
					#ifdef NLC_TRANSLATE_NEGATIVE_PROPERTIES_AND_CONDITIONS
					if(actionEntity->negative)
					{
						//cout << "actionEntity->negative" << endl;
						propertyConnection->negative = true;	//this is required for the 1g16a 16-July-2014 "remove properties/conditions" implementation
						propertyConnectionReverse->negative = true;	//not used
					}
					#endif
					#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_BASIC_GENERATE_CONTEXT_BLOCKS_IF_SAME_REFERENCE_SET
					//added 1i8g
					if(sameReferenceSet)
					{
						propertyConnection->sameReferenceSet = true;
						propertyConnectionReverse->sameReferenceSet = true;
					}
					#endif
					#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
					if(actionEntity->negative)
					{
						actionObjectEntity->negative = true;	//this is required to be set for the current logical conditions/conjunctions implementation
					}
					#endif
				}
			}
		}
	}
}

#endif



