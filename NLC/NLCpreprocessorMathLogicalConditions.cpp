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
 * File Name: NLCpreprocessorMathLogicalConditions.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2014 Baxter AI (baxterai.com)
 * Project: Natural Language Programming Interface (compiler)
 * Project Version: 1k6b 14-October-2014
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/



#include <ctime>
#include <cstdlib>	//for random number generation
#include <cmath>

#include "NLCpreprocessorMathLogicalConditions.h"
#include "SHAREDvars.h"

#ifdef NLC_PREPROCESSOR_MATH
#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE

#ifdef NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
NLCsuperphrase::NLCsuperphrase(void)
{
	lineIndexOfFirstCharacterInPhrase = INT_DEFAULT_VALUE;
	phraseContents = "";
	hasConjunction = false;
	conjunctionType = INT_DEFAULT_VALUE;
	next = NULL;
}
NLCsuperphrase::~NLCsuperphrase(void)
{
}
#endif

bool replaceLogicalConditionNaturalLanguageMathWithSymbols(string * lineContents, int logicalConditionOperator, bool * additionalClosingBracketRequired, bool parallelReplacement)
{
	bool result = true;
	
	for(int i=0; i<NLC_PREPROCESSOR_MATH_OPERATORS_NUMBER_OF_TYPES; i++)
	{
		*lineContents = replaceAllOccurancesOfString(lineContents, preprocessorMathOperatorsEquivalentNumberOfTypes[i], preprocessorMathOperatorsForLogicalConditions[i]);	//NB this is type sensitive; could be changed in the future
	}
	
	if(!parallelReplacement)
	{
		//replace the logical condition operator with a lower case version if necessary
		lineContents->replace(0, logicalConditionOperationsArray[logicalConditionOperator].length(), logicalConditionOperationsArray[logicalConditionOperator]);
	}
	
	/*
	for(int i=0; i<NLC_LOGICAL_CONDITION_OPERATIONS_NUMBER_OF_TYPES; i++)
	{
		int index = lineContents->find(logicalConditionOperationsArray[i]);
		if((index != CPP_STRING_FIND_RESULT_FAIL_VALUE) && (index == 0))
		{
			logicalConditionOperatorFound = true;
			*logicalConditionOperator = i;
			cout << "detectLogicalConditionOperatorAtStartOfLine(): logicalConditionOperatorFound" << logicalConditionOperationsArray[i] << endl; 
		}
	}
	*/
	
	if(logicalConditionOperator != NLC_LOGICAL_CONDITION_OPERATIONS_ELSE)
	{
		//detect conjunctions...
		*additionalClosingBracketRequired = false;
		#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE_REPLACE_COMMAS_WITH_BRACKETS
		for(int i=0; i<NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_COORDINATING_CONJUNCTION_WITH_PAUSE_ARRAY_NUMBER_OF_TYPES; i++)
		{
			int index = (*lineContents).find(preprocessorMathOperatorsEquivalentConjunctionsWithPause[i]);	//NB this is type sensitive; could be changed in the future
			if(index != CPP_STRING_FIND_RESULT_FAIL_VALUE)
			{
				*additionalClosingBracketRequired = true;
			}
			#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
			cout << "additionalClosingBracketRequired" << endl;
			#endif
		}
		#endif
		for(int i=0; i<NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_COORDINATING_CONJUNCTION_ARRAY_NUMBER_OF_TYPES; i++)
		{
			*lineContents = replaceAllOccurancesOfString(lineContents, preprocessorMathOperatorsEquivalentConjunctions[i], progLangCoordinatingConjunctions[i]);	//NB this is type sensitive; could be changed in the future
		}

		//ensure all logical condition operators have enclosing brackets eg if(...) - this is done to prevent "if" in "if the house is cold" from being merged into an NLP parsable phrase

		if(!parallelReplacement)
		{
			char characterAfterLogicalConditionOperator = lineContents->at(logicalConditionOperationsArray[logicalConditionOperator].length());
			if(characterAfterLogicalConditionOperator == NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_OPEN_BRACKET)
			{//NB intermediary white text not currently supported, eg "if (...)"
				#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE_REPLACE_COMMAS_WITH_BRACKETS
				if(*additionalClosingBracketRequired)
				{
					lineContents->insert(logicalConditionOperationsArray[logicalConditionOperator].length()+1, 1, NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_OPEN_BRACKET);
				}
				#endif
			}
			else if(characterAfterLogicalConditionOperator == CHAR_SPACE)
			{
				lineContents->replace(logicalConditionOperationsArray[logicalConditionOperator].length(), 1, NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_OPEN_BRACKET_STRING);
				#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE_REPLACE_COMMAS_WITH_BRACKETS
				if(*additionalClosingBracketRequired)
				{
					lineContents->insert(logicalConditionOperationsArray[logicalConditionOperator].length()+1, 1, NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_OPEN_BRACKET);
				}	
				#endif
			}
			else
			{
				cout << "replaceLogicalConditionNaturalLanguageMathWithSymbols() error: invalid symbol found after logicalConditionOperator: " << logicalConditionOperationsArray[logicalConditionOperator] << characterAfterLogicalConditionOperator << endl;
			}
		}
	}
	
	#ifdef NLC_PREPROCESSOR_MATH_FIX_USER_INAPPROPRIATE_USE_OF_EQUALS_SET_IN_LOGICAL_CONDITIONS
	*lineContents = replaceAllOccurancesOfString(lineContents, NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_SET_WITH_PADDING, NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_TEST_WITH_PADDING);
	#endif
	
	return result;
}

bool replaceLogicalConditionNaturalLanguageMathWithSymbolsEnd(NLCsentence * firstNLCsentenceInFullSentence, bool additionalClosingBracketRequired)
{
	bool result = true;
	
	//remove all commas from mathText:
	firstNLCsentenceInFullSentence->mathText = replaceAllOccurancesOfString(&(firstNLCsentenceInFullSentence->mathText), ", ", "");	//added 1j19a
	firstNLCsentenceInFullSentence->mathText = replaceAllOccurancesOfString(&(firstNLCsentenceInFullSentence->mathText), STRING_COMMA, "");
	#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
	cout << "remove all commas from mathText: mathText = " << firstNLCsentenceInFullSentence->mathText << endl;
	#endif

	if(firstNLCsentenceInFullSentence->logicalConditionOperator != NLC_LOGICAL_CONDITION_OPERATIONS_ELSE)
	{	
		char lastCharacterInMathText = firstNLCsentenceInFullSentence->mathText[firstNLCsentenceInFullSentence->mathText.length()-1];
		if(lastCharacterInMathText == NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_CLOSE_BRACKET)
		{//NB intermediary white text not currently supported, eg "if (...)"
			#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE_REPLACE_COMMAS_WITH_BRACKETS
			if(additionalClosingBracketRequired)
			{
				firstNLCsentenceInFullSentence->mathText.insert(firstNLCsentenceInFullSentence->mathText.length(), 1, NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_CLOSE_BRACKET);
			}
			#endif
		}
		else
		{
			firstNLCsentenceInFullSentence->mathText.insert(firstNLCsentenceInFullSentence->mathText.length(), 1, NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_CLOSE_BRACKET);
			#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE_REPLACE_COMMAS_WITH_BRACKETS
			if(additionalClosingBracketRequired)
			{
				firstNLCsentenceInFullSentence->mathText.insert(firstNLCsentenceInFullSentence->mathText.length(), 1, NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_CLOSE_BRACKET);
			}	
			#endif
			#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
			cout << "insert CLOSE_BRACKET: mathText = " << firstNLCsentenceInFullSentence->mathText << endl;
			#endif
		}
	}
	
	return result;
}





