/*******************************************************************************
 *
 * This file is part of BAIPROJECT.
 *
 * BAIPROJECT is licensed under the GNU Affero General Public License
 * version 3, as published by the Free Software Foundation. The use of
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
 * File Name: NLCtranslatorCodeBlocksLogicalConditionsAdvanced.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2017 Baxter AI (baxterai.com)
 * Project: Natural Language Compiler
 * Project Version: 2e3a 16-December-2017
 * Requirements: requires text parsed by BAI General Intelligence Algorithm (GIA)
 *
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


