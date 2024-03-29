 /*******************************************************************************
 *
 * License: GNU Affero General Public License version 3 (AGPLv3)
 *
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: NLCtranslatorCodeBlocksLogicalConditions.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2022 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler
 * Project Version: 2p1a 05-June-2022
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 * /
 *******************************************************************************/


#include "NLCtranslatorCodeBlocksLogicalConditions.hpp"

#ifdef NLC_TRANSLATOR_LOGICAL_CONDITIONS_FOR_LOOP_ADD_ENTITY_TO_NEW_CONTEXT_LIST
GIAentityNode* logicalConditionForLoopPrimaryEntityTemp;
#endif

#ifdef NLC_PREPROCESSOR_MATH
bool NLCtranslatorCodeBlocksLogicalConditionsClass::generateCodeBlocksFromMathText(NLCcodeblock** currentCodeBlockInTree, map<int, vector<GIAentityNode*>*>::iterator sentenceIterFirstInFullSentence, int sentenceIndex, NLCpreprocessorSentence* fullSentence, const string NLCfunctionName)
{
	bool result = true;

	NLCcodeblock* currentCodeBlockInTreeAtBaseLevel = *currentCodeBlockInTree;
	string whileLogicalConditionConjunctionBooleanName = NLCcodeBlockClass.generateWhileLogicalConditionConjunctionBooleanName(fullSentence->indentation);

	#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
	if(fullSentence->hasLogicalConditionOperator)
	{
		NLCcodeblock* currentCodeBlockAtStartOfLogicalConditionCommand = *currentCodeBlockInTree;
		NLCcodeblock* currentCodeBlockAtStartOfLogicalConditionCommandForLoop = NULL;
		if(fullSentence->logicalConditionOperator == NLC_LOGICAL_CONDITION_OPERATIONS_WHILE)
		{
			*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockDeclareNewBoolVar(*currentCodeBlockInTree, whileLogicalConditionConjunctionBooleanName, true);
			*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockWhileHasBool(*currentCodeBlockInTree, whileLogicalConditionConjunctionBooleanName);
			*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockSetBoolVar(*currentCodeBlockInTree, whileLogicalConditionConjunctionBooleanName, false);
		}

		//CHECKTHIS; is NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE required for non-logical condition mathText?
		if((fullSentence->logicalConditionOperator == NLC_LOGICAL_CONDITION_OPERATIONS_IF) || (fullSentence->logicalConditionOperator == NLC_LOGICAL_CONDITION_OPERATIONS_WHILE) || (fullSentence->logicalConditionOperator == NLC_LOGICAL_CONDITION_OPERATIONS_FOR))
		{
			int caseIndex = 0;
			int currentLevel = fullSentence->indentation;
			int currentLogicalConditionOperator = fullSentence->logicalConditionOperator;
			bool stillFindingLogicalConditionAtCurrentLevel = true;
			NLCpreprocessorSentence* currentSentence = fullSentence;
			map<int, vector<GIAentityNode*>*>::iterator sentenceIter = sentenceIterFirstInFullSentence;
			while(stillFindingLogicalConditionAtCurrentLevel)
			{//this loop is only required by NLC_LOGICAL_CONDITION_OPERATIONS_IF (it is not used by NLC_LOGICAL_CONDITION_OPERATIONS_WHILE and NLC_LOGICAL_CONDITION_OPERATIONS_FOR)


				#ifdef NLC_PREPROCESSOR_MATH_USE_LOGICAL_CONDITION_OPERATIONS_ADVANCED_BACKWARDS_COMPATIBLE_VARIABLE_NAMES
				if(fullSentence->logicalConditionOperator != NLC_LOGICAL_CONDITION_OPERATIONS_FOR)
				{
					//use the same logical condition check naming scheme as NLC_LOGICAL_CONDITION_OPERATIONS_ADVANCED;
					string logicalConditionConjunctionBooleanName = NLCcodeBlockClass.generateLogicalConditionConjunctionBooleanName(currentSentence->indentation, caseIndex, NLC_LOGICAL_CONDITION_OPERATIONS_IF);
					*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockDeclareNewBoolArray(*currentCodeBlockInTree, logicalConditionConjunctionBooleanName, false);
				}
				#endif

				bool isLogicalConditionOperatorAtCurrentLevel = false;
				if(fullSentence->logicalConditionOperator == NLC_LOGICAL_CONDITION_OPERATIONS_IF)
				{
					if(currentSentence == fullSentence)
					{
						isLogicalConditionOperatorAtCurrentLevel = true;
					}
					else if(currentSentence->hasLogicalConditionOperator)
					{
						if(currentSentence->indentation == fullSentence->indentation)
						{
							if((currentSentence->logicalConditionOperator > fullSentence->logicalConditionOperator) || (currentSentence->logicalConditionOperator == NLC_LOGICAL_CONDITION_OPERATIONS_ELSE_IF))	//allow multiple else if statements
							{
								isLogicalConditionOperatorAtCurrentLevel = true;
							}
							else
							{
								stillFindingLogicalConditionAtCurrentLevel = false;
							}
						}
						else if(currentSentence->indentation > fullSentence->indentation)
						{
							//gone up a level, ignore all logical condition operators
						}
						else if(currentSentence->indentation < fullSentence->indentation)
						{
							//gone down (back) a level; quit search for logical Condition operator sentences at current level (if, else if, else)
							stillFindingLogicalConditionAtCurrentLevel = false;
						}
					}
				}
				else
				{//while and for loops do not use cases (only if statements use cases)
					isLogicalConditionOperatorAtCurrentLevel = true;	//NB currentSentence == fullSentence
					stillFindingLogicalConditionAtCurrentLevel = false;
				}


				if(isLogicalConditionOperatorAtCurrentLevel)
				{
					int sentenceIndexOfFullSentence = currentSentence->firstNLPparsablePhraseInList->sentenceIndex;

					if((fullSentence->logicalConditionOperator == NLC_LOGICAL_CONDITION_OPERATIONS_FOR) && (currentSentence->mathTextNLPparsablePhraseTotal > 1))
					{
						//assume "and" conjunction(s) has been specified; eg "For all baskets in the house and apples in the tree, eat the pie."
					}

					if(currentSentence->mathTextNLPparsablePhraseTotal > 0)
					{
						NLCpreprocessorParsablePhrase* parsablePhrase = currentSentence->firstNLPparsablePhraseInList;

						map<int, vector<GIAentityNode*>*>::iterator parsablePhraseIter = sentenceIter;
						for(int phraseIndex=0; phraseIndex<currentSentence->mathTextNLPparsablePhraseTotal; phraseIndex++)
						{
							vector<GIAentityNode*>* entityNodesActiveListParsablePhrase = parsablePhraseIter->second;

							if(parsablePhrase->mathTextNLPparsablePhraseIndex != phraseIndex)
							{
								cout << "generateCodeBlocksFromMathText{} error: (currentSentence->mathTextNLPparsablePhraseIndex != i)" << endl;
							}
							if(fullSentence->logicalConditionOperator == NLC_LOGICAL_CONDITION_OPERATIONS_FOR)
							{
								if(!generateCodeBlocksFromMathTextNLPparsablePhraseLogicalConditionFor(currentCodeBlockInTree, entityNodesActiveListParsablePhrase, parsablePhrase->sentenceIndex, currentSentence, parsablePhrase, phraseIndex, &currentCodeBlockAtStartOfLogicalConditionCommandForLoop, fullSentence))
								{
									result = false;
								}
							}
							else
							{
								GIAentityNode* definitionRelationshipObjectEntity = NULL;
								GIAentityNode* logicalConditionOperationObject = NULL;
								#ifdef NLC_LOGICAL_CONDITION_OPERATIONS_BASED_ON_ACTIONS_BASIC
								if(checkIfPhraseContainsAction(entityNodesActiveListParsablePhrase, parsablePhrase->firstNLPparsablePhraseInList->sentenceIndex, &logicalConditionOperationObject))
								{//eg "The sun fights. / If the sun fights, the dog is happy."

									string parsablePhraseReferenceName = NLCpreprocessorSentenceClass.generateMathTextNLPparsablePhraseReference(currentSentence->firstNLPparsablePhraseInList->sentenceIndex, parsablePhrase);
									*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockDeclareNewBoolVar(*currentCodeBlockInTree, parsablePhraseReferenceName, false);

									setDummyReferenceSetIDforAllEntitiesInPhrase(entityNodesActiveListParsablePhrase, parsablePhrase->sentenceIndex);	//this is required for searchForEquivalentSubnetToIfStatement{}
									GIAentityNode* actionEntityCompare = logicalConditionOperationObject;	//if statement comparison...
									GIAentityNode* actionEntityCompareNetworkIndex = GIAtranslatorOperations.getPrimaryNetworkIndexNodeDefiningInstance(actionEntityCompare);
									if(NLCtranslatorCodeBlocksLogicalConditionsAdvanced.searchForEquivalentSubnetToIfStatement(actionEntityCompareNetworkIndex, logicalConditionOperationObject, false))
									{
										*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockSetBoolVar(*currentCodeBlockInTree, parsablePhraseReferenceName, true);
									}
								} else
								#endif
								#ifdef NLC_LOGICAL_CONDITION_OPERATIONS_BASED_ON_CONCEPTS
								#ifdef NLC_LOGICAL_CONDITION_OPERATIONS_BASED_ON_CONCEPTS_BASIC
								if(checkIfPhraseContainsConceptWithDefinitionLink(entityNodesActiveListParsablePhrase, parsablePhrase->sentenceIndex, &logicalConditionOperationObject))
								#else
								if(checkIfPhraseContainsConcept(entityNodesActiveListParsablePhrase, parsablePhrase->sentenceIndex, &logicalConditionOperationObject))
								#endif
								{//eg "Red dogs are pies. / If red dogs are pies, eat the cabbage."

									//logical operations on concepts are performed by NLC (code is not generated for them by NLC as they are not performed at runtime) - eg If red dogs are/[!NLC_LOGICAL_CONDITION_OPERATIONS_BASED_ON_CONCEPTS_BASIC:]have pies, eat the cabbage.	[as opposed to: "if the red dog is the/a pie, eat the cabbage"]
									//verify the truth of the if statement now (if the statement is false, disable all classStructure formation based on condition subject subset)

									string parsablePhraseReferenceName = NLCpreprocessorSentenceClass.generateMathTextNLPparsablePhraseReference(currentSentence->firstNLPparsablePhraseInList->sentenceIndex, parsablePhrase);
									*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockDeclareNewBoolVar(*currentCodeBlockInTree, parsablePhraseReferenceName, false);

									setDummyReferenceSetIDforAllEntitiesInPhrase(entityNodesActiveListParsablePhrase, parsablePhrase->sentenceIndex);	//this is required for searchForEquivalentSubnetToIfStatement{}
									GIAentityNode* conceptEntityCompare = logicalConditionOperationObject;	//if statement comparison...
									GIAentityNode* conceptEntityCompareNetworkIndex = GIAtranslatorOperations.getPrimaryNetworkIndexNodeDefiningInstance(conceptEntityCompare);
									if(NLCtranslatorCodeBlocksLogicalConditionsAdvanced.searchForEquivalentSubnetToIfStatement(conceptEntityCompareNetworkIndex, logicalConditionOperationObject, true))	//searches for previous "red dogs are pies"
									{
										*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockSetBoolVar(*currentCodeBlockInTree, parsablePhraseReferenceName, true);
									}

								} else
								#ifdef NLC_LOGICAL_CONDITION_OPERATIONS_BASED_ON_CONCEPTS_BASIC_REDEFINITIONS
								if(checkIfPhraseContainsSubstanceWithDefinitionLink(entityNodesActiveListParsablePhrase, parsablePhrase->sentenceIndex, &logicalConditionOperationObject, &definitionRelationshipObjectEntity))
								{//eg "The dog is an alsation. / If the dog is an alsation, eat the cabbage."

									NLCcodeblock* currentCodeBlockAtStartOfparsablePhrase = *currentCodeBlockInTree;

									string parsablePhraseReferenceName = NLCpreprocessorSentenceClass.generateMathTextNLPparsablePhraseReference(currentSentence->firstNLPparsablePhraseInList->sentenceIndex, parsablePhrase);
									*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockDeclareNewBoolVar(*currentCodeBlockInTree, parsablePhraseReferenceName, false);

									GIAentityNode* parentEntity = NLCtranslatorCodeBlocksOperations.getParent(logicalConditionOperationObject, sentenceIndex);
									NLCgenerateContextBlocksVariables generateContextBlocksVariables;
									generateContextBlocksVariables.onlyGenerateContextBlocksIfConnectionsParsedForNLCorSameReferenceSet = false;
									generateContextBlocksVariables.searchConceptsForChildren = false;	//added 1n5g (only check the explicit variable for definition)
									bool generatedContextBlocks = NLCtranslatorCodeBlocksOperations.generateContextBlocks(currentCodeBlockInTree, parentEntity, sentenceIndex, &generateContextBlocksVariables, false, NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION);	//check if should parse categories here
									//bool generatedContextBlocks = generateContextBlocksSimple(currentCodeBlockInTree, parentEntity, sentenceIndex, &generateContextBlocksVariables, false, NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION);	//check if should parse categories here

									//eg If the dog is an alsation, eat the cabbage
									*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockCheckParentClassNameExecuteFunction1(*currentCodeBlockInTree, logicalConditionOperationObject, definitionRelationshipObjectEntity->entityName);

									//eg If the dog is a red alsation, eat the cabbage
									if(NLCtranslatorCodeBlocksOperations.createCodeBlockForStatements(currentCodeBlockInTree, NLCitemClass.generateInstanceName(logicalConditionOperationObject), definitionRelationshipObjectEntity, sentenceIndex, &generateContextBlocksVariables))
									{

									}

									*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockSetBoolVar(*currentCodeBlockInTree, parsablePhraseReferenceName, true);
									*currentCodeBlockInTree = NLCcodeBlockClass.getLastCodeBlockInLevel(currentCodeBlockAtStartOfparsablePhrase);
								} else
								#endif
								#endif
								if(!generateCodeBlocksFromMathTextNLPparsablePhrase(currentCodeBlockInTree, entityNodesActiveListParsablePhrase, parsablePhrase->sentenceIndex, currentSentence, parsablePhrase, phraseIndex, caseIndex))
								{
									result = false;
								}
							}
							parsablePhrase = parsablePhrase->next;
							parsablePhraseIter++;
						}
					}
					caseIndex++;
					currentSentence = currentSentence->next;
					sentenceIter++;
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
			
			if(fullSentence->logicalConditionOperator == NLC_LOGICAL_CONDITION_OPERATIONS_IF)
			{
				currentCodeBlockInTreeAtBaseLevel = *currentCodeBlockInTree;	//currentCodeBlockInTreeAtBaseLevel will point to NLC_CODEBLOCK_TYPE_MATHTEXT_WITH_LOGICAL_OPERATOR (113) once set
			}
			else if(fullSentence->logicalConditionOperator == NLC_LOGICAL_CONDITION_OPERATIONS_WHILE)
			{
				currentCodeBlockInTreeAtBaseLevel = NLCcodeBlockClass.getLastSetCodeBlockInLevel(currentCodeBlockAtStartOfLogicalConditionCommand);	//currentCodeBlockInTreeAtBaseLevel will point to NLC_CODEBLOCK_TYPE_WHILE (114)?
			}
			else if(fullSentence->logicalConditionOperator == NLC_LOGICAL_CONDITION_OPERATIONS_FOR)
			{
				#ifdef NLC_TRANSLATOR_LOGICAL_CONDITIONS_SINGLE_SENTENCE_MULTIPLE_LEVEL_FOR_LOOPS_OLD
				currentCodeBlockInTreeAtBaseLevel = currentCodeBlockAtStartOfLogicalConditionCommandForLoop;
				#else
				currentCodeBlockInTreeAtBaseLevel = NLCcodeBlockClass.getLastSetCodeBlockInLevel(currentCodeBlockAtStartOfLogicalConditionCommand);	//currentCodeBlockInTreeAtBaseLevel will point to NLC_CODEBLOCK_TYPE_FOR_GENERIC_LIST (115)
				#ifdef NLC_ADVANCED_REFERENCING_MONITOR_CONTEXT
				NLCcodeblock* currentCodeBlockInTreeAtBaseLevelForLoop = NLCcodeBlockClass.getLastSetCodeBlockInLevel(currentCodeBlockAtStartOfLogicalConditionCommandForLoop);
				currentCodeBlockInTreeAtBaseLevelForLoop->isLogicalCondition = true;
				currentCodeBlockInTreeAtBaseLevelForLoop->contextLevel = fullSentence->indentation+1;
				#endif
				#endif
			}
		}
		else if((fullSentence->logicalConditionOperator == NLC_LOGICAL_CONDITION_OPERATIONS_ELSE_IF) || (fullSentence->logicalConditionOperator == NLC_LOGICAL_CONDITION_OPERATIONS_ELSE))
		{
			currentCodeBlockInTreeAtBaseLevel = *currentCodeBlockInTree;	//currentCodeBlockInTreeAtBaseLevel will point to NLC_CODEBLOCK_TYPE_MATHTEXT_WITH_LOGICAL_OPERATOR (113) once set
		}
		else
		{
			cerr << "generateCodeBlocksFromMathText{} error: illegal fullSentence->logicalConditionOperator" << endl;
			exit(EXIT_ERROR);
		}
		
		#ifdef NLC_ADVANCED_REFERENCING_MONITOR_CONTEXT
		if(fullSentence->logicalConditionOperator != NLC_LOGICAL_CONDITION_OPERATIONS_FOR)
		{
			//cout << "currentCodeBlockInTreeAtBaseLevel->codeBlockType = " << currentCodeBlockInTreeAtBaseLevel->codeBlockType << endl;
			(*currentCodeBlockInTree)->isLogicalCondition = true;
			(*currentCodeBlockInTree)->contextLevel = fullSentence->indentation+1;
		}
		#endif
	}
	else
	{
	#endif

		NLCpreprocessorParsablePhrase* parsablePhrase = fullSentence->firstNLPparsablePhraseInList;
		map<int, vector<GIAentityNode*>*>::iterator parsablePhraseIter = sentenceIterFirstInFullSentence;
		for(int phraseIndex=0; phraseIndex<fullSentence->mathTextNLPparsablePhraseTotal; phraseIndex++)
		{
			vector<GIAentityNode*>* entityNodesActiveListParsablePhrase = parsablePhraseIter->second;
			if(parsablePhrase->mathTextNLPparsablePhraseIndex != phraseIndex)
			{
				cout << "generateCodeBlocksFromMathText{} error: (currentSentence->mathTextNLPparsablePhraseIndex != i)" << endl;
			}
			if(!generateCodeBlocksFromMathTextNLPparsablePhrase(currentCodeBlockInTree, entityNodesActiveListParsablePhrase, parsablePhrase->sentenceIndex, fullSentence, parsablePhrase, phraseIndex, 0))
			{
				result = false;
			}
			parsablePhraseIter++;
			parsablePhrase = parsablePhrase->next;
		}

	#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
	}
	#endif

	#ifdef NLC_MATH_OBJECTS_ADVANCED_USE_UNIQUE_OPERATORS
	int progLang = NLCprintDefs.getProgLang();	//CHECKTHIS - note this is an unusual implementation
	fullSentence->mathText = SHAREDvars.replaceAllOccurancesOfString(&(fullSentence->mathText), NLC_PREPROCESSOR_MATH_OPERATOR_STRING_EQUALS_TEST_WITH_PADDING, progLangStringEqualsTest[progLang]);
	fullSentence->mathText = SHAREDvars.replaceAllOccurancesOfString(&(fullSentence->mathText), NLC_PREPROCESSOR_MATH_OPERATOR_STRING_ADD_WITH_PADDING, progLangStringAdd[progLang]);
	#endif

	#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
	if(fullSentence->hasLogicalConditionOperator)
	{
		if(fullSentence->logicalConditionOperator == NLC_LOGICAL_CONDITION_OPERATIONS_WHILE)
		{
			fullSentence->mathText.replace(0, string(NLC_LOGICAL_CONDITION_OPERATIONS_WHILE_STRING).length(), string(NLC_LOGICAL_CONDITION_OPERATIONS_IF_STRING));	//replace "while" with "if" for the purposes of generating final code (while loop has already been defined)
		}

		if(fullSentence->logicalConditionOperator != NLC_LOGICAL_CONDITION_OPERATIONS_FOR)
		{
			*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockMathTextWithLogicalOperator(*currentCodeBlockInTree, fullSentence->mathText);
		}

		if(fullSentence->logicalConditionOperator == NLC_LOGICAL_CONDITION_OPERATIONS_WHILE)
		{
			*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockSetBoolVar(*currentCodeBlockInTree, whileLogicalConditionConjunctionBooleanName, true);
		}

		#ifdef NLC_ADVANCED_REFERENCING_MONITOR_CONTEXT
		*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlocksDeclareContextList(*currentCodeBlockInTree, fullSentence->indentation+1);
		#ifdef NLC_TRANSLATOR_LOGICAL_CONDITIONS_FOR_LOOP_ADD_ENTITY_TO_NEW_CONTEXT_LIST
		if(fullSentence->logicalConditionOperator == NLC_LOGICAL_CONDITION_OPERATIONS_FOR)
		{
			if(result)	//verify that logicalConditionForLoopPrimaryEntityTemp has been set by generateCodeBlocksFromMathTextNLPparsablePhraseLogicalConditionFor (ie foundParsablePhrase)
			{
				*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlocksAddEntityToContextLevelListExecuteFunction(*currentCodeBlockInTree, NLCcodeBlockClass.getCurrentLogicalConditionLevel()+1, logicalConditionForLoopPrimaryEntityTemp, sentenceIndex);
			}
		}
		#endif
		#endif

		if(fullSentence->next != NULL)
		{
			NLCpreprocessorSentence* nextNLCfullSentenceInList = fullSentence->next;


			currentCodeBlockInTreeAtBaseLevel = currentCodeBlockInTreeAtBaseLevel->next;
			
			if(nextNLCfullSentenceInList->indentation == (fullSentence->indentation + 1))
			{
				//do not, just record the in the tree
				NLCtranslatorCodeBlocksLogicalConditionsAdvanced.setCodeBlockAtPreviousLogicalConditionBaseLevelArray(fullSentence->indentation, currentCodeBlockInTreeAtBaseLevel);
			}
			else if(nextNLCfullSentenceInList->indentation <= fullSentence->indentation)
			{
				*currentCodeBlockInTree = currentCodeBlockInTreeAtBaseLevel;
				//NB if(nextNLCfullSentenceInList->indentation < fullSentence->indentation) will be processed later by generateCodeBlocks{}
			}
			else
			{
				cout << "NLC_PREPROCESSOR generateCodeBlocksPart2logicalConditions{} error: invalid indentation of nextNLCfullSentenceInList, sentenceIndex = " << sentenceIndex << endl;
				cout << "nextNLCfullSentenceInList->indentation <= fullSentence->indentation + 1" << endl;
				cout << "fullSentence->indentation = " << fullSentence->indentation << endl;
				cout << "nextNLCfullSentenceInList->indentation = " << nextNLCfullSentenceInList->indentation << endl;
			}
		}

	}
	else
	{
	#endif

		*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockMathTextLine(*currentCodeBlockInTree, fullSentence->mathText);

		#ifdef NLC_MATH_OBJECTS
		#ifndef NLC_MATH_OBJECTS_TEST_NULL_POINTER_MAINTAIN_CONTEXT
		if(fullSentence->mathTextIdentifiesMathValue)
		{
			*currentCodeBlockInTree = NLCcodeBlockClass.getLastCodeBlockInLevel(currentCodeBlockInTreeAtBaseLevel);
		}
		#endif
		#endif

	#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
	}
	#endif


	return result;
}

bool NLCtranslatorCodeBlocksLogicalConditionsClass::generateCodeBlocksFromMathTextNLPparsablePhrase(NLCcodeblock** currentCodeBlockInTree, vector<GIAentityNode*>* entityNodesActiveListParsablePhrase, int sentenceIndex, NLCpreprocessorSentence* currentFullSentence, const NLCpreprocessorParsablePhrase* parsablePhrase, const int phraseIndex, const int caseIndex)
{
	bool foundParsablePhrase = false;


	//for NLP parsable phrase;
	//eg1 "the number of chickens" in "if(the number of chickens > the number of apples...)"
	//eg2 "the number of red dogs" in "X = Y * (the number of red dogs) + the number of blue birds near the mountain"
	NLCcodeblock* currentCodeBlockAtStartOfparsablePhrase = *currentCodeBlockInTree;
	string parsablePhraseReferenceName = NLCpreprocessorSentenceClass.generateMathTextNLPparsablePhraseReference(currentFullSentence->firstNLPparsablePhraseInList->sentenceIndex, parsablePhrase);	//parsablePhraseGenerateNumberOfElementCounterName
	*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockDeclareNewIntVar(*currentCodeBlockInTree, parsablePhraseReferenceName, 0);	//?this will need to be changed to createCodeBlockDeclareNewIntArray in the future to support multiple cases (ie if, else if, else)
	#ifdef NLC_GENERATE_UNIQUE_CONTEXT_BLOCK_FOR_EACH_SENTENCE_LOGICAL_CONDITIONS_PARSABLE_PHRASES
	NLCcodeblock* firstCodeBlockInPhrase = *currentCodeBlockInTree;
	*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlocksCreateContextBlock(*currentCodeBlockInTree);
	#endif

	//if !NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE, currently only accept entities with $qVar defined, eg "Number of red dogs". prep_of(number-4, dogs-7) [NLP] / _quantity(dog[8], _$qVar[1]) [GIA]
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListParsablePhrase->begin(); entityIter != entityNodesActiveListParsablePhrase->end(); entityIter++)
	{
		GIAentityNode* entity = (*entityIter);
		if(NLCcodeBlockClass.checkSentenceIndexParsingCodeBlocks(entity, sentenceIndex, false))
		{
			if(readParsablePhraseEntryEntityChecks(entity))
			{//redundant
				if(isNumberOf(entity))
				{

					if(foundParsablePhrase)
					{
						cout << "generateCodeBlocksFromMathTextNLPparsablePhrase{} error: more than one parsable phrase primary entity found" << endl;
					}
					foundParsablePhrase = true;

					NLCgenerateContextBlocksVariables generateContextBlocksVariables;
					generateContextBlocksVariables.onlyGenerateContextBlocksIfConnectionsParsedForNLCorSameReferenceSet = false;
					
					#ifdef NLC_LOGICAL_CONDITION_OPERATIONS_SUPPORT_INDEFINITE_LOGICAL_CONDITION_OBJECTS
					if(!NLCcodeBlockClass.assumedToAlreadyHaveBeenDeclared(entity))
					{
						cout << "generateCodeBlocksFromMathTextNLPparsablePhrase{} error: isNumberOf entities must be definite " << endl;
					}
					//number of statements must be expressed using definite variables, but they will not be advanced referenced by GIA (and so must be located in the typeList)
						//"the number of x" will have already been declared, but is not advanced referenced, so much search the typeList
					#ifdef NLC_GENERATE_TYPE_LISTS
					entity->grammaticalDefiniteTemp = false;	//this triggers generateContextBlocks{} to execute createCodeBlockForOrInPropertyList{} on parent rather than createCodeBlockForOrInLocalList{}
					#endif
					if(!NLCcodeBlockClass.assumedToAlreadyHaveBeenDeclared(entity))
					{
						#ifdef NLC_GENERATE_TYPE_LISTS
						*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockForPropertyTypeClass(*currentCodeBlockInTree, entity);	//eg "If a house is green, do this", an instanceList (OLD: localList) for "a house" is assumed to have already been declared, one of which may be green, so search all house instanceLists within house typeList...
						//if at least one instanceList of type currentLogicalConditionObject has not previously been declared, then the code will result in a compilation error
						//if at least one instanceList of type currentLogicalConditionObject has previously been declared, but does not have the required properties (eg green), then the code will compile but the if statement will fail
						#else
						//entity->grammaticalDefiniteTemp = true;		//removed 1j15a, readded 1j15c, removed 1n22b
						entity->NLClocalListVariableHasBeenInitialised = true;		//added 1n22b
						#endif
					}
					#endif
					
					if(!NLCtranslatorCodeBlocksOperations.getParentAndGenerateContextBlocks(currentCodeBlockInTree, entity, sentenceIndex, &generateContextBlocksVariables))
					{
					}
					#ifdef NLC_GENERATE_TYPE_LISTS
					entity->grammaticalDefiniteTemp = true;
					#endif

					*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockIncrementIntVar(*currentCodeBlockInTree, parsablePhraseReferenceName);

					*currentCodeBlockInTree = NLCcodeBlockClass.getLastCodeBlockInLevel(currentCodeBlockAtStartOfparsablePhrase);
				}
			}
		}
	}
	if(!foundParsablePhrase)
	{
		#ifndef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
		cout << "generateCodeBlocksFromMathTextNLPparsablePhrase{} error: !foundParsablePhrase" << endl;
		#endif
		*currentCodeBlockInTree = NLCcodeBlockClass.clearCodeBlock(currentCodeBlockAtStartOfparsablePhrase);

		#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
		#ifdef NLC_MATH_OBJECTS


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

		int mathObjectVariableType = getMathObjectVariableTypeAfterGIA(entityNodesActiveListParsablePhrase, sentenceIndex, currentFullSentence, parsablePhrase);
		if(mathObjectVariableType == NLC_MATH_OBJECTS_VARIABLE_TYPE_BOOLEAN_STATEMENT)
		{
			#ifdef NLC_PREPROCESSOR_MATH_USE_LOGICAL_CONDITION_OPERATIONS_ADVANCED_BACKWARDS_COMPATIBLE_VARIABLE_NAMES
			parsablePhraseReferenceName = NLCcodeBlockClass.generateLogicalConditionConjunctionBooleanName(currentFullSentence->indentation, caseIndex, phraseIndex, NLC_LOGICAL_CONDITION_OPERATIONS_IF);
			#else
			*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockDeclareNewBoolVar(*currentCodeBlockInTree, parsablePhraseReferenceName, false);	//eg bool thedogistall = false;
			#endif
		}
		#ifdef NLC_MATH_OBJECTS
		else if((mathObjectVariableType == NLC_MATH_OBJECTS_VARIABLE_TYPE_NUMERICAL) || (mathObjectVariableType == NLC_MATH_OBJECTS_VARIABLE_TYPE_STRING) || (mathObjectVariableType == NLC_MATH_OBJECTS_VARIABLE_TYPE_BOOLEAN))
		{
			if(mathObjectVariableType == NLC_MATH_OBJECTS_VARIABLE_TYPE_NUMERICAL)
			{
				*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockDeclareNewDecimalPointerVar(*currentCodeBlockInTree, parsablePhraseReferenceName);	//eg double* thedogsvalue = NULL;
			}
			#ifdef NLC_MATH_OBJECTS_ADVANCED
			#ifdef NLC_MATH_OBJECTS_STRING
			else if(mathObjectVariableType == NLC_MATH_OBJECTS_VARIABLE_TYPE_STRING)
			{
				*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockDeclareNewStringPointerVar(*currentCodeBlockInTree, parsablePhraseReferenceName);	//eg string* thedogsvalue = NULL;
			}
			#endif
			#ifdef NLC_MATH_OBJECTS_BOOLEAN
			else if(mathObjectVariableType == NLC_MATH_OBJECTS_VARIABLE_TYPE_BOOLEAN)
			{
				*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockDeclareNewBooleanPointerVar(*currentCodeBlockInTree, parsablePhraseReferenceName);	//eg bool* thedogsvalue = NULL;
			}
			#endif
			#endif
		}
		#endif
		else if(mathObjectVariableType == NLC_MATH_OBJECTS_VARIABLE_TYPE_UNKNOWN)
		{
			#ifdef NLC_MATH_OBJECTS
			#ifdef NLC_MATH_OBJECTS_ADVANCED
			*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockDeclareNewGenericEntityPointerVar(*currentCodeBlockInTree, parsablePhraseReferenceName);	//NLCgenericEntityClass* thedogsvalue = NULL;
			#else
			cout << "generateCodeBlocksFromMathTextNLPparsablePhrase{} error: !NLC_MATH_OBJECTS_ADVANCED && (mathObjectVariableType == NLC_MATH_OBJECTS_VARIABLE_TYPE_UNKNOWN)" << endl;
			#endif
			#else
			cout << "generateCodeBlocksFromMathTextNLPparsablePhrase{} error: !NLC_MATH_OBJECTS && (mathObjectVariableType == NLC_MATH_OBJECTS_VARIABLE_TYPE_UNKNOWN)" << endl;			
			#endif
		}

		#ifdef NLC_GENERATE_UNIQUE_CONTEXT_BLOCK_FOR_EACH_SENTENCE_LOGICAL_CONDITIONS_PARSABLE_PHRASES
		firstCodeBlockInPhrase = *currentCodeBlockInTree;
		*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlocksCreateContextBlock(*currentCodeBlockInTree);
		#endif

		foundParsablePhrase = false;
		#ifdef NLC_TRANSLATOR_LOGICAL_CONDITIONS_BOOLEAN_STATEMENTS_INTERPRET_SUBJECT_AND_OBJECT_INDEPENDENTLY
		if(mathObjectVariableType == NLC_MATH_OBJECTS_VARIABLE_TYPE_BOOLEAN_STATEMENT)
		{//added 1t2a
			//this is required to parse both the subject and the object of the boolean statement independently
			NLCgenerateContextBlocksVariables generateContextBlocksVariablesLogicalConditionStatement;
			generateContextBlocksVariablesLogicalConditionStatement.logicalConditionStatement = true;
			if(NLCtranslatorCodeBlocksOperations.generateCodeBlocksPart3subjectObjectConnections(currentCodeBlockInTree, entityNodesActiveListParsablePhrase, sentenceIndex, &generateContextBlocksVariablesLogicalConditionStatement))
			{
				if(generateContextBlocksVariablesLogicalConditionStatement.negativeDetectedInContextBlocks)
				{
					int parsablePhraseReferenceNamePosInMathText = currentFullSentence->mathText.find(parsablePhraseReferenceName);
					if(parsablePhraseReferenceNamePosInMathText != CPP_STRING_FIND_RESULT_FAIL_VALUE)	//&& (parsablePhraseReferenceNamePosInMathText > 0
					{
						currentFullSentence->mathText.insert(parsablePhraseReferenceNamePosInMathText, 1, NLC_PREPROCESSOR_MATH_OPERATOR_NEGATIVE_CHAR);
					}
				}

				foundParsablePhrase = true;

				*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockSetBoolVar(*currentCodeBlockInTree, parsablePhraseReferenceName, true);		//eg thedogsvalue = true;

				*currentCodeBlockInTree = NLCcodeBlockClass.getLastCodeBlockInLevel(currentCodeBlockAtStartOfparsablePhrase);
			}
		}
		else
		{
		#endif
			for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListParsablePhrase->begin(); entityIter != entityNodesActiveListParsablePhrase->end(); entityIter++)
			{
				GIAentityNode* entity = (*entityIter);
				if(NLCcodeBlockClass.checkSentenceIndexParsingCodeBlocks(entity, sentenceIndex, false))
				{
					if(readParsablePhraseEntryEntityChecks(entity))
					{//required
						if(!isNumberOf(entity))	//CHECKTHIS
						{
							if(!foundParsablePhrase)
							{

								#ifdef NLC_TRANSLATOR_DO_NOT_REPARSE_CONTEXT_BLOCKS_IF_ALREADY_PARSED_DURING_ENTITY_INITIALISATION
								GIAentityNode* childEntity = NULL;
								NLCgenerateContextBlocksVariables generateContextBlocksVariables;
								parseLogicalConditionEntity(currentCodeBlockInTree, entity, sentenceIndex, (currentFullSentence->hasLogicalConditionOperator), &childEntity, &generateContextBlocksVariables);
								#else
								GIAentityNode* parentEntity = NLCtranslatorCodeBlocksOperations.getParent(entity, sentenceIndex);		//find both definite and indefinite parents; eg The dog's value = X / A dog's value = X

								//initialise parsing of indefinate entities (set how to intepret these, eg "a house")
								bool parentEntityWasNotDeclared = false;
								bool initialisedParent = false;
								#ifdef NLC_TRANSLATOR_LOGICAL_CONDITIONS_BOOLEAN_STATEMENTS_INTERPRET_SUBJECT_AND_OBJECT_INDEPENDENTLY
								cout << "generateCodeBlocksFromMathTextNLPparsablePhrase{}: error: NLC_TRANSLATOR_LOGICAL_CONDITIONS_BOOLEAN_STATEMENTS_INTERPRET_SUBJECT_AND_OBJECT_INDEPENDENTLY and indefinite entity detected during parse of math object parsable phrase" << endl;	
								#else
								if(!NLCcodeBlockClass.assumedToAlreadyHaveBeenDeclared(parentEntity))
								{
									parentEntityWasNotDeclared = true;
									if(currentFullSentence->hasLogicalConditionOperator)
									{
										#ifdef NLC_LOGICAL_CONDITION_OPERATIONS_SUPPORT_INDEFINITE_LOGICAL_CONDITION_OBJECTS
										//if/while statements can be expressed using either definite or indefinate variables, but if they indefinite they will not be advanced referenced by GIA (and so must be located in the typeList)
										#ifdef NLC_GENERATE_TYPE_LISTS
										//1i implementation
										*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockForPropertyTypeClass(*currentCodeBlockInTree, parentEntity);	//eg "If a house is green, do this", an instanceList (OLD: localList) for "a house" is assumed to have already been declared, one of which may be green, so search all house instanceLists within house typeList...
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
										if(NLCtranslatorCodeBlocksOperations.generateParentInitialisationCodeBlockWithChecks(currentCodeBlockInTree, parentEntity, sentenceIndex, false, false))
										{
											#ifdef NLC_TRANSLATOR_DO_NOT_REPARSE_CONTEXT_BLOCKS_IF_ALREADY_PARSED_DURING_ENTITY_INITIALISATION_BASIC
											initialisedParent = true;
											#endif
										}
									}
								}
								else
								{
									//eg The dog's value = X.
								}
								#endif
								GIAentityNode* childEntity = NULL;
								NLCgenerateContextBlocksVariables generateContextBlocksVariables;
								#ifdef NLC_TRANSLATOR_DO_NOT_REPARSE_CONTEXT_BLOCKS_IF_ALREADY_PARSED_DURING_ENTITY_INITIALISATION_BASIC
								if(initialisedParent)
								{
									bool foundChildEntity = false;
									childEntity = NLCcodeBlockClass.getSameReferenceSetSubstanceNonQualityChild(parentEntity, sentenceIndex, &foundChildEntity);
									if(foundChildEntity)
									{
										//NB even if NLC_LOCAL_LISTS_USE_INSTANCE_NAMES, the parent entity will not be more than 1 level above the child (as a new entity has been declared; eg "A dog's value = X.")
										#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_BLOCKS_FOR_PARENT_INITIALISATION_SPECIAL
										*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockForCategoryList(*currentCodeBlockInTree, entity, NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION, sentenceIndex);
										#else
										*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockForLocalList(*currentCodeBlockInTree, entity);
										#endif
									}
									else
									{
										#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_BLOCKS_FOR_PARENT_INITIALISATION_SPECIAL
										*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockForCategoryList(*currentCodeBlockInTree, *parentEntity, NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION, sentenceIndex);
										#else
										*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockForLocalList(*currentCodeBlockInTree, *parentEntity);
										#endif
										*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockForOrInPropertyList(*currentCodeBlockInTree, entity, NLCitemClass.generateInstanceName(*parentEntity));
									}
								}
								else
								{
								#endif
									generateContextBlocksVariables.onlyGenerateContextBlocksIfConnectionsParsedForNLCorSameReferenceSet = false;	//irrelevant (as no !sameReferenceSet connection)
									bool contextFound = parseParsablePhraseParent(currentCodeBlockInTree, sentenceIndex, parentEntity, &generateContextBlocksVariables, &childEntity, currentFullSentence->logicalConditionOperator);

								#ifdef NLC_TRANSLATOR_DO_NOT_REPARSE_CONTEXT_BLOCKS_IF_ALREADY_PARSED_DURING_ENTITY_INITIALISATION_BASIC
								}
								#endif
								#ifdef NLC_LOGICAL_CONDITION_OPERATIONS_SUPPORT_INDEFINITE_LOGICAL_CONDITION_OBJECTS
								if(currentFullSentence->hasLogicalConditionOperator)
								{
									if(parentEntityWasNotDeclared)
									{
										if(childEntity != parentEntity)
										{
											bool foundChildEntity = true;
											cout << "generateCodeBlocksFromMathTextNLPparsablePhrase{} error: !NLCcodeBlockClass.assumedToAlreadyHaveBeenDeclared(parentEntity) && foundChildEntity" << endl;
										}
									}
								}
								#endif
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

								#ifndef NLC_TRANSLATOR_LOGICAL_CONDITIONS_BOOLEAN_STATEMENTS_INTERPRET_SUBJECT_AND_OBJECT_INDEPENDENTLY
								if(mathObjectVariableType == NLC_MATH_OBJECTS_VARIABLE_TYPE_BOOLEAN_STATEMENT)
								{
									*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockSetBoolVar(*currentCodeBlockInTree, parsablePhraseReferenceName, true);		//eg thedogsvalue = true;
								}
								else 
								#endif
								#ifdef NLC_MATH_OBJECTS
								if((mathObjectVariableType == NLC_MATH_OBJECTS_VARIABLE_TYPE_NUMERICAL) || (mathObjectVariableType == NLC_MATH_OBJECTS_VARIABLE_TYPE_STRING) || (mathObjectVariableType == NLC_MATH_OBJECTS_VARIABLE_TYPE_BOOLEAN))
								{
									if(mathObjectVariableType == NLC_MATH_OBJECTS_VARIABLE_TYPE_NUMERICAL)
									{
										*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockSetDecimalPointerToEntityMathObjectNumericalValue(*currentCodeBlockInTree, parsablePhraseReferenceName, childEntity);		//eg thedogsvalue = &(childEntity->mathObjectNumericalValue);
										*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockSetMathObjectTypeAsNumerical(*currentCodeBlockInTree, childEntity);				//childEntity->mathObjectType = NLC_MATH_OBJECTS_VARIABLE_TYPE_NUMERICAL;
									}
									#ifdef NLC_MATH_OBJECTS_ADVANCED
									#ifdef NLC_MATH_OBJECTS_STRING
									else if(mathObjectVariableType == NLC_MATH_OBJECTS_VARIABLE_TYPE_STRING)
									{
										*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockSetStringPointerToEntityMathObjectStringValue(*currentCodeBlockInTree, parsablePhraseReferenceName, childEntity);		//eg thedogsvalue = &(childEntity->mathObjectStringValue);
										*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockSetMathObjectTypeAsString(*currentCodeBlockInTree, childEntity);				//childEntity->mathObjectType = NLC_MATH_OBJECTS_VARIABLE_TYPE_STRING;
									}
									#endif
									#ifdef NLC_MATH_OBJECTS_BOOLEAN
									else if(mathObjectVariableType == NLC_MATH_OBJECTS_VARIABLE_TYPE_BOOLEAN)
									{
										*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockSetBooleanPointerToEntityMathObjectBooleanValue(*currentCodeBlockInTree, parsablePhraseReferenceName, childEntity);		//eg thedogsvalue = &(childEntity->mathObjectBooleanValue);
										*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockSetMathObjectTypeAsBoolean(*currentCodeBlockInTree, childEntity);				//childEntity->mathObjectType = NLC_MATH_OBJECTS_VARIABLE_TYPE_BOOLEAN;
									}
									#endif
									#endif
									bool foundParsablePhraseInMathText = false;
									string parsablePhraseReferenceMathValue = NLCprintDefs.generateCodeEntityMathValuePointerText(parsablePhraseReferenceName, NLC_PROGRAMMING_LANGUAGE_DEFAULT);	//eg *childEntity
									currentFullSentence->mathText = SHAREDvars.replaceAllOccurancesOfString(&(currentFullSentence->mathText), parsablePhraseReferenceName, parsablePhraseReferenceMathValue, &foundParsablePhraseInMathText);	//"thedogsvalue" -> "*thedogsvalue"
								}
								#ifdef NLC_MATH_OBJECTS_ADVANCED
								else if(mathObjectVariableType == NLC_MATH_OBJECTS_VARIABLE_TYPE_UNKNOWN)
								{
									*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockSetGenericEntityPointerToEntity(*currentCodeBlockInTree, parsablePhraseReferenceName, childEntity);		//eg thedogsvalue = childEntity;
									currentFullSentence->mathText = generateAssignMathTextValueExecuteFunctionMathText(currentFullSentence, parsablePhraseReferenceName, (currentFullSentence->hasLogicalConditionOperator));	//replace "thedogsvalue = ..." with "assignMathObjectValue(thedogsvalue, ...)", replace "X = thedogsvalue" with "assignMathTextValue(X, thedogsvalue)" etc
								}
								#endif
								#endif

								foundParsablePhrase = true;
								if(!(currentFullSentence->hasLogicalConditionOperator))
								{
									currentFullSentence->mathTextIdentifiesMathValue = true;
								}

								*currentCodeBlockInTree = NLCcodeBlockClass.getLastCodeBlockInLevel(currentCodeBlockAtStartOfparsablePhrase);
							}
						}
						else
						{
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
				*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockTestDecimalPointerValue(*currentCodeBlockInTree, parsablePhraseReferenceName);			 //if(thedogsvalue == NULL) { cout << "error" << endl;}
				#else
				*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockCheckDecimalPointerValue(*currentCodeBlockInTree, parsablePhraseReferenceName);		 //if(thedogsvalue != NULL)
				#endif
			}
		}
		else
		{
			cout << "generateCodeBlocksFromMathTextNLPparsablePhrase{} error: !foundParsablePhrase" << endl;
			*currentCodeBlockInTree = NLCcodeBlockClass.clearCodeBlock(currentCodeBlockAtStartOfparsablePhrase);
		}
		#endif
		#endif
	}

	return foundParsablePhrase;
}

int NLCtranslatorCodeBlocksLogicalConditionsClass::getMathObjectVariableTypeAfterGIA(vector<GIAentityNode*>* entityNodesActiveListComplete, const int sentenceIndex, NLCpreprocessorSentence* currentFullSentence, const NLCpreprocessorParsablePhrase* parsablePhrase)
{
	bool foundBooleanStatementExpression = getMathObjectVariableTypeBooleanExpressionAfterGIA(entityNodesActiveListComplete, sentenceIndex);
	int mathObjectVariableType = getMathObjectVariableTypeSharedWrapper(foundBooleanStatementExpression, currentFullSentence, parsablePhrase);
	return mathObjectVariableType;
}
/*
int NLCtranslatorCodeBlocksLogicalConditionsClass::getMathObjectVariableTypeBeforeGIA(NLCpreprocessorSentence* currentFullSentence, const NLCpreprocessorParsablePhrase* parsablePhrase)
{
	bool foundBooleanStatementExpression = getMathObjectVariableTypeBooleanExpressionBeforeGIAestimate(parsablePhrase);
	int mathObjectVariableType = getMathObjectVariableTypeSharedWrapper(foundBooleanStatementExpression, currentFullSentence, parsablePhrase);
	return mathObjectVariableType;
}
*/

bool NLCtranslatorCodeBlocksLogicalConditionsClass::getMathObjectVariableTypeBooleanExpressionAfterGIA(vector<GIAentityNode*>* entityNodesActiveListComplete, const int sentenceIndex)
{
	bool foundBooleanStatementExpression = false;
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode* entity = (*entityIter);
		if(NLCcodeBlockClass.checkSentenceIndexParsingCodeBlocks(entity, sentenceIndex, false))
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
				#ifdef NLC_EXPLETIVES
				if(entity->isExpletive)
				{
					foundBooleanStatementExpression = true;
				}
				#endif
			}
		}
	}
	return foundBooleanStatementExpression;
}

