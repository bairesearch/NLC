 /*******************************************************************************
 *
 * License: GNU Affero General Public License version 3 (AGPLv3)
 *
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: NLCpreprocessorMathLogicalConditions.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2022 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler
 * Project Version: 2p1a 05-June-2022
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 * /
 *******************************************************************************/


#include "NLCpreprocessorMathLogicalConditions.hpp"

#ifdef NLC_PREPROCESSOR_MATH
#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE

#ifdef NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION
NLCsubphrase::NLCsubphrase(void)
{
	lineIndexOfFirstWordInPhrase = INT_DEFAULT_VALUE;
	//phraseContents = "";
	hasConjunction = false;
	conjunctionType = INT_DEFAULT_VALUE;
	next = NULL;
}
NLCsubphrase::~NLCsubphrase(void)
{
}
#endif

bool NLCpreprocessorMathLogicalConditionsClass::replaceLogicalConditionNaturalLanguageMathWithSymbols(vector<LRPpreprocessorPlainTextWord*>* lineContents, int logicalConditionOperator, bool* additionalClosingBracketRequired, const bool parallelReplacement)
{
	bool result = true;

		
	for(int i=0; i<NLC_PREPROCESSOR_MATH_OPERATORS_NUMBER_OF_TYPES; i++)
	{
		LRPpreprocessorWordClassObject.findAndReplaceAllOccurancesSimpleSubstringInWordListWithSimpleSubstring(lineContents, preprocessorMathOperatorsEquivalentNumberOfTypes[i], preprocessorMathOperatorsForLogicalConditions[i]);	//NB this is type sensitive; could be changed in the future
	}

	if(logicalConditionOperator != NLC_LOGICAL_CONDITION_OPERATIONS_ELSE)
	{
		//detect conjunctions...
		*additionalClosingBracketRequired = false;
		#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE_REPLACE_COMMAS_WITH_BRACKETS
		for(int i=0; i<NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_COORDINATING_CONJUNCTION_WITH_PAUSE_ARRAY_NUMBER_OF_TYPES; i++)
		{
			if(LRPpreprocessorWordClassObject.findSimpleSubstringInWordList(lineContents, preprocessorMathOperatorsEquivalentConjunctionsWithPause[i]))	//NB this is type sensitive; could be changed in the future
			{
				*additionalClosingBracketRequired = true;
			}
		}
		#endif
		for(int i=0; i<NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_COORDINATING_CONJUNCTION_ARRAY_NUMBER_OF_TYPES; i++)
		{
			LRPpreprocessorWordClassObject.findAndReplaceAllOccurancesSimpleSubstringInWordListWithSimpleSubstring(lineContents, preprocessorMathOperatorsEquivalentConjunctions[i], progLangCoordinatingConjunctions[i]);	//NB this is type sensitive; could be changed in the future
		}
	}

	#ifdef NLC_PREPROCESSOR_MATH_FIX_USER_INAPPROPRIATE_USE_OF_EQUALS_SET_IN_LOGICAL_CONDITIONS
	LRPpreprocessorWordClassObject.findAndReplaceAllOccurancesSimpleSubstringInWordListWithSimpleSubstring(lineContents, NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_SET, NLC_PREPROCESSOR_MATH_OPERATOR_EQUALS_TEST);
	#endif
	
	
	vector<LRPpreprocessorPlainTextWord*> logicalConditionOperationWordList;
	LRPpreprocessorWordClassObject.generateSentenceWordListFromStringSimple(&logicalConditionOperationWordList, &(logicalConditionOperationsArray[logicalConditionOperator]));
	
	if(!parallelReplacement)
	{
		//replace the logical condition operator with a lower case version if necessary
		LRPpreprocessorWordClassObject.replaceWordListAtIndexWithSimpleSubstring(lineContents, 0, logicalConditionOperationsArray[logicalConditionOperator]);
	}	
	if(logicalConditionOperator != NLC_LOGICAL_CONDITION_OPERATIONS_ELSE)
	{	
		//ensure all logical condition operators have enclosing brackets eg if(...) - this is done to prevent "if" in "if the house is cold" from being merged into an NLP parsable phrase
		if(!parallelReplacement)
		{
			int indexOfWordAfterLogicalConditionOperator = logicalConditionOperationWordList.size();
			//cout << "indexOfWordAfterLogicalConditionOperator = " << indexOfWordAfterLogicalConditionOperator << endl;
			
			string wordAfterLogicalConditionOperator = (*lineContents)[indexOfWordAfterLogicalConditionOperator]->tagName;
			if(wordAfterLogicalConditionOperator == SHAREDvars.convertCharToString(NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_OPEN_BRACKET))
			{
				#ifdef NLC_PREPROCESSOR_SUPPORT_WHITE_SPACE_BETWEEN_LOGICAL_CONDITION_AND_OPENING_BRACKET
				LRPpreprocessorWordClassObject.insertStringIntoWordList(lineContents, SHAREDvars.convertCharToString(NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_OPEN_BRACKET), indexOfWordAfterLogicalConditionOperator);
				#endif
				#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE_REPLACE_COMMAS_WITH_BRACKETS
				if(*additionalClosingBracketRequired)
				{
					LRPpreprocessorWordClassObject.insertStringIntoWordList(lineContents, SHAREDvars.convertCharToString(NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_OPEN_BRACKET), indexOfWordAfterLogicalConditionOperator+1);
				}
				#endif
			}
			//unsupported; else if(wordAfterLogicalConditionOperator == CHAR_SPACE)
			else
			{
				LRPpreprocessorWordClassObject.insertStringIntoWordList(lineContents, SHAREDvars.convertCharToString(NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_OPEN_BRACKET), indexOfWordAfterLogicalConditionOperator);	//lineContents->replace(logicalConditionOperationsArray[logicalConditionOperator].length(), 1, NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_OPEN_BRACKET_STRING);
				#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE_REPLACE_COMMAS_WITH_BRACKETS
				if(*additionalClosingBracketRequired)
				{
					LRPpreprocessorWordClassObject.insertStringIntoWordList(lineContents, SHAREDvars.convertCharToString(NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_OPEN_BRACKET), indexOfWordAfterLogicalConditionOperator+1);
				}
				#endif
			}
			/*
			else
			{
				cout << "replaceLogicalConditionNaturalLanguageMathWithSymbols{} error: invalid symbol found after logicalConditionOperator: " << logicalConditionOperationsArray[logicalConditionOperator] << characterAfterLogicalConditionOperator << endl;
			}
			*/
		}
	}

	return result;
}

