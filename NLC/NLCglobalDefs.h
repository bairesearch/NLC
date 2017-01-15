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
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2016 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 1t1d 12-September-2016
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/


#ifndef HEADER_NLC_GLOBAL_DEFS
#define HEADER_NLC_GLOBAL_DEFS

#include "SHAREDglobalDefs.h"
#include "GIAglobalDefs.h"

#define NLC_USE_LIBRARY_STANDARD	//disabled for OpenNLC
//#define NLC_USE_LIBRARY_USER
#ifndef NLC_DISABLE_1q_CODE_FOR_DEBUG
	//#define NLC_USE_LIBRARY_GENERATE_INDIVIDUAL_FILES       //1q1a
#endif

//#define NLC_DISABLE_1i_CODE_FOR_DEBUG - requires !GIA_DISABLE_CROSS_SENTENCE_REFERENCING
//#define NLC_DISABLE_1j_CODE_FOR_DEBUG - requires !GIA_DISABLE_CROSS_SENTENCE_REFERENCING
//#define NLC_DISABLE_1k_CODE_FOR_DEBUG - requires GIA_DISABLE_CROSS_SENTENCE_REFERENCING
//#define NLC_DISABLE_1l_CODE_FOR_DEBUG
//#define NLC_DISABLE_1m_CODE_FOR_DEBUG
//#define NLC_DISABLE_1n_CODE_FOR_DEBUG
//#define NLC_DISABLE_1o_CODE_FOR_DEBUG
//#define NLC_DISABLE_1p_CODE_FOR_DEBUG
//#define NLC_DISABLE_1q_CODE_FOR_DEBUG
//#define NLC_DISABLE_1r_CODE_FOR_DEBUG
//#define NLC_DISABLE_1s_CODE_FOR_DEBUG
//#define NLC_DISABLE_1t_CODE_FOR_DEBUG

#ifndef NLC_DISABLE_1s_CODE_FOR_DEBUG
	//#ifdef NLC_SUPPORT_REDEFINITIONS	//has not yet been defined
		#define NLC_SUPPORT_REDEFINITIONS_VERIFY_PARENT_CLASS_INTERNALLY	//1s7a
	//#endif
	#define NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS_USE_MORE_PRECISE_BUT_REDUNDANT_FUNCTIONS	//1s8a
	#ifdef GIA_TRANSLATOR_INTERPRET_PRENOMINAL_MODIFIER_SUBCLASSES
		#ifdef GIA_TRANSLATOR_INTERPRET_PRENOMINAL_MODIFIER_SUBCLASSES_DETECT_USER_DECLARED_SUBCLASS_ENTITIES
			#define NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN_SUBCLASSES	//1s8a
		#endif
		#ifdef GIA_TRANSLATOR_INTERPRET_PRENOMINAL_MODIFIER_SUBCLASSES_ENABLE_INCONSISTENT_REFERENCING
			#define NLC_SUPPORT_SENTENCES_WITH_MULTIPLE_NON_SAME_REFERENCE_SET_CONNECTIONS	//1s6a
		#endif
	#endif
	//#ifdef NLC_GENERATE_OBJECT_INITIALISATIONS_BASED_ON_CONCEPTS	//has not yet been defined
		#define NLC_GENERATE_OBJECT_INITIALISATIONS_BASED_ON_CONCEPTS_DEFINITIONS	//1s2a
		#define NLC_GENERATE_OBJECT_INITIALISATIONS_BASED_ON_CONCEPTS_REMOVE_REDUNDANT_CODE	//1s3a	//is this code required for non-category lists (!NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN)? is it required for instance lists (ie !NLC_USE_ADVANCED_REFERENCING)?
	//#endif
#endif

#ifndef NLC_DISABLE_1r_CODE_FOR_DEBUG
	#define NLC_USE_MATH_OBJECTS_ADVANCED	//1r5c	//requires NLC_USE_LIBRARY_BASE_EXTENDED
	#ifdef NLC_USE_MATH_OBJECTS_ADVANCED
		#define NLC_USE_MATH_OBJECTS_ADVANCED_ASSIGN_MATHOBJECT_VALUE_FUNCTION_NAME "assignMathObjectValue"
		#define NLC_USE_MATH_OBJECTS_ADVANCED_GET_MATHOBJECT_VALUE_FUNCTION_NAME "getMathObjectValue"
		#define NLC_USE_MATH_OBJECTS_STRING	//1r5c
		#ifdef NLC_USE_MATH_OBJECTS_STRING
			#define NLC_USE_MATH_OBJECTS_STRING_DELIMITER STRING_INVERTED_COMMAS
			#define NLC_USE_MATH_OBJECTS_STRING_DELIMITER_CHAR CHAR_INVERTED_COMMAS
		#endif
		#define NLC_USE_MATH_OBJECTS_BOOLEAN	//1r5l
		#ifdef NLC_USE_MATH_OBJECTS_BOOLEAN
			#define NLC_USE_MATH_OBJECTS_BOOLEAN_VALUE_TRUE "true"
			#define NLC_USE_MATH_OBJECTS_BOOLEAN_VALUE_FALSE "false"
		#endif
		#define NLC_USE_MATH_OBJECTS_ADVANCED_INFER_TYPE_BASED_ON_PREVIOUSLY_DECLARED_MATHTEXT_VARIABLES	//1r5l	//NB this code is not absolutely required (as the getMathObjectValue return type will be inferred when compiling generated code), however it will simplify/normalise the generated output code
		#ifdef NLC_USE_MATH_OBJECTS_ADVANCED_INFER_TYPE_BASED_ON_PREVIOUSLY_DECLARED_MATHTEXT_VARIABLES
			#define NLC_PREPROCESSOR_MATH_FIX_BUG_ADD_MATH_TEXT_VARIABLES_TO_FIRST_PHRASE_IN_FULL_SENTENCE	//1r5b //CHECKTHIS
			#define NLC_PREPROCESSOR_MATH_FIX_BUG_DO_NOT_ADD_TYPES_TO_MATH_TEXT_VARIABLES	//1r5l
			#define NLC_PREPROCESSOR_MATH_FIX_BUG_DO_NOT_ADD_LOGICAL_CONDITION_OPERATORS_TO_MATH_TEXT_VARIABLES	//1r5m	//optional
			//#define NLC_PREPROCESSOR_MATH_FIX_BUG_ADD_MATH_TEXT_VARIABLES_DUPLICATES	//1r5b	//not required and untested
			#define NLC_USE_MATH_OBJECTS_ADVANCED_INFER_TYPE_BASED_ON_PREVIOUSLY_DECLARED_MATHTEXT_VARIABLES_ADVANCED	//1r5l
			#ifdef NLC_USE_MATH_OBJECTS_ADVANCED_INFER_TYPE_BASED_ON_PREVIOUSLY_DECLARED_MATHTEXT_VARIABLES_ADVANCED
				#define NLC_PREPROCESSOR_MATH_MATHTEXT_VARIABLE_VALID_CHARACTERS (63)
				static char preprocessorMathtextVariableValidCharacters[NLC_PREPROCESSOR_MATH_MATHTEXT_VARIABLE_VALID_CHARACTERS] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '_'};
			#endif
		#endif
		//#define NLC_USE_MATH_OBJECTS_ADVANCED_USE_UNIQUE_OPERATORS	//1r5i	//optional
		#ifdef NLC_USE_MATH_OBJECTS_ADVANCED_USE_UNIQUE_OPERATORS
			//NB strings: must use unique string concatenation & and equality test ~~ symbols instead of + and ==
			//NB booleans: boolean "== true" / "== false" test statements are not supported; must say if(theDog) or if(!theDog). "the x" == "the y" statments are not supported either (eg "if the dog == the cat")
			#define NLC_USE_MATH_OBJECTS_ADVANCED_USE_UNIQUE_OPERATORS_SYMBOL_STRING_COMPARISON "~~"
			#define NLC_USE_MATH_OBJECTS_ADVANCED_USE_UNIQUE_OPERATORS_SYMBOL_STRING_ADDITION "&"
			#define NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_NUMERICAL_OPERATORS_NUMBER_OF_TYPES (21)
			static string mathObjectsVariableTypeNumericalOperators[NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_NUMERICAL_OPERATORS_NUMBER_OF_TYPES] = {">", "<", ">=", "<=", "-", "/", "*", "%", " 0", " 1", " 2", " 3", " 4", " 5", " 6", " 7", " 8", " 9", "the number of", "+", "=="};
			#define NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_STRING_OPERATORS_NUMBER_OF_TYPES (3)
			static string mathObjectsVariableTypeStringOperators[NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_STRING_OPERATORS_NUMBER_OF_TYPES] = {NLC_USE_MATH_OBJECTS_ADVANCED_USE_UNIQUE_OPERATORS_SYMBOL_STRING_ADDITION, NLC_USE_MATH_OBJECTS_ADVANCED_USE_UNIQUE_OPERATORS_SYMBOL_STRING_COMPARISON, NLC_USE_MATH_OBJECTS_STRING_DELIMITER};
			#define NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_BOOLEAN_OPERATORS_NUMBER_OF_TYPES (2)
			static string mathObjectsVariableTypeBooleanOperators[NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_BOOLEAN_OPERATORS_NUMBER_OF_TYPES] = {"true", "false"};	//NB presently there is only mathText boolean variables, not mathObject boolean variables. CHECKTHIS; what if a variable name contains the text "true" or "false"?
			#ifdef NLC_USE_MATH_OBJECTS_BOOLEAN
				#define NLC_USE_MATH_OBJECTS_ADVANCED_USE_UNIQUE_OPERATORS_ASSUME_LOGICAL_CONDITION_STATEMENTS_ARE_BOOLEAN_IF_UNKNOWN	//eg "if the dog"
			#endif
		#else
			//NB strings: can use default string concatenation + and equality test == symbols 
			//NB booleans: boolean "== true" / "== false" test statements are supported; can say if(theDog == true) or if(theDog == false) 
			#define NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_NUMERICAL_OPERATORS_NUMBER_OF_TYPES (19)
			static string mathObjectsVariableTypeNumericalOperators[NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_NUMERICAL_OPERATORS_NUMBER_OF_TYPES] = {">", "<", ">=", "<=", "-", "/", "*", "%", " 0", " 1", " 2", " 3", " 4", " 5", " 6", " 7", " 8", " 9", "the number of"};
			#define NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_STRING_OPERATORS_NUMBER_OF_TYPES (1)
			static string mathObjectsVariableTypeStringOperators[NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_STRING_OPERATORS_NUMBER_OF_TYPES] = {NLC_USE_MATH_OBJECTS_STRING_DELIMITER};
			#define NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_BOOLEAN_OPERATORS_NUMBER_OF_TYPES (2)
			static string mathObjectsVariableTypeBooleanOperators[NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_BOOLEAN_OPERATORS_NUMBER_OF_TYPES] = {"true", "false"};	//NB presently there is only mathText boolean variables, not mathObject boolean variables. CHECKTHIS; what if a variable name contains the text "true" or "false"?		
			#define NLC_USE_MATH_OBJECTS_ADVANCED_ADDITIONS	
			#ifdef NLC_USE_MATH_OBJECTS_ADVANCED_ADDITIONS
				//#define NLC_USE_MATH_OBJECTS_ADVANCED_ADDITIONS_SYMBOL_ADDITION "+"	//implied
				#define NLC_USE_MATH_OBJECTS_ADVANCED_ADD_MATHOBJECT_VALUE_FUNCTION_NAME "addMathObjectValue"
			#endif
			#define NLC_USE_MATH_OBJECTS_ADVANCED_COMPARISONS	//1r5h - (NB provides support for both mathobject string comparisons and mathobject numerical comparisons: not previously available)
			#ifdef NLC_USE_MATH_OBJECTS_ADVANCED_COMPARISONS
				//#define NLC_USE_MATH_OBJECTS_ADVANCED_ADDITIONS_SYMBOL_COMPARISON "=="	//implied
				#define NLC_USE_MATH_OBJECTS_ADVANCED_TEST_MATHOBJECT_VALUE_FUNCTION_NAME "testMathObjectValue"
			#endif
		#endif
	#endif
	#define NLC_PREPROCESSOR_SUPPORT_WHITE_SPACE_BETWEEN_LOGICAL_CONDITION_AND_OPENING_BRACKET    //1r5j  //intermediary white text, eg "if (...)"; NB generated text will be less readable eg if((...))  //should temporarily disable when performing transitional autotesting
	#define NLC_PREPROCESSOR_SUPPORT_IDENTICAL_PARSABLE_PHRASES_IN_SENTENCE       //1r5i  //should temporarily disable when performing transitional autotesting
	#ifndef NLC_PREPROCESSOR_SUPPORT_IDENTICAL_PARSABLE_PHRASES_IN_SENTENCE
		//#define NLC_PREPROCESSOR_RECORD_PARSABLE_PHRASE_POSITION_APPROXIMATE	//1r5i (never enabled or tested): alternate implementation of NLC_PREPROCESSOR_SUPPORT_IDENTICAL_PARSABLE_PHRASES_IN_SENTENCE
	#endif
	#ifdef NLC_USE_LIBRARY_GENERATE_INDIVIDUAL_FILES
		//#define NLC_API	//1r6b (coded ~1r5d)		//requires NLC_USE_LIBRARY_GENERATE_INDIVIDUAL_FILES
	#endif
	#ifdef NLC_API
		#define NLC_API_DEBUG
		#define NLC_API_DEFAULT_SOURCE_FOLDER_NAME "/home/systemusername/source/NLCthirdpartyAPI/"
		#define NLC_API_DEFAULT_CLASS_LIST_FILE_NAME "APIclassList.txt"
		#define DOXYGEN_XML_OUTPUT_FOLDER "xml/"	//relative path
		#define DOXYGEN_XML_CLASS_FILE_NAME_PREPEND "class"
		#define DOXYGEN_XML_CLASS_FILE_NAME_EXTENSION ".xml"
		#define NLC_API_THIRD_PARTY_API_OBJECT_VARIABLE_NAME "thirdpartyAPIobject"
		#define NLC_API_THIRD_PARTY_API_OBJECT_WRAP_FUNCTION_NAME "wrapThirdPartyAPIobject"
		#define NLC_API_THIRD_PARTY_API_OBJECT_UNWRAP_FUNCTION_NAME "unwrapThirdPartyAPIobject"
		#define NLC_API_THIRD_PARTY_API_FUNCTION_WRAP_FUNCTION_NAME "wrapThirdPartyAPIfunction"
		//#define NLC_API_SEPARATE_FILE_FOR_WRAPPER_FUNCTIONS		//note !NLC_API_SEPARATE_FILE_FOR_WRAPPER_FUNCTIONS is untested
		#ifdef NLC_API_SEPARATE_FILE_FOR_WRAPPER_FUNCTIONS
			#define NLC_API_SEPARATE_FILE_FOR_WRAPPER_FUNCTIONS_NAME_PREPEND "NLCgeneratedInterface"
		#endif
		#define NLC_API_VARIABLE_TYPE_LIST_NUMBER_OF_TYPES (1)	//this needs to be extended (and made programming language independent)
		static string APIvariableTypeListPrepend[NLC_API_VARIABLE_TYPE_LIST_NUMBER_OF_TYPES] = {"vector<"};
		static string APIvariableTypeListAppend[NLC_API_VARIABLE_TYPE_LIST_NUMBER_OF_TYPES] = {"*>"};
	#endif
	#ifdef GIA_REFERENCING_WILD_CARDS
		#define NLC_REFERENCING_WILD_CARDS	//ignore something/anything entities while parsing context
	#endif
