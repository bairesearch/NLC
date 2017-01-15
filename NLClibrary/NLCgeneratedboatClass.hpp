#ifndef HEADER_NLC_GENERATED_boatClass
#define HEADER_NLC_GENERATED_boatClass

#include "NLClibraryGenericEntityClass.hpp"

class nearClass;
class cabbageClass;
class boatClass : public NLCgenericEntityClass
{
public:
	boatClass(void);
	unordered_map<nearClass*, cabbageClass*> nearClasscabbageClassConditionList;
};

#endif
