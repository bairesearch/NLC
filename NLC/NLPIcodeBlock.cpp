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
 * File Name: NLPIcodeBlock.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2013 Baxter AI (baxterai.com)
 * Project: Natural Language Programming Interface (compiler)
 * Project Version: 1e6b 23-November-2013
 * Requirements: requires text parsed by NLP Parser (eg Relex; available in .CFF format <relations>)
 *
 *******************************************************************************/




#include "NLPIcodeBlock.h"
#include "GIAtranslatorOperations.h"


NLPIcodeblock::NLPIcodeblock(void)
{
	codeBlockType = NLPI_CODEBLOCK_TYPE_UNDEFINED;
	
	/*
	//used by language specific code generator (eg C++, java);
	codeBlockName = ""; 	//eg "for"
	openingText = "";	//eg "for(...){"
	closingText = ""; 	//eg "}";
	*/
	
	lowerLevel = NULL;
	next = NULL;	
}
NLPIcodeblock::~NLPIcodeblock(void)
{
}



//Resultant code: functionItem[context].functionItem[name](objectItem[context].objectItem[name]);	//NB functionItem[context] = action subject
NLPIcodeblock * createCodeBlockExecute(NLPIcodeblock * currentCodeBlockInTree, NLPIitem * functionItem, NLPIitem* objectItem)
{
	currentCodeBlockInTree->parameters.push_back(functionItem);
	currentCodeBlockInTree->parameters.push_back(objectItem);

	return createCodeBlock(currentCodeBlockInTree, NLPI_CODEBLOCK_TYPE_EXECUTE_FUNCTION);
}

NLPIcodeblock * createCodeBlockExecute(NLPIcodeblock * currentCodeBlockInTree, NLPIitem * functionItem)
{
	currentCodeBlockInTree->parameters.push_back(functionItem);

	return createCodeBlock(currentCodeBlockInTree, NLPI_CODEBLOCK_TYPE_EXECUTE_FUNCTION);
}

//add property
NLPIcodeblock * createCodeBlockAddNewProperty(NLPIcodeblock * currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* propertyEntity, int sentenceIndex)
{
	NLPIitem * entityItem = new NLPIitem(entity, NLPI_ITEM_TYPE_OBJECT);
	getEntityContext(entity, &(entityItem->context), false, sentenceIndex, false);
	currentCodeBlockInTree->parameters.push_back(entityItem);
	
	NLPIitem * propertyItem = new NLPIitem(propertyEntity, NLPI_ITEM_TYPE_OBJECT);
	getEntityContext(propertyEntity, &(propertyItem->context), false, sentenceIndex, false);
	currentCodeBlockInTree->parameters.push_back(propertyItem);
	
	int codeBlockType = NLPI_CODEBLOCK_TYPE_ADD_NEW_PROPERTY;
	currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);
	
	return currentCodeBlockInTree;
}

NLPIcodeblock * createCodeBlockAddProperty(NLPIcodeblock * currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* propertyEntity, int sentenceIndex)
{
	NLPIitem * entityItem = new NLPIitem(entity, NLPI_ITEM_TYPE_OBJECT);
	getEntityContext(entity, &(entityItem->context), false, sentenceIndex, false);
	currentCodeBlockInTree->parameters.push_back(entityItem);
	
	NLPIitem * propertyItem = new NLPIitem(propertyEntity, NLPI_ITEM_TYPE_OBJECT);
	getEntityContext(propertyEntity, &(propertyItem->context), false, sentenceIndex, false);
	currentCodeBlockInTree->parameters.push_back(propertyItem);
	
	int codeBlockType = NLPI_CODEBLOCK_TYPE_ADD_PROPERTY;
	currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);
	
	return currentCodeBlockInTree;
}

