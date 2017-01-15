#ifndef HEADER_NLC_GENERATED_dogClass
#define HEADER_NLC_GENERATED_dogClass

#include "NLClibraryGenericEntityClass.hpp"

class redClass;
class boneClass;
class dogClass : public NLCgenericEntityClass
{
public:
	dogClass(void);
	vector<redClass*> redClassPropertyList;
	vector<boneClass*> boneClassPropertyList;
};

#endif
