#include "NLClibraryGenericEntityClass.hpp"

class toClass;
class landClass;
class fileClass;
class moveClass : public NLCgenericEntityClass
{
public:
	moveClass(void);
	unordered_map<toClass*, landClass*> toClasslandClassConditionList;
	vector<fileClass*> fileClassActionObjectList;
};

