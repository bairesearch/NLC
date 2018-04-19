/*******************************************************************************
 *
 * No License
 * 
 * This work is under exclusive copyright (c) Baxter AI (baxterai.com). 
 * Nobody else can use, copy, distribute, or modify this work without being 
 * at risk of take-downs, shake-downs, or litigation. 
 * 
 * By publishing this source code in a public repository on GitHub, Terms of 
 * Service have been accepted by which Baxter AI have allowed others to view 
 * and fork their repository.
 * 
 * If you find software that doesn't have a license, that generally means you 
 * have no permission from the creators of the software to use, modify, or 
 * share the software. Although a code host such as GitHub may allow you to 
 * view and fork the code, this does not imply that you are permitted to use, 
 * modify, or share the software for any purpose.
 *
 * This notice has been derived from https://choosealicense.com/no-permission 
 * (https://web.archive.org/web/20180312144938/https://choosealicense.com/no-permission)
 *
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: NLCtranslatorCodeBlocksOperations.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2018 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler
 * Project Version: 2f1a 22-February-2018
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 * /
 *******************************************************************************/


#include "NLCtranslatorCodeBlocksOperations.hpp"


NLCpreprocessorSentence* firstNLCsentenceInListLocal;





bool NLCtranslatorCodeBlocksOperationsClass::generateCodeBlocksPart3subjectObjectConnections(NLCcodeblock** currentCodeBlockInTree, vector<GIAentityNode*>* entityNodesActiveListSentence, int sentenceIndex, NLCgenerateContextBlocksVariables* generateContextBlocksVariablesLogicalConditionStatement)
{
	bool result = true;
	
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListSentence->begin(); entityIter != entityNodesActiveListSentence->end(); entityIter++)
	{
		GIAentityNode* entity = (*entityIter);
		
		if(NLCcodeBlockClass.checkSentenceIndexParsingCodeBlocks(entity, sentenceIndex, false))
		{
			if(!checkNetworkIndexTypeEntity(entity))
			{
				GIAentityNode* subjectEntity = NULL;
				GIAentityNode* objectEntity = NULL;
				GIAentityConnection* connection = NULL;

				bool foundSubject = false;
				bool foundObject = false;
				bool foundSubjectObjectConnection = false;

				int connectionType = -1;

				if(entity->entityType == GIA_ENTITY_TYPE_ACTION)
				{
					#ifdef NLC_RECORD_ACTION_HISTORY_GENERALISABLE_DO_NOT_EXECUTE_PAST_TENSE_ACTIONS
					if(!isPotentialAction(entity))
					{
					#endif
						bool actionIsSingleWord = false;
						GIAentityConnection* actionSubjectConnection = NULL;
						if(getEntityCheckSameReferenceSetAndSentence(entity, &subjectEntity, &actionSubjectConnection, sentenceIndex, false, GIA_ENTITY_VECTOR_CONNECTION_TYPE_RELATIONSHIP_SUBJECT))
						{
							if(!(actionSubjectConnection->NLCparsedForCodeBlocks))	//added 1o3a (required if GIA adds identical entities to entityNodesActiveListSentence for a given sentenceIndex; eg during GIA_ADVANCED_REFERENCING aliasing)
							{
								if(!checkNetworkIndexTypeEntity(subjectEntity))	//redundant
								{
									foundSubject = true;	
									connectionType = GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTION;
								}
							}
						}
						GIAentityConnection* actionObjectConnection = NULL;
						if(getEntityCheckSameReferenceSetAndSentence(entity, &objectEntity, &actionObjectConnection, sentenceIndex, false, GIA_ENTITY_VECTOR_CONNECTION_TYPE_RELATIONSHIP_OBJECT))
						{
							if(!(actionObjectConnection->NLCparsedForCodeBlocks))	//added 1o3a (required if GIA adds identical entities to entityNodesActiveListSentence for a given sentenceIndex; eg during GIA_ADVANCED_REFERENCING aliasing)
							{
								if(!checkNetworkIndexTypeEntity(objectEntity))	//redundant
								{
									foundObject = true;
									#ifdef NLC_PREPROCESSOR_INTERPRET_SINGLE_WORD_SENTENCES_AS_ACTIONS
									if(objectEntity->entityName == NLC_PREPROCESSOR_INTERPRET_SINGLE_WORD_SENTENCES_AS_ACTIONS_DUMMY_TEXT_ACTION_OBJECT)
									{
										actionIsSingleWord = true;
										foundObject = false;
										objectEntity->disabled = true;	//prevent parsing of dummyActionObject
										actionIsSingleWord = true;
									}
									else
									{
									#endif
										if(!foundSubject)
										{
											connectionType = GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTION_REVERSE;
										}
									#ifdef NLC_PREPROCESSOR_INTERPRET_SINGLE_WORD_SENTENCES_AS_ACTIONS
									}
									#endif	
								}
							}
						}
						if(actionIsSingleWord)
						{
							connectionType = GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTION;
						}
						if(foundSubject || foundObject || actionIsSingleWord)
						{
							foundSubjectObjectConnection = true;

							if(generateCodeBlocksPart3subjectObjectConnection(currentCodeBlockInTree, sentenceIndex, entity, subjectEntity, objectEntity, connection, foundSubject, foundObject, connectionType, generateContextBlocksVariablesLogicalConditionStatement))
							{
								if(foundSubject)
								{
									actionSubjectConnection->NLCparsedForCodeBlocks = true;	//added 1o3a
								}
								if(foundObject)
								{
									actionObjectConnection->NLCparsedForCodeBlocks = true;	//added 1o3a
								}
							}
						}
					#ifdef NLC_RECORD_ACTION_HISTORY_GENERALISABLE_DO_NOT_EXECUTE_PAST_TENSE_ACTIONS
					}
					#endif

					/*
					}
					*/
				}
				else if(entity->entityType == GIA_ENTITY_TYPE_CONDITION)
				{
					#ifdef NLC_NORMALISE_TWOWAY_PREPOSITIONS_DUAL_CONDITION_LINKS_ENABLED
					if(!(entity->inverseConditionTwoWay))	//prevent double up creation of 2 way conditions
					{
					#endif
						GIAentityConnection* conditionSubjectConnection = NULL;
						if(getEntityCheckSameReferenceSetAndSentence(entity, &subjectEntity, &conditionSubjectConnection, sentenceIndex, false, GIA_ENTITY_VECTOR_CONNECTION_TYPE_RELATIONSHIP_SUBJECT))
						{
							if(!(conditionSubjectConnection->NLCparsedForCodeBlocks))	//added 1o3a (required if GIA adds identical entities to entityNodesActiveListSentence for a given sentenceIndex; eg during GIA_ADVANCED_REFERENCING aliasing)
							{
								foundSubject = true;
							}
						}
						GIAentityConnection* conditionObjectConnection = NULL;
						if(getEntityCheckSameReferenceSetAndSentence(entity, &objectEntity, &conditionObjectConnection, sentenceIndex, false, GIA_ENTITY_VECTOR_CONNECTION_TYPE_RELATIONSHIP_OBJECT))
						{
							if(!(conditionObjectConnection->NLCparsedForCodeBlocks))	//added 1o3a (required if GIA adds identical entities to entityNodesActiveListSentence for a given sentenceIndex; eg during GIA_ADVANCED_REFERENCING aliasing)
							{
								foundObject = true;
							}
						}
						if(foundSubject && foundObject)
						{
							foundSubjectObjectConnection = true;	
							connectionType = GIA_ENTITY_VECTOR_CONNECTION_TYPE_CONDITION;

							if(generateCodeBlocksPart3subjectObjectConnection(currentCodeBlockInTree, sentenceIndex, entity, subjectEntity, objectEntity, connection, foundSubject, foundObject, connectionType, generateContextBlocksVariablesLogicalConditionStatement))
							{
								conditionSubjectConnection->NLCparsedForCodeBlocks = true;	//added 1o3a
								conditionObjectConnection->NLCparsedForCodeBlocks = true;	//added 1o3a
							}
						}
					#ifdef NLC_NORMALISE_TWOWAY_PREPOSITIONS_DUAL_CONDITION_LINKS_ENABLED
					}
					#endif
				}
				else
				{
					for(vector<GIAentityConnection*>::iterator iter = entity->propertyNodeList->begin(); iter < entity->propertyNodeList->end(); iter++)
					{
						GIAentityConnection* propertyConnection = *iter;
						GIAentityNode* propertyRelationshipObjectEntity = GIAtranslatorOperations.getPropertyRelationshipObjectEntity(propertyConnection);
						if(NLCcodeBlockClass.checkSentenceIndexParsingCodeBlocks(propertyRelationshipObjectEntity, propertyConnection, sentenceIndex, false))
						{
							if(!(propertyConnection->sameReferenceSet))
							{
								if(!(propertyConnection->NLCparsedForCodeBlocks))	//added 1o3a (required if GIA adds identical entities to entityNodesActiveListSentence for a given sentenceIndex; eg during GIA_ADVANCED_REFERENCING aliasing)
								{
									if(!checkNetworkIndexTypeEntity(propertyRelationshipObjectEntity))	//redundant
									{
										subjectEntity = entity;
										objectEntity = propertyRelationshipObjectEntity;
										foundSubject = true;
										foundObject = true;
										foundSubjectObjectConnection = true;	
										connectionType = GIA_ENTITY_VECTOR_CONNECTION_TYPE_PROPERTY;
										connection = propertyConnection;

										if(generateCodeBlocksPart3subjectObjectConnection(currentCodeBlockInTree, sentenceIndex, entity, subjectEntity, objectEntity, connection, foundSubject, foundObject, connectionType, generateContextBlocksVariablesLogicalConditionStatement))
										{
											propertyConnection->NLCparsedForCodeBlocks = true;	//added 1o3a
										}
									}
								}
							}
						}
					}

					for(vector<GIAentityConnection*>::iterator iter = entity->definitionNodeList->begin(); iter < entity->definitionNodeList->end(); iter++)
					{
						GIAentityConnection* definitionConnection = *iter;
						GIAentityNode* definitionRelationshipObjectEntity = GIAtranslatorOperations.getDefinitionRelationshipObjectEntity(definitionConnection);
						if(NLCcodeBlockClass.checkSentenceIndexParsingCodeBlocks(definitionRelationshipObjectEntity, definitionConnection, sentenceIndex, false))
						{
							if(!(definitionConnection->sameReferenceSet))
							{
								if(!(definitionConnection->NLCparsedForCodeBlocks))	//added 1o3a (required if GIA adds identical entities to entityNodesActiveListSentence for a given sentenceIndex; eg during GIA_ADVANCED_REFERENCING aliasing)
								{
									if(!((definitionRelationshipObjectEntity->entityName == entity->entityName) && (definitionRelationshipObjectEntity->entityType == GIA_ENTITY_TYPE_CONCEPT)))	//ignore dream mode definition connections
									{	
										subjectEntity = entity;
										objectEntity = definitionRelationshipObjectEntity;
										foundSubject = true;
										foundObject = false;	//this is critical (for both logicalConditionStatement and !logicalConditionStatement)
										foundSubjectObjectConnection = true;	
										connectionType = GIA_ENTITY_VECTOR_CONNECTION_TYPE_DEFINITION;
										connection = definitionConnection;

										if(generateCodeBlocksPart3subjectObjectConnection(currentCodeBlockInTree, sentenceIndex, entity, subjectEntity, objectEntity, connection, foundSubject, foundObject, connectionType, generateContextBlocksVariablesLogicalConditionStatement))
										{
											definitionConnection->NLCparsedForCodeBlocks = true;	//added 1o3a
										}	
									}
								}
							}
						}
					}
				}

				#ifdef NLC_EXPLETIVES
				if(entity->isExpletive)
				{
					NLCcodeblock* codeBlockInTreeBeforeParseContext = *currentCodeBlockInTree;
					bool newInitialisation = false;
					GIAentityNode* expletiveParentEntity = NULL;
					//parsing of explitives is only required by logical condition statements (not for explitive initialisations)
					//*currentCodeBlockInTree = createCodeBlocksDeclareNewCategoryListVariable(*currentCodeBlockInTree, subjectEntity, NLC_ITEM_TYPE_SUBJECTCATEGORY_VAR_APPENDITION, sentenceIndex);	//create new subject category list

					#ifdef NLC_TRANSLATOR_LOGICAL_CONDITIONS_BOOLEAN_STATEMENTS_INTERPRET_SUBJECT_AND_OBJECT_INDEPENDENTLY
					if(generateContextBlocksVariablesLogicalConditionStatement->logicalConditionStatement)
					{
						if(getParentAndInitialiseParentIfNecessaryAndGenerateContextBlocks(currentCodeBlockInTree, entity, sentenceIndex, generateContextBlocksVariablesLogicalConditionStatement, false, &expletiveParentEntity, &newInitialisation))
						{

						}						
					}
					else
					{
					#endif					
						if(getParentAndInitialiseParentIfNecessary(currentCodeBlockInTree, entity, sentenceIndex, generateContextBlocksVariablesLogicalConditionStatement, false, &expletiveParentEntity, &newInitialisation))
						{

						}
					#ifdef NLC_TRANSLATOR_LOGICAL_CONDITIONS_BOOLEAN_STATEMENTS_INTERPRET_SUBJECT_AND_OBJECT_INDEPENDENTLY
					}
					#endif
				}
				#endif
			}
		}
	}
	
	return result;
}

bool NLCtranslatorCodeBlocksOperationsClass::generateCodeBlocksPart3subjectObjectConnection(NLCcodeblock** currentCodeBlockInTree, int sentenceIndex, GIAentityNode* entity, GIAentityNode* subjectEntity, GIAentityNode* objectEntity, const GIAentityConnection* connection, const bool foundSubject, bool foundObject, const int connectionType, NLCgenerateContextBlocksVariables* generateContextBlocksVariablesLogicalConditionStatement)
{
	bool result = true;

	
	NLCcodeblock* firstCodeBlockInSentence = *currentCodeBlockInTree;
	
	NLCgenerateContextBlocksVariables generateContextBlocksVariables;
	
	#ifdef NLC_TRANSLATOR_LOGICAL_CONDITIONS_BOOLEAN_STATEMENTS_INTERPRET_SUBJECT_AND_OBJECT_INDEPENDENTLY
	if(generateContextBlocksVariablesLogicalConditionStatement->logicalConditionStatement)
	{
		generateContextBlocksVariables.logicalConditionStatement = true;
		#ifdef NLC_TRANSLATOR_LOGICAL_CONDITIONS_BOOLEAN_STATEMENTS_INTERPRET_SUBJECT_AND_OBJECT_INDEPENDENTLY_SUPPORT_INDEFINITE
		//modified 1t2e, 1u7a, modified 1u11c (not compatible with indefinite entities that have properties, eg "if the blue bike has a green box")
		if(foundSubject)
		{	
			if(connectionType != GIA_ENTITY_VECTOR_CONNECTION_TYPE_DEFINITION)	//redundant
			{
				if(foundObject)
				{
					if(connectionType != GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTION_REVERSE)	//added 1u12a
					{
						if(objectEntity->entityType != GIA_ENTITY_TYPE_QUALITY)
						{
							if(!NLCcodeBlockClass.assumedToAlreadyHaveBeenDeclared(objectEntity))	//!isDefiniteEntity
							{
								*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlocksDeclareNewLocalListVariableIfNecessary(*currentCodeBlockInTree, objectEntity);
							}
						}
					}
				}
			}	
		}
		#endif
	}
	#endif
	
	GIAentityNode* subjectParentEntity = NULL;
	
	//entity->NLCparsedForCodeBlocks = true;
	if(connectionType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTION || connectionType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTION_REVERSE)
	{
		if(!(generateContextBlocksVariablesLogicalConditionStatement->logicalConditionStatement))
		{
			//initialise the action
			if(generateObjectInitialisationsFunction(currentCodeBlockInTree, entity, sentenceIndex))
			{
	
			}
			entity->NLCcontextGeneratedTemp = true;
		}
	}
	

	bool effectiveEach = false;
	bool addNewObjectForEachSubject = false;
	/*
	implement all/each;
		case 1: if detect "each"/"every"/"all" predeterminer {REDUNDANT: and object is singular [REDUNDANT: or quantity entity]} then add a new object for each subject
			eg Each player has a colour.
		case 2: if detect plural subject and indefinite plural object, then add a new object for each subject 
			[OLD: eg Each player has 16 pieces.	[/If each player has 16 pieces]}]
			eg the players have pieces.
		case 3: if detect plural subject and quality object, then add a new object for each subject 
	*/
	if(connectionType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_PROPERTY || connectionType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_CONDITION || connectionType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTION)
	{
		if(foundSubject && foundObject)
		{//this should always be the case for properties and conditions
			//first, initialise a new object if required (such that it remains accessible/in context in a new semtence	
			
			bool subjectEntityPredeterminerDetected = NLCitemClass.detectPredeterminer(subjectEntity, sentenceIndex);
			
			if(subjectEntityPredeterminerDetected)	//modified 1u12c; removed && (objectEntity->grammaticalNumber != GRAMMATICAL_NUMBER_PLURAL)
			{
				effectiveEach = true;
			}
			#ifdef NLC_TRANSLATOR_LOGICAL_CONDITIONS_BOOLEAN_STATEMENTS_INTERPRET_SUBJECT_AND_OBJECT_INDEPENDENTLY_DO_NOT_INTERPRET_NUMERIC_OBJECT_AS_EFFECTIVE_EACH
			if((subjectEntity->grammaticalNumber == GRAMMATICAL_NUMBER_PLURAL) && (objectEntity->grammaticalNumber == GRAMMATICAL_NUMBER_PLURAL) && !NLCcodeBlockClass.isDefiniteEntityStrict(objectEntity) && !(checkNumerosity(objectEntity)))	//modified 1u12d; changed from newInitialisationObject to !NLCcodeBlockClass.isDefiniteEntityStrict(objectEntity) //modified 1u12e; added && !(checkNumerosity(objectEntity)		
			#else
			if((subjectEntity->grammaticalNumber == GRAMMATICAL_NUMBER_PLURAL) && (objectEntity->grammaticalNumber == GRAMMATICAL_NUMBER_PLURAL) && !NLCcodeBlockClass.isDefiniteEntityStrict(objectEntity))	//modified 1u12d; changed from newInitialisationObject to !NLCcodeBlockClass.isDefiniteEntityStrict(objectEntity)
			#endif
			{
				effectiveEach = true;
			}
			if((subjectEntity->grammaticalNumber == GRAMMATICAL_NUMBER_PLURAL) && (objectEntity->entityType == GIA_ENTITY_TYPE_QUALITY))
			{
				effectiveEach = true;
			}
			
			if(effectiveEach)
			{
				if(!(generateContextBlocksVariablesLogicalConditionStatement->logicalConditionStatement))
				{
					addNewObjectForEachSubject = true;
				}
			}
		}
	}
	
	/*
	if(addNewObjectForEachSubject)
	{
		if(!(generateContextBlocksVariablesLogicalConditionStatement->logicalConditionStatement))
		{
			bool newInitialisationObject = false;
			generateContextBlocksVariables.getParentCheckLastParent = true;
			generateContextBlocksVariables.lastParent = subjectEntity;	//is this required? (designed for dual/two-way condition connections only)

			GIAentityNode* objectParentEntity = NULL;
			getParentAndInitialiseParentIfNecessary(currentCodeBlockInTree, objectEntity, sentenceIndex, &generateContextBlocksVariables, false, &objectParentEntity, &newInitialisationObject);
		}
	}
	*/
				
	bool newInitialisationSubject = false;	
	if(foundSubject)
	{
		generateContextBlocksVariables.getParentCheckLastParent = true;
		generateContextBlocksVariables.lastParent = objectEntity;	//is this required? (designed for dual/two-way condition connections only)
		
		NLCcodeblock* codeBlockInTreeBeforeParseContext = *currentCodeBlockInTree;
		*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlocksDeclareNewCategoryListVariable(*currentCodeBlockInTree, subjectEntity, NLC_ITEM_TYPE_SUBJECTCATEGORY_VAR_APPENDITION, sentenceIndex);	//create new subject category list
		if(getParentAndInitialiseParentIfNecessaryAndGenerateContextBlocks(currentCodeBlockInTree, subjectEntity, sentenceIndex, &generateContextBlocksVariables, false, &subjectParentEntity, &newInitialisationSubject))
		{
			//if(!addNewObjectForEachSubject)	//optional (removes redundancy but lowers consistency)
			//{
			*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockAddEntityToCategoryListCheckLastSentenceReferencedPluralExecuteFunction(*currentCodeBlockInTree, subjectEntity, subjectEntity, NLC_ITEM_TYPE_SUBJECTCATEGORY_VAR_APPENDITION, sentenceIndex, false);
			//}
		}
		
		if(!addNewObjectForEachSubject)
		{
			*currentCodeBlockInTree = NLCcodeBlockClass.getLastCodeBlockInLevel(codeBlockInTreeBeforeParseContext);	
			#ifdef NLC_TRANSLATOR_TEST_DEFINITE_ENTITY_EXISTENCE_SUBJECT_OBJECT
			generateDefiniteEntityExistenceTest(currentCodeBlockInTree, subjectEntity, sentenceIndex, NLC_ITEM_TYPE_SUBJECTCATEGORY_VAR_APPENDITION, generateContextBlocksVariablesLogicalConditionStatement, true);
			#endif
		}
	}
	
	#ifdef NLC_TRANSLATOR_LOGICAL_CONDITIONS_BOOLEAN_STATEMENTS_INTERPRET_SUBJECT_AND_OBJECT_INDEPENDENTLY_SUPPORT_INDEFINITE
	if(generateContextBlocksVariablesLogicalConditionStatement->logicalConditionStatement)
	{
		//modified 1t2e, 1u7a, modified 1u11c (not compatible with indefinite entities that have properties, eg "if the blue bike has a green box")
		if(foundSubject)
		{	
			if(connectionType != GIA_ENTITY_VECTOR_CONNECTION_TYPE_DEFINITION)	//redundant
			{
				if(foundObject)
				{
					if(connectionType != GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTION_REVERSE)	//added 1u12a
					{
						//1u11c:
						if(objectEntity->entityType == GIA_ENTITY_TYPE_QUALITY)
						{
							foundObject = false;
						}
						else
						{
							#ifdef NLC_TRANSLATOR_LOGICAL_CONDITIONS_BOOLEAN_STATEMENTS_INTERPRET_SUBJECT_AND_OBJECT_INDEPENDENTLY_SUPPORT_INDEFINITE_ADD_OBJECT_TO_LOCAL_LIST
							//1u12a
							if(!NLCcodeBlockClass.assumedToAlreadyHaveBeenDeclared(objectEntity))	//!isDefiniteEntity
							{
								//add the subject's object's to its local list
								
								NLCcodeblock* currentCodeBlockInTreeBackup = *currentCodeBlockInTree;
								generateContextBlocksVariablesLogicalConditionStatement->secondaryComparison = false;
								if(generateCodeBlocksVerifyConnection(currentCodeBlockInTree, connectionType, connection, subjectEntity, objectEntity, entity, foundSubject, false, sentenceIndex, false, generateContextBlocksVariablesLogicalConditionStatement))
								{	
									*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockAddEntityToLocalList(*currentCodeBlockInTree, objectEntity, objectEntity);
								}
								*currentCodeBlockInTree = NLCcodeBlockClass.getLastCodeBlockInLevel(currentCodeBlockInTreeBackup);
							}
							#endif						
						}
					}
				}
			}	
		}
	}
	#endif
	
	
	bool newInitialisationObject = false;
	if(foundObject)
	{
		generateContextBlocksVariables.getParentCheckLastParent = true;
		generateContextBlocksVariables.lastParent = subjectEntity;
			
		NLCcodeblock* codeBlockInTreeBeforeParseContext = *currentCodeBlockInTree;
		*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlocksDeclareNewCategoryListVariable(*currentCodeBlockInTree, objectEntity, NLC_ITEM_TYPE_OBJECTCATEGORY_VAR_APPENDITION, sentenceIndex);	//create new object category list
		GIAentityNode* objectParentEntity = NULL;
		if(getParentAndInitialiseParentIfNecessaryAndGenerateContextBlocks(currentCodeBlockInTree, objectEntity, sentenceIndex, &generateContextBlocksVariables, false, &objectParentEntity, &newInitialisationObject))
		{
			//if(!addNewObjectForEachSubject)	//optional (removes redundancy but lowers consistency)
			//{
			*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockAddEntityToCategoryListCheckLastSentenceReferencedPluralExecuteFunction(*currentCodeBlockInTree, objectEntity, objectEntity, NLC_ITEM_TYPE_OBJECTCATEGORY_VAR_APPENDITION, sentenceIndex, false);
			//}
		}

		if(!addNewObjectForEachSubject)
		{
			*currentCodeBlockInTree = NLCcodeBlockClass.getLastCodeBlockInLevel(codeBlockInTreeBeforeParseContext);
			#ifdef NLC_TRANSLATOR_TEST_DEFINITE_ENTITY_EXISTENCE_SUBJECT_OBJECT
			generateDefiniteEntityExistenceTest(currentCodeBlockInTree, objectEntity, sentenceIndex, NLC_ITEM_TYPE_OBJECTCATEGORY_VAR_APPENDITION, generateContextBlocksVariablesLogicalConditionStatement, true);
			#endif
		}
	}

	if(connectionType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTION || connectionType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTION_REVERSE)
	{
		entity->NLCcontextGeneratedTemp = false;
	}
	
	#ifdef NLC_TRANSLATOR_LOGICAL_CONDITIONS_BOOLEAN_STATEMENTS_INTERPRET_SUBJECT_AND_OBJECT_INDEPENDENTLY
	if((generateContextBlocksVariablesLogicalConditionStatement->logicalConditionStatement))
	{
		#ifdef NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY
		generateContextBlocksVariablesLogicalConditionStatement->testNumerosity = true;
		#endif
		generateContextBlocksVariablesLogicalConditionStatement->secondaryComparison = true;
		if(generateCodeBlocksVerifyConnection(currentCodeBlockInTree, connectionType, connection, subjectEntity, objectEntity, entity, foundSubject, foundObject, sentenceIndex, effectiveEach, generateContextBlocksVariablesLogicalConditionStatement))
		{	
			//code generation completed by generateCodeBlocksFromMathTextNLPparsablePhrase
		}	
	}
	else
	{
	#endif
		bool isPrimary = !addNewObjectForEachSubject;
		if(generateCodeBlocksAddConnection(currentCodeBlockInTree, connectionType, connection, subjectEntity, objectEntity, entity, foundSubject, foundObject, sentenceIndex,  subjectParentEntity, isPrimary))
		{	
			*currentCodeBlockInTree = NLCcodeBlockClass.getLastCodeBlockInLevel(firstCodeBlockInSentence);
		}
		else
		{
			if(!newInitialisationSubject && !newInitialisationObject)
			{
				*currentCodeBlockInTree = NLCcodeBlockClass.clearCodeBlock(firstCodeBlockInSentence);
			}
			else
			{
				*currentCodeBlockInTree = NLCcodeBlockClass.getLastCodeBlockInLevel(firstCodeBlockInSentence);
			}
		}
	#ifdef NLC_TRANSLATOR_LOGICAL_CONDITIONS_BOOLEAN_STATEMENTS_INTERPRET_SUBJECT_AND_OBJECT_INDEPENDENTLY
	}
	#endif

	if(addNewObjectForEachSubject)
	{
	
		#ifdef NLC_TRANSLATOR_TEST_DEFINITE_ENTITY_EXISTENCE_SUBJECT_OBJECT
		generateDefiniteEntityExistenceTest(currentCodeBlockInTree, subjectEntity, sentenceIndex, NLC_ITEM_TYPE_SUBJECTCATEGORY_VAR_APPENDITION, generateContextBlocksVariablesLogicalConditionStatement, true);
		#endif	
	}
			
	return result;
}

	
#ifdef NLC_GENERATE_FUNCTION_ARGUMENTS_BASED_ON_ACTION_AND_ACTION_OBJECT_VARS
bool NLCtranslatorCodeBlocksOperationsClass::generateObjectInitialisationsFunction(NLCcodeblock** currentCodeBlockInTree, GIAentityNode* actionRelationshipEntity, const int sentenceIndex)
{
	bool result = true;
	actionRelationshipEntity->NLCisSingularArgument = true;	//added 1e2c
	result = generateObjectInitialisationsAction(currentCodeBlockInTree, actionRelationshipEntity, sentenceIndex);
	return result;
}
#endif

