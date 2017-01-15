
bool generateCodeBlocksPart3actions(NLCcodeblock** currentCodeBlockInTree, vector<GIAentityNode*>* entityNodesActiveListSentence, int sentenceIndex, string NLCfunctionName, NLCsentence* currentNLCsentenceInList)
{
	bool result = true;
	
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListSentence->begin(); entityIter != entityNodesActiveListSentence->end(); entityIter++)
	{
		GIAentityNode* actionEntity = (*entityIter);
		if(actionEntity->isAction)
		{
			if(!(actionEntity->isActionConcept))
			{
				#ifdef NLC_DEBUG
				//cout << "generateCodeBlocksPart3actions(): " << endl;
				//cout << "actionEntity->entityName = " << actionEntity->entityName << endl;
				//cout << "currentNLCsentenceInList->singleWordSentenceActionName = " << currentNLCsentenceInList->singleWordSentenceActionName << endl;
				//cout << "actionEntity->isAction = " << actionEntity->isAction << endl;
				//cout << "actionEntity->hasAssociatedInstance = " << actionEntity->hasAssociatedInstance << endl;
				#endif
				
				if(checkSentenceIndexParsingCodeBlocks(actionEntity, sentenceIndex, true))
				{
					#ifdef NLC_PREPROCESSOR_INTERPRET_SINGLE_WORD_SENTENCES_AS_ACTIONS_REPLACE_ACTION_ALSO_DUE_TO_NLP_LIMITATION
					if(actionEntity->entityName == NLC_PREPROCESSOR_INTERPRET_SINGLE_WORD_SENTENCES_AS_ACTIONS_DUMMY_TEXT_ACTION)
					{
						actionEntity->entityName = currentNLCsentenceInList->singleWordSentenceActionName;
					}
					#endif

					generateActionCodeBlocks(currentCodeBlockInTree, actionEntity, sentenceIndex, NLCfunctionName);
				}
			}
		}
	}
	
	#ifdef NLC_ACTION_CATEGORY_LISTS_USE_FOR_PLURAL_ACTION_SUBJECTSOBJECTS_IN_MULTIACTION_INITIALISATION_SENTENCES
	#ifdef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES	//note NLCcategoryListCreatedTemp is only required to be cleared between sentences for !GIA_DISABLE_CROSS_SENTENCE_REFERENCING
	//clear for next sentence 
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListSentence->begin(); entityIter != entityNodesActiveListSentence->end(); entityIter++)
	{
		GIAentityNode* entity = (*entityIter);
		if(entity->NLCcategoryListCreatedTemp)
		{
			entity->NLCcategoryListCreatedTemp = false;
		}
	}
	#endif
	#endif
	
	return result;
}






bool generateCodeBlocksPart4objectInitialisations(NLCcodeblock** currentCodeBlockInTree, vector<GIAentityNode*>* entityNodesActiveListSentence, int sentenceIndex, string NLCfunctionName)
{
	bool result = true;
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListSentence->begin(); entityIter != entityNodesActiveListSentence->end(); entityIter++)
	{
		GIAentityNode* entity = *entityIter;
		if(checkSentenceIndexParsingCodeBlocks(entity, sentenceIndex, false))
		{
			if(!checkSpecialCaseEntity(entity, true))
			{
				#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
				generateCodeBlocksObjectInitialisationsForEntity(currentCodeBlockInTree, entity, sentenceIndex);
				#else
				//This code is effectively identical to generateCodeBlocksObjectInitialisationsForEntity(), without the generateParentContext argument;
				GIAentityNode* parentEntity = getParent(entity, sentenceIndex);
				if(!checkSpecialCaseEntity(parentEntity, true))
				{
					if(!generateParentInitialisationCodeBlockWithChecks(currentCodeBlockInTree, parentEntity , sentenceIndex, false))
					{
						generateObjectInitialisationsBasedOnPropertiesAndConditions(parentEntity, currentCodeBlockInTree , sentenceIndex, NULL, "", false, false);
					}
				}
				#endif
			}
		}
	}
	return result;
}

#ifdef NLC_SUPPORT_REDEFINITIONS
bool generateCodeBlocksPart5redefinitions(NLCcodeblock** currentCodeBlockInTree, vector<GIAentityNode*>* entityNodesActiveListSentence, vector<GIAentityNode*>* entityNodesActiveListComplete, int sentenceIndex, string NLCfunctionName)
{
	bool result = true;

	bool phraseContainsSubstanceWithDefinitionLink = false;
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListSentence->begin(); entityIter != entityNodesActiveListSentence->end(); entityIter++)
	{
		GIAentityNode* entity = (*entityIter);
		if(checkSentenceIndexParsingCodeBlocks(entity, sentenceIndex, false))
		{
			if(!checkSpecialCaseEntity(entity, true))
			{		
				for(vector<GIAentityConnection*>::iterator iter = entity->entityNodeDefinitionList->begin(); iter < entity->entityNodeDefinitionList->end(); iter++)
				{
					GIAentityConnection* definitionConnection = *iter;
					GIAentityNode* definitionEntity = definitionConnection->entity;
					if(checkSentenceIndexParsingCodeBlocks(definitionEntity, definitionConnection, sentenceIndex, false))
					{
						if(!(definitionConnection->sameReferenceSet))
						{
							#ifdef NLC_USE_ADVANCED_REFERENCING_SUPPORT_ALIASES
							if(definitionConnection->isAlias)
							{
								bool aliasAlreadyInitialised = false;
								string aliasName = definitionEntity->entityName;
								string aliasClassName = entity->entityName;

								string aliasNameTemp = "";
								if(findAliasInEntity(definitionEntity, &aliasNameTemp)) //*
								{
									aliasAlreadyInitialised = true;
								}
								if(!aliasAlreadyInitialised)
								{	
									//check this code
									#ifdef NLC_DEBUG_ADVANCED_REFERENCING_SUPPORT_ALIASES
									cout << "generateCodeBlocksPart5redefinitions (alias):" << endl;
									cout << "definitionEntity (aliasName) = " << definitionEntity << endl;
									cout << "entity (aliasClassName) = " << entity << endl;
									#endif

									/*
									unordered_map<string, string>*  functionAliasClassList = getFunctionAliasClassList();
									functionAliasClassList->insert(pair<string, string>(aliasName, entity));
									*/
									
									NLCcodeblock* firstCodeBlockInSentence = *currentCodeBlockInTree;
									GIAentityNode* parentEntity = NULL;
									
									NLCgenerateContextBlocksVariables generateContextBlocksVariables;
									//generateContextBlocksVariables.searchSubstanceConceptsForChildren = false;	//added 1n5g (only check the explicit variable for definition; do not parse categories) - CHECKTHIS
									generateContextBlocksVariables.onlyGenerateContextBlocksIfConnectionsParsedForNLCorSameReferenceSet = true;
									bool generatedContextBlocks = getParentAndInitialiseParentIfNecessaryOrGenerateContextBlocks(currentCodeBlockInTree, entity, sentenceIndex, &generateContextBlocksVariables, false, &parentEntity, false);

									/*OLD:
									bool generatedParentContext = false;
									if(!generateContextBlocks(currentCodeBlockInTree, entity, sentenceIndex, &generateContextBlocksVariables, generatedParentContext, NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION))
									{
										#ifdef NLC_DEBUG_ADVANCED_REFERENCING_SUPPORT_ALIASES
										cout << "identifyAliasesInCurrentSentence(): !generateContextBlocks: entity = " << entity->entityName << endl;
										#endif
									}
									*/

									*currentCodeBlockInTree = createCodeBlocksAddAliasToEntityAliasList(*currentCodeBlockInTree, entity, aliasName);

									*currentCodeBlockInTree = getLastCodeBlockInLevel(firstCodeBlockInSentence);

									//1k14c; replace all alias GIA entities with their respective class (eg dog), and add an alias to their vector list (eg Tom)
									for(vector<GIAentityNode*>::iterator entityIter2 = entityNodesActiveListComplete->begin(); entityIter2 != entityNodesActiveListComplete->end(); entityIter2++)
									{
										GIAentityNode* entity2 = (*entityIter2);
										if(entity2->entityName == aliasName)
										{
											if(entity2->sentenceIndexTemp > definitionEntity->sentenceIndexTemp)	//this test isn't required because of* 
											{
												entity2->aliasList.push_back(aliasName);
												entity2->entityName = aliasClassName;	
											}
										}
									}	
								}
							
							}
							else
							{
							#endif
								//eg [Alsations are dogs. The pound has a dog. The dog is happy.] The dog is an alsation.  ; converts dog to alsation

								#ifndef NLC_SUPPORT_REDEFINITIONS_FOR_IMMEDIATELY_DECLARED_INDEFINITE_ENTITIES
								//eg chickens are animals. an animal is a chicken. In practice this will not be implemented because GIA interprets indefinite-indefinite definitions as substance concepts. redefinitions are generally not implied for indefinite children (eg "an animal" in "an animal is a chicken") because they are ambiguous; this example either means a) animals are chickens (ie is a substanceConcept-substanceConcept definition; not a redefinition - and happens to be an incorrect statement based on aprior knowledge about the animal kingdom because we know chickens are animals not vice versa), or b) a newly declared animal is cast to a chicken (a specific version of animal, assuming "chickens are animals" has been declared)
								if(!isDefiniteEntity(definitionEntity))
								{
									bool foundDefiniteParentOfEntity = false;
									bool parseConditionParents = true;	//use default value here
									bool checkIsDefinite = true;
									GIAentityNode* parentEntity = getSameReferenceSetUniqueParent(entity, sentenceIndex, NULL, &foundDefiniteParentOfEntity, parseConditionParents, checkIsDefinite);
									if(isDefiniteEntity(entity) || foundDefiniteParentOfEntity)
									{
								#endif
										if(entity->entityName != definitionEntity->entityName)
										{//ignore substanceConcept definitions for for entities of same name
											
											#ifdef NLC_DEBUG
											cout << "generateCodeBlocksPart5redefinitions (definition):" << endl;
											cout << "sentenceIndex = " << sentenceIndex << endl;
											cout << "entity = " << entity->entityName << endl;
											cout << "definitionEntity = " << definitionEntity->entityName << endl;
											#endif
											
											NLCcodeblock* firstCodeBlockInSentence = *currentCodeBlockInTree;

											GIAentityNode* parentEntity = NULL;

											//1. and 2. get parent of the dog (eg pound) and generate context of the dog
											NLCgenerateContextBlocksVariables generateContextBlocksVariables;
											generateContextBlocksVariables.searchSubstanceConceptsForChildren = false;	//added 1n5g (only check the explicit variable for definition; do not parse categories) - CHECKTHIS
											bool generatedContextBlocks = getParentAndInitialiseParentIfNecessaryOrGenerateContextBlocks(currentCodeBlockInTree, entity, sentenceIndex, &generateContextBlocksVariables, false, &parentEntity, false);

											//3. verify that alsations are dogs
											*currentCodeBlockInTree = createCodeBlockCheckParentClassNameExecuteFunction2(*currentCodeBlockInTree, definitionEntity, entity->entityName);

											//4. cast the dog to alsation
											*currentCodeBlockInTree = createCodeConvertParentToChildClass(*currentCodeBlockInTree, entity, definitionEntity);

											//5. add alsation to alsation property list of pound 
												//LIMITATION: NB the dog will still be added to the dog property list of pound; therefore these must remain synced; ie the dog or the alsation cannot be deleted from the pound...
												//to avoid this limitation at present the user must define an object by its most specific class initially (avoiding redefinitions). NLC will automatically search for references to the child based on substance concept definition link to its parent [dream mode has connected substance concept definiton links to all instantations thereof]
											if(parentEntity != entity)
											{
												*currentCodeBlockInTree =  createCodeBlockAddProperty(*currentCodeBlockInTree, parentEntity, definitionEntity, sentenceIndex);
											}

											//6. add alsation to alsation local list
											*currentCodeBlockInTree =  createCodeBlockAddEntityToLocalList(*currentCodeBlockInTree, definitionEntity, definitionEntity);

											*currentCodeBlockInTree = getLastCodeBlockInLevel(firstCodeBlockInSentence);

										}
								#ifndef NLC_SUPPORT_REDEFINITIONS_FOR_IMMEDIATELY_DECLARED_INDEFINITE_ENTITIES
									}
									else
									{
										cout << "checkIfPhraseContainsSubstanceWithDefinitionLink() warning: !(isDefiniteEntity(entity) || foundDefiniteParentOfEntity))" << endl;
									}
								}
								else
								{
									cout << "checkIfPhraseContainsSubstanceWithDefinitionLink() warning: isDefiniteEntity(definitionEntity))" << endl;
								}
								#endif
							#ifdef NLC_USE_ADVANCED_REFERENCING_SUPPORT_ALIASES						
							}
							#endif
						}
					}
				}
			}
		}
	}
	return result;
}
#endif


