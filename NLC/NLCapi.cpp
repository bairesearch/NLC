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
 * File Name: NLCapi.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2016 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 1v7a 22-October-2016
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/


#include "NLCapi.h"
#include "NLCtranslatorClassDefinitions.h"
#include "NLCprintClassDefinitions.h"
#include "NLCprintDefs.h"
#include "NLCprintCodeBlocksFunctions.h"

#ifdef NLC_API
bool parseDoxygenClassXMLfile(string APIclassName, string APIsourceFolder, vector<NLCclassDefinition*>* classDefinitionList, int progLang)
{
	bool result = true;

	string doxygenXMLclassFileName = string(DOXYGEN_XML_CLASS_FILE_NAME_PREPEND) + APIclassName + DOXYGEN_XML_CLASS_FILE_NAME_EXTENSION;
	string doxygenXMLclassFileNameFullPath =  APIsourceFolder + DOXYGEN_XML_OUTPUT_FOLDER + doxygenXMLclassFileName;

 	XMLparserTag* firstTagInXMLFile = new XMLparserTag();

	cout << "doxygenXMLclassFileNameFullPath = " << doxygenXMLclassFileNameFullPath << endl;

 	if(!readXMLfile(doxygenXMLclassFileNameFullPath, firstTagInXMLFile))
 	{
		result = false;
	}

	XMLparserTag* currentTagUpdatedL1 = firstTagInXMLFile;

	if(currentTagUpdatedL1->name == NET_XML_TAG_doxygen)
	{
	}
	else
	{
		cout << "parseDoxygenClassXMLfile error: " << NET_XML_TAG_doxygen << " tag not detected";
		result = false;
	}

	if(result)
	{
		XMLparserTag* currentTagUpdatedL2 = currentTagUpdatedL1->firstLowerLevelTag;
		if(currentTagUpdatedL2->name == NET_XML_TAG_compounddef)
		{
			XMLparserTag* currentTagUpdatedL3 = currentTagUpdatedL2->firstLowerLevelTag;
			if(currentTagUpdatedL3->name == NET_XML_TAG_compoundname)	//always expect first tag in NET_XML_TAG_compounddef to be NET_XML_TAG_compoundname
			{
				if(currentTagUpdatedL3->value != APIclassName)
				{
					cout << "parseDoxygenClassXMLfile{} error: (NET_XML_TAG_compoundname value != doxygenXMLclassFileName)" << endl;
					result = false;
				}
				currentTagUpdatedL3 = currentTagUpdatedL3->nextTag;
			}
			else
			{
				cout << "parseDoxygenClassXMLfile error: " << NET_XML_TAG_compoundname << " tag not detected";
				result = false;
			}

			if(result)
			{
				string className = generateClassName(APIclassName);
				NLCclassDefinition* classDefinition = NULL;
				if(addClassDefinitionToList(classDefinitionList, className, &classDefinition))
				{//this should always be true considering APIclassNames should be unique

					string APIsourceHeaderFileName = "";
					#ifdef NLC_API_SEPARATE_FILE_FOR_WRAPPER_FUNCTIONS
					string printedClassDefinitionHeaderFileName = generateCodeClassDefinitionHeaderFileName(classDefinition->name);	//eg "NLCgeneratedInterfaceXClass.hpp"
					string printedClassDefinitionSourceFileName = generateCodeClassDefinitionSourceFileName(classDefinition->name);	//eg "NLCgeneratedInterfaceXClass.cpp"
					#endif
					string APIwrapperSourceWrapObjectFunctionHeaderText = generateAPIwrapperSourceWrapOrUnwrapObjectFunctionHeaderText(NLC_API_THIRD_PARTY_API_OBJECT_WRAP_FUNCTION_NAME, APIclassName, progLang);	//wrapThirdPartyAPIobject[APIclassName](APIclassName* thirdpartyAPIobject)
					string APIwrapperSourceUnwrapObjectFunctionHeaderText = generateAPIwrapperSourceWrapOrUnwrapObjectFunctionHeaderText(NLC_API_THIRD_PARTY_API_OBJECT_UNWRAP_FUNCTION_NAME, APIclassName, progLang);	//unwrapThirdPartyAPIobject[APIclassName](APIclassName* thirdpartyAPIobject)
					string APIwrapperSourceWrapObjectFunctionText = progLangClassMemberFunctionTypeDefault[progLang] + classDefinition->name + progLangFunctionOwnerClassDelimiter[progLang] + APIwrapperSourceWrapObjectFunctionHeaderText + CHAR_NEWLINE + progLangOpenBlock[progLang] + CHAR_NEWLINE;		//void APIclassNameClass::wrapThirdPartyAPIobject[APIclassName](APIclassName* thirdpartyAPIobject){
					string APIwrapperSourceUnwrapObjectFunctionText = progLangClassMemberFunctionTypeDefault[progLang] + classDefinition->name + progLangFunctionOwnerClassDelimiter[progLang] + APIwrapperSourceUnwrapObjectFunctionHeaderText + CHAR_NEWLINE + progLangOpenBlock[progLang] + CHAR_NEWLINE;	//void APIclassNameClass::unwrapThirdPartyAPIobject[APIclassName](APIclassName* thirdpartyAPIobject){
					string APIwrapperSourceWrapFunctionFunctionsText = "";
					string APIwrapperHeaderWrapFunctionFunctionsText = "";
					string APIwrapperSourceText = "";
					string APIwrapperHeaderText = "";
					#ifdef NLC_API_SEPARATE_FILE_FOR_WRAPPER_FUNCTIONS
					APIwrapperSourceText = APIwrapperSourceText + generateCodeHashIncludeReference(printedClassDefinitionHeaderFileName, progLang);	//eg #include "NLCgeneratedInterfaceXClass.hpp";
					#endif

					#ifdef NLC_DEBUG_API
					cout << "APIclassName = " << APIclassName << endl;
					#endif

					while(currentTagUpdatedL3->nextTag != NULL)
					{
						if(currentTagUpdatedL3->name == NET_XML_TAG_includes)
						{
							APIsourceHeaderFileName = currentTagUpdatedL3->value;
							#ifdef NLC_DEBUG_API
							cout << "NET_XML_TAG_includes found, APIsourceHeaderFileName = " << APIsourceHeaderFileName << endl;
							#endif
						}
						if(currentTagUpdatedL3->name == NET_XML_TAG_basecompoundref)
						{
							string APIclassParentName = currentTagUpdatedL3->value;	//TODO support template classes eg "QIntDict&lt; char &gt;" (QIntDict<char>)
							#ifdef NLC_DEBUG_API
							cout << "NET_XML_TAG_basecompoundref found, APIclassParentName = " << APIclassParentName << endl;
							#endif
							NLCclassDefinition* parentClassDefinition = NULL;
							if(addClassDefinitionToList(classDefinitionList, APIclassParentName, &parentClassDefinition))
							{
								parentClassDefinition->APIwrapperSourceText = new string("");	//do not add any wrapper code (only if this class is specifically defined by the API will this text be added)
								parentClassDefinition->APIwrapperHeaderText = new string("");	//do not add any wrapper code (only if this class is specifically defined by the API will this text be added)
								addDefinitionToClassDefinition(classDefinition, parentClassDefinition);
							}
						}
						if(currentTagUpdatedL3->name == NET_XML_TAG_sectiondef)
						{
							#ifdef NLC_DEBUG_API
							cout << "NET_XML_TAG_sectiondef found" << endl;
							#endif

							string sectionType = "";
							if(getAttribute(currentTagUpdatedL3, NET_XML_ATTRIBUTE_kind, &sectionType))
							{
								if(sectionType == NET_XML_TAG_sectiondef_ATTRIBUTE_kind_VALUE_privateattrib || sectionType == NET_XML_TAG_sectiondef_ATTRIBUTE_kind_VALUE_publicattrib || sectionType == NET_XML_TAG_sectiondef_ATTRIBUTE_kind_VALUE_protectedattrib)
								{
									generatePropertyClassLists(currentTagUpdatedL3, classDefinitionList, classDefinition, APIclassName, &APIwrapperSourceWrapObjectFunctionText, &APIwrapperSourceUnwrapObjectFunctionText, progLang);
								}
								else if(sectionType == NET_XML_TAG_sectiondef_ATTRIBUTE_kind_VALUE_privatefunc || sectionType == NET_XML_TAG_sectiondef_ATTRIBUTE_kind_VALUE_publicfunc || sectionType == NET_XML_TAG_sectiondef_ATTRIBUTE_kind_VALUE_protectedfunc)
								{
									generateFunctionClassLists(currentTagUpdatedL3, classDefinitionList, classDefinition, APIclassName, &APIwrapperSourceWrapFunctionFunctionsText, &APIwrapperHeaderWrapFunctionFunctionsText, progLang);
								}
							}
						}

						currentTagUpdatedL3 = currentTagUpdatedL3->nextTag;
					}

					APIwrapperSourceWrapObjectFunctionText = APIwrapperSourceWrapObjectFunctionText + progLangCloseBlock[progLang] + CHAR_NEWLINE + CHAR_NEWLINE;
					APIwrapperSourceUnwrapObjectFunctionText = APIwrapperSourceUnwrapObjectFunctionText + progLangCloseBlock[progLang] + CHAR_NEWLINE + CHAR_NEWLINE;
					APIwrapperSourceText = APIwrapperSourceText + APIwrapperSourceWrapObjectFunctionText;
					APIwrapperSourceText = APIwrapperSourceText + APIwrapperSourceUnwrapObjectFunctionText;
					APIwrapperSourceText = APIwrapperSourceText + APIwrapperSourceWrapFunctionFunctionsText;

					string APIsourceFileFullPath = APIsourceFolder + APIsourceHeaderFileName;
					printLine(progLangClassMemberFunctionTypeDefault[progLang] + APIwrapperSourceWrapObjectFunctionHeaderText + progLangEndLine[progLang], 1, &APIwrapperHeaderText);	//void wrapThirdPartyAPIobject(APIclassName* thirdpartyAPIobject);
					printLine(progLangClassMemberFunctionTypeDefault[progLang] + APIwrapperSourceUnwrapObjectFunctionHeaderText + progLangEndLine[progLang], 1, &APIwrapperHeaderText);	//void unwrapThirdPartyAPIobject(APIclassName* thirdpartyAPIobject);
					APIwrapperHeaderText = APIwrapperHeaderText + APIwrapperHeaderWrapFunctionFunctionsText;

					#ifdef NLC_API_SEPARATE_FILE_FOR_WRAPPER_FUNCTIONS
					string printedClassDefinitionAPIwrapperHeaderFileName = string(NLC_API_SEPARATE_FILE_FOR_WRAPPER_FUNCTIONS_NAME_PREPEND) + className + NLC_USE_LIBRARY_GENERATE_INDIVIDUAL_FILES_EXTENSION_HPP;	//NLCgeneratedInterfaceXClass.hpp
					string printedClassDefinitionAPIwrapperSourceFileName = string(NLC_API_SEPARATE_FILE_FOR_WRAPPER_FUNCTIONS_NAME_PREPEND) + className + NLC_USE_LIBRARY_GENERATE_INDIVIDUAL_FILES_EXTENSION_CPP;	//NLCgeneratedInterfaceXClass.cpp
					writeStringToFile(printedClassDefinitionAPIwrapperSourceFileName, &APIwrapperSourceText);
					writeStringToFile(printedClassDefinitionAPIwrapperHeaderFileName, &APIwrapperHeaderText);
					#else
					classDefinition->APIclass = true;
					classDefinition->APIsourceFileFullPath = APIsourceFileFullPath;
					cout << "className = " << className << endl;
					cout << "APIwrapperSourceText = " << APIwrapperSourceText << endl;
					cout << "APIwrapperHeaderText = " << APIwrapperHeaderText << endl;
					classDefinition->APIwrapperSourceText = new string(APIwrapperSourceText);
					classDefinition->APIwrapperHeaderText = new string(APIwrapperHeaderText);
					#endif
				}
			}
		}
		else
		{
			cout << "parseDoxygenClassXMLfile error: " << NET_XML_TAG_compounddef << " tag not detected";
			result = false;
		}
	}
	return result;
}