#ifdef NLC_TRANSLATOR_TEST_DEFINITE_ENTITY_EXISTENCE
void NLCtranslatorCodeBlocksOperationsClass::generateDefiniteEntityExistenceTest(NLCcodeblock** currentCodeBlockInTree, GIAentityNode* entity, int sentenceIndex, const string genericListAppendName, const NLCgenerateContextBlocksVariables* generateContextBlocksVariablesLogicalConditionStatement, const bool checkParent)
{	
	bool testDefiniteEntityExistence = true;
	#ifdef NLC_TRANSLATOR_LOGICAL_CONDITIONS_BOOLEAN_STATEMENTS_INTERPRET_SUBJECT_AND_OBJECT_INDEPENDENTLY
	if(generateContextBlocksVariablesLogicalConditionStatement->logicalConditionStatement)
	{
		testDefiniteEntityExistence = false;
		bool parseConditionParents = NLC_PARSE_CONDITION_PARENTS_DEFAULT_VALUE;
		bool checkIsDefinite = true;
		bool entityHasSameReferenceSetDefiniteParent = false;
		GIAentityNode* parentEntityNew = getSameReferenceSetUniqueParent(entity, sentenceIndex, NULL, &entityHasSameReferenceSetDefiniteParent, parseConditionParents, checkIsDefinite);
		if(NLCcodeBlockClass.isDefiniteEntityStrict(entity) || (checkParent && entityHasSameReferenceSetDefiniteParent))
		{
			testDefiniteEntityExistence = true;
		}
	}
	#endif
	if(testDefiniteEntityExistence)
	{
		NLCcodeblock* lastCodeBlockInTree2 = *currentCodeBlockInTree;
		#ifdef NLC_TRANSLATOR_TEST_DEFINITE_ENTITY_EXISTENCE_FUNCTION
		*currentCodeBlockInTree = NLCcodeBlockClass.createCodeVerifyDefiniteReferenceExistenceExecuteFunction(*currentCodeBlockInTree, entity, genericListAppendName, sentenceIndex);
		#else
		*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockIfHasCategoryItem(*currentCodeBlockInTree, entity, true, genericListAppendName, sentenceIndex);
		if(genericListAppendName == NLC_ITEM_TYPE_SUBJECTCATEGORY_VAR_APPENDITION)
		{
			*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockPrintWarning(*currentCodeBlockInTree, NLC_TRANSLATOR_TEST_DEFINITE_ENTITY_EXISTENCE_SUBJECT_WARNING_TEXT + entity->entityName);
		}
		else if(genericListAppendName == NLC_ITEM_TYPE_OBJECTCATEGORY_VAR_APPENDITION)
		{
			*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockPrintWarning(*currentCodeBlockInTree, NLC_TRANSLATOR_TEST_DEFINITE_ENTITY_EXISTENCE_OBJECT_WARNING_TEXT + entity->entityName);		
		}
		else if(genericListAppendName == NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION)
		{
			*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockPrintWarning(*currentCodeBlockInTree, NLC_TRANSLATOR_TEST_DEFINITE_ENTITY_EXISTENCE_CATEGORIES_WARNING_TEXT + entity->entityName);		
		}
		#endif
		*currentCodeBlockInTree = lastCodeBlockInTree2->next;
	}
}
#endif
	





bool NLCtranslatorCodeBlocksOperationsClass::generateContextBlocks(NLCcodeblock** currentCodeBlockInTree, GIAentityNode* parentEntity, int sentenceIndex, NLCgenerateContextBlocksVariables* generateContextBlocksVariables, const bool generatedParentContext, const string genericListAppendName)
{	
	#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN
	return generateContextBlocksCategories(currentCodeBlockInTree, parentEntity, sentenceIndex, generateContextBlocksVariables, generatedParentContext, genericListAppendName);	
	#else
	return generateContextBlocksSimple(currentCodeBlockInTree, parentEntity, sentenceIndex, generateContextBlocksVariables, generatedParentContext, genericListAppendName);
	#endif
}

#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN
bool NLCtranslatorCodeBlocksOperationsClass::generateContextBlocksCategories(NLCcodeblock** currentCodeBlockInTree, GIAentityNode* parentEntity, int sentenceIndex, NLCgenerateContextBlocksVariables* generateContextBlocksVariables, const bool generatedParentContext, const string genericListAppendName)
{			
	bool contextFound = false;
	#ifdef NLC_ADVANCED_REFERENCING_SUPPORT_ALIASES
	string parentEntityAliasName = "";
	if(NLCcodeBlockClass.findAliasInEntity(parentEntity, &parentEntityAliasName))
	{
		//added 1k14b;
		*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlocksDeclareNewCategoryListVariable(*currentCodeBlockInTree, parentEntity, genericListAppendName, sentenceIndex);
		*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlocksFindAliasAndAddToCategoryListExecuteFunction(*currentCodeBlockInTree, parentEntityAliasName, parentEntity, genericListAppendName, sentenceIndex);
		*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockForCategoryList(*currentCodeBlockInTree, parentEntity, genericListAppendName, sentenceIndex);
		parentEntity->NLCcontextGenerated = true;
		contextFound = true;
	}
	else
	{
	#endif
		*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlocksDeclareNewCategoryListVariable(*currentCodeBlockInTree, parentEntity, genericListAppendName, sentenceIndex);
		#ifdef NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY_CHILDREN_BASIC
		if(generateContextBlocksVariables->testNumerosity)
		{
			string categoryListPropertyCountVariableName = NLCcodeBlockClass.generateCategoryListPropertyCountVariableName(parentEntity);
			*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockDeclareNewIntVar(*currentCodeBlockInTree, categoryListPropertyCountVariableName, 0);
		}
		#endif

		NLCcodeblock* lastCodeBlockInTree = *currentCodeBlockInTree;
		if(generateContextBlocksSimple(currentCodeBlockInTree, parentEntity, sentenceIndex, generateContextBlocksVariables, generatedParentContext, genericListAppendName))
		{
			contextFound = true;
		}

		addEntityToCategoryList(currentCodeBlockInTree, parentEntity, parentEntity, genericListAppendName, generateContextBlocksVariables, sentenceIndex, false);

		if(!(generatedParentContext && !contextFound))
		{
			*currentCodeBlockInTree = lastCodeBlockInTree->next;
		}

		lastCodeBlockInTree = *currentCodeBlockInTree;
		
		if(generateContextBlocksVariables->searchConceptsForChildren)
		{
			/*
			cout << "sentenceIndex = " << sentenceIndex << endl;
			cout << "parentEntity->entityName = " << parentEntity->entityName << endl;
			cout << "parentEntity->entityIndexTemp = " << parentEntity->entityIndexTemp << endl;
			*/
			//eg "A yellow bannana is on the table. Yellow bannanas are fruit. The fruit is tasty."
			for(vector<GIAentityConnection*>::iterator definitionNodeListIterator = parentEntity->definitionNodeList->begin(); definitionNodeListIterator < parentEntity->definitionNodeList->end(); definitionNodeListIterator++)
			{
				GIAentityNode* parentConcept = GIAtranslatorOperations.getDefinitionRelationshipObjectEntity(*definitionNodeListIterator);	//e.g. "fruit" concept
				/*
				cout << "\tsentenceIndex = " << sentenceIndex << endl;
				cout << "\tparentConcept->entityName = " << parentConcept->entityName << endl;
				*/
				if(parentConcept->entityType == GIA_ENTITY_TYPE_CONCEPT)
				{	
					if(parentConcept->entityName == parentEntity->entityName)	//added 1q3a
					{
						if(createCodeBlockForStatementsForDefinitionChildren(currentCodeBlockInTree, &lastCodeBlockInTree, parentEntity, parentConcept, sentenceIndex, generateContextBlocksVariables, true, genericListAppendName))
						{
							contextFound = true;
						}
					}
				}
			}
		}
		
		#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN_SUBCLASSES
		if(generateContextBlocksVariables->searchSubclassesForChildren)
		{
			if(parentEntity->isSubClass)
			{
				//eg "The goal has a line. The ball is near the goal line."			
				bool foundNearestSubClassParentEntity = false;
				GIAentityNode* nearestSubclassParentEntity = NULL;
				if(findNearestSubClassParentEntityCorrespondingToSubclassEntityInSameContext(parentEntity, &nearestSubclassParentEntity))
				{
					if(createCodeBlockForStatementsForNearestSubClassParentReference(currentCodeBlockInTree, &lastCodeBlockInTree, parentEntity, nearestSubclassParentEntity, sentenceIndex, generateContextBlocksVariables, true, genericListAppendName))
					{
						contextFound = true;
					}
				}
			}
		}
		#endif

		#ifdef NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY_CHILDREN_BASIC
		if(generateContextBlocksVariables->testNumerosity)
		{
			//test numerosity of child
			//cout << "parentEntity = " << parentEntity->entityName << endl;
			if(generateContextBlocksVariables->childQuantity > 1)
			{
				//cout << "parentEntity = " << parentEntity->entityName << endl;
				#ifdef NLC_CATEGORIES_TEST_PLURALITY_COMMENT
				*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockCommentSingleLine(*currentCodeBlockInTree, "numerosity tests (child)");
				#endif
				string categoryListPropertyCountVariableName = NLCcodeBlockClass.generateCategoryListPropertyCountVariableName(parentEntity);
				*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockIfIntVariableGreaterThanOrEqualToNum(*currentCodeBlockInTree, categoryListPropertyCountVariableName, generateContextBlocksVariables->childQuantity);
			}			

		}
		#endif
		
		#ifdef NLC_FUNCTIONS_SUPPORT_PLURAL_SUBJECTS_AND_OBJECTS
		if(generateContextBlocksVariables->enterGeneratedCategoryList)
		{
		#endif
			#ifdef NLC_CATEGORIES_TEST_PLURALITY
			bool testDefiniteEntityExistence = true;
			bool testPlurality = false;
			if((parentEntity->grammaticalNumber == GRAMMATICAL_NUMBER_SINGULAR) && NLCcodeBlockClass.assumedToAlreadyHaveBeenDeclared(parentEntity))	//added NLCcodeBlockClass.assumedToAlreadyHaveBeenDeclared(parentEntity) criteria 1j15a
			{
				testPlurality = true;
			}
			#ifdef NLC_TRANSLATOR_LOGICAL_CONDITIONS_BOOLEAN_STATEMENTS_INTERPRET_SUBJECT_AND_OBJECT_INDEPENDENTLY_SUPPORT_INDEFINITE
			if(generateContextBlocksVariables->logicalConditionStatement)
			{
				if(!NLCcodeBlockClass.isDefiniteEntityStrict(parentEntity))
				{
					testPlurality = false;
				}
			}
			#endif
			#ifdef NLC_TRANSLATOR_TEST_DEFINITE_ENTITY_EXISTENCE_CATEGORIES
			generateDefiniteEntityExistenceTest(currentCodeBlockInTree, parentEntity, sentenceIndex, genericListAppendName, generateContextBlocksVariables, false);
			#endif
			if(testPlurality)
			{
				#ifdef NLC_CATEGORIES_TEST_PLURALITY_COMMENT_REDUNDANT
				*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockCommentSingleLine(*currentCodeBlockInTree, "Singular definite plurality tests");
				#endif
				#ifdef NLC_CATEGORIES_TEST_PLURALITY_WARNING
				#ifndef NLC_CATEGORIES_TEST_PLURALITY_WARNING_PLACE_IN_NLC_PREDEFINED_FUNCTION_ADDTOCATEGORYIFPASSSINGULARDEFINITEREFERENCINGTESTS
				#ifdef NLC_CATEGORIES_TEST_PLURALITY_COMMENT
				*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockCommentSingleLine(*currentCodeBlockInTree, "Singular definite plurality tests");
				#endif
				NLCcodeblock* lastCodeBlockInTree2 = *currentCodeBlockInTree;
				*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockIfHasGreaterThanNumCategoryItem(*currentCodeBlockInTree, parentEntity, genericListAppendName, 1, sentenceIndex);
				*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockPrintWarning(*currentCodeBlockInTree, NLC_CATEGORIES_TEST_PLURALITY_WARNING_MESSAGE);
				*currentCodeBlockInTree = lastCodeBlockInTree2->next;
				#endif
				#endif
				
				#ifdef NLC_TRANSLATOR_LOGICAL_CONDITIONS_SINGLE_SENTENCE_MULTIPLE_LEVEL_FOR_LOOPS_OLD
				#ifndef NLC_GENERATE_UNIQUE_CONTEXT_BLOCK_FOR_EACH_SENTENCE_LOGICAL_CONDITIONS_FOR_LOOPS
				#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
				if(generateContextBlocksVariables->setCodeBlockInTreeAtBaseLevel)
				{
					generateContextBlocksVariables->currentCodeBlockInTreeAtBaseLevel = *currentCodeBlockInTree;
				}
				#endif
				#endif
				#endif
				#ifdef NLC_CATEGORIES_TEST_PLURALITY_ENFORCE
				*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockIfHasCategoryItem(*currentCodeBlockInTree, parentEntity, false, genericListAppendName, sentenceIndex);	//added 1j5a
				*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockGetBackCategoryEntityList(*currentCodeBlockInTree, parentEntity, genericListAppendName, sentenceIndex);
				#else
				*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockForCategoryList(*currentCodeBlockInTree, parentEntity, genericListAppendName, sentenceIndex);
				#endif
			}
			else
			{
			#endif
				#ifdef NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY_PARENT_BASIC
				if(generateContextBlocksVariables->testNumerosity)
				{
					//test numerosity of parent
					if(checkNumerosity(parentEntity))
					{
						#ifdef NLC_CATEGORIES_TEST_PLURALITY_COMMENT
						*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockCommentSingleLine(*currentCodeBlockInTree, "numerosity tests (parent)");
						#endif
						*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockIfHasGreaterThanOrEqualToNumCategoryItem(*currentCodeBlockInTree, parentEntity, genericListAppendName, parentEntity->quantityNumber, sentenceIndex);
					}
				}
				#endif

				#ifdef NLC_TRANSLATOR_LOGICAL_CONDITIONS_SINGLE_SENTENCE_MULTIPLE_LEVEL_FOR_LOOPS_OLD
				#ifndef NLC_GENERATE_UNIQUE_CONTEXT_BLOCK_FOR_EACH_SENTENCE_LOGICAL_CONDITIONS_FOR_LOOPS
				#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
				if(generateContextBlocksVariables->setCodeBlockInTreeAtBaseLevel)
				{
					generateContextBlocksVariables->currentCodeBlockInTreeAtBaseLevel = *currentCodeBlockInTree;
				}
				#endif
				#endif
				#endif
				*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockForCategoryList(*currentCodeBlockInTree, parentEntity, genericListAppendName, sentenceIndex);
			#ifdef NLC_CATEGORIES_TEST_PLURALITY
			}
			#endif

			#ifdef NLC_ADVANCED_REFERENCING
			*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockUpdateLastSentenceReferenced(*currentCodeBlockInTree, parentEntity, sentenceIndex);
			#endif
		
		#ifdef NLC_FUNCTIONS_SUPPORT_PLURAL_SUBJECTS_AND_OBJECTS
		}	
		#endif
		
	#ifdef NLC_ADVANCED_REFERENCING_SUPPORT_ALIASES
	}
	#endif
	return contextFound;

}
#endif

bool NLCtranslatorCodeBlocksOperationsClass::generateContextBlocksSimple(NLCcodeblock** currentCodeBlockInTree, GIAentityNode* parentEntity, int sentenceIndex, NLCgenerateContextBlocksVariables* generateContextBlocksVariables, const bool generatedParentContext, const string genericListAppendName)
{
	bool contextFound = false;
	
	NLCcodeblock* originalCodeBlockInTree = *currentCodeBlockInTree;

	//#ifdef NLC_DEBUG_PARSE_CONTEXT3
	//*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockDebug(*currentCodeBlockInTree, string("generateContextBlocksSimple{}: ") + parentEntity->entityName);
	//#endif

	#ifdef NLC_TRANSLATOR_LOGICAL_CONDITIONS_SINGLE_SENTENCE_MULTIPLE_LEVEL_FOR_LOOPS_OLD
	#ifndef NLC_GENERATE_UNIQUE_CONTEXT_BLOCK_FOR_EACH_SENTENCE_LOGICAL_CONDITIONS_FOR_LOOPS
	#ifndef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN
	#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
	if(generateContextBlocksVariables->setCodeBlockInTreeAtBaseLevel)
	{
		generateContextBlocksVariables->currentCodeBlockInTreeAtBaseLevel = *currentCodeBlockInTree;
	}
	#endif
	#endif
	#endif
	#endif
			
	if(!generatedParentContext)
	{
		//context property item:
		if(NLCcodeBlockClass.assumedToAlreadyHaveBeenDeclared(parentEntity))
		{
			//cout << "at1 parentEntity = " << parentEntity->entityName << "sentenceIndex = " << sentenceIndex << endl;
			*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockForOrInLocalList(*currentCodeBlockInTree, parentEntity);	
		}
		else
		{
			//cout << "at2 parentEntity = " << parentEntity->entityName << "sentenceIndex = " << sentenceIndex << endl;
			*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockForOrInPropertyList(*currentCodeBlockInTree, parentEntity);	
		}
	}

	//parse the children (properties and conditions) of an undeclared definite parent
	if(!createCodeBlockForStatements(currentCodeBlockInTree, NLCitemClass.generateInstanceName(parentEntity), parentEntity, sentenceIndex, generateContextBlocksVariables))
	{
		#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
		//if(!generatedParentContext)	//considered adding 1j13b
		//{
		parentEntity->NLCcontextGenerated = true;	//added 1g14b 15-July-2014
		//}		
		#endif
	}
	else
	{
		contextFound = true;
		#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
		parentEntity->NLCcontextGenerated = true;	//added 1g14b 15-July-2014
		#endif
	}

	return contextFound;
}