void generateActionCodeBlocks(NLCcodeblock** currentCodeBlockInTree, GIAentityNode* actionEntity, int sentenceIndex, string NLCfunctionName)
{
	NLCcodeblock* firstCodeBlockInSentence = *currentCodeBlockInTree;

	#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
	if(!(actionEntity->NLCparsedForlogicalConditionOperations))
	{
	#endif
		#ifdef NLC_RECORD_ACTION_HISTORY_GENERALISABLE_DO_NOT_EXECUTE_PAST_TENSE_ACTIONS
		if(!isPotentialAction(actionEntity))
		{
		#endif
			#ifdef NLC_DEBUG
			cout << "actionEntity->entityName = " << actionEntity->entityName << endl;
			cout << "sentenceIndex = " << sentenceIndex << endl;
			#endif

			#ifdef NLC_RECORD_ACTION_HISTORY_GENERALISABLE
			bool sameReferenceSet = false;
			#endif

			bool actionIsSingleWord = false;
			bool actionHasObject = false;
			GIAentityNode* objectEntity = NULL;
			GIAentityConnection* actionObjectConnection = NULL;
			if(getActionObjectEntityConnection(actionEntity, sentenceIndex, &actionObjectConnection))
			{
				//cout << "actionObjectConnection->sameReferenceSet = " << actionObjectConnection->sameReferenceSet << endl;
				#ifdef NLC_RECORD_ACTION_HISTORY_GENERALISABLE
				if(!(actionObjectConnection->sameReferenceSet))
				{
					//cout << "sentenceIndex " << sentenceIndex << endl;
					//cout << "actionEntity->entityName: " << actionEntity->entityName << endl;
					//cout << "objectEntity->entity: " << actionObjectConnection->entity->entityName << endl;
					//cout << "actionObjectConnection->sameReferenceSet: " << actionObjectConnection->sameReferenceSet << endl;
				#endif
					actionHasObject = true;
					objectEntity = actionObjectConnection->entity;
					#ifdef NLC_PREPROCESSOR_INTERPRET_SINGLE_WORD_SENTENCES_AS_ACTIONS
					if(objectEntity->entityName == NLC_PREPROCESSOR_INTERPRET_SINGLE_WORD_SENTENCES_AS_ACTIONS_DUMMY_TEXT_ACTION_OBJECT)
					{
						actionIsSingleWord = true;
						actionHasObject = false;
						objectEntity->disabled = true;	//prevent parsing of dummyActionObject by generateCodeBlocksPart4objectInitialisations()
					}
					#endif	
				#ifdef NLC_RECORD_ACTION_HISTORY_GENERALISABLE
				}
				#endif
			}
			bool actionHasSubject = false;
			GIAentityNode* subjectEntity = NULL;
			GIAentityConnection* actionSubjectConnection = NULL;
			if(getActionSubjectEntityConnection(actionEntity, sentenceIndex, &actionSubjectConnection))
			{
				//cout << "actionSubjectConnection->sameReferenceSet = " << actionSubjectConnection->sameReferenceSet << endl;
				#ifdef NLC_RECORD_ACTION_HISTORY_GENERALISABLE
				if(!(actionSubjectConnection->sameReferenceSet))
				{
					//cout << "sentenceIndex " << sentenceIndex << endl;
					//cout << "actionEntity->entityName: " << actionEntity->entityName << endl;
					//cout << "subjectEntity->entity: " << actionSubjectConnection->entity->entityName << endl;
					//cout << "actionSubjectConnection->sameReferenceSet: " << actionSubjectConnection->sameReferenceSet << endl;
				#endif
					actionHasSubject = true;
					subjectEntity = actionSubjectConnection->entity;
				#ifdef NLC_RECORD_ACTION_HISTORY_GENERALISABLE
				}
				#endif
			}


			NLCcodeblock* functionExecuteCodeBlockInTree = NULL;

			if(actionHasObject || actionHasSubject || actionIsSingleWord)
			{
				#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS
				initialiseFunctionArguments(currentCodeBlockInTree, actionEntity, sentenceIndex);
				//firstCodeBlockInSentence = *currentCodeBlockInTree;		//removed 1f1b... [CHECKTHIS]
				/*
				#ifdef NLC_USE_LIBRARY
				*currentCodeBlockInTree = createCodeBlockDeclareTempVariable(*currentCodeBlockInTree, generateClassName(NLC_CLASS_DEFINITIONS_GENERIC_LIBRARY_ENTITY_CLASS_TITLE), NLC_USE_LIBRARY_MOVE_FUNCTION_ACTIONOBJECT_PARENT_TEMP_VARIABLE_NAME);	//NLCgenericEntity* functionObjectParent;
				#endif
				*/
				#endif

				#ifndef NLC_DEFINE_LOCAL_VARIABLES_FOR_ALL_INDEFINATE_ENTITIES
				//this is where original getParentAndInitialiseParentIfNecessaryOrGenerateContextBlocks code went (for both subjectEntity and objectEntity)
				if(actionHasSubject)
				{
					getParentAndGenerateParentInitialisationCodeBlock(currentCodeBlockInTree, subjectEntity, sentenceIndex, true, false);	//parseConditionParents was previously set false in original implementation [although the GIA specification supports such arrangements, in practice however they probably can't be generated as x will always be a condition subject not a condition object of y in "x is near the y"]
				}
				if(actionHasObject)
				{
					getParentAndGenerateParentInitialisationCodeBlock(currentCodeBlockInTree, objectEntity, sentenceIndex, true, false);	//parseConditionParents was previously set false in original implementation [although the GIA specification supports such arrangements, in practice however they probably can't be generated as x will always be a condition subject not a condition object of y in "x is near the y"]
				}
				#endif

			}

			NLCgenerateContextBlocksVariables generateContextBlocksVariables;
			generateContextBlocksVariables.onlyGenerateContextBlocksIfConnectionsParsedForNLCorSameReferenceSet = true;

			if(actionHasObject)
			{
				#ifdef NLC_FUNCTIONS_SUPPORT_PLURAL_OBJECTS
				#ifdef NLC_FUNCTIONS_SUPPORT_PLURAL_OBJECTS_ENTER_GENERATED_CATEGORY_LIST
				generateContextBlocksVariables.enterGeneratedCategoryList = true;	//is required for createCodeBlockUpdateLastSentenceReferenced()
				NLCcodeblock* codeBlockInTreeBeforeParseContext = *currentCodeBlockInTree;
				#else
				generateContextBlocksVariables.enterGeneratedCategoryList = false;
				#endif
				#endif
				GIAentityNode* parentEntityFunctionObject = NULL;
				if(getParentAndInitialiseParentIfNecessaryOrGenerateContextBlocks(currentCodeBlockInTree, objectEntity, sentenceIndex, &generateContextBlocksVariables, false, &parentEntityFunctionObject, true))	//parseConditionParents was previously set false in original implementation [although the GIA specification supports such arrangements, in practice however they probably can't be generated as x will always be a condition subject not a condition object of y in "x is near the y"]
				{
					#ifdef NLC_DEBUG
					//cout << "actionHasObject: parent and its children initialised" << endl;
					#endif
				}
				#ifdef NLC_USE_LIBRARY_FROM_CONDITIONS
				if(parentEntityFunctionObject != objectEntity)
				{
					//*currentCodeBlockInTree = createCodeBlockSetTempVariable(*currentCodeBlockInTree, NLC_USE_LIBRARY_MOVE_FUNCTION_ACTIONOBJECT_PARENT_TEMP_VARIABLE_NAME, parentEntityFunctionObject);
					GIAentityNode* parentEntityFromCondition = new GIAentityNode();
					parentEntityFromCondition->entityName = NLC_USE_LIBRARY_MOVE_FUNCTION_ACTION_CONDITION_FROM_NAME;
					addOrConnectConditionToEntity(actionEntity, parentEntityFunctionObject, parentEntityFromCondition, false);	//this is required so that generateClassHeirarchyFunctions() adds the "from" condition to the action, but need to check that GIA supports NLC's use of the addOrConnectConditionToEntity() function
					*currentCodeBlockInTree = createCodeBlockAddNewConditionExistingObjectSimple(*currentCodeBlockInTree, actionEntity, parentEntityFromCondition, parentEntityFunctionObject);
				}
				#endif

				#ifdef NLC_RECORD_ACTION_HISTORY
				*currentCodeBlockInTree = createCodeBlockRecordHistoryActionObject(*currentCodeBlockInTree, actionEntity, objectEntity);
				#endif

				#ifdef NLC_FUNCTIONS_SUPPORT_PLURAL_OBJECTS
				#ifdef NLC_FUNCTIONS_SUPPORT_PLURAL_OBJECTS_ENTER_GENERATED_CATEGORY_LIST
				*currentCodeBlockInTree = getLastCodeBlockInLevel(codeBlockInTreeBeforeParseContext);
				#endif
				#endif

				NLCitem* functionSubjectItem = NULL;
				if(actionHasSubject)
				{
					#ifdef NLC_FUNCTIONS_SUPPORT_PLURAL_SUBJECTS
					#ifdef NLC_FUNCTIONS_SUPPORT_PLURAL_SUBJECTS_ENTER_GENERATED_CATEGORY_LIST
					generateContextBlocksVariables.enterGeneratedCategoryList = true;	//is required for createCodeBlockUpdateLastSentenceReferenced()
					codeBlockInTreeBeforeParseContext = *currentCodeBlockInTree;
					#else
					generateContextBlocksVariables.enterGeneratedCategoryList = false;	
					#endif
					#endif
					GIAentityNode* parentEntityFunctionSubject = NULL;
					if(getParentAndInitialiseParentIfNecessaryOrGenerateContextBlocks(currentCodeBlockInTree, subjectEntity, sentenceIndex, &generateContextBlocksVariables, false, &parentEntityFunctionSubject, true))	//parseConditionParents was previously set false in original implementation [although the GIA specification supports such arrangements, in practice however they probably can't be generated as x will always be a condition subject not a condition object of y in "x is near the y"]
					{
						#ifdef NLC_DEBUG
						//cout << "actionHasSubject2: parent and its children initialised" << endl;
						#endif
					}

					#ifdef NLC_RECORD_ACTION_HISTORY
					*currentCodeBlockInTree = createCodeBlockRecordHistoryActionSubject(*currentCodeBlockInTree, actionEntity, subjectEntity);
					#endif

					#ifdef NLC_FUNCTIONS_SUPPORT_PLURAL_SUBJECTS
					#ifdef NLC_FUNCTIONS_SUPPORT_PLURAL_SUBJECTS_ENTER_GENERATED_CATEGORY_LIST
					*currentCodeBlockInTree = getLastCodeBlockInLevel(codeBlockInTreeBeforeParseContext);
					#endif
					#endif

					functionExecuteCodeBlockInTree = *currentCodeBlockInTree;
					#ifdef NLC_RECORD_ACTION_HISTORY_GENERALISABLE_DO_NOT_EXECUTE_PAST_TENSE_ACTIONS
					if(!isNonImmediateAction(actionEntity))
					{
					#endif
						*currentCodeBlockInTree = createCodeBlockExecuteSubjectObject(*currentCodeBlockInTree, actionEntity, subjectEntity, objectEntity);
					#ifdef NLC_RECORD_ACTION_HISTORY_GENERALISABLE_DO_NOT_EXECUTE_PAST_TENSE_ACTIONS
					}
					#endif

					//subjectEntity->parsedForNLCcodeBlocksActionRound = true;
				}
				else
				{
					functionExecuteCodeBlockInTree = *currentCodeBlockInTree;
					#ifdef NLC_RECORD_ACTION_HISTORY_GENERALISABLE_DO_NOT_EXECUTE_PAST_TENSE_ACTIONS
					if(!isNonImmediateAction(actionEntity))
					{
					#endif
						*currentCodeBlockInTree = createCodeBlockExecuteObject(*currentCodeBlockInTree, actionEntity, objectEntity);
					#ifdef NLC_RECORD_ACTION_HISTORY_GENERALISABLE_DO_NOT_EXECUTE_PAST_TENSE_ACTIONS
					}
					#endif
				}

				actionEntity->NLCparsedForCodeBlocks = true;
				//actionEntity->parsedForNLCcodeBlocksActionRound = true;
				//objectEntity->parsedForNLCcodeBlocksActionRound = true;
			}
			else if(actionHasSubject)
			{
				#ifdef NLC_FUNCTIONS_SUPPORT_PLURAL_SUBJECTS
				#ifdef NLC_FUNCTIONS_SUPPORT_PLURAL_SUBJECTS_ENTER_GENERATED_CATEGORY_LIST
				generateContextBlocksVariables.enterGeneratedCategoryList = true;	//is required for createCodeBlockUpdateLastSentenceReferenced()
				NLCcodeblock* codeBlockInTreeBeforeParseContext = *currentCodeBlockInTree;
				#else
				generateContextBlocksVariables.enterGeneratedCategoryList = false;	
				#endif
				#endif
				GIAentityNode* parentEntityFunctionSubject = NULL;
				if(getParentAndInitialiseParentIfNecessaryOrGenerateContextBlocks(currentCodeBlockInTree, subjectEntity, sentenceIndex, &generateContextBlocksVariables, false, &parentEntityFunctionSubject, true))	//parseConditionParents was previously set false in original implementation [although the GIA specification supports such arrangements, in practice however they probably can't be generated as x will always be a condition subject not a condition object of y in "x is near the y"]
				{
					#ifdef NLC_DEBUG
					//cout << "actionHasSubject: parent and its children initialised" << endl;
					#endif
				}

				#ifdef NLC_RECORD_ACTION_HISTORY
				*currentCodeBlockInTree = createCodeBlockRecordHistoryActionSubject(*currentCodeBlockInTree, actionEntity, subjectEntity);
				#endif

				#ifdef NLC_FUNCTIONS_SUPPORT_PLURAL_SUBJECTS
				#ifdef NLC_FUNCTIONS_SUPPORT_PLURAL_SUBJECTS_ENTER_GENERATED_CATEGORY_LIST
				*currentCodeBlockInTree = getLastCodeBlockInLevel(codeBlockInTreeBeforeParseContext);	
				#endif
				#endif

				functionExecuteCodeBlockInTree = *currentCodeBlockInTree;
				#ifdef NLC_RECORD_ACTION_HISTORY_GENERALISABLE_DO_NOT_EXECUTE_PAST_TENSE_ACTIONS
				if(!isNonImmediateAction(actionEntity))
				{
				#endif
					*currentCodeBlockInTree = createCodeBlockExecuteSubject(*currentCodeBlockInTree, actionEntity, subjectEntity);
				#ifdef NLC_RECORD_ACTION_HISTORY_GENERALISABLE_DO_NOT_EXECUTE_PAST_TENSE_ACTIONS
				}
				#endif
				actionEntity->NLCparsedForCodeBlocks = true;
				//actionEntity->parsedForNLCcodeBlocksActionRound = true;
				//subjectEntity->parsedForNLCcodeBlocksActionRound = true;
			}
			#ifdef NLC_PREPROCESSOR_INTERPRET_SINGLE_WORD_SENTENCES_AS_ACTIONS
			else if(actionIsSingleWord)
			{
				functionExecuteCodeBlockInTree = *currentCodeBlockInTree;
				*currentCodeBlockInTree = createCodeBlockExecute(*currentCodeBlockInTree, actionEntity);

				actionEntity->NLCparsedForCodeBlocks = true;	
			}
			#endif

			#ifdef NLC_INTERPRET_ACTION_PROPERTIES_AND_CONDITIONS_AS_FUNCTION_ARGUMENTS
			if(actionHasObject || actionHasSubject || actionIsSingleWord)
			{
				#ifndef NLC_SUPPORT_INPUT_FILE_LISTS
				generateFunctionDeclarationArgumentsWithActionConceptInheritance(actionEntity, &(functionExecuteCodeBlockInTree->parameters));	//#ifdef NLC_SUPPORT_INPUT_FILE_LISTS use class definition parameters instead
				#endif

				//detect action properties and conditions (and disable these for NLC generate code block parse: they will become function execution arguments)
				for(vector<GIAentityConnection*>::iterator entityIter = actionEntity->conditionNodeList->begin(); entityIter != actionEntity->conditionNodeList->end(); entityIter++)
				{
					GIAentityNode* actionCondition = (*entityIter)->entity;
					(*entityIter)->NLCparsedForCodeBlocks = true;
					actionCondition->NLCparsedForCodeBlocks = true;
				}
				for(vector<GIAentityConnection*>::iterator entityIter = actionEntity->propertyNodeList->begin(); entityIter != actionEntity->propertyNodeList->end(); entityIter++)
				{
					GIAentityNode* actionProperty = (*entityIter)->entity;
					(*entityIter)->NLCparsedForCodeBlocks = true;
					actionProperty->NLCparsedForCodeBlocks = true;
				}
			}
			#endif
		#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
		}
		#endif
	#ifdef NLC_RECORD_ACTION_HISTORY_GENERALISABLE_DO_NOT_EXECUTE_PAST_TENSE_ACTIONS
	}
	#endif
	
	*currentCodeBlockInTree = getLastCodeBlockInLevel(firstCodeBlockInSentence);
}

