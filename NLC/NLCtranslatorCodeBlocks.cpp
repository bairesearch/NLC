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
 * Project Version: 1j12b 12-September-2014
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/



#include <ctime>
#include <cstdlib>	//for random number generation
#include <cmath>

#include "NLCtranslatorCodeBlocks.h"
#include "NLCtranslatorCodeBlocksLogicalConditions.h"
#include "NLCtranslatorCodeBlocksOperations.h"
#include "GIAtranslatorOperations.h"	//required for getPrimaryConceptNodeDefiningInstance()

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

	#ifdef NLC_DEBUG
	cout << "maxNumberSentences = " << maxNumberSentences << endl;
	#endif
	int sentenceIndex=GIA_NLP_START_SENTENCE_INDEX;
	while(sentenceIndex <= maxNumberSentences)
	{
		#ifdef NLC_DEBUG
		cout << "*** sentenceIndex = " << sentenceIndex << endl;
		#endif

		#ifdef NLC_PREPROCESSOR_GENERATE_COMMENTS
		if(getUseNLCpreprocessor())
		{
			if(currentNLCsentenceInList->isMath)
			{
				currentCodeBlockInTree = createCodeBlockCommentSingleLine(currentCodeBlockInTree, currentNLCsentenceInList->sentenceOriginal);
			}
			else
			{
				currentCodeBlockInTree = createCodeBlockCommentSingleLine(currentCodeBlockInTree, currentNLCsentenceInList->sentenceContents);
			}
		}
		#endif
			
		#ifdef NLC_DEFINE_LOCAL_VARIABLES_FOR_ALL_INDEFINATE_ENTITIES
		//Part Prep A - declareLocalVariables (for non-specific indefinte entities, eg "a chicken", not "a blue chicken") - added 1g8a;
		#ifdef NLC_DEBUG
		cout << "generateCodeBlocksPart1declareLocalVariables:" << endl;
		#endif
		declareLocalPropertyListsForIndefiniteEntities(&currentCodeBlockInTree, entityNodesActiveListComplete, sentenceIndex, NLCfunctionName, currentNLCsentenceInList);	//added 1g8a 11-July-2014
		#endif
		
		#ifdef NLC_GENERATE_OBJECT_INITIALISATIONS_BASED_ON_SUBSTANCE_CONCEPTS_FOR_ALL_DEFINITE_ENTITIES
		generateObjectInitialisationsBasedOnSubstanceConceptsForAllDefiniteEntities(&currentCodeBlockInTree, entityNodesActiveListComplete, sentenceIndex);
		#endif

		#ifdef NLC_PREPROCESSOR_MATH_REPLACE_NUMERICAL_VARIABLES_NAMES_FOR_NLP
		if(getUseNLCpreprocessor())
		{
			//reconcile temporary variable name replacement
			for(int i=0; i<currentNLCsentenceInList->variableNamesDetected.size(); i++)
			{	
				if(!(currentNLCsentenceInList->isMath))
				{//only replace variables names (and reconcile temporary variable name replacement) for non math text
					int dummyNumericalValue = generateDummyNumericalValue(i+1);
					string numericalVariableName = currentNLCsentenceInList->variableNamesDetected[i];
					#ifdef NLC_DEBUG_PREPROCESSOR_MATH_REPLACE_NUMERICAL_VARIABLES
					cout << "currentNLCsentenceInList->sentenceContents = " << currentNLCsentenceInList->sentenceContents << endl; 
					cout << "dummyNumericalValue = " << dummyNumericalValue << endl;
					cout << "numericalVariableName = " << numericalVariableName << endl;
					#endif
					if(!findAndSetDummyNumericalValueForReplacement(entityNodesActiveListComplete, sentenceIndex, dummyNumericalValue, numericalVariableName))
					{
						cout << "generateCodeBlocks() error: !findAndSetDummyNumericalValueForReplacement, dummyNumericalValueToRestore = " << dummyNumericalValue << ", numericalVariableName = " << numericalVariableName << endl;
					}
				}
				else
				{
					cout << "generateCodeBlocks() error: currentNLCsentenceInList->variableNamesDetected && currentNLCsentenceInList->isMath" << endl;
				}
			}
		}
		#endif
		
		#ifdef NLC_PREPROCESSOR_MATH
		if(getUseNLCpreprocessor() && (currentNLCsentenceInList->isMath))
		{
			#ifdef NLC_DEBUG_PREPROCESSOR_MATH
			cout << "generateCodeBlocksFromMathText(): currentNLCsentenceInList->mathText = " << currentNLCsentenceInList->mathText << endl;
			#endif
			
			//Part Prep B - generateCodeBlocksFromMathText - added 1h1d;
			#ifdef NLC_DEBUG
			cout << "generateCodeBlocksFromMathText:" << endl;
			#endif
			if(!generateCodeBlocksFromMathText(&currentCodeBlockInTree, entityNodesActiveListComplete, sentenceIndex, currentNLCsentenceInList, NLCfunctionName))
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
			if(currentNLCsentenceInList->next != NULL)
			{
				#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
				NLCsentence * nextNLCfullSentenceInList = currentNLCsentenceInList->next;
				bool currentSentenceContainsLogicalCondition = getCurrentSentenceContainsLogicalCondition();
				int currentLogicalConditionLevel = getCurrentLogicalConditionLevel();
				#elif defined NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
				NLCsentence * nextNLCfullSentenceInList = currentNLCsentenceInList;
				if(currentNLCsentenceInList->mathTextNLPparsablePhraseTotal > 0)
				{
					for(int phraseIndex=0; phraseIndex<currentNLCsentenceInList->mathTextNLPparsablePhraseTotal; phraseIndex++)
					{
						nextNLCfullSentenceInList = nextNLCfullSentenceInList->next;
					}
				}
				else
				{
					nextNLCfullSentenceInList = currentNLCsentenceInList->next;
				}
				#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
				cout << "\tcurrentNLCsentenceInList->mathTextNLPparsablePhraseTotal = " << currentNLCsentenceInList->mathTextNLPparsablePhraseTotal << endl;
				cout << "currentNLCsentenceInList->sentenceIndex = " << currentNLCsentenceInList->sentenceIndex << endl;
				cout << "currentNLCsentenceInList->sentenceContents = " << currentNLCsentenceInList->sentenceContents << endl;
				cout << "nextNLCfullSentenceInList->sentenceContents = " << nextNLCfullSentenceInList->sentenceContents << endl;
				cout << "currentNLCsentenceInList->indentation = " << currentNLCsentenceInList->indentation << endl;
				cout << "nextNLCfullSentenceInList->indentation = " << nextNLCfullSentenceInList->indentation << endl;
				#endif
				bool currentSentenceContainsLogicalCondition = currentNLCsentenceInList->hasLogicalConditionOperator;
				int currentLogicalConditionLevel = currentNLCsentenceInList->indentation;
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
					if(currentLogicalConditionLevel == 0)
					{
						cout << "NLC_USE_PREPROCESSOR generateCodeBlocks() error: invalid indentation of currentNLCsentenceInList->next, sentenceIndex = " << sentenceIndex << endl;
						cout << "(currentLogicalConditionLevel == 0) && nextNLCfullSentenceInList->indentation < currentNLCsentenceInList->indentation" << endl;
						cout << "currentNLCsentenceInList->indentation = " << currentNLCsentenceInList->indentation << endl;
						cout << "nextNLCfullSentenceInList->indentation = " << nextNLCfullSentenceInList->indentation << endl;
					}
					else
					{
						currentCodeBlockInTree = getCodeBlockAtPreviousLogicalConditionBaseLevelArray(nextNLCfullSentenceInList->indentation);
						#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
						setCurrentLogicalConditionLevel(nextNLCfullSentenceInList->indentation);
						#endif
					}
				}
				else
				{
					cout << "NLC_USE_PREPROCESSOR generateCodeBlocksPart2logicalConditions() error: invalid indentation of nextNLCfullSentenceInList, sentenceIndex = " << sentenceIndex << endl;
					cout << "nextNLCfullSentenceInList->indentation > currentNLCsentenceInList->indentation + 1" << endl;
					cout << "currentNLCsentenceInList->indentation = " << currentNLCsentenceInList->indentation << endl;
					cout << "nextNLCfullSentenceInList->indentation = " << nextNLCfullSentenceInList->indentation << endl;
				}
				
				if(nextNLCfullSentenceInList->next != NULL)
				{	
					sentenceIndex = nextNLCfullSentenceInList->sentenceIndex;
				}
				else
				{
					sentenceIndex = maxNumberSentences+1;
				}
				currentNLCsentenceInList = nextNLCfullSentenceInList;
				//cout << "next sentenceIndex = " << sentenceIndex << endl;
			}
			else
			{
				sentenceIndex++;
				//cout << "NLC_USE_PREPROCESSOR generateCodeBlocks() error: currentNLCsentenceInList->next == NULL, sentenceIndex = " << sentenceIndex << endl;
			}
			#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
			setCurrentSentenceContainsLogicalCondition(false);
			#endif
		}
		else
		{
			sentenceIndex++;
		}
		#else
		sentenceIndex++;
		#endif

	}

	return result;
}

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
				
				#ifdef NLC_ACTIVATE_PRE1i_CODE_FOR_DEBUG
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
						/*
						cout << "generateCodeBlocksFromMathText(): NLC_LOGICAL_CONDITION_OPERATIONS_FOR does not currently support multiple nlp parsable phrases" << endl;
						exit(0);
						*/
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
								if(!generateCodeBlocksFromMathTextNLPparsablePhraseLogicalConditionFor(currentCodeBlockInTree, entityNodesActiveListComplete, parsablePhrase->sentenceIndex, currentSentence, parsablePhrase, phraseIndex))
								{
									result = false;
								}
							}
							else
							{
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
			if(firstNLCsentenceInFullSentence->logicalConditionOperator != NLC_LOGICAL_CONDITION_OPERATIONS_WHILE)
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
				//cout << "sentenceIndex = " << sentenceIndex << endl;
				//cout << "checkSentenceIndexParsingCodeBlocks: " << entity->entityName << "sentenceIndex = " << entity->sentenceIndexTemp << endl;
				if(entity->isQuery)
				{
					if(foundParsablePhrase)
					{
						cout << "generateCodeBlocksFromMathTextNLPparsablePhrase() error: more than one parsable phrase primary entity found" << endl;
					}
					foundParsablePhrase = true;

					#ifdef NLC_DEBUG_PREPROCESSOR_MATH
					cout << "generateCodeBlocksFromMathTextNLPparsablePhrase(): found 'number of' designation, entity: " << entity->entityName << endl;
					#endif
					NLClogicalConditionConjunctionVariables logicalConditionConjunctionVariables;
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
						entity->grammaticalDefiniteTemp = true;		//set NLClocalListVariableHasBeenInitialised instead?
						#endif					
					//}
					#endif
					if(!getParentAndGenerateContextBlocks(currentCodeBlockInTree, entity, sentenceIndex, &logicalConditionConjunctionVariables, true))	//NB parseConditionParents probably does not need to ever be set to true (unless condition subject/object are switched and condition name is updated accordingly to reflect this inversion of relationship)
					{
						cout << "generateCodeBlocksFromMathTextNLPparsablePhrase() error: !getParentAndGenerateContextBlocks" << endl;
					}

					*currentCodeBlockInTree = createCodeBlockIncrementIntVar(*currentCodeBlockInTree, parsablePhraseReferenceName);

					*currentCodeBlockInTree = currentCodeBlockAtStartOfparsablePhrase;
					while((*currentCodeBlockInTree)->next != NULL)
					{
						(*currentCodeBlockInTree) = (*currentCodeBlockInTree)->next;
					}				
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
						if(entity->isQuery)
						{
							//cout << "generateCodeBlocksFromMathTextNLPparsablePhrase() error: entity->isQuery && !(entity->NLCcontextGenerated): part 1 must have failed" << endl;
						}
						else
						{		
							if(!foundParsablePhrase)
							{
								#ifdef NLC_DEBUG_PREPROCESSOR_MATH
								cout << "generateCodeBlocksFromMathTextNLPparsablePhrase(): found entity: " << entity->entityName << endl;
								#endif

								NLClogicalConditionConjunctionVariables logicalConditionConjunctionVariables;
								NLCcodeblock * NLCcodeBlockBeforeGenerateContext = *currentCodeBlockInTree; 
								#ifdef NLC_LOGICAL_CONDITION_OPERATIONS_SUPPORT_INDEFINITE_LOGICAL_CONDITION_OBJECTS
								//if/while statements can be expressed using either definite or indefinate variables, but if they indefinite they will not be advanced referenced by GIA (and so must be located in the typeList)
								if(!assumedToAlreadyHaveBeenDeclared(entity))
								{
									#ifdef NLC_GENERATE_TYPE_LISTS
									//1i implementation
									*currentCodeBlockInTree = createCodeBlockForPropertyTypeClass(*currentCodeBlockInTree, entity);	//eg "If a house is green, do this", an instanceList (OLD: localList) for "a house" is assumed to have already been declared, one of which may be green, so search all house instanceLists within house typeList...
									//if at least one instanceList of type currentLogicalConditionObject has not previously been declared, then the code will result in a compilation error
									//if at least one instanceList of type currentLogicalConditionObject has previously been declared, but does not have the required properties (eg green), then the code will compile but the if statement will fail
									#else
									//1j implementation
									entity->grammaticalDefiniteTemp = true;		//set NLClocalListVariableHasBeenInitialised instead?
									#endif
								}
								#endif
								if(!getParentAndGenerateContextBlocks(currentCodeBlockInTree, entity, sentenceIndex, &logicalConditionConjunctionVariables, true))	//NB parseConditionParents probably does not need to ever be set to true (unless condition subject/object are switched and condition name is updated accordingly to reflect this inversion of relationship)
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
									
									if(logicalConditionConjunctionVariables.negativeDetectedInContextBlocks)
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

									*currentCodeBlockInTree = currentCodeBlockAtStartOfparsablePhrase;
									while((*currentCodeBlockInTree)->next != NULL)
									{
										(*currentCodeBlockInTree) = (*currentCodeBlockInTree)->next;
									}								
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

bool generateCodeBlocksFromMathTextNLPparsablePhraseLogicalConditionFor(NLCcodeblock ** currentCodeBlockInTree, vector<GIAentityNode*> * entityNodesActiveListComplete, int sentenceIndex, NLCsentence * currentFullSentence, NLCsentence * parsablePhrase, int phraseIndex)
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
						NLClogicalConditionConjunctionVariables logicalConditionConjunctionVariables;
						NLCcodeblock * NLCcodeBlockBeforeGenerateContext = *currentCodeBlockInTree; 
						/*//for statements must be expressed using definite variables, and they will be advanced referenced by GIA (ie "for all the chickens...", not "for a chicken..")
						if(!assumedToAlreadyHaveBeenDeclared(entity))
						{
						      *currentCodeBlockInTree = createCodeBlockForPropertyTypeClass(*currentCodeBlockInTree, entity);   //eg "If a house is green, do this", an instanceList (OLD: localList) for "a house" is assumed to have already been declared, one of which may be green, so search all house instanceLists within house typeList...
						      //if at least one instanceList of type currentLogicalConditionObject has not previously been declared, then the code will result in a compilation error
						      //if at least one instanceList of type currentLogicalConditionObject has previously been declared, but does not have the required properties (eg green), then the code will compile but the if statement will fail
						}
						*/
						if(!getParentAndGenerateContextBlocks(currentCodeBlockInTree, entity, sentenceIndex, &logicalConditionConjunctionVariables, true))	//NB parseConditionParents probably does not need to ever be set to true (unless condition subject/object are switched and condition name is updated accordingly to reflect this inversion of relationship)
						{
							#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
							cout << "generateCodeBlocksFromMathTextNLPparsablePhrase() error: !getParentAndGenerateContextBlocks: sentenceIndex = " << sentenceIndex << endl;
							#endif

							*currentCodeBlockInTree = NLCcodeBlockBeforeGenerateContext;
							clearCodeBlock(*currentCodeBlockInTree);							
						}
						else
						{
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

						*currentCodeBlockInTree = createCodeBlocksDeclareNewLocalListVariableIfNecessary(*currentCodeBlockInTree, entity);

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
				if(!generateParentInitialisationCodeBlockWithChecks(currentCodeBlockInTree, parentEntity , sentenceIndex, false))
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
				//cout << "entity->quantityNumber = " << entity->quantityNumber << endl;
				//cout << "dummyNumericalValue = " << dummyNumericalValue << endl;
				//cout << "sentenceIndex = " << sentenceIndex << endl;
				entity->NLCoriginalNumericalVariableName = numericalVariableName;
				result = true;
			}
		}
		
	}
	return result;
}
#endif


#ifdef NLC_GENERATE_OBJECT_INITIALISATIONS_BASED_ON_SUBSTANCE_CONCEPTS_FOR_ALL_DEFINITE_ENTITIES
bool generateObjectInitialisationsBasedOnSubstanceConceptsForAllDefiniteEntities(NLCcodeblock ** currentCodeBlockInTree, vector<GIAentityNode*> * entityNodesActiveListComplete, int sentenceIndex)
{
	bool result = true;
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode * entity = (*entityIter);
		if(!(entity->isConcept) && !(entity->isAction) && !(entity->isSubstanceQuality) && !(entity->isSubstanceConcept) && !(entity->isCondition) && !(entity->isActionConcept))
		{
			//cout << "pass1: " << entity->entityName << endl;
			if(checkSentenceIndexParsingCodeBlocks(entity, sentenceIndex, false))
			{
				//cout << "pass2: " << entity->entityName << endl;
				if(assumedToAlreadyHaveBeenDeclared(entity))
				{//definite entity found
					generateObjectInitialisationsBasedOnSubstanceConcepts(entity, currentCodeBlockInTree, sentenceIndex, false);
				}	
			}
		}
	}
	return result;
}
#endif


