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
 * File Name: NLCIglobalDefs.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2018 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler Interface
 * Project Version: 2f1b 22-February-2018
 * Requirements: 
 * /
 *******************************************************************************/


#ifndef HEADER_NLCI_GLOBAL_DEFS
#define HEADER_NLCI_GLOBAL_DEFS

#include "NLCglobalDefs.hpp"

#define NLCI_OPEN_NLC

//#define NLCI_PROJECT_NLC_FILE_LIST_STORE_FULL_PATHS	//this will not work if the user adds a new file of the same name as an already associated file to the project
//#define NLCI_EDITOR_HIGHLIGHT_HTML	//else use qt syntax highlighter

#define NLCI_MAIN_WINDOW_WIDTH (640)
#define NLCI_MAIN_WINDOW_HEIGHT (480)
#define NLCI_EDITOR_WINDOW_WIDTH (640)
#define NLCI_EDITOR_WINDOW_HEIGHT (480)
#define NLCI_TEXT_DISPLAY_WINDOW_WIDTH (640)
#define NLCI_TEXT_DISPLAY_WINDOW_HEIGHT (480)
#define NLCI_TEXT_DISPLAY_WINDOW_NLC_GENERATED_WIDTH (640)
#define NLCI_TEXT_DISPLAY_WINDOW_NLC_GENERATED_HEIGHT (480)
#define NLCI_SEMANTIC_NETWORK_DISPLAY_WINDOW_WIDTH (640)
#define NLCI_SEMANTIC_NETWORK_DISPLAY_WINDOW_HEIGHT (480)
#define NLCI_SEMANTIC_NETWORK_FULL_DISPLAY_WINDOW_WIDTH (1920)
#define NLCI_SEMANTIC_NETWORK_FULLDISPLAY_WINDOW_HEIGHT (1080)

#ifdef NLCI_OPEN_NLC
#define NLCI_HOME_FOLDER "/home/user"	//QDir::homePath()
#define NLCI_NLC_ROOT_FOLDER NLCI_HOME_FOLDER "/source/git/repositories/NLC"
#define NLCI_GIA_ROOT_FOLDER NLCI_HOME_FOLDER "/source/git/repositories/NLC"
#else
#define NLCI_HOME_FOLDER "/home/user"	//QDir::homePath()
#define NLCI_NLC_ROOT_FOLDER NLCI_HOME_FOLDER "/source"
#define NLCI_GIA_ROOT_FOLDER NLCI_HOME_FOLDER "/source"
#endif
#define NLCI_NLP_ROOT_FOLDER NLCI_HOME_FOLDER "/soft/BAISource"
#define NLCI_NLP_RELEX_FOLDER NLCI_NLP_ROOT_FOLDER "/relex/relex-1.4.0"
#define NLCI_NLP_STANFORD_CORE_NLP_FOLDER NLCI_NLP_ROOT_FOLDER "/stanford/coreNLP/stanford-corenlp-full-2016-10-31"
#define NLCI_NLP_STANFORD_PARSER_FOLDER NLCI_NLP_ROOT_FOLDER "/stanford/parser/stanford-parser-full-2016-10-31"
#define NLCI_LRP_ROOT_FOLDER NLCI_HOME_FOLDER "/source/source/LRPdata"


#ifdef USE_NLCI