#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS
void initialiseFunctionArguments(NLCcodeblock** currentCodeBlockInTree, GIAentityNode* actionEntity, int sentenceIndex)
{
	actionEntity->NLCisSingularArgument = true;	//added 1e2c

	//declare an "abstract" variable for the action (that will be filled with the its properties and conditions) and passed as an argument to the function; eg "fast" of "run fast"
	if(!generateParentInitialisationCodeBlock(currentCodeBlockInTree, actionEntity, sentenceIndex))
	{
		
	}
}
#endif



//added recursion 1e8a
//onlyGenerateContextBlocksIfContextNotGeneratedForNLC removed 1i3b

bool generateObjectInitialisationsBasedOnPropertiesAndConditions(GIAentityNode* entity, NLCcodeblock** currentCodeBlockInTree, int sentenceIndex, GIAentityNode* parentEntity, string parentConditionName, bool generateParentContextTopLevel, bool generateParentContextPassThrough)
{
	string parentName = "";
	if(parentEntity != NULL)
	{
		parentName = generateInstanceName(parentEntity);
	}
	
	#ifdef NLC_DEBUG
	//cout << "generateObjectInitialisationsBasedOnPropertiesAndConditions(): entity = " << entity->entityName << endl;
	//cout << "parentName = " << parentName << endl;
	#endif
				
	#ifdef NLC_DEBUG_PARSE_CONTEXT3
	string generateParentContextStringTemp = "false";
	if(generateParentContextTopLevel)
	{
		generateParentContextStringTemp = "true";
	}
	*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("generateObjectInitialisationsBasedOnPropertiesAndConditions(): ") + entity->entityName + ", generateParentContextTopLevel = " + generateParentContextStringTemp);
	#endif

	#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
	//new implementation: only create context for parent (ie for parent entities...) at start of each generateObjectInitialisationsBasedOnPropertiesAndConditions() if a, b or c;
	//a) first call to generateObjectInitialisationsBasedOnPropertiesAndConditions;
	//added 1i8a->1i8c, moved 1i11d
	if(generateParentContextTopLevel)
	{	
		#ifdef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES	//ie #ifndef NLC_USE_ADVANCED_REFERENCING
		if(!(entity->isSubstanceQuality))	//this is required because referenced entities may have a connection to a parent defined in a preceeding sentence, yet generateObjectInitialisationsBasedOnPropertiesAndConditions is still executed on these entities (because they are tagged as wasReference and are accepted by checkSentenceIndexParsingCodeBlocks themselves)
		{
		#endif	
			#ifdef NLC_DEBUG_PARSE_CONTEXT3
			*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("generateObjectInitialisationsBasedOnPropertiesAndConditions(): a) generateContextForChildEntity(): ") + entity->entityName);
			#endif
			
			#ifdef NLC_DEBUG
			cout << "generateObjectInitialisationsBasedOnPropertiesAndConditions(): a) generateContextForChildEntity(): " << entity->entityName << endl;
			#endif
		
			if(generateContextForChildEntity(currentCodeBlockInTree, NULL, entity, sentenceIndex, true))
			{
				//cout << "generateContextForChildEntity pass: entity = " << entity->entityName << endl;
			}
			#ifdef NLC_RECORD_ACTION_HISTORY_COMPENSATE_FOR_EFFECTIVE_DEFINITE_ENTITIES_IMPLEMENTATION	//CHECKTHIS
			#ifndef NLC_RECORD_ACTION_HISTORY_COMPENSATE_FOR_EFFECTIVE_DEFINITE_ENTITIES_IMPLEMENTATION2
			else
			{
				#ifdef NLC_RECORD_ACTION_HISTORY
				if(!(entity->NLCcontextGenerated))	//e.g. must perform this check because "a pie" in "The chicken that ate a pie rows the boat." will not be initialised by generateParentInitialisationCodeBlockWithChecks() [and will remain undeclared] because its context will be parsed by generateActionCodeBlocks() when it is translating "the chicken... rows the boat" [a product of "that ate a pie" being in the same reference set as row action subject "chicken"] 
				{	
				#endif
					cout << "\t\t generateObjectInitialisationsBasedOnPropertiesAndConditions() error: generateParentContextTopLevel && !assumedToAlreadyHaveBeenDeclared: entity = " << entity->entityName << ", sentenceIndex = " << sentenceIndex << endl;
					cout << "\t\t sentenceIndex = " << sentenceIndex << endl; 
					exit(0);
				#ifdef NLC_RECORD_ACTION_HISTORY
				}
				#endif
			}
			#endif
			#endif
		#ifdef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES	//ie #ifndef NLC_USE_ADVANCED_REFERENCING
		}
		else
		{
			/*
			eg 1 A red dog rides a bike. Tom is the red Dog. Tom is happy.
			eg 2 A yellow banana is on the table. The yellow banana is a fruit. Apples are fruit. An apple is on the green tree. The yellow fruit is tasty.
			*/		
		}
		#endif
	}
	
	#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN
	if(generateParentContextPassThrough)
	{
		//b) the previous level call generateObjectInitialisationsBasedOnPropertiesAndConditions resulted in parsing sameReferenceSet connnections without the creation of a new property/conditionObject (pass through);
		//added 1i11l, moved 1l8b (fixed context 1l8i)
		//eg Tom's apple is blue.
		#ifdef NLC_DEBUG
		cout << "generateObjectInitialisationsBasedOnPropertiesAndConditions(): b) createCodeBlockForPropertyList: " << entity->entityName << endl;
		#endif
		
		*currentCodeBlockInTree = createCodeBlockForOrInPropertyList(*currentCodeBlockInTree, entity, parentName);

		//eg Tom's bright apple is blue.
		//generateContextBlocks(currentCodeBlockInTree, entity, sentenceIndex, &generateContextBlocksVariables);
		//parse the children (properties and conditions) of an undeclared definite parent
		NLCgenerateContextBlocksVariables generateContextBlocksVariables;
		generateContextBlocksVariables.onlyGenerateContextBlocksIfConnectionsParsedForNLCorSameReferenceSet = true;
		createCodeBlockForStatements(currentCodeBlockInTree, generateInstanceName(entity), entity, sentenceIndex, &generateContextBlocksVariables);		//added 1i11n
		
		#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_FOR_EACH_CHILD_GET_PARENT_ORIGINAL_IMPLEMENTATION	
		#ifndef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES
		if(!assumedToAlreadyHaveBeenDeclared(entity))	//is this necessary?
		{	
			//eg Tom's boat is red. Jack is near the red boat.
			addIntermediaryImplicitlyDeclaredEntityToLocalList(currentCodeBlockInTree, entity);
		}
		#endif
		#endif
	}
	else
	{
	#endif
		//c) the previous level call generateObjectInitialisationsBasedOnPropertiesAndConditions resulted in the creation of a new property/conditionObject (its context has not yet been generated);
		if(!(entity->NLCcontextGenerated))
		{//context block already created by generateContextBlocks()	//added 1g14b 15-July-2014
			if(!(entity->isSubstanceQuality))	//added 1l6f - ignore qualities as they will not have NLClocalListVariableHasBeenInitialised set when they were added as a property, because they will not have NLClocalListVariableHasBeenDeclared set - see declareLocalPropertyListsForIndefiniteEntities()
			{
				if(assumedToAlreadyHaveBeenDeclared(entity))
				{
					#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_BLOCKS_FOR_PARENT_INITIALISATION_SPECIAL
					#ifdef NLC_DEBUG
					cout << "generateObjectInitialisationsBasedOnPropertiesAndConditions(): c) createCodeBlockForCategoryList(): " << entity->entityName << endl;
					#endif
					#ifdef NLC_DEBUG_PARSE_CONTEXT2
					*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("generateObjectInitialisationsBasedOnPropertiesAndConditions(): c) createCodeBlockForCategoryList: ") + entity->entityName);
					#endif
					*currentCodeBlockInTree = createCodeBlockForCategoryList(*currentCodeBlockInTree, entity, NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION);
					entity->NLCcontextGenerated = true;	//is this required?
					#else
					#ifdef NLC_DEBUG
					cout << "generateObjectInitialisationsBasedOnPropertiesAndConditions(): c) createCodeBlockForLocalList(): " << entity->entityName << endl;
					#endif
					#ifdef NLC_DEBUG_PARSE_CONTEXT2
					*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("generateObjectInitialisationsBasedOnPropertiesAndConditions(): c) createCodeBlockForLocalList: ") + entity->entityName);
					#endif
					*currentCodeBlockInTree = createCodeBlockForLocalList(*currentCodeBlockInTree, entity);
					#endif
				}
				#ifdef NLC_DEFINE_LOCAL_VARIABLES_FOR_ALL_INDEFINATE_ENTITIES
				else
				{
					cout << "generateObjectInitialisationsBasedOnPropertiesAndConditions() error: !(entity->NLCcontextGenerated) && !assumedToAlreadyHaveBeenDeclared: entity = " << entity->entityName  << ", sentenceIndex = " << sentenceIndex << endl;
					cout << "NB it is possible a substance concept has been defined as a property of a non-substance concept entity, eg 'The pies near the house have red cars.' instead of 'The pies near the house have some red cars.'/'The pies near the house has 7 red cars.'" << endl;
						//NB this possibility can be corrected for with checkSpecialCaseEntity() check for substance concepts
					//OLD: corrected for with NLC_DEFINE_LOCAL_VARIABLES_FOR_ALL_INDEFINATE_ENTITIES condition; cout << "NB it is also possible that NLC_DEFINE_LOCAL_VARIABLES_FOR_ALL_INDEFINATE_ENTITIES has been disabled: (if !isSubstanceQuality) NLClocalListVariableHasBeenInitialised must be set when variables are added as a property" << endl;
				}
				#endif
			}
		}
	#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN
	}
	#endif
	#else
	//old implementation: always create context for parent at start of each call to generateObjectInitialisationsBasedOnPropertiesAndConditions() - this is a simpler implementation however it does not handle the case in which the previous child has already have had its context generated
	if(assumedToAlreadyHaveBeenDeclared(entity))
	{
		#ifdef NLC_DEBUG_PARSE_CONTEXT2
		*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("generateObjectInitialisationsBasedOnPropertiesAndConditions(): old implementation: createCodeBlockForPropertyListLocal: ") + entity->entityName);
		#endif
		*currentCodeBlockInTree = createCodeBlockForLocalList(*currentCodeBlockInTree, entity);
	}	
	else
	{
		#ifdef NLC_DEBUG_PARSE_CONTEXT2
		*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("generateObjectInitialisationsBasedOnPropertiesAndConditions(): old implementation: createCodeBlockForPropertyList: ") + entity->entityName);
		#endif

		entityClass->context.push_back(parentName);
		*currentCodeBlockInTree = createCodeBlockForPropertyList(*currentCodeBlockInTree, entity);
	}
	#endif
	
	#ifdef NLC_DEBUG_PARSE_CONTEXT2
	*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("generateObjectInitialisationsBasedOnPropertiesAndConditions finished parsing parent entity: ") + entity->entityName);
	#endif
					
	bool performedAtLeastOneObjectInitialisation = false;
	if(!checkSpecialCaseEntity(entity, false))
	{
		//property initialisations
		for(vector<GIAentityConnection*>::iterator propertyNodeListIterator = entity->propertyNodeList->begin(); propertyNodeListIterator < entity->propertyNodeList->end(); propertyNodeListIterator++)
		{
			GIAentityConnection* propertyConnection = (*propertyNodeListIterator);
			GIAentityNode* propertyEntity = propertyConnection->entity;
			#ifdef NLC_DEBUG
			cout << "\t\tpropertyConnection->sentenceIndexTemp = " << propertyConnection->sentenceIndexTemp << endl;
			#endif

			#ifdef NLC_VERIFY_CONNECTIONS_SENTENCE_INDEX
			if((checkSentenceIndexParsingCodeBlocks(propertyEntity, sentenceIndex, false) || propertyEntity->NLCparsedForCodeBlocks) && (propertyConnection->sentenceIndexTemp == sentenceIndex))
			#else
			if((checkSentenceIndexParsingCodeBlocks(propertyEntity, sentenceIndex, false) || propertyEntity->NLCparsedForCodeBlocks))			
			#endif
			{//only write properties that are explicated in current sentence

				bool newlyDeclaredEntityInCategoryList2 = false;
				bool performedAtLeastOneObjectInitialisationAtThisLevel = false;
				NLCcodeblock* firstCodeBlockInSection = *currentCodeBlockInTree;

				bool generatedContextForChild = generateContextForChildEntity(currentCodeBlockInTree, entity, propertyEntity, sentenceIndex, false);
				bool passThrough = !generatedContextForChild;
				
				if(!(propertyConnection->NLCparsedForCodeBlocks))
				{					
					#ifdef NLC_TRANSLATE_NEGATIVE_PROPERTIES_AND_CONDITIONS
					if(propertyConnection->negative || (propertyEntity->isSubstanceQuality && propertyEntity->negative))
					{
						#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS
						if(assumedToAlreadyHaveBeenDeclared(propertyEntity))
						{
							#ifdef NLC_DEBUG_PARSE_CONTEXT2
							*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("generateObjectInitialisationsBasedOnPropertiesAndConditions(): 3createCodeBlockRemoveProperties: ") + entity->entityName + string(" ") + propertyEntity->entityName);
							#endif
							#ifdef NLC_DEBUG
							cout << "createCodeBlockRemoveProperties: " << entity->entityName << ", " << propertyEntity->entityName << endl;
							#endif

							NLCitem* propertyClass = new NLCitem(propertyEntity, NLC_ITEM_TYPE_OBJECT);
							//*currentCodeBlockInTree = createCodeBlockRemoveEntitiesFromLocalList(*currentCodeBlockInTree, propertyEntity);	//removed 1m1f
							*currentCodeBlockInTree = createCodeBlockRemoveProperties(*currentCodeBlockInTree, entity, propertyEntity);
						}
						else
						{
						#endif
							//remove properties; eg "a ball" in "Tom does not have a ball."
							#ifdef NLC_DEBUG_PARSE_CONTEXT2
							*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("generateObjectInitialisationsBasedOnPropertiesAndConditions():  4createCodeBlockRemoveProperties: ") + entity->entityName + string(" ") + propertyEntity->entityName);
							#endif
							#ifdef NLC_DEBUG
							cout << "createCodeBlockRemoveProperties: " << entity->entityName << ", " << propertyEntity->entityName << endl;
							#endif

							*currentCodeBlockInTree = createCodeBlockRemoveProperties(*currentCodeBlockInTree, entity, propertyEntity);
						#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS
						}
						#endif
					}
					else
					{
					#endif
						#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS
						if(assumedToAlreadyHaveBeenDeclared(propertyEntity))
						{
							//use function argument PropertyList (do not create a new property); eg "the ball" in "Tom has the ball"
							#ifdef NLC_DEBUG_PARSE_CONTEXT2
							*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("generateObjectInitialisationsBasedOnPropertiesAndConditions(): 3createCodeBlockAddProperty: ") + entity->entityName + string(" ") + convertIntToString(entity->NLClocalListVariableHasBeenInitialised) + string(" ") + propertyEntity->entityName + string(" ") + convertIntToString(propertyEntity->NLClocalListVariableHasBeenInitialised));
							#endif
							#ifdef NLC_DEBUG
							cout << "createCodeBlockAddProperty: " << entity->entityName << ", " << propertyEntity->entityName << endl;
							#endif

							#ifndef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_FOR_EACH_CHILD
							NLCcodeblock* firstCodeBlockInSection2 = *currentCodeBlockInTree;
							NLCitem* propertyClass = new NLCitem(propertyEntity, NLC_ITEM_TYPE_OBJECT);
							*currentCodeBlockInTree = createCodeBlockForLocalList(*currentCodeBlockInTree, propertyClass);
							#endif

							*currentCodeBlockInTree = createCodeBlockAddProperty(*currentCodeBlockInTree, entity, propertyEntity, sentenceIndex);

							#ifndef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_FOR_EACH_CHILD
							*currentCodeBlockInTree = firstCodeBlockInSection2->next;
							#endif
						}
						else
						{
						#endif
							//create a new property; eg "a ball" in "Tom has a ball"
							#ifdef NLC_DEBUG_PARSE_CONTEXT2
							*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("generateObjectInitialisationsBasedOnPropertiesAndConditions(): 4createCodeBlockAddNewProperty: ") + entity->entityName + string(" ") + propertyEntity->entityName);
							#endif
							#ifdef NLC_DEBUG
							cout << "createCodeBlockAddNewProperty: " << entity->entityName << ", " << propertyEntity->entityName << endl;
							#endif

							newlyDeclaredEntityInCategoryList2 = true;
							*currentCodeBlockInTree = createCodeBlockCreateNewProperty(*currentCodeBlockInTree, entity, propertyEntity, sentenceIndex, true);

						#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS
						}
						#endif

						#ifdef GIA_TRANSLATOR_DREAM_MODE_LINK_SPECIFIC_CONCEPTS_AND_ACTIONS
						//moved 1e1b: only generate object initialisations for items based on subject concepts when items are created in context
						//Part 2b: generate object initialisations based on substance concepts (class inheritance)
						generateObjectInitialisationsBasedOnSubstanceConcepts(propertyEntity, currentCodeBlockInTree, sentenceIndex, newlyDeclaredEntityInCategoryList2);
						#endif
					#ifdef NLC_TRANSLATE_NEGATIVE_PROPERTIES_AND_CONDITIONS
					}
					#endif

					#ifdef NLC_DEBUG
					cout << "generateObjectInitialisationsBasedOnPropertiesAndConditions():" << endl;
					cout << "entity->entityName = " << entity->entityName << endl;
					cout << "propertyEntity->entityName = " << propertyEntity->entityName << endl;
					#endif

					propertyConnection->NLCparsedForCodeBlocks = true;
					propertyEntity->NLCparsedForCodeBlocks = true;		//added 3 October 2013 NLC1b2b - used for quick access of instances already declared in current context

					performedAtLeastOneObjectInitialisationAtThisLevel = true;
					
					passThrough = false;	//added 1l8b
				}

				NLCcodeblock* firstCodeBlockBeforeRecursion = *currentCodeBlockInTree;
				bool performedAtLeastOneObjectInitialisationAtALowerLevel = generateObjectInitialisationsBasedOnPropertiesAndConditions(propertyEntity, currentCodeBlockInTree, sentenceIndex, entity, "", false, passThrough);
				#ifdef NLC_DEBUG
				cout << "performedAtLeastOneObjectInitialisationAtALowerLevel = " << performedAtLeastOneObjectInitialisationAtALowerLevel << endl;
				#endif
				generateObjectInitialisationsBasedOnPropertiesAndConditionsUpdateCodeBlockPointer(currentCodeBlockInTree, firstCodeBlockBeforeRecursion, firstCodeBlockInSection, performedAtLeastOneObjectInitialisationAtThisLevel, performedAtLeastOneObjectInitialisationAtALowerLevel, &performedAtLeastOneObjectInitialisation);
			}
		}

		#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS_ADVANCED
		//added NLC 1g5e:
		if(!(entity->isCondition))
		{//do not parse conditions of conditions as one of the conditions is a logical condition conjunction (ie and/or)
		#endif
			//state initialisations
			for(vector<GIAentityConnection*>::iterator conditionNodeListIterator = entity->conditionNodeList->begin(); conditionNodeListIterator < entity->conditionNodeList->end(); conditionNodeListIterator++)
			{
				GIAentityConnection* conditionConnection = (*conditionNodeListIterator);
				GIAentityNode* conditionEntity = conditionConnection->entity;

				#ifdef NLC_NORMALISE_TWOWAY_PREPOSITIONS_DUAL_CONDITION_LINKS_ENABLED
				if(!(conditionEntity->inverseConditionTwoWay) || conditionConnection->isReference)	//prevent infinite loop for 2 way conditions 
				{
				#endif
					#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
					if(!(conditionEntity->NLClogicalConditionOperation))		//if(!(conditionConnection->NLCparsedForlogicalConditionOperations) && !(conditionEntity->NLCparsedForlogicalConditionOperations))	//this alternative test would require "tagAllEntitiesInSentenceSubsetAsPertainingToLogicalConditionOperationAdvanced(conditionSubject, sentenceIndex, false);" to be called before "generateObjectInitialisationsBasedOnPropertiesAndConditions()"
					{
					#endif
						bool foundConditionObject = false;
						GIAentityNode* conditionObject = NULL;
						if(!(conditionEntity->conditionObjectEntity->empty()))
						{
							conditionObject = (conditionEntity->conditionObjectEntity->back())->entity;
							foundConditionObject = true;

							#ifdef NLC_VERIFY_CONNECTIONS_SENTENCE_INDEX
							if((checkSentenceIndexParsingCodeBlocks(conditionEntity, sentenceIndex, false) || conditionEntity->NLCparsedForCodeBlocks) && (conditionConnection->sentenceIndexTemp == sentenceIndex))
							#else
							if((checkSentenceIndexParsingCodeBlocks(conditionEntity, sentenceIndex, false) || conditionEntity->NLCparsedForCodeBlocks))
							#endif
							{//only write conditions that are explicated in current sentence

								bool newlyDeclaredEntityInCategoryList2 = false;
								bool performedAtLeastOneObjectInitialisationAtThisLevel = false;
								NLCcodeblock* firstCodeBlockInSection = *currentCodeBlockInTree;

								NLCitem* entityClass = new NLCitem(entity, NLC_ITEM_TYPE_OBJECT);
								NLCitem* conditionObjectClass = new NLCitem(conditionObject, NLC_ITEM_TYPE_OBJECT);

								bool generatedContextForChild = generateContextForChildEntity(currentCodeBlockInTree, entity, conditionObject, sentenceIndex, true);
								bool passThrough = !generatedContextForChild;

								if(!(conditionConnection->NLCparsedForCodeBlocks))
								{
									#ifdef NLC_NORMALISE_TWOWAY_PREPOSITIONS
									GIAentityNode* entityInverse = conditionObject;
									GIAentityNode* conditionEntityInverse = NULL;
									if(conditionEntity->conditionTwoWay)
									{
										conditionEntityInverse = generateInverseConditionEntity(conditionEntity);
										#ifdef NLC_DEBUG
										cout << "conditionEntityInverse: conditionEntity = " << conditionEntity->entityName << endl;
										#endif
									}
									#endif

									#ifdef NLC_TRANSLATE_NEGATIVE_PROPERTIES_AND_CONDITIONS
									if(conditionEntity->negative)
									{
										#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS
										if(assumedToAlreadyHaveBeenDeclared(conditionObject))
										{
											#ifdef NLC_DEBUG_PARSE_CONTEXT2
											*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("generateObjectInitialisationsBasedOnPropertiesAndConditions(): 3BcreateCodeBlockRemoveConditions: ") + entity->entityName + string(" ") + conditionEntity->entityName);
											#endif

											//*currentCodeBlockInTree = createCodeBlockRemoveEntitiesFromLocalList(*currentCodeBlockInTree, conditionObject);	//removed 1m1f
											*currentCodeBlockInTree = createCodeBlockRemoveConditions(*currentCodeBlockInTree, entity, conditionEntity);
										}
										else
										{
										#endif
											#ifdef NLC_DEBUG_PARSE_CONTEXT2
											*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("generateObjectInitialisationsBasedOnPropertiesAndConditions():  4BcreateCodeBlockRemoveProperties: ") + entity->entityName + string(" ") + conditionEntity->entityName);
											#endif

											*currentCodeBlockInTree = createCodeBlockRemoveConditions(*currentCodeBlockInTree, entity, conditionEntity);
										#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS
										}
										#endif
									}
									else
									{
									#endif
										#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS
										if(assumedToAlreadyHaveBeenDeclared(conditionObject))
										{
											//use function argument PropertyList (do not create a new property to insert into condition); eg "the house" in "Tom is near a house"

											#ifdef NLC_DEBUG_PARSE_CONTEXT2
											*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("generateObjectInitialisationsBasedOnPropertiesAndConditions(): 3BcreateCodeBlockCondition: ") + entity->entityName + string(" ") + convertIntToString(entity->NLClocalListVariableHasBeenInitialised) + string(" ") + conditionObject->entityName + string(" ") + convertIntToString(conditionObject->NLClocalListVariableHasBeenInitialised));
											#endif

											#ifndef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_FOR_EACH_CHILD
											NLCcodeblock* firstCodeBlockInSection2 = *currentCodeBlockInTree;
											*currentCodeBlockInTree = createCodeBlockForLocalList(*currentCodeBlockInTree, conditionObjectClass);
											#endif

											*currentCodeBlockInTree = createCodeBlockAddCondition(*currentCodeBlockInTree, entity, conditionEntity, sentenceIndex);

											#ifndef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_FOR_EACH_CHILD
											*currentCodeBlockInTree = firstCodeBlockInSection2->next;
											#endif
										}
										else
										{
										#endif
											#ifdef NLC_DEBUG_PARSE_CONTEXT2
											*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("generateObjectInitialisationsBasedOnPropertiesAndConditions(): 4BcreateCodeBlockAddNewCondition: ") + entity->entityName + string(" ") + conditionObject->entityName);
											#endif

											//create a new condition; eg "a house" in "Tom is near a house"
											newlyDeclaredEntityInCategoryList2 = true;
											*currentCodeBlockInTree = createCodeBlockCreateNewCondition(*currentCodeBlockInTree, entity, conditionEntity, sentenceIndex, true);

										#ifdef NLC_DERIVE_LOCAL_FUNCTION_ARGUMENTS_BASED_ON_IMPLICIT_DECLARATIONS
										}
										#endif

										#ifdef GIA_TRANSLATOR_DREAM_MODE_LINK_SPECIFIC_CONCEPTS_AND_ACTIONS
										//moved 1e1b: only generate object initialisations for items based on subject concepts when items are created in context
										//Part 2b: generate object initialisations based on substance concepts (class inheritance)
										generateObjectInitialisationsBasedOnSubstanceConcepts(conditionEntity, currentCodeBlockInTree, sentenceIndex, newlyDeclaredEntityInCategoryList2);
										#endif
									#ifdef NLC_TRANSLATE_NEGATIVE_PROPERTIES_AND_CONDITIONS
									}
									#endif

									conditionConnection->NLCparsedForCodeBlocks = true;
									conditionEntity->NLCparsedForCodeBlocks = true;	//added NLC 1b2b/3 October 2013 - used for quick access of instances already declared in current context
									conditionObject->NLCparsedForCodeBlocks = true;	//added 1e6d

									performedAtLeastOneObjectInitialisationAtThisLevel = true;

									passThrough = false;	//added 1l8b
								}

								NLCcodeblock* firstCodeBlockBeforeRecursion = *currentCodeBlockInTree;
								bool performedAtLeastOneObjectInitialisationAtALowerLevel = generateObjectInitialisationsBasedOnPropertiesAndConditions(conditionObject, currentCodeBlockInTree, sentenceIndex, entity, conditionEntity->entityName, false, passThrough);

								generateObjectInitialisationsBasedOnPropertiesAndConditionsUpdateCodeBlockPointer(currentCodeBlockInTree, firstCodeBlockBeforeRecursion, firstCodeBlockInSection, performedAtLeastOneObjectInitialisationAtThisLevel, performedAtLeastOneObjectInitialisationAtALowerLevel, &performedAtLeastOneObjectInitialisation);
							}
						}
						else
						{
							//no condition object
						}
					#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED
					}
					#endif
				#ifdef NLC_NORMALISE_TWOWAY_PREPOSITIONS_DUAL_CONDITION_LINKS_ENABLED
				}
				#endif
			}
		#ifdef NLC_SUPPORT_LOGICAL_CONDITION_OPERATIONS_ADVANCED_CONJUNCTIONS_ADVANCED
		}
		#endif
	}
	
	//cout << "performedAtLeastOneObjectInitialisation = " << performedAtLeastOneObjectInitialisation << " entity = " << entity->entityName << endl;
	
	return performedAtLeastOneObjectInitialisation;
}