#endif

#ifndef NLC_DISABLE_1q_CODE_FOR_DEBUG
	#ifdef GIA_DISABLE_CROSS_SENTENCE_REFERENCING	//ie !NLC_LOCAL_LISTS_USE_INSTANCE_NAMES (NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT): has not yet been defined
		#define NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT_UPDATE_GENERATE_OBJECT_BY_NAME	//1q14k - required for use with NLClibrary as it assumes any object created has lastSentenceReferenced filled 
		#ifdef NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT_UPDATE_GENERATE_OBJECT_BY_NAME
			#define NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT_DEFAULT_SENTENCE_INDEX "0"
		#endif
	#endif
	#define NLC_VERIFY_LEGAL_TARGET_SOURCE_CHARACTERS	//1q14e
	#ifdef NLC_VERIFY_LEGAL_TARGET_SOURCE_CHARACTERS
		#define NLC_VERIFY_LEGAL_TARGET_SOURCE_CHARACTERS_NUMBER_OF_TYPES (63)
		static char legalTargetSourceCharacters[NLC_VERIFY_LEGAL_TARGET_SOURCE_CHARACTERS_NUMBER_OF_TYPES] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '_'};
	#endif
	//#define NLC_CONDITION_LISTS_VECTOR	//tested 1q12a (but disabled since)	//use vector<pair<E1*,E2*>> instead of unordered_map<E1*,E2*> for conditionLists: not currently supported by NLC standard library
	#ifdef GIA_DISABLE_CROSS_SENTENCE_REFERENCING	//ie !NLC_LOCAL_LISTS_USE_INSTANCE_NAMES: has not yet been defined
		//#ifdef NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT	//has not yet been defined
			#define NLC_TRANSLATOR_LOGICAL_CONDITIONS_FOR_LOOP_ADD_ENTITY_TO_NEW_CONTEXT_LIST	//1q11c
		//#endif
	#endif
	#define NLC_DO_NOT_PREDECLARE_LOCAL_LISTS_FOR_QUALITIES
	#ifdef NLC_DO_NOT_PREDECLARE_LOCAL_LISTS_FOR_QUALITIES
		//#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_BLOCKS_FOR_PARENT_INITIALISATION_SPECIAL	//has not yet been defined
			#ifdef GIA_DISABLE_CROSS_SENTENCE_REFERENCING	//ie !NLC_LOCAL_LISTS_USE_INSTANCE_NAMES: has not yet been defined. NB must only check NLC_LOCAL_LISTS_USE_INSTANCE_NAMES/GIA_DISABLE_CROSS_SENTENCE_REFERENCING here because NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_BLOCKS_FOR_PARENT_INITIALISATION_SPECIAL has not yet been defined
				#define NLC_DO_NOT_CREATE_LOCAL_LISTS_FOR_QUALITIES	//1q10d
			#endif
		//#endif
	#endif
	#ifndef GIA_DISABLE_CROSS_SENTENCE_REFERENCING	//ie NLC_LOCAL_LISTS_USE_INSTANCE_NAMES: has not yet been defined
		#define NLC_PREVENT_REDECLARATIONS_OF_CATEGORY_LISTS
	#else	
		//#ifdef NLC_USE_ADVANCED_REFERENCING_SUPPORT_ALIASES		//has not yet been defined; category list redeclarations are only a problem for NLC_USE_ADVANCED_REFERENCING when using NLC aliases		
			#define NLC_PREVENT_REDECLARATIONS_OF_CATEGORY_LISTS	//1q10b+
		//#endif
	#endif
	#ifdef NLC_PREVENT_REDECLARATIONS_OF_CATEGORY_LISTS	
		#define NLC_GENERATE_UNIQUE_CONTEXT_BLOCK_FOR_EACH_SENTENCE	//1q10b
		#ifdef NLC_GENERATE_UNIQUE_CONTEXT_BLOCK_FOR_EACH_SENTENCE
			#define NLC_GENERATE_UNIQUE_CONTEXT_BLOCK_FOR_EACH_SENTENCE_LOGICAL_CONDITIONS_PARSABLE_PHRASES
			#ifndef GIA_DISABLE_CROSS_SENTENCE_REFERENCING	//ie NLC_LOCAL_LISTS_USE_INSTANCE_NAMES: has not yet been defined
				#define NLC_GENERATE_UNIQUE_CONTEXT_BLOCK_FOR_EACH_SENTENCE_LOGICAL_CONDITIONS_FOR_LOOPS	//1q11b	//required with !NLC_USE_ADVANCED_REFERENCING to support consecutive for loops (iterating across same primary entity). Not required with NLC_USE_ADVANCED_REFERENCING (due to category lists being uniquely named between sentences), and currently unsupported by NLC_USE_ADVANCED_REFERENCING (due to referenceContextList maintenance)
			#endif
			//#define NLC_GENERATE_UNIQUE_CONTEXT_BLOCK_FOR_EACH_SENTENCE_LOGICAL_CONDITIONS_FULL_SENTENCES	//not yet implemented (requires integration with logical condition context level record system)
		#else
			#define NLC_GENERIC_LISTS_CATEGORIES_AND_SUBJECT_OBJECT_NAME_BY_INSTANCE_ID_AND_SENTENCE_INDEX	//tested 1q11a (but disabled since) - this can be used to prevent redeclarations of xCategoryList/xSubjectCategoryList/xObjectCategoryList	
			#ifdef NLC_GENERIC_LISTS_CATEGORIES_AND_SUBJECT_OBJECT_NAME_BY_INSTANCE_ID_AND_SENTENCE_INDEX
				#define NLC_GENERIC_LISTS_CATEGORIES_AND_SUBJECT_OBJECT_NAME_BY_INSTANCE_ID_AND_SENTENCE_INDEX_INSTANCE_NAME "I"
				#define NLC_GENERIC_LISTS_CATEGORIES_AND_SUBJECT_OBJECT_NAME_BY_INSTANCE_ID_AND_SENTENCE_INDEX_SENTENCE_NAME "S"
			#endif
		#endif
	#endif
	//#define NLC_SUPPORT_GIA_NLP_OR_XML_INPUT	//disabled 1q2b
	#define NLC_SUPPORT_INPUT_FUNCTION_LISTS_EXPLICIT_FROM_DEDICATED_FILE_SUPPORT_PREPROCESSOR	//1q2b
	#ifdef NLC_SUPPORT_INPUT_FUNCTION_LISTS_EXPLICIT_FROM_DEDICATED_FILE_SUPPORT_PREPROCESSOR
		#define NLC_SUPPORT_INPUT_FUNCTION_LISTS_EXPLICIT_FROM_DEDICATED_FILE_SUPPORT_PREPROCESSOR_COMBINED_FILE_NAME_APPEND_TEXT "afterInputListCombination.txt"
		#define NLC_SUPPORT_INPUT_FUNCTION_LISTS_EXPLICIT_FROM_DEDICATED_FILE_ENFORCE_NLC_FILE_EXTENSIONS
	#endif
	//#ifdef NLC_USE_LIBRARY	//has not been defined yet
		#define NLC_USE_PREDEFINED_FUNCTION_NAME_FOR_NATURAL_LANGUAGE_CODE_WITHOUT_FUNCTION_SPECIFIED	//1q2a	//new implementation: requires all functions specified in explicit input list (NLC_SUPPORT_INPUT_FUNCTION_LISTS_EXPLICIT_FROM_DEDICATED_FILE) to have .nlc extension
		#ifdef NLC_USE_PREDEFINED_FUNCTION_NAME_FOR_NATURAL_LANGUAGE_CODE_WITHOUT_FUNCTION_SPECIFIED
			#define NLC_USE_PREDEFINED_FUNCTION_NAME_FOR_NATURAL_LANGUAGE_CODE_WITHOUT_FUNCTION_SPECIFIED_NAME "NLCimplicitlyDeclaredFunctionArtificial"
			//#define NLC_USE_PREDEFINED_FUNCTION_NAME_FOR_NATURAL_LANGUAGE_CODE_WITHOUT_FUNCTION_SPECIFIED_DO_NOT_PRINT_ACTION_ARGUMENT	//enabled 1q2a, disabled 1q3b
			#define NLC_USE_PREDEFINED_FUNCTION_NAME_FOR_NATURAL_LANGUAGE_CODE_WITHOUT_FUNCTION_SPECIFIED_EXECUTE_IN_MAIN	//1q4a
		#endif
		#ifdef NLC_USE_LIBRARY_GENERATE_INDIVIDUAL_FILES
			#define NLC_USE_LIBRARY_GENERATE_INDIVIDUAL_FILES_NAME_PREPEND "NLCgenerated"	//1q1a
			#define NLC_USE_LIBRARY_GENERATE_INDIVIDUAL_FILES_NAME_PREPEND_BASE ""		//1q6d
			#define NLC_USE_LIBRARY_GENERATE_INDIVIDUAL_FILES_PREPROCSSOR_NAME_PREPEND "HEADER_NLC_GENERATED"	//1q1c
			#define NLC_USE_LIBRARY_GENERATE_INDIVIDUAL_FILES_PREPROCSSOR_NAME_DELIMITER '_'	//1q1c
			#define NLC_USE_LIBRARY_GENERATE_INDIVIDUAL_FILES_ADD_CLASS_FUNCTIONS_TO_CLASS_DEFINITIONS	//1q1d	//requires NLC_SUPPORT_INPUT_FUNCTION_LISTS	//requires NLC_CLASS_DEFINITIONS_SUPPORT_FUNCTIONS_WITHOUT_SUBJECT
			#define NLC_USE_LIBRARY_GENERATE_INDIVIDUAL_FILES_EXTENSION_CPP ".cpp"
			#define NLC_USE_LIBRARY_GENERATE_INDIVIDUAL_FILES_EXTENSION_HPP ".hpp"
			#define NLC_USE_LIBRARY_GENERATE_INDIVIDUAL_FILES_GENERIC_ENTITY_CLASS_NAME "NLClibraryGenericEntityClass"
			#define NLC_USE_LIBRARY_GENERATE_INDIVIDUAL_FILES_LIBRARY_HEADER_NAME "NLClibrary"	//must be sychronised with progLangDependenciesNLClibary[]
			#define NLC_USE_LIBRARY_GENERATE_INDIVIDUAL_FILES_LIST_NAME "NLCgeneratedList.txt"
			#define NLC_USE_LIBRARY_LIBRARY_FOLDER ""	//1q6d, changed 1q14h		//"../NLClibrary/"
			#define NLC_USE_LIBRARY_GENERATED_FOLDER ""	//1q6d, changed 1q14h		//"../NLCgenerated/"
			#define NLC_USE_LIBRARY_SOURCE_FOLDER ""	//1q6d, changed 1q14h		//"../source/"
		#endif
		//#ifdef NLC_USE_LIBRARY_FUNCTION_LISTS_FOR_ARGUMENT_RECONCILIATION	//has not been defined yet
			#define NLC_USE_LIBRARY_ASSUME_STANDARD_AND_USER_LIBRARY_FUNCTIONS_ACTION_ARGUMENT_TYPE_IS_NLC_GENERIC_ENTITY_CLASS	//1q1a	//if this is not defined, then wrapper functions must be created for every NLClibrary function (x) whose function action argument is of type NLCgenericEntityClass (instead of xClass)
		//#endif
	//#endif
