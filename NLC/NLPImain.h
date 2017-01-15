/*******************************************************************************
 *
 * This file is part of BAIPROJECT.
 *
 * BAIPROJECT is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License version 3
 * only, as published by the Free Software Foundation.
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
 * File Name: NLPImain.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2013 Baxter AI (baxterai.com)
 * Project: Natural Language Programming Interface (compiler)
 * Project Version: 1a1a 28-June-2013
 * Requirements: requires text parsed by NLP Parser (eg Relex; available in .CFF format <relations>)
 *
 *******************************************************************************/


#ifndef HEADER_NLPI_MAIN
#define HEADER_NLPI_MAIN

#include <iostream>
#include <fstream>
#include <ctime>
#include <cstring>
#include <cstdlib>	//for random number generation
#include <cmath>
#include <string>
#include <vector>
using namespace std;

#define NLPI_CODEBLOCK_TYPE_UNDEFINED (-1)
#define NLPI_CODEBLOCK_TYPE_FOR (1)
#define NLPI_CODEBLOCK_TYPE_IF_HAS_PROPERTIES (2)
#define NLPI_CODEBLOCK_TYPE_IF_SATISFIES_CONDITIONS (3)
#define NLPI_DEFAULT_CONTEXT "nlpiDefaultContext"	//eg "this."?
//shared with GIAtranslatorDefineReferencing.cpp
class NLPIcodeblock
{
public:

	NLPIcodeblock(void);
	~NLPIcodeblock(void);

	codeBlockType = -1;
	vector<string> parameters;
	
	//used by language specific code generator (eg C++, java);
	string codeBlockType; 	//eg "for"
	string openingText;	//eg "for(...){"
	string closingText; 	//eg "}";
	
	NLPIcodeblock * lowerLevel;
	NLPIcodeblock * next;
};

NLPIcodeblock * createCodeBlock(NLPIcodeblock * currentCodeBlockInTree, int codeBlockType);

int main(int argc,char **argv);

bool executeNLPI();

#endif