#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
bool generateCodeBlocksObjectInitialisationsForEntity(NLCcodeblock** currentCodeBlockInTree, GIAentityNode* entity, int sentenceIndex)
{
	bool result = true;

	#ifdef NLC_DEBUG_PARSE_CONTEXT
	cout << "\ngenerateCodeBlocksPart4objectInitialisations(): sentenceIndex = " << sentenceIndex << endl;
	cout << "\tentity->entityName = " << entity->entityName << endl;
	#endif

	NLCcodeblock* originalCodeBlockInLevel = *currentCodeBlockInTree;

	#ifdef NLC_DEBUG_PARSE_CONTEXT
	cout << "generateCodeBlocksObjectInitialisationsForEntity: getParent()" << endl;
	#endif
	GIAentityNode* parentEntity = getParent(entity, sentenceIndex);
	//cout << "done getParent" << endl;
	if(!checkSpecialCaseEntity(parentEntity, false))
	{
		#ifdef NLC_DEBUG_PARSE_CONTEXT
		cout << "\tentity = " << entity->entityName << endl;
		cout << "\tparentEntity = " << parentEntity->entityName << endl;
		cout << "generateCodeBlocksObjectInitialisationsForEntity: generateParentInitialisationCodeBlockWithChecks()" << endl;
		#endif
		if(!generateParentInitialisationCodeBlockWithChecks(currentCodeBlockInTree, parentEntity, sentenceIndex, false))
		{
			#ifdef NLC_DEBUG_PARSE_CONTEXT
			cout << "\tfail generateParentInitialisationCodeBlockWithChecks" << endl;
			cout << "generateCodeBlocksObjectInitialisationsForEntity: generateContextBlocksAndGenerateObjectInitialisationsBasedOnPropertiesAndConditions()" << endl;
			#endif
			if(!generateObjectInitialisationsBasedOnPropertiesAndConditions(parentEntity, currentCodeBlockInTree , sentenceIndex, NULL, "", true, false))
			{
				*currentCodeBlockInTree = originalCodeBlockInLevel;
				clearCodeBlock(originalCodeBlockInLevel);

				#ifdef NLC_DEBUG_PARSE_CONTEXT
				cout << "\tfail generateContextBlocksAndGenerateObjectInitialisationsBasedOnPropertiesAndConditions" << endl;
				#endif
			}
			else
			{
				*currentCodeBlockInTree = getLastCodeBlockInLevel(originalCodeBlockInLevel);
				#ifdef NLC_DEBUG_PARSE_CONTEXT
				cout << "\tpass generateContextBlocksAndGenerateObjectInitialisationsBasedOnPropertiesAndConditions" << endl;
				#endif
			}
		}
		else
		{
			#ifdef NLC_DEBUG_PARSE_CONTEXT
			cout << "\tpass generateParentInitialisationCodeBlockWithChecks" << endl;
			#endif
		}
	}
	return result;
}

