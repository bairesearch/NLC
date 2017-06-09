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
 * Project Version: 2c1c 01-June-2017
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

#ifndef HEADER_NLCI_GLOBAL_DEFS
#define HEADER_NLCI_GLOBAL_DEFS

#include "NLCglobalDefs.hpp"

//#define NLCI_OPEN_NLC
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
#else
#define NLCI_HOME_FOLDER "/home/user"	//QDir::homePath()
#endif

#ifdef USE_NLCI
#define NLCI_NLC_NLP_CLIENT (true)
#define NLCI_NLC_USE_LRP (true)
#define NLCI_NLC_LRP_FOLDER NLCI_HOME_FOLDER "/source/source/LRPdata"
#define NLCI_NLC_USE_NLC_PREPROCESSOR (true)
#define NLCI_NLC_USE_OUTPUT_TEXT_ALL_FILE (true)
#define NLCI_NLC_PRINT_OUTPUT (true)
#define NLCI_NLC_OUTPUT_TEXT_ALL_FILE_NAME "semanticNet"
#define NLCI_NLC_NLP_FEATURE_PARSER (GIA_NLP_FEATURE_PARSER_FOR_INPUT_TEXT_DEFAULT)
#define NLCI_NLC_NLP_DEPENDENCY_RELATIONS_PARSER (GIA_NLP_RELATIONS_PARSER_FOR_INPUT_TEXT_DEFAULT)
#define NLCI_NLC_NLP_RELEX_FOLDER NLCI_HOME_FOLDER "/soft/BAISource/relex/relex-1.4.0"
#define NLCI_NLC_NLP_STANFORD_CORE_NLP_FOLDER NLCI_HOME_FOLDER "/soft/BAISource/stanford/coreNLP/stanford-corenlp-full-2016-10-31"
#define NLCI_NLC_NLP_STANFORD_PARSER_FOLDER NLCI_HOME_FOLDER "/soft/BAISource/stanford/parser/stanford-parser-full-2016-10-31"
#define NLCI_NLC_INPUT_FOLDER NLCI_HOME_FOLDER "/source/NLCinput"
#define NLCI_NLC_OUTPUT_FOLDER NLCI_HOME_FOLDER "/source/NLCgenerated"
#ifdef NLCI_OPEN_NLC
#define NLCI_NLC_EXE_NAME_COMPILE_NLC_LIBRARY_GENERATED "compileOpenNLClibraryGenerated.bat"	//or compileOpenNLClibraryGenerated.bat
#else
#define NLCI_NLC_EXE_NAME_COMPILE_NLC_LIBRARY_GENERATED "compileNLClibraryGenerated.bat"	//or compileOpenNLClibraryGenerated.bat
#endif
#define NLCI_NLC_EXE_NAME_NLC_GENERATED_PROGRAM "NLCgeneratedProgram.exe"
#define NLCI_INPUT_FOLDER (NLCI_NLC_INPUT_FOLDER)
#define NLCI_LRP_FOLDER (NLCI_NLC_LRP_FOLDER)
#elif defined USE_GIAI
#define GIAI_GIA_NLP_CLIENT (true)
#define GIAI_GIA_USE_LRP (true)
#define GIAI_GIA_LRP_FOLDER NLCI_HOME_FOLDER "/source/source/LRPdata"
#define GIAI_GIA_USE_NLC_PREPROCESSOR (true)
#define GIAI_GIA_USE_OUTPUT_TEXT_ALL_FILE (true)
#define GIAI_GIA_PRINT_OUTPUT (true)
#define GIAI_GIA_PRINT_OUTPUT_QUERY (true)
#define GIAI_GIA_OUTPUT_TEXT_ALL_FILE_NAME "semanticNet"
#define GIAI_GIA_NLP_FEATURE_PARSER (GIA_NLP_FEATURE_PARSER_FOR_INPUT_TEXT_DEFAULT)
#define GIAI_GIA_NLP_DEPENDENCY_RELATIONS_PARSER (GIA_NLP_RELATIONS_PARSER_FOR_INPUT_TEXT_DEFAULT)
#define GIAI_GIA_NLP_FEATURE_PARSER_QUERY (GIA_NLP_FEATURE_PARSER_FOR_INPUT_TEXT_DEFAULT)
#define GIAI_GIA_NLP_DEPENDENCY_RELATIONS_PARSER_QUERY (GIA_NLP_RELATIONS_PARSER_FOR_INPUT_TEXT_DEFAULT)
#define GIAI_GIA_NLP_RELEX_FOLDER NLCI_HOME_FOLDER "/soft/BAISource/relex/relex-1.4.0"
#define GIAI_GIA_NLP_STANFORD_CORE_NLP_FOLDER NLCI_HOME_FOLDER "/soft/BAISource/stanford/coreNLP/stanford-corenlp-full-2016-10-31"
#define GIAI_GIA_NLP_STANFORD_PARSER_FOLDER NLCI_HOME_FOLDER "/soft/BAISource/stanford/parser/stanford-parser-full-2016-10-31"
#define GIAI_GIA_INPUT_FOLDER NLCI_HOME_FOLDER "/source/GIAworking"
#define GIAI_GIA_OUTPUT_FOLDER NLCI_HOME_FOLDER "/source/GIAworking"
#define NLCI_INPUT_FOLDER (GIAI_GIA_INPUT_FOLDER)
#define NLCI_LRP_FOLDER (GIAI_GIA_LRP_FOLDER)
#endif


#endif