void generatePropertyClassLists(XMLparserTag* currentTagUpdated, vector<NLCclassDefinition*>* classDefinitionList, NLCclassDefinition* classDefinition, string APIclassName, string* APIwrapperSourceWrapObjectFunctionText, string* APIwrapperSourceUnwrapObjectFunctionText, int progLang)
{
	XMLparserTag* currentTagUpdatedL2 = currentTagUpdated->firstLowerLevelTag;
	while(currentTagUpdatedL2->nextTag != NULL)
	{
		if(currentTagUpdatedL2->name == NET_XML_TAG_memberdef)	//eg <memberdef kind="variable" id="classMemberGroup_1a74b619b49dc3e68d42a365267172a0ea" prot="private" static="no" mutable="no">
		{
			string memberType = "";
			if(getAttribute(currentTagUpdatedL2, NET_XML_ATTRIBUTE_kind, &memberType))
			{
				if(memberType == NET_XML_TAG_memberdef_ATTRIBUTE_kind_VALUE_variable)
				{
					string variableName = "";
					string variableType = "";
					XMLparserTag* currentTagUpdatedL3 = currentTagUpdatedL2->firstLowerLevelTag;
					while(currentTagUpdatedL3->nextTag != NULL)
					{
						if(currentTagUpdatedL3->name == NET_XML_TAG_name)	//eg <name>memberList</name>
						{
							variableName = currentTagUpdatedL3->value;
							#ifdef NLC_DEBUG_API
							cout << "variableName = " << variableName << endl;
							#endif
						}
						if(currentTagUpdatedL3->name == NET_XML_TAG_type)	//eg <type><ref refid="classMemberList" kindref="compound">MemberList</ref> *</type>
						{
							variableType = getType(currentTagUpdatedL3);
							#ifdef NLC_DEBUG_API
							cout << "variableType = " << variableType << endl;
							#endif
						}

						currentTagUpdatedL3 = currentTagUpdatedL3->nextTag;
					}

					string variableType1 = "";
					string variableType1ClassName = "";
					string variableType2 = "";
					bool variableTypeList = false;
					bool variableTypeStandard = false;
					int mathtextVariableType = NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_UNKNOWN;
					detectVariableTypeDetails(classDefinitionList, classDefinition, variableName, variableType, &variableType1, &variableType1ClassName, &variableType2, &variableTypeList, &variableTypeStandard, &mathtextVariableType);

					int level = 1;
					generateCodeWrapObject(variableName, variableType1ClassName, APIclassName, variableTypeList, variableTypeStandard, mathtextVariableType, level, APIwrapperSourceWrapObjectFunctionText, progLang);
					generateCodeUnwrapObject(variableName, variableType1ClassName, variableType1, variableTypeList, variableTypeStandard, mathtextVariableType, level, APIwrapperSourceUnwrapObjectFunctionText, progLang, false);
				}
			}
		}
		currentTagUpdatedL2 = currentTagUpdatedL2->nextTag;
	}
}

