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
 * File Name: NLCglobalDefs.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2014 Baxter AI (baxterai.com)
 * Project: Natural Language Programming Interface (compiler)
 * Project Version: 1g14b 15-July-2014
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/



#ifndef HEADER_NLC_GLOBAL_DEFS
#define HEADER_NLC_GLOBAL_DEFS

#include "SHAREDglobalDefs.h"

#define NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE	//added 1g13b+ 15-July-2014
//#define NLC_PARSE_CONTEXT_DEBUG

#define NLC_DEFINE_LOCAL_VARIABLES_FOR_ALL_INDEFINATE_ENTITIES	//1g8a+ local variable implementation

#define NLC_CLASS_DEFINITIONS_ORDER_BY_DEPENDENCIES	//1f14b (required for C++ compilation)
#define NLC_CLASS_DEFINITIONS_USE_GENERIC_LIBRARY_ENTITY_CLASS	//1f14c (a base NLC entity class is required to be defined for integration of generic NLC Library)
#ifdef NLC_CLASS_DEFINITIONS_USE_GENERIC_LIBRARY_ENTITY_CLASS
	#define NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE "NLCgenericEntity"
#endif
//#define NLC_USE_DESTRUCTORS

#define NLC_SUPPORT_QUANTITIES	//1f3a

#define NLC_SUPPORT_CONDITION_LOGICAL_OPERATIONS		//1f1a+ if statement support
#ifdef NLC_SUPPORT_CONDITION_LOGICAL_OPERATIONS
	#define NLC_ONLY_SUPPORT_LOGICAL_CONJUNCTION_FOR_AT_START_OF_SENTENCE	//this is a more restricted implementation but is faster. It still requires modifications of GIA (it requires entityIndex information to be stored in GIAdatabase.cpp or GIAxmlConversion.cpp)
	#define NLC_LOGICAL_CONDITIONS_SUPPORT_CONJUNCTIONS	//1gXy+ logical if/while/for support + conjunction support
	#ifdef NLC_LOGICAL_CONDITIONS_SUPPORT_CONJUNCTIONS
		#define NLC_MAXIMUM_NUMBER_OF_CONJUNCTIONS_IN_SENTENCE (100)
		#define NLC_TRANSFORM_THE_ACTION_OF_POSSESSION_EG_HAVING_CONDITION_INTO_A_PROPERTY_CONDITION	//assumes #ifndef GIA_TRANSLATOR_TRANSFORM_THE_ACTION_OF_POSSESSION_EG_HAVING_INTO_A_PROPERTY_BASIC
		#define NLC_LOGICAL_CONDITION_CONJUNCTION_BOOLEAN_VARIABLE_NAME "logicalCondition"	//eg logicalCondition1
		#define NLC_WHILE_LOGICAL_CONDITION_CONJUNCTION_BOOLEAN_VARIABLE_NAME "whileLogicalCondition"	//eg whileLogicalCondition1
	#endif
	#define NLC_LOGICAL_CONDITION_OPERATIONS_NUMBER_OF_TYPES (7)
	#define NLC_SUPPORT_CONDITION_LOGICAL_OPERATIONS_BASED_ON_ACTIONS
	#ifdef NLC_SUPPORT_CONDITION_LOGICAL_OPERATIONS_BASED_ON_ACTIONS
		#define NLC_SUPPORT_CONDITION_LOGICAL_OPERATIONS_BASED_ON_ACTIONS_DUMMY_REFERENCE_SET_ID (99)
	#endif
	static string logicalConditionOperationsArray[NLC_LOGICAL_CONDITION_OPERATIONS_NUMBER_OF_TYPES] = {"for", "if", "as", "before", "after", "while", "when"};	//should be dynamically defined in NLCrules.xml
	#define NLC_LOGICAL_CONDITION_OPERATIONS_WORD_IMMEDIATELY_SUCCEEDING_FOR_NUMBER_OF_TYPES (3)
	static string logicalConditionOperationsWordImmediatelySucceedingForArray[NLC_LOGICAL_CONDITION_OPERATIONS_WORD_IMMEDIATELY_SUCCEEDING_FOR_NUMBER_OF_TYPES] = {"each", "all", "every"};	//should be dynamically defined in NLCrules.xml
	#define NLC_CONDITION_LOGICAL_OPERATIONS_FOR (0)	//default
	#define NLC_CONDITION_LOGICAL_OPERATIONS_IF (1)
	#define NLC_CONDITION_LOGICAL_OPERATIONS_WHILE (5)
	#ifdef GIA_CREATE_SUBSTANCE_CONCEPTS_FOR_ALL_SENTENCES_WITH_CONCEPTS	//hasnt been coded [always use substance concept nodes rather than raw concept nodes to store concept relationships]
		#define NLC_SUPPORT_CONDITION_LOGICAL_OPERATIONS_BASED_ON_CONCEPTS
		#ifdef NLC_SUPPORT_CONDITION_LOGICAL_OPERATIONS_BASED_ON_CONCEPTS
			//GIA_CREATE_SUBSTANCE_CONCEPTS_FOR_ALL_SENTENCES_WITH_CONCEPTS hasnt been coded therefore NLC_SUPPORT_CONDITION_LOGICAL_OPERATIONS_BASED_ON_CONCEPTS cannot be used
			//static bool isIncomingOutgoingConditionArray[GIA_ENTITY_NUMBER_OF_VECTOR_CONNECTION_TYPES] = {false, false, true, true, false, false, false, false, false, false, false, false, false, false};
		#endif
	#endif
