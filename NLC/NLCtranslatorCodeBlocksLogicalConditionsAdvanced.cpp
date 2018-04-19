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
 * File Name: NLCtranslatorCodeBlocksLogicalConditionsAdvanced.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2018 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler
 * Project Version: 2f7c 17-April-2018
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 * /
 *******************************************************************************/


#include "NLCtranslatorCodeBlocksLogicalConditionsAdvanced.hpp"

#ifdef NLC_PREPROCESSOR
static bool useNLCpreprocessor;
static NLCcodeblock* codeBlockAtPreviousLogicalConditionBaseLevelArray[NLC_PREPROCESSOR_MAX_INDENTATION_LEVELS];
void NLCtranslatorCodeBlocksLogicalConditionsAdvancedClass::initialiseLogicalConditionLevelRecordArray(const bool newUseNLCpreprocessor)
{
	useNLCpreprocessor = newUseNLCpreprocessor;
	for(int i=0; i<NLC_PREPROCESSOR_MAX_INDENTATION_LEVELS; i++)
	{
		codeBlockAtPreviousLogicalConditionBaseLevelArray[i] = NULL;
	}
}
bool NLCtranslatorCodeBlocksLogicalConditionsAdvancedClass::getUseNLCpreprocessor()
{
	return useNLCpreprocessor;
}
NLCcodeblock* NLCtranslatorCodeBlocksLogicalConditionsAdvancedClass::getCodeBlockAtPreviousLogicalConditionBaseLevelArray(const int index)
{
	return codeBlockAtPreviousLogicalConditionBaseLevelArray[index];
}
void NLCtranslatorCodeBlocksLogicalConditionsAdvancedClass::setCodeBlockAtPreviousLogicalConditionBaseLevelArray(const int index, NLCcodeblock* codeBlockToSet)
{
	codeBlockAtPreviousLogicalConditionBaseLevelArray[index] = codeBlockToSet;
}
#endif


#ifdef GIA_TRANSLATOR_DREAM_MODE_LINK_SPECIFIC_CONCEPTS_AND_ACTIONS
bool NLCtranslatorCodeBlocksLogicalConditionsAdvancedClass::searchForEquivalentSubnetToIfStatement(GIAentityNode* entityCompareNetworkIndex, GIAentityNode* entity, const bool compareConcepts)
{
	bool result = false;

	//code copied from identifyReferenceSetsSpecificConceptsAndLinkWithConcepts() in GIAtranslatorDefineReferencing.cpp

	int referenceSetID = NLC_LOGICAL_CONDITION_OPERATIONS_BASED_ON_ACTIONS_OR_NETWORK_INDEXES_DUMMY_REFERENCE_SET_ID;

	bool traceModeIsQuery = false;
	GIAreferenceTraceParameters referenceTraceParameters;
	referenceTraceParameters.referenceSetID = referenceSetID;
	referenceTraceParameters.sameReferenceSetTests = true;
	if(!compareConcepts)
	{
		referenceTraceParameters.linkSpecificConceptsAndActions = true;
	}

	for(vector<GIAentityConnection*>::iterator entityIter = entityCompareNetworkIndex->instanceNodeList->begin(); entityIter != entityCompareNetworkIndex->instanceNodeList->end(); entityIter++)
	{
		GIAentityNode* entityCompare = (*entityIter)->entity;

		if(!(entityCompare->disabled))
		{
			if(entity != entityCompare)
			{
				GIAqueryTraceParameters queryTraceParameters;		//not used


				int numberOfMatchedNodesTemp = 0;
				int numberOfMatchedNodesRequiredSynonymnDetectionTemp = 0;
				bool exactMatch = GIAquery.testReferencedEntityNodeForExactNameMatch2(entity, entityCompare, &numberOfMatchedNodesTemp, false, &numberOfMatchedNodesRequiredSynonymnDetectionTemp, traceModeIsQuery, &queryTraceParameters, &referenceTraceParameters);

				if(exactMatch)
				{
					if(numberOfMatchedNodesTemp > 0)
					{
						result = true;
					}
				}

				//now reset the matched nodes as unpassed (required such that they are retracable using a the different path)
				int irrelevant;
				string printEntityNodeString = "";
				bool traceInstantiations = GIA_QUERY_TRACE_NETWORK_INDEX_NODES_DEFINING_INSTANTIATIONS_VALUE;
				GIAquery.traceEntityNode(entityCompare, GIA_QUERY_TRACE_ENTITY_NODES_FUNCTION_RESET_TESTEDFORQUERYCOMPARISONTEMP, &irrelevant, &printEntityNodeString, NULL, traceInstantiations);
				GIAquery.traceEntityNode(entity, GIA_QUERY_TRACE_ENTITY_NODES_FUNCTION_RESET_TESTEDFORQUERYCOMPARISONTEMP, &irrelevant, &printEntityNodeString, NULL, traceInstantiations);
			}
		}
	}
	return result;
}
#endif