void generateFunctionClassLists(XMLparserTag* currentTagUpdated, vector<NLCclassDefinition*>* classDefinitionList, NLCclassDefinition* classDefinition, string APIclassName, string* APIwrapperSourceWrapFunctionFunctionsText, string* APIwrapperHeaderWrapFunctionFunctionsText, int progLang)
{
	XMLparserTag* currentTagUpdatedL2 = currentTagUpdated->firstLowerLevelTag;
	while(currentTagUpdatedL2->nextTag != NULL)
	{
		if(currentTagUpdatedL2->name == NET_XML_TAG_memberdef)	//eg  <memberdef kind="function" id="classMemberGroup_1a544526a0c59d95f8ce1af3b44d252861" prot="public" static="no" const="no" explicit="no" inline="no" virt="non-virtual">
		{
			string memberType = "";
			if(getAttribute(currentTagUpdatedL2, NET_XML_ATTRIBUTE_kind, &memberType))
			{
				if(memberType == NET_XML_TAG_memberdef_ATTRIBUTE_kind_VALUE_function)
				{
					string functionName = "";
					string functionType = "";
					vector<NLCvariable*> functionParameters;
					XMLparserTag* currentTagUpdatedL3 = currentTagUpdatedL2->firstLowerLevelTag;
					while(currentTagUpdatedL3->nextTag != NULL)
					{
						if(currentTagUpdatedL3->name == NET_XML_TAG_name)
						{
							functionName = currentTagUpdatedL3->value;	//eg <name>setInGroup</name>
							#ifdef NLC_DEBUG_API
							cout << "functionName = " << functionName << endl;
							#endif
						}
						else if(currentTagUpdatedL3->name == NET_XML_TAG_type)
						{
							functionType = getType(currentTagUpdatedL3);	//eg <type>void</type>
							#ifdef NLC_DEBUG_API
							cout << "functionType = " << functionType << endl;
							#endif
						}
						else if(currentTagUpdatedL3->name == NET_XML_TAG_param)
						{
							#ifdef NLC_DEBUG_API
							cout << "param = " << endl;
							#endif
							NLCvariable* param = new NLCvariable();
							functionParameters.push_back(param);
							XMLparserTag* currentTagUpdatedL4 = currentTagUpdatedL3->firstLowerLevelTag;
							while(currentTagUpdatedL4->nextTag != NULL)
							{
								if(currentTagUpdatedL4->name == NET_XML_TAG_declname)
								{
									param->name = currentTagUpdatedL4->value;	//eg <declname>parameterName</declname>
									#ifdef NLC_DEBUG_API
									cout << "param->name = " << param->name << endl;
									#endif
								}
								else if(currentTagUpdatedL4->name == NET_XML_TAG_type)	//eg <type><ref refid="classClassDef" kindref="compound">parameterType</ref> *</type> / <type>bool</type>
								{
									param->typeString = getType(currentTagUpdatedL4);
									#ifdef NLC_DEBUG_API
									cout << "param->typeString = " << param->typeString << endl;
									#endif
								}
								currentTagUpdatedL4 = currentTagUpdatedL4->nextTag;
							}
						}

						currentTagUpdatedL3 = currentTagUpdatedL3->nextTag;
					}

					string APIclassNameDestructor = progLangClassDestructorPrepend[progLang] + APIclassName;
					if((functionName != APIclassName) && (functionName != APIclassNameDestructor))
					{//ignore constructors/destructors

						string argumentText = "";
						for(vector<NLCvariable*>::iterator parametersIterator = functionParameters.begin(); parametersIterator < functionParameters.end(); parametersIterator++)
						{
							NLCvariable* currentParam = *parametersIterator;
							string variableName = currentParam->name;
							string variableType = currentParam->typeString;

							string variableType1 = variableName;
							string variableType1ClassName = generateClassName(variableType1);
							string variableType1InstanceName = generateInstanceNameArbitrary(variableType1);
							string variableType1LocalListName = generateLocalListName(variableType1ClassName, variableType1InstanceName);
							argumentText = argumentText + generateDefinitionText(generateCodeEntityListDefinitionTypeTextReferenceCompact(variableType1ClassName, progLang), variableType1LocalListName);		//vector<param1className*>& param1LocalList
						}
						string APIwrapperSourceWrapFunctionFunctionHeaderText = generateAPIwrapperSourceWrapFunctionFunctionHeaderText(NLC_API_THIRD_PARTY_API_FUNCTION_WRAP_FUNCTION_NAME + functionName, APIclassName, argumentText, progLang);	//wrapThirdPartyAPIfunction[functionName](vector<param1className*>& param1LocalList, vector<param2className*>& param2LocalList, etc)
						*APIwrapperSourceWrapFunctionFunctionsText = *APIwrapperSourceWrapFunctionFunctionsText + progLangClassMemberFunctionTypeDefault[progLang] + classDefinition->name + progLangFunctionOwnerClassDelimiter[progLang] + APIwrapperSourceWrapFunctionFunctionHeaderText + CHAR_NEWLINE + progLangOpenBlock[progLang] + CHAR_NEWLINE;	//void APIclassNameClass::wrapThirdPartyAPIfunction[functionName](vector<param1className*>& param1LocalList, vector<param2className*>& param2LocalList, etc){
						printLine(progLangClassMemberFunctionTypeDefault[progLang] + APIwrapperSourceWrapFunctionFunctionHeaderText + progLangEndLine[progLang], 1, APIwrapperHeaderWrapFunctionFunctionsText);		//void wrapThirdPartyAPIfunction[APIclassName](vector<param1className*>& param1LocalList, vector<param2className*>& param2LocalList, etc);

						string executeFunctionText = functionName + progLangClassMemberFunctionParametersOpen[progLang];
						bool firstParameter = true;
						int level = 1;
						for(vector<NLCvariable*>::iterator parametersIterator = functionParameters.begin(); parametersIterator < functionParameters.end(); parametersIterator++)
						{
							NLCvariable* currentParam = *parametersIterator;
							string variableName = currentParam->name;
							string variableType = currentParam->typeString;

							string variableType1 = "";
							string variableType1ClassName = "";
							string variableType2 = "";
							bool variableTypeList = false;
							bool variableTypeStandard = false;
							int mathtextVariableType = NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_UNKNOWN;
							detectVariableTypeDetails(classDefinitionList, classDefinition, variableName, variableType, &variableType1, &variableType1ClassName, &variableType2, &variableTypeList, &variableTypeStandard, &mathtextVariableType);

							string createNewEntityText = generateCodeNewEntity(variableType, variableName, progLang);	//variableType variableName = new variableType();
							printLine(createNewEntityText, level, APIwrapperSourceWrapFunctionFunctionsText);

							generateCodeUnwrapObject(variableName, variableType1ClassName, variableType1, variableTypeList, variableTypeStandard, mathtextVariableType, level, APIwrapperSourceWrapFunctionFunctionsText, progLang, true);

							if(firstParameter)
							{
								firstParameter = false;
							}
							else
							{
								executeFunctionText = executeFunctionText + progLangParameterSpaceNextParam[progLang];
							}
							string APIobjectVariableReferenceName = generateCodeReferenceText(NLC_API_THIRD_PARTY_API_OBJECT_VARIABLE_NAME, variableName, progLang);
							executeFunctionText = executeFunctionText + variableName;
						}
						executeFunctionText = executeFunctionText + progLangClassMemberFunctionParametersClose[progLang] + progLangEndLine[progLang];
						printLine(executeFunctionText, level, APIwrapperSourceWrapFunctionFunctionsText);

						*APIwrapperSourceWrapFunctionFunctionsText = *APIwrapperSourceWrapFunctionFunctionsText + progLangCloseBlock[progLang] + CHAR_NEWLINE + CHAR_NEWLINE;
					}
				}
			}
		}
		currentTagUpdatedL2 = currentTagUpdatedL2->nextTag;
	}
}

