#include "NLClibraryGenericEntityClass.hpp"

class moveClass;
class fileClass : public NLCgenericEntityClass
{
public:
	fileClass(void);
	vector<moveClass*> moveClassActionIncomingList;
};

