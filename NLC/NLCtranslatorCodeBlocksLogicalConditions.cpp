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
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2016 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 1u1c 24-September-2016
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/


#include "NLCtranslatorCodeBlocksLogicalConditions.h"
#include "NLCtranslatorCodeBlocksLogicalConditionsAdvanced.h"
#include "NLCtranslatorCodeBlocksOperations.h"
#include "GIAtranslatorOperations.h"	//required for getPrimaryNetworkIndexNodeDefiningInstance{}
#include "NLCprintDefs.h"	//required for NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION
#include "NLCpreprocessorMath.h"	//required for findCharacterAtIndexOrAfterSpace{}

#ifdef NLC_TRANSLATOR_LOGICAL_CONDITIONS_FOR_LOOP_ADD_ENTITY_TO_NEW_CONTEXT_LIST
GIAentityNode* logicalConditionForLoopPrimaryEntityTemp;
#endif

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
									GIAentityNode* actionEntityCompareNetworkIndex = getPrimaryNetworkIndexNodeDefiningInstance(actionEntityCompare);
									if(searchForEquivalentSubnetToIfStatement(actionEntityCompareNetworkIndex, logicalConditionOperationObject, false))
									{
										*currentCodeBlockInTree = createCodeBlockSetBoolVar(*currentCodeBlockInTree, parsablePhraseReferenceName, true);
										#ifdef NLC_DEBUG
										//cout << "NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_BASED_ON_ACTIONS_BASIC: passed logical condition" << endl;
										#endif
									}
								} else
								#endif
								#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_BASED_ON_CONCEPTS
								#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_BASED_ON_CONCEPTS_BASIC
								if(checkIfPhraseContainsConceptWithDefinitionLink(entityNodesActiveListParsablePhrase, parsablePhrase->sentenceIndex, &logicalConditionOperationObject))
								#else
								if(checkIfPhraseContainsConcept(entityNodesActiveListParsablePhrase, parsablePhrase->sentenceIndex, &logicalConditionOperationObject))
								#endif
								{//eg "Red dogs are pies. / If red dogs are pies, eat the cabbage."

									//logical operations on concepts are performed by NLC (code is not generated for them by NLC as they are not performed at runtime) - eg If red dogs are/[!NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_BASED_ON_CONCEPTS_BASIC:]have pies, eat the cabbage.	[as opposed to: "if the red dog is the/a pie, eat the cabbage"]
									//verify the truth of the if statement now (if the statement is false, disable all classStructure formation based on condition subject subset)

									#ifdef NLC_DEBUG
									cout << "logicalConditionOperationObject->isConcept" << endl;
									#endif
									string parsablePhraseReferenceName = generateMathTextNLPparsablePhraseReference(currentSentence->sentenceIndex, parsablePhrase);
									*currentCodeBlockInTree = createCodeBlockDeclareNewBoolVar(*currentCodeBlockInTree, parsablePhraseReferenceName, false);

									setDummyReferenceSetIDforAllEntitiesInPhrase(entityNodesActiveListParsablePhrase, parsablePhrase->sentenceIndex);	//this is required for searchForEquivalentSubnetToIfStatement{}
									GIAentityNode* conceptEntityCompare = logicalConditionOperationObject;	//if statement comparison...
									GIAentityNode* conceptEntityCompareNetworkIndex = getPrimaryNetworkIndexNodeDefiningInstance(conceptEntityCompare);
									if(searchForEquivalentSubnetToIfStatement(conceptEntityCompareNetworkIndex, logicalConditionOperationObject, true))	//searches for previous "red dogs are pies"
									{
										*currentCodeBlockInTree = createCodeBlockSetBoolVar(*currentCodeBlockInTree, parsablePhraseReferenceName, true);
										#ifdef NLC_DEBUG
										//cout << "NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_BASED_ON_CONCEPTS: passed logical condition" << endl;
										#endif
									}

								} else
								#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_BASED_ON_CONCEPTS_BASIC_REDEFINITIONS
								if(checkIfPhraseContainsSubstanceWithDefinitionLink(entityNodesActiveListParsablePhrase, parsablePhrase->sentenceIndex, &logicalConditionOperationObject, &definitionEntity))
								{//eg "The dog is an alsation. / If the dog is an alsation, eat the cabbage."

									NLCcodeblock* currentCodeBlockAtStartOfparsablePhrase = *currentCodeBlockInTree;

									#ifdef NLC_DEBUG
									//cout << "logicalConditionOperationObject->isSubstance" << endl;
									#endif
									string parsablePhraseReferenceName = generateMathTextNLPparsablePhraseReference(currentSentence->sentenceIndex, parsablePhrase);
									*currentCodeBlockInTree = createCodeBlockDeclareNewBoolVar(*currentCodeBlockInTree, parsablePhraseReferenceName, false);

									GIAentityNode* parentEntity = getParent(logicalConditionOperationObject, sentenceIndex);
									NLCgenerateContextBlocksVariables generateContextBlocksVariables;
									generateContextBlocksVariables.searchConceptsForChildren = false;	//added 1n5g (only check the explicit variable for definition)
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

	#ifdef NLC_USE_MATH_OBJECTS_ADVANCED_USE_UNIQUE_OPERATORS
	int progLang = getProgLang();	//CHECKTHIS - note this is an unusual implementation
	firstNLCsentenceInFullSentence->mathText = replaceAllOccurancesOfString(&(firstNLCsentenceInFullSentence->mathText), NLC_PREPROCESSOR_MATH_OPERATOR_STRING_EQUALS_TEST_WITH_PADDING, progLangStringEqualsTest[progLang]);
	firstNLCsentenceInFullSentence->mathText = replaceAllOccurancesOfString(&(firstNLCsentenceInFullSentence->mathText), NLC_PREPROCESSOR_MATH_OPERATOR_STRING_ADD_WITH_PADDING, progLangStringAdd[progLang]);
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
		#ifdef NLC_TRANSLATOR_LOGICAL_CONDITIONS_FOR_LOOP_ADD_ENTITY_TO_NEW_CONTEXT_LIST
		if(firstNLCsentenceInFullSentence->logicalConditionOperator == NLC_LOGICAL_CONDITION_OPERATIONS_FOR)
		{
			if(result)	//verify that logicalConditionForLoopPrimaryEntityTemp has been set by generateCodeBlocksFromMathTextNLPparsablePhraseLogicalConditionFor (ie foundParsablePhrase)
			{
				*currentCodeBlockInTree = createCodeBlocksAddEntityToContextLevelListExecuteFunction(*currentCodeBlockInTree, getCurrentLogicalConditionLevel()+1, logicalConditionForLoopPrimaryEntityTemp, sentenceIndex);
			}
		}
		#endif
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
				//NB if(nextNLCfullSentenceInList->indentation < firstNLCsentenceInFullSentence->indentation) will be processed later by generateCodeBlocks{}
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

bool generateCodeBlocksFromMathTextNLPparsablePhrase(NLCcodeblock** currentCodeBlockInTree, vector<GIAentityNode*>* entityNodesActiveListParsablePhrase, int sentenceIndex, NLCsentence* currentFullSentence, NLCsentence* parsablePhrase, int phraseIndex, int caseIndex)
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
	#ifdef NLC_GENERATE_UNIQUE_CONTEXT_BLOCK_FOR_EACH_SENTENCE_LOGICAL_CONDITIONS_PARSABLE_PHRASES
	NLCcodeblock* firstCodeBlockInPhrase = *currentCodeBlockInTree;
	*currentCodeBlockInTree = createCodeBlocksCreateContextBlock(*currentCodeBlockInTree);
	#endif

	//if !NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE, currently only accept entities with $qVar defined, eg "Number of red dogs". prep_of(number-4, dogs-7) [NLP] / _quantity(dog[8], _$qVar[1]) [GIA]
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListParsablePhrase->begin(); entityIter != entityNodesActiveListParsablePhrase->end(); entityIter++)
	{
		GIAentityNode* entity = (*entityIter);
		if(checkSentenceIndexParsingCodeBlocks(entity, sentenceIndex, false))
		{
			if(readParsablePhraseEntryEntityChecks(entity))
			{//redundant
				if(isNumberOf(entity))
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
					entity->grammaticalDefiniteTemp = false;	//this triggers generateContextBlocks{} to execute createCodeBlockForOrInPropertyList{} on parent rather than createCodeBlockForOrInLocalList{}
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
		*currentCodeBlockInTree = clearCodeBlock(currentCodeBlockAtStartOfparsablePhrase);

		#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
		#ifdef NLC_USE_MATH_OBJECTS

		#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
		cout << "generateCodeBlocksFromMathTextNLPparsablePhrase{} part 2" << endl;
		#endif

		/*for NLP parsable phrase;
		hasLogicalConditionOperator:
		//eg1 "the red chicken is next to the house" in "if(the red chicken is next to the house && the blue box has an apple)"

		!hasLogicalConditionOperator:
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

		int mathObjectVariableType = getMathObjectVariableType(entityNodesActiveListParsablePhrase, sentenceIndex, currentFullSentence, parsablePhrase);
		if(mathObjectVariableType == NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_BOOLEAN_STATEMENT)
		{
			#ifdef NLC_PREPROCESSOR_MATH_USE_LOGICAL_CONDITION_OPERATIONS_ADVANCED_BACKWARDS_COMPATIBLE_VARIABLE_NAMES
			parsablePhraseReferenceName = generateLogicalConditionConjunctionBooleanName(currentFullSentence->indentation, caseIndex, phraseIndex, NLC_LOGICAL_CONDITION_OPERATIONS_IF);
			#else
			*currentCodeBlockInTree = createCodeBlockDeclareNewBoolVar(*currentCodeBlockInTree, parsablePhraseReferenceName, false);	//eg bool thedogistall = false;
			#endif
		}
		else if((mathObjectVariableType == NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_NUMERICAL) || (mathObjectVariableType == NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_STRING) || (mathObjectVariableType == NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_BOOLEAN))
		{
			if(mathObjectVariableType == NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_NUMERICAL)
			{
				*currentCodeBlockInTree = createCodeBlockDeclareNewDecimalPointerVar(*currentCodeBlockInTree, parsablePhraseReferenceName);	//eg double* thedogsvalue = NULL;
			}
			#ifdef NLC_USE_MATH_OBJECTS_ADVANCED
			#ifdef NLC_USE_MATH_OBJECTS_STRING
			else if(mathObjectVariableType == NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_STRING)
			{
				*currentCodeBlockInTree = createCodeBlockDeclareNewStringPointerVar(*currentCodeBlockInTree, parsablePhraseReferenceName);	//eg string* thedogsvalue = NULL;
			}
			#endif
			#ifdef NLC_USE_MATH_OBJECTS_BOOLEAN
			else if(mathObjectVariableType == NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_BOOLEAN)
			{
				*currentCodeBlockInTree = createCodeBlockDeclareNewBooleanPointerVar(*currentCodeBlockInTree, parsablePhraseReferenceName);	//eg bool* thedogsvalue = NULL;
			}
			#endif
			#endif
		}
		#ifdef NLC_USE_MATH_OBJECTS_ADVANCED
		else if(mathObjectVariableType == NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_UNKNOWN)
		{
			*currentCodeBlockInTree = createCodeBlockDeclareNewGenericEntityPointerVar(*currentCodeBlockInTree, parsablePhraseReferenceName);	//NLCgenericEntityClass* thedogsvalue = NULL;
		}
		#endif

		#ifdef NLC_GENERATE_UNIQUE_CONTEXT_BLOCK_FOR_EACH_SENTENCE_LOGICAL_CONDITIONS_PARSABLE_PHRASES
		firstCodeBlockInPhrase = *currentCodeBlockInTree;
		*currentCodeBlockInTree = createCodeBlocksCreateContextBlock(*currentCodeBlockInTree);
		#endif

		foundParsablePhrase = false;
		#ifdef NLC_TRANSLATOR_LOGICAL_CONDITIONS_BOOLEAN_STATEMENTS_INTERPRET_SUBJECT_AND_OBJECT_INDEPENDENTLY
		if(mathObjectVariableType == NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_BOOLEAN_STATEMENT)
		{//added 1t2a
			//this is required to parse both the subject and the object of the boolean statement independently
			bool logicalConditionBooleanStatementNegativeDetected = false;

			if(generateCodeBlocksPart3subjectObjectConnections(currentCodeBlockInTree, entityNodesActiveListParsablePhrase, sentenceIndex, true, &logicalConditionBooleanStatementNegativeDetected))
			{
				if(logicalConditionBooleanStatementNegativeDetected)
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

				foundParsablePhrase = true;

				*currentCodeBlockInTree = createCodeBlockSetBoolVar(*currentCodeBlockInTree, parsablePhraseReferenceName, true);		//eg thedogsvalue = true;

				*currentCodeBlockInTree = getLastCodeBlockInLevel(currentCodeBlockAtStartOfparsablePhrase);
			}
		}
		else
		{
		#endif
			for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListParsablePhrase->begin(); entityIter != entityNodesActiveListParsablePhrase->end(); entityIter++)
			{
				GIAentityNode* entity = (*entityIter);
				if(checkSentenceIndexParsingCodeBlocks(entity, sentenceIndex, false))
				{
					if(readParsablePhraseEntryEntityChecks(entity))
					{//required
						if(!isNumberOf(entity))	//CHECKTHIS
						{
							if(!foundParsablePhrase)
							{
								#ifdef NLC_DEBUG_PREPROCESSOR_MATH
								cout << "generateCodeBlocksFromMathTextNLPparsablePhrase{}: found entity: " << entity->entityName << endl;
								#endif

								NLCcodeblock* NLCcodeBlockBeforeGenerateContext = *currentCodeBlockInTree;

								GIAentityNode* parentEntity = getParent(entity, sentenceIndex);		//find both definite and indefinite parents; eg The dog's value = X / A dog's value = X

								//initialise parsing of indefinate entities (set how to intepret these, eg "a house")
								bool parentEntityWasNotDeclared = false;
								if(!assumedToAlreadyHaveBeenDeclared(parentEntity))
								{
									parentEntityWasNotDeclared = true;
									if(currentFullSentence->hasLogicalConditionOperator)
									{
										#ifdef NLC_LOGICAL_CONDITION_OPERATIONS_SUPPORT_INDEFINITE_LOGICAL_CONDITION_OBJECTS
										//if/while statements can be expressed using either definite or indefinate variables, but if they indefinite they will not be advanced referenced by GIA (and so must be located in the typeList)
										#ifdef NLC_GENERATE_TYPE_LISTS
										//1i implementation
										*currentCodeBlockInTree = createCodeBlockForPropertyTypeClass(*currentCodeBlockInTree, parentEntity);	//eg "If a house is green, do this", an instanceList (OLD: localList) for "a house" is assumed to have already been declared, one of which may be green, so search all house instanceLists within house typeList...
										//if at least one instanceList of type currentLogicalConditionObject has not previously been declared, then the code will result in a compilation error
										//if at least one instanceList of type currentLogicalConditionObject has previously been declared, but does not have the required properties (eg green), then the code will compile but the if statement will fail
										#else
										//entity->grammaticalDefiniteTemp = true;		//removed 1j15a
										parentEntity->NLClocalListVariableHasBeenInitialised = true;		//added 1n22b
										#endif
										#endif

										//*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("generateCodeBlocksFromMathTextNLPparsablePhrase{}:  1 generateContextBlocks: ") + parentEntity->entityName);
										//NB logicalConditionOperator != NLC_LOGICAL_CONDITION_OPERATIONS_FOR (if so generateCodeBlocksFromMathTextNLPparsablePhraseLogicalConditionFor is executed instead)
										//therefore logicalConditionOperator == NLC_LOGICAL_CONDITION_OPERATIONS_IF/NLC_LOGICAL_CONDITION_OPERATIONS_ELSE_IF/NLC_LOGICAL_CONDITION_OPERATIONS_ELSE_WHILE
									}
									else
									{
										//isnt this redundant with parseParsablePhraseParent?
										//eg A dog's value = X.
										if(generateParentInitialisationCodeBlockWithChecks(currentCodeBlockInTree, parentEntity, sentenceIndex, false, false))
										{
											#ifdef NLC_DEBUG
											//cout << "generateParentInitialisationCodeBlockWithChecks passed" << endl;
											#endif
										}
									}
								}
								else
								{
									//eg The dog's value = X.
								}

								GIAentityNode* childEntity = NULL;
								NLCgenerateContextBlocksVariables generateContextBlocksVariables;
								bool contextFound = parseParsablePhraseParent(currentCodeBlockInTree, sentenceIndex, parentEntity, &generateContextBlocksVariables, &childEntity, currentFullSentence->logicalConditionOperator);

								#ifdef NLC_LOGICAL_CONDITION_OPERATIONS_SUPPORT_INDEFINITE_LOGICAL_CONDITION_OBJECTS
								if(currentFullSentence->hasLogicalConditionOperator)
								{
									if(parentEntityWasNotDeclared)
									{
										if(childEntity != parentEntity)
										{
											bool foundChildEntity = true;
											cout << "generateCodeBlocksFromMathTextNLPparsablePhrase{} error: !assumedToAlreadyHaveBeenDeclared(parentEntity) && foundChildEntity" << endl;
										}
									}
								}
								#endif

								#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
								cout << "generateCodeBlocksFromMathTextNLPparsablePhrase{} pass: parseParsablePhraseParent: sentenceIndex = " << sentenceIndex << endl;
								#endif

								if(currentFullSentence->hasLogicalConditionOperator)
								{
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
								}


								if(mathObjectVariableType == NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_BOOLEAN_STATEMENT)
								{
									*currentCodeBlockInTree = createCodeBlockSetBoolVar(*currentCodeBlockInTree, parsablePhraseReferenceName, true);		//eg thedogsvalue = true;
								}
								else if((mathObjectVariableType == NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_NUMERICAL) || (mathObjectVariableType == NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_STRING) || (mathObjectVariableType == NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_BOOLEAN))
								{
									if(mathObjectVariableType == NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_NUMERICAL)
									{
										*currentCodeBlockInTree = createCodeBlockSetDecimalPointerToEntityMathNumericalValue(*currentCodeBlockInTree, parsablePhraseReferenceName, childEntity);		//eg thedogsvalue = &(childEntity->numericalValue);
									}
									#ifdef NLC_USE_MATH_OBJECTS_ADVANCED
									#ifdef NLC_USE_MATH_OBJECTS_STRING
									else if(mathObjectVariableType == NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_STRING)
									{
										*currentCodeBlockInTree = createCodeBlockSetStringPointerToEntityMathStringValue(*currentCodeBlockInTree, parsablePhraseReferenceName, childEntity);		//eg thedogsvalue = &(childEntity->stringValue);
									}
									#endif
									#ifdef NLC_USE_MATH_OBJECTS_BOOLEAN
									else if(mathObjectVariableType == NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_BOOLEAN)
									{
										*currentCodeBlockInTree = createCodeBlockSetBooleanPointerToEntityMathBooleanValue(*currentCodeBlockInTree, parsablePhraseReferenceName, childEntity);		//eg thedogsvalue = &(childEntity->booleanValue);
									}
									#endif
									#endif
									bool foundParsablePhraseInMathText = false;
									string parsablePhraseReferenceMathValue = generateCodeEntityMathValuePointerText(parsablePhraseReferenceName, NLC_PROGRAMMING_LANGUAGE_DEFAULT);	//eg *childEntity
									currentFullSentence->mathText = replaceAllOccurancesOfString(&(currentFullSentence->mathText), parsablePhraseReferenceName, parsablePhraseReferenceMathValue, &foundParsablePhraseInMathText);	//"thedogsvalue" -> "*thedogsvalue"
								}
								#ifdef NLC_USE_MATH_OBJECTS_ADVANCED
								else if(mathObjectVariableType == NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_UNKNOWN)
								{
									*currentCodeBlockInTree = createCodeBlockSetGenericEntityPointerToEntity(*currentCodeBlockInTree, parsablePhraseReferenceName, childEntity);		//eg thedogsvalue = childEntity;
									currentFullSentence->mathText = generateAssignMathTextValueExecuteFunctionMathText(currentFullSentence, parsablePhraseReferenceName, (currentFullSentence->hasLogicalConditionOperator));	//replace "thedogsvalue = ..." with "assignMathObjectValue(thedogsvalue, ...)", replace "X = thedogsvalue" with "assignMathTextValue(X, thedogsvalue)" etc
								}
								#endif

								foundParsablePhrase = true;
								if(!(currentFullSentence->hasLogicalConditionOperator))
								{
									currentFullSentence->mathTextIdentifiesMathValue = true;
								}

								*currentCodeBlockInTree = getLastCodeBlockInLevel(currentCodeBlockAtStartOfparsablePhrase);
							}
						}
						else
						{
							#ifdef NLC_DEBUG
							//cout << "generateCodeBlocksFromMathTextNLPparsablePhrase{} error: entity->isNumberOf && !(entity->NLCcontextGenerated): part 1 must have failed" << endl;
							#endif
						}
					}
				}
			}
		#ifdef NLC_TRANSLATOR_LOGICAL_CONDITIONS_BOOLEAN_STATEMENTS_INTERPRET_SUBJECT_AND_OBJECT_INDEPENDENTLY
		}
		#endif
		if(foundParsablePhrase)
		{
			if(!(currentFullSentence->hasLogicalConditionOperator))
			{
				#ifdef NLC_MATH_OBJECTS_TEST_NULL_POINTER_MAINTAIN_CONTEXT
				*currentCodeBlockInTree = createCodeBlockTestDecimalPointerValue(*currentCodeBlockInTree, parsablePhraseReferenceName);			 //if(thedogsvalue == NULL) { cout << "error" << endl;}
				#else
				*currentCodeBlockInTree = createCodeBlockCheckDecimalPointerValue(*currentCodeBlockInTree, parsablePhraseReferenceName);		 //if(thedogsvalue != NULL)
				#endif
			}
		}
		else
		{
			cout << "generateCodeBlocksFromMathTextNLPparsablePhrase{} error: !foundParsablePhrase" << endl;
			*currentCodeBlockInTree = clearCodeBlock(currentCodeBlockAtStartOfparsablePhrase);
		}
		#endif
		#endif
	}

	return foundParsablePhrase;
}

int getMathObjectVariableType(vector<GIAentityNode*>* entityNodesActiveListComplete, int sentenceIndex, NLCsentence* currentFullSentence, NLCsentence* parsablePhrase)
{
	string parsablePhraseReferenceName = generateMathTextNLPparsablePhraseReference(currentFullSentence->sentenceIndex, parsablePhrase);

	#ifdef NLC_DEBUG
	//cout << "getMathObjectVariableType{}:\n" << endl;
	//cout << "parsablePhraseReferenceName = " << parsablePhraseReferenceName << endl;
	#endif

	int mathObjectVariableType = NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_UNKNOWN;

	string mathTextSubphraseContainingNLPparsablePhrase = "";
	int mathTextSubphraseContainingNLPparsablePhraseIndex = 0;
	if(currentFullSentence->hasLogicalConditionOperator)
	{
		getMathTextSubphraseContainingNLPparsablePhrase(currentFullSentence->mathText, parsablePhraseReferenceName, &mathTextSubphraseContainingNLPparsablePhrase, &mathTextSubphraseContainingNLPparsablePhraseIndex);
	}
	else
	{
		mathTextSubphraseContainingNLPparsablePhrase = currentFullSentence->mathText;
	}

	//find boolean statement expressions
	bool foundBooleanStatementExpression = false;
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode* entity = (*entityIter);
		if(checkSentenceIndexParsingCodeBlocks(entity, sentenceIndex, false))
		{
			if(readParsablePhraseEntryEntityChecks(entity))
			{//required
				for(int i=0; i<GIA_ENTITY_NUMBER_OF_VECTOR_CONNECTION_TYPES; i++)
				{
					for(vector<GIAentityConnection*>::iterator connectionIter = entity->entityVectorConnectionsArray[i].begin(); connectionIter != entity->entityVectorConnectionsArray[i].end(); connectionIter++)
					{
						GIAentityConnection* connection = (*connectionIter);
						#ifdef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES
						if(connection->sentenceIndexTemp == sentenceIndex)
						{
						#endif
							if(!(connection->sameReferenceSet))
							{
								foundBooleanStatementExpression = true;
							}
						#ifdef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES
						}
						#endif
					}
				}
			}
		}
	}
	/*//don't use this method (use GIA network instead):
	for(int i=0; i<NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_AUXILIARY_KEYWORDS_TAGGING_SUBJECT_OR_REFERENCE_NUMBER_OF_TYPES; i++)
	{
		int indexOfAuxiliaryTemp = currentPhrasePrimarySubject->sentenceContents.find(preprocessorMathAuxiliaryKeywordsTaggingSubjectOrReference[i], 0);
		if((indexOfAuxiliaryTemp != CPP_STRING_FIND_RESULT_FAIL_VALUE)
		{
			for(int i2=0; i2<NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_RCMOD_SAME_REFERENCE_SET_DELIMITER_NUMBER_OF_TYPES; i2++)
			{
				int indexOfRcmodTemp = currentPhrasePrimarySubject->sentenceContents.rfind(preprocessorMathRcmodSameReferenceSetDelimiter[i2], indexOfAuxiliaryTemp);
				if((indexOfAuxiliaryTemp != indexOfAuxiliaryTemp-(preprocessorMathRcmodSameReferenceSetDelimiter[i2].length()+1))
				{
					foundBooleanStatementExpression = true;
				}
		}
	}
	*/
	if(foundBooleanStatementExpression)
	{
		if(currentFullSentence->hasLogicalConditionOperator)
		{
			mathObjectVariableType = NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_BOOLEAN_STATEMENT;
			#ifdef NLC_DEBUG_MATH_OBJECTS_ADVANCED
			cout << "mathObjectVariableType = NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_BOOLEAN_STATEMENT" << endl;
			#endif
		}
		else
		{
			//eg1 "the dog = the chicken is happy" - must say; "if the chicken is happy, the dog = true". eg2 "bool X = the chicken is happy" -  must say; "if the chicken is happy, X = true"
			cout << "generateCodeBlocksFromMathTextNLPparsablePhrase{} error: illegal expression detected: !(currentFullSentence->hasLogicalConditionOperator) && foundBooleanStatementExpression" << endl;
			cout << "parsablePhrase->sentenceContents = " << parsablePhrase->sentenceContents << endl;
			exit(0);
		}
	}

	//find numerical expressions
	for(int i=0; i<NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_NUMERICAL_OPERATORS_NUMBER_OF_TYPES; i++)
	{
		if(mathTextSubphraseContainingNLPparsablePhrase.find(mathObjectsVariableTypeNumericalOperators[i]) != CPP_STRING_FIND_RESULT_FAIL_VALUE)
		{
			mathObjectVariableType = NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_NUMERICAL;
			#ifdef NLC_DEBUG_MATH_OBJECTS_ADVANCED
			cout << "mathObjectVariableType = NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_NUMERICAL" << endl;
			#endif
		}
	}

	#ifdef NLC_USE_MATH_OBJECTS_ADVANCED

	//find string expressions
	//#ifdef NLC_USE_MATH_OBJECTS_ADVANCED_USE_UNIQUE_OPERATORS	//optional
	#ifdef NLC_USE_MATH_OBJECTS_STRING
	for(int i=0; i<NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_STRING_OPERATORS_NUMBER_OF_TYPES; i++)
	{
		if(mathTextSubphraseContainingNLPparsablePhrase.find(mathObjectsVariableTypeStringOperators[i]) != CPP_STRING_FIND_RESULT_FAIL_VALUE)
		{
			mathObjectVariableType = NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_STRING;
			#ifdef NLC_DEBUG_MATH_OBJECTS_ADVANCED
			cout << "mathObjectVariableType = NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_STRING" << endl;
			#endif
		}
	}
	#endif
	//#endif

	//find boolean expressions
	#ifdef NLC_USE_MATH_OBJECTS_BOOLEAN
	for(int i=0; i<NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_BOOLEAN_OPERATORS_NUMBER_OF_TYPES; i++)
	{
		if(mathTextSubphraseContainingNLPparsablePhrase.find(mathObjectsVariableTypeBooleanOperators[i]) != CPP_STRING_FIND_RESULT_FAIL_VALUE)
		{
			mathObjectVariableType = NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_BOOLEAN;
			cout << "mathObjectVariableType = NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_BOOLEAN" << endl;
		}
	}
	#endif

	#ifdef NLC_USE_MATH_OBJECTS_ADVANCED_INFER_TYPE_BASED_ON_PREVIOUSLY_DECLARED_MATHTEXT_VARIABLES
	//NB this code is not absolutely required (as assignMathObjectValue types can be inferred when compiling generated code), however it will simplify/normalise the generated output code
	for(vector<NLCvariable*>::iterator iter = currentFullSentence->mathTextVariables.begin(); iter != currentFullSentence->mathTextVariables.end(); iter++)
	{
		NLCvariable* mathTextVariable = (*iter);
		if(mathTextVariable->type != NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_UNKNOWN)
		{
			#ifdef NLC_USE_MATH_OBJECTS_ADVANCED_INFER_TYPE_BASED_ON_PREVIOUSLY_DECLARED_MATHTEXT_VARIABLES_ADVANCED

			#ifdef NLC_USE_MATH_OBJECTS_ADVANCED_USE_UNIQUE_OPERATORS
			//egs foundMathtextVariableAssignment: eg1 [double] X = thecatssvalue
			//egs foundParsablePhraseReferenceNameAssignment: thedogsvalue = X
			#else
			//egs foundMathtextVariableAssignment: eg1 [double] X = thecatssvalue, eg2 [double] X = thecatssvalue + themousessvalue
			//egs foundParsablePhraseReferenceNameAssignment: thedogsvalue = X, eg2 thedogsvalue = thecatssvalue, eg3 thedogsvalue = X + Y, eg4 thedogsvalue = thecatssvalue + Y
			//egs foundParsablePhraseReferenceNameTest: eg1 X == thecatssvalue, eg2 eg1 thedogsvalue == X, eg4 X == thecatssvalue + themousessvalue, eg5 thedogsvalue == X + themousessvalue, eg6 thedogsvalue == X + Y, eg7 thedogsvalue == X + themousessvalue, eg6 thedogsvalue == X + Y, eg7 thedogsvalue == thecatssvalue + Y
			#endif

			#ifdef NLC_DEBUG
			//cout << "mathTextVariable name = " << mathTextVariable->name << endl;
			//cout << "mathTextVariable name length = " << (mathTextVariable->name).length() << endl;
			#endif

			if(findMathTextVariableWithinMathText(mathTextVariable->name, mathTextSubphraseContainingNLPparsablePhrase))
			{
				mathObjectVariableType = mathTextVariable->type;
				#ifdef NLC_DEBUG
				//cout << "mathObjectVariableType = " << mathObjectVariableType << endl;
				#endif
			}

			#else
			if(!(currentFullSentence->hasLogicalConditionOperator))
			{
				#ifdef NLC_USE_MATH_OBJECTS_ADVANCED_USE_UNIQUE_OPERATORS
				//egs foundMathtextVariableAssignment: eg1 [double] X = thecatssvalue
				#else
				//egs foundMathtextVariableAssignment: eg1 [double] X = thecatssvalue, eg2 [double] X = thecatssvalue + themousessvalue
				#endif

				cout << "mathTextVariable name = " << mathTextVariable->name << endl;
				cout << "mathTextVariable name length = " << (mathTextVariable->name).length() << endl;
				int indexOfMathEqualsSetCommand = currentFullSentence->mathText.find(NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_SET_CHAR);
				if(indexOfMathEqualsSetCommand != CPP_STRING_FIND_RESULT_FAIL_VALUE)
				{
					if(currentFullSentence->mathText[indexOfMathEqualsSetCommand-1] == CHAR_SPACE)
					{
						indexOfMathEqualsSetCommand = indexOfMathEqualsSetCommand-1;	//ignore space preceeding equals set character
					}

					//find reference to already declared mathtext variable
					string targetText = currentFullSentence->mathText.substr(0, indexOfMathEqualsSetCommand);
					cout << "targetText = " << targetText << endl;

					if((targetText == mathTextVariable->name) || (targetText == (mathTextVariable->name + STRING_SPACE)))
					{
						//eg X = The car + the house
						mathObjectVariableType = mathTextVariable->type;
						#ifdef NLC_DEBUG
						//cout << "mathObjectVariableType = " << mathObjectVariableType << endl;
						#endif
					}

					//find reference to mathtext variable declaration
					for(int j=0; j<NLC_PREPROCESSOR_MATH_MATHTEXT_VARIABLES_NUMBER_OF_TYPES; j++)
					{
						int indexOfType = targetText.find(preprocessorMathNaturalLanguageVariables[j]);
						if(indexOfType == 0)
						{
							if(targetText == (preprocessorMathNaturalLanguageVariables[j] + STRING_SPACE + mathTextVariable->name))
							{
								//eg double X = The car + the house
								mathObjectVariableType = mathTextVariable->type;
								#ifdef NLC_DEBUG
								//cout << "mathObjectVariableType = " << mathObjectVariableType << endl;
								#endif
							}
						}
					}
				}
			}
			#endif
		}
	}
	#endif

	#ifdef NLC_USE_MATH_OBJECTS_ADVANCED_USE_UNIQUE_OPERATORS
	if(currentFullSentence->hasLogicalConditionOperator)
	{
		if(mathObjectVariableType == NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_UNKNOWN)
		{
			#ifdef NLC_USE_MATH_OBJECTS_ADVANCED_USE_UNIQUE_OPERATORS_ASSUME_LOGICAL_CONDITION_STATEMENTS_ARE_BOOLEAN_IF_UNKNOWN
			mathObjectVariableType = NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_BOOLEAN;
			#else
			cout << "NLC_USE_MATH_OBJECTS_ADVANCED_USE_UNIQUE_OPERATORS: getMathObjectVariableType{} error: (currentFullSentence->hasLogicalConditionOperator) && (mathObjectVariableType == NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_UNKNOWN)" << endl;
			exit(0);
			#endif
		}
	}
	#endif

	#else
	if(mathObjectVariableType == NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_UNKNOWN)
	{
		mathObjectVariableType = NLC_USE_MATH_OBJECTS_VARIABLE_TYPE_NUMERICAL;
	}
	#endif

	return mathObjectVariableType;
}

bool getMathTextSubphraseContainingNLPparsablePhrase(string mathText, string parsablePhraseReferenceName, string* mathTextSubphraseContainingNLPparsablePhrase, int* mathTextSubphraseContainingNLPparsablePhraseIndex)
{
	bool result = true;
	bool foundConjunction = false;

	//remove the preceeding "if(" and trailing ")" of logical condition
	string mathTextLogicalConditionContents = "";
	int mathTextLogicalConditionContentsIndex = CPP_STRING_FIND_RESULT_FAIL_VALUE;
	bool foundLogicalConditionStartText = false;
	string logicalConditionEndText = string("") + NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_CLOSE_BRACKET;
	for(int i=0; i<NLC_LOGICAL_CONDITION_OPERATIONS_NUMBER_OF_TYPES; i++)
	{
		string logicalConditionStartText = logicalConditionOperationsArray[i] + NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_OPEN_BRACKET;
		if(mathText.find(logicalConditionStartText) == 0)
		{
			mathTextLogicalConditionContents = mathText.substr(logicalConditionStartText.length(), mathText.length() - logicalConditionStartText.length() - logicalConditionEndText.length());
			mathTextLogicalConditionContentsIndex = logicalConditionStartText.length();
			foundLogicalConditionStartText = true;
		}
	}
	if(foundLogicalConditionStartText)
	{
		#ifdef NLC_DEBUG_MATH_OBJECTS_ADVANCED
		cout << " mathText = " << mathText << endl;
		cout << " mathTextLogicalConditionContents = " << mathTextLogicalConditionContents << endl;
		#endif
		//algorithm: extract "&& (thehouse == " -> " (thehouse " -> "thehouse"

		//find numerical expressions
		int parsablePhraseReferenceNamePositionInMathtext = mathTextLogicalConditionContents.find(parsablePhraseReferenceName);
		if(parsablePhraseReferenceNamePositionInMathtext != CPP_STRING_FIND_RESULT_FAIL_VALUE)
		{
			//find all subphrases as demarcated by &&, ||
			int subphraseStartPosition = 0;
			int subphraseEndPosition = mathTextLogicalConditionContents.length();
			bool foundConjunctionLeft = false;
			bool foundConjunctionRight = false;
			for(int i=0; i<NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_COORDINATING_CONJUNCTION_WITH_AND_WITHOUT_WHITESPACE_ARRAY_NUMBER_OF_TYPES; i++)
			{
				int tempPos = mathTextLogicalConditionContents.find(progLangCoordinatingConjunctionsWithAndWithoutWhiteSpace[i], parsablePhraseReferenceNamePositionInMathtext);
				if(tempPos != CPP_STRING_FIND_RESULT_FAIL_VALUE)
				{
					if(tempPos < subphraseEndPosition)
					{
						subphraseEndPosition = tempPos;
						foundConjunctionRight = true;
					}
				}
			}
			for(int i=0; i<NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_COORDINATING_CONJUNCTION_WITH_AND_WITHOUT_WHITESPACE_ARRAY_NUMBER_OF_TYPES; i++)
			{
				int tempPos = mathTextLogicalConditionContents.rfind(progLangCoordinatingConjunctionsWithAndWithoutWhiteSpace[i], parsablePhraseReferenceNamePositionInMathtext);
				if(tempPos != CPP_STRING_FIND_RESULT_FAIL_VALUE)
				{
					tempPos = tempPos + progLangCoordinatingConjunctionsWithAndWithoutWhiteSpace[i].length();	//character after &&
					if(tempPos > subphraseStartPosition)
					{
						subphraseStartPosition = tempPos;
						foundConjunctionLeft = true;
					}
				}
			}

			string subphraseTemp = mathTextLogicalConditionContents.substr(subphraseStartPosition, subphraseEndPosition-subphraseStartPosition);
			if(foundConjunctionLeft || foundConjunctionRight)
			{
				int subphraseStartPositionTemp = CPP_STRING_FIND_RESULT_FAIL_VALUE;
				int subphraseEndPositionTemp = CPP_STRING_FIND_RESULT_FAIL_VALUE;
				#ifdef NLC_DEBUG_MATH_OBJECTS_ADVANCED
				cout << "subphraseTemp = " << subphraseTemp << endl;
				#endif
				if(findMatchingBrackets(subphraseTemp, &subphraseStartPositionTemp, &subphraseEndPositionTemp))
				{
					subphraseStartPosition = subphraseStartPosition + subphraseStartPositionTemp;
					subphraseEndPosition = subphraseStartPosition + (subphraseEndPositionTemp - subphraseStartPositionTemp);
				}
				foundConjunction = true;
			}
			else
			{
				foundConjunction = false;
			}

			*mathTextSubphraseContainingNLPparsablePhrase = mathTextLogicalConditionContents.substr(subphraseStartPosition, subphraseEndPosition-subphraseStartPosition);
			*mathTextSubphraseContainingNLPparsablePhraseIndex = subphraseStartPosition + mathTextLogicalConditionContentsIndex;
			
			if(removeSurroundingBracketsOfSubphrase(mathTextSubphraseContainingNLPparsablePhrase))	//added 1t3d
			{
				int sizeOfBracket = string(NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_OPEN_BRACKET_STRING).length();
				*mathTextSubphraseContainingNLPparsablePhraseIndex = *mathTextSubphraseContainingNLPparsablePhraseIndex + sizeOfBracket;		
			}
			
			#ifdef NLC_DEBUG_MATH_OBJECTS_ADVANCED
			cout << "*mathTextSubphraseContainingNLPparsablePhrase = " << *mathTextSubphraseContainingNLPparsablePhrase << endl;
			#endif
		}
		else
		{
			result = false;
			cout << "getMathObjectVariableType{} error: parsablePhraseReferenceNamePositionInMathtext cannot be identified" << endl;
			exit(0);
		}
	}
	else
	{
		result = false;
		cout << "getMathObjectVariableType{} error: !foundLogicalConditionStartText" << endl;
		exit(0);
	}

	return result;
}

bool findMatchingBrackets(string subphraseTemp, int* subphraseStartPositionTemp, int* subphraseEndPositionTemp)
{
	bool result = true;
	int numberOfOpenBrackets = 0;
	int numberOfCloseBrackets = 0;
	for(int i=0; i<subphraseTemp.length(); i++)
	{
		if(subphraseTemp[i] == NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_OPEN_BRACKET)
		{
			numberOfOpenBrackets++;
		}
	}
	for(int i=0; i<subphraseTemp.length(); i++)
	{
		if(subphraseTemp[i] == NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_CLOSE_BRACKET)
		{
			numberOfCloseBrackets++;
		}
	}
	if(numberOfOpenBrackets > numberOfCloseBrackets)
	{
		int numberExtraOpenBrackets = numberOfOpenBrackets - numberOfCloseBrackets;
		int numberOpenBracketsFound = 0;
		int i = 0;
		while(numberOpenBracketsFound < numberExtraOpenBrackets)
		{
			if(subphraseTemp[i] == NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_OPEN_BRACKET)
			{
				numberOpenBracketsFound++;
			}
			i++;
		}
		*subphraseStartPositionTemp = i;
		*subphraseEndPositionTemp = subphraseTemp.length();
	}
	else if(numberOfOpenBrackets < numberOfCloseBrackets)
	{
		int numberExtraCloseBrackets = numberOfCloseBrackets - numberOfOpenBrackets;
		int numberCloseBracketsFound = 0;
		int i = subphraseTemp.length()-1;
		while(numberCloseBracketsFound < numberExtraCloseBrackets)
		{
			if(subphraseTemp[i] == NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_CLOSE_BRACKET)
			{
				numberCloseBracketsFound++;
			}
			i--;
		}
		*subphraseStartPositionTemp = 0;
		*subphraseEndPositionTemp = i+1;
	}
	else
	{
		*subphraseStartPositionTemp = 0;
		*subphraseEndPositionTemp = subphraseTemp.length();
	}
	return result;
}

#ifdef NLC_USE_MATH_OBJECTS_ADVANCED
string generateAssignMathTextValueExecuteFunctionMathText(NLCsentence* currentFullSentence, string parsablePhraseReferenceName, bool hasLogicalConditionOperator)
{
	string* mathText = &(currentFullSentence->mathText);
	 
	bool foundParsablePhraseReferenceNameAssignment = false;
	int progLang = getProgLang();	//CHECKTHIS - note this is an unusual implementation, in future could update NLCtranslatorCodeBlocksLogicalConditions.cpp generateCodeBlocksFromMathText{} to not execute generateCodeBlocksFromMathText (ie print updated mathText), but instead execute a new codeBlocks subroutine createCodeBlockAssignMathTextValueExecute(targetText, sourceText)
	string mathTextUpdated = *mathText;
	int parsablePhraseReferenceNameIndex = mathText->find(parsablePhraseReferenceName);
	if(parsablePhraseReferenceNameIndex != CPP_STRING_FIND_RESULT_FAIL_VALUE)
	{
		int indexOfMathEqualsSetCommand = INT_DEFAULT_VALUE;
		bool foundMathEqualsSetCommand = findCharacterAtIndexOrAfterSpace(mathText, parsablePhraseReferenceNameIndex+parsablePhraseReferenceName.length(), NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_SET_CHAR, &indexOfMathEqualsSetCommand);	//mathText eg: "thedogsvalue =" OR "thedogsvalue="
		if(foundMathEqualsSetCommand)
		{
			#ifdef NLC_USE_MATH_OBJECTS_ADVANCED_USE_UNIQUE_OPERATORS
			//eg1 thedogsvalue = X, eg2 thedogsvalue = thecatssvalue
			#else
			//eg1 thedogsvalue = X, eg2 thedogsvalue = thecatssvalue, eg3 thedogsvalue = X + Y, eg4 thedogsvalue = thecatssvalue + Y
			#endif
			#ifndef NLC_USE_MATH_OBJECTS_ADVANCED_USE_UNIQUE_OPERATORS
			if(mathText->find(NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_TEST, indexOfMathEqualsSetCommand) != indexOfMathEqualsSetCommand)
			{//ignore equals test ("==") expressions
			#else
			//redundant as !(currentFullSentence->hasLogicalConditionOperator)
			#endif
				foundParsablePhraseReferenceNameAssignment = true;
				string targetValueText = getTargetValueText(mathText, indexOfMathEqualsSetCommand, NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_SET, progLang);	//eg thedogsvalue
				mathTextUpdated = NLC_USE_MATH_OBJECTS_ADVANCED_ASSIGN_MATHOBJECT_VALUE_FUNCTION_NAME + progLangOpenParameterSpace[progLang] + parsablePhraseReferenceName + progLangClassMemberFunctionParametersNext[progLang] + targetValueText + progLangCloseParameterSpace[progLang];	//eg0 "assignMathObjectValue(thedogsvalue, thechickensvalue)", eg1 "assignMathObjectValue(thedogsvalue, addMathTextValue(5 + theNumberOfApplesNearTheFarm))", eg2 "assignMathObjectValue(thedogsvalue, addMathTextValue("the dog's name is ", maxsName))"
			#ifndef NLC_USE_MATH_OBJECTS_ADVANCED_USE_UNIQUE_OPERATORS
			}
			#endif
		}
	}
	bool foundMathtextVariableAssignment = false;
	if(!foundParsablePhraseReferenceNameAssignment)
	{
		//create assignment wrapper
		int indexOfMathEqualsSetCommand = mathText->find(NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_SET_CHAR);
		if(indexOfMathEqualsSetCommand != CPP_STRING_FIND_RESULT_FAIL_VALUE)
		{
			#ifdef NLC_USE_MATH_OBJECTS_ADVANCED_USE_UNIQUE_OPERATORS
			//eg1 X = thecatssvalue
			#else
			//eg1 X = thecatssvalue, eg2 X = thecatssvalue + themousessvalue
			#endif
			
		
			#ifndef NLC_USE_MATH_OBJECTS_ADVANCED_USE_UNIQUE_OPERATORS
			if(mathText->find(NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_TEST, indexOfMathEqualsSetCommand) != indexOfMathEqualsSetCommand)
			{//a) ignore equals test ("==") expressions
				if(!findInvertedCommasEitherSideOfCharacter(mathText, indexOfMathEqualsSetCommand))
				{//b) ignore all equals signs within inverted commas
					//mathText eg: "X =" OR "X="
					#ifdef NLC_USE_MATH_OBJECTS_ADVANCED_ASSIGN_MATHTEXT_VALUE_FUNCTION
					if(mathText->find(NLC_USE_MATH_OBJECTS_ADVANCED_ASSIGN_MATHTEXT_VALUE_FUNCTION_NAME, indexOfMathEqualsSetCommand) != (indexOfMathEqualsSetCommand + 2))
					{//c) only create one instance of = getMathObjectValue(.. per sentence;	eg X = thecatssvalue + themousessvalue
					#else
					if(mathText->find(NLC_USE_MATH_OBJECTS_ADVANCED_GET_MATHOBJECT_VALUE_FUNCTION_NAME) != CPP_STRING_FIND_RESULT_FAIL_VALUE)	//redundant
					{//c) only create one instance of assignMathtextValue(.. per sentence;	eg X = thecatssvalue + themousessvalue
					#endif
			#else
			//redundant as a) !(currentFullSentence->hasLogicalConditionOperator), b) finding first instance of '=', so there will be no '"' characters before the '=' character, and c) there are no additions (+) so there will only be one parsable phrase found in the sentence
			#endif
						#ifdef NLC_USE_MATH_OBJECTS_ADVANCED_ASSIGN_MATHTEXT_VALUE_FUNCTION
						//verify that the equality source value text does not contain an NLP parsable phrase reference
						bool sourceIsParsablePhrase = false;
						string sourceValueText = getSourceValueText(mathText, indexOfMathEqualsSetCommand, progLang);
						NLCsentence* currentParsablePhrase2 = currentFullSentence;
						for(int i = 0; i < currentFullSentence->mathTextNLPparsablePhraseTotal; i++)
						{
							string parsablePhraseReferenceName2 = generateMathTextNLPparsablePhraseReference(currentFullSentence->sentenceIndex, currentParsablePhrase2);
							if(sourceValueText.find(parsablePhraseReferenceName2) != CPP_STRING_FIND_RESULT_FAIL_VALUE)
							{
								sourceIsParsablePhrase = true;
							}
							currentParsablePhrase2 = currentParsablePhrase2->next;
						}
						if(!sourceIsParsablePhrase)
						{		
							bool mathtextValueDeclarationDetected = false;
							int mathtextValueDeclarationType = INT_DEFAULT_VALUE;
							for(int j=0; j<NLC_PREPROCESSOR_MATH_MATHTEXT_VARIABLES_NUMBER_OF_TYPES; j++)
							{
								int indexOfType = mathText->find(preprocessorMathNaturalLanguageVariables[j]);
								if((indexOfType != CPP_STRING_FIND_RESULT_FAIL_VALUE) && (indexOfType == 0))
								{
									mathtextValueDeclarationDetected = true;	//explictTypeFound
									mathtextValueDeclarationType = j;	
								}
							}		
							if(mathtextValueDeclarationDetected)
							{
								//CHECKTHIS
								//eg "string X = thecatssvalue + themousessvalue" -> "string X; assignMathTextValue(X, thecatssvalue + themousessvalue);
								string mathTextValueDeclaration = sourceValueText + progLangEndLine[progLang] + progLangSpace[progLang];	//eg "string X; "
								string mathTextValueInitialisation = mathText->substr(preprocessorMathNaturalLanguageVariables[mathtextValueDeclarationType].length() + 1);	//eg "X = thecatssvalue + themousessvalue"	//+1 to remove space after type
								int indexOfMathEqualsSetCommandInitialisation = indexOfMathEqualsSetCommand - (preprocessorMathNaturalLanguageVariables[mathtextValueDeclarationType].length() + 1);		//+1 to remove space after type
								string sourceValueTextInitialisation = getSourceValueText(&mathTextValueInitialisation, indexOfMathEqualsSetCommandInitialisation, progLang);
								string targetValueTextInitialisation = getTargetValueText(&mathTextValueInitialisation, indexOfMathEqualsSetCommandInitialisation, NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_SET, progLang);
								string assignMathTextValueText = string(NLC_USE_MATH_OBJECTS_ADVANCED_ASSIGN_MATHTEXT_VALUE_FUNCTION_NAME) + progLangOpenParameterSpace[progLang] + generateReferenceText(sourceValueTextInitialisation, progLang) + progLangClassMemberFunctionParametersNext[progLang] + targetValueTextInitialisation + progLangCloseParameterSpace[progLang];	//eg0 "assignMathTextValue(X, thechickensvalue)", eg1 "assignMathTextValue(X, addMathTextValue(5 + theNumberOfApplesNearTheFarm))", eg2 "assignMathTextValue(X, addMathTextValue("the dog's name is ", maxsName))"
								mathTextUpdated = mathTextValueDeclaration + assignMathTextValueText;
								foundMathtextVariableAssignment = true;
							}
							else
							{
								//eg "X = thecatssvalue + themousessvalue" -> "assignMathTextValue(X, thecatssvalue + themousessvalue);
								string targetValueText = getTargetValueText(mathText, indexOfMathEqualsSetCommand, NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_SET, progLang);
								string assignMathTextValueText = string(NLC_USE_MATH_OBJECTS_ADVANCED_ASSIGN_MATHTEXT_VALUE_FUNCTION_NAME) + progLangOpenParameterSpace[progLang] + generateReferenceText(sourceValueText, progLang) + progLangClassMemberFunctionParametersNext[progLang] + targetValueText + progLangCloseParameterSpace[progLang];	//eg0 "assignMathTextValue(X, thechickensvalue)", eg1 "assignMathTextValue(X, addMathTextValue(5 + theNumberOfApplesNearTheFarm))", eg2 "assignMathTextValue(X, addMathTextValue("the dog's name is ", maxsName))"
								mathTextUpdated = assignMathTextValueText;
								foundMathtextVariableAssignment = true;
							}
						}
						#else
						string targetValueText = getTargetValueText(mathText, indexOfMathEqualsSetCommand, NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_SET, progLang);
						string getMathObjectValueText = string(NLC_USE_MATH_OBJECTS_ADVANCED_GET_MATHOBJECT_VALUE_FUNCTION_NAME) + progLangOpenParameterSpace[progLang] + targetValueText + progLangCloseParameterSpace[progLang];	//eg "X = thechickensvalue"  ->  "X = getMathObjectValue(thechickensvalue)"
						mathTextUpdated = mathText->substr(0, indexOfMathEqualsSetCommand+1) + STRING_SPACE + getMathObjectValueText;
						foundMathtextVariableAssignment = true;
						#endif
			#ifndef NLC_USE_MATH_OBJECTS_ADVANCED_USE_UNIQUE_OPERATORS
					}

				}
			}
			#endif
		
		}
	}

	#ifndef NLC_USE_MATH_OBJECTS_ADVANCED_USE_UNIQUE_OPERATORS
	if(hasLogicalConditionOperator)
	{
		bool foundParsablePhraseReferenceNameTest = false;
		if(foundMathtextVariableAssignment || foundParsablePhraseReferenceNameAssignment)
		{
			cout << "generateAssignMathTextValueExecuteFunctionMathText{} error: hasLogicalConditionOperator && (foundMathtextVariableAssignment || foundParsablePhraseReferenceNameAssignment)" << endl;
			exit(0);
		}

		int mathTextSubphraseContainingNLPparsablePhraseIndex = 0;
		string mathTextSubphraseContainingNLPparsablePhrase = "";
		bool subphraseFound = false;
		if(!getMathTextSubphraseContainingNLPparsablePhrase(*mathText, parsablePhraseReferenceName, &mathTextSubphraseContainingNLPparsablePhrase, &mathTextSubphraseContainingNLPparsablePhraseIndex))
		{
			cout << "generateAssignMathTextValueExecuteFunctionMathText{} error: !getMathTextSubphraseContainingNLPparsablePhrase" << endl;
			exit(0);
		}
		int indexOfMathEqualsTestCommand = mathTextSubphraseContainingNLPparsablePhrase.find(NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_TEST);
		if(indexOfMathEqualsTestCommand != CPP_STRING_FIND_RESULT_FAIL_VALUE)
		{
			#ifdef NLC_DEBUG
			cout << "mathTextSubphraseContainingNLPparsablePhrase = " << mathTextSubphraseContainingNLPparsablePhrase << endl;
			#endif
			//eg1 X == thecatssvalue, eg2 eg1 thedogsvalue == X eg3 thedogsvalue == thecatssvalue, eg3 thedogsvalue == thecatssvalue + themousessvalue, eg4 X == thecatssvalue + themousessvalue, eg5 thedogsvalue == X + themousessvalue, eg6 thedogsvalue == X + Y, eg7 thedogsvalue == X + themousessvalue, eg6 thedogsvalue == X + Y, eg7 thedogsvalue == thecatssvalue + Y [not X == Y]
			if(mathText->find(NLC_USE_MATH_OBJECTS_ADVANCED_TEST_MATHOBJECT_VALUE_FUNCTION_NAME) != 0)
			{//only create one instance of = testMathObjectValue(.. per sentence; eg1 X == thecatssvalue + themousessvalue, eg2 thecatssvalue == themousessvalue
				string targetValueText = getTargetValueText(&mathTextSubphraseContainingNLPparsablePhrase, indexOfMathEqualsTestCommand, NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_TEST, progLang);
				string sourceValueText = getSourceValueText(&mathTextSubphraseContainingNLPparsablePhrase, indexOfMathEqualsTestCommand, progLang);
				#ifdef NLC_USE_MATH_OBJECTS_ADVANCED_COMPARISONS
				string mathTextSubphraseContainingNLPparsablePhraseUpdated = string(NLC_USE_MATH_OBJECTS_ADVANCED_TEST_MATHOBJECT_VALUE_FUNCTION_NAME) + progLangOpenParameterSpace[progLang] + sourceValueText + progLangClassMemberFunctionParametersNext[progLang] + targetValueText + progLangCloseParameterSpace[progLang];	//eg "X == thechickensvalue"  ->  "testMathObjectValue(X, thechickensvalue)"
				#else
				string mathTextSubphraseContainingNLPparsablePhraseUpdated = sourceValueText + NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_TEST_WITH_PADDING + targetValueText;
				#endif
				mathTextUpdated.replace(mathTextSubphraseContainingNLPparsablePhraseIndex, mathTextSubphraseContainingNLPparsablePhrase.length(), mathTextSubphraseContainingNLPparsablePhraseUpdated);
				#ifdef NLC_DEBUG
				cout << "mathTextUpdated = " << mathTextUpdated << endl;
				#endif
				//progLangParameterSpaceNextParam
			}
		}
		else
		{
			int parsablePhraseReferenceNamePositionInSubphrase = mathTextSubphraseContainingNLPparsablePhrase.find(parsablePhraseReferenceName);
			if(parsablePhraseReferenceNamePositionInSubphrase != CPP_STRING_FIND_RESULT_FAIL_VALUE)
			{
				string parsablePhraseReferenceNameUpdated = string(NLC_USE_MATH_OBJECTS_ADVANCED_TEST_MATHOBJECT_VALUE_FUNCTION_NAME) + progLangOpenParameterSpace[progLang] + parsablePhraseReferenceName + progLangCloseParameterSpace[progLang];	//eg "thechickensvalue"  ->  "testMathObjectValue(thechickensvalue)"
				string mathTextSubphraseContainingNLPparsablePhraseUpdated = mathTextSubphraseContainingNLPparsablePhrase;
				mathTextSubphraseContainingNLPparsablePhraseUpdated.replace(parsablePhraseReferenceNamePositionInSubphrase, parsablePhraseReferenceName.length(), parsablePhraseReferenceNameUpdated);
				mathTextUpdated.replace(mathTextSubphraseContainingNLPparsablePhraseIndex, mathTextSubphraseContainingNLPparsablePhrase.length(), mathTextSubphraseContainingNLPparsablePhraseUpdated);
			}
		}
	}
	#endif

	return mathTextUpdated;
}


bool findInvertedCommasEitherSideOfCharacter(string* mathText, int indexOfCharacter)
{
	bool foundInvertedCommasEitherSideOfCharacter = false;
	if(mathText->find(NLC_USE_MATH_OBJECTS_STRING_DELIMITER, indexOfCharacter) != CPP_STRING_FIND_RESULT_FAIL_VALUE)
	{
		if(mathText->rfind(NLC_USE_MATH_OBJECTS_STRING_DELIMITER, indexOfCharacter) != CPP_STRING_FIND_RESULT_FAIL_VALUE)
		{
			foundInvertedCommasEitherSideOfCharacter = true;
		}
	}
	return foundInvertedCommasEitherSideOfCharacter;
}

string getTargetValueText(string* mathText, int indexOfCommand, string command, int progLang)
{
	string targetValueText = "";
	if((*mathText)[indexOfCommand + command.length()] == CHAR_SPACE)
	{
		targetValueText = mathText->substr(indexOfCommand + command.length() + 1);
	}
	else
	{
		targetValueText = mathText->substr(indexOfCommand + command.length());
	}
	#ifdef NLC_USE_MATH_OBJECTS_ADVANCED_ADDITIONS
	targetValueText = replaceAllAdditionSymbolsWithAdditionFunction(targetValueText, progLang);
	#endif
	return targetValueText;
}

string getSourceValueText(string* mathText, int indexOfCommand, int progLang)
{
	string sourceValueText = "";
	if((*mathText)[indexOfCommand - 1] == CHAR_SPACE)
	{
		sourceValueText = mathText->substr(0, indexOfCommand-1);
	}
	else
	{
		sourceValueText = mathText->substr(0, indexOfCommand);
	}
	#ifdef NLC_USE_MATH_OBJECTS_ADVANCED_ADDITIONS
	sourceValueText = replaceAllAdditionSymbolsWithAdditionFunction(sourceValueText, progLang);
	#endif
	return sourceValueText;
}

#ifdef NLC_USE_MATH_OBJECTS_ADVANCED_ADDITIONS
string replaceAllAdditionSymbolsWithAdditionFunction(string text, int progLang)
{
	removeSurroundingBracketsOfSubphrase(&text);	//added 1t3d
	
	//now detect all instances of "+" within text and insert addMathTextValue{} function
	//eg thedogsvalue + 5 -> addMathTextValue(thedogsvalue, 5)
	//algorithm eg: "a + b + c"  ->  "a , b + c"  ->  "a , b) + c"  ->  "addMathTextValue(addMathTextValue((a, b), c)"
	int pos = 0;
	string stringToFind = NLC_PREPROCESSOR_MATH_OPERATOR_STRING_ADD;
	int numberOfAdditionsFound = 0;
	while((pos = text.find(stringToFind, pos)) != CPP_STRING_FIND_RESULT_FAIL_VALUE)
	{
		int stringToFindLength = stringToFind.length();
		if(text[pos-1] == CHAR_SPACE)
		{
			pos = pos-1;	//remove blank space
			stringToFindLength = stringToFindLength + 1;
		}

		string replacementString = "";
		if(numberOfAdditionsFound > 0)
		{
			replacementString = progLangCloseParameterSpace[progLang] + progLangParameterSpaceNextParam[progLang];
		}
		else
		{
			replacementString = progLangParameterSpaceNextParam[progLang];
		}
		text.replace(pos, stringToFindLength, replacementString);
		pos = pos + replacementString.length();
		numberOfAdditionsFound++;
	}
	for(int i=0; i<numberOfAdditionsFound; i++)
	{
		text = string(NLC_USE_MATH_OBJECTS_ADVANCED_ADD_MATHOBJECT_VALUE_FUNCTION_NAME) + progLangOpenParameterSpace[progLang] + text;
	}
	if(numberOfAdditionsFound > 0)
	{
		text = text + progLangCloseParameterSpace[progLang];
	}
	return text;
}
#endif

bool removeSurroundingBracketsOfSubphrase(string* subphraseText)
{
	bool foundSurroundingBrackets = false;
	string subphraseTemp = *subphraseText;
	
	int numberOfOpenBrackets = 0;
	if((subphraseTemp[0] == NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_OPEN_BRACKET) && (subphraseTemp[subphraseTemp.length()-1] == NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_CLOSE_BRACKET))
	{
		int sizeOfBracket = string(NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_OPEN_BRACKET_STRING).length();	//assume == NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_CLOSE_BRACKET
		numberOfOpenBrackets = 1;
		int i = 0;
		foundSurroundingBrackets = true;
		for(int i=0; i<subphraseTemp.length()-sizeOfBracket; i++)	//-1 to ingore last bracket
		{
			if(subphraseTemp[i] == NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_OPEN_BRACKET)
			{
				numberOfOpenBrackets++;
			}
			if(subphraseTemp[i] == NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_CLOSE_BRACKET)
			{
				numberOfOpenBrackets--;
			}
			if(numberOfOpenBrackets < 1)
			{
				foundSurroundingBrackets = false;
			}
		}
		if(foundSurroundingBrackets)
		{
			//eg: "(a + b)"  ->  "a + b"
			//eg: "(a + (b))"  ->  "a + (b)"
			//eg: "(a == b)"  ->  "a == b"
			//eg: "(a == (b))"  ->  "a == (b)"
			
			*subphraseText = subphraseTemp.substr(sizeOfBracket, subphraseTemp.length()-(sizeOfBracket*2));
		}	
	}
	return foundSurroundingBrackets;
}



bool isNumberOf(GIAentityNode* entity)
{
	bool numberOfFound = false;
	#ifdef NLC_PREPROCESSOR_MATH_OLD_NUMBER_OF_IMPLEMENTATION_USING_QVARS
	if(entity->isQuery)
	#else
	if(entity->isNumberOf)
	#endif
	{
		numberOfFound = true;
	}
	return numberOfFound;
}

bool generateCodeBlocksFromMathTextNLPparsablePhraseLogicalConditionFor(NLCcodeblock** currentCodeBlockInTree, vector<GIAentityNode*>* entityNodesActiveListComplete, int sentenceIndex, NLCsentence* currentFullSentence, NLCsentence* parsablePhrase, int phraseIndex, NLCcodeblock** currentCodeBlockInTreeAtBaseLevel, NLCsentence* firstNLCsentenceInFullSentence)
{
	bool foundParsablePhrase = false;

	#ifdef NLC_DEBUG_PREPROCESSOR_MATH
	cout << "generateCodeBlocksFromMathTextNLPparsablePhraseLogicalConditionFor{}" << endl;
	#endif
	//generate NLP parsable phrase eg "all apples in the cart" in "for(all the apples in the cart)"

	#ifdef NLC_GENERATE_UNIQUE_CONTEXT_BLOCK_FOR_EACH_SENTENCE_LOGICAL_CONDITIONS_FOR_LOOPS
	NLCcodeblock* firstCodeBlockInPhrase = *currentCodeBlockInTree;
	*currentCodeBlockInTree = createCodeBlocksCreateContextBlock(*currentCodeBlockInTree);
	#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
	*currentCodeBlockInTreeAtBaseLevel = firstCodeBlockInPhrase;
	#ifdef NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT
	(*currentCodeBlockInTreeAtBaseLevel)->isLogicalCondition = true;
	(*currentCodeBlockInTreeAtBaseLevel)->contextLevel = firstNLCsentenceInFullSentence->indentation+1;
	#endif
	#endif
	#endif

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

						#ifdef NLC_TRANSLATOR_LOGICAL_CONDITIONS_FOR_LOOP_ADD_ENTITY_TO_NEW_CONTEXT_LIST
						logicalConditionForLoopPrimaryEntityTemp = childEntity;
						#endif

						#ifndef NLC_GENERATE_UNIQUE_CONTEXT_BLOCK_FOR_EACH_SENTENCE_LOGICAL_CONDITIONS_FOR_LOOPS
						#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
						*currentCodeBlockInTreeAtBaseLevel = generateContextBlocksVariables.currentCodeBlockInTreeAtBaseLevel;
						#ifdef NLC_USE_ADVANCED_REFERENCING_MONITOR_CONTEXT
						(*currentCodeBlockInTreeAtBaseLevel)->isLogicalCondition = true;
						(*currentCodeBlockInTreeAtBaseLevel)->contextLevel = firstNLCsentenceInFullSentence->indentation+1;
						#endif
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
	#ifndef NLC_GENERATE_UNIQUE_CONTEXT_BLOCK_FOR_EACH_SENTENCE_LOGICAL_CONDITIONS_FOR_LOOPS
	#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
	if(logicalConditionOperator == NLC_LOGICAL_CONDITION_OPERATIONS_FOR)
	{
		generateContextBlocksVariables->setCodeBlockInTreeAtBaseLevel = true;
	}
	#endif
	#endif

	#ifdef NLC_DEBUG
	//cout << "foundChildEntity = " << foundChildEntity << endl;
	//cout << "childEntity = " << (*childEntity)->entityName << endl;
	#endif

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
		#ifdef NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY_BASIC
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

#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_BASED_ON_ACTIONS_BASIC
bool checkIfPhraseContainsAction(vector<GIAentityNode*>* entityNodesActiveListComplete, int sentenceIndex, GIAentityNode** logicalConditionOperationObject)
{
	bool phraseContainsAction = false;
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode* entity = (*entityIter);
		if(checkSentenceIndexParsingCodeBlocks(entity, sentenceIndex, false))
		{
			if(entity->isAction || (entity->isConcept && entity->isActionConcept))
			{
				phraseContainsAction = true;
				*logicalConditionOperationObject = entity;
			}
		}
	}
	return phraseContainsAction;
}
#endif

#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_BASED_ON_CONCEPTS
#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_BASED_ON_CONCEPTS_BASIC
bool checkIfPhraseContainsConceptWithDefinitionLink(vector<GIAentityNode*>* entityNodesActiveListComplete, int sentenceIndex, GIAentityNode** logicalConditionOperationObject)
{
	bool phraseContainsConceptWithDefinitionLink = false;
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode* entity = (*entityIter);
		if(checkSentenceIndexParsingCodeBlocks(entity, sentenceIndex, false))
		{
			if(entity->entityType == GIA_ENTITY_TYPE_TYPE_CONCEPT)
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
								phraseContainsConceptWithDefinitionLink = true;
								*logicalConditionOperationObject = entity;
							}
							else
							{
								cout << "checkIfPhraseContainsConceptWithDefinitionLink{} warning: !(!isDefiniteEntity(entity)) && !isDefiniteEntity(definitionEntityTemp))" << endl;
							}
						}
					}
				}
				/*OLD: before 1n5b update;
				if(!(entity->entityNodeDefinitionList->empty()))
				{
					phraseContainsConcept = true;
					*logicalConditionOperationObject = entity;
				}
				*/
			}
		}
	}
	return phraseContainsConceptWithDefinitionLink;
}
#else
bool checkIfPhraseContainsConcept(vector<GIAentityNode*>* entityNodesActiveListComplete, int sentenceIndex, GIAentityNode** logicalConditionOperationObject)
{
	bool phraseContainsConcept = false;
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode* entity = (*entityIter);
		if(checkSentenceIndexParsingCodeBlocks(entity, sentenceIndex, false))
		{
			if(entity->entityType == GIA_ENTITY_TYPE_TYPE_CONCEPT)
			{
				phraseContainsConcept = true;
				*logicalConditionOperationObject = entity;

				for(vector<GIAentityConnection*>::iterator iter = entity->entityNodeDefinitionReverseList->begin(); iter < entity->entityNodeDefinitionReverseList->end(); iter++)
				{
					GIAentityConnection* definitionConnection = *iter;
					GIAentityNode* definitionChildEntity =  definitionConnection->entity;
					if(definitionChildEntity->sentenceIndexTemp == sentenceIndex)	//note (with USE_NLC) separate concept entites are created for logical condition NLP parsable phrases (GIA advanced referencing is not applied), therefore a direct test of sentenceIndexTemp can be made
					{
						if(!(definitionConnection->sameReferenceSet))
						{
							#ifdef GIA_TRANSLATOR_INTERPRET_PRENOMINAL_MODIFIER_SUBCLASSES_ENABLE_INCONSISTENT_REFERENCING
							//ignore additional subclass concepts/definitions created by GIA when parsing NLC logical condition statements (eg alsation_dog for "If the dog is an alsation")
							if((definitionChildEntity->entityType == GIA_ENTITY_TYPE_TYPE_CONCEPT) && (entity->isSubClass))
							{
								phraseContainsConcept = false;
							}
							#endif
							if(definitionChildEntity->entityType != GIA_ENTITY_TYPE_TYPE_CONCEPT)
							{
								phraseContainsConcept = false;	//this is absolutely required for NLC_TRANSLATOR_LOGICAL_CONDITIONS_BOOLEAN_STATEMENTS_INTERPRET_SUBJECT_AND_OBJECT_INDEPENDENTLY_DEFINITIONS/NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_BASED_ON_CONCEPTS_BASIC_REDEFINITIONS
							}
						}
					}
				}
			}
		}
	}
	return phraseContainsConcept;
}
#endif

