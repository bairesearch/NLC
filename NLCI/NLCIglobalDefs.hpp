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
 * File Name: NLCIglobalDefs.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2017 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler Interface
 * Project Version: 2d3a 12-November-2017
 * Requirements: 
 *
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