#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN
bool NLCtranslatorCodeBlocksOperationsClass::createCodeBlockForStatementsForDefinitionChildren(NLCcodeblock** currentCodeBlockInTree, NLCcodeblock** lastCodeBlockInTree, GIAentityNode* parentInstance, GIAentityNode* parentConcept, int sentenceIndex, NLCgenerateContextBlocksVariables* generateContextBlocksVariables, const bool generateContext, const string genericListAppendName)
{
	bool contextFound = false;
	for(vector<GIAentityConnection*>::iterator reverseDefinitionNodeListIterator = parentConcept->definitionReverseNodeList->begin(); reverseDefinitionNodeListIterator < parentConcept->definitionReverseNodeList->end(); reverseDefinitionNodeListIterator++)
	{
		GIAentityNode* child = GIAtranslatorOperations.getDefinitionRelationshipSubjectEntity(*reverseDefinitionNodeListIterator);
		if(child != parentInstance)
		{
			if(child->entityType == GIA_ENTITY_TYPE_CONCEPT)
			{
				GIAentityNode* childConcept = child;
				//recurse; eg "interesting bannanas" in "A yellow bannana is on the table. Interesting bannanas are yellow bannanas. Yellow bannanas are fruit. The fruit is tasty."
				if(createCodeBlockForStatementsForDefinitionChildren(currentCodeBlockInTree, lastCodeBlockInTree, parentInstance, childConcept, sentenceIndex, generateContextBlocksVariables, generateContext, genericListAppendName))
				{
					contextFound = true;
				}
			}
			else
			{
				GIAentityNode* childSubstance = child;
				//definition child (e.g. apple)
				#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN_DO_NOT_PARSE_DUPLICATE_CLASSES
				if(child->entityName != parentInstance->entityName)
				{
				#endif	
					//this code is from generateContextBlocksSimple{}:

					//context property item:	
					bool parseDefinitionChild = false;	
					if(NLCcodeBlockClass.assumedToAlreadyHaveBeenDeclared(childSubstance))
					{
						*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockForLocalList(*currentCodeBlockInTree, childSubstance);
						parseDefinitionChild = true;
					}
					else
					{
						parseDefinitionChild = false;	//changed @NLC1u3b: do not parse if not already declared
						/*
						parseDefinitionChild = true;
						#ifdef NLC_DEBUG_PARSE_CONTEXT_CHILDREN	
						cout << "2 NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN createCodeBlockForPropertyList{}: !assumedToAlreadyHaveBeenDeclared: childSubstance = " << childSubstance->entityName << endl;
						#endif
						*currentCodeBlockInTree = createCodeBlockForPropertyList(*currentCodeBlockInTree, childSubstance);
						*/
					}	

					if(parseDefinitionChild)
					{
						if(generateContext)
						{
							if(createCodeBlockForStatements(currentCodeBlockInTree, NLCitemClass.generateInstanceName(childSubstance), parentInstance, sentenceIndex, generateContextBlocksVariables))
							{
								contextFound = true;
							}
						}
						else
						{
							contextFound = true;
						}

						if((parentConcept->entityName != childSubstance->entityName) && checkParentExists(parentConcept, childSubstance->entityName))	//verify that "bananas are fruit"/"Chess is a game."
						{
							*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockIfTempVariableNameEqualsClassName(*currentCodeBlockInTree, childSubstance, parentConcept->entityName);	//verify that the substance (eg "the fruit") in its local list has previously been renamed to "banana" (see NLC_TRANSLATOR_GENERATE_CONTEXT_BLOCKS_PARSE_DEFINITIONS:generateCodeBlocksAddConnection:GIA_ENTITY_VECTOR_CONNECTION_TYPE_DEFINITION)

							//[substance definition logic #2] eg parsing back through this past sentence from banana to fruit; "the fruit is a yellow banana. [The banana is tasty.]" / "The game is chess. [The game of chess is good.]"
							addEntityToCategoryList(currentCodeBlockInTree, parentInstance, childSubstance, genericListAppendName, generateContextBlocksVariables, sentenceIndex, true);
						}
						else
						{
							//[substance definition logic #1] eg parsing back through this past sentence from fruit to banana; "The yellow banana is a fruit. [The yellow fruit is tasty.]"
							addEntityToCategoryList(currentCodeBlockInTree, parentInstance, childSubstance, genericListAppendName, generateContextBlocksVariables, sentenceIndex, false);
						}


						*currentCodeBlockInTree = NLCcodeBlockClass.getLastCodeBlockInLevel(*lastCodeBlockInTree);
						*lastCodeBlockInTree = *currentCodeBlockInTree;
					}

				#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN_DO_NOT_PARSE_DUPLICATE_CLASSES
				}
				#endif	
			}
		}
	}
	return contextFound;
}

bool NLCtranslatorCodeBlocksOperationsClass::addEntityToCategoryList(NLCcodeblock** currentCodeBlockInTree, const GIAentityNode* entity, const GIAentityNode* propertyRelationshipObjectEntity, const string genericListAppendName, const NLCgenerateContextBlocksVariables* generateContextBlocksVariables, const int sentenceIndex, const bool castToCategoryType)
{
	bool result = true;
	
	#ifdef NLC_ADVANCED_REFERENCING
	bool singular = false;
	if((entity->grammaticalNumber == GRAMMATICAL_NUMBER_SINGULAR) && NLCcodeBlockClass.assumedToAlreadyHaveBeenDeclared(entity))	//added NLCcodeBlockClass.assumedToAlreadyHaveBeenDeclared(parentEntity) criteria 1j15a
	{
		singular = true;
	}
	#ifdef NLC_TRANSLATOR_LOGICAL_CONDITIONS_BOOLEAN_STATEMENTS_INTERPRET_SUBJECT_AND_OBJECT_INDEPENDENTLY_SUPPORT_INDEFINITE
	if(generateContextBlocksVariables->logicalConditionStatement)
	{
		if(!NLCcodeBlockClass.isDefiniteEntityStrict(entity))
		{
			singular = false;
		}
	}
	#endif
	if(singular)
	{
		#ifdef NLC_ADVANCED_REFERENCING_COMMENT
		*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockCommentSingleLine(*currentCodeBlockInTree, "Singular definite referencing tests");
		#endif
		*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockAddEntityToCategoryListCheckLastSentenceReferencedSingularExecuteFunction(*currentCodeBlockInTree, entity, propertyRelationshipObjectEntity, genericListAppendName, sentenceIndex, castToCategoryType);
	}
	else
	{
		#ifdef NLC_ADVANCED_REFERENCING_COMMENT
		*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockCommentSingleLine(*currentCodeBlockInTree, "Plural definite referencing tests");
		#endif
		*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockAddEntityToCategoryListCheckLastSentenceReferencedPluralExecuteFunction(*currentCodeBlockInTree, entity, propertyRelationshipObjectEntity, genericListAppendName, sentenceIndex, castToCategoryType);
	}
	#else
	#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN_DO_NOT_ADD_DUPLICATES
	*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockAddEntityToCategoryListCheckLastSentenceReferencedPluralExecuteFunction(*currentCodeBlockInTree, entity, propertyRelationshipObjectEntity, genericListAppendName, sentenceIndex, castToCategoryType);	
	#else
	*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockAddEntityToCategoryList(*currentCodeBlockInTree, entity, propertyRelationshipObjectEntity, genericListAppendName, sentenceIndex);
	#endif
	#endif

	#ifdef NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY_CHILDREN_BASIC
	if(generateContextBlocksVariables->testNumerosity)
	{
		string categoryListPropertyCountVariableName = NLCcodeBlockClass.generateCategoryListPropertyCountVariableName(entity);
		*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockIncrementIntVar(*currentCodeBlockInTree, categoryListPropertyCountVariableName);
	}
	#endif

	return result;
}	

#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN_SUBCLASSES
bool NLCtranslatorCodeBlocksOperationsClass::findNearestSubClassParentEntityCorrespondingToSubclassEntityInSameContext(GIAentityNode* subclassEntity, GIAentityNode** nearestSubclassParentEntity)
{
	bool foundNearestSubClassParentEntity = false;

	/*
	#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN_SUBCLASSES_MULTIPLE
	vector<string> subclassChildEntityNames;
	getSubclassChildEntityNames(parentEntity->entityName, &subclassChildEntityNames);
	#else
	*/
	string subclassParentEntityName = GIAentityNodeClass.getParentClassEntityNameFromSubClassEntityName(subclassEntity->entityName);	//eg line
	string subclassChildEntityName = GIAentityNodeClass.getChildClassEntityNameFromSubClassEntityName(subclassEntity->entityName);	//eg goal
						
	#ifdef GIA_CREATE_NON_SPECIFIC_CONCEPTS_FOR_ALL_NETWORK_INDEXES
	GIAentityNode* subclassEntityNetworkIndex = GIAtranslatorOperations.getNonspecificConceptEntityFromInstance(subclassEntity);	//eg eg goal_line	
	#else
	GIAentityNode* subclassEntityNetworkIndex = GIAtranslatorOperations.getPrimaryNetworkIndexNodeDefiningInstance(subclassEntity);	//eg goal_line
	#endif	
	if(subclassEntityNetworkIndex != NULL)
	{
		for(vector<GIAentityConnection*>::iterator definitionNodeListIterator = subclassEntityNetworkIndex->definitionNodeList->begin(); definitionNodeListIterator < subclassEntityNetworkIndex->definitionNodeList->end(); definitionNodeListIterator++)
		{
			GIAentityNode* subclassParentEntityNetworkIndex = getDefinitionRelationshipObjectEntity(*definitionNodeListIterator);
			#ifdef GIA_CREATE_NON_SPECIFIC_CONCEPTS_FOR_ALL_NETWORK_INDEXES
			subclassParentEntityNetworkIndex = GIAtranslatorOperations.getPrimaryNetworkIndexNodeDefiningInstance(subclassParentEntityNetworkIndex);
			#endif
			
			if(subclassParentEntityNetworkIndex->entityName == subclassParentEntityName)
			{			
				for(vector<GIAentityConnection*>::iterator iter = subclassParentEntityNetworkIndex->instanceNodeList->begin(); iter < subclassParentEntityNetworkIndex->instanceNodeList->end(); iter++)
				{
					GIAentityNode* subclassParentEntity = (*iter)->entity;	//eg line
					#ifdef GIA_CREATE_NON_SPECIFIC_CONCEPTS_FOR_ALL_NETWORK_INDEXES
					if(!(subclassParentEntity->entityType == GIA_ENTITY_TYPE_CONCEPT))
					{
					#endif
						GIAentityNode definiteEntityArtificial;
						definiteEntityArtificial.sentenceIndexTemp = subclassEntity->sentenceIndexTemp;
						#ifdef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES
						int indentationDifferenceMin = NLC_PREPROCESSOR_MAX_INDENTATION_LEVELS;
						#endif
						int indentationDifferenceFound = 0;
						//NB don't enforce indefinite condition for subclassParentEntity, just find the nearest legal reference to the subclass entity; definite or indefinite (OLD: isIndefiniteEntityCorrespondingToDefiniteEntityInSameContext)
						if(checkIndefiniteEntityCorrespondingToDefiniteEntityInSameContext(subclassParentEntity, &definiteEntityArtificial, &indentationDifferenceFound))
						{
							if(entityHasPropertyParent(subclassParentEntity, subclassChildEntityName))
							{
								#ifdef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES
								if(indentationDifferenceFound < indentationDifferenceMin)
								{
									//find the indefinite entity closest to the definite entity, as a subclass reference which has not been explicitly declared previously eg "goal line" (but only more generally declared; ie "line"), should refer to the most recent reference (ie line)
									indentationDifferenceMin = indentationDifferenceFound;
								#endif
									*nearestSubclassParentEntity = subclassParentEntity;
									foundNearestSubClassParentEntity = true;
								#ifdef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES
								}
								#endif
							}
						}
					#ifdef GIA_CREATE_NON_SPECIFIC_CONCEPTS_FOR_ALL_NETWORK_INDEXES
					}
					#endif
				}
			}
		}
	}
	else
	{
		cout << "NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN_SUBCLASSES generateContextBlocksCategories{} error: subclassEntity->isSubClass && subclassEntityNetworkIndex == NULL" << endl;
	}
	
	return foundNearestSubClassParentEntity;
}

bool NLCtranslatorCodeBlocksOperationsClass::entityHasPropertyParent(GIAentityNode* entity, const string propertyParentName)
{
	bool result = false;
	for(vector<GIAentityConnection*>::iterator iter = entity->propertyReverseNodeList->begin(); iter < entity->propertyReverseNodeList->end(); iter++)
	{
		GIAentityNode* propertyParentEntity = getPropertyRelationshipSubjectEntity(*iter);
		if(propertyParentEntity->entityName == propertyParentName)
		{
			result = true;
		}
	}
	return result;
}

bool NLCtranslatorCodeBlocksOperationsClass::createCodeBlockForStatementsForNearestSubClassParentReference(NLCcodeblock** currentCodeBlockInTree, NLCcodeblock** lastCodeBlockInTree, GIAentityNode* subclassEntity, GIAentityNode* nearestSubclassParentEntity, int sentenceIndex, NLCgenerateContextBlocksVariables* generateContextBlocksVariables, const bool generateContext, const string genericListAppendName)
{
	bool contextFound = false;
	//this code is from createCodeBlockForStatementsForDefinitionChildren{}:

	//context property item:		
	if(NLCcodeBlockClass.assumedToAlreadyHaveBeenDeclared(nearestSubclassParentEntity))
	{
		*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockForLocalList(*currentCodeBlockInTree, nearestSubclassParentEntity);
	}
	else
	{
		cerr << "NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN_SUBCLASSES: generateContextBlocksCategories{} error: !NLCcodeBlockClass.assumedToAlreadyHaveBeenDeclared(nearestSubclassParentEntity): subclassEntity = " << subclassEntity->entityName << ", nearestSubclassParentEntity = " << nearestSubclassParentEntity->entityName << endl;
		exit(EXIT_ERROR);
	}
	
	NLCcodeblock* tempCodeBlockInTree = *currentCodeBlockInTree;
	
	if(generateContext)
	{
		if(createCodeBlockForStatements(currentCodeBlockInTree, NLCitemClass.generateInstanceName(nearestSubclassParentEntity), subclassEntity, sentenceIndex, generateContextBlocksVariables))
		{
			contextFound = true;
		}
	}
	else
	{
		contextFound = true;
	}
				
	addEntityToCategoryList(currentCodeBlockInTree, subclassEntity, nearestSubclassParentEntity, genericListAppendName, generateContextBlocksVariables, sentenceIndex, true);

					
	*currentCodeBlockInTree = NLCcodeBlockClass.getLastCodeBlockInLevel(*lastCodeBlockInTree);
	*lastCodeBlockInTree = *currentCodeBlockInTree;
	
	
	return contextFound;
}

#endif

#endif

bool NLCtranslatorCodeBlocksOperationsClass::createCodeBlockForStatements(NLCcodeblock** currentCodeBlockInTree, string parentInstanceName, GIAentityNode* entity, int sentenceIndex, NLCgenerateContextBlocksVariables* generateContextBlocksVariables)
{
	bool result = false;
	 		
	//if object near a red car / if object has a red car (if object has a car which is red)
	//if(item->has(property) && item->has(property1) etc..){
	if(createCodeBlockForConnectionType(GIA_ENTITY_VECTOR_CONNECTION_TYPE_PROPERTY, currentCodeBlockInTree, parentInstanceName, entity, sentenceIndex, generateContextBlocksVariables))
	{
		result = true;
	}

	//if object near a car that is behind the driveway / if object has a car that is near the house
	//if(item > 3){		/	if(greaterthan(item, 3)){
	if(createCodeBlockForConnectionType(GIA_ENTITY_VECTOR_CONNECTION_TYPE_CONDITION, currentCodeBlockInTree, parentInstanceName, entity, sentenceIndex, generateContextBlocksVariables))
	{
		result = true;
	}
	
	#ifdef NLC_RECORD_ACTION_HISTORY
	//if object near a car that drives /if object has a car that drives
	if(createCodeBlockForConnectionType(GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTION, currentCodeBlockInTree, parentInstanceName, entity, sentenceIndex, generateContextBlocksVariables))
	{
		result = true;
	}

	//if object near a car that is towed by a truck / if object has a car that is towed by a truck
	if(createCodeBlockForConnectionType(GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTION_REVERSE, currentCodeBlockInTree, parentInstanceName, entity, sentenceIndex, generateContextBlocksVariables))
	{
		result = true;
	}
	#endif
	
	#ifdef NLC_TRANSLATOR_GENERATE_CONTEXT_BLOCKS_PARSE_DEFINITIONS
	//if object near a car that is an apple /if object has a car that is an apple
	if(createCodeBlockForConnectionType(GIA_ENTITY_VECTOR_CONNECTION_TYPE_DEFINITION, currentCodeBlockInTree, parentInstanceName, entity, sentenceIndex, generateContextBlocksVariables))
	{
		result = true;
	}	
	#endif

	/*
	//if object near Tom's carparentInstanceName
	currentCodeBlockInTree = createCodeBlockIfHasPropertyOwner(currentCodeBlockInTree, item, entity, sentenceIndex);
	*/
	return result;
}


bool NLCtranslatorCodeBlocksOperationsClass::sameReferenceSetReferencingConnectionCheck(const GIAentityConnection* targetConnection, const NLCgenerateContextBlocksVariables* generateContextBlocksVariables)
{
	bool sameReferenceSetReferencing = false;
	#ifdef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES
	if((targetConnection->isReference) || ((generateContextBlocksVariables->generateContextBlocksIfSameReferenceSet) && (targetConnection->sameReferenceSet)))	//NB isReference check is probably redundant given sameReferenceSet check
	#else
	if((generateContextBlocksVariables->generateContextBlocksIfSameReferenceSet) && (targetConnection->sameReferenceSet))
	#endif
	{
		sameReferenceSetReferencing = true;
	}
	return sameReferenceSetReferencing;
}
		
bool NLCtranslatorCodeBlocksOperationsClass::createCodeBlockForConnectionType(const int connectionType, NLCcodeblock** currentCodeBlockInTree, string parentInstanceName, GIAentityNode* entity, int sentenceIndex, NLCgenerateContextBlocksVariables* generateContextBlocksVariables)
{				
	bool result = false;
	
	for(vector<GIAentityConnection*>::iterator targetNodeListIterator = entity->entityVectorConnectionsArray[connectionType].begin(); targetNodeListIterator < entity->entityVectorConnectionsArray[connectionType].end(); targetNodeListIterator++)
	{
		GIAentityConnection* targetConnection = (*targetNodeListIterator);
		GIAentityNode* targetEntity = targetConnection->entity;
		//cout << "targetEntity->entityName = " << targetEntity->entityName  << endl;
		#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
		#ifdef NLC_SENTENCES_WITH_MULTIPLE_NON_SAME_REFERENCE_SET_CONNECTIONS
		if(((targetConnection->NLCparsedForCodeBlocks) && (sentenceIndex > targetConnection->sentenceIndexTemp)) || sameReferenceSetReferencingConnectionCheck(targetConnection, generateContextBlocksVariables) || !(generateContextBlocksVariables->onlyGenerateContextBlocksIfConnectionsParsedForNLCorSameReferenceSet))	//added option 1g13b/15-July-2014	//added option 1i2a 20-August-2014	//added option 1i3d 21-August-2014	//NB isReference check is probably redundant given sameReferenceSet check
		#else
		if((targetConnection->NLCparsedForCodeBlocks) || sameReferenceSetReferencingConnectionCheck(targetConnection, generateContextBlocksVariables) || !(generateContextBlocksVariables->onlyGenerateContextBlocksIfConnectionsParsedForNLCorSameReferenceSet))	//added option 1g13b/15-July-2014	//added option 1i2a 20-August-2014	//added option 1i3d 21-August-2014	//NB isReference check is probably redundant given sameReferenceSet check		
		#endif
		{
		#endif
			
			#ifdef NLC_TRANSLATOR_GENERATE_CONTEXT_BLOCKS_PARSE_PARENT_EFFICIENT
			if(!(generateContextBlocksVariables->parseParentEfficient) || (GIAtranslatorOperations.getRelationshipObjectEntity(targetConnection) != generateContextBlocksVariables->childEntityNotToParse))
			{
			#endif
				#ifdef NLC_NORMALISE_TWOWAY_PREPOSITIONS_DUAL_CONDITION_LINKS_ENABLED
				if(!(targetEntity->inverseConditionTwoWay) || targetConnection->isReference)	//prevent infinite loop for 2 way conditions
				{
				#endif
					if(NLCcodeBlockClass.checkSentenceIndexParsingCodeBlocks(targetEntity, targetConnection, sentenceIndex, false))	//changed from true to false 1e5b	//generateContextBlocksVariables->checkSameSentenceConnection
					{//only write conditions that are explicated in current sentence


						bool resultTemp = false;
						bool generateContextForObject = false;
						GIAentityNode* objectEntity = NULL;

						#ifdef NLC_REFERENCING_WILD_CARDS
						NLCcodeblock* currentCodeBlockInTreeBeforeParsingConnection = *currentCodeBlockInTree;
						#endif

						if(connectionType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_PROPERTY)
						{
							if(createCodeBlockForGivenProperty(currentCodeBlockInTree, parentInstanceName, targetEntity, sentenceIndex, generateContextBlocksVariables, &objectEntity, &generateContextForObject))
							{
								resultTemp = true;
							}
						}
						else if(connectionType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_CONDITION)
						{
							if(createCodeBlockForGivenCondition(currentCodeBlockInTree, parentInstanceName, targetEntity, sentenceIndex, generateContextBlocksVariables, &objectEntity, &generateContextForObject))
							{
								resultTemp = true;
							}
						}
						#ifdef NLC_RECORD_ACTION_HISTORY
						else if(connectionType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTION)
						{
							if(createCodeBlockForGivenAction(currentCodeBlockInTree, parentInstanceName, targetEntity, sentenceIndex, generateContextBlocksVariables, &objectEntity, &generateContextForObject))
							{
								resultTemp = true;
							}
						}
						else if(connectionType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTION_REVERSE)
						{
							if(createCodeBlockForGivenActionIncoming(currentCodeBlockInTree, parentInstanceName, targetEntity, sentenceIndex, generateContextBlocksVariables, &objectEntity, &generateContextForObject))
							{
								resultTemp = true;
							}
						}
						#endif
						#ifdef NLC_TRANSLATOR_GENERATE_CONTEXT_BLOCKS_PARSE_DEFINITIONS
						else if(connectionType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_DEFINITION)
						{	
							#ifdef NLC_ADVANCED_REFERENCING_SUPPORT_ALIASES
							if(GIAtranslatorOperations.connectionIsAlias(targetConnection))
							{
								if(createCodeBlockForGivenAlias(currentCodeBlockInTree, entity, targetEntity, sentenceIndex, generateContextBlocksVariables, &objectEntity, &generateContextForObject))
								{
									resultTemp = true;
								}
							}
							else
							{
							#endif
								if(createCodeBlockForGivenDefinition(currentCodeBlockInTree, parentInstanceName, targetEntity, sentenceIndex, generateContextBlocksVariables, &objectEntity, &generateContextForObject))
								{
									resultTemp = true;
								}
							#ifdef NLC_ADVANCED_REFERENCING_SUPPORT_ALIASES	
							}
							#endif
						}
						#endif
						if(resultTemp)
						{
							result = true;
							targetConnection->NLCparsedForCodeBlocks = true;

							if(generateContextForObject)
							{
								#ifdef NLC_REFERENCING_WILD_CARDS
								if(SHAREDvars.textInTextArray(objectEntity->entityName, giaReferencingWildCardSubstanceArray, GIA_REFERENCING_WILD_CARDS_SUBSTANCES_NUMBER_OF_TYPES))
								{
									*currentCodeBlockInTree = NLCcodeBlockClass.clearCodeBlock(currentCodeBlockInTreeBeforeParsingConnection);
								}
								else
								{
								#endif
									#ifdef NLC_RECORD_ACTION_HISTORY
									if((connectionType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTION) || (connectionType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTION_REVERSE))
									{
										targetEntity->NLCcontextGeneratedTemp = true;
									}
									#endif	

									#ifdef NLC_TRANSLATOR_GENERATE_CONTEXT_BLOCKS_PARSE_PARENT_OF_TARGET_AND_MULTIPLE_DEFINITE_ENTITIES
									bool verifyObject = false;
									bool foundParentEntityNew = false;
									GIAentityNode* parentEntityNew = NULL;

									bool parseConditionParents = NLC_PARSE_CONDITION_PARENTS_DEFAULT_VALUE;
									bool checkIsDefinite = false;	//CHECKTHIS; support isolated definite objects, indefinite parents, and definite parents; eg 1. "the chicken that is next to the pie." , 2. "the chicken that is next to a dog's pie." and 3. "the chicken that is next to the dog's pie."
									parentEntityNew = getSameReferenceSetUniqueParent(objectEntity, sentenceIndex, entity, &foundParentEntityNew, parseConditionParents, checkIsDefinite);
									if(NLCcodeBlockClass.isDefiniteEntity(objectEntity) || foundParentEntityNew)	//ie objectEntity is explicitly or implicitly definite
									{
										if(!(objectEntity->entityType == GIA_ENTITY_TYPE_QUALITY))	//added 1n24a
										{
											verifyObject = true;
										}
									}

									if(verifyObject)
									{

										//save objectEntity as tempVariable objectEntityCandidate
										string candidateObjectClassName = NLCitemClass.generateClassName(objectEntity);
										string candidateObjectInstanceName = generateCandidateObjectName(objectEntity);
										*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockDeclareTempVariableAndSetToEntity(*currentCodeBlockInTree, candidateObjectClassName, candidateObjectInstanceName, objectEntity);

										//NB this code is based on generateContextForChildEntity{}: it requires NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN, NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_FOR_EACH_CHILD and NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_FOR_EACH_CHILD_GET_PARENT
										bool generatedContextForChild = false;
										if(foundParentEntityNew)
										{
											if(generateContextBlocksForParentEntity(currentCodeBlockInTree, objectEntity, parentEntityNew, sentenceIndex, generateContextBlocksVariables))
											{
												generatedContextForChild = true;
											}
											else
											{
												cout << "createCodeBlockForConnectionType{}: generateContextBlocksForParentEntity{} error: !generatedContextForChild" << endl;
											}
										}
										if(generateContextBlocks(currentCodeBlockInTree, objectEntity, sentenceIndex, generateContextBlocksVariables, generatedContextForChild, NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION))
										{

										}

										//now verify that objectEntity == objectEntityCandidate
										*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockIfTempVariableEqualsEntity(*currentCodeBlockInTree, candidateObjectClassName, candidateObjectInstanceName, objectEntity);
									}
									else
									{	//CHECKTHIS; support isolated indefinite objects; eg 4. "the chicken that is next to a pie."
									#endif
										createCodeBlockForStatements(currentCodeBlockInTree, NLCitemClass.generateInstanceName(objectEntity), objectEntity, sentenceIndex, generateContextBlocksVariables);
									#ifdef NLC_TRANSLATOR_GENERATE_CONTEXT_BLOCKS_PARSE_PARENT_OF_TARGET_AND_MULTIPLE_DEFINITE_ENTITIES
									}
									#endif

									#ifdef NLC_RECORD_ACTION_HISTORY
									if((connectionType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTION) || (connectionType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTION_REVERSE))
									{
										targetEntity->NLCcontextGeneratedTemp = false;
									}
									#endif	
								#ifdef NLC_REFERENCING_WILD_CARDS
								}
								#endif
							}							
						}					
					}
				#ifdef NLC_NORMALISE_TWOWAY_PREPOSITIONS_DUAL_CONDITION_LINKS_ENABLED
				}
				#endif
			#ifdef NLC_TRANSLATOR_GENERATE_CONTEXT_BLOCKS_PARSE_PARENT_EFFICIENT
			}
			#endif
		#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
		}
		#endif
	}
	
	return result;
}

