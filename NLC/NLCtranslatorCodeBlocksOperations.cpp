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
 * File Name: NLCtranslatorCodeBlocksOperations.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2014 Baxter AI (baxterai.com)
 * Project: Natural Language Programming Interface (compiler)
 * Project Version: 1h1f 26-July-2014
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/



#include <ctime>
#include <cstdlib>	//for random number generation
#include <cmath>

#include "NLCtranslatorCodeBlocksOperations.h"
#include "GIAtranslatorDefs.h"



void generateActionCodeBlocks(NLCcodeblock ** currentCodeBlockInTree, GIAentityNode * actionEntity, int sentenceIndex, string NLCfunctionName)
{
	NLCcodeblock * firstCodeBlockInSentence = *currentCodeBlockInTree;

	#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
	if(!(actionEntity->NLCparsedForlogicalConditionOperations))
	{
	#endif
		#ifdef NLC_DEBUG
		cout << "actionEntity->entityName = " << actionEntity->entityName << endl;
		#endif
		//cout << "sentenceIndexC = " << sentenceIndex << endl;

		bool actionHasObject = false;
		GIAentityNode * objectEntity = NULL;
		if(!(actionEntity->actionObjectEntity->empty()))
		{
			actionHasObject = true;
			objectEntity = (actionEntity->actionObjectEntity->back())->entity;
		}

		bool actionHasSubject = false;
		GIAentityNode * subjectEntity = NULL;
		if(!(actionEntity->actionSubjectEntity->empty()))
		{
			actionHasSubject = true;
			subjectEntity = (actionEntity->actionSubjectEntity->back())->entity;
		}

		NLCcodeblock * functionExecuteCodeBlockInTree = NULL;

		NLCitem * functionItem = NULL;
		if(actionHasObject || actionHasSubject)
		{
			//[q**^]
			functionItem = new NLCitem(actionEntity, NLC_ITEM_TYPE_FUNCTION);

			#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS
			initialiseFunctionArguments(currentCodeBlockInTree, actionEntity, sentenceIndex);
			//firstCodeBlockInSentence = *currentCodeBlockInTree;		//removed 1f1b... [CHECKTHIS]
			#endif

			#ifndef NLC_DEFINE_LOCAL_VARIABLES_FOR_ALL_INDEFINATE_ENTITIES
			//this is where original getParentAndInitialiseParentIfNecessaryAndGenerateContextBlocks code whent (for both subjectEntity and objectEntity)
			getParentAndGenerateParentInitialisationCodeBlock(currentCodeBlockInTree, subjectEntity, sentenceIndex, true, false);	//parseConditionParents was previously set false in original implementation [although the GIA specification supports such arrangements, in practice however they probably can't be generated as x will always be a condition subject not a condition object of y in "x is near the y"]
			getParentAndGenerateParentInitialisationCodeBlock(currentCodeBlockInTree, objectEntity, sentenceIndex, true, false);	//parseConditionParents was previously set false in original implementation [although the GIA specification supports such arrangements, in practice however they probably can't be generated as x will always be a condition subject not a condition object of y in "x is near the y"]
			#endif

		}


		if(actionHasObject)
		{
			NLClogicalConditionConjunctionVariables logicalConditionConjunctionVariables;	//not used
			if(getParentAndInitialiseParentIfNecessaryAndGenerateContextBlocks(currentCodeBlockInTree, objectEntity, sentenceIndex, &logicalConditionConjunctionVariables, true, false))	//parseConditionParents was previously set false in original implementation [although the GIA specification supports such arrangements, in practice however they probably can't be generated as x will always be a condition subject not a condition object of y in "x is near the y"]
			{
				//cout << "actionHasObject: parent and its children initialised" << endl;
			}
			if(actionHasSubject)
			{
				NLClogicalConditionConjunctionVariables logicalConditionConjunctionVariables;	//not used
				//cout  << "subjectEntity = " << subjectEntity->entityName << endl;
				if(getParentAndInitialiseParentIfNecessaryAndGenerateContextBlocks(currentCodeBlockInTree, subjectEntity, sentenceIndex, &logicalConditionConjunctionVariables, true, false))	//parseConditionParents was previously set false in original implementation [although the GIA specification supports such arrangements, in practice however they probably can't be generated as x will always be a condition subject not a condition object of y in "x is near the y"]
				{
					//cout << "actionHasSubject2: parent and its children initialised" << endl;
				}
				functionItem->context.push_back(generateInstanceName(subjectEntity));

				#ifdef NLC_NOT_NECESSARY
				//required just for implictlyDeclaredFunctionList...;
				NLCitem * functionItemFullContextForRecordOnly = new NLCitem(actionEntity, NLC_ITEM_TYPE_FUNCTION);
				getEntityContext(subjectEntity, &(functionItemFullContextForRecordOnly->context), true, sentenceIndex, true);
				implictlyDeclaredFunctionList.push_back(functionItemFullContextForRecordOnly);
				#endif

				//subjectEntity->parsedForNLCcodeBlocksActionRound = true;
			}
			#ifdef NLC_NOT_NECESSARY
			else
			{
				implictlyDeclaredFunctionListTopLevel.push_back(functionItem);
			}
			#endif

			functionExecuteCodeBlockInTree = *currentCodeBlockInTree;
			NLCitem *objectItem = new NLCitem(objectEntity, NLC_ITEM_TYPE_FUNCTION_OBJECT);
			*currentCodeBlockInTree = createCodeBlockExecute(*currentCodeBlockInTree, functionItem, objectItem);

			actionEntity->NLCparsedForCodeBlocks = true;
			//actionEntity->parsedForNLCcodeBlocksActionRound = true;
			//objectEntity->parsedForNLCcodeBlocksActionRound = true;
		}
		else if(actionHasSubject)
		{
			//[**^]
			NLClogicalConditionConjunctionVariables logicalConditionConjunctionVariables;
			if(getParentAndInitialiseParentIfNecessaryAndGenerateContextBlocks(currentCodeBlockInTree, subjectEntity, sentenceIndex, &logicalConditionConjunctionVariables, true, false))	//parseConditionParents was previously set false in original implementation [although the GIA specification supports such arrangements, in practice however they probably can't be generated as x will always be a condition subject not a condition object of y in "x is near the y"]
			{
				//cout << "actionHasSubject: parent and its children initialised" << endl;
			}
			//cout << "subjectRequiredTempVar" << endl;
			functionItem->context.push_back(generateInstanceName(subjectEntity));

			functionExecuteCodeBlockInTree = *currentCodeBlockInTree;
			*currentCodeBlockInTree = createCodeBlockExecute(*currentCodeBlockInTree, functionItem);

			actionEntity->NLCparsedForCodeBlocks = true;
			//actionEntity->parsedForNLCcodeBlocksActionRound = true;
			//subjectEntity->parsedForNLCcodeBlocksActionRound = true;
		}

		#ifdef NLC_INTERPRET_ACTION_PROPERTIES_AND_CONDITIONS_AS_FUNCTION_ARGUMENTS
		if(actionHasObject || actionHasSubject)
		{
			#ifndef NLC_SUPPORT_INPUT_FILE_LISTS
			generateFunctionPropertyConditionArgumentsWithActionConceptInheritance(actionEntity, &(functionExecuteCodeBlockInTree->parameters));	//#ifdef NLC_SUPPORT_INPUT_FILE_LISTS use class definition parameters instead
			#endif

			//detect action properties and conditions (and disable these for NLC generate code block parse: they will become function execution arguments)
			for(vector<GIAentityConnection*>::iterator entityIter = actionEntity->conditionNodeList->begin(); entityIter != actionEntity->conditionNodeList->end(); entityIter++)
			{
				GIAentityNode * actionCondition = (*entityIter)->entity;
				(*entityIter)->NLCparsedForCodeBlocks = true;
				actionCondition->NLCparsedForCodeBlocks = true;
			}
			for(vector<GIAentityConnection*>::iterator entityIter = actionEntity->propertyNodeList->begin(); entityIter != actionEntity->propertyNodeList->end(); entityIter++)
			{
				GIAentityNode * actionProperty = (*entityIter)->entity;
				(*entityIter)->NLCparsedForCodeBlocks = true;
				actionProperty->NLCparsedForCodeBlocks = true;
			}
		}
		#endif

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
	#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
	}
	#endif
	
	*currentCodeBlockInTree = firstCodeBlockInSentence;
	while((*currentCodeBlockInTree)->next != NULL)
	{
		*currentCodeBlockInTree = (*currentCodeBlockInTree)->next;
	}
}