bool NLCtranslatorCodeBlocksLogicalConditionsClass::getMathObjectVariableTypeBooleanExpressionBeforeGIAestimate(NLCpreprocessorSentence* currentFullSentence, const NLCpreprocessorParsablePhrase* parsablePhrase)
{
	 //parsablePhrasePrimarySubject
	bool foundBooleanStatementExpression = false;

	#ifdef NLC_MATH_OBJECTS_ADVANCED
	//NEW: note this function is not robust; e.g. in cases where the parsablePhrase represents NLC_MATH_OBJECTS_VARIABLE_TYPE_BOOLEAN (e.g. "the dog = true", or "if(the dog)" where "the dog" represents a boolean value)
	if(currentFullSentence->hasLogicalConditionOperator)
	{
		if(currentFullSentence->mathTextNLPparsablePhraseTotal > 0)	//2f8a
		{
			if(currentFullSentence->logicalConditionOperator != NLC_LOGICAL_CONDITION_OPERATIONS_ELSE)	//NB getMathObjectVariableTypeShared will fail if NLC_LOGICAL_CONDITION_OPERATIONS_ELSE (because sentence will contain no contents; only "else")
			{				
				string mathTextSubphraseContainingNLPparsablePhrase = "";
				int mathObjectVariableType = getMathObjectVariableTypeShared(currentFullSentence, parsablePhrase, &mathTextSubphraseContainingNLPparsablePhrase);
				//cout << "mathTextSubphraseContainingNLPparsablePhrase = " << mathTextSubphraseContainingNLPparsablePhrase << endl;
				if(mathObjectVariableType == NLC_MATH_OBJECTS_VARIABLE_TYPE_UNKNOWN)
				{
					//LRPpreprocessorWordClassObject.printWordList(&(parsablePhrase->sentenceContents));

					#ifndef NLC_MATH_OBJECTS_ADVANCED_USE_UNIQUE_OPERATORS
					//2f7b
					//i.e. use generic operators (== / +)
					bool foundNonBooleanStatementExpressionOperator = false;	
					for(int i=0; i<NLC_MATH_OBJECTS_VARIABLE_TYPE_GENERIC_OPERATORS_NUMBER_OF_TYPES; i++)
					{
						if(mathTextSubphraseContainingNLPparsablePhrase.find(mathObjectsVariableTypeGenericOperators[i]) != CPP_STRING_FIND_RESULT_FAIL_VALUE)
						{
							bool foundGenericComparisonOperator = true;
							//cout << "foundGenericComparisonOperator" << endl;
							foundNonBooleanStatementExpressionOperator = true;
						}
					}
					#ifdef NLC_MATH_OBJECTS_ADVANCED_DETECT_MALFORMED_STRING_OPERATORS
					for(int i=0; i<NLC_MATH_OBJECTS_VARIABLE_TYPE_MALFORMED_STRING_OPERATORS_NUMBER_OF_TYPES; i++)
					{
						if(mathTextSubphraseContainingNLPparsablePhrase.find(mathObjectsVariableTypeMaformedStringOperators[i]) != CPP_STRING_FIND_RESULT_FAIL_VALUE)
						{
							bool foundMalformattedStringComparisonOperator = true;
							//cout << "foundMalformattedStringComparisonOperator" << endl;
							foundNonBooleanStatementExpressionOperator =  true;
						}
					}
					#endif				
					if(!foundNonBooleanStatementExpressionOperator)
					{
					#endif
						//2f7c
						bool foundAuxiliaryOrVerb = false;
						for(int w=0; w<(parsablePhrase->sentenceContents).size(); w++)
						{
							LRPpreprocessorPlainTextWord* currentWord = (parsablePhrase->sentenceContents)[w];
							if(isWordAuxiliaryOrVerb(currentWord))
							{
								foundAuxiliaryOrVerb = true;
							}
						}

						if(foundAuxiliaryOrVerb)
						{
							//cout << "foundAuxiliaryOrVerb" << endl;
							//Note this is still not robust, e.g. "if(the dog that has[aux] a ball)" where "the dog that has a ball" represents a boolean value (as opposed to a boolean expression; e.g. "if(the dog has a ball)")
							foundBooleanStatementExpression = true;
						}
					#ifndef NLC_MATH_OBJECTS_ADVANCED_USE_UNIQUE_OPERATORS
					}
					#endif
				}
			}
		}
	}
	#else
	cerr << "NLCtranslatorCodeBlocksLogicalConditionsClass::getMathObjectVariableTypeBooleanExpressionBeforeGIA{} error: NLC_MATH_OBJECTS_ADVANCED is required" << endl;
	exit(EXIT_ERROR);
	#endif
	
	/*
	//OLD2; not robust, as even if verb is found, the POS type will not necessarily be verb
	for(int w=0; w<(parsablePhrase->sentenceContents).size(); w++)
	{
		LRPpreprocessorPlainTextWord* currentWord = (parsablePhrase->sentenceContents)[w];
		
		bool foundDelimiter = isWordAuxiliaryOrVerb(currentWord);

		if(foundDelimiter)
		{
			bool foundCorrespondingRcmod = false;
			for(int i2=0; i2<NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_RCMOD_SAME_REFERENCE_SET_DELIMITER_NUMBER_OF_TYPES; i2++)
			{
				if(w >= 1)
				{
					if((parsablePhrase->sentenceContents)[w-1] == preprocessorMathRcmodSameReferenceSetDelimiter[i2])
					{
						foundCorrespondingRcmod = true;	
					}
				}
			}
			if(!foundCorrespondingRcmod)
			{
				foundBooleanStatementExpression = true;
			}
		}
	}
	
	//OLD1; not robust; what if there is more than one auxiliary of a particular type in the parsable phrase
	for(int i=0; i<NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_AUXILIARY_KEYWORDS_TAGGING_SUBJECT_OR_REFERENCE_NUMBER_OF_TYPES; i++)
	{
		int indexOfAuxiliaryTemp = LRPpreprocessorWordClassObject.findStringInWordList(&(parsablePhrase->sentenceContents), preprocessorMathAuxiliaryKeywordsTaggingSubjectOrReference[i], 0);
		if(indexOfAuxiliaryTemp != CPP_STRING_FIND_RESULT_FAIL_VALUE)
		{
			for(int i2=0; i2<NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_RCMOD_SAME_REFERENCE_SET_DELIMITER_NUMBER_OF_TYPES; i2++)
			{
				int indexOfRcmodTemp = LRPpreprocessorWordClassObject.findStringInWordListReverse(&(parsablePhrase->sentenceContents), preprocessorMathRcmodSameReferenceSetDelimiter[i2], indexOfAuxiliaryTemp);
				if(indexOfAuxiliaryTemp != indexOfAuxiliaryTemp-(preprocessorMathRcmodSameReferenceSetDelimiter[i2].length()+1))
				{
					foundBooleanStatementExpression = true;
				}
			}
		}
	}
	*/
	
	return foundBooleanStatementExpression;
}

