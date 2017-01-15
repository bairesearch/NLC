/*******************************************************************************
 *
 * This file is part of BAIPROJECT.
 *
 * BAIPROJECT is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License version 3
 * only, as published by the Free Software Foundation. The use of
 * intermediary programs or interfaces including file i/o is considered
 * remote network interaction.
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
 * Project Version: 1f13b 17-April-2014
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/




#include "NLCcodeBlockClass.h"
#include "GIAtranslatorOperations.h"


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

NLCcodeblock * createCodeBlockForStatements(NLCcodeblock * currentCodeBlockInTree, NLCitem * item, GIAentityNode* entity, int sentenceIndex)
{
	//LIMITATION: only parse 1 sub level of conditions:

	//if object near a red car / if object has a red car (if object has a car which is red)
	//if(item->has(property) && item->has(property1) etc..){
	currentCodeBlockInTree = createCodeBlockForGivenProperties(currentCodeBlockInTree, item, entity, sentenceIndex);

	//if object near a car that is behind the driveway / if object has a car that is near the house 
	//if(item > 3){		/	if(greaterthan(item, 3)){
	currentCodeBlockInTree = createCodeBlockForGivenConditions(currentCodeBlockInTree, item, entity, sentenceIndex);

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
}		

NLCcodeblock * createCodeBlockForGivenProperties(NLCcodeblock * currentCodeBlockInTree, NLCitem * item, GIAentityNode * entity, int sentenceIndex)
{
	for(vector<GIAentityConnection*>::iterator propertyNodeListIterator = entity->propertyNodeList->begin(); propertyNodeListIterator < entity->propertyNodeList->end(); propertyNodeListIterator++)
	{
		GIAentityConnection * propertyConnection = (*propertyNodeListIterator);
		//if(!(propertyConnection->parsedForNLCcodeBlocks))	//removed 1e5b
		//{			
			GIAentityNode* propertyEntity = propertyConnection->entity;
			if(checkSentenceIndexParsingCodeBlocks(propertyEntity,  sentenceIndex, false))	//changed from true to false 1e5b
			{//only write conditions that are explicated in current sentence
				//cout << "createCodeBlockForGivenProperties: " << propertyEntity->entityName << endl;
				currentCodeBlockInTree = createCodeBlockForGivenProperty(currentCodeBlockInTree, item, propertyEntity, sentenceIndex);
				propertyConnection->parsedForNLCcodeBlocks = true;
			}
		//}
	}
	return currentCodeBlockInTree;
}
NLCcodeblock * createCodeBlockForGivenProperty(NLCcodeblock * currentCodeBlockInTree, NLCitem * item, GIAentityNode* propertyEntity, int sentenceIndex)
{
	NLCitem * propertyItem = new NLCitem(propertyEntity, NLC_ITEM_TYPE_CLASS);
	
	if(assumedToAlreadyHaveBeenDeclared(propertyEntity))
	{
		currentCodeBlockInTree = createCodeBlockForPropertyListLocal(currentCodeBlockInTree, propertyItem);
	}
	else
	{
		//cout << "createCodeBlockForGivenProperty: propertyEntity = " << propertyEntity->entityName << endl;
		propertyItem->context.push_back(item->instanceName);
		currentCodeBlockInTree = createCodeBlockForPropertyList(currentCodeBlockInTree, propertyItem);
	}
	
	currentCodeBlockInTree = createCodeBlockForStatements(currentCodeBlockInTree, propertyItem, propertyEntity, sentenceIndex);
	return currentCodeBlockInTree;
}

NLCcodeblock * createCodeBlockForGivenConditions(NLCcodeblock * currentCodeBlockInTree, NLCitem * item,  GIAentityNode * entity, int sentenceIndex)
{
	//cout << "createCodeBlockForGivenConditions: " << endl;
	for(vector<GIAentityConnection*>::iterator conditionNodeListIterator = entity->conditionNodeList->begin(); conditionNodeListIterator < entity->conditionNodeList->end(); conditionNodeListIterator++)
	{
		GIAentityConnection * conditionConnection = (*conditionNodeListIterator);
		//if(!(conditionConnection->parsedForNLCcodeBlocks))	//removed 1e5b
		//{
			GIAentityNode* conditionEntity = conditionConnection->entity;
			if(checkSentenceIndexParsingCodeBlocks(conditionEntity,  sentenceIndex, false))	//changed from true to false 1e5b
			{	
				currentCodeBlockInTree = createCodeBlockForGivenCondition(currentCodeBlockInTree, item, conditionEntity, sentenceIndex);
				conditionConnection->parsedForNLCcodeBlocks = true;
			}
		//}			
	}
	return currentCodeBlockInTree;
}
NLCcodeblock * createCodeBlockForGivenCondition(NLCcodeblock * currentCodeBlockInTree, NLCitem * item, GIAentityNode* conditionEntity, int sentenceIndex)
{
	if(!(conditionEntity->conditionObjectEntity->empty()))
	{
		GIAentityNode * conditionObject = (conditionEntity->conditionObjectEntity->back())->entity;

		NLCitem * conditionItem = new NLCitem(conditionEntity, NLC_ITEM_TYPE_CLASS);
		NLCitem * conditionObjectItem = new NLCitem(conditionObject, NLC_ITEM_TYPE_CLASS);
		
		conditionItem->context.push_back(item->instanceName);
		conditionObjectItem->context.push_back(item->instanceName);	//redundant
		currentCodeBlockInTree = createCodeBlockForConditionList(currentCodeBlockInTree, conditionItem, conditionObjectItem);

		//cout << "createCodeBlockForGivenCondition: " << conditionObjectItem->instanceName << endl;
		currentCodeBlockInTree = createCodeBlockForStatements(currentCodeBlockInTree, conditionObjectItem, conditionObject, sentenceIndex);
	}
	else
	{
		cout << "error createCodeBlockForGivenCondition(): condition does not have object" << endl;
	}
	return currentCodeBlockInTree;
}


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


