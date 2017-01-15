#ifndef HEADER_NLC_LIBRARY_DYNAMIC
#define HEADER_NLC_LIBRARY_DYNAMIC

#include "NLClibraryGenericEntityClass.hpp"
#include "NLCgeneratedHeirachyfunctionsWithNoSubjectArtificialClass.hpp"
#include "NLCgeneratedHeirachymoveClass.hpp"
#include "NLCgeneratedHeirachymainClass.hpp"
#include "NLCgeneratedHeirachyblueClass.hpp"
#include "NLCgeneratedHeirachydogClass.hpp"
#include "NLCgeneratedHeirachyfatClass.hpp"
#include "NLCgeneratedHeirachyrideClass.hpp"
#include "NLCgeneratedHeirachybikeClass.hpp"
#include "NLCgeneratedHeirachyenergyClass.hpp"
#include "NLCgeneratedHeirachydecreaseClass.hpp"

NLCgenericEntityClass* generateObjectByName(string name);
NLCgenericEntityClass* copyObjectByName(string name, NLCgenericEntityClass* entityToCopy);

#endif