string getType(XMLparserTag* typeTag)
{
	string typeString = "";
	bool foundRefTag = false;
	string refValue = "";
	if(typeTag->firstLowerLevelTag != NULL)
	{
		XMLparserTag* typeTagL2 = typeTag->firstLowerLevelTag;
		while(typeTagL2->nextTag != NULL)
		{
			if(typeTagL2->name == NET_XML_TAG_ref)	//eg <type><ref refid="classClassDef" kindref="compound">parameterType</ref> *</type> / <type>bool</type>
			{
				refValue = typeTagL2->value;
				foundRefTag = true;
			}
			typeTagL2 = typeTagL2->nextTag;
		}
	}
	if(foundRefTag)
	{
		typeString = refValue + typeTag->value;	//eg parameterType *
	}
	else
	{
		typeString = typeTag->value;	//eg bool
	}
	return typeString;
}

void detectVariableTypeDetails(vector<NLCclassDefinition*>* classDefinitionList, NLCclassDefinition* classDefinition, string variableName, string variableType, string* variableType1, string* variableType1ClassName, string* variableType2, bool* variableTypeList, bool* variableTypeStandard, int* mathtextVariableType)
{
	string targetClassName = "";
	string variableTypeFinal = "";
	int variableTypeStandardType = NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_UNKNOWN;
	bool createSecondLayer = false;

	*variableType1 = variableName;
	*variableType1ClassName = generateClassName(*variableType1);
	targetClassName = *variableType1ClassName;
	NLCclassDefinition* targetClassDefinition = NULL;
	if(addClassDefinitionToList(classDefinitionList, targetClassName, &targetClassDefinition))
	{
		targetClassDefinition->APIwrapperSourceText = new string("");	//do not add any wrapper code (only if this class is specifically defined by the API will this text be added)
		targetClassDefinition->APIwrapperHeaderText = new string("");	//do not add any wrapper code (only if this class is specifically defined by the API will this text be added)
	}
	addPropertyListToClassDefinition(classDefinition, targetClassDefinition);

	if(variableTypeIsList(variableType, variableType2))
	{
		//eg "vector<customClass*> listVariable;" / "vector<int> listVariable;"
		createSecondLayer = true;
		variableTypeFinal = *variableType2;
	}
	else
	{
		//eg "int variable;" / "customClass variable;"
		variableTypeFinal = variableType;
	}
	if(variableTypeIsStandard(variableTypeFinal, &variableTypeStandardType))
	{
		//eg  "int variable;" / "vector<int> listVariable;"
		*variableTypeStandard = true;
		*mathtextVariableType = APIvariableTypeStandardMathObjectTypes[variableTypeStandardType];
	}
	else
	{
		//eg "customClass variable;" / "vector<customClass*> listVariable"
		createSecondLayer = true;
		*variableType2 = variableTypeFinal;	//OLD: variableType
	}

	if(createSecondLayer)
	{
		string targetClassName2 = generateClassName(*variableType2);
		NLCclassDefinition* targetClassDefinition2 = NULL;
		if(addClassDefinitionToList(classDefinitionList, targetClassName2, &targetClassDefinition2))
		{
			targetClassDefinition2->APIwrapperSourceText = new string("");	//do not add any wrapper code (only if this class is specifically defined by the API will this text be added)
			targetClassDefinition2->APIwrapperHeaderText = new string("");	//do not add any wrapper code (only if this class is specifically defined by the API will this text be added)
		}
		addPropertyListToClassDefinition(targetClassDefinition, targetClassDefinition2);
	}
}

