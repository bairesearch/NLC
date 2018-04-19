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
 * File Name: NLCapi.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2018 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler
 * Project Version: 2f7b 17-April-2018
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 * /
 *******************************************************************************/


#include "NLCapi.hpp"

#ifdef NLC_API
bool NLCapiClass::parseDoxygenClassXMLfile(const string APIclassName, const string APIsourceFolder, vector<NLCclassDefinition*>* classDefinitionList, int progLang)
{
	bool result = true;

	string doxygenXMLclassFileName = string(DOXYGEN_XML_CLASS_FILE_NAME_PREPEND) + APIclassName + DOXYGEN_XML_CLASS_FILE_NAME_EXTENSION;
	string doxygenXMLclassFileNameFullPath =  APIsourceFolder + DOXYGEN_XML_OUTPUT_FOLDER + doxygenXMLclassFileName;

 	XMLparserTag* firstTagInXMLFile = new XMLparserTag();

	cout << "doxygenXMLclassFileNameFullPath = " << doxygenXMLclassFileNameFullPath << endl;

 	if(!XMLparserClass.readXMLfile(doxygenXMLclassFileNameFullPath, firstTagInXMLFile))
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
				string className = NLCitemClass.generateClassName(APIclassName);
				NLCclassDefinition* classDefinition = NULL;
				if(NLCtranslatorClassDefinitions.addClassDefinitionToList(classDefinitionList, className, &classDefinition))
				{//this should always be true considering APIclassNames should be unique

					string APIsourceHeaderFileName = "";
					#ifdef NLC_API_SEPARATE_FILE_FOR_WRAPPER_FUNCTIONS
					string printedClassDefinitionHeaderFileName = NLCprintClassDefinitions.generateCodeClassDefinitionHeaderFileName(classDefinition->name);	//eg "NLCgeneratedInterfaceXClass.hpp"
					string printedClassDefinitionSourceFileName = NLCprintClassDefinitions.generateCodeClassDefinitionSourceFileName(classDefinition->name);	//eg "NLCgeneratedInterfaceXClass.cpp"
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
					APIwrapperSourceText = APIwrapperSourceText + NLCprintClassDefinitions.generateCodeHashIncludeReference(printedClassDefinitionHeaderFileName, progLang);	//eg #include "NLCgeneratedInterfaceXClass.hpppp";
					#endif


					while(currentTagUpdatedL3->nextTag != NULL)
					{
						if(currentTagUpdatedL3->name == NET_XML_TAG_includes)
						{
							APIsourceHeaderFileName = currentTagUpdatedL3->value;
						}
						if(currentTagUpdatedL3->name == NET_XML_TAG_basecompoundref)
						{
							string APIclassParentName = currentTagUpdatedL3->value;	//TODO support template classes eg "QIntDict&lt; char &gt;" (QIntDict<char>)
							NLCclassDefinition* parentClassDefinition = NULL;
							if(NLCtranslatorClassDefinitions.addClassDefinitionToList(classDefinitionList, APIclassParentName, &parentClassDefinition))
							{
								parentClassDefinition->APIwrapperSourceText = new string("");	//do not add any wrapper code (only if this class is specifically defined by the API will this text be added)
								parentClassDefinition->APIwrapperHeaderText = new string("");	//do not add any wrapper code (only if this class is specifically defined by the API will this text be added)
								NLCtranslatorClassDefinitions.addDefinitionToClassDefinition(classDefinition, parentClassDefinition);
							}
						}
						if(currentTagUpdatedL3->name == NET_XML_TAG_sectiondef)
						{

							string sectionType = "";
							if(XMLparserClass.getAttribute(currentTagUpdatedL3, NET_XML_ATTRIBUTE_kind, &sectionType))
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
					NLCprintDefs.printLine(progLangClassMemberFunctionTypeDefault[progLang] + APIwrapperSourceWrapObjectFunctionHeaderText + progLangEndLine[progLang], 1, &APIwrapperHeaderText);	//void wrapThirdPartyAPIobject(APIclassName* thirdpartyAPIobject);
					NLCprintDefs.printLine(progLangClassMemberFunctionTypeDefault[progLang] + APIwrapperSourceUnwrapObjectFunctionHeaderText + progLangEndLine[progLang], 1, &APIwrapperHeaderText);	//void unwrapThirdPartyAPIobject(APIclassName* thirdpartyAPIobject);
					APIwrapperHeaderText = APIwrapperHeaderText + APIwrapperHeaderWrapFunctionFunctionsText;

					#ifdef NLC_API_SEPARATE_FILE_FOR_WRAPPER_FUNCTIONS
					string printedClassDefinitionAPIwrapperHeaderFileName = string(NLC_API_SEPARATE_FILE_FOR_WRAPPER_FUNCTIONS_NAME_PREPEND) + className + NLC_LIBRARY_GENERATE_INDIVIDUAL_FILES_EXTENSION_HPP;	//NLCgeneratedInterfaceXClass.hpp
					string printedClassDefinitionAPIwrapperSourceFileName = string(NLC_API_SEPARATE_FILE_FOR_WRAPPER_FUNCTIONS_NAME_PREPEND) + className + NLC_LIBRARY_GENERATE_INDIVIDUAL_FILES_EXTENSION_CPP;	//NLCgeneratedInterfaceXClass.cpp
					SHAREDvars.writeStringToFile(printedClassDefinitionAPIwrapperSourceFileName, &APIwrapperSourceText);
					SHAREDvars.writeStringToFile(printedClassDefinitionAPIwrapperHeaderFileName, &APIwrapperHeaderText);
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

void NLCapiClass::generatePropertyClassLists(XMLparserTag* currentTagUpdated, vector<NLCclassDefinition*>* classDefinitionList, NLCclassDefinition* classDefinition, const string APIclassName, string* APIwrapperSourceWrapObjectFunctionText, string* APIwrapperSourceUnwrapObjectFunctionText, const int progLang)
{
	XMLparserTag* currentTagUpdatedL2 = currentTagUpdated->firstLowerLevelTag;
	while(currentTagUpdatedL2->nextTag != NULL)
	{
		if(currentTagUpdatedL2->name == NET_XML_TAG_memberdef)	//eg <memberdef kind="variable" id="classMemberGroup_1a74b619b49dc3e68d42a365267172a0ea" prot="private" static="no" mutable="no">
		{
			string memberType = "";
			if(XMLparserClass.getAttribute(currentTagUpdatedL2, NET_XML_ATTRIBUTE_kind, &memberType))
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
						}
						if(currentTagUpdatedL3->name == NET_XML_TAG_type)	//eg <type><ref refid="classMemberList" kindref="compound">MemberList</ref> *</type>
						{
							variableType = getType(currentTagUpdatedL3);
						}

						currentTagUpdatedL3 = currentTagUpdatedL3->nextTag;
					}

					string variableType1 = "";
					string variableType1ClassName = "";
					string variableType2 = "";
					bool variableTypeList = false;
					bool variableTypeStandard = false;
					int mathtextVariableType = NLC_MATH_OBJECTS_VARIABLE_TYPE_UNKNOWN;
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

void NLCapiClass::generateFunctionClassLists(XMLparserTag* currentTagUpdated, vector<NLCclassDefinition*>* classDefinitionList, NLCclassDefinition* classDefinition, const string APIclassName, string* APIwrapperSourceWrapFunctionFunctionsText, string* APIwrapperHeaderWrapFunctionFunctionsText, int progLang)
{
	XMLparserTag* currentTagUpdatedL2 = currentTagUpdated->firstLowerLevelTag;
	while(currentTagUpdatedL2->nextTag != NULL)
	{
		if(currentTagUpdatedL2->name == NET_XML_TAG_memberdef)	//eg  <memberdef kind="function" id="classMemberGroup_1a544526a0c59d95f8ce1af3b44d252861" prot="public" static="no" const="no" explicit="no" inline="no" virt="non-virtual">
		{
			string memberType = "";
			if(XMLparserClass.getAttribute(currentTagUpdatedL2, NET_XML_ATTRIBUTE_kind, &memberType))
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
						}
						else if(currentTagUpdatedL3->name == NET_XML_TAG_type)
						{
							functionType = getType(currentTagUpdatedL3);	//eg <type>void</type>
						}
						else if(currentTagUpdatedL3->name == NET_XML_TAG_param)
						{
							NLCvariable* param = new NLCvariable();
							functionParameters.push_back(param);
							XMLparserTag* currentTagUpdatedL4 = currentTagUpdatedL3->firstLowerLevelTag;
							while(currentTagUpdatedL4->nextTag != NULL)
							{
								if(currentTagUpdatedL4->name == NET_XML_TAG_declname)
								{
									param->name = currentTagUpdatedL4->value;	//eg <declname>parameterName</declname>
								}
								else if(currentTagUpdatedL4->name == NET_XML_TAG_type)	//eg <type><ref refid="classClassDef" kindref="compound">parameterType</ref> *</type> / <type>bool</type>
								{
									param->typeString = getType(currentTagUpdatedL4);
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
							string variableType1ClassName = NLCitemClass.generateClassName(variableType1);
							string variableType1InstanceName = generateInstanceNameArbitrary(variableType1);
							string variableType1LocalListName = NLCprintDefs.generateLocalListName(variableType1ClassName, variableType1InstanceName);
							argumentText = argumentText + NLCprintDefs.generateDefinitionText(NLCprintDefs.generateCodeEntityListDefinitionTypeTextReferenceCompact(variableType1ClassName, progLang), variableType1LocalListName);		//vector<param1className*>& param1LocalList
						}
						string APIwrapperSourceWrapFunctionFunctionHeaderText = generateAPIwrapperSourceWrapFunctionFunctionHeaderText(NLC_API_THIRD_PARTY_API_FUNCTION_WRAP_FUNCTION_NAME + functionName, APIclassName, argumentText, progLang);	//wrapThirdPartyAPIfunction[functionName](vector<param1className*>& param1LocalList, vector<param2className*>& param2LocalList, etc)
						*APIwrapperSourceWrapFunctionFunctionsText = *APIwrapperSourceWrapFunctionFunctionsText + progLangClassMemberFunctionTypeDefault[progLang] + classDefinition->name + progLangFunctionOwnerClassDelimiter[progLang] + APIwrapperSourceWrapFunctionFunctionHeaderText + CHAR_NEWLINE + progLangOpenBlock[progLang] + CHAR_NEWLINE;	//void APIclassNameClass::wrapThirdPartyAPIfunction[functionName](vector<param1className*>& param1LocalList, vector<param2className*>& param2LocalList, etc){
						NLCprintDefs.printLine(progLangClassMemberFunctionTypeDefault[progLang] + APIwrapperSourceWrapFunctionFunctionHeaderText + progLangEndLine[progLang], 1, APIwrapperHeaderWrapFunctionFunctionsText);		//void wrapThirdPartyAPIfunction[APIclassName](vector<param1className*>& param1LocalList, vector<param2className*>& param2LocalList, etc);

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
							int mathtextVariableType = NLC_MATH_OBJECTS_VARIABLE_TYPE_UNKNOWN;
							detectVariableTypeDetails(classDefinitionList, classDefinition, variableName, variableType, &variableType1, &variableType1ClassName, &variableType2, &variableTypeList, &variableTypeStandard, &mathtextVariableType);

							string createNewEntityText = NLCprintDefs.generateCodeNewEntity(variableType, variableName, progLang);	//variableType variableName = new variableType();
							NLCprintDefs.printLine(createNewEntityText, level, APIwrapperSourceWrapFunctionFunctionsText);

							generateCodeUnwrapObject(variableName, variableType1ClassName, variableType1, variableTypeList, variableTypeStandard, mathtextVariableType, level, APIwrapperSourceWrapFunctionFunctionsText, progLang, true);

							if(firstParameter)
							{
								firstParameter = false;
							}
							else
							{
								executeFunctionText = executeFunctionText + progLangParameterSpaceNextParam[progLang];
							}
							string APIobjectVariableReferenceName = NLCprintDefs.generateCodeReferenceText(NLC_API_THIRD_PARTY_API_OBJECT_VARIABLE_NAME, variableName, progLang);
							executeFunctionText = executeFunctionText + variableName;
						}
						executeFunctionText = executeFunctionText + progLangClassMemberFunctionParametersClose[progLang] + progLangEndLine[progLang];
						NLCprintDefs.printLine(executeFunctionText, level, APIwrapperSourceWrapFunctionFunctionsText);

						*APIwrapperSourceWrapFunctionFunctionsText = *APIwrapperSourceWrapFunctionFunctionsText + progLangCloseBlock[progLang] + CHAR_NEWLINE + CHAR_NEWLINE;
					}
				}
			}
		}
		currentTagUpdatedL2 = currentTagUpdatedL2->nextTag;
	}
}

string NLCapiClass::getType(const XMLparserTag* typeTag)
{
	string typeString = "";
	bool foundRefTag = false;
	string refValue = "";
	if(typeTag->firstLowerLevelTag != NULL)
	{
		const XMLparserTag* typeTagL2 = typeTag->firstLowerLevelTag;
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

void NLCapiClass::detectVariableTypeDetails(vector<NLCclassDefinition*>* classDefinitionList, NLCclassDefinition* classDefinition, string variableName, string variableType, string* variableType1, string* variableType1ClassName, string* variableType2, const bool* variableTypeList, bool* variableTypeStandard, int* mathtextVariableType)
{
	string targetClassName = "";
	string variableTypeFinal = "";
	int variableTypeStandardType = NLC_MATH_OBJECTS_VARIABLE_TYPE_UNKNOWN;
	bool createSecondLayer = false;

	*variableType1 = variableName;
	*variableType1ClassName = NLCitemClass.generateClassName(*variableType1);
	targetClassName = *variableType1ClassName;
	NLCclassDefinition* targetClassDefinition = NULL;
	if(NLCtranslatorClassDefinitions.addClassDefinitionToList(classDefinitionList, targetClassName, &targetClassDefinition))
	{
		targetClassDefinition->APIwrapperSourceText = new string("");	//do not add any wrapper code (only if this class is specifically defined by the API will this text be added)
		targetClassDefinition->APIwrapperHeaderText = new string("");	//do not add any wrapper code (only if this class is specifically defined by the API will this text be added)
	}
	NLCtranslatorClassDefinitions.addPropertyListToClassDefinition(classDefinition, targetClassDefinition);

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
		string targetClassName2 = NLCitemClass.generateClassName(*variableType2);
		NLCclassDefinition* targetClassDefinition2 = NULL;
		if(NLCtranslatorClassDefinitions.addClassDefinitionToList(classDefinitionList, targetClassName2, &targetClassDefinition2))
		{
			targetClassDefinition2->APIwrapperSourceText = new string("");	//do not add any wrapper code (only if this class is specifically defined by the API will this text be added)
			targetClassDefinition2->APIwrapperHeaderText = new string("");	//do not add any wrapper code (only if this class is specifically defined by the API will this text be added)
		}
		NLCtranslatorClassDefinitions.addPropertyListToClassDefinition(targetClassDefinition, targetClassDefinition2);
	}
}

void NLCapiClass::generateCodeWrapObject(const string variableName, const string variableType1ClassName, const string APIclassName, const bool variableTypeList, const bool variableTypeStandard, const int mathtextVariableType, const int level, string* APIwrapperSourceWrapObjectFunctionText, const int progLang)
{
	string APIclassInstanceName = generateInstanceNameArbitrary(APIclassName);

	if(variableTypeList)
	{
		NLCprintCodeBlocksFunctions.generateCodeForEntityList(APIclassName, variableName, APIclassInstanceName, progLang, APIwrapperSourceWrapObjectFunctionText, level);	//for(vector<APIclassName*>::iterator iter = variableName->begin(); iter < variableName->end(); iter++) { APIclassName* APIclassInstanceName = *iter;
		string intermediaryVariableInstanceName = "intermediaryVariable";
		string createNewEntityText = NLCprintDefs.generateCodeNewEntity(variableType1ClassName, intermediaryVariableInstanceName, progLang);	//variableType1ClassName intermediaryVariableInstanceName = new variableType1ClassName();
		NLCprintDefs.printLine(createNewEntityText, level+1, APIwrapperSourceWrapObjectFunctionText);
		if(variableTypeStandard)
		{
			//untested
			string mathtextVariableReferenceName = NLCprintDefs.generateCodeEntityMathObjectValueText(intermediaryVariableInstanceName, mathtextVariableType, progLang);
			string setText = NLCprintDefs.generateCodeSetText(mathtextVariableReferenceName, APIclassInstanceName, progLang);	// intermediaryVariableInstanceName->variableNumerical[/String] = APIclassInstanceName;
			NLCprintDefs.printLine(setText, level+1, APIwrapperSourceWrapObjectFunctionText);
		}
		else
		{
			//untested
			string thirdpartyAPIobjectReferenceName = NLCprintDefs.generateCodeReferenceText(intermediaryVariableInstanceName, NLC_API_THIRD_PARTY_API_OBJECT_VARIABLE_NAME, progLang);
			string setText = NLCprintDefs.generateCodeSetText(thirdpartyAPIobjectReferenceName, APIclassInstanceName, progLang);	// intermediaryVariableInstanceName->thirdpartyAPIobject = APIclassInstanceName;
			NLCprintDefs.printLine(setText, level+1, APIwrapperSourceWrapObjectFunctionText);
		}
		NLCprintCodeBlocksFunctions.generateCodeAddEntityToList(intermediaryVariableInstanceName, NLCprintDefs.generatePropertyListName(variableType1ClassName), progLang, APIwrapperSourceWrapObjectFunctionText, level+1);	//variableType1PropertyList.push_back(intermediaryVariableInstanceName);
		NLCprintDefs.printLine(progLangCloseBlock[progLang], level, APIwrapperSourceWrapObjectFunctionText);
	}
	else
	{
		string intermediaryVariableInstanceName = "intermediaryVariable";
		string createNewEntityText = NLCprintDefs.generateCodeNewEntity(variableType1ClassName, intermediaryVariableInstanceName, progLang);	//variableType1ClassName intermediaryVariableInstanceName = new variableType1ClassName();
		NLCprintDefs.printLine(createNewEntityText, level, APIwrapperSourceWrapObjectFunctionText);
		if(variableTypeStandard)
		{
			//tested
			string mathtextVariableReferenceName = NLCprintDefs.generateCodeEntityMathObjectValueText(intermediaryVariableInstanceName, mathtextVariableType, progLang);
			string APIobjectVariableReferenceName = NLCprintDefs.generateCodeReferenceText(NLC_API_THIRD_PARTY_API_OBJECT_VARIABLE_NAME, variableName, progLang);
			string setText = NLCprintDefs.generateCodeSetText(mathtextVariableReferenceName, APIobjectVariableReferenceName, progLang);	// intermediaryVariableInstanceName->variableNumerical[/String] = thirdpartyAPIobject->variableName;
			NLCprintDefs.printLine(setText, level, APIwrapperSourceWrapObjectFunctionText);
		}
		else
		{
			//tested
			string thirdpartyAPIobjectReferenceName = NLCprintDefs.generateCodeReferenceText(intermediaryVariableInstanceName, NLC_API_THIRD_PARTY_API_OBJECT_VARIABLE_NAME, progLang);
			string APIobjectVariableReferenceName = NLCprintDefs.generateCodeReferenceText(NLC_API_THIRD_PARTY_API_OBJECT_VARIABLE_NAME, variableName, progLang);
			string setText = NLCprintDefs.generateCodeSetText(thirdpartyAPIobjectReferenceName, APIobjectVariableReferenceName, progLang);	// intermediaryVariableInstanceName->thirdpartyAPIobject = thirdpartyAPIobject->variableName;
			NLCprintDefs.printLine(setText, level, APIwrapperSourceWrapObjectFunctionText);
		}
		NLCprintCodeBlocksFunctions.generateCodeAddEntityToList(intermediaryVariableInstanceName, NLCprintDefs.generatePropertyListName(variableType1ClassName), progLang, APIwrapperSourceWrapObjectFunctionText, level);	//variableType1PropertyList.push_back(intermediaryVariableInstanceName);
	}
}

void NLCapiClass::generateCodeUnwrapObject(const string variableName, const string variableType1ClassName, const string variableType1, const bool variableTypeList, const bool variableTypeStandard, const int mathtextVariableType, const int level, string* APIwrapperSourceUnwrapObjectFunctionText, const int progLang, const bool useLocalList)
{
	string variableType1InstanceName = generateInstanceNameArbitrary(variableType1);

	if(variableTypeList)
	{
		if(useLocalList)
		{
			NLCprintCodeBlocksFunctions.generateCodeForEntityList(variableType1ClassName, NLCprintDefs.generateLocalListName(variableType1ClassName, variableType1InstanceName), variableType1InstanceName, progLang, APIwrapperSourceUnwrapObjectFunctionText, level);	//for(vector<variableType1ClassName*>::iterator iter = variableType1LocalList->begin(); iter < variableType1LocalList->end(); iter++) { variableType1ClassName* variableType1InstanceName = *iter;
		}
		else
		{
			NLCprintCodeBlocksFunctions.generateCodeForEntityList(variableType1ClassName, NLCprintDefs.generatePropertyListName(variableType1ClassName), variableType1InstanceName, progLang, APIwrapperSourceUnwrapObjectFunctionText, level);	//for(vector<variableType1ClassName*>::iterator iter = variableType1PropertyList->begin(); iter < variableType1PropertyList->end(); iter++) { variableType1ClassName* variableType1InstanceName = *iter;
		}

		string variableReferenceName = "";
		if(variableTypeStandard)
		{
			variableReferenceName = NLCprintDefs.generateCodeEntityMathObjectValueText(variableType1InstanceName, mathtextVariableType, progLang);	//variableType1Instance->mathObjectNumericalValue/mathObjectStringValue/mathObjectBooleanValue
		}
		else
		{
			variableReferenceName = NLCprintDefs.generateCodeReferenceText(variableType1InstanceName, NLC_API_THIRD_PARTY_API_OBJECT_VARIABLE_NAME, progLang);	//variableType1Instance->thirdpartyAPIobject
		}
		if(useLocalList)
		{
			string APIobjectVariableReferenceName = variableName;
			NLCprintCodeBlocksFunctions.generateCodeAddEntityToList(variableReferenceName, APIobjectVariableReferenceName, progLang, APIwrapperSourceUnwrapObjectFunctionText, level+1);	//variableName.push_back(variableType1Instance->thirdpartyAPIobject/mathObjectNumericalValue/mathObjectStringValue/mathObjectBooleanValue);
		}
		else
		{
			string APIobjectVariableReferenceName = NLCprintDefs.generateCodeReferenceText(NLC_API_THIRD_PARTY_API_OBJECT_VARIABLE_NAME, variableName, progLang);
			NLCprintCodeBlocksFunctions.generateCodeAddEntityToList(variableReferenceName, APIobjectVariableReferenceName, progLang, APIwrapperSourceUnwrapObjectFunctionText, level+1);	//thirdpartyAPIobject->variableName.push_back(variableType1Instance->thirdpartyAPIobject/mathObjectNumericalValue/mathObjectStringValue/mathObjectBooleanValue);
		}

		NLCprintDefs.printLine(progLangCloseBlock[progLang], level, APIwrapperSourceUnwrapObjectFunctionText);
	}
	else
	{
		if(useLocalList)
		{
			string tempVarDeclarationText = NLCprintDefs.generateCodeEntityDefinitionText(variableType1ClassName, variableType1InstanceName, progLang) + progLangEquals[progLang] + NLCprintDefs.generateLocalListName(variableType1ClassName, variableType1InstanceName) + progLangObjectReferenceDelimiter2[progLang] + progLangGetLast[progLang] + progLangEndLine[progLang];	//variableType1ClassName* variableType1Instance = variableType1LocalList->back();
			NLCprintDefs.printLine(tempVarDeclarationText, level, APIwrapperSourceUnwrapObjectFunctionText);
		}
		else
		{
			string tempVarDeclarationText = NLCprintDefs.generateCodeEntityDefinitionText(variableType1ClassName, variableType1InstanceName, progLang) + progLangEquals[progLang] + NLCprintDefs.generatePropertyListName(variableType1ClassName) + progLangObjectReferenceDelimiter2[progLang] + progLangGetLast[progLang] + progLangEndLine[progLang];	//variableType1ClassName* variableType1Instance = variableType1PropertyList->back();
			NLCprintDefs.printLine(tempVarDeclarationText, level, APIwrapperSourceUnwrapObjectFunctionText);
		}

		string variableReferenceName = "";
		if(variableTypeStandard)
		{
			variableReferenceName = NLCprintDefs.generateCodeEntityMathObjectValueText(variableType1InstanceName, mathtextVariableType, progLang);	//variableType1Instance->mathObjectNumericalValue/mathObjectStringValue/mathObjectBooleanValue
		}
		else
		{
			variableReferenceName = NLCprintDefs.generateCodeReferenceText(variableType1InstanceName, NLC_API_THIRD_PARTY_API_OBJECT_VARIABLE_NAME, progLang);	//variableType1Instance->thirdpartyAPIobject
		}
		string setText = "";
		if(useLocalList)
		{
			string APIobjectVariableReferenceName = variableName;
			setText = NLCprintDefs.generateCodeSetText(APIobjectVariableReferenceName, variableReferenceName, progLang);	//variableName = variableType1Instance->thirdpartyAPIobject/mathObjectNumericalValue/mathObjectStringValue/mathObjectBooleanValue;
		}
		else
		{
			string APIobjectVariableReferenceName = NLCprintDefs.generateCodeReferenceText(NLC_API_THIRD_PARTY_API_OBJECT_VARIABLE_NAME, variableName, progLang);
			setText = NLCprintDefs.generateCodeSetText(APIobjectVariableReferenceName, variableReferenceName, progLang);	//thirdpartyAPIobject->variableName = variableType1Instance->thirdpartyAPIobject/mathObjectNumericalValue/mathObjectStringValue/mathObjectBooleanValue;
		}
		NLCprintDefs.printLine(setText, level, APIwrapperSourceUnwrapObjectFunctionText);
	}
}

string NLCapiClass::generateInstanceNameArbitrary(const string classNameRaw)
{
	string instanceNameArbitrary = NLCitemClass.generateInstanceName(classNameRaw, 0);	//see GIAentityNode::GIAentityNode(void) for idInstance initialisation
	return instanceNameArbitrary;
}

bool NLCapiClass::variableTypeIsStandard(const string variableType, int* type)
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

bool NLCapiClass::variableTypeIsList(string variableType, string* variableTypeEmbedded)
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


string NLCapiClass::generateAPIwrapperSourceWrapOrUnwrapObjectFunctionHeaderText(string functionNamePrepend, const string classNameRaw, const int progLang)
{
	string APIwrapperSourceWrapObjectFunctionHeaderText = generateFunctionHeader(generateAPIwrapperSourceWrapperFunctionName(functionNamePrepend, classNameRaw), generateAPIwrapperSourceWrapperFunctionArgumentDefinitionText(classNameRaw, progLang), progLang);
	return APIwrapperSourceWrapObjectFunctionHeaderText;
}

string NLCapiClass::generateAPIwrapperSourceWrapFunctionFunctionHeaderText(string functionNamePrepend, const string classNameRaw, const string argumentsDefinitionText, const int progLang)
{
	string APIwrapperSourceWrapFunctionFunctionHeaderText = generateFunctionHeader(generateAPIwrapperSourceWrapperFunctionName(functionNamePrepend, classNameRaw), argumentsDefinitionText, progLang);
	return APIwrapperSourceWrapFunctionFunctionHeaderText;
}

string NLCapiClass::generateAPIwrapperSourceWrapperFunctionName(string functionNamePrepend, const string classNameRaw)
{
	#ifdef NLC_API_SEPARATE_FILE_FOR_WRAPPER_FUNCTIONS
	string APIwrapperSourceWrapperFunctionName = functionNamePrepend + classNameRaw;	//eg wrapThirdPartyAPIobjectAPIclassName
	#else
	string APIwrapperSourceWrapperFunctionName = functionNamePrepend;			//eg wrapThirdPartyAPIobject
	#endif
	return APIwrapperSourceWrapperFunctionName;
}

string NLCapiClass::generateAPIwrapperSourceWrapperFunctionArgumentDefinitionText(const string classNameRaw, const int progLang)
{
	string APIwrapperSourceWrapperFunctionArgumentDefinitionText = NLCprintDefs.generateDefinitionText(NLCprintDefs.generatePointerTypeText(classNameRaw, progLang), NLC_API_THIRD_PARTY_API_OBJECT_VARIABLE_NAME);	//eg APIclassName* thirdpartyAPIobject
	return APIwrapperSourceWrapperFunctionArgumentDefinitionText;
}

string NLCapiClass::generateFunctionHeader(const string functionName, const string argumentText, const int progLang)
{
	string functionHeaderText = functionName + progLangClassMemberFunctionParametersOpen[progLang] + argumentText + progLangClassMemberFunctionParametersClose[progLang];
	return functionHeaderText;
}



#endif