bool splitMathDetectedLineIntoNLPparsablePhrasesLogicalConditionCommands(NLCsentence * firstNLCsentenceInFullSentence, NLCsentence ** currentNLCsentenceInList, int * sentenceIndex, bool additionalClosingBracketRequired, bool detectedLogicalConditionCommand, int phraseIndexOfFirstLogicalCommand, string logicalConditionCommandSuperphraseContents)
{
	bool result = true;
	
	int currentIndentation = firstNLCsentenceInFullSentence->indentation;

	#ifdef NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
	if(detectedLogicalConditionCommand)
	{
		#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
		cout << "detectedLogicalConditionCommand: mathText = " << firstNLCsentenceInFullSentence->mathText << endl;
		cout << "phraseIndexOfFirstLogicalCommand = " << phraseIndexOfFirstLogicalCommand << endl;
		#endif
		
		if(phraseIndexOfFirstLogicalCommand == 0)
		{//eg If x+5 == 12405, X = 3+5 OR If x+5 == 12405, the dog is happy
		
		}

		NLCsentence * firstPhraseInLogicalConditionCommandOld = firstNLCsentenceInFullSentence;
		NLCsentence * lastPhraseBeforeLogicalConditionCommand = firstNLCsentenceInFullSentence;

		if(phraseIndexOfFirstLogicalCommand > 0)
		{
			for(int phraseIndex = 0; phraseIndex < phraseIndexOfFirstLogicalCommand; phraseIndex++)
			{
				lastPhraseBeforeLogicalConditionCommand = firstPhraseInLogicalConditionCommandOld;
				firstPhraseInLogicalConditionCommandOld = firstPhraseInLogicalConditionCommandOld->next;
			}
		}
		else
		{
			//eg If x+5 == 12405, the dog is happy
		}

		int indexOfLogicalConditionCommandInMathText;
		bool logicalConditionCommandContainsNLPparsablePhrase = false;
		if((firstPhraseInLogicalConditionCommandOld->sentenceContents != "") && (firstNLCsentenceInFullSentence->sentenceContents != NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_DUMMY))
		{
			logicalConditionCommandContainsNLPparsablePhrase = true;
			string firstParsablePhraseReferenceInLogicalConditionCommand = generateMathTextNLPparsablePhraseReference(firstNLCsentenceInFullSentence->sentenceIndex, firstPhraseInLogicalConditionCommandOld);
			//cout << "firstParsablePhraseReferenceInLogicalConditionCommand = " << firstParsablePhraseReferenceInLogicalConditionCommand << endl;
			indexOfLogicalConditionCommandInMathText = firstNLCsentenceInFullSentence->mathText.find(firstParsablePhraseReferenceInLogicalConditionCommand);
			//cout << "indexOfLogicalConditionCommandInMathText = " << indexOfLogicalConditionCommandInMathText << endl;
		}
		else
		{//logical condition command does not contain an nlp parsable phrase; it is just math, eg; "If the house is blue, X = 3+5"
			//cout << "logical condition command does not contain an nlp parsable phrase; it is just math" << endl;
			//cout << "\n\nphraseIndexOfFirstLogicalCommand = " << phraseIndexOfFirstLogicalCommand << endl;

			if(phraseIndexOfFirstLogicalCommand == 0)
			{//eg If x+5 == 12405, X = 3+5
				indexOfLogicalConditionCommandInMathText = firstNLCsentenceInFullSentence->mathText.find(logicalConditionCommandSuperphraseContents);
				//cout << "indexOfLogicalConditionCommandInMathText = " << indexOfLogicalConditionCommandInMathText << endl;
			}
			else
			{//eg If the house is blue, X = 3+5
				string lastParsablePhraseReferenceBeforeLogicalConditionCommand = generateMathTextNLPparsablePhraseReference(firstNLCsentenceInFullSentence->sentenceIndex, lastPhraseBeforeLogicalConditionCommand);
				//cout << "lastParsablePhraseReferenceBeforeLogicalConditionCommand = " << lastParsablePhraseReferenceBeforeLogicalConditionCommand << endl;
				indexOfLogicalConditionCommandInMathText = firstNLCsentenceInFullSentence->mathText.find(lastParsablePhraseReferenceBeforeLogicalConditionCommand) + lastParsablePhraseReferenceBeforeLogicalConditionCommand.length();
				//cout << "indexOfLogicalConditionCommandInMathText = " << indexOfLogicalConditionCommandInMathText << endl;			
			}
		}
		
		if(indexOfLogicalConditionCommandInMathText != CPP_STRING_FIND_RESULT_FAIL_VALUE)
		{
			//disconnect logical condition command parsable phrases from mathText

			int indentationOfLogicalCommand = firstNLCsentenceInFullSentence->indentation + 1;
			//cout << "indentationOfLogicalCommand = " << indentationOfLogicalCommand << endl;
			NLCsentence * firstPhraseInLogicalConditionCommand = new NLCsentence();
			firstPhraseInLogicalConditionCommand->indentation = indentationOfLogicalCommand;
			firstPhraseInLogicalConditionCommand->next = firstPhraseInLogicalConditionCommandOld->next;
			firstPhraseInLogicalConditionCommand->sentenceContents = firstPhraseInLogicalConditionCommandOld->sentenceContents;
			
			if(logicalConditionCommandContainsNLPparsablePhrase)
			{
				if(phraseIndexOfFirstLogicalCommand > 0)
				{//eg If the house is blue, the dog is happy 
					lastPhraseBeforeLogicalConditionCommand->next = new NLCsentence();
					(*currentNLCsentenceInList) = lastPhraseBeforeLogicalConditionCommand->next;
					*sentenceIndex = firstNLCsentenceInFullSentence->sentenceIndex + phraseIndexOfFirstLogicalCommand;
				}
				else
				{//eg If x+5 == 12405, the dog is happy 
					firstNLCsentenceInFullSentence->next = new NLCsentence();
					(*currentNLCsentenceInList) = firstNLCsentenceInFullSentence;
					(*currentNLCsentenceInList) = (*currentNLCsentenceInList)->next;
					firstNLCsentenceInFullSentence->sentenceContents = string(NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_DUMMY);
					*sentenceIndex = firstNLCsentenceInFullSentence->sentenceIndex + 1;	//sentenceIndex is unchanged by this assignment		
				}
			}
			
			string mathTextOfLogicalConditionCommand = firstNLCsentenceInFullSentence->mathText.substr(indexOfLogicalConditionCommandInMathText, firstNLCsentenceInFullSentence->mathText.length());
			firstNLCsentenceInFullSentence->mathTextNLPparsablePhraseTotal = phraseIndexOfFirstLogicalCommand;
			firstNLCsentenceInFullSentence->mathText = firstNLCsentenceInFullSentence->mathText.substr(0, indexOfLogicalConditionCommandInMathText);	//remove parsable phrase reference from mathText	//-2 to take into account intermediary comma CHAR_COMMA and white space CHAR_SPACE



			#ifdef NLC_DEBUG_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
			cout << "detectedLogicalConditionCommand; modified mathText for firstNLCsentenceInFullSentence = " << firstNLCsentenceInFullSentence->mathText << endl;
			cout << "now generateSeparateSentencesFromMathTextAndParsablePhrasesInCommand()... " << endl;
			cout << "sentenceIndex = " << *sentenceIndex << endl;
			#endif
			
			if(logicalConditionCommandContainsNLPparsablePhrase)
			{
				if(!generateSeparateSentencesFromMathTextAndParsablePhrasesInCommand(currentNLCsentenceInList, firstPhraseInLogicalConditionCommand, mathTextOfLogicalConditionCommand, sentenceIndex, firstNLCsentenceInFullSentence->sentenceIndex, indentationOfLogicalCommand))
				{
					result = false;
				}
			}
			else
			{
				lastPhraseBeforeLogicalConditionCommand->next = firstPhraseInLogicalConditionCommand;
				firstPhraseInLogicalConditionCommand->isMath = true;
				firstPhraseInLogicalConditionCommand->mathText = mathTextOfLogicalConditionCommand;
				#ifdef NLC_PREPROCESSOR_MATH_FIX_USER_INAPPROPRIATE_USE_OF_EQUALS_SET_IN_LOGICAL_CONDITIONS
				firstPhraseInLogicalConditionCommand->mathText = replaceAllOccurancesOfString(&(firstPhraseInLogicalConditionCommand->mathText), NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_TEST_WITH_PADDING, NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_SET_WITH_PADDING);
				#endif
				//remove all commas from mathText:
				firstPhraseInLogicalConditionCommand->mathText = replaceAllOccurancesOfString(&(firstPhraseInLogicalConditionCommand->mathText), STRING_COMMA, "");
				#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
				cout << "logical condition command mathText = " << firstPhraseInLogicalConditionCommand->mathText << endl;
				#endif
				firstPhraseInLogicalConditionCommand->sentenceContents = string(NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_DUMMY);
				firstPhraseInLogicalConditionCommand->next = new NLCsentence();
				(*currentNLCsentenceInList) = firstPhraseInLogicalConditionCommand->next;
			}
		}
		else
		{
			cout << "splitMathDetectedLineIntoNLPparsablePhrases() error: indexOfLogicalConditionCommandInMathText not found in mathText " << firstNLCsentenceInFullSentence->mathText << endl;
		}

	}
	#endif

	/*

	//need to parse "is" as equals, eg "if x is 33534"; for all mathText which is not NLP parsable text, replace "is" with "=" 
	//replace all instances of "is" in all mathText which is not NLP parsable text with "="
	firstNLCsentenceInFullSentence->mathText = replaceAllOccurancesOfString(&(firstNLCsentenceInFullSentence->mathText), string(NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_IS_EQUAL_TO_INFORMAL), string(NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_TEST));	//NB this is type sensitive; could be changed in the future

	//"x is equal to number of chickens." is supported by mathText, with "number of chickens" parsable phrase
	//the following cannot be parsed by NLP/GIA; "x is the number of chickens" as dummy numerical variable replacement only works for previously defined variables.; convert to mathText and parsable phrase ("x = the number of chickens")*

	*/

	#ifndef NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION

	//how do deal with logical condition commands? eg "if the dog has a ball and [the dog] has an apple, ride the bike."? must detect comma as a new NLP parsable phrase, and any parsable phrase without a starting conjunction as a logical condition command
	if(firstNLCsentenceInFullSentence->mathText[firstNLCsentenceInFullSentence->mathText.length()-1] == NLC_PREPROCESSOR_END_OF_SENTENCE_CHAR)
	{
		if(firstNLCsentenceInFullSentence->mathTextNLPparsablePhraseTotal > 1)
		{
			NLCsentence * currentPhrase2 = firstNLCsentenceInFullSentence;
			for(int phraseIndex = 0; phraseIndex < firstNLCsentenceInFullSentence->mathTextNLPparsablePhraseTotal-1; phraseIndex++)
			{
				currentPhrase2 = currentPhrase2->next;
			}
			//currentPhrase2 is the last phrase in the firstNLCsentenceInFullSentence
			//get first word in line

			#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
			cout << "firstNLCsentenceInFullSentence->mathTextNLPparsablePhraseTotal > 1" << endl;
			#endif

			string finalParsablePhraseReference = generateMathTextNLPparsablePhraseReference(firstNLCsentenceInFullSentence->sentenceIndex, currentPhrase2);
			int finalParsablePhraseReferencePos = firstNLCsentenceInFullSentence->mathText.rfind(finalParsablePhraseReference);
			if((finalParsablePhraseReferencePos != CPP_STRING_FIND_RESULT_FAIL_VALUE) && (finalParsablePhraseReferencePos == (firstNLCsentenceInFullSentence->mathText.length() - finalParsablePhraseReference.length() - 1)))	//-1 to take into account final NLC_PREPROCESSOR_END_OF_SENTENCE_CHAR
			{//the last text in math text is a parsable phrase; it is therefore a logical condition command candidate

				#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
				cout << "finalParsablePhraseReferencePos indicates that the last text in math text is a parsable phrase" << endl;	
				#endif

				bool finalParsablePhraseIsLogicalConditionCommand = false;
				//if(firstNLCsentenceInFullSentence->mathText[finalParsablePhraseReferencePos - 2] == CHAR_COMMA)	//-2 to take into account intermediary comma CHAR_COMMA and white space CHAR_SPACE
				int index = firstNLCsentenceInFullSentence->mathText.find(NLC_PREPROCESSOR_MATH_PARSABLE_PHRASE_START_TEXT_INDICATING_LOGICAL_CONDITION_COMMAND, finalParsablePhraseReferencePos - string(NLC_PREPROCESSOR_MATH_PARSABLE_PHRASE_START_TEXT_INDICATING_LOGICAL_CONDITION_COMMAND).length());
				if((index != CPP_STRING_FIND_RESULT_FAIL_VALUE) && (index == 0))
				{
					//e.g. If the basket that is near the house is above the tray, and the basket is blue, the dog is happy.*
					finalParsablePhraseIsLogicalConditionCommand = true;
					//cout << "finalParsablePhraseIsLogicalConditionCommand" << endl;
				}
				/*OLD:
				bool finalParsablePhraseIsLogicalConditionCommand = true;
				//NB conjunctions in mathText will already have been replaced with code (so dont check entityCoordinatingConjunctionArray)
				for(int i=0; i<NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_COORDINATING_CONJUNCTION_ARRAY_NUMBER_OF_TYPES; i++)
				{
					int index = firstNLCsentenceInFullSentence->mathText.find(progLangCoordinatingConjunctions[i], finalParsablePhraseReferencePos - progLangCoordinatingConjunctions[i].length() - 1);	//-1 to take into account intermediary white space CHAR_SPACE
					if((index != CPP_STRING_FIND_RESULT_FAIL_VALUE) && (index == 0))
					{
						//"&&"/"||" is the final text in the mathText
						finalParsablePhraseIsLogicalConditionCommand = false;
					}					
				}
				for(int i=0; i<NLC_PREPROCESSOR_MATH_OPERATORS_NUMBER_OF_TYPES; i++)
				{
					int index = firstNLCsentenceInFullSentence->mathText.find(preprocessorMathOperators[i], finalParsablePhraseReferencePos - preprocessorMathOperators[i].length() - 1);	//-1 to take into account intermediary white space CHAR_SPACE
					if((index != CPP_STRING_FIND_RESULT_FAIL_VALUE) && (index == 0))
					{
						//">"/"<"/"="/"+" is the final text in the mathText
						finalParsablePhraseIsLogicalConditionCommand = false;
					}					
				}
				*/							

				if(finalParsablePhraseIsLogicalConditionCommand)
				{
					#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
					cout << "finalParsablePhraseIsLogicalConditionCommand:" << currentPhrase2->sentenceContents << endl;
					#endif
					//disconnect logical condition command parsable phrase from mathText
					firstNLCsentenceInFullSentence->mathTextNLPparsablePhraseTotal = firstNLCsentenceInFullSentence->mathTextNLPparsablePhraseTotal - 1;
					firstNLCsentenceInFullSentence->mathText = firstNLCsentenceInFullSentence->mathText.substr(0, firstNLCsentenceInFullSentence->mathText.length()-finalParsablePhraseReference.length()-2);	//remove parsable phrase reference from mathText	//-2 to take into account intermediary comma CHAR_COMMA and white space CHAR_SPACE
					#ifdef NLC_PREPROCESSOR_MATH_FIX_USER_INAPPROPRIATE_USE_OF_EQUALS_SET_IN_LOGICAL_CONDITIONS
					firstNLCsentenceInFullSentence->mathText = replaceAllOccurancesOfString(&(firstNLCsentenceInFullSentence->mathText), NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_TEST_WITH_PADDING, NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_SET_WITH_PADDING);
					#endif					
					//OLD: firstNLCsentenceInFullSentence->mathText = firstNLCsentenceInFullSentence->mathText.substr(0, generateMathTextNLPparsablePhraseReference(firstNLCsentenceInFullSentence->sentenceIndex, currentPhrase2).length());	//remove parsable phrase reference from mathText
					#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
					cout << "finalParsablePhraseIsLogicalConditionCommand; modified mathText = " << firstNLCsentenceInFullSentence->mathText << endl;
					#endif
					currentPhrase2->indentation = currentIndentation + 1;
					currentPhrase2->mathTextNLPparsablePhraseIndex = INT_DEFAULT_VALUE;		
				}
			}
		}
	}
	#endif
	return result;
}



