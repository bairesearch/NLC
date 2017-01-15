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
 * File Name: NLCcodeBlockClass.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2014 Baxter AI (baxterai.com)
 * Project: Natural Language Programming Interface (compiler)
 * Project Version: 1h10b 04-August-2014
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/




#include "NLCcodeBlockClass.h"
#include "GIAtranslatorOperations.h"
#include "NLCprintDefs.h"	//required for progLangArrayOpen/progLangArrayClose



NLClogicalConditionConjunctionVariables::NLClogicalConditionConjunctionVariables(void)
{
	logicalOperation = NLC_LOGICAL_CONDITION_OPERATIONS_FOR;
	//#ifndef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS
	negative = BOOL_IRRELEVANT;
	//#endif
	#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS
	logicalConditionConjunctionIndex = INT_DEFAULT_VALUE;
	primaryEntityInLogicalConditionConjunctionSubset = NULL;
	foundLogicalConditionConjunction = NULL;
	#endif
	#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
	onlyGenerateContextBlocksIfConnectionsParsedForNLC = false;
	#endif
	#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
	negativeDetectedInContextBlocks = false;
	#endif
}
NLClogicalConditionConjunctionVariables::~NLClogicalConditionConjunctionVariables(void)
{
}

#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS
NLClogicalConditionConjunction::NLClogicalConditionConjunction(void)
{
	conjunctionType = INT_DEFAULT_VALUE;
	negative = false;
}
NLClogicalConditionConjunction::~NLClogicalConditionConjunction(void)
{
}
#endif


NLCcodeblock::NLCcodeblock(void)
{
	codeBlockType = NLC_CODEBLOCK_TYPE_UNDEFINED;

	/*
	//used by language specific code generator (eg C++, java);
	codeBlockName = ""; 	//eg "for"
	openingText = "";	//eg "for(...){"
	closingText = ""; 	//eg "}";
	*/

	lowerLevel = NULL;
	next = NULL;
}
NLCcodeblock::~NLCcodeblock(void)
{
}



//Resultant code: functionItem[context].functionItem[name](objectItem[context].objectItem[name]);	//NB functionItem[context] = action subject
NLCcodeblock * createCodeBlockExecute(NLCcodeblock * currentCodeBlockInTree, NLCitem * functionItem, NLCitem* objectItem)
{
	currentCodeBlockInTree->parameters.push_back(functionItem);
	currentCodeBlockInTree->parameters.push_back(objectItem);

	return createCodeBlock(currentCodeBlockInTree, NLC_CODEBLOCK_TYPE_EXECUTE_FUNCTION);
}

NLCcodeblock * createCodeBlockExecute(NLCcodeblock * currentCodeBlockInTree, NLCitem * functionItem)
{
	currentCodeBlockInTree->parameters.push_back(functionItem);

	return createCodeBlock(currentCodeBlockInTree, NLC_CODEBLOCK_TYPE_EXECUTE_FUNCTION);
}