#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS
void initialiseFunctionArguments(NLCcodeblock ** currentCodeBlockInTree, GIAentityNode * actionEntity, int sentenceIndex)
{
	//cout << "NLC_CODEBLOCK_TYPE_DECLARE_NEW_VARIABLE" << endl;
	actionEntity->NLCisSingularArgument = true;	//added 1e2c

	//declare an "abstract" variable for the action (that will be filled with the its properties and conditions) and passed as an argument to the function; eg "fast" of "run fast"
	//cout << "functionItem->instanceName = " << functionItem->instanceName << endl;
	//cout << "functionItem->className = " << functionItem->className << endl;
	*currentCodeBlockInTree = createCodeBlocksCreateNewLocalListVariable(*currentCodeBlockInTree, actionEntity);	//changed 1e10b

	generateObjectInitialisationsBasedOnPropertiesAndConditions(actionEntity, currentCodeBlockInTree, sentenceIndex, "", "", false);
	generateObjectInitialisationsBasedOnSubstanceConcepts(actionEntity, currentCodeBlockInTree, sentenceIndex);
}
#endif












bool getParentAndInitialiseParentIfNecessaryAndGenerateContextBlocks(NLCcodeblock ** currentCodeBlockInTree, GIAentityNode * currentEntity, int sentenceIndex, NLClogicalConditionConjunctionVariables * logicalConditionConjunctionVariables, bool parseConditionParents, bool parseLogicalConditions)
{
	GIAentityNode * parentEntity = getParent(currentEntity, sentenceIndex, parseConditionParents);

	bool performedAtLeastParentObjectInitialisation = false;
	if(checkSentenceIndexParsingCodeBlocks(currentEntity, sentenceIndex, false))
	{//is this required?
		performedAtLeastParentObjectInitialisation = initialiseParentIfNecessaryAndGenerateCodeBlocks(currentCodeBlockInTree, parentEntity, sentenceIndex, logicalConditionConjunctionVariables, parseConditionParents, parseLogicalConditions);
	}

	return performedAtLeastParentObjectInitialisation;

}
//added 1e6a
bool initialiseParentIfNecessaryAndGenerateCodeBlocks(NLCcodeblock ** currentCodeBlockInTree, GIAentityNode * parentEntity, int sentenceIndex, NLClogicalConditionConjunctionVariables * logicalConditionConjunctionVariables, bool parseConditionParents, bool parseLogicalConditions)
{
	bool performedAtLeastParentObjectInitialisation = false;

	#ifdef NLC_DEBUG
	cout << "\tgenerateContextBlocksAndInitialiseParentIfNecessary parent: " << parentEntity->entityName << endl;
	#endif

	if(generateParentInitialisationCodeBlock(currentCodeBlockInTree, parentEntity, sentenceIndex, parseLogicalConditions))
	{
		performedAtLeastParentObjectInitialisation = true;
	}

	if(!generateContextBlocks(currentCodeBlockInTree, parentEntity, sentenceIndex, logicalConditionConjunctionVariables))
	{

	}

	return performedAtLeastParentObjectInitialisation;
}






