bool splitMathDetectedLineIntoNLPparsablePhrasesLogicalConditionAddExplicitSubjectTextForConjunctions(NLCsentence * firstNLCsentenceInFullSentence, NLCsentence ** currentNLCsentenceInList, int * sentenceIndex, bool additionalClosingBracketRequired)
{	
	bool result = true;

	int currentIndentation = firstNLCsentenceInFullSentence->indentation;

	//for logical condition NLP parsable phrases, look for first instance of keywords has/is, and take the preceeding text as the context
	//this enables elimination for need for referencing in conjunctions, eg "if{(}the dog has a ball and [the dog] has an apple{)}"
	//FINISH THIS...
	NLCsentence * currentPhrasePrimarySubject = firstNLCsentenceInFullSentence;
	#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
	cout << "firstNLCsentenceInFullSentence->mathTextNLPparsablePhraseTotal = " << firstNLCsentenceInFullSentence->mathTextNLPparsablePhraseTotal << endl;
	#endif
	for(int phraseIndex=0; phraseIndex<firstNLCsentenceInFullSentence->mathTextNLPparsablePhraseTotal; phraseIndex++)
	{
		#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
		cout << "currentPhrasePrimarySubject->sentenceContents = " << currentPhrasePrimarySubject->sentenceContents << endl; 
		#endif
		bool phraseContainsPrimarySubject = true; 
		for(int i=0; i<NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_AUXILLARY_KEYWORDS_TAGGING_SUBJECT_OR_REFERENCE_NUMBER_OF_TYPES; i++)
		{
			int indexOfAuxillaryTemp = currentPhrasePrimarySubject->sentenceContents.find(preprocessorMathAuxillaryKeywordsTaggingSubjectOrReference[i], 0);
			if((indexOfAuxillaryTemp != CPP_STRING_FIND_RESULT_FAIL_VALUE) && (indexOfAuxillaryTemp == 0))
			{
				#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
				//cout << "phrase: " << currentPhrasePrimarySubject->sentenceContents << ": first word in phrase is an auxillary; it does not contain a subject (does not contain a primary subject)" << endl;
				#endif
				phraseContainsPrimarySubject = false;
			}
		}
		for(int i=0; i<NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_COORDINATING_CONJUNCTION_ARRAY_NUMBER_OF_TYPES; i++)
		{
			string parsablePhraseReference = generateMathTextNLPparsablePhraseReference(firstNLCsentenceInFullSentence->sentenceIndex, currentPhrasePrimarySubject);
			int indexOfParsablePhraseReferenceInMathText = firstNLCsentenceInFullSentence->mathText.find(parsablePhraseReference);
			if(indexOfParsablePhraseReferenceInMathText != CPP_STRING_FIND_RESULT_FAIL_VALUE)
			{
				int expectedPosOfConjunctionIfExistent = indexOfParsablePhraseReferenceInMathText - progLangCoordinatingConjunctions[i].length();
				int indexOfConjunction = firstNLCsentenceInFullSentence->mathText.find(progLangCoordinatingConjunctions[i], expectedPosOfConjunctionIfExistent);	
				if((indexOfConjunction != CPP_STRING_FIND_RESULT_FAIL_VALUE) && (indexOfConjunction == expectedPosOfConjunctionIfExistent))
				{
					#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
					//cout << "phrase: " << currentPhrasePrimarySubject->sentenceContents << ": is preceeded by a conjunction (and/or); it may not contain a subject (and certainly does not contain a primary subject)" << endl;
					#endif
					phraseContainsPrimarySubject = false;
				}
			}
			else
			{
				cout << "splitMathDetectedLineIntoNLPparsablePhrases() error: parsablePhraseReference " << parsablePhraseReference << " not found in mathText " << firstNLCsentenceInFullSentence->mathText << endl;
			}
		}

		if(phraseContainsPrimarySubject)
		{	
			#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
			cout << "\nphraseContainsPrimarySubject: " << currentPhrasePrimarySubject->sentenceContents << endl;
			#endif

			int indexOfPrimaryAuxillaryTaggingSubject = CPP_STRING_FIND_RESULT_FAIL_VALUE;
			int primaryAuxillaryType;

			bool stillFindingPrimaryAuxillary = true;
			int startPosToSearchForAuxillary = 0;
			while(stillFindingPrimaryAuxillary)
			{
				int indexOfNextClosestAuxillary = NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_MAX_CHARACTERS;
				bool foundAnAuxillaryButItWasIgnored = false;
				int indexOfClosestIgnoredAuxillary = NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_MAX_CHARACTERS;
				for(int i=0; i<NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_AUXILLARY_KEYWORDS_TAGGING_SUBJECT_OR_REFERENCE_NUMBER_OF_TYPES; i++)
				{
					int indexOfAuxillaryTemp = currentPhrasePrimarySubject->sentenceContents.find(preprocessorMathAuxillaryKeywordsTaggingSubjectOrReference[i], startPosToSearchForAuxillary);	
					if((indexOfAuxillaryTemp != CPP_STRING_FIND_RESULT_FAIL_VALUE) && (indexOfAuxillaryTemp < indexOfNextClosestAuxillary))
					{
						//ignore auxillary if has a preceeding 'that'/'which'; eg "the dog that is[ignore] near the house has[take] a ball or has[reference] an apple"
						//"If the basket that is near the house is above the tray, and the basket is blue, the dog is happy."
						//"If the basket that is near the house is above the tray and is blue, the dog is happy.
						bool ignoreAuxillary = false;
						for(int i2=0; i2<NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_RCMOD_SAME_REFERENCE_SET_DELIMITER_NUMBER_OF_TYPES; i2++)
						{
							int expectedPosOfRcmodSameReferenceSetDelimiterIfExistent = indexOfAuxillaryTemp - preprocessorMathRcmodSameReferenceSetDelimiter[i2].length() - 1;
							int indexOfRcmodSameReferenceSet = currentPhrasePrimarySubject->sentenceContents.find(preprocessorMathRcmodSameReferenceSetDelimiter[i2], expectedPosOfRcmodSameReferenceSetDelimiterIfExistent);	
							if((indexOfRcmodSameReferenceSet != CPP_STRING_FIND_RESULT_FAIL_VALUE) && (indexOfRcmodSameReferenceSet == expectedPosOfRcmodSameReferenceSetDelimiterIfExistent))
							{
								ignoreAuxillary = true;
								foundAnAuxillaryButItWasIgnored = true;
								if(indexOfAuxillaryTemp < indexOfClosestIgnoredAuxillary)
								{
									indexOfClosestIgnoredAuxillary = indexOfAuxillaryTemp;
								}
								#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
								//cout << "ignoreAuxillary" << endl;
								#endif
							}
						}

						if(!ignoreAuxillary)
						{
							indexOfNextClosestAuxillary = indexOfAuxillaryTemp;
							primaryAuxillaryType = i;
							#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
							//cout << "found nextClosestAuxillary: " << preprocessorMathAuxillaryKeywordsTaggingSubjectOrReference[i] << ", indexOfNextClosestAuxillary = " << indexOfNextClosestAuxillary << endl;
							#endif
						}
					}
				}
				if(indexOfNextClosestAuxillary != NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_MAX_CHARACTERS)
				{
					indexOfPrimaryAuxillaryTaggingSubject = indexOfNextClosestAuxillary;
					stillFindingPrimaryAuxillary = false;
				}
				else if(foundAnAuxillaryButItWasIgnored)
				{
					startPosToSearchForAuxillary = indexOfClosestIgnoredAuxillary + 1;
					#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
					//cout << "startPosToSearchForAuxillary = indexOfClosestIgnoredAuxillary: " << indexOfClosestIgnoredAuxillary << endl;
					#endif
				}
				else
				{
					stillFindingPrimaryAuxillary = false;
				}
			}

			if(indexOfPrimaryAuxillaryTaggingSubject != CPP_STRING_FIND_RESULT_FAIL_VALUE)
			{
				string subjectText = currentPhrasePrimarySubject->sentenceContents.substr(0, indexOfPrimaryAuxillaryTaggingSubject);	//check -1 is not required
				#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
				cout << "primary auxillary found for phrase: " << currentPhrasePrimarySubject->sentenceContents << ", i = " << indexOfPrimaryAuxillaryTaggingSubject << endl;
				cout << "subjectText = " << subjectText << endl;
				#endif

				NLCsentence * currentPhraseReferenceToPrimarySubject = currentPhrasePrimarySubject->next;
				for(int phraseIndex2=phraseIndex+1; phraseIndex2<firstNLCsentenceInFullSentence->mathTextNLPparsablePhraseTotal; phraseIndex2++)					
				{
					//now for each secondary auxillary referencing the subject, artificially generate (copy) the subject text
					#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
					cout << "currentPhraseReferenceToPrimarySubject = " << currentPhraseReferenceToPrimarySubject->sentenceContents << endl;
					cout << "preprocessorMathAuxillaryKeywordsTaggingSubjectOrReference[primaryAuxillaryType] = " << preprocessorMathAuxillaryKeywordsTaggingSubjectOrReference[primaryAuxillaryType] << endl;
					#endif
					
					#ifdef NLC_PREPROCESSOR_MATH_SEARCH_FOR_CONJUNCTION_SUBJECT_MATCH_NON_IDENTICAL_AUXILLARIES
					int indexOfSecondaryAuxillaryReferencingSubject = CPP_STRING_FIND_RESULT_FAIL_VALUE;
					for(int i=0; i<NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_AUXILLARY_KEYWORDS_TAGGING_SUBJECT_OR_REFERENCE_NUMBER_OF_TYPES; i++)
					{
						int indexOfAuxillaryTemp = currentPhraseReferenceToPrimarySubject->sentenceContents.find(preprocessorMathAuxillaryKeywordsTaggingSubjectOrReference[i]);
						if((indexOfAuxillaryTemp != CPP_STRING_FIND_RESULT_FAIL_VALUE) && (indexOfAuxillaryTemp  == 0))
						{
							indexOfSecondaryAuxillaryReferencingSubject = indexOfAuxillaryTemp;
						}
					}
					#else
					int indexOfSecondaryAuxillaryReferencingSubject = currentPhraseReferenceToPrimarySubject->sentenceContents.find(preprocessorMathAuxillaryKeywordsTaggingSubjectOrReference[primaryAuxillaryType]);	
					#endif
					if((indexOfSecondaryAuxillaryReferencingSubject != CPP_STRING_FIND_RESULT_FAIL_VALUE) && (indexOfSecondaryAuxillaryReferencingSubject == 0))
					{
					
						//cout << "phrase: " << currentPhraseReferenceToPrimarySubject->sentenceContents << ": found secondary auxillary" << endl;
						bool secondaryChecks = false;
						for(int i=0; i<NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_COORDINATING_CONJUNCTION_ARRAY_NUMBER_OF_TYPES; i++)
						{
							string parsablePhraseReference = generateMathTextNLPparsablePhraseReference(firstNLCsentenceInFullSentence->sentenceIndex, currentPhraseReferenceToPrimarySubject);
							int indexOfParsablePhraseReferenceInMathText = firstNLCsentenceInFullSentence->mathText.find(parsablePhraseReference);
							if(indexOfParsablePhraseReferenceInMathText != CPP_STRING_FIND_RESULT_FAIL_VALUE)
							{
								int expectedPosOfConjunctionIfExistent = indexOfParsablePhraseReferenceInMathText - progLangCoordinatingConjunctions[i].length();
								int indexOfConjunction = firstNLCsentenceInFullSentence->mathText.find(progLangCoordinatingConjunctions[i], expectedPosOfConjunctionIfExistent);	
								if((indexOfConjunction != CPP_STRING_FIND_RESULT_FAIL_VALUE) && (indexOfConjunction == expectedPosOfConjunctionIfExistent))
								{
									#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
									cout << "phrase: " << currentPhraseReferenceToPrimarySubject->sentenceContents << ": phrase is preceeded by a conjunction (and/or); it is a reference to a primary subject" << endl;
									#endif
									secondaryChecks = true;
								}
							}
							else
							{
								cout << "splitMathDetectedLineIntoNLPparsablePhrases() error: parsablePhraseReference " << parsablePhraseReference << " not found in mathText " << firstNLCsentenceInFullSentence->mathText << endl;
							}
						}

						if(secondaryChecks)
						{
							//insert subject content
							#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
							cout << "insert subject content" << endl;
							cout << "old currentPhraseReferenceToPrimarySubject->sentenceContents = " << currentPhraseReferenceToPrimarySubject->sentenceContents << endl;
							#endif
							string parsablePhraseReferenceOld = generateMathTextNLPparsablePhraseReference(firstNLCsentenceInFullSentence->sentenceIndex, currentPhraseReferenceToPrimarySubject);

							currentPhraseReferenceToPrimarySubject->sentenceContents.insert(indexOfSecondaryAuxillaryReferencingSubject, subjectText);

							string parsablePhraseReferenceNew = generateMathTextNLPparsablePhraseReference(firstNLCsentenceInFullSentence->sentenceIndex, currentPhraseReferenceToPrimarySubject);
							int parsablePhraseReferenceOldPos = firstNLCsentenceInFullSentence->mathText.find(parsablePhraseReferenceOld);
							if(parsablePhraseReferenceOldPos != CPP_STRING_FIND_RESULT_FAIL_VALUE)
							{
								firstNLCsentenceInFullSentence->mathText.replace(parsablePhraseReferenceOldPos, parsablePhraseReferenceOld.length(), parsablePhraseReferenceNew);
							}
							else
							{
								cout << "splitMathDetectedLineIntoNLPparsablePhrases() error: parsablePhraseReferenceOld " << parsablePhraseReferenceOld << " not found in mathText " << firstNLCsentenceInFullSentence->mathText << endl;
							}

							#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
							cout << "new currentPhraseReferenceToPrimarySubject->sentenceContents = " << currentPhraseReferenceToPrimarySubject->sentenceContents << endl;
							#endif
						}
					}
					currentPhraseReferenceToPrimarySubject = currentPhraseReferenceToPrimarySubject->next;
				}
			}
		}

		currentPhrasePrimarySubject = currentPhrasePrimarySubject->next;					
	}
	
	return result;

}

