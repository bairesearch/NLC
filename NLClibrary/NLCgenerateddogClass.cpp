#include "NLCgenerateddogClass.hpp"
#include "NLClibrary.hpp"

dogClass::dogClass(void)
{
	name = "dog";
	propertyLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("blue", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&blueClassPropertyList)));
	propertyLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("fat", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&fatClassPropertyList)));
	propertyLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("energy", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&energyClassPropertyList)));
	actionLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("ride", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&rideClassActionList)));
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

void dogClass::rideFunction(vector<dogClass*>& dogClassList, vector<rideClass*>& rideClassList, vector<bikeClass*>& bikeClassList)
{
	vector<NLCgenericEntityClass*> referenceContextList0;
	vector<energyClass*> energyClassList;
	//The dog's energy decreases.
	vector<decreaseClass*> decreaseClassList;
	vector<decreaseClass*> decrease1CategoryList;
	decreaseClass* decrease1 = addNewEntityToLocalList<decreaseClass>(&(decreaseClassList));
	decrease1CategoryList.push_back(decrease1);
	addEntityToReferenceContextList(referenceContextList0, decrease1, 1);
	vector<energyClass*> energy1SubjectCategoryList;
	vector<dogClass*> dog1CategoryList;
	for(vector<dogClass*>::iterator iter1 = dogClassList.begin(); iter1 < dogClassList.end(); iter1++) 
	{
		dogClass* dog1 = *iter1;
		//Singular definite referencing tests
		addToCategoryIfPassSingularDefiniteReferencingTests<dogClass, dogClass> (dog1CategoryList, dog1);
	}
	if(!(dog1CategoryList.empty()))
	{
		dogClass* dog1 = dog1CategoryList.back();
		dog1->lastSentenceReferenced.top() = 1;
		for(vector<energyClass*>::iterator iter2 = dog1->energyClassPropertyList.begin(); iter2 < dog1->energyClassPropertyList.end(); iter2++) 
		{
			energyClass* energy1 = *iter2;
			addToCategoryIfPassPluralDefiniteReferencingTests<energyClass, energyClass> (energyClassList, energy1);
			vector<energyClass*> energy1CategoryList;
			//Plural definite referencing tests
			addToCategoryIfPassPluralDefiniteReferencingTests<energyClass, energyClass> (energy1CategoryList, energy1);
			for(vector<energyClass*>::iterator iter3 = energy1CategoryList.begin(); iter3 < energy1CategoryList.end(); iter3++) 
			{
				energyClass* energy1 = *iter3;
				energy1->lastSentenceReferenced.top() = 1;
				addToCategoryIfPassPluralDefiniteReferencingTests<energyClass, energyClass> (energy1SubjectCategoryList, energy1);
			}
		}
	}
	for(vector<energyClass*>::iterator iter1 = energy1SubjectCategoryList.begin(); iter1 < energy1SubjectCategoryList.end(); iter1++) 
	{
		energyClass* energy1 = *iter1;
		addActionSubject<decreaseClass, energyClass>(decrease1, energy1, &(energy1->decreaseClassActionList), &(decrease1->energyClassActionSubjectList));
	}
	//(new energyClass)->decreaseFunction(energy1SubjectCategoryList, decreaseClassList);
	clearReferenceContextList(referenceContextList0);
}
