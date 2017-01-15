#include "NLClibraryGenericEntityClass.hpp"

class decreaseClass;
class energyClass : public NLCgenericEntityClass
{
public:
	energyClass(void);
	void decreaseFunction(vector<energyClass*>& energyClassList, vector<decreaseClass*>& decreaseClassList);
	vector<decreaseClass*> decreaseClassActionList;
};