#endif
#ifndef NLC_DISABLE_1p_CODE_FOR_DEBUG
	//#ifdef NLC_PREPROCESSOR_MATH_DETECT_AND_DECLARE_IMPLICITLY_DECLARED_VARIABLES		//has not been defined yet
		#define NLC_PREPROCESSOR_MATH_DETECT_USE_OF_UNDECLARED_VARIABLES	//effectively disabled 1h4b, reactivated 1p12c
		#ifdef NLC_PREPROCESSOR_MATH_DETECT_USE_OF_UNDECLARED_VARIABLES
			#define NLC_PREPROCESSOR_MATH_DETECT_MATHTEXT_VARIABLES_AT_END_OF_LINE //1p12d
		#endif
		#define NLC_PREPROCESSOR_MATH_DETECT_MATHTEXT_FUNCTIONS_SUPPORTED_BY_TARGET_LANGUAGE	//1p12e
		#ifdef NLC_PREPROCESSOR_MATH_DETECT_MATHTEXT_FUNCTIONS_SUPPORTED_BY_TARGET_LANGUAGE
			#define NLC_PREPROCESSOR_MATH_DETECT_MATHTEXT_FUNCTIONS_SUPPORTED_BY_TARGET_LANGUAGE_NUMBER_OF_TYPES (6)
			static string preprocessorMathTextFunctionsSupportedByTargetLanguage[NLC_PREPROCESSOR_MATH_DETECT_MATHTEXT_FUNCTIONS_SUPPORTED_BY_TARGET_LANGUAGE_NUMBER_OF_TYPES] = {"sin", "cos", "tan", "exp", "log", "print"};	//these need to be made dependent on target progLang (and declared in PrintDefs)
		#endif
	//#endif
	//#ifdef NLC_USE_LIBRARY	//has not been defined yet
		#define NLC_USE_LIBRARY_BASE_EXTENDED	//1p2a	//simplifies generated code	//requires NLC_USE_LIBRARY	//NB NLC_USE_LIBRARY_BASE_EXTENDED does not support NLC_CONDITION_LISTS_STORE_CONDITION_AS_STRING
		#ifdef NLC_USE_LIBRARY_BASE_EXTENDED
			#define NLC_USE_LIBRARY_BASE_EXTENDED_FUNCTION_NAME_ADD_PROPERTY "addProperty"
			#define NLC_USE_LIBRARY_BASE_EXTENDED_FUNCTION_NAME_ADD_CONDITION "addCondition"
			#ifndef NLC_DISABLE_1q_CODE_FOR_DEBUG
				//#ifdef NLC_NORMALISE_TWOWAY_PREPOSITIONS_MARK_INVERSE_CONDITIONS	//has not yet been defined
					#define NLC_USE_LIBRARY_BASE_EXTENDED_FUNCTION_NAME_ADD_CONDITION_INVERSE "addConditionInverse"		
				//#endif
			#endif
			#define NLC_USE_LIBRARY_BASE_EXTENDED_FUNCTION_NAME_REMOVE_PROPERTY "removeProperty"
			#define NLC_USE_LIBRARY_BASE_EXTENDED_FUNCTION_NAME_REMOVE_CONDITION "removeCondition"
			#define NLC_USE_LIBRARY_BASE_EXTENDED_FUNCTION_NAME_REMOVE_PROPERTIES "removeProperties"
			#define NLC_USE_LIBRARY_BASE_EXTENDED_FUNCTION_NAME_REMOVE_CONDITIONS "removeConditions"
			#define NLC_USE_LIBRARY_BASE_EXTENDED_FUNCTION_NAME_ADD_ACTIONSUBJECT "addActionSubject"
			#define NLC_USE_LIBRARY_BASE_EXTENDED_FUNCTION_NAME_ADD_ACTIONOBJECT "addActionObject"
			#define NLC_USE_LIBRARY_BASE_EXTENDED_FUNCTION_NAME_ADD_NEW_ENTITY_TO_LOCAL_LIST "addNewEntityToLocalList"
			#define NLC_USE_LIBRARY_BASE_EXTENDED_FUNCTION_NAME_ADD_ENTITY_TO_LOCAL_LIST "addEntityToLocalList"
			#define NLC_USE_ENUM_LISTS
			#ifdef NLC_USE_ENUM_LISTS
				#define NLC_ENUM_LIST_TYPE_DEFAULT_NON_ENUM "nonEnum"	//restored 1p13a	//CHECKTHIS
				#define NLC_USE_ENUM_LISTS_PROPERTIES
				#define NLC_USE_ENUM_LISTS_CONDITIONS
				//#define NLC_USE_ENUM_LISTS_ACTIONS	//not yet coded
			#endif
			#ifdef NLC_USE_LIBRARY_STANDARD
				//#define NLC_USE_LIBRARY_STANDARD_GENERIC_FUNCTIONS	//for test only (should produce same result)	//note generic functions represent the foundation for the NLC commercial library (enable library functions to be defined irrespective of entity name)
			#endif
		#else
			#define NLC_USE_NON_LIBRARY_FUNCTIONS_EXTENDED	//generates inline addProperty/addCondition functions only
		#endif
		//#define NLC_USE_LIBRARY_COPY_FUNCTION_COPY_INTERNAL_CONDITION_LISTS	//1p11a
		#define NLC_USE_LIBRARY_COPY_OBJECT_BY_NAME_FUNCTION_NAME "copyObjectByName"	//1p2a
		//#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS	//has not been defined yet
			#define NLC_USE_LIBRARY_FUNCTION_LISTS_FOR_ARGUMENT_RECONCILIATION	//1p3c
			#ifdef NLC_USE_LIBRARY_FUNCTION_LISTS_FOR_ARGUMENT_RECONCILIATION
				#define NLC_USE_LIBRARY_STANDARD_FUNCTION_LIST_FILE_NAME "NLClibraryStandardFunctionList.txt"	//1p3c
				#define NLC_USE_LIBRARY_USER_FUNCTION_LIST_FILE_NAME "NLClibraryUserFunctionList.txt"	//1p3c
			#endif
		//#endif
		#define NLC_USE_LIBRARY_DISABLE_FUNCTIONS_LIST_WARNING	//1p4e (temporary addition for testing)
	//#endif
	#define NLC_USE_MATH_OBJECTS	//1p2a (first declared 1n3b) - each entity has a (double) value which can be set by NLC mathText
	#ifdef NLC_USE_MATH_OBJECTS
		#define NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_NUMERICAL_NAME "numericalValue"
		#ifdef NLC_USE_MATH_OBJECTS_ADVANCED
			#ifdef NLC_USE_MATH_OBJECTS_STRING
				#define NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_STRING_NAME "stringValue"
			#endif
			#ifdef NLC_USE_MATH_OBJECTS_BOOLEAN
				#define NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_BOOLEAN_NAME "booleanValue"
			#endif
		#endif
		#define NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_NUMERICAL (0)
		#define NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_STRING (1)
		#define NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_BOOLEAN (2)
		#define NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_UNKNOWN (3)	//informal (NLC internal use only)
		#define NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_BOOLEAN_STATEMENT (4)	//informal (NLC internal use only) - eg "if the dog is happy"
		#ifdef NLC_USE_MATH_OBJECTS_ADVANCED
			#define NLC_USE_MATH_OBJECTS_VARIABLE_NUMBER_OF_TYPES (3)
			static string preprocessorMathObjectVariables[NLC_USE_MATH_OBJECTS_VARIABLE_NUMBER_OF_TYPES] = {NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_NUMERICAL_NAME, NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_STRING_NAME, NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_BOOLEAN_NAME};
		#else
			#define NLC_USE_MATH_OBJECTS_VARIABLE_NUMBER_OF_TYPES (1)
			static string preprocessorMathObjectVariables[NLC_USE_MATH_OBJECTS_VARIABLE_NUMBER_OF_TYPES] = {NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_NUMERICAL_NAME};	
		#endif
		#define NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_SUPPORT_ALPHANUMERIC_VARIABLE_NAMES_SUPPORT_FRACTIONAL_VALUES	//e.g. 5.5
		#define NLC_MATH_OBJECTS_TEST_NULL_POINTER_MAINTAIN_CONTEXT	//this prevents execution of mathText out of context
	#endif	

	#ifdef GIA_RECORD_POSSESSION_AUXILIARY_HAS_INFORMATION
		#define NLC_APPLY_GET_SAME_REFERENCE_SET_NON_QUALITY_CHILD_FIX_TO_VERIFY_NOT_POSSESSION_AUXILIARY_HAVE	//added 1p10a
	#elif defined GIA_RECORD_RCMOD_SET_INFORMATION
		//#define NLC_APPLY_GET_SAME_REFERENCE_SET_NON_QUALITY_CHILD_FIX_TO_VERIFY_RCMOD_DOES_NOT_INDICATE_SAME_REFERENCE_SET	//added 1p2b, removed 1p10a, no longer supported 1r4a
	#endif
	
	//#ifdef NLC_PREPROCESSOR_MATH	//has not been defined yet
		#define NLC_PARSE_CONDITION_PARENTS	//enforced 1p2b - this is now required by default (irrespective of NLC_NORMALISE_INVERSE_PREPOSITIONS) for at least generateCodeBlocksFromMathTextNLPparsablePhrase() part 2A and part 2B, such that the primary entity in the nlp parsable phrase can be identified
	//#endif
	#define NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE_DO_NOT_ADD_FUNCTION_DEPENDENCY_FOR_FUNCTION_REFERENCES	//added 1p4b
#endif
	
#ifndef NLC_DISABLE_1o_CODE_FOR_DEBUG
	#ifndef GIA_LRP_REDUCE_QUOTES_TO_SINGLE_WORDS
		#ifndef NLC_USE_MATH_OBJECTS_STRING
			#define NLC_PREPROCESSOR_REDUCE_QUOTES_TO_SINGLE_WORDS	//disabled 1r5b
		#endif
	#endif
#endif
	
#ifndef NLC_DISABLE_1n_CODE_FOR_DEBUG
	#define NLC_TRANSLATOR_LOGICAL_CONDITIONS_FOR_LOOP_IGNORE_SAME_REFERENCE_SET_COMPENSATE_FOR_NLP_FAILURE_TO_CREATE_RCMOD	//1n15g
	#define NLC_TRANSLATOR_GENERATE_CONTEXT_BLOCKS_PARSE_PARENT_EFFICIENT	//1n15a
	#define NLC_TRANSLATOR_GENERATE_CONTEXT_BLOCKS_PARSE_PARENT_OF_TARGET_AND_MULTIPLE_DEFINITE_ENTITIES	//1n15a
	#ifdef NLC_TRANSLATOR_GENERATE_CONTEXT_BLOCKS_PARSE_PARENT_OF_TARGET_AND_MULTIPLE_DEFINITE_ENTITIES
		#define NLC_TRANSLATOR_GENERATE_CONTEXT_BLOCKS_PARSE_PARENT_OF_TARGET_AND_MULTIPLE_DEFINITE_ENTITIES_CANDIDATE_OBJECT_NAME_PREPEND "Candidate"
	#endif
	#define NLC_TRANSLATOR_GENERATE_CONTEXT_BLOCKS_PARSE_DEFINITIONS	//1n7a
	#define NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN_DO_NOT_PARSE_DUPLICATE_CLASSES	//1n5e
	#define NLC_SUPPORT_REDEFINITIONS		//1n5d
	#ifdef NLC_SUPPORT_REDEFINITIONS
		#define NLC_SUPPORT_REDEFINITIONS_FOR_IMMEDIATELY_DECLARED_INDEFINITE_ENTITIES	//1n19b	//eg chickens are animals. an animal is a chicken. In practice this will not be implemented because GIA interprets indefinite-indefinite definitions as concepts
		#define NLC_CLASS_DEFINITIONS_DO_NOT_DEFINE_INHERITANCE_FOR_REDEFINITIONS	//1n10b/1n19c	//prevents circular definition; eg Chickens are animals. An animal is happy. The animal is a blue chicken.
		#define NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_BASED_ON_NETWORK_INDEXES_BASIC_DYNAMIC	//1n5b
		#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_BASED_ON_NETWORK_INDEXES_BASIC_DYNAMIC
			#define NLC_CLASS_PARENT_CLASS_LIST_NAME "parentClassList"
			#define NLC_CLASS_PARENT_CHECK_PARENT_CLASS_NAME_FUNCTION_NAME "checkParentClassName"
		#endif
	#endif
	#define NLC_USE_SUPPORT_REFERENCING_OBJECTS_IN_PLURAL_LIST_BY_NUMBER	//1n3b
	#ifdef NLC_USE_SUPPORT_REFERENCING_OBJECTS_IN_PLURAL_LIST_BY_NUMBER
		#define NLC_USE_SUPPORT_REFERENCING_OBJECTS_IN_PLURAL_LIST_BY_NUMBER_FOR_PROPERTIES	//not supported by Stanford NLP at present (_num relation is not generated)
	#endif
	#define NLC_USE_LIBRARY	//1n2a	//currently requires NLC_PROGRAMMING_LANGUAGE_CPP
	#ifdef NLC_USE_LIBRARY
		//must be synced with NLClibraryStandard.h:
		//#define NLC_USE_LIBRARY_FROM_CONDITIONS	//unfinished; FUTURE NLC - ensure from condition lists are added to class definitions and are filled correctly
		#ifdef NLC_USE_LIBRARY_FROM_CONDITIONS
			#define NLC_USE_LIBRARY_MOVE_FUNCTION_ACTION_CONDITION_FROM_NAME "from"
		#endif
		#define NLC_USE_LIBRARY_GENERATE_OBJECT_BY_NAME_FUNCTION_NAME "generateObjectByName"
	#endif
	#ifdef GIA_LRP_NLP_PARSABLE_PHRASE_SUPPORT_FILENAMES_WITH_FULLSTOPS_AND_FLOATS_AND_TIMES
		#define NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_SUPPORT_FILENAMES_WITH_FULLSTOPS	//1n2e
	#endif
	//#define NLC_NONOO	//1n1a
	#ifdef NLC_NONOO
		#define NLC_NONOO_CREATE_REVERSE_LISTS
		//#define NLC_NONOO_DISABLE_CLASS_HEIRACHY
	#endif
#endif

#ifndef NLC_DISABLE_1m_CODE_FOR_DEBUG
	#ifdef GIA_LRP_NORMALISE_INVERSE_PREPOSITIONS
		#define NLC_NORMALISE_INVERSE_PREPOSITIONS
		#ifdef NLC_NORMALISE_INVERSE_PREPOSITIONS
			#define NLC_PARSE_CONDITION_PARENTS
		#endif
	#endif
	#ifdef GIA_LRP_NORMALISE_TWOWAY_PREPOSITIONS
		#define NLC_NORMALISE_TWOWAY_PREPOSITIONS
		#ifdef GIA_LRP_NORMALISE_TWOWAY_PREPOSITIONS_DUAL_CONDITION_LINKS_ENABLED
			#define NLC_NORMALISE_TWOWAY_PREPOSITIONS_DUAL_CONDITION_LINKS_ENABLED	//GIA dual conditions are enabled (NLC will not parse GIA entities with inverseConditionTwoWay set; prevents infinite loop parsing - relies on GIA advanced referencing to parse inverted sentence contents. E.g. sentenceIndex1: a new two way condition is created (the inverted condition of which has a inverseConditionTwoWay set) (eg Tom is near the house). This inverted condition is referenced using GIA advanced referencing by a new sentenceIndex2 with inverted sentence contents (eg The house that is near Tom). Yet the condition connection created for the referenced condition (sentenceIndex2) will not be inverted, therefore it will be correctly parsed by NLC)
		#else
			#define NLC_NORMALISE_TWOWAY_PREPOSITIONS_DUAL_CONDITION_LINKS_DISABLED	//GIA dual conditions are disabled (NLC will create dual condition links; required for parsing of inverted sentence contents; eg Tom is near the house. The house that is near Tom is red.)
			#ifndef NLC_DISABLE_1q_CODE_FOR_DEBUG
				#define NLC_NORMALISE_TWOWAY_PREPOSITIONS_MARK_INVERSE_CONDITIONS	//added 1q14d (required for NLClibrary) - will set inverseConditionTwoWay for NLC condition entities	//does not support NLC_CONDITION_LISTS_STORE_CONDITION_AS_STRING
				#ifdef NLC_NORMALISE_TWOWAY_PREPOSITIONS_MARK_INVERSE_CONDITIONS
					#define NLC_NORMALISE_TWOWAY_PREPOSITIONS_MARK_INVERSE_CONDITIONS_NAME "inverseConditionTwoWay"
				#endif
			#endif
		#endif
	#endif
	#define NLC_NATURAL_LANGUAGE_CODE_FILE_NAME_EXTENSION ".nlc"