bool generateParentInitialisationCodeBlock(NLCcodeblock** currentCodeBlockInTree, GIAentityNode* parentEntity, int sentenceIndex)
{
	bool performedAtLeastParentObjectInitialisation = false;
	
	#ifdef NLC_DEBUG
	cout << "createCodeBlocksCreateNewLocalListVariable: " << parentEntity->entityName << endl;
	#endif
	#ifdef NLC_DEBUG_PARSE_CONTEXT3
	*currentCodeBlockInTree = createCodeBlockDebug(*currentCodeBlockInTree, string("generateParentInitialisationCodeBlockWithChecks(): ") + parentEntity->entityName);
	#endif
	
	*currentCodeBlockInTree = createCodeBlocksCreateNewLocalListVariable(*currentCodeBlockInTree, parentEntity, sentenceIndex);

	parentEntity->NLCparsedForCodeBlocks = true;
	parentEntity->NLClocalListVariableHasBeenInitialised = true;
	//cout << "createCodeBlocksCreateNewLocalListVariable: " << parentEntity->entityName << endl;

	#ifdef GIA_TRANSLATOR_DREAM_MODE_LINK_SPECIFIC_CONCEPTS_AND_ACTIONS
	//Part 2b: generate object initialisations based on substance concepts (class inheritance)
	generateObjectInitialisationsBasedOnSubstanceConcepts(parentEntity, currentCodeBlockInTree, sentenceIndex, true);
	#endif

	#ifdef NLC_DEBUG
	cout << "\tgenerateObjectInitialisationsBasedOnPropertiesAndConditions:" << parentEntity->entityName << endl;
	cout << "sentenceIndex = " << sentenceIndex << endl;
	#endif

	NLCcodeblock* lastCodeBlockInTree = *currentCodeBlockInTree;
	performedAtLeastParentObjectInitialisation = generateObjectInitialisationsBasedOnPropertiesAndConditions(parentEntity, currentCodeBlockInTree, sentenceIndex, NULL, "", false, false);
	
	*currentCodeBlockInTree = lastCodeBlockInTree;
	if(performedAtLeastParentObjectInitialisation)
	{
		*currentCodeBlockInTree = getLastCodeBlockInLevel(*currentCodeBlockInTree);
	}
	else
	{
		clearCodeBlock(*currentCodeBlockInTree);
	}
			
	return performedAtLeastParentObjectInitialisation;
}


