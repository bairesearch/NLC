#ifndef HEADER_NLC_GENERATED_fightClass
#define HEADER_NLC_GENERATED_fightClass

#include "NLClibraryGenericEntityClass.hpp"

class sunClass;
class fightClass : public NLCgenericEntityClass
{
public:
	fightClass(void);
	vector<sunClass*> sunClassActionSubjectList;
};

#endif