#ifdef NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
bool generateLogicalConditionImplicitConjunctionsAndIdentifyCommand(string * lineContents, bool * detectedLogicalConditionCommand, bool * foundImplicitConjunctions, string * logicalConditionCommandSuperphraseContents)
{
	bool result = true;
	
	*foundImplicitConjunctions = false;
	*detectedLogicalConditionCommand = false;
	
	#ifdef NLC_DEBUG_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
	cout << "generateLogicalConditionImplicitConjunctionsAndIdentifyCommand: lineContents = " << *lineContents << endl;
	#endif
	
	NLCsuperphrase * firstNLCsuperphraseInList = new NLCsuperphrase();
	NLCsuperphrase * currentNLCsuperphraseInList = firstNLCsuperphraseInList;
	
	int startPosToSearchForComma = 0;
	int commaIndex = 0;
	bool stillCommasToFind = true;
	while(stillCommasToFind)
	{
		int indexOfNextComma = lineContents->find(CHAR_COMMA, startPosToSearchForComma);	
		if(indexOfNextComma == CPP_STRING_FIND_RESULT_FAIL_VALUE)
		{
			stillCommasToFind = false;
			indexOfNextComma = lineContents->length();
		}
		
		bool conjunctionFoundInSuperphrase = false;
		int conjunctionTypeOfConjunction = INT_DEFAULT_VALUE;
		for(int i=0; i<NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_COORDINATING_CONJUNCTION_WITHOUT_PAUSE_ARRAY_NUMBER_OF_TYPES; i++)
		{
			int expectedPosOfConjunctionIfExistent = startPosToSearchForComma;
			//cout << "expectedPosOfConjunctionIfExistent = " << expectedPosOfConjunctionIfExistent << endl;
			int indexOfConjunctionTemp = lineContents->find(preprocessorMathOperatorsEquivalentConjunctionsWithoutPause[i], expectedPosOfConjunctionIfExistent);
			//cout << "indexOfConjunctionTemp = " << indexOfConjunctionTemp << endl;	
			if((indexOfConjunctionTemp != CPP_STRING_FIND_RESULT_FAIL_VALUE) && (indexOfConjunctionTemp == expectedPosOfConjunctionIfExistent))
			{
				conjunctionFoundInSuperphrase = true;
				conjunctionTypeOfConjunction = i;				
			}
		}

		string superphraseContents = lineContents->substr(startPosToSearchForComma, indexOfNextComma-startPosToSearchForComma);
		
		currentNLCsuperphraseInList->lineIndexOfFirstCharacterInPhrase = startPosToSearchForComma;
		currentNLCsuperphraseInList->hasConjunction = conjunctionFoundInSuperphrase;
		if(conjunctionFoundInSuperphrase)
		{	
			currentNLCsuperphraseInList->phraseContents = superphraseContents.substr(0, superphraseContents.length()-preprocessorMathOperatorsEquivalentConjunctionsWithoutPause[conjunctionTypeOfConjunction].length());	//super phrase contents must have conjunction removed to enable replaceLogicalConditionNaturalLanguageMathWithSymbols to be on logicalConditionCommandSuperphraseContents in parallel with lineContents, enabling logicalConditionCommandSuperphraseContents to be found within the lineContents of splitMathDetectedLineIntoNLPparsablePhrases() and an nlp parsable phrase phrase index to be assigned to the command
			currentNLCsuperphraseInList->conjunctionType = conjunctionTypeOfConjunction;
		}
		else
		{
			currentNLCsuperphraseInList->phraseContents = superphraseContents;
		}
		
		#ifdef NLC_DEBUG_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
		cout << "\ngenerateLogicalConditionImplicitConjunctionsAndIdentifyCommand(): create new NLCsuperphrase" << endl;
		cout << "lineContents = " << *lineContents << endl;
		cout << "startPosToSearchForComma = " << startPosToSearchForComma << endl;
		cout << "indexOfNextComma = " << indexOfNextComma << endl;
		cout << "superphraseContents = " << superphraseContents << endl;
		cout << "currentNLCsuperphraseInList->phraseContents = " << currentNLCsuperphraseInList->phraseContents << endl;
		cout << "currentNLCsuperphraseInList->lineIndexOfFirstCharacterInPhrase = " << currentNLCsuperphraseInList->lineIndexOfFirstCharacterInPhrase << endl;
		cout << "currentNLCsuperphraseInList->hasConjunction = " << currentNLCsuperphraseInList->hasConjunction << endl;
		cout << "currentNLCsuperphraseInList->conjunctionType = " << currentNLCsuperphraseInList->conjunctionType << endl;
		#endif
		
		currentNLCsuperphraseInList->next = new NLCsuperphrase();
		currentNLCsuperphraseInList = currentNLCsuperphraseInList->next;
				
		if(stillCommasToFind)
		{
			startPosToSearchForComma = indexOfNextComma + 1;			
		}		
		
		commaIndex++;
	}
	
	int numberOfSuperPhrases = commaIndex;	
	
	/*
	FUTURE support multiple logical condition commands in one one; NLC_PREPROCESSOR_MATH_SUPPORT_MULTIPLE_LOGICAL_CONDITION_COMMANDS_ON_ONE_LINE eg "if the house is blue, write the letter and read the book"/"else write the letter and read the book."
	support logical condition mathText commands on same line NLC_PREPROCESSOR_MATH_SUPPORT_LOGICAL_CONDITION_MATHTEXT_COMMANDS_ON_SAME_LINE eg "if the house is blue, X = 3+5"
	NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION support implicit conjunctions, eg "if the house is blue, the cat is green, and the bike is tall, ride the bike"
		algorithm: to determine whether text belongs to the logical condition test or command;
			if a phrase without a preceeding conjunction occurs after a phrase with a preceeding conjunction, take this phrase as the start of the logical condition command
				all other phrases without a preceeding conjuction are artifically assigned a preceeding conjunction of type based on the conjunction preceeding the last phrase in the logical condition test of command
		NB with NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION, splitMathDetectedLineIntoNLPparsablePhrases() can be used to support multiple commands on the same line for non-logical conditions; by generating separate NLC sentences for these parsable phrases 
	*/
	
	
	//all other phrases without a preceeding conjuction are artifically assigned a preceeding conjunction of type based on the conjunction preceeding the last phrase in the logical condition test of command
	currentNLCsuperphraseInList = firstNLCsuperphraseInList;
	bool previousPhraseHadConjunction = false;
	bool firstPhrase = true;
	while(currentNLCsuperphraseInList->next != NULL)
	{
		if(firstPhrase)
		{
		
		}
		else if(!(currentNLCsuperphraseInList->hasConjunction))
		{
			NLCsuperphrase * currentNLCsuperphraseInList2 = currentNLCsuperphraseInList;
			bool foundConjunctionOfFuturePhrase = false;
			int conjunctionTypeOfFuturePhrase = INT_DEFAULT_VALUE;
			while(currentNLCsuperphraseInList2->next != NULL)
			{
				if(!foundConjunctionOfFuturePhrase)
				{
					if(currentNLCsuperphraseInList2->hasConjunction)
					{
						foundConjunctionOfFuturePhrase = true;
						conjunctionTypeOfFuturePhrase = currentNLCsuperphraseInList2->conjunctionType;
					}
				}
				currentNLCsuperphraseInList2 = currentNLCsuperphraseInList2->next;
			}
			if(foundConjunctionOfFuturePhrase)
			{
				currentNLCsuperphraseInList->hasConjunction = true;				//redundant
				currentNLCsuperphraseInList->conjunctionType = conjunctionTypeOfFuturePhrase;	//redundant
				//update the lineContents with an artifical conjunction
				#ifdef NLC_DEBUG_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
				cout << "generateLogicalConditionImplicitConjunctionsAndIdentifyCommand(): foundConjunctionOfFuturePhrase" << endl;
				cout << "update the lineContents with an artifical conjunction: currentNLCsuperphraseInList->phraseContents = " << currentNLCsuperphraseInList->phraseContents << endl;
				cout << "old lineContents = " << *lineContents << endl;
				#endif
				lineContents->insert(currentNLCsuperphraseInList->lineIndexOfFirstCharacterInPhrase, preprocessorMathOperatorsEquivalentConjunctionsWithoutEndWhiteSpace[conjunctionTypeOfFuturePhrase]);
				#ifdef NLC_DEBUG_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
				cout << "new lineContents = " << *lineContents << endl;
				#endif
			}
		}
		
		currentNLCsuperphraseInList = currentNLCsuperphraseInList->next;
		firstPhrase = false;
	}
	

		
	//if a phrase without a preceeding conjunction occurs after a phrase with a preceeding conjunction, take this phrase as the start of the logical condition command
	currentNLCsuperphraseInList = firstNLCsuperphraseInList;
	previousPhraseHadConjunction = false;
	firstPhrase = true;
	commaIndex = 0;
	while(currentNLCsuperphraseInList->next != NULL)
	{
		if(firstPhrase)	//redundant
		{
		
		}
		else if(!(currentNLCsuperphraseInList->hasConjunction))
		{
			if(previousPhraseHadConjunction || (commaIndex = numberOfSuperPhrases-1))
			{
				//found first phrase in logical condition command
				*detectedLogicalConditionCommand = true; 
				//*indexOfLogicalConditionCommand = currentNLCsuperphraseInList->lineIndexOfFirstCharacterInPhrase;
				//cout << "indexOfLogicalConditionCommand = " << *indexOfLogicalConditionCommand << endl;
				*logicalConditionCommandSuperphraseContents = currentNLCsuperphraseInList->phraseContents;
				#ifdef NLC_DEBUG_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
				cout << "generateLogicalConditionImplicitConjunctionsAndIdentifyCommand(): found first phrase in logical condition command" << endl;
				cout << "logicalConditionCommandSuperphraseContents = " << *logicalConditionCommandSuperphraseContents << endl;
				#endif
			}
		} 
		
		if(currentNLCsuperphraseInList->hasConjunction)
		{
			previousPhraseHadConjunction = true;
		}
		else
		{
			previousPhraseHadConjunction = false;
		}
		
		currentNLCsuperphraseInList = currentNLCsuperphraseInList->next;
		firstPhrase = false;
		commaIndex++;
	}

	//cout << "lineContents = " << *lineContents << endl;
	return result;
}	