#endif



void generateObjectInitialisationsBasedOnPropertiesAndConditionsUpdateCodeBlockPointer(NLCcodeblock** currentCodeBlockInTree, NLCcodeblock* firstCodeBlockBeforeRecursion, NLCcodeblock* firstCodeBlockInSection, bool performedAtLeastOneObjectInitialisationAtThisLevel, bool performedAtLeastOneObjectInitialisationAtALowerLevel, bool* performedAtLeastOneObjectInitialisation)
{
	if(!performedAtLeastOneObjectInitialisationAtALowerLevel)
	{
		if(performedAtLeastOneObjectInitialisationAtThisLevel)
		{
			clearCodeBlock(firstCodeBlockBeforeRecursion);

			*currentCodeBlockInTree = getLastCodeBlockInLevel(firstCodeBlockInSection);
		}
		else
		{
			//erase redundant for loops:
			*currentCodeBlockInTree = clearCodeBlock(firstCodeBlockInSection);
		}
	}
	else
	{
		*currentCodeBlockInTree = getLastCodeBlockInLevel(firstCodeBlockInSection);
	}
	if(performedAtLeastOneObjectInitialisationAtThisLevel || performedAtLeastOneObjectInitialisationAtALowerLevel)
	{
		*performedAtLeastOneObjectInitialisation = true;
	}
}