bool generateContextBlocks(NLCcodeblock ** currentCodeBlockInTree, GIAentityNode * parentEntity, int sentenceIndex, NLClogicalConditionConjunctionVariables * logicalConditionConjunctionVariables)
{
	bool contextFound = false;

	NLCcodeblock * originalCodeBlockInTree = *currentCodeBlockInTree;

	NLCitem * propertyItem = new NLCitem(parentEntity, NLC_ITEM_TYPE_CLASS);
	//context property item:
	if(assumedToAlreadyHaveBeenDeclared(parentEntity))
	{
		*currentCodeBlockInTree = createCodeBlockForPropertyListLocal(*currentCodeBlockInTree, propertyItem);
	}
	else
	{
		*currentCodeBlockInTree = createCodeBlockForPropertyList(*currentCodeBlockInTree, propertyItem);
	}

	#ifdef NLC_DEBUG
	cout << "\tgenerateContextBlocks: " << parentEntity->entityName << endl;
	#endif
	//parse the children (properties and conditions) of an undeclared definite parent
	if(!createCodeBlockForStatements(currentCodeBlockInTree, generateInstanceName(parentEntity), parentEntity, sentenceIndex, logicalConditionConjunctionVariables))
	{
		#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
		if(logicalConditionConjunctionVariables->onlyGenerateContextBlocksIfConnectionsParsedForNLC)
		{
			*currentCodeBlockInTree = originalCodeBlockInTree;
		}
		#endif
	}
	else
	{
		contextFound = true;
		#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
		parentEntity->NLCcontextGenerated = true;	//added 1g14b 15-July-2014
		#endif
	}

	return contextFound;
}

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
		#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
		if((propertyConnection->NLCparsedForCodeBlocks) || !(logicalConditionConjunctionVariables->onlyGenerateContextBlocksIfConnectionsParsedForNLC))	//added option 1g13b 15-July-2014
		{
		#endif
			GIAentityNode* propertyEntity = propertyConnection->entity;
			if(checkSentenceIndexParsingCodeBlocks(propertyEntity, propertyConnection, sentenceIndex, false))	//changed from true to false 1e5b
			{//only write conditions that are explicated in current sentence
				#ifdef NLC_DEBUG
				cout << "createCodeBlockForGivenProperties: " << propertyEntity->entityName << endl;
				#endif
				propertyConnection->NLCparsedForCodeBlocks = true;
				#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS
				bool conjunctionConditionConnectionFound = hasConjunctionConditionConnection(propertyEntity, logicalConditionConjunctionVariables->primaryEntityInLogicalConditionConjunctionSubset, logicalConditionConjunctionVariables->logicalConditionConjunctionIndex, &(logicalConditionConjunctionVariables->foundLogicalConditionConjunction));	//dont need to test for mismatched logicalConditionConjunctionIndex; it is just for debugging
				if(!conjunctionConditionConnectionFound)
				{
				#endif
					result = true;
					#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
					//propertyConnection->NLCcontextGenerated = true;	//added 1g14b 15-July-2014
					propertyEntity->NLCcontextGenerated = true;	//added 1g14b 15-July-2014
					#endif
					//propertyEntity->NLCcontextGenerated = true;	//added 1g14b 15-July-2014
					createCodeBlockForGivenProperty(currentCodeBlockInTree, parentInstanceName, propertyEntity, sentenceIndex, logicalConditionConjunctionVariables);
					#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS
					propertyEntity->NLClogicalConditionConjunctionIndex = logicalConditionConjunctionVariables->logicalConditionConjunctionIndex;
					#endif
				#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS
				}
				#endif
			}
		#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
		}
		#endif
	}
	return result;
}
bool createCodeBlockForGivenProperty(NLCcodeblock ** currentCodeBlockInTree, string parentInstanceName, GIAentityNode* propertyEntity, int sentenceIndex, NLClogicalConditionConjunctionVariables * logicalConditionConjunctionVariables)
{
	bool result = true;
	NLCitem * propertyItem = new NLCitem(propertyEntity, NLC_ITEM_TYPE_CLASS);

	//cout << "createCodeBlockForGivenProperty: propertyEntity = " << propertyEntity->entityName << endl;
	/*
	if(assumedToAlreadyHaveBeenDeclared(propertyEntity))
	{
		#ifndef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS
		if(logicalOperation == NLC_LOGICAL_CONDITION_OPERATIONS_FOR)
		{
		#endif
			*currentCodeBlockInTree = createCodeBlockForPropertyListLocal(*currentCodeBlockInTree, propertyItem);
		#ifndef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS
		}
		else if(logicalOperation == NLC_LOGICAL_CONDITION_OPERATIONS_IF)
		{
			*currentCodeBlockInTree = createCodeBlockIfHasPropertyLocal(*currentCodeBlockInTree, propertyItem, logicalConditionConjunctionVariables->negative);
		}
		else if(logicalOperation == NLC_LOGICAL_CONDITION_OPERATIONS_WHILE)
		{
			*currentCodeBlockInTree = createCodeBlockWhileHasPropertyLocal(*currentCodeBlockInTree, propertyItem, logicalConditionConjunctionVariables->negative);
		}
		#endif
	}
	else
	{
	*/
	propertyItem->context.push_back(parentInstanceName);
	#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
	#ifndef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS
	if(logicalOperation == NLC_LOGICAL_CONDITION_OPERATIONS_FOR)
	{
	#endif
	#endif
		*currentCodeBlockInTree = createCodeBlockForPropertyList(*currentCodeBlockInTree, propertyItem);
	#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
	#ifndef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS
	}
	else if(logicalOperation == NLC_LOGICAL_CONDITION_OPERATIONS_IF)
	{
		*currentCodeBlockInTree = createCodeBlockIfHasProperty(*currentCodeBlockInTree, propertyItem, logicalConditionConjunctionVariables->negative);
	}
	else if(logicalOperation == NLC_LOGICAL_CONDITION_OPERATIONS_WHILE)
	{
		*currentCodeBlockInTree = createCodeBlockWhileHasProperty(*currentCodeBlockInTree, propertyItem, logicalConditionConjunctionVariables->negative);
	}
	#endif
	#endif
	/*
	}
	*/

	//DEBUG:
	//*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, propertyEntity->entityName);

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
		#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
		if((conditionConnection->NLCparsedForCodeBlocks) || !(logicalConditionConjunctionVariables->onlyGenerateContextBlocksIfConnectionsParsedForNLC))	//added option 1g13b 15-July-2014
		{
		#endif
			GIAentityNode* conditionEntity = conditionConnection->entity;
			if(checkSentenceIndexParsingCodeBlocks(conditionEntity, conditionConnection, sentenceIndex, false))	//changed from true to false 1e5b
			{
				conditionConnection->NLCparsedForCodeBlocks = true;
				#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS
				bool conjunctionConditionFound = textInTextArray(conditionEntity->entityName, entityCoordinatingConjunctionArray, ENTITY_COORDINATINGCONJUNCTION_ARRAY_NUMBER_OF_TYPES);
				if(!conjunctionConditionFound)
				{//do not parse conjunction conditions
					bool conjunctionConditionConnectionFound = hasConjunctionConditionConnection(conditionEntity, logicalConditionConjunctionVariables->primaryEntityInLogicalConditionConjunctionSubset, logicalConditionConjunctionVariables->logicalConditionConjunctionIndex, &(logicalConditionConjunctionVariables->foundLogicalConditionConjunction));	//dont need to test for mismatched logicalConditionConjunctionIndex; it is just for debugging
					if(!conjunctionConditionConnectionFound)
					{
				#endif
						bool result = true;
						if(!(conditionEntity->conditionObjectEntity->empty()))
						{
							GIAentityNode * conditionObject = (conditionEntity->conditionObjectEntity->back())->entity;
							//cout << "conditionObject = " << conditionObject->entityName << endl;
							#ifdef NLC_DEBUG
							cout << "createCodeBlockForGivenConditions: " << conditionEntity->entityName << endl;
							#endif
							result = true;
							#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
							//conditionConnection->NLCcontextGenerated = true;	//added 1g14b 15-July-2014
							conditionObject->NLCcontextGenerated = true;	//added 1g14b 15-July-2014
							#endif
							createCodeBlockForGivenCondition(currentCodeBlockInTree, parentInstanceName, conditionEntity, conditionObject, sentenceIndex, logicalConditionConjunctionVariables);
							#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS
							conditionEntity->NLClogicalConditionConjunctionIndex = logicalConditionConjunctionVariables->logicalConditionConjunctionIndex;
							#endif
						}
						else
						{
							result = false;
							cout << "error createCodeBlockForGivenCondition(): condition does not have object" << endl;
						}

				#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS
					}
				}
				else
				{
					logicalConditionConjunctionVariables->foundLogicalConditionConjunction = conditionEntity;
				}
				#endif
			}
		#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
		}
		#endif
	}
	return result;
}
bool createCodeBlockForGivenCondition(NLCcodeblock ** currentCodeBlockInTree, string parentInstanceName, GIAentityNode* conditionEntity, GIAentityNode* conditionObject, int sentenceIndex, NLClogicalConditionConjunctionVariables * logicalConditionConjunctionVariables)
{
	bool result = true;

	NLCitem * conditionItem = new NLCitem(conditionEntity, NLC_ITEM_TYPE_CLASS);
	NLCitem * conditionObjectItem = new NLCitem(conditionObject, NLC_ITEM_TYPE_CLASS);
	//cout << "createCodeBlockForGivenCondition: " << conditionObjectItem->instanceName << endl;

	conditionItem->context.push_back(parentInstanceName);
	conditionObjectItem->context.push_back(parentInstanceName);	//redundant

	#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
	#ifndef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS
	if(logicalOperation == NLC_LOGICAL_CONDITION_OPERATIONS_FOR)
	{
	#endif
	#endif
		*currentCodeBlockInTree = createCodeBlockForConditionList(*currentCodeBlockInTree, conditionItem, conditionObjectItem);
	#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
	#ifndef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS
	}
	else if(logicalOperation == NLC_LOGICAL_CONDITION_OPERATIONS_IF)
	{
		*currentCodeBlockInTree = createCodeBlockIfHasCondition(*currentCodeBlockInTree, conditionItem, conditionObjectItem, logicalConditionConjunctionVariables->negative);
	}
	else if(logicalOperation == NLC_LOGICAL_CONDITION_OPERATIONS_WHILE)
	{
		*currentCodeBlockInTree = createCodeBlockWhileHasCondition(*currentCodeBlockInTree, conditionItem, conditionObjectItem, logicalConditionConjunctionVariables->negative);
	}
	#endif
	#endif

	createCodeBlockForStatements(currentCodeBlockInTree, conditionObjectItem->instanceName, conditionObject, sentenceIndex, logicalConditionConjunctionVariables);

	return result;
}