bool NLCtranslatorCodeBlocksLogicalConditionsClass::isWordAuxiliaryOrVerb(LRPpreprocessorPlainTextWord* currentWord)
{
	bool foundDelimiter = false;

	for(int i=0; i<NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_AUXILIARY_KEYWORDS_TAGGING_SUBJECT_OR_REFERENCE_NUMBER_OF_TYPES; i++)
	{
		if(currentWord->tagName == preprocessorMathAuxiliaryKeywordsTaggingSubjectOrReference[i])	//CHECKTHIS (consider adding additional aux from wordlistAuxiliary.txt; e.g. "am")
		{
			foundDelimiter = true;
		}
	}

	#ifdef GIA_POS_REL_TRANSLATOR_HYBRID_NLC_PREPROCESSOR_PREFERENCE_NLP_PRELIM_POS_TAGS_OVER_LRP_WORD_TYPE_LISTS
	bool usePOSprelim = true;
	#else
	bool usePOSprelim = false;
	#endif
	#ifdef GIA_POS_REL_TRANSLATOR_GRAMMATICALLY_STRICT_VERB_VARIANTS_ONLY
	bool grammaticallyStrict = true;
	#else
	bool grammaticallyStrict = false;
	#endif
	if(LRPpreprocessorWordIdentification.determineIsVerb(currentWord, usePOSprelim, grammaticallyStrict));	
	{
		//not robust, as even if verb is found, the POS type will not necessarily be verb
		foundDelimiter = true;
	}

	return foundDelimiter;
}
	
