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
 * File Name: NLClibraryBase.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2016 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 1w4a 17-January-2017
 * Requirements: requires C++ code to be generated by NLC
 * Description: Base NLC library Functions (no generic property and condition lists) 
 * Note: These functions are hard coded and dual licensed under AGPLv3 and BAI Commercial
 *
 *******************************************************************************/
 
#ifndef HEADER_NLC_LIBRARY_BASE
#define HEADER_NLC_LIBRARY_BASE

#include "NLClibraryGenericEntityClass.hpp"
#ifdef NLC_LIBRARY_BASE_EXTENDED
#include "NLClibraryBaseExtended.hpp"
#endif

#ifdef NLC_PERFORM_PLURAL_DEFINITE_REFERENCING_TESTS
template <class E1, class E2>
void addToCategoryIfPassPluralDefiniteReferencingTests(vector<E1*>& entityCategoryList, E2* entity0);
#endif
#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS
template <class E1, class E2>
vector<E2*>& castVector(vector<E1*>& E1List);
#ifdef NLC_CONDITION_LISTS_VECTOR
template <class E1, class E2, class E3, class E4>
vector<pair<E3*, E4*>*>& castVectorPair(vector<pair<E1*, E2*>*>& E1E2List);
#else
template <class E1, class E2, class E3, class E4>
unordered_map<E3*, E4*>& castUnorderedMap(unordered_map<E1*, E2*>& E1E2List);	//not currently used
#endif
#endif

#ifdef NLC_ADVANCED_REFERENCING
#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN
template <class E1, class E2>
void addToCategoryIfPassSingularDefiniteReferencingTests(vector<E1*>& entityCategoryList, E2* entity0);
#endif
#ifdef NLC_ADVANCED_REFERENCING_SUPPORT_ALIASES
template <class E1>
void findAliasAndAddToCategoryList(vector<E1*>& E1List, string aliasName, vector<E1*>& E1CategoryList);
template <class E1>
bool findAliasNewFunction(E1* E1instance, string aliasName);
#endif
#endif

#include "NLClibraryBase.cpp"

#endif