#ifdef NLC_TRANSLATOR_GENERATE_CONTEXT_BLOCKS_PARSE_PARENT_OF_TARGET_AND_MULTIPLE_DEFINITE_ENTITIES
string NLCtranslatorCodeBlocksOperationsClass::generateCandidateObjectName(const GIAentityNode* objectEntity)
{
	string candidateObjectName = objectEntity->entityName + NLC_TRANSLATOR_GENERATE_CONTEXT_BLOCKS_PARSE_PARENT_OF_TARGET_AND_MULTIPLE_DEFINITE_ENTITIES_CANDIDATE_OBJECT_NAME_PREPEND;
	return candidateObjectName;
}
#endif
	
bool NLCtranslatorCodeBlocksOperationsClass::createCodeBlockForGivenProperty(NLCcodeblock** currentCodeBlockInTree, string parentInstanceName, GIAentityNode* propertyRelationshipEntity, const int sentenceIndex, NLCgenerateContextBlocksVariables* generateContextBlocksVariables, constEffective GIAentityNode** objectEntity, bool* generateContextForObject)
{
	bool result = true;
	GIAentityNode* propertyRelationshipObjectEntity = GIAtranslatorOperations.getPropertyRelationshipTargetEntity(propertyRelationshipEntity);

	*generateContextForObject = true;

	#ifdef NLC_TRANSLATOR_LOGICAL_CONDITIONS_BOOLEAN_STATEMENTS_INTERPRET_SUBJECT_AND_OBJECT_INDEPENDENTLY
	if(generateContextBlocksVariables->secondaryComparison)
	{
		secondaryComparisonSetIDinstance(propertyRelationshipObjectEntity);
	}
	#endif
				
	#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
	propertyRelationshipObjectEntity->NLCcontextGenerated = true;	//added 1g14b 15-July-2014
	#endif
	
	*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockForOrInPropertyList(*currentCodeBlockInTree, propertyRelationshipObjectEntity, parentInstanceName);


	#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
	#ifdef GIA_ADD_ARTIFICIAL_AUXILIARY_FOR_ALL_PROPERTIES_AND_DEFINITIONS
	if(propertyRelationshipEntity->negative || ((propertyRelationshipObjectEntity->entityType == GIA_ENTITY_TYPE_QUALITY) && propertyRelationshipObjectEntity->negative))	//NB NLP/GIA will assign the negative to the property relationship object for qualities (e.g. x is not red)
	#else
	if(propertyRelationshipObjectEntity->negative)	
	#endif
	{
		generateContextBlocksVariables->negativeDetectedInContextBlocks = true;
	}
	#endif
	#ifdef NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY_CHILDREN_BASIC
	if(generateContextBlocksVariables->testNumerosity)
	{
		if(checkNumerosity(propertyRelationshipObjectEntity))
		{
			generateContextBlocksVariables->childQuantity = propertyRelationshipObjectEntity->quantityNumber;
		}
	}
	#endif
	
	/*
	createCodeBlockForStatements(currentCodeBlockInTree, generateInstanceName(propertyRelationshipObjectEntity), propertyRelationshipObjectEntity, sentenceIndex, generateContextBlocksVariables);
	*/
	*objectEntity = propertyRelationshipObjectEntity;
					
	return result;
}

bool NLCtranslatorCodeBlocksOperationsClass::createCodeBlockForGivenCondition(NLCcodeblock** currentCodeBlockInTree, const string parentInstanceName, GIAentityNode* conditionRelationshipEntity, const int sentenceIndex, NLCgenerateContextBlocksVariables* generateContextBlocksVariables, GIAentityNode** objectEntity, bool* generateContextForObject)
{
	bool result = false;

	
	if(!(conditionRelationshipEntity->relationshipObjectEntity->empty()))
	{		
		result = true;	

		GIAentityNode* conditionRelationshipObjectEntity = (conditionRelationshipEntity->relationshipObjectEntity->back())->entity;

		#ifdef NLC_TRANSLATOR_LOGICAL_CONDITIONS_BOOLEAN_STATEMENTS_INTERPRET_SUBJECT_AND_OBJECT_INDEPENDENTLY
		if(generateContextBlocksVariables->secondaryComparison)
		{
			secondaryComparisonSetIDinstance(conditionRelationshipObjectEntity);
		}
		#endif

		*generateContextForObject = true;

		#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
		conditionRelationshipObjectEntity->NLCcontextGenerated = true;	//added 1g14b 15-July-2014
		#endif

		*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockForConditionList(*currentCodeBlockInTree, conditionRelationshipEntity, conditionRelationshipObjectEntity, parentInstanceName);


		#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
		if(conditionRelationshipEntity->negative)
		{
			generateContextBlocksVariables->negativeDetectedInContextBlocks = true;
		}
		#endif
		#ifdef NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY_CHILDREN_BASIC
		if(generateContextBlocksVariables->testNumerosity)
		{
			if(checkNumerosity(conditionRelationshipObjectEntity))
			{
				generateContextBlocksVariables->childQuantity = conditionRelationshipObjectEntity->quantityNumber;
			}
		}
		#endif

		/*
		createCodeBlockForStatements(currentCodeBlockInTree, generateInstanceName(conditionRelationshipObjectEntity), conditionRelationshipObjectEntity, sentenceIndex, generateContextBlocksVariables);
		*/
		*objectEntity = conditionRelationshipObjectEntity;
	}
	else
	{
		result = false;
		cout << "error createCodeBlockForGivenCondition{}: condition does not have object" << endl;
	}
	
	return result;
}

#ifdef NLC_RECORD_ACTION_HISTORY
bool NLCtranslatorCodeBlocksOperationsClass::createCodeBlockForGivenAction(NLCcodeblock** currentCodeBlockInTree, const string parentInstanceName, GIAentityNode* actionRelationshipEntity, const int sentenceIndex, NLCgenerateContextBlocksVariables* generateContextBlocksVariables, GIAentityNode** objectEntity, bool* generateContextForObject)
{
	bool result = false;

	if(!(actionRelationshipEntity->NLCcontextGeneratedTemp))
	{
		result = true;
		
		#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
		actionRelationshipEntity->NLCcontextGenerated = true;
		#endif

		*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockForActionList(*currentCodeBlockInTree, actionRelationshipEntity, parentInstanceName);	


		#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
		if(actionRelationshipEntity->negative)
		{
			generateContextBlocksVariables->negativeDetectedInContextBlocks = true;
		}
		#endif
			
		bool hasActionObject = false;
		if(!(actionRelationshipEntity->relationshipObjectEntity->empty()))
		{
			*generateContextForObject = true;
			
			GIAentityNode* actionRelationshipObjectEntity = (actionRelationshipEntity->relationshipObjectEntity->back())->entity;
	
			#ifdef NLC_TRANSLATOR_LOGICAL_CONDITIONS_BOOLEAN_STATEMENTS_INTERPRET_SUBJECT_AND_OBJECT_INDEPENDENTLY
			if(generateContextBlocksVariables->secondaryComparison)
			{
				secondaryComparisonSetIDinstance(actionRelationshipObjectEntity);
			}
			#endif
			
			#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
			actionRelationshipObjectEntity->NLCcontextGenerated = true;
			#endif
			#ifdef NLC_RECORD_ACTION_HISTORY_COMPENSATE_FOR_EFFECTIVE_DEFINITE_ENTITIES_IMPLEMENTATION1
			actionRelationshipObjectEntity->grammaticalDefiniteTemp = true;
			#endif

			hasActionObject = true;
			*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockForActionObjectList(*currentCodeBlockInTree, actionRelationshipObjectEntity, actionRelationshipEntity);

			/*
			actionRelationshipEntity->NLCcontextGeneratedTemp = true;
			createCodeBlockForStatements{currentCodeBlockInTree, generateInstanceName{actionRelationshipObjectEntity}, actionRelationshipObjectEntity, sentenceIndex, generateContextBlocksVariables};	//OLD: generateInstanceName{actionRelationshipEntity}
			actionRelationshipEntity->NLCcontextGeneratedTemp = false;
			*/
			*objectEntity = actionRelationshipObjectEntity;
		}
	}

	return result;
}

bool NLCtranslatorCodeBlocksOperationsClass::createCodeBlockForGivenActionIncoming(NLCcodeblock** currentCodeBlockInTree, const string parentInstanceName, GIAentityNode* actionRelationshipEntity, const int sentenceIndex, NLCgenerateContextBlocksVariables* generateContextBlocksVariables, GIAentityNode** objectEntity, bool* generateContextForObject)
{
	bool result = false;
	
	if(!(actionRelationshipEntity->NLCcontextGeneratedTemp))
	{
		result = true;
		
		#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
		actionRelationshipEntity->NLCcontextGenerated = true;
		#endif
		
		*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockForActionIncomingList(*currentCodeBlockInTree, actionRelationshipEntity, parentInstanceName);	


		#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
		if(actionRelationshipEntity->negative)
		{
			generateContextBlocksVariables->negativeDetectedInContextBlocks = true;
		}
		#endif
		
		bool hasActionSubject = false;
		if(!(actionRelationshipEntity->relationshipSubjectEntity->empty()))
		{
			*generateContextForObject = true;
			
			GIAentityNode* actionRelationshipSubjectEntity = (actionRelationshipEntity->relationshipSubjectEntity->back())->entity;
			
			#ifdef NLC_TRANSLATOR_LOGICAL_CONDITIONS_BOOLEAN_STATEMENTS_INTERPRET_SUBJECT_AND_OBJECT_INDEPENDENTLY
			if(generateContextBlocksVariables->secondaryComparison)
			{
				secondaryComparisonSetIDinstance(actionRelationshipSubjectEntity);
			}
			#endif
	
			#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
			actionRelationshipSubjectEntity->NLCcontextGenerated = true;
			#endif
			#ifdef NLC_RECORD_ACTION_HISTORY_COMPENSATE_FOR_EFFECTIVE_DEFINITE_ENTITIES_IMPLEMENTATION1
			actionRelationshipSubjectEntity->grammaticalDefiniteTemp = true;
			#endif
		
			hasActionSubject = true;
			*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockForActionSubjectList(*currentCodeBlockInTree, actionRelationshipSubjectEntity, actionRelationshipEntity);
			
			/*
			actionRelationshipEntity->NLCcontextGeneratedTemp = true;
			createCodeBlockForStatements(currentCodeBlockInTree, generateInstanceName(actionRelationshipSubjectEntity), actionRelationshipSubjectEntity, sentenceIndex, generateContextBlocksVariables);	//OLD: generateInstanceName(actionRelationshipEntity)
			actionRelationshipEntity->NLCcontextGeneratedTemp = false;
			*/
			*objectEntity = actionRelationshipSubjectEntity;
		}
	}
						
	return result;
}
#endif
#ifdef NLC_TRANSLATOR_GENERATE_CONTEXT_BLOCKS_PARSE_DEFINITIONS
bool NLCtranslatorCodeBlocksOperationsClass::createCodeBlockForGivenDefinition(NLCcodeblock** currentCodeBlockInTree, const string parentInstanceName, GIAentityNode* definitionRelationshipEntity, const int sentenceIndex, const NLCgenerateContextBlocksVariables* generateContextBlocksVariables, constEffective GIAentityNode** objectEntity, bool* generateContextForObject)
{
	bool result = true;
	GIAentityNode* definitionRelationshipObjectEntity = GIAtranslatorOperations.getDefinitionRelationshipTargetEntity(definitionRelationshipEntity);

	*generateContextForObject = true;
	
	#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
	definitionRelationshipObjectEntity->NLCcontextGenerated = true;
	#endif
	
	*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockCheckParentClassNameExecuteFunction1(*currentCodeBlockInTree, parentInstanceName, definitionRelationshipObjectEntity->entityName);
					
	
	/*
	createCodeBlockForStatements(currentCodeBlockInTree, parentInstanceName, definitionRelationshipObjectEntity, sentenceIndex, generateContextBlocksVariables);	//creates for statements (generates context) according to the properties/conditions of the concept (assuming it is a specific networkIndex eg "blue" in "if the boat is a blue chicken")
	*/
	*objectEntity = definitionRelationshipObjectEntity;
				
	return result;
}
#ifdef NLC_ADVANCED_REFERENCING_SUPPORT_ALIASES	
bool NLCtranslatorCodeBlocksOperationsClass::createCodeBlockForGivenAlias(NLCcodeblock** currentCodeBlockInTree, const GIAentityNode* entity, GIAentityNode* definitionRelationshipEntity, const int sentenceIndex, const NLCgenerateContextBlocksVariables* generateContextBlocksVariables, constEffective GIAentityNode** objectEntity, bool* generateContextForObject)
{
	bool result = true;	
	GIAentityNode* definitionRelationshipObjectEntity = GIAtranslatorOperations.getDefinitionRelationshipTargetEntity(definitionRelationshipEntity);
	
	*generateContextForObject = false;	//do not parse context past alias definition links
	
	#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE
	definitionRelationshipObjectEntity->NLCcontextGenerated = true;
	#endif
	
	string aliasName = definitionRelationshipObjectEntity->entityName;
	
	/*FUTURE CHECK alias has been added to definition entity?;
	if(findAliasInEntity(definitionRelationshipObjectEntity, &aliasName)
	{
	*/
		
	*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlocksFindAliasExecuteFunction(*currentCodeBlockInTree, aliasName, entity);


	return result;
}
#endif
#endif





































bool NLCtranslatorCodeBlocksOperationsClass::getParentAndInitialiseParentIfNecessary(NLCcodeblock** currentCodeBlockInTree, GIAentityNode* currentEntity, int sentenceIndex, NLCgenerateContextBlocksVariables* generateContextBlocksVariables, bool parseLogicalConditions, GIAentityNode** parentEntity, bool* newInitialisation)
{
	bool result = false;
	
	*parentEntity = getParent(currentEntity, sentenceIndex, generateContextBlocksVariables);
	
	
	if(NLCcodeBlockClass.checkSentenceIndexParsingCodeBlocks(currentEntity, sentenceIndex, false))
	{//is this required?


		#ifdef NLC_TRANSLATOR_LOGICAL_CONDITIONS_BOOLEAN_STATEMENTS_INTERPRET_SUBJECT_AND_OBJECT_INDEPENDENTLY
		if(generateContextBlocksVariables->logicalConditionStatement)
		{
			parseLogicalConditions = true;	//prevents initialisation of indefinite entities in logical comditions
		}
		#endif
		if(generateParentInitialisationCodeBlockWithChecks(currentCodeBlockInTree, *parentEntity, sentenceIndex, parseLogicalConditions, false))
		{
			
			result = true;
			*newInitialisation = true;
			//eg "barrel" in "A chicken's barrel eats the bike."
		}
	}
	
	return result;
}



bool NLCtranslatorCodeBlocksOperationsClass::getParentAndInitialiseParentIfNecessaryAndGenerateContextBlocks(NLCcodeblock** currentCodeBlockInTree, GIAentityNode* currentEntity, int sentenceIndex, NLCgenerateContextBlocksVariables* generateContextBlocksVariables, bool parseLogicalConditions, GIAentityNode** parentEntity, bool* newInitialisation)
{
	bool result = false;
	
	*parentEntity = getParent(currentEntity, sentenceIndex, generateContextBlocksVariables);
	
	
	if(NLCcodeBlockClass.checkSentenceIndexParsingCodeBlocks(currentEntity, sentenceIndex, false))
	{//is this required?


		#ifdef NLC_TRANSLATOR_LOGICAL_CONDITIONS_BOOLEAN_STATEMENTS_INTERPRET_SUBJECT_AND_OBJECT_INDEPENDENTLY
		if(generateContextBlocksVariables->logicalConditionStatement)
		{
			parseLogicalConditions = true;	//prevents initialisation of indefinite entities in logical comditions
		}
		#endif
		if(generateParentInitialisationCodeBlockWithChecks(currentCodeBlockInTree, *parentEntity, sentenceIndex, parseLogicalConditions, false))
		{
			
			result = true;
			*newInitialisation = true;
			//eg "barrel" in "A chicken's barrel eats the bike."
			
			if(*parentEntity == currentEntity)
			{				
				#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_BLOCKS_FOR_PARENT_INITIALISATION_SPECIAL
				*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockForCategoryList(*currentCodeBlockInTree, currentEntity, NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION, sentenceIndex);
				#else
				*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockForLocalList(*currentCodeBlockInTree, currentEntity);
				#endif
			}
			else
			{//case added 1n25a
				#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_BLOCKS_FOR_PARENT_INITIALISATION_SPECIAL
				*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockForCategoryList(*currentCodeBlockInTree, *parentEntity, NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION, sentenceIndex);
				#else
				*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockForLocalList(*currentCodeBlockInTree, *parentEntity);
				#endif
				*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockForOrInPropertyList(*currentCodeBlockInTree, currentEntity, NLCitemClass.generateInstanceName(*parentEntity));	
			}
		}
		else
		{

			#ifdef NLC_GENERATE_TYPE_LISTS
			bool parseTypeList = false;
			#endif
			#ifdef NLC_TRANSLATOR_LOGICAL_CONDITIONS_BOOLEAN_STATEMENTS_INTERPRET_SUBJECT_AND_OBJECT_INDEPENDENTLY_SUPPORT_INDEFINITE
			if(generateContextBlocksVariables->logicalConditionStatement)
			{
				if(!NLCcodeBlockClass.isDefiniteEntityStrict(*parentEntity))
				{
					//code copied from generateCodeBlocksFromMathTextNLPparsablePhrase

					//eg "If a house is green, do this
					#ifdef NLC_GENERATE_TYPE_LISTS
					parseTypeList = true;
					#else
					(*parentEntity)->NLClocalListVariableHasBeenInitialised = true;		//added 1n22b
					#endif
				}
			}
			#endif
			#ifdef NLC_GENERATE_TYPE_LISTS
			#ifdef GIA_ADVANCED_REFERENCING_PREVENT_REFERENCING_OF_ENTITIES_WITH_PREDETERMINERS
			if(NLCitemClass.detectPredeterminer(*parentEntity, sentenceIndex))
			{
				parseTypeList = true;	//added 1v9c
				(*parentEntity)->grammaticalDefiniteTemp = false;
			}
			#endif
			#ifdef GIA_ADVANCED_REFERENCING_PREVENT_REFERENCING_OF_PLURAL_ENTITIES
			if((*parentEntity)->grammaticalNumber == GRAMMATICAL_NUMBER_PLURAL)
			{	
				parseTypeList = true;	//added 1v9c
				(*parentEntity)->grammaticalDefiniteTemp = false;
			}
			#endif
			if(parseTypeList)
			{
				*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockForPropertyTypeClass(*currentCodeBlockInTree, *parentEntity);
			}
			#endif

			if(generateContextForChildEntity(currentCodeBlockInTree, NULL, currentEntity, sentenceIndex, true, generateContextBlocksVariables))	//NB parent entity parameter is set to NULL such that it can be obtained by getSameReferenceSetUniqueParent()
			{
				result = true;
			}
		}
	}
	
	return result;

}

bool NLCtranslatorCodeBlocksOperationsClass::generateParentInitialisationCodeBlockWithChecks(NLCcodeblock** currentCodeBlockInTree, GIAentityNode* parentEntity, int sentenceIndex, const bool parseLogicalConditions, const bool testOnly)
{
	bool result = false;
	

	#ifdef NLC_TRANSLATOR_LOGICAL_CONDITIONS_BOOLEAN_STATEMENTS_INTERPRET_SUBJECT_AND_OBJECT_INDEPENDENTLY
	if(!parseLogicalConditions)
	{
	#endif
		//moved here 1e8a (out of generateObjectInitialisationsBasedOnPropertiesAndConditions)
		//added 1e6c: eg A chicken's hat has a bike. / A blue dog has a bike.
		if(!checkNetworkIndexTypeEntity(parentEntity)) //OLD 1n: if(!checkSpecialCaseEntity(parentEntity, true))
		{
			if(!(parentEntity->NLCparsedForCodeBlocks))	// && !(entity->parsedForNLCcodeBlocksActionRound)
			{
				if(!NLCcodeBlockClass.assumedToAlreadyHaveBeenDeclared(parentEntity))
				{
					#ifndef NLC_DEFINE_LOCAL_VARIABLES_FOR_ALL_INDEFINATE_ENTITIES
					if(NLCcodeBlockClass.checkSentenceIndexParsingCodeBlocks(parentEntity, sentenceIndex, false))	//this is redundant with NLC_DEFINE_LOCAL_VARIABLES_FOR_ALL_INDEFINATE_ENTITIES
					{
					#endif
						#ifdef NLC_VERIFY_CONNECTIONS_SENTENCE_INDEX
						if(parentEntity->sentenceIndexTemp == sentenceIndex)	//ie "wasReference" is not a sufficient condition to initialise parent
						{
						#endif
							#ifdef NLC_RECORD_ACTION_HISTORY_GENERALISABLE
							if(!(parentEntity->NLCcontextGenerated))	//added 1l3b
							{
							#endif
								result = true;
								if(!testOnly)
								{
									generateObjectInitialisations(currentCodeBlockInTree, parentEntity, sentenceIndex);
								}
							#ifdef NLC_RECORD_ACTION_HISTORY_GENERALISABLE
							}		
							#endif								
						#ifdef NLC_VERIFY_CONNECTIONS_SENTENCE_INDEX
						}
						#endif
					#ifndef NLC_DEFINE_LOCAL_VARIABLES_FOR_ALL_INDEFINATE_ENTITIES
					}
					#endif
				}
			}
		}
	#ifdef NLC_TRANSLATOR_LOGICAL_CONDITIONS_BOOLEAN_STATEMENTS_INTERPRET_SUBJECT_AND_OBJECT_INDEPENDENTLY
	}
	#endif	

	return result;
}

