#include "NLCgeneratedfunctionsWithNoSubjectArtificialClass.hpp"
#include "NLClibrary.hpp"

functionsWithNoSubjectArtificialClass::functionsWithNoSubjectArtificialClass(void)
{
	name = "functionsWithNoSubjectArtificial";
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

void functionsWithNoSubjectArtificialClass::NLCimplicitlyDeclaredFunctionArtificialFunction(vector<NLCimplicitlyDeclaredFunctionArtificialClass*>& NLCimplicitlyDeclaredFunctionArtificialClassList, vector<ballClass*>& ballClassList, vector<goal_lineClass*>& goal_lineClassList)
{
	vector<NLCgenericEntityClass*> referenceContextList0;
	//The ball is near the goal line.
	{
		vector<ballClass*> ball1SubjectCategoryList;
		vector<ballClass*> ball1CategoryList;
		for(vector<ballClass*>::iterator iter2 = ballClassList.begin(); iter2 < ballClassList.end(); iter2++) 
		{
			ballClass* ball1 = *iter2;
			//Singular definite referencing tests
			addToCategoryIfPassSingularDefiniteReferencingTests<ballClass, ballClass>(ball1CategoryList, ball1);
		}
		//Singular definite plurality tests
		if(!(ball1CategoryList.empty()))
		{
			ballClass* ball1 = ball1CategoryList.back();
			ball1->lastSentenceReferenced.top() = 1;
			addToCategoryIfPassPluralDefiniteReferencingTests<ballClass, ballClass>(ball1SubjectCategoryList, ball1);
		}
		vector<goal_lineClass*> goal_line1ObjectCategoryList;
		vector<goal_lineClass*> goal_line1CategoryList;
		for(vector<goal_lineClass*>::iterator iter2 = goal_lineClassList.begin(); iter2 < goal_lineClassList.end(); iter2++) 
		{
			goal_lineClass* goal_line1 = *iter2;
			//Singular definite referencing tests
			addToCategoryIfPassSingularDefiniteReferencingTests<goal_lineClass, goal_lineClass>(goal_line1CategoryList, goal_line1);
		}
		//Singular definite plurality tests
		if(!(goal_line1CategoryList.empty()))
		{
			goal_lineClass* goal_line1 = goal_line1CategoryList.back();
			goal_line1->lastSentenceReferenced.top() = 1;
			addToCategoryIfPassPluralDefiniteReferencingTests<goal_lineClass, goal_lineClass>(goal_line1ObjectCategoryList, goal_line1);
		}
		for(vector<ballClass*>::iterator iter2 = ball1SubjectCategoryList.begin(); iter2 < ball1SubjectCategoryList.end(); iter2++) 
		{
			ballClass* ball1 = *iter2;
			for(vector<goal_lineClass*>::iterator iter3 = goal_line1ObjectCategoryList.begin(); iter3 < goal_line1ObjectCategoryList.end(); iter3++) 
			{
				goal_lineClass* goal_line1 = *iter3;
				addCondition<ballClass, nearClass, goal_lineClass>(ball1, &(ball1->nearClassgoal_lineClassConditionList), "near", goal_line1);
				addConditionInverse<goal_lineClass, nearClass, ballClass>(goal_line1, &(goal_line1->nearClassballClassConditionList), "near", ball1);
			}
		}
	}
	clearReferenceContextList(referenceContextList0);
}

int main()
{
	vector<NLCimplicitlyDeclaredFunctionArtificialClass*> NLCimplicitlyDeclaredFunctionArtificialClassList;
	vector<ballClass*> ballClassList;
	vector<goal_lineClass*> goal_lineClassList;
	(new functionsWithNoSubjectArtificialClass)->NLCimplicitlyDeclaredFunctionArtificialFunction(NLCimplicitlyDeclaredFunctionArtificialClassList, ballClassList, goal_lineClassList);
}