//add state
NLPIcodeblock * createCodeBlockAddNewCondition(NLPIcodeblock * currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* conditionEntity, int sentenceIndex)
{
	if(!(conditionEntity->conditionObjectEntity->empty()))
	{
		NLPIitem * entityItem = new NLPIitem(entity, NLPI_ITEM_TYPE_OBJECT);
		getEntityContext(entity, &(entityItem->context), false, sentenceIndex, false);
		currentCodeBlockInTree->parameters.push_back(entityItem);

		NLPIitem * conditionItem = new NLPIitem(conditionEntity, NLPI_ITEM_TYPE_OBJECT);
		currentCodeBlockInTree->parameters.push_back(conditionItem);

		GIAentityNode * conditionObject = (conditionEntity->conditionObjectEntity->back())->entity;
		NLPIitem * conditionObjectItem = new NLPIitem(conditionObject, NLPI_ITEM_TYPE_OBJECT);
		getEntityContext(conditionObject, &(conditionObjectItem->context), false, sentenceIndex, false);
		currentCodeBlockInTree->parameters.push_back(conditionObjectItem);

		int codeBlockType = NLPI_CODEBLOCK_TYPE_ADD_NEW_CONDITION;
		currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);
	}
	else
	{
		cout << "error: condition does not have object" << endl;
	}
	
	return currentCodeBlockInTree;
}

NLPIcodeblock * createCodeBlockAddCondition(NLPIcodeblock * currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* conditionEntity, int sentenceIndex)
{
	if(!(conditionEntity->conditionObjectEntity->empty()))
	{
		NLPIitem * entityItem = new NLPIitem(entity, NLPI_ITEM_TYPE_OBJECT);
		getEntityContext(entity, &(entityItem->context), false, sentenceIndex, false);
		currentCodeBlockInTree->parameters.push_back(entityItem);

		NLPIitem * conditionItem = new NLPIitem(conditionEntity, NLPI_ITEM_TYPE_OBJECT);
		currentCodeBlockInTree->parameters.push_back(conditionItem);

		GIAentityNode * conditionObject = (conditionEntity->conditionObjectEntity->back())->entity;
		NLPIitem * conditionObjectItem = new NLPIitem(conditionObject, NLPI_ITEM_TYPE_OBJECT);
		getEntityContext(conditionObject, &(conditionObjectItem->context), false, sentenceIndex, false);
		currentCodeBlockInTree->parameters.push_back(conditionObjectItem);

		int codeBlockType = NLPI_CODEBLOCK_TYPE_ADD_CONDITION;
		currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);
	}
	else
	{
		cout << "error: condition does not have object" << endl;
	}
	
	return currentCodeBlockInTree;
}

NLPIcodeblock * createCodeBlockAddNewListVariable(NLPIcodeblock * currentCodeBlockInTree, GIAentityNode* entity, int sentenceIndex)
{
	NLPIitem * entityItem = new NLPIitem(entity, NLPI_ITEM_TYPE_OBJECT);
	getEntityContext(entity, &(entityItem->context), false, sentenceIndex, false);
	currentCodeBlockInTree->parameters.push_back(entityItem);
	
	int codeBlockType = NLPI_CODEBLOCK_TYPE_CREATE_NEW_LIST_VARIABLE;
	currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);
	
	return currentCodeBlockInTree;
}




NLPIcodeblock * createCodeBlockForPropertyList(NLPIcodeblock * currentCodeBlockInTree, NLPIitem * item)
{
	currentCodeBlockInTree->parameters.push_back(item);
	int codeBlockType = NLPI_CODEBLOCK_TYPE_FOR_PROPERTY_LIST;
	return createCodeBlock(currentCodeBlockInTree, codeBlockType);
}

NLPIcodeblock * createCodeBlockForConditionList(NLPIcodeblock * currentCodeBlockInTree, NLPIitem * item, NLPIitem * objectItem)
{
	currentCodeBlockInTree->parameters.push_back(item);
	currentCodeBlockInTree->parameters.push_back(objectItem);
	int codeBlockType = NLPI_CODEBLOCK_TYPE_FOR_CONDITION_LIST;
	return createCodeBlock(currentCodeBlockInTree, codeBlockType);
}





