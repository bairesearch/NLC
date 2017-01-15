#include "NLCgeneratedfunctionsWithNoSubjectArtificialClass.hpp"
#include "NLClibrary.hpp"

functionsWithNoSubjectArtificialClass::functionsWithNoSubjectArtificialClass(void)
{
	name = "functionsWithNoSubjectArtificial";
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

void functionsWithNoSubjectArtificialClass::NLCimplicitlyDeclaredFunctionArtificialFunction(vector<NLCimplicitlyDeclaredFunctionArtificialClass*>& NLCimplicitlyDeclaredFunctionArtificialClassList, vector<tomClass*>& tomClassList)
{
	vector<NLCgenericEntityClass*> referenceContextList0;
	//Tom is happy.
	{
		vector<tomClass*> tom1SubjectCategoryList;
		vector<tomClass*> tom1CategoryList;
		for(vector<tomClass*>::iterator iter2 = tomClassList.begin(); iter2 < tomClassList.end(); iter2++) 
		{
			tomClass* tom1 = *iter2;
			//Singular definite referencing tests
			addToCategoryIfPassSingularDefiniteReferencingTests<tomClass, tomClass>(tom1CategoryList, tom1);
		}
		//Singular definite plurality tests
		if(!(tom1CategoryList.empty()))
		{
			tomClass* tom1 = tom1CategoryList.back();
			tom1->lastSentenceReferenced.top() = 1;
			addToCategoryIfPassPluralDefiniteReferencingTests<tomClass, tomClass>(tom1SubjectCategoryList, tom1);
		}
		vector<happyClass*> happy1ObjectCategoryList;
		vector<happyClass*> happy1CategoryList;
		happyClass* happy1 = new happyClass();
		happy1CategoryList.push_back(happy1);
		addEntityToReferenceContextList(referenceContextList0, happy1, 1);
		for(vector<happyClass*>::iterator iter2 = happy1CategoryList.begin(); iter2 < happy1CategoryList.end(); iter2++) 
		{
			happyClass* happy1 = *iter2;
			addToCategoryIfPassPluralDefiniteReferencingTests<happyClass, happyClass>(happy1ObjectCategoryList, happy1);
		}
		for(vector<tomClass*>::iterator iter2 = tom1SubjectCategoryList.begin(); iter2 < tom1SubjectCategoryList.end(); iter2++) 
		{
			tomClass* tom1 = *iter2;
			for(vector<happyClass*>::iterator iter3 = happy1ObjectCategoryList.begin(); iter3 < happy1ObjectCategoryList.end(); iter3++) 
			{
				happyClass* happy1 = *iter3;
				addProperty<tomClass, happyClass>(tom1, &(tom1->happyClassPropertyList), happy1);
			}
		}
	}
	clearReferenceContextList(referenceContextList0);
}

int main()
{
	vector<NLCimplicitlyDeclaredFunctionArtificialClass*> NLCimplicitlyDeclaredFunctionArtificialClassList;
	vector<tomClass*> tomClassList;
	(new functionsWithNoSubjectArtificialClass)->NLCimplicitlyDeclaredFunctionArtificialFunction(NLCimplicitlyDeclaredFunctionArtificialClassList, tomClassList);
}
