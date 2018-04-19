/*******************************************************************************
 *
 * No License
 * 
 * This work is under exclusive copyright (c) Baxter AI (baxterai.com). 
 * Nobody else can use, copy, distribute, or modify this work without being 
 * at risk of take-downs, shake-downs, or litigation. 
 * 
 * By publishing this source code in a public repository on GitHub, Terms of 
 * Service have been accepted by which Baxter AI have allowed others to view 
 * and fork their repository.
 * 
 * If you find software that doesn't have a license, that generally means you 
 * have no permission from the creators of the software to use, modify, or 
 * share the software. Although a code host such as GitHub may allow you to 
 * view and fork the code, this does not imply that you are permitted to use, 
 * modify, or share the software for any purpose.
 *
 * This notice has been derived from https://choosealicense.com/no-permission 
 * (https://web.archive.org/web/20180312144938/https://choosealicense.com/no-permission)
 *
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: NLCmain.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2018 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler
 * Project Version: 2f2a 04-April-2018
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 * /
 *******************************************************************************/


#ifndef HEADER_NLC_MAIN
#define HEADER_NLC_MAIN

#include "NLCglobalDefs.hpp"
#include "NLCcodeBlockClass.hpp"
#include "NLCclassDefinitionClass.hpp"
#include "NLCtranslator.hpp"
#include "NLCprint.hpp"
#include "NLCprintClassDefinitions.hpp"
#include "NLCprintCodeBlocks.hpp"
#include "NLCpreprocessor.hpp"
#include "NLCtranslatorClassDefinitions.hpp"
#include "NLCprintDefs.hpp"	//required for NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION, setProgLang
#ifdef NLC_API
#include "NLCapi.hpp"
#endif
#include "NLCtranslatorCodeBlocksOperations.hpp"
#include "GIAmain.hpp"
#include "GIAdatabase.hpp"
#ifdef USE_WORDNET
#include "GIAwordnet.hpp"
#endif
#ifdef GIA_SEM_REL_TRANSLATOR
#include "GIAsemanticParserDatabase.hpp"
#endif
#include "GIAtranslatorOperations.hpp"
#include "XMLrulesClass.hpp"
#include "SHAREDvars.hpp"

int main(const int argc, const char** argv);

class NLCmainClass
{
	private: SHAREDvarsClass SHAREDvars;
	private: GIAentityNodeClassClass GIAentityNodeClass;
	private: GIAtranslatorOperationsClass GIAtranslatorOperations;
	private: NLCclassDefinitionClassClass NLCclassDefinitionClass;
	private: NLCtranslatorClass NLCtranslator;
	private: NLCtranslatorClassDefinitionsClass NLCtranslatorClassDefinitions;
	private: NLCcodeBlockClassClass NLCcodeBlockClass;
		private: string removeFileNameExtensions(string NLCfunctionName);
		#ifdef NLC_PREDEFINED_FUNCTION_NAME_FOR_NATURAL_LANGUAGE_CODE_WITHOUT_FUNCTION_SPECIFIED
		public: string removeNLCfileNameExtension(string NLCfunctionName);
		#endif
		#ifdef NLC_TRANSFORM_THE_ACTION_OF_POSSESSION_EG_HAVING_INTO_A_PROPERTY
		public: void transformTheActionOfPossessionEgHavingIntoAproperty(vector<GIAentityNode*>* entityNodesActiveListComplete);
		#endif
		#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS
		public: bool generateClassDefinitionFunctionDeclarationsAndReconcileArguments(const int numberOfInputFilesInList, vector<NLCclassDefinition*>* classDefinitionList, vector<vector<GIAentityNode*>*>* entityNodesActiveListCompleteFunctions, vector<NLCcodeblock*>* firstCodeBlockInTreeList);
		#endif
		#ifndef NLC_LIBRARY
		private: void printPredefinedNLCfunctions(NLCcodeblock* currentCodeBlockInTree);
		#endif
		
	public: bool executeNLC(

		NLCfunction* firstNLCfunctionInList,
		GIAtranslatorVariablesClass* translatorVariablesTemplate,
		
		string inputFolderLocal, 
		string outputFolderLocal,

		bool useInputTextPlainTXTFile,
		string inputTextPlainTXTfileName,
		#ifdef NLC_INPUT_FUNCTION_LISTS_EXPLICIT_FROM_DEDICATED_FILE
		bool useNLCinputFileList,
		string NLCinputFileListName,
		#endif
	
		string outputTextNLPrelationXMLfileName,
		string outputTextNLPfeatureXMLfileName,
		bool useOutputTextCFFFile,
		string outputTextCFFFileName,
		bool useOutputTextXMLFile,
		string outputTextXMLFileName,
		bool useOutputTextCXLFile,
		string outputTextCXLFileName,
		bool useOutputTextLDRFile,
		string outputTextLDRFileName,
		bool useOutputTextPPMFile,
		string outputTextPPMFileName,
		bool useOutputTextSVGFile,
		string outputTextSVGFileName,

		bool useOutputTextAllFile,
		string outputTextAllFileName,
		
		//#ifdef NLC_PREPROCESSOR
		bool useNLCpreprocessor,
		//#endif
		#ifdef NLC_API
		bool NLCapi,
		string APIsourceFolder,
		string APIclassListFileName,
		#endif
		
		bool printOutput,
		bool displayInOpenGLAndOutputScreenshot,

		int rasterImageWidth,
		int rasterImageHeight,

		#ifdef GIA_DATABASE
		bool readFromDatabase,
		bool writeToDatabase,
		bool useDatabase,
		string KBdatabaseFolderName,
		#endif
		#ifdef GIA_SEM_REL_TRANSLATOR
		string semanticParserDatabaseFolderName,
		#endif
		#ifdef GIA_PREPROCESSOR_POS_TAGGER_DATABASE_PERSISTENT
		string POStaggerDatabaseFolderName,
		#endif
		
		#ifdef GIA_PREPROCESSOR
		bool useLRP,
		bool useOutputLRPTextPlainTXTFile,
		string outputLRPTextPlainTXTFileName,
		string lrpDataFolderName,
		#endif

		#ifdef USE_WORDNET
		int synonymnDetectionStatus
		#endif
		);
	
	#ifdef USE_CS_WORKAROUND
	bool GIAmainClass::executeNLC2();
	#endif
};
	


#endif