//add property
NLCcodeblock * createCodeBlockAddNewProperty(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* propertyEntity, int sentenceIndex, bool copyNewItemsToLocalList)
{
	#ifdef NLC_SUPPORT_QUANTITIES
	NLCcodeblock * origCurrentCodeBlockInTree = currentCodeBlockInTree;
	if(propertyEntity->quantityNumber > 1)
	{
		string numberIterationsOrVariable = convertIntToString(propertyEntity->quantityNumber);
		#ifdef NLC_PREPROCESSOR_MATH_REPLACE_NUMERICAL_VARIABLES_NAMES_FOR_NLP
		if(propertyEntity->NLCoriginalNumericalVariableName != "")
		{
			numberIterationsOrVariable = propertyEntity->NLCoriginalNumericalVariableName;
		}
		#endif
		currentCodeBlockInTree = createCodeBlockForInteger(currentCodeBlockInTree, numberIterationsOrVariable);
	}
	//for(int i=0; i<propertyEntity->quantityNumber; i++)
	//{
	#endif

	NLCitem * entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	NLCitem * propertyItem = new NLCitem(propertyEntity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(propertyItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_ADD_NEW_PROPERTY;
	currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);

	#ifdef NLC_DEFINE_LOCAL_VARIABLES_FOR_ALL_INDEFINATE_ENTITIES
	if(copyNewItemsToLocalList)
	{
		if(propertyEntity->NLClocalListVariableHasBeenDeclared)
		{//added 1g8a 11-July-2014
			currentCodeBlockInTree = createCodeBlockAddPropertyToLocalList(currentCodeBlockInTree, propertyEntity, propertyEntity);
			propertyEntity->NLClocalListVariableHasBeenInitialised = true;

			//DEBUG:
			//string debugString = string("10createCodeBlockAddNewProperty") + entity->entityName + string(" ") + convertIntToString(entity->NLClocalListVariableHasBeenInitialised) + string(" ") + propertyEntity->entityName + string(" ") + convertIntToString(propertyEntity->NLClocalListVariableHasBeenInitialised);
			//currentCodeBlockInTree = createCodeBlockDebug(currentCodeBlockInTree, debugString);
			//cout << debugString << endl;
		}
	}
	#endif

	#ifdef NLC_SUPPORT_QUANTITIES
	if(propertyEntity->quantityNumber > 1)
	{
		currentCodeBlockInTree = origCurrentCodeBlockInTree->next;
	}
	//}
	#endif

	return currentCodeBlockInTree;
}

NLCcodeblock * createCodeBlockAddNewPropertyToLocalList(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* propertyEntity)
{
	#ifdef NLC_SUPPORT_QUANTITIES
	NLCcodeblock * origCurrentCodeBlockInTree = currentCodeBlockInTree;
	if(propertyEntity->quantityNumber > 1)
	{
		string numberIterationsOrVariable = convertIntToString(propertyEntity->quantityNumber);
		#ifdef NLC_PREPROCESSOR_MATH_REPLACE_NUMERICAL_VARIABLES_NAMES_FOR_NLP
		if(propertyEntity->NLCoriginalNumericalVariableName != "")
		{
			numberIterationsOrVariable = propertyEntity->NLCoriginalNumericalVariableName;
		}
		#endif
		currentCodeBlockInTree = createCodeBlockForInteger(currentCodeBlockInTree, numberIterationsOrVariable);
	}
	//for(int i=0; i<propertyEntity->quantityNumber; i++)
	//{
	#endif

	NLCitem * entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	NLCitem * propertyItem = new NLCitem(propertyEntity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(propertyItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_ADD_NEW_PROPERTY_TO_LOCAL_LIST;
	currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);

	#ifdef NLC_SUPPORT_QUANTITIES
	if(propertyEntity->quantityNumber > 1)
	{
		currentCodeBlockInTree = origCurrentCodeBlockInTree->next;
	}
	//}
	#endif

	return currentCodeBlockInTree;
}

NLCcodeblock * createCodeBlockAddPropertyToLocalList(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* propertyEntity)
{
	NLCitem * entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	NLCitem * propertyItem = new NLCitem(propertyEntity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(propertyItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_ADD_PROPERTY_TO_LOCAL_LIST;
	currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}

NLCcodeblock * createCodeBlockAddProperty(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* propertyEntity, int sentenceIndex)
{
	NLCitem * entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	NLCitem * propertyItem = new NLCitem(propertyEntity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(propertyItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_ADD_PROPERTY;
	currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}


//add state
NLCcodeblock * createCodeBlockAddNewCondition(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* conditionEntity, int sentenceIndex, bool copyNewItemsToLocalList)
{
	if(!(conditionEntity->conditionObjectEntity->empty()))
	{

		GIAentityNode * conditionObject = (conditionEntity->conditionObjectEntity->back())->entity;

		#ifdef NLC_SUPPORT_QUANTITIES
		NLCcodeblock * origCurrentCodeBlockInTree = currentCodeBlockInTree;
		if(conditionObject->quantityNumber > 1)
		{
			string numberIterationsOrVariable = convertIntToString(conditionObject->quantityNumber);
			#ifdef NLC_PREPROCESSOR_MATH_REPLACE_NUMERICAL_VARIABLES_NAMES_FOR_NLP
			if(conditionObject->NLCoriginalNumericalVariableName != "")
			{
				numberIterationsOrVariable = conditionObject->NLCoriginalNumericalVariableName;
			}
			#endif
			currentCodeBlockInTree = createCodeBlockForInteger(currentCodeBlockInTree, numberIterationsOrVariable);
		}
		//for(int i=0; i<conditionObject->quantityNumber; i++)
		//{
		#endif

		NLCitem * entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
		currentCodeBlockInTree->parameters.push_back(entityItem);

		NLCitem * conditionItem = new NLCitem(conditionEntity, NLC_ITEM_TYPE_OBJECT);
		currentCodeBlockInTree->parameters.push_back(conditionItem);

		NLCitem * conditionObjectItem = new NLCitem(conditionObject, NLC_ITEM_TYPE_OBJECT);
		currentCodeBlockInTree->parameters.push_back(conditionObjectItem);

		int codeBlockType = NLC_CODEBLOCK_TYPE_ADD_NEW_CONDITION;
		currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);

		#ifdef NLC_DEFINE_LOCAL_VARIABLES_FOR_ALL_INDEFINATE_ENTITIES
		if(copyNewItemsToLocalList)
		{
			if(conditionObject->NLClocalListVariableHasBeenDeclared)
			{//added 1g8a 11-July-2014
				currentCodeBlockInTree = createCodeBlockAddPropertyToLocalList(currentCodeBlockInTree, conditionObject, conditionObject);
				conditionObject->NLClocalListVariableHasBeenInitialised = true;

				//DEBUG:
				//string debugString = string("11createCodeBlockAddNewCondition") + entity->entityName + string(" ") + convertIntToString(entity->NLClocalListVariableHasBeenInitialised) + string(" ") + conditionObject->entityName + string(" ") + convertIntToString(conditionObject->NLClocalListVariableHasBeenInitialised);
				//currentCodeBlockInTree = createCodeBlockDebug(currentCodeBlockInTree, debugString);
				//cout << debugString << endl;
			}
		}
		#endif

		#ifdef NLC_SUPPORT_QUANTITIES
		if(conditionObject->quantityNumber > 1)
		{
			currentCodeBlockInTree = origCurrentCodeBlockInTree->next;
		}
		//}
		#endif
	}
	else
	{
		cout << "error: condition does not have object" << endl;
	}

	return currentCodeBlockInTree;
}

NLCcodeblock * createCodeBlockAddCondition(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* conditionEntity, int sentenceIndex)
{
	if(!(conditionEntity->conditionObjectEntity->empty()))
	{
		NLCitem * entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
		//removed 1e7c as it is not used: getEntityContext(entity, &(entityItem->context), false, sentenceIndex, false);
		currentCodeBlockInTree->parameters.push_back(entityItem);

		NLCitem * conditionItem = new NLCitem(conditionEntity, NLC_ITEM_TYPE_OBJECT);
		currentCodeBlockInTree->parameters.push_back(conditionItem);

		GIAentityNode * conditionObject = (conditionEntity->conditionObjectEntity->back())->entity;
		NLCitem * conditionObjectItem = new NLCitem(conditionObject, NLC_ITEM_TYPE_OBJECT);
		currentCodeBlockInTree->parameters.push_back(conditionObjectItem);

		int codeBlockType = NLC_CODEBLOCK_TYPE_ADD_CONDITION;
		currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);
	}
	else
	{
		cout << "error: condition does not have object" << endl;
	}

	return currentCodeBlockInTree;
}

NLCcodeblock * createCodeBlocksCreateNewLocalListVariable(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* entity)
{
	currentCodeBlockInTree = createCodeBlocksDeclareNewLocalListVariable(currentCodeBlockInTree, entity);

	currentCodeBlockInTree = createCodeBlockAddNewPropertyToLocalList(currentCodeBlockInTree, entity, entity);

	return currentCodeBlockInTree;
}

NLCcodeblock * createCodeBlocksDeclareNewLocalListVariable(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* entity)
{
	NLCitem * entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_DECLARE_NEW_LOCAL_LIST_VARIABLE;
	currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}




NLCcodeblock * createCodeBlockForPropertyList(NLCcodeblock * currentCodeBlockInTree, NLCitem * item)
{
	currentCodeBlockInTree->parameters.push_back(item);
	int codeBlockType = NLC_CODEBLOCK_TYPE_FOR_PROPERTY_LIST;
	return createCodeBlock(currentCodeBlockInTree, codeBlockType);
}

NLCcodeblock * createCodeBlockForPropertyListLocal(NLCcodeblock * currentCodeBlockInTree, NLCitem * item)
{
	currentCodeBlockInTree->parameters.push_back(item);
	int codeBlockType = NLC_CODEBLOCK_TYPE_FOR_PROPERTY_LIST_LOCAL;
	return createCodeBlock(currentCodeBlockInTree, codeBlockType);
}

NLCcodeblock * createCodeBlockForConditionList(NLCcodeblock * currentCodeBlockInTree, NLCitem * item, NLCitem * objectItem)
{
	currentCodeBlockInTree->parameters.push_back(item);
	currentCodeBlockInTree->parameters.push_back(objectItem);
	int codeBlockType = NLC_CODEBLOCK_TYPE_FOR_CONDITION_LIST;
	return createCodeBlock(currentCodeBlockInTree, codeBlockType);
}

#ifdef NLC_SUPPORT_QUANTITIES
NLCcodeblock * createCodeBlockForInteger(NLCcodeblock * currentCodeBlockInTree, string numberIterationsOrVariable)
{
	NLCitem * integerItem = new NLCitem(numberIterationsOrVariable, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(integerItem);
	int codeBlockType = NLC_CODEBLOCK_TYPE_FOR_INTEGER;
	return createCodeBlock(currentCodeBlockInTree, codeBlockType);
}
#endif





NLCcodeblock * createCodeBlockNewFunction(NLCcodeblock * currentCodeBlockInTree, string NLCfunctionName, vector<GIAentityNode*> * entityNodesActiveListComplete)
{
	#ifdef NLC_SUPPORT_INPUT_FILE_LISTS
	//gets "fight" from "dog::fight"
	string functionName = "";
	bool foundFunctionOwnerClass = false;
	string functionOwnerName = "";
	bool foundFunctionObjectClass = false;
	string functionObjectName = "";
	parseFunctionNameFromNLCfunctionName(NLCfunctionName, &functionName, &functionOwnerName, &foundFunctionOwnerClass, &functionObjectName, &foundFunctionObjectClass);

	GIAentityNode * functionOwner = NULL;
	GIAentityNode * functionObject = NULL;
	GIAentityNode * function = NULL;
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode * entity = *entityIter;
		if(!(entity->isConcept) && !(entity->isActionConcept) && !(entity->isSubstanceConcept))
		{
			if(entity->entityName == functionOwnerName)
			{
				entity->NLCisSingularArgument = true;	//formalFunctionArgumentCorrespondsToActionSubjectUseThisAlias
				entity->NLCparsedForCodeBlocks = true;

				functionOwner = entity;
			}
			else if(entity->entityName == functionObjectName)
			{
				entity->NLCisSingularArgument = true;
				entity->NLCparsedForCodeBlocks = true;

				functionObject = entity;
			}
			else if(entity->entityName == functionName)
			{
				entity->NLCisSingularArgument = true;
				entity->NLCparsedForCodeBlocks = true;

				function = entity;
			}
		}
	}
	#else
	string functionName = NLCfunctionName;
	#endif

	NLCitem * functionItem = new NLCitem(functionName, NLC_ITEM_TYPE_FUNCTION);
	currentCodeBlockInTree->parameters.push_back(functionItem);
	#ifdef NLC_SUPPORT_INPUT_FILE_LISTS
	if(foundFunctionOwnerClass)
	{
		NLCitem * functionOwnerItem = new NLCitem(functionOwnerName, NLC_ITEM_TYPE_FUNCTION_OWNER);
		currentCodeBlockInTree->parameters.push_back(functionOwnerItem);
	}
	#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS
	if(foundFunctionObjectClass)	//added 21 November 2013
	{
		if(functionObject != NULL)
		{//functionObject is used by the function definition: use functionObject instance name
			//cout << "functionObjectName2 = " << functionObjectName << endl;
			NLCitem * functionObjectItem = new NLCitem(functionObject, NLC_ITEM_TYPE_FUNCTION_OBJECT);
			currentCodeBlockInTree->parameters.push_back(functionObjectItem);
		}
		else
		{//functionObject is not used by the function definition
			NLCitem * functionObjectItem = new NLCitem(functionObjectName, NLC_ITEM_TYPE_FUNCTION_OBJECT);
			currentCodeBlockInTree->parameters.push_back(functionObjectItem);
		}
	}
	#endif
	#endif

	#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS
	generateLocalFunctionArgumentsBasedOnImplicitDeclarations(entityNodesActiveListComplete, &(currentCodeBlockInTree->parameters));
	#endif

	currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, NLC_CODEBLOCK_TYPE_NEW_FUNCTION);

	#ifdef NLC_SUPPORT_INPUT_FILE_LISTS
	#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS
	if(functionOwner != NULL)
	{
		currentCodeBlockInTree = createCodeBlockDeclareAndInitialiseVariableForActionSubject(currentCodeBlockInTree, functionOwner);
		currentCodeBlockInTree = createCodeBlocksAddVariableToNewList(currentCodeBlockInTree, functionOwner);
	}
	#endif
	if(functionObject != NULL)
	{
		currentCodeBlockInTree = createCodeBlocksAddVariableToNewList(currentCodeBlockInTree, functionObject);
	}
	if(function != NULL)
	{
		currentCodeBlockInTree = createCodeBlocksAddVariableToNewList(currentCodeBlockInTree, function);
	}
	#endif

	return currentCodeBlockInTree;
}

NLCcodeblock * createCodeBlockDeclareAndInitialiseVariableForActionSubject(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* functionOwner)
{
	//"Dog dog1 = this;"
	NLCitem * functionOwnerItem = new NLCitem(functionOwner, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(functionOwnerItem);
	NLCitem * actionSubjectInstanceReplacementItem = new NLCitem(NLC_SUPPORT_INPUT_FILE_LISTS_ACTION_SUBJECT_INSTANCE_REPLACEMENT_NAME, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(actionSubjectInstanceReplacementItem);
	currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, NLC_CODEBLOCK_TYPE_DECLARE_AND_INITIALISE_VARIABLE);

	return currentCodeBlockInTree;
}

NLCcodeblock * createCodeBlocksAddVariableToNewList(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* entity)
{
	currentCodeBlockInTree = createCodeBlocksDeclareNewLocalListVariable(currentCodeBlockInTree, entity);
	currentCodeBlockInTree = createCodeBlockAddPropertyToLocalList(currentCodeBlockInTree, entity, entity);

	return currentCodeBlockInTree;
}

#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS
void generateLocalFunctionArgumentsBasedOnImplicitDeclarations(vector<GIAentityNode*> * entityNodesActiveListComplete, vector<NLCitem*> * parameters)
{
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode * entity = *entityIter;
		if(assumedToAlreadyHaveBeenDeclared(entity))
		{
			if(!(entity->isConcept))
			{
				#ifdef NLC_SUPPORT_INPUT_FILE_LISTS
				if(!entity->NLCisSingularArgument)
				{
				#endif
					//cout << "generateLocalFunctionArgumentsBasedOnImplicitDeclarations: entity->entityName = " << entity->entityName << endl;
					//detected "the x" without declaring x (ie implicit declaration)
					NLCitem * thisFunctionArgumentInstanceItem = new NLCitem(entity, NLC_ITEM_TYPE_THIS_FUNCTION_ARGUMENT_INSTANCE_PLURAL);
					parameters->push_back(thisFunctionArgumentInstanceItem);
				#ifdef NLC_SUPPORT_INPUT_FILE_LISTS
				}
				#endif
			}
		}
	}
}
bool assumedToAlreadyHaveBeenDeclared(GIAentityNode* entity)
{
	bool isAssumedToAlreadyHaveBeenDeclared = false;
	if((entity->grammaticalDefiniteTemp) || (entity->grammaticalProperNounTemp) || entity->NLClocalListVariableHasBeenInitialised || entity->NLCisSingularArgument)
	{
		isAssumedToAlreadyHaveBeenDeclared = true;
		/*
		cout << "entity->grammaticalDefiniteTemp = " << entity->grammaticalDefiniteTemp << endl;
		cout << "entity->grammaticalProperNounTemp = " << entity->grammaticalProperNounTemp << endl;
		cout << "entity->NLClocalListVariableHasBeenInitialised = " << entity->NLClocalListVariableHasBeenInitialised << endl;
		cout << "entity->NLCisSingularArgument = " << entity->NLCisSingularArgument << endl;
		*/
	}
	return isAssumedToAlreadyHaveBeenDeclared;
}
#endif


/*
NLCcodeblock * createCodeBlockForStatements(NLCcodeblock * currentCodeBlockInTree, NLCitem * item, GIAentityNode* entity, int sentenceIndex)
{
	for(int i=0; i<GIA_ENTITY_NUMBER_OF_VECTOR_CONNECTION_TYPES; i++)
	{
		if(codeBlockTypeIfStatementArrayUseVectorEntityConnection[i])
		{
			for(vector<GIAentityConnection*>::iterator connectionIter = entityNode->entityVectorConnectionsArray[i].begin(); connectionIter != entityNode->entityVectorConnectionsArray[i].end(); connectionIter++)
			{

			}
		}
	}
}
*/




NLCcodeblock * createCodeBlock(NLCcodeblock * currentCodeBlockInTree, int codeBlockType)
{
	#ifdef NLC_DEBUG
	cout << "createCodeBlock [" << codeBlockType << "] = " << currentCodeBlockInTree->codeBlockType << endl;
	#endif
	currentCodeBlockInTree->codeBlockType = codeBlockType;
	currentCodeBlockInTree->next = new NLCcodeblock();

	if(codeBlockType >= NLC_CODEBLOCK_TYPE_CONTAINERS)
	{
		currentCodeBlockInTree = createLowerLevel(currentCodeBlockInTree);
	}
	else
	{
		currentCodeBlockInTree = currentCodeBlockInTree->next;
	}
	return currentCodeBlockInTree;
}

NLCcodeblock * createLowerLevel(NLCcodeblock * currentCodeBlockInTree)
{
	currentCodeBlockInTree->lowerLevel = new NLCcodeblock();
	currentCodeBlockInTree = currentCodeBlockInTree->lowerLevel;
	return currentCodeBlockInTree;
}



bool getEntityContext(GIAentityNode * entity, vector<string> * context, bool includePresentObject, int sentenceIndex, bool markSameSentenceParentsAsParsed)
{
	if(includePresentObject)
	{
		string itemName = generateInstanceName(entity);
		context->push_back(itemName);
	}
	bool entityHasParent = false;
	bool stillSearching = true;
	GIAentityNode * currentEntity = entity;

	while(stillSearching)
	{
		if(!(currentEntity->propertyNodeReverseList->empty()))
		{
			entityHasParent = true;
			GIAentityNode * parentEntity = currentEntity;
			currentEntity = (currentEntity->propertyNodeReverseList->back())->entity;
			string itemName = generateInstanceName(currentEntity);
			if(markSameSentenceParentsAsParsed)
			{
				if(currentEntity->sentenceIndexTemp == sentenceIndex)
				{
					bool foundNode = false;
					GIAentityConnection * propertyConnection = findEntityNodePointerInVector(currentEntity, parentEntity, GIA_ENTITY_VECTOR_CONNECTION_TYPE_PROPERTIES, &foundNode);
					if(foundNode)
					{
						propertyConnection->NLCparsedForCodeBlocks = true;
					}
					else
					{
						cout << "getEntityContext() error: !foundNode" << endl;
					}
				}
			}
			//string itemName = currentEntity->entityName;	//OLD
			context->push_back(itemName);
		}
		else
		{
			stillSearching = false;
		}
	}
	return entityHasParent;
}


bool checkSentenceIndexParsingCodeBlocks(GIAentityNode * entity, GIAentityConnection * connection, int sentenceIndex, bool checkIfEntityHasBeenParsedForNLCcodeBlocks)
{
	bool result = false;
	//cout << "connection->sentenceIndexTemp = " << connection->sentenceIndexTemp << endl;
	#ifdef NLC_VERIFY_CONNECTIONS_SENTENCE_INDEX
	if(connection->sentenceIndexTemp == sentenceIndex)
	{
	#endif
		if(checkSentenceIndexParsingCodeBlocks(entity, sentenceIndex, checkIfEntityHasBeenParsedForNLCcodeBlocks))
		{
			result = true;
		}
	#ifdef NLC_VERIFY_CONNECTIONS_SENTENCE_INDEX
	}
	#endif
	return result;
}

bool checkSentenceIndexParsingCodeBlocks(GIAentityNode * entity, int sentenceIndex, bool checkIfEntityHasBeenParsedForNLCcodeBlocks)
{
	bool result = false;
	if(!checkIfEntityHasBeenParsedForNLCcodeBlocks || !(entity->NLCparsedForCodeBlocks))
	{
		#ifdef GIA_RECORD_WAS_REFERENCE_INFORMATION
		if((entity->sentenceIndexTemp == sentenceIndex) || (entity->wasReference))
		#else
		if(entity->sentenceIndexTemp == sentenceIndex)
		#endif
		{
			if(!(entity->disabled))
			{
				result = true;
			}
		}
	}
	return result;
}


bool checkDuplicateProperty(GIAentityNode * propertyEntity, GIAentityNode * childActionEntity)
{
	bool alreadyAdded = false;
	for(vector<GIAentityConnection*>::iterator propertyNodeListIterator = childActionEntity->propertyNodeList->begin(); propertyNodeListIterator < childActionEntity->propertyNodeList->end(); propertyNodeListIterator++)
	{
		GIAentityNode * propertyEntityLocal = (*propertyNodeListIterator)->entity;
		if((propertyEntity->entityName == propertyEntityLocal->entityName))
		{
			alreadyAdded = true;
		}
	}
	return alreadyAdded;
}

bool checkDuplicateCondition(GIAentityNode * conditionEntity, GIAentityNode * childActionEntity)
{
	bool alreadyAdded = false;
	for(vector<GIAentityConnection*>::iterator conditionNodeListIterator = childActionEntity->conditionNodeList->begin(); conditionNodeListIterator < childActionEntity->conditionNodeList->end(); conditionNodeListIterator++)
	{
		GIAentityNode * conditionEntityLocal = (*conditionNodeListIterator)->entity;
		string conditionObjectEntityLocalName = "";
		if(!(conditionEntityLocal->conditionObjectEntity->empty()))
		{
			conditionObjectEntityLocalName = (conditionEntityLocal->conditionObjectEntity->back())->entity->entityName;
		}
		string conditionObjectEntityName = "";
		if(!(conditionEntity->conditionObjectEntity->empty()))
		{
			conditionObjectEntityName = (conditionEntity->conditionObjectEntity->back())->entity->entityName;
		}
		if((conditionEntity->entityName == conditionEntityLocal->entityName) && (conditionObjectEntityName == conditionObjectEntityLocalName))
		{
			alreadyAdded = true;
		}
	}
	return alreadyAdded;
}

#ifdef NLC_SUPPORT_INPUT_FILE_LISTS
string parseFunctionNameFromNLCfunctionName(string NLCfunctionName)
{
	//gets "fight" from "dog::fight"
	string functionName = "";
	bool foundFunctionOwnerClass = false;
	string functionOwnerName = "";
	parseFunctionNameFromNLCfunctionName(NLCfunctionName, &functionName, &functionOwnerName, &foundFunctionOwnerClass);
	return functionName;
}

void parseFunctionNameFromNLCfunctionName(string NLCfunctionName, string * functionName, string * functionOwnerName, bool * foundFunctionOwnerClass)
{
	//gets "fight" from "dog::fight"
	bool foundFunctionObjectClass = false;
	string functionObjectName = "";
	parseFunctionNameFromNLCfunctionName(NLCfunctionName, functionName, functionOwnerName, foundFunctionOwnerClass, &functionObjectName, &foundFunctionObjectClass);
}

void parseFunctionNameFromNLCfunctionName(string NLCfunctionName, string * functionName, string * functionOwnerName, bool * foundFunctionOwnerClass, string * functionObjectName, bool * foundFunctionObjectClass)
{
	//gets "fight" from "dog::fight"
	*foundFunctionOwnerClass = false;
	*functionOwnerName = "";
	*foundFunctionObjectClass = false;
	*functionObjectName = "";
	*functionName = NLCfunctionName;
	int indexOfActionName = NLCfunctionName.find(NLC_SUPPORT_INPUT_FILE_LISTS_ACTION_DELIMITER);
	int indexOfObjectName = NLCfunctionName.find(NLC_SUPPORT_INPUT_FILE_LISTS_ACTION_OBJECT_DELIMITER);
	if(indexOfActionName != string::npos)
	{
		if(indexOfObjectName != string::npos)
		{
			*functionName = NLCfunctionName.substr(indexOfActionName+NLC_SUPPORT_INPUT_FILE_LISTS_ACTION_DELIMITER_LENGTH, indexOfObjectName-indexOfActionName-NLC_SUPPORT_INPUT_FILE_LISTS_ACTION_DELIMITER_LENGTH);
			*functionOwnerName = NLCfunctionName.substr(0, indexOfActionName);
			*functionObjectName = NLCfunctionName.substr(indexOfObjectName+NLC_SUPPORT_INPUT_FILE_LISTS_ACTION_OBJECT_DELIMITER_LENGTH, NLCfunctionName.length()-indexOfObjectName-(NLC_SUPPORT_INPUT_FILE_LISTS_ACTION_OBJECT_DELIMITER_LENGTH));
			*foundFunctionOwnerClass = true;
			*foundFunctionObjectClass = true;
			/*
			cout << "parseFunctionNameFromNLCfunctionName():" << endl;
			cout << "NLCfunctionName = " << NLCfunctionName << endl;
			cout << "functionName = " << *functionName << endl;
			cout << "functionOwnerName = " << *functionOwnerName << endl;
			cout << "functionObjectName = " << *functionObjectName << endl;
			*/
		}
		else
		{
			*functionName = NLCfunctionName.substr(indexOfActionName+NLC_SUPPORT_INPUT_FILE_LISTS_ACTION_DELIMITER_LENGTH, NLCfunctionName.length()-indexOfActionName-NLC_SUPPORT_INPUT_FILE_LISTS_ACTION_DELIMITER_LENGTH);
			*functionOwnerName = NLCfunctionName.substr(0, indexOfActionName);
			*foundFunctionOwnerClass = true;
			cout << "parseFunctionNameFromNLCfunctionName():" << endl;
			cout << "NLCfunctionName = " << NLCfunctionName << endl;
			cout << "functionName = " << *functionName << endl;
			cout << "functionOwnerName = " << *functionOwnerName << endl;
		}
	}
	else if(indexOfObjectName != string::npos)
	{
		*functionName = NLCfunctionName.substr(0, indexOfObjectName);
		*functionObjectName = NLCfunctionName.substr(indexOfObjectName+NLC_SUPPORT_INPUT_FILE_LISTS_ACTION_OBJECT_DELIMITER_LENGTH, NLCfunctionName.length()-indexOfObjectName-(NLC_SUPPORT_INPUT_FILE_LISTS_ACTION_OBJECT_DELIMITER_LENGTH));
		*foundFunctionObjectClass = true;
		cout << "parseFunctionNameFromNLCfunctionName():" << endl;
		cout << "NLCfunctionName = " << NLCfunctionName << endl;
		cout << "functionName = " << *functionName << endl;
		cout << "functionObjectName = " << *functionObjectName << endl;
	}
	else
	{
		*functionName = NLCfunctionName;
	}
}
#endif

#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS

NLCcodeblock * createCodeBlockElse(NLCcodeblock * currentCodeBlockInTree)
{
	NLCitem * tempItem = new NLCitem("notUsedButNLCprintCodeBlocksRequiresAtLeastOneItem", NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(tempItem);
	int codeBlockType = NLC_CODEBLOCK_TYPE_ELSE;
	return createCodeBlock(currentCodeBlockInTree, codeBlockType);
}

NLCcodeblock * createCodeBlockLogicalConditionConjunctionOfBools(NLCcodeblock * currentCodeBlockInTree, int logicalOperation, NLClogicalConditionConjunction * logicalConditionConjunctionArray, int logicalConditionConjunctionIndexMax, int logicalConditionLevel, int logicalConditionCase, bool elseIfDetected)
{
	//cout << "logicalConditionConjunctionIndexMax = " << logicalConditionConjunctionIndexMax << endl;
	for(int i=0; i<logicalConditionConjunctionIndexMax; i++)
	{
		string logicalConditionConjunctionBooleanName = generateLogicalConditionConjunctionBooleanName(logicalConditionLevel, logicalConditionCase, i, logicalOperation);
		NLCitem * conditionItem = new NLCitem(logicalConditionConjunctionBooleanName, NLC_ITEM_TYPE_VARIABLE);
		conditionItem->conjunctionType = logicalConditionConjunctionArray[i].conjunctionType;
		conditionItem->negative = logicalConditionConjunctionArray[i].negative;
		//cout << "currentCodeBlockInTree->parameters.push_back(conditionItem)" << endl;
		currentCodeBlockInTree->parameters.push_back(conditionItem);
		//cout << "done currentCodeBlockInTree->parameters.push_back(conditionItem)" << endl;
	}

	int codeBlockType;
	if(logicalOperation == NLC_LOGICAL_CONDITION_OPERATIONS_IF)
	{
		if(elseIfDetected)
		{
			codeBlockType = NLC_CODEBLOCK_TYPE_ELSE_IF_LOGICAL_CONJUNCTION_OF_BOOLS;
		}
		else
		{
			codeBlockType = NLC_CODEBLOCK_TYPE_IF_LOGICAL_CONJUNCTION_OF_BOOLS;
		}
	}
	else if(logicalOperation == NLC_LOGICAL_CONDITION_OPERATIONS_WHILE)
	{//not currently used
		codeBlockType = NLC_CODEBLOCK_TYPE_WHILE_LOGICAL_CONJUNCTION_OF_BOOLS;
	}
	else
	{
		cout << "createCodeBlockLogicalConditionHasBools() error: invalid logicalOperation: " << logicalOperation << endl;
	}

	return createCodeBlock(currentCodeBlockInTree, codeBlockType);
}

string generateLogicalConditionConjunctionBooleanName(int logicalConditionLevel, int logicalConditionCase, int logicalOperation)
{
	string logicalConditionConjunctionBooleanName = "";
	if(logicalOperation == NLC_LOGICAL_CONDITION_OPERATIONS_IF)
	{
		logicalConditionConjunctionBooleanName = string(NLC_LOGICAL_CONDITION_CONJUNCTION_BOOLEAN_VARIABLE_NAME) + string(NLC_LOGICAL_CONDITION_CONJUNCTION_BOOLEAN_VARIABLE_NAME_LEVEL) + convertIntToString(logicalConditionLevel) + string(NLC_LOGICAL_CONDITION_CONJUNCTION_BOOLEAN_VARIABLE_NAME_CASE) + convertIntToString(logicalConditionCase);
	}
	else if(logicalOperation == NLC_LOGICAL_CONDITION_OPERATIONS_WHILE)
	{
		logicalConditionConjunctionBooleanName = string(NLC_LOGICAL_CONDITION_CONJUNCTION_BOOLEAN_VARIABLE_NAME) + string(NLC_LOGICAL_CONDITION_CONJUNCTION_BOOLEAN_VARIABLE_NAME_LEVEL) + convertIntToString(logicalConditionLevel);
	}
	else
	{
		cout << "generateLogicalConditionConjunctionBooleanName() error: invalid logicalOperation: " << logicalOperation << endl;
	}
	
	return logicalConditionConjunctionBooleanName;
}


string generateLogicalConditionConjunctionBooleanName(int logicalConditionLevel, int logicalConditionCase, int logicalConditionConjunctionIndex, int logicalOperation)
{
	string logicalConditionConjunctionBooleanName = "";
	if(logicalOperation == NLC_LOGICAL_CONDITION_OPERATIONS_IF)
	{
		logicalConditionConjunctionBooleanName = string(NLC_LOGICAL_CONDITION_CONJUNCTION_BOOLEAN_VARIABLE_NAME) + string(NLC_LOGICAL_CONDITION_CONJUNCTION_BOOLEAN_VARIABLE_NAME_LEVEL) + convertIntToString(logicalConditionLevel) + string(NLC_LOGICAL_CONDITION_CONJUNCTION_BOOLEAN_VARIABLE_NAME_CASE) + convertIntToString(logicalConditionCase) + progLangArrayOpen[0] + convertIntToString(logicalConditionConjunctionIndex) + progLangArrayClose[0];
	}
	else if(logicalOperation == NLC_LOGICAL_CONDITION_OPERATIONS_WHILE)
	{
		logicalConditionConjunctionBooleanName = string(NLC_LOGICAL_CONDITION_CONJUNCTION_BOOLEAN_VARIABLE_NAME) + string(NLC_LOGICAL_CONDITION_CONJUNCTION_BOOLEAN_VARIABLE_NAME_LEVEL) + convertIntToString(logicalConditionLevel) + progLangArrayOpen[0] + convertIntToString(logicalConditionConjunctionIndex) + progLangArrayClose[0];	
	}
	else
	{
		cout << "generateLogicalConditionConjunctionBooleanName() error: invalid logicalOperation: " << logicalOperation << endl;
	}
	return logicalConditionConjunctionBooleanName;
}

NLCcodeblock * createCodeBlockDeclareNewBoolArray(NLCcodeblock * currentCodeBlockInTree, string boolArrayName, bool value)
{
	NLCitem * itemDeclareNewBoolVariable = new NLCitem(boolArrayName, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(itemDeclareNewBoolVariable);
	int codeBlockType;
	if(value)
	{
		codeBlockType = NLC_CODEBLOCK_TYPE_DECLARE_NEW_BOOL_ARRAY_INITIALISE_TRUE;
	}
	else
	{
		codeBlockType = NLC_CODEBLOCK_TYPE_DECLARE_NEW_BOOL_ARRAY_INITIALISE_FALSE;
	}
	return createCodeBlock(currentCodeBlockInTree, codeBlockType);
}
#else

NLCcodeblock * createCodeBlockIfHasProperty(NLCcodeblock * currentCodeBlockInTree, NLCitem * itemProperty, bool negative)
{
	currentCodeBlockInTree->parameters.push_back(itemProperty);
	int codeBlockType = NLC_CODEBLOCK_TYPE_IF_HAS_PROPERTY;
	if(negative)
	{
		itemProperty->negative = true;
	}
	return createCodeBlock(currentCodeBlockInTree, codeBlockType);
}

NLCcodeblock * createCodeBlockIfHasCondition(NLCcodeblock * currentCodeBlockInTree, NLCitem * itemCondition, NLCitem * itemConditionObject, bool negative)
{
	currentCodeBlockInTree->parameters.push_back(itemCondition);
	currentCodeBlockInTree->parameters.push_back(itemConditionObject);
	int codeBlockType = NLC_CODEBLOCK_TYPE_IF_HAS_CONDITION;
	if(negative)
	{
		itemCondition->negative = true;
	}
	return createCodeBlock(currentCodeBlockInTree, codeBlockType);
}

NLCcodeblock * createCodeBlockWhileHasProperty(NLCcodeblock * currentCodeBlockInTree, NLCitem * itemProperty, bool negative)
{
	currentCodeBlockInTree->parameters.push_back(itemProperty);
	int codeBlockType = NLC_CODEBLOCK_TYPE_WHILE_HAS_PROPERTY;
	if(negative)
	{
		itemProperty->negative = true;
	}
	return createCodeBlock(currentCodeBlockInTree, codeBlockType);
}

NLCcodeblock * createCodeBlockWhileHasCondition(NLCcodeblock * currentCodeBlockInTree, NLCitem * itemCondition, NLCitem * itemConditionObject, bool negative)
{
	currentCodeBlockInTree->parameters.push_back(itemCondition);
	currentCodeBlockInTree->parameters.push_back(itemConditionObject);
	int codeBlockType = NLC_CODEBLOCK_TYPE_WHILE_HAS_CONDITION;
	if(negative)
	{
		itemCondition->negative = true;
	}
	return createCodeBlock(currentCodeBlockInTree, codeBlockType);
}
#endif
#endif

NLCcodeblock * createCodeBlockWhileHasBool(NLCcodeblock * currentCodeBlockInTree, string whileLogicalConditionConjunctionBooleanName)
{
	NLCitem * conditionItem = new NLCitem(whileLogicalConditionConjunctionBooleanName, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(conditionItem);
	int codeBlockType = NLC_CODEBLOCK_TYPE_WHILE;
	return createCodeBlock(currentCodeBlockInTree, codeBlockType);
}

//logicalConditionLevel is defined based on user tab indenting of text file, as parsed by NLC preprocessor
string generateWhileLogicalConditionConjunctionBooleanName(int logicalConditionLevel)
{
	string whileLogicalConditionConjunctionBooleanName = string(NLC_WHILE_LOGICAL_CONDITION_CONJUNCTION_BOOLEAN_VARIABLE_NAME) + convertIntToString(logicalConditionLevel);
	return whileLogicalConditionConjunctionBooleanName;
}

NLCcodeblock * createCodeBlockDeclareNewBoolVar(NLCcodeblock * currentCodeBlockInTree, string boolVariableName, bool value)
{
	NLCitem * itemDeclareNewBoolVariable = new NLCitem(boolVariableName, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(itemDeclareNewBoolVariable);
	int codeBlockType;
	if(value)
	{
		codeBlockType = NLC_CODEBLOCK_TYPE_DECLARE_NEW_BOOL_VARIABLE_INITIALISE_TRUE;
	}
	else
	{
		codeBlockType = NLC_CODEBLOCK_TYPE_DECLARE_NEW_BOOL_VARIABLE_INITIALISE_FALSE;
	}
	return createCodeBlock(currentCodeBlockInTree, codeBlockType);
}

NLCcodeblock * createCodeBlockSetBoolVar(NLCcodeblock * currentCodeBlockInTree, string boolVariableName, bool value)
{
	NLCitem * itemSetBoolVariable = new NLCitem(boolVariableName, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(itemSetBoolVariable);
	int codeBlockType;
	if(value)
	{
		codeBlockType = NLC_CODEBLOCK_TYPE_SET_BOOL_VARIABLE_TRUE;
	}
	else
	{
		codeBlockType = NLC_CODEBLOCK_TYPE_SET_BOOL_VARIABLE_FALSE;
	}
	return createCodeBlock(currentCodeBlockInTree, codeBlockType);
}

NLCcodeblock * createCodeBlockDebug(NLCcodeblock * currentCodeBlockInTree, string warning)
{
	NLCitem * debugItem = new NLCitem(warning, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(debugItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_DEBUG;
	currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}

#ifdef NLC_TRANSLATE_NEGATIVE_PROPERTIES_AND_CONDITIONS
NLCcodeblock * createCodeBlockRemoveProperties(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* propertyEntity)
{
	NLCitem * entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	NLCitem * propertyItem = new NLCitem(propertyEntity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(propertyItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_REMOVE_PROPERTIES;
	currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}

NLCcodeblock * createCodeBlockRemovePropertiesFromLocalList(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* entity)
{
	NLCitem * entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
	currentCodeBlockInTree->parameters.push_back(entityItem);

	int codeBlockType = NLC_CODEBLOCK_TYPE_REMOVE_PROPERTIES_FROM_LOCAL_LIST;
	currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}

NLCcodeblock * createCodeBlockRemoveConditions(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* conditionEntity)
{
	if(!(conditionEntity->conditionObjectEntity->empty()))
	{
		NLCitem * entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
		//removed 1e7c as it is not used: getEntityContext(entity, &(entityItem->context), false, sentenceIndex, false);
		currentCodeBlockInTree->parameters.push_back(entityItem);

		NLCitem * conditionItem = new NLCitem(conditionEntity, NLC_ITEM_TYPE_OBJECT);
		currentCodeBlockInTree->parameters.push_back(conditionItem);

		GIAentityNode * conditionObject = (conditionEntity->conditionObjectEntity->back())->entity;
		NLCitem * conditionObjectItem = new NLCitem(conditionObject, NLC_ITEM_TYPE_OBJECT);
		currentCodeBlockInTree->parameters.push_back(conditionObjectItem);

		int codeBlockType = NLC_CODEBLOCK_TYPE_REMOVE_CONDITIONS;
		currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);
	}
	else
	{
		cout << "error: condition does not have object" << endl;
	}

	return currentCodeBlockInTree;
}
#endif

#ifdef NLC_PREPROCESSOR_MATH
NLCcodeblock * createCodeBlockMathTextLine(NLCcodeblock * currentCodeBlockInTree, string mathText)
{
	NLCitem * mathTextItem = new NLCitem(mathText, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(mathTextItem);
	
	int codeBlockType = NLC_CODEBLOCK_TYPE_MATHTEXT_LINE;
	currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}

NLCcodeblock * createCodeBlockMathTextWithLogicalOperator(NLCcodeblock * currentCodeBlockInTree, string mathText)
{
	if(!(currentCodeBlockInTree->parameters.empty()))
	{
		cout << "error: !(currentCodeBlockInTree->parameters.empty())" << endl;
	}
	NLCitem * mathTextItem = new NLCitem(mathText, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(mathTextItem);
		
	int codeBlockType = NLC_CODEBLOCK_TYPE_MATHTEXT_WITH_LOGICAL_OPERATOR;
	currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}
#endif

NLCcodeblock * createCodeBlockDeclareNewIntVar(NLCcodeblock * currentCodeBlockInTree, string intVariableName, int value)
{
	NLCitem * intNameItem = new NLCitem(intVariableName, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(intNameItem);
	//cout << "intVariableName = " << intVariableName << endl;

	string intValueString = convertIntToString(value);
	NLCitem * intValueItem = new NLCitem(intValueString, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(intValueItem);
	//cout << "intValueString = " << intValueString << endl;
		
	int codeBlockType = NLC_CODEBLOCK_TYPE_DECLARE_NEW_INT_VARIABLE;

	return createCodeBlock(currentCodeBlockInTree, codeBlockType);
}

NLCcodeblock * createCodeBlockIncrementIntVar(NLCcodeblock * currentCodeBlockInTree, string intVariableName)
{	
	NLCitem * intNameItem = new NLCitem(intVariableName, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(intNameItem);
	
	int codeBlockType = NLC_CODEBLOCK_TYPE_INCREMENT_INT_VARIABLE;

	return createCodeBlock(currentCodeBlockInTree, codeBlockType);
}

NLCcodeblock * createCodeBlockCommentSingleLine(NLCcodeblock * currentCodeBlockInTree, string comment)
{
	NLCitem * item = new NLCitem(comment, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(item);

	int codeBlockType = NLC_CODEBLOCK_TYPE_COMMENT_SINGLE_LINE;
	currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);

	return currentCodeBlockInTree;
}


void clearCodeBlock(NLCcodeblock * codeBlock)
{
	codeBlock->codeBlockType = NLC_CODEBLOCK_TYPE_UNDEFINED;
	codeBlock->next = NULL;
	codeBlock->lowerLevel = NULL;
	codeBlock->parameters.clear();
	if(!(codeBlock->parameters.empty()))
	{
		cout << "error: !(codeBlock->parameters.empty())" << endl;
	}	
}


