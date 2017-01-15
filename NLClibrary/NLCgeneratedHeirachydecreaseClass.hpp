#include "NLClibraryGenericEntityClass.hpp"

class energyClass;
class decreaseClass : public NLCgenericEntityClass
{
public:
	decreaseClass(void);
	vector<energyClass*> energyClassActionSubjectList;
};