bool NLCpreprocessorMathLogicalConditionsClass::replaceLogicalConditionNaturalLanguageMathWithSymbolsEnd(NLCpreprocessorSentence* fullSentence, const bool additionalClosingBracketRequired)
{
	bool result = true;

	//remove all commas from mathText:
	fullSentence->mathText = SHAREDvars.replaceAllOccurancesOfString(&(fullSentence->mathText), ", ", "");	//added 1j19a
	fullSentence->mathText = SHAREDvars.replaceAllOccurancesOfString(&(fullSentence->mathText), STRING_COMMA, "");
	
	if(fullSentence->logicalConditionOperator != NLC_LOGICAL_CONDITION_OPERATIONS_ELSE)
	{
		char lastCharacterInMathText = fullSentence->mathText[fullSentence->mathText.length()-1];
		if(lastCharacterInMathText == NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_CLOSE_BRACKET)
		{
			#ifdef NLC_PREPROCESSOR_SUPPORT_WHITE_SPACE_BETWEEN_LOGICAL_CONDITION_AND_OPENING_BRACKET
			fullSentence->mathText.insert(fullSentence->mathText.length(), 1, NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_CLOSE_BRACKET);
			#endif
			#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE_REPLACE_COMMAS_WITH_BRACKETS
			if(additionalClosingBracketRequired)
			{
				fullSentence->mathText.insert(fullSentence->mathText.length(), 1, NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_CLOSE_BRACKET);
			}
			#endif
		}
		else
		{
			fullSentence->mathText.insert(fullSentence->mathText.length(), 1, NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_CLOSE_BRACKET);
			#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE_REPLACE_COMMAS_WITH_BRACKETS
			if(additionalClosingBracketRequired)
			{
				fullSentence->mathText.insert(fullSentence->mathText.length(), 1, NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_CLOSE_BRACKET);
			}
			#endif
		}
	}

	return result;
}



