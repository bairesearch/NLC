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
 * Project Version: 1j15b 16-September-2014
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/



#include <ctime>
#include <cstdlib>	//for random number generation
#include <cmath>

#include "NLCtranslatorCodeBlocksOperations.h"
#include "GIAtranslatorDefs.h"
#include "GIAtranslatorOperations.h"	//required for getPrimaryConceptNodeDefiningInstance()


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
			//this is where original getParentAndInitialiseParentIfNecessaryOrGenerateContextBlocks code went (for both subjectEntity and objectEntity)
			getParentAndGenerateParentInitialisationCodeBlock(currentCodeBlockInTree, subjectEntity, sentenceIndex, true, false);	//parseConditionParents was previously set false in original implementation [although the GIA specification supports such arrangements, in practice however they probably can't be generated as x will always be a condition subject not a condition object of y in "x is near the y"]
			getParentAndGenerateParentInitialisationCodeBlock(currentCodeBlockInTree, objectEntity, sentenceIndex, true, false);	//parseConditionParents was previously set false in original implementation [although the GIA specification supports such arrangements, in practice however they probably can't be generated as x will always be a condition subject not a condition object of y in "x is near the y"]
			#endif

		}


		if(actionHasObject)
		{
			NLClogicalConditionConjunctionVariables logicalConditionConjunctionVariables;	//not used
			if(getParentAndInitialiseParentIfNecessaryOrGenerateContextBlocks(currentCodeBlockInTree, objectEntity, sentenceIndex, &logicalConditionConjunctionVariables, true, false))	//parseConditionParents was previously set false in original implementation [although the GIA specification supports such arrangements, in practice however they probably can't be generated as x will always be a condition subject not a condition object of y in "x is near the y"]
			{
				//cout << "actionHasObject: parent and its children initialised" << endl;
			}
			if(actionHasSubject)
			{
				NLClogicalConditionConjunctionVariables logicalConditionConjunctionVariables;	//not used
				//cout  << "subjectEntity = " << subjectEntity->entityName << endl;
				if(getParentAndInitialiseParentIfNecessaryOrGenerateContextBlocks(currentCodeBlockInTree, subjectEntity, sentenceIndex, &logicalConditionConjunctionVariables, true, false))	//parseConditionParents was previously set false in original implementation [although the GIA specification supports such arrangements, in practice however they probably can't be generated as x will always be a condition subject not a condition object of y in "x is near the y"]
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
			if(getParentAndInitialiseParentIfNecessaryOrGenerateContextBlocks(currentCodeBlockInTree, subjectEntity, sentenceIndex, &logicalConditionConjunctionVariables, true, false))	//parseConditionParents was previously set false in original implementation [although the GIA specification supports such arrangements, in practice however they probably can't be generated as x will always be a condition subject not a condition object of y in "x is near the y"]
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
	
	if(!generateParentInitialisationCodeBlock(currentCodeBlockInTree, actionEntity, sentenceIndex))
	{
		
	}
}
#endif












bool getParentAndInitialiseParentIfNecessaryOrGenerateContextBlocks(NLCcodeblock ** currentCodeBlockInTree, GIAentityNode * currentEntity, int sentenceIndex, NLClogicalConditionConjunctionVariables * logicalConditionConjunctionVariables, bool parseConditionParents, bool parseLogicalConditions)
{
	GIAentityNode * parentEntity = getParent(currentEntity, sentenceIndex, parseConditionParents);

	bool result = false;
	if(checkSentenceIndexParsingCodeBlocks(currentEntity, sentenceIndex, false))
	{//is this required?
		result = initialiseParentIfNecessaryOrGenerateCodeBlocks(currentCodeBlockInTree, parentEntity, sentenceIndex, logicalConditionConjunctionVariables, parseConditionParents, parseLogicalConditions);
	}

	return result;

}
//added 1e6a
bool initialiseParentIfNecessaryOrGenerateCodeBlocks(NLCcodeblock ** currentCodeBlockInTree, GIAentityNode * parentEntity, int sentenceIndex, NLClogicalConditionConjunctionVariables * logicalConditionConjunctionVariables, bool parseConditionParents, bool parseLogicalConditions)
{
	bool result = false;

	#ifdef NLC_DEBUG
	cout << "\tgenerateContextBlocksAndInitialiseParentIfNecessary parent: " << parentEntity->entityName << endl;
	#endif

	if(generateParentInitialisationCodeBlockWithChecks(currentCodeBlockInTree, parentEntity, sentenceIndex, parseLogicalConditions))
	{
		#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_BLOCKS_FOR_PARENT_INITIALISATION_SPECIAL
		*currentCodeBlockInTree = createCodeBlockForPropertyListCategory(*currentCodeBlockInTree, parentEntity, NLC_ITEM_TYPE_CATEGORYVAR_APPENDITION);
		#else
		generateContextBlocks(currentCodeBlockInTree, parentEntity, sentenceIndex, logicalConditionConjunctionVariables, false, NLC_ITEM_TYPE_CATEGORYVAR_APPENDITION);
		#endif
		result = true;
	}
	else
	{
		generateContextBlocks(currentCodeBlockInTree, parentEntity, sentenceIndex, logicalConditionConjunctionVariables, false, NLC_ITEM_TYPE_CATEGORYVAR_APPENDITION);
	}

	return result;
}





























#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN
bool generateContextBlocks(NLCcodeblock ** currentCodeBlockInTree, GIAentityNode * parentEntity, int sentenceIndex, NLClogicalConditionConjunctionVariables * logicalConditionConjunctionVariables, bool generatedParentContext, string genericListAppendName)
{	
	return generateContextBlocksCategories(currentCodeBlockInTree, parentEntity, sentenceIndex, logicalConditionConjunctionVariables, generatedParentContext, genericListAppendName);	
}

bool generateContextBlocksCategories(NLCcodeblock ** currentCodeBlockInTree, GIAentityNode * parentEntity, int sentenceIndex, NLClogicalConditionConjunctionVariables * logicalConditionConjunctionVariables, bool generatedParentContext, string genericListAppendName)
{			
	bool contextFound = false;
	*currentCodeBlockInTree = createCodeBlocksDeclareNewCategoryListVariable(*currentCodeBlockInTree, parentEntity, genericListAppendName);

	NLCcodeblock * lastCodeBlockInTree = *currentCodeBlockInTree;
	if(generateContextBlocksSimple(currentCodeBlockInTree, parentEntity, sentenceIndex, logicalConditionConjunctionVariables, generatedParentContext, genericListAppendName))
	{
		contextFound = true;
	}

	addPropertyToCategoryList(currentCodeBlockInTree, parentEntity, parentEntity, genericListAppendName);

	if(!(generatedParentContext && !contextFound))
	{
		*currentCodeBlockInTree = lastCodeBlockInTree->next;
	}

	lastCodeBlockInTree = *currentCodeBlockInTree;
	#ifdef NLC_DEBUG_PARSE_CONTEXT_CHILDREN
	cout << "contextFound: parentEntity = " << parentEntity->entityName << endl;
	#endif
	
	//eg "A yellow bannana is on the table. Yellow bannanas are fruit. The fruit is tasty."
	for(vector<GIAentityConnection*>::iterator definitionNodeListIterator = parentEntity->entityNodeDefinitionList->begin(); definitionNodeListIterator < parentEntity->entityNodeDefinitionList->end(); definitionNodeListIterator++)
	{
		GIAentityNode* parentSubstanceConcept = (*definitionNodeListIterator)->entity;	//e.g. "fruit" substance concept
		if(parentSubstanceConcept->isSubstanceConcept)
		{		
			#ifdef NLC_DEBUG_PARSE_CONTEXT_CHILDREN	
			cout << "NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN: createCodeBlockForStatementsForDefinitionChildren(): parentSubstanceConcept = " << parentSubstanceConcept->entityName << ", idInstance = " << parentSubstanceConcept->idInstance << endl;
			#endif
			if(createCodeBlockForStatementsForDefinitionChildren(currentCodeBlockInTree, &lastCodeBlockInTree, parentEntity, parentSubstanceConcept, sentenceIndex, logicalConditionConjunctionVariables, true, genericListAppendName))
			{
				contextFound = true;
			}
		}
	}
	
	#ifdef NLC_CATEGORIES_TEST_PLURALITY
	if((parentEntity->grammaticalNumber == GRAMMATICAL_NUMBER_SINGULAR) && assumedToAlreadyHaveBeenDeclared(parentEntity))	//added assumedToAlreadyHaveBeenDeclared(parentEntity) criteria 1j15a
	{
		#ifdef NLC_CATEGORIES_TEST_PLURALITY_COMMENT
		*currentCodeBlockInTree = createCodeBlockCommentSingleLine(*currentCodeBlockInTree, "Singular definite plurality tests");
		#endif
		
		#ifdef NLC_CATEGORIES_TEST_PLURALITY_WARNING
		NLCcodeblock * lastCodeBlockInTree2 = *currentCodeBlockInTree;
		*currentCodeBlockInTree = createCodeBlockIfHasMoreThanOneCategoryItem(*currentCodeBlockInTree, parentEntity, genericListAppendName);
		*currentCodeBlockInTree = createCodeBlockPrintWarning(*currentCodeBlockInTree, NLC_CATEGORIES_TEST_PLURALITY_WARNING_MESSAGE);
		*currentCodeBlockInTree = lastCodeBlockInTree2->next;
		#endif
		
		#ifdef NLC_CATEGORIES_TEST_PLURALITY_ENFORCE
		*currentCodeBlockInTree = createCodeBlockIfHasCategoryItem(*currentCodeBlockInTree, parentEntity, false, genericListAppendName);	//added 1j5a
		*currentCodeBlockInTree = createCodeBlockGetBackPropertyListCategory(*currentCodeBlockInTree, parentEntity, genericListAppendName);
		#else
		*currentCodeBlockInTree = createCodeBlockForPropertyListCategory(*currentCodeBlockInTree, parentEntity, genericListAppendName);
		#endif
	}
	else
	{
	#endif
		*currentCodeBlockInTree = createCodeBlockForPropertyListCategory(*currentCodeBlockInTree, parentEntity, genericListAppendName);
	#ifdef NLC_CATEGORIES_TEST_PLURALITY
	}
	#endif
	#ifdef NLC_USE_ADVANCED_REFERENCING
	*currentCodeBlockInTree = createCodeBlockUpdateLastSentenceReferenced(*currentCodeBlockInTree, parentEntity, sentenceIndex);
	#endif
	
	return contextFound;

}

bool generateContextBlocksSimple(NLCcodeblock ** currentCodeBlockInTree, GIAentityNode * parentEntity, int sentenceIndex, NLClogicalConditionConjunctionVariables * logicalConditionConjunctionVariables, bool generatedParentContext, string genericListAppendName)
#else
bool generateContextBlocks(NLCcodeblock ** currentCodeBlockInTree, GIAentityNode * parentEntity, int sentenceIndex, NLClogicalConditionConjunctionVariables * logicalConditionConjunctionVariables, bool generatedParentContext, string genericListAppendName)
#endif
{
	bool contextFound = false;
	
	NLCcodeblock * originalCodeBlockInTree = *currentCodeBlockInTree;

	//#ifdef NLC_DEBUG_PARSE_CONTEXT3
	//*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("generateContextBlocksSimple(): ") + parentEntity->entityName);
	//#endif

	if(!generatedParentContext)
	{
		NLCitem * propertyItem = new NLCitem(parentEntity, NLC_ITEM_TYPE_OBJECT);
		//context property item:
		if(assumedToAlreadyHaveBeenDeclared(parentEntity))
		{
			*currentCodeBlockInTree = createCodeBlockForPropertyListLocal(*currentCodeBlockInTree, propertyItem);
			#ifdef NLC_DEBUG_PARSE_CONTEXT3
			*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("finished generateContextBlocksSimple(): 1createCodeBlockForPropertyListLocal: ") + parentEntity->entityName);
			#endif
		}
		else
		{
			*currentCodeBlockInTree = createCodeBlockForPropertyList(*currentCodeBlockInTree, propertyItem);
			#ifdef NLC_DEBUG_PARSE_CONTEXT3
			*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("finished generateContextBlocksSimple(): 2createCodeBlockForPropertyList: ") + parentEntity->entityName);
			#endif
		}
	}

	#ifdef NLC_DEBUG
	cout << "\tgenerateContextBlocks: " << parentEntity->entityName << endl;
	#endif
	//parse the children (properties and conditions) of an undeclared definite parent
	if(!createCodeBlockForStatements(currentCodeBlockInTree, generateInstanceName(parentEntity), parentEntity, sentenceIndex, logicalConditionConjunctionVariables))
	{
		#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
		//if(!generatedParentContext)	//considered adding 1j13b
		//{
		parentEntity->NLCcontextGenerated = true;	//added 1g14b 15-July-2014
		//}		
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


#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN
bool createCodeBlockForStatementsForDefinitionChildren(NLCcodeblock ** currentCodeBlockInTree, NLCcodeblock ** lastCodeBlockInTree, GIAentityNode* parentInstance, GIAentityNode* parentSubstanceConcept, int sentenceIndex, NLClogicalConditionConjunctionVariables * logicalConditionConjunctionVariables, bool generateContext, string genericListAppendName)
{
	bool contextFound = false;
	#ifdef NLC_DEBUG_PARSE_CONTEXT_CHILDREN	
	cout << "\t NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN: createCodeBlockForStatementsForDefinitionChildren(): parentSubstanceConcept = " << parentSubstanceConcept->entityName << endl;		
	#endif
	for(vector<GIAentityConnection*>::iterator reverseDefinitionNodeListIterator = parentSubstanceConcept->entityNodeDefinitionReverseList->begin(); reverseDefinitionNodeListIterator < parentSubstanceConcept->entityNodeDefinitionReverseList->end(); reverseDefinitionNodeListIterator++)
	{
		GIAentityNode* child = (*reverseDefinitionNodeListIterator)->entity;
		if(child != parentInstance)
		{
			if(child->isSubstanceConcept)
			{
				GIAentityNode* childSubstanceConcept = child;
				//recurse; eg "interesting bannanas" in "A yellow bannana is on the table. Interesting bannanas are yellow bannanas. Yellow bannanas are fruit. The fruit is tasty."
				if(createCodeBlockForStatementsForDefinitionChildren(currentCodeBlockInTree, lastCodeBlockInTree, parentInstance, childSubstanceConcept, sentenceIndex, logicalConditionConjunctionVariables, generateContext, genericListAppendName))
				{
					contextFound = true;
				}
			}
			else
			{
				GIAentityNode* childSubstance = child;
				//definition child (e.g. apple)

				//this code is from generateContextBlocksSimple():
				
				NLCitem * propertyItem = new NLCitem(childSubstance, NLC_ITEM_TYPE_OBJECT);
				//context property item:		
				if(assumedToAlreadyHaveBeenDeclared(childSubstance))
				{
					#ifdef NLC_DEBUG_PARSE_CONTEXT_CHILDREN	
					cout << "1 NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN createCodeBlockForPropertyListLocal(): assumedToAlreadyHaveBeenDeclared: childSubstance = " << childSubstance->entityName << endl;
					#endif
					*currentCodeBlockInTree = createCodeBlockForPropertyListLocal(*currentCodeBlockInTree, propertyItem);
				}
				else
				{
					#ifdef NLC_DEBUG_PARSE_CONTEXT_CHILDREN	
					cout << "2 NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN createCodeBlockForPropertyList(): !assumedToAlreadyHaveBeenDeclared: childSubstance = " << childSubstance->entityName << endl;
					#endif
					*currentCodeBlockInTree = createCodeBlockForPropertyList(*currentCodeBlockInTree, propertyItem);
				}	

				if(generateContext)
				{
					if(createCodeBlockForStatements(currentCodeBlockInTree, generateInstanceName(childSubstance), parentInstance, sentenceIndex, logicalConditionConjunctionVariables))
					{
						contextFound = true;
					}
				}
				else
				{
					contextFound = true;
				}
				
				addPropertyToCategoryList(currentCodeBlockInTree, parentInstance, childSubstance, genericListAppendName);
				
				*currentCodeBlockInTree = (*lastCodeBlockInTree);
				while((*currentCodeBlockInTree)->next != NULL)
				{
					(*currentCodeBlockInTree) = (*currentCodeBlockInTree)->next;
				}
				*lastCodeBlockInTree = *currentCodeBlockInTree;
				#ifdef NLC_DEBUG_PARSE_CONTEXT_CHILDREN	
				cout << "3 NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN createCodeBlockForStatements(): contextFound: parentInstance = " << parentInstance->entityName << ", childSubstance = " << childSubstance << endl;
				#endif
			}
		}
	}
	return contextFound;
}

bool addPropertyToCategoryList(NLCcodeblock ** currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* propertyEntity, string genericListAppendName)
{
	bool result = true;
	
	#ifdef NLC_USE_ADVANCED_REFERENCING
	//cout << "entity->entityName = " << entity->entityName << endl;
	//cout << "entity->grammaticalDefiniteTemp = " << entity->grammaticalDefiniteTemp << endl;
	if((entity->grammaticalNumber == GRAMMATICAL_NUMBER_SINGULAR) && assumedToAlreadyHaveBeenDeclared(entity))	//added assumedToAlreadyHaveBeenDeclared(parentEntity) criteria 1j15a
	{
		#ifdef NLC_USE_ADVANCED_REFERENCING_COMMENT
		*currentCodeBlockInTree = createCodeBlockCommentSingleLine(*currentCodeBlockInTree, "Singular definite referencing tests");
		#endif
		*currentCodeBlockInTree = createCodeBlockAddPropertyToCategoryListCheckLastSentenceReferencedSingularExecuteFunction(*currentCodeBlockInTree, entity, propertyEntity, genericListAppendName);
	}
	else
	{
		#ifdef NLC_USE_ADVANCED_REFERENCING_COMMENT
		*currentCodeBlockInTree = createCodeBlockCommentSingleLine(*currentCodeBlockInTree, "Plural definite referencing tests");
		#endif
		*currentCodeBlockInTree = createCodeBlockAddPropertyToCategoryListCheckLastSentenceReferencedPluralExecuteFunction(*currentCodeBlockInTree, entity, propertyEntity, genericListAppendName);
	}
	#else
	*currentCodeBlockInTree = createCodeBlockAddPropertyToCategoryList(*currentCodeBlockInTree, entity, propertyEntity, genericListAppendName);
	#endif
	
	return result;
}	
#endif

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

	//if object near Tom's carparentInstanceName
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
		#ifdef GIA_USE_ADVANCED_REFERENCING
		if((propertyConnection->NLCparsedForCodeBlocks) || !(logicalConditionConjunctionVariables->onlyGenerateContextBlocksIfConnectionsParsedForNLC) || (propertyConnection->isReference) || ((logicalConditionConjunctionVariables->generateContextBlocksIfSameReferenceSet) && (propertyConnection->sameReferenceSet)))	//added option 1g13b/15-July-2014	//added option 1i2a 20-August-2014	//added option 1i3d 21-August-2014	//NB isReference check is probably redundant given sameReferenceSet check
		#else
		if((propertyConnection->NLCparsedForCodeBlocks) || !(logicalConditionConjunctionVariables->onlyGenerateContextBlocksIfConnectionsParsedForNLC) || ((logicalConditionConjunctionVariables->generateContextBlocksIfSameReferenceSet) && (propertyConnection->sameReferenceSet)))	//added option 1g13b/15-July-2014	//added option 1i2a 20-August-2014	//added option 1i3d 21-August-2014
		#endif
		{
		#endif
			GIAentityNode* propertyEntity = propertyConnection->entity;
			if(checkSentenceIndexParsingCodeBlocks(propertyEntity, propertyConnection, sentenceIndex, false))	//changed from true to false 1e5b	//logicalConditionConjunctionVariables->checkSameSentenceConnection
			{//only write conditions that are explicated in current sentence
				#ifdef NLC_DEBUG
				cout << "createCodeBlockForGivenProperties: " << propertyEntity->entityName << endl;
				#endif
				#ifdef NLC_DEBUG_PARSE_CONTEXT
				cout << "createCodeBlockForGivenProperties: " << propertyEntity->entityName << endl;
				cout << "\t propertyConnection->NLCparsedForCodeBlocks: " << propertyConnection->NLCparsedForCodeBlocks << endl;
				cout << "\t logicalConditionConjunctionVariables->onlyGenerateContextBlocksIfConnectionsParsedForNLC: " << logicalConditionConjunctionVariables->onlyGenerateContextBlocksIfConnectionsParsedForNLC << endl;
				#ifdef GIA_USE_ADVANCED_REFERENCING
				cout << "\t propertyConnection->isReference: " << propertyConnection->isReference << endl;
				#endif
				#endif
				#ifdef NLC_DEBUG_PARSE_CONTEXT3
				*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("createCodeBlockForGivenProperties(): ") + entity->entityName + string(" ") + propertyEntity->entityName);
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
					#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
					if(propertyConnection->negative)
					{
						logicalConditionConjunctionVariables->negativeDetectedInContextBlocks = true;
						//cout << "propertyConnection->negative: propertyEntity->entityName = " << propertyEntity->entityName << endl;
					}
					if(propertyEntity->isSubstanceQuality)
					{
						if(propertyEntity->negative)
						{
							//cout << "propertyEntity->negative: propertyEntity->entityName = " << propertyEntity->entityName << endl;
							logicalConditionConjunctionVariables->negativeDetectedInContextBlocks = true;
						}
					}
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
	NLCitem * propertyItem = new NLCitem(propertyEntity, NLC_ITEM_TYPE_OBJECT);

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
		#ifdef GIA_USE_ADVANCED_REFERENCING
		if((conditionConnection->NLCparsedForCodeBlocks) || !(logicalConditionConjunctionVariables->onlyGenerateContextBlocksIfConnectionsParsedForNLC) || (conditionConnection->isReference) || ((logicalConditionConjunctionVariables->generateContextBlocksIfSameReferenceSet) && (conditionConnection->sameReferenceSet)))	//added option 1g13b/15-July-2014	//added option 1i2a 20-August-2014	//added option 1i3d 21-August-2014	//NB isReference check is probably redundant given sameReferenceSet check	
		#else
		if((conditionConnection->NLCparsedForCodeBlocks) || !(logicalConditionConjunctionVariables->onlyGenerateContextBlocksIfConnectionsParsedForNLC) || ((logicalConditionConjunctionVariables->generateContextBlocksIfSameReferenceSet) && (conditionConnection->sameReferenceSet)))	//added option 1g13b/15-July-2014	//added option 1i2a 20-August-2014	//added option 1i3d 21-August-2014		
		#endif
		{
		#endif
			GIAentityNode* conditionEntity = conditionConnection->entity;
			if(checkSentenceIndexParsingCodeBlocks(conditionEntity, conditionConnection, sentenceIndex, false))	//changed from true to false 1e5b	//logicalConditionConjunctionVariables->checkSameSentenceConnection 
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
						if(!(conditionEntity->conditionObjectEntity->empty()))
						{
							GIAentityNode * conditionObject = (conditionEntity->conditionObjectEntity->back())->entity;
							//cout << "conditionObject = " << conditionObject->entityName << endl;
							#ifdef NLC_DEBUG
							cout << "createCodeBlockForGivenConditions: " << conditionEntity->entityName << endl;
							#endif
							#ifdef NLC_DEBUG_PARSE_CONTEXT3
							*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("createCodeBlockForGivenConditions(): ") + entity->entityName + string(" ") + conditionObject->entityName);
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
							#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
							if(conditionEntity->negative)
							{
								//cout << "conditionEntity->negative: conditionEntity->entityName = " << conditionEntity->entityName << endl;
								logicalConditionConjunctionVariables->negativeDetectedInContextBlocks = true;
							}
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

	NLCitem * conditionItem = new NLCitem(conditionEntity, NLC_ITEM_TYPE_OBJECT);
	NLCitem * conditionObjectItem = new NLCitem(conditionObject, NLC_ITEM_TYPE_OBJECT);
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
			{//do not reparse same conjunction conditions - added NLC 1g7b/11 July 2014
				if(*foundLogicalConditionConjunction == NULL)
				{//do not overwrite foundLogicalConditionConjunction; always take the first conjunction in subset as the one to parse next - added NLC 1g6j/10 July 2014
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

	#ifdef NLC_DEBUG_PARSE_CONTEXT
	cout << "generateCodeBlocksObjectInitialisationsForEntity: getParent()" << endl;
	#endif
	GIAentityNode * parentEntity = getParent(entity, sentenceIndex, true);	//parse condition parents in accordance with original generateCodeBlocksPart4objectInitialisations implementation
	#ifdef NLC_DEBUG_PARSE_CONTEXT
	cout << "\tparentEntity = " << parentEntity->entityName << endl;
	cout << "generateCodeBlocksObjectInitialisationsForEntity: generateParentInitialisationCodeBlockWithChecks()" << endl;
	#endif
	if(!generateParentInitialisationCodeBlockWithChecks(currentCodeBlockInTree, parentEntity, sentenceIndex, false))
	{
		#ifdef NLC_DEBUG_PARSE_CONTEXT
		cout << "\tfail generateParentInitialisationCodeBlockWithChecks" << endl;
		cout << "generateCodeBlocksObjectInitialisationsForEntity: generateContextBlocksAndGenerateObjectInitialisationsBasedOnPropertiesAndConditions()" << endl;
		#endif
		if(!generateObjectInitialisationsBasedOnPropertiesAndConditions(parentEntity, currentCodeBlockInTree , sentenceIndex, "", "", true, false))
		{
			*currentCodeBlockInTree = originalCodeBlockInLevel;
			clearCodeBlock(originalCodeBlockInLevel);

			#ifdef NLC_DEBUG_PARSE_CONTEXT
			cout << "\tfail generateContextBlocksAndGenerateObjectInitialisationsBasedOnPropertiesAndConditions" << endl;
			#endif
		}
		else
		{
			*currentCodeBlockInTree = originalCodeBlockInLevel;
			while((*currentCodeBlockInTree)->next != NULL)
			{
				(*currentCodeBlockInTree) = (*currentCodeBlockInTree)->next;
			}
			#ifdef NLC_DEBUG_PARSE_CONTEXT
			cout << "\tpass generateContextBlocksAndGenerateObjectInitialisationsBasedOnPropertiesAndConditions" << endl;
			#endif
		}
	}
	else
	{
		#ifdef NLC_DEBUG_PARSE_CONTEXT
		cout << "\tpass generateParentInitialisationCodeBlockWithChecks" << endl;
		#endif
	}
	return result;
}

#endif

















bool getParentAndGenerateParentInitialisationCodeBlock(NLCcodeblock ** currentCodeBlockInTree, GIAentityNode * entity, int sentenceIndex, bool parseConditionParents, bool parseLogicalConditions)
{
	bool result = false;
	GIAentityNode * parentEntity = getParent(entity, sentenceIndex, parseConditionParents);
	//cout << "parentEntity = " << parentEntity->entityName << endl;

	result = generateParentInitialisationCodeBlockWithChecks(currentCodeBlockInTree, parentEntity, sentenceIndex, parseLogicalConditions);
	return result;
}

bool generateParentInitialisationCodeBlockWithChecks(NLCcodeblock ** currentCodeBlockInTree, GIAentityNode * parentEntity, int sentenceIndex, bool parseLogicalConditions)
{
	bool result = false;

	//cout << "generateParentInitialisationCodeBlockWithChecks: entity->NLCparsedForlogicalConditionOperations = " << entity->NLCparsedForlogicalConditionOperations << endl;
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
										generateParentInitialisationCodeBlock(currentCodeBlockInTree, parentEntity, sentenceIndex);
										result = true;
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

	return result;
}

bool generateParentInitialisationCodeBlock(NLCcodeblock ** currentCodeBlockInTree, GIAentityNode * parentEntity, int sentenceIndex)
{
	bool performedAtLeastParentObjectInitialisation = false;
	
	#ifdef NLC_DEBUG
	cout << "createCodeBlocksCreateNewLocalListVariable: " << parentEntity->entityName << endl;
	#endif
	#ifdef NLC_DEBUG_PARSE_CONTEXT3
	*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("generateParentInitialisationCodeBlockWithChecks(): ") + parentEntity->entityName);
	#endif
	
	*currentCodeBlockInTree = createCodeBlocksCreateNewLocalListVariable(*currentCodeBlockInTree, parentEntity, sentenceIndex);

	parentEntity->NLCparsedForCodeBlocks = true;
	#ifdef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES
	parentEntity->NLClocalListVariableHasBeenInitialised = true;
	#endif
	//cout << "createCodeBlocksCreateNewLocalListVariable: " << parentEntity->entityName << endl;

	#ifdef GIA_TRANSLATOR_DREAM_MODE_LINK_SPECIFIC_CONCEPTS_AND_ACTIONS
	//Part 2b: generate object initialisations based on substance concepts (class inheritance)
	generateObjectInitialisationsBasedOnSubstanceConcepts(parentEntity, currentCodeBlockInTree, sentenceIndex, true);
	#endif

	#ifdef NLC_DEBUG
	cout << "\tgenerateObjectInitialisationsBasedOnPropertiesAndConditions:" << parentEntity->entityName << endl;
	cout << "sentenceIndex = " << sentenceIndex << endl;
	#endif

	NLCcodeblock * lastCodeBlockInTree = *currentCodeBlockInTree;
	performedAtLeastParentObjectInitialisation = generateObjectInitialisationsBasedOnPropertiesAndConditions(parentEntity, currentCodeBlockInTree, sentenceIndex, "", "", false, true);
	
	#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_BLOCKS_FOR_PARENT_INITIALISATION_SPECIAL
	*currentCodeBlockInTree = lastCodeBlockInTree;
	if(performedAtLeastParentObjectInitialisation)
	{
		while((*currentCodeBlockInTree)->next != NULL)
		{
			*currentCodeBlockInTree = (*currentCodeBlockInTree)->next;
		}
	}
	else
	{
		clearCodeBlock(*currentCodeBlockInTree);
	}
	#endif
			
	return performedAtLeastParentObjectInitialisation;
}






GIAentityNode * getParent(GIAentityNode * currentEntity, int sentenceIndex, bool parseConditionParents)
{
	GIAentityNode * parentEntityNew = currentEntity;
	
	bool foundParentProperty = false;
	for(vector<GIAentityConnection*>::iterator propertyNodeListIterator = currentEntity->propertyNodeReverseList->begin(); propertyNodeListIterator < currentEntity->propertyNodeReverseList->end(); propertyNodeListIterator++)
	{
		GIAentityConnection * parentConnection = *propertyNodeListIterator;
		GIAentityNode * parentEntity = parentConnection->entity;
		
		#ifdef NLC_DEFINE_LOCAL_VARIABLES_FOR_ALL_INDEFINATE_ENTITIES
		if(checkSentenceIndexParsingCodeBlocks(parentEntity, parentConnection, sentenceIndex, false))	//NB will parse references to entities in previous sentence
		#else
		if(checkSentenceIndexParsingCodeBlocks(parentEntity, parentConnection, sentenceIndex, false) || parentEntity->NLCparsedForCodeBlocks)
		#endif
		{
			parentEntityNew = getParent(parentEntity, sentenceIndex, parseConditionParents);
		}
		foundParentProperty = true;

	}
	if(!foundParentProperty && parseConditionParents)
	{//added 1e9a
		for(vector<GIAentityConnection*>::iterator conditionNodeListIterator = currentEntity->incomingConditionNodeList->begin(); conditionNodeListIterator < currentEntity->incomingConditionNodeList->end(); conditionNodeListIterator++)
		{
			GIAentityConnection * conditionConnection = *conditionNodeListIterator;
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
					parentEntityNew = getParent(conditionSubject, sentenceIndex, parseConditionParents);
				}
			}
		}
	}

	return parentEntityNew;
}

bool getParentAndGenerateContextBlocks(NLCcodeblock ** currentCodeBlockInTree, GIAentityNode * currentEntity, int sentenceIndex, NLClogicalConditionConjunctionVariables * logicalConditionConjunctionVariables, bool parseConditionParents)
{
	GIAentityNode * parentEntity = getParent(currentEntity, sentenceIndex, parseConditionParents);

	bool generatedContextBlocks = generateContextBlocks(currentCodeBlockInTree, parentEntity, sentenceIndex, logicalConditionConjunctionVariables, false, NLC_ITEM_TYPE_CATEGORYVAR_APPENDITION);

	return generatedContextBlocks;

}






//added recursion 1e8a
//onlyGenerateContextBlocksIfContextNotGeneratedForNLC removed 1i3b

bool generateObjectInitialisationsBasedOnPropertiesAndConditions(GIAentityNode * entity, NLCcodeblock ** currentCodeBlockInTree, int sentenceIndex, string parentName, string parentConditionName, bool generateParentContext, bool newlyDeclaredEntityInCategoryList)
{
	#ifdef NLC_DEBUG_PARSE_CONTEXT3
	string generateParentContextStringTemp = "false";
	if(generateParentContext)
	{
		generateParentContextStringTemp = "true";
	}
	*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("generateObjectInitialisationsBasedOnPropertiesAndConditions(): ") + entity->entityName + ", generateParentContext = " + generateParentContextStringTemp);
	#endif

	#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
	//added 1i8a->1i8c, moved 1i11d
	if(generateParentContext)
	{	
		NLClogicalConditionConjunctionVariables logicalConditionConjunctionVariables;
		logicalConditionConjunctionVariables.onlyGenerateContextBlocksIfConnectionsParsedForNLC = true;
		generateContextBlocks(currentCodeBlockInTree, entity, sentenceIndex, &logicalConditionConjunctionVariables, false, NLC_ITEM_TYPE_CATEGORYVAR_APPENDITION);
	}
	#endif
	#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_BLOCKS_FOR_PARENT_INITIALISATION_SPECIAL
	if(newlyDeclaredEntityInCategoryList)
	{
		*currentCodeBlockInTree = createCodeBlockForPropertyListCategory(*currentCodeBlockInTree, entity, NLC_ITEM_TYPE_CATEGORYVAR_APPENDITION);
		entity->NLCcontextGenerated = true;
	}
	#endif
	
	bool performedAtLeastOneObjectInitialisation = false;
	if(!(entity->isSubstanceConcept) && !(entity->isActionConcept) || (parentName != ""))		//|| (parentName != "") added 1i11k
	{
		//property initialisations
		for(vector<GIAentityConnection*>::iterator propertyNodeListIterator = entity->propertyNodeList->begin(); propertyNodeListIterator < entity->propertyNodeList->end(); propertyNodeListIterator++)
		{
			GIAentityConnection * propertyConnection = (*propertyNodeListIterator);
			GIAentityNode* propertyEntity = propertyConnection->entity;
			#ifdef NLC_DEBUG
			//cout << "\t\tpropertyConnection->sentenceIndexTemp = " << propertyConnection->sentenceIndexTemp << endl;
			#endif
					
			#ifdef NLC_VERIFY_CONNECTIONS_SENTENCE_INDEX
			if((checkSentenceIndexParsingCodeBlocks(propertyEntity, sentenceIndex, false) || propertyEntity->NLCparsedForCodeBlocks) && (propertyConnection->sentenceIndexTemp == sentenceIndex))
			#else
			if((checkSentenceIndexParsingCodeBlocks(propertyEntity, sentenceIndex, false) || propertyEntity->NLCparsedForCodeBlocks))			
			#endif
			{//only write properties that are explicated in current sentence

				bool performedAtLeastOneObjectInitialisationAtThisLevel = false;
				NLCcodeblock * firstCodeBlockInSection = *currentCodeBlockInTree;

				#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_FOR_EACH_CHILD
				NLClogicalConditionConjunctionVariables logicalConditionConjunctionVariables;
				logicalConditionConjunctionVariables.onlyGenerateContextBlocksIfConnectionsParsedForNLC = true;
				//research context in case, eg "The chicken has the ball which is near the park." (ie when initialisation property is definite; as distinguished from "The chicken has a ball near the park.")	
				bool generatedContext = false;
				#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_FOR_EACH_CHILD_GET_PARENT
				GIAentityNode * parentEntity = getSameReferenceSetDefiniteUniqueParent(propertyEntity, sentenceIndex, entity);
				#ifdef NLC_DEBUG_PARSE_CONTEXT4
				*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("generateObjectInitialisationsBasedOnPropertiesAndConditions() getSameReferenceSetDefiniteUniqueParent result; propertyEntity: ") + propertyEntity->entityName + string(", parentEntity: ") + parentEntity->entityName);
				#endif	
				//cout << "1a: propertyEntity = " << propertyEntity->entityName << endl;
				if(parentEntity != propertyEntity)
				{
					//cout << "1b: propertyEntity = " << propertyEntity->entityName << endl;
					#ifdef NLC_DEBUG_PARSE_CONTEXT4
					*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("generateObjectInitialisationsBasedOnPropertiesAndConditions(): (parentEntity != propertyEntity) propertyEntity: ") + propertyEntity->entityName + string(", parentEntity: ") + parentEntity->entityName);
					#endif

					if(generateContextBlocks(currentCodeBlockInTree, parentEntity, sentenceIndex, &logicalConditionConjunctionVariables, false, NLC_ITEM_TYPE_CATEGORYVAR_APPENDITION))		//changed from generateCategories 1i11o
					{
						//cout << "\n1c: propertyEntity = " << propertyEntity->entityName << endl;
						//cout << "1c: parentEntity = " << parentEntity->entityName << endl;
						generatedContext = true;
						#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN
						NLCitem * propertyEntityClass = new NLCitem(propertyEntity, NLC_ITEM_TYPE_OBJECT);
						propertyEntityClass->context.push_back(generateInstanceName(parentEntity));
						*currentCodeBlockInTree = createCodeBlockForPropertyList(*currentCodeBlockInTree, propertyEntityClass);	
						#endif		
						#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_FOR_EACH_CHILD_GET_PARENT_ORIGINAL_IMPLEMENTATION		
						*currentCodeBlockInTree = createCodeBlockAddPropertyToLocalList(*currentCodeBlockInTree, propertyEntity, propertyEntity);	//removed 1j10a
						#endif
						propertyEntity->NLClocalListVariableHasBeenInitialised = true;
					}
				}
				#endif

				if(assumedToAlreadyHaveBeenDeclared(propertyEntity))
				{
					#ifdef NLC_DEBUG_PARSE_CONTEXT4
					*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("generateObjectInitialisationsBasedOnPropertiesAndConditions(): assumedToAlreadyHaveBeenDeclared(propertyEntity): ") + propertyEntity->entityName);
					#endif

					#ifndef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN
					if(!generatedContext)
					{
					#endif
						if(generateContextBlocks(currentCodeBlockInTree, propertyEntity, sentenceIndex, &logicalConditionConjunctionVariables, generatedContext, NLC_ITEM_TYPE_CATEGORYVAR_APPENDITION))	//pass generatedContext 1j10a
						{
							generatedContext = true;
						}
						#ifndef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES
						else
						{
							//generatedContext = true;
						}
						#endif
					#ifndef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN
					}
					#endif						
				}
				
				if(!generatedContext)
				{
				#endif
					//is this code still required?
					#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
					//if(!onlyGenerateContextBlocksIfContextNotGeneratedForNLC || !(entity->NLCcontextGenerated))
					if(!(entity->NLCcontextGenerated))
					{//context block already created by generateContextBlocks()	//added 1g14b 15-July-2014
					#endif
						//cout << "entity->entityName = " << entity->entityName << endl;
						//for(all items in context){
						NLCitem * entityClass = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
						if(assumedToAlreadyHaveBeenDeclared(entity))
						{
							#ifdef NLC_DEBUG_PARSE_CONTEXT2
							*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("generateObjectInitialisationsBasedOnPropertiesAndConditions(): 1createCodeBlockForPropertyListLocal: ") + entity->entityName);
							#endif

							*currentCodeBlockInTree = createCodeBlockForPropertyListLocal(*currentCodeBlockInTree, entityClass);
						}
						else
						{
							#ifdef NLC_DEBUG_PARSE_CONTEXT2
							*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("generateObjectInitialisationsBasedOnPropertiesAndConditions(): 2createCodeBlockForPropertyList: ") + entity->entityName);
							#endif

							entityClass->context.push_back(parentName);
							*currentCodeBlockInTree = createCodeBlockForPropertyList(*currentCodeBlockInTree, entityClass);
						}
					#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
					}
					#endif
				#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_FOR_EACH_CHILD
				}
				#endif

				#ifdef NLC_DEBUG
				cout << "\t\tcreateCodeBlockForPropertyList: " << entity->entityName << endl;
				#endif

				bool newlyDeclaredEntityInCategoryList2 = false;

				if(!(propertyConnection->NLCparsedForCodeBlocks))
				{
					#ifdef NLC_TRANSLATE_NEGATIVE_PROPERTIES_AND_CONDITIONS
					if(propertyConnection->negative || (propertyEntity->isSubstanceQuality && propertyEntity->negative))
					{
						#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS
						if(assumedToAlreadyHaveBeenDeclared(propertyEntity))
						{
							//cout << "propertyEntity->entityName = " << propertyEntity->entityName << endl;
							#ifdef NLC_DEBUG_PARSE_CONTEXT2
							*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("generateObjectInitialisationsBasedOnPropertiesAndConditions(): 3createCodeBlockRemoveProperties: ") + entity->entityName + string(" ") + propertyEntity->entityName);
							#endif

							//NLCcodeblock * firstCodeBlockInSection2 = *currentCodeBlockInTree;

							NLCitem * propertyClass = new NLCitem(propertyEntity, NLC_ITEM_TYPE_OBJECT);
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
							#ifdef NLC_DEBUG_PARSE_CONTEXT2
							*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("generateObjectInitialisationsBasedOnPropertiesAndConditions():  4createCodeBlockRemoveProperties: ") + entity->entityName + string(" ") + propertyEntity->entityName);
							#endif

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
							#ifdef NLC_DEBUG_PARSE_CONTEXT2
							*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("generateObjectInitialisationsBasedOnPropertiesAndConditions(): 3createCodeBlockAddProperty: ") + entity->entityName + string(" ") + convertIntToString(entity->NLClocalListVariableHasBeenInitialised) + string(" ") + propertyEntity->entityName + string(" ") + convertIntToString(propertyEntity->NLClocalListVariableHasBeenInitialised));
							#endif

							//use function argument PropertyList (do not create a new property); eg "the ball" in "Tom has the ball"
							//cout << "propertyEntity->entityName = " << propertyEntity->entityName << endl;
							//for(all items in context){

							NLCcodeblock * firstCodeBlockInSection2 = *currentCodeBlockInTree;

							/*
							#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
							if(!onlyGenerateContextBlocksIfContextNotGeneratedForNLC)
							{//context block already created by generateContextBlocks()	//added 1g14b/15-July-2014
							#endif
							*/
							#ifndef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_FOR_EACH_CHILD
							NLCitem * propertyClass = new NLCitem(propertyEntity, NLC_ITEM_TYPE_OBJECT);
							*currentCodeBlockInTree = createCodeBlockForPropertyListLocal(*currentCodeBlockInTree, propertyClass);
							#endif
							/*
							#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
							}
							#endif
							*/

							*currentCodeBlockInTree = createCodeBlockAddProperty(*currentCodeBlockInTree, entity, propertyEntity, sentenceIndex);
							#ifdef NLC_DEBUG
							cout << "createCodeBlockAddProperty: " << entity->entityName << ", " << propertyEntity->entityName << endl;
							#endif
							*currentCodeBlockInTree = firstCodeBlockInSection2->next;
						}
						else
						{
						#endif
							#ifdef NLC_DEBUG_PARSE_CONTEXT2
							*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("generateObjectInitialisationsBasedOnPropertiesAndConditions(): 4createCodeBlockAddNewProperty: ") + entity->entityName + string(" ") + propertyEntity->entityName);
							#endif

							//create a new property; eg "a ball" in "Tom has a ball"

							newlyDeclaredEntityInCategoryList2 = true;
							*currentCodeBlockInTree = createCodeBlockCreateNewProperty(*currentCodeBlockInTree, entity, propertyEntity, sentenceIndex, true);
							
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
						propertyEntity->NLCparsedForCodeBlocks = true;		//added NLC 1b2b/3 October 2013  - used for quick access of instances already declared in current context

						//moved 1e1b: only generate object initialisations for items based on subject concepts when items are created in context
						#ifdef GIA_TRANSLATOR_DREAM_MODE_LINK_SPECIFIC_CONCEPTS_AND_ACTIONS
						//Part 2b: generate object initialisations based on substance concepts (class inheritance)
						generateObjectInitialisationsBasedOnSubstanceConcepts(propertyEntity, currentCodeBlockInTree, sentenceIndex, newlyDeclaredEntityInCategoryList2);
						#endif
					#ifdef NLC_TRANSLATE_NEGATIVE_PROPERTIES_AND_CONDITIONS
					}
					#endif

					performedAtLeastOneObjectInitialisationAtThisLevel = true;
				}
				else
				{//added 1i11l
					#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN
					if(!generatedContext)
					{
						NLCitem * propertyEntityClass = new NLCitem(propertyEntity, NLC_ITEM_TYPE_OBJECT);
						propertyEntityClass->context.push_back(generateInstanceName(entity));
						*currentCodeBlockInTree = createCodeBlockForPropertyList(*currentCodeBlockInTree, propertyEntityClass);
						
						//generateContextBlocks(currentCodeBlockInTree, propertyEntity, sentenceIndex, &logicalConditionConjunctionVariables);
						//parse the children (properties and conditions) of an undeclared definite parent
						createCodeBlockForStatements(currentCodeBlockInTree, generateInstanceName(propertyEntity), propertyEntity, sentenceIndex, &logicalConditionConjunctionVariables);		//added 1i11n
					}
					#endif			
				}

				NLCcodeblock * firstCodeBlockBeforeRecursion = *currentCodeBlockInTree;
				bool performedAtLeastOneObjectInitialisationAtALowerLevel = generateObjectInitialisationsBasedOnPropertiesAndConditions(propertyEntity, currentCodeBlockInTree, sentenceIndex, generateInstanceName(entity), "", false, newlyDeclaredEntityInCategoryList2);
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
						//cout << "foundConditionObject = " << conditionObject->entityName << endl;
						//cout << "checkSentenceIndexParsingCodeBlocks(conditionEntity, sentenceIndex, false) = " << checkSentenceIndexParsingCodeBlocks(conditionEntity, sentenceIndex, false) << endl;
						//cout << "conditionEntity->NLCparsedForCodeBlocks = " << conditionEntity->NLCparsedForCodeBlocks << endl;
						//cout << "conditionConnection->sentenceIndexTemp = " << conditionConnection->sentenceIndexTemp << endl;

						#ifdef NLC_VERIFY_CONNECTIONS_SENTENCE_INDEX
						if((checkSentenceIndexParsingCodeBlocks(conditionEntity, sentenceIndex, false) || conditionEntity->NLCparsedForCodeBlocks) && (conditionConnection->sentenceIndexTemp == sentenceIndex))
						#else
						if((checkSentenceIndexParsingCodeBlocks(conditionEntity, sentenceIndex, false) || conditionEntity->NLCparsedForCodeBlocks))
						#endif
						{//only write conditions that are explicated in current sentence

							bool performedAtLeastOneObjectInitialisationAtThisLevel = false;
							NLCcodeblock * firstCodeBlockInSection = *currentCodeBlockInTree;
							

							//cout << "entity->entityName = " << entity->entityName << endl;
							//for(all items in context){
							NLCitem * entityClass = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
							NLCitem * conditionObjectClass = new NLCitem(conditionObject, NLC_ITEM_TYPE_OBJECT);

							#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_FOR_EACH_CHILD
							NLClogicalConditionConjunctionVariables logicalConditionConjunctionVariables;
							logicalConditionConjunctionVariables.onlyGenerateContextBlocksIfConnectionsParsedForNLC = true;
							//research context in case, eg "The chicken has the ball which is near the park." (ie when initialisation property is definite; as distinguished from "The chicken has a ball near the park.")	
							bool generatedContext = false;
							#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_FOR_EACH_CHILD_GET_PARENT
							GIAentityNode * parentEntity = getSameReferenceSetDefiniteUniqueParent(conditionObject, sentenceIndex, entity);
							if(parentEntity != conditionObject)
							{
								#ifdef NLC_DEBUG_PARSE_CONTEXT4
								*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("generateObjectInitialisationsBasedOnPropertiesAndConditions(): (parentEntity != conditionObject) conditionObject: ") + conditionObject->entityName + string(", parentEntity: ") + parentEntity->entityName);
								#endif

								if(generateContextBlocks(currentCodeBlockInTree, parentEntity, sentenceIndex, &logicalConditionConjunctionVariables, false, NLC_ITEM_TYPE_CATEGORYVAR_APPENDITION))			//changed from generateCategories 1i11o
								{
									generatedContext = true;
									#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN
									NLCitem * conditionObjectEntityClass = new NLCitem(conditionObject, NLC_ITEM_TYPE_OBJECT);
									conditionObjectEntityClass->context.push_back(generateInstanceName(parentEntity));
									*currentCodeBlockInTree = createCodeBlockForPropertyList(*currentCodeBlockInTree, conditionObjectEntityClass);	
									#endif	
									#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_FOR_EACH_CHILD_GET_PARENT_ORIGINAL_IMPLEMENTATION								
									*currentCodeBlockInTree = createCodeBlockAddPropertyToLocalList(*currentCodeBlockInTree, conditionObject, conditionObject);	//removed 1j10a
									#endif
									conditionObject->NLClocalListVariableHasBeenInitialised = true;
								}
							}								
							#endif

							if(assumedToAlreadyHaveBeenDeclared(conditionObject))
							{
								#ifndef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN
								if(!generatedContext)
								{
								#endif
									#ifdef NLC_DEBUG_PARSE_CONTEXT4
									*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("generateObjectInitialisationsBasedOnPropertiesAndConditions(): assumedToAlreadyHaveBeenDeclared(propertyEntity): ") + conditionObject->entityName);
									#endif

									if(generateContextBlocks(currentCodeBlockInTree, conditionObject, sentenceIndex, &logicalConditionConjunctionVariables, generatedContext, NLC_ITEM_TYPE_CATEGORYVAR_APPENDITION))	//pass generatedContext 1j10a		
									{
										generatedContext = true;
									}
									#ifndef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES
									else
									{
										//generatedContext = true;
									}
									#endif
								#ifndef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN
								}
								#endif	
							}
							
							if(!generatedContext)
							{
							#endif
								//is this code still required?
								#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
								//if(!onlyGenerateContextBlocksIfContextNotGeneratedForNLC || !(entity->NLCcontextGenerated))
								if(!(entity->NLCcontextGenerated))
								{//context block already created by generateContextBlocks()	//added 1g14b/15-July-2014
								#endif
									if(assumedToAlreadyHaveBeenDeclared(entity))
									{
										#ifdef NLC_DEBUG_PARSE_CONTEXT2
										*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("generateObjectInitialisationsBasedOnPropertiesAndConditions(): 1BcreateCodeBlockForPropertyListLocal: ") + entity->entityName);
										#endif

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
										#ifdef NLC_DEBUG_PARSE_CONTEXT2
										*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("generateObjectInitialisationsBasedOnPropertiesAndConditions(): 2BcreateCodeBlockForPropertyList: ") + entity->entityName);
										#endif

										/*
										cout << "\t!assumedToAlreadyHaveBeenDeclared" << endl;
										cout << "parentName = " << parentName << endl;
										cout << "entity = " << entity->entityName << endl;
										cout << "conditionEntity = " << conditionEntity->entityName << endl;
										cout << "conditionObject = " << conditionObject->entityName << endl;
										*/

										NLCitem * parentConditionItem = new NLCitem(parentConditionName, NLC_ITEM_TYPE_OBJECT);
										parentConditionItem->context.push_back(parentName);
										*currentCodeBlockInTree = createCodeBlockForConditionList(*currentCodeBlockInTree, parentConditionItem, entityClass);
									}	
								#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
								}
								#endif
							#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_FOR_EACH_CHILD
							}
							#endif

							bool newlyDeclaredEntityInCategoryList2 = false;
							
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

										#ifdef NLC_DEBUG_PARSE_CONTEXT2
										*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("generateObjectInitialisationsBasedOnPropertiesAndConditions(): 3BcreateCodeBlockRemoveConditions: ") + entity->entityName + string(" ") + conditionEntity->entityName);
										#endif

										*currentCodeBlockInTree = createCodeBlockRemovePropertiesFromLocalList(*currentCodeBlockInTree, conditionObject);

										*currentCodeBlockInTree = createCodeBlockRemoveConditions(*currentCodeBlockInTree, entity, conditionEntity);

										//*currentCodeBlockInTree = firstCodeBlockInSection2->next;
									}
									else
									{
									#endif
										#ifdef NLC_DEBUG_PARSE_CONTEXT2
										*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("generateObjectInitialisationsBasedOnPropertiesAndConditions():  4BcreateCodeBlockRemoveProperties: ") + entity->entityName + string(" ") + conditionEntity->entityName);
										#endif

										*currentCodeBlockInTree = createCodeBlockRemoveConditions(*currentCodeBlockInTree, entity, conditionEntity);

									#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS
									}
									#endif

									conditionConnection->NLCparsedForCodeBlocks = true;
									conditionEntity->NLCparsedForCodeBlocks = true;	//added NLC 1b2b/3 October 2013 - used for quick access of instances already declared in current context
									conditionObject->NLCparsedForCodeBlocks = true;	//added 1e6d

								}
								else
								{
								#endif
									#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS
									if(assumedToAlreadyHaveBeenDeclared(conditionObject))
									{
										#ifdef NLC_DEBUG_PARSE_CONTEXT2
										*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("generateObjectInitialisationsBasedOnPropertiesAndConditions(): 3BcreateCodeBlockCondition: ") + entity->entityName + string(" ") + convertIntToString(entity->NLClocalListVariableHasBeenInitialised) + string(" ") + conditionObject->entityName + string(" ") + convertIntToString(conditionObject->NLClocalListVariableHasBeenInitialised));
										#endif

										NLCcodeblock * firstCodeBlockInSection2 = *currentCodeBlockInTree;

										//use function argument PropertyList (do not create a new property to insert into condition); eg "the house" in "Tom is near a house"
										//cout << "conditionObject->entityName = " << conditionObject->entityName << endl;
										//for(all items in context){

										/*
										#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
										if(!onlyGenerateContextBlocksIfContextNotGeneratedForNLC)
										{//context block already created by generateContextBlocks()	//added 1g14b/15-July-2014
										#endif
										*/
										#ifndef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_FOR_EACH_CHILD
										*currentCodeBlockInTree = createCodeBlockForPropertyListLocal(*currentCodeBlockInTree, conditionObjectClass);
										#endif
										/*
										#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
										}
										#endif
										*/

										*currentCodeBlockInTree = createCodeBlockAddCondition(*currentCodeBlockInTree, entity, conditionEntity, sentenceIndex);

										*currentCodeBlockInTree = firstCodeBlockInSection2->next;
									}
									else
									{
									#endif
										#ifdef NLC_DEBUG_PARSE_CONTEXT2
										*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("generateObjectInitialisationsBasedOnPropertiesAndConditions(): 4BcreateCodeBlockAddNewCondition: ") + entity->entityName + string(" ") + conditionObject->entityName);
										#endif

										//create a new condition; eg "a house" in "Tom is near a house"
										newlyDeclaredEntityInCategoryList2 = true;
										*currentCodeBlockInTree = createCodeBlockCreateNewCondition(*currentCodeBlockInTree, entity, conditionEntity, sentenceIndex, true);

									#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS
									}
									#endif

									conditionConnection->NLCparsedForCodeBlocks = true;
									conditionEntity->NLCparsedForCodeBlocks = true;	//added NLC 1b2b/3 October 2013 - used for quick access of instances already declared in current context
									conditionObject->NLCparsedForCodeBlocks = true;	//added 1e6d

									//moved 1e1b: only generate object initialisations for items based on subject concepts when items are created in context
									#ifdef GIA_TRANSLATOR_DREAM_MODE_LINK_SPECIFIC_CONCEPTS_AND_ACTIONS
									//Part 2b: generate object initialisations based on substance concepts (class inheritance)
									generateObjectInitialisationsBasedOnSubstanceConcepts(conditionEntity, currentCodeBlockInTree, sentenceIndex, newlyDeclaredEntityInCategoryList2);
									#endif
								#ifdef NLC_TRANSLATE_NEGATIVE_PROPERTIES_AND_CONDITIONS
								}
								#endif

								performedAtLeastOneObjectInitialisationAtThisLevel = true;
							}
							else
							{//added 1i11l
								#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN
								if(!generatedContext)
								{
									NLCitem * conditionObjectEntityClass = new NLCitem(conditionObject, NLC_ITEM_TYPE_OBJECT);
									conditionObjectEntityClass->context.push_back(generateInstanceName(entity));
									*currentCodeBlockInTree = createCodeBlockForPropertyList(*currentCodeBlockInTree, conditionObjectEntityClass);	
									
									//generateContextBlocks(currentCodeBlockInTree, propertyEntity, sentenceIndex, &logicalConditionConjunctionVariables);
									//parse the children (properties and conditions) of an undeclared definite parent
									createCodeBlockForStatements(currentCodeBlockInTree, generateInstanceName(conditionObject), conditionObject, sentenceIndex, &logicalConditionConjunctionVariables);	//added 1i11n
								}			
								#endif
							}

							NLCcodeblock * firstCodeBlockBeforeRecursion = *currentCodeBlockInTree;
							bool performedAtLeastOneObjectInitialisationAtALowerLevel = generateObjectInitialisationsBasedOnPropertiesAndConditions(conditionObject, currentCodeBlockInTree, sentenceIndex, generateInstanceName(entity), conditionEntity->entityName, false, newlyDeclaredEntityInCategoryList2);

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

