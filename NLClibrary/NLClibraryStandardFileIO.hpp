 /*******************************************************************************
 *
 * License: GNU Affero General Public License version 3 (AGPLv3)
 *
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: NLClibraryStandardFileIO.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2022 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 2p1a 05-June-2022
 * Requirements: requires C++ code to be generated by NLC
 *
 *******************************************************************************/
 
#ifndef HEADER_NLC_LIBRARY_STANDARD_FILEIO
#define HEADER_NLC_LIBRARY_STANDARD_FILEIO

#include "NLClibraryGenericEntityClass.hpp"
#include "XMLparserClass.hpp"

#define NLC_LIBRARY_FILEIO_XML_WRITE_LIST_TAGS		//verbose output (lower interoperability)
#define NLC_LIBRARY_FILEIO_XML_WRITE_LIST_TAGS_ENTRY	//verbose output (lower interoperability)

#define NLC_LIBRARY_FILEIO_FUNCTION_ACTIONOBJECT_FILE_NAME "file"
#define NLC_LIBRARY_FILEIO_FUNCTION_DEFAULT_FILE_NAME_PREPEND "NLCfileIO"
#define NLC_LIBRARY_FILEIO_FUNCTION_DEFAULT_FILE_NAME_APPEND_XML ".xml"
#define NLC_LIBRARY_FILEIO_FUNCTION_DEFAULT_FILE_NAME_APPEND_CSV ".csv"
#define NLC_LIBRARY_FILEIO_FUNCTION_DEFAULT_FILE_NAME_APPEND_TXT ".txt"
#define NLC_LIBRARY_FILEIO_FUNCTION_ACTION_CONDITION_FROM_NAME "from"
#define NLC_LIBRARY_FILEIO_FUNCTION_ACTION_CONDITION_TO_NAME "to"
#define NLC_LIBRARY_FILEIO_XML_ATTRIBUTENAME_CONDITION "condition"
#define NLC_LIBRARY_FILEIO_XML_ATTRIBUTENAME_LISTNAME "name"
#define NLC_LIBRARY_FILEIO_XML_ATTRIBUTENAME_MAPLISTNAME1 "conditionName"
#define NLC_LIBRARY_FILEIO_XML_ATTRIBUTENAME_MAPLISTNAME2 "conditionObjectName"
#define NLC_LIBRARY_FILEIO_XML_WRITE_PROPERTY_LISTS
#define NLC_LIBRARY_FILEIO_XML_WRITE_CONDITION_LISTS
//#define NLC_LIBRARY_FILEIO_XML_WRITE_ACTION_LISTS
//#ifdef NLC_LIBRARY_FILEIO_XML_WRITE_LIST_TAGS
	#define NLC_LIBRARY_FILEIO_XML_TAGNAME_PROPERTY_LIST_ALL "propertyLists"
	#define NLC_LIBRARY_FILEIO_XML_TAGNAME_CONDITION_LIST_ALL "conditionLists"
	#define NLC_LIBRARY_FILEIO_XML_TAGNAME_ACTION_LIST_ALL "actionLists"
	#define NLC_LIBRARY_FILEIO_XML_TAGNAME_ACTIONINCOMING_LIST_ALL "actionIncomingLists"
	#define NLC_LIBRARY_FILEIO_XML_TAGNAME_ACTIONOBJECT_LIST_ALL "actionObjectLists"
	#define NLC_LIBRARY_FILEIO_XML_TAGNAME_ACTIONSUBJECT_LIST_ALL "actionSubjectLists"	
	#define NLC_LIBRARY_FILEIO_XML_TAGNAME_PROPERTY_LIST "propertyList"
	#define NLC_LIBRARY_FILEIO_XML_TAGNAME_CONDITION_LIST "conditionList"
	#define NLC_LIBRARY_FILEIO_XML_TAGNAME_ACTION_LIST "actionList"
	#define NLC_LIBRARY_FILEIO_XML_TAGNAME_ACTIONINCOMING_LIST "actionIncomingList"
	#define NLC_LIBRARY_FILEIO_XML_TAGNAME_ACTIONOBJECT_LIST "actionObjectList"
	#define NLC_LIBRARY_FILEIO_XML_TAGNAME_ACTIONSUBJECT_LIST "actionSubjectList"
