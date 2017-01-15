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
 * File Name: NLCtranslatorCodeBlocks.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2014 Baxter AI (baxterai.com)
 * Project: Natural Language Programming Interface (compiler)
 * Project Version: 1h1f 26-July-2014
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/



#include <ctime>
#include <cstdlib>	//for random number generation
#include <cmath>

#include "NLCtranslatorCodeBlocks.h"
#include "NLCtranslatorCodeBlocksLogicalConditions.h"
#include "NLCtranslatorCodeBlocksOperations.h"

bool generateCodeBlocks(NLCcodeblock * firstCodeBlockInTree, vector<GIAentityNode*> * entityNodesActiveListComplete, int maxNumberSentences, string NLCfunctionName, NLCfunction * currentNLCfunctionInList)
{
	bool result = true;

	NLCcodeblock * currentCodeBlockInTree = firstCodeBlockInTree;

	#ifdef NLC_NOT_NECESSARY
	vector<NLCitem *> implictlyDeclaredFunctionList;	//implictlyDeclaredFunctionList is used to capture implicitly declared functions; to be added to object class definitions at end
	vector<NLCitem *> implictlyDeclaredFunctionListTopLevel;	//top level function list (used to store implicitly declared functions without subject/context/owner)
	#endif

	currentCodeBlockInTree = createCodeBlockNewFunction(currentCodeBlockInTree, NLCfunctionName, entityNodesActiveListComplete);

	//NLCcodeblock * nextCodeBlockInTree = NULL;	//not used now; assume only 1 command in text
	//for each action (command) in sentence;

	//#ifdef NLC_USE_PREPROCESSOR
	NLCsentence * currentNLCsentenceInList = currentNLCfunctionInList->firstNLCsentenceInFunction;
	//#endif

	//cout << "maxNumberSentences = " << maxNumberSentences << endl;
	for(int sentenceIndex=GIA_NLP_START_SENTENCE_INDEX; sentenceIndex <= maxNumberSentences; sentenceIndex++)
	{
		#ifdef NLC_DEBUG
		cout << "*** sentenceIndex = " << sentenceIndex << endl;
		#endif

		#ifdef NLC_DEFINE_LOCAL_VARIABLES_FOR_ALL_INDEFINATE_ENTITIES
		//Part Prep A - declareLocalVariables (for non-specific indefinte entities, eg "a chicken", not "a blue chicken") - added 1g8a;
		#ifdef NLC_DEBUG
		cout << "generateCodeBlocksPart1declareLocalVariables:" << endl;
		#endif
		declareLocalPropertyListsForIndefiniteEntities(&currentCodeBlockInTree, entityNodesActiveListComplete, sentenceIndex, NLCfunctionName, currentNLCsentenceInList);	//added 1g8a 11-July-2014
		#endif

		#ifdef NLC_PREPROCESSOR_MATH
		if(getUseNLCpreprocessor() && (currentNLCsentenceInList->isMath))
		{
			//Part Prep B - generateCodeBlocksFromMathText - added 1h1d;
			#ifdef NLC_DEBUG
			cout << "generateCodeBlocksFromMathText:" << endl;
			#endif
			if(!generateCodeBlocksFromMathText(&currentCodeBlockInTree, entityNodesActiveListComplete, sentenceIndex, currentNLCsentenceInList))
			{
				result = false;
			}
		}
		else
		{
		#endif	
			#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
			//Part 1 - logical conditions (eg If the house is red, ride the boat) - added 1f1a;
			#ifdef NLC_DEBUG
			cout << "generateCodeBlocksPart2logicalConditions:" << endl;
			#endif
			if(!generateCodeBlocksPart2logicalConditions(&currentCodeBlockInTree, entityNodesActiveListComplete, sentenceIndex, NLCfunctionName, currentNLCsentenceInList))
			{
				result = false;
			}
			#endif

			//Part 2; actions (eg Tom rides the boat)
			#ifdef NLC_DEBUG
			cout << "generateCodeBlocksPart3actions:" << endl;
			#endif
			if(!generateCodeBlocksPart3actions(&currentCodeBlockInTree, entityNodesActiveListComplete, sentenceIndex, NLCfunctionName))
			{
				result = false;
			}

			//Part 3: object initialisations (eg Tom has a boat) [without actions]
			#ifdef NLC_DEBUG
			cout << "generateCodeBlocksPart4objectInitialisations:" << endl;
			#endif
			if(!generateCodeBlocksPart4objectInitialisations(&currentCodeBlockInTree, entityNodesActiveListComplete, sentenceIndex, NLCfunctionName))
			{
				result = false;
			}
		#ifdef NLC_PREPROCESSOR_MATH
		}
		#endif

		#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
		clearContextGeneratedVariable(entityNodesActiveListComplete);
		#endif


		#ifdef NLC_USE_PREPROCESSOR
		if(getUseNLCpreprocessor())
		{
			#ifdef NLC_PREPROCESSOR_MATH_REPLACE_NUMERICAL_VARIABLES_NAMES_FOR_NLP
			//reconcile temporary variable name replacement
			for(int i=0; i<currentNLCsentenceInList->variableNamesDetected.size(); i++)
			{	
				if(!(currentNLCsentenceInList->isMath))
				{//only replace variables names (and reconcile temporary variable name replacement) for non math text
					int dummyNumericalValue = generateDummyNumericalValue(i);
					string numericalVariableName = currentNLCsentenceInList->variableNamesDetected[i];
					#ifdef NLC_DEBUG_PREPROCESSOR_MATH_REPLACE_NUMERICAL_VARIABLES
					cout << "dummyNumericalValue = " << dummyNumericalValue << endl;
					cout << "numericalVariableName = " << numericalVariableName << endl;
					#endif
					if(!findAndReplaceDummyNumericalValue(entityNodesActiveListComplete, sentenceIndex, dummyNumericalValue, numericalVariableName))
					{
						cout << "generateCodeBlocks() error: !findAndReplaceDummyNumericalValue, dummyNumericalValueToRestore = " << dummyNumericalValue << ", numericalVariableName = " << numericalVariableName << endl;
					}
				}
				else
				{
					cout << "generateCodeBlocks() error: currentNLCsentenceInList->variableNamesDetected && currentNLCsentenceInList->isMath" << endl;
				}
			}
			#endif
		
			if(currentNLCsentenceInList->next != NULL)
			{
				#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
				NLCsentence * nextNLCfullSentenceInList = currentNLCsentenceInList->next;
				bool currentSentenceContainsLogicalCondition = getCurrentSentenceContainsLogicalCondition();
				#elif defined NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
				NLCsentence * nextNLCfullSentenceInList = currentNLCsentenceInList;
				for(int phraseIndex=0; phraseIndex<currentNLCsentenceInList->mathTextNLPparsablePhraseTotal; phraseIndex++)
				{
					nextNLCfullSentenceInList = nextNLCfullSentenceInList->next;
				}
				bool currentSentenceContainsLogicalCondition = currentNLCsentenceInList->hasLogicalConditionOperator;
				#else
				cout << "preprocessor error: NLC_USE_PREPROCESSOR && !NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED && !NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE" << endl;
				#endif
				
				if(nextNLCfullSentenceInList->indentation == (currentNLCsentenceInList->indentation + 1))
				{
					if(currentSentenceContainsLogicalCondition)
					{
						//indentation already correctly processed in generateCodeBlocksPart2logicalConditions()
					}
					else
					{
						cout << "NLC_USE_PREPROCESSOR generateCodeBlocks() error: invalid indentation of nextNLCfullSentenceInList, sentenceIndex = " << sentenceIndex << endl;
						cout << "!currentSentenceContainsLogicalCondition && nextNLCfullSentenceInList->indentation == currentNLCsentenceInList->indentation + 1" << endl;
						cout << "currentNLCsentenceInList->indentation = " << currentNLCsentenceInList->indentation << endl;
						cout << "nextNLCfullSentenceInList->indentation = " << nextNLCfullSentenceInList->indentation << endl;
					}
				}
				else if(nextNLCfullSentenceInList->indentation == currentNLCsentenceInList->indentation)
				{
					if(currentSentenceContainsLogicalCondition)
					{
						//indentation already correctly processed in generateCodeBlocksPart2logicalConditions()
					}
					else
					{
						//no changes
					}
				}
				else if(nextNLCfullSentenceInList->indentation < currentNLCsentenceInList->indentation)
				{
					if(getCurrentLogicalConditionLevel() == 0)
					{
						cout << "NLC_USE_PREPROCESSOR generateCodeBlocks() error: invalid indentation of currentNLCsentenceInList->next, sentenceIndex = " << sentenceIndex << endl;
						cout << "(currentLogicalConditionLevel == 0) && nextNLCfullSentenceInList->indentation < currentNLCsentenceInList->indentation" << endl;
						cout << "currentNLCsentenceInList->indentation = " << currentNLCsentenceInList->indentation << endl;
						cout << "nextNLCfullSentenceInList->indentation = " << nextNLCfullSentenceInList->indentation << endl;
					}
					else
					{
						currentCodeBlockInTree = getCodeBlockAtPreviousLogicalConditionBaseLevelArray(nextNLCfullSentenceInList->indentation);
						setCurrentLogicalConditionLevel(nextNLCfullSentenceInList->indentation);
					}
				}
				else
				{
					cout << "NLC_USE_PREPROCESSOR generateCodeBlocksPart2logicalConditions() error: invalid indentation of nextNLCfullSentenceInList, sentenceIndex = " << sentenceIndex << endl;
					cout << "nextNLCfullSentenceInList->indentation > currentNLCsentenceInList->indentation + 1" << endl;
					cout << "currentNLCsentenceInList->indentation = " << currentNLCsentenceInList->indentation << endl;
					cout << "nextNLCfullSentenceInList->indentation = " << nextNLCfullSentenceInList->indentation << endl;
				}
				currentNLCsentenceInList = currentNLCsentenceInList->next;
			}
			else
			{
				cout << "NLC_USE_PREPROCESSOR generateCodeBlocks() error: currentNLCsentenceInList->next == NULL, sentenceIndex = " << sentenceIndex << endl;
			}
			#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
			setCurrentSentenceContainsLogicalCondition(false);
			#endif
		}
		#endif

	}
	return result;
}