bool NLCpreprocessorMathLogicalConditionsClass::splitMathDetectedLineIntoNLPparsablePhrasesLogicalConditionAddExplicitSubjectTextForConjunctions(NLCpreprocessorSentence* fullSentence, const int* sentenceIndex, const bool additionalClosingBracketRequired)
{
	bool result = true;

	int currentIndentation = fullSentence->indentation;

	//for logical condition NLP parsable phrases, look for first instance of keywords has/is, and take the preceeding text as the context
	//this enables elimination for need for referencing in conjunctions, eg "if{(}the dog has a ball and [the dog] has an apple{)}"
	//FINISH THIS...
	NLCpreprocessorParsablePhrase* currentPhrasePrimarySubject = fullSentence->firstNLPparsablePhraseInList;
	for(int phraseIndex=0; phraseIndex<fullSentence->mathTextNLPparsablePhraseTotal; phraseIndex++)
	{
		bool phraseContainsPrimarySubject = true;
		for(int i=0; i<NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_AUXILIARY_KEYWORDS_TAGGING_SUBJECT_OR_REFERENCE_NUMBER_OF_TYPES; i++)
		{
			int indexOfAuxiliaryTemp = LRPpreprocessorWordClassObject.findStringInWordList(&(currentPhrasePrimarySubject->sentenceContents), preprocessorMathAuxiliaryKeywordsTaggingSubjectOrReference[i], 0);
			if((indexOfAuxiliaryTemp != CPP_STRING_FIND_RESULT_FAIL_VALUE) && (indexOfAuxiliaryTemp == 0))
			{
				phraseContainsPrimarySubject = false;
			}
		}
		for(int i=0; i<NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_COORDINATING_CONJUNCTION_ARRAY_NUMBER_OF_TYPES; i++)
		{
			string parsablePhraseReference = NLCpreprocessorSentenceClass.generateMathTextNLPparsablePhraseReference(fullSentence->firstNLPparsablePhraseInList->sentenceIndex, currentPhrasePrimarySubject);
			int indexOfParsablePhraseReferenceInMathText = fullSentence->mathText.find(parsablePhraseReference);
			if(indexOfParsablePhraseReferenceInMathText != CPP_STRING_FIND_RESULT_FAIL_VALUE)
			{
				int expectedPosOfConjunctionIfExistent = indexOfParsablePhraseReferenceInMathText - progLangCoordinatingConjunctionsWithSpace[i].length();	//CHECKTHIS; use progLangCoordinatingConjunctionsWithSpace rather than progLangCoordinatingConjunctions
				int indexOfConjunction = fullSentence->mathText.find(progLangCoordinatingConjunctionsWithSpace[i], expectedPosOfConjunctionIfExistent);			//CHECKTHIS; use progLangCoordinatingConjunctionsWithSpace rather than progLangCoordinatingConjunctions
				if((indexOfConjunction != CPP_STRING_FIND_RESULT_FAIL_VALUE) && (indexOfConjunction == expectedPosOfConjunctionIfExistent))
				{
					phraseContainsPrimarySubject = false;
				}
			}
			else
			{
				cout << "splitMathDetectedLineIntoNLPparsablePhrases{} error: parsablePhraseReference " << parsablePhraseReference << " not found in mathText " << fullSentence->mathText << endl;
			}
		}

		if(phraseContainsPrimarySubject)
		{

			int indexOfPrimaryAuxiliaryTaggingSubject = CPP_STRING_FIND_RESULT_FAIL_VALUE;
			int primaryAuxiliaryType;

			bool stillFindingPrimaryAuxiliary = true;
			int startPosToSearchForAuxiliary = 0;
			while(stillFindingPrimaryAuxiliary)
			{
				int indexOfNextClosestAuxiliary = NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_MAX_WORDS;
				bool foundAnAuxiliaryButItWasIgnored = false;
				int indexOfClosestIgnoredAuxiliary = NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_MAX_WORDS;
				for(int i=0; i<NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_AUXILIARY_KEYWORDS_TAGGING_SUBJECT_OR_REFERENCE_NUMBER_OF_TYPES; i++)
				{
					int indexOfAuxiliaryTemp = LRPpreprocessorWordClassObject.findStringInWordList(&(currentPhrasePrimarySubject->sentenceContents), preprocessorMathAuxiliaryKeywordsTaggingSubjectOrReference[i], startPosToSearchForAuxiliary);
					if((indexOfAuxiliaryTemp != CPP_STRING_FIND_RESULT_FAIL_VALUE) && (indexOfAuxiliaryTemp < indexOfNextClosestAuxiliary))
					{
						//ignore auxiliary if has a preceeding 'that'/'which'; eg "the dog that is[ignore] near the house has[take] a ball or has[reference] an apple"
						//"If the basket that is near the house is above the tray, and the basket is blue, the dog is happy."
						//"If the basket that is near the house is above the tray and is blue, the dog is happy.
						bool ignoreAuxiliary = false;
						for(int i2=0; i2<NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_RCMOD_SAME_REFERENCE_SET_DELIMITER_NUMBER_OF_TYPES; i2++)
						{
							int expectedPosOfRcmodSameReferenceSetDelimiterIfExistent = indexOfAuxiliaryTemp-1;
							int indexOfRcmodSameReferenceSet = LRPpreprocessorWordClassObject.findStringInWordList(&(currentPhrasePrimarySubject->sentenceContents), preprocessorMathRcmodSameReferenceSetDelimiter[i2], expectedPosOfRcmodSameReferenceSetDelimiterIfExistent);
							if((indexOfRcmodSameReferenceSet != CPP_STRING_FIND_RESULT_FAIL_VALUE) && (indexOfRcmodSameReferenceSet == expectedPosOfRcmodSameReferenceSetDelimiterIfExistent))
							{
								ignoreAuxiliary = true;
								foundAnAuxiliaryButItWasIgnored = true;
								if(indexOfAuxiliaryTemp < indexOfClosestIgnoredAuxiliary)
								{
									indexOfClosestIgnoredAuxiliary = indexOfAuxiliaryTemp;
								}
							}
						}

						if(!ignoreAuxiliary)
						{
							indexOfNextClosestAuxiliary = indexOfAuxiliaryTemp;
							primaryAuxiliaryType = i;
						}
					}
				}
				if(indexOfNextClosestAuxiliary != NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_MAX_WORDS)
				{
					indexOfPrimaryAuxiliaryTaggingSubject = indexOfNextClosestAuxiliary;
					stillFindingPrimaryAuxiliary = false;
				}
				else if(foundAnAuxiliaryButItWasIgnored)
				{
					startPosToSearchForAuxiliary = indexOfClosestIgnoredAuxiliary + 1;
				}
				else
				{
					stillFindingPrimaryAuxiliary = false;
				}
			}

			if(indexOfPrimaryAuxiliaryTaggingSubject != CPP_STRING_FIND_RESULT_FAIL_VALUE)
			{
				vector<LRPpreprocessorPlainTextWord*> subjectText = LRPpreprocessorWordClassObject.extractSubWordListInWordList(&(currentPhrasePrimarySubject->sentenceContents), 0, indexOfPrimaryAuxiliaryTaggingSubject);

				NLCpreprocessorParsablePhrase* currentPhraseReferenceToPrimarySubject = currentPhrasePrimarySubject->next;
				for(int phraseIndex2=phraseIndex+1; phraseIndex2<fullSentence->mathTextNLPparsablePhraseTotal; phraseIndex2++)
				{
					//now for each secondary auxiliary referencing the subject, artificially generate (copy) the subject text

					#ifdef NLC_PREPROCESSOR_MATH_SEARCH_FOR_CONJUNCTION_SUBJECT_MATCH_NON_IDENTICAL_AUXILLARIES
					int indexOfSecondaryAuxiliaryReferencingSubject = CPP_STRING_FIND_RESULT_FAIL_VALUE;
					for(int i=0; i<NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_AUXILIARY_KEYWORDS_TAGGING_SUBJECT_OR_REFERENCE_NUMBER_OF_TYPES; i++)
					{
						int indexOfAuxiliaryTemp = LRPpreprocessorWordClassObject.findStringInWordList(&(currentPhraseReferenceToPrimarySubject->sentenceContents), preprocessorMathAuxiliaryKeywordsTaggingSubjectOrReference[i]);
						if((indexOfAuxiliaryTemp != CPP_STRING_FIND_RESULT_FAIL_VALUE) && (indexOfAuxiliaryTemp  == 0))
						{
							indexOfSecondaryAuxiliaryReferencingSubject = indexOfAuxiliaryTemp;
						}
					}
					#else
					int indexOfSecondaryAuxiliaryReferencingSubject = findStringInWordList(&(currentPhraseReferenceToPrimarySubject->sentenceContents), preprocessorMathAuxiliaryKeywordsTaggingSubjectOrReference[primaryAuxiliaryType]);
					#endif
					if((indexOfSecondaryAuxiliaryReferencingSubject != CPP_STRING_FIND_RESULT_FAIL_VALUE) && (indexOfSecondaryAuxiliaryReferencingSubject == 0))
					{
						bool secondaryChecks = false;
						for(int i=0; i<NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_COORDINATING_CONJUNCTION_ARRAY_NUMBER_OF_TYPES; i++)
						{
							string parsablePhraseReference = NLCpreprocessorSentenceClass.generateMathTextNLPparsablePhraseReference(fullSentence->firstNLPparsablePhraseInList->sentenceIndex, currentPhraseReferenceToPrimarySubject);
							int indexOfParsablePhraseReferenceInMathText = fullSentence->mathText.find(parsablePhraseReference);
							if(indexOfParsablePhraseReferenceInMathText != CPP_STRING_FIND_RESULT_FAIL_VALUE)
							{
								int expectedPosOfConjunctionIfExistent = indexOfParsablePhraseReferenceInMathText - progLangCoordinatingConjunctionsWithSpace[i].length();	//CHECKTHIS; use progLangCoordinatingConjunctionsWithSpace rather than progLangCoordinatingConjunctions
								int indexOfConjunction = fullSentence->mathText.find(progLangCoordinatingConjunctionsWithSpace[i], expectedPosOfConjunctionIfExistent);		//CHECKTHIS; use progLangCoordinatingConjunctionsWithSpace rather than progLangCoordinatingConjunctions
								if((indexOfConjunction != CPP_STRING_FIND_RESULT_FAIL_VALUE) && (indexOfConjunction == expectedPosOfConjunctionIfExistent))
								{
									secondaryChecks = true;
								}
							}
							else
							{
								cout << "splitMathDetectedLineIntoNLPparsablePhrases{} error: parsablePhraseReference " << parsablePhraseReference << " not found in mathText " << fullSentence->mathText << endl;
							}
						}

						if(secondaryChecks)
						{
							//insert subject content
							string parsablePhraseReferenceOld = NLCpreprocessorSentenceClass.generateMathTextNLPparsablePhraseReference(fullSentence->firstNLPparsablePhraseInList->sentenceIndex, currentPhraseReferenceToPrimarySubject);

							LRPpreprocessorWordClassObject.insertWordListIntoWordList((&currentPhraseReferenceToPrimarySubject->sentenceContents), &subjectText, indexOfSecondaryAuxiliaryReferencingSubject);

							string parsablePhraseReferenceNew = NLCpreprocessorSentenceClass.generateMathTextNLPparsablePhraseReference(fullSentence->firstNLPparsablePhraseInList->sentenceIndex, currentPhraseReferenceToPrimarySubject);
							int parsablePhraseReferenceOldPos = fullSentence->mathText.find(parsablePhraseReferenceOld);
							if(parsablePhraseReferenceOldPos != CPP_STRING_FIND_RESULT_FAIL_VALUE)
							{
								fullSentence->mathText.replace(parsablePhraseReferenceOldPos, parsablePhraseReferenceOld.length(), parsablePhraseReferenceNew);
							}
							else
							{
								cout << "splitMathDetectedLineIntoNLPparsablePhrases{} error: parsablePhraseReferenceOld " << parsablePhraseReferenceOld << " not found in mathText " << fullSentence->mathText << endl;
							}

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
bool NLCpreprocessorMathLogicalConditionsClass::generateLogicalConditionImplicitConjunctionsAndIdentifyCommand(vector<LRPpreprocessorPlainTextWord*>* lineContents, bool* detectedLogicalConditionCommand, vector<LRPpreprocessorPlainTextWord*>* logicalConditionCommandSubphraseContents, int* logicalConditionCommandSubphraseLineIndex)
{
	bool result = true;

	*detectedLogicalConditionCommand = false;

	NLCsubphrase* firstNLCsubphraseInList = new NLCsubphrase();
	NLCsubphrase* currentNLCsubphraseInList = firstNLCsubphraseInList;

	int startPosToSearchForComma = 0;
	int commaIndex = 0;
	bool stillCommasToFind = true;
	while(stillCommasToFind)
	{
		int indexOfNextComma = LRPpreprocessorWordClassObject.findStringInWordList(lineContents, STRING_COMMA, startPosToSearchForComma);
		if(indexOfNextComma == CPP_STRING_FIND_RESULT_FAIL_VALUE)
		{
			stillCommasToFind = false;
			indexOfNextComma = lineContents->size();
		}

		bool conjunctionFoundInSubphrase = false;
		int conjunctionTypeOfConjunction = INT_DEFAULT_VALUE;
		for(int i=0; i<NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_COORDINATING_CONJUNCTION_BASIC_ARRAY_NUMBER_OF_TYPES; i++)
		{
			int expectedPosOfConjunctionIfExistent = startPosToSearchForComma;
			if(LRPpreprocessorWordClassObject.findSimpleSubstringInWordListAtIndex(lineContents, preprocessorMathOperatorsEquivalentConjunctionsBasic[i], expectedPosOfConjunctionIfExistent, false))
			{
				conjunctionFoundInSubphrase = true;
				conjunctionTypeOfConjunction = i;
			}
		}

		vector<LRPpreprocessorPlainTextWord*> subphraseContents = LRPpreprocessorWordClassObject.extractSubWordListInWordList(lineContents, startPosToSearchForComma, indexOfNextComma-startPosToSearchForComma);


		currentNLCsubphraseInList->lineIndexOfFirstWordInPhrase = startPosToSearchForComma;
		currentNLCsubphraseInList->hasConjunction = conjunctionFoundInSubphrase;
		
		#ifdef NLC_PREPROCESSOR_DEBUG
		cout << "generateLogicalConditionImplicitConjunctionsAndIdentifyCommand{}: subphraseContents = " << LRPpreprocessorWordClassObject.generateTextFromVectorWordList(&subphraseContents) << endl;
		#endif

		if(conjunctionFoundInSubphrase)
		{
			if(subphraseContents.size() < 1)	//< 2?
			{
				cerr << "NLCpreprocessorMathLogicalConditionsClass::generateLogicalConditionImplicitConjunctionsAndIdentifyCommand{} error: (subphraseContents.size() < 1)" << endl;
				exit(EXIT_ERROR);
			}
			currentNLCsubphraseInList->phraseContents = LRPpreprocessorWordClassObject.extractSubWordListInWordList(&subphraseContents, 1);	//remove conjunction from subphrase contents (redundant) - ie the first word in the subphrase
			currentNLCsubphraseInList->conjunctionType = conjunctionTypeOfConjunction;
		}
		else
		{
			currentNLCsubphraseInList->phraseContents = subphraseContents;
		}


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
	CHECKTHIS:
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
				LRPpreprocessorWordClassObject.insertStringIntoWordList(lineContents, preprocessorMathOperatorsEquivalentConjunctionsBasic[conjunctionTypeOfFuturePhrase], currentNLCsubphraseInList->lineIndexOfFirstWordInPhrase);
								
				//added 1r5n: support multiple commas, eg "if the house is blue, the cat is green, the apple is sad, and the bike is tall, ride the bike"
				if(currentNLCsubphraseInList->next != NULL)
				{
					currentNLCsubphraseInList2 = currentNLCsubphraseInList->next;
					while(currentNLCsubphraseInList2->next != NULL)
					{
						currentNLCsubphraseInList2->lineIndexOfFirstWordInPhrase = currentNLCsubphraseInList2->lineIndexOfFirstWordInPhrase + 1;
						currentNLCsubphraseInList2 = currentNLCsubphraseInList2->next;
					}
				}

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
			if(previousPhraseHadConjunction || (commaIndex == numberOfSuperPhrases-1))
			{
				//found first phrase in logical condition command
				*detectedLogicalConditionCommand = true;
				//*indexOfLogicalConditionCommand = currentNLCsubphraseInList->lineIndexOfFirstWordInPhrase;
				*logicalConditionCommandSubphraseContents = currentNLCsubphraseInList->phraseContents;
				*logicalConditionCommandSubphraseLineIndex = currentNLCsubphraseInList->lineIndexOfFirstWordInPhrase;
				#ifdef NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION_DETECT_THEN
				if(LRPpreprocessorWordClassObject.findStringInWordList(logicalConditionCommandSubphraseContents, NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION_DETECT_THEN_NAME) == 0)	//ie ", then.."
				{
					//eg If the dog is happy, then ride the bike.
					LRPpreprocessorWordClassObject.removeWordFromWordList(logicalConditionCommandSubphraseContents, 0);	//remove the "then" word	//extractSubWordListInWordList(logicalConditionCommandSubphraseContents, 1, (logicalConditionCommandSubphraseContents->size()-1));
					*logicalConditionCommandSubphraseLineIndex = currentNLCsubphraseInList->lineIndexOfFirstWordInPhrase;
				}
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


	#ifdef NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION_DETECT_THEN
	if(!(*detectedLogicalConditionCommand))
	{
		int thenIndex = LRPpreprocessorWordClassObject.findStringInWordList(lineContents, NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_ADVANCED_PHRASE_DETECTION_DETECT_THEN_NAME);
		if(thenIndex != CPP_STRING_FIND_RESULT_FAIL_VALUE)
		{
			//eg If the dog is happy then ride the bike.
			*detectedLogicalConditionCommand = true;
			*logicalConditionCommandSubphraseContents = LRPpreprocessorWordClassObject.extractSubWordListInWordList(logicalConditionCommandSubphraseContents, thenIndex+1);
			*logicalConditionCommandSubphraseLineIndex = thenIndex;
		}		
	
	}
	#endif
	
	return result;
}



bool NLCpreprocessorMathLogicalConditionsClass::generateSeparateSentencesFromCommand(vector<LRPpreprocessorPlainTextWord*>* logicalConditionCommandSubphraseContents, int currentIndentation, NLCpreprocessorSentence* firstSentenceInLogicalConditionCommandTemp)
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

	NLCpreprocessorSentence* currentSentenceInLogicalConditionCommandTemp = firstSentenceInLogicalConditionCommandTemp;

	//1r5n: copied from replaceLogicalConditionNaturalLanguageMathWithSymbols;
	for(int i=0; i<NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_COORDINATING_CONJUNCTION_ARRAY_NUMBER_OF_TYPES; i++)
	{
		LRPpreprocessorWordClassObject.findAndReplaceAllOccurancesSimpleSubstringInWordListWithSimpleSubstring(logicalConditionCommandSubphraseContents, preprocessorMathOperatorsEquivalentConjunctions[i], progLangCoordinatingConjunctions[i]);		//NB this is type sensitive; could be changed in the future
	}
	//OLD: 1r5n: remove preceeding space	//CHECKTHIS: //if(logicalConditionCommandSubphraseContents[0] == CHAR_SPACE) logicalConditionCommandSubphraseContents = logicalConditionCommandSubphraseContents.substr(1);

	bool result = true;
	int startPosToSearchForConjunction = 0;
	int conjunctionIndex = 0;
	bool stillConjunctionsToFind = true;
	while(stillConjunctionsToFind)
	{
		int indexOfNextConjunction = NLC_PREPROCESSOR_MATH_NLP_PARSABLE_PHRASE_MAX_WORDS;
		int conjunctionTypeOfNextConjunction = INT_DEFAULT_VALUE;
		bool foundConjunction = false;
		for(int i=0; i<NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_COORDINATING_CONJUNCTION_WITHOUT_PAUSE_ARRAY_NUMBER_OF_TYPES; i++)
		{
			int indexOfConjunctionTemp = LRPpreprocessorWordClassObject.findStringInWordList(logicalConditionCommandSubphraseContents, progLangCoordinatingConjunctionsBasic[i], startPosToSearchForConjunction);		//updated 1r5k
			if(indexOfConjunctionTemp != CPP_STRING_FIND_RESULT_FAIL_VALUE)
			{
				if(indexOfConjunctionTemp < indexOfNextConjunction)
				{
					indexOfNextConjunction = indexOfConjunctionTemp;
					foundConjunction = true;
					conjunctionTypeOfNextConjunction = i;
					if(i != NLC_PREPROCESSOR_MATH_OPERATOR_EQUIVALENT_NATURAL_LANGUAGE_COORDINATING_CONJUNCTION_AND_INDEX)
					{
						cerr << "generateSeparateSentencesFromMathTextAndParsablePhrasesInCommand{}: error: command mathText has a conjunction that is not '&&' (and)" << endl;
						exit(EXIT_ERROR);
					}
				}
			}
		}

		if(!foundConjunction)
		{
			stillConjunctionsToFind = false;
			indexOfNextConjunction = logicalConditionCommandSubphraseContents->size();
		}

		vector<LRPpreprocessorPlainTextWord*> subCommandContents = LRPpreprocessorWordClassObject.extractSubWordListInWordList(logicalConditionCommandSubphraseContents, startPosToSearchForConjunction, indexOfNextConjunction-startPosToSearchForConjunction);	//CHECKTHIS; length parameter used to be indexOfNextConjunction

		if(foundConjunction)
		{
			LRPpreprocessorWordClassObject.addStringToWordList(&subCommandContents, STRING_FULLSTOP);	//1r5n
		}

		//currentSentenceInLogicalConditionCommandTemp->firstNLPparsablePhraseInList->sentenceIndex = ?		//CHECKTHIS
		currentSentenceInLogicalConditionCommandTemp->firstNLPparsablePhraseInList->sentenceContents = subCommandContents;
		currentSentenceInLogicalConditionCommandTemp->indentation = currentIndentation;
		currentSentenceInLogicalConditionCommandTemp->next = new NLCpreprocessorSentence();
		currentSentenceInLogicalConditionCommandTemp = currentSentenceInLogicalConditionCommandTemp->next;

		if(stillConjunctionsToFind)
		{
			startPosToSearchForConjunction = indexOfNextConjunction + 1;	//updated 1r5k	//+1 to account for progLangCoordinatingConjunctionsWithoutPause[conjunctionTypeOfNextConjunction] - CHECKTHIS
		}

		conjunctionIndex++;
	}
	return result;
}


#endif




#endif
#endif