#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_FOR_EACH_CHILD_GET_PARENT
GIAentityNode * getSameReferenceSetDefiniteUniqueParent(GIAentityNode * currentEntity, int sentenceIndex, GIAentityNode * generateObjectInitialisationsLastParent)
{
	GIAentityNode * parentEntityNew = currentEntity;
	
	for(vector<GIAentityConnection*>::iterator propertyNodeListIterator = currentEntity->propertyNodeReverseList->begin(); propertyNodeListIterator < currentEntity->propertyNodeReverseList->end(); propertyNodeListIterator++)
	{
		GIAentityConnection * parentConnection = *propertyNodeListIterator;
		GIAentityNode * parentEntity = parentConnection->entity;
		
		#ifdef NLC_DEFINE_LOCAL_VARIABLES_FOR_ALL_INDEFINATE_ENTITIES
		if(checkSentenceIndexParsingCodeBlocks(parentEntity, parentConnection, sentenceIndex, false))	//NB will parse references to entities in previous sentence
		#else
		if(checkSentenceIndexParsingCodeBlocks(parentEntity, parentConnection, sentenceIndex, false) || parentEntity->NLCparsedForCodeBlocks)
		#endif
		{
			if(parentConnection->sameReferenceSet)
			{
				//removed 1i11e, readded 1i11j
				if(parentEntity != generateObjectInitialisationsLastParent)
				{
					/*
					//added 1i11f, removed 1i11j
					if(!(parentEntity->NLCcontextGenerated))
					{
					*/
						if((parentEntity->grammaticalDefiniteTemp) || (parentEntity->grammaticalProperNounTemp))
						{
							parentEntityNew = getSameReferenceSetDefiniteUniqueParent(parentEntity, sentenceIndex, generateObjectInitialisationsLastParent);
						}
					/*	
					}
					*/
				}
			}
		}
	}
	return parentEntityNew;
}
#endif


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
void generateObjectInitialisationsBasedOnSubstanceConcepts(GIAentityNode * entity, NLCcodeblock ** currentCodeBlockInTree, int sentenceIndex, bool newlyDeclaredEntityInCategoryList)
{
	//added 6 December 2013: take into account plain concepts; eg "Dogs are fat. The dog rides the bike." <- the dog will be given the property 'fat'
	GIAentityNode * conceptEntity = getPrimaryConceptNodeDefiningInstance(entity);
	generateObjectInitialisationsBasedOnSubstanceConceptsRecurse(entity, conceptEntity, currentCodeBlockInTree, sentenceIndex, "", "", newlyDeclaredEntityInCategoryList);

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

			generateObjectInitialisationsBasedOnSubstanceConceptsRecurse(entity, definitionEntity, currentCodeBlockInTree, sentenceIndex, "", "", newlyDeclaredEntityInCategoryList);
		}
		//}
	}
}