void generateCodeWrapObject(string variableName, string variableType1ClassName, string APIclassName, bool variableTypeList, bool variableTypeStandard, int mathtextVariableType, int level, string* APIwrapperSourceWrapObjectFunctionText, int progLang)
{
	string APIclassInstanceName = generateInstanceNameArbitrary(APIclassName);

	if(variableTypeList)
	{
		generateCodeForEntityList(APIclassName, variableName, APIclassInstanceName, progLang, APIwrapperSourceWrapObjectFunctionText, level);	//for(vector<APIclassName*>::iterator iter = variableName->begin(); iter < variableName->end(); iter++) { APIclassName* APIclassInstanceName = *iter;
		string intermediaryVariableInstanceName = "intermediaryVariable";
		string createNewEntityText = generateCodeNewEntity(variableType1ClassName, intermediaryVariableInstanceName, progLang);	//variableType1ClassName intermediaryVariableInstanceName = new variableType1ClassName();
		printLine(createNewEntityText, level+1, APIwrapperSourceWrapObjectFunctionText);
		if(variableTypeStandard)
		{
			//untested
			string mathtextVariableReferenceName = generateCodeEntityMathObjectValueText(intermediaryVariableInstanceName, mathtextVariableType, progLang);
			string setText = generateCodeSetText(mathtextVariableReferenceName, APIclassInstanceName, progLang);	// intermediaryVariableInstanceName->variableNumerical[/String] = APIclassInstanceName;
			printLine(setText, level+1, APIwrapperSourceWrapObjectFunctionText);
		}
		else
		{
			//untested
			string thirdpartyAPIobjectReferenceName = generateCodeReferenceText(intermediaryVariableInstanceName, NLC_API_THIRD_PARTY_API_OBJECT_VARIABLE_NAME, progLang);
			string setText = generateCodeSetText(thirdpartyAPIobjectReferenceName, APIclassInstanceName, progLang);	// intermediaryVariableInstanceName->thirdpartyAPIobject = APIclassInstanceName;
			printLine(setText, level+1, APIwrapperSourceWrapObjectFunctionText);
		}
		generateCodeAddEntityToList(intermediaryVariableInstanceName, generatePropertyListName(variableType1ClassName), progLang, APIwrapperSourceWrapObjectFunctionText, level+1);	//variableType1PropertyList.push_back(intermediaryVariableInstanceName);
		printLine(progLangCloseBlock[progLang], level, APIwrapperSourceWrapObjectFunctionText);
	}
	else
	{
		string intermediaryVariableInstanceName = "intermediaryVariable";
		string createNewEntityText = generateCodeNewEntity(variableType1ClassName, intermediaryVariableInstanceName, progLang);	//variableType1ClassName intermediaryVariableInstanceName = new variableType1ClassName();
		printLine(createNewEntityText, level, APIwrapperSourceWrapObjectFunctionText);
		if(variableTypeStandard)
		{
			//tested
			string mathtextVariableReferenceName = generateCodeEntityMathObjectValueText(intermediaryVariableInstanceName, mathtextVariableType, progLang);
			string APIobjectVariableReferenceName = generateCodeReferenceText(NLC_API_THIRD_PARTY_API_OBJECT_VARIABLE_NAME, variableName, progLang);
			string setText = generateCodeSetText(mathtextVariableReferenceName, APIobjectVariableReferenceName, progLang);	// intermediaryVariableInstanceName->variableNumerical[/String] = thirdpartyAPIobject->variableName;
			printLine(setText, level, APIwrapperSourceWrapObjectFunctionText);
		}
		else
		{
			//tested
			string thirdpartyAPIobjectReferenceName = generateCodeReferenceText(intermediaryVariableInstanceName, NLC_API_THIRD_PARTY_API_OBJECT_VARIABLE_NAME, progLang);
			string APIobjectVariableReferenceName = generateCodeReferenceText(NLC_API_THIRD_PARTY_API_OBJECT_VARIABLE_NAME, variableName, progLang);
			string setText = generateCodeSetText(thirdpartyAPIobjectReferenceName, APIobjectVariableReferenceName, progLang);	// intermediaryVariableInstanceName->thirdpartyAPIobject = thirdpartyAPIobject->variableName;
			printLine(setText, level, APIwrapperSourceWrapObjectFunctionText);
		}
		generateCodeAddEntityToList(intermediaryVariableInstanceName, generatePropertyListName(variableType1ClassName), progLang, APIwrapperSourceWrapObjectFunctionText, level);	//variableType1PropertyList.push_back(intermediaryVariableInstanceName);
	}
}