#else
	#define NLC_NATURAL_LANGUAGE_CODE_FILE_NAME_EXTENSION ""
#endif
#define NLC_PARSE_CONDITION_PARENTS_DEFAULT_VALUE (true)

#ifndef GIA_DISABLE_CROSS_SENTENCE_REFERENCING
	#define NLC_LOCAL_LISTS_USE_INSTANCE_NAMES	//added 1e, removed 1j2b+, optional 1k11a+
#endif
#ifdef NLC_DISABLE_1i_CODE_FOR_DEBUG
	#define NLC_USE_ORIGINAL_INSTANCE_LIST_NAMES	
#else
	#ifndef NLC_DISABLE_1k_CODE_FOR_DEBUG
		#define NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_SUPPORT_ALPHANUMERIC_ENTITY_NAMES_ONLY	//1k7c	//required for most output languages
	#endif
	#define NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN	//1i1a/19-August-2014/1i3 - categories
	#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN
		#ifdef GIA_TRANSLATOR_DREAM_MODE_LINK_SPECIFIC_CONCEPTS_AND_ACTIONS
			#define NLC_GENERATE_OBJECT_INITIALISATIONS_BASED_ON_CONCEPTS	//assume 1i4a
		#endif
		#ifdef NLC_GENERATE_OBJECT_INITIALISATIONS_BASED_ON_CONCEPTS
			#define NLC_GENERATE_OBJECT_INITIALISATIONS_BASED_ON_CONCEPTS_FOR_ALL_DEFINITE_ENTITIES	//1i4a
		#endif
		#ifndef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES
			#define NLC_USE_ADVANCED_REFERENCING	//added 1j3a+ (effectively replaces GIA_USE_ADVANCED_REFERENCING)
			#ifdef NLC_USE_ADVANCED_REFERENCING
				#define NLC_USE_ADVANCED_REFERENCING_LAST_SENTENCE_REFERENCED_VARIABLE_NAME "lastSentenceReferenced"
				#define NLC_USE_ADVANCED_REFERENCING_SINGULAR_DEFINITE_REFERENCING_TESTS_FUNCTION_NAME "addToCategoryIfPassSingularDefiniteReferencingTests"
				#define NLC_USE_ADVANCED_REFERENCING_COMMENT
				#ifndef NLC_DISABLE_1k_CODE_FOR_DEBUG
					#define NLC_USE_ADVANCED_REFERENCING_SUPPORT_ALIASES	//1k14a - requires GIA_DISABLE_ALIAS_ENTITY_MERGING
					#ifdef NLC_USE_ADVANCED_REFERENCING_SUPPORT_ALIASES
						#define NLC_USE_ADVANCED_REFERENCING_SUPPORT_ALIASES_ALIAS_NAME "aliasName"
						#define NLC_USE_ADVANCED_REFERENCING_FIND_ALIAS_AND_ADD_TO_CATEGORY_LIST_FUNCTION_NAME "findAliasAndAddToCategoryList"
						#define NLC_USE_ADVANCED_REFERENCING_FIND_ALIAS_FUNCTION_NAME "findAlias"
						//#define NLC_USE_ADVANCED_REFERENCING_SUPPORT_ALIASES_CROSS_FUNCTION_ALIASES	//not yet implemented
						#define NLC_USE_ADVANCED_REFERENCING_SUPPORT_ALIASES_PREVENT_ADDING_AS_FUNCTION_ARGUMENT	//1k14d
					#endif
				#endif
			#endif
			#define NLC_CATEGORIES_TEST_PLURALITY	//1j1a
			#ifdef NLC_CATEGORIES_TEST_PLURALITY
				#define NLC_CATEGORIES_TEST_PLURALITY_ENFORCE	//interpret user definite singular references as singular even if an appropriate plural match exists
				#define NLC_CATEGORIES_TEST_PLURALITY_COMMENT
				//#define NLC_CATEGORIES_TEST_PLURALITY_WARNING
				#ifdef NLC_CATEGORIES_TEST_PLURALITY_WARNING
					#ifndef NLC_DISABLE_1k_CODE_FOR_DEBUG
						#define NLC_CATEGORIES_TEST_PLURALITY_WARNING_PLACE_IN_NLC_PREDEFINED_FUNCTION_ADDTOCATEGORYIFPASSSINGULARDEFINITEREFERENCINGTESTS	//1k6b
					#endif
					#define NLC_CATEGORIES_TEST_PLURALITY_WARNING_MESSAGE "Execution warning: multiple objects have been added to a singular definite variable (category) - should the entity have been defined as plural instead?"
				#endif
				#define NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY	//1j21a - test numerosity of categories and children; only applicable for logical conditions?	//eg "If 3 baskets have a pie, eat the apple."
				#ifdef NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY
					#define NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY_CHILDREN	//eg "If the basket has 3 pies, eat the apple."
				#endif
			#endif
		#endif
		#define NLC_USE_ADVANCED_REFERENCING_PLURAL_DEFINITE_REFERENCING_TESTS_FUNCTION_NAME "addToCategoryIfPassPluralDefiniteReferencingTests"
		#define NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN_DO_NOT_ADD_DUPLICATES	//1j8a
		#ifndef NLC_DISABLE_1l_CODE_FOR_DEBUG
			#define NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE_PATCH //1l1a
			#define NLC_FUNCTIONS_SUPPORT_PLURAL_SUBJECTS_AND_OBJECTS	//1l1b		//requires NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN
			#ifdef NLC_FUNCTIONS_SUPPORT_PLURAL_SUBJECTS_AND_OBJECTS
				#define NLC_FUNCTIONS_SUPPORT_PLURAL_SUBJECTS	//1l1b
				#define NLC_FUNCTIONS_SUPPORT_PLURAL_OBJECTS	//1l1b
			#endif
		#endif
	#endif
	
	#define NLC_LOGICAL_CONDITION_OPERATIONS_SUPPORT_INDEFINITE_LOGICAL_CONDITION_OBJECTS	//1i7a
	#ifdef NLC_LOGICAL_CONDITION_OPERATIONS_SUPPORT_INDEFINITE_LOGICAL_CONDITION_OBJECTS
		#ifdef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES
			#define NLC_GENERATE_TYPE_LISTS
		#endif
		#ifdef NLC_GENERATE_TYPE_LISTS
			#define NLC_ITEM_TYPE_TYPE_VAR_APPENDITION2 "Type"
			#define NLC_ITEM_TYPE_INSTANCE_VAR_APPENDITION2 "Instance"
		#endif
	#endif

	#define NLC_STRICT_NO_IMPLICIT_DECLARATIONS	//1i8a+
	#ifdef NLC_STRICT_NO_IMPLICIT_DECLARATIONS
		#define NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_BASIC_GENERATE_CONTEXT_BLOCKS_IF_SAME_REFERENCE_SET	//1i3d
		#define NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED	//1i8a+
		#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED
			#ifndef NLC_DISABLE_1j_CODE_FOR_DEBUG
				#ifndef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES	//NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_BLOCKS_FOR_PARENT_INITIALISATION_SPECIAL is required for !NLC_LOCAL_LISTS_USE_INSTANCE_NAMES. It is not required for NLC_LOCAL_LISTS_USE_INSTANCE_NAMES, but should be tested with NLC_LOCAL_LISTS_USE_INSTANCE_NAMES also as it is a cleaner more general implementation
					#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN
						#define NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_BLOCKS_FOR_PARENT_INITIALISATION_SPECIAL	//added 1j6a	//requires NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN
					#endif
				#endif
			#endif
			#define NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_FOR_EACH_CHILD	//1i8b
			#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_FOR_EACH_CHILD
				#define NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_FOR_EACH_CHILD_GET_PARENT	//1i11a
				#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_FOR_EACH_CHILD_GET_PARENT
					//#ifdef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES
						#define NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_FOR_EACH_CHILD_GET_PARENT_ORIGINAL_IMPLEMENTATION
					//#endif
				#endif
			#endif
		#endif
	#endif
	
	#ifndef NLC_DISABLE_1l_CODE_FOR_DEBUG
		#ifdef NLC_FUNCTIONS_SUPPORT_PLURAL_SUBJECTS_AND_OBJECTS
			#define NLC_ACTION_CATEGORY_LISTS
			#define NLC_ACTION_CATEGORY_LISTS_USE_AS_FUNCTION_EXECUTION_ARGUMENTS
			#define NLC_ACTION_CATEGORY_LISTS_USE_FOR_PLURAL_ACTION_SUBJECTSOBJECTS_IN_MULTIACTION_INITIALISATION_SENTENCES
		#endif
	#endif
#endif

#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN
	#ifdef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES
		#ifndef NLC_DISABLE_1l_CODE_FOR_DEBUG
			#define NLC_PERFORM_PLURAL_DEFINITE_REFERENCING_TESTS
		#endif
	#else
		#ifdef NLC_USE_ADVANCED_REFERENCING
			#define NLC_PERFORM_PLURAL_DEFINITE_REFERENCING_TESTS
		#endif
	#endif
#endif

#define NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS
#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS
	
	#define NLC_LOGICAL_CONDITION_OPERATIONS_NUMBER_OF_TYPES (9)
	static string logicalConditionOperationsArray[NLC_LOGICAL_CONDITION_OPERATIONS_NUMBER_OF_TYPES] = {"for", "if", "as", "before", "after", "while", "when", "else", "else if"};	//should be dynamically defined in NLCrules.xml
	#define NLC_LOGICAL_CONDITION_OPERATIONS_IF_STRING "if"
	#define NLC_LOGICAL_CONDITION_OPERATIONS_ELSE_STRING "else"
	#define NLC_LOGICAL_CONDITION_OPERATIONS_ELSE_IF_STRING "else if"
	#define NLC_LOGICAL_CONDITION_OPERATIONS_WHILE_STRING "while"

	#define NLC_LOGICAL_CONDITION_OPERATIONS_FOR (0)	//default
	#define NLC_LOGICAL_CONDITION_OPERATIONS_IF (1)
	#define NLC_LOGICAL_CONDITION_OPERATIONS_ELSE_IF (8)
	#define NLC_LOGICAL_CONDITION_OPERATIONS_ELSE (7)	//not used
	#define NLC_LOGICAL_CONDITION_OPERATIONS_WHILE (5)
	
	#define NLC_WHILE_LOGICAL_CONDITION_CONJUNCTION_BOOLEAN_VARIABLE_NAME "whileLogicalConditionL"	//eg whileLogicalConditionL0
	
	#define NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_BASED_ON_ACTIONS
	#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_BASED_ON_ACTIONS
		#ifndef NLC_DISABLE_1l_CODE_FOR_DEBUG
			#define NLC_RECORD_ACTION_HISTORY
			#ifdef NLC_RECORD_ACTION_HISTORY
				#define NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_BASED_ON_ACTIONS_ADVANCED
				#define NLC_ITEM_TYPE_ACTION_VAR_APPENDITION "Action"
				#define NLC_ITEM_TYPE_ACTIONINCOMING_VAR_APPENDITION "ActionIncoming"
				#define NLC_ITEM_TYPE_ACTIONSUBJECT_VAR_APPENDITION "ActionSubject"
				#define NLC_ITEM_TYPE_ACTIONOBJECT_VAR_APPENDITION "ActionObject"
				#ifndef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES
					#ifndef NLC_TRANSLATOR_GENERATE_CONTEXT_BLOCKS_PARSE_PARENT_OF_TARGET_AND_MULTIPLE_DEFINITE_ENTITIES
						#define NLC_RECORD_ACTION_HISTORY_COMPENSATE_FOR_EFFECTIVE_DEFINITE_ENTITIES_IMPLEMENTATION
					#endif
					#ifdef NLC_RECORD_ACTION_HISTORY_COMPENSATE_FOR_EFFECTIVE_DEFINITE_ENTITIES_IMPLEMENTATION
						#define NLC_RECORD_ACTION_HISTORY_COMPENSATE_FOR_EFFECTIVE_DEFINITE_ENTITIES_IMPLEMENTATION1	//"a pie" in "The chicken that ate a pie rowed the boat."
						//#define NLC_RECORD_ACTION_HISTORY_COMPENSATE_FOR_EFFECTIVE_DEFINITE_ENTITIES_IMPLEMENTATION2	//"a pie" in "The chicken that ate a pie rowed the boat."
					#endif
				#endif
			#else
				#ifdef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES
					#ifdef GIA_TRANSLATOR_DREAM_MODE_LINK_SPECIFIC_CONCEPTS_AND_ACTIONS	//required for searchForEquivalentSubnetToIfStatement
						#define NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_BASED_ON_ACTIONS_BASIC		//only for !NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
					#endif
				#endif
			#endif
		#endif
	#endif	
	#ifdef GIA_CREATE_NON_SPECIFIC_CONCEPTS_FOR_ALL_NETWORK_INDEXES	//always use concept nodes rather than raw networkIndex nodes to store networkIndex relationships
		#define NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_BASED_ON_NETWORK_INDEXES
		#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_BASED_ON_NETWORK_INDEXES
			//GIA_CREATE_CONCEPTS_FOR_ALL_SENTENCES_WITH_NETWORK_INDEXES hasnt been coded therefore NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_BASED_ON_NETWORK_INDEXES cannot be used
			//static bool isIncomingOutgoingConditionArray[GIA_ENTITY_NUMBER_OF_VECTOR_CONNECTION_TYPES] = {false, false, true, true, false, false, false, false, false, false, false, false, false, false};
			#ifndef NLC_DISABLE_1l_CODE_FOR_DEBUG
				#ifdef GIA_TRANSLATOR_DREAM_MODE_LINK_SPECIFIC_CONCEPTS_AND_ACTIONS	//required for searchForEquivalentSubnetToIfStatement
					#define NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_BASED_ON_NETWORK_INDEXES_BASIC
				#endif
			#endif
		#endif
	#endif
	#define NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_BASED_ON_ACTIONS_OR_NETWORK_INDEXES_DUMMY_REFERENCE_SET_ID (99)
#endif
#ifndef NLC_DISABLE_1l_CODE_FOR_DEBUG
	#define NLC_RECORD_ACTION_HISTORY_GENERALISABLE	//code introduced by NLC_RECORD_ACTION_HISTORY but doesn't necessarily require it
	#ifdef NLC_RECORD_ACTION_HISTORY_GENERALISABLE
		#define NLC_MARK_ACTION_SUBJECT_OBJECT_INDEFINITE_ENTITY_ACTIONS_AS_NOT_SAME_REFERENCE_SET	//1l3c, updated 1l10b
	#endif
	#ifdef NLC_RECORD_ACTION_HISTORY_GENERALISABLE
		#define NLC_RECORD_ACTION_HISTORY_GENERALISABLE_DO_NOT_EXECUTE_PAST_TENSE_ACTIONS	//this currently fails with NLC_LOCAL_LISTS_USE_INSTANCE_NAMES
	#endif
