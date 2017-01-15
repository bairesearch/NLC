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
 * Project Version: 1a1d 15-September-2013
 * Requirements: requires text parsed by NLP Parser (eg Relex; available in .CFF format <relations>)
 *
 *******************************************************************************/




#include "NLPIcodeBlock.h"


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
	itemType = NLPI_ITEM_TYPE_UNDEFINED;
	name = "";
}
NLPIitem::NLPIitem(GIAentityNode * entity, int newItemType)
{
	itemType = newItemType;
	entity->parsedForNLPI = true;
	name = generateItemName(entity, itemType);	
}
NLPIitem::NLPIitem(string newName, int newItemType)
{
	itemType = newItemType;
	name = newName;
}
NLPIitem::~NLPIitem(void)
{
}

string generateItemName(GIAentityNode * entity, int itemType)
{
	string itemName = "";
	if(itemType == NLPI_ITEM_TYPE_OBJECT)
	{
		itemName = entity->entityName + convertLongToString(entity->idInstance);	//NLPI_ITEM_TYPE_OBJECT: variable name; eg car23		//Alternative [safer] use: idActiveList
	}
	else if(itemType == NLPI_ITEM_TYPE_TEMPVAR)
	{
		itemName = entity->entityName + NLPI_ITEM_TYPE_TEMPVAR_APPENDITION;
	}	
	else
	{
		itemName = entity->entityName;	//NLPI_ITEM_TYPE_CLASS/NLPI_ITEM_TYPE_FUNCTION: name; eg car 
	}
	return itemName;
}
string convertLongToString(long number)
{
	//return to_string(number);	//C++11
	
	char tempString[100];
	sprintf(tempString, "%ld", number);
	return string(tempString);
}


NLPIcodeblock * createCodeBlockFor(NLPIcodeblock * currentCodeBlockInTree, NLPIitem * item)
{
	currentCodeBlockInTree->parameters.push_back(item);
	int codeBlockType = NLPI_CODEBLOCK_TYPE_FOR;
	return createCodeBlock(currentCodeBlockInTree, codeBlockType);
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


NLPIcodeblock * createCodeBlockIfStatements(NLPIcodeblock * currentCodeBlockInTree, NLPIitem * item, GIAentityNode* entity, int sentenceIndex)
{
	//LIMITATION: only parse 1 sub level of conditions:

	//if object near a red car / if object has a red car (if object has a car which is red)
	currentCodeBlockInTree = createCodeBlockIfHasProperties(currentCodeBlockInTree, item, entity, sentenceIndex);

	//if object near a car that is behind the driveway / if object has a car that is near the house 
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

NLPIcodeblock * createCodeBlockIfHasProperties(NLPIcodeblock * currentCodeBlockInTree, NLPIitem * item, GIAentityNode * entity, int sentenceIndex)
{
	for(vector<GIAentityConnection*>::iterator propertyNodeListIterator = entity->propertyNodeList->begin(); propertyNodeListIterator < entity->propertyNodeList->end(); propertyNodeListIterator++)
	{
		GIAentityNode* propertyEntity = (*propertyNodeListIterator)->entity;
		if(checkSentenceIndex(propertyEntity,  sentenceIndex))
		{//only write conditions that are explicated in current sentence
			currentCodeBlockInTree = createCodeBlockIfHasProperty(currentCodeBlockInTree, item, propertyEntity, sentenceIndex);
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
		GIAentityNode* conditionEntity = (*conditionNodeListIterator)->entity;
		if(checkSentenceIndex(conditionEntity,  sentenceIndex))
		{	
			currentCodeBlockInTree = createCodeBlockIfHasCondition(currentCodeBlockInTree, item, conditionEntity, sentenceIndex);
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
		getEntityContext(conditionObject, &(conditionObjectItem->context), false);
		currentCodeBlockInTree->parameters.push_back(conditionObjectItem);
		
		int codeBlockType = NLPI_CODEBLOCK_TYPE_IF_HAS_CONDITION;
		currentCodeBlockInTree = createCodeBlock(currentCodeBlockInTree, codeBlockType);
		
		currentCodeBlockInTree = createCodeBlockIfStatements(currentCodeBlockInTree, conditionObjectItem, conditionObject, sentenceIndex);
	}
	else
	{
		cout << "error: condition does not have object" << endl;
	}
	return currentCodeBlockInTree;
}




NLPIcodeblock * createCodeBlock(NLPIcodeblock * currentCodeBlockInTree, int codeBlockType)
{
	cout << "createCodeBlock [" << codeBlockType << "] = " << ((currentCodeBlockInTree->parameters).front())->name << endl;
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


//Resultant code: functionItem[context].functionItem[name](objectItem[context].objectItem[name]);	//NB functionItem[context] = action subject
NLPIcodeblock * createCodeBlockExecute(NLPIcodeblock * currentCodeBlockInTree, NLPIitem * functionItem, NLPIitem* objectItem)
{
	currentCodeBlockInTree->parameters.push_back(functionItem);
	currentCodeBlockInTree->parameters.push_back(objectItem);

	return createCodeBlock(currentCodeBlockInTree, NLPI_CODEBLOCK_TYPE_EXECUTE_FUNCTION);
}

NLPIcodeblock * createCodeBlockNewFunction(NLPIcodeblock * currentCodeBlockInTree, string functionName)
{
	NLPIitem * functionItem = new NLPIitem(functionName, NLPI_ITEM_TYPE_FUNCTION);
	currentCodeBlockInTree->parameters.push_back(functionItem);
	return createCodeBlock(currentCodeBlockInTree, NLPI_CODEBLOCK_TYPE_NEW_FUNCTION);
}


NLPIcodeblock * createLowerLevel(NLPIcodeblock * currentCodeBlockInTree)
{
	currentCodeBlockInTree->lowerLevel = new NLPIcodeblock();
	currentCodeBlockInTree = currentCodeBlockInTree->lowerLevel;
	return currentCodeBlockInTree;
}

bool getEntityContext(GIAentityNode * entity, vector<string> * context, bool includePresentObject)
{
	if(includePresentObject)
	{
		context->push_back(generateItemName(entity, NLPI_ITEM_TYPE_OBJECT));
	}
	bool entityHasParent = false;
	bool stillSearching = true;
	GIAentityNode * currentEntity = entity;
	
	while(stillSearching)
	{
		if(!(currentEntity->propertyNodeReverseList->empty()))
		{
			entityHasParent = true;
			currentEntity = (currentEntity->propertyNodeReverseList->back())->entity;
			string itemName = generateItemName(currentEntity, NLPI_ITEM_TYPE_OBJECT);
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
	return contextString;
}

bool checkSentenceIndex(GIAentityNode * entity, int sentenceIndex)
{
	bool result = false;
	if((entity->sentenceIndexTemp == sentenceIndex) || (entity->wasReference) && !(entity->parsedForNLPI))
	{
		result = true;
	}
	return result;
}

