#ifndef HEADER_NLC_GENERATED_cabbageClass
#define HEADER_NLC_GENERATED_cabbageClass

#include "NLClibraryGenericEntityClass.hpp"

class brownClass;
class happyClass;
class nearClass;
class boatClass;
class cabbageClass : public NLCgenericEntityClass
{
public:
	cabbageClass(void);
	vector<brownClass*> brownClassPropertyList;
	vector<happyClass*> happyClassPropertyList;
	unordered_map<nearClass*, boatClass*> nearClassboatClassConditionList;
};

#endif
