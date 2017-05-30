/*******************************************************************************
 *
 * This file is part of BAIPROJECT.
 *
 * BAIPROJECT is licensed under the GNU Affero General Public License
 * version 3, as published by the Free Software Foundation. The use of
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
 * File Name: NLCclassDefinitionClass.hpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2017 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 2b3e 25-May-2017
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/


#ifndef HEADER_NLC_CLASSDEFINITION_CLASS
#define HEADER_NLC_CLASSDEFINITION_CLASS

#include "NLCglobalDefs.hpp"
#include "NLCitemClass.hpp"
#include "GIAentityNodeClass.hpp"
#include "GIAentityConnectionClass.hpp"

	//progLangEndLine

#ifdef NLC_LIBRARY
	#define FUNCTION_INDEX_LIBRARY_FUNCTION (INT_DEFAULT_VALUE)	//library functions do not have a function index assigned to them	//OLD: 999999999
#endif

#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE
//used to create a dependency tree of functions
class NLCclassDefinitionFunctionDependency
{
public:
	NLCclassDefinitionFunctionDependency(void);
	NLCclassDefinitionFunctionDependency(string newName);
	~NLCclassDefinitionFunctionDependency(void);

	string functionName;
	string functionOwnerName;
	string functionObjectName;
	bool hasFunctionOwnerClass;
	bool hasFunctionObjectClass;

	int functionDefinitionListIndex;
	bool reconciledFunctionDeclarationArguments;

	bool isReferenceElseFunctionDefinition;
};
#endif

class NLCclassDefinition
{
public:

	NLCclassDefinition(void);
	NLCclassDefinition(string newName);
	~NLCclassDefinition(void);

	string name;	//className (or instanceName if isActionOrConditionInstanceNotClass)
	string functionNameSpecial;

	//classdefinition sublists;
	vector<NLCclassDefinition*> propertyList;      //subclass
	vector<NLCclassDefinition*> conditionList;     //declared conditions
	vector<NLCclassDefinition*> definitionList;    //inherited parents
	vector<NLCclassDefinition*> functionList;
	#ifdef NLC_RECORD_ACTION_HISTORY
	vector<NLCclassDefinition*> actionList; 	       //used by action subjects only
	vector<NLCclassDefinition*> actionIncomingList;        //used by action objects only
	vector<NLCclassDefinition*> actionSubjectList; //used by action class definitions only (these are distinct from invisible function reference class definitions)
	vector<NLCclassDefinition*> actionObjectList;  //used by action class definitions only (these are distinct from invisible function reference class definitions)
	#endif

	bool isActionOrConditionInstanceNotClass;
	bool isConditionInstance;	//added 1m3a

	#ifdef NLC_INPUT_FUNCTION_LISTS_CHECK_ACTION_SUBJECT_CONTENTS_FOR_IMPLICITLY_DECLARED_PARAMETERS
	GIAentityNode* actionOrConditionInstance;
	#endif
	vector<NLCitem*> parameters;

	bool isDisabledChildReplicantDeclaration;

	bool printed;

	#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE
	NLCclassDefinitionFunctionDependency* functionDependency;	//for function classDefinitions only (not for non-function classDefinitions) - includes library function classDefinitions
	vector<NLCclassDefinition*> functionDependencyList;		//for function classDefinitions only (not for non-function classDefinitions) - excludes library function classDefinitions
	#endif

	#ifdef NLC_LIBRARY_FUNCTION_LISTS_FOR_ARGUMENT_RECONCILIATION
	bool isLibraryFunctionDefinition;	//not used often
	#endif

	#ifdef NLC_API
	#ifndef NLC_API_SEPARATE_FILE_FOR_WRAPPER_FUNCTIONS
	bool APIclass;
	string APIsourceFileFullPath;
	string* APIwrapperSourceText;
	string* APIwrapperHeaderText;
	#endif
	#endif
};

class NLCclassDefinitionClassClass
{
	private: NLCitemClassClass NLCitemClass;
	#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE_DO_NOT_ADD_FUNCTION_DEPENDENCY_FOR_FUNCTION_REFERENCES
	public: NLCclassDefinition* findClassDefinitionFunction(vector<NLCclassDefinition*>* functionList, const string functionName, const string functionOwnerName, const string functionObjectName, const bool hasFunctionOwnerClass, const bool hasFunctionObjectClass, bool* foundClassDefinition);
	private: bool findItemInList(vector<NLCitem*>* parameters, const int itemType, const string itemName);
	#endif
	public: NLCclassDefinition* findClassDefinition(vector<NLCclassDefinition*>* classDefinitionList, const string name, bool* foundClassDefinition);
	public: NLCclassDefinition* findClassDefinitionCondition(vector<NLCclassDefinition*>* classDefinitionList, GIAentityNode* targetEntity, bool* foundClassDefinition);
	public: bool findFunctionDefinitionFunctionDependencyInList(vector<NLCclassDefinition*>* classDefinitionList, const string functionName, const string functionOwnerName, const string functionObjectName, const bool hasFunctionOwnerClass, const bool hasFunctionObjectClass, NLCclassDefinitionFunctionDependency** functionDependencyFound);
		public: bool findFunctionDependencyClassDefinitionInList(vector<NLCclassDefinition*>* classDefinitionList, const string functionName, const string functionOwnerName, const string functionObjectName, const bool hasFunctionOwnerClass, const bool hasFunctionObjectClass, constEffective NLCclassDefinition** classDefinitionFound);
			private: bool compareFunctionDependency(const NLCclassDefinitionFunctionDependency* functionDependency, const string functionName, const string functionOwnerName, const string functionObjectName, const bool hasFunctionOwnerClass, const bool hasFunctionObjectClass);
	private: bool findFunctionDefinitionFunctionDependencyInListByIndex(vector<NLCclassDefinition*>* classDefinitionList, const int functionIndex, NLCclassDefinitionFunctionDependency** functionDependencyFound);
		public: bool findFunctionDependencyClassDefinitionInListByIndex(vector<NLCclassDefinition*>* classDefinitionList, const int functionIndex, constEffective NLCclassDefinition** functionDefinitionFound);

	#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_RECURSIVE
	public: bool findFunctionDependencyInParent(NLCclassDefinition* parentFunctionDependencyClassDefinition, const string functionName, const string functionOwnerName, const string functionObjectName, const bool hasFunctionOwnerClass, const bool hasFunctionObjectClass, NLCclassDefinitionFunctionDependency** functionDependencyFound);
	#endif

	#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS
	#ifdef NLC_RECONCILE_CLASS_DEFINITION_LIST_FUNCTION_DECLARATION_ARGUMENTS_ADVANCED
	public: bool findFunctionDefinitionClassDefinitionExactOrNonExactMatch(vector<NLCclassDefinition*>* classDefinitionList, const string functionName, const string functionOwnerName, const string functionObjectName, const bool hasFunctionOwnerClass, const bool hasFunctionObjectClass, constEffective NLCclassDefinition** functionDefinitionClassDefinitionFound, const bool rearrangeClassList, bool* foundFunctionOwnerExactMatch, bool* foundFunctionObjectExactMatch);
		public: bool findFunctionDefinitionClassDefinition(vector<NLCclassDefinition*>* classDefinitionList, const string functionName, const string functionOwnerName, const string functionObjectName, const bool hasFunctionOwnerClass, const bool hasFunctionObjectClass, const bool findFunctionOwnerExactMatch, const bool findFunctionObjectExactMatch, constEffective NLCclassDefinition** functionDefinitionClassDefinitionFound, const bool rearrangeClassList);
			private: bool eraseFunctionDependencyFromFunctionDependencyList(vector<NLCclassDefinitionFunctionDependency*>* functionDependencyList, const NLCclassDefinitionFunctionDependency* functionDependencyToErase);
	#endif
	private: bool findParentClass(NLCclassDefinition* classDefinition, const string variableName, int inheritanceLevel, int* maxInheritanceLevel, constEffective NLCclassDefinition** parentClass);
	#endif
	//see NLCcodeBlocks.cpp for other versions of this function;
	public: bool findFunctionArgument(vector<NLCitem*>* parameters, const string itemName, const int itemType, constEffective NLCitem** functionArgument);
	public: bool findFunctionArgument(vector<NLCitem*>* parameters, const NLCitem* item, const int itemType, constEffective NLCitem** functionArgument);
	public: bool findFunctionArgument(vector<NLCitem*>* parameters, const int itemType, constEffective NLCitem** functionArgument);
};



#endif