void generateCodeUnwrapObject(string variableName, string variableType1ClassName, string variableType1, bool variableTypeList, bool variableTypeStandard, int mathtextVariableType, int level, string* APIwrapperSourceUnwrapObjectFunctionText, int progLang, bool useLocalList)
{
	string variableType1InstanceName = generateInstanceNameArbitrary(variableType1);

	if(variableTypeList)
	{
		if(useLocalList)
		{
			generateCodeForEntityList(variableType1ClassName, generateLocalListName(variableType1ClassName, variableType1InstanceName), variableType1InstanceName, progLang, APIwrapperSourceUnwrapObjectFunctionText, level);	//for(vector<variableType1ClassName*>::iterator iter = variableType1LocalList->begin(); iter < variableType1LocalList->end(); iter++) { variableType1ClassName* variableType1InstanceName = *iter;
		}
		else
		{
			generateCodeForEntityList(variableType1ClassName, generatePropertyListName(variableType1ClassName), variableType1InstanceName, progLang, APIwrapperSourceUnwrapObjectFunctionText, level);	//for(vector<variableType1ClassName*>::iterator iter = variableType1PropertyList->begin(); iter < variableType1PropertyList->end(); iter++) { variableType1ClassName* variableType1InstanceName = *iter;
		}

		string variableReferenceName = "";
		if(variableTypeStandard)
		{
			variableReferenceName = generateCodeEntityMathObjectValueText(variableType1InstanceName, mathtextVariableType, progLang);	//variableType1Instance->mathObjectNumericalValue/mathObjectStringValue/mathObjectBooleanValue
		}
		else
		{
			variableReferenceName = generateCodeReferenceText(variableType1InstanceName, NLC_API_THIRD_PARTY_API_OBJECT_VARIABLE_NAME, progLang);	//variableType1Instance->thirdpartyAPIobject
		}
		if(useLocalList)
		{
			string APIobjectVariableReferenceName = variableName;
			generateCodeAddEntityToList(variableReferenceName, APIobjectVariableReferenceName, progLang, APIwrapperSourceUnwrapObjectFunctionText, level+1);	//variableName.push_back(variableType1Instance->thirdpartyAPIobject/mathObjectNumericalValue/mathObjectStringValue/mathObjectBooleanValue);
		}
		else
		{
			string APIobjectVariableReferenceName = generateCodeReferenceText(NLC_API_THIRD_PARTY_API_OBJECT_VARIABLE_NAME, variableName, progLang);
			generateCodeAddEntityToList(variableReferenceName, APIobjectVariableReferenceName, progLang, APIwrapperSourceUnwrapObjectFunctionText, level+1);	//thirdpartyAPIobject->variableName.push_back(variableType1Instance->thirdpartyAPIobject/mathObjectNumericalValue/mathObjectStringValue/mathObjectBooleanValue);
		}

		printLine(progLangCloseBlock[progLang], level, APIwrapperSourceUnwrapObjectFunctionText);
	}
	else
	{
		if(useLocalList)
		{
			string tempVarDeclarationText = generateCodeEntityDefinitionText(variableType1ClassName, variableType1InstanceName, progLang) + progLangEquals[progLang] + generateLocalListName(variableType1ClassName, variableType1InstanceName) + progLangObjectReferenceDelimiter2[progLang] + progLangGetLast[progLang] + progLangEndLine[progLang];	//variableType1ClassName* variableType1Instance = variableType1LocalList->back();
			printLine(tempVarDeclarationText, level, APIwrapperSourceUnwrapObjectFunctionText);
		}
		else
		{
			string tempVarDeclarationText = generateCodeEntityDefinitionText(variableType1ClassName, variableType1InstanceName, progLang) + progLangEquals[progLang] + generatePropertyListName(variableType1ClassName) + progLangObjectReferenceDelimiter2[progLang] + progLangGetLast[progLang] + progLangEndLine[progLang];	//variableType1ClassName* variableType1Instance = variableType1PropertyList->back();
			printLine(tempVarDeclarationText, level, APIwrapperSourceUnwrapObjectFunctionText);
		}

		string variableReferenceName = "";
		if(variableTypeStandard)
		{
			variableReferenceName = generateCodeEntityMathObjectValueText(variableType1InstanceName, mathtextVariableType, progLang);	//variableType1Instance->mathObjectNumericalValue/mathObjectStringValue/mathObjectBooleanValue
		}
		else
		{
			variableReferenceName = generateCodeReferenceText(variableType1InstanceName, NLC_API_THIRD_PARTY_API_OBJECT_VARIABLE_NAME, progLang);	//variableType1Instance->thirdpartyAPIobject
		}
		string setText = "";
		if(useLocalList)
		{
			string APIobjectVariableReferenceName = variableName;
			setText = generateCodeSetText(APIobjectVariableReferenceName, variableReferenceName, progLang);	//variableName = variableType1Instance->thirdpartyAPIobject/mathObjectNumericalValue/mathObjectStringValue/mathObjectBooleanValue;
		}
		else
		{
			string APIobjectVariableReferenceName = generateCodeReferenceText(NLC_API_THIRD_PARTY_API_OBJECT_VARIABLE_NAME, variableName, progLang);
			setText = generateCodeSetText(APIobjectVariableReferenceName, variableReferenceName, progLang);	//thirdpartyAPIobject->variableName = variableType1Instance->thirdpartyAPIobject/mathObjectNumericalValue/mathObjectStringValue/mathObjectBooleanValue;
		}
		printLine(setText, level, APIwrapperSourceUnwrapObjectFunctionText);
	}
}