//#endif
#define NLC_LIBRARY_FILEIO_FILETYPE_XML (1)	//xml file
#define NLC_LIBRARY_FILEIO_FILETYPE_FLAT (2)	//flat file (text/csv file)
#define NLC_LIBRARY_FILEIO_FILETYPE_DEFAULT (NLC_LIBRARY_FILEIO_FILETYPE_XML)
#define NLC_LIBRARY_GENERATE_OBJECT_BY_NAME_FUNCTION_NAME "generateObjectByName"	
#define NLC_LIBRARY_FILEIO_FLAT_DELIMITER_COMMA ","
#define NLC_LIBRARY_FILEIO_FLAT_DELIMITER_TAB "\t"
#define NLC_LIBRARY_FILEIO_FLAT_DELIMITER_DEFAULT (NLC_LIBRARY_FILEIO_FLAT_DELIMITER_TAB)
#define NLC_LIBRARY_FILEIO_FLAT_NUMBER_OF_DELIMITERS (2)
static string nlcLibraryFileIOflatFileDelimiters[NLC_LIBRARY_FILEIO_FLAT_NUMBER_OF_DELIMITERS] = {NLC_LIBRARY_FILEIO_FLAT_DELIMITER_COMMA, NLC_LIBRARY_FILEIO_FLAT_DELIMITER_TAB};
#define NLC_LIBRARY_FILEIO_FLAT_NUMBER_OF_NUMERICAL_CHARACTERS (10)
static char nlcLibraryFileIOflatFileNumericalCharacters[NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_NUMERICAL_CHARACTERS_NUMBER_OF_TYPES] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
#define NLC_LIBRARY_FILEIO_FLAT_NUMBER_OF_ALPHABETIC_CHARACTERS (53)
static char nlcLibraryFileIOflatFileAlphabeticCharacters[NLC_LIBRARY_FILEIO_FLAT_NUMBER_OF_ALPHABETIC_CHARACTERS] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '_'};
#define NLC_ALLOW_ALPHANUMERIC_CLASS_NAMES
#define NLC_LIBRARY_FILEIO_FLAT_NULL_PROPERTY_VALUE "false"
#define NLC_LIBRARY_FILEIO_FLAT_PRESENT_PROPERTY_VALUE "true"

//writeFunction() limitation: only supports NLC_ADVANCED_REFERENCING
void writeFunction(vector<NLCgenericEntityClass*>& writeClassList, vector<NLCgenericEntityClass*>& writeObjectClassList);
	void writeXMLfilePropertyListEntry(XMLparserTag* firstTagInList, vector<NLCgenericEntityClass*>* writeObjectClassList);
		//#ifdef NLC_LIBRARY_FILEIO_XML_WRITE_PROPERTY_LISTS
		void writeXMLfilePropertyListRecurse(XMLparserTag* firstTagInList, vector<NLCgenericEntityClass*>* writeObjectClassList);
			void writeXMLfileVectorList(XMLparserTag* firstTagInList, vector<NLCgenericEntityClass*>* writeObjectClassList, string listName);
				XMLparserTag* createVectorListTagWithLowerLevel(XMLparserTag* currentTagInList, string tagName, vector<NLCgenericEntityClass*>* vectorClassList);
		//#endif
		#ifdef NLC_LIBRARY_FILEIO_XML_WRITE_CONDITION_LISTS
		void writeXMLfileConditionListRecurse(XMLparserTag* firstTagInList, unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>* writeObjectClassMapList);
			void writeXMLfileMapList(XMLparserTag* firstTagInList, unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>* writeObjectClassMapList, string listName);
				XMLparserTag* createMapListTagWithLowerLevel(XMLparserTag* currentTagInList, string tagName, unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>* writeObjectClassMapList);
		#endif
		#ifdef NLC_LIBRARY_FILEIO_XML_WRITE_ACTION_LISTS
		void writeXMLfileActionListRecurse(XMLparserTag* firstTagInList, vector<NLCgenericEntityClass*>* writeObjectClassList);
		void writeXMLfileActionIncomingListRecurse(XMLparserTag* firstTagInList, vector<NLCgenericEntityClass*>* writeObjectClassList);
		void writeXMLfileActionSubjectListRecurse(XMLparserTag* firstTagInList, vector<NLCgenericEntityClass*>* writeObjectClassList);
		void writeXMLfileActionObjectListRecurse(XMLparserTag* firstTagInList, vector<NLCgenericEntityClass*>* writeObjectClassList);
		#endif
		XMLparserTag* writeXMLfileObject(XMLparserTag* firstTagInList, NLCgenericEntityClass* writeObject);
			XMLparserTag* createListTagWithLowerLevel(XMLparserTag* currentTagInList, string tagName);