#endif

#ifndef NLC_DISABLE_1l_CODE_FOR_DEBUG
	#ifdef NLC_FUNCTIONS_SUPPORT_PLURAL_SUBJECTS
		#ifdef NLC_USE_ADVANCED_REFERENCING
			#define NLC_FUNCTIONS_SUPPORT_PLURAL_SUBJECTS_ENTER_GENERATED_CATEGORY_LIST
		#elif defined NLC_RECORD_ACTION_HISTORY
			#define NLC_FUNCTIONS_SUPPORT_PLURAL_SUBJECTS_ENTER_GENERATED_CATEGORY_LIST
		#endif
	#endif
	#ifdef NLC_FUNCTIONS_SUPPORT_PLURAL_OBJECTS
		#ifdef NLC_USE_ADVANCED_REFERENCING
			#define NLC_FUNCTIONS_SUPPORT_PLURAL_OBJECTS_ENTER_GENERATED_CATEGORY_LIST
		#elif defined NLC_RECORD_ACTION_HISTORY
			#define NLC_FUNCTIONS_SUPPORT_PLURAL_OBJECTS_ENTER_GENERATED_CATEGORY_LIST
		#endif
	#endif
#endif


#define NLC_USE_PREPROCESSOR	//1g17a/18-July-2014	//reimplementation 1h1a+/22-July-2014 //first working 1h1f
#ifdef NLC_USE_PREPROCESSOR
	#define NLC_USE_PREPROCESSOR_PREPROCESSED_FILE_NAME_APPEND_TEXT "afterPreprocessedforNLConly.txt"
	#ifndef NLC_DISABLE_1k_CODE_FOR_DEBUG
		#ifdef NLC_USE_ADVANCED_REFERENCING
			#define NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT	//1k2a
			#ifdef NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT
				#define NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT_ADD_ENTITY_TO_CONTEXT_LIST_FUNCTION_NAME "addEntityToReferenceContextList"
				#define NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT_CLEAR_CONTEXT_LIST_FUNCTION_NAME "clearReferenceContextList"
				#define NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT_SENTENCE_INDEX_VARIABLE_NAME "sentenceIndex"
				//#define NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT_PRINT_LEVEL_USED_INSTEAD_OF_CONTEXT_LEVEL
			#endif
			#define NLC_PREPROCESSOR_INTERPRET_SINGLE_WORD_SENTENCES_AS_ACTIONS	//1k6a
			#ifdef NLC_PREPROCESSOR_INTERPRET_SINGLE_WORD_SENTENCES_AS_ACTIONS
				#define NLC_PREPROCESSOR_INTERPRET_SINGLE_WORD_SENTENCES_AS_ACTIONS_DUMMY_TEXT_ACTION_OBJECT "dummyactionobject"
				#define NLC_PREPROCESSOR_INTERPRET_SINGLE_WORD_SENTENCES_AS_ACTIONS_REPLACE_ACTION_ALSO_DUE_TO_NLP_LIMITATION	//required for Stanford NLP
				#ifdef NLC_PREPROCESSOR_INTERPRET_SINGLE_WORD_SENTENCES_AS_ACTIONS_REPLACE_ACTION_ALSO_DUE_TO_NLP_LIMITATION
					#define NLC_PREPROCESSOR_INTERPRET_SINGLE_WORD_SENTENCES_AS_ACTIONS_DUMMY_TEXT_ACTION "dummyaction"
					#define NLC_PREPROCESSOR_INTERPRET_SINGLE_WORD_SENTENCES_AS_ACTIONS_DUMMY_TEXT_ACTION_FULL string(NLC_PREPROCESSOR_INTERPRET_SINGLE_WORD_SENTENCES_AS_ACTIONS_DUMMY_TEXT_ACTION " a " NLC_PREPROCESSOR_INTERPRET_SINGLE_WORD_SENTENCES_AS_ACTIONS_DUMMY_TEXT_ACTION_OBJECT)	//"dummyaction a dummyactionobject"
				#else
					#define NLC_PREPROCESSOR_INTERPRET_SINGLE_WORD_SENTENCES_AS_ACTIONS_DUMMY_TEXT_ACTION_OBJECT_FULL string(" a " NLC_PREPROCESSOR_INTERPRET_SINGLE_WORD_SENTENCES_AS_ACTIONS_DUMMY_TEXT_ACTION_OBJECT)	//" a dummyactionobject"
				#endif
			#endif
		#endif
	#endif
	#define NLC_PREPROCESSOR_GENERATE_COMMENTS
	#define NLC_PREPROCESSOR_MATH	//1h1a/22-July-2014	//requires NLC_PREPROCESSOR_LOGICAL_CONDITION_USE_ROBUST_NLP_INDEPENDENT_CODE for preprocessor isLogicalConditionOperator detection	//first working 1h2f
	#ifdef NLC_PREPROCESSOR_MATH
	
		#ifndef GIA_SUPPORT_NUMBER_OF
			#define NLC_PREPROCESSOR_MATH_OLD_NUMBER_OF_IMPLEMENTATION_USING_QVARS
		#endif
		
		#define NLC_PREPROCESSOR_END_OF_SENTENCE_CHAR (CHAR_FULLSTOP)	//this is defined by NLP/English
		#define NLC_PREPROCESSOR_END_OF_SENTENCE_QUESTION_CHAR (CHAR_QUESTIONMARK)	//this is defined by NLP/English
		#define NLC_PREPROCESSOR_MATH_TESTING_ALLOW_GENERATION_OF_UNCOMPILABLE_CODE
		#ifdef NLC_PREPROCESSOR_MATH_TESTING_ALLOW_GENERATION_OF_UNCOMPILABLE_CODE
			//#ifdef NLC_PREPROCESSOR_MATH_DETECT_USE_OF_UNDECLARED_VARIABLES	//will not be defined in releases < 1p
				#define NLC_PREPROCESSOR_MATH_ALLOW_UNDECLARED_MATHTEXT_VARIABLES_TO_BE_REFERENCED_BY_MATH
			//#endif
		#endif
		//#define NLC_PREPROCESSOR_MATH_USE_LOGICAL_CONDITION_OPERATIONS_ADVANCED_BACKWARDS_COMPATIBLE_VARIABLE_NAMES	//used for automated testing only
		#define NLC_PREPROCESSOR_MATH_USE_HUMAN_READABLE_VARIABLE_NAMES	
		#define NLC_PREPROCESSOR_MATH_OPERATOR_GREATER_THAN ">"
		#define NLC_PREPROCESSOR_MATH_OPERATOR_LESS_THAN "<"
		#define NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_TEST "=="
		#define NLC_PREPROCESSOR_MATH_OPERATOR_PLUS "+"
		#define NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_SET "="
		#define NLC_PREPROCESSOR_MATH_OPERATOR_GREATER_THAN_OR_EQUAL_TO ">="
		#define NLC_PREPROCESSOR_MATH_OPERATOR_LESS_THAN_OR_EQUAL_TO "<="
		#define NLC_PREPROCESSOR_MATH_OPERATOR_NOT_GREATER_THAN "<="
		#define NLC_PREPROCESSOR_MATH_OPERATOR_NOT_LESS_THAN ">="
		#define NLC_PREPROCESSOR_MATH_OPERATOR_DOES_NOT_EQUAL "!="	//invalid for set
		#define NLC_PREPROCESSOR_MATH_OPERATOR_IS_NOT_EQUAL_TO "!="	//invalid for set
		#define NLC_PREPROCESSOR_MATH_OPERATOR_OPEN_BRACKET "("
		#define NLC_PREPROCESSOR_MATH_OPERATOR_CLOSE_BRACKET ")"
		#ifdef NLC_USE_MATH_OBJECTS_ADVANCED_USE_UNIQUE_OPERATORS
			#define NLC_PREPROCESSOR_MATH_OPERATOR_STRING_EQUALS_TEST_NEW NLC_USE_MATH_OBJECTS_ADVANCED_USE_UNIQUE_OPERATORS_SYMBOL_STRING_COMPARISON STRING_SPACE NLC_USE_MATH_OBJECTS_STRING_DELIMITER	//~~ "
			#define NLC_PREPROCESSOR_MATH_OPERATOR_STRING_EQUALS_TEST NLC_USE_MATH_OBJECTS_ADVANCED_USE_UNIQUE_OPERATORS_SYMBOL_STRING_COMPARISON	//~~
		#else
			#define NLC_PREPROCESSOR_MATH_OPERATOR_STRING_EQUALS_TEST_NEW NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_TEST STRING_SPACE NLC_USE_MATH_OBJECTS_STRING_DELIMITER	//== "
			#define NLC_PREPROCESSOR_MATH_OPERATOR_STRING_EQUALS_TEST NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_TEST	//==
		#endif		
		#define NLC_PREPROCESSOR_MATH_OPERATOR_STRING_EQUALS_SET_NEW NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_SET STRING_SPACE NLC_USE_MATH_OBJECTS_STRING_DELIMITER	//= "
		#define NLC_PREPROCESSOR_MATH_OPERATOR_STRING_EQUALS_SET NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_SET	//=
		#ifdef NLC_USE_MATH_OBJECTS_ADVANCED_USE_UNIQUE_OPERATORS
			#define NLC_PREPROCESSOR_MATH_OPERATOR_STRING_ADD NLC_USE_MATH_OBJECTS_ADVANCED_USE_UNIQUE_OPERATORS_SYMBOL_STRING_ADDITION	//&
		#else
			#define NLC_PREPROCESSOR_MATH_OPERATOR_STRING_ADD NLC_PREPROCESSOR_MATH_OPERATOR_PLUS	//+
		#endif
		#define NLC_PREPROCESSOR_MATH_OPERATOR_BOOLEAN_EQUALS_TEST_TRUE NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_TEST STRING_SPACE NLC_USE_MATH_OBJECTS_BOOLEAN_VALUE_TRUE	//== true
		#define NLC_PREPROCESSOR_MATH_OPERATOR_BOOLEAN_EQUALS_TEST_FALSE NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_TEST STRING_SPACE NLC_USE_MATH_OBJECTS_BOOLEAN_VALUE_FALSE	//== false
		#define NLC_PREPROCESSOR_MATH_OPERATOR_BOOLEAN_EQUALS_SET_TRUE NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_SET STRING_SPACE NLC_USE_MATH_OBJECTS_BOOLEAN_VALUE_TRUE	//= true
		#define NLC_PREPROCESSOR_MATH_OPERATOR_BOOLEAN_EQUALS_SET_FALSE NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_SET STRING_SPACE NLC_USE_MATH_OBJECTS_BOOLEAN_VALUE_FALSE	//= false
		/*
		//not required; "not .." statements are automatically parsed by NLC, and although a boolean statement expression will be detected (eg "if the dog is not true") by getMathObjectVariableType, this will be superceeded as a boolean expression will be detected (triggered by the word "true") by getMathObjectVariableType
		#define NLC_PREPROCESSOR_MATH_OPERATOR_BOOLEAN_EQUALS_TEST_NOT_TRUE NLC_PREPROCESSOR_MATH_OPERATOR_IS_NOT_EQUAL_TO STRING_SPACE NLC_USE_MATH_OBJECTS_BOOLEAN_VALUE_TRUE	//!= true
		#define NLC_PREPROCESSOR_MATH_OPERATOR_BOOLEAN_EQUALS_TEST_NOT_FALSE NLC_PREPROCESSOR_MATH_OPERATOR_IS_NOT_EQUAL_TO STRING_SPACE NLC_USE_MATH_OBJECTS_BOOLEAN_VALUE_FALSE	//!= false
		static string preprocessorMathOperators[NLC_PREPROCESSOR_MATH_OPERATORS_NUMBER_OF_TYPES] = {NLC_PREPROCESSOR_MATH_OPERATOR_GREATER_THAN, NLC_PREPROCESSOR_MATH_OPERATOR_LESS_THAN, NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_SET, NLC_PREPROCESSOR_MATH_OPERATOR_PLUS, NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_SET, NLC_PREPROCESSOR_MATH_OPERATOR_GREATER_THAN_OR_EQUAL_TO, NLC_PREPROCESSOR_MATH_OPERATOR_LESS_THAN_OR_EQUAL_TO, NLC_PREPROCESSOR_MATH_OPERATOR_NOT_GREATER_THAN, NLC_PREPROCESSOR_MATH_OPERATOR_NOT_LESS_THAN, NLC_PREPROCESSOR_MATH_OPERATOR_DOES_NOT_EQUAL, NLC_PREPROCESSOR_MATH_OPERATOR_IS_NOT_EQUAL_TO, NLC_PREPROCESSOR_MATH_OPERATOR_OPEN_BRACKET, NLC_PREPROCESSOR_MATH_OPERATOR_CLOSE_BRACKET, NLC_PREPROCESSOR_MATH_OPERATOR_STRING_EQUALS_SET_NEW, NLC_PREPROCESSOR_MATH_OPERATOR_STRING_ADD, NLC_PREPROCESSOR_MATH_OPERATOR_BOOLEAN_EQUALS_SET_TRUE, NLC_PREPROCESSOR_MATH_OPERATOR_BOOLEAN_EQUALS_SET_FALSE, NLC_PREPROCESSOR_MATH_OPERATOR_BOOLEAN_EQUALS_SET_FALSE, NLC_PREPROCESSOR_MATH_OPERATOR_BOOLEAN_EQUALS_SET_TRUE};
		static string preprocessorMathOperatorsForLogicalConditions[NLC_PREPROCESSOR_MATH_OPERATORS_NUMBER_OF_TYPES] = {NLC_PREPROCESSOR_MATH_OPERATOR_GREATER_THAN, NLC_PREPROCESSOR_MATH_OPERATOR_LESS_THAN, NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_TEST, NLC_PREPROCESSOR_MATH_OPERATOR_PLUS, NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_TEST, NLC_PREPROCESSOR_MATH_OPERATOR_GREATER_THAN_OR_EQUAL_TO, NLC_PREPROCESSOR_MATH_OPERATOR_LESS_THAN_OR_EQUAL_TO, NLC_PREPROCESSOR_MATH_OPERATOR_NOT_GREATER_THAN, NLC_PREPROCESSOR_MATH_OPERATOR_NOT_LESS_THAN, NLC_PREPROCESSOR_MATH_OPERATOR_DOES_NOT_EQUAL, NLC_PREPROCESSOR_MATH_OPERATOR_IS_NOT_EQUAL_TO, NLC_PREPROCESSOR_MATH_OPERATOR_OPEN_BRACKET, NLC_PREPROCESSOR_MATH_OPERATOR_CLOSE_BRACKET, NLC_PREPROCESSOR_MATH_OPERATOR_STRING_EQUALS_TEST_NEW, NLC_PREPROCESSOR_MATH_OPERATOR_STRING_ADD, NLC_PREPROCESSOR_MATH_OPERATOR_BOOLEAN_EQUALS_TEST_TRUE, NLC_PREPROCESSOR_MATH_OPERATOR_BOOLEAN_EQUALS_TEST_FALSE, NLC_PREPROCESSOR_MATH_OPERATOR_BOOLEAN_EQUALS_TEST_NOT_TRUE, NLC_PREPROCESSOR_MATH_OPERATOR_BOOLEAN_EQUALS_TEST_NOT_FALSE};		
		*/						
		#ifdef NLC_USE_MATH_OBJECTS_ADVANCED
		#define NLC_PREPROCESSOR_MATH_OPERATORS_NUMBER_OF_TYPES (17)
		static string preprocessorMathOperators[NLC_PREPROCESSOR_MATH_OPERATORS_NUMBER_OF_TYPES] = {NLC_PREPROCESSOR_MATH_OPERATOR_GREATER_THAN, NLC_PREPROCESSOR_MATH_OPERATOR_LESS_THAN, NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_SET, NLC_PREPROCESSOR_MATH_OPERATOR_PLUS, NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_SET, NLC_PREPROCESSOR_MATH_OPERATOR_GREATER_THAN_OR_EQUAL_TO, NLC_PREPROCESSOR_MATH_OPERATOR_LESS_THAN_OR_EQUAL_TO, NLC_PREPROCESSOR_MATH_OPERATOR_NOT_GREATER_THAN, NLC_PREPROCESSOR_MATH_OPERATOR_NOT_LESS_THAN, NLC_PREPROCESSOR_MATH_OPERATOR_DOES_NOT_EQUAL, NLC_PREPROCESSOR_MATH_OPERATOR_IS_NOT_EQUAL_TO, NLC_PREPROCESSOR_MATH_OPERATOR_OPEN_BRACKET, NLC_PREPROCESSOR_MATH_OPERATOR_CLOSE_BRACKET, NLC_PREPROCESSOR_MATH_OPERATOR_STRING_EQUALS_SET_NEW, NLC_PREPROCESSOR_MATH_OPERATOR_STRING_ADD, NLC_PREPROCESSOR_MATH_OPERATOR_BOOLEAN_EQUALS_SET_TRUE, NLC_PREPROCESSOR_MATH_OPERATOR_BOOLEAN_EQUALS_SET_FALSE};
		static string preprocessorMathOperatorsForLogicalConditions[NLC_PREPROCESSOR_MATH_OPERATORS_NUMBER_OF_TYPES] = {NLC_PREPROCESSOR_MATH_OPERATOR_GREATER_THAN, NLC_PREPROCESSOR_MATH_OPERATOR_LESS_THAN, NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_TEST, NLC_PREPROCESSOR_MATH_OPERATOR_PLUS, NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_TEST, NLC_PREPROCESSOR_MATH_OPERATOR_GREATER_THAN_OR_EQUAL_TO, NLC_PREPROCESSOR_MATH_OPERATOR_LESS_THAN_OR_EQUAL_TO, NLC_PREPROCESSOR_MATH_OPERATOR_NOT_GREATER_THAN, NLC_PREPROCESSOR_MATH_OPERATOR_NOT_LESS_THAN, NLC_PREPROCESSOR_MATH_OPERATOR_DOES_NOT_EQUAL, NLC_PREPROCESSOR_MATH_OPERATOR_IS_NOT_EQUAL_TO, NLC_PREPROCESSOR_MATH_OPERATOR_OPEN_BRACKET, NLC_PREPROCESSOR_MATH_OPERATOR_CLOSE_BRACKET, NLC_PREPROCESSOR_MATH_OPERATOR_STRING_EQUALS_TEST_NEW, NLC_PREPROCESSOR_MATH_OPERATOR_STRING_ADD, NLC_PREPROCESSOR_MATH_OPERATOR_BOOLEAN_EQUALS_TEST_TRUE, NLC_PREPROCESSOR_MATH_OPERATOR_BOOLEAN_EQUALS_TEST_FALSE};		
		#else
		#define NLC_PREPROCESSOR_MATH_OPERATORS_NUMBER_OF_TYPES (13)
		static string preprocessorMathOperators[NLC_PREPROCESSOR_MATH_OPERATORS_NUMBER_OF_TYPES] = {NLC_PREPROCESSOR_MATH_OPERATOR_GREATER_THAN, NLC_PREPROCESSOR_MATH_OPERATOR_LESS_THAN, NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_SET, NLC_PREPROCESSOR_MATH_OPERATOR_PLUS, NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_SET, NLC_PREPROCESSOR_MATH_OPERATOR_GREATER_THAN_OR_EQUAL_TO, NLC_PREPROCESSOR_MATH_OPERATOR_LESS_THAN_OR_EQUAL_TO, NLC_PREPROCESSOR_MATH_OPERATOR_NOT_GREATER_THAN, NLC_PREPROCESSOR_MATH_OPERATOR_NOT_LESS_THAN, NLC_PREPROCESSOR_MATH_OPERATOR_DOES_NOT_EQUAL, NLC_PREPROCESSOR_MATH_OPERATOR_IS_NOT_EQUAL_TO, NLC_PREPROCESSOR_MATH_OPERATOR_OPEN_BRACKET, NLC_PREPROCESSOR_MATH_OPERATOR_CLOSE_BRACKET};
		static string preprocessorMathOperatorsForLogicalConditions[NLC_PREPROCESSOR_MATH_OPERATORS_NUMBER_OF_TYPES] = {NLC_PREPROCESSOR_MATH_OPERATOR_GREATER_THAN, NLC_PREPROCESSOR_MATH_OPERATOR_LESS_THAN, NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_TEST, NLC_PREPROCESSOR_MATH_OPERATOR_PLUS, NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_TEST, NLC_PREPROCESSOR_MATH_OPERATOR_GREATER_THAN_OR_EQUAL_TO, NLC_PREPROCESSOR_MATH_OPERATOR_LESS_THAN_OR_EQUAL_TO, NLC_PREPROCESSOR_MATH_OPERATOR_NOT_GREATER_THAN, NLC_PREPROCESSOR_MATH_OPERATOR_NOT_LESS_THAN, NLC_PREPROCESSOR_MATH_OPERATOR_DOES_NOT_EQUAL, NLC_PREPROCESSOR_MATH_OPERATOR_IS_NOT_EQUAL_TO, NLC_PREPROCESSOR_MATH_OPERATOR_OPEN_BRACKET, NLC_PREPROCESSOR_MATH_OPERATOR_CLOSE_BRACKET};
		#endif
		#define NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_SET_CHAR (CHAR_EQUALS)
		#define NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_SET_WITH_PADDING STRING_SPACE NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_SET STRING_SPACE
		#define NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_TEST_WITH_PADDING STRING_SPACE NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_TEST STRING_SPACE
		#define NLC_PREPROCESSOR_MATH_OPERATOR_STRING_ADD_WITH_PADDING STRING_SPACE NLC_PREPROCESSOR_MATH_OPERATOR_STRING_ADD STRING_SPACE
		#define NLC_PREPROCESSOR_MATH_OPERATOR_STRING_EQUALS_TEST_WITH_PADDING STRING_SPACE NLC_PREPROCESSOR_MATH_OPERATOR_STRING_EQUALS_TEST STRING_SPACE
		#ifndef NLC_USE_MATH_OBJECTS_ADVANCED_USE_UNIQUE_OPERATORS
			#define NLC_PREPROCESSOR_MATH_FIX_USER_INAPPROPRIATE_USE_OF_EQUALS_SET_IN_LOGICAL_CONDITIONS	//NB not compatible with NLC_USE_MATH_OBJECTS_ADVANCED_USE_UNIQUE_OPERATORS, as unsure which test operator to replace = with; == or ~~
		#endif
		
		#ifdef NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_SUPPORT_FILENAMES_WITH_FULLSTOPS
			#define NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_CHARACTERS_NUMBER_OF_TYPES (65)
			static char preprocessorMathNLPparsableCharacters[NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_CHARACTERS_NUMBER_OF_TYPES] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '_', '.','\''};
			#define NLC_NLP_PARSABLE_PHRASE_CHARACTERS_NUMBER_OF_TYPES (66)
			static char NLPparsableCharacters[NLC_NLP_PARSABLE_PHRASE_CHARACTERS_NUMBER_OF_TYPES] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '_', '-', '$', '.'};	
		#else
			#define NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_CHARACTERS_NUMBER_OF_TYPES (64)
			static char preprocessorMathNLPparsableCharacters[NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_CHARACTERS_NUMBER_OF_TYPES] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '_','\''};
			#define NLC_NLP_PARSABLE_PHRASE_CHARACTERS_NUMBER_OF_TYPES (65)
			static char NLPparsableCharacters[NLC_NLP_PARSABLE_PHRASE_CHARACTERS_NUMBER_OF_TYPES] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '_', '-', '$'};
		#endif

		//#ifdef NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY
			#define NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_SUPPORT_ALPHANUMERIC_VARIABLE_NAMES	//1j21b (updated 1k7a) //required for NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY
		//#endif
		#ifdef NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_SUPPORT_ALPHANUMERIC_VARIABLE_NAMES
			#ifndef NLC_DISABLE_1k_CODE_FOR_DEBUG
				#define NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_SUPPORT_ALPHANUMERIC_VARIABLE_NAMES_ONLY	//1k7b
				#ifdef NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_SUPPORT_ALPHANUMERIC_VARIABLE_NAMES_ONLY
					#define NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_NUMERICAL_CHARACTERS_NUMBER_OF_TYPES (10)
					static char preprocessorMathNLPparsableNumericalCharacters[NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_NUMERICAL_CHARACTERS_NUMBER_OF_TYPES] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
					#ifdef NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_SUPPORT_FILENAMES_WITH_FULLSTOPS
						#define NLC_PREPROCESSOR_MATH_VARIABLE_NAME_CHARACTERS_ILLEGAL_AS_FIRST_NUMBER_OF_TYPES (NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_NUMERICAL_CHARACTERS_NUMBER_OF_TYPES+1)
						static char preprocessorMathVariableNameCharactersIllegalAsFirst[NLC_PREPROCESSOR_MATH_VARIABLE_NAME_CHARACTERS_ILLEGAL_AS_FIRST_NUMBER_OF_TYPES] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.'};
					#else
						#define NLC_PREPROCESSOR_MATH_VARIABLE_NAME_CHARACTERS_ILLEGAL_AS_FIRST_NUMBER_OF_TYPES (NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_NUMERICAL_CHARACTERS_NUMBER_OF_TYPES)
						static char preprocessorMathVariableNameCharactersIllegalAsFirst[NLC_PREPROCESSOR_MATH_VARIABLE_NAME_CHARACTERS_ILLEGAL_AS_FIRST_NUMBER_OF_TYPES] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
					#endif
					#define NLC_PREPROCESSOR_MATH_VARIABLE_NAME_CHARACTERS_ILLEGAL_AS_FIRST_REPLACEMENT_CHARACTER "n"
					#define NLC_PREPROCESSOR_MATH_VARIABLE_NAME_CHARACTERS_MANDATORY_NUMBER_OF_TYPES (53)
					static char preprocessorMathVariableNameCharactersMandatory[NLC_PREPROCESSOR_MATH_VARIABLE_NAME_CHARACTERS_MANDATORY_NUMBER_OF_TYPES] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '_'};
				#endif
			#endif
		#else
			#define NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_CHARACTERS_MANDATORY_NUMBER_OF_TYPES (53)
			static char preprocessorMathNLPparsableCharactersMandatory[NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_CHARACTERS_MANDATORY_NUMBER_OF_TYPES] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '_'};
		#endif
		#define NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_CHARACTERS_DELIMITER_NUMBER_OF_TYPES (1)
		static char preprocessorMathNLPparsableCharactersDelimiter[NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_CHARACTERS_DELIMITER_NUMBER_OF_TYPES] = {CHAR_SPACE};	//CHAR_COMMA removed 1h1e (parsable phrases are divided by commas)
		#define NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_MIN_NUMBER_WORDS (2)
		#define NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_REFERENCE "nlpParsablePhraseRef"
		#define NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_REFERENCE_SENTENCE "S"
		#define NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_REFERENCE_PHRASE "P"
		//#define NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_REFERENCE_LEVEL "L"	//not currently used
		//#define NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_REFERENCE_CASE "C"	//not currently used
		#define NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_DUMMY "Do this."
		
		#define NLC_PREPROCESSOR_MATH_REPLACE_NUMERICAL_VARIABLES_NAMES_FOR_NLP	//old name: NLC_PREPROCESSOR_SUPPORT_MATH_DETECT_NUMERICAL_VARIABLES
		#ifdef NLC_PREPROCESSOR_MATH_REPLACE_NUMERICAL_VARIABLES_NAMES_FOR_NLP
			#define NLC_PREPROCESSOR_MATH_DUMMY_NUMBER_VALUE_BASE (9900)
			//#define NLC_PREPROCESSOR_REPLACE_NUMERICAL_VARIABLES_DETECT_GLOBAL_NUMERICAL_VARIABLES 	//global defs are disabled by default
		#endif
	

		#define NLC_PREPROCESSOR_MATH_DETECT_AND_DECLARE_IMPLICITLY_DECLARED_VARIABLES
		#ifdef NLC_PREPROCESSOR_MATH_DETECT_AND_DECLARE_IMPLICITLY_DECLARED_VARIABLES
			#define NLC_PREPROCESSOR_MATH_MATHTEXT_VARIABLE_TYPE_NUMERICAL "double$ "
			#define NLC_PREPROCESSOR_MATH_MATHTEXT_VARIABLE_TYPE_STRING "string$ "
			#define NLC_PREPROCESSOR_MATH_MATHTEXT_VARIABLE_TYPE_BOOLEAN "bool$ "
		#endif
		
		#if NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_MIN_NUMBER_WORDS <= 2
			#define NLC_PREPROCESSOR_MATH_SUPPORT_USER_VARIABLE_TYPE_DECLARATIONS
			#ifdef NLC_PREPROCESSOR_MATH_SUPPORT_USER_VARIABLE_TYPE_DECLARATIONS
				#define NLC_PREPROCESSOR_MATH_MATHTEXT_VARIABLES_NUMBER_OF_TYPES (8)
				static string preprocessorMathNaturalLanguageVariables[NLC_PREPROCESSOR_MATH_MATHTEXT_VARIABLES_NUMBER_OF_TYPES] = {"bool", "char", "short", "int", "integer", "float", "double", "string"};
				static string preprocessorMathMathTextVariables[NLC_PREPROCESSOR_MATH_MATHTEXT_VARIABLES_NUMBER_OF_TYPES] = {"bool$", "char$", "short$", "int$", "integer$", "float$", "double$", "string$"};	//{"$0", "$1", "$2", "$4", "$4", "#4", "#8", "??"};
				#ifdef NLC_USE_MATH_OBJECTS
				static int preprocessorMathTextVariableMathObjectTypes[NLC_PREPROCESSOR_MATH_MATHTEXT_VARIABLES_NUMBER_OF_TYPES] = {NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_BOOLEAN, NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_NUMERICAL, NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_NUMERICAL, NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_NUMERICAL, NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_NUMERICAL, NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_NUMERICAL, NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_NUMERICAL, NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_STRING};
				#ifdef NLC_API
				#define NLC_API_VARIABLE_TYPE_STANDARD_NUMBER_OF_TYPES (8)	//this needs to be extended (and made programming language independent)
				static string APIvariableTypeStandard[NLC_API_VARIABLE_TYPE_STANDARD_NUMBER_OF_TYPES] = {"bool", "char", "short", "int", "integer", "float", "double", "string"};	//should be synced with preprocessorMathNaturalLanguageVariables
				static int APIvariableTypeStandardMathObjectTypes[NLC_API_VARIABLE_TYPE_STANDARD_NUMBER_OF_TYPES] = {NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_BOOLEAN, NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_NUMERICAL, NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_NUMERICAL, NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_NUMERICAL, NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_NUMERICAL, NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_NUMERICAL, NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_NUMERICAL, NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_STRING};	//should be synced with preprocessorMathTextVariableMathObjectTypes
				#endif
				#endif
			#endif
		#endif
		
		#define NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_IS_EQUAL_TO_INFORMAL " is "
		#define NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE	//replaces NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED implementation	//first working 1h3i
		#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
			
			#define NLC_PREPROCESSOR_MATH_OPERATOR_NEGATIVE_CHAR '!'
			
			#define NLC_PREPROCESSOR_MATH_PARSABLE_PHRASE_START_TEXT_INDICATING_LOGICAL_CONDITION_COMMAND ", "
			#define NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
			#ifdef NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
				//#define NLC_PREPROCESSOR_MATH_SUPPORT_MULTIPLE_LOGICAL_CONDITION_COMMANDS_ON_ONE_LINE		//eg "if the house is blue, write the letter and read the book"/"else write the letter and read the book."	//Not yet implemented
				#define NLC_PREPROCESSOR_MATH_SUPPORT_LOGICAL_CONDITION_MATHTEXT_COMMANDS_ON_SAME_LINE 		//eg "if the house is blue, X = 3+5"	//untested
				#define NLC_PREPROCESSOR_MATH_SUPPORT_LOGICAL_CONDITION_IMPLICIT_CONJUNCTIONS			//eg "if the house is blue, the cat is green, and the bike is tall, ride the bike"	//testing now
				#define NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_COORDINATING_CONJUNCTION_AND_INDEX (0)	//&&
				#define NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_COORDINATING_CONJUNCTION_OR_INDEX (1)	//||
			#endif
			
			#define NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_IS_GREATER_THAN "is greater than"
			#define NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_IS_LESS_THAN "is less than"
			#define NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_EQUALS "equals"
			#define NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_PLUS "plus"
			#define NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_IS_EQUAL_TO "is equal to"
			#define NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_IS_GREATER_THAN_OR_EQUAL_TO "is greater than or equal to"
			#define NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_IS_LESS_THAN_OR_EQUAL_TO "is less than or equal to"
			#define NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_IS_NOT_GREATER_THAN "is not greater than"
			#define NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_IS_NOT_LESS_THAN "is not less than"
			#define NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_DOES_NOT_EQUAL "does not equal"
			#define NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_IS_NOT_EQUAL_TO "is not equal to"
			#define NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_OPEN_BRACKET "NLC macro arguments start"	//not used
			#define NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_CLOSE_BRACKET "NLC macro arguments end"	//not used	
			#define NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_IS_STRING "is \""
			#define NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADD_STRING "concatenated with"
			#define NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_IS_BOOLEAN_TRUE "is true"
			#define NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_IS_BOOLEAN_FALSE "is false"
			/*
			//not required; "not .." statements are automatically parsed by NLC, and although a boolean statement expression will be detected (eg "if the dog is not true") by getMathObjectVariableType, this will be superceeded as a boolean expression will be detected (triggered by the word "true") by getMathObjectVariableType
			#define NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_IS_BOOLEAN_NOT_TRUE "is not true"
			#define NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_IS_BOOLEAN_NOT_FALSE "is not false"
			*/
			//#define NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_EQUALS_STRING "is the same as"
			#ifdef NLC_USE_MATH_OBJECTS_ADVANCED
			static string preprocessorMathOperatorsEquivalentNumberOfTypes[NLC_PREPROCESSOR_MATH_OPERATORS_NUMBER_OF_TYPES] = {NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_IS_GREATER_THAN, NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_IS_LESS_THAN, NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_EQUALS, NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_PLUS, NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_IS_EQUAL_TO, NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_IS_GREATER_THAN_OR_EQUAL_TO, NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_IS_LESS_THAN_OR_EQUAL_TO, NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_IS_NOT_GREATER_THAN, NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_IS_NOT_LESS_THAN, NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_DOES_NOT_EQUAL, NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_IS_NOT_EQUAL_TO, NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_OPEN_BRACKET, NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_CLOSE_BRACKET, NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_IS_STRING, NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADD_STRING, NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_IS_BOOLEAN_TRUE, NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_IS_BOOLEAN_FALSE};
			#else
			static string preprocessorMathOperatorsEquivalentNumberOfTypes[NLC_PREPROCESSOR_MATH_OPERATORS_NUMBER_OF_TYPES] = {NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_IS_GREATER_THAN, NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_IS_LESS_THAN, NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_EQUALS, NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_PLUS, NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_IS_EQUAL_TO, NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_IS_GREATER_THAN_OR_EQUAL_TO, NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_IS_LESS_THAN_OR_EQUAL_TO, NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_IS_NOT_GREATER_THAN, NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_IS_NOT_LESS_THAN, NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_DOES_NOT_EQUAL, NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_IS_NOT_EQUAL_TO, NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_OPEN_BRACKET, NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_CLOSE_BRACKET};			
			#endif
			
			#define NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE_REPLACE_COMMAS_WITH_BRACKETS		//this is required by NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
			#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE_REPLACE_COMMAS_WITH_BRACKETS
				#define NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_COORDINATING_CONJUNCTION_WITH_PAUSE_ARRAY_NUMBER_OF_TYPES (2)
				static string preprocessorMathOperatorsEquivalentConjunctionsWithPause[NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_COORDINATING_CONJUNCTION_WITH_PAUSE_ARRAY_NUMBER_OF_TYPES] = {", and ", ", or "};
				static string progLangCoordinatingConjunctionsWithPause[NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_COORDINATING_CONJUNCTION_WITH_PAUSE_ARRAY_NUMBER_OF_TYPES] = {") && (", ") || ("};				
				#define NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_COORDINATING_CONJUNCTION_ARRAY_NUMBER_OF_TYPES (4)
				static string preprocessorMathOperatorsEquivalentConjunctions[NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_COORDINATING_CONJUNCTION_ARRAY_NUMBER_OF_TYPES] = {", and ", ", or ", " and ", " or "};		//use intermediary mathText symbols for equivalent natural lanaguage replacements eg &&/|| and convert later to compiler specific symbols if necessary during codeblocks print
				static string progLangCoordinatingConjunctions[NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_COORDINATING_CONJUNCTION_ARRAY_NUMBER_OF_TYPES] = {") && (", ") || (", " && ", " || "};	//use intermediary mathText symbols for equivalent natural lanaguage replacements eg &&/|| and convert later to compiler specific symbols if necessary during codeblocks print 
				#define NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_COORDINATING_CONJUNCTION_WITHOUT_PAUSE_ARRAY_NUMBER_OF_TYPES (2)
				static string preprocessorMathOperatorsEquivalentConjunctionsWithoutPause[NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_COORDINATING_CONJUNCTION_WITHOUT_PAUSE_ARRAY_NUMBER_OF_TYPES] = {" and ", " or "};
				static string progLangCoordinatingConjunctionsWithoutPause[NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_COORDINATING_CONJUNCTION_WITHOUT_PAUSE_ARRAY_NUMBER_OF_TYPES] = {" && ", " || "};
				#define NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_COORDINATING_CONJUNCTION_WITHOUT_END_WHITESPACE_ARRAY_NUMBER_OF_TYPES (2)
				static string preprocessorMathOperatorsEquivalentConjunctionsWithoutEndWhiteSpace[NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_COORDINATING_CONJUNCTION_WITHOUT_END_WHITESPACE_ARRAY_NUMBER_OF_TYPES] = {" and", " or"};
				static string progLangCoordinatingConjunctionsWithoutEndWhiteSpace[NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_COORDINATING_CONJUNCTION_WITHOUT_END_WHITESPACE_ARRAY_NUMBER_OF_TYPES] = {" &&", " ||"};
				#define NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_COORDINATING_CONJUNCTION_WITHOUT_WHITESPACE_ARRAY_NUMBER_OF_TYPES (2)
				static string progLangCoordinatingConjunctionsWithoutWhiteSpace[NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_COORDINATING_CONJUNCTION_WITHOUT_WHITESPACE_ARRAY_NUMBER_OF_TYPES] = {"&&", "||"};
				#define NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_COORDINATING_CONJUNCTION_WITH_AND_WITHOUT_WHITESPACE_ARRAY_NUMBER_OF_TYPES (4)
				static string progLangCoordinatingConjunctionsWithAndWithoutWhiteSpace[NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_COORDINATING_CONJUNCTION_WITH_AND_WITHOUT_WHITESPACE_ARRAY_NUMBER_OF_TYPES] = {" && ", " || ", "&&", "||"};
			#else
				#define NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_COORDINATING_CONJUNCTION_ARRAY_NUMBER_OF_TYPES (2)
				static string preprocessorMathOperatorsEquivalentConjunctions[NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_COORDINATING_CONJUNCTION_ARRAY_NUMBER_OF_TYPES] = {"and", "or"};		//use intermediary mathText symbols for equivalent natural lanaguage replacements eg &&/|| and convert later to compiler specific symbols if necessary during codeblocks print
				static string progLangCoordinatingConjunctions[NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_COORDINATING_CONJUNCTION_ARRAY_NUMBER_OF_TYPES] = {"&&", "||"};	//use intermediary mathText symbols for equivalent natural lanaguage replacements eg &&/|| and convert later to compiler specific symbols if necessary during codeblocks print 

			#endif
			#define NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_OPEN_BRACKET '('	//use intermediary mathText symbols for equivalent natural lanaguage replacements eg &&/|| and convert later to compiler specific symbols if necessary during codeblocks print 
			#define NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_CLOSE_BRACKET ')'	//use intermediary mathText symbols for equivalent natural lanaguage replacements eg &&/|| and convert later to compiler specific symbols if necessary during codeblocks print
			#define NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_OPEN_BRACKET_STRING "("
			#define NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_CLOSE_BRACKET_STRING ")"
			
			#define NLC_LOGICAL_CONDITION_OPERATIONS_IF_ELSE_IF_ELSE_NUMBER_OF_TYPES (3)
			static int logicalConditionOperationsIfElseIfElseArray[NLC_LOGICAL_CONDITION_OPERATIONS_IF_ELSE_IF_ELSE_NUMBER_OF_TYPES] = {NLC_LOGICAL_CONDITION_OPERATIONS_IF, NLC_LOGICAL_CONDITION_OPERATIONS_ELSE_IF, NLC_LOGICAL_CONDITION_OPERATIONS_ELSE};	
			#define NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_AUXILIARY_KEYWORDS_TAGGING_SUBJECT_OR_REFERENCE_NUMBER_OF_TYPES (4)
			static string preprocessorMathAuxiliaryKeywordsTaggingSubjectOrReference[NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_AUXILIARY_KEYWORDS_TAGGING_SUBJECT_OR_REFERENCE_NUMBER_OF_TYPES] = {"has", "have", "is", "are"};	//don't use lemmas				
			#define NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_RCMOD_SAME_REFERENCE_SET_DELIMITER_NUMBER_OF_TYPES (2)
			static string preprocessorMathRcmodSameReferenceSetDelimiter[NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_RCMOD_SAME_REFERENCE_SET_DELIMITER_NUMBER_OF_TYPES] = {"that", "which"};			
			
			#define NLC_PREPROCESSOR_MATH_SEARCH_FOR_CONJUNCTION_SUBJECT_MATCH_NON_IDENTICAL_AUXILLARIES	//introduced 1h6c //test this 
				
			#define NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_MAX_CHARACTERS (10000)
		#endif
		//#define NLC_PREPROCESSOR_PRINT_OUTPUT
	#endif
	//#define NLC_PREPROCESSOR_SUPPORT_MULTILINE_SENTENCES
	//#define NLC_PREPROCESSOR_SUPPORT_MATH_DECIMAL_PLACES
	#define NLC_PREPROCESSOR_INDENTATION_CHAR (CHAR_TAB)
	#define NLC_PREPROCESSOR_FUNCTION_HEADER_STRING "function"
	#define NLC_PREPROCESSOR_FUNCTION_HEADER_MID_CHAR (STRING_SPACE)
	#define NLC_PREPROCESSOR_MAX_INDENTATION_LEVELS (100)
