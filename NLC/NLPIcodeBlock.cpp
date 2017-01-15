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
 * Project Version: 1b6a 04-October-2013
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

NLPIitem::NLPIitem(void)
{
	instanceName = "";
	itemType = NLPI_ITEM_INSTANCE_ID_UNDEFINED;
	name = "";
}
NLPIitem::NLPIitem(GIAentityNode * entity, int newItemType)
{
	itemType = newItemType;
	name = generateClassName(entity);
	instanceName = generateInstanceName(entity);
	//entity->parsedForNLPIcodeBlocks = true;
}
NLPIitem::NLPIitem(string newName, int newItemType)
{
	instanceName = "";
	itemType = newItemType;
	name = newName;
}
NLPIitem::~NLPIitem(void)
{
}

string generateClassName(GIAentityNode * entity)
{
	string className = "";
	#ifndef NLPI_BAD_IMPLEMENTATION
	className = entity->entityName + "Class";
	#else
	if(entity->isConcept)
	{
		className = entity->entityName + "Class";
	}
	else
	{
		className = entity->entityName + convertLongToString(entity->idInstance) + "Class";
	}
	#endif
	return className;
}
string generateInstanceName(GIAentityNode * entity)
{
	string instanceName = entity->entityName + convertLongToString(entity->idInstance);
	return instanceName;
}
string generateActionName(GIAentityNode * entity)
{
	string actionName = entity->entityName;
	return actionName;
}

string convertLongToString(long number)
{
	//return to_string(number);	//C++11
	
	char tempString[100];
	sprintf(tempString, "%ld", number);
	return string(tempString);
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

	return createCodeBlock(currentCodeBlockInTree, NLPI_CODEBLOCK_TYPE_EXECUTE_FUNCTION_NO_OBJECT);
}

//add property
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




NLPIcodeblock * createCodeBlockFor(NLPIcodeblock * currentCodeBlockInTree, NLPIitem * item)
{
	currentCodeBlockInTree->parameters.push_back(item);
	int codeBlockType = NLPI_CODEBLOCK_TYPE_FOR;
	return createCodeBlock(currentCodeBlockInTree, codeBlockType);
}


NLPIcodeblock * createCodeBlockNewFunction(NLPIcodeblock * currentCodeBlockInTree, string functionName)
{
	NLPIitem * functionItem = new NLPIitem(functionName, NLPI_ITEM_TYPE_FUNCTION);
	currentCodeBlockInTree->parameters.push_back(functionItem);
	return createCodeBlock(currentCodeBlockInTree, NLPI_CODEBLOCK_TYPE_NEW_FUNCTION);
}



