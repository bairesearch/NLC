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
 * File Name: NLCtranslatorCodeBlocksLogicalConditions.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2015 Baxter AI (baxterai.com)
 * Project: Natural Language Programming Interface (compiler)
 * Project Version: 1n9b 25-January-2015
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/



#include <ctime>
#include <cstdlib>	//for random number generation
#include <cmath>

#include "NLCtranslatorCodeBlocksLogicalConditions.h"
#include "NLCtranslatorCodeBlocksLogicalConditionsAdvanced.h"
#include "NLCtranslatorCodeBlocksOperations.h"
#include "GIAtranslatorOperations.h"	//required for getPrimaryConceptNodeDefiningInstance()
#include "NLCprintDefs.h"	//required for NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION

		
#ifdef NLC_PREPROCESSOR_MATH
bool generateCodeBlocksFromMathText(NLCcodeblock ** currentCodeBlockInTree, vector<GIAentityNode*> * entityNodesActiveListComplete, int sentenceIndex, NLCsentence * firstNLCsentenceInFullSentence, string NLCfunctionName)
{
	#ifdef NLC_DEBUG_PREPROCESSOR_MATH
	cout << "\n generateCodeBlocksFromMathText(): sentenceIndex = " << sentenceIndex << endl;
	#endif
	bool result = true;

	NLCcodeblock * currentCodeBlockInTreeAtBaseLevel = *currentCodeBlockInTree;
	string whileLogicalConditionConjunctionBooleanName = generateWhileLogicalConditionConjunctionBooleanName(firstNLCsentenceInFullSentence->indentation);
	
	#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
	if(firstNLCsentenceInFullSentence->hasLogicalConditionOperator)
	{
		if(firstNLCsentenceInFullSentence->logicalConditionOperator == NLC_LOGICAL_CONDITION_OPERATIONS_WHILE)
		{
			*currentCodeBlockInTree = createCodeBlockDeclareNewBoolVar(*currentCodeBlockInTree, whileLogicalConditionConjunctionBooleanName, true);
			currentCodeBlockInTreeAtBaseLevel = *currentCodeBlockInTree;
			*currentCodeBlockInTree = createCodeBlockWhileHasBool(*currentCodeBlockInTree, whileLogicalConditionConjunctionBooleanName);
			*currentCodeBlockInTree = createCodeBlockSetBoolVar(*currentCodeBlockInTree, whileLogicalConditionConjunctionBooleanName, false);
		}
						
		//CHECKTHIS; is NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE required for non-logical condition mathText?
		if((firstNLCsentenceInFullSentence->logicalConditionOperator == NLC_LOGICAL_CONDITION_OPERATIONS_IF) || (firstNLCsentenceInFullSentence->logicalConditionOperator == NLC_LOGICAL_CONDITION_OPERATIONS_WHILE) || (firstNLCsentenceInFullSentence->logicalConditionOperator == NLC_LOGICAL_CONDITION_OPERATIONS_FOR))
		{
			#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
			cout << "firstNLCsentenceInFullSentence->logicalConditionOperator == NLC_LOGICAL_CONDITION_OPERATIONS_IF" << endl;
			#endif
			int caseIndex = 0;
			int currentLevel = firstNLCsentenceInFullSentence->indentation;
			int currentLogicalConditionOperator = firstNLCsentenceInFullSentence->logicalConditionOperator;
			bool stillFindingLogicalConditionAtCurrentLevel = true;
			NLCsentence * currentSentence = firstNLCsentenceInFullSentence;
			while(stillFindingLogicalConditionAtCurrentLevel)
			{//this loop is only required by NLC_LOGICAL_CONDITION_OPERATIONS_IF (it is not used by NLC_LOGICAL_CONDITION_OPERATIONS_WHILE and NLC_LOGICAL_CONDITION_OPERATIONS_FOR)
				
				#ifdef NLC_DISABLE_1i_CODE_FOR_DEBUG
				declareLocalPropertyListsForIndefiniteEntities(currentCodeBlockInTree, entityNodesActiveListComplete, sentenceIndex, NLCfunctionName, currentSentence);	//indefinite logical condition objects (eg "a house" in "if a house is green, do this") must have been previously declared else output code will not compile [as these statements implicitly assume the existence of "a house"; which may or may not be "green"]
				#endif
				
				#ifdef NLC_PREPROCESSOR_MATH_USE_LOGICAL_CONDITION_OPERATIONS_ADVANCED_BACKWARDS_COMPATIBLE_VARIABLE_NAMES
				if(firstNLCsentenceInFullSentence->logicalConditionOperator != NLC_LOGICAL_CONDITION_OPERATIONS_FOR)
				{
					//use the same logical condition check naming scheme as NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED;
					string logicalConditionConjunctionBooleanName = generateLogicalConditionConjunctionBooleanName(currentSentence->indentation, caseIndex, NLC_LOGICAL_CONDITION_OPERATIONS_IF);							
					*currentCodeBlockInTree = createCodeBlockDeclareNewBoolArray(*currentCodeBlockInTree, logicalConditionConjunctionBooleanName, false);
				}
				#endif
			
				bool isLogicalConditionOperatorAtCurrentLevel = false;
				if(firstNLCsentenceInFullSentence->logicalConditionOperator == NLC_LOGICAL_CONDITION_OPERATIONS_IF)
				{
					if(currentSentence == firstNLCsentenceInFullSentence)
					{
						isLogicalConditionOperatorAtCurrentLevel = true;
					}
					else if(currentSentence->hasLogicalConditionOperator)
					{
						#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
						cout << "currentSentence->hasLogicalConditionOperator: " << logicalConditionOperationsArray[currentSentence->logicalConditionOperator] << endl;
						#endif
						if(currentSentence->indentation == firstNLCsentenceInFullSentence->indentation)
						{
							if((currentSentence->logicalConditionOperator > firstNLCsentenceInFullSentence->logicalConditionOperator) || (currentSentence->logicalConditionOperator == NLC_LOGICAL_CONDITION_OPERATIONS_ELSE_IF))	//allow multiple else if statements
							{
								isLogicalConditionOperatorAtCurrentLevel = true;
							}
							else
							{
								stillFindingLogicalConditionAtCurrentLevel = false;
							}
						}
						else if(currentSentence->indentation > firstNLCsentenceInFullSentence->indentation)
						{
							//gone up a level, ignore all logical condition operators
						}
						else if(currentSentence->indentation < firstNLCsentenceInFullSentence->indentation)
						{
							//gone down (back) a level; quit search for logical Condition operator sentences at current level (if, else if, else)
							stillFindingLogicalConditionAtCurrentLevel = false;
						}			
					}
				}
				else
				{//while and for loops do not use cases (only if statements use cases)
					isLogicalConditionOperatorAtCurrentLevel = true;	//NB currentSentence == firstNLCsentenceInFullSentence
					stillFindingLogicalConditionAtCurrentLevel = false;
				}
				
				
				if(isLogicalConditionOperatorAtCurrentLevel)
				{
					int sentenceIndexOfFullSentence = currentSentence->sentenceIndex;
					#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
					cout << "isLogicalConditionOperatorAtCurrentLevel: " << currentSentence->sentenceIndex << ", " << currentSentence->sentenceContents << endl;
					cout << "currentSentence->mathTextNLPparsablePhraseTotal = " << currentSentence->mathTextNLPparsablePhraseTotal << endl;
					#endif
					
					if((firstNLCsentenceInFullSentence->logicalConditionOperator == NLC_LOGICAL_CONDITION_OPERATIONS_FOR) && (currentSentence->mathTextNLPparsablePhraseTotal > 1))
					{
						//assume "and" conjunction(s) has been specified; eg "For all baskets in the house and apples in the tree, eat the pie."
					}
					
					if(currentSentence->mathTextNLPparsablePhraseTotal > 0)
					{
						NLCsentence * parsablePhrase = currentSentence;
						for(int phraseIndex=0; phraseIndex<currentSentence->mathTextNLPparsablePhraseTotal; phraseIndex++)
						{
							if(parsablePhrase->mathTextNLPparsablePhraseIndex != phraseIndex)
							{
								cout << "generateCodeBlocksFromMathText() error: (currentSentence->mathTextNLPparsablePhraseIndex != i)" << endl;
							}
							if(firstNLCsentenceInFullSentence->logicalConditionOperator == NLC_LOGICAL_CONDITION_OPERATIONS_FOR)
							{
								if(!generateCodeBlocksFromMathTextNLPparsablePhraseLogicalConditionFor(currentCodeBlockInTree, entityNodesActiveListComplete, parsablePhrase->sentenceIndex, currentSentence, parsablePhrase, phraseIndex, &currentCodeBlockInTreeAtBaseLevel, firstNLCsentenceInFullSentence))
								{
									result = false;
								}
							}
							else
							{
								GIAentityNode * definitionEntity = NULL;
								GIAentityNode * logicalConditionOperationObject = NULL;
								#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_BASED_ON_ACTIONS_BASIC
								if(checkIfPhraseContainsAction(entityNodesActiveListComplete, parsablePhrase->sentenceIndex, &logicalConditionOperationObject))
								{//eg "The sun fights. / If the sun fights, the dog is happy."
								
									string parsablePhraseReferenceName = generateMathTextNLPparsablePhraseReference(currentSentence->sentenceIndex, parsablePhrase);
									*currentCodeBlockInTree = createCodeBlockDeclareNewBoolVar(*currentCodeBlockInTree, parsablePhraseReferenceName, false);

									setDummyReferenceSetIDforAllEntitiesInPhrase(entityNodesActiveListComplete, parsablePhrase->sentenceIndex);	//this is required for searchForEquivalentSubnetToIfStatement()
									GIAentityNode * actionEntityCompare = logicalConditionOperationObject;	//if statement comparison...
									GIAentityNode * actionEntityCompareConcept = getPrimaryConceptNodeDefiningInstance(actionEntityCompare);
									if(searchForEquivalentSubnetToIfStatement(actionEntityCompareConcept, logicalConditionOperationObject, false))
									{
										*currentCodeBlockInTree = createCodeBlockSetBoolVar(*currentCodeBlockInTree, parsablePhraseReferenceName, true);
										#ifdef NLC_DEBUG
										//cout << "NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_BASED_ON_ACTIONS_BASIC: passed logical condition" << endl;
										#endif
									}								
								} else 
								#endif
								#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_BASED_ON_CONCEPTS_BASIC
								if(checkIfPhraseContainsSubstanceConceptWithDefinitionLink(entityNodesActiveListComplete, parsablePhrase->sentenceIndex, &logicalConditionOperationObject))
								{//eg "Red dogs are pies. / If red dogs are pies, eat the cabbage."
								
									//logical operations on concepts are performed by NLC (code is not generated for them by NLC as they are not performed at runtime) - eg If red dogs are pies, eat the cabbage.	[as opposed to: "if the red dog is the/a pie, eat the cabbage"]
									//verify the truth of the if statement now (if the statement is false, disable all classStructure formation based on condition subject subset)
								
									//cout << "logicalConditionOperationObject->isSubstanceConcept" << endl;
									string parsablePhraseReferenceName = generateMathTextNLPparsablePhraseReference(currentSentence->sentenceIndex, parsablePhrase);
									*currentCodeBlockInTree = createCodeBlockDeclareNewBoolVar(*currentCodeBlockInTree, parsablePhraseReferenceName, false);

									setDummyReferenceSetIDforAllEntitiesInPhrase(entityNodesActiveListComplete, parsablePhrase->sentenceIndex);	//this is required for searchForEquivalentSubnetToIfStatement()
									GIAentityNode * substanceConceptEntityCompare = logicalConditionOperationObject;	//if statement comparison...
									GIAentityNode * substanceConceptEntityCompareConcept = getPrimaryConceptNodeDefiningInstance(substanceConceptEntityCompare);
									if(searchForEquivalentSubnetToIfStatement(substanceConceptEntityCompareConcept, logicalConditionOperationObject, true))	//searches for previous "red dogs are pies"
									{
										*currentCodeBlockInTree = createCodeBlockSetBoolVar(*currentCodeBlockInTree, parsablePhraseReferenceName, true);
										#ifdef NLC_DEBUG
										//cout << "NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_BASED_ON_CONCEPTS: passed logical condition" << endl;
										#endif
									}
								} else
								#endif
								#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_BASED_ON_CONCEPTS_BASIC_DYNAMIC
								if(checkIfPhraseContainsSubstanceWithDefinitionLink(entityNodesActiveListComplete, parsablePhrase->sentenceIndex, &logicalConditionOperationObject, &definitionEntity))
								{//eg "The dog is an alsation. / If the dog is an alsation, eat the cabbage."
								
									//cout << "logicalConditionOperationObject->isSubstance" << endl;
									string parsablePhraseReferenceName = generateMathTextNLPparsablePhraseReference(currentSentence->sentenceIndex, parsablePhrase);
									*currentCodeBlockInTree = createCodeBlockDeclareNewBoolVar(*currentCodeBlockInTree, parsablePhraseReferenceName, false);
	
									bool parseConditionParents = true;	//use default value here
									GIAentityNode * parentEntity = getParent(logicalConditionOperationObject, sentenceIndex, parseConditionParents);
									NLCgenerateContextBlocksVariables generateContextBlocksVariables;
									generateContextBlocksVariables.searchSubstanceConceptsForChildren = false;	//added 1n5g (only check the explicit variable for definition)
									bool generatedContextBlocks = generateContextBlocks(currentCodeBlockInTree, parentEntity, sentenceIndex, &generateContextBlocksVariables, false, NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION);	//check if should parse categories here
									//bool generatedContextBlocks = generateContextBlocksSimple(currentCodeBlockInTree, parentEntity, sentenceIndex, &generateContextBlocksVariables, false, NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION);	//check if should parse categories here
									
									//eg If the dog is an alsation, eat the cabbage
									*currentCodeBlockInTree = createCodeBlockCheckParentClassNameExecuteFunction1(*currentCodeBlockInTree, logicalConditionOperationObject, definitionEntity->entityName);
									
									//eg If the dog is a red alsation, eat the cabbage
									if(createCodeBlockForStatements(currentCodeBlockInTree, generateInstanceName(logicalConditionOperationObject), definitionEntity, sentenceIndex, &generateContextBlocksVariables))
									{
										
									}
									
									*currentCodeBlockInTree = createCodeBlockSetBoolVar(*currentCodeBlockInTree, parsablePhraseReferenceName, true);
								} else
								#endif
								if(!generateCodeBlocksFromMathTextNLPparsablePhrase(currentCodeBlockInTree, entityNodesActiveListComplete, parsablePhrase->sentenceIndex, currentSentence, parsablePhrase, phraseIndex, caseIndex))
								{
									result = false;
								}
							}
							#ifdef NLC_DEBUG_PREPROCESSOR_MATH
							cout << "finished generateCodeBlocksFromMathTextNLPparsablePhrase()" << endl;
							#endif
							parsablePhrase = parsablePhrase->next;
						}
						caseIndex++;
						currentSentence = parsablePhrase;
					}
					else
					{
						caseIndex++;
						currentSentence = currentSentence->next;						
					}
				}
				else
				{
					if(currentSentence->next != NULL)
					{
						currentSentence = currentSentence->next;
					}
					else
					{
						stillFindingLogicalConditionAtCurrentLevel = false;
					}
				}
			}
		
			if(firstNLCsentenceInFullSentence->logicalConditionOperator == NLC_LOGICAL_CONDITION_OPERATIONS_IF)
			{
				currentCodeBlockInTreeAtBaseLevel = (*currentCodeBlockInTree);
			}			
		}
		else if((firstNLCsentenceInFullSentence->logicalConditionOperator == NLC_LOGICAL_CONDITION_OPERATIONS_ELSE_IF) || (firstNLCsentenceInFullSentence->logicalConditionOperator == NLC_LOGICAL_CONDITION_OPERATIONS_ELSE))
		{
			currentCodeBlockInTreeAtBaseLevel = *currentCodeBlockInTree;		
		}
		else
		{
			cout << "generateCodeBlocksFromMathText() error: illegal firstNLCsentenceInFullSentence->logicalConditionOperator" << endl;
			exit(0);
		}
		
		#ifdef NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT
		if(firstNLCsentenceInFullSentence->logicalConditionOperator != NLC_LOGICAL_CONDITION_OPERATIONS_FOR)
		{
			(*currentCodeBlockInTree)->isLogicalCondition = true;
			(*currentCodeBlockInTree)->contextLevel = firstNLCsentenceInFullSentence->indentation+1;
		}
		#endif
	}
	else
	{
	#endif
		NLCsentence * parsablePhrase = firstNLCsentenceInFullSentence;
		for(int phraseIndex=0; phraseIndex<firstNLCsentenceInFullSentence->mathTextNLPparsablePhraseTotal; phraseIndex++)
		{
			if(parsablePhrase->mathTextNLPparsablePhraseIndex != phraseIndex)
			{
				cout << "generateCodeBlocksFromMathText() error: (currentSentence->mathTextNLPparsablePhraseIndex != i)" << endl;
			}
			if(!generateCodeBlocksFromMathTextNLPparsablePhrase(currentCodeBlockInTree, entityNodesActiveListComplete, parsablePhrase->sentenceIndex, firstNLCsentenceInFullSentence, parsablePhrase, phraseIndex, 0))
			{
				result = false;
			}
			parsablePhrase = parsablePhrase->next;
		}
	#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
	}
	#endif	

	#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
	if(firstNLCsentenceInFullSentence->hasLogicalConditionOperator)
	{
		if(firstNLCsentenceInFullSentence->logicalConditionOperator == NLC_LOGICAL_CONDITION_OPERATIONS_WHILE)
		{
			firstNLCsentenceInFullSentence->mathText.replace(0, string(NLC_LOGICAL_CONDITION_OPERATIONS_WHILE_STRING).length(), string(NLC_LOGICAL_CONDITION_OPERATIONS_IF_STRING));	//replace "while" with "if" for the purposes of generating final code (while loop has already been defined)
		}
			
		if(firstNLCsentenceInFullSentence->logicalConditionOperator != NLC_LOGICAL_CONDITION_OPERATIONS_FOR)
		{
			#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
			cout << "createCodeBlockMathTextWithLogicalOperator: firstNLCsentenceInFullSentence->mathText = " << firstNLCsentenceInFullSentence->mathText << endl;
			#endif
			*currentCodeBlockInTree = createCodeBlockMathTextWithLogicalOperator(*currentCodeBlockInTree, firstNLCsentenceInFullSentence->mathText);
		}
		
		if(firstNLCsentenceInFullSentence->logicalConditionOperator == NLC_LOGICAL_CONDITION_OPERATIONS_WHILE)
		{
			*currentCodeBlockInTree = createCodeBlockSetBoolVar(*currentCodeBlockInTree, whileLogicalConditionConjunctionBooleanName, true);
		}
		
		#ifdef NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT
		*currentCodeBlockInTree = createCodeBlocksDeclareContextList(*currentCodeBlockInTree, firstNLCsentenceInFullSentence->indentation+1);
		#endif
		
		if(firstNLCsentenceInFullSentence->next != NULL)
		{
			NLCsentence * nextNLCfullSentenceInList = firstNLCsentenceInFullSentence;
			bool hasNextSentence = false;
			if(firstNLCsentenceInFullSentence->mathTextNLPparsablePhraseTotal > 0)
			{
				for(int phraseIndex=0; phraseIndex<firstNLCsentenceInFullSentence->mathTextNLPparsablePhraseTotal; phraseIndex++)
				{
					nextNLCfullSentenceInList = nextNLCfullSentenceInList->next;
				}
			}
			else
			{
				nextNLCfullSentenceInList = firstNLCsentenceInFullSentence->next;			
			}
			
			#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE	
			cout << "firstNLCsentenceInFullSentence->sentenceContents = " << firstNLCsentenceInFullSentence->sentenceContents << endl;
			cout << "nextNLCfullSentenceInList->sentenceContents = " << nextNLCfullSentenceInList->sentenceContents << endl;
			cout << "firstNLCsentenceInFullSentence->indentation = " << firstNLCsentenceInFullSentence->indentation << endl;
			cout << "nextNLCfullSentenceInList->indentation = " << nextNLCfullSentenceInList->indentation << endl;
			#endif
			
			if(nextNLCfullSentenceInList->indentation == (firstNLCsentenceInFullSentence->indentation + 1))
			{
				#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
				cout << "(nextNLCfullSentenceInList->indentation == (firstNLCsentenceInFullSentence->indentation + 1))" << endl;
				#endif
				//do not, just record the in the tree
				setCodeBlockAtPreviousLogicalConditionBaseLevelArray(firstNLCsentenceInFullSentence->indentation, currentCodeBlockInTreeAtBaseLevel->next);
			}
			else if(nextNLCfullSentenceInList->indentation <= firstNLCsentenceInFullSentence->indentation)
			{
				#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
				cout << "(nextNLCfullSentenceInList->indentation <= firstNLCsentenceInFullSentence->indentation)" << endl;
				#endif			
				*currentCodeBlockInTree = currentCodeBlockInTreeAtBaseLevel->next;
				//NB if(nextNLCfullSentenceInList->indentation < firstNLCsentenceInFullSentence->indentation) will be processed later by generateCodeBlocks()
			}
			else
			{
				cout << "NLC_USE_PREPROCESSOR generateCodeBlocksPart2logicalConditions() error: invalid indentation of nextNLCfullSentenceInList, sentenceIndex = " << sentenceIndex << endl;
				cout << "nextNLCfullSentenceInList->indentation <= firstNLCsentenceInFullSentence->indentation + 1" << endl;
				cout << "firstNLCsentenceInFullSentence->indentation = " << firstNLCsentenceInFullSentence->indentation << endl;
				cout << "nextNLCfullSentenceInList->indentation = " << nextNLCfullSentenceInList->indentation << endl;
			}
		}
									
	}
	else
	{
	#endif
		*currentCodeBlockInTree = createCodeBlockMathTextLine(*currentCodeBlockInTree, firstNLCsentenceInFullSentence->mathText);
	#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
	}
	#endif
	
	#ifdef NLC_DEBUG_PREPROCESSOR_MATH
	cout << "finished generateCodeBlocksFromMathText()" << endl;
	#endif
	
	return result;
}	

