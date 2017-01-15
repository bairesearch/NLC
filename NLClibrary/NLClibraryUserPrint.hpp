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
 * File Name: NLClibraryUserPrint.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2016 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 1u1b 24-September-2016
 * Requirements: requires C++ code to be generated by NLC
 *
 *******************************************************************************/
 
#ifndef HEADER_NLC_LIBRARY_USER_PRINT
#define HEADER_NLC_LIBRARY_USER_PRINT

#define NLC_LIBRARY_USER_PRINT_CONDITIONS_TEMP	//this should not be used for deployment to prevent infinite loops

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