#define NLCI_NLC_NLP_CLIENT (true)
#define NLCI_NLC_USE_LRP (true)
#define NLCI_NLC_LRP_FOLDER NLCI_LRP_ROOT_FOLDER
#define NLCI_NLC_USE_NLC_PREPROCESSOR (true)
#define NLCI_NLC_USE_OUTPUT_TEXT_ALL_FILE (true)
#define NLCI_NLC_PRINT_OUTPUT (true)
#define NLCI_NLC_OUTPUT_TEXT_ALL_FILE_NAME "semanticNet"
#define NLCI_NLC_NLP_FEATURE_PARSER (GIA_NLP_FEATURE_PARSER_FOR_INPUT_TEXT_DEFAULT)
#define NLCI_NLC_NLP_DEPENDENCY_RELATIONS_PARSER (GIA_NLP_RELATIONS_PARSER_FOR_INPUT_TEXT_DEFAULT)
#define NLCI_NLC_NLP_RELEX_FOLDER NLCI_NLP_RELEX_FOLDER
#define NLCI_NLC_NLP_STANFORD_CORE_NLP_FOLDER NLCI_NLP_STANFORD_CORE_NLP_FOLDER
#define NLCI_NLC_NLP_STANFORD_PARSER_FOLDER NLCI_NLP_STANFORD_PARSER_FOLDER
#define NLCI_NLC_INPUT_FOLDER NLCI_NLC_ROOT_FOLDER "/NLCinput"
#define NLCI_NLC_OUTPUT_FOLDER NLCI_NLC_ROOT_FOLDER "/NLCgenerated"
#ifdef NLCI_OPEN_NLC
#define NLCI_NLC_EXE_NAME_COMPILE_NLC_LIBRARY_GENERATED "compileOpenNLClibraryGenerated.bat"	//or compileOpenNLClibraryGenerated.bat
#else
#define NLCI_NLC_EXE_NAME_COMPILE_NLC_LIBRARY_GENERATED "compileNLClibraryGenerated.bat"	//or compileOpenNLClibraryGenerated.bat
#endif
#define NLCI_NLC_EXE_NAME_NLC_GENERATED_PROGRAM "NLCgeneratedProgram.exe"
#define NLCI_INPUT_FOLDER (NLCI_NLC_INPUT_FOLDER)
#define NLCI_LRP_FOLDER (NLCI_NLC_LRP_FOLDER)
#define NLCI_NLC_FILE_TYPE_FILTER_NAME "nlc files (*.nlc)"
#define NLCI_NLC_PROJECT_FILE_TYPE_FILTER_NAME "nlcp files (*.nlcp)"
#define NLCI_FILE_TYPE_FILTER_NAME (NLCI_NLC_FILE_TYPE_FILTER_NAME)
#define NLCI_FILE_TYPE (NLC_NATURAL_LANGUAGE_CODE_FILE_NAME_EXTENSION)

#elif defined USE_GIAI

#define NLCI_GIA_NLP_CLIENT (true)
#define NLCI_GIA_USE_LRP (true)
#define NLCI_GIA_LRP_FOLDER NLCI_LRP_ROOT_FOLDER
#define NLCI_GIA_USE_NLC_PREPROCESSOR (true)
#define NLCI_GIA_USE_OUTPUT_TEXT_ALL_FILE (true)
#define NLCI_GIA_PRINT_OUTPUT (true)
#define NLCI_GIA_PRINT_OUTPUT_QUERY (true)
#define NLCI_GIA_OUTPUT_TEXT_ALL_FILE_NAME "semanticNet"
#define NLCI_GIA_NLP_FEATURE_PARSER (GIA_NLP_FEATURE_PARSER_FOR_INPUT_TEXT_DEFAULT)
#define NLCI_GIA_NLP_DEPENDENCY_RELATIONS_PARSER (GIA_NLP_RELATIONS_PARSER_FOR_INPUT_TEXT_DEFAULT)
#define NLCI_GIA_NLP_FEATURE_PARSER_QUERY (GIA_NLP_FEATURE_PARSER_FOR_INPUT_TEXT_DEFAULT)
#define NLCI_GIA_NLP_DEPENDENCY_RELATIONS_PARSER_QUERY (GIA_NLP_RELATIONS_PARSER_FOR_INPUT_TEXT_DEFAULT)
#define NLCI_GIA_NLP_RELEX_FOLDER NLCI_NLP_RELEX_FOLDER
#define NLCI_GIA_NLP_STANFORD_CORE_NLP_FOLDER NLCI_NLP_STANFORD_CORE_NLP_FOLDER
#define NLCI_GIA_NLP_STANFORD_PARSER_FOLDER NLCI_NLP_STANFORD_PARSER_FOLDER
#define NLCI_GIA_INPUT_FOLDER NLCI_GIA_ROOT_FOLDER "/GIAinput"
#define NLCI_GIA_OUTPUT_FOLDER NLCI_GIA_ROOT_FOLDER "/GIAgenerated"
#define NLCI_INPUT_FOLDER (NLCI_GIA_INPUT_FOLDER)
#define NLCI_LRP_FOLDER (NLCI_GIA_LRP_FOLDER)
#define NLCI_GIA_FILE_TYPE_FILTER_NAME "text files (*.txt)"
#define NLCI_FILE_TYPE_FILTER_NAME (NLCI_GIA_FILE_TYPE_FILTER_NAME)
#define NLCI_FILE_TYPE ".txt"

#endif


#endif