bool NLCtranslatorCodeBlocksOperationsClass::generateObjectInitialisations(NLCcodeblock** currentCodeBlockInTree, GIAentityNode* entity, int sentenceIndex)
{
	bool result = true;

	
	NLCcodeblock* codeBlockInTreeBeforeGenerateParentInitialisation = *currentCodeBlockInTree;
	
	*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlocksCreateNewLocalListVariable(*currentCodeBlockInTree, entity, sentenceIndex);

	entity->NLCparsedForCodeBlocks = true;
	entity->NLClocalListVariableHasBeenInitialised = true;
	
	#ifdef NLC_GENERATE_OBJECT_INITIALISATIONS_BASED_ON_CONCEPTS
	//Part 2b: generate object initialisations based on concepts (class inheritance)
	generateObjectInitialisationsBasedOnConcepts(entity, entity, currentCodeBlockInTree, sentenceIndex, true);
	#endif

	//*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockDebug(*currentCodeBlockInTree, string("generateObjectInitialisations{}: ") + entity->entityName);

	NLCcodeblock* codeBlockInTreeBeforeGenerateObjectInitialisations = *currentCodeBlockInTree;
	#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_BLOCKS_FOR_PARENT_INITIALISATION_SPECIAL	//CHECKTHIS
	*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockForCategoryList(*currentCodeBlockInTree, entity, NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION, sentenceIndex);
	#else
	*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockForLocalList(*currentCodeBlockInTree, entity);
	#endif
	
	#ifdef NLC_TRANSLATOR_INTERPRET_PROPERNOUNS_WITH_DEFINITION_LINK_AS_NEWLY_DECLARED
	#ifdef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES
	entity->NLCfirstInstanceOfProperNounInContext = false;	//so that the entity will no longer be interpreted as a new declaration by isDefiniteEntity
	#endif
	#endif

	bool addObject = false;
	//a ball that has a car...
	if(generateObjectInitialisationsForConnectionType(currentCodeBlockInTree, GIA_ENTITY_VECTOR_CONNECTION_TYPE_PROPERTY, entity, sentenceIndex))
	{
		addObject = true;
	}
	//a ball which is near a car
	if(generateObjectInitialisationsForConnectionType(currentCodeBlockInTree, GIA_ENTITY_VECTOR_CONNECTION_TYPE_CONDITION, entity, sentenceIndex))
	{
		addObject = true;
	}
	#ifdef NLC_RECORD_ACTION_HISTORY
	//a ball which drives a car...
	if(generateObjectInitialisationsForConnectionType(currentCodeBlockInTree, GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTION, entity, sentenceIndex))
	{
		addObject = true;
	}
	//a ball which is driven by a car
	if(generateObjectInitialisationsForConnectionType(currentCodeBlockInTree, GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTION_REVERSE, entity, sentenceIndex))
	{
		addObject = true;
	}
	#endif
	#ifdef NLC_REDEFINITIONS
	//a ball which is a car
	if(generateObjectInitialisationsForConnectionType(currentCodeBlockInTree, GIA_ENTITY_VECTOR_CONNECTION_TYPE_DEFINITION, entity, sentenceIndex))
	{
		addObject = true;
	}	
	#endif
	
	if(!addObject)
	{
		*currentCodeBlockInTree = NLCcodeBlockClass.clearCodeBlock(codeBlockInTreeBeforeGenerateObjectInitialisations);
	}
	
	*currentCodeBlockInTree = NLCcodeBlockClass.getLastCodeBlockInLevel(codeBlockInTreeBeforeGenerateParentInitialisation);
	
	return result;
}
	
bool NLCtranslatorCodeBlocksOperationsClass::generateObjectInitialisationsForConnectionType(NLCcodeblock** currentCodeBlockInTree, const int connectionType, GIAentityNode* entity, int sentenceIndex)
{
	bool result = false;
	for(vector<GIAentityConnection*>::iterator targetNodeListIterator = entity->entityVectorConnectionsArray[connectionType].begin(); targetNodeListIterator < entity->entityVectorConnectionsArray[connectionType].end(); targetNodeListIterator++)
	{
		GIAentityConnection* targetConnection = *targetNodeListIterator;
		GIAentityNode* targetEntity = targetConnection->entity;
		if(NLCcodeBlockClass.checkSentenceIndexParsingCodeBlocks(targetEntity, targetConnection, sentenceIndex, false))
		{
			if(targetConnection->sameReferenceSet)
			{
				if(!(targetEntity->NLCcontextGeneratedTemp))
				{
					bool addObject = false;
					GIAentityNode* actionOrConditionRelationshipEntity = NULL;
					GIAentityNode* objectEntity = NULL;
					GIAentityNode* subjectEntity = NULL;
					bool foundObject = false;
					bool foundSubject = false;
					bool recurse = false;
					GIAentityNode* recurseEntity = NULL;
					if(connectionType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_PROPERTY)
					{
						//foundSubject = true;
						foundObject = true;
						subjectEntity = entity;
						objectEntity = GIAtranslatorOperations.getPropertyRelationshipObjectEntity(targetConnection);
						recurse = true;
						recurseEntity = objectEntity;
						addObject = true;

					}
					else if(connectionType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_CONDITION)
					{
						GIAentityConnection* conditionObjectConnection = NULL;
						if(getEntityCheckSameReferenceSetAndSentence(targetEntity, &objectEntity, &conditionObjectConnection, sentenceIndex, true, GIA_ENTITY_VECTOR_CONNECTION_TYPE_RELATIONSHIP_OBJECT))
						{
							foundSubject = true;
							subjectEntity = entity;
							actionOrConditionRelationshipEntity = targetEntity;

							foundObject = true;
							recurse = true;
							recurseEntity = objectEntity;

							addObject = true;
						}
					}
					#ifdef NLC_RECORD_ACTION_HISTORY
					else if(connectionType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTION)
					{
						#ifdef NLC_RECORD_ACTION_HISTORY_EXTENDED
						foundSubject = true;
						#endif
						subjectEntity = entity;
						actionOrConditionRelationshipEntity = targetEntity;
						GIAentityConnection* actionObjectConnection = NULL;
						if(getEntityCheckSameReferenceSetAndSentence(targetEntity, &objectEntity, &actionObjectConnection, sentenceIndex, true, GIA_ENTITY_VECTOR_CONNECTION_TYPE_RELATIONSHIP_OBJECT))
						{
							foundObject = true;
							recurse = true;
							recurseEntity = objectEntity;
						}
						addObject = true;
					}
					else if(connectionType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTION_REVERSE)
					{
						#ifdef NLC_RECORD_ACTION_HISTORY_EXTENDED
						foundObject = true;
						#endif
						objectEntity = entity;
						actionOrConditionRelationshipEntity = targetEntity;
						GIAentityConnection* actionSubjectConnection = NULL;
						if(getEntityCheckSameReferenceSetAndSentence(targetEntity, &subjectEntity, &actionSubjectConnection, sentenceIndex, true, GIA_ENTITY_VECTOR_CONNECTION_TYPE_RELATIONSHIP_SUBJECT))
						{
							foundSubject = true;
							recurse = true;
							recurseEntity = subjectEntity;
						}
						addObject = true;
					}
					#endif
					#ifdef NLC_TRANSLATOR_GENERATE_CONTEXT_BLOCKS_PARSE_DEFINITIONS
					else if(connectionType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_DEFINITION)
					{	
						//foundSubject = true;
						foundObject = true;
						subjectEntity = entity;
						objectEntity = GIAtranslatorOperations.getDefinitionRelationshipObjectEntity(targetConnection);
						recurse = false;
						addObject = true;
					}
					#endif

					//targetEntity->NLCparsedForCodeBlocks = true;
					#ifdef NLC_RECORD_ACTION_HISTORY
					if((connectionType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTION) || (connectionType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTION_REVERSE))
					{
						//initialise the action
						if(generateObjectInitialisationsAction(currentCodeBlockInTree, actionOrConditionRelationshipEntity, sentenceIndex))	//subset of generateObjectInitialisationsFunction()
						{

						}
					}
					#endif

					if(recurse)
					{

						NLCgenerateContextBlocksVariables generateContextBlocksVariables;
						generateContextBlocksVariables.getParentCheckLastParent = true;
						generateContextBlocksVariables.lastParent = entity;
						if((connectionType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTION) || (connectionType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTION_REVERSE))
						{
							actionOrConditionRelationshipEntity->NLCcontextGeneratedTemp = true;	//prevent actionRelationshipEntity from being parsed by getParentAndInitialiseParentIfNecessaryAndGenerateContextBlocks:generateContextBlocks;
						}
							
						GIAentityNode* recurseEntityParent = NULL;
						bool newInitialisation = false;
						if(getParentAndInitialiseParentIfNecessaryAndGenerateContextBlocks(currentCodeBlockInTree, recurseEntity, sentenceIndex, &generateContextBlocksVariables, false, &recurseEntityParent, &newInitialisation))
						{
							//*currentCodeBlockInTree = createCodeBlockAddEntityToCategoryListCheckLastSentenceReferencedPluralExecuteFunction(*currentCodeBlockInTree, recurseEntity, recurseEntity, NLC_ITEM_TYPE_RECURSEENTITYCATEGORY_VAR_APPENDITION, sentenceIndex);
						}
						/*NO:	
						if(generateObjectInitialisations(currentCodeBlockInTree, recurseEntity, sentenceIndex))
						{

						}
						*/
					}

					if((connectionType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTION) || (connectionType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTION_REVERSE))
					{
						actionOrConditionRelationshipEntity->NLCcontextGeneratedTemp = false;	//redundant
					}

					if(addObject)
					{
						
						bool isPrimary = false;
						if(generateCodeBlocksAddConnection(currentCodeBlockInTree, connectionType, targetConnection, subjectEntity, objectEntity, actionOrConditionRelationshipEntity, foundSubject, foundObject, sentenceIndex, NULL, isPrimary))
						{
							result = true;
						}
					}
				}
			}
		}
	}
	
	return result;
}

bool NLCtranslatorCodeBlocksOperationsClass::generateCodeBlocksAddConnection(NLCcodeblock** currentCodeBlockInTree, const int connectionType, const GIAentityConnection* connection, GIAentityNode* subjectEntity, GIAentityNode* objectEntity, GIAentityNode* actionOrConditionRelationshipEntity, const bool foundSubject, const bool foundObject, int sentenceIndex, const GIAentityNode* subjectParentEntity, const bool primary)
{
	bool result = false;

	NLCcodeblock* codeBlockInTreeBeforeParseContext = *currentCodeBlockInTree;
	
	if((connectionType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTION) || (connectionType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTION_REVERSE))
	{
		result = true;
		GIAentityNode* actionRelationshipEntity = actionOrConditionRelationshipEntity;
		if(foundSubject)
		{
			if(primary)
			{
				*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockForCategoryList(*currentCodeBlockInTree, subjectEntity, NLC_ITEM_TYPE_SUBJECTCATEGORY_VAR_APPENDITION, sentenceIndex);
			}
			#ifdef NLC_RECORD_ACTION_HISTORY
			*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockRecordHistoryActionSubject(*currentCodeBlockInTree, actionRelationshipEntity, subjectEntity);
			#endif	
		}
		*currentCodeBlockInTree = NLCcodeBlockClass.getLastCodeBlockInLevel(codeBlockInTreeBeforeParseContext);
		if(foundObject)
		{
			if(primary)
			{
				*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockForCategoryList(*currentCodeBlockInTree, objectEntity, NLC_ITEM_TYPE_OBJECTCATEGORY_VAR_APPENDITION, sentenceIndex);
			}
			#ifdef NLC_RECORD_ACTION_HISTORY
			*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockRecordHistoryActionObject(*currentCodeBlockInTree, actionRelationshipEntity, objectEntity);
			#endif
			#ifdef NLC_LIBRARY_FROM_CONDITIONS
			if(objectParentEntity != objectEntity)
			{
				//*currentCodeBlockInTree = createCodeBlockSetTempVariable(*currentCodeBlockInTree, NLC_LIBRARY_MOVE_FUNCTION_ACTIONOBJECT_PARENT_TEMP_VARIABLE_NAME, parentEntityFunctionObject);
				GIAentityNode* parentEntityFromCondition = new GIAentityNode();
				parentEntityFromCondition->entityName = NLC_LIBRARY_MOVE_FUNCTION_ACTION_CONDITION_FROM_NAME;
				GIAtranslatorOperations.addOrConnectConditionToEntity(actionRelationshipEntity, parentEntityFunctionObject, parentEntityFromCondition, false);	//this is required so that generateClassHeirarchyFunctions{} adds the "from" condition to the action, but need to check that GIA supports NLC's use of the addOrConnectConditionToEntity{} function
				*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockAddConditionSimple(*currentCodeBlockInTree, actionRelationshipEntity, parentEntityFromCondition, parentEntityFunctionObject);
			}
			#endif
		}
		*currentCodeBlockInTree = NLCcodeBlockClass.getLastCodeBlockInLevel(codeBlockInTreeBeforeParseContext);
		
		if(primary)
		{
			#ifdef NLC_RECORD_ACTION_HISTORY_GENERALISABLE_DO_NOT_EXECUTE_PAST_TENSE_ACTIONS
			if(!isNonImmediateAction(actionRelationshipEntity))
			{
			#endif
				#ifndef NLC_FUNCTIONS_SUPPORT_PLURAL_OBJECTS
				if(foundSubject)
				{
					*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockForCategoryList(*currentCodeBlockInTree, subjectEntity, NLC_ITEM_TYPE_SUBJECTCATEGORY_VAR_APPENDITION, sentenceIndex);
				}	
				if(foundObject)
				{
					*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockForCategoryList(*currentCodeBlockInTree, objectEntity, NLC_ITEM_TYPE_OBJECTCATEGORY_VAR_APPENDITION, sentenceIndex);
				}
				#endif

				if(foundSubject && foundObject)
				{
					*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockExecuteSubjectObject(*currentCodeBlockInTree, actionRelationshipEntity, subjectEntity, objectEntity, sentenceIndex);
				}	
				else if(foundSubject)
				{
					*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockExecuteSubject(*currentCodeBlockInTree, actionRelationshipEntity, subjectEntity, sentenceIndex);
				}	
				else if(foundObject)
				{
					*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockExecuteObject(*currentCodeBlockInTree, actionRelationshipEntity, objectEntity, sentenceIndex);
				}			
				else
				{
					*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockExecute(*currentCodeBlockInTree, actionRelationshipEntity, sentenceIndex);
				}
			#ifdef NLC_RECORD_ACTION_HISTORY_GENERALISABLE_DO_NOT_EXECUTE_PAST_TENSE_ACTIONS	
			}
			#endif	
		}
	}
	else
	{
		if(primary)
		{
			if(foundSubject)
			{
				*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockForCategoryList(*currentCodeBlockInTree, subjectEntity, NLC_ITEM_TYPE_SUBJECTCATEGORY_VAR_APPENDITION, sentenceIndex);
			}	
			if(foundObject)
			{
				*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockForCategoryList(*currentCodeBlockInTree, objectEntity, NLC_ITEM_TYPE_OBJECTCATEGORY_VAR_APPENDITION, sentenceIndex);
			}
		}
		
		if(connectionType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_PROPERTY)
		{
			GIAentityNode* propertyRelationshipObjectEntity = objectEntity;

			result = true;
			#ifdef NLC_TRANSLATE_NEGATIVE_PROPERTIES_AND_CONDITIONS
			#ifdef GIA_ADD_ARTIFICIAL_AUXILIARY_FOR_ALL_PROPERTIES_AND_DEFINITIONS
			GIAentityNode* propertyRelationshipEntity = connection->entity;
			if(propertyRelationshipEntity->negative || ((propertyRelationshipObjectEntity->entityType == GIA_ENTITY_TYPE_QUALITY) && propertyRelationshipObjectEntity->negative))	//NB NLP/GIA will assign the negative to the property relationship object for qualities (e.g. x is not red)
			#else
			if(connection->negative || ((propertyRelationshipObjectEntity->entityType == GIA_ENTITY_TYPE_QUALITY) && propertyRelationshipObjectEntity->negative))
			#endif
			{
				if(NLCcodeBlockClass.isDefiniteEntity(propertyRelationshipObjectEntity))	//added 1p1b - CHECKTHIS
				{
					//remove property link; eg "the ball" in "Tom does not have the ball."
					*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockRemoveProperty(*currentCodeBlockInTree, subjectEntity, propertyRelationshipObjectEntity);
				}
				else
				{
					//remove property links; eg "a ball" in "Tom does not have a ball."
					*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockRemoveProperties(*currentCodeBlockInTree, subjectEntity, propertyRelationshipObjectEntity);
				}
			}
			else
			{
			#endif
				//add property links; eg "the ball" in "Tom has a/the ball"
				*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockAddProperty(*currentCodeBlockInTree, subjectEntity, propertyRelationshipObjectEntity, sentenceIndex);
			#ifdef NLC_TRANSLATE_NEGATIVE_PROPERTIES_AND_CONDITIONS
			}
			#endif				
		}
		else if(connectionType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_CONDITION)
		{
			result = true;
			GIAentityNode* conditionRelationshipEntity = actionOrConditionRelationshipEntity;
			GIAentityNode* conditionRelationshipObjectEntity = NULL;
			if(!(conditionRelationshipEntity->relationshipObjectEntity->empty()))
			{		
				conditionRelationshipObjectEntity = (conditionRelationshipEntity->relationshipObjectEntity->back())->entity;
			}
			
			#ifdef NLC_TRANSLATE_NEGATIVE_PROPERTIES_AND_CONDITIONS
			if(conditionRelationshipEntity->negative)
			{
				if(NLCcodeBlockClass.isDefiniteEntity(conditionRelationshipObjectEntity))	//added 1p1b - CHECKTHIS
				{
					//remove condition link; eg "a house" in "Tom is not near the house"
					*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockRemoveCondition(*currentCodeBlockInTree, subjectEntity, conditionRelationshipEntity);
				}
				else
				{
					//remove condition links; eg "a house" in "Tom is not near a house"
					*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockRemoveConditions(*currentCodeBlockInTree, subjectEntity, conditionRelationshipEntity);
				}
			}
			else
			{
			#endif
				//add condition links; eg "the house" in "Tom is near a/the house"
				*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockAddCondition(*currentCodeBlockInTree, subjectEntity, conditionRelationshipEntity, sentenceIndex);
			#ifdef NLC_TRANSLATE_NEGATIVE_PROPERTIES_AND_CONDITIONS
			}
			#endif
		}
		else if(connectionType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_DEFINITION)
		{
			GIAentityNode* definitionRelationshipObjectEntity = objectEntity;

			#ifdef NLC_MATH_OBJECTS
			if(NLCpreprocessorSentenceClass.isStringNumberOrFractional(definitionRelationshipObjectEntity->entityName)) 
			{
				result = true;
				//eg The value is 5.5
				*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockSetMathObjectNumericalValue(*currentCodeBlockInTree, subjectEntity, definitionRelationshipObjectEntity);
			}
			else
			{
			#endif
				#ifdef NLC_ADVANCED_REFERENCING_SUPPORT_ALIASES			
				if(GIAtranslatorOperations.connectionIsAlias(connection))
				{
					#ifdef NLC_ADVANCED_REFERENCING_SUPPORT_ALIASES_MERGERS
					if(isDefiniteEntity(subjectEntity) && isDefiniteEntity(definitionRelationshipObjectEntity))
					{
						if(subjectEntity->entityName == definitionRelationshipObjectEntity->entityName)
						{
							//eg the new dogs are the original dogs
							/*
							NB this merger command can be used to create a subset of dogs by subsequently executing: i = 0; for every new dog {if i = 1, the dog is not new; i = i+1;}
							*/
							
							result = true;

							//1. merge all subject attributes (properties etc) with object 
							*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlocksMergeEntity1AttributesIntoEntity2ExecuteFunction(*currentCodeBlockInTree, subjectEntity, definitionRelationshipObjectEntity);

							//2. remove entity from entityLocalList (effectively delete the entity from existence)
							*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockRemoveEntityFromLocalListExecuteFunction(*currentCodeBlockInTree, subjectEntity);
						}
						#ifdef NLC_ADVANCED_REFERENCING_SUPPORT_ALIASES_MERGERS_DIFFERENT_NAMES
						else
						{
							//eg The dog is the Alsatian		
							//3. verify that alsations are dogs
							#ifdef NLC_REDEFINITIONS_VERIFY_PARENT_CLASS_INTERNALLY
							//FUTURE NLC - could use classDefinitionList instead of GIAentityNode concepts; but generateClassHeirarchy needs to be called before generateCodeBlocks
							if(checkParentExists(definitionRelationshipObjectEntity, subjectEntity->entityName))
							{
								result = true;

								//1. merge all subject attributes (properties etc) with object 
								*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlocksMergeEntity1AttributesIntoEntity2ExecuteFunction(*currentCodeBlockInTree, subjectEntity, definitionRelationshipObjectEntity);

								//2. replace entity in entityLocalList (effectively delete the entity from existence)
								*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockReplaceEntityInLocalListExecuteFunction(*currentCodeBlockInTree, subjectEntity, definitionRelationshipObjectEntity);
							}
							//3. verify that dogs are alsations
							else if(checkParentExists(subjectEntity, definitionRelationshipObjectEntity->entityName))
							{
								result = true;

								//1. merge all subject attributes (properties etc) with object 
								*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlocksMergeEntity1AttributesIntoEntity2ExecuteFunction(*currentCodeBlockInTree, definitionRelationshipObjectEntity, subjectEntity);

								//2. replace entity in entityLocalList (effectively delete the entity from existence)
								*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockReplaceEntityInLocalListExecuteFunction(*currentCodeBlockInTree, definitionRelationshipObjectEntity, subjectEntity);
							}
							else
							{
								//currently ignore these cases as NLC definition class hierarchy will not store all properties of Alsatian in dog class (which is required for merger)
							}
							#else
							cout << "NLCtranslatorCodeBlocksOperationsClass::generateCodeBlocksAddConnection{} error: NLC_ADVANCED_REFERENCING_SUPPORT_ALIASES_MERGERS_DIFFERENT_NAMES requires NLC_REDEFINITIONS_VERIFY_PARENT_CLASS_INTERNALLY" << endl; 
							#endif
						}
						#endif
					}
					else
					{
					#endif
						//eg The name of the red dog is Tom.

						result = true;
						bool aliasAlreadyInitialised = false;
						string aliasName = definitionRelationshipObjectEntity->entityName;
						string aliasClassName = subjectEntity->entityName;

						string aliasNameTemp = "";
						if(NLCcodeBlockClass.findAliasInEntity(definitionRelationshipObjectEntity, &aliasNameTemp)) //*
						{
							aliasAlreadyInitialised = true;
						}
						if(!aliasAlreadyInitialised)
						{	
							//check this code

							NLCcodeblock* firstCodeBlockInSentence = *currentCodeBlockInTree;
							GIAentityNode* parentEntity = NULL;

							*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlocksAddAliasToEntityAliasList(*currentCodeBlockInTree, subjectEntity, aliasName);

							//1k14c; replace all alias GIA entities with their respective class (eg dog), and add an alias to their vector list (eg Tom)
							GIAentityNode* aliasNetworkIndexEntity = GIAtranslatorOperations.getPrimaryNetworkIndexNodeDefiningInstance(definitionRelationshipObjectEntity);
							for(vector<GIAentityConnection*>::iterator iter2 = aliasNetworkIndexEntity->instanceNodeList->begin(); iter2 < aliasNetworkIndexEntity->instanceNodeList->end(); iter2++)
							{
								GIAentityNode* entity2 = (*iter2)->entity;
								if(entity2->entityName == aliasName)
								{
									if(entity2->sentenceIndexTemp > definitionRelationshipObjectEntity->sentenceIndexTemp)	//this test isn't required because of* 
									{
										entity2->aliasList.push_back(aliasName);
										entity2->entityName = aliasClassName;	
									}
								}
							}

							definitionRelationshipObjectEntity->NLCisAlias = true; //added 1o1b (prevents addition of alias to class heirachy)	
						}
					#ifdef NLC_ADVANCED_REFERENCING_SUPPORT_ALIASES_MERGERS
					}
					#endif
				}
				else
				{
				#endif
					//eg [Alsations are dogs. The pound has a dog. The dog is happy.] The dog is an alsation.  ; converts dog to alsation

					#ifdef NLC_REDEFINITIONS
					#ifndef NLC_REDEFINITIONS_FOR_IMMEDIATELY_DECLARED_INDEFINITE_ENTITIES
					//eg chickens are animals. an animal is a chicken. In practice this will not be implemented because GIA interprets indefinite-indefinite definitions as concepts. redefinitions are generally not implied for indefinite children (eg "an animal" in "an animal is a chicken") because they are ambiguous; this example either means a) animals are chickens (ie is a concept-concept definition; not a redefinition - and happens to be an incorrect statement based on aprior knowledge about the animal kingdom because we know chickens are animals not vice versa), or b) a newly declared animal is cast to a chicken (a specific version of animal, assuming "chickens are animals" has been declared)
					if(!NLCcodeBlockClass.isDefiniteEntity(definitionRelationshipObjectEntity))
					{
						bool foundDefiniteParentOfEntity = false;
						bool parseConditionParents = NLC_PARSE_CONDITION_PARENTS_DEFAULT_VALUE;
						bool checkIsDefinite = true;
						GIAentityNode* parentEntity = getSameReferenceSetUniqueParent(subjectEntity, sentenceIndex, NULL, &foundDefiniteParentOfEntity, parseConditionParents, checkIsDefinite);
						if(NLCcodeBlockClass.isDefiniteEntity(subjectEntity) || foundDefiniteParentOfEntity)
						{
					#endif
							if(subjectEntity->entityName != definitionRelationshipObjectEntity->entityName)
							{//ignore concept definitions for for entities of same name
								
								

								NLCcodeblock* firstCodeBlockInSentence = *currentCodeBlockInTree;

								GIAentityNode* parentEntity = NULL;

								//1. and 2. get parent of the dog (eg pound) and generate context of the dog (already done)
								//generateContextBlocksVariables.searchConceptsForChildren = false;	//added 1n5g (only check the explicit variable for definition; do not parse categories) - CHECKTHIS
	
								//3. verify that alsations are dogs
								#ifdef NLC_REDEFINITIONS_VERIFY_PARENT_CLASS_INTERNALLY
								//FUTURE NLC - could use classDefinitionList instead of GIAentityNode concepts; but generateClassHeirarchy needs to be called before generateCodeBlocks
								if(checkParentExists(definitionRelationshipObjectEntity, subjectEntity->entityName))
								{
								#else
									*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockCheckParentClassNameExecuteFunction2(*currentCodeBlockInTree, definitionRelationshipObjectEntity, subjectEntity->entityName);
								#endif
									result = true;
									
									//4. cast the dog to alsation
									*currentCodeBlockInTree = NLCcodeBlockClass.createCodeConvertParentToChildClass(*currentCodeBlockInTree, subjectEntity, definitionRelationshipObjectEntity);

									//5. add alsation to alsation property list of pound 
										//LIMITATION: NB the dog will still be added to the dog property list of pound; therefore these must remain synced; ie the dog or the alsation cannot be deleted from the pound...
										//to avoid this limitation at present the user must define an object by its most specific class initially (avoiding redefinitions). NLC will automatically search for references to the child based on concept definition link to its parent [dream mode has connected concept definiton links to all instantations thereof]
									if(subjectParentEntity != subjectEntity)
									{
										*currentCodeBlockInTree =  NLCcodeBlockClass.createCodeBlockAddProperty(*currentCodeBlockInTree, subjectParentEntity, definitionRelationshipObjectEntity, sentenceIndex);
									}

									//6. add alsation to alsation local list
									GIAentityNode* definitionEntityNetworkIndexEntity = GIAtranslatorOperations.getPrimaryNetworkIndexNodeDefiningInstance(definitionRelationshipObjectEntity);
									if(NLCcodeBlockClass.assumedToAlreadyHaveBeenDeclared(definitionRelationshipObjectEntity) || definitionEntityNetworkIndexEntity->NLClocalListVariableHasBeenDeclared)	//added 1q5b, changed 1q8a
									{								
										*currentCodeBlockInTree =  NLCcodeBlockClass.createCodeBlockAddEntityToLocalList(*currentCodeBlockInTree, definitionRelationshipObjectEntity, definitionRelationshipObjectEntity);
									}

									/*
									#ifdef NLC_GENERATE_OBJECT_INITIALISATIONS_BASED_ON_CONCEPTS
									//7. generate object initialisations based on concepts (class inheritance)
									generateObjectInitialisationsBasedOnConcepts(definitionRelationshipObjectEntity, definitionRelationshipObjectEntity, currentCodeBlockInTree, sentenceIndex, true);
									#endif
									*/	
								#ifdef NLC_REDEFINITIONS_VERIFY_PARENT_CLASS_INTERNALLY
								}
								#endif						

							}
					#ifndef NLC_REDEFINITIONS_FOR_IMMEDIATELY_DECLARED_INDEFINITE_ENTITIES
						}
						else
						{
							cout << "checkIfPhraseContainsSubstanceWithDefinitionLink{} warning: !(isDefiniteEntity{subjectEntity} || foundDefiniteParentOfEntity)" << endl;
						}
					}
					else
					{
						cout << "checkIfPhraseContainsSubstanceWithDefinitionLink{} warning: isDefiniteEntity{definitionRelationshipObjectEntity}" << endl;
					}
					#endif
					#endif
				#ifdef NLC_ADVANCED_REFERENCING_SUPPORT_ALIASES						
				}
				#endif
			#ifdef NLC_MATH_OBJECTS						
			}
			#endif				
		}
	}
	return result;
}