#endif

#define NLC_TRANSLATE_NEGATIVE_PROPERTIES_AND_CONDITIONS	//1g16a/16-July-2014

#define NLC_VERIFY_CONNECTIONS_SENTENCE_INDEX	//1g15a/16-July-2014	//requires GIA_STORE_CONNECTION_SENTENCE_INDEX

#define NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE	//added 1g13b+/15-July-2014

#define NLC_DEFINE_LOCAL_VARIABLES_FOR_ALL_INDEFINATE_ENTITIES	//1g8a+ local variable implementation
#ifndef NLC_DISABLE_1k_CODE_FOR_DEBUG
	#define NLC_USE_ADVANCED_REFERENCING_DECLARE_LOCAL_PROPERTY_LISTS_FOR_ALL_INDEFINITE_ENTITIES_FOR_ALL_SENTENCES	//1k1a
#endif

#define NLC_CLASS_DEFINITIONS_ORDER_BY_DEPENDENCIES	//1f14b (required for C++ compilation)
#define NLC_CLASS_DEFINITIONS_USE_GENERIC_LIBRARY_ENTITY_CLASS	//1f14c (a base NLC entity class is required to be defined for integration of generic NLC Library)
#ifdef NLC_CLASS_DEFINITIONS_USE_GENERIC_LIBRARY_ENTITY_CLASS
	#define NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE "NLCgenericEntity"
