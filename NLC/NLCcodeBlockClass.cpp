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
 * Project Version: 1g6g 09-July-2014
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/




#include "NLCcodeBlockClass.h"
#include "GIAtranslatorOperations.h"
#include "NLCprintDefs.h"	//required for progLangArrayOpen/progLangArrayClose



NLClogicalConditionConjunctionVariables::NLClogicalConditionConjunctionVariables(void)
{
	logicalOperation = NLC_CONDITION_LOGICAL_OPERATIONS_FOR;
	#ifndef NLC_LOGICAL_CONDITIONS_SUPPORT_CONJUNCTIONS
	negative = BOOL_IRRELEVANT;
	#endif
	logicalConditionConjunctionIndex = INT_DEFAULT_VALUE;
	primaryEntityInLogicalConditionConjunctionSubset = NULL;
	foundLogicalConditionConjunction = NULL;
}
NLClogicalConditionConjunctionVariables::~NLClogicalConditionConjunctionVariables(void)
{
}


NLClogicalConditionConjunction::NLClogicalConditionConjunction(void)
{
	conjunctionType = INT_DEFAULT_VALUE;
	negative = false;
}
NLClogicalConditionConjunction::~NLClogicalConditionConjunction(void)
{
}


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
NLCcodeblock * createCodeBlockAddNewProperty(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* propertyEntity, int sentenceIndex)
{
	#ifdef NLC_SUPPORT_QUANTITIES
	for(int i=0; i<propertyEntity->quantityNumber; i++)
	{
	#endif
		NLCitem * entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
		currentCodeBlockInTree->parameters.push_back(entityItem);

		NLCitem * propertyItem = new NLCitem(propertyEntity, NLC_ITEM_TYPE_OBJECT);
		currentCodeBlockInTree->parameters.push_back(propertyItem);

		int codeBlockType = NLC_CODEBLOCK_TYPE_ADD_NEW_PROPERTY;
		currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);
	#ifdef NLC_SUPPORT_QUANTITIES
	}
	#endif
	return currentCodeBlockInTree;
}