#ifdef NLC_TRANSLATOR_LOGICAL_CONDITIONS_BOOLEAN_STATEMENTS_INTERPRET_SUBJECT_AND_OBJECT_INDEPENDENTLY
//assume is logicalConditionStatement
bool NLCtranslatorCodeBlocksOperationsClass::generateCodeBlocksVerifyConnection(NLCcodeblock** currentCodeBlockInTree, const int connectionType, const GIAentityConnection* connection, GIAentityNode* subjectEntity, GIAentityNode* objectEntity, GIAentityNode* actionOrConditionRelationshipEntity, const bool foundSubject, const bool foundObject, const int sentenceIndex, const bool effectiveEach, NLCgenerateContextBlocksVariables* generateContextBlocksVariablesLogicalConditionStatement)
{
	
	bool result = false;
	
	bool subjectNumerosityTests = false;
	bool specificObjectNumerosityTests = false;
	bool objectNumerosityTests = false;
	
	if(foundSubject && foundObject)
	{
		if(checkNumerosity(subjectEntity) && !checkNumerosity(objectEntity))	
		{
			specificObjectNumerosityTests = true;
		}
		else if(checkNumerosity(subjectEntity) && checkNumerosity(objectEntity))
		{
			specificObjectNumerosityTests = true;
		}
		else if(effectiveEach)
		{
			specificObjectNumerosityTests = true;
		}
		else if(checkNumerosity(objectEntity))
		{
			objectNumerosityTests = true;
		}
	}
	else if(foundObject)
	{
		if(checkNumerosity(objectEntity))
		{
			objectNumerosityTests = true;	//CHECKTHIS; if 7 cars are ridden (no subject)
		}

	}
	if(foundSubject)
	{
		if(checkNumerosity(subjectEntity))
		{
			subjectNumerosityTests = true;
		}
		else if(effectiveEach)
		{
			subjectNumerosityTests = true;
		}
	}	
	
	NLCgenerateContextBlocksVariables generateContextBlocksVariables;
	generateContextBlocksVariables.secondaryComparison = generateContextBlocksVariablesLogicalConditionStatement->secondaryComparison;
	GIAentityNode* objectEntityTemp = NULL;
	bool generateContextForObjectTemp = false;
	bool generateTest = false;

	#ifdef NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY_PARENT
	NLCcodeblock* firstCodeBlockAtLevel1 = *currentCodeBlockInTree;
	#endif
	#ifdef NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY_CHILDREN
	NLCcodeblock* firstCodeBlockAtLevel2 = NULL;
	#endif
	
	
	if(foundSubject)	//assume true
	{
		#ifdef NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY_PARENT
		if(generateContextBlocksVariablesLogicalConditionStatement->testNumerosity)
		{
			if(subjectNumerosityTests)
			{
				string categoryListPropertyCountVariableName = NLCcodeBlockClass.generateCategoryListPropertyCountVariableName(subjectEntity);
				*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockDeclareNewIntVar(*currentCodeBlockInTree, categoryListPropertyCountVariableName, 0);
			}
			if(objectNumerosityTests)
			{
				string categoryListPropertyCountVariableName = NLCcodeBlockClass.generateCategoryListPropertyCountVariableName(objectEntity);
				*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockDeclareNewIntVar(*currentCodeBlockInTree, categoryListPropertyCountVariableName, 0);
			}
		}
		#endif
		
		*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockForCategoryList(*currentCodeBlockInTree, subjectEntity, NLC_ITEM_TYPE_SUBJECTCATEGORY_VAR_APPENDITION, sentenceIndex);
	}
	#ifdef NLC_TRANSLATOR_LOGICAL_CONDITIONS_BOOLEAN_STATEMENTS_INTERPRET_SUBJECT_AND_OBJECT_INDEPENDENTLY_SUPPORT_INDEFINITE_OBJECT_STRICT_NUMEROSITY	
	if(foundObject)
	#else
	if(objectEntity != NULL)
	#endif
	{
		#ifdef NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY_CHILDREN
		firstCodeBlockAtLevel2 = *currentCodeBlockInTree;
		if(generateContextBlocksVariablesLogicalConditionStatement->testNumerosity)
		{
			if(specificObjectNumerosityTests)
			{
				string categoryListPropertyCountVariableName = NLCcodeBlockClass.generateCategoryListPropertyCountVariableName(objectEntity);
				*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockDeclareNewIntVar(*currentCodeBlockInTree, categoryListPropertyCountVariableName, 0);
			}
		}
		#endif
		#ifndef NLC_TRANSLATOR_LOGICAL_CONDITIONS_BOOLEAN_STATEMENTS_INTERPRET_SUBJECT_AND_OBJECT_INDEPENDENTLY_SUPPORT_INDEFINITE_OBJECT_STRICT_NUMEROSITY
		if(foundObject)
		{
		#endif
			*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockForCategoryList(*currentCodeBlockInTree, objectEntity, NLC_ITEM_TYPE_OBJECTCATEGORY_VAR_APPENDITION, sentenceIndex);
		#ifndef NLC_TRANSLATOR_LOGICAL_CONDITIONS_BOOLEAN_STATEMENTS_INTERPRET_SUBJECT_AND_OBJECT_INDEPENDENTLY_SUPPORT_INDEFINITE_OBJECT_STRICT_NUMEROSITY	
		}
		#endif
	}	
	
	
	
	#ifdef NLC_RECORD_ACTION_HISTORY
	if(connectionType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTION)
	{
		if(createCodeBlockForGivenAction(currentCodeBlockInTree, NLCitemClass.generateInstanceName(subjectEntity), actionOrConditionRelationshipEntity, sentenceIndex, &generateContextBlocksVariables, &objectEntityTemp, &generateContextForObjectTemp))
		{
			result = true;
			generateTest = generateContextForObjectTemp;
		}
	}
	else if(connectionType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_ACTION_REVERSE)
	{	
		if(createCodeBlockForGivenActionIncoming(currentCodeBlockInTree, NLCitemClass.generateInstanceName(objectEntity), actionOrConditionRelationshipEntity, sentenceIndex, &generateContextBlocksVariables, &objectEntityTemp, &generateContextForObjectTemp))
		{
			result = true;
			generateTest = generateContextForObjectTemp;
		}
	}
	#endif
	else if(connectionType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_PROPERTY)
	{
		GIAentityNode* propertyRelationshipEntity = connection->entity;
		if(createCodeBlockForGivenProperty(currentCodeBlockInTree, NLCitemClass.generateInstanceName(subjectEntity), propertyRelationshipEntity, sentenceIndex, &generateContextBlocksVariables, &objectEntityTemp, &generateContextForObjectTemp))
		{
			//this additional negative check code is from createCodeBlockForConnectionType;
			#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
			#ifdef GIA_ADD_ARTIFICIAL_AUXILIARY_FOR_ALL_PROPERTIES_AND_DEFINITIONS
			if(propertyRelationshipEntity->negative)
			#else
			if(connection->negative)
			#endif
			{
				generateContextBlocksVariables.negativeDetectedInContextBlocks = true;
			}
			#endif
			result = true;
			generateTest = true;
		}
	}
	else if(connectionType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_CONDITION)
	{
		if(createCodeBlockForGivenCondition(currentCodeBlockInTree, NLCitemClass.generateInstanceName(subjectEntity), actionOrConditionRelationshipEntity, sentenceIndex, &generateContextBlocksVariables, &objectEntityTemp, &generateContextForObjectTemp))
		{
			result = true;
			generateTest = true;
		}
	}
	#ifdef NLC_TRANSLATOR_LOGICAL_CONDITIONS_BOOLEAN_STATEMENTS_INTERPRET_SUBJECT_AND_OBJECT_INDEPENDENTLY_DEFINITIONS
	else if(connectionType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_DEFINITION)
	{
		GIAentityNode* definitionRelationshipEntity = connection->entity;
		GIAentityNode* definitionRelationshipObjectEntity = objectEntity;
		#ifdef NLC_MATH_OBJECTS
		if(NLCpreprocessorSentenceClass.isStringNumberOrFractional(definitionRelationshipObjectEntity->entityName)) 
		{
			result = true;
			//eg if the value is 5.5	//CHECKTHIS
			*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockTestMathObjectNumericalValue(*currentCodeBlockInTree, subjectEntity, definitionRelationshipObjectEntity);
		}
		else
		{
		#endif
			#ifdef NLC_ADVANCED_REFERENCING_SUPPORT_ALIASES
			if(GIAtranslatorOperations.connectionIsAlias(connection))
			{	
				//CHECKTHIS
				//eg If the name of the dog is Max, ride the bike.
				if(createCodeBlockForGivenAlias(currentCodeBlockInTree, subjectEntity, definitionRelationshipEntity, sentenceIndex, &generateContextBlocksVariables, &objectEntityTemp, &generateContextForObjectTemp))
				{
					result = true;

					#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
					#ifdef GIA_ADD_ARTIFICIAL_AUXILIARY_FOR_ALL_PROPERTIES_AND_DEFINITIONS
					if(definitionRelationshipEntity->negative)
					#else
					if(connection->negative)
					#endif
					{
						generateContextBlocksVariables.negativeDetectedInContextBlocks = true;
					}
					#endif
				}
			}
			else
			{
			#endif
				//CHECKTHIS (code based on generateCodeBlocksAddConnection)

				//eg verify that alsations are dogs
				
				/*removed 1t2f
				#ifdef NLC_REDEFINITIONS_VERIFY_PARENT_CLASS_INTERNALLY
				//FUTURE NLC - could use classDefinitionList instead of GIAentityNode concepts; but generateClassHeirarchy needs to be called before generateCodeBlocks
				if(checkParentExists(definitionRelationshipObjectEntity, subjectEntity->entityName))
				{
				#else
				*/
				*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockCheckParentClassNameExecuteFunction2(*currentCodeBlockInTree, definitionRelationshipObjectEntity, subjectEntity->entityName);
				//#endif
				
				result = true;
				//eg verify that the dog is an alsation
				*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockIfTempVariableNameEqualsClassName(*currentCodeBlockInTree, subjectEntity, definitionRelationshipObjectEntity->entityName);	//eg if(dog->name == "alsation")

				
				#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
				#ifdef GIA_ADD_ARTIFICIAL_AUXILIARY_FOR_ALL_PROPERTIES_AND_DEFINITIONS
				if(definitionRelationshipEntity->negative)
				#else
				if(connection->negative)
				#endif
				{
					generateContextBlocksVariables.negativeDetectedInContextBlocks = true;
				}
				#endif
				
				/*
				#ifdef NLC_REDEFINITIONS_VERIFY_PARENT_CLASS_INTERNALLY
				}
				#endif
				*/
			#ifdef NLC_ADVANCED_REFERENCING_SUPPORT_ALIASES	
			}
			#endif	
		#ifdef NLC_MATH_OBJECTS
		}
		#endif	
	}
	#endif

	
	if(result)
	{
		if(generateContextBlocksVariables.negativeDetectedInContextBlocks)
		{
			generateContextBlocksVariablesLogicalConditionStatement->negativeDetectedInContextBlocks = true;
		}

		if(generateTest)
		{
			//ignore cases without action subject or object; eg If the car rode... 
			
			GIAentityNode targetEntity;	//reference target variable/iterator in subject entity property/condition/action/definition list
			targetEntity.entityName = objectEntityTemp->entityName;
			targetEntity.idInstance = objectEntityTemp->idInstance;
			if(generateContextBlocksVariablesLogicalConditionStatement->secondaryComparison)
			{
				secondaryComparisonRestoreIDinstance(objectEntityTemp);
			}
				
			if(foundSubject && foundObject)
			{
				//eg if the baskets have the pie
				//ignore cases with indefinite object eg if Tom has a car (in which case foundObject will have been set to false)
				*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockIfTempVariableEqualsEntity(*currentCodeBlockInTree, &targetEntity, objectEntity);	//if(param1 == param2) {
			}
			
			#ifdef NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY
			if(generateContextBlocksVariablesLogicalConditionStatement->testNumerosity)
			{
				#ifdef NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY_CHILDREN
				#ifdef NLC_TRANSLATOR_LOGICAL_CONDITIONS_BOOLEAN_STATEMENTS_INTERPRET_SUBJECT_AND_OBJECT_INDEPENDENTLY_SUPPORT_INDEFINITE_OBJECT_STRICT_NUMEROSITY	
				if(foundObject)
				#else
				if(objectEntity != NULL)
				#endif
				{
					if(specificObjectNumerosityTests || objectNumerosityTests)
					{
						//eg If the basket has 3 pies, eat the apple.
						string categoryListPropertyCountVariableName = NLCcodeBlockClass.generateCategoryListPropertyCountVariableName(objectEntity);
						*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockIncrementIntVar(*currentCodeBlockInTree, categoryListPropertyCountVariableName);
	
						if(specificObjectNumerosityTests)
						{
							*currentCodeBlockInTree = NLCcodeBlockClass.getLastCodeBlockInLevel(firstCodeBlockAtLevel2);	//eg it each cat has 7 bikes, each cat has a bike, 7 cats have 7 bikes, if 7 cats have a bike
						}
						else if(objectNumerosityTests)
						{
							*currentCodeBlockInTree = NLCcodeBlockClass.getLastCodeBlockInLevel(firstCodeBlockAtLevel1);	//eg the cats have 7 bikes, 
						}
						if(checkNumerosity(objectEntity))
						{
							#ifdef NLC_CATEGORIES_TEST_PLURALITY_COMMENT
							*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockCommentSingleLine(*currentCodeBlockInTree, "numerosity tests (child)");
							#endif
							*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockIfIntVariableGreaterThanOrEqualToNum(*currentCodeBlockInTree, categoryListPropertyCountVariableName, objectEntity->quantityNumber);
						}
						else
						{
							//just verify that at least 1 object item is found
							*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockIfIntVariableGreaterThanOrEqualToNum(*currentCodeBlockInTree, categoryListPropertyCountVariableName, 1);
						}
					}		
				}	
				#endif
				#ifdef NLC_CATEGORIES_TEST_PLURALITY_NUMEROSITY_PARENT
				if(foundSubject)	//assume true
				{
					if(subjectNumerosityTests)
					{
						//eg If 3 baskets have a pie, eat the apple.
						string categoryListPropertyCountVariableName = NLCcodeBlockClass.generateCategoryListPropertyCountVariableName(subjectEntity);
						*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockIncrementIntVar(*currentCodeBlockInTree, categoryListPropertyCountVariableName);
						
						*currentCodeBlockInTree = NLCcodeBlockClass.getLastCodeBlockInLevel(firstCodeBlockAtLevel1);
						
						if(checkNumerosity(subjectEntity))
						{
							#ifdef NLC_CATEGORIES_TEST_PLURALITY_COMMENT
							*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockCommentSingleLine(*currentCodeBlockInTree, "numerosity tests (parent)");
							#endif
							*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockIfIntVariableGreaterThanOrEqualToNum(*currentCodeBlockInTree, categoryListPropertyCountVariableName, subjectEntity->quantityNumber);
						}
						else if(effectiveEach)
						{
							*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockIfIntVariableEqualsListSize(*currentCodeBlockInTree, categoryListPropertyCountVariableName, subjectEntity, NLC_ITEM_TYPE_SUBJECTCATEGORY_VAR_APPENDITION, sentenceIndex);
						}
					}
				}
				#endif		
			}	
			#endif
		}
	}
	
	
	return result;
}
#endif

#ifdef NLC_RECORD_ACTION_HISTORY_GENERALISABLE_DO_NOT_EXECUTE_PAST_TENSE_ACTIONS
bool NLCtranslatorCodeBlocksOperationsClass::isNonImmediateAction(const GIAentityNode* actionRelationshipEntity)
{
	//updated 1m2a
	bool isNonImmediateAction = false;
	if(actionRelationshipEntity->grammaticalTenseModifierArrayTemp[GRAMMATICAL_TENSE_MODIFIER_STATE] == true)
	{
		isNonImmediateAction = true;
	}
	else if(actionRelationshipEntity->grammaticalTenseModifierArrayTemp[GRAMMATICAL_TENSE_MODIFIER_POTENTIAL] == true)	//redundant, as this is already filtered by isPotentialAction()
	{
		isNonImmediateAction = true;
	}
	else if(actionRelationshipEntity->grammaticalTenseModifierArrayTemp[GRAMMATICAL_TENSE_MODIFIER_POTENTIAL_INVERSE] == true)	//redundant, as this is already filtered by isPotentialAction()
	{
		isNonImmediateAction = true;
	}
	else if(actionRelationshipEntity->grammaticalTenseModifierArrayTemp[GRAMMATICAL_TENSE_MODIFIER_PROGRESSIVE] == true)
	{
		isNonImmediateAction = true;
	}
	else if(actionRelationshipEntity->grammaticalTenseModifierArrayTemp[GRAMMATICAL_TENSE_MODIFIER_PASSIVE] == true)	//added 1n8a
	{
		isNonImmediateAction = true;
	}
	//CHECKTHIS; check GRAMMATICAL_TENSE_MODIFIER_INFINITIVE is being generated correctly (ie is being correctly distinguished from VBP/present not third person singular) - otherwise isNonImmediateAction will have to check for GRAMMATICAL_TENSE_MODIFIER_INFINITIVE also
		
	if(actionRelationshipEntity->timeConditionNode != NULL)
	{
		const GIAtimeConditionNode* timeCondition = actionRelationshipEntity->timeConditionNode;
		if(timeCondition->tense == GRAMMATICAL_TENSE_PAST)
		{
			isNonImmediateAction = true;
		}
	}
	return isNonImmediateAction;
}