bool generateCodeBlocksFromMathTextNLPparsablePhrase(NLCcodeblock ** currentCodeBlockInTree, vector<GIAentityNode*> * entityNodesActiveListComplete, int sentenceIndex, NLCsentence * currentFullSentence, NLCsentence * parsablePhrase, int phraseIndex, int caseIndex)
{
	bool foundParsablePhrase = false;
	
	#ifdef NLC_DEBUG_PREPROCESSOR_MATH
	cout << "generateCodeBlocksFromMathTextNLPparsablePhrase() part 1" << endl;
	#endif
	//generate NLP parsable phrase eg "the number of chickens" in "if(the number of chickens > the number of apples...)"
	NLCcodeblock * currentCodeBlockAtStartOfparsablePhrase = *currentCodeBlockInTree;
	string parsablePhraseReferenceName = generateMathTextNLPparsablePhraseReference(currentFullSentence->sentenceIndex, parsablePhrase);	//parsablePhraseGenerateNumberOfElementCounterName
	*currentCodeBlockInTree = createCodeBlockDeclareNewIntVar(*currentCodeBlockInTree, parsablePhraseReferenceName, 0);	//?this will need to be changed to createCodeBlockDeclareNewIntArray in the future to support multiple cases (ie if, else if, else)
	
	//if !NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE, currently only accept entities with $qVar defined, eg "Number of red dogs". prep_of(number-4, dogs-7) [NLP] / _quantity(dog[8], _$qVar[1]) [GIA]
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode * entity = (*entityIter);
		if(checkSentenceIndexParsingCodeBlocks(entity, sentenceIndex, false))
		{
			if(!(entity->isConcept) && !(entity->isCondition))
			{//redundant	
				#ifdef NLC_PREPROCESSOR_MATH_OLD_NUMBER_OF_IMPLEMENTATION_USING_QVARS
				if(entity->isQuery)
				#else
				if(entity->isNumberOf)
				#endif
				{
					#ifdef NLC_DEBUG
					//cout << "generateCodeBlocksFromMathTextNLPparsablePhrase(): sentenceIndex = " << sentenceIndex << endl;
					//cout << "generateCodeBlocksFromMathTextNLPparsablePhrase(): " << entity->entityName << ", entity->sentenceIndexTemp = " << entity->sentenceIndexTemp << endl;
					#endif
					
					if(foundParsablePhrase)
					{
						cout << "generateCodeBlocksFromMathTextNLPparsablePhrase() error: more than one parsable phrase primary entity found" << endl;
					}
					foundParsablePhrase = true;

					#ifdef NLC_DEBUG_PREPROCESSOR_MATH
					cout << "generateCodeBlocksFromMathTextNLPparsablePhrase(): found 'number of' designation, entity: " << entity->entityName << endl;
					#endif
					NLCgenerateContextBlocksVariables generateContextBlocksVariables;
					#ifdef NLC_LOGICAL_CONDITION_OPERATIONS_SUPPORT_INDEFINITE_LOGICAL_CONDITION_OBJECTS
					//number of statements must be expressed using definite variables, but they will not be advanced referenced by GIA (and so must be located in the typeList)
					//if(!assumedToAlreadyHaveBeenDeclared(entity))	//"the number of x" will have already been declared, but is not advanced referenced, so much search the typeList
					//{
						#ifdef NLC_GENERATE_TYPE_LISTS
						//1i implementation
						*currentCodeBlockInTree = createCodeBlockForPropertyTypeClass(*currentCodeBlockInTree, entity);	//eg "If a house is green, do this", an instanceList (OLD: localList) for "a house" is assumed to have already been declared, one of which may be green, so search all house instanceLists within house typeList...
						//if at least one instanceList of type currentLogicalConditionObject has not previously been declared, then the code will result in a compilation error
						//if at least one instanceList of type currentLogicalConditionObject has previously been declared, but does not have the required properties (eg green), then the code will compile but the if statement will fail
						#else
						//1j implementation
						entity->grammaticalDefiniteTemp = true;		//removed 1j15a
						#endif					
					//}
					#endif
					if(!getParentAndGenerateContextBlocks(currentCodeBlockInTree, entity, sentenceIndex, &generateContextBlocksVariables, true))	//NB parseConditionParents probably does not need to ever be set to true (unless condition subject/object are switched and condition name is updated accordingly to reflect this inversion of relationship)
					{
						#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
						cout << "generateCodeBlocksFromMathTextNLPparsablePhrase() error: !getParentAndGenerateContextBlocks: " << entity->entityName << endl;
						#endif
					}

					*currentCodeBlockInTree = createCodeBlockIncrementIntVar(*currentCodeBlockInTree, parsablePhraseReferenceName);

					*currentCodeBlockInTree = getLastCodeBlockInLevel(currentCodeBlockAtStartOfparsablePhrase);				
				}
			}
		}
	}	
	if(!foundParsablePhrase)
	{
		#ifndef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
		cout << "generateCodeBlocksFromMathTextNLPparsablePhrase() error: !foundParsablePhrase" << endl;		
		#endif
		*currentCodeBlockInTree = currentCodeBlockAtStartOfparsablePhrase;	//redundant
		clearCodeBlock(currentCodeBlockAtStartOfparsablePhrase);
	
	
		#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
		
		#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
		cout << "generateCodeBlocksFromMathTextNLPparsablePhrase() part 2" << endl;
		#endif
		
		#ifdef NLC_PREPROCESSOR_MATH_USE_LOGICAL_CONDITION_OPERATIONS_ADVANCED_BACKWARDS_COMPATIBLE_VARIABLE_NAMES
		parsablePhraseReferenceName = generateLogicalConditionConjunctionBooleanName(currentFullSentence->indentation, caseIndex, phraseIndex, NLC_LOGICAL_CONDITION_OPERATIONS_IF);
		#else
		*currentCodeBlockInTree = createCodeBlockDeclareNewBoolVar(*currentCodeBlockInTree, parsablePhraseReferenceName, false);	//?this will need to be changed to createCodeBlockDeclareNewBoolArray in the future to support multiple cases (ie if, else if, else)
		#endif
		
		//generate NLP parsable phrase eg "the red chicken is next to the house" in "if(the red chicken is next to the house && the blue box has an apple)"
		if(currentFullSentence->hasLogicalConditionOperator)	//CHECKTHIS; is NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE required for non-logical condition mathText?
		{
			foundParsablePhrase = false;
			for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
			{
				GIAentityNode * entity = (*entityIter);
				if(checkSentenceIndexParsingCodeBlocks(entity, sentenceIndex, false))
				{
					if(!(entity->isConcept) && !(entity->isCondition))
					{//required			
						#ifdef NLC_PREPROCESSOR_MATH_OLD_NUMBER_OF_IMPLEMENTATION_USING_QVARS
						if(entity->isQuery)
						#else
						if(entity->isNumberOf)
						#endif
						{
							#ifdef NLC_DEBUG
							//cout << "generateCodeBlocksFromMathTextNLPparsablePhrase() error: entity->isNumberOf && !(entity->NLCcontextGenerated): part 1 must have failed" << endl;
							#endif
						}
						else
						{		
							if(!foundParsablePhrase)
							{
								#ifdef NLC_DEBUG_PREPROCESSOR_MATH
								cout << "generateCodeBlocksFromMathTextNLPparsablePhrase(): found entity: " << entity->entityName << endl;
								#endif

								GIAentityNode * parentEntity = getParent(entity, sentenceIndex, true);	//NB parseConditionParents probably does not need to ever be set to true (unless condition subject/object are switched and condition name is updated accordingly to reflect this inversion of relationship)

								NLCgenerateContextBlocksVariables generateContextBlocksVariables;
								NLCcodeblock * NLCcodeBlockBeforeGenerateContext = *currentCodeBlockInTree; 
								bool contextFound = false;

								#ifdef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES
								#ifdef NLC_LOGICAL_CONDITION_OPERATIONS_SUPPORT_INDEFINITE_LOGICAL_CONDITION_OBJECTS
								//if/while statements can be expressed using either definite or indefinate variables, but if they indefinite they will not be advanced referenced by GIA (and so must be located in the typeList)
								if(!assumedToAlreadyHaveBeenDeclared(parentEntity))
								{
									#ifdef NLC_GENERATE_TYPE_LISTS
									//1i implementation
									*currentCodeBlockInTree = createCodeBlockForPropertyTypeClass(*currentCodeBlockInTree, parentEntity);	//eg "If a house is green, do this", an instanceList (OLD: localList) for "a house" is assumed to have already been declared, one of which may be green, so search all house instanceLists within house typeList...
									//if at least one instanceList of type currentLogicalConditionObject has not previously been declared, then the code will result in a compilation error
									//if at least one instanceList of type currentLogicalConditionObject has previously been declared, but does not have the required properties (eg green), then the code will compile but the if statement will fail
									#else
									//1j implementation
									//parentEntity->grammaticalDefiniteTemp = true;		//removed 1j15a
									#endif
								}
								#endif
								if(generateContextBlocks(currentCodeBlockInTree, parentEntity, sentenceIndex, &generateContextBlocksVariables, false, NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION))
								{
									contextFound = true;
								}
								#else
								//*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("generateCodeBlocksFromMathTextNLPparsablePhrase():  1 generateContextBlocks: ") + parentEntity->entityName);
								//NB logicalConditionOperator != NLC_LOGICAL_CONDITION_OPERATIONS_FOR (if so generateCodeBlocksFromMathTextNLPparsablePhraseLogicalConditionFor is executed instead)
								//therefore logicalConditionOperator == NLC_LOGICAL_CONDITION_OPERATIONS_IF/NLC_LOGICAL_CONDITION_OPERATIONS_ELSE_IF/NLC_LOGICAL_CONDITION_OPERATIONS_ELSE_WHILE
								generateContextBlocksVariables.onlyGenerateContextBlocksIfConnectionsParsedForNLC = true;
								if(generateContextBlocks(currentCodeBlockInTree, parentEntity, sentenceIndex, &generateContextBlocksVariables, false, NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION))
								{
									contextFound = true;
								}
								generateContextBlocksVariables.onlyGenerateContextBlocksIfConnectionsParsedForNLC = false;
								#ifdef NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY
								generateContextBlocksVariables.testNumerosity = true;
								#endif
								//*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("generateCodeBlocksFromMathTextNLPparsablePhrase():  2 generateContextBlocks: ") + parentEntity->entityName);
								if(generateContextBlocks(currentCodeBlockInTree, parentEntity, sentenceIndex, &generateContextBlocksVariables, true, NLC_ITEM_TYPE_LOGICALCONDITION_VAR_APPENDITION))
								{
									contextFound = true;
								}	
								#endif
	
								if(!contextFound)
								{
									#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
									cout << "generateCodeBlocksFromMathTextNLPparsablePhrase() error: !getParentAndGenerateContextBlocks: sentenceIndex = " << sentenceIndex << endl;
									#endif
									
									*currentCodeBlockInTree = NLCcodeBlockBeforeGenerateContext;
									clearCodeBlock(*currentCodeBlockInTree);							
								}
								else
								{
									#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
									cout << "generateCodeBlocksFromMathTextNLPparsablePhrase() pass: getParentAndGenerateContextBlocks: sentenceIndex = " << sentenceIndex << endl;
									#endif
									
									foundParsablePhrase = true;
									
									if(generateContextBlocksVariables.negativeDetectedInContextBlocks)
									{
										int parsablePhraseReferenceNamePosInMathText = currentFullSentence->mathText.find(parsablePhraseReferenceName);
										if(parsablePhraseReferenceNamePosInMathText != CPP_STRING_FIND_RESULT_FAIL_VALUE)	//&& (parsablePhraseReferenceNamePosInMathText > 0
										{
											currentFullSentence->mathText.insert(parsablePhraseReferenceNamePosInMathText, 1, NLC_PREPROCESSOR_MATH_OPERATOR_NEGATIVE_CHAR);
											#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
											cout << "negativeDetectedInContextBlocks detected; inserting NLC_PREPROCESSOR_MATH_OPERATOR_NEGATIVE_CHAR into mathText logical condition" << endl;
											#endif
										}
									}
									
									*currentCodeBlockInTree = createCodeBlockSetBoolVar(*currentCodeBlockInTree, parsablePhraseReferenceName, true);

									*currentCodeBlockInTree = getLastCodeBlockInLevel(currentCodeBlockAtStartOfparsablePhrase);								
								}
							}
						}
					}
				}
			}			
		}
		#endif
		if(!foundParsablePhrase)
		{
			cout << "generateCodeBlocksFromMathTextNLPparsablePhrase() error: !foundParsablePhrase" << endl;		
			*currentCodeBlockInTree = currentCodeBlockAtStartOfparsablePhrase;	//redundant
			clearCodeBlock(currentCodeBlockAtStartOfparsablePhrase);
		}
	}
	
	return foundParsablePhrase;
}