NLPIcodeblock * createCodeBlockNewFunction(NLPIcodeblock * currentCodeBlockInTree, string NLPIfunctionName, vector<GIAentityNode*> * entityNodesActiveListComplete)
{	
	#ifdef NLPI_SUPPORT_INPUT_FILE_LISTS
	//gets "fight" from "dog::fight"
	string functionName = "";
	bool foundFunctionOwnerClass = false;
	string functionOwnerName = "";
	bool foundFunctionObjectClass = false;
	string functionObjectName = "";
	parseFunctionNameFromNLPIfunctionName(NLPIfunctionName, &functionName, &functionOwnerName, &foundFunctionOwnerClass, &functionObjectName, &foundFunctionObjectClass);
	
	GIAentityNode * functionOwner = NULL;
	GIAentityNode * functionObject = NULL;
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode * entity = *entityIter;
		if(!(entity->isConcept) && !(entity->isActionConcept) && !(entity->isSubstanceConcept))
		{
			if(entity->entityName == functionOwnerName)
			{
				entity->NLPIisSingularArgument = true;	//formalFunctionArgumentCorrespondsToActionSubjectUseThisAlias
				
				functionOwner = entity;
			}
			else if(entity->entityName == functionObjectName)
			{
				entity->NLPIisSingularArgument = true;
			
				functionObject = entity;
			}
			else if(entity->entityName == functionName)
			{
				entity->NLPIisSingularArgument = true;	//added 1e2c
			}
		}
	}	
	#else
	string functionName = NLPIfunctionName;
	#endif
	
	NLPIitem * functionItem = new NLPIitem(functionName, NLPI_ITEM_TYPE_FUNCTION);
	currentCodeBlockInTree->parameters.push_back(functionItem);
	#ifdef NLPI_SUPPORT_INPUT_FILE_LISTS
	if(foundFunctionOwnerClass)
	{
		NLPIitem * functionOwnerItem = new NLPIitem(functionOwnerName, NLPI_ITEM_TYPE_FUNCTION_OWNER);
		currentCodeBlockInTree->parameters.push_back(functionOwnerItem);	
	}
	#ifdef NLPI_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS
	if(foundFunctionObjectClass)	//added 21 November 2013
	{
		if(functionObject != NULL)
		{//functionObject is used by the function definition: use functionObject instance name
			//cout << "functionObjectName2 = " << functionObjectName << endl;
			NLPIitem * functionObjectItem = new NLPIitem(functionObject, NLPI_ITEM_TYPE_FUNCTION_OBJECT);	
			currentCodeBlockInTree->parameters.push_back(functionObjectItem);	
		}
		else
		{//functionObject is not used by the function definition
			NLPIitem * functionObjectItem = new NLPIitem(functionObjectName, NLPI_ITEM_TYPE_FUNCTION_OBJECT);
			currentCodeBlockInTree->parameters.push_back(functionObjectItem);			
		}
	}
	#endif
	#endif
	
	#ifdef NLPI_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS
	generateLocalFunctionArgumentsBasedOnImplicitDeclarations(entityNodesActiveListComplete, &(currentCodeBlockInTree->parameters));
	#endif
	
	currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, NLPI_CODEBLOCK_TYPE_NEW_FUNCTION);
	
	#ifdef NLPI_SUPPORT_INPUT_FILE_LISTS
	#ifdef NLPI_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS
	if(functionOwner != NULL)
	{
		//"Dog dog1 = this;"
		NLPIitem * functionOwnerItem = new NLPIitem(functionOwner, NLPI_ITEM_TYPE_OBJECT);
		currentCodeBlockInTree->parameters.push_back(functionOwnerItem);
		NLPIitem * actionSubjectInstanceReplacementItem = new NLPIitem(NLPI_SUPPORT_INPUT_FILE_LISTS_ACTION_SUBJECT_INSTANCE_REPLACEMENT_NAME, NLPI_ITEM_TYPE_OBJECT);
		currentCodeBlockInTree->parameters.push_back(actionSubjectInstanceReplacementItem);
		currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, NLPI_CODEBLOCK_TYPE_DECLARE_AND_INITIALISE_VARIABLE);
	}
	#endif
	#endif
	
	return currentCodeBlockInTree;
}