int NLCtranslatorCodeBlocksLogicalConditionsClass::getMathObjectVariableTypeSharedWrapper(bool foundBooleanStatementExpression, NLCpreprocessorSentence* currentFullSentence, const NLCpreprocessorParsablePhrase* parsablePhrase)
{
	int mathObjectVariableType = NLC_MATH_OBJECTS_VARIABLE_TYPE_UNKNOWN;
	
	if(foundBooleanStatementExpression)
	{
		if(currentFullSentence->hasLogicalConditionOperator)
		{
			mathObjectVariableType = NLC_MATH_OBJECTS_VARIABLE_TYPE_BOOLEAN_STATEMENT;
		}
		else
		{
			#ifdef NLC_TRANSLATOR_LOGICAL_CONDITIONS_BOOLEAN_STATEMENTS_INTERPRET_SUBJECT_AND_OBJECT_INDEPENDENTLY_IGNORE_NLP_BUG
			foundBooleanStatementExpression = false;
			#else
			//eg1 "the dog = the chicken is happy" - must say; "if the chicken is happy, the dog = true". eg2 "bool X = the chicken is happy" -  must say; "if the chicken is happy, X = true"
			cerr << "generateCodeBlocksFromMathTextNLPparsablePhrase{} error: illegal expression detected: !(currentFullSentence->hasLogicalConditionOperator) && foundBooleanStatementExpression" << endl;
			cerr << "parsablePhrase->sentenceContents = " << LRPpreprocessorWordClassObject.generateTextFromVectorWordList(&(parsablePhrase->sentenceContents)) << endl;
			exit(EXIT_ERROR);
			#endif
		}
	}

	string mathTextSubphraseContainingNLPparsablePhrase = "";	//not used
	int mathObjectVariableType2 = getMathObjectVariableTypeShared(currentFullSentence, parsablePhrase, &mathTextSubphraseContainingNLPparsablePhrase);	//this requires NLC_MATH_OBJECTS to produce output
	if(mathObjectVariableType2 != NLC_MATH_OBJECTS_VARIABLE_TYPE_UNKNOWN)
	{
		mathObjectVariableType = mathObjectVariableType2;
	}
	
	#ifdef NLC_MATH_OBJECTS
	#ifdef NLC_MATH_OBJECTS_ADVANCED

	#ifdef NLC_MATH_OBJECTS_ADVANCED_USE_UNIQUE_OPERATORS
	if(currentFullSentence->hasLogicalConditionOperator)
	{
		if(mathObjectVariableType == NLC_MATH_OBJECTS_VARIABLE_TYPE_UNKNOWN)
		{
			#ifdef NLC_MATH_OBJECTS_ADVANCED_USE_UNIQUE_OPERATORS_ASSUME_LOGICAL_CONDITION_STATEMENTS_ARE_BOOLEAN_IF_UNKNOWN
			mathObjectVariableType = NLC_MATH_OBJECTS_VARIABLE_TYPE_BOOLEAN;
			#else
			cerr << "NLC_MATH_OBJECTS_ADVANCED_USE_UNIQUE_OPERATORS: getMathObjectVariableType{} error: (currentFullSentence->hasLogicalConditionOperator) && (mathObjectVariableType == NLC_MATH_OBJECTS_VARIABLE_TYPE_UNKNOWN)" << endl;
			exit(EXIT_ERROR);
			#endif
		}
	}
	#endif

	#else
	if(mathObjectVariableType == NLC_MATH_OBJECTS_VARIABLE_TYPE_UNKNOWN)
	{
		mathObjectVariableType = NLC_MATH_OBJECTS_VARIABLE_TYPE_NUMERICAL;
	}
	#endif
	#endif

	return mathObjectVariableType;
}


