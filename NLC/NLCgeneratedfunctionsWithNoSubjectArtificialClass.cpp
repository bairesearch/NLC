#include "NLCgeneratedfunctionsWithNoSubjectArtificialClass.hpp"
#include "NLClibrary.hpp"

functionsWithNoSubjectArtificialClass::functionsWithNoSubjectArtificialClass(void)
{
	name = "functionsWithNoSubjectArtificial";
	parentClassList.push_back(static_cast<NLCgenericEntityClass*>(new NLCgenericEntityClass));
}

void functionsWithNoSubjectArtificialClass::NLCimplicitlyDeclaredFunctionArtificialFunction(vector<NLCimplicitlyDeclaredFunctionArtificialClass*>& NLCimplicitlyDeclaredFunctionArtificialClassList, vector<cityClass*>& cityClassList, vector<mouseClass*>& mouseClassList, vector<rabbitClass*>& rabbitClassList, vector<bikeClass*>& bikeClassList)
{
	vector<NLCgenericEntityClass*> referenceContextList0;
	vector<nameClass*> nameClassList;
	vector<beClass*> beClassList;
	//If((The city's name == X) and (the mouse is happy) and (the rabbit is > tom))
	NLCgenericEntityClass* ThecitysnameS1P0 = NULL;
	{
		vector<cityClass*> city1CategoryList;
		for(vector<cityClass*>::iterator iter2 = cityClassList.begin(); iter2 < cityClassList.end(); iter2++) 
		{
			cityClass* city1 = *iter2;
			//Singular definite referencing tests
			addToCategoryIfPassSingularDefiniteReferencingTests<cityClass, cityClass>(city1CategoryList, city1);
		}
		//Singular definite plurality tests
		if(!(city1CategoryList.empty()))
		{
			cityClass* city1 = city1CategoryList.back();
			city1->lastSentenceReferenced.top() = 1;
			for(vector<nameClass*>::iterator iter3 = city1->nameClassPropertyList.begin(); iter3 < city1->nameClassPropertyList.end(); iter3++) 
			{
				nameClass* name1 = *iter3;
				addToCategoryIfPassPluralDefiniteReferencingTests<nameClass, nameClass>(nameClassList, name1);
				vector<nameClass*> name1CategoryList;
				//Plural definite referencing tests
				addToCategoryIfPassPluralDefiniteReferencingTests<nameClass, nameClass>(name1CategoryList, name1);
				for(vector<nameClass*>::iterator iter4 = name1CategoryList.begin(); iter4 < name1CategoryList.end(); iter4++) 
				{
					nameClass* name1 = *iter4;
					name1->lastSentenceReferenced.top() = 1;
					ThecitysnameS1P0 = name;
				}
			}
		}
	}
	bool themouseishappyS1P1 = false;
	{
		vector<mouseClass*> mouse1SubjectCategoryList;
		vector<mouseClass*> mouse1CategoryList;
		for(vector<mouseClass*>::iterator iter2 = mouseClassList.begin(); iter2 < mouseClassList.end(); iter2++) 
		{
			mouseClass* mouse1 = *iter2;
			//Singular definite referencing tests
			addToCategoryIfPassSingularDefiniteReferencingTests<mouseClass, mouseClass>(mouse1CategoryList, mouse1);
		}
		//Singular definite plurality tests
		if(!(mouse1CategoryList.empty()))
		{
			mouseClass* mouse1 = mouse1CategoryList.back();
			mouse1->lastSentenceReferenced.top() = 2;
			addToCategoryIfPassPluralDefiniteReferencingTests<mouseClass, mouseClass>(mouse1SubjectCategoryList, mouse1);
		}
		for(vector<mouseClass*>::iterator iter2 = mouse1SubjectCategoryList.begin(); iter2 < mouse1SubjectCategoryList.end(); iter2++) 
		{
			mouseClass* mouse1 = *iter2;
			for(vector<happyClass*>::iterator iter3 = mouse1->happyClassPropertyList.begin(); iter3 < mouse1->happyClassPropertyList.end(); iter3++) 
			{
				happyClass* happyCandidate = *iter3;
				themouseishappyS1P1 = true;
			}
		}
	}
	double* therabbitisS1P2 = NULL;
	{
		vector<rabbitClass*> rabbit1CategoryList;
		for(vector<rabbitClass*>::iterator iter2 = rabbitClassList.begin(); iter2 < rabbitClassList.end(); iter2++) 
		{
			rabbitClass* rabbit1 = *iter2;
			//Singular definite referencing tests
			addToCategoryIfPassSingularDefiniteReferencingTests<rabbitClass, rabbitClass>(rabbit1CategoryList, rabbit1);
		}
		//Singular definite plurality tests
		if(!(rabbit1CategoryList.empty()))
		{
			rabbitClass* rabbit1 = rabbit1CategoryList.back();
			rabbit1->lastSentenceReferenced.top() = 3;
			therabbitisS1P2 = &(rabbit1->numericalValue);
		}
	}
	if((testMathObjectValue((ThecitysnameS1P0, X)) && (themouseishappyS1P1) && (*therabbitisS1P2 > tom)))
	{
		vector<NLCgenericEntityClass*> referenceContextList1;
		//Ride the bike.
		{
			vector<rideClass*> rideClassList;
			vector<rideClass*> ride1CategoryList;
			rideClass* ride1 = addNewEntityToLocalList<rideClass>(&(rideClassList));
			ride1CategoryList.push_back(ride1);
			addEntityToReferenceContextList(referenceContextList1, ride1, 4);
			vector<bikeClass*> bike1ObjectCategoryList;
			vector<bikeClass*> bike1CategoryList;
			for(vector<bikeClass*>::iterator iter3 = bikeClassList.begin(); iter3 < bikeClassList.end(); iter3++) 
			{
				bikeClass* bike1 = *iter3;
				//Singular definite referencing tests
				addToCategoryIfPassSingularDefiniteReferencingTests<bikeClass, bikeClass>(bike1CategoryList, bike1);
			}
			//Singular definite plurality tests
			if(!(bike1CategoryList.empty()))
			{
				bikeClass* bike1 = bike1CategoryList.back();
				bike1->lastSentenceReferenced.top() = 4;
				addToCategoryIfPassPluralDefiniteReferencingTests<bikeClass, bikeClass>(bike1ObjectCategoryList, bike1);
			}
			for(vector<bikeClass*>::iterator iter3 = bike1ObjectCategoryList.begin(); iter3 < bike1ObjectCategoryList.end(); iter3++) 
			{
				bikeClass* bike1 = *iter3;
				addActionObject<rideClass, bikeClass>(ride1, bike1, &(bike1->rideClassActionIncomingList), &(ride1->bikeClassActionObjectList));
			}
			rideFunction(rideClassList, bike1ObjectCategoryList);
		}
		clearReferenceContextList(referenceContextList1);
	}
	clearReferenceContextList(referenceContextList0);
}

int main()
{
	vector<NLCimplicitlyDeclaredFunctionArtificialClass*> NLCimplicitlyDeclaredFunctionArtificialClassList;
	vector<cityClass*> cityClassList;
	vector<mouseClass*> mouseClassList;
	vector<rabbitClass*> rabbitClassList;
	vector<bikeClass*> bikeClassList;
	(new functionsWithNoSubjectArtificialClass)->NLCimplicitlyDeclaredFunctionArtificialFunction(NLCimplicitlyDeclaredFunctionArtificialClassList, cityClassList, mouseClassList, rabbitClassList, bikeClassList);
}