bool NLCtranslatorCodeBlocksOperationsClass::isPotentialAction(const GIAentityNode* actionRelationshipEntity)
{
	//updated 1m2a
	bool isPotentialAction = false;
	if(actionRelationshipEntity->grammaticalTenseModifierArrayTemp[GRAMMATICAL_TENSE_MODIFIER_POTENTIAL] == true)
	{
		isPotentialAction = true;
	}
	if(actionRelationshipEntity->grammaticalTenseModifierArrayTemp[GRAMMATICAL_TENSE_MODIFIER_POTENTIAL_INVERSE] == true)
	{
		isPotentialAction = true;
	}
	return isPotentialAction;
}
#endif



bool NLCtranslatorCodeBlocksOperationsClass::getEntityCheckSameReferenceSetAndSentence(GIAentityNode* entity, GIAentityNode** entityToFind, GIAentityConnection** connection, const int sentenceIndex, const bool sameReferenceSet, int connectionType)
{
	bool found = false;
	if(getEntityConnection(entity, sentenceIndex, connection, connectionType))
	{
		if((*connection)->sameReferenceSet == sameReferenceSet)
		{	
			#ifdef NLC_NORMALISE_TWOWAY_PREPOSITIONS_DUAL_CONDITION_LINKS_ENABLED
			if(!connectionTypeIsCondition(connectionType, *connection) || ((!(entity->inverseConditionTwoWay) || (*connection)->isReference)))	//prevent infinite loop for 2 way conditions 
			{
			#endif
				*entityToFind = (*connection)->entity;
				if(NLCcodeBlockClass.checkSentenceIndexParsingCodeBlocks(*entityToFind, *connection, sentenceIndex, false))
				{
					found = true;	
				}
			#ifdef NLC_NORMALISE_TWOWAY_PREPOSITIONS_DUAL_CONDITION_LINKS_ENABLED
			}
			#endif
		}
	}
	return found;
}

bool NLCtranslatorCodeBlocksOperationsClass::connectionTypeIsCondition(const int connectionType, const GIAentityConnection* connection)
{
	bool result = false;
	/*
	if((connectionType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_RELATIONSHIP_SUBJECT) || (connectionType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_RELATIONSHIP_OBJECT))
	{
		if(connection->entityOrigin->entityType == GIA_ENTITY_TYPE_CONDITION)
		{
			result = true;	
		}
	}
	*/
	if((connectionType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_CONDITION) || (connectionType == GIA_ENTITY_VECTOR_CONNECTION_TYPE_CONDITION_REVERSE))
	{
		result = true;	//CHECKTHIS
	}
}

bool NLCtranslatorCodeBlocksOperationsClass::getEntityConnection(GIAentityNode* entity, const int sentenceIndex, GIAentityConnection** entityConnection, int connectionType)
{
	bool entityHasConnection = false;
	#ifdef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES	//&& #defined NLC_RECORD_ACTION_HISTORY_GENERALISABLE
	//required because GIA advanced referencing may connect a given action to multiple subjects/objects (ie across multiple sentences)
	for(vector<GIAentityConnection*>::iterator iter = entity->entityVectorConnectionsArray[connectionType].begin(); iter < entity->entityVectorConnectionsArray[connectionType].end(); iter++)
	{
		GIAentityConnection* entityConnectionTemp = *iter;
		if(entityConnectionTemp->sentenceIndexTemp == sentenceIndex)
		{
			*entityConnection = entityConnectionTemp;
			entityHasConnection = true;	
		}
	}
	#else
	if(!((entity->entityVectorConnectionsArray[connectionType]).empty()))
	{
		*entityConnection = ((entity->entityVectorConnectionsArray[connectionType]).back());
		entityHasConnection = true;
	}	
	#endif
	return entityHasConnection;
}	










GIAentityNode* NLCtranslatorCodeBlocksOperationsClass::getParent(GIAentityNode* currentEntity, int sentenceIndex)
{
	NLCgenerateContextBlocksVariables generateContextBlocksVariables;
	return getParent(currentEntity, sentenceIndex, &generateContextBlocksVariables);
}

GIAentityNode* NLCtranslatorCodeBlocksOperationsClass::getParent(GIAentityNode* currentEntity, int sentenceIndex, NLCgenerateContextBlocksVariables* generateContextBlocksVariables)
{	 
	GIAentityNode* parentEntityNew = currentEntity;
						
	bool foundParentProperty = false;
	for(vector<GIAentityConnection*>::iterator propertyNodeListIterator = currentEntity->propertyReverseNodeList->begin(); propertyNodeListIterator < currentEntity->propertyReverseNodeList->end(); propertyNodeListIterator++)
	{
		GIAentityConnection* propertyConnection = *propertyNodeListIterator;
		GIAentityNode* parentEntity = GIAtranslatorOperations.getPropertyRelationshipSubjectEntity(propertyConnection);

		#ifdef NLC_DEFINE_LOCAL_VARIABLES_FOR_ALL_INDEFINATE_ENTITIES
		if(NLCcodeBlockClass.checkSentenceIndexParsingCodeBlocks(parentEntity, propertyConnection, sentenceIndex, false))	//NB will parse references to entities in previous sentence
		#else
		if(NLCcodeBlockClass.checkSentenceIndexParsingCodeBlocks(parentEntity, propertyConnection, sentenceIndex, false) || parentEntity->NLCparsedForCodeBlocks)
		#endif
		{
			if(!(generateContextBlocksVariables->getParentCheckLastParent) || (parentEntity != generateContextBlocksVariables->lastParent))
			{
				parentEntityNew = getParent(parentEntity, sentenceIndex, generateContextBlocksVariables);
				foundParentProperty = true;
			}
		}
	}
	#ifdef NLC_PARSE_CONDITION_PARENTS
	if(!foundParentProperty && generateContextBlocksVariables->parseConditionParents)
	{//added 1e9a
		for(vector<GIAentityConnection*>::iterator conditionNodeListIterator = currentEntity->conditionReverseNodeList->begin(); conditionNodeListIterator < currentEntity->conditionReverseNodeList->end(); conditionNodeListIterator++)
		{
			GIAentityConnection* conditionConnection = *conditionNodeListIterator;
			GIAentityNode* conditionRelationshipEntity = conditionConnection->entity;

			#ifdef NLC_NORMALISE_TWOWAY_PREPOSITIONS_DUAL_CONDITION_LINKS_ENABLED
			if(!(conditionRelationshipEntity->inverseConditionTwoWay) || conditionConnection->isReference)	//prevent infinite loop for 2 way conditions 
			{
			#endif
				bool foundConditionSubject = false;
				GIAentityNode* conditionRelationshipSubjectEntity = NULL;
				if(!(conditionRelationshipEntity->relationshipSubjectEntity->empty()))
				{
					conditionRelationshipSubjectEntity = (conditionRelationshipEntity->relationshipSubjectEntity->back())->entity;

					foundConditionSubject = true;

					#ifdef NLC_DEFINE_LOCAL_VARIABLES_FOR_ALL_INDEFINATE_ENTITIES
					if(NLCcodeBlockClass.checkSentenceIndexParsingCodeBlocks(conditionRelationshipSubjectEntity, conditionConnection, sentenceIndex, false))	//NB will parse references to entities in previous sentence
					#else
					if(NLCcodeBlockClass.checkSentenceIndexParsingCodeBlocks(conditionRelationshipSubjectEntity, conditionConnection, sentenceIndex, false) || conditionRelationshipSubjectEntity->NLCparsedForCodeBlocks)
					#endif
					{
						if(!(generateContextBlocksVariables->getParentCheckLastParent) || (conditionRelationshipSubjectEntity != generateContextBlocksVariables->lastParent))
						{
							parentEntityNew = getParent(conditionRelationshipSubjectEntity, sentenceIndex, generateContextBlocksVariables);
						}
					}
				}		
			#ifdef NLC_NORMALISE_TWOWAY_PREPOSITIONS_DUAL_CONDITION_LINKS_ENABLED
			}
			#endif
		}
	}
	#endif

	return parentEntityNew;
}
								

bool NLCtranslatorCodeBlocksOperationsClass::getParentAndGenerateContextBlocks(NLCcodeblock** currentCodeBlockInTree, GIAentityNode* currentEntity, int sentenceIndex, NLCgenerateContextBlocksVariables* generateContextBlocksVariables)
{
	GIAentityNode* parentEntity = getParent(currentEntity, sentenceIndex, generateContextBlocksVariables);

	bool generatedContextBlocks = generateContextBlocks(currentCodeBlockInTree, parentEntity, sentenceIndex, generateContextBlocksVariables, false, NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION);

	return generatedContextBlocks;

}







bool NLCtranslatorCodeBlocksOperationsClass::generateContextForChildEntity(NLCcodeblock** currentCodeBlockInTree, GIAentityNode* entity, GIAentityNode* childEntity, int sentenceIndex, const bool topLevel, NLCgenerateContextBlocksVariables* generateContextBlocksVariablesLogicalConditionStatement)
{	
	#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_FOR_EACH_CHILD
	NLCgenerateContextBlocksVariables generateContextBlocksVariables = *generateContextBlocksVariablesLogicalConditionStatement;

	//OLD: research context in case, eg "The chicken has the ball which is near the park." (ie when initialisation property is definite; as distinguished from "The chicken has a ball near the park.")	
	bool generatedContextForChild = false;
	#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_FOR_EACH_CHILD_GET_PARENT
	bool foundDefiniteParentEntityNew = false;
	bool parseConditionParents = NLC_PARSE_CONDITION_PARENTS_DEFAULT_VALUE;
	bool checkIsDefinite = true;
	#ifdef NLC_TRANSLATOR_LOGICAL_CONDITIONS_BOOLEAN_STATEMENTS_INTERPRET_SUBJECT_AND_OBJECT_INDEPENDENTLY
	if(generateContextBlocksVariablesLogicalConditionStatement->logicalConditionStatement)
	{
		checkIsDefinite = false;
	}
	#endif
	#ifdef NLC_TRANSLATOR_LOGICAL_CONDITIONS_SINGLE_SENTENCE_MULTIPLE_LEVEL_FOR_LOOPS_OLD
	#ifdef NLC_TRANSLATOR_DO_NOT_REPARSE_CONTEXT_BLOCKS_IF_ALREADY_PARSED_DURING_ENTITY_INITIALISATION
	#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
	#ifndef NLC_GENERATE_UNIQUE_CONTEXT_BLOCK_FOR_EACH_SENTENCE_LOGICAL_CONDITIONS_FOR_LOOPS
	if(generateContextBlocksVariablesLogicalConditionStatement->setCodeBlockInTreeAtBaseLevel)
	{
		generateContextBlocksVariables.setCodeBlockInTreeAtBaseLevel = generateContextBlocksVariablesLogicalConditionStatement->setCodeBlockInTreeAtBaseLevel;
	}
	#endif
	#endif
	#endif
	#endif
	GIAentityNode* parentEntityNew = getSameReferenceSetUniqueParent(childEntity, sentenceIndex, entity, &foundDefiniteParentEntityNew, parseConditionParents, checkIsDefinite);
	if(foundDefiniteParentEntityNew)
	{
		//eg Tom has Jack's ball
		if(generateContextBlocksForParentEntity(currentCodeBlockInTree, childEntity, parentEntityNew, sentenceIndex, &generateContextBlocksVariables))
		{
			generatedContextForChild = true;
		}
		else
		{
			cout << "generateContextForChildEntity{}: generateContextBlocksForParentEntity{} error: !generatedContextForChild" << endl;
		}
	}
	#endif
	
	//if(assumedToAlreadyHaveBeenDeclared(childEntity))
	//{
		#ifndef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN
		#ifndef NLC_TRANSLATOR_GENERATE_CONTEXT_BLOCKS_PARSE_PARENT_EFFICIENT
		if(!generatedContextForChild)
		{
		#endif
		#endif
			//eg Tom has the blue ball 
			if(generateContextBlocks(currentCodeBlockInTree, childEntity, sentenceIndex, &generateContextBlocksVariables, generatedContextForChild, NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION))	//pass generatedContextForChild 1j10a
			{
				
			}
			
			generatedContextForChild = true;
			
		#ifndef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN
		#ifndef NLC_TRANSLATOR_GENERATE_CONTEXT_BLOCKS_PARSE_PARENT_EFFICIENT
		}
		#endif
		#endif				
	//}
	/*
	#ifdef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES	//ie #ifndef NLC_ADVANCED_REFERENCING
	else 
	{
		if(!generatedContextForChild)
		{
			//#ifdef NLC_DEBUG
			cout << "generateContextForChildEntity{}: generateContextBasedOnDeclaredParent: childEntity = " << childEntity->entityName << endl;
			cout << "generateContextForChildEntity childEntity = " << childEntity->entityName << "sentenceIndex = " << sentenceIndex << endl;		
			//#endif
			#ifdef NLC_DEBUG_PARSE_CONTEXT4
			*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockDebug(*currentCodeBlockInTree, string("generateContextForChildEntity{}: generateContextBasedOnDeclaredParent{childEntity}: ") + childEntity->entityName);
			#endif
			if(generateContextBasedOnDeclaredParent(childEntity, currentCodeBlockInTree, topLevel, entity, sentenceIndex, generateContextBlocksVariablesLogicalConditionStatement))
			{
				//for cases in which GIA advanced referencing has referenced entities whose parent was defined in a previous sentence;
				//eg 1 Tom's boat is red. The chicken rowed the red boat.
				//eg 2 Tom's boat is red. The red boat is new
				//NOT: Tom's boat is red. Tom's boat is new
				generatedContextForChild = true;
				#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_FOR_EACH_CHILD_GET_PARENT_ORIGINAL_IMPLEMENTATION		
				addIntermediaryImplicitlyDeclaredEntityToLocalList(currentCodeBlockInTree, childEntity, sentenceIndex);
				#endif
				childEntity->NLClocalListVariableHasBeenInitialised = true;	//added 1m4b
			}
		}
	}
	#endif
	*/
	#endif
	#ifdef NLC_TRANSLATOR_LOGICAL_CONDITIONS_SINGLE_SENTENCE_MULTIPLE_LEVEL_FOR_LOOPS_OLD
	#ifdef NLC_TRANSLATOR_DO_NOT_REPARSE_CONTEXT_BLOCKS_IF_ALREADY_PARSED_DURING_ENTITY_INITIALISATION
	#ifdef NLC_PREPROCESSOR_MATH_GENERATE_MATHTEXT_FROM_EQUIVALENT_NATURAL_LANGUAGE
	#ifndef NLC_GENERATE_UNIQUE_CONTEXT_BLOCK_FOR_EACH_SENTENCE_LOGICAL_CONDITIONS_FOR_LOOPS
	if(generateContextBlocksVariablesLogicalConditionStatement->setCodeBlockInTreeAtBaseLevel)
	{
		generateContextBlocksVariablesLogicalConditionStatement->currentCodeBlockInTreeAtBaseLevel = generateContextBlocksVariables.currentCodeBlockInTreeAtBaseLevel;
	}
	#endif
	#endif
	#endif
	#endif
			
	return generatedContextForChild;
}

bool NLCtranslatorCodeBlocksOperationsClass::generateContextBlocksForParentEntity(NLCcodeblock** currentCodeBlockInTree, GIAentityNode* childEntity, GIAentityNode* parentEntity, const int sentenceIndex, NLCgenerateContextBlocksVariables* generateContextBlocksVariables)
{
	bool result = false;
	
	#ifdef NLC_TRANSLATOR_GENERATE_CONTEXT_BLOCKS_PARSE_PARENT_EFFICIENT
	generateContextBlocksVariables->parseParentEfficient = true;
	generateContextBlocksVariables->childEntityNotToParse = childEntity;
	#endif
	
	if(generateContextBlocks(currentCodeBlockInTree, parentEntity, sentenceIndex, generateContextBlocksVariables, false, NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION))		//changed from generateCategories 1i11o
	{
		//eg Tom has Jack's blue ball
		#ifndef NLC_TRANSLATOR_GENERATE_CONTEXT_BLOCKS_PARSE_PARENT_EFFICIENT
		result = true;
		#endif
	}
		
	#ifdef NLC_TRANSLATOR_GENERATE_CONTEXT_BLOCKS_PARSE_PARENT_EFFICIENT
	generateContextBlocksVariables->parseParentEfficient = false;
	generateContextBlocksVariables->childEntityNotToParse = NULL;
	result = true;	//in case parent entity has no independent children (eg "red" in "The chicken's car" vs "The red chicken's car")
	#endif
		
	if(result)
	{
		#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN
		*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockForOrInPropertyList(*currentCodeBlockInTree, childEntity, NLCitemClass.generateInstanceName(parentEntity));	
		#endif

		#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_FOR_EACH_CHILD_GET_PARENT_ORIGINAL_IMPLEMENTATION		
		addIntermediaryImplicitlyDeclaredEntityToLocalList(currentCodeBlockInTree, childEntity, sentenceIndex);
		#endif
		childEntity->NLClocalListVariableHasBeenInitialised = true;
	}
	
	return result;
}


#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_FOR_EACH_CHILD_GET_PARENT
GIAentityNode* NLCtranslatorCodeBlocksOperationsClass::getSameReferenceSetUniqueParent(GIAentityNode* currentEntity, int sentenceIndex, GIAentityNode* generateObjectInitialisationsLastParent, bool* foundParentEntityNew, bool parseConditionParents, bool checkIsDefinite)
{
	*foundParentEntityNew = false;
	GIAentityNode* parentEntityNew = currentEntity;
	bool foundParentProperty = false;

	for(vector<GIAentityConnection*>::iterator propertyNodeListIterator = currentEntity->propertyReverseNodeList->begin(); propertyNodeListIterator < currentEntity->propertyReverseNodeList->end(); propertyNodeListIterator++)
	
	{
		GIAentityConnection* parentConnection = *propertyNodeListIterator;
		GIAentityNode* parentEntity = GIAtranslatorOperations.getPropertyRelationshipSubjectEntity(parentConnection);
		
		#ifdef NLC_DEFINE_LOCAL_VARIABLES_FOR_ALL_INDEFINATE_ENTITIES
		if(NLCcodeBlockClass.checkSentenceIndexParsingCodeBlocks(parentEntity, parentConnection, sentenceIndex, false))	//NB will parse references to entities in previous sentence
		#else
		if(NLCcodeBlockClass.checkSentenceIndexParsingCodeBlocks(parentEntity, parentConnection, sentenceIndex, false) || parentEntity->NLCparsedForCodeBlocks)
		#endif
		{
			if(parentConnection->sameReferenceSet)
			{
				//removed 1i11e, readded 1i11j
				if(parentEntity != generateObjectInitialisationsLastParent)
				{
					/*
					//added 1i11f, removed 1i11j
					if(!(parentEntity->NLCcontextGenerated))
					{
					*/
					if(NLCcodeBlockClass.isDefiniteEntity(parentEntity) || !checkIsDefinite)
					{
						bool foundParentEntityNewTemp = false;
						parentEntityNew = getSameReferenceSetUniqueParent(parentEntity, sentenceIndex, generateObjectInitialisationsLastParent, &foundParentEntityNewTemp, parseConditionParents, checkIsDefinite);
						*foundParentEntityNew = true;
						foundParentProperty = true;
					}
					/*	
					}
					*/
				}
			}
		}
	}

	#ifdef NLC_PARSE_CONDITION_PARENTS
	if(!foundParentProperty && parseConditionParents)
	{//added 1e9a
		for(vector<GIAentityConnection*>::iterator conditionNodeListIterator = currentEntity->conditionReverseNodeList->begin(); conditionNodeListIterator < currentEntity->conditionReverseNodeList->end(); conditionNodeListIterator++)
		{
			GIAentityConnection* conditionConnection = *conditionNodeListIterator;
			GIAentityNode* conditionRelationshipEntity = conditionConnection->entity;
			#ifdef NLC_NORMALISE_TWOWAY_PREPOSITIONS_DUAL_CONDITION_LINKS_ENABLED
			if(!(conditionRelationshipEntity->inverseConditionTwoWay) || conditionConnection->isReference)	//prevent infinite loop for 2 way conditions 
			{
			#endif
				bool foundConditionSubject = false;
				GIAentityNode* conditionRelationshipSubjectEntity = NULL;
				if(!(conditionRelationshipEntity->relationshipSubjectEntity->empty()))
				{
					conditionRelationshipSubjectEntity = (conditionRelationshipEntity->relationshipSubjectEntity->back())->entity;
					foundConditionSubject = true;

					#ifdef NLC_DEFINE_LOCAL_VARIABLES_FOR_ALL_INDEFINATE_ENTITIES
					if(NLCcodeBlockClass.checkSentenceIndexParsingCodeBlocks(conditionRelationshipSubjectEntity, conditionConnection, sentenceIndex, false))	//NB will parse references to entities in previous sentence
					#else
					if(NLCcodeBlockClass.checkSentenceIndexParsingCodeBlocks(conditionRelationshipSubjectEntity, conditionConnection, sentenceIndex, false) || conditionRelationshipSubjectEntity->NLCparsedForCodeBlocks)
					#endif
					{
						if(conditionConnection->sameReferenceSet)
						{
							//removed 1i11e, readded 1i11j
							if(conditionRelationshipSubjectEntity != generateObjectInitialisationsLastParent)
							{
								if(NLCcodeBlockClass.isDefiniteEntity(conditionRelationshipSubjectEntity) || !checkIsDefinite)
								{
									bool foundParentEntityNewTemp = false;
									parentEntityNew = getSameReferenceSetUniqueParent(conditionRelationshipSubjectEntity, sentenceIndex, generateObjectInitialisationsLastParent, &foundParentEntityNewTemp, parseConditionParents, checkIsDefinite);
									*foundParentEntityNew = true;
								}
							}
						}
					}
				}		
			#ifdef NLC_NORMALISE_TWOWAY_PREPOSITIONS_DUAL_CONDITION_LINKS_ENABLED
			}
			#endif
		}
	}
	#endif
		
	return parentEntityNew;
}
#endif




