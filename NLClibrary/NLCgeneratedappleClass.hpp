#ifndef HEADER_NLC_GENERATED_appleClass
#define HEADER_NLC_GENERATED_appleClass

#include "NLCgeneratedfruitClass.hpp"

class onClass;
class treeClass;
class appleClass : public fruitClass
{
public:
	appleClass(void);
	unordered_map<onClass*, treeClass*> onClasstreeClassConditionList;
};

#endif