#ifdef NLPI_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS
void generateLocalFunctionArgumentsBasedOnImplicitDeclarations(vector<GIAentityNode*> * entityNodesActiveListComplete, vector<NLPIitem*> * parameters)
{
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode * entity = *entityIter;
		if(assumedToAlreadyHaveBeenDeclared(entity))
		{
			if(!(entity->isConcept))
			{	
				#ifdef NLPI_SUPPORT_INPUT_FILE_LISTS
				if(!entity->NLPIisSingularArgument)
				{
				#endif
					//detected "the x" without declaring x (ie implicit declaration)
					NLPIitem * thisFunctionArgumentInstanceItem = new NLPIitem(entity, NLPI_ITEM_TYPE_THIS_FUNCTION_ARGUMENT_INSTANCE_PLURAL);
					parameters->push_back(thisFunctionArgumentInstanceItem);
				#ifdef NLPI_SUPPORT_INPUT_FILE_LISTS
				}
				#endif
			}
		}
	}	
}
bool assumedToAlreadyHaveBeenDeclared(GIAentityNode* entity)
{
	bool isAssumedToAlreadyHaveBeenDeclared = false;
	if((entity->grammaticalDefiniteTemp) || (entity->grammaticalProperNounTemp))
	{
		isAssumedToAlreadyHaveBeenDeclared = true;
	}
	return isAssumedToAlreadyHaveBeenDeclared;
}
#endif


