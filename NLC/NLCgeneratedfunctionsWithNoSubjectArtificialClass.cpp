#include "NLCgeneratedfunctionsWithNoSubjectArtificialClass.hpp"
#include "NLClibrary.hpp"

functionsWithNoSubjectArtificialClass::functionsWithNoSubjectArtificialClass(void)
{
	name = "functionsWithNoSubjectArtificial";
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

void functionsWithNoSubjectArtificialClass::NLCimplicitlyDeclaredFunctionArtificialFunction(vector<NLCimplicitlyDeclaredFunctionArtificialClass*>& NLCimplicitlyDeclaredFunctionArtificialClassList, vector<valueClass*>& valueClassList, vector<chickenClass*>& chickenClassList)
{
	vector<NLCgenericEntityClass*> referenceContextList0;
	//The value = 4 + the number of chickens
	double* Thevalue1 = NULL;
	{
		vector<valueClass*> value1CategoryList;
		for(vector<valueClassClass*>::iterator iter2 = valueClassList.begin(); iter2 < valueClassList.end(); iter2++) 
		{
			valueClassClass* value1 = *iter2;
			//Singular definite referencing tests
			addToCategoryIfPassSingularDefiniteReferencingTests<valueClass, valueClass>(value1CategoryList, value1);
		}
		//Singular definite plurality tests
		if(!(value1CategoryList.empty()))
		{
			valueClass* value1 = value1CategoryList.back();
			value1->lastSentenceReferenced.top() = 1;
			Thevalue1 = &(value1->numericalValue);
		}
	}
	if(Thevalue1 == NULL)
	{
		cout << "NLC runtime error: math value pointer undefined (referenced value could not be found); mathText execution will crash" << endl;
	}
	int thenumberofchickens1 = 0;
	{
		vector<chickenClass*> chicken1CategoryList;
		for(vector<chickenClassClass*>::iterator iter2 = chickenClassList.begin(); iter2 < chickenClassList.end(); iter2++) 
		{
			chickenClassClass* chicken1 = *iter2;
			//Plural definite referencing tests
			addToCategoryIfPassPluralDefiniteReferencingTests<chickenClass, chickenClass>(chicken1CategoryList, chicken1);
		}
		for(vector<chickenClass*>::iterator iter2 = chicken1CategoryList.begin(); iter2 < chicken1CategoryList.end(); iter2++) 
		{
			chickenClass* chicken1 = *iter2;
			chicken1->lastSentenceReferenced.top() = 2;
			thenumberofchickens1 = thenumberofchickens1 + 1;
		}
	}
	*Thevalue1 = 4 + thenumberofchickens1;
	clearReferenceContextList(referenceContextList0);
}

int main()
{
	vector<NLCimplicitlyDeclaredFunctionArtificialClass*> NLCimplicitlyDeclaredFunctionArtificialClassList;
	vector<valueClass*> valueClassList;
	vector<chickenClass*> chickenClassList;
	(new functionsWithNoSubjectArtificialClass)->NLCimplicitlyDeclaredFunctionArtificialFunction(NLCimplicitlyDeclaredFunctionArtificialClassList, valueClassList, chickenClassList);
}
