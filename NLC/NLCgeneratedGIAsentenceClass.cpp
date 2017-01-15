#include "NLCgeneratedGIAsentenceClass.hpp"
#include "NLClibrary.hpp"

GIAsentenceClass::GIAsentenceClass(void)
{
	name = "GIAsentence";
	numericalValue = numeric_limits<double>::quiet_NaN();
	inverseConditionTwoWay = false;
	thirdpartyAPIobject = NULL;
	propertyLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("sentenceIndex", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&sentenceIndexClassPropertyList)));
	propertyLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("maxNumberOfWordsInSentence", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&maxNumberOfWordsInSentenceClassPropertyList)));
	propertyLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("firstRelationInList", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&firstRelationInListClassPropertyList)));
	propertyLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("firstFeatureInList", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&firstFeatureInListClassPropertyList)));
	propertyLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("next", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&nextClassPropertyList)));
	propertyLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("previous", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&previousClassPropertyList)));
	propertyLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("isQuestion", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&isQuestionClassPropertyList)));
	propertyLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("semanticParserSuccessful", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&semanticParserSuccessfulClassPropertyList)));
	propertyLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("conditionEntityArtificialIndexCurrent", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&conditionEntityArtificialIndexCurrentClassPropertyList)));
	propertyLists.insert(pair<string, vector<NLCgenericEntityClass*>*>("md", reinterpret_cast<vector<NLCgenericEntityClass*>*>(&mdClassPropertyList)));
}

void GIAsentenceClass::wrapThirdPartyAPIobject(GIAsentence* thirdpartyAPIobject)
{
	sentenceIndexClass* intermediaryVariable = new sentenceIndexClass();
	intermediaryVariable->thirdpartyAPIobject = thirdpartyAPIobject->sentenceIndex;
	sentenceIndexClassPropertyList.push_back(intermediaryVariable);
	maxNumberOfWordsInSentenceClass* intermediaryVariable = new maxNumberOfWordsInSentenceClass();
	intermediaryVariable->thirdpartyAPIobject = thirdpartyAPIobject->maxNumberOfWordsInSentence;
	maxNumberOfWordsInSentenceClassPropertyList.push_back(intermediaryVariable);
	firstRelationInListClass* intermediaryVariable = new firstRelationInListClass();
	intermediaryVariable->thirdpartyAPIobject = thirdpartyAPIobject->firstRelationInList;
	firstRelationInListClassPropertyList.push_back(intermediaryVariable);
	firstFeatureInListClass* intermediaryVariable = new firstFeatureInListClass();
	intermediaryVariable->thirdpartyAPIobject = thirdpartyAPIobject->firstFeatureInList;
	firstFeatureInListClassPropertyList.push_back(intermediaryVariable);
	nextClass* intermediaryVariable = new nextClass();
	intermediaryVariable->thirdpartyAPIobject = thirdpartyAPIobject->next;
	nextClassPropertyList.push_back(intermediaryVariable);
	previousClass* intermediaryVariable = new previousClass();
	intermediaryVariable->thirdpartyAPIobject = thirdpartyAPIobject->previous;
	previousClassPropertyList.push_back(intermediaryVariable);
	isQuestionClass* intermediaryVariable = new isQuestionClass();
	intermediaryVariable->booleanValue = thirdpartyAPIobject->isQuestion;
	isQuestionClassPropertyList.push_back(intermediaryVariable);
	semanticParserSuccessfulClass* intermediaryVariable = new semanticParserSuccessfulClass();
	intermediaryVariable->booleanValue = thirdpartyAPIobject->semanticParserSuccessful;
	semanticParserSuccessfulClassPropertyList.push_back(intermediaryVariable);
	conditionEntityArtificialIndexCurrentClass* intermediaryVariable = new conditionEntityArtificialIndexCurrentClass();
	intermediaryVariable->thirdpartyAPIobject = thirdpartyAPIobject->conditionEntityArtificialIndexCurrent;
	conditionEntityArtificialIndexCurrentClassPropertyList.push_back(intermediaryVariable);
}

void GIAsentenceClass::unwrapThirdPartyAPIobject(GIAsentence* thirdpartyAPIobject)
{
	sentenceIndexClass* sentenceIndex0 = sentenceIndexClassPropertyList.back();
	thirdpartyAPIobject->sentenceIndex = sentenceIndex0->thirdpartyAPIobject;
	maxNumberOfWordsInSentenceClass* maxNumberOfWordsInSentence0 = maxNumberOfWordsInSentenceClassPropertyList.back();
	thirdpartyAPIobject->maxNumberOfWordsInSentence = maxNumberOfWordsInSentence0->thirdpartyAPIobject;
	firstRelationInListClass* firstRelationInList0 = firstRelationInListClassPropertyList.back();
	thirdpartyAPIobject->firstRelationInList = firstRelationInList0->thirdpartyAPIobject;
	firstFeatureInListClass* firstFeatureInList0 = firstFeatureInListClassPropertyList.back();
	thirdpartyAPIobject->firstFeatureInList = firstFeatureInList0->thirdpartyAPIobject;
	nextClass* next0 = nextClassPropertyList.back();
	thirdpartyAPIobject->next = next0->thirdpartyAPIobject;
	previousClass* previous0 = previousClassPropertyList.back();
	thirdpartyAPIobject->previous = previous0->thirdpartyAPIobject;
	isQuestionClass* isQuestion0 = isQuestionClassPropertyList.back();
	thirdpartyAPIobject->isQuestion = isQuestion0->booleanValue;
	semanticParserSuccessfulClass* semanticParserSuccessful0 = semanticParserSuccessfulClassPropertyList.back();
	thirdpartyAPIobject->semanticParserSuccessful = semanticParserSuccessful0->booleanValue;
	conditionEntityArtificialIndexCurrentClass* conditionEntityArtificialIndexCurrent0 = conditionEntityArtificialIndexCurrentClassPropertyList.back();
	thirdpartyAPIobject->conditionEntityArtificialIndexCurrent = conditionEntityArtificialIndexCurrent0->thirdpartyAPIobject;
}

void GIAsentenceClass::wrapThirdPartyAPIfunctioninsertMember(vector<mdClass*>& mdClassList)
{
	MemberDef* md = new MemberDef();
	mdClass* md0 = mdClassList.back();
	md = md0->thirdpartyAPIobject;
	insertMember(md);
}

