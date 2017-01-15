/*******************************************************************************
 *
 * This file is part of BAIPROJECT.
 *
 * BAIPROJECT is commercially licensed software. It may not be redistributed,
 * and may only be used by a registered licensee.
 *
 * BAIPROJECT is sold in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * BAI Commercial License for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You will have received a copy of the BAI Commercial License
 * along with BAIPROJECT. For more information, visit <http://www.baxterai.com>
 *
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: NLClibraryStandardPrint.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2015 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 1t2c 15-September-2016
 * Requirements: requires C++ code to be generated by NLC
 *
 *******************************************************************************/
 
#ifndef HEADER_NLC_LIBRARY_STANDARD_PRINT
#define HEADER_NLC_LIBRARY_STANDARD_PRINT

#define NLC_LIBRARY_STANDARD_PRINT_CONDITIONS_TEMP	//this should not be used for deployment to prevent infinite loops

#include "NLClibraryGenericEntityClass.hpp"

void printFunction(vector<NLCgenericEntityClass*>& printClassList, vector<NLCgenericEntityClass*>& printObjectClassList);
	void printEntity(NLCgenericEntityClass* printObject, int level);
		string createIndentationBasedOnLevel(int level);
void print(double numericalValue);
#ifdef NLC_USE_MATH_OBJECTS_ADVANCED
#ifdef NLC_USE_MATH_OBJECTS_STRING
void print(string stringValue);
#endif
#ifdef NLC_USE_MATH_OBJECTS_BOOLEAN
void print(string boolValue);
#endif
#endif

#endif
