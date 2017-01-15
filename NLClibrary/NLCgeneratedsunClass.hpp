#ifndef HEADER_NLC_GENERATED_sunClass
#define HEADER_NLC_GENERATED_sunClass

#include "NLClibraryGenericEntityClass.hpp"

class fightClass;
class sunClass : public NLCgenericEntityClass
{
public:
	sunClass(void);
	void fightFunction(vector<sunClass*>& sunClassList, vector<fightClass*>& fightClassList);
	vector<fightClass*> fightClassActionList;
};

#endif
