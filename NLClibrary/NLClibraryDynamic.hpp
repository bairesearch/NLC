#ifndef HEADER_NLC_LIBRARY_DYNAMIC
#define HEADER_NLC_LIBRARY_DYNAMIC

#include "NLClibraryGenericEntityClass.hpp"
#include "NLClibraryDynamicfunctionsWithNoSubjectArtificialClass.hpp"
#include "NLClibraryDynamicmoveClass.hpp"
#include "NLClibraryDynamicfileClass.hpp"
#include "NLClibraryDynamictoClass.hpp"
#include "NLClibraryDynamiclandClass.hpp"

NLCgenericEntityClass* generateObjectByName(string name);
NLCgenericEntityClass* copyObjectByName(string name, NLCgenericEntityClass* entityToCopy);

#endif