int NLCtranslatorCodeBlocksLogicalConditionsClass::getMathObjectVariableTypeShared(NLCpreprocessorSentence* currentFullSentence, const NLCpreprocessorParsablePhrase* parsablePhrase, string* mathTextSubphraseContainingNLPparsablePhraseRecord)
{
	int mathObjectVariableType = NLC_MATH_OBJECTS_VARIABLE_TYPE_UNKNOWN;

	string parsablePhraseReferenceName = NLCpreprocessorSentenceClass.generateMathTextNLPparsablePhraseReference(currentFullSentence->firstNLPparsablePhraseInList->sentenceIndex, parsablePhrase);
	string mathTextSubphraseContainingNLPparsablePhrase = "";
	int mathTextSubphraseContainingNLPparsablePhraseStartIndex = 0;
	int mathTextSubphraseContainingNLPparsablePhraseEndIndex = 0;
	//cout << "currentFullSentence->mathText = " << currentFullSentence->mathText << endl;
	if(currentFullSentence->hasLogicalConditionOperator)
	{
		getMathTextSubphraseContainingNLPparsablePhrase(currentFullSentence->mathText, parsablePhraseReferenceName, &mathTextSubphraseContainingNLPparsablePhrase, &mathTextSubphraseContainingNLPparsablePhraseStartIndex, &mathTextSubphraseContainingNLPparsablePhraseEndIndex);
	}
	else
	{
		mathTextSubphraseContainingNLPparsablePhrase = currentFullSentence->mathText;
	}
	
	*mathTextSubphraseContainingNLPparsablePhraseRecord = mathTextSubphraseContainingNLPparsablePhrase;
		
	//find numerical expressions
	for(int i=0; i<NLC_MATH_OBJECTS_VARIABLE_TYPE_NUMERICAL_OPERATORS_NUMBER_OF_TYPES; i++)
	{
		if(mathTextSubphraseContainingNLPparsablePhrase.find(mathObjectsVariableTypeNumericalOperatorsWithSpace[i]) != CPP_STRING_FIND_RESULT_FAIL_VALUE)
		{
			mathObjectVariableType = NLC_MATH_OBJECTS_VARIABLE_TYPE_NUMERICAL;
		}
	}

	#ifdef NLC_MATH_OBJECTS
	#ifdef NLC_MATH_OBJECTS_ADVANCED

	//find string expressions
	//#ifdef NLC_MATH_OBJECTS_ADVANCED_USE_UNIQUE_OPERATORS	//optional
	#ifdef NLC_MATH_OBJECTS_STRING
	for(int i=0; i<NLC_MATH_OBJECTS_VARIABLE_TYPE_STRING_OPERATORS_NUMBER_OF_TYPES; i++)
	{
		if(mathTextSubphraseContainingNLPparsablePhrase.find(mathObjectsVariableTypeStringOperators[i]) != CPP_STRING_FIND_RESULT_FAIL_VALUE)
		{
			mathObjectVariableType = NLC_MATH_OBJECTS_VARIABLE_TYPE_STRING;
		}
	}
	#endif
	//#endif

	//find boolean expressions
	#ifdef NLC_MATH_OBJECTS_BOOLEAN
	for(int i=0; i<NLC_MATH_OBJECTS_VARIABLE_TYPE_BOOLEAN_OPERATORS_NUMBER_OF_TYPES; i++)
	{
		if(mathTextSubphraseContainingNLPparsablePhrase.find(mathObjectsVariableTypeBooleanOperators[i]) != CPP_STRING_FIND_RESULT_FAIL_VALUE)
		{
			mathObjectVariableType = NLC_MATH_OBJECTS_VARIABLE_TYPE_BOOLEAN;
		}
	}
	#endif

	#ifdef NLC_MATH_OBJECTS_ADVANCED_INFER_TYPE_BASED_ON_PREVIOUSLY_DECLARED_MATHTEXT_VARIABLES
	//NB this code is not absolutely required (as assignMathObjectValue types can be inferred when compiling generated code), however it will simplify/normalise the generated output code
	for(vector<NLCvariable*>::iterator iter = currentFullSentence->mathTextVariables.begin(); iter != currentFullSentence->mathTextVariables.end(); iter++)
	{
		NLCvariable* mathTextVariable = (*iter);
		if(mathTextVariable->type != NLC_MATH_OBJECTS_VARIABLE_TYPE_UNKNOWN)
		{
			#ifdef NLC_MATH_OBJECTS_ADVANCED_INFER_TYPE_BASED_ON_PREVIOUSLY_DECLARED_MATHTEXT_VARIABLES_ADVANCED

			#ifdef NLC_MATH_OBJECTS_ADVANCED_USE_UNIQUE_OPERATORS
			//egs foundMathtextVariableAssignment: eg1 [double] X = thecatssvalue
			//egs foundParsablePhraseReferenceNameAssignment: thedogsvalue = X
			#else
			//egs foundMathtextVariableAssignment: eg1 [double] X = thecatssvalue, eg2 [double] X = thecatssvalue + themousessvalue
			//egs foundParsablePhraseReferenceNameAssignment: thedogsvalue = X, eg2 thedogsvalue = thecatssvalue, eg3 thedogsvalue = X + Y, eg4 thedogsvalue = thecatssvalue + Y
			//egs foundParsablePhraseReferenceNameTest: eg1 X == thecatssvalue, eg2 eg1 thedogsvalue == X, eg4 X == thecatssvalue + themousessvalue, eg5 thedogsvalue == X + themousessvalue, eg6 thedogsvalue == X + Y, eg7 thedogsvalue == X + themousessvalue, eg6 thedogsvalue == X + Y, eg7 thedogsvalue == thecatssvalue + Y
			#endif


			if(NLCpreprocessorMath.findMathTextVariableWithinMathText(mathTextVariable->name, mathTextSubphraseContainingNLPparsablePhrase))
			{
				mathObjectVariableType = mathTextVariable->type;
			}

			#else
			if(!(currentFullSentence->hasLogicalConditionOperator))
			{
				#ifdef NLC_MATH_OBJECTS_ADVANCED_USE_UNIQUE_OPERATORS
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
							}
						}
					}
				}
			}
			#endif
		}
	}
	#endif
	
	#endif
	#endif
	
	return mathObjectVariableType;
}