bool generateSeparateSentencesFromMathTextAndParsablePhrasesInCommand(NLCsentence ** currentNLCsentenceInList, NLCsentence * firstPhraseInCommand, string mathTextInCommand, int * sentenceIndex, int sentenceIndexOfFullSentence, int currentIndentation)
{	
	int startPosToSearchForConjunction = 0;
	int conjunctionIndex = 0;
	bool stillConjunctionsToFind = true;
	while(stillConjunctionsToFind)
	{
		int indexOfNextConjunction = NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_MAX_CHARACTERS;
		int conjunctionTypeOfNextConjunction = INT_DEFAULT_VALUE;
		for(int i=0; i<NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_COORDINATING_CONJUNCTION_ARRAY_NUMBER_OF_TYPES; i++)
		{
			int indexOfConjunctionTemp = mathTextInCommand.find(progLangCoordinatingConjunctions[i], startPosToSearchForConjunction);	
			if(indexOfConjunctionTemp != CPP_STRING_FIND_RESULT_FAIL_VALUE)
			{
				//cout << "mathTextInCommand = " << mathTextInCommand << endl;
				//cout << "indexOfConjunctionTemp = " << indexOfConjunctionTemp << endl;
				
				if(indexOfConjunctionTemp < indexOfNextConjunction)
				{
					indexOfNextConjunction = indexOfConjunctionTemp;
					conjunctionTypeOfNextConjunction = i;
					if(i != NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_COORDINATING_CONJUNCTION_AND_INDEX)
					{
						cout << "generateSeparateSentencesFromMathTextAndParsablePhrasesInCommand(): error: command mathText has a conjunction that is not '&&' (and)" << endl;
						exit(0);
					}
				}
			}
		}
		if(indexOfNextConjunction == NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_MAX_CHARACTERS)
		{
			stillConjunctionsToFind = false;
			indexOfNextConjunction = mathTextInCommand.length();
		}
		
		string subCommandContents = mathTextInCommand.substr(startPosToSearchForConjunction, indexOfNextConjunction);
		#ifdef NLC_DEBUG_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
		cout << "generateSeparateSentencesFromMathTextAndParsablePhrasesInCommand(): new conjunction found (or last ~phrase in list)" << endl;
		cout << "mathTextInCommand = " << mathTextInCommand << endl;
		cout << "subCommandContents = " << subCommandContents << endl;
		#endif
		
		NLCsentence * fullSentenceInCommand = (*currentNLCsentenceInList);
		(*currentNLCsentenceInList)->mathText = mathTextInCommand;
		(*currentNLCsentenceInList)->isMath = true;
		(*currentNLCsentenceInList)->sentenceContents = "";
		
		NLCsentence * currentPhraseInCommand = firstPhraseInCommand;
		int phraseIndexInSubCommand = 0;
		while(currentPhraseInCommand->next != NULL)
		{
			#ifdef NLC_DEBUG_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
			cout << "currentPhraseInCommand->sentenceContents = " << currentPhraseInCommand->sentenceContents << endl;
			#endif
			
			string parsablePhraseReference = generateMathTextNLPparsablePhraseReference(sentenceIndexOfFullSentence, currentPhraseInCommand);
			int indexOfParsablePhraseReferenceInSubCommand = subCommandContents.find(parsablePhraseReference);
			string parsablePhraseReferenceWithAppendedFullstop = parsablePhraseReference + NLC_PREPROCESSOR_END_OF_SENTENCE_CHAR;
			if(indexOfParsablePhraseReferenceInSubCommand != CPP_STRING_FIND_RESULT_FAIL_VALUE)
			{	
				//reference to currentPhraseInCommand is in subCommandContents
				#ifdef NLC_DEBUG_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
				cout << "parsablePhraseReference = " << parsablePhraseReference << endl;
				#endif
				if((parsablePhraseReferenceWithAppendedFullstop == mathTextInCommand) && (conjunctionIndex == 0) && !stillConjunctionsToFind)	//check the "(parsablePhraseReference == mathTextInCommand)" exact test is sufficient (or if white space can be allowed either side of test)
				{
					//no mathText detected
					#ifdef NLC_DEBUG_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
					cout << "generateSeparateSentencesFromMathTextAndParsablePhrasesInCommand(): no mathText detected in subcommand: " << mathTextInCommand << endl;
					#endif
					(*currentNLCsentenceInList)->mathText = "";
					(*currentNLCsentenceInList)->isMath = false;
					(*currentNLCsentenceInList)->indentation = currentIndentation;
					(*currentNLCsentenceInList)->sentenceContents = currentPhraseInCommand->sentenceContents;
					(*currentNLCsentenceInList)->sentenceIndex = (*sentenceIndex);
					(*currentNLCsentenceInList)->mathTextNLPparsablePhraseTotal = 0;
					(*currentNLCsentenceInList)->next = new NLCsentence();
					(*currentNLCsentenceInList) = (*currentNLCsentenceInList)->next;
					(*sentenceIndex) = (*sentenceIndex) + 1;				
				}
				else
				{
					#ifdef NLC_DEBUG_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
					cout << "generateSeparateSentencesFromMathTextAndParsablePhrasesInCommand(): mathText detected in subcommand: " << mathTextInCommand << endl;
					#endif
					(*currentNLCsentenceInList)->mathTextNLPparsablePhraseIndex = phraseIndexInSubCommand;
					(*currentNLCsentenceInList)->indentation = currentIndentation;
					(*currentNLCsentenceInList)->sentenceContents = currentPhraseInCommand->sentenceContents;
					(*currentNLCsentenceInList)->sentenceIndex = (*sentenceIndex);
					fullSentenceInCommand->mathTextNLPparsablePhraseTotal = fullSentenceInCommand->mathTextNLPparsablePhraseTotal + 1;
					(*currentNLCsentenceInList)->next = new NLCsentence();
					(*currentNLCsentenceInList) = (*currentNLCsentenceInList)->next;
					(*sentenceIndex) = (*sentenceIndex) + 1;	
					
					phraseIndexInSubCommand++;
				}		
			}

			currentPhraseInCommand = currentPhraseInCommand->next;
		}

		if(stillConjunctionsToFind)		
		{	
			startPosToSearchForConjunction = indexOfNextConjunction + 1;
		}
		
				
		conjunctionIndex++;
	}			
}


#endif




#endif
#endif





