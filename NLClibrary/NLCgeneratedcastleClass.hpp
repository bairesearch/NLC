#ifndef HEADER_NLC_GENERATED_castleClass
#define HEADER_NLC_GENERATED_castleClass

#include "NLClibraryGenericEntityClass.hpp"

class knightClass;
class declareClass;
class warClass;
class castleClass : public NLCgenericEntityClass
{
public:
	castleClass(void);
	vector<knightClass*> knightClassPropertyList;
	void declareFunction(vector<castleClass*>& castleClassList, vector<declareClass*>& declareClassList, vector<warClass*>& warClassList);
	vector<declareClass*> declareClassActionList;
};

#endif
