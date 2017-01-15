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
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 1p13c 03-August-2015
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/


#include "NLCtranslatorCodeBlocksLogicalConditions.h"
#include "NLCtranslatorCodeBlocksLogicalConditionsAdvanced.h"
#include "NLCtranslatorCodeBlocksOperations.h"
#include "GIAtranslatorOperations.h"	//required for getPrimaryConceptNodeDefiningInstance{}
#include "NLCprintDefs.h"	//required for NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION

		
#ifdef NLC_PREPROCESSOR_MATH
bool generateCodeBlocksFromMathText(NLCcodeblock** currentCodeBlockInTree, map<int, vector<GIAentityNode*>*>::iterator sentenceIterFirstInFullSentence, int sentenceIndex, NLCsentence* firstNLCsentenceInFullSentence, string NLCfunctionName)
{
	#ifdef NLC_DEBUG_PREPROCESSOR_MATH
	cout << "\n generateCodeBlocksFromMathText{}: sentenceIndex = " << sentenceIndex << endl;
	#endif
	bool result = true;
	
	NLCcodeblock* currentCodeBlockInTreeAtBaseLevel = *currentCodeBlockInTree;
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
			cout << "firstNLCsentenceInFullSentence->logicalConditionOperator == " << firstNLCsentenceInFullSentence->logicalConditionOperator << endl;
			#endif
			int caseIndex = 0;
			int currentLevel = firstNLCsentenceInFullSentence->indentation;
			int currentLogicalConditionOperator = firstNLCsentenceInFullSentence->logicalConditionOperator;
			bool stillFindingLogicalConditionAtCurrentLevel = true;
			NLCsentence* currentSentence = firstNLCsentenceInFullSentence;
			map<int, vector<GIAentityNode*>*>::iterator sentenceIter = sentenceIterFirstInFullSentence;
			while(stillFindingLogicalConditionAtCurrentLevel)
			{//this loop is only required by NLC_LOGICAL_CONDITION_OPERATIONS_IF (it is not used by NLC_LOGICAL_CONDITION_OPERATIONS_WHILE and NLC_LOGICAL_CONDITION_OPERATIONS_FOR)
				
				#ifdef NLC_DISABLE_1i_CODE_FOR_DEBUG
				declareLocalPropertyListsForIndefiniteEntities(currentCodeBlockInTree, entityNodesActiveListSentence, sentenceIndex, NLCfunctionName, currentSentence);	//indefinite logical condition objects (eg "a house" in "if a house is green, do this") must have been previously declared else output code will not compile [as these statements implicitly assume the existence of "a house"; which may or may not be "green"]
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
						NLCsentence* parsablePhrase = currentSentence;
						map<int, vector<GIAentityNode*>*>::iterator parsablePhraseIter = sentenceIter;
						for(int phraseIndex=0; phraseIndex<currentSentence->mathTextNLPparsablePhraseTotal; phraseIndex++)
						{
							vector<GIAentityNode*>* entityNodesActiveListParsablePhrase = parsablePhraseIter->second;
							
							if(parsablePhrase->mathTextNLPparsablePhraseIndex != phraseIndex)
							{
								cout << "generateCodeBlocksFromMathText{} error: (currentSentence->mathTextNLPparsablePhraseIndex != i)" << endl;
							}
							if(firstNLCsentenceInFullSentence->logicalConditionOperator == NLC_LOGICAL_CONDITION_OPERATIONS_FOR)
							{
								if(!generateCodeBlocksFromMathTextNLPparsablePhraseLogicalConditionFor(currentCodeBlockInTree, entityNodesActiveListParsablePhrase, parsablePhrase->sentenceIndex, currentSentence, parsablePhrase, phraseIndex, &currentCodeBlockInTreeAtBaseLevel, firstNLCsentenceInFullSentence))
								{
									result = false;
								}
							}
							else
							{
								GIAentityNode* definitionEntity = NULL;
								GIAentityNode* logicalConditionOperationObject = NULL;
								#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_BASED_ON_ACTIONS_BASIC
								if(checkIfPhraseContainsAction(entityNodesActiveListParsablePhrase, parsablePhrase->sentenceIndex, &logicalConditionOperationObject))
								{//eg "The sun fights. / If the sun fights, the dog is happy."
																	
									string parsablePhraseReferenceName = generateMathTextNLPparsablePhraseReference(currentSentence->sentenceIndex, parsablePhrase);
									*currentCodeBlockInTree = createCodeBlockDeclareNewBoolVar(*currentCodeBlockInTree, parsablePhraseReferenceName, false);

									setDummyReferenceSetIDforAllEntitiesInPhrase(entityNodesActiveListParsablePhrase, parsablePhrase->sentenceIndex);	//this is required for searchForEquivalentSubnetToIfStatement{}
									GIAentityNode* actionEntityCompare = logicalConditionOperationObject;	//if statement comparison...
									GIAentityNode* actionEntityCompareConcept = getPrimaryConceptNodeDefiningInstance(actionEntityCompare);
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
								if(checkIfPhraseContainsSubstanceConceptWithDefinitionLink(entityNodesActiveListParsablePhrase, parsablePhrase->sentenceIndex, &logicalConditionOperationObject))
								{//eg "Red dogs are pies. / If red dogs are pies, eat the cabbage."
																	
									//logical operations on concepts are performed by NLC (code is not generated for them by NLC as they are not performed at runtime) - eg If red dogs are pies, eat the cabbage.	[as opposed to: "if the red dog is the/a pie, eat the cabbage"]
									//verify the truth of the if statement now (if the statement is false, disable all classStructure formation based on condition subject subset)
								
									//cout << "logicalConditionOperationObject->isSubstanceConcept" << endl;
									string parsablePhraseReferenceName = generateMathTextNLPparsablePhraseReference(currentSentence->sentenceIndex, parsablePhrase);
									*currentCodeBlockInTree = createCodeBlockDeclareNewBoolVar(*currentCodeBlockInTree, parsablePhraseReferenceName, false);

									setDummyReferenceSetIDforAllEntitiesInPhrase(entityNodesActiveListParsablePhrase, parsablePhrase->sentenceIndex);	//this is required for searchForEquivalentSubnetToIfStatement{}
									GIAentityNode* substanceConceptEntityCompare = logicalConditionOperationObject;	//if statement comparison...
									GIAentityNode* substanceConceptEntityCompareConcept = getPrimaryConceptNodeDefiningInstance(substanceConceptEntityCompare);
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
								if(checkIfPhraseContainsSubstanceWithDefinitionLink(entityNodesActiveListParsablePhrase, parsablePhrase->sentenceIndex, &logicalConditionOperationObject, &definitionEntity))
								{//eg "The dog is an alsation. / If the dog is an alsation, eat the cabbage."
								
									NLCcodeblock* currentCodeBlockAtStartOfparsablePhrase = *currentCodeBlockInTree;
									
									//cout << "logicalConditionOperationObject->isSubstance" << endl;
									string parsablePhraseReferenceName = generateMathTextNLPparsablePhraseReference(currentSentence->sentenceIndex, parsablePhrase);
									*currentCodeBlockInTree = createCodeBlockDeclareNewBoolVar(*currentCodeBlockInTree, parsablePhraseReferenceName, false);
	
									GIAentityNode* parentEntity = getParent(logicalConditionOperationObject, sentenceIndex);
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
									*currentCodeBlockInTree = getLastCodeBlockInLevel(currentCodeBlockAtStartOfparsablePhrase);
								} else
								#endif
								if(!generateCodeBlocksFromMathTextNLPparsablePhrase(currentCodeBlockInTree, entityNodesActiveListParsablePhrase, parsablePhrase->sentenceIndex, currentSentence, parsablePhrase, phraseIndex, caseIndex))
								{
									result = false;
								}
							}
							#ifdef NLC_DEBUG_PREPROCESSOR_MATH
							cout << "finished generateCodeBlocksFromMathTextNLPparsablePhrase{}" << endl;
							#endif
							parsablePhrase = parsablePhrase->next;
							parsablePhraseIter++;
						}
						caseIndex++;
						currentSentence = parsablePhrase;
						sentenceIter = parsablePhraseIter;
					}
					else
					{
						caseIndex++;
						currentSentence = currentSentence->next;
						sentenceIter++;						
					}
				}
				else
				{
					if(currentSentence->next != NULL)
					{
						currentSentence = currentSentence->next;
						sentenceIter++;
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
			cout << "generateCodeBlocksFromMathText{} error: illegal firstNLCsentenceInFullSentence->logicalConditionOperator" << endl;
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

		NLCsentence* parsablePhrase = firstNLCsentenceInFullSentence;
		map<int, vector<GIAentityNode*>*>::iterator parsablePhraseIter = sentenceIterFirstInFullSentence;
		for(int phraseIndex=0; phraseIndex<firstNLCsentenceInFullSentence->mathTextNLPparsablePhraseTotal; phraseIndex++)
		{
			vector<GIAentityNode*>* entityNodesActiveListParsablePhrase = parsablePhraseIter->second;
			if(parsablePhrase->mathTextNLPparsablePhraseIndex != phraseIndex)
			{
				cout << "generateCodeBlocksFromMathText{} error: (currentSentence->mathTextNLPparsablePhraseIndex != i)" << endl;
			}
			if(!generateCodeBlocksFromMathTextNLPparsablePhrase(currentCodeBlockInTree, entityNodesActiveListParsablePhrase, parsablePhrase->sentenceIndex, firstNLCsentenceInFullSentence, parsablePhrase, phraseIndex, 0))
			{
				result = false;
			}
			parsablePhraseIter++;
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
			NLCsentence* nextNLCfullSentenceInList = firstNLCsentenceInFullSentence;
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
				cout << "NLC_USE_PREPROCESSOR generateCodeBlocksPart2logicalConditions{} error: invalid indentation of nextNLCfullSentenceInList, sentenceIndex = " << sentenceIndex << endl;
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
		
		#ifdef NLC_USE_MATH_OBJECTS
		#ifndef NLC_MATH_OBJECTS_TEST_NULL_POINTER_MAINTAIN_CONTEXT
		if(firstNLCsentenceInFullSentence->mathTextIdentifiesMathValue)
		{
			*currentCodeBlockInTree = getLastCodeBlockInLevel(currentCodeBlockInTreeAtBaseLevel);
		}
		#endif
		#endif
		
	#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
	}
	#endif
	
	#ifdef NLC_DEBUG_PREPROCESSOR_MATH
	cout << "finished generateCodeBlocksFromMathText{}" << endl;
	#endif
	
	return result;
}	

bool generateCodeBlocksFromMathTextNLPparsablePhrase(NLCcodeblock** currentCodeBlockInTree, vector<GIAentityNode*>* entityNodesActiveListComplete, int sentenceIndex, NLCsentence* currentFullSentence, NLCsentence* parsablePhrase, int phraseIndex, int caseIndex)
{
	bool foundParsablePhrase = false;
	
	#ifdef NLC_DEBUG_PREPROCESSOR_MATH
	cout << "generateCodeBlocksFromMathTextNLPparsablePhrase{} part 1 - for both logical conditions and non-logical conditions" << endl;
	#endif
	
	//for NLP parsable phrase;
	//eg1 "the number of chickens" in "if(the number of chickens > the number of apples...)"
	//eg2 "the number of red dogs" in "X = Y * (the number of red dogs) + the number of blue birds near the mountain"
	NLCcodeblock* currentCodeBlockAtStartOfparsablePhrase = *currentCodeBlockInTree;
	string parsablePhraseReferenceName = generateMathTextNLPparsablePhraseReference(currentFullSentence->sentenceIndex, parsablePhrase);	//parsablePhraseGenerateNumberOfElementCounterName
	*currentCodeBlockInTree = createCodeBlockDeclareNewIntVar(*currentCodeBlockInTree, parsablePhraseReferenceName, 0);	//?this will need to be changed to createCodeBlockDeclareNewIntArray in the future to support multiple cases (ie if, else if, else)
		
	//if !NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE, currently only accept entities with $qVar defined, eg "Number of red dogs". prep_of(number-4, dogs-7) [NLP] / _quantity(dog[8], _$qVar[1]) [GIA]
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode* entity = (*entityIter);
		if(checkSentenceIndexParsingCodeBlocks(entity, sentenceIndex, false))
		{
			if(readParsablePhraseEntryEntityChecks(entity))
			{//redundant	
				#ifdef NLC_PREPROCESSOR_MATH_OLD_NUMBER_OF_IMPLEMENTATION_USING_QVARS
				if(entity->isQuery)
				#else
				if(entity->isNumberOf)
				#endif
				{
					#ifdef NLC_DEBUG
					//cout << "generateCodeBlocksFromMathTextNLPparsablePhrase{}: sentenceIndex = " << sentenceIndex << endl;
					//cout << "generateCodeBlocksFromMathTextNLPparsablePhrase{}: " << entity->entityName << ", entity->sentenceIndexTemp = " << entity->sentenceIndexTemp << endl;
					#endif
					
					if(foundParsablePhrase)
					{
						cout << "generateCodeBlocksFromMathTextNLPparsablePhrase{} error: more than one parsable phrase primary entity found" << endl;
					}
					foundParsablePhrase = true;

					#ifdef NLC_DEBUG_PREPROCESSOR_MATH
					cout << "generateCodeBlocksFromMathTextNLPparsablePhrase{}: found 'number of' designation, entity: " << entity->entityName << endl;
					#endif
					NLCgenerateContextBlocksVariables generateContextBlocksVariables;
					#ifdef NLC_LOGICAL_CONDITION_OPERATIONS_SUPPORT_INDEFINITE_LOGICAL_CONDITION_OBJECTS
					#ifdef NLC_GENERATE_TYPE_LISTS
					//number of statements must be expressed using definite variables, but they will not be advanced referenced by GIA (and so must be located in the typeList)
						//"the number of x" will have already been declared, but is not advanced referenced, so much search the typeList
					entity->grammaticalDefiniteTemp = false;	//this triggers generateContextBlocks() to execute createCodeBlockForOrInPropertyList() on parent rather than createCodeBlockForOrInLocalList()					
					if(!assumedToAlreadyHaveBeenDeclared(entity))	
					{
						*currentCodeBlockInTree = createCodeBlockForPropertyTypeClass(*currentCodeBlockInTree, entity);	//eg "If a house is green, do this", an instanceList (OLD: localList) for "a house" is assumed to have already been declared, one of which may be green, so search all house instanceLists within house typeList...
						//if at least one instanceList of type currentLogicalConditionObject has not previously been declared, then the code will result in a compilation error
						//if at least one instanceList of type currentLogicalConditionObject has previously been declared, but does not have the required properties (eg green), then the code will compile but the if statement will fail
					}
					#else
					if(!assumedToAlreadyHaveBeenDeclared(entity))	
					{
						//entity->grammaticalDefiniteTemp = true;		//removed 1j15a, readded 1j15c, removed 1n22b
						entity->NLClocalListVariableHasBeenInitialised = true;		//added 1n22b	
					}	
					#endif
					#endif
					if(!getParentAndGenerateContextBlocks(currentCodeBlockInTree, entity, sentenceIndex, &generateContextBlocksVariables))
					{
						#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
						cout << "generateCodeBlocksFromMathTextNLPparsablePhrase{} error: !getParentAndGenerateContextBlocks: " << entity->entityName << endl;
						#endif
					}
					#ifdef NLC_GENERATE_TYPE_LISTS
					entity->grammaticalDefiniteTemp = true;
					#endif

					*currentCodeBlockInTree = createCodeBlockIncrementIntVar(*currentCodeBlockInTree, parsablePhraseReferenceName);

					*currentCodeBlockInTree = getLastCodeBlockInLevel(currentCodeBlockAtStartOfparsablePhrase);				
				}
			}
		}
	}	
	if(!foundParsablePhrase)
	{
		#ifndef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
		cout << "generateCodeBlocksFromMathTextNLPparsablePhrase{} error: !foundParsablePhrase" << endl;		
		#endif
		*currentCodeBlockInTree = clearCodeBlock(currentCodeBlockAtStartOfparsablePhrase);	//NB "*currentCodeBlockInTree = currentCodeBlockAtStartOfparsablePhrase"; redundant
	
		if(currentFullSentence->hasLogicalConditionOperator)	//CHECKTHIS; is NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE required for non-logical condition mathText?
		{
			#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE

			#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
			cout << "generateCodeBlocksFromMathTextNLPparsablePhrase() part 2A - for logical conditions only" << endl;
			#endif
			
			//for NLP parsable phrase;
			//eg "the red chicken is next to the house" in "if(the red chicken is next to the house && the blue box has an apple)"

			#ifdef NLC_PREPROCESSOR_MATH_USE_LOGICAL_CONDITION_OPERATIONS_ADVANCED_BACKWARDS_COMPATIBLE_VARIABLE_NAMES
			parsablePhraseReferenceName = generateLogicalConditionConjunctionBooleanName(currentFullSentence->indentation, caseIndex, phraseIndex, NLC_LOGICAL_CONDITION_OPERATIONS_IF);
			#else
			*currentCodeBlockInTree = createCodeBlockDeclareNewBoolVar(*currentCodeBlockInTree, parsablePhraseReferenceName, false);	//?this will need to be changed to createCodeBlockDeclareNewBoolArray in the future to support multiple cases (ie if, else if, else)
			#endif
		
			foundParsablePhrase = false;
			for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
			{
				GIAentityNode* entity = (*entityIter);
				if(checkSentenceIndexParsingCodeBlocks(entity, sentenceIndex, false))
				{
					if(readParsablePhraseEntryEntityChecks(entity))
					{//required			
						#ifdef NLC_PREPROCESSOR_MATH_OLD_NUMBER_OF_IMPLEMENTATION_USING_QVARS
						if(entity->isQuery)
						#else
						if(entity->isNumberOf)
						#endif
						{
							#ifdef NLC_DEBUG
							//cout << "generateCodeBlocksFromMathTextNLPparsablePhrase{} error: entity->isNumberOf && !(entity->NLCcontextGenerated): part 1 must have failed" << endl;
							#endif
						}
						else
						{		
							if(!foundParsablePhrase)
							{
								#ifdef NLC_DEBUG_PREPROCESSOR_MATH
								cout << "generateCodeBlocksFromMathTextNLPparsablePhrase{}: found entity: " << entity->entityName << endl;
								#endif

								NLCcodeblock* NLCcodeBlockBeforeGenerateContext = *currentCodeBlockInTree; 
								
								GIAentityNode* parentEntity = getParent(entity, sentenceIndex);
								
								#ifdef NLC_LOGICAL_CONDITION_OPERATIONS_SUPPORT_INDEFINITE_LOGICAL_CONDITION_OBJECTS
								//if/while statements can be expressed using either definite or indefinate variables, but if they indefinite they will not be advanced referenced by GIA (and so must be located in the typeList)
								bool parentEntityWasNotDeclared = false;
								if(!assumedToAlreadyHaveBeenDeclared(parentEntity))
								{
									parentEntityWasNotDeclared = true;
									#ifdef NLC_GENERATE_TYPE_LISTS
									//1i implementation
									*currentCodeBlockInTree = createCodeBlockForPropertyTypeClass(*currentCodeBlockInTree, parentEntity);	//eg "If a house is green, do this", an instanceList (OLD: localList) for "a house" is assumed to have already been declared, one of which may be green, so search all house instanceLists within house typeList...
									//if at least one instanceList of type currentLogicalConditionObject has not previously been declared, then the code will result in a compilation error
									//if at least one instanceList of type currentLogicalConditionObject has previously been declared, but does not have the required properties (eg green), then the code will compile but the if statement will fail
									#else
									//entity->grammaticalDefiniteTemp = true;		//removed 1j15a
									parentEntity->NLClocalListVariableHasBeenInitialised = true;		//added 1n22b
									#endif
								}
								#endif
								//*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("generateCodeBlocksFromMathTextNLPparsablePhrase{}:  1 generateContextBlocks: ") + parentEntity->entityName);
								//NB logicalConditionOperator != NLC_LOGICAL_CONDITION_OPERATIONS_FOR (if so generateCodeBlocksFromMathTextNLPparsablePhraseLogicalConditionFor is executed instead)
								//therefore logicalConditionOperator == NLC_LOGICAL_CONDITION_OPERATIONS_IF/NLC_LOGICAL_CONDITION_OPERATIONS_ELSE_IF/NLC_LOGICAL_CONDITION_OPERATIONS_ELSE_WHILE

								GIAentityNode* childEntity = NULL;
								NLCgenerateContextBlocksVariables generateContextBlocksVariables;
								bool contextFound = parseParsablePhraseParent(currentCodeBlockInTree, sentenceIndex, parentEntity, &generateContextBlocksVariables, &childEntity, currentFullSentence->logicalConditionOperator);

								#ifdef NLC_LOGICAL_CONDITION_OPERATIONS_SUPPORT_INDEFINITE_LOGICAL_CONDITION_OBJECTS
								if(parentEntityWasNotDeclared)
								{
									if(childEntity != parentEntity)
									{
										bool foundChildEntity = true;
										cout << "generateCodeBlocksFromMathTextNLPparsablePhrase{} error: !assumedToAlreadyHaveBeenDeclared(parentEntity) && foundChildEntity" << endl;
									}
								}
								#endif

								if(!contextFound)
								{
									#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
									cout << "generateCodeBlocksFromMathTextNLPparsablePhrase{} error: !getParentAndGenerateContextBlocks: sentenceIndex = " << sentenceIndex << endl;
									#endif
									
									*currentCodeBlockInTree = clearCodeBlock(NLCcodeBlockBeforeGenerateContext);							
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
											//#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
											cout << "negativeDetectedInContextBlocks detected; inserting NLC_PREPROCESSOR_MATH_OPERATOR_NEGATIVE_CHAR into mathText logical condition" << endl;
											//#endif
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
			if(!foundParsablePhrase)
			{
				cout << "generateCodeBlocksFromMathTextNLPparsablePhrase{} error: !foundParsablePhrase" << endl;		
				*currentCodeBlockInTree = clearCodeBlock(currentCodeBlockAtStartOfparsablePhrase);	//NB "*currentCodeBlockInTree = currentCodeBlockAtStartOfparsablePhrase;" redundant
			}
			#endif		
		}
		else
		{
			#ifdef NLC_USE_MATH_OBJECTS
			
			#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
			cout << "generateCodeBlocksFromMathTextNLPparsablePhrase() part 2B - for non logical conditions only" << endl;
			#endif
			
			/*for NLP parsable phrase;
			eg1 "The value" in "The value = 5" 
			eg2 "The value" in "The value = 5.5" 
			eg3 "the value" in "X = 74 + the value"
			eg4 "the dog's value" in "The dog's value = 4 + the number of chickens"
			eg5 "The brown dog = X"
			eg6 "A brown dog = X"
			eg7 "Y = the value + the number of chickens"
			algorithm: find parent entity in sentence entities (do not parse inverseConditionTwoWay conditions, only parse property parent if rcmodIndicatesSameReferenceSet [otherwise it indicates possessive relation eg Tom's boat]
				//FUTURE NLC - reject all sentences with !sameReferenceSet connections [as these cannot be combined with mathtext]	
			*/
			
			*currentCodeBlockInTree = createCodeBlockDeclareNewDecimalPointerVar(*currentCodeBlockInTree, parsablePhraseReferenceName);	//double* thedogsvalue = NULL;
		
			foundParsablePhrase = false;
			for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
			{
				GIAentityNode* entity = (*entityIter);
				if(checkSentenceIndexParsingCodeBlocks(entity, sentenceIndex, false))
				{
					if(readParsablePhraseEntryEntityChecks(entity))
					{//required			
								
						if(!foundParsablePhrase)
						{
							#ifdef NLC_DEBUG_PREPROCESSOR_MATH
							cout << "generateCodeBlocksFromMathTextNLPparsablePhrase{}: found entity: " << entity->entityName << endl;
							#endif

							NLCcodeblock* NLCcodeBlockBeforeGenerateContext = *currentCodeBlockInTree; 

							GIAentityNode* parentEntity = getParent(entity, sentenceIndex);		//find both definite and indefinite parents; eg The dog's value = X / A dog's value = X 
							
							if(!assumedToAlreadyHaveBeenDeclared(parentEntity))
							{
								//eg A dog's value = X.
								if(generateParentInitialisationCodeBlockWithChecks(currentCodeBlockInTree, parentEntity, sentenceIndex, false, false))
								{
									//cout << "generateParentInitialisationCodeBlockWithChecks passed" << endl;
								}					
							}
							else
							{
								//eg The dog's value = X.
							}
							
							GIAentityNode* childEntity = NULL;
							NLCgenerateContextBlocksVariables generateContextBlocksVariables;
							parseParsablePhraseParent(currentCodeBlockInTree, sentenceIndex, parentEntity, &generateContextBlocksVariables, &childEntity, currentFullSentence->logicalConditionOperator);

							*currentCodeBlockInTree = createCodeBlockSetDecimalPointerToEntityMathValue(*currentCodeBlockInTree, parsablePhraseReferenceName, childEntity);		//*thedogsvalue = childEntity->value;

							foundParsablePhrase = true;	
							currentFullSentence->mathTextIdentifiesMathValue = true;
							//parsablePhrase->mathTextNLPparsablePhraseIdentifiesMathValue = true;
							string parsablePhraseReferenceMathValue = generateCodeEntityMathValueText(parsablePhraseReferenceName, NLC_PROGRAMMING_LANGUAGE_DEFAULT);
							bool foundParsablePhraseInMathText = false;
							currentFullSentence->mathText = replaceAllOccurancesOfString(&(currentFullSentence->mathText), parsablePhraseReferenceName, parsablePhraseReferenceMathValue, &foundParsablePhraseInMathText);	//replace "thedogsvalue" with "thedogsvalue->value"
							if(!foundParsablePhraseInMathText)
							{
								cout << "generateCodeBlocksFromMathTextNLPparsablePhrase{} error: !foundParsablePhraseInMathText" << endl;
							}

							*currentCodeBlockInTree = getLastCodeBlockInLevel(currentCodeBlockAtStartOfparsablePhrase);
						}
					}
				}
			}
			if(foundParsablePhrase)
			{
				#ifdef NLC_MATH_OBJECTS_TEST_NULL_POINTER_MAINTAIN_CONTEXT
				*currentCodeBlockInTree = createCodeBlockTestDecimalPointerValue(*currentCodeBlockInTree, parsablePhraseReferenceName);			 //if(thedogsvalue == NULL) { cout << "error" << endl;}
				#else
				*currentCodeBlockInTree = createCodeBlockCheckDecimalPointerValue(*currentCodeBlockInTree, parsablePhraseReferenceName);		 //if(thedogsvalue != NULL)
				#endif
			}
			else
			{
				cout << "generateCodeBlocksFromMathTextNLPparsablePhrase{} error: !foundParsablePhrase" << endl;		
				*currentCodeBlockInTree = clearCodeBlock(currentCodeBlockAtStartOfparsablePhrase);
			}
			#endif
		}
	}
	
	return foundParsablePhrase;
}

bool generateCodeBlocksFromMathTextNLPparsablePhraseLogicalConditionFor(NLCcodeblock** currentCodeBlockInTree, vector<GIAentityNode*>* entityNodesActiveListComplete, int sentenceIndex, NLCsentence* currentFullSentence, NLCsentence* parsablePhrase, int phraseIndex, NLCcodeblock** currentCodeBlockInTreeAtBaseLevel, NLCsentence* firstNLCsentenceInFullSentence)
{
	bool foundParsablePhrase = false;
	
	#ifdef NLC_DEBUG_PREPROCESSOR_MATH
	cout << "generateCodeBlocksFromMathTextNLPparsablePhraseLogicalConditionFor{}" << endl;
	#endif
	//generate NLP parsable phrase eg "all apples in the cart" in "for(all the apples in the cart)"
	
	if((currentFullSentence->hasLogicalConditionOperator) && (currentFullSentence->logicalConditionOperator == NLC_LOGICAL_CONDITION_OPERATIONS_FOR))
	{
		foundParsablePhrase = false;
		for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
		{
			GIAentityNode* entity = (*entityIter);
			if(checkSentenceIndexParsingCodeBlocks(entity, sentenceIndex, false))
			{
				if(readParsablePhraseEntryEntityChecks(entity))
				{//required
					if(!foundParsablePhrase)
					{						
						bool foundDefiniteParentEntity = false;
						bool parseConditionParents = NLC_PARSE_CONDITION_PARENTS_DEFAULT_VALUE;
						bool checkIsDefinite = true;
						GIAentityNode* parentEntity = getSameReferenceSetUniqueParent(entity, sentenceIndex, NULL, &foundDefiniteParentEntity, parseConditionParents, checkIsDefinite);	//GIAentityNode* parentEntity = getParent(entity, sentenceIndex);
						
						/*//for statements must be expressed using definite variables, and they will be advanced referenced by GIA (ie "for all the chickens...", not "for a chicken..")
						if(!assumedToAlreadyHaveBeenDeclared(entity))
						{
						     * currentCodeBlockInTree = createCodeBlockForPropertyTypeClass(*currentCodeBlockInTree, entity);   //eg "If a house is green, do this", an instanceList (OLD: localList) for "a house" is assumed to have already been declared, one of which may be green, so search all house instanceLists within house typeList...
						      //if at least one instanceList of type currentLogicalConditionObject has not previously been declared, then the code will result in a compilation error
						      //if at least one instanceList of type currentLogicalConditionObject has previously been declared, but does not have the required properties (eg green), then the code will compile but the if statement will fail
						}
						*/
						
						GIAentityNode* childEntity = NULL;
						NLCgenerateContextBlocksVariables generateContextBlocksVariables;
						parseParsablePhraseParent(currentCodeBlockInTree, sentenceIndex, parentEntity, &generateContextBlocksVariables, &childEntity, currentFullSentence->logicalConditionOperator);

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
	return foundParsablePhrase;
}

bool parseParsablePhraseParent(NLCcodeblock** currentCodeBlockInTree, int sentenceIndex, GIAentityNode* parentEntity, NLCgenerateContextBlocksVariables* generateContextBlocksVariables, GIAentityNode** childEntity, int logicalConditionOperator)
{
	bool foundChildEntity = false;
	*childEntity = getSameReferenceSetSubstanceNonQualityChild(parentEntity, sentenceIndex, &foundChildEntity);
	
	generateContextBlocksVariables->onlyGenerateContextBlocksIfConnectionsParsedForNLCorSameReferenceSet = true;
	if(logicalConditionOperator == NLC_LOGICAL_CONDITION_OPERATIONS_FOR)
	{
		#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
		generateContextBlocksVariables->setCodeBlockInTreeAtBaseLevel = true;
		#endif
	}
	
	//cout << "foundChildEntity = " << foundChildEntity << endl;
	//cout << "childEntity = " << (*childEntity)->entityName << endl;
	
	bool contextFound = false;
	bool generatedContextForChild = false;
	if(foundChildEntity)
	{
		if(generateContextBlocksForParentEntity(currentCodeBlockInTree, *childEntity, parentEntity, sentenceIndex, generateContextBlocksVariables))
		{
			generatedContextForChild = true;
			contextFound = true;	//this is required for cases in which the entity (ball) has no children, eg "Jack's ball"
		}
		else
		{
			cout << "generateCodeBlocksFromMathTextNLPparsablePhraseLogicalConditionFor{}: generateContextBlocksForParentEntity{} error: !generatedContextForChild" << endl;
		}
	}
	
	if(logicalConditionOperator == NLC_LOGICAL_CONDITION_OPERATIONS_FOR)
	{
		#ifdef NLC_TRANSLATOR_LOGICAL_CONDITIONS_FOR_LOOP_IGNORE_SAME_REFERENCE_SET_COMPENSATE_FOR_NLP_FAILURE_TO_CREATE_RCMOD
		generateContextBlocksVariables->onlyGenerateContextBlocksIfConnectionsParsedForNLCorSameReferenceSet = false;
		#endif
	}
	else if(logicalConditionOperator != INT_DEFAULT_VALUE)
	{
		generateContextBlocksVariables->onlyGenerateContextBlocksIfConnectionsParsedForNLCorSameReferenceSet = false;
		#ifdef NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY
		generateContextBlocksVariables->testNumerosity = true;
		#endif	
	}
	
	if(generateContextBlocks(currentCodeBlockInTree, *childEntity, sentenceIndex, generateContextBlocksVariables, generatedContextForChild, NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION))
	{
		contextFound = true;
	}
		
	return contextFound;
}
				
#endif

#ifdef NLC_PREPROCESSOR_MATH_REPLACE_NUMERICAL_VARIABLES_NAMES_FOR_NLP
bool findAndSetDummyNumericalValueForReplacement(vector<GIAentityNode*>* entityNodesActiveListComplete, int sentenceIndex, int dummyNumericalValue, string numericalVariableName)
{
	bool result = true;
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode* entity = (*entityIter);
		if(checkSentenceIndexParsingCodeBlocks(entity, sentenceIndex, false))
		{
			if(entity->quantityNumber == dummyNumericalValue)
			{
				#ifdef NLC_DEBUG
				//cout << "findAndSetDummyNumericalValueForReplacement{}: " << endl;
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
bool checkIfPhraseContainsAction(vector<GIAentityNode*>* entityNodesActiveListComplete, int sentenceIndex, GIAentityNode** logicalConditionOperationObject)
{
	bool phraseContainsAction = false;
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode* entity = (*entityIter);
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
bool checkIfPhraseContainsSubstanceConceptWithDefinitionLink(vector<GIAentityNode*>* entityNodesActiveListComplete, int sentenceIndex, GIAentityNode** logicalConditionOperationObject)
{
	bool phraseContainsSubstanceConceptWithDefinitionLink = false;
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode* entity = (*entityIter);
		if(checkSentenceIndexParsingCodeBlocks(entity, sentenceIndex, false))
		{		
			if(entity->isSubstanceConcept)
			{
				for(vector<GIAentityConnection*>::iterator iter = entity->entityNodeDefinitionList->begin(); iter < entity->entityNodeDefinitionList->end(); iter++)
				{
					GIAentityConnection* definitionConnection = *iter;
					GIAentityNode* definitionEntityTemp =  definitionConnection->entity;
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
bool checkIfPhraseContainsSubstanceWithDefinitionLink(vector<GIAentityNode*>* entityNodesActiveListComplete, int sentenceIndex, GIAentityNode** logicalConditionOperationObject, GIAentityNode** definitionEntity)
{
	bool phraseContainsSubstanceWithDefinitionLink = false;
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode* entity = (*entityIter);
		if(checkSentenceIndexParsingCodeBlocks(entity, sentenceIndex, false))
		{		
			if((entity->isSubstance) && (!entity->isSubstanceConcept))
			{
				for(vector<GIAentityConnection*>::iterator iter = entity->entityNodeDefinitionList->begin(); iter < entity->entityNodeDefinitionList->end(); iter++)
				{
					GIAentityConnection* definitionConnection = *iter;
					GIAentityNode* definitionEntityTemp = definitionConnection->entity;
					if(definitionConnection->sentenceIndexTemp == sentenceIndex)
					{
						if(!(definitionConnection->sameReferenceSet))
						{
							if(!isDefiniteEntity(definitionEntityTemp))
							{
								bool foundDefiniteParentOfEntity = false;
								bool parseConditionParents = NLC_PARSE_CONDITION_PARENTS_DEFAULT_VALUE;
								bool checkIsDefinite = true;
								GIAentityNode* parentEntity = getSameReferenceSetUniqueParent(entity, sentenceIndex, NULL, &foundDefiniteParentOfEntity, parseConditionParents, checkIsDefinite);
								if(isDefiniteEntity(entity) || foundDefiniteParentOfEntity)
								{
									if(entity->entityName != definitionEntityTemp->entityName)
									{//ignore substanceConcept definitions for for entities of same name
										phraseContainsSubstanceWithDefinitionLink = true;
										*logicalConditionOperationObject = entity;
										*definitionEntity = definitionEntityTemp;
										//cout << "checkIfPhraseContainsSubstanceWithDefinitionLink: = " << entity->entityName << endl;
										//cout << "entity = " << entity->entityName << endl;
										//cout << "definitionEntity = " << definitionEntityTemp->entityName << endl;
									}
								}
								else
								{
									cout << "checkIfPhraseContainsSubstanceWithDefinitionLink() warning: !(isDefiniteEntity(entity) || foundDefiniteParentOfEntity))" << endl;
								}
							}
							else
							{
								cout << "checkIfPhraseContainsSubstanceWithDefinitionLink() warning: isDefiniteEntity(definitionEntityTemp))" << endl;
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


void setDummyReferenceSetIDforAllEntitiesInPhrase(vector<GIAentityNode*>* entityNodesActiveListComplete, int sentenceIndex)
{
	//cout << "setDummyReferenceSetIDforAllEntitiesInPhrase: " << endl;
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode* entity = (*entityIter);
		if(checkSentenceIndexParsingCodeBlocks(entity, sentenceIndex, false))
		{			
			entity->referenceSetID = NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_BASED_ON_ACTIONS_OR_CONCEPTS_DUMMY_REFERENCE_SET_ID;
			#ifdef NLC_DEBUG
			//cout << "setDummyReferenceSetIDforAllEntitiesInPhrase{}:" << endl;
			//cout << "entity = " << entity->entityName << endl;
			//cout << "entity->isConcept = " << entity->isConcept << endl;
			#endif
		}
	}
}

bool readParsablePhraseEntryEntityChecks(GIAentityNode* entity)
{
	bool result = false;
	if(!(entity->isConcept) && !(entity->isCondition))
	{
		result = true;
	}
	return result;
}