NLCcodeblock * createCodeBlockAddNewPropertyToLocalList(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* propertyEntity)
{
	#ifdef NLC_SUPPORT_QUANTITIES
	for(int i=0; i<propertyEntity->quantityNumber; i++)
	{
	#endif
		NLCitem * entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
		currentCodeBlockInTree->parameters.push_back(entityItem);

		NLCitem * propertyItem = new NLCitem(propertyEntity, NLC_ITEM_TYPE_OBJECT);
		currentCodeBlockInTree->parameters.push_back(propertyItem);

		int codeBlockType = NLC_CODEBLOCK_TYPE_ADD_NEW_PROPERTY_TO_LOCAL_LIST;
		currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);
	#ifdef NLC_SUPPORT_QUANTITIES
	}
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
NLCcodeblock * createCodeBlockAddNewCondition(NLCcodeblock * currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* conditionEntity, int sentenceIndex)
{
	if(!(conditionEntity->conditionObjectEntity->empty()))
	{
		GIAentityNode * conditionObject = (conditionEntity->conditionObjectEntity->back())->entity;

		#ifdef NLC_SUPPORT_QUANTITIES
		for(int i=0; i<conditionObject->quantityNumber; i++)
		{
		#endif

			NLCitem * entityItem = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
			currentCodeBlockInTree->parameters.push_back(entityItem);

			NLCitem * conditionItem = new NLCitem(conditionEntity, NLC_ITEM_TYPE_OBJECT);
			currentCodeBlockInTree->parameters.push_back(conditionItem);

			NLCitem * conditionObjectItem = new NLCitem(conditionObject, NLC_ITEM_TYPE_OBJECT);
			currentCodeBlockInTree->parameters.push_back(conditionObjectItem);

			int codeBlockType = NLC_CODEBLOCK_TYPE_ADD_NEW_CONDITION;
			currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);
		#ifdef NLC_SUPPORT_QUANTITIES
		}
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
				entity->parsedForNLCcodeBlocks = true;

				functionOwner = entity;
			}
			else if(entity->entityName == functionObjectName)
			{
				entity->NLCisSingularArgument = true;
				entity->parsedForNLCcodeBlocks = true;

				functionObject = entity;
			}
			else if(entity->entityName == functionName)
			{
				entity->NLCisSingularArgument = true;
				entity->parsedForNLCcodeBlocks = true;

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
	if((entity->grammaticalDefiniteTemp) || (entity->grammaticalProperNounTemp) || entity->NLClocalListVariableHasBeenDeclared || entity->NLCisSingularArgument)
	{
		isAssumedToAlreadyHaveBeenDeclared = true;
		/*
		cout << "entity->grammaticalDefiniteTemp = " << entity->grammaticalDefiniteTemp << endl;
		cout << "entity->grammaticalProperNounTemp = " << entity->grammaticalProperNounTemp << endl;
		cout << "entity->NLClocalListVariableHasBeenDeclared = " << entity->NLClocalListVariableHasBeenDeclared << endl;
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

bool createCodeBlockForStatements(NLCcodeblock ** currentCodeBlockInTree, string parentInstanceName, GIAentityNode* entity, int sentenceIndex, NLClogicalConditionConjunctionVariables * logicalConditionConjunctionVariables)
{
	//OLD? LIMITATION: only parse 1 sub level of conditions:
	bool result = false;
	
	//if object near a red car / if object has a red car (if object has a car which is red)
	//if(item->has(property) && item->has(property1) etc..){
	if(createCodeBlockForGivenProperties(currentCodeBlockInTree, parentInstanceName, entity, sentenceIndex, logicalConditionConjunctionVariables))
	{
		result = true;
	}

	//if object near a car that is behind the driveway / if object has a car that is near the house
	//if(item > 3){		/	if(greaterthan(item, 3)){
	if(createCodeBlockForGivenConditions(currentCodeBlockInTree, parentInstanceName, entity, sentenceIndex, logicalConditionConjunctionVariables))
	{
		result = true;
	}

	/*
	//if object near a car that is towed by a truck / if object has a car that is towed by a truck
	currentCodeBlockInTree = createCodeBlockIfIsActionObject(currentCodeBlockInTree, item, entity, sentenceIndex);

	//if object near a car that drives /if object has a car that drives
	currentCodeBlockInTree = createCodeBlockIfHasAction(currentCodeBlockInTree, item, entity, sentenceIndex);

	//if object near car that is a flyingCar
	currentCodeBlockInTree = createCodeBlockIfHasDefinition(currentCodeBlockInTree, item, entity, sentenceIndex);

	//if object near Tom's car
	currentCodeBlockInTree = createCodeBlockIfHasPropertyOwner(currentCodeBlockInTree, item, entity, sentenceIndex);
	*/
	return result;
}

bool createCodeBlockForGivenProperties(NLCcodeblock ** currentCodeBlockInTree, string parentInstanceName, GIAentityNode * entity, int sentenceIndex, NLClogicalConditionConjunctionVariables * logicalConditionConjunctionVariables)
{
	bool result = false;
	for(vector<GIAentityConnection*>::iterator propertyNodeListIterator = entity->propertyNodeList->begin(); propertyNodeListIterator < entity->propertyNodeList->end(); propertyNodeListIterator++)
	{
		GIAentityConnection * propertyConnection = (*propertyNodeListIterator);
		//if(!(propertyConnection->parsedForNLCcodeBlocks))	//removed 1e5b
		//{
			GIAentityNode* propertyEntity = propertyConnection->entity;
			if(checkSentenceIndexParsingCodeBlocks(propertyEntity,  sentenceIndex, false))	//changed from true to false 1e5b
			{//only write conditions that are explicated in current sentence
				#ifdef NLC_DEBUG2
				cout << "createCodeBlockForGivenProperties: " << propertyEntity->entityName << endl;
				#endif
				result = true;
				propertyConnection->parsedForNLCcodeBlocks = true;
				#ifdef generateContextBlocksAndInitialiseParentIfNecessary_PARSE_CHILD_PROPERTIES_AND_CONDITIONS_OF_CONTEXT_PARENT
				bool conjunctionConditionConnectionFound = hasConjunctionConditionConnection(propertyEntity, logicalConditionConjunctionVariables->primaryEntityInLogicalConditionConjunctionSubset, logicalConditionConjunctionVariables->logicalConditionConjunctionIndex, &(logicalConditionConjunctionVariables->foundLogicalConditionConjunction));	//dont need to test for mismatched logicalConditionConjunctionIndex; it is just for debugging
				if(!conjunctionConditionConnectionFound)
				{
				#endif
					createCodeBlockForGivenProperty(currentCodeBlockInTree, parentInstanceName, propertyEntity, sentenceIndex, logicalConditionConjunctionVariables);
					#ifdef NLC_LOGICAL_CONDITIONS_SUPPORT_CONJUNCTIONS
					propertyEntity->NLClogicalConditionConjunctionIndex = logicalConditionConjunctionVariables->logicalConditionConjunctionIndex;
					#endif
				#ifdef generateContextBlocksAndInitialiseParentIfNecessary_PARSE_CHILD_PROPERTIES_AND_CONDITIONS_OF_CONTEXT_PARENT
				}
				#endif
			}
		//}
	}
	return result;
}
bool createCodeBlockForGivenProperty(NLCcodeblock ** currentCodeBlockInTree, string parentInstanceName, GIAentityNode* propertyEntity, int sentenceIndex, NLClogicalConditionConjunctionVariables * logicalConditionConjunctionVariables)
{
	bool result = true;
	NLCitem * propertyItem = new NLCitem(propertyEntity, NLC_ITEM_TYPE_CLASS);

	//cout << "createCodeBlockForGivenProperty: propertyEntity = " << propertyEntity->entityName << endl;
	if(assumedToAlreadyHaveBeenDeclared(propertyEntity))
	{
		#ifndef NLC_LOGICAL_CONDITIONS_SUPPORT_CONJUNCTIONS
		if(logicalOperation == NLC_CONDITION_LOGICAL_OPERATIONS_FOR)
		{
		#endif
			*currentCodeBlockInTree = createCodeBlockForPropertyListLocal(*currentCodeBlockInTree, propertyItem);
		#ifndef NLC_LOGICAL_CONDITIONS_SUPPORT_CONJUNCTIONS
		}
		else if(logicalOperation == NLC_CONDITION_LOGICAL_OPERATIONS_IF)
		{
			*currentCodeBlockInTree = createCodeBlockIfHasPropertyLocal(*currentCodeBlockInTree, propertyItem, logicalConditionConjunctionVariables->negative);
		}
		else if(logicalOperation == NLC_CONDITION_LOGICAL_OPERATIONS_WHILE)
		{
			*currentCodeBlockInTree = createCodeBlockWhileHasPropertyLocal(*currentCodeBlockInTree, propertyItem, logicalConditionConjunctionVariables->negative);
		}	
		#endif
	}
	else
	{
		propertyItem->context.push_back(parentInstanceName);
		#ifndef NLC_LOGICAL_CONDITIONS_SUPPORT_CONJUNCTIONS
		if(logicalOperation == NLC_CONDITION_LOGICAL_OPERATIONS_FOR)
		{
		#endif
			*currentCodeBlockInTree = createCodeBlockForPropertyList(*currentCodeBlockInTree, propertyItem);
		#ifndef NLC_LOGICAL_CONDITIONS_SUPPORT_CONJUNCTIONS
		}
		else if(logicalOperation == NLC_CONDITION_LOGICAL_OPERATIONS_IF)
		{
			*currentCodeBlockInTree = createCodeBlockIfHasProperty(*currentCodeBlockInTree, propertyItem, logicalConditionConjunctionVariables->negative);
		}
		else if(logicalOperation == NLC_CONDITION_LOGICAL_OPERATIONS_WHILE)
		{
			*currentCodeBlockInTree = createCodeBlockWhileHasProperty(*currentCodeBlockInTree, propertyItem, logicalConditionConjunctionVariables->negative);
		}	
		#endif
	}
	createCodeBlockForStatements(currentCodeBlockInTree, propertyItem->instanceName, propertyEntity, sentenceIndex, logicalConditionConjunctionVariables);
	
	return result;
}

bool createCodeBlockForGivenConditions(NLCcodeblock ** currentCodeBlockInTree, string parentInstanceName,  GIAentityNode * entity, int sentenceIndex, NLClogicalConditionConjunctionVariables * logicalConditionConjunctionVariables)
{
	bool result = false;
	//cout << "createCodeBlockForGivenConditions: " << endl;
	for(vector<GIAentityConnection*>::iterator conditionNodeListIterator = entity->conditionNodeList->begin(); conditionNodeListIterator < entity->conditionNodeList->end(); conditionNodeListIterator++)
	{
		GIAentityConnection * conditionConnection = (*conditionNodeListIterator);
		//if(!(conditionConnection->parsedForNLCcodeBlocks))	//removed 1e5b
		//{
			GIAentityNode* conditionEntity = conditionConnection->entity;
			if(checkSentenceIndexParsingCodeBlocks(conditionEntity,  sentenceIndex, false))	//changed from true to false 1e5b
			{
				conditionConnection->parsedForNLCcodeBlocks = true;
				#ifdef NLC_LOGICAL_CONDITIONS_SUPPORT_CONJUNCTIONS
				bool conjunctionConditionFound = textInTextArray(conditionEntity->entityName, entityCoordinatingConjunctionArray, ENTITY_COORDINATINGCONJUNCTION_ARRAY_NUMBER_OF_TYPES);
				if(!conjunctionConditionFound)
				{//do not parse conjunction conditions
					#ifdef generateContextBlocksAndInitialiseParentIfNecessary_PARSE_CHILD_PROPERTIES_AND_CONDITIONS_OF_CONTEXT_PARENT
					bool conjunctionConditionConnectionFound = hasConjunctionConditionConnection(conditionEntity, logicalConditionConjunctionVariables->primaryEntityInLogicalConditionConjunctionSubset, logicalConditionConjunctionVariables->logicalConditionConjunctionIndex, &(logicalConditionConjunctionVariables->foundLogicalConditionConjunction));	//dont need to test for mismatched logicalConditionConjunctionIndex; it is just for debugging
					if(!conjunctionConditionConnectionFound)
					{
					#endif
				#endif
						#ifdef NLC_DEBUG2
						cout << "createCodeBlockForGivenConditions: " << conditionEntity->entityName << endl;
						#endif
						result = true;
						createCodeBlockForGivenCondition(currentCodeBlockInTree, parentInstanceName, conditionEntity, sentenceIndex, logicalConditionConjunctionVariables);
						#ifdef NLC_LOGICAL_CONDITIONS_SUPPORT_CONJUNCTIONS
						conditionEntity->NLClogicalConditionConjunctionIndex = logicalConditionConjunctionVariables->logicalConditionConjunctionIndex;
						#endif
				#ifdef NLC_LOGICAL_CONDITIONS_SUPPORT_CONJUNCTIONS
					#ifdef generateContextBlocksAndInitialiseParentIfNecessary_PARSE_CHILD_PROPERTIES_AND_CONDITIONS_OF_CONTEXT_PARENT
					}
					#endif
				}
				#ifdef generateContextBlocksAndInitialiseParentIfNecessary_PARSE_CHILD_PROPERTIES_AND_CONDITIONS_OF_CONTEXT_PARENT
				else
				{
					logicalConditionConjunctionVariables->foundLogicalConditionConjunction = conditionEntity;
				}
				#endif
				#endif
			}
		//}
	}
	return result;
}
bool createCodeBlockForGivenCondition(NLCcodeblock ** currentCodeBlockInTree, string parentInstanceName, GIAentityNode* conditionEntity, int sentenceIndex, NLClogicalConditionConjunctionVariables * logicalConditionConjunctionVariables)
{
	bool result = true;
	if(!(conditionEntity->conditionObjectEntity->empty()))
	{
		GIAentityNode * conditionObject = (conditionEntity->conditionObjectEntity->back())->entity;
		//cout << "conditionObject = " << conditionObject->entityName << endl;
		
		NLCitem * conditionItem = new NLCitem(conditionEntity, NLC_ITEM_TYPE_CLASS);
		NLCitem * conditionObjectItem = new NLCitem(conditionObject, NLC_ITEM_TYPE_CLASS);
		//cout << "createCodeBlockForGivenCondition: " << conditionObjectItem->instanceName << endl;

		conditionItem->context.push_back(parentInstanceName);
		conditionObjectItem->context.push_back(parentInstanceName);	//redundant
		
		#ifndef NLC_LOGICAL_CONDITIONS_SUPPORT_CONJUNCTIONS
		if(logicalOperation == NLC_CONDITION_LOGICAL_OPERATIONS_FOR)
		{
		#endif
			*currentCodeBlockInTree = createCodeBlockForConditionList(*currentCodeBlockInTree, conditionItem, conditionObjectItem);
		#ifndef NLC_LOGICAL_CONDITIONS_SUPPORT_CONJUNCTIONS
		}
		else if(logicalOperation == NLC_CONDITION_LOGICAL_OPERATIONS_IF)
		{
			*currentCodeBlockInTree = createCodeBlockIfHasCondition(*currentCodeBlockInTree, conditionItem, conditionObjectItem, logicalConditionConjunctionVariables->negative);
		}
		else if(logicalOperation == NLC_CONDITION_LOGICAL_OPERATIONS_WHILE)
		{
			*currentCodeBlockInTree = createCodeBlockWhileHasCondition(*currentCodeBlockInTree, conditionItem, conditionObjectItem, logicalConditionConjunctionVariables->negative);
		}
		#endif
		
		createCodeBlockForStatements(currentCodeBlockInTree, conditionObjectItem->instanceName, conditionObject, sentenceIndex, logicalConditionConjunctionVariables);
	}
	else
	{
		result = false;
		cout << "error createCodeBlockForGivenCondition(): condition does not have object" << endl;
	}
	return result;
}

#ifdef NLC_LOGICAL_CONDITIONS_SUPPORT_CONJUNCTIONS
#ifdef generateContextBlocksAndInitialiseParentIfNecessary_PARSE_CHILD_PROPERTIES_AND_CONDITIONS_OF_CONTEXT_PARENT
bool hasConjunctionConditionConnection(GIAentityNode * conditionEntity, GIAentityNode * primaryEntityInLogicalConditionConjunctionSubset, int logicalConditionConjunctionIndex, GIAentityNode ** foundLogicalConditionConjunction)	//dont need to test for mismatched logicalConditionConjunctionIndex; it is just for debugging
{
	bool conjunctionConditionConnectionFound = false;
	if(conditionEntity != primaryEntityInLogicalConditionConjunctionSubset)
	{//ignore primaryEntityInLogicalConditionConjunctionSubset
		for(vector<GIAentityConnection*>::iterator conditionNodeListIterator = conditionEntity->conditionNodeList->begin(); conditionNodeListIterator < conditionEntity->conditionNodeList->end(); conditionNodeListIterator++)
		{
			GIAentityConnection * conditionConnection = (*conditionNodeListIterator);
			GIAentityNode* conditionEntity2 = conditionConnection->entity;
			bool conjunctionConditionFound = textInTextArray(conditionEntity2->entityName, entityCoordinatingConjunctionArray, ENTITY_COORDINATINGCONJUNCTION_ARRAY_NUMBER_OF_TYPES);
			if(conjunctionConditionFound)
			{
				conjunctionConditionConnectionFound = true;
				*foundLogicalConditionConjunction = conditionEntity2;
			}
		}
		for(vector<GIAentityConnection*>::iterator conditionNodeListIterator = conditionEntity->incomingConditionNodeList->begin(); conditionNodeListIterator < conditionEntity->incomingConditionNodeList->end(); conditionNodeListIterator++)
		{
			GIAentityConnection * conditionConnection = (*conditionNodeListIterator);
			GIAentityNode* conditionEntity2 = conditionConnection->entity;
			bool conjunctionConditionFound = textInTextArray(conditionEntity2->entityName, entityCoordinatingConjunctionArray, ENTITY_COORDINATINGCONJUNCTION_ARRAY_NUMBER_OF_TYPES);
			if(conjunctionConditionFound)
			{
				conjunctionConditionConnectionFound = true;
				//*foundLogicalConditionConjunction = conditionEntity2;	//NB only parse conjunction conditions in forwards direction 
			}
		}
	}

	//for debugging only:
	if(!conjunctionConditionConnectionFound)
	{
		if((conditionEntity->NLClogicalConditionConjunctionIndex != logicalConditionConjunctionIndex) && (conditionEntity->NLClogicalConditionConjunctionIndex != INT_DEFAULT_VALUE))
		{
			cout << "hasConjunctionConditionConnection() error: child of primaryEntityInLogicalConditionConjunctionSubset has been declared as pertaining to a different logicalConditionConjunctionSubset - is this a shared context?" << endl;
		}
	}
		
	return conjunctionConditionConnectionFound;	
}
#endif
#endif


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
						propertyConnection->parsedForNLCcodeBlocks = true;
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


bool checkSentenceIndexParsingCodeBlocks(GIAentityNode * entity, int sentenceIndex, bool checkIfEntityHasBeenParsedForNLCcodeBlocks)
{
	bool result = false;
	if(!checkIfEntityHasBeenParsedForNLCcodeBlocks || !(entity->parsedForNLCcodeBlocks))
	{
		#ifdef GIA_DRAW_PRINT_ENTITY_NODES_IN_ORDER_OF_SENTENCE_INDEX
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

#ifdef NLC_LOGICAL_CONDITIONS_SUPPORT_CONJUNCTIONS
NLCcodeblock * createCodeBlockWhileHasBool(NLCcodeblock * currentCodeBlockInTree, string whileLogicalConditionConjunctionBooleanName)
{
	NLCitem * conditionItem = new NLCitem(whileLogicalConditionConjunctionBooleanName, NLC_ITEM_TYPE_VARIABLE);
	currentCodeBlockInTree->parameters.push_back(conditionItem);
	int codeBlockType = NLC_CODEBLOCK_TYPE_WHILE_LOGICAL_CONJUNCTION_OF_BOOLS;
	return createCodeBlock(currentCodeBlockInTree, codeBlockType);
}

NLCcodeblock * createCodeBlockLogicalConditionConjunctionOfBools(NLCcodeblock * currentCodeBlockInTree, int logicalOperation, NLClogicalConditionConjunction * logicalConditionConjunctionArray, int logicalConditionConjunctionIndexMax)
{
	//cout << "logicalConditionConjunctionIndexMax = " << logicalConditionConjunctionIndexMax << endl;
	for(int i=0; i<logicalConditionConjunctionIndexMax; i++)
	{
		string logicalConditionConjunctionBooleanName = generateLogicalConditionConjunctionBooleanName(i);
		NLCitem * conditionItem = new NLCitem(logicalConditionConjunctionBooleanName, NLC_ITEM_TYPE_VARIABLE);
		conditionItem->conjunctionType = logicalConditionConjunctionArray[i].conjunctionType;
		conditionItem->negative = logicalConditionConjunctionArray[i].negative;
		//cout << "currentCodeBlockInTree->parameters.push_back(conditionItem)" << endl;
		currentCodeBlockInTree->parameters.push_back(conditionItem);
		//cout << "done currentCodeBlockInTree->parameters.push_back(conditionItem)" << endl;
	}
							
	int codeBlockType;
	if(logicalOperation == NLC_CONDITION_LOGICAL_OPERATIONS_IF)
	{
		codeBlockType = NLC_CODEBLOCK_TYPE_IF_LOGICAL_CONJUNCTION_OF_BOOLS;
	}
	else if(logicalOperation == NLC_CONDITION_LOGICAL_OPERATIONS_WHILE)
	{
		codeBlockType = NLC_CODEBLOCK_TYPE_WHILE_LOGICAL_CONJUNCTION_OF_BOOLS;
	}
	else
	{
		cout << "createCodeBlockLogicalConditionHasBools() error: invalid logicalOperation: " << logicalOperation << endl;
	}
	
	return createCodeBlock(currentCodeBlockInTree, codeBlockType);
}
string generateLogicalConditionConjunctionBooleanName(int logicalConditionConjunctionIndex)
{
	string logicalConditionConjunctionBooleanName = string(NLC_LOGICAL_CONDITION_CONJUNCTION_BOOLEAN_VARIABLE_NAME) + progLangArrayOpen[0] + intToString(logicalConditionConjunctionIndex) + progLangArrayClose[0];
	return logicalConditionConjunctionBooleanName;
}

//logicalConditionLevel is defined based on user tab indenting of text file, as parsed by NLC preprocessor
string generateWhileLogicalConditionConjunctionBooleanName(int logicalConditionLevel)
{
	string whileLogicalConditionConjunctionBooleanName = string(NLC_WHILE_LOGICAL_CONDITION_CONJUNCTION_BOOLEAN_VARIABLE_NAME) + intToString(logicalConditionLevel);
	return whileLogicalConditionConjunctionBooleanName;
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




string intToString(int integer)
{
	char stringCharStar[100];
	sprintf(stringCharStar, "%d", integer);
	return string(stringCharStar);
}





