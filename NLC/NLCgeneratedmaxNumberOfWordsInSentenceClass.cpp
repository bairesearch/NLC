#include "NLCgeneratedmaxNumberOfWordsInSentenceClass.hpp"
#include "NLClibrary.hpp"

maxNumberOfWordsInSentenceClass::maxNumberOfWordsInSentenceClass(void)
{
	name = "maxNumberOfWordsInSentence";
	numericalValue = numeric_limits<double>::quiet_NaN();
	propertyLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("int", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&intClassPropertyList)));
}

