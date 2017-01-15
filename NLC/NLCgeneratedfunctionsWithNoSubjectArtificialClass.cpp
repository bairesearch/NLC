#include "NLCgeneratedfunctionsWithNoSubjectArtificialClass.hpp"
#include "NLClibrary.hpp"

functionsWithNoSubjectArtificialClass::functionsWithNoSubjectArtificialClass(void)
{
	name = "functionsWithNoSubjectArtificial";
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

void functionsWithNoSubjectArtificialClass::NLCimplicitlyDeclaredFunctionArtificialFunction(vector<NLCimplicitlyDeclaredFunctionArtificialClass*>& NLCimplicitlyDeclaredFunctionArtificialClassList, vector<moduleClass*>& moduleClassList)
{
	vector<NLCgenericEntityClass*> referenceContextList0;
	vector<bikeClass*> bikeClassList;
	vector<somethingClass*> somethingClassList;
	//The module thinks about a bike.
	{
		vector<thinkClass*> thinkClassList;
		vector<thinkClass*> think1CategoryList;
		thinkClass* think1 = addNewEntityToLocalList<thinkClass>(&(thinkClassList));
		think1CategoryList.push_back(think1);
		addEntityToReferenceContextList(referenceContextList0, think1, 1);
		for(vector<thinkClass*>::iterator iter2 = think1CategoryList.begin(); iter2 < think1CategoryList.end(); iter2++) 
		{
			thinkClass* think1 = *iter2;
			vector<bikeClass*> bike1CategoryList;
			bikeClass* bike1 = addNewEntityToLocalList<bikeClass>(&(bikeClassList));
			bike1CategoryList.push_back(bike1);
			addEntityToReferenceContextList(referenceContextList0, bike1, 1);
			for(vector<bikeClass*>::iterator iter3 = bike1CategoryList.begin(); iter3 < bike1CategoryList.end(); iter3++) 
			{
				bikeClass* bike1 = *iter3;
				addCondition<thinkClass, aboutClass, bikeClass>(think1, &(think1->aboutClassbikeClassConditionList), "about", bike1);
			}
		}
		vector<moduleClass*> module1SubjectCategoryList;
		vector<moduleClass*> module1CategoryList;
		for(vector<moduleClass*>::iterator iter2 = moduleClassList.begin(); iter2 < moduleClassList.end(); iter2++) 
		{
			moduleClass* module1 = *iter2;
			//Singular definite referencing tests
			addToCategoryIfPassSingularDefiniteReferencingTests<moduleClass, moduleClass>(module1CategoryList, module1);
		}
		//Singular definite plurality tests
		if(!(module1CategoryList.empty()))
		{
			moduleClass* module1 = module1CategoryList.back();
			module1->lastSentenceReferenced.top() = 1;
			addToCategoryIfPassPluralDefiniteReferencingTests<moduleClass, moduleClass>(module1SubjectCategoryList, module1);
		}
		for(vector<moduleClass*>::iterator iter2 = module1SubjectCategoryList.begin(); iter2 < module1SubjectCategoryList.end(); iter2++) 
		{
			moduleClass* module1 = *iter2;
			addActionSubject<thinkClass, moduleClass>(think1, module1, &(module1->thinkClassActionList), &(think1->moduleClassActionSubjectList));
		}
		(new moduleClass)->thinkFunction(module1SubjectCategoryList, thinkClassList);
	}
	//The module that thinks about something is tall.
	{
		vector<moduleClass*> module2SubjectCategoryList;
		vector<moduleClass*> module2CategoryList;
		for(vector<moduleClass*>::iterator iter2 = moduleClassList.begin(); iter2 < moduleClassList.end(); iter2++) 
		{
			moduleClass* module2 = *iter2;
			for(vector<thinkClass*>::iterator iter3 = module2->thinkClassActionList.begin(); iter3 < module2->thinkClassActionList.end(); iter3++) 
			{
				thinkClass* think2 = *iter3;
				//Singular definite referencing tests
				addToCategoryIfPassSingularDefiniteReferencingTests<moduleClass, moduleClass>(module2CategoryList, module2);
			}
		}
		//Singular definite plurality tests
		if(!(module2CategoryList.empty()))
		{
			moduleClass* module2 = module2CategoryList.back();
			module2->lastSentenceReferenced.top() = 2;
			addToCategoryIfPassPluralDefiniteReferencingTests<moduleClass, moduleClass>(module2SubjectCategoryList, module2);
		}
		vector<tallClass*> tall1ObjectCategoryList;
		vector<tallClass*> tall1CategoryList;
		tallClass* tall1 = new tallClass();
		tall1CategoryList.push_back(tall1);
		addEntityToReferenceContextList(referenceContextList0, tall1, 2);
		for(vector<tallClass*>::iterator iter2 = tall1CategoryList.begin(); iter2 < tall1CategoryList.end(); iter2++) 
		{
			tallClass* tall1 = *iter2;
			addToCategoryIfPassPluralDefiniteReferencingTests<tallClass, tallClass>(tall1ObjectCategoryList, tall1);
		}
		for(vector<moduleClass*>::iterator iter2 = module2SubjectCategoryList.begin(); iter2 < module2SubjectCategoryList.end(); iter2++) 
		{
			moduleClass* module2 = *iter2;
			for(vector<tallClass*>::iterator iter3 = tall1ObjectCategoryList.begin(); iter3 < tall1ObjectCategoryList.end(); iter3++) 
			{
				tallClass* tall1 = *iter3;
				addProperty<moduleClass, tallClass>(module2, &(module2->tallClassPropertyList), tall1);
			}
		}
	}
	clearReferenceContextList(referenceContextList0);
}

int main()
{
	vector<NLCimplicitlyDeclaredFunctionArtificialClass*> NLCimplicitlyDeclaredFunctionArtificialClassList;
	vector<moduleClass*> moduleClassList;
	(new functionsWithNoSubjectArtificialClass)->NLCimplicitlyDeclaredFunctionArtificialFunction(NLCimplicitlyDeclaredFunctionArtificialClassList, moduleClassList);
}