bool getParentAndGenerateParentInitialisationCodeBlock(NLCcodeblock** currentCodeBlockInTree, GIAentityNode* entity, int sentenceIndex, bool parseLogicalConditions)
{
	bool result = false;
	GIAentityNode* parentEntity = getParent(entity, sentenceIndex);
	#ifdef NLC_DEBUG
	//cout << "parentEntity = " << parentEntity->entityName << endl;
	#endif

	result = generateParentInitialisationCodeBlockWithChecks(currentCodeBlockInTree, parentEntity, sentenceIndex, parseLogicalConditions);
	return result;
}


#ifdef NLC_MARK_ACTION_SUBJECT_OBJECT_INDEFINITE_ENTITY_ACTIONS_AS_NOT_SAME_REFERENCE_SET
#ifdef NLC_DEBUG
cout << "markActionSubjectObjectIndefiniteEntityActionsAsNotSameReferenceSet:" << endl;
#endif
markActionSubjectObjectIndefiniteEntityActionsAsNotSameReferenceSet(&currentCodeBlockInTree, entityNodesActiveListSentence, sentenceIndex);
#endif
		
#ifdef NLC_MARK_ACTION_SUBJECT_OBJECT_INDEFINITE_ENTITY_ACTIONS_AS_NOT_SAME_REFERENCE_SET
bool markActionSubjectObjectIndefiniteEntityActionsAsNotSameReferenceSet(NLCcodeblock** currentCodeBlockInTree, vector<GIAentityNode*>* entityNodesActiveListSentence, int sentenceIndex)
{
	bool result = true;
	//e.g. "a chicken" in "A chicken that ate a pie rows the boat."/"A chicken that ate the pie rows the boat" - set all actions as !sameReferenceSet such that they are not parsed by future references to generateContextBlocks(), but are instead treated as actions
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListSentence->begin(); entityIter != entityNodesActiveListSentence->end(); entityIter++)
	{
		GIAentityNode* actionEntity = (*entityIter);
		if(actionEntity->isAction)
		{
			if(!(actionEntity->isActionConcept))	//CHECKTHIS
			{
				for(vector<GIAentityConnection*>::iterator iter = actionEntity->actionSubjectEntity->begin(); iter < actionEntity->actionSubjectEntity->end(); iter++)
				{
					GIAentityConnection* actionSubjectConnection = *iter;
					GIAentityNode* actionSubjectEntity = actionSubjectConnection->entity;
					if(!assumedToAlreadyHaveBeenDeclared(actionSubjectEntity))
					{//indefinite action subject entity found
						if(actionSubjectConnection->sameReferenceSet)
						{
							//Only perform markActionSubjectObjectIndefiniteEntityActionsAsNotSameReferenceSet for the first sentence in which the action is defined. Although not required for !NLC_LOCAL_LISTS_USE_INSTANCE_NAMES (as actions are never assigned connections across multiple sentence indices), this is critically important for NLC_LOCAL_LISTS_USE_INSTANCE_NAMES (ie GIA_ADVANCED_REFERENCING); eg to prevent the action connections in the second sentence of "A chicken that ate a pie rows the boat. The chicken that ate the pie is happy." from being changed to !sameReferenceSet 
							if(actionEntity->sentenceIndexTemp == actionSubjectConnection->sentenceIndexTemp) 
							{
								bool hasSameSentenceSameReferenceSetActionObject = false;
								bool hasSameSentenceSameReferenceSetIndefiniteActionObject = false;
								for(vector<GIAentityConnection*>::iterator iter = actionEntity->actionObjectEntity->begin(); iter < actionEntity->actionObjectEntity->end(); iter++)
								{
									GIAentityConnection* actionObjectConnection = *iter;
									GIAentityNode* actionObjectEntity = actionObjectConnection->entity;
									if(actionObjectConnection->sentenceIndexTemp == actionSubjectConnection->sentenceIndexTemp)
									{
										if(actionObjectConnection->sameReferenceSet)
										{
											hasSameSentenceSameReferenceSetActionObject = true;
											if(!assumedToAlreadyHaveBeenDeclared(actionObjectEntity))
											{//indefinite action subject entity found
												//e.g. "A chicken that ate a pie rows the boat." [not: "A chicken that ate the pie rows the boat." as the context of "the pie" will be parsed by generateContextBlocks()]
												actionObjectConnection->sameReferenceSet = false;
												#ifdef NLC_DEBUG
												cout << "markActionSubjectObjectIndefiniteEntityActionsAsNotSameReferenceSet() 1: actionObjectEntity = " << actionObjectEntity->entityName << ", action = " << actionEntity->entityName << endl;
												#endif
												hasSameSentenceSameReferenceSetIndefiniteActionObject = true;
											}
										}
									}
								}
								if(!hasSameSentenceSameReferenceSetActionObject || hasSameSentenceSameReferenceSetIndefiniteActionObject)
								{
									//e.g. "A chicken that ate rows the boat."/"A chicken that ate a pie rows the boat."
									actionSubjectConnection->sameReferenceSet = false;
									#ifdef NLC_DEBUG
									cout << "markActionSubjectObjectIndefiniteEntityActionsAsNotSameReferenceSet() 2: actionSubjectEntity = " << actionSubjectEntity->entityName << ", action = " << actionEntity->entityName << endl;
									#endif
								}
								else if(hasSameSentenceSameReferenceSetActionObject)
								{
									//e.g. "A chicken that ate the pie rows the boat." - mark "a chicken" as definite such that its context will be parsed by generateContextBlocks()
									//actionSubjectEntity->grammaticalDefiniteTemp = true;
									actionSubjectEntity->NLClocalListVariableHasBeenInitialised = true;	//added 1n22b
									//cout << "actionSubjectEntity = " << actionSubjectEntity->entityName << endl;
								}
							}
						}
					}
				}
				for(vector<GIAentityConnection*>::iterator iter = actionEntity->actionObjectEntity->begin(); iter < actionEntity->actionObjectEntity->end(); iter++)
				{
					GIAentityConnection* actionObjectConnection = *iter;
					GIAentityNode* actionObjectEntity = actionObjectConnection->entity;
					if(!assumedToAlreadyHaveBeenDeclared(actionObjectEntity))
					{//indefinite action object entity found
						if(actionObjectConnection->sameReferenceSet)
						{
							//Only perform markActionObjectSubjectIndefiniteEntityActionsAsNotSameReferenceSet for the first sentence in which the action is defined. Although not required for !NLC_LOCAL_LISTS_USE_INSTANCE_NAMES (as actions are never assigned connections across multiple sentence indices), this is critically important for NLC_LOCAL_LISTS_USE_INSTANCE_NAMES (ie GIA_ADVANCED_REFERENCING); eg to prevent the action connections in the second sentence of "A chicken that ate a pie rows the boat. The chicken that ate the pie is happy." from being changed to !sameReferenceSet 
							if(actionEntity->sentenceIndexTemp == actionObjectConnection->sentenceIndexTemp) 
							{
								bool hasSameSentenceSameReferenceSetActionSubject = false;
								bool hasSameSentenceSameReferenceSetIndefiniteActionSubject = false;
								for(vector<GIAentityConnection*>::iterator iter = actionEntity->actionSubjectEntity->begin(); iter < actionEntity->actionSubjectEntity->end(); iter++)
								{
									GIAentityConnection* actionSubjectConnection = *iter;
									GIAentityNode* actionSubjectEntity = actionSubjectConnection->entity;
									if(actionSubjectConnection->sentenceIndexTemp == actionObjectConnection->sentenceIndexTemp)
									{
										if(actionSubjectConnection->sameReferenceSet)
										{
											hasSameSentenceSameReferenceSetActionSubject = true;
											if(!assumedToAlreadyHaveBeenDeclared(actionSubjectEntity))
											{//indefinite action object entity found
												//e.g. "A pie that was eaten by a chicken rows the boat." [not: "A pie that was eaten by the chicken rows the boat." as the context of "the chicken" will be parsed by generateContextBlocks()]
												actionSubjectConnection->sameReferenceSet = false;
												#ifdef NLC_DEBUG
												cout << "markActionObjectSubjectIndefiniteEntityActionsAsNotSameReferenceSet() 3: actionSubjectEntity = " << actionSubjectEntity->entityName << ", action = " << actionEntity->entityName << endl;
												#endif
												hasSameSentenceSameReferenceSetIndefiniteActionSubject = true;
											}
										}
									}
								}
								if(!hasSameSentenceSameReferenceSetActionSubject || hasSameSentenceSameReferenceSetIndefiniteActionSubject)
								{
									//e.g. "A pie that was eaten by a chicken rows the boat."/"A pie that was eaten rows the boat."
									actionObjectConnection->sameReferenceSet = false;
									#ifdef NLC_DEBUG
									cout << "markActionObjectSubjectIndefiniteEntityActionsAsNotSameReferenceSet() 4: actionObjectEntity = " << actionObjectEntity->entityName << ", action = " << actionEntity->entityName << endl;
									#endif
								}
								else if(hasSameSentenceSameReferenceSetActionSubject)
								{
									//NOTNECESSARY based on current implementation of generateCodeBlocksFromMathTextNLPparsablePhrase():
									//e.g. "A pie that was eaten by the chicken rows the boat." -  mark "a pie" as definite such that its context will be parsed by generateContextBlocks()
									//actionObjectEntity->grammaticalDefiniteTemp = true;
								}
							}
						}
					}
				}
			}
		}
	}
	return result;
}	
#endif
