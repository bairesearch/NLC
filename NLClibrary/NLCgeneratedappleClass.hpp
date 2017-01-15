#ifndef HEADER_NLC_GENERATED_appleClass
#define HEADER_NLC_GENERATED_appleClass

#include "NLClibraryGenericEntityClass.hpp"

class happyClass;
class nearClass;
class pieClass;
class printClass;
class appleClass : public NLCgenericEntityClass
{
public:
	appleClass(void);
	vector<happyClass*> happyClassPropertyList;
	unordered_map<nearClass*, pieClass*> nearClasspieClassConditionList;
	vector<printClass*> printClassActionIncomingList;
};

#endif