bool NLCtranslatorCodeBlocksLogicalConditionsClass::getMathTextSubphraseContainingNLPparsablePhrase(string mathText, const string parsablePhraseReferenceName, string* mathTextSubphraseContainingNLPparsablePhrase, int* mathTextSubphraseContainingNLPparsablePhraseStartIndex, int* mathTextSubphraseContainingNLPparsablePhraseEndIndex)
{
	bool result = true;
	bool foundConjunction = false;

	//remove the preceeding "if(" and trailing ")" of logical condition
	string mathTextLogicalConditionContents = "";
	int mathTextLogicalConditionContentsIndex = CPP_STRING_FIND_RESULT_FAIL_VALUE;
	bool foundLogicalConditionStartText = false;
	string logicalConditionEndText = string("") + NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_CLOSE_BRACKET;
	//cout << "mathText = " << mathText << endl;
	for(int i=0; i<NLC_LOGICAL_CONDITION_OPERATIONS_NUMBER_OF_TYPES; i++)
	{
		string logicalConditionStartText = logicalConditionOperationsArray[i] + NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_OPEN_BRACKET;
		//cout << "logicalConditionStartText = " << logicalConditionStartText << endl;
		if(mathText.find(logicalConditionStartText) == 0)
		{
			mathTextLogicalConditionContents = mathText.substr(logicalConditionStartText.length(), mathText.length() - logicalConditionStartText.length() - logicalConditionEndText.length());
			mathTextLogicalConditionContentsIndex = logicalConditionStartText.length();
			foundLogicalConditionStartText = true;
		}
	}
	if(foundLogicalConditionStartText)
	{
		//algorithm: extract "&& (thehouse == " -> " (thehouse " -> "thehouse"

		//find numerical expressions
		//cout << "mathTextLogicalConditionContents = " << mathTextLogicalConditionContents << endl;
		//cout << "parsablePhraseReferenceName = " << parsablePhraseReferenceName << endl;
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
			*mathTextSubphraseContainingNLPparsablePhraseStartIndex = subphraseStartPosition + mathTextLogicalConditionContentsIndex;
			*mathTextSubphraseContainingNLPparsablePhraseEndIndex = subphraseEndPosition + mathTextLogicalConditionContentsIndex;
			
			if(removeSurroundingBracketsOfSubphrase(mathTextSubphraseContainingNLPparsablePhrase))	//added 1u1b
			{
				int sizeOfBracket = string(NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_OPEN_BRACKET_STRING).length();
				*mathTextSubphraseContainingNLPparsablePhraseStartIndex = *mathTextSubphraseContainingNLPparsablePhraseStartIndex + sizeOfBracket;		
			}
		}
		else
		{
			result = false;
			cerr << "getMathTextSubphraseContainingNLPparsablePhrase{} error: parsablePhraseReferenceNamePositionInMathtext cannot be identified" << endl;
			exit(EXIT_ERROR);
		}
	}
	else
	{
		result = false;
		cerr << "getMathTextSubphraseContainingNLPparsablePhrase{} error: !foundLogicalConditionStartText" << endl;
		exit(EXIT_ERROR);
	}

	return result;
}

bool NLCtranslatorCodeBlocksLogicalConditionsClass::findMatchingBrackets(string subphraseTemp, int* subphraseStartPositionTemp, int* subphraseEndPositionTemp)
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

#ifdef NLC_MATH_OBJECTS_ADVANCED
string NLCtranslatorCodeBlocksLogicalConditionsClass::generateAssignMathTextValueExecuteFunctionMathText(const NLCpreprocessorSentence* currentFullSentence, string parsablePhraseReferenceName, const bool hasLogicalConditionOperator)
{
	const string* mathText = &(currentFullSentence->mathText);
	 
	bool foundParsablePhraseReferenceNameAssignment = false;
	int progLang = NLCprintDefs.getProgLang();	//CHECKTHIS - note this is an unusual implementation, in future could update NLCtranslatorCodeBlocksLogicalConditions.cpp generateCodeBlocksFromMathText{} to not execute generateCodeBlocksFromMathText (ie print updated mathText), but instead execute a new codeBlocks subroutine createCodeBlockAssignMathTextValueExecute(targetText, sourceText)
	string mathTextUpdated = *mathText;
	int parsablePhraseReferenceNameIndex = mathText->find(parsablePhraseReferenceName);
	if(parsablePhraseReferenceNameIndex != CPP_STRING_FIND_RESULT_FAIL_VALUE)
	{
		int indexOfMathEqualsSetCommand = INT_DEFAULT_VALUE;
		bool foundMathEqualsSetCommand = NLCpreprocessorMath.findCharacterAtIndexOrAfterSpace(mathText, parsablePhraseReferenceNameIndex+parsablePhraseReferenceName.length(), NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_SET_CHAR, &indexOfMathEqualsSetCommand);	//mathText eg: "thedogsvalue =" OR "thedogsvalue="
		if(foundMathEqualsSetCommand)
		{
			#ifdef NLC_MATH_OBJECTS_ADVANCED_USE_UNIQUE_OPERATORS
			//eg1 thedogsvalue = X, eg2 thedogsvalue = thecatssvalue
			#else
			//eg1 thedogsvalue = X, eg2 thedogsvalue = thecatssvalue, eg3 thedogsvalue = X + Y, eg4 thedogsvalue = thecatssvalue + Y
			#endif
			#ifndef NLC_MATH_OBJECTS_ADVANCED_USE_UNIQUE_OPERATORS
			if(mathText->find(NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_TEST, indexOfMathEqualsSetCommand) != indexOfMathEqualsSetCommand)
			{//ignore equals test ("==") expressions
			#else
			//redundant as !(currentFullSentence->hasLogicalConditionOperator)
			#endif
				foundParsablePhraseReferenceNameAssignment = true;
				string targetValueText = getTargetValueText(mathText, indexOfMathEqualsSetCommand, NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_SET, progLang);	//eg thedogsvalue
				mathTextUpdated = NLC_MATH_OBJECTS_ADVANCED_ASSIGN_MATHOBJECT_VALUE_FUNCTION_NAME + progLangOpenParameterSpace[progLang] + parsablePhraseReferenceName + progLangClassMemberFunctionParametersNext[progLang] + targetValueText + progLangCloseParameterSpace[progLang];	//eg0 "assignMathObjectValue(thedogsvalue, thechickensvalue)", eg1 "assignMathObjectValue(thedogsvalue, addMathTextValue(5 + theNumberOfApplesNearTheFarm))", eg2 "assignMathObjectValue(thedogsvalue, addMathTextValue("the dog's name is ", maxsName))"
			#ifndef NLC_MATH_OBJECTS_ADVANCED_USE_UNIQUE_OPERATORS
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
			#ifdef NLC_MATH_OBJECTS_ADVANCED_USE_UNIQUE_OPERATORS
			//eg1 X = thecatssvalue
			#else
			//eg1 X = thecatssvalue, eg2 X = thecatssvalue + themousessvalue
			#endif
			
		
			#ifndef NLC_MATH_OBJECTS_ADVANCED_USE_UNIQUE_OPERATORS
			if(mathText->find(NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_TEST, indexOfMathEqualsSetCommand) != indexOfMathEqualsSetCommand)
			{//a) ignore equals test ("==") expressions
				if(!findInvertedCommasEitherSideOfCharacter(mathText, indexOfMathEqualsSetCommand))
				{//b) ignore all equals signs within inverted commas
					//mathText eg: "X =" OR "X="
					#ifdef NLC_MATH_OBJECTS_ADVANCED_ASSIGN_MATHTEXT_VALUE_FUNCTION
					if(mathText->find(NLC_MATH_OBJECTS_ADVANCED_ASSIGN_MATHTEXT_VALUE_FUNCTION_NAME, indexOfMathEqualsSetCommand) != (indexOfMathEqualsSetCommand + 2))
					{//c) only create one instance of = getMathObjectValue(.. per sentence;	eg X = thecatssvalue + themousessvalue
					#else
					if(mathText->find(NLC_MATH_OBJECTS_ADVANCED_GET_MATHOBJECT_VALUE_FUNCTION_NAME) != CPP_STRING_FIND_RESULT_FAIL_VALUE)	//redundant
					{//c) only create one instance of assignMathtextValue(.. per sentence;	eg X = thecatssvalue + themousessvalue
					#endif
			#else
			//redundant as a) !(currentFullSentence->hasLogicalConditionOperator), b) finding first instance of '=', so there will be no '"' characters before the '=' character, and c) there are no additions (+) so there will only be one parsable phrase found in the sentence
			#endif
						#ifdef NLC_MATH_OBJECTS_ADVANCED_ASSIGN_MATHTEXT_VALUE_FUNCTION
						//verify that the equality source value text does not contain an NLP parsable phrase reference
						bool sourceIsParsablePhrase = false;
						string sourceValueText = getSourceValueText(mathText, indexOfMathEqualsSetCommand, progLang);
						const NLCpreprocessorParsablePhrase* currentParsablePhrase2 = currentFullSentence->firstNLPparsablePhraseInList;
						for(int i = 0; i < currentFullSentence->mathTextNLPparsablePhraseTotal; i++)
						{
							string parsablePhraseReferenceName2 = NLCpreprocessorSentenceClass.generateMathTextNLPparsablePhraseReference(currentFullSentence->firstNLPparsablePhraseInList->sentenceIndex, currentParsablePhrase2);
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
								string assignMathTextValueText = string(NLC_MATH_OBJECTS_ADVANCED_ASSIGN_MATHTEXT_VALUE_FUNCTION_NAME) + progLangOpenParameterSpace[progLang] + NLCprintDefs.generateReferenceText(sourceValueTextInitialisation, progLang) + progLangClassMemberFunctionParametersNext[progLang] + targetValueTextInitialisation + progLangCloseParameterSpace[progLang];	//eg0 "assignMathTextValue(X, thechickensvalue)", eg1 "assignMathTextValue(X, addMathTextValue(5 + theNumberOfApplesNearTheFarm))", eg2 "assignMathTextValue(X, addMathTextValue("the dog's name is ", maxsName))"
								mathTextUpdated = mathTextValueDeclaration + assignMathTextValueText;
								foundMathtextVariableAssignment = true;
							}
							else
							{
								//eg "X = thecatssvalue + themousessvalue" -> "assignMathTextValue(X, thecatssvalue + themousessvalue);
								string targetValueText = getTargetValueText(mathText, indexOfMathEqualsSetCommand, NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_SET, progLang);
								string assignMathTextValueText = string(NLC_MATH_OBJECTS_ADVANCED_ASSIGN_MATHTEXT_VALUE_FUNCTION_NAME) + progLangOpenParameterSpace[progLang] + NLCprintDefs.generateReferenceText(sourceValueText, progLang) + progLangClassMemberFunctionParametersNext[progLang] + targetValueText + progLangCloseParameterSpace[progLang];	//eg0 "assignMathTextValue(X, thechickensvalue)", eg1 "assignMathTextValue(X, addMathTextValue(5 + theNumberOfApplesNearTheFarm))", eg2 "assignMathTextValue(X, addMathTextValue("the dog's name is ", maxsName))"
								mathTextUpdated = assignMathTextValueText;
								foundMathtextVariableAssignment = true;
							}
						}
						#else
						string targetValueText = getTargetValueText(mathText, indexOfMathEqualsSetCommand, NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_SET, progLang);
						string getMathObjectValueText = string(NLC_MATH_OBJECTS_ADVANCED_GET_MATHOBJECT_VALUE_FUNCTION_NAME) + progLangOpenParameterSpace[progLang] + targetValueText + progLangCloseParameterSpace[progLang];	//eg "X = thechickensvalue"  ->  "X = getMathObjectValue(thechickensvalue)"
						mathTextUpdated = mathText->substr(0, indexOfMathEqualsSetCommand+1) + STRING_SPACE + getMathObjectValueText;
						foundMathtextVariableAssignment = true;
						#endif
			#ifndef NLC_MATH_OBJECTS_ADVANCED_USE_UNIQUE_OPERATORS
					}

				}
			}
			#endif
		
		}
	}

	#ifndef NLC_MATH_OBJECTS_ADVANCED_USE_UNIQUE_OPERATORS
	if(hasLogicalConditionOperator)
	{
		bool foundParsablePhraseReferenceNameTest = false;
		if(foundMathtextVariableAssignment || foundParsablePhraseReferenceNameAssignment)
		{
			cerr << "generateAssignMathTextValueExecuteFunctionMathText{} error: hasLogicalConditionOperator && (foundMathtextVariableAssignment || foundParsablePhraseReferenceNameAssignment)" << endl;
			exit(EXIT_ERROR);
		}

		int mathTextSubphraseContainingNLPparsablePhraseStartIndex = 0;
		int mathTextSubphraseContainingNLPparsablePhraseEndIndex = 0;
		string mathTextSubphraseContainingNLPparsablePhrase = "";
		bool subphraseFound = false;
		if(!getMathTextSubphraseContainingNLPparsablePhrase(*mathText, parsablePhraseReferenceName, &mathTextSubphraseContainingNLPparsablePhrase, &mathTextSubphraseContainingNLPparsablePhraseStartIndex, &mathTextSubphraseContainingNLPparsablePhraseEndIndex))
		{
			cerr << "generateAssignMathTextValueExecuteFunctionMathText{} error: !getMathTextSubphraseContainingNLPparsablePhrase" << endl;
			exit(EXIT_ERROR);
		}
		int indexOfMathEqualsTestCommand = mathTextSubphraseContainingNLPparsablePhrase.find(NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_TEST);
		if(indexOfMathEqualsTestCommand != CPP_STRING_FIND_RESULT_FAIL_VALUE)
		{
			//eg1 X == thecatssvalue, eg2 eg1 thedogsvalue == X eg3 thedogsvalue == thecatssvalue, eg3 thedogsvalue == thecatssvalue + themousessvalue, eg4 X == thecatssvalue + themousessvalue, eg5 thedogsvalue == X + themousessvalue, eg6 thedogsvalue == X + Y, eg7 thedogsvalue == X + themousessvalue, eg6 thedogsvalue == X + Y, eg7 thedogsvalue == thecatssvalue + Y [not X == Y]
			if(mathText->find(NLC_MATH_OBJECTS_ADVANCED_TEST_MATHOBJECT_VALUE_FUNCTION_NAME) != 0)
			{//only create one instance of = testMathObjectValue(.. per sentence; eg1 X == thecatssvalue + themousessvalue, eg2 thecatssvalue == themousessvalue
				string targetValueText = getTargetValueText(&mathTextSubphraseContainingNLPparsablePhrase, indexOfMathEqualsTestCommand, NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_TEST, progLang);
				string sourceValueText = getSourceValueText(&mathTextSubphraseContainingNLPparsablePhrase, indexOfMathEqualsTestCommand, progLang);
				#ifdef NLC_MATH_OBJECTS_ADVANCED_COMPARISONS
				string mathTextSubphraseContainingNLPparsablePhraseUpdated = string(NLC_MATH_OBJECTS_ADVANCED_TEST_MATHOBJECT_VALUE_FUNCTION_NAME) + progLangOpenParameterSpace[progLang] + sourceValueText + progLangClassMemberFunctionParametersNext[progLang] + targetValueText + progLangCloseParameterSpace[progLang];	//eg "X == thechickensvalue"  ->  "testMathObjectValue(X, thechickensvalue)"
				#else
				string mathTextSubphraseContainingNLPparsablePhraseUpdated = sourceValueText + NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_TEST_WITH_PADDING + targetValueText;
				#endif
				mathTextUpdated.replace(mathTextSubphraseContainingNLPparsablePhraseStartIndex, mathTextSubphraseContainingNLPparsablePhrase.length(), mathTextSubphraseContainingNLPparsablePhraseUpdated);
				//progLangParameterSpaceNextParam
			}
		}
		else
		{
			int parsablePhraseReferenceNamePositionInSubphrase = mathTextSubphraseContainingNLPparsablePhrase.find(parsablePhraseReferenceName);
			if(parsablePhraseReferenceNamePositionInSubphrase != CPP_STRING_FIND_RESULT_FAIL_VALUE)
			{
				string parsablePhraseReferenceNameUpdated = string(NLC_MATH_OBJECTS_ADVANCED_TEST_MATHOBJECT_VALUE_FUNCTION_NAME) + progLangOpenParameterSpace[progLang] + parsablePhraseReferenceName + progLangCloseParameterSpace[progLang];	//eg "thechickensvalue"  ->  "testMathObjectValue(thechickensvalue)"
				string mathTextSubphraseContainingNLPparsablePhraseUpdated = mathTextSubphraseContainingNLPparsablePhrase;
				mathTextSubphraseContainingNLPparsablePhraseUpdated.replace(parsablePhraseReferenceNamePositionInSubphrase, parsablePhraseReferenceName.length(), parsablePhraseReferenceNameUpdated);
				mathTextUpdated.replace(mathTextSubphraseContainingNLPparsablePhraseStartIndex, mathTextSubphraseContainingNLPparsablePhrase.length(), mathTextSubphraseContainingNLPparsablePhraseUpdated);
			}
		}
	}
	#endif

	return mathTextUpdated;
}


bool NLCtranslatorCodeBlocksLogicalConditionsClass::findInvertedCommasEitherSideOfCharacter(const string* mathText, int indexOfCharacter)
{
	bool foundInvertedCommasEitherSideOfCharacter = false;
	if(mathText->find(NLC_MATH_OBJECTS_STRING_DELIMITER, indexOfCharacter) != CPP_STRING_FIND_RESULT_FAIL_VALUE)
	{
		if(mathText->rfind(NLC_MATH_OBJECTS_STRING_DELIMITER, indexOfCharacter) != CPP_STRING_FIND_RESULT_FAIL_VALUE)
		{
			foundInvertedCommasEitherSideOfCharacter = true;
		}
	}
	return foundInvertedCommasEitherSideOfCharacter;
}

string NLCtranslatorCodeBlocksLogicalConditionsClass::getTargetValueText(const string* mathText, int indexOfCommand, string command, int progLang)
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
	#ifdef NLC_MATH_OBJECTS_ADVANCED_ADDITIONS
	targetValueText = replaceAllAdditionSymbolsWithAdditionFunction(targetValueText, progLang);
	#endif
	return targetValueText;
}

