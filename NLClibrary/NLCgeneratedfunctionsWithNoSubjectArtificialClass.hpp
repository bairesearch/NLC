#ifndef HEADER_NLC_GENERATED_functionsWithNoSubjectArtificialClass
#define HEADER_NLC_GENERATED_functionsWithNoSubjectArtificialClass

#include "NLClibraryGenericEntityClass.hpp"

class moveClass;
class NLCgenericEntityClass;
class mainClass;
class bikeClass;
class functionsWithNoSubjectArtificialClass : public NLCgenericEntityClass
{
public:
	functionsWithNoSubjectArtificialClass(void);
	void moveFunction(vector<moveClass*>& moveClassList, vector<NLCgenericEntityClass*>& NLCgenericEntityClassList);
	void mainFunction(vector<mainClass*>& mainClassList, vector<bikeClass*>& bikeClassList);
};

#endif