#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_BASED_ON_CONCEPTS_BASIC_REDEFINITIONS
bool checkIfPhraseContainsSubstanceWithDefinitionLink(vector<GIAentityNode*>* entityNodesActiveListComplete, int sentenceIndex, GIAentityNode** logicalConditionOperationObject, GIAentityNode** definitionEntity)
{
	bool phraseContainsSubstanceWithDefinitionLink = false;
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode* entity = (*entityIter);
		if(checkSentenceIndexParsingCodeBlocks(entity, sentenceIndex, false))
		{
			if(entity->entityType == GIA_ENTITY_TYPE_TYPE_SUBSTANCE)
			{
				for(vector<GIAentityConnection*>::iterator iter = entity->entityNodeDefinitionList->begin(); iter < entity->entityNodeDefinitionList->end(); iter++)
				{
					GIAentityConnection* definitionConnection = *iter;
					GIAentityNode* definitionEntityTemp = definitionConnection->entity;
					if(definitionConnection->sentenceIndexTemp == sentenceIndex)	//note (with USE_NLC) separate concept entites are created for logical condition NLP parsable phrases (GIA advanced referencing is not applied), therefore a direct test of sentenceIndexTemp can be made
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
									{//ignore concept definitions for for entities of same name
										phraseContainsSubstanceWithDefinitionLink = true;
										*logicalConditionOperationObject = entity;
										*definitionEntity = definitionEntityTemp;
										#ifdef NLC_DEBUG
										//cout << "checkIfPhraseContainsSubstanceWithDefinitionLink: = " << entity->entityName << endl;
										//cout << "entity = " << entity->entityName << endl;
										//cout << "definitionEntity = " << definitionEntityTemp->entityName << endl;
										#endif
									}
								}
								else
								{
									cout << "checkIfPhraseContainsSubstanceWithDefinitionLink{} warning: !(isDefiniteEntity(entity) || foundDefiniteParentOfEntity))" << endl;
								}
							}
							else
							{
								cout << "checkIfPhraseContainsSubstanceWithDefinitionLink{} warning: isDefiniteEntity(definitionEntityTemp))" << endl;
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
#endif


void setDummyReferenceSetIDforAllEntitiesInPhrase(vector<GIAentityNode*>* entityNodesActiveListComplete, int sentenceIndex)
{
	#ifdef NLC_DEBUG
	//cout << "setDummyReferenceSetIDforAllEntitiesInPhrase: " << endl;
	#endif
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode* entity = (*entityIter);
		if(checkSentenceIndexParsingCodeBlocks(entity, sentenceIndex, false))
		{
			entity->referenceSetID = NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_BASED_ON_ACTIONS_OR_NETWORK_INDEXES_DUMMY_REFERENCE_SET_ID;
			#ifdef NLC_DEBUG
			//cout << "setDummyReferenceSetIDforAllEntitiesInPhrase{}:" << endl;
			//cout << "entity = " << entity->entityName << endl;
			//cout << "entity->isNetworkIndex = " << entity->isNetworkIndex << endl;
			#endif
		}
	}
}


bool readParsablePhraseEntryEntityChecks(GIAentityNode* entity)
{
	bool result = false;
	if(!(entity->entityType == GIA_ENTITY_TYPE_TYPE_NETWORK_INDEX) && !(entity->entityType == GIA_ENTITY_TYPE_TYPE_CONDITION))
	{
		result = true;
	}
	return result;
}

#ifdef NLC_PREPROCESSOR_MATH_REPLACE_NUMERICAL_VARIABLES_NAMES_FOR_NLP
bool findDummyNumberAndReplaceWithOriginalNumericalVariableName(vector<GIAentityNode*>* entityNodesActiveListComplete, int sentenceIndex, int dummyNumber, string numericalVariableName)
{
	bool result = true;
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode* entity = (*entityIter);
		if(checkSentenceIndexParsingCodeBlocks(entity, sentenceIndex, false))
		{
			if(entity->quantityNumber == dummyNumber)
			{
				#ifdef NLC_DEBUG
				//cout << "findDummyNumberAndReplaceWithOriginalNumericalVariableName{}: " << endl;
				//cout << "entity->quantityNumber = " << entity->quantityNumber << endl;
				//cout << "dummyNumber = " << dummyNumber << endl;
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

#endif