bool generateCodeBlocksFromMathTextNLPparsablePhraseLogicalConditionFor(NLCcodeblock ** currentCodeBlockInTree, vector<GIAentityNode*> * entityNodesActiveListComplete, int sentenceIndex, NLCsentence * currentFullSentence, NLCsentence * parsablePhrase, int phraseIndex, NLCcodeblock ** currentCodeBlockInTreeAtBaseLevel, NLCsentence * firstNLCsentenceInFullSentence)
{
	bool foundParsablePhrase = false;
	
	#ifdef NLC_DEBUG_PREPROCESSOR_MATH
	cout << "generateCodeBlocksFromMathTextNLPparsablePhraseLogicalConditionFor()" << endl;
	#endif
	//generate NLP parsable phrase eg "all apples in the cart" in "for(all the apples in the cart)"
	
	if((currentFullSentence->hasLogicalConditionOperator) && (currentFullSentence->logicalConditionOperator == NLC_LOGICAL_CONDITION_OPERATIONS_FOR))
	{
		foundParsablePhrase = false;
		for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
		{
			GIAentityNode * entity = (*entityIter);
			if(checkSentenceIndexParsingCodeBlocks(entity, sentenceIndex, false))
			{
				if(!(entity->isConcept) && !(entity->isCondition))
				{//required
					if(!foundParsablePhrase)
					{
						NLCgenerateContextBlocksVariables generateContextBlocksVariables;
						#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
						generateContextBlocksVariables.setCodeBlockInTreeAtBaseLevel = true;
						#endif
						NLCcodeblock * NLCcodeBlockBeforeGenerateContext = *currentCodeBlockInTree; 
						/*//for statements must be expressed using definite variables, and they will be advanced referenced by GIA (ie "for all the chickens...", not "for a chicken..")
						if(!assumedToAlreadyHaveBeenDeclared(entity))
						{
						      *currentCodeBlockInTree = createCodeBlockForPropertyTypeClass(*currentCodeBlockInTree, entity);   //eg "If a house is green, do this", an instanceList (OLD: localList) for "a house" is assumed to have already been declared, one of which may be green, so search all house instanceLists within house typeList...
						      //if at least one instanceList of type currentLogicalConditionObject has not previously been declared, then the code will result in a compilation error
						      //if at least one instanceList of type currentLogicalConditionObject has previously been declared, but does not have the required properties (eg green), then the code will compile but the if statement will fail
						}
						*/
						//cout << "getParentAndGenerateContextBlocks:" << endl;
						if(!getParentAndGenerateContextBlocks(currentCodeBlockInTree, entity, sentenceIndex, &generateContextBlocksVariables, true))	//NB parseConditionParents probably does not need to ever be set to true (unless condition subject/object are switched and condition name is updated accordingly to reflect this inversion of relationship)
						{
							#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
							cout << "generateCodeBlocksFromMathTextNLPparsablePhrase() error: !getParentAndGenerateContextBlocks: sentenceIndex = " << sentenceIndex << endl;
							#endif
							
							#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
							*currentCodeBlockInTreeAtBaseLevel = generateContextBlocksVariables.currentCodeBlockInTreeAtBaseLevel;
							#ifdef NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT
							(*currentCodeBlockInTreeAtBaseLevel)->isLogicalCondition = true;
							(*currentCodeBlockInTreeAtBaseLevel)->contextLevel = firstNLCsentenceInFullSentence->indentation+1;
							#endif
							#endif
							foundParsablePhrase = true;						
						}
						else
						{
							#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
							*currentCodeBlockInTreeAtBaseLevel = generateContextBlocksVariables.currentCodeBlockInTreeAtBaseLevel;
							#ifdef NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT
							(*currentCodeBlockInTreeAtBaseLevel)->isLogicalCondition = true;
							(*currentCodeBlockInTreeAtBaseLevel)->contextLevel = firstNLCsentenceInFullSentence->indentation+1;
							#endif
							#endif
							foundParsablePhrase = true;
						}
					}	
				}
			}
		}
	}
	return foundParsablePhrase;
}
					
