#ifndef HEADER_NLC_GENERATED_pieClass
#define HEADER_NLC_GENERATED_pieClass

#include "NLClibraryGenericEntityClass.hpp"

class nearClass;
class appleClass;
class pieClass : public NLCgenericEntityClass
{
public:
	pieClass(void);
	unordered_map<nearClass*, appleClass*> nearClassappleClassConditionList;
};

#endif
