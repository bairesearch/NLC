/*******************************************************************************
 *
 * This file is part of BAIPROJECT.
 *
 * BAIPROJECT is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License version 3
 * only, as published by the Free Software Foundation.
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
 * File Name: NLPIclassDefinition.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2013 Baxter AI (baxterai.com)
 * Project: Natural Language Programming Interface (compiler)
 * Project Version: 1c3a 27-October-2013
 * Requirements: requires text parsed by NLP Parser (eg Relex; available in .CFF format <relations>)
 *
 *******************************************************************************/




#include "NLPIclassDefinition.h"


NLPIclassDefinition::NLPIclassDefinition(string newName)
{
	name = newName;	

	isActionOrConditionInstanceNotClass = false;
	actionOrConditionInstance = NULL;
}
NLPIclassDefinition::NLPIclassDefinition(void)
{
	name = "";	

	isActionOrConditionInstanceNotClass = false;
	actionOrConditionInstance = NULL;
}
NLPIclassDefinition::~NLPIclassDefinition(void)
{
}

/*
bool checkSentenceIndexParsingClassHeirarchy(GIAentityNode * entity, int sentenceIndex)
{
	bool result = false;
	if(((entity->sentenceIndexTemp == sentenceIndex) || (entity->wasReference)) && !(entity->parsedForNLPIclassHeirarchy))
	{
		result = true;
	}
	return result;
}
*/

NLPIclassDefinition * findClassDefinition(vector<NLPIclassDefinition *> * classDefinitionList, string className, bool * foundClassDefinition)
{
	NLPIclassDefinition * classDefinitionFound = NULL;
	for(vector<NLPIclassDefinition*>::iterator classDefinitionIter = classDefinitionList->begin(); classDefinitionIter != classDefinitionList->end(); classDefinitionIter++)
	{	
		NLPIclassDefinition *  currentClassDef = *classDefinitionIter;
		if(currentClassDef->name == className)
		{
			classDefinitionFound = currentClassDef;
			*foundClassDefinition = true;
		}
	}
	return classDefinitionFound;
} 
