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
 * File Name: NLClibraryBaseExtended.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2016 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 1u13b 02-October-2016
 * Requirements: requires C++ code to be generated by NLC
 * Description: Base NLC library Functions (no generic property and condition lists) 
 * Note: These extended functions are not generally hard coded (unlike those in 
 * NLClibraryBase) but are still dual licensed under AGPLv3 and BAI Commercial
 *
 *******************************************************************************/
 
#ifndef HEADER_NLC_LIBRARY_BASE_EXTENDED
#define HEADER_NLC_LIBRARY_BASE_EXTENDED

#include "NLClibraryGenericEntityClass.hpp"

#ifdef NLC_USE_LIBRARY_BASE_EXTENDED
template <class E1, class E2>
void addProperty(E1* E1Instance, vector<E2*>* E2propertyList, E2* E2Instance);
template <class E1, class E2, class E3>
#ifdef NLC_CONDITION_LISTS_VECTOR
void addCondition(E1* E1Instance, vector<pair<E2*, E3*>*>* E2E3conditionList, string E2className, E3* E3Instance);	//NB E2className is redundant as it can be generated from new E2()
#else
void addCondition(E1* E1Instance, unordered_map<E2*, E3*>* E2E3conditionList, string E2className, E3* E3Instance);	//NB E2className is redundant as it can be generated from new E2()
#endif
#ifdef NLC_NORMALISE_TWOWAY_PREPOSITIONS_MARK_INVERSE_CONDITIONS
template <class E1, class E2, class E3>
#ifdef NLC_CONDITION_LISTS_VECTOR
void addConditionInverse(E1* E1Instance, vector<pair<E2*, E3*>*>* E2E3conditionList, string E2className, E3* E3Instance);	//NB E2className is redundant as it can be generated from new E2()
#else
void addConditionInverse(E1* E1Instance, unordered_map<E2*, E3*>* E2E3conditionList, string E2className, E3* E3Instance);	//NB E2className is redundant as it can be generated from new E2()
#endif
#endif
template <class E1, class E2>
void addActionSubject(E1* E1action, E2* E2actionSubject, vector<E1*>* E1actionList, vector<E2*>* E2actionSubjectList);
template <class E1, class E2>
void addActionObject(E1* E1action, E2* E2actionObject, vector<E1*>* E1actionIncomingList, vector<E2*>* E2actionObjectList);

template <class E1, class E2>
void removeProperty(E1* E1Instance, vector<E2*>* E2propertyList, E2* E2Instance);
template <class E1, class E2, class E3>
#ifdef NLC_CONDITION_LISTS_VECTOR
void removeCondition(E1* E1Instance, vector<pair<E2*, E3*>*>* E2E3conditionList, string E2className, E3* E3Instance);	//NB E2className is redundant as it can be generated from new E2()
#else
void removeCondition(E1* E1Instance, unordered_map<E2*, E3*>* E2E3conditionList, string E2className, E3* E3Instance);	//NB E2className is redundant as it can be generated from new E2()
#endif
template <class E1, class E2>
void removeProperties(E1* E1Instance, vector<E2*>* E2propertyList, E2* E2Instance);
template <class E1, class E2, class E3>
#ifdef NLC_CONDITION_LISTS_VECTOR
void removeConditions(E1* E1Instance, vector<pair<E2*, E3*>*>* E2E3conditionList, string E2className, E3* E3Instance);	//NB E2className is redundant as it can be generated from new E2()
#else
void removeConditions(E1* E1Instance, unordered_map<E2*, E3*>* E2E3conditionList, string E2className, E3* E3Instance);	//NB E2className is redundant as it can be generated from new E2()
#endif

#ifdef NLC_USE_ENUM_LISTS
#ifdef NLC_USE_ENUM_LISTS_PROPERTIES
template <class E1, class E2>
void addEnumProperty(E1* E1Instance, E2* E2Instance, vector<NLCgenericEntityClass*>* propertyList);
template <class E1, class E2>
void clearExistingEnumProperty(E1* E1Instance, E2* E2Instance);
#endif
#ifdef NLC_USE_ENUM_LISTS_CONDITIONS
template <class E1, class E2, class E3>
#ifdef NLC_CONDITION_LISTS_VECTOR
void addEnumCondition(E1* E1Instance, E2* E2Instance, E3* E3Instance, vector<pair<NLCgenericEntityClass*, NLCgenericEntityClass*>*>* conditionList);
#else
void addEnumCondition(E1* E1Instance, E2* E2Instance, E3* E3Instance, unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>* conditionList);
#endif
template <class E1, class E2, class E3>
void clearExistingEnumCondition(E1* E1Instance, string E2className, E3* E3Instance);
#endif
#endif

template <class E1>
E1* addNewEntityToLocalList(vector<E1*>* E1classList);
template <class E1>
void addEntityToLocalList(vector<E1*>* E1classList, E1* E1Instance);

template <class E1>
bool removeItemFromVectorList(vector<E1*>* vectorList, E1* itemToRemove);
template <class E1, class E2>
#ifdef NLC_CONDITION_LISTS_VECTOR
bool removeItemFromConditionList(vector<pair<E1*, E2*>*>* unorderedMap, string conditionName, pair<E1*, E2*>*itemToRemove);
#else
bool removeItemFromConditionList(unordered_map<E1*, E2*>* unorderedMap, string conditionName, pair<E1*, E2*>*itemToRemove);
/*
template <class E1, class E2>
bool removeObjectFromConditionList(unordered_map<E1*, E2*>* unorderedMap, E2 *objectToRemove);
*/
#endif

#endif

#include "NLClibraryBaseExtended.cpp"

#endif
