#include "NLCgeneratedfunctionsWithNoSubjectArtificialClass.hpp"
#include "NLClibrary.hpp"

functionsWithNoSubjectArtificialClass::functionsWithNoSubjectArtificialClass(void)
{
	name = "functionsWithNoSubjectArtificial";
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

void functionsWithNoSubjectArtificialClass::NLCimplicitlyDeclaredFunctionArtificialFunction(vector<NLCimplicitlyDeclaredFunctionArtificialClass*>& NLCimplicitlyDeclaredFunctionArtificialInstanceList, vector<moduleClass*>& module1InstanceList)
{
	//The module that does something is tall.
	{
		vector<moduleClass*> module1SubjectCategoryList;
		vector<moduleClass*> module1CategoryList;
		for(vector<moduleClass*>::iterator iter2 = module1InstanceList.begin(); iter2 < module1InstanceList.end(); iter2++) 
		{
			moduleClass* module1 = *iter2;
			for(vector<doClass*>::iterator iter3 = module1->doClassActionList.begin(); iter3 < module1->doClassActionList.end(); iter3++) 
			{
				doClass* do1 = *iter3;
				for(vector<somethingClass*>::iterator iter4 = do1->somethingClassActionObjectList.begin(); iter4 < do1->somethingClassActionObjectList.end(); iter4++) 
				{
					somethingClass* something1 = *iter4;
					addToCategoryIfPassPluralDefiniteReferencingTests<moduleClass, moduleClass>(module1CategoryList, module1);
				}
			}
		}
		for(vector<moduleClass*>::iterator iter2 = module1CategoryList.begin(); iter2 < module1CategoryList.end(); iter2++) 
		{
			moduleClass* module1 = *iter2;
			addToCategoryIfPassPluralDefiniteReferencingTests<moduleClass, moduleClass>(module1SubjectCategoryList, module1);
		}
		vector<tallClass*> tall1ObjectCategoryList;
		vector<tallClass*> tall1InstanceList;
		tallClass* tall1 = addNewEntityToLocalList<tallClass>(&(tall1InstanceList));
		for(vector<tallClass*>::iterator iter2 = tall1InstanceList.begin(); iter2 < tall1InstanceList.end(); iter2++) 
		{
			tallClass* tall1 = *iter2;
			addToCategoryIfPassPluralDefiniteReferencingTests<tallClass, tallClass>(tall1ObjectCategoryList, tall1);
		}
		for(vector<moduleClass*>::iterator iter2 = module1SubjectCategoryList.begin(); iter2 < module1SubjectCategoryList.end(); iter2++) 
		{
			moduleClass* module1 = *iter2;
			for(vector<tallClass*>::iterator iter3 = tall1ObjectCategoryList.begin(); iter3 < tall1ObjectCategoryList.end(); iter3++) 
			{
				tallClass* tall1 = *iter3;
				addProperty<moduleClass, tallClass>(module1, &(module1->tallClassPropertyList), tall1);
			}
		}
		vector<moduleClass*> module1SubjectCategoryList;
		vector<moduleClass*> module1CategoryList;
		for(vector<moduleClass*>::iterator iter2 = module1InstanceList.begin(); iter2 < module1InstanceList.end(); iter2++) 
		{
			moduleClass* module1 = *iter2;
			for(vector<tallClass*>::iterator iter3 = module1->tallClassPropertyList.begin(); iter3 < module1->tallClassPropertyList.end(); iter3++) 
			{
				tallClass* tall1 = *iter3;
				for(vector<doClass*>::iterator iter4 = module1->doClassActionList.begin(); iter4 < module1->doClassActionList.end(); iter4++) 
				{
					doClass* do1 = *iter4;
					for(vector<somethingClass*>::iterator iter5 = do1->somethingClassActionObjectList.begin(); iter5 < do1->somethingClassActionObjectList.end(); iter5++) 
					{
						somethingClass* something1 = *iter5;
						addToCategoryIfPassPluralDefiniteReferencingTests<moduleClass, moduleClass>(module1CategoryList, module1);
					}
				}
			}
		}
		for(vector<moduleClass*>::iterator iter2 = module1CategoryList.begin(); iter2 < module1CategoryList.end(); iter2++) 
		{
			moduleClass* module1 = *iter2;
			addToCategoryIfPassPluralDefiniteReferencingTests<moduleClass, moduleClass>(module1SubjectCategoryList, module1);
		}
		for(vector<moduleClass*>::iterator iter2 = module1SubjectCategoryList.begin(); iter2 < module1SubjectCategoryList.end(); iter2++) 
		{
			moduleClass* module1 = *iter2;
			if(checkParentClassName(static_cast<NLCgenericEntityClass*>(new somethingClass), "module"))
			{
				somethingClass* something1 = static_cast<somethingClass*>(module1);
				something1->name = "something";
			}
		}
		vector<tallClass*> tall1SubjectCategoryList;
		vector<tallClass*> tall1CategoryList;
		for(vector<tallClass*>::iterator iter2 = tall1InstanceList.begin(); iter2 < tall1InstanceList.end(); iter2++) 
		{
			tallClass* tall1 = *iter2;
			addToCategoryIfPassPluralDefiniteReferencingTests<tallClass, tallClass>(tall1CategoryList, tall1);
		}
		for(vector<tallClass*>::iterator iter2 = tall1CategoryList.begin(); iter2 < tall1CategoryList.end(); iter2++) 
		{
			tallClass* tall1 = *iter2;
			addToCategoryIfPassPluralDefiniteReferencingTests<tallClass, tallClass>(tall1SubjectCategoryList, tall1);
		}
		for(vector<tallClass*>::iterator iter2 = tall1SubjectCategoryList.begin(); iter2 < tall1SubjectCategoryList.end(); iter2++) 
		{
			tallClass* tall1 = *iter2;
			if(checkParentClassName(static_cast<NLCgenericEntityClass*>(new somethingClass), "tall"))
			{
				somethingClass* something1 = static_cast<somethingClass*>(tall1);
				something1->name = "something";
				addProperty<moduleClass, somethingClass>(module1, &(module1->somethingClassPropertyList), something1);
			}
		}
	}
}

int main()
{
	vector<NLCimplicitlyDeclaredFunctionArtificialClass*> NLCimplicitlyDeclaredFunctionArtificialInstanceList;
	vector<moduleClass*> module1InstanceList;
	(new functionsWithNoSubjectArtificialClass)->NLCimplicitlyDeclaredFunctionArtificialFunction(NLCimplicitlyDeclaredFunctionArtificialInstanceList, module1InstanceList);
}