string generateInstanceNameArbitrary(string classNameRaw)
{
	string instanceNameArbitrary = generateInstanceName(classNameRaw, 0);	//see GIAentityNode::GIAentityNode(void) for idInstance initialisation
	return instanceNameArbitrary;
}

bool variableTypeIsStandard(string variableType, int* type)
{
	bool variableTypeStandard = false;
	for(int i=0; i<NLC_API_VARIABLE_TYPE_LIST_NUMBER_OF_TYPES; i++)
	{
		if(variableType == APIvariableTypeStandard[i])
		{
			variableTypeStandard = true;
			*type = i;
		}
	}
	return variableTypeStandard;
}

bool variableTypeIsList(string variableType, string* variableTypeEmbedded)
{
	bool variableTypeList = false;
	for(int i=0; i<NLC_API_VARIABLE_TYPE_LIST_NUMBER_OF_TYPES; i++)
	{
		if(variableType.find(APIvariableTypeListPrepend[i]) == 0)
		{
			if(variableType.rfind(APIvariableTypeListAppend[i]) == (variableType.length() - APIvariableTypeListAppend[i].length()))
			{
				variableTypeList = true;
				*variableTypeEmbedded = variableType.substr(APIvariableTypeListPrepend[i].length(), (variableType.length() - APIvariableTypeListPrepend[i].length() - APIvariableTypeListAppend[i].length()));
			}
		}
	}
	return variableTypeList;
}


