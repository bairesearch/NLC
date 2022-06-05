 /*******************************************************************************
 *
 * License: GNU Affero General Public License version 3 (AGPLv3)
 *
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: NLClibraryStandardPrint.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2022 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 2p1a 05-June-2022
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
void print(double mathObjectNumericalValue);
#ifdef NLC_MATH_OBJECTS_ADVANCED
#ifdef NLC_MATH_OBJECTS_STRING
void print(string mathObjectStringValue);
#endif
#ifdef NLC_MATH_OBJECTS_BOOLEAN
void print(string boolValue);
#endif
#endif

#endif
