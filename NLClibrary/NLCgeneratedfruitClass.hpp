#ifndef HEADER_NLC_GENERATED_fruitClass
#define HEADER_NLC_GENERATED_fruitClass

#include "NLClibraryGenericEntityClass.hpp"

class yellowClass;
class tastyClass;
class fruitClass : public NLCgenericEntityClass
{
public:
	fruitClass(void);
	vector<yellowClass*> yellowClassPropertyList;
	vector<tastyClass*> tastyClassPropertyList;
};

#endif