string NLCtranslatorCodeBlocksLogicalConditionsClass::getSourceValueText(const string* mathText, const int indexOfCommand, int progLang)
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
	#ifdef NLC_MATH_OBJECTS_ADVANCED_ADDITIONS
	sourceValueText = replaceAllAdditionSymbolsWithAdditionFunction(sourceValueText, progLang);
	#endif
	return sourceValueText;
}

#ifdef NLC_MATH_OBJECTS_ADVANCED_ADDITIONS
string NLCtranslatorCodeBlocksLogicalConditionsClass::replaceAllAdditionSymbolsWithAdditionFunction(string text, int progLang)
{
	removeSurroundingBracketsOfSubphrase(&text);	//added 1u1b
	
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
		text = string(NLC_MATH_OBJECTS_ADVANCED_ADD_MATHOBJECT_VALUE_FUNCTION_NAME) + progLangOpenParameterSpace[progLang] + text;
	}
	if(numberOfAdditionsFound > 0)
	{
		text = text + progLangCloseParameterSpace[progLang];
	}
	return text;
}
#endif

bool NLCtranslatorCodeBlocksLogicalConditionsClass::removeSurroundingBracketsOfSubphrase(string* subphraseText)
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



bool NLCtranslatorCodeBlocksLogicalConditionsClass::isNumberOf(const GIAentityNode* entity)
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