void generateObjectInitialisationsBasedOnSubstanceConceptsRecurse(GIAentityNode * entity, GIAentityNode * definitionEntity, NLCcodeblock ** currentCodeBlockInTree, int sentenceIndex, string parentName, string parentConditionName, bool newlyDeclaredEntityInCategoryList)
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
				NLCitem * entityClass = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
				#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_BLOCKS_FOR_PARENT_INITIALISATION_SPECIAL
				if(newlyDeclaredEntityInCategoryList)
				{
					*currentCodeBlockInTree = createCodeBlockForPropertyListCategory(*currentCodeBlockInTree, entity, NLC_ITEM_TYPE_CATEGORYVAR_APPENDITION);
				}
				else
				{
				#endif
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
				#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_BLOCKS_FOR_PARENT_INITIALISATION_SPECIAL
				}
				#endif

				*currentCodeBlockInTree = createCodeBlockCreateNewProperty(*currentCodeBlockInTree, entity, propertyEntity, sentenceIndex, false);

				entity->NLCparsedForCodeBlocks = true;			//added NLC 1b6b/4 October 2013 - used for quick access of instances already declared in current context
				generateObjectInitialisationsBasedOnSubstanceConceptsRecurse(entity, propertyEntity, currentCodeBlockInTree, sentenceIndex, generateInstanceName(definitionEntity), "", true);		//updated 9 November 2013 - support recursion of complex substance concept definition

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
					NLCitem * entityClass = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);

					#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_BLOCKS_FOR_PARENT_INITIALISATION_SPECIAL
					if(newlyDeclaredEntityInCategoryList)
					{
						*currentCodeBlockInTree = createCodeBlockForPropertyListCategory(*currentCodeBlockInTree, entity, NLC_ITEM_TYPE_CATEGORYVAR_APPENDITION);
					}
					else
					{
					#endif
						if(assumedToAlreadyHaveBeenDeclared(entity))
						{
							*currentCodeBlockInTree = createCodeBlockForPropertyListLocal(*currentCodeBlockInTree, entityClass);
						}
						else
						{
							NLCitem * parentConditionItem = new NLCitem(parentConditionName, NLC_ITEM_TYPE_OBJECT);
							parentConditionItem->context.push_back(parentName);
							*currentCodeBlockInTree = createCodeBlockForConditionList(*currentCodeBlockInTree, parentConditionItem, entityClass);
						}
					#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_BLOCKS_FOR_PARENT_INITIALISATION_SPECIAL
					}
					#endif
				
					*currentCodeBlockInTree = createCodeBlockCreateNewCondition(*currentCodeBlockInTree, entity, conditionEntity, sentenceIndex, false);

					entity->NLCparsedForCodeBlocks = true;			//added NLC 1b6b/4 October 2013 - used for quick access of instances already declared in current context
					generateObjectInitialisationsBasedOnSubstanceConceptsRecurse(entity, conditionObject, currentCodeBlockInTree, sentenceIndex, generateInstanceName(definitionEntity), conditionEntity->entityName, true);	//updated 9 November 2013 - support recursion of complex substance concept definition

					*currentCodeBlockInTree = firstCodeBlockInSection->next;
				}

			}
		}
	#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_BASED_ON_CONCEPTS
	}
	#endif
}
#endif