void readFunction(vector<NLCgenericEntityClass*>& readClassList, vector<NLCgenericEntityClass*>& readObjectClassList);
	string getTopLevelPropertyListNameFromXMLreadFileContents(XMLparserTag* firstTagInXMLFile);
	bool readXMLfileToNLCpropertyListsEntry(XMLparserTag* firstTagInList, vector<NLCgenericEntityClass*>* readObjectClassList);
		//#ifdef NLC_LIBRARY_FILEIO_XML_WRITE_PROPERTY_LISTS
		bool readXMLfilePropertyListRecurse(XMLparserTag* firstTagInList, vector<NLCgenericEntityClass*>* readObjectClassList);
			bool readXMLfileVectorList(XMLparserTag* firstTagInList, vector<NLCgenericEntityClass*>* readObjectClassList, string listName);
		//#endif
		#ifdef NLC_LIBRARY_FILEIO_XML_WRITE_CONDITION_LISTS
		bool readXMLfileConditionListRecurse(XMLparserTag* firstTagInList, unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>* readObjectClassMapList);
			bool readXMLfileMapList(XMLparserTag* firstTagInList, unordered_map<NLCgenericEntityClass*, NLCgenericEntityClass*>* readObjectClassMapList, string listName);
		#endif
		#ifdef NLC_LIBRARY_FILEIO_XML_WRITE_ACTION_LISTS
		void readXMLfileActionListRecurse(XMLparserTag* firstTagInList, vector<NLCgenericEntityClass*>* readObjectClassList);
		void readXMLfileActionIncomingListRecurse(XMLparserTag* firstTagInList, vector<NLCgenericEntityClass*>* readObjectClassList);
		void readXMLfileActionSubjectListRecurse(XMLparserTag* firstTagInList, vector<NLCgenericEntityClass*>* readObjectClassList);
		void readXMLfileActionObjectListRecurse(XMLparserTag* firstTagInList, vector<NLCgenericEntityClass*>* readObjectClassList);
		#endif
		void readXMLfileObject(XMLparserTag* firstTagInList, NLCgenericEntityClass* readObject);
			bool readFileObjectVectorListAll(XMLparserTag* currentTagInList, NLCgenericEntityClass* readObject, string vectorListAllTagName, string vectorListTagName);
			#ifdef NLC_LIBRARY_FILEIO_XML_WRITE_CONDITION_LISTS
			bool readFileObjectMapListAll(XMLparserTag* currentTagInList, NLCgenericEntityClass* readObject, string vectorListAllTagName, string vectorListTagName);
			#endif

bool writeNLCflatFilePropertyLists(string fileName, vector<NLCgenericEntityClass*>* writeObjectClassList, string delimiter);
bool readNLCflatfilePropertyLists(string fileName, vector<NLCgenericEntityClass*>* readObjectClassList, string delimiter, string parentObjectName);

bool variableNameIsAcceptableNLCclassName(string currentVariableName);	
	bool stringContainsNumbers(string s);		
	bool stringContainsAlphabetic(string s);

#endif

