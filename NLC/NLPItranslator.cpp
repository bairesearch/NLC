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
 * File Name: NLPItranslator.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2013 Baxter AI (baxterai.com)
 * Project: Natural Language Programming Interface (compiler)
 * Project Version: 1a1d 15-September-2013
 * Requirements: requires text parsed by NLP Parser (eg Relex; available in .CFF format <relations>)
 *
 *******************************************************************************/



#include <ctime>
#include <cstdlib>	//for random number generation
#include <cmath>

#include "NLPItranslator.h"


bool generateCodeBlocks(NLPIcodeblock * firstCodeBlockInTree, vector<GIAentityNode*> * entityNodesActiveListComplete, vector<GIAentityNode*> * entityNodesActiveListActions, int maxNumberSentences)
{
	
	NLPIcodeblock * currentCodeBlockInTree = firstCodeBlockInTree;
	
	currentCodeBlockInTree = createCodeBlockNewFunction(currentCodeBlockInTree, "main");

	//NLPIcodeblock * nextCodeBlockInTree = NULL;	//not used now; assume only 1 command in text
	//for each action (command) in sentence;
	
	//cout << "maxNumberSentences = " << maxNumberSentences << endl;
	for(int sentenceIndex=1; sentenceIndex <= maxNumberSentences; sentenceIndex++)
	{		
		//method1;
		for(vector<GIAentityNode*>::iterator entityNodesActiveListActionsIterator = entityNodesActiveListActions->begin(); entityNodesActiveListActionsIterator < entityNodesActiveListActions->end(); entityNodesActiveListActionsIterator++)
		{		
			GIAentityNode * actionEntity = (*entityNodesActiveListActionsIterator);
			cout << "actionEntity->entityName = " << actionEntity->entityName << endl;
			//cout << "actionEntity->isAction = " << actionEntity->isAction << endl;
			//cout << "actionEntity->hasAssociatedInstance = " << actionEntity->hasAssociatedInstance << endl;
			
			if(checkSentenceIndex(actionEntity,  sentenceIndex))
			{
				//cout << "h1" << endl;
				
				bool actionHasObject = false;
				GIAentityNode * objectEntity = NULL;
				if(!(actionEntity->actionObjectEntity->empty()))
				{
					actionHasObject = true;
					objectEntity = (actionEntity->actionObjectEntity->back())->entity;
				}
				cout << "h1b" << endl;
				bool actionHasSubject = false;
				GIAentityNode * subjectEntity = NULL;
				if(!(actionEntity->actionSubjectEntity->empty()))
				{
					actionHasSubject = true;
					subjectEntity = (actionEntity->actionSubjectEntity->back())->entity;
				}
				
				cout << "h2" << endl;
				
				if(actionHasObject)
				{
					bool objectRequiredTempVar = false;	//not used
					NLPIitem * objectItem = NULL;
					currentCodeBlockInTree = generateConditionBlocks(currentCodeBlockInTree, objectEntity, &objectItem, sentenceIndex, &objectRequiredTempVar);
					
					cout << "h3" << endl;
					NLPIitem * functionItem = new NLPIitem(actionEntity, NLPI_ITEM_TYPE_FUNCTION);
					if(actionHasSubject)
					{
						bool subjectRequiredTempVar = false;
						NLPIitem * subjectItem = NULL;
						currentCodeBlockInTree = generateConditionBlocks(currentCodeBlockInTree, subjectEntity, &subjectItem, sentenceIndex, &subjectRequiredTempVar);
						cout << "h4" << endl;
						if(subjectRequiredTempVar)
						{	
							cout << "subjectRequiredTempVar" << endl;						
							functionItem->context.push_back(subjectItem->name);
						}
						else
						{
							getEntityContext(subjectEntity, &(functionItem->context), true);
						}
					}
					cout << "h5" << endl;
					
					currentCodeBlockInTree = createCodeBlockExecute(currentCodeBlockInTree, functionItem, objectItem);
				}
				
				cout << "h6" << endl;
				/*		
				findContextOfObject(objectEntity)

				#ifdef GIA_SEMANTIC_NET_DO_NOT_WRITE_DISABLED_ENTITY_NODES
				if(!(currentEntity->disabled))
				{
				#endif

				#ifdef GIA_SEMANTIC_NET_DO_NOT_WRITE_DISABLED_ENTITY_NODES
				}
				#endif
				*/
			}
		}
		
		cout << "q1" << endl;
	
		//method2;
		//cout << "*** sentenceIndex = " << sentenceIndex << endl;
		for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
		{
			GIAentityNode * entityNode = *entityIter;
			if(checkSentenceIndex(entityNode,  sentenceIndex))
			{			
			
			}
		}
		
		cout << "q2" << endl;
	}
	
}

NLPIcodeblock * generateConditionBlocks(NLPIcodeblock * currentCodeBlockInTree, GIAentityNode * objectOrSubjectEntity, NLPIitem ** objectOrSubjectItem, int sentenceIndex, bool * requiredTempVar)
{
	*requiredTempVar = false;

	bool objectOrSubjectHasProperties = false;
	if(!(objectOrSubjectEntity->propertyNodeList->empty()))
	{
		objectOrSubjectHasProperties = true;
	}
	bool objectOrSubjectHasConditions = false;
	if(!(objectOrSubjectEntity->conditionNodeList->empty()))
	{
		objectOrSubjectHasConditions = true;	//not used
	}							
	bool multipleobjectOrSubjects = false;
	if(objectOrSubjectEntity->grammaticalNumber == GRAMMATICAL_NUMBER_PLURAL)
	{
		multipleobjectOrSubjects = true;
	}
	bool objectOrSubjectsHaveParent = false;

	if(multipleobjectOrSubjects || objectOrSubjectHasProperties || objectOrSubjectHasConditions)
	{//for loop required
		*requiredTempVar = true;
		
		//for(all items in context){
		NLPIitem * objectOrSubjectClass = new NLPIitem(objectOrSubjectEntity, NLPI_ITEM_TYPE_CLASS);
		objectOrSubjectsHaveParent = getEntityContext(objectOrSubjectEntity, &(objectOrSubjectClass->context), false);
		currentCodeBlockInTree = createCodeBlockFor(currentCodeBlockInTree, objectOrSubjectClass);
		*objectOrSubjectItem = new NLPIitem(objectOrSubjectEntity, NLPI_ITEM_TYPE_TEMPVAR);
		
		//specificobjectOrSubjects
		currentCodeBlockInTree = createCodeBlockIfHasProperties(currentCodeBlockInTree, *objectOrSubjectItem, objectOrSubjectEntity, sentenceIndex);
		//if(item->has(property) && item->has(property1) etc..){

		currentCodeBlockInTree = createCodeBlockIfHasConditions(currentCodeBlockInTree, *objectOrSubjectItem, objectOrSubjectEntity, sentenceIndex);
		//if(item > 3){		/	if(greaterthan(item, 3)){						
	}
	else
	{
		*objectOrSubjectItem = new NLPIitem(objectOrSubjectEntity, NLPI_ITEM_TYPE_OBJECT);
		objectOrSubjectsHaveParent = getEntityContext(objectOrSubjectEntity, &((*objectOrSubjectItem)->context), false);
	}
	return currentCodeBlockInTree;
}