#endif

#ifdef NLC_PREPROCESSOR_MATH_REPLACE_NUMERICAL_VARIABLES_NAMES_FOR_NLP
bool findAndSetDummyNumericalValueForReplacement(vector<GIAentityNode*> * entityNodesActiveListComplete, int sentenceIndex, int dummyNumericalValue, string numericalVariableName)
{
	bool result = true;
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode * entity = (*entityIter);
		if(checkSentenceIndexParsingCodeBlocks(entity, sentenceIndex, false))
		{
			if(entity->quantityNumber == dummyNumericalValue)
			{
				#ifdef NLC_DEBUG
				//cout << "findAndSetDummyNumericalValueForReplacement(): " << endl;
				//cout << "entity->quantityNumber = " << entity->quantityNumber << endl;
				//cout << "dummyNumericalValue = " << dummyNumericalValue << endl;
				//cout << "sentenceIndex = " << sentenceIndex << endl;
				#endif
				entity->NLCoriginalNumericalVariableName = numericalVariableName;
				result = true;
			}
		}	
	}
	return result;
}
#endif

#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_BASED_ON_ACTIONS_BASIC
bool checkIfPhraseContainsAction(vector<GIAentityNode*> * entityNodesActiveListComplete, int sentenceIndex, GIAentityNode ** logicalConditionOperationObject)
{
	bool phraseContainsAction = false;
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode * entity = (*entityIter);
		if(checkSentenceIndexParsingCodeBlocks(entity, sentenceIndex, false))
		{		
			if(entity->isAction || entity->isActionConcept)
			{
				phraseContainsAction = true;
				*logicalConditionOperationObject = entity;
			}
		}
	}
	return phraseContainsAction;
}
#endif

