// Fill out your copyright notice in the Description page of Project Settings.

#include "GeneralTTSComponent.h"

using namespace std;

// Sets default values for this component's properties
UGeneralTTSComponent::UGeneralTTSComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGeneralTTSComponent::BeginPlay()
{
	Super::BeginPlay();

	if (!Speaker) {
		Speaker = NewObject<UAudioComponent>(this);
		Speaker->RegisterComponent();
	}
}

// Called every frame
void UGeneralTTSComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (idSynthesisReady != "") {
		SynthesisReady.Broadcast(idSynthesisReady);
		idSynthesisReady = "";
	}
}

void UGeneralTTSComponent::getResult(FTTSData response, FString id)
{
	handle->TTSResultAvailableUnsubscribeUser(TTSResultAvailableHandle);
	handle->Shutdown();

	Buffer.Remove(id);
	Buffer.Add(id, response);
	idSynthesisReady = id;
}

void UGeneralTTSComponent::TTSSynthesize(FString ssml, FString id)
{
	FTTSResultAvailableDelegate TTSResultSubscriber;
	TTSResultSubscriber.BindUObject(this, &UGeneralTTSComponent::getResult);
	handle = GeneralTTSThread::setup(ssml, id, Endpoint);
	TTSResultAvailableHandle = handle->TTSResultAvailableSubscribeUser(TTSResultSubscriber);
}

USoundWave* UGeneralTTSComponent::TTSGetSound(FString id) {
    USoundWave* SyntheticVoice = NewObject<USoundWave>();
    SyntheticVoice->SetSampleRate(SamplingRate);
    SyntheticVoice->NumChannels = 1;

	if (HeaderBitsToTrim > 0 && HeaderBitsToTrim <= Buffer[id].AudioData.Num() * sizeof(uint8)) {
		int32 TrimmedDataSize = Buffer[id].AudioData.Num() - HeaderBitsToTrim;
		SyntheticVoice->RawPCMDataSize = TrimmedDataSize * sizeof(uint8);
		SyntheticVoice->Duration = (float)TrimmedDataSize / (2 * (float)SamplingRate);
		SyntheticVoice->RawPCMData = static_cast<uint8*>(FMemory::Malloc(SyntheticVoice->RawPCMDataSize));
		FMemory::Memcpy(SyntheticVoice->RawPCMData, Buffer[id].AudioData.GetData() + HeaderBitsToTrim, SyntheticVoice->RawPCMDataSize);
	}
	else {
		SyntheticVoice->RawPCMDataSize = Buffer[id].AudioData.Num() * sizeof(uint8);
		SyntheticVoice->Duration = (float)Buffer[id].AudioData.Num() / (2 * (float)SamplingRate);
		SyntheticVoice->RawPCMData = static_cast<uint8*>(FMemory::Malloc(SyntheticVoice->RawPCMDataSize));
		FMemory::Memcpy(SyntheticVoice->RawPCMData, Buffer[id].AudioData.GetData(), SyntheticVoice->RawPCMDataSize);
	}

	if (SecondsOfSilenceAtEnd > 0) {
		int32 SilenceSampleCount = FMath::RoundToInt(SecondsOfSilenceAtEnd * SamplingRate);	//Silence Sample to add
		int32 SilenceDataSize = SilenceSampleCount * sizeof(int16);
		int32 CombinedDataSize = SyntheticVoice->RawPCMDataSize + SilenceDataSize;
		uint8* CombinedData = static_cast<uint8*>(FMemory::Realloc(SyntheticVoice->RawPCMData, CombinedDataSize));	//Memory realloc

		if (CombinedData) {
			FMemory::Memset(CombinedData + SyntheticVoice->RawPCMDataSize, 0, SilenceDataSize);	//Adding silence bits (0)
			SyntheticVoice->RawPCMData = CombinedData;
			SyntheticVoice->RawPCMDataSize = CombinedDataSize;
			SyntheticVoice->Duration += SecondsOfSilenceAtEnd;
		}
		else {
			FMemory::Free(SyntheticVoice->RawPCMData);	//Failed Realloc
			SyntheticVoice->RawPCMData = nullptr;
			SyntheticVoice->RawPCMDataSize = 0;
			SyntheticVoice->Duration = 0;
		}
	}


    return SyntheticVoice;
}