#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS
bool hasConjunctionConditionConnection(GIAentityNode * conditionEntity, GIAentityNode * primaryEntityInLogicalConditionConjunctionSubset, int logicalConditionConjunctionIndex, GIAentityNode ** foundLogicalConditionConjunction)	//dont need to test for mismatched logicalConditionConjunctionIndex; it is just for debugging
{
	bool conjunctionConditionConnectionFound = false;

	for(vector<GIAentityConnection*>::iterator conditionNodeListIterator = conditionEntity->conditionNodeList->begin(); conditionNodeListIterator < conditionEntity->conditionNodeList->end(); conditionNodeListIterator++)
	{
		GIAentityConnection * conditionConnection = (*conditionNodeListIterator);
		GIAentityNode* conditionEntity2 = conditionConnection->entity;
		bool conjunctionConditionFound = textInTextArray(conditionEntity2->entityName, entityCoordinatingConjunctionArray, ENTITY_COORDINATINGCONJUNCTION_ARRAY_NUMBER_OF_TYPES);
		if(conjunctionConditionFound)
		{
			if(conditionEntity != primaryEntityInLogicalConditionConjunctionSubset)
			{//ignore primaryEntityInLogicalConditionConjunctionSubset
				if(conditionEntity2->NLCconjunctionCondition)
				{//condition added 1g6h; do not parse nodes with conjunction condition connections if the conjunction condition has already been parsed by checkConditionForLogicalCondition()
					conjunctionConditionConnectionFound = true;
				}
			}
			//if(conditionEntity != primaryEntityInLogicalConditionConjunctionSubset) {//removed NLC 1g6j - 10 July 2014
			if(!(conditionEntity2->NLCconjunctionCondition))
			{//do not reparse same conjunction conditions - added NLC 1g7b - 11 July 2014
				if(*foundLogicalConditionConjunction == NULL)
				{//do not overwrite foundLogicalConditionConjunction; always take the first conjunction in subset as the one to parse next - added NLC 1g6j - 10 July 2014
					*foundLogicalConditionConjunction = conditionEntity2;
				}
			}
			//}
		}
	}
	if(conditionEntity != primaryEntityInLogicalConditionConjunctionSubset)
	{
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

	/*
	//for debugging only:
	if(!conjunctionConditionConnectionFound)
	{
		if((conditionEntity->NLClogicalConditionConjunctionIndex != logicalConditionConjunctionIndex) && (conditionEntity->NLClogicalConditionConjunctionIndex != INT_DEFAULT_VALUE))
		{
			cout << "hasConjunctionConditionConnection() error: child of primaryEntityInLogicalConditionConjunctionSubset has been declared as pertaining to a different logicalConditionConjunctionSubset - is this a shared context?" << endl;
		}
	}
	*/

	return conjunctionConditionConnectionFound;
}
#endif
















//static int haltForDebug = false;

#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
bool generateCodeBlocksObjectInitialisationsForEntity(NLCcodeblock ** currentCodeBlockInTree, GIAentityNode * entity, int sentenceIndex)
{
	bool result = true;

	#ifdef NLC_DEBUG_PARSE_CONTEXT
	cout << "\ngenerateCodeBlocksPart4objectInitialisations(): sentenceIndex = " << sentenceIndex << endl;
	cout << "\tentity->entityName = " << entity->entityName << endl;
	#endif

	NLCcodeblock * originalCodeBlockInLevel = *currentCodeBlockInTree;
	NLClogicalConditionConjunctionVariables logicalConditionConjunctionVariables;
	logicalConditionConjunctionVariables.onlyGenerateContextBlocksIfConnectionsParsedForNLC = true;

	#ifdef NLC_DEBUG_PARSE_CONTEXT
	cout << "generateCodeBlocksObjectInitialisationsForEntity: getParent()" << endl;
	#endif
	GIAentityNode * parentEntity = getParent(entity, sentenceIndex, true);
	#ifdef NLC_DEBUG_PARSE_CONTEXT
	cout << "\tparentEntity = " << parentEntity->entityName << endl;
	cout << "generateCodeBlocksObjectInitialisationsForEntity: initialiseParentIfNecessaryAndGenerateCodeBlocks()" << endl;
	#endif
	if(!initialiseParentIfNecessaryOrGenerateCodeBlocks(currentCodeBlockInTree, parentEntity, sentenceIndex, &logicalConditionConjunctionVariables, true, false))	//parse condition parents in accordance with original generateCodeBlocksPart4objectInitialisations implementation
	{
		#ifdef NLC_DEBUG_PARSE_CONTEXT
		cout << "\tfail initialiseParentIfNecessaryOrGenerateCodeBlocks" << endl;
		cout << "generateCodeBlocksObjectInitialisationsForEntity: generateObjectInitialisationsBasedOnPropertiesAndConditions()" << endl;
		#endif
		if(!generateObjectInitialisationsBasedOnPropertiesAndConditions(parentEntity, currentCodeBlockInTree , sentenceIndex, "", "", true))
		{
			*currentCodeBlockInTree = originalCodeBlockInLevel;
			clearCodeBlock(originalCodeBlockInLevel);

			#ifdef NLC_DEBUG_PARSE_CONTEXT
			cout << "\tfail generateObjectInitialisationsBasedOnPropertiesAndConditions" << endl;
			#endif
		}
		else
		{
			#ifdef NLC_DEBUG_PARSE_CONTEXT
			cout << "\tpass generateObjectInitialisationsBasedOnPropertiesAndConditions" << endl;
			#endif
		}
	}
	else
	{
		#ifdef NLC_DEBUG_PARSE_CONTEXT
		cout << "\tpass initialiseParentIfNecessaryOrGenerateCodeBlocks" << endl;
		#endif
	}
	return result;
}

//added 1g14b 15-July-2014 (do not generate code blocks if parent and its children are already initialised)
bool initialiseParentIfNecessaryOrGenerateCodeBlocks(NLCcodeblock ** currentCodeBlockInTree, GIAentityNode * parentEntity, int sentenceIndex, NLClogicalConditionConjunctionVariables * logicalConditionConjunctionVariables, bool parseConditionParents, bool parseLogicalConditions)
{
	bool performedAtLeastParentObjectInitialisation = false;

	#ifdef NLC_DEBUG
	cout << "\tinitialiseParentIfNecessaryOrGenerateCodeBlocks parent: " << parentEntity->entityName << endl;
	#endif

	if(generateParentInitialisationCodeBlock(currentCodeBlockInTree, parentEntity, sentenceIndex, parseLogicalConditions))
	{
		performedAtLeastParentObjectInitialisation = true;
	}
	else
	{
		if(!generateContextBlocks(currentCodeBlockInTree, parentEntity, sentenceIndex, logicalConditionConjunctionVariables))
		{

		}
	}

	return performedAtLeastParentObjectInitialisation;
}
#endif

















bool getParentAndGenerateParentInitialisationCodeBlock(NLCcodeblock ** currentCodeBlockInTree, GIAentityNode * entity, int sentenceIndex, bool parseConditionParents, bool parseLogicalConditions)
{
	GIAentityNode * parentEntity = getParent(entity, sentenceIndex, parseConditionParents);
	//cout << "parentEntity = " << parentEntity->entityName << endl;

	bool performedAtLeastParentObjectInitialisation = false;

	performedAtLeastParentObjectInitialisation = generateParentInitialisationCodeBlock(currentCodeBlockInTree, parentEntity, sentenceIndex, parseLogicalConditions);
}

bool generateParentInitialisationCodeBlock(NLCcodeblock ** currentCodeBlockInTree, GIAentityNode * parentEntity, int sentenceIndex, bool parseLogicalConditions)
{
	bool performedAtLeastParentObjectInitialisation = false;

	//cout << "generateParentInitialisationCodeBlock: entity->NLCparsedForlogicalConditionOperations = " << entity->NLCparsedForlogicalConditionOperations << endl;
	#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
	if(!(parentEntity->NLCparsedForlogicalConditionOperations) || parseLogicalConditions)	//CHECKTHIS; change from !(entity->NLCparsedForlogicalConditionOperations) to !(parentEntity->NLCparsedForlogicalConditionOperations) 1g14a 15-July-2014
	{
	#endif
		#ifdef NLC_CREATE_IMPLICITLY_DECLARED_ACTION_OBJECT_AND_SUBJECT_VARIABLES
		//moved here 1e8a (out of generateObjectInitialisationsBasedOnPropertiesAndConditions)
		//added 1e6c: eg A chicken's hat has a bike. / A blue dog has a bike.
		if(!(parentEntity->isConcept))
		{
			if(!(parentEntity->NLCparsedForCodeBlocks))	// && !(entity->parsedForNLCcodeBlocksActionRound)
			{
				if(!assumedToAlreadyHaveBeenDeclared(parentEntity))
				{
					if(!(parentEntity->isAction))	//added 1e6d
					{
						#ifndef NLC_DEFINE_LOCAL_VARIABLES_FOR_ALL_INDEFINATE_ENTITIES
						if(checkSentenceIndexParsingCodeBlocks(parentEntity, sentenceIndex, false))	//this is redundant with NLC_DEFINE_LOCAL_VARIABLES_FOR_ALL_INDEFINATE_ENTITIES
						{
						#endif
							if(!(parentEntity->isCondition))
							{
								if(!(parentEntity->isSubstanceConcept) && !(parentEntity->isActionConcept))
								{
									#ifdef NLC_VERIFY_CONNECTIONS_SENTENCE_INDEX
									if(parentEntity->sentenceIndexTemp == sentenceIndex)	//ie "wasReference" is not a sufficient condition to initialise parent
									{
									#endif
										#ifdef NLC_DEBUG
										cout << "createCodeBlocksCreateNewLocalListVariable: " << parentEntity->entityName << endl;
										#endif
										#ifdef NLC_DEFINE_LOCAL_VARIABLES_FOR_ALL_INDEFINATE_ENTITIES
										if(parentEntity->NLClocalListVariableHasBeenDeclared)
										{//added 1g8a 11-July-2014
											*currentCodeBlockInTree = createCodeBlockAddNewPropertyToLocalList(*currentCodeBlockInTree, parentEntity, parentEntity);
										}
										else
										{
										#endif

											*currentCodeBlockInTree = createCodeBlocksCreateNewLocalListVariable(*currentCodeBlockInTree, parentEntity);	//is this ever called with NLC_DEFINE_LOCAL_VARIABLES_FOR_ALL_INDEFINATE_ENTITIES?
										#ifdef NLC_DEFINE_LOCAL_VARIABLES_FOR_ALL_INDEFINATE_ENTITIES
										}
										#endif
										parentEntity->NLCparsedForCodeBlocks = true;
										parentEntity->NLClocalListVariableHasBeenInitialised = true;
										//cout << "createCodeBlocksCreateNewLocalListVariable: " << parentEntity->entityName << endl;

										#ifdef GIA_TRANSLATOR_DREAM_MODE_LINK_SPECIFIC_CONCEPTS_AND_ACTIONS
										//Part 2b: generate object initialisations based on substance concepts (class inheritance)
										generateObjectInitialisationsBasedOnSubstanceConcepts(parentEntity, currentCodeBlockInTree, sentenceIndex);
										#endif

										#ifdef NLC_DEBUG
										cout << "\tgenerateObjectInitialisationsBasedOnPropertiesAndConditions:" << parentEntity->entityName << endl;
										cout << "sentenceIndex = " << sentenceIndex << endl;
										#endif
										performedAtLeastParentObjectInitialisation = generateObjectInitialisationsBasedOnPropertiesAndConditions(parentEntity, currentCodeBlockInTree, sentenceIndex, "", "", false);
									#ifdef NLC_VERIFY_CONNECTIONS_SENTENCE_INDEX
									}
									#endif
								}
							}
						#ifndef NLC_DEFINE_LOCAL_VARIABLES_FOR_ALL_INDEFINATE_ENTITIES
						}
						#endif
					}
				}
			}
		}
		#endif

	#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
	}
	#endif

	return performedAtLeastParentObjectInitialisation;
}









GIAentityNode * getParent(GIAentityNode * currentEntity, int sentenceIndex, bool parseConditionParents)
{
	if(!(currentEntity->propertyNodeReverseList->empty()))
	{
		GIAentityConnection * parentConnection = currentEntity->propertyNodeReverseList->back();
		GIAentityNode * parentEntity = parentConnection->entity;

		#ifdef NLC_DEFINE_LOCAL_VARIABLES_FOR_ALL_INDEFINATE_ENTITIES
		if(checkSentenceIndexParsingCodeBlocks(parentEntity, parentConnection, sentenceIndex, false))	//NB will parse references to entities in previous sentence
		#else
		if(checkSentenceIndexParsingCodeBlocks(parentEntity, parentConnection, sentenceIndex, false) || parentEntity->NLCparsedForCodeBlocks)
		#endif
		{
			currentEntity = getParent(parentEntity, sentenceIndex, parseConditionParents);
		}
	}
	else if(!(currentEntity->incomingConditionNodeList->empty()) && parseConditionParents)
	{//added 1e9a
		GIAentityConnection * conditionConnection = currentEntity->incomingConditionNodeList->back();
		GIAentityNode * conditionEntity = conditionConnection->entity;

		bool foundConditionSubject = false;
		GIAentityNode * conditionSubject = NULL;
		if(!(conditionEntity->conditionSubjectEntity->empty()))
		{
			conditionSubject = (conditionEntity->conditionSubjectEntity->back())->entity;
			foundConditionSubject = true;

			#ifdef NLC_DEFINE_LOCAL_VARIABLES_FOR_ALL_INDEFINATE_ENTITIES
			if(checkSentenceIndexParsingCodeBlocks(conditionSubject, conditionConnection, sentenceIndex, false))	//NB will parse references to entities in previous sentence
			#else
			if(checkSentenceIndexParsingCodeBlocks(conditionSubject, conditionConnection, sentenceIndex, false) || conditionSubject->NLCparsedForCodeBlocks)
			#endif
			{
				currentEntity = getParent(conditionSubject, sentenceIndex, parseConditionParents);
			}
		}
	}

	return currentEntity;
}







//added recursion 1e8a
bool generateObjectInitialisationsBasedOnPropertiesAndConditions(GIAentityNode * entity, NLCcodeblock ** currentCodeBlockInTree, int sentenceIndex, string parentName, string parentConditionName, bool onlyGenerateContextBlocksIfContextNotGeneratedForNLC)
{
	bool performedAtLeastOneObjectInitialisation = false;
	if(!(entity->isSubstanceConcept) && !(entity->isActionConcept))
	{
		//property initialisations
		for(vector<GIAentityConnection*>::iterator propertyNodeListIterator = entity->propertyNodeList->begin(); propertyNodeListIterator < entity->propertyNodeList->end(); propertyNodeListIterator++)
		{
			GIAentityConnection * propertyConnection = (*propertyNodeListIterator);
			GIAentityNode* propertyEntity = propertyConnection->entity;
			#ifdef NLC_DEBUG
			//cout << "\t\tpropertyConnection->sentenceIndexTemp = " << propertyConnection->sentenceIndexTemp << endl;
			#endif
			if((checkSentenceIndexParsingCodeBlocks(propertyEntity, sentenceIndex, false) || propertyEntity->NLCparsedForCodeBlocks) && (propertyConnection->sentenceIndexTemp == sentenceIndex))
			{//only write properties that are explicated in current sentence

				bool performedAtLeastOneObjectInitialisationAtThisLevel = false;
				NLCcodeblock * firstCodeBlockInSection = *currentCodeBlockInTree;

				#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
				if(!onlyGenerateContextBlocksIfContextNotGeneratedForNLC || !(entity->NLCcontextGenerated))
				{//context block already created by initialiseParentIfNecessaryOrGenerateCodeBlocks():generateContextBlocks()	//added 1g14b 15-July-2014
				#endif

					//cout << "entity->entityName = " << entity->entityName << endl;
					//for(all items in context){
					NLCitem * entityClass = new NLCitem(entity, NLC_ITEM_TYPE_CLASS);
					if(assumedToAlreadyHaveBeenDeclared(entity))
					{
						//DEBUG:
						//*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("1createCodeBlockForPropertyListLocal") + entity->entityName);

						*currentCodeBlockInTree = createCodeBlockForPropertyListLocal(*currentCodeBlockInTree, entityClass);
					}
					else
					{
						//DEBUG:
						//*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("2createCodeBlockForPropertyList") + entity->entityName);

						entityClass->context.push_back(parentName);
						*currentCodeBlockInTree = createCodeBlockForPropertyList(*currentCodeBlockInTree, entityClass);
					}
				#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
				}
				#endif

				#ifdef NLC_DEBUG
				cout << "\t\tcreateCodeBlockForPropertyList: " << entity->entityName << endl;
				#endif

				if(!(propertyConnection->NLCparsedForCodeBlocks))
				{
					#ifdef NLC_TRANSLATE_NEGATIVE_PROPERTIES_AND_CONDITIONS
					if(propertyConnection->negative || (propertyEntity->isSubstanceQuality && propertyEntity->negative))
					{
						#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS
						if(assumedToAlreadyHaveBeenDeclared(propertyEntity))
						{
							//cout << "propertyEntity->entityName = " << propertyEntity->entityName << endl;

							//NLCcodeblock * firstCodeBlockInSection2 = *currentCodeBlockInTree;

							NLCitem * propertyClass = new NLCitem(propertyEntity, NLC_ITEM_TYPE_CLASS);
							*currentCodeBlockInTree = createCodeBlockRemovePropertiesFromLocalList(*currentCodeBlockInTree, propertyEntity);

							*currentCodeBlockInTree = createCodeBlockRemoveProperties(*currentCodeBlockInTree, entity, propertyEntity);
							#ifdef NLC_DEBUG
							cout << "createCodeBlockRemoveProperties: " << entity->entityName << ", " << propertyEntity->entityName << endl;
							#endif
							//*currentCodeBlockInTree = firstCodeBlockInSection2->next;
						}
						else
						{
						#endif
							//remove properties; eg "a ball" in "Tom has a ball"

							*currentCodeBlockInTree = createCodeBlockRemoveProperties(*currentCodeBlockInTree, entity, propertyEntity);
							#ifdef NLC_DEBUG
							cout << "createCodeBlockRemoveProperties: " << entity->entityName << ", " << propertyEntity->entityName << endl;
							#endif
						#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS
						}
						#endif

						#ifdef NLC_DEBUG
						cout << "generateObjectInitialisationsBasedOnPropertiesAndConditions():" << endl;
						cout << "entity->entityName = " << entity->entityName << endl;
						cout << "propertyEntity->entityName = " << propertyEntity->entityName << endl;
						#endif

						propertyConnection->NLCparsedForCodeBlocks = true;
						propertyEntity->NLCparsedForCodeBlocks = true;		//added 3 October 2013 NLC1b2b - used for quick access of instances already declared in current context

					}
					else
					{
					#endif
						#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS
						if(assumedToAlreadyHaveBeenDeclared(propertyEntity))
						{
							//DEBUG:
							//*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("3createCodeBlockAddNewProperty") + entity->entityName + string(" ") + convertIntToString(entity->NLClocalListVariableHasBeenInitialised) + string(" ") + propertyEntity->entityName + string(" ") + convertIntToString(propertyEntity->NLClocalListVariableHasBeenInitialised));

							//use function argument PropertyList (do not create a new property); eg "the ball" in "Tom has the ball"
							//cout << "propertyEntity->entityName = " << propertyEntity->entityName << endl;
							//for(all items in context){

							NLCcodeblock * firstCodeBlockInSection2 = *currentCodeBlockInTree;

							#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
							if(!onlyGenerateContextBlocksIfContextNotGeneratedForNLC)
							{//context block already created by initialiseParentIfNecessaryOrGenerateCodeBlocks():generateContextBlocks()	//added 1g14b 15-July-2014
							#endif
								NLCitem * propertyClass = new NLCitem(propertyEntity, NLC_ITEM_TYPE_CLASS);
								*currentCodeBlockInTree = createCodeBlockForPropertyListLocal(*currentCodeBlockInTree, propertyClass);
							#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
							}
							#endif

							*currentCodeBlockInTree = createCodeBlockAddProperty(*currentCodeBlockInTree, entity, propertyEntity, sentenceIndex);
							#ifdef NLC_DEBUG
							cout << "createCodeBlockAddProperty: " << entity->entityName << ", " << propertyEntity->entityName << endl;
							#endif
							*currentCodeBlockInTree = firstCodeBlockInSection2->next;
						}
						else
						{
						#endif
							//DEBUG:
							//*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("4createCodeBlockAddNewProperty") + entity->entityName + string(" ") + propertyEntity->entityName);

							//create a new property; eg "a ball" in "Tom has a ball"

							*currentCodeBlockInTree = createCodeBlockAddNewProperty(*currentCodeBlockInTree, entity, propertyEntity, sentenceIndex, true);
							#ifdef NLC_DEBUG
							cout << "createCodeBlockAddNewProperty: " << entity->entityName << ", " << propertyEntity->entityName << endl;
							#endif
						#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS
						}
						#endif

						#ifdef NLC_DEBUG
						cout << "\t\tgenerateObjectInitialisationsBasedOnPropertiesAndConditions():" << endl;
						cout << "\t\tentity->entityName = " << entity->entityName << endl;
						cout << "\t\tpropertyEntity->entityName = " << propertyEntity->entityName << endl;
						#endif

						propertyConnection->NLCparsedForCodeBlocks = true;
						propertyEntity->NLCparsedForCodeBlocks = true;		//added 3 October 2013 NLC1b2b - used for quick access of instances already declared in current context

						//moved 1e1b: only generate object initialisations for items based on subject concepts when items are created in context
						#ifdef GIA_TRANSLATOR_DREAM_MODE_LINK_SPECIFIC_CONCEPTS_AND_ACTIONS
						//Part 2b: generate object initialisations based on substance concepts (class inheritance)
						generateObjectInitialisationsBasedOnSubstanceConcepts(propertyEntity, currentCodeBlockInTree, sentenceIndex);
						#endif
					#ifdef NLC_TRANSLATE_NEGATIVE_PROPERTIES_AND_CONDITIONS
					}
					#endif

					performedAtLeastOneObjectInitialisationAtThisLevel = true;
				}

				NLCcodeblock * firstCodeBlockBeforeRecursion = *currentCodeBlockInTree;
				bool performedAtLeastOneObjectInitialisationAtALowerLevel = generateObjectInitialisationsBasedOnPropertiesAndConditions(propertyEntity, currentCodeBlockInTree, sentenceIndex, generateInstanceName(entity), "", onlyGenerateContextBlocksIfContextNotGeneratedForNLC);
				#ifdef NLC_DEBUG
				cout << "performedAtLeastOneObjectInitialisationAtALowerLevel = " << performedAtLeastOneObjectInitialisationAtALowerLevel << endl;
				#endif
				generateObjectInitialisationsBasedOnPropertiesAndConditionsUpdateCodeBlockPointer(currentCodeBlockInTree, firstCodeBlockBeforeRecursion, firstCodeBlockInSection, performedAtLeastOneObjectInitialisationAtThisLevel, performedAtLeastOneObjectInitialisationAtALowerLevel, &performedAtLeastOneObjectInitialisation);
			}
		}

		#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS
		//added NLC 1g5e:
		if(!(entity->isCondition))
		{//do not parse conditions of conditions as one of the conditions is a logical condition conjunction (ie and/or)
		#endif
			//state initialisations
			for(vector<GIAentityConnection*>::iterator conditionNodeListIterator = entity->conditionNodeList->begin(); conditionNodeListIterator < entity->conditionNodeList->end(); conditionNodeListIterator++)
			{
				GIAentityConnection * conditionConnection = (*conditionNodeListIterator);
				GIAentityNode* conditionEntity = conditionConnection->entity;

				#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
				if(!(conditionEntity->NLClogicalConditionOperation))
				//if(!(conditionConnection->NLCparsedForlogicalConditionOperations) && !(conditionEntity->NLCparsedForlogicalConditionOperations))	//this alternative test would require "tagAllEntitiesInSentenceSubsetAsPertainingToLogicalConditionOperation(conditionSubject, sentenceIndex, false);" to be called before "generateObjectInitialisationsBasedOnPropertiesAndConditions()"
				{
				#endif
					bool foundConditionObject = false;
					GIAentityNode * conditionObject = NULL;
					if(!(conditionEntity->conditionObjectEntity->empty()))
					{
						conditionObject = (conditionEntity->conditionObjectEntity->back())->entity;
						foundConditionObject = true;

						if((checkSentenceIndexParsingCodeBlocks(conditionEntity, sentenceIndex, false) || conditionEntity->NLCparsedForCodeBlocks) && (conditionConnection->sentenceIndexTemp == sentenceIndex))
						{//only write conditions that are explicated in current sentence

							bool performedAtLeastOneObjectInitialisationAtThisLevel = false;
							NLCcodeblock * firstCodeBlockInSection = *currentCodeBlockInTree;

							//cout << "entity->entityName = " << entity->entityName << endl;
							//for(all items in context){
							NLCitem * entityClass = new NLCitem(entity, NLC_ITEM_TYPE_CLASS);
							NLCitem * conditionObjectClass = new NLCitem(conditionObject, NLC_ITEM_TYPE_CLASS);

							#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
							if(!onlyGenerateContextBlocksIfContextNotGeneratedForNLC || !(entity->NLCcontextGenerated))
							{//context block already created by initialiseParentIfNecessaryOrGenerateCodeBlocks():generateContextBlocks()	//added 1g14b 15-July-2014
							#endif
								if(assumedToAlreadyHaveBeenDeclared(entity))
								{
									/*
									cout << "\tassumedToAlreadyHaveBeenDeclared" << endl;
									cout << "parentName = " << parentName << endl;
									cout << "entity = " << entity->entityName << endl;
									cout << "conditionEntity = " << conditionEntity->entityName << endl;
									cout << "conditionObject = " << conditionObject->entityName << endl;
									*/
									*currentCodeBlockInTree = createCodeBlockForPropertyListLocal(*currentCodeBlockInTree, entityClass);
								}
								else
								{
									/*
									cout << "\t!assumedToAlreadyHaveBeenDeclared" << endl;
									cout << "parentName = " << parentName << endl;
									cout << "entity = " << entity->entityName << endl;
									cout << "conditionEntity = " << conditionEntity->entityName << endl;
									cout << "conditionObject = " << conditionObject->entityName << endl;
									*/
									NLCitem * parentConditionItem = new NLCitem(parentConditionName, NLC_ITEM_TYPE_CLASS);
									parentConditionItem->context.push_back(parentName);
									*currentCodeBlockInTree = createCodeBlockForConditionList(*currentCodeBlockInTree, parentConditionItem, entityClass);
								}
							#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
							}
							#endif

							if(!(conditionConnection->NLCparsedForCodeBlocks))
							{
								#ifdef NLC_DEBUG
								cout << "!(conditionConnection->NLCparsedForCodeBlocks): " << conditionObject->entityName << endl;
								#endif

								#ifdef NLC_TRANSLATE_NEGATIVE_PROPERTIES_AND_CONDITIONS
								if(conditionEntity->negative)
								{
									#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS
									if(assumedToAlreadyHaveBeenDeclared(conditionObject))
									{
										//NLCcodeblock * firstCodeBlockInSection2 = *currentCodeBlockInTree;
										//cout << "conditionObject->entityName = " << conditionObject->entityName << endl;

										*currentCodeBlockInTree = createCodeBlockRemovePropertiesFromLocalList(*currentCodeBlockInTree, conditionObject);

										*currentCodeBlockInTree = createCodeBlockRemoveConditions(*currentCodeBlockInTree, entity, conditionEntity);

										//*currentCodeBlockInTree = firstCodeBlockInSection2->next;
									}
									else
									{
									#endif
										//create a new condition; eg "a house" in "Tom is near a house"
										*currentCodeBlockInTree = createCodeBlockRemoveConditions(*currentCodeBlockInTree, entity, conditionEntity);

									#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS
									}
									#endif

									conditionConnection->NLCparsedForCodeBlocks = true;
									conditionEntity->NLCparsedForCodeBlocks = true;	//added 3 October 2013 NLC1b2b - used for quick access of instances already declared in current context
									conditionObject->NLCparsedForCodeBlocks = true;	//added 1e6d

								}
								else
								{
								#endif
									#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS
									if(assumedToAlreadyHaveBeenDeclared(conditionObject))
									{
										NLCcodeblock * firstCodeBlockInSection2 = *currentCodeBlockInTree;

										//use function argument PropertyList (do not create a new property to insert into condition); eg "the house" in "Tom is near a house"
										//cout << "conditionObject->entityName = " << conditionObject->entityName << endl;
										//for(all items in context){

										#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
										if(!onlyGenerateContextBlocksIfContextNotGeneratedForNLC)
										{//context block already created by initialiseParentIfNecessaryOrGenerateCodeBlocks():generateContextBlocks()	//added 1g14b 15-July-2014
										#endif
											*currentCodeBlockInTree = createCodeBlockForPropertyListLocal(*currentCodeBlockInTree, conditionObjectClass);
										#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
										}
										#endif

										*currentCodeBlockInTree = createCodeBlockAddCondition(*currentCodeBlockInTree, entity, conditionEntity, sentenceIndex);

										*currentCodeBlockInTree = firstCodeBlockInSection2->next;
									}
									else
									{
									#endif
										//create a new condition; eg "a house" in "Tom is near a house"
										*currentCodeBlockInTree = createCodeBlockAddNewCondition(*currentCodeBlockInTree, entity, conditionEntity, sentenceIndex, true);

									#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS
									}
									#endif

									conditionConnection->NLCparsedForCodeBlocks = true;
									conditionEntity->NLCparsedForCodeBlocks = true;	//added 3 October 2013 NLC1b2b - used for quick access of instances already declared in current context
									conditionObject->NLCparsedForCodeBlocks = true;	//added 1e6d

									//moved 1e1b: only generate object initialisations for items based on subject concepts when items are created in context
									#ifdef GIA_TRANSLATOR_DREAM_MODE_LINK_SPECIFIC_CONCEPTS_AND_ACTIONS
									//Part 2b: generate object initialisations based on substance concepts (class inheritance)
									generateObjectInitialisationsBasedOnSubstanceConcepts(conditionEntity, currentCodeBlockInTree, sentenceIndex);
									#endif
								#ifdef NLC_TRANSLATE_NEGATIVE_PROPERTIES_AND_CONDITIONS
								}
								#endif

								performedAtLeastOneObjectInitialisationAtThisLevel = true;
							}


							NLCcodeblock * firstCodeBlockBeforeRecursion = *currentCodeBlockInTree;
							bool performedAtLeastOneObjectInitialisationAtALowerLevel = generateObjectInitialisationsBasedOnPropertiesAndConditions(conditionObject, currentCodeBlockInTree, sentenceIndex, generateInstanceName(entity), conditionEntity->entityName, onlyGenerateContextBlocksIfContextNotGeneratedForNLC);

							generateObjectInitialisationsBasedOnPropertiesAndConditionsUpdateCodeBlockPointer(currentCodeBlockInTree, firstCodeBlockBeforeRecursion, firstCodeBlockInSection, performedAtLeastOneObjectInitialisationAtThisLevel, performedAtLeastOneObjectInitialisationAtALowerLevel, &performedAtLeastOneObjectInitialisation);
						}
					}
					else
					{
						//no condition object
					}
				#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
				}
				#endif
			}
		#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS
		}
		#endif
	}
	return performedAtLeastOneObjectInitialisation;
}

void generateObjectInitialisationsBasedOnPropertiesAndConditionsUpdateCodeBlockPointer(NLCcodeblock ** currentCodeBlockInTree, NLCcodeblock * firstCodeBlockBeforeRecursion, NLCcodeblock * firstCodeBlockInSection, bool performedAtLeastOneObjectInitialisationAtThisLevel, bool performedAtLeastOneObjectInitialisationAtALowerLevel, bool * performedAtLeastOneObjectInitialisation)
{
	if(!performedAtLeastOneObjectInitialisationAtALowerLevel)
	{
		if(performedAtLeastOneObjectInitialisationAtThisLevel)
		{
			clearCodeBlock(firstCodeBlockBeforeRecursion);

			*currentCodeBlockInTree = firstCodeBlockInSection;
			while((*currentCodeBlockInTree)->next != NULL)
			{
				*currentCodeBlockInTree = (*currentCodeBlockInTree)->next;
			}
		}
		else
		{
			//erase redundant for loops:
			*currentCodeBlockInTree = firstCodeBlockInSection;
			clearCodeBlock(*currentCodeBlockInTree);
		}
	}
	else
	{
		*currentCodeBlockInTree = firstCodeBlockInSection;
		while((*currentCodeBlockInTree)->next != NULL)
		{
			*currentCodeBlockInTree = (*currentCodeBlockInTree)->next;
		}
	}
	if(performedAtLeastOneObjectInitialisationAtThisLevel || performedAtLeastOneObjectInitialisationAtALowerLevel)
	{
		*performedAtLeastOneObjectInitialisation = true;
	}
}

#ifdef GIA_TRANSLATOR_DREAM_MODE_LINK_SPECIFIC_CONCEPTS_AND_ACTIONS
void generateObjectInitialisationsBasedOnSubstanceConcepts(GIAentityNode * entity, NLCcodeblock ** currentCodeBlockInTree, int sentenceIndex)
{
	//added 6 December 2013: take into account plain concepts; eg "dogs are fat. The dog rides the bike." <- the dog will be given the property 'fat'
	GIAentityNode * conceptEntity = (entity->entityNodeDefiningThisInstance->back())->entity;
	generateObjectInitialisationsBasedOnSubstanceConceptsRecurse(entity, conceptEntity, currentCodeBlockInTree, sentenceIndex, "", "");

	for(vector<GIAentityConnection*>::iterator entityNodeDefinitionListIterator = entity->entityNodeDefinitionList->begin(); entityNodeDefinitionListIterator < entity->entityNodeDefinitionList->end(); entityNodeDefinitionListIterator++)
	{
		GIAentityConnection * definitionConnection = (*entityNodeDefinitionListIterator);
		//if(!(definitionConnection->NLCparsedForCodeBlocks))	//probably not required
		//{
		GIAentityNode* definitionEntity = definitionConnection->entity;
		//check the definition is a substance concept
		if((definitionEntity->isSubstanceConcept) || (definitionEntity->isActionConcept))	//added (definitionEntity->isActionConcept)  changed 1e2e
		{
			//cout << "isSubstanceConcept" << endl;
			definitionConnection->NLCparsedForCodeBlocks = true;

			generateObjectInitialisationsBasedOnSubstanceConceptsRecurse(entity, definitionEntity, currentCodeBlockInTree, sentenceIndex, "", "");
		}
		//}
	}
}

void generateObjectInitialisationsBasedOnSubstanceConceptsRecurse(GIAentityNode * entity, GIAentityNode * definitionEntity, NLCcodeblock ** currentCodeBlockInTree, int sentenceIndex, string parentName, string parentConditionName)
{
	#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_BASED_ON_CONCEPTS
	if(!(definitionEntity->NLCparsedForlogicalConditionOperations))
	{
	#endif
		//property initialisations
		for(vector<GIAentityConnection*>::iterator propertyNodeListIterator = definitionEntity->propertyNodeList->begin(); propertyNodeListIterator < definitionEntity->propertyNodeList->end(); propertyNodeListIterator++)
		{
			GIAentityConnection * propertyConnection = (*propertyNodeListIterator);
			GIAentityNode* propertyEntity = propertyConnection->entity;

			bool alreadyAdded = checkDuplicateProperty(propertyEntity, entity);
			if(!alreadyAdded)
			{
				NLCcodeblock * firstCodeBlockInSection = *currentCodeBlockInTree;
				bool loopUsed = false;

				//cout << "property initialisation: entity->entityName = " << entity->entityName << endl;
				//for(all items in context){
				NLCitem * entityClass = new NLCitem(entity, NLC_ITEM_TYPE_CLASS);
				if(assumedToAlreadyHaveBeenDeclared(entity))
				{
					*currentCodeBlockInTree = createCodeBlockForPropertyListLocal(*currentCodeBlockInTree, entityClass);
				}
				else
				{
					//bool entityHasParent = getEntityContext(entity, &(entityClass->context), false, sentenceIndex, true);
					entityClass->context.push_back(parentName);
					*currentCodeBlockInTree = createCodeBlockForPropertyList(*currentCodeBlockInTree, entityClass);
				}

				*currentCodeBlockInTree = createCodeBlockAddNewProperty(*currentCodeBlockInTree, entity, propertyEntity, sentenceIndex, false);

				entity->NLCparsedForCodeBlocks = true;			//added 4 October 2013 NLC1b6b  - used for quick access of instances already declared in current context
				generateObjectInitialisationsBasedOnSubstanceConceptsRecurse(entity, propertyEntity, currentCodeBlockInTree, sentenceIndex, generateInstanceName(definitionEntity), "");		//updated 9 November 2013 - support recursion of complex substance concept definition

				*currentCodeBlockInTree = firstCodeBlockInSection->next;
			}
		}
		//state initialisations
		for(vector<GIAentityConnection*>::iterator conditionNodeListIterator = definitionEntity->conditionNodeList->begin(); conditionNodeListIterator < definitionEntity->conditionNodeList->end(); conditionNodeListIterator++)
		{
			GIAentityConnection * conditionConnection = (*conditionNodeListIterator);
			GIAentityNode* conditionEntity = conditionConnection->entity;

			bool alreadyAdded = checkDuplicateCondition(conditionEntity, entity);
			if(!alreadyAdded)
			{
				NLCcodeblock * firstCodeBlockInSection = *currentCodeBlockInTree;

				bool foundConditionObject = false;
				GIAentityNode * conditionObject = NULL;
				if(!(conditionEntity->conditionObjectEntity->empty()))
				{
					conditionObject = (conditionEntity->conditionObjectEntity->back())->entity;
					foundConditionObject = true;

					//cout << "condition initialisation:  entity->entityName = " << entity->entityName << endl;
					//for(all items in context){
					NLCitem * entityClass = new NLCitem(entity, NLC_ITEM_TYPE_CLASS);

					if(assumedToAlreadyHaveBeenDeclared(entity))
					{
						*currentCodeBlockInTree = createCodeBlockForPropertyListLocal(*currentCodeBlockInTree, entityClass);
					}
					else
					{
						NLCitem * parentConditionItem = new NLCitem(parentConditionName, NLC_ITEM_TYPE_CLASS);
						parentConditionItem->context.push_back(parentName);
						*currentCodeBlockInTree = createCodeBlockForConditionList(*currentCodeBlockInTree, parentConditionItem, entityClass);
					}

					*currentCodeBlockInTree = createCodeBlockAddNewCondition(*currentCodeBlockInTree, entity, conditionEntity, sentenceIndex, false);

					entity->NLCparsedForCodeBlocks = true;			//added 4 October 2013 NLC1b6b  - used for quick access of instances already declared in current context
					generateObjectInitialisationsBasedOnSubstanceConceptsRecurse(entity, conditionObject, currentCodeBlockInTree, sentenceIndex, generateInstanceName(definitionEntity), conditionEntity->entityName);	//updated 9 November 2013 - support recursion of complex substance concept definition

					*currentCodeBlockInTree = firstCodeBlockInSection->next;
				}

			}
		}
	#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_BASED_ON_CONCEPTS
	}
	#endif
}
#endif