/*
NLPIcodeblock * createCodeBlockIfStatements(NLPIcodeblock * currentCodeBlockInTree, NLPIitem * item, GIAentityNode* entity, int sentenceIndex)
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


NLPIcodeblock * createCodeBlockIfHasProperties(NLPIcodeblock * currentCodeBlockInTree, NLPIitem * item, GIAentityNode * entity, int sentenceIndex)
{
	for(vector<GIAentityConnection*>::iterator propertyNodeListIterator = entity->propertyNodeList->begin(); propertyNodeListIterator < entity->propertyNodeList->end(); propertyNodeListIterator++)
	{
		GIAentityConnection * propertyConnection = (*propertyNodeListIterator);
		if(!(propertyConnection->parsedForNLPIcodeBlocks))
		{
			GIAentityNode* propertyEntity = propertyConnection->entity;
			if(checkSentenceIndexParsingCodeBlocks(propertyEntity,  sentenceIndex))
			{//only write conditions that are explicated in current sentence
				currentCodeBlockInTree = createCodeBlockIfHasProperty(currentCodeBlockInTree, item, propertyEntity, sentenceIndex);
				propertyConnection->parsedForNLPIcodeBlocks = true;
			}
		}
	}
	return currentCodeBlockInTree;
}
NLPIcodeblock * createCodeBlockIfHasProperty(NLPIcodeblock * currentCodeBlockInTree, NLPIitem * item, GIAentityNode* propertyEntity, int sentenceIndex)
{
	currentCodeBlockInTree->parameters.push_back(item);
	
	NLPIitem * propertyItem = new NLPIitem(propertyEntity, NLPI_ITEM_TYPE_CLASS);
	currentCodeBlockInTree->parameters.push_back(propertyItem);
	
	int codeBlockType = NLPI_CODEBLOCK_TYPE_IF_HAS_PROPERTY;
	currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);
	
	currentCodeBlockInTree = createCodeBlockIfStatements(currentCodeBlockInTree, propertyItem, propertyEntity, sentenceIndex);
	return currentCodeBlockInTree;
}

NLPIcodeblock * createCodeBlockIfHasConditions(NLPIcodeblock * currentCodeBlockInTree, NLPIitem * item,  GIAentityNode * entity, int sentenceIndex)
{
	for(vector<GIAentityConnection*>::iterator conditionNodeListIterator = entity->conditionNodeList->begin(); conditionNodeListIterator < entity->conditionNodeList->end(); conditionNodeListIterator++)
	{
		GIAentityConnection * conditionConnection = (*conditionNodeListIterator);
		if(!(conditionConnection->parsedForNLPIcodeBlocks))
		{
			GIAentityNode* conditionEntity = conditionConnection->entity;
			if(checkSentenceIndexParsingCodeBlocks(conditionEntity,  sentenceIndex))
			{	
				currentCodeBlockInTree = createCodeBlockIfHasCondition(currentCodeBlockInTree, item, conditionEntity, sentenceIndex);
				conditionConnection->parsedForNLPIcodeBlocks = true;
			}
		}			
	}
	return currentCodeBlockInTree;
}
NLPIcodeblock * createCodeBlockIfHasCondition(NLPIcodeblock * currentCodeBlockInTree, NLPIitem * item, GIAentityNode* conditionEntity, int sentenceIndex)
{
	if(!(conditionEntity->conditionObjectEntity->empty()))
	{
		currentCodeBlockInTree->parameters.push_back(item);
		NLPIitem * conditionItem = new NLPIitem(conditionEntity, NLPI_ITEM_TYPE_FUNCTION);
		currentCodeBlockInTree->parameters.push_back(conditionItem);
		
		GIAentityNode * conditionObject = (conditionEntity->conditionObjectEntity->back())->entity;
		NLPIitem * conditionObjectItem = new NLPIitem(conditionObject, NLPI_ITEM_TYPE_OBJECT);
		getEntityContext(conditionObject, &(conditionObjectItem->context), false, sentenceIndex, true);
		currentCodeBlockInTree->parameters.push_back(conditionObjectItem);
		
		int codeBlockType = NLPI_CODEBLOCK_TYPE_IF_HAS_CONDITION;
		currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);
		
		currentCodeBlockInTree = createCodeBlockIfStatements(currentCodeBlockInTree, conditionObjectItem, conditionObject, sentenceIndex);
	}
	else
	{
		cout << "error createCodeBlockIfHasCondition(): condition does not have object" << endl;
	}
	return currentCodeBlockInTree;
}

NLPIcodeblock * createCodeBlockIfStatements(NLPIcodeblock * currentCodeBlockInTree, NLPIitem * item, GIAentityNode* entity, int sentenceIndex)
{
	//LIMITATION: only parse 1 sub level of conditions:

	//if object near a red car / if object has a red car (if object has a car which is red)
	//if(item->has(property) && item->has(property1) etc..){
	currentCodeBlockInTree = createCodeBlockIfHasProperties(currentCodeBlockInTree, item, entity, sentenceIndex);

	//if object near a car that is behind the driveway / if object has a car that is near the house 
	//if(item > 3){		/	if(greaterthan(item, 3)){
	currentCodeBlockInTree = createCodeBlockIfHasConditions(currentCodeBlockInTree, item, entity, sentenceIndex);

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



NLPIcodeblock * createCodeBlock(NLPIcodeblock * currentCodeBlockInTree, int codeBlockType)
{
	#ifdef NLPI_DEBUG
	cout << "createCodeBlock [" << codeBlockType << "] = " << ((currentCodeBlockInTree->parameters).front())->name << endl;
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
		string itemName = entity->entityName + convertLongToString(entity->idInstance);
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
			string itemName = currentEntity->entityName + convertLongToString(currentEntity->idInstance);
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

string generateStringFromContextVector(vector<string> * context, int progLang)
{
	string contextString = "";
	for(vector<string>::iterator contextIterator = context->begin(); contextIterator < context->end(); contextIterator++)
	{
		string currentContext = *contextIterator;
		/*
		string delimiter = "":
		if(progLang == NLPI_PROGRAMMING_LANGUAGE_DEFAULT)
		{
			delimiter = progLangObjectReferenceDelimiter[progLang];
		}
		else
		{
			cout << "error: generateStringFromContextVector() only yet finished for NLPI_PROGRAMMING_LANGUAGE_DEFAULT" << endl; 
		}
		*/
		contextString = currentContext + progLangObjectReferenceDelimiter[progLang] + contextString;
	}
	
	#ifdef NLPI_PRINT_EXPLICIT_LOCAL_CONTEXT
	if(contextString == "")
	{
		contextString = string(NLPI_LOCAL_CONTEXT_NAME) + progLangObjectReferenceDelimiter[progLang];
	}
	#endif
	
	return contextString;
}



bool checkSentenceIndexParsingCodeBlocks(GIAentityNode * entity, int sentenceIndex)
{
	bool result = false;
	if(((entity->sentenceIndexTemp == sentenceIndex) || (entity->wasReference)) && !(entity->parsedForNLPIcodeBlocks))
	{
		result = true;
	}
	return result;
}