#endif
//#define NLC_USE_DESTRUCTORS

#define NLC_SUPPORT_QUANTITIES	//1f3a

#ifndef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
	#define NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED		//1f1a+ if statement support	//not currently maintained (with introduction of NLC preprocessor logical condition detection)
#endif

#define NLC_TRANSFORM_THE_ACTION_OF_POSSESSION_EG_HAVING_CONDITION_INTO_A_PROPERTY_CONDITION	//assumes #ifndef GIA_TRANSLATOR_TRANSFORM_THE_ACTION_OF_POSSESSION_EG_HAVING_INTO_A_PROPERTY_BASIC

#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED

	#define NLC_LOGICAL_CONDITION_CONJUNCTION_BOOLEAN_VARIABLE_NAME "logicalCondition"	//eg logicalCondition	
	#define NLC_LOGICAL_CONDITION_CONJUNCTION_BOOLEAN_VARIABLE_NAME_LEVEL "L"		//eg logicalConditionL0		//L="level"
	#define NLC_LOGICAL_CONDITION_CONJUNCTION_BOOLEAN_VARIABLE_NAME_CASE "C"		//eg logicalConditionL0C0	//C="case"
	
	#define NLC_ONLY_SUPPORT_LOGICAL_CONJUNCTION_FOR_AT_START_OF_SENTENCE	//this is a more restricted implementation but is faster. It still requires modifications of GIA (it requires entityIndex information to be stored in GIAdatabase.cpp or GIAxmlConversion.cpp)
	#define NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS_ADVANCED	//1gXy+ logical if/while/for support + conjunction support
	#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS_ADVANCED
		#define NLC_MAXIMUM_NUMBER_OF_CONJUNCTIONS_IN_SENTENCE (100)
		//#assert defined NLC_TRANSFORM_THE_ACTION_OF_POSSESSION_EG_HAVING_CONDITION_INTO_A_PROPERTY_CONDITION
	#else
		#define NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS_BASIC
	#endif
	
	#ifdef NLC_USE_PREPROCESSOR
		#define NLC_PREPROCESSOR_LOGICAL_CONDITION_DUMMY_TEXT_ACTION "do"
		#define NLC_PREPROCESSOR_LOGICAL_CONDITION_DUMMY_TEXT_ACTION_OBJECT "this"
		#define NLC_PREPROCESSOR_LOGICAL_CONDITION_DUMMY_TEXT_TEST_ELSE "If this is done,"	//replaces "Else"
		#define NLC_PREPROCESSOR_LOGICAL_CONDITION_DUMMY_TEXT_TEST_ELSEIF "If"		//replaces "Else if"
		#define NLC_PREPROCESSOR_LOGICAL_CONDITION_DUMMY_TEXT_COMMAND_ELSE " " NLC_PREPROCESSOR_LOGICAL_CONDITION_DUMMY_TEXT_ACTION " " NLC_PREPROCESSOR_LOGICAL_CONDITION_DUMMY_TEXT_ACTION_OBJECT "."	//" do this."	//appending to "Else" statments without a command (in which it is assumed the following indented lines constitute the command)
		#define NLC_PREPROCESSOR_LOGICAL_CONDITION_DUMMY_TEXT_COMMAND "," NLC_PREPROCESSOR_LOGICAL_CONDITION_DUMMY_TEXT_COMMAND_ELSE	//", do this."	//appending to "If" statments without a command (in which it is assumed the following indented lines constitute the command)
		#define NLC_PREPROCESSOR_LOGICAL_CONDITION_USE_ROBUST_NLP_INDEPENDENT_CODE
	#endif
