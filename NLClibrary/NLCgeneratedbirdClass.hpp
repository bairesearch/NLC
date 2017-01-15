#ifndef HEADER_NLC_GENERATED_birdClass
#define HEADER_NLC_GENERATED_birdClass

#include "NLClibraryGenericEntityClass.hpp"

class blueClass;
class nearClass;
class mountainClass;
class birdClass : public NLCgenericEntityClass
{
public:
	birdClass(void);
	vector<blueClass*> blueClassPropertyList;
	unordered_map<nearClass*, mountainClass*> nearClassmountainClassConditionList;
};

#endif