string generateAPIwrapperSourceWrapOrUnwrapObjectFunctionHeaderText(string functionNamePrepend, string classNameRaw, int progLang)
{
	string APIwrapperSourceWrapObjectFunctionHeaderText = generateFunctionHeader(generateAPIwrapperSourceWrapperFunctionName(functionNamePrepend, classNameRaw), generateAPIwrapperSourceWrapperFunctionArgumentDefinitionText(classNameRaw, progLang), progLang);
	return APIwrapperSourceWrapObjectFunctionHeaderText;
}

string generateAPIwrapperSourceWrapFunctionFunctionHeaderText(string functionNamePrepend, string classNameRaw, string argumentsDefinitionText, int progLang)
{
	string APIwrapperSourceWrapFunctionFunctionHeaderText = generateFunctionHeader(generateAPIwrapperSourceWrapperFunctionName(functionNamePrepend, classNameRaw), argumentsDefinitionText, progLang);
	return APIwrapperSourceWrapFunctionFunctionHeaderText;
}

string generateAPIwrapperSourceWrapperFunctionName(string functionNamePrepend, string classNameRaw)
{
	#ifdef NLC_API_SEPARATE_FILE_FOR_WRAPPER_FUNCTIONS
	string APIwrapperSourceWrapperFunctionName = functionNamePrepend + classNameRaw;	//eg wrapThirdPartyAPIobjectAPIclassName
	#else
	string APIwrapperSourceWrapperFunctionName = functionNamePrepend;			//eg wrapThirdPartyAPIobject
	#endif
	return APIwrapperSourceWrapperFunctionName;
}

string generateAPIwrapperSourceWrapperFunctionArgumentDefinitionText(string classNameRaw, int progLang)
{
	string APIwrapperSourceWrapperFunctionArgumentDefinitionText = generateDefinitionText(generatePointerTypeText(classNameRaw, progLang), NLC_API_THIRD_PARTY_API_OBJECT_VARIABLE_NAME);	//eg APIclassName* thirdpartyAPIobject
	return APIwrapperSourceWrapperFunctionArgumentDefinitionText;
}

string generateFunctionHeader(string functionName, string argumentText, int progLang)
{
	string functionHeaderText = functionName + progLangClassMemberFunctionParametersOpen[progLang] + argumentText + progLangClassMemberFunctionParametersClose[progLang];
	return functionHeaderText;
}



#endif





