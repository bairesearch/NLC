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
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2017 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler (Programming Interface)
 * Project Version: 1w3a 14-January-2017
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

bool replaceLogicalConditionNaturalLanguageMathWithSymbols(string* lineContents, int logicalConditionOperator, bool* additionalClosingBracketRequired, const bool parallelReplacement)
{
	bool result = true;

	#ifdef NLC_MATH_OBJECTS_ADVANCED
	//ignore string quotations during replacement
	bool stillFindingLineContentsSub = true;
	int lineContentsSubIndex = 0;
	int lineContentsSubIndexEnd = 0;
	string lineContentsNew = "";
	while(stillFindingLineContentsSub) 
	{
		int indexOfStringDelimiter = lineContents->find(NLC_MATH_OBJECTS_STRING_DELIMITER_CHAR, lineContentsSubIndex);
		if(indexOfStringDelimiter != CPP_STRING_FIND_RESULT_FAIL_VALUE)
		{
			lineContentsSubIndexEnd = indexOfStringDelimiter+1;
		}
		else
		{
			lineContentsSubIndexEnd = lineContents->length();
			stillFindingLineContentsSub = false;
		}
		string lineContentsSub = lineContents->substr(lineContentsSubIndex, lineContentsSubIndexEnd-lineContentsSubIndex);
	#else
	string lineContentsSub = *lineContents;
	#endif
		
		for(int i=0; i<NLC_PREPROCESSOR_MATH_OPERATORS_NUMBER_OF_TYPES; i++)
		{
			bool foundAtLeastOneInstance = false;
			lineContentsSub = replaceAllOccurancesOfString(&lineContentsSub, preprocessorMathOperatorsEquivalentNumberOfTypes[i], preprocessorMathOperatorsForLogicalConditions[i], &foundAtLeastOneInstance);	//NB this is type sensitive; could be changed in the future
			/*
			if(foundAtLeastOneInstance)
			{
				cout << "replaceLogicalConditionNaturalLanguageMathWithSymbols{} foundAtLeastOneInstance" << endl;
			}
			*/
		}

		/*
		for(int i=0; i<NLC_LOGICAL_CONDITION_OPERATIONS_NUMBER_OF_TYPES; i++)
		{
			int index = lineContentsSub.find(logicalConditionOperationsArray[i]);
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
				int index = lineContentsSub.find(preprocessorMathOperatorsEquivalentConjunctionsWithPause[i]);	//NB this is type sensitive; could be changed in the future
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
				lineContentsSub = replaceAllOccurancesOfString(&lineContentsSub, preprocessorMathOperatorsEquivalentConjunctions[i], progLangCoordinatingConjunctions[i]);	//NB this is type sensitive; could be changed in the future
			}
		}

		#ifdef NLC_PREPROCESSOR_MATH_FIX_USER_INAPPROPRIATE_USE_OF_EQUALS_SET_IN_LOGICAL_CONDITIONS
		lineContentsSub = replaceAllOccurancesOfString(&lineContentsSub, NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_SET_WITH_PADDING, NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_TEST_WITH_PADDING);
		#endif
		
	#ifdef NLC_MATH_OBJECTS_ADVANCED
		lineContentsNew = lineContentsNew + lineContentsSub;
		if(stillFindingLineContentsSub)
		{	
			//add the string quotation text
			int indexOfStringDelimiter = lineContents->find(NLC_MATH_OBJECTS_STRING_DELIMITER_CHAR, lineContentsSubIndexEnd);
			if(indexOfStringDelimiter != CPP_STRING_FIND_RESULT_FAIL_VALUE)
			{
				lineContentsSubIndex = indexOfStringDelimiter + 1;
				lineContentsNew = lineContentsNew + lineContents->substr(lineContentsSubIndexEnd, indexOfStringDelimiter-lineContentsSubIndexEnd + 1);
			}
			else
			{
				//unfinished quotation
				stillFindingLineContentsSub = false;
				lineContentsNew = lineContentsNew + lineContents->substr(lineContentsSubIndexEnd);	
				cout << "replaceLogicalConditionNaturalLanguageMathWithSymbols{} error: unfinished quotation detected" << endl;
			}			
		}
	}
	*lineContents = lineContentsNew;
	#else
	*lineContents = lineContentsSub;
	#endif
	
	
	if(!parallelReplacement)
	{
		//replace the logical condition operator with a lower case version if necessary
		lineContents->replace(0, logicalConditionOperationsArray[logicalConditionOperator].length(), logicalConditionOperationsArray[logicalConditionOperator]);
	}	
	if(logicalConditionOperator != NLC_LOGICAL_CONDITION_OPERATIONS_ELSE)
	{	
		//ensure all logical condition operators have enclosing brackets eg if(...) - this is done to prevent "if" in "if the house is cold" from being merged into an NLP parsable phrase
		if(!parallelReplacement)
		{
			char characterAfterLogicalConditionOperator = lineContents->at(logicalConditionOperationsArray[logicalConditionOperator].length());
			if(characterAfterLogicalConditionOperator == NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_OPEN_BRACKET)
			{
				#ifdef NLC_PREPROCESSOR_SUPPORT_WHITE_SPACE_BETWEEN_LOGICAL_CONDITION_AND_OPENING_BRACKET
				lineContents->insert(logicalConditionOperationsArray[logicalConditionOperator].length(), 1, NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_OPEN_BRACKET);
				#endif
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

	return result;
}

bool replaceLogicalConditionNaturalLanguageMathWithSymbolsEnd(NLCsentence* firstNLCsentenceInFullSentence, const bool additionalClosingBracketRequired)
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
		{
			#ifdef NLC_PREPROCESSOR_SUPPORT_WHITE_SPACE_BETWEEN_LOGICAL_CONDITION_AND_OPENING_BRACKET
			firstNLCsentenceInFullSentence->mathText.insert(firstNLCsentenceInFullSentence->mathText.length(), 1, NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_CLOSE_BRACKET);
			#endif
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



bool splitMathDetectedLineIntoNLPparsablePhrasesLogicalConditionAddExplicitSubjectTextForConjunctions(NLCsentence* firstNLCsentenceInFullSentence, constEffective NLCsentence** currentNLCsentenceInList, const int* sentenceIndex, const bool additionalClosingBracketRequired)
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
						#ifdef NLC_DEBUG
						//cout << "phrase: " << currentPhraseReferenceToPrimarySubject->sentenceContents << ": found secondary auxiliary" << endl;
						#endif
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
bool generateLogicalConditionImplicitConjunctionsAndIdentifyCommand(string* lineContents, bool* detectedLogicalConditionCommand, string* logicalConditionCommandSubphraseContents, int* logicalConditionCommandSubphraseLineIndex)
{
	bool result = true;

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
			int indexOfConjunctionTemp = lineContents->find(preprocessorMathOperatorsEquivalentConjunctionsWithoutPause[i], expectedPosOfConjunctionIfExistent);
			#ifdef NLC_DEBUG
			//cout << "expectedPosOfConjunctionIfExistent = " << expectedPosOfConjunctionIfExistent << endl;
			//cout << "indexOfConjunctionTemp = " << indexOfConjunctionTemp << endl;
			#endif
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
			currentNLCsubphraseInList->phraseContents = subphraseContents.substr(preprocessorMathOperatorsEquivalentConjunctionsWithoutPause[conjunctionTypeOfConjunction].length());	//remove conjunction from subphrase contents (redundant)
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
	FUTURE support multiple logical condition commands in one line; NLC_PREPROCESSOR_MATH_SUPPORT_MULTIPLE_LOGICAL_CONDITION_COMMANDS_ON_ONE_LINE eg "if the house is blue, write the letter and read the book"/"else write the letter and read the book."
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

				//added 1r5n: support multiple commas, eg "if the house is blue, the cat is green, the apple is sad, and the bike is tall, ride the bike"
				if(currentNLCsubphraseInList->next != NULL)
				{
					currentNLCsubphraseInList2 = currentNLCsubphraseInList->next;
					while(currentNLCsubphraseInList2->next != NULL)
					{
						currentNLCsubphraseInList2->lineIndexOfFirstCharacterInPhrase = currentNLCsubphraseInList2->lineIndexOfFirstCharacterInPhrase + preprocessorMathOperatorsEquivalentConjunctionsWithoutEndWhiteSpace[conjunctionTypeOfFuturePhrase].length();
						currentNLCsubphraseInList2 = currentNLCsubphraseInList2->next;
					}
				}

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
				#ifdef NLC_DEBUG
				//cout << "indexOfLogicalConditionCommand = " <<* indexOfLogicalConditionCommand << endl;
				#endif
				*logicalConditionCommandSubphraseContents = currentNLCsubphraseInList->phraseContents;
				*logicalConditionCommandSubphraseLineIndex = currentNLCsubphraseInList->lineIndexOfFirstCharacterInPhrase;
				#ifdef NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION_DETECT_THEN
				if(logicalConditionCommandSubphraseContents->find(NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION_DETECT_THEN_NAME) == 0)	//ie ", then.."
				{
					//eg If the dog is happy, then ride the bike.
					int thenLength = string(NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION_DETECT_THEN_NAME).length();
					*logicalConditionCommandSubphraseContents = logicalConditionCommandSubphraseContents->substr(thenLength);
					*logicalConditionCommandSubphraseLineIndex = currentNLCsubphraseInList->lineIndexOfFirstCharacterInPhrase;
				}
				#endif
				
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

	#ifdef NLC_DEBUG
	//cout << "lineContents = " <<* lineContents << endl;
	#endif

	#ifdef NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION_DETECT_THEN
	if(!(*detectedLogicalConditionCommand))
	{
		int thenIndex = lineContents->find(NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION_DETECT_THEN_NAME);
		if(thenIndex != CPP_STRING_FIND_RESULT_FAIL_VALUE)
		{
			//eg If the dog is happy then ride the bike.
			int thenLength = string(NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION_DETECT_THEN_NAME).length();
			*detectedLogicalConditionCommand = true;
			*logicalConditionCommandSubphraseContents = lineContents->substr(thenIndex + thenLength);
			*logicalConditionCommandSubphraseLineIndex = thenIndex;
		}		
	
	}
	#endif
	
	return result;
}



bool generateSeparateSentencesFromCommand(string logicalConditionCommandSubphraseContents, int currentIndentation, NLCsentence* firstSentenceInLogicalConditionCommandTemp)
{
	/*
	algorithm;
	if the car is blue, open the door and ride the bike.
	->
	if the car is blue
		open the door.
		ride the bike.

	logicalConditionCommandSubphraseContents = open the door && ride the bike
	*/

	NLCsentence* currentSentenceInLogicalConditionCommandTemp = firstSentenceInLogicalConditionCommandTemp;

	//1r5n: copied from replaceLogicalConditionNaturalLanguageMathWithSymbols;
	for(int i=0; i<NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_COORDINATING_CONJUNCTION_ARRAY_NUMBER_OF_TYPES; i++)
	{
		logicalConditionCommandSubphraseContents = replaceAllOccurancesOfString(&logicalConditionCommandSubphraseContents, preprocessorMathOperatorsEquivalentConjunctions[i], progLangCoordinatingConjunctions[i]);	//NB this is type sensitive; could be changed in the future
	}
	//1r5n: remove preceeding space
	if(logicalConditionCommandSubphraseContents[0] == CHAR_SPACE)
	{
		logicalConditionCommandSubphraseContents = logicalConditionCommandSubphraseContents.substr(1);
	}

	bool result = true;
	int startPosToSearchForConjunction = 0;
	int conjunctionIndex = 0;
	bool stillConjunctionsToFind = true;
	while(stillConjunctionsToFind)
	{
		int indexOfNextConjunction = NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_MAX_CHARACTERS;
		int conjunctionTypeOfNextConjunction = INT_DEFAULT_VALUE;
		bool foundConjunction = false;
		for(int i=0; i<NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_COORDINATING_CONJUNCTION_WITHOUT_PAUSE_ARRAY_NUMBER_OF_TYPES; i++)
		{
			int indexOfConjunctionTemp = logicalConditionCommandSubphraseContents.find(progLangCoordinatingConjunctionsWithoutPause[i], startPosToSearchForConjunction);		//updated 1r5k
			if(indexOfConjunctionTemp != CPP_STRING_FIND_RESULT_FAIL_VALUE)
			{
				#ifdef NLC_DEBUG
				//cout << "mathTextInCommand = " << mathTextInCommand << endl;
				//cout << "indexOfConjunctionTemp = " << indexOfConjunctionTemp << endl;
				#endif

				if(indexOfConjunctionTemp < indexOfNextConjunction)
				{
					indexOfNextConjunction = indexOfConjunctionTemp;
					foundConjunction = true;
					conjunctionTypeOfNextConjunction = i;
					if(i != NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_COORDINATING_CONJUNCTION_AND_INDEX)
					{
						cout << "generateSeparateSentencesFromMathTextAndParsablePhrasesInCommand{}: error: command mathText has a conjunction that is not '&&' (and)" << endl;
						exit(0);
					}
				}
			}
		}

		if(!foundConjunction)
		{
			stillConjunctionsToFind = false;
			indexOfNextConjunction = logicalConditionCommandSubphraseContents.length();
		}

		string subCommandContents = logicalConditionCommandSubphraseContents.substr(startPosToSearchForConjunction, indexOfNextConjunction);

		if(foundConjunction)
		{
			subCommandContents = subCommandContents + CHAR_FULLSTOP;	//1r5n
		}

		#ifdef NLC_DEBUG_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
		cout << "generateSeparateSentencesFromMathTextAndParsablePhrasesInCommand{}: new conjunction found (or last ~phrase in list)" << endl;
		cout << "subCommandContents = " << subCommandContents << endl;
		#endif

		currentSentenceInLogicalConditionCommandTemp->sentenceContents = subCommandContents;
		currentSentenceInLogicalConditionCommandTemp->indentation = currentIndentation;
		currentSentenceInLogicalConditionCommandTemp->next = new NLCsentence();
		currentSentenceInLogicalConditionCommandTemp = currentSentenceInLogicalConditionCommandTemp->next;

		if(stillConjunctionsToFind)
		{
			startPosToSearchForConjunction = indexOfNextConjunction + progLangCoordinatingConjunctionsWithoutPause[conjunctionTypeOfNextConjunction].length();	//updated 1r5k
		}

		conjunctionIndex++;
	}
	return result;
}


#endif




#endif
#endif





