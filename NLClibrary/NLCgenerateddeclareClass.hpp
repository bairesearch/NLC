#ifndef HEADER_NLC_GENERATED_declareClass
#define HEADER_NLC_GENERATED_declareClass

#include "NLClibraryGenericEntityClass.hpp"

class castleClass;
class warClass;
class declareClass : public NLCgenericEntityClass
{
public:
	declareClass(void);
	vector<castleClass*> castleClassActionSubjectList;
	vector<warClass*> warClassActionObjectList;
};

#endif
