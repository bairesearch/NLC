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
 * File Name: NLPIglobalDefs.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2013 Baxter AI (baxterai.com)
 * Project: Natural Language Programming Interface (compiler)
 * Project Version: 1e8b 24-November-2013
 * Requirements: requires text parsed by NLP Parser (eg Relex; available in .CFF format <relations>)
 *
 *******************************************************************************/



#ifndef HEADER_NLPI_GLOBAL_DEFS
#define HEADER_NLPI_GLOBAL_DEFS

#include "SHAREDglobalDefs.h"

//#define NLPI_DEBUG
//#define NLPI_DEBUG_PRINT_HIDDEN_CLASSES
//#define NLPI_STRICT_MODE_FAVOUR_COMPILATION_RATHER_THAN_DESIGN_USE_MAIN_ENTRY_POINT

//#define NLPI_CREATE_A_SEPARATE_CLASS_FOR_SUBSTANCE_CONCEPT_DEFINITIONS	//BAD

#define NLPI_SUPPORT_INPUT_FILE_LISTS	//added 1d1x
#ifdef NLPI_SUPPORT_INPUT_FILE_LISTS
	#define NLPI_SUPPORT_INPUT_FILE_LISTS_MAX_INHERITANCE_DEPTH_FOR_CLASS_CASTING (99)
	#define NLPI_SUPPORT_INPUT_FILE_LISTS_CHECK_ACTION_SUBJECT_CONTENTS_FOR_IMPLICITLY_DECLARED_PARAMETERS	//added 1d1b
	#define NLPI_SUPPORT_INPUT_FILE_LISTS_ACTION_DELIMITER "#"
	#define NLPI_SUPPORT_INPUT_FILE_LISTS_ACTION_DELIMITER_LENGTH (1)
	#define NLPI_SUPPORT_INPUT_FILE_LISTS_ACTION_OBJECT_DELIMITER "+"
	#define NLPI_SUPPORT_INPUT_FILE_LISTS_ACTION_OBJECT_DELIMITER_LENGTH (1)
#endif

#define NLPI_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS
//#define NLPI_INTERPRET_ACTION_PROPERTIES_AND_CONDITIONS_AS_FUNCTION_ARGUMENTS	//removed 1e1a; now pass action action and action object as arguments cf NLPI_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS (do not pass action subject properties and conditions as arguments)
#define NLPI_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS	//added 1e1a

#define NLPI_PREVENT_INHERITANCE_DOUBLE_DECLARATIONS_OF_CLASS_LIST_VARIABLES
//#define NLPI_BAD_IMPLEMENTATION
//#define NLPI_USE_STRING_INDEXED_UNORDERED_MAPS_FOR_CONDITION_LISTS

//#define NLPI_PRINT_EXPLICIT_LOCAL_CONTEXT
#ifdef NLPI_PRINT_EXPLICIT_LOCAL_CONTEXT
	#define NLPI_LOCAL_CONTEXT_NAME "locaL"
#endif

#endif
