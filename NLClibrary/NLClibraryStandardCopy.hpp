 /*******************************************************************************
 *
 * License: GNU Affero General Public License version 3 (AGPLv3)
 *
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: NLClibraryStandardCopy.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2022 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 2p1a 05-June-2022
 * Requirements: requires C++ code to be generated by NLC
 *
 *******************************************************************************/

#ifndef HEADER_NLC_LIBRARY_STANDARD_COPY
#define HEADER_NLC_LIBRARY_STANDARD_COPY

#include "NLClibraryGenericEntityClass.hpp"

void copyFunction(vector<NLCgenericEntityClass*>& copyClassList, vector<NLCgenericEntityClass*>& copyObjectClassList);
NLCgenericEntityClass* copyObjectAndChildren(NLCgenericEntityClass* objectToCopy);
	NLCgenericEntityClass* copyObjectAndProperties(NLCgenericEntityClass* objectToCopy);
	#ifdef NLC_LIBRARY_COPY_FUNCTION_COPY_INTERNAL_CONDITION_LISTS
	void copyConditionLinks(NLCgenericEntityClass* objectToCopyTopLevel, NLCgenericEntityClass* objectToCopy, NLCgenericEntityClass* copyOfCopyObject);
		bool findObjectInPropertyHierarchy(NLCgenericEntityClass* object, NLCgenericEntityClass* objectToFind);
	#endif
NLCgenericEntityClass* copyObjectByNameWithoutChildren(string name, NLCgenericEntityClass* entityToCopy);
#endif