#endif
#define NLC_LOGICAL_CONDITION_OPERATIONS_WORD_IMMEDIATELY_SUCCEEDING_FOR_NUMBER_OF_TYPES (3)
static string logicalConditionOperationsWordImmediatelySucceedingForArray[NLC_LOGICAL_CONDITION_OPERATIONS_WORD_IMMEDIATELY_SUCCEEDING_FOR_NUMBER_OF_TYPES] = {"each", "all", "every"};	//should be dynamically defined in NLCrules.xml (should sync with GIArules.xml redistributeStanfordRelationsSetPluralBasedOnPredeterminers)

//#define NLC_STRICT_MODE_FAVOUR_COMPILATION_RATHER_THAN_DESIGN_USE_MAIN_ENTRY_POINT	//depreciated 1q1a
//#define NLC_CREATE_A_SEPARATE_CLASS_FOR_CONCEPT_DEFINITIONS	//BAD	//depreciated 1q6a: not supported by fillActionLists

//#define NLC_CREATE_IMPLICITLY_DECLARED_ACTION_OBJECT_AND_SUBJECT_VARIABLES	//1e3a	//no longer used

#define NLC_SUPPORT_INPUT_FUNCTION_LISTS	//started 1d1x	//required for NLC functions
#ifdef NLC_SUPPORT_INPUT_FUNCTION_LISTS
	#define NLC_SUPPORT_INPUT_FUNCTION_LISTS_EXPLICIT_FROM_DEDICATED_FILE	//added 1d1x	//required for NLC functions
	#ifdef NLC_USE_PREPROCESSOR
		#define NLC_SUPPORT_INPUT_FUNCTION_LISTS_PREPROCESSOR	//1g17a/18-July-2014	//reimplementation 1h1a+/22-July-2014 //first working 1h1f
	#endif
	#define NLC_SUPPORT_INPUT_FUNCTION_LISTS_MAX_INHERITANCE_DEPTH_FOR_CLASS_CASTING (99)
	#define NLC_SUPPORT_INPUT_FUNCTION_LISTS_ACTION_DELIMITER "#"
	#define NLC_SUPPORT_INPUT_FUNCTION_LISTS_ACTION_DELIMITER_LENGTH (1)
	#define NLC_SUPPORT_INPUT_FUNCTION_LISTS_ACTION_OBJECT_DELIMITER "+"
	#define NLC_SUPPORT_INPUT_FUNCTION_LISTS_ACTION_OBJECT_DELIMITER_LENGTH (1)
	#ifdef NLC_USE_LIBRARY
		#define NLC_SUPPORT_INPUT_FUNCTION_LISTS_ACTION_ARGUMENT_DELIMITER "!"
		#define NLC_SUPPORT_INPUT_FUNCTION_LISTS_ACTION_ARGUMENT_DELIMITER_LENGTH (1)
	#endif
	#define NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS	//added x?
	#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS
		#define NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_BASED_ON_IMPLICITLY_DECLARED_VARIABLES_IN_CURRENT_FUNCTION_DEFINITION	//added x?
		#ifdef NLC_DISABLE_1k_CODE_FOR_DEBUG
			#define NLC_SUPPORT_INPUT_FUNCTION_LISTS_CHECK_ACTION_SUBJECT_CONTENTS_FOR_IMPLICITLY_DECLARED_PARAMETERS	//added 1d1b
		#else
			#define NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED	//1k9c
			#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
				#define NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ACCEPT_NON_EXACT_MATCH	//1k9c
				#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ACCEPT_NON_EXACT_MATCH
					#define NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ACCEPT_NON_EXACT_MATCH_SUBJECT	//1k9c
					#define NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ACCEPT_NON_EXACT_MATCH_OBJECT	//1k9c
				#endif
				#define NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE	//1k13a
				#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE
					#define NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE_ACTIVE	//official code (can be disabled for testing)
					#define NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE_IGNORE_DUPLICATE_FUNCTION_DELCARATIONS	//1k13a		//mandatory as of 1p4a
				#endif
			#endif
			#define NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_ARGUMENTS_NO_OBJECT      //1k13a 
			#define NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_ARGUMENTS_NO_SUBJECT     //1k13a	//requires NLC_CLASS_DEFINITIONS_SUPPORT_FUNCTIONS_WITHOUT_SUBJECT
		#endif
		#define NLC_CAST_VECTOR_FUNCTION_NAME "castVector"	//1k9d
		#ifndef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
			#define NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_BASED_ON_IMPLICITLY_DECLARED_VARIABLES_IN_CURRENT_FUNCTION_DEFINITION_NON_ADVANCED
		#endif
	#endif
	#define NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS
	#ifndef NLC_DISABLE_1k_CODE_FOR_DEBUG
		#define NLC_GENERATE_FUNCTION_ARGUMENTS_PASS_LISTS_BY_REFERENCE	//added 1k5d
		#define NLC_GENERATE_FUNCTION_ARGUMENTS_ENABLE_TYPE_CASTING	//added 1k9e
		#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS
			#ifndef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES
				#ifdef NLC_USE_PREPROCESSOR
					#define NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS_SUPPORT_LOCAL_LISTS_USE_CLASS_NAMES	//added 1k10a/1k12a
					#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS_SUPPORT_LOCAL_LISTS_USE_CLASS_NAMES
						#ifndef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN_SUBCLASSES
							//#define NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS_SUPPORT_LOCAL_LISTS_USE_CLASS_NAMES_ADVANCED	//added 1k12b, disabled 1s8a (because the algorithm implemented behind this function fails in certain cases)
						#endif
					#endif
				#endif
			#endif
		#endif
	#endif
	#ifndef NLC_DISABLE_1k_CODE_FOR_DEBUG
		#define NLC_CLASS_DEFINITIONS_CREATE_FUNCTION_DECLARATIONS_FOR_NEW_FUNCTION_DEFINITIONS	//1k13a	//required by NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE	//mandatory as of 1p4a
		#ifdef NLC_CLASS_DEFINITIONS_CREATE_FUNCTION_DECLARATIONS_FOR_NEW_FUNCTION_DEFINITIONS
			#define NLC_CLASS_DEFINITIONS_CREATE_FUNCTION_DECLARATIONS_FOR_NEW_FUNCTION_DEFINITIONS_CLASS_DEFINITION_HIDDEN_NAME_APPEND "NewFunctionDefinition"
		#endif
	#endif
#endif
#ifndef NLC_DISABLE_1k_CODE_FOR_DEBUG
	#define NLC_CLASS_DEFINITIONS_SUPPORT_FUNCTIONS_WITHOUT_SUBJECT	//1k13a	//required by NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE	//mandatory as of 1p4a
	#ifdef NLC_CLASS_DEFINITIONS_SUPPORT_FUNCTIONS_WITHOUT_SUBJECT
		#define NLC_CLASS_DEFINITIONS_SUPPORT_FUNCTIONS_WITHOUT_SUBJECT_ARTIFICIAL_CLASS_NAME "functionsWithNoSubjectArtificial"
	#endif
#endif
	
//#ifdef NLC_SUPPORT_INPUT_FUNCTION_LISTS
	//#define NLC_INTERPRET_ACTION_PROPERTIES_AND_CONDITIONS_AS_FUNCTION_ARGUMENTS	//removed 1e1a; now pass action action and action object as arguments cf NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS (do not pass action subject[?] properties and conditions as arguments)	//depreciated
	#define NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS	//added 1e1a
	#ifndef NLC_DISABLE_1k_CODE_FOR_DEBUG
		#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS
			#define NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS_PASS_AS_LISTS	//added 1k5c
		#endif
		//#define NLC_CONDITION_LISTS_STORE_CONDITION_AS_STRING	//certified 1k3a	//NB NLC_CONDITION_LISTS_STORE_CONDITION_AS_STRING/unorderedMap<sting, entity*> is not an appropriate data structure to store conditionLists, as there may be more than one condition of a given type; therefore are currently using unorderedMap<entity*, entity*>
	#endif
//#endif

#define NLC_PREVENT_INHERITANCE_DOUBLE_DECLARATIONS_OF_CLASS_LIST_VARIABLES
#ifdef NLC_PREVENT_INHERITANCE_DOUBLE_DECLARATIONS_OF_CLASS_LIST_VARIABLES
	#define NLC_ENTITY_VECTOR_CONNECTION_TYPE_FUNCTIONS (14)	//added 1q9a //artificial entity connection representing attached functionLists (redundant if NLC_RECORD_ACTION_HISTORY:GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTIONS/actionLists is used)
#endif
//#define NLC_BAD_IMPLEMENTATION

//#define NLC_PRINT_EXPLICIT_LOCAL_CONTEXT
#ifdef NLC_PRINT_EXPLICIT_LOCAL_CONTEXT
	#define NLC_LOCAL_CONTEXT_NAME "locaL"
#endif

//#define NLC_DEBUG_PREPROCESSOR_PREMATURE_QUIT

//#define NLC_DEBUG_PARSE_CONTEXT4
//#define NLC_DEBUG_PARSE_CONTEXT3
//#define NLC_DEBUG_PARSE_CONTEXT2


//#define NLC_DEBUG_ADVANCED_REFERENCING_SUPPORT_ALIASES
//#define NLC_DEBUG_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
//#define NLC_DEBUG_PARSE_CONTEXT_CHILDREN
//#define NLC_DEBUG_PARSE_CONTEXT
//#define NLC_PREPROCESSOR_PRINT_OUTPUT
//#define NLC_DEBUG_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
//#define NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
//#define NLC_DEBUG_PREPROCESSOR_MATH_DETECT_AND_DECLARE_UNDECLARED_VARIABLES
//#define NLC_DEBUG_PREPROCESSOR_MATH_REPLACE_NUMERICAL_VARIABLES
//#define NLC_DEBUG_PREPROCESSOR_MATH
//#define NLC_DEBUG_PREPROCESSOR
//#define NLC_DEBUG_LOGICAL_CONDITION_CONJUNCTIONS
//#define NLC_DEBUG
//#define NLC_DEBUG_PRINT_HIDDEN_CLASSES


#endif