#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_BASED_ON_CONCEPTS_BASIC
bool checkIfPhraseContainsSubstanceConceptWithDefinitionLink(vector<GIAentityNode*> * entityNodesActiveListComplete, int sentenceIndex, GIAentityNode ** logicalConditionOperationObject)
{
	bool phraseContainsSubstanceConceptWithDefinitionLink = false;
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode * entity = (*entityIter);
		if(checkSentenceIndexParsingCodeBlocks(entity, sentenceIndex, false))
		{		
			if(entity->isSubstanceConcept)
			{
				for(vector<GIAentityConnection*>::iterator iter = entity->entityNodeDefinitionList->begin(); iter < entity->entityNodeDefinitionList->end(); iter++)
				{
					GIAentityConnection * definitionConnection = *iter;
					GIAentityNode * definitionEntityTemp =  definitionConnection->entity;
					if(definitionConnection->sentenceIndexTemp == sentenceIndex)
					{
						if(!(definitionConnection->sameReferenceSet))
						{
							if(!isDefiniteEntity(entity) && !isDefiniteEntity(definitionEntityTemp))
							{
								phraseContainsSubstanceConceptWithDefinitionLink = true;
								*logicalConditionOperationObject = entity;
							}
							else
							{
								cout << "checkIfPhraseContainsSubstanceConceptWithDefinitionLink() warning: !(!isDefiniteEntity(entity)) && !isDefiniteEntity(definitionEntityTemp))" << endl;
							}
						}
					}
				}
				/*OLD: before 1n5b update;	
				if(!(entity->entityNodeDefinitionList->empty()))
				{
					phraseContainsSubstanceConcept = true;
					*logicalConditionOperationObject = entity;
				}
				*/
			}
		}
	}
	return phraseContainsSubstanceConceptWithDefinitionLink;
}
#endif