#ifdef NLC_PREPROCESSOR_MATH
bool generateCodeBlocksFromMathText(NLCcodeblock ** currentCodeBlockInTree, vector<GIAentityNode*> * entityNodesActiveListComplete, int sentenceIndex, NLCsentence * firstNLCsentenceInFullSentence)
{
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
		if(firstNLCsentenceInFullSentence->logicalConditionOperator == NLC_LOGICAL_CONDITION_OPERATIONS_IF)
		{
			/*
			//use the same logical condition check naming scheme as NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED;
			string logicalConditionConjunctionBooleanName = generateLogicalConditionConjunctionBooleanName(currentLogicalConditionLevel, currentLogicalConditionCase[currentLogicalConditionLevel], logicalOperation);							
			*currentCodeBlockInTree = createCodeBlockDeclareNewBoolArray(*currentCodeBlockInTree, logicalConditionConjunctionBooleanName, false);
			*/
			
			int caseIndex = 0;
			int currentLevel = firstNLCsentenceInFullSentence->indentation;
			int currentLogicalConditionOperator = firstNLCsentenceInFullSentence->logicalConditionOperator;
			bool stillFindingLogicalConditionAtCurrentLevel = true;
			NLCsentence * currentSentence = firstNLCsentenceInFullSentence;
			while(stillFindingLogicalConditionAtCurrentLevel)
			{
				bool isLogicalConditionOperatorAtCurrentLevel = false;
				if(currentSentence->hasLogicalConditionOperator)
				{
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
				
				NLCsentence * parsablePhrase = currentSentence;
				if(isLogicalConditionOperatorAtCurrentLevel)
				{
					int sentenceIndexOfFullSentence = currentSentence->sentenceIndex;
					for(int phraseIndex=0; phraseIndex<currentSentence->mathTextNLPparsablePhraseTotal; phraseIndex++)
					{
						if(parsablePhrase->mathTextNLPparsablePhraseIndex != phraseIndex)
						{
							cout << "generateCodeBlocksFromMathText() error: (currentSentence->mathTextNLPparsablePhraseIndex != i)" << endl;
						}
						if(!generateCodeBlocksFromMathTextNLPparsablePhrase(currentCodeBlockInTree, entityNodesActiveListComplete, parsablePhrase->sentenceIndex, firstNLCsentenceInFullSentence, parsablePhrase, phraseIndex, sentenceIndexOfFullSentence, caseIndex))
						{
							result = false;
						}
						parsablePhrase = parsablePhrase->next;
					}
					caseIndex++;
					currentSentence = parsablePhrase;
				}
				else
				{
					if(currentSentence->next != NULL)
					{
						currentSentence = currentSentence->next;
					}
				}
			}
		}
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
			if(!generateCodeBlocksFromMathTextNLPparsablePhrase(currentCodeBlockInTree, entityNodesActiveListComplete, parsablePhrase->sentenceIndex, firstNLCsentenceInFullSentence, parsablePhrase, phraseIndex, firstNLCsentenceInFullSentence->sentenceIndex, 0))
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
		if(firstNLCsentenceInFullSentence->logicalConditionOperator != NLC_LOGICAL_CONDITION_OPERATIONS_WHILE)
		{
			currentCodeBlockInTreeAtBaseLevel = *currentCodeBlockInTree;
		}
		if(firstNLCsentenceInFullSentence->logicalConditionOperator == NLC_LOGICAL_CONDITION_OPERATIONS_WHILE)
		{
			firstNLCsentenceInFullSentence->mathText.replace(0, string(NLC_LOGICAL_CONDITION_OPERATIONS_WHILE_STRING).length(), string(NLC_LOGICAL_CONDITION_OPERATIONS_IF_STRING));	//replace "while" with "if" for the purposes of generating final code (while loop has already been defined)
		}

		*currentCodeBlockInTree = createCodeBlockMathTextWithLogicalOperator(*currentCodeBlockInTree, firstNLCsentenceInFullSentence->mathText);
		
		if(firstNLCsentenceInFullSentence->logicalConditionOperator == NLC_LOGICAL_CONDITION_OPERATIONS_WHILE)
		{
			*currentCodeBlockInTree = createCodeBlockSetBoolVar(*currentCodeBlockInTree, whileLogicalConditionConjunctionBooleanName, true);
		}
		
		NLCsentence * nextNLCfullSentenceInList = firstNLCsentenceInFullSentence;
		for(int phraseIndex=0; phraseIndex<firstNLCsentenceInFullSentence->mathTextNLPparsablePhraseTotal; phraseIndex++)
		{
			nextNLCfullSentenceInList = nextNLCfullSentenceInList->next;
		}
					
		if(nextNLCfullSentenceInList->indentation == (firstNLCsentenceInFullSentence->indentation + 1))
		{
			//do not, just record the in the tree
			setCodeBlockAtPreviousLogicalConditionBaseLevelArray(firstNLCsentenceInFullSentence->indentation, currentCodeBlockInTreeAtBaseLevel->next);
			setCurrentLogicalConditionLevel(getCurrentLogicalConditionLevel() + 1);
		}
		else if(nextNLCfullSentenceInList->indentation <= firstNLCsentenceInFullSentence->indentation)
		{
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
	else
	{
	#endif
		*currentCodeBlockInTree = createCodeBlockMathTextLine(*currentCodeBlockInTree, firstNLCsentenceInFullSentence->mathText);
	#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
	}
	#endif
	
	
	return result;
}	

bool generateCodeBlocksFromMathTextNLPparsablePhrase(NLCcodeblock ** currentCodeBlockInTree, vector<GIAentityNode*> * entityNodesActiveListComplete, int sentenceIndex, NLCsentence * firstNLCsentenceInFullSentence, NLCsentence * parsablePhrase, int phraseIndex, int sentenceIndexOfFullSentence, int caseIndex)
{
	bool foundParsablePhrase = false;
	
	cout << "generateCodeBlocksFromMathTextNLPparsablePhrase() part 1" << endl;
	//generate NLP parsable phrase eg "the number of chickens" in "if(the number of chickens > the number of apples...)"
	NLCcodeblock * currentCodeBlockAtStartOfparsablePhrase = *currentCodeBlockInTree;
	string parsablePhraseReferenceName = generateMathTextNLPparsablePhraseReference(sentenceIndex, phraseIndex);	//parsablePhraseGenerateNumberOfElementCounterName
	*currentCodeBlockInTree = createCodeBlockDeclareNewIntVar(*currentCodeBlockInTree, parsablePhraseReferenceName, 0);	//?this will need to be changed to createCodeBlockDeclareNewIntArray in the future to support multiple cases (ie if, else if, else)
	
	//if !NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE, currently only accept entities with $qVar defined, eg "Number of red dogs". prep_of(number-4, dogs-7) [NLP] / _quantity(dog[8], _$qVar[1]) [GIA]
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode * entity = (*entityIter);
		if(checkSentenceIndexParsingCodeBlocks(entity, sentenceIndex, false))
		{
			if(entity->isQuery)
			{
				if(foundParsablePhrase)
				{
					cout << "generateCodeBlocksFromMathTextNLPparsablePhrase() error: more than one parsable phrase primary entity found" << endl;
				}
				foundParsablePhrase = true;
				
				cout << "generateCodeBlocksFromMathTextNLPparsablePhrase(): found 'number of' $qVar /  _quantity(dog[8], _$qVar[1]) variable: " << entity->entityName << endl;
				NLClogicalConditionConjunctionVariables logicalConditionConjunctionVariables;
				if(getParentAndInitialiseParentIfNecessaryAndGenerateContextBlocks(currentCodeBlockInTree, entity, sentenceIndex, &logicalConditionConjunctionVariables, true, false))	//NB parseConditionParents probably does not need to ever be set to true (unless condition subject/object are switched and condition name is updated accordingly to reflect this inversion of relationship)
				{
					cout << "generateCodeBlocksFromMathTextNLPparsablePhrase() error: parent of  parsable phrase primary entity not previously initialised" << endl;
				}
				
				*currentCodeBlockInTree = createCodeBlockIncrementIntVar(*currentCodeBlockInTree, parsablePhraseReferenceName);
				*currentCodeBlockInTree = currentCodeBlockAtStartOfparsablePhrase->next->next;
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
		cout << "generateCodeBlocksFromMathTextNLPparsablePhrase() part 2" << endl;
		*currentCodeBlockInTree = createCodeBlockDeclareNewBoolVar(*currentCodeBlockInTree, parsablePhraseReferenceName, false);	//?this will need to be changed to createCodeBlockDeclareNewBoolArray in the future to support multiple cases (ie if, else if, else)
		
		//generate NLP parsable phrase eg "the red chicken is next to the house" in "if(the red chicken is next to the house && the blue box has an apple)"
		if(firstNLCsentenceInFullSentence->hasLogicalConditionOperator)	//CHECKTHIS; is NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE required for non-logical condition mathText?
		{
			foundParsablePhrase = false;
			currentCodeBlockAtStartOfparsablePhrase = *currentCodeBlockInTree;
			for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
			{
				GIAentityNode * entity = (*entityIter);
				if(checkSentenceIndexParsingCodeBlocks(entity, sentenceIndex, false))
				{
					if(!(entity->NLCcontextGenerated))
					{
						if(entity->isQuery)
						{
							cout << "generateCodeBlocksFromMathTextNLPparsablePhrase() error: entity->isQuery && !(entity->NLCcontextGenerated): part 1 must have failed" << endl;
						}
						else
						{		
							foundParsablePhrase = true;

							NLClogicalConditionConjunctionVariables logicalConditionConjunctionVariables;
							if(getParentAndInitialiseParentIfNecessaryAndGenerateContextBlocks(currentCodeBlockInTree, entity, sentenceIndex, &logicalConditionConjunctionVariables, true, false))	//NB parseConditionParents probably does not need to ever be set to true (unless condition subject/object are switched and condition name is updated accordingly to reflect this inversion of relationship)
							{
								cout << "generateCodeBlocksFromMathTextNLPparsablePhrase() error: parent of  parsable phrase primary entity not previously initialised" << endl;
							}
							
							/*
							//use the same logical condition check naming scheme as NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED;
							string logicalConditionConjunctionBooleanName = generateLogicalConditionConjunctionBooleanName(getCurrentLogicalConditionLevel(), caseIndex, parsablePhrase, logicalOperation);
							*currentCodeBlockInTree = createCodeBlockSetBoolVar(*currentCodeBlockInTree, logicalConditionConjunctionBooleanName, true);							
							*/
							*currentCodeBlockInTree = createCodeBlockSetBoolVar(*currentCodeBlockInTree, parsablePhraseReferenceName, true);
							*currentCodeBlockInTree = currentCodeBlockAtStartOfparsablePhrase->next->next;
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
#endif

bool declareLocalPropertyListsForIndefiniteEntities(NLCcodeblock ** currentCodeBlockInTree, vector<GIAentityNode*> * entityNodesActiveListComplete, int sentenceIndex, string NLCfunctionName, NLCsentence * currentNLCsentenceInList)
{
	bool result = true;
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode * entity = (*entityIter);
		if(!(entity->isConcept) && !(entity->isAction) && !(entity->isSubstanceQuality) && !(entity->isSubstanceConcept) && !(entity->isCondition) && !(entity->isActionConcept))
		{
			#ifdef NLC_USE_PREPROCESSOR
			bool validClassContents = true;
			if((entity->entityName == NLC_PREPROCESSOR_LOGICAL_CONDITION_DUMMY_TEXT_ACTION) || (entity->entityName == NLC_PREPROCESSOR_LOGICAL_CONDITION_DUMMY_TEXT_ACTION_OBJECT))
			{
				validClassContents = false;
			}
			if(validClassContents)
			{
			#endif
				//cout << "pass1: " << entity->entityName << endl;
				if(checkSentenceIndexParsingCodeBlocks(entity, sentenceIndex, false))
				{
					//cout << "pass2: " << entity->entityName << endl;
					if(!assumedToAlreadyHaveBeenDeclared(entity))
					{//indefinite entity found
						if(!(entity->NLClocalListVariableHasBeenDeclared))
						{
							//cout << "pass3: " << entity->entityName << endl;
							/*OLD declareLocalPropertyListsForAllNonSpecificIndefiniteEntities() code;
							bool foundPropertyInSameSentence = false;
							bool foundConditionInSameSentence = false;
							for(vector<GIAentityConnection*>::iterator propertyNodeListIterator = entity->propertyNodeList->begin(); propertyNodeListIterator < entity->propertyNodeList->end(); propertyNodeListIterator++)
							{
								GIAentityNode* propertyEntity = (*propertyNodeListIterator)->entity;
								if(checkSentenceIndexParsingCodeBlocks(propertyEntity, sentenceIndex, false))
								{
									foundPropertyInSameSentence = true;
								}
							}
							for(vector<GIAentityConnection*>::iterator conditionNodeListIterator = entity->conditionNodeList->begin(); conditionNodeListIterator < entity->conditionNodeList->end(); conditionNodeListIterator++)
							{
								GIAentityNode* conditionEntity = (*conditionNodeListIterator)->entity;
								if(checkSentenceIndexParsingCodeBlocks(conditionEntity, sentenceIndex, false))
								{
									foundConditionInSameSentence = true;
								}
							}
							if(!foundPropertyInSameSentence && !foundConditionInSameSentence)
							{
							*/
							
							#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
							#ifdef NLC_USE_PREPROCESSOR
							#ifdef NLC_PREPROCESSOR_LOGICAL_CONDITION_USE_ROBUST_NLP_INDEPENDENT_CODE
							NLCcodeblock * firstCodeBlockAtStartOfElseStatement = *currentCodeBlockInTree;
							NLCcodeblock * firstCodeBlockAtStartOfIfStatement = NULL;
							NLCcodeblock * previousCodeBlockInTree = NULL;
							setCurrentCodeBlockInTreeToStartOfIfStatement(currentCodeBlockInTree, &firstCodeBlockAtStartOfIfStatement, firstCodeBlockAtStartOfElseStatement, currentNLCsentenceInList->elseIfDetected, currentNLCsentenceInList->elseDetected);
							previousCodeBlockInTree = *currentCodeBlockInTree;
							#endif
							#endif
							#endif
							
							*currentCodeBlockInTree = createCodeBlocksDeclareNewLocalListVariable(*currentCodeBlockInTree, entity);
							
							#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
							#ifdef NLC_USE_PREPROCESSOR
							#ifdef NLC_PREPROCESSOR_LOGICAL_CONDITION_USE_ROBUST_NLP_INDEPENDENT_CODE
							restoreCurrentCodeBlockInTreeToStartOfElseStatement(currentCodeBlockInTree, firstCodeBlockAtStartOfIfStatement, firstCodeBlockAtStartOfElseStatement, currentNLCsentenceInList->elseIfDetected, currentNLCsentenceInList->elseDetected, &previousCodeBlockInTree);
							#endif
							#endif
							#endif
							
							#ifdef NLC_DEBUG
							cout << "declareLocalPropertyListsForIndefiniteEntities(): createCodeBlocksDeclareNewLocalListVariable for " << entity->entityName << endl;
							#endif
							entity->NLClocalListVariableHasBeenDeclared = true;
							/*
							}
							*/
							
						}
					}
				}
			#ifdef NLC_USE_PREPROCESSOR
			}
			#endif
		}
	}
	return result;
}

bool generateCodeBlocksPart3actions(NLCcodeblock ** currentCodeBlockInTree, vector<GIAentityNode*> * entityNodesActiveListComplete, int sentenceIndex, string NLCfunctionName)
{
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode * actionEntity = (*entityIter);
		if(actionEntity->isAction)
		{
			if(!(actionEntity->isActionConcept))
			{
				//cout << "actionEntity->isAction = " << actionEntity->isAction << endl;
				//cout << "actionEntity->hasAssociatedInstance = " << actionEntity->hasAssociatedInstance << endl;

				if(checkSentenceIndexParsingCodeBlocks(actionEntity, sentenceIndex, true))
				{
					generateActionCodeBlocks(currentCodeBlockInTree, actionEntity, sentenceIndex, NLCfunctionName);
				}
			}
		}
	}
	return true;
}






bool generateCodeBlocksPart4objectInitialisations(NLCcodeblock ** currentCodeBlockInTree, vector<GIAentityNode*> * entityNodesActiveListComplete, int sentenceIndex, string NLCfunctionName)
{
	bool result = true;
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode * entity = *entityIter;
		if(checkSentenceIndexParsingCodeBlocks(entity, sentenceIndex, false))
		{
			if(!(entity->isConcept) && !(entity->isAction) && !(entity->isSubstanceConcept) && !(entity->isCondition) && !(entity->isActionConcept))
			{
				#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
				generateCodeBlocksObjectInitialisationsForEntity(currentCodeBlockInTree, entity, sentenceIndex);
				#else
				GIAentityNode * parentEntity = getParent(entity, sentenceIndex, true);
				if(!generateParentInitialisationCodeBlock(currentCodeBlockInTree, parentEntity , sentenceIndex, false))
				{
					generateObjectInitialisationsBasedOnPropertiesAndConditions(parentEntity, currentCodeBlockInTree , sentenceIndex, "", "", false);
				}
				#endif
			}
		}
	}
	return result;
}



#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
bool clearContextGeneratedVariable(vector<GIAentityNode*> * entityNodesActiveListComplete)
{
	bool result = true;
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode * entity = *entityIter;
		entity->NLCcontextGenerated = false;

	}
	return result;
}
#endif

#ifdef NLC_PREPROCESSOR_MATH_REPLACE_NUMERICAL_VARIABLES_NAMES_FOR_NLP
bool findAndReplaceDummyNumericalValue(vector<GIAentityNode*> * entityNodesActiveListComplete, int sentenceIndex, int dummyNumericalValue, string numericalVariableName)
{
	bool result = true;
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode * entity = (*entityIter);
		if(checkSentenceIndexParsingCodeBlocks(entity, sentenceIndex, false))
		{
			if(entity->quantityNumber == dummyNumericalValue)
			{
				entity->NLCoriginalNumericalVariableName = numericalVariableName;
				result = true;
			}
		}
		
	}
	return result;
}
#endif





