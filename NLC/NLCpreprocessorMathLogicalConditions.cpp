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
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2015 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 1q6c 20-August-2015
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
 *******************************************************************************/


#include "NLCpreprocessorMathLogicalConditions.h"
#include "SHAREDvars.h"

#ifdef NLC_PREPROCESSOR_MATH
#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE

#ifdef NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
NLCsubphrase::NLCsubphrase(void)
{
	lineIndexOfFirstCharacterInPhrase = INT_DEFAULT_VALUE;
	phraseContents = "";
	hasConjunction = false;
	conjunctionType = INT_DEFAULT_VALUE;
	next = NULL;
}
NLCsubphrase::~NLCsubphrase(void)
{
}
#endif

bool replaceLogicalConditionNaturalLanguageMathWithSymbols(string* lineContents, int logicalConditionOperator, bool* additionalClosingBracketRequired, bool parallelReplacement)
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
			cout << "detectLogicalConditionOperatorAtStartOfLine{}: logicalConditionOperatorFound" << logicalConditionOperationsArray[i] << endl; 
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
				cout << "replaceLogicalConditionNaturalLanguageMathWithSymbols{} error: invalid symbol found after logicalConditionOperator: " << logicalConditionOperationsArray[logicalConditionOperator] << characterAfterLogicalConditionOperator << endl;
			}
		}
	}
	
	#ifdef NLC_PREPROCESSOR_MATH_FIX_USER_INAPPROPRIATE_USE_OF_EQUALS_SET_IN_LOGICAL_CONDITIONS
	*lineContents = replaceAllOccurancesOfString(lineContents, NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_SET_WITH_PADDING, NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_TEST_WITH_PADDING);
	#endif
	
	return result;
}

bool replaceLogicalConditionNaturalLanguageMathWithSymbolsEnd(NLCsentence* firstNLCsentenceInFullSentence, bool additionalClosingBracketRequired)
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