#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_BASED_ON_CONCEPTS_BASIC_DYNAMIC
bool checkIfPhraseContainsSubstanceWithDefinitionLink(vector<GIAentityNode*> * entityNodesActiveListComplete, int sentenceIndex, GIAentityNode ** logicalConditionOperationObject, GIAentityNode ** definitionEntity)
{
	bool phraseContainsSubstanceWithDefinitionLink = false;
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode * entity = (*entityIter);
		if(checkSentenceIndexParsingCodeBlocks(entity, sentenceIndex, false))
		{		
			if((entity->isSubstance) && (!entity->isSubstanceConcept))
			{
				for(vector<GIAentityConnection*>::iterator iter = entity->entityNodeDefinitionList->begin(); iter < entity->entityNodeDefinitionList->end(); iter++)
				{
					GIAentityConnection * definitionConnection = *iter;
					GIAentityNode * definitionEntityTemp = definitionConnection->entity;
					if(definitionConnection->sentenceIndexTemp == sentenceIndex)
					{
						if(!(definitionConnection->sameReferenceSet))
						{
							if(isDefiniteEntity(entity) && !isDefiniteEntity(definitionEntityTemp))
							{
								if(entity->entityName != definitionEntityTemp->entityName)
								{//ignore substanceConcept definitions for for entities of same name
									phraseContainsSubstanceWithDefinitionLink = true;
									*logicalConditionOperationObject = entity;
									*definitionEntity = definitionEntityTemp;
									//cout << "entity = " << entity->entityName << endl;
									//cout << "definitionEntity = " << definitionEntityTemp->entityName << endl;
								}
							}
							else
							{
								cout << "checkIfPhraseContainsSubstanceWithDefinitionLink() warning: !(isDefiniteEntity(entity)) && !isDefiniteEntity(definitionEntityTemp))" << endl;
							}
						}
					}
				}
			}
		}
	}
	return phraseContainsSubstanceWithDefinitionLink;
}
#endif


void setDummyReferenceSetIDforAllEntitiesInPhrase(vector<GIAentityNode*> * entityNodesActiveListComplete, int sentenceIndex)
{
	//cout << "setDummyReferenceSetIDforAllEntitiesInPhrase: " << endl;
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode * entity = (*entityIter);
		if(checkSentenceIndexParsingCodeBlocks(entity, sentenceIndex, false))
		{			
			entity->referenceSetID = NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_BASED_ON_ACTIONS_OR_CONCEPTS_DUMMY_REFERENCE_SET_ID;
			#ifdef NLC_DEBUG
			//cout << "setDummyReferenceSetIDforAllEntitiesInPhrase():" << endl;
			//cout << "entity = " << entity->entityName << endl;
			//cout << "entity->isConcept = " << entity->isConcept << endl;
			#endif
		}
	}
}

