// Fill out your copyright notice in the Description page of Project Settings.


#include "InfluenceDiag.h"

UInfluenceDiag::UInfluenceDiag(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{}

void UInfluenceDiag::Init()
{
	if (!initialized) {
		initialized = true;
	}

	switch (InferenceAlgorithm)
	{
	case InferenceIDAlgs::ShaferShenoyLIMID:
		inference = new gum::ShaferShenoyLIMIDInference<double>(&id);
		break;
	}
}

// Duplicate code (in BayesianNetwork.cpp)
void UInfluenceDiag::makeInference()
{
	try {
		inference->makeInference();
	}
	catch (gum::NotFound& e)
		UE_LOG(LogTemp, Warning, TEXT("%hs from %hs"), e.errorType().c_str(), e.errorContent().c_str());
}

// Duplicate code (in BayesianNetwork.cpp)
TMap<FString, float> UInfluenceDiag::getPosterior(FString variable)
{
	const std::string nodeName(TCHAR_TO_UTF8(*variable));
	TMap<FString, float> out;
	unsigned int j;

	try {
		gum::Potential<double> result = inference->posterior(nodeName);
		gum::Instantiation inst(result);

		for (inst.setFirst(), j = 0; !inst.end(); ++inst, ++j)
			out.Add(FString(result.variable(0).label(j).c_str()), result.get(inst));
	}
	catch (gum::NotFound& e)
		UE_LOG(LogTemp, Warning, TEXT("%hs from %hs"), e.errorType().c_str(), e.errorContent().c_str());

	return out;
}

// Duplicate code (in BayesianNetwork.cpp)
void UInfluenceDiag::addEvidence(FString variable, TArray<float> data)
{
	std::vector<double> vec;
	for (const float value : data)
		vec.push_back(value);

	auto var = TCHAR_TO_UTF8(*variable);

	if (inference->hasEvidence(var))
		inference->eraseEvidence(var);
	inference->addEvidence(var, vec);
}

// Duplicate code (in BayesianNetwork.cpp)
void UInfluenceDiag::eraseAllEvidence()
{
	inference->eraseAllEvidence();
}

// Duplicate code (in BayesianNetwork.cpp)
void UInfluenceDiag::eraseEvidence(FString variable)
{
	inference->eraseEvidence(TCHAR_TO_UTF8(*variable));
}

/*
void UInfluenceDiag::addDiscretizedVariable(FString variable, FString description, float minTick, float maxTick, float nPoints, InfluenceNodeType nodeType)
{
	if (!nodeNames.Contains(variable)) 
	{
		gum::DiscretizedVariable<float> newNode(TCHAR_TO_UTF8(*variable), TCHAR_TO_UTF8(*description));
		std::vector<float> ticks = myLinspace(minTick, maxTick, nPoints);

		for (float i : ticks)
			newNode.addTick(i);

		switch (nodeType) {
		case InfluenceNodeType::NORMAL: id.add(newNode); break;
		case InfluenceNodeType::CHANCE: id.addChanceNode(newNode); break;
		case InfluenceNodeType::UTILITY: id.addUtilityNode(newNode); break;
		case InfluenceNodeType::DECISION: id.addDecisionNode(newNode); break;
		}

		nodeNames.Add(variable);
		nodeDescriptions.Add(variable, description);
	}
}
*/

void UInfluenceDiag::addNode(FString variable, FString description, TArray<FString> labels, InfluenceNodeType nodeType)
{
	if (!nodeNames.Contains(variable))
	{
		gum::LabelizedVariable newNode(TCHAR_TO_UTF8(*variable), TCHAR_TO_UTF8(*description), 0);
		nodeNames.Add(variable);
		nodeDescriptions.Add(variable, description);

		for (FString label : labels)
			newNode.addLabel(TCHAR_TO_UTF8(*label));

		switch (nodeType) {
		case InfluenceNodeType::NORMAL: id.add(newNode); break;
		case InfluenceNodeType::CHANCE: id.addChanceNode(newNode); break;
		case InfluenceNodeType::UTILITY: id.addUtilityNode(newNode); break;
		case InfluenceNodeType::DECISION: id.addDecisionNode(newNode); break;
		}
	}
}

void UInfluenceDiag::addArc(FString parent, FString child)
{
	FString newArc = parent + "_" + child;

	for (FString arc : arcs)
		if (arc == newArc)
			return;

	try {
		id.addArc(TCHAR_TO_UTF8(*parent), TCHAR_TO_UTF8(*child));
		arcs.Add(newArc);
	}
	catch (gum::NotFound& e)
		UE_LOG(LogTemp, Warning, TEXT("%hs from %hs while adding arc"), e.errorType().c_str(), e.errorContent().c_str());
}

void UInfluenceDiag::fillCPT(FString variable, TArray<float> values)
{
	std::vector<double> cptValues;
	for (float value : values)
		cptValues.push_back(value);

	try {
		id.cpt(TCHAR_TO_UTF8(*variable)).fillWith(cptValues);
	}
	catch (gum::NotFound& e)
		UE_LOG(LogTemp, Warning, TEXT("%hs from %hs while filling"), e.errorType().c_str(), e.errorContent().c_str());
}

void UInfluenceDiag::fillUtility(FString variable, TArray<float> values)
{
	// TODO: add utility node check
	std::vector<double> utilityValues;
	for (float value : values)
		utilityValues.push_back(value);

	try {
		id.utility(TCHAR_TO_UTF8(*variable)).fillWith(utilityValues);
	}
	catch (gum::NotFound& e)
		UE_LOG(LogTemp, Warning, TEXT("%hs from %hs while filling"), e.errorType().c_str(), e.errorContent().c_str());
}


// TO TEST
void UInfluenceDiag::writeBIFXML(FString file)
{
	auto writer = gum::BIFXMLIDWriter<double>();
	writer.write(TCHAR_TO_UTF8(*file), id);
}

// TO TEST, duplicate code (in BayesianNetwork.cpp)
void UInfluenceDiag::erase(FString variable)
{
	const std::string nodeName(TCHAR_TO_UTF8(*variable));

	TArray<FString> toRemove;

	for (FString arc : arcs)
		if (arc.Contains(variable))
			toRemove.Add(arc);

	for (FString arc : toRemove)
		arcs.Remove(arc);

	id.erase(nodeName);
	nodeNames.Remove(variable);
	nodeDescriptions.Remove(variable);
}

// Duplicate code (in BayesianNetwork.cpp)
int UInfluenceDiag::idFromName(FString variable)
{
	return id.idFromName(TCHAR_TO_UTF8(*variable));
}