bool splitMathDetectedLineIntoNLPparsablePhrasesLogicalConditionCommands(NLCsentence* firstNLCsentenceInFullSentence, NLCsentence** currentNLCsentenceInList, int* sentenceIndex, bool additionalClosingBracketRequired, bool detectedLogicalConditionCommand, int phraseIndexOfFirstLogicalCommand, string logicalConditionCommandSubphraseContents)
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
		{//eg If x+5 == 12405, X = 3+5 OR If x+5 == 12405, the dog is happy.
		
		}

		NLCsentence* firstPhraseInLogicalConditionCommandOld = firstNLCsentenceInFullSentence;
		NLCsentence* lastPhraseBeforeLogicalConditionCommand = firstNLCsentenceInFullSentence;

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
			//eg If x+5 == 12405, the dog is happy.
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
				indexOfLogicalConditionCommandInMathText = firstNLCsentenceInFullSentence->mathText.find(logicalConditionCommandSubphraseContents);
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
			NLCsentence* firstPhraseInLogicalConditionCommand = new NLCsentence();
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
				{//eg If x+5 == 12405, the dog is happy.
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
			cout << "sentenceIndex = " <<* sentenceIndex << endl;
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
				//remove all commas from mathText:
				string logicalConditionCommandCommaTextToRemove = string("") + STRING_COMMA + STRING_SPACE;	//this was STRING_COMMA before 1k6c
				mathTextOfLogicalConditionCommand = replaceAllOccurancesOfString(&mathTextOfLogicalConditionCommand, logicalConditionCommandCommaTextToRemove, "");
				lastPhraseBeforeLogicalConditionCommand->next = firstPhraseInLogicalConditionCommand;
				
				#ifdef NLC_PREPROCESSOR_INTERPRET_SINGLE_WORD_SENTENCES_AS_ACTIONS
				bool logicalConditionCommandIsValidVariableName = false; 
				string logicalConditionCommandWithoutFullStop = "";
				if(mathTextOfLogicalConditionCommand[mathTextOfLogicalConditionCommand.length()-1] == NLC_PREPROCESSOR_END_OF_SENTENCE_CHAR)	//only process logical condition commands with fullstop as potential single word actions (ie non mathtext)
				{
					logicalConditionCommandWithoutFullStop = mathTextOfLogicalConditionCommand.substr(0, mathTextOfLogicalConditionCommand.length()-1);
					logicalConditionCommandIsValidVariableName = isStringValidVariableName(logicalConditionCommandWithoutFullStop, true);
					//cout << "splitMathDetectedLineIntoNLPparsablePhrasesLogicalConditionCommands{}: logical condition command NLC_PREPROCESSOR_END_OF_SENTENCE_CHAR detected" << endl;
					//cout << "logicalConditionCommandWithoutFullStop = " << logicalConditionCommandWithoutFullStop << endl;
				}
				if(logicalConditionCommandIsValidVariableName)
				{
					#ifdef NLC_PREPROCESSOR_INTERPRET_SINGLE_WORD_SENTENCES_AS_ACTIONS_REPLACE_ACTION_ALSO_DUE_TO_NLP_LIMITATION
					string actionName = logicalConditionCommandWithoutFullStop;
					firstPhraseInLogicalConditionCommand->singleWordSentenceActionName = actionName;
					firstPhraseInLogicalConditionCommand->sentenceContents = "" + NLC_PREPROCESSOR_INTERPRET_SINGLE_WORD_SENTENCES_AS_ACTIONS_DUMMY_TEXT_ACTION_FULL + STRING_FULLSTOP;
					#else
					firstPhraseInLogicalConditionCommand->sentenceContents = "" + actionName + NLC_PREPROCESSOR_INTERPRET_SINGLE_WORD_SENTENCES_AS_ACTIONS_DUMMY_TEXT_ACTION_OBJECT_FULL + STRING_FULLSTOP;
					#endif
					//cout << "splitMathDetectedLineIntoNLPparsablePhrasesLogicalConditionCommands{}: logicalConditionCommandIsNLCparsableWord" << endl;
					//cout << "firstPhraseInLogicalConditionCommand->sentenceContents = " << firstPhraseInLogicalConditionCommand->sentenceContents << endl;
				}
				else
				{
				#endif
			
					firstPhraseInLogicalConditionCommand->isMath = true;
					firstPhraseInLogicalConditionCommand->mathText = mathTextOfLogicalConditionCommand;
					#ifdef NLC_PREPROCESSOR_MATH_FIX_USER_INAPPROPRIATE_USE_OF_EQUALS_SET_IN_LOGICAL_CONDITIONS
					firstPhraseInLogicalConditionCommand->mathText = replaceAllOccurancesOfString(&(firstPhraseInLogicalConditionCommand->mathText), NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_TEST_WITH_PADDING, NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_SET_WITH_PADDING);
					#endif

					#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
					cout << "logical condition command mathText = " << firstPhraseInLogicalConditionCommand->mathText << endl;
					#endif
					firstPhraseInLogicalConditionCommand->sentenceContents = string(NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_DUMMY);
					
					//firstPhraseInLogicalConditionCommand->mathTextNLPparsablePhraseTotal = 0;	//why has this not been set?

				#ifdef NLC_PREPROCESSOR_INTERPRET_SINGLE_WORD_SENTENCES_AS_ACTIONS
				}
				#endif
				
				firstPhraseInLogicalConditionCommand->sentenceIndex = (*sentenceIndex);	//added 1k6c - why wasn't this set before?
				
				firstPhraseInLogicalConditionCommand->next = new NLCsentence();
				(*currentNLCsentenceInList) = firstPhraseInLogicalConditionCommand->next;
			}
		}
		else
		{
			cout << "splitMathDetectedLineIntoNLPparsablePhrases{} error: indexOfLogicalConditionCommandInMathText not found in mathText " << firstNLCsentenceInFullSentence->mathText << endl;
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
			NLCsentence* currentPhrase2 = firstNLCsentenceInFullSentence;
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



bool splitMathDetectedLineIntoNLPparsablePhrasesLogicalConditionAddExplicitSubjectTextForConjunctions(NLCsentence* firstNLCsentenceInFullSentence, NLCsentence** currentNLCsentenceInList, int* sentenceIndex, bool additionalClosingBracketRequired)
{	
	bool result = true;

	int currentIndentation = firstNLCsentenceInFullSentence->indentation;

	//for logical condition NLP parsable phrases, look for first instance of keywords has/is, and take the preceeding text as the context
	//this enables elimination for need for referencing in conjunctions, eg "if{(}the dog has a ball and [the dog] has an apple{)}"
	//FINISH THIS...
	NLCsentence* currentPhrasePrimarySubject = firstNLCsentenceInFullSentence;
	#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
	cout << "firstNLCsentenceInFullSentence->mathTextNLPparsablePhraseTotal = " << firstNLCsentenceInFullSentence->mathTextNLPparsablePhraseTotal << endl;
	#endif
	for(int phraseIndex=0; phraseIndex<firstNLCsentenceInFullSentence->mathTextNLPparsablePhraseTotal; phraseIndex++)
	{
		#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
		cout << "currentPhrasePrimarySubject->sentenceContents = " << currentPhrasePrimarySubject->sentenceContents << endl; 
		#endif
		bool phraseContainsPrimarySubject = true; 
		for(int i=0; i<NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_AUXILIARY_KEYWORDS_TAGGING_SUBJECT_OR_REFERENCE_NUMBER_OF_TYPES; i++)
		{
			int indexOfAuxiliaryTemp = currentPhrasePrimarySubject->sentenceContents.find(preprocessorMathAuxiliaryKeywordsTaggingSubjectOrReference[i], 0);
			if((indexOfAuxiliaryTemp != CPP_STRING_FIND_RESULT_FAIL_VALUE) && (indexOfAuxiliaryTemp == 0))
			{
				#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
				//cout << "phrase: " << currentPhrasePrimarySubject->sentenceContents << ": first word in phrase is an auxiliary; it does not contain a subject (does not contain a primary subject)" << endl;
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
				cout << "splitMathDetectedLineIntoNLPparsablePhrases{} error: parsablePhraseReference " << parsablePhraseReference << " not found in mathText " << firstNLCsentenceInFullSentence->mathText << endl;
			}
		}

		if(phraseContainsPrimarySubject)
		{	
			#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
			cout << "\nphraseContainsPrimarySubject: " << currentPhrasePrimarySubject->sentenceContents << endl;
			#endif

			int indexOfPrimaryAuxiliaryTaggingSubject = CPP_STRING_FIND_RESULT_FAIL_VALUE;
			int primaryAuxiliaryType;

			bool stillFindingPrimaryAuxiliary = true;
			int startPosToSearchForAuxiliary = 0;
			while(stillFindingPrimaryAuxiliary)
			{
				int indexOfNextClosestAuxiliary = NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_MAX_CHARACTERS;
				bool foundAnAuxiliaryButItWasIgnored = false;
				int indexOfClosestIgnoredAuxiliary = NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_MAX_CHARACTERS;
				for(int i=0; i<NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_AUXILIARY_KEYWORDS_TAGGING_SUBJECT_OR_REFERENCE_NUMBER_OF_TYPES; i++)
				{
					int indexOfAuxiliaryTemp = currentPhrasePrimarySubject->sentenceContents.find(preprocessorMathAuxiliaryKeywordsTaggingSubjectOrReference[i], startPosToSearchForAuxiliary);	
					if((indexOfAuxiliaryTemp != CPP_STRING_FIND_RESULT_FAIL_VALUE) && (indexOfAuxiliaryTemp < indexOfNextClosestAuxiliary))
					{
						//ignore auxiliary if has a preceeding 'that'/'which'; eg "the dog that is[ignore] near the house has[take] a ball or has[reference] an apple"
						//"If the basket that is near the house is above the tray, and the basket is blue, the dog is happy."
						//"If the basket that is near the house is above the tray and is blue, the dog is happy.
						bool ignoreAuxiliary = false;
						for(int i2=0; i2<NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_RCMOD_SAME_REFERENCE_SET_DELIMITER_NUMBER_OF_TYPES; i2++)
						{
							int expectedPosOfRcmodSameReferenceSetDelimiterIfExistent = indexOfAuxiliaryTemp - preprocessorMathRcmodSameReferenceSetDelimiter[i2].length() - 1;
							int indexOfRcmodSameReferenceSet = currentPhrasePrimarySubject->sentenceContents.find(preprocessorMathRcmodSameReferenceSetDelimiter[i2], expectedPosOfRcmodSameReferenceSetDelimiterIfExistent);	
							if((indexOfRcmodSameReferenceSet != CPP_STRING_FIND_RESULT_FAIL_VALUE) && (indexOfRcmodSameReferenceSet == expectedPosOfRcmodSameReferenceSetDelimiterIfExistent))
							{
								ignoreAuxiliary = true;
								foundAnAuxiliaryButItWasIgnored = true;
								if(indexOfAuxiliaryTemp < indexOfClosestIgnoredAuxiliary)
								{
									indexOfClosestIgnoredAuxiliary = indexOfAuxiliaryTemp;
								}
								#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
								//cout << "ignoreAuxiliary" << endl;
								#endif
							}
						}

						if(!ignoreAuxiliary)
						{
							indexOfNextClosestAuxiliary = indexOfAuxiliaryTemp;
							primaryAuxiliaryType = i;
							#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
							//cout << "found nextClosestAuxiliary: " << preprocessorMathAuxiliaryKeywordsTaggingSubjectOrReference[i] << ", indexOfNextClosestAuxiliary = " << indexOfNextClosestAuxiliary << endl;
							#endif
						}
					}
				}
				if(indexOfNextClosestAuxiliary != NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_MAX_CHARACTERS)
				{
					indexOfPrimaryAuxiliaryTaggingSubject = indexOfNextClosestAuxiliary;
					stillFindingPrimaryAuxiliary = false;
				}
				else if(foundAnAuxiliaryButItWasIgnored)
				{
					startPosToSearchForAuxiliary = indexOfClosestIgnoredAuxiliary + 1;
					#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
					//cout << "startPosToSearchForAuxiliary = indexOfClosestIgnoredAuxiliary: " << indexOfClosestIgnoredAuxiliary << endl;
					#endif
				}
				else
				{
					stillFindingPrimaryAuxiliary = false;
				}
			}

			if(indexOfPrimaryAuxiliaryTaggingSubject != CPP_STRING_FIND_RESULT_FAIL_VALUE)
			{
				string subjectText = currentPhrasePrimarySubject->sentenceContents.substr(0, indexOfPrimaryAuxiliaryTaggingSubject);	//check -1 is not required
				#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
				cout << "primary auxiliary found for phrase: " << currentPhrasePrimarySubject->sentenceContents << ", i = " << indexOfPrimaryAuxiliaryTaggingSubject << endl;
				cout << "subjectText = " << subjectText << endl;
				#endif

				NLCsentence* currentPhraseReferenceToPrimarySubject = currentPhrasePrimarySubject->next;
				for(int phraseIndex2=phraseIndex+1; phraseIndex2<firstNLCsentenceInFullSentence->mathTextNLPparsablePhraseTotal; phraseIndex2++)					
				{
					//now for each secondary auxiliary referencing the subject, artificially generate (copy) the subject text
					#ifdef NLC_DEBUG_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
					cout << "currentPhraseReferenceToPrimarySubject = " << currentPhraseReferenceToPrimarySubject->sentenceContents << endl;
					cout << "preprocessorMathAuxiliaryKeywordsTaggingSubjectOrReference[primaryAuxiliaryType] = " << preprocessorMathAuxiliaryKeywordsTaggingSubjectOrReference[primaryAuxiliaryType] << endl;
					#endif
					
					#ifdef NLC_PREPROCESSOR_MATH_SEARCH_FOR_CONJUNCTION_SUBJECT_MATCH_NON_IDENTICAL_AUXILLARIES
					int indexOfSecondaryAuxiliaryReferencingSubject = CPP_STRING_FIND_RESULT_FAIL_VALUE;
					for(int i=0; i<NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_AUXILIARY_KEYWORDS_TAGGING_SUBJECT_OR_REFERENCE_NUMBER_OF_TYPES; i++)
					{
						int indexOfAuxiliaryTemp = currentPhraseReferenceToPrimarySubject->sentenceContents.find(preprocessorMathAuxiliaryKeywordsTaggingSubjectOrReference[i]);
						if((indexOfAuxiliaryTemp != CPP_STRING_FIND_RESULT_FAIL_VALUE) && (indexOfAuxiliaryTemp  == 0))
						{
							indexOfSecondaryAuxiliaryReferencingSubject = indexOfAuxiliaryTemp;
						}
					}
					#else
					int indexOfSecondaryAuxiliaryReferencingSubject = currentPhraseReferenceToPrimarySubject->sentenceContents.find(preprocessorMathAuxiliaryKeywordsTaggingSubjectOrReference[primaryAuxiliaryType]);	
					#endif
					if((indexOfSecondaryAuxiliaryReferencingSubject != CPP_STRING_FIND_RESULT_FAIL_VALUE) && (indexOfSecondaryAuxiliaryReferencingSubject == 0))
					{
					
						//cout << "phrase: " << currentPhraseReferenceToPrimarySubject->sentenceContents << ": found secondary auxiliary" << endl;
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
								cout << "splitMathDetectedLineIntoNLPparsablePhrases{} error: parsablePhraseReference " << parsablePhraseReference << " not found in mathText " << firstNLCsentenceInFullSentence->mathText << endl;
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

							currentPhraseReferenceToPrimarySubject->sentenceContents.insert(indexOfSecondaryAuxiliaryReferencingSubject, subjectText);

							string parsablePhraseReferenceNew = generateMathTextNLPparsablePhraseReference(firstNLCsentenceInFullSentence->sentenceIndex, currentPhraseReferenceToPrimarySubject);
							int parsablePhraseReferenceOldPos = firstNLCsentenceInFullSentence->mathText.find(parsablePhraseReferenceOld);
							if(parsablePhraseReferenceOldPos != CPP_STRING_FIND_RESULT_FAIL_VALUE)
							{
								firstNLCsentenceInFullSentence->mathText.replace(parsablePhraseReferenceOldPos, parsablePhraseReferenceOld.length(), parsablePhraseReferenceNew);
							}
							else
							{
								cout << "splitMathDetectedLineIntoNLPparsablePhrases{} error: parsablePhraseReferenceOld " << parsablePhraseReferenceOld << " not found in mathText " << firstNLCsentenceInFullSentence->mathText << endl;
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
bool generateLogicalConditionImplicitConjunctionsAndIdentifyCommand(string* lineContents, bool* detectedLogicalConditionCommand, bool* foundImplicitConjunctions, string* logicalConditionCommandSubphraseContents)
{
	bool result = true;
	
	*foundImplicitConjunctions = false;
	*detectedLogicalConditionCommand = false;
	
	#ifdef NLC_DEBUG_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
	cout << "generateLogicalConditionImplicitConjunctionsAndIdentifyCommand: lineContents = " <<* lineContents << endl;
	#endif
	
	NLCsubphrase* firstNLCsubphraseInList = new NLCsubphrase();
	NLCsubphrase* currentNLCsubphraseInList = firstNLCsubphraseInList;
	
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
		
		bool conjunctionFoundInSubphrase = false;
		int conjunctionTypeOfConjunction = INT_DEFAULT_VALUE;
		for(int i=0; i<NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_COORDINATING_CONJUNCTION_WITHOUT_PAUSE_ARRAY_NUMBER_OF_TYPES; i++)
		{
			int expectedPosOfConjunctionIfExistent = startPosToSearchForComma;
			//cout << "expectedPosOfConjunctionIfExistent = " << expectedPosOfConjunctionIfExistent << endl;
			int indexOfConjunctionTemp = lineContents->find(preprocessorMathOperatorsEquivalentConjunctionsWithoutPause[i], expectedPosOfConjunctionIfExistent);
			//cout << "indexOfConjunctionTemp = " << indexOfConjunctionTemp << endl;	
			if((indexOfConjunctionTemp != CPP_STRING_FIND_RESULT_FAIL_VALUE) && (indexOfConjunctionTemp == expectedPosOfConjunctionIfExistent))
			{
				conjunctionFoundInSubphrase = true;
				conjunctionTypeOfConjunction = i;				
			}
		}

		string subphraseContents = lineContents->substr(startPosToSearchForComma, indexOfNextComma-startPosToSearchForComma);
		
		currentNLCsubphraseInList->lineIndexOfFirstCharacterInPhrase = startPosToSearchForComma;
		currentNLCsubphraseInList->hasConjunction = conjunctionFoundInSubphrase;
		if(conjunctionFoundInSubphrase)
		{	
			currentNLCsubphraseInList->phraseContents = subphraseContents.substr(0, subphraseContents.length()-preprocessorMathOperatorsEquivalentConjunctionsWithoutPause[conjunctionTypeOfConjunction].length());	//sub phrase contents must have conjunction removed to enable replaceLogicalConditionNaturalLanguageMathWithSymbols to be on logicalConditionCommandSubphraseContents in parallel with lineContents, enabling logicalConditionCommandSubphraseContents to be found within the lineContents of splitMathDetectedLineIntoNLPparsablePhrases() and an nlp parsable phrase phrase index to be assigned to the command
			currentNLCsubphraseInList->conjunctionType = conjunctionTypeOfConjunction;
		}
		else
		{
			currentNLCsubphraseInList->phraseContents = subphraseContents;
		}
		
		#ifdef NLC_DEBUG_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
		cout << "\ngenerateLogicalConditionImplicitConjunctionsAndIdentifyCommand{}: create new NLCsubphrase" << endl;
		cout << "lineContents = " <<* lineContents << endl;
		cout << "startPosToSearchForComma = " << startPosToSearchForComma << endl;
		cout << "indexOfNextComma = " << indexOfNextComma << endl;
		cout << "subphraseContents = " << subphraseContents << endl;
		cout << "currentNLCsubphraseInList->phraseContents = " << currentNLCsubphraseInList->phraseContents << endl;
		cout << "currentNLCsubphraseInList->lineIndexOfFirstCharacterInPhrase = " << currentNLCsubphraseInList->lineIndexOfFirstCharacterInPhrase << endl;
		cout << "currentNLCsubphraseInList->hasConjunction = " << currentNLCsubphraseInList->hasConjunction << endl;
		cout << "currentNLCsubphraseInList->conjunctionType = " << currentNLCsubphraseInList->conjunctionType << endl;
		#endif
		
		currentNLCsubphraseInList->next = new NLCsubphrase();
		currentNLCsubphraseInList = currentNLCsubphraseInList->next;
				
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
	currentNLCsubphraseInList = firstNLCsubphraseInList;
	bool previousPhraseHadConjunction = false;
	bool firstPhrase = true;
	while(currentNLCsubphraseInList->next != NULL)
	{
		if(firstPhrase)
		{
		
		}
		else if(!(currentNLCsubphraseInList->hasConjunction))
		{
			NLCsubphrase* currentNLCsubphraseInList2 = currentNLCsubphraseInList;
			bool foundConjunctionOfFuturePhrase = false;
			int conjunctionTypeOfFuturePhrase = INT_DEFAULT_VALUE;
			while(currentNLCsubphraseInList2->next != NULL)
			{
				if(!foundConjunctionOfFuturePhrase)
				{
					if(currentNLCsubphraseInList2->hasConjunction)
					{
						foundConjunctionOfFuturePhrase = true;
						conjunctionTypeOfFuturePhrase = currentNLCsubphraseInList2->conjunctionType;
					}
				}
				currentNLCsubphraseInList2 = currentNLCsubphraseInList2->next;
			}
			if(foundConjunctionOfFuturePhrase)
			{
				currentNLCsubphraseInList->hasConjunction = true;				//redundant
				currentNLCsubphraseInList->conjunctionType = conjunctionTypeOfFuturePhrase;	//redundant
				//update the lineContents with an artifical conjunction
				#ifdef NLC_DEBUG_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
				cout << "generateLogicalConditionImplicitConjunctionsAndIdentifyCommand{}: foundConjunctionOfFuturePhrase" << endl;
				cout << "update the lineContents with an artifical conjunction: currentNLCsubphraseInList->phraseContents = " << currentNLCsubphraseInList->phraseContents << endl;
				cout << "old lineContents = " <<* lineContents << endl;
				#endif
				lineContents->insert(currentNLCsubphraseInList->lineIndexOfFirstCharacterInPhrase, preprocessorMathOperatorsEquivalentConjunctionsWithoutEndWhiteSpace[conjunctionTypeOfFuturePhrase]);
				#ifdef NLC_DEBUG_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
				cout << "new lineContents = " <<* lineContents << endl;
				#endif
			}
		}
		
		currentNLCsubphraseInList = currentNLCsubphraseInList->next;
		firstPhrase = false;
	}
	

		
	//if a phrase without a preceeding conjunction occurs after a phrase with a preceeding conjunction, take this phrase as the start of the logical condition command
	currentNLCsubphraseInList = firstNLCsubphraseInList;
	previousPhraseHadConjunction = false;
	firstPhrase = true;
	commaIndex = 0;
	while(currentNLCsubphraseInList->next != NULL)
	{
		if(firstPhrase)	//redundant
		{
		
		}
		else if(!(currentNLCsubphraseInList->hasConjunction))
		{
			if(previousPhraseHadConjunction || (commaIndex = numberOfSuperPhrases-1))
			{
				//found first phrase in logical condition command
				*detectedLogicalConditionCommand = true; 
				//*indexOfLogicalConditionCommand = currentNLCsubphraseInList->lineIndexOfFirstCharacterInPhrase;
				//cout << "indexOfLogicalConditionCommand = " <<* indexOfLogicalConditionCommand << endl;
				*logicalConditionCommandSubphraseContents = currentNLCsubphraseInList->phraseContents;
				#ifdef NLC_DEBUG_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
				cout << "generateLogicalConditionImplicitConjunctionsAndIdentifyCommand{}: found first phrase in logical condition command" << endl;
				cout << "logicalConditionCommandSubphraseContents = " <<* logicalConditionCommandSubphraseContents << endl;
				#endif
			}
		} 
		
		if(currentNLCsubphraseInList->hasConjunction)
		{
			previousPhraseHadConjunction = true;
		}
		else
		{
			previousPhraseHadConjunction = false;
		}
		
		currentNLCsubphraseInList = currentNLCsubphraseInList->next;
		firstPhrase = false;
		commaIndex++;
	}

	//cout << "lineContents = " <<* lineContents << endl;
	return result;
}	



bool generateSeparateSentencesFromMathTextAndParsablePhrasesInCommand(NLCsentence** currentNLCsentenceInList, NLCsentence* firstPhraseInCommand, string mathTextInCommand, int* sentenceIndex, int sentenceIndexOfFullSentence, int currentIndentation)
{	
	bool result = true;
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
						cout << "generateSeparateSentencesFromMathTextAndParsablePhrasesInCommand{}: error: command mathText has a conjunction that is not '&&' (and)" << endl;
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
		cout << "generateSeparateSentencesFromMathTextAndParsablePhrasesInCommand{}: new conjunction found (or last ~phrase in list)" << endl;
		cout << "mathTextInCommand = " << mathTextInCommand << endl;
		cout << "subCommandContents = " << subCommandContents << endl;
		#endif
		
		NLCsentence* fullSentenceInCommand = (*currentNLCsentenceInList);
		(*currentNLCsentenceInList)->mathText = mathTextInCommand;
		(*currentNLCsentenceInList)->isMath = true;
		(*currentNLCsentenceInList)->sentenceContents = "";
		
		NLCsentence* currentPhraseInCommand = firstPhraseInCommand;
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
					cout << "generateSeparateSentencesFromMathTextAndParsablePhrasesInCommand{}: no mathText detected in subcommand: " << mathTextInCommand << endl;
					#endif
					
					/*//this implementation is not currently possible because NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_MIN_NUMBER_WORDS == 2
					#ifdef NLC_PREPROCESSOR_INTERPRET_SINGLE_WORD_SENTENCES_AS_ACTIONS
					string sentenceContents = currentPhraseInCommand->sentenceContents;
					if(isStringValidVariableName(sentenceContents))
					{
						#ifdef NLC_PREPROCESSOR_INTERPRET_SINGLE_WORD_SENTENCES_AS_ACTIONS_REPLACE_ACTION_ALSO_DUE_TO_NLP_LIMITATION
						string actionName = sentenceContents.substr(0, sentenceContents.length()-1);
						(*currentNLCsentenceInList)->singleWordSentenceActionName = actionName;
						sentenceContents = "" + NLC_PREPROCESSOR_INTERPRET_SINGLE_WORD_SENTENCES_AS_ACTIONS_DUMMY_TEXT_ACTION_OBJECT_FULL + STRING_FULLSTOP;
						#else
						sentenceContents = sentenceContents.insert((sentenceContents.length()-1), NLC_PREPROCESSOR_INTERPRET_SINGLE_WORD_SENTENCES_AS_ACTIONS_DUMMY_TEXT_ACTION_OBJECT_FULL);
						#endif
						cout << "sentenceContents = " << sentenceContents << endl;
					}
					currentPhraseInCommand->sentenceContents = sentenceContents;
					#endif
					*/
					
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
					cout << "generateSeparateSentencesFromMathTextAndParsablePhrasesInCommand{}: mathText detected in subcommand: " << mathTextInCommand << endl;
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
	return result;			
}


#endif




#endif
#endif