bool NLCtranslatorCodeBlocksLogicalConditionsClass::generateCodeBlocksFromMathTextNLPparsablePhraseLogicalConditionFor(NLCcodeblock** currentCodeBlockInTree, vector<GIAentityNode*>* entityNodesActiveListComplete, int sentenceIndex, const NLCpreprocessorSentence* currentFullSentence, const NLCpreprocessorParsablePhrase* parsablePhrase, const int phraseIndex, NLCcodeblock** currentCodeBlockInTreeAtBaseLevel, const NLCpreprocessorSentence* fullSentence)
{
	bool foundParsablePhrase = false;

	//generate NLP parsable phrase eg "all apples in the cart" in "for(all the apples in the cart)"

	#ifdef NLC_GENERATE_UNIQUE_CONTEXT_BLOCK_FOR_EACH_SENTENCE_LOGICAL_CONDITIONS_FOR_LOOPS
	NLCcodeblock* firstCodeBlockInPhrase = *currentCodeBlockInTree;
	*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlocksCreateContextBlock(*currentCodeBlockInTree);
	#ifdef NLC_TRANSLATOR_LOGICAL_CONDITIONS_SINGLE_SENTENCE_MULTIPLE_LEVEL_FOR_LOOPS_OLD
	#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
	*currentCodeBlockInTreeAtBaseLevel = firstCodeBlockInPhrase;
	#ifdef NLC_ADVANCED_REFERENCING_MONITOR_CONTEXT
	(*currentCodeBlockInTreeAtBaseLevel)->isLogicalCondition = true;
	(*currentCodeBlockInTreeAtBaseLevel)->contextLevel = fullSentence->indentation+1;
	#endif
	#endif
	#endif
	#endif
	
	#ifndef NLC_GENERATE_UNIQUE_CONTEXT_BLOCK_FOR_EACH_SENTENCE_LOGICAL_CONDITIONS_FOR_LOOPS
	#ifndef NLC_TRANSLATOR_LOGICAL_CONDITIONS_SINGLE_SENTENCE_MULTIPLE_LEVEL_FOR_LOOPS_OLD
	*currentCodeBlockInTreeAtBaseLevel = *currentCodeBlockInTree;
	#endif
	#endif
	
	if((currentFullSentence->hasLogicalConditionOperator) && (currentFullSentence->logicalConditionOperator == NLC_LOGICAL_CONDITION_OPERATIONS_FOR))
	{
		foundParsablePhrase = false;
		for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
		{
			GIAentityNode* entity = (*entityIter);
			if(NLCcodeBlockClass.checkSentenceIndexParsingCodeBlocks(entity, sentenceIndex, false))
			{
				if(readParsablePhraseEntryEntityChecks(entity))
				{//required
					if(!foundParsablePhrase)
					{
						#ifdef NLC_TRANSLATOR_DO_NOT_REPARSE_CONTEXT_BLOCKS_IF_ALREADY_PARSED_DURING_ENTITY_INITIALISATION
						GIAentityNode* childEntity = NULL;
						NLCgenerateContextBlocksVariables generateContextBlocksVariables;
						#ifdef NLC_TRANSLATOR_LOGICAL_CONDITIONS_SINGLE_SENTENCE_MULTIPLE_LEVEL_FOR_LOOPS_OLD
						#ifndef NLC_GENERATE_UNIQUE_CONTEXT_BLOCK_FOR_EACH_SENTENCE_LOGICAL_CONDITIONS_FOR_LOOPS
						#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
						generateContextBlocksVariables.setCodeBlockInTreeAtBaseLevel = true;
						#endif
						#endif
						#endif
						parseLogicalConditionEntity(currentCodeBlockInTree, entity, sentenceIndex, true, &childEntity, &generateContextBlocksVariables);							
						#else
						bool foundDefiniteParentEntity = false;
						bool parseConditionParents = NLC_PARSE_CONDITION_PARENTS_DEFAULT_VALUE;
						bool checkIsDefinite = true;
						GIAentityNode* parentEntity = NLCtranslatorCodeBlocksOperations.getSameReferenceSetUniqueParent(entity, sentenceIndex, NULL, &foundDefiniteParentEntity, parseConditionParents, checkIsDefinite);	//GIAentityNode* parentEntity = getParent(entity, sentenceIndex);

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
						generateContextBlocksVariables.onlyGenerateContextBlocksIfConnectionsParsedForNLCorSameReferenceSet = false;	//irrelevant (as no !sameReferenceSet connection)
						parseParsablePhraseParent(currentCodeBlockInTree, sentenceIndex, parentEntity, &generateContextBlocksVariables, &childEntity, currentFullSentence->logicalConditionOperator);
						#endif
						
						#ifdef NLC_TRANSLATOR_LOGICAL_CONDITIONS_FOR_LOOP_ADD_ENTITY_TO_NEW_CONTEXT_LIST
						logicalConditionForLoopPrimaryEntityTemp = childEntity;
						#endif

						#ifdef NLC_TRANSLATOR_LOGICAL_CONDITIONS_SINGLE_SENTENCE_MULTIPLE_LEVEL_FOR_LOOPS_OLD
						#ifndef NLC_GENERATE_UNIQUE_CONTEXT_BLOCK_FOR_EACH_SENTENCE_LOGICAL_CONDITIONS_FOR_LOOPS
						#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
						*currentCodeBlockInTreeAtBaseLevel = generateContextBlocksVariables.currentCodeBlockInTreeAtBaseLevel;
						#ifdef NLC_ADVANCED_REFERENCING_MONITOR_CONTEXT
						(*currentCodeBlockInTreeAtBaseLevel)->isLogicalCondition = true;
						(*currentCodeBlockInTreeAtBaseLevel)->contextLevel = fullSentence->indentation+1;
						#endif
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

#ifdef NLC_TRANSLATOR_DO_NOT_REPARSE_CONTEXT_BLOCKS_IF_ALREADY_PARSED_DURING_ENTITY_INITIALISATION
void NLCtranslatorCodeBlocksLogicalConditionsClass::parseLogicalConditionEntity(NLCcodeblock** currentCodeBlockInTree, GIAentityNode* entity, int sentenceIndex, const bool hasLogicalConditionOperator, GIAentityNode** childEntity, NLCgenerateContextBlocksVariables* generateContextBlocksVariables)
{
	GIAentityNode* parentEntity = NLCtranslatorCodeBlocksOperations.getParent(entity, sentenceIndex);		//find both definite and indefinite parents; eg The dog's value = X / A dog's value = X

	bool foundChildEntity = false;
	*childEntity = NLCcodeBlockClass.getSameReferenceSetSubstanceNonQualityChild(parentEntity, sentenceIndex, &foundChildEntity);

	GIAentityNode* parentEntityTemp = NULL;	//already determined
	bool newInitialisation = false;
	generateContextBlocksVariables->onlyGenerateContextBlocksIfConnectionsParsedForNLCorSameReferenceSet = false;	//irrelevant (as no !sameReferenceSet connection)
	if(hasLogicalConditionOperator)
	{
		generateContextBlocksVariables->logicalConditionStatement = true;
	}
	NLCtranslatorCodeBlocksOperations.getParentAndInitialiseParentIfNecessaryAndGenerateContextBlocks(currentCodeBlockInTree, *childEntity, sentenceIndex, generateContextBlocksVariables, false, &parentEntityTemp, &newInitialisation);
}
#else
						
bool NLCtranslatorCodeBlocksLogicalConditionsClass::parseParsablePhraseParent(NLCcodeblock** currentCodeBlockInTree, int sentenceIndex, GIAentityNode* parentEntity, NLCgenerateContextBlocksVariables* generateContextBlocksVariables, GIAentityNode** childEntity, const int logicalConditionOperator)
{
	bool foundChildEntity = false;
	*childEntity = NLCcodeBlockClass.getSameReferenceSetSubstanceNonQualityChild(parentEntity, sentenceIndex, &foundChildEntity);

	generateContextBlocksVariables->onlyGenerateContextBlocksIfConnectionsParsedForNLCorSameReferenceSet = true;
	#ifndef NLC_GENERATE_UNIQUE_CONTEXT_BLOCK_FOR_EACH_SENTENCE_LOGICAL_CONDITIONS_FOR_LOOPS
	#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
	if(logicalConditionOperator == NLC_LOGICAL_CONDITION_OPERATIONS_FOR)
	{
		generateContextBlocksVariables->setCodeBlockInTreeAtBaseLevel = true;
	}
	#endif
	#endif


	bool contextFound = false;
	bool generatedContextForChild = false;
	if(foundChildEntity)
	{
		if(NLCtranslatorCodeBlocksOperations.generateContextBlocksForParentEntity(currentCodeBlockInTree, *childEntity, parentEntity, sentenceIndex, generateContextBlocksVariables))
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

	if(NLCtranslatorCodeBlocksOperations.generateContextBlocks(currentCodeBlockInTree, *childEntity, sentenceIndex, generateContextBlocksVariables, generatedContextForChild, NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION))
	{
		contextFound = true;
	}

	return contextFound;
}
#endif

#endif

#ifdef NLC_LOGICAL_CONDITION_OPERATIONS_BASED_ON_ACTIONS_BASIC
bool NLCtranslatorCodeBlocksLogicalConditionsClass::checkIfPhraseContainsAction(vector<GIAentityNode*>* entityNodesActiveListComplete, const int sentenceIndex, constEffective GIAentityNode** logicalConditionOperationObject)
{
	bool phraseContainsAction = false;
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode* entity = (*entityIter);
		if(NLCcodeBlockClass.checkSentenceIndexParsingCodeBlocks(entity, sentenceIndex, false))
		{
			if(entity->entityType == GIA_ENTITY_TYPE_ACTION)	//removed || (entity->isConcept && entity->isActionConcept) 1u15a
			{
				phraseContainsAction = true;
				*logicalConditionOperationObject = entity;
			}
		}
	}
	return phraseContainsAction;
}
#endif

#ifdef NLC_LOGICAL_CONDITION_OPERATIONS_BASED_ON_CONCEPTS
#ifdef NLC_LOGICAL_CONDITION_OPERATIONS_BASED_ON_CONCEPTS_BASIC
bool NLCtranslatorCodeBlocksLogicalConditionsClass::checkIfPhraseContainsConceptWithDefinitionLink(vector<GIAentityNode*>* entityNodesActiveListComplete, const int sentenceIndex, constEffective GIAentityNode** logicalConditionOperationObject)
{
	bool phraseContainsConceptWithDefinitionLink = false;
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode* entity = (*entityIter);
		if(NLCcodeBlockClass.checkSentenceIndexParsingCodeBlocks(entity, sentenceIndex, false))
		{
			if(entity->entityType == GIA_ENTITY_TYPE_CONCEPT)
			{
				for(vector<GIAentityConnection*>::iterator iter = entity->definitionNodeList->begin(); iter < entity->definitionNodeList->end(); iter++)
				{
					GIAentityConnection* definitionConnection = *iter;
					GIAentityNode* definitionEntityTemp =  definitionConnection->entity;
					if(definitionConnection->sentenceIndexTemp == sentenceIndex)
					{
						if(!(definitionConnection->sameReferenceSet))
						{
							if(!NLCcodeBlockClass.isDefiniteEntity(entity) && !NLCcodeBlockClass.isDefiniteEntity(definitionEntityTemp))
							{
								phraseContainsConceptWithDefinitionLink = true;
								*logicalConditionOperationObject = entity;
							}
							else
							{
								cout << "checkIfPhraseContainsConceptWithDefinitionLink{} warning: !(!NLCcodeBlockClass.isDefiniteEntity(entity)) && !NLCcodeBlockClass.isDefiniteEntity(definitionEntityTemp))" << endl;
							}
						}
					}
				}
				/*OLD: before 1n5b update;
				if(!(entity->definitionNodeList->empty()))
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
bool NLCtranslatorCodeBlocksLogicalConditionsClass::checkIfPhraseContainsConcept(vector<GIAentityNode*>* entityNodesActiveListComplete, const int sentenceIndex, constEffective GIAentityNode** logicalConditionOperationObject)
{
	bool phraseContainsConcept = false;
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode* entity = (*entityIter);
		if(NLCcodeBlockClass.checkSentenceIndexParsingCodeBlocks(entity, sentenceIndex, false))
		{
			if(entity->entityType == GIA_ENTITY_TYPE_CONCEPT)
			{
				phraseContainsConcept = true;
				*logicalConditionOperationObject = entity;

				for(vector<GIAentityConnection*>::iterator iter = entity->definitionReverseNodeList->begin(); iter < entity->definitionReverseNodeList->end(); iter++)
				{
					GIAentityConnection* definitionConnection = *iter;
					GIAentityNode* definitionChildEntity = GIAtranslatorOperations.getDefinitionRelationshipSubjectEntity(definitionConnection);
					if(definitionChildEntity->sentenceIndexTemp == sentenceIndex)	//note (with USE_NLC) separate concept entites are created for logical condition NLP parsable phrases (GIA advanced referencing is not applied), therefore a direct test of sentenceIndexTemp can be made
					{
						if(!(definitionConnection->sameReferenceSet))
						{
							#ifdef GIA_TRANSLATOR_INTERPRET_PRENOMINAL_MODIFIER_SUBCLASSES_ENABLE_INCONSISTENT_REFERENCING
							//ignore additional subclass concepts/definitions created by GIA when parsing NLC logical condition statements (eg alsation_dog for "If the dog is an alsation")
							if((definitionChildEntity->entityType == GIA_ENTITY_TYPE_CONCEPT) && (entity->isSubClass))
							{
								phraseContainsConcept = false;
							}
							#endif
							if(definitionChildEntity->entityType != GIA_ENTITY_TYPE_CONCEPT)
							{
								phraseContainsConcept = false;	//this is absolutely required for NLC_TRANSLATOR_LOGICAL_CONDITIONS_BOOLEAN_STATEMENTS_INTERPRET_SUBJECT_AND_OBJECT_INDEPENDENTLY_DEFINITIONS/NLC_LOGICAL_CONDITION_OPERATIONS_BASED_ON_CONCEPTS_BASIC_REDEFINITIONS
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

#ifdef NLC_LOGICAL_CONDITION_OPERATIONS_BASED_ON_CONCEPTS_BASIC_REDEFINITIONS
bool NLCtranslatorCodeBlocksLogicalConditionsClass::checkIfPhraseContainsSubstanceWithDefinitionLink(vector<GIAentityNode*>* entityNodesActiveListComplete, int sentenceIndex, constEffective GIAentityNode** logicalConditionOperationObject, constEffective GIAentityNode** definitionRelationshipObjectEntity)
{
	bool phraseContainsSubstanceWithDefinitionLink = false;
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode* entity = (*entityIter);
		if(NLCcodeBlockClass.checkSentenceIndexParsingCodeBlocks(entity, sentenceIndex, false))
		{
			if(entity->entityType == GIA_ENTITY_TYPE_SUBSTANCE)
			{
				for(vector<GIAentityConnection*>::iterator iter = entity->definitionNodeList->begin(); iter < entity->definitionNodeList->end(); iter++)
				{
					GIAentityConnection* definitionConnection = *iter;
					GIAentityNode* definitionEntityTemp = getDefinitionRelationshipObjectEntity(definitionConnection);
					if(definitionConnection->sentenceIndexTemp == sentenceIndex)	//note (with USE_NLC) separate concept entites are created for logical condition NLP parsable phrases (GIA advanced referencing is not applied), therefore a direct test of sentenceIndexTemp can be made
					{
						if(!(definitionConnection->sameReferenceSet))
						{
							if(!NLCcodeBlockClass.isDefiniteEntity(definitionEntityTemp))
							{
								bool foundDefiniteParentOfEntity = false;
								bool parseConditionParents = NLC_PARSE_CONDITION_PARENTS_DEFAULT_VALUE;
								bool checkIsDefinite = true;
								GIAentityNode* parentEntity = NLCtranslatorCodeBlocksOperations.getSameReferenceSetUniqueParent(entity, sentenceIndex, NULL, &foundDefiniteParentOfEntity, parseConditionParents, checkIsDefinite);
								if(NLCcodeBlockClass.isDefiniteEntity(entity) || foundDefiniteParentOfEntity)
								{
									if(entity->entityName != definitionEntityTemp->entityName)
									{//ignore concept definitions for for entities of same name
										phraseContainsSubstanceWithDefinitionLink = true;
										*logicalConditionOperationObject = entity;
										*definitionRelationshipObjectEntity = definitionEntityTemp;
									}
								}
								else
								{
									cout << "checkIfPhraseContainsSubstanceWithDefinitionLink{} warning: !(NLCcodeBlockClass.isDefiniteEntity(entity) || foundDefiniteParentOfEntity))" << endl;
								}
							}
							else
							{
								cout << "checkIfPhraseContainsSubstanceWithDefinitionLink{} warning: NLCcodeBlockClass.isDefiniteEntity(definitionEntityTemp))" << endl;
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


void NLCtranslatorCodeBlocksLogicalConditionsClass::setDummyReferenceSetIDforAllEntitiesInPhrase(vector<GIAentityNode*>* entityNodesActiveListComplete, const int sentenceIndex)
{
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode* entity = (*entityIter);
		if(NLCcodeBlockClass.checkSentenceIndexParsingCodeBlocks(entity, sentenceIndex, false))
		{
			entity->referenceSetID = NLC_LOGICAL_CONDITION_OPERATIONS_BASED_ON_ACTIONS_OR_NETWORK_INDEXES_DUMMY_REFERENCE_SET_ID;
		}
	}
}


bool NLCtranslatorCodeBlocksLogicalConditionsClass::readParsablePhraseEntryEntityChecks(const GIAentityNode* entity)
{
	bool result = false;
	#ifdef GIA_ADD_ARTIFICIAL_AUXILIARY_FOR_ALL_PROPERTIES_AND_DEFINITIONS
	if(!(entity->entityType == GIA_ENTITY_TYPE_NETWORK_INDEX) && !(entity->entityType == GIA_ENTITY_TYPE_CONDITION) && !(entity->entityType == GIA_ENTITY_TYPE_PROPERTY) && !(entity->entityType == GIA_ENTITY_TYPE_DEFINITION))
	#else
	if(!(entity->entityType == GIA_ENTITY_TYPE_NETWORK_INDEX) && !(entity->entityType == GIA_ENTITY_TYPE_CONDITION))
	#endif
	{
		result = true;
	}
	return result;
}

#ifdef NLC_PREPROCESSOR_MATH_REPLACE_NUMERICAL_VARIABLES_NAMES_FOR_NLP
bool NLCtranslatorCodeBlocksLogicalConditionsClass::findDummyNumberAndReplaceWithOriginalNumericalVariableName(vector<GIAentityNode*>* entityNodesActiveListComplete, const int sentenceIndex, const int dummyNumber, string numericalVariableName)
{
	bool result = true;
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode* entity = (*entityIter);
		if(NLCcodeBlockClass.checkSentenceIndexParsingCodeBlocks(entity, sentenceIndex, false))
		{
			if(entity->quantityNumber == dummyNumber)
			{
				entity->NLCoriginalNumericalVariableName = numericalVariableName;
				result = true;
			}
		}
	}
	return result;
}
#endif
#endif