/*
NLPIcodeblock * createCodeBlockForStatements(NLPIcodeblock * currentCodeBlockInTree, NLPIitem * item, GIAentityNode* entity, int sentenceIndex)
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

NLPIcodeblock * createCodeBlockForStatements(NLPIcodeblock * currentCodeBlockInTree, NLPIitem * item, GIAentityNode* entity, int sentenceIndex)
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

NLPIcodeblock * createCodeBlockForGivenProperties(NLPIcodeblock * currentCodeBlockInTree, NLPIitem * item, GIAentityNode * entity, int sentenceIndex)
{
	for(vector<GIAentityConnection*>::iterator propertyNodeListIterator = entity->propertyNodeList->begin(); propertyNodeListIterator < entity->propertyNodeList->end(); propertyNodeListIterator++)
	{
		GIAentityConnection * propertyConnection = (*propertyNodeListIterator);
		//if(!(propertyConnection->parsedForNLPIcodeBlocks))	//removed 1e5b
		//{			
			GIAentityNode* propertyEntity = propertyConnection->entity;
			if(checkSentenceIndexParsingCodeBlocks(propertyEntity,  sentenceIndex, false))	//changed from true to false 1e5b
			{//only write conditions that are explicated in current sentence
				//cout << "createCodeBlockForGivenProperties: " << propertyEntity->entityName << endl;
				currentCodeBlockInTree = createCodeBlockForGivenProperty(currentCodeBlockInTree, item, propertyEntity, sentenceIndex);
				propertyConnection->parsedForNLPIcodeBlocks = true;
			}
		//}
	}
	return currentCodeBlockInTree;
}
NLPIcodeblock * createCodeBlockForGivenProperty(NLPIcodeblock * currentCodeBlockInTree, NLPIitem * item, GIAentityNode* propertyEntity, int sentenceIndex)
{
	NLPIitem * propertyItem = new NLPIitem(propertyEntity, NLPI_ITEM_TYPE_CLASS);
	propertyItem->context.push_back(item->instanceName);
	currentCodeBlockInTree = createCodeBlockForPropertyList(currentCodeBlockInTree, propertyItem);
	
	currentCodeBlockInTree = createCodeBlockForStatements(currentCodeBlockInTree, propertyItem, propertyEntity, sentenceIndex);
	return currentCodeBlockInTree;
}

NLPIcodeblock * createCodeBlockForGivenConditions(NLPIcodeblock * currentCodeBlockInTree, NLPIitem * item,  GIAentityNode * entity, int sentenceIndex)
{
	for(vector<GIAentityConnection*>::iterator conditionNodeListIterator = entity->conditionNodeList->begin(); conditionNodeListIterator < entity->conditionNodeList->end(); conditionNodeListIterator++)
	{
		GIAentityConnection * conditionConnection = (*conditionNodeListIterator);
		//if(!(conditionConnection->parsedForNLPIcodeBlocks))	//removed 1e5b
		//{
			GIAentityNode* conditionEntity = conditionConnection->entity;
			if(checkSentenceIndexParsingCodeBlocks(conditionEntity,  sentenceIndex, false))	//changed from true to false 1e5b
			{	
				currentCodeBlockInTree = createCodeBlockForGivenCondition(currentCodeBlockInTree, item, conditionEntity, sentenceIndex);
				conditionConnection->parsedForNLPIcodeBlocks = true;
			}
		//}			
	}
	return currentCodeBlockInTree;
}
NLPIcodeblock * createCodeBlockForGivenCondition(NLPIcodeblock * currentCodeBlockInTree, NLPIitem * item, GIAentityNode* conditionEntity, int sentenceIndex)
{
	if(!(conditionEntity->conditionObjectEntity->empty()))
	{
		GIAentityNode * conditionObject = (conditionEntity->conditionObjectEntity->back())->entity;

		NLPIitem * conditionItem = new NLPIitem(conditionEntity, NLPI_ITEM_TYPE_CLASS);
		NLPIitem * conditionObjectItem = new NLPIitem(conditionObject, NLPI_ITEM_TYPE_CLASS);
		conditionItem->context.push_back(item->instanceName);
		conditionObjectItem->context.push_back(item->instanceName);	//redundant
		currentCodeBlockInTree = createCodeBlockForConditionList(currentCodeBlockInTree, conditionItem, conditionObjectItem);
			
		currentCodeBlockInTree = createCodeBlockForStatements(currentCodeBlockInTree, conditionObjectItem, conditionObject, sentenceIndex);
	}
	else
	{
		cout << "error createCodeBlockForGivenCondition(): condition does not have object" << endl;
	}
	return currentCodeBlockInTree;
}


NLPIcodeblock * createCodeBlock(NLPIcodeblock * currentCodeBlockInTree, int codeBlockType)
{
	#ifdef NLPI_DEBUG
	cout << "createCodeBlock [" << codeBlockType << "] = " << currentCodeBlockInTree->codeBlockType << endl;
	#endif
	currentCodeBlockInTree->codeBlockType = codeBlockType;
	currentCodeBlockInTree->next = new NLPIcodeblock();
	
	if(codeBlockType >= NLPI_CODEBLOCK_TYPE_CONTAINERS)
	{
		currentCodeBlockInTree = createLowerLevel(currentCodeBlockInTree);
	}
	else
	{	
		currentCodeBlockInTree = currentCodeBlockInTree->next;
	}
	return currentCodeBlockInTree;
}

NLPIcodeblock * createLowerLevel(NLPIcodeblock * currentCodeBlockInTree)
{
	currentCodeBlockInTree->lowerLevel = new NLPIcodeblock();
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
						propertyConnection->parsedForNLPIcodeBlocks = true;
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


bool checkSentenceIndexParsingCodeBlocks(GIAentityNode * entity, int sentenceIndex, bool checkIfEntityHasBeenParsedForNLPIcodeBlocks)
{
	bool result = false;
	if(!checkIfEntityHasBeenParsedForNLPIcodeBlocks || !(entity->parsedForNLPIcodeBlocks))
	{
		#ifdef GIA_DRAW_PRINT_ENTITY_NODES_IN_ORDER_OF_SENTENCE_INDEX
		if((entity->sentenceIndexTemp == sentenceIndex) || (entity->wasReference))
		#else
		if(entity->sentenceIndexTemp == sentenceIndex)		
		#endif
		{
			result = true;
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

#ifdef NLPI_SUPPORT_INPUT_FILE_LISTS
string parseFunctionNameFromNLPIfunctionName(string NLPIfunctionName)
{
	//gets "fight" from "dog::fight"
	string functionName = "";
	bool foundFunctionOwnerClass = false;
	string functionOwnerName = "";
	parseFunctionNameFromNLPIfunctionName(NLPIfunctionName, &functionName, &functionOwnerName, &foundFunctionOwnerClass);	
	return functionName;
}

void parseFunctionNameFromNLPIfunctionName(string NLPIfunctionName, string * functionName, string * functionOwnerName, bool * foundFunctionOwnerClass)
{
	//gets "fight" from "dog::fight"
	bool foundFunctionObjectClass = false;
	string functionObjectName = "";
	parseFunctionNameFromNLPIfunctionName(NLPIfunctionName, functionName, functionOwnerName, foundFunctionOwnerClass, &functionObjectName, &foundFunctionObjectClass);	
}

void parseFunctionNameFromNLPIfunctionName(string NLPIfunctionName, string * functionName, string * functionOwnerName, bool * foundFunctionOwnerClass, string * functionObjectName, bool * foundFunctionObjectClass)
{
	//gets "fight" from "dog::fight"
	*foundFunctionOwnerClass = false;
	*functionOwnerName = "";
	*foundFunctionObjectClass = false;
	*functionObjectName = "";
	*functionName = NLPIfunctionName;
	int indexOfActionName = NLPIfunctionName.find(NLPI_SUPPORT_INPUT_FILE_LISTS_ACTION_DELIMITER);
	int indexOfObjectName = NLPIfunctionName.find(NLPI_SUPPORT_INPUT_FILE_LISTS_ACTION_OBJECT_DELIMITER);
	if(indexOfActionName != string::npos)
	{
		if(indexOfObjectName != string::npos)
		{
			*functionName = NLPIfunctionName.substr(indexOfActionName+NLPI_SUPPORT_INPUT_FILE_LISTS_ACTION_DELIMITER_LENGTH, indexOfObjectName-indexOfActionName-NLPI_SUPPORT_INPUT_FILE_LISTS_ACTION_DELIMITER_LENGTH);
			*functionOwnerName = NLPIfunctionName.substr(0, indexOfActionName);
			*functionObjectName = NLPIfunctionName.substr(indexOfObjectName+NLPI_SUPPORT_INPUT_FILE_LISTS_ACTION_OBJECT_DELIMITER_LENGTH, NLPIfunctionName.length()-indexOfObjectName-(NLPI_SUPPORT_INPUT_FILE_LISTS_ACTION_OBJECT_DELIMITER_LENGTH));
			*foundFunctionOwnerClass = true;
			*foundFunctionObjectClass = true;	
			/*
			cout << "parseFunctionNameFromNLPIfunctionName():" << endl;
			cout << "NLPIfunctionName = " << NLPIfunctionName << endl;
			cout << "functionName = " << *functionName << endl;
			cout << "functionOwnerName = " << *functionOwnerName << endl;
			cout << "functionObjectName = " << *functionObjectName << endl;	
			*/
		}
		else
		{
			*functionName = NLPIfunctionName.substr(indexOfActionName+NLPI_SUPPORT_INPUT_FILE_LISTS_ACTION_DELIMITER_LENGTH, NLPIfunctionName.length()-indexOfActionName-NLPI_SUPPORT_INPUT_FILE_LISTS_ACTION_DELIMITER_LENGTH);
			*functionOwnerName = NLPIfunctionName.substr(0, indexOfActionName);
			*foundFunctionOwnerClass = true;
			cout << "parseFunctionNameFromNLPIfunctionName():" << endl;
			cout << "NLPIfunctionName = " << NLPIfunctionName << endl;
			cout << "functionName = " << *functionName << endl;
			cout << "functionOwnerName = " << *functionOwnerName << endl;
		}
	}
	else if(indexOfObjectName != string::npos)
	{
		*functionName = NLPIfunctionName.substr(0, indexOfObjectName);
		*functionObjectName = NLPIfunctionName.substr(indexOfObjectName+NLPI_SUPPORT_INPUT_FILE_LISTS_ACTION_OBJECT_DELIMITER_LENGTH, NLPIfunctionName.length()-indexOfObjectName-(NLPI_SUPPORT_INPUT_FILE_LISTS_ACTION_OBJECT_DELIMITER_LENGTH));
		*foundFunctionObjectClass = true;
		cout << "parseFunctionNameFromNLPIfunctionName():" << endl;
		cout << "NLPIfunctionName = " << NLPIfunctionName << endl;
		cout << "functionName = " << *functionName << endl;
		cout << "functionObjectName = " << *functionObjectName << endl;	
	}
	else
	{
		*functionName = NLPIfunctionName;
	}
}
#endif


