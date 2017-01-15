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
 * File Name: NLPIclassDefinition.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2013 Baxter AI (baxterai.com)
 * Project: Natural Language Programming Interface (compiler)
 * Project Version: 1a3a 03-October-2013
 * Requirements: requires text parsed by NLP Parser (eg Relex; available in .CFF format <relations>)
 *
 *******************************************************************************/


#ifndef HEADER_NLPI_CLASSDEFINITION
#define HEADER_NLPI_CLASSDEFINITION

#include <iostream>
#include <fstream>
#include <ctime>
#include <cstring>
#include <cstdlib>	//for random number generation
#include <cmath>
#include <string>
#include <vector>
#include <vector>
#include <unordered_map>
using namespace std;

#define NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES (7)	//this needs to be moved to NLPIglobalDefs.h

static string progLangClassTitlePrepend[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"class ", "class ", "class ", "class ", "class ", "class ", "class "};
static string progLangOpenClass[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"{", "{", "{", "{", "{", "{", "{"};
static string progLangCloseClass[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"};", "};", "};", "};", "};", "};", "};"};
static string progLangClassIntro[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"public:", "public:", "public:", "public:", "public:", "public:", "public:"};
static string progLangClassConstructorDestructorAppend[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"(void);", "(void);", "(void);", "(void);", "(void);", "(void);", "(void);"};
static string progLangClassDestructorPrepend[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"~", "~", "~", "~", "~", "~", "~"};
static string progLangClassListTypeStart[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"vector<", "vector<", "vector<", "vector<", "vector<", "vector<", "vector<"};
static string progLangClassListTypeEnd[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {" *> ", " *> ", " *> ", " *> ", " *> ", " *> ", " *> "};
static string progLangClassNameType[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"string ", "string ", "string ", "string ", "string ", "string ", "string "};
static string progLangClassMemberFunctionType[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"void ", "void ", "void ", "void ", "void ", "void ", "void "};
static string progLangClassMemberFunctionParameters[NLPI_NUMBER_OF_PROGRAMMING_LANGUAGES] = {"()", "()", "()", "()", "()", "()", "()"};

	//progLangEndLine
	
class NLPIclassDefinition
{
public:

	NLPIclassDefinition(void);
	NLPIclassDefinition(string newName);
	~NLPIclassDefinition(void);
	
	string name;
	vector<NLPIclassDefinition *> propertyList;	//subclass
	vector<NLPIclassDefinition *> conditionList;	//declared conditions
	vector<NLPIclassDefinition *> definitionList;	//inherited parents
	vector<NLPIclassDefinition *> functionList;
};

NLPIclassDefinition * findClassDefinition(vector<NLPIclassDefinition *> * classDefinitionList, string className, bool * foundClassDefinition);




#endif
