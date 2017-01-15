#include "NLCgeneratedfunctionsWithNoSubjectArtificialClass.hpp"
#include "NLClibrary.hpp"

functionsWithNoSubjectArtificialClass::functionsWithNoSubjectArtificialClass(void)
{
	name = "functionsWithNoSubjectArtificial";
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

void functionsWithNoSubjectArtificialClass::NLCimplicitlyDeclaredFunctionArtificialFunction(vector<NLCimplicitlyDeclaredFunctionArtificialClass*>& NLCimplicitlyDeclaredFunctionArtificialClassList, vector<sunClass*>& sunClassList, vector<cabbageClass*>& cabbageClassList)
{
	vector<NLCgenericEntityClass*> referenceContextList0;
	//If the sun fights, print the cabbage.
	bool thesunfights1 = false;
	vector<sunClass*> sun1CategoryList;
	int sun1CategoryListPropertyCount = 0;
	for(vector<sunClass*>::iterator iter1 = sunClassList.begin(); iter1 < sunClassList.end(); iter1++) 
	{
		sunClass* sun1 = *iter1;
		for(vector<fightClass*>::iterator iter2 = sun1->fightClassActionList.begin(); iter2 < sun1->fightClassActionList.end(); iter2++) 
		{
			fightClass* fight1 = *iter2;
			//Singular definite referencing tests
			addToCategoryIfPassSingularDefiniteReferencingTests<sunClass, sunClass> (sun1CategoryList, sun1);
			sun1CategoryListPropertyCount = sun1CategoryListPropertyCount + 1;
		}
	}
	if(!(sun1CategoryList.empty()))
	{
		sunClass* sun1 = sun1CategoryList.back();
		sun1->lastSentenceReferenced.top() = 1;
		thesunfights1 = true;
	}
	if(thesunfights1print )
	{
		vector<NLCgenericEntityClass*> referenceContextList1;
		//
		clearReferenceContextList(referenceContextList1);
	}
	clearReferenceContextList(referenceContextList0);
}

int main()
{
	vector<NLCimplicitlyDeclaredFunctionArtificialClass*> NLCimplicitlyDeclaredFunctionArtificialClassList;
	vector<sunClass*> sunClassList;
	vector<cabbageClass*> cabbageClassList;
	(new functionsWithNoSubjectArtificialClass)->NLCimplicitlyDeclaredFunctionArtificialFunction(NLCimplicitlyDeclaredFunctionArtificialClassList, sunClassList, cabbageClassList);
}