#ifdef NLC_GENERATE_OBJECT_INITIALISATIONS_BASED_ON_CONCEPTS
void NLCtranslatorCodeBlocksOperationsClass::generateObjectInitialisationsBasedOnConcepts(GIAentityNode* targetEntity, GIAentityNode* entity, NLCcodeblock** currentCodeBlockInTree, int sentenceIndex, const bool newlyDeclaredEntityInCategoryList)
{
	
	#ifdef NLC_GENERATE_OBJECT_INITIALISATIONS_BASED_ON_CONCEPTS_DEFINITIONS
	if(targetEntity != entity)
	{
		generateObjectInitialisationsBasedOnConceptsRecurse(targetEntity, entity, currentCodeBlockInTree, sentenceIndex, NULL, "", newlyDeclaredEntityInCategoryList);
	}
	#ifdef GIA_CREATE_NON_SPECIFIC_CONCEPTS_FOR_ALL_NETWORK_INDEXES
	else	
	{//first call to generateObjectInitialisationsBasedOnConcepts
		GIAentityNode* networkIndexEntity = GIAtranslatorOperations.getPrimaryNetworkIndexNodeDefiningInstance(entity);
		generateObjectInitialisationsBasedOnConcepts(targetEntity, networkIndexEntity, currentCodeBlockInTree, sentenceIndex, newlyDeclaredEntityInCategoryList);
	}
	#endif
	#else
	#ifndef GIA_CREATE_NON_SPECIFIC_CONCEPTS_FOR_ALL_NETWORK_INDEXES	//removed condition 1r2a
	//added 6 December 2013: take into account plain networkIndexes; eg "Dogs are fat. The dog rides the bike." <- the dog will be given the property 'fat'
	GIAentityNode* networkIndexEntity = GIAtranslatorOperations.getPrimaryNetworkIndexNodeDefiningInstance(entity);
	generateObjectInitialisationsBasedOnConceptsRecurse(targetEntity, networkIndexEntity, currentCodeBlockInTree, sentenceIndex, NULL, "", newlyDeclaredEntityInCategoryList);	
	#endif
	#endif
	
	for(vector<GIAentityConnection*>::iterator entityNodeDefinitionListIterator = entity->definitionNodeList->begin(); entityNodeDefinitionListIterator < entity->definitionNodeList->end(); entityNodeDefinitionListIterator++)
	{
		GIAentityConnection* definitionConnection = (*entityNodeDefinitionListIterator);
		//if(!(definitionConnection->NLCparsedForCodeBlocks))	//probably not required
		//{
		GIAentityNode* definitionRelationshipObjectEntity = GIAtranslatorOperations.getDefinitionRelationshipObjectEntity(definitionConnection);
		//check the definition is a concept
		#ifdef GIA_CREATE_NON_SPECIFIC_CONCEPTS_FOR_ALL_NETWORK_INDEXES
		if(definitionRelationshipObjectEntity->entityType == GIA_ENTITY_TYPE_CONCEPT)
		#else
		if((definitionRelationshipObjectEntity->entityType == GIA_ENTITY_TYPE_CONCEPT) || (definitionRelationshipObjectEntity->entityType == GIA_ENTITY_TYPE_NETWORK_INDEX))	//added (definitionRelationshipObjectEntity->entityType == GIA_ENTITY_TYPE_NETWORK_INDEX) 1r2a
		#endif
		{
			#ifndef NLC_TRANSLATOR_GENERATE_CONTEXT_BLOCKS_PARSE_DEFINITIONS
			definitionConnection->NLCparsedForCodeBlocks = true;
			#endif
		
			
			#ifdef NLC_GENERATE_OBJECT_INITIALISATIONS_BASED_ON_CONCEPTS_DEFINITIONS
			generateObjectInitialisationsBasedOnConcepts(targetEntity, definitionRelationshipObjectEntity, currentCodeBlockInTree, sentenceIndex, newlyDeclaredEntityInCategoryList);
			#else
			generateObjectInitialisationsBasedOnConceptsRecurse(targetEntity, definitionRelationshipObjectEntity, currentCodeBlockInTree, sentenceIndex, NULL, "", newlyDeclaredEntityInCategoryList);
			#endif
			
			#ifndef NLC_GENERATE_OBJECT_INITIALISATIONS_BASED_ON_CONCEPTS_REMOVE_REDUNDANT_CODE
			//added 1q8b
			//DOING: check whether targetEntity needs to be replaced with entity
			if(definitionRelationshipObjectEntity->entityName != targetEntity->entityName)
			{
				GIAentityNode* definitionEntityNetworkIndexEntity = definitionRelationshipObjectEntity;
				#ifndef GIA_CREATE_NON_SPECIFIC_CONCEPTS_FOR_ALL_NETWORK_INDEXES
				if(!(definitionRelationshipObjectEntity->entityType == GIA_ENTITY_TYPE_NETWORK_INDEX))
				{
				#endif
					definitionEntityNetworkIndexEntity = GIAtranslatorOperations.getPrimaryNetworkIndexNodeDefiningInstance(definitionRelationshipObjectEntity);
				#ifndef GIA_CREATE_NON_SPECIFIC_CONCEPTS_FOR_ALL_NETWORK_INDEXES
				}
				#endif
				if(definitionEntityNetworkIndexEntity->NLClocalListVariableHasBeenDeclared)	//assumedToAlreadyHaveBeenDeclared(definitionRelationshipObjectEntity)
				{
					NLCcodeblock* firstCodeBlockInSection = *currentCodeBlockInTree;

					//#ifdef NLC_DEBUG
					cout << "generateObjectInitialisationsBasedOnConcepts{}: add targetEntity to definition local list; definitionRelationshipObjectEntity->entityName = " << definitionRelationshipObjectEntity->entityName << ", targetEntity->entityName = " << targetEntity->entityName << endl;
					//#endif
	
					*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockForLocalList(*currentCodeBlockInTree, targetEntity);

					*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockAddEntityToLocalList(*currentCodeBlockInTree, definitionRelationshipObjectEntity, targetEntity);	//this is required such that GIA can access the targetEntity by its parent name; eg Max is a red dog. The red dog is happy.

					*currentCodeBlockInTree = firstCodeBlockInSection->next;				
				}
			}
			#endif
		}
		//}
	}
}

void NLCtranslatorCodeBlocksOperationsClass::generateObjectInitialisationsBasedOnConceptsRecurse(GIAentityNode* targetEntity, GIAentityNode* definitionRelationshipObjectEntity, NLCcodeblock** currentCodeBlockInTree, int sentenceIndex, const GIAentityNode* parentEntity, const string parentConditionName, const bool newlyDeclaredEntityInCategoryList)
{
	string parentName = "";
	if(parentEntity != NULL)
	{
		parentName = NLCitemClass.generateInstanceName(parentEntity);
	}
	
	//property initialisations
	for(vector<GIAentityConnection*>::iterator propertyNodeListIterator = definitionRelationshipObjectEntity->propertyNodeList->begin(); propertyNodeListIterator < definitionRelationshipObjectEntity->propertyNodeList->end(); propertyNodeListIterator++)
	{
		GIAentityConnection* propertyConnection = (*propertyNodeListIterator);
		#ifdef GIA_ENABLE_CONCEPT_ADVANCED_REFERENCING
		if(!(propertyConnection->isReference))
		{
		#endif
			GIAentityNode* propertyRelationshipObjectEntity = GIAtranslatorOperations.getPropertyRelationshipObjectEntity(propertyConnection);

			bool alreadyAdded = NLCcodeBlockClass.checkDuplicateProperty(propertyRelationshipObjectEntity, targetEntity);
			if(!alreadyAdded)
			{
				NLCcodeblock* firstCodeBlockInSection = *currentCodeBlockInTree;
				bool loopUsed = false;

				#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_BLOCKS_FOR_PARENT_INITIALISATION_SPECIAL
				if(newlyDeclaredEntityInCategoryList)
				{
					*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockForCategoryList(*currentCodeBlockInTree, targetEntity, NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION, sentenceIndex);
				}
				else
				{
				#endif
					if(NLCcodeBlockClass.assumedToAlreadyHaveBeenDeclared(targetEntity))
					{
						*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockForLocalList(*currentCodeBlockInTree, targetEntity);
					}
					else
					{
						*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockForPropertyList(*currentCodeBlockInTree, targetEntity, parentName);
					}
				#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_BLOCKS_FOR_PARENT_INITIALISATION_SPECIAL
				}
				#endif

				*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockCreateNewProperty(*currentCodeBlockInTree, targetEntity, propertyRelationshipObjectEntity, sentenceIndex, false);

				targetEntity->NLCparsedForCodeBlocks = true;			//added NLC 1b6b/4 October 2013 - used for quick access of instances already declared in current context
				generateObjectInitialisationsBasedOnConceptsRecurse(targetEntity, propertyRelationshipObjectEntity, currentCodeBlockInTree, sentenceIndex, definitionRelationshipObjectEntity, "", true);		//updated 9 November 2013 - support recursion of complex concept definition

				*currentCodeBlockInTree = firstCodeBlockInSection->next;
			}
		#ifdef GIA_ENABLE_CONCEPT_ADVANCED_REFERENCING
		}
		#endif
	}
	//state initialisations
	for(vector<GIAentityConnection*>::iterator conditionNodeListIterator = definitionRelationshipObjectEntity->conditionNodeList->begin(); conditionNodeListIterator < definitionRelationshipObjectEntity->conditionNodeList->end(); conditionNodeListIterator++)
	{
		GIAentityConnection* conditionConnection = (*conditionNodeListIterator);
		#ifdef GIA_ENABLE_CONCEPT_ADVANCED_REFERENCING
		if(!(conditionConnection->isReference))
		{
		#endif
			GIAentityNode* conditionRelationshipEntity = conditionConnection->entity;

			#ifdef NLC_NORMALISE_TWOWAY_PREPOSITIONS_DUAL_CONDITION_LINKS_ENABLED
			if(!(conditionRelationshipEntity->inverseConditionTwoWay) || conditionConnection->isReference)	//prevent infinite loop for 2 way conditions
			{
			#endif		
				bool alreadyAdded = NLCcodeBlockClass.checkDuplicateCondition(conditionRelationshipEntity, targetEntity);
				if(!alreadyAdded)
				{
					NLCcodeblock* firstCodeBlockInSection = *currentCodeBlockInTree;

					bool foundConditionObject = false;
					GIAentityNode* conditionRelationshipObjectEntity = NULL;
					if(!(conditionRelationshipEntity->relationshipObjectEntity->empty()))
					{
						conditionRelationshipObjectEntity = (conditionRelationshipEntity->relationshipObjectEntity->back())->entity;
						foundConditionObject = true;


						#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_BLOCKS_FOR_PARENT_INITIALISATION_SPECIAL
						if(newlyDeclaredEntityInCategoryList)
						{
							*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockForCategoryList(*currentCodeBlockInTree, targetEntity, NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION, sentenceIndex);
						}
						else
						{
						#endif
							if(NLCcodeBlockClass.assumedToAlreadyHaveBeenDeclared(targetEntity))
							{
								*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockForLocalList(*currentCodeBlockInTree, targetEntity);
							}
							else
							{
								NLCitem* entityClass = new NLCitem(targetEntity, NLC_ITEM_TYPE_OBJECT);
								NLCitem* parentConditionItem = new NLCitem(parentConditionName, NLC_ITEM_TYPE_OBJECT);
								parentConditionItem->context.push_back(parentName);
								*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockForConditionList(*currentCodeBlockInTree, parentConditionItem, entityClass);
							}
						#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_BLOCKS_FOR_PARENT_INITIALISATION_SPECIAL
						}
						#endif

						*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockCreateNewCondition(*currentCodeBlockInTree, targetEntity, conditionRelationshipEntity, sentenceIndex, false);

						targetEntity->NLCparsedForCodeBlocks = true;			//added NLC 1b6b/4 October 2013 - used for quick access of instances already declared in current context
						generateObjectInitialisationsBasedOnConceptsRecurse(targetEntity, conditionRelationshipObjectEntity, currentCodeBlockInTree, sentenceIndex, definitionRelationshipObjectEntity, conditionRelationshipEntity->entityName, true);	//updated 9 November 2013 - support recursion of complex concept definition

						*currentCodeBlockInTree = firstCodeBlockInSection->next;

					}
				}
			#ifdef NLC_NORMALISE_TWOWAY_PREPOSITIONS_DUAL_CONDITION_LINKS_ENABLED
			}
			#endif
		#ifdef GIA_ENABLE_CONCEPT_ADVANCED_REFERENCING
		}
		#endif
	}
}
#endif


#ifdef NLC_ADVANCED_REFERENCING_SUPPORT_ALIASES

#ifdef NLC_ADVANCED_REFERENCING_SUPPORT_ALIASES_PREVENT_ADDING_AS_FUNCTION_ARGUMENT
//CURRENTLYILLEGAL: "Tom rides a bike. Tom is the red dog."
void NLCtranslatorCodeBlocksOperationsClass::fillFunctionAliasClassList(vector<GIAentityNode*>* entityNodesActiveListComplete)
{	
	for(vector<GIAentityNode*>::iterator entityIter = entityNodesActiveListComplete->begin(); entityIter != entityNodesActiveListComplete->end(); entityIter++)
	{
		GIAentityNode* aliasClassEntity = (*entityIter);

		for(vector<GIAentityConnection*>::iterator entityNodeDefinitionListIterator = aliasClassEntity->definitionNodeList->begin(); entityNodeDefinitionListIterator < aliasClassEntity->definitionNodeList->end(); entityNodeDefinitionListIterator++)
		{
			GIAentityConnection* definitionConnection = (*entityNodeDefinitionListIterator);
			GIAentityNode* aliasEntity = GIAtranslatorOperations.getDefinitionRelationshipObjectEntity(definitionConnection);

			if(GIAtranslatorOperations.connectionIsAlias(definitionConnection))
			{
				string aliasName = aliasEntity->entityName;
				string aliasClassName = aliasClassEntity->entityName;
					
				unordered_map<string, string>* functionAliasClassList = NLCcodeBlockClass.getFunctionAliasClassList();
				functionAliasClassList->insert(pair<string, string>(aliasName, aliasClassName));
			}
		}
	}
}
#endif

#endif

bool NLCtranslatorCodeBlocksOperationsClass::checkSpecialCaseEntity(const GIAentityNode* entity, const bool detectActions)
{
	bool specialCaseEntity = false;
	if((entity->entityType == GIA_ENTITY_TYPE_NETWORK_INDEX) || (entity->entityType == GIA_ENTITY_TYPE_CONCEPT) || (GIAentityNodeClass.entityIsRelationship(entity) && (entity->entityType != GIA_ENTITY_TYPE_ACTION)))
	{
		specialCaseEntity = true;
	}
	else if(detectActions && (entity->entityType == GIA_ENTITY_TYPE_ACTION))
	{
		specialCaseEntity = true;
	}
	return specialCaseEntity;
}	

bool NLCtranslatorCodeBlocksOperationsClass::checkNetworkIndexTypeEntity(const GIAentityNode* entity)
{
	bool networkIndexTypeEntity = false;
	if((entity->entityType == GIA_ENTITY_TYPE_NETWORK_INDEX) || (entity->entityType == GIA_ENTITY_TYPE_CONCEPT))
	{
		networkIndexTypeEntity = true;
	}
	return networkIndexTypeEntity;
}
		

#ifdef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES
bool NLCtranslatorCodeBlocksOperationsClass::generateContextBasedOnDeclaredParent(GIAentityNode* entity, NLCcodeblock** currentCodeBlockInTree, const bool topLevel, const GIAentityNode* generateObjectInitialisationsLastParent, int sentenceIndex, const NLCgenerateContextBlocksVariables* generateContextBlocksVariablesLogicalConditionStatement)
{
	bool foundParentProperty = false;
	for(vector<GIAentityConnection*>::iterator propertyNodeListIterator = entity->propertyReverseNodeList->begin(); propertyNodeListIterator < entity->propertyReverseNodeList->end(); propertyNodeListIterator++)
	{
		GIAentityConnection* parentConnection = *propertyNodeListIterator;
		GIAentityNode* parentEntity = getPropertyRelationshipSubjectEntity(parentConnection);
				
		if(!foundParentProperty)
		{
			if(parentEntity->sentenceIndexTemp <= entity->sentenceIndexTemp)	//no strict same sentence check as this function assumes GIA referencing
			{
				if(!(parentEntity->disabled))
				{
					if(NLCcodeBlockClass.assumedToAlreadyHaveBeenDeclared(parentEntity))
					{
						if(parentEntity != generateObjectInitialisationsLastParent)	//added 1l7h
						{
							foundParentProperty = true;
							if(topLevel)
							{						
								*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockForLocalList(*currentCodeBlockInTree, parentEntity);	
							}
							
							*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockForPropertyList(*currentCodeBlockInTree, entity, NLCitemClass.generateInstanceName(parentEntity));	
							entity->NLCcontextGenerated = true;
							NLCgenerateContextBlocksVariables generateContextBlocksVariables = *generateContextBlocksVariablesLogicalConditionStatement;
							
							generateContextBlocks(currentCodeBlockInTree, entity, sentenceIndex, &generateContextBlocksVariables, true, NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION);		//added 1l13b
							//createCodeBlockForStatements(currentCodeBlockInTree, NLCitemClass.generateInstanceName(entity), entity, sentenceIndex, &generateContextBlocksVariables);	//added 1l13a	//or generateContextBlocksSimple(currentCodeBlockInTree, entity, sentenceIndex, &generateContextBlocksVariables, true, NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION)
	
							/*//alternative implementation not possible, because of "Tom's boat is red. The chicken rowed the red boat."
							if(generateContextBlocksSimple(currentCodeBlockInTree, entity, sentenceIndex, &generateContextBlocksVariables, false, NLC_ITEM_TYPE_CATEGORY_VAR_APPENDITION))
							{

							}
							*/
	
						}
					}
				}
			}
		}
	}
	return foundParentProperty;
}
#endif

#ifdef NLC_PARSE_OBJECT_CONTEXT_BEFORE_INITIALISE_ADVANCED_GENERATE_CONTEXT_FOR_EACH_CHILD_GET_PARENT_ORIGINAL_IMPLEMENTATION		
void NLCtranslatorCodeBlocksOperationsClass::addIntermediaryImplicitlyDeclaredEntityToLocalList(NLCcodeblock** currentCodeBlockInTree, const GIAentityNode* childEntity, const int sentenceIndex)
{
	#ifdef NLC_CATEGORIES_PARSE_CONTEXT_CHILDREN_DO_NOT_ADD_DUPLICATES
	#ifdef NLC_LOCAL_LISTS_USE_INSTANCE_NAMES
	*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockAddEntityToGenericListCheckLastSentenceReferencedPluralExecuteFunction(*currentCodeBlockInTree, childEntity, NLCitemClass.generateInstanceName(childEntity), NLC_ITEM_TYPE_INSTANCE_VAR_APPENDITION, childEntity, false);	
	#else
	*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockAddEntityToGenericListCheckLastSentenceReferencedPluralExecuteFunction(*currentCodeBlockInTree, childEntity, childEntity->entityName, NLC_ITEM_TYPE_CLASS_VAR_APPENDITION, childEntity, false);		//OR; ... , generateClassName(entity), "", ...		
	#endif
	#else
	*currentCodeBlockInTree = NLCcodeBlockClass.createCodeBlockAddEntityToLocalList(*currentCodeBlockInTree, childEntity, childEntity);	//removed 1j10a, restored 1j12b for NLC_LOCAL_LISTS_USE_INSTANCE_NAMES only, restored for !NLC_LOCAL_LISTS_USE_INSTANCE_NAMES 1l12a
	#endif
}
#endif
			

bool NLCtranslatorCodeBlocksOperationsClass::checkNumerosity(const GIAentityNode* entity)
{
	bool hasNumerosity = false;
	if((entity->hasQuantity) && (entity->grammaticalNumber == GRAMMATICAL_NUMBER_PLURAL))
	{
		hasNumerosity = true;
	}
	return hasNumerosity;
}
					
bool NLCtranslatorCodeBlocksOperationsClass::generateObjectInitialisationsAction(NLCcodeblock** currentCodeBlockInTree, GIAentityNode* actionRelationshipEntity, const int sentenceIndex)
{
	bool result = true;
	
	//declare an "abstract" variable for the action (that will be filled with the its properties and conditions) and passed as an argument to the function; eg "fast" of "run fast"
	if(!generateObjectInitialisations(currentCodeBlockInTree, actionRelationshipEntity, sentenceIndex))
	{
		result = false;
	}
	
	return result;
}

bool NLCtranslatorCodeBlocksOperationsClass::checkParentExists(GIAentityNode* object, const string parentName)
{
	bool result = false;
	if(object->entityName == parentName)
	{
		result = true;
	}
	for(vector<GIAentityConnection*>::iterator iter1 = object->definitionNodeList->begin(); iter1 < object->definitionNodeList->end(); iter1++) 
	{
		GIAentityNode* parent = GIAtranslatorOperations.getDefinitionRelationshipObjectEntity(*iter1);
		if(checkParentExists(parent, parentName))
		{
			result = true;
		}
	}
	return result;
}

#ifdef NLC_TRANSLATOR_LOGICAL_CONDITIONS_BOOLEAN_STATEMENTS_INTERPRET_SUBJECT_AND_OBJECT_INDEPENDENTLY
void NLCtranslatorCodeBlocksOperationsClass::secondaryComparisonSetIDinstance(GIAentityNode* entity)
{
	entity->NLCidInstanceBackup = entity->idInstance;
	entity->idInstance = NLC_TRANSLATOR_LOGICAL_CONDITIONS_BOOLEAN_STATEMENTS_INTERPRET_SUBJECT_AND_OBJECT_INDEPENDENTLY_COMPARISON_IDINSTANCE;
}
void NLCtranslatorCodeBlocksOperationsClass::secondaryComparisonRestoreIDinstance(GIAentityNode* entity)
{
	entity->idInstance = entity->NLCidInstanceBackup;
}
#endif



//based on checkIndefiniteEntityCorrespondingToDefiniteEntityInSameContextGIA from GIAtranslatorOperations.cpp
NLCpreprocessorSentence* NLCtranslatorCodeBlocksOperationsClass::getFirstNLCsentenceInList()
{
	return firstNLCsentenceInListLocal;
}
void NLCtranslatorCodeBlocksOperationsClass::setFirstNLCsentenceInList(NLCpreprocessorSentence* firstNLCsentenceInListNew)
{
	firstNLCsentenceInListLocal = firstNLCsentenceInListNew;
}
bool NLCtranslatorCodeBlocksOperationsClass::checkIndefiniteEntityCorrespondingToDefiniteEntityInSameContext(const GIAentityNode* indefiniteEntity, const GIAentityNode* definiteEntity, int* indentationDifferenceFound)
{
	bool foundIndefiniteEntity = false;

	if(indefiniteEntity->sentenceIndexTemp < definiteEntity->sentenceIndexTemp)
	{
		NLCpreprocessorSentence* firstNLCsentenceInList = getFirstNLCsentenceInList();
		bool foundIndefiniteEntitySentence = false;
		NLCpreprocessorSentence* indefiniteEntityNLCsentenceInList = NULL;
		if(NLCpreprocessorSentenceClass.getSentenceInSentenceList(indefiniteEntity->sentenceIndexTemp, firstNLCsentenceInList, &indefiniteEntityNLCsentenceInList))
		{
			foundIndefiniteEntitySentence = true;
		}
		
		if(foundIndefiniteEntitySentence)
		{
			bool foundDefiniteEntitySentence = false;
			NLCpreprocessorSentence* definiteEntityNLCsentenceInList = NULL;
			if(NLCpreprocessorSentenceClass.getSentenceInSentenceList(definiteEntity->sentenceIndexTemp, indefiniteEntityNLCsentenceInList, &definiteEntityNLCsentenceInList))
			{
				foundDefiniteEntitySentence = true;
			}
			
			NLCpreprocessorSentence* currentNLCsentenceInList = indefiniteEntityNLCsentenceInList;
			int minimumIndentationBetweenIndefiniteAndDefiniteEntitySentence = indefiniteEntityNLCsentenceInList->indentation;
			while(currentNLCsentenceInList != definiteEntityNLCsentenceInList)
			{
				if(currentNLCsentenceInList->indentation < minimumIndentationBetweenIndefiniteAndDefiniteEntitySentence)
				{
				       minimumIndentationBetweenIndefiniteAndDefiniteEntitySentence = currentNLCsentenceInList->indentation;
				}
				currentNLCsentenceInList = currentNLCsentenceInList->next;
			}

			
			if(foundDefiniteEntitySentence)
			{
				if(minimumIndentationBetweenIndefiniteAndDefiniteEntitySentence < indefiniteEntityNLCsentenceInList->indentation)
				{
				}
				else if(definiteEntityNLCsentenceInList->indentation < indefiniteEntityNLCsentenceInList->indentation)
				{
				}
				else
				{
				       foundIndefiniteEntity = true;
				       *indentationDifferenceFound = definiteEntityNLCsentenceInList->indentation - indefiniteEntityNLCsentenceInList->indentation;
				}
			}
			else
			{
			}
		}
		else
		{
		}
	}

	return foundIndefiniteEntity;
}