#endif

//#define NLC_DEBUG_LOGICAL_CONDITION_CONJUNCTIONS
//#define NLC_DEBUG
//#define NLC_DEBUG_PRINT_HIDDEN_CLASSES
//#define NLC_STRICT_MODE_FAVOUR_COMPILATION_RATHER_THAN_DESIGN_USE_MAIN_ENTRY_POINT

#define NLC_LOCAL_LISTS_USE_INSTANCE_NAMES

//#define NLC_CREATE_A_SEPARATE_CLASS_FOR_SUBSTANCE_CONCEPT_DEFINITIONS	//BAD

#define NLC_CREATE_IMPLICITLY_DECLARED_ACTION_OBJECT_AND_SUBJECT_VARIABLES	//1e3a

#define NLC_SUPPORT_INPUT_FILE_LISTS	//added 1d1x
#ifdef NLC_SUPPORT_INPUT_FILE_LISTS
	#define NLC_SUPPORT_INPUT_FILE_LISTS_MAX_INHERITANCE_DEPTH_FOR_CLASS_CASTING (99)
	#define NLC_SUPPORT_INPUT_FILE_LISTS_CHECK_ACTION_SUBJECT_CONTENTS_FOR_IMPLICITLY_DECLARED_PARAMETERS	//added 1d1b
	#define NLC_SUPPORT_INPUT_FILE_LISTS_ACTION_DELIMITER "#"
	#define NLC_SUPPORT_INPUT_FILE_LISTS_ACTION_DELIMITER_LENGTH (1)
	#define NLC_SUPPORT_INPUT_FILE_LISTS_ACTION_OBJECT_DELIMITER "+"
	#define NLC_SUPPORT_INPUT_FILE_LISTS_ACTION_OBJECT_DELIMITER_LENGTH (1)
#endif

#define NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS
//#define NLC_INTERPRET_ACTION_PROPERTIES_AND_CONDITIONS_AS_FUNCTION_ARGUMENTS	//removed 1e1a; now pass action action and action object as arguments cf NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS (do not pass action subject properties and conditions as arguments)
#define NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS	//added 1e1a

#define NLC_PREVENT_INHERITANCE_DOUBLE_DECLARATIONS_OF_CLASS_LIST_VARIABLES
//#define NLC_BAD_IMPLEMENTATION
//#define NLC_USE_STRING_INDEXED_UNORDERED_MAPS_FOR_CONDITION_LISTS

//#define NLC_PRINT_EXPLICIT_LOCAL_CONTEXT
#ifdef NLC_PRINT_EXPLICIT_LOCAL_CONTEXT
	#define NLC_LOCAL_CONTEXT_NAME "locaL"
#endif

#endif
